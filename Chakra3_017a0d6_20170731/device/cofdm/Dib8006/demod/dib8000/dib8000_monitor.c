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
#include "frontend.h"
#include "component_monitor.h"

#include "dib8000.h"
#include "dib8000_priv.h"
#include "msAPI_Timer.h"
static int dib8000_get_demod_monitor(struct dib8000_state *state, struct dibDemodMonitor *m)
{
    uint16_t val = 0,v;
    uint16_t i;

    val = dib8000_read_word(state, 568);
    m->locks.agc        = (val >> 14) & 1;
    m->locks.corm       = (val >> 13) & 1;
    m->locks.coff       = (val >> 12) & 1;
    m->locks.coff_cpil  = (val >> 11) & 1;
    m->locks.lmod4      = (val >> 10) & 1;
    m->locks.pha3       = (val >>  9) & 1;
    m->locks.equal      = (val >>  8) & 1;
    m->locks.fec_mpeg   = (val >> 7) & 1;
    m->locks.fec_mpeg_b = (val >> 6) & 1;
    m->locks.fec_mpeg_c = (val >> 5) & 1;
    m->locks.tmcc_dec   = (val >> 4) & 1;
    m->locks.tmcc_sync  = (val >> 3) & 1;
    m->locks.tmcc_data  = (val >> 1) & 1;
    m->locks.dvsy       = (val >>  0) & 1;

    m->locks.vit        = dib8000_read_word(state, 554) & 1;
    m->locks.vit_b      = dib8000_read_word(state, 555) & 1;
    m->locks.vit_c      = dib8000_read_word(state, 556) & 1;

    m->iq_misgain = dib8000_read_word(state, 396);
    m->iq_misphi = dib8000_read_word(state, 395);
    if (m->iq_misphi & 0x800)
        m->iq_misphi -= 0x1000;

    val = dib8000_read_word(state, 542);
    m->equal_noise_mant = (val >> 6) & 0xFF;
    m->equal_noise_exp = ((val & 0x3F));

    val = dib8000_read_word(state, 543);
    m->equal_signal_mant = (val >> 6) & 0xFF;
    m->equal_signal_exp  = (val & 0x3F);

    if ((m->equal_noise_exp & 0x20) != 0)
        m->equal_noise_exp -= 0x40;
    if ((m->equal_signal_exp & 0x20) != 0)
        m->equal_signal_exp -= 0x40;

    val = dib8000_read_word(state, 544);
    m->mer_mant = (val >> 6) & 0xFF;
    m->mer_exp = (val & 0x3F);
    if ((m->mer_exp & 0x20) == 0x20)
        m->mer_exp -= 0x40;

    if (state->revision < 0x8002)
    {
        m->can_display_ber_several_layers = 0;

        m->ber_raw          = dib8000_read32(state, 560);
        m->PacketErrors     = dib8000_read_word(state, 565);
    }
    else
    {
        m->can_display_ber_several_layers = 1;

        m->ber_raw_A        = dib8000_read32(state, 560);
        m->ber_raw_B        = dib8000_read32(state, 576);
        m->ber_raw_C        = dib8000_read32(state, 581);
        m->PacketErrors_A   = dib8000_read_word(state, 562);
        m->PacketErrors_B   = dib8000_read_word(state, 578);
        m->PacketErrors_C   = dib8000_read_word(state, 583);

        if (state->ber_monitored_layer == LAYER_C)
        {
            m->ber_raw      = m->ber_raw_C;
            m->PacketErrors = m->PacketErrors_C;
        }
        else if (state->ber_monitored_layer == LAYER_B)
        {
            m->ber_raw      = m->ber_raw_B;
            m->PacketErrors = m->PacketErrors_B;
        }
        else // layer A by default
        {
            m->ber_raw      = m->ber_raw_A;
            m->PacketErrors = m->PacketErrors_A;
        }
    }

    m->PacketErrorCount = dib8000_read_word(state, 567);
    m->isdbt_err_sec_layerA = dib8000_read_word(state, 551) != 0;
    m->isdbt_err_sec_layerB = dib8000_read_word(state, 552) != 0;
    m->isdbt_err_sec_layerC = dib8000_read_word(state, 553) != 0;

    // Timing offset read
    m->timing_offset = (dib8000_read32(state, 437) >> 1);
    if (m->timing_offset  & 0x20000000)
        m->timing_offset -= 0x40000000;

    m->timf_current = dib8000_read32(state, 435);
    if (state->cfg.pll)
        m->timf_default = state->cfg.pll->timf;
    else
        m->timf_default = 20776863;

    m->dds_freq = dib8000_read32(state, 433);
    if (m->dds_freq  & 0x2000000)
        m->dds_freq -= 0x4000000;

    val = dib8000_read_word(state, 26);
    m->invspec = val & 0x01;
    if (m->invspec > 0)
        m->dds_freq = (1 << 26) - m->dds_freq;

    m->p_dds_freq = dib8000_read32(state, 27) & 0x1ffffff;

    m->viterbi_syndrome = dib8000_read_word(state, 557);
    m->viterbi_syndrome_b = dib8000_read_word(state, 558);
    m->viterbi_syndrome_c = dib8000_read_word(state, 559);

    INIT_CHANNEL(&m->cur_digital_channel, STANDARD_ISDBT);
    m->cur_digital_channel.type = STANDARD_ISDBT;

    /* for the DiB8000A we need to read the config */
    switch ((dib8000_read_word(state, 0) >> 13) & 0x3) {
        case 1: m->cur_digital_channel.u.isdbt.nfft = FFT_2K; break;
        case 2: m->cur_digital_channel.u.isdbt.nfft = FFT_4K; break;
        default: m->cur_digital_channel.u.isdbt.nfft = FFT_8K; break;
    }
    m->cur_digital_channel.u.isdbt.guard = dib8000_read_word(state, 1) & 0x3;

    m->cur_digital_channel.u.isdbt.sb_mode = dib8000_read_word(state, 508) & 0x3;
    m->cur_digital_channel.u.isdbt.partial_reception = (dib8000_read_word(state, 505)) & 0x1;

    for (i = 0; i < 3; i++) {
        m->cur_digital_channel.u.isdbt.layer[i].nb_segments = dib8000_read_word(state, 493+i) & 0xF;
        m->cur_digital_channel.u.isdbt.layer[i].code_rate   = dib8000_read_word(state, 481+i) & 0x7;
        m->cur_digital_channel.u.isdbt.layer[i].time_intlv  = dib8000_read_word(state, 499+i) & 0x7;

        val = dib8000_read_word(state, 487+i) & 0x3;
        switch(val) {
        case 0: m->cur_digital_channel.u.isdbt.layer[i].constellation = QAM_DQPSK; break;
        case 1: m->cur_digital_channel.u.isdbt.layer[i].constellation = QAM_QPSK; break;
        case 2: m->cur_digital_channel.u.isdbt.layer[i].constellation = QAM_16QAM; break;
        case 3:
        default : m->cur_digital_channel.u.isdbt.layer[i].constellation = QAM_64QAM; break;
        }
    }

    //val = dib8000_read_word(state, 481);
    //m->cur_channel.intlv_native = (val >> 5) & 0x1;

    val = dib8000_read_word(state, 548);
    m->way0_ok = (val >> 1) & 1;
    m->way1_ok = (val     ) & 1;
    m->dvsy_delay = ((val >> 2) & 0x7ff) * 2;
    m->dvsy_first_arrived = (val >> 14) & 1;

    val = dib8000_read_word(state, 547);
    m->divin_fifo_overflow = val >> 14;
    m->divin_nberr_sym = val & 0x3fff;

    m->adc_power_i = dib8000_read32(state, 384) & 0xfffff;

    m->adc_monitor_only = 0;
    m->adc_power_q = dib8000_read32(state, 386) & 0xfffff;

    m->rf_power = dib8000_read_word(state, 390);

    m->agc1_raw = dib8000_read_word(state, 388);
    m->agc2_raw = dib8000_read_word(state, 389);
    m->agc_wbd_raw = dib8000_read_word(state, 393);
    m->agc_split = (uint8_t) dib8000_read_word(state, 392);

    m->internal_clk = dib8000_read32(state, 23) /1000;

    m->n_2dpa_monitoring = 1;

    val = dib8000_read_word(state, 536);
    m->n_2dpa_mu_int  = (val >> 3) & 0x7f;
    m->n_2dpa_num_fir = (val >> 0) & 0x07;

    for (v = 0; v < 4; v++) {
        uint32_t v32 = dib8000_read32(state, 459 + v*2);
        m->cti_def_raw[v] = v32 & 0xffff;
        if((v32 >> 16 )&0x1)
            m->cti_def_raw[v] -= (1 << 16);
    }

#if 0
#include <math.h>

    dib8000_write_word(state, 586, 1); // P_csic_rst_mnt_pilerr
    dib8000_write_word(state, 586, 0);


    FILE *f = fopen("/tmp/pil_err", "w");
    uint16_t pil[1870], b[4];

    data_bus_client_read_multi16_attr(demod_get_data_bus_client(state->fe), 588, DATA_BUS_ACCESS_MODE_NO_ADDRESS_INCREMENT, pil, 1870);

    for (i = 1; i < 1870 * 3 + 1; i++) {
        double mant, err, chan;
        int16_t e;

        fprintf(f, "%d ", i);
        dib8000_write_word(state, 587, i);

        while (!dib8000_read_word(state, 593)) // n_csic_mnt_chan2_rdy

            data_bus_client_read_multi16(demod_get_data_bus_client(state->fe), 589, b, 4);

#if 0
        mant = b[0]  / 256.0;
        e = b[1];
        if (e & 0x8)
            e -= 0x10;
        chan = 10*log10(mant * pow(2.0, e) / 256.0);
        fprintf(f, "%f ", -45.0 + chan );
#endif

        mant = b[2]  / 256.0;
        e = b[3];
        if (e & 0x8)
            e -= 0x10;
        chan = 10*log10(mant * pow(2.0, e) / 256.0);
        fprintf(f, "%f ", chan );

#if 1
        mant = (pil[i/3] & 0x7f) / 128.0;

        e =  (pil[i/3] >> 7);
        if (e & 0x10)
            e -= 0x20;

        err = 10*log10(mant * pow(2.0, e - 15));


        fprintf(f, "%f", err );
#endif
        fprintf(f, "\n");
    }
    fclose(f);
#endif

    /*
       dbgpl(&dib8000_dbg, "n_imp_cnt_burst  = %d", rd(406) );
       dbgpl(&dib8000_dbg, "n_imp_cnt_burst1 = %d", rd(407) );
       dbgpl(&dib8000_dbg, "n_imp_cnt_burst2 = %d", rd(408) );
       dbgpl(&dib8000_dbg, "n_imp_cnt_burst3 = %d", rd(409) );
       dbgpl(&dib8000_dbg, "P_imp:             %x", rd(137) );
       DibMSleep(200);
     */

#ifdef DIBCOM_EXTENDED_MONITORING
    demod_monitor_post_process(m);
#endif
    return DIB_RETURN_SUCCESS;
}

