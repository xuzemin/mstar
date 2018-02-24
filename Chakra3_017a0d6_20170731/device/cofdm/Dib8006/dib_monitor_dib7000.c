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
#include "component_monitor.h"

#define val_(name) //{ printf("%-30s",name); }




void dump_dvb_channel(struct dibDVBChannel *cd)
{
	switch (cd->nfft) {
		case 1:  printf("8K   "); break;
		case 2:  printf("4K   "); break;
		case 0:  printf("2K   "); break;
		default: printf("UNK  "); break;
	}

	printf("1/%-2i  ", 32 / (1 << cd->guard));

	switch (cd->nqam) {
		case 0:  printf("QPSK  "); break;
		case 1:  printf("16QAM "); break;
		case 2:  printf("64QAM "); break;
		default: printf("UNK   "); break;
	}

	printf("%i    ", cd->vit_hrch);
	printf("%i    ", cd->vit_alpha);
	printf("%i/%i ", cd->vit_code_rate_hp, cd->vit_code_rate_hp + 1);
	printf("%i/%i ", cd->vit_code_rate_lp, cd->vit_code_rate_lp + 1);
	printf("%s"    , cd->intlv_native ? "NATIVE" : "EXTENDED");
}
#ifdef CONFIG_STANDARD_DVBT
void dump_dvb_digital_channel(struct dibChannel *cd)
{
	switch (cd->u.dvbt.nfft) {
		case 1:  printf("8K   "); break;
		case 2:  printf("4K   "); break;
		case 0:  printf("2K   "); break;
		default: printf("UNK  "); break;
	}

	printf("1/%-2i  ", 32 / (1 << cd->u.dvbt.guard));

	switch (cd->u.dvbt.constellation) {
		case 0:  printf("QPSK  "); break;
		case 1:  printf("16QAM "); break;
		case 2:  printf("64QAM "); break;
		default: printf("UNK   "); break;
	}

	printf("%i    ", cd->u.dvbt.hrch);
	printf("%i    ", cd->u.dvbt.alpha);
	printf("%i/%i ", cd->u.dvbt.code_rate_hp, cd->u.dvbt.code_rate_hp + 1);
	printf("%i/%i ", cd->u.dvbt.code_rate_lp, cd->u.dvbt.code_rate_lp + 1);
	printf("%s"    , cd->u.dvbt.intlv_native ? "NATIVE" : "EXTENDED");
}

void dump_dvbsh_digital_channel(struct dibChannel *cd)
{
	switch (cd->u.dvbsh.dvb_common.nfft) {
		case 1:  printf("8K   "); break;
		case 2:  printf("4K   "); break;
		case 0:  printf("2K   "); break;
		case 3:  printf("1K   "); break;
		default: printf("UNK  "); break;
	}

	printf("1/%-2i  ", 32 / (1 << cd->u.dvbsh.dvb_common.guard));

	switch (cd->u.dvbsh.dvb_common.constellation) {
		case 0:  printf("QPSK  "); break;
		case 1:  printf("16QAM "); break;
		default: printf("UNK   "); break;
	}

	printf("%i    ", cd->u.dvbsh.dvb_common.hrch);
	printf("%i    ", cd->u.dvbsh.dvb_common.alpha);

    printf(" %s   ", DVBSH_CODERATE_TO_STRING(cd->u.dvbsh.dvb_common.code_rate_hp));
    printf("%s"    , DVBSH_CODERATE_TO_STRING(cd->u.dvbsh.dvb_common.code_rate_lp));

}
#endif

#ifdef CONFIG_STANDARD_ISDBT
void dump_isdbt_channel(struct dibChannel *cd)
{
    uint8_t i;

    switch (cd->u.isdbt.nfft) {
		case 1:  printf("8K     "); break;
		case 2:  printf("4K     "); break;
		case 0:  printf("2K     "); break;
		default: printf("UNK    "); break;
	}

	printf("1/%-2d      ", 32 / (1 << cd->u.isdbt.guard));
    printf("%d       ", cd->u.isdbt.sb_mode);
    printf("%d       ", cd->u.isdbt.partial_reception);
	for (i = 0; i<3; i++)
    {
        printf("%.2d    ", cd->u.isdbt.layer[i].nb_segments);

        switch (cd->u.isdbt.layer[i].constellation) {
		    case 0:  printf("QPSK   "); break;
		    case 1:  printf("16QAM  "); break;
		    case 2:  printf("64QAM  "); break;
            case 3 : printf("DQPSK  "); break;
		    default: printf("UNK    "); break;
        }
        printf("%d/%d    ", cd->u.isdbt.layer[i].code_rate, cd->u.isdbt.layer[i].code_rate + 1);
        printf("%d         ", cd->u.isdbt.layer[i].time_intlv);
	}
}
#endif

