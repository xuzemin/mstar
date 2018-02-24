#include <string.h>
#include "nmiioctl.h"
#include "MsCommon.h"
//#include "HbCommon.h"
#include "Board.h"
#include "msAPI_Tuning.h"
#include "MApp_ATV_Scan.h"
#if(FRONTEND_TUNER_TYPE == NM_120V_TUNER)

#define XO_OUT_EN 1

#if 1
#define NMI_LOG		printf
#else
#define NMI_LOG		printf
#endif
extern uint32_t rReg32(uint16_t adr);
extern void wReg32(uint16_t adr, uint32_t val);
/*static void NMI120_ShowAsicPara(void)
{
	tTnrStatus status;

	if(nmi_drv_ctl(NMI_DRV_GET_STATUS,&status)<0)
	{
		printf("[NMI ASIC] Failed to get status!!!\n");
		return	;
	}
	
	printf("[NMI ASIC] AGC Lock: %d\n", status.ds.agclock);
	printf("[NMI ASIC] Dagc: %2.3f\n", ((double)status.ds.dagc)/(1ul << 15));

	printf("[NMI ASIC] Rssi: %3.2f dBm\n", status.gain.rssix100/100.0);
	
	printf("[NMI ASIC] Lna Code: %02x\n", (uint8_t)status.gain.lnacode);
	printf("[NMI ASIC] Lna Gain: %2.1f\n", status.gain.lnadbx100/100.0);

	printf("[NMI ASIC] BBLI Code: %02x\n", (uint8_t)status.gain.bblicode);
	printf("[NMI ASIC] BBLI Cain: %2.1f\n", status.gain.bblidbx100/100.0);

	return ;
}*/

MS_BOOL NMI120_LoopThrough(void);//Leo add
MS_BOOL MDrv_Tuner_Reset(void);//wang add
MS_BOOL devTunerInit(void)
{
	int result;
	tTnrInit cfg;
	memset((void *)&cfg, 0, sizeof(tTnrInit));

	cfg.ldobypass = 0;
	cfg.xo = 24000;
	//cfg.xo = 38400;
	cfg.i2c_adr = 0xce;
	cfg.init_bus_only = 0;
	cfg.xo_out_en = XO_OUT_EN;

	result = nmi_drv_ctl(NMI_DRV_INIT, (void *)&cfg);

	if(result < 0)
	{
		NMI_LOG(">> NMI_DRV_INIT failed. result = %d\n", result);
		return FALSE;
	}
	//Leo else
	{
		int chipid;
		tNmiDriverVer ver;

		nmi_drv_ctl(NMI_DRV_VERSION, &ver);
		NMI_LOG("[NMI] NMI 120,13x driver version (%d.%d.%d.%d) build %d\n", ver.major, ver.minor, ver.rev1, ver.rev2, ver.buildrev);

		nmi_drv_ctl(NMI_DRV_GET_CHIPID, &chipid);
		printf("[NMI] Chip ID = 0x%08x\n", chipid);

	}
	NMI120_LoopThrough();//Leo add
	return TRUE;
}

extern IF_FREQ MDrv_IFDM_GetIF(void);
extern void MDrv_IFDM_SetIF(IF_FREQ eIF_Freq);
static int nm130vsecamlflag = 0;//
void devAtvSecamlSetReg(void)
{
	//if(nm130vsecamlflag == 1)
	{
			uint32_t val32;
			uint32_t temp;
			val32 =  rReg32(0x210);
			temp = (val32>>16)&0x1ff;
			if(temp!=0x139ul)
			{
				val32 |= (0x139ul << 16);//swan
				wReg32(0x210,val32);
				printf("------------------devAtvSecamlSetReg temp= %d\n", temp);
			}
			//nm130vsecamlflag = 0;
	}
}
MS_BOOL devTunerSetPLLData(MS_U32 wPLLData, MS_U8 ucBw)//MHZ
{
	tTnrTune tune;
	//int rf_freq_offset_lut = 0;
	tNmiTvStd   std;

    double dRFfreq;
	int spectrum = 1;
    UNUSED(ucBw);
	
	memset((void *)&tune, 0, sizeof(tTnrTune));


    #if (TN_FREQ_STEP == FREQ_STEP_62_5KHz)
    dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*62.5);
    #elif (TN_FREQ_STEP == FREQ_STEP_50KHz)
    dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*50);
    #else
    dRFfreq = (double)((wPLLData-msAPI_Tuner_GetIF())*31.25);
    #endif 

	//NMI_LOG("\nSet Frequency: freq = (%d) KHz\n", (uint32_t)dRFfreq);

