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
/******************************************************************************
 Copyright (c) 2004 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DevI2S.c
 [Date]:        26-June-2006
 [Comment]:
   Digital Audio subroutines.
 [Reversion History]:
*******************************************************************************/

#define _DEVAUDIO_I2S_
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "DevI2S_STA333.h"

/* This is the reference source code of STA323W */
//SOUND 2.0 CHANNALE,speaker=8o,9w
#define CHANNEL1_CFG_VAL  0x10//0x00//0x08
#define CHANNEL2_CFG_VAL  0x50//0x40//0x48
#define CHANNEL3_CFG_VAL  0x80
#define MAIN_VOLUME_VAL   0x0A;//0x10;//0x18//0x1A//0x1d//0x1C

void DevI2s_STA333_Init(void)
{
	U8 I2C_buf1;

/* the master clock select 0x62 = 384fs,0x63 = 256fs,0x64 = 128fs fault detect enable */
	I2C_buf1=0x63;//0x64;
/* the first parameter is the number that how many registers will be written
   the second parameter is the address that the variable
   the third parameter is the DDX chip address
   the fourth parameter is the begining register address */
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_A,I2C_buf1);

/* the serial input format select, I2s format, MSB first*/
	I2C_buf1=0x80;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_B,I2C_buf1);

/* Use default output mode*/
	I2C_buf1=0x9F;//0x97;//0x22;//c2;//0x42;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_C,I2C_buf1);

/* High pass enbale, No De-emphasis, No DSP by pass, Anti-Clipping Mode*/
	I2C_buf1=0x70;//0x50; //0x40;//0x00;58
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_D,I2C_buf1);

/* Use standard MPC, AM mode disable, normal output speed*/
	I2C_buf1=0xc2;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_E,I2C_buf1);

/*	let the EAPD high, 2 DDX channel, invalid detect disable, Auto EAPD on disable*/
	I2C_buf1=0xc0;//0x5D;//0xDC;//0xC0;//MODIFIED_BY_HHH 071206
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_F,I2C_buf1);

/*	main and channel mute*/
	I2C_buf1=0x00;//0x46;//0x06;//0x10;//0x11;//0x06:mute ch1,ch2     0x00:clear mute	//MODIFIED_BY_HHH 071206
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE,I2C_buf1);

/* Preset EQ, user defined pre-scale*/
	I2C_buf1=0x80;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_AUTO1,I2C_buf1);

/* Switching frequency determined by AMAM setting*/
	I2C_buf1=0x00;//0xf0;//0xA0;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_AUTO2,I2C_buf1);

/* flat mode EQ*/
	I2C_buf1=0x00;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_AUTO3,I2C_buf1);

/* channel1 mapped to limiter 1, tone and treble control bypass*/
    I2C_buf1=CHANNEL1_CFG_VAL;//0x08;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG,I2C_buf1);

/* channel2 mapped to limiter 1, tone and treble control bypass*/
    I2C_buf1=CHANNEL2_CFG_VAL;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG,I2C_buf1);

/* channel3 mapped to limiter 2, tone and treble control enable*/
	I2C_buf1=0x77;//0x20;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_TONEBASS,I2C_buf1);
	
/* tone and treble are 0 dB*/
	I2C_buf1=CHANNEL3_CFG_VAL;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG,I2C_buf1);

/* Limiter1 attack and rease rate*/
	I2C_buf1=0x6a;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L1AR_RATE,I2C_buf1);

/* Limiter1 attack and rease threshold*/
	I2C_buf1=0x4b;//0x69;//0x9c;//0x8c; 
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L1AR_THRESHOLD,I2C_buf1);

/* Limiter2 attack and rease rate*/
	I2C_buf1=0x6a;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L2AR_RATE,I2C_buf1);

/* Limiter2 attack and rease threshold*/
	I2C_buf1=0x69;//0x9d;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_L2AR_THRESHOLD,I2C_buf1);
	
/*	initiate the volume, volume = 20 */
	I2C_buf1= MAIN_VOLUME_VAL;//0x30;//0x10;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME,I2C_buf1);

	I2C_buf1=0x30;//lcf 80203 0x2a; //0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_VOL,I2C_buf1);
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_VOL,I2C_buf1);
	I2C_buf1= 0x2a;//lcf 80203 0x26;////0x18;beicl 080131
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_VOL,I2C_buf1);

