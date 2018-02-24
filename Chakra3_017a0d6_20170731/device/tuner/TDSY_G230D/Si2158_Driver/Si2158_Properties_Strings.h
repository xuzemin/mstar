/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API properties strings definitions
   FILE: Si2158_Properties_Strings.h
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_0_build_4
   Revision: 0.1
   Date: July 30 2012
   Tag: ROM33_2_0_build_4_LGIT_V0.1
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2158_PROPERTIES_STRINGS_H_
#define   _Si2158_PROPERTIES_STRINGS_H_

#if defined (__cplusplus)
extern "C" {
#endif

#ifdef Si2158_COMMAND_LINE_APPLICATION

extern Si2158_PropObj Si2158_prop;

typedef enum   {
  Si2158_UNSIGNED_CHAR,
  Si2158_SIGNED_CHAR,
  Si2158_UNSIGNED_INT,
  Si2158_SIGNED_INT
} Si2158_datatypeEnum;

typedef struct {
  char *name;
  int   value;
} Si2158_optionStruct;

/* _properties_features_enum_insertion_start */
typedef enum {
  Si2158_ATV,
  Si2158_COMMON,
  Si2158_DTV,
  Si2158_TUNER
} Si2158_featureEnum;
/* _properties_features_enum_insertion_point */

typedef struct {
  char                *name;
  Si2158_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2158_optionStruct *option;
} Si2158_fieldDicoStruct;

typedef struct {
  Si2158_featureEnum      feature;
  char                   *name;
  int                     nbFields;
  Si2158_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2158_propertyInfoStruct;

/* _properties_strings_extern_insertion_start */

extern Si2158_optionStruct    Si2158_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si2158_fieldDicoStruct Si2158_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2158_fieldDicoStruct Si2158_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[];
extern Si2158_optionStruct    Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[];
extern Si2158_fieldDicoStruct Si2158_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_ARTIFICIAL_SNOW_PROP_GAIN[];
extern Si2158_optionStruct    Si2158_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[];
extern Si2158_fieldDicoStruct Si2158_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si2158_optionStruct    Si2158_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE[];
extern Si2158_fieldDicoStruct Si2158_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_EXT_AGC_PROP_MIN_10MV[];
extern Si2158_optionStruct    Si2158_ATV_EXT_AGC_PROP_MAX_10MV[];
extern Si2158_fieldDicoStruct Si2158_ATV_EXT_AGC_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_IEN_PROP_CHLIEN[];
extern Si2158_optionStruct    Si2158_ATV_IEN_PROP_PCLIEN[];
extern Si2158_fieldDicoStruct Si2158_ATV_IEN_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2158_optionStruct    Si2158_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si2158_fieldDicoStruct Si2158_ATV_INT_SENSE_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_IR_PROP_GEAR[];
extern Si2158_optionStruct    Si2158_ATV_IR_PROP_FILTER[];
extern Si2158_fieldDicoStruct Si2158_ATV_IR_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_IRCAL_DRIFT_PROP_STEP_LIMIT[];
extern Si2158_optionStruct    Si2158_ATV_IRCAL_DRIFT_PROP_DEAD_ZONE[];
extern Si2158_fieldDicoStruct Si2158_ATV_IRCAL_DRIFT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_IRCAL_MON_PROP_EXPIRATION_FIELDS[];
extern Si2158_optionStruct    Si2158_ATV_IRCAL_MON_PROP_DISABLE_THRESHOLD[];
extern Si2158_fieldDicoStruct Si2158_ATV_IRCAL_MON_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_LIF_FREQ_PROP_OFFSET[];
extern Si2158_fieldDicoStruct Si2158_ATV_LIF_FREQ_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_LIF_OUT_PROP_OFFSET[];
extern Si2158_optionStruct    Si2158_ATV_LIF_OUT_PROP_AMP[];
extern Si2158_fieldDicoStruct Si2158_ATV_LIF_OUT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_MIN_LVL_LOCK_PROP_THRS[];
extern Si2158_fieldDicoStruct Si2158_ATV_MIN_LVL_LOCK_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2158_optionStruct    Si2158_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2158_fieldDicoStruct Si2158_ATV_PGA_TARGET_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2158_fieldDicoStruct Si2158_ATV_RF_TOP_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2158_optionStruct    Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2158_fieldDicoStruct Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2158_optionStruct    Si2158_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si2158_optionStruct    Si2158_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM[];
extern Si2158_fieldDicoStruct Si2158_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2158_fieldDicoStruct Si2158_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2158_fieldDicoStruct Si2158_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ[];
extern Si2158_fieldDicoStruct Si2158_DEBUG_SAMPLE_FREQ_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si2158_optionStruct    Si2158_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si2158_fieldDicoStruct Si2158_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2158_optionStruct    Si2158_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2158_fieldDicoStruct Si2158_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2158_optionStruct    Si2158_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si2158_fieldDicoStruct Si2158_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2158_optionStruct    Si2158_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2158_fieldDicoStruct Si2158_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_FILTER_SELECT_PROP_FILTER[];
extern Si2158_fieldDicoStruct Si2158_DTV_FILTER_SELECT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_IEN_PROP_CHLIEN[];
extern Si2158_fieldDicoStruct Si2158_DTV_IEN_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2158_optionStruct    Si2158_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2158_fieldDicoStruct Si2158_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2158_fieldDicoStruct Si2158_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2158_optionStruct    Si2158_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2158_fieldDicoStruct Si2158_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2158_optionStruct    Si2158_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2158_fieldDicoStruct Si2158_DTV_INT_SENSE_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2158_fieldDicoStruct Si2158_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2158_optionStruct    Si2158_DTV_LIF_OUT_PROP_AMP[];
extern Si2158_fieldDicoStruct Si2158_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_MODE_PROP_BW[];
extern Si2158_optionStruct    Si2158_DTV_MODE_PROP_MODULATION[];
extern Si2158_optionStruct    Si2158_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2158_fieldDicoStruct Si2158_DTV_MODE_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2158_optionStruct    Si2158_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2158_fieldDicoStruct Si2158_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2158_optionStruct    Si2158_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2158_fieldDicoStruct Si2158_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2158_fieldDicoStruct Si2158_DTV_RF_TOP_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2158_optionStruct    Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2158_fieldDicoStruct Si2158_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH[];
extern Si2158_fieldDicoStruct Si2158_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_MASTER_IEN_PROP_TUNIEN[];
extern Si2158_optionStruct    Si2158_MASTER_IEN_PROP_ATVIEN[];
extern Si2158_optionStruct    Si2158_MASTER_IEN_PROP_DTVIEN[];
extern Si2158_optionStruct    Si2158_MASTER_IEN_PROP_ERRIEN[];
extern Si2158_optionStruct    Si2158_MASTER_IEN_PROP_CTSIEN[];
extern Si2158_fieldDicoStruct Si2158_MASTER_IEN_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2158_fieldDicoStruct Si2158_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_TUNER_IEN_PROP_TCIEN[];
extern Si2158_optionStruct    Si2158_TUNER_IEN_PROP_RSSILIEN[];
extern Si2158_optionStruct    Si2158_TUNER_IEN_PROP_RSSIHIEN[];
extern Si2158_fieldDicoStruct Si2158_TUNER_IEN_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si2158_optionStruct    Si2158_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si2158_fieldDicoStruct Si2158_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2158_optionStruct    Si2158_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2158_optionStruct    Si2158_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2158_fieldDicoStruct Si2158_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2158_optionStruct    Si2158_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si2158_optionStruct    Si2158_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si2158_fieldDicoStruct Si2158_TUNER_RETURN_LOSS_PROP_FIELDS[];

/* _properties_strings_extern_insertion_point */
extern Si2158_propertyInfoStruct Si2158_propertyDictionary[];

int   Si2158_PropertyNames       (L1_Si2158_Context *api, char *msg);
int   Si2158_PropertyIndex       (L1_Si2158_Context *api, char *property);
int   Si2158_PropertyFields      (L1_Si2158_Context *api, int propIndex, char *msg);
int   Si2158_PropertyFieldIndex  (L1_Si2158_Context *api, int propIndex, char *field);
int   Si2158_PropertyFieldEnums  (L1_Si2158_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2158_GetValueFromEntry   (L1_Si2158_Context *api, Si2158_fieldDicoStruct field, char *entry, int *value);
char *Si2158_GetEnumFromValue    (L1_Si2158_Context *api, Si2158_fieldDicoStruct field, int iValue);
char *Si2158_GetEnumFromField    (L1_Si2158_Context *api, Si2158_fieldDicoStruct field);
int   Si2158_SetFieldFromEntry   (L1_Si2158_Context *api, Si2158_fieldDicoStruct field, char *entry);
void  Si2158_showProperty        (L1_Si2158_Context *api, int propertyIndex);
void  Si2158_showPropertyNamed   (L1_Si2158_Context *api, char *property);
int   Si2158_showProperties      (L1_Si2158_Context *api, Si2158_featureEnum feature);
void  Si2158_setupProperty       (L1_Si2158_Context *api, int propIndex);
int   Si2158_setupProperties     (L1_Si2158_Context *api, Si2158_featureEnum feature);

#endif /* Si2158_COMMAND_LINE_APPLICATION */

/* _properties_strings_protos_insertion_start */

#ifdef    Si2158_COMMAND_LINE_APPLICATION
int  Si2158_showATVProperties   (L1_Si2158_Context *api);
int  Si2158_showCOMMONProperties(L1_Si2158_Context *api);
int  Si2158_showDTVProperties   (L1_Si2158_Context *api);
int  Si2158_showTUNERProperties (L1_Si2158_Context *api);


int  Si2158_showAllProperties    (L1_Si2158_Context *api);
#endif /* Si2158_COMMAND_LINE_APPLICATION */
void  Si2158_setupATVDefaults   (L1_Si2158_Context *api);
void  Si2158_setupCOMMONDefaults(L1_Si2158_Context *api);
void  Si2158_setupDTVDefaults   (L1_Si2158_Context *api);
void  Si2158_setupTUNERDefaults (L1_Si2158_Context *api);

void  Si2158_setupAllDefaults   (L1_Si2158_Context *api);

int  Si2158_setupATVProperties   (L1_Si2158_Context *api);
int  Si2158_setupCOMMONProperties(L1_Si2158_Context *api);
int  Si2158_setupDTVProperties   (L1_Si2158_Context *api);
int  Si2158_setupTUNERProperties (L1_Si2158_Context *api);
int  Si2158_setupAllProperties   (L1_Si2158_Context *api);

int  Si2158_downloadATVProperties   (L1_Si2158_Context *api);
int  Si2158_downloadCOMMONProperties(L1_Si2158_Context *api);
int  Si2158_downloadDTVProperties   (L1_Si2158_Context *api);
int  Si2158_downloadTUNERProperties (L1_Si2158_Context *api);
int  Si2158_downloadAllProperties   (L1_Si2158_Context *api);
/* _properties_strings_protos_insertion_point */

#if defined (__cplusplus)
};
#endif

#endif /* _Si2158_PROPERTIES_STRINGS_H_ */