int channel_decoder_have_standard(struct dibChannelDecoderMonitor m[], int num, int st)
{
    do {
        num--;
        if (m[num].type == st)
            return 1;
    } while (num);
    return 0;
}

void channel_decoder_print_monitor(struct dibChannelDecoderMonitor m[], int num)
{
    int k=0;

    if (channel_decoder_have_standard(m, num, STANDARD_DVBSH)) {
        printf("\nSH info :          SH dem lock  per            iter        CRC header ok  tc_punct_id   Select_hp     nFFT    nqam     dvb_sh \n");
        printf("                   | SH lock    |       PS     |  overflow | pha_sh_frame |  pading_err | common_mult | hrch  | mux    |\n");
        for (k = 0; k < num; k++) {
            if (m[k].type == STANDARD_DVBSH)
                printf("Turbo decoder %d :  %d %d       %7.5f   %-5d  %-2d %d        %d %d            %-2d %-2d         %d %d           %d %d     %d 0x%04x %d\n", k, m[k].u.sh.misc, m[k].u.sh.sh_lock, m[k].u.sh.sh_per, m[k].u.sh.sh_PS, m[k].u.sh.sh_nb_iter, m[k].u.sh.sh_overflow, m[k].u.sh.sh_crc_header_ok, m[k].u.sh.sh_pha_sh_frame, m[k].u.sh.sh_tc_punct_id, m[k].u.sh.sh_padding_err, m[k].u.sh.sh_select_hp, m[k].u.sh.sh_common_mult , m[k].u.sh.sh_nfft , m[k].u.sh.sh_hrch,  m[k].u.sh.sh_Nqam, m[k].u.sh.mux, m[k].u.sh.dvb_sh);
        }
    }

    if (channel_decoder_have_standard(m, num, STANDARD_CMMB)) {
        printf("\nCMMB info :         slot num       per       iter/iter max     syndrome_first_iter    overflow_count   bloc_error      error flag     RS table count  RS table error count      RS per\n");
        for (k = 0; k < num; k++) {
            if (m[k].type == STANDARD_CMMB)
                printf("CMMB decoder %d :       %2d        %7.5f       %2d/%2d                     %d               %5d              %d                %d           %d                   %d               %f\n", k, m[k].u.cmmb.sl_num, m[k].u.cmmb.per, m[k].u.cmmb.nb_iteration, m[k].u.cmmb.nb_max_iteration, m[k].u.cmmb.syndrome_first_iter, m[k].u.cmmb.overflow_cnt, m[k].u.cmmb.bloc_error, m[k].u.cmmb.err_flag, m[k].u.cmmb.rs_table_count, m[k].u.cmmb.rs_table_error_count,  m[k].u.cmmb.rs_table_count ? (double)m[k].u.cmmb.rs_table_error_count / (double)m[k].u.cmmb.rs_table_count : 0);
        }
    }

    if (channel_decoder_have_standard(m, num, STANDARD_DVBT)) {
        printf("\n");
        printf("\n");
        val_("Viterbi syndrome");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.dvbt.viterbi_syndrome);
        printf("\n");
        
        val_("packet error count");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.dvbt.PacketErrors);
        printf("\n");

        val_("packet error cumul");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.dvbt.PacketErrorCount);
        printf("\n");

        val_("Bit Error Rate");
        for (k = 0; k < num; k++)
             printf("%-15g", m[k].u.dvbt.ber);
        printf("\n");

        val_("Quasi Error Free");
        for (k = 0; k < num; k++)
            printf("%-15s", m[k].u.dvbt.ber < 2e-4 && m[k].u.dvbt.PacketErrors == 0 ? "OK" : "*** NOT OK ***");
        printf("\n");
                
        printf("\nchannel decoder locks:     fec_frm \n");
        printf("                       vit | fec_mpeg\n");
        for (k = 0; k < num; k++) {
            printf("channel decoder %2d:     %d  %d  %d\n",k,
                    m[k].u.dvbt.locks.vit, m[k].u.dvbt.locks.fec_frm, m[k].u.dvbt.locks.fec_mpeg/*, m[k].u.dvbt.viterbi_syndrome, m[k].u.dvbt.PacketErrors, m[k].u.dvbt.PacketErrorCount, m[k].u.dvbt.ber*/);
            printf("\n");
        }
    }

    if (channel_decoder_have_standard(m, num, STANDARD_ISDBT)) {
        printf("\n");
        printf("\n");
        val_("Viterbi syndrome layer a");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.isdbt.viterbi_syndrome);
        printf("\n");
        val_("Viterbi syndrome layer b");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.isdbt.viterbi_syndrome_b);
        printf("\n");
        val_("Viterbi syndrome layer c");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.isdbt.viterbi_syndrome_c);
        printf("\n");

        val_("packet error count A");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.isdbt.PacketErrors_A);
        printf("\n");
        val_("packet error count B");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.isdbt.PacketErrors_B);
        printf("\n");
        val_("packet error count C");
        for (k = 0; k < num; k++)
            printf("%-15i", m[k].u.isdbt.PacketErrors_C);
        printf("\n");


        val_("packet error cumul");
        for (k = 0; k < num; k++)
        printf("%-15i", m[k].u.isdbt.PacketErrorCount);
        printf("\n");

        val_("Bit Error Rate A");
        for (k = 0; k < num; k++)
            printf("%-15g", m[k].u.isdbt.berA);
        printf("\n");
        val_("Bit Error Rate B");
        for (k = 0; k < num; k++)
            printf("%-15g", m[k].u.isdbt.berB);
        printf("\n");
        val_("Bit Error Rate C");
        for (k = 0; k < num; k++)
            printf("%-15g", m[k].u.isdbt.berC);
        printf("\n");

        /*val_("Quasi Error Free");
        for (k = 0; k < num; k++)
            printf("%-15s", m[k].u.isdbt.ber < 2e-4 && m[k].u.isdbt.PacketErrors == 0 ? "OK" : "*** NOT OK ***");
        printf("\n");*/
        
        printf("\nchannel decoder locks:            fec_mpeg(a b c) \n");
        printf("                       vit(a b c) | \n");
        for (k = 0; k < num; k++) {
            printf("channel decoder %2d:    %d %d %d       %d %d %d\n",k,
                    m[k].u.dvbt.locks.vit, m[k].u.isdbt.locks.vit_b, m[k].u.isdbt.locks.vit_c, m[k].u.isdbt.locks.fec_mpeg, m[k].u.isdbt.locks.fec_mpeg_b, m[k].u.isdbt.locks.fec_mpeg_c);
            printf("\n");
        }
    }

    if (channel_decoder_have_standard(m, num, STANDARD_DAB)) {

        printf("Viterbi syndrome : GLOBAL | FIC | MSC | SubId -> syndrome | ber \n");
               
        for (k = 0; k < num; k++) {
            if (m[k].type == STANDARD_DAB) {
                printf("                   %4d   %4d  %4d    %2d    -> %4d       %d\n", m[k].u.dab.syn,m[k].u.dab.syn_fic,m[k].u.dab.syn_msc, m[k].u.dab.subc_id, m[k].u.dab.syn_subc, m[k].u.dab.ber );
            }
        }
        printf("\nSubcId | Start addr | Size | Prev addr | Prev Size | Form | Table Index | L1punct | L2 punct |  PI1  |  PI2  | I  \n");

        for (k = 0; k < num; k++) {
            if (m[k].type == STANDARD_DAB) {
                printf("    %2d | %3d        | %3d  | %3d       | %3d       | %1d    | %2d          | %5d   |    %4d  |%4d   |%4d   | %4d  \n", m[k].u.dab.subc_id, m[k].u.dab.subc_staddr, m[k].u.dab.subc_sz, m[k].u.dab.subc_staddr_prev, m[k].u.dab.subc_sz_prev, m[k].u.dab.subc_form, m[k].u.dab.subc_index, m[k].u.dab.subc_L1punct, m[k].u.dab.subc_L2punct, m[k].u.dab.subc_PI1, m[k].u.dab.subc_PI2, m[k].u.dab.subc_I);
            }
        }
        printf("\n");
        printf("MPEG_lock     DMB_Lock_frm  Fec_Lock_frm     TimeDtlv_overflow  IsMSC          Recfg      Fec_mpfail\n");  
        printf("| Fec_BER_RS  | Fec_mpcor   | Fec_ber_rscnt  | cif_counter      | Fec_rsnperr  | subc new | Fec_mpfail_cnt\n");

           
        for (k = 0; k < num; k++) {
            if (m[k].type == STANDARD_DAB) {
                printf("%1d %7d     %1d %2d          %1d %3d            %1d %3d              %1d %7d      %1d %1d        %1d %7d\n", m[k].u.dab.fec_lock_mpeg, m[k].u.dab.fec_ber_rs, m[k].u.dab.dmb_lock_frm, m[k].u.dab.fec_mpcor, m[k].u.dab.fec_lock_frm, m[k].u.dab.fec_ber_rscnt, m[k].u.dab.TimeDtlv_overflow, m[k].u.dab.cifcounter, m[k].u.dab.isMSC,  m[k].u.dab.fec_ber_rsnperr, m[k].u.dab.recfg, m[k].u.dab.subc_new, m[k].u.dab.fec_mpfail, m[k].u.dab.fec_mpfail_cnt);
            }
        }
    }
}

