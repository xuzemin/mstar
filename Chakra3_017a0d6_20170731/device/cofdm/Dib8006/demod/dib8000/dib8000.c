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
#include "Utl.h"
#include "msAPI_Memory.h"
static int dib8000_wakeup(struct dibFrontend *fe)
{
    struct dib8000_state *state = fe->demod_priv;

    dib8000_set_power_mode(state, DIB8000M_POWER_ALL);
    dib8000_set_adc_state(state, DIBX000_ADC_ON);
    if (dib8000_set_adc_state(state, DIBX000_SLOW_ADC_ON) != DIB_RETURN_SUCCESS)
        dbgp("FE %d Can not start Slow ADC\n", fe->id);

    return DIB_RETURN_SUCCESS;
}

static int dib8000_sleep(struct dibFrontend *fe, uint8_t deep)
{
    struct dib8000_state *st = fe->demod_priv;
    if (!deep) {
        dib8000_set_output_mode(st, OUTPUT_MODE_OFF);
        dib8000_set_power_mode(st, DIB8000M_POWER_INTERFACE_ONLY);
        return dib8000_set_adc_state(st, DIBX000_SLOW_ADC_OFF) |
            dib8000_set_adc_state(st, DIBX000_ADC_OFF);
    } else {
        dibx000_deep_sleep_i2c_master(&st->i2c_master);
        return DIB_RETURN_SUCCESS;
    }
}

void dib8000_set_timf(struct dibFrontend *fe, uint32_t timf)
{
    struct dib8000_state *state = fe->demod_priv;
    dib8000_write_word(state, 29, (uint16_t) (timf >> 16) & 0xffff);
    dib8000_write_word(state, 30, (uint16_t)  timf        & 0xffff);
}

int dib8000_get_timf(struct dibFrontend *fe)
{
    struct dib8000_state *state = fe->demod_priv;
    uint16_t buf[2];
    data_bus_client_read_multi16(demod_get_data_bus_client(state->fe), 29, buf, 2);
    return ((buf[0] << 16) | buf[1]);
}

void dib8000_set_dds(struct dib8000_state *state, int32_t offset_khz)
{
    int16_t unit_khz_dds_val = (uint16_t) (67108864 / state->cfg.pll->internal); /* 2**26 / Fsampling is the unit 1KHz offset */
    uint32_t abs_offset_khz = abs_offset_khz = ABS(offset_khz),
        dds = state->cfg.pll->ifreq & 0x1ffffff;
    uint8_t invert = !!(state->cfg.pll->ifreq & (1 << 25));

    if (offset_khz < 0)
        unit_khz_dds_val *= -1;

    /* IF tuner */
    if (invert)
        dds -= abs_offset_khz * unit_khz_dds_val;
    else
        dds += abs_offset_khz * unit_khz_dds_val;

    dbgp("FE %d: Setting a DDS frequency offset of %c%dkHz\n", state->fe->id, invert ? '-' : ' ', dds / unit_khz_dds_val);

    if (abs_offset_khz <= (state->cfg.pll->internal/2)) { /* Max dds offset is the half of the demod freq */
        dib8000_write_word(state, 26, (0 << 1) | invert);
        dib8000_write_word(state, 27, (uint16_t) (dds >> 16) & 0x1ff);
        dib8000_write_word(state, 28, (uint16_t) (dds      ) & 0xffff);
    }
}

static int dib8000_get_signal_status(struct dibFrontend *fe, struct dibDVBSignalStatus *status)
{
    struct dib8000_state *st = fe->demod_priv;
    uint16_t v = dib8000_read_word(st, 568);

    status->tps_data_lock  = (v >> 1) & 1; /* TMCC Data lock */
    status->mpeg_data_lock = !!((v >> 5) & 7); /* if one of the fec_locks is one, we say data is present */

    if (status->mpeg_data_lock)
        status->bit_error_rate = dib8000_read32(st,560);
    else
        status->bit_error_rate = 2097151;

    v = dib8000_read_word(st, 390);
    status->signal_strength = (100 - ((v * 100) / 65535));
    return DIB_RETURN_SUCCESS;
}

static int dib8000_set_wbd_ref(struct dibFrontend *fe, uint16_t value)
{
    struct dib8000_state *state = fe->demod_priv;
    if (value > 4095)
        value = 4095;
    state->wbd_ref = value;
    return dib8000_write_word(state, 106, value);
}

static uint16_t dib8000_get_wbd_ref(struct dibFrontend *fe)
{
    struct dib8000_state *state = fe->demod_priv;
    return state->wbd_ref;
}

