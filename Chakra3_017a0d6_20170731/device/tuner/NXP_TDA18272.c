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
/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          main.c
 *
 *                3
 *
 * \date          %modify_time%
 *
 * \brief         Sample application code of the NXP OM3910 driver.
 *
 * REFERENCE DOCUMENTS :
 *                OM3912_Driver_User_Guide.pdf
 *
 * Detailed description may be added here.
 *
 * \section info Change Information
 *
*/

//*--------------------------------------------------------------------------------------
//* Include Standard files
//*--------------------------------------------------------------------------------------
#ifndef _NXP_TDA18272_S
#define _NXP_TDA18272_S

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "drvGPIO.h"

#define TM_FALSE  1
#define TUNER_BUSY  1
#define TUNER_FREE  0
static U8 u8TunerBusy=TUNER_FREE;

//*--------------------------------------------------------------------------------------
//* Prototype of function to be provided by customer
//*--------------------------------------------------------------------------------------
tmErrorCode_t 	UserWrittenI2CRead(tmUnitSelect_t tUnit,UInt32 AddrSize, UInt8* pAddr,UInt32 ReadLen, UInt8* pData);
tmErrorCode_t 	UserWrittenI2CWrite (tmUnitSelect_t tUnit, UInt32 AddrSize, UInt8* pAddr,UInt32 WriteLen, UInt8* pData);
tmErrorCode_t 	UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms);

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CRead
//* Object              : 
//* Input Parameters    : 	tmUnitSelect_t tUnit
//* 						UInt32 AddrSize,
//* 						UInt8* pAddr,
//* 						UInt32 ReadLen,
//* 						UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CRead(tmUnitSelect_t tUnit,	UInt32 AddrSize, UInt8* pAddr,
UInt32 ReadLen, UInt8* pData)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_FALSE;
    //U8 i;
    UNUSED(tUnit);
      if(MDrv_IIC_ReadBytes(NXP18272_I2C_ADDR, (U8) AddrSize, pAddr, (U16) ReadLen, pData))
	{
	err = TM_OK;
	/*
	printf("FK1602 Read Data:");
		for(i=0;i<ReadLen;i++)
	printf("%bx  ",*(pData+i));
		printf("\n");
		*/
      	}

    return err;

}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenI2CWrite
//* Object              : 
//* Input Parameters    : 	tmUnitSelect_t tUnit
//* 						UInt32 AddrSize,
//* 						UInt8* pAddr,
//* 						UInt32 WriteLen,
//* 						UInt8* pData
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenI2CWrite (tmUnitSelect_t tUnit, 	UInt32 AddrSize, UInt8* pAddr,
UInt32 WriteLen, UInt8* pData)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_FALSE;
    //U8 i;
    UNUSED(tUnit);
	/*
	printf("FK1602 Write Data:");
	for(i=0;i<WriteLen;i++)
	printf("%bx  ",*(pData+i));
	printf("\n");
	*/
    if(MDrv_IIC_WriteBytes(NXP18272_I2C_ADDR, (U8) AddrSize, pAddr, (U16) WriteLen, pData))
	err = TM_OK;

    return err;
}

//*--------------------------------------------------------------------------------------
//* Function Name       : UserWrittenWait
//* Object              : 
//* Input Parameters    : 	tmUnitSelect_t tUnit
//* 						UInt32 tms
//* Output Parameters   : tmErrorCode_t.
//*--------------------------------------------------------------------------------------
tmErrorCode_t UserWrittenWait(tmUnitSelect_t tUnit, UInt32 tms)
{
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    UNUSED(tUnit);
    msAPI_Timer_Delayms(tms);
    return err;
}


extern IF_FREQ MDrv_IFDM_GetIF(void);
void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
        double dRFfreq;
	 tmTDA182I2StandardMode_t StandardMode;
	 IF_FREQ CurrentStandard;
        tmTunerOnlyRequest_t TuneRequest;
	 tmUnitSelect_t  sysUnit= 0;
        UNUSED(eBand);
	
        #if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
        dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*62.5);
        #elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
        dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*50);
        #else
        dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*31.25);
        #endif 
		
	CurrentStandard=MDrv_IFDM_GetIF();

	if(CurrentStandard==IF_FREQ_B)
			StandardMode=tmTDA182I2_ANLG_B;
	else if  (CurrentStandard==IF_FREQ_G)
			StandardMode=tmTDA182I2_ANLG_GH;
	else if  (CurrentStandard==IF_FREQ_I)
			StandardMode=tmTDA182I2_ANLG_I;
	else if  (CurrentStandard==IF_FREQ_DK)
			StandardMode=tmTDA182I2_ANLG_DK;
	else if  (CurrentStandard==IF_FREQ_L)
			StandardMode=tmTDA182I2_ANLG_L;
	else if  (CurrentStandard==IF_FREQ_L_PRIME)
			StandardMode=tmTDA182I2_ANLG_LL;
	else if  (CurrentStandard==IF_FREQ_MN)
			StandardMode=tmTDA182I2_ANLG_MN;
	else 
			StandardMode=tmTDA182I2_ANLG_B;
		
          /* OM3912 Send Request 55.25 MHz standard PAL B*/
    TuneRequest.dwFrequency = dRFfreq*1000L;
    TuneRequest.dwStandard = StandardMode;
    tmsysOM3869SSendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
    
}

