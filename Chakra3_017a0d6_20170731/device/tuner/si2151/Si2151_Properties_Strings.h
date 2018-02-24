/*************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties strings definitions
   FILE: Si2151_Properties_Strings.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_11
   Revision: 0.4
   Date: December 15 2015
   Tag: ROM61_1_1_build_11_V0.4
  (C) Copyright 2015, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   _Si2151_PROPERTIES_STRINGS_H_
#define   _Si2151_PROPERTIES_STRINGS_H_

#ifdef Si2151_COMMAND_LINE_APPLICATION

extern Si2151_PropObj Si2151_prop;

typedef enum   {
  Si2151_UNSIGNED_CHAR,
  Si2151_SIGNED_CHAR,
  Si2151_UNSIGNED_INT,
  Si2151_SIGNED_INT
} Si2151_datatypeEnum;

typedef struct {
  const char *name;
  int         value;
} Si2151_optionStruct;

typedef enum {
  Si2151_ATV,
  Si2151_COMMON,
  Si2151_DTV,
  Si2151_TUNER
} Si2151_featureEnum;

typedef struct {
  const char          *name;
  Si2151_datatypeEnum  datatype;
  void                *pField;
  int                  nbOptions;
  Si2151_optionStruct *option;
} Si2151_fieldDicoStruct;

typedef struct {
  Si2151_featureEnum      feature;
  const char             *name;
  int                     nbFields;
  Si2151_fieldDicoStruct *field;
  unsigned int            propertyCode;
} Si2151_propertyInfoStruct;


extern Si2151_optionStruct    Si2151_ATV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2151_fieldDicoStruct Si2151_ATV_AGC_SPEED_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED[];
extern Si2151_optionStruct    Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD[];
extern Si2151_fieldDicoStruct Si2151_ATV_AGC_SPEED_LOW_RSSI_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_ARTIFICIAL_SNOW_PROP_GAIN[];
extern Si2151_optionStruct    Si2151_ATV_ARTIFICIAL_SNOW_PROP_PERIOD[];
extern Si2151_fieldDicoStruct Si2151_ATV_ARTIFICIAL_SNOW_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE[];
extern Si2151_fieldDicoStruct Si2151_ATV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_EXT_AGC_PROP_MIN_10MV[];
extern Si2151_optionStruct    Si2151_ATV_EXT_AGC_PROP_MAX_10MV[];
extern Si2151_fieldDicoStruct Si2151_ATV_EXT_AGC_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_HSYNC_OUT_PROP_POLARITY[];
extern Si2151_optionStruct    Si2151_ATV_HSYNC_OUT_PROP_WIDTH[];
extern Si2151_optionStruct    Si2151_ATV_HSYNC_OUT_PROP_OFFSET[];
extern Si2151_fieldDicoStruct Si2151_ATV_HSYNC_OUT_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_LIF_FREQ_PROP_OFFSET[];
extern Si2151_fieldDicoStruct Si2151_ATV_LIF_FREQ_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_LIF_OUT_PROP_OFFSET[];
extern Si2151_optionStruct    Si2151_ATV_LIF_OUT_PROP_AMP[];
extern Si2151_fieldDicoStruct Si2151_ATV_LIF_OUT_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_PGA_LIMITS_PROP_MIN[];
extern Si2151_optionStruct    Si2151_ATV_PGA_LIMITS_PROP_MAX[];
extern Si2151_fieldDicoStruct Si2151_ATV_PGA_LIMITS_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2151_optionStruct    Si2151_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2151_fieldDicoStruct Si2151_ATV_PGA_TARGET_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_RF_TOP_PROP_ATV_RF_TOP[];
extern Si2151_fieldDicoStruct Si2151_ATV_RF_TOP_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2151_fieldDicoStruct Si2151_ATV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_VIDEO_MODE_PROP_VIDEO_SYS[];
extern Si2151_optionStruct    Si2151_ATV_VIDEO_MODE_PROP_INVERT_SPECTRUM[];
extern Si2151_fieldDicoStruct Si2151_ATV_VIDEO_MODE_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP[];
extern Si2151_fieldDicoStruct Si2151_ATV_VSNR_CAP_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_CRYSTAL_TRIM_PROP_XO_CAP[];
extern Si2151_fieldDicoStruct Si2151_CRYSTAL_TRIM_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_AGC_AUTO_FREEZE_PROP_THLD[];
extern Si2151_optionStruct    Si2151_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT[];
extern Si2151_fieldDicoStruct Si2151_DTV_AGC_AUTO_FREEZE_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2151_optionStruct    Si2151_DTV_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2151_fieldDicoStruct Si2151_DTV_AGC_SPEED_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE[];
extern Si2151_fieldDicoStruct Si2151_DTV_CONFIG_IF_PORT_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_EXT_AGC_PROP_MIN_10MV[];
extern Si2151_optionStruct    Si2151_DTV_EXT_AGC_PROP_MAX_10MV[];
extern Si2151_fieldDicoStruct Si2151_DTV_EXT_AGC_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_IF_AGC_SPEED_PROP_ATTACK[];
extern Si2151_optionStruct    Si2151_DTV_IF_AGC_SPEED_PROP_DECAY[];
extern Si2151_fieldDicoStruct Si2151_DTV_IF_AGC_SPEED_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED[];
extern Si2151_optionStruct    Si2151_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM[];
extern Si2151_fieldDicoStruct Si2151_DTV_INITIAL_AGC_SPEED_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD[];
extern Si2151_fieldDicoStruct Si2151_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_ATSC[];
extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_QAM_US[];
extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_DVBT[];
extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_DVBC[];
extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_ISDBT[];
extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_ISDBC[];
extern Si2151_optionStruct    Si2151_DTV_INTERNAL_ZIF_PROP_DTMB[];
extern Si2151_fieldDicoStruct Si2151_DTV_INTERNAL_ZIF_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_LIF_FREQ_PROP_OFFSET[];
extern Si2151_fieldDicoStruct Si2151_DTV_LIF_FREQ_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_LIF_OUT_PROP_OFFSET[];
extern Si2151_optionStruct    Si2151_DTV_LIF_OUT_PROP_AMP[];
extern Si2151_fieldDicoStruct Si2151_DTV_LIF_OUT_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_MODE_PROP_BW[];
extern Si2151_optionStruct    Si2151_DTV_MODE_PROP_MODULATION[];
extern Si2151_optionStruct    Si2151_DTV_MODE_PROP_INVERT_SPECTRUM[];
extern Si2151_fieldDicoStruct Si2151_DTV_MODE_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_PGA_LIMITS_PROP_MIN[];
extern Si2151_optionStruct    Si2151_DTV_PGA_LIMITS_PROP_MAX[];
extern Si2151_fieldDicoStruct Si2151_DTV_PGA_LIMITS_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_PGA_TARGET_PROP_PGA_TARGET[];
extern Si2151_optionStruct    Si2151_DTV_PGA_TARGET_PROP_OVERRIDE_ENABLE[];
extern Si2151_fieldDicoStruct Si2151_DTV_PGA_TARGET_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_RF_AGC_SPEED_PROP_ATTACK[];
extern Si2151_optionStruct    Si2151_DTV_RF_AGC_SPEED_PROP_DECAY[];
extern Si2151_fieldDicoStruct Si2151_DTV_RF_AGC_SPEED_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_RF_TOP_PROP_DTV_RF_TOP[];
extern Si2151_fieldDicoStruct Si2151_DTV_RF_TOP_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_LO[];
extern Si2151_fieldDicoStruct Si2151_DTV_RSQ_RSSI_THRESHOLD_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_DTV_WB_AGC_SPEED_PROP_ATTACK[];
extern Si2151_optionStruct    Si2151_DTV_WB_AGC_SPEED_PROP_DECAY[];
extern Si2151_fieldDicoStruct Si2151_DTV_WB_AGC_SPEED_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_BLOCKED_VCO_PROP_VCO_CODE[];
extern Si2151_fieldDicoStruct Si2151_TUNER_BLOCKED_VCO_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_BLOCKED_VCO2_PROP_VCO_CODE[];
extern Si2151_fieldDicoStruct Si2151_TUNER_BLOCKED_VCO2_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_BLOCKED_VCO3_PROP_VCO_CODE[];
extern Si2151_fieldDicoStruct Si2151_TUNER_BLOCKED_VCO3_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_LO_INJECTION_PROP_BAND_1[];
extern Si2151_optionStruct    Si2151_TUNER_LO_INJECTION_PROP_BAND_2[];
extern Si2151_optionStruct    Si2151_TUNER_LO_INJECTION_PROP_BAND_3[];
extern Si2151_fieldDicoStruct Si2151_TUNER_LO_INJECTION_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_PROP_CONFIG[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_PROP_MODE[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_PROP_RESERVED[];
extern Si2151_fieldDicoStruct Si2151_TUNER_RETURN_LOSS_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY[];
extern Si2151_fieldDicoStruct Si2151_TUNER_RETURN_LOSS_OPTIMIZE_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW[];
extern Si2151_optionStruct    Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY[];
extern Si2151_fieldDicoStruct Si2151_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET[];
extern Si2151_fieldDicoStruct Si2151_TUNER_TF1_BOUNDARY_OFFSET_PROP_FIELDS[];

extern Si2151_optionStruct    Si2151_XOUT_PROP_AMP[];
extern Si2151_fieldDicoStruct Si2151_XOUT_PROP_FIELDS[];

extern Si2151_propertyInfoStruct Si2151_propertyDictionary[];

int   Si2151_PropertyNames       (L1_Si2151_Context *api, char *msg);
int   Si2151_PropertyIndex       (L1_Si2151_Context *api, const char *property);
int   Si2151_PropertyFields      (L1_Si2151_Context *api, int propIndex, char *msg);
int   Si2151_PropertyFieldIndex  (L1_Si2151_Context *api, int propIndex, char *field);
int   Si2151_PropertyFieldEnums  (L1_Si2151_Context *api, int propIndex, int fieldIndex, char *msg);
int   Si2151_GetValueFromEntry   (L1_Si2151_Context *api, Si2151_fieldDicoStruct field, char *entry, int *value);
char *Si2151_GetEnumFromValue    (L1_Si2151_Context *api, Si2151_fieldDicoStruct field, int iValue);
char *Si2151_GetEnumFromField    (L1_Si2151_Context *api, Si2151_fieldDicoStruct field);
int   Si2151_SetFieldFromEntry   (L1_Si2151_Context *api, Si2151_fieldDicoStruct field, char *entry);
void  Si2151_showProperty        (L1_Si2151_Context *api, int propertyIndex);
void  Si2151_showPropertyNamed   (L1_Si2151_Context *api, char *property);
int   Si2151_showProperties      (L1_Si2151_Context *api, Si2151_featureEnum feature);
void  Si2151_setupProperty       (L1_Si2151_Context *api, int propIndex);
int   Si2151_setupProperties     (L1_Si2151_Context *api, Si2151_featureEnum feature);

#endif /* Si2151_COMMAND_LINE_APPLICATION */


int  Si2151_setupATVProperties   (L1_Si2151_Context *api);
int  Si2151_setupCOMMONProperties(L1_Si2151_Context *api);
int  Si2151_setupDTVProperties   (L1_Si2151_Context *api);
int  Si2151_setupTUNERProperties (L1_Si2151_Context *api);
int  Si2151_setupAllProperties   (L1_Si2151_Context *api);

#endif /* _Si2151_PROPERTIES_STRINGS_H_ */







