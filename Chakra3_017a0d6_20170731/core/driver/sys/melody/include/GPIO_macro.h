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

#ifndef _DRV_GPIO_H_
#define _DRV_GPIO_H_

#include "chip/bond.h"  // pad index, and gpio mapping
#include "drvGlobal.h"  // register access functions
#include "drvGPIO.h"
#include "drvPM.h"

//------------------------------GPIO_PIN----------------------------------------
#define GPIO_NONE               0       // Not GPIO pin (default)
#define GPIO_IN                 1       // GPI
#define GPIO_OUT_LOW            2       // GPO output low
#define GPIO_OUT_HIGH           3       // GPO output high

//----------------------------------------------------------------------------
// Private Macros
//----------------------------------------------------------------------------

#define __GPIO_REG(g)       ___GPIO_REG(g)
#define __GPIO_BIT(g)       ___GPIO_BIT(g)

// don't use these outside this header
#define ___GPIO_REG(r, b)   r
#define ___GPIO_BIT(r, b)   b

//----------------------------------------------------------------------------
// Internal GPIO
//----------------------------------------------------------------------------
#define GPIO0_PAD PAD_TCON0
#define GPIO0_OEN 0x101e60, BIT0
#define GPIO0_OUT 0x101e5e, BIT0
#define GPIO0_IN  0x101e5c, BIT0

#define GPIO1_PAD PAD_TCON1
#define GPIO1_OEN 0x101e60, BIT1
#define GPIO1_OUT 0x101e5e, BIT1
#define GPIO1_IN  0x101e5c, BIT1

#define GPIO2_PAD PAD_TCON2
#define GPIO2_OEN 0x101e60, BIT2
#define GPIO2_OUT 0x101e5e, BIT2
#define GPIO2_IN  0x101e5c, BIT2

#define GPIO3_PAD PAD_TCON3
#define GPIO3_OEN 0x101e60, BIT3
#define GPIO3_OUT 0x101e5e, BIT3
#define GPIO3_IN  0x101e5c, BIT3

#define GPIO4_PAD PAD_TCON4
#define GPIO4_OEN 0x101e60, BIT4
#define GPIO4_OUT 0x101e5e, BIT4
#define GPIO4_IN  0x101e5c, BIT4

#define GPIO5_PAD PAD_TCON5
#define GPIO5_OEN 0x101e60, BIT5
#define GPIO5_OUT 0x101e5e, BIT5
#define GPIO5_IN  0x101e5c, BIT5

#define GPIO6_PAD PAD_TCON6
#define GPIO6_OEN 0x101e60, BIT6
#define GPIO6_OUT 0x101e5e, BIT6
#define GPIO6_IN  0x101e5c, BIT6

#define GPIO7_PAD PAD_TCON7
#define GPIO7_OEN 0x101e60, BIT7
#define GPIO7_OUT 0x101e5e, BIT7
#define GPIO7_IN  0x101e5c, BIT7

#define GPIO8_PAD PAD_TCON8
#define GPIO8_OEN 0x101e61, BIT0
#define GPIO8_OUT 0x101e5f, BIT0
#define GPIO8_IN  0x101e5d, BIT0

#define GPIO9_PAD PAD_TCON9
#define GPIO9_OEN 0x101e61, BIT1
#define GPIO9_OUT 0x101e5f, BIT1
#define GPIO9_IN  0x101e5d, BIT1

#define GPIO10_PAD PAD_TCON10
#define GPIO10_OEN 0x101e61, BIT2
#define GPIO10_OUT 0x101e5f, BIT2
#define GPIO10_IN  0x101e5d, BIT2

#define GPIO11_PAD PAD_TCON11
#define GPIO11_OEN 0x101e54, BIT0
#define GPIO11_OUT 0x101e52, BIT0
#define GPIO11_IN  0x101e50, BIT0

#define GPIO12_PAD PAD_PWM3
#define GPIO12_OEN 0x101e87, BIT7
#define GPIO12_OUT 0x101e85, BIT7
#define GPIO12_IN  0x101e83, BIT7

#define GPIO13_PAD PAD_PWM2
#define GPIO13_OEN 0x101e87, BIT6
#define GPIO13_OUT 0x101e85, BIT6
#define GPIO13_IN  0x101e83, BIT6

#define GPIO14_PAD PAD_PWM1
#define GPIO14_OEN 0x101e87, BIT5
#define GPIO14_OUT 0x101e85, BIT5
#define GPIO14_IN  0x101e83, BIT5

