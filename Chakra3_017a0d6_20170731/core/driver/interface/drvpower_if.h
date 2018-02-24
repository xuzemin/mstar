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
/// @file  drvpower_if.h
/// @brief power Module
/// @author MStar Semiconductor Inc.
////////////////////////////////////////////////////////////////////////////////

#ifndef _DRVPOWER_IF_H_
#define _DRVPOWER_IF_H_

#include "datatype.h"

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define VER_CHECK_HEADER    'M','S','V','C','0','0'
#define PWR_LIB_ID          'P','2'
#define PWR_INTERFACE_VER   '0','1'
#define PWR_BUILD_VER       '0','0','0','1'
#define CHANGE_LIST_NUM     '0','0','0','9','0','6','1','8'
#define PRODUCT_NAME        'A','7'
#define CUSTOMER_NAME       'A'
#define DEVELOP_STAGE       'B','L','E','G'
#define OS_VERSION          '0','0'
#define CHECK_SUM           'T'

//Copy from Board.h
#define POWERMODE_S0            0   // Working
#define POWERMODE_S1            1   // Sleep, MCU run in SDRAM; MIU low speed; Disable un-use power
#define POWERMODE_S2            2   // Sleep, Reboot MCU and run in FLASH; MIU low speed; Disable un-use power
#define POWERMODE_S3            3   // Sleep, Reboot MCU and run in FLASH; SDRAM stop, Disable most extra power
#define POWERMODE_S4            4   // Hibernate, Reboot MCU and stop, All clock stop, Disable most power
#define POWERMODE_S5            5   // Off, The system is completely off

// Power Saving Mode
#define PSM_MPEG                (0x01)
#define PSM_DEMUX               (0x02)
#define PSM_GE                  (0x04)
#define PSM_DVBPLL              (0x08)

//Checking if the system is 1st boot up
#define CHECK_PM_OFF_FLAG       1
#define CHECK_RTC_OCLOCK        2

// Power Down Function
#define PDF_EXT_DEVICE          (0x01)
#define PDF_ANA                 (0x02)
#define PDF_DIG                 (0x04)
#define PDF_SDR                 (0x08)
#define PDF_MPLL                (0x10)
#define PDF_ACLK                (0x20)
#define PDF_RESERVE             (0x40)
#define PDF_HWAKEUP             (0x80)

//#define REG(addr)   (*(volatile U8 *)(addr))
#define MASK(x)     (((1<<(x##_BITS))-1) << x##_SHIFT)

#define BK_CHIPTOP(x)           (0x1E00 + x)
#define BK_ADCDVI(x)            (0x2500 + x)

#define POWER_DOWN              (1)
#define POWER_ON                (0)
#define POWER_RESET             (1)

typedef struct
{
     //Analog IP
     U8 AdcR         :1;
     U8 AdcG         :1;
     U8 AdcB         :1;
     U8 AdcY         :1;
     U8 Gmcp         :1;
     U8 GmcY         :1;
     U8 GmcC         :1;
     U8 VifDac       :1;
     U8 CvbsBufOut   :1;
     U8 DacCvbs      :1;
     U8 VifIftop     :1;
     //U8 BandgapBias :1;
     U8 VRefPdn      :1;
     U8 FastBlanking :1;
     U8 AdcRgbBiasCurrentControl: 1;
     U8 Audio        :1;
     //Ditital IP
     U8 Vd           :1;
     U8 Vif          :1;
     U8 Svd          :1;
     U8 Cytlif       :1;
     U8 MvdM4V       :1;
     U8 Dc           :1;
     U8 Tsp          :1;
     U8 Ve           :1;
     U8 Rvd          :1;
     U8 Strld        :1;
     U8 Aeon         :1;
     U8 Gopg2        :1;
}PowerSaveIndi_t;