/*void mac_print_monitor(struct dibMacMonitor m_mac[], struct dibDemodMonitor m_demod[], int num)
{
    int k;

        printf("\nMAC info :  ADsample lock\n");
        printf("            | \n");
        for (k = 0; k < num; k++) {
            printf("Mac %d :     %d\n", k, m_mac[k].ad_sample_lock);
        }
}*/ //20100902

int demods_have_standard(struct dibDemodMonitor m[], int num, int st)
{
    do {
        num--;
        if (m[num].cur_digital_channel.type == st)
            return 1;
    } while (num);
    return 0;
}



void dib7000_print_monitor(struct dibDemodMonitor m[], struct dibDemodStatistic s[], int stat_count, int num)
{
	int k,i;

	if(!demods_have_standard(m, num, STANDARD_DAB)) {
		val_("I adc power dBVrms");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].I_adc_power*65536));
		printf("\n");
				
		val_("Q adc power dBVrms");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].Q_adc_power*65536));
		printf("\n");
	}

	val_("DC offset on I");
	for (k = 0; k < num; k++)
		printf("%-15d  (*2^16)", (int)(m[k].iqc_dcoff_i*65536));
	printf("\n");

	val_("DC offset on Q");
	for (k = 0; k < num; k++)
	printf("%-15d  (*2^16)", (int)(m[k].iqc_dcoff_q*65536));
	printf("\n");

	val_("IQ gain mismatch (dB)");
	for (k = 0; k < num; k++)
		printf("%-15d  (*2^16)", (int)(m[k].iq_gain_mismatch*65536));
	printf("\n");

	val_("IQ phase mismatch (degree)");
	for (k = 0; k < num; k++)
		printf("%-15d  (*2^16)", (int)(m[k].iq_phase_mismatch*65536));
	printf("\n");

	if (m[0].n_adc_mode <= 1 && !m[0].adc_monitor_only) {
		val_("rf power dBm");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].rf_power_dbm*65536));
		printf("\n");

		val_("WBD:");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].agc_wbd*65536));
		printf("\n");

		val_("AGCglobal (norm)");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)m[k].rf_power);
		printf("\n");

		val_("AGC1 (norm)");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].agc1*65536));
		printf("\n");

		val_("AGC2 (norm)");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].agc2*65536));
		printf("\n");
		val_("AGC Split");
		for (k = 0; k < num; k++)
			printf("%-15d", m[k].agc_split);
		printf("\n");

		printf("\n");
	}