static const int32_t lut_1000ln_mant[] =
{
    908,7003,7090,7170,7244,7313,7377,7438,7495,7549,7600
};

int32_t dib8000_get_adc_power(struct dibFrontend *fe, uint8_t mode)
{
    struct dib8000_state *state = fe->demod_priv;
    uint32_t ix =0, tmp_val =0, exp0 = 0, mant = 0;
    int32_t val;

    val = dib8000_read32(state,384);
    /* mode = 1 : ln_agcpower calc using mant-exp conversion and mantis look up table */
    if(mode) {
        tmp_val = val;
        while(tmp_val>>=1)
            exp0++;
        mant = (val * 1000 / (1<<exp0));
        ix = (uint8_t)((mant-1000)/100); /* index of the LUT */
        val = (lut_1000ln_mant[ix] + 693*(exp0-20) - 6908); /* 1000 * ln(adcpower_real) ; 693 = 1000ln(2) ; 6908 = 1000*ln(1000) ; 20 comes from adc_real = adc_pow_int / 2**20 */
        val = (val*256)/1000;
    }
    return val;
}


static uint32_t dib8000_ctrl_timf(struct dibFrontend *fe, uint8_t op, uint32_t timf)
{
    struct dib8000_state *state = fe->demod_priv;
    switch (op) {
        case DEMOD_TIMF_SET: state->timf = timf; break;
        case DEMOD_TIMF_UPDATE: dib8000_update_timf(state); break;
        case DEMOD_TIMF_GET: break;
    }
    dib8000_set_bandwidth(state, fe->current_bw);
    return state->timf;
}

static int dib8000_get_channel(struct dibFrontend *fe, struct dibChannel *cd)
{
    struct dib8000_state *state = fe->demod_priv;
    uint16_t v;
    int i;

    cd->type = STANDARD_ISDBT;

    v = (dib8000_read_word(state, 570) & 0x30 ) >> 4; // read mode
    switch (v) {
        case 1: cd->u.isdbt.nfft = FFT_2K; break;
        case 2: cd->u.isdbt.nfft = FFT_4K; break;
        default:
        case 3: cd->u.isdbt.nfft = FFT_8K; break;
    }
    v = dib8000_read_word(state, 570) & 0x3;

    switch (v) {
        case 0: cd->u.isdbt.guard = GUARD_INTERVAL_1_32; break;
        case 1: cd->u.isdbt.guard = GUARD_INTERVAL_1_16; break;
        case 2: cd->u.isdbt.guard = GUARD_INTERVAL_1_8 ; break;
        default:
        case 3: cd->u.isdbt.guard = GUARD_INTERVAL_1_4 ; break;
    }
    cd->u.isdbt.partial_reception  =  dib8000_read_word(state, 505) & 0x1;
    cd->u.isdbt.sb_mode            =  dib8000_read_word(state, 508) & 0x1;
    cd->u.isdbt.spectrum_inversion = (dib8000_read_word(state, 570) & 0x40) >> 6;

    for (i=0; i<3; i++) {
        cd->u.isdbt.layer[i].code_rate = dib8000_read_word(state, 481+i) & 0x7;

        switch (dib8000_read_word(state, 487+i)) {
            case 0: cd->u.isdbt.layer[i].constellation = QAM_DQPSK; break;
            case 1: cd->u.isdbt.layer[i].constellation = QAM_QPSK ; break;
            case 2: cd->u.isdbt.layer[i].constellation = QAM_16QAM; break;
            default :
            case 3: cd->u.isdbt.layer[i].constellation = QAM_64QAM; break;
        }
        cd->u.isdbt.layer[i].nb_segments = dib8000_read_word(state, 493+i) & 0xf;
        cd->u.isdbt.layer[i].time_intlv  = dib8000_read_word(state, 499+i) & 0x3;
    }
    cd->u.isdbt.sb_subchannel = state->subchannel;

    return DIB_RETURN_SUCCESS;
}

static int dib8000_release(struct dibFrontend *fe)
{
    struct dib8000_state *st = fe->demod_priv;
    dibx000_exit_i2c_master(&st->i2c_master);
    if (st != NULL)
        MemFree(st,sizeof(struct dib8000_state));
    if (fe->release_compat_fe & COMPONENT_LAYER_RELEASE)
        MemFree(fe, sizeof(struct dibFrontend));
    return 0;
}

