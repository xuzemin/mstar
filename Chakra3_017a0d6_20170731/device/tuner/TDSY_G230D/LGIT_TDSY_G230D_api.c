/****************************************************************************
*
* 							LG Innotek Co.,Ltd.
*
* Copyright (C) 2012, LG Innotek, Gwangju, Korea, All Rights Reserved.
*
* File: LGIT_TDSY_G230D_api.c
*
* version: 3.00.00
*
* Description: LGIT_TDSY_G230D Tuner API 
*
* Description			Version		Date		Author
* ---------------------------------------------------------------------
* Create				1.00.00		2012.03.28	JH.KIM
* Modify				1.10.00		2012.04.10	JH.KIM		Add DVB-T2 FEF - GPIO1 High for AGC freeze input
* Modify				2.00.00		2012.07.05	JH.KIM		Add ROM A3
* Modify				2.00.01		2012.07.18	JH.KIM		GPIO1_DRIVE_0 -> GPIO1_DISABLE
* Modify				2.00.02		2012.07.23	Warren		[DVB-C] RL Mode:Cable RL:31
* Modify				2.01.00		2012.07.26	JH.KIM		Firmware update: 0Eb9 -> 0Eb14, IR Gear: 8 -> 9
* Modify				3.00.00		2012.08.14	JH.KIM		Firmware update: 0Eb14 -> 0Eb15, Add ROM A20
****************************************************************************/

#include "LGIT_TDSY_G230D_api.h"

L1_Si2158_Context* Si2158;
L1_Si2158_Context front_end;
int return_code;
int addr;
unsigned char Si2158RomId;

void LGIT_TDSY_G230D_Open(void)
{
/* Local Variables */
	return_code=0;
	
/* For tuner */
	// Software Initialization (Initialize Level 1 and Level 0 Context) 
	Si2158 = &front_end;
	addr = 0xC0; //TDSY_G230D Tuner Address
	LGIT_bsp_i2c_init();
	Si2158_L1_API_Init(Si2158, addr);	

/* For Demodulator */
}

MS_BOOL LGIT_TDSY_G230D_Initialize(void)
{
/* Local Variables */
    MS_BOOL retb = TRUE;
/* For tuner */
	// Power UP
	if( (return_code = Si2158_Init(Si2158)) != 0)
	{
		LGIT_dbg("ERROR CODE : %d, Si2158_Init\n",return_code);	
        retb = FALSE;
	}
	Si2158RomId = Si2158->rsp->part_info.romid;
	
	// Load Firmware
	if(Si2158RomId == 0x31) {//A2
		if( (return_code = Si2158_LoadFirmware(Si2158, Si2158_FW_0_Lb8, SI2158_FIRMWARE_LINES_0_Lb8)) != 0)
		{
			LGIT_dbg("ERROR CODE : %d, Si2158_LoadFirmware\n",return_code);
            retb = FALSE;
		}
	} else if(Si2158RomId == 0x32) {//A3
		if( (return_code = Si2158_LoadFirmware(Si2158, Si2158_FW_0_Eb15, SI2158_FIRMWARE_LINES_0_Eb15)) != 0)
		{
			LGIT_dbg("ERROR CODE : %d, Si2158_LoadFirmware\n",return_code);
            retb = FALSE;
		}
	} else if(Si2158RomId == 0x33) {//A20
		if( (return_code = Si2158_LoadFirmware_16(Si2158, Si2158_FW_2_0bx, SI2158_FIRMWARE_LINES_2_0bx)) != 0)
		{
			LGIT_dbg("ERROR CODE : %d, Si2158_LoadFirmware\n",return_code);
            retb = FALSE;
		}
	} else {
		LGIT_dbg("Unknown Si2158 Rom ID: 0x%x\n", Si2158RomId);
        retb = FALSE;
	}

	// Start the Firmware
	if ( (return_code = Si2158_StartFirmware(Si2158)) != 0)
	{
		LGIT_dbg("ERROR CODE : %d, Si2158_StartFirmware\n",return_code);
        retb = FALSE;
	}

	// Config Pins
	 if ( (return_code = Si2158_L1_CONFIG_PINS (Si2158, 		
                                      Si2158_CONFIG_PINS_CMD_GPIO1_MODE_DISABLE,
                                      Si2158_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                      Si2158_CONFIG_PINS_CMD_GPIO2_MODE_DRIVE_0,
                                      Si2158_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                      Si2158_CONFIG_PINS_CMD_RESERVED1_RESERVED,
                                      Si2158_CONFIG_PINS_CMD_RESERVED2_RESERVED,
                			   Si2158_CONFIG_PINS_CMD_RESERVED3_RESERVED)) !=0)
	{
        	LGIT_dbg("ERROR CODE : %d, Si2158_L1_CONFIG_PINS Error\n",return_code);
            retb = FALSE;
	}

	// Set ATV startup configuration
	setupATVDefaults (Si2158);
	// Set Common Properties startup configuration
	setupCOMMONDefaults (Si2158);
	// Set DTV startup configuration
	setupDTVDefaults (Si2158);
	// Set Tuner Properties startup configuration
	setupTUNERDefaults (Si2158);
	
	if (0 == return_code)
	{
		LGIT_dbg("Initialize OK Part : %d, Version : %c.%c, RomID : %x\n", Si2158->rsp->part_info.part, Si2158->rsp->part_info.pmajor, Si2158->rsp->part_info.pminor, Si2158->rsp->part_info.romid);
	}
    return retb;

/* For Demodulator */
}

