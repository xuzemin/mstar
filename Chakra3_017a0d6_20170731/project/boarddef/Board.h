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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _BOARD_H_
#define _BOARD_H_

#include "datatype.h"
#include "hwreg.h"
#include "chiptype.h"
#include "drvXC_IOPort.h"
//------------------------------BOOTLOADER--------------------------------------


//------------------------------ LGD --------------------------------------
//#define ART_SW_PROTO_BOARD
#define TOUCH_KEY_ID            (0x58)
#define LGD_TOUCH_KEY           1

//------------------------------PUMODE_WORK-------------------------------------
#define PUMODE_WORK             0
#define PUMODE_STANDBY          1

//------------------------------TV_SYSTEM---------------------------------------
#define TV_NTSC                 0
#define TV_PAL                  1
#define TV_CHINA                2

//------------------------------AUDIO_SYSTEM_SEL--------------------------------
#define AUDIO_SYSTEM_BTSC       0
#define AUDIO_SYSTEM_A2         1
#define AUDIO_SYSTEM_EIAJ       2

//Eddie added at 20071231
#define HDCPKEY_USE_CODE        0
#define HDCPKEY_USE_24C04       1
#define HDCPKEY_USE_24C08       2
#define HDCPKEY_USE_24C16       3
#define HDCPKEY_USE_24C32       4
//End of Eddie

//------------------------------DRAM type---------------------------------------
#define SDRAM_32                0
#define DDRAM_32                1
#define DDRAM_16                2

// new style for S4...
#define SDR                     0x10
#define DDR_I                   0x11
#define DDR_II                  0x12
#define DDR_III                 0x13

//------------------------------DRAM Bus---------------------------------------
#define DRAM_BUS_16             0
#define DRAM_BUS_32             1

//------------------------------DDRPLL Freq--------------------------------------
#define DDRLLL_FREQ_166         166
#define DDRLLL_FREQ_200         200
#define DDRLLL_FREQ_333         333
#define DDRLLL_FREQ_380         380
#define DDRLLL_FREQ_400         400
#define DDRLLL_FREQ_450         450

#define LC_60DX440U             0


#if (LC_60DX440U)
#define SAMPO_IR_TYPE       IR_TYPE_SHARP_RC
#define HONHAI60            1
#else
#define SAMPO_IR_TYPE       IR_TYPE_SAMPO_RC
#define HONHAI60            0
#endif


//------------------------------DRAM Chip---------------------------------------
#define DRAM_ETRON              0
#define DRAM_NANYA              1

//------------------------------DRAM Size---------------------------------------
#define DDRAM16_32M             0
#define DDRAM16_64M             1

#define EEPROM_CLK_100KHZ       0
#define EEPROM_CLK_200KHZ       1
#define EEPROM_CLK_400KHZ       2

#define EEPROM_BLK_CPY_SIZE     MSAPI_DMX_SECTION_4K

//------------------------------HDCP_KEY_TYPE-------------------------------
#define HDCP_KEY_IN_CODE        0 //debug only
#define HDCP_KEY_IN_24C04       1 //Product use
#define HDCP_KEY_IN_24C64       2 //debug only
#define HDCP_KEY_IN_DB          3 //Product use
#define HDCP_KEY_IN_EFUSE       4 //Product use


#define HDCP22_KEY_IN_CODE        0 //debug only
#define HDCP22_KEY_IN_DB          1 //Product use
#define HDCP22_KEY_NONE           9 //Product use


#define HDCP22_AES_KEY_IN_CODE        0 //debug/production use
#define HDCP22_AES_KEY_IN_DB          1 //Product use
#define HDCP22_AES_KEY_NONE           9 // no HDCP22

//------------------------------POWER_KEY_SEL------------
#define POWER_KEY_PAD_WAKEUP    0   // power key is connected to PAD_WAKEUP
#define POWER_KEY_PAD_INT       1   // power key is connected to PAD_INT

//------------------------------VIDEO_FIRMWARE_CODE_SEL-------------------------
#define VIDEO_FIRMWARE_CODE_SD  0x00
#define VIDEO_FIRMWARE_CODE_HD  0x10

//------------------------------IO_DEVICE_SEL-----------------------------------
#define IO_DEV_NULL                 (-1)
#define IO_DEV_UART0            0
#define IO_DEV_UART1            1
#define IO_DEV_PIU_UART0        2

//------------------------------EXT_SUBMCU_TYPE---------------------------------
#define EXT_SUBMCU_NONE         0
#define EXT_SUBMCU_MSTAR_UA01   1   // UART, chip A, protocol 01

//------------------------------------------------------------------------------------
//FRONTEND_DEMO_TUNER_IIC_TYPE
//------------------------------------------------------------------------------------
#define TWO_ROAD_SEPARATE       1
#define ONE_ROAD_BUS            2
#define DEMO_TO_TUNER           3

//------------------------------MEMORY_MAP--------------------------------------
//#define MMAP_24MB               0
#define MMAP_16MB               1
//#define MMAP_8MB                2
//#define MMAP_4MB                3
//#define MMAP_4MB_FLASH          4
#define MMAP_32MB               5
#define MMAP_64MB               6
//#define MMAP_64_32MB            7
#define MMAP_128MB              8//#define MMAP_64_64MB            8
//#define MMAP_64MB_SD            9
#define MMAP_64_64MB            10//#define MMAP_128MB              10
#define MMAP_128_128MB          11
#define MMAP_128_256MB          12
#define MMAP_256_256MB          13
#define MMAP_256MB              14


