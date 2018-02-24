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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
////////////////////////////////////////////////////////////////////////////////

#define VA1G5BF8010_C
#ifndef SHARP_C
#define SHARP_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "COFDM_Demodulator.h"
#include "VA1G5BF8010.h"

#define  Tuner_VA1G5BF8010_DBG(x)  //x

static FREQSTEP m_eFrequencyStep;

#define _ATV_TUNER_I2C_ID     0xc2
#define _DTV_DEMODE_I2C_ID     0x30

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_50KHz;
        break;
    }
}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
     BYTE cTunerData[6];
     DWORD freq;
     U8 CP210;
    //printf("8010 ---> devTunerSetPLLData() \n");
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);

    //** Byte-4: (R0~R2), Bit7 fix to 1, Bit8 fixe to 1
#if ( TN_FREQ_STEP == FREQ_STEP_50KHz )
      cTunerData[2] = 0xC3;
#else  //142.86KHz
      cTunerData[2] = 0xC1;
#endif

    //** Byte-5: (BS1~BS4) = (Bit0 ~ Bit3)
    if(eBand == E_RFBAND_VHF_LOW)
          cTunerData[3] = 0x01;
    else if (eBand == E_RFBAND_VHF_HIGH)
        cTunerData[3] = 0x02;
    else
        cTunerData[3] = 0x04;
       //For ATV: BS4 =1 (Bit3)
       cTunerData[3]|=0x08;
       //CP Value(CP0~CP2) = (Bit5 ~ Bit7)
       freq = (DWORD)( ( (DWORD)wPLLData*50 ) );
       CP210 = 4; //Set Default to avoid compiler warning
    if(freq<161000)
    {
        if(freq<153000)
            CP210=4;
        else
            CP210=5;
    }
    else if( (freq>=161000) && (freq<426000) )
    {
        if(freq<233000)
            CP210=3;
        else if( (freq<343000) && (freq>=233000) )
            CP210=5;
        else
            CP210=7;
    }
    else if(freq>=426000)
    {
        if(freq<463000)
            CP210=3;
        else if(freq<563000 && freq>=463000)
            CP210=4;
        else if(freq<613000 && freq>=563000)
            CP210=5;
        else if(freq<713000 && freq>=613000)
            CP210=6;
        else
            CP210=7;
    }

    cTunerData[3] &= 0x1F;
    cTunerData[3] |= ((CP210<<5)&0xE0);

    //** Byte-4:AL0 ~ AL2(Bit0~Bit2), ATV = 0x06;
    // Bit-3:ATC => 0:Normal mode, 1:Search mode
    // Bit7: Fix to 1
       cTunerData[4] =0x86;//0x86 => Normal mode 0xE0 => Search mode


    Tuner_VA1G5BF8010_DBG(printf("Tuner8010: ATV  Tuner: %bx,  %bx,  %bx,  %bx \n ", cTunerData[0], cTunerData[1], cTunerData[2], cTunerData[3], cTunerData[4]));
    devCOFDM_PassThroughI2C_WriteBytes(_ATV_TUNER_I2C_ID, 0, NULL, 5, cTunerData);

}

void devTunerInit(void)
{
    BYTE cTunerData[5];
       U8 u8add;
    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    Tuner_VA1G5BF8010_DBG(printf("Tuner8010: devTunerInit() \n"));
    //To Init the register define from spec
    //<1>. Register-0x01 = 0x40
        cTunerData[0]=0x40;
        u8add = 0x01;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);
    //<2>. Register-0x11 = 0x21 //Only for Air 3ch
       // cTunerData[0]=0x21;
       // u8add = 0x11;
       // MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);
    //<3>. Register-0x22 = 0x83
        cTunerData[0]=0x83;
        u8add = 0x22;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);
    //<4>. Register-0x30,31,32 = 0x20,11,22
        cTunerData[0]=0x20;
        cTunerData[1]=0x11;
        cTunerData[2]=0x22;
        u8add = 0x30;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 3, cTunerData);
    //<5>. Register-0x5F = 0x80
        cTunerData[0]=0x80;
        u8add = 0x5F;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);

//** To disable TS
        cTunerData[0]=0x00;
        cTunerData[1]=0x00;
        u8add = 0x1E;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 2, cTunerData);

}

#define DIGITAL_TUNER_IF    44.000//36.166



void devDigitalTuner_Init()//B:??? Need to implement it
{
    BYTE cTunerData[5];
       U8 u8add;

  Tuner_VA1G5BF8010_DBG(printf("Tuner8010: devDigitalTuner_Init() \n"));
    //To Init the register define from spec
    //<1>. Register-0x01 = 0x40
        cTunerData[0]=0x40;
        u8add = 0x01;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);
    //<2>. Register-0x11 = 0x21 //Only for Air 3ch
       // cTunerData[0]=0x21;
       // u8add = 0x11;
       // MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);
    //<3>. Register-0x22 = 0x83
        cTunerData[0]=0x83;
        u8add = 0x22;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);
    //<4>. Register-0x30,31,32 = 0x20,11,22
        cTunerData[0]=0x20;
        cTunerData[1]=0x11;
        cTunerData[2]=0x22;
        u8add = 0x30;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 3, cTunerData);
    //<5>. Register-0x5F = 0x80
        cTunerData[0]=0x80;
        u8add = 0x5F;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 1, cTunerData);

