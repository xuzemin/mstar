//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>

#include "Board.h"

#if( ENABLE_S2 && (FRONTEND_DEMOD_S2_TYPE == EMBEDDED_DVBS_DEMOD) )

//#include <math.h>
#include "MsCommon.h"
#include "drvIIC.h"
#include "MsOS.h"
#include "drvDemod.h"

#include "drvDMD_INTERN_DVBS.h"

#include "drvDMD_VD_MBX.h"
#include "INTERN_DVBS.h"
#include "drvGPIO.h"
#include "apiDigiTuner.h"
#include "MApp_MenuChannel.h"
#include "SysInit.h"


extern MS_SAT_PARAM sat_info;
extern BLINDSCAN_STATUS _enBlindScanStatus;

extern BOOL MDrv_DVBS_Tuner_Initial(void);
extern BOOLEAN MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);
extern MS_BOOL MDrv_DVBS_Tuner_CheckLock(void);

#define COFDMDMD_MUTEX_TIMEOUT       (2000)
// TODO, I found the following define is also in INTERN_T2_cofdm_demodulator.c, set box team, they define this in the board define.
#define FRONTEND_DEMOD_IQ_SWAP      0

// TODO,   set box team, they define this in the board.h
#define AutoSymbol_Timeout   10000
#define FixSymbol_AutoQam_Timeout   2000
#define FixSymbol_FixQam_Timeout   2000
//------------------------------DEMOD_IQ-----------------
#define DEMOD_IQ_I_IN               0
#define DEMOD_IQ_Q_IN               1
#define DEMOD_IQ_IQ_IN              2

// TODO, set box team, they define this in the board define.
#define FRONTEND_DEMOD_IQ_TYPE      DEMOD_IQ_IQ_IN


#ifdef MS_DEBUG
#define DBG_MSB(x)  x
#else
#define DBG_MSB(x)  //x
#endif

static  MS_U16 _u16TunerCenterFreq    =0;
static  MS_U16 _u16BlindScanStartFreq =0;
static  MS_U16 _u16BlindScanEndFreq   =0;

static MS_BOOL bInited = FALSE;
static MS_S32 _s32MutexId = -1;

static MS_U32 _u32IFrequency = {5000};


static DMD_RFAGC_SSI ALPS_TUNER_RfagcSsi[] =
{
    {-15.00,    0x19},
    {-25.00,    0x31},
    {-26.00,    0x33},
    {-27.00,    0x35},
    {-28.00,    0x35},
    {-29.00,    0x36},
    {-30.00,    0x37},
    {-31.00,    0x38},
    {-32.00,    0x3A},
    {-33.00,    0x3E},
    {-34.00,    0x40},
    {-35.00,    0x41},
    {-36.00,    0x43},
    {-37.00,    0x44},
    {-38.00,    0x46},
    {-39.00,    0x47},
    {-40.00,    0x49},
    {-41.00,    0x4B},
    {-42.00,    0x4E},
    {-43.00,    0x50},
    {-44.00,    0x53},
    {-45.00,    0x56},
    {-46.00,    0x59},
    {-46.50,    0x5B},
    {-47.00,    0x5D},
    {-48.00,    0x62},
    {-49.00,    0x67},
    {-50.00,    0x6B},
    {-51.00,    0x73},
    {-52.00,    0x7A},
    {-53.00,    0x85},
    {-53.50,    0x8E},
    {-54.00,    0x98},
    {-54.10,    0x9F},
    {-54.20,    0xA4},
    {-54.30,    0xA7},
    {-54.40,    0xAC},
    {-55.00,    0xAC},
    {-55.00,    0xFF},
};

