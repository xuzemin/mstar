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
/// @file  drvpower.c
/// @brief power Module
/// @author MStar Semiconductor Inc.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVPOWER_C_
#define _DRVPOWER_C_

////////////////////////////////////////////////////////////////////////////////
// Include List
////////////////////////////////////////////////////////////////////////////////
//$ Hal & CPU
#include "hwreg.h" //"hwreg_S4LE.h" //2009/06/18
//$ Utility
#include "drvGlobal.h"
#include "drvTSP.h"
//#include "drvCPU.h"
//$ Priviate
//$ Interface
#include "drvpower_if.h"
#include "drvISR.h"
#include "drvMIU.h"
#include "debug.h" //2009/06/18
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
////////////////////////////////////////////////////////////////////////////////
// Local defines & local structures
////////////////////////////////////////////////////////////////////////////////
#define DRVPOWER_DBG(x)
#define ANALOG_IP       ENABLE
#define DIGITAL_IP      ENABLE

////////////////////////////////////////////////////////////////////////////////
// Global Variables
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Extern Function
////////////////////////////////////////////////////////////////////////////////
extern bit  MDrv_Sys_IsCodeInSPI( void );
extern void MDrv_Sys_RunCodeInSPI( void );
extern void MDrv_Sys_Reboot( void );
static U8 caVerInfo[33] =
{
    VER_CHECK_HEADER    // 0,0 fixed
    ,PWR_LIB_ID         // LIB ID
    ,PWR_INTERFACE_VER  // MIU Interface Version
    ,PWR_BUILD_VER      // MIU SW LIB Version
    ,CHANGE_LIST_NUM    // Change List 00000
    ,PRODUCT_NAME       // PRODUCT
    ,CUSTOMER_NAME      // CUSTOMER
    ,DEVELOP_STAGE      // Develop Stage
    ,OS_VERSION         // OS
    ,CHECK_SUM          // check sum
};

