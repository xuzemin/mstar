/*
 *           Copyright 2010 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be 
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


///
/// @file 
/// @brief Declare functions for external Sharp BS2S7HZ6306 tuner control
///
//$Revision: 258 $ 
//$Date: 2008-02-06 14:05:26 -0500 (Wed, 06 Feb 2008) $
// 
#ifndef ExtSharpBS2S7HZ6306_h_h
	#define ExtSharpBS2S7HZ6306_h_h

	#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"
	#include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"
	
	//Included to support the blind scan fix made to blindscanform.cpp file ae per raptor.
	#define SHARP_TUNER_FACTOR_VALUE			9
	#define SHARP_HSYM_ACQ_TH_VALUE				20480
	#define SHARP_HSYM_CD_TH_VALUE				156
	//////////////////////////////////////////////////////////////////////////////////////

	#ifdef AVL_CPLUSPLUS
extern "C" {
	#endif

	AVL_DVBSx_ErrorCode ExtSharpBS2S7HZ6306_Initialize(struct AVL_Tuner * pTuner);
	AVL_DVBSx_ErrorCode ExtSharpBS2S7HZ6306_GetLockStatus(struct AVL_Tuner * pTuner );
	AVL_DVBSx_ErrorCode ExtSharpBS2S7HZ6306_Lock(struct AVL_Tuner * pTuner);

	#ifdef AVL_CPLUSPLUS
}
	#endif
#endif
