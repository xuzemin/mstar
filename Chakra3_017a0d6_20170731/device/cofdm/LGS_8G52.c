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
*                        (c) copyright 2007,legendsilicon,beijing,China
*
*                                 All Rights Reserved
*
*
* File Name            : LGS8942.c
*
* Programmer(s)            : wangying
*
* Date Created            : 2007.07.25
*
* Date Updated            :
*
* Current Revision        : V1.0.0
*
* Modification History    :
*
* Description            :
*
***************************************************************************************/

/***************************************************************************************
*                                  INCLUDE FILES
***************************************************************************************/
#include "Board.h"
#ifdef CUS_HSS
#include "LGS_8G52_HSS.c"
#else
#include <stdarg.h>
#include <stdio.h>

#include "LGS_8G52.h"   //spelling error ZQ modify 090819
#include "drvIIC.h"		//spelling error ZQ modify 090819
//#include "MApp_Scan.h"
//#include "MApp_IR.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
U8 BCHData[4][2];
U8 BCHCount;

#define _DTMB_

#ifdef _DTMB_
BYTE LGS8G52_SelectTunerType(UINT8 canTuner)
{
	UINT8 datax;
	UINT8 tmp[4];
	if (LGS_ReadRegister(0x07, &datax)) goto failed;
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
	if (LGS_WriteRegister(0x07, datax ))goto failed;
	if (LGS_WriteRegister(0x09, tmp[0]))goto failed;
	if (LGS_WriteRegister(0x0A, tmp[1]))goto failed;
	if (LGS_WriteRegister(0x0B, tmp[2]))goto failed;
	if (LGS_WriteRegister(0x0C, tmp[3]))goto failed;
	return LGS_NO_ERROR;
failed:
	return LGS_CHANGE_MODE_ERROR;
}


#endif


#ifdef _DTMB_
const UINT8 LGS8G52_Data[] =
{
	0x01,0x30,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xE4,0xF5,0xA8,0xF5,0xB8,0xF5,0x88,0xF5,
	0x89,0xF5,0x87,0x75,0xD0,0x00,0x11,0x50,
	0x11,0x50,0xF4,0xF5,0x80,0xF5,0x90,0xF5,
	0xA0,0xF5,0xB0,0x75,0x81,0x30,0x80,0x01,
	0x32,0x90,0x80,0x12,0x74,0xFF,0xF0,0x90,
	0x80,0x13,0x74,0x1F,0xF0,0x90,0x80,0x23,
	0x74,0x01,0xF0,0x90,0x80,0x22,0xF0,0x90,
	0x00,0x48,0x74,0x00,0xF0,0x90,0x80,0x4D,
	0x74,0x05,0xF0,0x90,0x80,0x09,0xE0,0x60,
	0x21,0x12,0x00,0xDD,0x14,0x60,0x1B,0x12,
	0x00,0xDD,0x14,0x60,0x15,0x12,0x00,0xDD,
	0x14,0x60,0x0F,0x12,0x00,0xDD,0x14,0x60,
	0x09,0x12,0x00,0xDD,0x14,0x60,0x03,0x12,
	0x00,0xDD,0x90,0x80,0x42,0xE0,0x60,0x0B,
	0x14,0x60,0x0C,0x14,0x60,0x0D,0x14,0x60,
	0x0E,0x01,0xB3,0x74,0x04,0x01,0xB9,0x74,
	0x05,0x01,0xB9,0x74,0x07,0x01,0xB9,0x74,
	0x0A,0xC0,0xE0,0x74,0xC8,0x12,0x00,0xE2,
	0xD0,0xE0,0x14,0x70,0xF4,0x90,0x80,0x09,
	0xE0,0x70,0xAE,0x12,0x00,0xF6,0x12,0x00,
	0xFE,0x90,0x00,0x48,0xE0,0x04,0xF0,0x90,
	0x80,0x4E,0xF0,0x01,0x73,0x90,0x80,0x08,
	0xF0,0x22,0xF8,0x7A,0x0C,0x79,0xFD,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD9,
	0xF6,0xDA,0xF2,0xD8,0xEE,0x22,0x90,0x80,
	0x65,0xE0,0x54,0xFD,0xF0,0x22,0x90,0x80,
	0x65,0xE0,0x44,0xC2,0xF0,0x22
};

