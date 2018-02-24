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
#include <stdio.h>

#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "hwreg.h"
#include "sysinfo.h"
#include "debug.h"
#include "drvUartDebug.h"
#include "drvISR.h"
//#include "drvTSP.h"
#include "drvCPU.h"
#include "SysInit.h"
#include "Analog_Reg.h"
#include "drvpower_if.h"
#include "GPIO.h"
#include "drvIIC.h"
#include "msIR.h"
#include "drvAUDIO.h"
#include "drvGlobal.h"
#include "msKeypad.h"
#include "apiXC_Adc.h"
#include "apiPNL.h"
#include "drvIR.h"
#include "drvUSB.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_SaveData.h"
#include "msAPI_DrvInit.h"
#include "msAPI_Power.h"
#include "msAPI_Timer.h"
#include "MApp_Sleep.h"
#include "msAPI_IR.h"
#include "msAPI_MIU.h"
#include "msAPI_Flash.h"
#include "MApp_InputSource.h"
#include "MApp_Sleep.h"

extern void MDrv_Power_SetMode(U8 u8Mode);

#define DBGNUM(x, y)            //{putchar(x);putchar(y);putchar('\n');}

#define __boot_from_spi __attribute__ ((__section__ (".boot_from_spi_start.text")))

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
#ifndef MSOS_TYPE_LINUX
//------------------------------------------------------------------------------
/// Execute power on initialization.
/// @param
/// @return TRUE- Success.
///         FALSE - Failure.
//------------------------------------------------------------------------------
void USB_Init_Configure(void)
{
    U32 ii;
    printf(" USB_Init_Configure port 0\r\n");
    //MDrv_WriteByteMask(0x102508, 0x0,0x0c); //Enable current source in DVI

    //open port 0  // USB0_regbase: 0x103a80
    MDrv_WriteByte(0x100700, 0x0A); // Disable MAC initial suspend, Reset UHC
    MDrv_WriteByte(0x100700, 0x28); // Release UHC reset, enable UHC XIU function

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
    MsOS_DelayTask(10);

    //improve the efficiency of USB access MIU when system is busy
    MDrv_WriteRegBit(0x102400+0x81, ENABLE, 0xF);

    //Disable battery charge mode
    //MDrv_WriteRegBit(0x123600+0x0C, DISABLE, 0x40);// [6]= reg_into_host_bc_sw_tri
    //MDrv_WriteRegBit(0x123600+0x03, DISABLE, 0x40);// [6]= reg_host_bc_en
    //MDrv_WriteRegBit(0x103A80+0x01, DISABLE, 0x40);//IREF_PDN=1¡¦b1. (utmi+0x01[6] )

    //Enable ECO for monkey test 2012/12/05
    MDrv_WriteRegBit(0x103A80+0x10, ENABLE, 0x40);

    MDrv_USB_EnterPowerSaveMode();
    //end
    
    printf("USB_Init_Configure port 0 done...\n");
    
    printf(" USB_Init_Configure port 1\r\n");
    //MDrv_WriteByteMask(0x102508, 0x0,0x0c); //Enable current source in DVI

    //open port 1  // USB0_regbase: 0x103a80
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
    MsOS_DelayTask(10);

    //improve the efficiency of USB access MIU when system is busy
    MDrv_WriteRegBit(0x100D00+0x81, ENABLE, 0xF);

    //Disable battery charge mode
    //MDrv_WriteRegBit(0x123600+0x0C, DISABLE, 0x40);// [6]= reg_into_host_bc_sw_tri
    //MDrv_WriteRegBit(0x123600+0x03, DISABLE, 0x40);// [6]= reg_host_bc_en
    //MDrv_WriteRegBit(0x103A80+0x01, DISABLE, 0x40);//IREF_PDN=1¡¦b1. (utmi+0x01[6] )

    //Enable ECO for monkey test 2012/12/05
    MDrv_WriteRegBit(0x103A00+0x10, ENABLE, 0x40);

    MDrv_USB_EnterPowerSaveMode_Port2();
    //end
    
    printf("USB_Init_Configure port 1 done...\n");
}
#endif

