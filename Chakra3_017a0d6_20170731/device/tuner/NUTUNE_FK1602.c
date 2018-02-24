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
#ifndef _NUTNUE_FK1602_S
#define _NUTNUE_FK1602_S

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
#include "MApp_GlobalSettingSt.h"

//#include "MApp_Scan.h"

#define TM_FALSE  1
#define FK1602_BUSY  1
#define FK1602_FREE  0
static U8 u8FK1602Busy=FK1602_FREE;

#if 0//(FRONTEND_DEMOD_TYPE == TOSHIBA_TC90527FG_DEMOD)
    #define _DEMO_I2C_ID          0x30 // 0x80 // 0x3c
#else
    #define _DEMO_I2C_ID          0x80 // 0x3c
#endif

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

	#if (DEMO_TUNER_IIC_TYPE == TWO_ROAD_SEPARATE)
		if(MDrv_IIC_ReadBytes(NXP18273_I2C_ADDR, (U8) AddrSize, pAddr, (U16) ReadLen, pData))
			err = TM_OK;
	#elif (DEMO_TUNER_IIC_TYPE == ONE_ROAD_BUS)
		if(MDrv_IIC_ReadBytes(_TUNER_I2C_ID, (U8) AddrSize, pAddr, (U16) ReadLen, pData))
	 		err = TM_OK;
	#else
		if(devCOFDM_PassThroughI2C_ReadBytes(_TUNER_I2C_ID, (U8) AddrSize, pAddr, (U16) ReadLen, pData))
			err = TM_OK;
    #endif

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
    UNUSED(tUnit);
#if 0
      U8 i;
	printf("FK1602 Write Data:");
	for(i=0;i<WriteLen;i++)
	printf("%bx  ",*(pData+i));
	printf("\n");
#endif
	#if (DEMO_TUNER_IIC_TYPE == TWO_ROAD_SEPARATE)
		if(MDrv_IIC_WriteBytes(NXP18273_I2C_ADDR,  (U8) AddrSize, pAddr, (U16) WriteLen, pData))
			err = TM_OK;
	#elif (DEMO_TUNER_IIC_TYPE == ONE_ROAD_BUS)
		if(MDrv_IIC_WriteBytes(_TUNER_I2C_ID, (U8) AddrSize, pAddr, (U16) WriteLen, pData))
	 		err = TM_OK;
#elif 0//(FRONTEND_DEMOD_TYPE == TOSHIBA_TC90527FG_DEMOD)
			U8 i;
			U8 u8data[AddrSize+WriteLen+2],j;
			u8data[0] = 0xFE;//through start address
			u8data[1] = _TUNER_I2C_ID;//through start address
			for (i=0,j=0;i<AddrSize+WriteLen;i++)
			{
				if(i<AddrSize)
        {
					u8data[2+i] = *(pAddr+i);
        }
        else if((i<AddrSize+WriteLen)&&(i>=AddrSize))
				{
					u8data[2+i] = *(pData+j);
					j++;
				}
			}
			if(MDrv_IIC_WriteBytes(_DEMO_I2C_ID, 0, pAddr, (U16)(WriteLen+AddrSize+2), u8data))
				err = TM_OK;
#else
    if (devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, (U8) AddrSize, pAddr, (U16) WriteLen, pData))
        err = TM_OK;
    #endif
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
#if (FRONTEND_TUNER_TYPE != NXP_TDA18274_TUNER)
static tmTDA18273StandardMode_t devTuner_GetTunerStandard(void)
{
    IF_FREQ IF_Freq = MDrv_IFDM_GetIF();
    tmTDA18273StandardMode_t StandardMode;


    // IF Freq To Tuner Standard
    switch( IF_Freq )
{
        case IF_FREQ_B:
            StandardMode = tmTDA18273_ANLG_B;
            break;
        case IF_FREQ_G:
            StandardMode = tmTDA18273_ANLG_GH;
            break;
        case IF_FREQ_I:
            StandardMode = tmTDA18273_ANLG_I;
            break;
        case IF_FREQ_DK:
            StandardMode = tmTDA18273_ANLG_DK;
            break;
        case IF_FREQ_L:
            StandardMode = tmTDA18273_ANLG_L;
            break;
        case IF_FREQ_L_PRIME:
            StandardMode = tmTDA18273_ANLG_LL;
            break;
        case IF_FREQ_MN:
            StandardMode = tmTDA18273_ANLG_MN;
            break;

        default:
            //printf("\nError! Unknown IF-Freq!!\n");
            StandardMode = tmTDA18273_ANLG_B;
            break;
    }

    return StandardMode;
	}
