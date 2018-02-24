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

////////////////////////////////////////////////////////////////////////////////
//
// @file msAPI_DrvInit.h
/// This file includes MStar driver initialization application interface
// @brief Driver initialization
///@author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MSAPI_DRVINIT_C_
#define _MSAPI_DRVINIT_C_

/******************************************************************************/
/*                            Header Files                                    */
/* ****************************************************************************/

#include <stdio.h>
#include <string.h>
//#include "datatype.h"
#include "Board.h"
#include "debug.h"
#include "mstar_debug.h"

// Common Definition
#include "MsCommon.h"
#include "MsTypes.h"

#include "BinInfo.h"
#include "SysInit.h"
#include "debug.h"
#include "hwreg.h"
#include "Panel.h"
#include "GPIO.h"

#include "msFlash.h"


#include "MsOS.h"
#include "MsIRQ.h"

#include "drvSAR.h"
#include "drvSYS.h"


#include "apiXC.h"
#include "apiGOP.h"
#include "apiGOP.h"
#if HDMITX_4030_ENABLE
#include"Device_hdmitx_4030.h"
#endif

#if(ENABLE_DTV)
#if( DEMOD_USE_UTOPIA || DEMOD_ATSC_USE_UTOPIA )
#include "drvDMD_common.h"
#endif
//#include "msAPI_Demod.h"
#endif

#include "drvAUDIO.h"

#include "msAPI_MailBox.h"
#include "msAPI_Global.h"
#include "msAPI_DrvInit.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"
#include "msAPI_Video.h"
#include "msAPI_VD.h"
#include "msAPI_OCP.h"
#include "msAPI_Global.h"
#include "msAPI_Bootloader.h"
#include "msAPI_OSD.h"
#if ENABLE_CEC
#include "msAPI_CEC.h"
#endif

#include "msAPI_Tuner.h"
#include "msAPI_Flash.h"
#include "msAPI_IR.h"


#include "MApp_Font.h"

#include "drvCPU.h"
#include "drvISR.h"
#include "drvBDMA.h"
#include "drvpower_if.h"
#if 1//ndef ATSC_SYSTEM
#include "drvDSCMB.h"
#endif

#if (ENABLE_PWS )
  #include "drvPWS.h"
#endif
#include "drvMVOP.h"
#include "drvSERFLASH.h"
#include "drvUartDebug.h"
#include "drvIIC.h"
#include "drvXC_HDMI_if.h"
#include "drvUSB.h"
#include "drvDDC2BI.h"
#include "drvTVEncoder.h"
#include "drvPM.h"
#include "drvIR.h"
#include "drvSEM.h"
#include "drvVIF_Temp.h"


#include "apiDMX.h"
#include "apiPNL.h"
#include "apiXC_Sys.h"
#include "apiXC_Hdmi.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Cus.h"
#include "apiXC_Ace.h"
#include "apiXC_Dlc.h"
#include "apiAUDIO.h"
#include "apiDMX.h"

#include "msIR.h"
#include "msKeypad.h"

#ifdef SUPPORT_AP_BIN_IN_FLASH_2
#include "InfoBlock.h"
#endif

#if (ENABLE_MHL == ENABLE)
#include "msAPI_MHL.h"
#include "Mhl.h"
#if (MHL_TYPE == MHL_TYPE_INTERNAL)
#include "apiMHL.h"
#elif (MHL_TYPE == MHL_TYPE_ELAND)
#include "apiMHL_ELAND.h"
#endif
#endif

#if (MHEG5_ENABLE)
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_MHEG5.h"
#endif

#include "drvPQ.h"

#include "msAPI_Memory.h"
#include "msAPI_IR.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_Init.h"
#if (ENABLE_3D_PROCESS)   // anvi
#include "MApp_Scaler.h"
#endif

#if(ENABLE_DTV)
#include "mapp_demux.h"
#if(ENABLE_ATSC)
#include "MApp_Psip.h"
#endif
#endif

#include "MApp_IR.h"

#if (ENABLE_HDR)
#include "MApp_HDR.h"
#endif

//-------------------------------------------------------------------------
extern void USB_Init_Configure(void);



//******************************************************************************

#define DRVINIT_DBG(x)              x //gchen @ 20171222 //open debug
#define POWERDOWN_EXEC_DBG(x)       x //gchen @ 20171222 //open debug

//******************************************************************************

#define PM_LOCK_SUPPORT             1   // 1: Enable 0: Disable

#define MK_U32(B0, B1, B2, B3)      ((((U32)(B3))<<24) | (((U32)(B2))<<16) | (((U32)(B1))<<8) | ((U32)(B0)))
#define MK_U16(B0, B1)              ((((U16)(B1))<< 8) | ((U16)(B0)))

#define DEBUG_PANEL_INFO_FROM_MAILBOX   0

#define MCU_REG_BASE                    0x1000           //0x001000
#define PMSLEEP_REG_BASE                0x0e00           //0x000e00
#define REG_PM_CPUX_SW_RSTZ             (PMSLEEP_REG_BASE + 0x29*2)

//------------------------------------------------------------------------------
// External funciton
//------------------------------------------------------------------------------


/***************************************************************************************/
/// Initial system and all drivers
/***************************************************************************************/

void MDrv_Chip_Initial( void )
{

#ifdef ENABLE_MINI_DUMP
    MsOS_EnableInterrupt(E_INT_FIQ_WDT);

    MDrv_Sys_SetWatchDogTimer( 10 );  //set 10 second
    MDrv_Sys_EnableWatchDog();

    MsOS_EnableInterrupt(E_INT_IRQ_MIU);
    MDrv_WriteRegBit(MIU_PROTECT_LOG_CLEAR, 0, 1<<1);
#else
    MDrv_Sys_SetWatchDogTimer( 10 );  //set 10 second
    MDrv_Sys_EnableWatchDog();
#endif

    MDrv_BDMA_Init(MIU_INTERVAL);

    MDrv_MIU_SetIOMapBase();
}

