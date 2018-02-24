#ifndef _MSAPI_DTV_DB_DUMP_H_
#define _MSAPI_DTV_DB_DUMP_H_

#include "Board.h"

#if( ENABLE_DTV_DB_DUMP )

#include "msAPI_DTV_Common.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_MW_GlobalSt.h"


//========================================================================

#define CM_DUMP_INFO_ALL        0xFFFFFFFF
#define CM_DUMP_INFO_CH_TBL_MAP BIT0
#define CM_DUMP_INFO_CH_TBL     BIT1
#define CM_DUMP_INFO_ID_TBL_MAP BIT2
#define CM_DUMP_INFO_ID_TBL     BIT3

void msAPI_DTV_DB_DumpDB(TypDtvDbSel eDtvDbSel, U32 u32Flag);


//========================================================================

#endif // ENABLE_DTV_DB_DUMP

#endif // _MSAPI_DTV_DB_DUMP_H_

