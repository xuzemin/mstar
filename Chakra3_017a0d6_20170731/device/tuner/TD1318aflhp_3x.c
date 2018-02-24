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

/******************************************************************************
 Copyright (c) 2004 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DevTuner.c
 [Date]:        30-Mar-2004
 [Comment]:
   TV tuner subroutines.
 [Reversion History]:
*******************************************************************************/

#define TD1318_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "COFDM_Demodulator.h"
#include "IF_Demodulator.h"

#include "TD1318aflhp_3x.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

//#include "SWI2C.h"
/*
PLL step size PLL ref. divider ratio R1 R0
166.67 kHz 24 1 0 //2
50 kHz 80 0 0
62.5 kHz 64 1 1 //3
*/

#define DIVIDER_RATIO_31_25KHz  0x0E //don't support
#define DIVIDER_RATIO_62_5KHz   0x03 //R1 =1 R0 =1
#define DIVIDER_RATIO_166_7KHz  0x02 //R1 =1 R0 =0
#define DIVIDER_RATIO_50KHz     0x00 // R1 =0 R0 =0

#if (TN_FREQ_STEP == FREQ_STEP_31_25KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_31_25KHz
#elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#endif

#define DEBUG_PAL_TUNER   0

#define PAL_DBG_MSG(x) // x
#define USE_INTERNAL_AGC 0

#define USE_EXTERNAL_RF_AGC

#define TN_FREQ_SR          ((UINT)(1000/62.5))
#define CP_T 0x0E

static FREQSTEP m_eFrequencyStep;

unsigned char rf_agc_setting=EXTERNAL_RF_AGC;


void devTunerSetRFAGCSetting(unsigned char s)
{
    rf_agc_setting=s;
}


void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_31_25KHz:
    case FREQSTEP_62_5KHz:
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_62_5KHz;
        break;
    }
}


void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{

    //BYTE code cp_t=0x0E;
    BYTE cTunerData[4];
    unsigned long freq=(unsigned long)wPLLData*1000/16;

    freq=freq/1000;
    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);




    UNUSED(eBand);
    //printf("\n\n Tune Analog Search %d MHz",(unsigned int)freq);

// Control Data Byte 1 CP T2 T1 T0 R1 R0 0
//CP T2 T1 T0 = 0 1 1 sends auxillary byte

//0xf6
//1 1 1 1 0 1 1 0
// CP =1 || T2 T1 T0 , 1 1 0 ,Medium CP
// R1 R0 , 1 1 , 62.5 MHz

    //cTunerData[2]=0x80+(CP_T)<<3+(DIVIDER_RATIO_62_5KHz<<1);


    cTunerData[2]=0xF6;


    if( wPLLData < (161.25 * TN_FREQ_SR) )  // low bank
    {
        //printf ("\n low band");
        cTunerData[3] = 0x01;
    }
    else if( wPLLData < (447.25 * TN_FREQ_SR )) // middle band
    {
        //printf ("\n middle band");
        cTunerData[3] = 0x02;
    }
    else
    {
        //printf ("\n high band");
        cTunerData[3] = 0x04;
    }

    //printf("\n Philips Tuner Write %x %x %x %x ",(unsigned int)cTunerData[0],(unsigned int)cTunerData[1],(unsigned int)cTunerData[2],(unsigned int)cTunerData[3]);
  #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
  	U16 u16Temp=0x0200;
	u16Temp|=_TUNER_I2C_ID;
	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, cTunerData);
   #else 
   	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
   #endif


    MsOS_DelayTask(20);
    cTunerData[2] = (cTunerData[2] & 0XC7) | 0x18; // to send AB byte instead of BB byte

    #ifdef USE_EXTERNAL_RF_AGC
        cTunerData[3]=0x60;//** ME 07 march 2008 ,In Analogue Mode We are enabling External RF AGC */
    #else
        cTunerData[3] = 0x20; //106 dBuV ,normal time constant
    #endif

  #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, cTunerData);
   #else 
   	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
   #endif
    MsOS_DelayTask(100); //It would be necessary to change wait durations later


}

void devTunerInit(void)
{
    BYTE cTunerData[4];

    //printf("\n Philips Tuner Init");
    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
    cTunerData[2]=0x80+((CP_T)<<3)+(DIVIDER_RATIO_62_5KHz<<1);
    cTunerData[3] = 0x01;

  #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
  	U16 u16Temp=0x0200;
	u16Temp|=_TUNER_I2C_ID;
	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, cTunerData);
   #else 
   	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, cTunerData);
   #endif




}

#define DIGITAL_TUNER_IF    36.167

