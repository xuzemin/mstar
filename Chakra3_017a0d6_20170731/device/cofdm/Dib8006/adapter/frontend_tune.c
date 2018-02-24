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
#include "frontend_tune.h"
#include "component_monitor.h"
#include "msAPI_Timer.h"
#define MAX_AUTOSEARCH_ITERATIONS 10000


//DEBUG_OBJECT_STATIC(sample_dbg, DEBUG_ADAPTER, "SAMPLE");
static const struct dibDebugObject sample_dbg = { \
        DEBUG_ADAPTER, 
        "SAMPLE"
    };


void dump_digital_channel_params(struct dibChannel *cd)
{
#ifdef CONFIG_STANDARD_DVBT
    if (cd->type == STANDARD_DVBT) {
        dbgp("STANDARD DVB-T/H: ");
        dbgp("RF=%dkHz, ",cd->RF_kHz);
            switch (cd->u.dvbt.nfft) {
                    case FFT_8K: dbgp("8K "); break;
                    case FFT_4K: dbgp("4K "); break;
                    case FFT_2K: dbgp("2K "); break;
                    default: dbgp("FFT_UNK "); break;
            }

            dbgp("1/%i ", 32 / (1 << cd->u.dvbt.guard));
            switch (cd->u.dvbt.constellation) {
                    case QAM_QPSK: dbgp("QPSK "); break;
                    case QAM_16QAM: dbgp("16QAM "); break;
                    case QAM_64QAM: dbgp("64QAM "); break;
            default: dbgp("QAM_UNK "); break;
            }

            dbgp("%s ", cd->u.dvbt.intlv_native ? "NATIVE_INTLV" : "EXTENDED_INTLV");
            dbgp("ALPHA %i ", cd->u.dvbt.alpha);
            dbgp("Code Rate HP %i/%i ", cd->u.dvbt.code_rate_hp, cd->u.dvbt.code_rate_hp + 1);
            dbgp("Code Rate LP %i/%i ", cd->u.dvbt.code_rate_lp, cd->u.dvbt.code_rate_lp + 1);
            dbgp("HRCH %i\n", cd->u.dvbt.hrch);
    }
#endif
#ifdef CONFIG_STANDARD_DVBSH
    if (cd->type == STANDARD_DVBSH) {
        dbgp("STANDARD DVB-SH: ");
        dbgp("RF=%dkHz, ",cd->RF_kHz);
        dbgp("dvb_sh %d ", cd->u.dvbsh.dvb_sh);

        switch (cd->u.dvbsh.dvb_common.nfft) {
            case FFT_8K: dbgp("FFT 8K "); break;
            case FFT_4K: dbgp("FFT 4K "); break;
            case FFT_2K: dbgp("FFT 2K "); break;
            case FFT_1K: dbgp("FFT 1K "); break;
            default: dbgp("FFT_UNK "); break;
        }

        dbgp("GT=1/%i  ", 32 / (1 << cd->u.dvbsh.dvb_common.guard));
        switch (cd->u.dvbsh.dvb_common.constellation) {
            case QAM_QPSK: dbgp("QPSK "); break;
            case QAM_16QAM: dbgp("16QAM "); break;
            default: dbgp("QAM_UNK "); break;
        }
        dbgp("INTLV %s ", cd->u.dvbsh.dvb_common.intlv_native ? "NATIVE" : "EXTENDED");
        dbgp("ALPHA %i ", cd->u.dvbsh.dvb_common.alpha);
        dbgp("Code Rate HP %s ", DVBSH_CODERATE_TO_STRING(cd->u.dvbsh.dvb_common.code_rate_hp));
        dbgp("Code Rate LP %s ", DVBSH_CODERATE_TO_STRING(cd->u.dvbsh.dvb_common.code_rate_lp));
        dbgp("HRCH %i\n", cd->u.dvbsh.dvb_common.hrch);
        dbgp("SH INTLV - [CMult = %d]  [Nb of late taps = %d] [Nb of slices = %d] [Slice dist = %d] [Non late incr = %d]\n", cd->u.dvbsh.common_mult,cd->u.dvbsh.nof_late_taps,cd->u.dvbsh.nof_slices,cd->u.dvbsh.slice_distance, cd->u.dvbsh.non_late_incr);
    }
#endif

#ifdef CONFIG_STANDARD_ISDBT
    if (cd->type == STANDARD_ISDBT) {
        int i;
        dbgp("STANDARD ISDBT: ");
        dbgp("RF=%dkHz, ",cd->RF_kHz);
            switch (cd->u.isdbt.nfft) {
                    case FFT_8K: dbgp("8K "); break;
                    case FFT_4K: dbgp("4K "); break;
                    case FFT_2K: dbgp("2K "); break;
                    default: dbgp("FFT_UNK "); break;
            }

            dbgp("1/%d  ", 32 / (1 << cd->u.isdbt.guard));

                if (cd->u.isdbt.spectrum_inversion)
                        dbgp("inverted  ");
        dbgp("%s ", cd->u.isdbt.partial_reception ? "PARTIAL_RCPT" : "NATIVE_RCPT");
        dbgp("%s ", cd->u.isdbt.sb_mode ? "SB_mode":"");
        for (i = 0; i < 3; i ++) {
            dbgp("| L%c: nb_seg: %d ", 'a' + i, cd->u.isdbt.layer[i].nb_segments);
            switch (cd->u.isdbt.layer[i].constellation) {
                        case QAM_QPSK: dbgp("QPSK "); break;
                        case QAM_16QAM: dbgp("16QAM "); break;
                        case QAM_64QAM: dbgp("64QAM "); break;
                case QAM_DQPSK: dbgp("DQPSK"); break;
                        default: dbgp("QAM_UNK "); break;
                }
            dbgp("%d/%d ",cd->u.isdbt.layer[i].code_rate, cd->u.isdbt.layer[i].code_rate+1);
            dbgp("%d ", cd->u.isdbt.layer[i].time_intlv);
        }
        dbgp("\n");
    }
#endif
#ifdef CONFIG_STANDARD_DAB
    if (cd->type == STANDARD_DAB) {
        int i;
        dbgp("STANDARD TDMB/DAB: ");
        dbgp("RF=%dkHz, ",cd->RF_kHz);
        switch (cd->u.dab.tmode) {
            case 1: dbgp("T-MODE   I 1536 carriers"); break;
            case 2:     dbgp("T-MODE  II 384  carriers "); break;
            case 3:     dbgp("T-MODE III 192  carriers"); break;
            case 4:     dbgp("T-MODE  IV 768  carriers"); break;
        }

        for (i = 0; i < cd->u.dab.nb_active_sub ; i ++) {
            dbgp("-> sub-channel item #%2d subChid:%2d ",i, cd->u.dab.subChannel[i].subChid);
            dbgp("| start address : %3d\n",i, cd->u.dab.subChannel[i].start_address);
            dbgp("%s ", cd->u.dab.subChannel[i].form ? "UEP" : "EEP");
            switch(cd->u.dab.subChannel[i].form)
            {
                case 0: // UEP
                    dbgp("| table index : %2d ", cd->u.dab.subChannel[i].table_index);
                    break;
                case 1: // EEP
                    dbgp("| option : %2d ",             cd->u.dab.subChannel[i].option);
                    dbgp("| protection level : %2d ",   cd->u.dab.subChannel[i].protection_level);
                    dbgp("| sub size : %3d CUs ",       cd->u.dab.subChannel[i].sub_size);
                    break;
            }
            // Additionnal params
            dbgp("\nstart_addr_prev : %3d Cus ",        cd->u.dab.subChannel[i].start_addr_prev);
            dbgp("| size_prev : %3d Cus ",              cd->u.dab.subChannel[i].size_prev);
            dbgp("| is_ts : %1d ",              cd->u.dab.subChannel[i].is_ts);
            dbgp("| URAM addr : %04x ", cd->u.dab.subChannel[i].addr_URAM);
            dbgp("| %s\n", cd->u.dab.subChannel[i].subc_new ? "New sub-channel !" : "Old sub-channel");
        }
        dbgp("\n");
    }
#endif
}

