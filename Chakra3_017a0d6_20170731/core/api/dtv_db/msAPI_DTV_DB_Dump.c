
#include "Board.h"

#if( ENABLE_DTV_DB_DUMP )

#include "msAPI_DTV_Common.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_DTV_DB.h"
#include "msAPI_DTV_DB_Dump.h"
#include "msAPI_DTVSystem_Private.h"

#include "MApp_SaveData.h"

#include <stddef.h>


//-------------------------------------------------------------------------
U16 msAPI_DtvDB_Get_ProgramCount(TypDtvDbSel eDtvDbSel, U8 u8ServiceIdx, U8 u8OptionIdx );

//==========================================================

BOOL msAPI_DTV_DB_Is_ProgramActive(U16 u16ProgIdx, U8* pu8ProgTblMap)
{
    if( pu8ProgTblMap[u16ProgIdx/8] & (1 << (u16ProgIdx%8)) )
        return TRUE;

    return FALSE;
}

BOOL msAPI_DTV_DB_Is_IDTabActive(U16 u16IDIdx, U8* pu8IDTblMap)
{
    if( pu8IDTblMap[u16IDIdx/8] & (1 << (u16IDIdx%8)) )
        return TRUE;

    return FALSE;
}

void msAPI_DTV_DB_PrintServiceName(U8* pu8Name, U16 u16MaxLen)
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
            printf("(%X)", u8Char);
        }
    }
    putchar(']');
}

void msAPI_DTV_DB_PrintServiceType(U8 u8ServiceType)
{
    char* pcServiceType = "Unknown Service";

    switch(u8ServiceType)
    {
        case E_SERVICETYPE_ATV:
            pcServiceType = "ATV";
            break;
        case E_SERVICETYPE_DTV:
            pcServiceType = "DTV";
            break;
        case E_SERVICETYPE_RADIO:
            pcServiceType = "RADIO";
            break;
        case E_SERVICETYPE_DATA:
            pcServiceType = "DATA";
            break;

        //case E_SERVICETYPE_UNITED_TV:
          //  pcServiceType = "UNITED";
            //break;

        default:
            break;
    }

    printf(" %s ", pcServiceType);
}

void msAPI_DTV_DB_Dump_Prog_ByService(TypDtvDbSel eDtvDbSel, MEMBER_SERVICETYPE bServiceType )
{
    U8 u8ServiceIdx = ConvertServiceTypeToPosition(bServiceType);
    U16 u16PosIndex;
    U16 u16ProgCount;
    U16 u16Order;
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    DTVPROGRAMINDEX* pstProgIndex;
    U8 au8ServiceName[MAX_SERVICE_NAME];



    u16ProgCount = msAPI_DtvDB_Get_ProgramCount(eDtvDbSel, u8ServiceIdx, E_PROGACESS_INCLUDE_ALL);
    printf("\n========== u8ServiceIdx=%u, u16ProgCount=%u ==========\n", u8ServiceIdx, u16ProgCount);

    for( u16PosIndex = 0; u16PosIndex < u16ProgCount; u16PosIndex += 1 )
    {
        u16Order = ConvertPositionToOrder_DBSel(eDtvDbSel, bServiceType, u16PosIndex);

        pstProgIndex = &(pstProgramIndexTable[u16Order]);
        printf("Pos %u: Order=%u, LCN=%u,", u16PosIndex, u16Order, pstProgIndex->wLCN);

        printf(" IDIdx=%u: PRIdx=%u, ", pstProgIndex->cIDIndex, pstProgIndex->wPRIndex);

        // Use CM api get service name
        if( msAPI_CM_GetServiceName(bServiceType, u16PosIndex, au8ServiceName) )
        {
            msAPI_DTV_DB_PrintServiceName( au8ServiceName, MAX_SERVICE_NAME );
        }

        if( pstProgIndex->bIsFavorite )
            printf(" Fav=%u, ", pstProgIndex->bIsFavorite);

        if( !(pstProgIndex->bVisibleServiceFlag) )
            printf(" Vis=%u, ", pstProgIndex->bVisibleServiceFlag);

        if( pstProgIndex->bIsDelete )
            printf(" Del=%u, ", pstProgIndex->bIsDelete);

        printf("\n");
    }
}

