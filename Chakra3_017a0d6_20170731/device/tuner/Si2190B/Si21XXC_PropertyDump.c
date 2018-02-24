/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API properties definitions
   FILE: Si21XXC_PropertyDump.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#define   Si21XXC_COMMAND_PROTOTYPES

#include "Si21XXC_L1_API.h"
#include "Si21XXC_PropertyDump.h"
#include <string.h>

#define MAX_PROPS 60
int count;
unsigned char ddrData[MAX_PROPS][9];
/***********************************************************************************************************************
  Si21XXC_L1_DUMP_TUNER_STATUS function
  Use:        Returns a tune command encoded to i2c bytes

  Parameter: *api     the Si21XXC context
  Parameter: mode     ATV or DTV
  Parameter: freq     frequency (hz)
  Parameter: cmdByteBuffer -- buffer for data
  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the tune command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/
unsigned char Si21XXC_L1_DUMP_TUNER_STATUS(L1_Si21XXC_Context *api,unsigned char   mode,
                                                unsigned long   freq,unsigned char cmdByteBuffer[])
{
    SiTRACE("Si21XXC_L1_DUMP_TUNER_STATUS ");
    SiTRACE("\n");
    cmdByteBuffer[0] = 8;
    cmdByteBuffer[1] = Si21XXC_TUNER_TUNE_FREQ_CMD;
    cmdByteBuffer[2] = (unsigned char) ( ( mode & Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_LSB);
    cmdByteBuffer[3] = (unsigned char)0x00;
    cmdByteBuffer[4] = (unsigned char)0x00;
    cmdByteBuffer[5] = (unsigned char) ( ( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB);
    cmdByteBuffer[6] = (unsigned char) ((( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>8);
    cmdByteBuffer[7] = (unsigned char) ((( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>16);
    cmdByteBuffer[8] = (unsigned char) ((( freq & Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_MASK ) << Si21XXC_TUNER_TUNE_FREQ_CMD_FREQ_LSB)>>24);

    return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  DumpProperty function
  Use:        Returns a single property command encoded to i2c bytes

  Parameter: *api     the Si21XXC context
  Parameter: prop     property command #
  Parameter: cmdByteBuffer -- buffer for data
  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the setProperty command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char DumpProperty(L1_Si21XXC_Context *api,int prop,unsigned char cmdByteBuffer[])
{
    int shadowData=0;
    int propData=0;
    unsigned char reserved = 0;

    Si21XXC_PackProperty(api->propShadow, prop, &shadowData);
    Si21XXC_PackProperty(api->prop, prop, &propData);

    if (1)//(shadowData != propData)
    {

        cmdByteBuffer[0] = 6;
        cmdByteBuffer[1] = Si21XXC_SET_PROPERTY_CMD;
        cmdByteBuffer[2] = (unsigned char) ( ( reserved & Si21XXC_SET_PROPERTY_CMD_RESERVED_MASK ) << Si21XXC_SET_PROPERTY_CMD_RESERVED_LSB);
        cmdByteBuffer[3] = (unsigned char) ( ( prop     & Si21XXC_SET_PROPERTY_CMD_PROP_MASK     ) << Si21XXC_SET_PROPERTY_CMD_PROP_LSB    );
        cmdByteBuffer[4] = (unsigned char) ((( prop     & Si21XXC_SET_PROPERTY_CMD_PROP_MASK     ) << Si21XXC_SET_PROPERTY_CMD_PROP_LSB    )>>8);
        cmdByteBuffer[5] = (unsigned char) ( ( propData     & Si21XXC_SET_PROPERTY_CMD_DATA_MASK     ) << Si21XXC_SET_PROPERTY_CMD_DATA_LSB    );
        cmdByteBuffer[6] = (unsigned char) ((( propData     & Si21XXC_SET_PROPERTY_CMD_DATA_MASK     ) << Si21XXC_SET_PROPERTY_CMD_DATA_LSB    )>>8);
        //safe_printf("Property Bytes:%x,%x,%x,%x,%x,%x,%x\n",cmdByteBuffer[0],cmdByteBuffer[1],cmdByteBuffer[2],cmdByteBuffer[3],
        //        cmdByteBuffer[4],cmdByteBuffer[5],cmdByteBuffer[6]);
        return 1;
    }
    else
    {
        return 0;
    }

}
/***********************************************************************************************************************
  Si21XXC_DumpATVProperties function
  Use:        Command to dump all changed properties to DDR memory.

  Parameter: *api     the Si21XXC context

  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the setProperty command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_DumpATVProperties(L1_Si21XXC_Context *api)
{
    unsigned char tns[7];

    #ifdef    Si21XXC_ATV_AFC_RANGE_PROP
    if (DumpProperty(api,Si21XXC_ATV_AFC_RANGE_PROP,tns))
    {
        memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_AFC_RANGE_PROP */
    #ifdef    Si21XXC_ATV_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_ATV_AGC_SPEED_PROP,tns))
    {
        memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_AGC_SPEED_PROP */
    #ifdef    Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP
    if (DumpProperty(api,Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP,tns))
    {
        memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_AGC_SPEED_LOW_RSSI_PROP */
    #ifdef    Si21XXC_ATV_ARTIFICIAL_SNOW_PROP
    if (DumpProperty(api,Si21XXC_ATV_ARTIFICIAL_SNOW_PROP,tns))
    {
        memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_ARTIFICIAL_SNOW_PROP */
    #ifdef    Si21XXC_ATV_AUDIO_MODE_PROP
    if (DumpProperty(api,Si21XXC_ATV_AUDIO_MODE_PROP,tns))
    {
         memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_AUDIO_MODE_PROP */
    #ifdef    Si21XXC_ATV_CONFIG_IF_PORT_PROP
    if (DumpProperty(api,Si21XXC_ATV_CONFIG_IF_PORT_PROP,tns))
    {
         memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_CONFIG_IF_PORT_PROP */
    if (api->rsp->part_info.romid == 0x70 || api->rsp->part_info.romid == 0x71)
    {
        #ifdef    Si2190B_ATV_CVBS_ATTENUATION_PROP
        if (DumpProperty(api,Si2190B_ATV_CVBS_ATTENUATION_PROP,tns))
        {
             memcpy(ddrData[count++],&tns,7);
        }
        #endif /* Si2190B_ATV_CVBS_ATTENUATION_PROP */
    }
    #ifdef    Si21XXC_ATV_CVBS_OUT_PROP
    if (DumpProperty(api,Si21XXC_ATV_CVBS_OUT_PROP,tns))
    {
         memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_CVBS_OUT_PROP */
    #ifdef    Si21XXC_ATV_CVBS_OUT_FINE_PROP
    if (DumpProperty(api,Si21XXC_ATV_CVBS_OUT_FINE_PROP,tns))
    {
         memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_CVBS_OUT_FINE_PROP */

    #ifdef    Si21XXC_ATV_IEN_PROP
    if (DumpProperty(api,Si21XXC_ATV_IEN_PROP,tns))
    {
         memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_IEN_PROP */
    #ifdef    Si21XXC_ATV_INT_SENSE_PROP
    if (DumpProperty(api,Si21XXC_ATV_INT_SENSE_PROP,tns))
    {
        memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_INT_SENSE_PROP */
    #ifdef    Si21XXC_ATV_PGA_TARGET_PROP
    if (DumpProperty(api,Si21XXC_ATV_PGA_TARGET_PROP,tns))
    {
        memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_PGA_TARGET_PROP */
    #ifdef    Si21XXC_ATV_RF_TOP_PROP
    if (DumpProperty(api,Si21XXC_ATV_RF_TOP_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_RF_TOP_PROP */
    #ifdef    Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP
    if (DumpProperty(api,Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_RSQ_RSSI_THRESHOLD_PROP */
    #ifdef    Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP
    if (DumpProperty(api,Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_RSQ_SNR_THRESHOLD_PROP */
    #ifdef    Si21XXC_ATV_SIF_OUT_PROP
    if (DumpProperty(api,Si21XXC_ATV_SIF_OUT_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_SIF_OUT_PROP */
    #ifdef    Si21XXC_ATV_SOUND_AGC_LIMIT_PROP
    if (DumpProperty(api,Si21XXC_ATV_SOUND_AGC_LIMIT_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_SOUND_AGC_LIMIT_PROP */
    #ifdef    Si21XXC_ATV_SOUND_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_ATV_SOUND_AGC_SPEED_PROP,tns))
    {
          memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_SOUND_AGC_SPEED_PROP */
    #ifdef    Si21XXC_ATV_VIDEO_EQUALIZER_PROP
    if (DumpProperty(api,Si21XXC_ATV_VIDEO_EQUALIZER_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_VIDEO_EQUALIZER_PROP */
    #ifdef    Si21XXC_ATV_VIDEO_MODE_PROP
    if (DumpProperty(api,Si21XXC_ATV_VIDEO_MODE_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_VIDEO_MODE_PROP */
    #ifdef    Si21XXC_ATV_VSNR_CAP_PROP
    if (DumpProperty(api,Si21XXC_ATV_VSNR_CAP_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_ATV_VSNR_CAP_PROP */

    return NO_Si21XXC_ERROR;

    }
/***********************************************************************************************************************
  Si21XXC_DumpDTVProperties function
  Use:        Command to dump all changed properties to DDR memory.

  Parameter: *api     the Si21XXC context

  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the setProperty command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_DumpDTVProperties(L1_Si21XXC_Context *api)
    {
    unsigned char tns[7];

	#ifdef    Si21XXC_DTV_AGC_AUTO_FREEZE_PROP
    if (DumpProperty(api,Si21XXC_DTV_AGC_AUTO_FREEZE_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
	#endif /* Si21XXC_DTV_AGC_AUTO_FREEZE_PROP */

    #ifdef    Si21XXC_DTV_AGC_FREEZE_INPUT_PROP
    if (DumpProperty(api,Si21XXC_DTV_AGC_FREEZE_INPUT_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_AGC_FREEZE_INPUT_PROP */
    #ifdef    Si21XXC_DTV_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_DTV_AGC_SPEED_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_AGC_SPEED_PROP */
    #ifdef    Si21XXC_DTV_CONFIG_IF_PORT_PROP
    if (DumpProperty(api,Si21XXC_DTV_CONFIG_IF_PORT_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_CONFIG_IF_PORT_PROP */
    #ifdef    Si21XXC_DTV_EXT_AGC_PROP
    if (DumpProperty(api,Si21XXC_DTV_EXT_AGC_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_EXT_AGC_PROP */
    #ifdef    Si21XXC_DTV_IEN_PROP
    if (DumpProperty(api,Si21XXC_DTV_IEN_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_IEN_PROP */
    #ifdef    Si21XXC_DTV_IF_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_DTV_IF_AGC_SPEED_PROP,tns))
    {
          memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_IF_AGC_SPEED_PROP */
    #ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_DTV_INITIAL_AGC_SPEED_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PROP */
    #ifdef    Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP
    if (DumpProperty(api,Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_INITIAL_AGC_SPEED_PERIOD_PROP */
    #ifdef    Si21XXC_DTV_INTERNAL_ZIF_PROP
    if ((api->rsp->part_info.part == 91) && (api->rsp->part_info.chiprev==3))
    {
        SiTRACE("DTV_INTERNAL_ZIF not defined for Si2191C.\n");
    }
    else
    {
        if (DumpProperty(api,Si21XXC_DTV_INTERNAL_ZIF_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
    }
    #endif /* Si21XXC_DTV_INTERNAL_ZIF_PROP */
    #ifdef    Si21XXC_DTV_INT_SENSE_PROP
    if (DumpProperty(api,Si21XXC_DTV_INT_SENSE_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_INT_SENSE_PROP */
    #ifdef    Si21XXC_DTV_LIF_FREQ_PROP
    if (DumpProperty(api,Si21XXC_DTV_LIF_FREQ_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_LIF_FREQ_PROP */
    #ifdef    Si21XXC_DTV_LIF_OUT_PROP
    if (DumpProperty(api,Si21XXC_DTV_LIF_OUT_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_LIF_OUT_PROP */
    #ifdef    Si21XXC_DTV_MODE_PROP
    if (DumpProperty(api,Si21XXC_DTV_MODE_PROP,tns))
    {
          memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_MODE_PROP */

    #ifdef    Si21XXC_DTV_RF_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_DTV_RF_AGC_SPEED_PROP,tns))
    {
          memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_RF_AGC_SPEED_PROP */

    #ifdef    Si21XXC_DTV_RF_TOP_PROP
    if (DumpProperty(api,Si21XXC_DTV_RF_TOP_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_RF_TOP_PROP */
    #ifdef    Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP
    if (DumpProperty(api,Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_RSQ_RSSI_THRESHOLD_PROP */

    #ifdef    Si21XXC_DTV_WB_AGC_SPEED_PROP
    if (DumpProperty(api,Si21XXC_DTV_WB_AGC_SPEED_PROP,tns))
    {
          memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_DTV_WB_AGC_SPEED_PROP */

    return NO_Si21XXC_ERROR;

}
/***********************************************************************************************************************
  Si21XXC_DumpTunerProperties function
  Use:        Command to dump all changed properties to DDR memory.

  Parameter: *api     the Si21XXC context

  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the setProperty command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_DumpTunerProperties(L1_Si21XXC_Context *api)
{
   unsigned char tns[7];
    #ifdef    Si21XXC_TUNER_BLOCKED_VCO_PROP
    if (DumpProperty(api,Si21XXC_TUNER_BLOCKED_VCO_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_TUNER_BLOCKED_VCO_PROP */
    #ifdef    Si21XXC_TUNER_IEN_PROP
    if (DumpProperty(api,Si21XXC_TUNER_IEN_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_TUNER_IEN_PROP */
    #ifdef    Si21XXC_TUNER_INT_SENSE_PROP
    if (DumpProperty(api,Si21XXC_TUNER_INT_SENSE_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_TUNER_INT_SENSE_PROP */
    #ifdef    Si21XXC_TUNER_LO_INJECTION_PROP
    if (DumpProperty(api,Si21XXC_TUNER_LO_INJECTION_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_TUNER_LO_INJECTION_PROP */
    #ifdef    Si21XXC_TUNER_RETURN_LOSS_PROP
    if (DumpProperty(api,Si21XXC_TUNER_RETURN_LOSS_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
    #endif /* Si21XXC_TUNER_RETURN_LOSS_PROP */
    if (api->rsp->part_info.romid == 0x70 || api->rsp->part_info.romid == 0x71)
    {
        #ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP
        if (DumpProperty(api,Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
        #endif /* Si21XXC_TUNER_RETURN_LOSS_PROP */

        #ifdef    Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP
        if (DumpProperty(api,Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
        #endif /* Si21XXC_TUNER_RETURN_LOSS_PROP */

        #ifdef    Si2190B_WIDE_BAND_ATT_THRS_PROP
        if (DumpProperty(api,Si2190B_WIDE_BAND_ATT_THRS_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
        #endif /* Si2190B_WIDE_BAND_ATT_THRS_PROP */
        #ifdef    Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP
        if (DumpProperty(api,Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
        #endif /* Si2190B_TUNER_TF1_BOUNDARY_OFFSET_PROP */
    }
   return NO_Si21XXC_ERROR;

}
/***********************************************************************************************************************
  Si21XXC_DumpCommonProperties function
  Use:        Command to dump all changed properties to DDR memory.

  Parameter: *api     the Si21XXC context

  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the setProperty command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_DumpCommonProperties(L1_Si21XXC_Context *api)
{
    unsigned char tns[7];
    #ifdef    Si21XXC_CRYSTAL_TRIM_PROP
        if (DumpProperty(api,Si21XXC_CRYSTAL_TRIM_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
    #endif /* Si21XXC_CRYSTAL_TRIM_PROP */
    #ifdef    Si21XXC_MASTER_IEN_PROP
        if (DumpProperty(api,Si21XXC_MASTER_IEN_PROP,tns))
        {
               memcpy(ddrData[count++],&tns,7);
        }
    #endif /* Si21XXC_MASTER_IEN_PROP */

	#ifdef    Si21XXC_XOUT_PROP
    if (DumpProperty(api,Si21XXC_XOUT_PROP,tns))
    {
           memcpy(ddrData[count++],&tns,7);
    }
	#endif /* Si21XXC_XOUT_PROP */

    return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  Si21XXC_DumpProperties function
  Use:        Command to dump all changed properties to DDR memory.

  Parameter: *api     the Si21XXC context

  Behavior:  .
               The cmdByteBuffer is arranged so the first byte is the length of the I2C transaction
                The following bytes are the setProperty command.
  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_DumpProperties(L1_Si21XXC_Context *api)
{
    Si21XXC_DumpATVProperties(api);
    Si21XXC_DumpDTVProperties(api);
    Si21XXC_DumpTunerProperties(api);
    Si21XXC_DumpCommonProperties(api);

    return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  Si21XXC_DumpAllToMem function
  Use:        Dumps all changed properties and the current tuner status to memory

  Parameter: *api     the Si21XXC context

  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_DumpAllToMem(L1_Si21XXC_Context *api,unsigned long *ddrTunerDataAddr, unsigned long *ddrTunerDataSize )
{
    unsigned char tns[9];
    count=0;
//    int i = 0, j =0;

    memset((char*)ddrData, 0x00, sizeof(ddrData));
    // this will reset all shadow properties to the default
    Si21XXC_storePropertiesDefaults(api->propShadow);
    Si21XXC_DumpProperties(api);

    Si21XXC_L1_TUNER_STATUS (api, Si21XXC_TUNER_STATUS_CMD_INTACK_OK);
    if(api->rsp->tuner_status.freq <= 43000000)
    {
        api->rsp->tuner_status.freq = 43000000;
    }
    Si21XXC_L1_DUMP_TUNER_STATUS(api,api->rsp->tuner_status.mode,
                                             api->rsp->tuner_status.freq,tns);
    memcpy(ddrData[count++],&tns,9);
    *ddrTunerDataAddr = (unsigned long)ddrData;
    *ddrTunerDataSize =  sizeof(ddrData);
#if 0
    safe_printf(" ddrdata : %x   ddrTunerData :%x size: %x", (unsigned int)ddrData, (unsigned int)ddrTunerDataAddr,(unsigned int)*ddrTunerDataSize);
    safe_printf(" /************************** Si21XXC_DumpAllToMem    **************************************/\n");
    for(i =0;i< MAX_PROPS; i++)
    {
        for(j =0;j<9; j++)
        {

            safe_printf("%x ", ddrData[i][j]);
        }
       safe_printf("\n");
    }
    safe_printf(" /*******************************************************************************************/\n");
#endif

    return NO_Si21XXC_ERROR;
}
/***********************************************************************************************************************
  Si21XXC_RestoreFromMem function
  Use:        restores all changed properties from the kernel mode and updates the prop and propShadow structures.

  Parameter: *api     the Si21XXC context

  Returns:    0 if no error, an error code otherwise
 ***********************************************************************************************************************/

unsigned char Si21XXC_RestoreFromMem(L1_Si21XXC_Context *api)
{
    int i;
    unsigned int prop;
    int data;
    // this will restore the data from ddr memory to the prop structures
    // 1      2   3   4    5     6
    //0x14 0x00 0x0a 0x07 0x00 0x01
    for (i=0;i<count;i++)
    {
        if (ddrData[i][1]==0x14)
        {
            prop = (ddrData[i][4] << 8) | ddrData[i][3];
            data = (ddrData[i][6] << 8) | ddrData[i][5];
			Si21XXC_UnpackProperty (api->prop,prop,  data);
            Si21XXC_UnpackProperty (api->propShadow,prop,  data);
        }

    }

    return NO_Si21XXC_ERROR;
}