static void dib8000_set_ber_monitored_layer(struct dib8000_state *state, int layer)
{
    if (state->revision < 0x8002)
    {
        if (layer == state->ber_monitored_layer)
            return;
        switch (layer) {
        case LAYER_A: // layer A
            state->ber_monitored_layer = LAYER_A;
            state->layer_b_nb_seg = (dib8000_read_word(state, 3) & 0x3c0) >>6;
            state->layer_c_nb_seg = (dib8000_read_word(state, 4) & 0x3c0) >>6;
            dib8000_write_word(state, 3, dib8000_read_word(state, 3) & 0xfc3f); // P_Nseg_1 = 0
            dib8000_write_word(state, 4, dib8000_read_word(state, 4) & 0xfc3f); // P_Nseg_2 = 0
            //current_reg |= 0x60; // P_fec_ber_rs_len = 3
            break;
        case LAYER_B: // layer B
        case LAYER_C: // layer C
            dbgp("cannot ask ber for layer: %d\n", layer);
            return;
        case LAYER_ALL: // layer A+B+C
            state->ber_monitored_layer = LAYER_ALL;
            dib8000_write_word(state, 3, (dib8000_read_word(state, 3) & (0xfc3f)) | (state->layer_b_nb_seg << 6));
            dib8000_write_word(state, 4, (dib8000_read_word(state, 4) & (0xfc3f)) | (state->layer_c_nb_seg << 6));
        default: break;
        }
    }
    else
        state->ber_monitored_layer = layer;
}

