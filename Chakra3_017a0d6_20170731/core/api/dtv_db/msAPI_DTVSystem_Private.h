#ifndef _API_DTVSYSTEM_PRIVATE_H_
#define _API_DTVSYSTEM_PRIVATE_H_

#include "Board.h"

#if(ENABLE_DTV)



#ifdef API_DTVSYSTEM_C
    #define _API_DTV_SYS_DEC_
#else
    #define _API_DTV_SYS_DEC_   extern
#endif


//======================================================================
typedef BYTE E_LCN_ASSIGNMENT_TYPE;
//---------------------------------------
#define E_LCN_INVALID                   0x00
#define E_LCN_ABSENT                    0x01
#define E_LCN_PRESENT                   0x02
#define E_LCN_DUPLICATE                 0x04
#define E_LCN_SAME_SERVICE              0x08
#define E_LCN_LAST                      0x10//RiksTV spec , ONID 0x2242 LCN 900~999 shall be end of list for hearing and visually impaired people
#define E_LCN_ZERO                      0x20
//#define E_LCN_NOT_NATIVE_ON_ID          0x10

//======================================================================
// ===== DataBase -DVBT/DTMB =====
_API_DTV_SYS_DEC_ DTVPROGRAMINDEX g_astDTVProgramIndexTable_DVBT[MAX_DTVPROGRAM]; // Program Index Table

_API_DTV_SYS_DEC_ BYTE g_acDTVProgramTableMap_DVBT[MAX_DTVCHANNELTABLE_MAP]; // Program Table Map
_API_DTV_SYS_DEC_ BYTE g_acDTVIDtableMap_DVBT[MAX_DTVIDTABLE_MAP]; // ID Table Map

_API_DTV_SYS_DEC_ DTVPROGRAMID_M g_astDTVProgramIDTable_DVBT[MAX_MUX_NUMBER]; // ID Table

_API_DTV_SYS_DEC_ DTVNETWORK g_astDTVNetwork_DVBT[MAX_NETWOEK_NUMBER]; // NetWork Table

_API_DTV_SYS_DEC_ U16 g_au16ProgramCount_DVBT[E_CM_SERVICE_POS_NUMS][MAX_COUNT_PROGRAM_OPTION];

// ===== DataBase - DVBC =====
#if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
_API_DTV_SYS_DEC_ DTVPROGRAMINDEX m_astDTVProgramIndexTable_DVBC[MAX_DTVPROGRAM_DVBC]; // Program Index Table

_API_DTV_SYS_DEC_ BYTE m_acDTVProgramTableMap_DVBC[MAX_DTVCHANNELTABLE_MAP_DVBC]; // Program Table Map
_API_DTV_SYS_DEC_ BYTE m_acDTVIDtableMap_DVBC[MAX_DTV_C_IDTABLE_MAP]; // ID Table Map

_API_DTV_SYS_DEC_ DTVPROGRAMID_M g_astDTVProgramIDTable_DVBC[MAX_MUX_NUMBER_DVBC]; // ID Table
    //#define _astDTVCProgramIDTable g_astDTVProgramIDTable_DVBC

_API_DTV_SYS_DEC_ DTVNETWORK s_astDTVNetwork_DVBC[MAX_NETWOEK_NUMBER];
_API_DTV_SYS_DEC_ U16 g_au16ProgramCount_DVBC[E_CM_SERVICE_POS_NUMS][MAX_COUNT_PROGRAM_OPTION];
#endif

//-----------------------------------------------------------------------------

#if(ENABLE_API_DTV_SYSTEM_2015)
_API_DTV_SYS_DEC_ WORD m_awCurrentOrderOfTV[E_DTV_DB_NUM];
_API_DTV_SYS_DEC_ WORD m_awPastOrderOfTV[E_DTV_DB_NUM];
_API_DTV_SYS_DEC_ WORD m_awCurrentOrderOfRadio[E_DTV_DB_NUM];
_API_DTV_SYS_DEC_ WORD m_awPastOrderOfRadio[E_DTV_DB_NUM];
_API_DTV_SYS_DEC_ WORD m_awCurrentOrderOfData[E_DTV_DB_NUM];
_API_DTV_SYS_DEC_ WORD m_awPastOrderOfData[E_DTV_DB_NUM];
_API_DTV_SYS_DEC_ MEMBER_SERVICETYPE m_aeCurrentServiceType[E_DTV_DB_NUM];