////////////////////////////////////////////////////////////////////////////////
// Global Function
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_GetVerInfo
/// @brief \b Function  \b Description: Get power library version informaiton
/// @param <IN>         \b None:
/// @param <OUT>        \b **ppVerInfo: pointer to a U8 string stored verion information
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b caVer: Library version information
////////////////////////////////////////////////////////////////////////////////
void MDrv_Power_GetVerInfo(U8 **ppVerInfo)
{
    *ppVerInfo = (U8 *)caVerInfo;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_CheckAnalogIP
/// @brief \b Function  \b Description: This function check if support analog IP
/// @param <IN>         \b None :
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE : Support analog IP
///                     \b FALSE: Not Support analog IP
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MDrv_Power_CheckAnalogIP(void)
{
    DRVPOWER_DBG(printf("Analog IP:%u\n", ANALOG_IP));
    return (ANALOG_IP);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_CheckAnalogIP
/// @brief \b Function  \b Description: This function check if support digital IP
/// @param <IN>         \b None :
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE : Support digital IP
///                     \b FALSE: Not Support digital IP
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MDrv_Power_CheckDigitIP(void)
{
    DRVPOWER_DBG(printf("Digital IP:%u\n", DIGITAL_IP));
    return (DIGITAL_IP);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_SetMode
/// @brief \b Function  \b Description: Setting power mode
/// @param <IN>         \b u8Mode : PM_MODE_ON, PM_MODE_OFF_EXEC, PM_MODE_OFF, PM_MODE_ON_EXEC
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE : Support digital IP
/// @param <RET>        \b FALSE: Not Support digital IP
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Power_SetMode(U8 u8Mode)
{
    MDrv_WriteByteMask(PM_OFF_FLAG, u8Mode, PM_MODE_MASK);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_SetMode
/// @brief \b Function  \b Description: Setting power mode
/// @param <IN>         \b u8Mode : PM_MODE_ON, PM_MODE_OFF_EXEC, PM_MODE_OFF, PM_MODE_ON_EXEC
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE : Support digital IP
/// @param <RET>        \b FALSE: Not Support digital IP
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Set_Power_Flag(U8 u8Mode, U8 u8Flag)
{
    MDrv_WriteRegBit(PM_OFF_FLAG, u8Flag, u8Mode);
}

////////////////////////////////////////////////////////////////////////////////
U8 MDrv_Get_Power_Flag(U8 u8Flag)
{
    return( ( MDrv_ReadByte(PM_OFF_FLAG) & u8Flag )? 1: 0 ) ;
}


////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_Is1STBootUp
/// @brief \b Function  \b Description: Checking if the system is 1st boot up
/// @param <IN>         \b u8Chk1stBootMode: CHECK_PM_OFF_FLAG ,CHECK_RTC_OCLOCK
/// @param <IN>         \b u32SysTime: Current system time
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE : 1st Bootup
/// @param <RET>        \b FALSE: Not 1st Bootup
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MDrv_Power_Is1STBootUp(U8 u8Chk1stBootMode, U32 u32SysTime)
{
    if (u8Chk1stBootMode == CHECK_RTC_OCLOCK)
    {
        if(u32SysTime < 10)
            return TRUE;
    }
    else if(u8Chk1stBootMode == CHECK_PM_OFF_FLAG)
    {
        if ( !(MDrv_ReadByte(PM_OFF_FLAG) & PM_FIRST_BOOTUP) )
        {
            MDrv_WriteRegBit(PM_OFF_FLAG, ENABLE, PM_FIRST_BOOTUP);
            return TRUE;
        }
    }

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_IsPowerDown
/// @brief \b Function  \b Description: Checking if it is power down mode
/// @param <IN>         \b None:
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE : Power down
/// @param <RET>        \b FALSE: Not Power down
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
BOOLEAN MDrv_Power_IsPowerDown()
{
    U8 u8PDFunc = 0;

    if(!(MDrv_ReadByte(PM_OFF_FLAG) & PM_FIRST_BOOTUP))
    {
        MDrv_WriteRegBit(PM_OFF_FLAG, ENABLE, PM_FIRST_BOOTUP);
    }

    if((MDrv_ReadByte(PM_OFF_FLAG) & PM_MODE_MASK) == PM_MODE_OFF_EXEC)
    {

        switch(MDrv_ReadByte(PM_OFF_FLAG) & PM_PDMODE_MASK)
        {
            case PM_PDMODE_S1:
                u8PDFunc = PDF_EXT_DEVICE + PDF_ANA;
                break;
            case PM_PDMODE_S2:
                u8PDFunc = PDF_EXT_DEVICE + PDF_ANA;
                break;
            case PM_PDMODE_S3:
                u8PDFunc = PDF_EXT_DEVICE + PDF_ANA + PDF_DIG + PDF_SDR + PDF_MPLL + PDF_ACLK;
                break;
            case PM_PDMODE_S4:
                u8PDFunc = PDF_EXT_DEVICE + PDF_ANA + PDF_DIG + PDF_SDR + PDF_MPLL + PDF_ACLK + PDF_HWAKEUP;
                break;
            default:
                return FALSE;
        }

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_Set_PDMode
/// @brief \b Function  \b Description: Set power down mode
/// @param <IN>         \b u8Mode:POWERMODE_S1,POWERMODE_S2,POWERMODE_S3,POWERMODE_S4
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Power_Set_PDMode(U8 u8Mode)
{
    U8 u8PDFunc = 0;
    u8Mode = PM_PDMODE_S1;  //marlon always setting PM_PDMODE_S1,marlon STR watch this PM_OFF_FLAG register, this function no used, need refine
    MDrv_WriteRegBit(PM_OFF_FLAG, DISABLE, PM_PDMODE_MASK);
    switch(u8Mode)
    {
        case POWERMODE_S1:
            MDrv_WriteRegBit(PM_OFF_FLAG, ENABLE, PM_PDMODE_S1);
            u8PDFunc = PDF_EXT_DEVICE + PDF_ANA;
            break;
        case POWERMODE_S2:
            MDrv_WriteRegBit(PM_OFF_FLAG, ENABLE, PM_PDMODE_S2);
            u8PDFunc = PDF_EXT_DEVICE + PDF_ANA;
            break;
        case POWERMODE_S3:
            MDrv_WriteRegBit(PM_OFF_FLAG, ENABLE, PM_PDMODE_S3);
            u8PDFunc = PDF_EXT_DEVICE + PDF_ANA + PDF_DIG + PDF_SDR + PDF_MPLL + PDF_ACLK;
            break;
        case POWERMODE_S4:
            MDrv_WriteRegBit(PM_OFF_FLAG, ENABLE, PM_PDMODE_S4);
            u8PDFunc = PDF_EXT_DEVICE + PDF_ANA + PDF_DIG + PDF_SDR + PDF_MPLL + PDF_ACLK + PDF_HWAKEUP;
            break;

        default:
            ASSERT(0);
            break;
    }
}


////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_Init
/// @brief \b Function  \b Description: Initial all global variables
/// @param <IN>         \b None:
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Power_Init()
{
    // set power flag to standby mode
    g_eOnTimerDateForStandBy = 0;
    g_eDayOfWeekForStandBy = 0;
    g_eOnTimerDate = 0;
    g_bWakeUpByOnTimer = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_ResetAndPowerUp
/// @brief \b Function  \b Description: Reset and poer on again
/// @param <IN>         \b None:
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Power_ResetAndPowerUp(void)
{
    // Change power management status
    MDrv_WriteByteMask(PM_OFF_FLAG, PM_MODE_ON_EXEC, PM_MODE_MASK);
    MDrv_WriteRegBit(PM_OFF_FLAG, DISABLE, PM_P3_RESET_FLAG);

    // disable interrupt.
    MsOS_CPU_DisableInterrupt();

    MsOS_CPU_MaskAllInterrupt();

    MsOS_DisableAllInterrupts();

    if (!MDrv_Sys_IsCodeInSPI())
    {
        MDrv_Sys_RunCodeInSPI();
    }

    MDrv_Sys_Reboot();
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_Saving_Mode
/// @brief \b Function  \b Description: Power saving mode for some HW module: GE,
///                         MPEG, DEMUX or DVBPLL (Right now only MPEG is used??)
/// @param <IN>         \b u8Flag: PSM_MPEG, PSM_DEMUX,PSM_GE,PSM_DVBPLL
/// @param <IN>         \b bEnable: Enable power saving mode
///                         --Disable   (0)
///                         --Enable    (1)
/// @param <IN>         \b bPwrSaveT: Enable Power saving for TSP
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_Power_Saving_Mode(U8 u8Flag, BOOLEAN bEnable, BOOLEAN bPwrSaveT)
{
    if(bEnable)
    {
        DRVPOWER_DBG(printf("MDrv_Power_Saving_Mode(Enable):0x%02bX\n", u8Flag));

        // GE Releated
        if (u8Flag & PSM_GE)
            MDrv_Power_Set_HwClock(E_HWCLK_GE_ONOFF, POWER_DOWN);

        // MPEG Releated
        if (u8Flag & PSM_MPEG)
        {
            MDrv_Power_Set_HwClock(E_HWCLK_MVD_ONOFF, POWER_DOWN);
            MDrv_Power_Set_HwClock(E_HWCLK_MVDBOOT_ONOFF, POWER_DOWN);
            MDrv_Power_Set_HwClock(E_HWCLK_DC0_ONOFF, POWER_DOWN);
        }

        // Demux Releated
        if (u8Flag & PSM_DEMUX)
        {
            MDrv_Power_Set_HwClock(E_HWCLK_TSP_ONOFF, POWER_DOWN);
            MDrv_Power_Set_HwClock(E_HWCLK_TS0_ONOFF, POWER_DOWN);
            MDrv_Power_Set_HwClock(E_HWCLK_TSOUT_ONOFF, POWER_DOWN);
            MDrv_Power_Set_HwClock(E_HWCLK_STC0_ONOFF, POWER_DOWN);
        }
    }
    else
    {
        DRVPOWER_DBG(printf("MDrv_Power_Saving_Mode(Disable):0x%02bX\n", u8Flag));

        // MPEG Releated
        if (u8Flag & PSM_MPEG)
        {
            MDrv_Power_Set_HwClock(E_HWCLK_MVD_ONOFF, POWER_ON);
            MDrv_Power_Set_HwClock(E_HWCLK_MVDBOOT_ONOFF, POWER_ON);
            MDrv_Power_Set_HwClock(E_HWCLK_DC0_ONOFF, POWER_ON);
        }

        // Demux Releated
        if (u8Flag & PSM_DEMUX)
        {
            if (!bPwrSaveT)
            {
                MDrv_Power_Set_HwClock(E_HWCLK_TSP_ONOFF, POWER_ON);
                MDrv_Power_Set_HwClock(E_HWCLK_TS0_ONOFF, POWER_ON);
                MDrv_Power_Set_HwClock(E_HWCLK_TSOUT_ONOFF, POWER_ON);
                MDrv_Power_Set_HwClock(E_HWCLK_STC0_ONOFF, POWER_ON);
                MsOS_DelayTask(2);
            }
        }

        // GE Releated
        if (u8Flag & PSM_GE)
            MDrv_Power_Set_HwClock(E_HWCLK_GE_ONOFF, POWER_ON);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_Power_Set_HwClock
/// @brief \b Function  \b Description: Setting HW module clock on/off/setting.
/// @param <IN>         \b eModule: HW module
/// @param <IN>         \b eValue: Enalbe HW clock
///                         --Disable   (0)
///                         --Enable    (1)
/// @param <OUT>        \b None :
/// @param <RET>        \b TRUE: Success.
/// @param <RET>        \b TRUE: Failure
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
Bool MDrv_Power_Set_HwClock (HW_MODULE_CLOCK_SETTING eModule, int eValue)
{
    Bool bRet = TRUE;

    switch(eModule)
    {
    // Setting MCU HW CLock
    case E_HWCLK_MCU_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x45), eValue, BIT0);
        break;
    case E_HWCLK_MCU_SETTING:
        MDrv_WriteByteMask(BK_CHIPTOP(0x22), eValue, BIT0);
        break;

    // Setting AEON HW CLock
    case E_HWCLK_AEON_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x26), (eValue<<6), BIT6);
        break;

    // Setting MIU HW CLock
    case E_HWCLK_MIU_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x25), (eValue<<4), BIT4);
        break;

    // Setting TSP HW CLock
    case E_HWCLK_TSP_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x27), (eValue<<4), BIT4);
        break;
    case E_HWCLK_TS0_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x26), eValue, BIT0);
        break;
    case E_HWCLK_TS2_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x3A), eValue, BIT0);
        break;
    case E_HWCLK_TSOUT_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x3A), (eValue<<4), BIT4);
        break;

    // Setting STC0 HW CLock
    case E_HWCLK_STC0_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x27), (eValue<<4), BIT4);
        break;

    // Setting MADSTC HW CLock
    case E_HWCLK_MADSTC_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x28), (eValue<<4), BIT4);
        break;

    // Setting MVD HW CLock
    case E_HWCLK_MVD_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x29), (eValue<<4), BIT4);
        break;
    case E_HWCLK_MVDBOOT_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x29), eValue, BIT0);
        break;

    // Setting M4V HW CLock
    case E_HWCLK_M4V_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2A), eValue, BIT0);
        break;

    // Setting DC0 HW CLock
    case E_HWCLK_DC0_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2A), (eValue<<4), BIT4);
        break;

    // Setting DHC HW CLock
    case E_HWCLK_DHC_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2F), eValue, BIT0);
        MDrv_WriteByteMask(BK_CHIPTOP(0x2B), eValue, BIT0);
        MDrv_WriteByteMask(BK_CHIPTOP(0x58), eValue, BIT0);
        MDrv_WriteByteMask(BK_CHIPTOP(0x58), (eValue<<2), BIT2);
        MDrv_WriteByteMask(BK_CHIPTOP(0x59), eValue, BIT0);
        MDrv_WriteByteMask(BK_CHIPTOP(0x59), (eValue<<6), BIT6);
        break;

    // Setting GE HW CLock
    case E_HWCLK_GE_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2B), (eValue<<4), BIT4);
        break;

    // Setting GOP HW CLock
    case E_HWCLK_GOP0_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2C), eValue, BIT0);
        break;
    case E_HWCLK_GOP1_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2C), (eValue<<4), BIT4);
        break;
    case E_HWCLK_GOPD_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2D), eValue, BIT0);
        break;

    // Setting VD HW CLock (VD/VDMCU/VD200)
    case E_HWCLK_VD_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x2D), (eValue<<4), BIT4);
        MDrv_WriteByteMask(BK_CHIPTOP(0x2E), eValue, BIT0);
        MDrv_WriteByteMask(BK_CHIPTOP(0x2E), (eValue<<4), BIT4);
        break;

    // Setting VE HW CLock (VE/VEDAC/VEIN)
    case E_HWCLK_VE_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x33), eValue, BIT0);
        MDrv_WriteByteMask(BK_CHIPTOP(0x33), (eValue<<4), BIT4);
        MDrv_WriteByteMask(BK_CHIPTOP(0x38), eValue, BIT0);
        break;

    // Setting STRLD HW CLock
    case E_HWCLK_STRLD_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x44), eValue, BIT0);
        break;

    // Setting DDR HW CLock
    case E_HWCLK_DDR_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x25), eValue, BIT0);
        break;

    // Setting DAC HW CLock
    case E_HWCLK_DAC_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x34), eValue, BIT0);
        break;

    // Setting USB HW CLock
    case E_HWCLK_USB_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x24), eValue, BIT0);
        break;

    // Setting PCMCIA HW CLock
    case E_HWCLK_PCMCIA_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x31), (eValue<<4), BIT4);
        break;

    // Setting FCIE HW CLock (Card Reader)
    case E_HWCLK_FCIE_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x39), eValue, BIT0);
        break;

    // Setting FCLK HW CLock
    case E_HWCLK_FCLK_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x35), eValue, BIT0);
        break;

    // Setting FMCLK HW CLock
    case E_HWCLK_FMCLK_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x36), eValue, BIT0);
        break;

    // Setting ODCLK HW CLock
    case E_HWCLK_ODCLK_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x37), eValue, BIT0);
        break;

    // Setting FICLKF2 HW CLock
    case E_HWCLK_FICLKF2_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x30), (eValue<<4),BIT4);
        break;

    // Setting IDCLK2 HW CLock
    case E_HWCLK_IDCLK2_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x3F), eValue, BIT0);
        break;

    // Setting TCK HW CLock
    case E_HWCLK_TCK_ONOFF:
        MDrv_WriteByteMask(BK_CHIPTOP(0x26), (eValue<<4), BIT4);
        break;

    default:
        bRet = FALSE;
        break;
    }

    return bRet;
}

