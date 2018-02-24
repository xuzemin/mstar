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
/********************************************************************
* SemcoTDA18273.c
* TDA18273 Functions
* General Standard API 
* By yooheeyong 2011/08/23
*********************************************************************/
/***********************

History.
2011.10.11 - DK. Jung
      
    SemcoTDA18273_SetStandardMode() 수정 
                                    == >    (DVB_T2 일 경우 3 번째 Param = 0, 그외 경우는 1)
    InstanceCustom.h
                                    ==> 구주. 미주, ISDB-T 공용화.
    SemcoTDA18273_Init
                                    ==>  Param 2 : Single 이면 0, Dual  이면 1

*****************/





// For I2C interface
#ifdef _SEMCO
#include "lib.h"
#include "SEMCO_tx_process.h"
#include "SEMCO_rx_process.h"
#else
#include "UserDefinedIIC.h"
#endif


#include "SemcoTDA18273.h"
#include "tmbslTDA18273local.h"

tmbslFrontEndDependency_t sSrvTunerFunc;


// By DK. Jung
/// 0 => Signale   else=> Dual
unsigned char u8DualTuner;

/* Initialize TDA18273 */
int SemcoTDA18273_Init(int nDeviceId, unsigned char SingleOrDual)
{
	int ret;
	ret = 0;

	/* low layer struct set up to link with user written functions */
	/* Semco only use 3 functions such as IIC write, read and wait. */
    sSrvTunerFunc.sIo.Write      = TDA18273_I2cWrite;
    sSrvTunerFunc.sIo.Read       = TDA18273_I2cRead;
	sSrvTunerFunc.sTime.Wait     = TDA18273_Wait;
    sSrvTunerFunc.sTime.Get      = Null;
	sSrvTunerFunc.sDebug.Print   = Null;
	sSrvTunerFunc.sMutex.Acquire = Null;
	sSrvTunerFunc.sMutex.DeInit  = Null;
	sSrvTunerFunc.sMutex.Init    = Null;
	sSrvTunerFunc.sMutex.Release = Null;
	sSrvTunerFunc.dwAdditionalDataSize = 0;
	sSrvTunerFunc.pAdditionalData      = Null;

	// DK. Jung
	u8DualTuner = SingleOrDual;

	/* Init */
    ret = tmbslTDA18273Init(nDeviceId,&sSrvTunerFunc);
	if(ret != TM_OK) return 1;
    else{}

     /* Set Power On */
	ret = tmbslTDA18273SetPowerState(nDeviceId,(tmTDA18273PowerState_t)tmPowerOn);
	if(ret != TM_OK) return 1;		

	 /* Set VSYNC add by yooheeyong 20101118 with ohj */
	 /* 2nd parameter = 1 internal VSYNC Generator */
	 ret = tmddTDA18273SetVsync_int(nDeviceId,1);
	 if(ret != TM_OK) return 1;


	// If mode is Dual,
	if(SingleOrDual)
	{
		 /* XTout_Mode */
		 //  nDeviceId 2: 0xC0(Master), 1: 0xC6(Slave) 
		 // Only will enter this area when idx is master mode. 
		if(nDeviceId == TDA18273_C0)
		{
			ret = tmddTDA18273SetXTout(nDeviceId,0x03); // XTout 16 MHz
			 if(ret != TM_OK) return 1;	 	
		}
	}
	else
	{
		ret = tmddTDA18273SetXTout(nDeviceId, 0); 
		if(ret != TM_OK) return 1;

	}
//#endif

	 /* Reset */
	 ret = tmbslTDA18273Reset(nDeviceId);
	 if(ret != TM_OK) return 1;	 	
	 	

	 return 0;
}

/* Deinitialize TDA18273 */
int SemcoTDA18273_DeInit(int nDeviceId)
{
	/* Deinitialize driver */
	int ret=0;

	ret = tmbslTDA18273DeInit(nDeviceId);

	// DK. Jung
	u8DualTuner = 0;


	return ret;
}


