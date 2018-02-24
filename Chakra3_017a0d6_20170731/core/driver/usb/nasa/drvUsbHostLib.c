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
//Copyright (C) 2008 MStar  All Rights Reserved.

/*! \file  drvUsbHostLib.c
    \brief  Platform function for USB Host.


 \n\b History:
    \n\b Date: 2008/8/27
    \n\b Author: Colin Tsai
    \n\b Reason: Create
    \n
*/
//=============================================================================
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "datatype.h"
#include "debug.h"  // for PLATFORM define
#include "sysinfo.h"
#include "drvGlobal.h"

#include "drvUSB.h"
#include "drvUsbHostConfig.h"

extern void MsOS_DelayTask(U32);
extern U8 drvUSBHost_PTP_Initial(void);
extern U8 drvUSBHost_PTP_Initial_Port2(void);
extern U8 drvUSBHost_HID_Initial(void);
extern U8 drvUSBHost_HID_Initial_Port2(void);

/////////////////////////////////////////////////////////////////////////////
//  For USB Port 0
/////////////////////////////////////////////////////////////////////////////
extern void UsbPort0UTMIInitial(void);

    #ifdef UHC_BASE
    U32    gUHC_BASE = UHC_BASE;
    #else
    U32     gUHC_BASE = 0;
    #endif

    #ifdef UTMIBaseAddr
    U32     gUTMI_BASE = UTMIBaseAddr;
    #else
    U32     gUTMI_BASE = 0;
    #endif

    #ifdef USBCBase
    U32     gUSBC_BASE = USBCBase;
    #else
    U32     gUSBC_BASE = 0;
    #endif

void drvUSBHost_TurnOffPowerDownMode(void)
{
#if (ENABLE_USB) && defined(USB_POWER_SAVING_MODE)
#ifdef NEW_USB_POWER_SAVING_MODE
    MDrv_WriteRegBit(0x103A80, DISABLE, (BIT1|BIT6|BIT7));
	MDrv_WriteRegBit(0x103A80+0x01, DISABLE, (BIT2|BIT3|BIT6));
#else
    U32 ii;

    printf("USB port 0 exit power save ");
    MDrv_WriteByte(0x100700, 0x0A); // Disable MAC initial suspend, Reset UHC
    MDrv_WriteByte(0x100700, 0x28); // Release UHC reset, enable UHC XIU function

    MDrv_WriteRegBit(0x103A80+0x02, ENABLE, BIT2);  // Set bit <2> (CLK12_SEL) to 1 for low voltage crystal clock

    MDrv_WriteByte(0x103A80, 0x01); // Turn all (including hs_current) use override mode
    MDrv_WriteByte(0x103A80+0x01, 0x00);

    MDrv_WriteRegBit(0x103A80+0x3C, ENABLE, 0x01);  // set CA_START as 1
    MsOS_DelayTask(10);
    MDrv_WriteRegBit(0x103A80+0x3C, DISABLE, 0x01);  // release CA_START

    ii=0;
    while( (MDrv_ReadByte(0x103A80+0x3C) & 0x02) == 0)  // polling bit <1> (CA_END)
    {
        if (ii++>10000)
        {
            printf("Poll USB port0 CA_END timeout\n");
            break;
        }
    }

    MDrv_WriteByteMask(0x100700+0x02, BIT0, (BIT0|BIT1));  //UHC select enable

    MDrv_WriteRegBit(0x102400+0x40, DISABLE, BIT4); //0: VBUS On.
    MsOS_DelayTask(1);
    printf("done\n");
#endif
#endif
}

void MDrv_USB_ExitPowerSaveMode(void)
{
    drvUSBHost_TurnOffPowerDownMode();
}

