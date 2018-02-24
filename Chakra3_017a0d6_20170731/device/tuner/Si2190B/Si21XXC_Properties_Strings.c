/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties strings functions definitions
   FILE: Si21XXC_L1_Properties_Strings.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si21XXC_COMMAND_PROTOTYPES

#include "Si21XXC_L1_API.h"
#include "Si21XXC_Properties_Strings.h"

#ifdef Si21XXC_COMMAND_LINE_APPLICATION

/* define a local PropObj variable to use for the Property Dictionary initializer */
Si21XXC_PropObj Si21XXC_prop;
char optionText[20];

const char *Si21XXC_featureText[] =
{
  "ATV",
  "COMMON",
  "DTV",
  "TUNER",
};

Si21XXC_optionStruct    Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_AFC_RANGE_PROP_FIELDS[] =
{
  {"RANGE_KHZ", Si21XXC_UNSIGNED_INT, &Si21XXC_prop.atv_afc_range.range_khz, sizeof(Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ},
};

Si21XXC_optionStruct    Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
{
  {"AUTO",       0},
  {"89",        89},
  {"105",      105},
  {"121",      121},
  {"137",      137},
  {"158",      158},
  {"172",      172},
  {"178",      178},
  {"185",      185},
  {"196",      196},
  {"206",      206},
  {"216",      216},
  {"219",      219},
  {"222",      222},
  {"223",      223},
  {"248",      248},
  {"250",      250},
  {"251",      251},
  {"CUSTOM",     1},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_agc_speed.if_agc_speed, sizeof(Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED},
};

Si21XXC_optionStruct    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[] =
{
  {"89",        89},
  {"105",      105},
  {"121",      121},
  {"137",      137},
  {"158",      158},
  {"172",      172},
  {"178",      178},
  {"185",      185},
  {"196",      196},
  {"206",      206},
  {"216",      216},
  {"219",      219},
  {"222",      222},
  {"223",      223},
  {"248",      248},
  {"250",      250},
  {"251",      251},
  {"CUSTOM",     1},
};
Si21XXC_optionStruct    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_agc_speed_low_rssi.if_agc_speed, sizeof(Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED},
  {"THLD",           Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_agc_speed_low_rssi.thld        , sizeof(Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD        )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD        },
};

Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN[] =
{
  {"AUTO",     0},
  {"0DB",      1},
  {"6DB",      2},
  {"12DB",     3},
  {"18DB",     4},
  {"24DB",     5},
  {"30DB",     6},
  {"36DB",     7},
  {"42DB",     8},
  {"OFF",      9},
};
Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND[] =
{
  {"MUTE",             0},
  {"6DB",              1},
  {"12DB",             2},
  {"18DB",             3},
  {"24DB",             4},
  {"30DB",             5},
  {"36DB",             6},
  {"PASS_THROUGH",     7},
};
Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD[] =
{
  {"LONG",      0},
  {"SHORT",     1},
};
Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[] =
{
  {"GAIN",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_artificial_snow.gain  , sizeof(Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN  )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN  },
  {"SOUND",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_artificial_snow.sound , sizeof(Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND },
  {"PERIOD", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_artificial_snow.period, sizeof(Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD},
  {"OFFSET",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_artificial_snow.offset, sizeof(Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET},
};

Si21XXC_optionStruct    Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS[] =
{
  {"DEFAULT",             0},
  {"MONO",                1},
  {"MONO_NICAM",          2},
  {"A2",                  3},
  {"A2_DK2",              4},
  {"A2_DK3",              5},
  {"BTSC",                6},
  {"EIAJ",                7},
  {"SCAN",                8},
  {"A2_DK4",              9},
  {"WIDE_SCAN",          10},
  {"MONO_NICAM_6DB",     11},
  {"MONO_NICAM_10DB",    12},
};
Si21XXC_optionStruct    Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW[] =
{
  {"DEFAULT",            0},
  {"4X_OVERMOD",         1},
  {"8X_OVERMOD",         2},
  {"12X_OVERMOD",        3},
  {"7P5_KHZ_OFFSET",     4},
  {"15_KHZ_OFFSET",      5},
  {"30_KHZ_OFFSET",      6},
  {"75_KHZ_OFFSET",      7},
  {"150_KHZ_OFFSET",     8},
  {"CUSTOM",             9},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_AUDIO_MODE_PROP_FIELDS[] =
{
  {"AUDIO_SYS",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_audio_mode.audio_sys   , sizeof(Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS   )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS   },
  {"CHAN_BW",      Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_audio_mode.chan_bw,     sizeof(Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW},
};

Si21XXC_optionStruct    Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[] =
{
  {"CVBS_IF2B_SOUND_IF2A",           0},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"ATV_OUT_TYPE", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_config_if_port.atv_out_type, sizeof(Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE},
};
Si21XXC_optionStruct    Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   127}
};
Si21XXC_optionStruct    Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    63}
};
Si21XXC_optionStruct    Si2190B_ATV_CVBS_ATTENUATION_PROP_BW[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",     7}
};
Si21XXC_fieldDicoStruct Si2190B_ATV_CVBS_ATTENUATION_PROP_FIELDS[] =
{
  {"THRESHOLD", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_cvbs_attenuation.threshold, sizeof(Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD)/sizeof(Si21XXC_optionStruct), Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD},
  {"RATE",      Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_cvbs_attenuation.rate     , sizeof(Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE     )/sizeof(Si21XXC_optionStruct), Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE     },
  {"BW",        Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_cvbs_attenuation.bw       , sizeof(Si2190B_ATV_CVBS_ATTENUATION_PROP_BW       )/sizeof(Si21XXC_optionStruct), Si2190B_ATV_CVBS_ATTENUATION_PROP_BW       },
};
Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_CVBS_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_cvbs_out.offset, sizeof(Si21XXC_ATV_CVBS_OUT_PROP_OFFSET)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_CVBS_OUT_PROP_OFFSET},
  {"AMP",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_cvbs_out.amp   , sizeof(Si21XXC_ATV_CVBS_OUT_PROP_AMP   )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_CVBS_OUT_PROP_AMP   },
};

Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP[] =
{
  {"MIN_RANGE",    25},
  {"MAX_RANGE",   100}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_CVBS_OUT_FINE_PROP_FIELDS[] =
{
  {"OFFSET",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_cvbs_out_fine.offset, sizeof(Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET},
  {"AMP",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_cvbs_out_fine.amp   , sizeof(Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP   )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP   },
};

Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_PCLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_DLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_SNRLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_SNRHIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_ien.chlien , sizeof(Si21XXC_ATV_IEN_PROP_CHLIEN )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_IEN_PROP_CHLIEN },
  {"PCLIEN",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_ien.pclien , sizeof(Si21XXC_ATV_IEN_PROP_PCLIEN )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_IEN_PROP_PCLIEN },
  {"DLIEN",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_ien.dlien  , sizeof(Si21XXC_ATV_IEN_PROP_DLIEN  )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_IEN_PROP_DLIEN  },
  {"SNRLIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_ien.snrlien, sizeof(Si21XXC_ATV_IEN_PROP_SNRLIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_IEN_PROP_SNRLIEN},
  {"SNRHIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_ien.snrhien, sizeof(Si21XXC_ATV_IEN_PROP_SNRHIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_IEN_PROP_SNRHIEN},
};

Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.chlnegen , sizeof(Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN },
  {"PCLNEGEN",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.pclnegen , sizeof(Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN },
  {"DLNEGEN",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.dlnegen  , sizeof(Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN  )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN  },
  {"SNRLNEGEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.snrlnegen, sizeof(Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN},
  {"SNRHNEGEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.snrhnegen, sizeof(Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN},
  {"CHLPOSEN",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.chlposen , sizeof(Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN },
  {"PCLPOSEN",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.pclposen , sizeof(Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN },
  {"DLPOSEN",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.dlposen  , sizeof(Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN  )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN  },
  {"SNRLPOSEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.snrlposen, sizeof(Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN},
  {"SNRHPOSEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_int_sense.snrhposen, sizeof(Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN},
};

Si21XXC_optionStruct    Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET[] =
{
  {"MIN_RANGE",   -13},
  {"MAX_RANGE",     7}
};
Si21XXC_optionStruct    Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_PGA_TARGET_PROP_FIELDS[] =
{
  {"PGA_TARGET",        Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_pga_target.pga_target     , sizeof(Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET     )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET     },
  {"OVERRIDE_ENABLE", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_pga_target.override_enable, sizeof(Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE},
};

Si21XXC_optionStruct    Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP[] =
{
  {"AUTO",      0},
  {"P5DB",      1},
  {"P4DB",      2},
  {"P3DB",      3},
  {"P2DB",      4},
  {"P1DB",      5},
  {"0DB",       6},
  {"M1DB",      7},
  {"M2DB",      8},
  {"M3DB",      9},
  {"M4DB",     10},
  {"M5DB",     11},
  {"M6DB",     12},
  {"M7DB",     13},
  {"M8DB",     14},
  {"M9DB",     15},
  {"M10DB",    16},
  {"M11DB",    17},
  {"M12DB",    18},
  {"M13DB",    19},
  {"M14DB",    20},
  {"M15DB",    21},
  {"M16DB",    22},
  {"M17DB",    23},
  {"M18DB",    24},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_RF_TOP_PROP_FIELDS[] =
{
  {"ATV_RF_TOP", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_rf_top.atv_rf_top, sizeof(Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP},
};

Si21XXC_optionStruct    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_optionStruct    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_rsq_rssi_threshold.lo, sizeof(Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_rsq_rssi_threshold.hi, sizeof(Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si21XXC_optionStruct    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_optionStruct    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS[] =
{
  {"LO", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_rsq_snr_threshold.lo, sizeof(Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO},
  {"HI", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_rsq_snr_threshold.hi, sizeof(Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI},
};

Si21XXC_optionStruct    Si21XXC_ATV_SIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_optionStruct    Si21XXC_ATV_SIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_SIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_sif_out.offset, sizeof(Si21XXC_ATV_SIF_OUT_PROP_OFFSET)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_SIF_OUT_PROP_OFFSET},
  {"AMP",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_sif_out.amp   , sizeof(Si21XXC_ATV_SIF_OUT_PROP_AMP   )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_SIF_OUT_PROP_AMP   },
};

Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN[] =
{
  {"MIN_RANGE",   -84},
  {"MAX_RANGE",    84}
};
Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN[] =
{
  {"MIN_RANGE",   -84},
  {"MAX_RANGE",    84}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_FIELDS[] =
{
  {"MAX_GAIN",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_sound_agc_limit.max_gain, sizeof(Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN},
  {"MIN_GAIN",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_sound_agc_limit.min_gain, sizeof(Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN},
};

Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_SOUND_AGC_SPEED_PROP_FIELDS[] =
{
  {"SYSTEM_L",      Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_sound_agc_speed.system_l     , sizeof(Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L     )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L     },
  {"OTHER_SYSTEMS", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_sound_agc_speed.other_systems, sizeof(Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS},
};

Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE[] =
{
  {"MIN_RANGE",   -25},
  {"MAX_RANGE",    15}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_VIDEO_EQUALIZER_PROP_FIELDS[] =
{
  {"SLOPE",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.atv_video_equalizer.slope, sizeof(Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE},
};

Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS[] =
{
  {"B",      0},
  {"GH",     1},
  {"M",      2},
  {"N",      3},
  {"I",      4},
  {"DK",     5},
  {"L",      6},
  {"LP",     7},
};
Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_MODE_PROP_COLOR[] =
{
  {"PAL_NTSC",     0},
  {"SECAM",        1},
};
Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_VIDEO_MODE_PROP_FIELDS[] =
{
  {"VIDEO_SYS",     Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_video_mode.video_sys    , sizeof(Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS    )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS    },
  {"COLOR",         Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_video_mode.color        , sizeof(Si21XXC_ATV_VIDEO_MODE_PROP_COLOR        )/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_VIDEO_MODE_PROP_COLOR        },
  {"INVERT_SIGNAL", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_video_mode.invert_signal, sizeof(Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL},
};

Si21XXC_optionStruct    Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   127}
};
Si21XXC_fieldDicoStruct Si21XXC_ATV_VSNR_CAP_PROP_FIELDS[] =
{
  {"ATV_VSNR_CAP", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.atv_vsnr_cap.atv_vsnr_cap, sizeof(Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP)/sizeof(Si21XXC_optionStruct), Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP},
};

Si21XXC_optionStruct    Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP[] =
{
  {"4p7pF",      0},
  {"4p95pF",     1},
  {"5p2pF",      2},
  {"5p45pF",     3},
  {"5p7pF",      4},
  {"5p95pF",     5},
  {"6p2pF",      6},
  {"6p45pF",     7},
  {"6p7pF",      8},
  {"6p95pF",     9},
  {"7p2pF",     10},
  {"7p45pF",    11},
  {"7p7pF",     12},
  {"7p95pF",    13},
  {"8p2pF",     14},
  {"8p45pF",    15},
};
Si21XXC_fieldDicoStruct Si21XXC_CRYSTAL_TRIM_PROP_FIELDS[] =
{
  {"XO_CAP", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.crystal_trim.xo_cap, sizeof(Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP)/sizeof(Si21XXC_optionStruct), Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP},
};

Si21XXC_optionStruct    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_optionStruct    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT[] =
{
  {"MIN_RANGE",     1},
  {"MAX_RANGE",   250}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_FIELDS[] =
{
  {"THLD",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_agc_auto_freeze.thld   , sizeof(Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD   )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD   },
  {"TIMEOUT", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_agc_auto_freeze.timeout, sizeof(Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT},
};

Si21XXC_optionStruct    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[] =
{
  {"LOW",      0},
  {"HIGH",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN[] =
{
  {"NONE",         0},
  {"GPIO1",        1},
  {"GPIO2",        2},
  {"RESERVED",     3},
  {"AGC1",         4},
  {"AGC2",         5},
  {"LIF1A",        6},
  {"LIF1B",        7},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[] =
{
  {"LEVEL", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_agc_freeze_input.level, sizeof(Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL},
  {"PIN",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_agc_freeze_input.pin  , sizeof(Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN  )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN  },
};

Si21XXC_optionStruct    Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
{
  {"AUTO",     0},
  {"39",      39},
  {"54",      54},
  {"63",      63},
  {"89",      89},
  {"105",    105},
  {"121",    121},
  {"137",    137},
  {"158",    158},
  {"172",    172},
  {"185",    185},
  {"196",    196},
  {"206",    206},
  {"216",    216},
  {"219",    219},
  {"222",    222},
};
Si21XXC_optionStruct    Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_agc_speed.if_agc_speed, sizeof(Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_agc_speed.agc_decim   , sizeof(Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM   },
};

Si21XXC_optionStruct    Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[] =
{
  {"LIF_IF1",         0},
  {"LIF_IF2",         1},
  {"LIF_SE_IF1A",     4},
  {"LIF_SE_IF2A",     5},
  {"LVDS",            6},
};
Si21XXC_optionStruct    Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[] =
{
  {"INTERNAL",      0},
  {"AGC1_3DB",      1},
  {"AGC2_3DB",      2},
  {"AGC1_FULL",     3},
  {"AGC2_FULL",     4},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"DTV_OUT_TYPE",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_config_if_port.dtv_out_type  , sizeof(Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  },
  {"DTV_AGC_SOURCE", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_config_if_port.dtv_agc_source, sizeof(Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE},
};

Si21XXC_optionStruct    Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_optionStruct    Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_EXT_AGC_PROP_FIELDS[] =
{
  {"MIN_10MV", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_ext_agc.min_10mv, sizeof(Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV},
  {"MAX_10MV", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_ext_agc.max_10mv, sizeof(Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV},
};

Si21XXC_optionStruct    Si21XXC_DTV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_ien.chlien, sizeof(Si21XXC_DTV_IEN_PROP_CHLIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_IEN_PROP_CHLIEN},
};
Si21XXC_optionStruct    Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK[] =
{
  {"AUTO",     0},
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   231}
};
Si21XXC_optionStruct    Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY[] =
{
  {"AUTO",     0},
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   231}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_IF_AGC_SPEED_PROP_FIELDS[] =
{
  {"ATTACK", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_if_agc_speed.attack, sizeof(Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK},
  {"DECAY",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_if_agc_speed.decay , sizeof(Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY },
};

Si21XXC_optionStruct    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[] =
{
  {"AUTO",     0},
  {"39",      39},
  {"54",      54},
  {"63",      63},
  {"89",      89},
  {"105",    105},
  {"121",    121},
  {"137",    137},
  {"158",    158},
  {"172",    172},
  {"185",    185},
  {"196",    196},
  {"206",    206},
  {"216",    216},
  {"219",    219},
  {"222",    222},
};
Si21XXC_optionStruct    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_initial_agc_speed.if_agc_speed, sizeof(Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_initial_agc_speed.agc_decim   , sizeof(Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   },
};

Si21XXC_optionStruct    Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[] =
{
  {"PERIOD", Si21XXC_UNSIGNED_INT, &Si21XXC_prop.dtv_initial_agc_speed_period.period, sizeof(Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD},
};

Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_INTERNAL_ZIF_PROP_FIELDS[] =
{
  {"ATSC",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.atsc  , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC  )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC  },
  {"QAM_US", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.qam_us, sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US},
  {"DVBT",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.dvbt  , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT  )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT  },
  {"DVBC",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.dvbc  , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC  )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC  },
  {"ISDBT",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.isdbt , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT },
  {"ISDBC",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.isdbc , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC },
  {"DTMB",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_internal_zif.dtmb  , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB  )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB  },
};

Si21XXC_optionStruct    Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_int_sense.chlnegen, sizeof(Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN},
  {"CHLPOSEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_int_sense.chlposen, sizeof(Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN},
};

Si21XXC_optionStruct    Si21XXC_DTV_LIF_FREQ_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",  7000}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_LIF_FREQ_PROP_FIELDS[] =
{
  {"OFFSET", Si21XXC_UNSIGNED_INT, &Si21XXC_prop.dtv_lif_freq.offset, sizeof(Si21XXC_DTV_LIF_FREQ_PROP_OFFSET)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_LIF_FREQ_PROP_OFFSET},
};

Si21XXC_optionStruct    Si21XXC_DTV_LIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_optionStruct    Si21XXC_DTV_LIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_LIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_lif_out.offset, sizeof(Si21XXC_DTV_LIF_OUT_PROP_OFFSET)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_LIF_OUT_PROP_OFFSET},
  {"AMP",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_lif_out.amp   , sizeof(Si21XXC_DTV_LIF_OUT_PROP_AMP   )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_LIF_OUT_PROP_AMP   },
};

Si21XXC_optionStruct    Si21XXC_DTV_MODE_PROP_BW[] =
{
  {"BW_6MHZ",     6},
  {"BW_7MHZ",     7},
  {"BW_8MHZ",     8},
  {"BW_1P7MHZ",     9},
  {"BW_6P1MHZ",    10},
};
Si21XXC_optionStruct    Si21XXC_DTV_MODE_PROP_MODULATION[] =
{
  {"ATSC",       0},
  {"QAM_US",     1},
  {"DVBT",       2},
  {"DVBC",       3},
  {"ISDBT",      4},
  {"ISDBC",      5},
  {"DTMB",       6},
  {"CW_LEGACY",    14},
  {"CW",        15},
};
Si21XXC_optionStruct    Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_MODE_PROP_FIELDS[] =
{
  {"BW",              Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_mode.bw             , sizeof(Si21XXC_DTV_MODE_PROP_BW             )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_MODE_PROP_BW             },
  {"MODULATION",      Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_mode.modulation     , sizeof(Si21XXC_DTV_MODE_PROP_MODULATION     )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_MODE_PROP_MODULATION     },
  {"INVERT_SPECTRUM", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_mode.invert_spectrum, sizeof(Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM},
};

Si21XXC_optionStruct    Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   231}
};
Si21XXC_optionStruct    Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   231}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_RF_AGC_SPEED_PROP_FIELDS[] =
{
  {"ATTACK", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_rf_agc_speed.attack, sizeof(Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK},
  {"DECAY",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_rf_agc_speed.decay , sizeof(Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY },
};

Si21XXC_optionStruct    Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP[] =
{
  {"AUTO",        0},
  {"P10DB",       1},
  {"P9P5DB",      2},
  {"P9DB",        3},
  {"P8P5DB",      4},
  {"P8DB",        5},
  {"P7P5DB",      6},
  {"P7DB",        7},
  {"P6P5DB",      8},
  {"P6DB",        9},
  {"P5P5DB",     10},
  {"P5DB",       11},
  {"P4P5DB",     12},
  {"P4DB",       13},
  {"P3P5DB",     14},
  {"P3DB",       15},
  {"P2P5DB",     16},
  {"P2DB",       17},
  {"P1P5DB",     18},
  {"P1DB",       19},
  {"P0P5DB",     20},
  {"0DB",        21},
  {"M0P5DB",     22},
  {"M1DB",       23},
  {"M1P5DB",     24},
  {"M2DB",       25},
  {"M2P5DB",     26},
  {"M3DB",       27},
  {"M3P5DB",     28},
  {"M4DB",       29},
  {"M4P5DB",     30},
  {"M5DB",       31},
  {"M5P5DB",     32},
  {"M6DB",       33},
  {"M6P5DB",     34},
  {"M7DB",       35},
  {"M7P5DB",     36},
  {"M8DB",       37},
  {"M8P5DB",     38},
  {"M9DB",       39},
  {"M9P5DB",     40},
  {"M10DB",      41},
  {"M10P5DB",    42},
  {"M11DB",      43},
  {"M11P5DB",    44},
  {"M12DB",      45},
  {"M12P5DB",    46},
  {"M13DB",      47},
  {"M13P5DB",    48},
  {"M14DB",      49},
  {"M14P5DB",    50},
  {"M15DB",      51},
  {"M15P5DB",    52},
  {"M16DB",      53},
  {"M16P5DB",    54},
  {"M17DB",      55},
  {"M17P5DB",    56},
  {"M18DB",      57},
  {"M18P5DB",    58},
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_RF_TOP_PROP_FIELDS[] =
{
  {"DTV_RF_TOP", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_rf_top.dtv_rf_top, sizeof(Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP},
};

Si21XXC_optionStruct    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_optionStruct    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.dtv_rsq_rssi_threshold.lo, sizeof(Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si21XXC_SIGNED_CHAR, &Si21XXC_prop.dtv_rsq_rssi_threshold.hi, sizeof(Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si21XXC_optionStruct    Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK[] =
{
  {"AUTO",     0},
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   231}
};
Si21XXC_optionStruct    Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY[] =
{
  {"AUTO",     0},
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   231}
};
Si21XXC_fieldDicoStruct Si21XXC_DTV_WB_AGC_SPEED_PROP_FIELDS[] =
{
  {"ATTACK", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_wb_agc_speed.attack, sizeof(Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK)/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK},
  {"DECAY",  Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.dtv_wb_agc_speed.decay , sizeof(Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY )/sizeof(Si21XXC_optionStruct), Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY },
};

Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_TUNIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_ATVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_DTVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_ERRIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_CTSIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_MASTER_IEN_PROP_FIELDS[] =
{
  {"TUNIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.master_ien.tunien, sizeof(Si21XXC_MASTER_IEN_PROP_TUNIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_MASTER_IEN_PROP_TUNIEN},
  {"ATVIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.master_ien.atvien, sizeof(Si21XXC_MASTER_IEN_PROP_ATVIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_MASTER_IEN_PROP_ATVIEN},
  {"DTVIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.master_ien.dtvien, sizeof(Si21XXC_MASTER_IEN_PROP_DTVIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_MASTER_IEN_PROP_DTVIEN},
  {"ERRIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.master_ien.errien, sizeof(Si21XXC_MASTER_IEN_PROP_ERRIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_MASTER_IEN_PROP_ERRIEN},
  {"CTSIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.master_ien.ctsien, sizeof(Si21XXC_MASTER_IEN_PROP_CTSIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_MASTER_IEN_PROP_CTSIEN},
};

Si21XXC_optionStruct    Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE[] =
{
  {"MIN_RANGE", -32768},
  {"MAX_RANGE", 32767}
};
Si21XXC_fieldDicoStruct Si21XXC_TUNER_BLOCKED_VCO_PROP_FIELDS[] =
{
  {"VCO_CODE",   Si21XXC_SIGNED_INT, &Si21XXC_prop.tuner_blocked_vco.vco_code, sizeof(Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE},
};

Si21XXC_optionStruct    Si21XXC_TUNER_IEN_PROP_TCIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_IEN_PROP_RSSILIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_IEN_PROP_RSSIHIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_TUNER_IEN_PROP_FIELDS[] =
{
  {"TCIEN",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_ien.tcien   , sizeof(Si21XXC_TUNER_IEN_PROP_TCIEN   )/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_IEN_PROP_TCIEN   },
  {"RSSILIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_ien.rssilien, sizeof(Si21XXC_TUNER_IEN_PROP_RSSILIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_IEN_PROP_RSSILIEN},
  {"RSSIHIEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_ien.rssihien, sizeof(Si21XXC_TUNER_IEN_PROP_RSSIHIEN)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_IEN_PROP_RSSIHIEN},
};

Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_TUNER_INT_SENSE_PROP_FIELDS[] =
{
  {"TCNEGEN",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_int_sense.tcnegen   , sizeof(Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN   )/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN   },
  {"RSSILNEGEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_int_sense.rssilnegen, sizeof(Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN},
  {"RSSIHNEGEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_int_sense.rssihnegen, sizeof(Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN},
  {"TCPOSEN",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_int_sense.tcposen   , sizeof(Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN   )/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN   },
  {"RSSILPOSEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_int_sense.rssilposen, sizeof(Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN},
  {"RSSIHPOSEN", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_int_sense.rssihposen, sizeof(Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN},
};

Si21XXC_optionStruct    Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si21XXC_optionStruct    Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si21XXC_fieldDicoStruct Si21XXC_TUNER_LO_INJECTION_PROP_FIELDS[] =
{
  {"BAND_1", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_lo_injection.band_1, sizeof(Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1},
  {"BAND_2", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_lo_injection.band_2, sizeof(Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2},
  {"BAND_3", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_lo_injection.band_3, sizeof(Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3},
};

Si21XXC_optionStruct    Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG[] =
{
  {"3",       3},
  {"7",       7},
  {"11",     11},
  {"15",     15},
  {"19",     19},
  {"23",     23},
  {"27",     27},
  {"31",     31},
  {"35",     35},
  {"39",     39},
  {"43",     43},
  {"47",     47},
  {"51",     51},
  {"59",     59},
  {"67",     67},
  {"75",     75},
  {"83",     83},
  {"91",     91},
  {"103",   103},
  {"115",   115},
  {"127",   127},
};
Si21XXC_optionStruct    Si21XXC_TUNER_RETURN_LOSS_PROP_MODE[] =
{
  {"TERRESTRIAL",     0},
  {"CABLE",           1},
};
Si21XXC_fieldDicoStruct Si21XXC_TUNER_RETURN_LOSS_PROP_FIELDS[] =
{
  {"CONFIG", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss.config, sizeof(Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG)/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG},
  {"MODE",   Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss.mode  , sizeof(Si21XXC_TUNER_RETURN_LOSS_PROP_MODE  )/sizeof(Si21XXC_optionStruct), Si21XXC_TUNER_RETURN_LOSS_PROP_MODE  },
};

Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",     7}
};
Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG[] =
{
  {"2",           0},
  {"3",           1},
  {"4",           2},
  {"5",           3},
  {"6",           4},
  {"7",           5},
  {"8",           6},
  {"9",           7},
  {"10",          8},
  {"11",          9},
  {"13",         10},
  {"15",         11},
  {"17",         12},
  {"19",         13},
  {"23",         14},
  {"27",         15},
  {"31",         16},
  {"35",         17},
  {"39",         18},
  {"43",         19},
  {"47",         20},
  {"51",         21},
  {"59",         22},
  {"67",         23},
  {"75",         24},
  {"83",         25},
  {"91",         26},
  {"103",        27},
  {"115",        28},
  {"127",        29},
  {"DISABLE",    30},
};
Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si21XXC_fieldDicoStruct Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_FIELDS[] =
{
  {"THLD",                Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize.thld               , sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD               )/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD               },
  {"CONFIG",              Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize.config             , sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG             )/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG             },
  {"ENGAGEMENT_DELAY",    Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize.engagement_delay   , sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY   )/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY   },
  {"DISENGAGEMENT_DELAY", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize.disengagement_delay, sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY)/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY},
};

Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    31}
};
Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",     7}
};
Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si21XXC_fieldDicoStruct Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_FIELDS[] =
{
  {"THLD",             Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize_2.thld            , sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD            )/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD            },
  {"WINDOW",           Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize_2.window          , sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW          )/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW          },
  {"ENGAGEMENT_DELAY", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.tuner_return_loss_optimize_2.engagement_delay, sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY)/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY},
};


Si21XXC_optionStruct    Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET[] =
{
  {"MIN_RANGE",  -100},
  {"MAX_RANGE",   100}
};
Si21XXC_fieldDicoStruct Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_FIELDS[] =
{
  {"TF1_BOUNDARY_OFFSET",   Si21XXC_SIGNED_INT, &Si21XXC_prop.tuner_tf1_boundary_offset.tf1_boundary_offset, sizeof(Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET)/sizeof(Si21XXC_optionStruct), Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET},
};

Si21XXC_optionStruct    Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS[] =
{
  {"AUTO",        0},
  {"P6DBM",       6},
  {"P5DBM",       7},
  {"P4DBM",       8},
  {"P3DBM",       9},
  {"P2DBM",      10},
  {"P1DBM",      11},
  {"0DBM",       12},
  {"M1DBM",      13},
  {"M2DBM",      14},
  {"M3DBM",      15},
  {"M4DBM",      16},
  {"M5DBM",      17},
  {"M6DBM",      18},
  {"M7DBM",      19},
  {"M8DBM",      20},
  {"M9DBM",      21},
  {"M10DBM",     22},
  {"M11DBM",     23},
  {"M12DBM",     24},
  {"DISABLE",   255},
};
Si21XXC_fieldDicoStruct Si2190B_WIDE_BAND_ATT_THRS_PROP_FIELDS[] =
{
  {"WB_ATT_THRS", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.wide_band_att_thrs.wb_att_thrs, sizeof(Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS)/sizeof(Si21XXC_optionStruct), Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS},
};
Si21XXC_optionStruct    Si21XXC_XOUT_PROP_AMP[] =
{
  {"HIGH",     0},
  {"LOW",      1},
};
Si21XXC_fieldDicoStruct Si21XXC_XOUT_PROP_FIELDS[] =
{
  {"AMP", Si21XXC_UNSIGNED_CHAR, &Si21XXC_prop.xout.amp, sizeof(Si21XXC_XOUT_PROP_AMP)/sizeof(Si21XXC_optionStruct), Si21XXC_XOUT_PROP_AMP},
};

Si21XXC_propertyInfoStruct Si21XXC_propertyDictionary[] =
{
  {Si21XXC_ATV   , "ATV_AFC_RANGE"               , sizeof(Si21XXC_ATV_AFC_RANGE_PROP_FIELDS               )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_AFC_RANGE_PROP_FIELDS                , Si21XXC_ATV_AFC_RANGE_PROP                },
  {Si21XXC_ATV   , "ATV_AGC_SPEED"               , sizeof(Si21XXC_ATV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_AGC_SPEED_PROP_FIELDS                , Si21XXC_ATV_AGC_SPEED_PROP                },
  {Si21XXC_ATV   , "ATV_AGC_SPEED_LOW_RSSI"      , sizeof(Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS      )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS       , Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP       },
  {Si21XXC_ATV   , "ATV_ARTIFICIAL_SNOW"         , sizeof(Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_FIELDS         )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_FIELDS          , Si21XXC_ATV_ARTIFICIAL_SNOW_PROP          },
  {Si21XXC_ATV   , "ATV_AUDIO_MODE"              , sizeof(Si21XXC_ATV_AUDIO_MODE_PROP_FIELDS              )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_AUDIO_MODE_PROP_FIELDS               , Si21XXC_ATV_AUDIO_MODE_PROP               },
  {Si21XXC_ATV   , "ATV_CONFIG_IF_PORT"          , sizeof(Si21XXC_ATV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_CONFIG_IF_PORT_PROP_FIELDS           , Si21XXC_ATV_CONFIG_IF_PORT_PROP           },
  {Si21XXC_ATV   , "ATV_CVBS_ATTENUATION"        , sizeof(Si2190B_ATV_CVBS_ATTENUATION_PROP_FIELDS        )/sizeof(Si21XXC_fieldDicoStruct), Si2190B_ATV_CVBS_ATTENUATION_PROP_FIELDS         , Si2190B_ATV_CVBS_ATTENUATION_PROP         },
  {Si21XXC_ATV   , "ATV_CVBS_OUT"                , sizeof(Si21XXC_ATV_CVBS_OUT_PROP_FIELDS                )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_CVBS_OUT_PROP_FIELDS                 , Si21XXC_ATV_CVBS_OUT_PROP                 },
  {Si21XXC_ATV   , "ATV_CVBS_OUT_FINE"           , sizeof(Si21XXC_ATV_CVBS_OUT_FINE_PROP_FIELDS           )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_CVBS_OUT_FINE_PROP_FIELDS            , Si21XXC_ATV_CVBS_OUT_FINE_PROP            },
  {Si21XXC_ATV   , "ATV_IEN"                     , sizeof(Si21XXC_ATV_IEN_PROP_FIELDS                     )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_IEN_PROP_FIELDS                      , Si21XXC_ATV_IEN_PROP                      },
  {Si21XXC_ATV   , "ATV_INT_SENSE"               , sizeof(Si21XXC_ATV_INT_SENSE_PROP_FIELDS               )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_INT_SENSE_PROP_FIELDS                , Si21XXC_ATV_INT_SENSE_PROP                },
  {Si21XXC_ATV   , "ATV_PGA_TARGET"              , sizeof(Si21XXC_ATV_PGA_TARGET_PROP_FIELDS              )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_PGA_TARGET_PROP_FIELDS               , Si21XXC_ATV_PGA_TARGET_PROP               },
  {Si21XXC_ATV   , "ATV_RF_TOP"                  , sizeof(Si21XXC_ATV_RF_TOP_PROP_FIELDS                  )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_RF_TOP_PROP_FIELDS                   , Si21XXC_ATV_RF_TOP_PROP                   },
  {Si21XXC_ATV   , "ATV_RSQ_RSSI_THRESHOLD"      , sizeof(Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si21XXC_ATV   , "ATV_RSQ_SNR_THRESHOLD"       , sizeof(Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS       )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS        , Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP        },
  {Si21XXC_ATV   , "ATV_SIF_OUT"                 , sizeof(Si21XXC_ATV_SIF_OUT_PROP_FIELDS                 )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_SIF_OUT_PROP_FIELDS                  , Si21XXC_ATV_SIF_OUT_PROP                  },
  {Si21XXC_ATV   , "ATV_SOUND_AGC_LIMIT"         , sizeof(Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_FIELDS         )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_FIELDS          , Si21XXC_ATV_SOUND_AGC_LIMIT_PROP          },
  {Si21XXC_ATV   , "ATV_SOUND_AGC_SPEED"         , sizeof(Si21XXC_ATV_SOUND_AGC_SPEED_PROP_FIELDS         )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_SOUND_AGC_SPEED_PROP_FIELDS          , Si21XXC_ATV_SOUND_AGC_SPEED_PROP          },
  {Si21XXC_ATV   , "ATV_VIDEO_EQUALIZER"         , sizeof(Si21XXC_ATV_VIDEO_EQUALIZER_PROP_FIELDS         )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_VIDEO_EQUALIZER_PROP_FIELDS          , Si21XXC_ATV_VIDEO_EQUALIZER_PROP          },
  {Si21XXC_ATV   , "ATV_VIDEO_MODE"              , sizeof(Si21XXC_ATV_VIDEO_MODE_PROP_FIELDS              )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_VIDEO_MODE_PROP_FIELDS               , Si21XXC_ATV_VIDEO_MODE_PROP               },
  {Si21XXC_ATV   , "ATV_VSNR_CAP"                , sizeof(Si21XXC_ATV_VSNR_CAP_PROP_FIELDS                )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_ATV_VSNR_CAP_PROP_FIELDS                 , Si21XXC_ATV_VSNR_CAP_PROP                 },
  {Si21XXC_COMMON, "CRYSTAL_TRIM"                , sizeof(Si21XXC_CRYSTAL_TRIM_PROP_FIELDS                )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_CRYSTAL_TRIM_PROP_FIELDS                 , Si21XXC_CRYSTAL_TRIM_PROP                 },
  {Si21XXC_COMMON, "MASTER_IEN"                  , sizeof(Si21XXC_MASTER_IEN_PROP_FIELDS                  )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_MASTER_IEN_PROP_FIELDS                   , Si21XXC_MASTER_IEN_PROP                   },
  {Si21XXC_COMMON, "XOUT"                        , sizeof(Si21XXC_XOUT_PROP_FIELDS                        )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_XOUT_PROP_FIELDS                         , Si21XXC_XOUT_PROP                         },
  {Si21XXC_DTV   , "DTV_AGC_AUTO_FREEZE"         , sizeof(Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_FIELDS         )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_FIELDS          , Si21XXC_DTV_AGC_AUTO_FREEZE_PROP          },
  {Si21XXC_DTV   , "DTV_AGC_FREEZE_INPUT"        , sizeof(Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_FIELDS        )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_FIELDS         , Si21XXC_DTV_AGC_FREEZE_INPUT_PROP         },
  {Si21XXC_DTV   , "DTV_AGC_SPEED"               , sizeof(Si21XXC_DTV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_AGC_SPEED_PROP_FIELDS                , Si21XXC_DTV_AGC_SPEED_PROP                },
  {Si21XXC_DTV   , "DTV_CONFIG_IF_PORT"          , sizeof(Si21XXC_DTV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_CONFIG_IF_PORT_PROP_FIELDS           , Si21XXC_DTV_CONFIG_IF_PORT_PROP           },
  {Si21XXC_DTV   , "DTV_EXT_AGC"                 , sizeof(Si21XXC_DTV_EXT_AGC_PROP_FIELDS                 )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_EXT_AGC_PROP_FIELDS                  , Si21XXC_DTV_EXT_AGC_PROP                  },
  {Si21XXC_DTV   , "DTV_IEN"                     , sizeof(Si21XXC_DTV_IEN_PROP_FIELDS                     )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_IEN_PROP_FIELDS                      , Si21XXC_DTV_IEN_PROP                      },
  {Si21XXC_DTV   , "DTV_IF_AGC_SPEED"            , sizeof(Si21XXC_DTV_IF_AGC_SPEED_PROP_FIELDS            )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_IF_AGC_SPEED_PROP_FIELDS             , Si21XXC_DTV_IF_AGC_SPEED_PROP             },
  {Si21XXC_DTV   , "DTV_INITIAL_AGC_SPEED"       , sizeof(Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_FIELDS       )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_FIELDS        , Si21XXC_DTV_INITIAL_AGC_SPEED_PROP        },
  {Si21XXC_DTV   , "DTV_INITIAL_AGC_SPEED_PERIOD", sizeof(Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS)/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS , Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP },
  {Si21XXC_DTV   , "DTV_INTERNAL_ZIF"            , sizeof(Si21XXC_DTV_INTERNAL_ZIF_PROP_FIELDS            )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_INTERNAL_ZIF_PROP_FIELDS             , Si21XXC_DTV_INTERNAL_ZIF_PROP             },
  {Si21XXC_DTV   , "DTV_INT_SENSE"               , sizeof(Si21XXC_DTV_INT_SENSE_PROP_FIELDS               )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_INT_SENSE_PROP_FIELDS                , Si21XXC_DTV_INT_SENSE_PROP                },
  {Si21XXC_DTV   , "DTV_LIF_FREQ"                , sizeof(Si21XXC_DTV_LIF_FREQ_PROP_FIELDS                )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_LIF_FREQ_PROP_FIELDS                 , Si21XXC_DTV_LIF_FREQ_PROP                 },
  {Si21XXC_DTV   , "DTV_LIF_OUT"                 , sizeof(Si21XXC_DTV_LIF_OUT_PROP_FIELDS                 )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_LIF_OUT_PROP_FIELDS                  , Si21XXC_DTV_LIF_OUT_PROP                  },
  {Si21XXC_DTV   , "DTV_MODE"                    , sizeof(Si21XXC_DTV_MODE_PROP_FIELDS                    )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_MODE_PROP_FIELDS                     , Si21XXC_DTV_MODE_PROP                     },
  {Si21XXC_DTV   , "DTV_RF_AGC_SPEED"            , sizeof(Si21XXC_DTV_RF_AGC_SPEED_PROP_FIELDS            )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_RF_AGC_SPEED_PROP_FIELDS             , Si21XXC_DTV_RF_AGC_SPEED_PROP             },
  {Si21XXC_DTV   , "DTV_RF_TOP"                  , sizeof(Si21XXC_DTV_RF_TOP_PROP_FIELDS                  )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_RF_TOP_PROP_FIELDS                   , Si21XXC_DTV_RF_TOP_PROP                   },
  {Si21XXC_DTV   , "DTV_RSQ_RSSI_THRESHOLD"      , sizeof(Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si21XXC_DTV   , "DTV_WB_AGC_SPEED"            , sizeof(Si21XXC_DTV_WB_AGC_SPEED_PROP_FIELDS            )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_DTV_WB_AGC_SPEED_PROP_FIELDS             , Si21XXC_DTV_WB_AGC_SPEED_PROP             },
  {Si21XXC_TUNER , "TUNER_BLOCKED_VCO"           , sizeof(Si21XXC_TUNER_BLOCKED_VCO_PROP_FIELDS           )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_TUNER_BLOCKED_VCO_PROP_FIELDS            , Si21XXC_TUNER_BLOCKED_VCO_PROP            },
  {Si21XXC_TUNER , "TUNER_IEN"                   , sizeof(Si21XXC_TUNER_IEN_PROP_FIELDS                   )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_TUNER_IEN_PROP_FIELDS                    , Si21XXC_TUNER_IEN_PROP                    },
  {Si21XXC_TUNER , "TUNER_INT_SENSE"             , sizeof(Si21XXC_TUNER_INT_SENSE_PROP_FIELDS             )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_TUNER_INT_SENSE_PROP_FIELDS              , Si21XXC_TUNER_INT_SENSE_PROP              },
  {Si21XXC_TUNER , "TUNER_LO_INJECTION"          , sizeof(Si21XXC_TUNER_LO_INJECTION_PROP_FIELDS          )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_TUNER_LO_INJECTION_PROP_FIELDS           , Si21XXC_TUNER_LO_INJECTION_PROP           },
  {Si21XXC_TUNER , "TUNER_RETURN_LOSS"           , sizeof(Si21XXC_TUNER_RETURN_LOSS_PROP_FIELDS           )/sizeof(Si21XXC_fieldDicoStruct), Si21XXC_TUNER_RETURN_LOSS_PROP_FIELDS            , Si21XXC_TUNER_RETURN_LOSS_PROP            },
  {Si21XXC_TUNER , "TUNER_RETURN_LOSS_OPTIMIZE"  , sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_FIELDS  )/sizeof(Si21XXC_fieldDicoStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_FIELDS   , Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP   },
  {Si21XXC_TUNER , "TUNER_RETURN_LOSS_OPTIMIZE_2", sizeof(Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_FIELDS)/sizeof(Si21XXC_fieldDicoStruct), Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_FIELDS , Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP },
  {Si21XXC_TUNER , "WIDE_BAND_ATT_THRS"          , sizeof(Si2190B_WIDE_BAND_ATT_THRS_PROP_FIELDS)/sizeof(Si21XXC_fieldDicoStruct), Si2190B_WIDE_BAND_ATT_THRS_PROP_FIELDS , Si2190B_WIDE_BAND_ATT_THRS_PROP },
  {Si21XXC_TUNER , "TUNER_TF1_BOUNDARY_OFFSET"   , sizeof(Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_FIELDS)/sizeof(Si21XXC_fieldDicoStruct), Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_FIELDS , Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP },
};

int   Si21XXC_PropertyNames        (L1_Si21XXC_Context *api, char *msg)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si21XXC_propertyDictionary)/sizeof(Si21XXC_propertyInfoStruct);
  msg[0]='\0';
  for (propIndex=0; propIndex<size; propIndex++)
  {
    safe_strcat(msg,Si21XXC_propertyDictionary[propIndex].name);
    if (propIndex< (size-1)) safe_strcat(msg," ");
  }
  return propIndex;
};

int   Si21XXC_PropertyIndex        (L1_Si21XXC_Context *api, const char *property)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si21XXC_propertyDictionary)/sizeof(Si21XXC_propertyInfoStruct);
  for (propIndex=0; propIndex <size; propIndex++)
  {
    if (strcmp_nocase(property, Si21XXC_propertyDictionary[propIndex].name)==0)
    {
      return propIndex;
    }
  }
  return -1;
};

int   Si21XXC_PropertyFields       (L1_Si21XXC_Context *api, int propIndex, char *msg)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (fieldIndex=0; fieldIndex < Si21XXC_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    safe_strcat(msg, Si21XXC_propertyDictionary[propIndex].field[fieldIndex].name);
    if (fieldIndex< (Si21XXC_propertyDictionary[propIndex].nbFields-1)) safe_strcat(msg," ");
  }
  return -1;
};

int   Si21XXC_PropertyFieldIndex   (L1_Si21XXC_Context *api, int propIndex, char *field)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  for (fieldIndex=0; fieldIndex < Si21XXC_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    if (strcmp_nocase(field, Si21XXC_propertyDictionary[propIndex].field[fieldIndex].name)==0)
    {
      return fieldIndex;
    }
  }
  return -1;
};

int   Si21XXC_PropertyFieldEnums   (L1_Si21XXC_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int enumIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (enumIndex=0; enumIndex < Si21XXC_propertyDictionary[propIndex].field[fieldIndex].nbOptions; enumIndex++)
  {
    safe_strcat(msg, Si21XXC_propertyDictionary[propIndex].field[fieldIndex].option[enumIndex].name);
    if (enumIndex < (Si21XXC_propertyDictionary[propIndex].field[fieldIndex].nbOptions-1)) safe_strcat(msg," ");
  }
  return enumIndex;
};

int   Si21XXC_PropertyFieldRanges  (L1_Si21XXC_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int index;
  char buf[10];
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (index=0; index < 2; index++)
  {
    itoa(Si21XXC_propertyDictionary[propIndex].field[fieldIndex].option[index].value,buf,10);
    safe_strcat(msg, buf);
    if (index < 1) safe_strcat(msg," - ");
  }
  return index;
};

int   Si21XXC_GetValueFromEntry    (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field, char *entry, int *value)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */

  if (!strcmp_nocase(field.option[0].name,"MIN_RANGE"))
  {
    if (field.datatype== Si21XXC_UNSIGNED_INT || field.datatype== Si21XXC_UNSIGNED_CHAR)
    {
      *value = (unsigned int)atoi(entry);
      return 1;
    }
    else if (field.datatype == Si21XXC_SIGNED_INT || field.datatype == Si21XXC_SIGNED_CHAR)
    {
      *value = (int)atoi(entry);
      return 1;
    }
  }
  for (optionIndex=0; optionIndex < field.nbOptions; optionIndex++)
  {
    if (strcmp_nocase(entry, field.option[optionIndex].name     )==0)
    {
      *value = field.option[optionIndex].value;
      return 1;
    }
  }
  return 0;
};

char *Si21XXC_GetEnumFromValue     (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field, int iValue)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */
  if (field.nbOptions ==0 )
    {
    safe_sprintf(optionText, "%d", iValue);
    return optionText;
  }
  for (optionIndex=0; optionIndex < field.nbOptions; optionIndex++)
  {
    if (iValue == field.option[optionIndex].value)
    {
      return (char*)field.option[optionIndex].name;
    }
  }
  return (char*)NULL;
};

int   Si21XXC_GetValueFromField    (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field)
{
  short intValue;
  short *fieldAsInt;
  short iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si21XXC_SIGNED_INT   )
  {
      fieldAsInt= (short *) ((field.pField-(void *) &Si21XXC_prop)+ (void *)api->prop);
  }
  else if (field.datatype == Si21XXC_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si21XXC_prop)+ (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si21XXC_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si21XXC_prop)+ (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si21XXC_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned short *) ((field.pField-(void *) &Si21XXC_prop)+ (void *)api->prop);
  }

  return  *fieldAsInt;
};

char *Si21XXC_GetEnumFromField     (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field)
{
  int intValue;
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si21XXC_SIGNED_INT   )
  {
      fieldAsInt= (int *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop);
  }
  else if (field.datatype == Si21XXC_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si21XXC_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si21XXC_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned int *)((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop);
  }

  return Si21XXC_GetEnumFromValue(api, field, *fieldAsInt);
};

int   Si21XXC_SetFieldFromEntry    (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field, char *entry)
{
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &iTmp;
  if (Si21XXC_GetValueFromEntry(api, field, entry, fieldAsInt) == 0) return 0;
  if (field.datatype == Si21XXC_SIGNED_INT )
  {
    *( (int *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si21XXC_UNSIGNED_CHAR)
  {
    *( (unsigned char *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si21XXC_SIGNED_CHAR)
  {
    *( (char *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop))=iTmp;
  }
  else /* if (field.datatype == Si21XXC_UNSIGNED_INT) */
  {
    *( (unsigned int *) ((field.pField-(void *) &Si21XXC_prop) + (void *)api->prop))=iTmp;
  }

  return 1;
};

void  Si21XXC_showProperty         (L1_Si21XXC_Context *api, int propIndex)
{
  int fieldIndex;
  for (fieldIndex=0; fieldIndex<Si21XXC_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    safe_printf("%s:%s:%s = ", Si21XXC_featureText[Si21XXC_propertyDictionary[propIndex].feature], Si21XXC_propertyDictionary[propIndex].name, Si21XXC_propertyDictionary[propIndex].field[fieldIndex].name);
    safe_printf("<%s>\n", Si21XXC_GetEnumFromField(api, Si21XXC_propertyDictionary[propIndex].field[fieldIndex]));
  }

}

void  Si21XXC_showPropertyNamed    (L1_Si21XXC_Context *api, char *property)
{
  int propIndex;

  if ((propIndex = Si21XXC_PropertyIndex(api, property)) >= 0)
  {
    Si21XXC_showProperty(api, propIndex);
  }
  else
  {
    safe_printf("Unknown property '%s'\n", property);
  }

}

void  Si21XXC_setupProperty        (L1_Si21XXC_Context *api, int propIndex)
{
  #define LMAX 20
  char entry[LMAX];
  char setup_msg[1000];
  int fieldIndex;
  char isRangeType = 1;

  for (fieldIndex=0; fieldIndex<Si21XXC_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    isRangeType = (strcmp_nocase(Si21XXC_propertyDictionary[propIndex].field[fieldIndex].option->name,"MIN_RANGE") == 0);

    safe_printf("%s:%s:%s = ", Si21XXC_featureText[Si21XXC_propertyDictionary[propIndex].feature], Si21XXC_propertyDictionary[propIndex].name, Si21XXC_propertyDictionary[propIndex].field[fieldIndex].name);

    if ( isRangeType )
    {
      safe_printf("<%d>\n", Si21XXC_GetValueFromField(api, Si21XXC_propertyDictionary[propIndex].field[fieldIndex]));
      Si21XXC_PropertyFieldRanges(api, propIndex, fieldIndex, setup_msg);
      safe_printf("Range: <%s>  ",setup_msg);
    }
    else
    {
      Si21XXC_PropertyFieldEnums(api, propIndex, fieldIndex, setup_msg);
      safe_printf("<%s>\n Options: <%s>\n", Si21XXC_GetEnumFromField(api, Si21XXC_propertyDictionary[propIndex].field[fieldIndex]), setup_msg);
    }

    fgets(entry,LMAX,stdin);

    if (strlen(entry) > 1)
    {
      entry[strlen(entry)-1]='\0';
      if (!Si21XXC_SetFieldFromEntry(api, Si21XXC_propertyDictionary[propIndex].field[fieldIndex], entry))
      {
        safe_printf("Invalid entry!\n");
      }
    }

    if (isRangeType)
      safe_printf("<%d>\n\n", Si21XXC_GetValueFromField(api, Si21XXC_propertyDictionary[propIndex].field[fieldIndex]));
    else
      safe_printf("<%s>\n\n", Si21XXC_GetEnumFromField(api, Si21XXC_propertyDictionary[propIndex].field[fieldIndex]));
  }
}

int   Si21XXC_setupProperties      (L1_Si21XXC_Context *api, Si21XXC_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si21XXC_propertyDictionary)/sizeof(Si21XXC_propertyInfoStruct);

  safe_printf("\n%s properties:\n\n", Si21XXC_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si21XXC_propertyDictionary[propertyIndex].feature != feature) continue;
    Si21XXC_setupProperty(api, propertyIndex);
  }
  return 0;
}

int Si21XXC_setupATVProperties       (L1_Si21XXC_Context *api)
{
  SiTRACE("Si21XXC_setupATVProperties       \n");
  Si21XXC_setupProperties(api, Si21XXC_ATV);
  return 0;
}

int Si21XXC_setupCOMMONProperties    (L1_Si21XXC_Context *api)
{
  SiTRACE("Si21XXC_setupCOMMONProperties    \n");
  Si21XXC_setupProperties(api, Si21XXC_COMMON);
  return 0;
}

int Si21XXC_setupDTVProperties       (L1_Si21XXC_Context *api)
{
  SiTRACE("Si21XXC_setupDTVProperties       \n");
  Si21XXC_setupProperties(api, Si21XXC_DTV);
  return 0;
}

int Si21XXC_setupTUNERProperties     (L1_Si21XXC_Context *api)
{
  SiTRACE("Si21XXC_setupTUNERProperties     \n");
  Si21XXC_setupProperties(api, Si21XXC_TUNER);
  return 0;
}

int Si21XXC_setupAllProperties  (L1_Si21XXC_Context *api)
{
  Si21XXC_setupATVProperties       (api);
  Si21XXC_setupCOMMONProperties    (api);
  Si21XXC_setupDTVProperties       (api);
  Si21XXC_setupTUNERProperties     (api);
  return 0;
}


#endif /* Si21XXC_COMMAND_LINE_APPLICATION */







