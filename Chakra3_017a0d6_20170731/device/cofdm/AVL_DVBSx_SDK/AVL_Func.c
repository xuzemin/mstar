/*
 *           Copyright 2007-2009 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */

#include "stdio.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IRx.h"
#include "AVL_DVBSx_SDK/BSP/IBSP.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBase.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/ITuner.h"
#include "AVL_DVBSx_SDK/addon/ExtAV2011.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IDiseqc.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBlindScan.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"
#include "AVL_DVBSx_SDK/AVL_Func.h"
#include "time.h"
#include "Board.h"
#include "AVL_DVBSx_SDK/LNB_Controler.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBlindscanAPI.h"

enum AVL_Demod_ReferenceClock_Select_t
{
    Ref_clock_4M=0,
    Ref_clock_4M5=1,
    Ref_clock_10M=2,
    Ref_clock_16M=3,
    Ref_clock_27M=4,
    Ref_clock_Enhance_4M=5,
    Ref_clock_Enhance_4M5=6,
    Ref_clock_Enhance_10M=7,
    Ref_clock_Enhance_16M=8,
    Ref_clock_Enhance_27M=9,
};

enum AVL_TunerLPF_Calculation_Flag
{
    InputLPF = 0,
    InputSymbolRate = 1,
};

struct AVL_Demod_Tuner_Configuration_t
{
    AVL_char m_ChannelId;                                               
    AVL_uint16 m_uiDemodAddress;                                       
    enum AVL_Demod_ReferenceClock_Select_t   m_DemodReferenceClk;      

    enum AVL_DVBSx_MpegMode m_TSOutPutMode;                             
    enum AVL_DVBSx_MpegClockPolarity m_TSClockPolarity;                
    enum AVL_DVBSx_MpegFormat m_TSFormat;                               
    enum AVL_DVBSx_MpegSerialPin m_SerDataPin;                         

    AVL_uint16 m_uiTunerAddress;                                        
    AVL_uint16 m_uiTuner_I2Cbus_clock;                                  
    AVL_uint16 m_uiTunerMaxLPF_100Khz;                                  
    enum AVL_TunerLPF_Calculation_Flag m_LPF_Config_flag;               
    enum AVL_DVBSx_RfagcPola m_TunerRFAGC;                              
    enum AVL_DVBSx_SpectrumPolarity m_Tuner_IQ_SpectrumMode;            
    AVL_DVBSx_ErrorCode(* m_pInitializeFunc)(struct AVL_Tuner *);       
    AVL_DVBSx_ErrorCode(* m_pGetLockStatusFunc)(struct AVL_Tuner *);    
    AVL_DVBSx_ErrorCode(* m_pLockFunc)(struct AVL_Tuner *);             
};

extern MS_BOOL bUnicable;
extern AVL_uint16 u16UniStartFreq_100kHz;
extern AVL_uint16 u16UniStopFreq_100kHz;
#define AVL_DMD_MSG(x)				x
#define AVL_DMD_ERR(x)				x

extern AVL_uchar ucPatchData [];
static	struct AVL_DVBSx_Chip  _AVL_DVBSx_Chip;
static	struct AVL_Tuner _Tuner;
static	struct AVL_DVBSx_Chip * p_gAVLChip = &_AVL_DVBSx_Chip;
static	struct AVL_Tuner * p_gTuner =&_Tuner;
struct AVL_DVBSx_BlindScanAPI_Setting BSsetting;
enum AVL_DVBSx_BlindScanAPI_Status BS_Status;
static      AVL_uint32  signal_symbolrate = 22425000;		//The symbol rate in a unit of Hz.
static     AVL_uchar  _bTuneError = 0;
static AVL_uint16 BS_Index = 0;

struct Signal_Level  SignalLevel [47]=
{
	{8285,	-922},{10224,	-902},{12538,	-882},{14890,	-862},{17343,	-842},{19767,	-822},{22178,	-802},{24618,	-782},{27006,	-762},{29106,	-742},
	{30853,	-722},{32289,	-702},{33577,	-682},{34625,	-662},{35632,	-642},{36552,	-622},{37467,	-602},{38520,	-582},{39643,	-562},{40972,	-542},
	{42351,	-522},{43659,	-502},{44812,	-482},{45811,	-462},{46703,	-442},{47501,	-422},{48331,	-402},{49116,	-382},{49894,	-362},{50684,	-342},
	{51543,	-322},{52442,	-302},{53407,	-282},{54314,	-262},{55208,	-242},{56000,	-222},{56789,	-202},{57544,	-182},{58253,	-162},{58959,	-142},
	{59657,	-122},{60404,	-102},{61181,	 -82},{62008,	 -62},{63032,	 -42},{65483,	 -22},{65535,	 -12}

};
struct AVL_Demod_Tuner_Configuration_t Board_Config =
{
	0,
	AVL_DVBSx_SA_0,
	Ref_clock_27M,
	AVL_DVBSx_MPM_Parallel,
	AVL_DVBSx_MPCP_Rising,
	AVL_DVBSx_MPF_TSP,
	AVL_DVBSx_MPSP_DATA0,
	0xC6,
	200,
	440,
	InputSymbolRate,
	AVL_DVBSx_RA_Invert,
	AVL_DVBSx_Spectrum_Invert,
	&AVL_DVBSx_ExtAV2011_Initialize,
	&AVL_DVBSx_ExtAV2011_GetLockStatus,
	&AVL_DVBSx_ExtAV2011_Lock,
};    