#define  DDR2_INTERFACE_QFP          0
#define  DDR2_INTERFACE_BGA          1
#define  DDR3_INTERFACE_BGA          2
#define  DDR2_INTERFACE_BGA_4X_MODE  3

//------------------------------MS_FONT_SIZE_TYPE-------------------------------
#define MS_FONT_SMALL               0
#define MS_FONT_LARGE               1
#define MS_FONT_NORMAL              2

//------------------------------UNUSED MACROS-----------------------------------
#define _FUNC_NOT_USED()            do {} while ( 0 )

//------------------------------MS_BOARD_TYPE_SEL-------------------------------
// Demo board made in Taiwan
/*
#define BD_MST064A_D01A_S               0x0094  // H6 USBx1
#define BD_MST064A_D01C_S               0x0095  // H6 USB x2
#define BD_MST064B_D01B_S               0x0096
#define BD_MST064C_D01A_S               0x0097  // TCON BGA27x27
#define BD_MST064D_D01A_S               0x0098
#define BD_MST064E_D01A                 0x0099
#define BD_MST064F_D01A                 0x009A

#define BD_MST072A_D01A_S               0x00A0
#define BD_MST072A_D01A                 0x00A1
#define BD_MST072B_D01B_S               0x00A2
*/

//S7M,...
/*
#define BD_T3_FPGA_001                  0x0701
#define BD_MST087A_D01A_S               0x0702  // 256p QFP
#define BD_MST087B_S7M_D01A_S           0x0703  // S7M - support URSA3
#define BD_MST087B_S7_D01A_S            0x0704  // S7
#define BD_MST087C_D02A_S               0x0705  // SEC X1
#define BD_MST087D_D01A_S               0x0706  // S7
#define BD_MST087C_D01A_S               0x0707  //
#define BD_MST087E_D01A_S               0x0708  //
#define BD_MST087E_D01A                 0x0709
#define BD_MST087F_D01A                 0x070A
*/

//S7LD
/*
#define BD_MST090A_D01A_S               0x0750
#define BD_MST090B_D01A_S               0x0751
#define BD_MST090C_D01A_S               0x0752
#define BD_MSD380B_D01A                 0x0753  //SZ T4 SD Board
#define BD_MST090D_D01A_S               0x0754
#define BD_MST090E_D01A_S               0x0755
#define BD_MST090F_C01A                 0x0756  //20100402EL
*/

//S7LA
/*
#define BD_MST091A_D01A_S               0x0780
#define BD_MST091B_D01A_S               0x0781
#define BD_MST091C_D01A_S               0x0782
*/

//S7J: please reserved 0x790 to 0x7A0 for Janus
/*
#define BD_MST092A_D01A_S               0x0790
#define BD_MST092B_D01A_S               0x0791
#define BD_MST092C_D01A_S               0x0792
#define BD_MST216A_JNS_10A_9463         0x0793
#define BD_MST092A_D01A                 0x0794
#define BD_MST092B_D01A                 0x0795
#define BD_MST092B_D02A                 0x0796

#define BD_LGD_V02                      0x079A
#define BD_LGD_TOUCH_KEY_206_207        0x079B
*/

//S8
/*
#define BD_MST093A_D01A_S               0x07A0
#define BD_MST087F_D01A_T8              0x07A1
#define BD_MST105A_D01A_S               0x07A2
#define BD_MST105B_D01A_S               0x07A3
#define BD_MST105C_D01A_S               0x07A4
#define BD_MST105B_D01A_S_T12           0x07A5
#define BD_MST105C_D01A_S_T12           0x07A6
#define BD_MST105D_D01A_S_T12           0x07A7
*/

//S7L / S7ML
/*
#define BD_MST106A_D01A_S               0x07B0
#define BD_MST106B_D01A_S               0x07B1
#define BD_MST105A_D01A_S_T9            0x07B2
#define BD_MST087E_D01A_T9              0x07B3
#define BD_MST110A_D01A_S               0x07B4
*/

// M10
//#define BD_MST109A_D01A_S               0x07C0
//#define BD_MST109C_D01A_S               0x07C1
//#define BD_MST109D_D01A_S               0x07C2
//#define BD_MST109E_D01A_S               0x07C3
//#define BD_MST109F_D01A_S               0x07C4

// EULER
#define BD_MST165A_D01B_S               0x0890  // PIN=100
#define BD_MST165B_D01B_S               0x0891  // PIN=128
#define BD_MST165C_D01B_S               0x0892  // PIN=156
#define BD_MST042B_EULER                0x0893  // PIN=128  //SZ demo board EDEN to EULER
#define BD_MST047B_10APU                0x0894  // PIN=128  //SZ demo board EDEN to EULER
#define BD_MST048B_10APB_13101          0x0895  // PIN=156

