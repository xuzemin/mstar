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
#include "hwreg.h"
#include "drvGlobal.h"
#include "MsTypes.h"
#include "chip/bond.h"

#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

#define _MapBase_nonPM_MELODY 0xA0200000
#define _MapBase_PM_MELODY    0xA0000000

#define _MEMMAP_nonPM_  _RVM1(0x0000, 0x10, 0xFF)
#define _MEMMAP_PM_     _RVM1(0x0000, 0x00, 0xFF)
#define _MEMMAP_nonPM_11_  _RVM1(0x0000, 0x11, 0xFF)

static U32 u32MapBase;

static void MDrv_PAD_WriteByte(U32 u32RegAddr, U8 u8Val)
{
    ((volatile U8*)(u32MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)] = u8Val;
}

static U8 MDrv_PAD_ReadByte(U32 u32RegAddr)
{
    return ((volatile U8*)(u32MapBase))[(u32RegAddr << 1) - (u32RegAddr & 1)];
}

static void MDrv_PAD_WriteByteMask(U32 u32Reg_addr, U8 u8Value, U8 u8Mask)
{
    U8 u8Val = MDrv_PAD_ReadByte(u32Reg_addr);

    u8Val = (u8Val & ~(u8Mask)) | (u8Value & u8Mask);
    MDrv_PAD_WriteByte(u32Reg_addr, u8Val);
}

