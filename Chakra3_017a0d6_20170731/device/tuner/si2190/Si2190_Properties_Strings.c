/*************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 1 API
   API properties strings functions definitions
   FILE: Si2190_L1_Properties.c
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Tag:  ROM40_0_A_build_10_V0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si2190_COMMAND_PROTOTYPES

#include "Si2190_L1_API.h"
#include "Si2190_Properties_Strings.h"

#ifdef Si2190_COMMAND_LINE_APPLICATION

/* define a local PropObj variable to use for the Property Dictionary initializer */
Si2190_PropObj Si2190_prop;
char optionText[20];

/* _properties_features_text_insertion_start */
const char *Si2190_featureText[] =
{
  "ATV",
  "COMMON",
  "DTV",
  "TUNER",
};
/* _properties_features_text_insertion_point */

/* _properties_strings_insertion_start */
Si2190_optionStruct    Si2190_ATV_AFC_RANGE_PROP_RANGE_KHZ[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si2190_fieldDicoStruct Si2190_ATV_AFC_RANGE_PROP_FIELDS[] =
{
  {"RANGE_KHZ", Si2190_UNSIGNED_INT, &Si2190_prop.atv_afc_range.range_khz, sizeof(Si2190_ATV_AFC_RANGE_PROP_RANGE_KHZ)/sizeof(Si2190_optionStruct), Si2190_ATV_AFC_RANGE_PROP_RANGE_KHZ},
};

Si2190_optionStruct    Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
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
  {"248",      248},
  {"250",      250},
  {"251",      251},
  {"CUSTOM",     1},
};
Si2190_fieldDicoStruct Si2190_ATV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_agc_speed.if_agc_speed, sizeof(Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2190_optionStruct), Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED},
};

Si2190_optionStruct    Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[] =
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
  {"248",      248},
  {"250",      250},
  {"251",      251},
  {"CUSTOM",     1},
};
Si2190_optionStruct    Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_fieldDicoStruct Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_agc_speed_low_rssi.if_agc_speed, sizeof(Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED)/sizeof(Si2190_optionStruct), Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED},
  {"THLD",           Si2190_SIGNED_CHAR, &Si2190_prop.atv_agc_speed_low_rssi.thld        , sizeof(Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD        )/sizeof(Si2190_optionStruct), Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD        },
};

Si2190_optionStruct    Si2190_ATV_ARTIFICIAL_SNOW_PROP_GAIN[] =
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
Si2190_optionStruct    Si2190_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_fieldDicoStruct Si2190_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[] =
{
  {"GAIN",   Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_artificial_snow.gain  , sizeof(Si2190_ATV_ARTIFICIAL_SNOW_PROP_GAIN  )/sizeof(Si2190_optionStruct), Si2190_ATV_ARTIFICIAL_SNOW_PROP_GAIN  },
  {"OFFSET",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_artificial_snow.offset, sizeof(Si2190_ATV_ARTIFICIAL_SNOW_PROP_OFFSET)/sizeof(Si2190_optionStruct), Si2190_ATV_ARTIFICIAL_SNOW_PROP_OFFSET},
};

Si2190_optionStruct    Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS[] =
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
Si2190_optionStruct    Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW[] =
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
Si2190_fieldDicoStruct Si2190_ATV_AUDIO_MODE_PROP_FIELDS[] =
{
  {"AUDIO_SYS",    Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_audio_mode.audio_sys   , sizeof(Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS   )/sizeof(Si2190_optionStruct), Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS   },
  {"CHAN_FILT_BW", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_audio_mode.chan_filt_bw, sizeof(Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW)/sizeof(Si2190_optionStruct), Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW},
};

Si2190_optionStruct    Si2190_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[] =
{
  {"CVBS_IF2B_SOUND_IF2A",           0},
  {"CVBS_IF2B_SOUND_IF2A_75OHM",     1},
  {"LIF_DIFF_IF1",                   8},
  {"LIF_DIFF_IF2",                  10},
  {"LIF_SE_IF1A",                   12},
  {"LIF_SE_IF2A",                   14},
};
Si2190_fieldDicoStruct Si2190_ATV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"ATV_OUT_TYPE", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_config_if_port.atv_out_type, sizeof(Si2190_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE)/sizeof(Si2190_optionStruct), Si2190_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE},
};

Si2190_optionStruct    Si2190_ATV_CVBS_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_optionStruct    Si2190_ATV_CVBS_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_fieldDicoStruct Si2190_ATV_CVBS_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_cvbs_out.offset, sizeof(Si2190_ATV_CVBS_OUT_PROP_OFFSET)/sizeof(Si2190_optionStruct), Si2190_ATV_CVBS_OUT_PROP_OFFSET},
  {"AMP",    Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_cvbs_out.amp   , sizeof(Si2190_ATV_CVBS_OUT_PROP_AMP   )/sizeof(Si2190_optionStruct), Si2190_ATV_CVBS_OUT_PROP_AMP   },
};