static int dib8000_get_ber_monitored_layer(struct dib8000_state *state)
{
    if (state->revision < 0x8002)
    {
        switch (state->ber_monitored_layer) {
        case LAYER_A: return LAYER_A;
        case LAYER_ALL:
        default: return LAYER_ALL;
        }
    }

    return state->ber_monitored_layer;
}

static int dib8000_reset_pe_count(struct dib8000_state *st)
{
    uint8_t b[4], nb[4] = { 0, 0, 0, 1 };

    dib8000_read(st,  23,  b, 4);
    dib8000_write(st, 23, nb, 4);
    dib8000_write(st, 23,  b, 4);

    return 0;
}

static void dib8000_get_snr_discrete(struct dib8000_state *state, uint32_t *s, uint32_t *n)
{
    uint32_t t;
    int8_t exp1;

    /* SNR */
    t = dib8000_read_word(state, 542);
    *n = (t >> 6) & 0xff;
    exp1 = (uint8_t) (t & 0x3f);
    if (exp1 & 0x20)
        exp1 -= 0x40;
    *n <<= exp1 + 16;

    t = dib8000_read_word(state, 543);
    *s = (t >> 6) & 0xff;
    exp1 = (uint8_t) (t & 0x3f);
    if (exp1 & 0x20)
        exp1 -= 0x40;
    *s <<= exp1 + 16;

}