//static code U8 padInitTbl[] =
volatile U8 code padInitTbl[]= //__attribute__((__section__ (".isp_info"))) =
{
    0x39, 0xB6, 0x5B, 0x53,     // magic code for ISP_Tool

    // programable device number
    // spi flash count
    2,
    //1 + (PIN_SPI_CZ1 != 0) + (PIN_SPI_CZ2 != 0) + (PIN_SPI_CZ3 != 0),
    0x00,                       // nor
    0x00,                       // nand
    0x00,                       // reserved
    0x00,                       // reserved
    0x00,                       // reserved

//---------------------------------------------------------------------
// GPIO Configuartion
//---------------------------------------------------------------------
    _MEMMAP_nonPM_,

    #if(PAD_TCON0_IS_GPIO != GPIO_NONE)
    #define PAD_TCON0_OEN (PAD_TCON0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_TCON0_OUT (PAD_TCON0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e5e, PAD_TCON0_OUT, BIT0),
    _RVM1(0x1e60, PAD_TCON0_OEN, BIT0),
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_tconconfig[0] = 0b
    _RVM1(0x1ef2, 0, BIT0 ),   //reg[101ef2]#0 = 0b
    //reg_fastuartmode = 0b
    _RVM1(0x1e04, 0, BIT4 ),   //reg[101e04]#4 = 0b
    //reg_3d_lr_config[2:0] = 00b
    _RVM1(0x1e10, 0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    //reg_8bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT1 ),   //reg[101ef8]#1 = 0b
    //reg_chiptop_spdif_mux_gpio10 = 0b
    _RVM1(0x1e3f, 0, BIT6 ),   //reg[101e3f]#6 = 0b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_led_mode[3:2] = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 000b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_agc_dbg[7] = 0b
    _RVM1(0x1e27, 0, BIT4 ),   //reg[101e27]#4 = 0b
    #endif

    #if(PAD_TCON1_IS_GPIO != GPIO_NONE)
    #define PAD_TCON1_OEN (PAD_TCON1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_TCON1_OUT (PAD_TCON1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e5e, PAD_TCON1_OUT, BIT1),
    _RVM1(0x1e60, PAD_TCON1_OEN, BIT1),
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_tconconfig[1] = 0b
    _RVM1(0x1ef2, 0, BIT1 ),   //reg[101ef2]#1 = 0b
    //reg_fastuartmode = 0b
    _RVM1(0x1e04, 0, BIT4 ),   //reg[101e04]#4 = 0b
    //reg_8bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT1 ),   //reg[101ef8]#1 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_led_mode[3:2] = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    //reg_spdifoutconfig = 0b
    _RVM1(0x1eaf, 0, BIT1 ),   //reg[101eaf]#1 = 0b
    //reg_parallel_TS_in_Config[1:0]= 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_agc_dbg = 0
    _RVM1(0x1e27, 0, BIT4 ),   //reg[101e27] #4 = 0
    #endif

    #if(PAD_TCON2_IS_GPIO != GPIO_NONE)
    #define PAD_TCON2_OEN (PAD_TCON2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_TCON2_OUT (PAD_TCON2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e5e, PAD_TCON2_OUT, BIT2),
    _RVM1(0x1e60, PAD_TCON2_OEN, BIT2),
    //reg_tconconfig[2]= 0b
    _RVM1(0x1ef2, 0, BIT2 ),   //reg[101ef2]#2 = 0b
    //reg_chiptop_dummy_3[9] = 0b
    _RVM1(0x1e3f, 0, BIT1 ),   //reg[101e3f]#1 = 0b
    //reg_8bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT1 ),   //reg[101ef8]#1 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_led_mode[3:2] = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    #endif

    #if(PAD_TCON3_IS_GPIO != GPIO_NONE)
    #define PAD_TCON3_OEN (PAD_TCON3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_TCON3_OUT (PAD_TCON3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e5e, PAD_TCON3_OUT, BIT3),
    _RVM1(0x1e60, PAD_TCON3_OEN, BIT3),
    //reg_tconconfig[3]= 0b
    _RVM1(0x1ef2, 0, BIT3 ),   //reg[101ef2]#3 = 0b
    //reg_chiptop_dummy_3[9] = 0b
    _RVM1(0x1e3f, 0, BIT1 ),   //reg[101e3f]#1 = 0b
    //reg_8bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT1 ),   //reg[101ef8]#1 = 0b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_led_mode[3:2] = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    #endif

    #if(PAD_TCON4_IS_GPIO != GPIO_NONE)
    #define PAD_TCON4_OEN (PAD_TCON4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_TCON4_OUT (PAD_TCON4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e5e, PAD_TCON4_OUT, BIT4),
    _RVM1(0x1e60, PAD_TCON4_OEN, BIT4),
    //reg_tconconfig[4]=0b
    _RVM1(0x1ef2, 0, BIT4 ),   //reg[101ef2]#4 =0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] =000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_TCON5_IS_GPIO != GPIO_NONE)
    #define PAD_TCON5_OEN (PAD_TCON5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_TCON5_OUT (PAD_TCON5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e5e, PAD_TCON5_OUT, BIT5),
    _RVM1(0x1e60, PAD_TCON5_OEN, BIT5),
    //reg_tconconfig[5]= 0b
    _RVM1(0x1ef2, 0, BIT5 ),   //reg[101ef2]#5 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_TCON6_IS_GPIO != GPIO_NONE)
    #define PAD_TCON6_OEN (PAD_TCON6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_TCON6_OUT (PAD_TCON6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e5e, PAD_TCON6_OUT, BIT6),
    _RVM1(0x1e60, PAD_TCON6_OEN, BIT6),
    //reg_tconconfig[6]= 0b
    _RVM1(0x1ef2, 0, BIT6 ),   //reg[101ef2]#6 = 0b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_TCON7_IS_GPIO != GPIO_NONE)
    #define PAD_TCON7_OEN (PAD_TCON7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_TCON7_OUT (PAD_TCON7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e5e, PAD_TCON7_OUT, BIT7),
    _RVM1(0x1e60, PAD_TCON7_OEN, BIT7),
    //reg_tconconfig[7]= 0b
    _RVM1(0x1ef2, 0, BIT7 ),   //reg[101ef2]#7 = 0b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_PWM3_IS_GPIO != GPIO_NONE)
    #define PAD_PWM3_OEN (PAD_PWM3_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_PWM3_OUT (PAD_PWM3_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e85, PAD_PWM3_OUT, BIT7),
    _RVM1(0x1e87, PAD_PWM3_OEN, BIT7),
    //reg_PWM3Config = 0b
    _RVM1(0x1e40, 0, BIT7 ),   //reg[101e40]#7 = 0b
    #endif

    #if(PAD_PWM2_IS_GPIO != GPIO_NONE)
    #define PAD_PWM2_OEN (PAD_PWM2_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_PWM2_OUT (PAD_PWM2_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e85, PAD_PWM2_OUT, BIT6),
    _RVM1(0x1e87, PAD_PWM2_OEN, BIT6),
    //reg_PWM2Config = 0b
    _RVM1(0x1e40, 0, BIT6 ),   //reg[101e40]#6 = 0b
    #endif

    #if(PAD_PWM1_IS_GPIO != GPIO_NONE)
    #define PAD_PWM1_OEN (PAD_PWM1_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_PWM1_OUT (PAD_PWM1_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e85, PAD_PWM1_OUT, BIT5),
    _RVM1(0x1e87, PAD_PWM1_OEN, BIT5),
    //reg_mhl_vbus_config[2:0] = 000b
    _RVM1(0x1ef9, 0, BIT7|BIT6|BIT5 ),   //reg[101ef9]#7~#5 = 000b
    //reg_chiptop_dummy_3[13] = 0b
    _RVM1(0x1e3f, 0, BIT5 ),   //reg[101e3f]#5 = 0b
    //reg_PWM1Config = 0b
    _RVM1(0x1e40, 0, BIT5 ),   //reg[101e40]#5 = 0b
    #endif

    #if(PAD_PWM0_IS_GPIO != GPIO_NONE)
    #define PAD_PWM0_OEN (PAD_PWM0_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_PWM0_OUT (PAD_PWM0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e85, PAD_PWM0_OUT, BIT4),
    _RVM1(0x1e87, PAD_PWM0_OEN, BIT4),
    //reg_mhl_vbus_config[2:0] = 000b
    _RVM1(0x1ef9, 0, BIT7|BIT6|BIT5 ),   //reg[101ef9]#7~#5 = 000b
    //reg_PWM0Config = 0b
    _RVM1(0x1e40, 0, BIT4 ),   //reg[101e40]#4 = 0b
    #endif

    #if(PAD_LVSYNC_IS_GPIO != GPIO_NONE)
    #define PAD_LVSYNC_OEN (PAD_LVSYNC_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_LVSYNC_OUT (PAD_LVSYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x329e, PAD_LVSYNC_OUT, BIT0),
    _RVM1(0x32a2, PAD_LVSYNC_OEN, BIT0),
    //reg_output_conf[1:0]
    _RVM1(0x32da, 0, BIT1|BIT0 ),   //reg[1032da]#1~#0 = 00b
    //reg_ext_data_en[0]
    _RVM1(0x328c, BIT0 , BIT0 ),   //reg[10328c]#0 = 1b
    //reg_gpo_sel[0]
    _RVM1(0x329a, BIT0 , BIT0 ),   //reg[10329a]#0 = 1b
    //_RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_LHSYNC_IS_GPIO != GPIO_NONE)
    #define PAD_LHSYNC_OEN (PAD_LHSYNC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_LHSYNC_OUT (PAD_LHSYNC_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x329e, PAD_LHSYNC_OUT, BIT1),
    _RVM1(0x32a2, PAD_LHSYNC_OEN, BIT1),
    //reg_output_conf[1:0]
    _RVM1(0x32da, 0, BIT1|BIT0 ),   //reg[1032da]#1~#0 = 00b
    //reg_ext_data_en[1]
    _RVM1(0x328c, BIT1 , BIT1 ),   //reg[10328c]#1 = 1b
    //reg_gpo_sel[1]
    _RVM1(0x329a, BIT1 , BIT1 ),   //reg[10329a]#1 = 1b
    //_RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_LDE_IS_GPIO != GPIO_NONE)
    #define PAD_LDE_OEN (PAD_LDE_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LDE_OUT (PAD_LDE_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x329e, PAD_LDE_OUT, BIT2),
    _RVM1(0x32a2, PAD_LDE_OEN, BIT2),
    //reg_output_conf[3:2]
    _RVM1(0x32da, 0, BIT3|BIT2 ),   //reg[1032da]#3~#2 = 00b
    //reg_ext_data_en[2]
    _RVM1(0x328c, BIT2 , BIT2 ),   //reg[10328c]#2 = 1b
    //reg_gpo_sel[2]
    _RVM1(0x329a, BIT2 , BIT2 ),   //reg[10329a]#2 = 1b
    //_RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_LCK_IS_GPIO != GPIO_NONE)
    #define PAD_LCK_OEN (PAD_LCK_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_LCK_OUT (PAD_LCK_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x329e, PAD_LCK_OUT, BIT3),
    _RVM1(0x32a2, PAD_LCK_OEN, BIT3),
    //reg_output_conf[3:2]
    _RVM1(0x32da, 0, BIT3|BIT2 ),   //reg[1032da]#3~#2 = 00b
    //reg_ext_data_en[3]
    _RVM1(0x328c, BIT3 , BIT3 ),   //reg[10328c]#3 = 1b
    //reg_gpo_sel[3]
    _RVM1(0x329a, BIT3 , BIT3 ),   //reg[10329a]#3 = 1b
    //_RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD7_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD7_OEN (PAD_R_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_R_ODD7_OUT (PAD_R_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x329e, PAD_R_ODD7_OUT, BIT4),
    _RVM1(0x32a2, PAD_R_ODD7_OEN, BIT4),
    //reg_output_conf[5:4]
    _RVM1(0x32da, 0, BIT5|BIT4 ),   //reg[1032da]#5~#4 = 00b
    //reg_ext_data_en[4]
    _RVM1(0x328c, BIT4 , BIT4 ),   //reg[10328c]#4 = 1b
    //reg_gpo_sel[12]
    _RVM1(0x329a, BIT4 , BIT4 ),   //reg[10329a]#4 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD6_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD6_OEN (PAD_R_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_R_ODD6_OUT (PAD_R_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x329e, PAD_R_ODD6_OUT, BIT5),
    _RVM1(0x32a2, PAD_R_ODD6_OEN, BIT5),
    //reg_output_conf[5:4]
    _RVM1(0x32da, 0, BIT5|BIT4 ),   //reg[1032da]#5~#4 = 00b
    //reg_ext_data_en[5]
    _RVM1(0x328c, BIT5 , BIT5 ),   //reg[10328c]#5 = 1b
    //reg_gpo_sel[5]
    _RVM1(0x329a, BIT5 , BIT5 ),   //reg[10329a]#5 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD5_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD5_OEN (PAD_R_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_R_ODD5_OUT (PAD_R_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x329e, PAD_R_ODD5_OUT, BIT6),
    _RVM1(0x32a2, PAD_R_ODD5_OEN, BIT6),
    //reg_output_conf[7:6]
    _RVM1(0x32da, 0, BIT7|BIT6 ),   //reg[1032da]#7~#6 = 00b
    //reg_ext_data_en[6]
    _RVM1(0x328c, BIT6 , BIT6 ),   //reg[10328c]#6 = 1b
    //reg_gpo_sel[6]
    _RVM1(0x329a, BIT6 , BIT6 ),   //reg[10329a]#6 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD4_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD4_OEN (PAD_R_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_R_ODD4_OUT (PAD_R_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x329e, PAD_R_ODD4_OUT, BIT7),
    _RVM1(0x32a2, PAD_R_ODD4_OEN, BIT7),
    //reg_output_conf[7:6]
    _RVM1(0x32da, 0, BIT7|BIT6 ),   //reg[1032da]#7~#6 = 00b
    //reg_ext_data_en[7]
    _RVM1(0x328c, BIT7 , BIT7 ),   //reg[10328c]#7 = 1b
    //reg_gpo_sel[7]
    _RVM1(0x329a, BIT7 , BIT7 ),   //reg[10329a]#7 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD3_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD3_OEN (PAD_R_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_R_ODD3_OUT (PAD_R_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x329f, PAD_R_ODD3_OUT, BIT0),
    _RVM1(0x32a3, PAD_R_ODD3_OEN, BIT0),
    //reg_output_conf[9:8]
    _RVM1(0x32db, 0, BIT1|BIT0 ),   //reg[1032db]#1~#0 = 00b
    //reg_ext_data_en[8]
    _RVM1(0x328d, BIT0 , BIT0 ),   //reg[10328d]#0 = 1b
    //reg_gpo_sel[8]
    _RVM1(0x329b, BIT0 , BIT0 ),   //reg[10329b]#0 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD2_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD2_OEN (PAD_R_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_R_ODD2_OUT (PAD_R_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x329f, PAD_R_ODD2_OUT, BIT1),
    _RVM1(0x32a3, PAD_R_ODD2_OEN, BIT1),
    //reg_output_conf[9:8]
    _RVM1(0x32db, 0, BIT1|BIT0 ),   //reg[1032db]#1~#0 = 00b
    //reg_ext_data_en[9]
    _RVM1(0x328d, BIT1 , BIT1 ),   //reg[10328d]#1 = 1b
    //reg_gpo_sel[9]
    _RVM1(0x329b, BIT1 , BIT1 ),   //reg[10329b]#1 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD1_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD1_OEN (PAD_R_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_R_ODD1_OUT (PAD_R_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x329f, PAD_R_ODD1_OUT, BIT2),
    _RVM1(0x32a3, PAD_R_ODD1_OEN, BIT2),
    //reg_output_conf[11:10]
    _RVM1(0x32db, 0, BIT3|BIT2 ),   //reg[1032db]#3~#2 = 00b
    //reg_ext_data_en[10]
    _RVM1(0x328d, BIT2 , BIT2 ),   //reg[10328d]#2 = 1b
    //reg_gpo_sel[10]
    _RVM1(0x329b, BIT2 , BIT2 ),   //reg[10329b]#2 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_R_ODD0_IS_GPIO != GPIO_NONE)
    #define PAD_R_ODD0_OEN (PAD_R_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_R_ODD0_OUT (PAD_R_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x329f, PAD_R_ODD0_OUT, BIT3),
    _RVM1(0x32a3, PAD_R_ODD0_OEN, BIT3),
    //reg_output_conf[11:10]
    _RVM1(0x32db, 0, BIT3|BIT2 ),   //reg[1032db]#3~#2 = 00b
    //reg_ext_data_en[11]
    _RVM1(0x328d, BIT3 , BIT3 ),   //reg[10328d]#3 = 1b
    //reg_gpo_sel[11]
    _RVM1(0x329b, BIT3 , BIT3 ),   //reg[10329b]#3 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD7_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD7_OEN (PAD_G_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_G_ODD7_OUT (PAD_G_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x329f, PAD_G_ODD7_OUT, BIT4),
    _RVM1(0x32a3, PAD_G_ODD7_OEN, BIT4),
    //reg_output_conf[13:12]
    _RVM1(0x32db, 0, BIT5|BIT4 ),   //reg[1032db]#5~#4 = 00b
    //reg_ext_data_en[12]
    _RVM1(0x328d, BIT4 , BIT4 ),   //reg[10328d]#4 = 1b
    //reg_gpo_sel[12]
    _RVM1(0x329b, BIT4 , BIT4 ),   //reg[10329b]#4 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD6_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD6_OEN (PAD_G_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_G_ODD6_OUT (PAD_G_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x329f, PAD_G_ODD6_OUT, BIT5),
    _RVM1(0x32a3, PAD_G_ODD6_OEN, BIT5),
    //reg_output_conf[13:12]
    _RVM1(0x32db, 0, BIT5|BIT4 ),   //reg[1032db]#5~#4 = 00b
    //reg_ext_data_en[13]
    _RVM1(0x328d, BIT5 , BIT5 ),   //reg[10328d]#5 = 1b
    //reg_gpo_sel[13]
    _RVM1(0x329b, BIT5 , BIT5 ),   //reg[10329b]#5 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD5_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD5_OEN (PAD_G_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_G_ODD5_OUT (PAD_G_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x329f, PAD_G_ODD5_OUT, BIT6),
    _RVM1(0x32a3, PAD_G_ODD5_OEN, BIT6),
    //reg_output_conf[15:14]
    _RVM1(0x32db, 0, BIT7|BIT6 ),   //reg[1032db]#7~#6 = 00b
    //reg_ext_data_en[14]
    _RVM1(0x328d, BIT6 , BIT6 ),   //reg[10328d]#6 = 1b
    //reg_gpo_sel[14]
    _RVM1(0x329b, BIT6 , BIT6 ),   //reg[10329b]#6 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD4_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD4_OEN (PAD_G_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_G_ODD4_OUT (PAD_G_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x329f, PAD_G_ODD4_OUT, BIT7),
    _RVM1(0x32a3, PAD_G_ODD4_OEN, BIT7),
    //reg_output_conf[15:14]
    _RVM1(0x32db, 0, BIT7|BIT6 ),   //reg[1032db]#7~#6 = 00b
    //reg_ext_data_en[15]
    _RVM1(0x328d, BIT7 , BIT7 ),   //reg[10328d]#7 = 1b
    //reg_gpo_sel[15]
    _RVM1(0x329b, BIT7 , BIT7 ),   //reg[10329b]#7 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD3_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD3_OEN (PAD_G_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_G_ODD3_OUT (PAD_G_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x32a0, PAD_G_ODD3_OUT, BIT0),
    _RVM1(0x32a4, PAD_G_ODD3_OEN, BIT0),
    //reg_output_conf[17:16]
    _RVM1(0x32dc, 0, BIT1|BIT0 ),   //reg[1032dc]#1~#0 = 00b
    //reg_ext_data_en[16]
    _RVM1(0x328e, BIT0 , BIT0 ),   //reg[10328e]#0 = 1b
    //reg_gpo_sel[16]
    _RVM1(0x329c, BIT0 , BIT0 ),   //reg[10329c]#0 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD2_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD2_OEN (PAD_G_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_G_ODD2_OUT (PAD_G_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x32a0, PAD_G_ODD2_OUT, BIT1),
    _RVM1(0x32a4, PAD_G_ODD2_OEN, BIT1),
    //reg_output_conf[17:16]
    _RVM1(0x32dc, 0, BIT1|BIT0 ),   //reg[1032dc]#1~#0 = 00b
    //reg_ext_data_en[17]
    _RVM1(0x328e, BIT1 , BIT1 ),   //reg[10328e]#1 = 1b
    //reg_gpo_sel[17]
    _RVM1(0x329c, BIT1 , BIT1 ),   //reg[10329c]#1 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD1_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD1_OEN (PAD_G_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_G_ODD1_OUT (PAD_G_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x32a0, PAD_G_ODD1_OUT, BIT2),
    _RVM1(0x32a4, PAD_G_ODD1_OEN, BIT2),
    //reg_output_conf[19:18]
    _RVM1(0x32dc, 0, BIT3|BIT2 ),   //reg[1032dc]#3~#2 = 00b
    //reg_ext_data_en[18]
    _RVM1(0x328e, BIT2 , BIT2 ),   //reg[10328e]#2 = 1b
    //reg_gpo_sel[18]
    _RVM1(0x329c, BIT2 , BIT2 ),   //reg[10329c]#2 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_G_ODD0_IS_GPIO != GPIO_NONE)
    #define PAD_G_ODD0_OEN (PAD_G_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_G_ODD0_OUT (PAD_G_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x32a0, PAD_G_ODD0_OUT, BIT3),
    _RVM1(0x32a4, PAD_G_ODD0_OEN, BIT3),
    //reg_output_conf[19:18]
    _RVM1(0x32dc, 0, BIT3|BIT2 ),   //reg[1032dc]#3~#2 = 00b
    //reg_ext_data_en[19]
    _RVM1(0x328e, BIT3 , BIT3 ),   //reg[10328e]#3 = 1b
    //reg_gpo_sel[19]
    _RVM1(0x329c, BIT3 , BIT3 ),   //reg[10329c]#3 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD7_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD7_OEN (PAD_B_ODD7_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_B_ODD7_OUT (PAD_B_ODD7_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x32a0, PAD_B_ODD7_OUT, BIT4),
    _RVM1(0x32a4, PAD_B_ODD7_OEN, BIT4),
    //reg_output_conf[21:20]
    _RVM1(0x32dc, 0, BIT5|BIT4 ),   //reg[1032dc]#5~#4 = 00b
    //reg_ext_data_en[20]
    _RVM1(0x328e, BIT4 , BIT4 ),   //reg[10328e]#4 = 1b
    //reg_gpo_sel[20]
    _RVM1(0x329c, BIT4 , BIT4 ),   //reg[10329c]#4 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD6_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD6_OEN (PAD_B_ODD6_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_B_ODD6_OUT (PAD_B_ODD6_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x32a0, PAD_B_ODD6_OUT, BIT5),
    _RVM1(0x32a4, PAD_B_ODD6_OEN, BIT5),
    //reg_output_conf[21:20]
    _RVM1(0x32dc, 0, BIT5|BIT4 ),   //reg[1032dc]#5~#4 = 00b
    //reg_ext_data_en[21]
    _RVM1(0x328e, BIT5 , BIT5 ),   //reg[10328e]#5 = 1b
    //reg_gpo_sel[21]
    _RVM1(0x329c, BIT5 , BIT5 ),   //reg[10329c]#5 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD5_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD5_OEN (PAD_B_ODD5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_B_ODD5_OUT (PAD_B_ODD5_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x32a0, PAD_B_ODD5_OUT, BIT6),
    _RVM1(0x32a4, PAD_B_ODD5_OEN, BIT6),
    //reg_output_conf[23:22]
    _RVM1(0x32dc, 0, BIT7|BIT6 ),   //reg[1032dc]#7~#6 = 00b
    //reg_ext_data_en[22]
    _RVM1(0x328e, BIT6 , BIT6 ),   //reg[10328e]#6 = 1b
    //reg_gpo_sel[22]
    _RVM1(0x329c, BIT6 , BIT6 ),   //reg[10329c]#6 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD4_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD4_OEN (PAD_B_ODD4_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_B_ODD4_OUT (PAD_B_ODD4_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x32a0, PAD_B_ODD4_OUT, BIT7),
    _RVM1(0x32a4, PAD_B_ODD4_OEN, BIT7),
    //reg_output_conf[23:22]
    _RVM1(0x32dc, 0, BIT7|BIT6 ),   //reg[1032dc]#7~#6 = 00b
    //reg_ext_data_en[23]
    _RVM1(0x328e, BIT7 , BIT7 ),   //reg[10328e]#7 = 1b
    //reg_gpo_sel[23]
    _RVM1(0x329c, BIT7 , BIT7 ),   //reg[10329c]#7 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD3_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD3_OEN (PAD_B_ODD3_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_B_ODD3_OUT (PAD_B_ODD3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x32a1, PAD_B_ODD3_OUT, BIT0),
    _RVM1(0x32a5, PAD_B_ODD3_OEN, BIT0),
    //reg_output_conf[25:24]
    _RVM1(0x32dd, 0, BIT1|BIT0 ),   //reg[1032dd]#1~#0 = 00b
    //reg_ext_data_en[24]
    _RVM1(0x328f, BIT0 , BIT0 ),   //reg[10328f]#0 = 1b
    //reg_gpo_sel[24]
    _RVM1(0x329d, BIT0 , BIT0 ),   //reg[10329d]#0 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD2_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD2_OEN (PAD_B_ODD2_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_B_ODD2_OUT (PAD_B_ODD2_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x32a1, PAD_B_ODD2_OUT, BIT1),
    _RVM1(0x32a5, PAD_B_ODD2_OEN, BIT1),
    //reg_output_conf[25:24]
    _RVM1(0x32dd, 0, BIT1|BIT0 ),   //reg[1032dd]#1~#0 = 00b
    //reg_ext_data_en[25]
    _RVM1(0x328f, BIT1 , BIT1 ),   //reg[10328f]#1 = 1b
    //reg_gpo_sel[25]
    _RVM1(0x329d, BIT1 , BIT1 ),   //reg[10329d]#1 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD1_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD1_OEN (PAD_B_ODD1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_B_ODD1_OUT (PAD_B_ODD1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x32a1, PAD_B_ODD1_OUT, BIT2),
    _RVM1(0x32a5, PAD_B_ODD1_OEN, BIT2),
    //reg_output_conf[27:26]
    _RVM1(0x32dd, 0, BIT3|BIT2 ),   //reg[1032dd]#3~#2 = 00b
    //reg_ext_data_en[26]
    _RVM1(0x328f, BIT2 , BIT2 ),   //reg[10328f]#2 = 1b
    //reg_gpo_sel[26]
    _RVM1(0x329d, BIT2 , BIT2 ),   //reg[10329d]#2 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_B_ODD0_IS_GPIO != GPIO_NONE)
    #define PAD_B_ODD0_OEN (PAD_B_ODD0_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_B_ODD0_OUT (PAD_B_ODD0_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x32a1, PAD_B_ODD0_OUT, BIT3),
    _RVM1(0x32a5, PAD_B_ODD0_OEN, BIT3),
    //reg_output_conf[27:26]
    _RVM1(0x32dd, 0, BIT3|BIT2 ),   //reg[1032dd]#3~#2 = 00b
    //reg_ext_data_en[27]
    _RVM1(0x328f, BIT3 , BIT3 ),   //reg[10328f]#3 = 1b
    //reg_gpo_sel[27]
    _RVM1(0x329d, BIT3 , BIT3 ),   //reg[10329d]#3 = 1b
    _RVM1(0x1e02, BIT0 , BIT0 ),   //reg[101e02]#0 = 1b
    #endif

    #if(PAD_GPIO0_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO0_OEN (PAD_GPIO0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO0_OUT (PAD_GPIO0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7a, PAD_GPIO0_OUT, BIT0),
    _RVM1(0x1e7e, PAD_GPIO0_OEN, BIT0),
    //reg_seconduartmode = 00b
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1~#0 = 00b
    //reg_3d_lr_config[2:0] = 000b
    _RVM1(0x1e10, 0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    //reg_6bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT0 ),   //reg[101ef8]#0 = 0b
    //reg_usbdrvvbusconfig_eq_1 = 0b
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1~#0 = 00b
    //reg_mhl_vbus_config[2:0] = 000b
    _RVM1(0x1ef9, 0, BIT7|BIT6|BIT5 ),   //reg[101ef9]#7~#5 = 000b
    //reg_mhl_debug_en = 0b
    _RVM1(0x1ef9, 0, BIT4 ),   //reg[101ef9]#4 = 0b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO1_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO1_OEN (PAD_GPIO1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO1_OUT (PAD_GPIO1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e7a, PAD_GPIO1_OUT, BIT1),
    _RVM1(0x1e7e, PAD_GPIO1_OEN, BIT1),
    //reg_seconduartmode = 00b
    _RVM1(0x1e05, 0, BIT1|BIT0 ),   //reg[101e05]#1~#0 = 00b
    //reg_6bit_ttl = 0b
    _RVM1(0x1ef8, 0, BIT0 ),   //reg[101ef8]#0 = 0b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_led_mode[3:2] = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    //reg_usbdrvvbusconfig_eq_1 = 0b
    _RVM1(0x1e04, 0, BIT1|BIT0 ),   //reg[101e04]#1~#0 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO2_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO2_OEN (PAD_GPIO2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO2_OUT (PAD_GPIO2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e7a, PAD_GPIO2_OUT, BIT2),
    _RVM1(0x1e7e, PAD_GPIO2_OEN, BIT2),
    //reg_mhl_vbus_config[2:0] = 000b
    _RVM1(0x1ef9, 0, BIT7|BIT6|BIT5 ),   //reg[101ef9]#7~#5 = 000b
    //reg_chiptop_dummy_3[10] = 0b
    _RVM1(0x1e3f, 0, BIT2 ),   //reg[101e3f]#2 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_i2sinconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT4|BIT3 ),   //reg[101eae]#4 ~#3 = 00b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_led_mode[3:2] = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO3_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO3_OEN (PAD_GPIO3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO3_OUT (PAD_GPIO3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e7a, PAD_GPIO3_OUT, BIT3),
    _RVM1(0x1e7e, PAD_GPIO3_OEN, BIT3),
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~#2 = 00b
    //reg_chiptop_dummy_3[10] = 0b
    _RVM1(0x1e3f, 0, BIT2 ),   //reg[101e3f]#2 = 0b
    //reg_chiptop_dummy_3[11] = 0b
    _RVM1(0x1e3f, 0, BIT3 ),   //reg[101e3f]#3 = 0b
    //reg_chiptop_dummy_3[12] = 0b
    _RVM1(0x1e3f, 0, BIT4 ),   //reg[101e3f]#4 = 0b
    //reg_i2sinconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT4|BIT3 ),   //reg[101eae]#4 ~#3 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    #endif

    #if(PAD_GPIO4_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO4_OEN (PAD_GPIO4_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO4_OUT (PAD_GPIO4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e7a, PAD_GPIO4_OUT, BIT4),
    _RVM1(0x1e7e, PAD_GPIO4_OEN, BIT4),
    //reg_chiptop_dummy_3[10] = 0b
    _RVM1(0x1e3f, 0, BIT2 ),   //reg[101e3f]#2 = 0b
    //reg_chiptop_dummy_3[11] = 0b
    _RVM1(0x1e3f, 0, BIT3 ),   //reg[101e3f]#3 = 0b
    //reg_chiptop_dummy_3[12] = 0b
    _RVM1(0x1e3f, 0, BIT4 ),   //reg[101e3f]#4 = 0b
    //reg_chiptop_dummy_3[15] = 0b
    _RVM1(0x1e3f, 0, BIT7 ),   //reg[101e3f]#7 = 0b
    //reg_thirduartmode[1:0] = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3 ~#2 = 00b
    //reg_i2sinconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT4|BIT3 ),   //reg[101eae]#4 ~#3 = 00b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    #endif

    #if(PAD_GPIO5_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO5_OEN (PAD_GPIO5_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO5_OUT (PAD_GPIO5_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e7a, PAD_GPIO5_OUT, BIT5),
    _RVM1(0x1e7e, PAD_GPIO5_OEN, BIT5),
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_fourthuartmode[1:0] = 00b
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    //reg_spdifoutconfig = 0b
    _RVM1(0x1eaf, 0, BIT1 ),   //reg[101eaf]#1 = 0b
    #endif

    #if(PAD_GPIO6_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO6_OEN (PAD_GPIO6_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO6_OUT (PAD_GPIO6_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e7a, PAD_GPIO6_OUT, BIT6),
    _RVM1(0x1e7e, PAD_GPIO6_OEN, BIT6),
    //reg_chiptop_dummy_3[10] = 0b
    _RVM1(0x1e3f, 0, BIT2 ),   //reg[101e3f]#2 = 0b
    //reg_chiptop_dummy_3[11] = 0b
    _RVM1(0x1e3f, 0, BIT3 ),   //reg[101e3f]#3 = 0b
    //reg_chiptop_dummy_3[12] = 0b
    _RVM1(0x1e3f, 0, BIT4 ),   //reg[101e3f]#4 = 0b
    //reg_i2sinconfig = 00b
    _RVM1(0x1eae, 0, BIT4|BIT3 ),   //reg[101eae]#4~#3 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_PWM5Config = 00b
    _RVM1(0x1e41, 0, BIT3|BIT2 ),   //reg[101e41]#3~#2 = 0b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO7_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO7_OEN (PAD_GPIO7_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO7_OUT (PAD_GPIO7_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e7a, PAD_GPIO7_OUT, BIT7),
    _RVM1(0x1e7e, PAD_GPIO7_OEN, BIT7),
    //reg_chiptop_dummy_3[10] = 0b
    _RVM1(0x1e3f, 0, BIT2 ),   //reg[101e3f]#2 = 0b
    //reg_chiptop_dummy_3[12] = 0b
    _RVM1(0x1e3f, 0, BIT4 ),   //reg[101e3f]#4 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_spdifinconfig = 0b
    _RVM1(0x1eae, 0, BIT7 ),   //reg[101eae]#7 = 0b
    //reg_PWM4Config = 00b
    _RVM1(0x1e41, 0, BIT1|BIT0 ),   //reg[101e41]#1~#0 = 00b
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO8_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO8_OEN (PAD_GPIO8_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO8_OUT (PAD_GPIO8_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e7b, PAD_GPIO8_OUT, BIT0),
    _RVM1(0x1e7f, PAD_GPIO8_OEN, BIT0),
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_thirduartmode = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_i2sinconfig = 00b
    _RVM1(0x1eae, 0, BIT4|BIT3 ),   //reg[101eae]#4~#3 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    #endif

    #if(PAD_GPIO9_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO9_OEN (PAD_GPIO9_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO9_OUT (PAD_GPIO9_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e7b, PAD_GPIO9_OUT, BIT1),
    _RVM1(0x1e7f, PAD_GPIO9_OEN, BIT1),
    //reg_thirduartmode = 00b
    _RVM1(0x1e05, 0, BIT3|BIT2 ),   //reg[101e05]#3~#2 = 00b
    //reg_i2sinconfig = 00b
    _RVM1(0x1eae, 0, BIT4|BIT3 ),   //reg[101eae]#4~#3 = 0b
    //reg_i2soutconfig[1:0] = 00b
    _RVM1(0x1eae, 0, BIT6|BIT5 ),   //reg[101eae]#6 ~#5 = 00b
    //reg_et_mode = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    //reg_parallel_TS_in_Config = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_parallel_ts_out_config = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2 ~#0 = 000b
    #endif

    #if(PAD_GPIO10_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO10_OEN (PAD_GPIO10_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO10_OUT (PAD_GPIO10_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e7b, PAD_GPIO10_OUT, BIT2),
    _RVM1(0x1e7f, PAD_GPIO10_OEN, BIT2),
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_parallel_ts_out_config = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2 ~#0 = 000b
    #endif

    #if(PAD_GPIO11_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO11_OEN (PAD_GPIO11_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO11_OUT (PAD_GPIO11_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e7b, PAD_GPIO11_OUT, BIT3),
    _RVM1(0x1e7f, PAD_GPIO11_OEN, BIT3),
    //reg_ddcrmode[3:0] = 0000b
    _RVM1(0x1ef6, 0, BIT3|BIT2|BIT1|BIT0 ),   //reg[101ef6]#3 ~#0 = 0000b
    //reg_parallel_TS_in_Config = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_parallel_ts_out_config = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2 ~#0 = 000b
    #endif

    #if(PAD_GPIO17_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO17_OEN (PAD_GPIO17_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO17_OUT (PAD_GPIO17_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e7c, PAD_GPIO17_OUT, BIT1),
    _RVM1(0x1e80, PAD_GPIO17_OEN, BIT1),
    //reg_parallel_TS_in_Config = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5 ~#4 = 00b
    //reg_chiptop_dummy_3[11] = 0b
    _RVM1(0x1e3f, 0, BIT3 ),   //reg[101e3f]#3 = 0b
    //reg_parallel_ts_out_config = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2 ~#0 = 000b
    #endif

    #if(PAD_INT_IS_GPIO != GPIO_NONE)
    #define PAD_INT_OEN (PAD_INT_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_INT_OUT (PAD_INT_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e45, PAD_INT_OUT, BIT2),
    _RVM1(0x1e49, PAD_INT_OEN, BIT2),
    //reg_int_gpio = 1b
    _RVM1(0x1e4f, BIT2 , BIT2 ),   //reg[101e4f]#2 = 1b
    #endif

    #if(PAD_CEC_IS_GPIO != GPIO_NONE)
    #define PAD_CEC_OEN (PAD_CEC_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_CEC_OUT (PAD_CEC_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e08, PAD_CEC_OUT, BIT0),
    _RVM1(0x1e08, PAD_CEC_OEN, BIT1),
    //reg_pmcec_en = 0
    _RVM1(0x3401, 0, BIT6 ),   //reg[003401]#6 = 0b
    //reg_parallel_ts_out_config = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2 ~#0 = 000b
    #endif

    _MEMMAP_PM_,

    #if(PAD_SAR3_IS_GPIO != GPIO_NONE)
    #define PAD_SAR3_OEN (PAD_SAR3_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_SAR3_OUT (PAD_SAR3_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1424, PAD_SAR3_OUT, BIT3),
    _RVM1(0x1423, PAD_SAR3_OEN, BIT3),
    _RVM1(0x1422, 0, BIT3 ),   //reg[1422] #3 = 0b
    #else
    _RVM1(0x1423, BIT3, BIT3),
    _RVM1(0x1422, BIT3, BIT3),   //reg[1422] #3 = 1b
    #endif

    #if(PAD_SAR2_IS_GPIO != GPIO_NONE)
    #define PAD_SAR2_OEN (PAD_SAR2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_SAR2_OUT (PAD_SAR2_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1424, PAD_SAR2_OUT, BIT2),
    _RVM1(0x1423, PAD_SAR2_OEN, BIT2),
    _RVM1(0x1422, 0, BIT2),   //reg[1422] #2 = 0b
    #else
    _RVM1(0x1423, BIT2, BIT2),
    _RVM1(0x1422, BIT2, BIT2),   //reg[1422] #2 = 1b
    #endif

    #if(PAD_SAR1_IS_GPIO != GPIO_NONE)
    #define PAD_SAR1_OEN (PAD_SAR1_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_SAR1_OUT (PAD_SAR1_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1424, PAD_SAR1_OUT, BIT1),
    _RVM1(0x1423, PAD_SAR1_OEN, BIT1),
    _RVM1(0x1422, 0, BIT1),   //reg[1422] #1 = 0b
    #else
    _RVM1(0x1423, BIT1, BIT1),
    _RVM1(0x1422, BIT1, BIT1),   //reg[1422] #1 = 1b
    #endif

    #if(PAD_SAR0_IS_GPIO != GPIO_NONE)
    #define PAD_SAR0_OEN (PAD_SAR0_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_SAR0_OUT (PAD_SAR0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1424, PAD_SAR0_OUT, BIT0),
    _RVM1(0x1423, PAD_SAR0_OEN, BIT0),
    _RVM1(0x1422, 0, BIT0),   //reg[1422] #0 = 0b
    #else
    _RVM1(0x1423, BIT0, BIT0),
    _RVM1(0x1422, BIT0,  BIT0),   //reg[1422] #0 = 1b
    #endif

    _MEMMAP_nonPM_,

    #if(PAD_DDCDA_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDA_CLK_OEN (PAD_DDCDA_CLK_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_DDCDA_CLK_OUT (PAD_DDCDA_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e16, PAD_DDCDA_CLK_OUT, BIT0),
    _RVM1(0x1e18, PAD_DDCDA_CLK_OEN, BIT0),
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_ddcda_en = 0b
    _RVM1(0x1ef9, 0, BIT1 ),   //reg[101ef9]#1 = 0b
    #endif

    #if(PAD_DDCDA_DAT_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDA_DAT_OEN (PAD_DDCDA_DAT_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_DDCDA_DAT_OUT (PAD_DDCDA_DAT_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e16, PAD_DDCDA_DAT_OUT, BIT1),
    _RVM1(0x1e18, PAD_DDCDA_DAT_OEN, BIT1),
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_ddcda_en = 0b
    _RVM1(0x1ef9, 0, BIT1 ),   //reg[101ef9]#1 = 0b
    #endif

    #if(PAD_HOTPLUG_A_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUG_A_OEN (PAD_HOTPLUG_A_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_HOTPLUG_A_OUT (PAD_HOTPLUG_A_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e17, PAD_HOTPLUG_A_OUT, BIT0),
    _RVM1(0x1e19, PAD_HOTPLUG_A_OEN, BIT0),
    //reg_hotpluga_gpio_en = 1b
    _RVM1(0x1e17, BIT5 , BIT5 ),   //reg[101e17]#5 = 1b
    //reg_mhl_cbus_config[1:0] = 00b
    _RVM1(0x1efa, 0, BIT1|BIT0 ),   //reg[101efa]#1~#0 = 00b
    #endif

    #if(PAD_DDCDB_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDB_CLK_OEN (PAD_DDCDB_CLK_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_DDCDB_CLK_OUT (PAD_DDCDB_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e16, PAD_DDCDB_CLK_OUT, BIT2),
    _RVM1(0x1e18, PAD_DDCDB_CLK_OEN, BIT2),
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_ddcdb_en = 0b
    _RVM1(0x1ef9, 0, BIT2 ),   //reg[101ef9]#2 = 0b
    #endif

    #if(PAD_DDCDB_DAT_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDB_DAT_OEN (PAD_DDCDB_DAT_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_DDCDB_DAT_OUT (PAD_DDCDB_DAT_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e16, PAD_DDCDB_DAT_OUT, BIT3),
    _RVM1(0x1e18, PAD_DDCDB_DAT_OEN, BIT3),
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    //reg_ddcdb_en = 0b
    _RVM1(0x1ef9, 0, BIT2 ),   //reg[101ef9]#2 = 0b
    #endif

    #if(PAD_HOTPLUG_B_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUG_B_OEN (PAD_HOTPLUG_B_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_HOTPLUG_B_OUT (PAD_HOTPLUG_B_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e17, PAD_HOTPLUG_B_OUT, BIT1),
    _RVM1(0x1e19, PAD_HOTPLUG_B_OEN, BIT1),
    //reg_mhl_cbus_config[1:0] = 00b
    _RVM1(0x1efa, 0, BIT1|BIT0 ),   //reg[101efa]#1~#0 = 00b
    #endif

    #if(PAD_DDCDC_CLK_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDC_CLK_OEN (PAD_DDCDC_CLK_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_DDCDC_CLK_OUT (PAD_DDCDC_CLK_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e16, PAD_DDCDC_CLK_OUT, BIT4),
    _RVM1(0x1e18, PAD_DDCDC_CLK_OEN, BIT4),
    //reg_ddcdc_en = 0b
    _RVM1(0x1ef9, 0, BIT3 ),   //reg[101ef9]#3 = 0b
    #endif

    #if(PAD_DDCDC_DAT_IS_GPIO != GPIO_NONE)
    #define PAD_DDCDC_DAT_OEN (PAD_DDCDC_DAT_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_DDCDC_DAT_OUT (PAD_DDCDC_DAT_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e16, PAD_DDCDC_DAT_OUT, BIT5),
    _RVM1(0x1e18, PAD_DDCDC_DAT_OEN, BIT5),
    //reg_ddcdc_en = 0b
    _RVM1(0x1ef9, 0, BIT3 ),   //reg[101ef9]#3 = 0b
    #endif

    #if(PAD_HOTPLUG_C_IS_GPIO != GPIO_NONE)
    #define PAD_HOTPLUG_C_OEN (PAD_HOTPLUG_C_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_HOTPLUG_C_OUT (PAD_HOTPLUG_C_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e17, PAD_HOTPLUG_C_OUT, BIT2),
    _RVM1(0x1e19, PAD_HOTPLUG_C_OEN, BIT2),
    //reg_mhl_cbus_config[1:0] = 00b
    _RVM1(0x1efa, 0, BIT1|BIT0 ),   //reg[101efa]#1~#0 = 00b
    #endif

    #if(PAD_MHL_DET_IS_GPIO != GPIO_NONE)
    #define PAD_MHL_DET_OEN (PAD_MHL_DET_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_MHL_DET_OUT (PAD_MHL_DET_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e17, PAD_MHL_DET_OUT, BIT3),
    _RVM1(0x1e19, PAD_MHL_DET_OEN, BIT3),
    //reg_mhl_det_en = 0b
    _RVM1(0x1ef9, 0, BIT0 ),   //reg[101ef9]#0 = 0b
    #endif

    #if(PAD_GPIO20_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO20_OEN (PAD_GPIO20_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO20_OUT (PAD_GPIO20_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e42, PAD_GPIO20_OUT, BIT0),
    _RVM1(0x1e46, PAD_GPIO20_OEN, BIT0),
    #endif

    #if(PAD_GPIO21_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO21_OEN (PAD_GPIO21_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO21_OUT (PAD_GPIO21_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e42, PAD_GPIO21_OUT, BIT1),
    _RVM1(0x1e46, PAD_GPIO21_OEN, BIT1),
    #endif

    #if(PAD_GPIO22_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO22_OEN (PAD_GPIO22_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO22_OUT (PAD_GPIO22_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e42, PAD_GPIO22_OUT, BIT2),
    _RVM1(0x1e46, PAD_GPIO22_OEN, BIT2),
    #endif

    #if(PAD_GPIO23_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO23_OEN (PAD_GPIO23_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO23_OUT (PAD_GPIO23_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e42, PAD_GPIO23_OUT, BIT3),
    _RVM1(0x1e46, PAD_GPIO23_OEN, BIT3),
    #endif

    #if(PAD_GPIO24_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO24_OEN (PAD_GPIO24_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO24_OUT (PAD_GPIO24_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e42, PAD_GPIO24_OUT, BIT4),
    _RVM1(0x1e46, PAD_GPIO24_OEN, BIT4),
    #endif

    #if(PAD_GPIO25_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO25_OEN (PAD_GPIO25_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO25_OUT (PAD_GPIO25_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e42, PAD_GPIO25_OUT, BIT5),
    _RVM1(0x1e46, PAD_GPIO25_OEN, BIT5),
    #endif

    #if(PAD_GPIO26_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO26_OEN (PAD_GPIO26_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO26_OUT (PAD_GPIO26_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e42, PAD_GPIO26_OUT, BIT6),
    _RVM1(0x1e46, PAD_GPIO26_OEN, BIT6),
    #endif

    #if(PAD_GPIO27_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO27_OEN (PAD_GPIO27_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO27_OUT (PAD_GPIO27_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e42, PAD_GPIO27_OUT, BIT7),
    _RVM1(0x1e46, PAD_GPIO27_OEN, BIT7),
    #endif

    #if(PAD_GPIO28_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO28_OEN (PAD_GPIO28_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO28_OUT (PAD_GPIO28_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e43, PAD_GPIO28_OUT, BIT0),
    _RVM1(0x1e47, PAD_GPIO28_OEN, BIT0),
    #endif

    #if(PAD_GPIO29_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO29_OEN (PAD_GPIO29_IS_GPIO == GPIO_IN ? BIT1: 0)
    #define PAD_GPIO29_OUT (PAD_GPIO29_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x1e43, PAD_GPIO29_OUT, BIT1),
    _RVM1(0x1e47, PAD_GPIO29_OEN, BIT1),
    #endif

    #if(PAD_GPIO30_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO30_OEN (PAD_GPIO30_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_GPIO30_OUT (PAD_GPIO30_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x1e43, PAD_GPIO30_OUT, BIT2),
    _RVM1(0x1e47, PAD_GPIO30_OEN, BIT2),
    #endif

    #if(PAD_GPIO31_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO31_OEN (PAD_GPIO31_IS_GPIO == GPIO_IN ? BIT3: 0)
    #define PAD_GPIO31_OUT (PAD_GPIO31_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x1e43, PAD_GPIO31_OUT, BIT3),
    _RVM1(0x1e47, PAD_GPIO31_OEN, BIT3),
    #endif

    #if(PAD_GPIO32_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO32_OEN (PAD_GPIO32_IS_GPIO == GPIO_IN ? BIT4: 0)
    #define PAD_GPIO32_OUT (PAD_GPIO32_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x1e43, PAD_GPIO32_OUT, BIT4),
    _RVM1(0x1e47, PAD_GPIO32_OEN, BIT4),
    #endif

    #if(PAD_GPIO33_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO33_OEN (PAD_GPIO33_IS_GPIO == GPIO_IN ? BIT5: 0)
    #define PAD_GPIO33_OUT (PAD_GPIO33_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x1e43, PAD_GPIO33_OUT, BIT5),
    _RVM1(0x1e47, PAD_GPIO33_OEN, BIT5),
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef6, 0, BIT5|BIT4 ),   //reg[101ef6]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO34_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO34_OEN (PAD_GPIO34_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_GPIO34_OUT (PAD_GPIO34_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x1e43, PAD_GPIO34_OUT, BIT6),
    _RVM1(0x1e47, PAD_GPIO34_OEN, BIT6),
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO35_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO35_OEN (PAD_GPIO35_IS_GPIO == GPIO_IN ? BIT7: 0)
    #define PAD_GPIO35_OUT (PAD_GPIO35_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x1e43, PAD_GPIO35_OUT, BIT7),
    _RVM1(0x1e47, PAD_GPIO35_OEN, BIT7),
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PAD_GPIO36_IS_GPIO != GPIO_NONE)
    #define PAD_GPIO36_OEN (PAD_GPIO36_IS_GPIO == GPIO_IN ? BIT0: 0)
    #define PAD_GPIO36_OUT (PAD_GPIO36_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x1e44, PAD_GPIO36_OUT, BIT0),
    _RVM1(0x1e48, PAD_GPIO36_OEN, BIT0),
    //reg_parallel_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 00b
    //reg_serial_TS_in_Config[1:0] = 00b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    //reg_parallel_ts_out_config[2:0] = 000b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    #endif

    #if(PADA_HSYNC0_IS_GPIO != GPIO_NONE)
    #define PADA_HSYNC0_OEN (PADA_HSYNC0_IS_GPIO == GPIO_IN ? 0: BIT0)
    #define PADA_HSYNC0_OUT (PADA_HSYNC0_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x255a, PADA_HSYNC0_OUT, BIT6),
    _RVM1(0x255a, PADA_HSYNC0_OEN, BIT0),
    //reg_test_hsync[3] = 0b
    _RVM1(0x2560, 0, BIT3 ),   //reg[102560]#3 = 0b
    //reg_gpio_hsync_en[0] = 1b
    _RVM1(0x2558, BIT0 , BIT0 ),   //reg[102558]#0 = 1b
    #endif

    #if(PADA_HSYNC1_IS_GPIO != GPIO_NONE)
    #define PADA_HSYNC1_OEN (PADA_HSYNC1_IS_GPIO == GPIO_IN ? 0: BIT1)
    #define PADA_HSYNC1_OUT (PADA_HSYNC1_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x255a, PADA_HSYNC1_OUT, BIT7),
    _RVM1(0x255a, PADA_HSYNC1_OEN, BIT1),
    //reg_test_hsync[4] = 0b
    _RVM1(0x2560, 0, BIT4 ),   //reg[102560]#4 = 0b
    //reg_gpio_hsync_en[1] = 1b
    _RVM1(0x2558, BIT1 , BIT1 ),   //reg[102558]#1 = 1b
    #endif

    #if(PADA_VSYNC0_IS_GPIO != GPIO_NONE)
    #define PADA_VSYNC0_OEN (PADA_VSYNC0_IS_GPIO == GPIO_IN ? 0: BIT3)
    #define PADA_VSYNC0_OUT (PADA_VSYNC0_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x255b, PADA_VSYNC0_OUT, BIT1),
    _RVM1(0x255a, PADA_VSYNC0_OEN, BIT3),
    //reg_test_vsync[0] = 0b
    _RVM1(0x2561, 0, BIT0 ),   //reg[102561]#0 = 0b
    //reg_gpio_vsync_en[3] = 1b
    _RVM1(0x2558, BIT3 , BIT3 ),   //reg[102558]#3 = 1b
    #endif

    #if(PADA_VSYNC1_IS_GPIO != GPIO_NONE)
    #define PADA_VSYNC1_OEN (PADA_VSYNC1_IS_GPIO == GPIO_IN ? 0: BIT4)
    #define PADA_VSYNC1_OUT (PADA_VSYNC1_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x255b, PADA_VSYNC1_OUT, BIT2),
    _RVM1(0x255a, PADA_VSYNC1_OEN, BIT4),
    //reg_test_vsync[1] = 0b
    _RVM1(0x2561, 0, BIT1 ),   //reg[102561]#1 = 0b
    //reg_gpio_vsync_en[4] = 1b
    _RVM1(0x2558, BIT4 , BIT4 ),   //reg[102558]#4 = 1b
    #endif

    #if(PADA_RIN0P_IS_GPIO != GPIO_NONE)
    #define PADA_RIN0P_OEN (PADA_RIN0P_IS_GPIO == GPIO_IN ? 0: BIT0)
    #define PADA_RIN0P_OUT (PADA_RIN0P_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2537, PADA_RIN0P_OUT, BIT0),
    _RVM1(0x2536, PADA_RIN0P_OEN, BIT0,
    //reg_gpio_rgb_en[0] = 1b
    _RVM1(0x2534, BIT0 , BIT0 ),   //reg[102534]#0 = 1b
    #endif

    #if(PADA_RIN1P_IS_GPIO != GPIO_NONE)
    #define PADA_RIN1P_OEN (PADA_RIN1P_IS_GPIO == GPIO_IN ? 0: BIT1)
    #define PADA_RIN1P_OUT (PADA_RIN1P_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2537, PADA_RIN1P_OUT, BIT1),
    _RVM1(0x2536, PADA_RIN1P_OEN, BIT1),
    //reg_gpio_rgb_en[1] = 1b
    _RVM1(0x2534, BIT1 , BIT1 ),   //reg[102534]#1 = 1b
    #endif

    #if(PADA_RIN0M_IS_GPIO != GPIO_NONE)
    #define PADA_RIN0M_OEN (PADA_RIN0M_IS_GPIO == GPIO_IN ? 0: BIT4)
    #define PADA_RIN0M_OUT (PADA_RIN0M_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2537, PADA_RIN0M_OUT, BIT4),
    _RVM1(0x2536, PADA_RIN0M_OEN, BIT4),
    //reg_gpio_rgb_en[0] = 1b
    _RVM1(0x2534, BIT0 , BIT0 ),   //reg[102534]#0 = 1b
    #endif

    #if(PADA_RIN1M_IS_GPIO != GPIO_NONE)
    #define PADA_RIN1M_OEN (PADA_RIN1M_IS_GPIO == GPIO_IN ? 0: BIT5)
    #define PADA_RIN1M_OUT (PADA_RIN1M_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2537, PADA_RIN1M_OUT, BIT5),
    _RVM1(0x2536, PADA_RIN1M_OEN, BIT5),
    //reg_gpio_rgb_en[1] = 1b
    _RVM1(0x2534, BIT1 , BIT1 ),   //reg[102534]#1 = 1b
    #endif

    #if(PADA_GIN0P_IS_GPIO != GPIO_NONE)
    #define PADA_GIN0P_OEN (PADA_GIN0P_IS_GPIO == GPIO_IN ? 0: BIT0)
    #define PADA_GIN0P_OUT (PADA_GIN0P_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2539, PADA_GIN0P_OUT, BIT0),
    _RVM1(0x2538, PADA_GIN0P_OEN, BIT0),
    //reg_gpio_rgb_en[0] = 1b
    _RVM1(0x2534, BIT0 , BIT0 ),   //reg[102534]#0 = 1b
    #endif

    #if(PADA_GIN1P_IS_GPIO != GPIO_NONE)
    #define PADA_GIN1P_OEN (PADA_GIN1P_IS_GPIO == GPIO_IN ? 0: BIT1)
    #define PADA_GIN1P_OUT (PADA_GIN1P_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x2539, PADA_GIN1P_OUT, BIT1),
    _RVM1(0x2538, PADA_GIN1P_OEN, BIT1),
    //reg_gpio_rgb_en[1] = 1b
    _RVM1(0x2534, BIT1 , BIT1 ),   //reg[102534]#1 = 1b
    #endif

    #if(PADA_GIN0M_IS_GPIO != GPIO_NONE)
    #define PADA_GIN0M_OEN (PADA_GIN0M_IS_GPIO == GPIO_IN ? 0: BIT4)
    #define PADA_GIN0M_OUT (PADA_GIN0M_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2539, PADA_GIN0M_OUT, BIT4),
    _RVM1(0x2538, PADA_GIN0M_OEN, BIT4),
    //reg_gpio_rgb_en[0] = 1b
    _RVM1(0x2534, BIT0 , BIT0 ),   //reg[102534]#0 = 1b
    #endif

    #if(PADA_GIN1M_IS_GPIO != GPIO_NONE)
    #define PADA_GIN1M_OEN (PADA_GIN1M_IS_GPIO == GPIO_IN ? 0: BIT5)
    #define PADA_GIN1M_OUT (PADA_GIN1M_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x2539, PADA_GIN1M_OUT, BIT5),
    _RVM1(0x2538, PADA_GIN1M_OEN, BIT5),
    //reg_gpio_rgb_en[1] = 1b
    _RVM1(0x2534, BIT1 , BIT1 ),   //reg[102534]#1 = 1b
    #endif

    #if(PADA_BIN0P_IS_GPIO != GPIO_NONE)
    #define PADA_BIN0P_OEN (PADA_BIN0P_IS_GPIO == GPIO_IN ? 0: BIT0)
    #define PADA_BIN0P_OUT (PADA_BIN0P_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x253b, PADA_BIN0P_OUT, BIT0),
    _RVM1(0x253a, PADA_BIN0P_OEN, BIT0),
    //reg_gpio_rgb_en[0] = 1b
    _RVM1(0x2534, BIT0 , BIT0 ),   //reg[102534]#0 = 1b
    #endif

    #if(PADA_BIN1P_IS_GPIO != GPIO_NONE)
    #define PADA_BIN1P_OEN (PADA_BIN1P_IS_GPIO == GPIO_IN ? 0: BIT1)
    #define PADA_BIN1P_OUT (PADA_BIN1P_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x253b, PADA_BIN1P_OUT, BIT1),
    _RVM1(0x253a, PADA_BIN1P_OEN, BIT1),
    //reg_gpio_rgb_en[1] = 1b
    _RVM1(0x2534, BIT1 , BIT1 ),   //reg[102534]#1 = 1b
    #endif

    #if(PADA_BIN0M_IS_GPIO != GPIO_NONE)
    #define PADA_BIN0M_OEN (PADA_BIN0M_IS_GPIO == GPIO_IN ? 0: BIT4)
    #define PADA_BIN0M_OUT (PADA_BIN0M_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x253b, PADA_BIN0M_OUT, BIT4),
    _RVM1(0x253a, PADA_BIN0M_OEN, BIT4),
    //reg_gpio_rgb_en[0] = 1b
    _RVM1(0x2534, BIT0 , BIT0 ),   //reg[102534]#0 = 1b
    #endif

    #if(PADA_BIN1M_IS_GPIO != GPIO_NONE)
    #define PADA_BIN1M_OEN (PADA_BIN1M_IS_GPIO == GPIO_IN ? 0: BIT5)
    #define PADA_BIN1M_OUT (PADA_BIN1M_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x253b, PADA_BIN1M_OUT, BIT5),
    _RVM1(0x253a, PADA_BIN1M_OEN, BIT5),
    //reg_gpio_rgb_en[1] = 1b
    _RVM1(0x2534, BIT1 , BIT1 ),   //reg[102534]#1 = 1b
    #endif

    _MEMMAP_nonPM_11_,

    #if(PAD_LINEIN_L0_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_L0_OEN (PAD_LINEIN_L0_IS_GPIO == GPIO_IN ? BIT2 : 0)
    #define PAD_LINEIN_L0_OUT (PAD_LINEIN_L0_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bf6, PAD_LINEIN_L0_OUT, BIT0),
    _RVM1(0x2bf6, PAD_LINEIN_L0_OEN, BIT2),
    _RVM1(0x2bf6, BIT1 , BIT1 ),   //reg[112bf6]#1 = 1b
    #endif

    #if(PAD_LINEIN_R0_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_R0_OEN (PAD_LINEIN_R0_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_LINEIN_R0_OUT (PAD_LINEIN_R0_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2bf6, PAD_LINEIN_R0_OUT, BIT4),
    _RVM1(0x2bf6, PAD_LINEIN_R0_OEN, BIT6),
    _RVM1(0x2bf6, BIT5 , BIT5 ),   //reg[112bf6]#5 = 1b
    #endif

    #if(PAD_LINEIN_L1_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_L1_OEN (PAD_LINEIN_L1_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LINEIN_L1_OUT (PAD_LINEIN_L1_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bf7, PAD_LINEIN_L1_OUT, BIT0),
    _RVM1(0x2bf7, PAD_LINEIN_L1_OEN, BIT2),
    _RVM1(0x2bf7, BIT1 , BIT1 ),   //reg[112bf7]#1 = 1b
    #endif

    #if(PAD_LINEIN_R1_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_R1_OEN (PAD_LINEIN_R1_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_LINEIN_R1_OUT (PAD_LINEIN_R1_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2bf7, PAD_LINEIN_R1_OUT, BIT4),
    _RVM1(0x2bf7, PAD_LINEIN_R1_OEN, BIT6),
    _RVM1(0x2bf7, BIT5 , BIT5 ),   //reg[112bf7]#5 = 1b
    #endif

    #if(PAD_LINEIN_L2_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_L2_OEN (PAD_LINEIN_L2_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LINEIN_L2_OUT (PAD_LINEIN_L2_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bf8, PAD_LINEIN_L2_OUT, BIT0),
    _RVM1(0x2bf8, PAD_LINEIN_L2_OEN, BIT2),
    _RVM1(0x2bf8, BIT1 , BIT1 ),   //reg[112bf8]#1 = 1b
    #endif

    #if(PAD_LINEIN_R2_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_R2_OEN (PAD_LINEIN_R2_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_LINEIN_R2_OUT (PAD_LINEIN_R2_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2bf8, PAD_LINEIN_R2_OUT, BIT4),
    _RVM1(0x2bf8, PAD_LINEIN_R2_OEN, BIT6),
    _RVM1(0x2bf8, BIT5 , BIT5 ),   //reg[112bf8]#5 = 1b
    #endif

    #if(PAD_LINEIN_L3_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_L3_OEN (PAD_LINEIN_L3_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LINEIN_L3_OUT (PAD_LINEIN_L3_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bf9, PAD_LINEIN_L3_OUT, BIT0),
    _RVM1(0x2bf9, PAD_LINEIN_L3_OEN, BIT2),
    _RVM1(0x2bf9, BIT1 , BIT1 ),   //reg[112bf9]#1 = 1b
    #endif

    #if(PAD_LINEIN_R3_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_R3_OEN (PAD_LINEIN_R3_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_LINEIN_R3_OUT (PAD_LINEIN_R3_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2bf9, PAD_LINEIN_R3_OUT, BIT4),
    _RVM1(0x2bf9, PAD_LINEIN_R3_OEN, BIT6),
    _RVM1(0x2bf9, BIT5 , BIT5 ),   //reg[112bf9]#5 = 1b
    #endif

    #if(PAD_LINEIN_L4_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_L4_OEN (PAD_LINEIN_L4_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LINEIN_L4_OUT (PAD_LINEIN_L4_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bfa, PAD_LINEIN_L4_OUT, BIT0),
    _RVM1(0x2bfa, PAD_LINEIN_L4_OEN, BIT2),
    _RVM1(0x2bfa, BIT1 , BIT1 ),   //reg[112bfa]#1 = 1b
    #endif

    #if(PAD_LINEIN_R4_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_R4_OEN (PAD_LINEIN_R4_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_LINEIN_R4_OUT (PAD_LINEIN_R4_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2bfa, PAD_LINEIN_R4_OUT, BIT4),
    _RVM1(0x2bfa, PAD_LINEIN_R4_OEN, BIT6),
    _RVM1(0x2bfa, BIT5 , BIT5 ),   //reg[112bfa]#5 = 1b
    #endif

    #if(PAD_LINEIN_L5_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_L5_OEN (PAD_LINEIN_L5_IS_GPIO == GPIO_IN ? BIT2: 0)
    #define PAD_LINEIN_L5_OUT (PAD_LINEIN_L5_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x2bfb, PAD_LINEIN_L5_OUT, BIT0),
    _RVM1(0x2bfb, PAD_LINEIN_L5_OEN, BIT2),
    _RVM1(0x2bfb, BIT1 , BIT1 ),   //reg[112bfb]#1 = 1b
    #endif

    #if(PAD_LINEIN_R5_IS_GPIO != GPIO_NONE)
    #define PAD_LINEIN_R5_OEN (PAD_LINEIN_R5_IS_GPIO == GPIO_IN ? BIT6: 0)
    #define PAD_LINEIN_R5_OUT (PAD_LINEIN_R5_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x2bfb, PAD_LINEIN_R5_OUT, BIT4),
    _RVM1(0x2bfb, PAD_LINEIN_R5_OEN, BIT6),
    _RVM1(0x2bfb, BIT5 , BIT5 ),   //reg[112bfb]#5 = 1b
    #endif

    #if(PAD_RXCN_A_IS_GPIO != GPIO_NONE)
    #define PAD_RXCN_A_OEN_1 (PAD_RXCN_A_IS_GPIO == GPIO_IN ? 0 : BIT0)
    #define PAD_RXCN_A_OEN_0 (PAD_RXCN_A_IS_GPIO == GPIO_IN ? BIT0 : 0)
    #define PAD_RXCN_A_OUT (PAD_RXCN_A_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0b0e, PAD_RXCN_A_OUT, BIT0),
    _RVM1(0x0b0d, PAD_RXCN_A_OEN_1, BIT0}
    _RVM1(0x0b0c, PAD_RXCN_A_OEN_0, BIT0}
    #endif

    #if(PAD_RXCP_A_IS_GPIO != GPIO_NONE)
    #define PAD_RXCP_A_OEN_1 (PAD_RXCP_A_IS_GPIO == GPIO_IN ? 0 : BIT1)
    #define PAD_RXCP_A_OEN_0 (PAD_RXCP_A_IS_GPIO == GPIO_IN ? BIT1 : 0)
    #define PAD_RXCP_A_OUT (PAD_RXCP_A_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0b0e, PAD_RXCP_A_OUT, BIT1),
    _RVM1(0x0b0d, PAD_RXCP_A_OEN_1, BIT1}
    _RVM1(0x0b0c, PAD_RXCP_A_OEN_0, BIT1}
    #endif

    #if(PAD_RX0N_A_IS_GPIO != GPIO_NONE)
    #define PAD_RX0N_A_OEN_1 (PAD_RX0N_A_IS_GPIO == GPIO_IN ? 0 : BIT2)
    #define PAD_RX0N_A_OEN_0 (PAD_RX0N_A_IS_GPIO == GPIO_IN ? BIT2 : 0)
    #define PAD_RX0N_A_OUT (PAD_RX0N_A_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0b0e, PAD_RX0N_A_OUT, BIT2),
    _RVM1(0x0b0d, PAD_RX0N_A_OEN_1, BIT2}
    _RVM1(0x0b0c, PAD_RX0N_A_OEN_0, BIT2}
    #endif

    #if(PAD_RX0P_A_IS_GPIO != GPIO_NONE)
    #define PAD_RX0P_A_OEN_1 (PAD_RX0P_A_IS_GPIO == GPIO_IN ? 0 : BIT3)
    #define PAD_RX0P_A_OEN_0 (PAD_RX0P_A_IS_GPIO == GPIO_IN ? BIT3 : 0)
    #define PAD_RX0P_A_OUT (PAD_RX0P_A_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0b0e, PAD_RX0P_A_OUT, BIT3),
    _RVM1(0x0b0d, PAD_RX0P_A_OEN_1, BIT3}
    _RVM1(0x0b0c, PAD_RX0P_A_OEN_0, BIT3}
    #endif

    #if(PAD_RX1N_A_IS_GPIO != GPIO_NONE)
    #define PAD_RX1N_A_OEN_1 (PAD_RX1N_A_IS_GPIO == GPIO_IN ? 0 : BIT4)
    #define PAD_RX1N_A_OEN_0 (PAD_RX1N_A_IS_GPIO == GPIO_IN ? BIT4 : 0)
    #define PAD_RX1N_A_OUT (PAD_RX1N_A_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0b0e, PAD_RX1N_A_OUT, BIT4),
    _RVM1(0x0b0d, PAD_RX1N_A_OEN_1, BIT4}
    _RVM1(0x0b0c, PAD_RX1N_A_OEN_0, BIT4}
    #endif

    #if(PAD_RX1P_A_IS_GPIO != GPIO_NONE)
    #define PAD_RX1P_A_OEN_1 (PAD_RX1P_A_IS_GPIO == GPIO_IN ? 0 : BIT5)
    #define PAD_RX1P_A_OEN_0 (PAD_RX1P_A_IS_GPIO == GPIO_IN ? BIT5 : 0)
    #define PAD_RX1P_A_OUT (PAD_RX1P_A_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0b0e, PAD_RX1P_A_OUT, BIT5),
    _RVM1(0x0b0d, PAD_RX1P_A_OEN_1, BIT5}
    _RVM1(0x0b0c, PAD_RX1P_A_OEN_0, BIT5}
    #endif

    #if(PAD_RX2N_A_IS_GPIO != GPIO_NONE)
    #define PAD_RX2N_A_OEN_1 (PAD_RX2N_A_IS_GPIO == GPIO_IN ? 0 : BIT6)
    #define PAD_RX2N_A_OEN_0 (PAD_RX2N_A_IS_GPIO == GPIO_IN ? BIT6 : 0)
    #define PAD_RX2N_A_OUT (PAD_RX2N_A_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0b0e, PAD_RX2N_A_OUT, BIT6),
    _RVM1(0x0b0d, PAD_RX2N_A_OEN_1, BIT6}
    _RVM1(0x0b0c, PAD_RX2N_A_OEN_0, BIT6}
    #endif

    #if(PAD_RX2P_A_IS_GPIO != GPIO_NONE)
    #define PAD_RX2P_A_OEN_1 (PAD_RX2P_A_IS_GPIO == GPIO_IN ? 0 : BIT7)
    #define PAD_RX2P_A_OEN_0 (PAD_RX2P_A_IS_GPIO == GPIO_IN ? BIT7 : 0)
    #define PAD_RX2P_A_OUT (PAD_RX2P_A_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0b0e, PAD_RX2P_A_OUT, BIT7),
    _RVM1(0x0b0d, PAD_RX2P_A_OEN_1, BIT7}
    _RVM1(0x0b0c, PAD_RX2P_A_OEN_0, BIT7}
    #endif

    #if(PAD_RXCN_B_IS_GPIO != GPIO_NONE)
    #define PAD_RXCN_B_OEN_1 (PAD_RXCN_B_IS_GPIO == GPIO_IN ? 0 : BIT0)
    #define PAD_RXCN_B_OEN_0 (PAD_RXCN_B_IS_GPIO == GPIO_IN ? BIT0 : 0)
    #define PAD_RXCN_B_OUT (PAD_RXCN_B_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0b12, PAD_RXCN_B_OUT, BIT0),
    _RVM1(0x0b11, PAD_RXCN_B_OEN_1, BIT0}
    _RVM1(0x0b10, PAD_RXCN_B_OEN_0, BIT0}
    #endif

    #if(PAD_RXCP_B_IS_GPIO != GPIO_NONE)
    #define PAD_RXCP_B_OEN_1 (PAD_RXCP_B_IS_GPIO == GPIO_IN ? 0 : BIT1)
    #define PAD_RXCP_B_OEN_0 (PAD_RXCP_B_IS_GPIO == GPIO_IN ? BIT1 : 0)
    #define PAD_RXCP_B_OUT (PAD_RXCP_B_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0b12, PAD_RXCP_B_OUT, BIT1),
    _RVM1(0x0b11, PAD_RXCP_B_OEN_1, BIT1}
    _RVM1(0x0b10, PAD_RXCP_B_OEN_0, BIT1}
    #endif

    #if(PAD_RX0N_B_IS_GPIO != GPIO_NONE)
    #define PAD_RX0N_B_OEN_1 (PAD_RX0N_B_IS_GPIO == GPIO_IN ? 0 : BIT2)
    #define PAD_RX0N_B_OEN_0 (PAD_RX0N_B_IS_GPIO == GPIO_IN ? BIT2 : 0)
    #define PAD_RX0N_B_OUT (PAD_RX0N_B_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0b12, PAD_RX0N_B_OUT, BIT2),
    _RVM1(0x0b11, PAD_RX0N_B_OEN_1, BIT2}
    _RVM1(0x0b10, PAD_RX0N_B_OEN_0, BIT2}
    #endif

    #if(PAD_RX0P_B_IS_GPIO != GPIO_NONE)
    #define PAD_RX0P_B_OEN_1 (PAD_RX0P_B_IS_GPIO == GPIO_IN ? 0 : BIT3)
    #define PAD_RX0P_B_OEN_0 (PAD_RX0P_B_IS_GPIO == GPIO_IN ? BIT3 : 0)
    #define PAD_RX0P_B_OUT (PAD_RX0P_B_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0b12, PAD_RX0P_B_OUT, BIT3),
    _RVM1(0x0b11, PAD_RX0P_B_OEN_1, BIT3}
    _RVM1(0x0b10, PAD_RX0P_B_OEN_0, BIT3}
    #endif

    #if(PAD_RX1N_B_IS_GPIO != GPIO_NONE)
    #define PAD_RX1N_B_OEN_1 (PAD_RX1N_B_IS_GPIO == GPIO_IN ? 0 : BIT4)
    #define PAD_RX1N_B_OEN_0 (PAD_RX1N_B_IS_GPIO == GPIO_IN ? BIT4 : 0)
    #define PAD_RX1N_B_OUT (PAD_RX1N_B_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0b12, PAD_RX1N_B_OUT, BIT4),
    _RVM1(0x0b11, PAD_RX1N_B_OEN_1, BIT4}
    _RVM1(0x0b10, PAD_RX1N_B_OEN_0, BIT4}
    #endif

    #if(PAD_RX1P_B_IS_GPIO != GPIO_NONE)
    #define PAD_RX1P_B_OEN_1 (PAD_RX1P_B_IS_GPIO == GPIO_IN ? 0 : BIT5)
    #define PAD_RX1P_B_OEN_0 (PAD_RX1P_B_IS_GPIO == GPIO_IN ? BIT5 : 0)
    #define PAD_RX1P_B_OUT (PAD_RX1P_B_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0b12, PAD_RX1P_B_OUT, BIT5),
    _RVM1(0x0b11, PAD_RX1P_B_OEN_1, BIT5}
    _RVM1(0x0b10, PAD_RX1P_B_OEN_0, BIT5}
    #endif

    #if(PAD_RX2N_B_IS_GPIO != GPIO_NONE)
    #define PAD_RX2N_B_OEN_1 (PAD_RX2N_B_IS_GPIO == GPIO_IN ? 0 : BIT6)
    #define PAD_RX2N_B_OEN_0 (PAD_RX2N_B_IS_GPIO == GPIO_IN ? BIT6 : 0)
    #define PAD_RX2N_B_OUT (PAD_RX2N_B_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0b12, PAD_RX2N_B_OUT, BIT6),
    _RVM1(0x0b11, PAD_RX2N_B_OEN_1, BIT6}
    _RVM1(0x0b10, PAD_RX2N_B_OEN_0, BIT6}
    #endif

    #if(PAD_RX2P_B_IS_GPIO != GPIO_NONE)
    #define PAD_RX2P_B_OEN_1 (PAD_RX2P_B_IS_GPIO == GPIO_IN ? 0 : BIT7)
    #define PAD_RX2P_B_OEN_0 (PAD_RX2P_B_IS_GPIO == GPIO_IN ? BIT7 : 0)
    #define PAD_RX2P_B_OUT (PAD_RX2P_B_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0b12, PAD_RX2P_B_OUT, BIT7),
    _RVM1(0x0b11, PAD_RX2P_B_OEN_1, BIT7}
    _RVM1(0x0b10, PAD_RX2P_B_OEN_0, BIT7}
    #endif

    #if(PAD_RXCN_D_IS_GPIO != GPIO_NONE)
    #define PAD_RXCN_D_OEN_1 (PAD_RXCN_D_IS_GPIO == GPIO_IN ? 0 : BIT0)
    #define PAD_RXCN_D_OEN_0 (PAD_RXCN_D_IS_GPIO == GPIO_IN ? BIT0 : 0)
    #define PAD_RXCN_D_OUT (PAD_RXCN_D_IS_GPIO == GPIO_OUT_HIGH ? BIT0: 0)
    _RVM1(0x0b16, PAD_RXCN_D_OUT, BIT0),
    _RVM1(0x0b15, PAD_RXCN_D_OEN_1, BIT0}
    _RVM1(0x0b14, PAD_RXCN_D_OEN_0, BIT0}
    #endif

    #if(PAD_RXCP_D_IS_GPIO != GPIO_NONE)
    #define PAD_RXCP_D_OEN_1 (PAD_RXCP_D_IS_GPIO == GPIO_IN ? 0 : BIT1)
    #define PAD_RXCP_D_OEN_0 (PAD_RXCP_D_IS_GPIO == GPIO_IN ? BIT1 : 0)
    #define PAD_RXCP_D_OUT (PAD_RXCP_D_IS_GPIO == GPIO_OUT_HIGH ? BIT1: 0)
    _RVM1(0x0b16, PAD_RXCP_D_OUT, BIT1),
    _RVM1(0x0b15, PAD_RXCP_D_OEN_1, BIT1}
    _RVM1(0x0b14, PAD_RXCP_D_OEN_0, BIT1}
    #endif

    #if(PAD_RX0N_D_IS_GPIO != GPIO_NONE)
    #define PAD_RX0N_D_OEN_1 (PAD_RX0N_D_IS_GPIO == GPIO_IN ? 0 : BIT2)
    #define PAD_RX0N_D_OEN_0 (PAD_RX0N_D_IS_GPIO == GPIO_IN ? BIT2 : 0)
    #define PAD_RX0N_D_OUT (PAD_RX0N_D_IS_GPIO == GPIO_OUT_HIGH ? BIT2: 0)
    _RVM1(0x0b16, PAD_RX0N_D_OUT, BIT2),
    _RVM1(0x0b15, PAD_RX0N_D_OEN_1, BIT2}
    _RVM1(0x0b14, PAD_RX0N_D_OEN_0, BIT2}
    #endif

    #if(PAD_RX0P_D_IS_GPIO != GPIO_NONE)
    #define PAD_RX0P_D_OEN_1 (PAD_RX0P_D_IS_GPIO == GPIO_IN ? 0 : BIT3)
    #define PAD_RX0P_D_OEN_0 (PAD_RX0P_D_IS_GPIO == GPIO_IN ? BIT3 : 0)
    #define PAD_RX0P_D_OUT (PAD_RX0P_D_IS_GPIO == GPIO_OUT_HIGH ? BIT3: 0)
    _RVM1(0x0b16, PAD_RX0P_D_OUT, BIT3),
    _RVM1(0x0b15, PAD_RX0P_D_OEN_1, BIT3}
    _RVM1(0x0b14, PAD_RX0P_D_OEN_0, BIT3}
    #endif

    #if(PAD_RX1N_D_IS_GPIO != GPIO_NONE)
    #define PAD_RX1N_D_OEN_1 (PAD_RX1N_D_IS_GPIO == GPIO_IN ? 0 : BIT4)
    #define PAD_RX1N_D_OEN_0 (PAD_RX1N_D_IS_GPIO == GPIO_IN ? BIT4 : 0)
    #define PAD_RX1N_D_OUT (PAD_RX1N_D_IS_GPIO == GPIO_OUT_HIGH ? BIT4: 0)
    _RVM1(0x0b16, PAD_RX1N_D_OUT, BIT4),
    _RVM1(0x0b15, PAD_RX1N_D_OEN_1, BIT4}
    _RVM1(0x0b14, PAD_RX1N_D_OEN_0, BIT4}
    #endif

    #if(PAD_RX1P_D_IS_GPIO != GPIO_NONE)
    #define PAD_RX1P_D_OEN_1 (PAD_RX1P_D_IS_GPIO == GPIO_IN ? 0 : BIT5)
    #define PAD_RX1P_D_OEN_0 (PAD_RX1P_D_IS_GPIO == GPIO_IN ? BIT5 : 0)
    #define PAD_RX1P_D_OUT (PAD_RX1P_D_IS_GPIO == GPIO_OUT_HIGH ? BIT5: 0)
    _RVM1(0x0b16, PAD_RX1P_D_OUT, BIT5),
    _RVM1(0x0b15, PAD_RX1P_D_OEN_1, BIT5}
    _RVM1(0x0b14, PAD_RX1P_D_OEN_0, BIT5}
    #endif

    #if(PAD_RX2N_D_IS_GPIO != GPIO_NONE)
    #define PAD_RX2N_D_OEN_1 (PAD_RX2N_D_IS_GPIO == GPIO_IN ? 0 : BIT6)
    #define PAD_RX2N_D_OEN_0 (PAD_RX2N_D_IS_GPIO == GPIO_IN ? BIT6 : 0)
    #define PAD_RX2N_D_OUT (PAD_RX2N_D_IS_GPIO == GPIO_OUT_HIGH ? BIT6: 0)
    _RVM1(0x0b16, PAD_RX2N_D_OUT, BIT6),
    _RVM1(0x0b15, PAD_RX2N_D_OEN_1, BIT6}
    _RVM1(0x0b14, PAD_RX2N_D_OEN_0, BIT6}
    #endif

    #if(PAD_RX2P_D_IS_GPIO != GPIO_NONE)
    #define PAD_RX2P_D_OEN_1 (PAD_RX2P_D_IS_GPIO == GPIO_IN ? 0 : BIT7)
    #define PAD_RX2P_D_OEN_0 (PAD_RX2P_D_IS_GPIO == GPIO_IN ? BIT7 : 0)
    #define PAD_RX2P_D_OUT (PAD_RX2P_D_IS_GPIO == GPIO_OUT_HIGH ? BIT7: 0)
    _RVM1(0x0b16, PAD_RX2P_D_OUT, BIT7),
    _RVM1(0x0b15, PAD_RX2P_D_OEN_1, BIT7}
    _RVM1(0x0b14, PAD_RX2P_D_OEN_0, BIT7}
    #endif

//---------------------------------------------------------------------
// Pad Configuartion
//---------------------------------------------------------------------
    _MEMMAP_nonPM_,

#if (PADS_TCON_CONFIG != Unknown_pad_mux)
#define TCON0    ((PADS_TCON_CONFIG & BIT0) ? BIT0 : 0)
#define TCON1    ((PADS_TCON_CONFIG & BIT1) ? BIT1 : 0)
#define TCON2    ((PADS_TCON_CONFIG & BIT2) ? BIT2 : 0)
#define TCON3    ((PADS_TCON_CONFIG & BIT3) ? BIT3 : 0)
#define TCON4    ((PADS_TCON_CONFIG & BIT4) ? BIT4 : 0)
#define TCON5    ((PADS_TCON_CONFIG & BIT5) ? BIT5 : 0)
#define TCON6    ((PADS_TCON_CONFIG & BIT6) ? BIT6 : 0)
#define TCON7    ((PADS_TCON_CONFIG & BIT7) ? BIT7 : 0)
#define SET_TCON TCON0|TCON1|TCON2|TCON3|TCON4|TCON5|TCON6|TCON7
        _RVM3(0x1EF2, SET_TCON, 0x3FFFFF),
#endif

#if (PADS_UART2_MODE != Unknown_pad_mux)
#define UART2_CFG   ((PADS_UART2_MODE == UART2_MODE(1)) ? BIT0: 0)
        _RVM1(0x1E05, UART2_CFG, BIT1|BIT0),
#endif

#if (PADS_UART3_MODE != Unknown_pad_mux)
#define UART3_CFG   ((PADS_UART3_MODE == UART3_MODE(1)) ? BIT2: 0)
        _RVM1(0x1E05, UART3_CFG, BIT3|BIT2),
#endif

#if (PADS_UART4_MODE != Unknown_pad_mux)
#define UART4_CFG   ((PADS_UART4_MODE == UART4_MODE(1)) ? BIT6: 0)
#define UART4_CFG2  ((PADS_UART4_MODE == UART4_MODE(2)) ? BIT1: 0)
        _RVM1(0x1E04, UART4_CFG, BIT7|BIT6),
        _RVM1(0x1E3F, UART4_CFG2, BIT1),
#endif

#if (PADS_FAST_UART_MODE != Unknown_pad_mux)
#define UARTF_CFG   ((PADS_FAST_UART_MODE == UARTF_MODE(1)) ? BIT4: 0)
        _RVM1(0x1E04, UARTF_CFG, BIT5|BIT4),
#endif

#define UART_INV    ((UART0_INV ? BIT0 : 0) | \
                     (UART1_INV ? BIT1 : 0) | \
                     (UART2_INV ? BIT2 : 0) | \
                     (UART3_INV ? BIT3 : 0) | \
                     (UART4_INV ? BIT4 : 0))

        _RVM1(0x1EAB, UART_INV, BITMASK(4:0)),
        _RVM1(0x1EA6, (UART1_SRC_SEL << 4) | (UART0_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA7, (UART3_SRC_SEL << 4) | (UART2_SRC_SEL << 0), BITMASK(7:0)),
        _RVM1(0x1EA8, (UART4_SRC_SEL << 0), BITMASK(3:0)),

#if (PADS_3DLR_MODE != Unknown_pad_mux)
#define XC3DLR_CFG   ((PADS_3DLR_MODE == XC3DLR_MODE(1)) ? BIT0: \
                                      (PADS_3DLR_MODE == XC3DLR_MODE(2)) ? BIT1: \
                                      (PADS_3DLR_MODE == XC3DLR_MODE(3)) ? (BIT1|BIT0): \
                                      (PADS_3DLR_MODE == XC3DLR_MODE(4)) ? BIT2: 0)
            _RVM1(0x1E10, XC3DLR_CFG, BIT2|BIT1|BIT0),
#endif

#if (PADS_TTL_MODE != Unknown_pad_mux)
#define TTL_CFG    ((PADS_TTL_MODE == TTL_MODE(1)) ? BIT0 : \
                                (PADS_TTL_MODE == TTL_MODE(2)) ? BIT1 : 0)
            _RVM1(0x1EF8, TTL_CFG, BIT1|BIT0),
#endif

#if (PADS_USBDRVVBUS != Unknown_pad_mux)
#define USBDRVVBUS_CFG ((PADS_USBDRVVBUS == USBDRVVBUS_MODE(1)) ? (BIT0) : \
                    (PADS_USBDRVVBUS == USBDRVVBUS_MODE(2)) ? (BIT1) : 0)
        _RVM1(0x1E04, USBDRVVBUS_CFG, BIT1|BIT0)
