/*************************************************************************************
                  Silicon Laboratories Broadcast Si2157 Layer 1 API
   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.
   API properties strings definitions
   FILE: Si2157_Properties_Strings.h
   Supported IC : Si2157
   Compiled for ROM 50 firmware 3_4_build_4
   Revision: 0.1
   Date: November 06 2013
   Tag: ROM50_3_4_build_4_V0.1
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2157_PROPERTIES_STRINGS_H_
#define   _Si2157_PROPERTIES_STRINGS_H_

#ifdef Si2157_COMMAND_LINE_APPLICATION

extern Si2157_PropObj Si2157_prop;

typedef enum   {
  Si2157_UNSIGNED_CHAR,
  Si2157_SIGNED_CHAR,
  Si2157_UNSIGNED_INT,
  Si2157_SIGNED_INT
} Si2157_datatypeEnum;

typedef struct {
  const char *name;
  int         value;
} Si2157_optionStruct;

typedef enum {
  Si2157_ATV,
  Si2157_COMMON,
  Si2157_DTV,
  Si2157_TUNER
} Si2157_featureEnum;

typedef struct {
  const char          *name;
  Si2157_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2157_optionStruct *option;
} Si2157_fieldDicoStruct;

typedef struct {
  Si2157_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si2157_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2157_propertyInfoStruct;


extern Si2157_optionStruct    Si2157_ATV_AFC_RANGE_PROP_RANGE_KHZ[];
extern Si2157_fieldDicoStruct Si2157_ATV_AFC_RANGE_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2157_fieldDicoStruct Si2157_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[];
extern Si2157_optionStruct    Si2157_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[];
extern Si2157_fieldDicoStruct Si2157_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_ARTIFICIAL_SNOW_PROP_GAIN[];
extern Si2157_optionStruct    Si2157_ATV_ARTIFICIAL_SNOW_PROP_PERIOD[];
extern Si2157_optionStruct    Si2157_ATV_ARTIFICIAL_SNOW_PROP_OFFSET[];
extern Si2157_fieldDicoStruct Si2157_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si2157_optionStruct    Si2157_ATV_CONFIG_IF_PORT_PROP_ATV_AGC_SOURCE[];
extern Si2157_fieldDicoStruct Si2157_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_EXT_AGC_PROP_MIN_10MV[];
extern Si2157_optionStruct    Si2157_ATV_EXT_AGC_PROP_MAX_10MV[];
extern Si2157_fieldDicoStruct Si2157_ATV_EXT_AGC_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_HSYNC_OUT_PROP_GPIO_SEL[];
extern Si2157_optionStruct    Si2157_ATV_HSYNC_OUT_PROP_WIDTH[];
extern Si2157_optionStruct    Si2157_ATV_HSYNC_OUT_PROP_OFFSET[];
extern Si2157_fieldDicoStruct Si2157_ATV_HSYNC_OUT_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_IEN_PROP_CHLIEN[];
extern Si2157_optionStruct    Si2157_ATV_IEN_PROP_PCLIEN[];
extern Si2157_fieldDicoStruct Si2157_ATV_IEN_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2157_optionStruct    Si2157_ATV_INT_SENSE_PROP_PCLNEGEN[];
extern Si2157_optionStruct    Si2157_ATV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2157_optionStruct    Si2157_ATV_INT_SENSE_PROP_PCLPOSEN[];
extern Si2157_fieldDicoStruct Si2157_ATV_INT_SENSE_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_LIF_FREQ_PROP_OFFSET[];
extern Si2157_fieldDicoStruct Si2157_ATV_LIF_FREQ_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_LIF_OUT_PROP_OFFSET[];
extern Si2157_optionStruct    Si2157_ATV_LIF_OUT_PROP_AMP[];
extern Si2157_fieldDicoStruct Si2157_ATV_LIF_OUT_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2157_optionStruct    Si2157_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2157_fieldDicoStruct Si2157_ATV_PGA_TARGET_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2157_fieldDicoStruct Si2157_ATV_RF_TOP_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2157_optionStruct    Si2157_ATV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2157_fieldDicoStruct Si2157_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2157_optionStruct    Si2157_ATV_VIDEO_MODE_PROP_COLOR[];
extern Si2157_optionStruct    Si2157_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM[];
extern Si2157_fieldDicoStruct Si2157_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2157_fieldDicoStruct Si2157_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2157_fieldDicoStruct Si2157_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_AGC_FREEZE_INPUT_PROP_LEVEL[];
extern Si2157_optionStruct    Si2157_DTV_AGC_FREEZE_INPUT_PROP_PIN[];
extern Si2157_fieldDicoStruct Si2157_DTV_AGC_FREEZE_INPUT_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2157_optionStruct    Si2157_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2157_fieldDicoStruct Si2157_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2157_optionStruct    Si2157_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE[];
extern Si2157_fieldDicoStruct Si2157_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2157_optionStruct    Si2157_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2157_fieldDicoStruct Si2157_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_IEN_PROP_CHLIEN[];
extern Si2157_fieldDicoStruct Si2157_DTV_IEN_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2157_optionStruct    Si2157_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2157_fieldDicoStruct Si2157_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2157_fieldDicoStruct Si2157_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2157_optionStruct    Si2157_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2157_fieldDicoStruct Si2157_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_INT_SENSE_PROP_CHLNEGEN[];
extern Si2157_optionStruct    Si2157_DTV_INT_SENSE_PROP_CHLPOSEN[];
extern Si2157_fieldDicoStruct Si2157_DTV_INT_SENSE_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2157_fieldDicoStruct Si2157_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2157_optionStruct    Si2157_DTV_LIF_OUT_PROP_AMP[];
extern Si2157_fieldDicoStruct Si2157_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_MODE_PROP_BW[];
extern Si2157_optionStruct    Si2157_DTV_MODE_PROP_MODULATION[];
extern Si2157_optionStruct    Si2157_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2157_fieldDicoStruct Si2157_DTV_MODE_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2157_optionStruct    Si2157_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2157_fieldDicoStruct Si2157_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2157_optionStruct    Si2157_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2157_fieldDicoStruct Si2157_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2157_fieldDicoStruct Si2157_DTV_RF_TOP_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2157_optionStruct    Si2157_DTV_RSQ_RSSI_THRESHOLD_PROP_HI[];
extern Si2157_fieldDicoStruct Si2157_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_DTV_ZIF_DC_CANCELLER_BW_PROP_BANDWIDTH[];
extern Si2157_fieldDicoStruct Si2157_DTV_ZIF_DC_CANCELLER_BW_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_MASTER_IEN_PROP_TUNIEN[];
extern Si2157_optionStruct    Si2157_MASTER_IEN_PROP_ATVIEN[];
extern Si2157_optionStruct    Si2157_MASTER_IEN_PROP_DTVIEN[];
extern Si2157_optionStruct    Si2157_MASTER_IEN_PROP_ERRIEN[];
extern Si2157_optionStruct    Si2157_MASTER_IEN_PROP_CTSIEN[];
extern Si2157_fieldDicoStruct Si2157_MASTER_IEN_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2157_fieldDicoStruct Si2157_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_TUNER_IEN_PROP_TCIEN[];
extern Si2157_optionStruct    Si2157_TUNER_IEN_PROP_RSSILIEN[];
extern Si2157_optionStruct    Si2157_TUNER_IEN_PROP_RSSIHIEN[];
extern Si2157_fieldDicoStruct Si2157_TUNER_IEN_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_TUNER_INT_SENSE_PROP_TCNEGEN[];
extern Si2157_optionStruct    Si2157_TUNER_INT_SENSE_PROP_RSSILNEGEN[];
extern Si2157_optionStruct    Si2157_TUNER_INT_SENSE_PROP_RSSIHNEGEN[];
extern Si2157_optionStruct    Si2157_TUNER_INT_SENSE_PROP_TCPOSEN[];
extern Si2157_optionStruct    Si2157_TUNER_INT_SENSE_PROP_RSSILPOSEN[];
extern Si2157_optionStruct    Si2157_TUNER_INT_SENSE_PROP_RSSIHPOSEN[];
extern Si2157_fieldDicoStruct Si2157_TUNER_INT_SENSE_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2157_optionStruct    Si2157_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2157_optionStruct    Si2157_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2157_fieldDicoStruct Si2157_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si2157_optionStruct    Si2157_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si2157_fieldDicoStruct Si2157_TUNER_RETURN_LOSS_PROP_FIELDS[];

extern Si2157_optionStruct    Si2157_XOUT_PROP_AMP[];
extern Si2157_fieldDicoStruct Si2157_XOUT_PROP_FIELDS[];

extern Si2157_propertyInfoStruct Si2157_propertyDictionary[];

int   Si2157_PropertyNames       (L1_Si2157_Context *api, char *msg);
int   Si2157_PropertyIndex       (L1_Si2157_Context *api, const char *property);
int   Si2157_PropertyFields      (L1_Si2157_Context *api, int propIndex, char *msg);
int   Si2157_PropertyFieldIndex  (L1_Si2157_Context *api, int propIndex, char *field);
int   Si2157_PropertyFieldEnums  (L1_Si2157_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2157_GetValueFromEntry   (L1_Si2157_Context *api, Si2157_fieldDicoStruct field, char *entry, int *value);
char *Si2157_GetEnumFromValue    (L1_Si2157_Context *api, Si2157_fieldDicoStruct field, int iValue);
char *Si2157_GetEnumFromField    (L1_Si2157_Context *api, Si2157_fieldDicoStruct field);
int   Si2157_SetFieldFromEntry   (L1_Si2157_Context *api, Si2157_fieldDicoStruct field, char *entry);
void  Si2157_showProperty        (L1_Si2157_Context *api, int propertyIndex);
void  Si2157_showPropertyNamed   (L1_Si2157_Context *api, char *property);
int   Si2157_showProperties      (L1_Si2157_Context *api, Si2157_featureEnum feature);
void  Si2157_setupProperty       (L1_Si2157_Context *api, int propIndex);
int   Si2157_setupProperties     (L1_Si2157_Context *api, Si2157_featureEnum feature);

#endif /* Si2157_COMMAND_LINE_APPLICATION */

int  Si2157_setupATVProperties   (L1_Si2157_Context *api);
int  Si2157_setupCOMMONProperties(L1_Si2157_Context *api);
int  Si2157_setupDTVProperties   (L1_Si2157_Context *api);
int  Si2157_setupTUNERProperties (L1_Si2157_Context *api);
int  Si2157_setupAllProperties   (L1_Si2157_Context *api);


#endif /* _Si2157_PROPERTIES_STRINGS_H_ */





