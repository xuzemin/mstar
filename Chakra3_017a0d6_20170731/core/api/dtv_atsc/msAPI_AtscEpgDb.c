
#include "Board.h"

#if( ENABLE_ATSC && ENABLE_ATSC_EPG_DB_2016 )

#include "debug.h"
#include "sysinfo.h"
#include "Utl.h"

#include "msAPI_AtscEpgDb.h"

#include "MApp_GlobalFunction.h"

//#include "MApp_GlobalSettingSt_Common.h"


#if defined(ATSC_EPGDB_BUF_LEN)&&(ATSC_EPGDB_BUF_LEN>0)
    #define API_ATSC_EPGDB_BUF_LEN  ATSC_EPGDB_BUF_LEN
    #define API_ATSC_EPGDB_BUF_ADR  ATSC_EPGDB_BUF_ADR
#else
    #define API_ATSC_EPGDB_BUF_LEN  EVENTDB_SDRAM_LEN
    #define API_ATSC_EPGDB_BUF_ADR  EVENTDB_SDRAM_ADR
#endif


#if 0//( API_ATSC_EPGDB_BUF_LEN < 0x400000 )
    #error "API_ATSC_EPGDB_BUF_LEN is too small"
#endif

//=================================================================================


#if( (ATSC_EPG_VIR_CH_NUM>1) ) // Multi-channel

  #if( (NEW_MAX_TAB_NUM == 8) ) //one-day
    #define ATSC_EPG_VIR_CH_EVENT_NUM   (120)
  #else // Multi-channel and multi-day
    #define ATSC_EPG_VIR_CH_EVENT_NUM   (120)
  #endif

#else // One channel and one day
    #define ATSC_EPG_VIR_CH_EVENT_NUM   (400) // 50 x 8

#endif

#define ATSC_EPG_EVENT_NUM          (ATSC_EPG_VIR_CH_NUM*ATSC_EPG_VIR_CH_EVENT_NUM)

#define ATSC_EPG_ETT_NUM            (ATSC_EPG_EVENT_NUM/3)//4000


typedef struct ATSC_EPGDB_PACK
{
    //U8 u8VirChInfo[ATSC_EPG_VIR_CH_NUM];
    //MS_EPG_EVENT_New astEvent[ATSC_EPG_VIR_CH_NUM][ATSC_EPG_VIR_CH_EVENT_NUM];
    MS_EPG_EVENT_New astEvent[ATSC_EPG_EVENT_NUM];

    MS_EPG_EVENT_ETT_New astEttData[ATSC_EPG_ETT_NUM];
} StuAtscEpgDbData;

static StuAtscEpgDbData* s_EpgDb_pstDbData = NULL;

typedef struct
{
    BOOLEAN bDbChanged;
} StuAtscEpgDbInfo;

static StuAtscEpgDbInfo s_EpgDb_stInfo;

static U8 s_bEpgDb_u8DebugMode = 0;

//=================================================================================

void msAPI_AtscEpgDb_PrintEventList(MS_EPG_EVENT_New* apstEventList[], U16 u16EventListMaxNum);

void msAPI_AtscEpgDb_DeleteEventsByUser(void);
void MApp_ATSC_EpgDb_DeleteEvents_CB(void);

//-----------------------------------------------------------------------------------------------

#define DEBUG_ATSC_EPG_MEM  0

void msAPI_AtscEpgDb_Init(void)
{
#if(DEBUG_ATSC_EPG_MEM)
    PRINT_CURRENT_LINE();

    msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_CYAN);

    printf("sizeof(MS_EPG_RATING)=%u\n", sizeof(MS_EPG_RATING));

    printf("sizeof(MS_EPG_Caption_Service_Item)=%u\n", sizeof(MS_EPG_Caption_Service_Item));
    printf("sizeof(MS_EPG_Caption_Service)=%u\n", sizeof(MS_EPG_Caption_Service));


    printf("sizeof(MS_EPG_EVENT_New)=%u\n", sizeof(MS_EPG_EVENT_New));
    printf("ATSC_EPG_EVENT_NUM=%u\n", ATSC_EPG_EVENT_NUM);
    printf(" ==> %u * %u =%u\n", sizeof(MS_EPG_EVENT_New), ATSC_EPG_EVENT_NUM,
                                (sizeof(MS_EPG_EVENT_New)* ATSC_EPG_EVENT_NUM) );


    printf("sizeof(MS_EPG_EVENT_ETT_New)=%u\n", sizeof(MS_EPG_EVENT_ETT_New));
    printf("ATSC_EPG_ETT_NUM=%u\n", ATSC_EPG_ETT_NUM);
    printf(" ==> %u * %u =%u\n", sizeof(MS_EPG_EVENT_ETT_New), ATSC_EPG_ETT_NUM,
                                (sizeof(MS_EPG_EVENT_ETT_New)* ATSC_EPG_ETT_NUM) );

    printf("sizeof(StuAtscEpgDbData)=%u(0x%X)\n", sizeof(StuAtscEpgDbData), sizeof(StuAtscEpgDbData));

    printf("API_ATSC_EPGDB_BUF_LEN=%u\n", API_ATSC_EPGDB_BUF_LEN);

    msDebug_ANSI_AllAttrOffText();