// Eden
#define BD_MST043B_10ALB_12351          0x08A0  // SZ Eden Board 156pin,old
#define BD_MST043B_10BLB_12413          0x08A1  // SZ Eden Board 156pin,new
#define BD_MST042B_10BLU_12423          0x08A2  // SZ Eden Board 128pin
#define BD_MST044B_10BLA_12423          0x08A3  // SZ Eden Board 100pin
#define BD_MST044B_10BLA_12423_32       0x08A4  // SZ Eden Board 100pin
#define BD_MST165A_D01A_S_EDEN          0x08A5  // PIN=100
#define BD_MST165C_D01A_S_EDEN          0x08A6  // PIN=
#define BD_MST165C_D01B_S_EDEN          0x08A7  // PIN=
#define BD_MST165A_D01B_S_EDEN          0x08A8  // PIN=100
#define BD_MST165B_D01A_S               0x08A9  // eden


//Emerald
#define BD_MST157A_D01A_S_EMERALD       0x0860
#define BD_MST157B_D01A_S_EMERALD       0x0861
#define BD_MST157C_D01A_S_EMERALD       0x0862
#define BD_MST157E_D01A_S_EMERALD       0x0863
#define BD_MST157E_D01B_S_EMERALD       0x0864
#define BD_MST157E_D01C_S_EMERALD       0x0865
#define BD_MST157E_D01D_S_EMERALD       0x0866
#define BD_MST157F_D01A_S_EMERALD       0x0867
#define BD_MST157E_C02A_EMERALD         0x0868  // demo board
#define BD_MST157E_C02A_EMERALD_CUS21SH 0x086F  // Sharp
#define BD_MST157E_C02A_EMERALD_CUS21SH_DTMB 0x0870  // Sharp China
#define BD_MST157I_D01A_S_EMERALD       0x0871

//Nugget
//#define BD_MST180A_D01A_S_NUGGET        0x0880
//#define BD_MST180B_D01A_S_NUGGET        0x0881
//#define BD_MST180C_D01A_S_NUGGET        0x0882

//Nikon
//#define BD_MST186A_D01A_S_NIKON         0x08C0
//#define BD_MST186B_D01A_S_NIKON         0x08C1
//#define BD_MST186C_D01A_S_NIKON         0x08C2
//#define BD_MST186D_D01A_S_NIKON         0x08C3

//Nasa
#define BD_MST195A_D01A_S_NASA          0x08D0
#define BD_MST195B_D01A_S_NASA          0x08D1
#define BD_MST195C_D01A_S_NASA          0x08D2
#define BD_MST186A_D01A_S_NASA          0x08D3
#define BD_MST186E_D01A_S_NASA          0x08D4
#define BD_MST060B_10AZBT_13502         0x08D5
#define BD_MST061B_10AZU_14014          0x08D6
#define BD_MST233B_D01A_S_NASA          0x08D7
#define BD_SEC_XL3_MEGA_NASA            0x08D8

//Milan
#define BD_MST214A_D01A_S_MILAN         0x08E0
#define BD_MST214B_D01A_S_MILAN         0x08E1
#define BD_MST214C_D01A_S_MILAN         0x08E2
#define BD_MST214D_D01A_S_MILAN         0x08E3
#define BD_MST073B_10AGS                0x08E4
#define BD_MST074B_10AGS                0x08E5

//Mulan
#define BD_MST225A_D01A_S_MULAN         0x0900

// Maya
#define BD_MST222A_D01A_S               0x0B00 //176 pin
#define BD_MST222B_D01A_S               0x0B01 //156 pin
#define BD_MST222C_D01A_S               0x0B02 //156 pin, Eden p2p
#define BD_MST084B_10AHB_15043          0x0B03 //SZ
#define BD_MST222F_D01A_S               0x0B04 //Need refined
#define BD_MST084B_10AHB_LVDS           0x0B05 //Box request board
#define BD_SOLUM_XL1U                   0x0B06 //SEC XL1U


//Whisky
#define BD_MST233A_D01A_S               0x0B10 //
#define BD_MST233B_D01A_S               0x0B11 //
#define BD_MST223B_D01A_S               0x0B14 //
#define BD_MST089B_10ANB_15213          0x0B12 //
#define BD_MST090B_10ANU_15213          0x0B13 //
#define BD_SOLUM_CUS                    0x0B15 // for Korea cus SoluM develop

//Melody
#define BD_MST242A_D01A_S               0x0B20 //  80 pin
#define BD_MST242B_D01A_S               0x0B21 // 128 pin
#define BD_MST242C_D01A_S               0x0B22 // 156 pin
#define BD_MST242D_D01A_S               0x0B23 // 80 pin
#define BD_MST097B_10ARB_15384          0x0B28 // 156 pin - sz
#define BD_MST096B_10ARU_15384          0x0B29 // 128 pin -sz
#define BD_MST094B_10ARJ_15374          0x0B2A //80 pin -sz
#define BD_MST106B_10ARU_16115_ISDB_MELODY  0x0B2B // 128 pin -sz
#define BD_MST094B_20ARJ_16234          0x0B2C //80 pin new -sz

