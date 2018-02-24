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
#ifndef MONITOR_H
#define MONITOR_H

#include <adapter/component_monitor.h>

#ifdef CONFIG_STANDARD_ANALOG
#ifdef ANALOG_DECODER_CX2584X_MONITOR
#include <analog_decoder/cx2584x_monitor.h>
#endif
#endif

#ifdef CONFIG_TUNER_XC3028
#include <tuner/xc3028.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct dibBoardMonitor {
	int dib7000_count;
	struct dibDemodMonitor dib7000[4];

#ifdef CONFIG_STANDARD_ANALOG
#ifdef ANALOG_DECODER_CX2584X_MONITOR
	int cx2584x_count;
	struct cx2584x_monitor cx2584x;
#endif
#endif

#ifdef CONFIG_TUNER_XC3028
	int xc3028_count;
	struct xc3028_monitor xc3028;
#endif

#ifdef CONFIG_STANDARD_ANALOG
	int dib5000_count;
	struct dibAnalogVideoMonitor dib5000_video[3];
	struct dibAnalogAudioMonitor dib5000_audio[3];
#endif

	int dib0070_count;
	struct dibTunerMonitor dib0070[4];

	int channel_decoder_count;
    struct dibChannelDecoderMonitor dib_channel_decoder[2];

	int mac_count;
    struct dibMacMonitor dib_mac[2];
};

extern void dib7000_print_monitor(struct dibDemodMonitor *m, struct dibDemodStatistic s[], int stat_count, int num);
extern void channel_decoder_print_monitor(struct dibChannelDecoderMonitor *m, int num);
//extern void mac_print_monitor(struct dibMacMonitor m_mac[], struct dibDemodMonitor m_demod[], int num);

struct cx2584x_monitor;
extern void cx2584x_print_monitor(struct cx2584x_monitor *m, int num);

struct xc3028_monitor;
extern void xc3028_print_monitor(struct xc3028_monitor *m, int num);

extern void dib5000_video_print_monitor(struct dibAnalogVideoMonitor *m, int num);
extern void dib5000_audio_print_monitor(struct dibAnalogAudioMonitor *m, int num);

extern void dib0070_tuner_print_monitor(struct dibTunerMonitor *m, int num);

#ifdef __cplusplus
}
#endif

#endif
