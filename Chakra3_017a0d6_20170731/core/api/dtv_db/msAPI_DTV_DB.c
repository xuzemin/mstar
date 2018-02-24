
#include "Board.h"

#if( ENABLE_DTV /*&& ENABLE_API_DTV_SYSTEM_2015*/ )
#include <stddef.h>     /* offsetof */

#include "msAPI_DTV_Common.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_DTVSystem_Private.h"

#include "msAPI_DTV_DB.h"
#include "msAPI_DTV_DB_RamDisk.h"

//#include "MApp_SaveData.h"


//=========================================================================

extern BOOLEAN IsServiceTypeValid(MEMBER_SERVICETYPE bServiceType);
//extern U16 msAPI_DtvDB_Get_ProgTableArraySize(TypDtvDbSel eCurDbSel);

//=========================================================================


//=========================================================================

typedef U16 TYP_au16DtvProgramCount[MAX_COUNT_PROGRAM_OPTION];

typedef struct
{
    // DataBase Magic ID
    U16 u16DataBaseMagicId;

    // DTV Program Table Map
    U8* pu8ProgramTableMap;
    U16 u16ProgramTableMapArraySize;
    U32 u32ProgramTableMapRamDiskAddr;

    // DTV Program Table
    //U8* pstProgramTable;
    U16 u16ProgramTableArraySize;
    U32 u32ProgramTableRamDiskAddr;

    // DTV ID Table Map
    U8* pu8IDTableMap;
    U16 u16IDTableMapArraySize;
    U32 u32IDTableMapRamDiskAddr;

    // DTV Program ID Table
    DTVPROGRAMID_M * pstProgIdTable;
    U16 u16ProgIdTableArraySize;
    U32 u32ProgIdTableRamDiskAddr;

    // NetWork:
    DTVNETWORK * pstNetWorkTable;
    U16 u16NetWorkTableArraySize;
    U32 u32NetWorkTableRamDiskAddr;

    // Program Count
    TYP_au16DtvProgramCount * p_au16ProgramCount;

    // Program Index table
    DTVPROGRAMINDEX * pstProgramIndexTable;
    U16 u16ProgramIndexTableArraySize;

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
    // Aud info Table
    //AUD_INFO * pstAudInfoTab;
    U16 u16AudInfoTableArraySize;
    U32 u32AudInfoTableRamDiskAddr;
#endif
} StuDtvDbInfo;

//------------------------------------------------------------------

// DataBase - DVBT

extern WORD m_awProgramCount[E_CM_SERVICE_POS_NUMS][MAX_COUNT_PROGRAM_OPTION];


// DataBase - DVBS
#if 0//ENABLE_S2
extern DTVPROGRAMINDEX m_astS2ProgramIndexTable[MAX_DTV_S2_PROGRAM]; // Program Index Table
extern BYTE m_acS2ProgramTableMap[MAX_S2_CHANNELTABLE_MAP]; // Program Table Map
extern BYTE m_acs2IDtableMap[MAX_S2_IDTABLE_MAP];   // ID Table Map
extern DTVPROGRAMID_M _astS2ProgramIDTable[MAX_DTV_S2_MUX_NUMBER]; // ID Table
extern WORD m_awS2ProgramCount[3][MAX_COUNT_PROGRAM_OPTION];
extern DTVNETWORK _astS2Network[MAX_NETWOEK_S2_NUMBER]; // NetWork Table
#endif

