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
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,

// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
// File Name: DrvAuTAS5707.c
// Description: TI I2S Audio Amplifier
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////
#define DRV_TAS5707_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Board.h"
#include "hwreg.h"
#include "datatype.h"
#include"drvIIC.h"
#include "GPIO.h"
#include "DevTAS5707.h"
#include "MApp_GlobalVar.h"
#include "msAPI_Timer.h"

#if (DIGITAL_I2S_SELECT==AUDIO_I2S_TAS5707)

#define TAS5707_ADDR     0x36
#define TAS5707_BUSID     (((U16) E_I2C_BUS_SYS << 8) | TAS5707_ADDR)

static TAS5707_REGMAP				sm_sRegImage;
#define __ENDTBL__         0xFF


#ifdef TAS_DEBUG
    #define TAS_MSG(x)      x
#else
    #define TAS_MSG(x)
#endif


static BOOLEAN si_dvTAS5707RegsRead(void)
{
    U8* pu8Buf;
    U8  cSubAddr[1];
    cSubAddr[0] = sm_sRegImage.ucAddr;
    pu8Buf = sm_sRegImage.sDatas;
    return MDrv_IIC_ReadBytes(TAS5707_BUSID, 1, cSubAddr, sm_sRegImage.ucNumber, pu8Buf);
}



static BOOLEAN si_dvTAS5707RegsWrite(void)
{
    U8 *pu8Buf;
    U8  cSubAddr[1];
    cSubAddr[0] = sm_sRegImage.ucAddr;
    pu8Buf = sm_sRegImage.sDatas;
    return MDrv_IIC_WriteBytes(TAS5707_BUSID,1,cSubAddr,sm_sRegImage.ucNumber,pu8Buf);
    /*while(sm_sRegImage.ucNumber>0)
    {
        sm_sRegImage.ucNumber--;
        pu8Buf[0] = sm_sRegImage.sDatas[i];
        result=MDrv_IIC_WriteBytes(TAS5707_BUSID,1,
                                    cSubAddr,
                                    1,
                                    pu8Buf);
        i++;
    }
    return result;*/
}



code TAS5707_REGMAP DrvTas5707InitTbl1[] =
{
	// Addr  Count   DataArrary
//wait 50ms here to let part acquiring lock
//01	(Below) 	DRC energy time(2ms)
{0x3A,  0x08,    {0x00, 0x01, 0x53,0x8F, 0x00, 0x7D, 0x2F ,0xD2}},
//01	(Below) 	DRC attack time(1ms)
{0x3B,  0x08,    {0x00, 0x02, 0xA3, 0x9A, 0x00, 0x7D, 0x2F, 0xD2}},
//01	(Below) 	DRC decay time(100ms)
{0x3C,  0x08,    {0x00, 0x00, 0x06, 0xD3, 0x00, 0x7F, 0xF9, 0x2B}},
//01	(Below) 	DRC threshold 1(-9.5dB£¬8.8W,THD+N=8.747%)
{0x40,  0x04,    {0xFD, 0xB5, 0x36, 0xF2}},
//01	(Below) 	DRC compression ratio£¨100£©
{0x41,  0x04,    {0x03, 0x81, 0x47, 0xAF}},
//01	(Below) 	DRC offset£¨0£©
{0x42,  0x04,    {0x00, 0x08, 0x42, 0x10}},
//01	(Below) 	DRC control
{0x46,  0x04,    {0x00, 0x00, 0x00, 0x01}},
//01	(Below) 	Bank switch control £¨no automatic bank switching)
{0x50,  0x04,    {0x0F, 0x70, 0x80, 0x00}},
//01	(Below) 	Input Mux Register(BD mode)
{0x20,  0x04,    {0x00, 0x89, 0x77, 0x7A}},
//01	(Below)	PWM Output MUX Register (Note: Writes to this register affect Inter-Channel Delay)
{0x25,  0x04,    {0x01, 0x02	, 0x13, 0x45}},
{0x07,  0x01,   {0x10}},	//Master Volume Register (0xFF = Mute)
{0x08,  0x01,   {0x30}},	//Channel 1 Volume
{0x09,  0x01,   {0x30}},	//Channel 2 Volume
{0x06,  0x01,   {0x00}},	//Soft Mute Register (mute off)
{0x03,  0x01,   {0xA0}},	//System Control Register 1(opt.)
{0x04,  0x01,   {0x05}},	//Serial Data Interface Register
{0x05,  0x01,   {0x00}},	//System Control Register 2(exit hard mute)
{0x0E,  0x01,   {0x91}},	//Micro Register(opt.)
{0x10,  0x01,   {0x02}},	//Modulation Limit(opt.)
{0x1A,  0x01,   {0x0A}},	//Split Capacitor Charge Period(opt.)
{0x1C,  0x01,   {0x02}},	//Back-end Error Register(opt.)
{0x11,  0x01,   {0xB8}},	//Inter-Channel Delay Channel 1
{0x12,  0x01,   {0x60}},	//Inter-Channel Delay Channel 2
{0x13,  0x01,   {0xA0}},	//Inter-Channel Delay Channel 3
{0x14,  0x01,   {0x48}},	//Inter-Channel Delay Channel 4
{__ENDTBL__,  0x00,   {0x00}},

};