void LGIT_TDSY_G230D_ChangeStandard(Lgit_tuner_standard_t standard, Lgit_tuner_bandwidth_t bandwidth)
 {
 /* Local Variables */
	int i, j;
	unsigned char ucSts;
	unsigned char cAGC223_ALT5[3][16] = 
	{{0xb8, 0x26, 0xc0, 0x0c, 0x0c, 0x00, 0x00, 0xf6, 0x8c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f},
	{0xb9, 0xd0, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x01, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0xb9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x76, 0x08, 0x00, 0x00}};

 /* For Tuner */
	if(standard >= LGIT_TUNER_STD_PAL_B) //ATV 
	{
		for(i = 0; i<=2; i++){
			LGIT_bsp_i2c_write(addr, &(cAGC223_ALT5[i][0]), 16);
			for(j=0; j<100; j++)
			{
				LGIT_bsp_i2c_read(addr, &ucSts, 1);
				if(ucSts & 0x80)
				{
					break;
				}
				LGIT_sleep(1);
			}
		}
	}

 	switch(bandwidth)
	{
		case LGIT_TUNER_BW_6MHz:
			Si2158->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_6MHZ;
			break;
		case LGIT_TUNER_BW_7MHz:
			Si2158->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_7MHZ;
			break;
		case LGIT_TUNER_BW_8MHz:
			Si2158->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_8MHZ;
			break;
		default:
			Si2158->prop->dtv_mode.bw = Si2158_DTV_MODE_PROP_BW_BW_8MHZ;
			break;
	}
	
	switch(standard)
	{
		case LGIT_TUNER_STD_8VSB:
			Si2158->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_ATSC;		
			Si2158->prop->dtv_agc_freeze_input.level           = Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW;
  			Si2158->prop->dtv_agc_freeze_input.pin             = Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE;
			Si2158->prop->dtv_lif_freq.offset                  =  C_Si2158_IF_FREQUENCY_8VSB;//5000; 
			Si2158->prop->dtv_lif_out.amp                      =    30;
			Si2158->prop->dtv_agc_speed.if_agc_speed           = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->dtv_agc_speed.agc_decim              = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
			//Si2158->prop->dtv_rf_top.dtv_rf_top                = Modified in Tune Function;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;

		case LGIT_TUNER_STD_DVBT:
			Si2158->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBT;		
			Si2158->prop->dtv_agc_freeze_input.level           = Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW;
  			Si2158->prop->dtv_agc_freeze_input.pin             = Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE;
			Si2158->prop->dtv_lif_freq.offset                  =  C_Si2158_IF_FREQUENCY_DVBT;//5000; 
			Si2158->prop->dtv_lif_out.amp                      =    27;//30;
			Si2158->prop->dtv_agc_speed.if_agc_speed           = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->dtv_agc_speed.agc_decim              = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
			//Si2158->prop->dtv_rf_top.dtv_rf_top                = Modified in Tune Function;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_DVBT2:	
			Si2158->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBT;	
			Si2158->prop->dtv_agc_freeze_input.level           = Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_HIGH;
  			Si2158->prop->dtv_agc_freeze_input.pin             = Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_GPIO1;
			Si2158->prop->dtv_lif_freq.offset                  =  C_Si2158_IF_FREQUENCY_DVBT2;//5000; 
			Si2158->prop->dtv_lif_out.amp                      =    39;//30;
			Si2158->prop->dtv_agc_speed.if_agc_speed           = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->dtv_agc_speed.agc_decim              = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF;
			//Si2158->prop->dtv_rf_top.dtv_rf_top                = Modified in Tune Function;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_USQAM:
			Si2158->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_QAM_US;
			Si2158->prop->dtv_agc_freeze_input.level           = Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW;
  			Si2158->prop->dtv_agc_freeze_input.pin             = Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE;
			Si2158->prop->dtv_lif_freq.offset                  = C_Si2158_IF_FREQUENCY_USQAM;//5000; 
			Si2158->prop->dtv_lif_out.amp                      =    30;
			Si2158->prop->dtv_agc_speed.if_agc_speed           = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->dtv_agc_speed.agc_decim              = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF; 
			Si2158->prop->dtv_rf_top.dtv_rf_top                = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;			
		case LGIT_TUNER_STD_DVBC:
			Si2158->prop->dtv_mode.modulation = Si2158_DTV_MODE_PROP_MODULATION_DVBC;
			Si2158->prop->dtv_agc_freeze_input.level           = Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW;
  			Si2158->prop->dtv_agc_freeze_input.pin             = Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE;
			Si2158->prop->dtv_lif_freq.offset                  =  C_Si2158_IF_FREQUENCY_DVBC;;//5000; 
			Si2158->prop->dtv_lif_out.amp                      =    30;
			Si2158->prop->dtv_agc_speed.if_agc_speed           = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->dtv_agc_speed.agc_decim              = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF; 
			Si2158->prop->dtv_rf_top.dtv_rf_top                = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 31;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_CABLE;
			break;
		case LGIT_TUNER_STD_PAL_B:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_B; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   =     1; //custom
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO;
			Si2158->prop->atv_pga_target.pga_target            =     2; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =   102; 
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_PAL_G:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_GH; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   =     1; //custom
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO;
			Si2158->prop->atv_pga_target.pga_target            =     2; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =   102;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_PAL_I:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_I; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   =     1; //custom
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO;
			Si2158->prop->atv_pga_target.pga_target            =     2; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =   102;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_PAL_D:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_DK; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   =     1; //custom
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO;
			Si2158->prop->atv_pga_target.pga_target            =     2; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =   102;
			//Si2158->prop->tuner_lo_injection.band_1			   = Modified in Tune Function;
			//Si2158->prop->tuner_lo_injection.band_2			   = Modified in Tune Function;
			//Si2158->prop->tuner_lo_injection.band_3			   = Modified in Tune Function;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_SECAM_L:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_L; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   = Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_M11DB;
			Si2158->prop->atv_pga_target.pga_target            =     2; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =   102;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_SECAM_LP:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LP;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_SECAM;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_L1; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   = Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO;
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_M11DB;
			Si2158->prop->atv_pga_target.pga_target            =     2; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_ENABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =   102;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		case LGIT_TUNER_STD_NTSC:
		case LGIT_TUNER_STD_PAL_M:
			Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;
			Si2158->prop->atv_video_mode.color = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;
			Si2158->prop->atv_lif_freq.offset                  =  C_Si2158_IF_CENTER_M; 
			Si2158->prop->atv_lif_out.amp                      =    39;
			Si2158->prop->atv_agc_speed.if_agc_speed		   =     1; //custom
			Si2158->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO;
			Si2158->prop->atv_pga_target.pga_target            =     0; 
			Si2158->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE; 	
			Si2158->prop->atv_vsnr_cap.atv_vsnr_cap            =     0;
			Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
			Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			Si2158->prop->tuner_return_loss.config		= 127;
			Si2158->prop->tuner_return_loss.mode 		= Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL;			
			break;
		default:
			break;			
	}	

  LGIT_dbg("Si2158_downloadAllProperties\n");
  LGIT_dbg("%d \n",Si2158->prop->atv_afc_range.range_khz);
  LGIT_dbg("%d \n",Si2158->prop->atv_agc_speed.if_agc_speed);
  LGIT_dbg("%d \n",Si2158->prop->atv_agc_speed_low_rssi.if_agc_speed);
  LGIT_dbg("%d \n",Si2158->prop->atv_ext_agc.max_10mv);
  LGIT_dbg("%d \n",Si2158->prop->atv_ext_agc.min_10mv);
  LGIT_dbg("%d \n",Si2158->prop->atv_lif_freq.offset);
  LGIT_dbg("%d \n",Si2158->prop->atv_lif_out.offset);
  LGIT_dbg("%d \n",Si2158->prop->atv_lif_out.amp);
  LGIT_dbg("%d \n",Si2158->prop->atv_video_mode.invert_spectrum);
  LGIT_dbg("%d \n",Si2158->prop->dtv_lif_freq.offset);
  LGIT_dbg("%d \n",Si2158->prop->dtv_lif_out.offset);
  LGIT_dbg("%d \n",Si2158->prop->dtv_mode.invert_spectrum);
	if ( (return_code = Si2158_downloadAllProperties(Si2158)) != 0)
	{
		LGIT_dbg("ERROR CODE : %d, Si2158_downloadAllProperties",return_code);
	}

/* For Demodulator */
}
#if 0
void LGIT_TDSY_G230D_PreSet(
                 unsigned int RfFreqKHz, 
                 Lgit_tuner_standard_t standard, 
                 Lgit_tuner_bandwidth_t bandwidth)
 {
 	;
 }
