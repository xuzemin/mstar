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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef TDTC_G311D_C
#define TDTC_G311D_C

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "drvGPIO.h"

#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalSettingSt.h"
//Jun  #define DIVIDER_RATIO_31_25KHz  0x04

#define DIVIDER_RATIO_62_5KHz                  0x00
#define DIVIDER_RATIO_166_7KHz               0x02
#define DIVIDER_RATIO_50KHz                      0x03

#define USE_EXTERNAL_RF_AGC        1

#if (TN_FREQ_STEP == FREQ_STEP_50KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_50KHz
#elif (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
#define DIVIDER_RATIO      DIVIDER_RATIO_62_5KHz
#endif

#define DEBUG_PAL_TUNER   0

#define  PAL_DBG_MSG(x)  x

static FREQSTEP m_eFrequencyStep;

U8 ucStatus; // tuner status

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
        m_eFrequencyStep = FREQSTEP_31_25KHz;
        break;
    }
}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{

    BYTE cTunerData[6];
    U16  u16Freq;
    // Write DB1,DB2,CB,BB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);
    #if (EN_AGC_CONTROL)
         EXT_RF_AGC_ON();
    #endif
    u16Freq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData-msAPI_Tuner_GetIF());

     cTunerData[2] = 0xC0;

      if(eBand == E_RFBAND_VHF_LOW)
    {
        if ( u16Freq <= 169 )
        {
            cTunerData[3] = (0x0 << 5);
        }
        else if(u16Freq <= 179)
        {
            cTunerData[3] = (0x1 << 5);
        }
         else if(u16Freq <= 189)
        {
            cTunerData[3] = (0x2 << 5);
        }
        else
        {
            cTunerData[3] = (0x3 << 5);

        }
        cTunerData[3] |= 0x01;

    }
    else if(eBand == E_RFBAND_VHF_HIGH)
    {
        if ( u16Freq <=  406)
        {
            cTunerData[3] = (0x0 << 5);
        }
        else  if ( u16Freq <=  438)
        {
            cTunerData[3] = (0x1 << 5);
        }
         else  if ( u16Freq <=  461)
        {
            cTunerData[3] = (0x2 << 5);
        }
         else  if ( u16Freq <  483)
        {
            cTunerData[3] = (0x3 << 5);
        }
        else
        {
            cTunerData[3] = (0x3 << 5);

        }
        cTunerData[3] |= 0x02;

    }
    else
    {
        if ( u16Freq <750)
        {
            cTunerData[3] = (0x0 << 5);
        }
         else if ( u16Freq < 817 )
        {
            cTunerData[3] = (0x1 << 5);
        }
         else if ( u16Freq < 862 )
        {
            cTunerData[3] = (0x2 << 5);
        }
         else if ( u16Freq < 862 )
        {
            cTunerData[3] = (0x2 << 5);
        }
         else if ( u16Freq < 882 )
        {
            cTunerData[3] = (0x3 << 5);
        }
         else if ( u16Freq < 895 )
        {
            cTunerData[3] = (0x4 << 5);
        }
        else if ( u16Freq < 903 )
        {
            cTunerData[3] = (0x5 << 5);
        }
        else
        {
            cTunerData[3] = (0x5 << 5);

        }
         cTunerData[3] |= 0x04;
    }

     cTunerData[4] = 0x86;

     cTunerData[5] = cTunerData[3] ;

#if 0
printf("---> ATV Tuner: \n");

    {
        BYTE i;
        for(i=0;i<5;i++)
            printf("%lx ", (U32)cTunerData[i]);
        printf("\n\r");
    }
#endif

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    {
        U16 u16Temp=0x0200;

        u16Temp|=_TUNER_I2C_ID;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 6, cTunerData);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, cTunerData);
#endif

}

void devTunerInit(void)
{
    BYTE cTunerData[6];

    //devTunerSetFreqStep(TN_FREQ_STEP);//Type mismatch,
    cTunerData[0] = 0;
    cTunerData[1] = 0;
     U16 u16Temp=0x0200;

   #if (EN_AGC_CONTROL)
         EXT_RF_AGC_ON();
   #endif
    cTunerData[2] = 0xC0;
    cTunerData[3] = 0x01;
    cTunerData[4] = 0x86;
    cTunerData[5] = 0x01;
#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    u16Temp|=_TUNER_I2C_ID;
    MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 6, cTunerData);
 #else
    devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 6, cTunerData);
 #endif
}


#define DIGITAL_TUNER_IF    36.167

/*************************************************************************
  Subject:    FQD1216 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_Init()
{
     #if (EN_AGC_CONTROL)
     EXT_RF_AGC_OFF();
    #endif
}

#define DIVIDER_166K              3
//#define DIVIDER_142K              1
//#define DIVIDER_80K               2
#define DIVIDER_62K               0
//#define DIVIDER_31K               4
#define DIVIDER_50K               2

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char CONFIG[6];

    eBandWidth = eBandWidth;
    //MDrv_Set_Digital_TUNER1(Freq, eBandWidth);
      #if (EN_AGC_CONTROL)
     EXT_RF_AGC_OFF();
    #endif
    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * 6 + 0.5); //step size = 62.5KHz
    // Step 166.7 Khz   1000/166.7 = 6

    //DB1
    CONFIG[0] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[1] = ( unsigned char ) ( value );


     CONFIG[2] = 0xC2 ; // CB1


     if(Freq < 127)
     {
          CONFIG[3] =0x01|(0x2 << 5);
     }
     else if(Freq < 151)
     {
          CONFIG[3] =0x01|(0x3 << 5);
     }
     else if(Freq < 176)
     {
          CONFIG[3] =0x01|(0x4<< 5);
     }
     else if(Freq < 193)
     {
          CONFIG[3] =0x01|(0x5 << 5);
     }
     else if(Freq < 337)
     {
          CONFIG[3] =0x02|(0x2 << 5);
     }
     else if(Freq < 394)
     {
          CONFIG[3] =0x02|(0x3 << 5);
     }
     else if(Freq < 446)
     {
          CONFIG[3] =0x02|(0x4 << 5);
     }
     else if(Freq < 457)
     {
          CONFIG[3] =0x02|(0x5 << 5);
     }
     else if(Freq < 480)
     {
          CONFIG[3] =0x02|(0x6 << 5);
     }

     else if(Freq < 692)
     {
          CONFIG[3] =0x04|(0x3 << 5);
     }
     else if(Freq < 812)
     {
          CONFIG[3] =0x04|(0x4 << 5);
     }
     else if(Freq <=890)
     {
          CONFIG[3] =0x04|(0x5 << 5);
     }
     else if(Freq < 902)
     {
          CONFIG[3] =0x04|(0x6 << 5);
     }

    CONFIG[4] = 0x86;//0x81; // CB1

    CONFIG[5] =CONFIG[3];

    //printf("Tuner: %bx, %bx, %bx, %bx, %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4]);

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) || (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD)
    {
       U16 u16Temp=0x0200;
       u16Temp|=_TUNER_I2C_ID;
       MDrv_IIC_WriteBytes(u16Temp, 0, NULL, 6, CONFIG);
    }
#else
        devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID, 0, NULL, 6, CONFIG);
#endif
}

#undef TDTC_G001D_C
#endif