void msAPI_DTV_DB_DumpDB(TypDtvDbSel eDtvDbSel, U32 u32Flag)
{
    U16 i, j;
    U8 u8Tmp;
    U16 u16IDIdx;
    U16 u16ProgIndex;
    U16 u16PrintCount = 0;
    U16 u16PrintCount_Max = 30;
    U8 au8ServiceName[MAX_SERVICE_NAME];


    PRINT_CURRENT_LINE();
    printf("msAPI_DTV_DB_DumpDB(eDtvDbSel=%u, u32Flag=0x%X)\n", eDtvDbSel, u32Flag);


#if 1//(ENABLE_API_DTV_SYSTEM_2015)
    //pDtvChDB = (DTV_CHANNEL_DATA_STRUCTURE*)MsOS_PA2KSEG1(RAM_DISK_MEM_ADDR+RM_DTV_CHSET_START_ADDR);

    // Program Index Table
    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);
    U16 u16ProgramIndexArraySize = msAPI_DtvDB_Get_ProgramIndexTableArraySize(eDtvDbSel);

    // Prog table Map
    U8* pu8ProgramTableMap = msAPI_DtvDB_Get_ProgTableMap(eDtvDbSel);
    U16 u16ProgramTableMapArraySize = msAPI_DtvDB_Get_ProgTableMapArraySize(eDtvDbSel);

    // Prog table
    DTV_CHANNEL_INFO* pstProgTable = (DTV_CHANNEL_INFO*)MsOS_PA2KSEG1(RAM_DISK_MEM_ADDR+msAPI_DtvDB_Get_ProgTableRamDiskAddr(eDtvDbSel));
    U16 u16ProgTableArraySize = msAPI_DtvDB_Get_ProgTableArraySize(eDtvDbSel);
    printf("RAM_DISK_MEM_ADDR=0x%X\n", RAM_DISK_MEM_ADDR);
    printf("msAPI_DtvDB_Get_ProgTableRamDiskAddr(eDtvDbSel)=0x%X\n", msAPI_DtvDB_Get_ProgTableRamDiskAddr(eDtvDbSel));
    printf("pstProgTable=0x%X\n", (U32)pstProgTable);
//    printf("RAM_DISK_MEM_ADDR=0x%X\n", RAM_DISK_MEM_ADDR);

    // ID table map
    U8* pu8IDTableMap = msAPI_DtvDB_Get_ProgIdTableMap(eDtvDbSel);
    U16 u16IDTableMapArraySize = msAPI_DtvDB_Get_ProgIdTableMapArraySize(eDtvDbSel);

    // ID table
    DTVPROGRAMID_M* pstIDTable = msAPI_DtvDB_Get_ProgIdTable(eDtvDbSel);
    U16 u16IDTableArraySize = msAPI_DtvDB_Get_ProgIdTableArraySize(eDtvDbSel);;

#else
    DTV_CHANNEL_DATA_STRUCTURE* pDtvChDB = NULL;
    pDtvChDB = (DTV_CHANNEL_DATA_STRUCTURE*)MsOS_PA2KSEG1(RAM_DISK_MEM_ADDR+RM_DTV_CHSET_START_ADDR);

    DTVPROGRAMINDEX* pstProgramIndexTable = msAPI_DtvDB_Get_ProgramIndexTable(eDtvDbSel);//m_astDTVProgramIndexTable;
    U16 u16ProgramIndexArraySize = MAX_DTVPROGRAM;

    // Prog table Map
    //U8* pu8ProgramTableMap = pDtvChDB->bDTVChannelTableMap;
    U8* pu8ProgramTableMap = m_acDTVProgramTableMap;
    U16 u16ProgramTableMapArraySize = MAX_DTVCHANNELTABLE_MAP;

    // Prog table
    DTV_CHANNEL_INFO* pstProgTable = pDtvChDB->astDTVChannelTable;
    U16 u16ProgTableArraySize = MAX_DTVPROGRAM;

    // ID table map
    //U8* pu8IDTableMap = pDtvChDB->bDTVIDtableMap;
    U8* pu8IDTableMap = m_acDTVIDtableMap;
    U16 u16IDTableMapArraySize = MAX_DTVIDTABLE_MAP;

    // ID table
    //DTVPROGRAMID_M* pstIDTable = pDtvChDB->astDtvIDTable;
    DTVPROGRAMID_M* pstIDTable = _astDTVProgramIDTable;
    U16 u16IDTableArraySize = MAX_MUX_NUMBER;
#endif

    //static DTVNETWORK _astDTVNetwork[MAX_NETWOEK_NUMBER];


    printf("\nDTV DataBase:\n");

    printf(" sizeof(DTVPROGRAMINDEX)=0x%X\n", sizeof(DTVPROGRAMINDEX));

    printf(" pstProgramIndexTable=0x%X\n", (U32)pstProgramIndexTable);
    //printf(" offset wService_ID=0x%X\n", (U32)&(pstProgramIndexTable->wService_ID));
    //printf(" offset wLCN=0x%X\n", (U32)&(pstProgramIndexTable->wLCN));
    //printf(" offset wSimu_LCN=0x%X\n", (U32)&(pstProgramIndexTable->wSimu_LCN));


    printf(" RAM_DISK_MEM_ADDR=0x%X\n", RAM_DISK_MEM_ADDR);
    printf(" RM_DTV_CHSET_START_ADDR=0x%X\n", RM_DTV_CHSET_START_ADDR);

    //printf(" pDtvChDB=0x%X\n", (U32)pDtvChDB);
    //printf(" wID=0x%X\n", pDtvChDB->wID);
    //printf(" bSerialNum=0x%X\n", pDtvChDB->bSerialNum);
    //printf(" bIsLogicalChannelNumberArranged=%u\n", pDtvChDB->bIsLogicalChannelNumberArranged);