static uint16_t dib8000_identify(struct dibDataBusClient *client)
{
    uint16_t value;	
    //because of glitches sometimes
    value = data_bus_client_read16(client, 896);

    if ((value = data_bus_client_read16(client, 896)) != 0x01b3) {
        dbgp("wrong Vendor ID (read=0x%x)\n", value);
        return 0;
    }

    value = data_bus_client_read16(client, 897);
    if (value != 0x8000 && value != 0x8001 && value != 0x8002) {
        dbgp("wrong Device ID (%x)\n", value);
        return 0;
    }

    switch (value) {
        case 0x8000: dbgp( "found DiB8000A\n"); break;
        case 0x8001: dbgp( "found DiB8000B\n"); break;
        case 0x8002: dbgp( "found DiB8000C\n"); break;
    }

    return value;
}

/* exported functions */
void dib8000_set_hostbus_diversity(struct dibFrontend *fe, uint8_t onoff)
{
    struct dib8000_state *st = fe->demod_priv;
    st->cfg.hostbus_diversity = onoff;
}

/* demod operations */
static int dib8000_demod_set_output_mode(struct dibFrontend *fe, int mode)
{
    struct dib8000_state *st = fe->demod_priv;
    return dib8000_set_output_mode(st, mode);
}

static int dib8000_set_gpio(struct dibFrontend *fe, uint8_t num, uint8_t dir, uint8_t val)
{
    struct dib8000_state *state = fe->demod_priv;
    return dib8000_cfg_gpio(state, num, dir, val);
}

static int dib8000_sad_calib(struct dib8000_state *state)
{
    /* internal */
    dib8000_write_word(state, 923, (0 << 1) | (0 << 0));
    dib8000_write_word(state, 924, 776); // 0.625*3.3 / 4096

    /* do the calibration */
    dib8000_write_word(state, 923, (1 << 0));
    dib8000_write_word(state, 923, (0 << 0));

    DibMSleep(1);
    return DIB_RETURN_SUCCESS;
}

int dib8000_set_bandwidth(struct dib8000_state *state, uint32_t bw)
{
    uint32_t timf;

    if (bw == 0)
        bw = 6000;

    if (state->timf == 0) {
        dbgp("FE %d is going to use the default TIMF value\n", state->fe->id);
        timf = state->timf_default;
    } else {
        dbgp("FE %d is going to use the updated TIMF value\n", state->fe->id);
        timf = state->timf;
    }

    dib8000_write_word(state, 29, (uint16_t) ((timf >> 16) & 0xffff));
    dib8000_write_word(state, 30, (uint16_t) ((timf      ) & 0xffff));

    return DIB_RETURN_SUCCESS;
}

static void dib8000_reset_pll_common(struct dib8000_state *state, const struct dibx000_bandwidth_config *bw)
{
    dbgp("FE %d ifreq: %d %x, inversion: %d\n", state->fe->id, bw->ifreq, bw->ifreq, bw->ifreq >> 25);
    dib8000_write_word(state, 23, (uint16_t)(((bw->internal*1000) >> 16) & 0xffff)); /* P_sec_len */
    dib8000_write_word(state, 24,  (uint16_t)((bw->internal*1000)        & 0xffff));
    dib8000_write_word(state, 27, (uint16_t)(( bw->ifreq          >> 16) & 0x01ff));
    dib8000_write_word(state, 28,   (uint16_t)(bw->ifreq                 & 0xffff));
    dib8000_write_word(state, 26,  (uint16_t)((bw->ifreq          >> 25) & 0x0003));
    dib8000_write_word(state, 922, bw->sad_cfg);
}