void msAPI_ChipInit(void)
{
#if 1//defined (MIPS_CHAKRA) || defined(__AEONR2__)
    MDrv_SetBEON_Host(TRUE);
#endif

    MDrv_Chip_Initial();

    //printf("msAPI_ChipInit ok\n");
}

/***************************************************************************************/
/// enable interrupt
/***************************************************************************************/
void msAPI_Interrupt_Init(void)
{
    //printf("msAPI_Interrupt_Init()\n");

    /* enable external interrupt */
    //mhal_interrupt_unmask( E_INTERRUPT_FIQ );
    //mhal_interrupt_unmask( E_INTERRUPT_IRQ );
    //mhal_interrupt_enable();

#ifndef MSOS_TYPE_LINUX
    MsOS_CPU_UnMaskInterrupt( E_INTERRUPT_FIQ );
    MsOS_CPU_UnMaskInterrupt( E_INTERRUPT_IRQ );
    MsOS_CPU_EnableInterrupt();
#endif
}

/***************************************************************************************/
/// Power down execution
/***************************************************************************************/
#ifdef __mips__
     extern void MDrv_BDMA_SetSPIOffsetForMCU(void);
#endif

#if (PM_RUNS_IN == PM_RUNS_IN_51)
void msAPI_Power_SetPowerMode2PM51(PM_WakeCfg *PmWakeCfg)
{
    //MDrv_MBX_SetDbgLevel(MBX_DBG_LEVEL_ALL);
    POWERDOWN_EXEC_DBG(printf("\33[1;29m msAPI_Power_SetPowerMode_N51 \n\33[0m"));
    MS_U8 u8Cnt;
    MBX_Result mbxResult;
    PM_Result pmResult; //????????????? useless

    #define PA_PmWakeCfg  ((PM51_MEM_MEMORY_TYPE&MIU1)?(PM51_MEM_ADR|MIU_INTERVAL):PM51_MEM_ADR)
    PM_WakeCfg *pPmWakeCfg = (PM_WakeCfg*)_PA2VA(PA_PmWakeCfg);

    MS_U8 u8PmWakeIRArray[]=
    {   //IR wake-up key define
        IRKEY_POWER, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY
    };

    MS_U8 u8PmWakeIRArray2[] =
    {
        //IR wake-up key 2 define
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY,
        IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY, IRKEY_DUMY
    };


    PmWakeCfg->bPmWakeEnableIR     = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_IR)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableSAR    = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_KEYPAD)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableGPIO0  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_GPIO0)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableGPIO1  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_GPIO1)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableUART1  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_UART1)?(TRUE):(FALSE));
#if( ENABLE_POWER_SAVING_DPMS )
    PmWakeCfg->bPmWakeEnableSYNC   = ((g_bVGANoSignalPowerDown)?((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_SYNC)?(TRUE):(FALSE)):(FALSE));
#else
    PmWakeCfg->bPmWakeEnableSYNC   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_SYNC)?(TRUE):(FALSE));
#endif
    PmWakeCfg->bPmWakeEnableESYNC  = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_ESYNC)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableRTC0   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_RTC0)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableRTC1   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_RTC1)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableDVI0   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_DVI0)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableDVI2   = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_DVI2)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableCEC    = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_CEC)?
                                     ((DB_HDMI_SETTING.g_bHdmiCecMode)?
                                     (DB_HDMI_SETTING.g_bHdmiCecAutoTvOn):(FALSE)):(FALSE));
    PmWakeCfg->bPmWakeEnableAVLINK = ((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_AVLINK)?(TRUE):(FALSE));
    PmWakeCfg->bPmWakeEnableMHL    = ((ENABLE_MHL)?((stPowerGenSetting.wPM_WakeUpDevice & PM_WAKEUP_BY_MHL)?(TRUE):(FALSE)):(FALSE));
    PmWakeCfg->bPmWakeEnableWOL    = FALSE;

    for(u8Cnt=0; u8Cnt<PM_MAX_BUF_WAKE_IR; u8Cnt++)
    {
        PmWakeCfg->u8PmWakeIR[u8Cnt] = u8PmWakeIRArray[u8Cnt];
    }
    for(u8Cnt=0; u8Cnt<PM_MAX_BUF_WAKE_IR2; u8Cnt++)
    {
        PmWakeCfg->u8PmWakeIR2[u8Cnt] = u8PmWakeIRArray2[u8Cnt];
    }

    #if 0
    printf("bPmWakeEnableIR     = %x\n", PmWakeCfg->bPmWakeEnableIR);
    printf("bPmWakeEnableSAR    = %x\n", PmWakeCfg->bPmWakeEnableSAR);
    printf("bPmWakeEnableGPIO0  = %x\n", PmWakeCfg->bPmWakeEnableGPIO0);
    printf("bPmWakeEnableGPIO1  = %x\n", PmWakeCfg->bPmWakeEnableGPIO1);
    printf("bPmWakeEnableUART1  = %x\n", PmWakeCfg->bPmWakeEnableUART1);
    printf("bPmWakeEnableSYNC   = %x\n", PmWakeCfg->bPmWakeEnableSYNC);
    printf("bPmWakeEnableESYNC  = %x\n", PmWakeCfg->bPmWakeEnableESYNC);
    printf("bPmWakeEnableRTC0   = %x\n", PmWakeCfg->bPmWakeEnableRTC0);
    printf("bPmWakeEnableRTC1   = %x\n", PmWakeCfg->bPmWakeEnableRTC1);
    printf("bPmWakeEnableDVI0   = %x\n", PmWakeCfg->bPmWakeEnableDVI0);
    printf("bPmWakeEnableDVI2   = %x\n", PmWakeCfg->bPmWakeEnableDVI2);
    printf("bPmWakeEnableCEC    = %x\n", PmWakeCfg->bPmWakeEnableCEC);
    printf("bPmWakeEnableAVLINK = %x\n", PmWakeCfg->bPmWakeEnableAVLINK);
    printf("bPmWakeEnableMHL    = %x\n", PmWakeCfg->bPmWakeEnableMHL);
    printf("bPmWakeEnableWOL    = %x\n", PmWakeCfg->bPmWakeEnableWOL);
  #endif

    MDrv_BDMA_SetSPIOffsetForMCU();

    mbxResult = MSApi_MBX_RegisterMSG(E_MBX_CLASS_PM_WAIT, 6);
    if(E_MBX_SUCCESS != mbxResult)
    {
        printf("E_MBX_CLASS_PM_WAIT - MBX register msg error\n");
    }

    //MDrv_PM_SetDbgLevel(E_PM_DBGLV_ALL);
    //MDrv_MBX_SetDbgLevel(MBX_DBG_LEVEL_INFO);

    // Initialize IR before power down
    //msAPI_IR_Initialize();

    // Initialize SAR before power down
    //msAPI_KeyPad_Initialize();

    memcpy((void*)pPmWakeCfg,(void*)PmWakeCfg,sizeof(PM_WakeCfg));
    MsOS_Dcache_Flush((MS_U32)PmWakeCfg, sizeof(PM_WakeCfg));
    MsOS_FlushMemory();

    pmResult = MDrv_PM_Init((PM_WakeCfg*)PA_PmWakeCfg);

    POWERDOWN_EXEC_DBG(printf(" MDrv_PM_Init return 0x%02X \n", pmResult));

}
#endif

