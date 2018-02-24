
#include "Board.h"

#if( ENABLE_ATSC )

#include "Utl.h"
#include "debug.h"


#include "msAPI_DTVSystem_ATSC.h"
#include "msAPI_Tuner_ATSC.h"

#include "msAPI_AtscEpgDb.h"

//==================================================

StuDtvAtscInfo g_stDtvAtscInfo;

// todo: rename
//MS_U8 fEnableSignalCheck;


void msAPI_DTVSystem_ATSC_Init(void)
{
    //PRINT_CURRENT_LINE();
    memset( &(g_stDtvAtscInfo), 0, sizeof(StuDtvAtscInfo) );

    msAPI_Tuner_ATSC_Init_FreqVar();

#if(ENABLE_ATSC_EPG_DB_2016)
    msAPI_AtscEpgDb_Init();
#endif

}

BOOLEAN msAPI_DtvATSC_IsValidRfNumber(U8 u8RfNum)
{
    U8 u8RfNumberMax;

    if( ANT_TYPE == ANT_AIR )
    {
        u8RfNumberMax = MAX_AIR_PHYSICAL_CH_NUM;
    }
    else //ANT_CATV
    {
        u8RfNumberMax = MAX_CATV_PHYSICAL_CH_NUM;
    }

    if( (u8RfNum > 0) && (u8RfNum < u8RfNumberMax) )
    {
        return TRUE;
    }

    return FALSE;
}

#endif

