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
///@file drvsys.h
///@brief System functions: Initialize, interrupt
///@author MStarSemi Inc.
///
///////////////////////////////////////////////////////////////////////////////

#define  _DRV_SYS_C_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Board.h"
#include "sysinfo.h"
#include "hwreg.h"
#include "drvGPIO.h"
#include "drvUartDebug.h"
#include "MsTypes.h"
#include "MsDevice.h"
#include "drvMMIO.h"
#include "drvBDMA.h"
#include "drvMIU.h"
#include "drvWDT.h"
#include "SysInit.h"
#include "drvGlobal.h"
#include "drvISR.h"
#include "drvIIC.h"
#include "drvGPIO.h"
#include "Board.h"
#include "debug.h"
#include "drvUART.h"
#include "drvPM.h"
#include "msIR.h"
#include "Panel.h"
#include "MApp_SaveData.h"
#include "MApp_GlobalFunction.h"
#ifdef ENABLE_MINI_DUMP
#include "msAPI_MSDCtrl.h"
#include "msAPI_FCtrl.h"
#include "imginfo.h"
#endif
#include "util_symbol.h"

#if defined(__aeon__)
#include "risc32_spr.h"
#endif

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
#include "msAPI_Timer.h"
#endif

#include "msAPI_MIU.h"


static U8 u8OrigWdtTimer = 0x0A;    //Default 10 sec

#define WAIT_WDT_DELAY 50000
/******************************************************************************/
/*                     Local Defines                                          */
/******************************************************************************/
#define PM_LOCK_SUPPORT             1   // 1: Enable 0: Disable
#if (PM_LOCK_SUPPORT == 1)
#include "drvSEM.h"
#endif

// set 1 to enable support for download image to dram and run from MSTV_Tool
#define DOWNLOAD_RUN_SERVER     0
#define DBG_SYS_PNT(x)   //x
#define PIU_UART0_BAUDRATE          38400
/******************************************************************************/
/*                     Global Variables                                       */
/******************************************************************************/

// memory map for pre-built libraries
//U32 u32SecbufAddr = ((SECBUF_START_MEMORY_TYPE & MIU1) ? (SECBUF_START_ADR | MIU_INTERVAL) : (SECBUF_START_ADR));
//U32 u32SecbufSize = SECBUF_START_LEN;

U32 u32OadbufMonitorAddr = NULL;
U32 u32OadbufMonitorSize = NULL;
U32 u32OadbufDownloadAddr = NULL;
U32 u32OadbufDownloadSize = NULL;

U32 u32SubtitleAddr = ((SUBTITLE_MEMORY_TYPE & MIU1) ? (SUBTITLE_ADR | MIU_INTERVAL) : (SUBTITLE_ADR));
U32 u32SubtitleSize = SUBTITIE_OFFSET;

//U8 u8Sec1KFilterNum  = 8;
//U8 u8Sec4KFilterNum  = 8;
//U8 u8RecordFilterNum = 16;

//U32 u32Sec1KFilterBufferSize = 0x600;   //1.5K
//U32 u32Sec4KFilterBufferSize = 0x4000;  //16 K
//U32 u32Sec4KEitFilterBufferSize = 0x4000; //16K for eit schedule

//U32 u32CRCbufAddr = NULL;

unsigned long RIU_MAP;

#define u8ChipIdMajor   REG8(REG_CHIP_ID_MAJOR)
#define u8ChipIdMinor   REG8(REG_CHIP_ID_MINOR)
#define u8ChipVer       REG8(REG_CHIP_VERSION)
#define u8ChipRev       REG8(REG_CHIP_REVISION)

/******************************************************************************/
#include "SysInit_Common.c"  //include common file for all chip