#if(!BLOADER)

#if (PM_RUNS_IN == PM_RUNS_IN_51)
void MDrv_Power_ExecutePowerDown2PM51(PM_WakeCfg *PmWakeCfg, PM_PowerDownCfg *PmPowerDownCfg)
{
    POWERDOWN_EXEC_DBG(printf("\33[1;29mMDrv_Power_ExecutePowerDown_N51 \n\33[0m"));

    PM_Result pmResult; //????????????? useless

    #define PA_PmPowerDownCfg  ((PM51_MEM_MEMORY_TYPE&MIU1)?(PM51_MEM_ADR|MIU_INTERVAL):PM51_MEM_ADR)
    PM_PowerDownCfg *pPmPowerDownCfg =(PM_PowerDownCfg*)_PA2VA(PA_PmPowerDownCfg);


    if (   PmWakeCfg->bPmWakeEnableSYNC   // Power down because of VGA no signal
        || PmWakeCfg->bPmWakeEnableMHL
       )
    {
        PmPowerDownCfg->u8PowerDownMode = E_PM_STANDBY; // PM51 is alive(standby)
    }
    else
    {
        PmPowerDownCfg->u8PowerDownMode = E_PM_SLEEP; // PM51 is sleep
    }
    PmPowerDownCfg->u8WakeAddress = E_PM_WAKE_LAST;

#if 0
    printf("u8PowerDownMode = %x\n", PmPowerDownCfg->u8PowerDownMode);
    printf("u8WakeAddress   = %x\n", PmPowerDownCfg->u8WakeAddress);
#endif

#if defined(MIPS_CHAKRA) || defined(ARM_CHAKRA)
    memcpy((void*)pPmPowerDownCfg,(void*)PmPowerDownCfg,sizeof(PM_PowerDownCfg));
    MsOS_Dcache_Flush((MS_U32)PmPowerDownCfg, sizeof(PM_PowerDownCfg));
    MsOS_FlushMemory();
    pmResult = MDrv_PM_PowerDown((PM_PowerDownCfg *)PA_PmPowerDownCfg);
#endif

#if defined(__aeon__)
    MsOS_Dcache_Flush((MS_U32)PmPowerDownCfg, sizeof(PM_PowerDownCfg));
    MsOS_FlushMemory();
    pmResult = MDrv_PM_PowerDown(PmPowerDownCfg);
#endif

    POWERDOWN_EXEC_DBG(printf(" MDrv_PM_PowerDown return 0x%02X \n", pmResult));

}
#endif

void msAPI_Power_PowerDown_EXEC(void)
{
    POWERDOWN_EXEC_DBG(printf("\33[1;29m msAPI_Power_PowerDown_EXEC1 \n\33[0m"));
#if (PM_RUNS_IN == PM_RUNS_IN_51)

    PM_WakeCfg PmWakeCfg;
    PM_PowerDownCfg PmPowerDownCfg;

    POWERDOWN_EXEC_DBG(printf("\r\n >> msAPI_Power_PowerDown_EXEC \n"));
    POWERDOWN_EXEC_DBG(printf("   wPM_WakeUpDevice = 0x%x \n", stPowerGenSetting.wPM_WakeUpDevice));

    msAPI_Power_SetPowerMode2PM51(&PmWakeCfg);
#elif (PM_RUNS_IN == PM_RUNS_IN_CACHE)

#elif (PM_RUNS_IN == PM_RUNS_IN_FLASH)
    msAPI_Power_SetPowerMode();
#endif


#if ( POWER_CONTROL != ENABLE )
    POWER_ON_OFF1_Off();
#endif

    LED_GRN_Off();
    LED_RED_On();

#if ENABLE_CEC
    ARC_CTRL_OFF();

    if ( DB_HDMI_SETTING.g_bHdmiCecMode )
    {
        if ( stGenSetting.g_SoundSetting.TVspeakerMode == TVspeaker_Mode_ExtAmp )
        {
            msAPI_CEC_PostMsg_SystemAudioModeRequestTermination(DIRECTMSG);

            MsOS_DelayTask(200);
        }

        if ( DB_HDMI_SETTING.g_bHdmiCecDeviceAutoStandby )
        {
            msAPI_CEC_PostMsg_Standby(DIRECTMSG);
            MsOS_DelayTask(200);
        }
    }

  #if (PM_RUNS_IN == PM_RUNS_IN_51)
    MApi_CEC_ConfigWakeUp();
  #endif
#endif

    puts("\n ~~~ POWER DOWN ~~~ \n");

#if (ENABLE_MHL == ENABLE)
    #if 0//(ENABLE_POST_INIT)
        if( MApp_Get_PostInit_Status() == TRUE )
    #endif
        {
            msAPI_MHL_TV_DC_off();
        }
#endif

#if (PM_RUNS_IN == PM_RUNS_IN_FLASH)
    MDrv_Power_ExecutePowerDown();
#elif (PM_RUNS_IN == PM_RUNS_IN_CACHE)
    MDrv_Power_ExecutePowerDown();
#elif( PM_RUNS_IN == PM_RUNS_IN_51 )
    MDrv_Power_ExecutePowerDown2PM51(&PmWakeCfg, &PmPowerDownCfg);
#endif

    MDrv_Sys_StopCpu(1);
}
#endif

