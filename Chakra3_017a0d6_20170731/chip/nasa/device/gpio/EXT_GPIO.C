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
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include "sysinfo.h"
#include "hwreg.h"
#include "SysInit.h"
#include "debug.h"
#include "drvGPIO.h"
#include "drvGlobal.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"

#define ASSERT(expr)    __ASSERT(expr)

//-----------------------------------------------------------------
// 8-bit I2C IO expander for GPIO
//-----------------------------------------------------------------
#if (I2C_IO_EXPANDER_TYPE != I2C_IO_EXPANDER_NONE)

#include "drvIIC.h"

#ifndef I2C_IO_EXPANDER_P0_IS_GPIO
    #define I2C_IO_EXPANDER_P0_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P1_IS_GPIO
    #define I2C_IO_EXPANDER_P1_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P2_IS_GPIO
    #define I2C_IO_EXPANDER_P2_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P3_IS_GPIO
    #define I2C_IO_EXPANDER_P3_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P4_IS_GPIO
    #define I2C_IO_EXPANDER_P4_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P5_IS_GPIO
    #define I2C_IO_EXPANDER_P5_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P6_IS_GPIO
    #define I2C_IO_EXPANDER_P6_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P7_IS_GPIO
    #define I2C_IO_EXPANDER_P7_IS_GPIO 0
#endif


#if (I2C_IO_EXPANDER_TYPE == I2C_IO_EXPANDER_MSG1016RC)
#ifndef I2C_IO_EXPANDER_P8_IS_GPIO
    #define I2C_IO_EXPANDER_P8_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P9_IS_GPIO
    #define I2C_IO_EXPANDER_P9_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P10_IS_GPIO
    #define I2C_IO_EXPANDER_P10_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P11_IS_GPIO
    #define I2C_IO_EXPANDER_P11_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P12_IS_GPIO
    #define I2C_IO_EXPANDER_P12_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P13_IS_GPIO
    #define I2C_IO_EXPANDER_P13_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P14_IS_GPIO
    #define I2C_IO_EXPANDER_P14_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P15_IS_GPIO
    #define I2C_IO_EXPANDER_P15_IS_GPIO 0
#endif
//***
#ifndef I2C_IO_EXPANDER_P16_IS_GPIO
    #define I2C_IO_EXPANDER_P16_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P17_IS_GPIO
    #define I2C_IO_EXPANDER_P17_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P18_IS_GPIO
    #define I2C_IO_EXPANDER_P18_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P19_IS_GPIO
    #define I2C_IO_EXPANDER_P19_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P20_IS_GPIO
    #define I2C_IO_EXPANDER_P20_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P21_IS_GPIO
    #define I2C_IO_EXPANDER_P21_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P22_IS_GPIO
    #define I2C_IO_EXPANDER_P22_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P23_IS_GPIO
    #define I2C_IO_EXPANDER_P23_IS_GPIO 0
#endif
//***
#ifndef I2C_IO_EXPANDER_P24_IS_GPIO
    #define I2C_IO_EXPANDER_P24_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P25_IS_GPIO
    #define I2C_IO_EXPANDER_P25_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P26_IS_GPIO
    #define I2C_IO_EXPANDER_P26_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P27_IS_GPIO
    #define I2C_IO_EXPANDER_P27_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P28_IS_GPIO
    #define I2C_IO_EXPANDER_P28_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P29_IS_GPIO
    #define I2C_IO_EXPANDER_P29_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P30_IS_GPIO
    #define I2C_IO_EXPANDER_P30_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P31_IS_GPIO
    #define I2C_IO_EXPANDER_P31_IS_GPIO 0
#endif

//***
#ifndef I2C_IO_EXPANDER_P32_IS_GPIO
    #define I2C_IO_EXPANDER_P32_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P33_IS_GPIO
    #define I2C_IO_EXPANDER_P33_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P34_IS_GPIO
    #define I2C_IO_EXPANDER_P34_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P35_IS_GPIO
    #define I2C_IO_EXPANDER_P35_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P36_IS_GPIO
    #define I2C_IO_EXPANDER_P36_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P37_IS_GPIO
    #define I2C_IO_EXPANDER_P37_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P38_IS_GPIO
    #define I2C_IO_EXPANDER_P38_IS_GPIO 0
