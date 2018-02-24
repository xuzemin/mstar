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
/// @brief Declare customized data structure for Sharp BS2S7HZ6306 tuner
/// 
//$Revision: 258 $ 
//$Date: 2008-02-06 14:05:26 -0500 (Wed, 06 Feb 2008) $
// 
#ifndef SharpBS2S7HZ6306_h_h
	#define SharpBS2S7HZ6306_h_h

	#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"

	#ifdef AVL_CPLUSPLUS
extern "C" {
	#endif

	enum SharpBS2S7HZ6306_BBGain
	{
		Bbg_0_Sharp,
		Bbg_1_Sharp,
		Bbg_2_Sharp,
		Bbg_4_Sharp   
	};

	enum SharpBS2S7HZ6306_PumpCurrent
	{
		PC_78_150_Sharp = 0,	///< = 0 min +/- 78 uA; typical +/- 120 uA; Max +/- 150 uA
		PC_169_325_Sharp = 1,	///< = 1 min +/- 169 uA; typical +/- 260 uA; Max +/- 325 uA
		PC_360_694_Sharp = 2,	///< = 2 min +/- 360 uA; typical +/- 555 uA; Max +/- 694 uA
		PC_780_1500_Sharp = 3	///< = 3 min +/- 780 uA; typical +/- 1200 uA; Max +/- 1500 uA
	};

	struct SharpBS2S7HZ6306_TunerPara
	{
		enum SharpBS2S7HZ6306_PumpCurrent     m_ChargPump;
		enum SharpBS2S7HZ6306_BBGain          m_BBGain;
	};

	struct SharpBS2S7HZ6306_Registers
	{
		AVL_uchar m_ucLPF;
		AVL_uchar m_ucRegData[4];
	};

	#ifdef AVL_CPLUSPLUS
}
	#endif
#endif
