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
///////////////////////////////////////////////////////////////////////////////////////////////////
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
#include "MApp_Audio.h"
#include "drvGPIO.h"

#if (NO_SIGNAL_AUTO_SHUTDOWN )
#include "MApp_NoSignal_AutoSleep.h"
#endif

#if(PM_RUNS_IN == PM_RUNS_IN_FLASH)||(PM_RUNS_IN == PM_RUNS_IN_CACHE)
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
#include "MApp_IR.h"

#include "Dlp_Optical.h" //gchen @ 20171222

extern void MDrv_Power_SetMode(U8 u8Mode);
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#define DBGNUM(x, y)            //{putchar(x);putchar(y);putchar('\n');}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//extern void USB_Init_Configure(void);

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

void MDrv_Power_PMPowerRst(void)
{
  #if(PM_RUNS_IN == PM_RUNS_IN_FLASH)
    {
        printf("%s() Line %d:\n", __FUNCTION__, __LINE__);
        //printf("PM wake-up status 0x%x\n",MDrv_Read2Byte(0x341E));

    #if (  (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)   \
         ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)    \
         ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)    \
        )
        MDrv_Write2Byte(0x1034A0,0x03D2);    // clear PM 5V status
        MDrv_Write2Byte(0x1034A0,0x0392);    // hd0
        MDrv_Write2Byte(0x1034A4,0x020C);    // hd2

        MDrv_Write2Byte(0x1034A0,0x0192);    // hd0. [9] reg_pm_swrst = "0"
        MDrv_Write2Byte(0x1034A0,0x0392);    // hd0. [9] reg_pm_swrst = "1"

        MDrv_WriteRegBit(0x3DB0,1,BIT3);    // IR wakeup flag clear of NEC (or NEC-like) format
        MDrv_WriteByte(0x04B6,0x0F);        // DDC2BI wakeup flag clear
    #endif
    }
  #endif
}

BOOLEAN MDrv_Power_ExecutePowerUp(void)
{
    // Change power management status
    MDrv_Power_SetMode( PM_MODE_ON );

    MDrv_Set_Power_Flag ( PM_P3_RESET_FLAG,DISABLE );
#if ENABLE_POWER_SAVING_DPMS
    MDrv_Set_Power_Flag ( VGA_POWERSAVING ,DISABLE );
#endif

#if 0//ndef MSOS_TYPE_LINUX   ==> Move to msAPI_DrvInit_Init_USB()
    DBGNUM('P', '0');
    USB_Init_Configure();
    DBGNUM('P', '1');
#endif

// Don't know this is for which chip!
#if 0//def TEST_POWER_DOWN
    MDrv_WriteByte(0x1C00,0x5F);
    MDrv_WriteByte(0x1C01,0xFF);
#endif

    //DBGNUM('P', '2');

    return TRUE;
}

#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)
#define __boot_from_spi __attribute__ ((__section__ (".boot_from_spi_start.text")))
#define _SPI_RESET_VECTOR_BASE_ADDR  0x10000


//static void msAPI_BootFromSPI(void)
void __boot_from_spi msAPI_BootFromSPI(void)
{
    U32 u32Addr = _SPI_RESET_VECTOR_BASE_ADDR;

    //set up reset vector base
    RIU[0x1002AC] = 0x0000;//SPI
    RIU[0x100290] = 0x0000;//SPI

    RIU[0x1002B4] = (U16)(u32Addr >> 16);
    RIU[0x002E54] = (U16)(0x829f);  // set wtd_mcu_rst passwd
    RIU[0x002E52] &= (~0x0100); // non-fire wtd_mcu_rst

    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    RIU[0x100280] = (0x001F); // set spi_boot=1, release rstz_miu
    RIU[0x002E52] |= (0x0100); // fire wtd_mcu_rst

    //########################################
    //#
    //# Due to the fact that __loader_2nd is a specified section
    //# Have to avoid to use some api functions out of this section
    //#
    //########################################
    //MDrv_Write2Byte(0x1002B4, (U16)(u32Addr >> 16));
    //MDrv_Write2Byte(0x002E54, 0x829f);  // set wtd_mcu_rst passwd
    //MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)&(~BIT8));  // non-fire wtd_mcu_rst
    //wdt reset to dram: bellow 2 lines must in the same cache line 256bytes
    //MDrv_Write2Byte(0x100280, MDrv_Read2Byte(0x100280)|(0x002F));  // set sdr_boot=1, release rstz_miu
    //MDrv_Write2Byte(0x002E52, MDrv_Read2Byte(0x002E52)|(BIT8));  // fire wtd_mcu_rst
}