#endif
#ifndef I2C_IO_EXPANDER_P39_IS_GPIO
    #define I2C_IO_EXPANDER_P39_IS_GPIO 0
#endif


#endif //I2C_IO_EXPANDER_MSG1016RC
#define I2C_IO_OEN  ((I2C_IO_EXPANDER_P0_IS_GPIO <= GPIO_IN ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P1_IS_GPIO <= GPIO_IN ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P2_IS_GPIO <= GPIO_IN ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P3_IS_GPIO <= GPIO_IN ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P4_IS_GPIO <= GPIO_IN ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P5_IS_GPIO <= GPIO_IN ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P6_IS_GPIO <= GPIO_IN ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P7_IS_GPIO <= GPIO_IN ? BIT7 : 0))

#define I2C_IO_OUT  ((I2C_IO_EXPANDER_P0_IS_GPIO == GPIO_OUT_HIGH ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P1_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P2_IS_GPIO == GPIO_OUT_HIGH ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P3_IS_GPIO == GPIO_OUT_HIGH ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P4_IS_GPIO == GPIO_OUT_HIGH ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P5_IS_GPIO == GPIO_OUT_HIGH ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P6_IS_GPIO == GPIO_OUT_HIGH ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P7_IS_GPIO == GPIO_OUT_HIGH ? BIT7 : 0))

#if (I2C_IO_EXPANDER_TYPE == I2C_IO_EXPANDER_PCA9557)
//-----------------------------------------------------------------
// PCA9557
// 8-bit I2C and SMBus I/O port with reset
//-----------------------------------------------------------------

static U8 PCA9557_u8OUT = I2C_IO_OUT;
static U8 PCA9557_u8OEN = I2C_IO_OEN;

void MDrv_ExGPIO_Init(void)
{
    U8 u8Loop;

    // Input Polarity Inversion
    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteByte(I2C_IO_EXPANDER_ADDR, 2, 0x00) != FALSE)
            break;
    ASSERT(u8Loop);

    // Initial Output Data
    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteByte(I2C_IO_EXPANDER_ADDR, 1, I2C_IO_OUT) != FALSE)
            break;
    ASSERT(u8Loop);

    // I/O direction
    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteByte(I2C_IO_EXPANDER_ADDR, 3, I2C_IO_OEN) != FALSE)
            break;
    ASSERT(u8Loop);
}

void MDrv_ExGPIO_Dir(U8 u8BitMask, BOOLEAN bIsInput)
{
    U8 u8Loop;

    if (bIsInput)
        PCA9557_u8OEN |= u8BitMask;
    else
        PCA9557_u8OEN &= ~u8BitMask;

    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteByte(I2C_IO_EXPANDER_ADDR, 3, PCA9557_u8OEN) != FALSE)
            break;
    ASSERT(u8Loop);
}

void MDrv_ExGPIO_Set(U8 u8BitMask, BOOLEAN bHigh)
{
    U8 u8Loop;

    if (bHigh)
        PCA9557_u8OUT |= u8BitMask;
    else
        PCA9557_u8OUT &= ~u8BitMask;

    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteByte(I2C_IO_EXPANDER_ADDR, 1, PCA9557_u8OUT) != FALSE)
            break;
    ASSERT(u8Loop);
}

BIT MDrv_ExGPIO_Get(U8 u8BitMask)
{
    U8 u8Loop;
    U8 u8Input;

    u8Input = 0;

    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_ReadByte(I2C_IO_EXPANDER_ADDR, 0, &u8Input) != FALSE)
            break;
    ASSERT(u8Loop);

    return (BIT)(u8Input & u8BitMask);
}

#elif (I2C_IO_EXPANDER_TYPE == I2C_IO_EXPANDER_PCF8574)
//-----------------------------------------------------------------
// PCF8574
// Remote 8-bit I/O expander for I2C-bus
//-----------------------------------------------------------------

static U8 PCF8574_u8OUT = I2C_IO_OUT;

void MDrv_ExGPIO_Init(void)
{
    U8 u8Loop;

    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR, 0, 0, 1, &PCF8574_u8OUT) != FALSE)
            break;
    ASSERT(u8Loop);
}

void MDrv_ExGPIO_Dir(U8 u8BitMask, BOOLEAN bIsInput)
{
    // nothing to do
    UNUSED(u8BitMask);
    UNUSED(bIsInput);
}