static uint32_t dib8000_get_snr(struct dib8000_state *state)
{
    uint32_t s,n;
    dib8000_get_snr_discrete(state, &s, &n);
    return uint32_finite_div(s, n, 16);
}

#ifdef DIBCOM_EXTENDED_MONITORING
int dib8000_get_spectrum_powmean(struct dibFrontend *fe, uint8_t *buf)
{
    struct dib8000_state *state = fe->demod_priv;
    uint32_t cur_timf, original_timf, original_dds, powmean;
    uint16_t restart, res_khz, buf16[2];
    int16_t dds_offset_khz;

    uint16_t iqc = dib8000_read_word(state, 40);
    uint16_t pha = dib8000_read_word(state, 36);
    uint16_t pana =dib8000_read_word(state, 116);

    uint8_t iq_path;

    /* get original timf */
    original_timf = dib8000_get_timf(fe);
    /* get original dds */
    data_bus_client_read_multi16(demod_get_data_bus_client(state->fe), 27, buf16, 2);
    original_dds  = (buf16[0] << 16) | buf16[1];

    /* get buf instruction */
    res_khz = (buf[3] << 8) | buf[4];
    dds_offset_khz = (buf[0] << 8) | buf[1];

    iq_path = buf[2];

    /* compute timf Vs requested resolution KHz */
    cur_timf = (original_timf / (fe->current_bw)) * res_khz;

    dib8000_set_timf(fe, cur_timf);

    /* compute dds */
    dib8000_set_dds(state, dds_offset_khz);

    /*select IQ path */
    switch (iq_path) {
        case 0:
            dib8000_write_word(state, 38, (1<<14)|(1<<13)|(3<<11)|1024);
            break;
        case 1:
            dib8000_write_word(state, 38, (1<<14)|(0<<13)|(3<<11)|1024);
            break;
        case 2:
            dib8000_write_word(state, 38, (0<<14)|(1<<13)|(3<<11)|1024);
            break;
    }

    /* freeze IQ corr */
    dib8000_write_word(state, 40, iqc | (3 << 11)); /* Discard the IqC block */
    dib8000_write_word(state, 36, pha | 1);
    dib8000_write_word(state, 116, 2); /* p_ana_gain = 2*/

    /* start measurement */
    /* restart palf */
    restart = dib8000_read_word(state, 770);
    dib8000_write_word(state, 770, restart | (1<<7));
    dib8000_write_word(state, 770, restart);
    DibMSleep(78125 / res_khz * 0.2);

    /* get powmean */
    data_bus_client_read_multi16(demod_get_data_bus_client(state->fe), 418, buf16, 2);
    powmean =  (( buf16[0] << 16) | buf16[1]);

    /* set back original params */
    dib8000_write_word(state, 40, iqc);
    dib8000_write_word(state, 36, pha);
    dib8000_write_word(state, 116, pana);

    /* set back original timf */
    dib8000_set_timf(fe, original_timf);
    /* set back original dds */
    dib8000_write_word(state, 27, (original_dds >> 16) & 0x3ff);
    dib8000_write_word(state, 28, (original_dds & 0xffff));

    return powmean;

}


