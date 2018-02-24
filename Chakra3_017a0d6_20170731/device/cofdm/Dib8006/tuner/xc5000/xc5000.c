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
#include <adapter/frontend.h>
#include <adapter/databus.h>

#include <tuner/xc5000.h>

#include "xc5000_control.h"

#include "xc5000_channelmaps.h"

#include "xc5000_firmwares.h"

#include "xc5000_Standards.h"
#include "msAPI_Timer.h"
#include "Utl.h"
#include "msAPI_Memory.h"
struct xc5000_state {
       struct dibTunerInfo info;
    struct dibFrontend *fe;
       const struct xc5000_config *cfg;

       struct dibDataBusHost *i2c_adap;

       XC_TV_STANDARD *current_tv_mode_ptr;
       XC_CHANNEL_MAP *current_channel_map_ptr;
       XC_CHANNEL     *current_channel_ptr;
       uint8_t        *firmware_ptr;
       long            current_IF_Freq_khz;
       int base_firmware_downloaded;

       int reset;
};

static struct dibDebugObject xc5000_dbg = {
    DEBUG_TUNER,
    "XC5000",
};

/* functions used by the XCEIVE-tuner to be implemented by the device */
static int xc_wait(int wait_ms)
{
    DibMSleep(wait_ms);
    return XC_RESULT_SUCCESS;
}

static int xc_send_i2c_data(struct xc5000_state *st, uint8_t i2c_addr, uint8_t *b, uint32_t len)
{
    int ret;
	struct dibI2CAccess msg;
    INIT_I2C_ACCESS_FOR_WRITE(msg, st->cfg->i2c_address, b, (uint8_t) len);
    ret = i2c_transfer(st->i2c_adap,&msg);
    if (ret != DIB_RETURN_SUCCESS)
        return XC_RESULT_RESET_FAILURE;
    return XC_RESULT_SUCCESS;
}

static int xc_read_reg(struct xc5000_state *st, uint16_t reg, unsigned short int *data)
{
    unsigned char bo[2], bi[2];
    struct dibI2CAccess msg;

    bo[0] = (reg >> 8) & 0xff;
    bo[1] =  reg       & 0xff;

    INIT_I2C_ACCESS_FOR_READ(msg, st->cfg->i2c_address, bo, 2, bi, 2);

    if (i2c_transfer(st->i2c_adap,&msg) != 0)
        return XC_RESULT_RESET_FAILURE;

    *data = (bi[0] << 8) | bi[1];
    return XC_RESULT_SUCCESS;
}

#include "xc5000_control.c"

static int xc5000_reset(struct dibFrontend *fe)
{
    struct xc5000_state *st = fe->tuner_priv;
    uint16_t productID;

    if (st->reset) {
         st->firmware_ptr = XC5000_firmware_SEQUENCE;


        st->base_firmware_downloaded = 0;
        st->current_tv_mode_ptr     = &XC5000_Standard[0];
        st->current_channel_map_ptr = &AllChannelMaps[0]; // {"USA - Analog - Air", 68, USA_Analog_Air}
        st->current_IF_Freq_khz     = 4500; // SIF = 4500
        st->current_channel_ptr     = &st->current_channel_map_ptr->channels[0]; // channel 2

        if (xc_initialize(st, st->current_tv_mode_ptr, st->current_channel_map_ptr) != XC_RESULT_SUCCESS)
            return DIB_RETURN_ERROR;

        if (xc_set_rf_mode(st, 0) != XC_RESULT_SUCCESS)
            return DIB_RETURN_ERROR;        // RF Source is Air

        st->reset = 0;

        if (xc_get_product_id(st, &productID) != XC_RESULT_SUCCESS)
            return DIB_RETURN_ERROR;

        dbgpl(&xc5000_dbg, "%s: product: %d", __FUNCTION__, productID);
    }

    return DIB_RETURN_SUCCESS;
}

