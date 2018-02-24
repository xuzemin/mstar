/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API properties strings functions definitions
   FILE: Si2158_L1_Properties.c
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_0_build_4
   Revision: 0.1
   Tag:  ROM33_2_0_build_4_LGIT_V0.1
   Date: July 30 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si2158_COMMAND_PROTOTYPES

#include "Si2158_L1_API.h"
#include "Si2158_Properties_Strings.h"

#ifdef Si2158_COMMAND_LINE_APPLICATION

/* define a local PropObj variable to use for the Property Dictionary initializer */
Si2158_PropObj Si2158_prop;
char optionText[20];

/* _properties_features_text_insertion_start */
char *Si2158_featureText[] =
{
  "ATV",
  "COMMON",
  "DTV",
  "TUNER",
};
/* _properties_features_text_insertion_point */

/* _properties_strings_insertion_start */
Si2158_optionStruct    Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si2158_fieldDicoStruct Si2158_ATV_AFC_RANGE_PROP_FIELDS[] =
{
  {"RANGE_KHZ", Si2158_UNSIGNED_INT, &Si2158_prop.atv_afc_range.range_khz, sizeof(Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ)/sizeof(Si2158_optionStruct), Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ},
};

Si2158_optionStruct    Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
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
Si2158_fieldDicoStruct Si2158_ATV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_agc_speed.if_agc_speed, sizeof(Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2158_optionStruct), Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED},
};

Si2158_optionStruct    Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[] =
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
Si2158_optionStruct    Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2158_fieldDicoStruct Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_agc_speed_low_rssi.if_agc_speed, sizeof(Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED)/sizeof(Si2158_optionStruct), Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED},
  {"THLD",           Si2158_SIGNED_CHAR, &Si2158_prop.atv_agc_speed_low_rssi.thld        , sizeof(Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD        )/sizeof(Si2158_optionStruct), Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD        },
};

Si2158_optionStruct    Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN[] =
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
Si2158_optionStruct    Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2158_fieldDicoStruct Si2158_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[] =
{
  {"GAIN",   Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_artificial_snow.gain  , sizeof(Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN  )/sizeof(Si2158_optionStruct), Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN  },
  {"OFFSET",   Si2158_SIGNED_CHAR, &Si2158_prop.atv_artificial_snow.offset, sizeof(Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET)/sizeof(Si2158_optionStruct), Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET},
};

Si2158_optionStruct    Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[] =
{
  {"LIF_DIFF_IF1",     8},
  {"LIF_DIFF_IF2",    10},
  {"LIF_SE_IF1A",     12},
  {"LIF_SE_IF2A",     14},
};
Si2158_optionStruct    Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE[] =
{
  {"INTERNAL",     0},
  {"AGC1_3DB",     1},
  {"AGC2_3DB",     2},
};
Si2158_fieldDicoStruct Si2158_ATV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"ATV_OUT_TYPE",   Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_config_if_port.atv_out_type  , sizeof(Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE  )/sizeof(Si2158_optionStruct), Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE  },
  {"ATV_AGC_SOURCE", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_config_if_port.atv_agc_source, sizeof(Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE)/sizeof(Si2158_optionStruct), Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE},
};

Si2158_optionStruct    Si2158_ATV_EXT_AGC_PROP_MIN_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_ATV_EXT_AGC_PROP_MAX_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_ATV_EXT_AGC_PROP_FIELDS[] =
{
  {"MIN_10MV", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ext_agc.min_10mv, sizeof(Si2158_ATV_EXT_AGC_PROP_MIN_10MV)/sizeof(Si2158_optionStruct), Si2158_ATV_EXT_AGC_PROP_MIN_10MV},
  {"MAX_10MV", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ext_agc.max_10mv, sizeof(Si2158_ATV_EXT_AGC_PROP_MAX_10MV)/sizeof(Si2158_optionStruct), Si2158_ATV_EXT_AGC_PROP_MAX_10MV},
};

Si2158_optionStruct    Si2158_ATV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_ATV_IEN_PROP_PCLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_ATV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ien.chlien, sizeof(Si2158_ATV_IEN_PROP_CHLIEN)/sizeof(Si2158_optionStruct), Si2158_ATV_IEN_PROP_CHLIEN},
  {"PCLIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ien.pclien, sizeof(Si2158_ATV_IEN_PROP_PCLIEN)/sizeof(Si2158_optionStruct), Si2158_ATV_IEN_PROP_PCLIEN},
};

Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_PCLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_PCLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_ATV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_int_sense.chlnegen, sizeof(Si2158_ATV_INT_SENSE_PROP_CHLNEGEN)/sizeof(Si2158_optionStruct), Si2158_ATV_INT_SENSE_PROP_CHLNEGEN},
  {"PCLNEGEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_int_sense.pclnegen, sizeof(Si2158_ATV_INT_SENSE_PROP_PCLNEGEN)/sizeof(Si2158_optionStruct), Si2158_ATV_INT_SENSE_PROP_PCLNEGEN},
  {"CHLPOSEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_int_sense.chlposen, sizeof(Si2158_ATV_INT_SENSE_PROP_CHLPOSEN)/sizeof(Si2158_optionStruct), Si2158_ATV_INT_SENSE_PROP_CHLPOSEN},
  {"PCLPOSEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_int_sense.pclposen, sizeof(Si2158_ATV_INT_SENSE_PROP_PCLPOSEN)/sizeof(Si2158_optionStruct), Si2158_ATV_INT_SENSE_PROP_PCLPOSEN},
};

Si2158_optionStruct    Si2158_ATV_IR_PROP_GEAR[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_ATV_IR_PROP_FILTER[] =
{
  {"HW_FILTERS",         0},
  {"CUSTOM_FILTERS",     1},
};
Si2158_fieldDicoStruct Si2158_ATV_IR_PROP_FIELDS[] =
{
  {"GEAR",   Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ir.gear  , sizeof(Si2158_ATV_IR_PROP_GEAR  )/sizeof(Si2158_optionStruct), Si2158_ATV_IR_PROP_GEAR  },
  {"FILTER", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ir.filter, sizeof(Si2158_ATV_IR_PROP_FILTER)/sizeof(Si2158_optionStruct), Si2158_ATV_IR_PROP_FILTER},
};

Si2158_optionStruct    Si2158_ATV_IRCAL_DRIFT_PROP_STEP_LIMIT[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_ATV_IRCAL_DRIFT_PROP_DEAD_ZONE[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_ATV_IRCAL_DRIFT_PROP_FIELDS[] =
{
  {"STEP_LIMIT", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ircal_drift.step_limit, sizeof(Si2158_ATV_IRCAL_DRIFT_PROP_STEP_LIMIT)/sizeof(Si2158_optionStruct), Si2158_ATV_IRCAL_DRIFT_PROP_STEP_LIMIT},
  {"DEAD_ZONE",  Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ircal_drift.dead_zone , sizeof(Si2158_ATV_IRCAL_DRIFT_PROP_DEAD_ZONE )/sizeof(Si2158_optionStruct), Si2158_ATV_IRCAL_DRIFT_PROP_DEAD_ZONE },
};

Si2158_optionStruct    Si2158_ATV_IRCAL_MON_PROP_EXPIRATION_FIELDS[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_ATV_IRCAL_MON_PROP_DISABLE_THRESHOLD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_ATV_IRCAL_MON_PROP_FIELDS[] =
{
  {"EXPIRATION_FIELDS", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ircal_mon.expiration_fields, sizeof(Si2158_ATV_IRCAL_MON_PROP_EXPIRATION_FIELDS)/sizeof(Si2158_optionStruct), Si2158_ATV_IRCAL_MON_PROP_EXPIRATION_FIELDS},
  {"DISABLE_THRESHOLD", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_ircal_mon.disable_threshold, sizeof(Si2158_ATV_IRCAL_MON_PROP_DISABLE_THRESHOLD)/sizeof(Si2158_optionStruct), Si2158_ATV_IRCAL_MON_PROP_DISABLE_THRESHOLD},
};

Si2158_optionStruct    Si2158_ATV_LIF_FREQ_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",  7000}
};
Si2158_fieldDicoStruct Si2158_ATV_LIF_FREQ_PROP_FIELDS[] =
{
  {"OFFSET", Si2158_UNSIGNED_INT, &Si2158_prop.atv_lif_freq.offset, sizeof(Si2158_ATV_LIF_FREQ_PROP_OFFSET)/sizeof(Si2158_optionStruct), Si2158_ATV_LIF_FREQ_PROP_OFFSET},
};

Si2158_optionStruct    Si2158_ATV_LIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_ATV_LIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_ATV_LIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_lif_out.offset, sizeof(Si2158_ATV_LIF_OUT_PROP_OFFSET)/sizeof(Si2158_optionStruct), Si2158_ATV_LIF_OUT_PROP_OFFSET},
  {"AMP",    Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_lif_out.amp   , sizeof(Si2158_ATV_LIF_OUT_PROP_AMP   )/sizeof(Si2158_optionStruct), Si2158_ATV_LIF_OUT_PROP_AMP   },
};

Si2158_optionStruct    Si2158_ATV_MIN_LVL_LOCK_PROP_THRS[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_ATV_MIN_LVL_LOCK_PROP_FIELDS[] =
{
  {"THRS", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_min_lvl_lock.thrs, sizeof(Si2158_ATV_MIN_LVL_LOCK_PROP_THRS)/sizeof(Si2158_optionStruct), Si2158_ATV_MIN_LVL_LOCK_PROP_THRS},
};

Si2158_optionStruct    Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET[] =
{
  {"MIN_RANGE",   -13},
  {"MAX_RANGE",     7}
};
Si2158_optionStruct    Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_ATV_PGA_TARGET_PROP_FIELDS[] =
{
  {"PGA_TARGET",        Si2158_SIGNED_CHAR, &Si2158_prop.atv_pga_target.pga_target     , sizeof(Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET     )/sizeof(Si2158_optionStruct), Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET     },
  {"OVERRIDE_ENABLE", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_pga_target.override_enable, sizeof(Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE)/sizeof(Si2158_optionStruct), Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE},
};

Si2158_optionStruct    Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP[] =
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
Si2158_fieldDicoStruct Si2158_ATV_RF_TOP_PROP_FIELDS[] =
{
  {"ATV_RF_TOP", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_rf_top.atv_rf_top, sizeof(Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP)/sizeof(Si2158_optionStruct), Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP},
};

Si2158_optionStruct    Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2158_optionStruct    Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2158_fieldDicoStruct Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si2158_SIGNED_CHAR, &Si2158_prop.atv_rsq_rssi_threshold.lo, sizeof(Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si2158_optionStruct), Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si2158_SIGNED_CHAR, &Si2158_prop.atv_rsq_rssi_threshold.hi, sizeof(Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si2158_optionStruct), Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si2158_optionStruct    Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS[] =
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
Si2158_optionStruct    Si2158_ATV_VIDEO_MODE_PROP_COLOR[] =
{
  {"PAL_NTSC",     0},
  {"SECAM",        1},
};
Si2158_optionStruct    Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si2158_fieldDicoStruct Si2158_ATV_VIDEO_MODE_PROP_FIELDS[] =
{
  {"VIDEO_SYS",       Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_video_mode.video_sys      , sizeof(Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS      )/sizeof(Si2158_optionStruct), Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS      },
  {"COLOR",           Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_video_mode.color          , sizeof(Si2158_ATV_VIDEO_MODE_PROP_COLOR          )/sizeof(Si2158_optionStruct), Si2158_ATV_VIDEO_MODE_PROP_COLOR          },
  {"INVERT_SPECTRUM", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_video_mode.invert_spectrum, sizeof(Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM)/sizeof(Si2158_optionStruct), Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM},
};

Si2158_optionStruct    Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   127}
};
Si2158_fieldDicoStruct Si2158_ATV_VSNR_CAP_PROP_FIELDS[] =
{
  {"ATV_VSNR_CAP", Si2158_UNSIGNED_CHAR, &Si2158_prop.atv_vsnr_cap.atv_vsnr_cap, sizeof(Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP)/sizeof(Si2158_optionStruct), Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP},
};

Si2158_optionStruct    Si2158_CRYSTAL_TRIM_PROP_XO_CAP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",    15}
};
Si2158_fieldDicoStruct Si2158_CRYSTAL_TRIM_PROP_FIELDS[] =
{
  {"XO_CAP", Si2158_UNSIGNED_CHAR, &Si2158_prop.crystal_trim.xo_cap, sizeof(Si2158_CRYSTAL_TRIM_PROP_XO_CAP)/sizeof(Si2158_optionStruct), Si2158_CRYSTAL_TRIM_PROP_XO_CAP},
};

Si2158_optionStruct    Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   207}
};
Si2158_fieldDicoStruct Si2158_DEBUG_SAMPLE_FREQ_PROP_FIELDS[] =
{
  {"FS_MHZ", Si2158_UNSIGNED_INT, &Si2158_prop.debug_sample_freq.fs_mhz, sizeof(Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ)/sizeof(Si2158_optionStruct), Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ},
};