//$$$$ =========================================================================
//$$$$ Analog IP
//$$$$ =========================================================================
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForLvdsSet
/// @brief \b Function  \b Description: Set power save for Lvds
/// @param <IN>         \b None:
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForLvdsSet(void)
{
    MDrv_WriteByte(0x32f0,0x46);

    MDrv_WriteByte(0x32DA , 0x50);
    MDrv_WriteByte(0x32DB , 0x55);
    MDrv_WriteByte(0x32DC , 0x55);
    MDrv_WriteByte(0x32DD , 0x05);
    MDrv_WriteByte(0x32DE , 0x00);
    MDrv_WriteByte(0x32DF , 0x00);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForAdcSet
/// @brief \b Function  \b Description: Set power save for ADC
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForAdcSet(PowerSaveIndi_t PsIndi)
{
    if(PsIndi.AdcR)
        MDrv_WriteRegBit(PM_ADC_RGB, 1, BIT5); //PM_ADC_R OFF
    else
        MDrv_WriteRegBit(PM_ADC_RGB, 0, BIT5); //PM_ADC_R ON

    if(PsIndi.AdcG)
        MDrv_WriteRegBit(PM_ADC_RGB, 1, BIT6); //PM_ADC_G OFF
    else
        MDrv_WriteRegBit(PM_ADC_RGB, 0, BIT6); //PM_ADC_G ON

    if(PsIndi.AdcB)
        MDrv_WriteRegBit(PM_ADC_RGB, 1, BIT7); //PM_ADC_B OFF
    else
        MDrv_WriteRegBit(PM_ADC_RGB, 0, BIT7); //PM_ADC_B ON

    if(PsIndi.AdcY)
        MDrv_WriteRegBit(PM_ADC_Y, 1, BIT6);   //PM_ADC_Y OFF
    else
        MDrv_WriteRegBit(PM_ADC_Y, 0, BIT6);   //PM_ADC_Y ON

}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForGmcSet
/// @brief \b Function  \b Description: Set power save for Gmc
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForGmcSet(PowerSaveIndi_t PsIndi)
{
    PsIndi.Vd=PsIndi.Vd; //removed warnning message
    #if 0  //  T3 bringup , refine later
    //$ GMC
    // BIT2 should always be 0
    if(PsIndi.Gmcp)
        MDrv_WriteByte(PM_GMC, (MDrv_ReadByte(PM_GMC) | 0x18));
    else
        MDrv_WriteByte(PM_GMC, (MDrv_ReadByte(PM_GMC) & (~0x1C)));

    if(PsIndi.GmcY)
        MDrv_WriteByte(PM_GMC, (MDrv_ReadByte(PM_GMC) | BIT1));
    else
        MDrv_WriteByte(PM_GMC, (MDrv_ReadByte(PM_GMC) & (~BIT1)));

    if(PsIndi.GmcC)
        MDrv_WriteByte(PM_GMC, (MDrv_ReadByte(PM_GMC) | BIT0));
    else
        MDrv_WriteByte(PM_GMC, (MDrv_ReadByte(PM_GMC) & (~BIT0)));
    #endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForCvbsBufOutSet
/// @brief \b Function  \b Description: Set power save for CvbsBufOut
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForCvbsBufOutSet(PowerSaveIndi_t PsIndi)
{
    //$ CVBS BUF OUT
    if (PsIndi.CvbsBufOut)
    {
        MDrv_WriteRegBit(PM_CVBS_BUF_OUT, 1, BIT0); //power down CVBS buffer out 1: cvbso1
        MDrv_WriteRegBit(PM_CVBS2_BUF_OUT, 1, BIT0); //power down CVBS buffer out 2: cvbso2
    }
    else
    {
        MDrv_WriteRegBit(PM_CVBS_BUF_OUT, 0, BIT0); //power on CVBS buffer out 1: cvbso1
        MDrv_WriteRegBit(PM_CVBS2_BUF_OUT, 0, BIT0); //power on CVBS buffer out 1: cvbso2
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForDacCvbsSet
/// @brief \b Function  \b Description: Set power save for DacCvbs
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForDacCvbsSet(PowerSaveIndi_t PsIndi)
{
    //$ DAC_CVBS
    if (PsIndi.DacCvbs)
    {
        MDrv_WriteRegBit(PM_DAC_CVBS, 0, BIT3); //OFF
        MDrv_WriteRegBit(PM_DAC_CVBS2, 0, BIT3); //OFF
    }
    else
    {
        MDrv_WriteRegBit(PM_DAC_CVBS, 1, BIT3); //ON
        MDrv_WriteRegBit(PM_DAC_CVBS2, 1, BIT3); //ON
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForBandGapBiasSet
/// @brief \b Function  \b Description: Set power save for BandGapBias
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForBandGapBiasSet(PowerSaveIndi_t PsIndi)
{
    #if 1  //  T3 bringup , refine later
    if(PsIndi.VRefPdn)
        MDrv_WriteRegBit(PM_ADC_RGB, 1, BIT2); //power down bandgap
    else
        MDrv_WriteRegBit(PM_ADC_RGB, 0, BIT2); //power on bandgap
    #else
    MDrv_WriteByte(PM_ADC_VCTRL_L, 0x1E);//0x1E;
    MDrv_WriteByte(PM_ADC_VCTRL_H, 0x00);
    MDrv_WriteByte(PM_ADC_VTRL_YC_L, 0x1E);//0x1E;
    MDrv_WriteByte(PM_ADC_VTRL_YC_H, 0x00);

    if(PsIndi.VRefPdn)
    {
        MDrv_WriteByte(0x25BA, (MDrv_ReadByte(0x25BA) | BIT0));
        MDrv_WriteByte(0x25B9, (MDrv_ReadByte(0x25B9) | BIT6));
        MDrv_WriteByte(0x25B9, (MDrv_ReadByte(0x25B9) | BIT7));
    }
    else
    {
        MDrv_WriteByte(0x25BA, (MDrv_ReadByte(0x25BA) & (~BIT0)));
        MDrv_WriteByte(0x25B9, (MDrv_ReadByte(0x25B9) & (~BIT6)));
        MDrv_WriteByte(0x25B9, (MDrv_ReadByte(0x25B9) & (~BIT7)));
    }
    #endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForFastBlankingSet
/// @brief \b Function  \b Description: Set power save for FastBlanking
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForFastBlankingSet(PowerSaveIndi_t PsIndi)
{
    if(PsIndi.FastBlanking)// OFF
    {
         MDrv_WriteRegBit(PM_ADC_FBLANK, 1, BIT6);
    }
    else// ON
    {
        MDrv_WriteRegBit(PM_ADC_FBLANK, 0, BIT6);
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForAdcRgbBiasCurrentControlSet
/// @brief \b Function  \b Description: Set power save for AdcRgbBiasCurrentControl
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForAdcRgbBiasCurrentControlSet(PowerSaveIndi_t PsIndi)
{
#if 1  //  T3 bringup , refine later
    if(PsIndi.AdcRgbBiasCurrentControl)
    {
        MDrv_WriteRegBit(PM_ADC_Y, 1, BIT2);//1: power down I-clamp on RGB channel
        MDrv_WriteRegBit(PM_ADC_Y, 1, BIT3);//1: power down I-clamp on VD-Y channel
        MDrv_WriteRegBit(PM_ADC_Y, 1, BIT4);//1: power down I-clamp on VD-C channel
    }
    else
    {
        MDrv_WriteRegBit(PM_ADC_Y, 0, BIT2);//1: power on I-clamp on RGB channel
        MDrv_WriteRegBit(PM_ADC_Y, 0, BIT3);//1: power on I-clamp on VD-Y channel
        MDrv_WriteRegBit(PM_ADC_Y, 0, BIT4);//1: power on I-clamp on VD-C channel
    }

#else
    if(PsIndi.AdcRgbBiasCurrentControl)
    {
        MDrv_WriteByte(PM_ADC_ICTRL_RGB_L, 0x65);//0x65;
        MDrv_WriteByte(PM_ADC_ICTRL_RGB_H, 0x05);
        MDrv_WriteByte(PM_ADC_ICTRL_YC_L, 0x65);//0x65;
        MDrv_WriteByte(PM_ADC_ICTRL_YC_H, 0x05);
    }
    else
    {
        MDrv_WriteByte(PM_ADC_ICTRL_RGB_L, 0x65);//0x65;
        MDrv_WriteByte(PM_ADC_ICTRL_RGB_H, 0x05);
        MDrv_WriteByte(PM_ADC_ICTRL_YC_L, 0x65);//0x65;
        MDrv_WriteByte(PM_ADC_ICTRL_YC_H, 0x05);
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForAudio
/// @brief \b Function  \b Description: Set power save for Audio
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForAudio(PowerSaveIndi_t PsIndi)
{
    if(PsIndi.Audio)
    {
        MDrv_WriteByte(0x2ce0, 0x50); // Audio codec save AU 7mA
        MDrv_WriteByte(0x2ce1, 0x55); // Audio codec save AU 7mA
    }
    else
    {
        MDrv_WriteByte(0x2ce0, 0x00);
        MDrv_WriteByte(0x2ce1, 0x00);
    }
}

//$$$$ =========================================================================
//$$$$ Digital IP
//$$$$ =========================================================================
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForVdSet
/// @brief \b Function  \b Description: Set power save for VD
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForVdSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Vd=PsIndi.Vd; //removed warnning message
#if 0   //  T3 bringup , refine later
    if (PsIndi.Vd)
    {
        MDrv_WriteByte(0x3613, (MDrv_ReadByte(0x3613) | BIT6));// COMB SW reset
        MDrv_WriteByte(0x3801, (MDrv_ReadByte(0x3801) | BIT7));// SECAM SW reset
        MDrv_WriteByte(0x3770, (MDrv_ReadByte(0x3770) | BIT3));// VBI DEC SW reset

        MDrv_WriteByte(0x3514, (MDrv_ReadByte(0x3514) | BIT7));// AFEC SW reset
        MDrv_WriteByte(0x130C, (MDrv_ReadByte(0x130C) | BIT0));// VD_MCU reset

        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) | BIT3));// MIU0 group0 ttxsk(VD) W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) | BIT0));// MIU0 group1 VD(comb) W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) | BIT1));// MIU0 group1 VD(comb) R
        MDrv_WriteByte(0x1287, (MDrv_ReadByte(0x1287) | BIT0));// MIU0 group2 ttx(VD) R/W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) | BIT0));// MIU1 group1 VD(comb) W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) | BIT1));// MIU1 group1 VD(comb) R

        MDrv_WriteRegBit(REG_CKG_VDS, 1, BIT0);    //REG_CKG_VDS
        MDrv_WriteRegBit(REG_CKG_VDS, 1, BIT4);    //REG_CKG_VDS
        MDrv_WriteRegBit(REG_CKG_VDGOPD, 1, BIT4); //REG_CKG_VDGOPD
    }
    else
    {
        MDrv_WriteRegBit(REG_CKG_VDS, 0, BIT0);    //REG_CKG_VDS
        MDrv_WriteRegBit(REG_CKG_VDS, 0, BIT4);    //REG_CKG_VDS
        MDrv_WriteRegBit(REG_CKG_VDGOPD,  0, BIT4); //REG_CKG_VDGOPD
        MDrv_WriteByte(0x3613, (MDrv_ReadByte(0x3613) & (~BIT6))); // COMB SW reset
        MDrv_WriteByte(0x3801, (MDrv_ReadByte(0x3801) & (~BIT7))); // SECAM SW reset
        MDrv_WriteByte(0x3770, (MDrv_ReadByte(0x3770) & (~BIT3))); // VBI DEC SW reset

        MDrv_WriteByte(0x3514, (MDrv_ReadByte(0x3514) & (~BIT7))); // AFEC SW reset
        MDrv_WriteByte(0x130C, (MDrv_ReadByte(0x130C) & (~BIT0))); // VD_MCU reset

        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) & (~BIT3)));// MIU0 group0 ttxsk(VD) W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) & (~BIT0)));// MIU0 group1 VD(comb) W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) & (~BIT1)));// MIU0 group1 VD(comb) R
        MDrv_WriteByte(0x1287, (MDrv_ReadByte(0x1287) & (~BIT0)));// MIU0 group2 ttx(VD) R/W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) & (~BIT0)));// MIU1 group1 VD(comb) W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) & (~BIT1)));// MIU1 group1 VD(comb) R
        //run VD IP on procedure ....????
    }
 #endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForSVdSet
/// @brief \b Function  \b Description: Set power save for SVD
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForSvdSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Svd=PsIndi.Svd;   //removed warnning
#if 0   //  T3 bringup , refine later

     //$ SVD ==================================================
    if (PsIndi.Svd)
    {
        MDrv_WriteByte(REG_SVD_SW_RST , (REG_SVD_RESET_CPURST|REG_SVD_RESET_SWRST));
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) | BIT4));// MIU0 group0 svd_db R
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) | BIT5));// MIU0 group0 svd_db W
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) | BIT0));// MIU0 group2 svd_en R
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) | BIT6));// MIU0 group2 svdintp R
        MDrv_WriteByte(0x0646, (MDrv_ReadByte(0x0646) | BIT7));// MIU1 group0 svd_en R
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) | BIT0));// MIU1 group0 svd_db R
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) | BIT1));// MIU1 group0 svdintp R
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) | BIT2));// MIU1 group0 svd_db W
        MDrv_WriteRegBit(0x1E58, 1, BIT0);     //CKG_SVD OFF
    }
    else
    {
        MDrv_WriteRegBit(0x1E58, 0, BIT0);      //CKG_SVD on
        // SVD ENG SW reset release
        MDrv_WriteByte(REG_SVD_SW_RST, (MDrv_ReadByte(REG_SVD_SW_RST) & (~REG_SVD_RESET_SWRST)));
        // SVD CPU SW reset release
        MDrv_WriteByte(REG_SVD_SW_RST, (MDrv_ReadByte(REG_SVD_SW_RST) & (~REG_SVD_RESET_CPURST)));

        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) & (~BIT4)));// MIU0 group0 svd_db R
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) & (~BIT5)));// MIU0 group0 svd_db W
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) & (~BIT0)));// MIU0 group2 svd_en R
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) & (~BIT6)));// MIU0 group2 svdintp R
        MDrv_WriteByte(0x0646, (MDrv_ReadByte(0x0646) & (~BIT7)));// MIU1 group0 svd_en R
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) & (~BIT0)));// MIU1 group0 svd_db R
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) & (~BIT1)));// MIU1 group0 svdintp R
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) & (~BIT2)));// MIU1 group0 svd_db W
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForCytlifSet
/// @brief \b Function  \b Description: Set power save for Cytlif
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForCytlifSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Cytlif=PsIndi.Cytlif;
#if 0   //  T3 bringup , refine later
    //$ cytlif
    if (PsIndi.Cytlif)
        MDrv_WriteRegBit(REG_CKG_TSOUT, 1, BIT0); //OFF
    else
        MDrv_WriteRegBit(REG_CKG_TSOUT, 0, BIT0); //ON
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForMvdM4vSet
/// @brief \b Function  \b Description: Set power save for MvdM4v
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForMvdM4vSet(PowerSaveIndi_t PsIndi)
{
PsIndi.MvdM4V=PsIndi.MvdM4V;
#if 0   //  T3 bringup , refine later
    if (PsIndi.MvdM4V)
    {
        MDrv_WriteByte(MVD_CTRL, (MDrv_ReadByte(MVD_CTRL) | BIT0));// MVD SW reset
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) | BIT6));// MIU0 group2 MVD R
        MDrv_WriteByte(0x1287, (MDrv_ReadByte(0x1287) | BIT3));// MIU0 group2 MVD W
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) | BIT1));// MIU1 group0 MVD R
        MDrv_WriteByte(0x0687, (MDrv_ReadByte(0x0687) | BIT3));// MIU1 group2 MVD W
        MDrv_WriteByte(REG_CKG_MVD, (MDrv_ReadByte(REG_CKG_MVD) | CKG_MVD_GATED));
        MDrv_WriteByte(REG_MVD_BOOT, (MDrv_ReadByte(REG_MVD_BOOT) | CKG_MVD_BOOT_GATED));
        MDrv_WriteByte(REG_CKG_MVD_IAP_RMEM, (MDrv_ReadByte(REG_CKG_MVD_IAP_RMEM) | CKG_MVD_IAP_RMEM_GATED));
    }
    else
    {
        MDrv_WriteByte(REG_CKG_MVD, (MDrv_ReadByte(REG_CKG_MVD) & (~CKG_MVD_GATED)));
        MDrv_WriteByte(REG_MVD_BOOT, (MDrv_ReadByte(REG_MVD_BOOT) & (~CKG_MVD_BOOT_GATED)));
        MDrv_WriteByte(REG_CKG_MVD_IAP_RMEM, (MDrv_ReadByte(REG_CKG_MVD_IAP_RMEM) & (~CKG_MVD_IAP_RMEM_GATED)));
        MDrv_WriteByte(REG_CKG_MVD, (MDrv_ReadByte(REG_CKG_MVD) | CKG_MVD_BOOT_CLK_MIU));
        MDrv_WriteByte(MVD_CTRL, (MDrv_ReadByte(MVD_CTRL) & (~BIT0))); // MVD SW reset
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) & (~BIT6)));// MIU0 group2 MVD R
        MDrv_WriteByte(0x1287, (MDrv_ReadByte(0x1287) & (~BIT3)));// MIU0 group2 MVD W
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) & (~BIT1)));// MIU1 group0 MVD R
        MDrv_WriteByte(0x0687, (MDrv_ReadByte(0x0687) & (~BIT3)));// MIU1 group2 MVD W
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForDcSet
/// @brief \b Function  \b Description: Set power save for DC
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForDcSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Dc=PsIndi.Dc;
#if 0   //  T3 bringup , refine later
    //$ DC
    if (PsIndi.Dc)
    {
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) | BIT2));// MIU0 group0 TSP R
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) | BIT1));// MIU0 group0 TSP W
        MDrv_WriteRegBit(0x1E2A,    1, BIT4); // OFF
        MDrv_WriteRegBit(REG_CKG_AEON1DC0, 1, BIT0); // OFF
    }
    else
    {
        MDrv_WriteRegBit(0x1E2A,    0, BIT4); //ON
        MDrv_WriteRegBit(REG_CKG_AEON1DC0, 0, BIT0); //ON
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) & (~BIT2)));// MIU0 group0 TSP R
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) & (~BIT1)));// MIU0 group0 TSP W
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForTspSet
/// @brief \b Function  \b Description: Set power save for tsp
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForTspSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Tsp=PsIndi.Tsp;
#if 0   //  T3 bringup , refine later
    //TSP
    if (PsIndi.Tsp)
    {
        MDrv_WriteRegBit(REG_CKG_AEONTS0, 1, BIT0); //REG_CKG_AEONTS0
        MDrv_WriteRegBit(REG_CKG_STC0TSP, 1, BIT0); //REG_CKG_STC0TSP
    }
    else
    {
        MDrv_WriteRegBit(REG_CKG_AEONTS0, 0, BIT0); //REG_CKG_AEONTS0
        MDrv_WriteRegBit(REG_CKG_STC0TSP, 0, BIT0); //REG_CKG_STC0TSP

        // Need SW reset
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForVeet
/// @brief \b Function  \b Description: Set power save for Ve
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForVeSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Ve=PsIndi.Ve;
#if 0   //  T3 bringup , refine later
    if (PsIndi.Ve)
    {
        MDrv_WriteByte(0x3B00, 0x0); //Off VE IP
        MDrv_WriteByte(0x3B00, (MDrv_ReadByte(0x3B00) | BIT4));// SW reset
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) | BIT0));// MIU0 group0 VE W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) | BIT2));// MIU0 group1 VE W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) | BIT3));// MIU0 group1 VE R
        MDrv_WriteByte(0x0666, (MDrv_ReadByte(0x0666) | BIT5));// MIU0 group1 VE W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) | BIT2));// MIU0 group1 VE W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) | BIT3));// MIU0 group1 VE R
        MDrv_WriteByte(REG_CKG_VE, (MDrv_ReadByte(REG_CKG_VE) | CKG_VE_GATED));
        MDrv_WriteByte(REG_CKG_VEDAC, (MDrv_ReadByte(REG_CKG_VEDAC) | CKG_VEDAC_GATED));
        MDrv_WriteByte(REG_CKG_VE_IN, (MDrv_ReadByte(REG_CKG_VE_IN) | CKG_VE_IN_GATED));
    }
    else
    {
        MDrv_WriteByte(REG_CKG_VE, (MDrv_ReadByte(REG_CKG_VE) & (~CKG_VE_GATED)));
        MDrv_WriteByte(REG_CKG_VEDAC, (MDrv_ReadByte(REG_CKG_VEDAC) & (~CKG_VEDAC_GATED)));
        MDrv_WriteByte(REG_CKG_VE_IN, (MDrv_ReadByte(REG_CKG_VE_IN) & (~CKG_VE_IN_GATED)));
        MDrv_WriteByte(0x3B00, (MDrv_ReadByte(0x3B00) & (~BIT4)));// SW reset release
        MDrv_WriteByte(0x1247, (MDrv_ReadByte(0x1247) & (~BIT0)));// MIU0 group0 VE W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) & (~BIT2)));// MIU0 group1 VE W
        MDrv_WriteByte(0x1267, (MDrv_ReadByte(0x1267) & (~BIT3)));// MIU0 group1 VE R
        MDrv_WriteByte(0x0666, (MDrv_ReadByte(0x0666) & (~BIT5)));// MIU0 group1 VE W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) & (~BIT2)));// MIU0 group1 VE W
        MDrv_WriteByte(0x0667, (MDrv_ReadByte(0x0667) & (~BIT3)));// MIU0 group1 VE R
        //run VE IP enable procedure ...???????
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForRvdSet
/// @brief \b Function  \b Description: Set power save for Rvd
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForRvdSet(PowerSaveIndi_t PsIndi)
{
PsIndi.Rvd=PsIndi.Rvd;
#if 0   //  T3 bringup , refine later
    if(PsIndi.Rvd)
    {
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) | BIT6));// MIU0 group2 R/W
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) | BIT1));// MIU1 group0 R/W
        MDrv_WriteByte(REG_CKG_RVD, (MDrv_ReadByte(REG_CKG_RVD) | CKG_RVD_GATED));
    }
    else
    {
        MDrv_WriteByte(0x1286, (MDrv_ReadByte(0x1286) & (~BIT6)));// MIU0 group2 R/W
        MDrv_WriteByte(0x0647, (MDrv_ReadByte(0x0647) & (~BIT1)));// MIU1 group0 R/W
        MDrv_WriteByte(REG_CKG_RVD, (MDrv_ReadByte(REG_CKG_RVD) & (~CKG_RVD_GATED)));
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForStrld
/// @brief \b Function  \b Description: Set power save for Strld
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveForStrld(PowerSaveIndi_t PsIndi)
{
PsIndi.Strld=PsIndi.Strld;
#if 0   //  T3 bringup , refine later
    if(PsIndi.Strld)
    {
        MDrv_WriteRegBit(REG_CKG_STRLD,1,CKG_STRLD_GATED);
        MDrv_WriteByte(0x1246, (MDrv_ReadByte(0x1246) | BIT3));// MIU0 group0 W
        MDrv_WriteByte(0x1246, (MDrv_ReadByte(0x1246) | BIT4));// MIU0 group0 R
    }
    else
    {
        MDrv_WriteRegBit(REG_CKG_STRLD,0,CKG_STRLD_GATED);
        MDrv_WriteByte(0x1246, (MDrv_ReadByte(0x1246) & (~BIT3)));// MIU0 group0 W
        MDrv_WriteByte(0x1246, (MDrv_ReadByte(0x1246) & (~BIT4)));// MIU0 group0 R
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForAeon
/// @brief \b Function  \b Description: Set power save for Aeon
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void Mdrv_PowerSaveForAeon(PowerSaveIndi_t PsIndi)
{
PsIndi.Aeon=PsIndi.Aeon;
#if 0   //  T3 bringup , refine later
    if(PsIndi.Aeon)
    {
        MDrv_WriteByte(REG_CKG_AEON, (MDrv_ReadByte(REG_CKG_AEON) | BIT6));
    }
    else
    {
        MDrv_WriteByte(REG_CKG_AEON, (MDrv_ReadByte(REG_CKG_AEON) & (~BIT6)));
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForGopg2
/// @brief \b Function  \b Description: Set power save for Gopg2
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void Mdrv_PowerSaveForGopg2(PowerSaveIndi_t PsIndi)
{
PsIndi.Gopg2=PsIndi.Gopg2;
#if 0   //  T3 bringup , refine later
    if(PsIndi.Gopg2)
    {
        MDrv_WriteByte(REG_CKG_GOPG2, (MDrv_ReadByte(REG_CKG_GOPG2) | BIT0));
    }
    else
    {
        MDrv_WriteByte(REG_CKG_GOPG2, (MDrv_ReadByte(REG_CKG_GOPG2) & (~BIT0)));
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForDTV
/// @brief \b Function  \b Description: Set power save for DTV
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForDTV(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =1;
    pPsIndi->AdcG           =1;
    pPsIndi->AdcB           =1;
    pPsIndi->AdcY           =1;
    pPsIndi->Gmcp           =1;
    pPsIndi->GmcY           =1;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =1;
    pPsIndi->DacCvbs        =0;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0;  // 1->0
    pPsIndi->FastBlanking   = 1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =0;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =0;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =0;
    pPsIndi->Dc             =0;
    pPsIndi->Tsp            =0;
    pPsIndi->Ve             =0;
    pPsIndi->Rvd            =0;   // 1->0 for DTV slow screen
    pPsIndi->Strld          =0;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForATV
/// @brief \b Function  \b Description: Set power save for ATV
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForATV(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =1;
    pPsIndi->AdcG           =1;
    pPsIndi->AdcB           =1;
    pPsIndi->AdcY           =0;
    pPsIndi->Gmcp           =0;
    pPsIndi->GmcY           =0;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =0;
    pPsIndi->CvbsBufOut     =0;
    pPsIndi->DacCvbs        =0;
    pPsIndi->VifIftop       =0;
    pPsIndi->VRefPdn        =0; // 1->0
    pPsIndi->FastBlanking   = 1;
    pPsIndi->AdcRgbBiasCurrentControl = 0;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =0;
    pPsIndi->Vif            =0;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;

}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForAV
/// @brief \b Function  \b Description: Set power save for AV
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForAV(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =1;
    pPsIndi->AdcG           =1;
    pPsIndi->AdcB           =1;
    pPsIndi->AdcY           =0;
    pPsIndi->Gmcp           =0;
    pPsIndi->GmcY           =0;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =0;
    pPsIndi->DacCvbs        =0;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0;  // 1->0
    pPsIndi->FastBlanking   =1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =0;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForRGB
/// @brief \b Function  \b Description: Set power save for RGB
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForRGB(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =0;
    pPsIndi->AdcG           =0;
    pPsIndi->AdcB           =0;
    pPsIndi->AdcY           =1;
    pPsIndi->Gmcp           =1;
    pPsIndi->GmcY           =1;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =1;
    pPsIndi->DacCvbs        =1;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =1;
    pPsIndi->FastBlanking   =1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =1;
    //Digital IP
    pPsIndi->Vd             =1;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =1;
    pPsIndi->Gopg2          =1;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForScart
/// @brief \b Function  \b Description: Set power save for Scart
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForScart(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =0;
    pPsIndi->AdcG           =0;
    pPsIndi->AdcB           =0;
    pPsIndi->AdcY           =0;
    pPsIndi->Gmcp           =0;
    pPsIndi->GmcY           =0;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =1;
    pPsIndi->DacCvbs        =1;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0; // 1->0
    pPsIndi->FastBlanking   =0;
    pPsIndi->AdcRgbBiasCurrentControl = 0;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =0;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForComponent
/// @brief \b Function  \b Description: Set power save for Component
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForComponent(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =0;
    pPsIndi->AdcG           =0;
    pPsIndi->AdcB           =0;
    pPsIndi->AdcY           =1;
    pPsIndi->Gmcp           =1;
    pPsIndi->GmcY           =1;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =1;
    pPsIndi->DacCvbs        =1;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0; // 1->0
    pPsIndi->FastBlanking   =1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =1;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForHDMI
/// @brief \b Function  \b Description: Set power save for HDMI
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForHDMI(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =1;
    pPsIndi->AdcG           =1;
    pPsIndi->AdcB           =1;
    pPsIndi->AdcY           =1;
    pPsIndi->Gmcp           =1;
    pPsIndi->GmcY           =1;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =1;
    pPsIndi->DacCvbs        =1;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0;  // 1->0
    pPsIndi->FastBlanking   =1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =1;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForSV
/// @brief \b Function  \b Description: Set power save for SV
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForSV(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =0;
    pPsIndi->AdcG           =1;
    pPsIndi->AdcB           =0;
    pPsIndi->AdcY           =0;
    pPsIndi->Gmcp           =0;
    pPsIndi->GmcY           =0;
    pPsIndi->GmcC           =0;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =0;
    pPsIndi->DacCvbs        =1;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0; // 1->0
    pPsIndi->FastBlanking   =1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =0;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =1;
    pPsIndi->Cytlif         =1;
    pPsIndi->MvdM4V         =1;
    pPsIndi->Dc             =1;
    pPsIndi->Tsp            =1;
    pPsIndi->Ve             =1;
    pPsIndi->Rvd            =1;
    pPsIndi->Strld          =1;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PowerSaveForStorage
/// @brief \b Function  \b Description: Set power save for Storage
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PowerSaveSetFlagForStorage(PowerSaveIndi_t *pPsIndi)
{
    if (!pPsIndi)
        return;

    //Analog IP
    pPsIndi->AdcR           =1;
    pPsIndi->AdcG           =1;
    pPsIndi->AdcB           =1;
    pPsIndi->AdcY           =1;
    pPsIndi->Gmcp           =1;
    pPsIndi->GmcY           =1;
    pPsIndi->GmcC           =1;
    pPsIndi->VifDac         =1;
    pPsIndi->CvbsBufOut     =1;
    pPsIndi->DacCvbs        =0;
    pPsIndi->VifIftop       =1;
    pPsIndi->VRefPdn        =0; // 1->0
    pPsIndi->FastBlanking   =1;
    pPsIndi->AdcRgbBiasCurrentControl = 1;
    pPsIndi->Audio          =0;
    //Digital IP
    pPsIndi->Vd             =0;
    pPsIndi->Vif            =1;
    pPsIndi->Svd            =0;
    pPsIndi->Cytlif         =0;
    pPsIndi->MvdM4V         =0;
    pPsIndi->Dc             =0;
    pPsIndi->Tsp            =0;
    pPsIndi->Ve             =0;
    pPsIndi->Rvd            =0;
    pPsIndi->Strld          =0;
    pPsIndi->Aeon           =0;
    pPsIndi->Gopg2          =0;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: MDrv_PsPrintIndi
/// @brief \b Function  \b Description: Dump power save indicator
/// @param <IN>         \b PsIndi: power save indicator
/// @param <OUT>        \b None :
/// @param <RET>        \b None :
/// @param <GLOBAL>     \b None :
////////////////////////////////////////////////////////////////////////////////
void MDrv_PsPrintIndi(PowerSaveIndi_t PsIndi)
{
#if (ANALOG_IP == ENABLE)
   DRVPOWER_DBG(printf("pPsIndi->AdcR     = %x\n ", PsIndi.AdcR));
   DRVPOWER_DBG(printf("pPsIndi->AdcG     = %x\n ", PsIndi.AdcG));
   DRVPOWER_DBG(printf("pPsIndi->AdcB     = %x\n ", PsIndi.AdcB));
   DRVPOWER_DBG(printf("pPsIndi->AdcY     = %x\n ", PsIndi.AdcY));
   DRVPOWER_DBG(printf("pPsIndi->Gmcp     = %x\n ", PsIndi.Gmcp));
   DRVPOWER_DBG(printf("pPsIndi->GmcY     = %x\n ", PsIndi.GmcY));
   DRVPOWER_DBG(printf("pPsIndi->GmcC     = %x\n ", PsIndi.GmcC));
   DRVPOWER_DBG(printf("pPsIndi->VifDac      = %x\n ", PsIndi.VifDac      ));
   DRVPOWER_DBG(printf("pPsIndi->CvbsBufOut  = %x\n ", PsIndi.CvbsBufOut  ));
   DRVPOWER_DBG(printf("pPsIndi->DacCvbs     = %x\n ", PsIndi.DacCvbs     ));
   DRVPOWER_DBG(printf("pPsIndi->VifIftop    = %x\n ", PsIndi.VifIftop    ));
   DRVPOWER_DBG(printf("pPsIndi->VRefPdn = %x\n ", PsIndi.VRefPdn ));
   DRVPOWER_DBG(printf("pPsIndi->FastBlanking = %x\n ", PsIndi.FastBlanking));
#endif

#if (DIGITAL_IP == ENABLE)
   DRVPOWER_DBG(printf("pPsIndi->Vd          = %x\n ", PsIndi.Vd          ));
   DRVPOWER_DBG(printf("pPsIndi->Vif         = %x\n ", PsIndi.Vif         ));
   DRVPOWER_DBG(printf("pPsIndi->Svd         = %x\n ", PsIndi.Svd         ));
   DRVPOWER_DBG(printf("pPsIndi->Cytlif      = %x\n ", PsIndi.Cytlif      ));
   DRVPOWER_DBG(printf("pPsIndi->MvdM4V      = %x\n ", PsIndi.MvdM4V      ));
   DRVPOWER_DBG(printf("pPsIndi->Dc          = %x\n ", PsIndi.Dc          ));
   DRVPOWER_DBG(printf("pPsIndi->Tsp         = %x\n ", PsIndi.Tsp         ));
   DRVPOWER_DBG(printf("pPsIndi->Ve          = %x\n ", PsIndi.Ve          ));
   DRVPOWER_DBG(printf("pPsIndi->Rvd         = %x\n ", PsIndi.Rvd         ));
   DRVPOWER_DBG(printf("pPsIndi->Strld         = %x\n ", PsIndi.Strld));
   DRVPOWER_DBG(printf("pPsIndi->Gopg2         = %x\n ", PsIndi.Gopg2));
#endif
   PsIndi = PsIndi;
}

//#######################################################################################
//#######################################################################################
//#######################################################################################
#include "Board.h"
#define MIPS_L1CACHE_DBG(X)     //X
#if (PM_RUNS_IN == PM_RUNS_IN_CACHE)
#include "datatype.h"
#include "sysinfo.h"
#include "msAPI_BDMA.h"

// for Run in cache
#define CONFIG_KSEG0_MASK (0x00000007)
#define KSEG0_UNCACHED (0x2)
#define KSEG0_CACHE (0x3) // Cacheable, noncoherent, write-back, write allocate
#define KSEG0_BASE  (0x80000000)
#define KSEG1_BASE  (0xA0000000)

#define MIPS_CLOCK_FREQ_XTAL 12000000

#define HAL_MIPS_CACHE_INDEX_LOAD_TAG_I      0x04 /* 1 0 */
#define HAL_MIPS_CACHE_INDEX_LOAD_TAG_D      0x05 /* 1 1 */
#define HAL_MIPS_CACHE_INDEX_STORE_TAG_I     0x08 /* 2 0 */
#define HAL_MIPS_CACHE_INDEX_STORE_TAG_D     0x09 /* 2 1 */
#define HAL_MIPS_CACHE_INDEX_STORE_DATA_I    0x0c /* 7 0 */
#define HAL_MIPS_CACHE_INDEX_STORE_DATA_D    0x0d /* 7 1 */

#define hazard_barrier() ({ asm volatile(".set push\n"\
                                         ".set mips32r2\n"\
                                         "ehb\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n"\
                                         ".set pop\n"); 0; })

#define Hit_Invalidate_D    0x11
#define Hit_Writeback_Inv_D 0x15
#define _BIT(x)                      (1<<(x))
#define Hit_Invalidate_I 0x10
#define cache_op(op,addr)                       \
	__asm__ __volatile__(                       \
	"   .set    push                    \n" \
	"   .set    noreorder               \n" \
	"   .set    mips3\n\t               \n" \
	"   cache   %0, %1                  \n" \
	"   .set    pop                 \n" \
	:                               \
	: "i" (op), "R" (*(unsigned char *)(addr)))

typedef struct {
        unsigned int waysize;   /* Bytes per way */
        unsigned short sets;    /* Number of lines per set */
        unsigned char ways;     /* Number of ways */
        unsigned char linesz;   /* Size of line in bytes */
        unsigned char waybit;   /* Bits to select in a cache set */
        unsigned char flags;    /* Flags describing cache properties */
}cache_desc;


void read_icache_config(cache_desc *icache_dsc)
{
    unsigned int config1;
    unsigned int lsize;
    unsigned int icache_size;

    asm volatile (       \
            ".set\tmips32\n\t"   \
            "mfc0 %0, $16, 1\n\t"\
            ".set\tmips0\n\t"    \
            : "=r" (config1));
    MIPS_L1CACHE_DBG(printf("icache config = %x\n", config1));

    if ((lsize = ((config1 >> 19) & 7)))
    {
        icache_dsc->linesz = 2 << lsize;
    }
    else
    {
        icache_dsc->linesz = lsize;
    }
    icache_dsc->sets = 64 << ((config1 >> 22) & 7);
    icache_dsc->ways = 1 + ((config1 >> 16) & 7);

    icache_size = icache_dsc->sets *
                  icache_dsc->ways *
                  icache_dsc->linesz;
    //icache_dsc->waybit = ffs(icache_size/icache_dsc->ways) - 1;
    icache_dsc->waybit =  __builtin_ffs(icache_size/icache_dsc->ways) - 1;
    MIPS_L1CACHE_DBG(printf("icache_dsc->linesz = %x\n", icache_dsc->linesz));
    MIPS_L1CACHE_DBG(printf("icache_dsc->sets = %x\n", icache_dsc->sets));
    MIPS_L1CACHE_DBG(printf("icache_dsc->ways = %x\n", icache_dsc->ways));
    MIPS_L1CACHE_DBG(printf("icache_dsc->waybit = %x\n", icache_dsc->waybit));
    MIPS_L1CACHE_DBG(printf("icache_size = %x\n", icache_size));
}

void read_dcache_config(cache_desc *dcache_dsc)
{
    unsigned int config1;
    unsigned int lsize;
    unsigned int dcache_size;

    asm volatile (       \
            ".set\tmips32\n\t"   \
            "mfc0 %0, $16, 1\n\t"\
            ".set\tmips0\n\t"    \
            : "=r" (config1));
    MIPS_L1CACHE_DBG(printf("dcache config = %x\n", config1));

    if ((lsize = ((config1 >> 10) & 7)))
    {
        dcache_dsc->linesz = 2 << lsize;
    }
    else
    {
        dcache_dsc->linesz = lsize;
    }
    dcache_dsc->sets = 64 << ((config1 >> 13) & 7);
    dcache_dsc->ways = 1 + ((config1 >> 7) & 7);

    dcache_size = dcache_dsc->sets *
                  dcache_dsc->ways *
                  dcache_dsc->linesz;
    //icache_dsc->waybit = ffs(icache_size/icache_dsc->ways) - 1;
    dcache_dsc->waybit =  __builtin_ffs(dcache_size/dcache_dsc->ways) - 1;
    MIPS_L1CACHE_DBG(printf("dcache_dsc->linesz = %x\n", dcache_dsc->linesz));
    MIPS_L1CACHE_DBG(printf("dcache_dsc->sets = %x\n", dcache_dsc->sets));
    MIPS_L1CACHE_DBG(printf("dcache_dsc->ways = %x\n", dcache_dsc->ways));
    MIPS_L1CACHE_DBG(printf("dcache_dsc->waybit = %x\n", dcache_dsc->waybit));
    MIPS_L1CACHE_DBG(printf("dcache_size = %x\n", dcache_size));
}

void enable_cache(MS_BOOL bEnable)
{
    unsigned int config;

    asm volatile("mfc0 %0, $16\n" \
             ".set push\n"    \
             ".set mips32r2\n"\
             "ehb\n"          \
             ".set pop\n" : "=r" (config) : );

    config = (config & ~CONFIG_KSEG0_MASK) | (bEnable ? KSEG0_CACHE : KSEG0_UNCACHED);

    asm volatile("mtc0 %0, $16\n" \
             ".set push\n"    \
             ".set mips32r2\n"\
             "ehb\n"          \
             ".set pop\n" : : "r" (config) );
}

void invalidate_icache(void)
{
    cache_desc c;
    MS_U32 linesize;
    MS_U32 start;
    MS_U32 end;

    MS_U32 addr;
    MS_U8  u8OffsetBit, u8IndexBit, u8WayBit;
    MS_U32 u32Way, u32Index;

    read_icache_config(&c);
    linesize = c.linesz;

    u8OffsetBit = __builtin_ffs(c.linesz) - 1;
    u8IndexBit = __builtin_ffs( (c.sets * c.ways * c.linesz)/ c.ways) - 1;
    u8WayBit = u8IndexBit + (__builtin_ffs(c.ways) - 1);

    start = KSEG0_BASE;
    end = start + (c.sets * c.ways * c.linesz); // cache size

    // Invalidate lines
    asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
    hazard_barrier();

    for(addr = start; addr < end; addr += linesize)
    {

        unsigned int taglo;

        u32Way = addr & BITMASK(u8WayBit-1 : u8IndexBit);
        u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);

        taglo = (_VA2PA(addr) & 0xFFFFF800) & ~(1 << 7) & ~(1 << 5); // PTaglo[31:11], V[7], L[5]
        asm volatile("mtc0  %0, $28, 0" : : "r" (taglo));
        hazard_barrier();

        asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_I),
                "r" (u32Way | u32Index));
        hazard_barrier();
    }
}

void flush_cache(unsigned long start_addr, unsigned long size)
{	
	unsigned long lsize = 16;
	unsigned long addr = start_addr & ~(lsize - 1);
	unsigned long aend = (start_addr + size - 1) & ~(lsize - 1);
	unsigned int    dwReadData = 0;	
	while (1) {		
		cache_op(Hit_Writeback_Inv_D, addr);
		cache_op(Hit_Invalidate_I, addr);
		if (addr == aend)
			break;
		addr += lsize;
	} 

    #ifdef CONFIG_MSTAR_L2_CACHE_ENABLE
	//Flush L2 All and Invalid
	dwReadData = *(volatile unsigned int *)(0xbf203104);
	dwReadData &= ~(0x1F);
	dwReadData |= 0x04;
	//Flush All and Invalid
	*(volatile unsigned int *)(0xbf203104) = dwReadData;
	dwReadData = *(volatile unsigned int *)(0xbf203104);
	dwReadData |= _BIT(4);
	*(volatile unsigned int *)(0xbf203104) = dwReadData;
	do
	{
		dwReadData = *(volatile unsigned int *)(0xbf20317c);
		dwReadData &= _BIT(10);
		//Check Status of Flush All Finish
	} while(dwReadData == 0);
    #endif

	//Flush MIU pipe
	dwReadData = *(volatile unsigned int *)(0xbf203104);
	dwReadData &= ~(0x1F);
	dwReadData |= 0x02;
	//Flush MIU Pipe
	*(volatile unsigned int *)(0xbf203104) = dwReadData;
	dwReadData = *(volatile unsigned int *)(0xbf203104);
	dwReadData |= _BIT(4);
	*(volatile unsigned int *)(0xbf203104) = dwReadData;
	do
	{
		dwReadData = *(volatile unsigned int *)(0xbf20317c);
		dwReadData &= _BIT(9);
		//Check Status of Flush MIU Pipe Finish    
	} while(dwReadData == 0);
}

MS_BOOL ric_fill_icache(MS_U32 insts[], MS_U32 size)
{
    cache_desc c;
    MS_U32 linesize;
    MS_U32 start;
    MS_U32 end;
    MS_U32 ws_inc;
    MS_U32 ws_end;
    MS_U32 ws, bytes, addr, i;
    MS_U8  u8OffsetBit, u8IndexBit, u8WayBit;
    MS_U32 u32Way, u32Index;

    read_icache_config(&c);
    linesize = c.linesz;

    start = (MS_U32)(((MS_U32)insts&0x1FFFFFFF)|KSEG0_BASE);//0x83412000;
    end = (MS_U32)  (start+size);

    MIPS_L1CACHE_DBG(printf("start = 0x%x, end = 0x%x\n", (unsigned int)start, (unsigned int)end));

    ws_inc = 1U << c.waybit;
    ws_end = c.ways << c.waybit;

    u8OffsetBit = __builtin_ffs(c.linesz) - 1;
    u8IndexBit = __builtin_ffs( (c.sets * c.ways * c.linesz)/ c.ways) - 1;
    u8WayBit = u8IndexBit + (__builtin_ffs(c.ways) - 1);
    MIPS_L1CACHE_DBG(printf("u8OffsetBit = %d \n", u8OffsetBit));
    MIPS_L1CACHE_DBG(printf("u8IndexBit = %d \n", u8IndexBit));
    MIPS_L1CACHE_DBG(printf("u8WayBit = %d \n", u8WayBit));

    if(size % 4)
    {
        printf("The size is unalignment\n");
        return FALSE;
    }

    // Fill instruction to each way
    i = 0;
    for(addr = start; addr < end; addr += linesize)
    {
        unsigned int taglo;

        asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
        hazard_barrier();

        u32Way = addr & BITMASK(u8WayBit-1 : u8IndexBit);
        u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);

        for(bytes = 0; bytes < linesize; bytes += 8)
        {
            unsigned int lo = insts[i++];
            unsigned int hi = insts[i++];
            asm volatile("mtc0  %0, $28, 1" : : "r" (lo));
            asm volatile("mtc0  %0, $29, 1" : : "r" (hi));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_DATA_I),
                "r" (u32Way | u32Index | bytes));
            hazard_barrier();
        }

        // Lock line

        asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
        hazard_barrier();

        taglo = (_VA2PA(addr) & 0xFFFFF800) | (1 << 7) | (1 << 5); // PTaglo[31:11], V[7], L[5]
        asm volatile("mtc0  %0, $28, 0" : : "r" (taglo));
        hazard_barrier();

        //u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);
        asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_I),
                "r" (u32Way | u32Index));
        hazard_barrier();
    }


    MIPS_L1CACHE_DBG(printf("Clear Way-Select\n"));
    // Clear Way-Select
    asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
    hazard_barrier();
    for(addr = start; addr < end; addr += linesize)
    {
        for(ws = 0; ws < ws_end; ws += ws_inc)
        {
            asm volatile("mtc0  %0, $28, 0" : : "r" (0));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                    "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_I),
                    "r" (addr ^ ws));
            hazard_barrier();
        }
    }
    // Disable WST test mode
    asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
    hazard_barrier();

    MIPS_L1CACHE_DBG(printf("Disable WST test mode\n"));

    return TRUE;
}

MS_BOOL ric_fill_dcache(MS_U32 insts[], MS_U32 size)
{
    cache_desc c;
    MS_U32 linesize;
    MS_U32 start;
    MS_U32 end;
    MS_U32 ws_inc;
    MS_U32 ws_end;
    MS_U32 ws, bytes, addr, i;
    MS_U8  u8OffsetBit, u8IndexBit, u8WayBit;
    MS_U32 u32Way, u32Index;

    read_dcache_config(&c);
    linesize = c.linesz;

    start = (MS_U32)(((MS_U32)insts&0x1FFFFFFF)|KSEG0_BASE);//0x8341A000;
    end = (MS_U32)  (start+size);

    MIPS_L1CACHE_DBG(printf("start = 0x%x, end = 0x%x\n", (unsigned int)start, (unsigned int)end));

    ws_inc = 1U << c.waybit;
    ws_end = c.ways << c.waybit;

    u8OffsetBit = __builtin_ffs(c.linesz) - 1;
    u8IndexBit = __builtin_ffs( (c.sets * c.ways * c.linesz)/ c.ways) - 1;
    u8WayBit = u8IndexBit + (__builtin_ffs(c.ways) - 1);
    MIPS_L1CACHE_DBG(printf("u8OffsetBit = %d \n", u8OffsetBit));
    MIPS_L1CACHE_DBG(printf("u8IndexBit = %d \n", u8IndexBit));
    MIPS_L1CACHE_DBG(printf("u8WayBit = %d \n", u8WayBit));

    if(size % 4)
    {
        printf("The size is unalignment\n");
        return FALSE;
    }

    // Fill instruction to each way
    i = 0;
    for(addr = start; addr < end; addr += linesize)
    {
        unsigned int taglo;

        asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
        hazard_barrier();

        u32Way = addr & BITMASK(u8WayBit-1 : u8IndexBit);
        u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);

        for(bytes = 0; bytes < linesize; bytes += 4)
        {
            unsigned int lo = insts[i++];
            //unsigned int hi = insts[i++];
            asm volatile("mtc0  %0, $28, 3" : : "r" (lo));
            //asm volatile("mtc0  %0, $29, 1" : : "r" (hi));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_DATA_D),
                "r" (u32Way | u32Index | bytes));
            hazard_barrier();
        }

        // Lock line

        asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
        hazard_barrier();

        taglo = (_VA2PA(addr) & 0xFFFFF800) | (1 << 7);// | (1 << 5); // PTaglo[31:11], V[7], L[5]
        asm volatile("mtc0  %0, $28, 2" : : "r" (taglo));
        hazard_barrier();

        //u32Index = addr & BITMASK(u8IndexBit-1 : u8OffsetBit);
        asm volatile("cache %0, 0(%1)" : :
                "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_D),
                "r" (u32Way | u32Index));
        hazard_barrier();
    }


    MIPS_L1CACHE_DBG(printf("Clear Way-Select\n"));
    // Clear Way-Select
    asm volatile("mtc0 %0, $26" : : "r" (0x20000000));
    hazard_barrier();
    for(addr = start; addr < end; addr += linesize)
    {
        for(ws = 0; ws < ws_end; ws += ws_inc)
        {
            asm volatile("mtc0  %0, $28, 2" : : "r" (0));
            hazard_barrier();

            asm volatile("cache %0, 0(%1)" : :
                    "I" (HAL_MIPS_CACHE_INDEX_STORE_TAG_D),
                    "r" (addr ^ ws));
            hazard_barrier();
        }
    }
    // Disable WST test mode
    asm volatile("mtc0 %0, $26" : : "r" (0x00000000));
    hazard_barrier();

    MIPS_L1CACHE_DBG(printf("Disable WST test mode\n"));

    return TRUE;
}
//################################
// Export Global Function for PM Standby
//################################
int MDrv_Sys_RunCodeInL1Cache(void)
{
    #define PM_FLASH_ADDR    0x10000
    #define PM_SDRAM_ADDR    AEON_MEM_ADR
    #define PM_BIN_SIZE      0x10000

    MS_U32 u32FlashAddr=PM_FLASH_ADDR;
    MS_U32 u32SdramAddr=PM_SDRAM_ADDR;
    MS_U32 u32PMBinSize=PM_BIN_SIZE;
    MS_U32 u32NCacheAddr;
    MS_U32 u32VCacheAddr;
    MS_U32* pu32VAddr;
    MS_U8 u8temp;

    //#####################
    //(1) Copy PM code to DRAM
    MDrv_MIU_Protect(AEON_MEM_USE_MIU_PROTECT_BLOCK_ID, &u8temp, u32SdramAddr, u32PMBinSize, DISABLE);
    u32NCacheAddr = (MS_U32)MsOS_PA2KSEG1(u32SdramAddr);
    u32VCacheAddr = (MS_U32)MsOS_PA2KSEG0(u32SdramAddr);
    MApi_BDMA_CopyFromResource(u32FlashAddr,u32NCacheAddr, u32PMBinSize);
    MsOS_DelayTaskUs(50);

    //#####################
    //(2) Copy PM code to L1 cache
    //MS_U32 irqNum; 
    //irqNum = MsOS_DisableAllInterrupts();
    invalidate_icache();
    MsOS_FlushMemory();
    enable_cache(0);
    pu32VAddr = (MS_U32*)u32NCacheAddr;
    ric_fill_icache(pu32VAddr,0x8000);
    pu32VAddr = (MS_U32 *)(u32NCacheAddr+0x8000);
    ric_fill_dcache(pu32VAddr,0x8000);
    //enable_cache(1); //move this routine to PM.bin 

    //#############################################################
    //[##NOTE##] DO NOT ADD ANY CODE HERE !!!
    //#############################################################
    //(3) Jump to L1 cache memory immediately  : address = u32VCacheAddr|0x400
    //## u32VCacheAddr : must be the same base as the value defined in CPU_PM linker script
    asm volatile (
            "move $9, %[i0]\n\t" \
            "j $9\n\t" \
            "nop\n\t" \
            : \
            : [i0] "r"(u32VCacheAddr|0x400) \
            : "memory" \
    );
    while(1);

    return 0;
}





#endif

#undef _DRVPOWER_C_
#endif
