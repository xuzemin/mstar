/*
 *           Copyright 2012 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be 
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


///$Date: 2012-3-8 21:47 $
///
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"

AVL_DVBSx_ErrorCode AVL_DVBSx_ITuner_CalculateLPF(AVL_uint16 uiSymbolRate_10kHz, struct AVL_Tuner * pTuner)
{
	AVL_uint32 lpf = uiSymbolRate_10kHz;
	lpf *= 675;			//roll off = 0.35
	lpf /= 10000;
	lpf += 30;
	pTuner->m_uiLPF_100kHz = (AVL_uint16)lpf;
	return(AVL_DVBSx_EC_OK);
}