#endif
void LGIT_TDSY_G230D_Tune(
                 unsigned int RfFreqKHz, 
                 Lgit_tuner_standard_t standard,
                 Lgit_tuner_bandwidth_t bandwidth)
 {
 /* Local Variables */
 	unsigned long freq = 0; //Hz Unit
    //printf("LGIT_TDSY_G230D_Tune %ld\n",RfFreqKHz);
/* For Tuner */
	if(RfFreqKHz < 300000 && standard==LGIT_TUNER_STD_PAL_B)
	{
		standard = LGIT_TUNER_STD_PAL_B;
		LGIT_TDSY_G230D_ChangeStandard(standard, bandwidth);
	}
	else if(RfFreqKHz >= 300000 && standard==LGIT_TUNER_STD_PAL_B)
	{
		LGIT_dbg("Error Over 300MHz is PAL G\n");
		standard = LGIT_TUNER_STD_PAL_G;
		LGIT_TDSY_G230D_ChangeStandard(standard, bandwidth);
	}
	else if (RfFreqKHz < 300000 && standard==LGIT_TUNER_STD_PAL_G)
	{
		LGIT_dbg("Error Under 300MHz is PAL B\n");
		standard = LGIT_TUNER_STD_PAL_B;
		LGIT_TDSY_G230D_ChangeStandard(standard, bandwidth);
	}
	else if (RfFreqKHz >= 300000 && standard==LGIT_TUNER_STD_PAL_G)
	{
		standard = LGIT_TUNER_STD_PAL_G;
		LGIT_TDSY_G230D_ChangeStandard(standard, bandwidth);
	}

	//Make input frequency to center frequency
	switch(standard)
	{
		case LGIT_TUNER_STD_8VSB: //ATSC
			freq = (long)(RfFreqKHz*1000);

			if(RfFreqKHz < 470499) { //Band 1,2
				Si2158->prop->dtv_rf_top.dtv_rf_top = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB;
			} else { //Band 3
				Si2158->prop->dtv_rf_top.dtv_rf_top = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_P2DB;
			}
			Si2158_L1_SetProperty2(Si2158, Si2158_DTV_RF_TOP_PROP);	
			break;			

		case LGIT_TUNER_STD_DVBT:
			freq = (long)(RfFreqKHz*1000);

			if(RfFreqKHz < 470499) { //Band 1,2
				Si2158->prop->dtv_rf_top.dtv_rf_top = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB;
			} else { //Band 3
				Si2158->prop->dtv_rf_top.dtv_rf_top = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_P2DB;
			}
			Si2158_L1_SetProperty2(Si2158, Si2158_DTV_RF_TOP_PROP);	
			break;			
		case LGIT_TUNER_STD_DVBT2:
			freq = (long)(RfFreqKHz*1000);

			if(RfFreqKHz < 470499) { //Band 1,2
				Si2158->prop->dtv_rf_top.dtv_rf_top = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_M5DB;
			} else { //Band 3
				Si2158->prop->dtv_rf_top.dtv_rf_top = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_P2DB;
			}
			Si2158_L1_SetProperty2(Si2158, Si2158_DTV_RF_TOP_PROP);	
			break;			
		case LGIT_TUNER_STD_DVBC:	
			freq = (long)(RfFreqKHz*1000);			
			break;
		case LGIT_TUNER_STD_USQAM:
			freq = (long)(RfFreqKHz*1000);			
			break;	
		case LGIT_TUNER_STD_PAL_B:
			freq = (long)((RfFreqKHz+2250)*1000);
			break;
		case LGIT_TUNER_STD_PAL_G:
			freq = (long)((RfFreqKHz+2750)*1000);
			break;
		case LGIT_TUNER_STD_PAL_I:
			freq = (long)((RfFreqKHz+2750)*1000);
			break;
		case LGIT_TUNER_STD_PAL_D:
			freq = (long)((RfFreqKHz+2750)*1000);

			if(RfFreqKHz < 190499) { //Band 1
				Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE;
				Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_HIGH_SIDE;
				Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_HIGH_SIDE;
			} else { //Band 2,3
				Si2158->prop->tuner_lo_injection.band_1			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_LOW_SIDE;
				Si2158->prop->tuner_lo_injection.band_2			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE;
				Si2158->prop->tuner_lo_injection.band_3			   = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE;
			}
			Si2158_L1_SetProperty2(Si2158, Si2158_TUNER_LO_INJECTION_PROP);	
			break;
		case LGIT_TUNER_STD_SECAM_L:
			freq = (long)((RfFreqKHz+2750)*1000);
			break;
		case LGIT_TUNER_STD_SECAM_LP:
			freq = (long)((RfFreqKHz-2750)*1000);
			break;
		case LGIT_TUNER_STD_NTSC:
		case LGIT_TUNER_STD_PAL_M:
			freq = (long)((RfFreqKHz+1750)*1000);
			break;
		default:
			break;
	}
 	
	if(standard > 19) //ATV
	{
		return_code = Si2158_Tune(Si2158, Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq);
	}
	else //DTV
	{
		return_code = Si2158_Tune(Si2158, Si2158_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq);
	}

	if(return_code)
	{
		LGIT_dbg("ERROR CODE : %d, Si2158_Tune\n",return_code);
	}

/* For Demodulator */
 }