/// Define the HW modules to turn on/off.
typedef enum
{
    E_HWCLK_USB_ONOFF,
    E_HWCLK_DDR_ONOFF,
    E_HWCLK_MIU_ONOFF,
    E_HWCLK_TS0_ONOFF,
    E_HWCLK_TCK_ONOFF,
    E_HWCLK_AEON_ONOFF,
    E_HWCLK_TSP_ONOFF,
    E_HWCLK_STC0_ONOFF,
    E_HWCLK_MADSTC_ONOFF,
    E_HWCLK_MVDBOOT_ONOFF,
    E_HWCLK_MVD_ONOFF,
    E_HWCLK_M4V_ONOFF,
    E_HWCLK_DC0_ONOFF,
    E_HWCLK_DHCSBM_ONOFF,
    E_HWCLK_GE_ONOFF,
    E_HWCLK_GOP0_ONOFF,
    E_HWCLK_GOP1_ONOFF,
    E_HWCLK_GOPD_ONOFF,
    E_HWCLK_VD_ONOFF,
    E_HWCLK_VDMCU_ONOFF,
    E_HWCLK_VD200_ONOFF,
    E_HWCLK_DHC_ONOFF,
    E_HWCLK_FICLKF2_ONOFF,
    E_HWCLK_PCMCIA_ONOFF,
    E_HWCLK_VE_ONOFF,
    E_HWCLK_VEDAC_ONOFF,
    E_HWCLK_DAC_ONOFF,
    E_HWCLK_FCLK_ONOFF,
    E_HWCLK_FMCLK_ONOFF,
    E_HWCLK_ODCLK_ONOFF,
    E_HWCLK_VEIN_ONOFF,
    E_HWCLK_FCIE_ONOFF,
    E_HWCLK_TS2_ONOFF,
    E_HWCLK_TSOUT_ONOFF,
    E_HWCLK_IDCLK2_ONOFF,
    E_HWCLK_STRLD_ONOFF,
    E_HWCLK_MCU_ONOFF,
    E_HWCLK_MCU_SETTING,
    E_HWCLK_DHCDDR_GATING,
    E_HWCLK_DHCSYNTH_GATING,
    E_HWCLK_DHCMCU_GATING,
    E_HWCLK_DHCLIVE_GATING,
} HW_MODULE_CLOCK_SETTING;

#ifdef _DRVPOWER_C_
#define EXTERN
#else
#define EXTERN   extern
#endif

//EXTERN bit bPowerOnMode;
EXTERN S16 g_eOnTimerDateForStandBy;
EXTERN S16 g_eDayOfWeekForStandBy; // todo
EXTERN S16 g_eOnTimerDate;
EXTERN BOOLEAN g_bWakeUpByOnTimer;

EXTERN U8  volatile g_u8TimeInfo_Flag;
EXTERN U32 volatile gSystemTimeCount;
EXTERN U32 volatile gWakeupSystemTime;
EXTERN U8 volatile gSystemTimeCount_TCON;

#undef EXTERN
//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
BOOLEAN MDrv_Power_Is1STBootUp(U8 u8Chk1stBootMode, U32 u32SysTime);
BOOLEAN MDrv_Power_IsPowerDown(void);
BOOLEAN MDrv_Power_CheckPowerOnKey(void);
BOOLEAN MDrv_Power_ExecutePowerUp(void);
BOOLEAN MDrv_Power_Set_HwClock (HW_MODULE_CLOCK_SETTING eModule, int eValue);
BOOLEAN MDrv_Power_CheckAnalogIP(void);
BOOLEAN MDrv_Power_CheckDigitIP(void);
void MDrv_Power_Init(void);
void MDrv_Power_SetMode(U8 u8Mode);
void MDrv_Power_Set_PDMode(U8 u8Mode);
void MDrv_Power_ResetAndPowerDown(void);
void MDrv_Power_ExecutePowerDown(void);
void MDrv_Power_PMPowerRst(void);
void MDrv_Power_Standby(void);
void MDrv_Power_Saving_Mode(U8 u8Flag, BOOLEAN bEnable, BOOLEAN bPwrSaveT);
void MDrv_PsPrintIndi(PowerSaveIndi_t PsIndi);
void MDrv_Power_GetVerInfo(U8 **ppVerInfo);

//Analog IP
void MDrv_PowerSaveForLvdsSet(void);
void MDrv_PowerSaveForAdcSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForGmcSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForCvbsBufOutSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForDacCvbsSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForBandGapBiasSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForFastBlankingSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForAdcRgbBiasCurrentControlSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForAudio(PowerSaveIndi_t PsIndi);

//Digital IP
void MDrv_PowerSaveForVdSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForSvdSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForCytlifSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForMvdM4vSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForDcSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForTspSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForVeSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForRvdSet(PowerSaveIndi_t PsIndi);
void MDrv_PowerSaveForStrld(PowerSaveIndi_t PsIndi);
void Mdrv_PowerSaveForAeon(PowerSaveIndi_t PsIndi);
void Mdrv_PowerSaveForGopg2(PowerSaveIndi_t PsIndi);

void MDrv_PowerSaveSetFlagForDTV(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForATV(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForAV(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForRGB(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForScart(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForComponent(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForHDMI(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForSV(PowerSaveIndi_t *pPsIndi);
void MDrv_PowerSaveSetFlagForStorage(PowerSaveIndi_t *pPsIndi);


void MDrv_Set_Power_Flag(U8 u8Mode, U8 u8Flag);
U8 MDrv_Get_Power_Flag(U8 flag);

int EAR_PHONE_get_level(void); //gchen @ 20171218
int GetEarphoneState(void); //gchen @ 20171218
#if 0 //EANBLE_V56_IO_KEY
int keystone_positive_get_level(void); // xzm @ 20171222
int keystone_negative_get_level(void); // xzm @ 20171222
#endif
#endif // _DRVPOWER_H_
