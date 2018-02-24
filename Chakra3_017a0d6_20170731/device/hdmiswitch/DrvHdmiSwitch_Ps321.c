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
#define PS321_C

/********************************************************************************
// \file      Ps321.c
// \version
// \date
//
// (C) Copyright 2004 by Parade
// All rights reserved.
//
//
********************************************************************************/
#define _PS321_C_

// C Library
#include <string.h>
#include <stdio.h>

#if (INPUT_HDMI_VIDEO_COUNT>0)
#include "datatype.h"
#include "drvIIC.h"
#include "DrvHdmiSwitch_Ps321.h"

#define PSDBG(x) //x

U8 code EDIDDATA[256]=
{
#if 0
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x42, 0x49, 0x70, 0x06, 0x01, 0x00, 0x00, 0x00,
    0x07, 0x11, 0x01, 0x03, 0x81, 0x46, 0x27, 0x78, 0x0A, 0xDE, 0x58, 0xA3, 0x54, 0x4C, 0x99, 0x26,
    0x0F, 0x45, 0x47, 0xBF, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C, 0x25, 0x00,
    0xC4, 0x8E, 0x21, 0x00, 0x00, 0x9E, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C,
    0x25, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x9E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10,
    0x10, 0x3E, 0x96, 0x00, 0x13, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x50,
    0x52, 0x49, 0x20, 0x48, 0x44, 0x4D, 0x49, 0x20, 0x54, 0x56, 0x0A, 0x20, 0x00, 0x00, 0x00, 0xFD,
    0x00, 0x30, 0x56, 0x0F, 0x41, 0x09, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0xD1,
    0x02, 0x03, 0x28, 0x71, 0x48, 0x01, 0x02, 0x03, 0x04, 0x85, 0x06, 0x07, 0x10, 0x26, 0x09, 0x07,
    0x07, 0x15, 0x07, 0x50, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00,
    0xC4, 0x66, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x80, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10,
    0x10, 0x3E, 0x96, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0,
    0x1E, 0x20, 0x6E, 0x28, 0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xA0, 0x14,
    0x51, 0xF0, 0x16, 0x00, 0x26, 0x7C, 0x43, 0x00, 0x13, 0x8E, 0x21, 0x00, 0x00, 0x98, 0x8C, 0x0A,
    0xA0, 0x14, 0x51, 0xF0, 0x16, 0x00, 0x26, 0x7C, 0x43, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x98,
    0xD6, 0x09, 0x80, 0xA0, 0x20, 0xE0, 0x2D, 0x10, 0x08, 0x60, 0x22, 0x00, 0x12, 0x8E, 0x21, 0xEC,

#elif 1  // CUS_X HAxxx EDID
    0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x42, 0x49, 0x70, 0x06, 0x01, 0x00, 0x00, 0x00,
    0x07, 0x11, 0x01, 0x03, 0x81, 0x46, 0x27, 0x78, 0x0A, 0xDE, 0x58, 0xA3, 0x54, 0x4C, 0x99, 0x26,
    0x0F, 0x45, 0x47, 0xBF, 0xEE, 0x00, 0x31, 0x4F, 0x45, 0x4C, 0x45, 0x4F, 0x61, 0x4A, 0x61, 0x4F,
    0x45, 0x59, 0x01, 0x01, 0x01, 0x01, 0x01, 0x1D, 0x80, 0x18, 0x71, 0x1C, 0x16, 0x20, 0x58, 0x2C,
    0x25, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x9E, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10,
    0x10, 0x3E, 0x96, 0x00, 0x13, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x50,
    0x52, 0x49, 0x20, 0x48, 0x44, 0x4D, 0x49, 0x20, 0x54, 0x56, 0x0A, 0x20, 0x00, 0x00, 0x00, 0xFD,
    0x00, 0x30, 0x56, 0x0F, 0x41, 0x09, 0x00, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x01, 0x74,
    0x02, 0x03, 0x27, 0x71, 0x47, 0x01, 0x02, 0x03, 0x04, 0x85, 0x06, 0x07, 0x26, 0x09, 0x07, 0x07,
    0x15, 0x07, 0x50, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10, 0x3E, 0x96, 0x00, 0xC4,
    0x66, 0x03, 0x0C, 0x00, 0x10, 0x00, 0x80, 0x8C, 0x0A, 0xD0, 0x8A, 0x20, 0xE0, 0x2D, 0x10, 0x10,
    0x3E, 0x96, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x18, 0x01, 0x1D, 0x00, 0x72, 0x51, 0xD0, 0x1E,
    0x20, 0x6E, 0x28, 0x55, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x1E, 0x8C, 0x0A, 0xA0, 0x14, 0x51,
    0xF0, 0x16, 0x00, 0x26, 0x7C, 0x43, 0x00, 0x13, 0x8E, 0x21, 0x00, 0x00, 0x98, 0x8C, 0x0A, 0xA0,
    0x14, 0x51, 0xF0, 0x16, 0x00, 0x26, 0x7C, 0x43, 0x00, 0xC4, 0x8E, 0x21, 0x00, 0x00, 0x98, 0xD6,
    0x09, 0x80, 0xA0, 0x20, 0xE0, 0x2D, 0x10, 0x08, 0x60, 0x22, 0x00, 0x12, 0x8E, 0x21, 0x08, 0xF6,

#else
    0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x22,0x4C,0x4C,0x34,0x01,0x00,0x00,0x00,
    0x31,0x11,0x01,0x03,0x80,0x66,0x39,0x78,0x0A,0xD8,0x3D,0xA7,0x53,0x36,0xAB,0x26,
    0x11,0x47,0x4A,0x20,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
    0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,
    0x25,0x00,0xC4,0x8E,0x21,0x00,0x00,0x9E,0x01,0x1D,0x00,0x72,0x51,0xD0,0x1E,0x20,
    0x6E,0x28,0x55,0x00,0xC4,0x8E,0x21,0x00,0x00,0x1E,0x00,0x00,0x00,0xFC,0x00,0x4C,
    0x34,0x36,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00,0xFD,
    0x00,0x2D,0x41,0x0F,0x45,0x0F,0x00,0x0A,0x20,0x20,0x20,0x20,0x20,0x20,0x01,0x35,
    0x02,0x03,0x1E,0x71,0x4A,0x85,0x04,0x03,0x93,0x14,0x07,0x12,0x16,0x10,0x1F,0x23,
    0x09,0x07,0x07,0x83,0x01,0x00,0x00,0x66,0x03,0x0C,0x00,0x10,0x00,0x00,0x8C,0x0A,
    0xD0,0x8A,0x20,0xE0,0x2D,0x10,0x10,0x3E,0x96,0x00,0xC4,0x8E,0x21,0x00,0x00,0x18,
    0x01,0x1D,0x00,0xBC,0x52,0xD0,0x1E,0x20,0xB8,0x28,0x55,0x40,0xC4,0x8E,0x21,0x00,
    0x00,0x1E,0x01,0x1D,0x80,0xD0,0x72,0x1C,0x16,0x20,0x10,0x2C,0x25,0x80,0xC4,0x8E,
    0x21,0x00,0x00,0x9E,0x8C,0x0A,0xD0,0x90,0x20,0x40,0x31,0x20,0x0C,0x40,0x55,0x00,
    0xC4,0x8E,0x21,0x00,0x00,0x18,0x01,0x1D,0x80,0x18,0x71,0x1C,0x16,0x20,0x58,0x2C,
    0x25,0x00,0xC4,0x8E,0x21,0x00,0x00,0x9E,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,
#endif
};