Si2190_optionStruct    Si2190_ATV_CVBS_OUT_FINE_PROP_OFFSET[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_optionStruct    Si2190_ATV_CVBS_OUT_FINE_PROP_AMP[] =
{
  {"MIN_RANGE",    25},
  {"MAX_RANGE",   100}
};
Si2190_fieldDicoStruct Si2190_ATV_CVBS_OUT_FINE_PROP_FIELDS[] =
{
  {"OFFSET",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_cvbs_out_fine.offset, sizeof(Si2190_ATV_CVBS_OUT_FINE_PROP_OFFSET)/sizeof(Si2190_optionStruct), Si2190_ATV_CVBS_OUT_FINE_PROP_OFFSET},
  {"AMP",    Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_cvbs_out_fine.amp   , sizeof(Si2190_ATV_CVBS_OUT_FINE_PROP_AMP   )/sizeof(Si2190_optionStruct), Si2190_ATV_CVBS_OUT_FINE_PROP_AMP   },
};

Si2190_optionStruct    Si2190_ATV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_IEN_PROP_PCLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_IEN_PROP_DLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_IEN_PROP_SNRLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_IEN_PROP_SNRHIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_ATV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN",  Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_ien.chlien , sizeof(Si2190_ATV_IEN_PROP_CHLIEN )/sizeof(Si2190_optionStruct), Si2190_ATV_IEN_PROP_CHLIEN },
  {"PCLIEN",  Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_ien.pclien , sizeof(Si2190_ATV_IEN_PROP_PCLIEN )/sizeof(Si2190_optionStruct), Si2190_ATV_IEN_PROP_PCLIEN },
  {"DLIEN",   Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_ien.dlien  , sizeof(Si2190_ATV_IEN_PROP_DLIEN  )/sizeof(Si2190_optionStruct), Si2190_ATV_IEN_PROP_DLIEN  },
  {"SNRLIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_ien.snrlien, sizeof(Si2190_ATV_IEN_PROP_SNRLIEN)/sizeof(Si2190_optionStruct), Si2190_ATV_IEN_PROP_SNRLIEN},
  {"SNRHIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_ien.snrhien, sizeof(Si2190_ATV_IEN_PROP_SNRHIEN)/sizeof(Si2190_optionStruct), Si2190_ATV_IEN_PROP_SNRHIEN},
};

Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_PCLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_DLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRHNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_PCLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_DLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRHPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_ATV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN",  Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.chlnegen , sizeof(Si2190_ATV_INT_SENSE_PROP_CHLNEGEN )/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_CHLNEGEN },
  {"PCLNEGEN",  Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.pclnegen , sizeof(Si2190_ATV_INT_SENSE_PROP_PCLNEGEN )/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_PCLNEGEN },
  {"DLNEGEN",   Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.dlnegen  , sizeof(Si2190_ATV_INT_SENSE_PROP_DLNEGEN  )/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_DLNEGEN  },
  {"SNRLNEGEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.snrlnegen, sizeof(Si2190_ATV_INT_SENSE_PROP_SNRLNEGEN)/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_SNRLNEGEN},
  {"SNRHNEGEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.snrhnegen, sizeof(Si2190_ATV_INT_SENSE_PROP_SNRHNEGEN)/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_SNRHNEGEN},
  {"CHLPOSEN",  Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.chlposen , sizeof(Si2190_ATV_INT_SENSE_PROP_CHLPOSEN )/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_CHLPOSEN },
  {"PCLPOSEN",  Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.pclposen , sizeof(Si2190_ATV_INT_SENSE_PROP_PCLPOSEN )/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_PCLPOSEN },
  {"DLPOSEN",   Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.dlposen  , sizeof(Si2190_ATV_INT_SENSE_PROP_DLPOSEN  )/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_DLPOSEN  },
  {"SNRLPOSEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.snrlposen, sizeof(Si2190_ATV_INT_SENSE_PROP_SNRLPOSEN)/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_SNRLPOSEN},
  {"SNRHPOSEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_int_sense.snrhposen, sizeof(Si2190_ATV_INT_SENSE_PROP_SNRHPOSEN)/sizeof(Si2190_optionStruct), Si2190_ATV_INT_SENSE_PROP_SNRHPOSEN},
};

Si2190_optionStruct    Si2190_ATV_PGA_TARGET_PROP_PGA_TARGET[] =
{
  {"MIN_RANGE",   -13},
  {"MAX_RANGE",     7}
};
Si2190_optionStruct    Si2190_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_ATV_PGA_TARGET_PROP_FIELDS[] =
{
  {"PGA_TARGET",        Si2190_SIGNED_CHAR, &Si2190_prop.atv_pga_target.pga_target     , sizeof(Si2190_ATV_PGA_TARGET_PROP_PGA_TARGET     )/sizeof(Si2190_optionStruct), Si2190_ATV_PGA_TARGET_PROP_PGA_TARGET     },
  {"OVERRIDE_ENABLE", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_pga_target.override_enable, sizeof(Si2190_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE)/sizeof(Si2190_optionStruct), Si2190_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE},
};

Si2190_optionStruct    Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP[] =
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
Si2190_fieldDicoStruct Si2190_ATV_RF_TOP_PROP_FIELDS[] =
{
  {"ATV_RF_TOP", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_rf_top.atv_rf_top, sizeof(Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP)/sizeof(Si2190_optionStruct), Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP},
};

Si2190_optionStruct    Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_optionStruct    Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_fieldDicoStruct Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_rsq_rssi_threshold.lo, sizeof(Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si2190_optionStruct), Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_rsq_rssi_threshold.hi, sizeof(Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si2190_optionStruct), Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si2190_optionStruct    Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_optionStruct    Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_fieldDicoStruct Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS[] =
{
  {"LO", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_rsq_snr_threshold.lo, sizeof(Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_LO)/sizeof(Si2190_optionStruct), Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_LO},
  {"HI", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_rsq_snr_threshold.hi, sizeof(Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_HI)/sizeof(Si2190_optionStruct), Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_HI},
};

Si2190_optionStruct    Si2190_ATV_SIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_optionStruct    Si2190_ATV_SIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_fieldDicoStruct Si2190_ATV_SIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_sif_out.offset, sizeof(Si2190_ATV_SIF_OUT_PROP_OFFSET)/sizeof(Si2190_optionStruct), Si2190_ATV_SIF_OUT_PROP_OFFSET},
  {"AMP",    Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_sif_out.amp   , sizeof(Si2190_ATV_SIF_OUT_PROP_AMP   )/sizeof(Si2190_optionStruct), Si2190_ATV_SIF_OUT_PROP_AMP   },
};

Si2190_optionStruct    Si2190_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN[] =
{
  {"MIN_RANGE",   -84},
  {"MAX_RANGE",    84}
};
Si2190_optionStruct    Si2190_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN[] =
{
  {"MIN_RANGE",   -84},
  {"MAX_RANGE",    84}
};
Si2190_fieldDicoStruct Si2190_ATV_SOUND_AGC_LIMIT_PROP_FIELDS[] =
{
  {"MAX_GAIN",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_sound_agc_limit.max_gain, sizeof(Si2190_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN)/sizeof(Si2190_optionStruct), Si2190_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN},
  {"MIN_GAIN",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_sound_agc_limit.min_gain, sizeof(Si2190_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN)/sizeof(Si2190_optionStruct), Si2190_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN},
};

Si2190_optionStruct    Si2190_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si2190_optionStruct    Si2190_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si2190_fieldDicoStruct Si2190_ATV_SOUND_AGC_SPEED_PROP_FIELDS[] =
{
  {"SYSTEM_L",      Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_sound_agc_speed.system_l     , sizeof(Si2190_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L     )/sizeof(Si2190_optionStruct), Si2190_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L     },
  {"OTHER_SYSTEMS", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_sound_agc_speed.other_systems, sizeof(Si2190_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS)/sizeof(Si2190_optionStruct), Si2190_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS},
};

Si2190_optionStruct    Si2190_ATV_VIDEO_EQUALIZER_PROP_SLOPE[] =
{
  {"MIN_RANGE",    -8},
  {"MAX_RANGE",     7}
};
Si2190_fieldDicoStruct Si2190_ATV_VIDEO_EQUALIZER_PROP_FIELDS[] =
{
  {"SLOPE",   Si2190_SIGNED_CHAR, &Si2190_prop.atv_video_equalizer.slope, sizeof(Si2190_ATV_VIDEO_EQUALIZER_PROP_SLOPE)/sizeof(Si2190_optionStruct), Si2190_ATV_VIDEO_EQUALIZER_PROP_SLOPE},
};

Si2190_optionStruct    Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS[] =
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
Si2190_optionStruct    Si2190_ATV_VIDEO_MODE_PROP_COLOR[] =
{
  {"PAL_NTSC",     0},
  {"SECAM",        1},
};
Si2190_optionStruct    Si2190_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si2190_fieldDicoStruct Si2190_ATV_VIDEO_MODE_PROP_FIELDS[] =
{
  {"VIDEO_SYS",     Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_video_mode.video_sys    , sizeof(Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS    )/sizeof(Si2190_optionStruct), Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS    },
  {"COLOR",         Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_video_mode.color        , sizeof(Si2190_ATV_VIDEO_MODE_PROP_COLOR        )/sizeof(Si2190_optionStruct), Si2190_ATV_VIDEO_MODE_PROP_COLOR        },
  {"INVERT_SIGNAL", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_video_mode.invert_signal, sizeof(Si2190_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL)/sizeof(Si2190_optionStruct), Si2190_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL},
};

Si2190_optionStruct    Si2190_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   127}
};
Si2190_fieldDicoStruct Si2190_ATV_VSNR_CAP_PROP_FIELDS[] =
{
  {"ATV_VSNR_CAP", Si2190_UNSIGNED_CHAR, &Si2190_prop.atv_vsnr_cap.atv_vsnr_cap, sizeof(Si2190_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP)/sizeof(Si2190_optionStruct), Si2190_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP},
};

Si2190_optionStruct    Si2190_CRYSTAL_TRIM_PROP_XO_CAP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si2190_fieldDicoStruct Si2190_CRYSTAL_TRIM_PROP_FIELDS[] =
{
  {"XO_CAP", Si2190_UNSIGNED_CHAR, &Si2190_prop.crystal_trim.xo_cap, sizeof(Si2190_CRYSTAL_TRIM_PROP_XO_CAP)/sizeof(Si2190_optionStruct), Si2190_CRYSTAL_TRIM_PROP_XO_CAP},
};

Si2190_optionStruct    Si2190_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   207}
};
Si2190_fieldDicoStruct Si2190_DEBUG_SAMPLE_FREQ_PROP_FIELDS[] =
{
  {"FS_MHZ", Si2190_UNSIGNED_INT, &Si2190_prop.debug_sample_freq.fs_mhz, sizeof(Si2190_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ)/sizeof(Si2190_optionStruct), Si2190_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ},
};

Si2190_optionStruct    Si2190_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[] =
{
  {"LOW",      0},
  {"HIGH",     1},
};
Si2190_optionStruct    Si2190_DTV_AGC_FREEZE_INPUT_PROP_PIN[] =
{
  {"NONE",         0},
  {"GPIO1",        1},
  {"GPIO2",        2},
  {"RESERVED",     3},
  {"AGC1",         4},
  {"AGC2",         5},
};
Si2190_fieldDicoStruct Si2190_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[] =
{
  {"LEVEL", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_agc_freeze_input.level, sizeof(Si2190_DTV_AGC_FREEZE_INPUT_PROP_LEVEL)/sizeof(Si2190_optionStruct), Si2190_DTV_AGC_FREEZE_INPUT_PROP_LEVEL},
  {"PIN",   Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_agc_freeze_input.pin  , sizeof(Si2190_DTV_AGC_FREEZE_INPUT_PROP_PIN  )/sizeof(Si2190_optionStruct), Si2190_DTV_AGC_FREEZE_INPUT_PROP_PIN  },
};

Si2190_optionStruct    Si2190_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
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
Si2190_optionStruct    Si2190_DTV_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si2190_fieldDicoStruct Si2190_DTV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_agc_speed.if_agc_speed, sizeof(Si2190_DTV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2190_optionStruct), Si2190_DTV_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_agc_speed.agc_decim   , sizeof(Si2190_DTV_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si2190_optionStruct), Si2190_DTV_AGC_SPEED_PROP_AGC_DECIM   },
};

Si2190_optionStruct    Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[] =
{
  {"LIF_IF1",         0},
  {"LIF_IF2",         1},
  {"LIF_SE_IF1A",     4},
  {"LIF_SE_IF2A",     5},
};
Si2190_optionStruct    Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[] =
{
  {"INTERNAL",      0},
  {"AGC1_3DB",      1},
  {"AGC2_3DB",      2},
  {"AGC1_FULL",     3},
  {"AGC2_FULL",     4},
};
Si2190_fieldDicoStruct Si2190_DTV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"DTV_OUT_TYPE",   Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_config_if_port.dtv_out_type  , sizeof(Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  )/sizeof(Si2190_optionStruct), Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  },
  {"DTV_AGC_SOURCE", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_config_if_port.dtv_agc_source, sizeof(Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE)/sizeof(Si2190_optionStruct), Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE},
};

Si2190_optionStruct    Si2190_DTV_EXT_AGC_PROP_MIN_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_optionStruct    Si2190_DTV_EXT_AGC_PROP_MAX_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_fieldDicoStruct Si2190_DTV_EXT_AGC_PROP_FIELDS[] =
{
  {"MIN_10MV", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_ext_agc.min_10mv, sizeof(Si2190_DTV_EXT_AGC_PROP_MIN_10MV)/sizeof(Si2190_optionStruct), Si2190_DTV_EXT_AGC_PROP_MIN_10MV},
  {"MAX_10MV", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_ext_agc.max_10mv, sizeof(Si2190_DTV_EXT_AGC_PROP_MAX_10MV)/sizeof(Si2190_optionStruct), Si2190_DTV_EXT_AGC_PROP_MAX_10MV},
};

Si2190_optionStruct    Si2190_DTV_FILTER_SELECT_PROP_FILTER[] =
{
  {"LEGACY",      0},
  {"CUSTOM1",     1},
  {"CUSTOM2",     2},
};
Si2190_fieldDicoStruct Si2190_DTV_FILTER_SELECT_PROP_FIELDS[] =
{
  {"FILTER", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_filter_select.filter, sizeof(Si2190_DTV_FILTER_SELECT_PROP_FILTER)/sizeof(Si2190_optionStruct), Si2190_DTV_FILTER_SELECT_PROP_FILTER},
};

Si2190_optionStruct    Si2190_DTV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_DTV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_ien.chlien, sizeof(Si2190_DTV_IEN_PROP_CHLIEN)/sizeof(Si2190_optionStruct), Si2190_DTV_IEN_PROP_CHLIEN},
};

