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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    MApp_MenuChannel.c
/// @author MStar Semiconductor Inc.
/// @brief  Channel Menu Helper Function
///////////////////////////////////////////////////////////////////////////////////////////////////
#define MAPP_MENUCHANNEL_C

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

#include "MsCommon.h"
#include "MApp_MenuChannel.h"
#include "apiDTVSatTable.h"
#include "MApp_GlobalSettingSt.h"
#include "mapp_si_if.h"
#include "mapp_demux.h"
#include "Utl.h"
#include "apiDigiTuner.h"
#include "MApp_GlobalVar.h"


#if (ENABLE_S2) //ohya++ 20130802
DTVPROGRAMID_M _afe_param[MAX_TPSOFSAT_NUM];

extern WORD MApi_DB_DFT_PositionBySatID2PCHIndex(BYTE bSatID,WORD wPosition);


MS_U16 _AddDefaultTPsExceptFreq(MS_U8 u8SatID,MS_U32 u32Freq)
{
     DTVPROGRAMID_M carrierParam;
     MS_U16 wTPPos, wTPIdx;
     MS_U16 wTPNum,wIdx;

     // Coverity 206235
     memset(&carrierParam, 0, sizeof(DTVPROGRAMID_M));

     wTPNum = MApi_DB_DFT_PhysicalChannelBySatID(u8SatID);
     wIdx = 1;
     for(wTPPos=0;wTPPos<wTPNum;wTPPos++)
     {
        wTPIdx = MApi_DB_DFT_PositionBySatID2PCHIndex(u8SatID, wTPPos);
        GetIDTable(wTPIdx, (BYTE *)&carrierParam,E_DATA_ID_TABLE);
        if(carrierParam.u32S2Frequency != u32Freq)
        {
            memcpy((MS_U8*)&_afe_param[wIdx] ,(MS_U8*)&carrierParam,sizeof(DTVPROGRAMID_M)) ;
            wIdx++;
        }
    }
    return (wIdx);
}


void MApp_MenuChannel_FullScan_Start(void)
{
    if(_u16MultiTPNum == 0)
        u32TPSCount = _AddDefaultTPsExceptFreq(_lnb_satelliteID[0],0);
    else
        u32TPSCount  = _u16MultiTPNum;
    _u32Frequency  = _afe_param[0].u32S2Frequency;
    _u16RFCh  = 0;
    _u32NumOfChanScan = 0;
    _u16GetTPSNum = 0;
    _u8SATTotalNum = MApi_DB_SAT_GetSATCount();
    _u8CurScanSATPos = 0;
    _u16AddTPSNum = u32TPSCount;
    _u8TPBlindScanProgress = 0;
    _u8MotorPosition = 0;
    eAutoTune = FE_TUNE_AUTO;
}

void MApp_MenuChannel_BuildScan_Start(void)
{
    printf("\r\nBuildScan_Start int");
    u32TPSCount = 0;
    _u32Frequency  = _afe_param[0].u32S2Frequency;
    _u16RFCh  = 0;
    _u32NumOfChanScan = 0;
    _u16GetTPSNum = 0;
    _u8SATTotalNum = MApi_DB_SAT_GetSATCount();
    _u8CurScanSATPos = 0;
    _u16AddTPSNum = 0;
    _u8TPBlindScanProgress = 0;
    _u8MotorPosition = 0;
    eAutoTune = FE_TUNE_AUTO;
}
void MApp_MenuChannel_ManuScan_Start(void)
{
    eAutoTune = FE_TUNE_AUTO;
    u32TPSCount = 1;
    _u32Frequency  = _afe_param[0].u32S2Frequency;
    _u32NumOfChanScan = 0;
    _u16GetTPSNum = 0;
    _u8SATTotalNum = MApi_DB_SAT_GetSATCount();
    _u8CurScanSATPos = 0;
    _u16AddTPSNum = u32TPSCount;
    _u8TPBlindScanProgress = 0;
    _u8MotorPosition = 0;
    _lnb_satelliteID[1]=0xFF;
    _u16RFCh  = 0;
}
void MApp_MenuChannel_NetworkScan_Start(void)
{
    printf("\r\nNetworkdScan_Start int");
     if(_u16MultiTPNum == 0)
        u32TPSCount = _AddDefaultTPsExceptFreq(_lnb_satelliteID[0],0);
    else
        u32TPSCount  = _u16MultiTPNum;
    _u32Frequency  = _afe_param[0].u32S2Frequency;
    _u16RFCh  = 0;
    _u32NumOfChanScan = 0;
    _u16GetTPSNum = 0;
    _u8SATTotalNum = MApi_DB_SAT_GetSATCount();
    _u8CurScanSATPos = 0;
    _u16AddTPSNum = u32TPSCount;
    _u8TPBlindScanProgress = 0;
    _u8MotorPosition = 0;
    eAutoTune = FE_TUNE_AUTO;
}

MS_BOOL MApp_MenuChannel_ResetScanSatIDList(void)
{
   BYTE i;
   for(i=0;i<MAX_SCANSAT_NUM;i++)
    _lnb_satelliteID[i]=0xff;
    _u8MultiSatNum = 0;

    return TRUE;
}

MS_BOOL MApp_MenuChannel_AddScanSat(MS_U8 SatID)
{
    _lnb_satelliteID[_u8MultiSatNum] = SatID;
    printf("\r\n_lnb_satelliteID[_u8MultiSatNum] = %2x  20100712 " ,_lnb_satelliteID[_u8MultiSatNum]);
    _u8MultiSatNum ++;
    return TRUE;
}

MS_BOOL MApp_MenuChannel_ResetScanTpList(void)
{
    WORD i;
   for(i=0;i<MAX_TPSOFSAT_NUM;i++)
    memset(&_afe_param[i],0x00,sizeof(DTVPROGRAMID_M));
    _u16MultiTPNum = 0;
    return TRUE;
}

MS_BOOL MApp_MenuChannel_AddScanTp(DTVPROGRAMID_M stTpParam)
{
    _afe_param[_u16MultiTPNum] = stTpParam;
    _u16MultiTPNum ++;
    return TRUE;
}

MS_BOOL MApp_MenuChannel_SetLNBPower(MS_EN_LNBPWR_ONOFF enLNBPowe,MS_U8 u8Polarity,MS_BOOL bPorInvert)
{
       return MApi_DigiTuner_Satellite_SetLNBPower(enLNBPowe,u8Polarity,bPorInvert);
}

#endif

#undef MAPP_MENUCHANNEL_C