void MDrv_ExGPIO_Set(U8 u8BitMask, BOOLEAN bHigh)
{
    U8 u8Loop;

    if (bHigh)
        PCF8574_u8OUT |= u8BitMask;
    else
        PCF8574_u8OUT &= ~u8BitMask;

    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR, 0, 0, 1, &PCF8574_u8OUT) != FALSE)
            break;
    ASSERT(u8Loop);
}

BIT MDrv_ExGPIO_Get(U8 u8BitMask)
{
    U8 u8Loop;
    U8 u8Input;

    u8Input = 0;

    for (u8Loop = 3; u8Loop > 0; u8Loop--)
        if (MDrv_IIC_ReadBytes(I2C_IO_EXPANDER_ADDR, 0, 0, 1, &u8Input) != FALSE)
            break;
    ASSERT(u8Loop);

    return (BIT)(u8Input & u8BitMask);
}


#elif (I2C_IO_EXPANDER_TYPE == I2C_IO_EXPANDER_MSG1016RC)

#define I2C_IO_OEN0  ((I2C_IO_EXPANDER_P0_IS_GPIO <= GPIO_IN ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P1_IS_GPIO <= GPIO_IN ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P2_IS_GPIO <= GPIO_IN ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P3_IS_GPIO <= GPIO_IN ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P4_IS_GPIO <= GPIO_IN ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P5_IS_GPIO <= GPIO_IN ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P6_IS_GPIO <= GPIO_IN ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P7_IS_GPIO <= GPIO_IN ? BIT7 : 0))

#define I2C_IO_OEN1  ((I2C_IO_EXPANDER_P8_IS_GPIO <= GPIO_IN ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P9_IS_GPIO <= GPIO_IN ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P10_IS_GPIO <= GPIO_IN ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P11_IS_GPIO <= GPIO_IN ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P12_IS_GPIO <= GPIO_IN ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P13_IS_GPIO <= GPIO_IN ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P14_IS_GPIO <= GPIO_IN ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P15_IS_GPIO <= GPIO_IN ? BIT7 : 0))
#define I2C_IO_OEN2  ((I2C_IO_EXPANDER_P16_IS_GPIO <= GPIO_IN ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P17_IS_GPIO <= GPIO_IN ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P18_IS_GPIO <= GPIO_IN ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P19_IS_GPIO <= GPIO_IN ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P20_IS_GPIO <= GPIO_IN ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P21_IS_GPIO <= GPIO_IN ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P22_IS_GPIO <= GPIO_IN ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P23_IS_GPIO <= GPIO_IN ? BIT7 : 0))

#define I2C_IO_OEN3  ((I2C_IO_EXPANDER_P24_IS_GPIO <= GPIO_IN ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P25_IS_GPIO <= GPIO_IN ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P26_IS_GPIO <= GPIO_IN ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P27_IS_GPIO <= GPIO_IN ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P28_IS_GPIO <= GPIO_IN ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P29_IS_GPIO <= GPIO_IN ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P30_IS_GPIO <= GPIO_IN ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P31_IS_GPIO <= GPIO_IN ? BIT7 : 0))

#define I2C_IO_OEN4  ((I2C_IO_EXPANDER_P32_IS_GPIO <= GPIO_IN ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P33_IS_GPIO <= GPIO_IN ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P34_IS_GPIO <= GPIO_IN ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P35_IS_GPIO <= GPIO_IN ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P36_IS_GPIO <= GPIO_IN ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P37_IS_GPIO <= GPIO_IN ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P38_IS_GPIO <= GPIO_IN ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P39_IS_GPIO <= GPIO_IN ? BIT7 : 0))


#define I2C_IO_OUT0  ((I2C_IO_EXPANDER_P0_IS_GPIO == GPIO_OUT_HIGH ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P1_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P2_IS_GPIO == GPIO_OUT_HIGH ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P3_IS_GPIO == GPIO_OUT_HIGH ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P4_IS_GPIO == GPIO_OUT_HIGH ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P5_IS_GPIO == GPIO_OUT_HIGH ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P6_IS_GPIO == GPIO_OUT_HIGH ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P7_IS_GPIO == GPIO_OUT_HIGH ? BIT7 : 0) )

