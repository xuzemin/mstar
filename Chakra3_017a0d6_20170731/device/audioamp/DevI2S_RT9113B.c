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
 //wjq20100112>>>
#ifndef __DEVI2S_RT9113B_C__
#define __DEVI2S_RT9113B_C__

#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "drvIIC.h"

#include "DevI2S_RT9113B.h"

#define RT9113B_ADDR        0x36

#ifndef I2C_BUS_IDX
#define I2C_BUS_IDX         0
#endif

#define RT9113B_BUSID     (((MS_U16) I2C_BUS_IDX << 8) | RT9113B_ADDR)
#define  MAX_DATA_LENGTH   20

U8  g_ucRT9113BRegAddr;


/****************************
        amp init regs
****************************/
U8 AmpReadTbl[] =
{
    //DataLength        Address     DataN       DataN+1...
    1, 0x0a, 0xff,
    0x00,
};

U8 AmpInitTblRa188b[] =
{
    1, 0x80, 0x80,
    1, 0x12, 0xD9,
    1, 0x13, 0x06,
    1, 0x84, 0x90,
    1, 0x16, 0x06,
    1, 0x18, 0x13,
    1, 0x81, 0x14,
    1, 0x19, 0x56,     // SW Volume default +16 dB
    1, 0x13, 0x02,
    1, 0x05, 0x02,
    1, 0x74, 0x00,
    1, 0x73, 0x8c,
    1, 0x73, 0x8c,
    1, 0x15, 0x44,
    2, 0x07, 0x01, 0x10,
    0x00,
};

U8 AmpInitTblTka188e[] =
{
    //DataLength        Address     DataN       DataN+1...
    1, 0x05, 0x40,
    1, 0x80, 0x80,
    1, 0x11, 0xA9,
    1, 0x12, 0xD8,
    1, 0x13, 0x02,
    1, 0x15, 0x04,
    1, 0x16, 0x05,
    1, 0x18, 0x12,
    1, 0x81, 0x14,
    1, 0x82, 0x39,
    1, 0x05, 0x02,
    1, 0x15, 0xC4,
    1, 0x19, 0x56,
    1, 0x07, 0x10,     // SW Volume default +16 dB
    4, 0x57, 0x00, 0x01, 0xCC, 0x00,
    1, 0x03, 0xB0,
    4, 0x21, 0x3F, 0x7F, 0x00, 0xA9,
    4, 0x22, 0x07, 0xE5, 0x01, 0xFF,
    1, 0x70, 0xF1,
    4, 0x45, 0x00, 0x08, 0x5A, 0x8B,
    8, 0x3A, 0x00, 0x18, 0x12, 0x78, 0x00, 0x7F, 0xFF, 0x51,
    8, 0x3D, 0x00, 0x70, 0x0F, 0xE8, 0x00, 0x7F, 0xF9, 0x2C,
    8, 0x47, 0x00, 0x70, 0x0F, 0xE8, 0x00, 0x7F, 0xE0, 0x69,
    8, 0xAC, 0x00, 0x70, 0x0F, 0xE8, 0x00, 0x7F, 0xFF, 0x3E,
    0x00,
};

U8 AmpmasterSWMute[] =
{
    1, 0x06, 0x03,
    0x00,
};

U8 AmpmasterSWUnMute[] =
{
    1, 0x06, 0x00,
    0x00,
};

BOOL DevI2S_RT9113_Init(void)
{
    U8 * Pstr=NULL;
    U8 DataLength = 0;
    printf("*****Amplifier_Init****\n");
    Audio_Amplifier_ON();
    msAPI_Timer_Delayms(2);
    Adj_Volume_On();
    msAPI_Timer_Delayms(40);

    Pstr = AmpReadTbl;
    DataLength = *Pstr;
    g_ucRT9113BRegAddr = *(++Pstr);
    Pstr++;
    if(MApi_SWI2C_ReadBytes(RT9113B_BUSID, 1, &g_ucRT9113BRegAddr, DataLength, Pstr) != TRUE)
    {
        printf("MApi_SWI2C_ReadBytes FAIL!!\n");
        return FALSE;
    }
    printf("==========RT9113B chip id is:%d==========\n", AmpReadTbl[2]);

    if(AmpReadTbl[2] == 0x00)       //chip revision ID(0x00-TKA188E,0xff-RA188B)
    {
        Pstr = AmpInitTblTka188e;
    }
    else
    {
        Pstr = AmpInitTblRa188b;
    }

    do
    {
        DataLength = *Pstr;
        if(DataLength>MAX_DATA_LENGTH)
        {
            printf("** RT9113 set command error!!\n");
            break;
        }
        g_ucRT9113BRegAddr = *(++Pstr);
        Pstr++;
        if (MApi_SWI2C_WriteBytes(RT9113B_BUSID,1,&g_ucRT9113BRegAddr,DataLength, Pstr) == FALSE)
        {
            printf("** RT9113 write fail = %d\n",g_ucRT9113BRegAddr);
        }
        msAPI_Timer_Delayms(2);

        Pstr = Pstr + DataLength;
    }while(*Pstr != 0);

    return TRUE;
}


BOOL DevI2S_RT9113_SWMute(BOOL bMute)
{
    U8 * Pstr = NULL;
    U8 DataLength = 0;

    printf("******Amplifier_RT9113_SWMute(%d)\n",bMute);
    if(bMute)
    {
        Pstr=AmpmasterSWMute;
        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("9113 set command error!!\n");
                break;
            }
            g_ucRT9113BRegAddr = *(++Pstr);
            Pstr++;

            if (MApi_SWI2C_WriteBytes(RT9113B_BUSID,1, &g_ucRT9113BRegAddr, DataLength, Pstr) == FALSE)
            {
                printf("9113write fail = %d\n",g_ucRT9113BRegAddr);
            }
            msAPI_Timer_Delayms(2);
            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);
    }
    else
    {

        Pstr=AmpmasterSWUnMute;
        do
        {
            DataLength = *Pstr;
            if(DataLength>20)
            {
                printf("9113 set command error!!\n");
                break;
            }
            g_ucRT9113BRegAddr = *(++Pstr);
            Pstr++;

            if (MApi_SWI2C_WriteBytes(RT9113B_BUSID,1, &g_ucRT9113BRegAddr, DataLength, Pstr) == FALSE)
            {
                printf("9113write fail = %d\n",g_ucRT9113BRegAddr);
            }
            msAPI_Timer_Delayms(2);

            Pstr = Pstr + DataLength;
        }while(*Pstr != 0);
    }
    return TRUE;
}

BOOL DevI2S_RT9113_Mute(BOOL bMute)
{
    // TODO: HW no use
    UNUSED(bMute);
    return TRUE;
}

#endif/*End __DEVI2S_RT9113B_C__*/