#endif

    // Check if EPG use size > mmap alloc size
    BUILD_ERROR_IF_TRUE( (sizeof(StuAtscEpgDbData)) > (API_ATSC_EPGDB_BUF_LEN) );

    s_EpgDb_pstDbData = (StuAtscEpgDbData*)MsOS_PA2KSEG0(API_ATSC_EPGDB_BUF_ADR);

    msAPI_AtscEpgDb_ResetDB();

    s_EpgDb_stInfo.bDbChanged = TRUE;
}

#define msAPI_AtscEpgDb_IsEventValid(u16EvtIdx)     (s_EpgDb_pstDbData->astEvent[(u16EvtIdx)].event_id != INVALID_EVENT_ID)
//#define msAPI_AtscEpgDb_IsEventInvalid(u16EvtIdx)   ( !msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
BOOLEAN msAPI_AtscEpgDb_Is_EventValid(U16 u16EvtIdx )
{
    if( u16EvtIdx >= ATSC_EPG_EVENT_NUM )
        return FALSE;

    if( s_EpgDb_pstDbData->astEvent[(u16EvtIdx)].event_id == INVALID_EVENT_ID )
        return FALSE;

    return TRUE;
}

void msAPI_AtscEpgDb_ResetDB(void)
{
    PRINT_CURRENT_LINE();
    MS_EPG_EVENT_New* pstEPG_EVENT_New;


    s_EpgDb_stInfo.bDbChanged = TRUE;


    // Reset All Event
    U16 u16EvtIdx;
    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        pstEPG_EVENT_New = &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);

        // Set event to invalid
        pstEPG_EVENT_New->event_id = INVALID_EVENT_ID;
        pstEPG_EVENT_New->u16SrcId = ATSC_EPG_INVALID_SRC_ID;

        //s_EpgDb_pstDbData->apstEventUserList[u16EvtIdx] = NULL;
    }

    // Reset All Ett
    U16 u16EttIdx;
    for( u16EttIdx = 0; u16EttIdx < ATSC_EPG_ETT_NUM; u16EttIdx += 1 )
    {
        s_EpgDb_pstDbData->astEttData[u16EttIdx].u16EttDataLen = 0;
        s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[0] = 0;
        s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[0] = 0;
    }

#if 0 // Add test event

    // Set event to invalid
    u16EvtIdx = 0;
    pstEPG_EVENT_New = &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);
    memset(pstEPG_EVENT_New, 0, sizeof(MS_EPG_EVENT_New));

    pstEPG_EVENT_New->event_id = 0x11;
    pstEPG_EVENT_New->u16SrcId = 0x12;

    pstEPG_EVENT_New->au8Title[0] = 0x12;
    pstEPG_EVENT_New->au8Title[1] = 0x34;
    pstEPG_EVENT_New->au8Title[2] = 0;
    pstEPG_EVENT_New->au8Title[3] = 0;

    pstEPG_EVENT_New->u16DbEttIdx = 0;

    u16EttIdx = 0;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].u16EttDataLen = 4;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[0] = 0x56;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[1] = 0x78;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[2] = 0;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[3] = 0;
#endif

}

void msAPI_AtscEpgDb_Set_DebugMode(U8 u8DebugMode)
{
    s_bEpgDb_u8DebugMode = u8DebugMode;
}

// If successful, return EventIdx
U16 msAPI_AtscEpgDb_Get_EmptyEventIdx(void)
{
    U16 u16EvtIdx;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( !msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            return u16EvtIdx;
        }
    }

    printf("\nError: Get empty event failed, need delete some event!\n");

    msAPI_AtscEpgDb_DeleteEventsByUser();

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( !msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            return u16EvtIdx;
        }
    }

    printf("\nError: Still empty!\n");

    return ATSC_EPG_INVALID_EVENT_IDX;
}

BOOLEAN msAPI_AtscEpgDb_Set_Event(U16 u16EvtIdx, const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New)
{
    if( u16EvtIdx >= ATSC_EPG_EVENT_NUM )
        return FALSE;

    s_EpgDb_pstDbData->astEvent[u16EvtIdx] = *pstMS_EPG_EVENT_New;

    return TRUE;
}

BOOLEAN msAPI_AtscEpgDb_Get_Event(U16 u16EvtIdx, MS_EPG_EVENT_New* pstMS_EPG_EVENT_New )
{
    if( u16EvtIdx >= ATSC_EPG_EVENT_NUM )
        return FALSE;

    *pstMS_EPG_EVENT_New = s_EpgDb_pstDbData->astEvent[u16EvtIdx];

    return TRUE;
}

const MS_EPG_EVENT_New* msAPI_AtscEpgDb_Get_Event_Pointer(U16 u16EvtIdx)
{
    if( u16EvtIdx >= ATSC_EPG_EVENT_NUM )
        return NULL;

    return &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);
}