#include <math.h>
static int dib8000_get_channel_profile(struct dib8000_state *state, struct dibDemodChannelProfile *profile)
{
    int i;
    uint8_t b[4];
    int16_t re[128], im[128];

    profile->pha_shift = dib8000_read_word(state, 426) & 0x1fff;

    // adp_freeze, rst_monit, select_fir
    dib8000_write_word(state, 221, (1 << 3));
    dib8000_write_word(state, 221, (1 << 3) | (1 << 2) | (2 << 0));
    dib8000_write_word(state, 221, (1 << 3) | (0 << 2) | (2 << 0));

    for (i = 0; i < 128; i++) {
        dib8000_read(state, 528, b, 4);
        re[i] = (b[0] << 8) | b[1];
        im[i] = (b[2] << 8) | b[3];
        if (b[0] & 0x40)
            re[i] -= 0x8000;
        if (b[2] & 0x40)
            im[i] -= 0x8000;
    }

    dib8000_write_word(state, 221, 0);

    demod_channel_profile_calc(re,im,profile);
    return DIB_RETURN_SUCCESS;
}
#endif
int dib8000_generic_monitoring(struct dibFrontend *fe, uint32_t cmd, uint8_t *b, uint32_t size, uint32_t offset)
{	
	size = size;
    struct dib8000_state *state = fe->demod_priv;
    int ret = DIB_RETURN_NOT_SUPPORTED;
	void* d;
	d = (void*)b;
    switch (cmd & ~GENERIC_MONIT_REQUEST_SIZE) {
        case GENERIC_MONIT_COMPAT_EXTENDED:
            ret = sizeof(struct dibDemodMonitor);
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
                dib8000_get_demod_monitor(state, (struct dibDemodMonitor *) d);
            break;

        case GENERIC_MONIT_RESET_PE_COUNT:
            ret = 0;
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
                dib8000_reset_pe_count(state);
            break;
 
#ifdef DIBCOM_EXTENDED_MONITORING
        case GENERIC_MONIT_COMPAT_PROFILE:
            ret = sizeof(struct dibDemodChannelProfile);
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
                dib8000_get_channel_profile(state, (struct dibDemodChannelProfile *) d);
            break;
#endif
        case GENERIC_MONIT_SNR_DISCRETE:
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE)) {
                uint32_t s,n;
                dib8000_get_snr_discrete(state, &s, &n);
                b[0] = (uint8_t) (s >> 24);
                b[1] = (uint8_t) (s >> 16);
                b[2] = (uint8_t) (s >>  8);
                b[3] = (uint8_t) (s      );
                b[4] = (uint8_t) (n >> 24);
                b[5] = (uint8_t) (n >> 16);
                b[6] = (uint8_t) (n >>  8);
                b[7] = (uint8_t) (n      );
            }
            ret = 8;
            break;

        case GENERIC_MONIT_SNR:
        case GENERIC_MONIT_SNR_COMBINED:
            ret = 4;

            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE)) {
                uint32_t snr = dib8000_get_snr(state);

				printf("GENERIC_MONIT_SNR: %d \n",snr);
                if (cmd == GENERIC_MONIT_SNR_COMBINED && fe->input != NULL) {
                    uint8_t i[4] = { 0 };
                    frontend_generic_monitoring(fe->input, GENERIC_MONIT_SNR_COMBINED, i, 4, 0);
                    snr += (i[0] << 24) | (i[1] << 16) | (i[2] << 8) | i[3];
                }

                b[0] = (uint8_t) (snr >> 24);
                b[1] = (uint8_t) (snr >> 16);
                b[2] = (uint8_t) (snr >>  8);
                b[3] = (uint8_t) (snr      );
            }
            break;

        case GENERIC_MONIT_SET_BER_LAYER:
            ret = 0;
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
                dib8000_set_ber_monitored_layer(state, offset);
            break;

        case GENERIC_MONIT_BER_LAYER:
            ret = 0;
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
                ret = dib8000_get_ber_monitored_layer(state);
            break;

        case GENERIC_MONIT_SET_BER_RS_LEN:
            ret = 0;
            if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
                ret = dib8000_write_word(state, 285, (dib8000_read_word(state, 285) & ~0x60) | ((uint16_t) ((offset&0x3) << 5)) );
            break;

#ifdef DIBCOM_EXTENDED_MONITORING
    case GENERIC_MONIT_GET_SPECTRUM_POWMEAN:
        ret = 0;
        if(!(cmd & GENERIC_MONIT_REQUEST_SIZE))
            ret = dib8000_get_spectrum_powmean(fe, b);
        break;
#endif
    default:
    break;
    }
    return ret;
}
//#endif

//#ifdef DIBCOM_GENERIC_MONITORING

#if 0
double dump_cti_carrier(struct dibFrontend *demod, int selected_carrier, int average_nb)
{
    struct dib8000_state *state = demod->demod_priv;
    int i;
    uint32_t r;
    int16_t re_, im_;
    double power = 0;


    for (i = 0; i < average_nb; i++) {
        dib8000_write_word(state, 212, selected_carrier);

        r   = dib8000_read32(state, 456);
        re_ = (uint16_t) ((r >> 10) & 0x3ff);
        im_ = (uint16_t) ((r      ) & 0x3ff);

        if (re_ & 0x200)
            re_ -= 0x400;
        if (im_ & 0x200)
            im_ -= 0x400;

        power += pow(re_ / (double) 0x200, 2) + pow(im_ / (double) 0x200, 2);
    }
    power /= (double) average_nb;
    power = 10*log10(power + 1e-10);

    return power;
}
#endif

