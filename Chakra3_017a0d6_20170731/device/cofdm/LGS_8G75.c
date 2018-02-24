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
/***************************************************************************************
*
*						(c) copyright 2007,legendsilicon,beijing,China
*
*						         All Rights Reserved
*
*
* File Name			: LGS_8G75.c
*
* Programmer(s)			: wangying
*
* Date Created			: 2008.05.21
*
* Date Updated			:
*
* Current Revision		: v2.2.11
*
* Modification History	:
*
* Description			:
*
***************************************************************************************/

/***************************************************************************************
*								  INCLUDE FILES
***************************************************************************************/
#include "LGS_TYPES.h"
//#include "LGS_HOOK.h"
#include "LGS_8G75.h"
#include "LGS_DEBUG.h"

#include "LGS_HOOK.c"

const UINT8 LGS8G75_Data[] =
{
	0x01,0x30,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xE4,0xF5,0xA8,0xF5,0xB8,0xF5,0x88,0xF5,0x89,0xF5,0x87,0x75,0xD0,0x00,0x11,0x50,
	0x11,0x50,0xF4,0xF5,0x80,0xF5,0x90,0xF5,0xA0,0xF5,0xB0,0x75,0x81,0x30,0x80,0x01,
	0x32,0x90,0x80,0x12,0x74,0xFF,0xF0,0x90,0x80,0x13,0x74,0x1F,0xF0,0x90,0x80,0x23,
	0x74,0x01,0xF0,0x90,0x80,0x22,0xF0,0x90,0x00,0x48,0x74,0x00,0xF0,0x90,0x80,0x4D,
	0x74,0x05,0xF0,0x90,0x80,0x09,0xE0,0x60,0x21,0x12,0x00,0xDD,0x14,0x60,0x1B,0x12,
	0x00,0xDD,0x14,0x60,0x15,0x12,0x00,0xDD,0x14,0x60,0x0F,0x12,0x00,0xDD,0x14,0x60,
	0x09,0x12,0x00,0xDD,0x14,0x60,0x03,0x12,0x00,0xDD,0x90,0x80,0x42,0xE0,0x60,0x0B,
	0x14,0x60,0x0C,0x14,0x60,0x0D,0x14,0x60,0x0E,0x01,0xB3,0x74,0x04,0x01,0xB9,0x74,
	0x05,0x01,0xB9,0x74,0x07,0x01,0xB9,0x74,0x0A,0xC0,0xE0,0x74,0xC8,0x12,0x00,0xE2,
	0xD0,0xE0,0x14,0x70,0xF4,0x90,0x80,0x09,0xE0,0x70,0xAE,0x12,0x00,0xF6,0x12,0x00,
	0xFE,0x90,0x00,0x48,0xE0,0x04,0xF0,0x90,0x80,0x4E,0xF0,0x01,0x73,0x90,0x80,0x08,
	0xF0,0x22,0xF8,0x7A,0x0C,0x79,0xFD,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD9,
	0xF6,0xDA,0xF2,0xD8,0xEE,0x22,0x90,0x80,0x65,0xE0,0x54,0xFD,0xF0,0x22,0x90,0x80,
	0x65,0xE0,0x44,0xC2,0xF0,0x22
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_ComputeSectionAddress(UINT8 regAddr, UINT8 *psecAddr)
{
/*
	//Sect 1: 0x00 ~ 0xBF; Sect 2: 0xC0 ~ 0xFF , Jay
	if (regAddr >= 0x00 && regAddr <= 0xBF)
	{
		*psecAddr = LGS8G75_SEC1_ADDR;
	}
	else if (regAddr >= 0xC0 && regAddr <= 0xFF)
	{
		*psecAddr = LGS8G75_SEC2_ADDR;
	}
	else
		return LGS_REGISTER_ERROR;	//illegal register address
*/
	regAddr = regAddr;
	*psecAddr = LGS8G75_SEC1_ADDR;

	return LGS_NO_ERROR;
}
LGS_RESULT LGS8G75_WriteRegister(UINT8 regAddr, UINT8 regVal)
{
    UINT8 secAddr;
    LGS8G75_ComputeSectionAddress(regAddr, &secAddr);
    if( MDrv_IIC_WriteByte( secAddr, regAddr, regVal ) == FALSE )
    {
        return LGS_I2C_OPEN_ERROR;
    }
        return LGS_NO_ERROR;
}
LGS_RESULT LGS8G75_ReadRegister(UINT8 regAddr, UINT8 *pregVal)
{
    UINT8 secAddr;
     LGS8G75_ComputeSectionAddress(regAddr, &secAddr);
        if(MDrv_IIC_ReadByte( secAddr, regAddr, pregVal ) == FALSE  )
        {
        return LGS_I2C_OPEN_ERROR;
    }
        return LGS_NO_ERROR;
}
LGS_RESULT LGS8G75_SectionWriteRegister(UINT8 secAddr, UINT8 regAddr, UINT8 regVal)
{

    if( MDrv_IIC_WriteByte( secAddr, regAddr, regVal ) == FALSE )
    {
        return LGS_I2C_OPEN_ERROR;
    }
        return LGS_NO_ERROR;
}
LGS_RESULT LGS8G75_SectionReadRegister(UINT8 secAddr, UINT8 regAddr, UINT8 *pregVal)
{

        if(MDrv_IIC_ReadByte( secAddr, regAddr, pregVal ) == FALSE  )
        {
        return LGS_I2C_OPEN_ERROR;
    	}
        return LGS_NO_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0
LGS_RESULT LGS8G75_WriteRegister(UINT8 regAddr, UINT8 regVal)
{
	UINT8 secAddr;
	UINT8 buffer[4];
	INT8 err = LGS_NO_ERROR;

	err = LGS8G75_ComputeSectionAddress(regAddr, &secAddr);
	if ( err != LGS_NO_ERROR )
	{
		LGS_Debug(("\t LGS_ComputeSectionAddress is failed!\n"));
		goto failed;
	}

	buffer[0] = regAddr;
	buffer[1] = regVal;

	err = LGS_OpenI2C(&g_lgsHandleI2c, secAddr, 1);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_OpenI2C is failed!\n"));
		goto failed;
	}

	err = LGS_WriteI2C(g_lgsHandleI2c, buffer, 2, 100);
	if(err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_WriteI2C is failed, setting sectiong(%02x) register(%02x) to %02x!\n",
			secAddr, buffer[0], buffer[1]));
		goto failed;
	}

	err = LGS_CloseI2C(g_lgsHandleI2c);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_CloseI2C is failed!\n"));
		goto failed;
	}