#else
static TDA182I4StandardMode_t devTuner_GetTunerStandard(void)
{
    IF_FREQ IF_Freq = MDrv_IFDM_GetIF();
    TDA182I4StandardMode_t StandardMode;


    // IF Freq To Tuner Standard
    switch( IF_Freq )
	{
        case IF_FREQ_B:
            StandardMode = TDA182I4_ANLG_B;
            break;
        case IF_FREQ_G:
            StandardMode = TDA182I4_ANLG_GH;
            break;
        case IF_FREQ_I:
            StandardMode = TDA182I4_ANLG_I;
            break;
        case IF_FREQ_DK:
            StandardMode = TDA182I4_ANLG_DK;
            break;
        case IF_FREQ_L:
            StandardMode = TDA182I4_ANLG_L;
            break;
        case IF_FREQ_L_PRIME:
            StandardMode = TDA182I4_ANLG_LL;
            break;
        case IF_FREQ_MN:
            StandardMode = TDA182I4_ANLG_MN;
            break;

        default:
            //printf("\nError! Unknown IF-Freq!!\n");
            StandardMode = TDA182I4_ANLG_B;
            break;
    }

    return StandardMode;
	}
#if 0
static UInt32 devTuner_GetTunerStandard(void)
{
    IF_FREQ IF_Freq = MDrv_IFDM_GetIF();
    UInt32 StandardMode;


    // IF Freq To Tuner Standard
    switch( IF_Freq )
	{
        case IF_FREQ_B:
            StandardMode = LGIT_TUNER_STD_PAL_B;
            break;
        case IF_FREQ_G:
            StandardMode = LGIT_TUNER_STD_PAL_G;
            break;
        case IF_FREQ_I:
            StandardMode = LGIT_TUNER_STD_PAL_I;
            break;
        case IF_FREQ_DK:
            StandardMode = LGIT_TUNER_STD_PAL_D;
            break;
        case IF_FREQ_L:
            StandardMode = LGIT_TUNER_STD_SECAM_L;
            break;
        case IF_FREQ_L_PRIME:
            StandardMode = LGIT_TUNER_STD_SECAM_LP;
            break;
        case IF_FREQ_MN:
            StandardMode = LGIT_TUNER_STD_PAL_M;
            break;

        default:
            printf("\nError! Unknown IF-Freq!!\n");
            StandardMode = LGIT_TUNER_STD_PAL_B;
            break;
	}

    return StandardMode;
}
#endif
#endif
#if 0 // uncalled
void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
	double dRFfreq;
#if  (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
	TDA182I4StandardMode_t StandardMode;
#else
	tmTDA18273StandardMode_t StandardMode;
#endif
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
    StandardMode = devTuner_GetTunerStandard();
	if(CurrentStandard==IF_FREQ_B)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_B;
	#else
		StandardMode=tmTDA18273_ANLG_B;
	#endif
	}
	else if  (CurrentStandard==IF_FREQ_G)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_GH;
	#else
		StandardMode=tmTDA18273_ANLG_GH;
	#endif
	}
	else if  (CurrentStandard==IF_FREQ_I)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_I;
	#else
		StandardMode=tmTDA18273_ANLG_I;
	#endif
	}
	else if  (CurrentStandard==IF_FREQ_DK)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_DK;
	#else
		StandardMode=tmTDA18273_ANLG_DK;
	#endif
	}
	else if  (CurrentStandard==IF_FREQ_L)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_L;
	#else
		StandardMode=tmTDA18273_ANLG_L;
	#endif
	}
	else if  (CurrentStandard==IF_FREQ_L_PRIME)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_LL;
	#else
		StandardMode=tmTDA18273_ANLG_LL;
	#endif
	}
	else if  (CurrentStandard==IF_FREQ_MN)
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_MN;
	#else
		StandardMode=tmTDA18273_ANLG_MN;
	#endif
	}
	else
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		StandardMode=TDA182I4_ANLG_B;
	#else
		StandardMode=tmTDA18273_ANLG_B;
	#endif
	}
    /* OM3912 Send Request 55.25 MHz standard PAL B*/
    TuneRequest.dwFrequency = dRFfreq*1000L;
    TuneRequest.dwStandard = StandardMode;
    tmsysOM3912SendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
}
#endif