BOOLEAN devPS321_IIC_WriteByte( U8 u8SlaveID, U8 u8RegAddr, U8 u8Data )
{
    return MDrv_IIC_WriteByte( u8SlaveID, u8RegAddr, u8Data );
}

BOOLEAN devPS321_IIC_ReadByte ( U8 u8SlaveID, U8 u8RegAddr, U8 *pu8Data )
{
    return MDrv_IIC_ReadByte( u8SlaveID, u8RegAddr, pu8Data );
}

void HdmiSwitch_PS321_Init(void)
{
    U8 RdValue,RdEDIDValue;
    U8 checksum2,checksum3;
    U16 i;

    PSDBG(printf("\r\n PS321 HDMI Switch Init!"));

    /* S/W Set Mode load EDID to EDID Shadow */

    // Disable Port 1/2/3 termination resistors.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, 0xE0);

    // Enable S/W Set Mode.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, EDIDBUFCTL, 0x01);

    // Load 256 bytes EDID data to PS321 EDID shadow.
    for (i=0;i<256;i++)
        devPS321_IIC_WriteByte(PS321_I2C_ADDR_EDID, 0x00+i, EDIDDATA[i]);


    // Set the Port1 CEC physical address location in the EDID shadow block1 0x9B.
    //Port2/3 Physical address location is the same as Port1.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, SWPHYADDR, PHYADDR_VAL);



    // Set Port2 CEC Physical address 0x2000.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, AB_ADDR2, AB_ADDR2_VAL);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CD_ADDR2, CD_ADDR2_VAL);

    // Calculate Port2 checksum.
    checksum2 = 0;
    for( i=128;i<255;i++)
    {
        if ( i == PHYADDR_VAL )
            checksum2 += AB_ADDR2_VAL;
        else if ( i == PHYADDR_VAL +1 )
            checksum2 += CD_ADDR2_VAL;
        else
            checksum2 += EDIDDATA[i];
    }

    checksum2 = (0x100 - (checksum2 & 0xff)) & 0xff;

    // Set Port2 checksum.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CKSUM2, checksum2);

    // Set Port3 CEC Physical address 0x3000.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, AB_ADDR3, AB_ADDR3_VAL);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CD_ADDR3, CD_ADDR3_VAL);

    // Calculate Port3 checksum.
    checksum3 = 0;
    for (i=128;i<255;i++)
    {
        if ( i == PHYADDR_VAL )
            checksum3 += AB_ADDR3_VAL;
        else if ( i == PHYADDR_VAL+1 )
            checksum3 += CD_ADDR3_VAL;
        else
            checksum3 += EDIDDATA[i];
    }

    checksum3 = (0x100 - (checksum3 & 0xff)) & 0xff;

    // Set Port3 checksum.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CKSUM3, checksum3);

    // Enable EDID readable by SCL1/SDA1, SCL2/SDA2 and SCL3/SDA3.
    // Enable software set the Physical address value for Port2 and Port3.
    // Enable software set physical address location.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, EDIDBUFCTL, 0x07);

    // Enable Port 1/2/3 termination resistors.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, 0x00);


    /* Local I2C read EDID from EDID Shadow for debug */

    // Enable SCL_CTL/SDA_CTL to read EDID shadow.
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, EDIDBUFCTL, &RdValue);//RdValue = I2CReadByte(PS321_I2C_ADDR_CTRL,EDIDBUFCTL);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, EDIDBUFCTL, RdValue | 0x20);

    // Read 256 bytes EDID from PS321 EDID shadow and print out.
    for (i=0;i<256;i++)
    {
        devPS321_IIC_ReadByte(PS321_I2C_ADDR_EDID, 0x00+i, &RdEDIDValue);//RdEDIDValue = I2CReadByte(PS321_I2C_ADDR_EDID, 0x00+i);
        /*
        printf("[%x] ", (U16)RdEDIDValue);
        if (i%15 == 0 && i!=0)
            printf("\r\n");
        */
    };

    // Disable SCL_CTL/SDA_CTL to read EDID shadow.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, EDIDBUFCTL, RdValue & 0xDF);

     /* Equalization setting */
    // Enable individual port equalization setting
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, CONFIG, &RdValue);//RdValue = I2CReadByte(PS321_I2C_ADDR_CTRL, CONFIG);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CONFIG, RdValue | 0x08);

    // Set Port1 equalization 3dB@1.65Gbps ~ 4dB@2.25Gbps.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RCV_EQ_SET, 0xa0);

    // Set Port2 equalization 12dB@1.65Gbps ~ 14dB@2.25Gbps.
    // Set Port3 equalization 12dB@1.65Gbps ~ 14dB@2.25Gbps.
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RCV_EQ_SET2, 0x88);

    // Device enters standby mode
    Ps321_Switch_HDMI_StandbyMode();

}

