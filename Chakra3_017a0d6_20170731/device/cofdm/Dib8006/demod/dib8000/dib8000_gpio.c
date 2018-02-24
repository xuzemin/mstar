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

int dib8000_cfg_gpio(struct dib8000_state *st, uint8_t num, uint8_t dir, uint8_t val)
{
	st->cfg.gpio_dir = dib8000_read_word(st, 1029);
	st->cfg.gpio_dir &= ~(1 << num);         /* reset the direction bit */
	st->cfg.gpio_dir |=  (dir & 0x1) << num; /* set the new direction */
	dib8000_write_word(st, 1029, st->cfg.gpio_dir);

	st->cfg.gpio_val = dib8000_read_word(st, 1030);
	st->cfg.gpio_val &= ~(1 << num);          /* reset the direction bit */
	st->cfg.gpio_val |=  (val & 0x01) << num; /* set the new value */
	dib8000_write_word(st, 1030, st->cfg.gpio_val);

	dbgp("gpio dir: %x: gpio val: %x\n",
		st->cfg.gpio_dir, st->cfg.gpio_val);

	return DIB_RETURN_SUCCESS;
}

int dib8000_reset_gpio(struct dib8000_state *st)
{
	/* reset the GPIOs */
	dib8000_write_word(st, 1029, st->cfg.gpio_dir);
	dib8000_write_word(st, 1030, st->cfg.gpio_val);

	/* TODO 782 is P_gpio_od */

	dib8000_write_word(st, 1032, st->cfg.gpio_pwm_pos);

	dib8000_write_word(st, 1037, st->cfg.pwm_freq_div);
	return DIB_RETURN_SUCCESS;
}

int dib8000_set_pwm_gpio(struct dibFrontend *fe, uint8_t num, uint8_t id, uint8_t freq, uint32_t rate)
{
	struct dib8000_state *state = fe->demod_priv;
    uint16_t value;
    uint8_t bit1 = (3 - id)*4;

    if (id > 4)
        return DIB_RETURN_ERROR;

    dib8000_cfg_gpio(state, num, 0, 0);

    value  = dib8000_read_word(state, 1032);
    value &= ~(0xf << bit1);
    value |=  (num << bit1);
    dib8000_write_word(state, 1032, value);
    dib8000_write_word(state, 1033 + id, (uint16_t)rate);
    dib8000_write_word(state, 1037, freq);
    return DIB_RETURN_SUCCESS;
}