#if 0
void LGIT_TDSY_G230D_PostSet(
                  unsigned int RfFreqKHz, 
                  Lgit_tuner_standard_t standard, 
                  Lgit_tuner_bandwidth_t bandwidth)
{
	; //for future use
}
#endif
void LGIT_TDSY_G230D_MonitorTuner(Lgit_tuner_standard_t standard, int *TuneComplete, int *InputLevel, int *AtvTunerLockStatus,int *AtvOffset)
{
	LGIT_sleep(10);
	
	if ( (return_code = Si2158_L1_TUNER_STATUS (Si2158, Si2158_TUNER_STATUS_CMD_INTACK_CLEAR)) != 0)
	{
		LGIT_dbg("ERROR CODE : %d,  Si2158_L1_TUNER_STATUS\n",return_code);
	}
	*InputLevel = Si2158->rsp->tuner_status.rssi; //dBm unit, 2's complement number
	*TuneComplete = Si2158->rsp->tuner_status.tc; // 0:busy, 1:done

	if(standard >= LGIT_TUNER_STD_PAL_B) //Only for ATV
	{
		if ( (return_code = Si2158_L1_ATV_STATUS (Si2158, Si2158_ATV_STATUS_CMD_INTACK_CLEAR)) != 0)
		{
			LGIT_dbg("ERROR CODE : %d,  Si2158_L1_ATV_STATUS\n", return_code);
		}
		*AtvOffset= Si2158->rsp->atv_status.afc_freq; //KHz unit
		*AtvTunerLockStatus = Si2158->rsp->atv_status.chl; // 0:UNLOCK, 1:LOCK	
	}	
}

