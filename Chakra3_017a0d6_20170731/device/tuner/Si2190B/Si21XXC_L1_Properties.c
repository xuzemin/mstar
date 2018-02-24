/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties definitions
   FILE: Si21XXC_L1_Properties.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si21XXC_COMMAND_PROTOTYPES

#include "Si21XXC_L1_API.h"

/***********************************************************************************************************************
  Si21XXC_L1_SetProperty function
  Use:        property set function
              Used to call L1_SET_PROPERTY with the property Id and data provided.
  Parameter: *api     the Si21XXC context
  Parameter: prop     the property Id
  Parameter: data     the property bytes
  Behavior:  This function will only download the property if required.
               Conditions to download the property are:
                - The property changes
                - The propertyWriteMode is set to Si21XXC_DOWNLOAD_ALWAYS
                - The property is unknown to Si21XXC_PackProperty (this may be useful for debug purpose)
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_SetProperty(L1_Si21XXC_Context *api, unsigned int prop, int  data)  {
    unsigned char  reserved          = 0;
    return Si21XXC_L1_SET_PROPERTY (api, reserved, prop, data);
}

/***********************************************************************************************************************
  Si21XXC_L1_GetProperty function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si21XXC context
  Parameter: prop     the property Id
  Parameter: *data    a buffer to store the property bytes into
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_GetProperty         (L1_Si21XXC_Context *api, unsigned int prop_code, int *data) {
    unsigned char  reserved          = 0;
    unsigned char res;
    res = Si21XXC_L1_GET_PROPERTY (api, reserved, prop_code);
    *data = api->rsp->get_property.data;
    return res;
}
/***********************************************************************************************************************
  Si21XXC_L1_SetProperty2 function
  Use:        Sets the property given the property code.
  Parameter: *api     the Si21XXC context
  Parameter: prop     the property Id

  Returns:    NO_Si21XXC_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_SetProperty2(L1_Si21XXC_Context *api, unsigned int prop_code) {
    int data=0, res=0;//20120914,SSVD,ADD.
    res = Si21XXC_PackProperty(api->prop,prop_code,&data);
    if (res != NO_Si21XXC_ERROR) {
     SiTRACE("\nSi2XX_L1_SetProperty2: %s 0x%04x!\n\n", Si21XXC_L1_API_ERROR_TEXT(res), prop_code);
     SiERROR(Si21XXC_L1_API_ERROR_TEXT(res));
      return res;
    }
    return Si21XXC_L1_SetProperty (api, prop_code & 0xffff, data);
}
/***********************************************************************************************************************
  Si21XXC_L1_GetProperty2 function
  Use:        property get function
              Used to call L1_GET_PROPERTY with the property Id provided.
  Parameter: *api     the Si21XXC context
  Parameter: prop     the property Id

  Returns:    NO_Si21XXC_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_GetProperty2(L1_Si21XXC_Context *api, unsigned int prop_code) {
  int data, res;
  res = Si21XXC_L1_GetProperty(api, prop_code & 0xffff, &data);
  if (res != NO_Si21XXC_ERROR) {
    SiTRACE("Si21XXC_L1_GetProperty2: %s 0x%04x\n", Si21XXC_L1_API_ERROR_TEXT(res), prop_code);
    SiERROR(Si21XXC_L1_API_ERROR_TEXT(res));
    return res;
  }
  return Si21XXC_UnpackProperty(api->prop, prop_code, data);
}
/*****************************************************************************************
 NAME: Si21XXC_downloadATVProperties
  DESCRIPTION: Setup Si21XXC ATV properties configuration
  This function will download all the ATV configuration properties.
  The function Si21XXC_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si21XXC Context
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
  Programming Guide Reference:    ATV setup flowchart
******************************************************************************************/
int  Si21XXC_downloadATVProperties         (L1_Si21XXC_Context *api) {
    char download_mode;
  SiTRACE("Si21XXC_downloadATVProperties\n");
#ifdef    Si21XXC_ATV_AFC_RANGE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_AFC_RANGE_PROP_CODE               ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_AFC_RANGE_PROP */
#ifdef    Si21XXC_ATV_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_AGC_SPEED_PROP_CODE               ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_AGC_SPEED_PROP */
#ifdef    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE      ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */
#ifdef    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_CODE         ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */
#ifdef    Si21XXC_ATV_AUDIO_MODE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_AUDIO_MODE_PROP_CODE              ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_AUDIO_MODE_PROP */
#ifdef    Si21XXC_ATV_CONFIG_IF_PORT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_CONFIG_IF_PORT_PROP */
  if (api->rsp->part_info.romid == 0x70  || api->rsp->part_info.romid == 0x71)
  {
    #ifdef    Si2190B_ATV_CVBS_ATTENUATION_PROP
      if (Si21XXC_L1_SetProperty2(api, Si2190B_ATV_CVBS_ATTENUATION_PROP_CODE        ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
    #endif /* Si2190B_ATV_CVBS_ATTENUATION_PROP */
  }
#ifdef    Si21XXC_ATV_CVBS_OUT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_CVBS_OUT_PROP_CODE                ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_CVBS_OUT_PROP */
#ifdef    Si21XXC_ATV_CVBS_OUT_FINE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_CVBS_OUT_FINE_PROP_CODE           ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_CVBS_OUT_FINE_PROP */
#ifdef    Si21XXC_ATV_IEN_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_IEN_PROP_CODE                     ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_IEN_PROP */
#ifdef    Si21XXC_ATV_INT_SENSE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_INT_SENSE_PROP_CODE               ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_INT_SENSE_PROP */
#ifdef    Si21XXC_ATV_PGA_TARGET_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_PGA_TARGET_PROP_CODE              ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_PGA_TARGET_PROP */
#ifdef    Si21XXC_ATV_RF_TOP_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_RF_TOP_PROP_CODE                  ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_RF_TOP_PROP */
#ifdef    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_CODE       ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */
#ifdef    Si21XXC_ATV_SIF_OUT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_SIF_OUT_PROP_CODE                 ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_SIF_OUT_PROP */
#ifdef    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_CODE         ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */
#ifdef    Si21XXC_ATV_SOUND_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_SOUND_AGC_SPEED_PROP_CODE         ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_SOUND_AGC_SPEED_PROP */
#ifdef    Si21XXC_ATV_VIDEO_EQUALIZER_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_VIDEO_EQUALIZER_PROP_CODE         ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_VIDEO_EQUALIZER_PROP */
#ifdef    Si21XXC_ATV_VIDEO_MODE_PROP
  download_mode=api->propertyWriteMode;
  api->propertyWriteMode=DOWNLOAD_ALWAYS;
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_VIDEO_MODE_PROP_CODE              ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
  api->propertyWriteMode=download_mode;
#endif /* Si21XXC_ATV_VIDEO_MODE_PROP */
#ifdef    Si21XXC_ATV_VSNR_CAP_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_VSNR_CAP_PROP_CODE                ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_ATV_VSNR_CAP_PROP */
return NO_Si21XXC_ERROR;
}
/*****************************************************************************************
 NAME: Si21XXC_downloadCOMMONProperties
  DESCRIPTION: Setup Si21XXC COMMON properties configuration
  This function will download all the COMMON configuration properties.
  The function Si21XXC_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si21XXC Context
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
  Programming Guide Reference:    COMMON setup flowchart
******************************************************************************************/
int  Si21XXC_downloadCOMMONProperties      (L1_Si21XXC_Context *api) {
  SiTRACE("Si21XXC_downloadCOMMONProperties\n");
#ifdef    Si21XXC_CRYSTAL_TRIM_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_CRYSTAL_TRIM_PROP_CODE                ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_CRYSTAL_TRIM_PROP */
#ifdef    Si21XXC_MASTER_IEN_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_MASTER_IEN_PROP_CODE                  ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_MASTER_IEN_PROP */
#ifdef    Si21XXC_XOUT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_XOUT_PROP_CODE                        ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_XOUT_PROP */
return NO_Si21XXC_ERROR;
}
/*****************************************************************************************
 NAME: Si21XXC_downloadDTVProperties
  DESCRIPTION: Setup Si21XXC DTV properties configuration
  This function will download all the DTV configuration properties.
  The function Si21XXC_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si21XXC Context
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
  Programming Guide Reference:    DTV setup flowchart
******************************************************************************************/
int  Si21XXC_downloadDTVProperties         (L1_Si21XXC_Context *api) {
  char download_mode;
  SiTRACE("Si21XXC_downloadDTVProperties\n");
#ifdef    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_CODE         ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */
#ifdef    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_CODE        ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */
#ifdef    Si21XXC_DTV_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_AGC_SPEED_PROP_CODE               ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_AGC_SPEED_PROP */
#ifdef    Si21XXC_DTV_CONFIG_IF_PORT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_CONFIG_IF_PORT_PROP_CODE          ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_CONFIG_IF_PORT_PROP */
#ifdef    Si21XXC_DTV_EXT_AGC_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_EXT_AGC_PROP_CODE                 ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_EXT_AGC_PROP */
#ifdef    Si21XXC_DTV_IEN_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_IEN_PROP_CODE                     ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_IEN_PROP */
#ifdef    Si21XXC_DTV_IF_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_IF_AGC_SPEED_PROP_CODE            ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_IF_AGC_SPEED_PROP */
#ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_CODE       ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */
#ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
#ifdef    Si21XXC_DTV_INTERNAL_ZIF_PROP
  if ((api->rsp->part_info.part == 91) && (api->rsp->part_info.chiprev==3))
  {
      SiTRACE("DTV_INTERNAL_ZIF not defined for Si2191-C20.\n");
  }
  else
  {
      if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_INTERNAL_ZIF_PROP_CODE            ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
  }
#endif /* Si21XXC_DTV_INTERNAL_ZIF_PROP */
#ifdef    Si21XXC_DTV_INT_SENSE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_INT_SENSE_PROP_CODE               ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_INT_SENSE_PROP */
#ifdef    Si21XXC_DTV_LIF_FREQ_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_LIF_FREQ_PROP_CODE                ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_LIF_FREQ_PROP */
#ifdef    Si21XXC_DTV_LIF_OUT_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_LIF_OUT_PROP_CODE                 ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_LIF_OUT_PROP */
#ifdef    Si21XXC_DTV_MODE_PROP
  download_mode=api->propertyWriteMode;
  api->propertyWriteMode=DOWNLOAD_ALWAYS;
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_MODE_PROP_CODE                    ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
  api->propertyWriteMode=download_mode;
#endif /* Si21XXC_DTV_MODE_PROP */
#ifdef    Si21XXC_DTV_RF_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_RF_AGC_SPEED_PROP_CODE            ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_RF_AGC_SPEED_PROP */
#ifdef    Si21XXC_DTV_RF_TOP_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_RF_TOP_PROP_CODE                  ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_RF_TOP_PROP */
#ifdef    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE      ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */
#ifdef    Si21XXC_DTV_WB_AGC_SPEED_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_WB_AGC_SPEED_PROP_CODE            ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_DTV_WB_AGC_SPEED_PROP */
return NO_Si21XXC_ERROR;
}
/*****************************************************************************************
 NAME: Si21XXC_downloadTUNERProperties
  DESCRIPTION: Setup Si21XXC TUNER properties configuration
  This function will download all the TUNER configuration properties.
  The function Si21XXC_storeUserProperties should be called before the first call to this function.
  Parameter:  Pointer to Si21XXC Context
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
  Programming Guide Reference:    TUNER setup flowchart
******************************************************************************************/
int  Si21XXC_downloadTUNERProperties       (L1_Si21XXC_Context *api) {
  SiTRACE("Si21XXC_downloadTUNERProperties\n");
#ifdef    Si21XXC_TUNER_BLOCKED_VCO_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_TUNER_BLOCKED_VCO_PROP_CODE           ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_TUNER_BLOCKED_VCO_PROP */
#ifdef    Si21XXC_TUNER_IEN_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_TUNER_IEN_PROP_CODE                   ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_TUNER_IEN_PROP */
#ifdef    Si21XXC_TUNER_INT_SENSE_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_TUNER_INT_SENSE_PROP_CODE             ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_TUNER_INT_SENSE_PROP */
#ifdef    Si21XXC_TUNER_LO_INJECTION_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_TUNER_LO_INJECTION_PROP_CODE          ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_TUNER_LO_INJECTION_PROP */
#ifdef    Si21XXC_TUNER_RETURN_LOSS_PROP
  if (Si21XXC_L1_SetProperty2(api, Si21XXC_TUNER_RETURN_LOSS_PROP_CODE           ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
#endif /* Si21XXC_TUNER_RETURN_LOSS_PROP */
  if (api->rsp->part_info.romid == 0x70 || api->rsp->part_info.romid == 0x71)
  {
    #ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
      if (Si21XXC_L1_SetProperty2(api, Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CODE  ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
    #endif /* Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP */
    #ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
      if (Si21XXC_L1_SetProperty2(api, Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_CODE) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
    #endif /* Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */
    #ifdef    Si2190B_WIDE_BAND_ATT_THRS_PROP
      if (Si21XXC_L1_SetProperty2(api, Si2190B_WIDE_BAND_ATT_THRS_PROP_CODE          ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
    #endif /* Si2190B_WIDE_BAND_ATT_THRS_PROP */
  }
  if (api->rsp->part_info.romid == 0x71)
    {
      #ifdef    Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
      if (Si21XXC_L1_SetProperty2(api, Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_CODE   ) != NO_Si21XXC_ERROR) {return ERROR_Si21XXC_SENDING_COMMAND;}
      #endif /* Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */

    }
return NO_Si21XXC_ERROR;
}
int  Si21XXC_downloadAllProperties         (L1_Si21XXC_Context *api) {
  Si21XXC_downloadATVProperties         (api);
  Si21XXC_downloadCOMMONProperties      (api);
  Si21XXC_downloadDTVProperties         (api);
  Si21XXC_downloadTUNERProperties       (api);
  return 0;
}

/***********************************************************************************************************************
  Si21XXC_PackProperty function
  Use:        This function will pack all the members of a property into an integer for the SetProperty function.

  Parameter: *prop          the Si21XXC property context
  Parameter:  prop_code     the property Id
  Parameter:  *data         an int to store the property data

  Returns:    NO_Si21XXC_ERROR if the property exists.
 ***********************************************************************************************************************/
unsigned char Si21XXC_PackProperty            (Si21XXC_PropObj   *prop, unsigned int prop_code, int *data) {
    switch (prop_code) {
    #ifdef        Si21XXC_ATV_AFC_RANGE_PROP
     case         Si21XXC_ATV_AFC_RANGE_PROP_CODE:
      *data = (prop->atv_afc_range.range_khz & Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK) << Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB ;
     break;
    #endif /*     Si21XXC_ATV_AFC_RANGE_PROP */
    #ifdef        Si21XXC_ATV_AGC_SPEED_PROP
     case         Si21XXC_ATV_AGC_SPEED_PROP_CODE:
      *data = (prop->atv_agc_speed.if_agc_speed & Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB ;
     break;
    #endif /*     Si21XXC_ATV_AGC_SPEED_PROP */
    #ifdef        Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
      *data = (prop->atv_agc_speed_low_rssi.if_agc_speed & Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK) << Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB  |
              (prop->atv_agc_speed_low_rssi.thld         & Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK        ) << Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB ;
     break;
    #endif /*     Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
     case         Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_CODE:
      *data = (prop->atv_artificial_snow.gain   & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK  ) << Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB  |
              (prop->atv_artificial_snow.sound  & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MASK ) << Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND_LSB  |
              (prop->atv_artificial_snow.period & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_MASK) << Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LSB  |
              (prop->atv_artificial_snow.offset & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_MASK) << Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si21XXC_ATV_AUDIO_MODE_PROP
        case         Si21XXC_ATV_AUDIO_MODE_PROP_CODE:
        *data = (prop->atv_audio_mode.audio_sys  & Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK ) << Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB  |
              (prop->atv_audio_mode.chan_bw    & Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK   ) << Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB ;
        break;
    #endif /*     Si21XXC_ATV_AUDIO_MODE_PROP */
    #ifdef        Si21XXC_ATV_CONFIG_IF_PORT_PROP
     case         Si21XXC_ATV_CONFIG_IF_PORT_PROP_CODE:
      *data = (prop->atv_config_if_port.atv_out_type & Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK) << Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB ;
     break;
    #endif /*     Si21XXC_ATV_CONFIG_IF_PORT_PROP */

    #ifdef        Si2190B_ATV_CVBS_ATTENUATION_PROP
     case         Si2190B_ATV_CVBS_ATTENUATION_PROP_CODE:
      *data = (prop->atv_cvbs_attenuation.threshold & Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD_MASK) << Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD_LSB  |
              (prop->atv_cvbs_attenuation.rate      & Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE_MASK     ) << Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE_LSB  |
              (prop->atv_cvbs_attenuation.bw        & Si2190B_ATV_CVBS_ATTENUATION_PROP_BW_MASK       ) << Si2190B_ATV_CVBS_ATTENUATION_PROP_BW_LSB ;
     break;
    #endif /*     Si2190B_ATV_CVBS_ATTENUATION_PROP */

    #ifdef        Si21XXC_ATV_CVBS_OUT_PROP
     case         Si21XXC_ATV_CVBS_OUT_PROP_CODE:
      *data = (prop->atv_cvbs_out.offset & Si21XXC_ATV_CVBS_OUT_PROP_OFFSET_MASK) << Si21XXC_ATV_CVBS_OUT_PROP_OFFSET_LSB  |
              (prop->atv_cvbs_out.amp    & Si21XXC_ATV_CVBS_OUT_PROP_AMP_MASK   ) << Si21XXC_ATV_CVBS_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si21XXC_ATV_CVBS_OUT_PROP */
    #ifdef        Si21XXC_ATV_CVBS_OUT_FINE_PROP
     case         Si21XXC_ATV_CVBS_OUT_FINE_PROP_CODE:
      *data = (prop->atv_cvbs_out_fine.offset & Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK) << Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB  |
              (prop->atv_cvbs_out_fine.amp    & Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP_MASK   ) << Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP_LSB ;
     break;
    #endif /*     Si21XXC_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si21XXC_ATV_IEN_PROP
     case         Si21XXC_ATV_IEN_PROP_CODE:
      *data = (prop->atv_ien.chlien  & Si21XXC_ATV_IEN_PROP_CHLIEN_MASK ) << Si21XXC_ATV_IEN_PROP_CHLIEN_LSB  |
              (prop->atv_ien.pclien  & Si21XXC_ATV_IEN_PROP_PCLIEN_MASK ) << Si21XXC_ATV_IEN_PROP_PCLIEN_LSB  |
              (prop->atv_ien.dlien   & Si21XXC_ATV_IEN_PROP_DLIEN_MASK  ) << Si21XXC_ATV_IEN_PROP_DLIEN_LSB  |
              (prop->atv_ien.snrlien & Si21XXC_ATV_IEN_PROP_SNRLIEN_MASK) << Si21XXC_ATV_IEN_PROP_SNRLIEN_LSB  |
              (prop->atv_ien.snrhien & Si21XXC_ATV_IEN_PROP_SNRHIEN_MASK) << Si21XXC_ATV_IEN_PROP_SNRHIEN_LSB ;
     break;
    #endif /*     Si21XXC_ATV_IEN_PROP */
    #ifdef        Si21XXC_ATV_INT_SENSE_PROP
     case         Si21XXC_ATV_INT_SENSE_PROP_CODE:
      *data = (prop->atv_int_sense.chlnegen  & Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN_MASK ) << Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (prop->atv_int_sense.pclnegen  & Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN_MASK ) << Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN_LSB  |
              (prop->atv_int_sense.dlnegen   & Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN_MASK  ) << Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN_LSB  |
              (prop->atv_int_sense.snrlnegen & Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK) << Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB  |
              (prop->atv_int_sense.snrhnegen & Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK) << Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB  |
              (prop->atv_int_sense.chlposen  & Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN_MASK ) << Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN_LSB  |
              (prop->atv_int_sense.pclposen  & Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN_MASK ) << Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN_LSB  |
              (prop->atv_int_sense.dlposen   & Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN_MASK  ) << Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN_LSB  |
              (prop->atv_int_sense.snrlposen & Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK) << Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB  |
              (prop->atv_int_sense.snrhposen & Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK) << Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB ;
     break;
    #endif /*     Si21XXC_ATV_INT_SENSE_PROP */
    #ifdef        Si21XXC_ATV_PGA_TARGET_PROP
     case         Si21XXC_ATV_PGA_TARGET_PROP_CODE:
      *data = (prop->atv_pga_target.pga_target      & Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK     ) << Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB  |
              (prop->atv_pga_target.override_enable & Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK) << Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB ;
     break;
    #endif /*     Si21XXC_ATV_PGA_TARGET_PROP */
    #ifdef        Si21XXC_ATV_RF_TOP_PROP
     case         Si21XXC_ATV_RF_TOP_PROP_CODE:
      *data = (prop->atv_rf_top.atv_rf_top & Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK) << Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB ;
     break;
    #endif /*     Si21XXC_ATV_RF_TOP_PROP */
    #ifdef        Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      *data = (prop->atv_rsq_rssi_threshold.lo & Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (prop->atv_rsq_rssi_threshold.hi & Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
      *data = (prop->atv_rsq_snr_threshold.lo & Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK) << Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB  |
              (prop->atv_rsq_snr_threshold.hi & Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK) << Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si21XXC_ATV_SIF_OUT_PROP
     case         Si21XXC_ATV_SIF_OUT_PROP_CODE:
      *data = (prop->atv_sif_out.offset & Si21XXC_ATV_SIF_OUT_PROP_OFFSET_MASK) << Si21XXC_ATV_SIF_OUT_PROP_OFFSET_LSB  |
              (prop->atv_sif_out.amp    & Si21XXC_ATV_SIF_OUT_PROP_AMP_MASK   ) << Si21XXC_ATV_SIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si21XXC_ATV_SIF_OUT_PROP */
    #ifdef        Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
     case         Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_CODE:
      *data = (prop->atv_sound_agc_limit.max_gain & Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK) << Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB  |
              (prop->atv_sound_agc_limit.min_gain & Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK) << Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB ;
     break;
    #endif /*     Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si21XXC_ATV_SOUND_AGC_SPEED_PROP
     case         Si21XXC_ATV_SOUND_AGC_SPEED_PROP_CODE:
      *data = (prop->atv_sound_agc_speed.system_l      & Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK     ) << Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB  |
              (prop->atv_sound_agc_speed.other_systems & Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK) << Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB ;
     break;
    #endif /*     Si21XXC_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si21XXC_ATV_VIDEO_EQUALIZER_PROP
     case         Si21XXC_ATV_VIDEO_EQUALIZER_PROP_CODE:
      *data = (prop->atv_video_equalizer.slope & Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK) << Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB ;
     break;
    #endif /*     Si21XXC_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si21XXC_ATV_VIDEO_MODE_PROP
     case         Si21XXC_ATV_VIDEO_MODE_PROP_CODE:
      *data = (prop->atv_video_mode.video_sys     & Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK    ) << Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB  |
              (prop->atv_video_mode.color         & Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_MASK        ) << Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_LSB  |
              (prop->atv_video_mode.invert_signal & Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK) << Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB ;
     break;
    #endif /*     Si21XXC_ATV_VIDEO_MODE_PROP */
    #ifdef        Si21XXC_ATV_VSNR_CAP_PROP
     case         Si21XXC_ATV_VSNR_CAP_PROP_CODE:
      *data = (prop->atv_vsnr_cap.atv_vsnr_cap & Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK) << Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB ;
     break;
    #endif /*     Si21XXC_ATV_VSNR_CAP_PROP */
    #ifdef        Si21XXC_CRYSTAL_TRIM_PROP
     case         Si21XXC_CRYSTAL_TRIM_PROP_CODE:
      *data = (prop->crystal_trim.xo_cap & Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP_MASK) << Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP_LSB ;
     break;
    #endif /*     Si21XXC_CRYSTAL_TRIM_PROP */
    #ifdef        Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
     case         Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_CODE:
      *data = (prop->dtv_agc_auto_freeze.thld    & Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD_MASK   ) << Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD_LSB  |
              (prop->dtv_agc_auto_freeze.timeout & Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_MASK) << Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_LSB ;
     break;
    #endif /*     Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef        Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
     case         Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_CODE:
      *data = (prop->dtv_agc_freeze_input.level & Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK) << Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB  |
              (prop->dtv_agc_freeze_input.pin   & Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK  ) << Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB ;
     break;
    #endif /*     Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si21XXC_DTV_AGC_SPEED_PROP
     case         Si21XXC_DTV_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_agc_speed.if_agc_speed & Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (prop->dtv_agc_speed.agc_decim    & Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si21XXC_DTV_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_CONFIG_IF_PORT_PROP
     case         Si21XXC_DTV_CONFIG_IF_PORT_PROP_CODE:
      *data = (prop->dtv_config_if_port.dtv_out_type   & Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK  ) << Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  |
              (prop->dtv_config_if_port.dtv_agc_source & Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK) << Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB ;
     break;
    #endif /*     Si21XXC_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si21XXC_DTV_EXT_AGC_PROP
     case         Si21XXC_DTV_EXT_AGC_PROP_CODE:
      *data = (prop->dtv_ext_agc.min_10mv & Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV_MASK) << Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV_LSB  |
              (prop->dtv_ext_agc.max_10mv & Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV_MASK) << Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV_LSB ;
     break;
    #endif /*     Si21XXC_DTV_EXT_AGC_PROP */
    #ifdef        Si21XXC_DTV_IEN_PROP
     case         Si21XXC_DTV_IEN_PROP_CODE:
      *data = (prop->dtv_ien.chlien & Si21XXC_DTV_IEN_PROP_CHLIEN_MASK) << Si21XXC_DTV_IEN_PROP_CHLIEN_LSB ;
     break;
    #endif /*     Si21XXC_DTV_IEN_PROP */
    #ifdef        Si21XXC_DTV_IF_AGC_SPEED_PROP
     case         Si21XXC_DTV_IF_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_if_agc_speed.attack & Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK_MASK) << Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK_LSB  |
              (prop->dtv_if_agc_speed.decay  & Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY_MASK ) << Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY_LSB ;
     break;
    #endif /*     Si21XXC_DTV_IF_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
     case         Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_initial_agc_speed.if_agc_speed & Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB  |
              (prop->dtv_initial_agc_speed.agc_decim    & Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK   ) << Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB ;
     break;
    #endif /*     Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
      *data = (prop->dtv_initial_agc_speed_period.period & Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK) << Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB ;
     break;
    #endif /*     Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si21XXC_DTV_INTERNAL_ZIF_PROP
     case         Si21XXC_DTV_INTERNAL_ZIF_PROP_CODE:
      *data = (prop->dtv_internal_zif.atsc   & Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC_MASK  ) << Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC_LSB  |
              (prop->dtv_internal_zif.qam_us & Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK) << Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB  |
              (prop->dtv_internal_zif.dvbt   & Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT_MASK  ) << Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT_LSB  |
              (prop->dtv_internal_zif.dvbc   & Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC_MASK  ) << Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC_LSB  |
              (prop->dtv_internal_zif.isdbt  & Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK ) << Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB  |
              (prop->dtv_internal_zif.isdbc  & Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK ) << Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB  |
              (prop->dtv_internal_zif.dtmb   & Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB_MASK  ) << Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB_LSB ;
     break;
    #endif /*     Si21XXC_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si21XXC_DTV_INT_SENSE_PROP
     case         Si21XXC_DTV_INT_SENSE_PROP_CODE:
      *data = (prop->dtv_int_sense.chlnegen & Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN_MASK) << Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN_LSB  |
              (prop->dtv_int_sense.chlposen & Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN_MASK) << Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN_LSB ;
     break;
    #endif /*     Si21XXC_DTV_INT_SENSE_PROP */
    #ifdef        Si21XXC_DTV_LIF_FREQ_PROP
     case         Si21XXC_DTV_LIF_FREQ_PROP_CODE:
      *data = (prop->dtv_lif_freq.offset & Si21XXC_DTV_LIF_FREQ_PROP_OFFSET_MASK) << Si21XXC_DTV_LIF_FREQ_PROP_OFFSET_LSB ;
     break;
    #endif /*     Si21XXC_DTV_LIF_FREQ_PROP */
    #ifdef        Si21XXC_DTV_LIF_OUT_PROP
     case         Si21XXC_DTV_LIF_OUT_PROP_CODE:
      *data = (prop->dtv_lif_out.offset & Si21XXC_DTV_LIF_OUT_PROP_OFFSET_MASK) << Si21XXC_DTV_LIF_OUT_PROP_OFFSET_LSB  |
              (prop->dtv_lif_out.amp    & Si21XXC_DTV_LIF_OUT_PROP_AMP_MASK   ) << Si21XXC_DTV_LIF_OUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si21XXC_DTV_LIF_OUT_PROP */
    #ifdef        Si21XXC_DTV_MODE_PROP
     case         Si21XXC_DTV_MODE_PROP_CODE:
      *data = (prop->dtv_mode.bw              & Si21XXC_DTV_MODE_PROP_BW_MASK             ) << Si21XXC_DTV_MODE_PROP_BW_LSB  |
              (prop->dtv_mode.modulation      & Si21XXC_DTV_MODE_PROP_MODULATION_MASK     ) << Si21XXC_DTV_MODE_PROP_MODULATION_LSB  |
              (prop->dtv_mode.invert_spectrum & Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM_MASK) << Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM_LSB ;
     break;
    #endif /*     Si21XXC_DTV_MODE_PROP */
    #ifdef        Si21XXC_DTV_RF_AGC_SPEED_PROP
     case         Si21XXC_DTV_RF_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_rf_agc_speed.attack & Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK_MASK) << Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK_LSB  |
              (prop->dtv_rf_agc_speed.decay  & Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY_MASK ) << Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY_LSB ;
     break;
    #endif /*     Si21XXC_DTV_RF_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_RF_TOP_PROP
     case         Si21XXC_DTV_RF_TOP_PROP_CODE:
      *data = (prop->dtv_rf_top.dtv_rf_top & Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK) << Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB ;
     break;
    #endif /*     Si21XXC_DTV_RF_TOP_PROP */
    #ifdef        Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      *data = (prop->dtv_rsq_rssi_threshold.lo & Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK) << Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB  |
              (prop->dtv_rsq_rssi_threshold.hi & Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK) << Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB ;
     break;
    #endif /*     Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */
     #ifdef        Si21XXC_DTV_WB_AGC_SPEED_PROP
     case         Si21XXC_DTV_WB_AGC_SPEED_PROP_CODE:
      *data = (prop->dtv_wb_agc_speed.attack & Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK_MASK) << Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK_LSB  |
              (prop->dtv_wb_agc_speed.decay  & Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY_MASK ) << Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY_LSB ;
     break;
    #endif /*     Si21XXC_DTV_WB_AGC_SPEED_PROP */
    #ifdef        Si21XXC_MASTER_IEN_PROP
     case         Si21XXC_MASTER_IEN_PROP_CODE:
      *data = (prop->master_ien.tunien & Si21XXC_MASTER_IEN_PROP_TUNIEN_MASK) << Si21XXC_MASTER_IEN_PROP_TUNIEN_LSB  |
              (prop->master_ien.atvien & Si21XXC_MASTER_IEN_PROP_ATVIEN_MASK) << Si21XXC_MASTER_IEN_PROP_ATVIEN_LSB  |
              (prop->master_ien.dtvien & Si21XXC_MASTER_IEN_PROP_DTVIEN_MASK) << Si21XXC_MASTER_IEN_PROP_DTVIEN_LSB  |
              (prop->master_ien.errien & Si21XXC_MASTER_IEN_PROP_ERRIEN_MASK) << Si21XXC_MASTER_IEN_PROP_ERRIEN_LSB  |
              (prop->master_ien.ctsien & Si21XXC_MASTER_IEN_PROP_CTSIEN_MASK) << Si21XXC_MASTER_IEN_PROP_CTSIEN_LSB ;
     break;
    #endif /*     Si21XXC_MASTER_IEN_PROP */
    #ifdef        Si21XXC_TUNER_BLOCKED_VCO_PROP
     case         Si21XXC_TUNER_BLOCKED_VCO_PROP_CODE:
      *data = (prop->tuner_blocked_vco.vco_code & Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK) << Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB ;
     break;
    #endif /*     Si21XXC_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si21XXC_TUNER_IEN_PROP
     case         Si21XXC_TUNER_IEN_PROP_CODE:
      *data = (prop->tuner_ien.tcien    & Si21XXC_TUNER_IEN_PROP_TCIEN_MASK   ) << Si21XXC_TUNER_IEN_PROP_TCIEN_LSB  |
              (prop->tuner_ien.rssilien & Si21XXC_TUNER_IEN_PROP_RSSILIEN_MASK) << Si21XXC_TUNER_IEN_PROP_RSSILIEN_LSB  |
              (prop->tuner_ien.rssihien & Si21XXC_TUNER_IEN_PROP_RSSIHIEN_MASK) << Si21XXC_TUNER_IEN_PROP_RSSIHIEN_LSB ;
     break;
    #endif /*     Si21XXC_TUNER_IEN_PROP */
    #ifdef        Si21XXC_TUNER_INT_SENSE_PROP
     case         Si21XXC_TUNER_INT_SENSE_PROP_CODE:
      *data = (prop->tuner_int_sense.tcnegen    & Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN_MASK   ) << Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN_LSB  |
              (prop->tuner_int_sense.rssilnegen & Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK) << Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB  |
              (prop->tuner_int_sense.rssihnegen & Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK) << Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB  |
              (prop->tuner_int_sense.tcposen    & Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN_MASK   ) << Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN_LSB  |
              (prop->tuner_int_sense.rssilposen & Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK) << Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB  |
              (prop->tuner_int_sense.rssihposen & Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK) << Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB ;
     break;
    #endif /*     Si21XXC_TUNER_INT_SENSE_PROP */
    #ifdef        Si21XXC_TUNER_LO_INJECTION_PROP
     case         Si21XXC_TUNER_LO_INJECTION_PROP_CODE:
      *data = (prop->tuner_lo_injection.band_1 & Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1_MASK) << Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1_LSB  |
              (prop->tuner_lo_injection.band_2 & Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2_MASK) << Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2_LSB  |
              (prop->tuner_lo_injection.band_3 & Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3_MASK) << Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3_LSB ;
     break;
    #endif /*     Si21XXC_TUNER_LO_INJECTION_PROP */
    #ifdef        Si21XXC_TUNER_RETURN_LOSS_PROP
     case         Si21XXC_TUNER_RETURN_LOSS_PROP_CODE:
      *data = (prop->tuner_return_loss.config & Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG_MASK) << Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG_LSB  |
              (prop->tuner_return_loss.mode   & Si21XXC_TUNER_RETURN_LOSS_PROP_MODE_MASK  ) << Si21XXC_TUNER_RETURN_LOSS_PROP_MODE_LSB ;
     break;
    #endif /*     Si21XXC_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
     case         Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CODE:
      *data = (prop->tuner_return_loss_optimize.thld                & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_MASK               ) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_LSB  |
              (prop->tuner_return_loss_optimize.config              & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_MASK             ) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_LSB  |
              (prop->tuner_return_loss_optimize.engagement_delay    & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_MASK   ) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_LSB  |
              (prop->tuner_return_loss_optimize.disengagement_delay & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_MASK) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_LSB ;
     break;
    #endif /*     Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP */
    #ifdef        Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
     case         Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_CODE:
      *data = (prop->tuner_return_loss_optimize_2.thld             & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_MASK            ) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_LSB  |
              (prop->tuner_return_loss_optimize_2.window           & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_MASK          ) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_LSB  |
              (prop->tuner_return_loss_optimize_2.engagement_delay & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_MASK) << Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_LSB ;
     break;
    #endif /*     Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */
    #ifdef        Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
     case         Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_CODE:
      *data = (prop->tuner_tf1_boundary_offset.tf1_boundary_offset & Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_MASK) << Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_LSB ;
     break;
    #endif /*     Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */
    #ifdef        Si2190B_WIDE_BAND_ATT_THRS_PROP
     case         Si2190B_WIDE_BAND_ATT_THRS_PROP_CODE:
      *data = (prop->wide_band_att_thrs.wb_att_thrs & Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_MASK) << Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_LSB ;
     break;
    #endif /*     Si2190B_WIDE_BAND_ATT_THRS_PROP */
    #ifdef        Si21XXC_XOUT_PROP
     case         Si21XXC_XOUT_PROP_CODE:
      *data = (prop->xout.amp & Si21XXC_XOUT_PROP_AMP_MASK) << Si21XXC_XOUT_PROP_AMP_LSB ;
     break;
    #endif /*     Si21XXC_XOUT_PROP */
     default : return ERROR_Si21XXC_UNKNOWN_PROPERTY; break;
    }
    return NO_Si21XXC_ERROR;
  }


/***********************************************************************************************************************
  Si21XXC_UnpackProperty function
  Use:        This function will unpack all the members of a property from an integer from the GetProperty function.

  Parameter: *prop          the Si21XXC property context
  Parameter:  prop_code     the property Id
  Parameter:  data          the property data

  Returns:    NO_Si21XXC_ERROR if the property exists.
 ***********************************************************************************************************************/
unsigned char Si21XXC_UnpackProperty          (Si21XXC_PropObj   *prop, unsigned int prop_code, int  data) {
    switch (prop_code) {
    #ifdef        Si21XXC_ATV_AFC_RANGE_PROP
     case         Si21XXC_ATV_AFC_RANGE_PROP_CODE:
               prop->atv_afc_range.range_khz = (data >> Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ_LSB) & Si21XXC_ATV_AFC_RANGE_PROP_RANGE_KHZ_MASK;
     break;
    #endif /*     Si21XXC_ATV_AFC_RANGE_PROP */
    #ifdef        Si21XXC_ATV_AGC_SPEED_PROP
     case         Si21XXC_ATV_AGC_SPEED_PROP_CODE:
               prop->atv_agc_speed.if_agc_speed     = (data >> Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB    ) & Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
     break;
    #endif /*     Si21XXC_ATV_AGC_SPEED_PROP */
    #ifdef        Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
               prop->atv_agc_speed_low_rssi.if_agc_speed = (data >> Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_LSB) & Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_MASK;
               prop->atv_agc_speed_low_rssi.thld         = (data >> Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_LSB        ) & Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_THLD_MASK;
     break;
    #endif /*     Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
     case         Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_CODE:
               prop->atv_artificial_snow.gain   = (data >> Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN_LSB  ) & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_GAIN_MASK;
               prop->atv_artificial_snow.sound  = (data >> Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND_LSB ) & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MASK;
               prop->atv_artificial_snow.period = (data >> Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LSB) & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_MASK;
               prop->atv_artificial_snow.offset = (data >> Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_LSB) & Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_OFFSET_MASK;
     break;
    #endif /*     Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si21XXC_ATV_AUDIO_MODE_PROP
        case         Si21XXC_ATV_AUDIO_MODE_PROP_CODE:
               prop->atv_audio_mode.audio_sys  = (data >> Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS_LSB ) & Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS_MASK;
               prop->atv_audio_mode.chan_bw    = (data >> Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW_LSB   ) & Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW_MASK;
        break;
    #endif /*     Si21XXC_ATV_AUDIO_MODE_PROP */
    #ifdef        Si21XXC_ATV_CONFIG_IF_PORT_PROP
     case         Si21XXC_ATV_CONFIG_IF_PORT_PROP_CODE:
               prop->atv_config_if_port.atv_out_type = (data >> Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_LSB) & Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_MASK;
     break;
    #endif /*     Si21XXC_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2190B_ATV_CVBS_ATTENUATION_PROP
     case         Si2190B_ATV_CVBS_ATTENUATION_PROP_CODE:
               prop->atv_cvbs_attenuation.threshold = (data >> Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD_LSB) & Si2190B_ATV_CVBS_ATTENUATION_PROP_THRESHOLD_MASK;
               prop->atv_cvbs_attenuation.rate      = (data >> Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE_LSB     ) & Si2190B_ATV_CVBS_ATTENUATION_PROP_RATE_MASK;
               prop->atv_cvbs_attenuation.bw        = (data >> Si2190B_ATV_CVBS_ATTENUATION_PROP_BW_LSB       ) & Si2190B_ATV_CVBS_ATTENUATION_PROP_BW_MASK;
     break;
    #endif /*     Si2190B_ATV_CVBS_ATTENUATION_PROP */
    #ifdef        Si21XXC_ATV_CVBS_OUT_PROP
     case         Si21XXC_ATV_CVBS_OUT_PROP_CODE:
               prop->atv_cvbs_out.offset = (data >> Si21XXC_ATV_CVBS_OUT_PROP_OFFSET_LSB) & Si21XXC_ATV_CVBS_OUT_PROP_OFFSET_MASK;
               prop->atv_cvbs_out.amp    = (data >> Si21XXC_ATV_CVBS_OUT_PROP_AMP_LSB   ) & Si21XXC_ATV_CVBS_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si21XXC_ATV_CVBS_OUT_PROP */
    #ifdef        Si21XXC_ATV_CVBS_OUT_FINE_PROP
     case         Si21XXC_ATV_CVBS_OUT_FINE_PROP_CODE:
               prop->atv_cvbs_out_fine.offset = (data >> Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET_LSB) & Si21XXC_ATV_CVBS_OUT_FINE_PROP_OFFSET_MASK;
               prop->atv_cvbs_out_fine.amp    = (data >> Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP_LSB   ) & Si21XXC_ATV_CVBS_OUT_FINE_PROP_AMP_MASK;
     break;
    #endif /*     Si21XXC_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si21XXC_ATV_IEN_PROP
     case         Si21XXC_ATV_IEN_PROP_CODE:
               prop->atv_ien.chlien  = (data >> Si21XXC_ATV_IEN_PROP_CHLIEN_LSB ) & Si21XXC_ATV_IEN_PROP_CHLIEN_MASK;
               prop->atv_ien.pclien  = (data >> Si21XXC_ATV_IEN_PROP_PCLIEN_LSB ) & Si21XXC_ATV_IEN_PROP_PCLIEN_MASK;
               prop->atv_ien.dlien   = (data >> Si21XXC_ATV_IEN_PROP_DLIEN_LSB  ) & Si21XXC_ATV_IEN_PROP_DLIEN_MASK;
               prop->atv_ien.snrlien = (data >> Si21XXC_ATV_IEN_PROP_SNRLIEN_LSB) & Si21XXC_ATV_IEN_PROP_SNRLIEN_MASK;
               prop->atv_ien.snrhien = (data >> Si21XXC_ATV_IEN_PROP_SNRHIEN_LSB) & Si21XXC_ATV_IEN_PROP_SNRHIEN_MASK;
     break;
    #endif /*     Si21XXC_ATV_IEN_PROP */
    #ifdef        Si21XXC_ATV_INT_SENSE_PROP
     case         Si21XXC_ATV_INT_SENSE_PROP_CODE:
               prop->atv_int_sense.chlnegen  = (data >> Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN_LSB ) & Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN_MASK;
               prop->atv_int_sense.pclnegen  = (data >> Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN_LSB ) & Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN_MASK;
               prop->atv_int_sense.dlnegen   = (data >> Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN_LSB  ) & Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN_MASK;
               prop->atv_int_sense.snrlnegen = (data >> Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN_LSB) & Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN_MASK;
               prop->atv_int_sense.snrhnegen = (data >> Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN_LSB) & Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN_MASK;
               prop->atv_int_sense.chlposen  = (data >> Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN_LSB ) & Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN_MASK;
               prop->atv_int_sense.pclposen  = (data >> Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN_LSB ) & Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN_MASK;
               prop->atv_int_sense.dlposen   = (data >> Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN_LSB  ) & Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN_MASK;
               prop->atv_int_sense.snrlposen = (data >> Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN_LSB) & Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN_MASK;
               prop->atv_int_sense.snrhposen = (data >> Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN_LSB) & Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN_MASK;
     break;
    #endif /*     Si21XXC_ATV_INT_SENSE_PROP */
    #ifdef        Si21XXC_ATV_PGA_TARGET_PROP
     case         Si21XXC_ATV_PGA_TARGET_PROP_CODE:
               prop->atv_pga_target.pga_target      = (data >> Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET_LSB     ) & Si21XXC_ATV_PGA_TARGET_PROP_PGA_TARGET_MASK;
               prop->atv_pga_target.override_enable = (data >> Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_LSB) & Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_MASK;
     break;
    #endif /*     Si21XXC_ATV_PGA_TARGET_PROP */
    #ifdef        Si21XXC_ATV_RF_TOP_PROP
     case         Si21XXC_ATV_RF_TOP_PROP_CODE:
               prop->atv_rf_top.atv_rf_top = (data >> Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB) & Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK;
     break;
    #endif /*     Si21XXC_ATV_RF_TOP_PROP */
    #ifdef        Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               prop->atv_rsq_rssi_threshold.lo = (data >> Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               prop->atv_rsq_rssi_threshold.hi = (data >> Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
               prop->atv_rsq_snr_threshold.lo = (data >> Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO_LSB) & Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_LO_MASK;
               prop->atv_rsq_snr_threshold.hi = (data >> Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI_LSB) & Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si21XXC_ATV_SIF_OUT_PROP
     case         Si21XXC_ATV_SIF_OUT_PROP_CODE:
               prop->atv_sif_out.offset = (data >> Si21XXC_ATV_SIF_OUT_PROP_OFFSET_LSB) & Si21XXC_ATV_SIF_OUT_PROP_OFFSET_MASK;
               prop->atv_sif_out.amp    = (data >> Si21XXC_ATV_SIF_OUT_PROP_AMP_LSB   ) & Si21XXC_ATV_SIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si21XXC_ATV_SIF_OUT_PROP */
    #ifdef        Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
     case         Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_CODE:
               prop->atv_sound_agc_limit.max_gain = (data >> Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_LSB) & Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MAX_GAIN_MASK;
               prop->atv_sound_agc_limit.min_gain = (data >> Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_LSB) & Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_MIN_GAIN_MASK;
     break;
    #endif /*     Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si21XXC_ATV_SOUND_AGC_SPEED_PROP
     case         Si21XXC_ATV_SOUND_AGC_SPEED_PROP_CODE:
               prop->atv_sound_agc_speed.system_l      = (data >> Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_LSB     ) & Si21XXC_ATV_SOUND_AGC_SPEED_PROP_SYSTEM_L_MASK;
               prop->atv_sound_agc_speed.other_systems = (data >> Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_LSB) & Si21XXC_ATV_SOUND_AGC_SPEED_PROP_OTHER_SYSTEMS_MASK;
     break;
    #endif /*     Si21XXC_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si21XXC_ATV_VIDEO_EQUALIZER_PROP
     case         Si21XXC_ATV_VIDEO_EQUALIZER_PROP_CODE:
               prop->atv_video_equalizer.slope = (data >> Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE_LSB) & Si21XXC_ATV_VIDEO_EQUALIZER_PROP_SLOPE_MASK;
     break;
    #endif /*     Si21XXC_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si21XXC_ATV_VIDEO_MODE_PROP
     case         Si21XXC_ATV_VIDEO_MODE_PROP_CODE:
               prop->atv_video_mode.video_sys     = (data >> Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_LSB    ) & Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_MASK;
               prop->atv_video_mode.color         = (data >> Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_LSB        ) & Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_MASK;
               prop->atv_video_mode.invert_signal = (data >> Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_LSB) & Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_MASK;
     break;
    #endif /*     Si21XXC_ATV_VIDEO_MODE_PROP */
    #ifdef        Si21XXC_ATV_VSNR_CAP_PROP
     case         Si21XXC_ATV_VSNR_CAP_PROP_CODE:
               prop->atv_vsnr_cap.atv_vsnr_cap = (data >> Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_LSB) & Si21XXC_ATV_VSNR_CAP_PROP_ATV_VSNR_CAP_MASK;
     break;
    #endif /*     Si21XXC_ATV_VSNR_CAP_PROP */
    #ifdef        Si21XXC_CRYSTAL_TRIM_PROP
     case         Si21XXC_CRYSTAL_TRIM_PROP_CODE:
               prop->crystal_trim.xo_cap = (data >> Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP_LSB) & Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP_MASK;
     break;
    #endif /*     Si21XXC_CRYSTAL_TRIM_PROP */
    #ifdef        Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
     case         Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_CODE:
               prop->dtv_agc_auto_freeze.thld    = (data >> Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD_LSB   ) & Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_THLD_MASK;
               prop->dtv_agc_auto_freeze.timeout = (data >> Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_LSB) & Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_TIMEOUT_MASK;
     break;
    #endif /*     Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef        Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
     case         Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_CODE:
               prop->dtv_agc_freeze_input.level = (data >> Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LSB) & Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_MASK;
               prop->dtv_agc_freeze_input.pin   = (data >> Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN_LSB  ) & Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN_MASK;
     break;
    #endif /*     Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si21XXC_DTV_AGC_SPEED_PROP
     case         Si21XXC_DTV_AGC_SPEED_PROP_CODE:
               prop->dtv_agc_speed.if_agc_speed = (data >> Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               prop->dtv_agc_speed.agc_decim    = (data >> Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si21XXC_DTV_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_CONFIG_IF_PORT_PROP
     case         Si21XXC_DTV_CONFIG_IF_PORT_PROP_CODE:
               prop->dtv_config_if_port.dtv_out_type   = (data >> Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LSB  ) & Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_MASK;
               prop->dtv_config_if_port.dtv_agc_source = (data >> Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_LSB) & Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_MASK;
     break;
    #endif /*     Si21XXC_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si21XXC_DTV_EXT_AGC_PROP
     case         Si21XXC_DTV_EXT_AGC_PROP_CODE:
               prop->dtv_ext_agc.min_10mv = (data >> Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV_LSB) & Si21XXC_DTV_EXT_AGC_PROP_MIN_10MV_MASK;
               prop->dtv_ext_agc.max_10mv = (data >> Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV_LSB) & Si21XXC_DTV_EXT_AGC_PROP_MAX_10MV_MASK;
     break;
    #endif /*     Si21XXC_DTV_EXT_AGC_PROP */
    #ifdef        Si21XXC_DTV_IEN_PROP
     case         Si21XXC_DTV_IEN_PROP_CODE:
               prop->dtv_ien.chlien = (data >> Si21XXC_DTV_IEN_PROP_CHLIEN_LSB) & Si21XXC_DTV_IEN_PROP_CHLIEN_MASK;
     break;
    #endif /*     Si21XXC_DTV_IEN_PROP */
    #ifdef        Si21XXC_DTV_IF_AGC_SPEED_PROP
     case         Si21XXC_DTV_IF_AGC_SPEED_PROP_CODE:
               prop->dtv_if_agc_speed.attack = (data >> Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK_LSB) & Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK_MASK;
               prop->dtv_if_agc_speed.decay  = (data >> Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY_LSB ) & Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY_MASK;
     break;
    #endif /*     Si21XXC_DTV_IF_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
     case         Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_CODE:
               prop->dtv_initial_agc_speed.if_agc_speed = (data >> Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_LSB) & Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_MASK;
               prop->dtv_initial_agc_speed.agc_decim    = (data >> Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_LSB   ) & Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_MASK;
     break;
    #endif /*     Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
               prop->dtv_initial_agc_speed_period.period = (data >> Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_LSB) & Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_PERIOD_MASK;
     break;
    #endif /*     Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si21XXC_DTV_INTERNAL_ZIF_PROP
     case         Si21XXC_DTV_INTERNAL_ZIF_PROP_CODE:
               prop->dtv_internal_zif.atsc   = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC_LSB  ) & Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC_MASK;
               prop->dtv_internal_zif.qam_us = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US_LSB) & Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US_MASK;
               prop->dtv_internal_zif.dvbt   = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT_LSB  ) & Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT_MASK;
               prop->dtv_internal_zif.dvbc   = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC_LSB  ) & Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC_MASK;
               prop->dtv_internal_zif.isdbt  = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT_LSB ) & Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT_MASK;
               prop->dtv_internal_zif.isdbc  = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC_LSB ) & Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC_MASK;
               prop->dtv_internal_zif.dtmb   = (data >> Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB_LSB  ) & Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB_MASK;
     break;
    #endif /*     Si21XXC_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si21XXC_DTV_INT_SENSE_PROP
     case         Si21XXC_DTV_INT_SENSE_PROP_CODE:
               prop->dtv_int_sense.chlnegen = (data >> Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN_LSB) & Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN_MASK;
               prop->dtv_int_sense.chlposen = (data >> Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN_LSB) & Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN_MASK;
     break;
    #endif /*     Si21XXC_DTV_INT_SENSE_PROP */
    #ifdef        Si21XXC_DTV_LIF_FREQ_PROP
     case         Si21XXC_DTV_LIF_FREQ_PROP_CODE:
               prop->dtv_lif_freq.offset = (data >> Si21XXC_DTV_LIF_FREQ_PROP_OFFSET_LSB) & Si21XXC_DTV_LIF_FREQ_PROP_OFFSET_MASK;
     break;
    #endif /*     Si21XXC_DTV_LIF_FREQ_PROP */
    #ifdef        Si21XXC_DTV_LIF_OUT_PROP
     case         Si21XXC_DTV_LIF_OUT_PROP_CODE:
               prop->dtv_lif_out.offset = (data >> Si21XXC_DTV_LIF_OUT_PROP_OFFSET_LSB) & Si21XXC_DTV_LIF_OUT_PROP_OFFSET_MASK;
               prop->dtv_lif_out.amp    = (data >> Si21XXC_DTV_LIF_OUT_PROP_AMP_LSB   ) & Si21XXC_DTV_LIF_OUT_PROP_AMP_MASK;
     break;
    #endif /*     Si21XXC_DTV_LIF_OUT_PROP */
    #ifdef        Si21XXC_DTV_MODE_PROP
     case         Si21XXC_DTV_MODE_PROP_CODE:
               prop->dtv_mode.bw              = (data >> Si21XXC_DTV_MODE_PROP_BW_LSB             ) & Si21XXC_DTV_MODE_PROP_BW_MASK;
               prop->dtv_mode.modulation      = (data >> Si21XXC_DTV_MODE_PROP_MODULATION_LSB     ) & Si21XXC_DTV_MODE_PROP_MODULATION_MASK;
               prop->dtv_mode.invert_spectrum = (data >> Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM_LSB) & Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM_MASK;
     break;
    #endif /*     Si21XXC_DTV_MODE_PROP */
    #ifdef        Si21XXC_DTV_RF_AGC_SPEED_PROP
     case         Si21XXC_DTV_RF_AGC_SPEED_PROP_CODE:
               prop->dtv_rf_agc_speed.attack = (data >> Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK_LSB) & Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK_MASK;
               prop->dtv_rf_agc_speed.decay  = (data >> Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY_LSB ) & Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY_MASK;
     break;
    #endif /*     Si21XXC_DTV_RF_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_RF_TOP_PROP
     case         Si21XXC_DTV_RF_TOP_PROP_CODE:
               prop->dtv_rf_top.dtv_rf_top = (data >> Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB) & Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK;
     break;
    #endif /*     Si21XXC_DTV_RF_TOP_PROP */
    #ifdef        Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
               prop->dtv_rsq_rssi_threshold.lo = (data >> Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_LSB) & Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_LO_MASK;
               prop->dtv_rsq_rssi_threshold.hi = (data >> Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_LSB) & Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_HI_MASK;
     break;
    #endif /*     Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */
     #ifdef        Si21XXC_DTV_WB_AGC_SPEED_PROP
     case         Si21XXC_DTV_WB_AGC_SPEED_PROP_CODE:
               prop->dtv_wb_agc_speed.attack = (data >> Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK_LSB) & Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK_MASK;
               prop->dtv_wb_agc_speed.decay  = (data >> Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY_LSB ) & Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY_MASK;
     break;
    #endif /*     Si21XXC_DTV_WB_AGC_SPEED_PROP */
    #ifdef        Si21XXC_MASTER_IEN_PROP
     case         Si21XXC_MASTER_IEN_PROP_CODE:
               prop->master_ien.tunien = (data >> Si21XXC_MASTER_IEN_PROP_TUNIEN_LSB) & Si21XXC_MASTER_IEN_PROP_TUNIEN_MASK;
               prop->master_ien.atvien = (data >> Si21XXC_MASTER_IEN_PROP_ATVIEN_LSB) & Si21XXC_MASTER_IEN_PROP_ATVIEN_MASK;
               prop->master_ien.dtvien = (data >> Si21XXC_MASTER_IEN_PROP_DTVIEN_LSB) & Si21XXC_MASTER_IEN_PROP_DTVIEN_MASK;
               prop->master_ien.errien = (data >> Si21XXC_MASTER_IEN_PROP_ERRIEN_LSB) & Si21XXC_MASTER_IEN_PROP_ERRIEN_MASK;
               prop->master_ien.ctsien = (data >> Si21XXC_MASTER_IEN_PROP_CTSIEN_LSB) & Si21XXC_MASTER_IEN_PROP_CTSIEN_MASK;
     break;
    #endif /*     Si21XXC_MASTER_IEN_PROP */
    #ifdef        Si21XXC_TUNER_BLOCKED_VCO_PROP
     case         Si21XXC_TUNER_BLOCKED_VCO_PROP_CODE:
               prop->tuner_blocked_vco.vco_code = (data >> Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE_LSB) & Si21XXC_TUNER_BLOCKED_VCO_PROP_VCO_CODE_MASK;
     break;
    #endif /*     Si21XXC_TUNER_BLOCKED_VCO_PROP */
     #ifdef        Si21XXC_TUNER_IEN_PROP
     case         Si21XXC_TUNER_IEN_PROP_CODE:
               prop->tuner_ien.tcien    = (data >> Si21XXC_TUNER_IEN_PROP_TCIEN_LSB   ) & Si21XXC_TUNER_IEN_PROP_TCIEN_MASK;
               prop->tuner_ien.rssilien = (data >> Si21XXC_TUNER_IEN_PROP_RSSILIEN_LSB) & Si21XXC_TUNER_IEN_PROP_RSSILIEN_MASK;
               prop->tuner_ien.rssihien = (data >> Si21XXC_TUNER_IEN_PROP_RSSIHIEN_LSB) & Si21XXC_TUNER_IEN_PROP_RSSIHIEN_MASK;
     break;
    #endif /*     Si21XXC_TUNER_IEN_PROP */
    #ifdef        Si21XXC_TUNER_INT_SENSE_PROP
     case         Si21XXC_TUNER_INT_SENSE_PROP_CODE:
               prop->tuner_int_sense.tcnegen    = (data >> Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN_LSB   ) & Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN_MASK;
               prop->tuner_int_sense.rssilnegen = (data >> Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN_LSB) & Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN_MASK;
               prop->tuner_int_sense.rssihnegen = (data >> Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN_LSB) & Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN_MASK;
               prop->tuner_int_sense.tcposen    = (data >> Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN_LSB   ) & Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN_MASK;
               prop->tuner_int_sense.rssilposen = (data >> Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN_LSB) & Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN_MASK;
               prop->tuner_int_sense.rssihposen = (data >> Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN_LSB) & Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN_MASK;
     break;
    #endif /*     Si21XXC_TUNER_INT_SENSE_PROP */
    #ifdef        Si21XXC_TUNER_LO_INJECTION_PROP
     case         Si21XXC_TUNER_LO_INJECTION_PROP_CODE:
               prop->tuner_lo_injection.band_1 = (data >> Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1_LSB) & Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1_MASK;
               prop->tuner_lo_injection.band_2 = (data >> Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2_LSB) & Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2_MASK;
               prop->tuner_lo_injection.band_3 = (data >> Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3_LSB) & Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3_MASK;
     break;
    #endif /*     Si21XXC_TUNER_LO_INJECTION_PROP */
    #ifdef        Si21XXC_TUNER_RETURN_LOSS_PROP
     case         Si21XXC_TUNER_RETURN_LOSS_PROP_CODE:
               prop->tuner_return_loss.config = (data >> Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG_LSB) & Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG_MASK;
               prop->tuner_return_loss.mode   = (data >> Si21XXC_TUNER_RETURN_LOSS_PROP_MODE_LSB  ) & Si21XXC_TUNER_RETURN_LOSS_PROP_MODE_MASK;
     break;
    #endif /*     Si21XXC_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
     case         Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CODE:
               prop->tuner_return_loss_optimize.thld                = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_LSB               ) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_THLD_MASK;
               prop->tuner_return_loss_optimize.config              = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_LSB             ) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_MASK;
               prop->tuner_return_loss_optimize.engagement_delay    = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_LSB   ) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_ENGAGEMENT_DELAY_MASK;
               prop->tuner_return_loss_optimize.disengagement_delay = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_LSB) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_DISENGAGEMENT_DELAY_MASK;
     break;
    #endif /*     Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP */
    #ifdef        Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
     case         Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_CODE:
               prop->tuner_return_loss_optimize_2.thld             = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_LSB            ) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_THLD_MASK;
               prop->tuner_return_loss_optimize_2.window           = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_LSB          ) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_WINDOW_MASK;
               prop->tuner_return_loss_optimize_2.engagement_delay = (data >> Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_LSB) & Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_ENGAGEMENT_DELAY_MASK;
     break;
    #endif /*     Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */
    #ifdef        Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
     case         Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_CODE:
               prop->tuner_tf1_boundary_offset.tf1_boundary_offset = (data >> Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_LSB) & Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_TF1_BOUNDARY_OFFSET_MASK;
     break;
    #endif /*     Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */
    #ifdef        Si2190B_WIDE_BAND_ATT_THRS_PROP
     case         Si2190B_WIDE_BAND_ATT_THRS_PROP_CODE:
               prop->wide_band_att_thrs.wb_att_thrs = (data >> Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_LSB) & Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_MASK;
     break;
    #endif /*     Si2190B_WIDE_BAND_ATT_THRS_PROP */
    #ifdef        Si21XXC_XOUT_PROP
     case         Si21XXC_XOUT_PROP_CODE:
               prop->xout.amp = (data >> Si21XXC_XOUT_PROP_AMP_LSB) & Si21XXC_XOUT_PROP_AMP_MASK;
    break;
    #endif /*     Si21XXC_XOUT_PROP */
     default : return ERROR_Si21XXC_UNKNOWN_PROPERTY; break;
    }
    return NO_Si21XXC_ERROR;
  }