//Marlon
#define BD_MST269A_D01A_S_MARLON        0x0B40 //256 pin
#define BD_MST269B_D01A_S_MARLON        0x0B41 //216 pin
#define BD_MST269C_D01A_S_MARLON        0x0B42 //156 pin (ginga)
#define BD_MST269D_D01A_S_MARLON        0x0B43 //156 pin
#define BD_MST269E_D01A_S_MARLON        0x0B44 //128 pin
#define BD_MST269F_D01A_S_MARLON        0x0B45 //216 pin (new with tcon)
#define BD_MST118B_10ALU                0x0B50 // SZ 128 pin
#define BD_MST120B_10ALS                0x0B51 // SZ 216 pin
#define BD_MST122B_10ALBT               0x0B52 // SZ 156 pin
#define BD_MST127B_10ALSA               0x0B53 // SZ 216 pin (new with tcon)

// SZ board
//#define BD_MST064D_D01A_S_SBTVD_SZ      0x0138
//#define BD_MST256A_TT2_10A              0x0139
//#define BD_MST064F_D01B_SZ              0x013A
//#define BD_MST256A_TT2_20A              0x013B
//#define BD_MSD256_T2_10A                0x013C
//#define BD_MST556A_T2_10A               0x013D
//#define BD_MST556A_T2_10A_HX            0x013E
//#define BD_MST087E_D01A_HX              0x013F  // T3 for Hisense
//#define BD_MST536P_T3_10A               0x0140
//#define BD_MST087F_D01A_T               0x0141
//#define BD_MST6I78_Konka                0x0142
//#define BD_MSD523B_D01A                 0x0143  //SZ T4 HD board
//#define BD_MSD441C_T7_10A               0x0144
//#define BD_MSD523B_T4_20A               0x0145
#define BD_MSD309PX_HIS                 0x0146  //base BD_MSD523B_D01A
//#define BD_MST6I78_MALATA               0x0147      // T3 for DDR3 for malata
//#define BD_TCL_JNS_10A_9463             0x0148
//#define BD_MSD523I_T4_10A               0x0149
//#define BD_MSD306PT_HIS                 0x0150  //base on BD_MSD380B_D01A
//#define BD_MSD308PX_TCL                 0x0151  //base BD_MSD523B_D01A
//#define BD_SHENZHEN_END                 0x01FF

// Mazda
#define BD_MST253A_D01A_S_MAZDA       0x0C00
#define BD_MST243B_D01A_S_MAZDA       0x0C01
#define BD_MST137B_10APT_MAZDA        0x0C02



// Others
#define BD_UNKNOWN                  0xFFFF

//------------------------------MS_PROJECT_TYPE_SEL-------------------------------
#define PRJ_UNKNOWN                 0xFFFF

//#define PRJ_CUS_CODE_MASK           0xFF00
//#define IS_CUS_CODE(x)              ( (MS_PROJECT_TYPE_SEL & PRJ_CUS_CODE_MASK) == ((x) & PRJ_CUS_CODE_MASK) )

//===============================================
#define EVENT_DV                0
#define EVENT_PV                1
#define EVENT_PQ                2
#define EVENT_MP                3

//#define BOOT_VER_EVENT          EVENT_DV
#define BOOT_VER_NUM            1

//#define SW_VER_EVENT            EVENT_DV
#define SW_VER_NUM              "0"
#define HW_VER                  0
//===============================================


//#define ENABLE_MLINK   0

#define MS_PROJECT_TYPE_SEL     PRJ_UNKNOWN

#define MODEL_NAME              "DVBT-----"     // Used in imginfo.c. 9 characters.
#define AUTO_BUILD_SW_VER       "0"
////////////////////////////////////////////////////////////////////////////////
#define ENABLE_UART1_DEBUG    0

#ifndef ENABLE_UART_INIT
#define ENABLE_UART_INIT                1
#endif

#ifndef COMB_2D3D_SWITCH_PATCH
    #define COMB_2D3D_SWITCH_PATCH      1 //For FT unstable Htotal channel in Shanghai 20101013
#endif

#ifndef ENABLE_FACTORY_INPUT_SOURCE_FUNCTION
    #define ENABLE_FACTORY_INPUT_SOURCE_FUNCTION    0
#endif

#ifndef ENABLE_UI_PALETTE
    #define ENABLE_UI_PALETTE   DISABLE
#endif

//------------------------------------------------------------------------------
// SW feature configure header file
#include "SW_Config.h"

#include "Enum_Device.h"

//---------------------------------------------------------------

// Euler
#if (MS_BOARD_TYPE_SEL == BD_MST165A_D01B_S)
    #include "BD_MST165A_D01B_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165B_D01B_S)
    #include "BD_MST165B_D01B_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165C_D01B_S)
    #include "BD_MST165C_D01B_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042B_EULER)
    #include "BD_MST042B_EULER.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST047B_10APU)
    #include "BD_MST047B_10APU.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST048B_10APB_13101)
    #include "BD_MST048B_10APB_13101.h"

//--------------------------------------------------------------

