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
// Description: Interrupt Service Routines
//
////////////////////////////////////////////////////////////////////////////////

#define _DRV_ISR_C_

#include <stdio.h>
#include <string.h>
#include "MsTypes.h"

#if defined(__aeon__)
#include "risc32_spr.h"
#endif

#include "sysinfo.h"
#include "drvCPU.h"
#include "sysinfo.h"

#include "hwreg.h"

#include "GPIO.h"
#include "drvpower_if.h"
#include "drvGlobal.h"
#include "drvUartDebug.h"

#include "msIR.h"
#include "msKeypad.h"
#include "drvISR.h"
#include "SysInit.h"
#include "util_minidump.h"
#include "MsOS.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"
#include "msAPI_Timer.h"

#if ENABLE_TTX
#include "msAPI_TTX.h"
#endif

#if DTV_COUNT_DOWN_TIMER_PATCH
extern U8 u8DTVCountDownTimer;
#endif

extern void mdrv_dvi_clock_70mhz_swpatch2(INPUT_SOURCE_TYPE_t enInputSourceType);

#ifdef ENABLE_MINI_DUMP
extern void ProcessWDTIsr(MHAL_SavedRegisters *pHalReg, U32 vector);
extern void ProcessMIUIsr(MHAL_SavedRegisters *pHalReg, U32 vector);
#endif

#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
static void ProcessCPU0toCPU2Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    MsOS_EnableInterrupt(E_INT_FIQ_8051_TO_BEON);
}

static void ProcessCPU1toCPU2Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

	MsOS_EnableInterrupt(E_INT_FIQ_AEON_TO_BEON);
}
#endif

#if (defined(__aeon__) && !defined(__AEONR2__))
static void ProcessCPU0toCPU1Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    MsOS_EnableInterrupt(E_INT_FIQ_8051_TO_AEON);
}

static void ProcessCPU2toCPU1Isr(MHAL_SavedRegisters *pHalReg, U32 vector)
{
    UNUSED(pHalReg);
    UNUSED(vector);

    MsOS_EnableInterrupt(E_INT_FIQ_BEON_TO_AEON);
}
#endif


void MDrv_ISR_Init(void)
{
#if defined(MIPS_CHAKRA) || defined(__AEONR2__)
    MsOS_AttachInterrupt(E_INT_FIQ_8051_TO_BEON, (InterruptCb)ProcessCPU0toCPU2Isr);
    MsOS_AttachInterrupt(E_INT_FIQ_AEON_TO_BEON, (InterruptCb)ProcessCPU1toCPU2Isr);
#endif

#if (defined(__aeon__) && !defined(__AEONR2__))
    MsOS_AttachInterrupt(E_INT_FIQ_8051_TO_AEON, (InterruptCb)ProcessCPU0toCPU1Isr);
    MsOS_AttachInterrupt(E_INT_FIQ_BEON_TO_AEON, (InterruptCb)ProcessCPU2toCPU1Isr);
#endif
#ifdef ENABLE_MINI_DUMP
    MsOS_AttachInterrupt(E_INT_FIQ_WDT, (InterruptCb)ProcessWDTIsr);
    MsOS_AttachInterrupt(E_INT_IRQ_MIU, (InterruptCb)ProcessMIUIsr);
#endif
}
extern MS_U32 gsystem_time_ms;

//------------------------------------------------------------------------------------
//extern void Timer_Setting_Register(void *ptCb);
extern void Timer_IRQ_Register(void *ptCb);

#ifndef MSOS_TYPE_LINUX
#if ENABLE_TTX
BOOLEAN bTTXInISR=FALSE;
#endif

#if 0 //@@debug (COMB_2D3D_SWITCH_PATCH)  //For FT unstable Htotal channel in Shanghai 20101013
extern WORD g_Comb1msCounter;
#endif


static void TimerISR(void)
{
    gTimerCount0++;
    gu8100msTH++;

    msAPI_Timer_1ms_ISR();


    // Use a threshold to check the 100 ms. If the threshold
    // is greater or equal than the 100 ms. Increase the 100 ms
    // counter.
    if (gu8100msTH >= 100)
    {
        g100msTimeCount++;
        gu8100msTH = 0;
    }

    if (gTimerCount0%1000==0)
    {
        gSystemTimeCount++;

        gSystemTimeCount_TCON++;

        #if DTV_COUNT_DOWN_TIMER_PATCH
        if((u8DTVCountDownTimer != 0xFF) && (u8DTVCountDownTimer > 0))
            u8DTVCountDownTimer--;
        #endif
    }

    //--------------------------------
    //down time counter:
    if ( gTimerDownCount0 > 0 )
        gTimerDownCount0--;

    if ( gTimerDownCount1 > 0 )
        gTimerDownCount1--;

#if (!BLOADER)
  #if 0 //@@debug (COMB_2D3D_SWITCH_PATCH)  //For FT unstable Htotal channel in Shanghai 20101013
    if(g_Comb1msCounter)
        g_Comb1msCounter--;
  #endif
#endif

#if (IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)
    if(g_ucIrRepeatTimer > 0)
        g_ucIrRepeatTimer--;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
    if (g_u8IrKonRepeatTimeout)
        g_u8IrKonRepeatTimeout--;
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_TOSHIBA_MODE||IR_MODE_SEL == IR_TYPE_SWDECODE_CH_MODE)
    if (g_wIRRepeatTimer > 1)
        g_wIRRepeatTimer--;
    if (g_wIRCycleTimer > 1)
        g_wIRCycleTimer--;