static int xc5000_tune(struct xc5000_state *st,
        XC_TV_STANDARD *standard, XC_CHANNEL_MAP *map,
        uint32_t rf, uint32_t ifreq,
        int input, int analog)
{
    int i;
    int delta = 0x7fffffff;
    XC_CHANNEL *channel = NULL;

    dbgpl(&xc5000_dbg, "tuning for standard: '%s' - '%s' - %dkHz (IF: %d)", standard->Name, map->MapType, rf, ifreq);

    if (xc_initialize(st, standard, map) != XC_RESULT_SUCCESS) {
        dbgpl(&xc5000_dbg, "ERROR: xc_initialize");
        return DIB_RETURN_ERROR;
    }

    if (xc_set_rf_mode(st, input) != XC_RESULT_SUCCESS) {
        dbgpl(&xc5000_dbg, "ERROR: xc_set_rf_mode");
        return DIB_RETURN_ERROR;
    }

    if (xc_FineTune_RF_frequency(st, rf * 1000) != XC_RESULT_SUCCESS) {
        dbgpl(&xc5000_dbg, "ERROR: xc_FineTune_RF_frequency");
        return DIB_RETURN_ERROR;
    }
    xc_wait(100);

    if (analog) {
        uint16_t lock;
        int count = 100;
        /* find closest channel */
        for (i = 0; i < map->nb_channels; i++) {
            if (ABS((rf*1000)/15625L - map->channels[i].frequency) < delta) {
                channel = &map->channels[i];
                delta = ABS((rf*1000)/15625L - map->channels[i].frequency);
            }
        }
        if (channel == NULL)
            return DIB_RETURN_ERROR;

        dbgpl(&xc5000_dbg, "CHANNEL: %s %d <-> %d %x", channel->identifier, rf, channel->frequency * 15625L / 1000, channel->dcode);

        while (count--) {
            if (xc_get_lock_status(st, &lock) != XC_RESULT_SUCCESS) {
                dbgpl(&xc5000_dbg, "ERROR: xc_get_lock_status");
                break;
            }
            if (lock & 0x0001)
                break;
            dbgpl(&xc5000_dbg, "lock: %d (0x%04x)", lock, lock);
            xc_wait(10);
        }

#if 0
        if (xc_set_channel(st, ifreq, channel) != XC_RESULT_SUCCESS) {
            dbgpl(&xc5000_dbg, "ERROR: xc_set_rf_frequency");
            return DIB_RETURN_ERROR;
        }
#endif
    } else
        xc_set_if_frequency(st, ifreq * 1000);

    dbgpl(&xc5000_dbg, "tuner tuned successfully");

    return DIB_RETURN_SUCCESS;
}

static int xc5000_tune_digital(struct dibFrontend *fe, struct dibChannel *ch)
{
    struct xc5000_state *st = fe->tuner_priv;
    XC_TV_STANDARD *tv;
    XC_CHANNEL_MAP *map;
    int32_t offset = -(int32_t)(ch->bandwidth_kHz/2 + 1250);

	st->current_IF_Freq_khz = 5200; //5.2 Mhz

    switch (ch->bandwidth_kHz) {
    case 8000:
        tv =  &XC5000_Standard[29]; //DTV8-DIBCOM-5_2MHZ
        map = &AllChannelMaps[26]; // XC5000_channel_map_France_Digital_Air;
        offset = -8000/2 + 1250;
        break;
    case 7000:
        tv =  &XC5000_Standard[31]; //DTV7-DIBCOM-5_2MHZ
        map = &AllChannelMaps[26]; // XC5000_channel_map_France_Digital_Air;
        offset = -7000/2 + 1250;
        break;
    case 6000:
        tv =  &XC5000_Standard[32]; //DTV6-XCEIVE-4_56MHZ
        map = &AllChannelMaps[14]; // XC5000_channel_map_France_Digital_Air;
        offset =  -6000/2 + 1250;
        break;
    default:
        dbgpl(&xc5000_dbg,  "not implemented Bandwidth : %d", ch->bandwidth_kHz);
        return DIB_RETURN_ERROR;
    }
	dbgpl(&xc5000_dbg,"XCEIVE B=%d",ch->bandwidth_kHz);

    fe->current_rf = ch->RF_kHz;
    return xc5000_tune(st, tv, map, ch->RF_kHz + offset, 5200, 0, 0);
}