/***************************************************************************************/
/// Power On execution
/***************************************************************************************/
void msAPI_PowerON_EXEC(void)
{
    //printf(">> msAPI_PowerON_EXEC() \n");

  #if ( POWER_CONTROL != ENABLE )
    POWER_ON_OFF1_On();
  #endif

    LED_RED_Off();
    LED_GRN_On();

    MDrv_Power_SetMode(PM_MODE_ON);
}

/******************************************************************************/
/// Initial system and all drivers
/******************************************************************************/
#if (ENABLE_SUPPORT_MM_PHOTO_4K_2K ==1)
extern void GOPVsyncIsr(MHAL_SavedRegisters *pHalReg, U32 vector);
#endif

void msAPI_DrvInit_Init_MIU_Group(void)
{
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NIKON) \
   ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NUGGET) \
   )
    //Client Select code from MDrv_ClientSelectToMIUx
    MDrv_Write2Byte( ( RIUBASE_MIU+0xf0 ), ClientGruop0_in_MIU1 );
    MDrv_Write2Byte( ( RIUBASE_MIU+0xf2 ), ClientGruop1_in_MIU1 );
    MDrv_Write2Byte( ( RIUBASE_MIU+0xf4 ), ClientGruop2_in_MIU1 );

    MDrv_Write2Byte( ( RIUBASE_MIU2+0xf0 ), ClientGruop0_in_IP  );
    MDrv_Write2Byte( ( RIUBASE_MIU2+0xf2 ), ClientGruop1_in_IP  );
    MDrv_Write2Byte( ( RIUBASE_MIU2+0xf4 ), ClientGruop2_in_IP  );
#endif
}

#define ENABLE_DEBUG_INIT_FLASH     0

#if(ENABLE_DEBUG_INIT_FLASH)
    #define DEBUG_INIT_FLASH(x) x
#else
    #define DEBUG_INIT_FLASH(x)
#endif

// Flash type:
//  0xC2, 0x20, 0x15: MX25L6406(E)
void msAPI_DrvInit_Init_Flash(void)
{
#if 1//(ENABLE_DEBUG_INIT_FLASH)
    U8 i;
#define FLASH_ID_SIZE   3
    U8 au8FlashId[FLASH_ID_SIZE];
    U32 u32FlashSize = 0;
#define INIT_FLASH_RETRY_TIME   2
#define CHECK_FLASH_SIZE_MIN    0x400000
#endif

    DEBUG_INIT_FLASH( PRINT_CURRENT_LINE(); );
    DEBUG_INIT_FLASH( printf("MDrv_SERFLASH_Init()\n"); );

#ifdef DEFAULT_FLASH_TYPE
    MDrv_FLASH_Assign_FlashType(DEFAULT_FLASH_TYPE);
#endif

    MDrv_SERFLASH_Init();

#if 1//(ENABLE_DEBUG_INIT_FLASH)
    for( i = 0; i < INIT_FLASH_RETRY_TIME; ++ i )
    {
        if( i > 0 )
        {
            msAPI_Timer_Delayms(10);
        }

        //printf("Wait flash free...\n");
        //msAPI_Flash_WaitWriteDone(FLASH_BLOCK_ERASE_MAX_TIME);

        DEBUG_INIT_FLASH(printf("Checking flash type&size...\n"); );

        if( FALSE == MDrv_SERFLASH_ReadID(au8FlashId, FLASH_ID_SIZE) )
        {
            printf(" MDrv_SERFLASH_ReadID() failed!\n");
            continue;
        }
        DEBUG_INIT_FLASH( printf("Flash Id: 0x%X 0x%X 0x%X\n", au8FlashId[0], au8FlashId[1], au8FlashId[2]); );

        if( FALSE == MDrv_SERFLASH_DetectSize(&u32FlashSize) )
        {
            printf(" MDrv_SERFLASH_DetectSize() failed!\n");
            //printf(" => u32FlashSize=0x%X\n", u32FlashSize);
            continue;
        }

        if( u32FlashSize < CHECK_FLASH_SIZE_MIN )
        {
            DEBUG_INIT_FLASH(printf(" u32FlashSize=0x%X is invalid!\n", u32FlashSize););
            continue;
        }
        else
        {
            break;
        }
    }

    DEBUG_INIT_FLASH( printf(" => u32FlashSize=0x%X\n", u32FlashSize); );

    if( u32FlashSize < CHECK_FLASH_SIZE_MIN )
    {
        printf(" u32FlashSize=0x%X is invalid!\n", u32FlashSize);
        //MDrv_Sys_StopCpu(1);
        msDebug_FatalErrorHandler(FATAL_ERR_ID_FLASH_SIZE_INVALID, u32FlashSize);
    }
#endif

    DEBUG_INIT_FLASH(printf(" MDrv_SERFLASH_Init() done\n"););

    // Pass WP pin control function to driver
    MDrv_SERFLASH_SetFlashWPCallBack(msFlash_ActiveFlash_Set_HW_WP);
}

