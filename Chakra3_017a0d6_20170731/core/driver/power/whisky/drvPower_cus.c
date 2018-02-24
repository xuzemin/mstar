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

    MDrv_WriteRegBit(0x102300+0x40, DISABLE, BIT4); //0: VBUS On.
    MsOS_DelayTask(10);

    //improve the efficiency of USB access MIU when system is busy
    MDrv_WriteRegBit(0x102300+0x81, ENABLE, 0xF);

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

//others move to drvPower_std.c
