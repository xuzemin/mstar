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




#include "stdio.h"
#include "time.h"
#include "IBSP.h"
#include "avl_dvbsx.h"
#include "IBase.h"
#include "IRx.h"
#include "ITuner.h"
#include "ExtSharpBS2S7HZ6306.h"
#include "II2C.h"
#include "IDiseqc.h"
#include "IBlindScan.h"
#include "ExternalTuner_source.h"

extern AVL_uchar ucPatchData [];			//defined in AVl6211_patch.dat.cpp

#define tuner_slave_address     0xC0        //The Tuner slave address. It is the write address of the tuner device. i.e. it is 8 bits address and the last bit is the R/W flag which is zero. Although this data structure support 10 bits I2C address. The AVLDVBSx chip not supports it. 
#define tuner_I2Cbus_clock      200         //The clock speed of the tuner dedicated I2C bus, in a unit of kHz.
#define tuner_LPF               340         //The LPF of the tuner,in a unit of 100kHz.
#define Diseqc_Tone_Frequency   22          // The Diseqc bus speed in the unit of kHz. Normally, it should be 22kHz. 
#define bs_min_symbolrate		1			//The minimum symbol rate, 1M
#define bs_max_symbolrate		45			//The maximum symbol rate, 45M
#define bs_start_freq			965			//The start rf frequency, 965M
#define bs_stop_freq			2100		//The stop rf frequency, 2100M

void AVL_DVBSx_Error_Dispose(AVL_DVBSx_ErrorCode r)
{
    switch(r)
	{
	    case AVL_DVBSx_EC_OK:
		    printf("AVL_DVBSx_EC_OK !\n");
			break;
	    case AVL_DVBSx_EC_GeneralFail:
			printf("AVL_DVBSx_EC_GeneralFail !\n");
			break;
		case AVL_DVBSx_EC_I2CFail:
			printf("AVL_DVBSx_EC_I2CFail !\n");
			break;
		case AVL_DVBSx_EC_TimeOut:
			printf("AVL_DVBSx_EC_TimeOut !\n");
			break;
	    case AVL_DVBSx_EC_Running:
			printf("AVL_DVBSx_EC_Running !\n");
			break;
		case AVL_DVBSx_EC_MemoryRunout:
			printf("AVL_DVBSx_EC_MemoryRunout !\n");
			break;
		case AVL_DVBSx_EC_BSP_ERROR1:
			printf("AVL_DVBSx_EC_BSP_ERROR1 !\n");
			break;
		case AVL_DVBSx_EC_BSP_ERROR2:
			printf("AVL_DVBSx_EC_BSP_ERROR2 !\n");
			break;
	}
}

AVL_DVBSx_ErrorCode CPU_Halt(struct AVL_DVBSx_Chip * pAVLChip)
{
     AVL_DVBSx_ErrorCode r;
     AVL_uint16 i= 0;
	 
     r = AVL_DVBSx_IBase_SendRxOP(OP_RX_HALT, pAVLChip );

     if(AVL_DVBSx_EC_OK == r)
     {
          while(i++<20)
          {
              r = AVL_DVBSx_IBase_GetRxOPStatus(pAVLChip);
              if(AVL_DVBSx_EC_OK == r)
              {
                   break;
              }
              else
              {
                   AVL_DVBSx_IBSP_Delay(10);
              }
          }
     }
	 return (r);
}