//** To disable TS
        cTunerData[0]=0x00;
        cTunerData[1]=0x00;
        u8add = 0x1E;
        MDrv_IIC_WriteBytes(_DTV_DEMODE_I2C_ID, 1, &u8add, 2, cTunerData);


//** To disable PSK 0x13 = 0x80, 0x17 = 0xFF
        cTunerData[0]=0x80;
        u8add = 0x13;
        MDrv_IIC_WriteBytes(0x32, 1, &u8add, 1, cTunerData);
        cTunerData[0]=0xFF;
        u8add = 0x17;
        MDrv_IIC_WriteBytes(0x32, 1, &u8add, 1, cTunerData);



}
/*************************************************************************
  Subject:   SHARP tuner paremeter write
  Function:   Set_Digital_TUNER
  Parmeter:   Freq: "RF+IF" in MHz
                 eBandWidth: BW_MODE_6MHZ, BW_MODE_7MHZ, BW_MODE_8MHZ
                 CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
//???? => To Do: For Freq = 61.25MHz need to set register[0x11] = 0x23 (Default =0x21)

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[6];
       U8 bs321,cp210,u8Data;

    eBandWidth = eBandWidth; //Avoid the compiler warning;

    //printf("set to Ch32\n");
    //Freq=578;  //ch34
    //eBandWidth=3;  //8M
    //Step 166.7 Khz   1000/166.7 = 6
    //value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 20);
    //value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6);  //VA1T1ED-60606

#if 0 //Test;;
     Freq = 521;
     eBandWidth = E_RF_CH_BAND_6MHz;
     Tuner_VA1G5BF8010_DBG(printf("???? For Test, Tuner8010: Force to Freq = 521, B=6MHz...\n"));
#endif



//For Byte1-----(I2C Address)
    //8010: For Sharp Tuner DTV Step = 142.86 => 1000/142.86=6.999
      value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 7);//VA1G5BF8010


//For Byte2-----(CONFIG[0])
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

//For Byte3----(CONFIG[1])
    CONFIG[1] = ( unsigned char ) ( value );

//For Byte4----(CONFIG[2])
       //** R2,R1,R0(Bit2~0), Digital = 0,0,1
    CONFIG[2] = 0x01;  //Step = 142.86 K
       //** Bit7,6 fix to 1 / Bit 3,4,5 fix to 0
    CONFIG[2] |= 0xC0;  //Step = 142.86 K

//For Byte5----(CONFIG[3])
    //U/V
      bs321 = 0x01; //Set Default Value

    if(Freq < 161)
        bs321 = 0x01;
    else if(Freq>=161 && Freq<426)
                bs321 = 0x02;
    else if(Freq>=426)
                bs321 = 0x04;
    CONFIG[3] = bs321;
      //For DTV => Bit 3 (BS4) =0
      Tuner_VA1G5BF8010_DBG(printf("Tuner8010: bs321 = %bx\n", bs321));
    //Charge Pump
    cp210 = 0x80; //Set Default Value
    if(Freq<153)                        cp210 = 0x80;
    else if(Freq>=153 && Freq<161)    cp210 = 0xA0;
    else if(Freq>=161 && Freq<233)    cp210 = 0x60;
    else if(Freq>=233 && Freq<343)    cp210 = 0xA0;
    else if(Freq>=343 && Freq<426)    cp210 = 0xE0;
    else if(Freq>=426 && Freq<463)    cp210 = 0x60;
    else if(Freq>=463 && Freq<563)    cp210 = 0x80;
    else if(Freq>=563 && Freq<613)    cp210 = 0xA0;
    else if(Freq>=613 && Freq<713)    cp210 = 0xC0;
    else if(Freq>=713)                    cp210 = 0xE0;
    CONFIG[3] |= cp210;


//For Byte6----(CONFIG[4])
    //Bit 7 Fix to 1;;From Spec
    CONFIG[4] = 0x80;
    //Set AL0 ~ AL2 (Bit) to = 0,0,0;;Spec recommand
    u8Data=0;
    CONFIG[4] |= u8Data;
    //ATC => Bit 3 (0:Normal Mode, 1:Fast Search Mode)
    //??? => Maybe we can enhance the Auto Scan speed using Fast Search Mode

    Tuner_VA1G5BF8010_DBG(printf("Tuner8010: DTV Tuner: %bx,  %bx,  %bx,  %bx,  %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]));
    devCOFDM_PassThroughI2C_WriteBytes(_ATV_TUNER_I2C_ID, 0, NULL, 5, CONFIG);

}

#undef VA1G5BF8010_C
#endif
