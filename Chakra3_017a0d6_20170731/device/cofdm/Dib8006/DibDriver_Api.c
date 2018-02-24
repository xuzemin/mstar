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
#include "sip.h"
#include "dib8000.h"
#include "component_monitor.h"
#include "demod_parameters.h"
#include "DibDriver_Api.h"
#include "msAPI_Timer.h"
#include "msAPI_Memory.h"
#include "drvIIC.h"
#include "dib_monitor_dib7000.h"


static struct dib8000_config Nutune_dib8000_config = {
    1,   // output_mpeg2_in_188_bytes
    1,   // hostbus_diversity

    NULL, // update_lna

    1, // agc_config_count
    &xc5000_agc_config,  // agc
    &xc4000_bw_config_12mhz_ISDBT,//xc5000_bw_config_31_875MHz, // bw

    DIB8000_GPIO_DEFAULT_DIRECTIONS,
    DIB8000_GPIO_DEFAULT_VALUES,
    DIB8000_GPIO_DEFAULT_PWM_POS,
    0, // pwm_freq_div
    NULL,
    0,
    0,
    0,
    0,
};

/*static int default_nutune_reset(struct dibFrontend *fe)
{
    demod_set_gpio(fe, 8,0,0);
    DibMSleep(10);
    demod_set_gpio(fe, 8,0,1);
    dbgp("Nutune reset done\n");
    return 0;
}*/

/* configs for the xc5000 */
/*const struct fi4801_config default_fi4801_config = 
{
	0xC2,
	default_nutune_reset,
	1,
	31875
};*/

#if 0
static struct xc5000_config default_nutune_config = {
    DEFAULT_XC5000_I2C_ADDRESS, // i2c_address
    default_xc5000_reset,       // reset
    1,                          // fm_input
    //32000,                      // clock_khz
    31875,                      // clock_khz
};
#endif
static int DibDriver_I2C_Xfer(struct dibDataBusClient *client, struct dibDataBusAccess *msg)
{
	uint16_t addr;
	uint16_t sub_addr;
	uint32_t val;

	addr = data_bus_access_device_id(client, msg);//I2C Adde
	addr = (uint16_t)(addr & 0xFE);
	sub_addr = (msg->tx[0] << 8) & 0xFF00;
	sub_addr = (sub_addr | msg->tx[1]) & 0xFFFF;
	
	if (msg->rx == NULL || msg->rxlen == 0)
	{	//return spp_host_i2c_xfer_write(client, msg,1);
		val = (uint32_t)msg->tx[2];
		val <<= 8;
		val = val | msg->tx[3];

		//dbgp("DibDriver_I2C_Xfer +write add:0x%x subaddr:%d val:%d \n",addr, sub_addr, val);
		if(!MDrv_IIC_WriteBytes(addr, 2, (uint8_t*)msg->tx, (uint8_t)(msg->txlen-2), (uint8_t*)(msg->tx+2))){
			dbgp("DibDriver_I2C_Xfer +write ** error add:0x%x subaddr:%d val:%d \n",addr, sub_addr, val);
		}
		return 0; 
	}
	else{
		if(!MDrv_IIC_ReadBytes(addr, 2,(uint8_t*)msg->tx, msg->rxlen, msg->rx)){
			//dbgp("DibDriver_I2C_Xfer - read ** error \n");
		}
		val = (uint32_t)msg->rx[0];
		val <<= 8;
		val = val | msg->rx[1];
		if(msg->rxlen == 4){
			val <<= 8;
			val = val | msg->rx[2];
			val <<= 8;
			val = val | msg->rx[3];
		}
//		dbgp("DibDriver_I2C_Xfer -read add:0x%x subaddr:%d val:%d \n",addr, sub_addr, val);
		return  0;
	}

}

static int DibDriver_I2CInit(struct dibDataBusHost *i2c)
{
	int ret;

	ret = data_bus_host_init(i2c, DATA_BUS_I2C, DibDriver_I2C_Xfer, NULL);

	return ret;
}


struct dibFrontend frontend;
struct dibDataBusHost *dib_i2c = NULL;
//extern struct dibFrontend * fi4801_register(struct dibFrontend *fe, struct dibDataBusHost *i2c_adap, const struct fi4801_config *cfg);
static bool inited = FALSE;
int DibDriver_Init(void)
{	
	int ret;
//	struct dibDataBusHost *i2c;

/*	struct dibChannel channel;
    struct dibAnalogChannel  achannel;
	struct dibDemodMonitor mon;
    unsigned char tune_in_digital = 0;*/
	

	

	if(dib_i2c == NULL)
	{
		dib_i2c = MemAlloc(sizeof(struct dibDataBusHost));
	}
	if(!inited){
	//	default_nutune_reset(&frontend);
	    frontend_init(&frontend); /* initializing the frontend-structure */
	    frontend_set_id(&frontend, 0); /* assign an absolute ID to the frontend */
	    frontend_set_description(&frontend, "ISDB-T #0");
		
		ret = DibDriver_I2CInit(dib_i2c);
		if(ret){
			return DIBDRIVER_ERROR;
		}
	    if (dib8000_register(&frontend, dib_i2c,  0x90, &Nutune_dib8000_config) == NULL) {
	        DibDbgPrint("-E-  can not register dib8000\n");
	        return 1;
	    }
		inited= TRUE;
	}

#if 0
    i2c = dib8000_get_i2c_master(&frontend, DIBX000_I2C_INTERFACE_TUNER, 1);
    if (fi4801_register((struct dibFrontend *)&frontend, i2c, (const struct fi4801_config *)&default_fi4801_config) == NULL) {
        DibDbgPrint("-E-  can not register fi4801\n");
        return 1;
    }
#endif
    dib8000_i2c_enumeration(dib_i2c, 1, DEFAULT_DIB8000_I2C_ADDRESS, 0x90); /* do the i2c-enumeration for the dib8000 and use 0x90 as the I2C address */

    frontend_reset(&frontend);


	return DIBDRIVER_SUCCESS;
}