StuDtvDbInfo s_astDtvDbInfo[E_DTV_DB_NUM] =
{
    // DVBT/DTMB
    {
        // DataBase Magic ID
        DTVDATA_ID,
        // DTV Program Table Map: Array, Array Size, RamDiskAddr
        g_acDTVProgramTableMap_DVBT, MAX_DTVCHANNELTABLE_MAP,    BASEADDRESS_PR_DTVPRTABLEMAP,
        // DTV Program Table:  Array, Array Size, RamDiskAddr
                                    MAX_DTVPROGRAM,             BASEADDRESS_PR_DTVPRTABLE,

        // DTV ID Table Map: Array, Array Size, RamDiskAddr
        g_acDTVIDtableMap_DVBT,     MAX_DTVIDTABLE_MAP,         BASEADDRESS_PR_DTVIDTABLEMAP,
        // DTV Program ID Table: Array, Array Size, RamDiskAddr
        g_astDTVProgramIDTable_DVBT, MAX_MUX_NUMBER,             BASEADDRESS_PR_DTVIDTABLE,

        // NetWork
        g_astDTVNetwork_DVBT,       MAX_NETWOEK_NUMBER,         BASEADDRESS_PR_DTVNETWORK,
        // Program Count
        g_au16ProgramCount_DVBT,
        // Program Index: Array, Array size
        g_astDTVProgramIndexTable_DVBT,MAX_DTVPROGRAM,

    #if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
        // Aud info Table
        //U16 u16AudInfoTableArraySize;
        CM_AUDINFO_MAX_NUM_DVB,
        //U32 u32AudInfoTableRamDiskAddr;
        BASEADDRESS_PR_AUD_INFO,
    #endif

    },

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    // DVBC
    {
        // DataBase Magic ID
        DTVDATA_ID_DVBC,
        // DTV Program Table Map
        m_acDTVProgramTableMap_DVBC,MAX_DTVCHANNELTABLE_MAP_DVBC, BASEADDRESS_PR_DTV_C_PRTABLEMAP,
        // DTV Program Table:  Array, Array Size, RamDiskAddr
                                    MAX_DTVPROGRAM_DVBC,        BASEADDRESS_PR_DTV_C_PRTABLE,

        // DTV ID Table Map: Array, Array Size, RamDiskAddr
        m_acDTVIDtableMap_DVBC,     MAX_DTV_C_IDTABLE_MAP,      BASEADDRESS_PR_DTV_C_IDTABLEMAP,
        // DTV Program ID Table: Array, Array Size, RamDiskAddr
        g_astDTVProgramIDTable_DVBC,MAX_MUX_NUMBER_DVBC,       BASEADDRESS_PR_DTV_C_IDTABLE,

        // NetWork
        s_astDTVNetwork_DVBC,       MAX_NETWOEK_NUMBER,         BASEADDRESS_PR_DTV_C_DTVNETWORK,
        // Program Count
        g_au16ProgramCount_DVBC,

        // Program Index: Array, Array size
        m_astDTVProgramIndexTable_DVBC, MAX_DTVPROGRAM_DVBC,

    #if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
        // Aud info Table
        //U16 u16AudInfoTableArraySize;
        CM_AUDINFO_MAX_NUM_DVBC,
        //U32 u32AudInfoTableRamDiskAddr;
        BASEADDRESS_PR_AUD_INFO_DVBC,
    #endif

    },
#endif

#if(ENABLE_S2)
    // DVBS
    {
        // DataBase Magic ID
        DTVDATA_ID_DVBS,

        // DTV Program Table Map
        m_acS2ProgramTableMap,  MAX_S2_CHANNELTABLE_MAP,    S2_BASEADDRESS_PR_DTVPRTABLEMAP,
        // DTV Program Table:  Array, Array Size, RamDiskAddr
                                MAX_DTV_S2_PROGRAM,         S2_BASEADDRESS_PR_DTVPRTABLE,

        // DTV ID Table Map: Array, Array Size, RamDiskAddr
        m_acs2IDtableMap,       MAX_S2_IDTABLE_MAP,         S2_BASEADDRESS_PR_DTVIDTABLEMAP,
        // DTV Program ID Table: Array, Array Size, RamDiskAddr
        _astS2ProgramIDTable,   MAX_DTV_S2_MUX_NUMBER,      S2_BASEADDRESS_PR_DTVIDTABLE,

        // NetWork
        _astS2Network,          MAX_NETWOEK_S2_NUMBER,      S2_BASEADDRESS_PR_DTVNETWORK,
        // Program Count
        m_awS2ProgramCount,
        // Program Index: Array, Array size
        m_astS2ProgramIndexTable, MAX_DTV_S2_PROGRAM,

    #if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
        // Aud info Table
        //U16 u16AudInfoTableArraySize;
        CM_AUDINFO_MAX_NUM_DVBS,
        //U32 u32AudInfoTableRamDiskAddr;
        S2_BASEADDRESS_PR_AUD_INFO,
    #endif

    },
#endif
};

StuDtvDbInfo* msAPI_DtvDB_Get_DtvDbInfo(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel > E_DTV_DB_NUM )
        eCurDbSel = E_DTV_DB_SEL_DVBT;

    return &(s_astDtvDbInfo[eCurDbSel]);
}