failed:
	return err;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_ReadRegister(UINT8 regAddr, UINT8 *pregVal)
{
	UINT8 secAddr;
	UINT8 buffer[4];
	INT8 err = LGS_NO_ERROR;

	LGS_Debug(("\t Calling LGS8G75_ReadRegister for register_address(%02x)\n", regAddr));

	err = LGS8G75_ComputeSectionAddress(regAddr, &secAddr);
	if ( err != LGS_NO_ERROR )
	{
		LGS_Debug(("\t LGS_ComputeSectionAddress is failed!\n"));
		goto failed;
	}

	buffer[0] = regAddr;

	err = LGS_OpenI2C(&g_lgsHandleI2c, secAddr, 1);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_OpenI2C is failed!\n"));
		goto failed;
	}

	err = LGS_WriteI2C(g_lgsHandleI2c, buffer, 1, 100);
	if(err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_WriteI2C is failed!\n"));
		goto failed;
	}

	err = LGS_ReadI2C(g_lgsHandleI2c, pregVal, 1, 100);
	if(err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_ReadI2C is failed, sectiong(%02x) register(%02x)!\n",
			secAddr, regAddr));
		goto failed;
	}

	err = LGS_CloseI2C(g_lgsHandleI2c);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_CloseI2C is failed!\n"));
		goto failed;
	}

failed:
	return err;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SectionReadRegister(UINT8 secAddr, UINT8 regAddr, UINT8 *pregVal)
{
	UINT8	buffer[4];
	INT8	err = LGS_NO_ERROR;

	buffer[0] = regAddr;

	err = LGS_OpenI2C(&g_lgsHandleI2c, secAddr, 1);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_OpenI2C is failed!\n"));
		goto failed;
	}

	err = LGS_WriteI2C(g_lgsHandleI2c, buffer, 1, 100);
	if(err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_WriteI2C is failed!\n"));
		goto failed;
	}

	err = LGS_ReadI2C(g_lgsHandleI2c, pregVal, 1, 100);
	if(err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_ReadI2C is failed, sectiong(%02x) register(%02x)!\n",
			secAddr, regAddr));
		goto failed;
	}

	err = LGS_CloseI2C(g_lgsHandleI2c);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_CloseI2C is failed!\n"));
		goto failed;
	}

