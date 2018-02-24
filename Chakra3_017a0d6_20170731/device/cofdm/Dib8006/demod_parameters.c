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
#include "demod_parameters.h"
/* XC5000 */
const struct dibx000_agc_config xc5000_agc_config = {
	BAND_VHF | BAND_UHF,       // band_caps

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=0, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712,  // inv_gain
	21,  // time_stabiliz

	0,  // alpha_level
	118,  // thlock

	0,     // wbd_inv
	2867,  // wbd_ref
	0,  // wbd_sel
	2,  // wbd_alpha

	0,  // agc1_max
	0,  // agc1_min
	39718,  // agc2_max
	9930,  // agc2_min
	0,  // agc1_pt1
	0,  // agc1_pt2
	0,  // agc1_pt3
	0,  // agc1_slope1
	0,  // agc1_slope2
	0,  // agc2_pt1
	128,  // agc2_pt2
	29,  // agc2_slope1
	29,  // agc2_slope2

	17,  // alpha_mant
	27,  // alpha_exp
	23,  // beta_mant
	51,  // beta_exp

	1,  // perform_agc_softsplit
	{
	0,
	0,
	0,
	0,
	}
};

/* XC4000 */
const struct dibx000_agc_config xc4000_agc_config = {
	BAND_VHF | BAND_UHF,       // band_caps

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=0, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712,  // inv_gain
	21,  // time_stabiliz

	0,  // alpha_level
	118,  // thlock

	0,     // wbd_inv
	2867,  // wbd_ref
	0,  // wbd_sel
	2,  // wbd_alpha

	0,  // agc1_max
	0,  // agc1_min
	39718,  // agc2_max
	9930,  // agc2_min
	0,  // agc1_pt1
	0,  // agc1_pt2
	0,  // agc1_pt3
	0,  // agc1_slope1
	0,  // agc1_slope2
	0,  // agc2_pt1
	128,  // agc2_pt2
	29,  // agc2_slope1
	29,  // agc2_slope2

	17,  // alpha_mant
	27,  // alpha_exp
	23,  // beta_mant
	51,  // beta_exp

	1,  // perform_agc_softsplit
	{
	0,
	0,
	0,
	0,
	}
};


/* XC3028 */
const struct dibx000_agc_config xc3028_agc_config = {
	BAND_VHF | BAND_UHF,       // band_caps

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=0, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712,  // inv_gain
	21,  // time_stabiliz

	0,  // alpha_level
	118,  // thlock

	0,     // wbd_inv
	2867,  // wbd_ref
	0,  // wbd_sel
	2,  // wbd_alpha

	0,  // agc1_max
	0,  // agc1_min
	39718,  // agc2_max
	9930,  // agc2_min
	0,  // agc1_pt1
	0,  // agc1_pt2
	0,  // agc1_pt3
	0,  // agc1_slope1
	0,  // agc1_slope2
	0,  // agc2_pt1
	128,  // agc2_pt2
	29,  // agc2_slope1
	29,  // agc2_slope2

	17,  // alpha_mant
	27,  // alpha_exp
	23,  // beta_mant
	51,  // beta_exp

	1,  // perform_agc_softsplit
	{
	0,
	0,
	0,
	0,
	}
};

const struct dibx000_bandwidth_config xc5000_bw_config = {
	60000, 30000, // internal, sampling
	1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(1 << 25) | 5816102, // ifreq = 5.200000 MHz
	18179756, // timf
	30000000, // xtal_hz
	0,
	0
};


// for DVB-T demod
const struct dibx000_bandwidth_config xc4000_bw_config_12mhz = {
	60000, 30000, // internal, sampling
	1, 20, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
	(1 << 25) | 5816102, // ifreq = 5.200000 MHz
	20452225, // timf
	0,
	0,
	0
};

