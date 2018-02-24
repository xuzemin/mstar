////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __API_DTVSATTABLE_C__
#define __API_DTVSATTABLE_C__


#include "Board.h"

#if (ENABLE_S2)
#include "apiDTVSatTable.h"
#include "MApp_SaveData.h"
#include "msAPI_DTVSystem.h"

#include "apiXC_Sys.h"
#include "apiXC_Cus.h"


#include <stddef.h>
#include <string.h>
#include "sysinfo.h"
#include "debug.h"
#include "msAPI_Ram.h"
#include "msAPI_MIU.h"
#include "MApp_DataBase_CH.h"
#include "msAPI_Flash.h"

#define BASEADDRESS_SAT_DATA                         RM_START_ADDRESS_OF_SAT_DATA_STRUCTURE ///TODO:: move to the position in front of channel database
#define BASEADDRESS_SAT_TABLEMAP                     ( BASEADDRESS_SAT_DATA + (offsetof(SAT_DATA_STRUCTURE, acSATTableMap)) )
#define BASEADDRESS_SAT_TABLE                        ( BASEADDRESS_SAT_DATA + (offsetof(SAT_DATA_STRUCTURE, astSATTable)) )
#define END_ADDRESS_OF_SAT_DATA_STRUCTURE            (BASEADDRESS_SAT_DATA + (sizeof(SAT_DATA_STRUCTURE)))

static BYTE m_acSATTableMap[MAX_SATTABLEMAP] = {0};
static BYTE m_selSatTableMap[MAX_SATTABLEMAP];
static BYTE _bCurrentSATPosition=0;
static BOOLEAN SetNVRAM_S2(DWORD wAddress, BYTE * pcBuffer, BYTE cSize)
{
    U32 u32DramAddr = wAddress + RAM_DISK_MEM_ADDR;

    if(wAddress>=BASEADDRESS_SAT_DATA && wAddress<END_ADDRESS_OF_SAT_DATA_STRUCTURE)
    {
    #if 1
        memcpy( (void *)_PA2VA(u32DramAddr),pcBuffer,cSize);
    #else

    #if (ENABLE_S2_8M_FLASH)
      #if(ENABLE_COMPRESS_DATA)
        memcpy( (void *)_PA2VA(wAddress-RM_GEN_USAGE+DRAM_640K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)))),pcBuffer,cSize);
      #else
        memcpy( (void *)_PA2VA(wAddress-RM_GEN_USAGE+DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)))),pcBuffer,cSize);
      #endif
    #else
        memcpy( (void *)_PA2VA(wAddress-RM_GEN_USAGE+DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)))),pcBuffer,cSize);
    #endif
    #endif
        //g_u8QuickDataBase |= QUICK_DB_UPDATE;
        MApp_DB_CH_Set_DataChanged(TRUE);
    }
    else
    {
        __ASSERT(0);
    }
    return TRUE;
}

static BOOLEAN GetNVRAM_S2(DWORD wAddress, BYTE * pcBuffer, BYTE cSize)
{
    U32 u32DramAddr = wAddress + RAM_DISK_MEM_ADDR;

    if(wAddress>=BASEADDRESS_SAT_DATA && wAddress<END_ADDRESS_OF_SAT_DATA_STRUCTURE)
    {
#if 1
        memcpy(pcBuffer,(void *)_PA2VA(u32DramAddr),cSize);
#else
    #if (ENABLE_S2_8M_FLASH)
    #if(ENABLE_COMPRESS_DATA)
        memcpy(pcBuffer,(void *)_PA2VA(wAddress-RM_GEN_USAGE+DRAM_640K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)))),cSize);
    #else
        memcpy(pcBuffer,(void *)_PA2VA(wAddress-RM_GEN_USAGE+DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)))),cSize);
    #endif
    #else
        memcpy(pcBuffer,(void *)_PA2VA(wAddress-RM_GEN_USAGE+DRAM_64K_DB_START(((DATABASE_START_MEMORY_TYPE & MIU1) ? (DATABASE_START_ADR | MIU_INTERVAL) : (DATABASE_START_ADR)))),cSize);
    #endif
