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
/***********************************************************************************
*    File:                R2A10406NP.c
*
*    Project:              TV/AV
*
*    Description:
*
*    Date:                 started from 2006.02.16
*
***********************************************************************************/

#include "COFDM_Demodulator.h"
#include "R2A10406NP.h"
#include "drvIIC.h"
#include "debug.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
//#define DEBUG_IFDEMODULATOR
#ifdef DEBUG_IFDEMODULATOR
    #define debugIFDemodulatorPrint(a,b)    debugPrint(a,b)
#else
    #define debugIFDemodulatorPrint(a,b)
#endif

//****************************************************************************
// Private functions of this file.
//****************************************************************************



//****************************************************************************
// Start of public implementation
//****************************************************************************

/**
 FUNCTION    : void MDrv_IFDM_Init(void)

 USAGE    : To initialize IF-demodulator.

 INPUT    : None

 OUTPUT    : None

 GLOBALS: None

*/
void MDrv_IFDM_Init(void)
{
    m_eIF_Freq = IF_FREQ_INVALID;

    MDrv_IFDM_SetIF(IF_FREQ_B);
}

/**
 FUNCTION    : eAFC MDrv_IFDM_GetFreqDev(void)

 USAGE    : To get frequency deviation.

 INPUT    : None

 OUTPUT    : eAFC : Frequency deviation. See below.
                    b3 b2 b1 b0
                    0  1  1  1   under (f0 - 187.5 kHz)
                    0  1  1  0   f0 - 162.5 kHz
                    0  1  0  1   f0 - 137.5 kHz
                    0  1  0  0   f0 - 112.5 kHz
                    0  0  1  1   f0 - 87.5 kHz
                    0  0  1  0   f0 - 62.5 kHz
                    0  0  0  1   f0 - 37.5 kHz
                    0  0  0  0   f0 - 12.5 kHz
                    1  1  1  1   f0 + 12.5 kHz
                    1  1  1  0   f0 + 37.5 kHz
                    1  1  0  1   f0 + 62.5 kHz
                    1  1  0  0   f0 + 87.5 kHz
                    1  0  1  1   f0 + 112.5 kHz
                    1  0  1  0   f0 + 137.5 kHz
                    1  0  0  1   f0 + 162.5 kHz
                    1  0  0  0   over (f0 + 187.5 kHz)

 GLOBALS: None

*/

AFC MDrv_IFDM_GetFreqDev(void)
{
    BYTE cValue;
    BYTE  bAFCTable[5] =
    {
        E_AFC_PLUS_62p5KHz,
        E_AFC_PLUS_37p5KHz,
        E_AFC_PLUS_12p5KHz,
        E_AFC_MINUS_37p5KHz    ,
        E_AFC_MINUS_62p5KHz
    } ;

    devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
    if((cValue & _MASK_OF_AFCWIN) == 0x40)
    {
        putchar('A');
        MsOS_DelayTask(100);
        devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
    }
    if( (cValue & _MASK_OF_AFCWIN) <= _AFCWIN_IN_WINDOW )
    {
        //printf("\r\n AFT = %bx", bAFCTable[(cValue&_MASK_OF_AFC)>>5]);
        return  bAFCTable[(cValue&_MASK_OF_AFC)>>5];
    }

    return E_AFC_BELOW_MINUS_187p5KHz;
}

BOOLEAN MDrv_IFDM_IsAFCInWindow(void)
{
    BYTE cValue;

    devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID, 0, NULL, 1, &cValue);
    if( (cValue & _MASK_OF_AFCWIN) == _AFCWIN_IN_WINDOW )
    {
        return TRUE;
    }

    return FALSE;
}

/**
 FUNCTION    : void MDrv_IFDM_SetIF(eIF_FREQ eIF_Freq)

 USAGE    : To Set IF.

 INPUT    : eIF_Freq -    IF_FREQ_B : B
                        IF_FREQ_G : G
                        IF_FREQ_I : I
                        IF_FREQ_DK : DK
                        IF_FREQ_L : L
                        IF_FREQ_L_PRIME : L'
                        IF_FREQ_MN : M/N
                        IF_FREQ_J : M(Japan)

 OUTPUT    : None

 GLOBALS: None

*/
void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq)
{
    BYTE cIF_Data[2];

     switch(eIF_Freq)
      {
           case  IF_FREQ_B:
           case  IF_FREQ_G:
               {
                   cIF_Data[0] = 0;
                cIF_Data[1] = 0xC2;
                //putchar('B');
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 1;
                cIF_Data[1] = 0xB0;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 2;
                cIF_Data[1] = 0x3D;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 3;
                cIF_Data[1] = 0x00;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 4;
                cIF_Data[1] = 0x0A;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 5;
                cIF_Data[1] = 0x73;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
               }
                    break;
        case  IF_FREQ_I:
               {
                   cIF_Data[0] = 0;
                cIF_Data[1] = 0xC2;
                //putchar('I');
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 1;
                cIF_Data[1] = 0xB0;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 2;
                cIF_Data[1] = 0x5D;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 3;
                cIF_Data[1] = 0x00;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 4;
                cIF_Data[1] = 0x0A;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 5;
                cIF_Data[1] = 0x73;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
               }
                    break;
        case  IF_FREQ_DK:
               {
                   cIF_Data[0] = 0;
                cIF_Data[1] = 0xC2;
                //putchar('D');
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 1;
                cIF_Data[1] = 0xB0;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 2;
                cIF_Data[1] = 0x7D;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 3;
                cIF_Data[1] = 0x00;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 4;
                cIF_Data[1] = 0x0A;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 5;
                cIF_Data[1] = 0x73;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
               }
                    break;

        case  IF_FREQ_L:
        case  IF_FREQ_L_PRIME:
               {
                   cIF_Data[0] = 0;
                cIF_Data[1] = 0xC0;
                //putchar('L');
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 1;
                cIF_Data[1] = 0xB0;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 2;
                cIF_Data[1] = 0x79;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 3;
                cIF_Data[1] = 0x00;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 4;
                cIF_Data[1] = 0x0A;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
                   cIF_Data[0] = 5;
                cIF_Data[1] = 0x73;
                MDrv_IIC_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 2, cIF_Data);
               }
                    break;
    default:

        return;

      }

    m_eIF_Freq = eIF_Freq;

}

void MDrv_IFDM_CVBSOff(void)
{
    //BYTE cIF_Data[2];

    //cIF_Data[0] = _IF_DEM_SUB_ADDRESS;
    //cIF_Data[1] = _TUNER_CVBS_NOT_USED_VALUE;

    //printf("MDrv_IFDM_CVBSOff\n");
    //devCOFDM_PassThroughI2C_WriteBytes(_IF_DEM_I2C_ID, 0, NULL, 4, cIF_Data);

}

IF_FREQ MDrv_IFDM_GetIF(void)
{
    return m_eIF_Freq;
}