static AVL_DVBSx_ErrorCode AVL_DVBSx_TuneChannel(AVL_uint16 uiFreq_MHz,AVL_uint32 uiSymbolRate_Hz);
//for Send out Tone
/*****************************************************************
*  AVL_DVBSx_DiSEqC_SetToneOut
*
*  set tone
*
*  Input:
*       ucTone     1 or 0
*       ucCount    the repeat 1(0) count
*
*****************************************************************/
AVL_DVBSx_ErrorCode AVL_DiSEqC_SetToneOut(AVL_uchar ucTone)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
 	struct AVL_DVBSx_Diseqc_TxStatus sTxStatus;

	#define TONE_COUNT              	8

  	r = AVL_DVBSx_IDiseqc_SendTone(ucTone, TONE_COUNT, p_gAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		AVL_DMD_ERR(printf("\rSend tone %d --- Fail!\n",ucTone));
	}
	else
	{
	    do
	    {
			AVL_DVBSx_IBSP_Delay(1);
		    r =AVL_DVBSx_IDiseqc_GetTxStatus(&sTxStatus, p_gAVLChip);   //Get current status of the Diseqc transmitter data FIFO.
	    }
	    while(1 != sTxStatus.m_TxDone);			//Wait until operation finished.
	    if(AVL_DVBSx_EC_OK == r)
	    {
		    ;
	    }
	    else
	    {
		    AVL_DMD_ERR(printf("\rOutput tone %d --- Fail!\n",ucTone));
	    }
	}
	return (r);
}

//for DiSEqC
AVL_DVBSx_ErrorCode AVL_DiSEqC_SetLNBOut(AVL_uchar ucLow)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_uchar uiOut;

	r = AVL_DVBSx_IDiseqc_SetLNBOut(ucLow, p_gAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		AVL_DMD_ERR(printf("\rSet LNB output  --- Fail !\n"));
	}
	else
	{
 	    r = AVL_DVBSx_IDiseqc_GetLNBOut(&uiOut, p_gAVLChip);   //Get the current LNB output pin level.
     	if((AVL_DVBSx_EC_OK == r) && (ucLow == uiOut))
	    {
			;
	    }
	    else
	    {
			AVL_DMD_ERR(printf("\rLNB output not change --- Fail!\n"));
          	r = AVL_DVBSx_EC_GeneralFail;
	    }
	}
	return (r);
}

AVL_DVBSx_ErrorCode AVL_DiSEqC_GetLNBOut(AVL_puchar pucLNBOut)
{
 	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
 	AVL_uchar uiOut = 0;

 	r = AVL_DVBSx_IDiseqc_GetLNBOut(&uiOut, p_gAVLChip);   //Get the current LNB output pin level.
   	* pucLNBOut = uiOut;

 	return (r);
}

AVL_DVBSx_ErrorCode AVL_DiSEqC_Set22kOnOff(AVL_uchar uc22kOn)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;

	if(uc22kOn)
	{
       	r = AVL_DVBSx_IDiseqc_StartContinuous(p_gAVLChip);
  	}
 	else
  	{
     	r = AVL_DVBSx_IDiseqc_StopContinuous(p_gAVLChip);
  	}
	if(AVL_DVBSx_EC_OK == r)
	{
		;
	}
	else
	{
		AVL_DMD_ERR(printf("\rSet 22k On/Off --- Fail!\n"));
	}
	return (r);
}

AVL_DVBSx_ErrorCode  AVL_DiSEqC_Get22kOnOff(AVL_puchar puc22kOn)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_uchar ui22kon = 0;
	AVL_DMD_MSG(printf("\r[AVL_DiSEqC_Get22kOnOff] is call!\n"));
	///add later......
	r = AVL_DVBSx_IDiseqc_GetContinuous(&ui22kon, p_gAVLChip);   //Get the current LNB output pin level.
	* puc22kOn = ui22kon;

	return AVL_DVBSx_EC_OK;
}