void drvUSBHost_TurnOnPowerDownMode(void)
{
#if (ENABLE_USB) && defined(USB_POWER_SAVING_MODE)
#ifdef NEW_USB_POWER_SAVING_MODE
    MDrv_WriteRegBit(0x103A80, ENABLE, (BIT1|BIT6|BIT7));
	MDrv_WriteRegBit(0x103A80+0x01, ENABLE, (BIT2|BIT3|BIT6));
#else
    printf("USB port 0 enter power save ");

    MsOS_DelayTask(2);

    MDrv_WriteByte(0x103A80+0x02, 0x84); // bit <15>: reg_hs_rterm_pdn, bit <7>: reg_bond_sel
    MDrv_WriteByte(0x103A80+0x03, 0x90);
    MDrv_WriteByte(0x103A80, 0xC3); // power down override mode enable
    MDrv_WriteByte(0x103A80+0x01, 0x6D); // turn off all except fl_xcvr_pdn, pll_pdn(bit <9>), reg_pdn(bit<15>) and ref_pdn(bit <2>)

//    MDrv_WriteByte(0x100700, 0x00); // Enable initial suspend
//    MDrv_WriteByte(0x100700+0x02, 0x00); // UHC select disable
    printf("done\n");
#endif
#endif
}

void MDrv_USB_EnterPowerSaveMode(void)
{
    drvUSBHost_TurnOnPowerDownMode();
}

void drvUSBHost_UTMIInitial(void)
{
#if (ENABLE_USB)
    UsbPort0UTMIInitial();
#endif
}

BOOLEAN drvUSBHost_isPort0Enable(void)
{
#if (ENABLE_USB)
    return TRUE;
#else
    return FALSE;
#endif
}

/////////////////////////////////////////////////////////////////////////////
// For USB Port 2
/////////////////////////////////////////////////////////////////////////////
extern void UsbPort2UTMIInitial(void);

    #ifdef UHC2_BASE
    U32     gUHC2_BASE = UHC2_BASE;
    #else
    U32     gUHC2_BASE = 0;
    #endif

    #ifdef UTMIBaseAddr2
    U32     gUTMI2_BASE= UTMIBaseAddr2;
    #else
    U32     gUTMI2_BASE= 0;
    #endif

    #ifdef USBCBase2
    U32     gUSBC2_BASE = USBCBase2;
    #else
    U32     gUSBC2_BASE = 0;
    #endif

void drvUSBHost_TurnOffPowerDownMode_Port2(void)
{
#if (ENABLE_USB_2) && defined(USB_POWER_SAVING_MODE)
#ifdef NEW_USB_POWER_SAVING_MODE
    MDrv_WriteRegBit(0x103A00, DISABLE, (BIT1|BIT6|BIT7));
	MDrv_WriteRegBit(0x103A00+0x01, DISABLE, (BIT2|BIT3|BIT6));
#else
    U32 ii;

    printf("USB port 1 exit power save ");

    MDrv_WriteByte( 0x100780, 0x0a);          // Disable MAC initial suspend, Reset UHC
    MDrv_WriteByte( 0x100780, 0x28);          // Release UHC reset, enable UHC and OTG XIU function

    MDrv_WriteRegBit(0x103A00+0x22, ENABLE, BIT7|BIT6|BIT5);  // Set PLL_TEST[23:21] for enable 480MHz clock
    MDrv_WriteRegBit(0x103A00+0x20, ENABLE, BIT1|BIT0);  // Set PLL_TEST[1] for PLL multiplier 20X, PLL_TEST[0] for low voltage crystal clock
    MDrv_WriteRegBit(0x103A00+0x02, ENABLE, BIT2);  // Set bit <2> (CLK12_SEL) to 1 for low voltage crystal clock
    MDrv_Write2Byte((0x103A00+0x08), 0x0000); // Disable force_pll_on // Enable band-gap current
    MDrv_Write2Byte(0x103A00 , 0x6bc3); // reg_pdn: bit<15>, bit <2> ref_pdn,Turn on reference voltage and regulator
    MsOS_DelayTask(1);         // delay 1ms

    MDrv_Write2Byte(0x103A00, 0x69c3); // Turn on UPLL, reg_pdn: bit<9>
    MsOS_DelayTask(2);          // delay 2ms

    MDrv_Write2Byte(0x103A00, 0x0001); // Turn all (including hs_current) use override mode

    MDrv_WriteByte(0x100780, 0x0A); // Disable MAC initial suspend, Reset UHC
    MDrv_WriteByte(0x100780, 0x28); // Release UHC reset, enable UHC XIU function

    MDrv_WriteRegBit(0x103A00+0x3C, ENABLE, 0x01);  // set CA_START as 1
    MsOS_DelayTask(10);
    MDrv_WriteRegBit(0x103A00+0x3C, DISABLE, 0x01);  // release CA_START

    ii=0;
    while( (MDrv_ReadByte(0x103A00+0x3C) & 0x02) == 0)  // polling bit <1> (CA_END)
    {
        if (ii++>10000)
        {
            printf("Poll USB port1 CA_END timeout\n");
            break;
        }
    }

    MDrv_WriteByteMask(0x100780+0x02, BIT0, (BIT0|BIT1));  //UHC select enable

    MDrv_WriteRegBit(0x100D00+0x40, DISABLE, BIT4); //0: VBUS On.
    MsOS_DelayTask(1);
    printf("done\n");
#endif
#endif
}