#define GPIO15_PAD PAD_PWM0
#define GPIO15_OEN 0x101e87, BIT4
#define GPIO15_OUT 0x101e85, BIT4
#define GPIO15_IN  0x101e83, BIT4

#define GPIO16_PAD PAD_LVSYNC
#define GPIO16_OEN 0x1032a2, BIT0
#define GPIO16_OUT 0x10329e, BIT0
#define GPIO16_IN  0x1032aa, BIT0

#define GPIO17_PAD PAD_LHSYNC
#define GPIO17_OEN 0x1032a2, BIT1
#define GPIO17_OUT 0x10329e, BIT1
#define GPIO17_IN  0x1032aa, BIT1

#define GPIO18_PAD PAD_LDE
#define GPIO18_OEN 0x1032a2, BIT2
#define GPIO18_OUT 0x10329e, BIT2
#define GPIO18_IN  0x1032aa, BIT2

#define GPIO19_PAD PAD_LCK
#define GPIO19_OEN 0x1032a2, BIT3
#define GPIO19_OUT 0x10329e, BIT3
#define GPIO19_IN  0x1032aa, BIT3

#define GPIO20_PAD PAD_R_ODD7
#define GPIO20_OEN 0x1032a2, BIT4
#define GPIO20_OUT 0x10329e, BIT4
#define GPIO20_IN  0x1032aa, BIT4

#define GPIO21_PAD PAD_R_ODD6
#define GPIO21_OEN 0x1032a2, BIT5
#define GPIO21_OUT 0x10329e, BIT5
#define GPIO21_IN  0x1032aa, BIT5

#define GPIO22_PAD PAD_R_ODD5
#define GPIO22_OEN 0x1032a2, BIT6
#define GPIO22_OUT 0x10329e, BIT6
#define GPIO22_IN  0x1032aa, BIT6

#define GPIO23_PAD PAD_R_ODD4
#define GPIO23_OEN 0x1032a2, BIT7
#define GPIO23_OUT 0x10329e, BIT7
#define GPIO23_IN  0x1032aa, BIT7

#define GPIO24_PAD PAD_R_ODD3
#define GPIO24_OEN 0x1032a3, BIT0
#define GPIO24_OUT 0x10329f, BIT0
#define GPIO24_IN  0x1032ab, BIT0

#define GPIO25_PAD PAD_R_ODD2
#define GPIO25_OEN 0x1032a3, BIT1
#define GPIO25_OUT 0x10329f, BIT1
#define GPIO25_IN  0x1032ab, BIT1

#define GPIO26_PAD PAD_R_ODD1
#define GPIO26_OEN 0x1032a3, BIT2
#define GPIO26_OUT 0x10329f, BIT2
#define GPIO26_IN  0x1032ab, BIT2

#define GPIO27_PAD PAD_R_ODD0
#define GPIO27_OEN 0x1032a3, BIT3
#define GPIO27_OUT 0x10329f, BIT3
#define GPIO27_IN  0x1032ab, BIT3

#define GPIO28_PAD PAD_G_ODD7
#define GPIO28_OEN 0x1032a3, BIT4
#define GPIO28_OUT 0x10329f, BIT4
#define GPIO28_IN  0x1032ab, BIT4

#define GPIO29_PAD PAD_G_ODD6
#define GPIO29_OEN 0x1032a3, BIT5
#define GPIO29_OUT 0x10329f, BIT5
#define GPIO29_IN  0x1032ab, BIT5

#define GPIO30_PAD PAD_G_ODD5
#define GPIO30_OEN 0x1032a3, BIT6
#define GPIO30_OUT 0x10329f, BIT6
#define GPIO30_IN  0x1032ab, BIT6

#define GPIO31_PAD PAD_G_ODD4
#define GPIO31_OEN 0x1032a3, BIT7
#define GPIO31_OUT 0x10329f, BIT7
#define GPIO31_IN  0x1032ab, BIT7

#define GPIO32_PAD PAD_G_ODD3
#define GPIO32_OEN 0x1032a4, BIT0
#define GPIO32_OUT 0x1032a0, BIT0
#define GPIO32_IN  0x1032ac, BIT0

#define GPIO33_PAD PAD_G_ODD2
#define GPIO33_OEN 0x1032a4, BIT1
#define GPIO33_OUT 0x1032a0, BIT1
#define GPIO33_IN  0x1032ac, BIT1

