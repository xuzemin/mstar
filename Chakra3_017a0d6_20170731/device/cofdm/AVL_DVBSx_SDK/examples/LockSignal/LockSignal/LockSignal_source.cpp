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
#include "IBSP.h"
#include "avl_dvbsx.h"
#include "IBase.h"
#include "IRx.h"
#include "ITuner.h"
#include "ExtSharpBS2S7HZ6306.h"
#include "II2C.h"
#include "IDiseqc.h"
#include "IBlindScan.h"
#include "LockSignal_source.h"

extern AVL_uchar ucPatchData [];			 //Defined in AVL6211_patch.dat.cpp.
extern struct Signal_Level  SignalLevel [47];    //Defined in SignalLevel.cpp

#define signal_symbolrate		30000000		//The symbol rate in a unit of Hz. 
#define tuner_slave_address     0xC0            //The Tuner slave address. It is the write address of the tuner device. i.e. it is 8 bits address and the last bit is the R/W flag which is zero. Although this data structure support 10 bits I2C address. The AVL chip not supports it. 
#define tuner_I2Cbus_clock      200             //The clock speed of the tuner dedicated I2C bus, in a unit of kHz.
#define tuner_freq				1000			//The frequency tuner will lock to, in a unit of MHz.
#define tuner_LPF               340             //The LPF of the tuner,in a unit of 100kHz.
#define Diseqc_Tone_Frequency   22              // The Diseqc bus speed in the unit of kHz. Normally, it should be 22kHz. 


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
	struct AVL_DVBSx_MpegInfo sMpegMode;
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
	AVL_DVBSx_IBSP_Delay(100);	  //Wait 100 ms to assure that the AVL_DVBSx chip boots up.This function should be implemented by customer.
  
	//This function should be called to verify the AVL_DVBSx chip has completed its initialization procedure.
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

	//Setup MPEG mode parameters.
    sMpegMode.m_MpegFormat = AVL_DVBSx_MPF_TS;
	sMpegMode.m_MpegMode = AVL_DVBSx_MPM_Parallel;
	sMpegMode.m_MpegClockPolarity = AVL_DVBSx_MPCP_Falling;
	
	//This function should be called after demod initialized to set MPEG mode.
	r = AVL_DVBSx_IRx_SetMpegMode(&sMpegMode,pAVLChip );
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Set MPEG output mode failed !\n");
		return (r);
	}
    
	// Enable the MPEG output (this function call has no effect for the AVL_DVBSxLG and AVL_DVBSxLGa devices)
	r = AVL_DVBSx_IRx_DriveMpegOutput(pAVLChip);

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

	//The Diseqc should be initialized if AVL_DVBSx need to supply power to LNB. This function should be called after IBase initialized to initialize the Diseqc.
	r = AVL_DVBSx_IDiseqc_Initialize(&sDiseqcPara, pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Diseqc Initialization failed !\n");
	}
	return (r);
}