#ifdef CONFIG_STANDARD_DAB
	if(demods_have_standard(m, num, STANDARD_DAB)) {
		val_("AGC power");
		for (k = 0; k < num; k++)
			printf("%-15.2f", m[k].agc_db);
		printf("\n");

		val_("Power estimation dB");
		printf("%-15.2g", m[0].equal_signal_dB);
		printf("\n");

		val_("Demod clock Hz");
		for (k = 0; k < num; k++)
			printf("%d", m[k].internal_clk);
		printf("\n");
	}
		if (demods_have_standard(m, num, STANDARD_DAB)) {
			val_("small/large freq offset");
			for (k = 0; k < num; k++)
				printf(" %-4.3g | %3d", m[k].dab.small_freqoff,m[k].dab.large_freqoff);
			printf("\n");
		}
#endif
		val_("Carrier offset in Khz");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^8)", (int)(m[k].carrier_offset*256));
		printf("\n");

	if (m[0].adc_monitor_only) {
		val_("ADC LNPower");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].adc_lnpower*65536));
		printf("\n");
	}

	if (m[0].n_adc_mode == 0) {
		val_("Timing offset in ppm");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].timing_offset_ppm*65536));
		printf("\n");

#ifdef CONFIG_STANDARD_ISDBT
		if (demods_have_standard(m, num, STANDARD_ISDBT)) {
			if (!m[0].do_not_display_chandec) {
				val_("Viterbi syndrome layer a");
				for (k = 0; k < num; k++)
					printf("%-15d", m[k].viterbi_syndrome);
				printf("\n");
				val_("Viterbi syndrome layer b");
				for (k = 0; k < num; k++)
					printf("%-15d", m[k].viterbi_syndrome_b);
				printf("\n");
				val_("Viterbi syndrome layer c");
				for (k = 0; k < num; k++)
					printf("%-15d", m[k].viterbi_syndrome_c);
				printf("\n");
			}

		}