#endif
    }
    else
    {
        MS_DEBUG_MSG(printf("\n DTV GetNVRAM  >> something wrong...."));
    }
    return TRUE;
}

static MS_BOOL IsSATEntityActive(BYTE bSATIndex)
{
    if (MAX_NUM_OF_SAT <= bSATIndex)
    {
        return FALSE;
    }
    return ((m_acSATTableMap[bSATIndex/8] & (0x01 << (bSATIndex % 8))) ? TRUE : FALSE);
}

static WORD GetSATCount(void)
{
    BYTE bSATIndex;
    BYTE bSATCount = 0;

    for (bSATIndex = 0; bSATIndex < MAX_NUM_OF_SAT; bSATIndex++)
    {
        if (TRUE == IsSATEntityActive(bSATIndex))
        {
            bSATCount++;
        }
    }

    if (MAX_NUM_OF_SAT <= bSATCount)
    {
        return MAX_NUM_OF_SAT;
    }

    return bSATCount;
}

static BOOLEAN ActiveSATEntity(BYTE bSATIndex, MS_BOOL bActive)
{
    BYTE cTemp;
    if (MAX_NUM_OF_SAT <= bSATIndex)
    {
        return FALSE;
    }

    cTemp = bSATIndex / 8;
    if (TRUE == bActive)
    {
        m_acSATTableMap[cTemp] =  m_acSATTableMap[cTemp] | (0x01 << (bSATIndex % 8));
    }
    else
    {
        m_acSATTableMap[cTemp] =  m_acSATTableMap[cTemp] & ~(0x01 << (bSATIndex % 8));
    }
    return SetNVRAM_S2(BASEADDRESS_SAT_TABLEMAP + cTemp, &(m_acSATTableMap[cTemp]), sizeof(BYTE));
}

static BYTE GetEmptyIndexOfSATTable(void)
{
    BYTE bSATIndex;

    for (bSATIndex = 0; bSATIndex < MAX_NUM_OF_SAT; bSATIndex++)
    {
        if (FALSE == IsSATEntityActive(bSATIndex))
        {
            return bSATIndex;
        }
    }

    return INVALID_SATINDEX;
}
static BOOLEAN SetSATTable(BYTE bSATIndex, BYTE * pcBuffer, eSATDATA_MEMBER eMember)
{
    if (MAX_NUM_OF_SAT <= bSATIndex)
    {
        return FALSE;
    }

    if (eMember != pftSATALL && FALSE == IsSATEntityActive(bSATIndex))
    {
        return FALSE;
    }

    switch (eMember)
    {
        case pftSATALL:
            return SetNVRAM_S2(BASEADDRESS_SAT_TABLE +(bSATIndex*sizeof(MS_SAT_PARAM)),pcBuffer, sizeof(MS_SAT_PARAM));
        default:
            break;
    }

    return FALSE;
}

//-------------------------------------------------------------------------------------------------
/// Add a physical channel into physical channel database
/// @param pcPhyChIdx \b OUT: the pointer of physical channel index
/// @param pCarrierParam \b IN: pointer of carrier parameter
//-------------------------------------------------------------------------------------------------
BOOLEAN MApi_DB_SAT_AddSAT(BYTE *pbSATIdx, MS_SAT_PARAM *pSATParam)
{
    BYTE bSATIndex;

    bSATIndex = GetEmptyIndexOfSATTable();
    if (MAX_NUM_OF_SAT <= bSATIndex || INVALID_SATINDEX == bSATIndex)
    {
        return FALSE;
    }

    if (TRUE!= SetSATTable(bSATIndex, (BYTE *)pSATParam, pftSATALL))
    {
        return FALSE;
    }

    ActiveSATEntity(bSATIndex, TRUE);

    *pbSATIdx = bSATIndex;

    return TRUE;
}

BYTE MApi_DB_SAT_GetSatIDByIndexOfActiveSats(BYTE bIndexofactivesats)
{
    BYTE i;
    BYTE bPos = 0;
    for(i=0;i<MAX_NUM_OF_SAT;i++)
    {
        if(IsSATEntityActive(i))
        {
            bPos ++;

            if(bPos == bIndexofactivesats + 1)
            {
                return i;
            }
        }
    }
    return INVALID_SATINDEX;
}