#define GPIO34_PAD PAD_G_ODD1
#define GPIO34_OEN 0x1032a4, BIT2
#define GPIO34_OUT 0x1032a0, BIT2
#define GPIO34_IN  0x1032ac, BIT2

#define GPIO35_PAD PAD_G_ODD0
#define GPIO35_OEN 0x1032a4, BIT3
#define GPIO35_OUT 0x1032a0, BIT3
#define GPIO35_IN  0x1032ac, BIT3

#define GPIO36_PAD PAD_B_ODD7
#define GPIO36_OEN 0x1032a4, BIT4
#define GPIO36_OUT 0x1032a0, BIT4
#define GPIO36_IN  0x1032ac, BIT4

#define GPIO37_PAD PAD_B_ODD6
#define GPIO37_OEN 0x1032a4, BIT5
#define GPIO37_OUT 0x1032a0, BIT5
#define GPIO37_IN  0x1032ac, BIT5

#define GPIO38_PAD PAD_B_ODD5
#define GPIO38_OEN 0x1032a4, BIT6
#define GPIO38_OUT 0x1032a0, BIT6
#define GPIO38_IN  0x1032ac, BIT6

#define GPIO39_PAD PAD_B_ODD4
#define GPIO39_OEN 0x1032a4, BIT7
#define GPIO39_OUT 0x1032a0, BIT7
#define GPIO39_IN  0x1032ac, BIT7

#define GPIO40_PAD PAD_B_ODD3
#define GPIO40_OEN 0x1032a5, BIT0
#define GPIO40_OUT 0x1032a1, BIT0
#define GPIO40_IN  0x1032ad, BIT0

#define GPIO41_PAD PAD_B_ODD2
#define GPIO41_OEN 0x1032a5, BIT1
#define GPIO41_OUT 0x1032a1, BIT1
#define GPIO41_IN  0x1032ad, BIT1

#define GPIO42_PAD PAD_B_ODD1
#define GPIO42_OEN 0x1032a5, BIT2
#define GPIO42_OUT 0x1032a1, BIT2
#define GPIO42_IN  0x1032ad, BIT2

#define GPIO43_PAD PAD_B_ODD0
#define GPIO43_OEN 0x1032a5, BIT3
#define GPIO43_OUT 0x1032a1, BIT3
#define GPIO43_IN  0x1032ad, BIT3

#define GPIO44_PAD PAD_GPIO0
#define GPIO44_OEN 0x101e7e, BIT0
#define GPIO44_OUT 0x101e7a, BIT0
#define GPIO44_IN  0x101e76, BIT0

#define GPIO45_PAD PAD_GPIO1
#define GPIO45_OEN 0x101e7e, BIT1
#define GPIO45_OUT 0x101e7a, BIT1
#define GPIO45_IN  0x101e76, BIT1

#define GPIO46_PAD PAD_GPIO2
#define GPIO46_OEN 0x101e7e, BIT2
#define GPIO46_OUT 0x101e7a, BIT2
#define GPIO46_IN  0x101e76, BIT2

#define GPIO47_PAD PAD_GPIO3
#define GPIO47_OEN 0x101e7e, BIT3
#define GPIO47_OUT 0x101e7a, BIT3
#define GPIO47_IN  0x101e76, BIT3

#define GPIO48_PAD PAD_GPIO4
#define GPIO48_OEN 0x101e7e, BIT4
#define GPIO48_OUT 0x101e7a, BIT4
#define GPIO48_IN  0x101e76, BIT4

#define GPIO49_PAD PAD_GPIO5
#define GPIO49_OEN 0x101e7e, BIT5
#define GPIO49_OUT 0x101e7a, BIT5
#define GPIO49_IN  0x101e76, BIT5

#define GPIO50_PAD PAD_GPIO6
#define GPIO50_OEN 0x101e7e, BIT6
#define GPIO50_OUT 0x101e7a, BIT6
#define GPIO50_IN  0x101e76, BIT6

#define GPIO51_PAD PAD_GPIO7
#define GPIO51_OEN 0x101e7e, BIT7
#define GPIO51_OUT 0x101e7a, BIT7
#define GPIO51_IN  0x101e76, BIT7

#define GPIO52_PAD PAD_GPIO8
#define GPIO52_OEN 0x101e7f, BIT0
#define GPIO52_OUT 0x101e7b, BIT0
#define GPIO52_IN  0x101e77, BIT0

#define GPIO53_PAD PAD_GPIO9
#define GPIO53_OEN 0x101e7f, BIT1
#define GPIO53_OUT 0x101e7b, BIT1
#define GPIO53_IN  0x101e77, BIT1