// For coverity test
BOOLEAN MApp_AlwaysReturnTrue(void);

void __boot_from_spi msAPI_CheckBootFromSPI(void)
{
    //printf(">> msAPI_CheckBootFromSPI \r\n");

    //if (msAPI_MIU_QuickDataBaseCheck())
    {
        //printf("[M10]: Start to Run PM on SPI... \r\n");

        msAPI_BootFromSPI();
    }

    while(MApp_AlwaysReturnTrue())  //don't change it.
    {
        //##################################################
        //
        // Must avoid to fetch code from dram via miu in the icache line size boundary
        // when Boot from SPI
        // Solution : 1.use dummy code below to avoid hang up issue
        //            2.msAPI_CheckBootFromSPI() place into start address of text section
        //##################################################
    }
}

//#######################
//
// Wakeup Devices Configuration
//
//#######################

void MDrv_Power_PrintWakeUpFlag(U32 u32Flag)
{
    printf("WakeUpFlag=0x%X {", u32Flag);

    if( u32Flag&PM_WAKEUP_BY_DVI )
        printf(" DVI0,");

#if( ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE )
    if( u32Flag&PM_WAKEUP_BY_DVI1 )
        printf(" DVI1,");
    if( u32Flag&PM_WAKEUP_BY_DVI2 )
        printf(" DVI2,");
    if( u32Flag&PM_WAKEUP_BY_DVI3 )
        printf(" DVI3,");
#endif

    if( u32Flag&PM_WAKEUP_BY_VGA )
        printf(" VGA,");

    if( u32Flag&PM_WAKEUP_BY_CEC )
        printf(" CEC,");

    printf("}\n");
}

#if( ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE )
U16 MDrv_Power_Get_WakeUpFlag_ByInputSrc(INPUT_SOURCE_TYPE_t eINPUT_SOURCE_TYPE)
{
    U16 u16WakeUpFlag = 0;

    switch (_MApi_XC_HDMI_GetPortMapping(eINPUT_SOURCE_TYPE))
    {
        case INPUT_PORT_DVI0:
            u16WakeUpFlag = PM_WAKEUP_BY_DVI0;
            break;
        case INPUT_PORT_DVI1:
            u16WakeUpFlag = PM_WAKEUP_BY_DVI1;
            break;
        case INPUT_PORT_DVI2:
            u16WakeUpFlag = PM_WAKEUP_BY_DVI2;
            break;
        case INPUT_PORT_DVI3:
            u16WakeUpFlag = PM_WAKEUP_BY_DVI3;
            break;

        default:
            break;
    }

    return u16WakeUpFlag;
}

#endif

#define DEBUG_PM_WAKEUP(x)  x
void MDrv_Power_Standby_CheckWakeupDevice(void)
{
    //DEBUG_PM_WAKEUP( PRINT_CURRENT_LINE(); );
    DEBUG_PM_WAKEUP( printf("1. wPM_WakeUpDevice = 0x%X\n", stPowerGenSetting.wPM_WakeUpDevice); );
    DEBUG_PM_WAKEUP( MDrv_Power_PrintWakeUpFlag(stPowerGenSetting.wPM_WakeUpDevice); );


    // Config DVI flag ...
    if( IsHDMIInUse() )
    {
        if (! MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) ) // Has signal
        { // Power down by User, => No need wakeup by DVI
        #if( ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE )
            stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_DVI_ALL;
        #else
            stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_DVI;
        #endif
        }
        else // Power down by User or AutoSleep
        {
            // If power down by no_signal_auto_sleep, should auto wake up by sync~
        #if (NO_SIGNAL_AUTO_SHUTDOWN )
            if( g_NoSignalAutoSleep_bTimeoutAndGoToSleep )
            {
            #if( ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE )
                stPowerGenSetting.wPM_WakeUpDevice |= MDrv_Power_Get_WakeUpFlag_ByInputSrc(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW));
            #else
                stPowerGenSetting.wPM_WakeUpDevice |= PM_WAKEUP_BY_DVI;
            #endif
            }
            else
        #endif
            {
                // No need wake up by DVI signal
            }
        }
    }
    else
    { // Src is not HDMI => No need wakeup by DVI
    #if( ENABLE_PM_WAKEUP_DVI_PORT_SEPERATE )
        stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_DVI_ALL;
    #else
        stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_DVI;
    #endif
    }

    // Config VGA flag ...
  #if ENABLE_POWER_SAVING_DPMS
    if(g_bVGANoSignalPowerDown)
    {
        if (stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_VGA)
        {
            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_RGB, MAIN_WINDOW);
        }
    }
    else
    {
        stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_VGA;
    }
  #endif

    // Config CEC flag ...
  #if (ENABLE_WAKEUP_BY_CEC) // Wakeup from PM condition: CEC on and auto TV on
    if ((DB_HDMI_SETTING.g_bHdmiCecMode == ENABLE)&&(DB_HDMI_SETTING.g_bHdmiCecAutoTvOn == TRUE))
    {
        stPowerGenSetting.wPM_WakeUpDevice |= PM_WAKEUP_BY_CEC;
    }
    else
    {
        stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_CEC;
    }
  #endif

    DEBUG_PM_WAKEUP( printf("2.wPM_WakeUpDevice = 0x%X\n", stPowerGenSetting.wPM_WakeUpDevice ); );
    DEBUG_PM_WAKEUP( MDrv_Power_PrintWakeUpFlag(stPowerGenSetting.wPM_WakeUpDevice); );
}

