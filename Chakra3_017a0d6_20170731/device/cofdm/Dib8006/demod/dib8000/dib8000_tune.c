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
#include "dib8000_priv.h"
#include "msAPI_Timer.h"
//#define DEBUG_DIB8000_TUNE
#define CONFIG_DIB8000_NEW_AUTOSEARCH

static const int16_t coeff_2k_sb_1seg_dqpsk[8] =
{
  (769 << 5) | 0x0a, (745 << 5) | 0x03, (595 << 5) | 0x0d, (769 << 5) | 0x0a, (920 << 5) | 0x09, (784 << 5) | 0x02, (519 << 5) | 0x0c, (920 << 5) | 0x09
};

static const int16_t coeff_2k_sb_1seg[8] =
{
  (692 << 5) | 0x0b, (683 << 5) | 0x01, (519 << 5) | 0x09, (692 << 5) | 0x0b, 0 | 0x1f, 0 | 0x1f, 0 | 0x1f, 0 | 0x1f
};

static const int16_t coeff_2k_sb_3seg_0dqpsk_1dqpsk[8] =
{
  (832 << 5) | 0x10, (912 << 5) | 0x05, (900 << 5) | 0x12, (832 << 5) | 0x10, (-931 << 5) | 0x0f, (912 << 5) | 0x04, (807 << 5) | 0x11, (-931 << 5) | 0x0f
};

static const int16_t coeff_2k_sb_3seg_0dqpsk[8] =
{
  (622 << 5) | 0x0c, (941 << 5) | 0x04, (796 << 5) | 0x10, (622 << 5) | 0x0c, (982 << 5) | 0x0c, (519 << 5) | 0x02, (572 << 5) | 0x0e, (982 << 5) | 0x0c
};

static const int16_t coeff_2k_sb_3seg_1dqpsk[8] =
{
  (699 << 5) | 0x14, (607 << 5) | 0x04, (944 << 5) | 0x13, (699 << 5) | 0x14, (-720 << 5) | 0x0d, (640 << 5) | 0x03, (866 << 5) | 0x12, (-720 << 5) | 0x0d
};

static const int16_t coeff_2k_sb_3seg[8] =
{
  (664 << 5) | 0x0c, (925 << 5) | 0x03, (937 << 5) | 0x10, (664 << 5) | 0x0c, (-610 << 5) | 0x0a, (697 << 5) | 0x01, (836 << 5) | 0x0e, (-610 << 5) | 0x0a
};

static const int16_t coeff_4k_sb_1seg_dqpsk[8] =
{
  (-955 << 5) | 0x0e, (687 << 5) | 0x04, (818 << 5) | 0x10, (-955 << 5) | 0x0e, (-922 << 5) | 0x0d, (750 << 5) | 0x03, (665 << 5) | 0x0f, (-922 << 5) | 0x0d
};

static const int16_t coeff_4k_sb_1seg[8] =
{
  (638 << 5) | 0x0d, (683 << 5) | 0x02, (638 << 5) | 0x0d, (638 << 5) | 0x0d, (-655 << 5) | 0x0a, (517 << 5) | 0x00, (698 << 5) | 0x0d, (-655 << 5) | 0x0a
};

static const int16_t coeff_4k_sb_3seg_0dqpsk_1dqpsk[8] = {
  (-707 << 5) | 0x14, (910 << 5) | 0x06, (889 << 5) | 0x16, (-707 << 5) | 0x14, (-958 << 5) | 0x13, (993 << 5) | 0x05, (523 << 5) | 0x14, (-958 << 5) | 0x13
};

static const int16_t coeff_4k_sb_3seg_0dqpsk[8] = {
  (-723 << 5) | 0x13, (910 << 5) | 0x05, (777 << 5) | 0x14, (-723 << 5) | 0x13, (-568 << 5) | 0x0f, (547 << 5) | 0x03, (696 << 5) | 0x12, (-568 << 5) | 0x0f
};

static const int16_t coeff_4k_sb_3seg_1dqpsk[8] =
{
  (-940 << 5) | 0x15, (607 << 5) | 0x05, (915 << 5) | 0x16, (-940 << 5) | 0x15, (-848 << 5) | 0x13, (683 << 5) | 0x04, (543 << 5) | 0x14, (-848 << 5) | 0x13
};

static const int16_t coeff_4k_sb_3seg[8] =
{
  (612 << 5) | 0x12, (910 << 5) | 0x04, (864 << 5) | 0x14, (612 << 5) | 0x12, (-869 << 5) | 0x13, (683 << 5) | 0x02, (869 << 5) | 0x12, (-869 << 5) | 0x13
};

static const int16_t coeff_8k_sb_1seg_dqpsk[8] =
{
  (-835 << 5) | 0x12, (684 << 5) | 0x05, (735 << 5) | 0x14, (-835 << 5) | 0x12, (-598 << 5) | 0x10, (781 << 5) | 0x04, (739 << 5) | 0x13, (-598 << 5) | 0x10
};

static const int16_t coeff_8k_sb_1seg[8] =
{
  (673 << 5) | 0x0f, (683 << 5) | 0x03, (808 << 5) | 0x12, (673 << 5) | 0x0f, (585 << 5) | 0x0f, (512 << 5) | 0x01, (780 << 5) | 0x0f, (585 << 5) | 0x0f
};

static const int16_t coeff_8k_sb_3seg_0dqpsk_1dqpsk[8] =
{
  (863 << 5) | 0x17, (930 << 5) | 0x07, (878 << 5) | 0x19, (863 << 5) | 0x17, (0   << 5) | 0x14, (521 << 5) | 0x05, (980 << 5) | 0x18, (0   << 5) | 0x14
};

static const int16_t coeff_8k_sb_3seg_0dqpsk[8] =
{
  (-924 << 5) | 0x17, (910 << 5) | 0x06, (774 << 5) | 0x17, (-924 << 5) | 0x17, (-877 << 5) | 0x15, (565 << 5) | 0x04, (553 << 5) | 0x15, (-877 << 5) | 0x15
};

static const int16_t coeff_8k_sb_3seg_1dqpsk[8] =
{
  (-921 << 5) | 0x19, (607  << 5) | 0x06, (881  << 5) | 0x19, (-921 << 5) | 0x19, (-921 << 5) | 0x14, (713  << 5) | 0x05, (1018 << 5) | 0x18, (-921  << 5) | 0x14
};

static const int16_t coeff_8k_sb_3seg[8] =
{
  (514 << 5) | 0x14, (910 << 5) | 0x05, (861 << 5) | 0x17, (514 << 5) | 0x14, (690 << 5) | 0x14, (683 << 5) | 0x03, (662 << 5) | 0x15, (690 << 5) | 0x14
};

static const int16_t ana_fe_coeff_3seg[24]  =
{
    81, 80, 78, 74, 68, 61, 54, 45, 37, 28, 19, 11, 4, 1022, 1017, 1013, 1010, 1008, 1008, 1008, 1008, 1010, 1014, 1017
};

static const int16_t ana_fe_coeff_1seg[24]  =
{
    249, 226, 164, 82, 5, 981, 970, 988, 1018, 20, 31, 26, 8, 1012, 1000, 1018, 1012, 8, 15, 14, 9, 3, 1017, 1003
};

static const int16_t ana_fe_coeff_13seg[24] =
{
    396, 305, 105, -51, -77, -12, 41, 31, -11, -30, -11, 14, 15, -2, -13, -7, 5, 8, 1, -6, -7, -3, 0, 1
};

static int fft_to_mode(struct dib8000_state *state, struct dibChannel *ch)
{	state = state;
    switch(ch->u.isdbt.nfft) {
    	case FFT_2K: return 1;
    	case FFT_4K: return 2;
    	default:
    	case FFT_AUTO:
    	case FFT_8K: return 3;
    }
}

static void dib8000_restart_agc(struct dib8000_state *state)
{
	// P_restart_iqc & P_restart_agc
	dib8000_write_word(state, 770, 0x0a00);
	dib8000_write_word(state, 770, 0x0000);
}

static int dib8000_update_lna(struct dib8000_state *state)
{
	uint16_t dyn_gain;

	if (state->cfg.update_lna) {
		// read dyn_gain here (because it is demod-dependent and not tuner)
		dyn_gain = dib8000_read_word(state, 390);

		if (state->cfg.update_lna(state->fe, dyn_gain)) { // LNA has changed
			dib8000_restart_agc(state);
			return 1;
		}
	}
	return 0;
}

void dib8000_update_timf(struct dib8000_state *state)
{
	uint32_t timf = state->timf = dib8000_read32(state, 435);

	dib8000_write_word(state, 29, (uint16_t) (timf >> 16));
	dib8000_write_word(state, 30, (uint16_t) (timf & 0xffff));
	dbgp("FE %d Updated timing frequency: %d (default: %d)\n",state->fe->id, state->timf, state->timf_default);
}

static int dib8000_agc_soft_split(struct dib8000_state *state)
{
	uint16_t agc,split_offset;

	if(!state->current_agc || !state->current_agc->perform_agc_softsplit || state->current_agc->split.max == 0)
		return FE_CALLBACK_TIME_NEVER;

	// n_agc_global
	agc = dib8000_read_word(state, 390);

	if (agc > state->current_agc->split.min_thres)
		split_offset = state->current_agc->split.min;
	else if (agc < state->current_agc->split.max_thres)
		split_offset = state->current_agc->split.max;
	else
		split_offset = state->current_agc->split.max *
			(agc - state->current_agc->split.min_thres) /
			(state->current_agc->split.max_thres - state->current_agc->split.min_thres);

	dbgp("FE %d AGC split_offset: %d\n",state->fe->id, split_offset);

	// P_agc_force_split and P_agc_split_offset
	dib8000_write_word(state, 107, (dib8000_read_word(state, 107) & 0xff00) | split_offset);
    return 5000;
}

