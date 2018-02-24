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
int dib8000_set_diversity_in(struct dibFrontend *fe, int onoff)
{
    struct dib8000_state *state = fe->demod_priv;
    uint16_t tmp = dib8000_read_word(state, 273) & 0xfff0;

    if (!state->differential_constellation) {
        dib8000_write_word(state, 272, 1 << 9); //dvsy_off_lmod4 = 1
        dib8000_write_word(state, 273, tmp | (1 << 2) | 2); // sync_enable = 1; comb_mode = 2
    } else {
        dib8000_write_word(state, 272, 0); //dvsy_off_lmod4 = 0
        dib8000_write_word(state, 273, tmp); // sync_enable = 0; comb_mode = 0
    }
    state->diversity_onoff = onoff;

    switch (onoff) {
    case 0: /* only use the internal way - not the diversity input */
        dib8000_write_word(state, 270, 1);
        dib8000_write_word(state, 271, 0);
        break;
    case 1: /* both ways */
        dib8000_write_word(state, 270, 6);
        dib8000_write_word(state, 271, 6);
        break;
    case 2: /* only the diversity input */
        dib8000_write_word(state, 270, 0);
        dib8000_write_word(state, 271, 1);
        break;
    }

    dbgp("fe %d state->revision = 0x%04x\n",fe->id, state->revision);
    if (state->revision == 0x8002) {
        tmp = dib8000_read_word(state, 903);
        dib8000_write_word(state, 903, tmp & ~(1 << 3));
        DibMSleep(30);
        dib8000_write_word(state, 903, tmp | (1 << 3));
    }

    return DIB_RETURN_SUCCESS;
}

static void dib8000_set_acquisition_mode(struct dib8000_state *state)
{
    uint16_t nud = dib8000_read_word(state, 298);
    dbgp("acquisition mode activated\n");
    if (state->revision >= 0x8002)
        nud |= (1<<5) | (1<<2);
    else
        nud |= (1<<3) | (1<<0);
    dib8000_write_word(state, 298, nud);
}

int dib8000_set_output_mode(struct dib8000_state *state, int mode)
{
    uint16_t outreg, fifo_threshold, smo_mode,
             sram = 0x0205; /* by default SDRAM deintlv is enabled */

    outreg = 0;
    fifo_threshold = 1792;
    smo_mode = (dib8000_read_word(state, 299) & 0x0050) | (1 << 1);

    dbgp("-I-  Setting output mode for demod %p to %d\n", state->fe, mode);
    state->output_mode = mode;

    switch (mode) {
    case OUTPUT_MODE_TS_PARALLEL_GATED:   // STBs with parallel gated clock
        outreg = (1 << 10);  /* 0x0400 */
        break;
    case OUTPUT_MODE_TS_PARALLEL_CONT:    // STBs with parallel continues clock
        outreg = (1 << 10) | (1 << 6); /* 0x0440 */
        break;
    case OUTPUT_MODE_TS_SERIAL:          // STBs with serial input
        outreg = (1 << 10) | (2 << 6) | (0 << 1); /* 0x0482 */
        break;
    case OUTPUT_MODE_DIVERSITY:
        if (state->cfg.hostbus_diversity) {
            outreg = (1 << 10) | (4 << 6); /* 0x0500 */
            sram &= 0xfdff;
        } else
            sram |= 0x0c00;
        break;
    case OUTPUT_MODE_TS_FIFO:            // e.g. USB feeding
        smo_mode |= (3 << 1);
        fifo_threshold = 512;
        outreg = (1 << 10) | (5 << 6);
        break;
    case OUTPUT_MODE_OFF:  // disable
        outreg = 0;
        break;

    case OUTPUT_MODE_ANALOG_ADC:
        outreg = (1 << 10) | (3 << 6);
        dib8000_set_acquisition_mode(state);
        break;

    default:
        dbgp("Unhandled output_mode passed to be set for demod %p\n", state->fe);
        return DIB_RETURN_ERROR;
    }

    if (state->cfg.output_mpeg2_in_188_bytes)
        smo_mode |= (1 << 5) ;

    dib8000_write_word(state,  299, smo_mode);
    dib8000_write_word(state,  300, fifo_threshold); /* synchronous fread */
    dib8000_write_word(state, 1286, outreg);
    dib8000_write_word(state, 1291, sram);

    return DIB_RETURN_SUCCESS;
}

int dib8000_pid_filter_ctrl(struct dibFrontend *fe, uint8_t onoff)
{
    struct dib8000_state *state = fe->demod_priv;
    uint16_t val = dib8000_read_word(state, 299) & 0xffef;
    val |= (onoff & 0x1) << 4;

    dbgp("pid filter enabled %d\n", onoff);
    return dib8000_write_word(state, 299, val);
}

int dib8000_pid_filter(struct dibFrontend *fe, uint8_t id, uint16_t pid, uint8_t onoff)
{
    struct dib8000_state *state = fe->demod_priv;
    dbgp("Index %x, PID %d, OnOff %d\n", id, pid, onoff);
    return dib8000_write_word(state, 305 + id, onoff ? (1 << 13) | pid : 0);
}