#if 1
	IF_FREQ CurrentStandard=MDrv_IFDM_GetIF();
printf("CurrentStandard = %d\n", CurrentStandard);

		tune.vif = 7000000;
	if(CurrentStandard==IF_FREQ_B) 
	{
		std = nPAL_G;
		tune.vif = 6400000;
		tune.rfinvert = 0;
		spectrum = 1;
	} 
	else if  (CurrentStandard==IF_FREQ_G) 
	{
		std = nPAL_G;
		tune.vif = 6400000;
		tune.rfinvert = 0;
		spectrum = 1;
	} 
	else if  (CurrentStandard==IF_FREQ_I) 
	{
		std = nPAL_I;
		tune.vif = 7250000;
		tune.rfinvert = 0;
		spectrum = 1;
	}
	else if  (CurrentStandard==IF_FREQ_DK) 
	{
		std = nPAL_K;
		tune.vif = 6850000;
		tune.rfinvert = 0;
		spectrum = 1;
	} 
	else if  (CurrentStandard==IF_FREQ_L) 
	{
	#if(ENABLE_130V_SECAML_ATVSCAN)
	printf("enATVScanState = %d\n", MApp_ATV_Scan_ScanState());
	if(MApp_ATV_Scan_ScanState() == STATE_ATV_SCAN_WAIT)
	{
		std = nPAL_K;
	}
	else
	{
		std = nSECAM_L;
	}
		
	#else
		std = nSECAM_L;
	#endif
		tune.vif = 6750000;
		tune.rfinvert = 0;
		spectrum = 1;
	} 
	else if  (CurrentStandard==IF_FREQ_L_PRIME) 
	{
		std = nSECAM_L;
		tune.vif = 6150000;
		tune.rfinvert = 1;
		spectrum = 0;
	
	} 
	else if  (CurrentStandard==IF_FREQ_MN) 
	{
		std = nPAL_M;
		tune.vif = 6400000;
		tune.rfinvert = 0;
		spectrum = 1;
	} 
	else
	{
		std = nPAL_K;
		tune.vif = 6850000;
		tune.rfinvert = 0;
		spectrum = 1;
		
	}