#endif
#ifdef CONFIG_STANDARD_DVBT
		if (demods_have_standard(m, num, STANDARD_DVBT)) {
			if (!m[0].do_not_display_chandec) {
				val_("Viterbi syndrome");
				for (k = 0; k < num; k++)
					printf("%-15i", m[k].viterbi_syndrome);
				printf("\n");
			}
		}
#endif
#ifdef CONFIG_STANDARD_DAB
		if (demods_have_standard(m, num, STANDARD_DAB)) {
			if (!m[0].do_not_display_chandec) {
				val_("\nTransmission Mode : ");
				switch (m[0].dab.tmode) {
					case 0 : val_("I"); break;
					case 1 : val_("II"); break;
					case 2 : val_("III"); break;
					case 3 : val_("IV"); break;
				}
				printf("\n");

				val_("Viterbi syndrome GLOBAL | FIC | MSC : ");
				printf("  %d | %d | %d ", m[0].dab.syn,m[0].dab.syn_fic,m[0].dab.syn_msc);
				printf("\n");

				val_("Viterbi syndrome SubId");
				for (k = 0; k < num; k++)
					printf("%d syndrome = %d", m[0].dab.syn_subid, m[0].dab.syn_subc);
				printf("\n");
			}
		}
#endif
		val_("C/N (dB)");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)", (int)(m[k].CoN*65536));
		printf("\n");

		if ( demods_have_standard(m, num, STANDARD_DVBT) || demods_have_standard(m, num, STANDARD_ISDBT) || demods_have_standard(m, num, STANDARD_DAB) ) {

#ifdef CONFIG_STANDARD_ISDBT
			if ((demods_have_standard(m, num, STANDARD_ISDBT)) && (m[0].can_display_ber_several_layers == 1))
			{
				if (!m[0].do_not_display_chandec) {
					val_("packet error count A");
					for (k = 0; k < num; k++)
						printf("%-15d", m[k].PacketErrors_A);
					printf("\n");
					val_("packet error count B");
					for (k = 0; k < num; k++)
						printf("%-15d", m[k].PacketErrors_B);
					printf("\n");
					val_("packet error count C");
					for (k = 0; k < num; k++)
						printf("%-15d", m[k].PacketErrors_C);
					printf("\n");
				}
			}
			else
#endif
			if (!m[0].do_not_display_chandec) {

				val_("packet error count");
				for (k = 0; k < num; k++)
					printf("%-15d", m[k].PacketErrors);
				printf("\n");
			}

			if (!(demods_have_standard(m, num, STANDARD_ISDBT)) || (m[0].can_display_ber_several_layers != 1))
			{
				if (!m[0].do_not_display_chandec) {
					val_("packet error cumul");
					for (k = 0; k < num; k++)
					printf("%-15d", m[k].PacketErrorCount);
					printf("\n");
				}
			}

#ifdef CONFIG_STANDARD_ISDBT
			if ((demods_have_standard(m, num, STANDARD_ISDBT)) && (m[0].can_display_ber_several_layers == 1) && (!m[0].do_not_display_chandec))
			{
				val_("Bit Error Rate A");
				for (k = 0; k < num; k++)
					printf("%-15d (*2^16)", (int)(m[k].berA*65536));
				printf("\n");
				val_("Bit Error Rate B");
				for (k = 0; k < num; k++)
					printf("%-15d (*2^16)", (int)(m[k].berB*65536));
				printf("\n");
				val_("Bit Error Rate C");
				for (k = 0; k < num; k++)
					printf("%-15d (*2^16)", (int)(m[k].berC*65536));
				printf("\n");
			}
			else
#endif
			if (!m[0].do_not_display_chandec) {

				val_("Bit Error Rate");
				for (k = 0; k < num; k++)
					printf("%-15d  (*2^16)", (int)(m[k].ber*65536));
				printf("\n");
			}
		}

		if ( (demods_have_standard(m, num, STANDARD_DVBT)) || (demods_have_standard(m, num, STANDARD_ISDBT))) {
			if (!m[0].do_not_display_chandec) {
				val_("MER");
				for (k = 0; k < num; k++)
					printf("%-15d  (*2^8)", (int)(m[k].mer*256));
				printf("\n");

				val_("Quasi Error Free");
				for (k = 0; k < num; k++)
					printf("%-15s", m[k].ber < 2e-4 && m[k].PacketErrors == 0 ? "OK" : "*** NOT OK ***");
				printf("\n");
			}
		} else if (demods_have_standard(m, num, STANDARD_DAB)) {
			val_("Quasi Error Free : ber<1e-4");
			printf("%-15s", m[0].ber < 1e-4 && m[0].PacketErrors == 0 ? "OK" : "*** NOT OK ***");
			printf("\n");
		}