#define I2C_IO_OUT1  ((I2C_IO_EXPANDER_P8_IS_GPIO == GPIO_OUT_HIGH ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P9_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P10_IS_GPIO == GPIO_OUT_HIGH ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P11_IS_GPIO == GPIO_OUT_HIGH ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P12_IS_GPIO == GPIO_OUT_HIGH ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P13_IS_GPIO == GPIO_OUT_HIGH ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P14_IS_GPIO == GPIO_OUT_HIGH ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P15_IS_GPIO == GPIO_OUT_HIGH ? BIT7 : 0) )


#define I2C_IO_OUT2  ((I2C_IO_EXPANDER_P16_IS_GPIO == GPIO_OUT_HIGH ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P17_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P18_IS_GPIO == GPIO_OUT_HIGH ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P19_IS_GPIO == GPIO_OUT_HIGH ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P20_IS_GPIO == GPIO_OUT_HIGH ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P21_IS_GPIO == GPIO_OUT_HIGH ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P22_IS_GPIO == GPIO_OUT_HIGH ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P23_IS_GPIO == GPIO_OUT_HIGH ? BIT7 : 0) )

#define I2C_IO_OUT3  ((I2C_IO_EXPANDER_P24_IS_GPIO == GPIO_OUT_HIGH ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P25_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P26_IS_GPIO == GPIO_OUT_HIGH ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P27_IS_GPIO == GPIO_OUT_HIGH ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P28_IS_GPIO == GPIO_OUT_HIGH ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P29_IS_GPIO == GPIO_OUT_HIGH ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P30_IS_GPIO == GPIO_OUT_HIGH ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P31_IS_GPIO == GPIO_OUT_HIGH ? BIT7 : 0) )

#define I2C_IO_OUT4  ((I2C_IO_EXPANDER_P32_IS_GPIO == GPIO_OUT_HIGH ? BIT0 : 0) | \
                     (I2C_IO_EXPANDER_P33_IS_GPIO == GPIO_OUT_HIGH ? BIT1 : 0) | \
                     (I2C_IO_EXPANDER_P34_IS_GPIO == GPIO_OUT_HIGH ? BIT2 : 0) | \
                     (I2C_IO_EXPANDER_P35_IS_GPIO == GPIO_OUT_HIGH ? BIT3 : 0) | \
                     (I2C_IO_EXPANDER_P36_IS_GPIO == GPIO_OUT_HIGH ? BIT4 : 0) | \
                     (I2C_IO_EXPANDER_P37_IS_GPIO == GPIO_OUT_HIGH ? BIT5 : 0) | \
                     (I2C_IO_EXPANDER_P38_IS_GPIO == GPIO_OUT_HIGH ? BIT6 : 0) | \
                     (I2C_IO_EXPANDER_P39_IS_GPIO == GPIO_OUT_HIGH ? BIT7 : 0) )



//static U8 MSG1016RC_u8OUT0 = I2C_IO_OUT0;
//static U8 MSG1016RC_u8OUT1 = I2C_IO_OUT1;



BOOLEAN MDrv_MILLY_IIC_WriteBytes(U16 u16BusNumSlaveID, U8 AddrCnt, U8* pu8addr, U16 u16size, U8* pBuf)
{

return MDrv_IIC_WriteBytes(u16BusNumSlaveID,AddrCnt,pu8addr,u16size,pBuf);

}

BOOLEAN MDrv_MILLY_IIC_ReadBytes(U16 u16BusNumSlaveID, U8 AddrCnt, U8* pu8addr, U16 u16size, U8* pBuf)
{

return MDrv_IIC_ReadBytes(u16BusNumSlaveID,AddrCnt,pu8addr,u16size,pBuf);

}



