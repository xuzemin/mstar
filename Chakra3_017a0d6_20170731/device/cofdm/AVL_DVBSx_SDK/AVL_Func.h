/*
 *           Copyright 2007-2009 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


#ifndef AVL_FUNC_H_
#define AVL_FUNC_H_

#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"

struct Signal_Level
{
    AVL_uint16 SignalLevel;
    AVL_int16 SignalDBM;
};

void AVL_Error_Dispose(AVL_DVBSx_ErrorCode r);
//AVL_DVBSx_ErrorCode AVL_A8293_Control(AVL_uchar Level);
AVL_DVBSx_ErrorCode AVL_SetMpegMode(AVL_uchar bParallelTS,AVL_uchar bLockChannel,MS_BOOL bchangeclock,MS_BOOL bInpuSource);
AVL_DVBSx_ErrorCode AVL_Initialize(void);
AVL_DVBSx_ErrorCode AVL_SetFrequency(AVL_uint16 uiFreq_MHz,AVL_uint32 uiSymbolRate_Hz);

AVL_DVBSx_ErrorCode AVL_GetLockStatus(void);
AVL_DVBSx_ErrorCode AVL_GetBER(float *pfBER);
AVL_DVBSx_ErrorCode AVL_GetPER(float *pfPER);
AVL_DVBSx_ErrorCode AVL_GetSNR(AVL_int32 *pfSNR);
AVL_DVBSx_ErrorCode AVL_GetRFOffset(AVL_int16 *piRFOff);
AVL_DVBSx_ErrorCode AVL_GetSinalLevel(AVL_int16 *piRFSignalLevel);
AVL_DVBSx_ErrorCode AVL_GetSignalInfo(struct AVL_DVBSx_SignalInfo *pSignalInfo);

AVL_DVBSx_ErrorCode AVL_DiSEqC_SetToneOut(AVL_uchar ucTone);
AVL_DVBSx_ErrorCode AVL_DiSEqC_SetLNBOut(AVL_uchar ucLow);
AVL_DVBSx_ErrorCode AVL_DiSEqC_GetLNBOut(AVL_puchar pucLNBOut);
AVL_DVBSx_ErrorCode AVL_DiSEqC_Set22kOnOff(AVL_uchar uc22kOn);
AVL_DVBSx_ErrorCode  AVL_DiSEqC_Get22kOnOff(AVL_puchar puc22kOn);
AVL_DVBSx_ErrorCode AVL_DiSEqC_SetCmd(AVL_puchar pucCmd,AVL_uchar ucCmdSize);

AVL_DVBSx_ErrorCode AVL_Blind_start(AVL_int16 u16StartFreq,AVL_int16 u16EndFreq);
AVL_DVBSx_ErrorCode AVL_Blind_NextFreqBlindScan(AVL_uchar* u8BlindScanEnd,MS_U8* u8Progress);
AVL_DVBSx_ErrorCode AVL_Blind_WaitCurFreqFinished(AVL_uchar* u8Progress,AVL_uchar* ucFindNum);
AVL_DVBSx_ErrorCode AVL_Blind_Cancel(void);
AVL_DVBSx_ErrorCode AVL_Blind_End(void);
AVL_DVBSx_ErrorCode AVL_Blind_GetChannel(AVL_uint16 u16Start,AVL_uint16 *chNum,struct AVL_DVBSx_Channel *channels);
AVL_uint32 AVL_Blind_GetCurrentFreq(void);

#endif