static BOOLEAN GetSATTable(BYTE bSATIndex, BYTE * pcBuffer, eSATDATA_MEMBER eMember)
{
    if (MAX_NUM_OF_SAT <= bSATIndex)
    {
        return FALSE;
    }

    if (IsSATEntityActive(bSATIndex) == FALSE)
    {
        return FALSE;
    }
    switch (eMember)
    {
    case pftSATALL:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM)),
                        pcBuffer, sizeof(MS_SAT_PARAM));
    case pftSATNAME:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, aSatName)),
                        pcBuffer, MAX_SATNAME_LEN+1);

    case pftLOLOF:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, u16LoLOF)),
                        pcBuffer, sizeof(MS_U16));
    case pftHILOF:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, u16HiLOF)),
                        pcBuffer, sizeof(MS_U16));
    case pftLNBTYPE:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, eLNBType)),
                        pcBuffer, sizeof(MS_EN_LNBTYPE));

    case pftDISEQCLEVEL:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, eDiseqcLevel)),
                        pcBuffer, sizeof(MS_EN_DISEQC_LEVEL));
    case pftSWT10PORT:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, eSwt10Port)),
                        pcBuffer, sizeof(MS_EN_SWT_PORT));
    case pftSWT11PORT:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, eSwt11Port)),
                        pcBuffer, sizeof(MS_EN_SWT_PORT));
    case pft22KONOFF:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, e22KOnOff)),
                        pcBuffer, sizeof(MS_EN_22K_ONOFF));
    case pftLNBPWRONOFF:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, eLNBPwrOnOff)),
                        pcBuffer, sizeof(MS_EN_LNBPWR_ONOFF));
    case pft0V12VONOFF:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, e0V12VOnOff)),
                        pcBuffer, sizeof(MS_EN_0V12V_ONOFF));
    case pftPOSITION:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, u8Position)),
                        pcBuffer, sizeof(MS_U8));
    case pftANGLE:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, u16Angle)),
                        pcBuffer, sizeof(MS_U16));
    case pftPORTYPE:
        return GetNVRAM_S2(BASEADDRESS_SAT_TABLE +
                        (bSATIndex*sizeof(MS_SAT_PARAM) + offsetof(MS_SAT_PARAM, bPorInvert)),
                        pcBuffer, sizeof(MS_U16));
    default:
        break;
    }

    return FALSE;
}

BOOLEAN MApi_DB_SAT_GetSATParam(BYTE bSATIdx, MS_SAT_PARAM *pSATParam)
{
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)pSATParam, pftSATALL))
    {
        return FALSE;
    }
    else
    {
        return  TRUE;
    }
}

static void  UnSelectAllSat(void)
{
     BYTE i;

     for (i = 0; i < (MAX_SATTABLEMAP); i++)
     {
        m_selSatTableMap[i] = 0x00;
     }
}

BOOLEAN MApi_DB_SAT_InitSATTable(void)
{
    GetNVRAM_S2(BASEADDRESS_SAT_TABLEMAP, (BYTE *)m_acSATTableMap, sizeof(m_acSATTableMap));
    UnSelectAllSat();

#if 0
    {
        U8 i;
        for (i = 0; i < (MAX_SATTABLEMAP); i++)
        {
            printf(" m_acSATTableMap[%u]=%2bx\n", i, m_acSATTableMap[i]);
        }
    }
#endif

    return  TRUE;
}

BYTE MApi_DB_SAT_GetSATCount(void)
{
    BYTE u8ChnCnt = 0;

    u8ChnCnt = GetSATCount();
    return u8ChnCnt;
}
static MS_BOOL IsSatEntirySelect(BYTE ucSatID)
{
    if (MAX_NUM_OF_SAT <= ucSatID)
    {
        return FALSE;
    }
    return ((m_selSatTableMap[ucSatID/8] & (0x01 << (ucSatID % 8))) ? TRUE : FALSE);
}

