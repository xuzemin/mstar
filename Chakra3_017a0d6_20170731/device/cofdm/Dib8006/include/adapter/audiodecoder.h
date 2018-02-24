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
#ifndef ADAPTER_AUDIODECODER_H
#define ADAPTER_AUDIODECODER_H

#include "common.h"
#include "databus.h"

#ifdef __cplusplus
extern "C" {
#endif

enum dibAudioStandard {
    AUDIO_STANDARD_NONE = 0,
	AUDIO_STANDARD_AUTO,
    AUDIO_STANDARD_BTSC,
    AUDIO_STANDARD_EIAJ,
    AUDIO_STANDARD_NICAM_BG,
    AUDIO_STANDARD_NICAM_DK,
    AUDIO_STANDARD_NICAM_L,
    AUDIO_STANDARD_NICAM_I,
    AUDIO_STANDARD_A2_M,
    AUDIO_STANDARD_FM,
	AUDIO_STANDARD_AM_L,
};

/*this value is a bit mask*/
enum dibAudioInput {
   AUDIO_TV_INPUT = 0x1,
   AUDIO_FM_INPUT = 0x2,
   AUDIO_TUNER_INPUT = AUDIO_FM_INPUT | AUDIO_TV_INPUT,
   AUDIO_INPUT_LINE = 0x4,
   AUDIO_MUTE = 0x8,
};


struct dibAudioStatus
{
	enum dibAudioStandard standard;
	uint32_t                mode;
    uint8_t                 locked;
#define FREQUENCY_LOCKED    0
#define FREQUENCY_TOO_LOW   1
#define FREQUENCY_TOO_HIGH  2
    uint8_t                 PLL_offset;
};

struct dibAnalogAudioMonitor;

struct dibAudioDecoderInfo
{
	const char *name;
	struct {
        int  (*reset)          (struct dibFrontend *);

		int  (*wakeup)         (struct dibFrontend *);
		int  (*sleep)          (struct dibFrontend *);

		int  (*set_input)      (struct dibFrontend *, enum dibAudioInput);
		int  (*set_standard)   (struct dibFrontend *, enum dibAudioStandard);
		int  (*set_mode)       (struct dibFrontend *, uint32_t audio_mode);
		int  (*set_smpl_freq)  (struct dibFrontend *, uint32_t frequency);

		void (*get_status)     (struct dibFrontend *, struct dibAudioStatus *);
		void (*get_mode)       (struct dibFrontend *, uint32_t *audio_mode);

		void (*notify)         (struct dibFrontend *, enum dibChannelChange);

		int  (*get_monitoring) (struct dibFrontend *, struct dibAnalogAudioMonitor *);

		void (*release)        (struct dibFrontend *);
	} ops;

    uint8_t  powered_up;
	uint8_t  muted;
	uint32_t standard;
	uint32_t tv_audio_mode;
	enum dibAudioInput input;
	uint32_t frequency;

	struct dibDataBusClient data_bus_client;
};

extern void audio_decoder_init(struct dibFrontend *);

#define audio_decoder_get_name(fe) fe->audio_info->name

#define FE_AUDIO_FUNC_CHECK(obj, func)  FE_FUNC_CHECK(obj, audio_info, func)
#define FE_AUDIO_FUNC_CALL(obj, func)   FE_FUNC_CALL(obj,  audio_info, func)

#define audio_decoder_reset(a) (FE_AUDIO_FUNC_CHECK(a, reset) ? FE_AUDIO_FUNC_CALL(a, reset)(a) : DIB_RETURN_SUCCESS)

#define audio_decoder_wake_up(a) (FE_AUDIO_FUNC_CHECK(a, wakeup) ? FE_AUDIO_FUNC_CALL(a, wakeup)(a) : DIB_RETURN_ERROR)
#define audio_decoder_wakeup audio_decoder_wake_up

#define audio_decoder_sleep(a) (FE_AUDIO_FUNC_CHECK(a, sleep) ? FE_AUDIO_FUNC_CALL(a,sleep)(a) : DIB_RETURN_ERROR)

#define audio_decoder_set_input(a, i) (FE_AUDIO_FUNC_CHECK(a,set_input) ? FE_AUDIO_FUNC_CALL(a,set_input)(a, i) : DIB_RETURN_ERROR)
#define audio_decoder_set_standard(a, s) (FE_AUDIO_FUNC_CHECK(a, set_standard) ? FE_AUDIO_FUNC_CALL(a,set_standard)(a, s) : DIB_RETURN_ERROR)
#define audio_decoder_set_mode(a, m) (FE_AUDIO_FUNC_CHECK(a,set_mode) ? FE_AUDIO_FUNC_CALL(a,set_mode)(a, m) : DIB_RETURN_ERROR)
#define audio_decoder_set_sampling_frequency(a, f) (FE_AUDIO_FUNC_CHECK(a, set_smpl_freq) ? FE_AUDIO_FUNC_CALL(a, set_smpl_freq)(a, f) : DIB_RETURN_ERROR)

#define audio_decoder_get_status(a, s) do { if (FE_AUDIO_FUNC_CHECK(a, get_status)) FE_AUDIO_FUNC_CALL(a,get_status)(a, s); } while (0)
#define audio_decoder_get_mode(a, m) do { if (FE_AUDIO_FUNC_CHECK(a, get_mode)) FE_AUDIO_FUNC_CALL(a,get_mode)(a, m); } while (0)

#define audio_decoder_notify_channel_change(a, c) do { if (FE_AUDIO_FUNC_CHECK(a, notify)) FE_AUDIO_FUNC_CALL(a, notify)(a, c); } while(0)

#define audio_decoder_get_monitoring(a, m) (FE_AUDIO_FUNC_CHECK(a, get_monitoring) ? FE_AUDIO_FUNC_CALL(a, get_monitoring)(a, m) : DIB_RETURN_ERROR)

#define audio_decoder_release(a) do { if (FE_AUDIO_FUNC_CHECK(a,release)) FE_AUDIO_FUNC_CALL(a, release)(a); } while (0)

#ifdef __cplusplus
}
#endif

#endif
