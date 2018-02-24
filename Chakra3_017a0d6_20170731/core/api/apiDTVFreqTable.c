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

//#include "MsCommon.h"
#include "Board.h"
#include "Utl.h"

#if (ENABLE_S2)

#include "apiDTVFreqTable.h"

static BYTE m_selTPTableMap[MAX_S2_IDTABLE_MAP];

static MS_BOOL IsPCHEntirySelect(WORD wPCH)
{
     if (MAX_DTV_S2_MUX_NUMBER<= wPCH)
         return FALSE;
     if (IsS2ChannelEntityActive(wPCH) == FALSE)
     {
          return FALSE;
     }

    return ((m_selTPTableMap[wPCH/8] & (0x01 << (wPCH % 8))) ? TRUE : FALSE);
}

BOOLEAN MApi_DFT_SelectPCHEntity(WORD wPCH, MS_BOOL bSelected)
{
    WORD cTemp;

    if (MAX_DTV_S2_MUX_NUMBER<= wPCH)
        return FALSE;

    if (IsS2ChannelEntityActive(wPCH) == FALSE)
    {
          return FALSE;
    }

    cTemp = wPCH / 8;
    if (TRUE == bSelected)
    {
        m_selTPTableMap[cTemp] =  m_selTPTableMap[cTemp] | (0x01 << (wPCH % 8));
    }
    else
    {
        m_selTPTableMap[cTemp] =  m_selTPTableMap[cTemp] & ~(0x01 << (wPCH % 8));
    }
    return TRUE;
}

BOOLEAN MApi_DFT_IsPCHEntirySelect(WORD wPCH)
{
    return IsPCHEntirySelect(wPCH);
}
static void  UnSelectAllPCH(void)
{
    WORD i;
    for (i = 0; i < (MAX_S2_IDTABLE_MAP); i++)
    {
        m_selTPTableMap[i] = 0x00;//zeng change
    }
}

void MApi_DFT_UnSelectAllPCH(void)
{
    UnSelectAllPCH();
}

/*static WORD GetPhysicalChannelCount(void)
{
    WORD wPchIndex;
    WORD wPhyChCount = 0;

    for (wPchIndex = 0; wPchIndex < MAX_DTV_S2_MUX_NUMBER; wPchIndex++)
    {
        if (TRUE == IsS2ChannelEntityActive(wPchIndex))
            wPhyChCount++;
    }

    if (MAX_DTV_S2_MUX_NUMBER <= wPhyChCount)
        return MAX_DTV_S2_MUX_NUMBER;

    return wPhyChCount;
}*/

void MApi_DB_DFT_CheckIfAnySamePCH(WORD *pwPhyChIdx, DTVPROGRAMID_M *pCarrierParam)
{
    MS_U8   u8SatID = INVALID_SATINDEX; // Coverity 218309
    DTVPROGRAMID_M CarrierParam;
    WORD i;

       // Coverity 218308
       memset(&CarrierParam, 0, sizeof(DTVPROGRAMID_M));

    for (i = 0; i < MAX_DTV_S2_MUX_NUMBER; i++)
    {
        if (TRUE == IsS2ChannelEntityActive(i))
        {
            GetIDTable(i, (BYTE *)&u8SatID, E_DATA_ID_SATLITE);
            GetIDTable(i, (BYTE *)&CarrierParam, E_DATA_ID_TABLE);
            if (CarrierParam.u32S2Frequency == pCarrierParam->u32S2Frequency
            && u8SatID == pCarrierParam->SatelliteId
            && CarrierParam.u8Polarity== pCarrierParam->u8Polarity)
            {
                *pwPhyChIdx = i;
                return ;
            }
        }
    }
    *pwPhyChIdx = INVALID_PCHINDEX;
    return ;
}

static WORD GetEmptyIndexOfPhysicalChannelTable(void)
{
    WORD wPchIndex;

    for (wPchIndex = 0; wPchIndex < MAX_DTV_S2_MUX_NUMBER; wPchIndex++)
    {
        if (FALSE == IsS2ChannelEntityActive(wPchIndex))
        {
            return wPchIndex;
        }
    }

    return INVALID_PCHINDEX;
}

BOOLEAN MApi_DB_DFT_AddPhysicalChannel(WORD *pwPhyChIdx, DTVPROGRAMID_M *pCarrierParam)
{
    WORD wPchIndex;

    wPchIndex = GetEmptyIndexOfPhysicalChannelTable();
    printf("\r\n wPchIndex_emptyindex = %d 20100806 ",wPchIndex);
    if (MAX_DTV_S2_MUX_NUMBER <= wPchIndex || INVALID_PCHINDEX == wPchIndex)
    {
        return FALSE;
    }
    if ( !SetIDTable(wPchIndex, (BYTE *)pCarrierParam, E_DATA_ID_TABLE))
    {
        return FALSE;
    }

    //ActiveIDEntity(wPchIndex, TRUE);
    ActiveIDEntity_DBSel(E_DTV_DB_SEL_DVBS, wPchIndex, TRUE);

    *pwPhyChIdx = wPchIndex;

    return TRUE;
}

static WORD _MApi_DB_DFT_PCHIndex2PositionBySatID(WORD wPchIndex,BYTE *pbSatID)
{
    WORD wPos = 0;
    BYTE u8TmpSatID,u8SatID;
    WORD i;

    if(pbSatID == NULL)
        return(INVALID_POSBYSATID);

    if(!GetIDTable(wPchIndex, (BYTE *)&u8SatID, E_DATA_ID_SATLITE))
    {
        return(INVALID_POSBYSATID);
    }
    for(i=0;i<wPchIndex;i++)
    {
        if(GetIDTable(i, (BYTE *)&u8TmpSatID, E_DATA_ID_SATLITE) && u8TmpSatID == u8SatID)
        {
            wPos++;
        }
    }
    return(wPos);
}

WORD MApi_DB_DFT_PCHIndex2PositionBySatID(WORD wPchIndex,BYTE *pbSatID)
{
    return _MApi_DB_DFT_PCHIndex2PositionBySatID(wPchIndex,pbSatID);
}

BOOLEAN MApi_DB_DFT_UpdatePhysicalChannel(WORD wPchIndex, DTVPROGRAMID_M *pCarrierParam)
{
    return SetIDTable(wPchIndex, (BYTE *)pCarrierParam, E_DATA_ID_TABLE);
}

BOOLEAN MApi_DB_DFT_DeletePhysicalChannel(WORD wPhyChIdx)
{
    if (MAX_NUM_OF_PCH <= wPhyChIdx || INVALID_PCHINDEX == wPhyChIdx)
    {
        return FALSE;
    }

    //ActiveIDEntity(wPhyChIdx, FALSE);
    ActiveIDEntity_DBSel(E_DTV_DB_SEL_DVBS, wPhyChIdx, FALSE);

    return TRUE;
}
#endif