#if (!BLOADER)
void msAPI_DrvInit_InitMBX(void)
{
    MBX_Result mbxResult;

    mbxResult = MSApi_MBX_Init();
    if(E_MBX_SUCCESS != mbxResult)
    {
        printf("\nError: MBX init error\n");
    }

    MSApi_MBX_Enable(TRUE);
}
#endif

void msAPI_DrvInitStep1(void)
{
    MDrv_Power_ExecutePowerUp();

#if (!BLOADER)
    msAPI_DrvInit_InitMBX();

    msAPI_Timer_SyncToPmRTC();

#endif // #if (!BLOADER)


#if (!BLOADER)
    // MStar Debug Intialization
    MStarDebugInitial();


 #if ENABLE_MSTV_UART_DEBUG
    MDrv_UART_DebugInit();
 #else
    MDrv_UART_Register_Empty_RecvHandler();
 #endif

 #if(ENABLE_UART2)
     MDrv_UART2_DebugInit();
 #endif

#endif



    MDrv_SYS_Init();


    msAPI_DrvInit_Init_MIU_Group();

    /* init MIU, dont put the code loading bin files before MIU Initialization */
    msAPI_MIU_Init();

    // Init flash driver
    msAPI_DrvInit_Init_Flash();

}

#if (!BLOADER)
void msAPI_DrvInit_InitVIF(void)
{
    // Init VIF driver
    MDrv_IFDM_Init();
}
#endif

#if (ENABLE_DTV)

#define DEBUG_DEMUX(x)  x

BOOL g_DrvInit_DemuxInited = 0;

BOOL msAPI_DrvInit_Get_DemuxInited(void)
{
    return g_DrvInit_DemuxInited;
}

void msAPI_DrvInit_ExitDemux(void)
{
//PRINT_CURRENT_LINE();
    DEBUG_DEMUX( PRINT_CUR_FUNCTION(); );

    if( g_DrvInit_DemuxInited == 0 )
    {
        PRINT_CURRENT_LINE();
        printf("\nWarning: Demux is not inited!\n");
        return;
    }

#if(ENABLE_DVB)
    MApp_Dmx_CloseAllFilters();
#endif

#if(ENABLE_ATSC)
    MApp_Dmx_CloseAllFilters_ATSC();
#endif

    MApi_DMX_Exit();

    g_DrvInit_DemuxInited = 0;
}