static int xc5000_tune_analog(struct dibFrontend *fe, struct dibAnalogChannel *ch)
{
#ifdef CONFIG_STANDARD_ANALOG
    struct xc5000_state *st = fe->tuner_priv;
	int32_t offset = 0;

    XC_TV_STANDARD *tv;
    XC_CHANNEL_MAP *map;

    dbgpl(&xc5000_dbg, "xc5000_tune_analog");

    switch (ch->TunerStandard) {
    case AnalogVideo_PAL_M:
    case AnalogVideo_PAL_N:
    case AnalogVideo_NTSC_M:
        tv = &XC5000_Standard[0]; // XC5000_M/N-NTSC/PAL-BTSC-IF_SEQUENCE
        break;
    case AnalogVideo_SECAM_L:
        tv = &XC5000_Standard[10]; // XC5000_L_SECAM_NICAM_SEQUENCE
        break;
    case AnalogVideo_PAL_G:
    case AnalogVideo_PAL_B:
        tv = &XC5000_Standard[8]; // XC5000_XB/G-PAL-A2#A_SEQUENCE
        break;
    case AnalogVideo_PAL_I:
        tv = &XC5000_Standard[5]; // XC5000_I_PAL_NICAM_SEQUENCE
        break;
    case AnalogVideo_SECAM_D:
    case AnalogVideo_SECAM_K:
        tv = &XC5000_Standard[18]; // XC5000_D/K-SECAM-A2 DK1_SEQUENCE
        break;
    case AnalogVideo_PAL_D:
        tv = &XC5000_Standard[14]; // XC5000_D_K_PAL_A2_SEQUENCE
        break;
    case AnalogRadio_FM:
        if (st->cfg->fm_input == 2)
            tv = &XC5000_Standard[19];
        else
            tv = &XC5000_Standard[20];
        break;
    default:
        dbgpl(&xc5000_dbg, "passed TV mode not taken into consideration yet (%x)", ch->TunerStandard);
        return DIB_RETURN_ERROR;
    }

    switch (ch->CountryCode) {
    case CTRY_FRANCE:
        if (ch->Cable)
            map =&AllChannelMaps[25]; //  &France_Analog_Cable;
        else
            map =&AllChannelMaps[24]; //  &France_Analog_Air;
        break;
    case CTRY_TAIWAN:
        if (ch->Cable)
            map =&AllChannelMaps[9];  // &Taiwan_Analog_Cable;
        else
            map =&AllChannelMaps[8];  // &Taiwan_Analog_Air;
        break;
    case CTRY_UNITED_KINGDOM:
        if (ch->Cable)
            map =&AllChannelMaps[29]; // &UK_Analog_Cable;
        else
            map =&AllChannelMaps[28]; // &UK_Analog_Air;
        break;
    case CTRY_UNITED_STATES:
        if (ch->Cable)
            map =&AllChannelMaps[0];  // &USA_Analog_Cable;
        else
            map =&AllChannelMaps[1]; // &USA_Analog_Air;
        break;
    case CTRY_PRCHINA:
        if (ch->Cable)
            map =&AllChannelMaps[37];   // &China_Analog_Cable;
        else
            map =&AllChannelMaps[36];  // &China_Analog_Air;

        tv = &XC5000_Standard[9]; // XC5000_D_K_PAL_NICAM_SEQUENCE

        break;
    case CTRY_JAPAN:
        if (ch->Cable)
            map = &AllChannelMaps[13];  // &Japan_Analog_Cable;
        else
            map = &AllChannelMaps[12]; // &Japan_Analog_Air;
        break;
    default:
        if (ch->CountryCode != CTRY_DEFAULT)
            dbgpl(&xc5000_dbg, "country not handled yet - using default (%d)", ch->CountryCode);

        map = &AllChannelMaps[21];  // XC5000_channel_map_France_Analog_Air;

        break;
    }

	if (ch->RF_kHz < 303000)
		offset += 500;

    return xc5000_tune(st, tv, map, ch->RF_kHz+offset, 0, ch->Cable != 0, 1);
#endif
    return DIB_RETURN_ERROR;
}

static int xc5000_sleep(struct dibFrontend *fe)
{
    struct xc5000_state *st = fe->tuner_priv;
    return xc_shutdown(st);
}

static int xc5000_release(struct dibFrontend *fe)
{
    struct xc5000_state *st = fe->tuner_priv;
    if (st != NULL)
        MemFree(st,sizeof(struct xc5000_state));

    return 0;
}

static struct dibTunerInfo xc5000_info = {
    "Xceive XC5000",  // name
    TUNER_CAN_UHF | TUNER_CAN_VHF,

    { // ops
        xc5000_reset,

        NULL, // init
        xc5000_sleep, // sleep

        xc5000_tune_digital,  // tune_digital
#ifdef CONFIG_STANDARD_ANALOG
        xc5000_tune_analog,   // tune_analog
#else
        NULL,
#endif
        NULL,
        xc5000_release, // release
    }
};

struct dibFrontend * xc5000_register(struct dibFrontend *fe, struct dibDataBusHost *i2c_adap, const struct xc5000_config *cfg)
{
    struct xc5000_state *st = MemAlloc(sizeof(struct xc5000_state));
    if (st == NULL)
        return NULL;
    DibZeroMemory(st,sizeof(struct xc5000_state));

    frontend_register_tuner(fe, &st->info, &xc5000_info, st);

    st->cfg = cfg;
    st->i2c_adap = i2c_adap;
    st->fe = fe;

    st->reset = 1;

	return fe;
}