U16 msAPI_AtscEpgDb_Get_Event_By_CH_EventId_Time(const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New)
{
    U16 u16EvtIdx;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            if( (s_EpgDb_pstDbData->astEvent[u16EvtIdx].event_id == pstMS_EPG_EVENT_New->event_id)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u8RfNum == pstMS_EPG_EVENT_New->u8RfNum)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16SrcId == pstMS_EPG_EVENT_New->u16SrcId)
              //&&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u8EitTblNumber == pstMS_EPG_EVENT_New->u8EitTblNumber)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u32TimeLen == pstMS_EPG_EVENT_New->u32TimeLen)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].start_time == pstMS_EPG_EVENT_New->start_time)
              )
            {
                return u16EvtIdx;
            }
        }
    }

    return ATSC_EPG_INVALID_EVENT_IDX;
}

U16 msAPI_AtscEpgDb_Get_Event_By_CH_EventId(const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New)
{
    U16 u16EvtIdx;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            if( (s_EpgDb_pstDbData->astEvent[u16EvtIdx].event_id == pstMS_EPG_EVENT_New->event_id)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u8RfNum == pstMS_EPG_EVENT_New->u8RfNum)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16SrcId == pstMS_EPG_EVENT_New->u16SrcId)
              )
            {
                return u16EvtIdx;
            }
        }
    }

    return ATSC_EPG_INVALID_EVENT_IDX;
}

BOOLEAN msAPI_AtscEpgDb_Add_Event(const MS_EPG_EVENT_New* pstMS_EPG_EVENT_New)
{
//printf("msAPI_AtscEpgDb_Add_Event()\n");

    // Check if this event-id exist
    U16 u16EventIdx = msAPI_AtscEpgDb_Get_Event_By_CH_EventId_Time(pstMS_EPG_EVENT_New);

    if( u16EventIdx == ATSC_EPG_INVALID_EVENT_IDX )// If event is not exist, get a empty event
    {
        u16EventIdx = msAPI_AtscEpgDb_Get_EmptyEventIdx();

        if( u16EventIdx == ATSC_EPG_INVALID_EVENT_IDX ) // Get empty fail
        {
            return FALSE;
        }
    }
    else // Event is exist
    {
        // Check Eit index
        if( pstMS_EPG_EVENT_New->u8EitTblNumber > s_EpgDb_pstDbData->astEvent[u16EventIdx].u8EitTblNumber )
        {
            // Skip this event
            //PRINT_CURRENT_LINE();
            //printf("Skip event!");
            return FALSE;
        }
    }

    msAPI_AtscEpgDb_Set_Event(u16EventIdx, pstMS_EPG_EVENT_New);

    return TRUE;
}

BOOLEAN msAPI_AtscEpgDb_Delete_Event(U16 u16EvtIdx)
{
    //printf("msAPI_AtscEpgDb_Delete_Event(%u)\n", u16EvtIdx);

    if( u16EvtIdx >= ATSC_EPG_EVENT_NUM )
        return FALSE;

    // If event is valid, delete Ett first
    if( s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16DbEttIdx < ATSC_EPG_ETT_NUM )
    {
        msAPI_AtscEpgDb_Delete_Ett(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16DbEttIdx);
    }

    s_EpgDb_pstDbData->astEvent[u16EvtIdx].event_id = INVALID_EVENT_ID;
    s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16SrcId = ATSC_EPG_INVALID_SRC_ID;

    return TRUE;
}

U16 msAPI_AtscEpgDb_Delete_Event_By_RfNum(U8 u8RfNum)
{
    printf("msAPI_AtscEpgDb_Delete_Event_By_RfNum(%u)\n", u8RfNum);

    if( u8RfNum >= 150 )
        return 0;


    U16 u16EvtIdx;
    const MS_EPG_EVENT_New* pstEPG_EVENT_New;
    U16 u16DeleteCount = 0;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            pstEPG_EVENT_New = &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);

            //printf("idx=%u, Rf=%u\n", u16EvtIdx, pstEPG_EVENT_New->u8RfNum);

            if( pstEPG_EVENT_New->u8RfNum == u8RfNum )
            {
                //printf("Del idx=%u, Rf=%u\n", u16EvtIdx, pstEPG_EVENT_New->u8RfNum);

                msAPI_AtscEpgDb_Delete_Event(u16EvtIdx);

                u16DeleteCount += 1;
            }
        }
    }

    printf(" => Total del count = %u\n", u16DeleteCount);

    return u16DeleteCount;
}

BOOLEAN msAPI_AtscEpgDb_SwapEvent(U16 u16EvtIdx1, U16 u16EvtIdx2)
{
    printf("SwapEvent(%u, %u)\n", u16EvtIdx1, u16EvtIdx2);

    if( u16EvtIdx1 >= ATSC_EPG_EVENT_NUM )
        return FALSE;

    if( u16EvtIdx2 >= ATSC_EPG_EVENT_NUM )
        return FALSE;


//    printf("&(s_EpgDb_pstDbData->astEvent[u16EvtIdx1]) =0x%X\n ", &(s_EpgDb_pstDbData->astEvent[u16EvtIdx1]) );
    MS_EPG_EVENT_New stMS_EPG_EVENT_New_Tmp = s_EpgDb_pstDbData->astEvent[u16EvtIdx1];

    s_EpgDb_pstDbData->astEvent[u16EvtIdx1] = s_EpgDb_pstDbData->astEvent[u16EvtIdx2];

    s_EpgDb_pstDbData->astEvent[u16EvtIdx2] = stMS_EPG_EVENT_New_Tmp;

    return TRUE;
}

