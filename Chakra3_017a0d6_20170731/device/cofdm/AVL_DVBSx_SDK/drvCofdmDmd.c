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

#include "AVL_Board.h"
#include "drvCofdmDmd.h" //Temp for use
#include "AVL_Func.h"
#include "debug.h"
#include "msAPI_DTVSystem.h"
#include "apiDigiTuner.h"

#if 1//def MS_DEBUG
#define DMD_ERR(_print)	     			_print
#define DMD_MSG(_print)      			_print
#else
#define DMD_ERR(_print)	     			_print
#define DMD_MSG(_print)      			_print
#endif

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#define CPU_CLOCK_FREQ 				143000000
#define DVBC_MSEC_LOOP              ( CPU_CLOCK_FREQ/1000/4 )
#define DVBC_DELAY(_loop)           { volatile MS_U32 i; for (i=0; i<(_loop)*DVBC_MSEC_LOOP; i++); }
#define COFDMDMD_STACK_SIZE        	(2048)
#define COFDMDMD_MUTEX_TIMEOUT   	(2000)

MS_BOOL bUnicable = FALSE;
AVL_uint16 u16UniStartFreq_100kHz = 0;
AVL_uint16 u16UniStopFreq_100kHz = 0;
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
//static void*                        _pTaskStack;
//static MS_S32                       _s32EventId;
static MS_BOOL 	 		bInited     = FALSE;

MS_U32 SysDelay(MS_U32 dwMs)
{
    if (bInited)
    {
        MsOS_DelayTask(dwMs);
    }
    else
    {
        DVBC_DELAY(dwMs);
    }
    return (0);
}

static void _AVL_HwReset(void)
{
    extern void MApi_Demod_HWReset(MS_BOOL bReset);
    DMD_MSG(printf("--->HW Reset for DEMOD\n"));
    MApi_Demod_HWReset(TRUE);
    SysDelay(200);//100ms
    MApi_Demod_HWReset(FALSE);
    SysDelay(200);
}

MS_BOOL MDrv_CofdmDmd_SetTsSerial(MS_BOOL bSerial,MS_BOOL bInvTsClock,MS_BOOL bInpuSource)
{
    AVL_DVBSx_ErrorCode errRet;

    errRet = AVL_SetMpegMode(!bSerial,1,bInvTsClock,bInpuSource);
    if(errRet != AVL_DVBSx_EC_OK)
    {
   		return FALSE;
    }
    return TRUE;
}