static DMD_IFAGC_SSI ALPS_TUNER_IfagcSsi_LoRef[] =
{
    {-54.30,    0x5F},
    {-54.40,    0x60},
    {-55.00,    0x63},
    {-56.00,    0x68},
    {-57.50,    0x6C},
    {-58.00,    0x70},
    {-59.00,    0x75},
    {-60.00,    0x79},
    {-61.40,    0x7D},
    {-62.00,    0x80},
    {-63.00,    0x81},
    {-64.00,    0x83},
    {-65.00,    0x84},
    {-66.00,    0x85},
    {-67.00,    0x87},
    {-68.00,    0x88},
    {-69.00,    0x89},
    {-70.00,    0x8A},
    {-71.00,    0x8C},
    {-72.00,    0x8D},
    {-73.00,    0x8F},
    {-74.00,    0x90},
    {-75.00,    0x92},
    {-76.00,    0x93},
    {-77.00,    0x95},
    {-78.00,    0x96},
    {-79.00,    0x98},
    {-80.00,    0x99},
    {-81.00,    0x9B},
    {-82.00,    0x9D},
    {-83.00,    0x9E},
    {-84.00,    0xA0},
    {-85.00,    0xA2},
    {-86.00,    0xA4},
    {-87.00,    0xA6},
    {-88.00,    0xA8},
    {-89.00,    0xAA},
    {-90.00,    0xAC},
    {-91.00,    0xAD},
    {-92.00,    0xAF},
    {-93.00,    0xB0},
    {-93.00,    0xFF},
};

static DMD_IFAGC_SSI ALPS_TUNER_IfagcSsi_HiRef[] =
{
    {-54.30,    0x5F},
    {-54.40,    0x60},
    {-55.00,    0x63},
    {-56.00,    0x68},
    {-57.50,    0x6C},
    {-58.00,    0x70},
    {-59.00,    0x75},
    {-60.00,    0x79},
    {-61.40,    0x7D},
    {-62.00,    0x80},
    {-63.00,    0x81},
    {-64.00,    0x83},
    {-65.00,    0x84},
    {-66.00,    0x85},
    {-67.00,    0x87},
    {-68.00,    0x88},
    {-69.00,    0x89},
    {-70.00,    0x8A},
    {-71.00,    0x8C},
    {-72.00,    0x8D},
    {-73.00,    0x8F},
    {-74.00,    0x90},
    {-75.00,    0x92},
    {-76.00,    0x93},
    {-77.00,    0x95},
    {-78.00,    0x96},
    {-79.00,    0x98},
    {-80.00,    0x99},
    {-81.00,    0x9B},
    {-82.00,    0x9D},
    {-83.00,    0x9E},
    {-84.00,    0xA0},
    {-85.00,    0xA2},
    {-86.00,    0xA4},
    {-87.00,    0xA6},
    {-88.00,    0xA8},
    {-89.00,    0xAA},
    {-90.00,    0xAC},
    {-91.00,    0xAD},
    {-92.00,    0xAF},
    {-93.00,    0xB0},
    {-93.00,    0xFF},
};

static DMD_IFAGC_ERR ALPS_TUNER_IfagcErr_LoRef[] =
{
    {0.00,        0x0A},
    {0.00,        0xFF},

};

static DMD_IFAGC_ERR ALPS_TUNER_IfagcErr_HiRef[] =
{
    {0.00,        0x2D},
    {0.00,        0xFF},        // stopper
};

static DMD_SQI_CN_NORDIGP1 SqiCnNordigP1[] =
{
    {_QPSK,  _CR1Y2, 5.1 },
    {_QPSK,  _CR2Y3, 6.9 },
    {_QPSK,  _CR3Y4, 7.9 },
    {_QPSK,  _CR5Y6, 8.9 },
    {_QPSK,  _CR7Y8, 9.7 },
    {_16QAM, _CR1Y2, 10.8},
    {_16QAM, _CR2Y3, 13.1},
    {_16QAM, _CR3Y4, 12.2},
    {_16QAM, _CR5Y6, 15.6},
    {_16QAM, _CR7Y8, 16.0},
    {_64QAM, _CR1Y2, 16.5},
    {_64QAM, _CR2Y3, 16.3},
    {_64QAM, _CR3Y4, 17.8},
    {_64QAM, _CR3Y4, 21.2},
    {_64QAM, _CR5Y6, 21.6},
    {_64QAM, _CR7Y8, 22.5},
};

MS_BOOL DVBS_Intern_Exit(void)
{
     MDrv_DMD_DVBS_SetPowerState(E_POWER_SUSPEND);
	 return TRUE;
}