Si2158_optionStruct    Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[] =
{
  {"LOW",      0},
  {"HIGH",     1},
};
Si2158_optionStruct    Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN[] =
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
Si2158_fieldDicoStruct Si2158_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[] =
{
  {"LEVEL", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_agc_freeze_input.level, sizeof(Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL)/sizeof(Si2158_optionStruct), Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL},
  {"PIN",   Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_agc_freeze_input.pin  , sizeof(Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN  )/sizeof(Si2158_optionStruct), Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN  },
};

Si2158_optionStruct    Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[] =
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
Si2158_optionStruct    Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si2158_fieldDicoStruct Si2158_DTV_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_agc_speed.if_agc_speed, sizeof(Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2158_optionStruct), Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_agc_speed.agc_decim   , sizeof(Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si2158_optionStruct), Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM   },
};

Si2158_optionStruct    Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[] =
{
  {"LIF_IF1",         0},
  {"LIF_IF2",         1},
  {"LIF_SE_IF1A",     4},
  {"LIF_SE_IF2A",     5},
};
Si2158_optionStruct    Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[] =
{
  {"INTERNAL",      0},
  {"AGC1_3DB",      1},
  {"AGC2_3DB",      2},
  {"AGC1_FULL",     3},
  {"AGC2_FULL",     4},
};
Si2158_fieldDicoStruct Si2158_DTV_CONFIG_IF_PORT_PROP_FIELDS[] =
{
  {"DTV_OUT_TYPE",   Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_config_if_port.dtv_out_type  , sizeof(Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  )/sizeof(Si2158_optionStruct), Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE  },
  {"DTV_AGC_SOURCE", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_config_if_port.dtv_agc_source, sizeof(Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE)/sizeof(Si2158_optionStruct), Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE},
};

Si2158_optionStruct    Si2158_DTV_EXT_AGC_PROP_MIN_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_DTV_EXT_AGC_PROP_MAX_10MV[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_DTV_EXT_AGC_PROP_FIELDS[] =
{
  {"MIN_10MV", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_ext_agc.min_10mv, sizeof(Si2158_DTV_EXT_AGC_PROP_MIN_10MV)/sizeof(Si2158_optionStruct), Si2158_DTV_EXT_AGC_PROP_MIN_10MV},
  {"MAX_10MV", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_ext_agc.max_10mv, sizeof(Si2158_DTV_EXT_AGC_PROP_MAX_10MV)/sizeof(Si2158_optionStruct), Si2158_DTV_EXT_AGC_PROP_MAX_10MV},
};

Si2158_optionStruct    Si2158_DTV_FILTER_SELECT_PROP_FILTER[] =
{
  {"LEGACY",      0},
  {"CUSTOM1",     1},
  {"CUSTOM2",     2},
};
Si2158_fieldDicoStruct Si2158_DTV_FILTER_SELECT_PROP_FIELDS[] =
{
  {"FILTER", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_filter_select.filter, sizeof(Si2158_DTV_FILTER_SELECT_PROP_FILTER)/sizeof(Si2158_optionStruct), Si2158_DTV_FILTER_SELECT_PROP_FILTER},
};

Si2158_optionStruct    Si2158_DTV_IEN_PROP_CHLIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_DTV_IEN_PROP_FIELDS[] =
{
  {"CHLIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_ien.chlien, sizeof(Si2158_DTV_IEN_PROP_CHLIEN)/sizeof(Si2158_optionStruct), Si2158_DTV_IEN_PROP_CHLIEN},
};

Si2158_optionStruct    Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[] =
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
Si2158_optionStruct    Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[] =
{
  {"OFF",     0},
  {"2",       1},
  {"4",       2},
  {"8",       3},
};
Si2158_fieldDicoStruct Si2158_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[] =
{
  {"IF_AGC_SPEED", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_initial_agc_speed.if_agc_speed, sizeof(Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED)/sizeof(Si2158_optionStruct), Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED},
  {"AGC_DECIM",    Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_initial_agc_speed.agc_decim   , sizeof(Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   )/sizeof(Si2158_optionStruct), Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM   },
};

Si2158_optionStruct    Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE", 65535}
};
Si2158_fieldDicoStruct Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[] =
{
  {"PERIOD", Si2158_UNSIGNED_INT, &Si2158_prop.dtv_initial_agc_speed_period.period, sizeof(Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD)/sizeof(Si2158_optionStruct), Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD},
};

Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_ATSC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_DVBT[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_DVBC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_DTMB[] =
{
  {"LIF",     0},
  {"ZIF",     1},
};
Si2158_fieldDicoStruct Si2158_DTV_INTERNAL_ZIF_PROP_FIELDS[] =
{
  {"ATSC",   Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.atsc  , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_ATSC  )/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_ATSC  },
  {"QAM_US", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.qam_us, sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US)/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US},
  {"DVBT",   Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.dvbt  , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_DVBT  )/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_DVBT  },
  {"DVBC",   Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.dvbc  , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_DVBC  )/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_DVBC  },
  {"ISDBT",  Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.isdbt , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT )/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT },
  {"ISDBC",  Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.isdbc , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC )/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC },
  {"DTMB",   Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_internal_zif.dtmb  , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_DTMB  )/sizeof(Si2158_optionStruct), Si2158_DTV_INTERNAL_ZIF_PROP_DTMB  },
};

