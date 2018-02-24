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

#ifndef __GPIO_H__
#define __GPIO_H__

#include "Board.h"
#include "apiXC.h"
#include "GPIO_macro.h"
#include "apiPNL.h"
#include "msKeypad.h"

// === Scart ID Level (FIXME: just copy from S3P) ===
// Level 0: 0V ~ 2V
// Level 1A: 4.5V ~ 7V (aspect ratio 16:9)
// Level 1B: 9.5V ~ 12V
#define SCART_ID_LEVEL_0V           0
//#define SCART_ID_LEVEL_1V         0
//#define SCART_ID_LEVEL_2V         0
#define SCART_ID_LEVEL_3V           19
#define SCART_ID_LEVEL_4V           21//31//21//35
//#define SCART_ID_LEVEL_4p5V       35
//#define SCART_ID_LEVEL_5V         35
//#define SCART_ID_LEVEL_6V         35
//#define SCART_ID_LEVEL_7V         35
#define SCART_ID_LEVEL_8V           45//60
//#define SCART_ID_LEVEL_9V         60
//#define SCART_ID_LEVEL_9p5V       60
//#define SCART_ID_LEVEL_10V        60

#ifndef SCART_16_9_LEVEL
#define SCART_16_9_LEVEL            21
#endif
#ifndef SCART_4_3_LEVEL
#define SCART_4_3_LEVEL             45
#endif

#define SCART_DETECT_LEVEL          SCART_16_9_LEVEL

#ifndef SCART_ID1_SAR_CHAN
#define SCART_ID1_SAR_CHAN          KEYPAD_ADC_CHANNEL_8 //set invalid channel
#endif

#define SCART_ID2_SAR_CHAN          0xFF //set invalid channel
//****************************************************************************
// Public attributes.
//****************************************************************************

//#define IO_EXPANDER_I2C_ID        0x70

#define GPIO_DIRECTION_OUT        0x00
#define GPIO_DIRECTOIN_IN        0x01

typedef enum
{
    ST_DET                    = 0x00,        // GPIO2                INPUT
    PANEL_CTL                = 0x01,        // GPIO15/CEC            OUTPUT
    ANT_5V_MNT                = 0x02,        // LCK/GPIO100            INPUT
    INV_CTL                    = 0x03,        // LDE/GPIO99            OUTPUT
    POWER_ON_OFF1            = 0x04,        // LHSYNC/GPIO98        OUTPUT
    TU_ERROR_N                = 0x05,        // INT2                    INPUT
    HDMI_5V                    = 0x06,        // I2S_IN_SD            INPUT
    MUTE                    = 0x07,        // SPDIF_IN                OUTPUT
    EEPROM_WP                = 0x08,        // I2S_OUT_MCK            OUTPUT
    TU_RESET_N                = 0x09,        // I2S_OUT_WS            OUTPUT
    SC_RE1                    = 0x0A,        // I2S_OUT_BCK            OUTPUT
    SC_RE2                    = 0x0B,        // I2S_OUT_BCK            OUTPUT
    LED_RED                    = 0x0C,        // SPDIF_OUT            OUTPUT
    LED_GRN                    = 0x0D,        // GPIO14/UART_TX1/CEC    OUTPUT
    SCL_D_TU                = 0x0E,        // GPIO3                SCL
    SDA_D_TU                = 0x0F,        // GPIO4                SDA
    SCL_A_TU                = 0x10,        // I2S_IN_WS/GPIO44        SCL
    SDA_A_TU                = 0x11,        // I2S_IN_BCK/GPIO45    SDA
    FLASH_WP                = 0x12,        // SAR3                    OUTPUT
    // GPIO - IO EXPANDER
    //ANT_5V_CTL                = 0x13,        // D0                    OUTPUT
    //BOOSTER                    = 0x14,        // D1                    OUTPUT
    //AGC_SPEED                = 0x15,        // D2                    OUTPUT
    //RGB_SW                    = 0x16,        // D3                    OUTPUT
    MAX_GPIO
} GPIO_NAME;

// FUNCTOIN PROTOTYPE
void msGPIO_Init(void);
void InitGPIO(void);
void InitIOExpander(void);
void SetGPIODirectionOut( GPIO_NAME eGPIOName );
void SetGPIODirectionIn( GPIO_NAME cGPIOName );
void SetGPIOHigh( GPIO_NAME eGPIOName );
void SetGPIOLow( GPIO_NAME eGPIOName );
BOOLEAN GetGPIOValue( GPIO_NAME eGPIOName );

extern U8 g_u8TransientBacklight;

//void SetPanelBacklight(bit bEnable);
void msAPI_GPIO_RegisterGPIOMethods(XC_PNL_OBJ* panel_interface);

void MApi_PNL_SetInverter(BOOLEAN bEnable);

BYTE GetScart1IDLevel(void);
BYTE GetScart2IDLevel(void);
BYTE GetSarAdcLevel(U8 u8Channel);

BOOLEAN IsScart1Connected(void);
BOOLEAN IsScart2Connected(void);
BOOLEAN IsScartRGB(void);
BOOLEAN SetSpiIndex(U8 u8SpiIndex);

BOOLEAN msAPI_GPIO_IsSourceJustConnected( INPUT_SOURCE_TYPE_t type );
BOOLEAN msAPI_GPIO_IsSourceJustDisConnected( INPUT_SOURCE_TYPE_t type );



#if (I2C_IO_EXPANDER_TYPE == I2C_IO_EXPANDER_MSG1016RC)

extern void MDrv_ExGPIO0_Set(U8 u8BitMask, BOOLEAN bHigh);
extern void MDrv_ExGPIO1_Set(U8 u8BitMask, BOOLEAN bHigh);
extern void MDrv_ExGPIO2_Set(U8 u8BitMask, BOOLEAN bHigh);
extern void MDrv_ExGPIO3_Set(U8 u8BitMask, BOOLEAN bHigh);


#endif

BOOLEAN IsScartChange(void);
void ResetScartChange(void);

#endif // __GPIO_H__