/* Do the autosearch with num demods */
static int do_fe_autosearch(struct dibFrontend fe[], int num, struct dibChannel *ch)
{
    int ret,i,k,stat = 0, num_failed = 0, succeeded = 0;

    for (i = 0; i < num; i++) {
        if ((ret = demod_autosearch_start_ex(&fe[i], ch)) != 0) {
            dbgp("starting autosearch failed for demod %d\n",i);
            return ret;
        }
    }

    for (i = 0; !succeeded && num != num_failed && i < MAX_AUTOSEARCH_ITERATIONS; i++) {
        for (k = 0; k < num; k++) {
            if (!(stat & (1 << k))) { // if not already excluded from autosearch
                switch (demod_autosearch_irq(&fe[k])) {
                    case 0: break;
                    case 2:
                            dbgp("Autosearch succeeded for demod %d - done.\n",k);
                            succeeded = 1;
                            break;
                    default:
                            dbgp("Autosearch IRQ return unhandled value for demod %d.\n",k);
                    case 1: /* fall throught wanted */
                            dbgp("Autosearch failed for demod %d - exluding from list.\n",k);
                            stat |= (1 << k);
                            num_failed++;
                            break;
                }
                if (succeeded)
                    break;
            }
        }
        DibMSleep(1);
    }

    if (!succeeded) {
        dbgp("Autosearch failed for %d demod(s)\n",num_failed);
        return 1;
    }

    ch->context.status = CHANNEL_STATUS_PARAMETERS_SET;
    return demod_get_channel(&fe[k],ch);
}