static void dib8000_reset_pll(struct dib8000_state *state)
{
    const struct dibx000_bandwidth_config *pll = state->cfg.pll;
    uint16_t clk_cfg1;

    /* clk_cfg0 */
    dib8000_write_word(state, 901, (pll->pll_prediv << 8) | (pll->pll_ratio << 0));

    /* clk_cfg1 */
    clk_cfg1 =                  (0 << 10) |
                                 (0 << 9) |
               (pll->IO_CLK_en_core << 8) |
                   (pll->bypclk_div << 5) |
                (pll->enable_refdiv << 4) |
                                 (1 << 3) |
                    (pll->pll_range << 1) |
                            pll->pll_reset;

    dib8000_write_word(state, 902, clk_cfg1);
    clk_cfg1 = (clk_cfg1 & 0xfff7) | (1 << 10) |(pll->pll_bypass << 3);
    dib8000_write_word(state, 902, clk_cfg1);

    dbgp("FE %d clk_cfg1 = 0x%04x\n", state->fe->id, clk_cfg1); /* 0x507 1 0 1 000 0 0 11 1 */

    /* smpl_cfg: P_refclksel=2, P_ensmplsel=1 nodivsmpl=1*/
    if (state->cfg.pll->ADClkSrc == 0)
        dib8000_write_word(state, 904, (0 << 15) |  (0 << 12) | (0 << 10) | (pll->modulo << 8) | (pll->ADClkSrc << 7) | (0 << 1));
    else if (state->cfg.refclksel != 0)
        dib8000_write_word(state, 904, (0 << 15) |  (1 << 12) | ((state->cfg.refclksel&0x3) << 10) | (pll->modulo << 8) | (pll->ADClkSrc << 7) | (0 << 1));
    else
        dib8000_write_word(state, 904, (0 << 15) |  (1 << 12) | (3 << 10) | (pll->modulo << 8) | (pll->ADClkSrc << 7) | (0 << 1));

    dib8000_reset_pll_common(state, pll);
}

int dib8000_update_pll(struct dibFrontend *fe, struct dibx000_bandwidth_config *pll)
{
    struct dib8000_state *state = fe->demod_priv;
    if (pll != NULL) {
        dib8000_write_word(state, 901, (state->cfg.pll->pll_prediv << 8) | (pll->pll_ratio << 0)); // only the PLL ratio is updated.
        return DIB_RETURN_SUCCESS;
    }
    return DIB_RETURN_ERROR;
}

static const uint16_t dib8000_defaults[] = {
    /* auto search configuration - lock0 by default waiting
       for cpil_lock; lock1 cpil_lock; lock2 tmcc_sync_lock */

    3, 7,
    	0x0004,
    	0x0400,
    	0x0814,

    12, 11,
    	0x001b,
    	0x7740,
    	0x005b,
    	0x8d80,
    	0x01c9,
    	0xc380,
    	0x0000,
    	0x0080,
    	0x0000,
    	0x0090,
    	0x0001,
    	0xd4c0,

    /*1, 32,
    	0x6680 // P_corm_thres Lock algorithms configuration */

    11, 80, /* set ADC level to -16 */
    	(1 << 13) - 825 - 117,
    	(1 << 13) - 837 - 117,
    	(1 << 13) - 811 - 117,
    	(1 << 13) - 766 - 117,
    	(1 << 13) - 737 - 117,
    	(1 << 13) - 693 - 117,
    	(1 << 13) - 648 - 117,
    	(1 << 13) - 619 - 117,
    	(1 << 13) - 575 - 117,
    	(1 << 13) - 531 - 117,
    	(1 << 13) - 501 - 117,

    4, 108,
            0,
            0,
            0,
            0,

    /* Imp noise config */
#ifdef CONFIG_DIB8000_USE_IMPULSIVE_NOISE_COMPENSATION
    4, 141,
        219, /* inh, rst_burst & P_imp_Tpow*/
        219, /* P_imp_Taccpow */
        183, /* P_imp_Tparam */
        18, /* P_imp_sum_gamma_length & P_imp_Tdelta */
    1, 151,
        810, /* P_imp_satin_var */
    1, 156,
        113, /* P_imp_mkv_log_prior_0 */
    1, 161,
        113, /* P_imp_mkv_log_prior_1 */
    7, 166,
        113, /* P_imp_mkv_log_prior_2 */
        1164, /* P_imp_mkvl_alpha_3 */
        16382, /* P_imp_mkvl_1_alpha_3 */
        1459,  /* P_imp_mkvl_beta_3 */
        16363, /* P_imp_mkvl_1_beta_3 */
        113,   /* P_imp_mkv_log_prior_3 */
        64512, /* P_imp_mkv_log_prior_4 */
#endif

    1, 175,
    	0x0410,
    1, 179,
    	8192, // P_fft_nb_to_cut

    6, 181,
    	0x2800, // P_coff_corthres_ ( 2k 4k 8k ) 0x2800
    	0x2800,
    	0x2800,
    	0x2800, // P_coff_cpilthres_ ( 2k 4k 8k ) 0x2800
    	0x2800,
    	0x2800,

    2, 193,
    	0x0666, // P_pha3_thres
    	0x0000, // P_cti_use_cpe, P_cti_use_prog

    2, 205,
    	0x200f, // P_cspu_regul, P_cspu_win_cut
    	0x000f, // P_des_shift_work

    5, 215,
    	0x023d, // P_adp_regul_cnt
    	0x00a4, // P_adp_noise_cnt
    	0x00a4, // P_adp_regul_ext
    	0x7ff0, // P_adp_noise_ext
    	0x3ccc, // P_adp_fil

    1, 230,
    	0x0000, // P_2d_byp_ti_num

    1, 263,
    	0x800, //P_equal_thres_wgn

    1, 268,
    	(2 << 9) | 39, // P_equal_ctrl_synchro, P_equal_speedmode

    1, 270,
    	0x0001, // P_div_lock0_wait
    1, 285,
    	0x0020, //p_fec_
    1, 299,
    	0x0062, // P_smo_mode, P_smo_rs_discard, P_smo_fifo_flush, P_smo_pid_parse, P_smo_error_discard

    1, 338,
    	(1 << 12) | // P_ctrl_corm_thres4pre_freq_inh=1
            (1 << 10) | // P_ctrl_pre_freq_mode_sat=1
            (0 <<  9) | // P_ctrl_pre_freq_inh=0
            (3 <<  5) | // P_ctrl_pre_freq_step=3
            (1 <<  0),  // P_pre_freq_win_len=1

    1, 903,
    	(0 << 4) | 2, // P_divclksel=0 P_divbitsel=2 (was clk=3,bit=1 for MPW)

    0,
};