void LGIT_TDSY_G230D_GetTunerSettings(void)
{
	char buff[1024];
	char separator[10] = "\n  ";

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_AFC_RANGE_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_AGC_SPEED_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

if(Si2158RomId >= 0x32) {
	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);
	
	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_ARTIFICIAL_SNOW_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);
}

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_CONFIG_IF_PORT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_EXT_AGC_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_IEN_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_INT_SENSE_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

if(Si2158RomId >= 0x32) {
	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_IR_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);
}

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_IRCAL_DRIFT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_IRCAL_MON_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_LIF_FREQ_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_LIF_OUT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_MIN_LVL_LOCK_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_PGA_TARGET_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_RF_TOP_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_VIDEO_MODE_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_ATV_VSNR_CAP_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_CRYSTAL_TRIM_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DEBUG_SAMPLE_FREQ_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_AGC_FREEZE_INPUT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_AGC_SPEED_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_CONFIG_IF_PORT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_EXT_AGC_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_FILTER_SELECT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_IEN_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_INITIAL_AGC_SPEED_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_INTERNAL_ZIF_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_INT_SENSE_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_LIF_FREQ_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_LIF_OUT_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_MODE_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_PGA_LIMITS_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_PGA_TARGET_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_RF_TOP_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_MASTER_IEN_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_TUNER_BLOCKED_VCO_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);
	
	Si2158_L1_GetPropertyString(Si2158, Si2158_TUNER_IEN_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_TUNER_INT_SENSE_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_TUNER_LO_INJECTION_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_GetPropertyString(Si2158, Si2158_TUNER_RETURN_LOSS_PROP, separator, buff);	
	LGIT_dbg("%s\n", buff);

	Si2158_L1_DTV_STATUS (Si2158, 1);
	Si2158_L1_GetCommandResponseString(Si2158, Si2158_DTV_STATUS_CMD_CODE, separator, buff);
	LGIT_dbg("%s\n", buff);
	
	Si2158_L1_ATV_STATUS (Si2158, 1);
	Si2158_L1_GetCommandResponseString(Si2158, Si2158_ATV_STATUS_CMD_CODE, separator, buff);
	LGIT_dbg("%s\n", buff);
	
	Si2158_L1_TUNER_STATUS (Si2158, 1);
	Si2158_L1_GetCommandResponseString(Si2158, Si2158_TUNER_STATUS_CMD_CODE, separator, buff);
	LGIT_dbg("%s\n", buff);
	
	Si2158_L1_GET_REV(Si2158);
	Si2158_L1_GetCommandResponseString(Si2158, Si2158_GET_REV_CMD_CODE, separator, buff);
	LGIT_dbg("%s\n", buff);

}

