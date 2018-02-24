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
 Copyright (c) 2008 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: DevTuner.c
 [Date]:        30-Jun-2008
 [Comment]:
   TV tuner subroutines.
 [Reversion History]:
*******************************************************************************/
#define DTOS403LH121A_C

#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"
#include "COFDM_Demodulator.h"
#include "DTOS403LH121A.h"

static FREQSTEP m_eFrequencyStep;

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    printf("EDDIE:FRONTEND_TUNER_TYPE==SEC_DTOS403LH121A \n");
    switch(eFreqStep)
    {
    //case FREQSTEP_31_25KHz: //have not support
    case FREQSTEP_62_5KHz:
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        //m_eFrequencyStep = FREQSTEP_31_25KHz;
        m_eFrequencyStep = FREQSTEP_50KHz;
        break;
    }
}



void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
    BYTE cTunerData[5]={0,0,0,0,0};

    // Write DB1,DB2,CB,BB
    //DB1,DB
    cTunerData[0] = HIBYTE(wPLLData);
    cTunerData[1] = LOBYTE(wPLLData);
    //CB
    cTunerData[2] = 0xC8|DIVIDER_RATIO;
    //BB
    if(eBand == E_RFBAND_VHF_LOW)
        cTunerData[3] = 0x01;
    else if(eBand == E_RFBAND_VHF_HIGH)
        cTunerData[3] = 0x02;
    else  //UHF
        cTunerData[3] = 0x08;

    //AB
    cTunerData[4] = 0x86; //AL2,AL1,AL0 = 111 =>Disable internal RF AGC for Analog
                                   //ATV uses external AGC which is controlled by Demod

#if ((MS_BOARD_TYPE_SEL == BD_MST087A_D01A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087B_S7M_D01A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087B_S7_D01A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087C_D02A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087D_D01A_S))
     {
        U16 u16Temp;

        u16Temp=I2CGROUPSEL |TUNER_I2C_WRITE_ADDR;
        MDrv_IIC_WriteBytes(u16Temp,  0, NULL, 5, cTunerData);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(TUNER_I2C_WRITE_ADDR, 0, NULL, 5, cTunerData);
#endif
}

void devTunerInit(void)
{

}

void devDigitalTuner_Init()
{

}
//------------------------------------------------------------------------------
//  Subject:     DTOS403LH121A tuner paremeter write
//  Function:   Set_Digital_TUNER
//  Parmeter:   Freq: "RF+IF" in MHz
//                 eBandWidth:  7MHZ, 8MHZ
//                 CONFIG: pointer to tuner address
//  Return :    NONE
//  Remark:
//------------------------------------------------------------------------------

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned int value;
    unsigned char u8CP;
    unsigned char u8T0=0;
    unsigned char CONFIG[7]={0,0,0,0,0,0,0};



//PLL ratio= (FREQin +FREQifout)/Fstep  =>  MHz+MHz/KHz= KHz*1000/KHz
    printf("EDDIE:DTOS403_MODE=0x%bx RSA_RSB=0x%bx T0=0x%bx OS=0x%bx \n",DTOS403_MODE,RSA_RSB,T0,OS);
    printf("EDDIE:CONTROL_BYTE_SETTING=0x%bx   \n",CONTROL_BYTE_SETTING);

    value = ( unsigned int ) ( ( Freq + DIGITAL_TUNER_IF ) * COEFF_INTEGER + COEFF_FINETUNE);

    printf("EDDIE: Tuner PLL value =0x%x \n",value);

    CONFIG[0]=TUNER_I2C_WRITE_ADDR;

    //DB1
    CONFIG[1] = ( unsigned char ) ( value >> 8 );

    //DB2
    CONFIG[2] = ( unsigned char ) ( value );

    //CB
    // ChargePump Setting
    if(DTOS403_MODE==DTOS403_NORMAL_MODE)
    {
        if(Freq<NM_FREQ_BOUNDRY)
            u8CP=0x01;  //50uA
        else
            u8CP=0x00;  //250uA
    }
    else
    {
         if(Freq<=EXTMODE_FREQ_BOUNDRY1 ||
            (Freq>=EXTMODE_FREQ_BOUNDRY3 && Freq<=EXTMODE_FREQ_BOUNDRY4))
         {
            u8CP=0x01; u8T0=0x00;  //50uA
         }
        else if(Freq<=EXTMODE_FREQ_BOUNDRY2 ||
                  (Freq>=EXTMODE_FREQ_BOUNDRY4 && Freq<=EXTMODE_FREQ_BOUNDRY5) ||
                  (Freq>=EXTMODE_FREQ_BOUNDRY6 && Freq<=EXTMODE_FREQ_BOUNDRY7))
        {
            u8CP=0x01; u8T0=0x01;  //125uA
        }
        else if(Freq<=EXTMODE_FREQ_BOUNDRY3 ||
                  (Freq>=EXTMODE_FREQ_BOUNDRY5 && Freq<=EXTMODE_FREQ_BOUNDRY6) ||
                  (Freq>=EXTMODE_FREQ_BOUNDRY7 && Freq<=EXTMODE_FREQ_BOUNDRY8))
        {
            u8CP=0x00; u8T0=0x00;  //250uA
        }
        else
        {
            u8CP=0x00; u8T0=0x01;  //650uA
        }
    }

    CONFIG[3]=CONTROL_BYTE_SETTING | (u8CP<< CP_BITLOC_STARTFROM) |(u8T0 <<T0_BITLOC_STARTFROM);

    //AB
   // CONFIG[6]=u8RFAGC_TAKEOVER<<4 | u8RFAGC_TIMECONSTANT<<7 ;
    CONFIG[4]=(U8) RFAGC_TAKEOVER_MODE | RFAGC_TC_MODE ;

     //CB
    CONFIG[5]=CONFIG[3];

    //BB:  IFA 0 0 P3 P2 P4 P1 P0
    if(Freq <= DTV_VHF_LOWMAX_FREQ)
        CONFIG[6] |= 0x01;
    else if(Freq <= DTV_VHF_HIGHMAX_FREQ)
        CONFIG[6] |= 0x02;
    else
        CONFIG[6] |= 0x10;

     if(eBandWidth ==E_RF_CH_BAND_8MHz)
          CONFIG[6] |= IF_8M_INTERNAL_SAW_FILTER_BW;

    #if ((MS_BOARD_TYPE_SEL == BD_MST087A_D01A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087B_S7M_D01A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087B_S7_D01A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087C_D02A_S) || \
        (MS_BOARD_TYPE_SEL == BD_MST087D_D01A_S))
     {
        U16 u16Temp;

        u16Temp=I2CGROUPSEL |TUNER_I2C_WRITE_ADDR;

        MDrv_IIC_WriteBytes(u16Temp,  0, NULL,6, &CONFIG[1]);
    }
#else
    devCOFDM_PassThroughI2C_WriteBytes(TUNER_I2C_WRITE_ADDR, 0, NULL, 6,  &CONFIG[1]);
#endif
    printf("###DTV Tuner Data: %bX %bX %bX %bX %bX  %bx  %bx\n", CONFIG[0], CONFIG[1], CONFIG[2], CONFIG[3], CONFIG[4],CONFIG[5],CONFIG[6]);


}

void devTunerReadPLLReg( U8 *pRegData,U8 u8RegNum)
{
    U16 u16I2CAddr;

    u16I2CAddr=I2CGROUPSEL | TUNER_I2C_READ_ADDR ;
    MDrv_IIC_ReadBytes(u16I2CAddr, 0, NULL, (U16) u8RegNum,pRegData);

}


#undef DTOS403LH121A_C
