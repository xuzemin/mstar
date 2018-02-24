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


//$Revision: 202 $ 
//$Date: 2008-01-14 17:28:53 -0500 (Mon, 14 Jan 2008) $
// 
#ifndef IBSP_h_h
	#define IBSP_h_h

	#include "avl_dvbsx.h"

	#ifdef AVL_CPLUSPLUS
extern "C" {
	#endif

	#define MAX_II2C_READ_SIZE	64
	#define MAX_II2C_Write_SIZE	64

	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_Initialize(System::String^ strServerName, int iPort);
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_Dispose(void);
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_Delay( AVL_uint32 uiMS );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CRead( const struct AVL_DVBSx_Chip * pAVLChip,  AVL_puchar pucBuff, AVL_puint16 puiSize );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CWrite( const struct AVL_DVBSx_Chip * pAVLChip,  AVL_puchar pucBuff, AVL_puint16 puiSize );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_InitSemaphore( AVL_psemaphore pSemaphore );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_WaitSemaphore( AVL_psemaphore pSemaphore );         
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_ReleaseSemaphore( AVL_psemaphore pSemaphore );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CReadGeneric( AVL_uint16 uiSlaveAddr,  AVL_puchar pucBuff, AVL_puint16 puiSize );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CWriteGeneric( AVL_uint16 uiSlaveAddr,  AVL_puchar pucBuff, AVL_puint16 puiSize );

	///Aardvark GPIO functions

	//AA_GPIO_BITS
	#define AA_GPIO_SCL  		0x01		///< Pin 1
	#define	AA_GPIO_SDA  		0x02		///< Pin 3
	#define	AA_GPIO_MISO 		0x04		///< Pin 5
	#define	AA_GPIO_SCK  		0x08		///< Pin 7
	#define	AA_GPIO_MOSI 		0x10		///< Pin 8
	#define	AA_GPIO_SS   		0x20		///< Pin 9

	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_AAGPIO_SetDirection( AVL_uchar ucDirectionMask );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_AAGPIO_SetValue( AVL_uchar ucValueMask );
	AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_AAGPIO_GetValue( AVL_puchar pucValueMask );

	#ifdef AVL_CPLUSPLUS
}
	#endif
#endif