static int dib8000_set_bus_speed(struct dibFrontend *fe, uint16_t bus_type, uint32_t speed)
{
    struct dib8000_state *state = fe->demod_priv;

    if (data_bus_host_type( demod_get_data_bus_client(fe)->host ) == bus_type) {
        if ((bus_type == DATA_BUS_I2C) && (state->cfg.pll->internal < 57000) && (speed > 400))
            data_bus_client_set_speed(demod_get_data_bus_client(fe), 400);
        else
            data_bus_client_set_speed(demod_get_data_bus_client(fe), speed);
    }
    return DIB_RETURN_SUCCESS;
}

static int dib8000_reset(struct dibFrontend *fe)
{
    struct dib8000_state *state = fe->demod_priv;
    uint16_t l = 0, r;
    const uint16_t *n;

    dib8000_write_word(state, 1287, 0x0003); /* sram lead in, rdy */

    dib8000_set_bus_speed(fe, DATA_BUS_I2C, 200);
    dib8000_set_bus_speed(fe, DATA_BUS_MMIO_SRAM_LIKE, 0);

    if ((state->revision = dib8000_identify( demod_get_data_bus_client(fe) )) == 0)
        return DIB_RETURN_ERROR;

    if (state->revision == 0x8000)
        dbgp("FE %d Error : dib8000 MA not supported\n", fe->id);

    dibx000_reset_i2c_master(&state->i2c_master);
    dib8000_set_power_mode(state, DIB8000M_POWER_ALL);

    dib8000_set_adc_state(state, DIBX000_ADC_OFF);

    /* restart all parts */
    dib8000_write_word(state, 770, 0xffff);
    dib8000_write_word(state, 771, 0xffff);
    dib8000_write_word(state, 772, 0xfffc);
    dib8000_write_word(state, 1280, 0x004d);
    dib8000_write_word(state, 1281, 0x000c);

    dib8000_write_word(state, 770, 0x0000);
    dib8000_write_word(state, 771, 0x0000);
    dib8000_write_word(state, 772, 0x0000);
    dib8000_write_word(state, 898, 0x0004); // sad
    dib8000_write_word(state, 1280, 0x0000);
    dib8000_write_word(state, 1281, 0x0000);

    /* drives */
    if (state->cfg.drives)
        dib8000_write_word(state, 906, state->cfg.drives);
    else {
        dbgp("FE %d : Using standard PAD-drive-settings, please adjust settings in config-struct to be optimal.\n",fe->id);
        dib8000_write_word(state, 906, 0x2d98); // min drive SDRAM - not optimal - adjust
    }

    dib8000_reset_pll(state);
    dib8000_write_word(state, 898, 0x0004); // sad

    dib8000_set_bus_speed(fe, DATA_BUS_I2C, 1000);
    dib8000_set_bus_speed(fe, DATA_BUS_MMIO_SRAM_LIKE, 1);

    if (dib8000_reset_gpio(state) != DIB_RETURN_SUCCESS)
        dbgp("FE %d : GPIO reset was not successful.\n",fe->id);

	dbgp("dib8000_reset,set mode: %d\n", OUTPUT_MODE_OFF);
    if (dib8000_set_output_mode(state, (int)OUTPUT_MODE_OFF) != DIB_RETURN_SUCCESS)
        dbgp("FE %d : OUTPUT_MODE could not be resetted.\n",fe->id);

    state->current_agc = NULL;

    // P_iqc_alpha_pha, P_iqc_alpha_amp, P_iqc_dcc_alpha, ...
    /* P_iqc_ca2 = 0; P_iqc_impnc_on = 0; P_iqc_mode = 0;*/
    if(state->cfg.pll->ifreq == 0)
        dib8000_write_word(state, 40, 0x0755); /* P_iqc_corr_inh = 0 enable IQcorr block*/
    else
        dib8000_write_word(state, 40, 0x1f55); /* P_iqc_corr_inh = 1 disable IQcorr block*/

    n = dib8000_defaults;
    l = *n++;
    while (l) {
        r = *n++;
        do {
            dib8000_write_word(state, r, *n++);
            r++;
        } while (--l);
        l = *n++;
    }

    state->isdbt_cfg_loaded=0;

    //div_cfg override for special configs
    if (state->cfg.div_cfg != 0)
        dib8000_write_word(state, 903, state->cfg.div_cfg);

    /* unforce divstr regardless whether i2c enumeration was done or not */
    dib8000_write_word(state, 1285, dib8000_read_word(state, 1285) & ~(1 << 1) );

    dib8000_set_bandwidth(state, 6000);

    dib8000_set_adc_state(state, DIBX000_SLOW_ADC_ON);
    dib8000_sad_calib(state);
    dib8000_set_adc_state(state, DIBX000_SLOW_ADC_OFF);

    demod_set_ber_rs_len(fe, 3);

    dib8000_set_power_mode(state, DIB8000M_POWER_INTERFACE_ONLY);

	
    return DIB_RETURN_SUCCESS;
}