#endif

#if (PADS_MHLCBUS_MODE != Unknown_pad_mux)
#define MHLCBUS_CFG  ((PADS_MHLCBUS_MODE == MHLCBUS_MODE(1)) ? BIT0 : \
                                         (PADS_MHLCBUS_MODE == MHLCBUS_MODE(2)) ? BIT1 : \
                                         (PADS_MHLCBUS_MODE == MHLCBUS_MODE(3)) ? (BIT1|BIT0) : 0)
            _RVM1(0x1EFA, MHLCBUS_CFG, BIT1|BIT0),
        _MEMMAP_PM_,
        _RVM1(0x2F40, 0, BIT3), //oen
        _RVM1(0x2F40, 0, BIT4), //output low for hot plug
        _MEMMAP_nonPM_,
#endif

#if (PADS_MHLVBUS_MODE != Unknown_pad_mux)
#define MHLVBUS_CFG  ((PADS_MHLVBUS_MODE == MHLVBUS_MODE(1)) ? BIT5 : \
                                         (PADS_MHLVBUS_MODE == MHLVBUS_MODE(2)) ? BIT6 : \
                                         (PADS_MHLVBUS_MODE == MHLVBUS_MODE(3)) ? (BIT6|BIT5) : \
                                         (PADS_MHLVBUS_MODE == MHLVBUS_MODE(4)) ? BIT7 : 0)
            _RVM1(0x1EF9, MHLVBUS_CFG, BIT7|BIT6|BIT5),