/* Set standard mode */
/* NotDVB_T2 :TDVB_T2 ==> 0      else(DVB_T, ISDB_T, ATSC ..) ==> 1 */
int SemcoTDA18273_SetStandardMode(int nDeviceId, tmTDA18273StandardMode_t stdMode, int NotDVB_T2)
{
	int ret;
	unsigned int nIF;
	
	ret = 0;
	nIF = 0;

	ret = tmbslTDA18273SetStandardMode(nDeviceId,stdMode);

      /* When use DVB-T, change defualt value for IF output level by yooheeyong 20110901 */


//      if(nOnlyDVB_T)
//  	      ret = tmddTDA18273SetIF_Level(nDeviceId, tmTDA18273_IF_Output_Level_0_5Vpp_min_12_18dB); /* tmTDA18273_IF_Output_Level_0_5Vpp_min_12_18dB */
	/// nOnlyDVB_T 가 0 이면 20111011
      if(!NotDVB_T2)   // t2 일 경우만..
  	      ret = tmddTDA18273SetIF_Level(nDeviceId, tmTDA18273_IF_Output_Level_1Vpp_min_6_24dB); /* tmTDA18273_IF_Output_Level_0_5Vpp_min_12_18dB */
	else
	{
	;
	}
// By DK.Jung
	if(u8DualTuner)
//      if(bDualTuner)
      	{
//		if(bMaster)
		if(!nDeviceId)
		{
	      	     switch(stdMode)
			{
 	      	         case tmTDA18273_QAM_6MHz:
	                    nIF = 3550000;
	                break;

 	      	         case tmTDA18273_QAM_8MHz:
	                    nIF = 5050000;
	                break;	          

 	      	         case tmTDA18273_ATSC_6MHz:
	                    nIF = 3200000;
	                break;	   

 	      	         case tmTDA18273_ISDBT_6MHz:
	                    nIF = 3200000;
	                break;	   	

 	      	         case tmTDA18273_DVBT_1_7MHz:
	                    nIF = 800000;
	                break;	   

 	      	         case tmTDA18273_DVBT_6MHz:
	                    nIF = 3200000;
	                break;	   

 	      	         case tmTDA18273_DVBT_7MHz:
	                    nIF = 3450000;
	                break;	   	

 	      	         case tmTDA18273_DVBT_8MHz:
	                    nIF = 3950000;
	                break;	  	 

 	      	         case tmTDA18273_DVBT_10MHz:
	                    nIF = 4950000;
	                break;	  

 	      	         case tmTDA18273_DMBT_8MHz:
	                    nIF = 3950000;
	                break;	  

 	      	         case tmTDA18273_FM_Radio:
	                    nIF = 1200000;
	                break;	  

 	      	         case tmTDA18273_ANLG_MN:
	                    nIF = 5350000 - 1750000;
	                break;	        

 	      	         case tmTDA18273_ANLG_B:
	                    nIF = 6350000 - 2250000;
	                break;	     

 	      	         case tmTDA18273_ANLG_GH:
	                    nIF = 6700000 - 2750000;
	                break;	  

 	      	         case tmTDA18273_ANLG_I:
	                    nIF = 7200000 - 2750000;
	                break;	 

 	      	         case tmTDA18273_ANLG_DK:
	                    nIF = 6800000 - 2750000;
	                break;		

 	      	         case tmTDA18273_ANLG_L:
	                    nIF = 6700000 - 2750000;
	                break;		

 	      	         case tmTDA18273_ANLG_LL:
	                    nIF = 1200000 - (-2750000);
	                break;		     

 	      	         case tmTDA18273_Scanning:
	                    nIF = 7200000 - 2750000;
	                break;		

 	      	         case tmTDA18273_ScanXpress:
	                    nIF = 4950000;
	                break;		

	                default:
	                	 nIF = 3200000; /* DVB-T 6MHz */

			}

      	    	}
	else{
	      	     switch(stdMode)
			{
 	      	         case tmTDA18273_QAM_6MHz:
	                    nIF = 3650000;
	                break;

 	      	         case tmTDA18273_QAM_8MHz:
	                    nIF = 4950000;  
	                break;	          

 	      	         case tmTDA18273_ATSC_6MHz:
	                    nIF = 3300000;
	                break;	   

 	      	         case tmTDA18273_ISDBT_6MHz:
	                    nIF = 3300000;
	                break;	   	

 	      	         case tmTDA18273_DVBT_1_7MHz:
	                    nIF = 900000;
	                break;	   

 	      	         case tmTDA18273_DVBT_6MHz:
	                    nIF = 3300000;
	                break;	   

 	      	         case tmTDA18273_DVBT_7MHz:
	                    nIF = 3550000;
	                break;	   	

 	      	         case tmTDA18273_DVBT_8MHz:
	                    nIF = 4050000;
	                break;	  	 

 	      	         case tmTDA18273_DVBT_10MHz:
	                    nIF = 5050000;
	                break;	  

 	      	         case tmTDA18273_DMBT_8MHz:
	                    nIF = 4050000;
	                break;	  

 	      	         case tmTDA18273_FM_Radio:
	                    nIF = 1300000;
	                break;	  

 	      	         case tmTDA18273_ANLG_MN:
	                    nIF = 5450000 - 1750000;
	                break;	        

 	      	         case tmTDA18273_ANLG_B:
	                    nIF = 6450000 - 2250000;
	                break;	     

 	      	         case tmTDA18273_ANLG_GH:
	                    nIF = 6800000 - 2750000;
	                break;	  

 	      	         case tmTDA18273_ANLG_I:
	                    nIF = 7300000 - 2750000;
	                break;	 

 	      	         case tmTDA18273_ANLG_DK:
	                    nIF = 6900000 - 2750000;
	                break;		

 	      	         case tmTDA18273_ANLG_L:
	                    nIF = 6800000 - 2750000;
	                break;		

 	      	         case tmTDA18273_ANLG_LL:
	                    nIF = 1300000 - (-2750000);
	                break;		     

 	      	         case tmTDA18273_Scanning:
	                    nIF = 7300000 - 2750000;
	                break;		

 	      	         case tmTDA18273_ScanXpress:
	                    nIF = 5050000;
	                break;		

	                default:
	                	 nIF = 3300000; /* DVB-T 6MHz */

	      	     }
	}

           ret = tmddTDA18273SetIF_Freq(nDeviceId,nIF);

      	}
	else
	{
		;
	}
	  

	return ret;
}

