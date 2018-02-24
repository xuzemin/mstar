/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4_InstanceCustom.h
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA182I4_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 * \par Changelog
 *  -0.0.0.9 FEAP908 multi-tuners adaptation
 *  -0.0.0.8 new settings DVB-T/T2 , ISDB-T
 *
 *
 * \par Version_Definition
 *  VERSION_TAG:TDA182I4_SETTINGS_CUSTOMER_NUM.TDA182I4_SETTINGS_PROJECT_NUM.TDA182I4_SETTINGS_MAJOR_VER.TDA182I4_SETTINGS_MINOR_VER
 *
*/

#ifndef _TDA182I4_INSTANCE_CUSTOM_H
#define _TDA182I4_INSTANCE_CUSTOM_H


#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/

/* Driver settings version definition */
#define TDA182I4_SETTINGS_CUSTOMER_NUM 0                     /* SW Settings Customer Number */
#define TDA182I4_SETTINGS_PROJECT_NUM  0                     /* SW Settings Project Number  */
#define TDA182I4_SETTINGS_MAJOR_VER    1                     /* SW Settings Major Version   */
#define TDA182I4_SETTINGS_MINOR_VER    8                     /* SW Settings Minor Version   */

/*  number of tuner supported by driver */
#define TDA182I4_UNITS  1

/* RC Cal Offset  0x00:+4%; 0x01:+2%; 0x02:0%  0x03:-2%  */
#define TDA182I4_RC_Cal_Offset 0x01