#endif

#if (PADS_MHLDBG_MODE != Unknown_pad_mux)
#define MHLDBG_CFG ((PADS_MHLDBG_MODE == MHLDBG_MODE(1)) ? BIT4 : 0)
            _RVM1(0x1EF9, MHLDBG_CFG, BIT4),
#endif

#if (PADS_MHLDET_MODE != Unknown_pad_mux)
#define MHLDET_CFG ((PADS_MHLDET_MODE == MHLDET_MODE(1)) ? BIT0 : 0)
            _RVM1(0x1EF9, MHLDET_CFG, BIT0),
#endif

#if (PADS_DDCDA_MODE!= Unknown_pad_mux)
#define DDCDA_CFG ((PADS_DDCDA_MODE == DDCDA_MODE(1)) ? BIT1 : 0)
        _RVM1(0x1EF9, DDCDA_CFG, BIT1),
#endif

#if (PADS_DDCDB_MODE!= Unknown_pad_mux)
#define DDCDB_CFG ((PADS_DDCDB_MODE == DDCDB_MODE(1)) ? BIT2 : 0)
        _RVM1(0x1EF9, DDCDB_CFG, BIT2),
#endif

#if (PADS_DDCDC_MODE!= Unknown_pad_mux)
#define DDCDC_CFG ((PADS_DDCDC_MODE == DDCDC_MODE(1)) ? BIT3 : 0)
        _RVM1(0x1EF9, DDCDC_CFG, BIT3),
