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
#include "II2C.h"
#include "IDiseqc.h"
#include "Diseqc_source.h"

extern AVL_uchar ucPatchData[];			//defined in AVL6211_patch.dat.cpp

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


AVL_DVBSx_ErrorCode Initialize(struct AVL_DVBSx_Chip * pAVLChip)
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
	AVL_DVBSx_IBSP_Delay(100);	  //Wait 100 ms to assure that the AVLDVBSx chip boots up.This function should be implemented by customer.
  
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
    //Setup Diseqc parameters for Diseqc initialization.
	sDiseqcPara.m_RxTimeout = AVL_DVBSx_DRT_150ms;
	sDiseqcPara.m_RxWaveForm = AVL_DVBSx_DWM_Normal;
	sDiseqcPara.m_ToneFrequency_kHz = Diseqc_Tone_Frequency;		
	sDiseqcPara.m_TXGap = AVL_DVBSx_DTXG_15ms;
	sDiseqcPara.m_TxWaveForm = AVL_DVBSx_DWM_Normal;

	//This function should be called after IBase initialized to initialize the Diseqc.
	r = AVL_DVBSx_IDiseqc_Initialize(&sDiseqcPara, pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Diseqc Initialization failed !\n");
	}
	return (r);
}

AVL_DVBSx_ErrorCode Diseqc(void)
{
	struct AVL_DVBSx_Chip AVL_DVBSxChip;
	struct AVL_DVBSx_Diseqc_TxStatus sTxStatus;
	struct AVL_DVBSx_Diseqc_RxStatus sRxStatus;
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_uchar ucData[8];
	AVL_uchar i,i1;

	struct AVL_DVBSx_Chip * pAVLChip = &AVL_DVBSxChip;

    //This function do all the initialization work. It should be called only once at the beginning.
	r=Initialize(pAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Initialization failed !\n");
		return (r);
	}
	printf("Initialization success !\n");	
	
	//This function can be called after initialization to set the LNB pin output high.
	r = AVL_DVBSx_IDiseqc_SetLNBOut(1, pAVLChip);    
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Set LNB output high --- Fail !\n");
	}
	else
	{
 	    r = AVL_DVBSx_IDiseqc_GetLNBOut(ucData, pAVLChip);   //Get the current LNB output pin level.
        if((AVL_DVBSx_EC_OK == r) && (1 == ucData[0]))
	    {
		     printf("Set LNB output high --- Success !\n");
	    }
	    else
	    {
		     printf("Set LNB output high --- Fail !\n");
	    }
	}
		
	//This function can be called after initialization to set the LNB pin output low.
	r = AVL_DVBSx_IDiseqc_SetLNBOut(0, pAVLChip);     
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Set LNB output low --- Fail !\n");
	}
	else
	{
	    r = AVL_DVBSx_IDiseqc_GetLNBOut(ucData, pAVLChip);   //Get the current LNB output pin level.
	    if((AVL_DVBSx_EC_OK == r) && (0 == ucData[0]))
	    {
		    printf("Set LNB output low --- Success !\n");
	    }
	    else
	    {
		    printf("Set LNB output low --- Fail !\n");
	    }	
	}

	//This function can be called after initialization to start sending out continuous 22k Diseqc waveform.
	r = AVL_DVBSx_IDiseqc_StartContinuous(pAVLChip);    
	if(AVL_DVBSx_EC_OK == r)
	{
		printf("Start continuous output --- Success !\n");
	}	
	else
	{
		printf("Start continuous output --- Fail!\n");
	}

	//This function can be called to stop sending out continuous 22k Diseqc waveform.
	r = AVL_DVBSx_IDiseqc_StopContinuous(pAVLChip);    
	if(AVL_DVBSx_EC_OK == r)
	{
		printf("Stop continuous output --- Success !\n");
	}
	else
	{
		printf("Stop continuous output --- Fail!\n");
	}

	//This function can be called after initialization to send out 8 tone_1s.
	r = AVL_DVBSx_IDiseqc_SendTone(1, 8, pAVLChip);     
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Output 8 tone 1 --- Fail!\n");
	}
	else
	{
	    do
	    {
		    r =AVL_DVBSx_IDiseqc_GetTxStatus(&sTxStatus, pAVLChip);   //Get current status of the Diseqc transmitter data FIFO.
	    }
	    while(1 != sTxStatus.m_TxDone);			//Wait until operation finished.
	    if(AVL_DVBSx_EC_OK == r)
	    {
		    printf("Output 8 tone 1 --- Success !\n");
	    }
	    else
	    {
		    printf("Output 8 tone 1 --- Fail!\n");
	    }
	}

	//This function can be called after initialization to send out 8 tone_0s.
	r = AVL_DVBSx_IDiseqc_SendTone(0, 8, pAVLChip);    
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Output 8 tone 0 --- Fail!\n");
	}
	else
	{
	    do
	    {
		    r =AVL_DVBSx_IDiseqc_GetTxStatus(&sTxStatus, pAVLChip);     //Get current status of the Diseqc transmitter data FIFO.
	    }
	    while(1 != sTxStatus.m_TxDone);			//Wait until operation finished.
	    if(AVL_DVBSx_EC_OK == r)
	    {
		    printf("Output 8 tone 0 --- Success !\n");
	    }
	    else
	    {
		    printf("Output 8 tone 0 --- Fail!\n");
	    }
	}

	for(i = 0; i<8; i++)
	{
		ucData[i] = i;
	}
    //This function can be called after initialization to send out 8 modulation bytes.
	r = AVL_DVBSx_IDiseqc_SendModulationData(ucData, 8, pAVLChip);    
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Output 8 modulation bytes --- Fail!\n");
	}
	else
	{
	    do                       
	    {
		    r = AVL_DVBSx_IDiseqc_GetTxStatus(&sTxStatus, pAVLChip);        //Get current status of the Diseqc transmitter data FIFO.
	    }
	    while(1 != sTxStatus.m_TxDone);			//Wait until operation finished.
	    if(AVL_DVBSx_EC_OK == r)
	    {
		    printf("Output 8 modulation bytes: 1, 2, 3, 4, 5, 6, 7, 8 --- Success !\n");
	    }
	    else
	    {
		    printf("Output 8 modulation bytes: 1, 2, 3, 4, 5, 6, 7, 8 --- Fail!\n");
	    }
	}

	//Before receiving modulation data, we should send some request data first.
	//Read input status. 
	do
	{
		r = AVL_DVBSx_IDiseqc_GetRxStatus(&sRxStatus, pAVLChip);    //Get current status of the Diseqc receiver.
	}
	while(1 != sRxStatus.m_RxDone);       //Wait until operation finished.
	if(AVL_DVBSx_EC_OK != r)
	{
		printf("Read modulation bytes --- Fail!\n");
	}
	else
	{
	    if(0 != sRxStatus.m_RxFifoCount)      //Data received.
	    {
		    i = sRxStatus.m_RxFifoCount;
			//This function can be called to read data back from the Diseqc input FIFO when there are data received.
		    r = AVL_DVBSx_IDiseqc_ReadModulationData(ucData, &i, pAVLChip);     
            if(AVL_DVBSx_EC_OK == r)
	        {
		       printf("Received %u modulation bytes:",i);
		       for(i1=0; i1<i; i1++)
	           {
		           printf("%u,", ucData[i1]);
	           } 
		       printf("\n");
	        }
	        else
	        {
		       printf("Read modulation data --- Fail!\n");
	        }  
	    }
	    else
	    {
		    printf("There is no data in input FIFO.\n");
	    }
	}
	return (r);
}