/* first_addr is 0x90 for DiB8000 */
int dib8000_i2c_enumeration(struct dibDataBusHost *host, int no_of_demods, uint8_t default_addr, uint8_t first_addr)
{
    int k = 0;
    uint8_t new_addr = 0;
    struct dibDataBusClient client;

    data_bus_client_init(&client, &dibx000_i2c_data_bus_client, host);
    data_bus_client_set_speed(&client, 200);

    for (k = no_of_demods-1; k >= 0; k--) {
        /* designated i2c address */
        new_addr = first_addr + (k << 1);

        data_bus_client_set_device_id(&client, new_addr);
        data_bus_client_write16(&client, 1287, 0x0003); /* sram lead in, rdy */
        if (dib8000_identify(&client) == 0) {
            data_bus_client_write16(&client, 1287, 0x0003); /* sram lead in, rdy */
            data_bus_client_set_device_id(&client, default_addr);
            if (dib8000_identify(&client) == 0) {
                dbgp("#%d: not identified\n", k);
                return DIB_RETURN_ERROR;
            }
        }

        /* start diversity to pull_down div_str - just for i2c-enumeration */
        data_bus_client_write16(&client, 1286, (1 << 10) | (4 << 6));

        /* set new i2c address and force divstart */
        data_bus_client_write16(&client, 1285, (new_addr << 2) | 0x2);
        data_bus_client_set_device_id(&client, new_addr);
        dib8000_identify(&client);
        dbgp("IC %d initialized (to i2c_address 0x%x)\n", k, new_addr);
    }

    for (k = 0; k < no_of_demods; k++) {
        new_addr = first_addr | (k << 1);
        data_bus_client_set_device_id(&client, new_addr);

        // unforce divstr
        data_bus_client_write16(&client, 1285, new_addr << 2);

        /* deactivate div - it was just for i2c-enumeration */
        data_bus_client_write16(&client, 1286, 0);
    }

	return DIB_RETURN_SUCCESS;
}

struct dibDataBusHost * dib8000_get_i2c_master(struct dibFrontend *fe, enum dibx000_i2c_interface intf, int gating)
{
    struct dib8000_state *st = fe->demod_priv;
    return dibx000_get_i2c_adapter(&st->i2c_master, intf, gating);
}

void dib8000_close_gate(struct dibFrontend *fe)
{
    struct dib8000_state *state = fe->demod_priv;
    dib8000_write_word(state, 1025, 1 << 8);
}

void dib8000_enable_output_clock(struct dibFrontend *fe)
{
    struct dib8000_state *state = fe->demod_priv;
    dib8000_reset_pll(state);
}