#elif(IR_MODE_SEL == IR_TYPE_SWDECODE_RCA_MODE)
       if(g_wIrRcaRemoteTimer > 0)
    {
           g_wIrRcaRemoteTimer--;
    }
       else
    {
        g_ucIrCodeBuf=IRKEY_DUMY;
    }

    if (g_u8IrKeyRepeatCounter>0)
        g_u8IrKeyRepeatCounter--;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_NEC_MODE)
    if(g_ucIrRepeatTimer > 0)
        g_ucIrRepeatTimer--;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_MITSUBISHI_MODE)
    if(g_ucIrRepeatTimer > 0)
        g_ucIrRepeatTimer--;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_PIONEER)
    if(g_u8IRDetectTimer < 0xFF)
        g_u8IRDetectTimer++;
    if(g_u8IRRepeatInvalid < 0xFF)
        g_u8IRRepeatInvalid++;
#endif

#if ((KEYPAD_TYPE_SEL != KEYPAD_TYPE_NONE) && (KEYPAD_USE_NEW_CHECK))
    if(g_ucKeyPadRepeatTimer < 0xFFFF)
        g_ucKeyPadRepeatTimer++;
#endif

    //-------------------------------
#if (ENABLE_UART2)
    if (g_Uart2CheckTick)
    {
        --g_Uart2CheckTick;
        if ( g_Uart2CheckTick == 0 )
        {
            g_bUart2Detected = FALSE;
            g_Uart2Command.Index = 0;
        }
    }
#endif // #if (ENABLE_UART2)

    //-------------------------------

    #if (!BLOADER)
    #if (ENABLE_MSTV_UART_DEBUG )
    if (g_Uart0CheckTick)
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            g_bUart0Detected = FALSE;
            g_UartCommand.Index = 0;
        }
    }
    #elif XMODEM_DWNLD_ENABLE //for xmodem
     if ( g_Uart0CheckTick )
    {
        --g_Uart0CheckTick;
        if ( g_Uart0CheckTick == 0 )
        {
            XModem_Rx_Timeout = TRUE;
        }
    }
    #endif
#endif // #if (!BLOADER)

    //-------------------------------

#if (ENABLE_UART1_INTERRUPT == ENABLE)
    #if(ENABLE_UART1_DEBUG)
    if (g_Uart1CheckTick)
    {
        --g_Uart1CheckTick;
        if ( g_Uart1CheckTick == 0 )
        {
            g_bUart1Detected = FALSE;
            g_ucUart1BufIndex = 0;
        }
    }
    #endif
#endif

    #if (!BLOADER)
    #if ENABLE_TTX
    {
        bTTXInISR=TRUE;

        msAPI_TTX_CollectPackets();

        bTTXInISR=FALSE;
    }
    #endif

    if(MApi_XC_HDMI_Func_Caps() & CAPS_DVI_ADJ_70M)
    {
#ifdef DVI_NEW_Patch
    // 20081226 - DVI+HDCP snow noise patch - start ...
        if(g_DVI70MhzPollingCounter)
        {
            g_DVI70MhzPollingCounter--;

            if(g_DVI70MhzPollingCounter == 0)
                mdrv_dvi_clock_70mhz_swpatch2(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
        }
    // 20081226 - DVI+HDCP snow noise patch - end ...
#endif
    }
    #endif
}

void MDrv_Timer_ISR_Register(void)
{
    MS_U32 check_timer_status;

    check_timer_status = MsOS_CreateTimer( (TimerCb) TimerISR,
                                                  0,
                                                  1,
                                                  TRUE,
                                                  "Check timer");
}
#endif

/**************************
System trap function
 vectors.s assumes that this function will never return
****************************/
extern void msAPI_ShowWarningMessage(BOOLEAN bShow, const char *warningMsg);
char g_strTrapFileLineName[256]={0};
void trapBackUpLocation(const char *filename, unsigned long line)
{
    memset(g_strTrapFileLineName, 0, sizeof(g_strTrapFileLineName));
    snprintf(g_strTrapFileLineName, sizeof(g_strTrapFileLineName), "System trap at %s :%u", filename, line);
}
void ProcessSysTrap(MHAL_SavedRegisters *pHalReg, U32 vector)
{
   printf("system trap");
   msAPI_ShowWarningMessage(TRUE, g_strTrapFileLineName);

#ifdef ENABLE_MINI_DUMP
   MDrv_Sys_MiniDump(pHalReg, vector, MINI_DUMP_FOR_SYS_TRAP);
#else
   UNUSED(pHalReg);
   UNUSED(vector);
#endif

   MDrv_Sys_DisableWatchDog();
   MDrv_Sys_StopCpu(1);
}
