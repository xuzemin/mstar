#ifndef _MSAPI_DTV_DB_H_
#define _MSAPI_DTV_DB_H_

#include "Board.h"

#if(ENABLE_DTV /*&& ENABLE_API_DTV_SYSTEM_2015*/)

#include "msAPI_DTV_Common.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_MW_GlobalSt.h"



//========================================================================

//========================================================================
U16 msAPI_DtvDB_Get_DataBaseMagicId(TypDtvDbSel eDtvDbSel);

U8* msAPI_DtvDB_Get_ProgTableMap(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvDB_Get_ProgTableMapArraySize(TypDtvDbSel eDtvDbSel);
U32 msAPI_DtvDB_Get_ProgTableMapRamDiskAddr(TypDtvDbSel eDtvDbSel);

U16 msAPI_DtvDB_Get_ProgTableArraySize(TypDtvDbSel eDtvDbSel);
U32 msAPI_DtvDB_Get_ProgTableRamDiskAddr(TypDtvDbSel eDtvDbSel);
BOOLEAN msAPI_DtvDB_Is_ProgTableIndexValid(TypDtvDbSel eDtvDbSel, U16 u16ProgIndex );

U8* msAPI_DtvDB_Get_ProgIdTableMap(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvDB_Get_ProgIdTableMapArraySize(TypDtvDbSel eDtvDbSel);
U32 msAPI_DtvDB_Get_ProgIdTableMapRamDiskAddr(TypDtvDbSel eDtvDbSel);

DTVPROGRAMID_M* msAPI_DtvDB_Get_ProgIdTable(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvDB_Get_ProgIdTableArraySize(TypDtvDbSel eDtvDbSel);
U32 msAPI_DtvDB_Get_ProgIdTableRamDiskAddr(TypDtvDbSel eDtvDbSel);
BOOLEAN msAPI_DtvDB_Is_IDTableIndexValid(TypDtvDbSel eDtvDbSel, U16 u16IDIndex );


DTVNETWORK* msAPI_DtvDB_Get_NetWorkTable(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvDB_Get_NetWorkTableArraySize(TypDtvDbSel eDtvDbSel);
U32 msAPI_DtvDB_Get_NetWorkTableRamDiskAddr(TypDtvDbSel eDtvDbSel);

DTVPROGRAMINDEX* msAPI_DtvDB_Get_ProgramIndexTable(TypDtvDbSel eDtvDbSel);
U16 msAPI_DtvDB_Get_ProgramIndexTableArraySize(TypDtvDbSel eDtvDbSel);

//-----------------------------------------------------------------------------------------
U32 msAPI_DtvDB_Get_RamDiskAddr_ProgTable_ByIndex(TypDtvDbSel eDtvDbSel, U16 u16PRIndex);
U32 msAPI_DtvDB_Get_RamDiskAddr_LogicalChannelNumberArranged(TypDtvDbSel eDtvDbSel);

U32 msAPI_DtvDB_Get_RamDiskAddr_IdTable_ByIndex(TypDtvDbSel eDtvDbSel, U16 u16IdIndex);
U32 msAPI_DtvDB_Get_RamDiskAddr_NetWork_ByIndex(TypDtvDbSel eDtvDbSel, U16 u16NetWorkIndex);

//========================================================================

BOOLEAN msAPI_DtvDB_Set_Identify(TypDtvDbSel eDtvDbSel, U16 u16Identify);
U16 msAPI_DtvDB_Get_Identify(TypDtvDbSel eDtvDbSel);

#if (NTV_FUNCTION_ENABLE)
BOOLEAN msAPI_DtvDB_Set_FavoriteRegion(TypDtvDbSel eDtvDbSel, U8 u8FavoriteRegion);
U8 msAPI_DtvDB_Get_FavoriteRegion(TypDtvDbSel eDtvDbSel);
#endif

//-----------------------------------------------------------------------------------------

BOOLEAN msAPI_DtvDB_Set_CurServiceType(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE eServiceType);
MEMBER_SERVICETYPE msAPI_DtvDB_Get_CurServiceType(TypDtvDbSel eDtvDbSel);

BOOLEAN msAPI_DtvDB_Set_CurOrderOfTV(TypDtvDbSel eDtvDbSel, U16 u16Order);
U16 msAPI_DtvDB_Get_CurOrderOfTV(TypDtvDbSel eDtvDbSel);
BOOLEAN msAPI_DtvDB_Set_CurOrderOfRadio(TypDtvDbSel eDtvDbSel, U16 u16Order);
U16 msAPI_DtvDB_Get_CurOrderOfRadio(TypDtvDbSel eDtvDbSel);
BOOLEAN msAPI_DtvDB_Set_CurOrderOfData(TypDtvDbSel eDtvDbSel, U16 u16Order);
U16 msAPI_DtvDB_Get_CurOrderOfData(TypDtvDbSel eDtvDbSel);

//-----------------------------------------------------------------------------------------
BOOLEAN msAPI_DtvDB_Save_ProgramTableMap(TypDtvDbSel eDtvDbSel, U8* pu8ProgTableMap, U16 u16ArraySize );
BOOLEAN msAPI_DtvDB_Load_ProgramTableMap(TypDtvDbSel eDtvDbSel, U8* pu8ProgTableMap, U16 u16ArraySize );

BOOLEAN msAPI_DtvDB_Save_IDTableMap(TypDtvDbSel eDtvDbSel, U8* pu8IDTableMap, U16 u16ArraySize );
BOOLEAN msAPI_DtvDB_Load_IDTableMap(TypDtvDbSel eDtvDbSel, U8* pu8IDTableMap, U16 u16ArraySize );
BOOLEAN msAPI_DtvDB_Load_IDTable(TypDtvDbSel eDtvDbSel, DTVPROGRAMID_M* pstIDTable, U16 u16ArraySize );

BOOLEAN msAPI_DtvDB_Load_NetWorkTable(TypDtvDbSel eDtvDbSel, DTVNETWORK* pstNetWorkTable, U16 u16ArraySize );

//---------------------------------------------------------------------------------------------------------------
#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
#define CM_AUD_INFO_INVALID_INDEX   0xFFFF
U16 msAPI_DtvDB_Get_AudInfoTableArraySize(TypDtvDbSel eDtvDbSel);
U32 msAPI_DtvDB_Get_AudInfoTableRamDiskAddr(TypDtvDbSel eCurDbSel);
BOOLEAN msAPI_DtvDB_Get_AudInfoTable(TypDtvDbSel eDtvDbSel, U16 u16Index, AUD_INFO* pstAudInfoTable, U16 u16ArraySize );
BOOLEAN msAPI_DtvDB_Set_AudInfoTable(TypDtvDbSel eDtvDbSel, U16 u16Index, AUD_INFO* pstAudInfoTable, U16 u16ArraySize );
void msAPI_DtvDB_AudInfoTable_ResetAll(TypDtvDbSel eDtvDbSel, AUD_INFO* pstAudInfoTable);
U16 msAPI_DtvDB_AudInfo_AllocSpace(U8 u8SpaceCount);

#endif

//========================================================================

#endif

#endif