Si2190_optionStruct    Si2190_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[] =
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
Si2190_optionStruct    Si2190_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si2190_fieldDicoStruct Si2190_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_initial_agc_speed.if_agc_speed, sizeof(Si2190_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2190_optionStruct), Si2190_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_initial_agc_speed.agc_decim   , sizeof(Si2190_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si2190_optionStruct), Si2190_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   },
};

Si2190_optionStruct    Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si2190_fieldDicoStruct Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[] =
{
  {"PERIOD", Si2190_UNSIGNED_INT, &Si2190_prop.dtv_initial_agc_speed_period.period, sizeof(Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD)/sizeof(Si2190_optionStruct), Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD},
};

Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_ATSC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_QAM_US[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_DVBT[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_DVBC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_ISDBT[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_ISDBC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_DTMB[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2190_fieldDicoStruct Si2190_DTV_INTERNAL_ZIF_PROP_FIELDS[] =
{
  {"ATSC",   Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.atsc  , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_ATSC  )/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_ATSC  },
  {"QAM_US", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.qam_us, sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_QAM_US)/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_QAM_US},
  {"DVBT",   Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.dvbt  , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_DVBT  )/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_DVBT  },
  {"DVBC",   Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.dvbc  , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_DVBC  )/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_DVBC  },
  {"ISDBT",  Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.isdbt , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_ISDBT )/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_ISDBT },
  {"ISDBC",  Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.isdbc , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_ISDBC )/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_ISDBC },
  {"DTMB",   Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_internal_zif.dtmb  , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_DTMB  )/sizeof(Si2190_optionStruct), Si2190_DTV_INTERNAL_ZIF_PROP_DTMB  },
};

Si2190_optionStruct    Si2190_DTV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_DTV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_DTV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_int_sense.chlnegen, sizeof(Si2190_DTV_INT_SENSE_PROP_CHLNEGEN)/sizeof(Si2190_optionStruct), Si2190_DTV_INT_SENSE_PROP_CHLNEGEN},
  {"CHLPOSEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_int_sense.chlposen, sizeof(Si2190_DTV_INT_SENSE_PROP_CHLPOSEN)/sizeof(Si2190_optionStruct), Si2190_DTV_INT_SENSE_PROP_CHLPOSEN},
};

Si2190_optionStruct    Si2190_DTV_LIF_FREQ_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",  7000}
};
Si2190_fieldDicoStruct Si2190_DTV_LIF_FREQ_PROP_FIELDS[] =
{
  {"OFFSET", Si2190_UNSIGNED_INT, &Si2190_prop.dtv_lif_freq.offset, sizeof(Si2190_DTV_LIF_FREQ_PROP_OFFSET)/sizeof(Si2190_optionStruct), Si2190_DTV_LIF_FREQ_PROP_OFFSET},
};

Si2190_optionStruct    Si2190_DTV_LIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_optionStruct    Si2190_DTV_LIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2190_fieldDicoStruct Si2190_DTV_LIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_lif_out.offset, sizeof(Si2190_DTV_LIF_OUT_PROP_OFFSET)/sizeof(Si2190_optionStruct), Si2190_DTV_LIF_OUT_PROP_OFFSET},
  {"AMP",    Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_lif_out.amp   , sizeof(Si2190_DTV_LIF_OUT_PROP_AMP   )/sizeof(Si2190_optionStruct), Si2190_DTV_LIF_OUT_PROP_AMP   },
};