#define DEBUG_LOAD_TSP_BIN(x)   //x
BOOL msAPI_DrvInit_InitDemux(EnuInitDemuxCase eInitDemuxCase)
{
    eInitDemuxCase = eInitDemuxCase;
    DEBUG_DEMUX(printf("msAPI_DrvInit_InitDemux(eInitDemuxCase=%u)\n", eInitDemuxCase););

    BININFO   DMXBinInfo;
    BOOLEAN   bResult;

#if 0//(BLOADER)
    MS_U32  u32DMXBinAddr, u32DMXTmp;
    U32 u32PoolBufAddr = (POOL_BUFFER_MEMORY_TYPE & MIU1 ? (POOL_BUFFER_ADR | MIU_INTERVAL): (POOL_BUFFER_ADR));

    U32 u32DecompDestBufAddr;
    U32 u32DecompSrcBufAddr = u32PoolBufAddr;
    U32 u32DecompTmpBufAddr = u32DecompSrcBufAddr + 0x100000;
#else

  #if((CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)&&defined(VDEC_BALANCE_BW_ADR))
    U32 u32DecompDestBufAddr = MemAlign(VDEC_BALANCE_BW_ADR, 256UL);
  #else
    U32 u32DecompDestBufAddr = MemAlign(VDEC_BITSTREAM_ADR, 256UL);
  #endif
    U32 u32DecompSrcBufAddr = u32DecompDestBufAddr + 0x100000;
    U32 u32DecompTmpBufAddr = u32DecompSrcBufAddr + 0x100000;
#endif

    DEBUG_LOAD_TSP_BIN(printf("u32DecompDestBufAddr=0x%X\n", u32DecompDestBufAddr););
    DEBUG_LOAD_TSP_BIN(printf("u32DecompSrcBufAddr=0x%X\n", u32DecompSrcBufAddr););
    DEBUG_LOAD_TSP_BIN(printf("u32DecompTmpBufAddr=0x%X\n", u32DecompTmpBufAddr););


    if( g_DrvInit_DemuxInited == 1 )
    {
        PRINT_CURRENT_LINE();
        printf("\nWarning: Demux driver is already inited!\n");
        return FALSE;
    }


#if ((BLOADER)||(FLASH_SIZE <=FLASH_SIZE_4MB))
    DMXBinInfo.B_ID = BIN_ID_CODE_DEMUX_COMPRESS;
#else
    DMXBinInfo.B_ID = BIN_ID_CODE_DEMUX;
#endif

    MDrv_Sys_Get_BinInfo(&DMXBinInfo, &bResult);
    if ( bResult != PASS)
    {
        printf( "\nError: Could not find Demux binary on flash.\n");
        return FALSE;
    }

    DEBUG_LOAD_TSP_BIN(printf("DMXBinInfo.B_FAddr=0x%X\n", DMXBinInfo.B_FAddr););
    DEBUG_LOAD_TSP_BIN(printf("DMXBinInfo.B_Len=0x%X\n", DMXBinInfo.B_Len););

    //MApi_BDMA_Copy(DMXBinInfo.B_FAddr, u32DecompDestBufAddr, 0x5468, MIU_FLASH2SDRAM);
    //printf("Flash CRC=0x%X\n", msAPI_CRC_Cal((U8*)MsOS_PA2KSEG1(u32DecompDestBufAddr), 0x5468) );

#if 0//(BLOADER)
    u32DMXTmp = (MS_U32)msAPI_Memory_Allocate((U16)(DMXBinInfo.B_Len+256),BUF_ID_LOAD_TSP_BIN);
    if (u32DMXTmp == NULL)
    {
        //ASSERT(u32DMXTmp);
        printf( "\nError: msAPI_Memory_Allocate() failed.\n");
        return FALSE;
    }

    //t8 must be 256 aligment, fannie, 2010/04/03
    u32DMXBinAddr = MemAlign(u32DMXTmp, 256UL);  // address must align by chip ex: t8 256 align
    //u32DMXBinAddr = MemAlign(u32DMXTmp,128UL);  // address must align by chip ex: t2 64 align, t3 128 align

    u32DecompDestBufAddr = MsOS_VA2PA(u32DMXBinAddr);
#endif

#if 0//(BLOADER)
    if( SUCCESS != MDrv_DMA_LoadBin( &DMXBinInfo,
            u32DMXBinAddr,
            MsOS_PA2KSEG0( u32DecompSrcBufAddr), //_PA2VA( u32PoolBufAddr),
            MsOS_PA2KSEG0( u32DecompTmpBufAddr) //_PA2VA( u32PoolBufAddr + BUF_FOR_DECOMPRESS_OFFSET1)
         )
      )
    {
        printf("\nError: Load DMXBin Fail!");
        msAPI_Memory_Free((void *)u32DMXTmp, BUF_ID_LOAD_TSP_BIN);
        return FALSE;
    }
#else

  #if 1 // For compressed tsp.bin
    if( SUCCESS != MDrv_DMA_LoadBin( &DMXBinInfo,
              MsOS_PA2KSEG0(u32DecompDestBufAddr), // Dest addr
              MsOS_PA2KSEG0( u32DecompSrcBufAddr), // Src
              MsOS_PA2KSEG0( u32DecompTmpBufAddr) // tmp
           )
        )
    {
          printf("\nError: Load DMXBin Fail!");
          return FALSE;
    }
  #else
    msAPI_MIU_Copy(DMXBinInfo.B_FAddr,
            MS_VA2PA(u32DMXBinAddr),
            MemAlign(DMXBinInfo.B_Len,8UL),
            MIU_FLASH2SDRAM);
  #endif

#endif


    //printf("FOD CRC=0x%X\n", msAPI_CRC_Cal((U8*)MsOS_PA2KSEG0(DMXBinInfo.B_FAddr+0x7800000), 0x5468) );
    //printf("u32DecompDestBufAddr CRC=0x%X\n", msAPI_CRC_Cal( (U8*)MsOS_PA2KSEG0(u32DecompDestBufAddr), 0x5468) );
    //Print_Buffer( (U8*)MsOS_PA2KSEG1(u32DecompDestBufAddr+0x5268), 0x280 );

    DEBUG_LOAD_TSP_BIN(printf("DMXBinInfo.B_Len=0x%X\n", DMXBinInfo.B_Len););

    //MApi_DMX_SetFW( MS_VA2PA(u32DMXBinAddr), DMXBinInfo.B_Len);
    MApi_DMX_SetFW( u32DecompDestBufAddr, DMXBinInfo.B_Len);

    MApi_DMX_SetHK(TRUE);

    MApi_DMX_Init();

  #if ENABLE_DMX_VQ_BUF//VQ_ENABLE
    DMX_TSPParam tspparam;
    tspparam.phyFWAddr = u32DecompDestBufAddr;//MS_VA2PA(u32DMXBinAddr);
    tspparam.u32FWSize = DMXBinInfo.B_Len;
    tspparam.phyVQAddr = TSP_VQ_BUFFER_ADR;
    tspparam.u32VQSize = TSP_VQ_BUFFER_LEN;
    MApi_DMX_TSPInit(&tspparam);
  #endif


#if MHEG5_ENABLE
  #if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON))
    MApi_DMX_SetOwner(16,63,TRUE);
  #else
    MApi_DMX_SetOwner(16,31,TRUE);
  #endif
#else
    // No MHEG, HK can use all filter
    MApi_DMX_SetOwner(0,31,TRUE);
#endif


#if 0//(BLOADER)
    msAPI_Memory_Free((void *)u32DMXTmp, BUF_ID_LOAD_TSP_BIN);
#endif

    g_DrvInit_DemuxInited = 1;

    return TRUE;
}
#endif

#if (!BLOADER)
void msAPI_DrvInit_Init_IR(void)
{
  #if ENABLE_IR_BIN
    MApp_IrBin_Init();
  #endif
    ///* init IR */
  #if 1 // No need use chip option!
    msIR_Initialize(MST_XTAL_CLOCK_MHZ);
  #else
    #if ((CHIP_FAMILY_TYPE!=CHIP_FAMILY_EDEN) && \
        (CHIP_FAMILY_TYPE!=CHIP_FAMILY_NASA) && \
        (CHIP_FAMILY_TYPE!=CHIP_FAMILY_EULER))
      #ifdef __aeon__
        msAPI_IR_Initialize();
      #else
        msIR_Initialize(MST_XTAL_CLOCK_MHZ);
      #endif
    #else
        msIR_Initialize(MST_XTAL_CLOCK_MHZ);
    #endif
  #endif


    printf("driver IR init ok\n");
}

void msAPI_DrvInit_Init_KeyPad(void)
{
  #if( POWER_KEY_PAD_BY_INTERRUPT )
    MDrv_Sys_SetInterrupt(EX0_INT_IN, ENABLE);
  #endif

    MDrv_SAR_Kpd_Init();

  #if 0
    msAPI_KeyPad_Initialize();
  #else
    msKeypad_Init();
  #endif
}

void msAPI_DrvInit_Init_PWS(void)
{
#if ( ENABLE_PWS)
    #if ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)    \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)   \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)  \
        ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MELODY)  \
        )

        MDrv_PWS_Init(E_PWS_VIF_DUAL_SAW);

    #elif ( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD)   \
          ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)     \
          ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)      \
          ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON)    \
          ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)     \
          )

