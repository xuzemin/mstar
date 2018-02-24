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

#ifndef _DRVSYS_H_
#define _DRVSYS_H_
#include "hwreg.h"
#include "drvGlobal.h"
#include "Board.h"
#include "InfoBlock.h"
#include "SysInit_Common.h"

#ifdef _DRV_SYS_C_
    #define DRVSYS_EX
#else
    #define DRVSYS_EX extern
#endif

#define SUBTITIE_OFFSET             0x10000

////////////////////////////////////////////////////////////////////////////////
// prototype for putcharUARTn
////////////////////////////////////////////////////////////////////////////////

#if ( ENABLE_UART0 )
DRVSYS_EX char putcharUART0( char c );
#else
#define putcharUART0( c )   _FUNC_NOT_USED()
#endif

#if 0//( ENABLE_UART1 )
DRVSYS_EX char putcharUART1( char c );
#else
#define putcharUART1( c )   _FUNC_NOT_USED()
#endif

DRVSYS_EX void puthex( U16 u16HexVal );

////////////////////////////////////////////////////////////////////////////////
// PIU Watch Dog Timer
////////////////////////////////////////////////////////////////////////////////

// Disable watchdog is not suggested at any time, please ask related people first
// 1. During firmware upgrade, disable WDT before erase flash
// 2. In factory menu, WDT on/off option

#define MDrv_Sys_WatchDogCycles( sec ) (  (((sec) * MST_XTAL_CLOCK_HZ)) )



#define MDrv_Sys_ClearWatchDog()        MDrv_WriteByte(RIUBASE_WDT, MDrv_ReadByte(RIUBASE_WDT)|(BIT0))


#define  MDrv_Sys_IsWatchDogEnabled()    (MDrv_Read4Byte(WDT_TIMER_0))

DRVSYS_EX void  MDrv_Sys_EnableWatchDog(void);
DRVSYS_EX void MDrv_Sys_SetWatchDogTimer( U8 sec );
DRVSYS_EX void MDrv_Sys_DisableWatchDog( void );




// This is not really necessary, WDT is enabled after MCU reset

//#define MDrv_Sys_IsWatchDogEnabled()    (MDrv_Read2Byte(WDT_RST) != 0xAA55)

#define MDrv_Sys_IsResetByWatchDog()    (MDrv_ReadByte(WDT_RST) & BIT0)


#define MDrv_Sys_ClearWatchDogStatus()  MDrv_WriteByte(WDT_RST, BIT0)




////////////////////////////////////////////////////////////////////////////////
// Uart mux selection (see UART_SEL_TYPE in hwreg_S4L.h for mux)
////////////////////////////////////////////////////////////////////////////////

#define MDrv_Sys_SetUart0Mux(mux)   MDrv_WriteByteMask( 0x1EA6, ((mux) << 2), BITMASK( 4:2 ) )
#define MDrv_Sys_SetUart1Mux(mux)   MDrv_WriteByteMask( 0x1EA6, ((mux) << 5), BITMASK( 7:5 ) )
#define MDrv_Sys_SetUart2Mux(mux)   MDrv_WriteByteMask( 0x1EA7, ((mux) << 0), BITMASK( 2:0 ) )

////////////////////////////////////////////////////////////////////////////////
//extern U32 u32SecbufAddr;
//extern U32 u32SecbufSize;

extern U32 u32OadbufMonitorAddr;
extern U32 u32OadbufMonitorSize;
extern U32 u32OadbufDownloadAddr;
extern U32 u32OadbufDownloadSize;

extern U32 u32SubtitleAddr;
extern U32 u32SubtitleSize;

DRVSYS_EX U8 u8ChipIdMajor;
DRVSYS_EX U8 u8ChipIdMinor;
DRVSYS_EX U8 u8ChipVer;
DRVSYS_EX U8 u8ChipRev;

DRVSYS_EX void MDrv_Sys_InitUartForXtalClk( char cOutputChar );
DRVSYS_EX bit  MDrv_Sys_IsCodeInSPI( void );
DRVSYS_EX void MDrv_Sys_RunCodeInMIU( U16 u16MIUAddrInBank, U8 u8NumBanks, BOOLEAN bBypassCache );
DRVSYS_EX void MDrv_Sys_RunCodeInSPI( void );
DRVSYS_EX void MDrv_Sys_WatchDogEnable(U8 mode);
DRVSYS_EX void MDrv_Sys_Set_ECC_DMA(U8 mode);
DRVSYS_EX void MDrv_Sys_Reboot( void );
DRVSYS_EX void MDrv_Sys_WholeChipReset( void );
DRVSYS_EX void MDrv_Sys_ResetAeon( BOOLEAN bReset );

// use "void *" as generic pointer type
DRVSYS_EX void MDrv_Sys_CopyMIU2VAR(U32 srcaddr, void *dstaddr, U16 len);
DRVSYS_EX void MDrv_Sys_CopyVAR2MIU(void *srcaddr, U32 dstaddr, U16 len);

DRVSYS_EX void MDrv_Sys_UartControl(BOOLEAN bEnable);
//DRVSYS_EX void AEON_StartAddress_Assignment(U8 Select, U32 CodeAddress, U32 DataAddress);


#if (XMODEM_DWNLD_ENABLE)
    DRVSYS_EX void MDrv_Sys_XmodemUartInit( void );
#endif

DRVSYS_EX void MDrv_Sys_Get_BinInfo(BININFO *pBinInfo, BOOLEAN *pbResult);
//DRVSYS_EX void MDrv_Sys_Set_CIDInfo(U8 *pCIDInfo);

#if (ENABLE_UART_INIT)
DRVSYS_EX void console_init(void);
#endif

//*****************************************************************************

#undef DRVSYS_EX
#endif // _DRVSYS_H_