#endif
		
	tune.rf = dRFfreq*1000;

	#if(ENABLE_PALBG_48DOT25_SCAN)
	if(std == nPAL_K && tune.rf >= (48250000-250000) && tune.rf <= (48250000+250000))
	{
		std = nPAL_G;
		tune.vif = 6400000;
		tune.rfinvert = 0;
		spectrum = 1;
		msAPI_AUD_SetAudioStandard(E_AUDIOSTANDARD_BG);
		//MDrv_IFDM_SetIF(IF_FREQ_G);	
	}
	#endif

	//after tuning, exit from KEY_EXIT, the secam l' wrong
	#if(ENABLE_130V_SECAML_ATVSCAN)//因为130V对SECAM L/L'识别不准才这么做
	if((CurrentStandard==IF_FREQ_L ||CurrentStandard==IF_FREQ_L_PRIME ))
	{
		if(tune.rf <=66500000) 
		{
			std = nPAL_K;
			tune.vif = 6150000;
			tune.rfinvert = 1;
			spectrum = 0;
			MDrv_IFDM_SetIF(IF_FREQ_L_PRIME);	
		}
		else
		{
			if(MApp_ATV_Scan_ScanState() != STATE_ATV_SCAN_WAIT)
			{
				std = nSECAM_L;
				tune.vif = 6750000;
				tune.rfinvert = 0;
				spectrum = 1;
				MDrv_IFDM_SetIF(IF_FREQ_L);	
			}
		} 
		
	} 		
	#endif
	
	//tune.vif = 6900000;
	tune.std = std;
	
	
	tune.output = nIf;
	tune.dacSel = nDacDefault;
	//tune.rf += rf_freq_offset_lut; //work at ATV mode, no need

	if(nmi_drv_ctl(NMI_DRV_TUNE, &tune) < 0)
	{
		NMI_LOG("\n[NMI]>> Change Frequency Fail......\n");
		return FALSE;
	}
	else
	{
		
		//int if_outpur =90;//90; // 90 = output 150 mv

  		tTnrVideoAmp m_videoamp;
		if  (spectrum) 
			nmi_drv_ctl(NMI_DRV_INVERT_SPECTRUM, (void *)(&spectrum));
		
		if  (MDrv_IFDM_GetIF() == IF_FREQ_L_PRIME) 
		{
			wReg8(0x05,0x87);
			wReg8(0x35,0x5F);
			{
			      uint32_t val32;
				val32 =  rReg32(0x210);
				val32 |= (0x159ul << 16);//swan
				wReg32(0x210,val32);
				printf("------------------devAtvSecamlSetReg temp= %x\n", val32);
				MsOS_DelayTask(200);//add This!! If no this delay, Secam L/L'' will not be locked.
			}

		/*
			if(NMI120_GetRSSI(1)>80)
			{
 				m_videoamp.amp = SECAMLL_130V_HIGH_STRENGTH_VIDEOAMP;
				nmi_tnr_set_video_amp(&m_videoamp);
				MsOS_DelayTask(200);//add This!! If no this delay, Secam L/L'' will not be locked.
			}
			else
			{
 				m_videoamp.amp = SECAMLL_130V_LOW_STRENGTH_VIDEOAMP;
				nmi_tnr_set_video_amp(&m_videoamp);
			}
				*/
		}
		else if  (MDrv_IFDM_GetIF() == IF_FREQ_L) 
		{
 			m_videoamp.amp = 0;
			nmi_tnr_set_video_amp(&m_videoamp);
		}
		else
		{
 			m_videoamp.amp = 0;
			nmi_tnr_set_video_amp(&m_videoamp);
		}
		


		if(MDrv_IFDM_GetIF() == IF_FREQ_B)//song bin test,for atv 噪波
		{
		     if(tune.rf >= (49750000-250000) && tune.rf <= (49750000+250000))
		     {
				wReg8(0x36, 0x7c);
				NMI_LOG("\n[NMI]>> 0x36 = 0x7c. \n");
		     }
		}

	if( (CurrentStandard==IF_FREQ_B) && (tune.rf <= 48250000+250000)&&(tune.rf >= 48250000-250000)) //swan fix,recover sensitivity
		{
			wReg8(0x05,0x87);
			NMI_LOG("\n[NMI]>>swan write 0x05 = 0x87\n");
		}	

	if( (CurrentStandard==IF_FREQ_L) &&std == nSECAM_L) //swan fix,recover sensitivity
		{
			//wReg8(0x05,0x87);
			NMI_LOG("\n[NMI]>>CurrentStandard==IF_FREQ_L\n");
			nm130vsecamlflag = 0;
			if(NMI120_GetRSSI(1)>50)
			{
			      uint32_t val32;
				val32 =  rReg32(0x210);
				val32 &= ~(0x1fful << 16);
				wReg32(0x210,val32);
				nm130vsecamlflag = 1;
				MsOS_DelayTask(200);//add This!! If no this delay, Secam L/L'' will not be locked.
			}
			//wReg32(0x03,0x8f);//songbin 120518
		}

#if 1//Joe 120517
		//songbin changed 120517
		if(CurrentStandard==IF_FREQ_B
			||CurrentStandard==IF_FREQ_G
			||CurrentStandard==IF_FREQ_DK
			||CurrentStandard==IF_FREQ_L)//songbin 120518
		{
			wReg8(0x35,0x58);
		}
		else
		{
			wReg8(0x35,0x5f);
		}

		//if(CurrentStandard==IF_FREQ_B
		//	||CurrentStandard==IF_FREQ_G)
		//	wReg32(0x110,0x6c50);//songbin 120518
			
#endif			
			
		//nmi_drv_ctl(NMI_DRV_SET_IF_OUTPUT_VOLTAGE, (void *)(&if_outpur));
		NMI_LOG("\n[NMI]Change Frequency successful: freq = (%lu) Hz, IF = (%lu Hz) BW = (%d MHz ).\n", tune.rf, tune.vif, ucBw);
		
		//printf("--strength = %d--- r32 = 0x%x\n", NMI120_GetRSSI(0), rReg32(0x104));

		
		return TRUE;
	}
}