#if 0



#if 0
static int xc5000_soft_reset(struct xc5000_state *st)
{
    uint16_t productId = 0;
    uint8_t hw_majorversion, hw_minorversion, fw_majorversion, fw_minorversion;

//    if (!st->fwDownloaded) {
        uint8_t *seq;


        if (xc_load_i2c_sequence(st, seq) != XC_RESULT_SUCCESS) {
            dbgpl(&xc5000_dbg, "download_xc5000_firmware ERROR");
            return DIB_RETURN_ERROR;
        }
        dbgpl(&xc5000_dbg, "download_xc5000_firmware OK ");
  //  }

    //xc_initialize(st); // Auto Calibration

    xc_wait(100);

    xc_get_product_id(st, &productId);
    dbgpl(&xc5000_dbg, "product ID: %d", productId);
    if (productId != 5000) {
        dbgpl(&xc5000_dbg, "wrong product ID");
        return DIB_RETURN_ERROR;
    }

    xc_get_version(st, &hw_majorversion, &hw_minorversion,
			               &fw_majorversion, &fw_minorversion);

	dbgpl(&xc5000_dbg, "hw ver : %d.%d fw ver: %d.%d", hw_majorversion,hw_minorversion, fw_majorversion,fw_minorversion);

    return DIB_RETURN_SUCCESS;
}
#endif

/* tuner control interface of DiBcom */
static int xc5000_initialize_Standard(struct xc5000_state *st,
									  XC_TV_STANDARD* new_tv_std_ptr,
									  XC_CHANNEL_MAP* new_channel_map_ptr,
									  unsigned short modeTrans,
									  unsigned short digitalMode,
									  unsigned int frequency) // in Khz
{
#if 0
    unsigned int FinKhz;
	int maxChannel, i;
	int result=XC_RESULT_RESET_FAILURE;

    if (frequency < 30000 || frequency > 900000)
		return XC_RESULT_RESET_FAILURE;

    maxChannel = new_channel_map_ptr->nb_channels;

	if ((maxChannel < 0) || (maxChannel > 200))
		return XC_RESULT_RESET_FAILURE;

    st->XC5000_current_channel_map_ptr = new_channel_map_ptr;

	DibDbgPrint( "xc5000_initialize_Standard maxChannel = %d\n ", maxChannel);
    DibDbgPrint( "xc5000 try to TUNE at Frequency = %d Khz\n ", frequency);

	for (i=0; i<maxChannel; i++) {
		FinKhz = (new_channel_map_ptr->channels[i].frequency * 15625) / 1000;

        DibDbgPrint( "ChannelMapping FinKhz = %d Khz ", FinKhz);

		if (frequency >= FinKhz) {
			if ((frequency - FinKhz) < 5000 ) {
				result = XC_RESULT_SUCCESS;
				break;
			}
		} else
			break;
	}

	DibDbgPrint( "Channel F = %d Khz, request Frequency = %d Khz ",FinKhz, frequency);

    if (result != XC_RESULT_SUCCESS)
		return XC_RESULT_RESET_FAILURE;

	result = xc5000_SetTVStandard(st, new_tv_std_ptr->VideoMode, new_tv_std_ptr->AudioMode);

    result |= xc5000_set_RF_frequency(st, FinKhz);
//	    xc5000_wait(100); // need if register 0x10

    if (result != XC_RESULT_SUCCESS)
		return XC_RESULT_RESET_FAILURE;


	if (digitalMode) {
        result |= xc5000_set_IF_frequency(st, st->ifFrequencyKhz); // to be checked in case analog
        result |= xc5000_go(st, modeTrans, 0x8a);
	} else {
		if (xc5000_WaitForLock(st) != 1) {
			result = XC_RESULT_RESET_FAILURE;
		} else {
            result = xc5000_go(st, modeTrans, 9);
		}
	}

    return result;
#endif
    return DIB_RETURN_ERROR;
}


#if 0
static int xc5000_get_monitoring(struct dibFrontend *fe, struct xc5000_monitor *m)
{
    struct xc5000_state *st = fe->tuner_priv;

    xc_get_version(st, &m->ver[0], &m->ver[1], &m->ver[2], &m->ver[3]);
    xc_get_product_id(st, &m->pid);

    xc_get_lock_status(st, &m->lock);
    //xc_get_frequency_error(st, &m->freq_error);
    xc_get_quality(st, &m->quality);
    //xc_get_hsync_freq(st, &m->hsync_freq_hz);
    xc_get_frame_lines(st, &m->frame_lines);

    return DIB_RETURN_SUCCESS;
}
#endif
#endif