U16 msAPI_AtscEpgDb_Get_MaxEventNum(void)
{
    return ATSC_EPG_EVENT_NUM;
}

U16 msAPI_AtscEpgDb_Get_EventNum(void)
{
    U16 u16EvtIdx;
    U16 u16Count = 0;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            u16Count += 1;
        }
    }

    return u16Count;
}

/*
U16 msAPI_AtscEpgDb_Get_EventIdx_BySrcId(U8 u8RfNum, U16 u16SrcId, U16 u16SrcEvtIdx )
{
    U16 u16EvtIdx;
    U16 u16Count = 0;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            if( (s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16SrcId == u16SrcId)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u8RfNum == u8RfNum)
              )
            {
                if( u16SrcEvtIdx == u16Count )
                {
                    return u16EvtIdx;
                }

                u16Count += 1;
            }
        }
    }

    return ATSC_EPG_INVALID_EVENT_IDX;
}
*/
/*
BOOLEAN msAPI_AtscEpgDb_Set_Event_BySrcId(U16 u16SrcId, U16 u16SrcEvtIdx, MS_EPG_EVENT_New* pstMS_EPG_EVENT_New)
{
    return TRUE;
}
*/
/*
BOOLEAN msAPI_AtscEpgDb_Get_Event_BySrcId(U8 u8RfNum, U16 u16SrcId, U16 u16SrcEvtIdx, MS_EPG_EVENT_New* pstMS_EPG_EVENT_New )
{
    U16 u16EvtIdx = msAPI_AtscEpgDb_Get_EventIdx_BySrcId( u8RfNum, u16SrcId, u16SrcEvtIdx );
    return msAPI_AtscEpgDb_Get_Event( u16EvtIdx, pstMS_EPG_EVENT_New );
}
*/

BOOLEAN msAPI_AtscEpgDb_Get_EventNum_BySrcId(U8 u8RfNum, U16 u16SrcId)
{
    U16 u16EvtIdx;
    U16 u16Count = 0;

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            if( (s_EpgDb_pstDbData->astEvent[u16EvtIdx].u16SrcId == u16SrcId)
              &&(s_EpgDb_pstDbData->astEvent[u16EvtIdx].u8RfNum == u8RfNum)
              )
            {
                u16Count += 1;
            }
        }
    }

    return u16Count;
}

// If successful, return EttIdx
U16 msAPI_AtscEpgDb_Get_EmptyEttIdx(void)
{
    U16 u16EttIdx;

    for( u16EttIdx = 0; u16EttIdx < ATSC_EPG_ETT_NUM; u16EttIdx += 1 )
    {
        if( s_EpgDb_pstDbData->astEttData[u16EttIdx].u16EttDataLen == 0 )
        {
            return u16EttIdx;
        }
    }

    return ATSC_EPG_INVALID_ETT_IDX;
}

BOOLEAN msAPI_AtscEpgDb_Set_Ett(U16 u16EttIdx, MS_EPG_EVENT_ETT_New* pstMS_EPG_EVENT_ETT_New)
{
    if( u16EttIdx >= ATSC_EPG_ETT_NUM )
        return FALSE;

    if( (pstMS_EPG_EVENT_ETT_New->u16EttDataLen == 0)
      &&(pstMS_EPG_EVENT_ETT_New->u16EttDataLen > ATSC_EPG_ETT_DATA_SIZE)
      )
    {
        return FALSE;
    }

    // pstMS_EPG_EVENT_ETT_New  ==> EpgDb
    memcpy( &(s_EpgDb_pstDbData->astEttData[u16EttIdx]), pstMS_EPG_EVENT_ETT_New, sizeof(MS_EPG_EVENT_ETT_New) );

    // Fill '0' for string end
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[ATSC_EPG_ETT_DATA_SIZE-1] = 0;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[ATSC_EPG_ETT_DATA_SIZE-2] = 0;

    return TRUE;
}

BOOLEAN msAPI_AtscEpgDb_Get_Ett(U16 u16EttIdx, MS_EPG_EVENT_ETT_New* pstMS_EPG_EVENT_ETT_New)
{
    if( u16EttIdx >= ATSC_EPG_ETT_NUM )
        return FALSE;

    // Check data...
    if( s_EpgDb_pstDbData->astEttData[u16EttIdx].u16EttDataLen > ATSC_EPG_ETT_DATA_SIZE )
    {
        s_EpgDb_pstDbData->astEttData[u16EttIdx].u16EttDataLen = 0;
        s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[0] = 0;
        s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[1] = 0;
    }

    // EpgDb  ==> pstMS_EPG_EVENT_ETT_New
    memcpy( pstMS_EPG_EVENT_ETT_New, &(s_EpgDb_pstDbData->astEttData[u16EttIdx]), sizeof(MS_EPG_EVENT_ETT_New) );

    return TRUE;
}