BOOLEAN Drv_TAS5707_WRITE_DATAS(U8 ucSubAddr, U8 ucCnt, U8* pBufs )
{
    //U8* pu8Data;
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = ucSubAddr;
    sm_sRegImage.ucNumber = ucCnt;

    memcpy((U8*)&sm_sRegImage.sDatas[0],pBufs,ucCnt);

    bResult = si_dvTAS5707RegsWrite();

    if(bResult)
	{
        TAS_MSG(printf("\r \n Write 5707 Success!"));
	}
    else
	{
        TAS_MSG(printf("\r \n Write 5707 Fail!"));
	}

    return bResult;
}

BOOLEAN Drv_TAS5707_READ_DATAS(U8 ucSubAddr, U8 ucCnt, U8* pBufs )
{
    //U8* pu8Data;
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = ucSubAddr;
    sm_sRegImage.ucNumber = ucCnt;

    bResult = si_dvTAS5707RegsRead();

    memcpy(pBufs,(U8*)&sm_sRegImage.sDatas[0],ucCnt);

    if(bResult)
    {
        if(ucCnt == 1)
            printf("\r \n READ Data = %x",(U16)sm_sRegImage.sDatas[0]);
        else if(ucCnt == 4)
            printf("\r \n READ Data = %x, %x, %x, %x",(U16)sm_sRegImage.sDatas[0],
            (U16)sm_sRegImage.sDatas[1],(U16)sm_sRegImage.sDatas[2],(U16)sm_sRegImage.sDatas[3]);
        else if(ucCnt == 20){
            printf("\r \n READ Data = ");
            for(iu8Loop_i=0;iu8Loop_i<20;iu8Loop_i++)
            {
                 printf(" %x",(U16)sm_sRegImage.sDatas[iu8Loop_i]);
            }
        }
    }
    else
        printf("\r \n READ 5707 Fail!");

    return bResult;
}
/*void drvTAS5707_MuteSubwoof(BOOLEAN bMute)
{
    U8* pu8Buf;
    U8 u8Temp;

    MDrv_TAS5707_IIC_ReadBytes(TAS5707_BUSID,0x06,1,pu8Buf);
    u8Temp = *pu8Buf;
    sm_sRegImage.ucAddr=0x06;
    sm_sRegImage.ucNumber=1;

    if(bMute)
    {
	    sm_sRegImage.sDatas[0]= u8Temp|BIT5;
    }
    else
    {
    	sm_sRegImage.sDatas[0]= u8Temp&(~BIT5);
    }
    printf("\r\n[sDatas_Value]: %x",(U16)sm_sRegImage.sDatas[0]);
	si_dvTAS5707RegsWrite();
}
*/
void drvTAS5707_HWInit(void)
{

        Audio_Amplifier_ON();
        msAPI_Timer_Delayms(1);
       	I2S_Reset_High();
        msAPI_Timer_Delayms(5);
        I2S_Reset_Low();
        msAPI_Timer_Delayms(1);
        I2S_Reset_High();
}

void drvTAS5707_RegInit(void)
{
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr=0x1b;
    sm_sRegImage.ucNumber=1;
    sm_sRegImage.sDatas[0]=0;
    si_dvTAS5707RegsWrite();
    msAPI_Timer_Delayms(50);

    iu8Loop_i = 0;
    while(1)
	{
    	if(DrvTas5707InitTbl1[iu8Loop_i].ucAddr == __ENDTBL__)
		break;
        sm_sRegImage.ucAddr = DrvTas5707InitTbl1[iu8Loop_i].ucAddr;
        sm_sRegImage.ucNumber = DrvTas5707InitTbl1[iu8Loop_i].ucNumber;
        memcpy((U8*)&sm_sRegImage.sDatas[0],
            (U8*)(&DrvTas5707InitTbl1[iu8Loop_i].sDatas[0]),
            sm_sRegImage.ucNumber);
        bResult=si_dvTAS5707RegsWrite();
	    if(bResult)
		{
	        TAS_MSG(printf("\r \n dai Write 5707 Success!\n"));
		}
	    else
    	{
	        TAS_MSG(printf("\r \n dai Write 5707 Fail!\n"));
    	}
		++iu8Loop_i;
	}
    //drvTAS5707_Subwoof();
    if(bResult)
	{
        TAS_MSG(printf("\r \n dai Write 5707 Success!\n"));
	}
    else
	{
        TAS_MSG(printf("\r \n dai Write 5707 Fail!\n"));
	}
}