#define GPIO54_PAD PAD_GPIO10
#define GPIO54_OEN 0x101e7f, BIT2
#define GPIO54_OUT 0x101e7b, BIT2
#define GPIO54_IN  0x101e77, BIT2

#define GPIO55_PAD PAD_GPIO11
#define GPIO55_OEN 0x101e7f, BIT3
#define GPIO55_OUT 0x101e7b, BIT3
#define GPIO55_IN  0x101e77, BIT3

#define GPIO56_PAD PAD_GPIO12
#define GPIO56_OEN 0x101e7f, BIT4
#define GPIO56_OUT 0x101e7b, BIT4
#define GPIO56_IN  0x101e77, BIT4

#define GPIO57_PAD PAD_GPIO13
#define GPIO57_OEN 0x101e7f, BIT5
#define GPIO57_OUT 0x101e7b, BIT5
#define GPIO57_IN  0x101e77, BIT5

#define GPIO58_PAD PAD_GPIO14
#define GPIO58_OEN 0x101e7f, BIT6
#define GPIO58_OUT 0x101e7b, BIT6
#define GPIO58_IN  0x101e77, BIT6

#define GPIO59_PAD PAD_GPIO15
#define GPIO59_OEN 0x101e7f, BIT7
#define GPIO59_OUT 0x101e7b, BIT7
#define GPIO59_IN  0x101e77, BIT7

#define GPIO60_PAD PAD_GPIO16
#define GPIO60_OEN 0x101e80, BIT0
#define GPIO60_OUT 0x101e7c, BIT0
#define GPIO60_IN  0x101e78, BIT0

#define GPIO61_PAD PAD_GPIO17
#define GPIO61_OEN 0x101e80, BIT1
#define GPIO61_OUT 0x101e7c, BIT1
#define GPIO61_IN  0x101e78, BIT1

#define GPIO62_PAD PAD_GPIO18
#define GPIO62_OEN 0x101e80, BIT2
#define GPIO62_OUT 0x101e7c, BIT2
#define GPIO62_IN  0x101e78, BIT2

#define GPIO63_PAD PAD_GPIO19
#define GPIO63_OEN 0x101e80, BIT3
#define GPIO63_OUT 0x101e7c, BIT3
#define GPIO63_IN  0x101e78, BIT3

#define GPIO64_PAD PAD_INT
#define GPIO64_OEN 0x101e49, BIT2
#define GPIO64_OUT 0x101e45, BIT2
#define GPIO64_IN  0x101e4d, BIT2

//########################
//
//  SKIP GPIO65 : PAD_TESTPIN
//
//########################

#define GPIO66_PAD PAD_PMGPIO
#define GPIO66_OEN 0x0e3c, BIT1
#define GPIO66_OUT 0x0e3a, BIT1
#define GPIO66_IN  0x0e3b, BIT1

#define GPIO67_PAD PAD_GPIO_PM1
#define GPIO67_OEN 0x0e1e, BIT1
#define GPIO67_OUT 0x0e20, BIT1
#define GPIO67_IN  0x0e22, BIT1

#define GPIO68_PAD PAD_GPIO_PM4
#define GPIO68_OEN 0x0e1e, BIT4
#define GPIO68_OUT 0x0e20, BIT4
#define GPIO68_IN  0x0e22, BIT4

#define GPIO69_PAD PAD_GPIO_PM5
#define GPIO69_OEN 0x0e1e, BIT5
#define GPIO69_OUT 0x0e20, BIT5
#define GPIO69_IN  0x0e22, BIT5

#define GPIO70_PAD PAD_GPIO_PM6
#define GPIO70_OEN 0x0e1e, BIT6
#define GPIO70_OUT 0x0e20, BIT6
#define GPIO70_IN  0x0e22, BIT6

#define GPIO71_PAD PAD_CEC
#define GPIO71_OEN 0x0E3c, BIT2
#define GPIO71_OUT 0x0E3a, BIT2
#define GPIO71_IN  0x0E3b, BIT2

#define GPIO72_PAD PAD_SAR3
#define GPIO72_OEN 0x1423, BIT3
#define GPIO72_OUT 0x1424, BIT3
#define GPIO72_IN  0x1425, BIT3

#define GPIO73_PAD PAD_SAR2
#define GPIO73_OEN 0x1423, BIT2
#define GPIO73_OUT 0x1424, BIT2
#define GPIO73_IN  0x1425, BIT2