// Emerald
#elif (MS_BOARD_TYPE_SEL == BD_MST157E_C02A_EMERALD)
    #include "BD_MST157E_C02A_EMERALD.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST157E_C02A_EMERALD_CUS21SH)
    #include "BD_MST157E_C02A_EMERALD_CUS21SH.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST157E_C02A_EMERALD_CUS21SH_DTMB)
    #include "BD_MST157E_C02A_EMERALD_CUS21SH_DTMB.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST157A_D01A_S_EMERALD)    //Emerald
    #include "BD_MST157A_D01A_S_EMERALD.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST157B_D01A_S_EMERALD)    //Emerald
    #include "BD_MST157B_D01A_S_EMERALD.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST157C_D01A_S_EMERALD)    //Emerald
    #include "BD_MST157C_D01A_S_EMERALD.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST157I_D01A_S_EMERALD)
    #include "BD_MST157I_D01A_S_EMERALD.h"

//--------------------------------------------------------------

// Eden
#elif (MS_BOARD_TYPE_SEL == BD_MST043B_10ALB_12351)       // Eden
    #include "BD_MST043B_10ALB_12351.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST043B_10BLB_12413)       // Eden
    #include "BD_MST043B_10BLB_12413.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST042B_10BLU_12423)        // Eden
    #include "BD_MST042B_10BLU_12423.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST044B_10BLA_12423)        // Eden
    #include "BD_MST044B_10BLA_12423.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST044B_10BLA_12423_32)     // Eden
    #include "BD_MST044B_10BLA_12423_32.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165A_D01A_S_EDEN)     // Eden
    #include "BD_MST165A_D01A_S_EDEN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165A_D01B_S_EDEN)     // Eden
    #include "BD_MST165A_D01B_S_EDEN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165C_D01A_S_EDEN)     // Eden
    #include "BD_MST165C_D01A_S_EDEN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165C_D01B_S_EDEN)     // Eden
    #include "BD_MST165C_D01B_S_EDEN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST165B_D01A_S)   //Eden
    #include "BD_MST165B_D01A_S.h"
//--------------------------------------------------------------

// Nasa
#elif (MS_BOARD_TYPE_SEL == BD_MST195A_D01A_S_NASA)      //Nasa
    #include "BD_MST195A_D01A_S_NASA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST195B_D01A_S_NASA)      //Nasa
    #include "BD_MST195B_D01A_S_NASA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST195C_D01A_S_NASA)      //Nasa
    #include "BD_MST195C_D01A_S_NASA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST186A_D01A_S_NASA)      //Nasa
    #include "BD_MST186A_D01A_S_NASA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST186E_D01A_S_NASA)      //Nasa
    #include "BD_MST186E_D01A_S_NASA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST060B_10AZBT_13502)      //Nasa
    #include "BD_MST060B_10AZBT_13502.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST061B_10AZU_14014)      //Nasa
    #include "BD_MST061B_10AZU_14014.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST233B_D01A_S_NASA)      //Nasa
    #include "BD_MST233B_D01A_S_NASA.h"
#elif (MS_BOARD_TYPE_SEL == BD_SEC_XL3_MEGA_NASA)      //Nasa
    #include "BD_XL3_MEGA_NASA.h"

//--------------------------------------------------------------

// Milan
#elif (MS_BOARD_TYPE_SEL == BD_MST214A_D01A_S_MILAN)     //Milan
    #include "BD_MST214A_D01A_S_MILAN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST214B_D01A_S_MILAN)     //Milan
    #include "BD_MST214B_D01A_S_MILAN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST214C_D01A_S_MILAN)     //Milan
    #include "BD_MST214C_D01A_S_MILAN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST214D_D01A_S_MILAN)     //Milan
    #include "BD_MST214D_D01A_S_MILAN.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST073B_10AGS)            //Milan
    #include "BD_MST073B_10AGS.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST074B_10AGS)            //Milan
    #include "BD_MST074B_10AGS.h"

//--------------------------------------------------------------

// Maya
#elif (MS_BOARD_TYPE_SEL == BD_MST084B_10AHB_15043) // Maya
    #include "BD_MST084B_10AHB_15043.h"

#elif (MS_BOARD_TYPE_SEL == BD_SOLUM_XL1U) // Maya
    #include "BD_SOLUM_XL1U.h"


#elif (MS_BOARD_TYPE_SEL == BD_MST222B_D01A_S) // Maya
    #include "BD_MST222B_D01A_S.h"

#elif (MS_BOARD_TYPE_SEL == BD_MST084B_10AHB_LVDS) // Maya
    #include "BD_MST084B_10AHB_LVDS.h"

#elif (MS_BOARD_TYPE_SEL == BD_MST222F_D01A_S) // Maya
    #include "BD_MST222F_D01A_S.h"

//#elif (MS_BOARD_TYPE_SEL == BD_MST225A_D01A_S_MULAN) // Mulan
//    #include "BD_MST225A_D01A_S_MULAN.h"

//--------------------------------------------------------------

//whisky
#elif (MS_BOARD_TYPE_SEL == BD_MST233A_D01A_S)
    #include "BD_MST233A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST233B_D01A_S)
    #include "BD_MST233B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST223B_D01A_S)
    #include "BD_MST223B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST089B_10ANB_15213)
    #include "BD_MST089B_10ANB_15213.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST090B_10ANU_15213)
    #include "BD_MST090B_10ANU_15213.h"
#elif (MS_BOARD_TYPE_SEL == BD_SOLUM_CUS)
    #include "BD_SOLUM_CUS.h"