#endif

#if (PADS_I2SIN_MODE != Unknown_pad_mux)
#define I2SIN_CFG    ((PADS_I2SIN_MODE == I2SIN_MODE(1)) ? BIT3 : 0)
        _RVM1(0x1EAE, I2SIN_CFG, BIT4|BIT3),
#endif

#if (PADS_I2SOUT_MODE != Unknown_pad_mux)
#define I2SOUT_CFG   ((PADS_I2SOUT_MODE == I2SOUT_MODE(1)) ? BIT5 : \
                                     (PADS_I2SOUT_MODE == I2SOUT_MODE(2)) ? BIT6 : 0)
#define I2SOUT_CFG2   ((PADS_I2SOUT_MODE == I2SOUT_MODE(3)) ? BIT2 : \
                                         (PADS_I2SOUT_MODE == I2SOUT_MODE(4)) ? BIT3 : \
                                         (PADS_I2SOUT_MODE == I2SOUT_MODE(5)) ? (BIT4) : 0)
        _RVM1(0x1EAE, I2SOUT_CFG, BIT6|BIT5),
        _RVM1(0x1E3F, I2SOUT_CFG2, BIT4|BIT3|BIT2),
#endif

#if (PADS_CEC_MODE != Unknown_pad_mux)
#define CEC_CFG   ((PADS_CEC_MODE == CEC_MODE(1)) ? BIT6 : 0)
            _MEMMAP_PM_,
            _RVM1(0x3401, CEC_CFG, BIT6),
            _MEMMAP_nonPM_,