failed:
	return err;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SectionWriteRegister(UINT8 secAddr, UINT8 regAddr, UINT8 regVal)
{
	UINT8	buffer[4];
	INT8	err = LGS_NO_ERROR;

	buffer[0] = regAddr;
	buffer[1] = regVal;

	err = LGS_OpenI2C(&g_lgsHandleI2c, secAddr, 1);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_OpenI2C is failed!\n"));
		goto failed;
	}

	err = LGS_WriteI2C(g_lgsHandleI2c, buffer, 2, 100);
	if(err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_WriteI2C is failed, setting sectiong(%02x) register(%02x) to %02x!\n",
			secAddr, buffer[0], buffer[1]));
		goto failed;
	}

	err = LGS_CloseI2C(g_lgsHandleI2c);
	if (err != LGS_NO_ERROR)
	{
		LGS_Debug(("\t LGS_CloseI2C is failed!\n"));
		goto failed;
	}

failed:
	return err;
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LGS_RESULT LGS8G75_SoftReset(void)
{
	INT8 err = LGS_NO_ERROR;
	UINT8 dat;
	printf("\r\n --LGS8G75_SoftReset--");
	err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x02, &dat);
	if (err != LGS_NO_ERROR)
		return err;

	dat = dat & 0xFE;

	err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x02, dat);
	if (err != LGS_NO_ERROR)
		return err;

	dat = dat | 0x01;
	err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x02, dat);
	if (err != LGS_NO_ERROR)
		return err;

	LGS_Wait(5); // wait 5 ms, allows SNR, AGC, AFC and feedback loops to stabilize

	return LGS_NO_ERROR;
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SelectADMode(UINT8 extAd)
{
	INT8 err = LGS_NO_ERROR;
	UINT8 datax;

	err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x07, &datax);
	if (err != LGS_NO_ERROR)
		return err;

	if (extAd == 0x00) //INTERNAL_AD
	{
		datax &= ~0x80;
	}
	else  //EXTERNAL_AD
	{
		datax |= 0x80;

	}

	err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x07, datax);
	if (err != LGS_NO_ERROR)
		return err;

	return LGS_NO_ERROR;
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SetMpegMode(UINT8 clkFree, UINT8 clkPolInvd, UINT8 serial)
{
	INT8 err = LGS_NO_ERROR;
	UINT8 dat;
       printf("\r\n --LGS8G75_SetMpegMode--");
	err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x30, &dat);
//	err = LGS8G75_ReadRegister (0xC2, &dat);
	if (err != LGS_NO_ERROR)
		return err;

	dat = dat & (~0x07);
	dat = dat | (serial & 0x01) | ((clkPolInvd<<1) & 0x02) | ((clkFree<<2) & 0x04);

	err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x30, dat);
//	err = LGS8G75_WriteRegister (0xC2, dat);
	if (err != LGS_NO_ERROR)
		return err;

	err = LGS8G75_SoftReset();
	if (err != LGS_NO_ERROR)
		return err;

	return LGS_NO_ERROR;
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SetManualParameters(UINT8 datax)
{
	UINT8	data19, tmp;
       printf("\r\n --LGS8G75_SetManualParameters--");
//	if(LGS8G75_WriteRegister(0x7D, datax))	return LGS_SET_MANUAL_ERROR;
	if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x19, &data19))	return LGS_SET_MANUAL_ERROR;
	tmp = datax << 1;
	tmp |= (data19 & 0x81);
	if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x19, tmp))	return LGS_SET_MANUAL_ERROR;

	LGS8G75_SoftReset();
	return LGS_NO_ERROR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_CheckLocked(UINT8 *result)
{
	/* returns true if demod CA locked and AFC Locked, false otherwise */
	INT8	err = LGS_NO_ERROR;

	err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x13, result);
	if (err != LGS_NO_ERROR)
		return err;

	*result = *result & 0x90;		/* Check Flag CA_Locked and AFC_Locked, Jay	*/
	if (*result == 0x90)
		*result = 1;
	else
		*result = 0;

	return LGS_NO_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