StuDtvDbInfo* msAPI_DtvDB_Get_CurDtvDbInfo(void)
{
    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();
    return msAPI_DtvDB_Get_DtvDbInfo(eCurDbSel);
}

//========================================================================
U16 msAPI_DtvDB_Get_DataBaseMagicId(TypDtvDbSel eDtvDbSel)
{
    if( eDtvDbSel >= E_DTV_DB_NUM ) // Coverity189831
    {
        return 0;
    }

    return s_astDtvDbInfo[eDtvDbSel].u16DataBaseMagicId;
}

U8* msAPI_DtvDB_Get_ProgTableMap(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189842
    {
        return 0;
    }

    return s_astDtvDbInfo[eCurDbSel].pu8ProgramTableMap;
}

U16 msAPI_DtvDB_Get_ProgTableMapArraySize(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189843
    {
        return 0;
    }

    return s_astDtvDbInfo[eCurDbSel].u16ProgramTableMapArraySize;
}

U32 msAPI_DtvDB_Get_ProgTableMapRamDiskAddr(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189844
        return 0;

    return s_astDtvDbInfo[eCurDbSel].u32ProgramTableMapRamDiskAddr;
}

U16 msAPI_DtvDB_Get_ProgTableArraySize(TypDtvDbSel eDtvDbSel)
{
    if( eDtvDbSel >= E_DTV_DB_NUM ) // Coverity189841
    {
        return 0;
    }

    return s_astDtvDbInfo[eDtvDbSel].u16ProgramTableArraySize;
}

U32 msAPI_DtvDB_Get_ProgTableRamDiskAddr(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189845
        return 0;

    return s_astDtvDbInfo[eCurDbSel].u32ProgramTableRamDiskAddr;
}

BOOLEAN msAPI_DtvDB_Is_ProgTableIndexValid(TypDtvDbSel eDtvDbSel, U16 u16ProgIndex )
{
    U16 u16ProgTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel);
    if( u16ProgIndex >= u16ProgTableArraySize )
    {
        return FALSE;
    }
    return TRUE;
}

U8* msAPI_DtvDB_Get_ProgIdTableMap(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189837
    {
        return 0;
    }

    return s_astDtvDbInfo[eCurDbSel].pu8IDTableMap;
}

U16 msAPI_DtvDB_Get_ProgIdTableMapArraySize(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189838
    {
        return 0;
    }

    return s_astDtvDbInfo[eCurDbSel].u16IDTableMapArraySize;
}

U32 msAPI_DtvDB_Get_ProgIdTableMapRamDiskAddr(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189839
        return 0;

    return s_astDtvDbInfo[eCurDbSel].u32IDTableMapRamDiskAddr;
}

DTVPROGRAMID_M* msAPI_DtvDB_Get_ProgIdTable(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189835
    {
        return NULL;
    }

    return (s_astDtvDbInfo[eCurDbSel].pstProgIdTable);
}

U16 msAPI_DtvDB_Get_ProgIdTableArraySize(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189836
    {
        return 0;
    }

    return s_astDtvDbInfo[eCurDbSel].u16ProgIdTableArraySize;
}

U32 msAPI_DtvDB_Get_ProgIdTableRamDiskAddr(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189840
        return 0;

    return s_astDtvDbInfo[eCurDbSel].u32ProgIdTableRamDiskAddr;
}

BOOLEAN msAPI_DtvDB_Is_IDTableIndexValid(TypDtvDbSel eDtvDbSel, U16 u16IDIndex )
{
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    if( u16IDIndex >= u16IDTableArraySize )
    {
        return FALSE;
    }
    return TRUE;
}

DTVNETWORK* msAPI_DtvDB_Get_NetWorkTable(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189832
    {
        return NULL;
    }

    return s_astDtvDbInfo[eCurDbSel].pstNetWorkTable;
}

U16 msAPI_DtvDB_Get_NetWorkTableArraySize(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189833
    {
        return 0;
    }

    return s_astDtvDbInfo[eCurDbSel].u16NetWorkTableArraySize;
}

U32 msAPI_DtvDB_Get_NetWorkTableRamDiskAddr(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189834
        return 0;

    return s_astDtvDbInfo[eCurDbSel].u32NetWorkTableRamDiskAddr;
}

