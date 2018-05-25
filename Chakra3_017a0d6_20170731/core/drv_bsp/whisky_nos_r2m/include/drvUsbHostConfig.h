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
#ifndef DRV_USB_HOST_CONFIG_H
#define DRV_USB_HOST_CONFIG_H

//#define ATV_SERISE_USE
//#define NEPTUNE_SERIAL_USE
//#define CERAMAL_SERISE_USE
//#define PLUTO_SERIAL_USE
//#define TITANIA2_SERIAL_USE
//#define TITANIA3_SERIAL_USE
//#define EUCLID_SERIAL_USE
#define MAYA_USE

#if defined (MCU_AEON)
#define CPU_TYPE_AEON
#elif defined (MCU_MIPS_4KE) || defined(MCU_MIPS_34K) || defined(MCU_MIPS_74K) || defined(MCU_MIPS_1004K)
#define CPU_TYPE_MIPS
#elif defined (__arm__)
#define CPU_TYPE_ARM
#else
  #if defined (MIPS_CHAKRA)
  #define CPU_TYPE_MIPS
  #else
  #define CPU_TYPE_AEON
  #endif
#endif


#if defined(CPU_TYPE_AEON)
#define OS_BASE_ADDR        0xa0000000
#elif defined(CPU_TYPE_MIPS)
  #if defined(TITANIA3_SERIAL_USE) || defined(EUCLID_SERIAL_USE) || defined(MAYA_USE)
    #define OS_BASE_ADDR        0xbf000000
  #else
    #define OS_BASE_ADDR        0xbf800000
  #endif
#elif defined(CPU_TYPE_ARM)
    #define OS_BASE_ADDR        0xfd000000
#else
#No_CPU_type_for_USB
#endif

#ifdef PLUTO_SERIAL_USE
#define UHC_BASE    (OS_BASE_ADDR+0x4800)
#define UHC2_BASE   (OS_BASE_ADDR+0x1600)
#define UTMIBaseAddr      (OS_BASE_ADDR+0x7500)
#define UTMIBaseAddr2   (OS_BASE_ADDR+0x7580)
#define USBCBase            (OS_BASE_ADDR+0xe00)
#define USBCBase2           (OS_BASE_ADDR+0x1800)
#endif

#ifdef TITANIA2_SERIAL_USE
#define UHC_BASE    (OS_BASE_ADDR+0x4800)
#define UHC2_BASE   (OS_BASE_ADDR+0x1a00)
#define UTMIBaseAddr       (OS_BASE_ADDR+0x7500)
#define UTMIBaseAddr2   (OS_BASE_ADDR+0x7400)
#define USBCBase            (OS_BASE_ADDR+0xe00)
#define USBCBase2           (OS_BASE_ADDR+0xf00)
#endif

#ifdef EUCLID_SERIAL_USE
#define UHC_BASE            (OS_BASE_ADDR+0x204800)
#define UHC2_BASE           (OS_BASE_ADDR+0x201a00)
#define UTMIBaseAddr        (OS_BASE_ADDR+0x207500)
#define UTMIBaseAddr2       (OS_BASE_ADDR+0x207400)
#define USBCBase            (OS_BASE_ADDR+0x200e00)
#define USBCBase2           (OS_BASE_ADDR+0x200f00)
#endif

#ifdef TITANIA3_SERIAL_USE
#define UHC_BASE    (OS_BASE_ADDR+0x204800)
#define UHC2_BASE   (OS_BASE_ADDR+0x201a00)
#define UTMIBaseAddr       (OS_BASE_ADDR+0x207500)
#define UTMIBaseAddr2   (OS_BASE_ADDR+0x207400)
#define USBCBase            (OS_BASE_ADDR+0x200e00)
#define USBCBase2           (OS_BASE_ADDR+0x200f00)

#define UHC3_BASE   (OS_BASE_ADDR+0x227200)
#define UTMIBaseAddr3   (OS_BASE_ADDR+0x207200)
#define USBCBase3           (OS_BASE_ADDR+0x227000)

#define UHC4_BASE   (OS_BASE_ADDR+0x227100)
#define UTMIBaseAddr4   (OS_BASE_ADDR+0x244100)
#define USBCBase4           (OS_BASE_ADDR+0x244c00)
#endif

#ifdef TRITON_SERIAL_USE
#define UHC_BASE    0x2e00
#define UTMIBaseAddr     0x3100
#endif

#ifdef NEPTUNE_SERIAL_USE
#define UHC_BASE    (OS_BASE_ADDR+0x4800)
#define UTMIBaseAddr     (OS_BASE_ADDR+0x7500)
#endif

#if 0
#ifdef  CERAMAL_SERISE_USE
#define UHC_BASE    0x2400
#define UTMIBaseAddr     0x1f00
#define OnePort_OTG_EHCI
#define Process_018_USE
#endif
#endif

#ifdef  ATV_SERISE_USE
#define UHC_BASE     (OS_BASE_ADDR+0x4800)
#define UTMIBaseAddr     (OS_BASE_ADDR+0x7500)
#endif

#ifdef MAYA_USE
#define UHC_BASE      (OS_BASE_ADDR + (0x102400 << 1))
#define UHC2_BASE     (OS_BASE_ADDR + (0x102300 << 1))
#define UTMIBaseAddr  (OS_BASE_ADDR + (0x103A80 << 1))
#define UTMIBaseAddr2 (OS_BASE_ADDR + (0x103A00 << 1))
#define USBCBase      (OS_BASE_ADDR + (0x100700 << 1))
#define USBCBase2     (OS_BASE_ADDR + (0x100780 << 1))
#endif


//#define USB_PTP_ENABLE
//#define USB2_PTP_ENABLE
//#define USB3_PTP_ENABLE
//#define USB4_PTP_ENABLE

#define USB_HID_ENABLE
#define USB2_HID_ENABLE
//#define USB3_HID_ENABLE
//#define USB4_HID_ENABLE


#endif //#ifndef DRV_USB_HOST_CONFIG_H