AVL_DVBSx_ErrorCode AVL_DiSEqC_SetCmd(AVL_puchar pucCmd,AVL_uchar ucCmdSize)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
 	struct AVL_DVBSx_Diseqc_TxStatus sTxStatus;

  	r = AVL_DVBSx_IDiseqc_SendModulationData(pucCmd, ucCmdSize, p_gAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
		AVL_DMD_ERR(printf("\rOutput modulation bytes --- Fail!\n"));
	}
	else
	{
	    do
	    {
			AVL_DVBSx_IBSP_Delay(1);
		    r = AVL_DVBSx_IDiseqc_GetTxStatus(&sTxStatus, p_gAVLChip);        //Get current status of the Diseqc transmitter data FIFO.
	    }
		while(1 != sTxStatus.m_TxDone);			//Wait until operation finished.
	    if(AVL_DVBSx_EC_OK == r)
	    {
		    ;
	    }
	    else
	    {
		    AVL_DMD_ERR(printf("\rOutput modulation bytes --- Fail!\n"));
	    }
	}
	return (r);
}

//for channel
void AVL_Error_Dispose(AVL_DVBSx_ErrorCode r)
{
    switch(r)
	{
	    case AVL_DVBSx_EC_OK:
		    AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_OK!\n"));
			break;
	    case AVL_DVBSx_EC_GeneralFail:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_GeneralFail!\n"));
			break;
		case AVL_DVBSx_EC_I2CFail:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_I2CFail!\n"));
			break;
		case AVL_DVBSx_EC_TimeOut:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_TimeOut!\n"));
			break;
	    case AVL_DVBSx_EC_Running:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_Running!\n"));
			break;
		case AVL_DVBSx_EC_MemoryRunout:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_MemoryRunout!\n"));
			break;
		case AVL_DVBSx_EC_BSP_ERROR1:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_BSP_ERROR1!\n"));
			break;
		case AVL_DVBSx_EC_BSP_ERROR2:
			AVL_DMD_MSG(printf("\rAVL_DVBSx_EC_BSP_ERROR2!\n"));
			break;
	}
}