AVL_DVBSx_ErrorCode LockSignal(void)
{
	struct AVL_DVBSx_Chip  AVL_DVBSxChip;
	struct AVL_Tuner Tuner;
	struct AVL_DVBSx_Channel Channel;  
	struct AVL_DVBSx_SignalInfo SignalInfo;
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	AVL_uint16 uiLockStatus=0;
	AVL_uint32 uiSNR,uiPER,uiBER;
    AVL_int16 iRFOff,uiRFSignalDBM;
	AVL_uint16 uiRFSignalLevel;
    AVL_uint32 uiTimeth; 
    AVL_uint16 uiCounter,i;

	struct AVL_DVBSx_Chip * pAVLChip = &AVL_DVBSxChip;		
	struct AVL_Tuner * pTuner =&Tuner;	

    //This function do all the initialization work.It should be called only once at the beginning.It needn��t be recalled when we want to lock a new channel.
	r=Initialize(pAVLChip,pTuner);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Initialization failed !\n");
		return (r);
	}
	printf("Initialization success !\n");

	//Change the value defined by macro and go back here when we want to lock a new channel.
	pTuner->m_uiFrequency_100kHz = tuner_freq*10;      
	pTuner->m_uiLPF_100kHz = tuner_LPF;

	//Halt CPU to improve the tuner locking speed. It's the optional operation before locking tuner.
    r=CPU_Halt(pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("CPU halt failed !\n");
		return (r);
	}

    //This function should be called after initialization to lock the tuner.
	r = pTuner->m_pLockFunc(pTuner);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Tuner lock failed !\n");
		return (r);
	}
	AVL_DVBSx_IBSP_Delay(150);		//Wait a while for tuner to lock in certain frequency.

	//This function should be called to check the lock status of the tuner.
	r = pTuner->m_pGetLockStatusFunc(pTuner);
	if (AVL_DVBSx_EC_OK != r)
	{
 		printf("Tuner test failed !\n");
		return (r);
	}
	printf("Tuner test success !\n");

	Channel.m_uiSymbolRate_Hz = signal_symbolrate;      //Change the value defined by macro when we want to lock a new channel.
	Channel.m_Flags = (CI_FLAG_IQ_NO_SWAPPED) << CI_FLAG_IQ_BIT;	//Normal IQ
	Channel.m_Flags |= (CI_FLAG_IQ_AUTO_BIT_AUTO) << CI_FLAG_IQ_AUTO_BIT;	//Enable automatic IQ swap detection
	Channel.m_Flags |= (CI_FLAG_DVBS2_UNDEF) << CI_FLAG_DVBS2_BIT;			//Enable automatic standard detection

	//This function should be called after tuner locked to lock the channel.
	r = AVL_DVBSx_IRx_LockChannel(&Channel, pAVLChip);  
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Lock channel failed !\n");
		return (r);
	}
    
	//Channel lock time increase while symbol rate decrease.Give the max waiting time for different symbolrates.
	if(signal_symbolrate<5000000)
	{
		uiTimeth=5000*2;       //The max waiting time is 5000ms,considering the IQ swapped status the time should be doubled.
	}
	else if(signal_symbolrate<10000000)
	{
        uiTimeth=600*2;        //The max waiting time is 600ms,considering the IQ swapped status the time should be doubled.
	}
	else
	{
        uiTimeth=250*2;        //The max waiting time is 250ms,considering the IQ swapped status the time should be doubled.
	} 
	uiCounter=uiTimeth/10;
	do
	{
		//This function should be called to check the lock status of the demod.
		r = AVL_DVBSx_IRx_GetLockStatus(&uiLockStatus, pAVLChip);
		if ((AVL_DVBSx_EC_OK == r)&&(1 == uiLockStatus))
		{
			break;
		}
        AVL_DVBSx_IBSP_Delay(10);    //Wait 10ms for demod to lock the channel.
	}while(--uiCounter);
	if(0==uiCounter)
	{
		printf("Time out...\nChannel unlock !\n");
		return (r);
	}
	printf("Channel locked !\nWait a few seconds to get the signal information...\n");
	
	// Before we call function AVL_DVBSx_IDVBSxRx_GetPER,function A1108_IABSRx_ResetErrorStat should be called . 
	// Do NOT call AVL_DVBSx_IDVBSxRx_ResetErrorStat before AVL1108 chip lock a signal. It may lock the AVL_DVBSx.
	r=AVL_DVBSx_IRx_ResetErrorStat(pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Reset error status failed !\n");
		return (r);
	}
	AVL_DVBSx_IBSP_Delay(5000);		//Wait a while for SNR BER/PER calculation
	//This function can be called to read back the current PER calculation result after function AVL_DVBSx_IDVBSxRx_ResetErrorStat called.
	r=AVL_DVBSx_IRx_GetPER(&uiPER, pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Get PER --- Fail !\n");
	}	
    else
	{
		printf("PER=%.9f\n",(float)(uiPER*1.0e-9));
	}

	//This function can be called to read back the current BER calculation result after function AVL_DVBSx_IDVBSxRx_ResetErrorStat called.
	r=AVL_DVBSx_IRx_GetDVBSBER(&uiBER, pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Get DVBS BER failed.  This function should only be called if the input signal is a DVBS signal.\n");
	}	
    else
	{
		printf("BER=%.9f\n",(float)(uiBER*1.0e-9));
	}

	//This function can be called to read back the current SNR estimate after the channel locked and some waiting time.
	r=AVL_DVBSx_IRx_GetSNR(&uiSNR, pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Get SNR --- Fail !\n"); 
	}
    else
	{
		printf("SNR=%.2fdb\n",(float)(uiSNR/100.0));
	}

	//This function can be called to get the RF frequency offset after the channel locked.
	r=AVL_DVBSx_IRx_GetRFOffset(&iRFOff, pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		 printf("Get RFOffset --- Fail !\n");
	}
    else
	{
		 printf("RFOffset=%.3fM\n",(float)(iRFOff/10.0));
	}
    //This function can be called to get the RF signal level after the channel locked.
	r=AVL_DVBSx_IRx_GetSignalLevel(&uiRFSignalLevel, pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Get SignalLevel --- Fail !\n");
	}
	else
	{
		for(i=0; i<47; i++)
		{
			if(uiRFSignalLevel<= SignalLevel[i].SignalLevel)   
			{
				//Calculate the corresponding DBM value.
                if((0==i)&&(uiRFSignalLevel< SignalLevel[i].SignalLevel))
				{
					printf("RFSignalLevel is too weak !");
				}
				else
				{
					uiRFSignalDBM=SignalLevel[i].SignalDBM;
				}
				break;
			} 
		}		
		printf("RFSignalLevel::%.1fdbm\n",(float)(uiRFSignalDBM/10.0));
	}  
		
	//This function can be called to get the current locked signal information after the channel locked.
	r=AVL_DVBSx_IRx_GetSignalInfo(&SignalInfo, pAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		printf("Get SignalInfo --- Fail !\n");
    }	
	else
	{
		printf("Modulation::%u\nCodeRate::%u\nRollOff::%u\nPilot::%u\n",SignalInfo.m_modulation,SignalInfo.m_coderate,SignalInfo.m_rolloff,SignalInfo.m_pilot);
	}

	return (r);
}