AVL_DVBSx_ErrorCode Initialize(struct AVL_DVBSx_Chip * pAVLChip,struct AVL_Tuner * pTuner)
{
    struct AVL_DVBSx_Diseqc_Para sDiseqcPara;
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;

#if 0  
	//This function should be implemented by customer.
	//This function should be called before all other functions to prepare everything for a BSP operation.
	r = AVL_DVBSx_IBSP_Initialize();
#endif
	if( AVL_DVBSx_EC_OK !=r )
	{
		printf("BSP Initialization failed !\n");
		return (r);
	}
    // This function should be called after bsp initialized to initialize the chip object.
    r = Init_AVL_DVBSx_ChipObject(pAVLChip, AVL_DVBSx_SA_0);	
	if( AVL_DVBSx_EC_OK !=r ) 
	{
		printf("Chip Object Initialization failed !\n");
		return (r);
	}
	//This function should be called after chip object initialized to initialize the IBase,using reference clock as 10M. Make sure you pickup the right pll_conf since it may be modified in BSP.
	r = AVL_DVBSx_IBase_Initialize(const_cast<AVL_DVBSx_PllConf *>(pll_conf+2), ucPatchData, pAVLChip); 
	if( AVL_DVBSx_EC_OK !=r ) 
	{
		printf("IBase Initialization failed !\n");
		return (r);
	}
	AVL_DVBSx_IBSP_Delay(100);	  //Wait 100 ms to assure that the AVLDVBsx chip boots up.This function should be implemented by customer.
  
	//This function should be called to verify the AVLDVBSx chip has completed its initialization procedure.
    r = AVL_DVBSx_IBase_GetStatus(pAVLChip);
	if( AVL_DVBSx_EC_OK != r )       
	{
		printf("Booted failed !\n");
		return (r);
	}
    printf("Booted !\n");
    //This function should be called after IBase initialized to initialize the demod.
	r = AVL_DVBSx_IRx_Initialize(pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Demod Initialization failed !\n");
		return (r);
	}
	//This function should be called after demod initialized to set RF AGC polar.
	//User does not need to setup this for Sharp tuner since it is the default value. But for other tuners, user may need to do it here.
    r = AVL_DVBSx_IRx_SetRFAGCPola(AVL_DVBSx_RA_Invert, pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Set RF AGC Polar failed !\n");
		return (r);
	}
    //Setup tuner parameters for tuner initialization.
	pTuner->m_uiSlaveAddress = tuner_slave_address;        
	pTuner->m_uiI2CBusClock_kHz = tuner_I2Cbus_clock;      	
    pTuner->m_pParameters = 0;          
    pTuner->m_pAVLChip = pAVLChip;    
	pTuner->m_pInitializeFunc = &ExtSharpBS2S7HZ6306_Initialize;     
	pTuner->m_pLockFunc = &ExtSharpBS2S7HZ6306_Lock; 
	pTuner->m_pGetLockStatusFunc = &ExtSharpBS2S7HZ6306_GetLockStatus;

	//This function should be called after IBase initialized to initialize the tuner.
	r = pTuner->m_pInitializeFunc(pTuner);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Tuner Initialization failed !\n");
		return (r);
	}
    //Setup Diseqc parameters for Diseqc initialization.
	sDiseqcPara.m_RxTimeout = AVL_DVBSx_DRT_150ms;
	sDiseqcPara.m_RxWaveForm = AVL_DVBSx_DWM_Normal;
	sDiseqcPara.m_ToneFrequency_kHz = Diseqc_Tone_Frequency;		
	sDiseqcPara.m_TXGap = AVL_DVBSx_DTXG_15ms;
	sDiseqcPara.m_TxWaveForm = AVL_DVBSx_DWM_Normal;

	//The Diseqc should be initialized if AVLDVBSx need to supply power to LNB. This function should be called after IBase initialized to initialize the Diseqc.
	r = AVL_DVBSx_IDiseqc_Initialize(&sDiseqcPara, pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Diseqc Initialization failed !\n");
	}
	return (r);
}