//--------------------------------------------------------------

//Melody
#elif (MS_BOARD_TYPE_SEL == BD_MST242A_D01A_S)
    #include "BD_MST242A_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST242B_D01A_S)
    #include "BD_MST242B_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST242C_D01A_S)
    #include "BD_MST242C_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST242D_D01A_S)
    #include "BD_MST242D_D01A_S.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST097B_10ARB_15384)
    #include "BD_MST097B_10ARB_15384.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST096B_10ARU_15384)
    #include "BD_MST096B_10ARU_15384.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST106B_10ARU_16115_ISDB_MELODY)
    #include "BD_MST106B_10ARU_16115_ISDB_MELODY.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST094B_10ARJ_15374)
    #include "BD_MST094B_10ARJ_15374.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST094B_20ARJ_16234)
    #include "BD_MST094B_20ARJ_16234.h"
//--------------------------------------------------------------

// Marlon
#elif (MS_BOARD_TYPE_SEL == BD_MST269A_D01A_S_MARLON)     //Marlon
    #include "BD_MST269A_D01A_S_MARLON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST269B_D01A_S_MARLON)     //Marlon
    #include "BD_MST269B_D01A_S_MARLON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST269C_D01A_S_MARLON)     //Marlon
    #include "BD_MST269C_D01A_S_MARLON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST269D_D01A_S_MARLON)     //Marlon
    #include "BD_MST269D_D01A_S_MARLON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST269E_D01A_S_MARLON)     //Marlon
    #include "BD_MST269E_D01A_S_MARLON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST269F_D01A_S_MARLON)     //Marlon
    #include "BD_MST269F_D01A_S_MARLON.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST118B_10ALU)
    #include "BD_MST118B_10ALU.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST120B_10ALS)
    #include "BD_MST120B_10ALS.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST122B_10ALBT)
    #include "BD_MST122B_10ALBT.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST127B_10ALSA)
    #include "BD_MST127B_10ALSA.h"
//--------------------------------------------------------------

#elif (MS_BOARD_TYPE_SEL == BD_MST253A_D01A_S_MAZDA)/*Mazda*/
    #include "BD_MST253A_D01A_S_MAZDA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST243B_D01A_S_MAZDA)/*Mazda*/
    #include "BD_MST243B_D01A_S_MAZDA.h"
#elif (MS_BOARD_TYPE_SEL == BD_MST137B_10APT_MAZDA)/*Mazda*/
    #include "BD_MST137B_10APT_MAZDA.h"

//--------------------------------------------------------------

#else
    #error Unknow board type
#endif


/******************************************************************************/

#ifndef USE_UTOPIA
    #define USE_UTOPIA                          DISABLE
#endif

#ifndef FRONTEND_DEMOD_DVBT_TYPE
    #define FRONTEND_DEMOD_DVBT_TYPE            FRONTEND_DEMOD_TYPE
    #define TS_PARALLEL_DVBT_OUTPUT             TS_PARALLEL_OUTPUT
    #define DEMOD_DVBT_USE_UTOPIA               USE_UTOPIA
#endif

#ifndef FRONTEND_DEMOD_T2_TYPE
    #define FRONTEND_DEMOD_T2_TYPE          MSTAR_NONE_DEMOD
#endif

#ifndef TS_PARALLEL_DVBT2_OUTPUT
    #define TS_PARALLEL_DVBT2_OUTPUT            TS_PARALLEL_OUTPUT
#endif

#ifndef FRONTEND_DEMOD_DVBC_TYPE
    #define FRONTEND_DEMOD_DVBC_TYPE            FRONTEND_SECOND_DEMOD_TYPE
    #define TS_PARALLEL_DVBC_OUTPUT             TS_PARALLEL_OUTPUT
    #define DEMOD_DVBC_USE_UTOPIA               USE_UTOPIA
#endif

#ifndef FRONTEND_DEMOD_DTMB_TYPE
    #define FRONTEND_DEMOD_DTMB_TYPE            MSTAR_NONE_DEMOD
    #define TS_PARALLEL_DTMB_OUTPUT             (!TS_PARALLEL_OUTPUT)
    #define DEMOD_DTMB_USE_UTOPIA               USE_UTOPIA
#endif

#ifndef FRONTEND_DEMOD_ISDBT_TYPE
    #define FRONTEND_DEMOD_ISDBT_TYPE           MSTAR_NONE_DEMOD
    #define TS_PARALLEL_ISDBT_OUTPUT            (!TS_PARALLEL_OUTPUT)
    #define DEMOD_ISDBT_USE_UTOPIA              USE_UTOPIA
#endif


//---------------------------------------------------------------------------
#if 1//(ENABLE_S2)
  #ifndef FRONTEND_DEMOD_S2_TYPE
    #define FRONTEND_DEMOD_S2_TYPE              MSTAR_NONE_DEMOD
  #endif

  #ifndef TS_PARALLEL_S2_OUTPUT
    #define TS_PARALLEL_S2_OUTPUT               TS_PARALLEL_OUTPUT
  #endif
#endif
//---------------------------------------------------------------------------