static void _MDrv_IR_ConfigWakeUp(void)
{
#if( IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE )
    // set header code for HW NEC decode
    MDrv_WriteByte(STNADBY_IR_HEADER_CODE0_1,IR_HEADER_CODE0);
    MDrv_WriteByte(STNADBY_IR_HEADER_CODE0_2,IR_HEADER_CODE1);

    //support 2nd NEC Full decode
    MDrv_WriteByte(STNADBY_IR_HEADER_CODE1_1,IR_HEADER_CODE_2ND0);
    MDrv_WriteByte(STNADBY_IR_HEADER_CODE1_2,IR_HEADER_CODE_2ND1);
    MDrv_WriteRegBit(STNADBY_IR_HEADER_CODE1_EN, IR_2ND_NEC_DECODE_EN, _IR_HEADER_CODE1_EN);
#endif

    // set power-on key
    #if 1//Configure IR_WAKEUP_KEYX in IR_XXX_YYY.h
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY0,IR_WAKEUP_KEY0);
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY1,IR_WAKEUP_KEY1);
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY2,IR_WAKEUP_KEY2);
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY3,IR_WAKEUP_KEY3);
    #else //for test and test ok
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY0,IRKEY_SELECT);
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY1,IRKEY_CHANNEL_MINUS);
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY2,IRKEY_CHANNEL_PLUS);
    MDrv_WriteByte(STNADBY_WAKEUP_IR_KEY3,IRKEY_INPUT_SOURCE );
    #endif
}

// standby
void MDrv_Power_StandbyPowerOff(void)
{
    printf("=> StandBy \n");

    MDrv_Power_Standby_CheckWakeupDevice();
    msAPI_Power_SetWakeUpDevice();

    //configure wakeup devices
    _MDrv_IR_ConfigWakeUp();

    // new M12 standby mode code base
    //MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);
	MUTE_Off(); //gchen @ 20180207 //power off mute off
    Panel_VCC_OFF();
    Panel_Backlight_VCC_OFF();

	//<<gchen  @ 20171222 //adayo power off 
	Optical_Led_OpenANDClose(0);
	printf("=> StandBy 22\n");

	//MsOS_DelayTask(15*1000);
	printf("=> StandBy 33\n");
	//Power_Off();
	//>>gchen  @ 20171222 //adayo power off 
	
    MDrv_COPRO_Disable();

    // RTC setting ??

    // stop all interrupt
    MsOS_CPU_DisableInterrupt();
    MsOS_CPU_MaskAllInterrupt();
    MsOS_DisableAllInterrupts();

#if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)   \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)    \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)    \
    )
    // change SPI clock to XTAL
    MDrv_Write2Byte(0x0008e2, 0x011a);
    MDrv_Write2Byte(0x0008e4, 0x0000);
    MDrv_WriteByte(0x000f41, 0x3c);
    MDrv_WriteByte(0x000f41, 0x7c);
    MDrv_WriteByte(0x100b2c, 0x00);
    MDrv_WriteByte(0x100b2c, 0x20);

    // change R2 clock to XTAL
    MDrv_WriteByte(0x100b25, 0x08);
