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
#ifndef ADAPTER_DEBUG_H
#define ADAPTER_DEBUG_H

#include "DibDriver_Platform.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_ADAPTER 0x0001
#define DEBUG_DEMOD   0x0002
#define DEBUG_TUNER   0x0004
#define DEBUG_VIDEO   0x0008
#define DEBUG_AUDIO   0x0010
#define DEBUG_ANALOG  0x0018
#define DEBUG_BUS     0x0020
#define DEBUG_SIP     0x0040
#define DEBUG_LAYOUT  0x0080
#define DEBUG_BOARD   0x0100
#define DEBUG_HAL     0x0120

#define DEBUG_MASK    0xffff

#define DEBUG_PREFIX_MAX_LEN 50
struct dibDebugObject {
	uint32_t mask;
	char     prefix[DEBUG_PREFIX_MAX_LEN];
};

#ifndef DEBUG_OBJECT
#define DEBUG_OBJECT(name, type, text) \
    const struct dibDebugObject name = { \
        type, \
        text \
    };
#endif

#ifndef DEBUG_OBJECT_STATIC
#define DEBUG_OBJECT_STATIC(name, type, text) static DEBUG_OBJECT(name, type, text)
#endif

extern void debug_object_init(struct dibDebugObject *obj, char *prefix, uint32_t mask);

#ifndef DEBUG_FUNCTIONS_PROTOTYPED_BY_PLATFORM
/* to be implemented by the platform */

//! Print a line of debugging information
/**
 * This function is called from inside the code to ask for printing
 * one line of debugging. The first argument gives information about
 * the context the debugging message was emitted.
 * \param dbg context-information about the source of this debug-message.
 * \param fmt format string
 * \param ... arguments
 */
extern void platform_debug_printf_line(const struct dibDebugObject *dbg, const char *fmt, ...);

//! Print some characters of debugging information
/**
 * This function is called from inside the code to ask for printing
 * some characters which not necessarily need to be a line. There is
 * not information about the context of this debugging message. It is
 * used to print related information which is spread of several lines
 * of code.
 * \param fmt format string
 * \param ... arguments
 */
//extern void debug_printf(const char *fmt, ...);
#endif

#define dbgpl platform_debug_printf_line
#define dbgp   printf

#define dbg_bufdump(b,l) do { uint32_t _i = 0; for (_i = 0; _i < (l); _i++) dbgp("%02x ",b[_i]); } while (0)


/* backward compat */
#define DibDbgPrint dbgp

#define fstart do { dbgp("++ %s - %d\n", __FUNCTION__, __LINE__ ); } while (0)
#define fend   do { dbgp("-- %s - %d\n", __FUNCTION__, __LINE__ ); } while (0)

#ifdef DIBCOM_TESTING
#define dbg_testing(x) printf("%s - %s\n", __FUNCTION__, x)
#else
#define dbg_testing(x)
#endif

#ifdef __cplusplus
}
#endif

#endif