//------------------------------ Bring up define -----------------------------------
//#define _TEMP_S7LD_                 0   // 1: unmask(for release),0:mask(for IP owner debug)
#define _TEST_VGA_                  0   //only for VGA ADC test good phase function: disable Peaking,sharpness, and nonscaling.
//#define _TEMP_S7LA_                 0   // 1: unmask(for release),0:mask(for IP owner debug)
//#define _TEMP_S8_                   1   // 1: unmask(for release),0:mask(for IP owner debug)
//#define _TEMP_M10_                  0   // 1: unmask(for release),0:mask(for IP owner debug)
#define _TEMP_EULER_                0 // 1: unmask(for release),0:mask(for IP owner debug)
#define _TEMP_S7L_ENABLE_URSA_      0
#define _TEMP_EMERALD_              0
#define _TEMP_NUGGET_               0
#define _TEMP_NIKON_                0
#define _TEMP_NASA_                 0
#define _TEMP_MILAN_                0
#define _TEMP_MELODY_               0
#define _TEMP_MARLON_               0

/*
#if (_TEMP_S7LD_)
    #define XC_BRINGUP              0  // 1: for chip bring up, usually we'll disable post-scaling filter of XC
    #define AU_BRINGUP              0   // 1: for chip bring up, usually we'll disable audio when bring up
#elif(_TEMP_M10_)
    #define XC_BRINGUP              0
    #define AU_BRINGUP              0
    */
#if(_TEMP_EULER_)
    #define XC_BRINGUP              0
    #define AU_BRINGUP              0
#elif(_TEMP_EMERALD_)
    #define XC_BRINGUP              1
    #define AU_BRINGUP              0
#elif(_TEMP_NUGGET_)
    #define XC_BRINGUP              1
    #define AU_BRINGUP              0
#elif(_TEMP_NIKON_)
    #define XC_BRINGUP              1
    #define AU_BRINGUP              0
#elif(_TEMP_NASA_)
    #define XC_BRINGUP              1
    #define AU_BRINGUP              0
#elif(_TEMP_MILAN_)
    #define XC_BRINGUP              0
    #define AU_BRINGUP              0
#elif(_TEMP_MELODY_)
    #define XC_BRINGUP              1
    #define AU_BRINGUP              0
#elif(_TEMP_MARLON_)
    #define XC_BRINGUP              0
    #define AU_BRINGUP              0
#else
    #define XC_BRINGUP              0
    #define AU_BRINGUP              0
#endif


//************************* CEC SW Version *************************

#define CEC_OLD_VERSION     0
#define CEC_NEW_VERSION     1   // currently only for Emerald

//
//------------------------------------------------------------------------------
// This file is used for config those option depend on chip
#include "config_depend_on_chip.h"

//------------------------------------------------------------------------------
// The file can fix compile error if some board definition didn't define
#include "default_option_define.h"

// TODO:

    // should always place in the end of Board.h; no move!
    #define XMODEM_DWNLD_ENABLE      0
    #define XMODEM_1K                0

//------PCI_PORT_FUNCTION---------------------------------------------------------
#define NO_PCI_PORT                 0x00
#define PCI_PORT_IS_GPIO            0x01
#define PCI_PORT_IS_CARDREADER      0x02
#define ATCON_PORT                  0x03

#define IS_GPIO_PIN                 0x00
#define IS_PWM_PIN                  0x01

//PWM0~3 mode
#define NORMAL_MODE                 0
#define ENHANCE_MODE                1

//------DMA TYPE------------------------------------------------------------------
#define DRAM_GE_DMA                 0
#define DRAM_W1_DMA                 1
#define DRAM_BYTEDMA                2
#define DRAM_DMATYPE                DRAM_BYTEDMA//DRAM_W1_DMA

//------Sub Micro-----------------------------------------------------------------
#ifndef EXT_SUBMCU_TYPE
#define EXT_SUBMCU_TYPE             EXT_SUBMCU_NONE
#endif

//------------------------------ Board Default -----------------------------------
#ifndef I2C_IO_EXPANDER_TYPE
#define I2C_IO_EXPANDER_TYPE        I2C_IO_EXPANDER_NONE
#endif

#ifndef USE_SW_I2C
#define USE_SW_I2C                  1
#endif


#ifndef INPUT_HDMI1_MUX
#define INPUT_HDMI1_MUX         INPUT_PORT_DVI0
#endif
#ifndef INPUT_HDMI2_MUX
#define INPUT_HDMI2_MUX         INPUT_PORT_DVI1
#endif
#ifndef INPUT_HDMI3_MUX
#define INPUT_HDMI3_MUX         INPUT_PORT_DVI2
#endif
#ifndef INPUT_HDMI4_MUX
#define INPUT_HDMI4_MUX         INPUT_PORT_DVI3
#endif

#ifndef PWS_INPUT_HDMI1_PATH
#define PWS_INPUT_HDMI1_PATH         _HDMI1_
#endif
#ifndef PWS_INPUT_HDMI2_PATH
#define PWS_INPUT_HDMI2_PATH         _HDMI2_
#endif
#ifndef PWS_INPUT_HDMI3_PATH
#define PWS_INPUT_HDMI3_PATH         _HDMI3_
#endif
#ifndef PWS_INPUT_HDMI4_PATH
#define PWS_INPUT_HDMI4_PATH         _HDMI4_
#endif

