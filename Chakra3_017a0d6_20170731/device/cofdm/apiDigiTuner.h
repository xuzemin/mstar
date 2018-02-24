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

//////////////////////////////////////////////////////////////////////////////
///
/// @file   apiDigiTuner.h
/// @brief  Digital Tuner Low-Level API
/// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////

#ifndef _API_DIGI_TUNER_H_
#define _API_DIGI_TUNER_H_

#if (ENABLE_S2)
//---------------------------------------------------------------------------
//  Include file
//---------------------------------------------------------------------------
#include "apiDTVSatTable.h"
#include "msAPI_Tuner.h"
#include "msAPI_DTVSystem.h"
/*
extern MS_BOOL MApi_DigiTuner_Init(void);
#ifdef DVBS
extern void MApi_DigiTuner_ForceRetune(void);
#endif
extern MS_BOOL MApi_DigiTuner_PowerOnOff(MS_BOOL bEnPower);
extern MS_BOOL MApi_DigiTuner_GetTPSInfo(MS_FE_CARRIER_PARAM* pParam);
extern MS_BOOL MApi_DigiTuner_GetSatInfo(MS_SAT_PARAM* pSatInfo);
extern MS_BOOL MApi_DigiTuner_GetCurrentLOF(MS_U16* pLOF);
extern MS_BOOL MApi_DigiTuner_SetBW(EN_TER_BW_MODE eBandWidth);
extern MS_BOOL MApi_DigiTuner_GetLock(void);
extern MS_BOOL MApi_DigiTuner_GetPWR(MS_S16 *ps16PWR);
extern MS_BOOL MApi_DigiTuner_GetBER(float *pfltBER);
extern MS_BOOL MApi_DigiTuner_GetRollOff(EN_SAT_ROLL_OFF_TYPE *pRollOff);
extern MS_BOOL MApi_DigiTuner_Satellite_Set22K(MS_BOOL b22KOn);
*/


typedef enum
{
    //unicalbe
    E_ACT_DISEQC_ODU_CHCHG,
    E_ACT_DISEQC_ODU_PWROFF,
    E_ACT_DISEQC_ODU_UBXSIGNAL,
    E_ACT_DISEQC_ODU_CONFIG,
    E_ACT_DISEQC_ODU_LOFREQ,
} EN_DVBS_ACTION_TYPE;
//DiSEqC
// Framing byte
#define DISEQC_FRM                0xE0
#define DISEQC_FRM_REPEAT         (1 << 0)
#define DISEQC_FRM_REPLY_REQ      (1 << 1)

// Address byte
#define DISEQC_ADR_ALL            0x00
#define DISEQC_ADR_SW_ALL         0x10
#define DISEQC_ADR_LNB            0x11
#define DISEQC_ADR_LNB_SW         0x12
#define DISEQC_ADR_SW_BLK         0x14
#define DISEQC_ADR_SW             0x15
#define DISEQC_ADR_SMATV          0x18
#define DISEQC_ADR_POL_ALL        0x20
#define DISEQC_ADR_POL_LIN        0x21
#define DISEQC_ADR_POS_ALL        0x30
#define DISEQC_ADR_POS_AZ         0x31
#define DISEQC_ADR_POS_EL         0x32

// Command byte
#define DISEQC_CMD_RESET           0x00
#define DISEQC_CMD_CLR_RESET       0x01
#define DISEQC_CMD_WRITE_N0        0x38
#define DISEQC_CMD_WRITE_N1        0x39
#define DISEQC_CMD_WRITE_FREQ      0x58
#define DISEQC_CMD_HALT            0x60
#define DISEQC_CMD_LMT_OFF         0x63
#define DISEQC_CMD_LMT_E           0x66
#define DISEQC_CMD_LMT_W           0x67
#define DISEQC_CMD_DRIVE_E         0x68
#define DISEQC_CMD_DRIVE_W         0x69
#define DISEQC_CMD_STORE_POS       0x6A
#define DISEQC_CMD_GOTO_POS        0x6B
#define DISEQC_CMD_GOTO_X          0x6E
#define DISEQC_CMD_ODU_CHCHG       0x5A
#define DISEQC_CMD_ODU_PWROFF      0x5A
#define DISEQC_CMD_ODU_UBXSIGNAL   0x5B
#define DISEQC_CMD_ODU_CONFIG      0x5B
#define DISEQC_CMD_ODU_LOFREQ      0x5B
#define DISEQC_CMD_ODU_CHCHG_MDU   0x5C
#define DISEQC_CMD_ODU_PWROFF_MDU  0x5C
#define DISEQC_CMD_ODU_UBXSIGNAL_MDU   0x5D
#define DISEQC_CMD_ODU_CONFIG_MDU  0x5D
#define DISEQC_CMD_ODU_LOFREQ_MDU  0x5D