// for DiB8000 only
/*const struct dibx000_bandwidth_config xc4000_bw_config_12mhz_ISDBT = {
	60000, 30000, // internal, sampling
	1, 20, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
	(1 << 25) | 5816102, // ifreq = 5.200000 MHz
	18179755, // timf
	12000000, // gpio3_clk
};*/
const struct dibx000_bandwidth_config xc4000_bw_config_12mhz_ISDBT = {
	50625, 25312, // internal, sampling
	2, 15, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (621 << 0), // sad_cfg: refsel, sel, freq_15k
	(1 << 25) | 8782148, // ifreq = 44.000000 MHz
	21546377, // timf
	27000000, // xtal
	0,
	0
};




/* PLL Configuration for COFDM BW_MHz = 8.000000 With external clock = 30.000000 */
const struct dibx000_bandwidth_config xc3028_bw_config = {
	60000, 30000, // internal, sampling
	1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
	(1 << 25) | 5816102, // ifreq = 5.200000 MHz
	20452225, // timf
	30000000, // xtal_hz
	0,
	0
};

const struct dibx000_bandwidth_config xc3028_bw_config_12mhz = {
	60000, 30000, // internal, sampling
	1, 20, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
	(1 << 25) | 5816102, // ifreq = 5.200000 MHz
	20452225, // timf
	0,
	0,
	0
};