BOOLEAN msAPI_AtscEpgDb_Delete_Ett(U16 u16EttIdx)
{
    if( u16EttIdx >= ATSC_EPG_ETT_NUM )
        return FALSE;

    s_EpgDb_pstDbData->astEttData[u16EttIdx].u16EttDataLen = 0;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[0] = 0;
    s_EpgDb_pstDbData->astEttData[u16EttIdx].au8EttData[1] = 0;
    return TRUE;
}

U16 msAPI_AtscEpgDb_Set_EttData(MS_EPG_EVENT_ETT_New* pstMS_EPG_EVENT_ETT_New, U8* au8DataBuf, U16 u16DataLen)
{
    if( u16DataLen > (ATSC_EPG_ETT_DATA_SIZE-2) )
        u16DataLen = (ATSC_EPG_ETT_DATA_SIZE-2) ;

    pstMS_EPG_EVENT_ETT_New->u16EttDataLen = u16DataLen;

    memcpy(pstMS_EPG_EVENT_ETT_New->au8EttData, au8DataBuf, u16DataLen);

    pstMS_EPG_EVENT_ETT_New->au8EttData[u16DataLen] = 0;
    pstMS_EPG_EVENT_ETT_New->au8EttData[u16DataLen+1] = 0;

    return u16DataLen;
}

// Change this function to change sorting type
int msAPI_AtscEpgDb_CompareEvent(MS_EPG_EVENT_New* apstEventList[], U16 u16EvtIdx1, U16 u16EvtIdx2)
{
    // compare src id first
    if( apstEventList[u16EvtIdx1]->u16SrcId > apstEventList[u16EvtIdx2]->u16SrcId )
        return 1;

    else if( apstEventList[u16EvtIdx1]->u16SrcId < apstEventList[u16EvtIdx2]->u16SrcId )
        return -1;

    //  compare time
    if( apstEventList[u16EvtIdx1]->start_time > apstEventList[u16EvtIdx2]->start_time )
        return 1;
    else
        return -1;
}

#define DEBUG_SORT(x)   x

void msAPI_AtscEpgDb_SortEventList(MS_EPG_EVENT_New* apstEventList[], U16 u16EventListNum )
{
    DEBUG_SORT( printf("msAPI_AtscEpgDb_SortEventList(u16EventListNum=%u)\n", u16EventListNum); );

    if( u16EventListNum <= 1 )
    {
        // No need sort...
        return ;
    }

    // Sort all Event by time
    U16 u16EventCount = u16EventListNum;
    DEBUG_SORT( printf("u16EventCount=%u\n", u16EventCount ); );

    U16 u16Idx1, u16Idx2;
    for( u16Idx1 = 0; u16Idx1 < (u16EventCount-1); u16Idx1 += 1 ) // For 0 ~ N-2
    {
        DEBUG_SORT( printf("Sort-%u\n", u16Idx1); );
        for( u16Idx2 = u16Idx1+1; u16Idx2 < u16EventCount; u16Idx2 += 1 ) // For (u16Idx1+1) ~ N-1
        {
            //printf("%u %u\n", u16Idx1, u16Idx2 );
            // If u16Idx1 > u16Idx2, swap  ==> keep small one in front of list
            if( msAPI_AtscEpgDb_CompareEvent(apstEventList, u16Idx1, u16Idx2) > 0 )
            { // If u16Ord1 < u16Ord2, swap it
                // Swap Event(u16Idx1, u16Idx2);
                MS_EPG_EVENT_New* stMS_EPG_EVENT_New_Tmp = apstEventList[u16Idx1];
                apstEventList[u16Idx1] = apstEventList[u16Idx2];
                apstEventList[u16Idx2] = stMS_EPG_EVENT_New_Tmp;
            }
        }
    }

    s_EpgDb_stInfo.bDbChanged = FALSE;

    //msAPI_AtscEpgDb_PrintAllDb();
}

#if 0
void msAPI_AtscEpgDb_SortEvent(void)
{
    PRINT_CURRENT_LINE();

    if( s_EpgDb_stInfo.bDbChanged == FALSE ) // DB no changed
    {
        printf("Skip this time\n");
        return;
    }

    // Sort all Event by time
    //U16 u16EventCount = ATSC_EPG_EVENT_NUM;
    U16 u16EventCount = ATSC_EPG_EVENT_NUM;
    printf("u16EventCount=%u\n", u16EventCount );

    U16 u16Idx1, u16Idx2;
    for( u16Idx1 = 0; u16Idx1 < (u16EventCount-1); u16Idx1 += 1 ) // For 0 ~ N-2
    {
        printf("Sort-%u\n", u16Idx1);
        for( u16Idx2 = u16Idx1+1; u16Idx2 < u16EventCount; u16Idx2 += 1 ) // For (u16Idx1+1) ~ N-1
        {
            //printf("%u %u\n", u16Idx1, u16Idx2 );
            // If u16Idx1 > u16Idx2, swap  ==> keep small one in front of list
            if( msAPI_AtscEpgDb_CompareEvent(u16Idx1, u16Idx2) > 0 )
            { // If u16Ord1 < u16Ord2, swap it
                msAPI_AtscEpgDb_SwapEvent(u16Idx1, u16Idx2);
            }
        }
    }

    s_EpgDb_stInfo.bDbChanged = FALSE;

    msAPI_AtscEpgDb_PrintAllDb();
}
#endif