#ifndef ENABLE_PWS
#define ENABLE_PWS 0 // Analog IP PWS, for U3 and T3
#endif

#ifndef ENABLE_DIP_PWS
#define ENABLE_DIP_PWS 0  //Digital IP PWS, for U3 only now
#endif

#ifndef ENABLE_DIP_MONITOR
#define ENABLE_DIP_MONITOR 0//For U3 oly now
#endif

#ifndef INPUT_SCART1_FS_USE_SAR2
#define INPUT_SCART1_FS_USE_SAR2 0
#endif

#ifndef SCART_ALWAYS_OUTPUT_ATV
#if ENABLE_ATSC
#define  SCART_ALWAYS_OUTPUT_ATV  DISABLE
#else
#define  SCART_ALWAYS_OUTPUT_ATV  ENABLE
#endif
#endif

//----SPI FLASH------------------------------------------------------------------
#ifndef FLASH_BLOCK_SIZE
    #define FLASH_BLOCK_SIZE    0x10000
#endif
#ifndef MAINSPKOPA
   #define  MAINSPKOPA   1
#endif

#ifndef ENABLE_POWERON_VIDEO
    #define ENABLE_POWERON_VIDEO        DISABLE //enable it to display Video when system boot up
#endif

//#define FLASH_BLOCK_COUNT       (FLASH_SIZE/FLASH_BLOCK_SIZE)
#ifndef ENABLE_MFC_6M20
#define ENABLE_MFC_6M20    0
#endif

#ifndef ENABLE_MFC_6M30
#define ENABLE_MFC_6M30       0
#endif

#ifndef ENABLE_6M40_4KX2K_PROCESS
#define ENABLE_6M40_4KX2K_PROCESS       0// 6M40  Controll
#endif

#ifndef ENABLE_6M50_4KX2K_PROCESS
#define ENABLE_6M50_4KX2K_PROCESS       0// 6M50  Controll ,ENBALE 6M50,MUST ENBALE 6M40,because use same driver.
#endif

#ifndef ENABLE_TCON_IN8903_PROCESS
    #define ENABLE_TCON_IN8903_PROCESS       0// TCON IN8903 (Innolux 4K2K Vx1 Tcon)
#endif

#ifndef CONFIG_3D_HWLVDSLRFLAG
#define CONFIG_3D_HWLVDSLRFLAG       0
#endif

#if 0//(CHIP_FAMILY_TYPE == CHIP_FAMILY_A5)
    #define ENABLE_FRC_R2               1
    #define VD_PLAYER_IS_IN_CROP_CPU    0
#else
    #define ENABLE_FRC_R2               0
#if((CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)&&(MEMORY_MAP == MMAP_32MB)&&(ENABLE_ATSC))
    #define VD_PLAYER_IS_IN_CROP_CPU    0
#else
    #define VD_PLAYER_IS_IN_CROP_CPU    1
#endif
#endif

#ifndef ENABLE_MM_HD_FB
    #define ENABLE_MM_HD_FB             DISABLE
#endif


#ifndef ENABLE_DTV_HD_FB
    #define ENABLE_DTV_HD_FB            DISABLE
#endif


#define IS_MXL_TUNER        (  (FRONTEND_TUNER_TYPE == MxL_601SI_TUNER) \
                            || (FRONTEND_TUNER_TYPE == MxL_301RF_TUNER) \
                            || (FRONTEND_TUNER_TYPE == MxL_661SI_TUNER) )

#if(ENABLE_ATSC)
  #ifndef ENABLE_SOUNDTRACK_CHECKER_NEW
    #define ENABLE_SOUNDTRACK_CHECKER_NEW      1
  #endif
#endif

//------------------------------------------------------------------
#ifndef Set_3D_OFF
    #define Set_3D_OFF()    _FUNC_NOT_USED()
#endif

#ifndef Set_3D_ON
    #define Set_3D_ON()     _FUNC_NOT_USED()
#endif


//=======================================================
// Set LNB power mode by gpio:      ENABLE: GPIO/DISBALE: IIC
#ifndef ENABLE_LNBPW_BY_GPIO
    #define ENABLE_LNBPW_BY_GPIO            DISABLE
#endif
//=======================================================


#if (PADS_SPDIF_OUT != Unknown_pad_mux)
    #define HW_SPDIF_ENABLE         TRUE
#else
    #define HW_SPDIF_ENABLE         FALSE
#endif





//#######################
//Please do not remove below
//#######################
//******************************************************************************
// Bench option...
// Milan:
//  (1) signal sboot BIST status : PAD_PWM1
//  (2) signal App running status :
//       PAD_TCON0 : 214A
//       PAD_GPIO2 : 214B,214C,214D
//******************************************************************************
//#define BENCH_CODE_USAGE

#if( defined(MCU_AEON) && defined(MIPS_CHAKRA) )
    #error "compile option error!!"
#endif

#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
  #if( defined(MCU_AEON) )
    #error "compile option error!!"
  #endif
  #if( defined(MIPS_CHAKRA) )
    #error "compile option error!!"
  #endif
#endif

#endif // _BOARD_H_