AVL_DVBSx_ErrorCode CPU_Halt(struct AVL_DVBSx_Chip * pAVL_DVBSx_Chip)
{
     AVL_DVBSx_ErrorCode r;
     AVL_uint16 i= 0;

     r = AVL_DVBSx_IBase_SendRxOP(OP_RX_HALT, pAVL_DVBSx_Chip );
     if(AVL_DVBSx_EC_OK == r)
     {
          while(i++<40)
          {
              r = AVL_DVBSx_IBase_GetRxOPStatus(pAVL_DVBSx_Chip);
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

AVL_DVBSx_ErrorCode AVL_SetMpegMode(AVL_uchar bParallelTS,AVL_uchar bLockChannel,MS_BOOL bInvTsClock,MS_BOOL bInpuSource)
{
       AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
       struct AVL_DVBSx_MpegInfo sMpegMode;
	#if(!ENABLE_S2_CI)
	   UNUSED(bInvTsClock);
	#endif
       //Setup MPEG mode parameters.
       sMpegMode.m_MpegFormat = AVL_DVBSx_MPF_TSP;
       if(bParallelTS)
       {
            sMpegMode.m_MpegMode = AVL_DVBSx_MPM_Parallel;
       }
       else
       {
	      sMpegMode.m_MpegMode = AVL_DVBSx_MPM_Serial;
       }

    #if TS_CLK_INV
		sMpegMode.m_MpegClockPolarity = AVL_DVBSx_MPCP_Rising;
    #else
		#if(ENABLE_S2_CI)
        if (bInvTsClock==1)//(msAPI_CI_CardDetect())
		{
			sMpegMode.m_MpegClockPolarity = AVL_DVBSx_MPCP_Rising;
        	//printf("\r\naaaaaaa ci\n");
    	}
		else
		#endif	
   		{
   			sMpegMode.m_MpegClockPolarity = AVL_DVBSx_MPCP_Falling;
         	//printf("\r\naaaaaaa no ci\n");
	    }
    #endif

	//This function should be called after demod initialized to set MPEG mode.
	r = AVL_DVBSx_IRx_SetMpegMode(&sMpegMode,p_gAVLChip );

	if(AVL_DVBSx_EC_OK != r)
	{
		//printf("Set MPEG output mode failed !\n");
		return (r);
	}
  	if(bParallelTS == 0)
   	{
     	// r = AVL_DVBSx_IDVBSxRx_SwapSerialMpegData(pAVLChip,0);
		r=AVL_DVBSx_IRx_SetMpegSerialPin(p_gAVLChip, AVL_DVBSx_MPSP_DATA7);//set bit0 ,default is bit7
		//AVL_DVBSx_IDVBSxRx_SetSerialMpegClk(pAVLChip,0x20003);
	}
	else
	{
      	r = AVL_DVBSx_IRx_EnableMpegPersistentClockMode(800,p_gAVLChip);
			 
  	}
	// Enable the MPEG output (this function call has no effect for the AVLLG and AVLLGa devices)
	if(bInpuSource)
       	r = AVL_DVBSx_IRx_DriveMpegOutput(p_gAVLChip);
	else
	   	r = AVL_DVBSx_IRx_ReleaseMpegOutput(p_gAVLChip);

	if(bLockChannel)
	{
		struct AVL_DVBSx_Channel Channel;
     	Channel.m_uiSymbolRate_Hz = signal_symbolrate;
      	Channel.m_Flags = (CI_FLAG_IQ_NO_SWAPPED) << CI_FLAG_IQ_BIT;	//Normal IQ
   		Channel.m_Flags |= (CI_FLAG_IQ_AUTO_BIT_AUTO) << CI_FLAG_IQ_AUTO_BIT;	//Enable automatic IQ swap detection
       	Channel.m_Flags |= (CI_FLAG_DVBS2_UNDEF) << CI_FLAG_DVBS2_BIT;			//Enable automatic standard detection

      	//This function should be called after tuner locked to lock the channel.
       	r = AVL_DVBSx_IRx_LockChannel(&Channel, p_gAVLChip);
    	if (AVL_DVBSx_EC_OK != r)
      	{
          	AVL_DMD_ERR(printf("\rLock channel failed!\n"));
       	}
	}

	return (r);
}
AVL_DVBSx_ErrorCode AVL_Initialize(void)
{
	#define Diseqc_Tone_Frequency   	22 

    AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
    struct AVL_DVBSx_Diseqc_Para sDiseqcPara;
    //struct AVL_DVBSx_MpegInfo sMpegMode;
    struct AVL_DVBSx_VerInfo VerInfo;

    struct AVL_Demod_Tuner_Configuration_t *pBoardConfig = &Board_Config;

    AVL_DMD_MSG(printf("------ AVL_DVBSx_Initialize ------\n"));

    p_gAVLChip->m_uiBusId=pBoardConfig->m_ChannelId;

    // This function should be called after bsp initialized to initialize the chip object.
    r = Init_AVL_DVBSx_ChipObject(p_gAVLChip, (pBoardConfig->m_uiDemodAddress)<<1);
	if( AVL_DVBSx_EC_OK != r ) 
	{
        AVL_DMD_ERR(printf("[AVL6211] Chip Object Initialization failed !\n"));
		return (r);
	}

    //This function should be called after chip object initialized to initialize the IBase,using reference clock as 10M. Make sure you pickup the right pll_conf since it may be modified in BSP.
    r = AVL_DVBSx_IBase_Initialize(&(pll_conf[pBoardConfig->m_DemodReferenceClk]), ucPatchData, p_gAVLChip);
	if( AVL_DVBSx_EC_OK != r ) 
	{
        AVL_DMD_ERR(printf("[AVL6211] IBase Initialization failed !\n"));
		return (r);
	}
	AVL_DVBSx_IBSP_Delay(100);	  //Wait 100 ms to assure that the AVL_DVBSx chip boots up.This function should be implemented by customer.
  
	//This function should be called to verify the AVL_DVBSx chip has completed its initialization procedure.
    r = AVL_DVBSx_IBase_GetStatus(p_gAVLChip);
	if( AVL_DVBSx_EC_OK != r )       
	{
        AVL_DMD_ERR(printf("[AVL6211] Booted failed !\n"));
		return (r);
	}
    AVL_DMD_MSG(printf("[AVL6211] Booted !\n"));

    //Get Chip ID, Patch version and SDK version.
    AVL_DVBSx_IBase_GetVersion(&VerInfo, p_gAVLChip);
    AVL_DMD_MSG(printf("[AVL6211] Chip Ver:%d.%d.%d  API Ver:%d.%d.%d  Patch Ver:%d.%d.%d \n",
           VerInfo.m_Chip.m_Major, VerInfo.m_Chip.m_Minor, VerInfo.m_Chip.m_Build,
           VerInfo.m_API.m_Major, VerInfo.m_API.m_Minor, VerInfo.m_API.m_Build,
           VerInfo.m_Patch.m_Major, VerInfo.m_Patch.m_Minor, VerInfo.m_Patch.m_Build));

    //This function should be called after IBase initialized to initialize the demod.
	r = AVL_DVBSx_IRx_Initialize(p_gAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
        AVL_DMD_ERR(printf("[AVL6211] Demod Initialization failed !\n"));
		return (r);
	}

	//This function should be called after demod initialized to set RF AGC polar.
	//User does not need to setup this for Sharp tuner since it is the default value. But for other tuners, user may need to do it here.
    r |= AVL_DVBSx_IRx_SetRFAGCPola(pBoardConfig->m_TunerRFAGC, p_gAVLChip);
    r |= AVL_DVBSx_IRx_DriveRFAGC(p_gAVLChip);

	if(AVL_DVBSx_EC_OK != r)
	{
        AVL_DMD_ERR(printf("[AVL6211] Set RF AGC Polar failed !\n"));
		return (r);
	}

	r = AVL_SetMpegMode(TS_PARALLEL_OUTPUT,0,0,1);

	//Setup tuner parameters for tuner initialization.
    p_gTuner->m_uiSlaveAddress = pBoardConfig->m_uiTunerAddress;
    p_gTuner->m_uiI2CBusClock_kHz = pBoardConfig->m_uiTuner_I2Cbus_clock;
    p_gTuner->m_pParameters = 0;          
    p_gTuner->m_pAVLChip = p_gAVLChip;    
    p_gTuner->m_pInitializeFunc = pBoardConfig->m_pInitializeFunc;
    p_gTuner->m_pLockFunc = pBoardConfig->m_pLockFunc;
    p_gTuner->m_pGetLockStatusFunc = pBoardConfig->m_pGetLockStatusFunc;

	//This function should be called after IBase initialized to initialize the tuner.
    r |= p_gTuner->m_pInitializeFunc(p_gTuner);
	if(AVL_DVBSx_EC_OK != r)
	{
        AVL_DMD_ERR(printf("[AVL6211] Tuner Initialization failed !\n"));
		return (r);
	}

    //Setup DiSEqC parameters for DiSEqC initialization.
	sDiseqcPara.m_RxTimeout = AVL_DVBSx_DRT_150ms;
	sDiseqcPara.m_RxWaveForm = AVL_DVBSx_DWM_Normal;
	sDiseqcPara.m_ToneFrequency_kHz = Diseqc_Tone_Frequency;		
	sDiseqcPara.m_TXGap = AVL_DVBSx_DTXG_15ms;
	sDiseqcPara.m_TxWaveForm = AVL_DVBSx_DWM_Normal;

    //The DiSEqC should be initialized if AVL_DVBSx need to supply power to LNB. This function should be called after IBase initialized to initialize the DiSEqC.
    r |= AVL_DVBSx_IDiseqc_Initialize(&sDiseqcPara, p_gAVLChip);
	if(AVL_DVBSx_EC_OK != r)
	{
        AVL_DMD_ERR(printf("[AVL6211] DiSEqC Initialization failed !\n"));
	}
	return (r);
	
}	
static AVL_DVBSx_ErrorCode AVL_Set_LPF(struct AVL_Tuner * pTuner_lpf)
{
	struct AVL_Demod_Tuner_Configuration_t *pBoardConfig = &Board_Config;

	if (pBoardConfig->m_LPF_Config_flag == InputSymbolRate)
	{
		pTuner_lpf->m_uiLPF_100kHz = pTuner_lpf->m_uiSymbolRate_Hz/(1000*100);
	}
	else
	{
		pTuner_lpf->m_uiLPF_100kHz = (pTuner_lpf->m_uiSymbolRate_Hz*75)/(1000*100*100)+40;
	}

	if (pTuner_lpf->m_uiLPF_100kHz > pBoardConfig->m_uiTunerMaxLPF_100Khz)
	{
		pTuner_lpf->m_uiLPF_100kHz = pBoardConfig->m_uiTunerMaxLPF_100Khz;
	}

	return AVL_DVBSx_EC_OK;
}
static AVL_DVBSx_ErrorCode AVL_DVBSx_TuneChannel(AVL_uint16 uiFreq_MHz,AVL_uint32 uiSymbolRate_Hz)
{
 	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
 	struct AVL_DVBSx_Channel Channel;
	printf("\r\n <AVL Dead Follow 1>...\n");
	AVL_DMD_MSG(printf("\r[AVL_DVBSx_TuneChannel] uiFreq_MHz:%d, uiSymbolRate_Hz:%d!\n",uiFreq_MHz,uiSymbolRate_Hz));
	p_gTuner->m_uiFrequency_100kHz = (uiFreq_MHz*10);
	p_gTuner->m_uiSymbolRate_Hz = uiSymbolRate_Hz;
	printf("\r\n <AVL Dead Follow 2>...\n");
	AVL_Set_LPF(p_gTuner);
	printf("\r\n <AVL Dead Follow 3>...\n");
  	signal_symbolrate = uiSymbolRate_Hz;
	printf("\r\n <AVL Dead Follow 4>...\n");
 	//r=CPU_Halt(pAVLChip);

  	//This function should be called after initialization to lock the tuner.

	r = p_gTuner->m_pLockFunc(p_gTuner);
	printf("\r\n <AVL Dead Follow 5>...\n");
  	if (AVL_DVBSx_EC_OK != r)
	{
 		AVL_DMD_ERR(printf("\rSet Tuner failed!\n"));
		return (r);
	}
	printf("\r\n <AVL Dead Follow 6>...\n");
 	AVL_DVBSx_IBSP_Delay(50);		//Wait a while for tuner to lock in certain frequency.
 	//This function should be called to check the lock status of the tuner.
   	r = p_gTuner->m_pGetLockStatusFunc(p_gTuner);
   	if (AVL_DVBSx_EC_OK != r)
   	{
		AVL_DMD_ERR(printf("[AVL6211] Tuner test failed !\n"));
       	return (r);
   	}
 	Channel.m_uiSymbolRate_Hz = signal_symbolrate;
	Channel.m_Flags = (CI_FLAG_IQ_NO_SWAPPED) << CI_FLAG_IQ_BIT;	//Normal IQ
	Channel.m_Flags |= (CI_FLAG_IQ_AUTO_BIT_AUTO) << CI_FLAG_IQ_AUTO_BIT;	//Enable automatic IQ swap detection
	Channel.m_Flags |= (CI_FLAG_DVBS2_UNDEF) << CI_FLAG_DVBS2_BIT;			//Enable automatic standard detection
	//This function should be called after tuner locked to lock the channel.
	r = AVL_DVBSx_IRx_LockChannel(&Channel, p_gAVLChip);
	printf("\r\n <AVL Dead Follow 7>...\n");
	if (AVL_DVBSx_EC_OK != r)
	{
		AVL_DMD_ERR(printf("\rLock channel failed!\n"));
		return (r);
	}
	return (r);
}

AVL_DVBSx_ErrorCode AVL_SetFrequency(AVL_uint16 uiFreq_MHz,AVL_uint32 uiSymbolRate_Hz)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;

 	_bTuneError = 0;
  	if(AVL_DVBSx_TuneChannel(uiFreq_MHz,uiSymbolRate_Hz) != AVL_DVBSx_EC_OK)
  	{
      	_bTuneError = 1;
   	}

	#if 0
   	r=AVL_DVBSx_IRx_ResetErrorStat(pAVLChip);
   	if (AVL_DVBSx_EC_OK != r)
   	{
       	printf("Reset error status failed !\n");
       	return (r);
  	}
	#endif
  	return (r);
}


AVL_DVBSx_ErrorCode AVL_GetLockStatus(void)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	AVL_uint16 uiLockStatus=0;

	r = AVL_DVBSx_IRx_GetLockStatus(&uiLockStatus, p_gAVLChip);
	if ((AVL_DVBSx_EC_OK != r)||(1 != uiLockStatus))
	{
		return (AVL_DVBSx_EC_GeneralFail);
	}

	return (AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_GetPER(float *pfPER)
{
 	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	AVL_uint32 uiPER;

	//This function can be called to read back the current PER calculation result after function AVL_DVBSx_IRx_ResetErrorStat called.
    r=AVL_DVBSx_IRx_GetPER(&uiPER, p_gAVLChip);
    if (AVL_DVBSx_EC_OK != r)
    {
     	uiPER = 0;
    	AVL_DMD_ERR(printf("\rGet PER --- Fail!\n"));
    }
    *pfPER = (float)(uiPER*1.0e-9);
    return (r);
}

AVL_DVBSx_ErrorCode AVL_GetBER(float *pfBER)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	AVL_uint32 uiBER;

    //This function can be called to read back the current BER calculation result after function AVL_DVBSx_IRxResetErrorStat called.
	r=AVL_DVBSx_IRx_GetDVBSBER(&uiBER, p_gAVLChip);
    if (AVL_DVBSx_EC_OK != r)
    {
       	uiBER = 0;
		AVL_DMD_ERR(printf("\rGet BER --- Fail!\n"));
    }
    *pfBER = (float)(uiBER*1.0e-9);
    return (r);
}

AVL_DVBSx_ErrorCode AVL_GetSNR(AVL_int32 *pfSNR)
{
     AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
     AVL_uint32 uiSNR;

    if(_bTuneError)
    {
         *pfSNR = 0;
         return AVL_DVBSx_EC_GeneralFail;
    }
    //This function can be called to read back the current SNR estimate after the channel locked and some waiting time.
    r=AVL_DVBSx_IRx_GetSNR(&uiSNR, p_gAVLChip);
    if (AVL_DVBSx_EC_OK != r)
    {
		AVL_DMD_ERR(printf("\rGet SNR --- Fail!\n"));
     	uiSNR = 0;
    }
    *pfSNR = (uiSNR/75);
    return (r);
}

AVL_DVBSx_ErrorCode AVL_GetRFOffset(AVL_int16 *piRFOff)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	AVL_int16 iRFOff;

 	//This function can be called to get the RF frequency offset after the channel locked.
	r=AVL_DVBSx_IRx_GetRFOffset(&iRFOff, p_gAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		AVL_DMD_ERR(printf("\rGet RFOffset --- Fail!\n"));
      	iRFOff = 0;
	}
  	*piRFOff = iRFOff/10;
  	return (r);
}

AVL_DVBSx_ErrorCode AVL_GetSinalLevel(AVL_int16 *piRFSignalLevel)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	AVL_uint16 uiRFSignalLevel;
	AVL_int16 uiRFSignalDBM=0;
 	AVL_int16 i;

 	//This function can be called to get the RF signal level after the channel locked.
	r=AVL_DVBSx_IRx_GetSignalLevel(&uiRFSignalLevel, p_gAVLChip);
	if (AVL_DVBSx_EC_OK != r)
	{
		AVL_DMD_ERR(printf("\rGet SignalLevel --- Fail!\n"));
      	uiRFSignalDBM = 0;
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
					AVL_DMD_MSG(printf("\rRFSignalLevel is too weak!\n"));
				}
				else
				{
					uiRFSignalDBM=SignalLevel[i].SignalDBM;   
				}
				break;
			}
		}
	}
	*piRFSignalLevel = (float)(uiRFSignalDBM/10.0);

	return (r);
}