//Mstar Cofdm comman interface
MS_BOOL MDrv_CofdmDmd_Init(void)
{
    AVL_DVBSx_ErrorCode errRet;
    printf("[+]MDrv_CofdmDmd_Init\n");
    bInited = FALSE;
    printf("[+]_AVL_HWReset\n");
    _AVL_HwReset();
    printf("[-]_AVL_HWReset\n");
    errRet = AVL_Initialize();
    printf("[-]AVL_Initialize\n");
    AVL_Error_Dispose(errRet);
    bInited = TRUE;
    printf("[-]MDrv_CofdmDmd_Init\n");

    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_Open(void)
{
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_Close(void)
{
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_Reset(void)
{
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_Restart(CofdmDMD_Param *pParam)
{
    DMD_MSG(printf("\r\nu32TunerFreq = %d, u32SymbolRate = %d\n", pParam->u32TunerFreq, pParam->u32SymbolRate));
	AVL_SetFrequency(pParam->u32TunerFreq,pParam->u32SymbolRate);
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_SetMode(CofdmDMD_Mode *pMode)
{
    UNUSED(pMode);
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_TsOut(MS_BOOL bEnable)
{
    UNUSED(bEnable);
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_PowerOnOff(MS_BOOL bPowerOn)
{
    printf("MDrv_Demod_PowerOnOff!!!\n");
    extern void AVL_DVBSx_Tuner_Set_PD(MS_BOOL bPowerOff);
    if(!bPowerOn)
    {
        AVL_DVBSx_Tuner_Set_PD(TRUE);
    }
    else
    {
        AVL_DVBSx_Tuner_Set_PD(FALSE);
    }
    printf("Javy Set PowerDown!!!\n");

    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_SetBW(MS_U32 u32BW)
{
    UNUSED(u32BW);
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetBW(MS_U32 *pu32BW)
{
    UNUSED(pu32BW);
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock)
{
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
    	*pbLock = TRUE;
    }
    else
    {
     	*pbLock = FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_TPSGetLock(MS_BOOL *pbLock)
{
    // get lock
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
     	*pbLock = TRUE;
    }
    else
    {
    	*pbLock = FALSE;
    }
    return TRUE ;
}

MS_BOOL MDrv_CofdmDmd_MPEGGetLock(MS_BOOL *pbLock)
{
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
      	*pbLock = TRUE;
    }
    else
    {
    	*pbLock = FALSE;
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetSNR(MS_U32 *pu32SNR)
{
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
      	if(AVL_GetSNR((AVL_int32 *)pu32SNR) != AVL_DVBSx_EC_OK)
      	{
          	*pu32SNR = 0;
       	}
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetBER(float *pfBER)
{
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
     	if(AVL_GetBER(pfBER) != AVL_DVBSx_EC_OK)
      	{
          	*pfBER = 0;
      	}
    }
    return TRUE;

}

MS_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *ps32Signal)
{
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
     	MS_S16 s16Signallevel;
       	AVL_GetSinalLevel(&s16Signallevel);
      	*ps32Signal = s16Signallevel;
    }
    return TRUE;

}

MS_BOOL MDrv_CofdmDmd_GetRollOff(MS_U8 *pRollOff)
{
    struct AVL_DVBSx_SignalInfo SignalInfo;
    if( AVL_GetSignalInfo(&SignalInfo) == AVL_DVBSx_EC_OK)
    {
     	if(SignalInfo.m_rolloff == AVL_DVBSx_RO_35)
      	{
          	*pRollOff = 0;
      	}
     	else if(SignalInfo.m_rolloff == AVL_DVBSx_RO_35)
      	{
           	*pRollOff = 1;
      	}
     	else
     	{
         	*pRollOff = 2;
     	}
    }
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff)
{
    MS_BOOL bRet = FALSE;

    *ps16RFOff = 0;
    if( AVL_GetLockStatus() == AVL_DVBSx_EC_OK)
    {
      	if( AVL_GetRFOffset(ps16RFOff) != AVL_DVBSx_EC_OK)
       	{
          	*ps16RFOff = 0;
      	}
      	bRet = TRUE;
    }
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_GetParam(CofdmDMD_Param *pParam)
{
    UNUSED(pParam);
    return TRUE;
}

MS_BOOL MDrv_CofdmDmd_Config(MS_U8 *pRegParam)
{
    UNUSED(pRegParam);

    return TRUE;
}

//-------------------------------------------------------------------------------------------------
//blind scan
//-----------------------------------------------------------------------------------------------
MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode)
{
	MS_BOOL bRet = TRUE;
    if (bUCMode)
    {
        //DBG_DOMOD_MSB(printf("%s, UNICALBE mode on\n", __FUNCTION__));
        bUnicable = TRUE;
    }
	if(AVL_Blind_start(u16StartFreq,u16EndFreq) != AVL_DVBSx_EC_OK)
	{
        bUnicable = FALSE;
        u16UniStartFreq_100kHz = 0;
        u16UniStopFreq_100kHz = 0;
		bRet = FALSE;
	}
	return bRet;
}

//[out]:MS_BOOL  == FALSE------>scan end
MS_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress)
{
	MS_BOOL bRet = TRUE;
	MS_U8 u8End;
	if(AVL_Blind_NextFreqBlindScan(&u8End,u8Progress) != AVL_DVBSx_EC_OK)
	{
	   	bRet = FALSE;
	}
	if(u8End > 0)
	{
	   	*bBlindScanEnd = TRUE;
	}
	else
	{
	   	*bBlindScanEnd = FALSE;
	}
	return bRet;
}

//MDrv_CofdmDmd_BlindScan_WaitFinished
//wait blind scan current freq finished,not ended blind scan
MS_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MS_U8* u8Progress,MS_U8 *u8FindNum)
{
    MS_BOOL bRet = TRUE;
	if(AVL_Blind_WaitCurFreqFinished((MS_U8*)u8Progress,u8FindNum) != AVL_DVBSx_EC_OK)
	{
		bRet = FALSE;
	}
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void)
{
    MS_BOOL bRet = TRUE;
    {
      	if(AVL_Blind_Cancel() != AVL_DVBSx_EC_OK)
      	{
         	bRet = FALSE;
       	}
    }
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_End(void)
{
    MS_BOOL bRet = TRUE;
	if(AVL_Blind_End() != AVL_DVBSx_EC_OK)
 	{
      	bRet = FALSE;
  	}

    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTable)
{
    MS_BOOL bRet = TRUE;
	struct AVL_DVBSx_Channel channels[MAX_TPSOFSAT];
	MS_U16 u16ChNum = MAX_TPSOFSAT,idx=0;

	if(AVL_Blind_GetChannel(u16ReadStart,&u16ChNum,channels) != AVL_DVBSx_EC_OK)
	{
    	bRet =  FALSE;
      	*u16TPNum = 0;
 	}
  	else
  	{
    	*u16TPNum = u16ChNum;
     	for(idx = 0;idx < u16ChNum;idx++)
     	{
          	pTable[idx].u32S2Frequency = channels[idx].m_uiFrequency_kHz /1000;
        	pTable[idx].u16SymbolRate = channels[idx].m_uiSymbolRate_Hz /1000;
    	}
  	}
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MS_U32 *u32CurrentFeq)
{
    MS_BOOL bRet = TRUE;
	*u32CurrentFeq = AVL_Blind_GetCurrentFreq();
    return bRet;
}
//-------------------------------------------------------------------------------------------------
//  drvDiSEqC Function
//-------------------------------------------------------------------------------------------------
MS_BOOL MDrv_DiSEqC_SetTone(MS_BOOL bTone1)
{
  	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	MS_BOOL bRet = TRUE;

 	r = AVL_DiSEqC_SetToneOut((MS_U8)bTone1);
	if(AVL_DVBSx_EC_OK != r)
	{
		bRet = FALSE;
	}
	if(bTone1)
	{
      	DMD_MSG(printf("\r\nSet Tone1\n"));
	}
	else
	{
   		DMD_MSG(printf("\r\nSet Tone0\n"));
	}
	return bRet;
}

MS_BOOL MDrv_DiSEqC_SetLNBOut(MS_BOOL bLow)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	MS_BOOL bRet = TRUE;
	r = AVL_DiSEqC_SetLNBOut((MS_U8)bLow);
	if(AVL_DVBSx_EC_OK != r)
	{
		bRet = FALSE;
	}
	return bRet;
}

MS_BOOL MDrv_DiSEqC_GetLNBOut(MS_BOOL* bLNBOutLow)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	MS_U8 u8LNBOut =0;
	MS_BOOL bRet = TRUE;
	r = AVL_DiSEqC_GetLNBOut(&u8LNBOut);
	if(u8LNBOut)
	{
     	*bLNBOutLow = TRUE;
	}
	else
	{
   		*bLNBOutLow = FALSE;
  	}
	if(AVL_DVBSx_EC_OK != r)
	{
		bRet = FALSE;
	}
	return bRet;
}

MS_BOOL MDrv_DiSEqC_Set22kOnOff(MS_BOOL b22kOn)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	MS_U8 u822kStatus =0;
	MS_BOOL bRet = TRUE;
	r = AVL_DiSEqC_Get22kOnOff(&u822kStatus);
	if(r != AVL_DVBSx_EC_OK)
	{
   		u822kStatus = !b22kOn;
  	}

  	if(u822kStatus != b22kOn)
   	{
       	DMD_MSG(printf("\r\nb22kOn=%d\n",b22kOn));
       	r = AVL_DiSEqC_Set22kOnOff((MS_U8)b22kOn);
       	if(AVL_DVBSx_EC_OK != r)
       	{
           	bRet = FALSE;
       	}
   	}

	return bRet;
}

MS_BOOL MDrv_DiSEqC_Get22kOnOff(MS_BOOL* b22kOn)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	MS_U8 u822kStatus =0;
	MS_BOOL bRet = TRUE;
	r = AVL_DiSEqC_Get22kOnOff(&u822kStatus);
	if(u822kStatus)
	{
    	*b22kOn = TRUE;
	}
	else
	{
		*b22kOn = FALSE;
	}
	if(AVL_DVBSx_EC_OK != r)
	{
		bRet = FALSE;
	}
	return bRet;
}

MS_BOOL MDrv_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize)
{
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	MS_BOOL bRet = TRUE;
	r = AVL_DiSEqC_SetCmd(pCmd,u8CmdSize);

	if(AVL_DVBSx_EC_OK != r)
	{
		bRet = FALSE;
	}
	DMD_MSG(printf("\r\nCmdData[2] = 0x%X\n",pCmd[2]));
	DMD_MSG(printf("\r\nCmdData[3] = 0x%X\n",pCmd[3]));
	return bRet;
}

#if (SUPPORT_UNICABLE)
#define MAX_IF_FREQ  2150
#define MIN_IF_FREQ   950
#define MAX_SYM_RATE         45000
#define MIN_SYM_RATE         1
const MS_U8 u8BankMap[2][2][2] =
{
{{0, 2}, {1, 3}}, //PosA, Low/High Band, Vertical/Horizontal Polarity
{{4, 6}, {5, 7}}  //PosB, Low/High Band, Vertical/Horizontal Polarity
};
MS_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo)
{
    MS_BOOL bIsHiLOF = FALSE;
    S32 s32Freq = 0;

    //MW_DTV_FRONTEND_FUNCTION("MW_DTV_FrontEnd_DVBS::Set6(%ld,%ld,%d) \n", u32Frequency, u32SymRate, u8Polarity);
    //ASSERT(u8Polarity<=1);

    // calc Mid Freq & LNB control(22K on/off)
    if (stSatInfo->u16LoLOF == stSatInfo->u16HiLOF)
    {
        s32Freq  = u32Frequency;
        s32Freq -= stSatInfo->u16LoLOF ;
        if(s32Freq < 0)
        {
            s32Freq = -s32Freq;
        }
        bIsHiLOF = FALSE;
    }
    else // 2LOF
    {
        if(stSatInfo->u16LoLOF < MAX_C_LOF_FREQ) // c band
        {
            s32Freq  = u32Frequency;
            if(u8Polarity == 1) //H ---> use low LOF
            {
                bIsHiLOF = FALSE;
                s32Freq = abs(stSatInfo->u16LoLOF - s32Freq);
            }
            else   //V --->use high LOF
            {
                bIsHiLOF = TRUE;
                s32Freq =  abs(stSatInfo->u16HiLOF - s32Freq) ;
            }
        }
        else //Ku band
        {
            U32 u32MidFreq;
            S32 s32Offset = 0;
            s32Freq  = u32Frequency;
            u32MidFreq = abs(s32Freq - stSatInfo->u16LoLOF) ;
            s32Offset = stSatInfo->u16LoLOF + MAX_IF_FREQ - stSatInfo->u16HiLOF - MIN_IF_FREQ;
            if(s32Offset < 0)
            {
                s32Offset = 0;
            }
            else
            {
                s32Offset /= 2;
            }
            if(u32MidFreq <= (U32)(MAX_IF_FREQ - s32Offset))
            {
                bIsHiLOF = FALSE;
                s32Freq = u32MidFreq;
            }
            else
            {
                bIsHiLOF = TRUE;
                s32Freq = abs(s32Freq - stSatInfo->u16HiLOF) ;
            }
        }
    }

    if(s32Freq < MIN_IF_FREQ || s32Freq > MAX_IF_FREQ)
    {
        printf("Invalid Freq = %ld\n", s32Freq);
        s32Freq = MIN_IF_FREQ;
    }
    if(u32SymRate > MAX_SYM_RATE || u32SymRate < MIN_SYM_RATE)
    {
        printf("Invalid u32SymRate = %ld\n", u32SymRate*1000);
        u32SymRate = 1000;
    }

    {
        U16 u16TuneWord = ((s32Freq + stSatInfo->u16IFreq)/4) - 350;
        ODU_ChChg(stSatInfo->u8ChannelId, u8BankMap[0][bIsHiLOF][u8Polarity], u16TuneWord,0);

		printf("[Gaven],set();[Unicable] [(Freq = %ld + IFreq = %d)/4 - 350] = (TuneWord = %d)\n",s32Freq, stSatInfo->u16IFreq, u16TuneWord);
        printf("[Gaven],set();[Unicable] ChannelId = %d, u32SymRate = %ld, u8Polarity = %d, Bank = %d\n",stSatInfo->u8ChannelId, u32SymRate*1000, u8Polarity, u8BankMap[0][bIsHiLOF][u8Polarity]);

        AVL_SetFrequency(stSatInfo->u16IFreq, u32SymRate*1000);
    }

    return TRUE;
}
#endif