void devTunerSetFreq(U32 u32Freq)
{
    #if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
    TDA182I4StandardMode_t StandardMode;
    #else
    tmTDA18273StandardMode_t StandardMode;
    #endif
    tmTunerOnlyRequest_t TuneRequest;
    tmUnitSelect_t  sysUnit= 0;


    StandardMode = devTuner_GetTunerStandard();

#if 0
    printf("[devTunerSetFreq(freq=%lu) ", u32Freq);

    //printf(" MDrv_IFDM_GetIF()=%u; ", MDrv_IFDM_GetIF());

    printf(" u8TunerStd=%u; ", StandardMode);

    switch(StandardMode)
    {
        case tmTDA18273_ANLG_DK:
            printf("DK");
            break;
        case tmTDA18273_ANLG_L:
            printf("L");
            break;
        case tmTDA18273_ANLG_LL:
            printf("LL");
            break;
        default:
            break;
    }
    printf("]\n");
#endif

    /* OM3912 Send Request 55.25 MHz standard PAL B*/
    TuneRequest.dwFrequency = u32Freq;//dRFfreq*1000L;
    TuneRequest.dwStandard = StandardMode;
    TuneRequest.eTunerLock = tmsysFrontEndStateUnknown;
    tmsysOM3912SendRequest(sysUnit, &TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
}

void devTunerInit(void)
{
   //* Begin
    /* Variable declarations */
    tmErrorCode_t err = TM_OK;
    tmbslFrontEndDependency_t sSrvTunerFunc;
    tmTunerOnlyRequest_t TuneRequest;
    tmUnitSelect_t  sysUnit= 0;

    if (u8FK1602Busy==FK1602_FREE)
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

    /* system init : TDA18273 */
    err = tmsysOM3912Init(sysUnit, &sSrvTunerFunc);
    if(err != TM_OK)
       return ;

    /* Hardware power state */
    err = tmsysOM3912SetPowerState(sysUnit, tmPowerOn);

    /* Hardware initialization */
    err = tmsysOM3912Reset(sysUnit);
    if(err != TM_OK)
       return ;
	u8FK1602Busy=FK1602_BUSY;
    	}
    /* OM3912 Send Request 55.25 MHz standard PAL B*/
    TuneRequest.dwFrequency = 55250000L;
#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
	TuneRequest.dwStandard = TDA182I4_ANLG_B;
#else
	TuneRequest.dwStandard = tmTDA18273_ANLG_B;
#endif
    err = tmsysOM3912SendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
    return ;
}


