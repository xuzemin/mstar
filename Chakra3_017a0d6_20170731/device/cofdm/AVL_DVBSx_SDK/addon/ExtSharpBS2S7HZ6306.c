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


//$Revision: 776 $ 
//$Date: 2009-05-18 13:48:32 -0400 (Mon, 18 May 2009) $
// 
#include "SharpBS2S7HZ6306.h"
#include "ExtSharpBS2S7HZ6306.h"
#include "II2CRepeater.h"
#include "IBSP.h"
#include "II2C.h"
#include "IBase.h"

AVL_DVBSx_ErrorCode SharpBS2S7HZ6306Regs_SetLPF( AVL_uint16 uiLPF_10kHz, struct SharpBS2S7HZ6306_Registers * pTunerRegs )
{
	uiLPF_10kHz /=100;
	if( uiLPF_10kHz <10 )
	{
		uiLPF_10kHz = 10;
	}
	if( uiLPF_10kHz>34 )
	{
		uiLPF_10kHz = 34;
	}
	pTunerRegs->m_ucLPF = (AVL_uchar)((uiLPF_10kHz-10)/2+3);
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode SharpBS2S7HZ6306_SetBBGain( enum SharpBS2S7HZ6306_BBGain BBGain, struct SharpBS2S7HZ6306_Registers * pTunerRegs )
{
	pTunerRegs->m_ucRegData[0] &=  ~(0x3<<5);
	pTunerRegs->m_ucRegData[0] |= ((AVL_uchar)(BBGain)<<5);
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode SharpBS2S7HZ6306_SetChargePump( enum SharpBS2S7HZ6306_PumpCurrent Current, struct SharpBS2S7HZ6306_Registers * pTunerRegs )
{
	pTunerRegs->m_ucRegData[2] &= ~(0x3<<5);
	pTunerRegs->m_ucRegData[2] |= ((AVL_uchar)(Current)<<5);
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode SharpBS2S7HZ6306_SetFrequency( AVL_uint16 uiFrequency_100kHz, struct SharpBS2S7HZ6306_Registers * pTunerRegs)
{
	AVL_uint16 P, N, A, DIV;

	if( uiFrequency_100kHz<9500 )
	{
		return(AVL_DVBSx_EC_GeneralFail);
	}
	else if( uiFrequency_100kHz<9860 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x5<<5);
		P = 16;
		DIV = 1;
	}
	else if( uiFrequency_100kHz<10730 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x6<<5);
		P = 16;
		DIV = 1;
	}
	else if( uiFrequency_100kHz<11540 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x7<<5);
		P = 32;
		DIV = 1;
	}
	else if( uiFrequency_100kHz<12910 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x1<<5);
		P = 32;
		DIV = 0;
	}
	else if( uiFrequency_100kHz<14470 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x2<<5);
		P = 32;
		DIV = 0;
	}
	else if( uiFrequency_100kHz<16150 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x3<<5);
		P = 32;
		DIV = 0;
	}
	else if( uiFrequency_100kHz<17910 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x4<<5);
		P = 32;
		DIV = 0;
	}
	else if( uiFrequency_100kHz<19720 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x5<<5);
		P = 32;
		DIV = 0;
	}
	else if( uiFrequency_100kHz<=21500 )
	{
		pTunerRegs->m_ucRegData[3] &= ~(0x7<<5);
		pTunerRegs->m_ucRegData[3] |= (0x6<<5);
		P = 32;
		DIV = 0;
	}
	else
	{
		return(AVL_DVBSx_EC_GeneralFail);
	}

	A = (uiFrequency_100kHz/10)%P;
	N = (uiFrequency_100kHz/10)/P;

	pTunerRegs->m_ucRegData[3] &= ~(0x1<<4);
	if( P==16 )
	{
		pTunerRegs->m_ucRegData[3] |= (0x1<<4);
	}

	pTunerRegs->m_ucRegData[3] &= ~(0x1<<1);
	pTunerRegs->m_ucRegData[3] |= (AVL_uchar)(DIV<<1);

	pTunerRegs->m_ucRegData[1] &= ~(0x1f<<0);
	pTunerRegs->m_ucRegData[1] |= (AVL_uchar)(A<<0);

	pTunerRegs->m_ucRegData[1] &= ~(0x7<<5);
	pTunerRegs->m_ucRegData[1] |= (AVL_uchar)(N<<5);
	pTunerRegs->m_ucRegData[0] &= ~(0x1f<<0);
	pTunerRegs->m_ucRegData[0] |= (AVL_uchar)((N>>3)<<0);

	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode SharpBS2S7HZ6306_CommitSetting(const struct AVL_Tuner * pTuner , struct SharpBS2S7HZ6306_Registers * pTunerRegs )
{
	AVL_DVBSx_ErrorCode r;
	pTunerRegs->m_ucRegData[0] &= 0x7f;
	pTunerRegs->m_ucRegData[2] |= 0x80;

	pTunerRegs->m_ucRegData[2] &= ~(0x7<<2);
	pTunerRegs->m_ucRegData[3] &= ~(0x3<<2);

	r = AVL_DVBSx_II2CRepeater_SendData((AVL_uchar)(pTuner->m_uiSlaveAddress), pTunerRegs->m_ucRegData, 4, pTuner->m_pAVLChip );
	if( r != AVL_DVBSx_EC_OK )
	{
		return(r);
	}
	pTunerRegs->m_ucRegData[2] |= (0x1<<2);

	r |= AVL_DVBSx_II2CRepeater_SendData((AVL_uchar)(pTuner->m_uiSlaveAddress), (pTunerRegs->m_ucRegData)+2, 1, pTuner->m_pAVLChip );
	if( r != AVL_DVBSx_EC_OK )
	{
		return(r);
	}
	r |= AVL_DVBSx_IBSP_Delay(12);

	r |= SharpBS2S7HZ6306Regs_SetLPF ((AVL_uint16)(pTuner->m_uiLPF_100kHz*10), pTunerRegs);
	pTunerRegs->m_ucRegData[2] |= ((((pTunerRegs->m_ucLPF)>>1)&0x1)<<3); /* PD4 */
	pTunerRegs->m_ucRegData[2] |= ((((pTunerRegs->m_ucLPF)>>0)&0x1)<<4); /* PD5 */
	pTunerRegs->m_ucRegData[3] |= ((((pTunerRegs->m_ucLPF)>>3)&0x1)<<2); /* PD2 */
	pTunerRegs->m_ucRegData[3] |= ((((pTunerRegs->m_ucLPF)>>2)&0x1)<<3); /* PD3 */

	r |= AVL_DVBSx_II2CRepeater_SendData((AVL_uchar)(pTuner->m_uiSlaveAddress), (pTunerRegs->m_ucRegData)+2, 2, pTuner->m_pAVLChip );

	return(r);
}