AVL_DVBSx_ErrorCode AVL_GetSignalInfo(struct AVL_DVBSx_SignalInfo *pSignalInfo)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_SignalInfo SignalInfo;

	//This function can be called to get the current locked signal information after the channel locked.
	r=AVL_DVBSx_IRx_GetSignalInfo(&SignalInfo, p_gAVLChip);
 	*pSignalInfo = SignalInfo;

  	return (r);
}

void AVL_Display_TP_Info(struct AVL_DVBSx_Channel * pChannel, AVL_uint16 Channel_Num)
{
	AVL_uint16 i;
	AVL_DMD_MSG(printf("\n"));
	for(i=0; i<Channel_Num; i++)
	{
		AVL_DMD_MSG(printf("Ch%2d: RF: %4d SR: %5d ", i+1, (pChannel[i].m_uiFrequency_kHz/1000),(pChannel[i].m_uiSymbolRate_Hz/1000)));
		switch((pChannel[i].m_Flags & CI_FLAG_DVBS2_BIT_MASK)>>CI_FLAG_DVBS2_BIT)
		{
			case CI_FLAG_DVBS:
				 AVL_DMD_MSG(printf("  DVBS  "));
				 break;
			case CI_FLAG_DVBS2:
				 AVL_DMD_MSG(printf("  DVBS2  "));
				 break;
			case CI_FLAG_DVBS2_UNDEF:
				 AVL_DMD_MSG(printf("  Unknown  "));
				 break;
		} 
		switch((pChannel[i].m_Flags & CI_FLAG_IQ_BIT_MASK)>>CI_FLAG_IQ_BIT)
		{
			case CI_FLAG_IQ_NO_SWAPPED:
				 AVL_DMD_MSG(printf("  Normal  "));
				 break;
			case CI_FLAG_IQ_SWAPPED:
				 AVL_DMD_MSG(printf("  Invert  "));
				 break;
		}
		AVL_DMD_MSG(printf("\n"));
	}	
}

