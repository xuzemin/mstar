/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties strings definitions
   FILE: Si21XXC_Properties_Strings.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si21XXC_PROPERTIES_STRINGS_H_
#define   _Si21XXC_PROPERTIES_STRINGS_H_

#ifdef __cplusplus
extern "C"{
#endif
#ifdef Si21XXC_COMMAND_LINE_APPLICATION

extern Si21XXC_PropObj Si21XXC_prop;

typedef enum   {
  Si21XXC_UNSIGNED_CHAR,
  Si21XXC_SIGNED_CHAR,
  Si21XXC_UNSIGNED_INT,
  Si21XXC_SIGNED_INT
} Si21XXC_datatypeEnum;

typedef struct {
  const char *name;
  int   value;
} Si21XXC_optionStruct;

typedef enum {
  Si21XXC_ATV,
  Si21XXC_COMMON,
  Si21XXC_DTV,
  Si21XXC_TUNER
} Si21XXC_featureEnum;

typedef struct {
  const char          *name;
  Si21XXC_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si21XXC_optionStruct *option;
} Si21XXC_fieldDicoStruct;

typedef struct {
  Si21XXC_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si21XXC_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si21XXC_propertyInfoStruct;


extern Si21XXC_optionStruct    Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[];
extern Si21XXC_optionStruct    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND[];
extern Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD[];
extern Si21XXC_optionStruct    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS[];
extern Si21XXC_optionStruct    Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_AUDIO_MODE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD[];
extern Si21XXC_optionStruct    Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE[];
extern Si21XXC_optionStruct    Si2190B_ATV_CVBS_ATTENUATION_PROP_BW[];
extern Si21XXC_fieldDicoStruct Si2190B_ATV_CVBS_ATTENUATION_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_PROP_OFFSET[];
extern Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_PROP_AMP[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_CVBS_OUT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET[];
extern Si21XXC_optionStruct    Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_CVBS_OUT_FINE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_CHLIEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_PCLIEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_DLIEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_SNRLIEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_IEN_PROP_SNRHIEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_IEN_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_INT_SENSE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si21XXC_optionStruct    Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_PGA_TARGET_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_RF_TOP_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si21XXC_optionStruct    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO[];
extern Si21XXC_optionStruct    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_SIF_OUT_PROP_OFFSET[];
extern Si21XXC_optionStruct    Si21XXC_ATV_SIF_OUT_PROP_AMP[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_SIF_OUT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN[];
extern Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L[];
extern Si21XXC_optionStruct    Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_SOUND_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_VIDEO_EQUALIZER_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si21XXC_optionStruct    Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si21XXC_fieldDicoStruct Si21XXC_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si21XXC_fieldDicoStruct Si21XXC_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD[];
extern Si21XXC_optionStruct    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si21XXC_optionStruct    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si21XXC_optionStruct    Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si21XXC_optionStruct    Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si21XXC_optionStruct    Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_EXT_AGC_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_IEN_PROP_CHLIEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_IEN_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK[];
extern Si21XXC_optionStruct    Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_IF_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_INT_SENSE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_LIF_OUT_PROP_OFFSET[];
extern Si21XXC_optionStruct    Si21XXC_DTV_LIF_OUT_PROP_AMP[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_LIF_OUT_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_MODE_PROP_BW[];
extern Si21XXC_optionStruct    Si21XXC_DTV_MODE_PROP_MODULATION[];
extern Si21XXC_optionStruct    Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_MODE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK[];
extern Si21XXC_optionStruct    Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_RF_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_RF_TOP_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si21XXC_optionStruct    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK[];
extern Si21XXC_optionStruct    Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY[];
extern Si21XXC_fieldDicoStruct Si21XXC_DTV_WB_AGC_SPEED_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_TUNIEN[];
extern Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_ATVIEN[];
extern Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_DTVIEN[];
extern Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_ERRIEN[];
extern Si21XXC_optionStruct    Si21XXC_MASTER_IEN_PROP_CTSIEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_MASTER_IEN_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si21XXC_fieldDicoStruct Si21XXC_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_TUNER_IEN_PROP_TCIEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_IEN_PROP_RSSILIEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_IEN_PROP_RSSIHIEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_TUNER_IEN_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si21XXC_fieldDicoStruct Si21XXC_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si21XXC_fieldDicoStruct Si21XXC_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si21XXC_optionStruct    Si21XXC_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si21XXC_fieldDicoStruct Si21XXC_TUNER_RETURN_LOSS_PROP_FIELDS[];
extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD[];
extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG[];
extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY[];
extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY[];
extern Si21XXC_fieldDicoStruct Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD[];
extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW[];
extern Si21XXC_optionStruct    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY[];
extern Si21XXC_fieldDicoStruct Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET[];
extern Si21XXC_fieldDicoStruct Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS[];
extern Si21XXC_fieldDicoStruct Si2190B_WIDE_BAND_ATT_THRS_PROP_FIELDS[];

extern Si21XXC_optionStruct    Si21XXC_XOUT_PROP_AMP[];
extern Si21XXC_fieldDicoStruct Si21XXC_XOUT_PROP_FIELDS[];

extern Si21XXC_propertyInfoStruct Si21XXC_propertyDictionary[];

int   Si21XXC_PropertyNames       (L1_Si21XXC_Context *api, char *msg);
int   Si21XXC_PropertyIndex       (L1_Si21XXC_Context *api, const char *property);
int   Si21XXC_PropertyFields      (L1_Si21XXC_Context *api, int propIndex, char *msg);
int   Si21XXC_PropertyFieldIndex  (L1_Si21XXC_Context *api, int propIndex, char *field);
int   Si21XXC_PropertyFieldEnums  (L1_Si21XXC_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si21XXC_GetValueFromEntry   (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field, char *entry, int *value);
char *Si21XXC_GetEnumFromValue    (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field, int iValue);
char *Si21XXC_GetEnumFromField    (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field);
int   Si21XXC_SetFieldFromEntry   (L1_Si21XXC_Context *api, Si21XXC_fieldDicoStruct field, char *entry);
void  Si21XXC_showProperty        (L1_Si21XXC_Context *api, int propertyIndex);
void  Si21XXC_showPropertyNamed   (L1_Si21XXC_Context *api, char *property);
int   Si21XXC_showProperties      (L1_Si21XXC_Context *api, Si21XXC_featureEnum feature);
void  Si21XXC_setupProperty       (L1_Si21XXC_Context *api, int propIndex);
int   Si21XXC_setupProperties     (L1_Si21XXC_Context *api, Si21XXC_featureEnum feature);

#endif /* Si21XXC_COMMAND_LINE_APPLICATION */


int  Si21XXC_setupATVProperties   (L1_Si21XXC_Context *api);
int  Si21XXC_setupCOMMONProperties(L1_Si21XXC_Context *api);
int  Si21XXC_setupDTVProperties   (L1_Si21XXC_Context *api);
int  Si21XXC_setupTUNERProperties (L1_Si21XXC_Context *api);
int  Si21XXC_setupAllProperties   (L1_Si21XXC_Context *api);

/* _properties_strings_protos_insertion_point */
#ifdef __cplusplus
}
#endif
#endif /* _Si21XXC_PROPERTIES_STRINGS_H_ */







