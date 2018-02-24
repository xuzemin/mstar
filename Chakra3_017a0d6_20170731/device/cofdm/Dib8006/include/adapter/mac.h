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
#ifndef ADAPTER_MAC_H
#define ADAPTER_MAC_H

#include "common.h"
#include "databus.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dibMacMonitor;
struct dibDemodMonitor;

#define DLL_SH  1
#define DLL_MAC 2

//! generic description of a Mac
/**
 * This struct describes a MAC in a generic way. Each MAC-driver has to implement one.
 */
struct dibMac {
    const char name[MAX_INFO_NAME_LENGTH]; /*! Keeps a human-readable name as a string. */
    struct {
        int (*reset) (struct dibMac *);

        int (*wakeup) (struct dibMac *);
        int (*sleep) (struct dibMac *, uint8_t deep);

        int (*set_gpio) (struct dibMac *, uint8_t num, uint8_t dir, uint8_t val);

        int (*set_frequency) (struct dibMac * fe, uint32_t freq_ref, uint32_t freq_out, uint32_t select_dll_id, uint16_t divider);

        int (*release) (struct dibMac *);

        int (*set_output_mode)(struct dibMac *, int);
        int (*set_input_mode)(struct dibMac *, int);
        int (*get_monitoring)(struct dibMac *, struct dibMacMonitor *, struct dibDemodMonitor *);

        int (*download_code)(struct dibMac *, uint8_t *code, uint32_t size, uint8_t encrypted, uint32_t jump_address);
    } ops;

    struct dibDataBusClient data_bus_client; /*! structure the mac uses to read from and write to itself (how to access the register) */
    void *priv;
};

extern void mac_init(struct dibMac *, const struct dibMac *, void *priv);

#define mac_get_name(mac) mac->name

/* stable API for dibMacOps - use this instead of the function pointers directly */
#define FE_MAC_FUNC_CHECK(obj, func)  FE_FUNC_CHECK(obj, mac, func)
#ifndef FE_MAC_FUNC_CALL
#define FE_MAC_FUNC_CALL(obj, func)   FE_FUNC_CALL(obj, mac, func)
#endif

//! Reset a mac
extern int mac_reset(struct dibMac *);

//! Wake up a mac
/**
 * Has to be called after sleep and before each tune - to put the mac into a defined state
 *
 * \param d pointer to a valid struct dibFrontend
 */
extern int mac_wakeup(struct dibMac *);

//! Software-suspend a mac.
/**
 * Put the mac to sleep per software. Note that the power consumption is
 * still higher than doing it by hardware. Temporary low-power-mode during
 * runtime.
 *
 * \param d pointer to a valid struct dibMac
 */
extern int mac_sleep(struct dibMac *, uint8_t deep);


//! Set output mode of the MAC.
/**
 * Set up the output_mode of a demod. Valid modes can be found in common.h . (e.g. OUTMODE_DIVERSITY, OUTMODE_MPEG2_SERIAL).
 *
 * \param d pointer to a valid struct dibMac
 * \param m output mode (default: OUTMODE_MPEG2_FIFO)
 */
extern int mac_set_output_mode(struct dibMac *, uint16_t mode);

//! Set intput mode of the MAC.
/**
 * Set up the intput_mode of a MAC.
 *
 * \param d pointer to a valid struct dibMac
 * \param m intput mode onoff
 */
extern int mac_set_input_mode(struct dibMac *, uint16_t mode);

//! Manipulate the GPIO of a mac
/**
 * Use this function to manipulate the state of a GPIO of the chip.
 *
 * \param d pointer to a valid struct dibMac
 * \param num number of GPIO to control (if in doubt do not touch at least GPIO1,2 and GPIO3,4)
 * \param dir GPIO direction 0 = OUT, 1 = IN
 * \param val state of the GPIO (valid only in direction out) -> 0 = low, 1 = high
 */
extern int mac_set_gpio(struct dibMac *, uint8_t num, uint8_t dir, uint8_t val);

extern int mac_set_frequency(struct dibMac * mac, uint32_t freq_ref, uint32_t freq_out, uint32_t select_dll_id, uint16_t divider);

/* for monitoring */
extern int mac_get_monitoring(struct dibMac *mac, struct dibMacMonitor *m_mac, struct dibDemodMonitor *m_demod);

/* for downloading a firmware */
extern int mac_download_code(struct dibMac * mac, uint8_t *code, uint32_t size, uint8_t encrypted, uint32_t jump_addr);

//! Free mac memory
/**
 * Calling the function cleans up and frees private memory.
 *
 * \param d pointer to a valid struct dibMac
 */
extern void mac_release(struct dibMac *);

#define mac_get_data_bus_client(d) ((d) != NULL ? &(d)->data_bus_client : NULL)

#ifdef __cplusplus
}
#endif

#endif