/* tune (do autosearch in case of unknown parameters) */
void frontend_tune_diversity_sync(struct dibFrontend fe[],int num, struct dibChannel *ch)
{
    int i, sleep_time, ret;

    for (i = 0; i < num; i++)
        frontend_wakeup(&fe[i]);

    for (i = 0; i < num; i++) {
        if (tuner_tune(&fe[i], ch) != 0) {
            dbgp("Tuner tune_digital failed\n");
            return;
        }

        /* prepare the agc startup loop */
        demod_agc_restart(&fe[i]);
    }

    do {
        sleep_time = -1;
        for (i = 0; i < num; i++) {
            ret = demod_agc_startup_ex(&fe[i], ch);
            if (ret > sleep_time)
                sleep_time = ret;
        }
        if (sleep_time != -1)
            DibMSleep(sleep_time);
    } while (sleep_time != -1);

    if (ch->context.status == CHANNEL_STATUS_PARAMETERS_UNKNOWN)
        if (do_fe_autosearch(fe, num, ch) != 0) {
            dbgp("autosearching parameters failed.\n");
            demod_set_output_mode(&fe[0], CONFIG_OUTPUT_MODE);
            return;
        }

    dump_digital_channel_params(ch);

    for (i = 0; i < num; i++) {
        frontend_tune_restart(&fe[i], FE_RESTART_TUNE_PROCESS_FROM_DEMOD, ch);
        if (demod_tune_ex(&fe[i],ch) != 0)
            dbgp("tuning failed for demod - this is just a warning could be normal in diversity.\n");
    }

    for (i = 0; i < num; i++) {
        if (i == num-1) { // last demod in a diversity chain - turn off div-in combination
            dbgp("setting diversity in off for demod %d\n",i);
            demod_set_diversity_in(&fe[i], 0);
        } else {
            dbgp("setting diversity in on  for demod %d\n",i);
            demod_set_diversity_in(&fe[i], 1);
        }

        if (i == 0) { // first demod in a diversity chain - no diversity output
            dbgp("setting normal output for demod %d\n",i);
            demod_set_output_mode(&fe[i], CONFIG_OUTPUT_MODE);
        } else {
            dbgp("setting diversity out on for demod %d\n",i);
            demod_set_output_mode(&fe[i], OUTMODE_DIVERSITY);
        }
    }
    return;
}