// i2c_master
void dib8000_reset_sync_pha(struct dibFrontend* fe, uint32_t loop_factor)
{
    struct dib8000_state *state = fe->demod_priv;
    struct dibDataBusClient *client = demod_get_data_bus_client(state->fe);
    uint32_t i,j;

    if (state->diversity_onoff == 0) {
        dbgp("FE %d : Diversity is not active\n", fe->id);
        return;
    }
    for (i = 0; i < loop_factor; i++) {
        uint8_t div_errors[128]; // = dib8000_read_word(state, 547)& 0x3fff;
	uint16_t error = 0;
        data_bus_client_read_attr( client, 547, DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT | DATA_BUS_ACCESS_MODE_16BIT, div_errors, 128);
        for (j=0;j<128;j+=2) {
            error = ((div_errors[j]<<8) + (div_errors[j+1])) & 0x3fff;
            if (error)
                break;
        }
        if (error != 0) {
            //dbgpl(&dib8000_dbg, "errors : %d",div_errors[j]);
            uint16_t val = dib8000_read_word(state, 904);
            dib8000_write_word(state, 904, (val & 0xfcff) | 0x100);
            dib8000_write_word(state, 904, val);
            val = dib8000_read_word(state, 770) & 0xbfff;
            dib8000_write_word(state, 770, val| (1<<14));
            dib8000_write_word(state, 770, val);
            dbgp("dib 8000 reset\n");
            error = 0;
        }
    }
}

void dib8000_set_low_thres(struct dibFrontend* fe)
{
    struct dib8000_state *state = fe->demod_priv;
    state->saved_registers[0] = dib8000_read_word(state, 183);
    state->saved_registers[1] = dib8000_read_word(state, 182);
    state->saved_registers[2] = dib8000_read_word(state, 181);
    state->saved_registers[3] = dib8000_read_word(state, 180);
    state->saved_registers[4] = dib8000_read_word(state, 188);
    state->saved_registers[5] = dib8000_read_word(state, 9);
    dib8000_write_word(state, 183, 0); //p_coff_corthres_2K = 0
    dib8000_write_word(state, 182, 0); //p_coff_corthres_4K = 0
    dib8000_write_word(state, 181, 0); //p_coff_corthres_8K = 0
    dib8000_write_word(state, 180, 0x400); //default value exept p_coff_thres_lock = 0
    dib8000_write_word(state, 188, 0x200); //default value except lmod4_thres_lock = 0
    dib8000_write_word(state,   9, 0x14); //p_lock_div_mask = coff_lock + lmod4
    dib8000_write_word(state, 36, dib8000_read_word(state, 36) |1); //freeze pha shift
    dib8000_write_word(state, 31, dib8000_read_word(state, 31) |(1<<8)); //inh timf
}

void dib8000_reset_thres(struct dibFrontend* fe)
{
    struct dib8000_state *state = fe->demod_priv;
    dib8000_write_word(state, 183, state->saved_registers[0]); //previous value
    dib8000_write_word(state, 182, state->saved_registers[1]); //previous value
    dib8000_write_word(state, 181, state->saved_registers[2]); //previous value
    dib8000_write_word(state, 180, state->saved_registers[3]); //previous value
    dib8000_write_word(state, 188, state->saved_registers[4]); //previous value
    dib8000_write_word(state,   9, state->saved_registers[5]); //previous value
    dib8000_write_word(state, 36, dib8000_read_word(state, 36) & 0xfffe); //defreeze pha shift
    dib8000_write_word(state, 31, dib8000_read_word(state, 31) & 0xfeff); //deinh timf
}

void dib8000_tune_reset_fes(struct dibFrontend *fe[] , uint32_t num_fe)
{
    int i;
    if (num_fe > 0) {
        dbgp("Trying to reset %d\n",num_fe);
        dib8000_set_low_thres(fe[num_fe]);
        for (i=num_fe-1; i >= 0; i--) {
            if (fe[i]->input != NULL) {
                dbgp("fe%d\n",i);
                dib8000_reset_sync_pha(fe[i], 1000);
            }
        }
        dib8000_reset_thres(fe[num_fe]);
    }
}