#endif

#if (PADS_SPDIF_IN != Unknown_pad_mux)
#define SPDIFIN_CFG   ((PADS_SPDIF_IN == SPDIF_IN_MODE(1)) ? BIT7 : 0)
#define SPDIFIN_CFG2   ((PADS_SPDIF_IN == SPDIF_IN_MODE(2)) ? BIT0 : 0)
            _RVM1(0x1EAE, SPDIFIN_CFG, BIT7),
            _RVM1(0x1EAF, SPDIFIN_CFG2, BIT0),
#endif

#if (PADS_SPDIF_OUT != Unknown_pad_mux)
#define SPDIFOUT_CFG  ((PADS_SPDIF_OUT == SPDIF_OUT_MODE(1)) ? BIT1 : 0)
#define SPDIFOUT_CFG2   ((PADS_SPDIF_OUT == SPDIF_OUT_MODE(2)) ? BIT5 : \
                                         (PADS_SPDIF_OUT == SPDIF_OUT_MODE(3)) ? BIT6 : \
                                         (PADS_SPDIF_OUT == SPDIF_OUT_MODE(4)) ? (BIT7) : 0)
            _RVM1(0x1EAF, SPDIFOUT_CFG, BIT1),
            _RVM1(0x1E3F, SPDIFOUT_CFG2, BIT7|BIT6|BIT5),