#define GPIO74_PAD PAD_SAR1
#define GPIO74_OEN 0x1423, BIT1
#define GPIO74_OUT 0x1424, BIT1
#define GPIO74_IN  0x1425, BIT1

#define GPIO75_PAD PAD_SAR0
#define GPIO75_OEN 0x1423, BIT0
#define GPIO75_OUT 0x1424, BIT0
#define GPIO75_IN  0x1425, BIT0

#define GPIO76_PAD PAD_IRIN
#define GPIO76_OEN 0x3404, BIT0
#define GPIO76_OUT 0x3402, BIT0
#define GPIO76_IN  0x3406, BIT0

#define GPIO77_PAD PAD_DDCDA_CLK
#define GPIO77_OEN 0x101e18, BIT0
#define GPIO77_OUT 0x101e16, BIT0
#define GPIO77_IN  0x101e14, BIT0

#define GPIO78_PAD PAD_DDCDA_DAT
#define GPIO78_OEN 0x101e18, BIT1
#define GPIO78_OUT 0x101e16, BIT1
#define GPIO78_IN  0x101e14, BIT1

#define GPIO79_PAD PAD_HOTPLUG_A
#define GPIO79_OEN 0x101e19, BIT0
#define GPIO79_OUT 0x101e17, BIT0
#define GPIO79_IN  0x101e15, BIT0

#define GPIO80_PAD PAD_DDCDB_CLK
#define GPIO80_OEN 0x101e18, BIT2
#define GPIO80_OUT 0x101e16, BIT2
#define GPIO80_IN  0x101e14, BIT2

#define GPIO81_PAD PAD_DDCDB_DAT
#define GPIO81_OEN 0x101e18, BIT3
#define GPIO81_OUT 0x101e16, BIT3
#define GPIO81_IN  0x101e14, BIT3

#define GPIO82_PAD PAD_HOTPLUG_B
#define GPIO82_OEN 0x101e19, BIT1
#define GPIO82_OUT 0x101e17, BIT1
#define GPIO82_IN  0x101e15, BIT1

#define GPIO83_PAD PAD_DDCDC_CLK
#define GPIO83_OEN 0x101e18, BIT4
#define GPIO83_OUT 0x101e16, BIT4
#define GPIO83_IN  0x101e14, BIT4

#define GPIO84_PAD PAD_DDCDC_DAT
#define GPIO84_OEN 0x101e18, BIT5
#define GPIO84_OUT 0x101e16, BIT5
#define GPIO84_IN  0x101e14, BIT5

#define GPIO85_PAD PAD_HOTPLUG_C
#define GPIO85_OEN 0x101e19, BIT2
#define GPIO85_OUT 0x101e17, BIT2
#define GPIO85_IN  0x101e15, BIT2

#define GPIO86_PAD PAD_MHL_DET
#define GPIO86_OEN 0x101e19, BIT3
#define GPIO86_OUT 0x101e17, BIT3
#define GPIO86_IN  0x101e15, BIT3

#define GPIO87_PAD PAD_ARC
#define GPIO87_OEN 0x101e19, BIT4
#define GPIO87_OUT 0x101e17, BIT4
#define GPIO87_IN  0x101e15, BIT4

//----------------------------------------------------------------------------
// GPIO dispatcher
//----------------------------------------------------------------------------

#define GPIO_NUM(pin)       CONCAT(GPIO_PAD_, pin)

//----------------------------------------------------------------------------
// Multi-SPI Flash
//----------------------------------------------------------------------------
#define _Janus_EMBEDDED_FLASH_   0   // 1: with enbeded flash, 0: without enbeded flash

#if _Janus_EMBEDDED_FLASH_  // with enbeded flash
#define SPI_SEL_NONE()      MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x01)   // external #1
#define SPI_SEL_CZ0()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x00)   // internal #0
#define SPI_SEL_CZ1()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x01)   // external #1
#define SPI_SEL_CZ2()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x02)   // external #2
#define SPI_SEL_CZ3()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x03)   // Reserved
#else                   // without enbeded flash
#define SPI_SEL_NONE()      MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x00)   // external #1
#define SPI_SEL_CZ0()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x00)   // external #1
#define SPI_SEL_CZ1()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x01)   // external #2
#define SPI_SEL_CZ2()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x02)   // external #3
#define SPI_SEL_CZ3()       MDrv_WriteByte(ISP_REG_BASE+0xF4, 0x03)   // Reserved
#endif

#endif /* _DRV_GPIO_H_ */