void devTunerInit(void)
{
   //* Begin
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndDependency_t sSrvTunerFunc;
    tmTunerOnlyRequest_t TuneRequest;
    tmUnitSelect_t  sysUnit= 0;
    if (u8TunerBusy==TUNER_FREE)
    	{
    /* Low layer struct set-up to link with user written functions */
    sSrvTunerFunc.sIo.Write             = UserWrittenI2CWrite;
    sSrvTunerFunc.sIo.Read              = UserWrittenI2CRead;
    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = Null;
    sSrvTunerFunc.sMutex.Init           = Null;
    sSrvTunerFunc.sMutex.DeInit         = Null;
    sSrvTunerFunc.sMutex.Acquire        = Null;
    sSrvTunerFunc.sMutex.Release        = Null;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;

    /* system init : TDA18272 */
    err = tmsysOM3869SInit(sysUnit, &sSrvTunerFunc);
    if(err != TM_OK)
       return ;
   
    /* Hardware power state */
    err = tmsysOM3869SSetPowerState(sysUnit, tmPowerOn);

    /* Hardware initialization */
    err = tmsysOM3869SReset(sysUnit);
    if(err != TM_OK)
       return ;
	u8TunerBusy=TUNER_BUSY;
   }
    /* OM3869 Send Request 55.25 MHz standard PAL B*/
    TuneRequest.dwFrequency = 55250000L;
    TuneRequest.dwStandard = tmTDA182I2_ANLG_B;
    err = tmsysOM3869SSendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
	 
    return ;
}

/*************************************************************************
  Subject:    FQD1216 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{
   //* Begin
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndDependency_t sSrvTunerFunc;
    tmTunerOnlyRequest_t TuneRequest;
    tmUnitSelect_t  sysUnit= 0;
	
	 if (u8TunerBusy==TUNER_FREE)
    	{
    /* Low layer struct set-up to link with user written functions */
    sSrvTunerFunc.sIo.Write             = UserWrittenI2CWrite;
    sSrvTunerFunc.sIo.Read              = UserWrittenI2CRead;
    sSrvTunerFunc.sTime.Get             = Null;
    sSrvTunerFunc.sTime.Wait            = UserWrittenWait;
    sSrvTunerFunc.sDebug.Print          = Null;
    sSrvTunerFunc.sMutex.Init           = Null;
    sSrvTunerFunc.sMutex.DeInit         = Null;
    sSrvTunerFunc.sMutex.Acquire        = Null;
    sSrvTunerFunc.sMutex.Release        = Null;
    sSrvTunerFunc.dwAdditionalDataSize  = 0;
    sSrvTunerFunc.pAdditionalData       = Null;

    /* system init : TDA18272 */
    err = tmsysOM3869SInit(sysUnit, &sSrvTunerFunc);
    if(err != TM_OK)
       return ;
   
    /* Hardware power state */
    err = tmsysOM3869SSetPowerState(sysUnit, tmPowerOn);

    /* Hardware initialization */
    err = tmsysOM3869SReset(sysUnit);
    if(err != TM_OK)
       return ;
	u8TunerBusy=TUNER_BUSY;
   }
   
    /* OM3869 Send Request 546 MHz standard DVB_T*/
    TuneRequest.dwFrequency = 546000000L;
    TuneRequest.dwStandard = tmTDA182I2_DVBT_8MHz;
    err = tmsysOM3869SSendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
	 
    return ;
}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{    
     tmTunerOnlyRequest_t TuneRequest;
     tmUnitSelect_t  sysUnit= 0;

	/* OM3912 Send Request 55.25 MHz standard PAL B*/
    TuneRequest.dwFrequency = Freq*1000000L;
    TuneRequest.dwStandard = tmTDA182I2_DVBT_6MHz+eBandWidth-1;
    tmsysOM3869SSendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
}

#undef _NXP_TDA18272_S

#endif