U32 msAPI_AtscEpgDb_Get_EventTimeLen( const MS_EPG_EVENT_New* pstEPG_EVENT_New)
{
    if( pstEPG_EVENT_New == NULL )
        return 0;

    //return EPG_EVENT_LENGTH(pstEPG_EVENT_New->length[0],pstEPG_EVENT_New->length[1],pstEPG_EVENT_New->length[2];
    return pstEPG_EVENT_New->u32TimeLen;
}

U32 msAPI_AtscEpgDb_Get_EventTimeEnd( const MS_EPG_EVENT_New* pstEPG_EVENT_New)
{
    if( pstEPG_EVENT_New == NULL )
        return 0;

    return pstEPG_EVENT_New->start_time + pstEPG_EVENT_New->u32TimeLen;
}

U8 msAPI_AtscEpgDb_Get_EventTitle( const MS_EPG_EVENT_New* pstEPG_EVENT_New, U8* pu8TitleBuf, U8 u8TitleBufLen)
{
    if( pstEPG_EVENT_New == NULL )
        return 0;

    if( pu8TitleBuf == NULL )
        return 0;

    if( u8TitleBufLen < 2 )
        return 0;


    U8 u8CopySize = pstEPG_EVENT_New->u8TitleLen;

    if( u8CopySize > (u8TitleBufLen-2) )
    {
        u8CopySize = (u8TitleBufLen-2);
    }

    if( u8CopySize > 0 )
    {
        memcpy(pu8TitleBuf, pstEPG_EVENT_New->au8Title, u8CopySize);
    }

    pu8TitleBuf[u8CopySize] = 0;
    pu8TitleBuf[u8CopySize+1] = 0;

    return u8CopySize;
}

#define EPG_IS_IN_RANGE(a,x,y)  ( ((x) <= (a)) && ((a) < (y)) )

#define EPG_CHECK_TIME(a,b,x,y) (\
      ( EPG_IS_IN_RANGE( (x),(a),(b) ) )\
    ||( EPG_IS_IN_RANGE( (y),(a),(b) ) )\
    ||( EPG_IS_IN_RANGE( (a),(x),(y) ) )\
    )

U16 msAPI_AtscEpgDb_Get_EventList_Idx(U8 u8RfNum, U16 u16SrcId, U32 u32StartTime, U32 u32EndTime, U16 au16EventList[], U16 u16EventListMaxNum )
{
    U16 u16EvtIdx;
    MS_EPG_EVENT_New* pstEPG_EVENT_New;
    U16 u16EventCount = 0;
    U32 u32CurEventEndTime;


    if( au16EventList == NULL )
    {
        return 0;
    }
    if( u16EventListMaxNum > ATSC_EPG_EVENT_NUM )
    {
        return 0;
    }

    if( u32StartTime >= u32EndTime )
    {
        return 0;
    }

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            pstEPG_EVENT_New = &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);

            // Check channel
            if( (pstEPG_EVENT_New->u8RfNum == u8RfNum) &&(pstEPG_EVENT_New->u16SrcId == u16SrcId) )
            {
                u32CurEventEndTime = msAPI_AtscEpgDb_Get_EventTimeEnd(pstEPG_EVENT_New);

                // Check time ...
                /*if( ((pstEPG_EVENT_New->start_time >= u32StartTime)&&(pstEPG_EVENT_New->start_time < u32EndTime))
                  ||((u32CurEventEndTime >= u32StartTime)&&(u32CurEventEndTime < u32EndTime))
                  )*/
                if( EPG_CHECK_TIME(u32StartTime, u32EndTime, pstEPG_EVENT_New->start_time, u32CurEventEndTime) )
                {
                    //apstEventList[u16EventCount] = pstEPG_EVENT_New;
                    au16EventList[u16EventCount] = u16EvtIdx;

                    u16EventCount += 1;
                    if( u16EventCount >= u16EventListMaxNum )
                    {
                        break;
                    }
                }
            }
        }
    }

/*
    msAPI_AtscEpgDb_PrintEventList(apstEventList, u16EventCount);

    // If list count > 1, sorting
    if( u16EventCount > 1 )
    {
        msAPI_AtscEpgDb_SortEventList(apstEventList, u16EventCount);

        msAPI_AtscEpgDb_PrintEventList(apstEventList, u16EventCount);
    }
*/
    return u16EventCount;
}