void drvTAS5707_Shutdown(void)
{
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = 0x05;
    sm_sRegImage.ucNumber = 1;
    sm_sRegImage.sDatas[0] = 0x40;

    bResult = si_dvTAS5707RegsWrite();

    if(bResult)
        printf("\r \n Write 5707 Success!");
    else
        printf("\r \n Write 5707 Fail!");

    msAPI_Timer_Delayms(700);
}
void drvTAS5707_Mute(BOOLEAN bmute)
{
    BOOLEAN bResult = FALSE;

    sm_sRegImage.ucAddr = 0x05;
    sm_sRegImage.ucNumber = 1;
    if(bmute)
    {
    ??
        Audio_Amplifier_OFF();
    	msAPI_Timer_Delayms(20);
        sm_sRegImage.sDatas[0] = 0x60;
    }
    else
    {
        sm_sRegImage.sDatas[0] = 0x00;
    	msAPI_Timer_Delayms(20);
        Audio_Amplifier_ON();
    }
    bResult = si_dvTAS5707RegsWrite();
}

void drvTAS5707_SW_Init(void)
{
    drvTAS5707_Shutdown();
    drvTAS5707_HWInit();
    msAPI_Timer_Delayms(20);
    drvTAS5707_RegInit();
}
void drvTAS5707_SourceVolSel(INPUT_SOURCE_TYPE_t enInputSourceType)
{
	switch(enInputSourceType)
	{

		case INPUT_SOURCE_VGA:

		case INPUT_SOURCE_TV:

#if (INPUT_AV_VIDEO_COUNT == 1)
		case INPUT_SOURCE_CVBS:
#elif (INPUT_AV_VIDEO_COUNT == 2)
		case INPUT_SOURCE_CVBS:
		case INPUT_SOURCE_CVBS2:

#elif (INPUT_AV_VIDEO_COUNT == 3)
		//case INPUT_SOURCE_CVBS:
		case INPUT_SOURCE_CVBS2:
		case INPUT_SOURCE_CVBS3:
#endif

#if (INPUT_SV_VIDEO_COUNT == 1)
		case INPUT_SOURCE_SVIDEO:
#elif (INPUT_SV_VIDEO_COUNT == 2)
		case INPUT_SOURCE_SVIDEO:
		case INPUT_SOURCE_SVIDEO2:
#endif

#if (INPUT_YPBPR_VIDEO_COUNT == 1)
		case INPUT_SOURCE_YPBPR:
#elif (INPUT_YPBPR_VIDEO_COUNT==2)
		case INPUT_SOURCE_YPBPR:
		case INPUT_SOURCE_YPBPR2:
#endif

#if (INPUT_SCART_VIDEO_COUNT == 1)
		case INPUT_SOURCE_SCART:
#elif (INPUT_SCART_VIDEO_COUNT == 2)
		case INPUT_SOURCE_SCART:
		case INPUT_SOURCE_SCART2:
#endif

#if (ENABLE_HDMI)
		case INPUT_SOURCE_HDMI:
#if (INPUT_HDMI_VIDEO_COUNT >= 2)
		case INPUT_SOURCE_HDMI2:
#endif
#if (INPUT_HDMI_VIDEO_COUNT >= 3)
		case INPUT_SOURCE_HDMI3:
#endif
#endif

//		case INPUT_SOURCE_VGA:

		case INPUT_SOURCE_DTV:
		case INPUT_SOURCE_JPEG:
		default:
		sm_sRegImage.ucAddr=0x07;
		sm_sRegImage.ucNumber=1;
		sm_sRegImage.sDatas[0]=0x0A;
		si_dvTAS5707RegsWrite();
		break;

		case  INPUT_SOURCE_STORAGE:
		sm_sRegImage.ucAddr=0x07;
		sm_sRegImage.ucNumber=1;
		sm_sRegImage.sDatas[0]=0x1A;
		si_dvTAS5707RegsWrite();
		break;
	}
}
#endif
#undef DRV_TAS5707_C