AVL_DVBSx_ErrorCode AVL_Blind_start(AVL_int16 u16StartFreq,AVL_int16 u16EndFreq)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
	struct AVL_Demod_Tuner_Configuration_t *pBoardConfig = &Board_Config;

	CPU_Halt(p_gAVLChip);
	BS_Index = 0;
	r |= AVL_DVBSx_IBlindScanAPI_Initialize(pBSsetting);//this function set the parameters blind scan process needed.


	r |= AVL_DVBSx_IBlindScanAPI_SetFreqRange(pBSsetting, u16StartFreq, u16EndFreq); //Default scan rang is from 950 to 2150. User may call this function to change scan frequency rang.

	r |= AVL_DVBSx_IBlindScanAPI_SetScanMode(pBSsetting, AVL_DVBSx_BS_Fast_Mode);
		//r |= AVL_DVBSx_IBlindScanAPI_SetScanMode(pBSsetting, AVL_DVBSx_BS_Slow_Mode);
	r |= AVL_DVBSx_IBlindScanAPI_SetSpectrumMode(pBSsetting, pBoardConfig->m_Tuner_IQ_SpectrumMode); //Default set is AVL_DVBSx_Spectrum_Normal, it must be set correctly according Board HW configuration
	r |= AVL_DVBSx_IBlindScanAPI_SetMaxLPF(pBSsetting, pBoardConfig->m_uiTunerMaxLPF_100Khz); //Set Tuner max LPF value, this value will difference according tuner type

	return(r);
}