//	I2C_buf1=0x60;
//    MDrv_IIC_WriteByte(STA333_ADDR,DDX_LEFT_VOL,I2C_buf1);
//	I2C_buf1=0x60;
//    MDrv_IIC_WriteByte(STA333_ADDR,DDX_RIGHT_VOL,I2C_buf1);
/* alrough there is not the subwoofer channel for some configuration,
	I still have its source code for the reference*/
//	I2C_buf1=0x48;
//    MDrv_IIC_WriteByte(STA333_ADDR,DDX_SUBWOOFER_VOL,I2C_buf1);

#if (ENABLE_WALL_MODE)
    DevI2SSetCFTableByMode(WALL_MODE1);
#else
    DevI2S_STA333_SetCFTable();//jazzy 071130 update for TCL
#endif

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE,0x40);//clear mute

}


//===================
U8 MVolSave;
//==================
//New Version for mute
//=================
void STA333_DDX_Mute_New(void)
{
	printf("\r\n Mute",0);
    
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME ,0xFE);//set Master Volume as 0xFE
    msAPI_Timer_Delayms(5);
}

//==================
//New Version for unmute
//=================
void STA333_DDX_UnMute_New(void)
{   
    U8 Tempdata1,Tempdata2,Tempdata3,Tempdata;
	U8 I2C_buf1;

	printf("\r\n UnMute",0);

    MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL1_CFG,&Tempdata1 );//Read and save the Limmit setting
    MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL2_CFG,&Tempdata2 );
    MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL3_CFG,&Tempdata3 );

    Tempdata=Tempdata1&0xCF;								//clear the CxLSx bit as 00
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,Tempdata);
    Tempdata=Tempdata2&0xCF;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,Tempdata);
    Tempdata=Tempdata3&0xCF;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,Tempdata);
    msAPI_Timer_Delayms(2);//10-20ms delay

    Tempdata=Tempdata1|0x10;								//Set the CxLSx bit as 01
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,Tempdata);
    Tempdata=Tempdata2|0x10;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,Tempdata);
    Tempdata=Tempdata3|0x10;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,Tempdata);
    msAPI_Timer_Delayms(2);//10-20ms delay

    Tempdata=Tempdata1&0xCF;								//clear the CxLSx bit as 00
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,Tempdata);
    Tempdata=Tempdata2&0xCF;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,Tempdata);
    Tempdata=Tempdata3&0xCF;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,Tempdata);
    msAPI_Timer_Delayms(2);//10-20ms delay

    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,Tempdata1);//Restore the limiter setting
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,Tempdata2);
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,Tempdata3);
    //MDrv_IIC_WriteByte(STA333_ADDR,DDX_REG_MVOL ,MVolSave); //restore the Master volume
    I2C_buf1 = MAIN_VOLUME_VAL;
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME,I2C_buf1);
    msAPI_Timer_Delayms(20);//10-20ms delay
        
}

#if(ENABLE_WALL_MODE)
code U8  tEQAddrtable[] = {0x00, 0x05, 0x0A, 0x0F};

code U8 tCFtable[][3]=
{

//mode1 value hang

//0x00
	{0x80,0x4B,0xC0},{0x7F,0xB4,0x40},{0x7F,0xB4,0x29},{0x80,0x97,0x53},{0x3F,0xDA,0x20},    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.997688)
//0x05
	{0x9C,0x07,0xFC},{0x60,0xFE,0x33},{0x63,0xF8,0x04},{0xAD,0xC5,0xEC},{0x38,0x9D,0xF0},    // 48KFs, Biquad2, Address: 0x05~0x09 (stability: 0.801497)
//0x0A
	{0xD4,0x13,0x7F},{0x44,0x1A,0xCF},{0x2B,0xEC,0x81},{0xE1,0xE0,0xDA},{0x2D,0x02,0x2B},    // 48KFs, Biquad3, Address: 0x0A~0x0E (stability: 0.485104)
//0x0F
	{0x80,0xF1,0xAC},{0x7E,0x7E,0xC2},{0x7F,0x0E,0x54},{0x81,0xD8,0x6A},{0x3F,0xD4,0x6A},    // 48KFs, Biquad4, Address: 0x0F~0x13 (stability: 0.000000)