DTVPROGRAMINDEX* msAPI_DtvDB_Get_ProgramIndexTable(TypDtvDbSel eDtvDbSel)
{
    if( eDtvDbSel >= E_DTV_DB_NUM ) // Coverity189846
        return 0;

    return s_astDtvDbInfo[eDtvDbSel].pstProgramIndexTable;
}

U16 msAPI_DtvDB_Get_ProgramIndexTableArraySize(TypDtvDbSel eDtvDbSel)
{
    if( eDtvDbSel >= E_DTV_DB_NUM ) // Coverity189847
    {
        return 0;
    }

    return s_astDtvDbInfo[eDtvDbSel].u16ProgramIndexTableArraySize;
}

//========================================================================

U32 msAPI_DtvDB_Get_RamDiskAddr_Identify(TypDtvDbSel eCurDbSel)
{
    eCurDbSel = eCurDbSel; // Unused warning

#if(ENABLE_S2)
    if( eCurDbSel == E_DTV_DB_SEL_DVBS )
        return S2_BASEADDRESS_PR_IDENT;
#endif

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eCurDbSel == E_DTV_DB_SEL_DVBC)
        return BASEADDRESS_DTV_DVBC_IDENT;
#endif

    return BASEADDRESS_PR_IDENT;
}

U32 msAPI_DtvDB_Get_RamDiskAddr_LogicalChannelNumberArranged(TypDtvDbSel eCurDbSel)
{
    eCurDbSel = eCurDbSel; // Unused warning

    U32 u32RamDiskAddr_LogicalChannelNumberArranged;

#if(ENABLE_S2)
    if( eCurDbSel == E_DTV_DB_SEL_DVBS )
    {
        u32RamDiskAddr_LogicalChannelNumberArranged = S2_BASEADDRESS_PR_IS_LCN_ARRANGED;
    }
    else
#endif
#if( ENABLE_DVBC&&DVB_T_C_DIFF_DB )
    if( eCurDbSel == E_DTV_DB_SEL_DVBC )
    {
        u32RamDiskAddr_LogicalChannelNumberArranged = BASEADDRESS_DTV_DVBC_IS_LCN_ARRANGED;
    }
    else
#endif
    {
        u32RamDiskAddr_LogicalChannelNumberArranged = BASEADDRESS_PR_IS_LCN_ARRANGED;
    }

    return u32RamDiskAddr_LogicalChannelNumberArranged;
}

#if (NTV_FUNCTION_ENABLE)
U32 msAPI_DtvDB_Get_RamDiskAddr_FavoriteRegion(TypDtvDbSel eDtvDbSel)
{
#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
        return BASEADDRESS_PR_FAVORITE_REGION_DVBS;
#endif

#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC)
        return BASEADDRESS_PR_FAVORITE_REGION_DVBC;
#endif

    return BASEADDRESS_PR_FAVORITE_REGION;
}
#endif

U32 msAPI_DtvDB_Get_RamDiskAddr_ProgTable_ByIndex(TypDtvDbSel eCurDbSel, U16 u16PRIndex)
{
    return msAPI_DtvDB_Get_ProgTableRamDiskAddr(eCurDbSel) + (u16PRIndex * sizeof(DTV_CHANNEL_INFO));
}

U32 msAPI_DtvDB_Get_RamDiskAddr_IdTable_ByIndex(TypDtvDbSel eCurDbSel, U16 u16IdIndex)
{
    return msAPI_DtvDB_Get_ProgIdTableRamDiskAddr(eCurDbSel) + (u16IdIndex * sizeof(DTVPROGRAMID_M));
}

U32 msAPI_DtvDB_Get_RamDiskAddr_NetWork_ByIndex(TypDtvDbSel eCurDbSel, U16 u16NetWorkIndex)
{
    return msAPI_DtvDB_Get_NetWorkTableRamDiskAddr(eCurDbSel) + (u16NetWorkIndex * sizeof(DTVNETWORK));
}


//====================================================================
/*
TYP_au16DtvProgramCount* msAPI_DtvDB_Get_ProgramCountTable(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel > E_DTV_DB_NUM )
        return 0;


    printf("m_awProgramCount=0x%X\n", (U32)m_awProgramCount);
    printf("m_awDVBCProgramCount=0x%X\n", (U32)m_awDVBCProgramCount);
    printf("m_awS2ProgramCount=0x%X\n", (U32)m_awS2ProgramCount);

    return s_astDtvDbInfo[eCurDbSel].p_au16ProgramCount;
}
*/