//*******************************************************************************************

AVL_DVBSx_ErrorCode ExtSharpBS2S7HZ6306_Initialize(struct AVL_Tuner * pTuner)
{
	AVL_DVBSx_ErrorCode r;
	r = AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_slave_addr_addr, pTuner->m_uiSlaveAddress);
	r |= AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_use_internal_control_addr, 0);
	r |= AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_LPF_margin_100kHz_addr, 0);	//clean up the LPF margin for blind scan. for external driver, this must be zero.
	r |= AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_max_LPF_100kHz_addr, 320);	//set up the right LPF for blind scan to regulate the freq_step. This field should corresponding the flat response part of the LPF.
	r |= AVL_DVBSx_II2CRepeater_Initialize(pTuner->m_uiI2CBusClock_kHz, pTuner->m_pAVLChip);

	return(r);
}

AVL_DVBSx_ErrorCode ExtSharpBS2S7HZ6306_GetLockStatus(struct AVL_Tuner * pTuner )
{
	AVL_DVBSx_ErrorCode r;
	AVL_uint16 ucTemp;
	r = AVL_DVBSx_II2CRepeater_ReadData((AVL_uchar)(pTuner->m_uiSlaveAddress), (AVL_puchar)(&ucTemp), 1, pTuner->m_pAVLChip );
	if( AVL_DVBSx_EC_OK == r )
	{

		if( 0 == (ucTemp & 0x40) )
		{
			r = AVL_DVBSx_EC_Running ;
		}
	}
	return(r);
}

AVL_DVBSx_ErrorCode ExtSharpBS2S7HZ6306_Lock(struct AVL_Tuner * pTuner)
{
	AVL_DVBSx_ErrorCode r;
	struct SharpBS2S7HZ6306_Registers TunerRegs;
	struct SharpBS2S7HZ6306_TunerPara * pPara;

	TunerRegs.m_ucRegData[0] = 0;
	TunerRegs.m_ucRegData[1] = 0;
	TunerRegs.m_ucRegData[2] = 0;
	TunerRegs.m_ucRegData[3] = 0;

	r = SharpBS2S7HZ6306_SetFrequency(pTuner->m_uiFrequency_100kHz, &TunerRegs );
	if( 0 == pTuner->m_pParameters )	//use default values
	{
		r |= SharpBS2S7HZ6306_SetChargePump(PC_360_694_Sharp, &TunerRegs);
		r |= SharpBS2S7HZ6306_SetBBGain(Bbg_4_Sharp, &TunerRegs);
	}
	else		//use custom value
	{
		pPara = (struct SharpBS2S7HZ6306_TunerPara *)(pTuner->m_pParameters);
		r |= SharpBS2S7HZ6306_SetChargePump(pPara->m_ChargPump, &TunerRegs);
		r |= SharpBS2S7HZ6306_SetBBGain(pPara->m_BBGain, &TunerRegs);
	}
	r = SharpBS2S7HZ6306_CommitSetting(pTuner, &TunerRegs);
	return(r);
}