//mode1 value table

 //0x00
	{0x80,0x4B,0xC0},{0x7F,0xB4,0x40},{0x7F,0xB4,0x29},{0x80,0x97,0x53},{0x3F,0xDA,0x20},    // 48KFs, Biquad1, Address: 0x00~0x04 (stability: 0.997688)
//0x05
	{0x9C,0x07,0xFC},{0x60,0xFE,0x33},{0x63,0xF8,0x04},{0xAD,0xC5,0xEC},{0x38,0x9D,0xF0},    // 48KFs, Biquad2, Address: 0x05~0x09 (stability: 0.801497)
//0x0A
	{0xD4,0x13,0x7F},{0x44,0x1A,0xCF},{0x2B,0xEC,0x81},{0xE1,0xE0,0xDA},{0x2D,0x02,0x2B},    // 48KFs, Biquad3, Address: 0x0A~0x0E (stability: 0.485104)
//0x0F
	{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x00,0x00,0x00},{0x40,0x00,0x00},    // 48KFs, Biquad4, Address: 0x0F~0x13 (stability: 0.000000)
};

void  DevI2SSetCFTableByMode(SoundWallModeType  mode)  
{
    U8 i,j,ucIndex;
    U8 u8Temp;

    ucIndex = MDrv_IIC_ReadByte(STA333_ADDR,DDX_CONFIGURE_D,&u8Temp );
    MDrv_IIC_WriteByte(STA333_ADDR,DDX_CONFIGURE_D ,(u8Temp |0x10));//channel1,channel2 use same filter coefficient

    for(ucIndex = 0;ucIndex< sizeof(tEQAddrtable);ucIndex++)
    {
        MDrv_IIC_WriteByte(STA333_ADDR,REG_CFADDR1,tEQAddrtable[ucIndex]);
        for(j = 0;j<5;j++)
        {
            for(i = 0;i<3;i++)
            {
    		  MDrv_IIC_WriteByte(STA333_ADDR, (U8)(REG_B1CF1 + i+ 3*j), tCFtable[(j+5*ucIndex)+mode*20][i]);
            }
        }
        MDrv_IIC_WriteByte(STA333_ADDR,REG_CFUD ,0x02);
    	MDrv_IIC_WriteByte(STA333_ADDR,REG_CFUD ,0x02);
        MDrv_IIC_WriteByte(STA333_ADDR,REG_CFUD ,0x02);

    }
}
#endif
/*
void DecI2S_STA333_Patch(U8 ucCtl)
{
    U8 ucTmp;
    U8 u8Temp;
    printf("\r\nDecI2SPatch(%d)",ucCtl);
     if(ucCtl)
     {
        //ClrPinAudioMute();
        //Delay1ms(5);
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR,DDX_MUTE,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE ,(ucTmp |_BIT0));
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME, 0xFE);
        //SetPinAudioMute();
     }
     else
     {
        //ClrPinAudioMute();
        //Delay1ms(5);
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL1_CFG,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,(ucTmp&(~_BIT4)&(~_BIT5)));
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL2_CFG,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,(ucTmp&(~_BIT4)&(~_BIT5)));
        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CHANNEL3_CFG,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,(ucTmp&(~_BIT4)&(~_BIT5)));

        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL1_CFG ,CHANNEL1_CFG_VAL);
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL2_CFG ,CHANNEL2_CFG_VAL);
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_CHANNEL3_CFG ,CHANNEL3_CFG_VAL);
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MAIN_VOLUME, MAIN_VOLUME_VAL);

        ucTmp = MDrv_IIC_ReadByte(STA333_ADDR,DDX_MUTE,&u8Temp );
        MDrv_IIC_WriteByte(STA333_ADDR,DDX_MUTE ,(ucTmp &(~_BIT0)));
        //SetPinAudioMute();
     }
}

BOOL STA333_GetPowerDNStatus(void) 
{
	U8 Temp[3];
       U8 u8Temp;
	Temp[0] = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CONFIGURE_A,&u8Temp );
	Temp[1] = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CONFIGURE_B,&u8Temp );
	Temp[2] = MDrv_IIC_ReadByte(STA333_ADDR, DDX_CONFIGURE_C,&u8Temp );
    if((Temp[0]==63)&&(Temp[0]==80)&&(Temp[0]==97))
        return TRUE;
    else
        return FALSE;
}
*/
