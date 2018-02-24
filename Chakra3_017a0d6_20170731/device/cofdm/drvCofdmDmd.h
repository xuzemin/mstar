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
/// @file   drvOfdmDmd.h
/// @brief  COFDM Dmd Common Driver Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////
#include "apiDTVSatTable.h"
#ifndef _DRV_COFDM_DMD_H_
#define _DRV_COFDM_DMD_H_


//-------------------------------------------------------------------------------------------------
//  Driver Capability
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define TUNER_POLL_LOCK         1

//#define MAX_TPSOFSAT            10
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------



typedef struct
{
    // N/A
} CofdmDMD_Mode;

// Device dependant parameter
typedef struct
{
	MS_U32							u32TunerFreq;						///Tuner Freq
	MS_U32							u32SymbolRate;						///SymbolRate
	MS_U8							u8BandWidth;						///Tunser Bandwith
} CofdmDMD_Param;

typedef struct
{
	// N/A
}CofdmDMD_Status;

//-------------------------------------------------------------------------------------------------
//  Function Prototype
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
extern MS_BOOL MDrv_CofdmDmd_SetTsSerial(MS_BOOL bSerial,MS_BOOL bInvTsClock,MS_BOOL bInpuSource);
extern MS_BOOL MDrv_CofdmDmd_Init(void);
extern MS_BOOL MDrv_CofdmDmd_Open(void);
extern MS_BOOL MDrv_CofdmDmd_Close(void);
extern MS_BOOL MDrv_CofdmDmd_Reset(void);
extern MS_BOOL MDrv_CofdmDmd_Restart(CofdmDMD_Param *pParam);
extern MS_BOOL MDrv_CofdmDmd_SetMode(CofdmDMD_Mode *pMode);
extern MS_BOOL MDrv_CofdmDmd_TsOut(MS_BOOL bEnable);
extern MS_BOOL MDrv_CofdmDmd_PowerOnOff(MS_BOOL bPowerOn);
extern MS_BOOL MDrv_CofdmDmd_SetBW(MS_U32 u32BW);
extern MS_BOOL MDrv_CofdmDmd_GetBW(MS_U32 *pu32BW);
extern MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock);
extern MS_BOOL MDrv_CofdmDmd_TPSGetLock(MS_BOOL *pbLock);
extern MS_BOOL MDrv_CofdmDmd_MPEGGetLock(MS_BOOL *pbLock);
extern MS_BOOL MDrv_CofdmDmd_GetSNR(MS_U32 *pu32SNR);
extern MS_BOOL MDrv_CofdmDmd_GetBER(float *pfBER);
extern MS_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *ps32Signal);
extern MS_BOOL MDrv_CofdmDmd_GetParam(CofdmDMD_Param *pParam);
extern MS_BOOL MDrv_CofdmDmd_Config(MS_U8 *pRegParam);
extern MS_BOOL MDrv_CofdmDmd_GetRollOff(MS_U8 *pRollOff);
extern MS_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff);

extern MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bParam);
extern MS_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress);
extern MS_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MS_U8* u8Progress,MS_U8 *u8FindNum);
extern MS_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void);
extern MS_BOOL MDrv_CofdmDmd_BlindScan_End(void);
extern MS_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MS_U32 *u32CurrentFeq);

extern MS_BOOL MDrv_DiSEqC_SetTone(MS_BOOL bTone1);
extern MS_BOOL MDrv_DiSEqC_SetLNBOut(MS_BOOL ucLow);
extern MS_BOOL MDrv_DiSEqC_GetLNBOut(MS_BOOL* bLNBOutLow);
extern MS_BOOL MDrv_DiSEqC_Set22kOnOff(MS_BOOL b22kOn);
extern MS_BOOL MDrv_DiSEqC_Get22kOnOff(MS_BOOL* b22kOn);
extern MS_BOOL MDrv_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize);

#if (SUPPORT_UNICABLE)
extern MS_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo);
#endif

#endif // _DRV_TUNER_H_