/* MT226x */
const struct dibx000_agc_config mt226x_agc_config[2] = {
	{
		BAND_UHF, // band_caps

		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=1, P_agc_inv_pwm1=1, P_agc_inv_pwm2=1,
		* P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (1 << 10) | (1 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (5 << 1) | (0 << 0), // setup

		1130,  // inv_gain
		21,  // time_stabiliz

		0,  // alpha_level
		118,  // thlock

		0,     // wbd_inv
		3530,  // wbd_ref
		1,     // wbd_sel
		0,     // wbd_alpha

		65535,  // agc1_max
		33770,  // agc1_min
		65535,  // agc2_max
		23592,  // agc2_min

		0,    // agc1_pt1
		62,   // agc1_pt2
		255,  // agc1_pt3
		64,   // agc1_slope1
		64,   // agc1_slope2
		132,  // agc2_pt1
		192,  // agc2_pt2
		80,   // agc2_slope1
		80,   // agc2_slope2

		17,  // alpha_mant
		27,  // alpha_exp
		23,  // beta_mant
		51,  // beta_exp

		1,  // perform_agc_softsplit
	{
	0,
	0,
	0,
	0,
	}
		
	}, {
		BAND_VHF | BAND_LBAND, // band_caps

		/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=1, P_agc_inv_pwm1=1, P_agc_inv_pwm2=1,
		* P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
		(0 << 15) | (0 << 14) | (1 << 11) | (1 << 10) | (1 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

		2372, // inv_gain
		21,   // time_stabiliz

		0,    // alpha_level
		118,  // thlock

		0,    // wbd_inv
		3530, // wbd_ref
		1,     // wbd_sel
		0,    // wbd_alpha

		65535, // agc1_max
		0,     // agc1_min
		65535, // agc2_max
		23592, // agc2_min

		0,    // agc1_pt1
		128,  // agc1_pt2
		128,  // agc1_pt3
		128,  // agc1_slope1
		0,    // agc1_slope2
		128,  // agc2_pt1
		253,  // agc2_pt2
		81,   // agc2_slope1
		0,    // agc2_slope2

		17,  // alpha_mant
		27,  // alpha_exp
		23,  // beta_mant
		51,  // beta_exp

		1,  // perform_agc_softsplit
		{
		 0,
		 0,
		 0,
		 0,
		}
	}
};

/* PLL Configuration for COFDM BW_MHz = 8.000000 With external clock = 30.000000 */
const struct dibx000_bandwidth_config mt226x_bw_config = {
	60000, 15000, // internal, sampling
	1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 2, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 0, // ifreq = 0.000000 MHz
	20452225, // timf
	30000000, // xtal_hz
	0,
	0
};

//MT2067
const struct dibx000_agc_config dib7000_mt2067_agc_config = {
    BAND_FM | BAND_UHF | BAND_VHF,       // band_caps
    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (1 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup
    712,    // inv_gain
    41,     // time_stabiliz
    0,      // alpha_level
    118,    // thlock
    0,      // wbd_inv
    4095,   // wbd_ref
    0,      // wbd_sel
    0,      // wbd_alpha

    /*
    49151,  // agc1_max
    6554,  // agc1_min
    55705,  // agc2_max
    26214,   // agc2_min
    0,      // agc1_pt1
    87,     // agc1_pt2
    255,    // agc1_pt3
    122,     // agc1_slope1
    0,     // agc1_slope2
    87,    // agc2_pt1
    255,    // agc2_pt2
    44,     // agc2_slope1
    0,     // agc2_slope2
    */
    39321,  // agc1_max
    6554,  // agc1_min
    55705,  // agc2_max
    26214,   // agc2_min
    0,      // agc1_pt1
    87,     // agc1_pt2
    255,    // agc1_pt3
    94,     // agc1_slope1
    0,     // agc1_slope2
    87,    // agc2_pt1
    255,    // agc2_pt2
    44,     // agc2_slope1
    0,     // agc2_slope2

    21,     // alpha_mant
    25,     // alpha_exp
    28,     // beta_mant
    48,     // beta_exp
    0,      // perform_agc_softsplit
    {  0,     // split_min
       0, //     107,   // split_max
       0, //     51800, // global_split_min
       0, //     24700  // global_split_max
    },
};

const struct dibx000_agc_config dib8000_mt2067_agc_config = {

    BAND_FM | BAND_UHF | BAND_VHF,       // band_caps

    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    //                (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (1 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 <<
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), //

    712,  // inv_gain
    41,  // time_stabiliz

    0,  // alpha_level
    118,  // thlock

    0,     // wbd_inv
    4095,  // wbd_ref
    0,     // wbd_sel
    0,     // wbd_alpha

    52429, //65536.0*0.80,  // agc1_max
    6554,  //65536.0*0.10,  // agc1_min
    55706, //65536.0*0.85,  // agc2_max
    9830,  //65536.0*0.15,  // agc2_min

    0,  // agc1_pt1
    128,  //256.0*.50,  // agc1_pt2
    255,  // agc1_pt3

    90, //64.0*(0.8-0.10)/0.50,  // agc1_slope1
    0,  // agc1_slope2

    0,  // agc2_pt1
    128, //256.0*.50,  // agc2_pt2

    0,  // agc2_slope1
    77, //64.0*(0.85-0.15)/(1-0.50),  // agc2_slope2

    21,  // alpha_mant
    25,  // alpha_exp
    28,  // beta_mant
    48,  // beta_exp

    1,  // perform_agc_softsplit
    {
		0,
		0,
		0,
		0,
	}
};

const struct dibx000_agc_config max3541_hybrid_bg_agc_config = {
    BAND_UHF | BAND_VHF,       // band_caps

    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (1 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setu

    712,  // inv_gain
    41,   // time_stabiliz

    0,    // alpha_level
    118,  // thlock

    0,    // wbd_inv
    4096, // wbd_ref
    1,    // wbd_sel
    5,    // wbd_alpha

    47513,  // agc1_max
    29491,  // agc1_min
    52428,  // agc2_max
    26214,  // agc2_min

    0,      // agc1_pt1
    128,      // agc1_pt2
    255,    // agc1_pt3
    35,     // agc1_slope1
    0,     // agc1_slope2
    128,    // agc2_pt1
    255,    // agc2_pt2
    51,     // agc2_slope1
    0,     // agc2_slope2

    21,  // alpha_mant
    25,  // alpha_exp
    28,  // beta_mant
    48,  // beta_exp

    0,   // perform_agc_softsplit
    {
	 0,
	 0,
	 0,
	 0,
	}
};

const struct dibx000_agc_config max3541_hybrid_fg_agc_config = {
    BAND_UHF | BAND_VHF,       // band_caps

    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (1 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setu

    712,  // inv_gain
    41,   // time_stabiliz

    0,    // alpha_level
    118,  // thlock

    0,    // wbd_inv
    700, // wbd_ref
    1,    // wbd_sel
    5,    // wbd_alpha

    52428,  // agc1_max
    6553,  // agc1_min
    49151,  // agc2_max
    22937,  // agc2_min

    0,      // agc1_pt1
    154,      // agc1_pt2
    255,    // agc1_pt3
    75,     // agc1_slope1
    0,     // agc1_slope2
    154,    // agc2_pt1
    255,    // agc2_pt2
    64,     // agc2_slope1
    0,     // agc2_slope2

    21,  // alpha_mant
    25,  // alpha_exp
    28,  // beta_mant
    48,  // beta_exp

    0,   // perform_agc_softsplit
    {
		 0,
		 0,
		 0,
		 0,
		}
};

const struct dibx000_agc_config max3541_dib7000_fg_agc_config = {
    BAND_UHF | BAND_VHF,       // band_caps

    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setu

    712,  // inv_gain
    41,   // time_stabiliz

    0,    // alpha_level
    118,  // thlock

    0,    // wbd_inv
    512, // wbd_ref
    1,    // wbd_sel
    5,    // wbd_alpha

    49152,                 // agc1_max
    16384,                 // agc1_min
    42598,                 // agc2_max
    22938,                 // agc2_min

    0,                          // agc1_pt1
    0,                          // agc1_pt2
    255,                        // agc1_pt3
    57,       // agc1_slope1
    57,       // agc1_slope2
    143,                    // agc2_pt1
    143,                    // agc2_pt2
    44, // agc2_slope1
    44, // agc2_slope2

    21,  // alpha_mant
    25,  // alpha_exp
    28,  // beta_mant
    48,  // beta_exp

    0,   // perform_agc_softsplit
    {
		 0,
		 0,
		 0,
		 0,
		}
};

const struct dibx000_agc_config max3541_dib7000_bg_agc_config = {
    BAND_UHF | BAND_VHF,       // band_caps

    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setu

    712,  // inv_gain
    41,   // time_stabiliz

    0,    // alpha_level
    118,  // thlock

    0,    // wbd_inv
    2944, // wbd_ref
    1,    // wbd_sel
    5,    // wbd_alpha

    49152,                 // agc1_max
    16384,                 // agc1_min
    42598,                 // agc2_max
    22938,                 // agc2_min

    0,                          // agc1_pt1
    0,                          // agc1_pt2
    255,                        // agc1_pt3
    57,       // agc1_slope1
    57,       // agc1_slope2
    143,                    // agc2_pt1
    143,                    // agc2_pt2
    44, // agc2_slope1
    44, // agc2_slope2

    21,  // alpha_mant
    25,  // alpha_exp
    28,  // beta_mant
    48,  // beta_exp

    0,   // perform_agc_softsplit
    {
		 0,
		 0,
		 0,
		 0,
		}
};

const struct dibx000_agc_config max3541_dib8000_agc_config = {
    BAND_UHF | BAND_VHF,       // band_caps

    /* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=1,
     * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
    (0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setu

    712,  // inv_gain
    41,   // time_stabiliz

    0,    // alpha_level
    118,  // thlock

    1,    // wbd_inv
    384,  // wbd_ref
    0,    // wbd_sel
    5,    // wbd_alpha

    47513,                 // agc1_max
    6553,                 // agc1_min
    62258,                 // agc2_max
    14417,                 // agc2_min

    0,                          // agc1_pt1
    173,                          // agc1_pt2
    255,                        // agc1_pt3
    59,       // agc1_slope1
    0,       // agc1_slope2
    173,                    // agc2_pt1
    255,                    // agc2_pt2
    143, // agc2_slope1
    0, // agc2_slope2

    21,  // alpha_mant
    25,  // alpha_exp
    28,  // beta_mant
    48,  // beta_exp

    0,   // perform_agc_softsplit
    {
		 0,
		 0,
		 0,
		 0,
		}
};


const struct dibx000_bandwidth_config dib7000_mt2067_bw_config = {
    60750, 30375, // internal, sampling
    1, 9, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
    0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (1 << 12) | (517 << 0), // sad_cfg: refsel, sel, freq_15k
    (1 << 25) | 28334854, // ifreq = 35,1
    20199728, // timf
    27000000,
    3, 3, //refclk, divclk
};

const struct dibx000_bandwidth_config dib8000_mt2067_bw_config = {
    54000, 27000, // internal, sampling
    1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
    0, 0, 1, 0, 0 , // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
    (0 << 25) | 3827691, // ifreq = 57.080000 MHz
    20199729 , // timf
    27000000 , // xtal
    0,
    0
};

const struct dibx000_bandwidth_config max3541_dib7000_bw_config = {
    60000, 30000, // internal, sampling
    1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
    0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
    (1 << 25) | 27822217, // ifreq = 35.125000 MHz
    20452225, // timf
    30000000,
    3, 3, //refclk, divclk
};

const struct dibx000_bandwidth_config max3541_dib8000_bw_config = {
    60000, 30000, // internal, sampling
    1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
    0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (0 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
    (0 << 25) | 7437899, // ifreq = 36.650000 MHz
    18179756, // timf
    30000000,// xtal
    0,
    0
};

const struct dibx000_bandwidth_config dib8000_mt2067_pll_config = {
        56250, 28125, // internal, sampling
        2, 15, 1, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
        0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
        (3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
        (0 << 25) | 9544371, // ifreq = 36.125000 MHz
        19391739, // timf
        30000000, // xtal
        0,
        0
};

const struct dibx000_bandwidth_config dib8000_mt2067_pll_config_slave = {
        56250, 28125, // internal, sampling
        2, 8, 1, 0, 1, // pll_cfg: prediv, ratio, range, reset, bypass
        1, 0, 1, 0, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
        (3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
        (0 << 25) | 9544371, // ifreq = 36.125000 MHz
        19391739, // timf
        56250000, // xtal
        0,
        0
};


/* MT2060 */
const struct dibx000_agc_config mt2060_dib7000pc_agc_config = {
	BAND_UHF | BAND_VHF,

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712, // inv_gain
	41,  // time_stabiliz

	0,   // alpha_level
	118, // thlock

	0,    // wbd_inv
	4095, // wbd_ref
	0,    // wbd_sel
	0,    // wbd_alpha

#if 0 // org
	42598, // agc1_max = 0.65
	17694, // agc1_min = 0.27
	45875, // agc2_max = 0.70
	2621,  // agc2_min = 0.04

	0,   // agc1_pt1
	76,  // agc1_pt2
	139, // agc1_pt3

	52, // agc1_slope1
	59, // agc1_slope2

	107, // agc2_pt1
	172, // agc2_pt2

	57, // agc2_slope1
	70, // agc2_slope2
#endif

#if 0 // cal1
	0.65*65536.0, // agc1_max
	0.25*65536.0, // agc1_min
	0.65*65536.0, // agc2_max
	0.00*65536.0,  // agc2_min

	0,   // agc1_pt1
	(.35/.65)*256.0,  // agc1_pt2
	255, // agc1_pt3

	0, // agc1_slope1
	255, // agc1_slope2

	0, // agc2_pt1
	0, // agc2_pt2

	0, // agc2_slope1
	(0.65-0.00)*64.0, // agc2_slope2
#endif

#if 01 // cal1 calculated
	42598, // agc1_max
	16384, // agc1_min
	42598, // agc2_max
	    0, // agc2_min

	  0,   // agc1_pt1
	137,   // agc1_pt2
	255,   // agc1_pt3

	  0,   // agc1_slope1
	255,   // agc1_slope2

	0,     // agc2_pt1
	0,     // agc2_pt2

	 0,    // agc2_slope1
	41,    // agc2_slope2
#endif

	15, // alpha_mant
	25, // alpha_exp

	28, // beta_mant
	48, // beta_exp

	0, // perform_agc_softsplit
	{
		 0,
		 0,
		 0,
		 0,
		}
};

const struct dibx000_agc_config mt2060_agc_config = {
	BAND_UHF | BAND_VHF,       // band_caps

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712,  // inv_gain
	41,  // time_stabiliz

	0,  // alpha_level
	118,  // thlock

	0,     // wbd_inv
	4095,  // wbd_ref
	0,     // wbd_sel
	0,     // wbd_alpha

	42598,  // agc1_max
	17694,  // agc1_min
	45875,  // agc2_max
	2621,  // agc2_min
	0,  // agc1_pt1
	76,  // agc1_pt2
	139,  // agc1_pt3
	52,  // agc1_slope1
	59,  // agc1_slope2
	107,  // agc2_pt1
	172,  // agc2_pt2
	57,  // agc2_slope1
	70,  // agc2_slope2

	21,  // alpha_mant
	25,  // alpha_exp
	28,  // beta_mant
	48,  // beta_exp

	1,  // perform_agc_softsplit
	{  0,     // split_min
	   107,   // split_max
	   51800, // global_split_min
	   24700  // global_split_max
	},
};

/* MC44CD02 */
const struct dibx000_bandwidth_config mc44cd02_bw_config = {
    60000, 15000, // internal, sampling
    1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
    0, 0, 1, 1, 2, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
    0, // ifreq
    20452225, // timf
    30000000, // xtal_hz
    0,
    0
};

const struct dibx000_agc_config mc44cd02_agc_config = {
	BAND_UHF,       // band_caps

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=0, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (0 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712,  // inv_gain
	21,  // time_stabiliz

	0,  // alpha_level
	118,  // thlock

	0,  // wbd_inv
	2867,  // wbd_ref
	0,  // wbd_sel
	2,  // wbd_alpha

	55050,  // agc1_max
	0,  // agc1_min
	53084,  // agc2_max
	0,  // agc2_min
	0,  // agc1_pt1
	128,  // agc1_pt2
	124,  // agc1_pt3
	107,  // agc1_slope1
	107,  // agc1_slope2
	128,  // agc2_pt1
	255,  // agc2_pt2
	103,  // agc2_slope1
	0,  // agc2_slope2

	17,  // alpha_mant
	27,  // alpha_exp
	23,  // beta_mant
	51,  // beta_exp

	0,  // perform_agc_softsplit
	{
		 0,
		 0,
		 0,
		 0,
		}
};

const struct dibx000_bandwidth_config mt2060_bw_config = {
        60000, 30000, // internal, sampling
        1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
        0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
        (3 << 14) | (1 << 12) | (524 << 0), // sad_cfg: refsel, sel, freq_15k
        60258167, // ifreq
        20452225, // timf
        30000000, // xtal_hz
        0,
        0
};

const struct dibx000_bandwidth_config dib8000_mt2060_pll_config = {
    56250, 28125, // internal, sampling
    2, 15, 1, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
    0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
    (0 << 25) |10170721, // ifreq = 36.650000 MHz
    19391739, // timf
    30000000, // xtal
    0,
    0
};

const struct dibx000_bandwidth_config dib8000_mt2060_pll_config_slave = {
    56250, 28125, // internal, sampling
    2, 8, 1, 0, 1, // pll_cfg: prediv, ratio, range, reset, bypass
    1, 0, 1, 0, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
    (3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
    (0 << 25) |10170721, // ifreq = 36.650000 MHz
    19391739, // timf
    56250000, // xtal
    0,
    0
};

#if 0
struct dibx000_agc_config env57h12d5_agc_config = {
	BAND_UHF | BAND_VHF,       // band_caps

	/* P_agc_use_sd_mod1=0, P_agc_use_sd_mod2=0, P_agc_freq_pwm_div=5, P_agc_inv_pwm1=0, P_agc_inv_pwm2=0,
	 * P_agc_inh_dc_rv_est=0, P_agc_time_est=3, P_agc_freeze=0, P_agc_nb_est=2, P_agc_write=0 */
	(0 << 15) | (0 << 14) | (5 << 11) | (0 << 10) | (0 << 9) | (0 << 8) | (3 << 5) | (0 << 4) | (2 << 1) | (0 << 0), // setup

	712,  // inv_gain
	41,  // time_stabiliz

	0,  // alpha_level
	118,  // thlock

	0,  // wbd_inv
	4096,  // wbd_ref
	0,  // wbd_sel
	0,  // wbd_alpha

	42598,  // agc1_max
	17694,  // agc1_min
	45875,  // agc2_max
	2621,  // agc2_min
	0,  // agc1_pt1
	76,  // agc1_pt2
	139,  // agc1_pt3
	52,  // agc1_slope1
	59,  // agc1_slope2
	107,  // agc2_pt1
	172,  // agc2_pt2
	57,  // agc2_slope1
	70,  // agc2_slope2

	21,  // alpha_mant
	25,  // alpha_exp
	28,  // beta_mant
	48,  // beta_exp

	1,  // perform_agc_softsplit
};
#endif

const struct dibx000_bandwidth_config dib8000_dib0070_pll_config = {
	52500, 13125, // internal, sampling
	1, 7, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 2, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 0, // ifreq = 0 MHz
	20776863, // timf
	30000000, // xtal_hz
	0,
	0
};

/*struct dibx000_bandwidth_config dib8000_dib0070_pll_config_12MHz = {
	60000, 15000, // internal, sampling
	1, 20, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 2, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 0, // ifreq = 0 MHz
	18179755, // timf
	12000000, // xtal_hz
};*/

const struct dibx000_bandwidth_config dib8000_dib0070_pll_config_slave = {
    52500, 13125, // internal, sampling
	1, 4, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 2, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 0, // ifreq = 0 MHz
	20776863, // timf
	52500000, // xtal_hz
	0,
	0
};

// -------- 56.25 MHz -------------
const struct dibx000_bandwidth_config dib8000_mt2060_pll_config_36_125 = {
	56250, 28125, // internal, sampling
	2, 15, 1, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 9544371, // ifreq = 36.125000 MHz
	19391739, // timf
	30000000, // xtal
	0,
	0
};

const struct dibx000_bandwidth_config dib8000_mt2060_pll_config_slave_36_125 = {
	56250, 28125, // internal, sampling
	2, 8, 1, 0, 1, // pll_cfg: prediv, ratio, range, reset, bypass
	1, 0, 1, 0, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 9544371, // ifreq = 36.125000 MHz
	19391739, // timf
	56250000, // xtal
	0,
	0
};

const struct dibx000_bandwidth_config dib8001_mt2060_pll_config = {
	60000, 30000, // internal, sampling
	1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 6850697, // ifreq = 36.125000 MHz
	18179756, // timf
	30000000, // xtal
	0,
	0
};

const struct dibx000_bandwidth_config dib8001_mt2060_pll_config_27MHz = {
	54000, 27000, // internal, sampling
	1, 8, 3, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0, // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	(0 << 25) | 11340155, // ifreq = 36.125000 MHz
	//(1 << 25) | 22214277, // ifreq = 36.125000 MHz
	20199729, // timf
	27000000, // xtal
	0,
	0
};


const struct dibx000_bandwidth_config dib8000_mt2067_27mhz_pll_config = {
	54000, 27000, // internal, sampling
	2, 16, 1, 1, 0, // pll_cfg: prediv, ratio, range, reset, bypass
	0, 0, 1, 1, 0 , // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	//(1 << 25) | 22214277, // ifreq = 36.125000 MHz
	(1 << 25) | 21561829, // ifreq = 36.650000 MHz
	20199729 , // timf
	27000000 , // xtal
	0,
	0
};

const struct dibx000_bandwidth_config dib8000_mt2067_27mhz_pll_config_slave = {
	54000, 27000, // internal, sampling
	2, 8, 1, 0, 1, // pll_cfg: prediv, ratio, range, reset, bypass
	1, 0, 1, 0, 0 , // misc: refdiv, bypclk_div, IO_CLK_en_core, ADClkSrc, modulo
	(3 << 14) | (1 << 12) | (599 << 0), // sad_cfg: refsel, sel, freq_15k
	//(1 << 25) | 22214277, // ifreq = 36.125000 MHz
	(1 << 25) | 21561829, // ifreq = 36.650000 MHz
	20199729 , // timf
	54000000 , // xtal
	0,
	0
};
