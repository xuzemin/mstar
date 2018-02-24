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
#include "msAPI_Timer.h"
int tuner_reset(struct dibFrontend *fe)
{
    if (FE_TUNER_FUNC_CHECK(fe, reset))
        return FE_TUNER_FUNC_CALL(fe, reset)(fe);
    else return DIB_RETURN_SUCCESS;
}

int tuner_sleep(struct dibFrontend *fe)
{
    if (FE_TUNER_FUNC_CHECK(fe, sleep))
        return FE_TUNER_FUNC_CALL(fe, sleep)(fe);
    else return DIB_RETURN_SUCCESS;
}

#ifdef CONFIG_STANDARD_ANALOG
int tuner_tune_analog(struct dibFrontend *fe, struct dibAnalogChannel *ch)
{
    if (FE_TUNER_FUNC_CHECK(fe, tune_analog))
        return FE_TUNER_FUNC_CALL(fe, tune_analog)(fe,ch);
    else
        return DIB_RETURN_SUCCESS;
}
#endif

void tuner_release(struct dibFrontend *fe)
{
    if (FE_TUNER_FUNC_CHECK(fe, release))
        fe->tuner_info->ops.release(fe);
}

struct dibDataBusClient * tuner_get_data_bus_client(struct dibFrontend *fe)
{
    if ((fe != NULL) && (fe->tuner_info != NULL))
        return &fe->tuner_info->data_bus_client;
    else
        return NULL;
}

int tuner_wakeup(struct dibFrontend *fe)
{
    if (FE_TUNER_FUNC_CHECK(fe, wakeup))
        return FE_TUNER_FUNC_CALL(fe, wakeup)(fe);

    return DIB_RETURN_SUCCESS;
}

#ifndef NO_SHARED_TUNER
int tuner_try_inc_use_count(struct dibFrontend *tuner, int count)
{
	if ((tuner->tuner_info->use_count + count) > TUNER_MAX_USE_COUNT)
		return DIB_RETURN_ERROR;
	return DIB_RETURN_SUCCESS;
}

int tuner_inc_use_count(struct dibFrontend *tuner, int count)
{
	if (tuner_try_inc_use_count(tuner,count) != DIB_RETURN_SUCCESS)
		return DIB_RETURN_ERROR;

	tuner->tuner_info->use_count += count;
	return DIB_RETURN_SUCCESS;
}

int tuner_dec_use_count(struct dibFrontend *tuner, int count)
{
	tuner->tuner_info->use_count -= count;
	if (tuner->tuner_info->use_count < 0) {
        tuner->tuner_info->use_count = 0; //To be modified ASAP
        DibDbgPrint("-E-  tuner use_count is below zero - something is wrong\n");
		return DIB_RETURN_ERROR;
	}
	return DIB_RETURN_SUCCESS;
}

int tuner_use_count(struct dibFrontend *fe)
{
    if ((fe != NULL) && (fe->tuner_info != NULL))
        return fe->tuner_info->use_count;
    else
        return 4;
}
#endif

#ifndef NO_DVBCHANNEL_BACKWARD_COMPAT
int tuner_tune_digital(struct dibFrontend* tuner,struct dibDVBChannel* ch)
{
    struct dibChannel digitch;
    CONVERT_DVB_TO_DIGITAL_CHANNEL(ch, &digitch);
    return tuner_tune(tuner, &digitch);
}
#endif

int tuner_tune_fast(struct dibFrontend *fe, struct dibChannel *ch)
{
    if (fe->tuner_info) {
        if (fe->tuner_info->ops.tune_digital) {
            if (fe->tuner_info->caps & TUNER_CAN_FAST_TUNE) {
                if (component_ready(fe->tuner_info->callback_time, fe->tune_state, CT_TUNER_START)) {
					
                    uint32_t callback_time = fe->tuner_info->ops.tune_digital(fe, ch);

                    if (callback_time == FE_CALLBACK_TIME_NEVER)
                        fe->tuner_info->callback_time = FE_CALLBACK_TIME_NEVER;
                    else
                        fe->tuner_info->callback_time  = callback_time + systime();
                    //dbgpl(NULL,"fe%d->tuner_info->callback_time = %d  systime = %d ", fe->id, fe->tuner_info->callback_time, syst);
                }
                return DIB_RETURN_SUCCESS;
            }
#ifndef NO_SYNC_INTERFACE
            else {
                if (fe->tune_state == CT_TUNER_START) {

                    fe->tuner_info->callback_time = FE_CALLBACK_TIME_NEVER;
                    fe->tune_state = CT_TUNER_STOP;

                    return fe->tuner_info->ops.tune_digital(fe, ch);
                } else
                    return DIB_RETURN_SUCCESS;
            }
#endif
        } else
            fe->tuner_info->callback_time = FE_CALLBACK_TIME_NEVER;
    }
    return DIB_RETURN_NOT_SUPPORTED;
}

#ifndef NO_DVBCHANNEL_BACKWARD_COMPAT
/* backward compat */
int tuner_tune(struct dibFrontend *fe, struct dibChannel *ch)
{
    if (fe->tuner_info && fe->tuner_info->ops.tune_digital) {
        if (fe->tuner_info->caps & TUNER_CAN_FAST_TUNE) {
            int ret;
            fe->tune_state = CT_TUNER_START;
            do {
                ret = fe->tuner_info->ops.tune_digital(fe, ch);
                DibUSleep(ret * 100);
            } while (fe->tune_state != CT_TUNER_STOP);
            return DIB_RETURN_SUCCESS;
        } else
            return fe->tuner_info->ops.tune_digital(fe, ch);
    }
    return DIB_RETURN_SUCCESS;
}
#endif

#ifndef NO_ADVANCED_FEATURES
int tuner_get_frequency(struct dibFrontend *fe)
{
    uint8_t f[4];
    if (frontend_generic_monitoring(fe, GENERIC_MONIT_RADIO_FREQUENCY, f, 4, 0) == 4)
        return f[0] << 24 | f[1] << 16 | f[2] << 8 | f[3];
    return 0;
}
#endif