MS_BOOL MApi_SAT_IsSatEntirySelect(BYTE ucSatID)
{
    MS_BOOL bRet;
    bRet = IsSatEntirySelect(ucSatID);
    return bRet;
}

BOOLEAN MApi_SAT_SelectSATEntity(BYTE ucSatID, MS_BOOL bSelected)
{
    BYTE cTemp;

    if (MAX_NUM_OF_SAT <= ucSatID)
    {
        return FALSE;
    }

    cTemp = ucSatID / 8;
    if (TRUE == bSelected)
    {
        m_selSatTableMap[cTemp] =  m_selSatTableMap[cTemp] | (0x01 << (ucSatID % 8));
    }
    else
    {
        m_selSatTableMap[cTemp] =  m_selSatTableMap[cTemp] & ~(0x01 << (ucSatID % 8));
    }

    return TRUE;
}

BOOLEAN MApi_SAT_UnSelectAllSAT(void)
{
    UnSelectAllSat();
    return TRUE;
}

BYTE  MApi_SAT_SelectedSatNum(void)
{
     BYTE i;
     BYTE num = 0;

     for (i = 0; i < (MAX_NUM_OF_SAT); i++)
     {
         if(IsSatEntirySelect(i))
         {
                num ++;
         }
     }
     return num;
}
BOOLEAN MApi_DB_SAT_SetCurrentSATPosition(BYTE bPosition)
{
    _bCurrentSATPosition = bPosition;
    return TRUE;
}
BYTE MApi_DB_SAT_GetCurrentSATPosition(void)
{
    BYTE bPos;
    bPos = _bCurrentSATPosition;
    return bPos;
}
BOOLEAN MApi_DB_SAT_UpdateSAT(BYTE bSATIdx, MS_SAT_PARAM *pSATParam)
{
    if (TRUE != SetSATTable(bSATIdx, (BYTE *)pSATParam, pftSATALL))
    {
        return FALSE;
    }

    return TRUE;
}
BOOLEAN MApi_DB_SAT_DeleteSAT(BYTE bSATIdx)
{
    if (MAX_NUM_OF_SAT <= bSATIdx || INVALID_SATINDEX == bSATIdx)
    {
        return FALSE;
    }
    ActiveSATEntity(bSATIdx, FALSE);

    return TRUE;
}

BOOLEAN MApi_DB_SAT_DeleteAllSAT(void)
{
    BYTE bSATIdx;
    for (bSATIdx = 0; bSATIdx < MAX_NUM_OF_SAT; bSATIdx++)
    {
        ActiveSATEntity(bSATIdx, FALSE);
    }
    return TRUE;
}

BOOLEAN MApi_DB_SAT_GetSATName(BYTE bSATIdx,BYTE *pcSATName)
{
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)pcSATName, pftSATNAME))
    {
        return FALSE;
    }

    return TRUE;
}