//====================================================================

BOOLEAN msAPI_DtvDB_Set_Identify(TypDtvDbSel eDtvDbSel, U16 u16Identify)
{
    U32 u32RamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_Identify(eDtvDbSel);

    return SetNVRAM(u32RamDiskAddr, (BYTE *)&u16Identify, sizeof(u16Identify));
}

U16 msAPI_DtvDB_Get_Identify(TypDtvDbSel eDtvDbSel)
{
    U32 u32RamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_Identify(eDtvDbSel);
    U16 u16Identify = 0;

    GetNVRAM(u32RamDiskAddr, (BYTE *)&u16Identify, sizeof(u16Identify));

    return u16Identify;
}

#if (NTV_FUNCTION_ENABLE)
BOOLEAN msAPI_DtvDB_Set_FavoriteRegion(TypDtvDbSel eDtvDbSel, U8 u8FavoriteRegion)
{
    U32 u32RamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_FavoriteRegion(eDtvDbSel);

    return SetNVRAM(u32RamDiskAddr, (BYTE *)&u8FavoriteRegion, sizeof(u8FavoriteRegion));
}

U8 msAPI_DtvDB_Get_FavoriteRegion(TypDtvDbSel eDtvDbSel)
{
    U32 u32RamDiskAddr = msAPI_DtvDB_Get_RamDiskAddr_FavoriteRegion(eDtvDbSel);
    U8 u8FavoriteRegion;

    GetNVRAM(u32RamDiskAddr, (BYTE *)&u8FavoriteRegion, sizeof(u8FavoriteRegion));

    return u8FavoriteRegion;
}
#endif

BOOLEAN msAPI_DtvDB_Set_CurServiceType(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE eServiceType)
{
    if( FALSE == IsServiceTypeValid(eServiceType) )
    {
        return FALSE;
    }

    eDtvDbSel = eDtvDbSel; // Unused warning

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        stGenSetting.stDvbsSetting.eCurServiceType = eServiceType;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        stGenSetting.stTvSetting.eCurrentServiceType_DVBC = eServiceType;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.eCurrentServiceType = eServiceType;
    }

    return TRUE;
}

MEMBER_SERVICETYPE msAPI_DtvDB_Get_CurServiceType(TypDtvDbSel eDtvDbSel)
{
    MEMBER_SERVICETYPE bServiceType = E_SERVICETYPE_DTV;

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        bServiceType = stGenSetting.stDvbsSetting.eCurServiceType;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        bServiceType = stGenSetting.stTvSetting.eCurrentServiceType_DVBC;
    }
    else
#endif
    {
        bServiceType = stGenSetting.stTvSetting.eCurrentServiceType;
    }

    if( FALSE == IsServiceTypeValid(bServiceType) )
    {
        bServiceType = DEFAULT_CURRENT_SERVICETYPE;
        msAPI_DtvDB_Set_CurServiceType(eDtvDbSel, bServiceType);
    }

    return bServiceType;
}

BOOLEAN msAPI_DtvDB_Set_CurOrderOfTV(TypDtvDbSel eDtvDbSel, U16 u16Order)
{
    // Check u16Order
    U32 u32ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);


    if( u16Order >= u32ProgramIndexTableArraySize )
    {
        printf("\nError: u16Order=%u >= u32ProgramIndexTableArraySize=%u!\n", u16Order, u32ProgramIndexTableArraySize);
        return FALSE;
    }

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        stGenSetting.stDvbsSetting.u16CurDtvOrder = u16Order;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        stGenSetting.stTvSetting.u16CurDtvOrder_DVBC = u16Order;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.u16DTVRFChannelOrder = u16Order;
    }

    return TRUE;
}

U16 msAPI_DtvDB_Get_CurOrderOfTV(TypDtvDbSel eDtvDbSel)
{
    //U32 u32ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    U16 u16Order = 0;

    eDtvDbSel = eDtvDbSel; // Unused warning

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        u16Order = stGenSetting.stDvbsSetting.u16CurDtvOrder;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        u16Order = stGenSetting.stTvSetting.u16CurDtvOrder_DVBC;
    }
    else