U16 msAPI_AtscEpgDb_Get_EventList_Ref(U8 u8RfNum, U16 u16SrcId, U32 u32StartTime, U32 u32EndTime, MS_EPG_EVENT_New* apstEventList[], U16 u16EventListMaxNum )
{
    if( s_bEpgDb_u8DebugMode )
    {
        printf("msAPI_AtscEpgDb_Get_EventList_Ref(u8RfNum=%u,u16SrcId=%u, u32StartTime=%u, u32EndTime=%u)\n", u8RfNum, u16SrcId, u32StartTime, u32EndTime);
    }

    U16 u16EvtIdx;
    MS_EPG_EVENT_New* pstEPG_EVENT_New;
    U16 u16EventCount = 0;
    U32 u32CurEventEndTime;


    if( apstEventList == NULL )
    {
        return 0;
    }
    if( u16EventListMaxNum > ATSC_EPG_EVENT_NUM )
    {
        return 0;
    }

    if( u32StartTime >= u32EndTime )
    {
        return 0;
    }


    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            pstEPG_EVENT_New = &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);

            // Check channel
            if( (pstEPG_EVENT_New->u8RfNum == u8RfNum) &&(pstEPG_EVENT_New->u16SrcId == u16SrcId) )
            {
                u32CurEventEndTime = msAPI_AtscEpgDb_Get_EventTimeEnd(pstEPG_EVENT_New);

                //printf("%u pstEPG_EVENT_New->start_time=%u\n", u16EvtIdx, pstEPG_EVENT_New->start_time );
                //printf("  u32StartTime=%u, u32EndTime=%u\n", u32StartTime, u32EndTime);

                // Check time ...
                /*if( ((pstEPG_EVENT_New->start_time >= u32StartTime)&&(pstEPG_EVENT_New->start_time < u32EndTime))
                  ||((u32CurEventEndTime >= u32StartTime)&&(u32CurEventEndTime < u32EndTime))
                  ||((pstEPG_EVENT_New->start_time <= u32StartTime)&&(u32EndTime <= u32CurEventEndTime) )
                  ) */
                if( EPG_CHECK_TIME(u32StartTime, u32EndTime, pstEPG_EVENT_New->start_time, u32CurEventEndTime) )
                {
                    apstEventList[u16EventCount] = pstEPG_EVENT_New;

                    u16EventCount += 1;
                    if( u16EventCount >= u16EventListMaxNum )
                    {
                        break;
                    }
                }
            }
        }
    }

    if( s_bEpgDb_u8DebugMode )
    {
        msAPI_AtscEpgDb_PrintEventList(apstEventList, u16EventCount);
    }

    // If list count > 1, sorting
    if( u16EventCount > 1 )
    {
        msAPI_AtscEpgDb_SortEventList(apstEventList, u16EventCount);

        if( s_bEpgDb_u8DebugMode )
        {
            msAPI_AtscEpgDb_PrintEventList(apstEventList, u16EventCount);
        }
    }

    return u16EventCount;
}

void msAPI_AtscEpgDb_PrintTime(U32 u32DtvTime)
{
    //ST_TIME stST_TIME;
    //MApp_ConvertSeconds2StTime( u32DtvTime, &stST_TIME );
    MApp_Time_PrintTimeAndST_Time(u32DtvTime);
}

void msAPI_AtscEpgDb_PrintEventTitle(const U8* pu8Title, U16 u16MaxLen, BOOLEAN bIsUTF16)
{
    U16 u16Data;
    U8 u8Idx;
    U8 u8CharSize = 1;

    if( bIsUTF16 )
    {
        u8CharSize = 2;
    }

    printf("[");
    for( u8Idx = 0; u8Idx < u16MaxLen; u8Idx += u8CharSize )
    {
        if( bIsUTF16 )
            u16Data = (pu8Title[u8Idx+1]<<8) + pu8Title[u8Idx];
        else
            u16Data = pu8Title[u8Idx];

        if( u16Data == 0 )
            break;

        if( u16Data <= 0x7F )
        {
            putchar(u16Data);
        }
        else
        {
            printf("(%X)", u16Data);
        }
    }
    printf("]");
}

void msAPI_AtscEpgDb_PrintEvent(const MS_EPG_EVENT_New* pstEPG_EVENT_New)
{
    printf(" u8RfNum=%u,", pstEPG_EVENT_New->u8RfNum);
    printf(" u16SrcId=%u,", pstEPG_EVENT_New->u16SrcId);

    printf(" id=0x%X,", pstEPG_EVENT_New->event_id);

    printf(" Eit=%u,", pstEPG_EVENT_New->u8EitTblNumber);

    //U32 u32CurEventEndTime = pstEPG_EVENT_New->start_time + EPG_EVENT_LENGTH(pstEPG_EVENT_New->length[0],pstEPG_EVENT_New->length[1],pstEPG_EVENT_New->length[2]);
    //U32 u32CurEventEndTime = msAPI_AtscEpgDb_Get_EventTimeEnd(pstEPG_EVENT_New);

    //printf(" time=%u ", pstEPG_EVENT_New->start_time);
    printf(" time=" );
    msAPI_AtscEpgDb_PrintTime(pstEPG_EVENT_New->start_time);

    //printf(" len=" );
    //msAPI_AtscEpgDb_PrintTime(msAPI_AtscEpgDb_Get_EventTimeLen(pstEPG_EVENT_New));
    printf(" len=%u", msAPI_AtscEpgDb_Get_EventTimeLen(pstEPG_EVENT_New) );

    printf(" End=" );
    msAPI_AtscEpgDb_PrintTime(msAPI_AtscEpgDb_Get_EventTimeEnd(pstEPG_EVENT_New));

    printf(" Title[%u]=", pstEPG_EVENT_New->u8TitleLen);
    msAPI_AtscEpgDb_PrintEventTitle(pstEPG_EVENT_New->au8Title, ATSC_EPG_TITLE_DATA_SIZE, pstEPG_EVENT_New->fIsEitUTF16);

    printf(" ");
    //printf("\n");
}