MS_BOOL DVBS_Intern_Demod_Init(void)
{
    DMD_DVBS_InitData sDMD_DVBS_InitData;
    MS_BOOL ret;
    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    if (_s32MutexId < 0)
    {
        _s32MutexId = MsOS_CreateMutex(E_MSOS_FIFO, "OfDmd_Mutex", MSOS_PROCESS_SHARED);

        if (_s32MutexId < 0)
        {
            MDrv_Sys_StopCpu(1);;
            return FALSE;
        }

    }

    MDrv_SYS_DMD_VD_MBX_Init();

    static MS_U8 u8DMD_DVBS_InitExt[]={
       4, // version
       0, // reserved
       0x15, // TS_CLK
       1, // RFAGC tristate control default value, 1:trisate 0:non-tristate,never modify unless you know the meaning
       (MS_U8)(36167>>24), // IF Frequency
       (MS_U8)(36167>>16),
       (MS_U8)(36167>>8),
       (MS_U8)(36167>>0),
       (MS_U8)(24000>>24), // FS Frequency
       (MS_U8)(24000>>16),
       (MS_U8)(24000>>8),
       (MS_U8)(24000>>0),
       FRONTEND_DEMOD_IQ_SWAP, // IQ Swap
       FRONTEND_DEMOD_IQ_TYPE,//0, // u8ADCIQMode : 0=I path, 1=Q path, 2=both IQ
       0, // u8PadSel : 0=Normal, 1=analog pad
       0, // bPGAEnable : 0=disable, 1=enable
       5, // u8PGAGain : default 5
       (MS_U8)(AutoSymbol_Timeout>>8), // AutoSymbol_Timeout  10000ms~
       (MS_U8)(AutoSymbol_Timeout>>0),
       (MS_U8)(FixSymbol_AutoQam_Timeout>>8), // FixSymbol_AutoQam_Timeout 2000ms~
       (MS_U8)(FixSymbol_AutoQam_Timeout>>0),
       (MS_U8)(FixSymbol_FixQam_Timeout>>8), // FixSymbol_FixQam_Timeout  2000ms~
       (MS_U8)(FixSymbol_FixQam_Timeout>>0),
       };                // tuner parameter

    // tuner parameter
    sDMD_DVBS_InitData.u8SarChannel=0xFF; // 0xFF means un-connected
    sDMD_DVBS_InitData.pTuner_RfagcSsi=ALPS_TUNER_RfagcSsi;
    sDMD_DVBS_InitData.u16Tuner_RfagcSsi_Size=sizeof(ALPS_TUNER_RfagcSsi)/sizeof(DMD_RFAGC_SSI);
    sDMD_DVBS_InitData.pTuner_IfagcSsi_LoRef=ALPS_TUNER_IfagcSsi_LoRef;
    sDMD_DVBS_InitData.u16Tuner_IfagcSsi_LoRef_Size=sizeof(ALPS_TUNER_IfagcSsi_LoRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBS_InitData.pTuner_IfagcSsi_HiRef=ALPS_TUNER_IfagcSsi_HiRef;
    sDMD_DVBS_InitData.u16Tuner_IfagcSsi_HiRef_Size=sizeof(ALPS_TUNER_IfagcSsi_HiRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBS_InitData.pTuner_IfagcErr_LoRef=ALPS_TUNER_IfagcErr_LoRef;
    sDMD_DVBS_InitData.u16Tuner_IfagcErr_LoRef_Size=sizeof(ALPS_TUNER_IfagcErr_LoRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBS_InitData.pTuner_IfagcErr_HiRef=ALPS_TUNER_IfagcErr_HiRef;
    sDMD_DVBS_InitData.u16Tuner_IfagcErr_HiRef_Size=sizeof(ALPS_TUNER_IfagcErr_HiRef)/sizeof(DMD_IFAGC_SSI);
    sDMD_DVBS_InitData.pSqiCnNordigP1=SqiCnNordigP1;
    sDMD_DVBS_InitData.u16SqiCnNordigP1_Size=sizeof(SqiCnNordigP1)/sizeof(DMD_SQI_CN_NORDIGP1);

    // register init
    sDMD_DVBS_InitData.u8DMD_DVBS_DSPRegInitExt=NULL;
    sDMD_DVBS_InitData.u8DMD_DVBS_DSPRegInitSize=0;
    sDMD_DVBS_InitData.u8DMD_DVBS_InitExt=u8DMD_DVBS_InitExt;

    ret = MDrv_DMD_DVBS_Init(&sDMD_DVBS_InitData, sizeof(sDMD_DVBS_InitData)); // _UTOPIA
    if(ret == TRUE)
    {
        bInited = TRUE;
    }

    MDrv_DVBS_Tuner_Initial();
    return ret;
}


MS_BOOL MDrv_CofdmDmd_GetRFOffset(MS_S16 *ps16RFOff)
{
    float pFreqOffset;
    MS_BOOL bRet=TRUE;

    DBG_MSB(printf("INTERDVBS Begin.... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    bRet = MDrv_DMD_DVBS_Get_FreqOffset(&pFreqOffset, 0);
    *ps16RFOff = (int)pFreqOffset;
    DBG_MSB(printf("INTERDVBS ps16RFOff=%d\n",*ps16RFOff));
    DBG_MSB(printf("INTERDVBS End.... Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
    return bRet;
}

#define INTER_TUNER_WAIT_TIMEOUT    (50)
MS_BOOL  DVBS_Intern_SetFrequency(MS_U16 u16CenterFreqMHz, MS_U32 u32SymbolRate_Ks)
{
    MS_BOOL bRet=TRUE;
    MS_U16 u16LockCount;

    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, u16CenterFreqMHz=%d\n",__FUNCTION__,u16CenterFreqMHz));

    bRet&=MDrv_DVBS_Tuner_SetFreq(u16CenterFreqMHz, u32SymbolRate_Ks);
    if (bRet==FALSE)
        return bRet;

    u16LockCount=0;
    do
    {
        bRet=TRUE;
        bRet&=MDrv_DVBS_Tuner_CheckLock();
        MsOS_DelayTask(1);
        u16LockCount++;
    }while((bRet==FALSE) && (u16LockCount<INTER_TUNER_WAIT_TIMEOUT)) ;

    if (bRet==TRUE)
    {
        DBG_MSB(printf("Tuner PLL Lock\n"));
    }
    else
    {
        DBG_MSB(printf("Tuner PLL Unlock\n"));
    }
    DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_Start(MS_U16 u16StartFreq,MS_U16 u16EndFreq,MS_BOOL bUCMode)
{
    MS_BOOL bRet=0;
    _u16BlindScanStartFreq=u16StartFreq;
    _u16BlindScanEndFreq=u16EndFreq;
    _u16TunerCenterFreq=0;

    DBG_MSB(printf("INTERDVBS Begin.... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
	DBG_MSB(printf("  u16StartFreq=%d, u16EndFreq=%d\n", u16StartFreq,u16EndFreq));
    UNUSED(bUCMode);
    bRet = MDrv_DMD_DVBS_BlindScan_Start(u16StartFreq,u16EndFreq);
    DBG_MSB(printf("INTERDVBS End.... Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
	return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress)
{
    MS_BOOL bRet=0;
	MS_U16 u16TunerCenterFreq;
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));

    MDrv_DMD_DVBS_BlindScan_GetTunerFreq(&u16TunerCenterFreq);
	_u16TunerCenterFreq = u16TunerCenterFreq;
    DBG_MSB(printf("Get MDrv_CofdmDmd_BlindScan_NextFreq u16TunerCenterFreq=%d\n", u16TunerCenterFreq));


	if ((sat_info.u16LoLOF == sat_info.u16HiLOF) || (sat_info.u16LoLOF < MAX_C_LOF_FREQ)) // C Band
	{
		if (_enBlindScanStatus == BLINDSCAN_H_LoLOF)
		{
			*u8Progress = (U8)(((_u16TunerCenterFreq - _u16BlindScanStartFreq)*50)/(_u16BlindScanEndFreq-_u16BlindScanStartFreq));
		}
		else
		{
			*u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*50)/(_u16BlindScanEndFreq-_u16BlindScanStartFreq)) + 50);
		}
	}
	else //KU Band
	{
		switch (_enBlindScanStatus)
		{
			case BLINDSCAN_H_LoLOF:
				*u8Progress = (U8)(((_u16TunerCenterFreq - _u16BlindScanStartFreq)*25)/(_u16BlindScanEndFreq-_u16BlindScanStartFreq));
				break;
			case BLINDSCAN_V_LoLOF:
				*u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*25)/(_u16BlindScanEndFreq-_u16BlindScanStartFreq)) + 25);
				break;
			case BLINDSCAN_H_HiLOF:
				*u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*25)/(_u16BlindScanEndFreq-_u16BlindScanStartFreq)) + 50);
				break;
			case BLINDSCAN_V_HiLOF:
				*u8Progress = (U8)((((_u16TunerCenterFreq - _u16BlindScanStartFreq)*25)/(_u16BlindScanEndFreq-_u16BlindScanStartFreq)) + 75);
				break;
			default:
				*u8Progress = 0;
				break;
		}
	}
    DVBS_Intern_SetFrequency(u16TunerCenterFreq,44000);
    bRet = MDrv_DMD_DVBS_BlindScan_NextFreq(bBlindScanEnd);
    DBG_MSB(printf("INTERDVBS .End... Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
    DBG_MSB(printf("INTERDVBS .End... Funs=%s, line=%d, bBlindScanEnd=%d\n",__FUNCTION__,__LINE__,*bBlindScanEnd));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(MS_U8* u8Progress,MS_U8 *u8FindNum)
{
#if 0// Testing code
	*u8Progress = 100;
	*u8FindNum = 1;
	return 1;
#endif
    MS_BOOL bRet=0;
    DBG_MSB(printf("INTERDVBS Begin.... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    bRet = MDrv_DMD_DVBS_BlindScan_WaitCurFreqFinished(u8Progress,u8FindNum);
    DBG_MSB(printf("INTERDVBS .... Funs=%s, u8Progress=%d, u8FindNum=%d\n",__FUNCTION__,*u8Progress,*u8FindNum));
    DBG_MSB(printf("INTERDVBS End  .... Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
    return bRet;
}

MS_BOOL MDrv_CofdmDmd_BlindScan_Cancel(void)
{
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    _u16TunerCenterFreq = 0;
    return MDrv_DMD_DVBS_BlindScan_Cancel();
}

MS_BOOL MDrv_CofdmDmd_BlindScan_End(void)
{
    MS_BOOL bRet=0;
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
 	bRet = MDrv_DMD_DVBS_BlindScan_End();
    DBG_MSB(printf("INTERDVBS ..End.. Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
    return bRet;
}
MS_BOOL MDrv_CofdmDmd_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTable)
{
    MS_BOOL bRet=0;
    MS_U16  u16TableIndex;
    HAL_DEMOD_MS_FE_CARRIER_PARAM pTableFromDemod;

#if 0 // Testing code
	*u16TPNum=1;
	pTable[0].u32S2Frequency = 11050;
	pTable[0].u16SymbolRate  = 27500;
	return 1;
#endif
    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    bRet = MDrv_DMD_DVBS_BlindScan_GetChannel(u16ReadStart,u16TPNum,&pTableFromDemod);
    if (bRet)
	{
      for(u16TableIndex = 0; u16TableIndex < (*u16TPNum); u16TableIndex++)
      {
        pTable[u16TableIndex].u32S2Frequency =  pTableFromDemod.u32Frequency;
        pTable[u16TableIndex].u16SymbolRate  =  pTableFromDemod.SatParam.u32SymbolRate;
		DBG_MSB(printf("MDrv_CofdmDmd_BlindScan_GetChannel Freq:%d SymbolRate:%d\n", pTable[u16TableIndex].u32S2Frequency, pTable[u16TableIndex].u16SymbolRate));
      }
	}
	else
	{
        DBG_MSB(printf("GetChannel return Error!\n"));
	}
    DBG_MSB(printf("INTERDVBS ..End.. Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
    return bRet;
}
MS_BOOL MDrv_CofdmDmd_BlindScan_GetCurrentFreq(MS_U32 *u32CurrentFeq)
{
    MS_BOOL bRet=0;
    DBG_MSB(printf("INTERDVBS ..Begin Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    bRet = MDrv_DMD_DVBS_BlindScan_GetCurrentFreq(u32CurrentFeq);
	DBG_MSB(printf(" u32CurrentFeq=%d\n", u32CurrentFeq));
    DBG_MSB(printf("INTERDVBS ..End.. Funs=%s, line=%d, bRet=%d\n",__FUNCTION__,__LINE__,bRet));
	return bRet;
}
MS_BOOL MDrv_DiSEqC_SetTone(MS_BOOL bTone1)
{
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    return MDrv_DMD_DVBS_DiSEqC_SetTone(bTone1);
}

MS_BOOL MDrv_DiSEqC_SetLNBOut(MS_BOOL bLow)
{
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    return MDrv_DMD_DVBS_DiSEqC_SetLNBOut(bLow);
}

MS_BOOL MDrv_DiSEqC_Set22kOnOff(MS_BOOL b22kOn)
{
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    return MDrv_DMD_DVBS_DiSEqC_Set22kOnOff(b22kOn);

}
MS_BOOL MDrv_DiSEqC_Get22kOnOff(MS_BOOL* b22kOn)
{
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    return MDrv_DMD_DVBS_DiSEqC_Get22kOnOff(b22kOn);
}

MS_BOOL MDrv_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize)
{
    DBG_MSB(printf("INTERDVBS .... Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    #if (CHIP_FAMILY_MARLON == CHIP_FAMILY_TYPE)
    return MDrv_DMD_DVBS_Customized_DiSEqC_SendCmd(pCmd, u8CmdSize);
    #else
    return MDrv_DMD_DVBS_DiSEqC_SendCmd(pCmd, u8CmdSize);
    #endif
}



MS_BOOL MDrv_CofdmDmd_GetLock(MS_BOOL *pbLock)
{
    DMD_DVBS_LOCK_STATUS LockStatus;

    *pbLock = FALSE;
    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    if (MsOS_ObtainMutex(_s32MutexId, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        DBG_MSB(printf("%s: Obtain mutex failed.\n", __FUNCTION__));
        DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d return FALSE\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
	if(bInited == FALSE)
    {
        MsOS_ReleaseMutex(_s32MutexId);
        DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d return FALSE\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
    if(MDrv_DMD_DVBS_GetLock(DMD_DVBS_GETLOCK, &LockStatus) != TRUE)
    {
        MsOS_ReleaseMutex(_s32MutexId);
        DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d return FALSE\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
	switch (LockStatus)
    {
        case DMD_DVBS_LOCK:
            *pbLock = TRUE;
            break;
        case DMD_DVBS_CHECKEND:
            *pbLock = FALSE;
            break;
        case DMD_DVBS_UNLOCK:
            *pbLock = FALSE;
            break;
        case DMD_DVBS_CHECKING:
        default:
            *pbLock = FALSE;
            break;
    }

    MsOS_ReleaseMutex(_s32MutexId);
    DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d return TRUE for lock=%d\n",__FUNCTION__,__LINE__,*pbLock));
    return TRUE;
}
MS_BOOL MDrv_CofdmDmd_GetSNR(MS_U32 *pu32SNR)
{
    MS_BOOL ret;
    float SNRValue;

    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    if (MsOS_ObtainMutex(_s32MutexId, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        DBG_MSB(printf("%s: Obtain mutex failed.\n", __FUNCTION__));
	    DBG_MSB(printf("INTERDVBS ..End. Funs=%s, line=%d, return FALSE\n",__FUNCTION__,__LINE__));
        return FALSE;
    }

    if(bInited == FALSE)
    {
        *pu32SNR = 0;
        MsOS_ReleaseMutex(_s32MutexId);
	    DBG_MSB(printf("INTERDVBS ..End. Funs=%s, line=%d, return FALSE\n",__FUNCTION__,__LINE__));
        return FALSE;
    }

    ret = MDrv_DMD_DVBS_GetSNR(&SNRValue);
    *pu32SNR = (MS_U32) SNRValue;
    MsOS_ReleaseMutex(_s32MutexId);
    DBG_MSB(printf("INTERDVBS ..End. Funs=%s, ret=%d, SNR=%ld\n",__FUNCTION__,ret,*pu32SNR));
    return ret;
}

MS_BOOL MDrv_CofdmDmd_GetPWR(MS_S32 *ps32Signal)
{
    MS_BOOL ret;
    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    if (MsOS_ObtainMutex(_s32MutexId, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        DBG_MSB(printf("%s: Obtain mutex failed.\n", __FUNCTION__));
        return FALSE;
    }

    if(bInited == FALSE)
    {
        *ps32Signal = 0;
        MsOS_ReleaseMutex(_s32MutexId);
        return FALSE;
    }
    ret = MDrv_DMD_DVBS_GetSignalStrength((MS_U16*)ps32Signal);
    MsOS_ReleaseMutex(_s32MutexId);
    DBG_MSB(printf("INTERDVBS ..End. Funs=%s, line=%d, ps32Signal=%lx\n",__FUNCTION__,__LINE__,*ps32Signal));
    return ret;
}

MS_BOOL MDrv_DVBS_Demod_GetParam(DEMOD_MS_FE_CARRIER_PARAM* pParam)
{
    DMD_DVBS_MODULATION_TYPE QAMMode;
    MS_U32 u32SymbolRate;
    float FreqOff;

    DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));

    if (MsOS_ObtainMutex(_s32MutexId, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
    {
        DBG_MSB(printf("%s: Obtain mutex failed.\n", __FUNCTION__));
        return FALSE;
    }

    if(bInited == FALSE)
    {
        MsOS_ReleaseMutex(_s32MutexId);
        return FALSE;
    }

    if(FALSE == MDrv_DMD_DVBS_GetStatus(&QAMMode, &u32SymbolRate, &FreqOff))
    {
        MsOS_ReleaseMutex(_s32MutexId);
        return FALSE;
    }

    switch (QAMMode)
    {
        case DMD_DVBS_QPSK:
            pParam->SatParam.eConstellation =  DEMOD_SAT_QPSK;
            break;
        case DMD_DVBS_8PSK:
            pParam->SatParam.eConstellation =  DEMOD_SAT_8PSK;
            break;
        default:
            pParam->SatParam.eConstellation =  DEMOD_SAT_QPSK;
            break;
    }
    pParam->SatParam.u32SymbolRate = (MS_U16)u32SymbolRate;
    pParam->SatParam.s16FreqOffset = FreqOff;
    MsOS_ReleaseMutex(_s32MutexId);
    DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
    return TRUE;
}


MS_BOOL MDrv_CofdmDmd_Restart(CofdmDMD_Param* pParam)
{
	DMD_DVBS_MODULATION_TYPE eModulationType = DMD_DVBS_QPSK;
	// static DMD_DVBS_MODULATION_TYPE ePreModulationType =  DMD_DVBS_QPSK;
	// static MS_U16 u16PreSymbolRate = 0;

	DBG_MSB(printf("INTERDVBS ..Begin.. Funs=%s, line=%d, Frequncy=%ld\n",__FUNCTION__,__LINE__,pParam->u32TunerFreq));
	DVBS_Intern_SetFrequency(pParam->u32TunerFreq,(pParam->u32SymbolRate/1000));
	if (MsOS_ObtainMutex(_s32MutexId, COFDMDMD_MUTEX_TIMEOUT) == FALSE)
	{
		printf("%s: Obtain mutex failed.\n", __FUNCTION__);
		return FALSE;
	}

	if(bInited == FALSE)
	{
		MsOS_ReleaseMutex(_s32MutexId);
		return FALSE;
	}
	// TODO, in Set top box code, the following line is exist, but I don't know how to implement in this?
	/*
	switch(pParam->SatParam.eConstellation)
	{
		case DEMOD_SAT_QPSK:
			eModulationType = DMD_DVBS_QPSK;
			break;
		case DEMOD_SAT_8PSK:
			eModulationType = DMD_DVBS_8PSK;
			break;
		default:
			eModulationType = DMD_DVBS_QPSK;
			break;
	}
	*/
	//ePreModulationType = eModulationType;

#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) // Marlon demod driver symbol rate parameter is Hz
	if(FALSE == MDrv_DMD_DVBS_SetConfig(pParam->u32SymbolRate, eModulationType, _u32IFrequency, FRONTEND_DEMOD_IQ_SWAP, FALSE))
#else
	MS_U16 u16PreSymbolRate = pParam->u32SymbolRate/1000;

	DBG_MSB(printf("INTERDVBS .  Funs=%s, line=%d u16PreSymbolRate=%ld\n",__FUNCTION__,__LINE__,u16PreSymbolRate));

	if(FALSE == MDrv_DMD_DVBS_SetConfig(u16PreSymbolRate, eModulationType, _u32IFrequency, FRONTEND_DEMOD_IQ_SWAP, FALSE))
#endif
	{
		printf("MDrv_DMD_DVBS_SetConfig Fail \n");
		MsOS_ReleaseMutex(_s32MutexId);
		return FALSE;
	}
	DBG_MSB(printf("INTERDVBS .  Funs=%s, line=%d\n",__FUNCTION__,__LINE__));
	DBG_MSB(printf("INTERDVBS ..END.. Funs=%s, line=%d, eModulationType=%d\n",__FUNCTION__,__LINE__,eModulationType));
	MsOS_ReleaseMutex(_s32MutexId);
	return TRUE;
}

#if (SUPPORT_UNICABLE)
#define MAX_IF_FREQ  			2150
#define MIN_IF_FREQ   			950
#define MAX_SYM_RATE         	45000
#define MIN_SYM_RATE         	1
const MS_U8 u8BankMap[2][2][2] =
{
  //     {{0, 2}, {1, 3}}, //PosA, Low/High Band, Vertical/Horizontal Polarity
	{{2, 0}, {3, 1}},//PosA, Low/High Band, Horizontal/Vertical Polarity
	{{4, 6}, {5, 7}}  //PosB, Low/High Band, Vertical/Horizontal Polarity
};
MS_BOOL FrontEnd_DVBS2_Set(MS_U32 u32Frequency, MS_U32 u32SymRate, MS_U8 u8Polarity , MS_SAT_PARAM *stSatInfo)
{
    MS_BOOL bIsHiLOF = FALSE;
    S32 s32Freq = 0;
    CofdmDMD_Param unidmdpara;
    //MW_DTV_FRONTEND_FUNCTION("MW_DTV_FrontEnd_DVBS::Set6(%ld,%ld,%d) \n", u32Frequency, u32SymRate, u8Polarity);
    //ASSERT(u8Polarity<=1);
	//u32Frequency = 11053;
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

		printf("\r\n (%s,%d),FrontEnd_DVBS2_Set [%d] u16SymbolRate [%d], u16TuneWord = %ld\n",__FUNCTION__,__LINE__,u32Frequency, u32SymRate,u16TuneWord);
        ODU_ChChg(stSatInfo->u8ChannelId, u8BankMap[0][bIsHiLOF][u8Polarity], u16TuneWord,0);

		printf("[Gaven],set();[Unicable] [(Freq = %ld + IFreq = %d)/4 - 350] = (TuneWord = %d)\n",s32Freq, stSatInfo->u16IFreq, u16TuneWord);
		printf("[Gaven],set();[Unicable] ChannelId = %d, u32SymRate = %ld, u8Polarity = %d, Bank = %d\n",stSatInfo->u8ChannelId, u32SymRate*1000, u8Polarity, u8BankMap[0][bIsHiLOF][u8Polarity]);
		unidmdpara.u32TunerFreq=stSatInfo->u16IFreq;
		unidmdpara.u32SymbolRate=u32SymRate*1000;
		printf("[Gaven],set();[Unicable] s32Freq = %ld,u32TunerFreq = %ld, u32SymRate = %ld\n",s32Freq,unidmdpara.u32TunerFreq,unidmdpara.u32SymbolRate);
		if (MDrv_CofdmDmd_Restart(&unidmdpara) == FALSE)
		{
				return FALSE;
		}
    }
    return TRUE;
}
#endif

#endif // ENABLE_S2