// 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw(VIF); 4: internal single SAW; 5: no SAW(DIF)
      #if (VIF_SAW_ARCH == 0)
        MDrv_PWS_Init(E_PWS_VIF_DUAL_SAW);
      #elif (VIF_SAW_ARCH == 3) || (VIF_SAW_ARCH == 5)
        MDrv_PWS_Init(E_PWS_VIF_NO_SAW);
      #else
        MDrv_PWS_Init(E_PWS_VIF_SINGLE_SAW);
      #endif

    #else

        //MApi_PWS_Init();
        #error

    #endif

#endif // #if ( ENABLE_PWS)
}

void msAPI_DrvInit_Init_GE_GOP(void)
{
    GFX_Config tGFXcfg;

    tGFXcfg.bIsCompt = TRUE;
    tGFXcfg.bIsHK = TRUE;

    MApi_GFX_Init(&tGFXcfg);
    MApi_GOP_RegisterFBFmtCB(( MS_U32(*)(MS_U16 pitch,MS_U32 addr , MS_U16 fmt ))msAPI_OSD_RESOURCE_SetFBFmt);
    MApi_GOP_RegisterXCIsInterlaceCB(mvideo_sc_is_interlace);
    MApi_GOP_RegisterXCGetCapHStartCB(mvideo_sc_get_h_cap_start);
    MApi_GOP_RegisterXCReduceBWForOSDCB(MApi_XC_Sys_PQ_ReduceBW_ForOSD);

    //-----------------------------------------------------------------------------------
    GOP_InitInfo pGopInit;

    pGopInit.u16PanelWidth = g_IPanel.Width();//*(panelinfo->Width);
    pGopInit.u16PanelHeight = g_IPanel.Height();//*(panelinfo->Height);
    pGopInit.u16PanelHStr = g_IPanel.HStart();//*(panelinfo->HStart);
    pGopInit.u32GOPRBAdr = ((GOP_GWIN_RB_MEMORY_TYPE & MIU1) ? (GOP_GWIN_RB_ADR | MIU_INTERVAL) : (GOP_GWIN_RB_ADR));
    pGopInit.u32GOPRBLen = GOP_GWIN_RB_LEN;

    //there is a GOP_REGDMABASE_MIU1_ADR for MIU1
    pGopInit.u32GOPRegdmaAdr = ((GOP_REGDMABASE_MEMORY_TYPE & MIU1) ? (GOP_REGDMABASE_ADR | MIU_INTERVAL) : (GOP_REGDMABASE_ADR));//GOP_REGDMABASE_ADR;//
    pGopInit.u32GOPRegdmaLen = GOP_REGDMABASE_LEN;
  #if (ENABLE_SUPPORT_MM_PHOTO_4K_2K == 1)
    pGopInit.bEnableVsyncIntFlip = TRUE;
  #else
    pGopInit.bEnableVsyncIntFlip = FALSE;
  #endif

    E_GOP_API_Result eGOP_API_Result = MApi_GOP_Init(&pGopInit);

    #if (MAZDA_TMP_PATCH)
    MDrv_WriteRegBit(0x131046, FALSE, BIT5);
    #endif

    if( GOP_API_SUCCESS != eGOP_API_Result )
    {
        printf("\nError: MApi_GOP_Init() failed!(%u)\n", eGOP_API_Result);
        return;
    }

    MApi_GOP_GWIN_Set_TranspColorStretchMode(E_GOP_TRANSPCOLOR_STRCH_ASNORMAL);//issue:UI char have some black point.

    MApi_GFX_RegisterGetFontCB(msAPI_OSD_RESOURCE_GetFontInfoGFX);
    MApi_GFX_RegisterGetBMPCB(msAPI_OSD_RESOURCE_GetBitmapInfoGFX);

  #if (ENABLE_SUPPORT_MM_PHOTO_4K_2K == 1)
    MsOS_DisableInterrupt(E_INT_IRQ_GOP);
    MsOS_DetachInterrupt (E_INT_IRQ_GOP);
    MsOS_AttachInterrupt(E_INT_IRQ_GOP, (InterruptCb)GOPVsyncIsr);
    MsOS_EnableInterrupt(E_INT_IRQ_GOP);
  #endif


    DEBUG_INIT_FLOW( printf("GOP init done\n"); );
}
#endif

void msAPI_DrvInit_Init_USB(void)
{
    USB_Init_Configure();

  #if (ENABLE_USB)
    MDrv_USB_Init(((USB_BUFFER_START_MEMORY_TYPE & MIU1) ? (USB_BUFFER_START_ADR | MIU_INTERVAL) : (USB_BUFFER_START_ADR)));
  #endif

  #if (ENABLE_USB_2)
    MDrv_USB_Init_Port2(((USB_BUFFER2_START_MEMORY_TYPE & MIU1) ? (USB_BUFFER2_START_ADR | MIU_INTERVAL) : (USB_BUFFER2_START_ADR)));
  #endif
}

void msAPI_DrvInit_Init_XC_HDMI(void)
{
#if (!BLOADER)

    /* scaler intialization */
    MApi_XC_Sys_Init();
  #if (ENABLE_HDR)
    /* HDR intialization */
    MApp_HDR_Init();
  #endif

  #if (ENABLE_3D_PROCESS )  // anvi
    MApp_Scaler_3D_Behavior_init();
  #endif

  #if(ENABLE_3D_PROCESS \
   &&( ENABLE_MFC_6M30 || ENABLE_6M40_4KX2K_PROCESS || ENABLE_6M50_4KX2K_PROCESS) \
   && CONFIG_3D_HWLVDSLRFLAG \
    )
    MApi_XC_3D_Enable_Skip_Default_LR_Flag(ENABLE);
    PNL_Set3D_HWLVDSLRFlag();
  #endif