#endif
    {
        u16Order = stGenSetting.stTvSetting.u16DTVRFChannelOrder;
    }

    return u16Order;
}

BOOLEAN msAPI_DtvDB_Set_CurOrderOfRadio(TypDtvDbSel eDtvDbSel, U16 u16Order)
{
    // Check u16Order
    U32 u32ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);


    if( u16Order >= u32ProgramIndexTableArraySize )
    {
        printf("\nError: u16Order=%u >= u32ProgramIndexTableArraySize=%u!\n", u16Order, u32ProgramIndexTableArraySize);
        return FALSE;
    }

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        stGenSetting.stDvbsSetting.u16CurDtvRadioOrder = u16Order;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        stGenSetting.stTvSetting.u16CurDtvRadioOrder_DVBC = u16Order;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.u16RADIORFChannelOrder = u16Order;
    }

    return TRUE;
}

U16 msAPI_DtvDB_Get_CurOrderOfRadio(TypDtvDbSel eDtvDbSel)
{
    //U32 u32ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    U16 u16Order = 0;

    eDtvDbSel = eDtvDbSel; // Unused warning


#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        u16Order = stGenSetting.stDvbsSetting.u16CurDtvRadioOrder;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        u16Order = stGenSetting.stTvSetting.u16CurDtvRadioOrder_DVBC;
    }
    else
#endif
    {
        u16Order = stGenSetting.stTvSetting.u16RADIORFChannelOrder;
    }

    return u16Order;
}

BOOLEAN msAPI_DtvDB_Set_CurOrderOfData(TypDtvDbSel eDtvDbSel, U16 u16Order)
{
    // Check u16Order
    U32 u32ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);


    if( u16Order >= u32ProgramIndexTableArraySize )
    {
        printf("\nError: u16Order=%u >= u32ProgramIndexTableArraySize=%u!\n", u16Order, u32ProgramIndexTableArraySize);
        return FALSE;
    }

#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        stGenSetting.stDvbsSetting.u16CurDtvDataOrder = u16Order;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        stGenSetting.stTvSetting.u16CurDtvDataOrder_DVBC = u16Order;
    }
    else
#endif
    {
        stGenSetting.stTvSetting.u16DATARFChannelOrder = u16Order;
    }

    return TRUE;
}

U16 msAPI_DtvDB_Get_CurOrderOfData(TypDtvDbSel eDtvDbSel)
{
    //U32 u32ProgramIndexTableArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);
    U16 u16Order = 0;

    eDtvDbSel = eDtvDbSel; // Unused warning


#if(ENABLE_S2)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBS )
    {
        u16Order = stGenSetting.stDvbsSetting.u16CurDtvDataOrder;
    }
    else
#endif
#if(ENABLE_DVBC&&DVB_T_C_DIFF_DB)
    if( eDtvDbSel == E_DTV_DB_SEL_DVBC )
    {
        u16Order = stGenSetting.stTvSetting.u16CurDtvDataOrder_DVBC;
    }
    else
#endif
    {
        u16Order = stGenSetting.stTvSetting.u16DATARFChannelOrder;
    }

    return u16Order;
}

BOOLEAN msAPI_DtvDB_Save_ProgramTableMap(TypDtvDbSel eDtvDbSel, U8* pu8ProgTableMap, U16 u16ArraySize )
{
    U16 u16ProgTableMapArraySize = msAPI_DtvDB_Get_ProgTableMapArraySize(eDtvDbSel);
    U32 u32ProgTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgTableMapRamDiskAddr(eDtvDbSel);

    if( u16ArraySize > u16ProgTableMapArraySize )
    {
        u16ArraySize = u16ProgTableMapArraySize;
    }

    SetNVRAM(u32ProgTableMapRamDiskAddr, pu8ProgTableMap, u16ArraySize * sizeof(U8) );

    return TRUE;
}

BOOLEAN msAPI_DtvDB_Load_ProgramTableMap(TypDtvDbSel eDtvDbSel, U8* pu8ProgTableMap, U16 u16ArraySize )
{
    U16 u16ProgTableMapArraySize = msAPI_DtvDB_Get_ProgTableMapArraySize(eDtvDbSel);
    U32 u32ProgTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgTableMapRamDiskAddr(eDtvDbSel);

    if( u16ArraySize > u16ProgTableMapArraySize )
    {
        u16ArraySize = u16ProgTableMapArraySize;
    }

    GetNVRAM(u32ProgTableMapRamDiskAddr, pu8ProgTableMap, u16ArraySize * sizeof(U8) );

    return TRUE;
}