/*************************************************************************
  Subject:    TD1316 tuner initialized function
  Function:   devDigitalTuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{

}

//------------------------------------------------------------------------------
//  Subject:    TD1316 tuner paremeter write
//  Function:   Set_Digital_TUNER
//  Parmeter:   Freq: "RF+IF" in MHz
//                 eBandWidth: 6MHZ, 7MHZ, 8MHZ
//                 CONFIG: pointer to tuner address
//  Return :    NONE
//  Remark:
//------------------------------------------------------------------------------
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[6];

    //printf("\n Set Tuner Digital %d ",(unsigned int)(Freq));

    // always init tuner here because annalog will chane the init value
    // todo: consider app flow, don't init value every channel change.
    devDigitalTuner_Init();

    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 );


    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );


//   Control Data    Byte    1 CP T2 T1 T0 R1 R0 0



    if(Freq < 444)
        {
            //printf(" VHF ");
            CONFIG[3] = 0x02; //mid band           //Band Switch Byte (BB)

            if(Freq <= (262.0 - 36.167))
            {
                //10111100
                //cp_t : 0 1 1 1 medium cp
                //r1 r0 :1 0 ,166.67 KHz
                CONFIG[2] = 0xBC;        //Control Data Byte (CB)
            }
            else
            {
                //11110100
                //cp_t 1 1 1 0  ???
                //r1 r0 : 1 0 , 166.67 KHz
                CONFIG[2] = 0xF4;

            }
        }
    else
    {


        //printf(" UHF ");
        CONFIG[3] = 0x04;//high band             //Band Switch Byte (BB)

//      if(Freq <= (706000 - 36167))
        if(Freq <= (686.0 - 36.167))
        {
            //10111100
            //cp_t : 0 1 1 1 medium cp
            //r1 r0 :1 0 ,166.67 KHz


            CONFIG[2] = 0xBC;        //Control Data Byte (CB)
        }
        else if(Freq <= (798.0 - 36.167))
        {
            CONFIG[2] = 0xF4;
        }
        else
        {
            CONFIG[2] = 0xFC;
        }
    }

        if(eBandWidth == E_RF_CH_BAND_8MHz)
        {
            CONFIG[3] = CONFIG[3] | 0x08;         //8MHz SAW Filter
        }
        else
        {
            //bprintf("\n CONFIG[3] = 0x%x ::BW=7");
        }


  #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
  	U16 u16Temp=0x0200;
	u16Temp|=_TUNER_I2C_ID;
	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, CONFIG);
   #else 
   	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, CONFIG);
   #endif




        MsOS_DelayTask(20);
        CONFIG[2] = (CONFIG[2] & 0XC7) | 0x18; // to send AB byte instead of BB byte

        // 1 CP T2 T1 T0 R1 R0 0
        // 1 e  0  1  1  1  0  0

        //T2=0 and T1=T0=1 ,auxilary byte

#if 0
        CONFIG[3]=0x70;//rf agc loop break
        //CONFIG[3]=0x10;
        devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, CONFIG);
        MsOS_DelayTask(800);//ilerde optimize edilmesi gerekiyor
#endif

#if 1
        //ATC AL2 AL1 AL0 0 0 0 0
        //  1  0   1   0  0 0 0 0
        // ATC =1 ,Search Mode
        // AL ,106 dbuV


        //CONFIG[3]=0xA0;//Set AGC Take-over point to 106dBuV and AGC low current
        CONFIG[3]=0x90;//109 dbuV
  #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, CONFIG);
   #else 
   	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, CONFIG);
   #endif




        MsOS_DelayTask(800);//ilerde optimize edilmesi gerekiyor

        //ATC AL2 AL1 AL0 0 0 0 0
        // 0   0   1   0  0 0 0 0
        //ATC ,Normal mode
        //AL , 106 db

        //CONFIG[3] = 0x20;                    // After tuning phase completes, tuner switched to better reception mode
                                            // (Low AGC Current)
        CONFIG[3] = 0x10;//109 dbuV
        //printf(" Tuner:%bx, %bx, %bx, %bx", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3]);
  #if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)|| ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
	MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 4, CONFIG);
   #else 
   	devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 4, CONFIG);
   #endif
 #endif

}

//------------------------------------------------------------------------------
//  Subject:    TD1318 tuner status read
//  Function:   devDigitalTuner_ReadStatus
//  Parameter:
//  Return :    TRUE if everything is ok , FALSE if not ,Function puts status
//              information to pu8data
//  Remark:
//------------------------------------------------------------------------------
BOOLEAN devDigitalTuner_ReadStatus (U8* pu8data )
{
    return devCOFDM_PassThroughI2C_ReadBytes(_TUNER_I2C_ID, 0, NULL, 1,pu8data);


}

#undef TD1318_C