static int dib8000_set_agc_config(struct dib8000_state *state, uint8_t band)
{
	const struct dibx000_agc_config *agc = NULL;
	int i;
	if (state->current_band == band  && state->current_agc != NULL){
		return DIB_RETURN_SUCCESS;
	}
	state->current_band = band;

	for (i = 0; i < state->cfg.agc_config_count; i++)
		if (state->cfg.agc[i].band_caps & band) {
			agc = &state->cfg.agc[i];
			break;
		}

	if (agc == NULL) {
		dbgp("FE %d No valid AGC configuration found for band 0x%02x\n",state->fe->id, band);
		return DIB_RETURN_ERROR;
	}
	state->current_agc = agc;

	/* AGC */
	dib8000_write_word(state, 76 ,  agc->setup);
	dib8000_write_word(state, 77 ,  agc->inv_gain);
	dib8000_write_word(state, 78 ,  agc->time_stabiliz);
	dib8000_write_word(state, 101 , (agc->alpha_level << 12) | agc->thlock);

	// Demod AGC loop configuration
	dib8000_write_word(state, 102, (agc->alpha_mant << 5) | agc->alpha_exp);
	dib8000_write_word(state, 103, (agc->beta_mant  << 6) | agc->beta_exp);

	dbgp("FE %d WBD: ref: %d, sel: %d, active: %d, alpha: %d\n",
		state->fe->id, state->wbd_ref != 0 ? state->wbd_ref : agc->wbd_ref, agc->wbd_sel, !agc->perform_agc_softsplit, agc->wbd_sel);

	/* AGC continued */
	if (state->wbd_ref != 0)
		dib8000_write_word(state, 106, state->wbd_ref);
	else // use default
		dib8000_write_word(state, 106, agc->wbd_ref);
	dib8000_write_word(state, 107, (agc->wbd_alpha << 9) | (agc->perform_agc_softsplit << 8) );
	dib8000_write_word(state, 108,  agc->agc1_max);
	dib8000_write_word(state, 109,  agc->agc1_min);
	dib8000_write_word(state, 110,  agc->agc2_max);
	dib8000_write_word(state, 111,  agc->agc2_min);
	dib8000_write_word(state, 112, (agc->agc1_pt1 << 8) | agc->agc1_pt2 );
	dib8000_write_word(state, 113, (agc->agc1_slope1 << 8) | agc->agc1_slope2);
	dib8000_write_word(state, 114, (agc->agc2_pt1 << 8) | agc->agc2_pt2);
	dib8000_write_word(state, 115, (agc->agc2_slope1 << 8) | agc->agc2_slope2);

	dib8000_write_word(state, 75,   agc->agc1_pt3);
	dib8000_write_word(state, 923, (dib8000_read_word(state, 923) & 0xffe3) | (agc->wbd_inv << 4) | (agc->wbd_sel << 2)); /*LB : 929 -> 923*/

	return DIB_RETURN_SUCCESS;
}

void dib8000_pwm_agc_reset(struct dibFrontend *fe, struct dibChannel *ch)
{
	struct dib8000_state *state = fe->demod_priv;
    dib8000_set_adc_state(state, DIBX000_ADC_ON);
    dib8000_set_agc_config(state, (unsigned char)(BAND_OF_FREQUENCY(ch->RF_kHz)));
}

int dib8000_agc_startup(struct dibFrontend *fe, struct dibChannel *ch)
{
	struct dib8000_state *state = fe->demod_priv;
	enum frontend_tune_state *tune_state = &fe->tune_state;

    int ret = 0;

	switch (*tune_state) {
    case CT_AGC_START:
        // set power-up level: interf+analog+AGC
        dib8000_set_adc_state(state, DIBX000_ADC_ON);

        if (dib8000_set_agc_config(state, (unsigned char)(BAND_OF_FREQUENCY(ch->RF_kHz))) != DIB_RETURN_SUCCESS) {
            *tune_state = CT_AGC_STOP;
            fe->status = FE_STATUS_TUNE_FAILED;
			break;
        }

        ret = 70;
        *tune_state = CT_AGC_STEP_0;
        break;

    case CT_AGC_STEP_0:
        //AGC initialization
        if (state->cfg.agc_control)
            state->cfg.agc_control(state->fe, 1);

        dib8000_restart_agc(state);

        // wait AGC rough lock time
        ret = 50;
        *tune_state = CT_AGC_STEP_1;
        break;

    case CT_AGC_STEP_1:
        // wait AGC accurate lock time
        ret = 70;

        if (dib8000_update_lna(state))
            // wait only AGC rough lock time
            ret = 50;
        else
            *tune_state = CT_AGC_STEP_2;
        break;

    case CT_AGC_STEP_2:
        dib8000_agc_soft_split(state);

        if (state->cfg.agc_control)
            state->cfg.agc_control(state->fe, 0);

        *tune_state = CT_AGC_STOP;
        break;
    default:
        ret = dib8000_agc_soft_split(state);
        break;
    }
	return ret;

}

static const uint16_t lut_prbs_2k[14] =
{
    0, 0x423, 0x009, 0x5C7, 0x7A6, 0x3D8, 0x527, 0x7FF, 0x79B, 0x3D6, 0x3A2, 0x53B, 0x2F4, 0x213
};
static const uint16_t lut_prbs_4k[14] =
{
    0, 0x208, 0x0C3, 0x7B9, 0x423, 0x5C7, 0x3D8, 0x7FF, 0x3D6, 0x53B, 0x213, 0x029, 0x0D0, 0x48E
};
static const uint16_t lut_prbs_8k[14] =
{
    0, 0x740, 0x069, 0x7DD, 0x208, 0x7B9, 0x5C7, 0x7FF, 0x53B, 0x029, 0x48E, 0x4C4, 0x367, 0x684
};

static uint16_t dib8000_get_init_prbs(uint16_t subchannel, struct dibChannel *ch)
{
    int sub_channel_prbs_group = 0;

   sub_channel_prbs_group = (uint16_t) (subchannel / 3) +1;
   dbgp("sub_channel_prbs_group = %d , subchannel =%d prbs = 0x%04x\n",sub_channel_prbs_group, subchannel, lut_prbs_8k[sub_channel_prbs_group]);

    switch (ch->u.isdbt.nfft) {
        case FFT_2K : return lut_prbs_2k[sub_channel_prbs_group];
        case FFT_4K : return lut_prbs_4k[sub_channel_prbs_group];
        default:
        case FFT_8K : return lut_prbs_8k[sub_channel_prbs_group];
    }
}

static void dib8000_set_subchannel_prbs(struct dib8000_state *state, uint16_t init_prbs)
{
    uint16_t reg_1;
    reg_1 = dib8000_read_word(state, 1);
    //dbgpl(&dib8000_dbg,"set init_prbs = 0x%04x",init_prbs);
    dib8000_write_word(state, 1, (init_prbs<<2) | (reg_1&0x3)); // ADDR 1
}

/*
    uint16_t adc_target_16dB[11] = {(1 << 13) - 825 - 117, (1 << 13) - 837 - 117, (1 << 13) - 811 - 117, (1 << 13) - 766 - 117, (1 << 13) - 737 - 117,
                                    (1 << 13) - 693 - 117, (1 << 13) - 648 - 117, (1 << 13) - 619 - 117, (1 << 13) - 575 - 117, (1 << 13) - 531 - 117, (1 << 13) - 501 - 117};
*/
static const uint16_t adc_target_16dB[11] = { 7250, 7238, 7264, 7309, 7338, 7382, 7427, 7456, 7500, 7544, 7574};
static const uint8_t permu_seg[13] = { 6, 5, 7, 4, 8, 3, 9, 2, 10, 1, 11, 0, 12};

static void dib8000_update_ana_gain(struct dib8000_state *state, uint16_t ana_gain)
{
    uint16_t i;
    dib8000_write_word(state, 116 , ana_gain);

    // update ADC target depending on ana_gain
    if(ana_gain) { // set -16dB ADC target for ana_gain=-1
        for (i = 0; i < 10; i++)
            dib8000_write_word(state, 80+i , adc_target_16dB[i]);
    } else { // set -22dB ADC target for ana_gain=0
        for (i = 0; i < 10; i++)
            dib8000_write_word(state, 80+i , adc_target_16dB[i]-355);
    }
}

static void dib8000_load_ana_fe_coefs(struct dib8000_state *state, const int16_t *ana_fe)
{
    uint16_t mode = 0;
    if (state->isdbt_cfg_loaded == 0)
        for (mode = 0; mode < 24; mode++)
            dib8000_write_word(state, 117 + mode , ana_fe[mode]);
}