BOOLEAN msAPI_DtvDB_Save_IDTableMap(TypDtvDbSel eDtvDbSel, U8* pu8IDTableMap, U16 u16ArraySize )
{
    U16 u16IDTableMapArraySize = msAPI_DtvDB_Get_ProgIdTableMapArraySize(eDtvDbSel);
    U32 u32IDTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgIdTableMapRamDiskAddr(eDtvDbSel);

    if( u16ArraySize > u16IDTableMapArraySize )
    {
        u16ArraySize = u16IDTableMapArraySize;
    }

    return SetNVRAM(u32IDTableMapRamDiskAddr, pu8IDTableMap, u16ArraySize * sizeof(U8) );
}

BOOLEAN msAPI_DtvDB_Load_IDTableMap(TypDtvDbSel eDtvDbSel, U8* pu8IDTableMap, U16 u16ArraySize )
{
    U16 u16IDTableMapArraySize = msAPI_DtvDB_Get_ProgIdTableMapArraySize(eDtvDbSel);
    U32 u32IDTableMapRamDiskAddr = msAPI_DtvDB_Get_ProgIdTableMapRamDiskAddr(eDtvDbSel);

    if( u16ArraySize > u16IDTableMapArraySize )
    {
        u16ArraySize = u16IDTableMapArraySize;
    }

    GetNVRAM(u32IDTableMapRamDiskAddr, pu8IDTableMap, u16ArraySize * sizeof(U8) );

    return TRUE;
}

BOOLEAN msAPI_DtvDB_Load_IDTable(TypDtvDbSel eDtvDbSel, DTVPROGRAMID_M* pstIDTable, U16 u16ArraySize )
{
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);
    U32 u32IDTableRamDiskAddr = msAPI_DtvDB_Get_ProgIdTableRamDiskAddr(eDtvDbSel);


    if( u16ArraySize > u16IDTableArraySize )
    {
        u16ArraySize = u16IDTableArraySize;
    }

    GetNVRAM(u32IDTableRamDiskAddr, (U8*)pstIDTable, u16ArraySize * sizeof(DTVPROGRAMID_M) );

    return TRUE;
}

BOOLEAN msAPI_DtvDB_Load_NetWorkTable(TypDtvDbSel eDtvDbSel, DTVNETWORK* pstNetWorkTable, U16 u16ArraySize )
{
    U16 u16NetWorkTableArraySize = msAPI_DtvDB_Get_NetWorkTableArraySize(eDtvDbSel);
    U32 u32NetWorkTableRamDiskAddr = msAPI_DtvDB_Get_NetWorkTableRamDiskAddr(eDtvDbSel);


    if( u16ArraySize > u16NetWorkTableArraySize )
    {
        u16ArraySize = u16NetWorkTableArraySize;
    }

    GetNVRAM(u32NetWorkTableRamDiskAddr, (U8*)pstNetWorkTable, u16ArraySize * sizeof(DTVNETWORK) );

    return TRUE;
}

#if(ENABLE_CM_STORE_AUD_INFO_NEW_METHOD)
U16 msAPI_DtvDB_Get_AudInfoTableArraySize(TypDtvDbSel eDtvDbSel)
{
    if( eDtvDbSel >= E_DTV_DB_NUM ) // Coverity189841
    {
        return 0;
    }

    return s_astDtvDbInfo[eDtvDbSel].u16AudInfoTableArraySize;
}

U32 msAPI_DtvDB_Get_AudInfoTableRamDiskAddr(TypDtvDbSel eCurDbSel)
{
    if( eCurDbSel >= E_DTV_DB_NUM ) // Coverity189845
        return 0;

    return s_astDtvDbInfo[eCurDbSel].u32AudInfoTableRamDiskAddr;
}