MS_BOOL devDtvTunerSetPLLData(MS_U32 dwFreq, MS_U8 ucBw)//MHZ
{
	tTnrTune tune;

	memset((void *)&tune, 0, sizeof(tTnrTune));
	tune.rf = dwFreq*100000;
//	tune.vif = 4570000;
//	tune.vif = 4800000 + 100000;
//	tune.vif = 4800000 - 100000;
#if(DTV_SYSTEM_SEL == DTV_SYSTEM_DTMB)//DTMB
	tune.vif = 4000000;
	tune.std = nDTV_8; 
#else
	switch(ucBw)
	{
		case 1: 
			tune.vif = 3250000;
			tune.std = nDTV_6; 
			break;
		case 2: 
			tune.vif = 4500000;
			tune.std = nDTV_7; 
			break;
		case 3:
		default:
			tune.vif = 4800000;
			tune.std = nDTV_8; 
			break;
	}
#endif

	tune.output = nIf;

	if(nmi_drv_ctl(NMI_DRV_TUNE, &tune) < 0)
	{
		NMI_LOG("\n[NMI]>> Change Frequency Fail......\n");
		return FALSE;
	}
	else
	{
//		int spectrum = 1;
		int if_outpur = 90;

		#if(DTV_SYSTEM_SEL == DTV_SYSTEM_DTMB)
  		tTnrVideoAmp m_videoamp;

  		m_videoamp.amp = 15;
		nmi_tnr_set_video_amp(&m_videoamp);
		#else
  		tTnrVideoAmp m_videoamp;

  		m_videoamp.amp = 5;
		nmi_tnr_set_video_amp(&m_videoamp);
		#endif
		//nmi_drv_ctl(NMI_DRV_INVERT_SPECTRUM, (void *)(&spectrum));
		nmi_drv_ctl(NMI_DRV_SET_IF_OUTPUT_VOLTAGE, (void *)(&if_outpur));
		//NMI_LOG("\n[NMI]Change Frequency successful: freq = (%lu) Hz, IF = (%lu Hz) BW = (%d MHz ).\n", tune.rf, tune.vif, ucBw);
		printf("\n[NMI]Change Frequency successful: freq = (%lu) Hz, IF = (%lu Hz) BW = (%d MHz ).\n", tune.rf, tune.vif, ucBw);
		//NMI120_ShowAsicPara();
		if(((tune.rf <= 191500000+1000000)&&(tune.rf >= 191500000-1000000)) || 
			((tune.rf <= 219500000+1000000)&&(tune.rf >= 219500000-1000000)) )//swan fix,recover sensitivity
		{
			wReg8(0x05,0x87);
			NMI_LOG("\n[NMI]>>swan write 0x05 = 0x87\n");
		}
		return TRUE;
	}
}