AVL_DVBSx_ErrorCode AVL_Blind_NextFreqBlindScan(AVL_uchar* u8BlindScanEnd,MS_U8* u8Progress)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
		struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
	
		*u8BlindScanEnd = 0;
		*u8Progress = AVL_DVBSx_IBlindscanAPI_GetProgress(pBSsetting);
		AVL_DMD_MSG(printf("Progress: %3d ", *u8Progress));
		
		if(100 == *u8Progress)
		{
			*u8BlindScanEnd = 1;
			AVL_Display_TP_Info(pBSsetting->channels,pBSsetting->m_uiChannelCount);
			return (r);
		}

		r = AVL_DVBSx_IBlindScanAPI_Start(p_gAVLChip, p_gTuner, pBSsetting);
		if(AVL_DVBSx_EC_OK != r)
		{
			* u8BlindScanEnd = 1;
		}
	
		AVL_DVBSx_IBSP_Delay(10);
		return (r);
  	}


AVL_DVBSx_ErrorCode AVL_Blind_WaitCurFreqFinished(AVL_uchar* u8Progress,AVL_uchar* ucFindNum)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
	struct AVL_DVBSx_Channel * pChannel;
	
	*u8Progress = 0;
	*ucFindNum = 0;
	
	r = AVL_DVBSx_IBlindScanAPI_GetCurrentScanStatus(p_gAVLChip, pBSsetting);
	if(AVL_DVBSx_EC_OK == r)
	{		
		//r |= AVL_DVBSx_IBlindScanAPI_Adjust(p_gAVLChip, pBSsetting);this function has been called by AVL_DVBSx_IBlindScanAPI_GetCurrentScanStatus
		*u8Progress = 100;
		*ucFindNum = pBSsetting->m_uiChannelCount;
		AVL_DMD_MSG(printf("Found %d TP\n", pBSsetting->m_uiChannelCount));
		
#if 1
	while(BS_Index < pBSsetting->m_uiChannelCount)
		{
			pChannel = &pBSsetting->channels[BS_Index++];
			AVL_DMD_MSG(printf("Ch%2d: RF: %4d SR: %5d\n", BS_Index, pChannel->m_uiFrequency_kHz/1000, pChannel->m_uiSymbolRate_Hz/1000));
			//printf("Ch%2d: RF: %4d SR: %5d\n", BS_Index, pChannel->m_uiFrequency_kHz/1000, pChannel->m_uiSymbolRate_Hz/1000);
		}
		BS_Index = pBSsetting->m_uiChannelCount;
#endif
		
	}
	if(AVL_DVBSx_EC_Running == r)
	{
		AVL_DVBSx_IBSP_Delay(100);
	}
	
	return (AVL_DVBSx_EC_OK);
}


