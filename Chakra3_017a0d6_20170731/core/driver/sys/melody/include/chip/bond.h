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

#ifndef _CHIP_BOND_H_
#define _CHIP_BOND_H_

#include "Board.h"
//----------------------------------------------------------------------------
// UART_SRC_SEL
//----------------------------------------------------------------------------
#ifndef UART0_SRC_SEL
    #define UART0_SRC_SEL   (UART_SEL_R2)
#endif

#ifndef UART1_SRC_SEL
    #define UART1_SRC_SEL   (UART_SEL_NA)
#endif

#ifndef UART2_SRC_SEL
    #define UART2_SRC_SEL   (UART_SEL_NA)
#endif

#ifndef UART3_SRC_SEL
    #define UART3_SRC_SEL   (UART_SEL_NA)
#endif

#ifndef UART4_SRC_SEL
    #define UART4_SRC_SEL   (UART_SEL_NA)
#endif

//----------------------------------------------------------------------------
// UART_INV
//----------------------------------------------------------------------------

#ifndef UART0_INV
    #define UART0_INV   0
#endif

#ifndef UART1_INV
    #define UART1_INV   0
#endif

#ifndef UART2_INV
    #define UART2_INV   0
#endif

#ifndef UART3_INV
    #define UART3_INV   0
#endif

#ifndef UART4_INV
    #define UART4_INV   0
#endif

//----------------------------------------------------------------------------
// PIN_SPI_CZ[3:1]
//----------------------------------------------------------------------------

#ifndef PIN_SPI_CZ1
    #define PIN_SPI_CZ1 0
#endif

#ifndef PIN_SPI_CZ2
    #define PIN_SPI_CZ2 0
#endif

#ifndef PIN_SPI_CZ3
    #define PIN_SPI_CZ3 0
#endif

//----------------------------------------------------------------------------
// PIN_FLASH_WP
//----------------------------------------------------------------------------

#ifndef PIN_FLASH_WP0
    #define PIN_FLASH_WP0   0
#endif

#ifndef PIN_FLASH_WP1
    #define PIN_FLASH_WP1   0
#endif

#ifndef PIN_FLASH_WP2
    #define PIN_FLASH_WP2   0
#endif

#ifndef PIN_FLASH_WP3
    #define PIN_FLASH_WP3   0
#endif

#endif /* _CHIP_BOND_H_ */