/*
* channel estimation fine configuration
*/
static const uint16_t adp_Q64[4]      = {0x0148, 0xfff0, 0x00a4, 0xfff8}; /* P_adp_regul_cnt 0.04, P_adp_noise_cnt -0.002, P_adp_regul_ext 0.02, P_adp_noise_ext -0.001 */
static const uint16_t adp_Q16[4]      = {0x023d, 0xffdf, 0x00a4, 0xfff0}; /* P_adp_regul_cnt 0.07, P_adp_noise_cnt -0.004, P_adp_regul_ext 0.02, P_adp_noise_ext -0.002 */
static const uint16_t adp_Qdefault[4] = {0x099a, 0xffae, 0x0333, 0xfff8}; /* P_adp_regul_cnt 0.3,  P_adp_noise_cnt -0.01,  P_adp_regul_ext 0.1,  P_adp_noise_ext -0.002 */
static uint16_t dib8000_adp_fine_tune(struct dib8000_state *state, uint16_t max_constellation)
{
    uint16_t i, ana_gain = 0;
    const uint16_t * adp;

    /* channel estimation fine configuration */
    switch (max_constellation) {
        case QAM_64QAM:
	    ana_gain = 0x7; // -1 : avoid def_est saturation when ADC target is -16dB
            adp = &adp_Q64[0];
            //if (!state->cfg.hostbus_diversity) //if diversity, we should prehaps use the configuration of the max_constallation -1
            break;
        case QAM_16QAM:
            ana_gain = 0x7; // -1 : avoid def_est saturation when ADC target is -16dB
            adp = &adp_Q16[0];
            //if (!((state->cfg.hostbus_diversity) && (max_constellation == QAM_16QAM)))
            break;
        default:
            ana_gain = 0; // 0 : goes along with ADC target at -22dB to keep good mobile performance and lock at sensitivity level
            adp = &adp_Qdefault[0];
            break;
    }

    for (i = 0; i < 4; i++)
        dib8000_write_word(state, 215 + i , adp[i]);

    return ana_gain;
}