#else
const UINT8 LGS8G52_Data[] =
{
    0x01,0x30,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
    0xE4,0xF5,0xA8,0xF5,0xB8,0xF5,0x88,0xF5,
    0x89,0xF5,0x87,0x75,0xD0,0x00,0x11,0x50,
    0x11,0x50,0xF4,0xF5,0x80,0xF5,0x90,0xF5,
    0xA0,0xF5,0xB0,0x75,0x81,0x30,0x80,0x01,
    0x32,0x90,0x80,0x12,0x74,0xFF,0xF0,0x90,
    0x80,0x13,0x74,0x1F,0xF0,0x90,0x80,0x23,
    0x74,0x01,0xF0,0x90,0x80,0x22,0xF0,0x90,
    0x00,0x48,0x74,0x00,0xF0,0x90,0x80,0x4D,
    0x74,0x05,0xF0,0x90,0x80,0x09,0xE0,0x60,
    0x21,0x12,0x00,0xDD,0x14,0x60,0x1B,0x12,
    0x00,0xDD,0x14,0x60,0x15,0x12,0x00,0xDD,
    0x14,0x60,0x0F,0x12,0x00,0xDD,0x14,0x60,
    0x09,0x12,0x00,0xDD,0x14,0x60,0x03,0x12,
    0x00,0xDD,0x90,0x80,0x42,0xE0,0x60,0x0B,
    0x14,0x60,0x0C,0x14,0x60,0x0D,0x14,0x60,
    0x0E,0x01,0xB3,0x74,0x04,0x01,0xB9,0x74,
    0x05,0x01,0xB9,0x74,0x07,0x01,0xB9,0x74,
    0x0A,0xC0,0xE0,0x74,0xC8,0x12,0x00,0xE2,
    0xD0,0xE0,0x14,0x70,0xF4,0x90,0x80,0x09,
    0xE0,0x70,0xAE,0x12,0x00,0xF6,0x12,0x00,
    0xFE,0x90,0x00,0x48,0xE0,0x04,0xF0,0x90,
    0x80,0x4E,0xF0,0x01,0x73,0x90,0x80,0x08,
    0xF0,0x22,0xF8,0x7A,0x0C,0x79,0xFD,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xD9,
    0xF6,0xDA,0xF2,0xD8,0xEE,0x22,0x90,0x80,
    0x65,0xE0,0x54,0xFD,0xF0,0x22,0x90,0x80,
    0x65,0xE0,0x44,0xC2,0xF0,0x22
};
#endif
void LGS_Wait(U32 delay_cnt)
{
    MsOS_DelayTask(delay_cnt);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 LGS_ComputeSectionAddress(BYTE regAddr, BYTE *psecAddr)
{
    //Sect 1: 0x00 ~ 0xBF; Sect 2: 0xC0 ~ 0xFF , Jay
    if (regAddr >= 0x00 && regAddr <= 0xBF)
    {
        *psecAddr = LGS8g42ADDR ;
    }
    else if (regAddr >= 0xC0 && regAddr <= 0xFF)
    {
        *psecAddr = LGS8g42ADDR + 4;
    }
    else
        return LGS_REGISTER_ERROR;    //illegal register address

    return LGS_NO_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char LGS_WriteRegister(UINT8 regAddr, UINT8 regVal)
{
    UINT8 secAddr;
	U16 u16secAddr=regAddr;
    LGS_ComputeSectionAddress(regAddr, &secAddr);
    if( MDrv_IIC_WriteByte( u16secAddr, regAddr, regVal ) == FALSE )
    {
        return LGS_I2C_OPEN_ERROR;
    }
	else
	{
   		return LGS_NO_ERROR;
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char LGS_ReadRegister(UINT8 regAddr, UINT8 *pregVal)
{
      	UINT8 secAddr;
	  	U16 u16secAddr=regAddr;
	  
      	LGS_ComputeSectionAddress(regAddr, &secAddr);
        if(MDrv_IIC_ReadByte( u16secAddr, regAddr, pregVal ) == FALSE  )
        {
        	return LGS_I2C_OPEN_ERROR;
    	}
       else
		{
	        return LGS_NO_ERROR;
		}
}

char LGS8G52_SectionReadRegister(UINT8 secAddr, UINT8 regAddr, UINT8 *pregVal)
{
	  	U16 u16secAddr=secAddr;

     	if(MDrv_IIC_ReadByte( u16secAddr, regAddr, pregVal ) == FALSE  )
        {
        	return LGS_I2C_OPEN_ERROR;
    	}
       else
		{
        	return LGS_NO_ERROR;
		}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char  LGS8G52_SectionWriteRegister(UINT8 secAddr, UINT8 regAddr, UINT8 regVal)
{
	U16 u16secAddr=secAddr;

    if( MDrv_IIC_WriteByte( u16secAddr, regAddr, regVal ) == FALSE )
    {
        return LGS_I2C_OPEN_ERROR;
    }
    else
	{
        return LGS_NO_ERROR;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UINT8 LGS_SoftReset(void)
{
    char err = LGS_NO_ERROR;
    UINT8 dat;

    err = LGS_ReadRegister(0x02, &dat);
    if (err != LGS_NO_ERROR)
        return err;

    dat = dat & 0xFE;

    err = LGS_WriteRegister (0x02, dat);
    if (err != LGS_NO_ERROR)
        return err;

    dat = dat | 0x01;
    err = LGS_WriteRegister (0x02, dat);
    if (err != LGS_NO_ERROR)
        return err;

	LGS_Wait(400); // wait 5 ms, allows SNR, AGC, AFC and feedback loops to stabilize

    return LGS_NO_ERROR;
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char LGS_SelectADMode(UINT8 mode)
{
    char err = LGS_NO_ERROR;
    UINT8 datax;
    UINT8 datay;
    err = LGS_ReadRegister(0x07, &datax);
    if (err != LGS_NO_ERROR)
        return err;
    if (mode == INTERNAL_AD)
    {
        datay = 0;
        datax &= 0x7C;
    }
    else
    if (mode == EXTERNAL_AD)
    {
        datay = 0x40;
        datax |= 0x83;
    }
    err = LGS_WriteRegister(0xBA, datay );


    return LGS_WriteRegister(0x07, datax);
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char LGS_SetMpegMode(UINT8 serial, UINT8 clkPolarity, UINT8 clkGated)
{
    char err = LGS_NO_ERROR;
    UINT8 dat;

    err = LGS_ReadRegister (0xC2, &dat);
    if (err != LGS_NO_ERROR)
        return err;

    dat = dat & 0xF8;
    dat = dat | (serial & 0x01) | (clkPolarity & 0x02) | (clkGated & 0x04);

    err = LGS_WriteRegister (0xC2, dat);
    if (err != LGS_NO_ERROR)
        return err;

    err = LGS_SoftReset();
    if (err != LGS_NO_ERROR)
        return err;
    return LGS_NO_ERROR;
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 LGS_SetManualParameters(UINT8 datax)
{
    if(LGS_WriteRegister(0x7D, datax))    return LGS_SET_MANUAL_PARAMETERS_ERROR;
    LGS_SoftReset();
    return LGS_NO_ERROR;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char LGS_CheckLocked(void)
{
    /* returns true if demod CA locked and AFC Locked, false otherwise */
    char err = LGS_NO_ERROR;
    char i,j;
    UINT8 result;
    for(j=0;j<3;j++)
    {
        for(i=0;i<5;i++)
        {
            err = LGS_ReadRegister (0x4B, &result);
            if (err == LGS_NO_ERROR)
                break;
            MsOS_DelayTask(5);
        }
        if(i==5)
        {
            printf("8G52 I2C error!\n");
            return 0;
        }

        result = result & 0xC0;        /* Check Flag CA_Locked and AFC_Locked, Jay    */
        if (result == 0xC0)
        {
            result = 1;
            break;
        }
        else
        {
            result = 0;
        }
    }
	
    if(result == 0)
		printf("8G52 Unlock!\n");
	//else
		//printf("8G52 Locked!\n");
        return result;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

UINT8 LGS_SetManualMode(void)
{


    UINT8 datax,datay;
    if(LGS_ReadRegister(0x7E, &datax))    goto failed;
    datax &= 0xFE;
    if(LGS_WriteRegister(0x7E,datax ))    goto failed;

    //FEC self reset activated
    if(LGS_ReadRegister(0xC5, &datax))    goto failed;
    datax  = (datax & 0xE0) | 0x06;
    if(LGS_WriteRegister(0xC5, datax))    goto failed;
    if(LGS_ReadRegister(0x04, &datax))    goto failed;
    if(LGS_ReadRegister(0x7C, &datay))    goto failed;

    if( ((datax&0x03) == 0x01) && ((datay&0x80) == 0x80) )
    {
        LGS8G52_SectionWriteRegister( 0x36, 0x81, 0x02 );
        LGS8G52_SectionWriteRegister( 0x36, 0x81, 0x03 );
        LGS8G52_SectionWriteRegister( 0x36, 0x88, 0x05 );
    }
    else
    {
        LGS8G52_SectionWriteRegister( 0x36, 0x81, 0x00 );
        LGS8G52_SectionWriteRegister( 0x36, 0x88, 0x04 );
    }

    LGS_SoftReset();

    return LGS_NO_ERROR;
failed:
    return LGS_DETECT_ERROR;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// reg: 寄存器
// mask：掩码
// val：期望的正确值
// interval：每次循环之间的间隔
UINT8 WaitForLock( UINT8 reg, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times)
{
    UINT8    i = 0;
    UINT8    tmp;

    for( i=0; i<times; i++ )
    {
        LGS_Wait(interval);
        LGS_ReadRegister(reg, &tmp);


        if( (tmp & mask) == val )
        {
            *real_times = i;
            return true;
        }
    }
    *real_times = i;
    return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 LGS8G52_AutoDetect(void)
{
    UINT8 datax;
    UINT8 datay;
    char  i;
    UINT8 j;
    UINT8 k;
    UINT8 retryNum;
UINT8 lockresult;
	
    i = -1;
    j = 0;
    k = 0 ;

    retryNum = 0;

    if(LGS_WriteRegister(0x24, 0x1F )) goto failed;

    do
    {
        i++;

        if(LGS_ReadRegister( 0x04, &datax )) goto failed;
        if(LGS_ReadRegister( 0x37, &datay )) goto failed;
        datax &= 0xFC;
        switch( i%5 )
        {
            case 0: datay &= 0x7F; datax |= 0x02; break; // 945 VPN
            case 1: datay |= 0x80; datax |= 0x02; break; // 945 CPN

            case 2: datay &= 0x7F; datax |= 0x00; break; // 420 VPN
            case 3: datay |= 0x80; datax |= 0x00; break; // 420 CPN

            case 4: datay |= 0x80; datax |= 0x01; break; // 595 CPN

            default: datay &= 0x7F; datax |= 0x02;
        }
        if(LGS_WriteRegister(0x04, datax )) goto failed;
        if(LGS_WriteRegister(0x37, datay )) goto failed;
        LGS_SoftReset();
        #if  ( WATCH_DOG == ENABLE )   //(WDT_SWITCH || () )
                    msAPI_Timer_ResetWDT();
                #endif
           // MApp_DTVScan_ProcessUserInput();
               //if( Check_FlagofSkip()) return  LGS_DETECT_ERROR;
        switch( i%5 )
        {
            case 4:   LGS_Wait(300); break; // 595 CPN
            default:   break;
        }
              //  LGS_Wait(300);


#ifdef _DTMB_
                lockresult = WaitForLock( 0x4B, 0x80, 0x80, 1,10,&k);
		if( false == lockresult)  continue;
		if( 0xff == lockresult)  return (0xff);

                lockresult = WaitForLock( 0xA4, 0x03, 0x01, 5,20,&j);
		if( 0xff == lockresult)  return (0xff);
		if( false == lockresult)
#else
              if( false == WaitForLock( 0x4B, 0x80, 0x80, 10,20,&k))  continue;
        if( false == WaitForLock( 0xA4, 0x03, 0x01, 5,20,&j))
#endif
        {
            if(LGS_ReadRegister( 0x7C, &datax )) goto failed; //最高位为0：多载波   1:单载波
            if((datax & 0x80) == 0x80)
            {
                datax &= 0x7F;
                if(LGS_WriteRegister(0x24, 0x1F )) goto failed;
            }
            else
            {
                datax |= 0x80;

                if( 4 == i%5 )
                    if(LGS_WriteRegister(0x24, 0x05 )) goto failed;
            }
            if(LGS_WriteRegister(0x7C, datax )) goto failed;
            retryNum++;
            if (retryNum > 2)
            {
                retryNum = 0;
                continue;
            }
            i--;
            continue;
        }
        if(LGS_ReadRegister(0xA2, &datax))    goto failed;

        if(LGS_SetManualParameters(datax) != LGS_NO_ERROR)
            continue;

        break;

    } while( i<(5*2) );

    if(i == 5*2 )
    {
        goto failed;
    }

    return LGS_NO_ERROR;
failed:
    return LGS_DETECT_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////

UINT8 LGS_SetAutoMode(void)
{

//     set automode
    UINT8 datax;

    if(LGS_ReadRegister(0x03, &datax))    goto failed;
    datax &= 0xFE;
    if(LGS_WriteRegister(0x03, datax))    goto failed;

    if(LGS_ReadRegister(0x7E, &datax))    goto failed;
    datax |= 0x01;
    if(LGS_WriteRegister(0x7E, datax))    goto failed;

    //FEC self reset in never activated
    if(LGS_ReadRegister(0xC5, &datax))    goto failed;
    datax &= 0xE0;
    if(LGS_WriteRegister(0xC5, datax))    goto failed;

       if(LGS_WriteRegister(0xD9, 0x40 )) goto failed;
    //LGS_SoftReset();

      LGS8G52_SectionWriteRegister( 0x36, 0x81, 0x00 );
    LGS8G52_SectionWriteRegister( 0x36, 0x88, 0x04 );
    return LGS_NO_ERROR;
failed:
    return LGS_CHANGE_MODE_ERROR;
}
/*==============================================
/
/                About Tuner
/
//=============================================*/

char LGS_ComputeTunerRegister(UINT16 frequency,
                  UINT8 *ppd1,
                  UINT8 *ppd2,
                  UINT8 *pcb1,
                  UINT8 *pcb2,
                  UINT8 *pcb3a,
                  UINT8 *pcb3b)
{
    UINT16 tunerDivi;

    if (frequency >= 434 && frequency < 578) {
        *pcb2 = 0x94;
    }
    else if (frequency >= 578 && frequency < 650) {
        *pcb2 = 0xB4;
    }
    else if (frequency >= 650 && frequency < 746) {
        *pcb2 = 0xD4;
    }
    else if (frequency >= 746 && frequency <= 858) {
        *pcb2 = 0xF4;
    }
    else
        return LGS_FREQUENCY_ERROR; // illegal tuner frequency

    *pcb1  = 0xCA;
    *pcb3a = 0x8C;        // Search Mode
    *pcb3b = 0x84;        // Normal Mode

    //Npro = (freq + 36.1667)*24/4
    tunerDivi = (frequency*6) + 217;

    // now convert the tuner divider into the two tuner divider registers
    *ppd1 = (tunerDivi >> 8) & 0xFF;  // High byte
    *ppd2 = tunerDivi & 0xFF;         // Low  byte

    return LGS_NO_ERROR;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

UINT8 LGS_OpenTunerI2C(UINT8 tunerAddress)
{
    UINT8 err = LGS_NO_ERROR;
    err = LGS_WriteRegister(0x01,( tunerAddress>>1)| 0x80) ;
    return err;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

UINT8 LGS_CloseTunerI2C(void)
{
    UINT8 err = LGS_NO_ERROR;
    UINT8 registerData;
    err = LGS_ReadRegister (0x01, &registerData);
    registerData &= 0x7F ;
    err = LGS_WriteRegister(0x01, registerData);
    return err;
}
 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 LGS_SetCarrierMode(UINT8 mode)
{
    UINT8 err;
    UINT8 dat;
    err = LGS_ReadRegister(0x7C, &dat);
    if (err) return err;
    if (mode ==  SINGLE_CARRIER)
        dat |= 0x80;
    else if(mode == MULTI_CARRIER)
        dat &= 0x7f;
    err = LGS_WriteRegister(0x7C, dat);
    if (err) return err;
    LGS_SoftReset();
    return LGS_NO_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char LGS8G52_SelectADMode(UINT8 extAd)
{
    S8 err = LGS_NO_ERROR;
    U8 datax;
    U8 datay;

    err = LGS_ReadRegister(0x07, &datax);
    if (err != LGS_NO_ERROR)
        return err;

    if (extAd == 0x00) //INTERNAL_AD
    {
        datay = 0;
        datax &= 0x7C;
    }
    else if (extAd == 0x01) //EXTERNAL_AD
    {
        datay = 0x40;
        datax |= 0x83;
    }

    err = LGS_WriteRegister(0xBA, datay );
    if (err != LGS_NO_ERROR)
        return err;

    err = LGS_WriteRegister(0x07, datax);
    if (err != LGS_NO_ERROR)
        return err;

    return LGS_NO_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 LGS8G52_SetAutoMode(void)
{
    //set automode
    U8 datax;

    if(LGS_ReadRegister(0x03, &datax))    goto failed;
    datax &= 0xFE;
    if(LGS_WriteRegister(0x03, datax))    goto failed;

    if(LGS_ReadRegister(0x7E, &datax))    goto failed;
    datax |= 0x01;
    if(LGS_WriteRegister(0x7E, datax))    goto failed;

    //FEC self reset in never activated
    if(LGS_ReadRegister(0xC5, &datax))    goto failed;
    datax &= 0xE0;
    if(LGS_WriteRegister(0xC5, datax))    goto failed;

    if(LGS_WriteRegister(0xD9, 0x40 )) goto failed;

    //LGS8G52_SoftReset();
    LGS8G52_SectionWriteRegister( 0x36, 0x81, 0x00 );
    LGS8G52_SectionWriteRegister( 0x36, 0x88, 0x04 );

    return LGS_NO_ERROR;
failed:
    return LGS_CHANGE_MODE_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT8 LGS_AutoDetect(void)
{
    U8 datax;
    U8 datay;
    S8  i;
    U8 j;
    U8 k;

    j = 0;
    k = 0;
    i = -1;

       if(LGS_ReadRegister( 0x7C, &datax )) goto failed; //最高位为0：多载波   1:单载波
       datax &= 0x7F;
       if(LGS_WriteRegister(0x24, 0x1F )) goto failed;

       if(LGS_WriteRegister(0x7C, datax )) goto failed;

    do
    {
        i++;

        if(LGS_ReadRegister( 0x04, &datax )) goto failed;
        if(LGS_ReadRegister( 0x37, &datay )) goto failed;
        datax &= 0xFC;
        switch( i%5 )
        {
            case 0: datay &= 0x7F; datax |= 0x02; break; // 945 VPN
            case 1: datay |= 0x80; datax |= 0x02; break; // 945 CPN

            case 2: datay &= 0x7F; datax |= 0x00; break; // 420 VPN
            case 3: datay |= 0x80; datax |= 0x00; break; // 420 CPN

            case 4: datay |= 0x80; datax |= 0x01; break; // 595 CPN

            default: datay &= 0x7F; datax |= 0x02;
        }
        if(LGS_WriteRegister(0x04, datax )) goto failed;
        if(LGS_WriteRegister(0x37, datay )) goto failed;
          LGS_SoftReset();

        if( false == WaitForLock( 0x4B, 0x80, 0x80, 1,10,&k))  continue;
        if( false == WaitForLock( 0xA4, 0x03, 0x01, 5,20,&j))
        {
            i--;
            continue;
        }
        if(LGS_ReadRegister(0xA2, &datax))    goto failed;

        if(LGS_SetManualParameters(datax) != LGS_NO_ERROR)
            continue;

        break;

    } while( i<(5*2) );

    if(i == 5*2 )
    {
        goto failed;
    }

    return LGS_NO_ERROR;
failed:
    return LGS_DETECT_ERROR;
}

UINT8 LGS8G52_ReadType(void)
{
     U8 datax;

      if(LGS_ReadRegister(0xA2, &datax)==LGS_NO_ERROR) return datax;
      else     return 0;
}

UINT8 LGS8G52_ReadCarrier(void)
{
     U8 datax,i;
     for (i = 0; i<5; i++)
    {
      if(LGS_ReadRegister(0x7C, &datax)==LGS_NO_ERROR)
    {
       datax=datax&0x80;
       if(datax)
                return SINGLE_CARRIER  ;  //multi carrier
       else
         return MULTI_CARRIER ; //single carrier
          }
    }
          return 0xFF;
}

char  LGS8G52_Init(void)
{
    char    err = LGS_NO_ERROR;
    UINT8    *pb = LGS8G52_Data;
    UINT16  i;
	
//    if( err = LGS8G52_SectionWriteRegister(0x36, 0x88, 0x00) )    goto failed;
    if( err != LGS8G52_SectionWriteRegister(0x36, 0x81, 0x00) )    goto failed;

    if( err != LGS8G52_SectionWriteRegister(0x36, 0x82, 0x00) )    goto failed;
    if( err != LGS8G52_SectionWriteRegister(0x36, 0x80, 0x00) )    goto failed;
    if( err != LGS8G52_SectionWriteRegister(0x36, 0x83, 0x00) )    goto failed;
    if( err != LGS8G52_SectionWriteRegister(0x36, 0x80, 0x00) )    goto failed;

    for( i=0; i<sizeof(LGS8G52_Data); i++ )
    {
        if( !err = LGS8G52_SectionWriteRegister(0x36, 0x80, 0x00) )        goto failed;
        if( !err = LGS8G52_SectionWriteRegister(0x36, 0x82, (UINT8)(i&0xff)) )    goto failed;
        if( !err = LGS8G52_SectionWriteRegister(0x36, 0x83, (UINT8)(i>>8)) )    goto failed;

        if( err != LGS8G52_SectionWriteRegister(0x36, 0x84, *pb) )        goto failed;
        pb++;
    }

    if( err! = LGS8G52_SectionWriteRegister(0x36, 0x80, 0x00) )        goto failed;

	return LGS_NO_ERROR;
#ifdef _DTMB_
    LGS8G52_SelectTunerType(0x03);
	//printf("LGS8g52-----------------init-----------------------------\n");
#endif
failed:
    return LGS_I2C_OPEN_ERROR;
}


UINT8 LGS8G52_ReadIntension(void)
{
  U8 datax,datay;
  U16 Signalintension;

//  for(i=0;i<3;i++)
  {
    Signalintension=0;
    if( LGS_ReadRegister(0x3F, &datax)!=LGS_NO_ERROR) return 0x0;
    if( LGS_ReadRegister(0x3E, &datay)!=LGS_NO_ERROR) return 0x0;
    Signalintension|=datax;
    Signalintension=(Signalintension<<8)|datay;
  }
#ifdef _DTMB_
  printf("\n datax=%bx",datax);

  if(!LGS_CheckLocked()) return 0;

   datay=LGS8G52_ReadMastick();
   if(datay==1&&datax<=0x1D) return 0;

  if(datax==0x00)  return 1;
  else if(datax<=0x1D) return 5;
  else if(datax<=0x1e)return 4;
  else if(datax<=0x1F)return 3;
  else return 2;

#else
  if(Signalintension<0x100)    return 0;
  else if(Signalintension<0x190) return 5;
  else if(Signalintension<0x2a8) return 4;
  else if(Signalintension<0x381) return 3;
  else if(Signalintension<0x400) return 2;
  else return 1;
#endif

}

UINT8 LGS8G52_ReadMastick(void)
{
  U32 BCH_TPACK, BCH_EPACK,BER;
  U8 datax1,datax2,datax3,datax4;


  LGS_WriteRegister(0xC6,0x01);

  LGS_WriteRegister(0xC6,0x41);

  LGS_WriteRegister(0xC6,0x01);

  LGS_Wait(70);

  LGS_WriteRegister(0xC6,0x81);

  LGS_ReadRegister(0xD0, &datax4);
  LGS_ReadRegister(0xD1, &datax3);
  LGS_ReadRegister(0xD2, &datax2);
  LGS_ReadRegister(0xD3, &datax1);

    BCH_TPACK =(U32)datax1<<24+(U32)datax2<<16+(U32)datax3<<8+datax4;

    LGS_Wait(5);
    LGS_ReadRegister(0xD4, &datax4);
    LGS_ReadRegister(0xD5, &datax3);
    LGS_ReadRegister(0xD6, &datax2);
    LGS_ReadRegister(0xD7, &datax1);

    BCH_EPACK =(U32)datax1<<24+(U32)datax2<<16+(U32)datax3<<8+datax4;

#ifdef _DTMB_
    BER=100*BCH_EPACK/BCH_TPACK;
#else
    BER=10000*BCH_EPACK/BCH_TPACK;
#endif

    if( BCH_TPACK!=0)
        {
         if(BER==0)      return 5;
        else if (BER ==1) return 4;
        else if(BER<4) return 3;
        else if(BER <10) return 2;
        else return 1;
        }
    else  return 1;
}

BOOLEAN Set_CheckSignalCarrire(void)
{
  U8 datax;


  LGS_ReadRegister(0x7C,&datax);

  if(!(datax&0x80))  return TRUE ;


  LGS_WriteRegister(0xC6,0x00);

  LGS_WriteRegister(0xC6,0x40);

  LGS_WriteRegister(0xC6,0x00);
  BCHCount=0;

}

BOOLEAN  CheckSignalCarrire(void)
{
  U8 datax, datax1,datax2,datax3,datax4;

  LGS_ReadRegister(0x7C,&datax);

  if(!(datax&0x80))  return TRUE ;

/*
  LGS_WriteRegister(0xC6,0x00);

  LGS_WriteRegister(0xC6,0x40);

  LGS_WriteRegister(0xC6,0x00);
  LGS_Wait(2000);
  */
  LGS_WriteRegister(0xC6,0x80);

  LGS_ReadRegister(0xD0, &datax1);
  LGS_ReadRegister(0xD1, &datax2);
  LGS_ReadRegister(0xD2, &datax3);
  LGS_ReadRegister(0xD3, &datax4);

   switch(BCHCount)
   {
       case 0: BCHData[0][0]= datax1; BCHData[0][1]= datax2;  BCHCount++;break;
    case 1: BCHData[1][0]= datax1; BCHData[1][1]= datax2;  BCHCount++;break;
    //case 2: BCHData[2][0]= datax1; BCHData[2][1]= datax2;  BCHCount++;break;
    //case 3: BCHData[3][0]= datax1; BCHData[3][1]= datax2;  BCHCount++;break;
       default: BCHCount=0; break;
   }

  if(BCHCount==2)
 {  if((BCHData[0][0]==BCHData[1][0])&& (BCHData[0][1]==BCHData[1][1]))
  return FALSE;
  else   return TRUE;
  }
  else return TRUE;
}

UINT8 LGS8G52_ReadMode(void)
{
       U8 datax=0;
      if(LGS_ReadRegister(0x7D, &datax)==LGS_NO_ERROR)
       return   datax;
      else
      return LGS_I2C_READ_ERROR;

}

UINT8 LGS8G52_ReadPN(void)
{
     U8 datax=0;
      if(LGS_ReadRegister(0x04, &datax)==LGS_NO_ERROR)
       return   datax;
      else
      return LGS_I2C_READ_ERROR;
}
UINT8 LGS8G52_ReadPNFLIP(void)
{
    U8 datax=0;
      if(LGS_ReadRegister(0x37, &datax)==LGS_NO_ERROR)
       return   datax;
      else
      return LGS_I2C_READ_ERROR;
}
UINT8 LGS8G52_SetMode(U8 datax)
{

      if(LGS_WriteRegister(0x7D, datax)==LGS_NO_ERROR)
       return   LGS_NO_ERROR;
      else
      return LGS_I2C_WRITE_ERROR;

}

UINT8 LGS8G52_SetPN(U8 datax)
{
      if(LGS_WriteRegister(0x04, datax)==LGS_NO_ERROR)
       return   LGS_NO_ERROR;
      else
      return LGS_I2C_WRITE_ERROR;
}
UINT8 LGS8G52_SetPNFLIP(U8 datax)
{
      if(LGS_WriteRegister(0x37, datax)==LGS_NO_ERROR)
       return   LGS_NO_ERROR;
      else
      return LGS_I2C_WRITE_ERROR;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif
/* end of lgs8g42.c */