WORD MApi_DB_SAT_GetLoLOF(BYTE bSATIdx)
{
    WORD wLoLOF = 0;
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&wLoLOF, pftLOLOF))
    {
        return INVALID_LOF;
    }
    return wLoLOF;
}
WORD MApi_DB_SAT_GetHiLOF(BYTE bSATIdx)
{
    WORD wHiLOF = 0;
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&wHiLOF, pftHILOF))
        return INVALID_LOF;

    return wHiLOF;
}
MS_EN_LNBTYPE MApi_DB_SAT_GetLNBType(BYTE bSATIdx)
{
    MS_EN_LNBTYPE eLNBType;
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&eLNBType, pftLNBTYPE))
        return (MS_EN_LNBTYPE)INVALID_LNBTYPE;

    return eLNBType;
}
MS_EN_DISEQC_LEVEL MApi_DB_SAT_GetDisqecLevel(BYTE bSATIdx)
{
    MS_EN_DISEQC_LEVEL eDiseqcLevel ;
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&eDiseqcLevel, pftDISEQCLEVEL))
        return (MS_EN_DISEQC_LEVEL)INVALID_DISEQCLEVEL;

    return eDiseqcLevel;
}
MS_EN_SWT_PORT MApi_DB_SAT_GetSWT10Port(BYTE bSATIdx)
{
    MS_EN_SWT_PORT eSWTPort;

    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&eSWTPort, pftSWT10PORT))
        return (MS_EN_SWT_PORT)INVALID_SWTPORT;

    return eSWTPort;
}
MS_EN_SWT_PORT MApi_DB_SAT_GetSWT11Port(BYTE bSATIdx)
{
    MS_EN_SWT_PORT eSWTPort;

    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&eSWTPort, pftSWT11PORT))
        return (MS_EN_SWT_PORT)INVALID_SWTPORT;

    return eSWTPort;
}
MS_EN_22K_ONOFF MApi_DB_SAT_Get22KOnOff(BYTE bSATIdx)
{
    MS_EN_22K_ONOFF e22KOnOff;
    if (TRUE != GetSATTable(bSATIdx, (BYTE *)&e22KOnOff, pft22KONOFF))
        return (MS_EN_22K_ONOFF)INVALID_22KONOFF;

    return e22KOnOff;
}
MS_EN_LNBPWR_ONOFF MApi_DB_SAT_GetLNBPWROnOff(BYTE bSATIdx)
{
    MS_EN_LNBPWR_ONOFF eLNBPwrOnOff;

    if (TRUE!= GetSATTable(bSATIdx, (BYTE *)&eLNBPwrOnOff, pftLNBPWRONOFF))
        eLNBPwrOnOff=(MS_EN_LNBPWR_ONOFF)INVALID_LNBPWRONOFF;

    return eLNBPwrOnOff;
}
MS_EN_0V12V_ONOFF MApi_DB_SAT_Get0V12VOnOff(BYTE bSATIdx)
{
    MS_EN_0V12V_ONOFF e0V12VOnOff;

    if (TRUE!= GetSATTable(bSATIdx, (BYTE *)&e0V12VOnOff, pft0V12VONOFF))
        e0V12VOnOff=(MS_EN_0V12V_ONOFF)INVALID_0V12VONOFF;

    return e0V12VOnOff;
}

BYTE MApi_DB_SAT_GetSATMotorPositionBySatID(BYTE bSatID)
{
    BYTE bPosition = 0;

    if (TRUE!= GetSATTable(bSatID, (BYTE *)&bPosition, pftPOSITION))
        bPosition=INVALID_SAT_POSITION;
    return bPosition;
}

WORD MApi_DB_SAT_GetSATAngleBySatID(BYTE bSatID)
{
    WORD wAngle = 0;

    if (TRUE!= GetSATTable(bSatID, (BYTE *)&wAngle, pftANGLE))
        wAngle= INVALID_SATANGLE;

    return wAngle;
}

MS_U8 MApi_DB_GetSatIdByAngle(MS_U16 u16Angle)
{
    BYTE ucSatID;
    MS_U16 u16TmpAngle = 0;

    for(ucSatID=0;ucSatID<MAX_NUM_OF_SAT;ucSatID++)
    {
        if (TRUE!= GetSATTable(ucSatID, (BYTE *)&u16TmpAngle, pftANGLE))
        {
            return INVALID_SATINDEX;
        }

        if(u16TmpAngle == u16Angle)
        {
            return ucSatID;
        }
    }
    return INVALID_SATINDEX;
}

BYTE MApi_DB_SAT_GetActiveSatIndexBySatID(BYTE bSatID)
{
    BYTE i;
    BYTE cIndx = 0;

    for(i=0;i<MAX_NUM_OF_SAT;i++)
    {
        if(i == bSatID)
        {
            if(IsSATEntityActive(i))
            {
                return cIndx;
            }
            else
            {
                return INVALID_SATINDEX;
            }
        }
        if(IsSATEntityActive(i))
        {
            cIndx ++;
        }
    }
    return INVALID_SATINDEX;
}


BOOLEAN MApi_DB_SAT_ResetAllSATTable(void)
{
    WORD i;

    for (i = 0; i < (MAX_SATTABLEMAP); i++)
    {
        m_acSATTableMap[i] = 0x00;
    }
    UnSelectAllSat();

    SetNVRAM_S2(BASEADDRESS_SAT_TABLEMAP, m_acSATTableMap, sizeof(m_acSATTableMap));

    return TRUE;
}