void frontend_tune_diversity_async(struct dibFrontend fe[], int count, struct dibChannel *ch)
{
    int i, l, active;
    uint32_t callback_time;

	dbgp("frontend_tune_diversity_async,Freq:%d \n",ch->RF_kHz);
    /* restart the tuning process */
    for (i = 0; i < count; i++) {
        frontend_wakeup(&fe[i]);
        frontend_tune_restart(&fe[i], FE_RESTART_TUNE_PROCESS_FROM_TUNER, ch);
        if (i+1 < count)
            fe[i].input = &fe[i+1];
    }

    /* setup the diversity chain - data outputs */
    for (i = 0; i < count; i++) {
        if (i == count-1) { // last demod in a diversity chain - turn off div-in combination
            dbgp("setting diversity in off for demod %d\n",i);
            demod_set_diversity_in(&fe[i], 0);
        } else {
            dbgp("setting diversity in on  for demod %d\n",i);
            demod_set_diversity_in(&fe[i], 1);
        }

        if (i != 0) { // first demod in a diversity chain - no diversity output
            dbgp("setting diversity out on for demod %d\n",i);
            demod_set_output_mode(&fe[i], OUTMODE_DIVERSITY);
        }
    }

    active = 1;
    do {
        callback_time = FE_CALLBACK_TIME_NEVER;
        for (i = 0; i < count; i++) {
            frontend_tune(&fe[i], ch);

            /* we are in autosearch */
            if (ch->context.status == CHANNEL_STATUS_PARAMETERS_UNKNOWN) { // searching
		if ((frontend_get_status(&fe[i]) == FE_STATUS_DEMOD_SUCCESS) || (frontend_get_status(&fe[i]) == FE_STATUS_FFT_SUCCESS)) {
                    dbgp("Autosearch succeeded on FE %d\n", fe[i].id);
                    frontend_get_channel(&fe[i], ch); /* we read the channel parameters from the frontend which was successful */

                    dump_digital_channel_params(ch);

                    for (l = 0; l < count; l++) {
                        if (l != i ) /* and for all frontend except the successful one */
                            frontend_tune_restart(&fe[l], FE_RESTART_TUNE_PROCESS_FROM_DEMOD, ch); /* we restart the demod tuning process : partial_restart = 1*/
                    }
                }
            }
            if (frontend_callback_time(&fe[i]) < callback_time)
                callback_time = frontend_callback_time(&fe[i]);
        }

        /* tuning is done when the master frontend is done (failed or success) */
        if (frontend_get_status(&fe[0]) == FE_STATUS_TUNE_FAILED ||
                frontend_get_status(&fe[0]) == FE_STATUS_LOCKED ||
                frontend_get_status(&fe[0]) == FE_STATUS_DATA_LOCKED) {
            active = 0;
            /* we need to wait for all frontends to be finished */
            for (i = 0; i < count; i++)
                if (fe[i].tune_state != CT_DONE)
                    active = 1;
            if (active == 0)
                dbgp("tuning done with status %d\n", frontend_get_status(&fe[0]));
        }

        if ((active == 1) && (callback_time == FE_CALLBACK_TIME_NEVER)) {
            dbgp("strange callback time something went wrong\n");
            dbgp("active=%i\n", active);
            active = 0;
        }

        /* busy wait here - put useful code here, if you can or better integrate this code in your state-machine */
        while ((active == 1) && (systime() < callback_time)) { DibMSleep(1); /* utilize CPU */}

    } while (active);

    if (ch->context.status == CHANNEL_STATUS_PARAMETERS_SET)
        demod_set_output_mode(&fe[0], CONFIG_OUTPUT_MODE); // set the master output mode
}