//cc: HDMI
//original

void Ps321_Switch_HDMI_1(void)
{
    U8 RdValue;

    /* Switch to Port 2 */
    // Set HPD2 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0xCF);

    // Disable Port2 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x40);

    // Set HPD3 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0x3F);

    // Disable Port3 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x80);

    PSDBG(printf("PS321 HDMI1"));
    /* Switch to Port 1 */
    // Set HPD1 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0xF3);

    // Disable Port1 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x20);

    // Switch to Port1
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, CONFIG, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CONFIG, (RdValue & 0x0F) | 0x10);

    // Enable Port1 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue & 0xDF);

    // Set HPD1 to HIGH
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, (RdValue & 0xF3) | 0x0C );

}

#if (INPUT_HDMI_VIDEO_COUNT >= 2)
void Ps321_Switch_HDMI_2(void)
{
    U8 RdValue;

    // Set HPD1 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0xF3);

    // Disable Port1 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x20);
    PSDBG(printf("PS321 HDMI2"));

    // Set HPD3 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0x3F);

    // Disable Port3 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x80);

    /* Switch to Port 2 */
    // Set HPD2 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0xCF);

    // Disable Port2 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x40);

    // Switch to Port2
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, CONFIG, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CONFIG, (RdValue & 0x0F) | 0x20);

    // Enable Port2 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue & 0xBF);

    // Set HPD2 to HIGH
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, (RdValue & 0xCF) | 0x30);

}
#endif

#if (INPUT_HDMI_VIDEO_COUNT >= 3)
void Ps321_Switch_HDMI_3(void)
{
    U8 RdValue;

    // Set HPD1 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0xF3);

    // Disable Port1 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x20);
    PSDBG(printf("PS321 HDMI2"));

    // Set HPD2 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0xCF);

    // Disable Port2 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x40);

    PSDBG(printf("PS321 HDMI3"));
    /* Switch to Port 3 */
    // Set HPD3 to LOW
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, RdValue & 0x3F);

    // Disable Port3 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue | 0x80);

    // Switch to Port3
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, CONFIG, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CONFIG, (RdValue & 0x0F) | 0x40);

    // Enable Port3 termination resistors
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, RTERM_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, RTERM_SET, RdValue & 0x7F);

    // Set HPD3 to HIGH
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, HPD_SET, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, (RdValue & 0x3F) | 0xC0 );

}
#endif

void Ps321_Switch_HDMI_StandbyMode(void)
{
    U8 RdValue;

    PSDBG(printf("PS321 Standby!"));
    // Device enters standby mode
    devPS321_IIC_ReadByte(PS321_I2C_ADDR_CTRL, CONFIG, &RdValue);
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, CONFIG, RdValue | 0x80);

    // Set HPD1/2/3 to LOW
    devPS321_IIC_WriteByte(PS321_I2C_ADDR_CTRL, HPD_SET, 0x00 );

}

#endif

#undef _PS321DEC_