#elif(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)
   MDrv_WriteByte(0x100b20, 0x00);             // switch clk_mcu       =  12Mhz
   MDrv_WriteByte(0x100b2c, 0x1c);             // switch clk_spi       =  12Mhz
   MDrv_WriteByte(0x000f40, 0x00);             // switch clk_mcu_pm    =  12Mhz
   MDrv_WriteByte(0x000f41, 0x10);             // switch clk_spi_pm    =  12Mhz
   MDrv_WriteByte(0x100b25, 0x00);             // switch clk_mps_aeon  =  12Mhz (deglitch)
   MDrv_WriteByte(0x100b24, 0x00);             // switch clk_aeon      =  12Mhz (deglitch)
#endif

    //#if ( POWER_CONTROL == ENABLE ) // move to pm bin control
    //    POWER_ON_OFF1_Off();
    //#endif

    // R2 run code in PM.bin
    msAPI_CheckBootFromSPI();
}

//-------------------------------------------------------------------------------------------------
/// Power down procedure: after reboot, the main loop will execute power down procedure, and enter standby mode then
/// @param
/// @return
///
//-------------------------------------------------------------------------------------------------
void MDrv_Power_ExecutePowerDown(void)
{
    printf("MDrv_Power_ExecutePowerDown \r\n");

    #if (PM_MODE_SELECT == PM_MODE_DEEPSLEEP)
    MDrv_Power_PMPowerOff();
    #else //if (PM_MODE_SELECT == PM_MODE_STANBY)
    MDrv_Power_StandbyPowerOff();
    #endif
}
#endif


//################################################
//
//  Run code in MIPS L1 Cache Procedure
//
//################################################
#if (PM_RUNS_IN == PM_RUNS_IN_CACHE)
#include "drvPM.h"
#include "msIR.h"
extern int MDrv_Sys_RunCodeInL1Cache(void);

//#######################
//
// Wakeup Devices Configuration
//
//#######################

#define DEBUG_PM_WAKE_UP(x)     //x
void MDrv_Power_Standby_CheckWakeupDevice(void)
{
    DEBUG_PM_WAKE_UP( printf("1.stPowerGenSetting.wPM_WakeUpDevice=0x%X\n", stPowerGenSetting.wPM_WakeUpDevice); );

    if( IsHDMIInUse() )
    {
        if (! MApi_XC_PCMonitor_SyncLoss(MAIN_WINDOW) ) // Has signal
        {
            stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_DVI;
        }
        else
        {
            stPowerGenSetting.wPM_WakeUpDevice |= PM_WAKEUP_BY_DVI;
        }
    }
    else
    {
         stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_DVI;
    }

    DEBUG_PM_WAKE_UP( printf("wPM_WakeUpDevice&PM_WAKEUP_BY_DVI=0x%X\n", (stPowerGenSetting.wPM_WakeUpDevice&PM_WAKEUP_BY_DVI) ); );


  #if ENABLE_POWER_SAVING_DPMS
    if(g_bVGANoSignalPowerDown)
    {
        if (stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_VGA)
        {
            MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_RGB, MAIN_WINDOW);
        }
    }
    else
    {
        stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_VGA;
    }
  #endif

    DEBUG_PM_WAKE_UP( printf("wPM_WakeUpDevice&PM_WAKEUP_BY_VGA=0x%X\n", (stPowerGenSetting.wPM_WakeUpDevice&PM_WAKEUP_BY_VGA) ); );

  #if (ENABLE_WAKEUP_BY_CEC) // Wakeup from PM condition: CEC on and auto TV on
    if ( (DB_HDMI_SETTING.g_bHdmiCecMode == ENABLE) && (DB_HDMI_SETTING.g_bHdmiCecAutoTvOn == TRUE) )
    {
        stPowerGenSetting.wPM_WakeUpDevice |= PM_WAKEUP_BY_CEC;
    }
    else
    {
        stPowerGenSetting.wPM_WakeUpDevice &= ~PM_WAKEUP_BY_CEC;
    }
  #endif

    DEBUG_PM_WAKE_UP( printf("wPM_WakeUpDevice&PM_WAKEUP_BY_CEC=0x%X\n", (stPowerGenSetting.wPM_WakeUpDevice&PM_WAKEUP_BY_CEC) ); );

    printf("2.stPowerGenSetting.wPM_WakeUpDevice=0x%X\n", stPowerGenSetting.wPM_WakeUpDevice);
}

#define PM_SLEEP_SW_DUMMY0                  (RIUBASE_PM_SLEEP+0x72) //0x39*2
#define PM_SLEEP_SW_DUMMY1                  (RIUBASE_PM_SLEEP+0x78) //0x3C*2