void LGIT_TDSY_G230D_Close(void)
{
	LGIT_bsp_i2c_close();
}

void setupATVDefaults        (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupATVDefaults       \n");
  api->prop->atv_afc_range.range_khz              =  1000; /* (default  1000) */

  api->prop->atv_agc_speed.if_agc_speed           = Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO; /* (default 'AUTO') */

  api->prop->atv_agc_speed_low_rssi.if_agc_speed  = Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  api->prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */

  api->prop->atv_artificial_snow.gain             = Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_AUTO   ; /* (default 'AUTO') */
  api->prop->atv_artificial_snow.offset           =     0; /* (default     0) */

  api->prop->atv_config_if_port.atv_out_type      = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_DIFF_IF1   ;  /* (default 'LIF_DIFF_IF2') */
  api->prop->atv_config_if_port.atv_agc_source    = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_AGC1_3DB     ;  /* (default 'INTERNAL') */

  api->prop->atv_ext_agc.min_10mv                 =    50; /* (default    50) */
  api->prop->atv_ext_agc.max_10mv                 =   200; /* (default   200) */

  api->prop->atv_ien.chlien                       = Si2158_ATV_IEN_PROP_CHLIEN_ENABLE ; /* (default 'ENABLE') */
  api->prop->atv_ien.pclien                       = Si2158_ATV_IEN_PROP_PCLIEN_DISABLE ; /* (default 'DISABLE') */

  api->prop->atv_int_sense.chlnegen               = Si2158_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.pclnegen               = Si2158_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.chlposen               = Si2158_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->atv_int_sense.pclposen               = Si2158_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE  ; /* (default 'ENABLE') */

if(Si2158RomId >= 0x32) {
  api->prop->atv_ir.gear                          =     9; /* (default     8) */
  api->prop->atv_ir.filter                        = Si2158_ATV_IR_PROP_FILTER_CUSTOM_FILTERS ; /* (default 'CUSTOM_FILTERS') */
}

  api->prop->atv_ircal_drift.step_limit           =    10; /* (default    10) */
  api->prop->atv_ircal_drift.dead_zone            =    25; /* (default    25) */

  api->prop->atv_ircal_mon.expiration_fields      =   120; /* (default   120) */
  api->prop->atv_ircal_mon.disable_threshold      =   160; /* (default   255) */

  api->prop->atv_lif_freq.offset                  =  5000; /* (default  5000) */

  api->prop->atv_lif_out.offset                   =   100; /* (default   148) */
  api->prop->atv_lif_out.amp                      =   100; /* (default   100) */

  api->prop->atv_min_lvl_lock.thrs                =    34; /* (default    34) */

  api->prop->atv_pga_target.pga_target            =     0; /* (default     0) */
  api->prop->atv_pga_target.override_enable       = Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */

  api->prop->atv_rf_top.atv_rf_top                = Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO ; /* (default 'AUTO') */

  api->prop->atv_rsq_rssi_threshold.lo            =   -86; /* (default   -70) */
  api->prop->atv_rsq_rssi_threshold.hi            =     0; /* (default     0) */

  api->prop->atv_video_mode.video_sys             = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B              ; /* (default 'B') */
  api->prop->atv_video_mode.color                 = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC           ; /* (default 'PAL_NTSC') */
  api->prop->atv_video_mode.invert_spectrum       = Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM_INVERTED ; /* (default 'INVERTED') */

  api->prop->atv_vsnr_cap.atv_vsnr_cap            =     0; /* (default     0) */

}

