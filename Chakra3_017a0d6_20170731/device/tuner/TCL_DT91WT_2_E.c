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

#ifndef _TCL_DT91WT_2_E_C_
#define _TCL_DT91WT_2_E_C_

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "COFDM_Demodulator.h"
#include "Tuner.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_Tuning.h"
#include "MApp_GlobalSettingSt.h"

//#define TUNER_DEBUG
#define TUNER_DBINFO(x)             //x

void devTunerInit(void)
{
}

void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{

    unsigned char   dwTunerData[5];
    unsigned int    dwTunerFreq = 0;

    dwTunerData[0] = HIBYTE(wPLLData);
    dwTunerData[1] = LOBYTE(wPLLData);

    dwTunerFreq = msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData - msAPI_Tuner_GetIF());

    dwTunerData[2] = 0xBD;              //ATP[2:0] = 3'b011 = IF Out Level: 108 dBuv
                                        //RS[2:0] = 3'b101 = Reference Divider Ratio: 80 (50KHz)

    if(dwTunerFreq <= 165)
    {
        dwTunerData[3] = 0x21;          //Band Selection Port: VHF Low (48MHz - 165MHz)
    }
    else if(dwTunerFreq <= 450)
    {
        dwTunerData[3] = 0x22;          //Band Selection Port: VHF High (166MHz - 450MHz)
    }
    else
    {
        dwTunerData[3] = 0x2C;          //Band Selection Port: UHF (451MHz - 866MHz)
                                        //CP[2:0] = 3'b010
                                        //AISL = 0
                                        //BS3 = 1 to Set LNA On
    }

    dwTunerData[4] = 0xD1;

    TUNER_DBINFO(printf("[INFO] I2C Address: 0x%02x\n", (unsigned char) _TUNER_I2C_ID));
    TUNER_DBINFO(printf("[INFO] Tuner[0]: 0x%02x\n", dwTunerData[0]));
    TUNER_DBINFO(printf("[INFO] Tuner[1]: 0x%02x\n", dwTunerData[1]));
    TUNER_DBINFO(printf("[INFO] Tuner[2]: 0x%02x\n", dwTunerData[2]));
    TUNER_DBINFO(printf("[INFO] Tuner[3]: 0x%02x\n", dwTunerData[3]));
    TUNER_DBINFO(printf("[INFO] Tuner[4]: 0x%02x\n", dwTunerData[4]));

    if(MDrv_IIC_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, dwTunerData) == FALSE)
    {
        TUNER_DBINFO(printf("[Error] Write I2C Failed\n"));
        return;
    }
#ifdef TUNER_DEBUG
    else
    {
        unsigned char   byTunerStatus = 0;

        MDrv_IIC_ReadBytes(_TUNER_I2C_ID, 0, NULL, 1, &byTunerStatus);
        TUNER_DBINFO(printf("[INFO] Tuner Status: 0x%02x\n", (unsigned int) byTunerStatus));
    }
#endif

}

void devDigitalTuner_Init()
{
}

#define DIGITAL_TUNER_IF    36.1667     //IF-Center Frequency: 36.1667 MHz

void devDigitalTuner_SetFreq (double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    unsigned char   dwTunerData[5];
    unsigned int    dwTunerFreq = 0;

    //Set Dummy Value to Fix Compile Warning
    eBandWidth = E_RF_CH_BAND_6MHz;


#if (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    dwTunerFreq = (unsigned int) ((Freq + DIGITAL_TUNER_IF) * 1000 / 166.67);
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    dwTunerFreq = (unsigned int) ((Freq + DIGITAL_TUNER_IF) * 1000 / 62.5);
#else
    #error "Unknown DEMOD Type Selection"
#endif

    dwTunerData[0] = ((dwTunerFreq >> 8) & 0xFF);       //DB1
    dwTunerData[1] = (dwTunerFreq & 0xFF);              //DB2

#if (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
    dwTunerData[2] = 0x98;              //ATP[2:0] = 3'b011 = IF Out Level: 108 dBuv
                                        //RS[2:0] = 3'b000 = Reference Divider Ratio: 24 (166.67KHz)
#elif (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    dwTunerData[2] = 0x9B;              //ATP[2:0] = 3'b011 = IF Out Level: 108 dBuv
                                        //RS[2:0] = 3'b011 = Reference Divider Ratio: 64 (62.5KHz)
#else
    #error "Unknown DEMOD Type Selection"
#endif

    if(Freq < 165)
    {
        dwTunerData[3] = 0x85;          //Band Selection Port: VHF Low (48MHz - 165MHz)
    }
    else if(Freq < 450)
    {
        dwTunerData[3] = 0x86;          //Band Selection Port: VHF High (166MHz - 450MHz)
    }
    else
    {
        dwTunerData[3] = 0x8C;          //Band Selection Port: UHF (451MHz - 866MHz)
                                        //CP[2:0] = 3'b010
                                        //AISL = 0
                                        //BS3 = 1 to Set LNA On

        if(Freq > 670)
        {
            dwTunerData[3] += 0x40;     //Set Charge Pump Current to 600uA
        }
    }

#if (FRONTEND_DEMOD_TYPE == EMBEDDED_DVBC_DEMOD)
    dwTunerData[3] &= 0x3F;
#endif

    dwTunerData[4] = 0xD1;

    TUNER_DBINFO(printf("[INFO] I2C Address: 0x%02x\n", (unsigned char) _TUNER_I2C_ID));
    TUNER_DBINFO(printf("[INFO] Tuner[0]: 0x%02x\n", dwTunerData[0]));
    TUNER_DBINFO(printf("[INFO] Tuner[1]: 0x%02x\n", dwTunerData[1]));
    TUNER_DBINFO(printf("[INFO] Tuner[2]: 0x%02x\n", dwTunerData[2]));
    TUNER_DBINFO(printf("[INFO] Tuner[3]: 0x%02x\n", dwTunerData[3]));
    TUNER_DBINFO(printf("[INFO] Tuner[4]: 0x%02x\n", dwTunerData[4]));

    if(MDrv_IIC_WriteBytes(_TUNER_I2C_ID, 0, NULL, 5, dwTunerData) == FALSE)
    {
        TUNER_DBINFO(printf("[Error] Write I2C Failed\n"));
        return;
    }
#ifdef TUNER_DEBUG
    else
    {
        unsigned char   byTunerStatus = 0;

        MDrv_IIC_ReadBytes(_TUNER_I2C_ID, 0, NULL, 1, &byTunerStatus);
        TUNER_DBINFO(printf("[INFO] Tuner Status: 0x%02x\n", (unsigned int) byTunerStatus));
    }
#endif


}

#undef TDTC_G001D_C
#endif

