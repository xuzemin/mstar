#ifndef _MSAPI_DTVSYSTEM_DVBS_H_
#define _MSAPI_DTVSYSTEM_DVBS_H_


#include "Board.h"

#if( ENABLE_S2 )

//#include <stddef.h> /* offsetof */

#include "MApp_SaveData.h"

#include "apiDTVSatTable.h"


#ifdef _MSAPI_DTVSYSTEM_DVBS_C_
    #define _DTV_SYS_DVBS_DEC_
#else
    #define _DTV_SYS_DVBS_DEC_ extern
#endif

#define MAX_TPSOFSAT            10


#if 1//ENABLE_S2_WORD
#define INVALID_S2_PHYSICAL_CHANNEL_NUMBER		0xFFFF
#else
#define INVALID_S2_PHYSICAL_CHANNEL_NUMBER		0xFF
#endif
#if (ENABLE_S2_PROGRAM_PREPARE)
#define MAX_DTV_S2_PROGRAM						5000
#else
#define MAX_DTV_S2_PROGRAM						2000
#endif
#define MAX_DTV_S2_SERVICE_NAME					25
#define MAX_NETWOEK_S2_NUMBER					20
#define E_DATA_ID_SATLITE						0x29
//#define E_DATA_PROGRAM_SATLITE					0x2a
#if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
#define E_DATA_ID_FAV							0x2b
#endif
#define MAX_DTV_S2_MUX_NUMBER					3000

#define S2_FIRST_ORDER_OF_TV					0
#define S2_LAST_ORDER_OF_TV						(MAX_DTV_S2_PROGRAM - 1)
#define S2_FIRST_ORDER_OF_RADIO					(MAX_DTV_S2_PROGRAM - 1)
#define S2_LAST_ORDER_OF_RADIO					0
#define S2_FIRST_ORDER_OF_DATA					(MAX_DTV_S2_PROGRAM - 1)
#define S2_LAST_ORDER_OF_DATA					0

#define S2_DEFAULT_CURRENT_ORDER_TV				0x0000
#define S2_DEFAULT_CURRENT_ORDER_RADIO			(MAX_DTV_S2_PROGRAM - 1)
#define S2_DEFAULT_CURRENT_ORDER_DATA			(MAX_DTV_S2_PROGRAM - 1)


#if 1//(ENABLE_S2_WORD)
#define INVALID_S2_PHYSICAL_CHANNEL_NUMBER     0xFFFF
#else
#define INVALID_S2_PHYSICAL_CHANNEL_NUMBER     0xFF
#endif

#define MAX_S2_CHANNELTABLE_MAP			((MAX_DTV_S2_PROGRAM+7)/8)
#define MAX_S2_IDTABLE_MAP				((MAX_DTV_S2_MUX_NUMBER+7)/8)


//========================================================
// DataBase
#define DTVDATA_ID_DVBS                  0xA55A

#define START_ADDRESS_OF_S2_DTVDATA_STRUCTURE      (RM_DTV_S2_CHSET_START_ADDR)

#define S2_BASEADDRESS_PR_DATA                      START_ADDRESS_OF_S2_DTVDATA_STRUCTURE
#define S2_BASEADDRESS_PR_SERIALNO                  ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, bSerialNum)))
#define S2_BASEADDRESS_PR_IDENT                     ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, wID)))
//#define S2_BASEADDRESS_COUNTRY 						( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, eCountry)))

#define S2_BASEADDRESS_PR_IS_LCN_ARRANGED           ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, bIsLogicalChannelNumberArranged)))

#if (NTV_FUNCTION_ENABLE)
#define BASEADDRESS_PR_FAVORITE_REGION_DVBS         ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, bFavorite_Region)))
#endif

#if 1 // Save to Gen Setting
//#define S2_BASEADDRESS_PR_CURRENTORDER_TV           ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, s2_wCurOrderOfTV)))
//#define S2_BASEADDRESS_PR_CURRENTORDER_RADIO        ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, s2_wCurOrderOfRadio)))
//#define S2_BASEADDRESS_PR_CURRENTORDER_DATA         ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, s2_wCurOrderOfData)))
//#define S2_BASEADDRESS_PR_CURRENT_SERVICETYPE       ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, s2_eDTVCurrentServiceType)))
#endif

#define S2_BASEADDRESS_PR_DTVPRTABLEMAP             ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, bDTV_S2_ChannelTableMap)))
#define S2_BASEADDRESS_PR_DTVPRTABLE                ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, astDTV_S2_ChannelTable)))
#define S2_BASEADDRESS_PR_DTVIDTABLEMAP             ( RM_START_ADDRESS_OF_TP_DATA_STRUCTURE + (offsetof(TP_DATA_STRUCTURE, bDTV_S2_IDtableMap)))
#define S2_BASEADDRESS_PR_DTVIDTABLE                ( RM_START_ADDRESS_OF_TP_DATA_STRUCTURE + (offsetof(TP_DATA_STRUCTURE, astDtv_S2_IDTable)))
#define S2_BASEADDRESS_PR_DTVNETWORK                ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, astDtv_S2_Network)))

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
  #define S2_BASEADDRESS_PR_AUD_INFO                ( S2_BASEADDRESS_PR_DATA + (offsetof(DTV_S2_CHANNEL_DATA_STRUCTURE, astAudInfoTab)))