LGS_RESULT LGS8G75_SetManualMode(void)
{
	UINT8 datax, datay;
	printf("\r\n LGS8G75_SetManualMode--");
	if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x0C, &datax))	goto failed;
	datax &= (~0x80);
	if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x0C, datax))	goto failed;

	if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x0C, &datax))	goto failed;
	if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x19, &datay))	goto failed;

	if( ((datax&0x03) == 0x01) && (datay & 0x01) )
	{
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x6E, 0x05 ))	goto failed;

		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x02 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x03 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3d, 0x05 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3E, 0x28 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x53, 0x80 ))	goto failed;
	}
	else
	{
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x6E, 0x3F ))	goto failed;

		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x00 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3D, 0x04 ))	goto failed;
	}

	LGS8G75_SoftReset();

	return LGS_NO_ERROR;
failed:
	return LGS_DETECT_ERROR;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// reg: 寄存器
// mask：掩码
// val：期望的正确值
// interval：每次循环之间的间隔
LGS_RESULT LGS8G75_WaitForLock( UINT8 reg, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times)
{
	UINT8	i = 0;
	UINT8	tmp;

	for( i=0; i<times; i++ )
	{
		LGS_Wait(interval);
		LGS8G75_ReadRegister(reg, &tmp);

		if( (tmp & mask) == val )
		{
			*real_times = i;
			return LGS_NO_ERROR;
		}
	}
	*real_times = i;
	return LGS_TIMEOUT_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SectionWaitForLock( UINT8 sec, UINT8 reg, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times)
{
	UINT8	i = 0;
	UINT8	tmp;

	for( i=0; i<times; i++ )
	{
		LGS_Wait(interval);
		LGS8G75_SectionReadRegister(sec, reg, &tmp);

		if( (tmp & mask) == val )
		{
			*real_times = i;
			return LGS_NO_ERROR;
		}
	}
	*real_times = i;
	return LGS_TIMEOUT_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

#define NUM_OF_MODE		5
#define TIMES_DETECTION		(NUM_OF_MODE*2)

LGS_RESULT LGS8G75_AutoDetect(void)
{
	UINT8 datax;
	UINT8 datay;
	INT8  i;
	UINT8 j;
	UINT8 k;
	UINT8 retryNum;
	j = 0;
	k = 0;
	i = -1;
	retryNum = 0;
	printf("\r\n --LGS8G75_AutoDetect--");
	if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x6E, 0x3F))	goto failed;

	do
	{
		i++;

		if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x0C, &datax))	goto failed;
		if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x18, &datay))	goto failed;

		datax &= (~0x03);

		switch( i % NUM_OF_MODE )
		{
			case 0: datax |= 0x02; datay &= (~0x01); break;	// 945 VPN
			case 1: datax |= 0x02; datay |= 0x01; break;	// 945 CPN

			case 2: datax |= 0x00; datay &= (~0x01); break;	// 420 VPN
			case 3: datax |= 0x00; datay |= 0x01; break;	// 420 CPN

			case 4: datax |= 0x01; datay |= 0x01; break;	// 595 CPN

			default: datax |= 0x00;
		}

		if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x0C, datax))	goto failed;
		if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x18, datay))	goto failed;
		LGS8G75_SoftReset();

		if( LGS_TIMEOUT_ERROR == LGS8G75_SectionWaitForLock( LGS8G75_SEC1_ADDR, 0x13, 0x80, 0x80, 50,20,&k))	continue;
		if( LGS_TIMEOUT_ERROR == LGS8G75_SectionWaitForLock( LGS8G75_SEC1_ADDR, 0x1F, 0xC0, 0x80, 10,20,&j))
		{
			if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x19, &datax)) goto failed; //bit[0]为0：多载波   1:单载波
			if(datax & 0x01)	//单载波
			{
				datax &= (~0x01);

				if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x67, 0xAA))	goto failed;

				if( 4 == i%5 )
					if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x6E, 0x05))	goto failed;

			}
			else	//多载波
			{
				datax |= 0x01;

				if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x67, 0x98))	goto failed;

				if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x6E, 0x3F))	goto failed;
			}

			if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x19, datax)) goto failed;

			retryNum++;

			if (retryNum > 2)
			{
				retryNum = 0;
				continue;
			}
			i--;
			continue;
		}