void setupCOMMONDefaults     (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupCOMMONDefaults    \n");
if(Si2158RomId == 0x31)
  api->prop->crystal_trim.xo_cap                  =    9;  /* (default     12) */
if(Si2158RomId >= 0x32)
  api->prop->crystal_trim.xo_cap                  =    9;  /* (default     8) */

  api->prop->master_ien.tunien                    = Si2158_MASTER_IEN_PROP_TUNIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.atvien                    = Si2158_MASTER_IEN_PROP_ATVIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.dtvien                    = Si2158_MASTER_IEN_PROP_DTVIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.errien                    = Si2158_MASTER_IEN_PROP_ERRIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.ctsien                    = Si2158_MASTER_IEN_PROP_CTSIEN_OFF ; /* (default 'OFF') */

}

void setupDTVDefaults        (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupDTVDefaults       \n");
  api->prop->dtv_agc_freeze_input.level           = Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW  ; /* (default 'LOW') */
  api->prop->dtv_agc_freeze_input.pin             = Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   ; /* (default 'NONE') */

  api->prop->dtv_agc_speed.if_agc_speed           = Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  api->prop->dtv_agc_speed.agc_decim              = Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */

  api->prop->dtv_config_if_port.dtv_out_type      = Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1   ; /* (default 'LIF_IF1') */
  api->prop->dtv_config_if_port.dtv_agc_source    = Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_AGC1_3DB; /* (default     0) */

  api->prop->dtv_ext_agc.min_10mv                 =    50; /* (default    50) */
  api->prop->dtv_ext_agc.max_10mv                 =   200; /* (default   200) */

if(Si2158RomId == 0x31)
  api->prop->dtv_filter_select.filter             = Si2158_DTV_FILTER_SELECT_PROP_FILTER_LEGACY ; /* (default 'LEGACY') */
if(Si2158RomId >= 0x32)
  api->prop->dtv_filter_select.filter             = Si2158_DTV_FILTER_SELECT_PROP_FILTER_CUSTOM1 ; /* (default 'CUSTOM1') */

  api->prop->dtv_ien.chlien                       = Si2158_DTV_IEN_PROP_CHLIEN_ENABLE ; /* (default 'ENABLE') */

  api->prop->dtv_initial_agc_speed.if_agc_speed   = Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  api->prop->dtv_initial_agc_speed.agc_decim      = Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */

  api->prop->dtv_initial_agc_speed_period.period  =     0; /* (default     0) */

  api->prop->dtv_internal_zif.atsc                = Si2158_DTV_INTERNAL_ZIF_PROP_ATSC_LIF   ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.qam_us              = Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US_LIF ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.dvbt                = Si2158_DTV_INTERNAL_ZIF_PROP_DVBT_LIF   ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.dvbc                = Si2158_DTV_INTERNAL_ZIF_PROP_DVBC_LIF   ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.isdbt               = Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT_LIF  ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.isdbc               = Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC_LIF  ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.dtmb                = Si2158_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */

  api->prop->dtv_int_sense.chlnegen               = Si2158_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->dtv_int_sense.chlposen               = Si2158_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->dtv_lif_freq.offset                  =  5000; /* (default  5000) */

  api->prop->dtv_lif_out.offset                   =   148; /* (default   148) */
  api->prop->dtv_lif_out.amp                      =    27; /* (default    27) */

  api->prop->dtv_mode.bw                          = Si2158_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  api->prop->dtv_mode.modulation                  = Si2158_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  api->prop->dtv_mode.invert_spectrum             =     0; /* (default     0) */

if(Si2158RomId == 0x31) {
  api->prop->dtv_pga_limits.min                   =     0; /* (default     0) */
  api->prop->dtv_pga_limits.max                   =    56; /* (default    56) */
}
if(Si2158RomId >= 0x32) {
	api->prop->dtv_pga_limits.min                   =     -1; /* (default     -1) */
	api->prop->dtv_pga_limits.max                   =    -1; /* (default    -1) */
}

  api->prop->dtv_pga_target.pga_target            =     0; /* (default     0) */
  api->prop->dtv_pga_target.override_enable       = Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */

  api->prop->dtv_rf_top.dtv_rf_top                = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */

  api->prop->dtv_rsq_rssi_threshold.lo            =   -80; /* (default   -80) */
  api->prop->dtv_rsq_rssi_threshold.hi            =     0; /* (default     0) */

  api->prop->dtv_zif_dc_canceller_bw.bandwidth    = Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_DEFAULT ; /* (default 'DEFAULT') */

}

void setupTUNERDefaults      (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupTUNERDefaults     \n");
  api->prop->debug_sample_freq.fs_mhz             =     0; /* (default     0) */

  api->prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */

  api->prop->tuner_ien.tcien                      = Si2158_TUNER_IEN_PROP_TCIEN_ENABLE    ; /* (default 'DISABLE') */
  api->prop->tuner_ien.rssilien                   = Si2158_TUNER_IEN_PROP_RSSILIEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_ien.rssihien                   = Si2158_TUNER_IEN_PROP_RSSIHIEN_DISABLE ; /* (default 'DISABLE') */

  api->prop->tuner_int_sense.tcnegen              = Si2158_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE    ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.rssilnegen           = Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.rssihnegen           = Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.tcposen              = Si2158_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE     ; /* (default 'ENABLE') */
  api->prop->tuner_int_sense.rssilposen           = Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->tuner_int_sense.rssihposen           = Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->tuner_lo_injection.band_1            = Si2158_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  api->prop->tuner_lo_injection.band_2            = Si2158_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  api->prop->tuner_lo_injection.band_3            = Si2158_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */

  api->prop->tuner_return_loss.config             = Si2158_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  api->prop->tuner_return_loss.mode               = Si2158_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */

}