extern WORD MApi_GetLocationNum(void);
#define LOCATION_NUM (MApi_GetLocationNum())

extern MS_BOOL MApi_DigiTuner_Satellite_SetLNBPower(MS_EN_LNBPWR_ONOFF enLNBPowe,MS_U8 u8Polarity,MS_BOOL bPorInvert);
extern DISH_LOCATION SetSATLocation[];
extern MS_BOOL MApi_DigiTuner_GetMaxLockTime(EN_FE_TUNE_MODE eMode, MS_U32 *u32LockTime);
extern MS_BOOL MApi_DigiTuner_Tune2RfCh(MS_SAT_PARAM stSatInfor,DTVPROGRAMID_M *pParam, EN_FE_TUNE_MODE eMode);
extern MS_BOOL MApi_DigiTuner_MPEGGetLock(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_GoSatPos(MS_U8 u8SatPos);
extern MS_BOOL MApi_DigiTuner_TPSGetLock(void);
extern MS_BOOL MApi_DigiTuner_GetRFOffset(MS_S16 *ps16RFOffset);
extern MS_BOOL MApi_DigiTuner_BlindScan_Start(MS_SAT_PARAM stSATParam,MS_U8 u8Polarity,MS_BOOL bIsHiLOF);
extern MS_BOOL MApi_DigiTuner_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress);

extern MS_BOOL MApi_DigiTuner_BlindScan_WaitCurFeqFinished(MS_U8* u8Progress,MS_U8* u8FindNum);
extern MS_BOOL MApi_DigiTuner_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTPTable);
extern MS_BOOL MApi_DigiTuner_BlindScan_Cancel(void);
extern MS_BOOL MApi_DigiTuner_BlindScan_End(void);
extern void MApi_DigiTuner_GetSNR(MS_U16 *pu32SNR);
extern MS_U16 MApi_DigiTuner_getCurRFSignalSNR_Persent(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorConinuteWest(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorConinuteEast(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorStepEast(MS_U8 u8Step);
extern MS_BOOL MApi_DigiTuner_DiSEqC_MotorStepWest(MS_U8 u8Step);
extern MS_BOOL MApi_DigiTuner_DiSEqC_HaltMotor(void);

extern MS_BOOL MApi_DigiTuner_DiSEqC_Reset(void);
extern void MApi_Demod_HWReset(MS_BOOL bReset);
extern MS_BOOL MApi_DigiTuner_DiSEqC_SetEastLimit(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_SetWestLimit(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_DisableLimit(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_GoReferencePoint(void);
extern MS_BOOL MApi_DigiTuner_DiSEqC_SaveSatPos(MS_U8 u8SatPos);
extern MS_BOOL MApi_DigiTuner_DiSEqC_GotoX(MS_U16 u16SatLongitude,MS_S16 s16MyLongitude,MS_S16 s16MyLatitude);
extern void Int_DigiTuner_Tp_Sat(void);
extern MS_BOOL MApi_DigiTuner_GetPWR(MS_S16* ps16PWR);
extern MS_BOOL MApi_DigiTuner_DiSEqC_SendCmd(EN_DVBS_ACTION_TYPE eDiseqcCmd, U16 u16Param1, S16 s16Param2, S16 s16Param3);
extern void MApi_DigiTuner_Uni_SetFreq(void);
extern MS_BOOL ODU_ChChg(MS_U8 u8UbId, MS_U8 u8Bank, MS_U16 u16TuneWord, MS_BOOL bMDU);

extern void MApi_DigiTuner_Get_CurSATInfo(MS_SAT_PARAM* pstSAT_PARAM);

#endif
#endif // _API_DIGI_TUNER_H_