//		if(LGS8G75_ReadRegister(0xA2, &datax))	goto failed;
		if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x1F, &datax))	goto failed;
		datax &= (~0xC0);
		if(LGS8G75_SetManualParameters(datax) != LGS_NO_ERROR)
			continue;

		break;

	} while( i < TIMES_DETECTION );

    {
    U8 tmp13,temp;

         if (MDrv_IIC_ReadBytes(0x1c0, 0, &temp, 1, &temp) == FALSE)
     {
     		printf("\r\n --read fail\n");
     }
     printf("\r\n 2009-10-15 tuner = %x",temp);

    LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR,0x13,&tmp13);
    printf("\r\n 2009-10-15 8g75 0x13= %x",tmp13);
    LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR,0x30,&tmp13);
    printf("\r\n 2009-10-15 8g75 0x30= %x",tmp13);
          }

	if(i == TIMES_DETECTION )
	{
		goto failed;
	}

	return LGS_NO_ERROR;
failed:
	return LGS_DETECT_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

LGS_RESULT LGS8G75_SetAutoMode(void)
{
	//set automode
	UINT8 datax;
	printf("\r\n --LGS8G75_SetAutoMode--");
	if(LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x0C, &datax))	goto failed;
	printf("\r\n --datax = %x--",datax);
	datax &= (~0x04);
	datax |= 0x80;
	printf("\r\n --11datax = %x--",datax);
	if(LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x0C, datax))	goto failed;

	if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x00 ))	goto failed;
	if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3D, 0x04 ))	goto failed;

	return LGS_NO_ERROR;
failed:
	return LGS_CHANGE_MODE_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SelectTunerType(UINT8 canTuner)
{
	UINT8 datax;
	UINT8 tmp[4];

	if (LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x07, &datax)) goto failed;
	if (canTuner == 0x00)
	{
		datax |= 0x0C;
		tmp[0] = 0x00;tmp[1] = 0x00;tmp[2] = 0x00;tmp[3] = 0x00;
	}
	else if (canTuner == 0x01)//36MHz
	{
		datax &= 0xF3;
		tmp[0] = 0xCB;tmp[1] = 0x6B;tmp[2] = 0x28;tmp[3] = 0x2F;
	}
	else if(canTuner == 0x02)//36.125MHz
	{
		datax &= 0xF3;
		tmp[0] = 0x0D;tmp[1] = 0xE5;tmp[2] = 0x35;tmp[3] = 0x30;
	}
	else if(canTuner == 0x03)//36/167MHz
	{
		datax &= 0xF3;
		tmp[0] = 0x19;tmp[1] = 0x70;tmp[2] = 0x90;tmp[3] = 0x30;
	}
	else
	{
		datax &= 0xF3;
		tmp[0] = 0xCB;tmp[1] = 0x6B;tmp[2] = 0x28;tmp[3] = 0x2F;
	}
	if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x07, datax ))goto failed;

	if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x08, tmp[0]))goto failed;
	if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x09, tmp[1]))goto failed;
	if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x0A, tmp[2]))goto failed;
	if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x0B, tmp[3]))goto failed;

	if(canTuner != 0x00)
	{
		if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x26, 0x73))goto failed;
		if (LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x27, 0x91))goto failed;
	}

	return LGS_NO_ERROR;
failed:
	return LGS_CHANGE_MODE_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SelectXOFrequency(UINT8 is30400K)
{
/*	INT8 err;

	if( is30400K )
	{
		err = LGS8G75_WriteRegister(0x05, 0 );
		if (err != LGS_NO_ERROR)
			return err;
	}
	else
	{
		err = LGS8G75_WriteRegister(0x05, 4 );
		if (err != LGS_NO_ERROR)
			return err;
	}
*/
	is30400K = is30400K;
	return LGS_NO_ERROR;
}
LGS_RESULT LGS8G75_OpenTunerI2C(UINT8 tunerAddress)
{
    LGS_RESULT err = LGS_NO_ERROR;
    err = LGS8G75_WriteRegister(0x01,( tunerAddress>>1)| 0x80) ;
    return err;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

LGS_RESULT LGS8G75_CloseTunerI2C(void)
{
    UINT8 err = LGS_NO_ERROR;
    UINT8 registerData;
    err = LGS8G75_ReadRegister (0x01, &registerData);
    registerData &= 0x7F ;
    err = LGS8G75_WriteRegister(0x01, registerData);
    return err;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SetCarrierMode(UINT8 singleCarrier)
{
	LGS_RESULT err;
	UINT8 dat;
	printf("\r\n --LGS8G75_SetCarrierMode--");
	err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x19, &dat);
	if(err != LGS_NO_ERROR)		return err;

	if(singleCarrier)	// Single Carrier
	{
		dat |= 0x01;

		if( (err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x67, 0xAA) ))	return err;
	}
	else	//Multi Carrier
	{
		dat &= (~0x01);

		if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x67, 0x98)))	return err;
	}

	err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x19, dat);
	if (err != LGS_NO_ERROR)		return err;

	LGS8G75_SoftReset();
	return LGS_NO_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_Init()
{
	LGS_RESULT	err = LGS_NO_ERROR;
	const UINT8	*pb = LGS8G75_Data;
	UINT32		i;

	if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0xC6, 0x40 ))	goto failed;

	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x3D, 0x04)))	goto failed;
	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x39, 0x00)))	goto failed;

	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x3A, 0x00)) )	goto failed;
	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x38, 0x00)) )	goto failed;
	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x3B, 0x00)) )	goto failed;
	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x38, 0x00)) )	goto failed;

	for( i=0; i<sizeof(LGS8G75_Data); i++ )
	{
		if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x38, 0x00)) )			goto failed;
		if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x3A, (UINT8)(i&0xff))) )	goto failed;
		if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x3B, (UINT8)(i>>8))) )	goto failed;

		if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x3C, *pb)) )			goto failed;

		pb++;
	}

	if(( err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x38, 0x00)) )		goto failed;

    printf("\r\n2009-10-14 8g75 init ok ");