static void MDrv_Power_Standby_ConfigWakeupDevice(void)
{
    msAPI_KeyPad_Initialize();
    static PM_WakeCfg PmWakeCfg =
    {
        .u8PmWakeIR =
        {   //IR wake-up key define
            IRKEY_POWER, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF
        },

        .u8PmWakeIR2 =
        {   //IR wake-up key define
            IRKEY_POWER, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF,
            0xFF, 0xFF, 0xFF, 0xFF
        }
    };

    printf("stPowerGenSetting.wPM_WakeUpDevice=0x%X\n", stPowerGenSetting.wPM_WakeUpDevice);

    PmWakeCfg.bPmWakeEnableIR     = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_IR)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableSAR    = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_KEYPAD)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableGPIO0  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_GPIO0)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableGPIO1  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_GPIO1)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableUART1  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_UART)?(TRUE):(FALSE));
    #if( ENABLE_POWER_SAVING_DPMS )
    PmWakeCfg.bPmWakeEnableSYNC   = ((g_bVGANoSignalPowerDown)?((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_VGA)?(TRUE):(FALSE)):(FALSE));
    #else
    PmWakeCfg.bPmWakeEnableSYNC   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_VGA)?(TRUE):(FALSE));
    #endif
    PmWakeCfg.bPmWakeEnableESYNC  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_ESYNC)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableRTC0   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_RTC0)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableRTC1   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_RTC1)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableDVI0   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_DVI)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableDVI2   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_DVI2)?(TRUE):(FALSE));

#if(ENABLE_WAKEUP_BY_CEC)
    PmWakeCfg.bPmWakeEnableCEC    = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_CEC)? ((DB_HDMI_SETTING.g_bHdmiCecMode)? (DB_HDMI_SETTING.g_bHdmiCecAutoTvOn):(FALSE)):(FALSE));
#else
    PmWakeCfg.bPmWakeEnableCEC  = 0;
#endif

    PmWakeCfg.bPmWakeEnableAVLINK = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_AVLINK)?(TRUE):(FALSE));
    PmWakeCfg.bPmWakeEnableMHL    = ((ENABLE_MHL)?((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_MHL)?(TRUE):(FALSE)):(FALSE));
    PmWakeCfg.bPmWakeEnableWOL    = FALSE;

    printf("PmWakeCfg: 0x%X 0x%X\n", ((U8*)(&PmWakeCfg))[0], ((U8*)(&PmWakeCfg))[1]  );

    //#####################
    //(1) Initial Wakeup Settings
    MsOS_Dcache_Flush((MS_U32)&PmWakeCfg,(MS_U32)sizeof(PM_WakeCfg));
    MsOS_FlushMemory();
    if(MDrv_PM_Init_NMBX((PM_WakeCfg*)_VA2PA((MS_U32) &PmWakeCfg))==0)
    {
        printf("MDrv_PM_Init fail !!!\n");
    }

#if ENABLE_IR_BIN
    U8 u8KeyPower = MApp_IrBin_GetKeyCode(IRKEY_POWER);

    MDrv_WriteByte(PM_SLEEP_SW_DUMMY0, u8KeyPower);
    MDrv_WriteByte(PM_SLEEP_SW_DUMMY1, u8KeyPower);
#endif


}

// standby
void MDrv_Power_StandbyPowerOff(void)
{
    printf("=> StandBy \n");

    //configure wakeup devices
    MDrv_Power_Standby_CheckWakeupDevice();
    MDrv_Power_Standby_ConfigWakeupDevice();

    //power off misc devices
    MApp_Audio_Set_AmpMute(AUDIO_AMP_MUTE_ON);

    Panel_VCC_OFF();
    Panel_Backlight_VCC_OFF();

	//<<gchen  @ 20171222 //adayo power off 
	Optical_Led_OpenANDClose(0);
	printf("=> StandBy 2\n");
	MsOS_DelayTask(20*1000);
	printf("=> StandBy 3\n");
	//Power_Off();
	//>>gchen  @ 20171222 //adayo power off 
	
    //stop Co-processor
    MDrv_COPRO_Disable();

    //stop all interrupt
    MsOS_CPU_DisableInterrupt();
    MsOS_CPU_MaskAllInterrupt();
    MsOS_DisableAllInterrupts();

#if( MAZDA_TMP_PATCH )
    PRINT_CURRENT_LINE();
#else
    //enter standby
    MDrv_Sys_RunCodeInL1Cache();
#endif

}

void MDrv_Power_ExecutePowerDown(void)
{
    MDrv_Power_StandbyPowerOff();
}
#endif