void msAPI_AtscEpgDb_PrintEventList(MS_EPG_EVENT_New* apstEventList[], U16 u16EventListNum)
{
    printf("msAPI_AtscEpgDb_PrintEvent(u16EventListNum=%u)\n", u16EventListNum);

    U16 u16EvtIdx;
    MS_EPG_EVENT_New* pstEPG_EVENT_New;
    U16 u16MaxPrintNum = 100;
    U16 u16PrintCount = 0;

    printf("\nEvent list: u16MaxPrintNum=%u ----------------------------------\n", u16MaxPrintNum);

    for( u16EvtIdx = 0; u16EvtIdx < u16EventListNum; u16EvtIdx += 1 )
    {
        pstEPG_EVENT_New = apstEventList[u16EvtIdx];

        printf("idx=%u,", u16EvtIdx);

        msAPI_AtscEpgDb_PrintEvent(pstEPG_EVENT_New);

        printf("\n");

        u16PrintCount += 1;
        if( u16PrintCount >= u16MaxPrintNum )
        {
            break;
        }
    }

    printf("----------------------------------------------------------\n");
}

void msAPI_AtscEpgDb_PrintEvents(U16 u16MaxPrintNum)
{
    //printf("msAPI_AtscEpgDb_PrintEvents()\n");
    U16 u16EvtIdx;
    const MS_EPG_EVENT_New* pstEPG_EVENT_New;
    U16 u16PrintCount = 0;

    printf("ATSC_EPG_EVENT_NUM=%u\n", ATSC_EPG_EVENT_NUM);

    printf("\nAll Event: u16MaxPrintNum=%u ----------------------------------\n", u16MaxPrintNum);

    for( u16EvtIdx = 0; u16EvtIdx < ATSC_EPG_EVENT_NUM; u16EvtIdx += 1 )
    {
        if( msAPI_AtscEpgDb_IsEventValid(u16EvtIdx) )
        {
            pstEPG_EVENT_New = &(s_EpgDb_pstDbData->astEvent[u16EvtIdx]);

            printf("idx=%u,", u16EvtIdx);

            msAPI_AtscEpgDb_PrintEvent(pstEPG_EVENT_New);

            printf("\n");

            u16PrintCount += 1;
            if( u16PrintCount >= u16MaxPrintNum )
            {
                break;
            }
        }
    }

    printf("----------------------------------------------------------\n");

}

void msAPI_AtscEpgDb_PrintAllEtt(void)
{
    //printf("msAPI_AtscEpgDb_PrintAllEtt()\n");

    U16 u16EttIdx;
    const MS_EPG_EVENT_ETT_New* pstEVENT_ETT_New;
    U16 u16MaxPrintNum = 100;
    U16 u16PrintCount = 0;

    printf("\nAll ETT: u16MaxPrintNum=%u -------------------------------------------------\n", u16MaxPrintNum);

    for( u16EttIdx = 0; u16EttIdx < ATSC_EPG_ETT_NUM; u16EttIdx += 1 )
    {
        pstEVENT_ETT_New = &(s_EpgDb_pstDbData->astEttData[u16EttIdx]);

        if( pstEVENT_ETT_New->u16EttDataLen > 0 )
        {
            printf("idx=%u,", u16EttIdx);

            printf(" u16EttDataLen=%u,", pstEVENT_ETT_New->u16EttDataLen);

            printf(" ETT=");
            msAPI_AtscEpgDb_PrintEventTitle(pstEVENT_ETT_New->au8EttData, ATSC_EPG_ETT_DATA_SIZE, pstEVENT_ETT_New->bIsEttUTF16);

            printf("\n");

            u16PrintCount += 1;
            if( u16PrintCount >= u16MaxPrintNum )
            {
                break;
            }
        }
    }

    printf("----------------------------------------------------------\n");

}

void msAPI_AtscEpgDb_PrintAllDb(void)
{
    printf("msAPI_AtscEpgDb_PrintAllDb()\n");

    printf("bDbChanged = %u\n", s_EpgDb_stInfo.bDbChanged);

    msAPI_AtscEpgDb_PrintEvents(100);
    msAPI_AtscEpgDb_PrintAllEtt();
}

// When  DB full, need to call this function to delete some
void msAPI_AtscEpgDb_DeleteEventsByUser(void)
{
    //msAPI_AtscEpgDb_PrintEvents(1000);
    MApp_ATSC_EpgDb_DeleteEvents_CB();
}

void msAPI_AtscEpgDb_UI_Test(void)
{

}

#endif // ENABLE_ATSC