#endif

#if (PADS_INTGPIO_MODE!= Unknown_pad_mux)
#define INTGPIO_CFG   ((PADS_INT_GPIO == INTGPIO_MODE(1)) ? BIT2: 0)
        _RVM1(0x1E4F, INTGPIO_CFG, BIT2),
#endif

#if (PADS_PWM0_MODE != Unknown_pad_mux)
#define PWM0_CFG   ((PADS_PWM0_MODE == PWM0_MODE(1)) ? BIT4: 0)
        _RVM1(0x1E40, PWM0_CFG, BIT4),
        _RVM1(0x1E06, 0, BIT0),//pwm0 output enable
#endif

#if (PADS_PWM1_MODE != Unknown_pad_mux)
#define PWM1_CFG   ((PADS_PWM1_MODE == PWM1_MODE(1)) ? BIT5: 0)
        _RVM1(0x1E40, PWM1_CFG, BIT5),
        _RVM1(0x1E06, 0, BIT1),//pwm1 output enable
#endif

#if (PADS_PWM2_MODE != Unknown_pad_mux)
#define PWM2_CFG   ((PADS_PWM2_MODE == PWM2_MODE(1)) ? BIT6: 0)
        _RVM1(0x1E40, PWM2_CFG, BIT6),
        _RVM1(0x1E06, 0, BIT2),//pwm2 output enable
