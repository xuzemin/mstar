////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (MStar Confidential Information!�L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_DTVSystem.h
/// This file includes MStar DTV system application interface
/// @brief API for DTV control
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////

#define API_DTVSYSTEM_C


#include <stddef.h>
#include <string.h>
#include "sysinfo.h"
#include "debug.h"
#include "MsOS.h"
#include "Utl.h"

#include "msAPI_DTV_Common.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_DTVSystem_Private.h"

#if (ENABLE_DTV)
//#if (ENABLE_API_DTV_SYSTEM)


#include "msAPI_DTV_DB_RamDisk.h"
#include "msAPI_DTV_DB.h"

#include "msAPI_Ram.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h" // for EEPROM_SAVE_NONE
#include "msAPI_Timer.h"

#include "msAPI_ChProc.h"


#include "MApp_ChannelChange.h"

#include "MApp_DataBase.h"
#include "MApp_DataBase_CH.h"

#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"


#if (ENABLE_DVBC)
#include "MApp_CADTV_Proc.h"
#endif
#if ENABLE_S2
#include "MApp_GlobalSettingSt_tv_S2.h"
#include "MApp_RestoreToDefault.h"
#include "apiDTVFreqTable.h"
#endif


#include "MApp_TopStateMachine.h"
#include "MApp_InputSource.h" //
#include "MApp_DMP_Main.h" //??
#ifdef ENABLE_DELETE_PROGRAM_CONTROL
#include "ZUI_exefunc.h"
#include "MApp_OAD.h"
#endif

//===================================================================

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
#if ENABLE_DVB_T2
extern MS_U8 u8PlpIDList[32];
#endif

#if(ENABLE_UPDATE_MULTIPLEX_NIT_UAE)
extern BOOLEAN g_NITVersionChange;
#endif

//---------------------------------------------------------------------------

#define DEBUG_DTV_SYS(x)        //x
#define DEBUG_DTV_PROG_COUNT(x) //x

#define DEBUG_IDINDEX(x)    x
#define DEBUG_PRINDEX(x)    x

#define DEBUG_CM_ARRANGE_LCN(x)

//---------------------------------------------------------------------------

#if(ENABLE_S2_FAST_SCAN)
static BOOLEAN  _bM7ScanEnable = FALSE;
#endif

#if(ASTRA_HD_ENABLE)
static U8 _u8HDFocusIndex;
static BOOLEAN _u8IsAdd2List = FALSE;
static BOOLEAN _u8Add2ListSelectNO = FALSE;
static WORD wLCNConflictNum = 0;
static BOOLEAN bIsNITQuickScan = FALSE;

#endif

#if (ENABLE_LCN_CONFLICT)
#if(ASTRA_HD_ENABLE)
#define MAX_LCNCONFLICT_NUM     50
WORD wLCNConflictList[MAX_LCNCONFLICT_NUM];
#endif
#endif

//------------------------------------------------------------------------------
// Local defines
//------------------------------------------------------------------------------


#if ENABLE_DTV_STORE_TTX_PAGE_INFO// ENABLE_TTX
#define DEFAULT_LISTPAGE                            m_wDefaultListPageNumber
static ROM WORD m_wDefaultListPageNumber[MAX_LISTPAGE] =
{
    100,
    200,
    300,
    400
};
#endif

//----------------------------------------------------------------
#define UAE_ONID            0x2310
#define THAILAND_ONID       0x22FC
#define MALAYSIA_ONID       0x21CA
#define GHANA_ONID          0x2120
#define KUWAIT_ONID         0x219E
#define BAHRAIN_ONID        0x2030
#define OMAN_ONID           0x2200
#define QATAR_ONID          0x227A
#define SAUDI_ONID          0x22AA
#define SINGAPORE_ONID      0x22BE
//#define VIETNAM_ONID        0x1107   //Vietnam-VTC Mobile TV
//#define VNM_JSC_ONID        0x0170   //Vietnam-Audio Visual Global JSC
#define KENYA_ONID          0x2342   //DTT Tanzania
#define MYANMAR_ONID        0x2068

#define DTV_ONID_DENMARK    0x20D0
#define DTV_ONID_FINLAND    0x20F6
#define DTV_ONID_GERMANY    0x2114
#define DTV_ONID_INDONESIA  0x2168
#define DTV_ONID_IRELAND    0x2174
#define DTV_ONID_NORWAY     0x2242
#define DTV_ONID_SWEDEN     0x22F1

//----------------------------------------------------------------

#define MAX_LCN             9999
#define VALID_RANGE_LCN     799

#define RIKSTV_HEARING_AND_VISUALLY_IMPAIRED_LCN_START  900
#define RIKSTV_HEARING_AND_VISUALLY_IMPAIRED_LCN_END  999
#define ITALY_PREFER_LCN_OVERFLOW_START 75
#define ITALY_PREFER_LCN_OVERFLOW_END 99
#define ITALY_MAIN_LCN_OVERFLOW_START 850
#define ITALY_MAIN_LCN_OVERFLOW_END MAX_LCN//9999

#define ITALY_PREFER_LCN_START 1
#define ITALY_PREFER_LCN_END 99
#define ITALY_ASSIGN_LCN_START 100
#define ITALY_ASSIGN_LCN_END 999

#define ITALY_NETWORK_START 0x3001
#define ITALY_NETWORK_END 0x3100


//---------- DVBT -----------
#undef MAX_DTVPROGRAM
#undef MAX_MUX_NUMBER
#undef MAX_NETWOEK_NUMBER
#undef MAX_DTVCHANNELTABLE_MAP
#undef MAX_DTVIDTABLE_MAP


//#undef NTV_FUNCTION_ENABLE
//#define NTV_FUNCTION_ENABLE 1
//#undef ENABLE_FAVORITE_NETWORK
//#define ENABLE_FAVORITE_NETWORK 1


#if 1 // Normal
    // Please use new method, don't use this define!!
    //#define m_astDTVProgramIndexTable g_astDTVProgramIndexTable_DVBT
#else // Debug mode
    #define m_astDTVProgramIndexTable_  Rtn_DTVProgramIndexTable_DVBT(__LINE__)
DTVPROGRAMINDEX * Rtn_DTVProgramIndexTable_DVBT(U16 u16Line)
{
#if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
    if( CUR_DB_SEL() == E_DTV_DB_SEL_DVBC )
    {
    #if 1
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);
        printf("[DB Err-1 at %u]", u16Line);
        msDebug_ANSI_AllAttrOffText();
    #endif
        return m_astDTVProgramIndexTable_DVBC;
    }
#endif

#if(ENABLE_S2)
    if( CUR_DB_SEL() == E_DTV_DB_SEL_DVBS )
    {
    #if 1
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);
        printf("[DB Err-2 at %u]", u16Line);
        msDebug_ANSI_AllAttrOffText();
    #endif
        return m_astS2ProgramIndexTable;
    }
#endif

    if( E_DTV_DB_NUM > 1 )
        printf("[DB Err-3 at %u]", u16Line);

    return g_astDTVProgramIndexTable_DVBT;
}
#endif

#if 1 // Normal
    //#define _astDTVProgramIDTable   g_astDTVProgramIDTable_DVBT
#else // Debug
    #define _astDTVProgramIDTable_   Rtn_DTVProgramIDTable_DVBT(__LINE__)
DTVPROGRAMID_M * Rtn_DTVProgramIDTable_DVBT(U16 u16Line)
{
#if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
    if( CUR_DB_SEL() == E_DTV_DB_SEL_DVBC )
    {
    #if 1
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);
        printf("[DB Err-1 at %u]", u16Line);
        msDebug_ANSI_AllAttrOffText();
    #endif
        return g_astDTVProgramIDTable_DVBC;
    }
#endif

#if(ENABLE_S2)
    if( CUR_DB_SEL() == E_DTV_DB_SEL_DVBS )
    {
    #if 1
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);
        printf("[DB Err-2 at %u]", u16Line);
        msDebug_ANSI_AllAttrOffText();
    #endif
        return _astS2ProgramIDTable;
    }
#endif

    if( E_DTV_DB_NUM > 1 )
        printf("[DB Err-3 at %u]", u16Line);

    return g_astDTVProgramIDTable_DVBT;
}
#endif

//#define m_acDTVProgramTableMap g_acDTVProgramTableMap_DVBT
//#define m_acDTVIDtableMap g_acDTVIDtableMap_DVBT
//#define _astDTVNetwork  g_astDTVNetwork_DVBT

//WORD m_awProgramCount[E_CM_SERVICE_POS_NUMS][MAX_COUNT_PROGRAM_OPTION];

//-------------------------------------------------------------------------


static WORD m_wPastServiceId = INVALID_SERVICE_ID;
static BOOLEAN bNotAddThisService = FALSE;

static WORD m_wPastOriginalNetworkId = INVALID_ON_ID;
static WORD m_wPastTransportStreamId = INVALID_TS_ID;


static MEMBER_COUNTRY m_eCountry;


static U8 _au8CurNetworkName[MAX_NETWORK_NAME];
static U8 _au8CurNetworkLen;
static U16 _u16ValidAudioIndex=0xFFFF;
static BOOLEAN _bSaveDataToFlash=TRUE;
static U8 u8CM_LibVer[32] = {CM_VER()};

#if (NTV_FUNCTION_ENABLE)
static U8 s_au8FavoriteNetwork[E_DTV_DB_NUM] = {0};//{INVALID_NETWORKINDEX};
//static BYTE _cFavoriteNetwork = INVALID_NETWORKINDEX;
//#define _cFavoriteNetwork s_au8FavoriteNetwork[eCurDbSel]
#endif

static DTV_SIMPLE_SERVICE_INFO* _pDuplicateServiceList=NULL;

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
#define MAX_SGT_MUX_NUMBER 120
static U8 u8ServiceId;

static U16 _u16SgtServiceNumber;
static DVBS_SI_SGT_BASIC_SERVICE_LIST_INFO _astServiceListInfo[MAX_SGT_MUX_NUMBER];
static DVBS_SI_SGT_SERVICE_INFO _astServiceInfo[MAX_DTV_S2_PROGRAM];
static U16 _u16SgtServiceListIdCount =0;
extern MS_U8 _u8IsAstraLCNScan;
//static BOOLEAN msAPI_CM_ResetInvalidLCN(MEMBER_SERVICETYPE bServiceType, WORD wOriinalLCN);
static void RemoveServicebyLcnAssignmentType(MEMBER_SERVICETYPE bServiceType ,U8 u8LcnAssinmentType);
static void DeleteInvalidLCNService(MEMBER_SERVICETYPE bServiceType ,U8 u8LcnAssinmentType);

#endif //#if(ASTRA_HD_ENABLE)

#ifdef ENABLE_DELETE_PROGRAM_CONTROL
static BOOLEAN m_bVaildData = FALSE;
static BOOLEAN m_bHaveRemoved = FALSE;
static BYTE m_bRFChannelNumber;
static BYTE m_bPLP_ID;
static BYTE m_bHpLp;
static BYTE m_bCountOfServiceID;
static BYTE m_bsat;
static WORD m_wfreq;
static WORD m_wTSID;
static WORD m_wService_ID[MAX_COUNT_PROGRAM_OPTION];
static MEMBER_SERVICETYPE m_eService_Type[MAX_COUNT_PROGRAM_OPTION];
#endif

static BOOLEAN _bServiceMoved;

//------------------------------------------------------------------------------
// Private functions.
//------------------------------------------------------------------------------

//-----------------------------------------------------------------------------

static BOOLEAN IsPhysicalChannelNumberValid(U16 u16RFChannelNumber);

static BOOLEAN IsTS_IDValid(WORD wTransportStream_ID);
static BOOLEAN IsON_IDValid(WORD wOriginalNetwork_ID);

static BOOLEAN IsAudioPIDValid(WORD wAudPID);
//static BOOLEAN _IsAudioLangCodeValid(AUDIO_LANG_CODE eAudioLangCode);


//static BOOLEAN CreatDTVProgramIndexTableAndProgramIDTable(void);
static BOOLEAN CreatDTVProgramIndexTableAndProgramIDTable(TypDtvDbSel eDtvDbSel);


static BOOLEAN FillDTVProgramIndexTableWithOrder(TypDtvDbSel eDtvDbSel);
static BOOLEAN FillDTVProgramIndexTableWithoutOrder(TypDtvDbSel eDtvDbSel);

//static BOOLEAN FillDTVProgramIDTable(MEMBER_SERVICETYPE bServiceType);
//static BYTE AddProgramIDTable(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, BYTE cRFChannelNumber);


#if ENABLE_SBTVD_CM_APP
static BOOLEAN SortProgram_Brazil(MEMBER_SERVICETYPE bServiceType);
#endif


static BOOLEAN SortProgramforLCNSorting(void);
#if (NTV_FUNCTION_ENABLE)
static BOOLEAN SortProgramByRegionPriority(MEMBER_SERVICETYPE bServiceType);
static void msAPI_CM_FillMove_AttributeWithDefault(MEMBER_SERVICETYPE bServiceType);
static WORD msAPI_CM_GetFirstSpecialProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
static WORD msAPI_CM_GetLastSpecialProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped);
#endif

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
#if 0
static FUNCTION_RESULT ChangeLCN(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wLCN);
#else
static FUNCTION_RESULT SwapLCN(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wLCN);
#endif
#endif
static BOOLEAN MoveProgram(WORD wFromOrder, WORD wToOrder);
static BOOLEAN SwapProgram(WORD wFromOrder, WORD wToOrder);

static WORD GetEmptyIndexOfProgramTable_DBSel(TypDtvDbSel eDtvDbSel);

static BOOLEAN FillAudioStreamInfoWithDefault(AUD_INFO *pstAudioStreamInfo);

//static BOOLEAN FillProgramIndexWithDefault(DTVPROGRAMINDEX * pstDTVProgramIndex);
static BOOLEAN FillProgramDataWithDefault(BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember);
static BOOLEAN AreOrdersSameService(WORD wOrderOfChamp, WORD wOrderOfChallenger, BOOLEAN bCheckTSID);
static void DistinguishLCNSameService(MEMBER_SERVICETYPE bServiceType);
static BYTE GetCountOfSameServiceWithIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BOOLEAN bCheckTsID);
static BYTE GetCountOfSameServiceWithIDsAndPmtPid(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, WORD wPmt_Pid, BOOLEAN bCheckTsID);
static WORD GetOrderOfSameServiceWithIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, BOOLEAN bCheckTsID);

static WORD GetOrderOfSameServiceWithPCN(WORD cRFChannelNumber, WORD wService_ID);
//static WORD GetOrderOfSameServiceWithPCN(BYTE cRFChannelNumber, WORD wService_ID);

//static WORD GetProgramCount(MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption);


//----------------------------------------------------------------------------------------
//static BOOLEAN SaveCurrentServiceType(MEMBER_SERVICETYPE bServiceType);
#define SaveCurrentServiceType(bServiceType)    SaveCurrentServiceType_DBSel(CUR_DB_SEL(),(bServiceType))
static BOOLEAN SaveCurrentServiceType_DBSel(TypDtvDbSel eDtvDbSel,MEMBER_SERVICETYPE bServiceType);

//static MEMBER_SERVICETYPE LoadCurrentServiceType(void);
#define LoadCurrentServiceType()    LoadCurrentServiceType_DBSel(CUR_DB_SEL())
static MEMBER_SERVICETYPE LoadCurrentServiceType_DBSel(TypDtvDbSel eDtvDbSel);


//static WORD LoadCurrentOrderOfTV(void);
#define LoadCurrentOrderOfTV()  LoadCurrentOrderOfTV_DBSel(CUR_DB_SEL())
static WORD LoadCurrentOrderOfTV_DBSel(TypDtvDbSel eDtvDbSel);

//static WORD LoadCurrentOrderOfRadio(void);
#define LoadCurrentOrderOfRadio()   LoadCurrentOrderOfRadio_DBSel(CUR_DB_SEL())
static WORD LoadCurrentOrderOfRadio_DBSel(TypDtvDbSel eDtvDbSel);

//static WORD LoadCurrentOrderOfData(void);
#define LoadCurrentOrderOfData()    LoadCurrentOrderOfData_DBSel(CUR_DB_SEL())
static WORD LoadCurrentOrderOfData_DBSel(TypDtvDbSel eDtvDbSel);

//----------------------------------------------------------------------------------------

#if ENABLE_DTV_STORE_TTX_PAGE_INFO
static WORD GetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex);
static void SetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex, WORD u16ListPageNumber);
#endif


#if (ENABLE_SAVE_SQI)
#define INVALID_SQI 0xFFFF
static S8 SelectBestMux(CHANNEL_ATTRIBUTE *Misc1, WORD wNID_1, WORD wSQI1, CHANNEL_ATTRIBUTE *Misc2, WORD wNID_2, WORD wSQI2);
#else
static S8 SelectBestMux(CHANNEL_ATTRIBUTE *Misc1, WORD wNID_1, CHANNEL_ATTRIBUTE *Misc2, WORD wNID_2);
#endif
static void RemoveSameService(MEMBER_SERVICETYPE bServiceType);//for Nordig Spec


//static void ResetIDtable(void);
#define ResetIDtable()  ResetIDtable_DBSel(CUR_DB_SEL())
static void ResetIDtable_DBSel(TypDtvDbSel eDtvDbSel);


//static void RemoveInactiveID(void);
static void UpdateIDInfo(TypDtvDbSel eDtvDbSel);

E_CM_SERVICE_POS ConvertServiceTypeToPosition(MEMBER_SERVICETYPE eSERVICETYPE);
static void DistinguishSDLCNAndHDSimuLCNDuplicate(MEMBER_SERVICETYPE bServiceType, WORD wNativeON_ID);
static void _RestInvalidMUXAndNetwork(void);
#if ENABLE_DVBC
static BOOLEAN IsFreqInsideOffsetRange(U32 u32SrcFreq, U32 u32CompFreq);
#endif
static void _FillNextValidOrderToProgramData(DTV_CHANNEL_INFO *pDTVProgramData, WORD wPRIndex);

#if(ENABLE_S2_FAST_SCAN)
static WORD GetOrderOfSameServiceWithServiceIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal);
static U16 GetCountOfSameServiceWithServiceIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID);
#endif //#if(ENABLE_S2_FAST_SCAN)

#if (ENABLE_DTV_EPG)
static void (*_pfNotify_CM_SwapProgram)(WORD wFromOrder, WORD wToOrder)=NULL;
static void (*_pfNotify_CM_MoveProgram)(U16 u16FromIndex, U16 u16ToIndex)=NULL;
static void (*_pfNotify_SrvPriorityHandler) (U16 u16MainlistIdx)=NULL;
static void (*_pfNotify_CM_RemoveProgram) (WORD wSrvOrder)=NULL;
#endif
BOOLEAN _msAPI_CM_GetCurrentNetworkName(U8 *bNetworkName, U8 *u8NetworkLen);

static BOOLEAN _RemoveService(TypDtvDbSel eDtvDbSel, WORD cIDIndex, WORD wService_ID);
static WORD GetOrderOfSameServiceWithIDsAndRFCH(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, BOOLEAN bCheckTsID, U8 u8RFChannelNumber);

#define DBGMSG(x) // x
static WORD _wCurTSID=INVALID_TS_ID;
#if (ENABLE_EPG_MUX)
static BOOLEAN _bBarkerEITUpdate = FALSE;
#endif
#if (ENABLE_CI_PLUS)
static BOOLEAN _RemoveServiceWithSameLCN(TypDtvDbSel eDtvDbSel, U16 u16IDIndex, WORD wService_ID, WORD wLCN);
static BOOLEAN _bIsOpMode = FALSE;
static BOOLEAN _bIsOpType2 = FALSE;
#endif

//========================================================================

BOOLEAN msAPI_DtvSys_Is_LCN_RANK_COUNTRY(EN_OSD_COUNTRY_SETTING eOSD_COUNTRY)
{
    switch(eOSD_COUNTRY)
    {
        case OSD_COUNTRY_MALAYSIA:
        case OSD_COUNTRY_INDONESIA:
        case OSD_COUNTRY_THAILAND:
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
        case OSD_COUNTRY_KUWAIT:
        case OSD_COUNTRY_OMAN:
        case OSD_COUNTRY_QATAR:
        case OSD_COUNTRY_SAUDI_ARABIA:
        case OSD_COUNTRY_BAHRAIN:

    #if (ENABLE_COUNTRY_SINGAPORE)
        case OSD_COUNTRY_SINGAPORE:
    #endif

    #if (ENABLE_COUNTRY_GHANA)
        case OSD_COUNTRY_GHANA:
    #endif

    #if (ENABLE_COUNTRY_MYANMAR)
        case OSD_COUNTRY_MYANMAR:
    #endif
            return TRUE;

        default:
            break;
    }

    return FALSE;
}

U16 msAPI_DtvDB_Get_ProgramCount(TypDtvDbSel eDtvDbSel, U8 u8ServiceIdx, U8 u8OptionIdx )
{
    U16 u16Count = 0;

    eDtvDbSel=eDtvDbSel;

    if( u8ServiceIdx >= E_CM_SERVICE_POS_NUMS )
    {
        printf("\nError: u8ServiceIdx=%u\n", u8ServiceIdx);
        return 0;
    }
    if( u8OptionIdx >= MAX_COUNT_PROGRAM_OPTION )
    {
        printf("\nError: u8OptionIdx=%u\n", u8ServiceIdx);
        return 0;
    }

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        u16Count = m_awS2ProgramCount[u8ServiceIdx][u8OptionIdx];
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        u16Count = g_au16ProgramCount_DVBC[u8ServiceIdx][u8OptionIdx];
    }
    else
#endif
    {
        u16Count = g_au16ProgramCount_DVBT[u8ServiceIdx][u8OptionIdx];
    }

    return u16Count;
}

BOOL msAPI_DtvDB_Set_ProgramCount(TypDtvDbSel eDtvDbSel, U8 u8ServiceIdx, U8 u8OptionIdx, U16 u16Count )
{
    DEBUG_DTV_PROG_COUNT( printf("msAPI_DtvDB_Set_ProgramCount(eDtvDbSel=%u, u8ServiceIdx=%u, u8OptionIdx=%u, u16Count=%u)\n", eDtvDbSel, u8ServiceIdx, u8OptionIdx, u16Count); );

    eDtvDbSel=eDtvDbSel;

    if( u8ServiceIdx >= E_CM_SERVICE_POS_NUMS )
    {
        printf("\nError: u8ServiceIdx=%u\n", u8ServiceIdx);
        return FALSE;
    }
    if( u8OptionIdx >= MAX_COUNT_PROGRAM_OPTION )
    {
        printf("\nError: u8OptionIdx=%u\n", u8ServiceIdx);
        return FALSE;
    }

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        m_awS2ProgramCount[u8ServiceIdx][u8OptionIdx] = u16Count;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        g_au16ProgramCount_DVBC[u8ServiceIdx][u8OptionIdx] = u16Count;
    }
    else
#endif
    {
        g_au16ProgramCount_DVBT[u8ServiceIdx][u8OptionIdx] = u16Count;
    }

    return TRUE;
}

//------------------------------------------------------------------------------
///  Initialize Parameter
/// @return  :
//------------------------------------------------------------------------------
void msAPI_CM_Init(void)
{
#if(BLOADER)
    m_eCountry = DEFAULT_COUNTRY;
#else
    m_eCountry = stGenSetting.stTvSetting.eCountry;
#endif
}

#if (ENABLE_DTV_EPG)
void msAPI_CM_Init_EPG(DTV_CM_INIT_PARAMETER* psNotify)
{
    _pfNotify_CM_SwapProgram = psNotify->pfNotify_CM_SwapProgram;
    _pfNotify_CM_MoveProgram = psNotify->pfNotify_CM_MoveProgram;
    _pfNotify_SrvPriorityHandler = psNotify->pfNotify_SrvPriorityHandler;
    _pfNotify_CM_RemoveProgram = psNotify->pfNotify_CM_RemoveProgram;
    //printf("CM init\n");
}
#endif

void msAPI_CM_DebugArrange(void)
{
    WORD wdOrder,wdservice,wdLCN,wdLCNType,wdDelete,wService_ID,bVisibleServiceFlag,wdPRIndex,wPrio;
    DTVPROGRAMINDEX *pMuxTable;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    pMuxTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    for(wdOrder=0; wdOrder < u16ProgramIndexTableArraySize; wdOrder++)
    {
        if(FALSE == IsProgramEntityActive(pMuxTable[wdOrder].wPRIndex))
        {
            continue;
        }

        wdLCN = pMuxTable[wdOrder].wLCN;
        wdLCNType = pMuxTable[wdOrder].eLCNAssignmentType;
        wdservice = pMuxTable[wdOrder].bServiceType;
        wdDelete = pMuxTable[wdOrder].bIsDelete;
        wService_ID = pMuxTable[wdOrder].wService_ID;
        bVisibleServiceFlag = pMuxTable[wdOrder].bVisibleServiceFlag;
        wdPRIndex = pMuxTable[wdOrder].wPRIndex;
        wPrio = pMuxTable[wdOrder].bServiceTypePrio ;

        printf("--Debug: wdOrder=%d, wdservice=%d, wdLCN=%d, wdLCNType=%d, wService_ID=%d, wdDelete=%d, bVisibleServiceFlag=%d, wdPRIndex=%d, wPrio=%d\n",wdOrder,wdservice,wdLCN,wdLCNType,wService_ID,wdDelete,bVisibleServiceFlag,wdPRIndex, wPrio);
    }
}

#if(ENABLE_API_DTV_SYSTEM_2015)
void msAPI_CM_Reset_ProgramIndexTable(TypDtvDbSel eDtvDbSel)
{
    U16 i;
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    for ( i = 0; i < u16ProgramIndexTableArraySize; i++ )
    {
        pstProgramIndexTable[i].bServiceType = E_SERVICETYPE_INVALID;
        pstProgramIndexTable[i].bServiceTypePrio = E_SERVICETYPE_PRIORITY_NONE;
        pstProgramIndexTable[i].wPRIndex = INVALID_PRINDEX;
    }
}

void msAPI_CM_ResetAndSave_ServiceTypeAndOrder(TypDtvDbSel eDtvDbSel)
{
    m_aeCurrentServiceType[eDtvDbSel] = DEFAULT_CURRENT_SERVICETYPE;
    msAPI_DtvDB_Set_CurServiceType(eDtvDbSel, m_aeCurrentServiceType[eDtvDbSel]);

    m_awCurrentOrderOfTV[eDtvDbSel] = DEFAULT_CURRENT_ORDER_TV;
    SaveCurrentOrderOfTV_DBSel(eDtvDbSel, m_awCurrentOrderOfTV[eDtvDbSel]);
    m_awPastOrderOfTV[eDtvDbSel] = m_awCurrentOrderOfTV[eDtvDbSel];

    m_awCurrentOrderOfRadio[eDtvDbSel] = DEFAULT_CURRENT_ORDER_RADIO(eDtvDbSel);
    SaveCurrentOrderOfRadio_DBSel(eDtvDbSel, m_awCurrentOrderOfRadio[eDtvDbSel]);
    m_awPastOrderOfRadio[eDtvDbSel] = m_awCurrentOrderOfRadio[eDtvDbSel];

    m_awCurrentOrderOfData[eDtvDbSel] = DEFAULT_CURRENT_ORDER_DATA(eDtvDbSel);
    SaveCurrentOrderOfData_DBSel(eDtvDbSel, m_awCurrentOrderOfData[eDtvDbSel]);
    m_awPastOrderOfData[eDtvDbSel] = m_awCurrentOrderOfData[eDtvDbSel];
}

BOOLEAN msAPI_CM_ResetAllProgram_ByDBSel(TypDtvDbSel eDtvDbSel)
{
    U16 i;
    U8* pu8CurDTVProgramTableMap = msAPI_DtvDB_Get_ProgTableMap(eDtvDbSel);
    U16 u16CurDTVProgramTableMapArraySize = msAPI_DtvDB_Get_ProgTableMapArraySize(eDtvDbSel);


    PRINT_CURRENT_LINE();
    printf("msAPI_CM_ResetAllProgram(eDtvDbSel=%u)\n", eDtvDbSel);



    // Clear DtvProgramTableMap
#if 1 // New method
    for( i = 0; i < (u16CurDTVProgramTableMapArraySize); i++)
    {
        pu8CurDTVProgramTableMap[i] = 0x00;
    }

#else
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        for (i=0; i < (MAX_DTVCHANNELTABLE_MAP_DVBC); i++)
        {
            m_acDTV_C_ProgramTableMap[i] = 0x00;
        }
    }
    else
  #endif
    {
        for (i=0; i < (MAX_DTVCHANNELTABLE_MAP); i++)
        {
            m_acDTVProgramTableMap[i] = 0x00;
        }
    }
#endif

    // Copy DtvProgramTableMap to RamDisk
#if 1 // New method
    //SetNVRAM(u32CurDTVProgramTableMapRamDiskAddr, pu8CurDTVProgramTableMap, u16CurDTVProgramTableMapArraySize);
    msAPI_DtvDB_Save_ProgramTableMap(eDtvDbSel, pu8CurDTVProgramTableMap, u16CurDTVProgramTableMapArraySize );
#else
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        SetNVRAM(BASEADDRESS_PR_DTV_C_PRTABLEMAP, m_acDTVProgramTableMap_DVBC, sizeof(m_acDTV_C_ProgramTableMap));
    }
    else
  #endif
    {
        SetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP, m_acDTVProgramTableMap, sizeof(m_acDTVProgramTableMap));
    }
#endif

    LogicalChannelNumberIsArranged_DBSel(eDtvDbSel, FALSE);

    // Clear Program Index table
    msAPI_CM_Reset_ProgramIndexTable(eDtvDbSel);

    // Reset ID Table
    ResetIDtable_DBSel(eDtvDbSel);

    // Reset Favorite region
#if (NTV_FUNCTION_ENABLE)
    msAPI_CM_Set_FavoriteNetwork(INVALID_NETWORKINDEX);
#endif

    msAPI_CM_ResetAndSave_ServiceTypeAndOrder(eDtvDbSel);

    // Reset Program count
#if 1 // Use new method
    {
        U8 u8ServiceTypeIdx, u8OptionIdx;
        for( u8ServiceTypeIdx = 0; u8ServiceTypeIdx < E_CM_SERVICE_POS_NUMS; ++ u8ServiceTypeIdx )
        {
            for( u8OptionIdx = 0; u8OptionIdx < MAX_COUNT_PROGRAM_OPTION; ++ u8OptionIdx )
            {
                msAPI_DtvDB_Set_ProgramCount(eDtvDbSel, u8ServiceTypeIdx, u8OptionIdx, 0 );
            }
        }
    }
#else
  #if DVB_T_C_DIFF_DB
    //if (IsDVBCInUse())
    if( eCurDbSel == E_DTV_DB_SEL_DVBC )
    {
        //printf("\n~~~ ResetAllProgram DVBC...\n");
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    }
    else
  #endif
    {
        //printf("\n~~~ ResetAllProgram DTV...\n");
        m_awProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

        m_awProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

        m_awProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    }
#endif

    //clear unsupported ISO639 language code
    //msAPI_CM_ResetUnsupportedIso639Code();

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    {
        AUD_INFO stAudInfo;
        memset(&stAudInfo, 0, sizeof(stAudInfo));
        stAudInfo.wAudPID = INVALID_PID;
        msAPI_DtvDB_AudInfoTable_ResetAll(eDtvDbSel, &stAudInfo);
    }
#endif

    return TRUE;
}

#endif

//****************************************************************************
///  Reset all program
/// @return BOOLEAN : Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_ResetAllProgram(void)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    return msAPI_CM_ResetAllProgram_ByDBSel(eCurDbSel);

#else
    WORD i;
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        for (i=0; i < (MAX_DTVCHANNELTABLE_MAP_DVBC); i++)
        {
            m_acDTVProgramTableMap_DVBC[i] = 0x00;
        }
    }
    else
#endif
    {
        for (i=0; i < (MAX_DTVCHANNELTABLE_MAP); i++)
        {
            m_acDTVProgramTableMap[i] = 0x00;
        }
    }

#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        SetNVRAM(BASEADDRESS_PR_DTV_C_PRTABLEMAP, m_acDTVProgramTableMap_DVBC, sizeof(m_acDTVProgramTableMap_DVBC));
    }
    else
#endif
    {
        SetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP, m_acDTVProgramTableMap, sizeof(m_acDTVProgramTableMap));
    }
    LogicalChannelNumberIsArranged(FALSE);

    for (i=0; i < MAX_DTVPROGRAM; i++)
    {
        m_astDTVProgramIndexTable[i].bServiceType = E_SERVICETYPE_INVALID;
        m_astDTVProgramIndexTable[i].bServiceTypePrio = E_SERVICETYPE_PRIORITY_NONE;
        m_astDTVProgramIndexTable[i].wPRIndex = INVALID_PRINDEX;
    }
    ResetIDtable();
#if (NTV_FUNCTION_ENABLE)
    msAPI_CM_Set_FavoriteNetwork(INVALID_NETWORKINDEX);
#endif
    m_eCurrentServiceType = DEFAULT_CURRENT_SERVICETYPE;
    m_wCurrentOrderOfTV = DEFAULT_CURRENT_ORDER_TV;
    SaveCurrentOrderOfTV(m_wCurrentOrderOfTV);
    m_wPastOrderOfTV = m_wCurrentOrderOfTV;

    m_wCurrentOrderOfRadio = DEFAULT_CURRENT_ORDER_RADIO;
    SaveCurrentOrderOfRadio(m_wCurrentOrderOfRadio);
    m_wPastOrderOfRadio = m_wCurrentOrderOfRadio;
    m_wCurrentOrderOfData = DEFAULT_CURRENT_ORDER_DATA;
    SaveCurrentOrderOfData(m_wCurrentOrderOfData);
    m_wPastOrderOfData = m_wCurrentOrderOfData;

    #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        //printf("\n~~~ ResetAllProgram CATV...\n");
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    }
    else
    {
        //printf("\n~~~ ResetAllProgram DTV...\n");
        m_awProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

        m_awProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

        m_awProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    }
    #else
    m_awProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

    m_awProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

    m_awProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    #endif
    //clear unsupported ISO639 language code
    //msAPI_CM_ResetUnsupportedIso639Code();

    return TRUE;
#endif
}

//****************************************************************************
/// Get Current service type
/// @return MEMBER_SERVICETYPE : Service type
//****************************************************************************
MEMBER_SERVICETYPE msAPI_CM_GetCurrentServiceType(void)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
#endif
    return  m_eCurrentServiceType;
}

//****************************************************************************
/// Set Current service type
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN : Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_SetCurrentServiceType(MEMBER_SERVICETYPE bServiceType)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
#endif

    if( (FALSE == IsServiceTypeValid(bServiceType))
      ||(m_eCurrentServiceType == bServiceType)
      )
    {
        return FALSE;
    }

    m_eCurrentServiceType = bServiceType;
    SaveCurrentServiceType(m_eCurrentServiceType);

    return  TRUE;
}

//****************************************************************************
/// Get Current position
/// @param bServiceType \b IN: Service type
/// @return WORD : current position
//****************************************************************************
WORD msAPI_CM_GetCurrentPosition(MEMBER_SERVICETYPE bServiceType)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( bServiceType == E_SERVICETYPE_DTV )
    {
        return ConvertOrderToPosition(m_wCurrentOrderOfTV);
    }
    else if( bServiceType == E_SERVICETYPE_DATA )
    {
        return ConvertOrderToPosition(m_wCurrentOrderOfData);
    }
    else
    {
        return ConvertOrderToPosition(m_wCurrentOrderOfRadio);
    }
}

//****************************************************************************
/// Set Current position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition : current position
/// @return BOOLEAN : Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_SetCurrentPosition(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
#endif

    if( bServiceType == E_SERVICETYPE_DTV )
    {
        m_wPastOrderOfTV = m_wCurrentOrderOfTV;
        m_wCurrentOrderOfTV = ConvertPositionToOrder(bServiceType, wPosition);
        SaveCurrentOrderOfTV_DBSel(eCurDbSel, m_wCurrentOrderOfTV);
    }
    else if( bServiceType == E_SERVICETYPE_DATA )
    {
        m_wPastOrderOfData = m_wCurrentOrderOfData;
        m_wCurrentOrderOfData = ConvertPositionToOrder(bServiceType, wPosition);
        SaveCurrentOrderOfData_DBSel(eCurDbSel,m_wCurrentOrderOfData);
    }
    else
    {
        m_wPastOrderOfRadio = m_wCurrentOrderOfRadio;
        m_wCurrentOrderOfRadio = ConvertPositionToOrder(bServiceType, wPosition);
        SaveCurrentOrderOfRadio_DBSel(eCurDbSel,m_wCurrentOrderOfRadio);
    }

  #if (ENABLE_DTV_EPG)
    // Calculate Pr Priority for EPGDB
    if(_pfNotify_SrvPriorityHandler)
    {
        #if (TS_FROM_PLAYCARD == DISABLE)
        _pfNotify_SrvPriorityHandler(wPosition);
        #endif
    }
    //MApp_Epg_SrvPriorityHandler(wPosition);
  #endif

    return TRUE;
}

//****************************************************************************
/// Get list position by program position
/// @param wPosition \b IN: Position
/// @param eServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return WORD : Program position in channl list
//****************************************************************************
WORD msAPI_CM_GetListPositionbyPosition(WORD wPosition, MEMBER_SERVICETYPE eServiceType)
{
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(CUR_DB_SEL());

    WORD wOrder,wOrder1,wListPoistion;

    wOrder = ConvertPositionToOrder(eServiceType,wPosition);

    wListPoistion = 0;

    for(wOrder1=0; wOrder1 < wOrder; wOrder1++)
    {
        if( INVALID_LOGICAL_CHANNEL_NUMBER == pstDTVProgramIndexTable[wOrder1].wLCN )
        {
            continue;
        }
        if(FALSE == IsProgramEntityActive(pstDTVProgramIndexTable[wOrder1].wPRIndex))
        {
            continue;
        }
        wListPoistion++;
    }
    return wListPoistion;
}

//****************************************************************************
/// Get list position by program position
/// @param wListPoistion \b IN:  Program position in channl list
/// @param *eServiceType \b IN: Point to service type
/// -@see MEMBER_SERVICETYPE
/// @return WORD :  Position
//****************************************************************************
WORD msAPI_CM_GetPositionbyListPosition(WORD wListPoistion, MEMBER_SERVICETYPE *eServiceType)
{
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    WORD wOrder,wPosition;

    //for(wOrder=0; wOrder < MAX_DTVPROGRAM; wOrder++)
    for(wOrder=0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
    {
        if( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder].wLCN )
        {
            continue;
        }
        if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder].wPRIndex))
        {
            continue;
        }
        if(wListPoistion == 0) break;
        wListPoistion--;
    }

    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return INVALID_PROGRAM_POSITION;
    }
    else
    {
        wPosition = ConvertOrderToPosition(wOrder);
        *eServiceType = (MEMBER_SERVICETYPE)pstProgramIndexTable[wOrder].bServiceType;
        return wPosition;
    }
}

//****************************************************************************
/// Count program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param eBoundary \b IN: Boundry
/// -@see E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY
/// @return WORD : Program count
//****************************************************************************
WORD msAPI_CM_CountProgram(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return 0;
    }

    if(E_PROGACESS_INCLUDE_VISIBLE_ONLY == eBoundary)
    {
        return msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }
    else if( E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO == eBoundary)
    {
        return msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED);
    }
    else if( E_PROGACESS_INCLUDE_ALL== eBoundary)
    {
        return msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    }

    return 0;
}

//****************************************************************************
/// Get first program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : First Program position
//****************************************************************************
WORD msAPI_CM_GetFirstProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        if( TRUE == bIncludeSkipped )
        {
            return wPosition;
        }
        else
        {
            if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
            {
                return wPosition;
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}
//****************************************************************************
/// Get last program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : Last Program position
//****************************************************************************
WORD msAPI_CM_GetLastProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    for(wPosition=wProgramCount; wPosition >0; wPosition--)
    {
        if( TRUE == bIncludeSkipped )
        {
            return (wPosition-1);
        }
        else
        {
            if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, (wPosition-1), E_ATTRIBUTE_IS_SKIPPED) )
            {
                return (wPosition-1);
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}
#if NTV_FUNCTION_ENABLE
//****************************************************************************
/// Get first special program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : First Program position
//****************************************************************************
static WORD msAPI_CM_GetFirstSpecialProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wLCN;
    WORD wON_ID;
    WORD wOrder;
    BOOLEAN bIsSpecialService;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
        {
            continue;
        }


    #if 0//ENABLE_S2
        if (IsS2InUse())
            bIsSpecialService = m_astS2ProgramIndexTable[wOrder].bIsSpecialService;
        else
    #endif
            bIsSpecialService = pstProgramIndexTable[wOrder].bIsSpecialService;

        if( TRUE == bIncludeSkipped )
        {
            wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition);
            wON_ID = msAPI_CM_GetON_ID(bServiceType, wPosition);

            if(bIsSpecialService == TRUE && wON_ID == SI_ONID_NORWAY)
            {
                return wPosition;
            }
        }
        else
        {
            if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
            {
                wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition);
                wON_ID = msAPI_CM_GetON_ID(bServiceType, wPosition);

                if(bIsSpecialService == TRUE && wON_ID == SI_ONID_NORWAY)
                {
                    return wPosition;
                }
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}
//****************************************************************************
/// Get last program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : Last Program position
//****************************************************************************
static WORD msAPI_CM_GetLastSpecialProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wLCN;
    WORD wON_ID;
    WORD wOrder;
    BOOLEAN bIsSpecialService;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    for(wPosition=wProgramCount; wPosition >0; wPosition--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition-1);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;


        bIsSpecialService = pstProgramIndexTable[wOrder].bIsSpecialService;
        if( TRUE == bIncludeSkipped )
        {
            wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition-1);
            wON_ID = msAPI_CM_GetON_ID(bServiceType, wPosition-1);

            if(bIsSpecialService == TRUE && wON_ID == SI_ONID_NORWAY)
            {
                return (wPosition-1);
            }
            else
            {
                return INVALID_PROGRAM_POSITION;
            }
        }
        else
        {
            if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition-1, E_ATTRIBUTE_IS_SKIPPED) )
            {
                wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wPosition-1);
                wON_ID = msAPI_CM_GetON_ID(bServiceType, wPosition-1);

                if(bIsSpecialService == TRUE && wON_ID == SI_ONID_NORWAY)
                {
                    return (wPosition-1);
                }
                else
                {
                    return INVALID_PROGRAM_POSITION;
                }
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}
#endif

//****************************************************************************
/// Get next program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : First Program position
//****************************************************************************
WORD msAPI_CM_GetNextProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped, CHANNEL_LIST_TYPE bList_type, MEMBER_SERVICETYPE *bNewServiceType)
{
    WORD wProgramCount,wDTVProgramCount=0,wRadioProgramCount=0;
    WORD wDataProgramCount = 0;
    WORD wPosition,wOrder,wOriginalOrder;
    WORD i;
#if NTV_FUNCTION_ENABLE
    WORD wFirstDTVSpecailProgram = INVALID_PROGRAM_POSITION;
#endif

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    //MEMBER_SERVICETYPE bPreServiceType = bServiceType;
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( FALSE == IsPositionValid(bServiceType, wBasePosition) )
    {
        return INVALID_PROGRAM_POSITION;
    }
    if(bList_type == E_ALL_LIST && (bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO ||bServiceType == E_SERVICETYPE_DATA))
    {
        wDTVProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        wRadioProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        wDataProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        wProgramCount = wDTVProgramCount + wRadioProgramCount + wDataProgramCount;
    }
    else
    {
        wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }
    if(bList_type == E_ALL_LIST && (bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA))
    {
        if(bServiceType == E_SERVICETYPE_DTV && wBasePosition >= wDTVProgramCount)
        {
            wPosition = wDTVProgramCount;
        }
        else if(bServiceType == E_SERVICETYPE_RADIO && wBasePosition >= wRadioProgramCount)
        {
            wPosition = wRadioProgramCount;
        }
        else if(bServiceType == E_SERVICETYPE_DATA && wBasePosition >= wDataProgramCount)
        {
            wPosition = wDataProgramCount;
        }
        else
        {
            wPosition = wBasePosition;
        }
    }
    else if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }
    // if-part for LCN rank sort
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        for(wOrder=0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
        {
            if((WORD)bServiceType == pstProgramIndexTable[wOrder].bServiceType)
            {
                if(wBasePosition == 0) break;
                wBasePosition--;
            }
        }
        if(wOrder == u16ProgramIndexTableArraySize)
        {
            return INVALID_PROGRAM_POSITION;
        }
        wOriginalOrder = wOrder;

        for(wOrder=wOrder+1; wOrder < u16ProgramIndexTableArraySize; wOrder++)
        {
            if((INVALID_LOGICAL_CHANNEL_NUMBER != pstProgramIndexTable[wOrder].wLCN)
            &&( TRUE == pstProgramIndexTable[wOrder].bVisibleServiceFlag)
            &&( FALSE == pstProgramIndexTable[wOrder].bIsSkipped)
            &&( FALSE == pstProgramIndexTable[wOrder].bIsDelete))
            {
                break;
            }
        }

        if((wOrder == wOriginalOrder)||(wOrder == u16ProgramIndexTableArraySize))
        {
            for(wOrder=0;wOrder <wOriginalOrder; wOrder++)
            {
                if((INVALID_LOGICAL_CHANNEL_NUMBER != pstProgramIndexTable[wOrder].wLCN)
                &&( TRUE == pstProgramIndexTable[wOrder].bVisibleServiceFlag)
                &&( FALSE == pstProgramIndexTable[wOrder].bIsSkipped)
                &&( FALSE == pstProgramIndexTable[wOrder].bIsDelete))
                {
                    break;
                }
            }
        }

        if(wOrder != wOriginalOrder)
        {
            if( bNewServiceType != NULL )
            {
                *bNewServiceType = (MEMBER_SERVICETYPE)pstProgramIndexTable[wOrder].bServiceType;
            }
            wPosition = ConvertOrderToPosition(wOrder);
            return wPosition;
        }
        return INVALID_PROGRAM_POSITION;
    }

    for(i=0; i< wProgramCount; i++)
    {
        wPosition++;
        if(bList_type == E_ALL_LIST && (bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA))
        {
            if(bServiceType == E_SERVICETYPE_DTV)
            {
                if(wPosition >= wDTVProgramCount)
                {
#if NTV_FUNCTION_ENABLE
                    if(msAPI_CM_GetCountry() == E_NORWAY && msAPI_CM_GetLastSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped) != INVALID_PROGRAM_POSITION)
                    {
                        bServiceType = E_SERVICETYPE_DTV;
                    }
                    else
#endif
                    {
                        if(wRadioProgramCount > 0)
                        {
                                bServiceType = E_SERVICETYPE_RADIO;
                        }
                        else if(wDataProgramCount > 0)
                        {
                                bServiceType = E_SERVICETYPE_DATA;
                        }
                    }

                    wPosition = 0;
                }
#if (NTV_FUNCTION_ENABLE)
                else if(msAPI_CM_GetCountry() == E_NORWAY && wPosition == msAPI_CM_GetFirstSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped))
                {
                    if(wRadioProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_RADIO;
                        wPosition = 0;
                    }
                    else if(wDataProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DATA;
                        wPosition = 0;
                    }
                }
#endif
            }
            else if(bServiceType == E_SERVICETYPE_RADIO)
            {
                if(wPosition >= wRadioProgramCount)
                {
                    if(wDataProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DATA;
                    }
                    else if(wDTVProgramCount > 0)
                    {
#if NTV_FUNCTION_ENABLE
                        if(msAPI_CM_GetCountry() == E_NORWAY)
                        {
                            wFirstDTVSpecailProgram = msAPI_CM_GetFirstSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                        }
#endif
                        bServiceType = E_SERVICETYPE_DTV;
                    }
#if (NTV_FUNCTION_ENABLE)
                    if(msAPI_CM_GetCountry() == E_NORWAY)
                    {
                        if(wFirstDTVSpecailProgram != INVALID_PROGRAM_POSITION)
                            wPosition = wFirstDTVSpecailProgram;
                        else
                            wPosition = 0;
                    }
                    else
                    {
                        wPosition = 0;
                    }
#else
                    wPosition = 0;
#endif
                }
            }
            else if(bServiceType == E_SERVICETYPE_DATA)
            {
                if(wPosition >= wDataProgramCount)
                {
                    if(wDTVProgramCount > 0)
                    {
#if NTV_FUNCTION_ENABLE
                        if(msAPI_CM_GetCountry() == E_NORWAY)
                        {
                            wFirstDTVSpecailProgram = msAPI_CM_GetFirstSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                        }
#endif
                        bServiceType = E_SERVICETYPE_DTV;
                    }
                    else if(wRadioProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_RADIO;
                    }
#if NTV_FUNCTION_ENABLE
                    if(msAPI_CM_GetCountry() == E_NORWAY)
                    {
                        if(wFirstDTVSpecailProgram != INVALID_PROGRAM_POSITION)
                            wPosition = wFirstDTVSpecailProgram;
                        else
                            wPosition = 0;
                    }
                    else
                    {
                        wPosition = 0;
                    }
#else
                    wPosition = 0;
#endif
                }
            }
            #if 0
            if(bServiceType == E_SERVICETYPE_DTV && wPosition >= wDTVProgramCount)
            {
                bServiceType = E_SERVICETYPE_RADIO;
                wPosition=0;
            }
            else if(bServiceType == E_SERVICETYPE_RADIO && wPosition >= wRadioProgramCount)
            {
                bServiceType=E_SERVICETYPE_DTV;
                wPosition=0;
            }
            #endif
        }
        else if( wPosition >= wProgramCount )
        {
            wPosition = 0;
        }
        if(bList_type == E_ALL_LIST && bNewServiceType != NULL )
        {
            *bNewServiceType = bServiceType;
        }
        if( TRUE == bIncludeSkipped )
        {
            return wPosition;
        }
        else
        {
            if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
            {
                return wPosition;
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}

//****************************************************************************
/// Get previous program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @param *bNewServiceType \b IN: pointer to service type for return
/// -@see MEMBER_SERVICETYPE
/// @return WORD : First Program position
//****************************************************************************
WORD msAPI_CM_GetPrevProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped, CHANNEL_LIST_TYPE bList_type, MEMBER_SERVICETYPE *bNewServiceType)
{
    WORD wProgramCount = 0,wDTVProgramCount = 0,wRadioProgramCount = 0;
    WORD wDataProgramCount = 0;
    WORD wPosition,wOrder,wOriginalOrder;
    WORD i;
#if NTV_FUNCTION_ENABLE
    WORD wFirstDTVSpecailProgram = INVALID_PROGRAM_POSITION, wLastDTVSpecailProgram = INVALID_PROGRAM_POSITION;
#endif
    //MEMBER_SERVICETYPE bPreServiceType = bServiceType;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    if( u16ProgramIndexTableArraySize == 0 )
        return INVALID_PROGRAM_POSITION;


    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( FALSE == IsPositionValid(bServiceType, wBasePosition) )
    {
        return INVALID_PROGRAM_POSITION;
    }
    if(bList_type == E_ALL_LIST && (bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA))
    {
        wDTVProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        wRadioProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        wDataProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        wProgramCount = wDTVProgramCount + wRadioProgramCount + wDataProgramCount;
    }
    else
    {
        wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }
    if(bList_type == E_ALL_LIST && (bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA))
    {
        if(bServiceType == E_SERVICETYPE_DTV && wBasePosition >= wDTVProgramCount)
        {
            wPosition = wDTVProgramCount;
        }
        else if(bServiceType == E_SERVICETYPE_RADIO && wBasePosition >= wRadioProgramCount)
        {
            wPosition = wRadioProgramCount;
        }
        else if(bServiceType == E_SERVICETYPE_DATA && wBasePosition >= wDataProgramCount)
        {
            wPosition = wDataProgramCount;
        }
        else
        {
            wPosition = wBasePosition;
        }
    }
    else if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }
    // if-part for LCN rank sort
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        for(wOrder=0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
        {
            if((WORD)bServiceType == pstProgramIndexTable[wOrder].bServiceType)
            {
                if(wBasePosition == 0) break;

                wBasePosition--;
            }
        }
        if(wOrder >= u16ProgramIndexTableArraySize)
        {
            return INVALID_PROGRAM_POSITION;
        }

        wOriginalOrder = wOrder;

        //Fix coverity 185049. if u16ProgramIndexTableArraySize==0 then wOrder=wOrder-1 will let wOrder to 65535
        if(u16ProgramIndexTableArraySize > 0)
        {
            if(wOrder > 0)
            {
                for(wOrder=wOrder-1; wOrder > 0; wOrder--)
                {
                    if(wOrder >= u16ProgramIndexTableArraySize)
                    {
                        wOrder = u16ProgramIndexTableArraySize-1;
                    }
                    if(( INVALID_LOGICAL_CHANNEL_NUMBER != pstProgramIndexTable[wOrder].wLCN )
                    &&( TRUE == pstProgramIndexTable[wOrder].bVisibleServiceFlag)
                    &&( FALSE == pstProgramIndexTable[wOrder].bIsSkipped)
                    &&( FALSE == pstProgramIndexTable[wOrder].bIsDelete))
                    {
                        break;
                    }
                }
            }

            if((wOrder==wOriginalOrder)
            ||( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder].wLCN )
            ||( TRUE == pstProgramIndexTable[wOrder].bIsSkipped ))
            {
                for(wOrder=u16ProgramIndexTableArraySize-1;wOrder >wOriginalOrder; wOrder--)
                {
                    if(( INVALID_LOGICAL_CHANNEL_NUMBER != pstProgramIndexTable[wOrder].wLCN )
                    &&( TRUE == pstProgramIndexTable[wOrder].bVisibleServiceFlag)
                    &&( FALSE == pstProgramIndexTable[wOrder].bIsSkipped)
                    &&( FALSE == pstProgramIndexTable[wOrder].bIsDelete))
                    {
                        break;
                    }
                }
            }
        }


        if(wOrder!=wOriginalOrder)
        {
            //Fix coverity 182863
            if(bNewServiceType != NULL )
                *bNewServiceType = (MEMBER_SERVICETYPE)pstProgramIndexTable[wOrder].bServiceType;
            wPosition = ConvertOrderToPosition(wOrder);

            return wPosition;
        }
        return INVALID_PROGRAM_POSITION;
    }

    for(i=0; i< wProgramCount; i++)
    {
        if( wPosition > 0 )
        {
#if (NTV_FUNCTION_ENABLE)
            if((msAPI_CM_GetCountry() == E_NORWAY) && (bServiceType == E_SERVICETYPE_DTV))
            {
                wFirstDTVSpecailProgram = msAPI_CM_GetFirstSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                if(wFirstDTVSpecailProgram != INVALID_PROGRAM_POSITION && wPosition == wFirstDTVSpecailProgram)
                {
                    if(wDataProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DATA;
                        wPosition = wDataProgramCount - 1;
                    }
                    else if(wRadioProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_RADIO;
                        wPosition = wRadioProgramCount - 1;
                    }
                    else
                    {
                        wPosition--;
                    }
                }
                else
                    wPosition--;
            }
            else
#endif
            wPosition--;
        }
        else
        {
            if(bList_type == E_ALL_LIST && (bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA))
            {
                if(bServiceType == E_SERVICETYPE_DTV)
                {
#if NTV_FUNCTION_ENABLE
                    if((msAPI_CM_GetCountry() == E_NORWAY) && (wDTVProgramCount > 0))
                        wLastDTVSpecailProgram = msAPI_CM_GetLastSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                    if((msAPI_CM_GetCountry() == E_NORWAY) && (wLastDTVSpecailProgram != INVALID_PROGRAM_POSITION))
                    {
                        wPosition = wLastDTVSpecailProgram;
                    }
                    else
#endif
                    if(wDataProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DATA;
                        wPosition = wDataProgramCount - 1;
                    }
                    else if(wRadioProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_RADIO;
                        wPosition = wRadioProgramCount - 1;
                    }
                    else if(wDTVProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DTV;
                        wPosition = wDTVProgramCount - 1;
                    }
                }
                else if(bServiceType == E_SERVICETYPE_RADIO)
                {
                    if(wDTVProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DTV;
#if NTV_FUNCTION_ENABLE
                        if((msAPI_CM_GetCountry() == E_NORWAY) && (wDTVProgramCount > 0))
                            wFirstDTVSpecailProgram = msAPI_CM_GetFirstSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                        if((msAPI_CM_GetCountry() == E_NORWAY) && (wFirstDTVSpecailProgram != INVALID_PROGRAM_POSITION))
                        {
                            wPosition = wFirstDTVSpecailProgram-1;
                        }
                        else
#endif
                        wPosition = wDTVProgramCount - 1;
                    }
                    else if(wDataProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DATA;
                        wPosition = wDataProgramCount - 1;
                    }
                    else if(wRadioProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_RADIO;
                        wPosition = wRadioProgramCount - 1;
                    }
                }
                else if(bServiceType == E_SERVICETYPE_DATA)
                {
                    if(wRadioProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_RADIO;
                        wPosition = wRadioProgramCount - 1;
                    }
                    else if(wDTVProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DTV;
#if NTV_FUNCTION_ENABLE
                        if(msAPI_CM_GetCountry() == E_NORWAY)
                        {
                            wFirstDTVSpecailProgram = msAPI_CM_GetFirstSpecialProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                            if(wFirstDTVSpecailProgram != INVALID_PROGRAM_POSITION)
                            {
                                wPosition = wFirstDTVSpecailProgram-1;
                            }
                            else
                            {
                                wPosition = wDTVProgramCount - 1;
                            }
                        }
                        else
                        {
                            wPosition = wDTVProgramCount - 1;
                        }
#else
                        wPosition = wDTVProgramCount - 1;
#endif
                    }
                    else if(wDataProgramCount > 0)
                    {
                        bServiceType = E_SERVICETYPE_DATA;
                        wPosition = wDataProgramCount - 1;
                    }
                }
            }
            else
            {
                wPosition = wProgramCount - 1;
            }
        }
        if(bList_type == E_ALL_LIST && bNewServiceType != NULL )
        {
            *bNewServiceType = bServiceType;
        }
        if( TRUE == bIncludeSkipped )
        {
            return wPosition;
        }
        else
        {
            if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
            {
               return wPosition;
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}


//****************************************************************************
/// Count favorite program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return WORD : Favorite program number
//****************************************************************************
#if (CM_MULTI_FAVORITE)
static E_FAVORITE_TYPE g_DtvSys_eCurFavoriteType = E_FAVORITE_TYPE_1;
void msAPI_CM_Set_CurFavoriteType(E_FAVORITE_TYPE eFavoriteType)
{
    if( eFavoriteType > E_FAVORITE_TYPE_ALL )
        return;

    g_DtvSys_eCurFavoriteType = eFavoriteType;
}

E_MEMBER_CHANNEL_ATTRIBUTE msAPI_CM_ConvertFavTypeToChAttr(E_FAVORITE_TYPE eFavorType)
{
    E_MEMBER_CHANNEL_ATTRIBUTE eChAttr = E_ATTRIBUTE_IS_FAVORITE;

    switch(eFavorType)
    {
        case E_FAVORITE_TYPE_1:
            eChAttr = E_ATTRIBUTE_IS_FAVORITE1;
            break;
        case E_FAVORITE_TYPE_2:
            eChAttr = E_ATTRIBUTE_IS_FAVORITE2;
            break;
        case E_FAVORITE_TYPE_3:
            eChAttr = E_ATTRIBUTE_IS_FAVORITE3;
            break;
        case E_FAVORITE_TYPE_4:
            eChAttr = E_ATTRIBUTE_IS_FAVORITE4;
            break;

        case E_FAVORITE_TYPE_ALL:
            eChAttr = E_ATTRIBUTE_IS_FAVORITE;
            break;

        default:
            break;
    }

    return eChAttr;
}
#endif

WORD msAPI_CM_CountFavoriteProgram(MEMBER_SERVICETYPE bServiceType)
{
    WORD wProgramCount;
    WORD wFavoriteCount;
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return 0;
    }


#if( ENABLE_CHRPOC_NEW_FAVORITE_METHOD )
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
#else
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
#endif


    wFavoriteCount = 0;

    E_MEMBER_CHANNEL_ATTRIBUTE eAttrNeedToCheck = E_ATTRIBUTE_IS_FAVORITE;

#if CM_MULTI_FAVORITE//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    eAttrNeedToCheck = msAPI_CM_ConvertFavTypeToChAttr(g_DtvSys_eCurFavoriteType);
#endif

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        if( msAPI_CM_GetProgramAttribute(bServiceType, wPosition, eAttrNeedToCheck) )
        {
            wFavoriteCount++;
        }
    }

    return wFavoriteCount;
}

#if 1//( !ENABLE_CHRPOC_NEW_FAVORITE_METHOD )
//****************************************************************************
/// Get first favorite program position by listpositon
/// @param *eServiceType \b IN: Point to service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : First favorite Program position
//****************************************************************************
WORD msAPI_CM_GetFirstFavoriteProgramPositionbylistpositon(MEMBER_SERVICETYPE *eServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wPosition;
    MEMBER_SERVICETYPE  bServiceType=E_SERVICETYPE_DTV;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    E_MEMBER_CHANNEL_ATTRIBUTE eAttrNeedToCheck = E_ATTRIBUTE_IS_FAVORITE;

#if CM_MULTI_FAVORITE//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    eAttrNeedToCheck = msAPI_CM_ConvertFavTypeToChAttr(g_DtvSys_eCurFavoriteType);
#endif
    WORD i = 0;
    for(i=0; i < u16ProgramIndexTableArraySize; i++)
    {
        wPosition = msAPI_CM_GetPositionbyListPosition(i, (MEMBER_SERVICETYPE *)&bServiceType);
        *eServiceType = bServiceType;

#if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, (E_MEMBER_CHANNEL_ATTRIBUTE)(E_ATTRIBUTE_IS_FAVORITE1 + g_favorite_type)))
#else
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, eAttrNeedToCheck) )
#endif
        {
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
    }
    return INVALID_PROGRAM_POSITION;
}

//****************************************************************************
/// Get first favorite program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : First favorite Program position
//****************************************************************************
WORD msAPI_CM_GetFirstFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

#if( ENABLE_CHRPOC_NEW_FAVORITE_METHOD )
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
#else
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
#endif

    E_MEMBER_CHANNEL_ATTRIBUTE eAttrNeedToCheck = E_ATTRIBUTE_IS_FAVORITE;

#if CM_MULTI_FAVORITE//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    eAttrNeedToCheck = msAPI_CM_ConvertFavTypeToChAttr(g_DtvSys_eCurFavoriteType);
#endif

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
    #if 0//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, (E_MEMBER_CHANNEL_ATTRIBUTE)(E_ATTRIBUTE_IS_FAVORITE1 + g_favorite_type)))
    #else
        if( msAPI_CM_GetProgramAttribute(bServiceType, wPosition, eAttrNeedToCheck) )
    #endif
        {
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}

//****************************************************************************
/// Get last favorite program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : last favorite Program position
//****************************************************************************
#if 0
WORD msAPI_CM_GetLastFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wPosition = msAPI_CM_GetFirstFavoriteProgramPosition(bServiceType, bIncludeSkipped);
    return msAPI_CM_GetPrevFavoriteProgramPosition(bServiceType, wPosition, bIncludeSkipped);
}

//****************************************************************************
/// Get previous favorite program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : previous favorite Program position
//****************************************************************************
WORD msAPI_CM_GetPrevFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD i;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( FALSE == IsPositionValid(bServiceType, wBasePosition) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }

    E_MEMBER_CHANNEL_ATTRIBUTE eAttrNeedToCheck = E_ATTRIBUTE_IS_FAVORITE;

#if CM_MULTI_FAVORITE//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    eAttrNeedToCheck = msAPI_CM_ConvertFavTypeToChAttr(g_DtvSys_eCurFavoriteType);
#endif

    for(i=0; i < wProgramCount; i++)
    {
        if( wPosition > 0 )
        {
            wPosition--;
        }
        else
        {
            wPosition = wProgramCount - 1;
        }

    #if 0//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, (E_MEMBER_CHANNEL_ATTRIBUTE)(E_ATTRIBUTE_IS_FAVORITE1 + g_favorite_type)))
    #else
        if( msAPI_CM_GetProgramAttribute(bServiceType, wPosition, eAttrNeedToCheck) )
    #endif
        {
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}
#endif

//****************************************************************************
/// Get Next favorite program position by ListPosition
/// @param *eServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : Next favorite Program position
//****************************************************************************
WORD msAPI_CM_GetNextFavoriteProgramPositionbyListPosition(WORD wBasePosition, MEMBER_SERVICETYPE *eServiceType, BOOLEAN bIncludeSkipped)
{
    WORD wPosition = 0;
    MEMBER_SERVICETYPE  bServiceType=E_SERVICETYPE_DTV;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    E_MEMBER_CHANNEL_ATTRIBUTE eAttrNeedToCheck = E_ATTRIBUTE_IS_FAVORITE;

#if CM_MULTI_FAVORITE//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    eAttrNeedToCheck = msAPI_CM_ConvertFavTypeToChAttr(g_DtvSys_eCurFavoriteType);
#endif
    wBasePosition++;
    for(; wBasePosition< u16ProgramIndexTableArraySize; wBasePosition++)
    {
        wPosition = msAPI_CM_GetPositionbyListPosition(wBasePosition, (MEMBER_SERVICETYPE *)&bServiceType);
        *eServiceType = bServiceType;

#if 0 //ENABLE_S2_CHANNEL_FAV_NEWSTYLE
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, (E_MEMBER_CHANNEL_ATTRIBUTE)(E_ATTRIBUTE_IS_FAVORITE1 + g_favorite_type)))
#else
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, eAttrNeedToCheck) )
#endif
        {
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
    }
    return INVALID_PROGRAM_POSITION;
}

//****************************************************************************
/// Get Next favorite program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// -TRUE: Include skipped program
/// -FALSE: Not include
/// @return WORD : Next favorite Program position
//****************************************************************************
WORD msAPI_CM_GetNextFavoriteProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD i;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( FALSE == IsPositionValid(bServiceType, wBasePosition) )
    {
        return INVALID_PROGRAM_POSITION;
    }

#if( ENABLE_CHRPOC_NEW_FAVORITE_METHOD )
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
#else
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
#endif

    if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }

    E_MEMBER_CHANNEL_ATTRIBUTE eAttrNeedToCheck = E_ATTRIBUTE_IS_FAVORITE;

#if CM_MULTI_FAVORITE//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
    eAttrNeedToCheck = msAPI_CM_ConvertFavTypeToChAttr(g_DtvSys_eCurFavoriteType);
#endif

    for(i=0; i< wProgramCount; i++)
    {
        wPosition++;

        if( wPosition >= wProgramCount )
        {
            wPosition = 0;
        }

    #if 0//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
        if( TRUE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, (E_MEMBER_CHANNEL_ATTRIBUTE)(E_ATTRIBUTE_IS_FAVORITE1 + g_favorite_type)))
    #else
        if( msAPI_CM_GetProgramAttribute(bServiceType, wPosition, eAttrNeedToCheck) )
    #endif
        {
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_GetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
    }

    return INVALID_PROGRAM_POSITION;
}

#endif // #if( !ENABLE_CHRPOC_NEW_FAVORITE_METHOD )

//****************************************************************************
/// Get logical channel number (LCN)
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bSimuLCN \b IN: is SimuLCN or not
/// -TRUE: SimuLCN
/// -FALSE: LCN
/// @return WORD : LCN
//****************************************************************************
static WORD __msAPI_CM_GetLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSimuLCN)
{
    WORD wOrder,wLCN;

    wLCN = bSimuLCN ? INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER : INVALID_LOGICAL_CHANNEL_NUMBER;;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return wLCN;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return wLCN;
    }

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return wLCN;

    if(bSimuLCN)
    {
        wLCN = pstProgramIndexTable[wOrder].wSimu_LCN;
    }
    else
    {
        wLCN = pstProgramIndexTable[wOrder].wLCN;
    }

    return wLCN;
}

static WORD __msAPI_CM_GetOriginalLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_LOGICAL_CHANNEL_NUMBER;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_LOGICAL_CHANNEL_NUMBER;
    }


#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    WORD wLCN = 0;
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    if( FALSE == msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(
                    eCurDbSel, bServiceType, wPosition, (BYTE *)&wLCN, E_DATA_TS_LCN) )
    {
        return INVALID_LOGICAL_CHANNEL_NUMBER;
    }

    return wLCN;
#else

    WORD wOrder,wLCN = 0,wPRIndex;

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
 #if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
 #endif
    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
    GetProgramTable(wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN);

    return wLCN;
#endif
}

//****************************************************************************
// Use  __msAPI_CM_GetLogicalChannelNumber() if need
//****************************************************************************
WORD msAPI_CM_GetSimuLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    return __msAPI_CM_GetLogicalChannelNumber(bServiceType,wPosition,TRUE);
}

WORD msAPI_CM_GetOriginalLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    return __msAPI_CM_GetOriginalLogicalChannelNumber(bServiceType,wPosition);
}

//****************************************************************************
// Use  __msAPI_CM_GetLogicalChannelNumber() if need
//****************************************************************************
WORD msAPI_CM_GetLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    U16 u16LCN;

    //printf("msAPI_CM_GetLogicalChannelNumber(bServiceType=%u, wPosition=%u)\n", bServiceType, wPosition);

    u16LCN = __msAPI_CM_GetLogicalChannelNumber(bServiceType,wPosition,FALSE);

    //printf(" => u16LCN=%u\n", u16LCN, wPosition);

    return u16LCN;
}

//****************************************************************************
/// Get Logical Channel Number
/// @param wPosition \b IN: position
/// @return BYTE: Logical Channel Number
//****************************************************************************
WORD msAPI_CM_GetLogicalChannelNumberbyListPosition(WORD wPosition)
{
    WORD wOrder,wLCN;
    wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    for(wOrder=0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
    {
        if( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder].wLCN )
        {
            continue;
        }
        if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder].wPRIndex))
        {
            continue;
        }
        if(wPosition == 0) break;
        wPosition--;
    }

    if(wOrder >= u16ProgramIndexTableArraySize)
    {
        return INVALID_LOGICAL_CHANNEL_NUMBER;
    }
    else
    {
        wLCN = pstProgramIndexTable[wOrder].wLCN;
        return wLCN;
    }
}

//****************************************************************************
/// Get Physical Channel Number
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return BYTE: Physical Channel Number
//****************************************************************************
U16 msAPI_CM_GetPhysicalChannelNumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    WORD wOrder;
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    //printf("msAPI_CM_GetPhysicalChannelNumber(bServiceType=%u, wPosition=%u)\n", bServiceType, wPosition );

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    wOrder = ConvertPositionToOrder_DBSel(eCurDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        PRINT_CURRENT_LINE();
        printf("wOrder=%u >= u16ProgramIndexTableArraySize=%u!\n", wOrder,u16ProgramIndexTableArraySize);
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    return msAPI_DtvSys_Get_PCN_ByOrder(eCurDbSel, wOrder );
}

#if  ENABLE_SBTVD_DTV_SYSTEM
BYTE msAPI_CM_Get_FirstPhysicalChannelNumber(void)
{
    BYTE bMin_Num=0;
    U16 i;

    // Use new API
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    //DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    //U16 u16NetWorkIndex;


    for(i=0; i< u16IDTableArraySize && pMuxTable[i].cRFChannelNumber != INVALID_PHYSICAL_CHANNEL_NUMBER;i++)
    {
        bMin_Num = pMuxTable[i].cRFChannelNumber;
        if(pMuxTable[i].cRFChannelNumber < bMin_Num)
            bMin_Num = pMuxTable[i].cRFChannelNumber;
    }

    return bMin_Num;
}
#endif

#if ENABLE_SZ_DTV_ADDCH_SCAN_FUNCTION
//****************************************************************************
/// Is empty Physical Channel Number
/// @param bnumber \b IN: Physical Channel Number
/// @return BOOLEAN:
/// - 1: Default Not empty
/// - 0: Others
//****************************************************************************
BOOLEAN msAPI_IsEmptyPhysicalChannelNumber(BYTE u8Number)
{
    U16 i;
    // Use new API
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    //DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    //U16 u16NetWorkIndex;

    for(i=0;i<u16IDTableArraySize;i++)
    {
        if(pMuxTable[i].cRFChannelNumber==u8Number)
            return FALSE;
    }

    return TRUE;
}

//****************************************************************************
/// Get next Physical Channel Number
/// @param cRFChannelNumber \b IN: Physical Channel Number
/// @return BYTE: Physical Channel Number
//****************************************************************************
BYTE msAPI_CM_GetNextEmptyPhysicalChannelNumber(BYTE cRFChannelNumber)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize;
    BYTE i,number;
    U16 j;

    // Use new API
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    //DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    //U16 u16NetWorkIndex;

    eCountry = msAPI_CM_GetCountry();

    if( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
        return INVALID_PHYSICAL_CHANNEL_NUMBER;

        if( MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber &&
            cRFChannelNumber <= MAX_UHF_PHYSICAL_CHANNEL_NUMBER )
        {
            if( cRFChannelNumber == MAX_UHF_PHYSICAL_CHANNEL_NUMBER )
                return INVALID_PHYSICAL_CHANNEL_NUMBER;

            for(number=cRFChannelNumber+1;number<=MAX_UHF_PHYSICAL_CHANNEL_NUMBER;number++)
            {
                for(j=0;j<u16IDTableArraySize;j++)
                {
                    if(pMuxTable[j].cRFChannelNumber==number)
                        break;
                }
                if(j==u16IDTableArraySize)
             return (number);
            }

            return INVALID_PHYSICAL_CHANNEL_NUMBER;
     }
     else
     {
            cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

            for(i=0; i < cTableSize; i++)
            {
                if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
                {
                    if( (i+1) == cTableSize )
                    {
                        return MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
                    }
                }
            }

            for(i=i+1; i < cTableSize; i++)
            {
                number=pastPhysicalChannelInfoTable[i].cRFChannelNumber;
                for(j=0;j<u16IDTableArraySize;j++)
                {
                    if(pMuxTable[j].cRFChannelNumber==number)
                        break;
                }
                if(j==u16IDTableArraySize)
                {
                    return number;
                }
            }
            return MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
    }

    return INVALID_PHYSICAL_CHANNEL_NUMBER;
}
#endif

//****************************************************************************
/// Get PSI/SI Version
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param eVersionMember \b IN: PSI/SI Version member
/// -@see E_MEMBER_PSI_SI_VERSION
/// @return BYTE: PSI/SI Version
//****************************************************************************
BYTE msAPI_CM_GetPSISIVersion(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_PSI_SI_VERSION eVersionMember)
{
    WORD wOrder,wPRIndex;
    BYTE cVersion = 0;
    PROGRAMDATA_MEMBER eProgramDataMember;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PSI_SI_VERSION;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PSI_SI_VERSION;
    }

    switch( eVersionMember )
    {
    case E_VERSION_PAT:        eProgramDataMember = E_DATA_VERSION_PAT;        break;
    case E_VERSION_PMT:        eProgramDataMember = E_DATA_VERSION_PMT;        break;
    case E_VERSION_NIT:        eProgramDataMember = E_DATA_VERSION_NIT;        break;
    case E_VERSION_SDT:        eProgramDataMember = E_DATA_VERSION_SDT;        break;
    default:
        return INVALID_PSI_SI_VERSION;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16DTVProgramIndexTableArraySize )
        return INVALID_PSI_SI_VERSION;

    wPRIndex = pstDTVProgramIndexTable[wOrder].wPRIndex;

    if( TRUE != GetProgramTable(wPRIndex, &cVersion, eProgramDataMember) )
    {
        return INVALID_PSI_SI_VERSION;
    }

    if( FALSE == IsVersionValid(cVersion) )
    {
        return INVALID_PSI_SI_VERSION;
    }

    return cVersion;
}

//****************************************************************************
/// Get Program Attribute
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param eAttributeMember \b IN: Channel Attribute member
/// -@seeE_MEMBER_CHANNEL_ATTRIBUTE
/// @return BOOLEAN:
/// - 1: Default attribute is
/// - 0: Others
//****************************************************************************
U16 msAPI_CM_GetProgramAttribute_ByOrder(TypDtvDbSel eDtvDbSel, U16 u16Order, E_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember)
{
    U16 u16Ret = 0;
    BOOLEAN bIsValidParameter = TRUE;


#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
#else
    eDtvDbSel=eDtvDbSel;

    DTVPROGRAMINDEX * pstDTVProgramIndexTable = m_astDTVProgramIndexTable;
    U16 u16DTVProgramIndexTableArraySize = MAX_DTVPROGRAM;
  #if ENABLE_S2
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        pstDTVProgramIndexTable = m_astS2ProgramIndexTable;
        u16DTVProgramIndexTableArraySize = MAX_DTV_S2_PROGRAM;
    }
  #endif
#endif


    // Check Order
    if( u16Order >= u16DTVProgramIndexTableArraySize )
    {
        bIsValidParameter = FALSE;
    }


    switch(eAttributeMember)
    {
        case E_ATTRIBUTE_IS_VISIBLE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_VISIBLE_SERVICE_FLAG;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bVisibleServiceFlag;
            }
            break;

        case E_ATTRIBUTE_IS_NUMERIC_SELECTION:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_NUMERIC_SELECTION_FLAG;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bNumericSelectionFlag;
            }
            break;

        case E_ATTRIBUTE_IS_DELETED:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_DELETED;
            }
            else
            {

                u16Ret = pstDTVProgramIndexTable[u16Order].bIsDelete;
            }
            break;

        case E_ATTRIBUTE_IS_REPLACE_DEL:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_REPLACE_DEL;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsReplaceDel;
            }
            break;

    #if (CM_MULTI_FAVORITE)
        case E_ATTRIBUTE_IS_FAVORITE1:
        case E_ATTRIBUTE_IS_FAVORITE2:
        case E_ATTRIBUTE_IS_FAVORITE3:
        case E_ATTRIBUTE_IS_FAVORITE4:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_FAVORITE;
            }
            else
            {
                u16Ret = (GETBIT(pstDTVProgramIndexTable[u16Order].bIsFavorite, eAttributeMember-E_ATTRIBUTE_IS_FAVORITE1) > 0);
            }
            break;
    #endif

        case E_ATTRIBUTE_IS_FAVORITE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_FAVORITE;
            }
            else
            {

                u16Ret = pstDTVProgramIndexTable[u16Order].bIsFavorite;
            }
            break;

        case E_ATTRIBUTE_IS_SKIPPED:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_SKIPPED;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsSkipped;
            }
            break;

        case E_ATTRIBUTE_IS_LOCKED:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_LOCKED;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsLock;
            }
            break;

        case E_ATTRIBUTE_IS_SCRAMBLED:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_SCRAMBLED;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsScramble;
            }
            break;

        case E_ATTRIBUTE_IS_STILL_PICTURE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_STILL_PICTURE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsStillPicture;
            }
            break;

        case E_ATTRIBUTE_IS_REPLACE_SERVICE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_REPLACE_SERVICE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bReplaceService;
            }
            break;

        case E_ATTRIBUTE_IS_SERVICE_ID_ONLY:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_SERVICE_ID_ONLY;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsServiceIdOnly;
            }
            break;

        case E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_UNCONFIRMED_SERVICE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bUnconfirmedService;
            }
            break;

        case E_ATTRIBUTE_IS_INVALID_SERVICE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_INVALID_SERVICE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bInvalidService;
            }
            break;

        case E_ATTRIBUTE_IS_MOVED:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_MOVED;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsMove;
            }
            break;

        case E_ATTRIBUTE_IS_SPECIAL_CH:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_SPECIAL_SERVICE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsSpecialService;
            }
            break;

#if ENABLE_T_C_CHANNEL_MIX
        case E_ATTRIBUTE_IS_TERRESTRIAL:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_CABLE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsTerrestrial;
            }
            break;
#endif

        case E_ATTRIBUTE_IS_LCN_VALID:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = 0;// DEFAULT_LCN_VALID;
            }
            else
            {
                CHANNEL_ATTRIBUTE Misc;
                memset(&Misc,0,sizeof(CHANNEL_ATTRIBUTE));

                U16 u16PRIndex = pstDTVProgramIndexTable[u16Order].wPRIndex;

                GetProgramTable(u16PRIndex, (BYTE *)&Misc, E_DATA_MISC);
                u16Ret = Misc.bValidLCN;
            }
            break;

        case E_CH_ATTR_SERVICE_TYPE:
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_SERVICE_TYPE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bServiceType;
            }
            break;


#if(ASTRA_HD_ENABLE)
        case E_ATTRIBUTE_IS_NEW_SERVICE:
        {
            if( FALSE == bIsValidParameter )
            {
                u16Ret = DEFAULT_IS_NEW_SERVICE;
            }
            else
            {
                u16Ret = pstDTVProgramIndexTable[u16Order].bIsNewService;
            }
            break;
        }
#endif

        default:
            printf("\bError: %s() unsupport member=%u\n", __FUNCTION__, eAttributeMember);
            break;
    }

    return u16Ret;
}

U16 msAPI_CM_GetProgramAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    BOOLEAN bIsValidParameter;
    WORD wOrder;


    // Check parameter valid
    bIsValidParameter = TRUE;
    if( FALSE == IsServiceTypeValid(bServiceType) )
        bIsValidParameter = FALSE;
    else if( FALSE == IsPositionValid(bServiceType, wPosition) )
        bIsValidParameter = FALSE;


    if( bIsValidParameter )
        wOrder = ConvertPositionToOrder_DBSel(eCurDbSel, bServiceType, wPosition);
    else
        wOrder = INVALID_ORDER;


#if 1 // Use new method

    return msAPI_CM_GetProgramAttribute_ByOrder(eCurDbSel, wOrder, eAttributeMember);

#else

#if(ENABLE_API_DTV_SYSTEM_2015)
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = m_astDTVProgramIndexTable;
    U16 u16DTVProgramIndexTableArraySize = MAX_DTVPROGRAM;
  #if ENABLE_S2
    if( eCurDbSel == E_DTV_DB_SEL_DVBS )
    {
        pstDTVProgramIndexTable = m_astS2ProgramIndexTable;
        u16DTVProgramIndexTableArraySize = MAX_DTV_S2_PROGRAM;
    }
  #endif
#endif

    if( wOrder >= u16DTVProgramIndexTableArraySize )
    {
        printf("wOrder=%u >= u16DTVProgramIndexTableArraySize=%u\n", wOrder, u16DTVProgramIndexTableArraySize);
        bIsValidParameter = FALSE;
    }

#if 0//ENABLE_S2
    if(IsS2InUse())
    {
        switch (eAttributeMember)
        {
            case E_ATTRIBUTE_IS_VISIBLE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_VISIBLE_SERVICE_FLAG;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bVisibleServiceFlag;
                }
                break;
            case E_ATTRIBUTE_IS_NUMERIC_SELECTION:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_NUMERIC_SELECTION_FLAG;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bNumericSelectionFlag;
                }
                break;
            case E_ATTRIBUTE_IS_DELETED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_DELETED;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsDelete;
                }
                break;
            case E_ATTRIBUTE_IS_REPLACE_DEL:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_REPLACE_DEL;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsReplaceDel;
                }
                break;
        #if (CM_MULTI_FAVORITE)
            case E_ATTRIBUTE_IS_FAVORITE1:
            case E_ATTRIBUTE_IS_FAVORITE2:
            case E_ATTRIBUTE_IS_FAVORITE3:
            case E_ATTRIBUTE_IS_FAVORITE4:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_FAVORITE;
                }
                else
                {
                    bRet = (GETBIT(pstDTVProgramIndexTable[wOrder].bIsFavorite, eAttributeMember-E_ATTRIBUTE_IS_FAVORITE1) > 0);
                }
                break;
        #else
            case E_ATTRIBUTE_IS_FAVORITE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_FAVORITE;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsFavorite;
                }
                break;
        #endif
            case E_ATTRIBUTE_IS_SKIPPED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_SKIPPED;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsSkipped;
                }
                break;
            case E_ATTRIBUTE_IS_LOCKED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_LOCKED;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsLock;
                }
                break;
            case E_ATTRIBUTE_IS_SCRAMBLED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_SCRAMBLED;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsScramble;
                }
                break;
            case E_ATTRIBUTE_IS_STILL_PICTURE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_STILL_PICTURE;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsStillPicture;
                }
                break;
            case E_ATTRIBUTE_IS_SERVICE_ID_ONLY:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_SERVICE_ID_ONLY;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsServiceIdOnly;
                }
                break;
            case E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_UNCONFIRMED_SERVICE;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bUnconfirmedService;
                }
                break;
            case E_ATTRIBUTE_IS_INVALID_SERVICE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_INVALID_SERVICE;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bInvalidService;
                }
                break;
            case E_ATTRIBUTE_IS_MOVED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_MOVED;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsMove;
                }
                break;
            case E_ATTRIBUTE_IS_SPECIAL_CH:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_SPECIAL_SERVICE;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsSpecialService;
                }
                break;
        #if ENABLE_T_C_CHANNEL_MIX
            case E_ATTRIBUTE_IS_TERRESTRIAL:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_CABLE;
                }
                else
                {
                    bRet = pstDTVProgramIndexTable[wOrder].bIsTerrestrial;
                }
                break;
        #endif
            default:
                bRet = FALSE;
            break;
        }

        return bRet;
    }
#endif

    switch(eAttributeMember)
    {
    case E_ATTRIBUTE_IS_VISIBLE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_VISIBLE_SERVICE_FLAG;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bVisibleServiceFlag;
        }
        break;

    case E_ATTRIBUTE_IS_NUMERIC_SELECTION:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_NUMERIC_SELECTION_FLAG;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bNumericSelectionFlag;
        }
        break;

    case E_ATTRIBUTE_IS_DELETED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_DELETED;
        }
        else
        {

            bRet = pstDTVProgramIndexTable[wOrder].bIsDelete;
        }
        break;
    case E_ATTRIBUTE_IS_REPLACE_DEL:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_REPLACE_DEL;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsReplaceDel;
        }
        break;
#if (CM_MULTI_FAVORITE)
    case E_ATTRIBUTE_IS_FAVORITE1:
    case E_ATTRIBUTE_IS_FAVORITE2:
    case E_ATTRIBUTE_IS_FAVORITE3:
    case E_ATTRIBUTE_IS_FAVORITE4:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_FAVORITE;
        }
        else
        {
            bRet = (GETBIT(pstDTVProgramIndexTable[wOrder].bIsFavorite, eAttributeMember-E_ATTRIBUTE_IS_FAVORITE1) > 0);
        }
        break;
#else
    case E_ATTRIBUTE_IS_FAVORITE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_FAVORITE;
        }
        else
        {

            bRet = pstDTVProgramIndexTable[wOrder].bIsFavorite;
        }
        break;
#endif

    case E_ATTRIBUTE_IS_SKIPPED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_SKIPPED;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsSkipped;
        }
        break;

    case E_ATTRIBUTE_IS_LOCKED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_LOCKED;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsLock;
        }
        break;

    case E_ATTRIBUTE_IS_SCRAMBLED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_SCRAMBLED;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsScramble;
        }
        break;

    case E_ATTRIBUTE_IS_STILL_PICTURE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_STILL_PICTURE;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsStillPicture;
        }
        break;

    case E_ATTRIBUTE_IS_REPLACE_SERVICE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_REPLACE_SERVICE;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bReplaceService;
        }
        break;

    case E_ATTRIBUTE_IS_SERVICE_ID_ONLY:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_SERVICE_ID_ONLY;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsServiceIdOnly;
        }
        break;
    case E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_UNCONFIRMED_SERVICE;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bUnconfirmedService;
        }
        break;
    case E_ATTRIBUTE_IS_INVALID_SERVICE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_INVALID_SERVICE;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bInvalidService;
        }
        break;
    case E_ATTRIBUTE_IS_MOVED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_MOVED;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsMove;
        }
        break;
    case E_ATTRIBUTE_IS_SPECIAL_CH:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_SPECIAL_SERVICE;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsSpecialService;
        }
        break;

#if ENABLE_T_C_CHANNEL_MIX
    case E_ATTRIBUTE_IS_TERRESTRIAL:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_CABLE;
        }
        else
        {
            bRet = pstDTVProgramIndexTable[wOrder].bIsTerrestrial;
        }
        break;
#endif

    case E_ATTRIBUTE_IS_LCN_VALID:
        {
            CHANNEL_ATTRIBUTE Misc;
            memset(&Misc,0,sizeof(CHANNEL_ATTRIBUTE));
            GetProgramTable(wOrder, (BYTE *)&Misc, E_DATA_MISC);
            bRet = Misc.bValidLCN;
        }
        break;

    default:
        bRet = FALSE;
        break;
    }

    return bRet;

#endif
}

#if(ENABLE_S2_FAST_SCAN)
BYTE msAPI_CM_GetScanType(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    WORD wOrder;
    BYTE bRet;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);


#if ENABLE_S2
    if (IsS2InUse())
        bRet = pstDTVProgramIndexTable[wOrder].bIsFastScan;
    else
#endif
        bRet = FALSE;//m_astDTVProgramIndexTable[wOrder].bIsFastScan;

    return bRet;
}
#endif

//****************************************************************************
/// Get Program Video type
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return VIDEO_TYPE:
/// -@see VIDEO_TYPE
//****************************************************************************
VIDEO_TYPE msAPI_CM_GetProgramVideoType(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    BOOLEAN bIsValidParameter;
    WORD wOrder;
    VIDEO_TYPE bRet;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif


    bIsValidParameter = TRUE;
    bIsValidParameter &= IsServiceTypeValid(bServiceType);
    bIsValidParameter &= IsPositionValid(bServiceType, wPosition);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

    if( FALSE == bIsValidParameter )
    {
        bRet = DEFAULT_VIDEO_TYPE;
    }
    else
    {
    #if 0//ENABLE_S2
        if (IsS2InUse())
            bRet = (VIDEO_TYPE)m_astS2ProgramIndexTable[wOrder].eVideoType;
        else
    #endif
            bRet = (VIDEO_TYPE)pstProgramIndexTable[wOrder].eVideoType;
    }

    return bRet;
}
//****************************************************************************
/// Get Pmt PID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: Pmt PID
//****************************************************************************
WORD msAPI_CM_GetPmtPID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1//( ENABLE_API_DTV_SYSTEM_2015 )
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    U16 u16Pmt_PID = INVALID_PID;

    if( FALSE == msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (U8*)&u16Pmt_PID, E_DATA_PMT_PID) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPMT_PIDValid(u16Pmt_PID) )
    {
        return INVALID_PID;
    }

    return u16Pmt_PID;

#else

    WORD wOrder;
    WORD wPmt_PID = 0,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PID;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);


#if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;


    if( TRUE != GetProgramTable(wPRIndex, (BYTE *)&wPmt_PID, E_DATA_PMT_PID) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPMT_PIDValid(wPmt_PID) )
    {
        return INVALID_PID;
    }

    return wPmt_PID;
#endif
}

//****************************************************************************
/// Get PCR PID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: PCR PID
//****************************************************************************
WORD msAPI_CM_GetPCR_PID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1//( ENABLE_API_DTV_SYSTEM_2015 )
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    U16 u16PCR_PID = INVALID_PID;

    if( FALSE == msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (U8*)&u16PCR_PID, E_DATA_PCR_PID) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPCR_PIDValid(u16PCR_PID) )
    {
        return INVALID_PID;
    }

    return u16PCR_PID;

#else

    WORD wOrder;
    WORD wPCR_PID = 0,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PID;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    if( TRUE != GetProgramTable(wPRIndex, (BYTE *)&wPCR_PID, E_DATA_PCR_PID) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPCR_PIDValid(wPCR_PID) )
    {
        return INVALID_PID;
    }

    return wPCR_PID;
#endif
}

//****************************************************************************
/// Get Video PID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: Video PID
//****************************************************************************
WORD msAPI_CM_GetVideoPID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1//( ENABLE_API_DTV_SYSTEM_2015 )
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    U16 u16Video_PID = INVALID_PID;

    if( FALSE == msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (U8*)&u16Video_PID, E_DATA_VIDEO_PID) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsVideoPIDValid(u16Video_PID) )
    {
        return INVALID_PID;
    }

    return u16Video_PID;

#else

    WORD wOrder;
    WORD wVideo_PID = 0,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PID;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    if( TRUE != GetProgramTable(wPRIndex, (BYTE *)&wVideo_PID, E_DATA_VIDEO_PID) )
    {
        return INVALID_PID;
    }

    if( FALSE == IsVideoPIDValid(wVideo_PID) )
    {
        return INVALID_PID;
    }
    return wVideo_PID;
#endif
}

//****************************************************************************
/// Get Service ID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: Service ID
//****************************************************************************
WORD msAPI_CM_GetService_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    WORD wOrder, wService_ID;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_SERVICE_ID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_SERVICE_ID;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel) )
    {
        return INVALID_SERVICE_ID;
    }

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    wService_ID = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel)[wOrder].wService_ID;
#else
 #if ENABLE_S2
    if (IsS2InUse())
        wService_ID = m_astS2ProgramIndexTable[wOrder].wService_ID;
    else
 #endif
        wService_ID = m_astDTVProgramIndexTable[wOrder].wService_ID;
#endif

    if( FALSE == IsService_IDValid(wService_ID) )
    {
        return INVALID_SERVICE_ID;
    }

    return wService_ID;
}

//****************************************************************************
/// Get TS ID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: TS ID
//****************************************************************************
WORD msAPI_CM_GetTS_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16TS_ID = INVALID_TS_ID;

    if( FALSE == msAPI_DtvSys_Get_IDTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (U8*)&u16TS_ID, E_DATA_TS_ID) )
    {
        return INVALID_TS_ID;
    }

    if( FALSE == IsTS_IDValid(u16TS_ID) )
    {
        return INVALID_TS_ID;
    }

    return u16TS_ID;

#else

    WORD wOrder;
    U16 u16IDIndex;

    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())  pMuxTable=_astDTVCProgramIDTable;
  #endif
  #if ENABLE_S2
    if (IsS2InUse())    pMuxTable=_astS2ProgramIDTable;
  #endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_TS_ID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_TS_ID;
    }

    //wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    wOrder = ConvertPositionToOrder_DBSel(eCurDbSel, bServiceType, wPosition);

  #if ENABLE_S2
    if (IsS2InUse())
    {
        u16IDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
        if (FALSE == IsTS_IDValid(_astS2ProgramIDTable[u16IDIndex].wTransportStream_ID))
        {
            return INVALID_TS_ID;
        }
        return _astS2ProgramIDTable[u16IDIndex].wTransportStream_ID;
    }
  #endif
    u16IDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;

    if( FALSE == IsTS_IDValid(pMuxTable[u16IDIndex].wTransportStream_ID) )
    {
        return INVALID_TS_ID;
    }

    return pMuxTable[u16IDIndex].wTransportStream_ID;
#endif

}

//****************************************************************************
/// Get ON ID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: ON ID
//****************************************************************************
WORD msAPI_CM_GetON_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1//( ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 wOriginalNetwork_ID = INVALID_ON_ID;

    if( FALSE == msAPI_DtvSys_Get_IDTable_ByServiceAndPos(CUR_DB_SEL(), bServiceType, wPosition, (U8*)&wOriginalNetwork_ID, E_DATA_ON_ID) )
    {
        return INVALID_ON_ID;
    }
    if( FALSE == IsON_IDValid(wOriginalNetwork_ID) )
    {
        return INVALID_ON_ID;
    }

    return wOriginalNetwork_ID;

#else

    WORD wOrder;
#if ENABLE_S2_WORD
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_ON_ID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_ON_ID;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
#if ENABLE_S2
    if (IsS2InUse())
    {
        cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
        if (FALSE == IsON_IDValid(_astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID))
        {
            return INVALID_ON_ID;
        }
        return _astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID;
    }
#endif
    cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;

    if( FALSE == IsON_IDValid(pMuxTable[cIDIndex].wOriginalNetwork_ID) )
    {
        return INVALID_ON_ID;
    }

    return pMuxTable[cIDIndex].wOriginalNetwork_ID;
#endif
}

//****************************************************************************
/// Get Network ID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: Network ID
//****************************************************************************
WORD msAPI_CM_GetNetwork_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    U8 u8NetWorkIndex = 0;
    U16 u16Network_ID = INVALID_NID;

    //PRINT_CURRENT_LINE();

    // Get NetWork index (of NwtWork table) from ID Table
    if( FALSE == msAPI_DtvSys_Get_IDTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (U8*)&u8NetWorkIndex, E_DATA_NETWORK_INDEX) )
    {
        return INVALID_NID;
    }

    // Get NetWork ID from NetWork Table
    if( FALSE == GetIDTable_DBSel(eCurDbSel, u8NetWorkIndex, (U8*)&u16Network_ID, E_DATA_NETWORK_ID ) )
    {
        return INVALID_NID;
    }

    if( FALSE == IsON_IDValid(u16Network_ID) )
    {
        return INVALID_NID;
    }

    return u16Network_ID;
#else

    WORD wOrder;
#if ENABLE_S2_WORD
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_NID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_NID;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
#if ENABLE_S2
    if (IsS2InUse())
    {
        cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
        if (FALSE == IsON_IDValid(_astS2Network[_astDTVProgramIDTable[cIDIndex].cNetWorkIndex].wNetwork_ID))
        {
            return INVALID_NID;
        }
        return _astDTVNetwork[_astS2ProgramIDTable[cIDIndex].cNetWorkIndex].wNetwork_ID;
    }
#endif
    cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;

    if( FALSE == IsON_IDValid(_astDTVNetwork[pMuxTable[cIDIndex].cNetWorkIndex].wNetwork_ID) )
    {
        return INVALID_NID;
    }

    return _astDTVNetwork[pMuxTable[cIDIndex].cNetWorkIndex].wNetwork_ID;
#endif
}

//****************************************************************************
/// Get Cell ID Infomation
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *pwCellID \b IN: pointer to cell ID information for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetCellIDByPosition(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD *pwCellID)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16CellID = 0;

    if( FALSE == msAPI_DtvSys_Get_IDTable_ByServiceAndPos(CUR_DB_SEL(), bServiceType, wPosition, (U8*)&u16CellID, E_DATA_CELL_ID) )
    {
        return FALSE;
    }

    *pwCellID = u16CellID;

    return TRUE;

#else

    WORD wOrder;
#if ENABLE_S2_WORD
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }
    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
#if ENABLE_S2
    if (IsS2InUse())
    {
        cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
        *pwCellID=_astS2ProgramIDTable[cIDIndex].wCellID;
        return TRUE;
    }
#endif
    cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
    *pwCellID=pMuxTable[cIDIndex].wCellID;
    return TRUE;
#endif
}

//****************************************************************************
/// Get plp ID Infomation via TSID and ONID
/// @param wTS_ID \b IN: transport stream ID
/// @param wON_ID \b IN: original network ID
/// @param *pu8PLP_ID \b IN: pointer to plp ID information for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetPLPID_WithID(WORD wTS_ID, WORD wON_ID, U8* pu8PLP_ID)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16IDIndex = msAPI_DtvSys_Find_IDTab_By_TSId_ONId( CUR_DB_SEL(), wTS_ID, wON_ID);

    if( u16IDIndex == INVALID_IDINDEX )
        return FALSE;

    U8 u8PLPID = INVALID_PLPID;

    if( FALSE == GetIDTable_DBSel(CUR_DB_SEL(), u16IDIndex, (U8*)&u8PLPID, E_DATA_PLP) )
    {
        u8PLPID = INVALID_PLPID;
    }

    *pu8PLP_ID = u8PLPID;
    return TRUE;

#else

#if ENABLE_S2_WORD
    WORD i;
#else
    int i;
#endif
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if ENABLE_S2
    if(IsS2InUse())
    {
        for (i=0;i<MAX_DTV_S2_MUX_NUMBER;i++)
        {
            if ((_astS2ProgramIDTable[i].wTransportStream_ID == wTS_ID) && (_astS2ProgramIDTable[i].wOriginalNetwork_ID == wON_ID))
            {
                *pu8PLP_ID=_astS2ProgramIDTable[i].cPLPID;
                return TRUE;
            }
        }
        return FALSE;
    }
#endif
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif
    for(i=0;i<msAPI_CM_GetMuxMaxNumber();i++)
    {
        if((pMuxTable[i].wTransportStream_ID  == wTS_ID)
            && (pMuxTable[i].wOriginalNetwork_ID== wON_ID))
        {
            *pu8PLP_ID=pMuxTable[i].cPLPID;
            return TRUE;
        }
    }
    return FALSE;

#endif
}
//****************************************************************************
/// Get HpLP Infomation via TSID and ONID
/// @param wTS_ID \b IN: transport stream ID
/// @param wON_ID \b IN: original network ID
/// @param *pu8HpLP \b IN: pointer to HpLp information for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetHpLP_WithID(WORD wTS_ID, WORD wON_ID, U8* pu8HpLp)
{
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    U16 u16IDIndex = msAPI_DtvSys_Find_IDTab_By_TSId_ONId( eCurDbSel, wTS_ID, wON_ID);

    if( u16IDIndex == INVALID_IDINDEX )
        return FALSE;

#if 1

    DTVPROGRAMID_M *pstProgIdTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    *pu8HpLp = pstProgIdTable[u16IDIndex].cHpLp;

#else

    U8 u8HpLp = 0;

    if( FALSE == GetIDTable_DBSel(CUR_DB_SEL(), u16IDIndex, &u8HpLp, E_PRDATA_HPLP) )
    {
        return FALSE;
    }
    *pu8HpLp = u8HpLp;

#endif

    return TRUE;
}

//****************************************************************************
/// Get PLP ID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return WORD: PLP ID
//****************************************************************************
WORD msAPI_CM_GetPLP_ID(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1 // Use new method
    U8 u8PLPID = INVALID_PLPID;

    if( FALSE == msAPI_DtvSys_Get_IDTable_ByServiceAndPos(CUR_DB_SEL(), bServiceType, wPosition, &u8PLPID, E_DATA_PLP) )
    {
        u8PLPID = INVALID_PLPID;
    }

    return u8PLPID;

#else
    WORD wOrder;
#if ENABLE_S2_WORD
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PLPID;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PLPID;
    }

#if ENABLE_S2
    if (IsS2InUse())
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
        return _astS2ProgramIDTable[cIDIndex].cPLPID;
    }
#endif
    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;

    return pMuxTable[cIDIndex].cPLPID;
#endif
}

//****************************************************************************
/// Get HP/LP
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return BYTE: HP/LP 0=>HP, 1=>LP
//****************************************************************************
BYTE msAPI_CM_GetHpLp(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();

    U16 u16IDIndex = msAPI_DtvSys_Get_IDTabIndex_ByServiceAndPos( eCurDbSel, bServiceType, wPosition);

    if( u16IDIndex >= msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel) )
        return 0;

    U8 u8HpLp = 0;

    DTVPROGRAMID_M *pstProgIdTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);

    u8HpLp = pstProgIdTable[u16IDIndex].cHpLp;

    return u8HpLp;
}

BOOL msAPI_CM_Is_AudioStreamTypeValid(SI_AUDIOSTREAM_TYPE eSIAutioStreamType)
{
    switch( eSIAutioStreamType )
    {
        case E_SI_AUDIOSTREAM_MPEG:
        case E_SI_AUDIOSTREAM_AC3:
        case E_SI_AUDIOSTREAM_MPEG4:
        case E_SI_AUDIOSTREAM_AAC:
        case E_SI_AUDIOSTREAM_AC3P:
        case E_SI_AUDIOSTREAM_DRA:
            return TRUE;

        default:
            return FALSE;
    }

    return FALSE;
}

//****************************************************************************
/// Get Audio stream count
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return BYTE: Audio stream count
//****************************************************************************
BYTE msAPI_CM_GetAudioStreamCount(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];
    BYTE i;
    BYTE cAudioStreamCount;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return 0;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return 0;
    }

    memset(&stAudInfo,0,sizeof(stAudInfo));

#if 1 // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);

#else
    WORD wOrder, wPRIndex;

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

  #if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
  #endif
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
    GetProgramTable(wPRIndex, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);
#endif

    cAudioStreamCount = 0;
    for(i=0; i < MAX_AUD_LANG_NUM; i++)
    {
        if( (TRUE == IsAudioPIDValid(stAudInfo[i].wAudPID)) &&
            (GETBIT(_u16ValidAudioIndex,i)) &&
            (msAPI_CM_Is_AudioStreamTypeValid(stAudInfo[i].eSIAudType))
          )
        {
            cAudioStreamCount++;
//            printf("stAudInfo[%u].wAudPID=%u wAudType=%u \n",i,stAudInfo[i].wAudPID,stAudInfo[i].wAudType);
        }
        else
        {
            break;
        }
    }

    return cAudioStreamCount;
}

//****************************************************************************
/// Get Audio Stream Infomation
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *pstAudioStreamInfo \b IN: pointer to Audio stream information for return
/// -@see AUD_INFO
/// @param cOrdinal \b IN: Ordinal
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetAudioStreamInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition, AUD_INFO * pstAudioStreamInfo, BYTE cOrdinal)
{
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];


    memset(&stAudInfo, 0, sizeof(stAudInfo));

    FillAudioStreamInfoWithDefault(pstAudioStreamInfo);

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    if( MAX_AUD_LANG_NUM <= cOrdinal)
    {
        return FALSE;
    }

#if 1 // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);

#else
    WORD wOrder,wPRIndex;

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

  #if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
  #endif
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);
#endif

    if( (TRUE == IsAudioPIDValid(stAudInfo[cOrdinal].wAudPID)) &&
        (GETBIT(_u16ValidAudioIndex,cOrdinal)) &&
        (msAPI_CM_Is_AudioStreamTypeValid(stAudInfo[cOrdinal].eSIAudType))
      )
    {
        *pstAudioStreamInfo = stAudInfo[cOrdinal];

        return TRUE;
    }

    return FALSE;
}


//****************************************************************************
/// Get Program Infomation
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *pChannelInfo \b IN: pointer to Audio program information for return
/// -@see DTV_CHANNEL_INFO
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetProgramInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition,DTV_CHANNEL_INFO *pChannelInfo)
{
#if 1 // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    return msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (BYTE *)pChannelInfo, E_DATA_ALL);

#else

    WORD wOrder;
    WORD wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    if( TRUE != GetProgramTable(wPRIndex, (BYTE *)pChannelInfo, E_DATA_ALL) )
    {
        return FALSE;
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Arrange Audio Stream Infomation
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param stValidAudioInfo \b IN: pointer to Valid Audio Information
/// -@see AUD_VALID_INFO
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_ArrangeAudioStreamInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition, U16 cValidAudIndex)
{
    AUD_INFO stAudInfoNew[MAX_AUD_LANG_NUM],stAudInfo[MAX_AUD_LANG_NUM];
    WORD wOrder,wPRIndex;
    BYTE bAudioNum,i,bValidIndex,bInvalidIndex;
    BOOLEAN result = FALSE;

    memset(&stAudInfo,0,sizeof(stAudInfo));
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;


    GetProgramTable(wPRIndex, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);

    bAudioNum = 0;
    for(i=0; i < MAX_AUD_LANG_NUM; i++)
    {
        if( (TRUE == IsAudioPIDValid(stAudInfo[i].wAudPID))
          && (msAPI_CM_Is_AudioStreamTypeValid(stAudInfo[i].eSIAudType))
          )
        {
            bAudioNum++;
        }
        else
        {
            break;
        }
    }
    if(bAudioNum ==0)
    {
        return FALSE;
    }
    _u16ValidAudioIndex=0;
    bValidIndex=0;
    bInvalidIndex=bAudioNum-1;
    memset(stAudInfoNew,0,sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);
    for(i=0; i < bAudioNum; i++)
    {
        if( (TRUE == IsAudioPIDValid(stAudInfo[i].wAudPID)) &&
            (GETBIT(cValidAudIndex,i))  &&
            (msAPI_CM_Is_AudioStreamTypeValid(stAudInfo[i].eSIAudType))
          )
        {
            stAudInfoNew[bValidIndex]=stAudInfo[i];
            SETBIT(_u16ValidAudioIndex,bValidIndex);
            bValidIndex++;
        }
        else
        {
            stAudInfoNew[bInvalidIndex]=stAudInfo[i];
            CLRBIT(_u16ValidAudioIndex,bInvalidIndex);
            bInvalidIndex--;
        }
    }
    _bSaveDataToFlash=FALSE;
    if(memcmp(&stAudInfo,&stAudInfoNew,sizeof(AUD_INFO)))
    {
        result = SetProgramTable(wPRIndex, (BYTE*)stAudInfoNew, E_DATA_AUDIO_STREAM_INFO);
    }
    _bSaveDataToFlash=TRUE;
    return result;
    //return SetProgramTable(wPRIndex, (BYTE*)stAudInfoNew, E_DATA_AUDIO_STREAM_INFO);
}

//****************************************************************************
/// Get Next Audio Stream ordinal
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param cBaseOrdinal \b IN: Base Ordinal
/// @return BYTE: Next Audio stream ordinal
//****************************************************************************
BYTE msAPI_CM_GetNextAudioStreamOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE cBaseOrdinal)
{
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];
    BYTE i;
    BYTE cOrdinal;
    BYTE cAudioStreamCount;

    memset(&stAudInfo,0,sizeof(stAudInfo));
    if( MAX_AUD_LANG_NUM <= cBaseOrdinal)
    {
        return DEFAULT_SELECTED_AUDIO_STREAM;
    }

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return cBaseOrdinal;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return cBaseOrdinal;
    }

#if 1 // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);
#else
    WORD wOrder,wPRIndex;

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
  #if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
  #endif
    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
    GetProgramTable(wPRIndex, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);
#endif


    cOrdinal = cBaseOrdinal;
    cAudioStreamCount = msAPI_CM_GetAudioStreamCount(bServiceType, wPosition);

    for(i=0; i < cAudioStreamCount; i++)
    {
        cOrdinal++;
        if( cOrdinal >= cAudioStreamCount || cOrdinal >= MAX_AUD_LANG_NUM)
        {
            cOrdinal = 0;
        }

        if( (TRUE == IsAudioPIDValid(stAudInfo[cOrdinal].wAudPID)) &&
            (GETBIT(_u16ValidAudioIndex,cOrdinal)) &&
            (msAPI_CM_Is_AudioStreamTypeValid(stAudInfo[cOrdinal].eSIAudType))
          )
        {
            return cOrdinal;
        }
    }

    return cBaseOrdinal;
}

//****************************************************************************
/// Get Previous Audio Stream ordinal
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param cBaseOrdinal \b IN: Base Ordinal
/// @return BYTE: Previous Audio stream ordinal
//****************************************************************************
BYTE msAPI_CM_GetPrevAudioStreamOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE cBaseOrdinal)
{
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];

    BYTE i;
    BYTE cOrdinal;
    BYTE cAudioStreamCount;

    memset(&stAudInfo,0,sizeof(stAudInfo));

    if( MAX_AUD_LANG_NUM <= cBaseOrdinal)
    {
        return DEFAULT_SELECTED_AUDIO_STREAM;
    }

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return cBaseOrdinal;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return cBaseOrdinal;
    }


#if 1 // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);
#else
    WORD wPRIndex;
    WORD wOrder;

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

  #if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
  #endif
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO);
#endif

    cOrdinal = cBaseOrdinal;
    cAudioStreamCount = msAPI_CM_GetAudioStreamCount(bServiceType, wPosition);

    for(i=0; i < cAudioStreamCount; i++)
    {
        if( cOrdinal > 0 )
        {
            cOrdinal--;
        }
        else
        {
            cOrdinal = cAudioStreamCount-1;
        }

        if( (TRUE == IsAudioPIDValid(stAudInfo[cOrdinal].wAudPID))
          &&(msAPI_CM_Is_AudioStreamTypeValid(stAudInfo[cOrdinal].eSIAudType))
          )
        {
            return cOrdinal;
        }
    }

    return cBaseOrdinal;
}

//****************************************************************************
/// Get Service name
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *bChannelName \b IN: pointer to Channel name for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetServiceName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    WORD wPRIndex;

#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    BOOLEAN bRet = FALSE;
    BYTE aLang[MAX_MULTI_LINGUAL_SERVICE_NAME] = {0};
    BYTE aName[MAX_MULTI_LINGUAL_SERVICE_NAME][MAX_SERVICE_NAME];
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

#if 1 // Use new method
    wPRIndex = msAPI_DtvSys_Get_ProgTabIndex_ByServiceAndPos(eCurDbSel, bServiceType, wPosition);
#else
    WORD wOrder = ConvertPositionToOrder_DBSel(eCurDbSel, bServiceType, wPosition);

  #if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
  #endif
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
#endif

    // Check PRIndex valid
    if( FALSE == msAPI_DtvDB_Is_ProgTableIndexValid(eCurDbSel, wPRIndex) )
    {
        return FALSE;
    }


  #if 1
    memset(bChannelName, 0, sizeof(BYTE)*MAX_SERVICE_NAME);
  #else
    for(i=0; i < MAX_SERVICE_NAME; i++)
    {
        bChannelName[i] = NULL;
    }
  #endif


#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    BYTE i;
    memset(aLang, 0, sizeof(BYTE)*MAX_MULTI_LINGUAL_SERVICE_NAME);
    GetProgramTable(wPRIndex, (BYTE *)aLang, E_DATA_NAME_MULTILINGUAL_LANGUAGE);
    GetProgramTable(wPRIndex, (BYTE *)aName, E_DATA_SERVICE_MULTILINGUAL_NAME);
    for(i=0;i<MAX_MULTI_LINGUAL_SERVICE_NAME;i++)
    {
        if(aLang[i]==(U8)GET_OSD_MENU_LANGUAGE())
        {
            memcpy(bChannelName,aName[i],MAX_SERVICE_NAME);
            //printf("index =%x lang %x name %s %x %x %x %x %x\n",i,aLang[i],
            //  aName[i],aName[i][0],aName[i][1],aName[i][2],aName[i][3],aName[i][4]);
            bRet =  TRUE;
        }
    }
    if((bRet==TRUE)&&(bChannelName[0]!=NULL))  //get service name  //check if service name is empty or not
    {
        return bRet;
    }
#endif

    return GetProgramTable(wPRIndex, (BYTE *)bChannelName, E_DATA_SERVICE_NAME);
}

#if ENABLE_S2_PREDIT_RENAME
BOOLEAN msAPI_CM_SetServiceName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName)
{
#if 1 // Use new method

    return msAPI_DtvSys_Set_ProgramTable_ByServiceAndPos(CUR_DB_SEL(),
            bServiceType, wPosition,
            (BYTE *)bChannelName, E_DATA_SERVICE_NAME);

#else

    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }
    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

    wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;

    return SetProgramTable(wPRIndex, (BYTE *)bChannelName, E_DATA_SERVICE_NAME);
#endif
}
#endif

//****************************************************************************
/// Delete program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param fIsDelete \b IN: delete or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_DeleteProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,MS_U8 fIsDelete)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wFromOrder,wPRIndex;
    WORD wToOrder;
    WORD wDeletedPosition;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    /* For complier happy */
    fIsDelete = fIsDelete;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    // Why only DVBS need this?
#if ENABLE_S2
    if (IsS2InUse())
    {
        RemoveProgram(bServiceType, wPosition);
        return TRUE;
    }
#endif

    wDeletedPosition = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL) - 1;

    wFromOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        wToOrder = u16ProgramIndexTableArraySize -1;
    }
    else
    {
        wToOrder = ConvertPositionToOrder(bServiceType, wDeletedPosition);
    }
    MoveProgram(wFromOrder, wToOrder);

//#if (ENABLE_DTV_EPG)
    //MApp_Epg_MoveSrvBuffer(wFromOrder, wToOrder);
//#endif  //#if (ENABLE_DTV_EPG)
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        UpdateOrderOfProgramTable(E_SERVICETYPE_DATA);
        UpdateOrderOfProgramTable(E_SERVICETYPE_DTV);
        UpdateOrderOfProgramTable(E_SERVICETYPE_RADIO);
    }
    else
    {
        UpdateOrderOfProgramTable(bServiceType);
    }

#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wToOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wToOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    stCHAttribute.bIsDelete = TRUE;

#if 0//ENABLE_S2
    if (IsS2InUse())
        m_astS2ProgramIndexTable[wToOrder].bIsDelete = stCHAttribute.bIsDelete;
    else
#endif
        pstProgramIndexTable[wToOrder].bIsDelete = stCHAttribute.bIsDelete;

    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
    {
        return FALSE;
    }

    UpdateProgramCount(bServiceType);

    return TRUE;
}

//****************************************************************************
/// This function will set Replace Del
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bDel \b IN: it's a Replace Del program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_ReplaceDelProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bDel)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

    if( bDel == TRUE )
    {
        stCHAttribute.bIsReplaceDel = TRUE;
    }
    else
    {
        stCHAttribute.bIsReplaceDel = FALSE;
    }

#if 0//ENABLE_S2
    if (IsS2InUse())
        m_astS2ProgramIndexTable[wOrder].bIsReplaceDel = stCHAttribute.bIsReplaceDel;
    else
#endif
        pstProgramIndexTable[wOrder].bIsReplaceDel = stCHAttribute.bIsReplaceDel;

    UpdateProgramCount(bServiceType);

    return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
}

//****************************************************************************
/// This function will Recovery Del program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_RecoveryDelProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wPRIndex;
    WORD wRecoveryPosition;
    U16 u16Service_ID,u16TS_ID,u16ON_ID,u16CurPosition;
    MEMBER_SERVICETYPE bCurServiceType;

    bCurServiceType = msAPI_CM_GetCurrentServiceType();
    u16CurPosition = msAPI_CM_GetCurrentPosition(bCurServiceType);
    u16Service_ID = msAPI_CM_GetService_ID(bCurServiceType,u16CurPosition);
    u16ON_ID = msAPI_CM_GetON_ID(bCurServiceType,u16CurPosition);
    u16TS_ID = msAPI_CM_GetTS_ID(bCurServiceType,u16CurPosition);

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wRecoveryPosition = ConvertPositionToOrder(bServiceType, wPosition);
    if( wRecoveryPosition >= u16ProgramIndexTableArraySize )
        return FALSE;


#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wRecoveryPosition].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wRecoveryPosition].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

    stCHAttribute.bIsDelete = FALSE;

#if 0//ENABLE_S2
    if (IsS2InUse())
        m_astS2ProgramIndexTable[wRecoveryPosition].bIsDelete = stCHAttribute.bIsDelete;
    else
#endif
        pstProgramIndexTable[wRecoveryPosition].bIsDelete = stCHAttribute.bIsDelete;

    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
    {
        return FALSE;
    }

    UpdateProgramCount(bServiceType);

    msAPI_CM_ArrangeDataManager(TRUE,FALSE);

    return TRUE;
}

//****************************************************************************
/// This function will set service ID only program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param IsServiceIdOnly \b IN: it's a service ID only program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_ServiceIDOnlyProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,MS_U8 IsServiceIdOnly)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//ENABLE_S2
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
        m_astS2ProgramIndexTable[wOrder].bIsServiceIdOnly = IsServiceIdOnly;
    }
    else
    {
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
        m_astDTVProgramIndexTable[wOrder].bIsServiceIdOnly = IsServiceIdOnly;
    }
#else
    wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    pstProgramIndexTable[wOrder].bIsServiceIdOnly = IsServiceIdOnly;
#endif

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    stCHAttribute.bIsServiceIdOnly = IsServiceIdOnly;

    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
    {
        return FALSE;
    }

    return TRUE;
}

//****************************************************************************
/// This function will set scramble program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param IsScramble \b IN: it's a scramble program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_ScrambleProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition,MS_U8 IsScramble)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    stCHAttribute.bIsScramble = IsScramble;

#if 0//ENABLE_S2
    if (IsS2InUse())
        m_astS2ProgramIndexTable[wOrder].bIsScramble = stCHAttribute.bIsScramble;
    else
#endif
        pstProgramIndexTable[wOrder].bIsScramble = stCHAttribute.bIsScramble;

    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
    {
        return FALSE;
    }

    return TRUE;
}

//****************************************************************************
/// This function will set Video Type
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param u8VideoType \b IN: video type
/// -@see VIDEO_TYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_SetProgramVideoType(MEMBER_SERVICETYPE bServiceType, WORD wPosition,U8 u8VideoType)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

#if 0//ENABLE_S2
    if (IsS2InUse())
        m_astS2ProgramIndexTable[wOrder].eVideoType=stCHAttribute.eVideoType = u8VideoType;
    else
#endif
        pstProgramIndexTable[wOrder].eVideoType=stCHAttribute.eVideoType = u8VideoType;

    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
    {
        return FALSE;
    }

    return TRUE;
}

#if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
BOOLEAN msAPI_CM_GetFavChannelInfo(MEMBER_SERVICETYPE bServiceType, WORD wPosition,BYTE *pChannelFavInfo)
{
    if (FALSE == IsServiceTypeValid(bServiceType))
    {
        return FALSE;
    }
    if (FALSE == IsPositionValid(bServiceType, wPosition))
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();

    return msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(eDtvDbSel, bServiceType, wPosition, (BYTE *)pChannelFavInfo, E_DATA_ID_FAV)

/*
    WORD wOrder;
    WORD wPRIndex;

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    if (TRUE != GetProgramTable(wPRIndex, (BYTE *)pChannelFavInfo, E_DATA_ID_FAV))
    {
        return FALSE;
    }

    return TRUE;
*/
}
#endif

#if 0//(CM_MULTI_FAVORITE)
//****************************************************************************
/// This function will set Favorite program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bFavorite \b IN: it's a favorite program or not
/// @param eFavorType \b IN: set eFavorite Type
/// -@see E_FAVORITE_TYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_FavorProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bFavorite, E_FAVORITE_TYPE eFavorType)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

    if( bFavorite == TRUE )
    {
        if (eFavorType == E_FAVORITE_TYPE_ALL)
        {
            stCHAttribute.bIsFavorite |= BITMASK(E_FAVORITE_TYPE_4:E_FAVORITE_TYPE_1);
        }
        else
        {
            SETBIT(stCHAttribute.bIsFavorite, eFavorType);
        }
    }
    else
    {
        if (eFavorType == E_FAVORITE_TYPE_ALL)
        {
            stCHAttribute.bIsFavorite &= ~BITMASK(E_FAVORITE_TYPE_4:E_FAVORITE_TYPE_1);
        }
        else
        {
            CLRBIT(stCHAttribute.bIsFavorite, eFavorType);
        }
    }

#if 0//(ENABLE_S2)
    if(IsS2InUse())
        m_astS2ProgramIndexTable[wOrder].bIsFavorite = stCHAttribute&0x0F;
    else
#endif
        pstProgramIndexTable[wOrder].bIsFavorite = stCHAttribute&0x0F;

//    printf("After Set Fav Prog, m_astDTVProgramIndexTable[%d].bIsFavorite= 0x%x..\n", wOrder, m_astS2ProgramIndexTable[wOrder].bIsFavorite);
    return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_ID_FAV);
}

#else
//****************************************************************************
/// This function will set Favorite program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bFavorite \b IN: it's a favorite program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_FavorProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bFavorite)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


    wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

#if(CM_MULTI_FAVORITE)
    if( bFavorite == TRUE )
    {
        if (g_DtvSys_eCurFavoriteType == E_FAVORITE_TYPE_ALL)
        {
            stCHAttribute.bIsFavorite |= BITMASK(E_FAVORITE_TYPE_4:E_FAVORITE_TYPE_1);
        }
        else
        {
            SETBIT(stCHAttribute.bIsFavorite, g_DtvSys_eCurFavoriteType);
        }
    }
    else
    {
        if (g_DtvSys_eCurFavoriteType == E_FAVORITE_TYPE_ALL)
        {
            stCHAttribute.bIsFavorite &= ~BITMASK(E_FAVORITE_TYPE_4:E_FAVORITE_TYPE_1);
        }
        else
        {
            CLRBIT(stCHAttribute.bIsFavorite, g_DtvSys_eCurFavoriteType);
        }
    }
#else
    if( bFavorite == TRUE )
    {
        stCHAttribute.bIsFavorite = TRUE;
    }
    else
    {
        stCHAttribute.bIsFavorite = FALSE;
    }
#endif

    pstProgramIndexTable[wOrder].bIsFavorite = stCHAttribute.bIsFavorite;

    return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
}
#endif

//****************************************************************************
/// This function will set skip program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bSkip \b IN: it's a skip program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_SkipProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSkip)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    }
    else
#endif
    {
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    }

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

    if( bSkip == TRUE )
    {
        stCHAttribute.bIsSkipped = TRUE;
    }
    else
    {
        stCHAttribute.bIsSkipped = FALSE;
    }

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        m_astS2ProgramIndexTable[wOrder].bIsSkipped = stCHAttribute.bIsSkipped;
    }
    else
#endif
    {
        pstProgramIndexTable[wOrder].bIsSkipped = stCHAttribute.bIsSkipped;
    }

    return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
}

//****************************************************************************
/// This function will update program Visible or Selectable
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bVisible \b IN: it's a bVisible program or not
/// @param bSelectable \b IN: it's a bSelectable program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_UpdateProgramVisibleAndSelectable(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bVisible, BOOLEAN bSelectable)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;
    BOOLEAN bUpdate=FALSE;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    }
    else
#endif
    {
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    }

    memset(&stCHAttribute, 0, sizeof(CHANNEL_ATTRIBUTE));

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    if(stCHAttribute.bInvalidService && (bVisible || bSelectable))
    {
        return FALSE;
    }
    //printf("v..%bu %bu\n",stCHAttribute.bVisibleServiceFlag,stCHAttribute.bNumericSelectionFlag);

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        if(stCHAttribute.bVisibleServiceFlag != bVisible)
        {
            m_astS2ProgramIndexTable[wOrder].bVisibleServiceFlag=stCHAttribute.bVisibleServiceFlag = bVisible;
            bUpdate=TRUE;
        }
        if(stCHAttribute.bNumericSelectionFlag != bSelectable)
        {
            m_astS2ProgramIndexTable[wOrder].bNumericSelectionFlag=stCHAttribute.bNumericSelectionFlag = bSelectable;
            bUpdate=TRUE;
        }
    }
    else
#endif
    {
        if(stCHAttribute.bVisibleServiceFlag != bVisible)
        {
            pstProgramIndexTable[wOrder].bVisibleServiceFlag=stCHAttribute.bVisibleServiceFlag = bVisible;
            bUpdate=TRUE;
        }
        if(stCHAttribute.bNumericSelectionFlag != bSelectable)
        {
            pstProgramIndexTable[wOrder].bNumericSelectionFlag=stCHAttribute.bNumericSelectionFlag = bSelectable;
            bUpdate=TRUE;
        }
    }

    if(bUpdate)
    {
       UpdateProgramCount(bServiceType);
       return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    }

    return TRUE;
}

BOOLEAN msAPI_CM_UpdateProgramSpecialService(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bSpecialService)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;
    BOOLEAN bUpdate=FALSE;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    //memset(&stCHAttribute, 0, sizeof(CHANNEL_ATTRIBUTE));   //Fix coverity CID151884

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
        GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
        //printf("v..%bu \n",stCHAttribute.bIsSpecialService);
        if(stCHAttribute.bIsSpecialService != bSpecialService)
        {
            m_astS2ProgramIndexTable[wOrder].bIsSpecialService=stCHAttribute.bIsSpecialService = bSpecialService;
            bUpdate=TRUE;
        }
    }
    else
#endif
    {
        memset(&stCHAttribute, 0, sizeof(CHANNEL_ATTRIBUTE));

        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

        GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
        //printf("v..%bu \n",stCHAttribute.bIsSpecialService);
        if(stCHAttribute.bIsSpecialService != bSpecialService)
        {
            pstProgramIndexTable[wOrder].bIsSpecialService=stCHAttribute.bIsSpecialService = bSpecialService;
            bUpdate=TRUE;
        }
    }

    if(bUpdate)
    {
        UpdateProgramCount(bServiceType);
        return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    }

    return TRUE;
}

//****************************************************************************
/// This function will set lock program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param bLock \b IN: it's a bLock program or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_LockProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BOOLEAN bLock)
{
    CHANNEL_ATTRIBUTE stCHAttribute;
    WORD wOrder,wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    }
    else
#endif
    {
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    }

    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

    if( bLock == TRUE )
    {
        stCHAttribute.bIsLock = TRUE;
    }
    else
    {
        stCHAttribute.bIsLock = FALSE;
    }

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        m_astS2ProgramIndexTable[wOrder].bIsLock = stCHAttribute.bIsLock;
    }
    else
#endif
    {
        pstProgramIndexTable[wOrder].bIsLock = stCHAttribute.bIsLock;
    }

    return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
}

static void _FillNextValidOrderToProgramData(DTV_CHANNEL_INFO *pDTVProgramData, WORD wPRIndex)
{
    S32 s32Order;
    MEMBER_SERVICETYPE eServiceType;
    WORD wServiceID;

    if (NULL == pDTVProgramData)
        return;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    eServiceType = (MEMBER_SERVICETYPE)pDTVProgramData->stCHAttribute.bServiceType;
    wServiceID = pDTVProgramData->wService_ID;

    if (eServiceType == E_SERVICETYPE_DTV)
    {
        WORD wOrderOfTV=FIRST_ORDER_OF_TV;
        for(s32Order=wOrderOfTV; s32Order < u16DTVProgramIndexTableArraySize; s32Order++)
        {
            if((DEFAULT_SERVICE_TYPE == pstDTVProgramIndexTable[s32Order].bServiceType) &&
                (FALSE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)) )
            {
                pstDTVProgramIndexTable[s32Order].bServiceType = eServiceType;
                pstDTVProgramIndexTable[s32Order].wService_ID = wServiceID;
                pstDTVProgramIndexTable[s32Order].wPRIndex = wPRIndex;
                pstDTVProgramIndexTable[s32Order].cIDIndex = pDTVProgramData->bIDIdex;
                pDTVProgramData->wOrder = (WORD)s32Order;
                return;
            }
            else if(((E_SERVICETYPE_RADIO == pstDTVProgramIndexTable[s32Order].bServiceType) ||
                (E_SERVICETYPE_DATA == pstDTVProgramIndexTable[s32Order].bServiceType))&&
                (TRUE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)))
            {
                printf("No empty dtv order be found\n");
                return;
            }
        }
    }
    else if (eServiceType == E_SERVICETYPE_RADIO)
    {
        WORD wOrderOfRadio = FIRST_ORDER_OF_RADIO(eDtvDbSel);
        for(s32Order=0; s32Order < u16DTVProgramIndexTableArraySize; s32Order++)
        {
            if((E_SERVICETYPE_DATA == pstDTVProgramIndexTable[s32Order].bServiceType) &&
                (TRUE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)) )
            {
                wOrderOfRadio--;
            }
        }

        for(s32Order=wOrderOfRadio; s32Order >=FIRST_ORDER_OF_TV; s32Order--)
        {
            if((DEFAULT_SERVICE_TYPE == pstDTVProgramIndexTable[s32Order].bServiceType) &&
                (FALSE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)) )
            {
                pstDTVProgramIndexTable[s32Order].bServiceType = eServiceType;
                pstDTVProgramIndexTable[s32Order].wService_ID = wServiceID;
                pstDTVProgramIndexTable[s32Order].wPRIndex = wPRIndex;
                pstDTVProgramIndexTable[s32Order].cIDIndex = pDTVProgramData->bIDIdex;
                pDTVProgramData->wOrder = (WORD)s32Order;
                return;
            }
            else if((E_SERVICETYPE_DTV == pstDTVProgramIndexTable[s32Order].bServiceType) &&
                (TRUE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)))
            {
                printf("No empty radio order be found\n");
                return;
            }
        }
    }
    else if (eServiceType == E_SERVICETYPE_DATA)
    {
        WORD wOrderOfData = FIRST_ORDER_OF_DATA(eDtvDbSel);
        for(s32Order=wOrderOfData; s32Order >=FIRST_ORDER_OF_TV; s32Order--)
        {
            if((DEFAULT_SERVICE_TYPE == pstDTVProgramIndexTable[s32Order].bServiceType) &&
                (FALSE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)) )
            {
                pstDTVProgramIndexTable[s32Order].bServiceType = eServiceType;
                pstDTVProgramIndexTable[s32Order].wService_ID = wServiceID;
                pstDTVProgramIndexTable[s32Order].wPRIndex = wPRIndex;
                pstDTVProgramIndexTable[s32Order].cIDIndex = pDTVProgramData->bIDIdex;
                pDTVProgramData->wOrder = (WORD)s32Order;
                return;
            }
            else if(((E_SERVICETYPE_DTV == pstDTVProgramIndexTable[s32Order].bServiceType) ||
                (E_SERVICETYPE_RADIO == pstDTVProgramIndexTable[s32Order].bServiceType)) &&
                (TRUE == IsProgramEntityActive(pstDTVProgramIndexTable[s32Order].wPRIndex)))
            {
                printf("No empty data order be found\n");
                return;
            }
        }
    }
    else
    {
        pDTVProgramData->wOrder = DEFAULT_ORDER;
        return;
    }
}

//****************************************************************************
/// This function will add program
/// @param *pDTVProgramData \b IN: pointer to DTV program data
/// -@see DTV_CHANNEL_INFO
/// @return BOOLEAN: Function execution result
//****************************************************************************
#define DEBUG_CM_ADD_PROG(x)    x
BOOLEAN msAPI_CM_AddProgram(DTV_CHANNEL_INFO *pDTVProgramData, BOOLEAN *bDBFull, BOOLEAN bSkipCheck)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();

    MEMBER_COUNTRY eCountry;
    BOOLEAN bIsValid,bIsValidService=TRUE;
    WORD wPRIndex,l_wPosition;
    BOOLEAN bUpdateCurrentService;
    WORD wCurrentServiceId;
    WORD wCurrentONID;
    WORD wCurrentTSID;
    MEMBER_SERVICETYPE bServiceType, eGotServiceType;
    WORD wPosition, u16GotPosition;
    bNotAddThisService = FALSE;

    //remove old same service
    //_RemoveService(pDTVProgramData->bIDIdex,pDTVProgramData->wService_ID);

    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);


    DEBUG_CM_ADD_PROG( msDebug_ANSI_SetColorText(E_FONT_COLOR_GREEN); );
//    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_GREEN);
    DEBUG_CM_ADD_PROG( printf("msAPI_CM_AddProgram()\n"); );

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    wCurrentServiceId = msAPI_CM_GetService_ID(bServiceType, wPosition);
    wCurrentONID = msAPI_CM_GetON_ID(bServiceType, wPosition);
    wCurrentTSID = msAPI_CM_GetTS_ID(bServiceType, wPosition);

    //remove old same service
    printf("pDTVProgramData->bIDIdex...%d\n",pDTVProgramData->bIDIdex);
#if (ENABLE_CI_PLUS)
    if(TRUE == msAPI_CM_GetOpMode())
    {
        bUpdateCurrentService=_RemoveServiceWithSameLCN(eCurDbSel, pDTVProgramData->bIDIdex,pDTVProgramData->wService_ID, pDTVProgramData->wLCN);
        //printf("Op mode! bUpdateCurrentService = %d,  bNotAddThisService = %d\n", bUpdateCurrentService,bNotAddThisService);
        if(TRUE == bNotAddThisService)
        {
            printf("CI++1.4 LCN op/virtual service conflict with normal service...no add into database!\n");
            pDTVProgramData->stCHAttribute.bVisibleServiceFlag = FALSE;
            //return FALSE;
        }
    }
    else
#endif
    {
        bUpdateCurrentService=_RemoveService(eCurDbSel, pDTVProgramData->bIDIdex,pDTVProgramData->wService_ID);
    }

    if(bUpdateCurrentService)
    {
        m_wPastServiceId = pDTVProgramData->wService_ID;
        m_wPastOriginalNetworkId = pMuxTable[pDTVProgramData->bIDIdex].wOriginalNetwork_ID;
        m_wPastTransportStreamId = pMuxTable[pDTVProgramData->bIDIdex].wTransportStream_ID;

        if(msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_DTV, pMuxTable[pDTVProgramData->bIDIdex].cRFChannelNumber, &l_wPosition))
        {
            msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
            msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,l_wPosition);
        }
        else if(msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_RADIO, pMuxTable[pDTVProgramData->bIDIdex].cRFChannelNumber, &l_wPosition))
        {
            msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
            msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,l_wPosition);
        }
        else if(msAPI_CM_GetFirstPositionInPCN(E_SERVICETYPE_DATA, pMuxTable[pDTVProgramData->bIDIdex].cRFChannelNumber, &l_wPosition))
        {
            msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
            msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,l_wPosition);
        }
        else
        {
            //should not have this case
        }
    }
    else
    {
        if(TRUE == msAPI_CM_GetServiceTypeAndPositionWithIDs( wCurrentTSID, wCurrentONID, wCurrentServiceId, 1,&eGotServiceType, &u16GotPosition, TRUE ))
        {
            if(bServiceType != eGotServiceType)
            {
                msAPI_CM_SetCurrentServiceType(eGotServiceType);
            }
            if(wPosition != u16GotPosition)
            {
                msAPI_CM_SetCurrentPosition(eGotServiceType,u16GotPosition);
            }
        }
    }
    eCountry = msAPI_CM_GetCountry();

    if(msAPI_CM_GetCountry() == E_FRANCE)
    {
        float ber = 0.0;

        if(msAPI_Tuner_GetBER(&ber))
        {
            if(ber > 0.0002)
            {
                pDTVProgramData->stCHAttribute.wSignalStrength=pDTVProgramData->stCHAttribute.wSignalStrength&0x7F00;
            }
        }
    }

    wPRIndex = GetEmptyIndexOfProgramTable_DBSel(eCurDbSel);
    U16 u16ProgTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eCurDbSel);
    if( u16ProgTableArraySize <= wPRIndex || INVALID_PRINDEX == wPRIndex )
    {
        *bDBFull=TRUE;
        return FALSE;
    }
    *bDBFull=FALSE;
    bIsValid = TRUE;

    bIsValid &= IsServiceTypeValid((MEMBER_SERVICETYPE)pDTVProgramData->stCHAttribute.bServiceType);

    bIsValid &= IsService_IDValid(pDTVProgramData->wService_ID);

    if(bSkipCheck == FALSE)
    {
        bIsValidService &= IsLogicalChannelNumberValid(pDTVProgramData->wLCN);

        bIsValidService &= IsVersionValid(pDTVProgramData->stPSI_SI_Version.bPATVer);

        bIsValidService &= IsVersionValid(pDTVProgramData->stPSI_SI_Version.bPMTVer);

        bIsValidService &= IsVersionValid(pDTVProgramData->stPSI_SI_Version.bNITVer);

        bIsValidService &= IsVersionValid(pDTVProgramData->stPSI_SI_Version.bSDTVer);

        bIsValidService &= IsService_IDValid(pDTVProgramData->wService_ID);

        bIsValidService &= IsPMT_PIDValid(pDTVProgramData->wPmt_PID);

        bIsValidService &= IsPCR_PIDValid(pDTVProgramData->wPCR_PID);

        if( pDTVProgramData->stCHAttribute.bServiceType == E_SERVICETYPE_DTV )
        {
            bIsValidService &= IsVideoPIDValid(pDTVProgramData->wVideo_PID);

        }
        bIsValidService &= IsAudioStreamInfoValid(pDTVProgramData->stAudInfo);

    }

    printf("add service valid %d idindex %x sid %x lcn %d simulcn %d\n",bIsValidService,
        pDTVProgramData->bIDIdex,pDTVProgramData->wService_ID,
        pDTVProgramData->wLCN,pDTVProgramData->wSimu_LCN  );

    printf("cPLPID=%u, cHpLp=%u\n", pMuxTable[pDTVProgramData->bIDIdex].cPLPID, pMuxTable[pDTVProgramData->bIDIdex].cHpLp );

    printf(" bChannelName=");
    msAPI_DtvSys_PrintServiceName( pDTVProgramData->bChannelName, MAX_SERVICE_NAME );
    printf("\n");

    if( FALSE == bIsValid)
    {
        printf("bIsValid=FALSE!\n");
        return FALSE;
    }
    if( FALSE == bIsValidService)
    {
        pDTVProgramData->stCHAttribute.bInvalidService=TRUE;
        pDTVProgramData->stCHAttribute.bVisibleServiceFlag=FALSE;
        pDTVProgramData->stCHAttribute.bNumericSelectionFlag=FALSE;
    }

    if ((TRUE == pDTVProgramData->stCHAttribute.bInvalidService)
        || (FALSE == pDTVProgramData->stCHAttribute.bVisibleServiceFlag))
    {
        bIsValidService = FALSE;
    }
    else
    {
        bIsValidService = TRUE;
    }

    eCountry = msAPI_CM_GetCountry();

    if(FALSE == msAPI_CM_GetOpMode())
    {
        switch(eCountry)
        {
        case E_FINLAND:
        case E_SWEDEN:
        case E_DENMARK:
        case E_NORWAY:
        case E_GERMANY:
            if( INVALID_LOGICAL_CHANNEL_NUMBER != pDTVProgramData->wLCN &&
                9999 < pDTVProgramData->wLCN )
            {
                pDTVProgramData->wLCN &= 0x3FF;
            }
            break;

        default:
           #if (ENABLE_SBTVD_DTV_SYSTEM)
           if(!msAPI_SRC_IS_SBTVD_InUse())
           #endif
            {
                // Outside Nordig countries, LCN > 999 is Illegal. Set Invalid.
                if( INVALID_LOGICAL_CHANNEL_NUMBER != pDTVProgramData->wLCN &&
                    (999 < pDTVProgramData->wLCN ))
                {
                    pDTVProgramData->wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
                }
            }
            break;
        }
    }

    _FillNextValidOrderToProgramData(pDTVProgramData, wPRIndex);

    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)pDTVProgramData, E_DATA_ALL) )
    {
        return FALSE;
    }

    ActiveProgramEntity_DBSel(eCurDbSel, wPRIndex, TRUE);

    UpdateProgramCount((MEMBER_SERVICETYPE)pDTVProgramData->stCHAttribute.bServiceType);

    DEBUG_CM_ADD_PROG( msDebug_ANSI_AllAttrOffText(); );

    return bIsValidService;
}

static BOOLEAN _IsCountryNetworkService(WORD wNID)
{
    MEMBER_COUNTRY eCountry;
    eCountry = msAPI_CM_GetCountry();
    switch(eCountry)
    {
        case E_ITALY:
            if((wNID>=ITALY_NETWORK_START)&&(wNID<=ITALY_NETWORK_END))
            {
                return TRUE;
            }
            return FALSE;
        default:
            return TRUE;
    }
}

//****************************************************************************
/// This function will check it have duplicate LCN program(different service)
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wStartLCN \b IN: start number to check
/// @return DTV_SIMPLE_SERVICE_INFO*: list point of duplicate service
//****************************************************************************
DTV_SIMPLE_SERVICE_INFO* msAPI_CM_GetDuplicateService(MEMBER_SERVICETYPE bServiceType, WORD wStartLCN)
{
    DWORD index1,index2;
    DTV_CHANNEL_INFO stCHInfo;
    WORD NextLCN;
    DTV_SIMPLE_SERVICE_INFO *pItem,*pNext;
    WORD wCountryVisibleService,wCountryInvisibleService,wOtherCountryVisibleService;
    memset(&stCHInfo,0,sizeof(DTV_CHANNEL_INFO));

    PRINT_CURRENT_LINE();
#if(ASTRA_HD_ENABLE)
    BOOLEAN bIsScramble;
#endif

#if 1//( ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    //DTVNETWORK _astDTVNetwork[MAX_NETWOEK_NUMBER];
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eCurDbSel);

#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
  #if(ENABLE_S2)
    if (IsS2InUse())
    {
        pMuxTable=_astS2ProgramIDTable;
    }
  #endif
#endif

#if 0//(ENABLE_S2)
    if (IsS2InUse())
    {
        if(wStartLCN==1)//first
        {
            memset(m_astS2ProgramIndexTable,0,sizeof(DTVPROGRAMINDEX)*MAX_DTV_S2_PROGRAM);
            for(index1=0; index1 < MAX_DTV_S2_PROGRAM; index1++)//collect channel
            {
                m_astS2ProgramIndexTable[index1].bServiceType=E_SERVICETYPE_INVALID;
                if(IsProgramEntityActive(index1))
                {
                    if(GetProgramTable(index1, (BYTE*)&stCHInfo, E_DATA_ALL))
                    {
                        if(stCHInfo.stCHAttribute.bServiceType == bServiceType)
                        {
                            m_astS2ProgramIndexTable[index1].wService_ID=stCHInfo.wService_ID;
                            m_astS2ProgramIndexTable[index1].wLCN=stCHInfo.wLCN;
                            m_astS2ProgramIndexTable[index1].cIDIndex=stCHInfo.bIDIdex;
                            m_astS2ProgramIndexTable[index1].bServiceType=stCHInfo.stCHAttribute.bServiceType;
                            m_astS2ProgramIndexTable[index1].bVisibleServiceFlag=stCHInfo.stCHAttribute.bVisibleServiceFlag;
                        }
                    }
                }
            }


            for(index1=0; index1 < (MAX_DTV_S2_PROGRAM-1); index1++)//set same service
            {
                if(m_astS2ProgramIndexTable[index1].bServiceType==bServiceType)
                {
                    for(index2=index1+1; index2 < MAX_DTV_S2_PROGRAM; index2++)//set same service
                    {
                        if(m_astS2ProgramIndexTable[index2].bServiceType==bServiceType)
                        {
                            if(m_astS2ProgramIndexTable[index1].wService_ID==m_astS2ProgramIndexTable[index2].wService_ID)
                            {
                                if(pMuxTable[m_astS2ProgramIndexTable[index1].cIDIndex].wTransportStream_ID == \
                                    pMuxTable[m_astS2ProgramIndexTable[index2].cIDIndex].wTransportStream_ID && \
                                    pMuxTable[m_astS2ProgramIndexTable[index1].cIDIndex].wOriginalNetwork_ID == \
                                    pMuxTable[m_astS2ProgramIndexTable[index2].cIDIndex].wOriginalNetwork_ID)
                                {
                                    CHANNEL_ATTRIBUTE Misc1,Misc2;
                                    WORD wNID_1=INVALID_NID,wNID_2=INVALID_NID;
                                    GetProgramTable(index1, (BYTE *)&Misc1, E_DATA_MISC);
                                    GetProgramTable(index2, (BYTE *)&Misc2, E_DATA_MISC);

                                    if(pMuxTable[m_astS2ProgramIndexTable[index1].cIDIndex].cNetWorkIndex < INVALID_NETWORKINDEX)
                                    {
                                        wNID_1=_astDTVNetwork[pMuxTable[m_astS2ProgramIndexTable[index1].cIDIndex].cNetWorkIndex].wNetwork_ID;
                                    }
                                    if(pMuxTable[m_astS2ProgramIndexTable[index2].cIDIndex].cNetWorkIndex < INVALID_NETWORKINDEX)
                                    {
                                        wNID_2=_astDTVNetwork[pMuxTable[m_astS2ProgramIndexTable[index2].cIDIndex].cNetWorkIndex].wNetwork_ID;
                                    }
#if (ENABLE_SAVE_SQI)
                                    if(SelectBestMux(&Misc1,wNID_1, INVALID_SQI, &Misc2, wNID_2, INVALID_SQI)>0)
#else
                                    if(SelectBestMux(&Misc1,wNID_1,&Misc2,wNID_2)>0)
#endif
                                    {
                                        m_astS2ProgramIndexTable[index1].eLCNAssignmentType|=E_LCN_SAME_SERVICE;
                                    }
                                    else
                                    {
                                        m_astS2ProgramIndexTable[index2].eLCNAssignmentType|=E_LCN_SAME_SERVICE;
                                    }

                                }

                            }
                        }
                    }

                }
            }
        }
    }
    else
#endif
    {
    if(wStartLCN==1)//first
    {
        //memset(m_astDTVProgramIndexTable,0,sizeof(DTVPROGRAMINDEX)*MAX_DTVPROGRAM);
        memset(pstDTVProgramIndexTable, 0, sizeof(DTVPROGRAMINDEX)*u16ProgramIndexTableArraySize);

        //for(index1=0; index1 < MAX_DTVPROGRAM; index1++)//collect channel
        for(index1=0; index1 < u16ProgramIndexTableArraySize; index1++)//collect channel
        {
            pstDTVProgramIndexTable[index1].bServiceType=E_SERVICETYPE_INVALID;
            if(IsProgramEntityActive(index1))
            {
                if(GetProgramTable(index1, (BYTE*)&stCHInfo, E_DATA_ALL))
                {
                    if(stCHInfo.stCHAttribute.bServiceType == bServiceType)
                    {
                        pstDTVProgramIndexTable[index1].wService_ID=stCHInfo.wService_ID;
                        pstDTVProgramIndexTable[index1].wLCN=stCHInfo.wLCN;
                        pstDTVProgramIndexTable[index1].cIDIndex=stCHInfo.bIDIdex;
                        pstDTVProgramIndexTable[index1].bServiceType=stCHInfo.stCHAttribute.bServiceType;
                        pstDTVProgramIndexTable[index1].bVisibleServiceFlag=stCHInfo.stCHAttribute.bVisibleServiceFlag;
#if(ASTRA_HD_ENABLE)
                        if(GetASTRA_HD_ENABLE())
                        {
                            pstDTVProgramIndexTable[index1].bIsScramble=stCHInfo.stCHAttribute.bIsScramble;
                        }
#endif
                    }
                }
            }
        }


        //for(index1=0; index1 < (MAX_DTVPROGRAM-1); index1++)//set same service
        for(index1=0; index1 < (U32)(u16ProgramIndexTableArraySize-1); index1++)//set same service
        {
            if(pstDTVProgramIndexTable[index1].bServiceType==bServiceType)
            {
                //for(index2=index1+1; index2 < MAX_DTVPROGRAM; index2++)//set same service
                for(index2=index1+1; index2 < u16ProgramIndexTableArraySize; index2++)//set same service
                {
                    if(pstDTVProgramIndexTable[index2].bServiceType==bServiceType)
                    {
                        if(pstDTVProgramIndexTable[index1].wService_ID==pstDTVProgramIndexTable[index2].wService_ID)
                        {
                            if(pMuxTable[pstDTVProgramIndexTable[index1].cIDIndex].wTransportStream_ID == \
                                pMuxTable[pstDTVProgramIndexTable[index2].cIDIndex].wTransportStream_ID && \
                                pMuxTable[pstDTVProgramIndexTable[index1].cIDIndex].wOriginalNetwork_ID == \
                                pMuxTable[pstDTVProgramIndexTable[index2].cIDIndex].wOriginalNetwork_ID
#if(ASTRA_HD_ENABLE)
                                && (!GetASTRA_HD_ENABLE() || pstDTVProgramIndexTable[index1].wLCN == pstDTVProgramIndexTable[index2].wLCN)
#endif
                                )
                            {
                                CHANNEL_ATTRIBUTE Misc1, Misc2;
                                WORD wNID_1=INVALID_NID, wNID_2=INVALID_NID;

                                memset(&Misc1, 0, sizeof(CHANNEL_ATTRIBUTE));
                                memset(&Misc2, 0, sizeof(CHANNEL_ATTRIBUTE));

                                GetProgramTable(index1, (BYTE *)&Misc1, E_DATA_MISC);
                                GetProgramTable(index2, (BYTE *)&Misc2, E_DATA_MISC);

                                if(pMuxTable[pstDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize )
                                {
                                    wNID_1=pstNetworkTable[pMuxTable[pstDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex].wNetwork_ID;
                                }
                                if(pMuxTable[pstDTVProgramIndexTable[index2].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize )
                                {
                                    wNID_2=pstNetworkTable[pMuxTable[pstDTVProgramIndexTable[index2].cIDIndex].cNetWorkIndex].wNetwork_ID;
                                }

                            #if (ENABLE_SAVE_SQI)
                                if(SelectBestMux(&Misc1,wNID_1, INVALID_SQI, &Misc2, wNID_2, INVALID_SQI)>0)
                            #else
                                if(SelectBestMux(&Misc1,wNID_1,&Misc2,wNID_2)>0)
                            #endif
                                {
                                    pstDTVProgramIndexTable[index1].eLCNAssignmentType|=E_LCN_SAME_SERVICE;
                                }
                                else
                                {
                                    pstDTVProgramIndexTable[index2].eLCNAssignmentType|=E_LCN_SAME_SERVICE;
                                }

                            }

                        }
                    }
                }

            }
        }
    }
    }

Restart:
    wCountryVisibleService=0;
    wCountryInvisibleService=0;
    wOtherCountryVisibleService=0;
#if(ASTRA_HD_ENABLE)
    bIsScramble=0;
#endif
    while(_pDuplicateServiceList)//free old service
    {
        pItem=_pDuplicateServiceList;
        _pDuplicateServiceList=_pDuplicateServiceList->next;
        msAPI_Memory_Free(pItem, BUF_ID_DTV_SYS_DUPLICATE_SERVICE);
    }
    NextLCN=INVALID_LOGICAL_CHANNEL_NUMBER;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for(index1=0; index1 < MAX_DTV_S2_PROGRAM; index1++)//find next LCN
        {
            if(m_astS2ProgramIndexTable[index1].bServiceType == bServiceType)
            {
                if(m_astS2ProgramIndexTable[index1].wLCN>=wStartLCN && \
                    m_astS2ProgramIndexTable[index1].wLCN<NextLCN)
                {
                    NextLCN=m_astS2ProgramIndexTable[index1].wLCN;
                }
            }
        }
        if(NextLCN==INVALID_LOGICAL_CHANNEL_NUMBER)return NULL;//no more duplicate LCN

        for(index1=0; index1 < MAX_DTV_S2_PROGRAM; index1++)
        {
            if((m_astS2ProgramIndexTable[index1].wLCN==NextLCN)&&(m_astS2ProgramIndexTable[index1].bServiceType == bServiceType))
            {
                if(!(m_astS2ProgramIndexTable[index1].eLCNAssignmentType&E_LCN_SAME_SERVICE))
                {
                    BOOLEAN bCountryService;
                    if(pMuxTable[m_astS2ProgramIndexTable[index1].cIDIndex].cNetWorkIndex<MAX_NETWOEK_NUMBER)
                    {
                        //printf("network id %x name %s\n",_astDTVNetwork[pMuxTable[m_astDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex].wNetwork_ID,
                        //    _astDTVNetwork[pMuxTable[m_astDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex].bNetworkName);
                        bCountryService=_IsCountryNetworkService(_astDTVNetwork[pMuxTable[m_astS2ProgramIndexTable[index1].cIDIndex].cNetWorkIndex].wNetwork_ID);
                    }
                    else
                    {
                        ASSERT(0);
                        bCountryService=FALSE;
                    }
                    if(bCountryService || m_astS2ProgramIndexTable[index1].bVisibleServiceFlag)
                    {
                        pItem=(DTV_SIMPLE_SERVICE_INFO*)msAPI_Memory_Allocate(sizeof(DTV_SIMPLE_SERVICE_INFO),(EN_BUFFER_ID)0);
                        ASSERT(pItem);
                        if(pItem==NULL)goto exit;
                        memset(pItem,0,sizeof(DTV_SIMPLE_SERVICE_INFO));
                        GetProgramTable(index1, pItem->bChannelName, E_DATA_SERVICE_NAME);
                        pItem->wNumber=m_astS2ProgramIndexTable[index1].wLCN;
                        pItem->dwPosition=index1;
                        pItem->bVisible=m_astS2ProgramIndexTable[index1].bVisibleServiceFlag;
                        pItem->bCountryService=bCountryService;
                        pItem->bServiceToSelect=TRUE;
                        pItem->next=_pDuplicateServiceList;
                        _pDuplicateServiceList=pItem;

                        //printf("add service index %d lcn %d country %d visible %d name %s\n",
                        //    index1,pItem->wNumber,pItem->bCountryService,pItem->bVisible,pItem->bChannelName);
                        if(bCountryService)
                        {
                            if(pItem->bVisible)
                            {
                                wCountryVisibleService++;
                            }
                            else
                            {
                                wCountryInvisibleService++;
                            }
                        }
                        else
                        {
                            wOtherCountryVisibleService++;
                        }
                    }
                }
            }
        }
    }
    else
#endif
    {
    //for(index1=0; index1 < MAX_DTVPROGRAM; index1++)//find next LCN
    for(index1=0; index1 < u16ProgramIndexTableArraySize; index1++)//find next LCN
    {
        if(pstDTVProgramIndexTable[index1].bServiceType == bServiceType)
        {
            if(pstDTVProgramIndexTable[index1].wLCN>=wStartLCN && \
                pstDTVProgramIndexTable[index1].wLCN<NextLCN)
            {
                NextLCN=pstDTVProgramIndexTable[index1].wLCN;
            }
        }
    }
    if(NextLCN==INVALID_LOGICAL_CHANNEL_NUMBER)
    {
        return NULL;//no more duplicate LCN
    }

    //for(index1=0; index1 < MAX_DTVPROGRAM; index1++)
    for(index1=0; index1 < u16ProgramIndexTableArraySize; index1++)
    {
        if((pstDTVProgramIndexTable[index1].wLCN==NextLCN)&&(pstDTVProgramIndexTable[index1].bServiceType == bServiceType))
        {
#if(ASTRA_HD_ENABLE)
            if(GetASTRA_HD_ENABLE() && pstDTVProgramIndexTable[index1].bIsScramble == TRUE)
            {
                bIsScramble=pstDTVProgramIndexTable[index1].bIsScramble;
            }
#endif

            if(!(pstDTVProgramIndexTable[index1].eLCNAssignmentType&E_LCN_SAME_SERVICE))
            {
                BOOLEAN bCountryService;

                if(pMuxTable[pstDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                {
                    //printf("network id %x name %s\n",_astDTVNetwork[pMuxTable[m_astDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex].wNetwork_ID,
                    //  _astDTVNetwork[pMuxTable[m_astDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex].bNetworkName);
                    bCountryService=_IsCountryNetworkService(pstNetworkTable[pMuxTable[pstDTVProgramIndexTable[index1].cIDIndex].cNetWorkIndex].wNetwork_ID);
                }
                else
                {
                    ASSERT(0);
                    bCountryService=FALSE;
                }
                if(bCountryService || pstDTVProgramIndexTable[index1].bVisibleServiceFlag)
                {
                    pItem=(DTV_SIMPLE_SERVICE_INFO*)msAPI_Memory_Allocate(sizeof(DTV_SIMPLE_SERVICE_INFO),BUF_ID_DTV_SYS_DUPLICATE_SERVICE);
                    ASSERT(pItem);
                    if(pItem==NULL)goto exit;
                    memset(pItem,0,sizeof(DTV_SIMPLE_SERVICE_INFO));
                    GetProgramTable(index1, pItem->bChannelName, E_DATA_SERVICE_NAME);
                    pItem->wNumber=pstDTVProgramIndexTable[index1].wLCN;
                    pItem->dwPosition=index1;
                    pItem->bVisible=pstDTVProgramIndexTable[index1].bVisibleServiceFlag;
                    pItem->bCountryService=bCountryService;
                    pItem->bServiceToSelect=TRUE;
                    pItem->next=_pDuplicateServiceList;
                    _pDuplicateServiceList=pItem;

                    //printf("add service index %d lcn %d country %d visible %d name %s\n",
                    //  index1,pItem->wNumber,pItem->bCountryService,pItem->bVisible,pItem->bChannelName);
                    if(bCountryService)
                    {
                        if(pItem->bVisible)
                        {
                            wCountryVisibleService++;
                        }
                        else
                        {
                            wCountryInvisibleService++;
                        }
                    }
                    else
                    {
                        wOtherCountryVisibleService++;
                    }
                }
            }

        }
    }
    }
exit:

#if (ASTRA_HD_ENABLE)
    if(GetASTRA_HD_ENABLE() && (!bIsScramble))//if have an program is scramble,auto handle LCN conflict
    {
        wStartLCN=NextLCN+1;
        goto Restart;
    }
#endif
    //printf("wCountryVisibleService %d wCountryInvisibleService %d wOtherCountryVisibleService %d\n",
    //  wCountryVisibleService,wCountryInvisibleService,wOtherCountryVisibleService);
    if((wCountryVisibleService+wCountryInvisibleService+wOtherCountryVisibleService)>1)
    {
        if(wCountryVisibleService||wCountryInvisibleService)//have service match country
        {
            if(wCountryVisibleService<=1)
            {
                wStartLCN=NextLCN+1;
                goto Restart;
            }
            pNext=_pDuplicateServiceList;
            while(pNext)
            {
                if((pNext->bCountryService==FALSE)||(pNext->bVisible==FALSE))
                {
                    pNext->bServiceToSelect=FALSE;
                }
                pNext=pNext->next;
            }

        }
        else if(wOtherCountryVisibleService>1)
        {
            pNext=_pDuplicateServiceList;
            while(pNext)
            {
                if(pNext->bVisible==FALSE)
                {
                    pNext->bServiceToSelect=FALSE;
                }
                pNext=pNext->next;
            }
        }
        else
        {
            wStartLCN=NextLCN+1;
            goto Restart;
        }
    }
    else if(_pDuplicateServiceList!=NULL)
    {
        wStartLCN=NextLCN+1;
        goto Restart;
    }

    return _pDuplicateServiceList;
}

//****************************************************************************
/// This function will put the service that user select to the first in list
/// @param dwIndex \b IN: index of service
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_SetSelectService(DWORD dwIndex)
{
    CHANNEL_ATTRIBUTE Misc1;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel);


#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        if((dwIndex>=MAX_DTV_S2_PROGRAM)||(IsProgramEntityActive(dwIndex)==FALSE))
        {
            ASSERT(0);
            return FALSE;
        }
    }
    else
#endif
    {
        if((dwIndex>=u16ProgramTableArraySize)||(IsProgramEntityActive(dwIndex)==FALSE))
        {
            ASSERT(0);
            return FALSE;
        }
    }

    if(GetProgramTable(dwIndex, (BYTE *)&Misc1, E_DATA_MISC)==FALSE)
        return FALSE;

    Misc1.wSignalStrength = 0x7FFF;

    return SetProgramTable(dwIndex, (BYTE *)&Misc1, E_DATA_MISC);
}

//****************************************************************************
/// This function will update program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *pcBuffer \b IN: pointer buffer
/// @param eMember \b IN: program data member
/// -@see PROGRAMDATA_MEMBER
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_UpdateProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE *pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    AUD_INFO AudioInfo[MAX_AUD_LANG_NUM];
    AUD_INFO bPreAudioInfo[MAX_AUD_LANG_NUM];
    DTV_CHANNEL_INFO DTVProgramData;
    MEMBER_COUNTRY eCountry = E_COUNTRY_NUM;
    WORD wOrder = 0, wPRIndex = 0, cIDIndex = 0, wLCN = 0, wPreLCN = 0, wMemID = 0;
    //U16 wPreMemID = 0;
    BYTE bPhyNum = 0, bPrePhyNum = 0, bVerNum = 0, bPreVerNum = 0;
    BOOLEAN Ret=FALSE;
    //CHANNEL_ATTRIBUTE Misc1;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    memset(&AudioInfo, 0, sizeof(AudioInfo));
    memset(&bPreAudioInfo, 0, sizeof(bPreAudioInfo));

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
#else
 #if(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
        cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
    }
    else
 #endif
    {
        wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
        cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
    }
#endif


#if 0
    GetProgramTable(wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);

    if( TRUE == Misc1.bInvalidService)
    {
        return FALSE;
    }
#endif

    switch(eMember)
    {
    case E_DATA_ALL:

        memcpy(&DTVProgramData,pcBuffer,sizeof(DTV_CHANNEL_INFO));
        // need touch. check param.
//        return SetProgramTable(m_astDTVProgramIndexTable[wOrder].wPRIndex, pcBuffer, E_DATA_ALL);
        eCountry = msAPI_CM_GetCountry();
        switch(eCountry)
        {
        case E_FINLAND:
        case E_SWEDEN:
        case E_DENMARK:
        case E_NORWAY:
            if(FALSE == msAPI_CM_GetOpMode())
            {
                if( INVALID_LOGICAL_CHANNEL_NUMBER != DTVProgramData.wLCN &&
                    9999 < DTVProgramData.wLCN )
                {
                    DTVProgramData.wLCN &= 0x3FF;
                }
            }
            break;

        default:
            break;
        }
        Ret=SetProgramTable(wPRIndex, (BYTE *)&DTVProgramData, eMember);
        msAPI_CM_UpdateProgramVisibleAndSelectable(bServiceType,wPosition,
            DTVProgramData.stCHAttribute.bVisibleServiceFlag,
            DTVProgramData.stCHAttribute.bNumericSelectionFlag);
        return Ret;

    case E_DATA_LCN:
        GetProgramTable(wPRIndex, (BYTE *)&wPreLCN, E_DATA_LCN);
        memcpy(&wLCN,pcBuffer,sizeof(WORD));
        if( TRUE == IsLogicalChannelNumberValid(wLCN) )
        {
            CHANNEL_ATTRIBUTE Misc;
            GetProgramTable(wPRIndex, (BYTE *)&Misc, E_DATA_MISC);
            Misc.bValidLCN=TRUE;

            // The SI country should sync with ResetBestMuxData
            if( (msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_NORDIC_SPECIFIC_COUNTRY)) )
            {
                Misc.wSignalStrength=0x7FFD;
            }

            SetProgramTable(wPRIndex, (BYTE *)&Misc, E_DATA_MISC);
            if(wPreLCN != wLCN)
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_LCN);
            }
        }
        break;
    case E_DATA_TS_LCN:
        GetProgramTable(wPRIndex, (BYTE *)&wPreLCN, E_DATA_TS_LCN);
        memcpy(&wLCN,pcBuffer,sizeof(WORD));
        if( TRUE == IsLogicalChannelNumberValid(wLCN) )
        {
            if(wPreLCN != wLCN)
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_TS_LCN);
            }
        }
        break;
    case E_DATA_SIMU_LCN:
        GetProgramTable(wPRIndex, (BYTE *)&wPreLCN, E_DATA_SIMU_LCN);
        memcpy(&wLCN,pcBuffer,sizeof(WORD));
        if( TRUE == IsLogicalChannelNumberValid(wLCN) )
        {
            if(wPreLCN != wLCN)
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_SIMU_LCN);
            }
        }
        break;
    case E_DATA_PCN:
        GetProgramTable(wPRIndex, (BYTE *)&bPrePhyNum, E_DATA_PCN);
        memcpy(&bPhyNum,pcBuffer,sizeof(BYTE));
        if( TRUE == IsPhysicalChannelNumberValid(bPhyNum) )
        {
            if(bPrePhyNum != bPhyNum)
            {
                return SetIDTable(cIDIndex, pcBuffer, E_DATA_PCN);
            }
        }
        break;

    case E_DATA_VERSION_PAT:
        GetProgramTable(wPRIndex, (BYTE *)&bPreVerNum, E_DATA_VERSION_PAT);
        memcpy(&bVerNum,pcBuffer,sizeof(BYTE));
        if( TRUE == IsVersionValid(bVerNum) )
        {
            return SetProgramTable(wPRIndex, pcBuffer, E_DATA_VERSION_PAT);
        }
        break;

    case E_DATA_VERSION_PMT:
        GetProgramTable(wPRIndex, (BYTE *)&bPreVerNum, E_DATA_VERSION_PMT);
        memcpy(&bVerNum,pcBuffer,sizeof(BYTE));
        if( TRUE == IsVersionValid(bVerNum) )
        {
            if(bPreVerNum != bVerNum)
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_VERSION_PMT);
            }
        }
        break;

    case E_DATA_VERSION_NIT:
        GetProgramTable(wPRIndex, (BYTE *)&bPreVerNum, E_DATA_VERSION_NIT);
        memcpy(&bVerNum,pcBuffer,sizeof(BYTE));
        if( TRUE == IsVersionValid(bVerNum) )
        {
            if(bPreVerNum != bVerNum)
            {
            #if(ENABLE_UPDATE_MULTIPLEX_NIT_UAE)
                g_NITVersionChange = TRUE;
            #endif
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_VERSION_NIT);
            }
        }
        break;

    case E_DATA_VERSION_SDT:
        GetProgramTable(wPRIndex, (BYTE *)&bPreVerNum, E_DATA_VERSION_SDT);
        memcpy(&bVerNum,pcBuffer,sizeof(BYTE));
        if( TRUE == IsVersionValid(bVerNum) )
        {
            if(bPreVerNum != bVerNum)
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_VERSION_SDT);
            }
        }
        break;

    case E_DATA_TS_ID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_ON_ID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        if( TRUE == IsTS_IDValid(wMemID) )
        {
          #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                _astS2ProgramIDTable[cIDIndex].wTransportStream_ID = wMemID;
            }
            else
          #endif
            {
                pMuxTable[cIDIndex].wTransportStream_ID = wMemID;
            }
            return SetIDTable(cIDIndex, pcBuffer, E_DATA_TS_ID);
        }
        break;

    case E_DATA_ON_ID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_ON_ID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        if( TRUE == IsON_IDValid(wMemID) )
        {
          #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                _astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID = wMemID;
            }
            else
          #endif
            {
                pMuxTable[cIDIndex].wOriginalNetwork_ID = wMemID;
            }
            return SetIDTable(cIDIndex, pcBuffer, E_DATA_ON_ID);
        }
        break;

    case E_DATA_NETWORK_ID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_NETWORK_ID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        if( TRUE == IsON_IDValid(wMemID) )
        {
        #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                _astDTVNetwork[_astS2ProgramIDTable[cIDIndex].cNetWorkIndex].wNetwork_ID= wMemID;
                return SetIDTable(_astS2ProgramIDTable[cIDIndex].cNetWorkIndex, pcBuffer, E_DATA_NETWORK_ID);
            }
            else
        #endif
            {
                //_astDTVNetwork[pMuxTable[cIDIndex].cNetWorkIndex].wNetwork_ID = wMemID;
                pstNetworkTable[pMuxTable[cIDIndex].cNetWorkIndex].wNetwork_ID = wMemID;
                return SetIDTable(pMuxTable[cIDIndex].cNetWorkIndex, pcBuffer, E_DATA_NETWORK_ID);
            }
        }
        break;

    case E_DATA_CELL_ID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_SERVICE_ID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        {
        #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                _astS2ProgramIDTable[cIDIndex].wCellID= wMemID;
            }
            else
        #endif
            {
                pMuxTable[cIDIndex].wCellID= wMemID;
            }
            return SetIDTable(cIDIndex, pcBuffer, E_DATA_CELL_ID);
        }

    case E_DATA_SERVICE_ID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_SERVICE_ID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        if( TRUE == IsService_IDValid(wMemID) )
        {
            return SetProgramTable(wPRIndex, pcBuffer, E_DATA_SERVICE_ID);
        }
        break;

    case E_DATA_PCR_PID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_PCR_PID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        if( TRUE == IsPCR_PIDValid(wMemID) )
        {
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_PCR_PID);
            }
        }
        break;

    case E_DATA_PMT_PID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_PMT_PID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        if( TRUE == IsPMT_PIDValid(wMemID) )
        {
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_PMT_PID);
            }
        }
        break;

    case E_DATA_VIDEO_PID:
        //GetProgramTable(wPRIndex, (BYTE *)&wPreMemID, E_DATA_VIDEO_PID);
        memcpy(&wMemID,pcBuffer,sizeof(WORD));
        //if( bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_DATA)
        {
            if( TRUE == IsVideoPIDValid(wMemID) )
            {
                {
                    return SetProgramTable(wPRIndex, pcBuffer, E_DATA_VIDEO_PID);
                }
            }
        }
        break;

    case E_DATA_AUDIO_STREAM_INFO:
        GetProgramTable(wPRIndex, (BYTE *)&bPreAudioInfo, E_DATA_AUDIO_STREAM_INFO);
        memcpy(&AudioInfo,pcBuffer,sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);
        if( TRUE == IsAudioStreamInfoValid(AudioInfo) )
        {
            if(memcmp(&bPreAudioInfo,&AudioInfo,sizeof(AUD_INFO)*MAX_AUD_LANG_NUM))
            {
                return SetProgramTable(wPRIndex, pcBuffer, E_DATA_AUDIO_STREAM_INFO);
            }
        }
        break;

    case E_DATA_SERVICE_NAME:
        return SetProgramTable(wPRIndex, pcBuffer, E_DATA_SERVICE_NAME);

    #if ENABLE_DTV_STORE_TTX_PAGE_INFO
    case E_DATA_TTX_LIST:
         return SetProgramTable(wPRIndex, pcBuffer, E_DATA_TTX_LIST);
    #endif
    case E_DATA_REPLACE_SERVICE:
        {
            CHANNEL_ATTRIBUTE stCHAttribute;
            GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
            stCHAttribute.bReplaceService=*pcBuffer;
            pstProgramIndexTable[wOrder].bReplaceService=*pcBuffer;
            return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
        }

#if(MHEG5_SIINFO_ENABLE)
    case E_DATA_PROVIDER_NAME:
        return SetProgramTable(wPRIndex, pcBuffer,E_DATA_PROVIDER_NAME);
#endif //#if(MHEG5_SIINFO_ENABLE)
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    case E_DATA_MISC:
    {
        CHANNEL_ATTRIBUTE stCHAttribute;
        GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
        stCHAttribute.bVisibleServiceFlag=*pcBuffer;
        pstProgramIndexTable[wOrder].bVisibleServiceFlag=*pcBuffer;
        return SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
    }

    case E_DATA_SGT_PID:
    {
        WORD u16SgtPID;
        GetProgramTable(wPRIndex, (BYTE *)&u16SgtPID, E_DATA_SGT_PID);
        memcpy(&u16SgtPID,pcBuffer,sizeof(WORD));
        return SetProgramTable(wPRIndex, (BYTE *)&u16SgtPID, E_DATA_SGT_PID);
    }
#endif

    default:
        break;
    }

    return FALSE;
}

//------------------------------------------------------------------------------
/// -This function will get List Page Number
/// @param u8ListIndex \b IN: List Index
/// @param pwListPageNumber \b IN: pointer to List Page Number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
#if ENABLE_DTV_STORE_TTX_PAGE_INFO
BOOLEAN msAPI_CM_GetListPageNumber(BYTE u8ListIndex, WORD * pwListPageNumber,MEMBER_SERVICETYPE bServiceType,WORD wPosition)
{
    BYTE u8SavedListPage[MAX_LISTPAGE_SIZE];
    WORD wSavedListPageNumber,wOrder;


    if ( MAX_LISTPAGE <= u8ListIndex )
    {
        return FALSE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


  #if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        if ( TRUE != GetProgramTable(m_astS2ProgramIndexTable[wOrder].wPRIndex, u8SavedListPage, E_DATA_TTX_LIST) )
        {
            return FALSE;
        }
    }
    else
  #endif
    {
        if ( TRUE != GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, u8SavedListPage, E_DATA_TTX_LIST) )
        {
            return FALSE;
        }
    }

    wSavedListPageNumber = GetListPageNumber(u8SavedListPage, u8ListIndex);

    if ( wSavedListPageNumber < 100 || 899 < wSavedListPageNumber )
    {
        wSavedListPageNumber = DEFAULT_LISTPAGE[u8ListIndex];
    }

    *pwListPageNumber = wSavedListPageNumber;

    return TRUE;
}

//------------------------------------------------------------------------------
/// -This function will set List Page Number
/// @param u8ListIndex \b IN: List Index
/// @param pwListPageNumber \b IN: pointer to List Page Number
/// @return BOOLEAN: Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_CM_SetListPageNumber(BYTE u8ListIndex, WORD wListPageNumber,MEMBER_SERVICETYPE bServiceType,WORD wPosition)
{
    BYTE u8SavedListPage[MAX_LISTPAGE_SIZE];
    WORD wOrder;

    if ( MAX_LISTPAGE <= u8ListIndex )
    {
        return FALSE;
    }

    if ( wListPageNumber < 100 || 899 < wListPageNumber )
    {
        return FALSE;
    }


    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        if ( TRUE != GetProgramTable(m_astS2ProgramIndexTable[wOrder].wPRIndex, u8SavedListPage, E_DATA_TTX_LIST) )
        {
            return FALSE;
        }
        SetListPageNumber(u8SavedListPage, u8ListIndex, wListPageNumber);
        SetProgramTable(m_astS2ProgramIndexTable[wOrder].wPRIndex, u8SavedListPage, E_DATA_TTX_LIST);
    }
    else
#endif
    {
        if ( TRUE != GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, u8SavedListPage, E_DATA_TTX_LIST) )
        {
            return FALSE;
        }

        SetListPageNumber(u8SavedListPage, u8ListIndex, wListPageNumber);

        SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, u8SavedListPage, E_DATA_TTX_LIST);
    }
    return TRUE;
}
#endif

static void ReassignInvalidLCN(MEMBER_SERVICETYPE bServiceType)//for Freeview NZ spec
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
            if( m_astS2ProgramIndexTable[wOrder].wLCN > NZ_MAX_LCN)
            {
                m_astS2ProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
            }
        }
    }
    else
#endif
    {
        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
            if( wOrder >= u16ProgramIndexTableArraySize )
                continue;

            if( pstProgramIndexTable[wOrder].wLCN > NZ_MAX_LCN)
            {
                pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
            }
        }
    }
}
//****************************************************************************
/// Distinguish LCN Present or Absent
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishLCNPresentOrAbsent(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    WORD wOriinalLCN = 0;


    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);

            if( 0 == m_astS2ProgramIndexTable[wOrder].wLCN )
            {
                m_astS2ProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
            }

            if( INVALID_LOGICAL_CHANNEL_NUMBER == m_astS2ProgramIndexTable[wOrder].wLCN )
            {
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ABSENT;
            }
            else
            {
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_ABSENT);
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_PRESENT;
            }
        }
    }
    else
#endif
    {
    for( wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
        {
            continue;
        }

        if( FALSE == GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wOriinalLCN, E_DATA_TS_LCN) )
            continue;
        //printf("sid %d LCN %d %d\n",m_astDTVProgramIndexTable[wOrder].wService_ID,
        //wOriinalLCN,m_astDTVProgramIndexTable[wOrder].wLCN);

        if((FALSE == msAPI_CM_GetOpMode()) && (wOriinalLCN == 0))
        {
            pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
            pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
            pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ZERO;
            continue;
        }

        if((pstProgramIndexTable[wOrder].bIsMove == 0) && (wOriinalLCN==INVALID_LOGICAL_CHANNEL_NUMBER))
        {
            pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;//assign new number for no LCN service
        }

        if((FALSE == msAPI_CM_GetOpMode()) && ( 0 == pstProgramIndexTable[wOrder].wLCN ))
        {
            pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
        }

        //If LCN beyond VALID_RANGE_LCN,it will reset among the conflict range.
        if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)&&(wOriinalLCN > VALID_RANGE_LCN)&&(wOriinalLCN < INVALID_LOGICAL_CHANNEL_NUMBER))
        {
            pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
        }

    #if 1 // Sync code from CL:7796e1cbcfafc5880c75fde32c63be8203b9877a (Mantis-1085805)
        if( (INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder].wLCN)
          ||(INVALID_LOGICAL_CHANNEL_NUMBER == wOriinalLCN)
          )
    #else
        if( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder].wLCN )
    #endif
        {
            pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
            pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ABSENT;
        }
        else
        {
            pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_ABSENT);
            pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_PRESENT;
        }
    }
    }
}

//****************************************************************************
/// Distinguish LCN Last
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishLCNLast(MEMBER_SERVICETYPE bServiceType)
{
// mantis 1296594, RiksTV Task 10:10 LCN channel incorrect (Test case: TC16032502018)
#if 1 //(NTV_FUNCTION_ENABLE)
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    for( wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( pstProgramIndexTable[wOrder].bIsSpecialService)
        {
            if(msAPI_CM_GetCountry() == E_NORWAY)
            {
                pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_LAST;
            }
        }
    }
#else
    UNUSED(bServiceType);
#endif

}

//****************************************************************************
/// Distinguish LCN Duplicate
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishLCNDuplicate(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition1;
    WORD wOrder1, wOrder2;
    WORD wProgramCount;
    CHANNEL_ATTRIBUTE Misc1, Misc2;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#if 1//(!ASTRA_HD_ENABLE)
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eCurDbSel);
#endif
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
 #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
 #endif
#endif

    memset(&Misc1, 0, sizeof(CHANNEL_ATTRIBUTE));
    memset(&Misc2, 0, sizeof(CHANNEL_ATTRIBUTE));

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
        {
            wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);

            for( wPosition2 = wPosition1+1; wPosition2 < wProgramCount; wPosition2++ )
            {
                wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

                if( (m_astS2ProgramIndexTable[wOrder1].wLCN != 0 ) &&
                (m_astS2ProgramIndexTable[wOrder1].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
                (m_astS2ProgramIndexTable[wOrder1].wLCN == m_astS2ProgramIndexTable[wOrder2].wLCN) )
                {
                    #if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
                    #endif

                  #if(ASTRA_HD_ENABLE)
                    if(m_astS2ProgramIndexTable[wOrder2].bIsScramble == m_astS2ProgramIndexTable[wOrder1].bIsScramble)
                    {
                          if(m_astS2ProgramIndexTable[wOrder2].bServiceTypePrio != m_astS2ProgramIndexTable[wOrder1].bServiceTypePrio )
                  #else
                          if ( IS_NORDIC_COUNTRY( m_eCountry ) &&(m_astS2ProgramIndexTable[wOrder2].bServiceTypePrio != m_astS2ProgramIndexTable[wOrder1].bServiceTypePrio ))
                  #endif
                         {
                                if ( m_astS2ProgramIndexTable[wOrder2].bServiceTypePrio < m_astS2ProgramIndexTable[wOrder1].bServiceTypePrio )
                                {
                                    m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                    m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                                }
                                else
                                {
                                    m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                    m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                }
                          }
                          else
                          {
                              GetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                              GetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                              {
                              #if (ENABLE_SAVE_SQI)
                                  if(SelectBestMux(&Misc1,m_astS2ProgramIndexTable[wOrder1].cIDIndex, INVALID_SQI, &Misc2, m_astS2ProgramIndexTable[wOrder2].cIDIndex, INVALID_SQI)<=0)
                              #else
                                  if( SelectBestMux(&Misc1,m_astS2ProgramIndexTable[wOrder1].cIDIndex, &Misc2,m_astS2ProgramIndexTable[wOrder2].cIDIndex) <= 0 )
                              #endif
                                  {
                                      m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                      m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                  }
                                  else
                                  {
                                      m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                      m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                  }
                              }
                          }
                      }
             #if(ASTRA_HD_ENABLE)
                }
                else
                    {
                        if(m_astS2ProgramIndexTable[wOrder1].bIsScramble == 1)
                        {
                            m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
	                        m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                        }
                        else
                        {
                            m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
	                        m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                        }
                    }
              #endif
            }
        }
    }
    else
#endif
    {
    for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        for( wOrder2 = 0; wOrder2 < u16ProgramIndexTableArraySize; wOrder2++ )
        {
            if((wOrder1 != wOrder2)&&
               (pstProgramIndexTable[wOrder1].wLCN != 0 ) &&
               (pstProgramIndexTable[wOrder1].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
               (pstProgramIndexTable[wOrder2].wLCN != 0 ) &&
               (pstProgramIndexTable[wOrder2].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
               ((pstProgramIndexTable[wOrder1].eLCNAssignmentType & E_LCN_DUPLICATE) == 0)&&
               ((pstProgramIndexTable[wOrder2].eLCNAssignmentType & E_LCN_DUPLICATE) == 0)&&
			   ((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))|| ((pstProgramIndexTable[wOrder2].bServiceType == bServiceType)&&(!(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)))) ) &&
               (pstProgramIndexTable[wOrder1].wLCN == pstProgramIndexTable[wOrder2].wLCN) )
            {
                #if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
                #endif

#if(ASTRA_HD_ENABLE)
                if(GetASTRA_HD_ENABLE())
                {
                    if(msAPI_CM_IsLCNInConflictList(pstProgramIndexTable[wOrder1].wLCN) && msAPI_CM_GetAdd2ListSelectNOState())
                    {
                        GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                        GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);

        #if (ENABLE_SAVE_SQI)
                        if(SelectBestMux(&Misc1,pstProgramIndexTable[wOrder1].cIDIndex, INVALID_SQI, &Misc2, pstProgramIndexTable[wOrder2].cIDIndex, INVALID_SQI)<=0)
        #else
                        if( SelectBestMux(&Misc1,pstProgramIndexTable[wOrder1].cIDIndex, &Misc2,pstProgramIndexTable[wOrder2].cIDIndex) <= 0 )
        #endif  //ENABLE_SAVE_SQI
                        {
                            pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                            pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                        }
                        else
                        {
                            pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                            pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                        }
                        break;

                    }
                    else
                    {
                        if(pstProgramIndexTable[wOrder2].bIsNewService == pstProgramIndexTable[wOrder1].bIsNewService)
                        {
                            if(pstProgramIndexTable[wOrder2].bIsScramble == pstProgramIndexTable[wOrder1].bIsScramble)
                            {
                                if(pstProgramIndexTable[wOrder2].bServiceTypePrio != pstProgramIndexTable[wOrder1].bServiceTypePrio )
                                {
                                    if ( pstProgramIndexTable[wOrder2].bServiceTypePrio < pstProgramIndexTable[wOrder1].bServiceTypePrio )
                                    {
                                        pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                                    }
                                    else
                                    {
                                        pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                                    }

                                }
                                else
                                {
                                    GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                                    GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                    #if (ENABLE_SAVE_SQI)
                                    if(SelectBestMux(&Misc1,pstProgramIndexTable[wOrder1].cIDIndex, INVALID_SQI, &Misc2, pstProgramIndexTable[wOrder2].cIDIndex, INVALID_SQI)<=0)
                    #else
                                    if( SelectBestMux(&Misc1,pstProgramIndexTable[wOrder1].cIDIndex, &Misc2,pstProgramIndexTable[wOrder2].cIDIndex) <= 0 )
                    #endif  //ENABLE_SAVE_SQI
                                    {
                                        pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                    }
                                    else
                                    {
                                        pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                    }
                                }
                            }
                            else
                            {
                                if(pstProgramIndexTable[wOrder1].bIsScramble == 1)
                                {
                                    pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                    pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                }
                                else
                                {
                                    pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                    pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                                }
                            }
                        }
                        else
                        {
                            if(pstProgramIndexTable[wOrder2].bIsNewService == 1)
                            {
                                pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                            }
                            else
                            {
                                pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                                pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                            }
                        }
                    }
                }
                else
#endif // ASTRA_HD_ENABLE
                if ((IS_NORDIC_COUNTRY( m_eCountry )||OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND) &&(pstProgramIndexTable[wOrder2].bVisibleServiceFlag != pstProgramIndexTable[wOrder1].bVisibleServiceFlag ))
                {
                    if ( pstProgramIndexTable[wOrder2].bVisibleServiceFlag)
                    {
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                    }
                    else
                    {
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                    }
                }
                else if ( (IS_NORDIC_COUNTRY( m_eCountry )
                        ||OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA
                        || OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND
                    #if(ENABLE_COUNTRY_SINGAPORE)
                        || OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE
                    #endif
                        || OSD_COUNTRY_SETTING == OSD_COUNTRY_KENYA
                        || OSD_COUNTRY_SETTING == OSD_COUNTRY_INDONESIA)
                        &&(pstProgramIndexTable[wOrder2].bServiceTypePrio != pstProgramIndexTable[wOrder1].bServiceTypePrio ))
                {
                    if ( pstProgramIndexTable[wOrder2].bServiceTypePrio < pstProgramIndexTable[wOrder1].bServiceTypePrio )
                    {
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                    }
                    else
                    {
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);

                    }
                }
                else if ((OSD_COUNTRY_SETTING == OSD_COUNTRY_KENYA)&&
                    (pstProgramIndexTable[wOrder2].bServiceType != pstProgramIndexTable[wOrder1].bServiceType ))
                {
                    if ( pstProgramIndexTable[wOrder2].bServiceType < pstProgramIndexTable[wOrder1].bServiceType )
                    {
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                    }
                    else
                    {
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                    }
                }
                else
                {
                    GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                    GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);

#if (NTV_FUNCTION_ENABLE)
                    if((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)&&(pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex == s_au8FavoriteNetwork[eCurDbSel]
                         && pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex != s_au8FavoriteNetwork[eCurDbSel]))
                    {
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                    }
                    else if((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)&&(pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex != s_au8FavoriteNetwork[eCurDbSel]
                         && pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex == s_au8FavoriteNetwork[eCurDbSel]))
                    {
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                    }
                    else
#endif  //NTV_FUNCTION_ENABLE
                    {
                        WORD wNID_1=INVALID_NID,wNID_2=INVALID_NID;
#if (ENABLE_SAVE_SQI)
                        WORD wSQI_1=INVALID_SQI,wSQI_2=INVALID_SQI;
#endif  //ENABLE_SAVE_SQI
                        if(pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                        {
                            wNID_1=pstNetworkTable[pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex].wNetwork_ID;
                        }
                        if(pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                        {
                            wNID_2=pstNetworkTable[pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex].wNetwork_ID;
                        }

                    #if (ENABLE_SAVE_SQI)
                        if (pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].u32Frequency != pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].u32Frequency)
                        {
                            wSQI_1 = pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].wStrengthQuality;
                            wSQI_2 = pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].wStrengthQuality;
                        }
                        if(SelectBestMux(&Misc1,wNID_1, wSQI_1,&Misc2,wNID_2, wSQI_2) <= 0)
                    #else
                        if( SelectBestMux(&Misc1,wNID_1, &Misc2,wNID_2) <= 0 )
                    #endif  //ENABLE_SAVE_SQI
                        {
                            pstProgramIndexTable[wOrder2].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                            pstProgramIndexTable[wOrder2].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                        }
                        else
                        {
                            pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~(E_LCN_ABSENT|E_LCN_LAST);
                            pstProgramIndexTable[wOrder1].eLCNAssignmentType |= (E_LCN_DUPLICATE|E_LCN_PRESENT);
                        }
                    }
                }
            }
        }
    }
    }
}

//****************************************************************************
/// Distinguish SD and HD LCN Duplicate
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishSDAndHDLCNDuplicate(MEMBER_SERVICETYPE bServiceType)
{
#if (defined SUPPORT_MPEG2_SD_ONLY || (defined AUSTRALIA && (MEMORY_MAP <= MMAP_64MB)))
    UNUSED(bServiceType);
#else
    WORD wPosition1, wPosition2;
    WORD wOrder1, wOrder2;
    WORD wProgramCount;
    CHANNEL_ATTRIBUTE Misc1, Misc2;
    BOOLEAN bGotSameService=FALSE;
    MEMBER_COUNTRY eCountry;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif


    eCountry = msAPI_CM_GetCountry();
    memset((BYTE *)&Misc1,0x00,sizeof(CHANNEL_ATTRIBUTE));
    memset((BYTE *)&Misc2,0x00,sizeof(CHANNEL_ATTRIBUTE));
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
        {
            wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
            bGotSameService=FALSE;
            GetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
            for( wPosition2 = wPosition1+1; wPosition2 < wProgramCount; wPosition2++ )
            {
                wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
                if( (m_astS2ProgramIndexTable[wOrder1].wLCN != 0 ) &&
                    (m_astS2ProgramIndexTable[wOrder1].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
                    //(m_astDTVProgramIndexTable[wOrder1].wSimu_LCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER ) &&
                    (m_astS2ProgramIndexTable[wOrder2].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
                    //(m_astDTVProgramIndexTable[wOrder2].wSimu_LCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER ) &&
                    ((m_astS2ProgramIndexTable[wOrder1].wLCN == m_astS2ProgramIndexTable[wOrder2].wSimu_LCN) ||
                    (m_astS2ProgramIndexTable[wOrder1].wSimu_LCN == m_astS2ProgramIndexTable[wOrder2].wLCN)) )
                {
                #if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
                #endif
                    bGotSameService=TRUE;
                    GetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                    if(Misc1.eVideoType != Misc2.eVideoType)
                    {
                        WORD wNewLCN;
                        WORD wQuality;
                        WORD wLCN1,wLCN2;
                        wQuality=(Misc1.eVideoType == E_VIDEOTYPE_H264) ?
                                        (Misc1.wSignalStrength &0xff) : (Misc2.wSignalStrength &0xff);
                        if(wQuality)//check if HD service in good quality
                        {
                            wLCN1=m_astS2ProgramIndexTable[wOrder1].wLCN;
                            wLCN2=m_astS2ProgramIndexTable[wOrder2].wLCN;
                            if(!(m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType &E_LCN_DUPLICATE))
                            {
                                wNewLCN=m_astS2ProgramIndexTable[wOrder2].wLCN=wLCN1;
                                SetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(wNewLCN), E_DATA_LCN);
                            }
                            if(!(m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType &E_LCN_DUPLICATE))
                            {
                                wNewLCN=m_astS2ProgramIndexTable[wOrder1].wLCN =wLCN2;
                                SetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(wNewLCN), E_DATA_LCN);
                            }
                        }
                    }
                }
            }
            if(bGotSameService == FALSE)//for no the same SD service
            {
                if (((E_FRANCE == eCountry) && (Misc1.eVideoType != E_VIDEOTYPE_MPEG)) ||
                    ((E_UK == eCountry) && (INVALID_LOGICAL_CHANNEL_NUMBER == m_astS2ProgramIndexTable[wOrder1].wLCN)))
                {
                    WORD wNewLCN;
                    wNewLCN=m_astS2ProgramIndexTable[wOrder1].wSimu_LCN;
                    if((wNewLCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER)&&(!(m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType &E_LCN_DUPLICATE)))
                    {
                        m_astS2ProgramIndexTable[wOrder1].wLCN = wNewLCN;
                        SetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(wNewLCN), E_DATA_LCN);
                    }
                }
            }
        }
    }
    else
#endif  //0//(ENABLE_S2)
    {
    for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        bGotSameService=FALSE;
        GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);

        //Fix Mantis: 1371767
        WORD wONID= msAPI_CM_GetON_ID((MEMBER_SERVICETYPE)bServiceType, wPosition1);
        if((eCountry == E_FRANCE) &&( wONID != 0x20FA))
            continue;


        for( wPosition2 = wPosition1+1; wPosition2 < wProgramCount; wPosition2++ )
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

            if (eCountry == E_FRANCE)
            {
                if(pstProgramIndexTable[wOrder1].wLCN>799||pstProgramIndexTable[wOrder2].wLCN >799)
                    break;
            }

            if( (pstProgramIndexTable[wOrder1].wLCN != 0 ) &&
                (pstProgramIndexTable[wOrder1].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
                //(m_astDTVProgramIndexTable[wOrder1].wSimu_LCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER ) &&
                (pstProgramIndexTable[wOrder2].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER ) &&
                //(m_astDTVProgramIndexTable[wOrder2].wSimu_LCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER ) &&
            ((pstProgramIndexTable[wOrder1].wLCN == pstProgramIndexTable[wOrder2].wSimu_LCN) ||
            (pstProgramIndexTable[wOrder1].wSimu_LCN == pstProgramIndexTable[wOrder2].wLCN)) )
            {
#if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
#endif  //WATCH_DOG
                if(pstProgramIndexTable[wOrder1].wSimu_LCN == pstProgramIndexTable[wOrder2].wLCN)
                {
                    bGotSameService=TRUE;
                }
                GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                //if(Misc1.eVideoType != Misc2.eVideoType)
                {
                    WORD wNewLCN;
                    WORD wQuality;
                    WORD wLCN1,wLCN2;
                    CHANNEL_ATTRIBUTE stCHAttribute;
                    wQuality=(Misc1.eVideoType == E_VIDEOTYPE_H264) ?
                                    (Misc1.wSignalStrength &0xff) : (Misc2.wSignalStrength &0xff);
                   // if(wQuality)//check if HD service in good quality
                    {
                        wLCN1=pstProgramIndexTable[wOrder1].wLCN;
                        wLCN2=pstProgramIndexTable[wOrder2].wLCN;
						//sync from chakra3 branch:c_cn_3463_dvb_nos_ziggo-dev	mantis:1101044,1101082
                        if(!(pstProgramIndexTable[wOrder2].eLCNAssignmentType &E_LCN_DUPLICATE))
                        {
                            if(pstProgramIndexTable[wOrder1].wSimu_LCN == INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER)
                            {
                                GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                                //stCHAttribute.bIsDelete = pstProgramIndexTable[wOrder1].bIsDelete = TRUE;
                                stCHAttribute.bVisibleServiceFlag = pstProgramIndexTable[wOrder1].bVisibleServiceFlag = FALSE;
                                stCHAttribute.bNumericSelectionFlag  = pstProgramIndexTable[wOrder1].bNumericSelectionFlag = FALSE;
                                SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                             }
                            wNewLCN=pstProgramIndexTable[wOrder2].wLCN=wLCN1;
                            SetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(wNewLCN), E_DATA_LCN);
                        }
                        if(!(pstProgramIndexTable[wOrder1].eLCNAssignmentType &E_LCN_DUPLICATE))
                        {
                            if(pstProgramIndexTable[wOrder2].wSimu_LCN == INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER)
                            {
                                GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                                //stCHAttribute.bIsDelete = pstProgramIndexTable[wOrder2].bIsDelete = TRUE;
                                stCHAttribute.bVisibleServiceFlag = pstProgramIndexTable[wOrder2].bVisibleServiceFlag = FALSE;
                                stCHAttribute.bNumericSelectionFlag  = pstProgramIndexTable[wOrder2].bNumericSelectionFlag = FALSE;
                                SetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                             }
                            wNewLCN=pstProgramIndexTable[wOrder1].wLCN =wLCN2;
                            SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(wNewLCN), E_DATA_LCN);
                        }
                    }
                }
            }
        }
        if(bGotSameService == FALSE)//for no the same SD service
        {
            /*
            if ((((E_FRANCE == eCountry) || (E_PORTUGAL== eCountry))  && (Misc1.eVideoType != E_VIDEOTYPE_MPEG)) ||
                ((E_UK == eCountry) && (INVALID_LOGICAL_CHANNEL_NUMBER == m_astDTVProgramIndexTable[wOrder1].wLCN)))
            */
            {
                WORD wNewLCN;
                #if 1  ////Fix Mantis: 1371767, 1400311
                if( (eCountry == E_FRANCE) && (pstProgramIndexTable[wOrder1].bServiceTypePrio == E_SERVICETYPE_PRIORITY_LOW)&&(pstProgramIndexTable[wOrder1].wLCN != INVALID_LOGICAL_CHANNEL_NUMBER) )
                {
                    wNewLCN = pstProgramIndexTable[wOrder1].wLCN;
                }
                else
                #endif
                {
                    wNewLCN = pstProgramIndexTable[wOrder1].wSimu_LCN;
                }

                if( (wNewLCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER) && ( !(pstProgramIndexTable[wOrder1].eLCNAssignmentType & E_LCN_DUPLICATE) ) )
                {
                    pstProgramIndexTable[wOrder1].wLCN = wNewLCN;
                    SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(wNewLCN), E_DATA_LCN);
                }
            }

        }
    }
    }
#endif
}

static void DistinguishSDLCNAndHDSimuLCNDuplicate(MEMBER_SERVICETYPE bServiceType, WORD wNativeON_ID)
{
#if (defined SUPPORT_MPEG2_SD_ONLY || (defined AUSTRALIA && (MEMORY_MAP <= MMAP_64MB)))
    UNUSED(bServiceType);
    UNUSED(wNativeON_ID);
#else
    WORD wPosition1, wPosition2;
    WORD wOrder1, wOrder2;
    WORD wProgramCount;
    CHANNEL_ATTRIBUTE Misc1, Misc2;
    //BOOLEAN bGotSameService=FALSE;
    MEMBER_COUNTRY eCountry;
    WORD wHDSimuLCN;
    WORD wOriginalNetwork_ID = INVALID_ON_ID; // Coverity 218310

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

    eCountry = msAPI_CM_GetCountry();

    if(eCountry == E_UK)
    {
        wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
            {
                wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
                //bGotSameService=FALSE;
                GetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                GetIDTable(m_astS2ProgramIndexTable[wOrder1].cIDIndex, (BYTE *)&wOriginalNetwork_ID, E_DATA_ON_ID);
                if(Misc1.eVideoType != E_VIDEOTYPE_H264 || wOriginalNetwork_ID != wNativeON_ID)
                {
                    continue;
                }

                wHDSimuLCN = m_astS2ProgramIndexTable[wOrder1].wSimu_LCN;
                if(wHDSimuLCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER && wHDSimuLCN > 0)
                {
                    for( wPosition2 = 0; wPosition2 < wProgramCount; wPosition2++ )
                    {
                        if (wPosition2 == wPosition1) continue;

                        wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
                        GetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                        if((Misc2.eVideoType != E_VIDEOTYPE_H264) && (wHDSimuLCN == m_astS2ProgramIndexTable[wOrder2].wLCN))
                        {
                            if(!(m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType &E_LCN_DUPLICATE))
                            {
                                m_astS2ProgramIndexTable[wOrder2].wLCN = m_astS2ProgramIndexTable[wOrder1].wLCN;
                                SetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(m_astS2ProgramIndexTable[wOrder2].wLCN), E_DATA_LCN);
                            }
                        }
                    }
                    if(!(m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType &E_LCN_DUPLICATE))
                    {
                        m_astS2ProgramIndexTable[wOrder1].wLCN = wHDSimuLCN;
                        if(FALSE == SetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(m_astS2ProgramIndexTable[wOrder1].wLCN), E_DATA_LCN))
                        {
                            //printf("DATA LCN store fail\n");
                        }
                    }
                }
            }
        }
        else
    #endif
        {
        for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
        {
            wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
            //bGotSameService=FALSE;
            GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
            GetIDTable(pstProgramIndexTable[wOrder1].cIDIndex, (BYTE *)&wOriginalNetwork_ID, E_DATA_ON_ID);
            if((pstProgramIndexTable[wOrder1].bServiceTypePrio >= E_SERVICETYPE_PRIORITY_LOW) || wOriginalNetwork_ID != wNativeON_ID)
            {
                continue;
            }

            wHDSimuLCN = pstProgramIndexTable[wOrder1].wSimu_LCN;
            if(wHDSimuLCN != INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER && wHDSimuLCN > 0)
            {
                for( wPosition2 = 0; wPosition2 < wProgramCount; wPosition2++ )
                {
                    if (wPosition2 == wPosition1) continue;

                    wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
                    GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                    if((pstProgramIndexTable[wOrder2].bServiceTypePrio >= E_SI_SERVICETYPE_PRIORITY_LOW) && (wHDSimuLCN == pstProgramIndexTable[wOrder2].wLCN))
                    {
                        if(!(pstProgramIndexTable[wOrder2].eLCNAssignmentType &E_LCN_DUPLICATE))
                        {
                            pstProgramIndexTable[wOrder2].wLCN = pstProgramIndexTable[wOrder1].wLCN;
                            SetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(pstProgramIndexTable[wOrder2].wLCN), E_DATA_LCN);
                        }
                    }
                }
                if(!(pstProgramIndexTable[wOrder1].eLCNAssignmentType &E_LCN_DUPLICATE))
                {
                    pstProgramIndexTable[wOrder1].wLCN = wHDSimuLCN;
                    if(FALSE == SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(pstProgramIndexTable[wOrder1].wLCN), E_DATA_LCN))
                    {
                        //printf("DATA LCN store fail\n");
                    }
                }
            }
        }
    }
    }
#endif
}
//****************************************************************************
/// Distinguish Same Service
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishSameService(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition1, wPosition2;
    WORD wOrder1, wOrder2;
    WORD wProgramCount,wIDs_1=INVALID_TS_ID;
    CHANNEL_ATTRIBUTE Misc1, Misc2;
    memset((BYTE *)&Misc1,0x00,sizeof(CHANNEL_ATTRIBUTE));
    memset((BYTE *)&Misc2,0x00,sizeof(CHANNEL_ATTRIBUTE));
    BOOLEAN bIsSameService = FALSE;


#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);

            if(_bOnlyUpdateCurTS)
            {
                GetIDTable(m_astS2ProgramIndexTable[wOrder1].cIDIndex, (BYTE *)&wIDs_1, E_DATA_TS_ID);

                if(_wCurTS_ID != wIDs_1)
                {
                    continue;
                }
            }

            for(wPosition2=wPosition1+1; wPosition2 < wProgramCount; wPosition2++)
            {
                wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
                if(OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)
                {
                    bIsSameService = AreOrdersSameService(wOrder1, wOrder2, FALSE);
                }
                else
                {
                    bIsSameService = AreOrdersSameService(wOrder1, wOrder2, TRUE);
                }
                if( TRUE == bIsSameService)
                {
                    GetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                    GetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
                    {
#if (ENABLE_SAVE_SQI)
                     if(SelectBestMux(&Misc1,m_astS2ProgramIndexTable[wOrder1].cIDIndex, INVALID_SQI, &Misc2, m_astS2ProgramIndexTable[wOrder2].cIDIndex, INVALID_SQI)<=0)
#else
                     if( SelectBestMux(&Misc1,m_astS2ProgramIndexTable[wOrder1].cIDIndex, &Misc2,m_astS2ProgramIndexTable[wOrder2].cIDIndex) <= 0 )
#endif
                        {
                            m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                        }
                        else
                        {
                            m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                        }
                    }
                }
            }
        }
    }
    else
#endif
    {
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        #if ( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
        #endif

        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);

        if(_bOnlyUpdateCurTS)
        {
            GetIDTable(pstProgramIndexTable[wOrder1].cIDIndex, (BYTE *)&wIDs_1, E_DATA_TS_ID);

            if(_wCurTS_ID != wIDs_1)
            {
                continue;
            }
        }

        for(wPosition2=wPosition1+1; wPosition2 < wProgramCount; wPosition2++)
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

            bIsSameService = AreOrdersSameService(wOrder1, wOrder2, IS_SID_UNIQUE_COUNTRY(m_eCountry) ? FALSE : TRUE);


            if( TRUE == bIsSameService)
            {
                GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
#if 0//(NTV_FUNCTION_ENABLE)
                if((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)&&(pMuxTable[m_astDTVProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex == _cFavoriteNetwork
                    && pMuxTable[m_astDTVProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex != _cFavoriteNetwork))
                {
                    m_astDTVProgramIndexTable[wOrder2].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                }
                else if((OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY)&&(pMuxTable[m_astDTVProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex != _cFavoriteNetwork
                    && pMuxTable[m_astDTVProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex == _cFavoriteNetwork))
                {
                    m_astDTVProgramIndexTable[wOrder1].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                }
                else
#endif
                {
                    WORD wNID_1=INVALID_NID,wNID_2=INVALID_NID;
#if (ENABLE_SAVE_SQI)
                    WORD wSQI_1=INVALID_SQI, wSQI_2=INVALID_SQI;
#endif

                    if(pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                    {
                        wNID_1=pstNetworkTable[pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex].wNetwork_ID;
                    }
                    if(pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                    {
                        wNID_2=pstNetworkTable[pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex].wNetwork_ID;
                    }


                #if (ENABLE_SAVE_SQI)
                    if (pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].u32Frequency != pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].u32Frequency)
                    {
                        wSQI_1 = pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].wStrengthQuality;
                        wSQI_2 = pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].wStrengthQuality;
                    }
                    if(SelectBestMux(&Misc1,wNID_1, wSQI_1,&Misc2,wNID_2, wSQI_2) <= 0)
                #else
                    if(SelectBestMux(&Misc1,wNID_1,&Misc2,wNID_2) <= 0)
                #endif  //ENABLE_SAVE_SQI
                    {
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                        pstProgramIndexTable[wOrder1].bIsDelete = 0;
                    }
                    else
                    {
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                        pstProgramIndexTable[wOrder2].bIsDelete = 0;
                    }
            }
        }
    }
    }
    }
}

static void DistinguishLCNSameService(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition1, wPosition2;
    WORD wOrder1, wOrder2;
    WORD wProgramCount;
    CHANNEL_ATTRIBUTE Misc1, Misc2;
    WORD wLCN1, wLCN2;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    memset(&Misc1, 0, sizeof(CHANNEL_ATTRIBUTE));
    memset(&Misc2, 0, sizeof(CHANNEL_ATTRIBUTE));

    wLCN1 = INVALID_LOGICAL_CHANNEL_NUMBER;
    wLCN2 = INVALID_LOGICAL_CHANNEL_NUMBER;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif
            wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
            for( wPosition2 = wPosition1+1; wPosition2 < wProgramCount; wPosition2++ )
            {
                wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
                wLCN1 = m_astS2ProgramIndexTable[wOrder1].wLCN;
                wLCN2 = m_astS2ProgramIndexTable[wOrder2].wLCN;
                if( (wLCN1 != 0 ) && (wLCN1 != INVALID_LOGICAL_CHANNEL_NUMBER ) && (wLCN1 == wLCN2) )
                {
                    #if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
                    #endif
                    if( TRUE == AreOrdersSameService(wOrder1, wOrder2, FALSE) )
                    {
                        GetProgramTable(m_astS2ProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                        GetProgramTable(m_astS2ProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);
#if (ENABLE_SAVE_SQI)
                       if(SelectBestMux(&Misc1,m_astS2ProgramIndexTable[wOrder1].cIDIndex, INVALID_SQI, &Misc2, m_astS2ProgramIndexTable[wOrder2].cIDIndex, INVALID_SQI)<=0)
#else
                       if( SelectBestMux(&Misc1,m_astS2ProgramIndexTable[wOrder1].cIDIndex, &Misc2,m_astS2ProgramIndexTable[wOrder2].cIDIndex) <= 0 )
#endif
                        {
                            m_astS2ProgramIndexTable[wOrder2].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                        }
                        else
                        {
                            m_astS2ProgramIndexTable[wOrder1].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                        }
                    }
                }
            }
        }
    }
    else
#endif
    {
    for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
    {
        #if ( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
        #endif
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        for( wPosition2 = wPosition1+1; wPosition2 < wProgramCount; wPosition2++ )
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
            wLCN1 = pstProgramIndexTable[wOrder1].wLCN;
            wLCN2 = pstProgramIndexTable[wOrder2].wLCN;
            if(((TRUE == msAPI_CM_GetOpMode()) || (wLCN1 != 0 )) && (wLCN1 != INVALID_LOGICAL_CHANNEL_NUMBER ) && (wLCN1 == wLCN2) )
            {
                #if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
                #endif
#if (ENABLE_CI_PLUS)
                if((TRUE == msAPI_CM_GetOpMode()) /*&& ( TRUE == AreOrdersSameService(wOrder1, wOrder2, TRUE)*/
                    || ((FALSE == msAPI_CM_GetOpMode()) && ( TRUE == AreOrdersSameService(wOrder1, wOrder2, FALSE))))
#else
                //[NZ Freeview] NZ Transmission Rule Section 6.1, remove the duplicate LCN service
                //if( TRUE == AreOrdersSameService(wOrder1, wOrder2, FALSE) )
#endif
                {
                    GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);
                    GetProgramTable(pstProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&Misc2, E_DATA_MISC);


                    WORD wNID_1=INVALID_NID,wNID_2=INVALID_NID;
#if (ENABLE_SAVE_SQI)
                    WORD wSQI_1=INVALID_SQI, wSQI_2=INVALID_SQI;
#endif

                    if(pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                    {
                        wNID_1=pstNetworkTable[pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex].wNetwork_ID;
                    }
                    if(pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex < u16NetWorkTableArraySize)
                    {
                        wNID_2=pstNetworkTable[pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cNetWorkIndex].wNetwork_ID;
                    }

                #if (ENABLE_SAVE_SQI)
                    if (pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].u32Frequency != pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].u32Frequency)
                    {
                        wSQI_1 = pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].wStrengthQuality;
                        wSQI_2 = pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].wStrengthQuality;
                    }
                    if(SelectBestMux(&Misc1,wNID_1, wSQI_1,&Misc2,wNID_2, wSQI_2) <= 0)
                #else
                    if( SelectBestMux(&Misc1,wNID_1, &Misc2,wNID_2) <= 0 )
                #endif  //ENABLE_SAVE_SQI
                    {
                        pstProgramIndexTable[wOrder2].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                    }
                    else
                    {
                        pstProgramIndexTable[wOrder1].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                    }
                }
            }
        }
    }
}
}

//****************************************************************************
/// Distinguish NotNative ON_ID List
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wNativeON_IDList \b IN: Native ON_ID List
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishNotNativeON_IDS(MEMBER_SERVICETYPE bServiceType, WORD * pNativeON_IDList, U8 u8ListSize)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    WORD wOriginalNetwork_ID=INVALID_ON_ID;
    U16 u16IDIndex;
    BOOL bNative = FALSE;
    U8 ON_IDIndex = 0;


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);


#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
            GetIDTable(m_astS2ProgramIndexTable[wOrder].cIDIndex, (BYTE *)&wOriginalNetwork_ID, E_DATA_ON_ID);
            if( wNativeON_ID != wOriginalNetwork_ID )
            {
                //m_astDTVProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_NOT_NATIVE_ON_ID;
                m_astS2ProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ABSENT;
            }
        }
    }
    else
#endif
    {

        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            msAPI_Timer_ResetWDT();
            bNative = FALSE;

            wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
            if( wOrder >= u16ProgramIndexTableArraySize )
                continue;

            u16IDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if( u16IDIndex >= u16IDTableArraySize )
                continue;

            if( FALSE == GetIDTable(u16IDIndex, (BYTE *)&wOriginalNetwork_ID, E_DATA_ON_ID) )
                continue;

            for(ON_IDIndex = 0; ON_IDIndex < u8ListSize; ON_IDIndex++)
            {
                if( pNativeON_IDList[ON_IDIndex] == wOriginalNetwork_ID )
                {
                    bNative = TRUE;
                    break;
                }
            }
            if( FALSE == bNative )
            {
                //pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_NOT_NATIVE_ON_ID;

                pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
                pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
                pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ABSENT;
            }
        }
    }
}

//****************************************************************************
/// Distinguish NotNative ON_ID
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wNativeON_ID \b IN: Native ON_ID
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void DistinguishNotNativeON_ID(MEMBER_SERVICETYPE bServiceType, WORD wNativeON_ID)
{
#if 1
    DistinguishNotNativeON_IDS(bServiceType, &wNativeON_ID, 1);
#else
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    WORD wOriginalNetwork_ID=INVALID_ON_ID;
    U16 u16IDIndex;


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);


#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
            GetIDTable(m_astS2ProgramIndexTable[wOrder].cIDIndex, (BYTE *)&wOriginalNetwork_ID, E_DATA_ON_ID);
            if( wNativeON_ID != wOriginalNetwork_ID )
            {
                //m_astDTVProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_NOT_NATIVE_ON_ID;
                m_astS2ProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
                m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ABSENT;
            }
        }
    }
    else
#endif
    {

        for( wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            msAPI_Timer_ResetWDT();

            wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
            if( wOrder >= u16ProgramIndexTableArraySize )
                continue;

            u16IDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if( u16IDIndex >= u16IDTableArraySize )
                continue;

            if( FALSE == GetIDTable(u16IDIndex, (BYTE *)&wOriginalNetwork_ID, E_DATA_ON_ID) )
                continue;

            if( wNativeON_ID != wOriginalNetwork_ID )
            {
                //pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_NOT_NATIVE_ON_ID;

                pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
                pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_PRESENT|E_LCN_DUPLICATE);
                pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_ABSENT;
            }
        }
    }
#endif
}

static void RestoreOriginalLCN(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition,wPosition2,wPRIndex;
    WORD wOrder,wOrder2;
    WORD wProgramCount;
    WORD wOriinalLCN = 0;
    BOOLEAN bLCNExit=FALSE;

    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    for( wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        msAPI_Timer_ResetWDT();

        bLCNExit=FALSE;
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        if(pstDTVProgramIndexTable[wOrder].bIsMove)
        {
            continue;
        }
        if( pstDTVProgramIndexTable[wOrder].wLCN == INVALID_LOGICAL_CHANNEL_NUMBER)
        {
            continue;
        }
        wPRIndex = pstDTVProgramIndexTable[wOrder].wPRIndex;
        GetProgramTable(wPRIndex, (BYTE *)&wOriinalLCN, E_DATA_TS_LCN);

        if( (pstDTVProgramIndexTable[wOrder].wLCN == wOriinalLCN)
            || (wOriinalLCN == INVALID_LOGICAL_CHANNEL_NUMBER))
        {
            continue;
        }

        for( wPosition2 = 0; wPosition2 < wProgramCount; wPosition2++)
        {
            msAPI_Timer_ResetWDT();

            if(wPosition == wPosition2)
            {
                continue;
            }
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
            if(pstDTVProgramIndexTable[wOrder2].wLCN == wOriinalLCN)
            {
                bLCNExit=TRUE;
                break;
            }
        }
        if(!bLCNExit)
        {
            wPRIndex = pstDTVProgramIndexTable[wOrder].wPRIndex;
            //printf("restore LCN org %d new %d\n",m_astDTVProgramIndexTable[wOrder].wLCN,wOriinalLCN);
            pstDTVProgramIndexTable[wOrder].wLCN = wOriinalLCN;
            SetProgramTable(wPRIndex, (BYTE *)&wOriinalLCN, E_DATA_LCN);
        }
    }
}

//****************************************************************************
/// Assign New LCN
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param eAssignmentType \b IN: Assignment Type
/// -@see E_LCN_ASSIGNMENT_TYPE
/// @param wBeginFromLCN \b IN: begin LCN
/// @param wEndToLCN \b IN: End LCN
/// @param wBeginOfNewLCN \b IN: Begin Of New LCN
/// @param wEndOfNewLCN \b IN: End Of New LCN
/// @param wNewAssignableLCN \b IN: New Assignable LCN
/// @return BOOLEAN: Function execution result
//****************************************************************************
static void AssignNewLCN(MEMBER_SERVICETYPE bServiceType, E_LCN_ASSIGNMENT_TYPE eAssignmentType, WORD wBeginFromLCN, WORD wEndToLCN, WORD wBeginOfNewLCN, WORD wEndOfNewLCN, WORD wNewAssignableLCN)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    WORD wIndex;
    BOOLEAN bIsDeletionRequired;
    CHANNEL_ATTRIBUTE stCHAttribute;

    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    bIsDeletionRequired = FALSE;

    if( 0 == wBeginFromLCN &&
        0 == wEndToLCN &&
        0 == wBeginOfNewLCN &&
        0 == wEndOfNewLCN &&
        0 == wNewAssignableLCN )
    {
        bIsDeletionRequired = TRUE;
    }

    if( wNewAssignableLCN < wBeginOfNewLCN )
    {
        wNewAssignableLCN = wBeginOfNewLCN;
    }

    //assign new unused LCN within manual assignned range when wNewAssignableLCN > wEndOfNewLCN
    if( wNewAssignableLCN > wEndOfNewLCN)
    {
        for( wIndex = wBeginOfNewLCN; wIndex <= wEndOfNewLCN; wIndex++ )
        {
            for( wPosition = 0; wPosition < wProgramCount; wPosition++ )
            {
                wOrder = ConvertPositionToOrder(bServiceType, wPosition);
            #if 0//(ENABLE_S2)
                if(IsS2InUse())
                {
                    if(m_astS2ProgramIndexTable[wOrder].wLCN == wIndex)
                    {
                        break;
                    }
                }
                else
            #endif
                {
                    if(pstDTVProgramIndexTable[wOrder].wLCN == wIndex)
                    {
                        break;
                    }
                }
            }
            if (wPosition == wProgramCount)
            {
                wNewAssignableLCN = wIndex;
                //printf("new assigned LCN is %d\n", wNewAssignableLCN);
                break;
            }
        }
    }

    switch(eAssignmentType)
    {
    case E_LCN_DUPLICATE:
        for(wPosition=0; wPosition < wProgramCount ; wPosition++)
        {
            msAPI_Timer_ResetWDT();

            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        #if(ENABLE_S2)
            if(IsS2InUse())
            {
                if( ((E_LCN_DUPLICATE|E_LCN_PRESENT) == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType) &&
                    ((wBeginFromLCN <= pstDTVProgramIndexTable[wOrder].wLCN) ||
                     (pstDTVProgramIndexTable[wOrder].wLCN <= wEndToLCN)) )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;

                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_DUPLICATE|E_LCN_PRESENT);
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                        {
                            break;
                        }
                    }
                }
            }
            else
        #endif
            {
                if( ((E_LCN_DUPLICATE|E_LCN_PRESENT) == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType) &&
                    ((wBeginFromLCN <= pstDTVProgramIndexTable[wOrder].wLCN) ||
                     (pstDTVProgramIndexTable[wOrder].wLCN <= wEndToLCN)) )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;

                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_DUPLICATE|E_LCN_PRESENT);
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                        {
                            break;
                        }
                    }
                }
            }
        }
        break;

    case E_LCN_ABSENT:
        for(wPosition=0; wPosition < wProgramCount ; wPosition++)
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        #if(ENABLE_S2)
            if(IsS2InUse())
            {
                if( E_LCN_ABSENT == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;
                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ABSENT;
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                        {
                            break;
                        }
                    }
                }
            }
            else
        #endif
            {
                if( E_LCN_ABSENT == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;

                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ABSENT;
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                            break;
                    }
                }
            }
        }
        break;

    case E_LCN_ZERO:
        for(wPosition=0; wPosition < wProgramCount ; wPosition++)
        {
            msAPI_Timer_ResetWDT();

            wOrder = ConvertPositionToOrder(bServiceType, wPosition);

            if( E_LCN_ZERO == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
            {
                if( TRUE == bIsDeletionRequired )
                {
                    pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;

                    GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    stCHAttribute.bIsDelete = TRUE;
                    SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                }
                else
                {
                #if 1 // Sync code from CL:7796e1cbcfafc5880c75fde32c63be8203b9877a (Mantis-1085805)
                    if( (OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND)
                      ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_GERMANY)
                      || (OSD_COUNTRY_SETTING == OSD_COUNTRY_NETHERLANDS)
                      )
                #else
                    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND)
                #endif
                    {
                        pstDTVProgramIndexTable[wOrder].bVisibleServiceFlag = FALSE;
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ZERO;
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ZERO;
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                            break;
                    }
                }
            }
        }
        break;

    case E_LCN_SAME_SERVICE:
        for(wPosition=0; wPosition < wProgramCount ; wPosition++)
        {
            msAPI_Timer_ResetWDT();

            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        #if(ENABLE_S2)
            if(IsS2InUse())
            {
                if( E_LCN_SAME_SERVICE & pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;
                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_SAME_SERVICE;
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                        {
                            break;
                        }
                    }
                }
            }
            else
        #endif
            {
                if( E_LCN_SAME_SERVICE & pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;
                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                        pstDTVProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_SAME_SERVICE;
                        wNewAssignableLCN++;
                        if( wNewAssignableLCN > wEndOfNewLCN )
                            break;
                    }
                }
            }
        }
        break;

    case E_LCN_LAST:
    #if(ENABLE_S2)
        if(IsS2InUse())
        {
            WORD wMaxLCN = 0;
            WORD NewAssignLastLCN;
            //get special service max lcn
            for(wPosition=0; wPosition < wProgramCount ; wPosition++)
            {
#if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
#endif
                wOrder = ConvertPositionToOrder(bServiceType, wPosition);
                if( E_LCN_LAST & pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                {
                    if(pstDTVProgramIndexTable[wOrder].wLCN > wMaxLCN)
                    {
                        wMaxLCN = pstDTVProgramIndexTable[wOrder].wLCN;
                    }
                }
            }
            NewAssignLastLCN = wMaxLCN + 1;
            if(NewAssignLastLCN < wBeginOfNewLCN || NewAssignLastLCN > wEndOfNewLCN)
            {
                break;
            }
            //Special service duplicated lcn reassign lcn order
            for(wPosition=0; wPosition < wProgramCount ; wPosition++)
            {
            #if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
            #endif

                wOrder = ConvertPositionToOrder(bServiceType, wPosition);

                if( ((E_LCN_DUPLICATE|E_LCN_PRESENT|E_LCN_LAST) == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType) &&
                    ((wBeginFromLCN <= pstDTVProgramIndexTable[wOrder].wLCN) ||
                     (pstDTVProgramIndexTable[wOrder].wLCN <= wEndToLCN)) )
                {
                    if( TRUE == bIsDeletionRequired )
                    {
                        pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;

                        GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        stCHAttribute.bIsDelete = TRUE;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    }
                    else
                    {
                        pstDTVProgramIndexTable[wOrder].wLCN = NewAssignLastLCN;
                        SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(NewAssignLastLCN), E_DATA_LCN);
                        NewAssignLastLCN++;

                        if( NewAssignLastLCN > wEndOfNewLCN )
                        {
                            break;
                        }
                    }
                }
            }
            if(wNewAssignableLCN <= wBeginOfNewLCN)
            {
                break;
            }
            while(1)
            {
                WORD wMinimalLCN,wOrderMinimalLCN=0;
                wMinimalLCN=INVALID_LOGICAL_CHANNEL_NUMBER;
                for(wPosition=0; wPosition < wProgramCount ; wPosition++)
                {
                #if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
                #endif
                    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
                    if( E_LCN_LAST & pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                    {
                        if(pstDTVProgramIndexTable[wOrder].wLCN < wMinimalLCN)
                        {
                            wMinimalLCN=pstDTVProgramIndexTable[wOrder].wLCN;
                            wOrderMinimalLCN=wOrder;
                        }
                    }
                }

                if(wMinimalLCN != INVALID_LOGICAL_CHANNEL_NUMBER && wMinimalLCN < wNewAssignableLCN)
                {
                    pstDTVProgramIndexTable[wOrderMinimalLCN].eLCNAssignmentType &= ~E_LCN_LAST;
                    pstDTVProgramIndexTable[wOrderMinimalLCN].wLCN = wNewAssignableLCN;
                    SetProgramTable(pstDTVProgramIndexTable[wOrderMinimalLCN].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                    wNewAssignableLCN++;
                    if(wNewAssignableLCN > wEndOfNewLCN )
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
    #endif
     {
                WORD wMaxLCN = 0;
                WORD NewAssignLastLCN;
                //get special service max lcn
                for(wPosition=0; wPosition < wProgramCount ; wPosition++)
                {
#if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
#endif
                    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
                    if( E_LCN_LAST & pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                    {
                        if(pstDTVProgramIndexTable[wOrder].wLCN > wMaxLCN)
                        {
                            wMaxLCN = pstDTVProgramIndexTable[wOrder].wLCN;
                        }
                    }
                }
                NewAssignLastLCN = wMaxLCN + 1;
                if(NewAssignLastLCN < wBeginOfNewLCN || NewAssignLastLCN > wEndOfNewLCN)
                    break;
                //Special service duplicated lcn reassign lcn order
                for(wPosition=0; wPosition < wProgramCount ; wPosition++)
                {
                #if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
                #endif

                    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

                    if( ((E_LCN_DUPLICATE|E_LCN_PRESENT|E_LCN_LAST) == pstDTVProgramIndexTable[wOrder].eLCNAssignmentType) &&
                        ((wBeginFromLCN <= pstDTVProgramIndexTable[wOrder].wLCN) ||
                         (pstDTVProgramIndexTable[wOrder].wLCN <= wEndToLCN)) )
                    {
                        if( TRUE == bIsDeletionRequired )
                        {
                            pstDTVProgramIndexTable[wOrder].bIsDelete = TRUE;

                            GetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                            stCHAttribute.bIsDelete = TRUE;
                            SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                        }
                        else
                        {
                            pstDTVProgramIndexTable[wOrder].wLCN = NewAssignLastLCN;
                            SetProgramTable(pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(NewAssignLastLCN), E_DATA_LCN);
                            NewAssignLastLCN++;

                            if( NewAssignLastLCN > wEndOfNewLCN )
                            {
                                break;
                            }
                        }
                    }
                }
            if(wNewAssignableLCN <= wBeginOfNewLCN)
            {
                break;
            }
            while(1)
            {
                WORD wMinimalLCN,wOrderMinimalLCN=0;
                wMinimalLCN=INVALID_LOGICAL_CHANNEL_NUMBER;
                for(wPosition=0; wPosition < wProgramCount ; wPosition++)
                {
#if ( WATCH_DOG == ENABLE )
                    msAPI_Timer_ResetWDT();
#endif
                    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
                    if( E_LCN_LAST & pstDTVProgramIndexTable[wOrder].eLCNAssignmentType )
                    {
                        if(pstDTVProgramIndexTable[wOrder].wLCN < wMinimalLCN)
                        {
                            wMinimalLCN=pstDTVProgramIndexTable[wOrder].wLCN;
                            wOrderMinimalLCN=wOrder;
                        }
                    }
                }

                if(wMinimalLCN != INVALID_LOGICAL_CHANNEL_NUMBER && wMinimalLCN < wNewAssignableLCN)
                {
                    pstDTVProgramIndexTable[wOrderMinimalLCN].eLCNAssignmentType &= ~E_LCN_LAST;
                    pstDTVProgramIndexTable[wOrderMinimalLCN].wLCN = wNewAssignableLCN;
                    SetProgramTable(pstDTVProgramIndexTable[wOrderMinimalLCN].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                    wNewAssignableLCN++;
                    if(wNewAssignableLCN > wEndOfNewLCN )
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                        break;
                }
            }
        }
        break;

    default:
        break;
    }
}

//****************************************************************************
/// Assign New LCN for LCN Sorting with service type
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// -@see E_LCN_ASSIGNMENT_TYPE
/// @param wBeginFromLCN \b IN: begin LCN
/// @param wEndToLCN \b IN: End LCN
/// @param wBeginOfNewLCN \b IN: Begin Of New LCN
/// @param wEndOfNewLCN \b IN: End Of New LCN
/// @param wNewAssignableLCN \b IN: New Assignable LCN
//****************************************************************************
void AssignNewLCNforSorting(MEMBER_SERVICETYPE bServiceType, WORD wBeginFromLCN, WORD wEndToLCN, WORD wBeginOfNewLCN, WORD wEndOfNewLCN, WORD wLastLCN)
{
    WORD wOrder;
    WORD wIndex;
    WORD wNewAssignableLCN = 0; //Coverity 188447
    WORD wProgramCount = 0;
    WORD wMinOrder,wMinSID,wMinPriority,wMinMux,wCurrentSID,wCurrentPriority,wCurrentMux,wOrder1,wOrder2;
    BOOLEAN bIsDeletionRequired=0,bIsSortbyPriority=0,bIsSortbyMux=0;
    BOOLEAN bLCNFull = FALSE;
    CHANNEL_ATTRIBUTE stCHAttribute;
    E_LCN_ASSIGNMENT_TYPE eAssignmentType;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    bIsDeletionRequired = FALSE;

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    if( 0 == wBeginFromLCN &&
        0 == wEndToLCN &&
        0 == wBeginOfNewLCN &&
        0 == wEndOfNewLCN)
    {
        bIsDeletionRequired = TRUE;
    }

    wNewAssignableLCN = wBeginOfNewLCN;
    for( wOrder1 = 0; wOrder1 < wProgramCount; wOrder1++ )
    {
        if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder1].wPRIndex))
        {
            continue;
        }

        eAssignmentType = pstProgramIndexTable[wOrder1].eLCNAssignmentType;
        //UAE spec, LCN 0 denotes Invisible program
        if(IS_MIDDLEEAST_COUNTRY(OSD_COUNTRY_SETTING)&&(eAssignmentType == E_LCN_ZERO))
        {
            pstProgramIndexTable[wOrder1].bVisibleServiceFlag = FALSE;
            pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~E_LCN_ZERO;
            continue;
        }

        if((OSD_COUNTRY_SETTING == OSD_COUNTRY_UNITED_ARAB_EMIRATES)
        ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA)
#if(ENABLE_COUNTRY_SINGAPORE)
        ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE)
#endif
        ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_INDONESIA))
        {
            bIsSortbyPriority =TRUE; // choose sort LCN by service type priority for LCN behind 800
        }
#if (ENABLE_COUNTRY_GHANA)
        else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_GHANA)
        {
            bIsSortbyMux =TRUE;     // choose sort LCN by mux for LCN behind 800
        }
#endif
        if((eAssignmentType == (E_LCN_PRESENT|E_LCN_DUPLICATE))||(eAssignmentType == E_LCN_ABSENT)||(eAssignmentType == E_LCN_ZERO))
        {
            wMinOrder    = wOrder1;
            wMinSID      = pstProgramIndexTable[wOrder1].wService_ID;
            wMinPriority = pstProgramIndexTable[wOrder1].bServiceTypePrio;
            wMinMux      = pstProgramIndexTable[wOrder1].cIDIndex;

            if( TRUE == bIsDeletionRequired )
            {
                pstProgramIndexTable[wOrder1].bIsDelete = TRUE;

                GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                stCHAttribute.bIsDelete = TRUE;
                SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                continue;
            }
            else
            {
                for(wOrder2=wOrder1+1; wOrder2 < wProgramCount; wOrder2++)
                {
                    if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder2].wPRIndex))
                    {
                        continue;
                    }

                    eAssignmentType = pstProgramIndexTable[wOrder2].eLCNAssignmentType;

                    if((eAssignmentType == (E_LCN_PRESENT|E_LCN_DUPLICATE))||(eAssignmentType == E_LCN_ABSENT)||(eAssignmentType == E_LCN_ZERO))
                    {
                        if(bIsSortbyPriority) // sort by service type priority
                        {   //the higher the priority , the smaller the vaule.
                            wCurrentPriority = pstProgramIndexTable[wOrder2].bServiceTypePrio;

                            if( wMinPriority > wCurrentPriority )
                            {
                                wMinPriority = wCurrentPriority;
                                wMinOrder = wOrder2;
                            }
                        }
                        else if(bIsSortbyMux) // sort by mux
                        {
                            wCurrentMux = pstProgramIndexTable[wOrder2].cIDIndex;
                            if( wMinMux > wCurrentMux )
                            {
                                wMinMux = wCurrentMux;
                                wMinOrder = wOrder2;
                            }
                        }
                        else // sort by service id
                        {
                            wCurrentSID = pstProgramIndexTable[wOrder2].wService_ID;
                            if( wMinSID > wCurrentSID )
                            {
                                wMinSID = wCurrentSID;
                                wMinOrder = wOrder2;
                            }
                        }
                    }
                }

                if( wMinOrder != wOrder1 )
                {
                    SwapProgram(wMinOrder, wOrder1);// swap the data in array, so LCN and order sort from lowest to high
                }

                wOrder = wOrder1;
                pstProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                switch(pstProgramIndexTable[wOrder].eLCNAssignmentType)
                {
                    case (E_LCN_DUPLICATE|E_LCN_PRESENT):
                        pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_DUPLICATE|E_LCN_PRESENT);
                    break;
                    case E_LCN_ABSENT:
                        pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ABSENT;;
                    break;
                    case E_LCN_ZERO:
                        pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ZERO;
                    break;
                    default :
                    break;
                }

                if (!bLCNFull&&(wNewAssignableLCN < wEndOfNewLCN))
                {
                    wNewAssignableLCN++;
                }
                else
                {
                    bLCNFull = TRUE;
                    if(wNewAssignableLCN == wEndOfNewLCN)
                    {
                        wNewAssignableLCN = wBeginOfNewLCN;
                    }
                    // if the new LCN range is full, it will rank from (wNewAssignableLCN-1) in descending order
                    wNewAssignableLCN--;
                }
                //The LCN may be already used by other valid service. Before it is assigned to service, it should be checked.
                if(wNewAssignableLCN <= wLastLCN)
                {
                    for( wIndex = wNewAssignableLCN; wIndex > 1; wIndex-- )
                    {
                        for( wOrder = 0; wOrder < u16ProgramIndexTableArraySize; wOrder++ )
                        {
                            if(pstProgramIndexTable[wOrder].wLCN == wIndex)
                            {
                                break;
                            }
                        }

                        if (wOrder == u16ProgramIndexTableArraySize)
                        {
                            //it is the valid LCN number without used by other service
                            wNewAssignableLCN = wIndex;
                            break;
                        }
                    }
                }
            }
        }
    }
}

//****************************************************************************
/// Assign New LCN for LCN Sorting without service type
/// @param eAssignmentType \b IN: Assignment Type
/// -@see E_LCN_ASSIGNMENT_TYPE
/// @param wBeginFromLCN \b IN: begin LCN
/// @param wEndToLCN \b IN: End LCN
/// @param wBeginOfNewLCN \b IN: Begin Of New LCN
/// @param wEndOfNewLCN \b IN: End Of New LCN
/// @param wNewAssignableLCN \b IN: New Assignable LCN
//****************************************************************************
static void AssignNewLCNforLCNSorting(WORD wBeginFromLCN, WORD wEndToLCN, WORD wBeginOfNewLCN, WORD wEndOfNewLCN, WORD wLastLCN)
{
    WORD wOrder;
    WORD wIndex;
    WORD wNewAssignableLCN = 0; //Coverity 188447
    WORD wMinOrder,wMinSID,wMinPriority,wMinMux,wCurrentSID,wCurrentPriority,wCurrentMux,wOrder1,wOrder2;
    BOOLEAN bIsDeletionRequired=0,bIsSortbyPriority=0,bIsSortbyMux=0;
    BOOLEAN bLCNFull = FALSE;
    CHANNEL_ATTRIBUTE stCHAttribute;
    E_LCN_ASSIGNMENT_TYPE eAssignmentType;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    bIsDeletionRequired = FALSE;

    if( 0 == wBeginFromLCN &&
        0 == wEndToLCN &&
        0 == wBeginOfNewLCN &&
        0 == wEndOfNewLCN)
    {
        bIsDeletionRequired = TRUE;
    }

    wNewAssignableLCN = wBeginOfNewLCN;
    for( wOrder1 = 0; wOrder1 < u16ProgramIndexTableArraySize; wOrder1++ )
    {
        if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder1].wPRIndex))
        {
            continue;
        }

        eAssignmentType = pstProgramIndexTable[wOrder1].eLCNAssignmentType;
        //UAE spec, LCN 0 denotes Invisible program
        if(IS_MIDDLEEAST_COUNTRY(OSD_COUNTRY_SETTING)&&(eAssignmentType == E_LCN_ZERO))
        {
            pstProgramIndexTable[wOrder1].bVisibleServiceFlag = FALSE;
            pstProgramIndexTable[wOrder1].eLCNAssignmentType &= ~E_LCN_ZERO;
            continue;
        }

		if((OSD_COUNTRY_SETTING == OSD_COUNTRY_UNITED_ARAB_EMIRATES)
        ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA)
    #if(ENABLE_COUNTRY_SINGAPORE)
        ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE)
    #endif
        || OSD_COUNTRY_SETTING == OSD_COUNTRY_KENYA
        ||(OSD_COUNTRY_SETTING == OSD_COUNTRY_INDONESIA))
        {
            bIsSortbyPriority =TRUE; // choose sort LCN by service type priority for LCN behind 800
        }
#if (ENABLE_COUNTRY_GHANA)
        else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_GHANA)
        {
            bIsSortbyMux =TRUE;     // choose sort LCN by mux for LCN behind 800
        }
#endif
        if((eAssignmentType == (E_LCN_PRESENT|E_LCN_DUPLICATE))||(eAssignmentType == E_LCN_ABSENT)||(eAssignmentType == E_LCN_ZERO))
        {
            wMinOrder    = wOrder1;
            wMinSID      = pstProgramIndexTable[wOrder1].wService_ID;
            wMinPriority = pstProgramIndexTable[wOrder1].bServiceTypePrio;
            wMinMux      = pstProgramIndexTable[wOrder1].cIDIndex;

            if( TRUE == bIsDeletionRequired )
            {
                pstProgramIndexTable[wOrder1].bIsDelete = TRUE;

                GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                stCHAttribute.bIsDelete = TRUE;
                SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                continue;
            }
            else
            {
                for(wOrder2=wOrder1+1; wOrder2 < u16ProgramIndexTableArraySize; wOrder2++)
                {
                    if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder2].wPRIndex))
                    {
                        continue;
                    }

                    eAssignmentType = pstProgramIndexTable[wOrder2].eLCNAssignmentType;

                    if((eAssignmentType == (E_LCN_PRESENT|E_LCN_DUPLICATE))||(eAssignmentType == E_LCN_ABSENT)||(eAssignmentType == E_LCN_ZERO))
                    {
                        if(bIsSortbyPriority) // sort by service type priority
                        {   //the higher the priority , the smaller the vaule.
                            wCurrentPriority = pstProgramIndexTable[wOrder2].bServiceTypePrio;

                            if( wMinPriority > wCurrentPriority )
                            {
                                wMinPriority = wCurrentPriority;
                                wMinOrder = wOrder2;
                            }
                        }
                        else if(bIsSortbyMux) // sort by mux
                        {
                            wCurrentMux = pstProgramIndexTable[wOrder2].cIDIndex;
                            if( wMinMux > wCurrentMux )
                            {
                                wMinMux = wCurrentMux;
                                wMinOrder = wOrder2;
                            }
                        }
                        else // sort by service id
                        {
                            wCurrentSID = pstProgramIndexTable[wOrder2].wService_ID;
                            if( wMinSID > wCurrentSID )
                            {
                                wMinSID = wCurrentSID;
                                wMinOrder = wOrder2;
                            }
                        }
                    }
                }

                if( wMinOrder != wOrder1 )
                {
                    SwapProgram(wMinOrder, wOrder1);// swap the data in array, so LCN and order sort from lowest to high
                }

                wOrder = wOrder1;
                pstProgramIndexTable[wOrder].wLCN = wNewAssignableLCN;
                SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wNewAssignableLCN), E_DATA_LCN);
                switch(pstProgramIndexTable[wOrder].eLCNAssignmentType)
                {
                    case (E_LCN_DUPLICATE|E_LCN_PRESENT):
                        pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~(E_LCN_DUPLICATE|E_LCN_PRESENT);
                    break;
                    case E_LCN_ABSENT:
                        pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ABSENT;;
                    break;
                    case E_LCN_ZERO:
                        pstProgramIndexTable[wOrder].eLCNAssignmentType &= ~E_LCN_ZERO;
                    break;
                    default :
                    break;
                }

                if (!bLCNFull&&(wNewAssignableLCN < wEndOfNewLCN))
                {
                    wNewAssignableLCN++;
                }
                else
                {
                    bLCNFull = TRUE;
                    if(wNewAssignableLCN == wEndOfNewLCN)
                    {
                        wNewAssignableLCN = wBeginOfNewLCN;
                    }
                    // if the new LCN range is full, it will rank from (wNewAssignableLCN-1) in descending order
                    wNewAssignableLCN--;
                }
                //The LCN may be already used by other valid service. Before it is assigned to service, it should be checked.
                if(wNewAssignableLCN <= wLastLCN)
                {
                    for( wIndex = wNewAssignableLCN; wIndex > 1; wIndex-- )
                    {
                        for( wOrder = 0; wOrder < u16ProgramIndexTableArraySize; wOrder++ )
                        {
                            if(pstProgramIndexTable[wOrder].wLCN == wIndex)
                            {
                                break;
                            }
                        }

                        if (wOrder == u16ProgramIndexTableArraySize)
                        {
                            //it is the valid LCN number without used by other service
                            wNewAssignableLCN = wIndex;
                            break;
                        }
                    }
                }
            }
        }
    }
}

//****************************************************************************
/// Get last LCN
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param eExcludingTypes \b IN: LCN assignment Type
/// -@see E_LCN_ASSIGNMENT_TYPE
/// @return WORD: LCN
//****************************************************************************
static WORD GetLastLCN(MEMBER_SERVICETYPE bServiceType, E_LCN_ASSIGNMENT_TYPE eExcludingTypes)
{
    WORD wLastLCN;
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wLastLCN = 0;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for(wPosition=0; wPosition < wProgramCount; wPosition++)
        {
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);

            if( eExcludingTypes & m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType )
            {
                continue;
            }

            if( (INVALID_LOGICAL_CHANNEL_NUMBER != m_astS2ProgramIndexTable[wOrder].wLCN) &&
                (wLastLCN < m_astS2ProgramIndexTable[wOrder].wLCN) )
            {
                if(m_eCountry == E_AUSTRALIA)
                {
                    if( (m_astS2ProgramIndexTable[wOrder].wLCN >= 350) && (m_astS2ProgramIndexTable[wOrder].wLCN <= 399) )
                        wLastLCN = m_astS2ProgramIndexTable[wOrder].wLCN;
                }
                else
                {
                    wLastLCN = m_astS2ProgramIndexTable[wOrder].wLCN;
                }
            }
        }
    }
    else
#endif
    {
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        if( eExcludingTypes & pstProgramIndexTable[wOrder].eLCNAssignmentType )
        {
            continue;
        }

        if( (INVALID_LOGICAL_CHANNEL_NUMBER != pstProgramIndexTable[wOrder].wLCN) &&
            (wLastLCN < pstProgramIndexTable[wOrder].wLCN) )
        {
            if(m_eCountry == E_AUSTRALIA)
            {
                if( (pstProgramIndexTable[wOrder].wLCN >= 350) && (pstProgramIndexTable[wOrder].wLCN <= 399) )
                    wLastLCN = pstProgramIndexTable[wOrder].wLCN;
            }
            else
            {
                wLastLCN = pstProgramIndexTable[wOrder].wLCN;
            }
        }
    }
    }

    return wLastLCN;
}

//****************************************************************************
/// Get last LCN for all service type
/// @param eExcludingTypes \b IN: LCN assignment Type
/// -@see E_LCN_ASSIGNMENT_TYPE
/// @return WORD: LCN
//****************************************************************************
static WORD GetLastLCNforLCNSorting(E_LCN_ASSIGNMENT_TYPE eExcludingTypes)
{
    WORD wLastLCN,wNewAssignableDTVLCN,wNewAssignableRADIOLCN,wNewAssignableDATALCN;
    wNewAssignableDTVLCN = GetLastLCN( E_SERVICETYPE_DTV, eExcludingTypes ) ;
    wNewAssignableRADIOLCN = GetLastLCN( E_SERVICETYPE_RADIO, eExcludingTypes ) ;
    wNewAssignableDATALCN = GetLastLCN( E_SERVICETYPE_DATA, eExcludingTypes ) ;
    wLastLCN=wNewAssignableDTVLCN;

    if(wNewAssignableDTVLCN < wNewAssignableRADIOLCN) wLastLCN=wNewAssignableRADIOLCN;
    if(wNewAssignableRADIOLCN < wNewAssignableDATALCN) wLastLCN=wNewAssignableDATALCN;
    return wLastLCN;
}

static WORD GetLastLCNByRange(MEMBER_SERVICETYPE bServiceType, WORD wStart, WORD wEND)
{
    WORD wLastLCN=wStart;
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        for(wPosition=0; wPosition < wProgramCount; wPosition++)
        {
            for(wPosition=0; wPosition < wProgramCount; wPosition++)
            {
                wOrder = ConvertPositionToOrder(bServiceType, wPosition);
                if((pstProgramIndexTable[wOrder].wLCN<wStart)||(pstProgramIndexTable[wOrder].wLCN>wEND))
                {
                    continue;
                }
                if(wLastLCN < pstProgramIndexTable[wOrder].wLCN )
                {

                    wLastLCN = pstProgramIndexTable[wOrder].wLCN;
                }
            }
        }
    }
    else
#endif
    {
        for(wPosition=0; wPosition < wProgramCount; wPosition++)
        {
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);
            if((pstProgramIndexTable[wOrder].wLCN<wStart)||(pstProgramIndexTable[wOrder].wLCN>wEND))
            {
                continue;
            }
            if(wLastLCN < pstProgramIndexTable[wOrder].wLCN )
            {

                wLastLCN = pstProgramIndexTable[wOrder].wLCN;
            }
        }
    }

    return wLastLCN;
}

// return value : misc1 (-1), misc2 (1), equal (0)
#define BEST_MUX_DIFF 5
//****************************************************************************
/// Select Best Mux
/// @param Misc1 \b IN: channel attribute
/// -@see CHANNEL_ATTRIBUTE
/// @param Misc2 \b IN: channel attribute
/// -@see CHANNEL_ATTRIBUTE
/// @return S8: MUX
//****************************************************************************
#if (ENABLE_SAVE_SQI)
static S8 SelectBestMux(CHANNEL_ATTRIBUTE *Misc1, WORD wNID_1, WORD wSQI1, CHANNEL_ATTRIBUTE *Misc2, WORD wNID_2, WORD wSQI2)
#else
static S8 SelectBestMux(CHANNEL_ATTRIBUTE *Misc1, WORD wNID_1, CHANNEL_ATTRIBUTE *Misc2, WORD wNID_2)
#endif  //ENABLE_SAVE_SQI
{
#if 1 ////////////////////////////////////

    WORD snr_1, snr_2, strength_differ;
    MEMBER_COUNTRY eCountry;

    eCountry = msAPI_CM_GetCountry();

#if ENABLE_TARGET_REGION
    if(Misc1->cRegion != Misc2->cRegion)
    {
        if(Misc1->cRegion > Misc2->cRegion)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
#endif  //ENABLE_TARGET_REGION

    snr_1 = Misc1->wSignalStrength;
    snr_2 = Misc2->wSignalStrength;
    strength_differ = abs((snr_1>>8)-(snr_2>>8));

#if (ENABLE_SAVE_SQI)
    if ((wSQI1 != INVALID_SQI) && (wSQI2 != INVALID_SQI) && (eCountry == E_NEWZEALAND)
        && (snr_1 == 0x7FFE) && (snr_1 == snr_2))
    {
        if (abs((wSQI1>>8)-(wSQI2>>8)) <= BEST_MUX_DIFF)
        {
            wSQI1&=0xFF;
            wSQI2&=0xFF;
        }
        if (wSQI1>=wSQI2)
        {
            return -1;  //keep original
        }
    }
#endif  //ENABLE_SAVE_SQI

    if (strength_differ <= BEST_MUX_DIFF)
    {
        snr_1&=0xFF;
        snr_2&=0xFF;
    }

    if(Misc1->bUnconfirmedService || Misc1->bInvalidService)
    {
        return 1;   // select _tpr2
    }

    if(Misc2->bUnconfirmedService || Misc2->bInvalidService)
    {
        return -1;   // select _tp1
    }

    if(eCountry == E_ITALY)
    {
        if(wNID_1<ITALY_NETWORK_START || wNID_1>ITALY_NETWORK_END)
        {
            if(wNID_2>=ITALY_NETWORK_START && wNID_2<=ITALY_NETWORK_END)
            {
                return 1;   // select _tpr2
            }
        }
        else if(wNID_2<ITALY_NETWORK_START || wNID_2>ITALY_NETWORK_END)
        {
            if(wNID_1>=ITALY_NETWORK_START && wNID_1<=ITALY_NETWORK_END)
            {
                return -1;   // select _tp1
            }
        }
    }

    if(Misc1->bVisibleServiceFlag == FALSE)
    {
        return 1;   // select _tpr2
    }

    if(Misc2->bVisibleServiceFlag == FALSE)
    {
        return -1;   // select _tp1
    }

    // ========== Compare SNR ==========
    if(snr_1 == snr_2)
    {
        return -1;  // select _tpr1

    }
    else if (snr_1 > snr_2)
    {
        return -1;  // select _tpr1
    }
    else
    {
        return 1;   // select _tpr2
    }

    return 0;       // default return value

#else ////////////////////////////////////
    WORD    snr_1, snr_2;

    snr_1 = Misc1->wSignalStrength;
    snr_2 = Misc2->wSignalStrength;

    // ========== Compare SNR ==========
    if(snr_1 == snr_2)
        return 0;

    else if( snr_1 > snr_2 )
        return -1;    // select _tpr1

    else
        return 1;    // select _tpr2

    return 0;    // default return value
#endif  //if 1
}

//****************************************************************************
/// Reset Best Mux Data
/// @param eServiceType \b IN: service type
/// -@see MEMBER_SERVICETYPE
//****************************************************************************
static void ResetBestMuxData(MEMBER_SERVICETYPE eServiceType)
{
#if(ENABLE_DVB)
    //  Sync code from CL1462599(Mantis-996337):
    //  Some country  need wSignalStrength for sorting, but some country don't!
    //  In Nordig Spec, it doesn't use wSignalStrength for sorting, so we reset wSignalStrength to a const value
    if( !(msAPI_SI_IsSpecificCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING), SI_NORDIC_SPECIFIC_COUNTRY)) )
    {
        return;
    }
#endif  //ENABLE_DVB
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    CHANNEL_ATTRIBUTE stCHAttribute;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wProgramCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);

    for( wPosition = 0; wPosition < wProgramCount; wPosition++ )
    {
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, eServiceType, wPosition);

        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;

    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            GetProgramTable(m_astS2ProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
            stCHAttribute.wSignalStrength = 0x7FFE;//for Nordig Spec
            SetProgramTable(m_astS2ProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
        }
        else
    #endif
        {
            if( FALSE == GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                continue;

            stCHAttribute.wSignalStrength = 0x7FFE; //for Nordig Spec
            SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
        }
    }
}

//****************************************************************************
/// Keep Move Position
/// @param eServiceType \b IN: service type
/// -@see MEMBER_SERVICETYPE
//****************************************************************************
static void KeepMovePosition(MEMBER_SERVICETYPE eServiceType)
{
    WORD wPosition;
    WORD wSearchPos,i;
    WORD wOrder;
    WORD wSavedOrder = 0;
    WORD wProgramCount;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);

    for( wPosition = 0; wPosition < wProgramCount; wPosition++ )
    {
      #if ( WATCH_DOG == ENABLE )
        msAPI_Timer_ResetWDT();
      #endif

        wSearchPos = ConvertPositionToOrder_DBSel(eDtvDbSel, eServiceType, wPosition);
        if( wSearchPos >= u16ProgramIndexTableArraySize )
            continue;

        //printf(" wPosition:%d of Max:%d => Search Pos:%d\n", wPosition, wProgramCount, wSearchPos );

        for ( i = wPosition ; i <  wProgramCount ; i++ )
        {
            //wOrder = ConvertPositionToOrder( eServiceType, i );
            wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, eServiceType, i);
            //printf( "             i:%d of Max:%d => wOrder:%d \n", i, wProgramCount, wOrder );
            if( wOrder >= u16ProgramIndexTableArraySize )
                continue;


        #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                if( m_astS2ProgramIndexTable[wOrder].bIsMove == TRUE )
                {
                    GetProgramTable(m_astS2ProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wSavedOrder, E_DATA_ORDER);
                    //printf("              m_astDTVProgramIndexTable[wOrder].wPRIndex :%d, wSaveOrder:%d SearchPos:%d\n",
                    //                         m_astDTVProgramIndexTable[wOrder].wPRIndex, wSavedOrder, wSearchPos );
                    if ( wSavedOrder == wSearchPos )
                    {
                        if(i!=wPosition)
                        {
                            if( m_astS2ProgramIndexTable[wSavedOrder].bIsMove == TRUE )
                            {
                                SwapProgram(wOrder, wSavedOrder);
                            }
                            else
                            {
                                MoveProgram(wOrder, wSavedOrder);
                            }
                        }
                        break;
                    }
                }
            }
            else
        #endif
            {
                if( pstProgramIndexTable[wOrder].bIsMove == TRUE )
                {
                    if( FALSE == GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wSavedOrder, E_DATA_ORDER) )
                        continue;

                    //printf("              m_astDTVProgramIndexTable[wOrder].wPRIndex :%d, wSaveOrder:%d SearchPos:%d\n",
                    //                         m_astDTVProgramIndexTable[wOrder].wPRIndex, wSavedOrder, wSearchPos );
                    if ( wSavedOrder == wSearchPos )
                    {
                        if(i!=wPosition)
                        {
                            if( pstProgramIndexTable[wSavedOrder].bIsMove == TRUE )
                                SwapProgram(wOrder, wSavedOrder);
                            else
                                MoveProgram(wOrder, wSavedOrder);
                        }
                        break;
                    }
                }
            }
        }
    }
}

//****************************************************************************
/// Make All LCN Absent
/// @param eServiceType \b IN: service type
/// -@see MEMBER_SERVICETYPE
//****************************************************************************
static void MakeAllLCNAbsent(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition;
    WORD wProgramCount;
    WORD wOrder;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;

    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            m_astS2ProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
            m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType = E_LCN_ABSENT;
        }
        else
    #endif
        {
            pstProgramIndexTable[wOrder].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
            pstProgramIndexTable[wOrder].eLCNAssignmentType = E_LCN_ABSENT;
        }
    }
}

#if(ENABLE_S2_LCN_STYLE_AFTERSORT)
void ArrangeChannelNumberAfterSort(MEMBER_SERVICETYPE eServiceType)
{
    S32 s32Order =0;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    if(!IsS2InUse())
    {
        return;
    }
    if (eServiceType == E_SERVICETYPE_DTV)
    {
        WORD wOrderOfTV=S2_FIRST_ORDER_OF_TV;
        for(s32Order=wOrderOfTV; s32Order < MAX_DTV_S2_PROGRAM; s32Order++)
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            if(TRUE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex))
            {
                pstProgramIndexTable[s32Order].wLCN = (WORD)s32Order +1;
                SetProgramTable(pstProgramIndexTable[s32Order].wPRIndex, (BYTE *)&(pstProgramIndexTable[s32Order].wLCN), E_DATA_LCN);
            }
            else if(FALSE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex))
            {
                MS_DEBUG_MSG(printf("No empty dtv order be found\n"));
                return;
            }
        }
    }
    else if (eServiceType == E_SERVICETYPE_RADIO)
    {
        WORD wOrderOfRadio = S2_FIRST_ORDER_OF_RADIO;
        for(s32Order=0; s32Order < MAX_DTV_S2_PROGRAM; s32Order++)
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            if((E_SERVICETYPE_DATA == pstProgramIndexTable[s32Order].bServiceType) &&
                (TRUE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex)) )
            {
                wOrderOfRadio--;
            }
        }
         //printf("\r\nwOrderOfRadio=%d",wOrderOfRadio);
        for(s32Order=wOrderOfRadio; s32Order >=S2_FIRST_ORDER_OF_TV; s32Order--)
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            if(TRUE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex))
            {
                pstProgramIndexTable[s32Order].wLCN= wOrderOfRadio-(WORD)s32Order +1;
                SetProgramTable(pstProgramIndexTable[s32Order].wPRIndex, (BYTE *)&(pstProgramIndexTable[s32Order].wLCN), E_DATA_LCN);
            }
            else if(FALSE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex))
            {
                MS_DEBUG_MSG(printf("No empty radio order be found\n"));
                return;
            }
        }
    }
    else if (eServiceType == E_SERVICETYPE_DATA)
    {
        WORD wOrderOfData = S2_FIRST_ORDER_OF_DATA;
        printf("\r\nData");
        for(s32Order=wOrderOfData; s32Order >=S2_FIRST_ORDER_OF_TV; s32Order--)
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            if(TRUE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex))
            {
                pstProgramIndexTable[s32Order].wLCN= wOrderOfData-(WORD)s32Order+1;
                SetProgramTable(pstProgramIndexTable[s32Order].wPRIndex, (BYTE *)&(pstProgramIndexTable[s32Order].wLCN), E_DATA_LCN);
            }
            else if(FALSE == IsProgramEntityActive(pstProgramIndexTable[s32Order].wPRIndex))
            {
                MS_DEBUG_MSG(printf("No empty data order be found\n"));
                return;
            }
        }
    }
    else
    {
        pstProgramIndexTable[s32Order].wLCN = DEFAULT_ORDER;
        return;
    }
}
#endif


void PrintLCN(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition1;
    WORD wOrder1;
    WORD wProgramCount;
    CHANNEL_ATTRIBUTE Misc1, Misc2;
    MEMBER_COUNTRY eCountry;
    PRINT_CURRENT_LINE();

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif


    eCountry = msAPI_CM_GetCountry();
    memset((BYTE *)&Misc1,0x00,sizeof(CHANNEL_ATTRIBUTE));
    memset((BYTE *)&Misc2,0x00,sizeof(CHANNEL_ATTRIBUTE));
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    for( wPosition1 = 0; wPosition1 < wProgramCount; wPosition1++ )
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        GetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&Misc1, E_DATA_MISC);

        //WORD wONID= msAPI_CM_GetON_ID((MEMBER_SERVICETYPE)bServiceType, wPosition1);
        //printf("[%d] bServiceTypePrio = %d, wLCN = %d, sLCN = %d, wONID = 0x%x. serviceID= %d\n", wPosition1, pstProgramIndexTable[wOrder1].bServiceTypePrio, pstProgramIndexTable[wOrder1].wLCN, pstProgramIndexTable[wOrder1].wSimu_LCN, wONID,pstProgramIndexTable[wOrder1].wService_ID);
    }

}

//****************************************************************************
/// Arrange Logical Channel Number
/// @param eServiceType \b IN: service type
/// -@see MEMBER_SERVICETYPE
/// @param eLcnType \b IN: LCN type
/// -@see E_MEMBER_LCN_TYPE
//****************************************************************************
static void ArrangeLogicalChannelNumber(MEMBER_SERVICETYPE bServiceType, E_MEMBER_LCN_TYPE eLcnType, BOOLEAN bSkipDupSrvRemove)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();

    //PRINT_CURRENT_LINE();
    DEBUG_CM_ARRANGE_LCN( printf("[CM]ArrangeLogicalChannelNumber(typ=%u,eLcnType=%u)\n", bServiceType, eLcnType); );

    WORD wNewAssignableLCN;
	WORD wBeginOfNewLCN;
    MEMBER_COUNTRY eCountry;

    LogicalChannelNumberIsArranged_DBSel(eCurDbSel, FALSE);

    eCountry = msAPI_CM_GetCountry();

#if (ENABLE_CI_PLUS)
    if(TRUE == msAPI_CM_GetOpMode())
    {
        #if (!ENABLE_CI_PLUS_V1_4)
        {
        //DistinguishSameService(bServiceType);
        DistinguishLCNSameService(bServiceType);
        RemoveSameService(bServiceType);//for Nordig Spec
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
            ResetBestMuxData(bServiceType); //no check signal strength
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }
        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, 9999, 10000, 0x3FFF, wNewAssignableLCN );
        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 9999, 10000, 0x3FFF, wNewAssignableLCN );
        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        }
        #else
        {
            //DistinguishLCNSameService(bServiceType);
            //RemoveSameService(bServiceType);//for Nordig Spec
            printf("Op Type 2....Use original!!!\n");
        }
        #endif
        SortProgram(bServiceType);

        UpdateOrderOfProgramTable(bServiceType);
        UpdateProgramCount(bServiceType);
        LogicalChannelNumberIsArranged_DBSel(eCurDbSel, TRUE);

        return;
    }
#endif

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    if (GetASTRA_HD_ENABLE())
    {
        // printf("Use ASTRA LCN !\n");
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            DistinguishLCNPresentOrAbsent(bServiceType);
            DeleteInvalidLCNService(bServiceType,E_LCN_ABSENT);
            DistinguishLCNDuplicate(bServiceType);
            RemoveServicebyLcnAssignmentType(bServiceType,E_LCN_DUPLICATE);
            SortProgram(bServiceType);
        }

        UpdateOrderOfProgramTable(bServiceType);
        UpdateProgramCount(bServiceType);
        LogicalChannelNumberIsArranged(TRUE);

        return ;
    }
#endif  // #if ASTRA_HD_ENABLE


#if(ENABLE_S2)
    if(IsS2InUse())
    {
        MakeAllLCNAbsent(bServiceType);
    #ifndef S2_SCAN_CHANNEL_NUMBER_BUG
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            DistinguishSameService(bServiceType);
            KeepMovePosition(bServiceType);
        }
    #else
        KeepMovePosition(bServiceType);
    #endif
        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, 1 );
    #ifndef S2_SCAN_CHANNEL_NUMBER_BUG
        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );
    #endif
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            SortProgram(bServiceType);
        }
    }
    else
#endif
    {
        eCountry = msAPI_CM_GetCountry();
    }

#if ENABLE_ZIGGO
    if((eCountry == E_NETHERLANDS)
     ||(eCountry == E_AUSTRIA)
     ||(eCountry == E_HUNGARY)
     ||(eCountry == E_POLAND)
     ||(eCountry == E_ROMANIA)
     ||(eCountry == E_SWITZERLAND)
     ||(eCountry == E_IRELAND))
    {
        printf("Ziggo LCN arrange \n");
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        DistinguishSameService(bServiceType);
        RemoveSameService(bServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }
        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
        wBeginOfNewLCN = wNewAssignableLCN == 1 ? 1 : 800;
        AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        DistinguishLCNDuplicate(bServiceType);
        DistinguishSDAndHDLCNDuplicate(bServiceType);

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ZERO, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        SortProgram(bServiceType);
    }
    else
#endif
{
    switch(eCountry)
    {
#if ENABLE_SBTVD_DTV_SYSTEM
    case E_BRAZIL:
        DistinguishSameService(bServiceType);
        RemoveSameService(bServiceType);

        #if ENABLE_SBTVD_CM_APP
        SortProgram_Brazil(bServiceType);
        #else
        SortProgram(bServiceType);
        #endif
        break;
#endif

    case E_AUSTRALIA:
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        DistinguishSameService(bServiceType);

        // #1301255 - AUS-0055 [TC15060200390] Duplicated LCN issue, match for spec case do not remove same TSID, ONID, SID program.
        //RemoveSameService(bServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN(bServiceType, E_LCN_DUPLICATE, 1, 999, 350, MAX_LCN, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_ABSENT|E_LCN_SAME_SERVICE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_ABSENT, 1, 999, 350, MAX_LCN, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_SAME_SERVICE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_SAME_SERVICE, 1, 999, 350, MAX_LCN, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ZERO, 1, 999, 350, MAX_LCN, wNewAssignableLCN );

        SortProgram(bServiceType);
        break;

    case E_ITALY:
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        DistinguishSameService(bServiceType);
        RemoveSameService(bServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }

        wNewAssignableLCN = GetLastLCNByRange(bServiceType, ITALY_PREFER_LCN_OVERFLOW_START, ITALY_PREFER_LCN_OVERFLOW_END)+1;
        if(wNewAssignableLCN<=ITALY_PREFER_LCN_OVERFLOW_END)
        {
            AssignNewLCN(bServiceType, E_LCN_DUPLICATE, ITALY_PREFER_LCN_START, ITALY_PREFER_LCN_OVERFLOW_START-1, ITALY_PREFER_LCN_OVERFLOW_START, ITALY_PREFER_LCN_OVERFLOW_END, wNewAssignableLCN);
        }

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_ABSENT|E_LCN_SAME_SERVICE|E_LCN_DUPLICATE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_DUPLICATE, ITALY_ASSIGN_LCN_START, ITALY_MAIN_LCN_OVERFLOW_START-1, ITALY_MAIN_LCN_OVERFLOW_START, ITALY_MAIN_LCN_OVERFLOW_END, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_ABSENT|E_LCN_SAME_SERVICE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_ABSENT, ITALY_PREFER_LCN_START, ITALY_ASSIGN_LCN_END, ITALY_MAIN_LCN_OVERFLOW_START, ITALY_MAIN_LCN_OVERFLOW_END, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_SAME_SERVICE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_SAME_SERVICE, ITALY_PREFER_LCN_START, ITALY_ASSIGN_LCN_END, ITALY_MAIN_LCN_OVERFLOW_START, ITALY_MAIN_LCN_OVERFLOW_END, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ZERO, ITALY_PREFER_LCN_START, ITALY_ASSIGN_LCN_END, ITALY_MAIN_LCN_OVERFLOW_START, ITALY_MAIN_LCN_OVERFLOW_END, wNewAssignableLCN );

        SortProgram(bServiceType);
        break;

    case E_IRAN:
    case E_VIETNAM:
    case E_MOROCCO:
    case E_INDONESIA:
    case E_MYANMAR:
    {
// [DVB-T (Certification)][VNTA (Viet Nam) Backend Test]
// 2014-568 [TC16052500925]
        WORD wSameServiceBeginFrom = (eCountry == E_VIETNAM) ? 800 : 1;

        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        DistinguishSameService(bServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_ABSENT|E_LCN_SAME_SERVICE|E_LCN_DUPLICATE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_DUPLICATE, 1, MAX_LCN, wSameServiceBeginFrom, MAX_LCN, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_ABSENT|E_LCN_SAME_SERVICE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_ABSENT, 1, MAX_LCN, wSameServiceBeginFrom, MAX_LCN, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN(bServiceType, (E_LCN_SAME_SERVICE)) + 1;
        AssignNewLCN(bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN);

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN(bServiceType, E_LCN_ZERO, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN);

        SortProgram(bServiceType);
    }
        break;
    case E_UK:
    case E_NEWZEALAND:
    //case E_THAILAND:
    case E_MALAYSIA:
    case E_SINGAPORE:

        // DTG says we need use best mux rule to store duplicate service.
        if(E_NEWZEALAND== eCountry)
        {
            DistinguishNotNativeON_ID(bServiceType, 0x222A);
            ReassignInvalidLCN(bServiceType);//for Freeview NZ spec
        }
        else if(E_UK== eCountry)
        {
            DistinguishNotNativeON_ID(bServiceType, 0x233A);
            DistinguishLCNDuplicate(bServiceType);
            DistinguishSDLCNAndHDSimuLCNDuplicate(bServiceType, 0x233A);
        }
        else if (E_THAILAND == eCountry)
        {
            DistinguishNotNativeON_ID(bServiceType, 0x22FC);
        }
        else if (E_SINGAPORE == eCountry)
        {
            DistinguishNotNativeON_ID(bServiceType, 0x22BE);
        }

        DistinguishSameService(bServiceType);
        if(E_NEWZEALAND== eCountry)
        {
            DistinguishLCNSameService(bServiceType);
        }
        RemoveSameService(bServiceType);//for Nordig Spec
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);

        ResetBestMuxData(bServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, 799, 800, MAX_LCN, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 799, 800, MAX_LCN, wNewAssignableLCN );

        //wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
        //AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, 799, 800, 999, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ZERO, 1, 799, 800, MAX_LCN, wNewAssignableLCN );

        SortProgram(bServiceType);
        break;

  #if 0
        case E_FRANCE:
            DistinguishSDAndHDLCNDuplicate(bServiceType);
        case E_NETHERLANDS:
  #else // Modified by coverity_0601
        case E_PORTUGAL:
        case E_FRANCE:
        case E_NETHERLANDS:
        if (eCountry == E_FRANCE)
        {
            DistinguishNotNativeON_ID(bServiceType, 0x20FA);
           	DistinguishLCNDuplicate(bServiceType);
           	DistinguishSDAndHDLCNDuplicate(bServiceType);
        }
        else if (eCountry == E_PORTUGAL)
        {
            DistinguishLCNDuplicate(bServiceType);
            DistinguishSDAndHDLCNDuplicate(bServiceType);
        }
  #endif
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        DistinguishSameService(bServiceType);
        RemoveSameService(bServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }
		wBeginOfNewLCN = 800;
        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
		if(E_FRANCE == eCountry)wBeginOfNewLCN = wNewAssignableLCN;
		AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE ) + 1;
		if(E_FRANCE == eCountry)wBeginOfNewLCN = wNewAssignableLCN;
        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
		if(E_FRANCE == eCountry)wBeginOfNewLCN = wNewAssignableLCN;
        AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );
        if (eCountry == E_NETHERLANDS)
        {
            DistinguishLCNDuplicate(bServiceType);
            DistinguishSDAndHDLCNDuplicate(bServiceType);
        }

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
		if(E_FRANCE == eCountry)wBeginOfNewLCN = wNewAssignableLCN;
        AssignNewLCN( bServiceType, E_LCN_ZERO, 1, 799, wBeginOfNewLCN, MAX_LCN, wNewAssignableLCN );

        SortProgram(bServiceType);
        break;
    case E_NORWAY:
    case E_SWEDEN:
    case E_FINLAND:
    case E_DENMARK:
    case E_IRELAND:
    #if 0 // I am not sure if there is any side effect.
        if( eCountry == E_SWEDEN )
        {
            DistinguishNotNativeON_ID(bServiceType, 0x22F1);
        }
    #endif
        DistinguishSameService(bServiceType);
        if(bSkipDupSrvRemove == FALSE)
        {
            if(IS_BESTMUX_COUNTRY(m_eCountry))
            RemoveSameService(bServiceType);//for Nordig Spec
        }
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        if( eCountry == E_NORWAY )
        {
            //DistinguishNotNativeON_ID(bServiceType, 0x2242);
            DistinguishLCNLast(bServiceType);//for RiksTV spec,900~999 shall be end of list
        }
        if(bSkipDupSrvRemove == FALSE)
        {
            if(IS_BESTMUX_COUNTRY(m_eCountry))
            ResetBestMuxData(bServiceType);
        }
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(bServiceType);
        }

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE|E_LCN_LAST ) + 1;
        AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE|E_LCN_LAST ) + 1;

        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

        if( eCountry == E_NORWAY )
        {
            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE|E_LCN_LAST ) + 1;
            AssignNewLCN( bServiceType, E_LCN_LAST, 1, MAX_LCN, RIKSTV_HEARING_AND_VISUALLY_IMPAIRED_LCN_START, MAX_LCN, wNewAssignableLCN );
        }
//        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
//        AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, 9999, 1, 9999, wNewAssignableLCN );
//        AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 0, 0, 0, 0, 0 );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ZERO, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

        SortProgram(bServiceType);
#if NTV_FUNCTION_ENABLE
        if( eCountry == E_NORWAY )
        {
            SortProgramByRegionPriority(bServiceType);
        }
#endif

        break;

    case E_GERMANY:

    #if ENABLE_DVBC
        if( IsDVBCInUse() )
        {
            DistinguishLCNDuplicate(bServiceType);
            DistinguishLCNPresentOrAbsent(bServiceType);
            DistinguishLCNDuplicate(bServiceType);
            DistinguishSameService(bServiceType);
            RemoveSameService(bServiceType);

            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                KeepMovePosition(bServiceType);
            }

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
            AssignNewLCN( bServiceType, E_LCN_ZERO, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            SortProgram(bServiceType);
            break;
        }
        else
    #endif
    #if (ENABLE_S2)
        if( IsS2InUse() )
        {
            MakeAllLCNAbsent(bServiceType);

            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                DistinguishSameService(bServiceType);
                RemoveSameService(bServiceType);
            }

            AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, 1 );

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                SortProgram(bServiceType);
            }

            break;
        }
        else
    #endif
        { // DVBT,
             // Sync code from CL:7796e1cbcfafc5880c75fde32c63be8203b9877a (Mantis-1085805)
            //MakeAllLCNAbsent(bServiceType);
            DistinguishLCNDuplicate(bServiceType);
            DistinguishLCNPresentOrAbsent(bServiceType);

            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                DistinguishSameService(bServiceType);
                KeepMovePosition(bServiceType);
            }

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            //In Germany LCN 0 is invalid program
            AssignNewLCN( bServiceType, E_LCN_ZERO, 1, MAX_LCN, 1, MAX_LCN, 1 );

            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                SortProgram(bServiceType);
            }

            break;
        }
        break;

    case E_THAILAND:
        DistinguishNotNativeON_ID(bServiceType, THAILAND_ONID);
        DistinguishSameService(bServiceType);
        RemoveSameService(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        DistinguishLCNPresentOrAbsent(bServiceType);
        DistinguishLCNDuplicate(bServiceType);
        ResetBestMuxData(bServiceType);

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_DUPLICATE|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_DUPLICATE, 1, 9999, 800, 9999, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ABSENT|E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 9999, 800, 9999, wNewAssignableLCN );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_ZERO ) + 1;
        AssignNewLCN( bServiceType, E_LCN_ZERO, 1, 9999, 800, 9999, wNewAssignableLCN );

        SortProgram(bServiceType);
        break;

#if(ENABLE_S2_FAST_SCAN)
        case E_AUSTRIA:
        case E_BELGIUM:
        case E_CZECH:
        case E_HUNGARY:
        case E_LUXEMBOURG:
        case E_SLOVENIA:
        {
            if(_bM7ScanEnable == TRUE)
            {
                DistinguishSameService(bServiceType);
                RemoveSameService(bServiceType);
             }
            else
            {
                MakeAllLCNAbsent(bServiceType);
                if (!IsS2InUse())
                {
                    if( eLcnType != E_LCN_TYPE_MOVE)
                    {
                        DistinguishSameService(bServiceType);
                        RemoveSameService(bServiceType);
                    }
                }
            }

            AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, 1 );

            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                SortProgram(bServiceType);
            }

#if(ENABLE_S2_LCN_STYLE_AFTERSORT)
            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                ArrangeChannelNumberAfterSort(bServiceType);
            }
            if (!IsS2InUse())
            {
                MakeAllLCNAbsent(bServiceType);
                AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 999, 1, 999, 1 );
                wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
                AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, 999, 1, 999, wNewAssignableLCN );
                if( eLcnType != E_LCN_TYPE_MOVE)
                {
                    SortProgram(bServiceType);
                }
            }
#endif
        }
        break;
#endif //#if(ENABLE_S2_FAST_SCAN)

    default:
        MakeAllLCNAbsent(bServiceType);

    #if ENABLE_S2
        if (!IsS2InUse())
        {
            if( eLcnType != E_LCN_TYPE_MOVE)
            {

            DistinguishSameService(bServiceType);
            RemoveSameService(bServiceType);
            }
        }
    #else
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            DistinguishSameService(bServiceType);
            KeepMovePosition(bServiceType);
        }
    #endif

        AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, MAX_LCN, 1, MAX_LCN, 1 );

        wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
        AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, MAX_LCN, 1, MAX_LCN, wNewAssignableLCN );

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            SortProgram(bServiceType);
        }

    #if(ENABLE_S2_LCN_STYLE_AFTERSORT)
        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            ArrangeChannelNumberAfterSort(bServiceType);
        }
        if (!IsS2InUse())
        {
            MakeAllLCNAbsent(bServiceType);
            AssignNewLCN( bServiceType, E_LCN_ABSENT, 1, 999, 1, 999, 1 );
            wNewAssignableLCN = GetLastLCN( bServiceType, E_LCN_SAME_SERVICE ) + 1;
            AssignNewLCN( bServiceType, E_LCN_SAME_SERVICE, 1, 999, 1, 999, wNewAssignableLCN );
            if( eLcnType != E_LCN_TYPE_MOVE)
            {
                SortProgram(bServiceType);
            }
        }
    #endif

        break;
    }
}
    UpdateOrderOfProgramTable(bServiceType);

    UpdateProgramCount(bServiceType);

    LogicalChannelNumberIsArranged_DBSel(eCurDbSel, TRUE);
}

//****************************************************************************
/// Arrange Logical Channel Number for LCN sorting
/// @param eLcnType \b IN: LCN type
/// -@see E_MEMBER_LCN_TYPE
//****************************************************************************
static void ArrangeLogicalChannelNumberforLCNSorting(E_MEMBER_LCN_TYPE eLcnType)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    U16 u16MaxLcn,u16LcnStart;
    MEMBER_SERVICETYPE eServiceType;
    WORD wLastLCN;
    //WORD GCC_MiddleEast_ONIDList[6];

    LogicalChannelNumberIsArranged_DBSel(eCurDbSel, FALSE);
    PRINT_CURRENT_LINE();

    for(eServiceType =E_SERVICETYPE_DTV; eServiceType<E_SERVICETYPE_UNITED_TV; eServiceType++)
    {
    /* Move to msAPI_CM_DistinguishNotNativeON_ID_By_Country()
        switch(OSD_COUNTRY_SETTING)
        {
            case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
            case OSD_COUNTRY_KUWAIT:
            case OSD_COUNTRY_OMAN:
            case OSD_COUNTRY_QATAR:
            case OSD_COUNTRY_SAUDI_ARABIA:
            case OSD_COUNTRY_BAHRAIN:
                GCC_MiddleEast_ONIDList[0] = UAE_ONID;
                GCC_MiddleEast_ONIDList[1] = BAHRAIN_ONID;
                GCC_MiddleEast_ONIDList[2] = KUWAIT_ONID;
                GCC_MiddleEast_ONIDList[3] = OMAN_ONID;
                GCC_MiddleEast_ONIDList[4] = QATAR_ONID;
                GCC_MiddleEast_ONIDList[5] = SAUDI_ONID;
                DistinguishNotNativeON_IDS(eServiceType, GCC_MiddleEast_ONIDList, 6);
            break;

            case OSD_COUNTRY_MALAYSIA:
                DistinguishNotNativeON_ID(eServiceType,MALAYSIA_ONID);
            break;
#if(ENABLE_COUNTRY_SINGAPORE)
            case OSD_COUNTRY_SINGAPORE:
                DistinguishNotNativeON_ID(eServiceType,SINGAPORE_ONID);
            break;
#endif
            case OSD_COUNTRY_THAILAND:
                DistinguishNotNativeON_ID(eServiceType,THAILAND_ONID);
            break;
#if (ENABLE_COUNTRY_GHANA)
            case OSD_COUNTRY_GHANA:
                DistinguishNotNativeON_ID(eServiceType, GHANA_ONID);
            break;
#endif
#if (ENABLE_COUNTRY_KENYA)
            case OSD_COUNTRY_KENYA:
                DistinguishNotNativeON_ID(eServiceType, KENYA_ONID);
            break;
#endif
            default:
            break;
        }
        */

        DistinguishSameService(eServiceType);
        RemoveSameService(eServiceType);
        DistinguishLCNPresentOrAbsent(eServiceType);
        DistinguishLCNDuplicate(eServiceType);
        ResetBestMuxData(eServiceType);

        if( eLcnType != E_LCN_TYPE_MOVE)
        {
            KeepMovePosition(eServiceType);
        }
    }

    wLastLCN = GetLastLCNforLCNSorting(E_LCN_ABSENT);

    if( (wLastLCN == 0)&&
        ( (OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA)
#if(ENABLE_COUNTRY_SINGAPORE)
        || (OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE)
#endif
        || (OSD_COUNTRY_SETTING == OSD_COUNTRY_THAILAND)
#if(ENABLE_COUNTRY_MYANMAR)
        || (OSD_COUNTRY_SETTING == OSD_COUNTRY_MYANMAR)
#endif
#if (ENABLE_COUNTRY_GHANA)
        || (OSD_COUNTRY_SETTING == OSD_COUNTRY_GHANA)
#endif
        ) )
    {
        u16LcnStart = 1;
    }
    else if(wLastLCN < 800)
    {
        u16LcnStart = 800;
    }
    else
    {
        u16LcnStart = wLastLCN+1;
    }

    if(OSD_COUNTRY_SETTING == OSD_COUNTRY_INDONESIA)
    {
        u16MaxLcn = 900;
    }
    else if(OSD_COUNTRY_SETTING == OSD_COUNTRY_MALAYSIA
#if(ENABLE_COUNTRY_SINGAPORE)
        || (OSD_COUNTRY_SETTING == OSD_COUNTRY_SINGAPORE)
#endif
        || (OSD_COUNTRY_SETTING == OSD_COUNTRY_UNITED_ARAB_EMIRATES))
    {
        u16MaxLcn = 999;
    }
    else
    {
        u16MaxLcn = MAX_LCN;
    }

    AssignNewLCNforLCNSorting( 1, VALID_RANGE_LCN, u16LcnStart, u16MaxLcn, wLastLCN );
    SortProgramforLCNSorting();

    for(eServiceType =E_SERVICETYPE_DTV; eServiceType<E_SERVICETYPE_UNITED_TV; eServiceType++)
    {
        UpdateOrderOfProgramTable(eServiceType);
        UpdateProgramCount(eServiceType);
    }

    LogicalChannelNumberIsArranged_DBSel(eCurDbSel, TRUE);
}

U16 msAPI_CM_Get_ON_ID_ByCountry(EN_OSD_COUNTRY_SETTING eCountry)
{
    U16 u16OD_ID = 0;

    switch(eCountry)
    {
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
            u16OD_ID = UAE_ONID;
            break;

        case OSD_COUNTRY_KUWAIT:
            u16OD_ID = KUWAIT_ONID;
            break;

        case OSD_COUNTRY_OMAN:
            u16OD_ID = OMAN_ONID;
            break;

        case OSD_COUNTRY_QATAR:
            u16OD_ID = QATAR_ONID;
            break;

        case OSD_COUNTRY_SAUDI_ARABIA:
            u16OD_ID = SAUDI_ONID;
            break;

        case OSD_COUNTRY_BAHRAIN:
            u16OD_ID = BAHRAIN_ONID;
            break;

        case OSD_COUNTRY_MALAYSIA:
            u16OD_ID = MALAYSIA_ONID;
            break;

    #if(ENABLE_COUNTRY_SINGAPORE)
        case OSD_COUNTRY_SINGAPORE:
            u16OD_ID = SINGAPORE_ONID;
            break;
    #endif

        case OSD_COUNTRY_THAILAND:
            u16OD_ID = THAILAND_ONID;
            break;

    #if (ENABLE_COUNTRY_GHANA)
        case OSD_COUNTRY_GHANA:
            u16OD_ID = GHANA_ONID;
            break;
    #endif

    #if (ENABLE_COUNTRY_KENYA)
        case OSD_COUNTRY_KENYA:
            u16OD_ID = KENYA_ONID;
            break;
    #endif

    #if (ENABLE_COUNTRY_MYANMAR)
        case OSD_COUNTRY_MYANMAR:
            u16OD_ID = MYANMAR_ONID;
            break;
    #endif

        case OSD_COUNTRY_DENMARK:
            u16OD_ID = DTV_ONID_NORWAY;
            break;

        case OSD_COUNTRY_FINLAND:
            u16OD_ID = DTV_ONID_FINLAND;
            break;

        case OSD_COUNTRY_GERMANY:
            u16OD_ID = DTV_ONID_GERMANY;
            break;

        case OSD_COUNTRY_INDONESIA:
            u16OD_ID = DTV_ONID_INDONESIA;
            break;

        case OSD_COUNTRY_IRELAND:
            u16OD_ID = DTV_ONID_IRELAND;
            break;

        case OSD_COUNTRY_NORWAY:
            u16OD_ID = DTV_ONID_NORWAY;
            break;

        case OSD_COUNTRY_SWEDEN:
            u16OD_ID = DTV_ONID_SWEDEN;
            break;

        default:
            break;
    }

    return u16OD_ID;
}

void msAPI_CM_DistinguishNotNativeON_ID_By_Country(EN_OSD_COUNTRY_SETTING eCountry )
{
#if ( ENABLE_CABLE_READY_SETTING )
    if( eCountry == OSD_COUNTRY_FINLAND )
    {
        return;
    }
#endif

    switch(eCountry)
    {
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
        case OSD_COUNTRY_KUWAIT:
        case OSD_COUNTRY_OMAN:
        case OSD_COUNTRY_QATAR:
        case OSD_COUNTRY_SAUDI_ARABIA:
        case OSD_COUNTRY_BAHRAIN:
          {
            U16 aGCC_MiddleEast_ONIDList[] =
                {UAE_ONID, BAHRAIN_ONID, KUWAIT_ONID, OMAN_ONID, QATAR_ONID, SAUDI_ONID};

            DistinguishNotNativeON_IDS(E_SERVICETYPE_DTV, aGCC_MiddleEast_ONIDList, sizeof(aGCC_MiddleEast_ONIDList)/2);
            DistinguishNotNativeON_IDS(E_SERVICETYPE_RADIO, aGCC_MiddleEast_ONIDList, sizeof(aGCC_MiddleEast_ONIDList)/2);
            DistinguishNotNativeON_IDS(E_SERVICETYPE_DATA, aGCC_MiddleEast_ONIDList, sizeof(aGCC_MiddleEast_ONIDList)/2);
          }
            break;

        case OSD_COUNTRY_DENMARK:
        case OSD_COUNTRY_FINLAND:
    #if(ENABLE_MEDIA_BROADCAST)
        case OSD_COUNTRY_GERMANY:
    #endif
        case OSD_COUNTRY_INDONESIA:
        case OSD_COUNTRY_IRELAND:
        case OSD_COUNTRY_NORWAY:
        case OSD_COUNTRY_SWEDEN:
        case OSD_COUNTRY_MALAYSIA:
    #if(ENABLE_COUNTRY_SINGAPORE)
        case OSD_COUNTRY_SINGAPORE:
    #endif
        case OSD_COUNTRY_THAILAND:
    #if (ENABLE_COUNTRY_GHANA)
        case OSD_COUNTRY_GHANA:
    #endif
    #if (ENABLE_COUNTRY_KENYA)
        case OSD_COUNTRY_KENYA:
    #endif
    #if (ENABLE_COUNTRY_MYANMAR)
        case OSD_COUNTRY_MYANMAR:
    #endif
        {
            U16 u16ON_ID = msAPI_CM_Get_ON_ID_ByCountry(eCountry);

            if( u16ON_ID != 0)
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, u16ON_ID);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, u16ON_ID);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, u16ON_ID);
            }
        }
            break;

        default:
            break;
    }
}

void msAPI_CM_PrintAllProgram(void)
{
    WORD wPosition;
    WORD wProgramCount;
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);

    printf("[CM]Print all program LCN assign&sort: (%d)\n", wProgramCount);
    for(wPosition=0; wPosition < wProgramCount ; wPosition++)
    {
        printf("wLCN = %d, simuLCN = %d, service id = %d\n", pstDTVProgramIndexTable[wPosition].wLCN, pstDTVProgramIndexTable[wPosition].wSimu_LCN, pstDTVProgramIndexTable[wPosition].wService_ID);
    }
}



//****************************************************************************
/// Arrange Data Manager
/// @param bReArrangeLcn \b IN: reArrange LCN or not
/// - TRUE: Re-arrange
/// - FALSE: NO
/// @param bUpdatePosition \b IN: Update Position or not
/// - TRUE: Update
/// - FALSE: NO
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN __msAPI_CM_ArrangeDataManager(BOOLEAN bReArrangeLcn, BOOLEAN bUpdatePosition, BOOLEAN bSkipDupSrvRemove)
{
    MEMBER_SERVICETYPE bServiceType = E_SERVICETYPE_DTV, l_eServiceType = E_SERVICETYPE_DTV;
    WORD wPosition = 0, l_wPosition = 0;
    WORD wService_ID = 0;
    WORD wPhysicalChannelNumber = 0;
    WORD i;

    PRINT_CURRENT_LINE();
    printf("__msAPI_CM_ArrangeDataManager(bReArrangeLcn=%u, bUpdatePosition=%u,bSkipDupSrvRemove=%u)\n", bReArrangeLcn, bUpdatePosition, bSkipDupSrvRemove);
    //msAPI_CM_PrintAllProgram();

    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);


    if(bReArrangeLcn)
    {
        if(bUpdatePosition)
        {
            bServiceType = msAPI_CM_GetCurrentServiceType();
            wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
            wService_ID = msAPI_CM_GetService_ID(bServiceType, wPosition);
            wPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType, wPosition);
        }

        //for (i=0; i < MAX_DTVPROGRAM; i++)
        for (i=0; i < u16DTVProgramIndexTableArraySize; i++)
        {
            pstDTVProgramIndexTable[i].bServiceType = E_SERVICETYPE_INVALID;
            pstDTVProgramIndexTable[i].bServiceTypePrio = E_SERVICETYPE_PRIORITY_NONE;
            pstDTVProgramIndexTable[i].wPRIndex = INVALID_PRINDEX;
            pstDTVProgramIndexTable[i].wLCN = INVALID_LOGICAL_CHANNEL_NUMBER;
        }

#if(ENABLE_S2)//
        if(IsS2InUse())
        {
            msAPI_Timer_ResetWDT();

            if (TRUE == s2_IsLinkOfOrderValid())
            {
                s2_FillDTVProgramIndexTableWithOrder();
            }
            else
            {
                S2_FillDTVProgramIndexTableWithoutOrder();
            }
            msAPI_Timer_ResetWDT();
        }
        else
#endif
        {
            if (TRUE == IsLinkOfOrderValid(eCurDbSel))
            {
                FillDTVProgramIndexTableWithOrder(eCurDbSel);
            }
            else
            {
                FillDTVProgramIndexTableWithoutOrder(eCurDbSel);
            }
        }
    }

    UpdateProgramCount(E_SERVICETYPE_DTV);
    UpdateProgramCount(E_SERVICETYPE_DATA);
    UpdateProgramCount(E_SERVICETYPE_RADIO);

#if(ENABLE_S2)//
    if(IsS2InUse())
    {
        UpdateS2IDInfo();
    }
    else
#endif
    {
        UpdateIDInfo(eCurDbSel);
    }

    if(bReArrangeLcn)
    {
        if(FALSE == msAPI_CM_GetOpMode()
        #if ENABLE_CANAL_DIGITAL
        && (OSD_COUNTRY_NORWAY != OSD_COUNTRY_SETTING)
        #endif
        )
        {
        #if 1 // Use new function
            msAPI_CM_DistinguishNotNativeON_ID_By_Country(OSD_COUNTRY_SETTING);
        #else
            if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_NORWAY)
            #if DVB_T_C_DIFF_DB
                && (!IsDVBCInUse())
            #endif
                )
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x2242);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x2242);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x2242);
            }
            else if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_DENMARK)
            #if DVB_T_C_DIFF_DB
                && (!IsDVBCInUse())
            #endif
                )
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x20D0);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x20D0);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x20D0);
            }
            else if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_SWEDEN)
            #if DVB_T_C_DIFF_DB
                && (!IsDVBCInUse())
            #endif
                )
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x22F1);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x22F1);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x22F1);
            }
            else if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_FINLAND)
            #if DVB_T_C_DIFF_DB
                && (!IsDVBCInUse())
            #endif
                )
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x20F6);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x20F6);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x20F6);
            }
            else if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_IRELAND)
            #if DVB_T_C_DIFF_DB
                && (!IsDVBCInUse())
            #endif
                )

            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x2174);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x2174);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x2174);
            }
            else if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_INDONESIA)
            #if DVB_T_C_DIFF_DB
				&& (!IsDVBCInUse())
            #endif
				)
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x2168);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x2168);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x2168);
            }
         #if ENABLE_MEDIA_BROADCAST
            else if (( OSD_COUNTRY_SETTING== OSD_COUNTRY_GERMANY)
            #if DVB_T_C_DIFF_DB
				&& (!IsDVBCInUse())
            #endif
				)
            {
                DistinguishNotNativeON_ID(E_SERVICETYPE_DTV, 0x2114);
                DistinguishNotNativeON_ID(E_SERVICETYPE_RADIO, 0x2114);
                DistinguishNotNativeON_ID(E_SERVICETYPE_DATA, 0x2114);
            }
         #endif
        #endif
        }

        if(!IsS2InUse())
        {
            RestoreOriginalLCN(E_SERVICETYPE_DTV);
            RestoreOriginalLCN(E_SERVICETYPE_DATA);
            RestoreOriginalLCN(E_SERVICETYPE_RADIO);
        }
        if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
        {
            ArrangeLogicalChannelNumberforLCNSorting(E_LCN_TYPE_AUTO);
        }
        else
        {
            ArrangeLogicalChannelNumber(E_SERVICETYPE_DTV, E_LCN_TYPE_AUTO, bSkipDupSrvRemove);
            ArrangeLogicalChannelNumber(E_SERVICETYPE_DATA, E_LCN_TYPE_AUTO, bSkipDupSrvRemove);
            ArrangeLogicalChannelNumber(E_SERVICETYPE_RADIO, E_LCN_TYPE_AUTO, bSkipDupSrvRemove);
        }

        //msAPI_CM_DebugArrange();

        if(bUpdatePosition)
        {
            if((m_wPastServiceId != INVALID_SERVICE_ID) && (m_wPastOriginalNetworkId != INVALID_ON_ID))
            {
                BYTE cRFNumber = msAPI_CM_GetPhysicalChannelNumberByID(m_wPastOriginalNetworkId, m_wPastTransportStreamId);
                if(TRUE==msAPI_CM_GetServiceTypeAndPositionWithPCN(cRFNumber, m_wPastServiceId, &l_eServiceType, &l_wPosition))
                {
                    if (bServiceType != l_eServiceType)
                    {
                        msAPI_CM_SetCurrentServiceType(l_eServiceType);
                        #if (ENABLE_NZ_FREEVIEW&&MHEG5_ENABLE&&!BLOADER)//fixed for SI03::SIT 8
                            g_eCurrentRealServiceType=g_eCurrentUserServiceType = l_eServiceType;
                        #endif
                    }
                    if (wPosition != l_wPosition)
                    {
                        msAPI_CM_SetCurrentPosition(l_eServiceType, l_wPosition);
                        #if (ENABLE_NZ_FREEVIEW&&MHEG5_ENABLE&&!BLOADER)//fixed for SI03::SIT 8
                            if(l_eServiceType == E_SERVICETYPE_RADIO)
                                g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = l_wPosition;
                            #if NORDIG_FUNC //for Nordig Spec v2.0
                            else if(l_eServiceType == E_SERVICETYPE_DATA)
                                g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = l_wPosition;
                            #endif
                            else
                                g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = l_wPosition;
                        #endif
                    }
                }
                m_wPastServiceId = INVALID_SERVICE_ID;
                m_wPastOriginalNetworkId = INVALID_ON_ID;
                m_wPastTransportStreamId = INVALID_TS_ID;
            }
            else
            {
                if(TRUE==msAPI_CM_GetServiceTypeAndPositionWithPCN(wPhysicalChannelNumber, wService_ID, &l_eServiceType, &l_wPosition))
                {
                    if (wPosition != l_wPosition)
                    {
                        msAPI_CM_SetCurrentPosition(bServiceType, l_wPosition);
                        #if (ENABLE_NZ_FREEVIEW&&MHEG5_ENABLE&&!BLOADER)//fixed for SI03::SIT 8
                            g_eCurrentRealServiceType=g_eCurrentUserServiceType = l_eServiceType;
                            if(l_eServiceType == E_SERVICETYPE_RADIO)
                                g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = l_wPosition;
                            #if NORDIG_FUNC //for Nordig Spec v2.0
                            else if(l_eServiceType == E_SERVICETYPE_DATA)
                                g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = l_wPosition;
                            #endif
                            else
                                g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = l_wPosition;
                        #endif
                    }
                }
            }
        }

    #if ENABLE_CHPROC_ORDINAL_LIST // ENABLE_SBTVD_CM_APP
        //if( msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)       ||msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
        {
            msAPI_CHPROC_CM_InitOridial();
        }
    #endif

    }

#if ENABLE_S2
    if (!IsS2InUse())  //S2�²�Ҫ���TP
#endif
    _RestInvalidMUXAndNetwork();

    //msAPI_CM_PrintAllProgram();

    return TRUE;
}

//****************************************************************************
/// This function will arrange Data manager
/// @param bReArrangeLcn \b IN: Re-arrange LCN or NOT
/// - TRUE: Re-arrange
/// - FALSE: NO
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_ArrangeDataManager(BOOLEAN bReArrangeLcn, BOOLEAN bSkipDupSrvRemove)
{
    printf("msAPI_CM_ArrangeDataManager(bReArrangeLcn=%u, bSkipDupSrvRemove=%u)\n", bReArrangeLcn, bSkipDupSrvRemove);

    return __msAPI_CM_ArrangeDataManager(bReArrangeLcn, TRUE, bSkipDupSrvRemove);
}
//****************************************************************************
/// This function will sort data manager
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN ddmArrangeLogicalChannelNumber(MEMBER_SERVICETYPE eServiceType, E_MEMBER_LCN_TYPE eLcnType)
{
    if( FALSE == IsServiceTypeValid(eServiceType) )
    {
        return FALSE;
    }

    ArrangeLogicalChannelNumber(eServiceType, eLcnType, FALSE);

    return TRUE;
}

//****************************************************************************
/// This function will sort data manager
/// @return BOOLEAN: Function execution result
//****************************************************************************
#if 0
BOOLEAN msAPI_CM_SortDataManager(void)
{
    SortProgram(E_SERVICETYPE_DTV);
    SortProgram(E_SERVICETYPE_RADIO);
    UpdateOrderOfProgramTable(E_SERVICETYPE_DTV);
    UpdateOrderOfProgramTable(E_SERVICETYPE_RADIO);

    return TRUE;
}
#endif
//****************************************************************************
/// Get first position in PCN
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param cPCN \b IN: PCN
/// @param *pwPosition \b IN: pointer to position for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetFirstPositionInPCN(MEMBER_SERVICETYPE bServiceType, U16 u16PCN, WORD * pwPosition)
{
    WORD wPosition;
    WORD wOrder;
#if 1//(ENABLE_S2_WORD)
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    WORD wProgramCount;
    BOOLEAN eResult = FALSE;

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    //DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    if( FALSE == IsPhysicalChannelNumberValid(u16PCN) ||
        FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            break;


    #if(ENABLE_S2)
        if(IsS2InUse())
        {
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if( u16PCN == pMuxTable[cIDIndex].cRFChannelNumber )
            {
                *pwPosition = ConvertOrderToPosition(wOrder);
                eResult = TRUE;
                break;
            }
        }
        else
    #endif
        {
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;

        #if ENABLE_DVBC
            if( IsDVBCInUse() )
            {
                if (u16PCN == cIDIndex)
                {
                    *pwPosition = ConvertOrderToPosition(wOrder);
                    eResult = TRUE;
                    break;
                }
            }
            else
        #endif
            { // DVBT
                if( u16PCN == pMuxTable[cIDIndex].cRFChannelNumber )
                {
                    *pwPosition = ConvertOrderToPosition(wOrder);
                    eResult = TRUE;
                    break;
                }
            }

/*
#if ENABLE_T_C_COMBO
            if (IsDVBCInUse() && (cPCN == cIDIndex))
            {
                *pwPosition = ConvertOrderToPosition(wOrder);
                eResult = TRUE;
                break;
            }
            if( !IsDVBCInUse() && (cPCN == pMuxTable[cIDIndex].cRFChannelNumber) )
            {
                *pwPosition = ConvertOrderToPosition(wOrder);
                eResult = TRUE;
                break;
            }
#elif ENABLE_DVBC
            if (cPCN == cIDIndex)
            {
                *pwPosition = ConvertOrderToPosition(wOrder);
                eResult = TRUE;
                break;
            }
#else
            if( cPCN == pMuxTable[cIDIndex].cRFChannelNumber )
            {
                *pwPosition = ConvertOrderToPosition(wOrder);
                eResult = TRUE;
                break;
            }
#endif
*/
        }
    }

    return eResult;
}

#if ENABLE_SBTVD_DTV_SYSTEM
//****************************************************************************
/// Get first position in msjor number
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param cPCN \b IN: PCN
/// @param *pwPosition \b IN: pointer to position for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetFirstPositionInMajorNum(MEMBER_SERVICETYPE bServiceType, BYTE cMajorNum, WORD * pwPosition)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    BOOLEAN eResult = FALSE;

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);

    if( FALSE == IsPhysicalChannelNumberValid(cMajorNum) ||
        FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        if( cMajorNum == pstProgramIndexTable[wOrder].stLCN.bPhysicalChannel)
        {
            *pwPosition = ConvertOrderToPosition(wOrder);
            eResult = TRUE;
            break;
        }
    }

    return eResult;
}
#endif

//****************************************************************************
/// Get Service Type And Position With Physical Channel Number(PCN)
/// @param cPCN \b IN: Physical Channel Number
/// @param wService_ID \b IN: Service ID
/// @param peServiceType \b IN: pointer to service type to return
/// -@see MEMBER_SERVICETYPE
/// @param *pwPosition \b IN: pointer to position for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithPCN(WORD cPCN, WORD wService_ID, MEMBER_SERVICETYPE *peServiceType, WORD * pwPosition)
//BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithPCN(BYTE cPCN, WORD wService_ID, MEMBER_SERVICETYPE *peServiceType, WORD * pwPosition)
{
    WORD wOrder;

    if( FALSE == IsPhysicalChannelNumberValid(cPCN) ||
        FALSE == IsService_IDValid(wService_ID) )
    {
        return FALSE;
    }

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    wOrder = GetOrderOfSameServiceWithPCN(cPCN, wService_ID);
    //if( wOrder == INVALID_ORDER )
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return FALSE;
    }

#if 1 // Use new method
    *peServiceType = msAPI_DtvSys_Get_ServiceType_ByOrder( eCurDbSel, wOrder );
#else
 #if(ENABLE_S2)
    if(IsS2InUse())
    {
        *peServiceType = (MEMBER_SERVICETYPE)(m_astS2ProgramIndexTable[wOrder].bServiceType);
    }
    else
 #endif
    {
        *peServiceType = (MEMBER_SERVICETYPE)(m_astDTVProgramIndexTable[wOrder].bServiceType);
    }
#endif

    if( *peServiceType == E_SERVICETYPE_INVALID )
        return FALSE;

    *pwPosition = ConvertOrderToPosition(wOrder);

    return TRUE;
}

//****************************************************************************
/// Get Count Of Same Service With IDs
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param wService_ID \b IN: Service ID
/// @return BYTE: Count
//****************************************************************************
BYTE msAPI_CM_GetCountOfSameServiceWithIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID)
{
    BYTE cCountOfSameService;

    if( FALSE == IsTS_IDValid(wTransportStream_ID) ||
        FALSE == IsON_IDValid(wOriginalNetwork_ID) ||
        FALSE == IsService_IDValid(wService_ID) )
    {
        return 0;
    }

    cCountOfSameService = GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, TRUE) + GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, TRUE)+GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, TRUE);
    return cCountOfSameService;
}
//****************************************************************************
/// Get Service Type And Position With IDs and frequency.
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param pwPosition \b IN: pointer to Position for return
/// @param bCheckTsID \b IN: check TS ID or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDsAndRFCH(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID, U8 u8RFChannelNumber)
{
    WORD wOrder;
    MEMBER_SERVICETYPE bServiceType;


    if(bCheckTsID)bCheckTsID = IS_SID_UNIQUE_COUNTRY(m_eCountry) ? FALSE : TRUE;


    // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
    if( (bCheckTsID && (FALSE == IsTS_IDValid(wTransportStream_ID))) ||
        FALSE == IsON_IDValid(wOriginalNetwork_ID) ||
        FALSE == IsService_IDValid(wService_ID) ||
        0 == cOrdinal )
    {
        return FALSE;
    }

    if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_DTV;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_RADIO;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_DATA;
    }
    else
    {
        return FALSE;
    }

    wOrder = GetOrderOfSameServiceWithIDsAndRFCH(bServiceType, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal, bCheckTsID, u8RFChannelNumber);

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    //if( wOrder == INVALID_ORDER )
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return FALSE;
    }

#if 1
    *peServiceType = msAPI_DtvSys_Get_ServiceType_ByOrder( eCurDbSel, wOrder );
#else
    *peServiceType = (MEMBER_SERVICETYPE)m_astDTVProgramIndexTable[wOrder].bServiceType;
#endif

    if( *peServiceType == E_SERVICETYPE_INVALID )
        return FALSE;

    *pwPosition = ConvertOrderToPosition(wOrder);

    return TRUE;
}

//****************************************************************************
/// Get Service Type And Position With IDs And Service Type
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param wService_Type \b IN: Service Type
/// @param cOrdinal \b IN: Ordinal
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param pwPosition \b IN: pointer to Position for return
/// @param bCheckTsID \b IN: check TS ID or not
/// @return BOOLEAN: Function execution result
//****************************************************************************

BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDsandServiceType(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, MEMBER_SI_SERVICETYPE wService_Type, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID)
{
    WORD wOrder;
    MEMBER_SERVICETYPE bServiceType;


    if(bCheckTsID)bCheckTsID = IS_SID_UNIQUE_COUNTRY(m_eCountry) ? FALSE : TRUE;



    // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
    if( (bCheckTsID && (FALSE == IsTS_IDValid(wTransportStream_ID))) ||
        FALSE == IsON_IDValid(wOriginalNetwork_ID) ||
        FALSE == IsService_IDValid(wService_ID) ||
        0 == cOrdinal )
    {
        return FALSE;
    }

    if(E_TYPE_DTV == wService_Type)
    {
        if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DTV;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_RADIO;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DATA;
        }
        else
        {
            return FALSE;
        }
    }
    else if(E_TYPE_RADIO==wService_Type)
    {
        if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_RADIO;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DTV;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DATA;
        }
        else
        {
            return FALSE;
        }
    }
    else if(E_TYPE_DATA==wService_Type)
    {
        if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DATA;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DTV;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_RADIO;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DTV;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_RADIO;
        }
        else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
        {
            bServiceType = E_SERVICETYPE_DATA;
        }
        else
        {
            return FALSE;
        }
    }
    wOrder = GetOrderOfSameServiceWithIDs(bServiceType, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal, bCheckTsID);

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    //if( wOrder == INVALID_ORDER )
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return FALSE;
    }

#if 1
    *peServiceType = msAPI_DtvSys_Get_ServiceType_ByOrder( eCurDbSel, wOrder );
#else

 #if(ENABLE_S2)
    if(IsS2InUse())
    {
        *peServiceType = (MEMBER_SERVICETYPE)m_astS2ProgramIndexTable[wOrder].bServiceType;
    }
    else
 #endif
    {
        *peServiceType = (MEMBER_SERVICETYPE)m_astDTVProgramIndexTable[wOrder].bServiceType;
    }
#endif

    if( *peServiceType == E_SERVICETYPE_INVALID )
        return FALSE;

    *pwPosition = ConvertOrderToPosition(wOrder);

    return TRUE;
}

//****************************************************************************
/// Get Service Type And Position With IDs
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param pwPosition \b IN: pointer to Position for return
/// @param bCheckTsID \b IN: check TS ID or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID)
{
    WORD wOrder;
    MEMBER_SERVICETYPE bServiceType;


    if(bCheckTsID)bCheckTsID = IS_SID_UNIQUE_COUNTRY(m_eCountry) ? FALSE : TRUE;



    // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
    if( (bCheckTsID && (FALSE == IsTS_IDValid(wTransportStream_ID))) ||
        FALSE == IsON_IDValid(wOriginalNetwork_ID) ||
        FALSE == IsService_IDValid(wService_ID) ||
        0 == cOrdinal )
    {
        return FALSE;
    }

    if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_DTV;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_RADIO;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_DATA;
    }
    else
    {
        return FALSE;
    }

    wOrder = GetOrderOfSameServiceWithIDs(bServiceType, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal, bCheckTsID);

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    //if( wOrder == INVALID_ORDER )
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return FALSE;
    }

#if 1 // Use new method
    *peServiceType = bServiceType;//msAPI_DtvSys_Get_ServiceType_ByOrder( eCurDbSel, wOrder );
#else
  #if(ENABLE_S2)
    if(IsS2InUse())
    {
        *peServiceType = (MEMBER_SERVICETYPE)(m_astS2ProgramIndexTable[wOrder].bServiceType);
    }
    else
  #endif
    {
        *peServiceType = (MEMBER_SERVICETYPE)m_astDTVProgramIndexTable[wOrder].bServiceType;
    }
#endif

    if( *peServiceType == E_SERVICETYPE_INVALID )
        return FALSE;

    *pwPosition = ConvertOrderToPosition(wOrder);

    return TRUE;
}


//****************************************************************************
/// Get Service Type And Position With IDs And Pmt Pid
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param wPmt_Pid \b IN: New Pmt Pid
/// @param cOrdinal \b IN: Ordinal
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param pwPosition \b IN: pointer to Position for return
/// @param bCheckTsID \b IN: check TS ID or not
/// @param bCheckPmtPID \b IN: check PMT PID or not
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetServiceTypeAndPositionWithIDsAndPmtPid(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, WORD wPmt_Pid, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition, BOOLEAN bCheckTsID)
{
    WORD wOrder;
    MEMBER_SERVICETYPE bServiceType;


    if(bCheckTsID)bCheckTsID = IS_SID_UNIQUE_COUNTRY(m_eCountry) ? FALSE : TRUE;



    // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
    if( (bCheckTsID && (FALSE == IsTS_IDValid(wTransportStream_ID))) ||
        FALSE == IsON_IDValid(wOriginalNetwork_ID) ||
        FALSE == IsService_IDValid(wService_ID) ||
        0 == cOrdinal )
    {
        return FALSE;
    }

    if( cOrdinal <= GetCountOfSameServiceWithIDsAndPmtPid(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wPmt_Pid, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_DTV;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithIDsAndPmtPid(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wPmt_Pid, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_RADIO;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithIDsAndPmtPid(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, wPmt_Pid, bCheckTsID) )
    {
        bServiceType = E_SERVICETYPE_DATA;
    }
    else
    {
        return FALSE;
    }

    wOrder = GetOrderOfSameServiceWithIDs(bServiceType, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal, bCheckTsID);

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    //if( wOrder == INVALID_ORDER )
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return FALSE;
    }

#if 1 // Use new method
    *peServiceType = bServiceType;//msAPI_DtvSys_Get_ServiceType_ByOrder( eCurDbSel, wOrder );
#else
  #if(ENABLE_S2)
    if(IsS2InUse())
    {
        *peServiceType = (MEMBER_SERVICETYPE)(m_astS2ProgramIndexTable[wOrder].bServiceType);
    }
    else
  #endif
    {
        *peServiceType = (MEMBER_SERVICETYPE)m_astDTVProgramIndexTable[wOrder].bServiceType;
    }
#endif

    if( *peServiceType == E_SERVICETYPE_INVALID )
        return FALSE;

    *pwPosition = ConvertOrderToPosition(wOrder);

    return TRUE;
}

//****************************************************************************
/// Move Program
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param wFromPosition \b IN: from Position
/// @param wToPosition \b IN: To Position
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_MoveProgram(MEMBER_SERVICETYPE bServiceType, WORD wFromPosition, WORD wToPosition, MEMBER_SERVICETYPE btoServiceType)
{
    WORD wFromOrder, wToOrder;
    WORD wFromPRIndex, wToPRIndex;
    CHANNEL_ATTRIBUTE stFromCHAttribute, stToCHAttribute;
    MEMBER_SERVICETYPE l_eServiceType,bCurServiceType;
    WORD l_wPosition = 0,wCurPosition;
    WORD wCurService_ID;
    WORD wPhysicalChannelNumber;
  #if (ASTRA_HD_ENABLE)
    WORD wFromLcn,wToLcn;
  #endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsServiceTypeValid(btoServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wFromPosition) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(btoServiceType, wToPosition) )
    {
        return FALSE;
    }

    bCurServiceType = msAPI_CM_GetCurrentServiceType();
    wCurPosition = msAPI_CM_GetCurrentPosition(bCurServiceType);
    wCurService_ID = msAPI_CM_GetService_ID(bCurServiceType, wCurPosition);
    wPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bCurServiceType, wCurPosition);


    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);

    wFromOrder = ConvertPositionToOrder(bServiceType, wFromPosition);
    if( wFromOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

    wToOrder = ConvertPositionToOrder(btoServiceType, wToPosition);
    if( wToOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wFromPRIndex = m_astS2ProgramIndexTable[wFromOrder].wPRIndex;
        GetProgramTable(wFromPRIndex, (BYTE *)&stFromCHAttribute, E_DATA_MISC);
        stFromCHAttribute.bIsMove = TRUE;
        m_astS2ProgramIndexTable[wFromOrder].bIsMove = stFromCHAttribute.bIsMove;

        wToPRIndex = m_astS2ProgramIndexTable[wToOrder].wPRIndex;
        GetProgramTable(wToPRIndex, (BYTE *)&stToCHAttribute, E_DATA_MISC);
        stToCHAttribute.bIsMove = TRUE;
        m_astS2ProgramIndexTable[wToOrder].bIsMove = stToCHAttribute.bIsMove;
      #if (ASTRA_HD_ENABLE)
	GetProgramTable(wFromPRIndex, (BYTE *)&wFromLcn, E_DATA_LCN);
	GetProgramTable(wToPRIndex, (BYTE *)&wToLcn, E_DATA_LCN);
	printf("wFromLcn = %d,wToLcn = %d\n",wFromLcn,wToLcn);
	m_astS2ProgramIndexTable[wFromOrder].wLCN = wToLcn;
	m_astS2ProgramIndexTable[wToOrder].wLCN = wFromLcn;
	wTempLcn = wFromLcn;
	wFromLcn = wToLcn;
	wToLcn = wTempLcn;
	printf("wFromLcn = %d,wToLcn = %d\n",wFromLcn,wToLcn);
     #endif
    }
    else
#endif
    {
        wFromPRIndex = pstProgramIndexTable[wFromOrder].wPRIndex;
        if( FALSE == GetProgramTable(wFromPRIndex, (BYTE *)&stFromCHAttribute, E_DATA_MISC) )
            return FALSE;
        stFromCHAttribute.bIsMove = TRUE;
        pstProgramIndexTable[wFromOrder].bIsMove = stFromCHAttribute.bIsMove;

        wToPRIndex = pstProgramIndexTable[wToOrder].wPRIndex;
        if( FALSE == GetProgramTable(wToPRIndex, (BYTE *)&stToCHAttribute, E_DATA_MISC) )
            return FALSE;
        stToCHAttribute.bIsMove = TRUE;
        pstProgramIndexTable[wToOrder].bIsMove = stToCHAttribute.bIsMove;

#if (ASTRA_HD_ENABLE)
        if(GetASTRA_HD_ENABLE())
        {
            GetProgramTable(wFromPRIndex, (BYTE *)&wFromLcn, E_DATA_LCN);
            GetProgramTable(wToPRIndex, (BYTE *)&wToLcn, E_DATA_LCN);

            DEBUG_DTV_SYS(printf("wFromLcn = %d,wToLcn = %d\n",wFromLcn,wToLcn););
            pstProgramIndexTable[wFromOrder].wLCN = wToLcn;
            pstProgramIndexTable[wToOrder].wLCN = wFromLcn;
            //wFromLcn and  wToLcn exchange
            wFromLcn = wFromLcn + wToLcn;
            wToLcn = wFromLcn - wToLcn;
            wFromLcn = wFromLcn -wToLcn;
            DEBUG_DTV_SYS(printf("wFromLcn = %d,wToLcn = %d\n",wFromLcn,wToLcn););
        }
 #endif
    }

    SwapProgram(wFromOrder, wToOrder);

//#if (ENABLE_DTV_EPG)
    //MApp_Epg_MoveSrvBuffer(wFromOrder, wToOrder);
//#endif  //#if (ENABLE_DTV_EPG)

    UpdateOrderOfProgramTable(bServiceType);
    UpdateOrderOfProgramTable(btoServiceType);

    msAPI_CM_GetServiceTypeAndPositionWithPCN(wPhysicalChannelNumber, wCurService_ID, &l_eServiceType, &l_wPosition);
    if ((wCurPosition != l_wPosition) || (bServiceType != btoServiceType))      //if move between the different servicetype
    {
        msAPI_CM_SetCurrentPosition(bCurServiceType, l_wPosition);
    }
        //sync channel info
#if MHEG5_ENABLE
    g_eCurrentRealServiceType=g_eCurrentUserServiceType = bCurServiceType;
    if(bCurServiceType == E_SERVICETYPE_RADIO)
        g_wCurrentRadioRealServicePosition=g_wCurrentRadioUserServicePosition = l_wPosition;
#if NORDIG_FUNC //for Nordig Spec v2.0
    else if(bCurServiceType == E_SERVICETYPE_DATA)
        g_wCurrentDataRealServicePosition=g_wCurrentDataUserServicePosition = l_wPosition;
#endif
    else
        g_wCurrentTVRealServicePosition=g_wCurrentTVUserServicePosition = l_wPosition;
#endif
   if(!SetProgramTable(wFromPRIndex, (BYTE *)&stFromCHAttribute, E_DATA_MISC))
        return FALSE;

   if(!SetProgramTable(wToPRIndex, (BYTE *)&stToCHAttribute, E_DATA_MISC))
        return FALSE;

   #if (ASTRA_HD_ENABLE)
    if(GetASTRA_HD_ENABLE())
    {
        if(!SetProgramTable(wFromPRIndex, (BYTE *)&wFromLcn, E_DATA_LCN))
            return FALSE;

        if(!SetProgramTable(wToPRIndex, (BYTE *)&wToLcn, E_DATA_LCN))
            return FALSE;
    }
   #endif

    return TRUE;
}

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
FUNCTION_RESULT msAPI_CM_MoveLCN(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wLCN)
{
    WORD wOrder;

    MEMBER_SERVICETYPE bCurServiceType ,l_eServiceType;
    WORD wCurPosition = 0,l_wPosition;
    WORD wService_ID = 0;
    WORD wPhysicalChannelNumber = 0;

    //DBG_CM: printf("msAPI_CM_MoveProgram[Svr:%bu][From:%u][To:%u]\n",bServiceType,wFromPosition,wToPosition);
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return E_RESULT_INVALID_PARAMETER;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return E_RESULT_INVALID_PARAMETER;
    }

    bCurServiceType = msAPI_CM_GetCurrentServiceType();
    wCurPosition = msAPI_CM_GetCurrentPosition(bCurServiceType);
    wService_ID = msAPI_CM_GetService_ID(bCurServiceType, wCurPosition);
    wPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bCurServiceType, wCurPosition);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

    #if 0
    ChangeLCN(bServiceType, wPosition, wLCN);
    #else
    SwapLCN(bServiceType, wPosition, wLCN);
    #endif
    SortProgram(bServiceType);
    UpdateOrderOfProgramTable(bServiceType);

    if(TRUE==msAPI_CM_GetServiceTypeAndPositionWithPCN(wPhysicalChannelNumber, wService_ID, &l_eServiceType, &l_wPosition))
    {
        if (wCurPosition != l_wPosition)
        {
            msAPI_CM_SetCurrentPosition(bCurServiceType, l_wPosition);
        }
    }

    return E_RESULT_SUCCESS;
}
#endif

//****************************************************************************
/// Set TS to Update
/// @param bCheck \b IN: only update TS or not
/// @param wTS_ID \b IN: TS ID
//****************************************************************************
void msAPI_CM_Set_TS_Update(BOOLEAN bCheck, WORD wTS_ID)
{
    _bOnlyUpdateCurTS=bCheck;
    _wCurTS_ID=wTS_ID;
}

BOOLEAN msAPI_CM_RemoveProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    BOOLEAN bRemoved,eResult;
    MEMBER_SERVICETYPE eServiceType2, eServiceType1;
    WORD wPosition2, wPosition1;
    WORD wService_ID,wPhysicalChannelNumber,wProgCount;

    eServiceType2 = msAPI_CM_GetCurrentServiceType();
    wPosition2 = msAPI_CM_GetCurrentPosition(eServiceType2);
    wService_ID = msAPI_CM_GetService_ID(eServiceType2, wPosition2);
    wPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(eServiceType2,wPosition2);

    bRemoved = RemoveProgram(bServiceType,wPosition);

    if(bRemoved)
    {
        __msAPI_CM_ArrangeDataManager(TRUE,FALSE,FALSE);
        wProgCount = msAPI_CM_CountProgram(eServiceType2, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
        if(wProgCount)
        {
            //find service with same RF and S_ID
            eServiceType1 = eServiceType2;
            eResult = msAPI_CM_GetServiceTypeAndPositionWithPCN(wPhysicalChannelNumber, wService_ID, &eServiceType1, &wPosition1);
            if(TRUE != eResult || eServiceType1 != eServiceType2)
            {
                //find first service of current physical channel if service is not exist
                if(TRUE != msAPI_CM_GetFirstPositionInPCN(eServiceType2, wPhysicalChannelNumber, &wPosition1))
                {
                    wPosition1 = msAPI_CM_GetFirstProgramPosition(eServiceType2, FALSE);
                    if(INVALID_PROGRAM_POSITION == wPosition1)
                    {
                        //printf("Get program fail from bServiceType %bu\n", bServiceType);
                    }
                }
            }
            if(wPosition1 != wPosition2)
            {
                msAPI_CM_SetCurrentPosition(eServiceType2, wPosition1);
            }

        }
        else
        {
            //service type change
            eServiceType2 = (eServiceType2 == E_SERVICETYPE_DTV ? E_SERVICETYPE_RADIO : E_SERVICETYPE_DTV);
            msAPI_CM_SetCurrentServiceType(eServiceType2);
            wPosition2 = msAPI_CM_GetFirstProgramPosition(eServiceType2, FALSE);
            msAPI_CM_SetCurrentPosition(eServiceType2, wPosition2);
        }
    }
    return bRemoved;
}

//****************************************************************************
/// Remove Program
/// @param peServiceType \b IN: Service Type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: Position
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN RemoveProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();

    WORD wFromOrder;
    WORD wToOrder;
    WORD wRemovedPosition;
    WORD wPRIndex;
    WORD i;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    wRemovedPosition = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL) - 1;
    wFromOrder = ConvertPositionToOrder(bServiceType, wPosition);
    wToOrder = ConvertPositionToOrder(bServiceType, wRemovedPosition);
    {
        BYTE name[MAX_SERVICE_NAME];
        msAPI_CM_GetServiceName(bServiceType,wPosition,name);
        printf("%s.....sid %x name %s\n",__FUNCTION__,msAPI_CM_GetService_ID(bServiceType,wPosition),
            name);
    }

    MoveProgram(wFromOrder, wToOrder);
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        UpdateOrderOfProgramTable(E_SERVICETYPE_DATA);
        UpdateOrderOfProgramTable(E_SERVICETYPE_DTV);
        UpdateOrderOfProgramTable(E_SERVICETYPE_RADIO);
    }
    else
    {
    UpdateOrderOfProgramTable(bServiceType);
    }

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
#else
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = m_astDTVProgramIndexTable;
  #if(ENABLE_S2)
    if( IsS2InUse() )   pstDTVProgramIndexTable = m_astS2ProgramIndexTable;
  #endif
#endif

//#if(ENABLE_S2)
#if 0//(ENABLE_S2 && (ENABLE_API_DTV_SYSTEM_2015==0) )
    if(IsS2InUse())
    {
        wPRIndex = pstDTVProgramIndexTable[wToOrder].wPRIndex;
        FillProgramIndexWithDefault(&pstDTVProgramIndexTable[wToOrder]);

        S2_ActiveProgramEntity(wPRIndex, FALSE);

        UpdateProgramCount(bServiceType);

        if(bServiceType == E_SERVICETYPE_DATA && msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL))
        {
            for(i=0;i<msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);i++)
            {
                memcpy(&pstDTVProgramIndexTable[wToOrder-i],
                    &pstDTVProgramIndexTable[wToOrder-i-1 ],
                    sizeof(DTVPROGRAMINDEX));
            }
            FillProgramIndexWithDefault(&pstDTVProgramIndexTable[wToOrder-msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL)]);
            UpdateOrderOfProgramTable(E_SERVICETYPE_RADIO);
        }
    }
    else
#endif
    {
        wPRIndex = pstDTVProgramIndexTable[wToOrder].wPRIndex;
        FillProgramIndexWithDefault(&pstDTVProgramIndexTable[wToOrder]);

        ActiveProgramEntity_DBSel(eCurDbSel, wPRIndex, FALSE);

        UpdateProgramCount(bServiceType);

        if(bServiceType == E_SERVICETYPE_DATA && msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL))
        {
            for(i=0;i<msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);i++)
            {
                memcpy(&pstDTVProgramIndexTable[wToOrder-i],
                    &pstDTVProgramIndexTable[wToOrder-i-1 ],
                    sizeof(DTVPROGRAMINDEX));
            }
            FillProgramIndexWithDefault(&pstDTVProgramIndexTable[wToOrder-msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL)]);
            UpdateOrderOfProgramTable(E_SERVICETYPE_RADIO);
        }
    }

#if (ENABLE_DTV_EPG)
    if(_pfNotify_CM_RemoveProgram)
    {
        _pfNotify_CM_RemoveProgram(wFromOrder);
    }
#endif

    return TRUE;
}

//****************************************************************************
/// Remove Mismatched Program
/// @param peServiceType \b IN: Service Type
/// -@see MEMBER_SERVICETYPE
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @param pwService_ID \b IN: Service ID
/// @param peService_Type \b IN: peService Type
/// @param cCountOfServiceID \b IN: Count Of Service ID
/// @return BOOLEAN: Function execution result
//****************************************************************************
static U16 RemoveMismatchedProgram(MEMBER_SERVICETYPE bServiceType, WORD cRFChannelNumber, BYTE cPlp_ID, BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, U16 u16CountOfServiceID, BYTE sat, WORD freq)
{
    // Unused warning...
    peService_Type = peService_Type;
    sat = sat;
    freq = freq;

    WORD u16MaxMuxNum;
    U16 wIDIndex;
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD wServiceId;
    WORD i;
#if 1//(ENABLE_S2_FAST_SCAN)
    WORD j;
    WORD u16RemovedProgramCount;
#else
    BYTE j;
    BYTE cRemovedProgramCount;
#endif //#if(ENABLE_S2_FAST_SCAN)

#if(ENABLE_S2)
    WORD wCurIDindex=0;
    MEMBER_SERVICETYPE eCurServiceType;
#endif


    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);

    u16MaxMuxNum = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);


    if( FALSE == IsServiceTypeValid(bServiceType) ||
        FALSE == IsPhysicalChannelNumberValid(cRFChannelNumber) )
    {
        return 0;
    }

    //ASTRA_HD Don't need remove program when ts change
    //spec 2.8: handling of Old Service
#if(ASTRA_HD_ENABLE)
    if(GetASTRA_HD_ENABLE())
    {
        return 0;
    }
#endif


  #if(ENABLE_DVBC)
    if( IsDVBCInUse() ) // DVBC
    {
        UNUSED(cPlp_ID);
        UNUSED(cHpLp);
        wIDIndex = cRFChannelNumber;
        PRINT_TODO();
    }
    else
  #endif
#if(ENABLE_S2)
    if( IsS2InUse() ) // DVBS
    {
        UNUSED(cPlp_ID);
        UNUSED(cHpLp);
        UNUSED(cRFChannelNumber);

        // cRFChannelNumber is BYTE ,but the wIDIndex is WORD, so it not match form si
        // Only dvbs IDindex is WORD,so reget the IDindex to match
        eCurServiceType = msAPI_CM_GetCurrentServiceType();
        wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
        wCurIDindex = msAPI_CM_GetPhysicalChannelNumber(eCurServiceType, wPosition);
        //wIDIndex = cRFChannelNumber;
        //patch end

        for(wIDIndex=0; wIDIndex < u16MaxMuxNum; wIDIndex++)
        {
            if( (sat == pMuxTable[wIDIndex].SatelliteId)
              &&(freq == pMuxTable[wIDIndex].u32S2Frequency)
              &&(wIDIndex == wCurIDindex))  //(wIDIndex == cRFChannelNumber)
            {
              //printf(">>>>> wIDIndex = 0x%x, cRFChannelNumber =%x\n", wIDIndex,cRFChannelNumber);
              break;
            }
        }
    }
    else
#endif
    {
        for(wIDIndex=0; wIDIndex < u16MaxMuxNum; wIDIndex++)
        {
            if( (cHpLp == pMuxTable[wIDIndex].cHpLp)
             && (cPlp_ID == pMuxTable[wIDIndex].cPLPID)
             && (cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber) )
            {
                break;
            }
        }
    }

    if( u16MaxMuxNum <= wIDIndex )
    {
        return 0;
    }

    u16RemovedProgramCount = 0;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;

    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        wIDIndex = pstDTVProgramIndexTable[wOrder].cIDIndex;

    #if (ENABLE_S2)
        if( IsS2InUse() )
        {
            //printf("r\n_____default__%d_%d_%d___comp_%d_%d_%d___",wIDIndex,pMuxTable[wIDIndex].SatelliteId,pMuxTable[wIDIndex].u32S2Frequency,cRFChannelNumber,sat,freq);
            if( (sat== pMuxTable[wIDIndex].SatelliteId)
              &&(freq== pMuxTable[wIDIndex].u32S2Frequency)
              &&(wIDIndex == wCurIDindex) )
            {
                wServiceId = pstDTVProgramIndexTable[wOrder].wService_ID;

                //printf("\r\n+++wOrder=%d+++wServiceId=%d+++++bServiceType=%d",wOrder,wServiceId,bServiceType);
                for(j=0; j < u16CountOfServiceID; j++)
                {
                    //printf("\r\n____wServiceId=%d____bServiceType=%d",pwService_ID[j],peService_Type[j]);
                    if(pwService_ID[j] == wServiceId && peService_Type[j] == bServiceType)
                    {
                        break;
                    }
                }
                if( u16CountOfServiceID <= j )
                {
                    RemoveProgram(bServiceType, wPosition);
                    u16RemovedProgramCount++;
                }
            }
        }
        else
    #endif
        {
        #if ENABLE_DVBC
            if (IsDVBCInUse() && (wIDIndex != cRFChannelNumber))
            {
                wPosition--;
                continue;
            }
        #endif

        #if 1//ENABLE_T_C_COMBO
            if(
                (IsDVBCInUse()&&(wIDIndex == cRFChannelNumber))
               ||( ( IsDVBTInUse()||IsISDBTInUse())
                  &&(cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber)
                  &&(cPlp_ID == pMuxTable[wIDIndex].cPLPID)
                  &&(cHpLp == pMuxTable[wIDIndex].cHpLp)
                 )
              )
        #elif ENABLE_DVBC
            if (wIDIndex == cRFChannelNumber)
        #else // DVBT
            if( (cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber)
                && ((cPlp_ID == pMuxTable[wIDIndex].cPLPID)
                &&(cHpLp == pMuxTable[wIDIndex].cHpLp)))
        #endif
            {

                wServiceId = pstDTVProgramIndexTable[wOrder].wService_ID;

                for(j=0; j < u16CountOfServiceID; j++)
                {
                    if(pwService_ID[j] == wServiceId )//the service type maybe changed, don't check type//&& peService_Type[j] == bServiceType)
                    {
                        break;
                    }
                }

                if( ( u16CountOfServiceID <= j )
                  ||((_wCurTSID != INVALID_TS_ID) && (pMuxTable[wIDIndex].wTransportStream_ID != _wCurTSID)))
                {
                    RemoveProgram(bServiceType, wPosition);
                    u16RemovedProgramCount++;
                }
            }
        }

        wPosition--;
    }

    return u16RemovedProgramCount;
}

BOOLEAN IsServiceMoved(void)
{
    return _bServiceMoved;
}

void ResetServiceMovedFlag(void)
{
    _bServiceMoved = FALSE;
}

void EnableServiceMovedFlag(void)
{
    _bServiceMoved = TRUE;
}

static U16 RemoveMismatchedProgram_ALLPCN(MEMBER_SERVICETYPE bServiceType, MS_SI_SHORT_SERVICEINFO *pwService_Info, MEMBER_SERVICETYPE *peService_Type, U16 cCountOfServiceID)
{
    // Unused warning...
    peService_Type = peService_Type;

    WORD u16MaxMuxNum;
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    U16 wIDIndex;
    WORD wServiceId;
    WORD wTsid;
    WORD i;
    U16 j,m;
    U16 cRemovedProgramCount;
    WORD wValue;
#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);

    u16MaxMuxNum = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
#endif

    MEMBER_SERVICETYPE eCurServiceType = msAPI_CM_GetCurrentServiceType();
    WORD wCurPosition = msAPI_CM_GetCurrentPosition(eCurServiceType);
    TypDtvDbSel eDtvDbSel = msAPI_DTV_Comm_Get_DBSel();
    WORD wCurOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, eCurServiceType, wCurPosition);

    if( FALSE == IsServiceTypeValid(bServiceType))
    {
        return 0;
    }

    cRemovedProgramCount = 0;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;

    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        wServiceId = pstDTVProgramIndexTable[wOrder].wService_ID;
        wTsid = pMuxTable[pstDTVProgramIndexTable[wOrder].cIDIndex].wTransportStream_ID;
        for(j=0; j < cCountOfServiceID; j++)
        {
            if((pwService_Info[j].wService_ID == wServiceId )
             &&(pwService_Info[j].wTransportStream_ID == wTsid))//the service type maybe changed, don't check type//&& peService_Type[j] == bServiceType)
            {
                break;
            }
        }

        if( cCountOfServiceID <= j )
        {
            for(m=0; m < cCountOfServiceID; m++)
            {
                if((pwService_Info[m].wService_ID == wServiceId )
                    && (pwService_Info[m].wTransportStream_ID != pMuxTable[pstDTVProgramIndexTable[wOrder].cIDIndex].wTransportStream_ID))
                {
                    for(wIDIndex=0; wIDIndex < u16MaxMuxNum; wIDIndex++)
                    {
                        if(pwService_Info[m].wTransportStream_ID == pMuxTable[wIDIndex].wTransportStream_ID)
                        {
                            GetProgramTable_DBSel(eCurDbSel, pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wValue, E_DATA_ID_INDEX);
                            wValue = wIDIndex;
                            SetProgramTable_DBSel(eCurDbSel, pstDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wValue), E_DATA_ID_INDEX);
                            cRemovedProgramCount++;

                            if(wCurOrder == wOrder)
                               EnableServiceMovedFlag();

                            break;
                        }
                    }
                    break;
                }
            }
            if( cCountOfServiceID <= m )
            {
                RemoveProgram(bServiceType, wPosition);
                cRemovedProgramCount++;
            }
        }

        wPosition--;
    }

    return cRemovedProgramCount;
}

U16 msAPI_CM_RemoveMismatchedProgram_ALLPCN(MS_SI_SHORT_SERVICEINFO *pwService_Info, MEMBER_SERVICETYPE *peService_Type, U16 cCountOfServiceID)
{
    U16 cRemovedProgramCount=0;
    MEMBER_SERVICETYPE bServiceType, l_eServiceType;
    WORD wPosition, l_wPosition;
    WORD wService_ID;
    WORD wPhysicalChannelNumber;
    WORD wProgCount;
    BOOLEAN eResult;

    //PRINT_CURRENT_LINE();

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    wService_ID = msAPI_CM_GetService_ID(bServiceType, wPosition);
    wPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wPosition);

    {
        cRemovedProgramCount += RemoveMismatchedProgram_ALLPCN(E_SERVICETYPE_DTV, pwService_Info, peService_Type, cCountOfServiceID);
        cRemovedProgramCount += RemoveMismatchedProgram_ALLPCN(E_SERVICETYPE_DATA, pwService_Info, peService_Type, cCountOfServiceID);
        cRemovedProgramCount += RemoveMismatchedProgram_ALLPCN(E_SERVICETYPE_RADIO, pwService_Info, peService_Type, cCountOfServiceID);
    }

    if(cRemovedProgramCount)
    {
        __msAPI_CM_ArrangeDataManager(TRUE,FALSE,FALSE);
        wProgCount = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
        if(wProgCount)
        {
            //find service with same RF and S_ID
            l_eServiceType = bServiceType;
            eResult = msAPI_CM_GetServiceTypeAndPositionWithPCN(wPhysicalChannelNumber, wService_ID, &l_eServiceType, &l_wPosition);
            if(TRUE != eResult || l_eServiceType != bServiceType)
            {
                //find first service of current physical channel if service is not exist
                if(TRUE != msAPI_CM_GetFirstPositionInPCN(bServiceType, wPhysicalChannelNumber, &l_wPosition))
                {
                    l_wPosition = msAPI_CM_GetFirstProgramPosition(bServiceType, FALSE);
                    if(INVALID_PROGRAM_POSITION == l_wPosition)
                    {
                        //printf("Get program fail from bServiceType %bu\n", bServiceType);
                    }
                }
            }
            if((l_wPosition != wPosition)&&(!IsServiceMoved()))
            {
                msAPI_CM_SetCurrentPosition(bServiceType, l_wPosition);
            }
            else if(IsServiceMoved())
            {
                ResetServiceMovedFlag();
            }
        }
        else
        {
            //service type change
            bServiceType = (bServiceType == E_SERVICETYPE_DTV ? E_SERVICETYPE_RADIO : E_SERVICETYPE_DTV);
            msAPI_CM_SetCurrentServiceType(bServiceType);
            wPosition = msAPI_CM_GetFirstProgramPosition(bServiceType, FALSE);
            msAPI_CM_SetCurrentPosition(bServiceType, wPosition);
        }

    }

    return cRemovedProgramCount;
}

//****************************************************************************
/// Remove Same Program
/// @param peServiceType \b IN: Service Type
/// -@see MEMBER_SERVICETYPE
//****************************************************************************
static void RemoveSameService(MEMBER_SERVICETYPE bServiceType)//for Nordig Spec
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD i;

    if( FALSE == IsServiceTypeValid(bServiceType))
    {
        return ;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            if(m_astS2ProgramIndexTable[wOrder].eLCNAssignmentType & E_LCN_SAME_SERVICE)
            {
            #if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
            #endif

                RemoveProgram(bServiceType, wPosition);
            }
        }
        else
    #endif
        {
            if(pstDTVProgramIndexTable[wOrder].eLCNAssignmentType & E_LCN_SAME_SERVICE)
            {
                msAPI_Timer_ResetWDT();

                RemoveProgram(bServiceType, wPosition);
            }
        }
        wPosition--;
    }

}

//****************************************************************************
/// Remove Mismatched Program
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @param peServiceType \b IN: Service Type
/// -@see MEMBER_SERVICETYPE
/// @param pwService_ID \b IN: Service ID
/// @param cCountOfServiceID \b IN: Count Of Service ID
/// @return BYTE: Removed Program Count
//****************************************************************************

U16 msAPI_CM_RemoveMismatchedProgram(WORD cRFChannelNumber,WORD wTSID, BYTE cPLP_ID,BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, U16 u16CountOfServiceID,BYTE sat,WORD freq)
{
    U16 u16RemovedProgramCount=0;
    MEMBER_SERVICETYPE bServiceType, l_eServiceType;
    WORD wPosition, l_wPosition;
    WORD wService_ID;
    WORD wPhysicalChannelNumber;
    WORD wProgCount;
    BOOLEAN eResult;

    //PRINT_CURRENT_LINE();

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    wService_ID = msAPI_CM_GetService_ID(bServiceType, wPosition);
    wPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wPosition);

    if( FALSE == IsPhysicalChannelNumberValid(cRFChannelNumber) )
    {
        return 0;
    }

    if(u16CountOfServiceID>0)
    {
        _wCurTSID=wTSID;
    }

    {
        u16RemovedProgramCount += RemoveMismatchedProgram(E_SERVICETYPE_DTV, cRFChannelNumber, cPLP_ID, cHpLp, pwService_ID, peService_Type, u16CountOfServiceID,sat,freq);
        u16RemovedProgramCount += RemoveMismatchedProgram(E_SERVICETYPE_DATA, cRFChannelNumber, cPLP_ID, cHpLp, pwService_ID, peService_Type, u16CountOfServiceID,sat,freq);
        u16RemovedProgramCount += RemoveMismatchedProgram(E_SERVICETYPE_RADIO, cRFChannelNumber, cPLP_ID, cHpLp, pwService_ID, peService_Type, u16CountOfServiceID,sat,freq);
    }

    _wCurTSID=INVALID_TS_ID;
    if(u16RemovedProgramCount)
    {
        __msAPI_CM_ArrangeDataManager(TRUE,FALSE,FALSE);
        wProgCount = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
        if(wProgCount)
        {
            //find service with same RF and S_ID
            l_eServiceType = bServiceType;
            eResult = msAPI_CM_GetServiceTypeAndPositionWithPCN(wPhysicalChannelNumber, wService_ID, &l_eServiceType, &l_wPosition);
            if(TRUE != eResult || l_eServiceType != bServiceType)
            {
                //find first service of current physical channel if service is not exist
                if(TRUE != msAPI_CM_GetFirstPositionInPCN(bServiceType, wPhysicalChannelNumber, &l_wPosition))
            {
                l_wPosition = msAPI_CM_GetFirstProgramPosition(bServiceType, FALSE);
                if(INVALID_PROGRAM_POSITION == l_wPosition)
                {
                    //printf("Get program fail from bServiceType %bu\n", bServiceType);
                    }
                }
            }
            if(l_wPosition != wPosition)
            {
                msAPI_CM_SetCurrentPosition(bServiceType, l_wPosition);
            }

        }
        else
        {
            //service type change
            bServiceType = (bServiceType == E_SERVICETYPE_DTV ? E_SERVICETYPE_RADIO : E_SERVICETYPE_DTV);
            msAPI_CM_SetCurrentServiceType(bServiceType);
            wPosition = msAPI_CM_GetFirstProgramPosition(bServiceType, FALSE);
            msAPI_CM_SetCurrentPosition(bServiceType, wPosition);
        }

    }

    return u16RemovedProgramCount;
}

//****************************************************************************
/// Fill Program Data With Default
/// @param pDTVProgramData \b IN: DTV Program Data
/// -@see DTV_CHANNEL_INFO
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_FillProgramDataWithDefault(DTV_CHANNEL_INFO *pDTVProgramData)
{
    if( pDTVProgramData )
    {
        return FillProgramDataWithDefault((BYTE *)pDTVProgramData, E_DATA_ALL);
    }

    return FALSE;
}

#if 0//ENABLE_SCAN_CM_DEBUG
//****************************************************************************
/// Print All Program
//****************************************************************************
void msAPI_CM_PrintAllProgram(void)
{
    WORD wPosition;
    WORD wProgramCount;

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    printf("=== DTV Programs #[%u] ===\n", wProgramCount);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        msAPI_CM_PrintProgram(E_SERVICETYPE_DTV, wPosition);
    }

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    printf("\n=== RADIO Programs #[%u] ===\n", wProgramCount);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        msAPI_CM_PrintProgram(E_SERVICETYPE_RADIO, wPosition);
    }

    printf("\n\n");
}

//****************************************************************************
/// Print Program
//****************************************************************************
void msAPI_CM_PrintProgram(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    WORD wOrder;
    WORD wProgramCount;
    BYTE cIDIndex;
    BYTE bChannelName[MAX_SERVICE_NAME];
    //BYTE i;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    if( wProgramCount <= wPosition )
    {
        return;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

    cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
    memset(bChannelName, 0x00, MAX_SERVICE_NAME);
    GetProgramTable(m_astDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)bChannelName, E_DATA_SERVICE_NAME);
    printf("[%4u]LCN %05u SID %05u Phy %02u SType %u Vis %u Sel %u Move %u Scr %u Mheg %u SidOnly %u HD %u Name: %s \n",
            wOrder,
            m_astDTVProgramIndexTable[wOrder].wLCN,
            m_astDTVProgramIndexTable[wOrder].wService_ID,
            _astDTVProgramIDTable[cIDIndex].cRFChannelNumber,
            (U8)m_astDTVProgramIndexTable[wOrder].bServiceType,
            (U8)m_astDTVProgramIndexTable[wOrder].bVisibleServiceFlag,
            (U8)m_astDTVProgramIndexTable[wOrder].bNumericSelectionFlag,
            (U8)m_astDTVProgramIndexTable[wOrder].bIsMove,
            (U8)m_astDTVProgramIndexTable[wOrder].bIsScramble,
            (U8)m_astDTVProgramIndexTable[wOrder].bIsMHEGIncluded,
            (U8)m_astDTVProgramIndexTable[wOrder].bIsServiceIdOnly,
            (U8)m_astDTVProgramIndexTable[wOrder].eVideoType,
            bChannelName
            );
#if 0 // refine log msg
    for(i = 0; i < MAX_SERVICE_NAME; i++)
    {
        GetProgramTable(m_astDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)bChannelName, E_DATA_SERVICE_NAME);

        if(bChannelName[i] == NULL)
        {
            break;
        }

        printf("%c",(BYTE)bChannelName[i]);
    }
    printf("\n");
#endif

}
#endif

//****************************************************************************
// Start of private implementation
//****************************************************************************

//****************************************************************************
/// Is Service Type Valid
/// @param bServiceType \b IN: Service Type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsServiceTypeValid(MEMBER_SERVICETYPE bServiceType)
{
    if( bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA)
    {
        return TRUE;
    }

    return FALSE;
}

//****************************************************************************
/// Is Position Valid
/// @param bServiceType \b IN: Service Type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: Position
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsPositionValid(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    if( bServiceType == E_SERVICETYPE_DTV || bServiceType == E_SERVICETYPE_RADIO || bServiceType == E_SERVICETYPE_DATA)
    {
        if( wPosition < msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL) )
        {
            return TRUE;
        }
    }

    return FALSE;
}

//****************************************************************************
/// Is Logical Channel Number Valid
/// @param wLCN \b IN: LCN (Logical Channel Number)
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsLogicalChannelNumberValid(WORD wLCN)
{
    // Dummy code for avoid compile warning
  #if 0
    wLCN = 0;
  #else  // Modified by coverity_0468
    UNUSED(wLCN);
  #endif

    return TRUE;
}

//****************************************************************************
/// Is Physical Channel Number Valid
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
static BOOLEAN IsPhysicalChannelNumberValid(U16 u16RFChannelNumber)
{
    // Dummy code for avoid compile warning
  #if 0
    cRFChannelNumber = 0;
  #else // Modified by coverity_0469
    UNUSED(u16RFChannelNumber);
  #endif

    return TRUE;
}

//****************************************************************************
/// Is Version Valid
/// @param cVersion \b IN: Version
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsVersionValid(BYTE cVersion)
{
    // Dummy code for avoid compile warning
    if((cVersion != DEFAULT_VERSION) && (cVersion > 31))
    {
        return FALSE;
    }

    return TRUE;
}

//****************************************************************************
/// Is TS_ID Valid
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
static BOOLEAN IsTS_IDValid(WORD wTransportStream_ID)
{
    // Dummy code for avoid compile warning
  #if 0
    wTransportStream_ID = 0;
  #else // Modified by coverity_0470
    UNUSED(wTransportStream_ID);
  #endif

    return TRUE;
}

//****************************************************************************
/// Is ON_ID Valid
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
static BOOLEAN IsON_IDValid(WORD wOriginalNetwork_ID)
{
    // Dummy code for avoid compile warning
  #if 0
    wOriginalNetwork_ID = 0;
  #else // Modified by coverity_0471
    UNUSED(wOriginalNetwork_ID);
  #endif

    return TRUE;
}

//****************************************************************************
/// Is Service ID Valid
/// @param Service_ID \b IN: Service ID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsService_IDValid(WORD Service_ID)
{
    // Dummy code for avoid compile warning
  #if 0
    Service_ID = 0;
  #else // Modified by coverity_0472
    UNUSED(Service_ID);
  #endif

    return TRUE;
}

//****************************************************************************
/// Is PMT PID Valid
/// @param wPMT_PID \b IN: PMT PID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsPMT_PIDValid(WORD wPMT_PID)
{
    if( ((0x0010 <= wPMT_PID) && (wPMT_PID <= 0x1FFF)) )
    {
        return TRUE;
    }

    return FALSE;
}

//****************************************************************************
/// Is PCR_PID Valid
/// @param wPCR_PID \b IN: PCR PID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsPCR_PIDValid(WORD wPCR_PID)
{
    if( (wPCR_PID <= 0x0001) || ((0x0010 <= wPCR_PID) && (wPCR_PID <= 0x1FFF)) )
    {
        return TRUE;
    }

    return FALSE;
}

//****************************************************************************
/// Is Video PID Valid
/// @param wVideo_PID \b IN: Video PID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsVideoPIDValid(WORD wVideo_PID)
{
    if( (wVideo_PID <= 0x000F) || (0x1FFF < wVideo_PID) )
    {
        return FALSE;
    }

    return TRUE;
}

//****************************************************************************
/// Is Audio Stream Info Valid
/// @param pastAudioStreamInfo \b IN: Audio Stream Info
/// - @see AUD_INFO
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsAudioStreamInfoValid(AUD_INFO * pastAudioStreamInfo)
{
    // Dummy code for avoid compile warning
    pastAudioStreamInfo = pastAudioStreamInfo;
    return TRUE;
}

//****************************************************************************
/// Is Audio PID Valid
/// @param wAudPID \b IN: Audio PID
/// @return BOOLEAN:
/// - 1: Default is valid
/// - 0: NO
//****************************************************************************
static BOOLEAN IsAudioPIDValid(WORD wAudPID)
{//@@-- Changed from 209GL, for some Audio invalid stream.

    if( wAudPID == INVALID_PID )
        return FALSE;

    return TRUE;
}

//****************************************************************************
/// Is Logical Channel Number Arranged
/// @return BOOLEAN:
/// - 1: Default is arranged
/// - 0: NO
//****************************************************************************
//static BOOLEAN IsLogicalChannelNumberArranged(void)
BOOLEAN IsLogicalChannelNumberArranged_DBSel(TypDtvDbSel eDtvDbSel)
{
    BOOLEAN bIsArranged = TRUE;

#if(ENABLE_API_DTV_SYSTEM_2015)
    U32 u32RamDiskAddr_LogicalChannelNumberArranged = msAPI_DtvDB_Get_RamDiskAddr_LogicalChannelNumberArranged(eDtvDbSel);
    GetNVRAM(u32RamDiskAddr_LogicalChannelNumberArranged, (BYTE *)&bIsArranged, sizeof(U8));

#else

    eDtvDbSel=eDtvDbSel;

  #if(ENABLE_S2)
    if(IsS2InUse())
        GetNVRAM(S2_BASEADDRESS_PR_IS_LCN_ARRANGED, (BYTE *)&bIsArranged, sizeof(bIsArranged));
    else
  #endif
        GetNVRAM(BASEADDRESS_PR_IS_LCN_ARRANGED, (BYTE *)&bIsArranged, sizeof(bIsArranged));
#endif

    if( bIsArranged == TRUE || bIsArranged == FALSE )
    {
        return bIsArranged;
    }

    return FALSE;
}

//****************************************************************************
/// This function will set Logical Channel Number is Arranged
/// @param bIsArranged \b IN: Is Arranged or not
//****************************************************************************
//static void LogicalChannelNumberIsArranged(BOOLEAN bIsArranged)
void LogicalChannelNumberIsArranged_DBSel(TypDtvDbSel eDtvDbSel, BOOLEAN bIsArranged)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    if( bIsArranged )
        bIsArranged = 1;

    U32 u32RamDiskAddr_LogicalChannelNumberArranged = msAPI_DtvDB_Get_RamDiskAddr_LogicalChannelNumberArranged(eDtvDbSel);
    SetNVRAM(u32RamDiskAddr_LogicalChannelNumberArranged, (U8*)&bIsArranged, sizeof(U8));

#else

    eDtvDbSel=eDtvDbSel;
    if( bIsArranged == TRUE || bIsArranged == FALSE )
    {
    #if(ENABLE_S2)
        if(IsS2InUse())
            SetNVRAM(S2_BASEADDRESS_PR_IS_LCN_ARRANGED, (BYTE *)&bIsArranged, sizeof(bIsArranged));
        else
    #endif
        SetNVRAM(BASEADDRESS_PR_IS_LCN_ARRANGED, (BYTE *)&bIsArranged, sizeof(bIsArranged));
    }
#endif
}

//****************************************************************************
/// Convert Position To Order
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wPosition \b IN: Position
/// @return WORD: order
//****************************************************************************
//static WORD ConvertPositionToOrder(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
WORD ConvertPositionToOrder_DBSel(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16ProgramTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel);


    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        WORD wOrder;
        //if( wPosition < MAX_DTVPROGRAM )
        if( wPosition < u16ProgramIndexTableArraySize )
        {
            //for(wOrder=0; wOrder < MAX_DTVPROGRAM; wOrder++)
            for(wOrder=0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
            {
                //if(FALSE == IsProgramEntityActive(m_astDTVProgramIndexTable[wOrder].wPRIndex))
                if(FALSE == IsProgramEntityActive_DBSel(eDtvDbSel,pstDTVProgramIndexTable[wOrder].wPRIndex))
                {
                    continue;
                }
                //if((WORD)bServiceType == m_astDTVProgramIndexTable[wOrder].bServiceType)
                if((WORD)bServiceType == pstDTVProgramIndexTable[wOrder].bServiceType)
                {
                    if(wPosition == 0) break;
                    wPosition--;
                }
            }
            //if(MAX_DTVPROGRAM == wOrder)
            if(u16ProgramIndexTableArraySize == wOrder)
            {
                printf("must not pass in wPosition IsProgramEntityActive FALSE ,wOrder= MAX_DTVPROGRAM");
            }
            return wOrder;
        }
        else
        {
            //return MAX_DTVPROGRAM-1;
            return u16ProgramIndexTableArraySize - 1;
        }
    }

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    WORD wStartOrderOfRadio = u16ProgramIndexTableArraySize - msAPI_DtvDB_Get_ProgramCount(eDtvDbSel, E_CM_SERVICE_POS_DATA, INCLUDE_ALL ) -1;
#else
    WORD wStartOrderOfRadio;
  #if ENABLE_S2
    if (IsS2InUse())
    {
        wStartOrderOfRadio = MAX_DTV_S2_PROGRAM-m_awS2ProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
    }
    else
  #endif
    {
    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())
        {
            wStartOrderOfRadio = MAX_DTVPROGRAM_DVBC-m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
        }
        else
    #endif
        wStartOrderOfRadio = MAX_DTVPROGRAM-m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
    }
#endif

#if 1//(ENABLE_API_DTV_SYSTEM_2015)

    if( bServiceType == E_SERVICETYPE_DTV )
    {
        //if( wPosition < MAX_DTVPROGRAM )
        if( wPosition < u16ProgramIndexTableArraySize )
        {
            return wPosition;
        }
        else
        {
            //return LAST_ORDER_OF_TV; //(MAX_DTVPROGRAM-1)
            PRINT_CURRENT_LINE();
            printf("\nWarning: %u: Invalid postion=%u\n", __LINE__, wPosition);
            return u16ProgramIndexTableArraySize - 1;
        }
    }
    else if( bServiceType == E_SERVICETYPE_RADIO )
    {
        if( wPosition < (wStartOrderOfRadio+1) )
        {
            return (wStartOrderOfRadio-wPosition);
        }
        else
        {
            PRINT_CURRENT_LINE();
            printf("\nWarning: %u: Invalid postion=%u\n", __LINE__, wPosition);
            return LAST_ORDER_OF_RADIO; // 0
        }
    }
    else // E_SERVICETYPE_DATA
    {
        //if( wPosition < MAX_DTVPROGRAM )
        if( wPosition < u16ProgramIndexTableArraySize )
        {
            return (u16ProgramIndexTableArraySize - wPosition - 1);
        }
        else
        {
            PRINT_CURRENT_LINE();
            printf("\nWarning: %u: Invalid postion=%u\n", __LINE__, wPosition);
            return LAST_ORDER_OF_DATA; // 0
        }
    }
#else
  #if(ENABLE_S2 )
    if(IsS2InUse())
    {
        if( bServiceType == E_SERVICETYPE_DTV )
        {
            if( wPosition < MAX_DTV_S2_PROGRAM )
            {
                return wPosition;
            }
            else
            {
                return S2_LAST_ORDER_OF_TV;
            }
        }
        else if( bServiceType == E_SERVICETYPE_RADIO )
        {
            if( wPosition < (wStartOrderOfRadio+1) )
            {
                return (wStartOrderOfRadio-wPosition);
            }
            else
            {
                return S2_LAST_ORDER_OF_RADIO;
            }
        }
        else
        {
            if( wPosition < MAX_DTV_S2_PROGRAM )
            {
                return (MAX_DTV_S2_PROGRAM - wPosition - 1);
            }
            else
            {
                return S2_LAST_ORDER_OF_DATA;
            }
        }
    }
    else
  #endif
    {
        if( bServiceType == E_SERVICETYPE_DTV )
        {
            if( wPosition < MAX_DTVPROGRAM )
            {
                return wPosition;
            }
            else
            {
                return LAST_ORDER_OF_TV;
            }
        }
        else if( bServiceType == E_SERVICETYPE_RADIO )
        {
            if( wPosition < (wStartOrderOfRadio+1) )
            {
                return (wStartOrderOfRadio-wPosition);
            }
            else
            {
                return LAST_ORDER_OF_RADIO; // 0
            }
        }
        else
        {
            if( wPosition < MAX_DTVPROGRAM )
            {
                return (MAX_DTVPROGRAM - wPosition - 1);
            }
            else
            {
                return LAST_ORDER_OF_DATA; // 0
            }
        }
    }
#endif
}

//****************************************************************************
/// Convert Order To Position
/// @param wOrder \b IN: Order
/// @return WORD: Position
//****************************************************************************
//static WORD ConvertOrderToPosition(WORD wOrder)
WORD ConvertOrderToPosition_DBSel(TypDtvDbSel eDtvDbSel, WORD wOrder)
{
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
        WORD wPosition,wOrder1;
        WORD wDTVProgramCount=0,wRadioProgramCount=0,wDataProgramCount=0;
        MEMBER_SERVICETYPE bNewServiceType;

        if( wOrder >= u16ProgramIndexTableArraySize )
        {
            return u16ProgramIndexTableArraySize - 1;
        }

        for(wOrder1=0; wOrder1 < wOrder; wOrder1++)
        {
            switch(pstDTVProgramIndexTable[wOrder1].bServiceType)
            {
                case (WORD)E_SERVICETYPE_DTV: wDTVProgramCount++;
                    break;
                case (WORD)E_SERVICETYPE_RADIO: wRadioProgramCount++;
                    break;
                case (WORD)E_SERVICETYPE_DATA: wDataProgramCount++;
                    break;
                default:
                    break;
            }
        }


        bNewServiceType = (MEMBER_SERVICETYPE)pstDTVProgramIndexTable[wOrder].bServiceType;

        wPosition = INVALID_PROGRAM_POSITION;

        switch(bNewServiceType)
        {
            case E_SERVICETYPE_DTV: wPosition = wDTVProgramCount;
                        break;
            case E_SERVICETYPE_RADIO: wPosition = wRadioProgramCount;
                        break;
            case E_SERVICETYPE_DATA: wPosition = wDataProgramCount;
                        break;
            default:
                        break;
        }

        return wPosition;
    }


    U8 bServiceType;
    WORD wStartOrderOfRadio = LAST_ORDER_OF_RADIO;

#if(ENABLE_API_DTV_SYSTEM_2015)
    bServiceType = pstDTVProgramIndexTable[wOrder].bServiceType;
    wStartOrderOfRadio = u16ProgramIndexTableArraySize
                    - msAPI_DtvDB_Get_ProgramCount(eDtvDbSel, E_CM_SERVICE_POS_DATA, INCLUDE_ALL)
                    - 1;

#else
  #if ENABLE_S2
    if (IsS2InUse())
    {
        bServiceType = m_astS2ProgramIndexTable[wOrder].bServiceType;
        wStartOrderOfRadio = MAX_DTV_S2_PROGRAM - m_awS2ProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
    }
    else
  #endif
    {
    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())
        {
            bServiceType = m_astDTVProgramIndexTable[wOrder].bServiceType;
            wStartOrderOfRadio = MAX_DTVPROGRAM_DVBC - m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
        }
        else
        {
            bServiceType = m_astDTVProgramIndexTable[wOrder].bServiceType;
            wStartOrderOfRadio = MAX_DTVPROGRAM - m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
        }
    #else
        bServiceType = m_astDTVProgramIndexTable[wOrder].bServiceType;
        wStartOrderOfRadio = MAX_DTVPROGRAM - m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
    #endif
    }
#endif


#if(ENABLE_API_DTV_SYSTEM_2015)
    if( E_SERVICETYPE_DTV == bServiceType )
    {
        //if( wOrder < MAX_DTVPROGRAM )
        if( wOrder < u16ProgramIndexTableArraySize )
        {
            return wOrder;
        }
        else
        {
            //return MAX_DTVPROGRAM - 1;
            return u16ProgramIndexTableArraySize - 1;
        }
    }
    else if( E_SERVICETYPE_RADIO == bServiceType )
    {
        if( wOrder < (wStartOrderOfRadio+1) )
        {
            return (wStartOrderOfRadio - wOrder);
        }
        else
        {
            return wStartOrderOfRadio;
        }
    }
    else if( E_SERVICETYPE_DATA == bServiceType )
    {
        //if( wOrder < MAX_DTVPROGRAM )
        if( wOrder < u16ProgramIndexTableArraySize )
        {
            //return (MAX_DTVPROGRAM - wOrder - 1);
            return (u16ProgramIndexTableArraySize - wOrder - 1);
        }
        else
        {
            //return MAX_DTVPROGRAM - 1;
            return u16ProgramIndexTableArraySize - 1;
        }
    }
    else
    {
        return INVALID_PROGRAM_POSITION;
    }

#else

  #if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( E_SERVICETYPE_DTV == bServiceType )
        {
            if( wOrder < MAX_DTV_S2_PROGRAM )
            {
                return wOrder;
            }
            else
            {
                return MAX_DTV_S2_PROGRAM - 1;
            }
        }
        else if( E_SERVICETYPE_RADIO == bServiceType )
        {
            if( wOrder < (wStartOrderOfRadio+1) )
            {
                return (wStartOrderOfRadio - wOrder);
            }
            else
            {
                return wStartOrderOfRadio;
            }
        }
        else
        {
            if( wOrder < MAX_DTV_S2_PROGRAM )
            {
                return (MAX_DTV_S2_PROGRAM - wOrder - 1);
            }
            else
            {
                return MAX_DTV_S2_PROGRAM - 1;
            }
        }
    }
    else
  #endif
    {
        if( E_SERVICETYPE_DTV == bServiceType )
        {
            if( wOrder < MAX_DTVPROGRAM )
            {
                return wOrder;
            }
            else
            {
                return MAX_DTVPROGRAM - 1;
            }
        }
        else if( E_SERVICETYPE_RADIO == bServiceType )
        {
            if( wOrder < (wStartOrderOfRadio+1) )
            {
                return (wStartOrderOfRadio - wOrder);
            }
            else
            {
                return wStartOrderOfRadio;
            }
        }
        else
        {
            if( wOrder < MAX_DTVPROGRAM )
            {
                return (MAX_DTVPROGRAM - wOrder - 1);
            }
            else
            {
                return MAX_DTVPROGRAM - 1;
            }
        }
    }
#endif
}

//****************************************************************************
/// Creat DTV Program Index Table And Program ID Table
/// @return BOOLEAN: Function execution result
//****************************************************************************
//static BOOLEAN CreatDTVProgramIndexTableAndProgramIDTable(void)
static BOOLEAN CreatDTVProgramIndexTableAndProgramIDTable(TypDtvDbSel eDtvDbSel)
{
    WORD wOrder;

    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());
    DEBUG_DTV_SYS(printf("CreatDTVProgramIndexTableAndProgramIDTable(eDtvDbSel=%u)\n", eDtvDbSel););

#if(ENABLE_API_DTV_SYSTEM_2015)
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    for(wOrder = 0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
    {
        FillProgramIndexWithDefault(&(pstProgramIndexTable[wOrder]));
    }
#else
    eDtvDbSel=eDtvDbSel;
    for(wOrder = 0; wOrder < MAX_DTVPROGRAM; wOrder++)
    {
        FillProgramIndexWithDefault(&m_astDTVProgramIndexTable[wOrder]);
    }
#endif

    if( TRUE == IsLogicalChannelNumberArranged_DBSel(eDtvDbSel) &&
        TRUE == IsLinkOfOrderValid(eDtvDbSel) )
    {
        FillDTVProgramIndexTableWithOrder(eDtvDbSel);
        UpdateProgramCount(E_SERVICETYPE_DTV);
        UpdateProgramCount(E_SERVICETYPE_DATA);
        UpdateProgramCount(E_SERVICETYPE_RADIO);
        UpdateIDInfo(eDtvDbSel);

    }
    else if( TRUE == IsLogicalChannelNumberArranged_DBSel(eDtvDbSel) )
    {
        FillDTVProgramIndexTableWithoutOrder(eDtvDbSel);
        UpdateProgramCount(E_SERVICETYPE_DTV);
        UpdateProgramCount(E_SERVICETYPE_DATA);
        UpdateProgramCount(E_SERVICETYPE_RADIO);
        UpdateIDInfo(eDtvDbSel);
        SortProgram(E_SERVICETYPE_DTV);
        SortProgram(E_SERVICETYPE_RADIO);
        SortProgram(E_SERVICETYPE_DATA);
        UpdateOrderOfProgramTable(E_SERVICETYPE_DTV);
        UpdateOrderOfProgramTable(E_SERVICETYPE_DATA);
        UpdateOrderOfProgramTable(E_SERVICETYPE_RADIO);
    }
    else
    {
        msAPI_CM_ArrangeDataManager(TRUE,FALSE);
    }

    return TRUE;
}

//****************************************************************************
/// Is Link Of Order Valid
/// @return BOOLEAN:
/// - 1: Default is Valid
/// - 0: NO
//****************************************************************************
BOOLEAN IsLinkOfOrderValid(TypDtvDbSel eDBSel)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    //BYTE cMapForCheckingDuplicationOfOrder[MAX_DTVCHANNELTABLE_MAP];
    WORD wPRIndex;
    WORD wOrder = 0;
    U16 u16ProgTabArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDBSel);
    //U8* pu8ProgTableMap = msAPI_DtvDB_Get_ProgTableMap(eDBSel);
    U16 u16ProgTabMapSize;
    U8* cMapForCheckingDuplicationOfOrder;
    BOOLEAN bRtn = TRUE;



    if( u16ProgTabArraySize > 6000 )
    {
        // The size is not make sence
        return FALSE;
    }

    u16ProgTabMapSize = (u16ProgTabArraySize/8) + 1;

    cMapForCheckingDuplicationOfOrder = msAPI_Memory_Allocate( u16ProgTabMapSize, BUF_ID_CHANNEL_MANAGER);
    if( cMapForCheckingDuplicationOfOrder == NULL )
    {
        printf("\nError: Alloc memory failed!\n");
        return FALSE;
    }

    for(wPRIndex=0; wPRIndex < (u16ProgTabMapSize); wPRIndex++)
    {
        cMapForCheckingDuplicationOfOrder[wPRIndex] = 0x00;
    }

    //for(wPRIndex=0; wPRIndex < MAX_DTVPROGRAM; wPRIndex++)
    for(wPRIndex=0; wPRIndex < u16ProgTabArraySize; wPRIndex++)
    {
        if( TRUE == IsProgramEntityActive_DBSel(eDBSel, wPRIndex) )
        {
            GetProgramTable(wPRIndex, (BYTE *)&wOrder, E_DATA_ORDER);

            //if( MAX_DTVPROGRAM <= wOrder )
            if( u16ProgTabArraySize <= wOrder )
            {
                printf("Not linked case: %u\n", wPRIndex);
                //return FALSE; // not linked case.
                bRtn = FALSE;
                break;
            }

            if( TRUE == (cMapForCheckingDuplicationOfOrder[wOrder/8] & (0x01 << (wOrder%8))) )
            {
                printf("Duplicated case: %u\n", wPRIndex);
                //return FALSE; // duplicated case.
                bRtn = FALSE;
                break;
            }
            else
            {
                cMapForCheckingDuplicationOfOrder[wOrder/8] |= (0x01 << (wOrder%8));
            }
        }
    }

    msAPI_Memory_Free( cMapForCheckingDuplicationOfOrder, BUF_ID_CHANNEL_MANAGER);

    return bRtn;

#else
    eDBSel=eDBSel;
    BYTE cMapForCheckingDuplicationOfOrder[MAX_DTVCHANNELTABLE_MAP];
    WORD wPRIndex;
    WORD wOrder=0;

    for(wPRIndex=0; wPRIndex < (MAX_DTVCHANNELTABLE_MAP); wPRIndex++)
    {
        cMapForCheckingDuplicationOfOrder[wPRIndex] = 0x00;
    }

    for(wPRIndex=0; wPRIndex < MAX_DTVPROGRAM; wPRIndex++)
    {
        if( TRUE == IsProgramEntityActive(wPRIndex) )
        {
            GetProgramTable(wPRIndex, (BYTE *)&wOrder, E_DATA_ORDER);

            if( MAX_DTVPROGRAM <= wOrder )
            {
//                printf("Not linked case: %u\n", wPRIndex);
                return FALSE; // not linked case.
            }

            if( TRUE == (cMapForCheckingDuplicationOfOrder[wOrder/8] & (0x01 << (wOrder%8))) )
            {
//                printf("Duplicated case: %u\n", wPRIndex);
                return FALSE; // duplicated case.
            }
            else
            {
                cMapForCheckingDuplicationOfOrder[wOrder/8] |= (0x01 << (wOrder%8));
            }
        }
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Fill DTV Program Index Table With Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN FillDTVProgramIndexTableWithOrder(TypDtvDbSel eDBSel)
{
    WORD wPRIndex = 0;
    WORD wOrder = 0;
    WORD wValue = 0;
    CHANNEL_ATTRIBUTE stCHAttribute;

#if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
    BYTE bFavType=0;
#endif

    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());

#if(ENABLE_API_DTV_SYSTEM_2015)
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDBSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDBSel);
#else
    U16 u16ProgramIndexTableArraySize = MAX_DTVPROGRAM;
    DTVPROGRAMINDEX* pstProgramIndexTable = m_astDTVProgramIndexTable;
  #if(ENABLE_S2)
    if( eDBSel == E_DTV_DB_SEL_DVBS )
    {
        u16ProgramIndexTableArraySize = MAX_DTV_S2_PROGRAM;
        pstProgramIndexTable = m_astS2ProgramIndexTable;
    }
  #endif
#endif

    memset(&stCHAttribute, 0, sizeof(CHANNEL_ATTRIBUTE));

    //for( wPRIndex=0; wPRIndex < MAX_DTVPROGRAM; wPRIndex++)
    for( wPRIndex=0; wPRIndex < u16ProgramIndexTableArraySize; wPRIndex++)
    {
        if( TRUE == IsProgramEntityActive_DBSel(eDBSel, wPRIndex) )
        {
        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&bFavType, E_DATA_ID_FAV);
        #endif
            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&wOrder, E_DATA_ORDER);

            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

            pstProgramIndexTable[wOrder].bServiceType = stCHAttribute.bServiceType;

        #if(ENABLE_S2_FAST_SCAN)
            pstProgramIndexTable[wOrder].bIsFastScan = stCHAttribute.bIsFastScan;
        #endif

            pstProgramIndexTable[wOrder].bVisibleServiceFlag = stCHAttribute.bVisibleServiceFlag;
            pstProgramIndexTable[wOrder].bIsDelete = stCHAttribute.bIsDelete;
            pstProgramIndexTable[wOrder].bIsReplaceDel = stCHAttribute.bIsReplaceDel;
        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            pstProgramIndexTable[wOrder].bIsFavorite = bFavType&0x0F;
        #else
            pstProgramIndexTable[wOrder].bIsFavorite = stCHAttribute.bIsFavorite;
        #endif
            pstProgramIndexTable[wOrder].bIsSkipped = stCHAttribute.bIsSkipped;
            pstProgramIndexTable[wOrder].bIsLock = stCHAttribute.bIsLock;
            pstProgramIndexTable[wOrder].bIsStillPicture = stCHAttribute.bIsStillPicture;
            pstProgramIndexTable[wOrder].bIsMove = stCHAttribute.bIsMove;
            pstProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;
            pstProgramIndexTable[wOrder].bUnconfirmedService = stCHAttribute.bUnconfirmedService;
            pstProgramIndexTable[wOrder].bInvalidService = stCHAttribute.bInvalidService;
            pstProgramIndexTable[wOrder].bNumericSelectionFlag = stCHAttribute.bNumericSelectionFlag;
            pstProgramIndexTable[wOrder].bIsSpecialService = stCHAttribute.bIsSpecialService;
            pstProgramIndexTable[wOrder].bServiceTypePrio = stCHAttribute.bServiceTypePrio;
            pstProgramIndexTable[wOrder].bIsScramble = stCHAttribute.bIsScramble;
            pstProgramIndexTable[wOrder].bReplaceService = stCHAttribute.bReplaceService;
            pstProgramIndexTable[wOrder].bIsServiceIdOnly = stCHAttribute.bIsServiceIdOnly;
            pstProgramIndexTable[wOrder].eVideoType = stCHAttribute.eVideoType;

#if (ASTRA_HD_ENABLE)
            pstProgramIndexTable[wOrder].bIsNewService = DEFAULT_IS_NEW_SERVICE;
#endif
         #if ENABLE_T_C_CHANNEL_MIX
            pstProgramIndexTable[wOrder].bIsTerrestrial = stCHAttribute.bIsTerrestrial;
         #endif

            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&wValue, E_DATA_LCN);
            pstProgramIndexTable[wOrder].wLCN = wValue;
            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&wValue, E_DATA_SIMU_LCN);
            pstProgramIndexTable[wOrder].wSimu_LCN = wValue;
            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&wValue, E_DATA_SERVICE_ID);
            pstProgramIndexTable[wOrder].wService_ID = wValue;
            GetProgramTable_DBSel(eDBSel, wPRIndex, (BYTE *)&wValue, E_DATA_ID_INDEX);
            pstProgramIndexTable[wOrder].cIDIndex = wValue;

            pstProgramIndexTable[wOrder].wPRIndex = wPRIndex;
        }
    }

    return TRUE;
}

//****************************************************************************
/// Fill DTV Program Index Table Without Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN FillDTVProgramIndexTableWithoutOrder(TypDtvDbSel eDtvDbSel)
{
    WORD wPRIndex;
    WORD wOrderOfTV;
    WORD wOrderOfRadio;
    WORD wOrderOfData;
    WORD wOrder,wIDs_1=INVALID_TS_ID;
    WORD wValue= 0;
    CHANNEL_ATTRIBUTE stCHAttribute;

    wOrderOfTV = FIRST_ORDER_OF_TV;
    wOrderOfRadio = FIRST_ORDER_OF_RADIO(eDtvDbSel);
    wOrderOfData = FIRST_ORDER_OF_DATA(eDtvDbSel);
    wOrder = 0;

    stCHAttribute.bServiceType = E_SERVICETYPE_INVALID;


    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    //for(wPRIndex=0; wPRIndex < MAX_DTVPROGRAM; wPRIndex++)
    for(wPRIndex=0; wPRIndex < u16ProgramIndexTableArraySize; wPRIndex++)
    {
        //if( TRUE == IsProgramEntityActive(wPRIndex) )
        if( TRUE == IsProgramEntityActive_DBSel(eDtvDbSel, wPRIndex) )
        {
            //GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
            GetProgramTable_DBSel(eDtvDbSel, wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

            if( stCHAttribute.bServiceType == E_SERVICETYPE_DATA )
            {
                wOrderOfRadio--;
            }
        }
    }

    //for(wPRIndex=0; wPRIndex < MAX_DTVPROGRAM; wPRIndex++)
    for(wPRIndex=0; wPRIndex < u16ProgramIndexTableArraySize; wPRIndex++)
    {
        //if( TRUE == IsProgramEntityActive(wPRIndex) )
        if( TRUE == IsProgramEntityActive_DBSel(eDtvDbSel, wPRIndex) )
        {
            //GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
            GetProgramTable_DBSel(eDtvDbSel, wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);

            if( stCHAttribute.bServiceType == E_SERVICETYPE_DTV )
            {
                wOrder = wOrderOfTV;
            }
            else if( stCHAttribute.bServiceType == E_SERVICETYPE_RADIO )
            {
                wOrder = wOrderOfRadio;
            }
            else if( stCHAttribute.bServiceType == E_SERVICETYPE_DATA )
            {
                wOrder = wOrderOfData;
            }
            else
            {
                ActiveProgramEntity_DBSel(eDtvDbSel, wPRIndex, FALSE);
                continue;
            }

            pstProgramIndexTable[wOrder].bServiceType = stCHAttribute.bServiceType;

        #if(ENABLE_S2_FAST_SCAN)
            pstProgramIndexTable[wOrder].bIsFastScan = stCHAttribute.bIsFastScan;
        #endif

            pstProgramIndexTable[wOrder].bVisibleServiceFlag = stCHAttribute.bVisibleServiceFlag;
            pstProgramIndexTable[wOrder].bIsDelete = stCHAttribute.bIsDelete;
            pstProgramIndexTable[wOrder].bIsReplaceDel = stCHAttribute.bIsReplaceDel;
            pstProgramIndexTable[wOrder].bIsFavorite = stCHAttribute.bIsFavorite;
            pstProgramIndexTable[wOrder].bIsSkipped = stCHAttribute.bIsSkipped;
            pstProgramIndexTable[wOrder].bIsLock = stCHAttribute.bIsLock;
            pstProgramIndexTable[wOrder].bIsStillPicture = stCHAttribute.bIsStillPicture;
            pstProgramIndexTable[wOrder].bIsMove = stCHAttribute.bIsMove;
            pstProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;
            pstProgramIndexTable[wOrder].bUnconfirmedService = stCHAttribute.bUnconfirmedService;
            pstProgramIndexTable[wOrder].bInvalidService = stCHAttribute.bInvalidService;
            pstProgramIndexTable[wOrder].bNumericSelectionFlag = stCHAttribute.bNumericSelectionFlag;
            pstProgramIndexTable[wOrder].bIsSpecialService = stCHAttribute.bIsSpecialService;
            pstProgramIndexTable[wOrder].bServiceTypePrio = stCHAttribute.bServiceTypePrio;
            pstProgramIndexTable[wOrder].bIsScramble = stCHAttribute.bIsScramble;
            pstProgramIndexTable[wOrder].bReplaceService = stCHAttribute.bReplaceService;
            pstProgramIndexTable[wOrder].bIsServiceIdOnly = stCHAttribute.bIsServiceIdOnly;
            pstProgramIndexTable[wOrder].eVideoType = stCHAttribute.eVideoType;
            #if ENABLE_T_C_CHANNEL_MIX
            pstProgramIndexTable[wOrder].bIsTerrestrial = stCHAttribute.bIsTerrestrial;
            #endif

            GetProgramTable(wPRIndex, (BYTE *)&wValue, E_DATA_LCN);
            pstProgramIndexTable[wOrder].wLCN = wValue;
            GetProgramTable(wPRIndex, (BYTE *)&wValue, E_DATA_SIMU_LCN);
            pstProgramIndexTable[wOrder].wSimu_LCN = wValue;
            GetProgramTable(wPRIndex, (BYTE *)&wValue, E_DATA_SERVICE_ID);
            pstProgramIndexTable[wOrder].wService_ID = wValue;
            GetProgramTable(wPRIndex, (BYTE *)&wValue, E_DATA_ID_INDEX);
            pstProgramIndexTable[wOrder].cIDIndex = wValue;

            pstProgramIndexTable[wOrder].wPRIndex = wPRIndex;

            if(_bOnlyUpdateCurTS)
            {
                GetIDTable(pstProgramIndexTable[wOrder].cIDIndex, (BYTE *)&wIDs_1, E_DATA_TS_ID);
                if(_wCurTS_ID == wIDs_1)
                {
                    pstProgramIndexTable[wOrder].eLCNAssignmentType = DEFAULT_LCN_ASSIGNMENT_TYPE;
                }
                else
                {
                    if( E_LCN_SAME_SERVICE & pstProgramIndexTable[wOrder].eLCNAssignmentType )
                    {
                       pstProgramIndexTable[wOrder].eLCNAssignmentType = DEFAULT_LCN_ASSIGNMENT_TYPE;
                       pstProgramIndexTable[wOrder].eLCNAssignmentType |= E_LCN_SAME_SERVICE;
                    }
                    else
                        pstProgramIndexTable[wOrder].eLCNAssignmentType = DEFAULT_LCN_ASSIGNMENT_TYPE;
                }
            }
            else
            {
                pstProgramIndexTable[wOrder].eLCNAssignmentType = DEFAULT_LCN_ASSIGNMENT_TYPE;
            }

            if( stCHAttribute.bServiceType == E_SERVICETYPE_DTV )
            {
                wOrderOfTV++;
            }
            else if( stCHAttribute.bServiceType == E_SERVICETYPE_DATA )
            {
                wOrderOfData--;
            }
            else
            {
                wOrderOfRadio--;
            }
        }
    }

    return TRUE;
}

//****************************************************************************
/// Fill DTV Program ID Table
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
#if 0
static BOOLEAN FillDTVProgramIDTable(MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    BYTE cIDIndex,cIDIndex_pre=0xFF;
    BOOLEAN result;

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    result = TRUE;

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        GetProgramTable(m_astDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&cIDIndex, E_DATA_ID_INDEX);
        m_astDTVProgramIndexTable[wOrder].cIDIndex = cIDIndex;

        if(cIDIndex_pre!=cIDIndex)
        {
            GetIDTable(cIDIndex,(BYTE *)&_astDTVProgramIDTable[cIDIndex],E_DATA_ID_TABLE);
            if(FALSE == ActiveIDEntity(cIDIndex,TRUE))
                __ASSERT(0);
            cIDIndex_pre = cIDIndex;
        }

        if( INVALID_IDINDEX == cIDIndex )
        {
            result = FALSE;
            break;
        }
    }

    return result;
}
#endif

//****************************************************************************
/// Add Program ID Table
/// @param pstDtvIDTable \b IN: point of DTVPROGRAMID
/// -@see DTVPROGRAMID
/// @param bSave \b IN: save or not save mux info
/// @return BYTE: MUX Index
//****************************************************************************
#define DEBUG_CM_ADD_IDTAB(x)   x
BOOLEAN msAPI_CM_AddProgramIDTable(DTVPROGRAMID *pstDtvIDTable, BOOLEAN bSave, U16 *pu16IDIndex)
{
    TypDtvDbSel eDtvDbSel = msAPI_DTV_Comm_Get_DBSel();

    DEBUG_CM_ADD_IDTAB( printf(" msAPI_CM_AddProgramIDTable(bSave=%u)\n", bSave); );
    DEBUG_CM_ADD_IDTAB( printf(" eDtvDbSel=%u\n", eDtvDbSel); );

    WORD wIDIndex;
    BYTE cNameLen;
    BYTE cNetworkIndex = 0;
    DTVPROGRAMID_M stDtvIDTable_M;

    DTVPROGRAMID_M *pProgramIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);

    DEBUG_CM_ADD_IDTAB( printf(" wNetwork_ID=%u\n", pstDtvIDTable->wNetwork_ID); );

    // Find if already exist this network_id
    for(cNetworkIndex=0; cNetworkIndex < u16NetWorkTableArraySize; cNetworkIndex++)
    {
        if(pstDtvIDTable->wNetwork_ID == pstNetworkTable[cNetworkIndex].wNetwork_ID)
        {
            DEBUG_CM_ADD_IDTAB( printf(" NetWork already exist idx=%u\n", cNetworkIndex); );
            break;
        }
    }

    // If need new a network
    if(cNetworkIndex >= u16NetWorkTableArraySize)//search free network
    {
        for(cNetworkIndex=0; cNetworkIndex < u16NetWorkTableArraySize; cNetworkIndex++)
        {
            if((pstNetworkTable[cNetworkIndex].wNetwork_ID == INVALID_NID))
            {
                DEBUG_CM_ADD_IDTAB( printf(" Use new NetWork idx=%u\n", cNetworkIndex); );
                break;
            }
        }
    }
    if(cNetworkIndex == u16NetWorkTableArraySize)
    {
        printf("\nError: over max support network (%d)\n", cNetworkIndex);
    }

    // Find ID table ...
    DEBUG_CM_ADD_IDTAB( printf(" Find ID table\n"); );
    for(wIDIndex=0; wIDIndex < u16IDTableArraySize; wIDIndex++)
    {
      #if(ENABLE_S2)
        if(IsS2InUse())
        {
            if( pstDtvIDTable->u8Polarity == pProgramIDTable[wIDIndex].u8Polarity
             && pstDtvIDTable->SatelliteId == pProgramIDTable[wIDIndex].SatelliteId
             && pstDtvIDTable->u32S2Frequency == pProgramIDTable[wIDIndex].u32S2Frequency
             && pstDtvIDTable->u16SymbolRate == pProgramIDTable[wIDIndex].u16SymbolRate
             && IsIDEntityActive_DBSel(eDtvDbSel, wIDIndex)
              )
            {
                #if(ASTRA_HD_ENABLE)
                if(!GetASTRA_HD_ENABLE()||(pstDtvIDTable->wTransportStream_ID == pProgramIDTable[wIDIndex].wTransportStream_ID))
                #endif
                {
                    if(cNetworkIndex != pProgramIDTable[wIDIndex].cNetWorkIndex)
                    {
                        pProgramIDTable[wIDIndex].cNetWorkIndex = cNetworkIndex;
                        if((cNetworkIndex < u16NetWorkTableArraySize)
                         &&(FALSE == SetIDTable(wIDIndex,(BYTE *)&cNetworkIndex,E_DATA_NETWORK_INDEX)))
                        {
                            __ASSERT(0);
                        }
                    }
                    DEBUG_CM_ADD_IDTAB( printf(" ID table found =%u\n", wIDIndex); );
                    break;
                }
            }
        }
        else
      #endif
        {
            BOOL bIDTabFound = FALSE;

            #if ENABLE_DVBC
            if( IsDVBCInUse() )
            {
                if((pstDtvIDTable->u32Frequency == pProgramIDTable[wIDIndex].u32Frequency)
                  ||IsFreqInsideOffsetRange(pstDtvIDTable->u32Frequency, pProgramIDTable[wIDIndex].u32Frequency)
                  )
                {
                    bIDTabFound = TRUE;
                    DEBUG_CM_ADD_IDTAB( printf(" ID table found =%u\n", wIDIndex); );
                }
            }
            else //DVBT
            #endif
            {
                if( pstDtvIDTable->cRFChannelNumber == pProgramIDTable[wIDIndex].cRFChannelNumber
                 && pstDtvIDTable->cPLPID == pProgramIDTable[wIDIndex].cPLPID
                 && pstDtvIDTable->cHpLp == pProgramIDTable[wIDIndex].cHpLp
                  )
                {
                    bIDTabFound = TRUE;
                    DEBUG_CM_ADD_IDTAB( printf(" ID table found =%u\n", wIDIndex); );
                }
            }

            if( bIDTabFound )
            {
                DEBUG_CM_ADD_IDTAB( printf(" ID tab found: wIDIndex=%u\n", wIDIndex); );

                //TS change case
                if(cNetworkIndex != pProgramIDTable[wIDIndex].cNetWorkIndex)
                {
                    if((pProgramIDTable[wIDIndex].cNetWorkIndex < u16NetWorkTableArraySize))
                    {
                        cNetworkIndex = pProgramIDTable[wIDIndex].cNetWorkIndex;
                        pstNetworkTable[cNetworkIndex].wNetwork_ID=pstDtvIDTable->wNetwork_ID;
                        if(FALSE == SetIDTable(cNetworkIndex,(BYTE *)&pstNetworkTable[cNetworkIndex],E_DATA_NETWORK))
                        {
                            __ASSERT(0);
                        }
                    }
                }

                #if ENABLE_DVBC
                if (pstDtvIDTable->u32Frequency != pProgramIDTable[wIDIndex].u32Frequency && IsDVBCInUse())
                {
                    pProgramIDTable[wIDIndex].u32Frequency = pstDtvIDTable->u32Frequency;
                    if (FALSE == SetIDTable(wIDIndex, (BYTE *)&pstDtvIDTable->u32Frequency, E_DATA_FREQ))
                    {
                        __ASSERT(0);
                    }
                }
                #endif

                //for manual scan in change TS case
                if(pstDtvIDTable->wTransportStream_ID != pProgramIDTable[wIDIndex].wTransportStream_ID)
                {
                    pProgramIDTable[wIDIndex].wTransportStream_ID= pstDtvIDTable->wTransportStream_ID;
                    if (FALSE == SetIDTable(wIDIndex, (BYTE *)&pstDtvIDTable->wTransportStream_ID, E_DATA_TS_ID))
                    {
                        __ASSERT(0);
                    }
                }
                if(pstDtvIDTable->wOriginalNetwork_ID != pProgramIDTable[wIDIndex].wOriginalNetwork_ID)
                {
                    pProgramIDTable[wIDIndex].wOriginalNetwork_ID= pstDtvIDTable->wOriginalNetwork_ID;
                    if (FALSE == SetIDTable(wIDIndex, (BYTE *)&pstDtvIDTable->wOriginalNetwork_ID, E_DATA_ON_ID))
                    {
                        __ASSERT(0);
                    }
                }
                break;
            }
        }
    }

    // If not found old ID Tab, then  new a ID tab
    if( wIDIndex >= u16IDTableArraySize )
    {
        DEBUG_CM_ADD_IDTAB( printf(" ID table not found\n"); );

        for(wIDIndex=0; wIDIndex < u16IDTableArraySize; wIDIndex++)
        {
            #if (ENABLE_S2)
            if(IsS2InUse())
            {
                if(FALSE == IsIDEntityActive_DBSel(eDtvDbSel, wIDIndex)) // Is not used
                {
                    stDtvIDTable_M.wTransportStream_ID= pstDtvIDTable->wTransportStream_ID;
                    stDtvIDTable_M.wOriginalNetwork_ID = pstDtvIDTable->wOriginalNetwork_ID;
                    stDtvIDTable_M.cRFChannelNumber = pstDtvIDTable->cRFChannelNumber;
                    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                    stDtvIDTable_M.cOriginal_RF = pstDtvIDTable->cOriginal_RF;
                    stDtvIDTable_M.dwAlternativeTime = pstDtvIDTable->dwAlternativeTime;
                    #endif
                    stDtvIDTable_M.wCellID = pstDtvIDTable->wCellID;
                    stDtvIDTable_M.cPLPID = pstDtvIDTable->cPLPID;
                    stDtvIDTable_M.cHpLp= pstDtvIDTable->cHpLp;
                    stDtvIDTable_M.cNetWorkIndex = cNetworkIndex;

                    stDtvIDTable_M.SatelliteId =pstDtvIDTable->SatelliteId;;
                    stDtvIDTable_M.u32S2Frequency=pstDtvIDTable->u32S2Frequency;;
                    stDtvIDTable_M.u16SymbolRate=pstDtvIDTable->u16SymbolRate;;
                    stDtvIDTable_M.u8Polarity=pstDtvIDTable->u8Polarity;

                    memcpy(&pProgramIDTable[wIDIndex],&stDtvIDTable_M,sizeof(DTVPROGRAMID_M));

                    if(bSave)
                    {
                        SetIDTable(wIDIndex,(BYTE *)&stDtvIDTable_M,E_DATA_ID_TABLE);
                        if(TRUE != ActiveIDEntity_DBSel(eDtvDbSel,wIDIndex,TRUE))
                        {
                            __ASSERT(0);
                        }
                    }
                    break;
                }
                else
                {
                    continue;
                }
            }
            else
            #endif
            {
                BOOL bEmptyIDFound = FALSE;
                #if ENABLE_DVBC
                if( IsDVBCInUse() )
                {
                    if( INVALID_FREQUENCY == pProgramIDTable[wIDIndex].u32Frequency )
                    {
                        bEmptyIDFound = TRUE;
                    }
                }
                else
                #endif
                {   // DVBT
                    if( INVALID_PHYSICAL_CHANNEL_NUMBER == pProgramIDTable[wIDIndex].cRFChannelNumber )
                    {
                        bEmptyIDFound = TRUE;
                    }
                }

            if( bEmptyIDFound )
            {
                stDtvIDTable_M.wTransportStream_ID = pstDtvIDTable->wTransportStream_ID;
                stDtvIDTable_M.wOriginalNetwork_ID = pstDtvIDTable->wOriginalNetwork_ID;

                #if(ENABLE_DVBC)
                if( IsDVBCInUse() )
                {
                    stDtvIDTable_M.cRFChannelNumber = wIDIndex;
                }
                else
                #endif
                {
                    stDtvIDTable_M.cRFChannelNumber = pstDtvIDTable->cRFChannelNumber;
                }

                #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
                stDtvIDTable_M.cOriginal_RF = pstDtvIDTable->cOriginal_RF;
                stDtvIDTable_M.dwAlternativeTime = pstDtvIDTable->dwAlternativeTime;
                #endif
                #if (ENABLE_SAVE_SQI)
                stDtvIDTable_M.wStrengthQuality = pstDtvIDTable->wStrengthQuality;
                #endif
                stDtvIDTable_M.wCellID = pstDtvIDTable->wCellID;
                stDtvIDTable_M.cPLPID = pstDtvIDTable->cPLPID;
                stDtvIDTable_M.cHpLp= pstDtvIDTable->cHpLp;
                stDtvIDTable_M.cNetWorkIndex = cNetworkIndex;

              #if 1//ENABLE_DVBC
                stDtvIDTable_M.u32Frequency = pstDtvIDTable->u32Frequency;
                //stDtvIDTable_M.u32SymbRate = pstDtvIDTable->u32SymbRate;
                stDtvIDTable_M.u16SymbolRate = pstDtvIDTable->u16SymbolRate;

                stDtvIDTable_M.QamMode = pstDtvIDTable->QamMode;
                stDtvIDTable_M.enBandWidth= pstDtvIDTable->enBandWidth;
              #endif

                //  [step 3/4]
                #if PATCH_FOR_HW_LIMIT_EXT_SYNC
                extern  BOOLEAN g_Ext_Sync;
                if(g_Ext_Sync == TRUE)
                    stDtvIDTable_M.Ext_Sync = 0 ;
                else
                    stDtvIDTable_M.Ext_Sync = 1 ;
                printf("save  g_Ext_Sync = %d",g_Ext_Sync);
                #endif
                // end

                memcpy(&pProgramIDTable[wIDIndex],&stDtvIDTable_M,sizeof(DTVPROGRAMID_M));

                if(bSave)
                {
                    if( FALSE == IsIDEntityActive_DBSel(eDtvDbSel, wIDIndex) )
                    {
                        SetIDTable(wIDIndex,(BYTE *)&stDtvIDTable_M,E_DATA_ID_TABLE);
                        if(TRUE != ActiveIDEntity_DBSel(eDtvDbSel, wIDIndex, TRUE))
                        {
                            __ASSERT(0);
                        }
                    }
                }
                break;
            }
            }
        }
    }

    if(wIDIndex < msAPI_CM_GetMuxMaxNumber())
    {
        if(cNetworkIndex < u16NetWorkTableArraySize)
        {
            pstNetworkTable[cNetworkIndex].wNetwork_ID =  pstDtvIDTable->wNetwork_ID;
            _msAPI_CM_GetCurrentNetworkName(pstNetworkTable[cNetworkIndex].bNetworkName, &cNameLen);
            if(FALSE == SetIDTable(cNetworkIndex,(BYTE *)&pstNetworkTable[cNetworkIndex],E_DATA_NETWORK))
            {
                __ASSERT(0);
            }
        }
        *pu16IDIndex = wIDIndex;

        return TRUE;
    }

    return FALSE;
}

//****************************************************************************
/// Update Order Of Program Table
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN UpdateOrderOfProgramTable(MEMBER_SERVICETYPE bServiceType)
{
    TypDtvDbSel eCurDtvDbSel = msAPI_DTV_Comm_Get_DBSel();

    WORD wPosition;
    WORD wOrder;
    WORD wSavedOrder=0;
    WORD wProgramCount;
    WORD wDeletedOrder;
    WORD i;

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = 0;


    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDtvDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);


#if (ENABLE_S2)
    if(IsS2InUse())
    {
        for(i=0; i < wProgramCount; i++)
        {
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);

            if( (bServiceType == pstProgramIndexTable[wOrder].bServiceType) &&
            (TRUE == IsProgramEntityActive(pstProgramIndexTable[wOrder].wPRIndex)) )
            {
                GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wSavedOrder, E_DATA_ORDER);
                if( wOrder != wSavedOrder )
                {
                    wSavedOrder = wOrder;
                    SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wSavedOrder, E_DATA_ORDER);
                }

                wPosition++;
            }
            else
            {
                wDeletedOrder = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
                MoveProgram(wOrder, wDeletedOrder);

                pstProgramIndexTable[wDeletedOrder].bServiceType = E_SERVICETYPE_INVALID;
                pstProgramIndexTable[wDeletedOrder].wPRIndex = INVALID_PRINDEX;

                ActiveProgramEntity_DBSel(eCurDtvDbSel, pstProgramIndexTable[wDeletedOrder].wPRIndex, FALSE);

                UpdateProgramCount(bServiceType);
                wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
            }
        }
    }
    else
#endif
    {
        for(i=0; i < wProgramCount; i++)
        {
            wOrder = ConvertPositionToOrder(bServiceType, wPosition);

            if( (bServiceType == pstProgramIndexTable[wOrder].bServiceType) &&
                (TRUE == IsProgramEntityActive(pstProgramIndexTable[wOrder].wPRIndex)) )
            {
                GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wSavedOrder, E_DATA_ORDER);
                if( wOrder != wSavedOrder )
                {
                    wSavedOrder = wOrder;
                    SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wSavedOrder, E_DATA_ORDER);
                }

                wPosition++;
            }
            else
            {
                wDeletedOrder = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
                MoveProgram(wOrder, wDeletedOrder);

                pstProgramIndexTable[wDeletedOrder].bServiceType = E_SERVICETYPE_INVALID;
                pstProgramIndexTable[wDeletedOrder].wPRIndex = INVALID_PRINDEX;

                ActiveProgramEntity_DBSel(eCurDtvDbSel, pstProgramIndexTable[wDeletedOrder].wPRIndex, FALSE);

                UpdateProgramCount(bServiceType);
                wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
            }
        }
    }

    return TRUE;
}

#if ENABLE_SBTVD_CM_APP
static BOOLEAN SortProgram_Brazil(MEMBER_SERVICETYPE bServiceType)
{
    WORD wOrder1,wOrder2;
    WORD wMinLCN, wCurrentLCN;
    WORD wMinOrder;
    WORD wProgramCount;
    WORD wPosition1, wPosition2;
    WORD i;

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);

    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    // sort LCN from Min to Max
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
            continue;

        if( TRUE == pstProgramIndexTable[wOrder1].bIsMove )
        {
            continue;
        }

        wMinOrder = wOrder1;
        //bMinRF = _astDTVProgramIDTable[m_astDTVProgramIndexTable[wOrder1].cIDIndex].cRFChannelNumber;
        wMinLCN = ((pstProgramIndexTable[wOrder1].stLCN.bPhysicalChannel << 8) | pstProgramIndexTable[wOrder1].stLCN.bVirtualChannel);

        for(wPosition2=wPosition1+1; wPosition2 < wProgramCount; wPosition2++)
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
            //bCurrentRF = _astDTVProgramIDTable[m_astDTVProgramIndexTable[wOrder2].cIDIndex].cRFChannelNumber;
            wCurrentLCN = ((pstProgramIndexTable[wOrder2].stLCN.bPhysicalChannel << 8) | pstProgramIndexTable[wOrder2].stLCN.bVirtualChannel);

            if( (INVALID_LOGICAL_CHANNEL_NUMBER == wCurrentLCN) ||
                (TRUE == pstProgramIndexTable[wOrder2].bIsMove)||
                (FALSE == pstProgramIndexTable[wOrder2].bVisibleServiceFlag)||
                (TRUE == pstProgramIndexTable[wOrder2].bIsDelete))
            {
                continue;
            }

            if(wMinLCN > wCurrentLCN)
            {
                wMinLCN =  wCurrentLCN;
                wMinOrder =  wOrder2;
            }
        }

        if( wMinOrder != wOrder1 )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            SwapProgram(wMinOrder, wOrder1);
        }
    }

    // Move Invisible to last
    wPosition1 = 0;
    for(i=0; i < wProgramCount; i++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
            continue;

        if( FALSE == pstProgramIndexTable[wOrder1].bVisibleServiceFlag )
        {
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
            if( wOrder2 >= u16ProgramIndexTableArraySize )
                continue;

            MoveProgram(wOrder1, wOrder2);
        }
        else
        {
            wPosition1++;
        }
    }

    // Move Deleted to last
    wPosition1 = 0;
    for(i=0; i < wProgramCount; i++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
            continue;

        if( TRUE == pstProgramIndexTable[wOrder1].bIsDelete )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
            if( wOrder2 >= u16ProgramIndexTableArraySize )
                continue;

            MoveProgram(wOrder1, wOrder2);
        }
        else
        {
            wPosition1++;
        }
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED);
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
            continue;

        if( INVALID_LOGICAL_CHANNEL_NUMBER != pstProgramIndexTable[wOrder1].wLCN )
        {
            continue;
        }

        if( TRUE == pstProgramIndexTable[wOrder1].bIsMove )
        {
            continue;
        }

        wMinOrder = wOrder1;

        for(wPosition2=wPosition1+1; wPosition2 < wProgramCount; wPosition2++)
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
            if( wOrder2 >= u16ProgramIndexTableArraySize )
                continue;

            if( TRUE == pstProgramIndexTable[wOrder2].bIsMove )
                continue;

            if( pstProgramIndexTable[wOrder1].cIDIndex != pstProgramIndexTable[wOrder2].cIDIndex )
            {
                if( pMuxTable[pstProgramIndexTable[wOrder2].cIDIndex].cRFChannelNumber <
                    pMuxTable[pstProgramIndexTable[wOrder1].cIDIndex].cRFChannelNumber )
                {
                    wMinOrder = wOrder2;
                }
            }
        }

        if( wMinOrder != wOrder1 )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            SwapProgram(wMinOrder, wOrder1);
        }
    }

    return TRUE;
}
#endif

#if ENABLE_DTV_STORE_TTX_PAGE_INFO
//------------------------------------------------------------------------------
/// -This function will Get List Page Number
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8ListIndex \b IN: List Index
/// @return WORD: List page number
//------------------------------------------------------------------------------
static WORD GetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex)
{
    WORD u16ListPageNumber;
    WORD u16Temp;

    switch ( u8ListIndex )
    {
    case 0:
        u16Temp = (WORD)pu8Buffer[0];
        u16Temp = u16Temp & 0x00FF;
        u16ListPageNumber = u16Temp;

        u16Temp = (WORD)pu8Buffer[1];
        u16Temp = u16Temp & 0x0003;
        u16ListPageNumber |= (u16Temp << 8);
        break;

    case 1:
        u16Temp = (WORD)pu8Buffer[1];
        u16Temp = u16Temp & 0x00FC;
        u16ListPageNumber = u16Temp >> 2;

        u16Temp = (WORD)pu8Buffer[2];
        u16Temp = u16Temp & 0x000F;
        u16ListPageNumber |= (u16Temp << 6);
        break;

    case 2:
        u16Temp = (WORD)pu8Buffer[2];
        u16Temp = u16Temp & 0x00F0;
        u16ListPageNumber = u16Temp >> 4;

        u16Temp = (WORD)pu8Buffer[3];
        u16Temp = u16Temp & 0x003F;
        u16ListPageNumber |= (u16Temp << 4);
        break;

    case 3:
        u16Temp = (WORD)pu8Buffer[3];
        u16Temp = u16Temp & 0x00C0;
        u16ListPageNumber = u16Temp >> 6;

        u16Temp = (WORD)pu8Buffer[4];
        u16Temp = u16Temp & 0x00FF;
        u16ListPageNumber |= (u16Temp << 2);
        break;

    default:
        u16ListPageNumber = DEFAULT_LISTPAGE[0];
        break;
    }

    u16ListPageNumber &= 0x03FF;

    return u16ListPageNumber;
}

//------------------------------------------------------------------------------
/// -This function will Set List Page Number
/// @param pu8Buffer \b IN: pointer to Buffer
/// @param u8ListIndex \b IN: List Index
/// @param u16ListPageNumber \b IN: List Page Number
//------------------------------------------------------------------------------
static void SetListPageNumber(BYTE *pu8Buffer, BYTE u8ListIndex, WORD u16ListPageNumber)
{
    u16ListPageNumber &= 0x03FF;

    switch ( u8ListIndex )
    {
    case 0:
        pu8Buffer[0] &= 0x0000;
        pu8Buffer[0] |= (u16ListPageNumber & 0x00FF);

        pu8Buffer[1] &= 0x00FC;
        pu8Buffer[1] |= ((u16ListPageNumber & 0x0300) >> 8);
        break;

    case 1:
        pu8Buffer[1] &= 0x0003;
        pu8Buffer[1] |= ((u16ListPageNumber & 0x003F) << 2);

        pu8Buffer[2] &= 0x00F0;
        pu8Buffer[2] |= ((u16ListPageNumber & 0x03C0) >> 6);
        break;

    case 2:
        pu8Buffer[2] &= 0x000F;
        pu8Buffer[2] |= ((u16ListPageNumber & 0x000F) << 4);

        pu8Buffer[3] &= 0x00C0;
        pu8Buffer[3] |= ((u16ListPageNumber & 0x03F0) >> 4);
        break;

    case 3:
        pu8Buffer[3] &= 0x003F;
        pu8Buffer[3] |= ((u16ListPageNumber & 0x0003) << 6);

        pu8Buffer[4] &= 0x0000;
        pu8Buffer[4] |= ((u16ListPageNumber & 0x03FC) >> 2);
        break;
    }
}
#endif

#if (PRG_EDIT_INPUT_LCN_MOVE == 1)
#if 0
static FUNCTION_RESULT ChangeLCN(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wLCN)
{
    WORD wProgramCount;
    WORD wPosition1, wPosition2;
    WORD wOrder, wOrder1, wOrder2;
    WORD wTempLCN;

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);

        if( wLCN == m_astDTVProgramIndexTable[wOrder1].wLCN )
        {
            wTempLCN = wLCN;

            if (wPosition > wPosition1)
            {
                for (wPosition2=wPosition1; wPosition2 < wPosition; wPosition2++)
                {
                    wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

                    if ( wTempLCN == m_astDTVProgramIndexTable[wOrder2].wLCN )
                    {
                        m_astDTVProgramIndexTable[wOrder2].wLCN = (++wTempLCN);
                        SetProgramTable(m_astDTVProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(wTempLCN), E_DATA_LCN);
                    }
                    else
                    {
                        break;
                    }
                }

            }
            else
            {
                for (wPosition2=wPosition1; wPosition2 < wProgramCount ; wPosition2++)
                {
                    wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

                    if ( wTempLCN == m_astDTVProgramIndexTable[wOrder2].wLCN )
                    {
                        if (wTempLCN < 999)
                        {
                            m_astDTVProgramIndexTable[wOrder2].wLCN = (++wTempLCN);
                            SetProgramTable(m_astDTVProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(wTempLCN), E_DATA_LCN);
                        }
                        else
                        {
                            wTempLCN = 1;

                            if (999 == m_astDTVProgramIndexTable[wOrder2].wLCN )
                            {
                                m_astDTVProgramIndexTable[wOrder2].wLCN = wTempLCN;
                                SetProgramTable(m_astDTVProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(wTempLCN), E_DATA_LCN);
                            }

                            for (wPosition2=0; wPosition2 < wPosition ; wPosition2++)
                            {
                                wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);
                                if ( wTempLCN == m_astDTVProgramIndexTable[wOrder2].wLCN )
                                {
                                    m_astDTVProgramIndexTable[wOrder2].wLCN = (++wTempLCN) ;
                                    SetProgramTable(m_astDTVProgramIndexTable[wOrder2].wPRIndex, (BYTE *)&(wTempLCN), E_DATA_LCN);
                                }
                                else
                                {
                                    break;
                                }
                            }

                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

            }
            break;
        }
    }

    m_astDTVProgramIndexTable[wOrder].wLCN = wLCN;
    m_astDTVProgramIndexTable[wOrder].eLCNAssignmentType = E_LCN_PRESENT;
    SetProgramTable(m_astDTVProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wLCN), E_DATA_LCN);

    return E_RESULT_SUCCESS;
}

#else
static FUNCTION_RESULT SwapLCN(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wLCN)
{
    WORD wProgramCount;
    WORD wPosition1;
    WORD wOrder, wOrder1;
    WORD wTempLCN;

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return E_RESULT_FAILURE;

    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
            continue;

        if( wLCN == pstProgramIndexTable[wOrder1].wLCN )
        {
            wTempLCN = pstProgramIndexTable[wOrder].wLCN;
            pstProgramIndexTable[wOrder1].wLCN = wTempLCN;
            SetProgramTable(pstProgramIndexTable[wOrder1].wPRIndex, (BYTE *)&(wTempLCN), E_DATA_LCN);
            break;
        }
    }

    pstProgramIndexTable[wOrder].wLCN = wLCN;
    pstProgramIndexTable[wOrder].eLCNAssignmentType = E_LCN_PRESENT;

    SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&(wLCN), E_DATA_LCN);

    return E_RESULT_SUCCESS;
}
#endif
#endif

#if (NTV_FUNCTION_ENABLE)
static BOOLEAN SortProgramByRegionPriority(MEMBER_SERVICETYPE bServiceType)
{
    WORD wOrder1,wOrder2;
    WORD wProgramCount;
    WORD wPosition1,wPositionEnd;
    WORD i;
    U16 u16IDIndex;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
#if 0
    printf("###########################################\n");
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        printf("SID %u, LCN %u, Special %bu, cNetWorkIndex %bu\n",m_astDTVProgramIndexTable[wOrder1].wService_ID, m_astDTVProgramIndexTable[wOrder1].wLCN,
            m_astDTVProgramIndexTable[wOrder1].bIsSpecialService,_astDTVProgramIDTable[m_astDTVProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex);
    }
    printf("\n\n\n");
#endif
    //[3]Sort Service LCN 900-999 with ONID_NORWAY Order placed at the end of list
    wPositionEnd = wProgramCount;
    wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
    if( wOrder2 >= u16ProgramIndexTableArraySize )
    {
        return FALSE;
    }

    for(wPosition1 = 0; wPosition1 < wPositionEnd; )
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
        {
            wPosition1++;
            continue;
        }

        u16IDIndex = pstProgramIndexTable[wOrder1].cIDIndex;
        if(u16IDIndex >= u16IDTableArraySize)
            continue;

        if(pMuxTable[u16IDIndex].wOriginalNetwork_ID != SI_ONID_NORWAY)
        {
            break;
        }
        if(pstProgramIndexTable[wOrder1].bIsSpecialService == FALSE)
        {
            wPosition1++;
            continue;
        }
        if( TRUE == pstProgramIndexTable[wOrder1].bIsMove )
        {
            wPosition1++;
            continue;
        }

        MoveProgram(wOrder1, wOrder2);
        wPositionEnd--;

    }
#if 0
    printf("###########################################\n");
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        printf("SID %u, LCN %u, Special %bu, cNetWorkIndex %bu\n",m_astDTVProgramIndexTable[wOrder1].wService_ID, m_astDTVProgramIndexTable[wOrder1].wLCN,
            m_astDTVProgramIndexTable[wOrder1].bIsSpecialService,_astDTVProgramIDTable[m_astDTVProgramIndexTable[wOrder1].cIDIndex].cNetWorkIndex);
    }
    printf("\n\n\n");
#endif
    wPosition1 = 0;
    for(i=0; i < wProgramCount; i++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
        {
            wPosition1++;
            continue;
        }

        if( FALSE == pstProgramIndexTable[wOrder1].bVisibleServiceFlag )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
            MoveProgram(wOrder1, wOrder2);
        }
        else
        {
            wPosition1++;
        }
    }

    wPosition1 = 0;
    for(i=0; i < wProgramCount; i++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
        {
            wPosition1++;
            continue;
        }

        if( TRUE == pstProgramIndexTable[wOrder1].bIsDelete )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
            MoveProgram(wOrder1, wOrder2);
        }
        else
        {
            wPosition1++;
        }
    }

    UpdateOrderOfProgramTable(bServiceType);
    return TRUE;
}
#endif

static BOOLEAN  SortProgramforLCNSorting(void)
{
    WORD wOrder1,wOrder2;
    WORD wMinLCN, wCurrentLCN;
    WORD wMinOrder;
    WORD wMaxDTVProgramCount;

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    wMaxDTVProgramCount = u16ProgramIndexTableArraySize;


    for(wOrder1=0; wOrder1 < u16ProgramIndexTableArraySize; wOrder1++)
    {
        if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder1].wPRIndex))
        {
            continue;
        }

        wMinOrder = wOrder1;
        wMinLCN = pstProgramIndexTable[wOrder1].wLCN;

        for(wOrder2=wOrder1+1; wOrder2 < u16ProgramIndexTableArraySize; wOrder2++)
        {
            wCurrentLCN = pstProgramIndexTable[wOrder2].wLCN;

            if( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder2].wLCN )
            {
                continue;
            }
            if(FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrder2].wPRIndex))
            {
                continue;
            }

            if( wMinLCN > wCurrentLCN )
            {
                wMinLCN = wCurrentLCN;
                wMinOrder = wOrder2;
            }
        }

        if( wMinOrder != wOrder1 )
        {
            SwapProgram(wMinOrder, wOrder1);// swap the data in array, so LCN and order sort from lowest to high
        }
    }

    // Move Invisible to lasts
    for(wOrder1=0; wOrder1< wMaxDTVProgramCount; wOrder1++)
    {
        if( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder1].wLCN )
        {
            continue;
        }

        if( FALSE == pstProgramIndexTable[wOrder1].bVisibleServiceFlag )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif
            MoveProgram(wOrder1, wMaxDTVProgramCount-1);
            wOrder1 = wOrder1 - 1;
            wMaxDTVProgramCount = wMaxDTVProgramCount - 1;
        }
    }

    // Move Deleted to last
    for(wOrder1=0; wOrder1< wMaxDTVProgramCount; wOrder1++)
    {
        if( INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder1].wLCN )
        {
            continue;
        }

        if( TRUE == pstProgramIndexTable[wOrder1].bIsDelete )
        {
        #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
        #endif
            MoveProgram(wOrder1, wMaxDTVProgramCount-1);
            wOrder1 = wOrder1 - 1;
            wMaxDTVProgramCount = wMaxDTVProgramCount - 1;
        }
    }

    return TRUE;
}

BOOLEAN SortProgram(MEMBER_SERVICETYPE bServiceType)
{
    WORD wOrder1,wOrder2;
    WORD wMinLCN, wCurrentLCN;
    WORD wMinOrder;
    WORD wProgramCount;
    WORD wPosition1, wPosition2;
    WORD i;

    //PRINT_CURRENT_LINE();
    TypDtvDbSel eCurDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDtvDbSel);
    DTVPROGRAMINDEX* pProgramInfo = msAPI_DtvDB_Get_ProgramIndexTable(eCurDtvDbSel);


    // Sort prog by LCN
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);

    #if (PRG_EDIT_INPUT_LCN_MOVE == 0)
        if( TRUE == pProgramInfo[wOrder1].bIsMove )
        {
            continue;
        }
    #endif

        wMinOrder = wOrder1;

        wMinLCN = pProgramInfo[wOrder1].wLCN;

        for(wPosition2=wPosition1+1; wPosition2 < wProgramCount; wPosition2++)
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

            wCurrentLCN = pProgramInfo[wOrder2].wLCN;

            if( INVALID_LOGICAL_CHANNEL_NUMBER == pProgramInfo[wOrder2].wLCN )
            {
                continue;
            }

        #if (PRG_EDIT_INPUT_LCN_MOVE == 0)
            if( TRUE == pProgramInfo[wOrder2].bIsMove )
            {
                continue;
            }
        #endif

            if( FALSE == pProgramInfo[wOrder2].bVisibleServiceFlag )
            {
                continue;
            }

            if( TRUE == pProgramInfo[wOrder2].bIsDelete )
            {
                continue;
            }

            if( wMinLCN > wCurrentLCN )
            {
                wMinLCN = wCurrentLCN;
                wMinOrder = wOrder2;
            }
        }

        if( wMinOrder != wOrder1 )
        {
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            SwapProgram(wMinOrder, wOrder1);
        }
    }

    // Move invisible prog to the end of list
    wPosition1 = 0;
    for(i=0; i < wProgramCount; i++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( FALSE == pProgramInfo[wOrder1].bVisibleServiceFlag )
        {
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
            MoveProgram(wOrder1, wOrder2);
        }
        else
        {
            wPosition1++;
        }
    }

    // Move deleted prog to the end of list
    wPosition1 = 0;
    for(i=0; i < wProgramCount; i++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);
        if( TRUE == pProgramInfo[wOrder1].bIsDelete )
        {
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            wOrder2 = ConvertPositionToOrder(bServiceType, (wProgramCount-1));
            MoveProgram(wOrder1, wOrder2);
        }
        else
        {
            wPosition1++;
        }
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED);
    for(wPosition1=0; wPosition1 < wProgramCount; wPosition1++)
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition1);

        if( INVALID_LOGICAL_CHANNEL_NUMBER != pProgramInfo[wOrder1].wLCN )
        {
            continue;
        }

    #if (PRG_EDIT_INPUT_LCN_MOVE == 0)
        if( TRUE == pProgramInfo[wOrder1].bIsMove )
        {
            continue;
        }
    #endif

        wMinOrder = wOrder1;

        for(wPosition2=wPosition1+1; wPosition2 < wProgramCount; wPosition2++)
        {
            wOrder2 = ConvertPositionToOrder(bServiceType, wPosition2);

        #if (PRG_EDIT_INPUT_LCN_MOVE == 0)
            if( TRUE == pProgramInfo[wOrder2].bIsMove )
                continue;
        #endif


            if( pProgramInfo[wOrder1].cIDIndex != pProgramInfo[wOrder2].cIDIndex )
            {
            #if ENABLE_S2
                if (IsS2InUse())
                {
                    if( _astS2ProgramIDTable[pProgramInfo[wOrder2].cIDIndex].cRFChannelNumber <
                        _astS2ProgramIDTable[pProgramInfo[wOrder1].cIDIndex].cRFChannelNumber )
                    {
                        wMinOrder = wOrder2;
                    }
                }
                else
            #endif

            #if(ENABLE_DVBC)
                if( IsDVBCInUse() )
                {
                    if( pMuxTable[pProgramInfo[wOrder2].cIDIndex].u32Frequency <
                        pMuxTable[pProgramInfo[wOrder1].cIDIndex].u32Frequency )
                    {
                        wMinOrder = wOrder2;
                    }
                }
                else
            #endif
                {   // DVBT
                    if( pMuxTable[pProgramInfo[wOrder2].cIDIndex].cRFChannelNumber <
                        pMuxTable[pProgramInfo[wOrder1].cIDIndex].cRFChannelNumber )
                    {
                        wMinOrder = wOrder2;
                    }
                }
            }
        }

        if( wMinOrder != wOrder1 )
        {
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            SwapProgram(wMinOrder, wOrder1);
        }
    }

    UpdateOrderOfProgramTable(bServiceType);

    return TRUE;
}

//****************************************************************************
/// Move Program
/// @param wFromOrder \b IN: From Order
/// @param wToOrder \b IN: To Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN MoveProgram(WORD wFromOrder, WORD wToOrder)
{
    DTVPROGRAMINDEX stDTVProgramIndex;
    WORD wOrder,wOriinalLCN,wPRIndex;

    if(wFromOrder == wToOrder)
    {
        return TRUE;
    }

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

    wPRIndex    = 0;
    wOriinalLCN = 0;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if(wFromOrder > wToOrder)
        {
            stDTVProgramIndex = pstProgramIndexTable[wFromOrder];
            for(wOrder=wFromOrder; wOrder > wToOrder; wOrder--)
            {
                pstProgramIndexTable[wOrder] = pstProgramIndexTable[wOrder-1];
                            wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
                            GetProgramTable(wPRIndex, (BYTE *)&wOriinalLCN, E_DATA_TS_LCN);
                            if ((pstProgramIndexTable[wOrder].wLCN > 1) &&
                                (pstProgramIndexTable[wOrder].wLCN < INVALID_LCN_MAX_NUMBER)&&
                                (wOriinalLCN > INVALID_LCN_MAX_NUMBER))
                                {
                                    pstProgramIndexTable[wOrder].wLCN = pstProgramIndexTable[wOrder].wLCN-1;
                                }
            }
            pstProgramIndexTable[wToOrder] = stDTVProgramIndex;
        }
        else
        {
            stDTVProgramIndex = pstProgramIndexTable[wFromOrder];
            for(wOrder=wFromOrder; wOrder < wToOrder; wOrder++)
            {
                pstProgramIndexTable[wOrder] = pstProgramIndexTable[wOrder+1];
                            wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
                            GetProgramTable(wPRIndex, (BYTE *)&wOriinalLCN, E_DATA_TS_LCN);
                            if ((pstProgramIndexTable[wOrder].wLCN > 1) &&
                                (pstProgramIndexTable[wOrder].wLCN < INVALID_LCN_MAX_NUMBER)&&
                                (wOriinalLCN > INVALID_LCN_MAX_NUMBER))
                                {
                                    pstProgramIndexTable[wOrder].wLCN = pstProgramIndexTable[wOrder].wLCN-1;
                                }
            }
            pstProgramIndexTable[wToOrder] = stDTVProgramIndex;
        }
    }
    else
#endif
    {
        if(wFromOrder > wToOrder)
        {
            stDTVProgramIndex = pstProgramIndexTable[wFromOrder];
            for(wOrder=wFromOrder; wOrder > wToOrder; wOrder--)
            {
                pstProgramIndexTable[wOrder] = pstProgramIndexTable[wOrder-1];
            }
            pstProgramIndexTable[wToOrder] = stDTVProgramIndex;
        }
        else
        {
            stDTVProgramIndex = pstProgramIndexTable[wFromOrder];

            for(wOrder=wFromOrder; wOrder < wToOrder; wOrder++)
            {
                pstProgramIndexTable[wOrder] = pstProgramIndexTable[wOrder+1];
            }
            pstProgramIndexTable[wToOrder] = stDTVProgramIndex;
        }
    }

#if (ENABLE_DTV_EPG)
    if(_pfNotify_CM_MoveProgram)
    {
        _pfNotify_CM_MoveProgram(wFromOrder, wToOrder);
    }
#endif  //#if (ENABLE_EPG)

    return TRUE;
}

//****************************************************************************
/// Swap Program
/// @param wFromOrder \b IN: From Order
/// @param wToOrder \b IN: To Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN SwapProgram(WORD wFromOrder, WORD wToOrder)
{
    DTVPROGRAMINDEX stDTVProgramIndex;

    if( wFromOrder == wToOrder )
    {
        return TRUE;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    if( wFromOrder >= u16ProgramIndexTableArraySize )
        return FALSE;
    if( wToOrder >= u16ProgramIndexTableArraySize )
        return FALSE;


#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        stDTVProgramIndex = m_astS2ProgramIndexTable[wFromOrder];
        m_astS2ProgramIndexTable[wFromOrder] = m_astS2ProgramIndexTable[wToOrder];
        m_astS2ProgramIndexTable[wToOrder] = stDTVProgramIndex;
    }
    else
#endif
    {
        stDTVProgramIndex = pstProgramIndexTable[wFromOrder];
        pstProgramIndexTable[wFromOrder] = pstProgramIndexTable[wToOrder];
        pstProgramIndexTable[wToOrder] = stDTVProgramIndex;
    }

#if (ENABLE_DTV_EPG)
    if(_pfNotify_CM_SwapProgram)
    {
        _pfNotify_CM_SwapProgram(wFromOrder, wToOrder);
    }
#endif

    return TRUE;
}

//****************************************************************************
/// Get Program Table
/// @param wPRIndex \b IN: Program Index
/// @param pcBuffer \b IN: pointer To Buffer
/// @param eMember \b IN: program data Member
/// -@see PROGRAMDATA_MEMBER
/// @return BOOLEAN: Function execution result
//****************************************************************************
//static BOOLEAN GetProgramTable(DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
BOOLEAN GetProgramTable_DBSel(TypDtvDbSel eDbSel, DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    //printf("\nGetProgramTable [] wPRIndex = %d, eMember = %d\n", wPRIndex, eMember);

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    U16 u16ProgTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDbSel);


    // Check Prog Index ...
#if 1
    //if( wPRIndex >= u16ProgTableArraySize )
    if( FALSE == msAPI_DtvDB_Is_ProgTableIndexValid(eDbSel, wPRIndex) )
    {
        printf("\nError: wPRIndex=%u >= u16ProgTableArraySize=%u\n", wPRIndex, u16ProgTableArraySize);
        return FALSE;
    }
#else
    {
        if( MAX_DTVPROGRAM <= wPRIndex )
        {
            return FALSE;
        }
    }
#endif

    if( IsProgramEntityActive_DBSel(eDbSel, wPRIndex) == FALSE )
    {
        FillProgramDataWithDefault(pcBuffer, eMember);
        return FALSE;
    }


    U32 u32CurProgRamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_ProgTable_ByIndex(eDbSel,wPRIndex);

    //printf("Get eMember: %bu ", eMember);
#if ENABLE_S2
    //if (IsS2InUse())
    if( eDbSel == E_DTV_DB_SEL_DVBS )
    {
        switch(eMember)
        {
        case E_DATA_ALL:
            return GetNVRAM(u32CurProgRamDiskAddr, pcBuffer, sizeof(DTV_CHANNEL_INFO));

        case E_DATA_ORDER:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wOrder),
                    pcBuffer, sizeof(WORD));

        case E_DATA_LCN:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wLCN),
                    pcBuffer, sizeof(WORD));

#if 1//NTV_FUNCTION_ENABLE
        case E_DATA_TS_LCN:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wTS_LCN),
                    pcBuffer, sizeof(WORD));
#endif
        case E_DATA_SIMU_LCN:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wSimu_LCN),
                    pcBuffer, sizeof(WORD));

        case E_DATA_ID_INDEX:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bIDIdex),
                pcBuffer, sizeof(WORD));

        case E_DATA_VERSION_PAT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer),
                pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_PMT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer),
                pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_NIT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer),
                pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_SDT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer),
                pcBuffer, sizeof(BYTE));

        case E_DATA_MISC:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stCHAttribute),
                pcBuffer, sizeof(CHANNEL_ATTRIBUTE));

#if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
        case E_DATA_ID_FAV:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stChIsFav),
                pcBuffer, sizeof(BYTE));
#endif
        case E_DATA_SERVICE_ID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wService_ID),
                pcBuffer, sizeof(WORD));

        case E_DATA_PMT_PID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wPmt_PID),
                pcBuffer, sizeof(WORD));

        case E_DATA_PCR_PID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wPCR_PID),
                pcBuffer, sizeof(WORD));

        case E_DATA_VIDEO_PID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wVideo_PID),
                pcBuffer, sizeof(WORD));

        case E_DATA_AUDIO_STREAM_INFO:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stAudInfo),
                pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

        case E_DATA_SERVICE_NAME:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bChannelName),
                pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

#if ENABLE_DTV_STORE_TTX_PAGE_INFO
        case E_DATA_TTX_LIST:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, u8ListPage),
                pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
#endif
        /*
        case E_DATA_PROGRAM_SATLITE:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, SatId),
                pcBuffer, sizeof(BYTE));
                */

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
        case E_DATA_SGT_PID:
                return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wSgt_PID),
                pcBuffer, sizeof(WORD));
#endif

        default:
            return FALSE;
            break;
        }
    }
    else
#endif
    {
        switch(eMember)
        {
        case E_DATA_ALL:
            return GetNVRAM(u32CurProgRamDiskAddr, pcBuffer, sizeof(DTV_CHANNEL_INFO));

        case E_DATA_ORDER:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wOrder),
                            pcBuffer, sizeof(WORD));

        case E_DATA_LCN:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wLCN),
                            pcBuffer, sizeof(WORD));
#if 1//NTV_FUNCTION_ENABLE
        case E_DATA_TS_LCN:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wTS_LCN),
                            pcBuffer, sizeof(WORD));
#endif
        case E_DATA_SIMU_LCN:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wSimu_LCN),
                            pcBuffer, sizeof(WORD));

        case E_DATA_ID_INDEX:
        #if 1 //(ENABLE_S2_WORD)
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bIDIdex),
                    pcBuffer, sizeof(WORD));
        #else
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bIDIdex),
                            pcBuffer, sizeof(BYTE));
        #endif

        case E_DATA_VERSION_PAT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer),
                                pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_PMT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_NIT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_SDT:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_MISC:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stCHAttribute),
                            pcBuffer, sizeof(CHANNEL_ATTRIBUTE));

        case E_DATA_SERVICE_ID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wService_ID),
                            pcBuffer, sizeof(WORD));
        case E_DATA_PMT_PID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wPmt_PID),
                            pcBuffer, sizeof(WORD));
        case E_DATA_PCR_PID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wPCR_PID),
                            pcBuffer, sizeof(WORD));

        case E_DATA_VIDEO_PID:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wVideo_PID),
                            pcBuffer, sizeof(WORD));

        case E_DATA_AUDIO_STREAM_INFO:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stAudInfo),
                            pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

    #if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
        case E_DATA_NAME_MULTILINGUAL_LANGUAGE:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bMultiLanguage),
                            pcBuffer, sizeof(BYTE)*MAX_MULTI_LINGUAL_SERVICE_NAME);

        case E_DATA_SERVICE_MULTILINGUAL_NAME:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bMultiChannelName),
                            pcBuffer, sizeof(BYTE)*MAX_MULTI_LINGUAL_SERVICE_NAME*MAX_SERVICE_NAME);
    #endif

        case E_DATA_SERVICE_NAME:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bChannelName),
                            pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

        #if ENABLE_DTV_STORE_TTX_PAGE_INFO
        case E_DATA_TTX_LIST:
             return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, u8ListPage),
                        pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
        #endif

    #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
        case E_DATA_ID_FAV:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stChIsFav),
                pcBuffer, sizeof(BYTE));
    #endif

    #if(MHEG5_SIINFO_ENABLE)
         case E_DATA_PROVIDER_NAME:
            return GetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bProviderName),
                            pcBuffer, sizeof(BYTE)*SI_MAX_SERVICE_NAME);
    #endif //#if(MHEG5_SIINFO_ENABLE)

        default:
            return FALSE;
            break;
        }
    }

    return TRUE;

#else
    eDbSel=eDbSel;
    //printf("\nGetProgramTable [] wPRIndex = %d, eMember = %d\n", wPRIndex, eMember);
    DWORD StartAddress=BASEADDRESS_PR_DTVPRTABLE;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wPRIndex )
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if( MAX_DTVPROGRAM <= wPRIndex )
        {
            return FALSE;
        }
    }

    if(IsProgramEntityActive(wPRIndex) == FALSE)
    {
        FillProgramDataWithDefault(pcBuffer, eMember);
        return FALSE;
    }

#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        StartAddress=BASEADDRESS_PR_DTV_C_PRTABLE;
    }
#endif

    //printf("Get eMember: %bu ", eMember);
#if ENABLE_S2
    if (IsS2InUse())
    {
        switch(eMember)
        {
            case E_DATA_ALL:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)),
                pcBuffer, sizeof(DTV_CHANNEL_INFO));

            case E_DATA_ORDER:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wOrder)),
                pcBuffer, sizeof(WORD));

            case E_DATA_LCN:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wLCN)),
                pcBuffer, sizeof(WORD));

        #if NTV_FUNCTION_ENABLE
            case E_DATA_TS_LCN:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wTS_LCN)),
                pcBuffer, sizeof(WORD));
        #endif
            case E_DATA_SIMU_LCN:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wSimu_LCN)),
                pcBuffer, sizeof(WORD));

            case E_DATA_ID_INDEX:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bIDIdex)),
                pcBuffer, sizeof(WORD));

            case E_DATA_VERSION_PAT:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_PMT:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_NIT:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_SDT:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_MISC:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stCHAttribute)),
                pcBuffer, sizeof(CHANNEL_ATTRIBUTE));

        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            case E_DATA_ID_FAV:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stChIsFav)),
                pcBuffer, sizeof(BYTE));
        #endif
            case E_DATA_SERVICE_ID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wService_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_PMT_PID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wPmt_PID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_PCR_PID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wPCR_PID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_VIDEO_PID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wVideo_PID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_AUDIO_STREAM_INFO:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stAudInfo)),
                pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

            case E_DATA_SERVICE_NAME:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bChannelName)),
                pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

        #if ENABLE_DTV_STORE_TTX_PAGE_INFO
            case E_DATA_TTX_LIST:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, u8ListPage)),
                pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
        #endif
            case E_DATA_PROGRAM_SATLITE:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, SatId)),
                pcBuffer, sizeof(BYTE));

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
            case E_DATA_SGT_PID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wSgt_PID)),
                pcBuffer, sizeof(WORD));
#endif

            default:
                break;
        }
    }
    else
#endif
    {
    switch(eMember)
    {
    case E_DATA_ALL:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)),
                        pcBuffer, sizeof(DTV_CHANNEL_INFO));

    case E_DATA_ORDER:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wOrder)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_LCN:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wLCN)),
                        pcBuffer, sizeof(WORD));
#if 1//NTV_FUNCTION_ENABLE
    case E_DATA_TS_LCN:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wTS_LCN)),
                        pcBuffer, sizeof(WORD));
#endif
    case E_DATA_SIMU_LCN:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wSimu_LCN)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_ID_INDEX:
        #if 1//(ENABLE_S2_WORD)
            return GetNVRAM(StartAddress+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bIDIdex)),
                pcBuffer, sizeof(WORD));
        #else
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bIDIdex)),
                        pcBuffer, sizeof(BYTE));
        #endif

    case E_DATA_VERSION_PAT:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_VERSION_PMT:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_VERSION_NIT:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_VERSION_SDT:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_MISC:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stCHAttribute)),
                        pcBuffer, sizeof(CHANNEL_ATTRIBUTE));

    case E_DATA_SERVICE_ID:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wService_ID)),
                        pcBuffer, sizeof(WORD));
    case E_DATA_PMT_PID:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wPmt_PID)),
                        pcBuffer, sizeof(WORD));
    case E_DATA_PCR_PID:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wPCR_PID)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_VIDEO_PID:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wVideo_PID)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_AUDIO_STREAM_INFO:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stAudInfo)),
                        pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    case E_DATA_NAME_MULTILINGUAL_LANGUAGE:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bMultiLanguage)),
                        pcBuffer, sizeof(BYTE)*MAX_MULTI_LINGUAL_SERVICE_NAME);
    case E_DATA_SERVICE_MULTILINGUAL_NAME:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bMultiChannelName)),
                        pcBuffer, sizeof(BYTE)*MAX_MULTI_LINGUAL_SERVICE_NAME*MAX_SERVICE_NAME);
#endif

    case E_DATA_SERVICE_NAME:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bChannelName)),
                        pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

    #if ENABLE_DTV_STORE_TTX_PAGE_INFO
    case E_DATA_TTX_LIST:
         return GetNVRAM(StartAddress+
                    (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, u8ListPage)),
                    pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
    #endif

        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            case E_DATA_ID_FAV:
                return GetNVRAM(StartAddress+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stChIsFav)),
                pcBuffer, sizeof(BYTE));
        #endif

#if(MHEG5_SIINFO_ENABLE)
     case E_DATA_PROVIDER_NAME:
        return GetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bProviderName)),
                        pcBuffer, sizeof(BYTE)*SI_MAX_SERVICE_NAME);
#endif //#if(MHEG5_SIINFO_ENABLE)

    default:
        break;
    }
    }

    return FALSE;
#endif
}

//****************************************************************************
/// Set Program Table
/// @param wPRIndex \b IN: Program Index
/// @param pcBuffer \b IN: pointer To Buffer
/// @param eMember \b IN: program data Member
/// -@see PROGRAMDATA_MEMBER
/// @return BOOLEAN: Function execution result
//****************************************************************************
//static BOOLEAN SetProgramTable(DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
BOOLEAN SetProgramTable_DBSel(TypDtvDbSel eDbSel, DWORD wPRIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    U16 u16ProgTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDbSel);

    //printf("SetProgramTable(wPRIndex=0x%x, pcBuffer[0]=0x%X, eMember=%u)\n", wPRIndex, pcBuffer[0], eMember);

#if CHLIST_DISABLE_SI_AUTO_UPDATA
    if(g_enScanType != SCAN_TYPE_AUTO && g_enScanType != SCAN_TYPE_MANUAL &&
    (eMember != E_DATA_PCR_PID && eMember != E_DATA_VIDEO_PID && eMember != E_DATA_AUDIO_STREAM_INFO && eMember != E_DATA_PMT_PID))
    {
        return FALSE;
    }
#endif

    // Check Prog Index ...
#if 1
    //if( wPRIndex >= u16ProgTableArraySize )
    if( FALSE == msAPI_DtvDB_Is_ProgTableIndexValid(eDbSel, wPRIndex) )
    {
        printf("\nError: wPRIndex=%u >= u16ProgTableArraySize=%u\n", wPRIndex, u16ProgTableArraySize);
        return FALSE;
    }
#else
    {
        if( MAX_DTVPROGRAM <= wPRIndex )
        {
            return FALSE;
        }
    }
#endif

    if( (eMember != E_DATA_ALL) && FALSE == IsProgramEntityActive(wPRIndex) )
    {
        return FALSE;
    }

    //printf("Set eMember: %bu ", eMember);

    U32 u32CurProgRamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_ProgTable_ByIndex(eDbSel,wPRIndex);

#if ENABLE_S2
    //if (IsS2InUse())
    if( eDbSel == E_DTV_DB_SEL_DVBS )
    {
        switch(eMember)
        {
            case E_DATA_ALL:
            return SetNVRAM(u32CurProgRamDiskAddr, pcBuffer, sizeof(DTV_CHANNEL_INFO));

            case E_DATA_ORDER:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wOrder),
            pcBuffer, sizeof(WORD));

            case E_DATA_LCN:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wLCN),
            pcBuffer, sizeof(WORD));

        #if 1//NTV_FUNCTION_ENABLE
            case E_DATA_TS_LCN:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wTS_LCN),
            pcBuffer, sizeof(WORD));
        #endif

            case E_DATA_SIMU_LCN:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wSimu_LCN),
            pcBuffer, sizeof(WORD));

            case E_DATA_ID_INDEX:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bIDIdex),
            pcBuffer, sizeof(WORD));

            case E_DATA_VERSION_PAT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer),
            pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_PMT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer),
            pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_NIT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer),
            pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_SDT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer),
            pcBuffer, sizeof(BYTE));

            case E_DATA_MISC:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stCHAttribute),
            pcBuffer, sizeof(CHANNEL_ATTRIBUTE));

        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            case E_DATA_ID_FAV:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stChIsFav),
            pcBuffer, sizeof(BYTE));
        #endif

            case E_DATA_SERVICE_ID:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wService_ID),
            pcBuffer, sizeof(WORD));

            case E_DATA_PCR_PID:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wPCR_PID),
            pcBuffer, sizeof(WORD));

            case E_DATA_VIDEO_PID:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wVideo_PID),
            pcBuffer, sizeof(WORD));

            case E_DATA_AUDIO_STREAM_INFO:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stAudInfo),
            pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

            case E_DATA_SERVICE_NAME:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bChannelName),
            pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

    #if ENABLE_DTV_STORE_TTX_PAGE_INFO
            case E_DATA_TTX_LIST:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, u8ListPage),
            pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
    #endif

        /*
            case E_DATA_PROGRAM_SATLITE:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, SatId),
            pcBuffer, sizeof(BYTE));
            */

        #if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
            case E_DATA_SGT_PID:
                return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wSgt_PID),
                pcBuffer, sizeof(WORD));
        #endif

            default:
                return FALSE;
                break;
        }
    }
    else
#endif
    {
        switch(eMember)
        {
        case E_DATA_ALL:
            return SetNVRAM(u32CurProgRamDiskAddr,
                            pcBuffer, sizeof(DTV_CHANNEL_INFO));

        case E_DATA_ORDER:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wOrder),
                            pcBuffer, sizeof(WORD));

        case E_DATA_LCN:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wLCN),
                            pcBuffer, sizeof(WORD));
#if 1//NTV_FUNCTION_ENABLE
        case E_DATA_TS_LCN:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wTS_LCN),
                            pcBuffer, sizeof(WORD));
#endif
        case E_DATA_SIMU_LCN:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wSimu_LCN),
                            pcBuffer, sizeof(WORD));

        case E_DATA_ID_INDEX:
        #if 1 // (ENABLE_S2_WORD)
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bIDIdex),
                            pcBuffer, sizeof(WORD));
        #else
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bIDIdex),
                            pcBuffer, sizeof(BYTE));
        #endif

        case E_DATA_VERSION_PAT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_PMT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_NIT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_VERSION_SDT:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer),
                            pcBuffer, sizeof(BYTE));

        case E_DATA_MISC:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stCHAttribute),
                            pcBuffer, sizeof(CHANNEL_ATTRIBUTE));


        case E_DATA_SERVICE_ID:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wService_ID),
                            pcBuffer, sizeof(WORD));

        case E_DATA_PCR_PID:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wPCR_PID),
                            pcBuffer, sizeof(WORD));

        case E_DATA_VIDEO_PID:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, wVideo_PID),
                            pcBuffer, sizeof(WORD));

        case E_DATA_AUDIO_STREAM_INFO:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stAudInfo),
                            pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

        case E_DATA_SERVICE_NAME:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bChannelName),
                            pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

        #if ENABLE_DTV_STORE_TTX_PAGE_INFO
        case E_DATA_TTX_LIST:
             return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, u8ListPage),
                            pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
        #endif

#if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
        case E_DATA_ID_FAV:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, stChIsFav),
                        pcBuffer, sizeof(BYTE));
#endif

#if(MHEG5_SIINFO_ENABLE)
        case E_DATA_PROVIDER_NAME:
            return SetNVRAM(u32CurProgRamDiskAddr + offsetof(DTV_CHANNEL_INFO, bProviderName),
                            pcBuffer, sizeof(BYTE)*SI_MAX_SERVICE_NAME);

#endif //#if(MHEG5_SIINFO_ENABLE)

        default:
            return FALSE;
            break;
        }
    }

    return TRUE;

#else
    eDbSel=eDbSel;
    DWORD StartAddress=BASEADDRESS_PR_DTVPRTABLE;

    //printf("SetProgramTable(wPRIndex=0x%x, pcBuffer[0]=0x%X, eMember=%u)\n", wPRIndex, pcBuffer[0], eMember);

#if CHLIST_DISABLE_SI_AUTO_UPDATA
    if(g_enScanType != SCAN_TYPE_AUTO && g_enScanType != SCAN_TYPE_MANUAL &&
    (eMember != E_DATA_PCR_PID && eMember != E_DATA_VIDEO_PID && eMember != E_DATA_AUDIO_STREAM_INFO && eMember != E_DATA_PMT_PID))
    {
        return FALSE;
    }
#endif

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wPRIndex )
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if( MAX_DTVPROGRAM <= wPRIndex )
        {
            return FALSE;
        }
    }

    if( eMember != E_DATA_ALL && FALSE == IsProgramEntityActive(wPRIndex) )
    {
        return FALSE;
    }

    //printf("Set eMember: %bu ", eMember);
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        StartAddress=BASEADDRESS_PR_DTV_C_PRTABLE;
    }
#endif

#if ENABLE_S2
    if (IsS2InUse())
    {
        switch(eMember)
        {
            case E_DATA_ALL:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)),
                pcBuffer, sizeof(DTV_CHANNEL_INFO));

            case E_DATA_ORDER:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wOrder)),
                pcBuffer, sizeof(WORD));

            case E_DATA_LCN:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wLCN)),
                pcBuffer, sizeof(WORD));
        #if 1//NTV_FUNCTION_ENABLE
            case E_DATA_TS_LCN:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wTS_LCN)),
                pcBuffer, sizeof(WORD));
        #endif
            case E_DATA_SIMU_LCN:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wSimu_LCN)),
                pcBuffer, sizeof(WORD));

            case E_DATA_ID_INDEX:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bIDIdex)),
                pcBuffer, sizeof(WORD));

            case E_DATA_VERSION_PAT:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_PMT:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_NIT:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_VERSION_SDT:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_MISC:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stCHAttribute)),
                pcBuffer, sizeof(CHANNEL_ATTRIBUTE));

        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            case E_DATA_ID_FAV:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stChIsFav)),
                pcBuffer, sizeof(BYTE));
        #endif

            case E_DATA_SERVICE_ID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wService_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_PCR_PID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wPCR_PID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_VIDEO_PID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wVideo_PID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_AUDIO_STREAM_INFO:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stAudInfo)),
                pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

            case E_DATA_SERVICE_NAME:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bChannelName)),
                pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

        #if ENABLE_DTV_STORE_TTX_PAGE_INFO
            case E_DATA_TTX_LIST:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, u8ListPage)),
                pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
        #endif
        /*
            case E_DATA_PROGRAM_SATLITE:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLE+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, SatId)),
                pcBuffer, sizeof(BYTE));
                */
            default:
                break;
        }
    }
    else
#endif
    {
    switch(eMember)
    {
    case E_DATA_ALL:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)),
                        pcBuffer, sizeof(DTV_CHANNEL_INFO));

    case E_DATA_ORDER:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wOrder)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_LCN:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wLCN)),
                        pcBuffer, sizeof(WORD));
#if 1//NTV_FUNCTION_ENABLE
    case E_DATA_TS_LCN:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wTS_LCN)),
                        pcBuffer, sizeof(WORD));
#endif

    case E_DATA_SIMU_LCN:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wSimu_LCN)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_ID_INDEX:
        #if 1 //(ENABLE_S2_WORD)
            return SetNVRAM(StartAddress+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bIDIdex)),
                pcBuffer, sizeof(WORD));
        #else

        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bIDIdex)),
                        pcBuffer, sizeof(BYTE));
        #endif

    case E_DATA_VERSION_PAT:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPATVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_VERSION_PMT:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bPMTVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_VERSION_NIT:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bNITVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_VERSION_SDT:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stPSI_SI_Version)+offsetof(DVB_TABLE_VERSION, bSDTVer)),
                        pcBuffer, sizeof(BYTE));

    case E_DATA_MISC:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stCHAttribute)),
                        pcBuffer, sizeof(CHANNEL_ATTRIBUTE));


    case E_DATA_SERVICE_ID:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wService_ID)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_PCR_PID:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wPCR_PID)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_VIDEO_PID:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, wVideo_PID)),
                        pcBuffer, sizeof(WORD));

    case E_DATA_AUDIO_STREAM_INFO:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stAudInfo)),
                        pcBuffer, sizeof(AUD_INFO)*MAX_AUD_LANG_NUM);

    case E_DATA_SERVICE_NAME:
        return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bChannelName)),
                        pcBuffer, sizeof(BYTE)*MAX_SERVICE_NAME);

    #if ENABLE_DTV_STORE_TTX_PAGE_INFO
    case E_DATA_TTX_LIST:
         return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, u8ListPage)),
                        pcBuffer, sizeof(BYTE)*MAX_LISTPAGE_SIZE);
    #endif

        #if(ENABLE_S2_CHANNEL_FAV_NEWSTYLE)
            case E_DATA_ID_FAV:
                return SetNVRAM(StartAddress+
                (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, stChIsFav)),
                pcBuffer, sizeof(BYTE));
        #endif

        #if(MHEG5_SIINFO_ENABLE)
            case E_DATA_PROVIDER_NAME:
                return SetNVRAM(StartAddress+
                        (wPRIndex*sizeof(DTV_CHANNEL_INFO)+offsetof(DTV_CHANNEL_INFO, bProviderName)),
                        pcBuffer, sizeof(BYTE)*SI_MAX_SERVICE_NAME);

#endif //#if(MHEG5_SIINFO_ENABLE)

    default:
        break;
    }
    }
    return FALSE;
#endif
}

BOOLEAN SetIDTable(WORD u16IDIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    return SetIDTable_DBSel( CUR_DB_SEL(), u16IDIndex, pcBuffer, eMember);
}

BOOLEAN SetIDTable_DBSel(TypDtvDbSel eDtvDbSel, WORD u16IDIndex, BYTE * pcBuffer,PROGRAMDATA_MEMBER eMember)
{
    U16 u16ProgramIdTabArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);

#if 1//(ENABLE_API_DTV_SYSTEM_2015)

#else
    eDtvDbSel=eDtvDbSel;
    WORD bIDIndex = u16IDIndex;

    DWORD StartAddress=BASEADDRESS_PR_DTVIDTABLE;
    DWORD NetworkStartAddress=BASEADDRESS_PR_DTVNETWORK;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        StartAddress=BASEADDRESS_PR_DTV_C_IDTABLE;
        NetworkStartAddress=BASEADDRESS_PR_DTV_C_DTVNETWORK;
    }
  #endif
#endif

#if CHLIST_DISABLE_SI_AUTO_UPDATA
    if(g_enScanType != SCAN_TYPE_AUTO && g_enScanType != SCAN_TYPE_MANUAL)
    {
        return FALSE;
    }
#endif

    // Check parameter valid?
    if( (eMember == E_DATA_NETWORK_ID)
       ||(eMember == E_DATA_NETWORK_NAME)
       ||(eMember == E_DATA_NETWORK)
      )
    {
        if( u16IDIndex >= u16NetWorkTableArraySize )
        {
            printf("\nError: u16IDIndex=%u >= u16NetWorkTableArraySize=%u\n", u16IDIndex, u16NetWorkTableArraySize);
            return FALSE;
        }
    }
    else
    {
        if( u16IDIndex >= u16ProgramIdTabArraySize )
        {
            printf("\nError: u16IDIndex=%u >= u16ProgramIdTabArraySize=%u\n", u16IDIndex, u16ProgramIdTabArraySize);
            return FALSE;
        }
    }


#if 1//(ENABLE_API_DTV_SYSTEM_2015)

    U32 u32CurProgIdRamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_IdTable_ByIndex(eDtvDbSel, u16IDIndex);
    U32 u32CurProgNetWorkRamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_NetWork_ByIndex(eDtvDbSel, u16IDIndex);


#if(ENABLE_S2)
    //if (IsS2TVInUse())
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cPLPID),
                    pcBuffer, sizeof(BYTE));

        /*
            case E_PRDATA_HPLP:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cHpLp),
                    pcBuffer, sizeof(BYTE));
                    */

            case E_DATA_PCN:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cRFChannelNumber),
                pcBuffer, sizeof(BYTE));

            case E_DATA_TS_ID:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wTransportStream_ID),
                pcBuffer, sizeof(WORD));

            case E_DATA_ON_ID:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                return SetNVRAM( u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, wNetwork_ID),
                pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wCellID),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                return SetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, bNetworkName),
                pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                return SetNVRAM(u32CurProgNetWorkRamDiskAddr, pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cNetWorkIndex),
                    pcBuffer, sizeof(BYTE));

        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cOriginal_RF),
                    pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, dwAlternativeTime),
                pcBuffer, sizeof(DWORD));
        #endif
            case E_DATA_ID_TABLE:
                return SetNVRAM(u32CurProgIdRamDiskAddr, pcBuffer, sizeof(DTVPROGRAMID_M) );

            default:
                return FALSE;
        }
    }
    else
#endif
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cPLPID),
                            pcBuffer, sizeof(BYTE));
        /*
            case E_PRDATA_HPLP:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cHpLp),
                    pcBuffer, sizeof(BYTE));
                    */

            case E_DATA_PCN:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cRFChannelNumber),
                            pcBuffer, sizeof(BYTE));

            case E_DATA_TS_ID:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wTransportStream_ID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_ON_ID:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                return SetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, wNetwork_ID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wCellID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                return SetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, bNetworkName),
                            pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                return SetNVRAM(u32CurProgNetWorkRamDiskAddr,pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                return SetNVRAM( u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cNetWorkIndex),
                            pcBuffer, sizeof(BYTE) );

        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cOriginal_RF),
                            pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, dwAlternativeTime),
                                pcBuffer, sizeof(DWORD));
        #endif

            case E_DATA_ID_TABLE:
                return SetNVRAM(u32CurProgIdRamDiskAddr, pcBuffer, sizeof(DTVPROGRAMID_M));

        #if ENABLE_DVBC
            case E_DATA_FREQ:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, u32Frequency),
                                pcBuffer, sizeof(U32));

            case E_DATA_SYMB_RATE:
                //return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, u32SymbRate), pcBuffer, sizeof(U32));
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, u16SymbolRate), pcBuffer, sizeof(U16));

            case E_DATA_QAM_MODE:
                return SetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, QamMode),
                                pcBuffer, sizeof(BYTE));
        #endif

            default:
                return FALSE;
                break;
        }
    }

#else
  #if(ENABLE_S2)
    if (IsS2TVInUse())
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cPLPID)),pcBuffer, sizeof(BYTE));

            case E_DATA_PCN:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cRFChannelNumber)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_TS_ID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wTransportStream_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_ON_ID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, wNetwork_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wCellID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, bNetworkName)),
                pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVNETWORK)),pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cNetWorkIndex)),pcBuffer, sizeof(BYTE));

        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cOriginal_RF)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, dwAlternativeTime)),
                pcBuffer, sizeof(DWORD));
        #endif
            case E_DATA_ID_TABLE:
                return SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)),pcBuffer, sizeof(DTVPROGRAMID_M));
        }
    }
    else
  #endif
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cPLPID)),pcBuffer, sizeof(BYTE));

            case E_DATA_PCN:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cRFChannelNumber)),
                            pcBuffer, sizeof(BYTE));

            case E_DATA_TS_ID:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wTransportStream_ID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_ON_ID:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                return SetNVRAM(NetworkStartAddress+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, wNetwork_ID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wCellID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                return SetNVRAM(NetworkStartAddress+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, bNetworkName)),
                            pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                return SetNVRAM(NetworkStartAddress+(bIDIndex*sizeof(DTVNETWORK)),pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cNetWorkIndex)),pcBuffer, sizeof(BYTE));

        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cOriginal_RF)),
                            pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, dwAlternativeTime)),
                                pcBuffer, sizeof(DWORD));
        #endif

            case E_DATA_ID_TABLE:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)),pcBuffer, sizeof(DTVPROGRAMID_M));

        #if ENABLE_DVBC
            case E_DATA_FREQ:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, u32Frequency)),
                                pcBuffer, sizeof(U32));

            case E_DATA_SYMB_RATE:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, u32SymbRate)),
                                pcBuffer, sizeof(U32));

            case E_DATA_QAM_MODE:
                return SetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, QamMode)),
                                pcBuffer, sizeof(BYTE));
        #endif
        }
    }
#endif

    return FALSE;
}

#define DEBUG_GET_ID_TAB(x) //x
BOOLEAN GetIDTable(WORD u16IDIndex, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    return GetIDTable_DBSel( CUR_DB_SEL(), u16IDIndex, pcBuffer, eMember);
}

BOOLEAN GetIDTable_DBSel(TypDtvDbSel eDtvDbSel, WORD bIDIndex, BYTE * pcBuffer,PROGRAMDATA_MEMBER eMember)
{
    U16 u16ProgramIdTabArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);

#if(ENABLE_API_DTV_SYSTEM_2015)
    DEBUG_GET_ID_TAB(printf("GetIDTable_DBSel(eDtvDbSel=%u, bIDIndex=%u, eMember=%u)\n", eDtvDbSel, bIDIndex, eMember););

    //DEBUG_GET_ID_TAB(printf(" u16ProgramIdTabArraySize=%u\n", u16ProgramIdTabArraySize););
    //DEBUG_GET_ID_TAB(printf(" u16NetWorkTableArraySize=%u\n", u16NetWorkTableArraySize););

#else
    eDtvDbSel=eDtvDbSel;
    DWORD StartAddress=BASEADDRESS_PR_DTVIDTABLE;
    DWORD NetworkStartAddress=BASEADDRESS_PR_DTVNETWORK;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        StartAddress=BASEADDRESS_PR_DTV_C_IDTABLE;
        NetworkStartAddress=BASEADDRESS_PR_DTV_C_DTVNETWORK;
    }
  #endif
#endif

    // Check parameter valid?
#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    if( (eMember == E_DATA_NETWORK_ID)
       ||(eMember == E_DATA_NETWORK_NAME)
       ||(eMember == E_DATA_NETWORK)
      )
    {
        if( bIDIndex >= u16NetWorkTableArraySize )
        {
            printf("\nError: u16IDIndex=%u >= u16NetWorkTableArraySize=%u\n", bIDIndex, u16NetWorkTableArraySize);
            return FALSE;
        }
    }
    else
    {
        if( bIDIndex >= u16ProgramIdTabArraySize )
        {
            printf("\nError: u16IDIndex=%u >= u16ProgramIdTabArraySize=%u\n", bIDIndex, u16ProgramIdTabArraySize);
            return FALSE;
        }
    }
#else
  #if(ENABLE_S2)
    if (IsS2TVInUse())
    {
        if( MAX_DTV_S2_MUX_NUMBER <= bIDIndex )
    {
        return FALSE;
    }
    }
    else
  #endif
    {
        if( msAPI_CM_GetMuxMaxNumber() <= bIDIndex )
        {
            return FALSE;
        }
    }
#endif


#if(ENABLE_API_DTV_SYSTEM_2015)
    U32 u32CurProgIdRamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_IdTable_ByIndex(eDtvDbSel, bIDIndex);
    U32 u32CurProgNetWorkRamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_NetWork_ByIndex(eDtvDbSel, bIDIndex);

    //DEBUG_GET_ID_TAB(printf(" u32CurProgIdRamDiskAddr=%u\n", u32CurProgIdRamDiskAddr););
    //DEBUG_GET_ID_TAB(printf(" u32CurProgNetWorkRamDiskAddr=%u\n", u32CurProgNetWorkRamDiskAddr););

  #if(ENABLE_S2)
    //if(IsS2TVInUse())
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cPLPID),
                        pcBuffer, sizeof(BYTE));
        /*
            case E_PRDATA_HPLP:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cHpLp),
                        pcBuffer, sizeof(BYTE));
                        */

            case E_DATA_PCN:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cRFChannelNumber),
                    pcBuffer, sizeof(BYTE));

            case E_DATA_TS_ID:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wTransportStream_ID),
                pcBuffer, sizeof(WORD));

            case E_DATA_ON_ID:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID),
                pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wCellID),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                return GetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, wNetwork_ID),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                return GetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, bNetworkName),
                pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                return GetNVRAM(u32CurProgNetWorkRamDiskAddr, pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cNetWorkIndex),
                        pcBuffer, sizeof(BYTE));

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cOriginal_RF),
                    pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, dwAlternativeTime),
                    pcBuffer, sizeof(DWORD));
#endif
            case E_DATA_ID_TABLE:
                return GetNVRAM(u32CurProgIdRamDiskAddr,
                    pcBuffer, sizeof(DTVPROGRAMID_M));

            case E_DATA_ID_SATLITE:
                return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, SatelliteId),
                    pcBuffer, sizeof(BYTE));

            default:
                return FALSE;
        }
    }
    else
#endif
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                   return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cPLPID),
                            pcBuffer, sizeof(BYTE));

        /*
            case E_PRDATA_HPLP:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cHpLp),
                        pcBuffer, sizeof(BYTE));
                        */

            case E_DATA_PCN:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cRFChannelNumber),
                            pcBuffer, sizeof(BYTE));


            case E_DATA_TS_ID:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wTransportStream_ID),
                            pcBuffer, sizeof(WORD));


            case E_DATA_ON_ID:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, wCellID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                    return GetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, wNetwork_ID),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                    return GetNVRAM(u32CurProgNetWorkRamDiskAddr + offsetof(DTVNETWORK, bNetworkName),
                            pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                    return GetNVRAM(u32CurProgNetWorkRamDiskAddr, pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cNetWorkIndex),
                            pcBuffer, sizeof(BYTE));

        #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, cOriginal_RF),
                            pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, dwAlternativeTime),
                            pcBuffer, sizeof(DWORD));
        #endif
            case E_DATA_ID_TABLE:
                    return GetNVRAM(u32CurProgIdRamDiskAddr,
                            pcBuffer, sizeof(DTVPROGRAMID_M));
        #if ENABLE_DVBC
            case E_DATA_FREQ:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, u32Frequency),
                            pcBuffer, sizeof(U32));

            case E_DATA_SYMB_RATE:
                    //return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, u32SymbRate), pcBuffer, sizeof(U32));
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, u16SymbolRate), pcBuffer, sizeof(U16));

            case E_DATA_QAM_MODE:
                    return GetNVRAM(u32CurProgIdRamDiskAddr + offsetof(DTVPROGRAMID_M, QamMode),
                            pcBuffer, sizeof(BYTE));
        #endif

            default:
                return FALSE;
        }
    }
#else
  #if(ENABLE_S2)
    if(IsS2TVInUse())
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cPLPID)),pcBuffer, sizeof(BYTE));

            case E_DATA_PCN:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cRFChannelNumber)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_TS_ID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wTransportStream_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_ON_ID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wCellID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, wNetwork_ID)),
                pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, bNetworkName)),
                pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVNETWORK+(bIDIndex*sizeof(DTVNETWORK)),pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cNetWorkIndex)),pcBuffer, sizeof(BYTE));

    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cOriginal_RF)),
                pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, dwAlternativeTime)),
                pcBuffer, sizeof(DWORD));
    #endif
            case E_DATA_ID_TABLE:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)),
                pcBuffer, sizeof(DTVPROGRAMID_M));

            case E_DATA_ID_SATLITE:
                return GetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLE+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, SatelliteId)),
                pcBuffer, sizeof(BYTE));
        }
    }
    else
#endif
    {
        switch(eMember)
        {
            case E_DATA_PLP:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cPLPID)),pcBuffer, sizeof(BYTE));

            case E_DATA_PCN:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cRFChannelNumber)),
                            pcBuffer, sizeof(BYTE));


            case E_DATA_TS_ID:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wTransportStream_ID)),
                            pcBuffer, sizeof(WORD));


            case E_DATA_ON_ID:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wOriginalNetwork_ID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_CELL_ID:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, wCellID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_ID:
                    return GetNVRAM(NetworkStartAddress+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, wNetwork_ID)),
                            pcBuffer, sizeof(WORD));

            case E_DATA_NETWORK_NAME:
                    return GetNVRAM(NetworkStartAddress+(bIDIndex*sizeof(DTVNETWORK)+offsetof(DTVNETWORK, bNetworkName)),
                            pcBuffer, sizeof(BYTE)*MAX_NETWORK_NAME);

            case E_DATA_NETWORK:
                    return GetNVRAM(NetworkStartAddress+(bIDIndex*sizeof(DTVNETWORK)),pcBuffer, sizeof(DTVNETWORK));

            case E_DATA_NETWORK_INDEX:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cNetWorkIndex)),pcBuffer, sizeof(BYTE));

    #if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
            case E_DATA_ORIGINAL_PCN:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, cOriginal_RF)),
                            pcBuffer, sizeof(BYTE));

            case E_DATA_ALTERNATIVE_TIME:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, dwAlternativeTime)),
                            pcBuffer, sizeof(DWORD));
    #endif
            case E_DATA_ID_TABLE:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)),
                            pcBuffer, sizeof(DTVPROGRAMID_M));
    #if ENABLE_DVBC
            case E_DATA_FREQ:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, u32Frequency)),
                            pcBuffer, sizeof(U32));

            case E_DATA_SYMB_RATE:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, u32SymbRate)),
                            pcBuffer, sizeof(U32));

            case E_DATA_QAM_MODE:
                    return GetNVRAM(StartAddress+(bIDIndex*sizeof(DTVPROGRAMID_M)+offsetof(DTVPROGRAMID_M, QamMode)),
                            pcBuffer, sizeof(BYTE));
    #endif
        }
    }
#endif

    return FALSE;
}

//****************************************************************************
/// Get Empty Index Of Program Table
/// @return WORD: Program Index
//****************************************************************************
static WORD GetEmptyIndexOfProgramTable_DBSel(TypDtvDbSel eDtvDbSel)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    U16 u16ProgTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel);
#endif
    WORD wPRIndex;

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    for(wPRIndex=0; wPRIndex < u16ProgTableArraySize; wPRIndex++)
#else
    for(wPRIndex=0; wPRIndex < MAX_DTVPROGRAM; wPRIndex++)
#endif
    {
        if( FALSE == IsProgramEntityActive_DBSel(eDtvDbSel, wPRIndex) )
        {
            return wPRIndex;
        }
    }

    return INVALID_PRINDEX;
}

//****************************************************************************
/// Is Program Entity Active
/// @param wPRIndex \b IN: Program Index
/// @return BOOLEAN:
/// - 1: Default is Active
/// - 0: NO
//****************************************************************************
// Refine Status: 20150716 Done
//static BOOLEAN IsProgramEntityActive(WORD wPRIndex)
BOOLEAN IsProgramEntityActive_DBSel(TypDtvDbSel eDbSel, WORD wPRIndex )
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method

    U16 u16ProgTabArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDbSel);
    U8* pu8ProgTableMap = msAPI_DtvDB_Get_ProgTableMap(eDbSel);

    // Check range
    if( wPRIndex >= u16ProgTabArraySize )
    {
        return FALSE;
    }

    return ( (pu8ProgTableMap[wPRIndex/8] & (0x01 << (wPRIndex%8))) ? TRUE : FALSE );

#else

    eDbSel = eDbSel;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wPRIndex )
        {
            return FALSE;
        }
        return ( (m_acS2ProgramTableMap[wPRIndex/8] & (0x01 << (wPRIndex%8))) ? TRUE : FALSE );
    }
    else
#endif
    {
        if( MAX_DTVPROGRAM <= wPRIndex )
        {
            return FALSE;
        }

    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())
        {
            return ( (m_acDTVProgramTableMap_DVBC[wPRIndex/8] & (0x01 << (wPRIndex%8))) ? TRUE : FALSE );
        }
        else
    #endif
        {
            return ( (m_acDTVProgramTableMap[wPRIndex/8] & (0x01 << (wPRIndex%8))) ? TRUE : FALSE );
        }
    }
#endif
}

//static BOOLEAN IsIDEntityActive(WORD wIDIndex)
BOOLEAN IsIDEntityActive_DBSel(TypDtvDbSel eDtvDbSel, WORD wIDIndex)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16IDTabArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    U8* pu8IDTableMap = msAPI_DtvDB_Get_ProgIdTableMap(eDtvDbSel);


    // Check range
    if( wIDIndex >= u16IDTabArraySize )
    {
        return FALSE;
    }

    return ( (pu8IDTableMap[wIDIndex/8] & (0x01 << (wIDIndex%8))) ? TRUE : FALSE );
#else

    eDtvDbSel=eDtvDbSel;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_MUX_NUMBER <= wIDIndex )
        {
            return FALSE;
        }
        return ( (m_acs2IDtableMap[wIDIndex/8] & (0x01 << (wIDIndex%8))) ? TRUE : FALSE );
    }
    else
#endif
    {
        if( msAPI_CM_GetMuxMaxNumber() <= wIDIndex )
        {
            return FALSE;
        }

    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())
        {
            return ( (m_acDTVIDtableMap_DVBC[wIDIndex/8] & (0x01 << (wIDIndex%8))) ? TRUE : FALSE );
        }
        else
    #endif
        {
            return ( (m_acDTVIDtableMap[wIDIndex/8] & (0x01 << (wIDIndex%8))) ? TRUE : FALSE );
        }
    }

#endif
}

//****************************************************************************
/// This function will Active Program Entity
/// @param wPRIndex \b IN: Program Index
/// @param bActive \b IN: Active or noy
/// @return BOOLEAN: Function execution result
//****************************************************************************
//static BOOLEAN ActiveProgramEntity(WORD wPRIndex, BOOLEAN bActive)
BOOLEAN ActiveProgramEntity_DBSel(TypDtvDbSel eDtvDbSel, WORD wPRIndex, BOOLEAN bActive)
{
#if(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16ProgTabArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel);
    U8* pu8ProgTableMap = msAPI_DtvDB_Get_ProgTableMap(eDtvDbSel);
    U32 u32ProgTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgTableMapRamDiskAddr(eDtvDbSel);
    U16 u16Temp;


    // Check range
    if( wPRIndex >= u16ProgTabArraySize )
    {
        printf("\nError: wPRIndex=%u >= u16ProgTabArraySize=%u\n", wPRIndex, u16ProgTabArraySize);
        return FALSE;
    }

    u16Temp = wPRIndex / 8;

    if( TRUE == bActive )
    {
        pu8ProgTableMap[u16Temp] =  pu8ProgTableMap[u16Temp] | (0x01 << (wPRIndex%8));
    }
    else
    {
        pu8ProgTableMap[u16Temp] =  pu8ProgTableMap[u16Temp] & ~(0x01 << (wPRIndex%8));
    }

    SetNVRAM(u32ProgTableMapRamDiskAddr + u16Temp, &(pu8ProgTableMap[u16Temp]), sizeof(BYTE));

    return TRUE;

#else

    BYTE cTemp;

    eDtvDbSel=eDtvDbSel;

    if( MAX_DTVPROGRAM <= wPRIndex )
    {
        return FALSE;
    }

    cTemp = wPRIndex/8;

  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        if(TRUE == bActive)
        {
            m_acDTVProgramTableMap_DVBC[cTemp] =  m_acDTVProgramTableMap_DVBC[cTemp] | (0x01 << (wPRIndex%8));
        }
        else
        {
            m_acDTVProgramTableMap_DVBC[cTemp] =  m_acDTVProgramTableMap_DVBC[cTemp] & ~(0x01 << (wPRIndex%8));
        }

        SetNVRAM(BASEADDRESS_PR_DTV_C_PRTABLEMAP+cTemp, &(m_acDTVProgramTableMap_DVBC[cTemp]), sizeof(BYTE));
    }
    else
    {
        if(TRUE == bActive)
        {
            m_acDTVProgramTableMap[cTemp] =  m_acDTVProgramTableMap[cTemp] | (0x01 << (wPRIndex%8));
        }
        else
        {
            m_acDTVProgramTableMap[cTemp] =  m_acDTVProgramTableMap[cTemp] & ~(0x01 << (wPRIndex%8));
        }

        SetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP+cTemp, &(m_acDTVProgramTableMap[cTemp]), sizeof(BYTE));
    }
  #else
    if(TRUE == bActive)
    {
        m_acDTVProgramTableMap[cTemp] =  m_acDTVProgramTableMap[cTemp] | (0x01 << (wPRIndex%8));
    }
    else
    {
        m_acDTVProgramTableMap[cTemp] =  m_acDTVProgramTableMap[cTemp] & ~(0x01 << (wPRIndex%8));
    }

    SetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP+cTemp, &(m_acDTVProgramTableMap[cTemp]), sizeof(BYTE));
  #endif

    return TRUE;

#endif
}

BOOLEAN ActiveIDEntity(WORD wIDIndex, BOOLEAN bActive)
{
    return ActiveIDEntity_DBSel( CUR_DB_SEL(), wIDIndex, bActive);
}

BOOLEAN ActiveIDEntity_DBSel(TypDtvDbSel eDtvDbSel, WORD wIDIndex, BOOLEAN bActive)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    U16 u16IDTabArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    U8* pu8IDTableMap = msAPI_DtvDB_Get_ProgIdTableMap(eDtvDbSel);
    U16 u16Temp;
    U32 u32IDTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgIdTableMapRamDiskAddr(eDtvDbSel);



    // Check range
    if( wIDIndex >= u16IDTabArraySize )
    {
        printf("\nError: wPRIndex=%u >= u16IDTabArraySize=%u\n", wIDIndex, u16IDTabArraySize);
        return FALSE;
    }

    u16Temp = wIDIndex/8;

    if(TRUE == bActive)
    {
        pu8IDTableMap[u16Temp] =  pu8IDTableMap[u16Temp] | (0x01 << (wIDIndex%8));
    }
    else
    {
        pu8IDTableMap[u16Temp] =  pu8IDTableMap[u16Temp] & ~(0x01 << (wIDIndex%8));
    }

    SetNVRAM(u32IDTableMapRamDiskAddr + u16Temp, &(pu8IDTableMap[u16Temp]), sizeof(BYTE));

    return TRUE;

#else
    eDtvDbSel=eDtvDbSel;

#if 1 //(ENABLE_S2_WORD)
    WORD cTemp;
#else
    BYTE cTemp;
#endif

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_MUX_NUMBER <= wIDIndex )
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if( msAPI_CM_GetMuxMaxNumber() <= wIDIndex )
        {
            return FALSE;
        }
    }

    cTemp = wIDIndex/8;

#if ENABLE_S2
    if (IsS2InUse())
    {
        if(TRUE == bActive)
        {
            m_acs2IDtableMap[cTemp] =  m_acs2IDtableMap[cTemp] | (0x01 << (wIDIndex%8));
        }
        else
        {
            m_acs2IDtableMap[cTemp] =  m_acs2IDtableMap[cTemp] & ~(0x01 << (wIDIndex%8));
        }
        //printf("\r\n m_acs2IDtableMap[cTemp]=%d", m_acs2IDtableMap[cTemp]);
        SetNVRAM(S2_BASEADDRESS_PR_DTVIDTABLEMAP+cTemp, &(m_acs2IDtableMap[cTemp]), sizeof(BYTE));
    }
    else
#endif
    {
    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())
        {
            if(TRUE == bActive)
            {
                m_acDTVIDtableMap[cTemp] =  m_acDTVIDtableMap[cTemp] | (0x01 << (wIDIndex%8));
            }
            else
            {
                m_acDTVIDtableMap[cTemp] =  m_acDTVIDtableMap[cTemp] & ~(0x01 << (wIDIndex%8));
            }

            SetNVRAM(BASEADDRESS_PR_DTV_C_IDTABLEMAP+cTemp, &(m_acDTVIDtableMap_DVBC[cTemp]), sizeof(BYTE));
        }
        else
        {
            if(TRUE == bActive)
            {
                m_acDTVIDtableMap[cTemp] =  m_acDTVIDtableMap[cTemp] | (0x01 << (wIDIndex%8));
            }
            else
            {
                m_acDTVIDtableMap[cTemp] =  m_acDTVIDtableMap[cTemp] & ~(0x01 << (wIDIndex%8));
            }

            SetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP+cTemp, &(m_acDTVIDtableMap[cTemp]), sizeof(BYTE));
        }
    #else

        if(TRUE == bActive)
        {
            m_acDTVIDtableMap[cTemp] =  m_acDTVIDtableMap[cTemp] | (0x01 << (wIDIndex%8));
        }
        else
        {
            m_acDTVIDtableMap[cTemp] =  m_acDTVIDtableMap[cTemp] & ~(0x01 << (wIDIndex%8));
        }

        SetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP+cTemp, &(m_acDTVIDtableMap[cTemp]), sizeof(BYTE));
    #endif
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Fill Audio Stream Info With Default
/// @param pstAudioStreamInfo \b IN: Audio Stream Info
/// - @see AUD_INFO
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN FillAudioStreamInfoWithDefault(AUD_INFO *pstAudioStreamInfo)
{
    BYTE i;

    pstAudioStreamInfo->wAudPID = INVALID_PID;
    //pstAudioStreamInfo->wAudType = E_AUDIOSTREAM_INVALID;
    pstAudioStreamInfo->eSIAudType = E_SI_AUDIOSTREAM_INVALID;

#if 1//NTV_FUNCTION_ENABLE
    //pstAudioStreamInfo->u8ProfileAndLevel = 0;
    pstAudioStreamInfo->eProfileAndLevel = E_CM_PROFILE_NONE;
    //pstAudioStreamInfo->u8Component_AAC_Type = 0;
#endif

    for(i = 0; i < MAX_AUD_ISOLANG_NUM; i++)
    {
        pstAudioStreamInfo->aISOLangInfo[i].bAudType = 0x00;
        pstAudioStreamInfo->aISOLangInfo[i].bISOLanguageInfo = 0x00;
        pstAudioStreamInfo->aISOLangInfo[i].bIsValid = FALSE;
        pstAudioStreamInfo->aISOLangInfo[i].bBroadcastMixedAD = FALSE;
        pstAudioStreamInfo->aISOLangInfo[i].bISOLangIndex = LANGUAGE_NONE;
        pstAudioStreamInfo->aISOLangInfo[i].bReserved = FALSE;
    }
    return TRUE;
}

//****************************************************************************
/// Fill Program ID With Default
/// @param pstDTVPROGRAMID_M \b IN: DTV Program ID
/// - @see DTVPROGRAMID_M
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN FillProgramIDWithDefault(DTVPROGRAMID_M * pstDTVProgramID)
{
    pstDTVProgramID->wTransportStream_ID = INVALID_TS_ID;
    pstDTVProgramID->wOriginalNetwork_ID = INVALID_ON_ID;
    pstDTVProgramID->cNetWorkIndex = INVALID_NETWORKINDEX;
    pstDTVProgramID->cRFChannelNumber = INVALID_PHYSICAL_CHANNEL_NUMBER;
    pstDTVProgramID->cPLPID = INVALID_PLPID;
#if (ENABLE_SAVE_SQI)
    pstDTVProgramID->wStrengthQuality = DEFAULT_SIGNAL_STRENGTH;
#endif
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    pstDTVProgramID->cOriginal_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;
    pstDTVProgramID->dwAlternativeTime = INVALID_ALTERNATIVETIME;
#endif

#if (ENABLE_S2)
    if( IsS2InUse() )
    {
        pstDTVProgramID->u32S2Frequency = INVALID_FREQUENCY;
    }
    else
    {
        pstDTVProgramID->u32Frequency = INVALID_FREQUENCY;
    }
#endif

    //pstDTVProgramID->u32SymbRate  = INVALID_SYMBRATE;
    pstDTVProgramID->u16SymbolRate = INVALID_SYMBRATE;

  #if ENABLE_DVBC
    //pstDTVProgramID->u32Frequency = INVALID_FREQUENCY;
    pstDTVProgramID->QamMode      = INVALID_QAMMODE;
    pstDTVProgramID->enBandWidth  = (RF_CHANNEL_BANDWIDTH)0x0;
  #endif

#if(ENABLE_S2)
    //pstDTVProgramID->u32S2Frequency = 0xffffffff;
    //pstDTVProgramID->u16SymbolRate = 0xffff;
    pstDTVProgramID->u8Polarity = 1;//0xff;
    pstDTVProgramID->SatelliteId = 0xff;
#endif

    pstDTVProgramID->wCellID = DEFAULT_CELLID;

    return TRUE;
}

//****************************************************************************
/// Fill NETWORK With Default
/// @param DTVNETWORK \b IN: Network ID
/// - @see DTVNETWORK
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN FillNetworkWithDefault(DTVNETWORK * pstDTVNetwork)
{
    pstDTVNetwork->wNetwork_ID = INVALID_NID;
    memset(pstDTVNetwork->bNetworkName,0x00,sizeof(BYTE)*MAX_NETWORK_NAME);

    return TRUE;
}

//****************************************************************************
/// Fill Program Index With Default
/// @param pstDTVProgramIndex \b IN: DTV Program Index
/// - @see DTVPROGRAMINDEX
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN FillProgramIndexWithDefault(DTVPROGRAMINDEX * pstDTVProgramIndex)
{
    pstDTVProgramIndex->bServiceType = DEFAULT_SERVICE_TYPE;
    pstDTVProgramIndex->bVisibleServiceFlag = DEFAULT_VISIBLE_SERVICE_FLAG;
    pstDTVProgramIndex->bIsDelete = DEFAULT_IS_DELETED;
    pstDTVProgramIndex->bIsReplaceDel = DEFAULT_IS_REPLACE_DEL;
    pstDTVProgramIndex->bIsFavorite = DEFAULT_IS_FAVORITE;
    pstDTVProgramIndex->bIsSkipped = DEFAULT_IS_SKIPPED;
    pstDTVProgramIndex->bIsLock = DEFAULT_IS_LOCKED;
    pstDTVProgramIndex->bIsStillPicture = DEFAULT_IS_STILL_PICTURE;
    pstDTVProgramIndex->bIsMove = DEFAULT_IS_MOVED;
    pstDTVProgramIndex->bInvalidCell = DEFAULT_IS_INVALID_CELL;
    pstDTVProgramIndex->bUnconfirmedService = DEFAULT_IS_UNCONFIRMED_SERVICE;
    pstDTVProgramIndex->bInvalidService = DEFAULT_IS_INVALID_SERVICE;
    pstDTVProgramIndex->bNumericSelectionFlag = DEFAULT_NUMERIC_SELECTION_FLAG;
    pstDTVProgramIndex->wPRIndex = DEFAULT_PRINDEX;
    pstDTVProgramIndex->eLCNAssignmentType = DEFAULT_LCN_ASSIGNMENT_TYPE;
    pstDTVProgramIndex->wLCN = DEFAULT_LCN;
    pstDTVProgramIndex->wSimu_LCN = DEFAULT_SIMU_LCN;
    pstDTVProgramIndex->wService_ID = DEFAULT_SERVICE_ID;
    pstDTVProgramIndex->bServiceTypePrio = DEFAULT_SERVICE_TYPE_PRIO;
    pstDTVProgramIndex->bIsSpecialService = DEFAULT_SPECIAL_SERVICE;
    #if ENABLE_T_C_CHANNEL_MIX
    pstDTVProgramIndex->bIsTerrestrial = DEFAULT_IS_CABLE;
    #endif


#if 1//(ENABLE_S2_WORD)
    pstDTVProgramIndex->cIDIndex = 0xfff;
#else
    pstDTVProgramIndex->cIDIndex = 0x7f;
#endif

    return TRUE;
}

//****************************************************************************
/// Fill Program Data With Default
/// @param pcBuffer \b IN: pointer to Buffer
/// @param eMember \b IN: Member
/// - @see PROGRAMDATA_MEMBER
/// @return BOOLEAN: Function execution result
//****************************************************************************
static BOOLEAN FillProgramDataWithDefault(BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    BYTE i;
    CHANNEL_ATTRIBUTE Misc;
    AUD_INFO astAudioStreamInfo[MAX_AUD_LANG_NUM];
    DTV_CHANNEL_INFO DTVProgramData;
    BYTE sServiceName[MAX_SERVICE_NAME],bPhN,bVerNum;
    WORD wOrder,wLCN,wMemID;

    // Added by coverity_0216
    memset(&DTVProgramData, 0, sizeof(DTV_CHANNEL_INFO));

    switch(eMember)
    {
    case E_DATA_ALL:
        DTVProgramData.wOrder = DEFAULT_ORDER;
        DTVProgramData.wLCN = DEFAULT_LCN;
#if 1//NTV_FUNCTION_ENABLE
        DTVProgramData.wTS_LCN = DEFAULT_LCN;
#endif
        DTVProgramData.wSimu_LCN = DEFAULT_SIMU_LCN;
        DTVProgramData.stPSI_SI_Version.bPATVer = DEFAULT_VERSION;
        DTVProgramData.stPSI_SI_Version.bPMTVer = DEFAULT_VERSION;
        DTVProgramData.stPSI_SI_Version.bNITVer = DEFAULT_VERSION;
        DTVProgramData.stPSI_SI_Version.bSDTVer = DEFAULT_VERSION;
        DTVProgramData.stCHAttribute.bVisibleServiceFlag = DEFAULT_VISIBLE_SERVICE_FLAG;
        DTVProgramData.stCHAttribute.bNumericSelectionFlag = DEFAULT_NUMERIC_SELECTION_FLAG;
        DTVProgramData.stCHAttribute.bIsDelete = DEFAULT_IS_DELETED;
        DTVProgramData.stCHAttribute.bIsReplaceDel = DEFAULT_IS_REPLACE_DEL;
        DTVProgramData.stCHAttribute.bIsFavorite = DEFAULT_IS_FAVORITE;
        DTVProgramData.stCHAttribute.bIsSkipped = DEFAULT_IS_SKIPPED;
        DTVProgramData.stCHAttribute.bIsLock = DEFAULT_IS_LOCKED;
        DTVProgramData.stCHAttribute.bIsScramble = DEFAULT_IS_SCRAMBLED;
        DTVProgramData.stCHAttribute.bIsStillPicture = DEFAULT_IS_STILL_PICTURE;
        DTVProgramData.stCHAttribute.bIsMove = DEFAULT_IS_MOVED;
        DTVProgramData.stCHAttribute.bInvalidCell = DEFAULT_IS_INVALID_CELL;
        DTVProgramData.stCHAttribute.bUnconfirmedService = DEFAULT_IS_UNCONFIRMED_SERVICE;
        DTVProgramData.stCHAttribute.bInvalidService = DEFAULT_IS_INVALID_SERVICE;
        DTVProgramData.stCHAttribute.bReplaceService = DEFAULT_IS_REPLACE_SERVICE;
        DTVProgramData.stCHAttribute.bIsServiceIdOnly = DEFAULT_IS_SERVICE_ID_ONLY;
        DTVProgramData.stCHAttribute.eVideoType = DEFAULT_VIDEO_TYPE;
        DTVProgramData.stCHAttribute.bServiceType = DEFAULT_SERVICE_TYPE;
        DTVProgramData.stCHAttribute.bIsSpecialService = DEFAULT_SPECIAL_SERVICE;
        DTVProgramData.stCHAttribute.bServiceTypePrio = DEFAULT_SERVICE_TYPE_PRIO;
        DTVProgramData.stCHAttribute.wSignalStrength = DEFAULT_SIGNAL_STRENGTH;
        DTVProgramData.stCHAttribute.bValidLCN = DEFAULT_LCN_VALID;
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
        DTVProgramData.wSgt_PID = DEFAULT_SGT_PID;
#endif

#if ENABLE_TARGET_REGION
        DTVProgramData.stCHAttribute.cRegion = DEFAULT_REGION;
#endif
        #if ENABLE_T_C_CHANNEL_MIX
        DTVProgramData.stCHAttribute.bIsTerrestrial = DEFAULT_IS_CABLE;
        #endif
        DTVProgramData.wService_ID = DEFAULT_SERVICE_ID;
        DTVProgramData.wPmt_PID = DEFAULT_PMT_PID;
        DTVProgramData.wPCR_PID = DEFAULT_PCR_PID;
        DTVProgramData.wVideo_PID = DEFAULT_VIDEO_PID;

        for(i=0; i < MAX_AUD_LANG_NUM; i++)
        {
            FillAudioStreamInfoWithDefault(&(DTVProgramData.stAudInfo[i]));
        }
#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
        {
            int j;
            for(j=0;j<MAX_MULTI_LINGUAL_SERVICE_NAME;j++)
            {
                DTVProgramData.bMultiLanguage[j]=INVALID_LANG_INDEX;
                for(i=0; i < MAX_SERVICE_NAME; i++)
                {
                    DTVProgramData.bMultiChannelName[j][i] = NULL;
                }
            }
        }
#endif

        for(i=0; i < MAX_SERVICE_NAME; i++)
        {
            DTVProgramData.bChannelName[i] = NULL;
        }

        #if ENABLE_DTV_STORE_TTX_PAGE_INFO
        SetListPageNumber(DTVProgramData.u8ListPage, 0, DEFAULT_LISTPAGE[0]);
        SetListPageNumber(DTVProgramData.u8ListPage, 1, DEFAULT_LISTPAGE[1]);
        SetListPageNumber(DTVProgramData.u8ListPage, 2, DEFAULT_LISTPAGE[2]);
        SetListPageNumber(DTVProgramData.u8ListPage, 3, DEFAULT_LISTPAGE[3]);
        #endif
        memcpy(pcBuffer,&DTVProgramData,sizeof(DTV_CHANNEL_INFO));
        break;

    case E_DATA_ORDER:
        wOrder = DEFAULT_ORDER;
        memcpy(pcBuffer,&wOrder,sizeof(WORD));
        break;
    case E_DATA_SIMU_LCN:
    case E_DATA_LCN:
        if(eMember == E_DATA_LCN)
        {
            wLCN = DEFAULT_LCN;
        }
        else
        {
            wLCN = DEFAULT_SIMU_LCN;
        }
        memcpy(pcBuffer,&wLCN,sizeof(WORD));
        break;

    case E_DATA_PCN:
        bPhN = DEFAULT_PCN;
        memcpy(pcBuffer,&bPhN,sizeof(BYTE));
        break;

    case E_DATA_VERSION_PAT:
    case E_DATA_VERSION_PMT:
    case E_DATA_VERSION_NIT:
    case E_DATA_VERSION_SDT:
        bVerNum = DEFAULT_VERSION;
        memcpy(pcBuffer,&bVerNum,sizeof(BYTE));
        break;

    case E_DATA_MISC:
        Misc.bVisibleServiceFlag = DEFAULT_VISIBLE_SERVICE_FLAG;
        Misc.bNumericSelectionFlag = DEFAULT_NUMERIC_SELECTION_FLAG;
        Misc.bIsDelete = DEFAULT_IS_DELETED;
        Misc.bIsReplaceDel = DEFAULT_IS_REPLACE_DEL;
        Misc.bIsFavorite = DEFAULT_IS_FAVORITE;
        Misc.bIsSkipped = DEFAULT_IS_SKIPPED;
        Misc.bIsLock = DEFAULT_IS_LOCKED;
        Misc.bIsScramble = DEFAULT_IS_SCRAMBLED;
        Misc.bIsStillPicture = DEFAULT_IS_STILL_PICTURE;
        Misc.bIsMove = DEFAULT_IS_MOVED;
        Misc.bInvalidCell = DEFAULT_IS_INVALID_CELL;
        Misc.bInvalidService = DEFAULT_IS_INVALID_SERVICE;
        Misc.bUnconfirmedService = DEFAULT_IS_UNCONFIRMED_SERVICE;
        Misc.bReplaceService = DEFAULT_IS_REPLACE_SERVICE;
        Misc.bIsServiceIdOnly = DEFAULT_IS_SERVICE_ID_ONLY;
        Misc.eVideoType = DEFAULT_VIDEO_TYPE;
        Misc.bServiceType = DEFAULT_SERVICE_TYPE;
        Misc.bIsSpecialService = DEFAULT_SPECIAL_SERVICE;
        Misc.bServiceTypePrio = DEFAULT_SERVICE_TYPE_PRIO;
        Misc.wSignalStrength = DEFAULT_SIGNAL_STRENGTH;
        Misc.bValidLCN = DEFAULT_LCN_VALID;

#if ENABLE_TARGET_REGION
        Misc.cRegion=DEFAULT_REGION;
#endif
        #if ENABLE_T_C_CHANNEL_MIX
        Misc.bIsTerrestrial = DEFAULT_IS_CABLE;
        #endif
        memcpy(pcBuffer,&Misc,sizeof(CHANNEL_ATTRIBUTE));
        break;

    case E_DATA_TS_ID:
        wMemID = DEFAULT_TS_ID;
        memcpy(pcBuffer,&wMemID,sizeof(WORD));
        break;

    case E_DATA_ON_ID:
        wMemID = DEFAULT_ON_ID;
        memcpy(pcBuffer,&wMemID,sizeof(WORD));
        break;

    case E_DATA_SERVICE_ID:
        wMemID = DEFAULT_SERVICE_ID;
        memcpy(pcBuffer,&wMemID,sizeof(WORD));
        break;

    case E_DATA_PCR_PID:
        wMemID = DEFAULT_PCR_PID;
        memcpy(pcBuffer,&wMemID,sizeof(WORD));
        break;

    case E_DATA_VIDEO_PID:
        wMemID = DEFAULT_VIDEO_PID;
        memcpy(pcBuffer,&wMemID,sizeof(WORD));
        break;

    case E_DATA_AUDIO_STREAM_INFO:
        for(i=0; i < MAX_AUD_LANG_NUM; i++)
        {
            FillAudioStreamInfoWithDefault(&astAudioStreamInfo[i]);
        }
        memcpy(pcBuffer,astAudioStreamInfo,sizeof(AUD_INFO));
        break;

    case E_DATA_SERVICE_NAME:

        for(i=0; i < MAX_SERVICE_NAME; i++)
        {
            sServiceName[i] = NULL;
        }
        memcpy(pcBuffer,sServiceName,sizeof(BYTE)*MAX_SERVICE_NAME);
        break;

    default:
        return FALSE;
    }

    return TRUE;
}

//****************************************************************************
/// Are Orders Same Service
/// @param wOrderOfChamp \b IN: Order Of Champ
/// @param wOrderOfChallenger \b IN: Order Of Challenger
/// @return BOOLEAN:
/// - TRUE:  Is same
/// - FALSE: NO
//****************************************************************************
static BOOLEAN AreOrdersSameService(WORD wOrderOfChamp, WORD wOrderOfChallenger, BOOLEAN bCheckTSID)
{
    WORD wIDs_1=0;
    WORD wIDs_2=0;
    BOOLEAN bRet = FALSE;
#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wOrderOfChamp || MAX_DTV_S2_PROGRAM <= wOrderOfChallenger )
        {
            bRet = FALSE;
            goto exit1;
        }

        if( (m_astS2ProgramIndexTable[wOrderOfChamp].bServiceType == m_astS2ProgramIndexTable[wOrderOfChallenger].bServiceType) &&
        ((E_SERVICETYPE_DTV == m_astS2ProgramIndexTable[wOrderOfChamp].bServiceType) ||
        (E_SERVICETYPE_DATA == m_astS2ProgramIndexTable[wOrderOfChamp].bServiceType)||
        (E_SERVICETYPE_RADIO == m_astS2ProgramIndexTable[wOrderOfChamp].bServiceType)) )
        {
            if( (FALSE == IsProgramEntityActive(m_astS2ProgramIndexTable[wOrderOfChamp].wPRIndex)) ||
            (FALSE == IsProgramEntityActive(m_astS2ProgramIndexTable[wOrderOfChallenger].wPRIndex)) )
            {
                bRet = FALSE;
                goto exit1;
            }

            GetProgramTable(m_astS2ProgramIndexTable[wOrderOfChamp].wPRIndex, (BYTE *)&wIDs_1, E_DATA_SERVICE_ID);
            GetProgramTable(m_astS2ProgramIndexTable[wOrderOfChallenger].wPRIndex, (BYTE *)&wIDs_2, E_DATA_SERVICE_ID);
            if( wIDs_1 == wIDs_2 )
            {
                if(bCheckTSID)
                {
                    GetIDTable(m_astS2ProgramIndexTable[wOrderOfChamp].cIDIndex, (BYTE *)&wIDs_1, E_DATA_TS_ID);
                    GetIDTable(m_astS2ProgramIndexTable[wOrderOfChallenger].cIDIndex, (BYTE *)&wIDs_2, E_DATA_TS_ID);
                    if( wIDs_1 != wIDs_2 )
                    {
                        bRet = FALSE;
                        goto exit1;
                    }
                }
                GetIDTable(m_astS2ProgramIndexTable[wOrderOfChamp].cIDIndex, (BYTE *)&wIDs_1, E_DATA_ON_ID);
                GetIDTable(m_astS2ProgramIndexTable[wOrderOfChallenger].cIDIndex, (BYTE *)&wIDs_2, E_DATA_ON_ID);
                if( wIDs_1 == wIDs_2 )
                {
                    bRet = TRUE;
                    goto exit1;
                }
            }
        }
    }
    else
#endif
    {
        //if( MAX_DTVPROGRAM <= wOrderOfChamp || MAX_DTVPROGRAM <= wOrderOfChallenger )
        if( u16ProgramIndexTableArraySize <= wOrderOfChamp || u16ProgramIndexTableArraySize <= wOrderOfChallenger )
        {
            bRet = FALSE;
            goto exit1;
        }

        if( (pstProgramIndexTable[wOrderOfChamp].bServiceType == pstProgramIndexTable[wOrderOfChallenger].bServiceType) &&
            ((E_SERVICETYPE_DTV == pstProgramIndexTable[wOrderOfChamp].bServiceType) ||
            (E_SERVICETYPE_DATA == pstProgramIndexTable[wOrderOfChamp].bServiceType)||
            (E_SERVICETYPE_RADIO == pstProgramIndexTable[wOrderOfChamp].bServiceType)) )
        {
            if( (FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrderOfChamp].wPRIndex)) ||
                (FALSE == IsProgramEntityActive(pstProgramIndexTable[wOrderOfChallenger].wPRIndex)) )
            {
                bRet = FALSE;
                goto exit1;
            }

            GetProgramTable(pstProgramIndexTable[wOrderOfChamp].wPRIndex, (BYTE *)&wIDs_1, E_DATA_SERVICE_ID);
            GetProgramTable(pstProgramIndexTable[wOrderOfChallenger].wPRIndex, (BYTE *)&wIDs_2, E_DATA_SERVICE_ID);
            if( wIDs_1 == wIDs_2 )
            {
                if(bCheckTSID)
                {
                    GetIDTable(pstProgramIndexTable[wOrderOfChamp].cIDIndex, (BYTE *)&wIDs_1, E_DATA_TS_ID);
                    GetIDTable(pstProgramIndexTable[wOrderOfChallenger].cIDIndex, (BYTE *)&wIDs_2, E_DATA_TS_ID);
                    if( wIDs_1 != wIDs_2 )
                    {
                        bRet = FALSE;
                        goto exit1;
                    }
                }

                GetIDTable(pstProgramIndexTable[wOrderOfChamp].cIDIndex, (BYTE *)&wIDs_1, E_DATA_ON_ID);
                GetIDTable(pstProgramIndexTable[wOrderOfChallenger].cIDIndex, (BYTE *)&wIDs_2, E_DATA_ON_ID);
                if( wIDs_1 == wIDs_2 )
                {
                    bRet = TRUE;
                    goto exit1;

                }
            }
        }
    }
exit1:

    return bRet;

}

//****************************************************************************
/// Get Count Of Same Service With IDs
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param wService_ID \b IN: Service ID
/// @param bCheckTsID \b IN: bCheck TsID or not
/// - TRUE: To check
/// - FALSE: NO
/// @return BYTE: count
//****************************************************************************
static BYTE GetCountOfSameServiceWithIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BOOLEAN bCheckTsID)
{
    WORD wPosition;
    WORD wOrder;
#if 1//(ENABLE_S2_WORD)
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    WORD wProgramCount;
    BYTE cCountOfSameService;

#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    cCountOfSameService = 0;

    for(wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            if( wService_ID != m_astS2ProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }
            cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
            // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
            if( (!bCheckTsID || (wTransportStream_ID == _astS2ProgramIDTable[cIDIndex].wTransportStream_ID)) &&
            wOriginalNetwork_ID == _astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID )
            {
                cCountOfSameService++;
            }
        }
        else
    #endif
        {

            //if( wService_ID != m_astDTVProgramIndexTable[wOrder].wService_ID )
            if( wService_ID != pstProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }

            //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;

            // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
            if( (!bCheckTsID || (wTransportStream_ID == pMuxTable[cIDIndex].wTransportStream_ID)) &&
                wOriginalNetwork_ID == pMuxTable[cIDIndex].wOriginalNetwork_ID )
            {
              #if(ASTRA_HD_ENABLE)
                if(GetASTRA_HD_ENABLE() && pstProgramIndexTable[wOrder].bIsScramble)
                    continue;
              #endif
                cCountOfSameService++;
            }
        }
    }

    return cCountOfSameService;
}

//****************************************************************************
/// Get Count Of Same Service With IDs
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param wService_ID \b IN: Service ID
/// @param wPmt_Pid \b IN: Pmt_Pid
/// @param bCheckTsID \b IN: bCheck TsID or not
/// @param bCheckPmtPid \b IN: bCheck PmtPid or not
/// - TRUE: To check
/// - FALSE: NO
/// @return BYTE: count
//****************************************************************************
static BYTE GetCountOfSameServiceWithIDsAndPmtPid(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, WORD wPmt_Pid, BOOLEAN bCheckTsID)
{
    WORD wPosition;
    WORD wOrder;
    WORD cIDIndex;
    WORD wProgramCount;
    BYTE cCountOfSameService;

#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
 #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
 #endif
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    cCountOfSameService = 0;

    for(wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        //if( wService_ID != m_astDTVProgramIndexTable[wOrder].wService_ID )
        if( wService_ID != pstProgramIndexTable[wOrder].wService_ID )
        {
            continue;
        }

        //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;

        // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
        if( (!bCheckTsID || (wTransportStream_ID == pMuxTable[cIDIndex].wTransportStream_ID)) &&
            (wOriginalNetwork_ID == pMuxTable[cIDIndex].wOriginalNetwork_ID) && (wPmt_Pid == msAPI_CM_GetPmtPID(bServiceType,wPosition)) )
        {
            cCountOfSameService++;
        }
    }

    return cCountOfSameService;
}

//****************************************************************************
/// Get Order Of Same Service With IDs
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param wService_ID \b IN: Service ID
/// @param bCheckTsID \b IN: bCheck TsID or not
/// - TRUE: To check
/// - FALSE: NO
/// @return BYTE: count
//****************************************************************************
static WORD GetOrderOfSameServiceWithIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, BOOLEAN bCheckTsID)
{
    WORD wPosition;
    WORD wOrder;
#if 1//(ENABLE_S2_WORD)
    WORD cIDIndex;
#else
    BYTE cIDIndex;
#endif
    WORD wProgramCount;
    BYTE cCountOfSameService;
    WORD wRet;

#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    cCountOfSameService = 0;

    wRet = INVALID_ORDER;

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            if( wService_ID != m_astS2ProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }
            cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
            // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
            if( (!bCheckTsID || (wTransportStream_ID == _astS2ProgramIDTable[cIDIndex].wTransportStream_ID)) &&
            wOriginalNetwork_ID == _astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID )
            {
                cCountOfSameService++;

                if( cOrdinal == cCountOfSameService )
                {
                    wRet = wOrder;
                    break;
                }
            }
        }
        else
    #endif
        {

            //if( wService_ID != m_astDTVProgramIndexTable[wOrder].wService_ID )
            if( wService_ID != pstProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }

            //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;

            // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
            if( (!bCheckTsID || (wTransportStream_ID == pMuxTable[cIDIndex].wTransportStream_ID)) &&
                wOriginalNetwork_ID == pMuxTable[cIDIndex].wOriginalNetwork_ID )
            {
                cCountOfSameService++;

                if( cOrdinal == cCountOfSameService )
                {
                    wRet = wOrder;
                    break;
                }
            }
        }
    }

    return wRet;
}

//****************************************************************************
/// Get Order Of Same Service With IDs and frequency
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param wService_ID \b IN: Service ID
/// @param bCheckTsID \b IN: bCheck TsID or not
/// - TRUE: To check
/// - FALSE: NO
/// @return BYTE: count
//****************************************************************************
static WORD GetOrderOfSameServiceWithIDsAndRFCH(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, BOOLEAN bCheckTsID, U8 u8RFChannelNumber)
{
    WORD wPosition;
    WORD wOrder;
    WORD cIDIndex;
    WORD wProgramCount;
    BYTE cCountOfSameService;
    WORD wRet;

#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    cCountOfSameService = 0;

    wRet = INVALID_ORDER;

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        //if( wService_ID != m_astDTVProgramIndexTable[wOrder].wService_ID )
        if( wService_ID != pstProgramIndexTable[wOrder].wService_ID )
        {
            continue;
        }

        //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;

        //printf(" cIDIndex %d channel mum %d\n", cIDIndex, pMuxTable[cIDIndex].cRFChannelNumber);
        // if check ts id flag is 1, then check ts id -- we may not check ts id if it is dvb://xxx..xxx in MHEG 1.0.6 spec
        if( (!bCheckTsID || (wTransportStream_ID == pMuxTable[cIDIndex].wTransportStream_ID)) &&
            (wOriginalNetwork_ID == pMuxTable[cIDIndex].wOriginalNetwork_ID) &&
            (pMuxTable[cIDIndex].cRFChannelNumber != u8RFChannelNumber))
        {
            cCountOfSameService++;

            if( cOrdinal == cCountOfSameService )
            {
                wRet = wOrder;
                break;

            }
        }
    }

    return wRet;
}
//****************************************************************************
/// Get Order Of Same Service With PCN
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @param wService_ID \b IN: Service ID
/// @return WORD: order
//****************************************************************************

U16 GetOrderOfSameServiceWithPCN_ServiceType(WORD cRFChannelNumber, WORD wService_ID, MEMBER_SERVICETYPE bServiceType)
{
    WORD wPosition;
    WORD wOrder;
    WORD cIDIndex;
    WORD wProgramCount;
    WORD wRet = INVALID_ORDER;

#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
  #endif
#endif

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    wRet = INVALID_ORDER;
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize) // If Order valid?
        {
            continue;
        }

    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            if( wService_ID != m_astS2ProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }
            cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
            if( cRFChannelNumber == cIDIndex)
            {
                wRet = wOrder;
                goto exit1;
            }
        }
        else
    #endif
        {
            if( wService_ID != pstProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }

            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if( cIDIndex >= u16IDTableArraySize) // If ID Index valid?
            {
                continue;
            }

        /*
        #if (ENABLE_T_C_COMBO)
            if ((IsDVBCInUse() &&(cRFChannelNumber == cIDIndex)) ||
                (!IsDVBCInUse() &&( cRFChannelNumber == pMuxTable[cIDIndex].cRFChannelNumber )))
        #elif ENABLE_DVBC
            if (cRFChannelNumber == cIDIndex)
        #else
            if( cRFChannelNumber == pMuxTable[cIDIndex].cRFChannelNumber )
        #endif
        */
            if( cRFChannelNumber == msAPI_DtvSys_Get_PCN_ByOrder(eCurDbSel, wOrder ) )
            {
                wRet = wOrder;
                break;
            }
        }
    }

    return wRet;
}

static WORD GetOrderOfSameServiceWithPCN(WORD cRFChannelNumber, WORD wService_ID)
//static WORD GetOrderOfSameServiceWithPCN(BYTE cRFChannelNumber, WORD wService_ID)
{
    WORD wRet;


    wRet = GetOrderOfSameServiceWithPCN_ServiceType(cRFChannelNumber, wService_ID, E_SERVICETYPE_DTV);
    if( wRet != INVALID_ORDER )
        return wRet;

    wRet = GetOrderOfSameServiceWithPCN_ServiceType(cRFChannelNumber, wService_ID, E_SERVICETYPE_RADIO);
    if( wRet != INVALID_ORDER )
        return wRet;

    wRet = GetOrderOfSameServiceWithPCN_ServiceType(cRFChannelNumber, wService_ID, E_SERVICETYPE_DATA);

    return wRet;
}

//****************************************************************************
/// Get Program Count
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param eCountOption \b IN: Count Option
/// - @see COUNT_PROGRAM_OPTION
/// @return WORD: count
//****************************************************************************
WORD msAPI_DTV_GetProgramCount(MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption)
{
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return 0;
    }

#if(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    return msAPI_DtvDB_Get_ProgramCount(
            msAPI_DTV_Comm_Get_DBSel(),
            ConvertServiceTypeToPosition(bServiceType), eCountOption);
#else

 #if ENABLE_S2
    if ( IsS2InUse() )
    {
        return m_awS2ProgramCount[ConvertServiceTypeToPosition(bServiceType)][eCountOption];
    }
 #endif

  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
        return m_awDVBCProgramCount[ConvertServiceTypeToPosition(bServiceType)][eCountOption];
    else
  #endif
        return m_awProgramCount[ConvertServiceTypeToPosition(bServiceType)][eCountOption];

#endif
}

//****************************************************************************
/// Update Program Count
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
//****************************************************************************
//void UpdateProgramCount(MEMBER_SERVICETYPE bServiceType)
void UpdateProgramCount_DBSel(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType)
{
    U8 u8ServiceIdx = ConvertServiceTypeToPosition(bServiceType);
    U8 u8CountOptionIdx;
    U16 u16ProgCount;

    for( u8CountOptionIdx = 0; u8CountOptionIdx < MAX_COUNT_PROGRAM_OPTION; u8CountOptionIdx += 1 )
    {
        u16ProgCount = CountProgram_DBSel(eDtvDbSel, bServiceType, (COUNT_PROGRAM_OPTION)u8CountOptionIdx);
        msAPI_DtvDB_Set_ProgramCount(eDtvDbSel, u8ServiceIdx, u8CountOptionIdx, u16ProgCount);
    }
}

//****************************************************************************
/// Count Program
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param eCountOption \b IN: Count Option
/// - @see COUNT_PROGRAM_OPTION
//****************************************************************************
//static WORD CountProgram(MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption)
WORD CountProgram_DBSel(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, COUNT_PROGRAM_OPTION eCountOption)
{
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndex;
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    WORD wOrder;
    WORD wProgramCount = 0;


    for(wOrder=0; wOrder < u16ProgramIndexTableArraySize; wOrder++)
    {
        pstProgramIndex = &(pstProgramIndexTable[wOrder]);
        if( bServiceType == pstProgramIndex->bServiceType )
        {
            if( eCountOption == EXCLUDE_NOT_VISIBLE_AND_DELETED )
            {
                if( (FALSE == pstProgramIndex->bVisibleServiceFlag) ||
                    (TRUE == pstProgramIndex->bIsDelete) )
                {
                    continue;
                }
            }
            else if( eCountOption == INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED )
            {
                if( TRUE == pstProgramIndex->bIsDelete )
                {
                    continue;
                }
            }

            wProgramCount++;
        }
        else
        {
            continue;
        }
    }

    if( wProgramCount >= u16ProgramIndexTableArraySize )
    {
        return u16ProgramIndexTableArraySize;
    }

    return wProgramCount;
}

//****************************************************************************
/// Save Current Service Type
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @return BOOLEAN: Function execution result
//****************************************************************************
// Refine Status: 20150714 Done
//static BOOLEAN SaveCurrentServiceType(MEMBER_SERVICETYPE bServiceType)
static BOOLEAN SaveCurrentServiceType_DBSel(TypDtvDbSel eDbSel,MEMBER_SERVICETYPE bServiceType)
{
    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

#if (ENABLE_API_DTV_SYSTEM_2015) // Use new method
    return msAPI_DtvDB_Set_CurServiceType( eDbSel, bServiceType );

#else

    eDbSel=eDbSel;

  #if(ENABLE_S2)
    //if(IsS2InUse())
    if( eDbSel == E_DTV_DB_SEL_DVBS )
    {
        //return SetNVRAM( S2_BASEADDRESS_PR_CURRENT_SERVICETYPE, (BYTE *)&bServiceType, sizeof(bServiceType) );
        stGenSetting.stDvbsSetting.eCurServiceType = bServiceType;
    }
    else
  #endif
    {
        stGenSetting.stTvSetting.eCurrentServiceType = bServiceType;
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Load Current Service Type
/// @return MEMBER_SERVICETYPE:
/// - @see MEMBER_SERVICETYPE
//****************************************************************************
// Refine Status: 20150714 Done
//static MEMBER_SERVICETYPE LoadCurrentServiceType(void)
static MEMBER_SERVICETYPE LoadCurrentServiceType_DBSel(TypDtvDbSel eDbSel)
{
#if(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    MEMBER_SERVICETYPE eServiceType = msAPI_DtvDB_Get_CurServiceType(eDbSel);

    if( FALSE == IsServiceTypeValid(eServiceType) )
    {
        eServiceType = DEFAULT_CURRENT_SERVICETYPE;
        SaveCurrentServiceType_DBSel(eDbSel, eServiceType);
    }

    return eServiceType;

#else
    MEMBER_SERVICETYPE bServiceType = E_SERVICETYPE_DTV;


  #if(ENABLE_S2)
    //if(IsS2InUse())
    if( eDbSel == E_DTV_DB_SEL_DVBS )
    {
        //GetNVRAM( S2_BASEADDRESS_PR_CURRENT_SERVICETYPE, (BYTE *)&bServiceType, sizeof(bServiceType));
        bServiceType = stGenSetting.stDvbsSetting.eCurServiceType;
    }
    else
  #endif
    {
        bServiceType = stGenSetting.stTvSetting.eCurrentServiceType;
    }

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        bServiceType = DEFAULT_CURRENT_SERVICETYPE;
        //SaveCurrentServiceType(bServiceType);
        SaveCurrentServiceType_DBSel(eDbSel, bServiceType);
    }

    return bServiceType;
#endif
}

//****************************************************************************
/// Save Current Order Of TV
/// @param wOrder \b IN: Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
// Refine Status: 20150715 Done
//static BOOLEAN SaveCurrentOrderOfTV(WORD wOrder)
BOOLEAN SaveCurrentOrderOfTV_DBSel(TypDtvDbSel eDbSel, WORD wOrder)
{
    //PRINT_CURRENT_LINE();
    //printf("SaveCurrentOrderOfTV_DBSel(eDbSel=%u, wOrder=%u)\n", eDbSel, wOrder);

#if (ENABLE_API_DTV_SYSTEM_2015)
    return msAPI_DtvDB_Set_CurOrderOfTV( eDbSel, wOrder);
#else

    eDbSel=eDbSel;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wOrder )
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if( MAX_DTVPROGRAM <= wOrder )
        {
            return FALSE;
        }
    }

#if(ENABLE_S2)
    if(IsS2TVInUse())
    {
        //return SetNVRAM(S2_BASEADDRESS_PR_CURRENTORDER_TV, (BYTE *)&wOrder, sizeof(wOrder));
        stGenSetting.stDvbsSetting.u16CurDtvOrder = wOrder;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.u16DTVRFChannelOrder = wOrder;
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Load Current Order Of TV
/// @return WORD: order
//****************************************************************************
//static WORD LoadCurrentOrderOfTV(void)
static WORD LoadCurrentOrderOfTV_DBSel(TypDtvDbSel eDbSel)
{
    WORD wOrder=0;
    WORD wMaxTVOrder;


#if(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    wOrder = msAPI_DtvDB_Get_CurOrderOfTV(eDbSel);
#else
  #if(ENABLE_S2)
    if(IsS2InUse())
    {
        //GetNVRAM(S2_BASEADDRESS_PR_CURRENTORDER_TV, (BYTE *)&wOrder, sizeof(wOrder));
        wOrder = stGenSetting.stDvbsSetting.u16CurDtvOrder;
    }
    else
  #endif
    {
        wOrder = stGenSetting.stTvSetting.u16DTVRFChannelOrder;
    }
#endif

    // Check if Order valid?

    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
    #if(ENABLE_API_DTV_SYSTEM_2015) // Use new method
        //U16 u16PRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
        U16 u16PRIndex = msAPI_DtvDB_Get_ProgramIndexTable(eDbSel)[wOrder].wPRIndex;
        if(FALSE == IsProgramEntityActive_DBSel(eDbSel, u16PRIndex))
        {
           wOrder = DEFAULT_CURRENT_ORDER_TV;
           SaveCurrentOrderOfTV(wOrder);
        }
    #else
        if(FALSE == IsProgramEntityActive(m_astDTVProgramIndexTable[wOrder].wPRIndex))
        {
           wOrder = DEFAULT_CURRENT_ORDER_TV;
           SaveCurrentOrderOfTV(wOrder);
        }
    #endif
        return wOrder;
    }

#if(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    wMaxTVOrder = msAPI_DtvDB_Get_ProgramCount(eDbSel, E_CM_SERVICE_POS_DTV, INCLUDE_ALL) - 1;
#else
 #if(ENABLE_S2)
    if( IsS2InUse() )
    {
        wMaxTVOrder = m_awS2ProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL]-1;
    }
    else
 #endif
    {
        wMaxTVOrder = m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL]-1;
    }
#endif

    if( wMaxTVOrder < wOrder )
    {
        wOrder = DEFAULT_CURRENT_ORDER_TV;
        SaveCurrentOrderOfTV_DBSel(eDbSel, wOrder);
    }

    return wOrder;
}

//****************************************************************************
/// Save Current Order Of Radio
/// @param wOrder \b IN: Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
//static BOOLEAN SaveCurrentOrderOfRadio(WORD wOrder)
BOOLEAN SaveCurrentOrderOfRadio_DBSel(TypDtvDbSel eDbSel, WORD wOrder)
{
#if(ENABLE_API_DTV_SYSTEM_2015)  // Use new method
    return msAPI_DtvDB_Set_CurOrderOfRadio( eDbSel, wOrder);
#else

    eDbSel=eDbSel;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wOrder )
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if( MAX_DTVPROGRAM <= wOrder )
        {
            return FALSE;
        }
    }

#if(ENABLE_S2)
    if( IsS2TVInUse() )
    {
        //return SetNVRAM(S2_BASEADDRESS_PR_CURRENTORDER_RADIO, (BYTE *)&wOrder, sizeof(wOrder));
        stGenSetting.stDvbsSetting.u16CurDtvRadioOrder = wOrder;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.u16RADIORFChannelOrder = wOrder;
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Load Current Order Of Radio
/// @return WORD: order
//****************************************************************************
//static WORD LoadCurrentOrderOfRadio(void)
static WORD LoadCurrentOrderOfRadio_DBSel(TypDtvDbSel eDtvDbSel)
{
    WORD wOrder=0;
    WORD wMaxRadioOrder, wMinRadioOrder;


    wOrder = msAPI_DtvDB_Get_CurOrderOfRadio(eDtvDbSel);

    // Check Program Index
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
    #if 1//(ENABLE_API_DTV_SYSTEM_2015)
        if( wOrder >= msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel) )
        {
            wOrder = DEFAULT_CURRENT_ORDER_RADIO(eDtvDbSel);
        }

        U16 u16PRIndex = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel)[wOrder].wPRIndex;
        if( FALSE == IsProgramEntityActive_DBSel(eDtvDbSel, u16PRIndex) )
        {
           //wOrder = DEFAULT_CURRENT_ORDER_TV; //?
           wOrder = DEFAULT_CURRENT_ORDER_RADIO(eDtvDbSel);
           SaveCurrentOrderOfRadio_DBSel(eDtvDbSel, wOrder);
        }
    #else
        if(FALSE == IsProgramEntityActive(m_astDTVProgramIndexTable[wOrder].wPRIndex))
        {
           wOrder = DEFAULT_CURRENT_ORDER_RADIO;
           SaveCurrentOrderOfRadio_DBSel(eDtvDbSel, wOrder);
        }
    #endif
        return wOrder;
    }


#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    U16 u16ProgramCount_RadioAll = msAPI_DtvDB_Get_ProgramCount(eDtvDbSel, E_CM_SERVICE_POS_RADIO,INCLUDE_ALL);
    U16 u16ProgramCount_DataAll = msAPI_DtvDB_Get_ProgramCount(eDtvDbSel, E_CM_SERVICE_POS_DATA,INCLUDE_ALL);

    wMaxRadioOrder = u16ProgramIndexTableArraySize
                    - u16ProgramCount_DataAll - 1;

    if( u16ProgramCount_RadioAll )
    {
        wMinRadioOrder = u16ProgramIndexTableArraySize
                            - u16ProgramCount_DataAll
                            - u16ProgramCount_RadioAll;
    }
    else
    {
        wMinRadioOrder = wMaxRadioOrder;
    }

#else

  #if(ENABLE_S2)
    if(IsS2InUse())
    {
        wMaxRadioOrder = MAX_DTV_S2_PROGRAM - m_awS2ProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
        wMinRadioOrder = ((m_awS2ProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL]) ? \
        (MAX_DTV_S2_PROGRAM - m_awS2ProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-
        m_awS2ProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL]) : wMaxRadioOrder);
    }
    else
  #endif
    {
        wMaxRadioOrder = MAX_DTVPROGRAM - m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-1;
        wMinRadioOrder = ((m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL]) ? \
            (MAX_DTVPROGRAM - m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]-
            m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL]) : wMaxRadioOrder);
    }
#endif


    if( (wMinRadioOrder > wOrder) || (wMaxRadioOrder < wOrder))
    {
        wOrder = wMaxRadioOrder;//DEFAULT_CURRENT_ORDER_RADIO;
        SaveCurrentOrderOfRadio_DBSel(eDtvDbSel, wOrder);
    }

    return wOrder;
}
//****************************************************************************
/// Save Current Order Of Data
/// @param wOrder \b IN: Order
/// @return BOOLEAN: Function execution result
//****************************************************************************
//static BOOLEAN SaveCurrentOrderOfData(WORD wOrder)
BOOLEAN SaveCurrentOrderOfData_DBSel(TypDtvDbSel eDbSel, WORD wOrder)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    return msAPI_DtvDB_Set_CurOrderOfData(eDbSel, wOrder);

#else

    eDbSel=eDbSel;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        if( MAX_DTV_S2_PROGRAM <= wOrder )
        {
            return FALSE;
        }
    }
    else
#endif
    {
        if( MAX_DTVPROGRAM <= wOrder )
        {
            return FALSE;
        }
    }

#if(ENABLE_S2)
    if(IsS2TVInUse())
    {
        //return SetNVRAM(S2_BASEADDRESS_PR_CURRENTORDER_DATA, (BYTE *)&wOrder, sizeof(wOrder));
        stGenSetting.stDvbsSetting.u16CurDtvDataOrder = wOrder;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.u16DATARFChannelOrder = wOrder;
    }

    return TRUE;
#endif
}

//****************************************************************************
/// Load Current Order Of Data
/// @return WORD: order
//****************************************************************************
//static WORD LoadCurrentOrderOfData(void)
static WORD LoadCurrentOrderOfData_DBSel(TypDtvDbSel eDtvDbSel)
{
    WORD wOrder=0;
    WORD wMaxDataOrder, wMinDataOrder;


#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    wOrder = msAPI_DtvDB_Get_CurOrderOfData(eDtvDbSel);
#else

 #if(ENABLE_S2)
    if(IsS2InUse())
    {
        //GetNVRAM(S2_BASEADDRESS_PR_CURRENTORDER_DATA, (BYTE *)&wOrder, sizeof(wOrder));
        wOrder = stGenSetting.stDvbsSetting.u16CurDtvDataOrder;
    }
    else
 #endif
    {
        wOrder = stGenSetting.stTvSetting.u16DATARFChannelOrder;
    }
#endif


    // Check Program Index // Why??
    if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
    {
    #if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
        if( wOrder >= msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel) )
        {
            wOrder = DEFAULT_CURRENT_ORDER_DATA(eDtvDbSel);
        }

        U16 u16PRIndex = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel)[wOrder].wPRIndex;
        if( FALSE == IsProgramEntityActive_DBSel(eDtvDbSel, u16PRIndex) )
        {
           //wOrder = DEFAULT_CURRENT_ORDER_TV; //??
           wOrder = DEFAULT_CURRENT_ORDER_DATA(eDtvDbSel);
           SaveCurrentOrderOfData_DBSel(eDtvDbSel, wOrder);
        }

    #else
        if( FALSE == IsProgramEntityActive(m_astDTVProgramIndexTable[wOrder].wPRIndex) )
        {
           //wOrder = DEFAULT_CURRENT_ORDER_TV;
           wOrder = DEFAULT_CURRENT_ORDER_DATA;
           SaveCurrentOrderOfData(wOrder);
        }
    #endif

        return wOrder;
    }


#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    U16 u16ProgramCount_DataAll = msAPI_DtvDB_Get_ProgramCount(eDtvDbSel, E_CM_SERVICE_POS_DATA,INCLUDE_ALL);

    wMaxDataOrder = u16ProgramIndexTableArraySize - 1;

    if( u16ProgramCount_DataAll )
        wMinDataOrder = u16ProgramIndexTableArraySize - u16ProgramCount_DataAll;
    else
        wMinDataOrder = wMaxDataOrder;

#else

 #if(ENABLE_S2)
    if(IsS2InUse())
    {
        wMaxDataOrder = MAX_DTV_S2_PROGRAM - 1;
        wMinDataOrder = ((m_awS2ProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]) ?
        (MAX_DTV_S2_PROGRAM - m_awS2ProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]) :
        wMaxDataOrder);
    }
    else
 #endif
    {
        wMaxDataOrder = MAX_DTVPROGRAM - 1;
        wMinDataOrder = ((m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]) ?
                        (MAX_DTVPROGRAM - m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL]) :
                        wMaxDataOrder);
    }
#endif


    if( (wMinDataOrder > wOrder) || (wMaxDataOrder < wOrder))
    {
        wOrder = wMaxDataOrder;//DEFAULT_CURRENT_ORDER_DATA;
        SaveCurrentOrderOfData_DBSel(eDtvDbSel, wOrder);
    }

    return wOrder;
}

#if 0
static void RemoveInactiveID(void)
{
    BYTE    cIDIndex;

    for(cIDIndex=0; cIDIndex < MAX_MUX_NUMBER; cIDIndex++)
    {
        if(FALSE == IsIDEntityActive(cIDIndex))
        {
            FillProgramIDWithDefault(&_astDTVProgramIDTable[cIDIndex]);
            SetIDTable(cIDIndex,(BYTE *)&_astDTVProgramIDTable[cIDIndex],E_DATA_ID_TABLE);
            ActiveIDEntity(cIDIndex,FALSE);
        }
    }
}
#endif

// Refine Status: Done
//static void ResetIDtable(void)
static void ResetIDtable_DBSel(TypDtvDbSel eDtvDbSel)
{
    WORD wIDIndex;
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    // ID Table Map
    BYTE* pIDtableMap = msAPI_DtvDB_Get_ProgIdTableMap(eDtvDbSel);
    U16 u16IdTableMapArraySize = msAPI_DtvDB_Get_ProgIdTableMapArraySize(eDtvDbSel);
    //U32 u16IdTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgIdTableMapRamDiskAddr(eDtvDbSel);

    // ID Table
    DTVPROGRAMID_M * pProgramIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16ProgIdTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);

    // NetWork Table
    DTVNETWORK* pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);

#else
    BYTE* pIDtableMap=m_acDTVIDtableMap;
    DTVPROGRAMID_M *pProgramIDTable=_astDTVProgramIDTable;

    eDtvDbSel=eDtvDbSel;

 #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        pIDtableMap=m_acDTVIDtableMap_DVBC;
        pProgramIDTable=_astDTVCProgramIDTable;
    }
 #endif

#endif


    // Reset all Program ID table...
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    for(wIDIndex=0; wIDIndex < u16ProgIdTableArraySize; wIDIndex++)
#else
    for(wIDIndex=0; wIDIndex < msAPI_CM_GetMuxMaxNumber(); wIDIndex++)
#endif
    {
        FillProgramIDWithDefault(&pProgramIDTable[wIDIndex]);
        SetIDTable(wIDIndex, (BYTE *)&pProgramIDTable[wIDIndex], E_DATA_ID_TABLE);
    }

    // Reset all Network data
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    for(wIDIndex=0; wIDIndex < u16NetWorkTableArraySize; wIDIndex++)
    {
        FillNetworkWithDefault( &(pstNetWorkTable[wIDIndex]) );
        SetIDTable(wIDIndex, (BYTE *)&(pstNetWorkTable[wIDIndex]), E_DATA_NETWORK);
    }
#else
    for(wIDIndex=0; wIDIndex < MAX_NETWOEK_NUMBER; wIDIndex++)
    {
        FillNetworkWithDefault(&_astDTVNetwork[wIDIndex]);
        SetIDTable(wIDIndex, (BYTE *)&_astDTVNetwork[wIDIndex], E_DATA_NETWORK);
    }
#endif


    // Clear all ID table map ...
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    memset(pIDtableMap, 0, sizeof(U8)*u16IdTableMapArraySize );
    //SetNVRAM(u16IdTableMapRamDiskAddr, pIDtableMap, sizeof(U8)*u16IdTableMapArraySize );
    msAPI_DtvDB_Save_IDTableMap(eDtvDbSel, pIDtableMap, u16IdTableMapArraySize );
#else
  #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        memset(pIDtableMap,0,sizeof(m_acDTVIDtableMap_DVBC));
        SetNVRAM(BASEADDRESS_PR_DTV_C_IDTABLEMAP, pIDtableMap, sizeof(m_acDTVIDtableMap_DVBC));
    }
    else
  #endif
    {
        memset(pIDtableMap,0,sizeof(m_acDTVIDtableMap));
        SetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP, pIDtableMap, sizeof(m_acDTVIDtableMap));
    }
#endif

#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
  #if( ENABLE_S2 )
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {   // Restore to default value
        S2LoadIDTabla();
    }
  #endif
#endif
}

BOOLEAN msAPI_CM_UpdateNetworkCDSD(U8 u8PhNum,U32 u32Freq,U32 u32Symb,U8 u8Modu)
{
    if( u32Symb > 0xFFFF)
    {
        PRINT_CURRENT_LINE();
        printf("\nError: u32Symb=%u is too big!\n", u32Symb);
        return FALSE;
    }


    bool bresult= FALSE;
    DTVPROGRAMID_M stDPI;
    memset(&stDPI, 0, sizeof(DTVPROGRAMID_M));
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition;
    BYTE cRFChannelNumber;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    cRFChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType,wCurrentPosition);

    if(msAPI_CM_GetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE))
    {
        if( (stDPI.u32Frequency != u32Freq)
          //||(stDPI.u32SymbRate != u32Symb)
          ||(stDPI.u16SymbolRate != u32Symb)
          ||(stDPI.QamMode != u8Modu)
          )
        {
            if(msAPI_CM_Get_RFChannelIndex(cRFChannelNumber) == u8PhNum)
            {
                MApp_ChannelChange_DisableChannel(TRUE, MAIN_WINDOW); //the cur program need to show black when change the tuner
            }

            stDPI.u32Frequency = u32Freq;
            //stDPI.u32SymbRate= u32Symb;
            stDPI.u16SymbolRate= u32Symb;
            stDPI.QamMode= u8Modu;
            msAPI_CM_SetIDTable(u8PhNum,(BYTE *)&stDPI,E_DATA_ID_TABLE);

            MApp_ChannelChange_EnableChannel(MAIN_WINDOW); // change the tuner

            bresult = TRUE;
        }
    }
    return bresult;
}

// Copy ID Tabel/ID Table Map/NetWork  from RamDisk to Variable
static void UpdateIDInfo(TypDtvDbSel eDtvDbSel)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method

    // Load ID Table Map from RamDisk to Variable
    U8* pu8IDTableMap = msAPI_DtvDB_Get_ProgIdTableMap(eDtvDbSel);
    U16 u16ArraySize = msAPI_DtvDB_Get_ProgIdTableMapArraySize(eDtvDbSel);
    msAPI_DtvDB_Load_IDTableMap(eDtvDbSel, pu8IDTableMap, u16ArraySize );

    // Load ID Table  from RamDisk to Variable
    DTVPROGRAMID_M *pstIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    u16ArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    msAPI_DtvDB_Load_IDTable(eDtvDbSel, pstIDTable, u16ArraySize );

    // Load NetWork Table  from RamDisk to Variable
    DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    u16ArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    msAPI_DtvDB_Load_NetWorkTable(eDtvDbSel, pstNetWorkTable, u16ArraySize );

#else
    eDtvDbSel=eDtvDbSel; // Unused warning

    U16 u16Loop;
    BYTE* pIDtableMap=m_acDTVIDtableMap;
    DTVPROGRAMID_M *pProgramIDTable=_astDTVProgramIDTable;

 #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        pIDtableMap=m_acDTVIDtableMap_DVBC;
        pProgramIDTable=_astDTVCProgramIDTable;
    }
 #endif

    // Load ID Table Map from RamDisk to Variable
 #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        GetNVRAM(BASEADDRESS_PR_DTV_C_IDTABLEMAP, pIDtableMap, sizeof(m_acDTVIDtableMap_DVBC));
    }
    else
 #endif
    {
        GetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP, pIDtableMap, sizeof(m_acDTVIDtableMap));
    }

    // Load ID Table  from RamDisk to Variable
    for (u16Loop=0; u16Loop < msAPI_CM_GetMuxMaxNumber(); u16Loop++)
    {
/*
        if(u8Loop < (MAX_DTVIDTABLE_MAP))
        {
            m_acDTVIDtableMap[u8Loop] = 0x00;
        }
        GetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP, m_acDTVIDtableMap, sizeof(m_acDTVIDtableMap));
*/
        //FillProgramIDWithDefault(&_astDTVProgramIDTable[u8Loop]);
        GetIDTable(u16Loop,(BYTE *)&pProgramIDTable[u16Loop],E_DATA_ID_TABLE);
    }

    // Load NetWork Table  from RamDisk to Variable
    for (u16Loop=0; u16Loop < MAX_NETWOEK_NUMBER; u16Loop++)
    {
        //FillNetworkWithDefault(&_astDTVNetwork[u16Loop]);
        GetIDTable(u16Loop,(BYTE *)&_astDTVNetwork[u16Loop],E_DATA_NETWORK);
    }
#endif
}

static void _RestInvalidMUXAndNetwork(void)
{
    //U16 i;
    //U16 j;
#if 0//ENABLE_S2
    U16 maxtpnum,maxprogramnum;
#endif

#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif

    DTVPROGRAMID_M* pMuxInfo = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);//_astDTVProgramIDTable;

#if 0//ENABLE_S2
    if (IsS2InUse())
    {
        //pMuxInfo=_astS2ProgramIDTable;
        maxtpnum=MAX_DTV_S2_MUX_NUMBER;
        maxprogramnum= MAX_DTV_S2_PROGRAM;
    }
    else
    {
        maxtpnum=MAX_MUX_NUMBER;
        maxprogramnum= MAX_DTVPROGRAM;
    }
#endif

    U16 u16IDIndex;
    U16 u16Order;

    for (u16IDIndex = 0; u16IDIndex < u16IDTableArraySize; u16IDIndex ++) // For each ID Table
    {
         if( (pMuxInfo[u16IDIndex].cRFChannelNumber==INVALID_PHYSICAL_CHANNEL_NUMBER)
        #if ENABLE_DVBC
            && (pMuxInfo[u16IDIndex].u32Frequency==INVALID_FREQUENCY)
        #endif
            )
        {
            continue;
        }

        // Find someone use this IDTable...
        //for(j=0;j<MAX_DTVPROGRAM;j++)
        for( u16Order = 0; u16Order < u16ProgramIndexTableArraySize; u16Order++)
        {
        #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                if(m_astS2ProgramIndexTable[j].cIDIndex == i)
                {
                    break;
                }
            }
            else
        #endif
            {
                if( pstProgramIndexTable[u16Order].cIDIndex == u16IDIndex )
                {
                    break;
                }
            }
        }

        //if( j >= MAX_DTVPROGRAM )
        if( u16Order >= u16ProgramIndexTableArraySize ) // If nobody use this ID Tab, reset it
        {
            FillProgramIDWithDefault( &(pMuxInfo[u16IDIndex]) );
            SetIDTable(u16IDIndex, (BYTE *)&pMuxInfo[u16IDIndex], E_DATA_ID_TABLE);
            ActiveIDEntity(u16IDIndex, FALSE);
        }
    }

    U16 u16NetWorkIndex;
    DTVNETWORK* pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eCurDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eCurDbSel);
    for (u16NetWorkIndex=0; u16NetWorkIndex < u16NetWorkTableArraySize; u16NetWorkIndex++)
    {
        if(pstNetWorkTable[u16NetWorkIndex].wNetwork_ID == INVALID_NID)
        {
            continue;
        }

        for(u16IDIndex=0; u16IDIndex < u16IDTableArraySize; u16IDIndex++) // Find someone use this NetWorkIndex
        {
            if(pMuxInfo[u16IDIndex].cNetWorkIndex == u16NetWorkIndex)
            {
                break; // ==> Someone use this networkIndex
            }
        }

        if( u16IDIndex >= u16IDTableArraySize ) // Mean nobody use this NetWorkIndex, so reset it
        {
            FillNetworkWithDefault( &(pstNetWorkTable[u16NetWorkIndex]) );
            SetIDTable(u16NetWorkIndex, (BYTE *)&pstNetWorkTable[u16NetWorkIndex], E_DATA_NETWORK);
        }
    }
}

E_CM_SERVICE_POS ConvertServiceTypeToPosition(MEMBER_SERVICETYPE eServiceType)
{
    switch(eServiceType)
    {
        case E_SERVICETYPE_DTV: return E_CM_SERVICE_POS_DTV;
        case E_SERVICETYPE_RADIO: return E_CM_SERVICE_POS_RADIO;
        case E_SERVICETYPE_DATA: return E_CM_SERVICE_POS_DATA;
        default: return E_CM_SERVICE_POS_DTV;
    }
}

#if 0
//****************************************************************************
/// Reset Unsupported Iso639Code
//****************************************************************************
void msAPI_CM_ResetUnsupportedIso639Code(void)
{
    U8 temp=0;

    SetNVRAM(BASEADDRESS_PR_UNSUPPORT_LANGCODE_COUNT, &temp, sizeof(temp));
}

//****************************************************************************
/// Load Unsupported Iso639Code By Index
/// @param pBuf \b IN: pointer to Buf for return
/// @param u8BufSize \b IN: Buffer Size
/// @param u8Index \b IN: Index
//****************************************************************************
void msAPI_CM_LoadUnsupportedIso639CodeByIndex(U8 *pBuf, U8 u8BufSize, U8 u8Index)
{
    if(u8Index >= (MAX_UNSUPPORTED_ISO639CODE_NUM + UNSUPPORT_ISO639CODE_BASE_INDEX))
    {
        return;
    }
    GetNVRAM(BASEADDRESS_PR_NSUPPORT_LANGCODE + (MAX_ISO639CODE_LENGTH * (u8Index - UNSUPPORT_ISO639CODE_BASE_INDEX) ), pBuf, u8BufSize);
}

//****************************************************************************
/// Load Unsupported Iso639Code By Index
/// @param pCode \b IN: Code
/// @return U8: Unsupport ISO639CODE index
//****************************************************************************
U8 msAPI_CM_SaveUnsupportedIso639Code(U8 *pCode)
{
    U8 u8CurSaveNum=0;
    U8 i,au8Code[MAX_ISO639CODE_LENGTH];

    memset(au8Code,0x00,MAX_ISO639CODE_LENGTH);
    GetNVRAM(BASEADDRESS_PR_UNSUPPORT_LANGCODE_COUNT, &u8CurSaveNum, sizeof(u8CurSaveNum));

    if(u8CurSaveNum <= MAX_UNSUPPORTED_ISO639CODE_NUM)
    {
        for(i = 0; i < u8CurSaveNum; i++)
        {
            msAPI_CM_LoadUnsupportedIso639CodeByIndex(au8Code, MAX_ISO639CODE_LENGTH, (i + UNSUPPORT_ISO639CODE_BASE_INDEX));
            if(!memcmp(pCode, au8Code, MAX_ISO639CODE_LENGTH))
            {
                return (i + UNSUPPORT_ISO639CODE_BASE_INDEX);
            }
        }
    }

    if(u8CurSaveNum < MAX_UNSUPPORTED_ISO639CODE_NUM)
    {
        SetNVRAM(BASEADDRESS_PR_NSUPPORT_LANGCODE + (MAX_ISO639CODE_LENGTH * u8CurSaveNum ), pCode, MAX_ISO639CODE_LENGTH);

        u8CurSaveNum++;
        SetNVRAM(BASEADDRESS_PR_UNSUPPORT_LANGCODE_COUNT, &u8CurSaveNum, sizeof(u8CurSaveNum));
        return (u8CurSaveNum + UNSUPPORT_ISO639CODE_BASE_INDEX - 1);
    }
    else
    {
        return (MAX_UNSUPPORTED_ISO639CODE_NUM + UNSUPPORT_ISO639CODE_BASE_INDEX);
    }
}
#endif

//****************************************************************************
/// Reset Audio Valid Information
//****************************************************************************
void msAPI_CM_Reset_AudioValidIndex(void)
{
    _u16ValidAudioIndex=0xFFFF;
}

//****************************************************************************
/// Get current audio valid index
/// @return BYTE: valid index
//****************************************************************************
U16 msAPI_CM_Get_AudioValidIndex(void)
{
    return _u16ValidAudioIndex;
}

//****************************************************************************
/// Update Audio Valid Information
/// @param stValidAudioInfo \b IN: pointer to Valid Audio Information
/// -@see AUD_VALID_INFO
/// @return BOOLEAN:
/// - TRUE:  function done
/// - FALSE: NO
//****************************************************************************
BOOLEAN msAPI_CM_Update_AudioValidInfo(U16 u16AudioValidIndex)
{
    _u16ValidAudioIndex=u16AudioValidIndex;
    return TRUE;
}

//****************************************************************************
/// Get index of RF channel
/// @param bRFChannel \b IN: rf channel
/// @return BYTE: index
//****************************************************************************
WORD msAPI_CM_Get_RFChannelIndex(BYTE bRFChannel)
//BYTE msAPI_CM_Get_RFChannelIndex(BYTE bRFChannel)
{
#if(ENABLE_S2)
    if(IsS2InUse())
    {
        WORD j;
        for(j=0;j<MAX_DTV_S2_MUX_NUMBER;j++)
        {
            if(_astS2ProgramIDTable[j].cRFChannelNumber == bRFChannel)
            {
                return j;
            }
        }
        return MAX_DTV_S2_MUX_NUMBER;
    }
    else
#endif
    {
#if 1//ENABLE_T_C_COMBO
        U16 i;

    #if 1
        TypDtvDbSel eCurDbSel = CUR_DB_SEL();
        DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
        U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    #else
        DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
      #if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
        if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
      #endif
    #endif

    #if(ENABLE_DVBC)
        if( IsDVBCInUse() )
        {
      #if 1//(ENABLE_CI_PLUS)
            return bRFChannel;
      #else
            if (bRFChannel >= u16IDTableArraySize)
                return u16IDTableArraySize;
            else
                return bRFChannel;
      #endif
        }
    #endif

        // DVBT/DTMB
        for(i=0;i<u16IDTableArraySize;i++)
        {
            if(pMuxTable[i].cRFChannelNumber == bRFChannel)
            {
                return i;
            }
        }

        return u16IDTableArraySize;

#elif ENABLE_DVBC
#if (ENABLE_CI_PLUS)
        return bRFChannel;
#else
        if (bRFChannel>=msAPI_CM_GetMuxMaxNumber())
            return msAPI_CM_GetMuxMaxNumber();
        else
            return bRFChannel;
#endif
#else
        U16 i;
        for(i=0;i<msAPI_CM_GetMuxMaxNumber();i++)
        {
            if(_astDTVProgramIDTable[i].cRFChannelNumber == bRFChannel)
            {
                return i;
            }
        }

        return msAPI_CM_GetMuxMaxNumber();
#endif
    }
}

void msAPI_CM_SetAudioStreamValidIndex(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD wType, BYTE bISOLangIndex, U16 *pu16Index)
{
    AUD_INFO stAudInfo[MAX_AUD_LANG_NUM];
    WORD wOrder, wPRIndex;
    BYTE i;
    //BYTE cAudioStreamCount;

    memset(&stAudInfo,0,sizeof(stAudInfo));

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return;
    }

    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    }
    else
#endif
    {
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    }

    if( FALSE == GetProgramTable(wPRIndex, (BYTE *)stAudInfo, E_DATA_AUDIO_STREAM_INFO) )
    {
        *pu16Index = 0;
        return;
    }

    //cAudioStreamCount = 0;

    for(i=0; i < MAX_AUD_LANG_NUM; i++)
    {
        if( (TRUE == IsAudioPIDValid(stAudInfo[i].wAudPID))
          &&(wType == msAPI_CM_Get_AudStreamType_By_AudInfo( &(stAudInfo[i]) ) )
          &&(bISOLangIndex == stAudInfo[i].aISOLangInfo[0].bISOLangIndex)
          )
        {
            SETBIT(*pu16Index,i);
        }
    }

}

U16 msAPI_CM_GetPhysicalChannelNumberByID(WORD wONID, WORD wTSID)
{
#if 1 // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();

    U16 u16IDIndex = msAPI_DtvSys_Find_IDTab_By_TSId_ONId(eDtvDbSel, wTSID, wONID);
    U16 u16IDTabArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);

    if( u16IDIndex >= u16IDTabArraySize )
        return INVALID_PHYSICAL_CHANNEL_NUMBER;

    return msAPI_DtvSys_Get_PCN_ByIDIndex( eDtvDbSel, u16IDIndex);

#else
    U16 i;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        for(i=0;i<MAX_DTV_S2_MUX_NUMBER;i++)
        {
            if((_astS2ProgramIDTable[i].wOriginalNetwork_ID == wONID) && (_astS2ProgramIDTable[i].wTransportStream_ID== wTSID))
            {
                return _astS2ProgramIDTable[i].cRFChannelNumber;
            }
        }
    }
    else
#endif
    {
        DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())  pMuxTable=_astDTVCProgramIDTable;
    #endif

        for(i=0;i<msAPI_CM_GetMuxMaxNumber();i++)
        {
            if((pMuxTable[i].wOriginalNetwork_ID == wONID) && (pMuxTable[i].wTransportStream_ID== wTSID))
            {
            #if ENABLE_DVBC
                if( IsDVBCInUse() )
                {
                    return  i;
                }
                else
            #endif
                {
                    return pMuxTable[i].cRFChannelNumber;
                }
            }
        }
    }

    return INVALID_PHYSICAL_CHANNEL_NUMBER;
#endif
}

#if ENABLE_SDT_OTHER_MONITOR
static BOOLEAN _msAPI_CM_GetCEllID(WORD wTS_ID, WORD wON_ID, WORD *wCell_ID, BOOLEAN *bOverOneCell)
{
    WORD wIDIdex;
    WORD wCellID=DEFAULT_CELLID;
    WORD wPreCell=DEFAULT_CELLID;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    *bOverOneCell=FALSE;

    *wCell_ID = wCellID;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        for(wIDIdex=0; wIDIdex < MAX_DTV_S2_MUX_NUMBER; wIDIdex++)
        {
            if(wTS_ID == _astS2ProgramIDTable[wIDIdex].wTransportStream_ID && wON_ID == _astS2ProgramIDTable[wIDIdex].wOriginalNetwork_ID)
            {
                *wCell_ID = wCellID = _astS2ProgramIDTable[wIDIdex].wCellID;
                if(wPreCell && (wCellID!=wPreCell))
                {
                    *bOverOneCell=TRUE;
                    break;
                }
                else if(wPreCell==DEFAULT_CELLID)
                {
                    wPreCell=wCellID;
                }
            }
        }
    }
    else
#endif
    {
    for(wIDIdex=0; wIDIdex < u16IDTableArraySize; wIDIdex++)
    {
        if(wTS_ID == pMuxTable[wIDIdex].wTransportStream_ID && wON_ID == pMuxTable[wIDIdex].wOriginalNetwork_ID)
        {
            *wCell_ID = wCellID = pMuxTable[wIDIdex].wCellID;
            if(wPreCell && (wCellID!=wPreCell))
            {
                *bOverOneCell=TRUE;
                break;
            }
            else if(wPreCell==DEFAULT_CELLID)
            {
                wPreCell=wCellID;
            }
        }
    }
    }

    if(wCellID!=DEFAULT_CELLID)
    {
        return TRUE;
    }

    return FALSE;

}
BOOLEAN msAPI_CM_GetCEllID_WithID(WORD wTS_ID, WORD wON_ID, WORD *wCell_ID, BOOLEAN *bOverOneCell)
{
    *wCell_ID = DEFAULT_CELLID;
    if((_msAPI_CM_GetCEllID(wTS_ID, wON_ID, wCell_ID,bOverOneCell))==TRUE)
    {
        //printf("Get Cell ID %u\n",*wCell_ID);
    }
    if(*wCell_ID == DEFAULT_CELLID)
    {
        return FALSE;
    }
    return TRUE;
}

BOOLEAN msAPI_CM_Is_TSExist(WORD wONID, WORD wTSID, BYTE *pcRFChannelNumber)
{
#if 1// Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    DTVPROGRAMID_M * pstIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    U16 u16IDIndex = msAPI_DtvSys_Find_IDTab_By_TSId_ONId(eDtvDbSel, wTSID, wONID);

    if( FALSE == msAPI_DtvDB_Is_IDTableIndexValid(eDtvDbSel, u16IDIndex ) )
        return FALSE;

#if(ENABLE_S2)
    if( IsS2InUse() )
    {
        *pcRFChannelNumber = pstIDTable[u16IDIndex].cRFChannelNumber;
    }
    else
#endif
#if ENABLE_DVBC
    if( IsDVBCInUse() )
    {
        *pcRFChannelNumber = u16IDIndex;
    }
    else
#endif
    {
        *pcRFChannelNumber = pstIDTable[u16IDIndex].cRFChannelNumber;
    }

    return TRUE;

#else

    U16 i;

#if(ENABLE_S2)
    if(IsS2InUse())
    {
        for(i=0;i<MAX_DTV_S2_MUX_NUMBER;i++)
        {
            if((_astS2ProgramIDTable[i].wOriginalNetwork_ID == wONID) && (_astS2ProgramIDTable[i].wTransportStream_ID== wTSID))
            {
                *pcRFChannelNumber=_astS2ProgramIDTable[i].cRFChannelNumber;
                break;
            }
        }
        if(i>=MAX_DTV_S2_MUX_NUMBER)return FALSE;
            return TRUE;
    }
    else
#endif
    {
        DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif

        //printf("msAPI_CM_Is_TSExist ONID %u TSID %u\n",wONID,wTSID);
        for(i=0;i<msAPI_CM_GetMuxMaxNumber();i++)
        {
    //#if ENABLE_T_C_COMBO
        #if ENABLE_DVBC
            if(IsDVBCInUse())
            {
                if(pMuxTable[i].u32Frequency == INVALID_FREQUENCY)continue;
            }
            else
        #endif
            if(pMuxTable[i].cRFChannelNumber == INVALID_PHYSICAL_CHANNEL_NUMBER)
            {
                continue;
            }
//#elif ENABLE_DVBC
//            if(pMuxTable[i].u32Frequency == INVALID_FREQUENCY)continue;
//#else
//            if(pMuxTable[i].cRFChannelNumber == INVALID_PHYSICAL_CHANNEL_NUMBER)continue;
//#endif

            if((pMuxTable[i].wOriginalNetwork_ID == wONID) && (pMuxTable[i].wTransportStream_ID== wTSID))
            {
//#if ENABLE_T_C_COMBO
                *pcRFChannelNumber = IsDVBCInUse() ? i : pMuxTable[i].cRFChannelNumber;
//#elif ENABLE_DVBC
//                *pcRFChannelNumber =  i;
//#else
//                *pcRFChannelNumber=pMuxTable[i].cRFChannelNumber;
//#endif
                break;
            }
        }

        if(i>=msAPI_CM_GetMuxMaxNumber())
            return FALSE;

        return TRUE;
    }
#endif
}

BOOLEAN msAPI_CM_GetSameServiceInOtherMux(MEMBER_SERVICETYPE bServiceType, WORD wLCN, WORD wSID, WORD *pPosition)
{
    WORD wPosition;
    WORD wOrder1;
    WORD wProgramCount;


    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //DTVPROGRAMID_M * pstIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);

    for( wPosition = 0; wPosition < wProgramCount; wPosition++ )
    {
        wOrder1 = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder1 >= u16ProgramIndexTableArraySize )
            continue;

    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            if((m_astS2ProgramIndexTable[wOrder1].wLCN == wLCN)&&(wSID==m_astS2ProgramIndexTable[wOrder1].wService_ID))
            {
                *pPosition=wPosition;
                break;
            }
        }
        else
    #endif
        {
            //printf("find %u(%u) %u(%u)\n",m_astDTVProgramIndexTable[wOrder1].wLCN,wLCN,m_astDTVProgramIndexTable[wOrder1].wService_ID,wSID);
            if( (pstProgramIndexTable[wOrder1].wLCN == wLCN)
              &&(wSID==pstProgramIndexTable[wOrder1].wService_ID)
              )
            {
                //*pPosition = wPosition;
                break;
            }
        }
    }

    if( wPosition < wProgramCount )
    {
        *pPosition = wPosition;
        return TRUE;
    }

    return FALSE;
}
#endif

BOOLEAN msAPI_CM_IsServiceExistWithIDsAndLCN(WORD wOriginalNetwork_ID, WORD wService_ID,  WORD wLCN)
{
    WORD i;
    BOOLEAN eResult=FALSE;
    WORD cIDIndex;
    MEMBER_SERVICETYPE bServiceType;
    WORD wPosition,wProgramCount,wOrder;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    bServiceType=E_SERVICETYPE_DTV;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder > u16ProgramIndexTableArraySize)
            continue;

    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
            if(_astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
            {
                if(wService_ID == m_astS2ProgramIndexTable[wOrder].wService_ID)
                {
                    if(wLCN == m_astS2ProgramIndexTable[wOrder].wLCN)
                    {
                        //printf("got same lcn service\n");
                        eResult = TRUE;
                        break;
                    }
                }
            }
        }
        else
    #endif
        {
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if(pMuxTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
            {
                if(wService_ID == pstProgramIndexTable[wOrder].wService_ID)
                {
                    if(wLCN == pstProgramIndexTable[wOrder].wLCN)
                    {
                        //printf("got same lcn service\n");
                        eResult = TRUE;
                        break;
                    }
                }
            }
        }
        wPosition--;
    }

    bServiceType=E_SERVICETYPE_RADIO;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder > u16ProgramIndexTableArraySize)
            continue;


    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
            if(_astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
            {
                if(wService_ID == m_astS2ProgramIndexTable[wOrder].wService_ID)
                {
                    if(wLCN == m_astS2ProgramIndexTable[wOrder].wLCN)
                    {
                        //printf("got same lcn service\n");
                        eResult = TRUE;
                        break;
                    }
                }
            }
        }
        else
    #endif
        {
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if(pMuxTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
            {
                if(wService_ID == pstProgramIndexTable[wOrder].wService_ID)
                {
                    if(wLCN == pstProgramIndexTable[wOrder].wLCN)
                    {
                        //printf("got same lcn service\n");
                        eResult = TRUE;
                        break;
                    }
                }
            }
        }
        wPosition--;
    }

    bServiceType=E_SERVICETYPE_DATA;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder > u16ProgramIndexTableArraySize)
            continue;


    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            cIDIndex = m_astS2ProgramIndexTable[wOrder].cIDIndex;
            if(_astS2ProgramIDTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
            {
                if(wService_ID == m_astS2ProgramIndexTable[wOrder].wService_ID)
                {
                    if(wLCN == m_astS2ProgramIndexTable[wOrder].wLCN)
                    {
                        //printf("got same lcn service\n");
                        eResult = TRUE;
                        break;
                    }
                }
            }
        }
        else
    #endif
        {
            cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
            if(pMuxTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
            {
                if(wService_ID == pstProgramIndexTable[wOrder].wService_ID)
                {
                    if(wLCN == pstProgramIndexTable[wOrder].wLCN)
                    {
                        //printf("got same lcn service\n");
                        eResult = TRUE;
                        break;
                    }
                }
            }
        }
        wPosition--;
    }
    return eResult;
}

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
BOOLEAN msAPI_CM_RemoveMismatchedMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, BOOLEAN bRemove)
{
    WORD cIDIndex;
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD i;
    BYTE k;
    WORD wRemovedProgramCount=0;
    MEMBER_SERVICETYPE bServiceType;
    U32 u32GetTS=0;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkIndex;


    for(i=0;(i<cCountOfTS)&&(i<32);i++)
    {
        SETBIT(u32GetTS, i);
    }

    bServiceType=E_SERVICETYPE_DTV;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;

        cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
        if( cIDIndex >= u16IDTableArraySize )
            continue;

        u16NetWorkIndex = pMuxTable[cIDIndex].cNetWorkIndex;
        if( u16NetWorkIndex >= u16NetWorkTableArraySize )
            continue;

        if( wNID == pstNetWorkTable[u16NetWorkIndex].wNetwork_ID)
        {
            for(k=0;k<cCountOfTS;k++)
            {
                if(pMuxTable[cIDIndex].wTransportStream_ID == pwTS_ID[k])
                {
                    CLRBIT(u32GetTS,k);
                    break;
                }
            }
            if( cCountOfTS <= k )
            {
                if(bRemove)
                {
                    RemoveProgram(bServiceType, wPosition);
                }
                wRemovedProgramCount++;
            }
        }
        wPosition--;
    }

    bServiceType=E_SERVICETYPE_RADIO;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;

        cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
        if( cIDIndex >= u16IDTableArraySize )
            continue;

        u16NetWorkIndex = pMuxTable[cIDIndex].cNetWorkIndex;
        if( u16NetWorkIndex >= u16NetWorkTableArraySize )
            continue;

        if( wNID == pstNetWorkTable[u16NetWorkIndex].wNetwork_ID)
        {
            for(k=0;k<cCountOfTS;k++)
            {
                if(pMuxTable[cIDIndex].wTransportStream_ID == pwTS_ID[k])
                {
                    CLRBIT(u32GetTS,k);
                    break;
                }
            }
            if( cCountOfTS <= k)
            {
                if(bRemove)
                {
                    RemoveProgram(bServiceType, wPosition);
                }
                wRemovedProgramCount++;
            }
        }
        wPosition--;
    }

#if (NORDIG_FUNC) //for Nordig spec v2.0
    bServiceType=E_SERVICETYPE_DATA;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;

        cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
        if( cIDIndex >= u16IDTableArraySize )
            continue;

        u16NetWorkIndex = pMuxTable[cIDIndex].cNetWorkIndex;
        if( u16NetWorkIndex >= u16NetWorkTableArraySize )
            continue;

        if( wNID == pstNetWorkTable[u16NetWorkIndex].wNetwork_ID)
        {
            for(k=0;k<cCountOfTS;k++)
            {
                if(pMuxTable[cIDIndex].wTransportStream_ID == pwTS_ID[k])
                {
                    CLRBIT(u32GetTS,k);
                    break;
                }
            }
            if( cCountOfTS <= k)
            {
                if(bRemove)
                {
                    RemoveProgram(bServiceType, wPosition);
                }
                wRemovedProgramCount++;
            }
        }
        wPosition--;
    }
#endif

    if(wRemovedProgramCount && bRemove)
    {
        //printf("remove..........%\n");
        __msAPI_CM_ArrangeDataManager(TRUE, TRUE, FALSE);
    }

    *u32NewTS=u32GetTS;

    if(wRemovedProgramCount)
        return TRUE;

    return FALSE;
}

static BOOLEAN _msAPI_CM_Set_InvalidCell_ByServiceType(MEMBER_SERVICETYPE eServiceType, WORD wONID, WORD wTSID, WORD wCellID)
{
    WORD i;
    U16  u16IDIndex;

    WORD wPosition,wProgramCount,wOrder;
    WORD wPRIndex;
    CHANNEL_ATTRIBUTE stCHAttribute;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);



    //printf(" _msAPI_CM_Set_InvalidCell ONID %u TS %u Cell %u\n",wONID,wTSID,wCellID);

    //bServiceType=E_SERVICETYPE_DTV;
    wProgramCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(eServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
        {
            continue;
        }

        u16IDIndex = pstProgramIndexTable[wOrder].cIDIndex;
        if( u16IDIndex >= u16IDTableArraySize )
        {
            continue;
        }

        if( (pMuxTable[u16IDIndex].wOriginalNetwork_ID==wONID)
         && (pMuxTable[u16IDIndex].wTransportStream_ID==wTSID) )
        {
            if(pMuxTable[u16IDIndex].wCellID==wCellID)
            {
                if (FALSE == pstProgramIndexTable[wOrder].bInvalidCell)
                {
                    wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
                    if( FALSE == GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                        return FALSE;

                    stCHAttribute.bInvalidCell = TRUE;
                    pstProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;

                    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                    {
                        return FALSE;
                    }
                }
            }
            //printf("invalid cell %u cell %u lcn %u\n",m_astDTVProgramIndexTable[wOrder].bInvalidCell,_astDTVProgramIDTable[cIDIndex].wCellID,m_astDTVProgramIndexTable[wOrder].wLCN);
        }
        wPosition--;
    }

#if 0
    bServiceType=E_SERVICETYPE_RADIO;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        if((pMuxTable[cIDIndex].wOriginalNetwork_ID==wONID)
            && (pMuxTable[cIDIndex].wTransportStream_ID==wTSID))
        {
            if(pMuxTable[cIDIndex].wCellID==wCellID)
            {
                if (FALSE == m_astDTVProgramIndexTable[wOrder].bInvalidCell)
                {
                    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
                    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    stCHAttribute.bInvalidCell = TRUE;
                    m_astDTVProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;
                    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                    {
                        return FALSE;
                    }
                }
            }
            //printf("invalid cell %u cell %u lcn %u\n",m_astDTVProgramIndexTable[wOrder].bInvalidCell,_astDTVProgramIDTable[cIDIndex].wCellID,m_astDTVProgramIndexTable[wOrder].wLCN);
        }
        wPosition--;
    }

#if (NORDIG_FUNC) //for Nordig spec v2.0
    bServiceType=E_SERVICETYPE_DATA;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        if((pMuxTable[cIDIndex].wOriginalNetwork_ID==wONID)
            && (pMuxTable[cIDIndex].wTransportStream_ID==wTSID))
        {
            if(pMuxTable[cIDIndex].wCellID==wCellID)
            {
                if (FALSE == m_astDTVProgramIndexTable[wOrder].bInvalidCell)
                {
                    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
                    GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                    stCHAttribute.bInvalidCell = TRUE;
                    m_astDTVProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;
                    if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                    {
                        return FALSE;
                    }
                }
            }
            //printf("invalid cell %u cell %u lcn %u\n",m_astDTVProgramIndexTable[wOrder].bInvalidCell,_astDTVProgramIDTable[cIDIndex].wCellID,m_astDTVProgramIndexTable[wOrder].wLCN);
        }
        wPosition--;
    }
#endif
#endif

    return TRUE;
}

static BOOLEAN _msAPI_CM_Set_InvalidCell(WORD wONID, WORD wTSID, WORD wCellID)
{
    BOOL bRtn;

    bRtn = _msAPI_CM_Set_InvalidCell_ByServiceType(E_SERVICETYPE_DTV, wONID, wTSID, wCellID);
    if( bRtn == FALSE )
        return FALSE;

    bRtn = _msAPI_CM_Set_InvalidCell_ByServiceType(E_SERVICETYPE_RADIO, wONID, wTSID, wCellID);
    if( bRtn == FALSE )
        return FALSE;

#if (NORDIG_FUNC) //for Nordig spec v2.0
    bRtn = _msAPI_CM_Set_InvalidCell_ByServiceType(E_SERVICETYPE_DATA, wONID, wTSID, wCellID);
    if( bRtn == FALSE )
        return FALSE;
#endif

    return TRUE;
}

BOOLEAN msAPI_CM_SetMismatchedCell(WORD wONID, WORD wTSID, WORD *pCellLsit, U8 u8CellNumber, BOOLEAN *bRemoved)
{
    U8 j;
    U16 u16IDIndex;
    BOOLEAN eResult=FALSE;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    *bRemoved=FALSE;

    for( u16IDIndex=0; u16IDIndex < u16IDTableArraySize; u16IDIndex ++)
    {
        if( (pMuxTable[u16IDIndex].wCellID)
          &&(pMuxTable[u16IDIndex].wOriginalNetwork_ID == wONID)
          &&(pMuxTable[u16IDIndex].wTransportStream_ID == wTSID)
          )
        {
            //printf("msAPI_CM_SetMismatchedCell ts %u cell %u\n",_astDTVProgramIDTable[i].wTransportStream_ID,_astDTVProgramIDTable[i].wCellID);
            for(j=0;j<u8CellNumber;j++)
            {
                if(pMuxTable[u16IDIndex].wCellID == pCellLsit[j])
                {
                    break;
                }
            }

            if(j >= u8CellNumber)
            {
                *bRemoved=TRUE;
                _msAPI_CM_Set_InvalidCell(wONID, wTSID, pMuxTable[u16IDIndex].wCellID);
                eResult=TRUE;
            }
        }
    }

    return eResult;
}

BOOLEAN msAPI_CM_SetUnconfirmedServiceInvalid_ByServiceType(MEMBER_SERVICETYPE eServiceType, WORD wONID, WORD wTSID, BOOLEAN *bGotService)
{
    WORD i;
    U16  u16IDIndex;
    WORD wPosition,wProgramCount,wOrder;
    *bGotService=FALSE;
    WORD wPRIndex;
    CHANNEL_ATTRIBUTE stCHAttribute;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    //printf("x_msAPI_CM_Set_InvalidCell ONID %u TS %u Cell %u\n",wONID,wTSID,wCellID);

    //bServiceType=E_SERVICETYPE_DTV;
    wProgramCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(eServiceType, wPosition);
        if(wOrder > u16ProgramIndexTableArraySize )
            continue;

        u16IDIndex = pstProgramIndexTable[wOrder].cIDIndex;
        if(u16IDIndex > u16IDTableArraySize )
            continue;


        if( (pMuxTable[u16IDIndex].wOriginalNetwork_ID==wONID)
          && (pMuxTable[u16IDIndex].wTransportStream_ID==wTSID)
          && (pMuxTable[u16IDIndex].cRFChannelNumber==UNCONFIRMED_PHYSICAL_CHANNEL_NUMBER)
          )
        {
            *bGotService=TRUE;
            if (FALSE == pstProgramIndexTable[wOrder].bInvalidCell)
            {
                wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
                if( FALSE == GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                {
                    return FALSE;
                }

                stCHAttribute.bInvalidCell = TRUE;
                pstProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;

                if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                {
                    return FALSE;
                }
            }
        }
        wPosition--;
    }

#if 0
    bServiceType=E_SERVICETYPE_RADIO;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        if((pMuxTable[cIDIndex].wOriginalNetwork_ID==wONID)
            && (pMuxTable[cIDIndex].wTransportStream_ID==wTSID)
            && (pMuxTable[cIDIndex].cRFChannelNumber==UNCONFIRMED_PHYSICAL_CHANNEL_NUMBER))
        {
            *bGotService=TRUE;
            if (FALSE == m_astDTVProgramIndexTable[wOrder].bInvalidCell)
            {
                wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
                GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                stCHAttribute.bInvalidCell = TRUE;
                m_astDTVProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;
                if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                {
                    return FALSE;
                }
            }
        }
        wPosition--;
    }

#if (NORDIG_FUNC) //for Nordig spec v2.0
    bServiceType=E_SERVICETYPE_DATA;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        if((pMuxTable[cIDIndex].wOriginalNetwork_ID==wONID)
            && (pMuxTable[cIDIndex].wTransportStream_ID==wTSID)
            && (pMuxTable[cIDIndex].cRFChannelNumber==UNCONFIRMED_PHYSICAL_CHANNEL_NUMBER))
        {
            *bGotService=TRUE;
            if (FALSE == m_astDTVProgramIndexTable[wOrder].bInvalidCell)
            {
                wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;
                GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                stCHAttribute.bInvalidCell = TRUE;
                m_astDTVProgramIndexTable[wOrder].bInvalidCell = stCHAttribute.bInvalidCell;
                if( TRUE != SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                {
                    return FALSE;
                }
            }
        }
        wPosition--;
    }
#endif
#endif

    return TRUE;
}

BOOLEAN msAPI_CM_SetUnconfirmedServiceInvalid(WORD wONID, WORD wTSID, BOOLEAN *bGotService)
{
    BOOL bRtn;

    bRtn = msAPI_CM_SetUnconfirmedServiceInvalid_ByServiceType(E_SERVICETYPE_DTV, wONID, wTSID, bGotService);
    if( bRtn == FALSE )
        return FALSE;

    bRtn = msAPI_CM_SetUnconfirmedServiceInvalid_ByServiceType(E_SERVICETYPE_RADIO, wONID, wTSID, bGotService);
    if( bRtn == FALSE )
        return FALSE;

#if (NORDIG_FUNC) //for Nordig spec v2.0
    bRtn = msAPI_CM_SetUnconfirmedServiceInvalid_ByServiceType(E_SERVICETYPE_DATA, wONID, wTSID, bGotService);
    if( bRtn == FALSE )
        return FALSE;
#endif

    return TRUE;
}

BOOLEAN msAPI_CM_RemoveInvalidService(BOOLEAN *bCurCHIsRemoved)
{
    MEMBER_SERVICETYPE bServiceType, l_eServiceType;
    WORD wPosition, l_wPosition,wProgramCount,wOrder;
    WORD wService_ID;
    WORD i,position;
    BYTE cPhysicalChannelNumber;
    WORD wRemoveCnt=0;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    *bCurCHIsRemoved=FALSE;

    bServiceType = msAPI_CM_GetCurrentServiceType();
    wPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    wService_ID = msAPI_CM_GetService_ID(bServiceType, wPosition);
    cPhysicalChannelNumber = msAPI_CM_GetPhysicalChannelNumber(bServiceType, wPosition);


    bServiceType=E_SERVICETYPE_DTV;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder >= u16ProgramIndexTableArraySize)
            continue;

        if(pstProgramIndexTable[wOrder].bInvalidCell)
        {
            RemoveProgram(bServiceType, wPosition);
            wRemoveCnt++;
        }
        wPosition--;
    }

    bServiceType=E_SERVICETYPE_RADIO;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder >= u16ProgramIndexTableArraySize)
            continue;

        if(pstProgramIndexTable[wOrder].bInvalidCell)
        {
            RemoveProgram(bServiceType, wPosition);
            wRemoveCnt++;
        }
        wPosition--;
    }

#if (NORDIG_FUNC) //for Nordig spec v2.0
    bServiceType=E_SERVICETYPE_DATA;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder >= u16ProgramIndexTableArraySize)
            continue;

        if( pstProgramIndexTable[wOrder].bInvalidCell)
        {
            RemoveProgram(bServiceType, wPosition);
            wRemoveCnt++;
        }
        wPosition--;
    }
#endif

    if(wRemoveCnt)
    {
        __msAPI_CM_ArrangeDataManager(TRUE,FALSE,FALSE);
        if(TRUE== msAPI_CM_GetServiceTypeAndPositionWithPCN(cPhysicalChannelNumber, wService_ID, &l_eServiceType, &l_wPosition))
        {
            if (wPosition != l_wPosition)
            {
                msAPI_CM_SetCurrentPosition(l_eServiceType, l_wPosition);
                //printf("msAPI_CM_RemoveInvalidCell update position\n");
            }
        }
         else
        {
            *bCurCHIsRemoved=TRUE;
            //printf("msAPI_CM_RemoveInvalidCell current service is removed\n");
            if((position= msAPI_CM_GetFirstProgramPosition(E_SERVICETYPE_DTV,FALSE)) != INVALID_PROGRAM_POSITION )
            {
                msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,position);
            }
            else if((position= msAPI_CM_GetFirstProgramPosition(E_SERVICETYPE_RADIO,FALSE)) != INVALID_PROGRAM_POSITION)
            {
                msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,position);
            }
#if (NORDIG_FUNC) //for Nordig spec v2.0
            else if((position= msAPI_CM_GetFirstProgramPosition(E_SERVICETYPE_DATA,FALSE)) != INVALID_PROGRAM_POSITION)
            {
                msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
                msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,position);
            }
#endif
        }
    }

    return TRUE;
}

BOOLEAN msAPI_CM_CheckNetwork(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, U32 *u32NewTS, WORD *pwRemoveTSID, BYTE cMaxTSCnt, BOOLEAN *bRemove)
{
    U32 u32GetTS=0;
    BYTE j,k=0;
    U16 i;
    BOOLEAN bMatchNetwork=FALSE;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkIndex;


    *bRemove=FALSE;

    for(i=0;(i<cCountOfTS)&&(i<32);i++)
    {
        SETBIT(u32GetTS, i);
    }

    for(i=0;i<u16IDTableArraySize;i++)
    {
        u16NetWorkIndex = pMuxTable[i].cNetWorkIndex;
        if( u16NetWorkIndex < u16NetWorkTableArraySize)// anvi  resolve mantis 0378496(Chakra3)
        {
            if(pstNetWorkTable[u16NetWorkIndex].wNetwork_ID == wNID)
            {
                for(j=0;j<cCountOfTS;j++)
                {
                    if(pwTS_ID[j] == pMuxTable[i].wTransportStream_ID)
                    {
                        CLRBIT(u32GetTS,j);
                        break;
                    }
                }
                if(j>=cCountOfTS)
                {
                    *bRemove=TRUE;
                    if(k < cMaxTSCnt)
                    {
                        pwRemoveTSID[k] = pMuxTable[i].wTransportStream_ID;
                        k++;
                    }
                }
                bMatchNetwork=TRUE;
            }
        }
    }
    *u32NewTS=u32GetTS;
    if(bMatchNetwork == FALSE)
    {
        *u32NewTS=0;
    }
    return TRUE;
}
#endif

BOOLEAN msAPI_CM_GetIDTable(WORD bIDIndex, BYTE * pcBuffer,PROGRAMDATA_MEMBER eMember)
{
    return GetIDTable(bIDIndex, pcBuffer, eMember);
}

BOOLEAN msAPI_CM_SetIDTable(WORD bIDIndex, BYTE * pcBuffer,PROGRAMDATA_MEMBER eMember)
{
    return SetIDTable(bIDIndex, pcBuffer, eMember);
}

void msAPI_CM_EnableStoreDataToFlash(BOOLEAN bEnable)//20090806
{
    _bSaveDataToFlash=bEnable;
}

void msAPI_CM_GetCMVerString(U8 *pVer)
{
    if(pVer != NULL)
        memcpy(pVer, &u8CM_LibVer[0], sizeof(u8CM_LibVer));
}

//------------------------------------------------------------------------------
///  Reset DTV Data manager
/// @return BOOLEAN : Function execution result
//****************************************************************************
extern EN_SYS_INPUT_SOURCE_TYPE  _enSysInputSource[2];

#if( ENABLE_API_DTV_SYSTEM_2015)
#if (ENABLE_S2)
BOOLEAN msAPI_CM_ResetDTVDataManager_DVBS(void)
{
#if 0//(ENABLE_COMPRESS_DATA)
    MS_U32 pDatabaseInDram;
    pDatabaseInDram = RAM_DISK_DB_64K_START_ADDR;//DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)));
    memset((U8 *)_PA2VA((MS_U32)pDatabaseInDram),0xFF,RM_64K_USAGE);
#endif

    msAPI_CM_ResetS2Program();

#if(ENABLE_S2_PROGRAM_PREPARE)
    msAPI_CM_SetProgram();
#endif

    return TRUE;
}
#endif

#define CM_RESET_DB_ALL E_DTV_DB_NUM//0xFF
BOOLEAN msAPI_CM_ResetDTVDataManager_2015(TypDtvDbSel eDBSel)
{
    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());

#if (ENABLE_S2)
    BOOL bResetDVBS = FALSE;
#endif
#if (ENABLE_DVBC && DVB_T_C_DIFF_DB)
    BOOL bResetDVBC = FALSE;
#endif
#if 1//(ENABLE_DVBT)
    BOOL bResetDVBT = FALSE;
#endif


    if( eDBSel == CM_RESET_DB_ALL ) // For Power on init or Restore to default
    {
    #if (ENABLE_S2)
        bResetDVBS = TRUE;
    #endif
    #if (ENABLE_DVBC && DVB_T_C_DIFF_DB)
        bResetDVBC = TRUE;
    #endif
        bResetDVBT = TRUE;
    }
    else // For other app
    {
    #if (ENABLE_S2)
        if( eDBSel == E_DTV_DB_SEL_DVBS )
        {
            bResetDVBS = TRUE;
        } else
    #endif
    #if (ENABLE_DVBC && DVB_T_C_DIFF_DB)
        if( eDBSel == E_DTV_DB_SEL_DVBC)
        {
            bResetDVBC = TRUE;
        } else
    #endif
        {
            bResetDVBT = TRUE;
        }
    }


    EN_SYS_INPUT_SOURCE_TYPE eSysInputSource_Backup = _enSysInputSource[MAIN_WINDOW];
    U8 u8DVBCTvConnectionType_Backup = stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType;

#if (ENABLE_S2)
    if(bResetDVBS)
    {
        // Force use dvbs DB
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_S2;
        msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBS);

        msAPI_CM_ResetDTVDataManager_DVBS();

        msAPI_DtvDB_Set_Identify(E_DTV_DB_SEL_DVBS, DTVDATA_ID_DVBS);
    }
#endif
#if (ENABLE_DVBC && DVB_T_C_DIFF_DB)
    if(bResetDVBC)
    {
        // Force use dvbc DB
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_DVBC;
        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_C_TYPE;
        msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBC);

        msAPI_CM_ResetAllProgram();
        msAPI_DtvDB_Set_Identify(E_DTV_DB_SEL_DVBC, DTVDATA_ID_DVBC);
    }
#endif
    if(bResetDVBT)
    {
        // Force use dvbt DB
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_DVBT;
        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_T_TYPE;
        msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBT);

        msAPI_CM_ResetAllProgram();

        msAPI_DtvDB_Set_Identify(E_DTV_DB_SEL_DVBT, DTVDATA_ID);
    }

    // Restore original data
    _enSysInputSource[MAIN_WINDOW] = eSysInputSource_Backup;
    stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = u8DVBCTvConnectionType_Backup;
    msAPI_DTV_Comm_Set_ForceDBSel(DISABLE, E_DTV_DB_NUM);

    return TRUE;
}
#endif

BOOLEAN msAPI_CM_ResetDTVDataManager(BOOLEAN bResetAllDB)
{
    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());

#if( ENABLE_API_DTV_SYSTEM_2015) // Use new method

    if( bResetAllDB )
        msAPI_CM_ResetDTVDataManager_2015(CM_RESET_DB_ALL);
    else
    {
        TypDtvDbSel eCurDBSel = msAPI_DTV_Comm_Get_DBSel();
        msAPI_CM_ResetDTVDataManager_2015(eCurDBSel);
    }
    return TRUE;
#else

    U16 wID;

#if DVB_T_C_DIFF_DB
    if( bResetAllDB )
    {
    #if(ENABLE_S2)
        EN_SYS_INPUT_SOURCE_TYPE temp;
        temp =_enSysInputSource[MAIN_WINDOW];
    #endif

        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_T_TYPE;
        //msAPI_CM_SetCountry(DEFAULT_COUNTRY);
    #if(ENABLE_S2)
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_DVBT;
        //msAPI_InputSrcType_SetType(EN_SYS_INPUT_SOURCE_TYPE_DTV);
    #endif

    #if ENABLE_DTV
        msAPI_CM_ResetAllProgram();
    #endif
    #if(ENABLE_S2)
        //msAPI_InputSrcType_SetType(EN_SYS_INPUT_SOURCE_TYPE_S2);
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_S2;
        msAPI_CM_ResetS2Program();
    #if(ENABLE_S2_PROGRAM_PREPARE)
        msAPI_CM_SetProgram();
    #endif
        _enSysInputSource[MAIN_WINDOW] = temp;
    #endif

        wID = DTVDATA_ID;
        SetNVRAM(BASEADDRESS_PR_IDENT, (BYTE *)&wID, sizeof(wID));


    #if(ENABLE_S2)
        temp =_enSysInputSource[MAIN_WINDOW];
    #endif

        stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_C_TYPE;
        //msAPI_CM_SetCountry(DEFAULT_COUNTRY);

    #if(ENABLE_S2)
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_DVBC;
        //msAPI_InputSrcType_SetType(EN_SYS_INPUT_SOURCE_TYPE_DTV);
    #endif

    #if ENABLE_DTV
        msAPI_CM_ResetAllProgram();
    #endif


    #if(ENABLE_S2)
        _enSysInputSource[MAIN_WINDOW] = temp;
    #endif

        wID = DTVDATA_ID;
        SetNVRAM(BASEADDRESS_PR_IDENT, (BYTE *)&wID, sizeof(wID));
    }
    else
#else
    UNUSED(bResetAllDB);
#endif
    {
    #if(ENABLE_S2)
        EN_SYS_INPUT_SOURCE_TYPE temp;
        temp =_enSysInputSource[MAIN_WINDOW];
    #endif

    #if(ENABLE_COMPRESS_DATA)
        MS_U32 pDatabaseInDram;
        pDatabaseInDram = RAM_DISK_DB_64K_START_ADDR;//DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)));
        memset((U8 *)_PA2VA((MS_U32)pDatabaseInDram),0xFF,RM_64K_USAGE);
    #endif

        //msAPI_CM_SetCountry(DEFAULT_COUNTRY);
    #if ENABLE_DTV
    #if(ENABLE_S2)
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_S2;
    #endif
        msAPI_CM_ResetAllProgram();
    #endif
    #if (ENABLE_S2)
        _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_S2;
        msAPI_CM_ResetS2Program();
    #if(ENABLE_S2_PROGRAM_PREPARE)
        msAPI_CM_SetProgram();
    #endif
        _enSysInputSource[MAIN_WINDOW] = temp;
    #endif
        wID = DTVDATA_ID;
        SetNVRAM(BASEADDRESS_PR_IDENT, (BYTE *)&wID, sizeof(wID));
    }
    return TRUE;
#endif
}

#if( ENABLE_API_DTV_SYSTEM_2015)
void msAPI_CM_Init_LoadServiceTypeAndOrder(TypDtvDbSel eDtvDbSel)
{
    m_aeCurrentServiceType[eDtvDbSel] = LoadCurrentServiceType_DBSel(eDtvDbSel);

    m_awCurrentOrderOfTV[eDtvDbSel] = LoadCurrentOrderOfTV_DBSel(eDtvDbSel);
    m_awPastOrderOfTV[eDtvDbSel] = m_awCurrentOrderOfTV[eDtvDbSel];

    m_awCurrentOrderOfRadio[eDtvDbSel] = LoadCurrentOrderOfRadio_DBSel(eDtvDbSel);
    m_awPastOrderOfRadio[eDtvDbSel] = m_awCurrentOrderOfRadio[eDtvDbSel];

    m_awCurrentOrderOfData[eDtvDbSel] = LoadCurrentOrderOfData_DBSel(eDtvDbSel);
    m_awPastOrderOfData[eDtvDbSel] = m_awCurrentOrderOfData[eDtvDbSel];
}

// Load data from ramdisk to variable
void msAPI_CM_Init_LoadMisc(TypDtvDbSel eDtvDbSel)
{
    eDtvDbSel=eDtvDbSel;

    // Country already load in msAPI_CM_Init()


    // Load Favorite Region
#if (NTV_FUNCTION_ENABLE)
    //GetNVRAM(BASEADDRESS_PR_FAVORITE_REGION, (BYTE *)&_cFavoriteNetwork, sizeof(_cFavoriteNetwork));
    s_au8FavoriteNetwork[eDtvDbSel] = msAPI_DtvDB_Get_FavoriteRegion(eDtvDbSel);
#endif
}

void msAPI_CM_InitDTVDataManager_ByDBSel(TypDtvDbSel eDtvDbSel)
{
    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());

    // Check DB Identfy ...
    U16 u16DBMagicId = msAPI_DtvDB_Get_DataBaseMagicId(eDtvDbSel);

    // If DB is invalid, Reset it
    U16 u16CurID = msAPI_DtvDB_Get_Identify(eDtvDbSel);
    if( u16CurID != u16DBMagicId )
    {
        PRINT_CURRENT_LINE();
        printf("\nWarning: DB-DVBT ID=0x%X is wring!(0x%X)\n", u16CurID, u16DBMagicId);
        msAPI_CM_ResetDTVDataManager_2015(eDtvDbSel);
    }
    else
    { // Init DataManager

        // Country is store in GenSetting
        // Country already load in msAPI_CM_Init()
        //GetNVRAM(BASEADDRESS_COUNTRY, (BYTE *)&m_eCountry, sizeof(m_eCountry));

        // Load DTV data ...
        msAPI_CM_Init_LoadMisc(eDtvDbSel);

        // Load Program Table Map
        U8* pu8ProgramTableMap = msAPI_DtvDB_Get_ProgTableMap(eDtvDbSel);
        U16 u16ProgramTableMapArraySize = msAPI_DtvDB_Get_ProgTableMapArraySize(eDtvDbSel);

        //GetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP, (BYTE *)m_acDTVProgramTableMap, sizeof(m_acDTVProgramTableMap));
        msAPI_DtvDB_Load_ProgramTableMap(eDtvDbSel, pu8ProgramTableMap, u16ProgramTableMapArraySize);

        msAPI_Timer_ResetWDT();

    #if ENABLE_S2
        if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
        {
            CreatS2ProgramIndexTableAndProgramIDTable();
        }
        else
    #endif
        {
            CreatDTVProgramIndexTableAndProgramIDTable(eDtvDbSel);
        }

        msAPI_Timer_ResetWDT();

        msAPI_CM_Init_LoadServiceTypeAndOrder(eDtvDbSel);

    #if ENABLE_S2
        if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
        {
            if(stGenSetting.stDvbsSetting.g_sort_type != EN_SORT_BY_DEFAULT)
            { // Start up sorting test, if not default:
                msAPI_CM_QuickSortService(E_SERVICETYPE_DTV);
                msAPI_CM_QuickSortService(E_SERVICETYPE_RADIO);
                msAPI_CM_QuickSortService(E_SERVICETYPE_DATA);
            }
        }
    #endif

    }
}

//------------------------------------------------------------------------------
///  Initialize DTV Data manager
/// @return BOOLEAN : Function execution result
//------------------------------------------------------------------------------
BOOLEAN msAPI_CM_InitDTVDataManager_CurSource(void)
{
    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());

    //EN_SYS_INPUT_SOURCE_TYPE eSysInputSource_Backup = _enSysInputSource[MAIN_WINDOW];
    //U8 u8DVBCTvConnectionType_Backup = stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType;


    msAPI_DTV_Comm_Set_ForceDBSel(DISABLE, E_DTV_DB_NUM);

    // Init DB-DVBS ...
 #if(ENABLE_S2)
    if( IsS2InUse() )
    {
        printf("Init DB-DVBS...\n");
        msAPI_CM_InitDTVDataManager_ByDBSel(E_DTV_DB_SEL_DVBS);
    }
    else
 #endif
    // Init DB-DVBC ...
  #if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
    if( IsDVBCInUse() )
    {
        printf("Init DB-DVBC...\n");
        msAPI_CM_InitDTVDataManager_ByDBSel(E_DTV_DB_SEL_DVBC);
    }
    else
  #endif
    {
        // Init DB-DVBT ...
        printf("Init DB-DVBT...\n");
        msAPI_CM_InitDTVDataManager_ByDBSel(E_DTV_DB_SEL_DVBT);
    }

    // Restore original data
    //_enSysInputSource[MAIN_WINDOW] = eSysInputSource_Backup;
    //stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = u8DVBCTvConnectionType_Backup;
    //msAPI_DTV_Comm_Set_ForceDBSel(DISABLE, E_DTV_DB_NUM);

    return TRUE;
}

#endif

//------------------------------------------------------------------------------
///  Initialize DTV Data manager
/// @return BOOLEAN : Function execution result
//------------------------------------------------------------------------------

// Init all DTV DB for power on init
// Because this function will be called before InputSourceSwitch,
// Must force DB Sel
BOOLEAN msAPI_CM_InitDTVDataManager(void)
{
    DEBUG_DTV_SYS(PRINT_CURRENT_LINE());

#if(ENABLE_API_DTV_SYSTEM_2015)  // Use new method
    EN_SYS_INPUT_SOURCE_TYPE eSysInputSource_Backup = _enSysInputSource[MAIN_WINDOW];
    U8 u8DVBCTvConnectionType_Backup = stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType;


    // Init DB-DVBT ...
    // Force use dvbt DB
    printf("Init DB-DVBT...\n");
    _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_DVBT;
    stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_T_TYPE;
    msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBT);
    msAPI_CM_InitDTVDataManager_ByDBSel(E_DTV_DB_SEL_DVBT);


    // Init DB-DVBC ...
  #if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
    printf("Init DB-DVBC...\n");
    // Force use dvbc DB
    _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_DVBC;
    stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = EN_DVB_C_TYPE;
    msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBC);
    msAPI_CM_InitDTVDataManager_ByDBSel(E_DTV_DB_SEL_DVBC);
  #endif


    // Init DB-DVBS ...
 #if(ENABLE_S2)
    printf("Init DB-DVBS...\n");
     // Force use dvbs DB
    _enSysInputSource[MAIN_WINDOW] = EN_SYS_INPUT_SOURCE_TYPE_S2;
    msAPI_DTV_Comm_Set_ForceDBSel(ENABLE, E_DTV_DB_SEL_DVBS);
    msAPI_CM_InitDTVDataManager_ByDBSel(E_DTV_DB_SEL_DVBS);
 #endif

    // Restore original data
    _enSysInputSource[MAIN_WINDOW] = eSysInputSource_Backup;
    stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType = u8DVBCTvConnectionType_Backup;
    msAPI_DTV_Comm_Set_ForceDBSel(DISABLE, E_DTV_DB_NUM);

#else

    BYTE i;
    WORD wID=0;

 #if(ENABLE_S2)
    if(!IsS2InUse())
 #endif
    {
        for (i=0; i < 5; i++)
        {
            if( TRUE == GetNVRAM(BASEADDRESS_PR_IDENT, (BYTE *)&wID, sizeof(wID)) )
            {
                if ( wID == DTVDATA_ID )
                {
                    break;
                }
            }
        }

        if( wID != DTVDATA_ID )
        {
            msAPI_CM_ResetDTVDataManager(FALSE);
        }
    }

    //GetNVRAM(BASEADDRESS_COUNTRY, (BYTE *)&m_eCountry, sizeof(m_eCountry));

 #if (NTV_FUNCTION_ENABLE)
    GetNVRAM(BASEADDRESS_PR_FAVORITE_REGION, (BYTE *)&_cFavoriteNetwork, sizeof(_cFavoriteNetwork));
 #endif

 #if ENABLE_S2
    if( IsS2InUse() )
    {
        //m_eCountry= E_UK;
        msAPI_Timer_ResetWDT();

        GetNVRAM(S2_BASEADDRESS_PR_DTVPRTABLEMAP, (BYTE *)m_acS2ProgramTableMap, sizeof(m_acS2ProgramTableMap));
        CreatS2ProgramIndexTableAndProgramIDTable();

        msAPI_Timer_ResetWDT();
    }
    else
 #endif
    {
    #if DVB_T_C_DIFF_DB
        if (IsDVBCInUse())
        {
            GetNVRAM(BASEADDRESS_PR_DTV_C_PRTABLEMAP, (BYTE *)m_acDTVProgramTableMap_DVBC, sizeof(m_acDTVProgramTableMap_DVBC));
        }
        else
    #endif
        {
            GetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP, (BYTE *)m_acDTVProgramTableMap, sizeof(m_acDTVProgramTableMap));
        }

        //GetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP,(BYTE * )m_acDTVIDtableMap,sizeof(m_acDTVIDtableMap));
        CreatDTVProgramIndexTableAndProgramIDTable(CUR_DB_SEL());
    }

    m_eCurrentServiceType = LoadCurrentServiceType();
    m_wCurrentOrderOfTV = LoadCurrentOrderOfTV();
    m_wPastOrderOfTV = m_wCurrentOrderOfTV;
    m_wCurrentOrderOfRadio = LoadCurrentOrderOfRadio();
    m_wPastOrderOfRadio = m_wCurrentOrderOfRadio;
    m_wCurrentOrderOfData = LoadCurrentOrderOfData();
    m_wPastOrderOfData = m_wCurrentOrderOfData;

 #if ENABLE_S2
    if(IsS2InUse())
    {
      if(stGenSetting.stDvbsSetting.g_sort_type != EN_SORT_BY_DEFAULT)
      { // Start up sorting test, if not default:
          msAPI_CM_QuickSortService(E_SERVICETYPE_DTV);
          msAPI_CM_QuickSortService(E_SERVICETYPE_RADIO);
          msAPI_CM_QuickSortService(E_SERVICETYPE_DATA);
      }
    }
 #endif

#endif


    // What is this ???
#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
    memset(_astServiceListInfo, 0, sizeof(DVBS_SI_SGT_BASIC_SERVICE_LIST_INFO)*MAX_SGT_MUX_NUMBER);
#endif  //#if(ASTRA_HD_ENABLE)

    return TRUE;
}

//****************************************************************************
/// Get NVRAM
/// @param wAddress \b IN: Address
/// @param pcBuffer \b IN: pointer to Buffer for return
/// @param cSize \b IN: pointer to cSize for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN GetNVRAM(DWORD wAddress, BYTE * pcBuffer, WORD cSize)
{
#if (EEPROM_DB_STORAGE==EEPROM_SAVE_ALL)
    msAPI_rmBurstReadBytes(wAddress,pcBuffer,cSize);

#else

    U32 u32DramAddr = wAddress + RAM_DISK_MEM_ADDR;

   memcpy(pcBuffer,(void *)_PA2VA(u32DramAddr),cSize);

#endif

    return TRUE;
}

//****************************************************************************
/// Set NVRAM
/// @param wAddress \b IN: Address
/// @param pcBuffer \b IN: pointer to Buffer
/// @param cSize \b IN: pointer to cSize
/// @return BOOLEAN: Function execution result
//****************************************************************************

#define DEBUG_SET_NVRAM(x)  //x

BOOLEAN SetNVRAM(DWORD wAddress, BYTE * pcBuffer, WORD cSize)
{
    DEBUG_SET_NVRAM(printf("SetNVRAM(wAddress=0x%X, cSize=%u, data=0x%X)\n", wAddress, cSize, pcBuffer[0]););

    // Check address of ramdisk:
    if( (wAddress > RM_DB_TOTAL_USAGE)
      ||(wAddress > DATABASE_START_LEN)
      )
    {
        printf("\nError: SetNVRAM: address(0x%X) is over range!\n", wAddress);
        printf(" RM_DB_TOTAL_USAGE=%X\n", RM_DB_TOTAL_USAGE);
        printf(" DATABASE_START_LEN=%X\n", DATABASE_START_LEN);
        return FALSE;
    }

#if (EEPROM_DB_STORAGE==EEPROM_SAVE_ALL)
    msAPI_rmBurstWriteBytes(wAddress,pcBuffer, cSize);

#else

    U32 u32DramAddr = wAddress + RAM_DISK_MEM_ADDR;


    if( FALSE == msAPI_MIU_CompareBuf(u32DramAddr, pcBuffer, cSize) )
    {
        DEBUG_SET_NVRAM(printf("Data same\n"););
        return TRUE;
    }

    // copy new data to RamDisk
    memcpy( (void *)_PA2VA(u32DramAddr), pcBuffer, cSize);

    if ( !msAPI_CM_GetOpMode() ) //Only save normal mode CM
    {
        if(_bSaveDataToFlash)
        {
      #if(!BLOADER)
          //g_u8QuickDataBase |= QUICK_DB_UPDATE;
          MApp_DB_CH_Set_DataChanged(TRUE);
        #endif
        }
    }

#endif

    return TRUE;
}

//****************************************************************************
///  Get Country
/// @return MEMBER_COUNTRY : Country
//****************************************************************************
MEMBER_COUNTRY msAPI_CM_GetCountry(void)
{
    return m_eCountry;
}

//****************************************************************************
///  Set Country
/// @param eCountry \b IN: Country
/// - @see MEMBER_COUNTRY
/// @return BOOLEAN : Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_SetCountry(MEMBER_COUNTRY eCountry)
{
    if( eCountry < E_COUNTRY_NUM )
    {
        m_eCountry = eCountry;

    #if 1 // Use GenSetting
        stGenSetting.stTvSetting.eCountry = m_eCountry;
    #else
        SetNVRAM(BASEADDRESS_COUNTRY, (BYTE *)&eCountry, sizeof(eCountry));
    #endif

        //printf("\e[31;1m msAPI_CM_SetCountry(%d) \33[m \n", eCountry);

#if ENABLE_SBTVD_DTV_SYSTEM
        g_bIsSbtvdAppEn = IS_SBTVD_APP_COUNRTY(eCountry);
#endif

        return TRUE;
    }

    return FALSE;
}

//****************************************************************************
/// Get Network name
/// @param bIndex \b IN: bIndex
/// @param *bNetworkName \b IN: pointer to network name for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetNetworkName(BYTE bIndex, BYTE * bNetworkName)
{
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(CUR_DB_SEL());

    if( bIndex >= u16NetWorkTableArraySize)
    {
        return FALSE;
    }

    memset(bNetworkName, 0, MAX_NETWORK_NAME);

    return GetIDTable(bIndex, (BYTE *)bNetworkName, E_DATA_NETWORK_NAME);
}

//****************************************************************************
/// Store Network Name
/// @param bIndex \b IN: Network Name Table Index
/// @param *bNetworkName \b IN: pointer to Network Name for store
/// @return BYTE: Network Name Table Index of stored Network Name
//****************************************************************************
BOOLEAN msAPI_CM_SetNetworkName(BYTE bIndex, BYTE * bNetworkName)
{
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(CUR_DB_SEL());

    if( bIndex >= u16NetWorkTableArraySize || bNetworkName == NULL)
    {
        return FALSE;
    }

    return SetIDTable(bIndex, (BYTE *)bNetworkName, E_DATA_NETWORK_NAME);
}

BOOLEAN msAPI_CM_UpdateNetworkNameWithNID(WORD wNID, BYTE *bNetworkName)
{
    int i;
    BYTE cNetworkIndex;
    BYTE cTempNewWorkIndex = 0xFF;

    // Use new API
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M * pProgramIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);


    cNetworkIndex = u16NetWorkTableArraySize;

    for(i=0;i < u16NetWorkTableArraySize; i++)
    {
        if((wNID!= INVALID_NID) && (wNID == pstNetworkTable[i].wNetwork_ID))
        {
            cNetworkIndex = i;
            break;
        }
        else if((pstNetworkTable[i].wNetwork_ID == INVALID_NID) && (cTempNewWorkIndex == 0xFF))
        {
            cTempNewWorkIndex = i;
            break;
        }
    }

    if(cNetworkIndex < u16NetWorkTableArraySize)
    {
        if(memcmp(pstNetworkTable[cNetworkIndex].bNetworkName, bNetworkName, MAX_NETWORK_NAME))
        {
            memcpy(pstNetworkTable[cNetworkIndex].bNetworkName, bNetworkName, MAX_NETWORK_NAME);
            if(TRUE == msAPI_CM_SetNetworkName(cNetworkIndex, bNetworkName))
                return TRUE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {

        if(cTempNewWorkIndex != 0xFF)
        {
            cNetworkIndex = cTempNewWorkIndex;
            pstNetworkTable[cNetworkIndex].wNetwork_ID = wNID;
            if(memcmp(pstNetworkTable[cNetworkIndex].bNetworkName, bNetworkName, MAX_NETWORK_NAME))
            {
                memcpy(pstNetworkTable[cNetworkIndex].bNetworkName, bNetworkName, MAX_NETWORK_NAME);
                if(TRUE == msAPI_CM_SetNetworkName(cNetworkIndex, bNetworkName))
                return TRUE;
            }
            else
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

BOOLEAN msAPI_CM_SetCurrentNetworkName(U8 *bNetworkName, U8 u8NetworkLen)
{
    memset(_au8CurNetworkName,0,MAX_NETWORK_NAME);

    if(bNetworkName != NULL && u8NetworkLen)
    {
        _au8CurNetworkLen = u8NetworkLen > MAX_NETWORK_NAME ? MAX_NETWORK_NAME:u8NetworkLen;
        if(u8NetworkLen > MAX_NETWORK_NAME)
        {
            MS_DEBUG_MSG(printf("overrun-buffer-arg"));//coverity
        }
        else
        {
            memcpy(_au8CurNetworkName, bNetworkName, u8NetworkLen);
        }
        return TRUE;
    }
    return FALSE;
}

BOOLEAN _msAPI_CM_GetCurrentNetworkName(U8 *bNetworkName, U8 *u8NetworkLen)
{
    if(_au8CurNetworkLen)
    {
        memcpy(bNetworkName, _au8CurNetworkName, _au8CurNetworkLen);
        *u8NetworkLen = _au8CurNetworkLen;
        return TRUE;
    }
    else
    {
        *u8NetworkLen = 0;
        return FALSE;
    }
}

BOOLEAN msAPI_CM_GetCurrentNetworkName(U8 *bNetworkName, U8 *u8NetworkLen, U8 u8MaxLen)
{
    int i;
    MEMBER_SERVICETYPE bServiceType;
    WORD wCurrentPosition,wNetwork_ID;
    bServiceType = msAPI_CM_GetCurrentServiceType();
    wCurrentPosition = msAPI_CM_GetCurrentPosition(bServiceType);
    if(INVALID_PROGRAM_POSITION == wCurrentPosition)
    {
        return FALSE;
    }
    wNetwork_ID = msAPI_CM_GetNetwork_ID(bServiceType,wCurrentPosition);
    if(INVALID_NID == wNetwork_ID)
    {
        return FALSE;
    }

    // Use new API
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M * pProgramIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVNETWORK * pstNetworkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);



    for(i=0;i < u16NetWorkTableArraySize; i++)
    {
        if(wNetwork_ID == pstNetworkTable[i].wNetwork_ID)
        {
            if(u8MaxLen>MAX_NETWORK_NAME)
            {
                u8MaxLen=MAX_NETWORK_NAME;
            }
            msAPI_CM_GetNetworkName(i,bNetworkName);
            if(bNetworkName[u8MaxLen-1])
            {
                *u8NetworkLen=u8MaxLen;
            }
            else
            {
                *u8NetworkLen = strlen((char*)bNetworkName);
            }
            return TRUE;
        }
    }

    return FALSE;
}

//****************************************************************************
/// Count same Network program
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return WORD : Same network program number
//****************************************************************************
WORD msAPI_CM_CountNetworkProgram(MEMBER_SERVICETYPE bServiceType, U16 u16NetworkID)
{
    WORD wProgramCount;
    WORD wNetworkCount;
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return 0;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    wNetworkCount = 0;

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        if(u16NetworkID == msAPI_CM_GetNetwork_ID(bServiceType,wPosition))
        {
            wNetworkCount++;
        }
    }

    return wNetworkCount;
}

//****************************************************************************
/// Get first same network program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return WORD : First same Network Program position
//****************************************************************************
WORD msAPI_CM_GetFirstNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType, U16 u16NetworkID)
{
    WORD wProgramCount;
    WORD wPosition;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
         if(u16NetworkID == msAPI_CM_GetNetwork_ID(bServiceType,wPosition))
            return wPosition;
    }

    return INVALID_PROGRAM_POSITION;
}

//****************************************************************************
/// Get previous Same network program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @return WORD : previous same network Program position
//****************************************************************************
WORD msAPI_CM_GetPrevNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType,U16 wBasePosition, U16 u16NetworkID)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD i;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( FALSE == IsPositionValid(bServiceType, wBasePosition) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }

    for(i=0; i < wProgramCount; i++)
    {
        if( wPosition > 0 )
        {
            wPosition--;
        }
        else
        {
            wPosition = wProgramCount - 1;
        }

        if(u16NetworkID == msAPI_CM_GetNetwork_ID(bServiceType,wPosition))
            return wPosition;
    }

    return INVALID_PROGRAM_POSITION;
}

//****************************************************************************
/// Get Next same network program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wBasePosition \b IN: base position
/// @return WORD : Next network Program position
//****************************************************************************
WORD msAPI_CM_GetNextNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, U16 u16NetworkID)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD i;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    if( FALSE == IsPositionValid(bServiceType, wBasePosition) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }

    for(i=0; i< wProgramCount; i++)
    {
        wPosition++;

        if( wPosition >= wProgramCount )
        {
            wPosition = 0;
        }

        if(u16NetworkID == msAPI_CM_GetNetwork_ID(bServiceType,wPosition))
            return wPosition;
    }

    return INVALID_PROGRAM_POSITION;
}


//****************************************************************************
/// Get last same network program position
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @return WORD : last same network Program position
//****************************************************************************
WORD msAPI_CM_GetLastNetworkProgramPosition(MEMBER_SERVICETYPE bServiceType)
{
    U16 wPosition;
    U16 wNetworkID;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PROGRAM_POSITION;
    }

    wPosition = msAPI_CM_GetCurrentPosition(bServiceType);

    wNetworkID = msAPI_CM_GetNetwork_ID(bServiceType,wPosition);

    wPosition = msAPI_CM_GetFirstNetworkProgramPosition(bServiceType,wNetworkID);
    return msAPI_CM_GetPrevNetworkProgramPosition(bServiceType, wPosition,wNetworkID);
}

BOOLEAN msAPI_CM_GetIDIndexWithFreq(U32 u32Freq, U16 *pu16IDIndex)
//BOOLEAN msAPI_CM_GetIDIndexWithFreq(U32 u32Freq, BYTE *cIDIndex)
{
    U16 i;

    if (NULL == pu16IDIndex)
        return FALSE;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    //DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    //U16 u16NetWorkIndex;


    for(i=0; i < u16IDTableArraySize; i++)
    {
        if (pMuxTable[i].u32Frequency == u32Freq)
        {
            *pu16IDIndex = i;
            return TRUE;
        }
    }

    *pu16IDIndex = INVALID_IDINDEX;

    return FALSE;
}

#if ENABLE_DVBC
//****************************************************************************
/// check the source frequency is inside the range of comparing frequency
/// @param u32SrcFreq \b IN: souce frequency
/// @param U32CompFreq \b IN: compare frequency
/// @return BOOLEAN: TRUE: inside FALSE: outside
//****************************************************************************
static BOOLEAN IsFreqInsideOffsetRange(U32 u32SrcFreq, U32 u32CompFreq)
{
    U32 u32Min, u32Max;
    if ((u32CompFreq>=FREQ_OFFSET_RANGE) && (u32CompFreq-FREQ_OFFSET_RANGE>MIN_DVBC_FREQUENCY))
        u32Min = u32CompFreq-FREQ_OFFSET_RANGE;
    else
        u32Min = MIN_DVBC_FREQUENCY;

    if ((u32CompFreq+FREQ_OFFSET_RANGE)<MAX_DVBC_FREQUENCY)
        u32Max = u32CompFreq+FREQ_OFFSET_RANGE;
    else
        u32Max = MAX_DVBC_FREQUENCY;

    if ((u32SrcFreq>=u32Min) && (u32SrcFreq<=u32Max))
        return TRUE;
    else
        return FALSE;
}

BYTE msAPI_CM_RemoveQuickInstallMismatchedProgram(WORD *pwServiceID, U8 cCountOfServiceID, BYTE cRFChannelNumber, MEMBER_SERVICETYPE eServiceType)
{
    WORD wIDIndex;
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD wServiceId;
    WORD i;
    BYTE j;
    BYTE cRemovedProgramCount;

    if( FALSE == IsServiceTypeValid(eServiceType) ||
        FALSE == IsPhysicalChannelNumberValid(cRFChannelNumber) )
    {
        return 0;
    }

    wIDIndex = cRFChannelNumber;

    if( msAPI_CM_GetMuxMaxNumber() <= wIDIndex )
    {
        return 0;
    }

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);



    cRemovedProgramCount = 0;
    wProgramCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;

    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(eServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;

        wIDIndex = pstProgramIndexTable[wOrder].cIDIndex;

        if (wIDIndex == cRFChannelNumber)
        {
            wServiceId = pstProgramIndexTable[wOrder].wService_ID;

            for(j=0; j < cCountOfServiceID; j++)
            {
                if(pwServiceID[j] == wServiceId)
                {
                    break;
                }
            }
            if( cCountOfServiceID <= j )
            {
                RemoveProgram(eServiceType, wPosition);
                cRemovedProgramCount++;
            }
        }
        wPosition--;
    }

    return cRemovedProgramCount;
}

void msAPI_CM_RemoveQuickInstallMismatchedTS(U16 *pu16TsIds, U8 u8TsIdNum)
{
    U8 index3;
    U16 u16IDIndex, index2;
    WORD wTsId,wTotalServiceNumber,wOrder;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    for(u16IDIndex = 0; u16IDIndex < u16IDTableArraySize; ++ u16IDIndex )
    {
        wTsId = pMuxTable[u16IDIndex].wTransportStream_ID;

        if(wTsId == INVALID_TS_ID)
            continue;//TODO: Check if continue is needed or break is needed

        for(index2 = 0; index2 < u8TsIdNum; index2++)
        {
            if(pu16TsIds[index2] == wTsId)
                break;
        }

        if(index2 >= u8TsIdNum)
        {
            wTotalServiceNumber = CountProgram(E_SERVICETYPE_DTV, INCLUDE_ALL);
            for(index3 = 0; index3 < wTotalServiceNumber; index3++)
            {
                wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, index3);
                if( wOrder >= u16ProgramIndexTableArraySize )
                    continue;

                if(u16IDIndex == pstProgramIndexTable[wOrder].cIDIndex)
                {
                    RemoveProgram(E_SERVICETYPE_DTV, index3);
                    --index3;
                    --wTotalServiceNumber;
                }
            }

            wTotalServiceNumber = CountProgram(E_SERVICETYPE_RADIO, INCLUDE_ALL);
            for(index3 = 0; index3 < wTotalServiceNumber; index3++)
            {
                wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, index3);
                if( wOrder >= u16ProgramIndexTableArraySize )
                    continue;

                if(u16IDIndex == pstProgramIndexTable[wOrder].cIDIndex)
                {
                    RemoveProgram(E_SERVICETYPE_RADIO, index3);
                    --index3;
                    --wTotalServiceNumber;
                }
            }

        #if (NORDIG_FUNC)
            wTotalServiceNumber = CountProgram(E_SERVICETYPE_DATA, INCLUDE_ALL);
            for(index3 = 0; index3 < wTotalServiceNumber; index3++)
            {
                wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, index3);
                if( wOrder >= u16ProgramIndexTableArraySize )
                    continue;

                if(u16IDIndex == pstProgramIndexTable[wOrder].cIDIndex)
                {
                    RemoveProgram(E_SERVICETYPE_DATA, index3);
                    --index3;
                    --wTotalServiceNumber;
                }
            }
        #endif
        }
    }
}

#if ENABLE_T_C_CHANNEL_MIX
BOOLEAN msAPI_CM_RemoveDTVProgramOfAntenna(void)
{
    WORD i;

    for (i=0; i < (MAX_DTVIDTABLE_MAP); i++)
    {
        m_acDTVIDtableMap[i] = 0x00;
    }

  #if ENABLE_T_C_CHANNEL_MIX
    for (i=0; i < MAX_DTVPROGRAM; i++)
    {
        if( ((m_astDTVProgramIndexTable[i].bIsTerrestrial==FALSE) && IsDVBCInUse())
            || (m_astDTVProgramIndexTable[i].bIsTerrestrial && (IsDVBCInUse()==FALSE)) )
            m_acDTVProgramTableMap[i/8] &= (~(0x01 << (i%8)));
    }
  #endif

#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {
        SetNVRAM(BASEADDRESS_PR_DTV_C_PRTABLEMAP, m_acDTVProgramTableMap_DVBC, sizeof(m_acDTVProgramTableMap_DVBC));
    }
    else
#endif
    {
        SetNVRAM(BASEADDRESS_PR_DTVPRTABLEMAP, m_acDTVProgramTableMap, sizeof(m_acDTVProgramTableMap));
    }

    LogicalChannelNumberIsArranged(FALSE);

    for (i=0; i < MAX_DTVPROGRAM; i++)
    {
        if( (m_acDTVProgramTableMap[i/8] & (0x01 << (i%8))) != 0x00 )
        {
            m_acDTVIDtableMap[m_astDTVProgramIndexTable[i].cIDIndex/8] |= (0x01 << (m_astDTVProgramIndexTable[i].cIDIndex%8));
        }
        else
        {
            m_astDTVProgramIndexTable[i].bServiceType = E_SERVICETYPE_INVALID;
            m_astDTVProgramIndexTable[i].bServiceTypePrio = E_SERVICETYPE_PRIORITY_NONE;
            m_astDTVProgramIndexTable[i].wPRIndex = INVALID_PRINDEX;
        }
    }

    for(i=0; i < msAPI_CM_GetMuxMaxNumber(); i++)
    {
        if( (m_acDTVIDtableMap[i/8] & (0x01 << (i%8))) == 0x00 )
        {
            FillProgramIDWithDefault(&_astDTVProgramIDTable[i]);
            SetIDTable(i, (BYTE *)&_astDTVProgramIDTable[i], E_DATA_ID_TABLE);
            if(_astDTVProgramIDTable[i].cNetWorkIndex < MAX_NETWOEK_NUMBER)
            {
                FillNetworkWithDefault(&_astDTVNetwork[_astDTVProgramIDTable[i].cNetWorkIndex]);
                SetIDTable(_astDTVProgramIDTable[i].cNetWorkIndex, (BYTE *)&_astDTVNetwork[_astDTVProgramIDTable[i].cNetWorkIndex], E_DATA_NETWORK);
            }
        }
    }

    SetNVRAM(BASEADDRESS_PR_DTVIDTABLEMAP, m_acDTVIDtableMap, sizeof(m_acDTVIDtableMap));

    m_eCurrentServiceType = DEFAULT_CURRENT_SERVICETYPE;
    m_wCurrentOrderOfTV = DEFAULT_CURRENT_ORDER_TV;
    SaveCurrentOrderOfTV(m_wCurrentOrderOfTV);
    m_wPastOrderOfTV = m_wCurrentOrderOfTV;

    m_wCurrentOrderOfRadio = DEFAULT_CURRENT_ORDER_RADIO;
    SaveCurrentOrderOfRadio(m_wCurrentOrderOfRadio);
    m_wPastOrderOfRadio = m_wCurrentOrderOfRadio;
    m_wCurrentOrderOfData = DEFAULT_CURRENT_ORDER_DATA;
    SaveCurrentOrderOfData(m_wCurrentOrderOfData);
    m_wPastOrderOfData = m_wCurrentOrderOfData;

    #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())
    {   //printf("\n~~~ ResetAllProgram CATV...\n");
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awDVBCProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    }
    else
    {   //printf("\n~~~ ResetAllProgram DTV...\n");
        m_awProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

        m_awProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

        m_awProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
        m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    }
    #else
    m_awProgramCount[E_CM_SERVICE_POS_DTV][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DTV][INCLUDE_ALL] = 0;

    m_awProgramCount[E_CM_SERVICE_POS_RADIO][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_RADIO][INCLUDE_ALL] = 0;

    m_awProgramCount[E_CM_SERVICE_POS_DATA][EXCLUDE_NOT_VISIBLE_AND_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_NOT_VISIBLE_EXCLUDE_DELETED] = 0;
    m_awProgramCount[E_CM_SERVICE_POS_DATA][INCLUDE_ALL] = 0;
    #endif

    //clear unsupported ISO639 language code
    //msAPI_CM_ResetUnsupportedIso639Code();

    return TRUE;
}
#endif
#endif

BOOLEAN msAPI_CM_ResetAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    WORD wOrder,wPRIndex;
    CHANNEL_ATTRIBUTE stAttribute;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//(ENABLE_S2)
    if(IsS2InUse())
    {
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    }
    else
#endif
    {
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
    }

    if(GetProgramTable(wPRIndex, (BYTE *)&stAttribute, E_DATA_MISC))
    {
        stAttribute.bIsDelete  =  DEFAULT_IS_DELETED;
        stAttribute.bIsSkipped =  DEFAULT_IS_SKIPPED;
        stAttribute.bIsLock    =  DEFAULT_IS_LOCKED;
        stAttribute.bIsMove    =  DEFAULT_IS_MOVED;

        if(SetProgramTable(wPRIndex, (BYTE *)&stAttribute, E_DATA_MISC))
        {
        #if 0//(ENABLE_S2)
            if(IsS2InUse())
            {
                m_astS2ProgramIndexTable[wOrder].bIsDelete  = DEFAULT_IS_DELETED;
                m_astS2ProgramIndexTable[wOrder].bIsSkipped = DEFAULT_IS_SKIPPED;
                m_astS2ProgramIndexTable[wOrder].bIsLock     = DEFAULT_IS_LOCKED;
                m_astS2ProgramIndexTable[wOrder].bIsMove     = DEFAULT_IS_MOVED;
            }
            else
        #endif
            {
                pstProgramIndexTable[wOrder].bIsDelete  = DEFAULT_IS_DELETED;
                pstProgramIndexTable[wOrder].bIsSkipped = DEFAULT_IS_SKIPPED;
                pstProgramIndexTable[wOrder].bIsLock    = DEFAULT_IS_LOCKED;
                pstProgramIndexTable[wOrder].bIsMove    = DEFAULT_IS_MOVED;
            }
            return TRUE;
        }
    }

    return FALSE;
}

//****************************************************************************
///  Check if LCN exist in CM
/// @param bServiceType \b IN: service type
/// - @see MEMBER_SERVICETYPE
/// @param wLCN \b IN: logical channel number
/// @return BOOLEAN : Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_IsLCNExit(MEMBER_SERVICETYPE bServiceType, WORD wLCN, WORD *pPosition)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    DTVPROGRAMINDEX * pstProgramIndexTable;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if( wOrder >= u16ProgramIndexTableArraySize )
            continue;


    #if 0//(ENABLE_S2)
        if(IsS2InUse())
        {
            if( wLCN == m_astS2ProgramIndexTable[wOrder].wLCN )
            {
                return TRUE;
            }
        }
        else
    #endif
        {
            WORD wTmpLCN;

          #if (ASTRA_HD_ENABLE)
            if(GetASTRA_HD_ENABLE())
            {
                wTmpLCN = msAPI_CM_GetOriginalLogicalChannelNumber(bServiceType,wPosition);
            }
            else
          #endif
            {
                wTmpLCN = pstProgramIndexTable[wOrder].wLCN;
            }
            if( wLCN == wTmpLCN )
            {
                *pPosition=wPosition;
                return TRUE;
            }
        }
    }

    return FALSE;
}

#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
BYTE msAPI_CM_GetOriginalRFnumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
#if 1//(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    U8 u8Original_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;

    TypDtvDbSel eCurDbSel = CUR_DB_SEL();
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);

    if( FALSE == msAPI_DtvSys_Get_IDTable_ByServiceAndPos(eCurDbSel, bServiceType, wPosition, (BYTE *) &u8Original_RF, E_DATA_ORIGINAL_PCN) )
    {
        u8Original_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    return u8Original_RF;

#else

    WORD wOrder;
    WORD cIDIndex;
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
#if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
#endif

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }
    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
    {
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
    if( cIDIndex >= u16IDTableArraySize )
    {
        return INVALID_PHYSICAL_CHANNEL_NUMBER;
    }

    return pMuxTable[cIDIndex].cOriginal_RF;
#endif
}

BOOLEAN msAPI_CM_ResetOriginalRFnumber(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    WORD wOrder;
    WORD cIDIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if(wOrder >= u16ProgramIndexTableArraySize)
        return FALSE;

    cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
    if(cIDIndex >= u16IDTableArraySize)
        return FALSE;

    pMuxTable[cIDIndex].cOriginal_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;

    if(TRUE == msAPI_CM_SetIDTable(cIDIndex,(BYTE *)&pMuxTable[cIDIndex].cOriginal_RF, E_DATA_ORIGINAL_PCN))
    {
        return TRUE;
    }

    return FALSE;
}

BOOLEAN msAPI_CM_ResetAlternativeTime(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    WORD wOrder;
    WORD cIDIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if(wOrder >= u16ProgramIndexTableArraySize)
        return FALSE;

    cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
    if(cIDIndex >= u16IDTableArraySize)
        return FALSE;


    pMuxTable[cIDIndex].dwAlternativeTime = INVALID_ALTERNATIVETIME;

    if(TRUE == msAPI_CM_SetIDTable(cIDIndex,(BYTE *)&pMuxTable[cIDIndex].dwAlternativeTime, E_DATA_ALTERNATIVE_TIME))
    {
        return TRUE;
    }

    return FALSE;
}

U32 msAPI_CM_GetAlternativeTime(MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    WORD wOrder;
    WORD cIDIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return INVALID_ALTERNATIVETIME;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return INVALID_ALTERNATIVETIME;
    }

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if(wOrder >= u16ProgramIndexTableArraySize)
        return INVALID_ALTERNATIVETIME;

    cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
    if(cIDIndex >= u16IDTableArraySize)
        return INVALID_ALTERNATIVETIME;

    return pMuxTable[cIDIndex].dwAlternativeTime;
}
#endif

#if NTV_FUNCTION_ENABLE
BOOLEAN msAPI_CM_IS_NorwegianNetwork(BYTE cNetworkIndex)
{
    WORD wIDIndex;
    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);


    if( cNetworkIndex >= u16NetWorkTableArraySize )
    {
        //printf("overflow max NetworkIndex\n");
        return FALSE;
    }

    for(wIDIndex=0; wIDIndex < u16IDTableArraySize; wIDIndex++)
    {
        if(pMuxTable[wIDIndex].cRFChannelNumber == INVALID_PHYSICAL_CHANNEL_NUMBER)
        {
            //return FALSE;
            continue;
        }

        if( (cNetworkIndex == pMuxTable[wIDIndex].cNetWorkIndex)
          &&(pMuxTable[wIDIndex].wOriginalNetwork_ID == 0x2242))
        {
            return TRUE;
        }
    }

    return FALSE;
}

//****************************************************************************
///  Get Favorite Region
/// @return Favorite Region
//****************************************************************************
BYTE msAPI_CM_Get_FavoriteNetwork(void)
{
    TypDtvDbSel eCurDtvDbSel = msAPI_DTV_Comm_Get_DBSel();
    return s_au8FavoriteNetwork[eCurDtvDbSel];
    //return _cFavoriteNetwork;
}

//****************************************************************************
///  Set Favorite Region
/// @param cNetworkIndex \b IN: Favorite Region
//****************************************************************************
void msAPI_CM_Set_FavoriteNetwork(BYTE cNetworkIndex)
{
    //_cFavoriteNetwork = cNetworkIndex;
    TypDtvDbSel eCurDtvDbSel = msAPI_DTV_Comm_Get_DBSel();
    s_au8FavoriteNetwork[eCurDtvDbSel] = cNetworkIndex;

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    msAPI_DtvDB_Set_FavoriteRegion(eCurDtvDbSel, cNetworkIndex);
#else
    SetNVRAM(BASEADDRESS_PR_FAVORITE_REGION, (BYTE *)&cNetworkIndex, sizeof(cNetworkIndex));
#endif
}

static void msAPI_CM_FillMove_AttributeWithDefault(MEMBER_SERVICETYPE bServiceType)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD wPRIndex;
    CHANNEL_ATTRIBUTE stCHAttribute;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
        if(wOrder >= u16ProgramIndexTableArraySize)
            continue;

        if( TRUE == pstProgramIndexTable[wOrder].bIsMove )
        {
            pstProgramIndexTable[wOrder].bIsMove = DEFAULT_IS_MOVED;
            wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

            if( FALSE == GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC) )
                continue;

            stCHAttribute.bIsMove = pstProgramIndexTable[wOrder].bIsMove;

            if(FALSE == SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC))
            {
                __ASSERT(0);
            }
        }
    }

}

void msAPI_CM_RestoreProgramOrder(void)
{
    msAPI_CM_FillMove_AttributeWithDefault(E_SERVICETYPE_DTV);
    msAPI_CM_FillMove_AttributeWithDefault(E_SERVICETYPE_RADIO);
#if 1//NORDIG_FUNC
    msAPI_CM_FillMove_AttributeWithDefault(E_SERVICETYPE_DATA);
#endif
    msAPI_CM_ArrangeDataManager(TRUE,FALSE);
}

static void _msAPI_CM_RestoreLCN(MEMBER_SERVICETYPE bServiceType)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD wPRIndex;
    WORD wLCN;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        if(wOrder >= u16ProgramIndexTableArraySize)
            continue;

        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;


        if(FALSE == GetProgramTable(wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN))
        {
            //__ASSERT(0);
            continue;
        }

        pstProgramIndexTable[wOrder].wLCN = wLCN;

        if(FALSE == SetProgramTable(wPRIndex, (BYTE *)&wLCN, E_DATA_LCN))
        {
            //__ASSERT(0);
            continue;
        }
    }
}

void msAPI_CM_RestoreLCN(void)
{
    _msAPI_CM_RestoreLCN(E_SERVICETYPE_DTV);
    _msAPI_CM_RestoreLCN(E_SERVICETYPE_RADIO);
#if 1//NORDIG_FUNC
    _msAPI_CM_RestoreLCN(E_SERVICETYPE_DATA);
#endif
}
#endif

#if ENABLE_TARGET_REGION
void msAPI_CM_SetRegion(WORD wONID, WORD wTSID, WORD wSID, BYTE cValue)
{
    U16 u16Order;
    DTV_CHANNEL_INFO DTVProgramData;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    //printf("%s onid %x tsid %x sid %x cValue %x\n",__FUNCTION__,
    //  wONID,  wTSID,  wSID,  cValue);
    for( u16Order = 0; u16Order < u16ProgramIndexTableArraySize; u16Order ++)
    {
        if(IsProgramEntityActive(pstProgramIndexTable[u16Order].wPRIndex))
        {
            if( GetProgramTable(pstProgramIndexTable[u16Order].wPRIndex, (BYTE *)&DTVProgramData, E_DATA_ALL) )
            {
                //printf("check onid %x tsid %x sid %x(%d) %x\n",
                //  _astDTVProgramIDTable[DTVProgramData.bIDIdex].wOriginalNetwork_ID, _astDTVProgramIDTable[DTVProgramData.bIDIdex].wTransportStream_ID
                //  , DTVProgramData.wService_ID, DTVProgramData.bIDIdex,DTVProgramData.stCHAttribute.cRegion);
                if((pMuxTable[DTVProgramData.bIDIdex].wTransportStream_ID == wTSID) &&
                    (pMuxTable[DTVProgramData.bIDIdex].wOriginalNetwork_ID == wONID) &&
                    ((wSID==0)||(wSID==DTVProgramData.wService_ID))&&
                    (((DTVProgramData.stCHAttribute.cRegion&cValue)!=cValue)||(cValue==0)))
                {
                    if(cValue)
                    {
                        DTVProgramData.stCHAttribute.cRegion|=cValue;
                    }
                    else
                    {
                        DTVProgramData.stCHAttribute.cRegion=cValue;
                    }

                    SetProgramTable(pstProgramIndexTable[u16Order].wPRIndex, (BYTE *)&DTVProgramData, E_DATA_ALL);
                    //printf("onid %x tsid %x sid %x cValue %x(%x)\n",wONID,wTSID,wSID,cValue,DTVProgramData.stCHAttribute.cRegion);
                }
            }
        }
    }

/*
printf("dddddddddddddddddddddd\n");
    for(i=0; i< MAX_DTVPROGRAM; i++)
    {
        if(IsProgramEntityActive(m_astDTVProgramIndexTable[i].wPRIndex))
        {
            if( GetProgramTable(m_astDTVProgramIndexTable[i].wPRIndex, (BYTE *)&DTVProgramData, E_DATA_ALL) )
            {
                printf("tsid %x sid %x name %s index %d cRegion %x\n",_astDTVProgramIDTable[DTVProgramData.bIDIdex].wTransportStream_ID,DTVProgramData.wService_ID,
                    DTVProgramData.bChannelName,DTVProgramData.bIDIdex,
                    DTVProgramData.stCHAttribute.cRegion);
            }
        }
    }
    printf("xxxxxxxxxxxdddddddddddddddddddddd\n");
*/

}

#endif

BOOLEAN msAPI_CM_UpdateLCDV2(U8* pu8Country, U8 u8RegionId)
{
    WORD wProgramCount, wPosition, wOrder, wPreLCN, wLCN;
    U8 i, j;
    BOOLEAN bflag;
    LOGICAL_CHANNEL_V2 mLCDV2[LCDV2ArrayMaxSize];

    memset(mLCDV2, 0, sizeof(mLCDV2));
    msAPI_SI_GetLCDV2(mLCDV2);

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);


    for(i = 0; i < LCDV2ArrayMaxSize; i++)
    {
        if(memcmp(mLCDV2[i].u8CountryCode2, pu8Country, 3) != 0 || mLCDV2[i].u8ChanListId != u8RegionId)
        {
            continue;
        }

        //printf("[mstar][%s][%d] mathch contry:%c%c%c, regionid:%d\n", __FUNCTION__, __LINE__,
         //   pu8Country[0],pu8Country[1],pu8Country[2], u8RegionId);

        for(j = 0; j < mLCDV2[i].u8Count; j++)
        {
            bflag = FALSE;
            wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);

            for(wPosition = 0; wPosition < wProgramCount; wPosition++)
            {
                wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);

                if( wOrder >= u16ProgramIndexTableArraySize )
                    break;

                if(pstProgramIndexTable[wOrder].wService_ID == mLCDV2[i].list[j].u16ServiceID)
                {
                    GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wPreLCN, E_DATA_TS_LCN);
                    wLCN = mLCDV2[i].list[j].u16LCNNumber;
                    //printf("[mstar][%s][%d] prelcn:%d, curlcn:%d \n", __FUNCTION__, __LINE__, wPreLCN, wLCN);
                    if( TRUE == IsLogicalChannelNumberValid(wLCN))
                    {
                        if(wPreLCN != wLCN)
                        {
                            SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN);
                        }
                    }
                    bflag = TRUE;
                    break;
                }
            }
            if(bflag)
            {
                continue;
            }

            wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
            for(wPosition = 0; wPosition < wProgramCount; wPosition++)
            {
                wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, wPosition);

                if( wOrder >= u16ProgramIndexTableArraySize )
                    break;

                if(pstProgramIndexTable[wOrder].wService_ID == mLCDV2[i].list[j].u16ServiceID)
                {
                    GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wPreLCN, E_DATA_TS_LCN);
                    wLCN = mLCDV2[i].list[j].u16LCNNumber;
                    //printf("[mstar][%s][%d] prelcn:%d, curlcn:%d \n", __FUNCTION__, __LINE__, wPreLCN, wLCN);
                    if( TRUE == IsLogicalChannelNumberValid(wLCN))
                    {
                        if(wPreLCN != wLCN)
                        {
                            SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN);
                        }
                    }
                    bflag = TRUE;
                    break;
                }
            }
            if(bflag)
            {
                continue;
            }

            wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);
            for(wPosition = 0; wPosition < wProgramCount; wPosition++)
            {
                wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition);

                if( wOrder >= u16ProgramIndexTableArraySize )
                    break;

                if(pstProgramIndexTable[wOrder].wService_ID == mLCDV2[i].list[j].u16ServiceID)
                {
                    GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wPreLCN, E_DATA_TS_LCN);
                    wLCN = mLCDV2[i].list[j].u16LCNNumber;
                    //printf("[mstar][%s][%d] prelcn:%d, curlcn:%d \n", __FUNCTION__, __LINE__, wPreLCN, wLCN);
                    if( TRUE == IsLogicalChannelNumberValid(wLCN))
                    {
                        if(wPreLCN != wLCN)
                        {
                            SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN);
                        }
                    }
                    break;
                }
            }
        }
    }

    msAPI_CM_ArrangeDataManager(TRUE,FALSE);

    return TRUE;
}

#if (ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)
BOOLEAN msAPI_CM_UpdateLCNByChannellistId(U16 u16ChannellistId)
{
    WORD wProgramCount, wPosition, wOrder, wPreLCN, wLCN;
    U16 i, wServiceID;
    U16 _u16MaxAstraServiceCount = msAPI_CM_GetAstraServiceCount();
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    printf("[%s][%d] u16ChannellistId:%d \n", __FUNCTION__, __LINE__, u16ChannellistId);
    //msAPI_CM_DebugArrange();

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    for(wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
        wServiceID = pstProgramIndexTable[wOrder].wService_ID;
        for(i = 0; i < _u16MaxAstraServiceCount; i++)
        {
            if (_astServiceInfo[i].u16ServiceListID == u16ChannellistId && _astServiceInfo[i].stServiceInfo.stTripleIds.u16SrvId == wServiceID)
            {
                GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wPreLCN, E_DATA_LCN);
                wLCN = _astServiceInfo[i].stServiceInfo.u16LCN;
                if( TRUE == IsLogicalChannelNumberValid(wLCN))
                {
                    if(wPreLCN != wLCN)
                    {
                        printf("-%s,%d,ServiceID=%d,wLCN=%d,wPreLCN=%d,wPRIndex=%d \n",__FUNCTION__,__LINE__,_astServiceInfo[i].stServiceInfo.stTripleIds.u16SrvId,wLCN,wPreLCN,pstProgramIndexTable[wOrder].wPRIndex);
                        SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_LCN);
                    }
                }
                break;
            }
        }
    }

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    for(wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, wPosition);
        wServiceID = pstProgramIndexTable[wOrder].wService_ID;
        for(i = 0; i < _u16MaxAstraServiceCount; i++)
        {
            if (_astServiceInfo[i].u16ServiceListID == u16ChannellistId && _astServiceInfo[i].stServiceInfo.stTripleIds.u16SrvId == wServiceID)
            {
                GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wPreLCN, E_DATA_LCN);
                wLCN = _astServiceInfo[i].stServiceInfo.u16LCN;
                if( TRUE == IsLogicalChannelNumberValid(wLCN))
                {
                    if(wPreLCN != wLCN)
                    {
                        printf("-%s,%d,ServiceID=%d,wLCN=%d,wPreLCN=%d,wPRIndex=%d \n",__FUNCTION__,__LINE__,_astServiceInfo[i].stServiceInfo.stTripleIds.u16SrvId,wLCN,wPreLCN,pstProgramIndexTable[wOrder].wPRIndex);
                        SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_LCN);
                    }
                }
                break;
            }
        }
    }

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);
    for(wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition);
        wServiceID = pstProgramIndexTable[wOrder].wService_ID;
        for(i = 0; i < _u16MaxAstraServiceCount; i++)
        {
            if (_astServiceInfo[i].u16ServiceListID == u16ChannellistId && _astServiceInfo[i].stServiceInfo.stTripleIds.u16SrvId == wServiceID)
            {
                GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wPreLCN, E_DATA_LCN);
                wLCN = _astServiceInfo[i].stServiceInfo.u16LCN;
                if( TRUE == IsLogicalChannelNumberValid(wLCN))
                {
                    if(wPreLCN != wLCN)
                    {
                        printf("-%s,%d,ServiceID=%d,wLCN=%d,wPreLCN=%d,wPRIndex=%d \n",__FUNCTION__,__LINE__,_astServiceInfo[i].stServiceInfo.stTripleIds.u16SrvId,wLCN,wPreLCN,pstProgramIndexTable[wOrder].wPRIndex);
                        SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_LCN);
                    }
                }
                //break;   //display last one
            }
        }
    }

    msAPI_CM_ArrangeDataManager(TRUE,FALSE);

    return TRUE;
}



#if 0
static BOOLEAN msAPI_CM_ResetInvalidLCN(MEMBER_SERVICETYPE bServiceType, WORD wOriinalLCN)
{
    WORD wPosition;
    WORD wProgramCount;
    WORD wOrder, wNewlcn;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    wNewlcn = wOriinalLCN;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    for( wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

        if( 0 == pstProgramIndexTable[wOrder].wLCN || INVALID_LOGICAL_CHANNEL_NUMBER == pstProgramIndexTable[wOrder].wLCN )
        {
            pstProgramIndexTable[wOrder].wLCN = wNewlcn;
            SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wNewlcn, E_DATA_LCN);
            wNewlcn++;
        }
    }

    return TRUE;
}
#endif
static void RemoveServicebyLcnAssignmentType(MEMBER_SERVICETYPE bServiceType ,U8 u8LcnAssinmentType)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD i;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    printf("RemoveServicebyLcnAssignmentType\n");
    if( FALSE == IsServiceTypeValid(bServiceType))
    {
        return ;
    }
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
		{
        if(pstProgramIndexTable[wOrder].eLCNAssignmentType & u8LcnAssinmentType)
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            RemoveProgram(bServiceType, wPosition);
        }
        }
        wPosition--;
    }

}

static void DeleteInvalidLCNService(MEMBER_SERVICETYPE bServiceType ,U8 u8LcnAssinmentType)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD wOrder;
    WORD i;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    if( FALSE == IsServiceTypeValid(bServiceType))
    {
        return ;
    }
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        {
            if(pstProgramIndexTable[wOrder].eLCNAssignmentType & u8LcnAssinmentType)
            {
                #if ( WATCH_DOG == ENABLE )
                msAPI_Timer_ResetWDT();
                #endif

                msAPI_CM_DeleteProgram(bServiceType, wPosition, TRUE);
            }
        }
        wPosition--;
    }
}

#endif


BOOLEAN msAPI_CM_IS_SID_Unique_Country(void)
{
    return IS_SID_UNIQUE_COUNTRY(m_eCountry);
}

#if 0//(ENABLE_API_DTV_SYSTEM_2015)
// Search program by NetworkId and ServiceId, then return Order
U16 msAPI_CM_Find_Prog_By_NetworkId_And_ServiceId(TypDtvDbSel eDtvDbSel, WORD wOriginalNetwork_ID, WORD wService_ID)
{
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    DTVPROGRAMID_M * pstIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16IDTableArray = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);

}
#endif

BOOLEAN msAPI_CM_IsAVCService(WORD wOriginalNetwork_ID, WORD wService_ID)
{
    TypDtvDbSel eDtvDbSel = msAPI_DTV_Comm_Get_DBSel();

    WORD i;
    WORD cIDIndex;
    MEMBER_SERVICETYPE bServiceType;
    WORD wPosition,wProgramCount,wOrder;

#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
#else
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = m_astDTVProgramIndexTable;
    DTVPROGRAMID_M *pMuxTable=_astDTVProgramIDTable;
 #if DVB_T_C_DIFF_DB
    if (IsDVBCInUse())pMuxTable=_astDTVCProgramIDTable;
 #endif
#endif


    bServiceType=E_SERVICETYPE_DTV;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        // Get Order
        //wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);

        //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        cIDIndex = pstDTVProgramIndexTable[wOrder].cIDIndex;

        if(pMuxTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
        {
            //if(wService_ID == m_astDTVProgramIndexTable[wOrder].wService_ID)
            if(wService_ID == pstDTVProgramIndexTable[wOrder].wService_ID)
            {
                //if(m_astDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_HIGH
                //|| m_astDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_MIDDLE)
                if(pstDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_HIGH
                || pstDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_MIDDLE)
                {
                    return TRUE;
                }
                return FALSE;
            }
        }
        wPosition--;
    }

    bServiceType=E_SERVICETYPE_RADIO;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        //wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);

        //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        cIDIndex = pstDTVProgramIndexTable[wOrder].cIDIndex;

        if(pMuxTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
        {
            //if(wService_ID == m_astDTVProgramIndexTable[wOrder].wService_ID)
            if(wService_ID == pstDTVProgramIndexTable[wOrder].wService_ID)
            {
                //if(m_astDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_HIGH
                //|| m_astDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_MIDDLE)
                if(pstDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_HIGH
                || pstDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_MIDDLE)
                {
                    return TRUE;
                }
                return FALSE;

            }
        }
        wPosition--;
    }

    bServiceType=E_SERVICETYPE_DATA;
    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        //wOrder = ConvertPositionToOrder(bServiceType, wPosition);
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);

        //cIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        cIDIndex = pstDTVProgramIndexTable[wOrder].cIDIndex;

        if(pMuxTable[cIDIndex].wOriginalNetwork_ID==wOriginalNetwork_ID)
        {
            //if(wService_ID == m_astDTVProgramIndexTable[wOrder].wService_ID)
            if(wService_ID == pstDTVProgramIndexTable[wOrder].wService_ID)
            {
                //if(m_astDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_HIGH
                //|| m_astDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_MIDDLE)
                if(pstDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_HIGH
                || pstDTVProgramIndexTable[wOrder].bServiceTypePrio == E_SERVICETYPE_PRIORITY_MIDDLE)
                {
                    return TRUE;
                }
                return FALSE;

            }
        }
        wPosition--;
    }
    return FALSE;
}

BOOLEAN msAPI_CM_RestLCNByRF(WORD* pServiceList, WORD wNumber, BYTE cRFNumber)
{
    WORD wPosition;
    WORD wOrder;
    WORD wProgramCount;
    MEMBER_SERVICETYPE eServiceType;
    BYTE cRFIndex;
    WORD i,j;
    BOOLEAN bRet=FALSE;
    BOOLEAN bReset;
    WORD wLCN=INVALID_LOGICAL_CHANNEL_NUMBER;

    WORD wTS_ID,wON_ID;
    U8 u8PLP_ID,u8HpLp_ID,u8PLP_ID_DB,u8HpLp_ID_DB;
    msAPI_SI_Get_PLP_ID(&u8PLP_ID);
    u8HpLp_ID=msAPI_SI_Get_HpLp();

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


    for(i=0;i<3;i++)
    {
        if(i==0)eServiceType=E_SERVICETYPE_DTV;
        else if(i==1)eServiceType=E_SERVICETYPE_RADIO;
        else eServiceType=E_SERVICETYPE_DATA;

        wProgramCount = msAPI_DTV_GetProgramCount(eServiceType, INCLUDE_ALL);
        for(wPosition=0; wPosition < wProgramCount; wPosition++)
        {
          #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
          #endif

            wOrder = ConvertPositionToOrder(eServiceType, wPosition);
            if(wOrder >= u16ProgramIndexTableArraySize)
                continue;

            if(pstProgramIndexTable[wOrder].bIsMove)
            {
                continue;
            }

            cRFIndex=msAPI_CM_GetPhysicalChannelNumber(eServiceType,wPosition);
            wTS_ID = msAPI_CM_GetTS_ID(eServiceType,wPosition);
            wON_ID = msAPI_CM_GetON_ID(eServiceType,wPosition);
            msAPI_CM_GetPLPID_WithID(wTS_ID,wON_ID,&u8PLP_ID_DB);
            msAPI_CM_GetHpLP_WithID(wTS_ID,wON_ID,&u8HpLp_ID_DB);

            if((cRFIndex == cRFNumber)&&(u8PLP_ID_DB == u8PLP_ID)&&(u8HpLp_ID_DB == u8HpLp_ID))
            {
                if( FALSE == GetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN) )
                    return FALSE;

                if(wLCN == INVALID_LOGICAL_CHANNEL_NUMBER)
                {
                    continue;
                }
                bReset=TRUE;
                for(j=0;j<wNumber;j++)
                {
                    if(pServiceList[j] == pstProgramIndexTable[wOrder].wService_ID)
                    {
                        bReset=FALSE;
                        break;
                    }
                }
                if(bReset)
                {
                    wLCN=INVALID_LOGICAL_CHANNEL_NUMBER;
                    //printf("reset sid %d lcn %d\n",m_astDTVProgramIndexTable[wOrder].wService_ID,
                    //m_astDTVProgramIndexTable[wOrder].wLCN);
                    pstProgramIndexTable[wOrder].wLCN=INVALID_LOGICAL_CHANNEL_NUMBER;
                    pstProgramIndexTable[wOrder].wSimu_LCN=INVALID_SIMULCAST_LOGICAL_CHANNEL_NUMBER;

                    if( FALSE == SetProgramTable(pstProgramIndexTable[wOrder].wPRIndex, (BYTE *)&wLCN, E_DATA_TS_LCN) )
                        return FALSE;

                    bRet=TRUE;
                }
            }

        }
    }

    return bRet;
}

BOOLEAN msAPI_CM_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove, BYTE sat, WORD freq)
//BOOLEAN msAPI_CM_RemoveMux(WORD wNID, WORD *pwTS_ID,  BYTE cCountOfTS, BOOLEAN *bRemove)
{
    // Unused warning
    sat = sat;
    freq = freq;

    BYTE j;
    U16 i;
    WORD dummy1 = 0;
    MEMBER_SERVICETYPE dummy2;


    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    U16 u16NetWorkIndex;


    *bRemove=FALSE;

    memset(&dummy2, 0x00, sizeof(MEMBER_SERVICETYPE)); // fix coverity 207578

    for(i=0; i < u16IDTableArraySize;i++)
    {
        u16NetWorkIndex = pMuxTable[i].cNetWorkIndex;
        if( u16NetWorkIndex >= u16NetWorkTableArraySize )
            continue;


        if(pstNetWorkTable[u16NetWorkIndex].wNetwork_ID== wNID)
        {
            for(j=0;j<cCountOfTS;j++)
            {
                if(pwTS_ID[j] == pMuxTable[i].wTransportStream_ID)
                {
                    break;
                }
            }
            if(j>=cCountOfTS)
            {
                *bRemove=TRUE;
            #if 1//ENABLE_S2
                RemoveMismatchedProgram(E_SERVICETYPE_DTV, i, 0, 0, &dummy1, &dummy2, 0, sat, freq);
                RemoveMismatchedProgram(E_SERVICETYPE_DATA, i, 0, 0, &dummy1, &dummy2, 0, sat, freq);
                RemoveMismatchedProgram(E_SERVICETYPE_RADIO, i, 0, 0, &dummy1, &dummy2, 0, sat, freq);
            #else
                RemoveMismatchedProgram(E_SERVICETYPE_DTV,i, 0, 0, &dummy1, &dummy2, 0);
            #endif

            #if ENABLE_DVBC
                pMuxTable[i].u32Frequency=INVALID_FREQUENCY;
            #endif
                pMuxTable[i].cRFChannelNumber=INVALID_PHYSICAL_CHANNEL_NUMBER;
            }
        }
    }
    return TRUE;
}

#if(ENABLE_S2_CH_CHANGE_TO_SEARCHPOSITION)
BOOLEAN msAPI_CM_S2SetsearchPosition(WORD wPosition)
{
    WORD wOrder = 0; // fix coverity 207470
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = E_DTV_DB_SEL_DVBS;//msAPI_DTV_Comm_Get_DBSel();
#endif

    if(TRUE == s2_IsLinkOfOrderValid())
        GetProgramTable(wPosition, (BYTE *)&wOrder, E_DATA_ORDER);
    else
    {
        WORD tempOrder;

        for( tempOrder=0; tempOrder < MAX_DTV_S2_PROGRAM; tempOrder++)
        {
            if(pstProgramIndexTable[tempOrder].wPRIndex == wPosition)
            {
                wOrder = tempOrder;
                break;
            }
        }
    }
    msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)pstProgramIndexTable[wOrder].bServiceType);

    if(pstProgramIndexTable[wOrder].bServiceType==E_SERVICETYPE_DTV)
    {
        m_wPastOrderOfTV = wOrder;
        m_wCurrentOrderOfTV = wOrder;
        SaveCurrentOrderOfTV(m_wCurrentOrderOfTV);

        msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
        msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
    }
    else if(pstProgramIndexTable[wOrder].bServiceType==E_SERVICETYPE_RADIO)
    {
        m_wPastOrderOfRadio= wOrder;
        m_wCurrentOrderOfRadio= wOrder;
        SaveCurrentOrderOfTV(m_wCurrentOrderOfRadio);

        msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
        msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
    }
    else
    {
        m_wPastOrderOfData= wOrder;
        m_wCurrentOrderOfData= wOrder;
        SaveCurrentOrderOfTV(m_wCurrentOrderOfData);
        msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
        msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
    }
    return TRUE;
}
#endif

#if(ENABLE_S2_FIND_PROGRAM_BYNAME)
WORD msAPI_CM_CountFindProgramByName(MEMBER_SERVICETYPE bServiceType,BYTE *bProgramName)
{
    WORD wProgramCount;
    WORD wFindCount;
    WORD wPosition;
    U8 au8ServiceName[MAX_SERVICE_NAME] = {0},i; // fix coverity 207577
    BOOL result=TRUE;
    MS_U8 u8ProgName_chlist_bak[11];
    U8 tempBuffer_1[MAX_SERVICE_NAME] = {0}; // fix coverity 207466
    U8 u8SpecFlag=0;
    if( FALSE == IsServiceTypeValid(bServiceType) && E_SERVICETYPE_UNITED_TV != bServiceType)
    {
        return 0;
    }
    printf("\r\nbbbbbbbbbbbProgramName=");
    for(i=0;i<5;i++)
    {
        printf("%x ",bProgramName[i]);
    }
    printf("\r\n");
    if(bProgramName[0]==0)
        return 0;
    for(i=0; i<11; i++)
    {
        if(bProgramName[i]>=0x41&&bProgramName[i]<=0x5A)
            u8ProgName_chlist_bak[i] = bProgramName[i] + 0x20;
        else if(bProgramName[i]>=0x61&&bProgramName[i]<=0x7A)
            u8ProgName_chlist_bak[i] = bProgramName[i] - 0x20;
        else
            u8ProgName_chlist_bak[i] = bProgramName[i];
    }

    if (E_SERVICETYPE_UNITED_TV == bServiceType)
    {
        wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }
    else
    {
        wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }

    wFindCount = 0;
    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        if(msAPI_CM_FindProgramByNameGetServiceName(bServiceType, wPosition, (U8 *)au8ServiceName)==TRUE)
        {
            MApp_SI_GetString(tempBuffer_1, MAX_SERVICE_NAME, (U8 *)au8ServiceName, MAX_SERVICE_NAME, KEEP_CONTROL_CODE_NONE);
        }
        if(tempBuffer_1[0]==0x05)
            u8SpecFlag=1;
        else
            u8SpecFlag=0;

        for(i=0;bProgramName[i];i++)
        {
            printf("%c", au8ServiceName[i+u8SpecFlag]);
            if(au8ServiceName[i+u8SpecFlag]!=bProgramName[i]&&au8ServiceName[i+u8SpecFlag]!=u8ProgName_chlist_bak[i])
            {
                printf("%c", au8ServiceName[i+u8SpecFlag]);
                result=FALSE;
                break;
            }
        }
        if(result)
        {
            wFindCount++;
        }
        result=TRUE;
    }
    return wFindCount;
}

U16 msAPI_CM_FindProgramByNameGetProgramAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember)
{
    BOOLEAN bIsValidParameter;
    WORD wOrder;

    WORD DTVcount, Radiocount, Datacount;

    DTVcount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    Radiocount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    Datacount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED);

    if (wPosition < DTVcount)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
    }
    else if (wPosition >= DTVcount && wPosition < DTVcount + Radiocount)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, wPosition);
    }
    else
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition);
    }

    bIsValidParameter = TRUE;
    bIsValidParameter &= IsServiceTypeValid(bServiceType);
    bIsValidParameter &= IsPositionValid(bServiceType, wPosition);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if 1// Use standard api

    return msAPI_CM_GetProgramAttribute_ByOrder(CUR_DB_SEL(), wOrder, eAttributeMember);

#else

    BOOLEAN  bRet;

#if ENABLE_S2
    if(IsS2InUse())
    {
        switch (eAttributeMember)
        {
            case E_ATTRIBUTE_IS_VISIBLE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_VISIBLE_SERVICE_FLAG;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bVisibleServiceFlag;
                }
                break;
            case E_ATTRIBUTE_IS_NUMERIC_SELECTION:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_NUMERIC_SELECTION_FLAG;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bNumericSelectionFlag;
                }
                break;
            case E_ATTRIBUTE_IS_DELETED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_DELETED;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsDelete;
                }
                break;
            case E_ATTRIBUTE_IS_REPLACE_DEL:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_REPLACE_DEL;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsReplaceDel;
                }
                break;
#if (CM_MULTI_FAVORITE)
            case E_ATTRIBUTE_IS_FAVORITE1:
            case E_ATTRIBUTE_IS_FAVORITE2:
            case E_ATTRIBUTE_IS_FAVORITE3:
            case E_ATTRIBUTE_IS_FAVORITE4:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_FAVORITE;
                }
                else
                {
                    bRet = (GETBIT(m_astS2ProgramIndexTable[wOrder].bIsFavorite, eAttributeMember-E_ATTRIBUTE_IS_FAVORITE1) > 0);
                }
                break;
#else
            case E_ATTRIBUTE_IS_FAVORITE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_FAVORITE;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsFavorite;
                }
                break;
#endif
            case E_ATTRIBUTE_IS_SKIPPED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_SKIPPED;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsSkipped;
                }
                break;
            case E_ATTRIBUTE_IS_LOCKED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_LOCKED;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsLock;
                }
                break;
            case E_ATTRIBUTE_IS_SCRAMBLED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_SCRAMBLED;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsScramble;
                }
                break;
            case E_ATTRIBUTE_IS_STILL_PICTURE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_STILL_PICTURE;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsStillPicture;
                }
                break;
            case E_ATTRIBUTE_IS_SERVICE_ID_ONLY:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_SERVICE_ID_ONLY;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsServiceIdOnly;
                }
                break;
            case E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_UNCONFIRMED_SERVICE;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bUnconfirmedService;
                }
                break;
            case E_ATTRIBUTE_IS_INVALID_SERVICE:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_INVALID_SERVICE;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bInvalidService;
                }
                break;
            case E_ATTRIBUTE_IS_MOVED:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_MOVED;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsMove;
                }
                break;
            case E_ATTRIBUTE_IS_SPECIAL_CH:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_SPECIAL_SERVICE;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsSpecialService;
                }
                break;
#if ENABLE_T_C_CHANNEL_MIX
            case E_ATTRIBUTE_IS_TERRESTRIAL:
                if( FALSE == bIsValidParameter )
                {
                    bRet = DEFAULT_IS_CABLE;
                }
                else
                {
                    bRet = m_astS2ProgramIndexTable[wOrder].bIsTerrestrial;
                }
                break;
#endif
            default:
                bRet = FALSE;
            break;
        }
        return bRet;
    }
#endif
    switch(eAttributeMember)
    {
    case E_ATTRIBUTE_IS_VISIBLE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_VISIBLE_SERVICE_FLAG;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bVisibleServiceFlag;
        }
        break;

    case E_ATTRIBUTE_IS_NUMERIC_SELECTION:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_NUMERIC_SELECTION_FLAG;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bNumericSelectionFlag;
        }
        break;

    case E_ATTRIBUTE_IS_DELETED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_DELETED;
        }
        else
        {

            bRet = m_astDTVProgramIndexTable[wOrder].bIsDelete;
        }
        break;
    case E_ATTRIBUTE_IS_REPLACE_DEL:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_REPLACE_DEL;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsReplaceDel;
        }
        break;
#if (CM_MULTI_FAVORITE)
    case E_ATTRIBUTE_IS_FAVORITE1:
    case E_ATTRIBUTE_IS_FAVORITE2:
    case E_ATTRIBUTE_IS_FAVORITE3:
    case E_ATTRIBUTE_IS_FAVORITE4:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_FAVORITE;
        }
        else
        {
            bRet = (GETBIT(m_astDTVProgramIndexTable[wOrder].bIsFavorite, eAttributeMember-E_ATTRIBUTE_IS_FAVORITE1) > 0);
        }
        break;
#else
    case E_ATTRIBUTE_IS_FAVORITE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_FAVORITE;
        }
        else
        {

            bRet = m_astDTVProgramIndexTable[wOrder].bIsFavorite;
        }
        break;
#endif

    case E_ATTRIBUTE_IS_SKIPPED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_SKIPPED;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsSkipped;
        }
        break;

    case E_ATTRIBUTE_IS_LOCKED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_LOCKED;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsLock;
        }
        break;

    case E_ATTRIBUTE_IS_SCRAMBLED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_SCRAMBLED;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsScramble;
        }
        break;

    case E_ATTRIBUTE_IS_STILL_PICTURE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_STILL_PICTURE;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsStillPicture;
        }
        break;

    case E_ATTRIBUTE_IS_REPLACE_SERVICE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_REPLACE_SERVICE;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bReplaceService;
        }
        break;

    case E_ATTRIBUTE_IS_SERVICE_ID_ONLY:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_SERVICE_ID_ONLY;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsServiceIdOnly;
        }
        break;
    case E_ATTRIBUTE_IS_UNCONFIRMED_SERVICE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_UNCONFIRMED_SERVICE;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bUnconfirmedService;
        }
        break;
    case E_ATTRIBUTE_IS_INVALID_SERVICE:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_INVALID_SERVICE;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bInvalidService;
        }
        break;
    case E_ATTRIBUTE_IS_MOVED:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_MOVED;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsMove;
        }
        break;
    case E_ATTRIBUTE_IS_SPECIAL_CH:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_SPECIAL_SERVICE;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsSpecialService;
        }
        break;

#if ENABLE_T_C_CHANNEL_MIX
    case E_ATTRIBUTE_IS_TERRESTRIAL:
        if( FALSE == bIsValidParameter )
        {
            bRet = DEFAULT_IS_CABLE;
        }
        else
        {
            bRet = m_astDTVProgramIndexTable[wOrder].bIsTerrestrial;
        }
        break;
#endif
    case E_ATTRIBUTE_IS_LCN_VALID:
        {
            CHANNEL_ATTRIBUTE Misc;
            memset(&Misc,0,sizeof(CHANNEL_ATTRIBUTE));
            GetProgramTable(wOrder, (BYTE *)&Misc, E_DATA_MISC);
            bRet = Misc.bValidLCN;
        }
        break;
    default:
        bRet = FALSE;
        break;
    }

    return bRet;
#endif
}

BOOLEAN msAPI_CM_FindProgramByNameGetServiceName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * bChannelName)
{
    WORD wOrder,wPRIndex;
    BYTE i;
#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    BOOLEAN bRet = FALSE;
    BYTE aLang[MAX_MULTI_LINGUAL_SERVICE_NAME] = {0};
    BYTE aName[MAX_MULTI_LINGUAL_SERVICE_NAME][MAX_SERVICE_NAME];
#endif

    for(i=0; i < MAX_SERVICE_NAME; i++)
    {
        bChannelName[i] = NULL;
    }

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    //DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);


//////////////////////////bServiceType == E_SERVICETYPE_UNITED_TV
    if (E_SERVICETYPE_UNITED_TV == bServiceType)
    {
        WORD DTVcount, Radiocount, Datacount;

        DTVcount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        Radiocount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
        Datacount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED);

        if (wPosition < DTVcount)
        {
            wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
        }
        else if (wPosition >= DTVcount && wPosition < (DTVcount + Radiocount))
        {
            wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, (wPosition - DTVcount));
        }
        else if (wPosition >= (DTVcount + Radiocount) && wPosition < (DTVcount + Radiocount + Datacount))
        {
            wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition - (DTVcount + Radiocount));
        }
        else
        {
            wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
        }

        if( wOrder >= u16ProgramIndexTableArraySize )
            return FALSE;

    #if 0//ENABLE_S2
        if (IsS2InUse())
        {
            wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
        }
        else
    #endif
        {
            wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
        }

    #if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
        GetProgramTable(wPRIndex, (BYTE *)aLang, E_DATA_NAME_MULTILINGUAL_LANGUAGE);
        GetProgramTable(wPRIndex, (BYTE *)aName, E_DATA_SERVICE_MULTILINGUAL_NAME);
        for(i=0;i<MAX_MULTI_LINGUAL_SERVICE_NAME;i++)
        {
            if(aLang[i]==(U8)GET_OSD_MENU_LANGUAGE())
            {
                memcpy(bChannelName,aName[i],MAX_SERVICE_NAME);
                //printf("index =%x lang %x name %s %x %x %x %x %x\n",i,aLang[i],
                //  aName[i],aName[i][0],aName[i][1],aName[i][2],aName[i][3],aName[i][4]);
                bRet =  TRUE;
            }
        }
        if((bRet==TRUE)&&(bChannelName[0]!=NULL))  //get service name  //check if service name is empty or not
        {
            return bRet;
        }
    #endif

        return GetProgramTable(wPRIndex, (BYTE *)bChannelName, E_DATA_SERVICE_NAME);
    }

//////////////////////////bServiceType != E_SERVICETYPE_UNITED_TV
    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    if( wOrder >= u16ProgramIndexTableArraySize )
        return FALSE;

#if 0//ENABLE_S2
    if (IsS2InUse())
        wPRIndex = m_astS2ProgramIndexTable[wOrder].wPRIndex;
    else
#endif
        wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

#if ENABLE_SAVE_MULTILINGUAL_SERVICE_NAME
    GetProgramTable(wPRIndex, (BYTE *)aLang, E_DATA_NAME_MULTILINGUAL_LANGUAGE);
    GetProgramTable(wPRIndex, (BYTE *)aName, E_DATA_SERVICE_MULTILINGUAL_NAME);
    for(i=0;i<MAX_MULTI_LINGUAL_SERVICE_NAME;i++)
    {
        if(aLang[i]==(U8)GET_OSD_MENU_LANGUAGE())
        {
            memcpy(bChannelName,aName[i],MAX_SERVICE_NAME);
            //printf("index =%x lang %x name %s %x %x %x %x %x\n",i,aLang[i],
            //  aName[i],aName[i][0],aName[i][1],aName[i][2],aName[i][3],aName[i][4]);
            bRet =  TRUE;
        }
    }
    if((bRet==TRUE)&&(bChannelName[0]!=NULL))  //get service name  //check if service name is empty or not
    {
        return bRet;
    }
#endif

    return GetProgramTable(wPRIndex, (BYTE *)bChannelName, E_DATA_SERVICE_NAME);
}

WORD msAPI_CM_GetPrevFindProgramByNamePosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped,BYTE *bProgramName)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD i, k;
    MS_U8 u8ProgName_chlist_bak[11];
    U8 au8ServiceName[MAX_SERVICE_NAME] = {0}; // fix coverity 207580 and 207579
    BOOL result=TRUE;
    U8 tempBuffer_1[MAX_SERVICE_NAME] = {0}; // fix coverity 207469
    U8 u8SpecFlag=0;

    if( FALSE == IsServiceTypeValid(bServiceType) && E_SERVICETYPE_UNITED_TV != bServiceType)
    {
        return INVALID_PROGRAM_POSITION;
    }
    if( FALSE == IsPositionValid(bServiceType, wBasePosition) && E_SERVICETYPE_UNITED_TV != bServiceType)
    {
        return INVALID_PROGRAM_POSITION;
    }
    for(i=0; i<11; i++)
    {
        if(bProgramName[i]>=0x41&&bProgramName[i]<=0x5A)
            u8ProgName_chlist_bak[i] = bProgramName[i] + 0x20;
        else if(bProgramName[i]>=0x61&&bProgramName[i]<=0x7A)
            u8ProgName_chlist_bak[i] = bProgramName[i] - 0x20;
        else
            u8ProgName_chlist_bak[i] = bProgramName[i];
    }

    if (E_SERVICETYPE_UNITED_TV == bServiceType)
    {
        wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }
    else
    {
        wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }

    if( wBasePosition > wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }

    for(i = 0; i < wProgramCount; i++)
    {
        wPosition--;

        if(msAPI_CM_FindProgramByNameGetServiceName(bServiceType, wPosition, (U8 *)au8ServiceName)==TRUE)
        {
            MApp_SI_GetString(tempBuffer_1, MAX_SERVICE_NAME, (U8 *)au8ServiceName, MAX_SERVICE_NAME, KEEP_CONTROL_CODE_NONE);
        }
        if(tempBuffer_1[0]==0x05)
            u8SpecFlag=1;
        else
            u8SpecFlag=0;
        for(k=0;bProgramName[k];k++)
        {
            if(au8ServiceName[k+u8SpecFlag]!=bProgramName[k]&&au8ServiceName[k+u8SpecFlag]!=u8ProgName_chlist_bak[k])
            {
                result=FALSE;
                break;
            }
        }
        if(result)
        {
            //printf("\r\n____findnext=%d",wPosition);
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_FindProgramByNameGetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
        result=TRUE;

        if (wPosition == 0)
        {
            return INVALID_PROGRAM_POSITION;
        }
    }
    return INVALID_PROGRAM_POSITION;
}

WORD msAPI_CM_GetNextFindProgramByNamePosition(MEMBER_SERVICETYPE bServiceType, WORD wBasePosition, BOOLEAN bIncludeSkipped,BYTE *bProgramName)
{
    WORD wProgramCount;
    WORD wPosition;
    WORD i, k;
    MS_U8 u8ProgName_chlist_bak[11];
    U8 au8ServiceName[MAX_SERVICE_NAME] = {0}; // fix coverity 207580 and 207579
    BOOL result=TRUE;
    U8 tempBuffer_1[MAX_SERVICE_NAME] = {0}; // fix coverity 207469
    U8 u8SpecFlag=0;

    if( FALSE == IsServiceTypeValid(bServiceType) && E_SERVICETYPE_UNITED_TV != bServiceType)
    {
        return INVALID_PROGRAM_POSITION;
    }
    if( FALSE == IsPositionValid(bServiceType, wBasePosition) && E_SERVICETYPE_UNITED_TV != bServiceType)
    {
        return INVALID_PROGRAM_POSITION;
    }
    for(i=0; i<11; i++)
    {
        if(bProgramName[i]>=0x41&&bProgramName[i]<=0x5A)
            u8ProgName_chlist_bak[i] = bProgramName[i] + 0x20;
        else if(bProgramName[i]>=0x61&&bProgramName[i]<=0x7A)
            u8ProgName_chlist_bak[i] = bProgramName[i] - 0x20;
        else
            u8ProgName_chlist_bak[i] = bProgramName[i];
    }

    if (E_SERVICETYPE_UNITED_TV == bServiceType)
    {
        wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, EXCLUDE_NOT_VISIBLE_AND_DELETED)
            + msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }
    else
    {
        wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
    }

    if( wBasePosition >= wProgramCount )
    {
        wPosition = wProgramCount;
    }
    else
    {
        wPosition = wBasePosition;
    }

    for(i=0; i< wProgramCount; i++)
    {
        wPosition++;
        if( wPosition > wProgramCount )
        {
            wPosition = 0;
        }
        if(msAPI_CM_FindProgramByNameGetServiceName(bServiceType, wPosition, (U8 *)au8ServiceName)==TRUE)
        {
            MApp_SI_GetString(tempBuffer_1, MAX_SERVICE_NAME, (U8 *)au8ServiceName, MAX_SERVICE_NAME, KEEP_CONTROL_CODE_NONE);
        }
        if(tempBuffer_1[0]==0x05)
            u8SpecFlag=1;
        else
            u8SpecFlag=0;
        for(k=0;bProgramName[k];k++)
        {
            if(au8ServiceName[k+u8SpecFlag]!=bProgramName[k]&&au8ServiceName[k+u8SpecFlag]!=u8ProgName_chlist_bak[k])
            {
                result=FALSE;
                break;
            }
        }
        if(result)
        {
            //printf("\r\n____findnext=%d",wPosition);
            if( TRUE == bIncludeSkipped )
            {
                return wPosition;
            }
            else
            {
                if( FALSE == msAPI_CM_FindProgramByNameGetProgramAttribute(bServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED) )
                {
                    return wPosition;
                }
            }
        }
        result=TRUE;
    }
    return INVALID_PROGRAM_POSITION;
}
#endif

#if (ENABLE_LCN_CONFLICT)
void msAPI_CM_ResetLCNConflictParams(void)
{
    DTV_SIMPLE_SERVICE_INFO* pItem;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    WORD index1;

    memset(pstProgramIndexTable, 0, sizeof(DTVPROGRAMINDEX)*u16ProgramIndexTableArraySize);
    for(index1=0; index1 < u16ProgramIndexTableArraySize; index1++)
    {
        pstProgramIndexTable[index1].bServiceType=E_SERVICETYPE_INVALID;
        pstProgramIndexTable[index1].bServiceTypePrio = E_SERVICETYPE_PRIORITY_NONE;
        pstProgramIndexTable[index1].wPRIndex = INVALID_PRINDEX;
    }

    while(_pDuplicateServiceList)//free old service
    {
        pItem =_pDuplicateServiceList;
        _pDuplicateServiceList = _pDuplicateServiceList->next;
        msAPI_Memory_Free(pItem,BUF_ID_DTV_SYS_DUPLICATE_SERVICE);
    }
}
#endif

static BOOLEAN _RemoveService(TypDtvDbSel eDtvDbSel, WORD cIDIndex, WORD wService_ID)
{
    WORD i;
    WORD wPosition,wProgramCount,wOrder;
    WORD wCurPosition;

    eDtvDbSel=eDtvDbSel;

#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = eDtvDbSel;
#endif
#if 1 //(ENABLE_API_DTV_SYSTEM_2015) // Use new method
    //DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    //U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eCurDbSel);
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eCurDbSel);
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#endif


    wCurPosition = msAPI_CM_GetCurrentPosition(m_eCurrentServiceType);

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
        if(pstProgramIndexTable[wOrder].cIDIndex == cIDIndex)
        {
            if(pstProgramIndexTable[wOrder].wService_ID == wService_ID)
            {
                RemoveProgram(E_SERVICETYPE_DTV,wPosition);
                if((m_eCurrentServiceType == E_SERVICETYPE_DTV)
                    && (wPosition == wCurPosition))
                {
                    return TRUE;
                }
                return FALSE;
            }
        }
        wPosition--;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, wPosition);
        if(pstProgramIndexTable[wOrder].cIDIndex == cIDIndex)
        {
            if(pstProgramIndexTable[wOrder].wService_ID == wService_ID)
            {
                RemoveProgram(E_SERVICETYPE_RADIO,wPosition);
                if((m_eCurrentServiceType == E_SERVICETYPE_RADIO)
                    && (wPosition == wCurPosition))
                {
                    return TRUE;
                }
                return FALSE;

            }
        }
        wPosition--;
    }

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition);
        if(pstProgramIndexTable[wOrder].cIDIndex == cIDIndex)
        {
            if(pstProgramIndexTable[wOrder].wService_ID == wService_ID)
            {
                RemoveProgram(E_SERVICETYPE_DATA,wPosition);
                if((m_eCurrentServiceType == E_SERVICETYPE_DATA)
                    && (wPosition == wCurPosition))
                {
                    return TRUE;
                }
                return FALSE;

            }
        }
        wPosition--;
    }

    return FALSE;
}

#if 0//NTV_FUNCTION_ENABLE
#if ENABLE_FAVORITE_NETWORK
void msAPI_DTV_Program_Network_Info_Print(U8 u8Index)
{
       U8 i;

       printf("\r\n _cFavoriteNetwork     = %d",  _cFavoriteNetwork);
       printf("\r\n _au8CurNetworkLen     = %d",  _au8CurNetworkLen);
       printf("\r\n _au8CurNetworkName : ");

       for (i=0;i<MAX_NETWORK_NAME;i++)
         {
              if (_au8CurNetworkName[i] == 0)
                  break;

            printf("%c", _au8CurNetworkName[i]);
         }

       printf("\r\n");
       printf("\r\n _astDTVNetwork.wNetwork_ID    = %d" , _astDTVNetwork[u8Index].wNetwork_ID);
       printf("\r\n _astDTVNetwork.bNetworkName[] : ");

       for (i=0;i<MAX_NETWORK_NAME;i++)
          {
            if (_astDTVNetwork[u8Index].bNetworkName[i] == 0)
                  break;

            printf("%c", _astDTVNetwork[u8Index].bNetworkName[i]);
          }
}
#endif  //ENABLE_FAVORITE_NETWORK
#endif  //NTV_FUNCTION_ENABLE

#if ENABLE_DVB_T2
BOOLEAN msAPI_CM_DVBT2_RemoveMux(BYTE cRFChannelNumber, BYTE *pu8PlpIDList,  BYTE cCountOfPlpID)
{
    BYTE j;
    U16 i;
    WORD dummy1 = 0;   // fix coverity 207467
    MEMBER_SERVICETYPE dummy2 = E_SERVICETYPE_ATV;

    // Use new method
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    //U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    //DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    //U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    //DTVNETWORK * pstNetWorkTable = msAPI_DtvDB_Get_NetWorkTable(eDtvDbSel);
    //U16 u16NetWorkIndex;

    U8 u8ServiceCount=MApp_SI_GetScanNumOfPatItem();

    memset(&dummy2, 0x00, sizeof(MEMBER_SERVICETYPE));// fix coverity 207578

    for(i=0; i < u16IDTableArraySize; i++)
    {
        if(pMuxTable[i].cRFChannelNumber == cRFChannelNumber)
        {
            for(j=0;j<cCountOfPlpID;j++)
            {
                if(pu8PlpIDList[j] == pMuxTable[i].cPLPID)
                {
                    break;
                }
            }
            if((j>=cCountOfPlpID) && (j!=0))
            {
            #if 1//(ENABLE_S2)
                RemoveMismatchedProgram(E_SERVICETYPE_DTV,cRFChannelNumber, pMuxTable[i].cPLPID, pMuxTable[i].cHpLp, &dummy1, &dummy2, u8ServiceCount,0,0);
                RemoveMismatchedProgram(E_SERVICETYPE_RADIO,cRFChannelNumber, pMuxTable[i].cPLPID, pMuxTable[i].cHpLp, &dummy1, &dummy2, u8ServiceCount,0,0);
                RemoveMismatchedProgram(E_SERVICETYPE_DATA,cRFChannelNumber, pMuxTable[i].cPLPID, pMuxTable[i].cHpLp, &dummy1, &dummy2, u8ServiceCount,0,0);
            #else
                RemoveMismatchedProgram(E_SERVICETYPE_DTV,cRFChannelNumber, pMuxTable[i].cPLPID, pMuxTable[i].cHpLp, &dummy1, &dummy2, u8ServiceCount);
                RemoveMismatchedProgram(E_SERVICETYPE_RADIO,cRFChannelNumber, pMuxTable[i].cPLPID, pMuxTable[i].cHpLp, &dummy1, &dummy2, u8ServiceCount);
                RemoveMismatchedProgram(E_SERVICETYPE_DATA,cRFChannelNumber, pMuxTable[i].cPLPID, pMuxTable[i].cHpLp, &dummy1, &dummy2, u8ServiceCount);
            #endif
            }
        }
    }

    memset(u8PlpIDList,INVALID_PLPID,32);

    return TRUE;
}
#endif

#if (ENABLE_EPG_MUX)
void msAPI_CM_SetEITUpdate(BOOLEAN bUpdate)
{
    _bBarkerEITUpdate = bUpdate;

}
BOOLEAN  msAPI_CM_GetEITUpdate(void)
{
    return _bBarkerEITUpdate;
}
#endif

BOOLEAN msAPI_CM_GetOpMode(void)
{
#if (ENABLE_CI_PLUS)
    return _bIsOpMode;
#else
    return FALSE;
#endif
}

#if (ENABLE_CI_PLUS)
void msAPI_CM_SetOpMode(BOOLEAN bOpMpde)
{
    _bIsOpMode = bOpMpde;
}

void msAPI_CM_SetCIOpType2(BOOLEAN bOpType)
{
    _bIsOpType2 = bOpType;
}



void msAPI_CM_SwitchCMDB(BOOLEAN bOpMpde)
{
    if (bOpMpde) //switch to op mode
    {
        //clean DB of normal mode and reset DTVDataManager
    #ifdef DATABASE_BK_START_ADR
     #if( DATABASE_BK_START_LEN >= DATABASE_START_LEN )
        memcpy((void *)_PA2VA(((DATABASE_BK_START_MEMORY_TYPE & MIU1) ? (DATABASE_BK_START_ADR | MIU_INTERVAL) : (DATABASE_BK_START_ADR))),
                (void *)_PA2VA(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR))),
                DATABASE_BK_START_LEN);
     #endif
    #endif

        msAPI_CM_ResetDTVDataManager(FALSE);
    }
    else //switch to normal mode
    {
        //Reload CM database in Flash
        MApp_DB_CH_LoadDataBase();
    }
}

static BOOLEAN _RemoveServiceWithSameLCN(TypDtvDbSel eDtvDbSel, U16 u16IDIndex, WORD wService_ID, WORD wLCN)
{
#if(ENABLE_API_DTV_SYSTEM_2015)
    TypDtvDbSel eCurDbSel = eDtvDbSel;

    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    //U16 u16DTVProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eCurDbSel);
#else
    DTVPROGRAMINDEX * pstDTVProgramIndexTable = m_astDTVProgramIndexTable;
#endif
    WORD i;
    WORD wPosition,wProgramCount,wOrder;

    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        //wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, E_SERVICETYPE_DTV, wPosition);
        if(pstDTVProgramIndexTable[wOrder].cIDIndex == u16IDIndex)
        {
            if((pstDTVProgramIndexTable[wOrder].wService_ID == wService_ID)&& (pstDTVProgramIndexTable[wOrder].wLCN == wLCN))
            {
                //....CI+1.4.....Check whether it is Op service or virtual service, if not...do not remove program
                #if(ENABLE_CI_PLUS_V1_4)
                DTV_CHANNEL_INFO stChannelInfo;
                msAPI_CM_GetProgramInfo(E_SERVICETYPE_DTV, wPosition, &stChannelInfo);
                if((!stChannelInfo.stCHAttribute.bIsVirtualSevice)||(!stChannelInfo.stCHAttribute.bIsOpService))
            {
                    printf("CI+1.4...... LCN conflict with normal program...can not remove normal program and not add this program\n");

                    bNotAddThisService = TRUE;
                    //Store Op Conflict channel info

                    return FALSE;
                }
                #endif
                RemoveProgram(E_SERVICETYPE_DTV,wPosition);
                if((m_eCurrentServiceType == E_SERVICETYPE_DTV)
                    && (wPosition == msAPI_CM_GetCurrentPosition(m_eCurrentServiceType)))
                {
                    return TRUE;
                }
                return FALSE;
            }
        }
        wPosition--;
    }
    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        //wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, wPosition);
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, E_SERVICETYPE_RADIO, wPosition);
        if(pstDTVProgramIndexTable[wOrder].cIDIndex == u16IDIndex)
        {
            if((pstDTVProgramIndexTable[wOrder].wService_ID == wService_ID)&& (pstDTVProgramIndexTable[wOrder].wLCN == wLCN))
            {
                //....CI+1.4.....Check whether it is Op service or virtual service, if not...do not remove program
#if(ENABLE_CI_PLUS_V1_4)
                DTV_CHANNEL_INFO stChannelInfo;
                msAPI_CM_GetProgramInfo(E_SERVICETYPE_DTV, wPosition, &stChannelInfo);
                if((!stChannelInfo.stCHAttribute.bIsVirtualSevice)||(!stChannelInfo.stCHAttribute.bIsOpService))
            {
                    printf("CI+1.4...... LCN conflict with normal program...can not remove normal program\n");
                    bNotAddThisService = TRUE;
                    return FALSE;
                }
#endif

                RemoveProgram(E_SERVICETYPE_RADIO,wPosition);
                if((m_eCurrentServiceType == E_SERVICETYPE_RADIO)
                    && (wPosition == msAPI_CM_GetCurrentPosition(m_eCurrentServiceType)))
                {
                    return TRUE;
                }
                return FALSE;

            }
        }
        wPosition--;
    }
    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);
    wPosition = wProgramCount-1;
    for(i=wProgramCount; i > 0; i--)
    {
        //wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition);
        wOrder = ConvertPositionToOrder_DBSel(eDtvDbSel, E_SERVICETYPE_DATA, wPosition);
        if(pstDTVProgramIndexTable[wOrder].cIDIndex == u16IDIndex)
        {
            if((pstDTVProgramIndexTable[wOrder].wService_ID == wService_ID)
                && (pstDTVProgramIndexTable[wOrder].wLCN == wLCN))
            {
                //....CI+1.4.....Check whether it is Op service or virtual service, if not...do not remove program
#if(ENABLE_CI_PLUS_V1_4)
                DTV_CHANNEL_INFO stChannelInfo;
                msAPI_CM_GetProgramInfo(E_SERVICETYPE_DTV, wPosition, &stChannelInfo);
                if((!stChannelInfo.stCHAttribute.bIsVirtualSevice)||(!stChannelInfo.stCHAttribute.bIsOpService))
                {
                    printf("CI+1.4...... LCN conflict with normal program...can not remove normal program\n");
                    bNotAddThisService = TRUE;
                    return FALSE;
                }
#endif

                RemoveProgram(E_SERVICETYPE_DATA,wPosition);
                if((m_eCurrentServiceType == E_SERVICETYPE_DATA)
                    && (wPosition == msAPI_CM_GetCurrentPosition(m_eCurrentServiceType)))
                {
                    return TRUE;
                }
                return FALSE;

            }
        }
        wPosition--;
    }
    return FALSE;
}
#endif

U16 msAPI_CM_GetMuxMaxNumber(void)
{
#if( ENABLE_API_DTV_SYSTEM_2015 )
    return msAPI_DtvDB_Get_ProgIdTableArraySize( msAPI_DTV_Comm_Get_DBSel() );

#else

  #if ENABLE_S2
    if( IsS2InUse() )
    {
        return MAX_DTV_S2_MUX_NUMBER;
    }
  #endif

  #if (ENABLE_CI_PLUS)
    if( msAPI_CM_GetOpMode() )
    {
        return MAX_MUX_NUMBER; // DVBT
    }
  #endif

  #if(ENABLE_DVBC && DVB_T_C_DIFF_DB )
    if( IsDVBCInUse() )
    {
        return MAX_MUX_NUMBER_DVBC;
    }
  #endif

    return MAX_MUX_NUMBER;

#endif
}

#if(ASTRA_HD_ENABLE || ASTRA_LCN_ENABLE)

void msAPI_CM_SortServiceList(void)
{
    U8 u8ChListcount,u8ChListcount1;
    U8 u8MaxChListcount = (U8)msAPI_CM_GetServiceListIdCount();
    DVBS_SI_SGT_BASIC_SERVICE_LIST_INFO stTempServiceListInfo;
    for(u8ChListcount = 0;u8ChListcount<u8MaxChListcount-1;u8ChListcount++)
    {
        for(u8ChListcount1 = u8ChListcount+1;u8ChListcount1<u8MaxChListcount;u8ChListcount1++)
        {
            if(_astServiceListInfo[u8ChListcount].u16ServiceListID > _astServiceListInfo[u8ChListcount1].u16ServiceListID)
            {
               memcpy(stTempServiceListInfo.au8ServiceListName,_astServiceListInfo[u8ChListcount].au8ServiceListName,MAX_SERVICE_LIST_NAME);
                stTempServiceListInfo.stCountryInfo.bIsCountryAvailability = _astServiceListInfo[u8ChListcount].stCountryInfo.bIsCountryAvailability;
                stTempServiceListInfo.stCountryInfo.enSICountry = _astServiceListInfo[u8ChListcount].stCountryInfo.enSICountry;
               stTempServiceListInfo.iSUsed = _astServiceListInfo[u8ChListcount].iSUsed;
               stTempServiceListInfo.u16ServiceListID = _astServiceListInfo[u8ChListcount].u16ServiceListID;
               memcpy(_astServiceListInfo[u8ChListcount].au8ServiceListName,_astServiceListInfo[u8ChListcount1].au8ServiceListName,MAX_SERVICE_LIST_NAME);
                _astServiceListInfo[u8ChListcount].stCountryInfo.bIsCountryAvailability = _astServiceListInfo[u8ChListcount1].stCountryInfo.bIsCountryAvailability;
                _astServiceListInfo[u8ChListcount].stCountryInfo.enSICountry = _astServiceListInfo[u8ChListcount1].stCountryInfo.enSICountry;
               _astServiceListInfo[u8ChListcount].iSUsed = _astServiceListInfo[u8ChListcount1].iSUsed;
               _astServiceListInfo[u8ChListcount].u16ServiceListID = _astServiceListInfo[u8ChListcount1].u16ServiceListID;
               memcpy(_astServiceListInfo[u8ChListcount1].au8ServiceListName,stTempServiceListInfo.au8ServiceListName,MAX_SERVICE_LIST_NAME);
                _astServiceListInfo[u8ChListcount1].stCountryInfo.bIsCountryAvailability = stTempServiceListInfo.stCountryInfo.bIsCountryAvailability;
                _astServiceListInfo[u8ChListcount1].stCountryInfo.enSICountry = stTempServiceListInfo.stCountryInfo.enSICountry;
               _astServiceListInfo[u8ChListcount1].iSUsed = stTempServiceListInfo.iSUsed;
               _astServiceListInfo[u8ChListcount1].u16ServiceListID = stTempServiceListInfo.u16ServiceListID;
            }
        }
    }
}

BOOLEAN msAPI_CM_ResetServiceListInfoData(BOOLEAN bResetFlag)
{
   if(bResetFlag)
   {
       memset(_astServiceListInfo, 0, sizeof(DVBS_SI_SGT_BASIC_SERVICE_LIST_INFO)*MAX_SGT_MUX_NUMBER);
       memset(_astServiceInfo, 0, sizeof(DVBS_SI_SGT_SERVICE_INFO)*MAX_DTV_S2_PROGRAM);
       _u16SgtServiceNumber = 0;
       _u16SgtServiceListIdCount = 0;
       return TRUE;
   }

   return FALSE;
}

BOOLEAN msAPI_CM_SaveAstraServiceInfo(U16 u16ServiceListID, MS_SI_SGT_SERVICE_INFO *stServiceInfo)
{
   if(_u16SgtServiceNumber<MAX_DTV_S2_PROGRAM)
   {
        _astServiceInfo[_u16SgtServiceNumber].u16ServiceListID = u16ServiceListID;
        memcpy(&_astServiceInfo[_u16SgtServiceNumber].stServiceInfo,stServiceInfo,sizeof(MS_SI_SGT_SERVICE_INFO));
        _u16SgtServiceNumber++;
        return TRUE;
   }
   return FALSE;
}

U16 msAPI_CM_GetAstraServiceCount(void)
{
    return (_u16SgtServiceNumber);
}

MS_SI_SGT_SERVICE_INFO msAPI_CM_GetAstraServiceInfo(MS_U16 ServiceIndex)
{
    return _astServiceInfo[ServiceIndex].stServiceInfo;
}


U16 msAPI_CM_GetServiceListIdCount(void)
{
    return _u16SgtServiceListIdCount;
}


BOOLEAN msAPI_CM_SaveServiceListInfo(const U8 *pu8Dest, U16 u16ServiceListID, EN_SI_COUNTRY_SETTING eSICountry, BOOLEAN bIsCountryAvailability, BOOLEAN bListInFlag)
{
   int i = 0;

   if(bListInFlag)
   {
      for(i = 0; i < MAX_SGT_MUX_NUMBER; i++)
      {
         if(_astServiceListInfo[i].u16ServiceListID == FALSE)
         {
             _astServiceListInfo[i].iSUsed = FALSE;
             _astServiceListInfo[i].u16ServiceListID = u16ServiceListID;
             _astServiceListInfo[i].stCountryInfo.enSICountry = eSICountry;
             _astServiceListInfo[i].stCountryInfo.bIsCountryAvailability = bIsCountryAvailability;
             memcpy(_astServiceListInfo[i].au8ServiceListName, pu8Dest, MAX_SERVICE_LIST_NAME);
             _u16SgtServiceListIdCount++;
             break;
         }
      }

      if(i >= MAX_SGT_MUX_NUMBER)
      {
         return FALSE;
         printf(" ******  Service Lsit Info Save Failure!!  **********\n");
      }
  }
  else
  {
     for(i = 0; i < MAX_SGT_MUX_NUMBER; i++)
     {
       if((_astServiceListInfo[i].u16ServiceListID == u16ServiceListID)  && (u16ServiceListID != 0) )
       {
          if(memcmp(_astServiceListInfo[i].au8ServiceListName, pu8Dest, MAX_SERVICE_LIST_NAME))
          {
              memcpy(_astServiceListInfo[i].au8ServiceListName, pu8Dest, MAX_SERVICE_LIST_NAME);
              break;
          }
       }
     }
  }

   return TRUE;
}

BOOLEAN msAPI_CM_GetExistServiceListInfo( const U16 u16ServiceListID, BOOLEAN bListInFlag)
{
    int i = 0;
    BOOLEAN ret = FALSE;

    if(bListInFlag)
    {
        for(i = 0; i < MAX_SGT_MUX_NUMBER; i++)
        {
             if((_astServiceListInfo[i].u16ServiceListID == u16ServiceListID)  && (u16ServiceListID != 0) )
             {
                        ret = TRUE;
               break;
             }
        }
    }

    return ret;

}

U16 msAPI_CM_GetAvailableServiceListID(void)
{
  #if(ASTRA_LCN_ENABLE)
    int i = 0;

    for(i = 0; i < MAX_SGT_MUX_NUMBER; i++)
    {
        if(_astServiceListInfo[i].iSUsed == FALSE)
        {
             if( _astServiceListInfo[i].u16ServiceListID  != 0 )
             {
                 _astServiceListInfo[i].iSUsed = TRUE;
                 u8ServiceId = _astServiceListInfo[i].u16ServiceListID;
                 return u8ServiceId;

             }
        }
    }

    return 0;
  #elif(ASTRA_HD_ENABLE)
    if(msAPI_CM_GetServiceListFocusIndex() != 0xFF)
    {
        u8ServiceId =_astServiceListInfo[msAPI_CM_GetServiceListFocusIndex()].u16ServiceListID;
        if(_u16SgtServiceListIdCount < u8ServiceId)
        {
            return 0xFF;
        }
        return _astServiceListInfo[msAPI_CM_GetServiceListFocusIndex()].u16ServiceListID;
    }
    return 0;
  #endif
}

U16 msAPI_CM_GetCurrentServiceListID(void)
{
    return u8ServiceId;
}

void msAPI_CM_SetCurrentServiceListID(U8 u8Servid)
{
    u8ServiceId = u8Servid;
}

U16 msAPI_CM_GetServiceListIDwithIndex(U8 _u8index)
{
    return _astServiceListInfo[_u8index].u16ServiceListID;
}

void msAPI_CM_GetServiceListName(U16 u16index,U8 *u8CharBuff)
{
    msAPI_CM_SortServiceList();
    memcpy(u8CharBuff , _astServiceListInfo[u16index].au8ServiceListName, MAX_SERVICE_LIST_NAME);
    return ;
}

void msAPI_CM_SetServiceListFocusIndex( U8 u8index)
{
    if(u8index ==0xFF)
    {
        u8ServiceId = 0;
        _astServiceListInfo[msAPI_CM_GetServiceListFocusIndex()].u16ServiceListID = 0;
    }
    _u8HDFocusIndex = u8index;
}

U8 msAPI_CM_GetServiceListFocusIndex(void)
{
    return _u8HDFocusIndex;
}


BOOLEAN msAPI_CM_GetAdd2ListFlag(void)
{
    return _u8IsAdd2List;
}

void msAPI_CM_IsAdd2List(BOOLEAN bIsAdd)
{
    _u8IsAdd2List = bIsAdd;
}

BOOLEAN msAPI_CM_GetAdd2ListSelectNOState(void)
{
    return _u8Add2ListSelectNO;
}

void msAPI_CM_SetAdd2ListSelectNOState(BOOLEAN bIsNo)
{
    _u8Add2ListSelectNO = bIsNo;
}

BOOLEAN msAPI_CM_IsLCNInConflictList(WORD wlcn)
{
    MS_U8 u8Index;
    for(u8Index = 0;u8Index <= wLCNConflictNum;u8Index++)
    {
        if(wLCNConflictList[u8Index] == wlcn)
        {
            return TRUE;
        }
    }
    return FALSE;
}


void msAPI_CM_SetLCNConflictListNum(MS_U8 u8Num)
{
    wLCNConflictNum = u8Num;
}

MS_U8 msAPI_CM_GetLCNConflictListNum(void)
{
    return wLCNConflictNum;
}


BOOLEAN MApp_Get_IsNITQuickScan(void)
{
    return bIsNITQuickScan;
}

void MApp_Set_IsNITQuickScan(BOOLEAN bquick)
{
    bIsNITQuickScan = bquick;
}


//this function have no spec support,just for test
EN_OSD_COUNTRY_SETTING msAPI_CM_ServListInfo2OSDCountry(MS_U8 u8Index)
{
    msAPI_CM_SortServiceList();
    if(u8Index > 4)
    {
        return OSD_COUNTRY_NUMS;
    }
    if(_astServiceListInfo[u8Index].stCountryInfo.bIsCountryAvailability)
    {
        switch(_astServiceListInfo[u8Index].stCountryInfo.enSICountry)
        {
            case SI_COUNTRY_GERMANY:
            return OSD_COUNTRY_GERMANY;
            case SI_COUNTRY_AUSTRIA:
            return OSD_COUNTRY_AUSTRIA;
            case SI_COUNTRY_CZECH:
            return OSD_COUNTRY_CZECH;
            case SI_COUNTRY_SLOVAKIA:
            return OSD_COUNTRY_SLOVAKIA;
            default:
            return OSD_COUNTRY_NUMS;
        }
    }
    else
    {
        switch(_astServiceListInfo[u8Index].u16ServiceListID)
        {
            case 1:
            return OSD_COUNTRY_GERMANY;
            case 2:
            return OSD_COUNTRY_AUSTRIA;
            case 3:
            return OSD_COUNTRY_CZECH;
            case 4:
            return OSD_COUNTRY_SLOVAKIA;
            default:
            return OSD_COUNTRY_NUMS;
        }
    }
}

MS_U8 msAPI_CM_GetDefaultFocusWithServListID(void)
{
    MS_U8 u8Index;
    MS_U8 ListIdCount = msAPI_CM_GetServiceListIdCount();
    for(u8Index = 0;u8Index < ListIdCount; u8Index++)
    {
        if(OSD_COUNTRY_SETTING == msAPI_CM_ServListInfo2OSDCountry(u8Index))
        return u8Index;
    }
    return 0xFF;
}


void msAPI_CM_GetCurrentSatParam(BYTE *SatelliteId,U32 *u32S2Frequency,U16 *u16SymbolRate,BYTE *u8Polarity)
{
    U16 u16CurPosition;
    MEMBER_SERVICETYPE bCurServiceType;

    WORD wOrder;
	WORD cIDIndex;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    bCurServiceType = msAPI_CM_GetCurrentServiceType();
    u16CurPosition = msAPI_CM_GetCurrentPosition(bCurServiceType);
    wOrder = ConvertPositionToOrder(bCurServiceType, u16CurPosition);
    cIDIndex = pstProgramIndexTable[wOrder].cIDIndex;
    *SatelliteId = _astS2ProgramIDTable[cIDIndex].SatelliteId;
    *u32S2Frequency = _astS2ProgramIDTable[cIDIndex].u32S2Frequency;
    *u16SymbolRate = _astS2ProgramIDTable[cIDIndex].u16SymbolRate;
    *u8Polarity = _astS2ProgramIDTable[cIDIndex].u8Polarity;
}

void msAPI_CM_ClearAttribute(MEMBER_SERVICETYPE bServiceType, WORD wPosition, E_MEMBER_CHANNEL_ATTRIBUTE eAttributeMember)
{
#if ENABLE_S2
    BOOLEAN bIsValidParameter;
    WORD wOrder;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    bIsValidParameter = TRUE;
    bIsValidParameter &= IsServiceTypeValid(bServiceType);
    bIsValidParameter &= IsPositionValid(bServiceType, wPosition);

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);

	if(IsS2InUse())
	{
		switch (eAttributeMember)
	    {
			case E_ATTRIBUTE_IS_NEW_SERVICE:
			{
			    WORD wPRIndex;
			    CHANNEL_ATTRIBUTE stCHAttribute;
			    if(FALSE == bIsValidParameter)
                {
			        break;
			    }
                pstProgramIndexTable[wOrder].bIsNewService = DEFAULT_IS_NEW_SERVICE;
                wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;
                GetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                stCHAttribute.bIsNewService = DEFAULT_IS_NEW_SERVICE;
                SetProgramTable(wPRIndex, (BYTE *)&stCHAttribute, E_DATA_MISC);
                break;
			}
            default:
                break;
        }
    }
#endif
}


void msAPI_CM_ClearAllNewService(void)
{
    WORD wPosition,wServiType;
    WORD wProgramCount;
    for(wServiType = E_SERVICETYPE_DTV;wServiType <= E_SERVICETYPE_DATA; wServiType++)
    {
        wProgramCount = msAPI_DTV_GetProgramCount((MEMBER_SERVICETYPE)wServiType, INCLUDE_ALL);
        for(wPosition = 0;wPosition < wProgramCount; wPosition++)
        {
            msAPI_CM_ClearAttribute((MEMBER_SERVICETYPE)wServiType,wPosition, E_ATTRIBUTE_IS_NEW_SERVICE);
        }
    }
}

void msAPI_CM_GetSgtVersionandPID(MS_SGT_ITEM *pCurSgtVerandPID)
{
    U8 i=0,j=0;
    WORD wPosition,wProgramCount,wOrder,wPRIndex,wSgt_PID=0,wSgt_Version=DEFAULT_VERSION;
    MEMBER_SERVICETYPE wServiType;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    for(wServiType = E_SERVICETYPE_DTV;wServiType <= E_SERVICETYPE_DATA; wServiType++)
    {
        wProgramCount = msAPI_DTV_GetProgramCount((MEMBER_SERVICETYPE)wServiType, INCLUDE_ALL);
        for(wPosition = 0;wPosition < wProgramCount; wPosition++)
        {
            wOrder = ConvertPositionToOrder(wServiType, wPosition);
            wPRIndex = pstProgramIndexTable[wOrder].wPRIndex;

            if((TRUE == GetProgramTable(wPRIndex, (BYTE *)&wSgt_PID, E_DATA_SGT_PID)) && wSgt_PID)
            {
                for(j=0;j<i;j++)
                {
                    if(wSgt_PID == pCurSgtVerandPID[j].wPrivateSgtPID)
                        break;
                }

                if((j >= i)&&(i<SI_MAX_SGT_TABLE_NUMBER))
                {
                    GetProgramTable(wPRIndex, (BYTE *)&wSgt_Version, E_DATA_VERSION_SDT);
                    pCurSgtVerandPID[i].wPrivateSgtPID = wSgt_PID;
                    pCurSgtVerandPID[i].u8Sgtversion   = wSgt_Version;
                    printf("[passto] pid %d version %d \n",pCurSgtVerandPID[i].wPrivateSgtPID,pCurSgtVerandPID[i].u8Sgtversion);
                    i++;
                }
            }

            if(i>= SI_MAX_SGT_TABLE_NUMBER)
            {
                printf("[max warn]  SI_MAX_SGT_TABLE_NUMBER is full, sgt pid cant get any more\n");
                break;
            }
        }
    }
}


BOOLEAN msAPI_CM_RemoveIsNewService(void)
{
#if(ENABLE_S2)
    WORD wPosition;
    WORD wProgramCount;
    WORD wRemoveCount = 0;
    if(IsS2InUse())
    {
        wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);

        for(wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            if(msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV,wPosition,E_ATTRIBUTE_IS_NEW_SERVICE))
            {
                RemoveProgram(E_SERVICETYPE_DTV,wPosition);
                wProgramCount--;
                wPosition--;
                wRemoveCount++;
            }
        }
        wProgramCount =  msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
        for(wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            if(msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO,wPosition,E_ATTRIBUTE_IS_NEW_SERVICE))
            {
                RemoveProgram(E_SERVICETYPE_RADIO,wPosition);
                wProgramCount--;
                wPosition--;
                wRemoveCount++;
            }
        }
        wProgramCount =   msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);
        for(wPosition = 0; wPosition < wProgramCount; wPosition++)
        {
            if(msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA,wPosition,E_ATTRIBUTE_IS_NEW_SERVICE))
            {
                RemoveProgram(E_SERVICETYPE_DATA,wPosition);
                wProgramCount--;
                wPosition--;
                wRemoveCount++;
            }
        }
    }
    if(wRemoveCount)
        return TRUE;
#endif
    return FALSE;
}


#endif //#if(ASTRA_HD_ENABLE)

#if(MHEG5_SIINFO_ENABLE)
//****************************************************************************
/// Get Program Provider Name
/// @param bServiceType \b IN: Service type
/// -@see MEMBER_SERVICETYPE
/// @param wPosition \b IN: position
/// @param *bProvidername \b IN: pointer to Audio program information for return
/// -@see DTV_CHANNEL_PROVIDER_NAME_INFO
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_GetProviderName(MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE *bProvidername)
{
#if 1// Use new API
    return msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(CUR_DB_SEL(), bServiceType, wPosition, (BYTE *)bProvidername, E_DATA_PROVIDER_NAME);

#else

    WORD wOrder;
    WORD wPRIndex;

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return FALSE;
    }

    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return FALSE;
    }

    wOrder = ConvertPositionToOrder(bServiceType, wPosition);
    wPRIndex = m_astDTVProgramIndexTable[wOrder].wPRIndex;

    if( TRUE != GetProgramTable(wPRIndex, (BYTE *)bProvidername, E_DATA_PROVIDER_NAME) )
    {
        return FALSE;
    }

    return TRUE;
#endif
}

BOOLEAN msAPI_CM_GetServiceInfo(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, DTV_CM_SI_SERVICEINFO *pstServiceInfo)
{
    BYTE cOrdinal = 1;
    WORD wPosition = 0;

    MEMBER_SERVICETYPE  peServiceType =  E_SERVICETYPE_INVALID;
    BOOLEAN bRet = FALSE;
    BOOLEAN bResult = FALSE;

    bResult = msAPI_CM_GetServiceTypeAndPositionWithIDs(wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal,&peServiceType, &wPosition,TRUE);
    if(bResult)
    {
        switch(peServiceType)
       {
          case E_SERVICETYPE_DTV:
            pstServiceInfo->u8ServiceType = E_TYPE_DTV;
            break;

          case E_SERVICETYPE_RADIO:
            pstServiceInfo->u8ServiceType = E_TYPE_RADIO;
            break;

          case E_SERVICETYPE_DATA:
            pstServiceInfo->u8ServiceType = E_TYPE_DATA;
            break;

          default:
            pstServiceInfo->u8ServiceType = (BYTE)peServiceType;
            //peServiceType = E_TYPE_DTV;
            break;
        }
    }

    bRet = msAPI_CM_GetServiceName(peServiceType, wPosition, pstServiceInfo->bServiceName);
    bRet = msAPI_CM_GetProviderName(peServiceType, wPosition,pstServiceInfo->bProviderName);

    return bRet;
}
#endif //#if(MHEG5_SIINFO_ENABLE)

void SET_Default_TW_DTV_CH(void) //yiling 0821 dtv channel setting
{
    BYTE CHANNEL_ID[6][sizeof(DTVPROGRAMID_M)] =
    {
        // customize
        /*
        {0x18,0x0,0x9E,0x20,0x0,0x0,0x18,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x1A,0x0,0x9E,0x20,0x0,0x0,0x1A,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x1C,0x0,0x9E,0x20,0x0,0x0,0x1C,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x1E,0x0,0x9E,0x20,0x0,0x0,0x1E,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x20,0x0,0x9E,0x20,0x0,0x0,0x20,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x22,0x0,0x9E,0x20,0x0,0x0,0x22,0x0,0x2,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        */

    };

    BYTE CHANNEL_INFO[20][sizeof(DTV_CHANNEL_INFO)] =
    {
        // customize
        /*
        {0x00,0x00,0xE9,0x03,0xE9,0x03,0x00,0x00,0x01,0x00,0x32,0x74,0xE8,0x03,0x00,0x00,0x0C,0x01,0x0A,0x1C,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x64,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xEA,0x03,0x00,0x00,0xFF,0x00,0x01,0xEB,0x03,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x4E,0x2D,0x89,0x96,0x65,0x78,0x4F,0x4D,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0xF3,0x03,0xF3,0x03,0x01,0x00,0x02,0x00,0x32,0x74,0xF2,0x03,0x00,0x00,0x0C,0x01,0x0A,0x1C,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x65,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xF4,0x03,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x4E,0x2D,0x89,0x96,0x65,0xB0,0x80,0x5E,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0xFD,0x03,0xFD,0x03,0x02,0x00,0x03,0x00,0x32,0x74,0xFC,0x03,0x00,0x00,0x0C,0x01,0x0A,0x1C,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x66,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xFE,0x03,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x4E,0x2D,0x89,0x96,0x7D,0x9C,0x85,0xDD,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x00,0x00,0x07,0x04,0x07,0x04,0x03,0x00,0x04,0x00,0x32,0x74,0x06,0x04,0x00,0x00,0x0C,0x01,0x0A,0x1C,0xC8,0xBE,0x03,0x22,0x2C,0x64,0x67,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x05,0x08,0x04,0x00,0x00,0xFF,0x00,0x05,0x09,0x04,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x4E,0x2D,0x89,0x96,0x00,0x48,0x00,0x44,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

        {0x01,0x00,0xDB,0x07,0xDB,0x07,0x00,0x00,0x05,0x00,0x32,0x74,0xDA,0x07,0x00,0x00,0x05,0x06,0x04,0x04,0xC8,0xBE,0x03,0x20,0x2C,0x64,0xC9,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xDC,0x07,0x00,0x00,0xFF,0x00,0x01,0xDD,0x07,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x51,0x6C,0x51,0x71,0x96,0xFB,0x89,0x96,0x00,0x20,0x00,0x50,0x00,0x54,0x00,0x53,0x00,0x00},
        {0x01,0x00,0xE5,0x07,0xE5,0x07,0x01,0x00,0x06,0x00,0x32,0x74,0xE4,0x07,0x00,0x00,0x05,0x14,0x04,0x04,0xC8,0xBE,0x03,0x20,0x2C,0x64,0xCA,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xE6,0x07,0x00,0x00,0xFF,0x00,0x01,0xE7,0x07,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x51,0x6C,0x89,0x96,0x00,0x32,0x53,0xF0,0x00,0x20,0x00,0x50,0x00,0x54,0x00,0x53,0x00,0x32},
        {0x01,0x00,0xEF,0x07,0xEF,0x07,0x02,0x00,0x07,0x00,0x32,0x74,0xEE,0x07,0x00,0x00,0x05,0x1B,0x04,0x04,0xC8,0xBE,0x03,0x20,0x2C,0x64,0xCB,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xF0,0x07,0x00,0x00,0xFF,0x00,0x01,0xF1,0x07,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x5B,0xA2,0x5B,0xB6,0x96,0xFB,0x89,0x96,0x00,0x20,0x00,0x48,0x00,0x54,0x00,0x56,0x00,0x00},

        {0x02,0x00,0xB9,0x0B,0xB9,0x0B,0x00,0x00,0x08,0x00,0x32,0x74,0xB8,0x0B,0x00,0x00,0x02,0x01,0x1F,0x1F,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x2C,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xBA,0x0B,0x00,0x00,0xFF,0x00,0x01,0xBB,0x0B,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x6C,0x11,0x89,0x96,0x7D,0x9C,0x54,0x08,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x02,0x00,0xC3,0x0B,0xC3,0x0B,0x01,0x00,0x09,0x00,0x32,0x74,0xC2,0x0B,0x00,0x00,0x02,0x01,0x1F,0x1F,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x2D,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xC4,0x0B,0x00,0x00,0xFF,0x00,0x01,0xC5,0x0B,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x6C,0x11,0x89,0x96,0x4E,0xA4,0x90,0x1A,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x02,0x00,0xCD,0x0B,0xCD,0x0B,0x02,0x00,0x0a,0x00,0x32,0x74,0xCC,0x0B,0x00,0x00,0x02,0x01,0x1F,0x1F,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x2E,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xCE,0x0B,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x6C,0x11,0x89,0x96,0x65,0xB0,0x80,0x5E,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x02,0x00,0xE1,0x0B,0xE1,0x0B,0x03,0x00,0x0b,0x00,0x32,0x74,0xE0,0x0B,0x00,0x00,0x02,0x0B,0x1F,0x1F,0xC8,0xBE,0x03,0x22,0x2C,0x64,0x30,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x05,0xE2,0x0B,0x00,0x00,0xFF,0x00,0x05,0xE3,0x0B,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x6C,0x11,0x89,0x96,0x00,0x48,0x00,0x44,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

        {0x03,0x00,0xD1,0x07,0xD1,0x07,0x00,0x00,0x0c,0x00,0x32,0x74,0xD0,0x07,0x00,0x00,0x05,0x05,0x15,0x15,0xC8,0xBE,0x03,0x22,0x2C,0x64,0xC8,0x00,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x05,0xD2,0x07,0x00,0x00,0xFF,0x00,0x05,0xD3,0x07,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x51,0x6C,0x89,0x96,0x00,0x20,0x00,0x48,0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

        {0x04,0x00,0xA1,0x0F,0xA1,0x0F,0x00,0x00,0x0d,0x00,0x32,0x74,0x20,0x00,0x00,0x00,0x03,0x01,0x04,0x1C,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x90,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xA2,0x0F,0x00,0x00,0xFF,0x00,0x01,0xA3,0x0F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x53,0xF0,0x70,0x63,0x96,0xFB,0x89,0x96,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x04,0x00,0xAB,0x0F,0xAB,0x0F,0x01,0x00,0x0e,0x00,0x32,0x74,0x21,0x00,0x00,0x00,0x03,0x01,0x04,0x1C,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x91,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xAC,0x0F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x53,0xF0,0x89,0x96,0x8C,0xA1,0x7D,0x93,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x04,0x00,0xB5,0x0F,0xB5,0x0F,0x02,0x00,0x0f,0x00,0x32,0x74,0x22,0x00,0x00,0x00,0x03,0x01,0x04,0x1C,0xC8,0xBE,0x03,0x20,0x2C,0x64,0x92,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xB6,0x0F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x53,0xF0,0x89,0x96,0x7D,0x9C,0x54,0x08,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x04,0x00,0xBF,0x0F,0xBF,0x0F,0x03,0x00,0x10,0x00,0x32,0x74,0xBE,0x0F,0x00,0x00,0x03,0x01,0x04,0x1C,0xC8,0xBE,0x03,0x22,0x2C,0x64,0x93,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x05,0xC0,0x0F,0x00,0x00,0xFF,0x00,0x05,0xC1,0x0F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x53,0xF0,0x89,0x96,0x00,0x20,0x00,0x48,0x00,0x44,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00},

        {0x05,0x00,0x93,0x13,0x93,0x13,0x00,0x00,0x11,0x00,0x32,0x74,0x92,0x13,0x00,0x00,0x03,0x08,0x1F,0x1F,0xC8,0xBE,0x03,0x20,0x2C,0x64,0xF5,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0x94,0x13,0x00,0x00,0xFF,0x00,0x01,0x95,0x13,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x83,0xEF,0x89,0x96,0x00,0x43,0x00,0x54,0x00,0x53,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x05,0x00,0x9D,0x13,0x9D,0x13,0x01,0x00,0x12,0x00,0x32,0x74,0x9C,0x13,0x00,0x00,0x03,0x07,0x1F,0x1F,0xC8,0xBE,0x03,0x20,0x2C,0x64,0xF6,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0x9E,0x13,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x83,0xEF,0x89,0x96,0x65,0x59,0x80,0xB2,0x53,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        {0x05,0x00,0xA7,0x13,0xA7,0x13,0x02,0x00,0x13,0x00,0x32,0x74,0xA6,0x13,0x00,0x00,0x03,0x07,0x1F,0x1F,0xC8,0xBE,0x03,0x20,0x2C,0x64,0xF7,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x01,0xA8,0x13,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x83,0xEF,0x89,0x96,0x65,0xB0,0x80,0x5E,0x8C,0xC7,0x8A,0x0A,0x53,0xF0,0x00,0x00,0x00,0x00},
        {0x05,0x00,0xB1,0x13,0xB1,0x13,0x03,0x00,0x14,0x00,0x32,0x74,0xB0,0x13,0x00,0x00,0x03,0x0A,0x1F,0x1F,0xC8,0xBE,0x03,0x22,0x2C,0x64,0xF8,0x01,0xFF,0xFF,0xFF,0x07,0xFF,0x00,0x05,0xB2,0x13,0x00,0x00,0xFF,0x00,0x05,0xB3,0x13,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0xFF,0x00,0x00,0xFF,0x1F,0x00,0x00,0x14,0x83,0xEF,0x89,0x96,0x00,0x48,0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
        */
    };

    DWORD index1;
        msAPI_CM_ResetAllProgram();
        #if (ENABLE_DTV_EPG)
       // MApp_Epg_ResetDB_Event();
        #endif
//    MApp_SI_Scan_Init();
//    MApp_SI_Scan_End();
//    memset((MS_EPG_EVENT *)EIT_SCHE_EVENT_START_ADR,0,EIT_SCHE_EVENT_LEN);


    for(index1 =0;index1<6;index1++)
    {
        SetIDTable(index1,&CHANNEL_ID[index1][0], E_DATA_ID_TABLE);
        ActiveIDEntity(index1,TRUE);
    }

    for(index1 =0;index1<20;index1++)
    {
        SetProgramTable(index1,&CHANNEL_INFO[index1][0], E_DATA_ALL);
        ActiveProgramEntity_DBSel( CUR_DB_SEL(), index1, TRUE);
    }
    u16ScanDtvChNum =20;
//    FillDTVProgramIndexTableWithOrder();

    UpdateProgramCount(E_SERVICETYPE_DTV);


    msAPI_CM_InitDTVDataManager();
    //MApp_SI_Scan_End();
    if(TRUE != msAPI_CM_ArrangeDataManager(TRUE,TRUE))
    {
         printf( "MApp_DTV_Scan_End: msAPI_CM_ArrangeDataManager FAIL !! \n" );
    }

        MApp_ChannelChange_DisableChannel(FALSE, MAIN_WINDOW);

    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV,0);
    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO,0);
#if NORDIG_FUNC //for Nordig Spec v.20
    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA,0);
#endif

#if (ENABLE_DTV_EPG)
    // init epg database
    MApp_EIT_All_Sche_ResetFilter();

#if (!BLOADER)
    #if ENABLE_DVB
    MApp_Epg_Init();
    #endif
#endif


    MApp_EpgTimer_InitTimerSettings(TRUE);

#endif  //#if (ENABLE_DTV_EPG)


    if(!IsDTVInUse())
    {
        #if ENABLE_DMP
        if(IsStorageInUse())
        {
            MApp_DMP_Exit();
        }
        #endif

      #if(ENABLE_DVBT)
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
      #else
        UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
      #endif
        MApp_InputSource_ChangeInputSource(MAIN_WINDOW);
        MApp_ChannelChange_VariableInit();
    }
    else
    {
        MApp_TopStateMachine_SetTopState(STATE_TOP_CHANNELCHANGE);
    }
    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);

    //
}

#if(ENABLE_S2_FAST_SCAN)

//****************************************************************************
/// Get Count Of Same Service With ServiceIDs
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param wService_ID \b IN: Service ID
/// - TRUE: To check
/// - FALSE: NO
/// @return BYTE: count
//****************************************************************************
static U16 GetCountOfSameServiceWithServiceIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID)
{
    WORD wPosition;
    WORD wOrder;
    WORD cIDIndex;
    WORD wProgramCount;
    U16 u16CountOfSameService;

    if( (FALSE == IsTS_IDValid(wTransportStream_ID)) ||
        (FALSE == IsON_IDValid(wOriginalNetwork_ID)) ||
        (FALSE == IsService_IDValid(wService_ID)))
    {
        return 0;
    }


    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(CUR_DB_SEL());
    DTVPROGRAMID_M * pIDTable = msAPI_DtvDB_Get_ProgIdTable(CUR_DB_SEL());

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    u16CountOfSameService = 0;

    for(wPosition = 0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if 1//ENABLE_S2
       //if(IsS2InUse())
       {
            if( wService_ID != pstDTVProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }

            cIDIndex = pstDTVProgramIndexTable[wOrder].cIDIndex;

            if( wTransportStream_ID == pIDTable[cIDIndex].wTransportStream_ID )
                u16CountOfSameService++;
       }
#endif //#if ENABLE_S2

    }

      return u16CountOfSameService;
}

//****************************************************************************
/// Get Order Of Same Service With ServiceIDs
/// @param bServiceType \b IN: Service Type
/// - @see MEMBER_SERVICETYPE
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param wService_ID \b IN: Service ID
/// - TRUE: To check
/// - FALSE: NO
/// @return BYTE: count
//****************************************************************************
static WORD GetOrderOfSameServiceWithServiceIDs(MEMBER_SERVICETYPE bServiceType, WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal)
{
    WORD wPosition = 0xFFFF;
    WORD wOrder;
    WORD cIDIndex;
    WORD wProgramCount;
    BYTE cCountOfSameService = 0;
    WORD wRet;

    if((FALSE == IsTS_IDValid(wTransportStream_ID)) ||
        (FALSE == IsON_IDValid(wOriginalNetwork_ID)) ||
        (FALSE == IsService_IDValid(wService_ID)) ||
        (0 == cOrdinal ))
    {
        return FALSE;
    }

    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(CUR_DB_SEL());
    DTVPROGRAMID_M * pIDTable = msAPI_DtvDB_Get_ProgIdTable(CUR_DB_SEL());

    wProgramCount = msAPI_DTV_GetProgramCount(bServiceType, INCLUDE_ALL);
    cCountOfSameService = 0;

    wRet = INVALID_ORDER;

    for(wPosition=0; wPosition < wProgramCount; wPosition++)
    {
        wOrder = ConvertPositionToOrder(bServiceType, wPosition);

#if 1//ENABLE_S2
        //if(IsS2InUse())
        {
            if( wService_ID != pstDTVProgramIndexTable[wOrder].wService_ID )
            {
                continue;
            }

            cIDIndex = pstDTVProgramIndexTable[wOrder].cIDIndex;

            if( wTransportStream_ID == pIDTable[cIDIndex].wTransportStream_ID )
                cCountOfSameService++;
        }
#endif //#if ENABLE_S2

        if( cOrdinal == cCountOfSameService )
        {
            wRet = wOrder;
            break;
        }
    }

    return wRet;
}
//****************************************************************************
/// Function : Open DVBS Fast Scan Flag
/// Variable  : @bEnable : Enable Flag
/// @return  : 1: Success
///                   0: Failure
//****************************************************************************
BOOLEAN msAPI_CM_Action_Set_M7DVBS_OpenMonitor(BOOLEAN bEnable)
{
#if(ENABLE_S2_FAST_SCAN)
    _bM7ScanEnable = bEnable;
#endif //#if(ENABLE_S2_FAST_SCAN)

    return bEnable;
}

//****************************************************************************
/// Get Service Type And Position With ServiceIDs
/// @param wTransportStream_ID \b IN: Transport Stream ID
/// @param wOriginalNetwork_ID \b IN: Original Network ID
/// @param cOrdinal \b IN: Ordinal
/// @param peServiceType \b IN: pointer to Service type for return
/// -@see MEMBER_SERVICETYPE
/// @param pwPosition \b IN: pointer to Position for return
/// @return BOOLEAN: Function execution result
//****************************************************************************
BOOLEAN msAPI_CM_DVBS_GetServiceTypeAndPositionWithServiceIDs(WORD wTransportStream_ID, WORD wOriginalNetwork_ID, WORD wService_ID, BYTE cOrdinal, MEMBER_SERVICETYPE * peServiceType, WORD * pwPosition)
{
    WORD wOrder = 0xFFFF;
    MEMBER_SERVICETYPE bServiceType =  E_SERVICETYPE_INVALID;
    TypDtvDbSel eDtvDbSel = CUR_DB_SEL();
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    if((FALSE == IsTS_IDValid(wTransportStream_ID)) ||
        (FALSE == IsON_IDValid(wOriginalNetwork_ID)) ||
        (FALSE == IsService_IDValid(wService_ID)) ||
        (0 == cOrdinal ))
    {
        return FALSE;
    }

    if( cOrdinal <= GetCountOfSameServiceWithServiceIDs(E_SERVICETYPE_DTV, wTransportStream_ID, wOriginalNetwork_ID, wService_ID) )
    {
        bServiceType = E_SERVICETYPE_DTV;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithServiceIDs(E_SERVICETYPE_RADIO, wTransportStream_ID, wOriginalNetwork_ID, wService_ID) )
    {
        bServiceType = E_SERVICETYPE_RADIO;
    }
    else if( cOrdinal <= GetCountOfSameServiceWithServiceIDs(E_SERVICETYPE_DATA, wTransportStream_ID, wOriginalNetwork_ID, wService_ID) )
    {
        bServiceType = E_SERVICETYPE_DATA;
    }
    else
    {
        return FALSE;
    }

    wOrder = GetOrderOfSameServiceWithServiceIDs(bServiceType, wTransportStream_ID, wOriginalNetwork_ID, wService_ID, cOrdinal);

    if( wOrder == INVALID_ORDER )
    {
        return FALSE;
    }


    *peServiceType = (MEMBER_SERVICETYPE)pstProgramIndexTable[wOrder].bServiceType;

    *pwPosition = ConvertOrderToPosition(wOrder);

     return TRUE;
}

#endif //#if(ENABLE_S2_FAST_SCAN)

BOOL IS_ATV_CH(WORD wOrdinal)
{
    MEMBER_SERVICETYPE msServiceType;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, (BYTE *)&msServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_ALL);

    return (msServiceType == E_SERVICETYPE_ATV);
}

BOOL IS_HIDE_CH(WORD wOrdinal)
{
    BOOL bSkip = FALSE;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, (BYTE *)&bSkip, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_ALL);

    return bSkip;
}

BOOL IS_FAV_CH(WORD wOrdinal)
{
    BOOL bFav = FALSE;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, (BYTE *)&bFav, E_SERVICE_ATTR_FAVORITE, E_PROGACESS_INCLUDE_ALL);

    return bFav;
}

BOOL IS_LOCK_CH(WORD wOrdinal)
{
    BOOL bLock = FALSE;

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal, (BYTE *)&bLock, E_SERVICE_ATTR_LOCKED, E_PROGACESS_INCLUDE_ALL);

    return bLock;
}

void SET_HIDE_CH(BOOL bHide)
{
    MEMBER_SERVICETYPE msService = msAPI_CM_GetCurrentServiceType();

    WORD wPos = msAPI_CM_GetCurrentPosition(msService);

    if(msService == E_SERVICETYPE_ATV)
    {
        msAPI_ATV_SkipProgram(wPos, bHide);
    }
    else
    {
        msAPI_CM_SkipProgram(msService, wPos, bHide);
    }
}

void SET_FAV_CH(BOOL bFav)
{
    MEMBER_SERVICETYPE msService = msAPI_CM_GetCurrentServiceType();

    WORD wPos = msAPI_CM_GetCurrentPosition(msService);

    if(msService == E_SERVICETYPE_ATV)
    {
        msAPI_ATV_SetFavoriteProgram(wPos, bFav);
    }
    else
    {
        msAPI_CM_FavorProgram(msService, wPos, bFav);
    }
}

void SET_LOCK_CH(BOOL bLock)
{
    MEMBER_SERVICETYPE msService = msAPI_CM_GetCurrentServiceType();

    WORD wPos = msAPI_CM_GetCurrentPosition(msService);

    if(msService == E_SERVICETYPE_ATV)
    {
        msAPI_ATV_LockProgram(wPos, bLock);
    }
    else
    {
        msAPI_CM_LockProgram(msService, wPos, bLock);
    }
}

//------------------------------------------------------------------

BOOL msAPI_CM_Is_CurChannelT2(void)
{
#if(ENABLE_DVB_T2)
    MEMBER_SERVICETYPE eCurServiceType = msAPI_CM_GetCurrentServiceType();
    U16 u16CurrentPosition = msAPI_CM_GetCurrentPosition(eCurServiceType);
    U8 u8Plp_id = msAPI_CM_GetPLP_ID(eCurServiceType, u16CurrentPosition);

#if (ENABLE_CI_PLUS)
    // Is CI HC Tune
    if (TRUE == msAPI_DTV_Comm_GetIsCiTuneStatus())
    {
        if (0xFF != msAPI_DTV_Comm_GetPLPID())
        {
            return TRUE;
        }
    }
    // Is Normal Channel Change
    else
#endif
    {
        if (u8Plp_id != 0xFF)
        {
            return TRUE;
        }
    }
#endif

    return FALSE;
}

U16 msAPI_DtvSys_Get_DefaultOrderOfDtv(TypDtvDbSel eDtvDbSel)
{
    eDtvDbSel=eDtvDbSel;
    return DEFAULT_CURRENT_ORDER_TV;
}

U16 msAPI_DtvSys_Get_DefaultOrderOfRadio(TypDtvDbSel eDtvDbSel)
{
    return DEFAULT_CURRENT_ORDER_RADIO(eDtvDbSel);
}

U16 msAPI_DtvSys_Get_DefaultOrderOfData(TypDtvDbSel eDtvDbSel)
{
    return DEFAULT_CURRENT_ORDER_DATA(eDtvDbSel);
}

U16 msAPI_DtvSys_Get_ProgTabIndex_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    U16 u16ProgTabIndex = INVALID_PRINDEX;
    U16 u16Order = INVALID_ORDER;


    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return u16ProgTabIndex;
    }
    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return u16ProgTabIndex;
    }

    u16Order = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( u16Order >= msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel) )
    {
        return u16ProgTabIndex;
    }

    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    u16ProgTabIndex = pstDTVProgramIndexTable[u16Order].wPRIndex;

    return u16ProgTabIndex;
}

U16 msAPI_DtvSys_Get_IDTabIndex_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition)
{
    U16 u16IDTabIndex = INVALID_IDINDEX;
    U16 u16Order = INVALID_ORDER;


    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        return u16IDTabIndex;
    }
    if( FALSE == IsPositionValid(bServiceType, wPosition) )
    {
        return u16IDTabIndex;
    }

    u16Order = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, wPosition);
    if( u16Order >= msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel) )
    {
        return u16IDTabIndex;
    }

    DTVPROGRAMINDEX * pstDTVProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);

    u16IDTabIndex = pstDTVProgramIndexTable[u16Order].cIDIndex;

    return u16IDTabIndex;
}

BOOLEAN msAPI_DtvSys_Get_ProgramTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    U16 u16PRIndex = msAPI_DtvSys_Get_ProgTabIndex_ByServiceAndPos( eDtvDbSel, bServiceType, wPosition);

    if( u16PRIndex >= msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel) )
        return FALSE;

    return GetProgramTable_DBSel(eDtvDbSel, u16PRIndex, pcBuffer, eMember);
}

BOOLEAN msAPI_DtvSys_Set_ProgramTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    U16 u16PRIndex = msAPI_DtvSys_Get_ProgTabIndex_ByServiceAndPos( eDtvDbSel, bServiceType, wPosition);

    if( u16PRIndex >= msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel) )
        return FALSE;

    return SetProgramTable_DBSel(eDtvDbSel, u16PRIndex, pcBuffer, eMember);
}

BOOLEAN msAPI_DtvSys_Get_IDTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    U16 u16IDIndex = msAPI_DtvSys_Get_IDTabIndex_ByServiceAndPos( eDtvDbSel, bServiceType, wPosition);

    if( u16IDIndex >= msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel) )
        return FALSE;

    return GetIDTable_DBSel(eDtvDbSel, u16IDIndex, pcBuffer, eMember);
}

BOOLEAN msAPI_DtvSys_Set_IDTable_ByServiceAndPos(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType, WORD wPosition, BYTE * pcBuffer, PROGRAMDATA_MEMBER eMember)
{
    U16 u16IDIndex = msAPI_DtvSys_Get_IDTabIndex_ByServiceAndPos( eDtvDbSel, bServiceType, wPosition);

    if( u16IDIndex >= msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel) )
        return FALSE;

    return SetIDTable_DBSel(eDtvDbSel, u16IDIndex, pcBuffer, eMember);
}

U16 msAPI_DtvSys_Get_PCN_ByIDIndex(TypDtvDbSel eDtvDbSel, U16 u16IDIndex )
{
    U16 u16PCN = 0xFFFF;
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    DTVPROGRAMID_M * pstIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);

    if( u16IDIndex >= u16IDTableArraySize ) // If ID Index valid?
    {
        return u16PCN;
    }

#if(ENABLE_S2)
    if( IsS2InUse() ) // DVBS
    {
        u16PCN = u16IDIndex;
    } else
#endif
#if( ENABLE_DVBC )
    if( IsDVBCInUse() ) // DVBC
    {
        u16PCN = u16IDIndex;
    } else
#endif
    //if( IsDVBTInUse()||IsDTMBInUse() ) // DVBT/DTMB
    {
        u16PCN = pstIDTable[u16IDIndex].cRFChannelNumber;
    }

    return u16PCN;
}

U16 msAPI_DtvSys_Get_PCN_ByOrder(TypDtvDbSel eDtvDbSel, U16 u16Order )
{
    U16 u16PCN = 0xFFFF;
    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    U16 u16IDIndex;
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);


    if( u16Order >= u16ProgramIndexTableArraySize )
        return u16PCN;

    u16IDIndex = pstProgramIndexTable[u16Order].cIDIndex;
    if( u16IDIndex >= u16IDTableArraySize ) // If ID Index valid?
    {
        return u16PCN;
    }

    return msAPI_DtvSys_Get_PCN_ByIDIndex(eDtvDbSel, u16IDIndex );
}

MEMBER_SERVICETYPE msAPI_DtvSys_Get_ServiceType_ByOrder(TypDtvDbSel eDtvDbSel, U16 u16Order )
{
    MEMBER_SERVICETYPE eServiceType = E_SERVICETYPE_INVALID;

    DTVPROGRAMINDEX * pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    if( u16Order >= u16ProgramIndexTableArraySize )
        return eServiceType;

    if( pstProgramIndexTable[u16Order].bServiceType > E_SERVICETYPE_INVALID )
        pstProgramIndexTable[u16Order].bServiceType = E_SERVICETYPE_INVALID;

    eServiceType = (MEMBER_SERVICETYPE)pstProgramIndexTable[u16Order].bServiceType;

    return eServiceType;
}

U16 msAPI_DtvSys_Find_IDTab_By_TSId_ONId(TypDtvDbSel eDtvDbSel, WORD wTS_ID, WORD wON_ID)
{
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16IDTabArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    U16 u16IDIndex;

    for( u16IDIndex = 0; u16IDIndex < u16IDTabArraySize; u16IDIndex ++)
    {
        if( (pMuxTable[u16IDIndex].wTransportStream_ID == wTS_ID)
         && (pMuxTable[u16IDIndex].wOriginalNetwork_ID == wON_ID)
          )
        {
            return u16IDIndex;
        }
    }

    return INVALID_IDINDEX;
}

void msAPI_DtvSys_PrintServiceName(U8* pu8Name, U16 u16MaxLen)
{
    U16 u16CharIdx;
    U8 u8Char;

    putchar('[');
    for( u16CharIdx = 0; u16CharIdx < u16MaxLen; u16CharIdx += 1 )
    {
        u8Char = pu8Name[u16CharIdx];

        if( u8Char == 0 )
            break;

        if( u8Char >= 20 && u8Char < 0x80 )
        {
            printf("%c", u8Char );
        }
        else
        {
            printf("(0x%X)", u8Char);
        }
    }
    putchar(']');
}

BOOLEAN msAPI_DtvSys_Is_SortByLCN(void)
{
    //if( IS_LCN_RANK_COUNTRY(m_eOSDCountrySetting) )
    if( IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING) )
    {
        return TRUE;
    }

    return FALSE;
}

#ifdef ENABLE_DELETE_PROGRAM_CONTROL
BOOLEAN msAPI_CM_ResetRemoveProgramData(void)
{
    m_bVaildData = FALSE;
    m_bRFChannelNumber = 0;
    m_bPLP_ID = 0;
    m_bHpLp = 0;
    m_bCountOfServiceID = 0;
    m_wTSID = 0;
    m_bsat = 0;
    m_wfreq = 0;
    memset(m_wService_ID, 0, sizeof(m_wService_ID));
    memset(m_eService_Type, 0, sizeof(m_eService_Type));

    return TRUE;
}

BOOLEAN msAPI_CM_IsUserRemoveProgram(BOOLEAN bRemove)
{
    if(bRemove)
    {
        if(m_bVaildData == TRUE)
        {
            #if ENABLE_S2_WORD
            msAPI_CM_RemoveMismatchedProgram(m_bRFChannelNumber, m_wTSID, m_bPLP_ID, m_bHpLp, m_wService_ID, m_eService_Type, m_bCountOfServiceID, m_bsat, m_wfreq);
            #else
            msAPI_CM_RemoveMismatchedProgram(m_bRFChannelNumber, m_wTSID, m_bPLP_ID, m_bHpLp, m_wService_ID, m_eService_Type, m_bCountOfServiceID);
            #endif
        }
        m_bHaveRemoved = TRUE;
        //msAPI_ATV_InitATVDataManager();
    }
    msAPI_CM_ResetRemoveProgramData();
    return TRUE;
}

BOOLEAN msAPI_CM_GetRemoveProgram(E_SERVICE_CHANGE *pChangeType)
{
    BOOLEAN ret = FALSE;

    if(m_bHaveRemoved)
    {
        *pChangeType = E_SERVICE_REMOVED;
        ret = TRUE;
    }

    m_bHaveRemoved = FALSE;

    return ret;
}

#if ENABLE_S2_WORD
BOOLEAN msAPI_CM_HaveRemoveProgram(BYTE cRFChannelNumber, WORD wTSID, BYTE cPLP_ID, BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, BYTE cCountOfServiceID, BYTE sat,WORD freq)
#else
BOOLEAN msAPI_CM_HaveRemoveProgram(BYTE cRFChannelNumber, WORD wTSID, BYTE cPLP_ID, BYTE cHpLp, WORD *pwService_ID, MEMBER_SERVICETYPE *peService_Type, BYTE cCountOfServiceID)
#endif
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    DTVPROGRAMID_M *pMuxTable = msAPI_DtvDB_Get_ProgIdTable(eCurDbSel);
    static UINT32 u32SignalTimer = 0;
    WORD wProgramCount, wPosition, wOrder, wServiceId, i, j;
    U16 wIDIndex;
    BOOLEAN ret = FALSE;

    if(msAPI_Timer_DiffTimeFromNow(u32SignalTimer) < 3000)
    {
        return ret;
    }

    if(m_bVaildData == TRUE)
    {
        MApp_ZUI_ACT_ShutdownOSD();
        msAPI_CM_IsUserRemoveProgram(TRUE);    // Processing the original data
    }

    if( FALSE == IsPhysicalChannelNumberValid(cRFChannelNumber) )
    {
        return ret;
    }

    for(wIDIndex=0; wIDIndex < msAPI_CM_GetMuxMaxNumber(); wIDIndex++)
    {
        if( (cHpLp == pMuxTable[wIDIndex].cHpLp)
             && (cPLP_ID == pMuxTable[wIDIndex].cPLPID)
             && (cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber) )
        {
            break;
        }
    }

    if( msAPI_CM_GetMuxMaxNumber() <= wIDIndex )
    {
        return ret;
    }

    if(MApp_OAD_IsPowerOnCheck()||MApp_OAD_IsScheduleOnCheck())
	{
        return ret;
    }

    msAPI_CM_ResetRemoveProgramData();

    // DTV
    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    wPosition = wProgramCount-1;

    for(i = wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DTV, wPosition);

        wIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        wServiceId = m_astDTVProgramIndexTable[wOrder].wService_ID;

        if(cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber
            && cPLP_ID == pMuxTable[wIDIndex].cPLPID
            && cHpLp == pMuxTable[wIDIndex].cHpLp)
        {
            for(j=0; j < cCountOfServiceID; j++)
            {
                if(pwService_ID[j] == wServiceId )
                {
                    printf("match sid %x\n",wServiceId);
                    break;
                }
            }
            if(( cCountOfServiceID <= j )
              || ((cCountOfServiceID != 0) && (pMuxTable[wIDIndex].wTransportStream_ID != wTSID)))
            {
                ret = TRUE;
                goto DELETE;
            }
        }
        wPosition --;
    }

    // DATA
    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);
    wPosition = wProgramCount-1;

    for(i = wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_DATA, wPosition);

        wIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        wServiceId = m_astDTVProgramIndexTable[wOrder].wService_ID;

        if(cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber
            && cPLP_ID == pMuxTable[wIDIndex].cPLPID
            && cHpLp == pMuxTable[wIDIndex].cHpLp)
        {
            for(j=0; j < cCountOfServiceID; j++)
            {
                if(pwService_ID[j] == wServiceId )
                {
                    break;
                }
            }

            if(( cCountOfServiceID <= j )
              || ((cCountOfServiceID != 0) && (pMuxTable[wIDIndex].wTransportStream_ID != wTSID)))
            {
                ret = TRUE;
                goto DELETE;
            }
        }
        wPosition --;
    }

    // RADIO
    wProgramCount = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    wPosition = wProgramCount-1;

    for(i = wProgramCount; i > 0; i--)
    {
        wOrder = ConvertPositionToOrder(E_SERVICETYPE_RADIO, wPosition);

        wIDIndex = m_astDTVProgramIndexTable[wOrder].cIDIndex;
        wServiceId = m_astDTVProgramIndexTable[wOrder].wService_ID;

        if(cRFChannelNumber == pMuxTable[wIDIndex].cRFChannelNumber
            && cPLP_ID == pMuxTable[wIDIndex].cPLPID
            && cHpLp == pMuxTable[wIDIndex].cHpLp)
        {
            for(j=0; j < cCountOfServiceID; j++)
            {
                if(pwService_ID[j] == wServiceId )
                {
                    break;
                }
            }

            if(( cCountOfServiceID <= j )
              || ((cCountOfServiceID != 0) && (pMuxTable[wIDIndex].wTransportStream_ID != wTSID)))
            {
                ret = TRUE;
                goto DELETE;
            }
        }
        wPosition --;
    }

DELETE:

    if((ret == TRUE )&&((STATE_TOP_DIGITALINPUTS == MApp_TopStateMachine_GetTopState())
		||(STATE_TOP_CHANNELCHANGE == MApp_TopStateMachine_GetTopState())))
    {
        u32SignalTimer = msAPI_Timer_GetTime0();
        MApp_ZUI_ACT_ShutdownOSD();
        MApp_ZUI_ACT_StartupOSD(E_OSD_MESSAGE_BOX);
        MApp_ZUI_ACT_ExecuteWndAction( EN_EXE_SHOW_PROGRAM_DELETE_MSGBOX );
        m_bVaildData = TRUE;
        m_bRFChannelNumber = cRFChannelNumber;
        m_bPLP_ID = cPLP_ID;
        m_bHpLp = cHpLp;
        m_bCountOfServiceID = cCountOfServiceID;
        m_wTSID = wTSID;
        #if ENABLE_S2_WORD
        m_bsat = sat;
        m_wfreq = freq;
        #endif
        for(i = 0; i < m_bCountOfServiceID; i++) {
            m_wService_ID[i] = pwService_ID[i];
            m_eService_Type[i] = peService_Type[i];
        }
    }

     return ret;
}
#endif

AUDIOSTREAM_TYPE msAPI_CM_SIAudStreamType_To_AudStreamType(SI_AUDIOSTREAM_TYPE eSIAudStreamType)
{
    switch(eSIAudStreamType)
    {
        case E_SI_AUDIOSTREAM_AC3:
            return E_AUDIOSTREAM_AC3;
        case E_SI_AUDIOSTREAM_MPEG4:
            return E_AUDIOSTREAM_MPEG4;
        case E_SI_AUDIOSTREAM_AAC:
            return E_AUDIOSTREAM_AAC;
        case E_SI_AUDIOSTREAM_AC3P:
            return E_AUDIOSTREAM_AC3P;
        case E_SI_AUDIOSTREAM_MPEG:
            return E_AUDIOSTREAM_MPEG;
        case E_SI_AUDIOSTREAM_DRA:
            return E_AUDIOSTREAM_DRA;
        case E_SI_AUDIOSTREAM_INVALID:
            return E_AUDIOSTREAM_INVALID;

        default:
            break;
    }

    return E_AUDIOSTREAM_INVALID;
}

AUDIOSTREAM_TYPE msAPI_CM_Get_AudStreamType_By_AudInfo(AUD_INFO* pstAudInfo)
{
    return msAPI_CM_SIAudStreamType_To_AudStreamType(pstAudInfo->eSIAudType);
}

#define DEBUG_Get_MS_TPSetting(x)   //x
BOOLEAN msAPI_CM_Get_MS_TPSetting_By_IdTabIdx(U16 u16IdTabIdx, MS_TP_SETTING* pstMS_TP_SETTING)
{
    //PRINT_CURRENT_LINE();

    DEBUG_Get_MS_TPSetting( printf("msAPI_CM_Get_MS_TPSetting_By_IdTabIdx(idx=%u)\n", u16IdTabIdx); );

    // Check para ...
    if( pstMS_TP_SETTING == NULL )
        return FALSE;


    DTVPROGRAMID_M stPhyCh;

    memset( &stPhyCh, 0, sizeof(stPhyCh) );

    if( FALSE == msAPI_CM_GetIDTable(u16IdTabIdx, (BYTE *)&stPhyCh, E_DATA_ID_TABLE) )
        return FALSE;

    pstMS_TP_SETTING->u32Frequency   = stPhyCh.u32Frequency;

    pstMS_TP_SETTING->u32Symbol_rate = msAPI_CM_Get_IDTab_SymbolRate(&stPhyCh);

    pstMS_TP_SETTING->u8Modulation   = stPhyCh.QamMode;

    pstMS_TP_SETTING->enBandWidth = stPhyCh.enBandWidth;

    DEBUG_Get_MS_TPSetting( printf(" Freq=%u\n", stPhyCh.u32Frequency); );
    DEBUG_Get_MS_TPSetting( printf(" u32Symbol_rate=%u\n", pstMS_TP_SETTING->u32Symbol_rate); );
    DEBUG_Get_MS_TPSetting( printf(" mode=%u\n", stPhyCh.QamMode); );
    DEBUG_Get_MS_TPSetting( printf(" enBandWidth=%u\n", stPhyCh.enBandWidth); );

    return TRUE;
}

#if( ENABLE_CM_STORE_AUD_INFO_NEW_METHOD )
BOOLEAN msAPI_CM_Add_AudInfo(AUD_INFO * pstCMAudInfo, U8 u8Count)
{
    U16 u16AudInfoTabIdx = msAPI_DtvDB_AudInfo_AllocSpace(u8Count);
    printf("u16AudInfoTabIdx=%u\n", u16AudInfoTabIdx);

    if( u16AudInfoTabIdx == CM_AUD_INFO_INVALID_INDEX )
        return FALSE;

    msAPI_DtvDB_Set_AudInfoTable(CUR_DB_SEL(), u16AudInfoTabIdx, pstCMAudInfo, u8Count );

    return TRUE;
}
#endif

//------------------------------------------------------------------
#else
#if 0
MEMBER_SERVICETYPE msAPI_CM_GetCurrentServiceType(void)
{
    return E_SERVICETYPE_ATV;
}

WORD msAPI_CM_CountProgram(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    UNUSED(bServiceType);
    UNUSED(eBoundary);

    return 0;
}

WORD msAPI_CM_GetCurrentPosition(MEMBER_SERVICETYPE bServiceType)
{
    UNUSED(bServiceType);
    return INVALID_PROGRAM_POSITION;
}
#endif
#endif//#if ENABLE_DTV/(ENABLE_API_DTV_SYSTEM)


#undef API_DTVSYSTEM_C