/***********************************************************************************************************************
  Si21XXC_storePropertiesDefaults function
  Use:        property defaults function
              Used to fill the propShadow structure with startup values.
  Parameter: *prop     the Si21XXC_PropObject structure

 |---------------------------------------------------------------------------------------------------------------------|
 | Do NOT change this code unless you really know what you're doing!                                                   |
 | It should reflect the part internal property settings after firmware download                                       |
 |---------------------------------------------------------------------------------------------------------------------|

 Returns:    void
 ***********************************************************************************************************************/
void          Si21XXC_storePropertiesDefaults (Si21XXC_PropObj   *prop) {
  SiTRACE("Si21XXC_storePropertiesDefaults\n");
#ifdef    Si21XXC_ATV_AFC_RANGE_PROP
  prop->atv_afc_range.range_khz              =  1000; /* (default  1000) */
#endif /* Si21XXC_ATV_AFC_RANGE_PROP */

#ifdef    Si21XXC_ATV_AGC_SPEED_PROP
  prop->atv_agc_speed.if_agc_speed           = Si21XXC_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO     ; /* (default 'AUTO') */
#endif /* Si21XXC_ATV_AGC_SPEED_PROP */

#ifdef    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
  prop->atv_agc_speed_low_rssi.if_agc_speed  = Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_IF_AGC_SPEED_158 ; /* (default '158') */
  prop->atv_agc_speed_low_rssi.thld          =  -128; /* (default  -128) */
#endif /* Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */

#ifdef    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
  prop->atv_artificial_snow.gain             =     0; /* (default     0) */
  prop->atv_artificial_snow.sound            = Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_SOUND_MUTE  ; /* (default 'MUTE') */
  prop->atv_artificial_snow.period           = Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_PERIOD_LONG ; /* (default 'LONG') */
  prop->atv_artificial_snow.offset           =     0; /* (default     0) */
#endif /* Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */

#ifdef    Si21XXC_ATV_AUDIO_MODE_PROP
  prop->atv_audio_mode.audio_sys             = Si21XXC_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT  ; /* (default 'DEFAULT') */
  prop->atv_audio_mode.chan_bw               = Si21XXC_ATV_AUDIO_MODE_PROP_CHAN_BW_DEFAULT    ; /* (default 'DEFAULT') */
#endif /* Si21XXC_ATV_AUDIO_MODE_PROP */

#ifdef    Si21XXC_ATV_CONFIG_IF_PORT_PROP
  prop->atv_config_if_port.atv_out_type      = Si21XXC_ATV_CONFIG_IF_PORT_PROP_ATV_OUT_TYPE_CVBS_IF2B_SOUND_IF2A ; /* (default 'CVBS_IF2B_SOUND_IF2A') */
#endif /* Si21XXC_ATV_CONFIG_IF_PORT_PROP */

#ifdef    Si2190B_ATV_CVBS_ATTENUATION_PROP
  prop->atv_cvbs_attenuation.threshold                  =     0; /* (default     0) */
  prop->atv_cvbs_attenuation.rate                       =     0; /* (default     0) */
  prop->atv_cvbs_attenuation.bw                         =     4; /* (default     4) */
#endif /* Si2190B_ATV_CVBS_ATTENUATION_PROP */

#ifdef    Si21XXC_ATV_CVBS_OUT_PROP
  prop->atv_cvbs_out.offset                  =    25; /* (default    25) */
  prop->atv_cvbs_out.amp                     =   200; /* (default   200) */
#endif /* Si21XXC_ATV_CVBS_OUT_PROP */

#ifdef    Si21XXC_ATV_CVBS_OUT_FINE_PROP
  prop->atv_cvbs_out_fine.offset             =     0; /* (default     0) */
  prop->atv_cvbs_out_fine.amp                =   100; /* (default   100) */
#endif /* Si21XXC_ATV_CVBS_OUT_FINE_PROP */

#ifdef    Si21XXC_ATV_IEN_PROP
  prop->atv_ien.chlien                       = Si21XXC_ATV_IEN_PROP_CHLIEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_ien.pclien                       = Si21XXC_ATV_IEN_PROP_PCLIEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_ien.dlien                        = Si21XXC_ATV_IEN_PROP_DLIEN_DISABLE   ; /* (default 'DISABLE') */
  prop->atv_ien.snrlien                      = Si21XXC_ATV_IEN_PROP_SNRLIEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_ien.snrhien                      = Si21XXC_ATV_IEN_PROP_SNRHIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si21XXC_ATV_IEN_PROP */

#ifdef    Si21XXC_ATV_INT_SENSE_PROP
  prop->atv_int_sense.chlnegen               = Si21XXC_ATV_INT_SENSE_PROP_CHLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_int_sense.pclnegen               = Si21XXC_ATV_INT_SENSE_PROP_PCLNEGEN_DISABLE  ; /* (default 'DISABLE') */
  prop->atv_int_sense.dlnegen                = Si21XXC_ATV_INT_SENSE_PROP_DLNEGEN_DISABLE   ; /* (default 'DISABLE') */
  prop->atv_int_sense.snrlnegen              = Si21XXC_ATV_INT_SENSE_PROP_SNRLNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_int_sense.snrhnegen              = Si21XXC_ATV_INT_SENSE_PROP_SNRHNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->atv_int_sense.chlposen               = Si21XXC_ATV_INT_SENSE_PROP_CHLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_int_sense.pclposen               = Si21XXC_ATV_INT_SENSE_PROP_PCLPOSEN_ENABLE   ; /* (default 'ENABLE') */
  prop->atv_int_sense.dlposen                = Si21XXC_ATV_INT_SENSE_PROP_DLPOSEN_ENABLE    ; /* (default 'ENABLE') */
  prop->atv_int_sense.snrlposen              = Si21XXC_ATV_INT_SENSE_PROP_SNRLPOSEN_ENABLE  ; /* (default 'ENABLE') */
  prop->atv_int_sense.snrhposen              = Si21XXC_ATV_INT_SENSE_PROP_SNRHPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si21XXC_ATV_INT_SENSE_PROP */

#ifdef    Si21XXC_ATV_PGA_TARGET_PROP
  prop->atv_pga_target.pga_target                       =     0; /* (default     0) */
  prop->atv_pga_target.override_enable                  = Si21XXC_ATV_PGA_TARGET_PROP_OVERRIDE_ENABLE_DISABLE ; /* (default 'DISABLE') */
#endif /* Si21XXC_ATV_PGA_TARGET_PROP */

#ifdef    Si21XXC_ATV_RF_TOP_PROP
  prop->atv_rf_top.atv_rf_top                = Si21XXC_ATV_RF_TOP_PROP_ATV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si21XXC_ATV_RF_TOP_PROP */

#ifdef    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
  prop->atv_rsq_rssi_threshold.lo            =   -70; /* (default   -70) */
  prop->atv_rsq_rssi_threshold.hi            =     0; /* (default     0) */
#endif /* Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
  prop->atv_rsq_snr_threshold.lo             =    25; /* (default    25) */
  prop->atv_rsq_snr_threshold.hi             =    45; /* (default    45) */
#endif /* Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */

#ifdef    Si21XXC_ATV_SIF_OUT_PROP
  prop->atv_sif_out.offset                   =   135; /* (default   135) */
  prop->atv_sif_out.amp                      =    60; /* (default    60) */
#endif /* Si21XXC_ATV_SIF_OUT_PROP */

#ifdef    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
  prop->atv_sound_agc_limit.max_gain         =    84; /* (default    84) */
  prop->atv_sound_agc_limit.min_gain         =   -84; /* (default   -84) */
#endif /* Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */

#ifdef    Si21XXC_ATV_SOUND_AGC_SPEED_PROP
  prop->atv_sound_agc_speed.system_l         =     5; /* (default     5) */
  prop->atv_sound_agc_speed.other_systems    =     4; /* (default     4) */
#endif /* Si21XXC_ATV_SOUND_AGC_SPEED_PROP */

#ifdef    Si21XXC_ATV_VIDEO_EQUALIZER_PROP
  prop->atv_video_equalizer.slope            =     0; /* (default     0) */
#endif /* Si21XXC_ATV_VIDEO_EQUALIZER_PROP */

#ifdef    Si21XXC_ATV_VIDEO_MODE_PROP
  prop->atv_video_mode.video_sys             = Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B            ; /* (default 'B') */
  prop->atv_video_mode.color                 = Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC         ; /* (default 'PAL_NTSC') */
  prop->atv_video_mode.invert_signal         = Si21XXC_ATV_VIDEO_MODE_PROP_INVERT_SIGNAL_NORMAL   ; /* (default 'NORMAL') */
#endif /* Si21XXC_ATV_VIDEO_MODE_PROP */

#ifdef    Si21XXC_ATV_VSNR_CAP_PROP
  prop->atv_vsnr_cap.atv_vsnr_cap            =     0; /* (default     0) */
#endif /* Si21XXC_ATV_VSNR_CAP_PROP */

#ifdef    Si21XXC_CRYSTAL_TRIM_PROP
  prop->crystal_trim.xo_cap                  = Si21XXC_CRYSTAL_TRIM_PROP_XO_CAP_6P7PF ; /* (default '6p7pF') */
#endif /* Si21XXC_CRYSTAL_TRIM_PROP */

#ifdef    Si21XXC_MASTER_IEN_PROP
  prop->master_ien.tunien                    = Si21XXC_MASTER_IEN_PROP_TUNIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.atvien                    = Si21XXC_MASTER_IEN_PROP_ATVIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.dtvien                    = Si21XXC_MASTER_IEN_PROP_DTVIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.errien                    = Si21XXC_MASTER_IEN_PROP_ERRIEN_OFF ; /* (default 'OFF') */
  prop->master_ien.ctsien                    = Si21XXC_MASTER_IEN_PROP_CTSIEN_OFF ; /* (default 'OFF') */
#endif /* Si21XXC_MASTER_IEN_PROP */

#ifdef    Si21XXC_XOUT_PROP
  prop->xout.amp                             = Si21XXC_XOUT_PROP_AMP_HIGH ; /* (default 'HIGH') */
#endif /* Si21XXC_XOUT_PROP */

#ifdef    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
  prop->dtv_agc_auto_freeze.thld             =   255; /* (default   255) */
  prop->dtv_agc_auto_freeze.timeout          =     1; /* (default     1) */
#endif /* Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */

#ifdef    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
  prop->dtv_agc_freeze_input.level           = Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_LEVEL_LOW  ; /* (default 'LOW') */
  prop->dtv_agc_freeze_input.pin             = Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_PIN_NONE   ; /* (default 'NONE') */
#endif /* Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */

#ifdef    Si21XXC_DTV_AGC_SPEED_PROP
  prop->dtv_agc_speed.if_agc_speed           = Si21XXC_DTV_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_agc_speed.agc_decim              = Si21XXC_DTV_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si21XXC_DTV_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_CONFIG_IF_PORT_PROP
  prop->dtv_config_if_port.dtv_out_type      = Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_OUT_TYPE_LIF_IF1    ; /* (default 'LIF_IF1') */
  prop->dtv_config_if_port.dtv_agc_source    = Si21XXC_DTV_CONFIG_IF_PORT_PROP_DTV_AGC_SOURCE_INTERNAL ; /* (default 'INTERNAL') */
#endif /* Si21XXC_DTV_CONFIG_IF_PORT_PROP */

#ifdef    Si21XXC_DTV_EXT_AGC_PROP
  prop->dtv_ext_agc.min_10mv                 =    50; /* (default    50) */
  prop->dtv_ext_agc.max_10mv                 =   200; /* (default   200) */
#endif /* Si21XXC_DTV_EXT_AGC_PROP */

#ifdef    Si21XXC_DTV_IEN_PROP
  prop->dtv_ien.chlien                       = Si21XXC_DTV_IEN_PROP_CHLIEN_ENABLE ; /* (default 'ENABLE') */
#endif /* Si21XXC_DTV_IEN_PROP */

#ifdef    Si21XXC_DTV_IF_AGC_SPEED_PROP
  prop->dtv_if_agc_speed.attack              = Si21XXC_DTV_IF_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_if_agc_speed.decay               = Si21XXC_DTV_IF_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si21XXC_DTV_IF_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
  prop->dtv_initial_agc_speed.if_agc_speed   = Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_IF_AGC_SPEED_AUTO ; /* (default 'AUTO') */
  prop->dtv_initial_agc_speed.agc_decim      = Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_AGC_DECIM_OFF     ; /* (default 'OFF') */
#endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
  prop->dtv_initial_agc_speed_period.period  =     0; /* (default     0) */
#endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */

#ifdef    Si21XXC_DTV_INTERNAL_ZIF_PROP
  prop->dtv_internal_zif.atsc                = Si21XXC_DTV_INTERNAL_ZIF_PROP_ATSC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.qam_us              = Si21XXC_DTV_INTERNAL_ZIF_PROP_QAM_US_ZIF ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbt                = Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBT_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dvbc                = Si21XXC_DTV_INTERNAL_ZIF_PROP_DVBC_ZIF   ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbt               = Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBT_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.isdbc               = Si21XXC_DTV_INTERNAL_ZIF_PROP_ISDBC_ZIF  ; /* (default 'ZIF') */
  prop->dtv_internal_zif.dtmb                = Si21XXC_DTV_INTERNAL_ZIF_PROP_DTMB_LIF   ; /* (default 'LIF') */
#endif /* Si21XXC_DTV_INTERNAL_ZIF_PROP */

#ifdef    Si21XXC_DTV_INT_SENSE_PROP
  prop->dtv_int_sense.chlnegen               = Si21XXC_DTV_INT_SENSE_PROP_CHLNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->dtv_int_sense.chlposen               = Si21XXC_DTV_INT_SENSE_PROP_CHLPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si21XXC_DTV_INT_SENSE_PROP */

#ifdef    Si21XXC_DTV_LIF_FREQ_PROP
  prop->dtv_lif_freq.offset                  =  5000; /* (default  5000) */
#endif /* Si21XXC_DTV_LIF_FREQ_PROP */

#ifdef    Si21XXC_DTV_LIF_OUT_PROP
  prop->dtv_lif_out.offset                   =   148; /* (default   148) */
  prop->dtv_lif_out.amp                      =    27; /* (default    27) */
#endif /* Si21XXC_DTV_LIF_OUT_PROP */

#ifdef    Si21XXC_DTV_MODE_PROP
  prop->dtv_mode.bw                          = Si21XXC_DTV_MODE_PROP_BW_BW_8MHZ              ; /* (default 'BW_8MHZ') */
  prop->dtv_mode.modulation                  = Si21XXC_DTV_MODE_PROP_MODULATION_DVBT         ; /* (default 'DVBT') */
  prop->dtv_mode.invert_spectrum             = Si21XXC_DTV_MODE_PROP_INVERT_SPECTRUM_NORMAL  ; /* (default 'NORMAL') */
#endif /* Si21XXC_DTV_MODE_PROP */

#ifdef    Si21XXC_DTV_RF_AGC_SPEED_PROP
  prop->dtv_rf_agc_speed.attack              =     Si21XXC_DTV_RF_AGC_SPEED_PROP_ATTACK_AUTO; /* (default     0) */
  prop->dtv_rf_agc_speed.decay               =     Si21XXC_DTV_RF_AGC_SPEED_PROP_DECAY_AUTO; /* (default     0) */
#endif /* Si21XXC_DTV_RF_AGC_SPEED_PROP */

#ifdef    Si21XXC_DTV_RF_TOP_PROP
  prop->dtv_rf_top.dtv_rf_top                = Si21XXC_DTV_RF_TOP_PROP_DTV_RF_TOP_AUTO ; /* (default 'AUTO') */
#endif /* Si21XXC_DTV_RF_TOP_PROP */

#ifdef    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
  prop->dtv_rsq_rssi_threshold.lo            =   -80; /* (default   -80) */
  prop->dtv_rsq_rssi_threshold.hi            =     0; /* (default     0) */
#endif /* Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */

#ifdef    Si21XXC_DTV_WB_AGC_SPEED_PROP
  prop->dtv_wb_agc_speed.attack              = Si21XXC_DTV_WB_AGC_SPEED_PROP_ATTACK_AUTO ; /* (default 'AUTO') */
  prop->dtv_wb_agc_speed.decay               = Si21XXC_DTV_WB_AGC_SPEED_PROP_DECAY_AUTO  ; /* (default 'AUTO') */
#endif /* Si21XXC_DTV_WB_AGC_SPEED_PROP */

#ifdef    Si21XXC_TUNER_BLOCKED_VCO_PROP
  prop->tuner_blocked_vco.vco_code           = 0x8000; /* (default 0x8000) */
#endif /* Si21XXC_TUNER_BLOCKED_VCO_PROP */

#ifdef    Si21XXC_TUNER_IEN_PROP
  prop->tuner_ien.tcien                      = Si21XXC_TUNER_IEN_PROP_TCIEN_ENABLE     ; /* (default 'ENABLE') */
  prop->tuner_ien.rssilien                   = Si21XXC_TUNER_IEN_PROP_RSSILIEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_ien.rssihien                   = Si21XXC_TUNER_IEN_PROP_RSSIHIEN_DISABLE ; /* (default 'DISABLE') */
#endif /* Si21XXC_TUNER_IEN_PROP */

#ifdef    Si21XXC_TUNER_INT_SENSE_PROP
  prop->tuner_int_sense.tcnegen              = Si21XXC_TUNER_INT_SENSE_PROP_TCNEGEN_DISABLE    ; /* (default 'DISABLE') */
  prop->tuner_int_sense.rssilnegen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSILNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_int_sense.rssihnegen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSIHNEGEN_DISABLE ; /* (default 'DISABLE') */
  prop->tuner_int_sense.tcposen              = Si21XXC_TUNER_INT_SENSE_PROP_TCPOSEN_ENABLE     ; /* (default 'ENABLE') */
  prop->tuner_int_sense.rssilposen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSILPOSEN_ENABLE  ; /* (default 'ENABLE') */
  prop->tuner_int_sense.rssihposen           = Si21XXC_TUNER_INT_SENSE_PROP_RSSIHPOSEN_ENABLE  ; /* (default 'ENABLE') */
#endif /* Si21XXC_TUNER_INT_SENSE_PROP */

#ifdef    Si21XXC_TUNER_LO_INJECTION_PROP
  prop->tuner_lo_injection.band_1            = Si21XXC_TUNER_LO_INJECTION_PROP_BAND_1_HIGH_SIDE ; /* (default 'HIGH_SIDE') */
  prop->tuner_lo_injection.band_2            = Si21XXC_TUNER_LO_INJECTION_PROP_BAND_2_LOW_SIDE  ; /* (default 'LOW_SIDE') */
  prop->tuner_lo_injection.band_3            = Si21XXC_TUNER_LO_INJECTION_PROP_BAND_3_LOW_SIDE  ; /* (default 'LOW_SIDE') */
#endif /* Si21XXC_TUNER_LO_INJECTION_PROP */

#ifdef    Si21XXC_TUNER_RETURN_LOSS_PROP
  prop->tuner_return_loss.config             = Si21XXC_TUNER_RETURN_LOSS_PROP_CONFIG_127         ; /* (default '127') */
  prop->tuner_return_loss.mode               = Si21XXC_TUNER_RETURN_LOSS_PROP_MODE_TERRESTRIAL   ; /* (default 'TERRESTRIAL') */
#endif /* Si21XXC_TUNER_RETURN_LOSS_PROP */

#ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
  prop->tuner_return_loss_optimize.thld                 =     0; /* (default     0) */
  prop->tuner_return_loss_optimize.config               = Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE              ; /* (default 'DISABLE') */
  prop->tuner_return_loss_optimize.engagement_delay     =     7; /* (default     7) */
  prop->tuner_return_loss_optimize.disengagement_delay  =    10; /* (default    10) */
#endif /* Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP */

#ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
  prop->tuner_return_loss_optimize_2.thld               =    31; /* (default    31) */
  prop->tuner_return_loss_optimize_2.window             =     0; /* (default     0) */
  prop->tuner_return_loss_optimize_2.engagement_delay   =    15; /* (default    15) */
#endif /* Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */

#ifdef    Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
  prop->tuner_tf1_boundary_offset.tf1_boundary_offset   =     0; /* (default     0) */
#endif /* Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */

#ifdef    Si2190B_WIDE_BAND_ATT_THRS_PROP
  prop->wide_band_att_thrs.wb_att_thrs                  = Si2190B_WIDE_BAND_ATT_THRS_PROP_WB_ATT_THRS_AUTO ; /* (default 'AUTO') */
#endif /* Si2190B_WIDE_BAND_ATT_THRS_PROP */
}
#ifdef    Si21XXC_GET_PROPERTY_STRING
/***********************************************************************************************************************
  Si21XXC_L1_PropertyText function
  Use:        property text function
              Used to turn the property data into clear text.
  Parameter: *prop     the Si21XXC property structure (containing all properties)
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string (usually declared with a size of 1000 bytes)
  Returns:    NO_Si21XXC_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_PropertyText          (Si21XXC_PropObj   *prop, unsigned int prop_code, const char *separator, char *msg) {
    switch (prop_code) {
    #ifdef        Si21XXC_ATV_AFC_RANGE_PROP
     case         Si21XXC_ATV_AFC_RANGE_PROP_CODE:
      safe_sprintf(msg,"ATV_AFC_RANGE");
       safe_strcat(msg,separator); safe_strcat(msg,"-RANGE_KHZ "); safe_sprintf(msg,"%s%d", msg, prop->atv_afc_range.range_khz);
     break;
    #endif /*     Si21XXC_ATV_AFC_RANGE_PROP */
    #ifdef        Si21XXC_ATV_AGC_SPEED_PROP
     case         Si21XXC_ATV_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"ATV_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->atv_agc_speed.if_agc_speed ==     0) safe_strcat(msg,"AUTO   ");
      else if  (prop->atv_agc_speed.if_agc_speed ==    89) safe_strcat(msg,"89     ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   105) safe_strcat(msg,"105    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   121) safe_strcat(msg,"121    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   137) safe_strcat(msg,"137    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   158) safe_strcat(msg,"158    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   172) safe_strcat(msg,"172    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   178) safe_strcat(msg,"178    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   185) safe_strcat(msg,"185    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   196) safe_strcat(msg,"196    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   206) safe_strcat(msg,"206    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   216) safe_strcat(msg,"216    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   219) safe_strcat(msg,"219    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   222) safe_strcat(msg,"222    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   223) safe_strcat(msg,"223    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   248) safe_strcat(msg,"248    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   250) safe_strcat(msg,"250    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==   251) safe_strcat(msg,"251    ");
      else if  (prop->atv_agc_speed.if_agc_speed ==     1) safe_strcat(msg,"CUSTOM ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->atv_agc_speed.if_agc_speed);
     break;
    #endif /*     Si21XXC_ATV_AGC_SPEED_PROP */
    #ifdef        Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
     case         Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP_CODE:
      safe_sprintf(msg,"ATV_AGC_SPEED_LOW_RSSI");
       safe_strcat(msg,separator); safe_strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==    89) safe_strcat(msg,"89     ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   105) safe_strcat(msg,"105    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   121) safe_strcat(msg,"121    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   137) safe_strcat(msg,"137    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   158) safe_strcat(msg,"158    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   172) safe_strcat(msg,"172    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   178) safe_strcat(msg,"178    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   185) safe_strcat(msg,"185    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   196) safe_strcat(msg,"196    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   206) safe_strcat(msg,"206    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   216) safe_strcat(msg,"216    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   219) safe_strcat(msg,"219    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   222) safe_strcat(msg,"222    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   223) safe_strcat(msg,"223    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   248) safe_strcat(msg,"248    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   250) safe_strcat(msg,"250    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==   251) safe_strcat(msg,"251    ");
      else if  (prop->atv_agc_speed_low_rssi.if_agc_speed ==     1) safe_strcat(msg,"CUSTOM ");
      else                                                         safe_sprintf(msg,"%s%d", msg, prop->atv_agc_speed_low_rssi.if_agc_speed);
       safe_strcat(msg,separator); safe_strcat(msg,"-THLD "); safe_sprintf(msg,"%s%d", msg, prop->atv_agc_speed_low_rssi.thld);
     break;
    #endif /*     Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef        Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
     case         Si21XXC_ATV_ARTIFICIAL_SNOW_PROP_CODE:
      safe_sprintf(msg,"ATV_ARTIFICIAL_SNOW");
       safe_strcat(msg,separator); safe_strcat(msg,"-GAIN ");
           if  (prop->atv_artificial_snow.gain   ==     1) safe_strcat(msg,"0DB  ");
      else if  (prop->atv_artificial_snow.gain   ==     2) safe_strcat(msg,"6DB  ");
      else if  (prop->atv_artificial_snow.gain   ==     3) safe_strcat(msg,"12DB ");
      else if  (prop->atv_artificial_snow.gain   ==     4) safe_strcat(msg,"18DB ");
      else if  (prop->atv_artificial_snow.gain   ==     5) safe_strcat(msg,"24DB ");
      else if  (prop->atv_artificial_snow.gain   ==     6) safe_strcat(msg,"30DB ");
      else if  (prop->atv_artificial_snow.gain   ==     7) safe_strcat(msg,"36DB ");
      else if  (prop->atv_artificial_snow.gain   ==     8) safe_strcat(msg,"42DB ");
      else if  (prop->atv_artificial_snow.gain   ==     9) safe_strcat(msg,"OFF  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.gain);
       safe_strcat(msg,separator); safe_strcat(msg,"-SOUND ");
           if  (prop->atv_artificial_snow.sound  ==     0) safe_strcat(msg,"MUTE         ");
      else if  (prop->atv_artificial_snow.sound  ==     1) safe_strcat(msg,"6DB          ");
      else if  (prop->atv_artificial_snow.sound  ==     2) safe_strcat(msg,"12DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     3) safe_strcat(msg,"18DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     4) safe_strcat(msg,"24DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     5) safe_strcat(msg,"30DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     6) safe_strcat(msg,"36DB         ");
      else if  (prop->atv_artificial_snow.sound  ==     7) safe_strcat(msg,"PASS_THROUGH ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.sound);
       safe_strcat(msg,separator); safe_strcat(msg,"-PERIOD ");
           if  (prop->atv_artificial_snow.period ==     0) safe_strcat(msg,"LONG  ");
      else if  (prop->atv_artificial_snow.period ==     1) safe_strcat(msg,"SHORT ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.period);
       safe_strcat(msg,separator); safe_strcat(msg,"-OFFSET "); safe_sprintf(msg,"%s%d", msg, prop->atv_artificial_snow.offset);
     break;
    #endif /*     Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef        Si21XXC_ATV_AUDIO_MODE_PROP
     case         Si21XXC_ATV_AUDIO_MODE_PROP_CODE:
      safe_sprintf(msg,"ATV_AUDIO_MODE");
       safe_strcat(msg,separator); safe_strcat(msg,"-AUDIO_SYS ");
           if  (prop->atv_audio_mode.audio_sys ==     0) safe_strcat(msg,"DEFAULT         ");
      else if  (prop->atv_audio_mode.audio_sys ==     1) safe_strcat(msg,"MONO            ");
      else if  (prop->atv_audio_mode.audio_sys ==     2) safe_strcat(msg,"MONO_NICAM      ");
      else if  (prop->atv_audio_mode.audio_sys ==     3) safe_strcat(msg,"A2              ");
      else if  (prop->atv_audio_mode.audio_sys ==     4) safe_strcat(msg,"A2_DK2          ");
      else if  (prop->atv_audio_mode.audio_sys ==     5) safe_strcat(msg,"A2_DK3          ");
      else if  (prop->atv_audio_mode.audio_sys ==     6) safe_strcat(msg,"BTSC            ");
      else if  (prop->atv_audio_mode.audio_sys ==     7) safe_strcat(msg,"EIAJ            ");
      else if  (prop->atv_audio_mode.audio_sys ==     8) safe_strcat(msg,"SCAN            ");
      else if  (prop->atv_audio_mode.audio_sys ==     9) safe_strcat(msg,"A2_DK4          ");
      else if  (prop->atv_audio_mode.audio_sys ==    10) safe_strcat(msg,"WIDE_SCAN       ");
      else if  (prop->atv_audio_mode.audio_sys ==    11) safe_strcat(msg,"MONO_NICAM_6DB  ");
      else if  (prop->atv_audio_mode.audio_sys ==    12) safe_strcat(msg,"MONO_NICAM_10DB ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->atv_audio_mode.audio_sys);
       safe_strcat(msg,separator); safe_strcat(msg,"-CHAN_BW ");
           if  (prop->atv_audio_mode.chan_bw   ==     0) safe_strcat(msg,"DEFAULT        ");
      else if  (prop->atv_audio_mode.chan_bw   ==     1) safe_strcat(msg,"4X_OVERMOD     ");
      else if  (prop->atv_audio_mode.chan_bw   ==     2) safe_strcat(msg,"8X_OVERMOD     ");
      else if  (prop->atv_audio_mode.chan_bw   ==     3) safe_strcat(msg,"12X_OVERMOD    ");
      else if  (prop->atv_audio_mode.chan_bw   ==     4) safe_strcat(msg,"7P5_KHZ_OFFSET ");
      else if  (prop->atv_audio_mode.chan_bw   ==     5) safe_strcat(msg,"15_KHZ_OFFSET  ");
      else if  (prop->atv_audio_mode.chan_bw   ==     6) safe_strcat(msg,"30_KHZ_OFFSET  ");
      else if  (prop->atv_audio_mode.chan_bw   ==     7) safe_strcat(msg,"75_KHZ_OFFSET  ");
      else if  (prop->atv_audio_mode.chan_bw   ==     8) safe_strcat(msg,"150_KHZ_OFFSET ");
      else if  (prop->atv_audio_mode.chan_bw   ==     9) safe_strcat(msg,"CUSTOM         ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->atv_audio_mode.chan_bw);
     break;
    #endif /*     Si21XXC_ATV_AUDIO_MODE_PROP */
    #ifdef        Si21XXC_ATV_CONFIG_IF_PORT_PROP
     case         Si21XXC_ATV_CONFIG_IF_PORT_PROP_CODE:
      safe_sprintf(msg,"ATV_CONFIG_IF_PORT");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATV_OUT_TYPE ");
           if  (prop->atv_config_if_port.atv_out_type ==     0) safe_strcat(msg,"CVBS_IF2B_SOUND_IF2A ");
      else if  (prop->atv_config_if_port.atv_out_type ==     8) safe_strcat(msg,"LIF_DIFF_IF1         ");
      else if  (prop->atv_config_if_port.atv_out_type ==    10) safe_strcat(msg,"LIF_DIFF_IF2         ");
      else if  (prop->atv_config_if_port.atv_out_type ==    12) safe_strcat(msg,"LIF_SE_IF1A          ");
      else if  (prop->atv_config_if_port.atv_out_type ==    14) safe_strcat(msg,"LIF_SE_IF2A          ");
      else                                                     safe_sprintf(msg,"%s%d", msg, prop->atv_config_if_port.atv_out_type);
     break;
    #endif /*     Si21XXC_ATV_CONFIG_IF_PORT_PROP */
    #ifdef        Si2190B_ATV_CVBS_ATTENUATION_PROP
     case         Si2190B_ATV_CVBS_ATTENUATION_PROP_CODE:
      safe_sprintf(msg,"ATV_CVBS_ATTENUATION");
       safe_strcat(msg,separator); safe_strcat(msg,"-THRESHOLD "); safe_sprintf(msg,"%d", prop->atv_cvbs_attenuation.threshold);
       safe_strcat(msg,separator); safe_strcat(msg,"-RATE "); safe_sprintf(msg,"%d", prop->atv_cvbs_attenuation.rate);
       safe_strcat(msg,separator); safe_strcat(msg,"-BW "); safe_sprintf(msg,"%d", prop->atv_cvbs_attenuation.bw);
     break;
    #endif /*     Si2190B_ATV_CVBS_ATTENUATION_PROP */

    #ifdef        Si21XXC_ATV_CVBS_OUT_PROP
     case         Si21XXC_ATV_CVBS_OUT_PROP_CODE:
      safe_sprintf(msg,"ATV_CVBS_OUT");
       safe_strcat(msg,separator); safe_strcat(msg,"-OFFSET "); safe_sprintf(msg,"%s%d", msg, prop->atv_cvbs_out.offset);
       safe_strcat(msg,separator); safe_strcat(msg,"-AMP "); safe_sprintf(msg,"%s%d", msg, prop->atv_cvbs_out.amp);
     break;
    #endif /*     Si21XXC_ATV_CVBS_OUT_PROP */
    #ifdef        Si21XXC_ATV_CVBS_OUT_FINE_PROP
     case         Si21XXC_ATV_CVBS_OUT_FINE_PROP_CODE:
      safe_sprintf(msg,"ATV_CVBS_OUT_FINE");
       safe_strcat(msg,separator); safe_strcat(msg,"-OFFSET "); safe_sprintf(msg,"%s%d", msg, prop->atv_cvbs_out_fine.offset);
       safe_strcat(msg,separator); safe_strcat(msg,"-AMP "); safe_sprintf(msg,"%s%d", msg, prop->atv_cvbs_out_fine.amp);
     break;
    #endif /*     Si21XXC_ATV_CVBS_OUT_FINE_PROP */
    #ifdef        Si21XXC_ATV_IEN_PROP
     case         Si21XXC_ATV_IEN_PROP_CODE:
      safe_sprintf(msg,"ATV_IEN");
       safe_strcat(msg,separator); safe_strcat(msg,"-CHLIEN ");
           if  (prop->atv_ien.chlien  ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.chlien  ==     1) safe_strcat(msg,"ENABLE  ");
      else                                     safe_sprintf(msg,"%s%d", msg, prop->atv_ien.chlien);
       safe_strcat(msg,separator); safe_strcat(msg,"-PCLIEN ");
           if  (prop->atv_ien.pclien  ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.pclien  ==     1) safe_strcat(msg,"ENABLE  ");
      else                                     safe_sprintf(msg,"%s%d", msg, prop->atv_ien.pclien);
       safe_strcat(msg,separator); safe_strcat(msg,"-DLIEN ");
           if  (prop->atv_ien.dlien   ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.dlien   ==     1) safe_strcat(msg,"ENABLE  ");
      else                                     safe_sprintf(msg,"%s%d", msg, prop->atv_ien.dlien);
       safe_strcat(msg,separator); safe_strcat(msg,"-SNRLIEN ");
           if  (prop->atv_ien.snrlien ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.snrlien ==     1) safe_strcat(msg,"ENABLE  ");
      else                                     safe_sprintf(msg,"%s%d", msg, prop->atv_ien.snrlien);
       safe_strcat(msg,separator); safe_strcat(msg,"-SNRHIEN ");
           if  (prop->atv_ien.snrhien ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_ien.snrhien ==     1) safe_strcat(msg,"ENABLE  ");
      else                                     safe_sprintf(msg,"%s%d", msg, prop->atv_ien.snrhien);
     break;
    #endif /*     Si21XXC_ATV_IEN_PROP */
    #ifdef        Si21XXC_ATV_INT_SENSE_PROP
     case         Si21XXC_ATV_INT_SENSE_PROP_CODE:
      safe_sprintf(msg,"ATV_INT_SENSE");
       safe_strcat(msg,separator); safe_strcat(msg,"-CHLNEGEN ");
           if  (prop->atv_int_sense.chlnegen  ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.chlnegen  ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.chlnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-PCLNEGEN ");
           if  (prop->atv_int_sense.pclnegen  ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.pclnegen  ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.pclnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-DLNEGEN ");
           if  (prop->atv_int_sense.dlnegen   ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.dlnegen   ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.dlnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-SNRLNEGEN ");
           if  (prop->atv_int_sense.snrlnegen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrlnegen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrlnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-SNRHNEGEN ");
           if  (prop->atv_int_sense.snrhnegen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrhnegen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrhnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-CHLPOSEN ");
           if  (prop->atv_int_sense.chlposen  ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.chlposen  ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.chlposen);
       safe_strcat(msg,separator); safe_strcat(msg,"-PCLPOSEN ");
           if  (prop->atv_int_sense.pclposen  ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.pclposen  ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.pclposen);
       safe_strcat(msg,separator); safe_strcat(msg,"-DLPOSEN ");
           if  (prop->atv_int_sense.dlposen   ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.dlposen   ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.dlposen);
       safe_strcat(msg,separator); safe_strcat(msg,"-SNRLPOSEN ");
           if  (prop->atv_int_sense.snrlposen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrlposen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrlposen);
       safe_strcat(msg,separator); safe_strcat(msg,"-SNRHPOSEN ");
           if  (prop->atv_int_sense.snrhposen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_int_sense.snrhposen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->atv_int_sense.snrhposen);
     break;
    #endif /*     Si21XXC_ATV_INT_SENSE_PROP */
    #ifdef        Si21XXC_ATV_PGA_TARGET_PROP
     case         Si21XXC_ATV_PGA_TARGET_PROP_CODE:
      safe_sprintf(msg,"ATV_PGA_TARGET");
       safe_strcat(msg,separator); safe_strcat(msg,"-PGA_TARGET "); safe_sprintf(msg,"%d", prop->atv_pga_target.pga_target);
       safe_strcat(msg,separator); safe_strcat(msg,"-OVERRIDE_ENABLE ");
           if  (prop->atv_pga_target.override_enable ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->atv_pga_target.override_enable ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                    safe_sprintf(msg,"%s%d", msg,prop->atv_pga_target.override_enable);
     break;
    #endif /*     Si21XXC_ATV_PGA_TARGET_PROP */
    #ifdef        Si21XXC_ATV_RF_TOP_PROP
     case         Si21XXC_ATV_RF_TOP_PROP_CODE:
      safe_sprintf(msg,"ATV_RF_TOP");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATV_RF_TOP ");
           if  (prop->atv_rf_top.atv_rf_top ==     0) safe_strcat(msg,"AUTO  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     1) safe_strcat(msg,"P5DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     2) safe_strcat(msg,"P4DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     3) safe_strcat(msg,"P3DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     4) safe_strcat(msg,"P2DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     5) safe_strcat(msg,"P1DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     6) safe_strcat(msg,"0DB   ");
      else if  (prop->atv_rf_top.atv_rf_top ==     7) safe_strcat(msg,"M1DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     8) safe_strcat(msg,"M2DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==     9) safe_strcat(msg,"M3DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    10) safe_strcat(msg,"M4DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    11) safe_strcat(msg,"M5DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    12) safe_strcat(msg,"M6DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    13) safe_strcat(msg,"M7DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    14) safe_strcat(msg,"M8DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    15) safe_strcat(msg,"M9DB  ");
      else if  (prop->atv_rf_top.atv_rf_top ==    16) safe_strcat(msg,"M10DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    17) safe_strcat(msg,"M11DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    18) safe_strcat(msg,"M12DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    19) safe_strcat(msg,"M13DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    20) safe_strcat(msg,"M14DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    21) safe_strcat(msg,"M15DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    22) safe_strcat(msg,"M16DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    23) safe_strcat(msg,"M17DB ");
      else if  (prop->atv_rf_top.atv_rf_top ==    24) safe_strcat(msg,"M18DB ");
      else                                           safe_sprintf(msg,"%s%d", msg, prop->atv_rf_top.atv_rf_top);
     break;
    #endif /*     Si21XXC_ATV_RF_TOP_PROP */
    #ifdef        Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
     case         Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      safe_sprintf(msg,"ATV_RSQ_RSSI_THRESHOLD");
       safe_strcat(msg,separator); safe_strcat(msg,"-LO "); safe_sprintf(msg,"%s%d", msg, prop->atv_rsq_rssi_threshold.lo);
       safe_strcat(msg,separator); safe_strcat(msg,"-HI "); safe_sprintf(msg,"%s%d", msg, prop->atv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
     case         Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP_CODE:
      safe_sprintf(msg,"ATV_RSQ_SNR_THRESHOLD");
       safe_strcat(msg,separator); safe_strcat(msg,"-LO "); safe_sprintf(msg,"%s%d", msg, prop->atv_rsq_snr_threshold.lo);
       safe_strcat(msg,separator); safe_strcat(msg,"-HI "); safe_sprintf(msg,"%s%d", msg, prop->atv_rsq_snr_threshold.hi);
     break;
    #endif /*     Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef        Si21XXC_ATV_SIF_OUT_PROP
     case         Si21XXC_ATV_SIF_OUT_PROP_CODE:
      safe_sprintf(msg,"ATV_SIF_OUT");
       safe_strcat(msg,separator); safe_strcat(msg,"-OFFSET "); safe_sprintf(msg,"%s%d", msg, prop->atv_sif_out.offset);
       safe_strcat(msg,separator); safe_strcat(msg,"-AMP "); safe_sprintf(msg,"%s%d", msg, prop->atv_sif_out.amp);
     break;
    #endif /*     Si21XXC_ATV_SIF_OUT_PROP */
    #ifdef        Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
     case         Si21XXC_ATV_SOUND_AGC_LIMIT_PROP_CODE:
      safe_sprintf(msg,"ATV_SOUND_AGC_LIMIT");
       safe_strcat(msg,separator); safe_strcat(msg,"-MAX_GAIN "); safe_sprintf(msg,"%s%d", msg, prop->atv_sound_agc_limit.max_gain);
       safe_strcat(msg,separator); safe_strcat(msg,"-MIN_GAIN "); safe_sprintf(msg,"%s%d", msg, prop->atv_sound_agc_limit.min_gain);
     break;
    #endif /*     Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef        Si21XXC_ATV_SOUND_AGC_SPEED_PROP
     case         Si21XXC_ATV_SOUND_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"ATV_SOUND_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-SYSTEM_L "); safe_sprintf(msg,"%s%d", msg, prop->atv_sound_agc_speed.system_l);
       safe_strcat(msg,separator); safe_strcat(msg,"-OTHER_SYSTEMS "); safe_sprintf(msg,"%s%d", msg, prop->atv_sound_agc_speed.other_systems);
     break;
    #endif /*     Si21XXC_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef        Si21XXC_ATV_VIDEO_EQUALIZER_PROP
     case         Si21XXC_ATV_VIDEO_EQUALIZER_PROP_CODE:
      safe_sprintf(msg,"ATV_VIDEO_EQUALIZER");
       safe_strcat(msg,separator); safe_strcat(msg,"-SLOPE "); safe_sprintf(msg,"%s%d", msg, prop->atv_video_equalizer.slope);
     break;
    #endif /*     Si21XXC_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef        Si21XXC_ATV_VIDEO_MODE_PROP
     case         Si21XXC_ATV_VIDEO_MODE_PROP_CODE:
      safe_sprintf(msg,"ATV_VIDEO_MODE");
       safe_strcat(msg,separator); safe_strcat(msg,"-VIDEO_SYS ");
           if  (prop->atv_video_mode.video_sys     ==     0) safe_strcat(msg,"B  ");
      else if  (prop->atv_video_mode.video_sys     ==     1) safe_strcat(msg,"GH ");
      else if  (prop->atv_video_mode.video_sys     ==     2) safe_strcat(msg,"M  ");
      else if  (prop->atv_video_mode.video_sys     ==     3) safe_strcat(msg,"N  ");
      else if  (prop->atv_video_mode.video_sys     ==     4) safe_strcat(msg,"I  ");
      else if  (prop->atv_video_mode.video_sys     ==     5) safe_strcat(msg,"DK ");
      else if  (prop->atv_video_mode.video_sys     ==     6) safe_strcat(msg,"L  ");
      else if  (prop->atv_video_mode.video_sys     ==     7) safe_strcat(msg,"LP ");
      else                                                  safe_sprintf(msg,"%s%d", msg, prop->atv_video_mode.video_sys);
       safe_strcat(msg,separator); safe_strcat(msg,"-COLOR ");
           if  (prop->atv_video_mode.color         ==     0) safe_strcat(msg,"PAL_NTSC ");
      else if  (prop->atv_video_mode.color         ==     1) safe_strcat(msg,"SECAM    ");
      else                                                  safe_sprintf(msg,"%s%d", msg, prop->atv_video_mode.color);
       safe_strcat(msg,separator); safe_strcat(msg,"-INVERT_SIGNAL ");
           if  (prop->atv_video_mode.invert_signal ==     0) safe_strcat(msg,"NORMAL   ");
      else if  (prop->atv_video_mode.invert_signal ==     1) safe_strcat(msg,"INVERTED ");
      else                                                  safe_sprintf(msg,"%s%d", msg, prop->atv_video_mode.invert_signal);
     break;
    #endif /*     Si21XXC_ATV_VIDEO_MODE_PROP */
    #ifdef        Si21XXC_ATV_VSNR_CAP_PROP
     case         Si21XXC_ATV_VSNR_CAP_PROP_CODE:
      safe_sprintf(msg,"ATV_VSNR_CAP");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATV_VSNR_CAP "); safe_sprintf(msg,"%s%d", msg, prop->atv_vsnr_cap.atv_vsnr_cap);
     break;
    #endif /*     Si21XXC_ATV_VSNR_CAP_PROP */
    #ifdef        Si21XXC_CRYSTAL_TRIM_PROP
     case         Si21XXC_CRYSTAL_TRIM_PROP_CODE:
      safe_sprintf(msg,"CRYSTAL_TRIM");
       safe_strcat(msg,separator); safe_strcat(msg,"-XO_CAP ");
           if  (prop->crystal_trim.xo_cap ==     0) safe_strcat(msg,"4p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==     1) safe_strcat(msg,"4p95pF ");
      else if  (prop->crystal_trim.xo_cap ==     2) safe_strcat(msg,"5p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==     3) safe_strcat(msg,"5p45pF ");
      else if  (prop->crystal_trim.xo_cap ==     4) safe_strcat(msg,"5p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==     5) safe_strcat(msg,"5p95pF ");
      else if  (prop->crystal_trim.xo_cap ==     6) safe_strcat(msg,"6p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==     7) safe_strcat(msg,"6p45pF ");
      else if  (prop->crystal_trim.xo_cap ==     8) safe_strcat(msg,"6p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==     9) safe_strcat(msg,"6p95pF ");
      else if  (prop->crystal_trim.xo_cap ==    10) safe_strcat(msg,"7p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==    11) safe_strcat(msg,"7p45pF ");
      else if  (prop->crystal_trim.xo_cap ==    12) safe_strcat(msg,"7p7pF  ");
      else if  (prop->crystal_trim.xo_cap ==    13) safe_strcat(msg,"7p95pF ");
      else if  (prop->crystal_trim.xo_cap ==    14) safe_strcat(msg,"8p2pF  ");
      else if  (prop->crystal_trim.xo_cap ==    15) safe_strcat(msg,"8p45pF ");
      else                                         safe_sprintf(msg,"%s%d", msg, prop->crystal_trim.xo_cap);
     break;
    #endif /*     Si21XXC_CRYSTAL_TRIM_PROP */
    #ifdef        Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
     case         Si21XXC_DTV_AGC_AUTO_FREEZE_PROP_CODE:
      safe_sprintf(msg,"DTV_AGC_AUTO_FREEZE");
       safe_strcat(msg,separator); safe_strcat(msg,"-THLD "); safe_sprintf(msg,"%s%d", msg, prop->dtv_agc_auto_freeze.thld);
       safe_strcat(msg,separator); safe_strcat(msg,"-TIMEOUT "); safe_sprintf(msg,"%s%d", msg, prop->dtv_agc_auto_freeze.timeout);
     break;
    #endif /*     Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */
    #ifdef        Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
     case         Si21XXC_DTV_AGC_FREEZE_INPUT_PROP_CODE:
      safe_sprintf(msg,"DTV_AGC_FREEZE_INPUT");
       safe_strcat(msg,separator); safe_strcat(msg,"-LEVEL ");
           if  (prop->dtv_agc_freeze_input.level ==     0) safe_strcat(msg,"LOW  ");
      else if  (prop->dtv_agc_freeze_input.level ==     1) safe_strcat(msg,"HIGH ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->dtv_agc_freeze_input.level);
       safe_strcat(msg,separator); safe_strcat(msg,"-PIN ");
           if  (prop->dtv_agc_freeze_input.pin   ==     0) safe_strcat(msg,"NONE     ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     1) safe_strcat(msg,"GPIO1    ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     2) safe_strcat(msg,"GPIO2    ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     3) safe_strcat(msg,"RESERVED ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     4) safe_strcat(msg,"AGC1     ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     5) safe_strcat(msg,"AGC2     ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     6) safe_strcat(msg,"LIF1A    ");
      else if  (prop->dtv_agc_freeze_input.pin   ==     7) safe_strcat(msg,"LIF1B    ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->dtv_agc_freeze_input.pin);
     break;
    #endif /*     Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef        Si21XXC_DTV_AGC_SPEED_PROP
     case         Si21XXC_DTV_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"DTV_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->dtv_agc_speed.if_agc_speed ==     0) safe_strcat(msg,"AUTO ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    39) safe_strcat(msg,"39   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    54) safe_strcat(msg,"54   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    63) safe_strcat(msg,"63   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==    89) safe_strcat(msg,"89   ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   105) safe_strcat(msg,"105  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   121) safe_strcat(msg,"121  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   137) safe_strcat(msg,"137  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   158) safe_strcat(msg,"158  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   172) safe_strcat(msg,"172  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   185) safe_strcat(msg,"185  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   196) safe_strcat(msg,"196  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   206) safe_strcat(msg,"206  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   216) safe_strcat(msg,"216  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   219) safe_strcat(msg,"219  ");
      else if  (prop->dtv_agc_speed.if_agc_speed ==   222) safe_strcat(msg,"222  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->dtv_agc_speed.if_agc_speed);
       safe_strcat(msg,separator); safe_strcat(msg,"-AGC_DECIM ");
           if  (prop->dtv_agc_speed.agc_decim    ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->dtv_agc_speed.agc_decim    ==     1) safe_strcat(msg,"2   ");
      else if  (prop->dtv_agc_speed.agc_decim    ==     2) safe_strcat(msg,"4   ");
      else if  (prop->dtv_agc_speed.agc_decim    ==     3) safe_strcat(msg,"8   ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->dtv_agc_speed.agc_decim);
     break;
    #endif /*     Si21XXC_DTV_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_CONFIG_IF_PORT_PROP
     case         Si21XXC_DTV_CONFIG_IF_PORT_PROP_CODE:
      safe_sprintf(msg,"DTV_CONFIG_IF_PORT");
       safe_strcat(msg,separator); safe_strcat(msg,"-DTV_OUT_TYPE ");
           if  (prop->dtv_config_if_port.dtv_out_type   ==     0) safe_strcat(msg,"LIF_IF1     ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     1) safe_strcat(msg,"LIF_IF2     ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     4) safe_strcat(msg,"LIF_SE_IF1A ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     5) safe_strcat(msg,"LIF_SE_IF2A ");
      else if  (prop->dtv_config_if_port.dtv_out_type   ==     6) safe_strcat(msg,"LVDS        ");
      else                                                       safe_sprintf(msg,"%s%d", msg, prop->dtv_config_if_port.dtv_out_type);
       safe_strcat(msg,separator); safe_strcat(msg,"-DTV_AGC_SOURCE ");
           if  (prop->dtv_config_if_port.dtv_agc_source ==     0) safe_strcat(msg,"INTERNAL  ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     1) safe_strcat(msg,"AGC1_3DB  ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     2) safe_strcat(msg,"AGC2_3DB  ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     3) safe_strcat(msg,"AGC1_FULL ");
      else if  (prop->dtv_config_if_port.dtv_agc_source ==     4) safe_strcat(msg,"AGC2_FULL ");
      else                                                       safe_sprintf(msg,"%s%d", msg, prop->dtv_config_if_port.dtv_agc_source);
     break;
    #endif /*     Si21XXC_DTV_CONFIG_IF_PORT_PROP */
    #ifdef        Si21XXC_DTV_EXT_AGC_PROP
     case         Si21XXC_DTV_EXT_AGC_PROP_CODE:
      safe_sprintf(msg,"DTV_EXT_AGC");
       safe_strcat(msg,separator); safe_strcat(msg,"-MIN_10MV "); safe_sprintf(msg,"%s%d", msg, prop->dtv_ext_agc.min_10mv);
       safe_strcat(msg,separator); safe_strcat(msg,"-MAX_10MV "); safe_sprintf(msg,"%s%d", msg, prop->dtv_ext_agc.max_10mv);
     break;
    #endif /*     Si21XXC_DTV_EXT_AGC_PROP */
    #ifdef        Si21XXC_DTV_IEN_PROP
     case         Si21XXC_DTV_IEN_PROP_CODE:
      safe_sprintf(msg,"DTV_IEN");
       safe_strcat(msg,separator); safe_strcat(msg,"-CHLIEN ");
           if  (prop->dtv_ien.chlien ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->dtv_ien.chlien ==     1) safe_strcat(msg,"ENABLE  ");
      else                                    safe_sprintf(msg,"%s%d", msg, prop->dtv_ien.chlien);
     break;
    #endif /*     Si21XXC_DTV_IEN_PROP */
    #ifdef        Si21XXC_DTV_IF_AGC_SPEED_PROP
     case         Si21XXC_DTV_IF_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"DTV_IF_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATTACK ");
           if  (prop->dtv_if_agc_speed.attack ==     0) safe_strcat(msg,"AUTO ");
      else                                             safe_sprintf(msg,"%d", prop->dtv_if_agc_speed.attack);
       safe_strcat(msg,separator); safe_strcat(msg,"-DECAY ");
           if  (prop->dtv_if_agc_speed.decay  ==     0) safe_strcat(msg,"AUTO ");
      else                                             safe_sprintf(msg,"%d", prop->dtv_if_agc_speed.decay);
     break;
    #endif /*     Si21XXC_DTV_IF_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
     case         Si21XXC_DTV_INITIAL_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"DTV_INITIAL_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-IF_AGC_SPEED ");
           if  (prop->dtv_initial_agc_speed.if_agc_speed ==     0) safe_strcat(msg,"AUTO ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    39) safe_strcat(msg,"39   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    54) safe_strcat(msg,"54   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    63) safe_strcat(msg,"63   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==    89) safe_strcat(msg,"89   ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   105) safe_strcat(msg,"105  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   121) safe_strcat(msg,"121  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   137) safe_strcat(msg,"137  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   158) safe_strcat(msg,"158  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   172) safe_strcat(msg,"172  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   185) safe_strcat(msg,"185  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   196) safe_strcat(msg,"196  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   206) safe_strcat(msg,"206  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   216) safe_strcat(msg,"216  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   219) safe_strcat(msg,"219  ");
      else if  (prop->dtv_initial_agc_speed.if_agc_speed ==   222) safe_strcat(msg,"222  ");
      else                                                        safe_sprintf(msg,"%s%d", msg, prop->dtv_initial_agc_speed.if_agc_speed);
       safe_strcat(msg,separator); safe_strcat(msg,"-AGC_DECIM ");
           if  (prop->dtv_initial_agc_speed.agc_decim    ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->dtv_initial_agc_speed.agc_decim    ==     1) safe_strcat(msg,"2   ");
      else if  (prop->dtv_initial_agc_speed.agc_decim    ==     2) safe_strcat(msg,"4   ");
      else if  (prop->dtv_initial_agc_speed.agc_decim    ==     3) safe_strcat(msg,"8   ");
      else                                                        safe_sprintf(msg,"%s%d", msg, prop->dtv_initial_agc_speed.agc_decim);
     break;
    #endif /*     Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
     case         Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP_CODE:
      safe_sprintf(msg,"DTV_INITIAL_AGC_SPEED_PERIOD");
       safe_strcat(msg,separator); safe_strcat(msg,"-PERIOD "); safe_sprintf(msg,"%s%d", msg, prop->dtv_initial_agc_speed_period.period);
     break;
    #endif /*     Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef        Si21XXC_DTV_INTERNAL_ZIF_PROP
     case         Si21XXC_DTV_INTERNAL_ZIF_PROP_CODE:
      safe_sprintf(msg,"DTV_INTERNAL_ZIF");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATSC ");
           if  (prop->dtv_internal_zif.atsc   ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.atsc   ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.atsc);
       safe_strcat(msg,separator); safe_strcat(msg,"-QAM_US ");
           if  (prop->dtv_internal_zif.qam_us ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.qam_us ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.qam_us);
       safe_strcat(msg,separator); safe_strcat(msg,"-DVBT ");
           if  (prop->dtv_internal_zif.dvbt   ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.dvbt   ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.dvbt);
       safe_strcat(msg,separator); safe_strcat(msg,"-DVBC ");
           if  (prop->dtv_internal_zif.dvbc   ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.dvbc   ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.dvbc);
       safe_strcat(msg,separator); safe_strcat(msg,"-ISDBT ");
           if  (prop->dtv_internal_zif.isdbt  ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.isdbt  ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.isdbt);
       safe_strcat(msg,separator); safe_strcat(msg,"-ISDBC ");
           if  (prop->dtv_internal_zif.isdbc  ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.isdbc  ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.isdbc);
       safe_strcat(msg,separator); safe_strcat(msg,"-DTMB ");
           if  (prop->dtv_internal_zif.dtmb   ==     0) safe_strcat(msg,"LIF ");
      else if  (prop->dtv_internal_zif.dtmb   ==     1) safe_strcat(msg,"ZIF ");
      else                                             safe_sprintf(msg,"%s%d", msg, prop->dtv_internal_zif.dtmb);
     break;
    #endif /*     Si21XXC_DTV_INTERNAL_ZIF_PROP */
    #ifdef        Si21XXC_DTV_INT_SENSE_PROP
     case         Si21XXC_DTV_INT_SENSE_PROP_CODE:
      safe_sprintf(msg,"DTV_INT_SENSE");
       safe_strcat(msg,separator); safe_strcat(msg,"-CHLNEGEN ");
           if  (prop->dtv_int_sense.chlnegen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->dtv_int_sense.chlnegen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                            safe_sprintf(msg,"%s%d", msg, prop->dtv_int_sense.chlnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-CHLPOSEN ");
           if  (prop->dtv_int_sense.chlposen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->dtv_int_sense.chlposen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                            safe_sprintf(msg,"%s%d", msg, prop->dtv_int_sense.chlposen);
     break;
    #endif /*     Si21XXC_DTV_INT_SENSE_PROP */
    #ifdef        Si21XXC_DTV_LIF_FREQ_PROP
     case         Si21XXC_DTV_LIF_FREQ_PROP_CODE:
      safe_sprintf(msg,"DTV_LIF_FREQ");
       safe_strcat(msg,separator); safe_strcat(msg,"-OFFSET "); safe_sprintf(msg,"%s%d", msg, prop->dtv_lif_freq.offset);
     break;
    #endif /*     Si21XXC_DTV_LIF_FREQ_PROP */
    #ifdef        Si21XXC_DTV_LIF_OUT_PROP
     case         Si21XXC_DTV_LIF_OUT_PROP_CODE:
      safe_sprintf(msg,"DTV_LIF_OUT");
       safe_strcat(msg,separator); safe_strcat(msg,"-OFFSET "); safe_sprintf(msg,"%s%d", msg, prop->dtv_lif_out.offset);
       safe_strcat(msg,separator); safe_strcat(msg,"-AMP "); safe_sprintf(msg,"%s%d", msg, prop->dtv_lif_out.amp);
     break;
    #endif /*     Si21XXC_DTV_LIF_OUT_PROP */
    #ifdef        Si21XXC_DTV_MODE_PROP
     case         Si21XXC_DTV_MODE_PROP_CODE:
      safe_sprintf(msg,"DTV_MODE");
       safe_strcat(msg,separator); safe_strcat(msg,"-BW ");
           if  (prop->dtv_mode.bw              ==     6) safe_strcat(msg,"BW_6MHZ   ");
      else if  (prop->dtv_mode.bw              ==     7) safe_strcat(msg,"BW_7MHZ   ");
      else if  (prop->dtv_mode.bw              ==     8) safe_strcat(msg,"BW_8MHZ   ");
      else if  (prop->dtv_mode.bw              ==     9) safe_strcat(msg,"BW_1P7MHZ ");
      else if  (prop->dtv_mode.bw              ==    10) safe_strcat(msg,"BW_6P1MHZ ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->dtv_mode.bw);
       safe_strcat(msg,separator); safe_strcat(msg,"-MODULATION ");
           if  (prop->dtv_mode.modulation      ==     0) safe_strcat(msg,"ATSC      ");
      else if  (prop->dtv_mode.modulation      ==     1) safe_strcat(msg,"QAM_US    ");
      else if  (prop->dtv_mode.modulation      ==     2) safe_strcat(msg,"DVBT      ");
      else if  (prop->dtv_mode.modulation      ==     3) safe_strcat(msg,"DVBC      ");
      else if  (prop->dtv_mode.modulation      ==     4) safe_strcat(msg,"ISDBT     ");
      else if  (prop->dtv_mode.modulation      ==     5) safe_strcat(msg,"ISDBC     ");
      else if  (prop->dtv_mode.modulation      ==     6) safe_strcat(msg,"DTMB      ");
      else if  (prop->dtv_mode.modulation      ==    14) safe_strcat(msg,"CW_LEGACY ");
      else if  (prop->dtv_mode.modulation      ==    15) safe_strcat(msg,"CW        ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->dtv_mode.modulation);
       safe_strcat(msg,separator); safe_strcat(msg,"-INVERT_SPECTRUM ");
           if  (prop->dtv_mode.invert_spectrum ==     0) safe_strcat(msg,"NORMAL   ");
      else if  (prop->dtv_mode.invert_spectrum ==     1) safe_strcat(msg,"INVERTED ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->dtv_mode.invert_spectrum);
     break;
    #endif /*     Si21XXC_DTV_MODE_PROP */
    #ifdef        Si21XXC_DTV_RF_AGC_SPEED_PROP
     case         Si21XXC_DTV_RF_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"DTV_RF_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATTACK "); safe_sprintf(msg,"%s%d", msg, prop->dtv_rf_agc_speed.attack);
       safe_strcat(msg,separator); safe_strcat(msg,"-DECAY "); safe_sprintf(msg,"%s%d", msg, prop->dtv_rf_agc_speed.decay);
     break;
    #endif /*     Si21XXC_DTV_RF_AGC_SPEED_PROP */
    #ifdef        Si21XXC_DTV_RF_TOP_PROP
     case         Si21XXC_DTV_RF_TOP_PROP_CODE:
      safe_sprintf(msg,"DTV_RF_TOP");
       safe_strcat(msg,separator); safe_strcat(msg,"-DTV_RF_TOP ");
           if  (prop->dtv_rf_top.dtv_rf_top ==     0) safe_strcat(msg,"AUTO    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     1) safe_strcat(msg,"P10DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     2) safe_strcat(msg,"P9P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     3) safe_strcat(msg,"P9DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     4) safe_strcat(msg,"P8P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     5) safe_strcat(msg,"P8DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     6) safe_strcat(msg,"P7P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     7) safe_strcat(msg,"P7DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     8) safe_strcat(msg,"P6P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==     9) safe_strcat(msg,"P6DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    10) safe_strcat(msg,"P5P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    11) safe_strcat(msg,"P5DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    12) safe_strcat(msg,"P4P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    13) safe_strcat(msg,"P4DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    14) safe_strcat(msg,"P3P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    15) safe_strcat(msg,"P3DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    16) safe_strcat(msg,"P2P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    17) safe_strcat(msg,"P2DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    18) safe_strcat(msg,"P1P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    19) safe_strcat(msg,"P1DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    20) safe_strcat(msg,"P0P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    21) safe_strcat(msg,"0DB     ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    22) safe_strcat(msg,"M0P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    23) safe_strcat(msg,"M1DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    24) safe_strcat(msg,"M1P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    25) safe_strcat(msg,"M2DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    26) safe_strcat(msg,"M2P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    27) safe_strcat(msg,"M3DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    28) safe_strcat(msg,"M3P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    29) safe_strcat(msg,"M4DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    30) safe_strcat(msg,"M4P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    31) safe_strcat(msg,"M5DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    32) safe_strcat(msg,"M5P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    33) safe_strcat(msg,"M6DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    34) safe_strcat(msg,"M6P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    35) safe_strcat(msg,"M7DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    36) safe_strcat(msg,"M7P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    37) safe_strcat(msg,"M8DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    38) safe_strcat(msg,"M8P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    39) safe_strcat(msg,"M9DB    ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    40) safe_strcat(msg,"M9P5DB  ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    41) safe_strcat(msg,"M10DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    42) safe_strcat(msg,"M10P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    43) safe_strcat(msg,"M11DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    44) safe_strcat(msg,"M11P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    45) safe_strcat(msg,"M12DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    46) safe_strcat(msg,"M12P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    47) safe_strcat(msg,"M13DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    48) safe_strcat(msg,"M13P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    49) safe_strcat(msg,"M14DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    50) safe_strcat(msg,"M14P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    51) safe_strcat(msg,"M15DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    52) safe_strcat(msg,"M15P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    53) safe_strcat(msg,"M16DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    54) safe_strcat(msg,"M16P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    55) safe_strcat(msg,"M17DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    56) safe_strcat(msg,"M17P5DB ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    57) safe_strcat(msg,"M18DB   ");
      else if  (prop->dtv_rf_top.dtv_rf_top ==    58) safe_strcat(msg,"M18P5DB ");
      else                                           safe_sprintf(msg,"%s%d", msg, prop->dtv_rf_top.dtv_rf_top);
     break;
    #endif /*     Si21XXC_DTV_RF_TOP_PROP */
    #ifdef        Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
     case         Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP_CODE:
      safe_sprintf(msg,"DTV_RSQ_RSSI_THRESHOLD");
       safe_strcat(msg,separator); safe_strcat(msg,"-LO "); safe_sprintf(msg,"%s%d", msg, prop->dtv_rsq_rssi_threshold.lo);
       safe_strcat(msg,separator); safe_strcat(msg,"-HI "); safe_sprintf(msg,"%s%d", msg, prop->dtv_rsq_rssi_threshold.hi);
     break;
    #endif /*     Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef        Si21XXC_DTV_WB_AGC_SPEED_PROP
     case         Si21XXC_DTV_WB_AGC_SPEED_PROP_CODE:
      safe_sprintf(msg,"DTV_WB_AGC_SPEED");
       safe_strcat(msg,separator); safe_strcat(msg,"-ATTACK ");
           if  (prop->dtv_wb_agc_speed.attack ==     0) safe_strcat(msg,"AUTO ");
      else                                             safe_sprintf(msg,"%d", prop->dtv_wb_agc_speed.attack);
       safe_strcat(msg,separator); safe_strcat(msg,"-DECAY ");
           if  (prop->dtv_wb_agc_speed.decay  ==     0) safe_strcat(msg,"AUTO ");
      else                                             safe_sprintf(msg,"%d", prop->dtv_wb_agc_speed.decay);
     break;
    #endif /*     Si21XXC_DTV_WB_AGC_SPEED_PROP */
    #ifdef        Si21XXC_MASTER_IEN_PROP
     case         Si21XXC_MASTER_IEN_PROP_CODE:
      safe_sprintf(msg,"MASTER_IEN");
       safe_strcat(msg,separator); safe_strcat(msg,"-TUNIEN ");
           if  (prop->master_ien.tunien ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->master_ien.tunien ==     1) safe_strcat(msg,"ON  ");
      else                                       safe_sprintf(msg,"%s%d", msg, prop->master_ien.tunien);
       safe_strcat(msg,separator); safe_strcat(msg,"-ATVIEN ");
           if  (prop->master_ien.atvien ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->master_ien.atvien ==     1) safe_strcat(msg,"ON  ");
      else                                       safe_sprintf(msg,"%s%d", msg, prop->master_ien.atvien);
       safe_strcat(msg,separator); safe_strcat(msg,"-DTVIEN ");
           if  (prop->master_ien.dtvien ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->master_ien.dtvien ==     1) safe_strcat(msg,"ON  ");
      else                                       safe_sprintf(msg,"%s%d", msg, prop->master_ien.dtvien);
       safe_strcat(msg,separator); safe_strcat(msg,"-ERRIEN ");
           if  (prop->master_ien.errien ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->master_ien.errien ==     1) safe_strcat(msg,"ON  ");
      else                                       safe_sprintf(msg,"%s%d", msg, prop->master_ien.errien);
       safe_strcat(msg,separator); safe_strcat(msg,"-CTSIEN ");
           if  (prop->master_ien.ctsien ==     0) safe_strcat(msg,"OFF ");
      else if  (prop->master_ien.ctsien ==     1) safe_strcat(msg,"ON  ");
      else                                       safe_sprintf(msg,"%s%d", msg, prop->master_ien.ctsien);
     break;
    #endif /*     Si21XXC_MASTER_IEN_PROP */
    #ifdef        Si21XXC_TUNER_BLOCKED_VCO_PROP
     case         Si21XXC_TUNER_BLOCKED_VCO_PROP_CODE:
      safe_sprintf(msg,"TUNER_BLOCKED_VCO");
       safe_strcat(msg,separator); safe_strcat(msg,"-VCO_CODE "); safe_sprintf(msg,"%s%d", msg, prop->tuner_blocked_vco.vco_code);
     break;
    #endif /*     Si21XXC_TUNER_BLOCKED_VCO_PROP */
    #ifdef        Si21XXC_TUNER_IEN_PROP
     case         Si21XXC_TUNER_IEN_PROP_CODE:
      safe_sprintf(msg,"TUNER_IEN");
       safe_strcat(msg,separator); safe_strcat(msg,"-TCIEN ");
           if  (prop->tuner_ien.tcien    ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_ien.tcien    ==     1) safe_strcat(msg,"ENABLE  ");
      else                                        safe_sprintf(msg,"%s%d", msg, prop->tuner_ien.tcien);
       safe_strcat(msg,separator); safe_strcat(msg,"-RSSILIEN ");
           if  (prop->tuner_ien.rssilien ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_ien.rssilien ==     1) safe_strcat(msg,"ENABLE  ");
      else                                        safe_sprintf(msg,"%s%d", msg, prop->tuner_ien.rssilien);
       safe_strcat(msg,separator); safe_strcat(msg,"-RSSIHIEN ");
           if  (prop->tuner_ien.rssihien ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_ien.rssihien ==     1) safe_strcat(msg,"ENABLE  ");
      else                                        safe_sprintf(msg,"%s%d", msg, prop->tuner_ien.rssihien);
     break;
    #endif /*     Si21XXC_TUNER_IEN_PROP */
    #ifdef        Si21XXC_TUNER_INT_SENSE_PROP
     case         Si21XXC_TUNER_INT_SENSE_PROP_CODE:
      safe_sprintf(msg,"TUNER_INT_SENSE");
       safe_strcat(msg,separator); safe_strcat(msg,"-TCNEGEN ");
           if  (prop->tuner_int_sense.tcnegen    ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.tcnegen    ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->tuner_int_sense.tcnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-RSSILNEGEN ");
           if  (prop->tuner_int_sense.rssilnegen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssilnegen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssilnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-RSSIHNEGEN ");
           if  (prop->tuner_int_sense.rssihnegen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssihnegen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssihnegen);
       safe_strcat(msg,separator); safe_strcat(msg,"-TCPOSEN ");
           if  (prop->tuner_int_sense.tcposen    ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.tcposen    ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->tuner_int_sense.tcposen);
       safe_strcat(msg,separator); safe_strcat(msg,"-RSSILPOSEN ");
           if  (prop->tuner_int_sense.rssilposen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssilposen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssilposen);
       safe_strcat(msg,separator); safe_strcat(msg,"-RSSIHPOSEN ");
           if  (prop->tuner_int_sense.rssihposen ==     0) safe_strcat(msg,"DISABLE ");
      else if  (prop->tuner_int_sense.rssihposen ==     1) safe_strcat(msg,"ENABLE  ");
      else                                                safe_sprintf(msg,"%s%d", msg, prop->tuner_int_sense.rssihposen);
     break;
    #endif /*     Si21XXC_TUNER_INT_SENSE_PROP */
    #ifdef        Si21XXC_TUNER_LO_INJECTION_PROP
     case         Si21XXC_TUNER_LO_INJECTION_PROP_CODE:
      safe_sprintf(msg,"TUNER_LO_INJECTION");
       safe_strcat(msg,separator); safe_strcat(msg,"-BAND_1 ");
           if  (prop->tuner_lo_injection.band_1 ==     0) safe_strcat(msg,"LOW_SIDE  ");
      else if  (prop->tuner_lo_injection.band_1 ==     1) safe_strcat(msg,"HIGH_SIDE ");
      else                                               safe_sprintf(msg,"%s%d", msg, prop->tuner_lo_injection.band_1);
       safe_strcat(msg,separator); safe_strcat(msg,"-BAND_2 ");
           if  (prop->tuner_lo_injection.band_2 ==     0) safe_strcat(msg,"LOW_SIDE  ");
      else if  (prop->tuner_lo_injection.band_2 ==     1) safe_strcat(msg,"HIGH_SIDE ");
      else                                               safe_sprintf(msg,"%s%d", msg, prop->tuner_lo_injection.band_2);
       safe_strcat(msg,separator); safe_strcat(msg,"-BAND_3 ");
           if  (prop->tuner_lo_injection.band_3 ==     0) safe_strcat(msg,"LOW_SIDE  ");
      else if  (prop->tuner_lo_injection.band_3 ==     1) safe_strcat(msg,"HIGH_SIDE ");
      else                                               safe_sprintf(msg,"%s%d", msg, prop->tuner_lo_injection.band_3);
     break;
    #endif /*     Si21XXC_TUNER_LO_INJECTION_PROP */
    #ifdef        Si21XXC_TUNER_RETURN_LOSS_PROP
     case         Si21XXC_TUNER_RETURN_LOSS_PROP_CODE:
      safe_sprintf(msg,"TUNER_RETURN_LOSS");
       safe_strcat(msg,separator); safe_strcat(msg,"-CONFIG ");
           if  (prop->tuner_return_loss.config ==     3) safe_strcat(msg,"3   ");
      else if  (prop->tuner_return_loss.config ==     7) safe_strcat(msg,"7   ");
      else if  (prop->tuner_return_loss.config ==    11) safe_strcat(msg,"11  ");
      else if  (prop->tuner_return_loss.config ==    15) safe_strcat(msg,"15  ");
      else if  (prop->tuner_return_loss.config ==    19) safe_strcat(msg,"19  ");
      else if  (prop->tuner_return_loss.config ==    23) safe_strcat(msg,"23  ");
      else if  (prop->tuner_return_loss.config ==    27) safe_strcat(msg,"27  ");
      else if  (prop->tuner_return_loss.config ==    31) safe_strcat(msg,"31  ");
      else if  (prop->tuner_return_loss.config ==    35) safe_strcat(msg,"35  ");
      else if  (prop->tuner_return_loss.config ==    39) safe_strcat(msg,"39  ");
      else if  (prop->tuner_return_loss.config ==    43) safe_strcat(msg,"43  ");
      else if  (prop->tuner_return_loss.config ==    47) safe_strcat(msg,"47  ");
      else if  (prop->tuner_return_loss.config ==    51) safe_strcat(msg,"51  ");
      else if  (prop->tuner_return_loss.config ==    59) safe_strcat(msg,"59  ");
      else if  (prop->tuner_return_loss.config ==    67) safe_strcat(msg,"67  ");
      else if  (prop->tuner_return_loss.config ==    75) safe_strcat(msg,"75  ");
      else if  (prop->tuner_return_loss.config ==    83) safe_strcat(msg,"83  ");
      else if  (prop->tuner_return_loss.config ==    91) safe_strcat(msg,"91  ");
      else if  (prop->tuner_return_loss.config ==   103) safe_strcat(msg,"103 ");
      else if  (prop->tuner_return_loss.config ==   115) safe_strcat(msg,"115 ");
      else if  (prop->tuner_return_loss.config ==   127) safe_strcat(msg,"127 ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->tuner_return_loss.config);
       safe_strcat(msg,separator); safe_strcat(msg,"-MODE ");
           if  (prop->tuner_return_loss.mode   ==     0) safe_strcat(msg,"TERRESTRIAL ");
      else if  (prop->tuner_return_loss.mode   ==     1) safe_strcat(msg,"CABLE       ");
      else                                              safe_sprintf(msg,"%s%d", msg, prop->tuner_return_loss.mode);
     break;
    #endif /*     Si21XXC_TUNER_RETURN_LOSS_PROP */
    #ifdef        Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
     case         Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CODE:
      safe_sprintf(msg,"TUNER_RETURN_LOSS_OPTIMIZE");
      safe_strcat(msg,separator); safe_strcat(msg,"-THLD "); safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize.thld);
      safe_strcat(msg,separator); safe_strcat(msg,"-CONFIG ");
           if  (prop->tuner_return_loss_optimize.config              ==     0) safe_strcat(msg,"2       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     1) safe_strcat(msg,"3       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     2) safe_strcat(msg,"4       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     3) safe_strcat(msg,"5       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     4) safe_strcat(msg,"6       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     5) safe_strcat(msg,"7       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     6) safe_strcat(msg,"8       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     7) safe_strcat(msg,"9       ");
      else if  (prop->tuner_return_loss_optimize.config              ==     8) safe_strcat(msg,"10      ");
      else if  (prop->tuner_return_loss_optimize.config              ==     9) safe_strcat(msg,"11      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    10) safe_strcat(msg,"13      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    11) safe_strcat(msg,"15      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    12) safe_strcat(msg,"17      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    13) safe_strcat(msg,"19      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    14) safe_strcat(msg,"23      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    15) safe_strcat(msg,"27      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    16) safe_strcat(msg,"31      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    17) safe_strcat(msg,"35      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    18) safe_strcat(msg,"39      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    19) safe_strcat(msg,"43      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    20) safe_strcat(msg,"47      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    21) safe_strcat(msg,"51      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    22) safe_strcat(msg,"59      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    23) safe_strcat(msg,"67      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    24) safe_strcat(msg,"75      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    25) safe_strcat(msg,"83      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    26) safe_strcat(msg,"91      ");
      else if  (prop->tuner_return_loss_optimize.config              ==    27) safe_strcat(msg,"103     ");
      else if  (prop->tuner_return_loss_optimize.config              ==    28) safe_strcat(msg,"115     ");
      else if  (prop->tuner_return_loss_optimize.config              ==    29) safe_strcat(msg,"127     ");
      else if  (prop->tuner_return_loss_optimize.config              ==    30) safe_strcat(msg,"DISABLE ");
      else                                                                    safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize.config);
       safe_strcat(msg,separator); safe_strcat(msg,"-ENGAGEMENT_DELAY "); safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize.engagement_delay);
       safe_strcat(msg,separator); safe_strcat(msg,"-DISENGAGEMENT_DELAY "); safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize.disengagement_delay);
     break;
    #endif /*     Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP */
    #ifdef        Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
     case         Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP_CODE:
      safe_sprintf(msg,"TUNER_RETURN_LOSS_OPTIMIZE_2");
       safe_strcat(msg,separator); safe_strcat(msg,"-THLD "); safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize_2.thld);
       safe_strcat(msg,separator); safe_strcat(msg,"-WINDOW "); safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize_2.window);
       safe_strcat(msg,separator); safe_strcat(msg,"-ENGAGEMENT_DELAY "); safe_sprintf(msg,"%d", prop->tuner_return_loss_optimize_2.engagement_delay);
     break;
    #endif /*     Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP */
    #ifdef        Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
     case         Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP_CODE:
      safe_sprintf(msg,"TUNER_TF1_BOUNDARY_OFFSET");
       safe_strcat(msg,separator); safe_strcat(msg,"-TF1_BOUNDARY_OFFSET "); safe_sprintf(msg,"%d", prop->tuner_tf1_boundary_offset.tf1_boundary_offset);
     break;
    #endif /*     Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */
    #ifdef        Si2190B_WIDE_BAND_ATT_THRS_PROP
     case         Si2190B_WIDE_BAND_ATT_THRS_PROP_CODE:
      safe_sprintf(msg,"WIDE_BAND_ATT_THRS");
       safe_strcat(msg,separator); safe_strcat(msg,"-WB_ATT_THRS ");
           if  (prop->wide_band_att_thrs.wb_att_thrs ==     0) safe_strcat(msg,"AUTO    ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==     6) safe_strcat(msg,"P6DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==     7) safe_strcat(msg,"P5DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==     8) safe_strcat(msg,"P4DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==     9) safe_strcat(msg,"P3DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    10) safe_strcat(msg,"P2DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    11) safe_strcat(msg,"P1DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    12) safe_strcat(msg,"0DBM    ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    13) safe_strcat(msg,"M1DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    14) safe_strcat(msg,"M2DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    15) safe_strcat(msg,"M3DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    16) safe_strcat(msg,"M4DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    17) safe_strcat(msg,"M5DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    18) safe_strcat(msg,"M6DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    19) safe_strcat(msg,"M7DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    20) safe_strcat(msg,"M8DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    21) safe_strcat(msg,"M9DBM   ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    22) safe_strcat(msg,"M10DBM  ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    23) safe_strcat(msg,"M11DBM  ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==    24) safe_strcat(msg,"M12DBM  ");
      else if  (prop->wide_band_att_thrs.wb_att_thrs ==   255) safe_strcat(msg,"DISABLE ");
      else                                                    safe_sprintf(msg,"%d", prop->wide_band_att_thrs.wb_att_thrs);
     break;
    #endif /*     Si2190B_WIDE_BAND_ATT_THRS_PROP */

    #ifdef        Si21XXC_XOUT_PROP
     case         Si21XXC_XOUT_PROP_CODE:
      safe_sprintf(msg,"XOUT");
       safe_strcat(msg,separator); safe_strcat(msg,"-AMP ");
           if  (prop->xout.amp ==     0) safe_strcat(msg,"HIGH ");
      else if  (prop->xout.amp ==     1) safe_strcat(msg,"LOW  ");
      else                              safe_sprintf(msg,"%s%d", msg, prop->xout.amp);
     break;
    #endif /*     Si21XXC_XOUT_PROP */
     default : safe_sprintf(msg,"Unknown property code '0x%06x'\n", prop_code); return ERROR_Si21XXC_UNKNOWN_PROPERTY; break;
    }
  return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  Si21XXC_L1_FillPropertyStringText function
  Use:        property text retrieval function
              Used to retrieve the property text for a selected property.
  Parameter: *api      the Si21XXC context
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string (usually declared with a size of 1000 bytes)
  Returns:    NO_Si21XXC_ERROR if successful.
 ***********************************************************************************************************************/
void          Si21XXC_L1_FillPropertyStringText(L1_Si21XXC_Context *api, unsigned int prop_code, const char *separator, char *msg) {
  Si21XXC_L1_PropertyText (api->prop, prop_code, separator, msg);
}
/***********************************************************************************************************************
  Si21XXC_L1_GetPropertyString function
  Use:        current property text retrieval function
              Used to retrieve the property value from the hardware then retrieve the corresponding property text.
  Parameter: *api      the Si21XXC context
  Parameter: prop_code the property Id (used to know which property to use)
  Parameter: separator the string to use between fields (often either a blank or a newline character)
  Parameter: msg       the string used to store the resulting string (usually declared with a size of 1000 bytes)
  Returns:    NO_Si21XXC_ERROR if successful.
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_GetPropertyString     (L1_Si21XXC_Context *api, unsigned int prop_code, const char *separator, char *msg) {
    int res;
    res = Si21XXC_L1_GetProperty2(api,prop_code);
    if (res!=NO_Si21XXC_ERROR) { safe_sprintf(msg, "%s",Si21XXC_L1_API_ERROR_TEXT(res)); return res; }
    Si21XXC_L1_PropertyText(api->prop, prop_code, separator, msg);
    return NO_Si21XXC_ERROR;
  }
#endif /* Si21XXC_GET_PROPERTY_STRING */