void MDrv_ExGPIO_Init(void)
{
    //U8 u8Loop;

    U8 cIOExpander_cPWM[2];
    U8  cIOExpanderData[2];
    U8  cIOExpanderData_1[2];
    U8  cIOExpanderData_2[2];
    U8  cIOExpander_WReg_Addr0[3] = {0x10, 0x10,0x09};
    U8  cIOExpander_WReg_Addr1[3] = {0x10, 0x10,0x0A};

    U8  cIOExpander_WReg_Addr2[3] = {0x10, 0x10,0x0B};
    U8  cIOExpander_WReg_Addr3[3] = {0x10, 0x10,0x0C};



    U8  cIOExpander_CReg_Addr0[3]  = {0x10, 0x10,0x04};
    U8  cIOExpander_CReg_Addr1[3]  = {0x10, 0x10,0x05};

    U8  cIOExpander_CReg_Addr2[3]  = {0x10, 0x10,0x06};
    U8  cIOExpander_CReg_Addr3[3]  = {0x10, 0x10,0x07};


    U8  cIOExpander_dummy[3]         = {0x10, 0x10,0x01};
    U8  cIOExpander_Init_data[5]      = {0x53, 0x45, 0x52, 0x44, 0x42};
    U8 cIOExpander_PWM_Switch[3]  = {0x10, 0x10,0x03};

    //U8 WriteData0 , WriteData1;
    U8 ReadData[1];

    ReadData[1] =0;

    cIOExpander_cPWM[1] = 0x00;
    cIOExpander_cPWM[0] = 0x00;// reset

    cIOExpanderData_1[1] = 0x00;
    cIOExpanderData_1[0] = 0x37;

    cIOExpanderData_2[1] = 0x00;
    cIOExpanderData_2[0] = 0x35;


    // Disable I2C SERDB
    cIOExpanderData[1] = 0x00;
    cIOExpanderData[0] = 0x45;

    MDrv_MILLY_IIC_WriteBytes( I2C_IO_EXPANDER_ADDR, 0, NULL, 1, cIOExpanderData );
    MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,  0, NULL, 5, cIOExpander_Init_data); // SERDB
    MDrv_MILLY_IIC_WriteBytes( I2C_IO_EXPANDER_ADDR, 0, NULL, 1, cIOExpanderData_1 );    // use bus
    MDrv_MILLY_IIC_WriteBytes( I2C_IO_EXPANDER_ADDR, 0, NULL, 1, cIOExpanderData_2 );    // wait cpu. stop microm in ioexpander

    cIOExpanderData[1] = 0x00;
    cIOExpanderData[0] = 0x00;

  //$ Initial Output Data
  // dummy
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR, 3, cIOExpander_dummy, 1, cIOExpanderData);
  //reset
  MDrv_MILLY_IIC_WriteBytes( I2C_IO_EXPANDER_ADDR, 3, cIOExpander_PWM_Switch, 1, cIOExpander_cPWM );
  //Switch to pwm
  cIOExpander_cPWM[1] = 0x00;
  cIOExpander_cPWM[0] = 0x41;
  MDrv_MILLY_IIC_WriteBytes( I2C_IO_EXPANDER_ADDR, 3, cIOExpander_PWM_Switch, 1, cIOExpander_cPWM );

  //(1)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OUT0;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR, 3, cIOExpander_WReg_Addr0, 1, cIOExpanderData);

  //(2)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OUT1;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_WReg_Addr1, 1, cIOExpanderData);


  //(3)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OUT2;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_WReg_Addr2, 1, cIOExpanderData);
  //(4)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OUT3;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_WReg_Addr3, 1, cIOExpanderData);



  //$ I/O direction
  //(1)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8 )I2C_IO_OEN0;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_CReg_Addr0, 1, cIOExpanderData);

  //(2)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OEN1;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_CReg_Addr1, 1, cIOExpanderData);

  //(3)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OEN2;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_CReg_Addr2, 1, cIOExpanderData);
  //(4)
  cIOExpanderData[1] = 0x00;
  cIOExpanderData[0] = (U8)I2C_IO_OEN3;
  MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3, cIOExpander_CReg_Addr3, 1, cIOExpanderData);

}


void MDrv_ExGPIO0_Set(U8 u8BitMask, BOOLEAN bHigh)
{
    U8 cIOExpander_WReg_Addr1[3] = {0x10, 0x10,0x09};
    U8 MSG1016RC_u8OUT               = 0xAA ;

    MDrv_MILLY_IIC_ReadBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

   // printf("Milly ---> GPIO_GET(0~7) = %bx\n", MSG1016RC_u8OUT);

    if (bHigh)
        MSG1016RC_u8OUT |= u8BitMask;
    else
        MSG1016RC_u8OUT &= ~u8BitMask;

 //   printf("Milly ---> GPIO_SET(0~7) = %bx\n", MSG1016RC_u8OUT);
    MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

}