void MDrv_USB_ExitPowerSaveMode_Port2(void)
{
    drvUSBHost_TurnOffPowerDownMode_Port2();
}

void drvUSBHost_TurnOnPowerDownMode_Port2(void)
{
#if (ENABLE_USB_2) && defined(USB_POWER_SAVING_MODE)
#ifdef NEW_USB_POWER_SAVING_MODE
    MDrv_WriteRegBit(0x103A00, ENABLE, (BIT1|BIT6|BIT7));
	MDrv_WriteRegBit(0x103A00+0x01, ENABLE, (BIT2|BIT3|BIT6));
#else
    printf("USB port 1 enter power save ");

    MsOS_DelayTask(2);

    MDrv_WriteRegBit(0x103A00+0x08, ENABLE, BIT7); // power down band gap current
    MDrv_WriteByte(0x103A00+0x02, 0x80); // bit <15>: reg_hs_rterm_pdn, bit <7>: reg_bond_sel
    MDrv_WriteByte(0x103A00+0x03, 0x90);
    MDrv_WriteByte(0x103A00, 0xC7); // power down override mode enable
    MDrv_WriteByte(0x103A00+0x01, 0xEF); // turn off all except fl_xcvr_pdn

    MDrv_WriteByte(0x100780, 0x00); // Enable initial suspend
    MDrv_WriteByte(0x100780+0x02, 0x00); // UHC select disable
    printf("done\n");
#endif
#endif
}

void MDrv_USB_EnterPowerSaveMode_Port2(void)
{
    drvUSBHost_TurnOnPowerDownMode_Port2();
}

void drvUSBHost_UTMIInitial_Port2(void)
{
#if (ENABLE_USB_2)
    UsbPort2UTMIInitial();
#endif
}

BOOLEAN drvUSBHost_isPort2Enable(void)
{
#if (ENABLE_USB_2)
    return TRUE;
#else
    return FALSE;
#endif
}

/////////////////////////////////////////////////////////////////////////////
// For Both Port 0 and Port 2
/////////////////////////////////////////////////////////////////////////////
#ifdef USB_POWER_SAVING_MODE
U8 gUsbDeviceState=POWER_SAVING;
#else
U8 gUsbDeviceState=NO_DEVICE;
#endif

#ifdef USB_POWER_SAVING_MODE
U8 gUsbDeviceState_Port2 = POWER_SAVING;
#else
U8 gUsbDeviceState_Port2=NO_DEVICE;
#endif

void UsbTurnOffPowerDownMode(void)
{
    drvUSBHost_TurnOffPowerDownMode();
    drvUSBHost_TurnOffPowerDownMode_Port2();
}