#ifdef CONFIG_STANDARD_ISDBT
			if (demods_have_standard(m, num, STANDARD_ISDBT)) {
				printf("											|			 layer a		  | 		  layer b			|		   layer c			  | \n");
				printf("demod channel: nfft  guard	sb_mode  p_rcpt   nb_seg  modu	crate t_intlv	nb_seg	modu  crate t_intlv   nb_seg  modu	crate t_intlv\n");
				for (k=0; k < num; k++) {
					printf("demod %2d	  : ",k);
					dump_isdbt_channel(&m[k].cur_digital_channel);
					printf("\n");
				}
			}
#endif
#ifdef CONFIG_STANDARD_DVBT
			if (demods_have_standard(m, num, STANDARD_DVBT)) {
				printf("demod channel: nfft guard nqam	hrch alpha crhp crlp intlv\n");
				for (k=0; k < num; k++) {
					printf("demod %2d:		",k);
					dump_dvb_digital_channel(&m[k].cur_digital_channel);
					printf("\n");
				}
			} else if (demods_have_standard(m, num, STANDARD_DVBSH)) {
				printf("demod channel: nfft guard nqam	hrch alpha crhp 	 crlp\n");
				for (k=0; k < num; k++) {
					printf("demod %2d:		",k);
					dump_dvbsh_digital_channel(&m[k].cur_digital_channel);
					printf("\n");
				}
			}
#endif
		printf("\n");