/******************************************************************************/
void MDrv_Sys_InitUartForXtalClk( char cOutputChar )
{
    UNUSED(cOutputChar);
    MDrv_WriteRegBit(0x1E03, ENABLE, BIT2);          // enable UART RX
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MDrv_Sys_Get_BinInfo()
/// @brief \b Function \b Description : Get Specific Bin information
/// @param <IN>        \b None        :
/// @param <OUT>       \b pBinInfo    : Get Bin Information
/// @param <RET>       \b BOOLEAN     : Success or Fail
/// @param <GLOBAL>    \b None        :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Sys_Get_BinInfo(BININFO *pBinInfo, BOOLEAN *pbResult)
{
    BININFO NewBinInfo;

    // Added by coverity_0505
    memset(&NewBinInfo, 0, sizeof(BININFO));

    NewBinInfo.B_ID = pBinInfo->B_ID;
    *pbResult = Get_BinInfo(&NewBinInfo);
    pBinInfo->B_FAddr = NewBinInfo.B_FAddr;
    pBinInfo->B_Len   = NewBinInfo.B_Len;
    pBinInfo->B_IsComp = NewBinInfo.B_IsComp;
}

/******************************************************************************/
/// DO NOT MODIFY THIS FUNCTION, IT IS VERY DANGEROUS! (called by vectors.S)
/******************************************************************************/

#define STACK_SIZE      16384

//---------------------------------------------------------
//---------------------------------------------------------
void console_init(void)
{
    //bit 12 UART Enable, bit 11 UART RX Enable
    *(volatile MS_U32*)(0xA0000000+(0x0709*4)) |= 0x0800;

    // Clear UART_SEL
    *(volatile MS_U32*)(0xA0200000+(0x0F53*4)) = 0xFFFF;
    *(volatile MS_U32*)(0xA0200000+(0x0F54*4)) = 0x000F;

    //enable reg_uart_rx_enable;
    *(volatile MS_U32*)(0xA0200000+(0x0F01*4)) |= (1<<10);

    {
        MDrv_UART_Init(E_UART_AEON_R2, 115200);
        mdrv_uart_connect(E_UART_PORT0,E_UART_AEON_R2);
    }

  #if ENABLE_UART2
    {
        mdrv_uart_connect(E_UART_PORT2,E_UART_PIU_UART1);
    }
 #endif
}

void MDrv_Timer_Init(void) // Now support mode 1
{
    gTimerCount0 = 0;
    gTimerDownCount0 = 0;
    gTimerDownCount1 = 0;
    gu8100msTH = 0;
    g_u16ElapsedTimeSecond = 0;
}

extern unsigned char MDrv_IRQ_Init(void);
extern U32 __heap;
extern U32 __heap_end;

#ifdef __aeon__
void mhal_interrupt_unmask(MHAL_INTERRUPT_TYPE intr_num);
#endif


extern void MDrv_Timer_ISR_Register(void);
extern void MDrv_Timer_Setting_Register(void);
void start(void)
{
    U32 u32MiuProtectAlign;
    U32 u32Start;
    U32 u32End;
    U32 u32MiuProtectAddr_Start, u32MiuProtectAddr_End;

    // Added by coverity_0210
    //U8 zero_array[16] = {0};
    U32 u32Tmp;
    extern U8  _readonly_start[];
    extern U8  _readonly_end[];

    //extern void uart_init(U32 aeon_clock, U32 uart_clock);    //T3 FPGA test
    extern int  main(void);
    extern void MDrv_Pad_Init(void);
    extern void MDrv_ISR_Init(void);
    extern void mhal_stack_init(void *stack);

    char *stack;
    // Setup stack

    stack = (char *)malloc(STACK_SIZE);
    if (stack)
    {
        stack += STACK_SIZE;
        mhal_stack_init(stack);
    }
    else
    {
        ASSERT(0);
    }

#if (!BLOADER)
    MDrv_WDT_Init(E_WDT_DBGLV_NONE);
#endif

    MDrv_MMIO_GetBASE((MS_U32 *) &RIU_MAP, &u32Tmp, MS_MODULE_PM);

#if (PM_LOCK_SUPPORT == 1)
    MDrv_SEM_Init();
#endif

    MDrv_MIU_SetIOMapBase();

/*
    MDrv_MIU_ProtectAlign(&pageshift);
    u32Start = MsOS_VA2PA((U32)_readonly_start);
    u32End = MsOS_VA2PA((U32)_readonly_end);
    MDrv_MIU_Protect(0, zero_array, ALIGN(u32Start + ((1<<pageshift) - 1), pageshift), ALIGN(u32End, pageshift), ENABLE);
*/

    Util_InitSymbolTBL();

    console_init();

    MDrv_Pad_Init();

    mdrv_gpio_init();

    //RIU[0x101EA6] = 0x0001;
    //RIU[0x101E02] |= BIT10;
    //RIU[0x0e12] &= ~BIT12;

    // Show hello message
    printf(ANSI_COLOR_YELLOW);
    printf("\nHello Melody:%lx %s %s\n",RIU_MAP,__DATE__, __TIME__);
    printf("%s\n",__DATE__);
    printf("%s\n\n",__TIME__);
    printf(ANSI_COLOR_RESET);

    // Check boot time
#if 0//(ENABLE_AUTOTEST || ENABLE_BOOTTIME)
    {
        //for auto test recording booting time from Sboot to Ck2
        U32 PiuTick = MDrv_Read2Byte(0x3048);
        PiuTick |= (MDrv_Read2Byte(0x304a) << 16);
        U32 PiuTime = ((float)PiuTick / 12000000ul)*1000 ;  //ms
        PRINT_AUTOTEST_TIME("start sysinit", PiuTime);
        INIT_AUTOTEST_CHECKPT(PiuTime);
    }
#endif

    MDrv_SysInit_CheckSbootUseTime();


    {
        BOOL bRtn = FALSE;

        #define PROTECT_BEON_FULL_RANGE   1

      #if(PROTECT_BEON_FULL_RANGE)
        static U8 au8MiuProtectIds[16] = {MIU_CLIENT_R2M_W, MIU_CLIENT_BDMA_RW, MIU_CLIENT_USB_UHC0_RW, MIU_CLIENT_USB_UHC1_RW, MIU_CLIENT_USB_UHC2_RW,0};
      #else
       U8 au8MiuProtectIds[16] = {0};
      #endif

      #if(PROTECT_BEON_FULL_RANGE)
        u32Start = BEON_MEM_ADR;
        u32End = BEON_MEM_ADR + BEON_MEM_LEN;
      #else
        u32Start = MsOS_VA2PA((U32)_readonly_start);
        u32End = MsOS_VA2PA((U32)_readonly_end);
      #endif

        MDrv_MIU_ProtectAlign(&u32MiuProtectAlign);

        u32MiuProtectAddr_Start = ALIGN(u32Start + ((1<<u32MiuProtectAlign) - 1), u32MiuProtectAlign);
        u32MiuProtectAddr_End = ALIGN(u32End, u32MiuProtectAlign);

        printf("  _readonly_start=0x%X, _readonly_end=0x%X\n", _readonly_start, _readonly_end);
        //printf("MIU protect align=%X\n", 1ul << pageshift);
        printf("MIU protect align=0x%X, 0x%X\n", u32MiuProtectAlign, 1ul << u32MiuProtectAlign);
        printf("Beon protect start=%X, end=%X\n", u32MiuProtectAddr_Start, u32MiuProtectAddr_End );

        //MDrv_MIU_Protect(0, zero_array, ALIGN(u32Start + ((1<<pageshift) - 1), pageshift), ALIGN(u32End, pageshift), ENABLE);
        bRtn = MDrv_MIU_Protect(0, au8MiuProtectIds, u32MiuProtectAddr_Start, u32MiuProtectAddr_End, ENABLE);
        printf("MDrv_MIU_Protect rtn %u\n", bRtn );


        // mbox
      #if 0//def HDCP_MBX_BUFFER_ADR
      {
        // use 'static' to force 16 ID set to 0
        static  U8 au8MiuProtectIds_hk_spu_mbx[16] =  {MIU_CLIENT_R2M_W,MIU_CLIENT_R2M_R , MIU_CLIENT_SECURE_R2_RW, MIU_CLIENT_AESDMA_RW ,0};

        u32Start = HDCP_MBX_BUFFER_ADR;
        u32End = HDCP_MBX_BUFFER_ADR + HDCP_MBX_BUFFER_LEN;
        MDrv_MIU_ProtectAlign(&u32MiuProtectAlign);

        u32MiuProtectAddr_Start = ALIGN(u32Start + ((1<<u32MiuProtectAlign) - 1), u32MiuProtectAlign);
        u32MiuProtectAddr_End = ALIGN(u32End, u32MiuProtectAlign);

        bRtn = MDrv_MIU_Protect(1, au8MiuProtectIds_hk_spu_mbx, u32MiuProtectAddr_Start, u32MiuProtectAddr_End, ENABLE);
        printf("MDrv_MIU_Protect rtn %u\n", bRtn );
      }
      #endif

        // security r2
      #if 0//def SECURITY_R2_ADR
      {
        // use 'static' to force 16 ID set to 0
        static U8 au8MiuProtectIds_security[16] = {MIU_CLIENT_R2M_W,MIU_CLIENT_R2M_R , MIU_CLIENT_SECURE_R2_RW , MIU_CLIENT_AESDMA_RW,0};
        u32Start = SECURITY_R2_ADR;
        u32End = SECURITY_R2_ADR + SECURITY_R2_LEN;
        MDrv_MIU_ProtectAlign(&u32MiuProtectAlign);

        u32MiuProtectAddr_Start = ALIGN(u32Start + ((1<<u32MiuProtectAlign) - 1), u32MiuProtectAlign);
        u32MiuProtectAddr_End = ALIGN(u32End, u32MiuProtectAlign);

        bRtn = MDrv_MIU_Protect(2, au8MiuProtectIds_security, u32MiuProtectAddr_Start, u32MiuProtectAddr_End, ENABLE);
        printf("MDrv_MIU_Protect rtn %u\n", bRtn );
      }
      #endif
    }


    static PM_RtcParam PmRtcParam =
    {
        .u8PmRtcIndex = 0,
        .u32RtcCtrlWord = 12000000ul,
        .u32RtcSetMatchCounter = 0,
        .u32RtcGetMatchCounter = 0,
        .u32RtcSetCounter = 0,
        .u32RtcGetCounter = 0
    };

    MDrv_PM_RtcInit((PM_RtcParam*)_VA2PA((MS_U32)&PmRtcParam));


    //printf("heap => %x, => %x \n",&__heap, &__heap_end);
    if ((&__heap_end) <= (&__heap))
    {
        printf("## ERROR!! MMAP lyout for CPU code is not enough!!!\n");
    }
    else if (((U32)&__heap_end - (U32)&__heap) < 0x4B000)
    {
        U32 u32FreeSize;
        u32FreeSize = (U32)&__heap_end - (U32)&__heap;
        printf("## heap size is %dK under 300K!!\n", (u32FreeSize>>10));
    }

    MDrv_IIC_Init();

    //if ( ENABLE_POWER_GOOD_DETECT )
    //{
    //    MDrv_WriteRegBit(0x1EE4, ENABLE, 0x40);
    //    MDrv_WriteRegBit(0x1EE4, ENABLE, 0x1F);
    //}

#if DOWNLOAD_RUN_SERVER
    {
        //mhal_interrupt_disable();
        MsOS_CPU_DisableInterrupt();
        putchar( 'F' );
        putchar( 'W' );
        while (1)
        {
            MDrv_Sys_ClearWatchDog();
        }
    }
#else
    {
        if (WATCH_DOG == ENABLE)
        {
            MDrv_Sys_ClearWatchDog();
        }
        else
        {
            MDrv_Sys_DisableWatchDog();
        }
    }
#endif

    {
        extern void ProcessSysTrap( MHAL_SavedRegisters *pHalReg, U32 vector );
        extern void ProcessEx0Isr( MHAL_SavedRegisters *pHalReg, U32 vector );
        extern void ProcessEx1Isr( MHAL_SavedRegisters *pHalReg, U32 vector );

        //mhal_exception_attach( E_EXCEPTION_TRAP, ProcessSysTrap, E_EXCEPTION_TRAP );
        MsOS_CPU_AttachException( E_EXCEPTION_TRAP, ProcessSysTrap, E_EXCEPTION_TRAP );

        MsOS_Init();
        MDrv_ISR_Init();
    }

    MDrv_Timer_ISR_Register();
    MDrv_Timer_Init();
    MsOS_CPU_EnableInterrupt();

#ifdef __aeon__
    mhal_interrupt_unmask((MHAL_INTERRUPT_TYPE)3);
#endif

    CHECK_MIU_PROTECT_LOG();

    // jump to main() should never return
    main();

    //while(1);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function \b Name: MDrv_Sys_Set_CIDInfo()
/// @brief \b Function \b Description : To Set Customer Info
/// @param <IN>        \b pCIDInfo    : Input the CID Info
/// @param <OUT>       \b None        :
/// @param <GLOBAL>    \b None        :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Sys_Set_CIDInfo(U8 *pCIDInfo)
{
    MDrv_WriteByte(0x1033D0,pCIDInfo[0]);
    MDrv_WriteByte(0x1033D1,pCIDInfo[1]);
    MDrv_WriteByte(0x1033D2,pCIDInfo[2]);
    MDrv_WriteByte(0x1033D3,pCIDInfo[3]);

}

/******************************************************************************/
/// Copy variable from DRAM space to XDATA space
/// @param pAddr \b IN XDATA pointer
/// @param u32MiuAddr \b IN MIU address
/// @param u16Length \b IN size to copy
/******************************************************************************/

void MDrv_Sys_CopyMIU2VAR(U32 srcaddr, void *dstaddr, U16 len)
{
    memcpy(dstaddr, (U8 *)srcaddr, len);
}

// for backward compatible, do not use!
#undef MDrv_MIU_SDRAM2VARCopy
void MDrv_MIU_SDRAM2VARCopy(U32 srcaddr, void *dstaddr, U16 len)
{
    memcpy(dstaddr, (U8 *)srcaddr, len);
}

/******************************************************************************/
/// Copy variable from XDATA space to DRAM space
/// @param pAddr \b IN XDATA pointer
/// @param u32MiuAddr \b IN MIU address
/// @param u16Length \b IN size to copy
/******************************************************************************/

void MDrv_Sys_CopyVAR2MIU(void *srcaddr, U32 dstaddr, U16 len)
{
    memcpy((U8 *)dstaddr, srcaddr, len);
}

// for backward compatible, do not use!
#undef MDrv_MIU_VAR2SDRAMCopy
void MDrv_MIU_VAR2SDRAMCopy(void *srcaddr, U32 dstaddr, U16 len)
{
    memcpy((U8 *)dstaddr, srcaddr, len);
}

/******************************************************************************/
//
//   128T +------+          +------+ 128T
//     |  |      |          |      |  |
//     +--+ 8051 |          | Aeon +--+
//        |      |          |      |
//        +--+---+          +---+--+
//       +---+----+        +----+---+
//       |        |        |        |
//   boot_aeon   sw_rst   sw_rst  boot_8051
//
// When boot from 8051
//      reboot:   use reg_reset_cpu0 with password
//      run aeon: set reg_sw_reset_cpu1 to 1
// When boot from Aeon
//      reboot:   use reg_reset_cpu1 with password
//      run 8051: set reg_sw_reset_cpu0 to 1
/******************************************************************************/
void MDrv_Sys_WholeChipReset( void )
{
  #if 1
    MDrv_WriteByte( RIUBASE_PM_MISC+0x5C, 0xFF );
    MDrv_Write4Byte(0xEA0, 0x51685168);
    MDrv_WriteRegBit(RIUBASE_PM_MISC+0x52, 1, BIT7);
    MDrv_WriteRegBit(RIUBASE_PM_MISC+0x52, 1, BIT6);
    MDrv_WriteByte( RIUBASE_PM_MISC+0x5C, 0x79 );
  #else
    MDrv_WDT_SetTimer(0, 1);
  #endif

    //while(1); //Fix coverity for infinite loop
    MsOS_DelayTask(WAIT_WDT_DELAY);
}

/******************************************************************************/
///Reset 8051 to reboot
/******************************************************************************/
void MDrv_Sys_Reboot( void )
{
  #if 1
    MDrv_Write2Byte( REG_RESET_CPU_8051, 0x029F );
    MDrv_Write2Byte( REG_RESET_CPU_8051, 0x829F ); // can't ignore second 0x9F
  #else
    MDrv_WDT_SetTimer(0, 1);
  #endif
    //while(1);
}


void MDrv_Sys_SetWatchDogTimer( U8 sec )
{
     if( sec == 0 )
     {
        u8OrigWdtTimer = 1;
     }
     else
     {
        u8OrigWdtTimer = sec;
     }
}

void  MDrv_Sys_EnableWatchDog(void)
{
#if (WATCH_DOG == ENABLE )
    MDrv_Write4Byte(WDT_TIMER_0, ( MDrv_Sys_WatchDogCycles( u8OrigWdtTimer ) ));
#endif
}

//----------------------------------------------------------------
void MDrv_Sys_DisableWatchDog( void )
{
    MDrv_Write4Byte( WDT_TIMER_0, 0x0000UL );
}