BOOLEAN msAPI_DtvDB_Get_AudInfoTable(TypDtvDbSel eDtvDbSel, U16 u16Index, AUD_INFO* pstAudInfoTable, U16 u16ArraySize )
{
    U16 u16AudInfoTableArraySize = msAPI_DtvDB_Get_AudInfoTableArraySize(eDtvDbSel);

    if( (u16Index+u16ArraySize) > u16AudInfoTableArraySize )
    {
        return FALSE;
    }

    U32 u32AudInfoTableRamDiskAddr = msAPI_DtvDB_Get_AudInfoTableRamDiskAddr(eDtvDbSel);

    GetNVRAM(u32AudInfoTableRamDiskAddr + (u16Index*sizeof(AUD_INFO)), (U8*)pstAudInfoTable, u16ArraySize * sizeof(AUD_INFO) );

    return TRUE;
}

BOOLEAN msAPI_DtvDB_Set_AudInfoTable(TypDtvDbSel eDtvDbSel, U16 u16Index, AUD_INFO* pstAudInfoTable, U16 u16ArraySize )
{
    U16 u16AudInfoTableArraySize = msAPI_DtvDB_Get_AudInfoTableArraySize(eDtvDbSel);

    if( (u16Index+u16ArraySize) > u16AudInfoTableArraySize )
    {
        return FALSE;
    }

    U32 u32AudInfoTableRamDiskAddr = msAPI_DtvDB_Get_AudInfoTableRamDiskAddr(eDtvDbSel);

    SetNVRAM(u32AudInfoTableRamDiskAddr + (u16Index*sizeof(AUD_INFO)), (U8*)pstAudInfoTable, u16ArraySize * sizeof(AUD_INFO) );

    return TRUE;
}

void msAPI_DtvDB_AudInfoTable_ResetAll(TypDtvDbSel eDtvDbSel, AUD_INFO* pstAudInfoTable)
{
    U16 u16AudInfoTableArraySize = msAPI_DtvDB_Get_AudInfoTableArraySize(eDtvDbSel);

    U16 i;
    for( i = 0; i < u16AudInfoTableArraySize; ++ i )
    {
        msAPI_DtvDB_Set_AudInfoTable(eDtvDbSel, i, pstAudInfoTable, 1);
    }
}

U16 msAPI_DtvDB_AudInfo_AllocSpace(U8 u8SpaceCount)
{
    printf("msAPI_DtvDB_AudInfo_AllocSpace(u8SpaceCount=%u)\n", u8SpaceCount);

    TypDtvDbSel eCurDbSel = msAPI_DTV_Comm_Get_DBSel();

    U32 u32AudInfoTableRamDiskAddr = msAPI_DtvDB_Get_AudInfoTableRamDiskAddr( eCurDbSel );
    printf("u32AudInfoTableRamDiskAddr=0x%X\n", u32AudInfoTableRamDiskAddr);

    U32 u32AudInfoTableDramAddr = u32AudInfoTableRamDiskAddr + RAM_DISK_MEM_ADDR;

    printf("u32AudInfoTableDramAddr=0x%X\n", u32AudInfoTableDramAddr);

    AUD_INFO * pstAudInfoTab = (AUD_INFO *)MsOS_PA2KSEG0(u32AudInfoTableDramAddr);

    printf("pstAudInfoTab=0x%X\n", pstAudInfoTab);

    U16 u16AudInfoTableArraySize = msAPI_DtvDB_Get_AudInfoTableArraySize(eCurDbSel);

    U16 i;
    U16 u16ValidFrom = CM_AUD_INFO_INVALID_INDEX;
    U8 u8ValidCount = 0;

    BOOL bFindStart = TRUE;
    BOOL bFound = FALSE;

    for( i = 0; i < u16AudInfoTableArraySize; ++ i )
    {
        if( bFindStart )
        {
            if( pstAudInfoTab[i].wAudPID == INVALID_PID )
            {
                u16ValidFrom = i;
                u8ValidCount = 1;
                bFindStart = FALSE;
            }
            else
            {
                u8ValidCount = 0;
            }
        }
        else
        {
            if( pstAudInfoTab[i].wAudPID == INVALID_PID )
            {
                u8ValidCount += 1;
                if( u8ValidCount >= u8SpaceCount )
                {
                    // Successful
                    bFound = TRUE;
                    break;
                }
            }
            else
            {
                bFindStart = TRUE;
            }
        }
    }


    if( bFound )
    {
        printf(" => u16ValidFrom=%u\n", u16ValidFrom);
        return u16ValidFrom;
    }
    else
    {
        printf(" => Can not find space!\n");
        return CM_AUD_INFO_INVALID_INDEX;
    }
}

#endif

#endif