#if NTV_FUNCTION_ENABLE
    //printf(" bFavorite_Region=0x%X\n", pDtvChDB->bFavorite_Region);
#endif

    // Because alignment issue, can not use pDtvChDB->eCountry directly!
    printf(" stTvSetting.eCountry=%u\n", stGenSetting.stTvSetting.eCountry );
    printf(" u16DTVRFChannelOrder=%u\n", stGenSetting.stTvSetting.u16DTVRFChannelOrder );
    printf(" u16DATARFChannelOrder=%u\n", stGenSetting.stTvSetting.u16DATARFChannelOrder );
    printf(" u16RADIORFChannelOrder=%u\n", stGenSetting.stTvSetting.u16RADIORFChannelOrder );
    printf(" eCurrentServiceType=%u\n", stGenSetting.stTvSetting.eCurrentServiceType );


    //printf(" m_eCountry=%u\n", m_eCountry);

    printf(" MAX_DTVPROGRAM=%u\n", MAX_DTVPROGRAM);
    printf(" MAX_DTVCHANNELTABLE_MAP=%u\n", MAX_DTVCHANNELTABLE_MAP);

    printf(" MAX_MUX_NUMBER=%u\n", MAX_MUX_NUMBER);
    printf(" MAX_DTVIDTABLE_MAP=%u\n", MAX_DTVIDTABLE_MAP);

    printf(" MAX_NETWOEK_NUMBER=%u\n", MAX_NETWOEK_NUMBER);


    // Print program index
    {
        DTVPROGRAMINDEX* pstProgIndex;
        DTVPROGRAMID_M* pstID;

        u16PrintCount = 0;
        u16PrintCount_Max = 100;

        printf("pstProgramIndexTable[]={\n");
        for( i = 0; i < u16ProgramIndexArraySize; ++ i )
        {
            pstProgIndex = &(pstProgramIndexTable[i]);
            u16ProgIndex = pstProgIndex->wPRIndex;
            if( INVALID_PRINDEX != u16ProgIndex )
            {
                printf("[%u]PRIdx=%u,", i, u16ProgIndex);

                msAPI_DTV_DB_PrintServiceType(pstProgIndex->bServiceType);

                printf(" wLCN=%u,", pstProgIndex->wLCN);

                u16IDIdx = pstProgIndex->cIDIndex;
                pstID = &(pstIDTable[u16IDIdx]);

                printf(" ID=%u,", u16IDIdx);

                printf(" RF=%u, Freq=%u ", pstID->cRFChannelNumber, pstID->u32Frequency);

                // Use CM api get service name
                if( GetProgramTable(u16ProgIndex, (BYTE *)au8ServiceName, E_DATA_SERVICE_NAME) )
                {
                    msAPI_DTV_DB_PrintServiceName( au8ServiceName, MAX_SERVICE_NAME );
                }

                if( !(pstProgIndex->bVisibleServiceFlag) )
                {
                    printf(" Vis=%u,", pstProgIndex->bVisibleServiceFlag);
                }

                if( pstProgIndex->bIsDelete )
                {
                    printf(" Del=%u,", pstProgIndex->bIsDelete);
                }

                if( pstProgIndex->bIsSkipped )
                {
                    printf(" Skip=%u,", pstProgIndex->bIsSkipped);
                }

                printf("\n");
                u16PrintCount += 1;
            }

            if( u16PrintCount >= u16PrintCount_Max )
                break;
        }
        printf("} ------------------------- \n");
    }

    // Print program table Map
    if( u32Flag&CM_DUMP_INFO_CH_TBL_MAP )
    {
        U16 u16TotalProgMap = 0;

        printf("Program Table Map[]={\n");
        for( i = 0; i < u16ProgramTableMapArraySize; ++ i )
        {
            u8Tmp = pu8ProgramTableMap[i];
            if( u8Tmp )
            {
                printf(" [%u]=0x%X:", i, u8Tmp);
                for( j = 0; j < 8; ++j )
                {
                    if( u8Tmp & (1<<j) )
                    {
                        printf(" %u,", i*8+j);
                        u16TotalProgMap += 1;
                    }
                }
                printf("\n");
            }
        }
        printf("} Total = %u ---------------- \n", u16TotalProgMap);
    }

    // Print program table
    if( u32Flag&CM_DUMP_INFO_CH_TBL )
    {
        DTV_CHANNEL_INFO* pstChInfo;
        U16 u16TotalProg = 0;

        printf("Program Table[]={\n");
        for( u16ProgIndex = 0; u16ProgIndex < u16ProgTableArraySize; ++ u16ProgIndex )
        {
            if( msAPI_DTV_DB_Is_ProgramActive(u16ProgIndex, pu8ProgramTableMap) )
            {
                pstChInfo = &(pstProgTable[u16ProgIndex]);
                printf("Prog %u:\n", u16ProgIndex);
                printf(" IdTblIdx = %u,", pstChInfo->bIDIdex);
                printf(" wOrder = %u,", pstChInfo->wOrder);
                printf(" wService_ID = %u,", pstChInfo->wService_ID);

                printf(" wLCN = %u,", pstChInfo->wLCN);
                printf(" wTS_LCN = %u,", pstChInfo->wTS_LCN);
                printf(" wSimu_LCN = %u\n", pstChInfo->wSimu_LCN);

                printf(" Name=", pstChInfo->wSimu_LCN);
                msAPI_DTV_DB_PrintServiceName( pstChInfo->bChannelName, MAX_SERVICE_NAME );
                printf("\n");

                u16TotalProg += 1;
            }
        }
        printf("} Total = %u ---------------- \n", u16TotalProg);
    }


    // Print ID Table
    if( u32Flag&CM_DUMP_INFO_ID_TBL_MAP )
    {
        U16 u16TotalIDMap = 0;

        printf("ID Table Map[]={\n");
        for( i = 0; i < u16IDTableMapArraySize; ++ i )
        {
            u8Tmp = pu8ProgramTableMap[i];
            if( u8Tmp )
            {
                printf(" [%u]=0x%X:", i, u8Tmp);
                for( j = 0; j < 8; ++j )
                {
                    if( u8Tmp & (1<<j) )
                    {
                        printf(" %u,", i*8+j);
                        u16TotalIDMap += 1;
                    }
                }
                printf("\n");
            }
        }
        printf("} Total = %u ---------------- \n", u16TotalIDMap);
    }


    // Print ID table Map
    if( u32Flag&CM_DUMP_INFO_ID_TBL )
    {
        DTVPROGRAMID_M* pstID;
        U16 u16TotalID = 0;

        printf("ID Table[]={\n");
        for( u16IDIdx = 0; u16IDIdx < u16IDTableArraySize; ++ u16IDIdx )
        {
            if( msAPI_DTV_DB_Is_IDTabActive(u16IDIdx, pu8IDTableMap) )
            {
                pstID = &(pstIDTable[u16IDIdx]);
                printf("ID %u:\n", u16IDIdx);

                printf(" cRFChannelNumber = %u\n", pstID->cRFChannelNumber);

                printf(" u32Freq = %u,", pstID->u32Frequency);
                printf(" u32SymbRate = %u,", pstID->u32SymbRate);
                printf(" Qam = %u\n", pstID->QamMode);

                printf(" enBandWidth = %u,", pstID->enBandWidth);
                printf(" cHpLp = %u,", pstID->cHpLp);
                printf("\n");
                u16TotalID += 1;
            }
        }
        printf("} Total = %u ---------------- \n", u16TotalID);
    }


    // Dump program count
    //static WORD m_awProgramCount[3][MAX_COUNT_PROGRAM_OPTION];
    {
        printf("\nProgramCount[][]:\n");
        for( i = 0; i < E_CM_SERVICE_POS_NUMS; ++ i )
        {
            for( j = 0; j < MAX_COUNT_PROGRAM_OPTION; ++j )
            {
            #if 1//(ENABLE_API_DTV_SYSTEM_2015)
                printf(" [%u][%u]=%u\n", i, j, msAPI_DtvDB_Get_ProgramCount(eDtvDbSel,i,j) );
            #else
                printf(" [%u][%u]=%u\n", i, j, m_awProgramCount[i][j]);
            #endif

            }
        }
        printf(" -------------- \n");
    }

    // Dump all program by service
    {
        msAPI_DTV_DB_Dump_Prog_ByService(eDtvDbSel, E_SERVICETYPE_DTV);
        msAPI_DTV_DB_Dump_Prog_ByService(eDtvDbSel, E_SERVICETYPE_RADIO);
        msAPI_DTV_DB_Dump_Prog_ByService(eDtvDbSel, E_SERVICETYPE_DATA);
    }

}


#endif