#endif
}

void msAPI_DrvInitStep2(void)
{
#if (!BLOADER)

    //msAPI_DrvInit_Init_IR();

    //msAPI_DrvInit_Init_KeyPad();

    msAPI_DrvInit_Init_PWS();

#endif

    InitIOExpander(); //for other chip

#if (!BLOADER)

  #if (PM_LOCK_SUPPORT == 0)
    // Init Sem
    MDrv_SEM_Init();
  #endif

    // init Graphics Engine
    msAPI_DrvInit_Init_GE_GOP();

#endif // #if (!BLOADER)



  #ifdef SUPPORT_AP_BIN_IN_FLASH_2
    InfoBlock_DumpBinInfo();
    InfoBlock_Flash_2_Bin_Init();
    InfoBlock_DumpBinInfo();
  #endif

    // init Demux
    //mdrv_irq_unmask(IRQ_TSP2HK);
#if (ENABLE_DTV)
    msAPI_DrvInit_InitDemux(E_INIT_DEMUX_AT_POWER_ON_INIT);

    msAPI_DMX_Init();

 #if (!BLOADER)
  #if ENABLE_DVB
    MDrv_DSCMB_Init();
  #endif
 #endif


  #if ( DEMOD_DVBT_USE_UTOPIA || DEMOD_DVBC_USE_UTOPIA || DEMOD_ISDBT_USE_UTOPIA || DEMOD_DTMB_USE_UTOPIA || DEMOD_ATSC_USE_UTOPIA)
    MDrv_DMD_PreInit();
  #endif

#endif


  #if (!BLOADER)

    // Enable MAD interrupt
    MsOS_EnableInterrupt(E_INT_FIQ_DEC_DSP2UP);
    MsOS_EnableInterrupt(E_INT_FIQ_SE_DSP2UP);            //Robert.Yang

  #endif // #if (!BLOADER)

    // Move to MApp_PreInit_USB_Init()
    //msAPI_DrvInit_Init_USB();

  #if (!BLOADER)
    MDrv_AUDIO_InitMMIO();
  #endif


#if (!BLOADER)
    msAPI_DrvInit_InitVIF();
#endif

#if( HDMITX_4030_ENABLE ==ENABLE)
  device_hdmitx_4030_Chip_Init();
#endif
}

void msAPI_DrvInit_InitForBLoader(void)
{
    msAPI_DrvInitStep1();

    msAPI_DrvInitStep2();
}

void msAPI_ShowWarningMessage(BOOLEAN bShow, const char *warningMsg)
{
#if (!BLOADER)
    static U8 g_gwinID = GWIN_NO_AVAILABLE;
    static OSDClrBtn clrBtn;

    if(bShow && g_gwinID == GWIN_NO_AVAILABLE)
    {
        memset(&clrBtn, 0, sizeof(clrBtn));
        clrBtn.x =  0;
        clrBtn.y =  0;
        clrBtn.width = PANEL_WIDTH*3/4;
        clrBtn.height =PANEL_HEIGHT/4;
        clrBtn.radius = 0;
        clrBtn.u8Gradient = CONSTANT_COLOR;
        clrBtn.b_clr =  COLOR_BLUE;
        clrBtn.fHighLight =  FALSE;

        g_gwinID = MApi_GOP_GWIN_CreateWin( PANEL_WIDTH*3/4, PANEL_HEIGHT/4, DEFAULT_FB_FMT);
        if(g_gwinID != GWIN_NO_AVAILABLE)
        {
            MApi_GOP_GWIN_SetWinPosition(g_gwinID, PANEL_WIDTH/8, PANEL_HEIGHT*3/8);
            MApi_GOP_GWIN_Switch2Gwin(g_gwinID);
            msAPI_OSD_SetClipWindow(0, 0, PANEL_WIDTH*3/4, PANEL_HEIGHT/4);
            msAPI_OSD_DrawBlock(&clrBtn);

            clrBtn.x = 20;
            //clrBtn.width = PANEL_WIDTH/2;
            //clrBtn.height =  PANEL_HEIGHT/2;
            clrBtn.t_clr = COLOR_WHITE;
            clrBtn.b_clr = 0x020202;
            clrBtn.Fontfmt.flag = GEFONT_FLAG_VARWIDTH;
            clrBtn.enTextAlign = EN_ALIGNMENT_LEFT;
            clrBtn.bStringIndexWidth = CHAR_IDX_1BYTE;

            msAPI_OSD_DrawText(Font[FONT_0].fHandle, (U8 *)warningMsg, &clrBtn);

            MApi_GOP_GWIN_SetBlending(g_gwinID, TRUE, 63);
            MApi_GOP_GWIN_Enable(g_gwinID, ENABLE);
        }
    }
    else if(bShow==FALSE && g_gwinID != GWIN_NO_AVAILABLE)
    {
       MApi_GOP_GWIN_Enable(g_gwinID, DISABLE);
       MApi_GOP_GWIN_DeleteWin(g_gwinID);
       g_gwinID = GWIN_NO_AVAILABLE;
    }
#else
    UNUSED(bShow);
    UNUSED(warningMsg);
#endif
}

void msAPI_AEON_Disable(void)
{
#if (MHEG5_ENABLE)
    msAPI_MHEG5_SetBinStatus(FALSE);
#endif

#if(SUPPORT_AEON_MM)
    MDrv_COPRO_Disable();
#endif
}

void msAPI_Aeon_ReInitial(U16 u16AeonBinID)
{
    UNUSED(u16AeonBinID);
}
/*
void msAPI_BEON_Disable(void)
{
#if (MHEG5_ENABLE)
    msAPI_MHEG5_SetBinStatus(FALSE);
#endif

    MDrv_COPRO_Disable();
}
*/


//******************************************************************************

#undef _MSAPI_DRVINIT_C_

//******************************************************************************

#endif // #ifndef _MSAPI_DRVINIT_C_