Si2190_optionStruct    Si2190_DTV_MODE_PROP_BW[] =
{
  {"BW_6MHZ",     6},
  {"BW_7MHZ",     7},
  {"BW_8MHZ",     8},
};
Si2190_optionStruct    Si2190_DTV_MODE_PROP_MODULATION[] =
{
  {"ATSC",       0},
  {"QAM_US",     1},
  {"DVBT",       2},
  {"DVBC",       3},
  {"ISDBT",      4},
  {"ISDBC",      5},
  {"DTMB",       6},
  {"CW",        15},
};
Si2190_optionStruct    Si2190_DTV_MODE_PROP_INVERT_SPECTRUM[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si2190_fieldDicoStruct Si2190_DTV_MODE_PROP_FIELDS[] =
{
  {"BW",              Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_mode.bw             , sizeof(Si2190_DTV_MODE_PROP_BW             )/sizeof(Si2190_optionStruct), Si2190_DTV_MODE_PROP_BW             },
  {"MODULATION",      Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_mode.modulation     , sizeof(Si2190_DTV_MODE_PROP_MODULATION     )/sizeof(Si2190_optionStruct), Si2190_DTV_MODE_PROP_MODULATION     },
  {"INVERT_SPECTRUM", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_mode.invert_spectrum, sizeof(Si2190_DTV_MODE_PROP_INVERT_SPECTRUM)/sizeof(Si2190_optionStruct), Si2190_DTV_MODE_PROP_INVERT_SPECTRUM},
};

Si2190_optionStruct    Si2190_DTV_PGA_LIMITS_PROP_MIN[] =
{
  {"MIN_RANGE",    -1},
  {"MAX_RANGE",    56}
};
Si2190_optionStruct    Si2190_DTV_PGA_LIMITS_PROP_MAX[] =
{
  {"MIN_RANGE",    -1},
  {"MAX_RANGE",    56}
};
Si2190_fieldDicoStruct Si2190_DTV_PGA_LIMITS_PROP_FIELDS[] =
{
  {"MIN",   Si2190_SIGNED_CHAR, &Si2190_prop.dtv_pga_limits.min, sizeof(Si2190_DTV_PGA_LIMITS_PROP_MIN)/sizeof(Si2190_optionStruct), Si2190_DTV_PGA_LIMITS_PROP_MIN},
  {"MAX",   Si2190_SIGNED_CHAR, &Si2190_prop.dtv_pga_limits.max, sizeof(Si2190_DTV_PGA_LIMITS_PROP_MAX)/sizeof(Si2190_optionStruct), Si2190_DTV_PGA_LIMITS_PROP_MAX},
};

Si2190_optionStruct    Si2190_DTV_PGA_TARGET_PROP_PGA_TARGET[] =
{
  {"MIN_RANGE",   -13},
  {"MAX_RANGE",     7}
};
Si2190_optionStruct    Si2190_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_DTV_PGA_TARGET_PROP_FIELDS[] =
{
  {"PGA_TARGET",        Si2190_SIGNED_CHAR, &Si2190_prop.dtv_pga_target.pga_target     , sizeof(Si2190_DTV_PGA_TARGET_PROP_PGA_TARGET     )/sizeof(Si2190_optionStruct), Si2190_DTV_PGA_TARGET_PROP_PGA_TARGET     },
  {"OVERRIDE_ENABLE", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_pga_target.override_enable, sizeof(Si2190_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE)/sizeof(Si2190_optionStruct), Si2190_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE},
};

Si2190_optionStruct    Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP[] =
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
Si2190_fieldDicoStruct Si2190_DTV_RF_TOP_PROP_FIELDS[] =
{
  {"DTV_RF_TOP", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_rf_top.dtv_rf_top, sizeof(Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP)/sizeof(Si2190_optionStruct), Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP},
};

Si2190_optionStruct    Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_optionStruct    Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2190_fieldDicoStruct Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si2190_SIGNED_CHAR, &Si2190_prop.dtv_rsq_rssi_threshold.lo, sizeof(Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si2190_optionStruct), Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si2190_SIGNED_CHAR, &Si2190_prop.dtv_rsq_rssi_threshold.hi, sizeof(Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si2190_optionStruct), Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si2190_optionStruct    Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH[] =
{
  {"4_Hz",          0},
  {"8_Hz",          1},
  {"15_Hz",         2},
  {"30_Hz",         3},
  {"61_Hz",         4},
  {"121_Hz",        5},
  {"243_Hz",        6},
  {"486_Hz",        7},
  {"972_Hz",        8},
  {"1943_Hz",       9},
  {"3888_Hz",      10},
  {"7779_Hz",      11},
  {"15573_Hz",     12},
  {"31207_Hz",     13},
  {"62658_Hz",     14},
  {"126303_Hz",    15},
  {"DEFAULT",      16},
};
Si2190_fieldDicoStruct Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS[] =
{
  {"BANDWIDTH", Si2190_UNSIGNED_CHAR, &Si2190_prop.dtv_zif_dc_canceller_bw.bandwidth, sizeof(Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH)/sizeof(Si2190_optionStruct), Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH},
};

Si2190_optionStruct    Si2190_MASTER_IEN_PROP_TUNIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2190_optionStruct    Si2190_MASTER_IEN_PROP_ATVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2190_optionStruct    Si2190_MASTER_IEN_PROP_DTVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2190_optionStruct    Si2190_MASTER_IEN_PROP_ERRIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2190_optionStruct    Si2190_MASTER_IEN_PROP_CTSIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2190_fieldDicoStruct Si2190_MASTER_IEN_PROP_FIELDS[] =
{
  {"TUNIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.master_ien.tunien, sizeof(Si2190_MASTER_IEN_PROP_TUNIEN)/sizeof(Si2190_optionStruct), Si2190_MASTER_IEN_PROP_TUNIEN},
  {"ATVIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.master_ien.atvien, sizeof(Si2190_MASTER_IEN_PROP_ATVIEN)/sizeof(Si2190_optionStruct), Si2190_MASTER_IEN_PROP_ATVIEN},
  {"DTVIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.master_ien.dtvien, sizeof(Si2190_MASTER_IEN_PROP_DTVIEN)/sizeof(Si2190_optionStruct), Si2190_MASTER_IEN_PROP_DTVIEN},
  {"ERRIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.master_ien.errien, sizeof(Si2190_MASTER_IEN_PROP_ERRIEN)/sizeof(Si2190_optionStruct), Si2190_MASTER_IEN_PROP_ERRIEN},
  {"CTSIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.master_ien.ctsien, sizeof(Si2190_MASTER_IEN_PROP_CTSIEN)/sizeof(Si2190_optionStruct), Si2190_MASTER_IEN_PROP_CTSIEN},
};

Si2190_optionStruct    Si2190_TUNER_BLOCKED_VCO_PROP_VCO_CODE[] =
{
  {"MIN_RANGE", -32768},
  {"MAX_RANGE", 32767}
};
Si2190_fieldDicoStruct Si2190_TUNER_BLOCKED_VCO_PROP_FIELDS[] =
{
  {"VCO_CODE",   Si2190_SIGNED_INT, &Si2190_prop.tuner_blocked_vco.vco_code, sizeof(Si2190_TUNER_BLOCKED_VCO_PROP_VCO_CODE)/sizeof(Si2190_optionStruct), Si2190_TUNER_BLOCKED_VCO_PROP_VCO_CODE},
};

Si2190_optionStruct    Si2190_TUNER_IEN_PROP_TCIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_IEN_PROP_RSSILIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_IEN_PROP_RSSIHIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_TUNER_IEN_PROP_FIELDS[] =
{
  {"TCIEN",    Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_ien.tcien   , sizeof(Si2190_TUNER_IEN_PROP_TCIEN   )/sizeof(Si2190_optionStruct), Si2190_TUNER_IEN_PROP_TCIEN   },
  {"RSSILIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_ien.rssilien, sizeof(Si2190_TUNER_IEN_PROP_RSSILIEN)/sizeof(Si2190_optionStruct), Si2190_TUNER_IEN_PROP_RSSILIEN},
  {"RSSIHIEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_ien.rssihien, sizeof(Si2190_TUNER_IEN_PROP_RSSIHIEN)/sizeof(Si2190_optionStruct), Si2190_TUNER_IEN_PROP_RSSIHIEN},
};

Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_TCNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSILNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSIHNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_TCPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSILPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSIHPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2190_fieldDicoStruct Si2190_TUNER_INT_SENSE_PROP_FIELDS[] =
{
  {"TCNEGEN",    Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_int_sense.tcnegen   , sizeof(Si2190_TUNER_INT_SENSE_PROP_TCNEGEN   )/sizeof(Si2190_optionStruct), Si2190_TUNER_INT_SENSE_PROP_TCNEGEN   },
  {"RSSILNEGEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_int_sense.rssilnegen, sizeof(Si2190_TUNER_INT_SENSE_PROP_RSSILNEGEN)/sizeof(Si2190_optionStruct), Si2190_TUNER_INT_SENSE_PROP_RSSILNEGEN},
  {"RSSIHNEGEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_int_sense.rssihnegen, sizeof(Si2190_TUNER_INT_SENSE_PROP_RSSIHNEGEN)/sizeof(Si2190_optionStruct), Si2190_TUNER_INT_SENSE_PROP_RSSIHNEGEN},
  {"TCPOSEN",    Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_int_sense.tcposen   , sizeof(Si2190_TUNER_INT_SENSE_PROP_TCPOSEN   )/sizeof(Si2190_optionStruct), Si2190_TUNER_INT_SENSE_PROP_TCPOSEN   },
  {"RSSILPOSEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_int_sense.rssilposen, sizeof(Si2190_TUNER_INT_SENSE_PROP_RSSILPOSEN)/sizeof(Si2190_optionStruct), Si2190_TUNER_INT_SENSE_PROP_RSSILPOSEN},
  {"RSSIHPOSEN", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_int_sense.rssihposen, sizeof(Si2190_TUNER_INT_SENSE_PROP_RSSIHPOSEN)/sizeof(Si2190_optionStruct), Si2190_TUNER_INT_SENSE_PROP_RSSIHPOSEN},
};

Si2190_optionStruct    Si2190_TUNER_LO_INJECTION_PROP_BAND_1[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2190_optionStruct    Si2190_TUNER_LO_INJECTION_PROP_BAND_2[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2190_optionStruct    Si2190_TUNER_LO_INJECTION_PROP_BAND_3[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2190_fieldDicoStruct Si2190_TUNER_LO_INJECTION_PROP_FIELDS[] =
{
  {"BAND_1", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_lo_injection.band_1, sizeof(Si2190_TUNER_LO_INJECTION_PROP_BAND_1)/sizeof(Si2190_optionStruct), Si2190_TUNER_LO_INJECTION_PROP_BAND_1},
  {"BAND_2", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_lo_injection.band_2, sizeof(Si2190_TUNER_LO_INJECTION_PROP_BAND_2)/sizeof(Si2190_optionStruct), Si2190_TUNER_LO_INJECTION_PROP_BAND_2},
  {"BAND_3", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_lo_injection.band_3, sizeof(Si2190_TUNER_LO_INJECTION_PROP_BAND_3)/sizeof(Si2190_optionStruct), Si2190_TUNER_LO_INJECTION_PROP_BAND_3},
};

Si2190_optionStruct    Si2190_TUNER_RETURN_LOSS_PROP_CONFIG[] =
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
Si2190_optionStruct    Si2190_TUNER_RETURN_LOSS_PROP_MODE[] =
{
  {"TERRESTRIAL",     0},
  {"CABLE",           1},
};
Si2190_fieldDicoStruct Si2190_TUNER_RETURN_LOSS_PROP_FIELDS[] =
{
  {"CONFIG", Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_return_loss.config, sizeof(Si2190_TUNER_RETURN_LOSS_PROP_CONFIG)/sizeof(Si2190_optionStruct), Si2190_TUNER_RETURN_LOSS_PROP_CONFIG},
  {"MODE",   Si2190_UNSIGNED_CHAR, &Si2190_prop.tuner_return_loss.mode  , sizeof(Si2190_TUNER_RETURN_LOSS_PROP_MODE  )/sizeof(Si2190_optionStruct), Si2190_TUNER_RETURN_LOSS_PROP_MODE  },
};

Si2190_propertyInfoStruct Si2190_propertyDictionary[] =
{
  {Si2190_ATV   , "ATV_AFC_RANGE"               , sizeof(Si2190_ATV_AFC_RANGE_PROP_FIELDS               )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_AFC_RANGE_PROP_FIELDS                , Si2190_ATV_AFC_RANGE_PROP                },
  {Si2190_ATV   , "ATV_AGC_SPEED"               , sizeof(Si2190_ATV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_AGC_SPEED_PROP_FIELDS                , Si2190_ATV_AGC_SPEED_PROP                },
  {Si2190_ATV   , "ATV_AGC_SPEED_LOW_RSSI"      , sizeof(Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS      )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS       , Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP       },
  {Si2190_ATV   , "ATV_ARTIFICIAL_SNOW"         , sizeof(Si2190_ATV_ARTIFICIAL_SNOW_PROP_FIELDS         )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_ARTIFICIAL_SNOW_PROP_FIELDS          , Si2190_ATV_ARTIFICIAL_SNOW_PROP          },
  {Si2190_ATV   , "ATV_AUDIO_MODE"              , sizeof(Si2190_ATV_AUDIO_MODE_PROP_FIELDS              )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_AUDIO_MODE_PROP_FIELDS               , Si2190_ATV_AUDIO_MODE_PROP               },
  {Si2190_ATV   , "ATV_CONFIG_IF_PORT"          , sizeof(Si2190_ATV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_CONFIG_IF_PORT_PROP_FIELDS           , Si2190_ATV_CONFIG_IF_PORT_PROP           },
  {Si2190_ATV   , "ATV_CVBS_OUT"                , sizeof(Si2190_ATV_CVBS_OUT_PROP_FIELDS                )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_CVBS_OUT_PROP_FIELDS                 , Si2190_ATV_CVBS_OUT_PROP                 },
  {Si2190_ATV   , "ATV_CVBS_OUT_FINE"           , sizeof(Si2190_ATV_CVBS_OUT_FINE_PROP_FIELDS           )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_CVBS_OUT_FINE_PROP_FIELDS            , Si2190_ATV_CVBS_OUT_FINE_PROP            },
  {Si2190_ATV   , "ATV_IEN"                     , sizeof(Si2190_ATV_IEN_PROP_FIELDS                     )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_IEN_PROP_FIELDS                      , Si2190_ATV_IEN_PROP                      },
  {Si2190_ATV   , "ATV_INT_SENSE"               , sizeof(Si2190_ATV_INT_SENSE_PROP_FIELDS               )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_INT_SENSE_PROP_FIELDS                , Si2190_ATV_INT_SENSE_PROP                },
  {Si2190_ATV   , "ATV_PGA_TARGET"              , sizeof(Si2190_ATV_PGA_TARGET_PROP_FIELDS              )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_PGA_TARGET_PROP_FIELDS               , Si2190_ATV_PGA_TARGET_PROP               },
  {Si2190_ATV   , "ATV_RF_TOP"                  , sizeof(Si2190_ATV_RF_TOP_PROP_FIELDS                  )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_RF_TOP_PROP_FIELDS                   , Si2190_ATV_RF_TOP_PROP                   },
  {Si2190_ATV   , "ATV_RSQ_RSSI_THRESHOLD"      , sizeof(Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si2190_ATV   , "ATV_RSQ_SNR_THRESHOLD"       , sizeof(Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS       )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS        , Si2190_ATV_RSQ_SNR_THRESHOLD_PROP        },
  {Si2190_ATV   , "ATV_SIF_OUT"                 , sizeof(Si2190_ATV_SIF_OUT_PROP_FIELDS                 )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_SIF_OUT_PROP_FIELDS                  , Si2190_ATV_SIF_OUT_PROP                  },
  {Si2190_ATV   , "ATV_SOUND_AGC_LIMIT"         , sizeof(Si2190_ATV_SOUND_AGC_LIMIT_PROP_FIELDS         )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_SOUND_AGC_LIMIT_PROP_FIELDS          , Si2190_ATV_SOUND_AGC_LIMIT_PROP          },
  {Si2190_ATV   , "ATV_SOUND_AGC_SPEED"         , sizeof(Si2190_ATV_SOUND_AGC_SPEED_PROP_FIELDS         )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_SOUND_AGC_SPEED_PROP_FIELDS          , Si2190_ATV_SOUND_AGC_SPEED_PROP          },
  {Si2190_ATV   , "ATV_VIDEO_EQUALIZER"         , sizeof(Si2190_ATV_VIDEO_EQUALIZER_PROP_FIELDS         )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_VIDEO_EQUALIZER_PROP_FIELDS          , Si2190_ATV_VIDEO_EQUALIZER_PROP          },
  {Si2190_ATV   , "ATV_VIDEO_MODE"              , sizeof(Si2190_ATV_VIDEO_MODE_PROP_FIELDS              )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_VIDEO_MODE_PROP_FIELDS               , Si2190_ATV_VIDEO_MODE_PROP               },
  {Si2190_ATV   , "ATV_VSNR_CAP"                , sizeof(Si2190_ATV_VSNR_CAP_PROP_FIELDS                )/sizeof(Si2190_fieldDicoStruct), Si2190_ATV_VSNR_CAP_PROP_FIELDS                 , Si2190_ATV_VSNR_CAP_PROP                 },
  {Si2190_COMMON, "CRYSTAL_TRIM"                , sizeof(Si2190_CRYSTAL_TRIM_PROP_FIELDS                )/sizeof(Si2190_fieldDicoStruct), Si2190_CRYSTAL_TRIM_PROP_FIELDS                 , Si2190_CRYSTAL_TRIM_PROP                 },
  {Si2190_COMMON, "MASTER_IEN"                  , sizeof(Si2190_MASTER_IEN_PROP_FIELDS                  )/sizeof(Si2190_fieldDicoStruct), Si2190_MASTER_IEN_PROP_FIELDS                   , Si2190_MASTER_IEN_PROP                   },
  {Si2190_DTV   , "DTV_AGC_FREEZE_INPUT"        , sizeof(Si2190_DTV_AGC_FREEZE_INPUT_PROP_FIELDS        )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_AGC_FREEZE_INPUT_PROP_FIELDS         , Si2190_DTV_AGC_FREEZE_INPUT_PROP         },
  {Si2190_DTV   , "DTV_AGC_SPEED"               , sizeof(Si2190_DTV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_AGC_SPEED_PROP_FIELDS                , Si2190_DTV_AGC_SPEED_PROP                },
  {Si2190_DTV   , "DTV_CONFIG_IF_PORT"          , sizeof(Si2190_DTV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_CONFIG_IF_PORT_PROP_FIELDS           , Si2190_DTV_CONFIG_IF_PORT_PROP           },
  {Si2190_DTV   , "DTV_EXT_AGC"                 , sizeof(Si2190_DTV_EXT_AGC_PROP_FIELDS                 )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_EXT_AGC_PROP_FIELDS                  , Si2190_DTV_EXT_AGC_PROP                  },
  {Si2190_DTV   , "DTV_FILTER_SELECT"           , sizeof(Si2190_DTV_FILTER_SELECT_PROP_FIELDS           )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_FILTER_SELECT_PROP_FIELDS            , Si2190_DTV_FILTER_SELECT_PROP            },
  {Si2190_DTV   , "DTV_IEN"                     , sizeof(Si2190_DTV_IEN_PROP_FIELDS                     )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_IEN_PROP_FIELDS                      , Si2190_DTV_IEN_PROP                      },
  {Si2190_DTV   , "DTV_INITIAL_AGC_SPEED"       , sizeof(Si2190_DTV_INITIAL_AGC_SPEED_PROP_FIELDS       )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_INITIAL_AGC_SPEED_PROP_FIELDS        , Si2190_DTV_INITIAL_AGC_SPEED_PROP        },
  {Si2190_DTV   , "DTV_INITIAL_AGC_SPEED_PERIOD", sizeof(Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS)/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS , Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP },
  {Si2190_DTV   , "DTV_INTERNAL_ZIF"            , sizeof(Si2190_DTV_INTERNAL_ZIF_PROP_FIELDS            )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_INTERNAL_ZIF_PROP_FIELDS             , Si2190_DTV_INTERNAL_ZIF_PROP             },
  {Si2190_DTV   , "DTV_INT_SENSE"               , sizeof(Si2190_DTV_INT_SENSE_PROP_FIELDS               )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_INT_SENSE_PROP_FIELDS                , Si2190_DTV_INT_SENSE_PROP                },
  {Si2190_DTV   , "DTV_LIF_FREQ"                , sizeof(Si2190_DTV_LIF_FREQ_PROP_FIELDS                )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_LIF_FREQ_PROP_FIELDS                 , Si2190_DTV_LIF_FREQ_PROP                 },
  {Si2190_DTV   , "DTV_LIF_OUT"                 , sizeof(Si2190_DTV_LIF_OUT_PROP_FIELDS                 )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_LIF_OUT_PROP_FIELDS                  , Si2190_DTV_LIF_OUT_PROP                  },
  {Si2190_DTV   , "DTV_MODE"                    , sizeof(Si2190_DTV_MODE_PROP_FIELDS                    )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_MODE_PROP_FIELDS                     , Si2190_DTV_MODE_PROP                     },
  {Si2190_DTV   , "DTV_PGA_LIMITS"              , sizeof(Si2190_DTV_PGA_LIMITS_PROP_FIELDS              )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_PGA_LIMITS_PROP_FIELDS               , Si2190_DTV_PGA_LIMITS_PROP               },
  {Si2190_DTV   , "DTV_PGA_TARGET"              , sizeof(Si2190_DTV_PGA_TARGET_PROP_FIELDS              )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_PGA_TARGET_PROP_FIELDS               , Si2190_DTV_PGA_TARGET_PROP               },
  {Si2190_DTV   , "DTV_RF_TOP"                  , sizeof(Si2190_DTV_RF_TOP_PROP_FIELDS                  )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_RF_TOP_PROP_FIELDS                   , Si2190_DTV_RF_TOP_PROP                   },
  {Si2190_DTV   , "DTV_RSQ_RSSI_THRESHOLD"      , sizeof(Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si2190_DTV   , "DTV_ZIF_DC_CANCELLER_BW"     , sizeof(Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS     )/sizeof(Si2190_fieldDicoStruct), Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS      , Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP      },
  {Si2190_TUNER , "DEBUG_SAMPLE_FREQ"           , sizeof(Si2190_DEBUG_SAMPLE_FREQ_PROP_FIELDS           )/sizeof(Si2190_fieldDicoStruct), Si2190_DEBUG_SAMPLE_FREQ_PROP_FIELDS            , Si2190_DEBUG_SAMPLE_FREQ_PROP            },
  {Si2190_TUNER , "TUNER_BLOCKED_VCO"           , sizeof(Si2190_TUNER_BLOCKED_VCO_PROP_FIELDS           )/sizeof(Si2190_fieldDicoStruct), Si2190_TUNER_BLOCKED_VCO_PROP_FIELDS            , Si2190_TUNER_BLOCKED_VCO_PROP            },
  {Si2190_TUNER , "TUNER_IEN"                   , sizeof(Si2190_TUNER_IEN_PROP_FIELDS                   )/sizeof(Si2190_fieldDicoStruct), Si2190_TUNER_IEN_PROP_FIELDS                    , Si2190_TUNER_IEN_PROP                    },
  {Si2190_TUNER , "TUNER_INT_SENSE"             , sizeof(Si2190_TUNER_INT_SENSE_PROP_FIELDS             )/sizeof(Si2190_fieldDicoStruct), Si2190_TUNER_INT_SENSE_PROP_FIELDS              , Si2190_TUNER_INT_SENSE_PROP              },
  {Si2190_TUNER , "TUNER_LO_INJECTION"          , sizeof(Si2190_TUNER_LO_INJECTION_PROP_FIELDS          )/sizeof(Si2190_fieldDicoStruct), Si2190_TUNER_LO_INJECTION_PROP_FIELDS           , Si2190_TUNER_LO_INJECTION_PROP           },
  {Si2190_TUNER , "TUNER_RETURN_LOSS"           , sizeof(Si2190_TUNER_RETURN_LOSS_PROP_FIELDS           )/sizeof(Si2190_fieldDicoStruct), Si2190_TUNER_RETURN_LOSS_PROP_FIELDS            , Si2190_TUNER_RETURN_LOSS_PROP            },
};
/* _properties_strings_insertion_point */

int   Si2190_PropertyNames        (L1_Si2190_Context *api, char *msg)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si2190_propertyDictionary)/sizeof(Si2190_propertyInfoStruct);
  msg[0]='\0';
  for (propIndex=0; propIndex<size; propIndex++)
  {
    strcat(msg,Si2190_propertyDictionary[propIndex].name);
    if (propIndex< (size-1)) strcat(msg," ");
  }
  return propIndex;
}

int   Si2190_PropertyIndex        (L1_Si2190_Context *api, const char *property)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si2190_propertyDictionary)/sizeof(Si2190_propertyInfoStruct);
  for (propIndex=0; propIndex <size; propIndex++)
  {
    if (strcmp_nocase(property, Si2190_propertyDictionary[propIndex].name)==0)
    {
      return propIndex;
    }
  }
  return -1;
}

int   Si2190_PropertyFields       (L1_Si2190_Context *api, int propIndex, char *msg)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (fieldIndex=0; fieldIndex < Si2190_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    strcat(msg, Si2190_propertyDictionary[propIndex].field[fieldIndex].name);
    if (fieldIndex< (Si2190_propertyDictionary[propIndex].nbFields-1)) strcat(msg," ");
  }
  return -1;
}

int   Si2190_PropertyFieldIndex   (L1_Si2190_Context *api, int propIndex, char *field)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  for (fieldIndex=0; fieldIndex < Si2190_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    if (strcmp_nocase(field, Si2190_propertyDictionary[propIndex].field[fieldIndex].name)==0)
    {
      return fieldIndex;
    }
  }
  return -1;
}

int   Si2190_PropertyFieldEnums   (L1_Si2190_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int enumIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (enumIndex=0; enumIndex < Si2190_propertyDictionary[propIndex].field[fieldIndex].nbOptions; enumIndex++)
  {
    strcat(msg, Si2190_propertyDictionary[propIndex].field[fieldIndex].option[enumIndex].name);
    if (enumIndex < (Si2190_propertyDictionary[propIndex].field[fieldIndex].nbOptions-1)) strcat(msg," ");
  }
  return enumIndex;
}

int   Si2190_PropertyFieldRanges  (L1_Si2190_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int index;
  char buf[10];
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (index=0; index < 2; index++)
  {
    itoa(Si2190_propertyDictionary[propIndex].field[fieldIndex].option[index].value,buf,10);
    strcat(msg, buf);
    if (index < 1) strcat(msg," - ");
  }
  return index;
}

int   Si2190_GetValueFromEntry    (L1_Si2190_Context *api, Si2190_fieldDicoStruct field, char *entry, int *value)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */

  if (!strcmp_nocase(field.option[0].name,"MIN_RANGE"))
  {
    if (field.datatype== Si2190_UNSIGNED_INT || field.datatype== Si2190_UNSIGNED_CHAR)
    {
      *value = (unsigned int)atoi(entry);
      return 1;
    }
    else if (field.datatype == Si2190_SIGNED_INT || field.datatype == Si2190_SIGNED_CHAR)
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
}

char *Si2190_GetEnumFromValue     (L1_Si2190_Context *api, Si2190_fieldDicoStruct field, int iValue)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */
  if (field.nbOptions ==0 )
    {
    sprintf(optionText, "%d", iValue);
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
}

int   Si2190_GetValueFromField    (L1_Si2190_Context *api, Si2190_fieldDicoStruct field)
{
  short intValue;
  short *fieldAsInt;
  short iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si2190_SIGNED_INT   )
  {
      fieldAsInt= (short *) ((field.pField-(void *) &Si2190_prop)+ (void *)api->prop);
  }
  else if (field.datatype == Si2190_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si2190_prop)+ (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si2190_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si2190_prop)+ (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si2190_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned short *) ((field.pField-(void *) &Si2190_prop)+ (void *)api->prop);
  }

  return  *fieldAsInt;
}

char *Si2190_GetEnumFromField     (L1_Si2190_Context *api, Si2190_fieldDicoStruct field)
{
  int intValue;
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si2190_SIGNED_INT   )
  {
      fieldAsInt= (int *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop);
  }
  else if (field.datatype == Si2190_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si2190_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si2190_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned int *)((field.pField-(void *) &Si2190_prop) + (void *)api->prop);
  }

  return Si2190_GetEnumFromValue(api, field, *fieldAsInt);
}

int   Si2190_SetFieldFromEntry    (L1_Si2190_Context *api, Si2190_fieldDicoStruct field, char *entry)
{
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &iTmp;
  if (Si2190_GetValueFromEntry(api, field, entry, fieldAsInt) == 0) return 0;
  if (field.datatype == Si2190_SIGNED_INT )
  {
    *( (int *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si2190_UNSIGNED_CHAR)
  {
    *( (unsigned char *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si2190_SIGNED_CHAR)
  {
    *( (char *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop))=iTmp;
  }
  else /* if (field.datatype == Si2190_UNSIGNED_INT) */
  {
    *( (unsigned int *) ((field.pField-(void *) &Si2190_prop) + (void *)api->prop))=iTmp;
  }

  return 1;
}

void  Si2190_showProperty         (L1_Si2190_Context *api, int propIndex)
{
  int fieldIndex;
  for (fieldIndex=0; fieldIndex<Si2190_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    printf("%s:%s:%s = ", Si2190_featureText[Si2190_propertyDictionary[propIndex].feature], Si2190_propertyDictionary[propIndex].name, Si2190_propertyDictionary[propIndex].field[fieldIndex].name);
    printf("<%s>\n", Si2190_GetEnumFromField(api, Si2190_propertyDictionary[propIndex].field[fieldIndex]));
  }

}

void  Si2190_showPropertyNamed    (L1_Si2190_Context *api, char *property)
{
  int propIndex;

  if ((propIndex = Si2190_PropertyIndex(api, property)) >= 0)
  {
    Si2190_showProperty(api, propIndex);
  }
  else
  {
    printf("Unknown property '%s'\n", property);
  }

}

int   Si2190_showProperties       (L1_Si2190_Context *api, Si2190_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si2190_propertyDictionary)/sizeof(Si2190_propertyInfoStruct);

  printf("\n%s current properties:\n\n", Si2190_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si2190_propertyDictionary[propertyIndex].feature != feature) continue;
    Si2190_showProperty(api, propertyIndex);
  }
  return 0;
}

void  Si2190_setupProperty        (L1_Si2190_Context *api, int propIndex)
{
  #define LMAX 20
  char entry[LMAX];
  char setup_msg[1000];
  int fieldIndex;
  char isRangeType = 1;

  for (fieldIndex=0; fieldIndex<Si2190_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    isRangeType = (strcmp_nocase(Si2190_propertyDictionary[propIndex].field[fieldIndex].option->name,"MIN_RANGE") == 0);

    printf("%s:%s:%s = ", Si2190_featureText[Si2190_propertyDictionary[propIndex].feature], Si2190_propertyDictionary[propIndex].name, Si2190_propertyDictionary[propIndex].field[fieldIndex].name);

    if ( isRangeType )
    {
      printf("<%d>\n", Si2190_GetValueFromField(api, Si2190_propertyDictionary[propIndex].field[fieldIndex]));
      Si2190_PropertyFieldRanges(api, propIndex, fieldIndex, setup_msg);
      printf("Range: <%s>  ",setup_msg);
    }
    else
    {
      Si2190_PropertyFieldEnums(api, propIndex, fieldIndex, setup_msg);
      printf("<%s>\n Options: <%s>\n", Si2190_GetEnumFromField(api, Si2190_propertyDictionary[propIndex].field[fieldIndex]), setup_msg);
    }

    fgets(entry,LMAX,stdin);

    if (strlen(entry) > 1)
    {
      entry[strlen(entry)-1]='\0';
      if (!Si2190_SetFieldFromEntry(api, Si2190_propertyDictionary[propIndex].field[fieldIndex], entry))
      {
        printf("Invalid entry!\n");
      }
    }

    if (isRangeType)
      printf("<%d>\n\n", Si2190_GetValueFromField(api, Si2190_propertyDictionary[propIndex].field[fieldIndex]));
    else
      printf("<%s>\n\n", Si2190_GetEnumFromField(api, Si2190_propertyDictionary[propIndex].field[fieldIndex]));
  }
}

int   Si2190_setupProperties      (L1_Si2190_Context *api, Si2190_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si2190_propertyDictionary)/sizeof(Si2190_propertyInfoStruct);

  printf("\n%s properties:\n\n", Si2190_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si2190_propertyDictionary[propertyIndex].feature != feature) continue;
    Si2190_setupProperty(api, propertyIndex);
  }
  return 0;
}

#endif /* Si2190_COMMAND_LINE_APPLICATION */

/* _property_string_functions_insertion_start */
#ifdef    Si2190_COMMAND_LINE_APPLICATION
int Si2190_showATVProperties       (L1_Si2190_Context *api)
{
  return Si2190_showProperties(api, Si2190_ATV);
}

int Si2190_showCOMMONProperties    (L1_Si2190_Context *api)
{
  return Si2190_showProperties(api, Si2190_COMMON);
}

int Si2190_showDTVProperties       (L1_Si2190_Context *api)
{
  return Si2190_showProperties(api, Si2190_DTV);
}

int Si2190_showTUNERProperties     (L1_Si2190_Context *api)
{
  return Si2190_showProperties(api, Si2190_TUNER);
}

int Si2190_showAllProperties       (L1_Si2190_Context *api)
{
  Si2190_showATVProperties       (api);
  Si2190_showCOMMONProperties    (api);
  Si2190_showDTVProperties       (api);
  Si2190_showTUNERProperties     (api);
  return 0;
}

#endif /* Si2190_COMMAND_LINE_APPLICATION */
void Si2190_setupATVDefaults        (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupATVDefaults       \n");
  api->prop->atv_afc_range.range_khz              =  1000; /* (default  1000) */

  api->prop->atv_agc_speed.if_agc_speed           = Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */

  api->prop->atv_agc_speed_low_rssi.if_agc_speed  = Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  api->prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */

  api->prop->atv_artificial_snow.gain             = Si2190_ATV_ARTIFICIAL_SNOW_PROP_GAIN_AUTO   ; /* (default 'AUTO') */
  api->prop->atv_artificial_snow.offset           =     0; /* (default     0) */

  api->prop->atv_audio_mode.audio_sys             = Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT    ; /* (default 'DEFAULT') */
  api->prop->atv_audio_mode.chan_filt_bw          = Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW_DEFAULT ; /* (default 'DEFAULT') */

  api->prop->atv_config_if_port.atv_out_type      = Si2190_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_CVBS_IF2B_SOUND_IF2A ; /* (default 'CVBS_IF2B_SOUND_IF2A') */

  api->prop->atv_cvbs_out.offset                  =    25; /* (default    25) */
  api->prop->atv_cvbs_out.amp                     =   94;//tqy 200; /* (default   200) */

  api->prop->atv_cvbs_out_fine.offset             =     0; /* (default     0) */
  api->prop->atv_cvbs_out_fine.amp                =   100; /* (default   100) */

  api->prop->atv_ien.chlien                       = Si2190_ATV_IEN_PROP_CHLIEN_ENABLE   ; /* (default 'ENABLE') */
  api->prop->atv_ien.pclien                       = Si2190_ATV_IEN_PROP_PCLIEN_DISABLE  ; /* (default 'DISABLE') */
  api->prop->atv_ien.dlien                        = Si2190_ATV_IEN_PROP_DLIEN_DISABLE   ; /* (default 'DISABLE') */
  api->prop->atv_ien.snrlien                      = Si2190_ATV_IEN_PROP_SNRLIEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_ien.snrhien                      = Si2190_ATV_IEN_PROP_SNRHIEN_DISABLE ; /* (default 'DISABLE') */

  api->prop->atv_int_sense.chlnegen               = Si2190_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.pclnegen               = Si2190_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.dlnegen                = Si2190_ATV_INT_SENSE_PROP_DLNEGEN_DISABLE   ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.snrlnegen              = Si2190_ATV_INT_SENSE_PROP_SNRLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.snrhnegen              = Si2190_ATV_INT_SENSE_PROP_SNRHNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.chlposen               = Si2190_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  api->prop->atv_int_sense.pclposen               = Si2190_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  api->prop->atv_int_sense.dlposen                = Si2190_ATV_INT_SENSE_PROP_DLPOSEN_ENABLE    ; /* (default 'ENABLE') */
  api->prop->atv_int_sense.snrlposen              = Si2190_ATV_INT_SENSE_PROP_SNRLPOSEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->atv_int_sense.snrhposen              = Si2190_ATV_INT_SENSE_PROP_SNRHPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->atv_pga_target.pga_target            =     0; /* (default     0) */
  api->prop->atv_pga_target.override_enable       = Si2190_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */

  api->prop->atv_rf_top.atv_rf_top                = Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO ; /* (default 'AUTO') */

  api->prop->atv_rsq_rssi_threshold.lo            =   -70; /* (default   -70) */
  api->prop->atv_rsq_rssi_threshold.hi            =     0; /* (default     0) */

  api->prop->atv_rsq_snr_threshold.lo             =    25; /* (default    25) */
  api->prop->atv_rsq_snr_threshold.hi             =    45; /* (default    45) */

  api->prop->atv_sif_out.offset                   =   135; /* (default   135) */
  api->prop->atv_sif_out.amp                      =    29; /* (default    60) */

  api->prop->atv_sound_agc_limit.max_gain         =    84; /* (default    84) */
  api->prop->atv_sound_agc_limit.min_gain         =   -84; /* (default   -84) */

  api->prop->atv_sound_agc_speed.system_l         =     5; /* (default     5) */
  api->prop->atv_sound_agc_speed.other_systems    =     4; /* (default     4) */

  api->prop->atv_video_equalizer.slope            =     0; /* (default     0) */

  api->prop->atv_video_mode.video_sys             = Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B            ; /* (default 'B') */
  api->prop->atv_video_mode.color                 = Si2190_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC         ; /* (default 'PAL_NTSC') */
  api->prop->atv_video_mode.invert_signal         =     0; /* (default     0) */

  api->prop->atv_vsnr_cap.atv_vsnr_cap            =     0; /* (default     0) */

}

void Si2190_setupCOMMONDefaults     (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupCOMMONDefaults    \n");
  api->prop->crystal_trim.xo_cap                  =     8; /* (default     8) */

  api->prop->master_ien.tunien                    = Si2190_MASTER_IEN_PROP_TUNIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.atvien                    = Si2190_MASTER_IEN_PROP_ATVIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.dtvien                    = Si2190_MASTER_IEN_PROP_DTVIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.errien                    = Si2190_MASTER_IEN_PROP_ERRIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.ctsien                    = Si2190_MASTER_IEN_PROP_CTSIEN_OFF ; /* (default 'OFF') */

}

void Si2190_setupDTVDefaults        (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupDTVDefaults       \n");
  api->prop->dtv_agc_freeze_input.level           = Si2190_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW  ; /* (default 'LOW') */
  api->prop->dtv_agc_freeze_input.pin             = Si2190_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   ; /* (default 'NONE') */

  api->prop->dtv_agc_speed.if_agc_speed           = Si2190_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  api->prop->dtv_agc_speed.agc_decim              = Si2190_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */

  api->prop->dtv_config_if_port.dtv_out_type      = Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1   ; /* (default 'LIF_IF1') */
  api->prop->dtv_config_if_port.dtv_agc_source    =     0; /* (default     0) */

  api->prop->dtv_ext_agc.min_10mv                 =    50; /* (default    50) */
  api->prop->dtv_ext_agc.max_10mv                 =   200; /* (default   200) */

  api->prop->dtv_filter_select.filter             = Si2190_DTV_FILTER_SELECT_PROP_FILTER_CUSTOM1 ; /* (default 'CUSTOM1') */

  api->prop->dtv_ien.chlien                       = Si2190_DTV_IEN_PROP_CHLIEN_ENABLE ; /* (default 'ENABLE') */

  api->prop->dtv_initial_agc_speed.if_agc_speed   = Si2190_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  api->prop->dtv_initial_agc_speed.agc_decim      = Si2190_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */

  api->prop->dtv_initial_agc_speed_period.period  =     0; /* (default     0) */

  api->prop->dtv_internal_zif.atsc                = Si2190_DTV_INTERNAL_ZIF_PROP_ATSC_LIF   ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.qam_us              = Si2190_DTV_INTERNAL_ZIF_PROP_QAM_US_LIF ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.dvbt                = Si2190_DTV_INTERNAL_ZIF_PROP_DVBT_LIF   ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.dvbc                = Si2190_DTV_INTERNAL_ZIF_PROP_DVBC_LIF   ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.isdbt               = Si2190_DTV_INTERNAL_ZIF_PROP_ISDBT_LIF  ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.isdbc               = Si2190_DTV_INTERNAL_ZIF_PROP_ISDBC_LIF  ; /* (default 'LIF') */
  api->prop->dtv_internal_zif.dtmb                = Si2190_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */

  api->prop->dtv_int_sense.chlnegen               = Si2190_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->dtv_int_sense.chlposen               = Si2190_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->dtv_lif_freq.offset                  = (unsigned int)C_Si2190_IF_FREQUENCY;//5000; /* (default  5000) */

  api->prop->dtv_lif_out.offset                   =   148; /* (default   148) */
  api->prop->dtv_lif_out.amp                      =    27; /* (default    27) */

  api->prop->dtv_mode.bw                          = Si2190_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  api->prop->dtv_mode.modulation                  = Si2190_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  api->prop->dtv_mode.invert_spectrum             =     0; /* (default     0) */

  api->prop->dtv_pga_limits.min                   =    -1; /* (default    -1) */
  api->prop->dtv_pga_limits.max                   =    -1; /* (default    -1) */

  api->prop->dtv_pga_target.pga_target            =     0; /* (default     0) */
  api->prop->dtv_pga_target.override_enable       = Si2190_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */

  api->prop->dtv_rf_top.dtv_rf_top                = Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */

  api->prop->dtv_rsq_rssi_threshold.lo            =   -80; /* (default   -80) */
  api->prop->dtv_rsq_rssi_threshold.hi            =     0; /* (default     0) */

  api->prop->dtv_zif_dc_canceller_bw.bandwidth    = Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_DEFAULT ; /* (default 'DEFAULT') */

}

void Si2190_setupTUNERDefaults      (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupTUNERDefaults     \n");
  api->prop->debug_sample_freq.fs_mhz             =     0; /* (default     0) */

  api->prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */

  api->prop->tuner_ien.tcien                      = Si2190_TUNER_IEN_PROP_TCIEN_ENABLE     ; /* (default 'ENABLE') */
  api->prop->tuner_ien.rssilien                   = Si2190_TUNER_IEN_PROP_RSSILIEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_ien.rssihien                   = Si2190_TUNER_IEN_PROP_RSSIHIEN_DISABLE ; /* (default 'DISABLE') */

  api->prop->tuner_int_sense.tcnegen              = Si2190_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE    ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.rssilnegen           = Si2190_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.rssihnegen           = Si2190_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->tuner_int_sense.tcposen              = Si2190_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE     ; /* (default 'ENABLE') */
  api->prop->tuner_int_sense.rssilposen           = Si2190_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->tuner_int_sense.rssihposen           = Si2190_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->tuner_lo_injection.band_1            = Si2190_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  api->prop->tuner_lo_injection.band_2            = Si2190_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  api->prop->tuner_lo_injection.band_3            = Si2190_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */

  api->prop->tuner_return_loss.config             = Si2190_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  api->prop->tuner_return_loss.mode               = Si2190_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */

}

void Si2190_setupAllDefaults       (L1_Si2190_Context *api)
{
  Si2190_setupATVDefaults       (api);
  Si2190_setupCOMMONDefaults    (api);
  Si2190_setupDTVDefaults       (api);
  Si2190_setupTUNERDefaults     (api);
}

int Si2190_setupATVProperties       (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupATVProperties       \n");
#ifdef    Si2190_COMMAND_LINE_APPLICATION
  Si2190_setupProperties(api, Si2190_ATV);
#else  /* Si2190_COMMAND_LINE_APPLICATION */
  Si2190_setupATVDefaults(api);
#endif /* Si2190_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2190_setupCOMMONProperties    (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupCOMMONProperties    \n");
#ifdef    Si2190_COMMAND_LINE_APPLICATION
  Si2190_setupProperties(api, Si2190_COMMON);
#else  /* Si2190_COMMAND_LINE_APPLICATION */
  Si2190_setupCOMMONDefaults(api);
#endif /* Si2190_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2190_setupDTVProperties       (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupDTVProperties       \n");
#ifdef    Si2190_COMMAND_LINE_APPLICATION
  Si2190_setupProperties(api, Si2190_DTV);
#else  /* Si2190_COMMAND_LINE_APPLICATION */
  Si2190_setupDTVDefaults(api);
#endif /* Si2190_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2190_setupTUNERProperties     (L1_Si2190_Context *api)
{
  SiTRACE("Si2190_setupTUNERProperties     \n");
#ifdef    Si2190_COMMAND_LINE_APPLICATION
  Si2190_setupProperties(api, Si2190_TUNER);
#else  /* Si2190_COMMAND_LINE_APPLICATION */
  Si2190_setupTUNERDefaults(api);
#endif /* Si2190_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2190_setupAllProperties  (L1_Si2190_Context *api)
{
  Si2190_setupATVProperties       (api);
  Si2190_setupCOMMONProperties    (api);
  Si2190_setupDTVProperties       (api);
  Si2190_setupTUNERProperties     (api);
  return 0;
}


 /*****************************************************************************************
 NAME: Si2190_downloadATVProperties
  DESCRIPTION: Setup Si2190 ATV properties configuration
  This function will download all the ATV configuration properties.
  The function SetupATVDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2190 Context
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
  Programming Guide Reference:    ATV setup flowchart
******************************************************************************************/
int  Si2190_downloadATVProperties(L1_Si2190_Context *api)
{
  SiTRACE("Si2190_downloadATVProperties     \n");
#ifdef    Si2190_ATV_AFC_RANGE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_AFC_RANGE_PROP_CODE               ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_AFC_RANGE_PROP */
#ifdef    Si2190_ATV_AGC_SPEED_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_AGC_SPEED_PROP_CODE               ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_AGC_SPEED_PROP */
#ifdef    Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE      ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP */
#ifdef    Si2190_ATV_ARTIFICIAL_SNOW_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_ARTIFICIAL_SNOW_PROP_CODE         ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_ARTIFICIAL_SNOW_PROP */
#ifdef    Si2190_ATV_AUDIO_MODE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_AUDIO_MODE_PROP_CODE              ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_AUDIO_MODE_PROP */
#ifdef    Si2190_ATV_CONFIG_IF_PORT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_CONFIG_IF_PORT_PROP */
#ifdef    Si2190_ATV_CVBS_OUT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_CVBS_OUT_PROP_CODE                ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_CVBS_OUT_PROP */
#ifdef    Si2190_ATV_CVBS_OUT_FINE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_CVBS_OUT_FINE_PROP_CODE           ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_CVBS_OUT_FINE_PROP */
#ifdef    Si2190_ATV_IEN_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_IEN_PROP_CODE                     ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_IEN_PROP */
#ifdef    Si2190_ATV_INT_SENSE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_INT_SENSE_PROP_CODE               ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_INT_SENSE_PROP */
#ifdef    Si2190_ATV_PGA_TARGET_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_PGA_TARGET_PROP_CODE              ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_PGA_TARGET_PROP */
#ifdef    Si2190_ATV_RF_TOP_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_RF_TOP_PROP_CODE                  ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_RF_TOP_PROP */
#ifdef    Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si2190_ATV_RSQ_SNR_THRESHOLD_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_CODE       ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_RSQ_SNR_THRESHOLD_PROP */
#ifdef    Si2190_ATV_SIF_OUT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_SIF_OUT_PROP_CODE                 ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_SIF_OUT_PROP */
#ifdef    Si2190_ATV_SOUND_AGC_LIMIT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_SOUND_AGC_LIMIT_PROP_CODE         ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_SOUND_AGC_LIMIT_PROP */
#ifdef    Si2190_ATV_SOUND_AGC_SPEED_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_SOUND_AGC_SPEED_PROP_CODE         ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_SOUND_AGC_SPEED_PROP */
#ifdef    Si2190_ATV_VIDEO_EQUALIZER_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_VIDEO_EQUALIZER_PROP_CODE         ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_VIDEO_EQUALIZER_PROP */
#ifdef    Si2190_ATV_VIDEO_MODE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_VIDEO_MODE_PROP_CODE              ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_VIDEO_MODE_PROP */
#ifdef    Si2190_ATV_VSNR_CAP_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_ATV_VSNR_CAP_PROP_CODE                ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_ATV_VSNR_CAP_PROP */
return NO_Si2190_ERROR;
}

 /*****************************************************************************************
 NAME: Si2190_downloadCOMMONProperties
  DESCRIPTION: Setup Si2190 COMMON properties configuration
  This function will download all the COMMON configuration properties.
  The function SetupCOMMONDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2190 Context
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
  Programming Guide Reference:    COMMON setup flowchart
******************************************************************************************/
int  Si2190_downloadCOMMONProperties(L1_Si2190_Context *api)
{
  SiTRACE("Si2190_downloadCOMMONProperties                \n");
#ifdef    Si2190_CRYSTAL_TRIM_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_CRYSTAL_TRIM_PROP_CODE                ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_CRYSTAL_TRIM_PROP */
#ifdef    Si2190_MASTER_IEN_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_MASTER_IEN_PROP_CODE                  ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_MASTER_IEN_PROP */
return NO_Si2190_ERROR;
}

 /*****************************************************************************************
 NAME: Si2190_downloadDTVProperties
  DESCRIPTION: Setup Si2190 DTV properties configuration
  This function will download all the DTV configuration properties.
  The function SetupDTVDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2190 Context
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
  Programming Guide Reference:    DTV setup flowchart
******************************************************************************************/
int  Si2190_downloadDTVProperties(L1_Si2190_Context *api)
{
  SiTRACE("Si2190_downloadDTVProperties                  \n");
#ifdef    Si2190_DTV_AGC_FREEZE_INPUT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_AGC_FREEZE_INPUT_PROP_CODE        ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_AGC_FREEZE_INPUT_PROP */
#ifdef    Si2190_DTV_AGC_SPEED_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_AGC_SPEED_PROP_CODE               ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_AGC_SPEED_PROP */
#ifdef    Si2190_DTV_CONFIG_IF_PORT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_CONFIG_IF_PORT_PROP */
#ifdef    Si2190_DTV_EXT_AGC_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_EXT_AGC_PROP_CODE                 ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_EXT_AGC_PROP */
#ifdef    Si2190_DTV_FILTER_SELECT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_FILTER_SELECT_PROP_CODE           ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_FILTER_SELECT_PROP */
#ifdef    Si2190_DTV_IEN_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_IEN_PROP_CODE                     ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_IEN_PROP */
#ifdef    Si2190_DTV_INITIAL_AGC_SPEED_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_INITIAL_AGC_SPEED_PROP_CODE       ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_INITIAL_AGC_SPEED_PROP */
#ifdef    Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
#ifdef    Si2190_DTV_INTERNAL_ZIF_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_INTERNAL_ZIF_PROP_CODE            ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_INTERNAL_ZIF_PROP */
#ifdef    Si2190_DTV_INT_SENSE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_INT_SENSE_PROP_CODE               ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_INT_SENSE_PROP */
#ifdef    Si2190_DTV_LIF_FREQ_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_LIF_FREQ_PROP_CODE                ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_LIF_FREQ_PROP */
#ifdef    Si2190_DTV_LIF_OUT_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_LIF_OUT_PROP_CODE                 ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_LIF_OUT_PROP */
#ifdef    Si2190_DTV_MODE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_MODE_PROP_CODE                    ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_MODE_PROP */
#ifdef    Si2190_DTV_PGA_LIMITS_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_PGA_LIMITS_PROP_CODE              ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_PGA_LIMITS_PROP */
#ifdef    Si2190_DTV_PGA_TARGET_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_PGA_TARGET_PROP_CODE              ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_PGA_TARGET_PROP */
#ifdef    Si2190_DTV_RF_TOP_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_RF_TOP_PROP_CODE                  ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_RF_TOP_PROP */
#ifdef    Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE     ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP */
return NO_Si2190_ERROR;
}

 /*****************************************************************************************
 NAME: Si2190_downloadTUNERProperties
  DESCRIPTION: Setup Si2190 TUNER properties configuration
  This function will download all the TUNER configuration properties.
  The function SetupTUNERDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2190 Context
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
  Programming Guide Reference:    TUNER setup flowchart
******************************************************************************************/
int  Si2190_downloadTUNERProperties(L1_Si2190_Context *api)
{
  SiTRACE("Si2190_downloadTUNERProperties     \n");
#ifdef    Si2190_DEBUG_SAMPLE_FREQ_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_DEBUG_SAMPLE_FREQ_PROP_CODE           ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_DEBUG_SAMPLE_FREQ_PROP */
#ifdef    Si2190_TUNER_BLOCKED_VCO_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_TUNER_BLOCKED_VCO_PROP_CODE           ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_TUNER_BLOCKED_VCO_PROP */
#ifdef    Si2190_TUNER_IEN_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_TUNER_IEN_PROP_CODE                   ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_TUNER_IEN_PROP */
#ifdef    Si2190_TUNER_INT_SENSE_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_TUNER_INT_SENSE_PROP_CODE             ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_TUNER_INT_SENSE_PROP */
#ifdef    Si2190_TUNER_LO_INJECTION_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_TUNER_LO_INJECTION_PROP_CODE          ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_TUNER_LO_INJECTION_PROP */
#ifdef    Si2190_TUNER_RETURN_LOSS_PROP
  if (Si2190_L1_SetProperty2(api, Si2190_TUNER_RETURN_LOSS_PROP_CODE           ) != NO_Si2190_ERROR) {return ERROR_Si2190_SENDING_COMMAND;}
#endif /* Si2190_TUNER_RETURN_LOSS_PROP */
return NO_Si2190_ERROR;
}
int Si2190_downloadAllProperties       (L1_Si2190_Context *api)
{
  Si2190_downloadATVProperties       (api);
  Si2190_downloadCOMMONProperties    (api);
  Si2190_downloadDTVProperties       (api);
  Si2190_downloadTUNERProperties     (api);
  return 0;
}

/* _property_string_functions_insertion_point */