static void dib8000_set_isdbt_loop_params(struct dib8000_state *state, struct dibChannel *ch, enum param_loop_step loop_step)
{
    uint16_t reg_32 = 0, reg_37 = 0;

    switch (loop_step) {
        case LOOP_TUNE_1:
            if (ch->u.isdbt.sb_mode)  {
                if (ch->u.isdbt.partial_reception == 0) {
                    reg_32 = ((11-state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_alpha = (11-P_mode), P_corm_alpha=6, P_corm_thres=0x40 */
                    reg_37 = (3 << 5 ) | ( 0 << 4) | (10-state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = (10-P_mode)  */
                } else { /* Sound Broadcasting mode 3 seg */
                    reg_32 = ((10-state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_alpha = (10-P_mode), P_corm_alpha=6, P_corm_thres=0x60 */
                    reg_37 = (3 << 5 ) | ( 0 << 4) | (9-state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = (9-P_mode)  */
                }
            } else { /* 13-seg start conf offset loop parameters */
                reg_32 =((9-state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_alpha = (9-P_mode, P_corm_alpha=6, P_corm_thres=0x80 */
                reg_37 = (3 << 5 ) | ( 0 << 4) | (8-state->mode); /* P_ctrl_pha_off_max=3   P_ctrl_sfreq_inh =0  P_ctrl_sfreq_step = 9  */
            }
        break;
        case LOOP_TUNE_2:
            if (ch->u.isdbt.sb_mode)  {
                if (ch->u.isdbt.partial_reception == 0) {  // Sound Broadcasting mode 1 seg
                    reg_32 = ((13-state->mode) << 12) | (6 << 8) | 0x40; /* P_timf_alpha = (13-P_mode) , P_corm_alpha=6, P_corm_thres=0x40*/
                    reg_37 = (12-state->mode) | ((5+state->mode) << 5);
                } else {  // Sound Broadcasting mode 3 seg
                    reg_32 = ((12-state->mode) << 12) | (6 << 8) | 0x60; /* P_timf_alpha = (12-P_mode) , P_corm_alpha=6, P_corm_thres=0x60 */
                    reg_37 = (11-state->mode) | ((5+state->mode) << 5);
                }
            } else {  // 13 seg
                reg_32 = ((11-state->mode) << 12) | (6 << 8) | 0x80; /* P_timf_alpha = 8 , P_corm_alpha=6, P_corm_thres=0x80 */
                reg_37 = ((5+state->mode) << 5) | (10-state->mode);
            }
        break;
    }

    dib8000_write_word(state, 32, reg_32);
    dib8000_write_word(state, 37, reg_37);

}

static void dib8000_small_fine_tune(struct dib8000_state *state, struct dibChannel *ch)
{
    uint16_t i;
    const int16_t *ncoeff;

    dib8000_write_word(state, 352, state->seg_diff_mask);
    dib8000_write_word(state, 353, state->seg_mask);

    // P_small_coef_ext_enable=ISDB-Tsb, P_small_narrow_band=ISDB-Tsb, P_small_last_seg=13, P_small_offset_num_car=5
    dib8000_write_word(state, 351, (ch->u.isdbt.sb_mode << 9) | (ch->u.isdbt.sb_mode << 8) | (13 << 4) | 5);

    if(ch->u.isdbt.sb_mode) {
        /* ---- SMALL ---- */
        switch(ch->u.isdbt.nfft) {
            case FFT_2K:
                if (ch->u.isdbt.partial_reception == 0) { // 1-seg
                    if (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) // DQPSK
                        ncoeff = coeff_2k_sb_1seg_dqpsk;
                    else // QPSK or QAM
                        ncoeff = coeff_2k_sb_1seg;
                } else { // 3-segments
                    if (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) { // DQPSK on central segment
                        if (ch->u.isdbt.layer[1].constellation == QAM_DQPSK) // DQPSK on external segments
                            ncoeff = coeff_2k_sb_3seg_0dqpsk_1dqpsk;
                        else // QPSK or QAM on external segments
                            ncoeff = coeff_2k_sb_3seg_0dqpsk;
                    } else { // QPSK or QAM on central segment
                        if (ch->u.isdbt.layer[1].constellation == QAM_DQPSK) // DQPSK on external segments
                            ncoeff = coeff_2k_sb_3seg_1dqpsk;
                        else // QPSK or QAM on external segments
                            ncoeff = coeff_2k_sb_3seg;
                    }
                }
                break;
            case FFT_4K:
                if (ch->u.isdbt.partial_reception == 0) { // 1-seg
                    if (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) // DQPSK
                        ncoeff = coeff_4k_sb_1seg_dqpsk;
                    else // QPSK or QAM
                        ncoeff = coeff_4k_sb_1seg;
                } else { // 3-segments
                    if (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) { // DQPSK on central segment
                        if (ch->u.isdbt.layer[1].constellation == QAM_DQPSK) // DQPSK on external segments
                            ncoeff = coeff_4k_sb_3seg_0dqpsk_1dqpsk;
                        else // QPSK or QAM on external segments
                            ncoeff = coeff_4k_sb_3seg_0dqpsk;
                    } else { // QPSK or QAM on central segment
                        if (ch->u.isdbt.layer[1].constellation == QAM_DQPSK) // DQPSK on external segments
                          ncoeff = coeff_4k_sb_3seg_1dqpsk;
                        else // QPSK or QAM on external segments
                          ncoeff = coeff_4k_sb_3seg;
                    }
                }
                break;
            case FFT_AUTO:
            case FFT_8K:
            default:
                if (ch->u.isdbt.partial_reception == 0) { // 1-seg
                    if (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) // DQPSK
                        ncoeff = coeff_8k_sb_1seg_dqpsk;
                    else // QPSK or QAM
                        ncoeff = coeff_8k_sb_1seg;
                } else { // 3-segments
                    if (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) { // DQPSK on central segment
                        if (ch->u.isdbt.layer[1].constellation == QAM_DQPSK) // DQPSK on external segments
                            ncoeff = coeff_8k_sb_3seg_0dqpsk_1dqpsk;
                        else // QPSK or QAM on external segments
                            ncoeff = coeff_8k_sb_3seg_0dqpsk;
                    } else { // QPSK or QAM on central segment
                        if (ch->u.isdbt.layer[1].constellation == QAM_DQPSK) // DQPSK on external segments
                            ncoeff = coeff_8k_sb_3seg_1dqpsk;
                        else // QPSK or QAM on external segments
                            ncoeff = coeff_8k_sb_3seg;
                    }
                }
                break;
        }

        for(i = 0 ; i < 8 ; i++)
            dib8000_write_word(state, 343 + i, ncoeff[i]);
    }

}

static void dib8000_set_sync_wait(struct dib8000_state *state, struct dibChannel *ch)
{
    uint16_t sync_wait = 64;

    /* P_dvsy_sync_wait - reuse mode */
    switch (ch->u.isdbt.nfft) {
        case FFT_8K: sync_wait = 256; break;
        case FFT_4K: sync_wait = 128; break;
        default:
        case FFT_2K: sync_wait =  64; break;
    }
    if (state->cfg.diversity_delay == 0)
        sync_wait = (sync_wait * (1 << (ch->u.isdbt.guard)) * 3) / 2 + 48; // add 50% SFN margin + compensate for one DVSY-fifo
    else
        sync_wait = (sync_wait * (1 << (ch->u.isdbt.guard)) * 3) / 2 + state->cfg.diversity_delay; // add 50% SFN margin + compensate for DVSY-fifo

    dib8000_write_word(state, 273, (dib8000_read_word(state, 273) & 0x000f) | (sync_wait << 4));
}

static uint16_t dib8000_set_layer(struct dib8000_state *state, struct dibChannel *ch, uint8_t layer_index, uint16_t max_constellation)
{
    uint8_t  cr, constellation, timeI;

    switch(ch->u.isdbt.layer[layer_index].constellation) {
        case QAM_DQPSK: constellation = 0; break;
        case  QAM_QPSK: constellation = 1; break;
        case QAM_16QAM: constellation = 2; break;
        case QAM_64QAM:
        default :       constellation = 3; break;
    }

    switch(ch->u.isdbt.layer[layer_index].code_rate) {
        case VIT_CODERATE_1_2: cr = 1; break;
        case VIT_CODERATE_2_3: cr = 2; break;
        case VIT_CODERATE_3_4: cr = 3; break;
        case VIT_CODERATE_5_6: cr = 5; break;
        case VIT_CODERATE_7_8:
        default :              cr = 7; break;
    }

    if ( (ch->u.isdbt.layer[layer_index].time_intlv > 0) && ((ch->u.isdbt.layer[layer_index].time_intlv <= 3) || (ch->u.isdbt.layer[layer_index].time_intlv == 4 && ch->u.isdbt.sb_mode == 1)))
        timeI = ch->u.isdbt.layer[layer_index].time_intlv;
    else
        timeI = 0;

    dib8000_write_word(state, 2+layer_index, (constellation << 10) | ((ch->u.isdbt.layer[layer_index].nb_segments & 0xf) << 6) | (cr << 3) | timeI );
    if (ch->u.isdbt.layer[layer_index].nb_segments > 0) {
        switch (max_constellation) {
            case QAM_DQPSK:
            case QAM_QPSK:
                if (ch->u.isdbt.layer[layer_index].constellation == QAM_16QAM || ch->u.isdbt.layer[layer_index].constellation == QAM_64QAM)
                    max_constellation = ch->u.isdbt.layer[layer_index].constellation;
                break;
            case QAM_16QAM:
                if (ch->u.isdbt.layer[layer_index].constellation == QAM_64QAM)
                    max_constellation = ch->u.isdbt.layer[layer_index].constellation;
                break;
        }
    }

    return  max_constellation;
}

static void dib8000_set_13seg_channel(struct dib8000_state *state, struct dibChannel *ch)
{	ch = ch;
    uint16_t i;
    uint16_t coff_pow = 0x2800;

    state->seg_mask = 0x1fff; /* All 13 segments enabled */

    /* ---- COFF ---- Carloff, the most robust --- */
    if (state->isdbt_cfg_loaded == 0) {  // if not Sound Broadcasting mode : put default values for 13 segments
        dib8000_write_word(state, 180, (16 << 6) | 9 );
        dib8000_write_word(state, 187, (4 << 12) | (8 << 5) | 0x2 );
        coff_pow = 0x2800;
        for (i=0;i<6;i++)
            dib8000_write_word(state, 181+i, coff_pow);

      /* P_ctrl_corm_thres4pre_freq_inh=1, P_ctrl_pre_freq_mode_sat=1 */
      /* P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 3, P_pre_freq_win_len=1 */
      dib8000_write_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (3 << 5) | 1);

      /* P_ctrl_pre_freq_win_len=8, P_ctrl_pre_freq_thres_lockin=6 */
      dib8000_write_word(state, 340, (8 << 6) | (6 << 0));
      /* P_ctrl_pre_freq_thres_lockout=4, P_small_use_tmcc/ac/cp=1 */
      dib8000_write_word(state, 341, (4 << 3) | (1 << 2) | (1 << 1) | (1 << 0));

      dib8000_write_word(state, 228, 0);  // default value
      dib8000_write_word(state, 265, 31); // default value
      dib8000_write_word(state, 205, 0x200f); // init value
    }

    /*
    * make the cpil_coff_lock more robust but slower p_coff_winlen
    * 6bits; p_coff_thres_lock 6bits (for coff lock if needed)
    */

    /* if ( ( nbseg_diff>0)&&(nbseg_diff<13))
       dib8000_write_word(state, 187, (dib8000_read_word(state, 187) & 0xfffb) | (1 << 3));*/

    if (state->cfg.pll->ifreq == 0)
        dib8000_write_word(state, 266, ~state->seg_mask | state->seg_diff_mask | 0x40); /* P_equal_noise_seg_inh */

    dib8000_load_ana_fe_coefs(state, ana_fe_coeff_13seg);
}

// SB MODE : P_coff_corthres_8k, 4k, 2k and P_coff_cpilthres_8k, 4k, 2k
static const uint16_t coff_thres_1seg[3] = {300,150, 80};
static const uint16_t coff_thres_3seg[3] = {350,300,250};
static void dib8000_set_sb_channel(struct dib8000_state *state, struct dibChannel *ch)
{
    const uint16_t * coff;
    uint16_t i;

    if (ch->u.isdbt.nfft == FFT_2K || ch->u.isdbt.nfft == FFT_4K) {
        dib8000_write_word(state, 219, dib8000_read_word(state, 219) | 0x1); /* adp_pass =1 */
        dib8000_write_word(state, 190, dib8000_read_word(state, 190) | (0x1 << 14)); /* pha3_force_pha_shift = 1 */
    } else {
        dib8000_write_word(state, 219, dib8000_read_word(state, 219) & 0xfffe); /* adp_pass =0 */
        dib8000_write_word(state, 190, dib8000_read_word(state, 190) & 0xbfff); /* pha3_force_pha_shift = 0 */
    }

    if (ch->u.isdbt.partial_reception == 1) // 3-segments
        state->seg_mask = 0x00E0;
    else // 1-segment
        state->seg_mask = 0x0040;

    dib8000_write_word(state, 268, (dib8000_read_word(state, 268) & 0xF9FF) | 0x0200);

    // ---- COFF ---- Carloff, the most robust --- */
    // P_coff_cpil_alpha=4, P_coff_inh=0, P_coff_cpil_winlen=64, P_coff_narrow_band=1, P_coff_square_val=1, P_coff_one_seg=~partial_rcpt, P_coff_use_tmcc=1, P_coff_use_ac=1
    dib8000_write_word(state, 187, (4<<12) | (0<<11) | (63<<5) | (0x3 << 3) |((~ch->u.isdbt.partial_reception & 1) << 2) | 0x3);

    /*  dib8000_write_word(state, 351, dib8000_read_word(state, 351) | 0x200); // P_small_coef_ext_enable = 1 */

      dib8000_write_word(state, 340, (16 << 6) | (8 << 0)); // P_ctrl_pre_freq_win_len=16, P_ctrl_pre_freq_thres_lockin=8
      dib8000_write_word(state, 341, ( 6 << 3) | (1 << 2) | (1 << 1) | (1 << 0));//P_ctrl_pre_freq_thres_lockout=6, P_small_use_tmcc/ac/cp=1

    /* Sound Broadcasting mode 1 seg */
    if (ch->u.isdbt.partial_reception == 0) {
        // P_coff_winlen=63, P_coff_thres_lock=15, P_coff_one_seg_width = (P_mode == 3) , P_coff_one_seg_sym = (P_mode-1)
        if (state->mode == 3)
            dib8000_write_word(state, 180, 0x1fcf | ((state->mode-1) << 14));
        else
            dib8000_write_word(state, 180, 0x0fcf | ((state->mode-1) << 14));

        //P_ctrl_corm_thres4pre_freq_inh=1,P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 5, P_pre_freq_win_len=4
        dib8000_write_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (5 << 5) | 4);
        coff = &coff_thres_1seg[0];
    } else {   /* Sound Broadcasting mode 3 seg */
      dib8000_write_word(state, 180, 0x1fcf | (1 << 14));
      // P_ctrl_corm_thres4pre_freq_inh = 1, P_ctrl_pre_freq_mode_sat=1, P_ctrl_pre_freq_inh=0, P_ctrl_pre_freq_step = 4, P_pre_freq_win_len=4
      dib8000_write_word(state, 338, (1 << 12) | (1 << 10) | (0 << 9) | (4 << 5) | 4);
      coff = &coff_thres_3seg[0];
    }

    dib8000_write_word(state, 228, 1); // P_2d_mode_byp=1
    dib8000_write_word(state, 205, dib8000_read_word(state, 205) & 0xfff0); // P_cspu_win_cut = 0

    if (ch->u.isdbt.partial_reception == 0 && ch->u.isdbt.nfft == FFT_2K) {
        //dib8000_write_word(state, 219, dib8000_read_word(state, 219) & 0xfffe); // P_adp_pass = 0
        dib8000_write_word(state, 265, 15); // P_equal_noise_sel = 15
    }

    /* Write COFF thres */
    for(i = 0 ; i < 3 ; i++) {
        dib8000_write_word(state, 181+i, coff[i]);
        dib8000_write_word(state, 184+i, coff[i]);
    }

    /*
    * make the cpil_coff_lock more robust but slower p_coff_winlen
    * 6bits; p_coff_thres_lock 6bits (for coff lock if needed)
    */
    /* if ( ( nbseg_diff>0)&&(nbseg_diff<13))
       dib8000_write_word(state, 187, (dib8000_read_word(state, 187) & 0xfffb) | (1 << 3));*/

    dib8000_write_word(state, 266,~state->seg_mask | state->seg_diff_mask); /* P_equal_noise_seg_inh */

    if (ch->u.isdbt.partial_reception == 0)
        dib8000_write_word(state, 178, 64); /* P_fft_powrange = 64 */
    else
        dib8000_write_word(state, 178, 32); /* P_fft_powrange = 32 */
}

static void dib8000_set_isdbt_common_channel(struct dib8000_state *state, struct dibChannel *ch, uint8_t seq, uint8_t autosearching)
{
    uint16_t P_cfr_left_edge  = 0, P_cfr_right_edge = 0;
    uint16_t tmcc_pow = 0, ana_gain = 0, tmp = 0, i = 0, nbseg_diff = 0 ;
    uint16_t max_constellation = QAM_DQPSK;
    int init_prbs;

    /* P_mode == ?? */
    dib8000_write_word(state, 10, (seq << 4));

    /* init mode */
    state->mode = fft_to_mode(state, ch);

    /* set guard */
    tmp = dib8000_read_word(state, 1);
    dib8000_write_word(state, 1, (tmp&0xfffc) | (ch->u.isdbt.guard & 0x3));

    //dbgpl(&dib8000_dbg, "state->mode = %d ; guard = %d", state->mode, ch->u.isdbt.guard);

    //dib8000_write_word(state, 5, 13); /* p_last_seg = 13 */
    dib8000_write_word(state, 274, (dib8000_read_word(state, 274) & 0xffcf) | ((ch->u.isdbt.partial_reception & 1) << 5) | ((ch->u.isdbt.sb_mode & 1) << 4));

    /* signal optimization parameter */
    if (ch->u.isdbt.partial_reception) {
        state->seg_diff_mask = (ch->u.isdbt.layer[0].constellation == QAM_DQPSK) << permu_seg[0];
        for (i = 1; i < 3; i++)
            nbseg_diff += (ch->u.isdbt.layer[i].constellation == QAM_DQPSK) * ch->u.isdbt.layer[i].nb_segments;
        for (i= 0; i < nbseg_diff; i++)
            state->seg_diff_mask |= 1 << permu_seg[i+1];
    } else {
        for (i = 0; i < 3; i++)
            nbseg_diff += (ch->u.isdbt.layer[i].constellation == QAM_DQPSK) * ch->u.isdbt.layer[i].nb_segments;
        for (i= 0 ; i < nbseg_diff; i++)
            state->seg_diff_mask |= 1 << permu_seg[i];
    }
    //dbgpl(&dib8000_dbg, "fe %d nbseg_diff = %X (%d)", state->fe->id, state->seg_diff_mask, state->seg_diff_mask);

/*
*    P_equal_speedmode          0             0     2     0     0     1     268   10    9
*    P_equal_ctrl_synchro       39            0     9     0     0     1     268   8     0
*/
    if (state->seg_diff_mask)
        dib8000_write_word(state, 268, (dib8000_read_word(state, 268) & 0xF9FF) | 0x0200);
    else
        dib8000_write_word(state, 268, (2 << 9) | 39); //init value

    for (i = 0 ; i < 3; i++)
        max_constellation = dib8000_set_layer(state, ch, i, max_constellation);
    if (autosearching == 0)
    {
        state->layer_b_nb_seg = ch->u.isdbt.layer[1].nb_segments;
        state->layer_c_nb_seg = ch->u.isdbt.layer[2].nb_segments;
    }

    /* WRITE: Mode & Diff mask */
    dib8000_write_word(state, 0, (state->mode << 13) | state->seg_diff_mask);

    state->differential_constellation = (state->seg_diff_mask != 0);

    /* channel estimation fine configuration */
    ana_gain = dib8000_adp_fine_tune(state, max_constellation);

    /* update ana_gain depending on max constellation */
    dib8000_update_ana_gain(state, ana_gain);

    // ---- ANA_FE ----
    if (ch->u.isdbt.partial_reception) /* 3-segments */
        dib8000_load_ana_fe_coefs(state, ana_fe_coeff_3seg);
    else
        dib8000_load_ana_fe_coefs(state, ana_fe_coeff_1seg); /* 1-segment */


    /* TSB or ISDBT ? apply it now */
    if (ch->u.isdbt.sb_mode) {
        dib8000_set_sb_channel(state, ch);
        if(ch->u.isdbt.sb_subchannel != -1)
            init_prbs = dib8000_get_init_prbs(ch->u.isdbt.sb_subchannel, ch);
        else
            init_prbs = 0;
    } else {
        dib8000_set_13seg_channel(state, ch);
        init_prbs = 0xfff;
    }

    /* SMALL */
    dib8000_small_fine_tune(state, ch);

    dib8000_set_subchannel_prbs(state, init_prbs);
    //dbgpl(&dib8000_dbg,"fe %d state->seg_mask = 0x%04x state->seg_diff_mask = 0x%04x",state->fe->id, state->seg_mask, state->seg_diff_mask);

    // ---- CHAN_BLK ----
    for (i=0 ; i < 13 ; i++) {
        if ( (((~state->seg_diff_mask) >> i) & 1) == 1 ) {
            P_cfr_left_edge  += (1<<i) * ((i==0 ) || ((((state->seg_mask & (~state->seg_diff_mask)) >> (i-1)) & 1) == 0));
            P_cfr_right_edge += (1<<i) * ((i==12) || ((((state->seg_mask & (~state->seg_diff_mask)) >> (i+1)) & 1) == 0));
        }
    }
    dib8000_write_word(state, 222, P_cfr_left_edge ); /* P_cfr_left_edge */
    dib8000_write_word(state, 223, P_cfr_right_edge); /* P_cfr_right_edge */
    /* "P_cspu_left_edge" & "P_cspu_right_edge" not used => do not care */

    dib8000_write_word(state, 189, ~state->seg_mask | state->seg_diff_mask); /* P_lmod4_seg_inh */
    dib8000_write_word(state, 192, ~state->seg_mask | state->seg_diff_mask); /* P_pha3_seg_inh */
    dib8000_write_word(state, 225, ~state->seg_mask | state->seg_diff_mask); /* P_tac_seg_inh */

    if (!autosearching)
        dib8000_write_word(state, 288, (~state->seg_mask | state->seg_diff_mask) & 0x1fff); /* P_tmcc_seg_eq_inh */
    else
        dib8000_write_word(state, 288, 0x1fff); //disable equalisation of the tmcc when autosearch to be able to find the DQPSK channels.
    //dbgpl(&dib8000_dbg, "287 = %X (%d)", ~state->seg_mask | 0x1000, ~state->seg_mask | 0x1000);

    dib8000_write_word(state, 211, state->seg_mask & (~state->seg_diff_mask) ); /* P_des_seg_enabled */
    dib8000_write_word(state, 287, ~state->seg_mask | 0x1000); /* P_tmcc_seg_inh */

    dib8000_write_word(state, 178, 32); /* P_fft_powrange = 32 */

    // ---- TMCC ----
    for (i=0; i<3; i++)
        tmcc_pow += ( ((ch->u.isdbt.layer[i].constellation == QAM_DQPSK) * 4 + 1)*ch->u.isdbt.layer[i].nb_segments) ;

    // Quantif of "P_tmcc_dec_thres_?k" is (0, 5+mode, 9);
    // Threshold is set at 1/4 of max power.
    tmcc_pow *= (1 << (9-2));
    dib8000_write_word(state, 290, tmcc_pow); /* P_tmcc_dec_thres_2k */
    dib8000_write_word(state, 291, tmcc_pow); /* P_tmcc_dec_thres_4k */
    dib8000_write_word(state, 292, tmcc_pow); /* P_tmcc_dec_thres_8k */
    //dib8000_write_word(state, 287, (1 << 13) | 0x1000 );

    // ---- PHA3 ----
    if (state->isdbt_cfg_loaded == 0)
      dib8000_write_word(state, 250, 3285); /* p_2d_hspeed_thr0 */

    state->isdbt_cfg_loaded=0;
}

//-- P_dual_adc_enctr     <= P_dual_adc_cfg0(11 downto 0) ; Default = (others => '0')
//-- P_dual_adc_enadciz   <= P_dual_adc_cfg0(12)          ; Default = '1'
//-- P_dual_adc_enadcqz   <= P_dual_adc_cfg0(13)          ; Default = '1'
//-- P_dual_adc_enclk2    <= P_dual_adc_cfg0(14)          ; Default = '0'
//-- P_dual_adc_envbgz    <= P_dual_adc_cfg0(15)          ; Default = '0'
//P_dual_adc_cfg0            12288         0     16    0     0     1     913   15    0

//-- P_dual_adc_endeci    <= P_dual_adc_cfg1(0)   ; Default = '0'
//-- P_dual_adc_enibiasz  <= P_dual_adc_cfg1(1)   ; Default = '1'
//-- P_dual_adc_enshz     <= P_dual_adc_cfg1(2)   ; Default = '1'
//-- P_dual_adc_envcmz    <= P_dual_adc_cfg1(3)   ; Default = '1'
//-- P_dual_adc_envrfz    <= P_dual_adc_cfg1(4)   ; Default = '1'
//P_dual_adc_cfg1            30            0     5     0     0     1     914   6     2

//DEFAULT MODE IS POWERDOWN and UNDER RESET
//-- P_sar_adc_enadc     : out std_logic;  Default = '0'
//-- P_sar_adc_reset     : out std_logic;  Default = '1'
//P_sar_adc_cfg              2             0     2     0     0     1     914   1     0

// for the ADC enable is 0 - disable is 1
int dib8000_set_adc_state(struct dib8000_state *state, enum dibx000_adc_states no)
{
	int ret = 0;
	uint16_t reg_907 = dib8000_read_word(state, 907),
	       reg_908 = dib8000_read_word(state, 908);

	switch (no) {
		case DIBX000_SLOW_ADC_ON:
			reg_908 |= (1 << 1) | (1 << 0);
			ret |= dib8000_write_word(state, 908, reg_908);
			reg_908 &= ~(1 << 1);
			break;

		case DIBX000_SLOW_ADC_OFF:
			reg_908 |=  (1 << 1) | (1 << 0);
			break;

		case DIBX000_ADC_ON:
			reg_907 &= 0x0fff;
			reg_908 &= 0x0003;
			break;

		case DIBX000_ADC_OFF: // leave the VBG voltage on
			reg_907 = (1 << 13) | (1 << 12);
			reg_908 = (1 << 6) | (1 << 5) | (1 << 4) | (1 << 3) | (1 << 1);
			break;

		case DIBX000_VBG_ENABLE:
			reg_907 &= ~(1 << 15);
			break;

		case DIBX000_VBG_DISABLE:
			reg_907 |= (1 << 15);
			break;

		default:
			break;
	}

	ret |= dib8000_write_word(state, 907, reg_907);
	ret |= dib8000_write_word(state, 908, reg_908);

	return ret;
}

static void dib8000_demod_restart(struct dib8000_state *state) {
    dib8000_write_word(state, 770, 0x4000);
    dib8000_write_word(state, 770, 0x0000);
    return;
}

static void dib8000_viterbi_state(struct dib8000_state *state, uint8_t onoff) {
    uint16_t tmp;

    tmp = dib8000_read_word(state, 771);
    if(onoff) /* start P_restart_chd : channel_decoder */
        dib8000_write_word(state, 771, tmp & 0xfffd);
    else /* stop P_restart_chd : channel_decoder */
        dib8000_write_word(state, 771, tmp | (1<<1));
}

/*
    8 times Symbol time in 100us unit including Guard interval rounded to upper integer in 8MHz bandwidth
    Array is order by fft : 2K, 8K, 4K
    2K : 252+62   = us  => 8*3.14  = 25.12 => 26
    8K : 1008+252 = us  => 8*12.6 = 100.8 => 101
    4K : 504+126  = us  => 8*6.3  = 63 => 63
*/
static uint16_t LUT_isdbt_symbol_duration[4] = {26,101,63};
uint32_t dib8000_get_symbol_duration(struct dibChannel *ch) {
    uint16_t i;

    if(ch->u.isdbt.nfft == FFT_AUTO)
        i = 1; /* the longest one */
    else
        i = (uint16_t)ch->u.isdbt.nfft;

    return (LUT_isdbt_symbol_duration[i] / (ch->bandwidth_kHz/1000)) + 1;
}

static uint32_t dib8000_get_timeout(struct dib8000_state *state, uint32_t delay, enum timeout_mode mode) {
    if(mode == SYMBOL_DEPENDENT_ON)
        return systime() + (delay * state->symbol_duration);
    else
        return systime() + delay;
}

static void dib8000_set_frequency_offset(struct dib8000_state *state, struct dibChannel *ch)
{
    int i;
    int total_dds_offset_khz = ch->RF_kHz - state->fe->current_rf;

    if (ch->u.isdbt.sb_mode) {
        state->subchannel = ch->u.isdbt.sb_subchannel;

        i = dib8000_read_word(state, 26) & 1; /* P_dds_invspec */
        dib8000_write_word(state, 26, ch->u.isdbt.spectrum_inversion^i);

        if (state->cfg.pll->ifreq == 0) { /* low if tuner */
            if ((ch->u.isdbt.spectrum_inversion^i) == 0)
                dib8000_write_word(state, 26, dib8000_read_word(state, 26) | 1);
        } else {
            if ((ch->u.isdbt.spectrum_inversion^i) == 0)
                total_dds_offset_khz *= -1;
        }
    }

    /* Auto compensate all tuner freq offsets (diversity offset and/or low-if offset )*/
    dbgp("FE %d : %dkhz tuner offset (ch->RF_kHz = %dKHz & state->fe->current_rf = %dKHz) total_dds_offset_khz = %d\n", state->fe->id, ch->RF_kHz - state->fe->current_rf, ch->RF_kHz, state->fe->current_rf, total_dds_offset_khz);

    /* apply dds offset now */
    dib8000_set_dds(state, total_dds_offset_khz);
}

int dib8000_tune(struct dibFrontend *fe, struct dibChannel *ch)
{
    struct dib8000_state *state = fe->demod_priv;
    enum frontend_tune_state *tune_state = &fe->tune_state;
    struct dibChannelMonitor *mon = channel_frontend_monitoring(ch, state->fe->id);

    uint16_t locks, strength, deeper_interleaver = 0, i;
    struct dibChannelContext *context = &ch->context;
    int ret = 1; /* 1 symbol duration (in 100us unit) delay most of the time */
	strength = 0;
    uint32_t *timeout = &state->timeout;
    uint32_t now = systime();

#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
    uint32_t corm[4] = {0,0,0,0};
    uint8_t find_index, max_value;
#endif

#ifdef DEBUG_DIB8000_TUNE
    if (*tune_state < CT_DEMOD_STOP)
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
        dbgp("FE %d IN: context status = %d, TUNE_STATE %d autosearch step = %u systime = %u\n",fe->id, fe->status, *tune_state, state->autosearch_state, now);
#else
        dbgp("FE %d IN: context status = %d, TUNE_STATE %d systime = %u\n",fe->id, fe->status, *tune_state, now);
#endif
#endif

    locks = dib8000_read_word(state, 568);

    /* locks debug for test async */
    mon->locks = locks;

    switch (*tune_state) {
        case CT_DEMOD_START: /* 30 */
            dib8000_viterbi_state(state, 0); /* force chan dec in restart */

            /* Layer monit */
            if (state->ber_monitored_layer != LAYER_ALL)
                dib8000_write_word(state, 285, (dib8000_read_word(state, 285) & 0x60)|state->ber_monitored_layer);
            else
                dib8000_write_word(state, 285, dib8000_read_word(state, 285) & 0x60);

            dib8000_set_frequency_offset(state, ch);
            dib8000_set_bandwidth(state, ch->bandwidth_kHz);

            if (context->status == CHANNEL_STATUS_PARAMETERS_UNKNOWN) /* The channel struct is unknown, search it ! */
            {
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
                state->autosearch_state = AS_SEARCHING_FFT;
                state->found_nfft = FFT_AUTO;
                state->found_guard = GUARD_INTERVAL_AUTO;
#endif
                *tune_state = CT_DEMOD_SEARCH_NEXT;
            }
            else if (context->status == CHANNEL_STATUS_PARAMETERS_SET) { /* we already know the channel struct so TUNE only ! */
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
                state->autosearch_state = AS_DONE;
#endif
                *tune_state = CT_DEMOD_STEP_3;
            }
            state->symbol_duration = dib8000_get_symbol_duration(ch);
            break;

        case CT_DEMOD_SEARCH_NEXT: /* 51 */
                dib8000_autosearch_start(fe, ch);
                ret = 15;
                *tune_state = CT_DEMOD_STEP_1;
            break;

        case CT_DEMOD_STEP_1: /* 31 */
            switch (dib8000_autosearch_is_irq(fe)) {
                case 1: /* fail */
                    fe->status = FE_STATUS_TUNE_FAILED;
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
                    state->autosearch_state = AS_DONE;
#endif
                    *tune_state = CT_DEMOD_STOP; /* else we are done here */
                    break;
                case 2: /* Succes */
                    fe->status = FE_STATUS_FFT_SUCCESS; /* signal to the upper layer, that there was a channel found and the parameters can be read */
                    *tune_state = CT_DEMOD_STEP_3;
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
                    if (state->autosearch_state == AS_SEARCHING_GUARD) {
                        *tune_state = CT_DEMOD_STEP_2;
                    }
                    else
                        state->autosearch_state = AS_DONE;
#endif
                    break;
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
                case 3: /* Autosearch FFT max correlation endded */
                    *tune_state = CT_DEMOD_STEP_2;
                    break;
#endif
            }
            break;

        case CT_DEMOD_STEP_2:
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
            switch (state->autosearch_state) {
                case AS_SEARCHING_FFT:
                    /* searching for the correct FFT */
                    corm[2] = (dib8000_read_word(state, 594) << 16) | (dib8000_read_word(state, 595));
                    corm[1] = (dib8000_read_word(state, 596) << 16) | (dib8000_read_word(state, 597));
                    corm[0] = (dib8000_read_word(state, 598) << 16) | (dib8000_read_word(state, 599));
#ifdef DEBUG_DIB8000_TUNE
                    dbgp("FE %d corm fft: %u %u %u\n", fe->id, corm[0], corm[1], corm[2]);
#endif
                    max_value = 0;
                    for (find_index = 1 ; find_index < 3 ; find_index++) {
                        if (corm[max_value] < corm[find_index])
                            max_value = find_index ;
                    }

                    switch(max_value) {
                        case 0:     state->found_nfft = FFT_2K; break;
                        case 1:     state->found_nfft = FFT_4K; break;
                        case 2:
                        default:    state->found_nfft = FFT_8K; break;
                    }
#ifdef DEBUG_DIB8000_TUNE
                    dbgp("FE %d Autosearch FFT has found Mode %d\n", fe->id, max_value+1);
#endif
                    *tune_state = CT_DEMOD_SEARCH_NEXT;
                    state->autosearch_state = AS_SEARCHING_GUARD;
                    ret = 10;
                    break;
                case AS_SEARCHING_GUARD:
                    /* searching for the correct guard interval */
                    state->found_guard = dib8000_read_word(state, 570) & 0x3;
#ifdef DEBUG_DIB8000_TUNE
                    dbgp("FE %d guard interval found=%i\n", fe->id, state->found_guard);
#endif
                    *tune_state = CT_DEMOD_STEP_3;
                    break;
                default:
                    /* the demod should never be in this state */
                    fe->status = FE_STATUS_TUNE_FAILED;
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
                    state->autosearch_state = AS_DONE;
#endif
                    *tune_state = CT_DEMOD_STOP; /* else we are done here */
                    break;
            }
#else
            *tune_state = CT_DEMOD_STEP_3;
#endif
             break;

        case CT_DEMOD_STEP_3: /* 33 */
            dib8000_set_isdbt_loop_params(state, ch, LOOP_TUNE_1);
            dib8000_set_isdbt_common_channel(state, ch, 0, 0);/* setting the known channel parameters here */
            *tune_state = CT_DEMOD_STEP_4;
            break;

        case CT_DEMOD_STEP_4: /* (34) */
            /** do not restart demod already locked **/
            if (fe->status > FE_STATUS_FFT_SUCCESS)
                dib8000_demod_restart(state);

            dib8000_set_sync_wait(state, ch);
            dib8000_set_diversity_in(state->fe, state->diversity_onoff);

            locks = (dib8000_read_word(state, 180) >> 6) &0x3f; /* P_coff_winlen ? */
            /* coff should lock over P_coff_winlen ofdm symbols : give 3 times this lenght to lock */
            *timeout = dib8000_get_timeout(state, (2 * locks), SYMBOL_DEPENDENT_ON);
            *tune_state = CT_DEMOD_STEP_5;
            break;

        case CT_DEMOD_STEP_5: /* (35) */
            if (locks & (0x3 << 11) ) { /* coff-lock and off_cpil_lock achieved */
                dib8000_update_timf(state); /* we achieved a coff_cpil_lock - it's time to update the timf */
                if(!state->differential_constellation) {
                    /* 2 times lmod4_win_len + 10 symbols (pipe delay after coff + nb to compute a 1st correlation) */
                    *timeout = dib8000_get_timeout(state, (20 * ((dib8000_read_word(state, 188)>>5)&0x1f)), SYMBOL_DEPENDENT_ON);
                    *tune_state = CT_DEMOD_STEP_7;
                    } else {
                        *tune_state = CT_DEMOD_STEP_8;
                    }
            } else if (now > *timeout) {
                *tune_state = CT_DEMOD_STEP_6; /* goto check for diversity input connection */
            }
            break;

        case CT_DEMOD_STEP_6: /* (36)  if there is an input (diversity) */
            if(fe->input != NULL && state->output_mode != OUTPUT_MODE_DIVERSITY) {
                dbgp("FE %d outup_mode = %d\n", fe->id, state->output_mode);

                /* if there is a diversity fe in input and this fe is has not already failled : wait here until this this fe has succedeed or failled */
                //dbgpl(&dib8000_dbg,"FE %d tune state = %d", fe->input->id, fe->input->status);
                if ( fe->input->status <= FE_STATUS_STD_SUCCESS) /* Something is locked on the input fe */
                    *tune_state = CT_DEMOD_STEP_8; /* go for mpeg */
                else if (fe->input->status >= FE_STATUS_TUNE_TIME_TOO_SHORT ) { /* fe in input failled also, break the current one */
                      dbgp("FE %d tune state = %d\n", fe->input->id, fe->input->status);
                    *tune_state = CT_DEMOD_STOP; /* else we are done here ; step 8 will close the loops and exit */
                    dib8000_viterbi_state(state, 1); /* start viterbi chandec */
                    dib8000_set_isdbt_loop_params(state, ch, LOOP_TUNE_2);
                    fe->status = FE_STATUS_TUNE_FAILED;
                }
            } else {
                dib8000_viterbi_state(state, 1); /* start viterbi chandec */
                dib8000_set_isdbt_loop_params(state, ch, LOOP_TUNE_2);
                *tune_state = CT_DEMOD_STOP; /* else we are done here ; step 8 will close the loops and exit */
                fe->status = FE_STATUS_TUNE_FAILED;
            }
        break;

        case CT_DEMOD_STEP_7: /* 37 */
            if(locks & (1<<10)) { /* lmod4_lock */
                ret = 14; /* wait for 14 symbols */
                *tune_state = CT_DEMOD_STEP_8;
            }  else if(now > *timeout)
                *tune_state = CT_DEMOD_STEP_6; /* goto check for diversity input connection */
            break;

        case CT_DEMOD_STEP_8: /* 38 */
            dib8000_viterbi_state(state, 1); /* start viterbi chandec */
            dib8000_set_isdbt_loop_params(state, ch, LOOP_TUNE_2);

            /* now that tune is finished, lock0 should lock on fec_mpeg to output this lock on MP_LOCK. It's changed in autosearch start */
            //dib8000_write_word(state, 6, 0x200);

            /* mpeg will never lock on this condition because init_prbs is not set : search for it !*/
            if (ch->u.isdbt.sb_mode && ch->u.isdbt.sb_subchannel == -1 && !state->differential_constellation) {
                state->subchannel = 0;
                *tune_state = CT_DEMOD_STEP_11;
            } else {
                *tune_state = CT_DEMOD_STEP_9;
                fe->status = FE_STATUS_LOCKED;
            }
            break;

        case CT_DEMOD_STEP_9: /* 39 */
                if((dib8000_read_word(state, 1291)>>9)&0x1) { /* fe capable of deinterleaving : esram */
                    /* defines timeout for mpeg lock depending on interleaver lenght of longest layer */
                    for (i = 0; i < 3; i++) {
                        if(ch->u.isdbt.layer[i].time_intlv >= deeper_interleaver) {
                            dbgp("FE %d ch->u.isdbt.layer[%d].time_intlv = %d \n",state->fe->id, i, ch->u.isdbt.layer[i].time_intlv);
                            if(ch->u.isdbt.layer[i].nb_segments > 0) { /* valid layer */
                                deeper_interleaver = ch->u.isdbt.layer[i].time_intlv;
                                state->longest_intlv_layer = i;
                            }
                        }
                    }

                    if(deeper_interleaver == 0)
                        locks = 2; /* locks is the tmp local variable name */
                    else if (deeper_interleaver == 3)
                        locks = 8;
                    else
                        locks = 2 * deeper_interleaver;

                    if(fe->input != NULL) /* because of diversity sync */
                        locks*=2;


                    *timeout = now + (2000 * locks); /* give the mpeg lock 800ms if sram is present */
                    dbgp("FE %d Deeper interleaver mode = %d on layer %d : timeout mult factor = %d => will use timeout = %d\n",state->fe->id, deeper_interleaver, state->longest_intlv_layer, locks, *timeout);

                    *tune_state = CT_DEMOD_STEP_10;
                } else {
                    *tune_state = CT_DEMOD_STOP;
                }
            break;

        case CT_DEMOD_STEP_10: /* 40 */
            if (locks&(1<<(7-state->longest_intlv_layer))) { /* mpeg lock : check the longest one */
                dbgp("FE %d Mpeg locks [ L0 : %d | L1 : %d | L2 : %d ]\n",state->fe->id, (locks>>7)&0x1, (locks>>6)&0x1, (locks>>5)&0x1);
                if (ch->u.isdbt.sb_mode && ch->u.isdbt.sb_subchannel == -1 && !state->differential_constellation)
                    /* signal to the upper layer, that there was a channel found and the parameters can be read */
                    fe->status = FE_STATUS_DEMOD_SUCCESS;
                else
                    fe->status = fe->status = FE_STATUS_DATA_LOCKED;
                *tune_state = CT_DEMOD_STOP;
            } else if (now > *timeout) {
                if (ch->u.isdbt.sb_mode && ch->u.isdbt.sb_subchannel == -1 && !state->differential_constellation) { /* continue to try init prbs autosearch */
                    state->subchannel += 3;
                    *tune_state = CT_DEMOD_STEP_11;
                } else { /* we are done mpeg is not locking */
                    *tune_state = CT_DEMOD_STOP;
                    fe->status = FE_STATUS_TUNE_FAILED;
                }
            }
            break;

        case CT_DEMOD_STEP_11:  /* 41 : init prbs autosearch */
            if(state->subchannel <= 41) {
                dib8000_set_subchannel_prbs(state, dib8000_get_init_prbs(state->subchannel, ch));
                *tune_state = CT_DEMOD_STEP_9;
            } else {
                *tune_state = CT_DEMOD_STOP;
                fe->status = FE_STATUS_TUNE_FAILED;
            }
            break;

        default:
            break;
    }

    /* tuning is finished - cleanup the demod */
    switch (*tune_state) {
    case CT_DEMOD_STOP: /* (42) */
        //dib19000_write_word(state, 2120, 0x004); /* now we can enable the 2d estimation (1<<11) */
        //dib19000_write_word(state, 2115, 7782); /* close adp fil*/
        //dib19000_write_word(state, 2116, 0); /* enable adp */
        //
        ///* reset PE-counter */
        //data_bus_client_read_multi16(demod_get_data_bus_client(state->fe), 2068, buf, 2); // get pe into buf[0] and buf[1]
        //dib19000_write_word(state, 2068, 0);
        //dib19000_write_word(state, 2069, 1);
        //dib19000_write_word(state, 2068, buf[0]);
        //dib19000_write_word(state, 2069, buf[1]);
        ret = FE_CALLBACK_TIME_NEVER;
        frontend_set_steady_timestamp(fe,now+700);
        break;
    default:
        break;
    }

    return ret * state->symbol_duration;
}

int dib8000_post_tune_adaptation(struct dibFrontend *fe)
{
    struct dib8000_state *state = NULL;

    if (fe == NULL)
        return DIB_RETURN_ERROR;

    state = fe->demod_priv;
    return dib8000_agc_soft_split(state);
}

uint16_t dib8000_get_current_agc_global(struct dibFrontend *demod)
{
    struct dib8000_state *state = demod->demod_priv;
    /*LB : 903->774*/
    uint16_t cfg_774 = dib8000_read_word(state, 774);
    uint16_t agc;

    /* activate AGC and IQC */
    dib8000_write_word(state, 774, (cfg_774 & 0xf6ff)); /*LB : AGC from bit 10 -> 9*/
    //dib8000_restart_agc(state);

    DibMSleep(15);

    agc = dib8000_read_word(state, 390); /*LB : agc global doesn't move*/

    /* restore the previous state */
    dib8000_write_word(state, 774, cfg_774);

    return agc;
}

void dib8000_get_agc_values(struct dibFrontend *demod, uint16_t *agc_global, uint16_t *wbd)
{
    struct dib8000_state *state = demod->demod_priv;

    if (agc_global != NULL)
        *agc_global = dib8000_read_word(state, 390); /* AGC_global and AGC wdb don't move */
    if (wbd != NULL)
        *wbd = dib8000_read_word(state, 393);
}

void dib8000_autosearch_start(struct dibFrontend *fe, struct dibChannel *ch)
{
    uint8_t factor;
    uint32_t value;

    struct dib8000_state *state = fe->demod_priv;
    int slist = 0;
    struct dibChannel schan;

#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
    if ((state->revision >= 0x8002) && (state->autosearch_state == AS_SEARCHING_FFT)) {
        factor = 10;
        value = factor * state->cfg.pll->internal;

        dib8000_write_word(state,  37, 0x0065); //P_ctrl_pha_off_max default values
        dib8000_write_word(state, 116, 0x0000); // P_ana_gain to 0

        dib8000_write_word(state, 0, (dib8000_read_word(state, 0)&0x1fff) | (0<<13) | (1<<15)); // P_mode = 0, P_restart_search=1
        dib8000_write_word(state, 1, (dib8000_read_word(state, 1)&0xfffc) | 0); // P_guard = 0
        dib8000_write_word(state, 6, 0); // P_lock0_mask = 0
        dib8000_write_word(state, 7, 0); // P_lock1_mask = 0
        dib8000_write_word(state, 8, 0); // P_lock2_mask = 0
        dib8000_write_word(state, 10, (dib8000_read_word(state, 10)&0x200) | (16<<4) | (0<<0)); // P_search_list=16, P_search_maxtrial=0
        dib8000_write_word(state, 11, (value>>16)&0xffff); // P_search_end0
        dib8000_write_word(state, 12, value&0xffff);
        dib8000_write_word(state, 13, (value>>16)&0xffff); // P_search_end1
        dib8000_write_word(state, 14, value&0xffff);
        dib8000_write_word(state, 15, (value>>16)&0xffff); // P_search_end2
        dib8000_write_word(state, 16, value&0xffff);
        dib8000_write_word(state, 17, 0);
        dib8000_write_word(state, 18, 200); // P_search_rstst = 200
        dib8000_write_word(state, 19, 0);
        dib8000_write_word(state, 20, 400); // P_search_rstend = 400
        dib8000_write_word(state, 21, (value>>16)&0xffff); // P_search_checkst
        dib8000_write_word(state, 22, value&0xffff);
        dib8000_write_word(state, 32, (dib8000_read_word(state, 32)&0xf0ff) | (0<<8)); // P_corm_alpha = 0
        dib8000_write_word(state, 355, 2); // P_search_param_max = 2

        /* P_search_param_select = (1 | 1<<4 | 1 << 8) */
        dib8000_write_word(state, 356, 0);
        dib8000_write_word(state, 357, 0x111);

        dib8000_write_word(state, 770, (dib8000_read_word(state, 770)&0xdfff) | (1<<13)); // P_restart_ccg = 1
        dib8000_write_word(state, 770, (dib8000_read_word(state, 770)&0xdfff) | (0<<13)); // P_restart_ccg = 0
        dib8000_write_word(state, 0, (dib8000_read_word(state, 0)&0x7ff) | (0<<15) | (1<<13)); // P_restart_search = 0;
    } else if ((state->revision >= 0x8002) && (state->autosearch_state == AS_SEARCHING_GUARD)) {
        INIT_CHANNEL(&schan, STANDARD_ISDBT);
        schan = *ch;

        schan.u.isdbt.nfft                   = FFT_8K;
        schan.u.isdbt.guard                  = GUARD_INTERVAL_1_8;
        schan.u.isdbt.layer[0].constellation = QAM_64QAM;
        schan.u.isdbt.layer[0].code_rate     = VIT_CODERATE_2_3;
        schan.u.isdbt.layer[0].time_intlv    = 0;
        schan.u.isdbt.spectrum_inversion     = 0;
        schan.u.isdbt.layer[0].nb_segments   = 13;

        slist = 16;
        schan.u.isdbt.nfft = state->found_nfft;

        dib8000_set_isdbt_common_channel(state, &schan, (unsigned char)slist, 1);

        //set lock_mask values
        dib8000_write_word(state, 6, 0x4);
        dib8000_write_word(state, 7, 0x8);
        dib8000_write_word(state, 8, 0x1000);

        //set lock_mask wait time values
        factor = 1;
        value = factor * 50 * state->cfg.pll->internal * factor;
        dib8000_write_word(state, 11, (uint16_t) ((value >> 16) & 0xffff)); // lock0 wait time
        dib8000_write_word(state, 12, (uint16_t)  (value        & 0xffff)); // lock0 wait time
        value = factor * 100 * state->cfg.pll->internal * factor;
        dib8000_write_word(state, 13, (uint16_t) ((value >> 16) & 0xffff)); // lock1 wait time
        dib8000_write_word(state, 14, (uint16_t)  (value        & 0xffff)); // lock1 wait time
        value = factor * 1000 * state->cfg.pll->internal * factor;
        dib8000_write_word(state, 15, (uint16_t) ((value >> 16) & 0xffff)); // lock2 wait time
        dib8000_write_word(state, 16, (uint16_t)  (value        & 0xffff)); // lock2 wait time

        dib8000_write_word(state, 355, 3); /* P_search_param_max = 3 */

        /* P_search_param_select = 0xf; look for the 4 different guard intervals */
        dib8000_write_word(state, 356, 0);
        dib8000_write_word(state, 357, 0xf);

        value = dib8000_read_word(state, 0);
        dib8000_write_word(state, 0, (uint16_t) ((1 << 15) | value));
        dib8000_read_word(state, 1284);  /* reset the INT. n_irq_pending */
        dib8000_write_word(state, 0, (uint16_t) value);
    }
    else
#endif
    {
        INIT_CHANNEL(&schan, STANDARD_ISDBT);
        schan = *ch;

        schan.u.isdbt.nfft                   = FFT_8K;
        schan.u.isdbt.guard                  = GUARD_INTERVAL_1_8;
        schan.u.isdbt.layer[0].constellation = QAM_64QAM;
        schan.u.isdbt.layer[0].code_rate     = VIT_CODERATE_2_3;
        schan.u.isdbt.layer[0].time_intlv    = 0;

        schan.u.isdbt.spectrum_inversion     = 0;

        if (!schan.u.isdbt.sb_mode)
            schan.u.isdbt.layer[0].nb_segments   = 13;

        //choose the right list, in sb, always do everything
        if (schan.u.isdbt.sb_mode) {
            slist = 7;
            dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));
        } else {
            if (ch->u.isdbt.guard == GUARD_INTERVAL_AUTO) {
                if (ch->u.isdbt.nfft == FFT_AUTO) {
                    slist = 7;
                    dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));  // P_mode = 1 to have autosearch start ok with mode2
                } else {
                    slist = 3;
                    schan.u.isdbt.nfft = ch->u.isdbt.nfft;
                }
            } else {
                if (ch->u.isdbt.nfft == FFT_AUTO) {
                    slist = 2;
                    schan.u.isdbt.guard = ch->u.isdbt.guard;
                    dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));  // P_mode = 1
                } else {
                    slist = 0;
                    schan.u.isdbt.nfft = ch->u.isdbt.nfft;
                    schan.u.isdbt.guard = ch->u.isdbt.guard;
                }
            }
        }
        dbgp("FE %d Using list for autosearch : %d\n", fe->id, slist);

        dib8000_set_isdbt_common_channel(state, &schan, (unsigned char)slist, 1);
        //dib8000_write_word(state, 0, (dib8000_read_word(state, 0) & 0x9fff) | (1 << 13));  // P_mode = 1

        factor = 1;

        //set lock_mask values
        dib8000_write_word(state, 6, 0x4);
        dib8000_write_word(state, 7, 0x8);
        dib8000_write_word(state, 8, 0x1000);

        //set lock_mask wait time values
        value = 50 * state->cfg.pll->internal * factor;
        dib8000_write_word(state, 11, (uint16_t) ((value >> 16) & 0xffff)); // lock0 wait time
        dib8000_write_word(state, 12, (uint16_t)  (value        & 0xffff)); // lock0 wait time
        value = 100 * state->cfg.pll->internal * factor;
        dib8000_write_word(state, 13, (uint16_t) ((value >> 16) & 0xffff)); // lock1 wait time
        dib8000_write_word(state, 14, (uint16_t)  (value        & 0xffff)); // lock1 wait time
        value = 1000 * state->cfg.pll->internal * factor;
        dib8000_write_word(state, 15, (uint16_t) ((value >> 16) & 0xffff)); // lock2 wait time
        dib8000_write_word(state, 16, (uint16_t)  (value        & 0xffff)); // lock2 wait time

        value = dib8000_read_word(state, 0);
        dib8000_write_word(state, 0, (uint16_t) ((1 << 15) | value));
        dib8000_read_word(state, 1284);  // reset the INT. n_irq_pending
        dib8000_write_word(state, 0, (uint16_t) value);
    }
}

static int dib8000_autosearch_irq(struct dibFrontend *fe)
{
#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
    struct dib8000_state *state = fe->demod_priv;
#endif
    uint8_t b[2];
    if (data_bus_client_read(demod_get_data_bus_client(fe), 1284, b, 2) != DIB_RETURN_SUCCESS)
        return 1;

#ifdef CONFIG_DIB8000_NEW_AUTOSEARCH
    if ((state->revision >= 0x8002) && (state->autosearch_state == AS_SEARCHING_FFT)) {
        if (b[1] & 0x1) {
            dbgp("FE %d SEARCHING FFT : max correlation result available\n", fe->id);
            return 3;
        }
    }
    else
#endif
    {
        if (b[1] & 0x1) { // failed
            dbgp("FE %d Autosearch IRQ: failed\n", fe->id);
            return 1;
        }

        if (b[1] & 0x2) { // succeeded
            dbgp("FE %d Autosearch IRQ: success\n", fe->id);
            return 2;
        }
    }

    return 0; // still pending
}

/* autosearch workarounded for DIB8000*/
int dib8000_autosearch_is_irq(struct dibFrontend *fe)
{
    int ret = 0; /* pending is default */
    ret = dib8000_autosearch_irq(fe);
    return ret;
}

