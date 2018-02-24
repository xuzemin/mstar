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
#include "mac.h"

void mac_init(struct dibMac *target, const struct dibMac *src, void *priv)
{
    memcpy(target, src, sizeof(*target));
    target->priv = priv;
}

int mac_reset(struct dibMac *mac)
{
    if (mac && mac->ops.reset)
        return mac->ops.reset(mac);
    return DIB_RETURN_SUCCESS;
}

int mac_wakeup(struct dibMac *mac)
{
    if (mac && mac->ops.wakeup)
        return mac->ops.wakeup(mac);
    return DIB_RETURN_SUCCESS;
}

int mac_sleep(struct dibMac *mac, uint8_t deep)
{
    if (mac && mac->ops.sleep)
        return mac->ops.sleep(mac, deep);
    return DIB_RETURN_SUCCESS;
}

int mac_set_gpio(struct dibMac *mac, uint8_t num, uint8_t dir, uint8_t val)
{
    if (mac && mac->ops.set_gpio)
        return mac->ops.set_gpio(mac, num, dir, val);
    return DIB_RETURN_SUCCESS;
}

#ifdef CONFIG_BUILD_HOST
int mac_set_frequency(struct dibMac * mac, uint32_t freq_ref, uint32_t freq_out, uint32_t select_dll_id, uint16_t divider)
{
    if (mac && mac->ops.set_frequency)
        return mac->ops.set_frequency(mac, freq_ref, freq_out, select_dll_id, divider);
    return DIB_RETURN_SUCCESS;
}
#endif

int mac_set_output_mode(struct dibMac *mac, uint16_t mode)
{
    if (mac != NULL && mac->ops.set_output_mode)
        return mac->ops.set_output_mode(mac, mode);
    return DIB_RETURN_SUCCESS;
}

#ifdef CONFIG_BUILD_HOST
int mac_download_code(struct dibMac * mac, uint8_t *code, uint32_t size, uint8_t encrypted, uint32_t jump_addr)
{
    if (mac != NULL && mac->ops.download_code)
        return mac->ops.download_code(mac, code, size, encrypted, jump_addr);
    return DIB_RETURN_SUCCESS;
}
#endif
void mac_release(struct dibMac *mac)
{
    if (mac != NULL && mac->ops.release)
        mac->ops.release(mac);
}

int mac_set_input_mode(struct dibMac *mac, uint16_t mode)
{
    if (mac != NULL && mac->ops.set_input_mode)
        return mac->ops.set_input_mode(mac, mode);
    return DIB_RETURN_SUCCESS;
}
#ifdef CONFIG_BUILD_HOST
int mac_get_monitoring(struct dibMac *mac, struct dibMacMonitor *m_mac , struct dibDemodMonitor *m_demod)
{
    if (mac != NULL && mac->ops.get_monitoring)
        return mac->ops.get_monitoring(mac, m_mac, m_demod);
    return DIB_RETURN_SUCCESS;
}
#endif