Si2158_optionStruct    Si2158_DTV_INT_SENSE_PROP_CHLNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_DTV_INT_SENSE_PROP_CHLPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_DTV_INT_SENSE_PROP_FIELDS[] =
{
  {"CHLNEGEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_int_sense.chlnegen, sizeof(Si2158_DTV_INT_SENSE_PROP_CHLNEGEN)/sizeof(Si2158_optionStruct), Si2158_DTV_INT_SENSE_PROP_CHLNEGEN},
  {"CHLPOSEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_int_sense.chlposen, sizeof(Si2158_DTV_INT_SENSE_PROP_CHLPOSEN)/sizeof(Si2158_optionStruct), Si2158_DTV_INT_SENSE_PROP_CHLPOSEN},
};

Si2158_optionStruct    Si2158_DTV_LIF_FREQ_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",  7000}
};
Si2158_fieldDicoStruct Si2158_DTV_LIF_FREQ_PROP_FIELDS[] =
{
  {"OFFSET", Si2158_UNSIGNED_INT, &Si2158_prop.dtv_lif_freq.offset, sizeof(Si2158_DTV_LIF_FREQ_PROP_OFFSET)/sizeof(Si2158_optionStruct), Si2158_DTV_LIF_FREQ_PROP_OFFSET},
};

Si2158_optionStruct    Si2158_DTV_LIF_OUT_PROP_OFFSET[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_optionStruct    Si2158_DTV_LIF_OUT_PROP_AMP[] =
{
  {"MIN_RANGE",     0},
  {"MAX_RANGE",   255}
};
Si2158_fieldDicoStruct Si2158_DTV_LIF_OUT_PROP_FIELDS[] =
{
  {"OFFSET", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_lif_out.offset, sizeof(Si2158_DTV_LIF_OUT_PROP_OFFSET)/sizeof(Si2158_optionStruct), Si2158_DTV_LIF_OUT_PROP_OFFSET},
  {"AMP",    Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_lif_out.amp   , sizeof(Si2158_DTV_LIF_OUT_PROP_AMP   )/sizeof(Si2158_optionStruct), Si2158_DTV_LIF_OUT_PROP_AMP   },
};

Si2158_optionStruct    Si2158_DTV_MODE_PROP_BW[] =
{
  {"BW_6MHZ",     6},
  {"BW_7MHZ",     7},
  {"BW_8MHZ",     8},
};
Si2158_optionStruct    Si2158_DTV_MODE_PROP_MODULATION[] =
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
Si2158_optionStruct    Si2158_DTV_MODE_PROP_INVERT_SPECTRUM[] =
{
  {"NORMAL",       0},
  {"INVERTED",     1},
};
Si2158_fieldDicoStruct Si2158_DTV_MODE_PROP_FIELDS[] =
{
  {"BW",              Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_mode.bw             , sizeof(Si2158_DTV_MODE_PROP_BW             )/sizeof(Si2158_optionStruct), Si2158_DTV_MODE_PROP_BW             },
  {"MODULATION",      Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_mode.modulation     , sizeof(Si2158_DTV_MODE_PROP_MODULATION     )/sizeof(Si2158_optionStruct), Si2158_DTV_MODE_PROP_MODULATION     },
  {"INVERT_SPECTRUM", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_mode.invert_spectrum, sizeof(Si2158_DTV_MODE_PROP_INVERT_SPECTRUM)/sizeof(Si2158_optionStruct), Si2158_DTV_MODE_PROP_INVERT_SPECTRUM},
};

Si2158_optionStruct    Si2158_DTV_PGA_LIMITS_PROP_MIN[] =
{
  {"MIN_RANGE",    -1},
  {"MAX_RANGE",    56}
};
Si2158_optionStruct    Si2158_DTV_PGA_LIMITS_PROP_MAX[] =
{
  {"MIN_RANGE",    -1},
  {"MAX_RANGE",    56}
};
Si2158_fieldDicoStruct Si2158_DTV_PGA_LIMITS_PROP_FIELDS[] =
{
  {"MIN",   Si2158_SIGNED_CHAR, &Si2158_prop.dtv_pga_limits.min, sizeof(Si2158_DTV_PGA_LIMITS_PROP_MIN)/sizeof(Si2158_optionStruct), Si2158_DTV_PGA_LIMITS_PROP_MIN},
  {"MAX",   Si2158_SIGNED_CHAR, &Si2158_prop.dtv_pga_limits.max, sizeof(Si2158_DTV_PGA_LIMITS_PROP_MAX)/sizeof(Si2158_optionStruct), Si2158_DTV_PGA_LIMITS_PROP_MAX},
};

Si2158_optionStruct    Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET[] =
{
  {"MIN_RANGE",   -13},
  {"MAX_RANGE",     7}
};
Si2158_optionStruct    Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_DTV_PGA_TARGET_PROP_FIELDS[] =
{
  {"PGA_TARGET",        Si2158_SIGNED_CHAR, &Si2158_prop.dtv_pga_target.pga_target     , sizeof(Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET     )/sizeof(Si2158_optionStruct), Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET     },
  {"OVERRIDE_ENABLE", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_pga_target.override_enable, sizeof(Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE)/sizeof(Si2158_optionStruct), Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE},
};

Si2158_optionStruct    Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP[] =
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
Si2158_fieldDicoStruct Si2158_DTV_RF_TOP_PROP_FIELDS[] =
{
  {"DTV_RF_TOP", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_rf_top.dtv_rf_top, sizeof(Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP)/sizeof(Si2158_optionStruct), Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP},
};

Si2158_optionStruct    Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2158_optionStruct    Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[] =
{
  {"MIN_RANGE",  -128},
  {"MAX_RANGE",   127}
};
Si2158_fieldDicoStruct Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[] =
{
  {"LO",   Si2158_SIGNED_CHAR, &Si2158_prop.dtv_rsq_rssi_threshold.lo, sizeof(Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO)/sizeof(Si2158_optionStruct), Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO},
  {"HI",   Si2158_SIGNED_CHAR, &Si2158_prop.dtv_rsq_rssi_threshold.hi, sizeof(Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI)/sizeof(Si2158_optionStruct), Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI},
};

Si2158_optionStruct    Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH[] =
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
Si2158_fieldDicoStruct Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS[] =
{
  {"BANDWIDTH", Si2158_UNSIGNED_CHAR, &Si2158_prop.dtv_zif_dc_canceller_bw.bandwidth, sizeof(Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH)/sizeof(Si2158_optionStruct), Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH},
};

Si2158_optionStruct    Si2158_MASTER_IEN_PROP_TUNIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2158_optionStruct    Si2158_MASTER_IEN_PROP_ATVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2158_optionStruct    Si2158_MASTER_IEN_PROP_DTVIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2158_optionStruct    Si2158_MASTER_IEN_PROP_ERRIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2158_optionStruct    Si2158_MASTER_IEN_PROP_CTSIEN[] =
{
  {"OFF",     0},
  {"ON",      1},
};
Si2158_fieldDicoStruct Si2158_MASTER_IEN_PROP_FIELDS[] =
{
  {"TUNIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.master_ien.tunien, sizeof(Si2158_MASTER_IEN_PROP_TUNIEN)/sizeof(Si2158_optionStruct), Si2158_MASTER_IEN_PROP_TUNIEN},
  {"ATVIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.master_ien.atvien, sizeof(Si2158_MASTER_IEN_PROP_ATVIEN)/sizeof(Si2158_optionStruct), Si2158_MASTER_IEN_PROP_ATVIEN},
  {"DTVIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.master_ien.dtvien, sizeof(Si2158_MASTER_IEN_PROP_DTVIEN)/sizeof(Si2158_optionStruct), Si2158_MASTER_IEN_PROP_DTVIEN},
  {"ERRIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.master_ien.errien, sizeof(Si2158_MASTER_IEN_PROP_ERRIEN)/sizeof(Si2158_optionStruct), Si2158_MASTER_IEN_PROP_ERRIEN},
  {"CTSIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.master_ien.ctsien, sizeof(Si2158_MASTER_IEN_PROP_CTSIEN)/sizeof(Si2158_optionStruct), Si2158_MASTER_IEN_PROP_CTSIEN},
};

Si2158_optionStruct    Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE[] =
{
  {"MIN_RANGE", -32768},
  {"MAX_RANGE", 32767}
};
Si2158_fieldDicoStruct Si2158_TUNER_BLOCKED_VCO_PROP_FIELDS[] =
{
  {"VCO_CODE",   Si2158_SIGNED_INT, &Si2158_prop.tuner_blocked_vco.vco_code, sizeof(Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE)/sizeof(Si2158_optionStruct), Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE},
};

Si2158_optionStruct    Si2158_TUNER_IEN_PROP_TCIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_IEN_PROP_RSSILIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_IEN_PROP_RSSIHIEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_TUNER_IEN_PROP_FIELDS[] =
{
  {"TCIEN",    Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_ien.tcien   , sizeof(Si2158_TUNER_IEN_PROP_TCIEN   )/sizeof(Si2158_optionStruct), Si2158_TUNER_IEN_PROP_TCIEN   },
  {"RSSILIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_ien.rssilien, sizeof(Si2158_TUNER_IEN_PROP_RSSILIEN)/sizeof(Si2158_optionStruct), Si2158_TUNER_IEN_PROP_RSSILIEN},
  {"RSSIHIEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_ien.rssihien, sizeof(Si2158_TUNER_IEN_PROP_RSSIHIEN)/sizeof(Si2158_optionStruct), Si2158_TUNER_IEN_PROP_RSSIHIEN},
};

Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_TCNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_TCPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN[] =
{
  {"DISABLE",     0},
  {"ENABLE",      1},
};
Si2158_fieldDicoStruct Si2158_TUNER_INT_SENSE_PROP_FIELDS[] =
{
  {"TCNEGEN",    Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_int_sense.tcnegen   , sizeof(Si2158_TUNER_INT_SENSE_PROP_TCNEGEN   )/sizeof(Si2158_optionStruct), Si2158_TUNER_INT_SENSE_PROP_TCNEGEN   },
  {"RSSILNEGEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_int_sense.rssilnegen, sizeof(Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN)/sizeof(Si2158_optionStruct), Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN},
  {"RSSIHNEGEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_int_sense.rssihnegen, sizeof(Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN)/sizeof(Si2158_optionStruct), Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN},
  {"TCPOSEN",    Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_int_sense.tcposen   , sizeof(Si2158_TUNER_INT_SENSE_PROP_TCPOSEN   )/sizeof(Si2158_optionStruct), Si2158_TUNER_INT_SENSE_PROP_TCPOSEN   },
  {"RSSILPOSEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_int_sense.rssilposen, sizeof(Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN)/sizeof(Si2158_optionStruct), Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN},
  {"RSSIHPOSEN", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_int_sense.rssihposen, sizeof(Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN)/sizeof(Si2158_optionStruct), Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN},
};

Si2158_optionStruct    Si2158_TUNER_LO_INJECTION_PROP_BAND_1[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2158_optionStruct    Si2158_TUNER_LO_INJECTION_PROP_BAND_2[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2158_optionStruct    Si2158_TUNER_LO_INJECTION_PROP_BAND_3[] =
{
  {"LOW_SIDE",      0},
  {"HIGH_SIDE",     1},
};
Si2158_fieldDicoStruct Si2158_TUNER_LO_INJECTION_PROP_FIELDS[] =
{
  {"BAND_1", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_lo_injection.band_1, sizeof(Si2158_TUNER_LO_INJECTION_PROP_BAND_1)/sizeof(Si2158_optionStruct), Si2158_TUNER_LO_INJECTION_PROP_BAND_1},
  {"BAND_2", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_lo_injection.band_2, sizeof(Si2158_TUNER_LO_INJECTION_PROP_BAND_2)/sizeof(Si2158_optionStruct), Si2158_TUNER_LO_INJECTION_PROP_BAND_2},
  {"BAND_3", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_lo_injection.band_3, sizeof(Si2158_TUNER_LO_INJECTION_PROP_BAND_3)/sizeof(Si2158_optionStruct), Si2158_TUNER_LO_INJECTION_PROP_BAND_3},
};

Si2158_optionStruct    Si2158_TUNER_RETURN_LOSS_PROP_CONFIG[] =
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
Si2158_optionStruct    Si2158_TUNER_RETURN_LOSS_PROP_MODE[] =
{
  {"TERRESTRIAL",     0},
  {"CABLE",           1},
};
Si2158_fieldDicoStruct Si2158_TUNER_RETURN_LOSS_PROP_FIELDS[] =
{
  {"CONFIG", Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_return_loss.config, sizeof(Si2158_TUNER_RETURN_LOSS_PROP_CONFIG)/sizeof(Si2158_optionStruct), Si2158_TUNER_RETURN_LOSS_PROP_CONFIG},
  {"MODE",   Si2158_UNSIGNED_CHAR, &Si2158_prop.tuner_return_loss.mode  , sizeof(Si2158_TUNER_RETURN_LOSS_PROP_MODE  )/sizeof(Si2158_optionStruct), Si2158_TUNER_RETURN_LOSS_PROP_MODE  },
};

Si2158_propertyInfoStruct Si2158_propertyDictionary[] =
{
  {Si2158_ATV   , "ATV_AFC_RANGE"               , sizeof(Si2158_ATV_AFC_RANGE_PROP_FIELDS               )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_AFC_RANGE_PROP_FIELDS                , Si2158_ATV_AFC_RANGE_PROP                },
  {Si2158_ATV   , "ATV_AGC_SPEED"               , sizeof(Si2158_ATV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_AGC_SPEED_PROP_FIELDS                , Si2158_ATV_AGC_SPEED_PROP                },
  {Si2158_ATV   , "ATV_AGC_SPEED_LOW_RSSI"      , sizeof(Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS      )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS       , Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP       },
  {Si2158_ATV   , "ATV_ARTIFICIAL_SNOW"         , sizeof(Si2158_ATV_ARTIFICIAL_SNOW_PROP_FIELDS         )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_ARTIFICIAL_SNOW_PROP_FIELDS          , Si2158_ATV_ARTIFICIAL_SNOW_PROP          },
  {Si2158_ATV   , "ATV_CONFIG_IF_PORT"          , sizeof(Si2158_ATV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_CONFIG_IF_PORT_PROP_FIELDS           , Si2158_ATV_CONFIG_IF_PORT_PROP           },
  {Si2158_ATV   , "ATV_EXT_AGC"                 , sizeof(Si2158_ATV_EXT_AGC_PROP_FIELDS                 )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_EXT_AGC_PROP_FIELDS                  , Si2158_ATV_EXT_AGC_PROP                  },
  {Si2158_ATV   , "ATV_IEN"                     , sizeof(Si2158_ATV_IEN_PROP_FIELDS                     )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_IEN_PROP_FIELDS                      , Si2158_ATV_IEN_PROP                      },
  {Si2158_ATV   , "ATV_INT_SENSE"               , sizeof(Si2158_ATV_INT_SENSE_PROP_FIELDS               )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_INT_SENSE_PROP_FIELDS                , Si2158_ATV_INT_SENSE_PROP                },
  {Si2158_ATV   , "ATV_IR"                      , sizeof(Si2158_ATV_IR_PROP_FIELDS                      )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_IR_PROP_FIELDS                       , Si2158_ATV_IR_PROP                       },
  {Si2158_ATV   , "ATV_IRCAL_DRIFT"             , sizeof(Si2158_ATV_IRCAL_DRIFT_PROP_FIELDS             )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_IRCAL_DRIFT_PROP_FIELDS              , Si2158_ATV_IRCAL_DRIFT_PROP              },
  {Si2158_ATV   , "ATV_IRCAL_MON"               , sizeof(Si2158_ATV_IRCAL_MON_PROP_FIELDS               )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_IRCAL_MON_PROP_FIELDS                , Si2158_ATV_IRCAL_MON_PROP                },
  {Si2158_ATV   , "ATV_LIF_FREQ"                , sizeof(Si2158_ATV_LIF_FREQ_PROP_FIELDS                )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_LIF_FREQ_PROP_FIELDS                 , Si2158_ATV_LIF_FREQ_PROP                 },
  {Si2158_ATV   , "ATV_LIF_OUT"                 , sizeof(Si2158_ATV_LIF_OUT_PROP_FIELDS                 )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_LIF_OUT_PROP_FIELDS                  , Si2158_ATV_LIF_OUT_PROP                  },
  {Si2158_ATV   , "ATV_MIN_LVL_LOCK"            , sizeof(Si2158_ATV_MIN_LVL_LOCK_PROP_FIELDS            )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_MIN_LVL_LOCK_PROP_FIELDS             , Si2158_ATV_MIN_LVL_LOCK_PROP             },
  {Si2158_ATV   , "ATV_PGA_TARGET"              , sizeof(Si2158_ATV_PGA_TARGET_PROP_FIELDS              )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_PGA_TARGET_PROP_FIELDS               , Si2158_ATV_PGA_TARGET_PROP               },
  {Si2158_ATV   , "ATV_RF_TOP"                  , sizeof(Si2158_ATV_RF_TOP_PROP_FIELDS                  )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_RF_TOP_PROP_FIELDS                   , Si2158_ATV_RF_TOP_PROP                   },
  {Si2158_ATV   , "ATV_RSQ_RSSI_THRESHOLD"      , sizeof(Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si2158_ATV   , "ATV_VIDEO_MODE"              , sizeof(Si2158_ATV_VIDEO_MODE_PROP_FIELDS              )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_VIDEO_MODE_PROP_FIELDS               , Si2158_ATV_VIDEO_MODE_PROP               },
  {Si2158_ATV   , "ATV_VSNR_CAP"                , sizeof(Si2158_ATV_VSNR_CAP_PROP_FIELDS                )/sizeof(Si2158_fieldDicoStruct), Si2158_ATV_VSNR_CAP_PROP_FIELDS                 , Si2158_ATV_VSNR_CAP_PROP                 },
  {Si2158_COMMON, "CRYSTAL_TRIM"                , sizeof(Si2158_CRYSTAL_TRIM_PROP_FIELDS                )/sizeof(Si2158_fieldDicoStruct), Si2158_CRYSTAL_TRIM_PROP_FIELDS                 , Si2158_CRYSTAL_TRIM_PROP                 },
  {Si2158_COMMON, "MASTER_IEN"                  , sizeof(Si2158_MASTER_IEN_PROP_FIELDS                  )/sizeof(Si2158_fieldDicoStruct), Si2158_MASTER_IEN_PROP_FIELDS                   , Si2158_MASTER_IEN_PROP                   },
  {Si2158_DTV   , "DTV_AGC_FREEZE_INPUT"        , sizeof(Si2158_DTV_AGC_FREEZE_INPUT_PROP_FIELDS        )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_AGC_FREEZE_INPUT_PROP_FIELDS         , Si2158_DTV_AGC_FREEZE_INPUT_PROP         },
  {Si2158_DTV   , "DTV_AGC_SPEED"               , sizeof(Si2158_DTV_AGC_SPEED_PROP_FIELDS               )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_AGC_SPEED_PROP_FIELDS                , Si2158_DTV_AGC_SPEED_PROP                },
  {Si2158_DTV   , "DTV_CONFIG_IF_PORT"          , sizeof(Si2158_DTV_CONFIG_IF_PORT_PROP_FIELDS          )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_CONFIG_IF_PORT_PROP_FIELDS           , Si2158_DTV_CONFIG_IF_PORT_PROP           },
  {Si2158_DTV   , "DTV_EXT_AGC"                 , sizeof(Si2158_DTV_EXT_AGC_PROP_FIELDS                 )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_EXT_AGC_PROP_FIELDS                  , Si2158_DTV_EXT_AGC_PROP                  },
  {Si2158_DTV   , "DTV_FILTER_SELECT"           , sizeof(Si2158_DTV_FILTER_SELECT_PROP_FIELDS           )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_FILTER_SELECT_PROP_FIELDS            , Si2158_DTV_FILTER_SELECT_PROP            },
  {Si2158_DTV   , "DTV_IEN"                     , sizeof(Si2158_DTV_IEN_PROP_FIELDS                     )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_IEN_PROP_FIELDS                      , Si2158_DTV_IEN_PROP                      },
  {Si2158_DTV   , "DTV_INITIAL_AGC_SPEED"       , sizeof(Si2158_DTV_INITIAL_AGC_SPEED_PROP_FIELDS       )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_INITIAL_AGC_SPEED_PROP_FIELDS        , Si2158_DTV_INITIAL_AGC_SPEED_PROP        },
  {Si2158_DTV   , "DTV_INITIAL_AGC_SPEED_PERIOD", sizeof(Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS)/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS , Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP },
  {Si2158_DTV   , "DTV_INTERNAL_ZIF"            , sizeof(Si2158_DTV_INTERNAL_ZIF_PROP_FIELDS            )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_INTERNAL_ZIF_PROP_FIELDS             , Si2158_DTV_INTERNAL_ZIF_PROP             },
  {Si2158_DTV   , "DTV_INT_SENSE"               , sizeof(Si2158_DTV_INT_SENSE_PROP_FIELDS               )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_INT_SENSE_PROP_FIELDS                , Si2158_DTV_INT_SENSE_PROP                },
  {Si2158_DTV   , "DTV_LIF_FREQ"                , sizeof(Si2158_DTV_LIF_FREQ_PROP_FIELDS                )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_LIF_FREQ_PROP_FIELDS                 , Si2158_DTV_LIF_FREQ_PROP                 },
  {Si2158_DTV   , "DTV_LIF_OUT"                 , sizeof(Si2158_DTV_LIF_OUT_PROP_FIELDS                 )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_LIF_OUT_PROP_FIELDS                  , Si2158_DTV_LIF_OUT_PROP                  },
  {Si2158_DTV   , "DTV_MODE"                    , sizeof(Si2158_DTV_MODE_PROP_FIELDS                    )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_MODE_PROP_FIELDS                     , Si2158_DTV_MODE_PROP                     },
  {Si2158_DTV   , "DTV_PGA_LIMITS"              , sizeof(Si2158_DTV_PGA_LIMITS_PROP_FIELDS              )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_PGA_LIMITS_PROP_FIELDS               , Si2158_DTV_PGA_LIMITS_PROP               },
  {Si2158_DTV   , "DTV_PGA_TARGET"              , sizeof(Si2158_DTV_PGA_TARGET_PROP_FIELDS              )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_PGA_TARGET_PROP_FIELDS               , Si2158_DTV_PGA_TARGET_PROP               },
  {Si2158_DTV   , "DTV_RF_TOP"                  , sizeof(Si2158_DTV_RF_TOP_PROP_FIELDS                  )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_RF_TOP_PROP_FIELDS                   , Si2158_DTV_RF_TOP_PROP                   },
  {Si2158_DTV   , "DTV_RSQ_RSSI_THRESHOLD"      , sizeof(Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS      )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS       , Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP       },
  {Si2158_DTV   , "DTV_ZIF_DC_CANCELLER_BW"     , sizeof(Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS     )/sizeof(Si2158_fieldDicoStruct), Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS      , Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP      },
  {Si2158_TUNER , "DEBUG_SAMPLE_FREQ"           , sizeof(Si2158_DEBUG_SAMPLE_FREQ_PROP_FIELDS           )/sizeof(Si2158_fieldDicoStruct), Si2158_DEBUG_SAMPLE_FREQ_PROP_FIELDS            , Si2158_DEBUG_SAMPLE_FREQ_PROP            },
  {Si2158_TUNER , "TUNER_BLOCKED_VCO"           , sizeof(Si2158_TUNER_BLOCKED_VCO_PROP_FIELDS           )/sizeof(Si2158_fieldDicoStruct), Si2158_TUNER_BLOCKED_VCO_PROP_FIELDS            , Si2158_TUNER_BLOCKED_VCO_PROP            },
  {Si2158_TUNER , "TUNER_IEN"                   , sizeof(Si2158_TUNER_IEN_PROP_FIELDS                   )/sizeof(Si2158_fieldDicoStruct), Si2158_TUNER_IEN_PROP_FIELDS                    , Si2158_TUNER_IEN_PROP                    },
  {Si2158_TUNER , "TUNER_INT_SENSE"             , sizeof(Si2158_TUNER_INT_SENSE_PROP_FIELDS             )/sizeof(Si2158_fieldDicoStruct), Si2158_TUNER_INT_SENSE_PROP_FIELDS              , Si2158_TUNER_INT_SENSE_PROP              },
  {Si2158_TUNER , "TUNER_LO_INJECTION"          , sizeof(Si2158_TUNER_LO_INJECTION_PROP_FIELDS          )/sizeof(Si2158_fieldDicoStruct), Si2158_TUNER_LO_INJECTION_PROP_FIELDS           , Si2158_TUNER_LO_INJECTION_PROP           },
  {Si2158_TUNER , "TUNER_RETURN_LOSS"           , sizeof(Si2158_TUNER_RETURN_LOSS_PROP_FIELDS           )/sizeof(Si2158_fieldDicoStruct), Si2158_TUNER_RETURN_LOSS_PROP_FIELDS            , Si2158_TUNER_RETURN_LOSS_PROP            },
};
/* _properties_strings_insertion_point */

int   Si2158_PropertyNames        (L1_Si2158_Context *api, char *msg)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si2158_propertyDictionary)/sizeof(Si2158_propertyInfoStruct);
  msg[0]='\0';
  for (propIndex=0; propIndex<size; propIndex++)
  {
    strcat(msg,Si2158_propertyDictionary[propIndex].name);
    if (propIndex< (size-1)) strcat(msg," ");
  }
  return propIndex;
};

int   Si2158_PropertyIndex        (L1_Si2158_Context *api, char *property)
{
  int propIndex;
  int size;
  api = api; /* to avoid 'unused parameter' warning */
  size = sizeof(Si2158_propertyDictionary)/sizeof(Si2158_propertyInfoStruct);
  for (propIndex=0; propIndex <size; propIndex++)
  {
    if (strcmp_nocase(property, Si2158_propertyDictionary[propIndex].name)==0)
    {
      return propIndex;
    }
  }
  return -1;
};

int   Si2158_PropertyFields       (L1_Si2158_Context *api, int propIndex, char *msg)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (fieldIndex=0; fieldIndex < Si2158_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    strcat(msg, Si2158_propertyDictionary[propIndex].field[fieldIndex].name);
    if (fieldIndex< (Si2158_propertyDictionary[propIndex].nbFields-1)) strcat(msg," ");
  }
  return -1;
};

int   Si2158_PropertyFieldIndex   (L1_Si2158_Context *api, int propIndex, char *field)
{
  int fieldIndex;
  api = api; /* to avoid 'unused parameter' warning */
  for (fieldIndex=0; fieldIndex < Si2158_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    if (strcmp_nocase(field, Si2158_propertyDictionary[propIndex].field[fieldIndex].name)==0)
    {
      return fieldIndex;
    }
  }
  return -1;
};

int   Si2158_PropertyFieldEnums   (L1_Si2158_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int enumIndex;
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (enumIndex=0; enumIndex < Si2158_propertyDictionary[propIndex].field[fieldIndex].nbOptions; enumIndex++)
  {
    strcat(msg, Si2158_propertyDictionary[propIndex].field[fieldIndex].option[enumIndex].name);
    if (enumIndex < (Si2158_propertyDictionary[propIndex].field[fieldIndex].nbOptions-1)) strcat(msg," ");
  }
  return enumIndex;
};

int   Si2158_PropertyFieldRanges  (L1_Si2158_Context *api, int propIndex, int fieldIndex, char *msg)
{
  int index;
  char buf[10];
  api = api; /* to avoid 'unused parameter' warning */
  msg[0]='\0';
  for (index=0; index < 2; index++)
  {
    itoa(Si2158_propertyDictionary[propIndex].field[fieldIndex].option[index].value,buf,10);
    strcat(msg, buf);
    if (index < 1) strcat(msg," - ");
  }
  return index;
};

int   Si2158_GetValueFromEntry    (L1_Si2158_Context *api, Si2158_fieldDicoStruct field, char *entry, int *value)
{
  int optionIndex;
  api = api; /* to avoid 'unused parameter' warning */

  if (!strcmp_nocase(field.option[0].name,"MIN_RANGE"))
  {
    if (field.datatype== Si2158_UNSIGNED_INT || field.datatype== Si2158_UNSIGNED_CHAR)
    {
      *value = (unsigned int)atoi(entry);
      return 1;
    }
    else if (field.datatype == Si2158_SIGNED_INT || field.datatype == Si2158_SIGNED_CHAR)
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

char *Si2158_GetEnumFromValue     (L1_Si2158_Context *api, Si2158_fieldDicoStruct field, int iValue)
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
      return field.option[optionIndex].name;
    }
  }
  return (char*)NULL;
};

int   Si2158_GetValueFromField    (L1_Si2158_Context *api, Si2158_fieldDicoStruct field)
{
  short intValue;
  short *fieldAsInt;
  short iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si2158_SIGNED_INT   )
  {
      fieldAsInt= (short *) ((field.pField-(void *) &Si2158_prop)+ (void *)api->prop);
  }
  else if (field.datatype == Si2158_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si2158_prop)+ (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si2158_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si2158_prop)+ (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si2158_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned short *) ((field.pField-(void *) &Si2158_prop)+ (void *)api->prop);
  }

  return  *fieldAsInt;
};

char *Si2158_GetEnumFromField     (L1_Si2158_Context *api, Si2158_fieldDicoStruct field)
{
  int intValue;
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &intValue;

  if (field.datatype == Si2158_SIGNED_INT   )
  {
      fieldAsInt= (int *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop);
  }
  else if (field.datatype == Si2158_UNSIGNED_CHAR)
  {
      iTmp = *((unsigned char *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else if (field.datatype == Si2158_SIGNED_CHAR)
  {
      iTmp= *((char *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop));
      fieldAsInt = &iTmp;
  }
  else /* if (field.datatype == Si2158_UNSIGNED_INT) */
  {
      fieldAsInt = (unsigned int *)((field.pField-(void *) &Si2158_prop) + (void *)api->prop);
  }

  return Si2158_GetEnumFromValue(api, field, *fieldAsInt);
};

int   Si2158_SetFieldFromEntry    (L1_Si2158_Context *api, Si2158_fieldDicoStruct field, char *entry)
{
  int *fieldAsInt;
  int iTmp=0;
  fieldAsInt = &iTmp;
  if (Si2158_GetValueFromEntry(api, field, entry, fieldAsInt) == 0) return 0;
  if (field.datatype == Si2158_SIGNED_INT )
  {
    *( (int *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si2158_UNSIGNED_CHAR)
  {
    *( (unsigned char *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop))=iTmp;
  }
  else if (field.datatype == Si2158_SIGNED_CHAR)
  {
    *( (char *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop))=iTmp;
  }
  else /* if (field.datatype == Si2158_UNSIGNED_INT) */
  {
    *( (unsigned int *) ((field.pField-(void *) &Si2158_prop) + (void *)api->prop))=iTmp;
  }

  return 1;
};

void  Si2158_showProperty         (L1_Si2158_Context *api, int propIndex)
{
  int fieldIndex;
  for (fieldIndex=0; fieldIndex<Si2158_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    printf("%s:%s:%s = ", Si2158_featureText[Si2158_propertyDictionary[propIndex].feature], Si2158_propertyDictionary[propIndex].name, Si2158_propertyDictionary[propIndex].field[fieldIndex].name);
    printf("<%s>\n", Si2158_GetEnumFromField(api, Si2158_propertyDictionary[propIndex].field[fieldIndex]));
  }

}

void  Si2158_showPropertyNamed    (L1_Si2158_Context *api, char *property)
{
  int propIndex;

  if ((propIndex = Si2158_PropertyIndex(api, property)) >= 0)
  {
    Si2158_showProperty(api, propIndex);
  }
  else
  {
    printf("Unknown property '%s'\n", property);
  }

}

int   Si2158_showProperties       (L1_Si2158_Context *api, Si2158_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si2158_propertyDictionary)/sizeof(Si2158_propertyInfoStruct);

  printf("\n%s current properties:\n\n", Si2158_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si2158_propertyDictionary[propertyIndex].feature != feature) continue;
    Si2158_showProperty(api, propertyIndex);
  }
  return 0;
}

void  Si2158_setupProperty        (L1_Si2158_Context *api, int propIndex)
{
  #define LMAX 20
  char entry[LMAX];
  char setup_msg[1000];
  int fieldIndex;
  char isRangeType = 1;

  for (fieldIndex=0; fieldIndex<Si2158_propertyDictionary[propIndex].nbFields; fieldIndex++)
  {
    isRangeType = (strcmp_nocase(Si2158_propertyDictionary[propIndex].field[fieldIndex].option->name,"MIN_RANGE") == 0);

    printf("%s:%s:%s = ", Si2158_featureText[Si2158_propertyDictionary[propIndex].feature], Si2158_propertyDictionary[propIndex].name, Si2158_propertyDictionary[propIndex].field[fieldIndex].name);

    if ( isRangeType )
    {
      printf("<%d>\n", Si2158_GetValueFromField(api, Si2158_propertyDictionary[propIndex].field[fieldIndex]));
      Si2158_PropertyFieldRanges(api, propIndex, fieldIndex, setup_msg);
      printf("Range: <%s>  ",setup_msg);
    }
    else
    {
      Si2158_PropertyFieldEnums(api, propIndex, fieldIndex, setup_msg);
      printf("<%s>\n Options: <%s>\n", Si2158_GetEnumFromField(api, Si2158_propertyDictionary[propIndex].field[fieldIndex]), setup_msg);
    }

    fgets(entry,LMAX,stdin);

    if (strlen(entry) > 1)
    {
      entry[strlen(entry)-1]='\0';
      if (!Si2158_SetFieldFromEntry(api, Si2158_propertyDictionary[propIndex].field[fieldIndex], entry))
      {
        printf("Invalid entry!\n");
      }
    }

    if (isRangeType)
      printf("<%d>\n\n", Si2158_GetValueFromField(api, Si2158_propertyDictionary[propIndex].field[fieldIndex]));
    else
      printf("<%s>\n\n", Si2158_GetEnumFromField(api, Si2158_propertyDictionary[propIndex].field[fieldIndex]));
  }
}

int   Si2158_setupProperties      (L1_Si2158_Context *api, Si2158_featureEnum feature)
{
  int propertyIndex;
  int dictSize;

  dictSize=sizeof(Si2158_propertyDictionary)/sizeof(Si2158_propertyInfoStruct);

  printf("\n%s properties:\n\n", Si2158_featureText[feature]);

  for (propertyIndex=0; propertyIndex<dictSize; propertyIndex++)
  {
    if (Si2158_propertyDictionary[propertyIndex].feature != feature) continue;
    Si2158_setupProperty(api, propertyIndex);
  }
  return 0;
}

#endif /* Si2158_COMMAND_LINE_APPLICATION */

/* _property_string_functions_insertion_start */
#ifdef    Si2158_COMMAND_LINE_APPLICATION
int Si2158_showATVProperties       (L1_Si2158_Context *api)
{
  return Si2158_showProperties(api, Si2158_ATV);
};

int Si2158_showCOMMONProperties    (L1_Si2158_Context *api)
{
  return Si2158_showProperties(api, Si2158_COMMON);
};

int Si2158_showDTVProperties       (L1_Si2158_Context *api)
{
  return Si2158_showProperties(api, Si2158_DTV);
};

int Si2158_showTUNERProperties     (L1_Si2158_Context *api)
{
  return Si2158_showProperties(api, Si2158_TUNER);
};

int Si2158_showAllProperties       (L1_Si2158_Context *api)
{
  Si2158_showATVProperties       (api);
  Si2158_showCOMMONProperties    (api);
  Si2158_showDTVProperties       (api);
  Si2158_showTUNERProperties     (api);
  return 0;
};

#endif /* Si2158_COMMAND_LINE_APPLICATION */
void Si2158_setupATVDefaults        (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupATVDefaults       \n");
  api->prop->atv_afc_range.range_khz              =  1000; /* (default  1000) */

  api->prop->atv_agc_speed.if_agc_speed           = Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */

  api->prop->atv_agc_speed_low_rssi.if_agc_speed  = Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  api->prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */
  
	api->prop->atv_artificial_snow.gain             = Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN_AUTO   ; /* (default 'AUTO') */
  	api->prop->atv_artificial_snow.offset           =     0; /* (default     0) */
  
	api->prop->atv_config_if_port.atv_out_type      = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LIF_DIFF_IF1   ; //lgit /* (default 'LIF_DIFF_IF2') */
  api->prop->atv_config_if_port.atv_agc_source    = Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE_AGC1_3DB     ; //lgit /* (default 'INTERNAL') */

  api->prop->atv_ext_agc.min_10mv                 =    50; /* (default    50) */
  api->prop->atv_ext_agc.max_10mv                 =   200; /* (default   200) */

  api->prop->atv_ien.chlien                       = Si2158_ATV_IEN_PROP_CHLIEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->atv_ien.pclien                       = Si2158_ATV_IEN_PROP_PCLIEN_DISABLE ; /* (default 'DISABLE') */

  api->prop->atv_int_sense.chlnegen               = Si2158_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.pclnegen               = Si2158_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE ; /* (default 'DISABLE') */
  api->prop->atv_int_sense.chlposen               = Si2158_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */
  api->prop->atv_int_sense.pclposen               = Si2158_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE  ; /* (default 'ENABLE') */

  api->prop->atv_ir.gear                          =     8; /* (default     8) */
  api->prop->atv_ir.filter                        = Si2158_ATV_IR_PROP_FILTER_CUSTOM_FILTERS ; /* (default 'CUSTOM_FILTERS') */

  api->prop->atv_ircal_drift.step_limit           =    10; /* (default    10) */
  api->prop->atv_ircal_drift.dead_zone            =    25; /* (default    25) */

  api->prop->atv_ircal_mon.expiration_fields      =   120; /* (default   120) */
  api->prop->atv_ircal_mon.disable_threshold      =   160; /* (default   255) */

  api->prop->atv_lif_freq.offset                  =  5000; /* (default  5000) */

  api->prop->atv_lif_out.offset                   =   148; /* (default   148) */
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

void Si2158_setupCOMMONDefaults     (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupCOMMONDefaults    \n");
  api->prop->crystal_trim.xo_cap                  =     8; /* (default     8) */

  api->prop->master_ien.tunien                    = Si2158_MASTER_IEN_PROP_TUNIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.atvien                    = Si2158_MASTER_IEN_PROP_ATVIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.dtvien                    = Si2158_MASTER_IEN_PROP_DTVIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.errien                    = Si2158_MASTER_IEN_PROP_ERRIEN_OFF ; /* (default 'OFF') */
  api->prop->master_ien.ctsien                    = Si2158_MASTER_IEN_PROP_CTSIEN_OFF ; /* (default 'OFF') */

}

void Si2158_setupDTVDefaults        (L1_Si2158_Context *api)
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

  api->prop->dtv_pga_limits.min                   =    0; /* (default    -1) */
  api->prop->dtv_pga_limits.max                   =    56; /* (default    -1) */

  api->prop->dtv_pga_target.pga_target            =     0; /* (default     0) */
  api->prop->dtv_pga_target.override_enable       = Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */

  api->prop->dtv_rf_top.dtv_rf_top                = Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */

  api->prop->dtv_rsq_rssi_threshold.lo            =   -86; /* (default   -80) */
  api->prop->dtv_rsq_rssi_threshold.hi            =     0; /* (default     0) */

  api->prop->dtv_zif_dc_canceller_bw.bandwidth    = Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH_DEFAULT ; /* (default 'DEFAULT') */

}

void Si2158_setupTUNERDefaults      (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupTUNERDefaults     \n");
  api->prop->debug_sample_freq.fs_mhz             =     0; /* (default     0) */

  api->prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */

  api->prop->tuner_ien.tcien                      = Si2158_TUNER_IEN_PROP_TCIEN_ENABLE     ; /* (default 'ENABLE') */
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

void Si2158_setupAllDefaults       (L1_Si2158_Context *api)
{
  Si2158_setupATVDefaults       (api);
  Si2158_setupCOMMONDefaults    (api);
  Si2158_setupDTVDefaults       (api);
  Si2158_setupTUNERDefaults     (api);
}

int Si2158_setupATVProperties       (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupATVProperties       \n");
#ifdef    Si2158_COMMAND_LINE_APPLICATION
  Si2158_setupProperties(api, Si2158_ATV);
#else  /* Si2158_COMMAND_LINE_APPLICATION */
  Si2158_setupATVDefaults(api);
#endif /* Si2158_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2158_setupCOMMONProperties    (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupCOMMONProperties    \n");
#ifdef    Si2158_COMMAND_LINE_APPLICATION
  Si2158_setupProperties(api, Si2158_COMMON);
#else  /* Si2158_COMMAND_LINE_APPLICATION */
  Si2158_setupCOMMONDefaults(api);
#endif /* Si2158_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2158_setupDTVProperties       (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupDTVProperties       \n");
#ifdef    Si2158_COMMAND_LINE_APPLICATION
  Si2158_setupProperties(api, Si2158_DTV);
#else  /* Si2158_COMMAND_LINE_APPLICATION */
  Si2158_setupDTVDefaults(api);
#endif /* Si2158_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2158_setupTUNERProperties     (L1_Si2158_Context *api)
{
  SiTRACE("Si2158_setupTUNERProperties     \n");
#ifdef    Si2158_COMMAND_LINE_APPLICATION
  Si2158_setupProperties(api, Si2158_TUNER);
#else  /* Si2158_COMMAND_LINE_APPLICATION */
  Si2158_setupTUNERDefaults(api);
#endif /* Si2158_COMMAND_LINE_APPLICATION */
  return 0;
}

int Si2158_setupAllProperties  (L1_Si2158_Context *api)
{
  Si2158_setupATVProperties       (api);
  Si2158_setupCOMMONProperties    (api);
  Si2158_setupDTVProperties       (api);
  Si2158_setupTUNERProperties     (api);
  return 0;
}


 /*****************************************************************************************
 NAME: Si2158_downloadATVProperties
  DESCRIPTION: Setup Si2158 ATV properties configuration
  This function will download all the ATV configuration properties.
  The function SetupATVDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2158 Context
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
  Programming Guide Reference:    ATV setup flowchart
******************************************************************************************/
int  Si2158_downloadATVProperties(L1_Si2158_Context *api)
{
  SiTRACE("Si2158_downloadATVProperties     \n");
#if 1  
#ifdef    Si2158_ATV_AFC_RANGE_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_AFC_RANGE_PROP_CODE               ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_AFC_RANGE_PROP */
#ifdef    Si2158_ATV_AGC_SPEED_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_AGC_SPEED_PROP_CODE               ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_AGC_SPEED_PROP */
#ifdef    Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE      ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP */
#endif
#ifdef    Si2158_ATV_ARTIFICIAL_SNOW_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_ARTIFICIAL_SNOW_PROP_CODE         ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_ARTIFICIAL_SNOW_PROP */
#ifdef    Si2158_ATV_CONFIG_IF_PORT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_CONFIG_IF_PORT_PROP */
#ifdef    Si2158_ATV_EXT_AGC_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_EXT_AGC_PROP_CODE                 ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_EXT_AGC_PROP */
#ifdef    Si2158_ATV_IEN_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_IEN_PROP_CODE                     ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_IEN_PROP */
#ifdef    Si2158_ATV_INT_SENSE_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_INT_SENSE_PROP_CODE               ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_INT_SENSE_PROP */
#ifdef    Si2158_ATV_IR_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_IR_PROP_CODE                      ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_IR_PROP */
#ifdef    Si2158_ATV_IRCAL_DRIFT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_IRCAL_DRIFT_PROP_CODE             ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_IRCAL_DRIFT_PROP */
#ifdef    Si2158_ATV_IRCAL_MON_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_IRCAL_MON_PROP_CODE               ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_IRCAL_MON_PROP */
#ifdef    Si2158_ATV_LIF_FREQ_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_FREQ_PROP_CODE                ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_LIF_FREQ_PROP */
#ifdef    Si2158_ATV_LIF_OUT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_LIF_OUT_PROP_CODE                 ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_LIF_OUT_PROP */
#ifdef    Si2158_ATV_MIN_LVL_LOCK_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_MIN_LVL_LOCK_PROP_CODE            ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_MIN_LVL_LOCK_PROP */
#ifdef    Si2158_ATV_PGA_TARGET_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_PGA_TARGET_PROP_CODE              ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_PGA_TARGET_PROP */
#ifdef    Si2158_ATV_RF_TOP_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_RF_TOP_PROP_CODE                  ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_RF_TOP_PROP */
#ifdef    Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si2158_ATV_VIDEO_MODE_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP_CODE              ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_VIDEO_MODE_PROP */
#ifdef    Si2158_ATV_VSNR_CAP_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_ATV_VSNR_CAP_PROP_CODE                ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_ATV_VSNR_CAP_PROP */
return NO_Si2158_ERROR;
}

 /*****************************************************************************************
 NAME: Si2158_downloadCOMMONProperties
  DESCRIPTION: Setup Si2158 COMMON properties configuration
  This function will download all the COMMON configuration properties.
  The function SetupCOMMONDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2158 Context
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
  Programming Guide Reference:    COMMON setup flowchart
******************************************************************************************/
int  Si2158_downloadCOMMONProperties(L1_Si2158_Context *api)
{
  SiTRACE("Si2158_downloadCOMMONProperties                \n");
#ifdef    Si2158_CRYSTAL_TRIM_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_CRYSTAL_TRIM_PROP_CODE                ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_CRYSTAL_TRIM_PROP */
#ifdef    Si2158_MASTER_IEN_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_MASTER_IEN_PROP_CODE                  ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_MASTER_IEN_PROP */
return NO_Si2158_ERROR;
}

 /*****************************************************************************************
 NAME: Si2158_downloadDTVProperties
  DESCRIPTION: Setup Si2158 DTV properties configuration
  This function will download all the DTV configuration properties.
  The function SetupDTVDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2158 Context
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
  Programming Guide Reference:    DTV setup flowchart
******************************************************************************************/
int  Si2158_downloadDTVProperties(L1_Si2158_Context *api)
{
  SiTRACE("Si2158_downloadDTVProperties                  \n");
#ifdef    Si2158_DTV_AGC_FREEZE_INPUT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_FREEZE_INPUT_PROP_CODE        ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_AGC_FREEZE_INPUT_PROP */
#ifdef    Si2158_DTV_AGC_SPEED_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_AGC_SPEED_PROP_CODE               ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_AGC_SPEED_PROP */
#ifdef    Si2158_DTV_CONFIG_IF_PORT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_CONFIG_IF_PORT_PROP */
#ifdef    Si2158_DTV_EXT_AGC_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_EXT_AGC_PROP_CODE                 ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_EXT_AGC_PROP */
#ifdef    Si2158_DTV_FILTER_SELECT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_FILTER_SELECT_PROP_CODE           ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_FILTER_SELECT_PROP */
#ifdef    Si2158_DTV_IEN_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_IEN_PROP_CODE                     ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_IEN_PROP */
#ifdef    Si2158_DTV_INITIAL_AGC_SPEED_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PROP_CODE       ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_INITIAL_AGC_SPEED_PROP */
#ifdef    Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
#ifdef    Si2158_DTV_INTERNAL_ZIF_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_INTERNAL_ZIF_PROP_CODE            ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_INTERNAL_ZIF_PROP */
#ifdef    Si2158_DTV_INT_SENSE_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_INT_SENSE_PROP_CODE               ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_INT_SENSE_PROP */
#ifdef    Si2158_DTV_LIF_FREQ_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_FREQ_PROP_CODE                ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_LIF_FREQ_PROP */
#ifdef    Si2158_DTV_LIF_OUT_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_LIF_OUT_PROP_CODE                 ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_LIF_OUT_PROP */
#ifdef    Si2158_DTV_MODE_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP_CODE                    ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_MODE_PROP */
#ifdef    Si2158_DTV_PGA_LIMITS_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_PGA_LIMITS_PROP_CODE              ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_PGA_LIMITS_PROP */
#ifdef    Si2158_DTV_PGA_TARGET_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_PGA_TARGET_PROP_CODE              ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_PGA_TARGET_PROP */
#ifdef    Si2158_DTV_RF_TOP_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_RF_TOP_PROP_CODE                  ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_RF_TOP_PROP */
#ifdef    Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_CODE     ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP */
return NO_Si2158_ERROR;
}

 /*****************************************************************************************
 NAME: Si2158_downloadTUNERProperties
  DESCRIPTION: Setup Si2158 TUNER properties configuration
  This function will download all the TUNER configuration properties.
  The function SetupTUNERDefaults() should be called before the first call to this function.
  Parameter:  Pointer to Si2158 Context
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
  Programming Guide Reference:    TUNER setup flowchart
******************************************************************************************/
int  Si2158_downloadTUNERProperties(L1_Si2158_Context *api)
{
  SiTRACE("Si2158_downloadTUNERProperties     \n");
#ifdef    Si2158_DEBUG_SAMPLE_FREQ_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_DEBUG_SAMPLE_FREQ_PROP_CODE           ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_DEBUG_SAMPLE_FREQ_PROP */
#ifdef    Si2158_TUNER_BLOCKED_VCO_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_TUNER_BLOCKED_VCO_PROP_CODE           ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_TUNER_BLOCKED_VCO_PROP */
#ifdef    Si2158_TUNER_IEN_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_TUNER_IEN_PROP_CODE                   ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_TUNER_IEN_PROP */
#ifdef    Si2158_TUNER_INT_SENSE_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_TUNER_INT_SENSE_PROP_CODE             ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_TUNER_INT_SENSE_PROP */
#ifdef    Si2158_TUNER_LO_INJECTION_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_TUNER_LO_INJECTION_PROP_CODE          ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_TUNER_LO_INJECTION_PROP */
#ifdef    Si2158_TUNER_RETURN_LOSS_PROP
  if (Si2158_L1_SetProperty2(api, Si2158_TUNER_RETURN_LOSS_PROP_CODE           ) != NO_Si2158_ERROR) {return ERROR_Si2158_SENDING_COMMAND;}
#endif /* Si2158_TUNER_RETURN_LOSS_PROP */
return NO_Si2158_ERROR;
}
int Si2158_downloadAllProperties       (L1_Si2158_Context *api)
{
  Si2158_downloadATVProperties       (api);
  Si2158_downloadCOMMONProperties    (api);
  Si2158_downloadDTVProperties       (api);
  Si2158_downloadTUNERProperties     (api);

  return 0;
}

/* _property_string_functions_insertion_point */





