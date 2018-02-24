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
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"
#include "AVL_DVBSx_SDK/BSP/IBSP.h"

AVL_DVBSx_ErrorCode Init_AVL_DVBSx_ChipObject(struct AVL_DVBSx_Chip * pAVL_DVBSx_ChipObject, AVL_uint16 uiSlaveAddress)
{
	AVL_DVBSx_ErrorCode r;
	pAVL_DVBSx_ChipObject->m_SlaveAddr = uiSlaveAddress;
	pAVL_DVBSx_ChipObject->m_StdBuffIndex = 0;
	pAVL_DVBSx_ChipObject->Diseqc_OP_Status = AVL_DVBSx_DOS_Uninitialized;
	r = AVL_DVBSx_IBSP_InitSemaphore(&(pAVL_DVBSx_ChipObject->m_semRx));
	r |= AVL_DVBSx_IBSP_InitSemaphore(&(pAVL_DVBSx_ChipObject->m_semI2CRepeater));
	r |= AVL_DVBSx_IBSP_InitSemaphore(&(pAVL_DVBSx_ChipObject->m_semI2CRepeater_r));
	r |= AVL_DVBSx_IBSP_InitSemaphore(&(pAVL_DVBSx_ChipObject->m_semDiseqc));
	r |= AVL_DVBSx_II2C_Initialize(); // there is a internal protection to assure it will be initialized only once.
	return (r);
}