static UInt32 devDigitalTuner_GetStandardType(RF_CHANNEL_BANDWIDTH eBandWidth)
{
	UInt32 dwStandard;

#if ENABLE_DVBC //ENABLE_T_C_COMBO
	//if (stGenSetting.stScanMenuSetting.u8DVBCTvConnectionType == EN_DVB_C_TYPE)
	if( IsDVBCInUse() )
	{
    #if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		dwStandard = TDA182I4_DVBT_8MHz;
	#else
		dwStandard = tmTDA18273_QAM_8MHz;
	#endif
	}
	else
#endif //#else
#if(ENABLE_DTMB)
	//if(DTV_SYSTEM_SEL == DTV_SYSTEM_DTMB)
    if( IsDTMBInUse() )
	{
    #if 1//(DTV_SYSTEM_SEL == DTV_SYSTEM_DTMB)
        #if (DTV_DWSTANDARD_SEL==DTV_DWSTANDARD_6MHZ)
        	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
        		dwStandard = TDA182I4_DMBT_6MHz;
        	#else
        		dwStandard = tmTDA18273_DMBT_6MHz;
        	#endif
        #else
    		#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		        dwStandard = TDA182I4_DMBT_8MHz;
	        #else
		        dwStandard = tmTDA18273_DMBT_8MHz;
	        #endif
        #endif
    #else
		#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		    dwStandard = TDA182I4_DMBT_8MHz;
	    #else
		    dwStandard = tmTDA18273_DMBT_8MHz;
	    #endif
    #endif
	}
	else
#endif
	{
	#if (FRONTEND_TUNER_TYPE == NXP_TDA18274_TUNER)
		dwStandard = TDA182I4_DVBT_6MHz+eBandWidth-1;
	#else
		dwStandard = tmTDA18273_DVBT_6MHz+eBandWidth-1;
	#endif
	}

	return dwStandard;
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

	 if (u8FK1602Busy==FK1602_FREE)
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

	    /* system init : TDA18273 */
	    err = tmsysOM3912Init(sysUnit, &sSrvTunerFunc);
	    if(err != TM_OK)
	    	return ;

	    /* Hardware power state */
	    err = tmsysOM3912SetPowerState(sysUnit, tmPowerOn);

	    /* Hardware initialization */
	    err = tmsysOM3912Reset(sysUnit);

	    if(err != TM_OK)
	    	return ;
	    u8FK1602Busy=FK1602_BUSY;
	}

    /* OM3912 Send Request 546 MHz standard DVB-T  8 MHz*/
    TuneRequest.dwFrequency = 546000000L;
    TuneRequest.dwStandard = devDigitalTuner_GetStandardType(E_RF_CH_BAND_6MHz);
    err = tmsysOM3912SendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
    return ;
}

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
	tmTunerOnlyRequest_t TuneRequest;
	tmUnitSelect_t  sysUnit= 0;

	/* OM3912 Send Request 55.25 MHz standard PAL B*/
	TuneRequest.dwFrequency = Freq*1000000L;
    TuneRequest.dwStandard = devDigitalTuner_GetStandardType(eBandWidth);
	tmsysOM3912SendRequest(sysUnit,&TuneRequest,sizeof(TuneRequest), TRT_TUNER_ONLY );
}

void devDigitalTuner_ExtendCommand (MS_U8 u8SubCmd, MS_U32 u32Param1, MS_U32 u32Param2, void* pvoidParam3)
{
    switch(u8SubCmd)
    {
        case E_TUNER_SUBCMD_GET_RF_LEVEL:
        {
            *((float *)pvoidParam3)=200.0f; // should return in dBm, if not used, should return 200.0dBm
            /*
            tmErrorCode_t err = TM_OK;
            tmUnitSelect_t  sysUnit= 0;
            UInt32 u32RFLevelDbm=0;
            //
            err=tmsysOM3912GetSignalStrength(sysUnit, &u32RFLevelDbm);
            //printf("NuTune FK1601 RF Level %ld\n",u32RFLevelDbm);
            if(err != TM_OK)
            {
                *((float *)pvoidParam3)=-10.0f;
                printf("NuTune FK1601 RF Level Get Error\n");
            }
            else
            {
                // 10dBuV 7
                // 109dBuV 117
                float fTemp=0.0f;
                fTemp=u32RFLevelDbm; // dBuV
                if (fTemp < 7.0f)
                {
                    fTemp=7.0f;
                }

                if (fTemp > 117.0f)
                {
                    fTemp=117.0f;
                }

                fTemp=10.0f+(fTemp-7.0f)*(109.0f-10.0f)/(117.0f-7.0f);
                *((float *)pvoidParam3)=fTemp-109.0f; // dBuV to dBm

                //printf("NuTune FK1601 RF Level %f dBm\n",*((float *)pvoidParam3));
            }
            */
        }
        break;
        default:
            UNUSED(u8SubCmd);
            UNUSED(u32Param1);
            UNUSED(u32Param2);
            UNUSED(pvoidParam3);
        break;
    }
}

#undef _NUTNUE_FK1602_S

#endif

