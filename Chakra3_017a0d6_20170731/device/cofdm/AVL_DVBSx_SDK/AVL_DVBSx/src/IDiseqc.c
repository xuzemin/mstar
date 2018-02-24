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
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBase.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IDiseqc.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"
#include "AVL_DVBSx_SDK/BSP/IBSP.h"

///@cond
#define Diseqc_delay 20

/// Check if it is safe to switch DiSEqC operation mode.
/// 
/// @param pAVLChip A pointer point to a ::AVL_DVBSx_Chip object which is used to tell function which chip it is working on.
/// 
/// @return ::AVL_DVBSx_ErrorCode, 
/// Return ::AVL_DVBSx_EC_OK if it is OK to switch.
/// Return ::AVL_DVBSx_EC_Running if it is not safe to switch since the last transmit is not done yet.
/// Return ::AVL_DVBSx_EC_I2CFail if there is a I2C problem.
AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_IsSafeToSwitchMode( struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_uint32 i1;
	switch( pAVLChip->Diseqc_OP_Status )
	{
	case AVL_DVBSx_DOS_InModulation:
	case AVL_DVBSx_DOS_InTone:
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_st_addr, &i1);
		if( 1 != ((i1 & 0x00000040) >> 6) )	//check if the last transmit is done
		{
			r |= AVL_DVBSx_EC_Running;
		}
		break;
	case AVL_DVBSx_DOS_InContinuous:
	case AVL_DVBSx_DOS_Initialized:
		break;
	default:
		r |= AVL_DVBSx_EC_GeneralFail;
		break;
	}
	return(r);
}

