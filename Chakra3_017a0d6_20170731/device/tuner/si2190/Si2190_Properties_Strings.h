/*************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 1 API
   API properties strings definitions
   FILE: Si2190_Properties_Strings.h
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Date: August 13 2012
   Tag: ROM40_0_A_build_10_V0.1
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2190_PROPERTIES_STRINGS_H_
#define   _Si2190_PROPERTIES_STRINGS_H_

#ifdef Si2190_COMMAND_LINE_APPLICATION

extern Si2190_PropObj Si2190_prop;

typedef enum   {
  Si2190_UNSIGNED_CHAR,
  Si2190_SIGNED_CHAR,
  Si2190_UNSIGNED_INT,
  Si2190_SIGNED_INT
} Si2190_datatypeEnum;

typedef struct {
  const char *name;
  int   value;
} Si2190_optionStruct;

/* _properties_features_enum_insertion_start */
typedef enum {
  Si2190_ATV,
  Si2190_COMMON,
  Si2190_DTV,
  Si2190_TUNER
} Si2190_featureEnum;
/* _properties_features_enum_insertion_point */

typedef struct {
  const char          *name;
  Si2190_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2190_optionStruct *option;
} Si2190_fieldDicoStruct;

typedef struct {
  Si2190_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si2190_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2190_propertyInfoStruct;

/* _properties_strings_extern_insertion_start */

extern Si2190_optionStruct    Si2190_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si2190_fieldDicoStruct Si2190_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2190_fieldDicoStruct Si2190_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[];
extern Si2190_optionStruct    Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[];
extern Si2190_fieldDicoStruct Si2190_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_ARTIFICIAL_SNOW_PROP_GAIN[];
extern Si2190_optionStruct    Si2190_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[];
extern Si2190_fieldDicoStruct Si2190_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS[];
extern Si2190_optionStruct    Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW[];
extern Si2190_fieldDicoStruct Si2190_ATV_AUDIO_MODE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si2190_fieldDicoStruct Si2190_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_CVBS_OUT_PROP_OFFSET[];
extern Si2190_optionStruct    Si2190_ATV_CVBS_OUT_PROP_AMP[];
extern Si2190_fieldDicoStruct Si2190_ATV_CVBS_OUT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_CVBS_OUT_FINE_PROP_OFFSET[];
extern Si2190_optionStruct    Si2190_ATV_CVBS_OUT_FINE_PROP_AMP[];
extern Si2190_fieldDicoStruct Si2190_ATV_CVBS_OUT_FINE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_IEN_PROP_CHLIEN[];
extern Si2190_optionStruct    Si2190_ATV_IEN_PROP_PCLIEN[];
extern Si2190_optionStruct    Si2190_ATV_IEN_PROP_DLIEN[];
extern Si2190_optionStruct    Si2190_ATV_IEN_PROP_SNRLIEN[];
extern Si2190_optionStruct    Si2190_ATV_IEN_PROP_SNRHIEN[];
extern Si2190_fieldDicoStruct Si2190_ATV_IEN_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_DLNEGEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRLNEGEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRHNEGEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_DLPOSEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRLPOSEN[];
extern Si2190_optionStruct    Si2190_ATV_INT_SENSE_PROP_SNRHPOSEN[];
extern Si2190_fieldDicoStruct Si2190_ATV_INT_SENSE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2190_optionStruct    Si2190_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2190_fieldDicoStruct Si2190_ATV_PGA_TARGET_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2190_fieldDicoStruct Si2190_ATV_RF_TOP_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2190_optionStruct    Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2190_fieldDicoStruct Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_LO[];
extern Si2190_optionStruct    Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_HI[];
extern Si2190_fieldDicoStruct Si2190_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_SIF_OUT_PROP_OFFSET[];
extern Si2190_optionStruct    Si2190_ATV_SIF_OUT_PROP_AMP[];
extern Si2190_fieldDicoStruct Si2190_ATV_SIF_OUT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN[];
extern Si2190_optionStruct    Si2190_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN[];
extern Si2190_fieldDicoStruct Si2190_ATV_SOUND_AGC_LIMIT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L[];
extern Si2190_optionStruct    Si2190_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS[];
extern Si2190_fieldDicoStruct Si2190_ATV_SOUND_AGC_SPEED_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_VIDEO_EQUALIZER_PROP_SLOPE[];
extern Si2190_fieldDicoStruct Si2190_ATV_VIDEO_EQUALIZER_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2190_optionStruct    Si2190_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si2190_optionStruct    Si2190_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL[];
extern Si2190_fieldDicoStruct Si2190_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2190_fieldDicoStruct Si2190_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2190_fieldDicoStruct Si2190_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DEBUG_SAMPLE_FREQ_PROP_FS_MHZ[];
extern Si2190_fieldDicoStruct Si2190_DEBUG_SAMPLE_FREQ_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si2190_optionStruct    Si2190_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si2190_fieldDicoStruct Si2190_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2190_optionStruct    Si2190_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2190_fieldDicoStruct Si2190_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2190_optionStruct    Si2190_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si2190_fieldDicoStruct Si2190_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2190_optionStruct    Si2190_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2190_fieldDicoStruct Si2190_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_FILTER_SELECT_PROP_FILTER[];
extern Si2190_fieldDicoStruct Si2190_DTV_FILTER_SELECT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_IEN_PROP_CHLIEN[];
extern Si2190_fieldDicoStruct Si2190_DTV_IEN_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2190_optionStruct    Si2190_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2190_fieldDicoStruct Si2190_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2190_fieldDicoStruct Si2190_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2190_optionStruct    Si2190_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2190_fieldDicoStruct Si2190_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2190_optionStruct    Si2190_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2190_fieldDicoStruct Si2190_DTV_INT_SENSE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2190_fieldDicoStruct Si2190_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2190_optionStruct    Si2190_DTV_LIF_OUT_PROP_AMP[];
extern Si2190_fieldDicoStruct Si2190_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_MODE_PROP_BW[];
extern Si2190_optionStruct    Si2190_DTV_MODE_PROP_MODULATION[];
extern Si2190_optionStruct    Si2190_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2190_fieldDicoStruct Si2190_DTV_MODE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2190_optionStruct    Si2190_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2190_fieldDicoStruct Si2190_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2190_optionStruct    Si2190_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2190_fieldDicoStruct Si2190_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2190_fieldDicoStruct Si2190_DTV_RF_TOP_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2190_optionStruct    Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2190_fieldDicoStruct Si2190_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH[];
extern Si2190_fieldDicoStruct Si2190_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_MASTER_IEN_PROP_TUNIEN[];
extern Si2190_optionStruct    Si2190_MASTER_IEN_PROP_ATVIEN[];
extern Si2190_optionStruct    Si2190_MASTER_IEN_PROP_DTVIEN[];
extern Si2190_optionStruct    Si2190_MASTER_IEN_PROP_ERRIEN[];
extern Si2190_optionStruct    Si2190_MASTER_IEN_PROP_CTSIEN[];
extern Si2190_fieldDicoStruct Si2190_MASTER_IEN_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2190_fieldDicoStruct Si2190_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_TUNER_IEN_PROP_TCIEN[];
extern Si2190_optionStruct    Si2190_TUNER_IEN_PROP_RSSILIEN[];
extern Si2190_optionStruct    Si2190_TUNER_IEN_PROP_RSSIHIEN[];
extern Si2190_fieldDicoStruct Si2190_TUNER_IEN_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si2190_optionStruct    Si2190_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si2190_fieldDicoStruct Si2190_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2190_optionStruct    Si2190_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2190_optionStruct    Si2190_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2190_fieldDicoStruct Si2190_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2190_optionStruct    Si2190_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si2190_optionStruct    Si2190_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si2190_fieldDicoStruct Si2190_TUNER_RETURN_LOSS_PROP_FIELDS[];

/* _properties_strings_extern_insertion_point */
extern Si2190_propertyInfoStruct Si2190_propertyDictionary[];

int   Si2190_PropertyNames       (L1_Si2190_Context *api, char *msg);
int   Si2190_PropertyIndex       (L1_Si2190_Context *api, const char *property);
int   Si2190_PropertyFields      (L1_Si2190_Context *api, int propIndex, char *msg);
int   Si2190_PropertyFieldIndex  (L1_Si2190_Context *api, int propIndex, char *field);
int   Si2190_PropertyFieldEnums  (L1_Si2190_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2190_GetValueFromEntry   (L1_Si2190_Context *api, Si2190_fieldDicoStruct field, char *entry, int *value);
char *Si2190_GetEnumFromValue    (L1_Si2190_Context *api, Si2190_fieldDicoStruct field, int iValue);
char *Si2190_GetEnumFromField    (L1_Si2190_Context *api, Si2190_fieldDicoStruct field);
int   Si2190_SetFieldFromEntry   (L1_Si2190_Context *api, Si2190_fieldDicoStruct field, char *entry);
void  Si2190_showProperty        (L1_Si2190_Context *api, int propertyIndex);
void  Si2190_showPropertyNamed   (L1_Si2190_Context *api, char *property);
int   Si2190_showProperties      (L1_Si2190_Context *api, Si2190_featureEnum feature);
void  Si2190_setupProperty       (L1_Si2190_Context *api, int propIndex);
int   Si2190_setupProperties     (L1_Si2190_Context *api, Si2190_featureEnum feature);

#endif /* Si2190_COMMAND_LINE_APPLICATION */

/* _properties_strings_protos_insertion_start */

#ifdef    Si2190_COMMAND_LINE_APPLICATION
int  Si2190_showATVProperties   (L1_Si2190_Context *api);
int  Si2190_showCOMMONProperties(L1_Si2190_Context *api);
int  Si2190_showDTVProperties   (L1_Si2190_Context *api);
int  Si2190_showTUNERProperties (L1_Si2190_Context *api);


int  Si2190_showAllProperties    (L1_Si2190_Context *api);
#endif /* Si2190_COMMAND_LINE_APPLICATION */
void  Si2190_setupATVDefaults   (L1_Si2190_Context *api);
void  Si2190_setupCOMMONDefaults(L1_Si2190_Context *api);
void  Si2190_setupDTVDefaults   (L1_Si2190_Context *api);
void  Si2190_setupTUNERDefaults (L1_Si2190_Context *api);

void  Si2190_setupAllDefaults   (L1_Si2190_Context *api);

int  Si2190_setupATVProperties   (L1_Si2190_Context *api);
int  Si2190_setupCOMMONProperties(L1_Si2190_Context *api);
int  Si2190_setupDTVProperties   (L1_Si2190_Context *api);
int  Si2190_setupTUNERProperties (L1_Si2190_Context *api);
int  Si2190_setupAllProperties   (L1_Si2190_Context *api);

int  Si2190_downloadATVProperties   (L1_Si2190_Context *api);
int  Si2190_downloadCOMMONProperties(L1_Si2190_Context *api);
int  Si2190_downloadDTVProperties   (L1_Si2190_Context *api);
int  Si2190_downloadTUNERProperties (L1_Si2190_Context *api);
int  Si2190_downloadAllProperties   (L1_Si2190_Context *api);
/* _properties_strings_protos_insertion_point */

#endif /* _Si2190_PROPERTIES_STRINGS_H_ */