static const struct dibDemodInfo dib8000_info = {
    "DiBcom 8000M", // name
    MODE_ISDBT | FE_CAN_FAST_TUNE,// caps
    32,              // pid_filter_count

    { // ops
    dib8000_reset,

    dib8000_wakeup,        // wakeup
    dib8000_sleep,         // sleep

    dib8000_agc_startup,   // agc_startup
    dib8000_tune,          // tune

    NULL,  // autosearch_start
    NULL, // autosearch_irq
    dib8000_get_channel,       // get_channel

    dib8000_set_diversity_in,      // set_diversity_in
    dib8000_demod_set_output_mode, // set_output_mode
    dib8000_pid_filter_ctrl,       // pid_filter_ctrl
    dib8000_pid_filter,            // pid_filter

    dib8000_set_wbd_ref,         // set_wdb_ref
    dib8000_get_wbd_ref,         // set_wdb_ref

    dib8000_set_gpio,            // set_gpio

    dib8000_get_signal_status,   // get_signal_status

    dib8000_ctrl_timf,           // ctrl_timf

#ifdef DIBCOM_GENERIC_MONITORING
    dib8000_generic_monitoring,   // get_monitoring
#else
    NULL,
#endif
    dib8000_release, //release
    },

{
	NULL,
	0,
	0,
	NULL,
	NULL,
	0,
	0,
	NULL,
	0,
	NULL,
	0,
	NULL,
	NULL,
	0,
},	
	0,
	0,
	0
};
/* wakeup function actually */

struct dibFrontend * dib8000_register(struct dibFrontend *fe, struct dibDataBusHost *i2c_adap, uint8_t i2c_addr, const struct dib8000_config *cfg)
{
    struct dib8000_state *st = MemAlloc(sizeof(struct dib8000_state));
    struct dibDataBusClient *client;
    if (st == NULL)
        return NULL;
    DibZeroMemory(st,sizeof(struct dib8000_state));
    memcpy(&st->cfg, cfg, sizeof(struct dib8000_config));

    st->fe = fe;
    frontend_register_demod(fe, &st->info, &dib8000_info, st);
    fe->release_compat_fe &= ~COMPONENT_LAYER_RELEASE;
    st->timf_default = st->cfg.pll->timf;
    st->diversity_onoff = 0;

    client = demod_get_data_bus_client(fe);

    switch (data_bus_host_type(i2c_adap)) {
        case DATA_BUS_I2C:
            data_bus_client_init(client, &dibx000_i2c_data_bus_client, i2c_adap);
            data_bus_client_set_speed(client, 200);
            break;
        case DATA_BUS_MMIO_SRAM_LIKE:
        case DATA_BUS_SDIO:
            data_bus_client_init(client, &dibx000_mmio_data_bus_client, i2c_adap);
            data_bus_client_set_speed(client, 0);
            break;
    }
	data_bus_client_set_device_id(client, i2c_addr);

    dibx000_init_i2c_master(&st->i2c_master, DIB8000, demod_get_data_bus_client(fe));

    return fe;
}

int dib8000_attach(struct dibDataBusHost *i2c_adap, int no_of_demods,
    uint8_t default_addr, uint8_t do_i2c_enum,
    const struct dib8000_config cfg[], struct dibDemod *demod[])
{
    int i,num=0;

    if (no_of_demods < 1)
        return DIB_RETURN_ERROR;

    /* preparing the structures */
    for (i = 0; i < no_of_demods ; i++) {
        demod[i] = MemAlloc(sizeof(struct dibFrontend));
        if (do_i2c_enum)
            demod[i] = dib8000_register(demod[i], i2c_adap, 0x80+2*i, &cfg[i]);
        else
            demod[i] = dib8000_register(demod[i], i2c_adap, default_addr, &cfg[i]);
        demod[i]->release_compat_fe |= COMPONENT_LAYER_RELEASE;
        num++;
        if (demod[i] == NULL)
            goto error;
    }

    if (do_i2c_enum) {
        if (dib8000_i2c_enumeration(i2c_adap,no_of_demods,default_addr,0x80) != DIB_RETURN_SUCCESS)
            goto error;
    } else {
        data_bus_client_set_device_id(demod_get_data_bus_client(demod[0]), default_addr);
        if (dib8000_identify(demod_get_data_bus_client(demod[0])) == 0)
            goto error;
    }

    // do basic resets and power down
    for (i = 0; i < no_of_demods; i++) {
        dib8000_reset(demod[i]);

    }

    return 0;

error:
    for (i = 0; i < num; i++) {
        MemFree(demod[i]->demod_priv,sizeof(struct dib8000_state));
        demod[i] = NULL;
    }

    return DIB_RETURN_FRONT_END_COM_ERROR;
}

const struct dibDebugObject dib8000_dbg = {
    DEBUG_DEMOD,
    "DiB8000"
};
