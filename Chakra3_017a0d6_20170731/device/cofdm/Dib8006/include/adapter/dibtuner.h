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
#ifndef ADAPTER_TUNER_H
#define ADAPTER_TUNER_H

#include "frontend.h"
#include "databus.h"

#ifdef __cplusplus
extern "C" {
#endif

struct dibTunerMonitor;

#define TUNER_CAN_VHF   0x001
#define TUNER_CAN_UHF   0x002
#define TUNER_CAN_LBAND 0x004
#define TUNER_CAN_SBAND     0x008
#define TUNER_CAN_FAST_TUNE 0x010

#define TUNER_MAX_USE_COUNT 3

//! generic description of a Tuner
/**
 * This struct describes a tuner in generic way. Each tuner-driver has to implement one.
 */
struct dibTunerInfo {
	const char name[MAX_INFO_NAME_LENGTH]; /*! Keeps a human-readable name as a string. */
	int caps; /*! Defines the capabilities. */

	struct { /*! Generic operations each tuner has to provide */
        int (*reset) (struct dibFrontend *);
		int (*wakeup) (struct dibFrontend *); /*! Called after sleep and before each tune - to put the tuner into a defined state */
		int (*sleep) (struct dibFrontend *); /*! Put the tuner to sleep per software. Note that the power consumption is still higher than doing it by hardware. Temporary low-power-mode during runtime. */
		int (*tune_digital) (struct dibFrontend *, struct dibChannel *); /*! Tune the tuner to a channel */
		int (*tune_analog) (struct dibFrontend *, struct dibAnalogChannel *); /*! Tune the tuner in analog mode */
		int (*generic_monitoring) (struct dibFrontend *, uint32_t type, uint8_t *buf, uint32_t size, uint32_t offset); /*! Get monitoring information of the tuner. */
		int (*release) (struct dibFrontend *); /*! The tuner has to implement a function where it does his cleanup such an free private memory etc. . This is the field to fill for that. */
	} ops;

	int use_count; /*! This field is used for shared tuners not to use them in different configurations : add 2 for digital 1 for each analog (internal use only) */
    struct dibDataBusClient data_bus_client; /*! structure to get access to the registers of the tuner */

    uint32_t callback_time;
};

#define tuner_get_name(fe) fe->tuner_info->name

/* stable API for dibTunerOps - use this instead of the function pointers directly */
#define FE_TUNER_FUNC_CHECK(obj, func)  FE_FUNC_CHECK(obj, tuner_info, func)
#define FE_TUNER_FUNC_CALL(obj, func)   FE_FUNC_CALL(obj,  tuner_info, func)

extern int tuner_reset(struct dibFrontend *);
extern int tuner_init(struct dibFrontend *);
#define tuner_wakeup tuner_init

extern int tuner_sleep(struct dibFrontend *);

extern int tuner_tune(struct dibFrontend *fe, struct dibChannel *ch);

extern int tuner_tune_fast(struct dibFrontend *fe, struct dibChannel *ch);

#ifndef NO_DVBCHANNEL_BACKWARD_COMPAT
extern int tuner_tune_digital(struct dibFrontend *, struct dibDVBChannel *);
#endif

/* setting the bandwidth of a tuner is optional */
#define tuner_set_bandwidth_ex(f, c) DIB_RETURN_SUCCESS
#define tuner_set_bandwidth(f, c)    DIB_RETURN_SUCCESS

extern int tuner_tune_analog(struct dibFrontend *, struct dibAnalogChannel *);

extern int tuner_get_frequency(struct dibFrontend *);

void tuner_release(struct dibFrontend *);

extern struct dibDataBusClient * tuner_get_data_bus_client(struct dibFrontend *);
#define tuner_get_register_access(t) tuner_get_data_bus_client(t)

extern int tuner_try_inc_use_count(struct dibFrontend *, int);
extern int tuner_inc_use_count(struct dibFrontend *, int);
extern int tuner_dec_use_count(struct dibFrontend *, int);

extern int tuner_use_count(struct dibFrontend *);

#ifdef __cplusplus
}
#endif

#endif