AVL_DVBSx_ErrorCode ExternalTuner(void)
{
	struct AVL_DVBSx_Chip  AVL_DVBSxChip;
	struct AVL_Tuner Tuner;
	struct AVL_DVBSx_BlindScanPara bsPara;
	struct AVL_DVBSx_BlindScanInfo bsInfo;
	struct AVL_DVBSx_Channel channels[256];
	AVL_uint16 uiNextStartFreq_100kHz;
	AVL_uint16 uiMaxLPF;
	AVL_char ScanFlag;
	AVL_uint16 uiChannelOff;
	AVL_uint16 uiCnt;
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	time_t timer_start, timer_middle, BS_timediff;

	struct AVL_DVBSx_Chip * pAVLChip = &AVL_DVBSxChip;		
	struct AVL_Tuner * pTuner =&Tuner;	

    //This function do all the initialization work.It should be called only once at the beginning.
	r=Initialize(pAVLChip,pTuner);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Initialization failed !\n");
		return (r);
	}
	printf("Initialization success !\n");

	//Setup blind scan parameters and start to perform blind scan.	
	bsPara.m_uiMaxSymRate_kHz = 1000*bs_max_symbolrate;
	bsPara.m_uiMinSymRate_kHz = 1000*bs_min_symbolrate;
	r = AVL_DVBSx_II2C_Read16(pAVLChip, rc_tuner_max_LPF_100kHz_addr, &uiMaxLPF);     //Get the right LPF for blind scan to regulate the freq_step.

	time(&timer_start);                         //Start to calculate time.
	printf("Start to scan ");
	uiNextStartFreq_100kHz = 10*bs_start_freq;
	ScanFlag = 1;                   
	uiChannelOff=0;                 //Init the sum of channels that blind scan find.

	// The Sharp tuner does not invert the spectrum.  For other tuners, this may have to be set to AVL_DVBSx_BS_INVERT.	
	r = AVL_DVBSx_IBlindScan_SetSpectrumInversion(pAVLChip,AVL_DVBSx_BS_INVERT); 
    if(AVL_DVBSx_EC_OK != r)
	{
		printf("Set blindscan spectrum inversion failed !\n");
		return (r);
	}
    
	//Halt CPU to improve the tuner locking speed. It's the optional operation.
    r=CPU_Halt(pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("CPU halt failed !\n");
		return (r);
	}

	r = AVL_DVBSx_IBlindScan_Reset(pAVLChip);
	while(ScanFlag)
	{
		bsPara.m_uiStartFreq_100kHz = uiNextStartFreq_100kHz;    // Give the start scan frequency.
		if(bsPara.m_uiStartFreq_100kHz >= bs_stop_freq*10)
		{
			break;			//Do not need to do scan
		}
		//Sharp tuner has a maximum 34 MHz LPF, but only 32MHz is flat.
		//The scan frequency range is 640(32MHz*2*10),unit is 100KHz.
		bsPara.m_uiStopFreq_100kHz = bsPara.m_uiStartFreq_100kHz + uiMaxLPF*2; 

		if(bsPara.m_uiStopFreq_100kHz > bs_stop_freq*10)
		{
			bsPara.m_uiStopFreq_100kHz = bs_stop_freq*10;
			ScanFlag = 0;			//This is the last scan.
		}

		//Setup the tuner before scan
		pTuner->m_uiFrequency_100kHz = (bsPara.m_uiStartFreq_100kHz + bsPara.m_uiStopFreq_100kHz)/2;  //Calculate the center frequency.
		pTuner->m_uiLPF_100kHz = tuner_LPF; 
		r = pTuner->m_pLockFunc(pTuner);   //Lock the tuner.
		if(AVL_DVBSx_EC_OK != r)
	    {
		    printf("Tuner lock failed !\n");
		    return (r);
	     }
		
		AVL_DVBSx_IBSP_Delay(150);		//wait a while for tuner to lock in certain frequency.
		r = pTuner->m_pGetLockStatusFunc(pTuner);    //Check the lock status of the tuner.
	    if (AVL_DVBSx_EC_OK != r)		 
		{
			printf("Tuner can not lock to %f MHz !!!\n", pTuner->m_uiFrequency_100kHz/10.0);
			break;
		}

		//This function should be called after tuner lock to perform a blind scan.
		AVL_DVBSx_IBase_SetFunctionalMode(pAVLChip, AVL_DVBSx_FunctMode_BlindScan);
	    r = AVL_DVBSx_IBlindScan_Scan(&bsPara,pTuner->m_uiLPF_100kHz, pAVLChip);
	    if(AVL_DVBSx_EC_OK != r)
	    {
		    printf("Blind Scan failed !\n");
			return (r);
	    }
	
	    //Monitor the blind scan progress.
	    do 
	    {
		     printf(".");
			 AVL_DVBSx_IBSP_Delay(1000);		//wait 1 second
		     r = AVL_DVBSx_IBlindScan_GetScanStatus(&bsInfo, pAVLChip);  //Query the internal blind scan procedure information.
	         if(AVL_DVBSx_EC_OK != r)
	         {
		         printf("Get scan status failed !\n");
				 return (r);
	         }
		}	
	    while(100 != bsInfo.m_uiProgress);	//100 indicates the blind scan is finished.	

	    uiNextStartFreq_100kHz = bsInfo.m_uiNextStartFreq_100kHz;
	}
	printf("\n");
    
	    //The blind scan is finished now, read out the channel information
    r = AVL_DVBSx_IBlindScan_ReadChannelInfo(0, &(bsInfo.m_uiChannelCount), channels, pAVLChip);
	    if(AVL_DVBSx_EC_OK != r)
	    {
		    printf("Read channel information failed !\n");
			return (r);
	    }
    
	time(&timer_middle);
	BS_timediff=timer_middle-timer_start;
	printf("The Blind Scan took %ds\n",BS_timediff);

	for(uiCnt=0; uiCnt<bsInfo.m_uiChannelCount; uiCnt++)
	{
		printf("Ch%u:  RF: %.3f MHz SymbolRate: %f MHz ", 
			uiCnt+1, 
			(float)(channels[uiCnt].m_uiFrequency_kHz/1000.0),
			(float)(channels[uiCnt].m_uiSymbolRate_Hz/1000000.0));

		switch((channels[uiCnt].m_Flags & CI_FLAG_DVBS2_BIT_MASK)>>CI_FLAG_DVBS2_BIT)
		{
			case CI_FLAG_DVBS:
				 printf("DVBS ");
				 break;
			case CI_FLAG_DVBS2:
				 printf("DVBS2 ");
				 break;
#if 0
			case CI_FLAG_DVBSDTV:
				 printf("DTV ");
				 break;
			case CI_FLAG_DVBSDTV_AMC:
				 printf("AMC ");
				 break;
#endif
			case CI_FLAG_DVBS2_UNDEF:
				 printf("Unknown ");
				 break;
		} 
        switch((channels[uiCnt].m_Flags & CI_FLAG_IQ_BIT_MASK)>>CI_FLAG_IQ_BIT)
		{
			case CI_FLAG_IQ_NO_SWAPPED:
				 printf("Normal\n");
				 break;
			case CI_FLAG_IQ_SWAPPED:
				 printf("Invert\n");
				 break;
		}						 
	}
	return (r);
}