#define m_wCurrentOrderOfTV     m_awCurrentOrderOfTV[eCurDbSel]
#define m_wPastOrderOfTV        m_awPastOrderOfTV[eCurDbSel]
#define m_wCurrentOrderOfRadio  m_awCurrentOrderOfRadio[eCurDbSel]
#define m_wPastOrderOfRadio     m_awPastOrderOfRadio[eCurDbSel]
#define m_wCurrentOrderOfData   m_awCurrentOrderOfData[eCurDbSel]
#define m_wPastOrderOfData      m_awPastOrderOfData[eCurDbSel]
#define m_eCurrentServiceType   m_aeCurrentServiceType[eCurDbSel]

#else
_API_DTV_SYS_DEC_ WORD m_wCurrentOrderOfTV;
_API_DTV_SYS_DEC_ WORD m_wPastOrderOfTV;
_API_DTV_SYS_DEC_ WORD m_wCurrentOrderOfRadio;
_API_DTV_SYS_DEC_ WORD m_wPastOrderOfRadio;
_API_DTV_SYS_DEC_ WORD m_wCurrentOrderOfData;
_API_DTV_SYS_DEC_ WORD m_wPastOrderOfData;
_API_DTV_SYS_DEC_ MEMBER_SERVICETYPE        m_eCurrentServiceType;
#endif


_API_DTV_SYS_DEC_ BOOLEAN _bOnlyUpdateCurTS;
_API_DTV_SYS_DEC_ WORD _wCurTS_ID;

//======================================================================

#if( (ENABLE_DVBC&&DVB_T_C_DIFF_DB) \
   ||(ENABLE_S2) )
    #define CUR_DB_SEL()    msAPI_DTV_Comm_Get_DBSel()
#else
    #define CUR_DB_SEL()    E_DTV_DB_SEL_DVBT
#endif

//----------------------------------------------------------------------------
BOOLEAN GetNVRAM(DWORD wAddress, BYTE * pcBuffer, WORD cSize);
BOOLEAN SetNVRAM(DWORD wAddress, BYTE * pcBuffer, WORD cSize);
//----------------------------------------------------------------------------

BOOLEAN IsServiceTypeValid(MEMBER_SERVICETYPE bServiceType);
BOOLEAN IsPositionValid(MEMBER_SERVICETYPE bServiceType, WORD wPosition);

BOOLEAN IsService_IDValid(WORD Service_ID);

BOOLEAN IsLogicalChannelNumberValid(WORD wLCN);

BOOLEAN IsVersionValid(BYTE cVersion);

BOOLEAN IsPMT_PIDValid(WORD wPMT_PID);
BOOLEAN IsPCR_PIDValid(WORD wPCR_PID);

BOOLEAN IsVideoPIDValid(WORD wVideo_PID);

BOOLEAN IsAudioStreamInfoValid(AUD_INFO * pastAudioStreamInfo);

E_CM_SERVICE_POS ConvertServiceTypeToPosition(MEMBER_SERVICETYPE eServiceType);

//======================================================================
U16 msAPI_DtvSys_Get_ProgTabIndex_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition);
U16 msAPI_DtvSys_Get_IDTabIndex_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition);

BOOLEAN msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
BOOLEAN msAPI_DtvSys_Set_ProgramTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
BOOLEAN msAPI_DtvSys_Get_IDTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
BOOLEAN msAPI_DtvSys_Set_IDTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);

U16 msAPI_DtvSys_Get_PCN_ByIDIndex(TypDtvDbSel eDtvDbSel, U16 u16IDIndex );
U16 msAPI_DtvSys_Get_PCN_ByOrder(TypDtvDbSel eDtvDbSel, U16 u16Order );
MEMBER_SERVICETYPE msAPI_DtvSys_Get_ServiceType_ByOrder(TypDtvDbSel eDtvDbSel, U16 u16Order );

U16 msAPI_DtvSys_Find_IDTab_By_TSId_ONId(TypDtvDbSel eDtvDbSel, WORD wTS_ID, WORD wON_ID);
//======================================================================
//static BOOLEAN SetProgramTable(DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
#define SetProgramTable( wPRIndex, pcBuffer, eMember)   SetProgramTable_DBSel( CUR_DB_SEL(), (wPRIndex), (pcBuffer), (eMember))
BOOLEAN SetProgramTable_DBSel(TypDtvDbSel eDbSel, DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);

//static BOOLEAN GetProgramTable(DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
#define GetProgramTable(wPRIndex, pcBuffer, eMember) GetProgramTable_DBSel( CUR_DB_SEL(), (wPRIndex), (pcBuffer), (eMember))
BOOLEAN GetProgramTable_DBSel(TypDtvDbSel eDbSel, DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);

//static BOOLEAN ActiveProgramEntity(WORD wPRIndex, BOOLEAN bActive);
BOOLEAN ActiveProgramEntity_DBSel(TypDtvDbSel eDtvDbSel, WORD wPRIndex, BOOLEAN bActive);