#endif

#if (PADS_PWM3_MODE != Unknown_pad_mux)
#define PWM3_CFG   ((PADS_PWM3_MODE == PWM3_MODE(1)) ? BIT7: 0)
        _RVM1(0x1E40, PWM3_CFG, BIT7),
        _RVM1(0x1E06, 0, BIT3),//pwm3 output enable
#endif

#if (PADS_PWM4_MODE != Unknown_pad_mux)
#define PWM3_CFG   ((PADS_PWM4_MODE == PWM3_MODE(2)) ? BIT0: 0)
        _RVM1(0x1E41, PWM3_CFG, BIT1|BIT0),
        _RVM1(0x1E06, 0, BIT3),//real PWM[3] ==> pwm3 output enable
#endif

#if (PADS_PWM5_MODE != Unknown_pad_mux)
#define PWM2_CFG   ((PADS_PWM5_MODE == PWM2_MODE(2)) ? BIT2: 0)
        _RVM1(0x1E41, PWM2_CFG, BIT3|BIT2),
        _RVM1(0x1E06, 0, BIT2),//real PWM[2] ==> pwm2 output enable
#endif

#if (PADS_DDCR_MODE != Unknown_pad_mux)
#define DDCR_CFG   ((PADS_DDCR_MODE == MIIC_MODE(1)) ? BIT0: \
                         (PADS_DDCR_MODE == MIIC_MODE(2)) ? (BIT1|BIT0): \
                         (PADS_DDCR_MODE == MIIC_MODE(3)) ? (BIT2|BIT0): \
                         (PADS_DDCR_MODE == MIIC_MODE(4)) ? (BIT2|BIT1|BIT0): \
                         (PADS_DDCR_MODE == DDCR_MODE(1)) ? BIT1: \
                         (PADS_DDCR_MODE == DDCR_MODE(2)) ? BIT2: \
                         (PADS_DDCR_MODE == DDCR_MODE(3)) ? (BIT2|BIT1): \
                         (PADS_DDCR_MODE == DDCR_MODE(4)) ? BIT3: 0)
            _RVM1(0x1EF6, DDCR_CFG, BIT3|BIT2|BIT1|BIT0),
#endif

#if (PADS_TSINP_MODE != Unknown_pad_mux)
#define TSINP_CFG ((PADS_TSINP_MODE == TSINP_MODE(1)) ? BIT4 : \
                     (PADS_TSINP_MODE == TSINP_MODE(2)) ? BIT5 : \
                     (PADS_TSINP_MODE == TSINP_MODE(3)) ? (BIT5|BIT4) : 0)
        _RVM1(0x1EF7, TSINP_CFG, BIT5|BIT4),
#endif

#if (PADS_TSINS_MODE!= Unknown_pad_mux)
#define TSINS_CFG ((PADS_TSINS_MODE == TSINS_MODE(1)) ? BIT0 : \
                     (PADS_TSINS_MODE == TSINS_MODE(2)) ? BIT1 : 0)
        _RVM1(0x1EF7, TSINS_CFG, BIT3|BIT2|BIT1|BIT0),
#endif

#if (PADS_TSOUTP_MODE!= Unknown_pad_mux)
#define TSOUTP_CFG ((PADS_TSOUTP_MODE == TSOUTP_MODE(1)) ? BIT0 : \
                      (PADS_TSOUTP_MODE == TSOUTP_MODE(2)) ? BIT1 : \
                      (PADS_TSOUTP_MODE == TSOUTP_MODE(3)) ? (BIT1|BIT0) : \
                      (PADS_TSOUTP_MODE == TSOUTP_MODE(4)) ? BIT2 : 0)
        _RVM1(0x1E1C, TSOUTP_CFG, BIT2|BIT1|BIT0),
#endif

#if (PADS_SPDIFARC_MODE!= Unknown_pad_mux)
#define SPDIFARC_CFG_MODE ((PADS_SPDIFARC_MODE == ENABLE) ? BIT5 : 0) //reg_arc_mode
#define SPDIFARC_CFG_HPLGC ((PADS_SPDIFARC_MODE == ENABLE) ? 0 : BIT2) //reg_hotplugc_gpio_out
        _RVM1(0x1E19, SPDIFARC_CFG_MODE, BIT5), //reg_0x101E_0C[13]
        _RVM1(0x1E17, SPDIFARC_CFG_HPLGC, BIT2), //reg_0x101E_0B[10]
#endif

#if (PADS_MHLPORT_MODE!= Unknown_pad_mux)
#define MHLPORT_CFG  ((PADS_MHLPORT_MODE == MHLPORT_MODE(1)) ? (BIT4|BIT3) : 0)
        _MEMMAP_PM_,
        _RVM1(0x2F40, MHLPORT_CFG, BIT4|BIT3),
#endif

    _MEMMAP_nonPM_,

    // Clear all pad in
    _RVM1(0x1EA1, 0, BIT7),
    _END_OF_TBL2_,

    //external flash #1
    _MEMMAP_PM_,
    _RVM1(0x0E6A, 0x00, BIT0), //reg_spi_gpio set to 0 (swtch to spi_do, spi_di, spi_ck)
    _RVM1(0x0E6A, 0x00, BIT1), //reg_spicsz0_gpio set to 0 (enable spi_cz0)
    _RVM1(0x08F4, 0x00, 0xFF), //reg_chip_select set to 0 (select external flash #1)

    _MEMMAP_nonPM_,

#if (PIN_FLASH_WP0)
  #if ((MS_BOARD_TYPE_SEL == BD_MST242A_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST094B_10ARJ_15374))//PIN_66: PAD_SAR1
    _RVM1(0x1424, BIT1, BIT1), //output high
    _RVM1(0x1423, 0, BIT1), //oen: output(0)
    _RVM1(0x1422, 0, BIT1 ),   //reg[1422] #1 = 0b
  #elif ((MS_BOARD_TYPE_SEL == BD_MST242D_D01A_S))//PIN_66: PAD_SAR1
    _RVM1(0x1424, BIT1, BIT1), //output high
    _RVM1(0x1423, 0, BIT1), //oen: output(0)
    _RVM1(0x1422, 0, BIT1 ),   //reg[1422] #1 = 0b
  #elif ((MS_BOARD_TYPE_SEL == BD_MST242B_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST096B_10ARU_15384)) //PIN_85: PAD_TCON0
    _RVM1(0x1e5e, BIT0, BIT0), //output high
    _RVM1(0x1e60, 0, BIT0), //oen: output(0)
    _RVM1(0x1e04, 0, BIT7|BIT6 ),   //reg[101e04]#7~#6 = 00b
    _RVM1(0x1ef2, 0, BIT0 ),   //reg[101ef2]#0 = 0b
    _RVM1(0x1e04, 0, BIT4 ),   //reg[101e04]#4 = 0b
    _RVM1(0x1e10, 0, BIT2|BIT1|BIT0 ),   //reg[101e10]#2~#0 = 000b
    _RVM1(0x1ef8, 0, BIT1 ),   //reg[101ef8]#1 = 0b
    _RVM1(0x1e40, 0, BIT1|BIT0  ),   //reg[101e40]#1 ~ #0  = 00b
    _RVM1(0x1ee2, 0, BIT3|BIT2 ),   //reg[101ee2]#3~#2 = 00b
    _RVM1(0x1ef7, 0, BIT5|BIT4 ),   //reg[101ef7]#5~#4 = 000b
    _RVM1(0x1ef7, 0, BIT1|BIT0 ),   //reg[101ef7]#1~#0 = 00b
    _RVM1(0x1e1c, 0, BIT2|BIT1|BIT0 ),   //reg[101e1c]#2~#0 = 000b
    _RVM1(0x1e26, 0, BIT7 ),   //reg[101e26]#7 = 0b
  #elif ((MS_BOARD_TYPE_SEL == BD_MST242C_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST097B_10ARB_15384))//PIN_115: PAD_GPIO30
    _RVM1(0x1e43, BIT2, BIT2), //output high
    _RVM1(0x1e47, 0, BIT2), //oen: output(0)
   #else
    //#error "Please select correct boards"
  #endif
#endif
    _END_OF_TBL2_,

};

void MDrv_Pad_Init( void )
{
    U8 code *pPadConfig;
    U8  u8Length;
    U16 u16Index; // register index
    U32 u32RegAddr;

    u32MapBase = _MapBase_nonPM_MELODY;

    pPadConfig = (U8 *)padInitTbl + 10;

    while (1)
    {
        u16Index = (pPadConfig[0] << 8) + (pPadConfig[1]);

        if (u16Index == 0xFFFF) // check end of table
            break;

        pPadConfig += 2;

        if(u16Index == 0x0000) // switch base address
        {
            u32RegAddr = (U32)(((U32)pPadConfig[0])<<16);
            u32MapBase = (U32)_MapBase_PM_MELODY + (u32RegAddr<<1);
            pPadConfig += 2;
            continue;
        }

        u8Length = HIGHBYTE(u16Index) >> 6;
        u16Index &= 0x3FFF;

        while (1)
        {
            //printf("%x = %bx & %bx\n", u16Index, pPadConfig[0], pPadConfig[1]);
            MDrv_PAD_WriteByteMask((U32)u16Index, pPadConfig[0], pPadConfig[1]);
            pPadConfig += 2;

            if (u8Length == 0)
                break;

            u8Length--;
            u16Index++;
        }
    }

}

//-----------------------------------------------------------------
// Sanity check for PAD_TOP setting (TODO)
//-----------------------------------------------------------------
#if 0
#if (UART0_SRC_SEL == UART1_SRC_SEL) || \
    (UART0_SRC_SEL == UART2_SRC_SEL) || \
    (UART1_SRC_SEL == UART2_SRC_SEL)
    #error "UART src selection conflict"
#endif
#endif