failed:
	return err;

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_GetParameters(DEMOD_PARAMETERS *pPara)
{
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		dat;

	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x0C, &dat)))		goto failed;
	pPara->GuardIntvl = dat & 0x03;

	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x19, &dat)))		goto failed;
	pPara->SubCarrier	= (dat & 0x38) >> 3;
	pPara->FecRate		= (dat & 0x06) >> 1;
	pPara->TimeDeintvl	= (dat & 0x40) >> 6;
	pPara->CarrierMode	= dat & 0x01;

	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x18, &dat)))		goto failed;
	pPara->PnNumber = dat & 0x01;

	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x30, &dat)))		goto failed;
	pPara->IsMpegClockInvert = (dat & 0x02) >> 1;
	pPara->DataOutput = dat & 0x01;

	pPara->AdcClock = 0x00;

failed:
	return err;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LGS_RESULT LGS8G75_SetParameters(DEMOD_PARAMETERS *pPara)
{
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		dat;

	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x0C, &dat)))		goto failed;
	dat &= (~0x03);
	if( pPara->GuardIntvl > 2 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->GuardIntvl;
	if((err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x0C, dat)))		goto failed;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x19, &dat)))		goto failed;

	dat &= 0x80;
	if( pPara->SubCarrier > 4 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->SubCarrier << 3;

	if( pPara->FecRate > 2 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->FecRate << 1;

	if( pPara->TimeDeintvl > 1 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->TimeDeintvl << 6;

	if( pPara->CarrierMode > 1 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->CarrierMode;

	if((err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x19, dat)))		goto failed;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x18, &dat)))		goto failed;
	dat &= (~0x01);

	if( pPara->PnNumber > 1 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->PnNumber;

	if((err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x18, dat)))		goto failed;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if((err = LGS8G75_SectionReadRegister(LGS8G75_SEC1_ADDR, 0x30, &dat)))		goto failed;
	dat &= (~0x03);

	if( pPara->IsMpegClockInvert > 1 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->IsMpegClockInvert << 1;

	if( pPara->DataOutput > 1 )	{ err = LGS_NO_DEFINE; goto failed; }
	dat |= pPara->DataOutput;

	if((err = LGS8G75_SectionWriteRegister(LGS8G75_SEC1_ADDR, 0x30, dat)))		goto failed;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	pPara->AdcClock = 0x00;

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	LGS8G75_SetCarrierMode( pPara->CarrierMode );

	if( (pPara->CarrierMode == 1) && (pPara->GuardIntvl == 1) )
	{
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x6E, 0x05 ))	goto failed;

		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x02 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x03 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3d, 0x05 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3E, 0x28 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x53, 0x80 ))	goto failed;
	}
	else
	{
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x6E, 0x3F ))	goto failed;

		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x39, 0x00 ))	goto failed;
		if(LGS8G75_SectionWriteRegister( LGS8G75_SEC1_ADDR, 0x3D, 0x04 ))	goto failed;
	}

failed:
	return err;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* end of LGS_8G75.c */