//static BOOLEAN IsProgramEntityActive(WORD wPRIndex);
#define IsProgramEntityActive(wPRIndex) IsProgramEntityActive_DBSel( CUR_DB_SEL(), (wPRIndex) )
BOOLEAN IsProgramEntityActive_DBSel(TypDtvDbSel eDbSel, WORD wPRIndex );
//---------------------------------------------------------------------------------
BOOLEAN IsIDEntityActive_DBSel(TypDtvDbSel eDtvDbSel, WORD wIDIndex);
//---------------------------------------------------------------------------------
//static BOOLEAN IsLogicalChannelNumberArranged(void);
#define IsLogicalChannelNumberArranged()    IsLogicalChannelNumberArranged_DBSel(CUR_DB_SEL())
BOOLEAN IsLogicalChannelNumberArranged_DBSel(TypDtvDbSel eDtvDbSel);

//static void LogicalChannelNumberIsArranged(BOOLEAN bIsArranged);
#define LogicalChannelNumberIsArranged(bIsArranged) LogicalChannelNumberIsArranged_DBSel(CUR_DB_SEL(),(bIsArranged))
void LogicalChannelNumberIsArranged_DBSel(TypDtvDbSel eDtvDbSel, BOOLEAN bIsArranged);
//---------------------------------------------------------------------------------
//static BOOLEAN SaveCurrentOrderOfTV(WORD wOrder);
#define SaveCurrentOrderOfTV(wOrder)    SaveCurrentOrderOfTV_DBSel(CUR_DB_SEL(), (wOrder))
BOOLEAN SaveCurrentOrderOfTV_DBSel(TypDtvDbSel eDtvDbSel, WORD wOrder);

//static BOOLEAN SaveCurrentOrderOfRadio(WORD wOrder);
#define SaveCurrentOrderOfRadio(wOrder) SaveCurrentOrderOfRadio_DBSel(CUR_DB_SEL(), (wOrder))
BOOLEAN SaveCurrentOrderOfRadio_DBSel(TypDtvDbSel eDtvDbSel, WORD wOrder);

//static BOOLEAN SaveCurrentOrderOfData(WORD wOrder);
#define SaveCurrentOrderOfData(wOrder)  SaveCurrentOrderOfData_DBSel(CUR_DB_SEL(), (wOrder))
BOOLEAN SaveCurrentOrderOfData_DBSel(TypDtvDbSel eDtvDbSel, WORD wOrder);

//---------------------------------------------------------------------------------

BOOLEAN IsLinkOfOrderValid(TypDtvDbSel eDBSel);


//void UpdateProgramCount(MEMBER_SERVICETYPE bServiceType);
#define UpdateProgramCount(bServiceType)    UpdateProgramCount_DBSel(CUR_DB_SEL(), (bServiceType))
void UpdateProgramCount_DBSel(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType);


BOOLEAN FillProgramIndexWithDefault(DTVPROGRAMINDEX * pstDTVProgramIndex);

BOOLEAN FillProgramIDWithDefault(DTVPROGRAMID_M * pstDTVProgramID);

BOOLEAN FillNetworkWithDefault(DTVNETWORK * pstDTVNetwork);


//static WORD ConvertPositionToOrder(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
#define ConvertPositionToOrder(bServiceType, wPosition) ConvertPositionToOrder_DBSel(CUR_DB_SEL(),(bServiceType), (wPosition))
WORD ConvertPositionToOrder_DBSel(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition);

//static WORD ConvertOrderToPosition(WORD wOrder);
#define ConvertOrderToPosition(wOrder)  ConvertOrderToPosition_DBSel(CUR_DB_SEL(), (wOrder) )
WORD ConvertOrderToPosition_DBSel(TypDtvDbSel eDtvDbSel, WORD wOrder);

BOOLEAN UpdateOrderOfProgramTable(MEMBER_SERVICETYPE bServiceType);


//static WORD CountProgram(MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption);
#define CountProgram(bServiceType, eCountOption)    CountProgram_DBSel( CUR_DB_SEL(), (bServiceType), (eCountOption))
WORD CountProgram_DBSel(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption);

//---------------------------------------------------------------------------------
BOOLEAN RemoveProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
BOOLEAN SortProgram(MEMBER_SERVICETYPE bServiceType);

//---------------------------------------------------------------------------------

#if(ENABLE_API_DTV_SYSTEM_2015)
BOOLEAN msAPI_CM_ResetAllProgram_ByDBSel(TypDtvDbSel eDtvDbSel);
#endif

//======================================================================


#endif // ENABLE_DTV
#endif // _API_DTVSYSTEM_PRIVATE_H_