int DibDriver_Tune(int Freq, int bw, bool tune_digital)
{
	struct dibChannel channel;
 /*   struct dibAnalogChannel  achannel;
	struct	dibDVBSignalStatus status;
	struct dibDemodMonitor mon;
	uint8_t num;*/

   	bw = bw;// for complie error

    if (tune_digital) {
        // tuning in digital
        INIT_CHANNEL(&channel, STANDARD_ISDBT);
        channel.RF_kHz           = Freq;
        channel.bandwidth_kHz    = 6000;
		dbgp("DibDriver_Tune, freq: %d \n", channel.RF_kHz);
        tune_diversity(&frontend, 1, &channel);
		DibMSleep(200);
    }
    else {

#if 0
        // tuning in analog
        INIT_ANALOG_CHANNEL(&achannel);
        achannel.RF_kHz        = 479250;
        achannel.TunerStandard = AnalogVideo_SECAM_L;
        achannel.CountryCode   = 33;
        achannel.Cable         = 0;

        tuner_tune_analog(&frontend, &achannel);
#endif
    }
	return DIBDRIVER_SUCCESS;
}


#define DIBDRIVER_ENABLE_MONIT   TRUE
int DibDriver_CheckLock(void)
{
	struct	dibDVBSignalStatus status;
	struct dibDemodMonitor mon;
/*	uint32_t snr;
	uint8_t b[4];*/
#if DIBDRIVER_ENABLE_MONIT
	static int pre_time = 0;
	int cur_time;
#endif

	demod_get_signal_status(&frontend, &status);
	if(status.mpeg_data_lock == TRUE){
#if DIBDRIVER_ENABLE_MONIT
		cur_time = systime();		
		if((cur_time - pre_time) >= 2000){
			pre_time = cur_time;
			DibZeroMemory(&mon, sizeof(mon));
			demod_get_monitoring(&frontend, &mon);
			dib7000_print_monitor(&mon, NULL, 0 ,1);
		}
#endif
		return 1;
	}else{
		return 0;
	}
}

int DibDriver_GetSNR(void)
{
	struct dibDemodMonitor mon;
	
	DibZeroMemory(&mon, sizeof(mon));
	demod_get_monitoring(&frontend, &mon);
	return mon.CoN;
}

int DibDriver_GetSignalStrength(void)
{
	struct	dibDVBSignalStatus status;

	demod_get_signal_status(&frontend, &status);
	return status.signal_strength;

}

int DibDriver_Reset(void)
{
    return frontend_reset(&frontend);
}

#define QEF_LIMIT 200000
int DibDriver_GetSignalQuality(void)
{
	struct	dibDVBSignalStatus status;
	int quality;

	demod_get_signal_status(&frontend, &status);

	
	if(status.bit_error_rate > 900000){
		quality = 0;
	}else if(status.bit_error_rate <QEF_LIMIT/2){
		quality = 100-(5* status.bit_error_rate)/10000;
	}else{
		quality = 50-(5* status.bit_error_rate)/90000;
	}
	
	return quality;

}


int DibDriver_PassThrough(BOOL on)
{
	uint8_t data[6];
	uint16_t sub_addr;
	uint16_t val;

	
	
	if(on){
		sub_addr = 1028;
		data[0] = sub_addr >> 8 & 0xFF;
		data[1] = sub_addr & 0xFF;
		data[2] = 0;
		data[3] = 0;
		MDrv_IIC_WriteBytes(0x90, 2, data, 2, (data+2));
		val = ((0xC2) >> 1) << 9;
	}else{
		val = 1 << 8;
	}
	sub_addr = 1025;

	data[0] = sub_addr >> 8 & 0xFF;
	data[1] = sub_addr & 0xFF;
	data[2] = val >> 8 & 0xFF;
	data[3] = val & 0xFF;
	DibUSleep(1);
	MDrv_IIC_WriteBytes(0x90, 2, data, 2, (data+2));
	DibUSleep(1);
	return 0;
}

int DibDriver_TunerRead(unsigned char *data)
{
	DibDriver_PassThrough(1);
	MDrv_IIC_ReadBytes(0xC2,0,NULL,1,data);
	DibDriver_PassThrough(0);
	return 0;
}

int DibDriver_TunerWrite(unsigned char *data, int len)
{
	DibDriver_PassThrough(1);
	MDrv_IIC_WriteBytes(0xC2, 0, NULL, len, data);
	DibDriver_PassThrough(0);
	return 0;
}






