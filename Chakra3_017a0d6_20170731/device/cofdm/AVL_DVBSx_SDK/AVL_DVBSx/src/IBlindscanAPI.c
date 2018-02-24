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
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx_globals.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBase.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBlindScan.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBlindscanAPI.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IRx.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"
#include "AVL_DVBSx_SDK/BSP/IBSP.h"

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Initialize(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{		
	pBSsetting->m_uiScan_Start_Freq_MHz = 950;     //Default Set Blind scan start frequency
	pBSsetting->m_uiScan_Stop_Freq_MHz = 2150;     //Default Set Blind scan stop frequency
	pBSsetting->m_uiScan_Next_Freq_100KHz = 10*pBSsetting->m_uiScan_Start_Freq_MHz;

	pBSsetting->m_uiScan_Max_Symbolrate_MHz = 45;  //Set MAX symbol rate
	pBSsetting->m_uiScan_Min_Symbolrate_MHz = 2;   //Set MIN symbol rate
	
	pBSsetting->m_uiTuner_MaxLPF_100kHz = 340;

	pBSsetting->m_uiScan_Bind_No = 0;
	pBSsetting->m_uiScan_Progress_Per = 0;
	pBSsetting->m_uiScaning_Flag = 0;
	pBSsetting->m_uiChannelCount = 0;
	
	pBSsetting->m_eSpectrumMode = AVL_DVBSx_Spectrum_Normal;  //Set spectrum mode

	pBSsetting->BS_Mode = AVL_DVBSx_BS_Slow_Mode; //1: Freq Step forward is 10MHz        0: Freq Step firmware is 20.7MHz
	pBSsetting->m_uiScan_Center_Freq_Step_100KHz = 100;  //only valid when scan_algorithmic set to 1 and would be ignored when scan_algorithmic set to 0.

	return AVL_DVBSx_EC_OK;
}
AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetSpectrumMode(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting, enum AVL_DVBSx_SpectrumPolarity SpectrumMode)
{
	pBSsetting->m_eSpectrumMode = SpectrumMode;
	return AVL_DVBSx_EC_OK;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetScanMode(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting, enum AVL_DVBSx_BlindScanAPI_Mode Scan_Mode)
{
	pBSsetting->BS_Mode = Scan_Mode;
	return AVL_DVBSx_EC_OK;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetFreqRange(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting,AVL_uint16 StartFreq_MHz,AVL_uint16 EndFreq_MHz)
{
	pBSsetting->m_uiScan_Start_Freq_MHz = StartFreq_MHz;     //Change default start frequency
	pBSsetting->m_uiScan_Stop_Freq_MHz = EndFreq_MHz;        //Change default end frequency
	pBSsetting->m_uiScan_Next_Freq_100KHz = 10*pBSsetting->m_uiScan_Start_Freq_MHz;
	
	return AVL_DVBSx_EC_OK;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_SetMaxLPF(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting ,AVL_uint16 MaxLPF)
{
	pBSsetting->m_uiTuner_MaxLPF_100kHz = MaxLPF;
	
	return AVL_DVBSx_EC_OK;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Start(struct AVL_DVBSx_Chip * pAVLChip, struct AVL_Tuner * pTuner, struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanPara * pbsPara = &pBSsetting->bsPara;

	r |= AVL_DVBSx_IBase_SetFunctionalMode(pAVLChip, AVL_DVBSx_FunctMode_BlindScan);
	r |= AVL_DVBSx_IBase_SetSpectrumPolarity(pBSsetting->m_eSpectrumMode,pAVLChip); 

	if(pBSsetting->BS_Mode)
	{
		pTuner->m_uiFrequency_100kHz = 10*pBSsetting->m_uiScan_Start_Freq_MHz + 320 + (pBSsetting->m_uiScan_Bind_No) * pBSsetting->m_uiScan_Center_Freq_Step_100KHz;
		pbsPara->m_uiStartFreq_100kHz = pTuner->m_uiFrequency_100kHz - 320;
		pbsPara->m_uiStopFreq_100kHz =  pTuner->m_uiFrequency_100kHz + 320;
	}
	else
	{
		pbsPara->m_uiStartFreq_100kHz = pBSsetting->m_uiScan_Next_Freq_100KHz;
		pbsPara->m_uiStopFreq_100kHz = pBSsetting->m_uiScan_Next_Freq_100KHz + 320*2;
		pTuner->m_uiFrequency_100kHz = (pbsPara->m_uiStartFreq_100kHz + pbsPara->m_uiStopFreq_100kHz)/2;
	}

	pTuner->m_uiLPF_100kHz =  pBSsetting->m_uiTuner_MaxLPF_100kHz;
	
	r |= pTuner->m_pLockFunc(pTuner);	//Lock the tuner. 
	
	AVL_DVBSx_IBSP_Delay(50);		//wait a while for tuner to lock in certain frequency.
	
	r |= pTuner->m_pGetLockStatusFunc(pTuner);	 //Check the lock status of the tuner.
	if (AVL_DVBSx_EC_OK != r)		 
	{
		return r;
	}
			
	pbsPara->m_uiMaxSymRate_kHz = 1000*pBSsetting->m_uiScan_Max_Symbolrate_MHz;
	pbsPara->m_uiMinSymRate_kHz = 1000*pBSsetting->m_uiScan_Min_Symbolrate_MHz;
	
	r |= AVL_DVBSx_IBlindScan_Reset(pAVLChip);
	r |= AVL_DVBSx_IBlindScan_Scan(pbsPara,340, pAVLChip);
	pBSsetting->m_uiScaning_Flag = 1;
	
	return r;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_GetCurrentScanStatus(struct AVL_DVBSx_Chip * pAVLChip,struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanInfo * pbsInfo = &(pBSsetting->bsInfo);
	struct AVL_DVBSx_BlindScanPara * pbsPara = &(pBSsetting->bsPara);	
    
	r |= AVL_DVBSx_IBlindScan_GetScanStatus(pbsInfo, pAVLChip);  //Query the internal blind scan procedure information.
	

	if(100 == pbsInfo->m_uiProgress)
	{
		pBSsetting->m_uiScan_Next_Freq_100KHz = pbsInfo->m_uiNextStartFreq_100kHz;
		pBSsetting->m_uiScan_Progress_Per = AVL_min(100,((10*(pbsPara->m_uiStopFreq_100kHz - 10*pBSsetting->m_uiScan_Start_Freq_MHz))/(pBSsetting->m_uiScan_Stop_Freq_MHz - pBSsetting->m_uiScan_Start_Freq_MHz)));
		pBSsetting->m_uiScan_Bind_No++;	
		pBSsetting->m_uiScaning_Flag = 0;

		r |= AVL_DVBSx_IBlindScanAPI_Adjust(pAVLChip,pBSsetting);
		r |= AVL_DVBSx_IBase_SetFunctionalMode(pAVLChip,AVL_DVBSx_FunctMode_Demod);
	}
	if( r != AVL_DVBSx_EC_OK)
		return AVL_DVBSx_EC_GeneralFail;

	if(100 == pbsInfo->m_uiProgress)
		return AVL_DVBSx_EC_OK;
	else
		return AVL_DVBSx_EC_Running;
}


AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Adjust(struct AVL_DVBSx_Chip * pAVLChip,struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{
	
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;	
	struct AVL_DVBSx_BlindScanInfo * pbsInfo = &pBSsetting->bsInfo;
	AVL_uint16 Indext = pBSsetting->m_uiChannelCount;
	AVL_uint16 i,j,flag;
	struct AVL_DVBSx_Channel *pTemp;
	struct AVL_DVBSx_Channel *pValid;
	AVL_uint32 uiSymbolRate_Hz;
	AVL_uint32 ui_SR_offset;
	
	if(pbsInfo->m_uiChannelCount>0)
	{
		r |= AVL_DVBSx_IBlindScan_ReadChannelInfo(0, &(pbsInfo->m_uiChannelCount), pBSsetting->channels_Temp, pAVLChip);
	}

	for(i=0; i<pbsInfo->m_uiChannelCount; i++)
	{
		pTemp = &(pBSsetting->channels_Temp[i]);
		flag =0;
		for(j=0; j<pBSsetting->m_uiChannelCount; j++)
		{
			pValid = &(pBSsetting->channels[j]);
			if( (AVL_abssub(pValid->m_uiFrequency_kHz,pTemp->m_uiFrequency_kHz)*833) < AVL_min(pValid->m_uiSymbolRate_Hz,pTemp->m_uiSymbolRate_Hz) )
			{
				flag = 1;
				break;
			}				
		}

		if(0 == flag)
		{
			pBSsetting->channels[Indext].m_Flags = pTemp->m_Flags;
			pBSsetting->channels[Indext].m_uiSymbolRate_Hz = pTemp->m_uiSymbolRate_Hz;
			pBSsetting->channels[Indext].m_uiFrequency_kHz = 1000*((pTemp->m_uiFrequency_kHz+500)/1000);

			uiSymbolRate_Hz = pBSsetting->channels[Indext].m_uiSymbolRate_Hz;
			//----------------------------adjust symbol rate offset------------------------------------------------------------
			ui_SR_offset = ((uiSymbolRate_Hz%10000)>5000)?(10000-(uiSymbolRate_Hz%10000)):(uiSymbolRate_Hz%10000);
			if( ((uiSymbolRate_Hz>10000000) && (ui_SR_offset<3500)) || ((uiSymbolRate_Hz>5000000) && (ui_SR_offset<2000)) )
				uiSymbolRate_Hz = (uiSymbolRate_Hz%10000<5000)?(uiSymbolRate_Hz - ui_SR_offset):(uiSymbolRate_Hz + ui_SR_offset);

			ui_SR_offset = ((uiSymbolRate_Hz%1000)>500)?(1000-(uiSymbolRate_Hz%1000)):(uiSymbolRate_Hz%1000);
			if( (uiSymbolRate_Hz<5000000) && (ui_SR_offset< 500) )
				uiSymbolRate_Hz = (uiSymbolRate_Hz%1000<500)?(uiSymbolRate_Hz - ui_SR_offset):(uiSymbolRate_Hz + ui_SR_offset);
	
			pBSsetting->channels[Indext].m_uiSymbolRate_Hz = 1000*(uiSymbolRate_Hz/1000);
			//----------------------------------------------------------------------------------------------------------------
			Indext++;
		}
	}
	
	pBSsetting->m_uiChannelCount = Indext;
	
	return r;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindScanAPI_Exit(struct AVL_DVBSx_Chip * pAVLChip, struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanInfo * pbsInfo = &pBSsetting->bsInfo;

	if(pBSsetting->m_uiScaning_Flag == 1)
	{
		do
		{
			AVL_DVBSx_IBSP_Delay(50);			
			r |= AVL_DVBSx_IBlindScan_GetScanStatus(pbsInfo, pAVLChip);  //Query the internal blind scan procedure information.
			if(AVL_DVBSx_EC_OK !=r)
			{
				return r;			
			}
		}while(100 != pbsInfo->m_uiProgress);
		pBSsetting->m_uiScaning_Flag = 0;
	}

	r |= AVL_DVBSx_IBase_SetFunctionalMode(pAVLChip,AVL_DVBSx_FunctMode_Demod);
	AVL_DVBSx_IBSP_Delay(10);
	
	return r;
}

AVL_uint16 AVL_DVBSx_IBlindscanAPI_GetProgress(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{
	return pBSsetting->m_uiScan_Progress_Per;
}

AVL_uint16 AVL_DVBSx_IBlindscanAPI_GetTPCount(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting)
{
	return pBSsetting->m_uiChannelCount;
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBlindscanAPI_GetTP(struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting, AVL_uint16 uiStartIndex, AVL_puint16 uiNum, struct AVL_DVBSx_Channel *pChannel)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_Channel *pTemp;
	AVL_uint16 i;

	if(pBSsetting->m_uiChannelCount>=uiStartIndex)
	{
		*uiNum = AVL_min((pBSsetting->m_uiChannelCount - uiStartIndex),*uiNum);
	}
	else
	{
		return AVL_DVBSx_EC_GeneralFail;
	}
		
	for(i= 0; i< *uiNum; i++)
	{
		pTemp = &pBSsetting->channels[i+uiStartIndex];
		pChannel[i].m_uiFrequency_kHz = pTemp->m_uiFrequency_kHz;
		pChannel[i].m_uiSymbolRate_Hz = pTemp->m_uiSymbolRate_Hz;
		pChannel[i].m_Flags = pTemp->m_Flags;
	}

	return r;
}