BOOLEAN MApi_DB_SAT_insertSAT(U8 u8CurrentSATId, BYTE *stNextSatParam)
{
    BYTE i;
    BYTE u8SatCnt;
    MS_SAT_PARAM stSATParam;

    u8SatCnt = GetSATCount();
    for(i = u8SatCnt-1;i > u8CurrentSATId;i--)
    {
        GetSATTable(i, (BYTE *)&stSATParam, pftSATALL);
        SetSATTable(i+1,  (BYTE *)&stSATParam, pftSATALL);
    }
    SetSATTable(u8CurrentSATId, stNextSatParam, pftSATALL);

    return TRUE;
}

#if(ENABLE_S2_DATABASE_DBM)
BOOLEAN MApi_DB_SAT_DeleteAllTps(void)
{
    WORD wTPIdx;
    for (wTPIdx = 0; wTPIdx < MAX_DTV_S2_MUX_NUMBER; wTPIdx++)
    {
        //ActiveIDEntity(wTPIdx, FALSE);
        ActiveIDEntity_DBSel(E_DTV_DB_SEL_DVBS, wTPIdx, FALSE);
    }
    return TRUE;
}

BOOLEAN MApi_DB_SAT_GetTpByIndex(MS_U16 wTPIdx, Antenna_TPInfo *TpInfo)
{
    DTVPROGRAMID_M stDTVProgramID;
    if(GetIDTable(wTPIdx, (BYTE *)&stDTVProgramID, E_DATA_ID_TABLE))
    {
        TpInfo->eSatellite = (TYPE_SATELLITE)stDTVProgramID.SatelliteId;
        TpInfo->u32Frequency = stDTVProgramID.u32S2Frequency;
        TpInfo->u16SymbolRate = stDTVProgramID.u16SymbolRate;
        TpInfo->u8Polarity = stDTVProgramID.u8Polarity;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

MS_U16 MApi_DB_SAT_GetTotalTpNum(void)
{
    WORD i, wTotal=0;

    for (i = 0; i < MAX_DTV_S2_MUX_NUMBER; i++)
    {
        if(MApi_DB_SAT_GetTpActive(i))
        wTotal++;
    }
    return wTotal;
}

BOOLEAN AddTransponder(MS_U8 SatId, MS_U16 TpId, Antenna_TPInfo TpInfo)
{
    DTVPROGRAMID_M stDTVProgramID;

    stDTVProgramID.wTransportStream_ID = INVALID_TS_ID;
    stDTVProgramID.wOriginalNetwork_ID = INVALID_ON_ID;
    stDTVProgramID.cNetWorkIndex = INVALID_NETWORKINDEX;
    stDTVProgramID.cRFChannelNumber = INVALID_PHYSICAL_CHANNEL_NUMBER;
    stDTVProgramID.cPLPID = INVALID_PLPID;
#if ENABLE_TARGET_REGION
    stDTVProgramID.cRegion= DEFAULT_REGION;
#endif
#if (ENABLE_UPDATE_MULTIPLEX_VIA_NIT)
    stDTVProgramID.cOriginal_RF = INVALID_PHYSICAL_CHANNEL_NUMBER;
    stDTVProgramID.dwAlternativeTime = INVALID_ALTERNATIVETIME;
#endif

    stDTVProgramID.u32S2Frequency = TpInfo.u32Frequency;
    stDTVProgramID.u16SymbolRate = TpInfo.u16SymbolRate;
    stDTVProgramID.u8Polarity = TpInfo.u8Polarity;
    stDTVProgramID.SatelliteId = SatId;
    if(SetIDTable(TpId, (BYTE *)&stDTVProgramID, E_DATA_ID_TABLE))
    {
        //ActiveIDEntity(TpId, TRUE);
        ActiveIDEntity_DBSel(E_DTV_DB_SEL_DVBS, TpId, TRUE);
    }
    return TRUE;
}
#endif // #if(ENABLE_S2_DATABASE_DBM)

#endif // #if (ENABLE_S2)



////////////////////////////////////////////////////////////////////////////////
#endif // #ifndef __API_DTVSATTABLE_C__

