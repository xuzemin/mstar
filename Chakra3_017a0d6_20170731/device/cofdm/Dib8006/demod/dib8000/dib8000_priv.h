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
#ifndef DEMOD_DIB7000M_PRIV_H
#define DEMOD_DIB7000M_PRIV_H

#include "frontend.h"

#include "dib8000.h"

#include "dibx000_i2c_common.h"

enum dib8000_autosearch_step {
    AS_START = 0,
    AS_SEARCHING_FFT,
    AS_SEARCHING_GUARD,
    AS_DONE = 100,
};

enum param_loop_step {
    LOOP_TUNE_1,
    LOOP_TUNE_2
};

enum timeout_mode {
    SYMBOL_DEPENDENT_OFF = 0,
    SYMBOL_DEPENDENT_ON,
};

struct dib8000_state {
        struct dibDemodInfo info;
	struct dibFrontend *fe;

        struct dib8000_config cfg;

	struct dibx000_i2c_master i2c_master;

	uint16_t wbd_ref;

	uint8_t current_band;
	const struct dibx000_agc_config *current_agc;

	uint32_t timf_default;
	uint32_t timf;

	uint16_t revision;
        uint32_t timeout;

	/* tempory */
	uint8_t differential_constellation;
	int diversity_onoff;
	int ber_monitored_layer;
	uint16_t saved_registers[6];
	uint8_t layer_b_nb_seg;
	uint8_t layer_c_nb_seg;
        uint8_t isdbt_cfg_loaded;
        uint8_t subchannel;

        uint16_t seg_mask;
        uint16_t seg_diff_mask;
        uint16_t mode;
        uint8_t symbol_duration;

        uint16_t autosearch_state;
        uint16_t found_nfft;
        uint16_t found_guard;
        uint8_t longest_intlv_layer;
        uint16_t output_mode;
};

#define dib8000_read(st, subaddress, buf, len) data_bus_client_read(demod_get_data_bus_client(st->fe), subaddress, buf, len)
#define dib8000_write(st, subaddress, buf, len) data_bus_client_write(demod_get_data_bus_client(st->fe), subaddress, buf, len)

#define dib8000_read_word(st, subaddress)     data_bus_client_read16( demod_get_data_bus_client(st->fe), subaddress)
#define dib8000_write_word(st, subaddress, v) data_bus_client_write16( demod_get_data_bus_client(st->fe), subaddress, v)
#define dib8000_read32(st, address)              data_bus_client_read32(demod_get_data_bus_client(st->fe), address)

/* private use only */
enum dib8000_power_mode {
	DIB8000M_POWER_ALL = 0,
	DIB8000M_POWER_INTERFACE_ONLY,
};
extern void dib8000_set_power_mode(struct dib8000_state *, enum dib8000_power_mode);

extern int dib8000_set_bandwidth(struct dib8000_state *, uint32_t bw_idx);

extern int dib8000_reset_gpio(struct dib8000_state *);
extern int dib8000_cfg_gpio(struct dib8000_state *st, uint8_t num, uint8_t dir, uint8_t val);

extern int dib8000_set_adc_state(struct dib8000_state *state, enum dibx000_adc_states);

extern int dib8000_set_output_mode(struct dib8000_state *state, int mode);

/* demod operations */
extern int dib8000_set_diversity_in(struct dibFrontend *, int onoff);
extern void dib8000_autosearch_start(struct dibFrontend *, struct dibChannel *ch);
extern int dib8000_autosearch_is_irq(struct dibFrontend *);
extern int dib8000_pid_filter_ctrl(struct dibFrontend *, uint8_t onoff);
extern int dib8000_pid_filter(struct dibFrontend *, uint8_t id, uint16_t pid, uint8_t onoff);
extern int dib8000_dvb_t_get_channel_description(struct dibFrontend *, struct dibChannel *cd);
extern int dib8000_tune(struct dibFrontend *, struct dibChannel *ch);

extern void dib8000_update_timf(struct dib8000_state *state);
extern int dib8000_agc_startup(struct dibFrontend *, struct dibChannel *ch);

/* extended monitoring */
extern int dib8000_generic_monitoring(struct dibFrontend *, uint32_t type, uint8_t *buf, uint32_t size, uint32_t offset);

extern const struct dibDebugObject dib8000_dbg;

extern void dib8000_set_timf(struct dibFrontend *fe, uint32_t timf);
extern int dib8000_get_timf(struct dibFrontend *fe);
extern void dib8000_set_dds(struct dib8000_state *state, int32_t offset_khz);


extern int dib8000_get_sb_subchannel(struct dib8000_state *state, struct dibChannel *ch);
#endif