void devDigitalTuner_Init()
{
	
}
//------------------------------------------------------------------------------
//  Subject:     DTOS403LH121A tuner paremeter write
//  Function:   Set_Digital_TUNER
//  Parmeter:   Freq: "RF+IF" in MHz
//                 eBandWidth:  7MHZ, 8MHZ
//                 CONFIG: pointer to tuner address
//  Return :    NONE
//  Remark:
//------------------------------------------------------------------------------

void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
	devDtvTunerSetPLLData(Freq, eBandWidth);
}

int NMI120_GetLockStatus(void)
{
	tTnrStatus status;

	if(nmi_drv_ctl(NMI_DRV_GET_STATUS,&status)<0)
	{
		return 0;
	}

	return status.ds.agclock;
}
static int ABS(int x)
{
    return x < 0 ? -x : x;
}

int NMI120_GetRSSI(MS_U8 outputChoice)
{
	int rssi;
	tTnrStatus status;
	//NMI120_ShowAsicPara();
	if(nmi_drv_ctl(NMI_DRV_GET_STATUS,&status)<0)
	{
		return 0;
	}

	rssi = (int)status.gain.rssix100/100;
	if (1 == outputChoice) // for percent value
	{
		if ((rssi<=0) && (rssi>=-100))
		{
			rssi = ABS(rssi);
            if(rssi>85)
                rssi = 0;
            else if(rssi > 45)
                rssi = (85-rssi)*100/40;
            else
                rssi = 100;
		}
		else
		{
			if (rssi > 0)
			{
				rssi = 100;
			}

			if (rssi < -100)
			{
				rssi = 0;
			}
		}
	}
    printf("[NMI]SSI=%d\n",rssi);

	return rssi;
}


MS_BOOL MDrv_Tuner_PowerOnOff(MS_BOOL bPowerOn)
{
    if(bPowerOn==FALSE)
    {
        //if need loop through, passing LOOP_THROUGH,else passing SIGLE_IN
		//tTnrStatus status;

		nmi_drv_ctl(NMI_DRV_SLEEP,NULL);
    }
    return TRUE;
}

MS_BOOL MDrv_Tuner_Reset(void)
{
	nmi_drv_ctl(NMI_DRV_RESET_DEMOD_MOSAIC,NULL);
	return TRUE;
}
MS_BOOL NMI120_LoopThrough(void)
{
	//int result;
	tTnrInit cfg;
	tTnrLtCtrl ltCtl;
	//tTnrStatus status;

	memset((void *)&cfg, 0, sizeof(tTnrInit));

/*	cfg.ldobypass = 0;
	cfg.xo = 24;
	cfg.i2c_adr = 0xce;
	cfg.init_bus_only = 0;
	cfg.xo_out_en = XO_OUT_EN;

	result = nmi_drv_ctl(NMI_DRV_INIT, (void *)&cfg);

	if(result < 0)
	{
		NMI_LOG(">> NMI_DRV_INIT failed. result = %d\n", result);
		return FALSE;
	}
	else
	{
		int chipid;
		tNmiDriverVer ver;

		nmi_drv_ctl(NMI_DRV_VERSION, &ver);
		NMI_LOG("[NMI] NMI 120,13x driver version (%d.%d.%d.%d) build %d\n", ver.major, ver.minor, ver.rev1, ver.rev2, ver.buildrev);

		nmi_drv_ctl(NMI_DRV_GET_CHIPID, &chipid);
		NMI_LOG("[NMI] Chip ID = 0x%08x\n", chipid);
	}*/

	ltCtl.enable = TRUE;
	if(nmi_drv_ctl(NMI_DRV_LT_CTRL, (void *)&ltCtl)<0)
	{
		return FALSE;
	}
/*Leo
	if (nmi_drv_ctl(NMI_DRV_SLEEP, &status)<0)
	{
		return FALSE;
	}*/
	nmi_drv_ctl(NMI_DRV_WAKE_UP_LT, NULL);
	return TRUE;
}

#endif