AVL_DVBSx_ErrorCode AVL_Blind_GetChannel(AVL_uint16 u16Start,AVL_uint16 *chNum,struct AVL_DVBSx_Channel *channels)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
	
	struct AVL_DVBSx_Channel * pChannel;
	AVL_uint16 i;

	AVL_DMD_MSG(printf("Star: %d TotalCount %d\n", u16Start,pBSsetting->m_uiChannelCount));

	*chNum = pBSsetting->m_uiChannelCount - u16Start;
	
	for(i= 0; i< (pBSsetting->m_uiChannelCount - u16Start); i++)
	{
		pChannel = &pBSsetting->channels[i+u16Start];
		channels[i].m_uiFrequency_kHz = pChannel->m_uiFrequency_kHz;
		channels[i].m_uiSymbolRate_Hz = pChannel->m_uiSymbolRate_Hz;
		channels[i].m_Flags = pChannel->m_Flags;
	}

 	return(r);

}

AVL_DVBSx_ErrorCode AVL_Blind_Cancel(void)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
	
	AVL_DMD_MSG(printf("\r[AVL_Blind_Cancel]is call!\n"));

	r =  AVL_DVBSx_IBlindScan_Cancel(p_gAVLChip);
	AVL_DVBSx_IBSP_Delay(200);

	AVL_DVBSx_IBlindScanAPI_Exit(p_gAVLChip,pBSsetting);
	return (r);
}


AVL_DVBSx_ErrorCode AVL_Blind_End(void)
{
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;
	struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
	
	AVL_DMD_MSG(printf("\r[AVL_Blind_End]is call!\n"));

	r = AVL_DVBSx_IBlindScanAPI_Exit(p_gAVLChip,pBSsetting);
	return (r);

}

AVL_uint32 AVL_Blind_GetCurrentFreq(void)
{
	AVL_uint16 uiFreq_MHz;

	struct AVL_DVBSx_BlindScanAPI_Setting * pBSsetting = &BSsetting;
  	uiFreq_MHz = pBSsetting->m_uiScan_Start_Freq_MHz + (AVL_DVBSx_IBlindscanAPI_GetProgress(pBSsetting)*(pBSsetting->m_uiScan_Stop_Freq_MHz - pBSsetting->m_uiScan_Start_Freq_MHz))/100;
	
	return uiFreq_MHz;
}
/*
AVL_DVBSx_ErrorCode AVL_A8293_Control(AVL_uchar Level)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
		
	r = A8293_Control(Level);

	return (r);
}
*/
void AVL_DVBSx_Tuner_Set_PD(MS_BOOL bPowerOff)
{
        printf("Javy AVL_DVBSx_Tuner_Set_PD!!!\n");
        extern void Tuner_Set_PD (AVL_uint32 val,struct AVL_Tuner * p_gTuner); 
        if(bPowerOff)
        {
            Tuner_Set_PD (1,p_gTuner);
        }
        else
        {
            Tuner_Set_PD (0,p_gTuner);
        }
}