/* Set RF frequency */
int SemcoTDA18273_SetFrequency(int nDeviceId, unsigned int nFreq_Hz)
{
	int ret=0;

  ret = tmbslTDA18273SetRf(nDeviceId,nFreq_Hz);

	return ret;
}

/* Get PLL Lock status */
int SemcoTDA18273_GetLockStatus(int nDeviceId)
{
    tmbslFrontEndState_t  pLockStatus;

	tmbslTDA18273GetLockStatus(nDeviceId,&pLockStatus);

	if(pLockStatus == tmbslFrontEndStateLocked)
		return 1;
	else{}

	return 0;
}

/* Get IF frequency */
int SemcoTDA18273_GetIF(int nDeviceId, unsigned int *lpnIF_Hz)
{
	int ret=0;

	ret = (int)tmbslTDA18273GetIF(nDeviceId,(unsigned long *)lpnIF_Hz);

    return ret;
}

/* Wake Up*/
void SemcoTDA18273_On(int nDeviceId)
{
  tmbslTDA18273SetPowerState(nDeviceId,(tmTDA18273PowerState_t)tmPowerOn);
}

/* Stand By*/
void SemcoTDA18273_StandBy(int nDeviceId)
{
	tmbslTDA18273SetPowerState(nDeviceId,(tmTDA18273PowerState_t)tmPowerStandby);
}

/* MFT */
/* step : +1, -1 */
unsigned char SemcoTDA18273_MFT(int nDeviceId,char step)
{
	int ret=0;

	ret = tmbslTDA18273RFFineTuning(nDeviceId,step);

	return (unsigned char)ret;
}

/* Get Power Level */
/* 
 =========== RSSI  계산 예 ==============
UInt8 nRSSI;
int RSSI;

SemcoTDA18273_GetPowerLevel(&nRSSI);

RSSI = (nRSSI * 0.5) - 107;

printf("%d",RSSI);
*/
int SemcoTDA18273_GetPowerLevel(int nDeviceId, unsigned char *nRSSI)
{
  int ret=0;

  ret = tmbslTDA18273GetPowerLevel(nDeviceId, nRSSI);

  return ret;
}

/* Check RF filter robustness */
int SemcoTDA18273_CheckRFFilterRobustness(int nDeviceId, tmTDA18273RFFilterRating *lpFilterRating)
{
	int ret=0;
	
	ret = tmbslTDA18273CheckRFFilterRobustness(nDeviceId, lpFilterRating);

    return ret;
}



/* Get Temperature */
int SemcoTDA18273_GetTemperature(int nDeviceId, unsigned char *lpThermo)
{
	 int ret;

	 ret = tmddTDA18273GetTM_D(nDeviceId,lpThermo); 

	 return ret;
}