#ifdef CONFIG_STANDARD_ISDBT
		if (demods_have_standard(m, num, STANDARD_ISDBT)) {
			if (!m[0].do_not_display_chandec) {
				printf("demod locks:  agc	 coff		 lmod4	equal	   tmcc_sync   dvsy\n");
				printf("			  | corm | coff_cpil | pha3 | tmcc_dec | tmcc_data |  vit(a,b,c)  fec_mpeg(a,b,c) \n");
				for (k = 0; k < num; k++)
					printf("demod %2d:	   %d %d	%d %d		  %d %d    %d %d		%d %d		  %d  %d%d%d		 %d%d%d\n",k,
							m[k].locks.agc, m[k].locks.corm, m[k].locks.coff, m[k].locks.coff_cpil, m[k].locks.lmod4, m[k].locks.pha3, m[k].locks.equal,m[k].locks.tmcc_dec, m[k].locks.tmcc_sync, m[k].locks.tmcc_data, m[k].locks.dvsy, m[k].locks.vit, m[k].locks.vit_b,m[k].locks.vit_c, m[k].locks.fec_mpeg,m[k].locks.fec_mpeg_b,m[k].locks.fec_mpeg_c);
				printf("\n");
			}
		}
#endif
#ifdef CONFIG_STANDARD_DVBT
		if (demods_have_standard(m, num, STANDARD_DVBT)) {
			for (k = 0; k < num; k++) {
				if (!m[k].do_not_display_chandec) {
					printf("demod locks:  agc	 coff		 lmod4	equal fec_frm	 tps_dec	tps_data	 dvsy\n");
					printf("			  | corm | coff_cpil | pha3 | vit | fec_mpeg | tps_sync | tps_cellid |\n");
					break;
				}
			}
			for (k = 0; k < num; k++) {
				if (!m[k].do_not_display_chandec) {
					printf("demod %2d:	   %d %d	%d %d		  %d %d    %d %d   %d %d		%d %d		 %d %d			%d\n",k,
							m[k].locks.agc, m[k].locks.corm, m[k].locks.coff, m[k].locks.coff_cpil, m[k].locks.lmod4, m[k].locks.pha3, m[k].locks.equal, m[k].locks.vit, m[k].locks.fec_frm, m[k].locks.fec_mpeg, m[k].locks.tps_dec, m[k].locks.tps_sync, m[k].locks.tps_data, m[k].locks.tps_cellid, m[k].locks.dvsy);
					printf("\n");
				}
			}
		}
		else if (demods_have_standard(m, num, STANDARD_DVBSH)) {
			printf("demod locks:  agc	 coff		 lmod4	equal tps_dec	 tps_data	  dvsy\n");
			printf("			  | corm | coff_cpil | pha3 |	  | tps_sync | tps_cellid |\n");
			for (k = 0; k < num; k++)
				printf("demod %2d:	   %d %d	%d %d		  %d %d    %d	  %d %d 	   %d %d		  %d\n",k,
						m[k].locks.agc, m[k].locks.corm, m[k].locks.coff, m[k].locks.coff_cpil, m[k].locks.lmod4, m[k].locks.pha3, m[k].locks.equal,  m[k].locks.tps_dec, m[k].locks.tps_sync, m[k].locks.tps_data, m[k].locks.tps_cellid, m[k].locks.dvsy);
			printf("\n");
		}