void MDrv_ExGPIO1_Set(U8 u8BitMask, BOOLEAN bHigh)
{
    U8 cIOExpander_WReg_Addr1[3] = {0x10, 0x10,0x0A};
    U8 MSG1016RC_u8OUT               = 0xAA ;

    MDrv_MILLY_IIC_ReadBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

    //printf("Milly ---> GPIO_GET(8~15) = %bx\n", MSG1016RC_u8OUT);

    if (bHigh)
        MSG1016RC_u8OUT |= u8BitMask;
    else
        MSG1016RC_u8OUT &= ~u8BitMask;

    //printf("Milly ---> GPIO_SET(8~15) = %bx\n", MSG1016RC_u8OUT);
    MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

}


void MDrv_ExGPIO2_Set(U8 u8BitMask, BOOLEAN bHigh)
{
    U8 cIOExpander_WReg_Addr1[3] = {0x10, 0x10,0x0B};
    U8 MSG1016RC_u8OUT               = 0xAA ;

    MDrv_MILLY_IIC_ReadBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

    //printf("Milly ---> GPIO_GET(16~23) = %bx\n", MSG1016RC_u8OUT);

    if (bHigh)
        MSG1016RC_u8OUT |= u8BitMask;
    else
        MSG1016RC_u8OUT &= ~u8BitMask;

    //printf("Milly ---> GPIO_SET(16~23) = %bx\n", MSG1016RC_u8OUT);
    MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

}


void MDrv_ExGPIO3_Set(U8 u8BitMask, BOOLEAN bHigh)
{
    U8 cIOExpander_WReg_Addr1[3] = {0x10, 0x10,0x0C};
    U8 MSG1016RC_u8OUT               = 0xAA ;

    MDrv_MILLY_IIC_ReadBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

    //printf("Milly ---> GPIO_GET(24~31) = %bx\n", MSG1016RC_u8OUT);

    if (bHigh)
        MSG1016RC_u8OUT |= u8BitMask;
    else
        MSG1016RC_u8OUT &= ~u8BitMask;

    //printf("Milly ---> GPIO_SET(24~31) = %bx\n", MSG1016RC_u8OUT);
    MDrv_MILLY_IIC_WriteBytes(I2C_IO_EXPANDER_ADDR,3,
            cIOExpander_WReg_Addr1, 1, &MSG1016RC_u8OUT);

}

#endif

#endif  // !I2C_GPIO_EXPANDER

#if (EXT_SUBMCU_TYPE != EXT_SUBMCU_NONE)

#if (EXT_SUBMCU_TYPE == EXT_SUBMCU_MSTAR_UA01)

#include "drvUartDebug.h"

#define MCU_HDR             0xA5    // command header
#define MCU_RSP             0xCA    // response header

#define MCU_CMD_SET_GPIO    0x01
#define MCU_CMD_GET_GPIO    0x02
#define MCU_CMD_IR          0x03
#define MCU_CMD_KEY         0x04
#define MCU_CMD_CEC         0x05
#define MCU_CMD_STANDBY     0x06

void MDrv_SubGPIO_Set(U8 u8GpioId, BOOLEAN bHigh)
{
    U8 u8CkSum;

    putcharUART1(MCU_HDR);
    putcharUART1(MCU_CMD_SET_GPIO);     u8CkSum = MCU_CMD_SET_GPIO;
    putcharUART1(u8GpioId);             u8CkSum += u8GpioId;
    putcharUART1(bHigh);                u8CkSum += bHigh;

    putcharUART1(~u8CkSum);
}

BIT  MDrv_SubGPIO_Get(U8 u8GpioId)
{
    U16 u16Loop;
    U8 u8CkSum;
    U8 u8Char;

    putcharUART1(MCU_HDR);
    putcharUART1(MCU_CMD_GET_GPIO);     u8CkSum = MCU_CMD_GET_GPIO;
    putcharUART1(u8GpioId);             u8CkSum += u8GpioId;
    putcharUART1(~u8CkSum);

    u16Loop = 500;

    while ((!UART_GetChar(&u8Char) || u8Char != MCU_RSP) && u16Loop--)
        MsOS_DelayTask(1);
    while (!UART_GetChar(&u8Char) && u16Loop--)
        MsOS_DelayTask(1);
    while (!UART_GetChar(&u8CkSum) && u16Loop--)
        MsOS_DelayTask(1);

    // if ((u8Char + u8CkSum) != 0)   error

    return u8Char;

}

#endif

#endif  // (EXT_SUBMCU_TYPE != EXT_SUBMCU_NONE)