///@endcond

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_Initialize( const struct AVL_DVBSx_Diseqc_Para * pDiseqcPara, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	if( AVL_DVBSx_EC_OK == r )
	{
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_srst_addr, 1);

		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_samp_frac_n_addr, 200);		//2M=200*10kHz
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_samp_frac_d_addr, pAVLChip->m_DemodFrequency_10kHz);

		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tone_frac_n_addr, ((pDiseqcPara->m_ToneFrequency_kHz)<<1));
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tone_frac_d_addr, pAVLChip->m_DemodFrequency_10kHz*10);

		// Initialize the tx_control
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
		i1 &= 0x00000300;
		i1 |= 0x20;		//reset tx_fifo
		i1 |= ((AVL_uint32)(pDiseqcPara->m_TXGap) << 6);
		i1 |= ((AVL_uint32)(pDiseqcPara->m_TxWaveForm) << 4);
		i1 |= (1<<3);			//enable tx gap.
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
		i1 &= ~(0x20);	//release tx_fifo reset
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

		// Initialize the rx_control
		i1 = ((AVL_uint32)(pDiseqcPara->m_RxWaveForm) << 2);
		i1 |= (1<<1);	//active the receiver
		i1 |= (1<<3);	//envelop high when tone present
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_rx_cntrl_addr, i1);
		i1 = (AVL_uint32)(pDiseqcPara->m_RxTimeout);
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_rx_msg_tim_addr, i1);

		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_srst_addr, 0);

		if( AVL_DVBSx_EC_OK == r )
		{
			pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_Initialized;
		}
	}
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_ReadModulationData( AVL_puchar pucBuff, AVL_puchar pucSize, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1,i2;
	AVL_uchar pucBuffTemp[4];
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_rx_st_addr, &i1);
	r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i2);
	if((i2>>8) & 0x01)
	{
		pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_InModulation; 
	}
	if( AVL_DVBSx_DOS_InModulation == pAVLChip->Diseqc_OP_Status )
	{
		// In modulation mode
		if( (!((i2>>8) & 0x01 ) && (0x00000004 == (i1 & 0x00000004))) || (((i2>>8) & 0x01 ) &&(0x00000004 != (i1 & 0x00000004))))
		{
			*pucSize = (AVL_uchar)((i1 & 0x00000078)>>3);
			//Receive data
			for( i1=0; i1<*pucSize; i1++ )
			{
				r |= AVL_DVBSx_II2C_Read(pAVLChip, diseqc_rx_fifo_map_addr, pucBuffTemp, 4);
				pucBuff[i1] = pucBuffTemp[3];
			}
		}
		else
		{
			r = AVL_DVBSx_EC_GeneralFail;
		}
	}
	else
	{
		r = AVL_DVBSx_EC_GeneralFail;
	}

	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_SendModulationData( const AVL_puchar pucBuff, AVL_uchar ucSize, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1, i2;
	AVL_uchar pucBuffTemp[8];
	AVL_uchar Continuousflag = 0;
	AVL_uint16 uiTempOutTh = 0;

	if( ucSize>8 )
	{
		r = AVL_DVBSx_EC_MemoryRunout;
	}
	else
	{
		r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));   
		r |= AVL_DVBSx_IDiseqc_IsSafeToSwitchMode(pAVLChip);
		if( AVL_DVBSx_EC_OK ==  r)
		{
			if (pAVLChip->Diseqc_OP_Status == AVL_DVBSx_DOS_InContinuous)
			{
				r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
				if ((i1>>10) & 0x01)
				{
					Continuousflag = 1;
					i1 &= 0xfffff3ff;
					r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
					r |= AVL_DVBSx_IBSP_Delay(Diseqc_delay);		//delay 20ms
				}
			}
			//reset rx_fifo
			r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_rx_cntrl_addr, &i2);
			r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_rx_cntrl_addr, (i2|0x01));
			r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_rx_cntrl_addr, (i2&0xfffffffe));

			r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
			i1 &= 0xfffffff8;	//set to modulation mode and put it to FIFO load mode
			r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

			//trunk address
			ChunkAddr(diseqc_tx_fifo_map_addr, pucBuffTemp);
			pucBuffTemp[3] = 0;
			pucBuffTemp[4] = 0;
			pucBuffTemp[5] = 0;
			for( i2=0; i2<ucSize; i2++ )
			{
				pucBuffTemp[6] = pucBuff[i2];

				r |= AVL_DVBSx_II2C_Write(pAVLChip, pucBuffTemp, 7);
			}                           
			i1 |= (1<<2);  //start fifo transmit.
			r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

			if( AVL_DVBSx_EC_OK == r )
			{
				pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_InModulation;
			}
			do 
			{
				r |= AVL_DVBSx_IBSP_Delay(1);
				if (++uiTempOutTh > 500)
				{
					r |= AVL_DVBSx_EC_TimeOut;
					r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
					return(r);
				}
				r = AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_st_addr, &i1);
			} while ( 1 != ((i1 & 0x00000040) >> 6) );

			r = AVL_DVBSx_IBSP_Delay(Diseqc_delay);		//delay 20ms
			if (Continuousflag == 1)			//resume to send out wave
			{
				//No data in FIFO
				r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
				i1 &= 0xfffffff8; 
				i1 |= 0x03;		//switch to continuous mode
				r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

				//start to send out wave
				i1 |= (1<<10);  
				r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
				if( AVL_DVBSx_EC_OK == r )
				{
					pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_InContinuous;
				}
			}
		}
		r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	}

	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_GetTxStatus( struct AVL_DVBSx_Diseqc_TxStatus * pTxStatus, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	if( (AVL_DVBSx_DOS_InModulation == pAVLChip->Diseqc_OP_Status) || (AVL_DVBSx_DOS_InTone == pAVLChip->Diseqc_OP_Status) )
	{
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_st_addr, &i1);
		pTxStatus->m_TxDone = (AVL_uchar)((i1 & 0x00000040)>>6);
		pTxStatus->m_TxFifoCount = (AVL_uchar)((i1 & 0x0000003c)>>2);
	}
	else
	{
		r |= AVL_DVBSx_EC_GeneralFail;
	}
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_GetRxStatus( struct AVL_DVBSx_Diseqc_RxStatus * pRxStatus, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	if( AVL_DVBSx_DOS_InModulation == pAVLChip->Diseqc_OP_Status )
	{
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_rx_st_addr, &i1);
		pRxStatus->m_RxDone = (AVL_uchar)((i1 & 0x00000004)>>2);
		pRxStatus->m_RxFifoCount = (AVL_uchar)((i1 & 0x000000078)>>3);
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_rx_parity_addr, &i1);
		pRxStatus->m_RxFifoParChk = (AVL_uchar)(i1 & 0x000000ff);
	}
	else
	{
		r |= AVL_DVBSx_EC_GeneralFail;
	}
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_SetLNBOut( AVL_uchar uiOut, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
	i1 &= 0xfffffdff;
	i1 |= ((uiOut & 0x1)<<9);
	r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
	r |= AVL_DVBSx_IBSP_Delay(Diseqc_delay);		//delay 20ms
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_GetLNBOut( AVL_puchar puiOut, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
	i1 &= 0x00000200;
	*puiOut = (AVL_uchar)(i1>>9);
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_SendTone( AVL_uchar ucTone, AVL_uchar ucCount, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1, i2;
	AVL_uchar pucBuffTemp[8];
	AVL_uchar Continuousflag = 0;
	AVL_uint16 uiTempOutTh = 0;

	if( ucCount>8 )
	{
		r = AVL_DVBSx_EC_MemoryRunout;
	}
	else
	{
		r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
		r |= AVL_DVBSx_IDiseqc_IsSafeToSwitchMode(pAVLChip);

		if( AVL_DVBSx_EC_OK == r )
		{
			if (pAVLChip->Diseqc_OP_Status == AVL_DVBSx_DOS_InContinuous)
			{
				r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
				if ((i1>>10) & 0x01)
				{
					Continuousflag = 1;
					i1 &= 0xfffff3ff;
					r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
					r |= AVL_DVBSx_IBSP_Delay(Diseqc_delay);		//delay 20ms
				}
			}
			//No data in the FIFO.
			r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
			i1 &= 0xfffffff8;  //put it into the FIFO load mode.
			if( 0 == ucTone )
			{
				i1 |= 0x01;
			}
			else
			{
				i1 |= 0x02;
			}
			r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

			//trunk address
			ChunkAddr(diseqc_tx_fifo_map_addr, pucBuffTemp);
			pucBuffTemp[3] = 0;
			pucBuffTemp[4] = 0;
			pucBuffTemp[5] = 0;
			pucBuffTemp[6] = 1;

			for( i2=0; i2<ucCount; i2++ )
			{
				r |= AVL_DVBSx_II2C_Write(pAVLChip, pucBuffTemp, 7);
			}

			i1 |= (1<<2);  //start fifo transmit.
			r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
			if( AVL_DVBSx_EC_OK == r )
			{
				pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_InTone;
			}
			do 
			{
				r |= AVL_DVBSx_IBSP_Delay(1);
				if (++uiTempOutTh > 500)
				{
					r |= AVL_DVBSx_EC_TimeOut;
					r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
					return(r);
				}
				r = AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_st_addr, &i1);
			} while ( 1 != ((i1 & 0x00000040) >> 6) );

			r = AVL_DVBSx_IBSP_Delay(Diseqc_delay);		//delay 20ms
			if (Continuousflag == 1)			//resume to send out wave
			{
				//No data in FIFO
				r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
				i1 &= 0xfffffff8; 
				i1 |= 0x03;		//switch to continuous mode
				r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

				//start to send out wave
				i1 |= (1<<10);  
				r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
				if( AVL_DVBSx_EC_OK == r )
				{
					pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_InContinuous;
				}
			}
		}
		r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	}
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_StartContinuous (struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	r |= AVL_DVBSx_IDiseqc_IsSafeToSwitchMode(pAVLChip);

	if( AVL_DVBSx_EC_OK == r )
	{
		//No data in FIFO
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
		i1 &= 0xfffffff8; 
		i1 |= 0x03;		//switch to continuous mode
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);

		//start to send out wave
		i1 |= (1<<10);  
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
		if( AVL_DVBSx_EC_OK == r )
		{
			pAVLChip->Diseqc_OP_Status = AVL_DVBSx_DOS_InContinuous;
		}
	}
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_StopContinuous (struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	if( AVL_DVBSx_DOS_InContinuous == pAVLChip->Diseqc_OP_Status )
	{
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
		i1 &= 0xfffff3ff;
		r |= AVL_DVBSx_II2C_Write32(pAVLChip, diseqc_tx_cntrl_addr, i1);
	}

	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_SetLNB1Out( AVL_uchar uiOut, struct AVL_DVBSx_Chip * pAVLChip ) 
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 uiTemp;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	r |= AVL_DVBSx_II2C_Read32(pAVLChip, gpio_reg_enb, &uiTemp);
	uiTemp &= ~(1<<1);
	r |= AVL_DVBSx_II2C_Write32(pAVLChip, gpio_reg_enb, uiTemp);  

	r |= AVL_DVBSx_II2C_Read32(pAVLChip, gpio_data_reg_out, &uiTemp);
	if(uiOut)
	{
		uiTemp |= 1<<1 ;
	}
	else
	{
		uiTemp &= ~(1<<1) ;
	}
	r |= AVL_DVBSx_II2C_Write32(pAVLChip, gpio_data_reg_out, uiTemp);
	r |= AVL_DVBSx_IBSP_Delay(Diseqc_delay);		//delay 20ms
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_GetLNB1Out( AVL_puchar puiOut, struct AVL_DVBSx_Chip * pAVLChip )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint32 uiTemp;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	r |= AVL_DVBSx_II2C_Read32(pAVLChip, gpio_data_reg_out, &uiTemp);
	if(uiTemp & (1<<1))
	{
		*puiOut = 1;
	}
	else
	{
		*puiOut = 0;
	}
	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IDiseqc_GetContinuous (AVL_puchar puiCon,struct AVL_DVBSx_Chip * pAVLChip )
{
      AVL_DVBSx_ErrorCode r;
	AVL_uint32 i1;
	r = AVL_DVBSx_IBSP_WaitSemaphore(&(pAVLChip->m_semDiseqc));
	if( AVL_DVBSx_DOS_InContinuous == pAVLChip->Diseqc_OP_Status )
	{
		r |= AVL_DVBSx_II2C_Read32(pAVLChip, diseqc_tx_cntrl_addr, &i1);
		i1 &= 0x00000403;
	      *puiCon = (AVL_uchar)(i1>>10);
	}

	r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(pAVLChip->m_semDiseqc));
	return(r);
}