void UsbTurnOnPowerDownMode(void)
{
    drvUSBHost_TurnOnPowerDownMode();
    drvUSBHost_TurnOnPowerDownMode_Port2();
}

BOOLEAN drvUSBHost_isPowerSaveModeEnable(void)
{
#ifdef USB_POWER_SAVING_MODE
    return TRUE;
#else
    return FALSE;
#endif
}

U8 drvUSBHost_PTP_Init(U8 u8UsbPort)
{
    if (u8UsbPort == USB_PORT_0)
    {
#if defined(ENABLE_PTP) && defined(USB_PTP_ENABLE)
        return drvUSBHost_PTP_Initial();
#endif
    }

    if (u8UsbPort == USB_PORT_2)
    {
#if defined(ENABLE_PTP) && defined(USB2_PTP_ENABLE)
        return drvUSBHost_PTP_Initial_Port2();
#endif
    }

    return 1;   //PTP_RESP_FAIL
}

void XBYTE_OR(U32 Addr, U8 offset, U8 val)
{
    U16 temp;

    if (offset & 1)
    {
        temp=*(U16 volatile   *)(Addr+(offset-1)*2);
        *(U16 volatile   *)(Addr+(offset-1)*2)=(((U16)val)<<8) | (temp );
    }
    else
    {
        temp=*(U16 volatile   *)(Addr+offset*2);
        *(U16 volatile   *)(Addr+offset*2)=(temp )|val;
     }
}

void XBYTE_AND(U32 Addr, U8 offset,U8 val)
{
    U16 temp;

    if (offset &1)
    {
        temp=*(U16 volatile   *)(Addr+(offset-1)*2);
        *(U16 volatile   *)(Addr+(offset-1)*2)=((((U16)val)<<8)|0xff) & (temp );
    }
    else
    {
        temp=*(U16 volatile   *)(Addr+offset*2);
        *(U16 volatile   *)(Addr+offset*2)=(temp & (0xff00|val) );

     }
}

void XBYTE_SET(U32 Addr, U8 offset,U8 val)
{
    U16 temp;

    if (offset &1)
    {
        temp=*(U16 volatile   *)(Addr+(offset-1)*2);
        *(U16 volatile   *)(Addr+(offset-1)*2)=((temp & 0x00ff) | (((U16)val)<<8));
    }
    else
    {
        temp=*(U16 volatile   *)(Addr+offset*2);
        *(U16 volatile   *)(Addr+offset*2)=((temp & 0xff00) |val );
     }
}

U8 XBYTE_READ(U32 Addr, U8 offset)
{
    U16 temp;
    U8  uRetVal = 0;

    if (offset &1)
    {
        temp=*(U16 volatile   *)(Addr+(offset-1)*2);
        uRetVal = (U8) (temp >> 8);
    }
    else
    {
        temp=*(U16 volatile   *)(Addr+offset*2);
        uRetVal = (U8) temp;
    }

    //printf("XBYTE_READ: Addr: %X, offset: %X, uRetVal: %X\n", Addr, offset, uRetVal);
    return uRetVal;
}

U8 drvUSBHost_HID_Init(U8 u8UsbPort)
{
   if (u8UsbPort == USB_PORT_0)
    {
#if (ENABLE_USB) && defined(USB_HID_ENABLE)
        return drvUSBHost_HID_Initial();
#endif
    }

    if (u8UsbPort == USB_PORT_2)
    {
#if  (ENABLE_USB_2) && defined(USB2_HID_ENABLE)
        return drvUSBHost_HID_Initial_Port2();
#endif
    }

    return 1;   //PTP_RESP_FAIL

}
BOOLEAN Support_HID(void)
{
#if defined(USB_HID_ENABLE)
    return TRUE;
#endif
    return FALSE;

}

U8 MDrv_USBGetPortEnableStatus(void)
{
    U8 uPortSts = 0;

#if (ENABLE_USB)
    uPortSts |= 1;
#endif

#if (ENABLE_USB_2)
    uPortSts |= 2;
#endif

    return uPortSts;
}