/* Standard Preset Definitions: */
#define TDA182I4_INSTANCE_CUSTOM_STD_QAM_6MHZ \
    {                                                               /* QAM 6MHz */ \
        3600000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_6MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_min_8pc,                                 /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                          /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY  */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_NO_TOP_ADAPT,                            /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_0_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_QAM_8MHZ \
    {                                                               /* QAM 8MHz */ \
        5000000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_9MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_min_8pc,                                 /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_1MHz,                                          /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY  */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_NO_TOP_ADAPT,                            /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_0_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
	}

#define TDA182I4_INSTANCE_CUSTOM_STD_ATSC_6MHZ \
    {                                                               /* ATSC */ \
        3250000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_6MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_0pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_0_5MHz,                                        /* Hi Pass */ \
        TDA182I4_HPFOffset_min_12pc,                                 /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_plus_4pc,                          /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d100_u94dBuV,                   /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY  */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_98_VALUE_2,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_102dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d112_u107dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_3_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_0_6Vpp_min_10_3_19_7dB,            /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ISDBT_6MHZ \
    {                                                               /* ISDBT */ \
        3250000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_6MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_0_5MHz,                                        /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_plus_4pc,                          /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY  */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_0_6Vpp_min_10_3_19_7dB,            /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
    	TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
}

#define TDA182I4_INSTANCE_CUSTOM_STD_DVBT_1_7MHZ \
    {                                                               /* DVB-T/T2 1.7MHz */ \
        850000,                                                     /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_1_5MHz,                                        /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY  */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_DVBT_6MHZ \
    {                                                               /* DVB-T/T2 6MHz */ \
        3250000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_6MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_0_5MHz,                                        /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_plus_4pc,                          /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_DVBT_7MHZ \
    {                                                               /* DVB-T/T2 7MHz */ \
        4500000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_min_12pc,                                 /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_1_6MHz,                                        /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_8_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                          /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_0_8Vpp_min_8_22dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_DVBT_8MHZ \
    {                                                               /* DVB-T/T2 8MHz */ \
        4800000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_9MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_min_8pc,                                 /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_1_6MHz,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_min_12pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_9_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_min_4pc,                           /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_0_8Vpp_min_8_22dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_DVBT_10MHZ \
    {                                                               /* DVB-T/T2 10MHz */ \
        5000000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_10MHz,                                         /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_10_25MHz,                            /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_DMBT_6MHZ \
    {                                                               /* DMB-T 6M*/ \
        4000000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_7MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_1MHz,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_7_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_102dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }
	
#define TDA182I4_INSTANCE_CUSTOM_STD_DMBT_8MHZ \
    {                                                               /* DMB-T */ \
        4000000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_8_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_NF,                                    /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_112_VALUE_4,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1,  /* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_102dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT35,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_2_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Enabled,                              /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Enabled,                              /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_FM_RADIO \
    {                                                               /* FM */ \
        1250000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_1_5MHz,                                        /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_1MHz,                                          /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_0_8Vpp_min_8_22dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		1,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_MN \
    {                                                               /* NTSC M/N */ \
        5400000,                                                    /* IF */ \
        1750000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_6MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Enabled,                       /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_B \
    {                                                               /* PAL B */ \
        6400000,                                                    /* IF */ \
        2250000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_7MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Enabled,                       /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_GH \
    {                                                               /* PAL G/H */ \
        6750000,                                                    /* IF */ \
        2750000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Enabled,                       /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_I \
    {                                                               /* PAL I */ \
        7250000,                                                    /* IF */ \
        2750000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Enabled,                       /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_DK \
    {                                                               /* SECAM D/K */ \
        6850000,                                                    /* IF */ \
        2750000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_8_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Enabled,                       /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_L \
    {                                                               /* SECAM L */ \
        6750000,                                                    /* IF */ \
        2750000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_8_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Enabled,                                  /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Disabled,                            /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_6_min_9,              /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_LL \
    {                                                               /* SECAM L' */ \
        1250000,                                                    /* IF */ \
        -2750000,                                                   /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_0_3M,                                   /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_0_3M,                                   /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_6_min_9,              /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_3dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_BLIND_SCANNING \
    {                                                               /* Blind Scanning copy of PAL-I */ \
        7250000,                                                    /* IF */ \
        2750000,                                                    /* CF_Offset */ \
        TDA182I4_LPF_8MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_plus_4pc,                                /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Disabled,                          /* DC notch IF PPF */ \
        TDA182I4_HPF_Disabled,                                      /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_3,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_96dBuV,                               /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_TOP_ADAPT34,                             /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_1_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_0_7Vpp_min_9_21dB,                 /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_8_192ms,  /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

#define TDA182I4_INSTANCE_CUSTOM_STD_SCANXPRESS \
    {                                                               /* ScanXpress */ \
        5000000,                                                    /* IF */ \
        0,                                                          /* CF_Offset */ \
        TDA182I4_LPF_9MHz,                                          /* LPF */ \
        TDA182I4_LPFOffset_min_4pc,                                 /* LPF_Offset */ \
        TDA182I4_DC_Notch_IF_PPF_Enabled,                           /* DC notch IF PPF */ \
        TDA182I4_HPF_1MHz,                                          /* Hi Pass */ \
        TDA182I4_HPFOffset_0pc,                                     /* HPF Offset */ \
        TDA182I4_IF_Notch_Freq_6_25MHz,                             /* IF Notch Freq */ \
        TDA182I4_IF_Notch_Offset_0pc,                               /* IF Notch Offset */ \
        TDA182I4_IF_Notch_Disabled,                                 /* IF notch */ \
        TDA182I4_IFnotchToRSSI_Enabled,                             /* IF notch To RSSI */ \
        TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,                    /* AGC1 TOP I2C DN/UP */ \
        TDA182I4_AGC1_TOP_STRATEGY_4,                               /* AGC1 TOP STRATEGY */ \
        TDA182I4_AGC1_LNA_Zin_S11,                                   /* LNA_Zin */ \
		TDA182I4_RFAGC_Peak_Val_114_VALUE_6,						/* RFAGC_Peak_Val */ \
		TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0,					/* RFAGC_Adapt_TOP_ovld */ \
		TDA182I4_RFAGC_det_mode_RMS_VALUE_0,						/* RFAGC_det_mode */ \
        TDA182I4_AGC3_TOP_I2C_100dBuV,                              /* AGC3 TOP I2C */ \
        TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,                      /* AGC4 TOP DN/UP */ \
        TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,                      /* AGC5 TOP DN/UP */ \
        TDA182I4_RSSI_HP_FC_2_25M,                                  /* RSSI HP FC */ \
        TDA182I4_AGC5_HP_FC_2_25M,                                  /* AGC5 HP FC */ \
        TDA182I4_Top_Adapt_NO_TOP_ADAPT,                            /* AGC3 TOP Adapt Algorithm */ \
        TDA182I4_AGC3_Adapt_TOP_0_Step,                             /* AGC3 Adapt */ \
        TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,          /* AGC Overload TOP */ \
        TDA182I4_RF_Atten_3dB_Disabled,                             /* RF Atten 3dB */ \
        TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,                   /* IF Output Level */ \
        TDA182I4_S2D_Gain_6dB,                                      /* S2D Gain */ \
        TDA182I4_Negative_Modulation_Disabled,                      /* Negative Modulation */ \
        TDA182I4_AGCK_Time_Constant_32_768ms,                       /* AGCK Time Constant */ \
        TDA182I4_VHF_III_Mode_Disabled,                             /* VHF III Mode */ \
		0,															/* RSSI_Ck_speed 0:31.25 1: 62.5 Khz */ \
		0,															/* RSSI_Cap_Val 0: 0.3 1: 3pF */ \
		TDA182I4PowerSavingMode_normal,                             /* Normal or Low */ \
    }

/* Default configuration */
#define TDA182I4_INSTANCE_CUSTOM_CURPOWERSTATE_DEF tmPowerMax
#define TDA182I4_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF TDA182I4_PowerMax
#define TDA182I4_INSTANCE_CUSTOM_RF_DEF 0
#define TDA182I4_INSTANCE_CUSTOM_PROG_RF_DEF 0
#define TDA182I4_INSTANCE_CUSTOM_STANDARDMODE_DEF TDA182I4_StandardMode_Max
#define TDA182I4_INSTANCE_CUSTOM_CURPOWERSAVINGMODE TDA182I4PowerSavingMode_normal

/* Power settings */
#define TDA182I4_INSTANCE_CUSTOM_POWER_DEF \
    TDA182I4_INSTANCE_CUSTOM_CURPOWERSTATE_DEF,                     /* curPowerState */ \
    TDA182I4_INSTANCE_CUSTOM_CURLLPOWERSTATE_DEF,                   /* curLLPowerState */ \
    {                                                               /* mapLLPowerState */ \
        TDA182I4_PowerNormalMode,                                   /* tmPowerOn (D0) */ \
        TDA182I4_PowerStandbyWithXtalOn,                            /* tmPowerStandby (D1) */ \
        TDA182I4_PowerStandbyWithXtalOn,                            /* tmPowerSuspend (D2) */ \
        TDA182I4_PowerStandbyWithXtalOn                             /* tmPowerOff (D3) */ \
    }, \
    TDA182I4_INSTANCE_CUSTOM_CURPOWERSAVINGMODE

/* Standard Presets Aggregation: */
#define TDA182I4_INSTANCE_CUSTOM_STD_DEF \
    { \
        TDA182I4_INSTANCE_CUSTOM_STD_QAM_6MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_QAM_8MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_ATSC_6MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_ISDBT_6MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_DVBT_1_7MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_DVBT_6MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_DVBT_7MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_DVBT_8MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_DVBT_10MHZ, \
		TDA182I4_INSTANCE_CUSTOM_STD_DMBT_6MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_DMBT_8MHZ, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_FM_RADIO, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_MN, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_B, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_GH, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_I, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_DK, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_L, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_LL, \
        TDA182I4_INSTANCE_CUSTOM_STD_ANALOG_BLIND_SCANNING, \
        TDA182I4_INSTANCE_CUSTOM_STD_SCANXPRESS \
    }

#define TDA182I4_INSTANCE_CUSTOM_MASTER_0 \
    TDA182I4_INSTANCE_CUSTOM_POWER_DEF, \
    TDA182I4_INSTANCE_CUSTOM_RF_DEF,                                /* uRF */ \
    TDA182I4_INSTANCE_CUSTOM_PROG_RF_DEF,                           /* uProgRF */ \
    TDA182I4_INSTANCE_CUSTOM_STANDARDMODE_DEF,                      /* StandardMode */ \
    Null,                                                           /* pStandard */ \
    True,                                                           /* bOverridePLL */ \
    True,                                                           /* bFefEnable */ \
	False,                                                          /* bHalfRfImmunity */ \
	True,                                                           /* bCenelecMargin */ \
	( TDA182I4_Mode_LTO_Not_Used |TDA182I4_Mode_STO_Not_Used) ,     /* define LTO/STO option */ \
    TDA182I4_XTOUT_Amp_800mV,                                       /* curXTOutAmp */ \
	TDA182I4_LNA_RANGE_Minus11dB_Plus22dB,							/* curLNA_RANGE */ \
    TDA182I4_HwState_InitNotDone,                                   /* eHwState */ \
    TDA182I4_INSTANCE_CUSTOM_STD_DEF, \

/* Custom Driver Instance Parameters: (Path 0) */
#define TDA182I4_INSTANCE_CUSTOM_0 \
    TDA182I4_INSTANCE_CUSTOM_MASTER_0

#ifdef __cplusplus
}
#endif

#endif /* _TDA182I4_INSTANCE_CUSTOM_H */