#endif
#ifdef CONFIG_STANDARD_DAB
		 if (demods_have_standard(m, num, STANDARD_DAB)) {
			if (!m[0].do_not_display_chandec) {
				val_("Nonlin quant | reverse quant | full internal : ");
				for (k = 0; k < num; k++)
					printf("   %dbit | %dbit | %d", m[k].dab.nb_bit_quant, m[k].dab.nb_bit_reverse_quant,m[k].dab.tdint_full_internal);
				printf("\n");

				printf("DAB locks:	 dmb_lock_frm  ndec_tmode	 fec_mpeg	dabcoff_lock\n");
				printf("			 | corm_dmb    | ndec_frame  | fec_frm	|\n");
				for (k = 0; k < num; k++)
					printf("demod %2d:	  %d %d 		  %d %d 		  %d %d 	   %d\n",k,m[k].dab.dmb_lock_frm, m[k].locks.corm_lock_dmb, m[k].locks.ndec_tmode_lock, m[k].locks.ndec_frame_lock ,m[k].locks.fec_mpeg, m[k].locks.fec_frm, m[k].locks.dabcoff_lock);

				printf("SubChan :	  subc_id  recfg	  cifcounter  subc_sz		  sz_prev	index	   L2punct	  PI2\n");
				printf("			  |  isMSC | subc_new |  staddr   |   staddr_prev |   form	| L1punct  |   PI1	  | I\n");

				for (k = 0; k < num; k++)
				printf("demod %2d:	  %2d  %d	  %d %d 	  %3d %d	   %d  %d		   %d  %d	  %d %d   %d  %d	  %d %d\n",k,m[k].dab.subc_id, m[k].dab.isMSC, m[k].dab.recfg, m[k].dab.subc_new, m[k].dab.cifcounter, m[k].dab.subc_staddr, m[k].dab.subc_sz, m[k].dab.subc_staddr_prev, m[k].dab.subc_sz_prev, m[k].dab.subc_form, m[k].dab.subc_index, m[k].dab.subc_L1punct, m[k].dab.subc_L2punct, m[k].dab.subc_PI1, m[k].dab.subc_PI2, m[k].dab.subc_I);

				printf("\nFEC id	");
				for (i = 0 ; i < 12 ; i++)
					printf("%2d  ",i);
				printf("\n");

				for (k = 0; k < num; k++) {
					printf("%d STATE:  ",k);
					for (i = 0 ; i < 12 ; i++)
						printf("%2d  ",(m[k].dab.fec_state >> i)&0x1);
					printf("\n");

					printf("%d SubId:  ",k);
					for (i = 0 ; i < 12 ; i++)
						printf("%2d  ",m[k].dab.fec_subid[i]);
					printf("\n\n");
				}
			} else {
				printf("DAB locks:	 signal_detect\n");
				for (k = 0; k < num; k++)
					printf("demod %2d:	  %d\n",k, m[k].locks.coff);
			}

		}
#endif
		if ((!demods_have_standard(m, num, STANDARD_DAB))) {
			if (m[0].n_2dpa_monitoring) {
				val_("mu_int/num_fir");
				for (k = 0; k < num; k++)
					printf("%d/%d%15s", m[k].n_2dpa_mu_int, m[k].n_2dpa_num_fir, " ");
				printf("\n");

				for (i = 0; i < 4; i++) {
					printf("cti_def%d%20s",i," ");
					for (k = 0; k < num; k++)
						printf("%2d (%5d)	", (int)m[k].cti_def[i], m[k].cti_def_raw[i]);
					printf("\n");
				}
				printf("\n");
			}

			val_("Divin FIFO overflow");
			for (k = 0; k < num; k++)
				printf("%-15d",m[k].divin_fifo_overflow);
			printf("\n");

			val_("Divin error symbols");
			for (k = 0; k < num; k++)
				printf("%-15d",m[k].divin_nberr_sym);
			printf("\n");

			val_("Dvsy first arrived");
			for (k = 0; k < num; k++)
				printf("%-15d",m[k].dvsy_first_arrived);
			printf("\n");

			val_("Dvsy delay");
			for (k = 0; k < num; k++)
				printf("%-15d",m[k].dvsy_delay);
			printf("\n");

			val_("Divin OK (Way 0, 1)");
			for (k = 0; k < num; k++)
				printf("%d,%d%12s",m[k].way0_ok,m[k].way1_ok,"");
			printf("\n");
		}

		val_("Inversion"); //, DDS, (msb,lsb)");
		for (k = 0; k < num; k++)
			printf("%-15d",m[k].invspec);
		printf("\n");

		val_("p DDS Freq");
		for (k = 0; k < num; k++)
			printf("%-15d  (*2^16)",(int)(m[k].viewable_dds_freq*65536));
		printf("\n");

		if (stat_count > 0) {
			printf("\nDiB7000 statistics each time after %d monitor iterations\n",stat_count);
			val_("C/N (linear mean)");
			for (k = 0; k < num; k++)
				printf("%-15d  (*2^16)", (int)(s[k].CoN_lin_mean*65536));
			printf("\n");

			val_("C/N (logarithmic mean)");
			for (k = 0; k < num; k++)
				printf("%-15d  (*2^16)", (int)(s[k].CoN_log_mean*65536));
			printf("\n");

			val_("C/N (min)");
			for (k = 0; k < num; k++)
				printf("%-15d  (*2^16)", (int)(s[k].CoN_min*65536));
			printf("\n");

			val_("C/N (max)");
			for (k = 0; k < num; k++)
				printf("%-15d  (*2^16)", (int)(s[k].CoN_max*65536));
			printf("\n\n");
		}
	}
}