#endif

//=============================================================

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    #define CM_AUDINFO_MAX_NUM_DVBS     (MAX_DTV_S2_PROGRAM*5)
#endif


typedef struct
{
    BYTE                bDTV_S2_IDtableMap[MAX_S2_IDTABLE_MAP];
    DTVPROGRAMID_M      astDtv_S2_IDTable[MAX_DTV_S2_MUX_NUMBER];
} TP_DATA_STRUCTURE;

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

#if 1 // Save to Gen Setting
    //WORD				s2_wCurOrderOfTV;
    //WORD				s2_wCurOrderOfRadio;
    //WORD				s2_wCurOrderOfData;
    //MEMBER_SERVICETYPE	s2_eDTVCurrentServiceType;
#endif

    // Program Table Map
    BYTE                bDTV_S2_ChannelTableMap[MAX_S2_CHANNELTABLE_MAP];
    // Program Table
    DTV_CHANNEL_INFO    astDTV_S2_ChannelTable[MAX_DTV_S2_PROGRAM];

    // ID Table Map
    //BYTE                bDTVIDtableMap[MAX_DTVIDTABLE_MAP];
    // ID Table
    //DTVPROGRAMID_M      astDtvIDTable[MAX_MUX_NUMBER];

    // NetWork
    DTVNETWORK          astDtv_S2_Network[MAX_NETWOEK_S2_NUMBER];

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    AUD_INFO            astAudInfoTab[CM_AUDINFO_MAX_NUM_DVBS];
#endif

} DTV_S2_CHANNEL_DATA_STRUCTURE;


#define SORT_SERVICENAME_NUM	(MAX_SERVICE_NAME+1)

typedef struct
{
	U8 strServiceName[SORT_SERVICENAME_NUM];
}SORT_SERVICENAME_STRUCTURE;

typedef struct _msStack
{
	MS_U16 m_u16PivotArray[MAX_DTV_S2_PROGRAM];
	MS_U16 m_u16Counter;
}msStack;

//===============================================================

_DTV_SYS_DVBS_DEC_ DTVPROGRAMINDEX m_astS2ProgramIndexTable[MAX_DTV_S2_PROGRAM];
_DTV_SYS_DVBS_DEC_ BYTE m_acS2ProgramTableMap[MAX_S2_CHANNELTABLE_MAP];
_DTV_SYS_DVBS_DEC_ BYTE m_acs2IDtableMap[MAX_S2_IDTABLE_MAP];
_DTV_SYS_DVBS_DEC_ DTVPROGRAMID_M _astS2ProgramIDTable[MAX_DTV_S2_MUX_NUMBER];
_DTV_SYS_DVBS_DEC_ WORD m_awS2ProgramCount[3][MAX_COUNT_PROGRAM_OPTION];
_DTV_SYS_DVBS_DEC_ DTVNETWORK _astS2Network[MAX_NETWOEK_S2_NUMBER];

//===============================================================

BOOLEAN S2LoadIDTabla(void);

#if( !ENABLE_API_DTV_SYSTEM_2015 )
void ResetS2IDtable(void);
#endif

BOOLEAN s2_IsLinkOfOrderValid(void);

BOOLEAN s2_FillDTVProgramIndexTableWithOrder(void);
BOOLEAN S2_FillDTVProgramIndexTableWithoutOrder(void);

BOOLEAN CreatS2ProgramIndexTableAndProgramIDTable(void);

#if(ENABLE_S2_PROGRAM_PREPARE)
BYTE bGetSpeNameInList(BYTE * ChName, WORD ServiceId );
#endif

BOOLEAN S2_ActiveProgramEntity(WORD wPRIndex, BOOLEAN bActive);

BOOLEAN IsS2_Current_ProgramEntityActive(void);

WORD GetEmptyIndexOfS2ProgramTable(void);

void UpdateS2IDInfo(void);

extern BOOLEAN _GetSatInforByID(U8 u8SATId, MS_SAT_PARAM *pSATParam);

//===============================================================

BOOLEAN msAPI_CM_AddS2Program(DTV_CHANNEL_INFO *pDTVProgramData, BOOLEAN *bDBFull, BOOLEAN bSkipCheck);
BOOLEAN msAPI_CM_ResetS2Program(void);

WORD msAPI_CM_GetPhysicalidx(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
BYTE msAPI_CM_GetPhysicalsat(MEMBER_SERVICETYPE bServiceType, WORD wPosition);
WORD msAPI_CM_GetPhysicalfreq(MEMBER_SERVICETYPE bServiceType, WORD wPosition);

BOOLEAN msAPI_CM_EditS2ProgramIDTableOffset(DTVPROGRAMID_M *pstDtvIDTable, MS_S16 s16RFOffset);

void msAPI_CM_QuickSortService(MEMBER_SERVICETYPE bServiceType);

//===============================================================


#endif // ENABLE_S2
#endif // _MSAPI_DTVSYSTEM_DVBS_H_

