/***************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 2 API
   L2 API for commands and properties
   FILE: Si2190_L2_API.c
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Tag:  ROM40_0_A_build_10_V0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/
#include <string.h>
/* Si2190 API Defines */
/* define this if using the ATV video filter */
#undef USING_ATV_FILTER
/* define this if using the DTV video filter */
#undef USING_DLIF_FILTER
/************************************************************************************************************************/
/* Si2190 API Specific Includes */
#include "Si2190_L2_API.h"               /* Include file for this code */
//#include "Si2190_firmware_0_A_build_10.h"       /* firmware compatible with Si2190-marking */
#include "Si2190_firmware_1_1_build_4.h"       /* firmware compatible with Si2190-marking */

#define Si2190_BYTES_PER_LINE 8
#ifdef USING_ATV_FILTER
#include "write_ATV_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
/************************************************************************************************************************
  NAME: Si2190_Configure
  DESCRIPTION: Setup Si2190 video filters, GPIOs/clocks, Common Properties startup, etc.
  Parameter:  Pointer to Si2190 Context
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_Configure           (L1_Si2190_Context *api)
{
    int return_code;
    return_code = NO_Si2190_ERROR;

/* _specific_configure_insertion_start */
 #ifdef USING_ATV_FILTER
    if ((return_code = Si2190_LoadVideofilter(api,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES)) != NO_Si2190_ERROR)
       return return_code;
  #endif
     /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = Si2190_LoadVideofilter(api,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != NO_Si2190_ERROR)
       return return_code;
  #endif
    /* _specific_configure_insertion_point */

    /* Set All Properties startup configuration */
    Si2190_setupAllDefaults     (api);
    Si2190_downloadAllProperties(api);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2190_PowerUpWithPatch
  DESCRIPTION: Send Si2190 API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si2190 Context
  Returns:    Si2190/I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_PowerUpWithPatch    (L1_Si2190_Context *api)
{
    int return_code;
    return_code = NO_Si2190_ERROR;

    /* always wait for CTS prior to POWER_UP command */
    if ((return_code = Si2190_pollForCTS  (api)) != NO_Si2190_ERROR) {
        SiTRACE ("Si2190_pollForCTS error 0x%02x\n", return_code);
        return return_code;
    }

    if ((return_code = Si2190_L1_POWER_UP (api,
                            Si2190_POWER_UP_CMD_SUBCODE_CODE,
                            Si2190_POWER_UP_CMD_CLOCK_MODE_XTAL,
                            Si2190_POWER_UP_CMD_EN_XOUT_DIS_XOUT,
                            Si2190_POWER_UP_CMD_PD_LDO_LDO_POWER_UP,
                            Si2190_POWER_UP_CMD_RESERVED2_RESERVED,
                            Si2190_POWER_UP_CMD_RESERVED3_RESERVED,
                            Si2190_POWER_UP_CMD_RESERVED4_RESERVED,
                            Si2190_POWER_UP_CMD_RESERVED5_RESERVED,
                            Si2190_POWER_UP_CMD_RESERVED6_RESERVED,
                            Si2190_POWER_UP_CMD_RESERVED7_RESERVED,
                            Si2190_POWER_UP_CMD_RESET_RESET,
                            Si2190_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                            Si2190_POWER_UP_CMD_RESERVED8_RESERVED,
                            Si2190_POWER_UP_CMD_FUNC_BOOTLOADER,
                            Si2190_POWER_UP_CMD_CTSIEN_DISABLE,
                            Si2190_POWER_UP_CMD_WAKE_UP_WAKE_UP
                            )) != NO_Si2190_ERROR)
    {
        SiTRACE ("Si2190_L1_POWER_UP error 0x%02x: %s\n", return_code, Si2190_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
    if ((return_code = Si2190_L1_PART_INFO(api)) != NO_Si2190_ERROR) {
        SiTRACE ("Si2190_L1_PART_INFO error 0x%02x: %s\n", return_code, Si2190_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    SiTRACE("chiprev %d\n",        api->rsp->part_info.chiprev);
    SiTRACE("part    Si21%d\n",    api->rsp->part_info.part   );
    SiTRACE("pmajor  %d\n",        api->rsp->part_info.pmajor );
    if (api->rsp->part_info.pmajor >= 0x30) {
    SiTRACE("pmajor '%c'\n",       api->rsp->part_info.pmajor );
    }
    SiTRACE("pminor  %d\n",        api->rsp->part_info.pminor );
    if (api->rsp->part_info.pminor >= 0x30) {
    SiTRACE("pminor '%c'\n",       api->rsp->part_info.pminor );
    }
    SiTRACE("romid %3d/0x%02x\n",  api->rsp->part_info.romid,  api->rsp->part_info.romid );
#ifdef    PART_INTEGRITY_CHECKS
    /* Check the Chip revision, part and ROMID against expected values and report an error if incompatible */
    if (api->rsp->part_info.chiprev != api->chiprev) {
        SiTRACE ("INCOMPATIBLE PART error chiprev %d (expected %d)\n", api->rsp->part_info.chiprev, api->chiprev);
        return_code = ERROR_Si2190_INCOMPATIBLE_PART;
    }
    /* Part Number is represented as the last 2 digits */
    if (api->rsp->part_info.part != api->part) {
        SiTRACE ("INCOMPATIBLE PART error part   %d (expected %d)\n", api->rsp->part_info.part, api->part);
        return_code = ERROR_Si2190_INCOMPATIBLE_PART;
    }
    /* Part Major Version in ASCII */
    if (api->rsp->part_info.pmajor != api->partMajorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pmajor %d (expected %d)\n", api->rsp->part_info.pmajor, api->partMajorVersion);
        return_code = ERROR_Si2190_INCOMPATIBLE_PART;
    }
    /* Part Minor Version in ASCII */
    if (api->rsp->part_info.pminor != api->partMinorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pminor %d (expected %d)\n", api->rsp->part_info.pminor, api->partMinorVersion);
        return_code = ERROR_Si2190_INCOMPATIBLE_PART;
    }
    /* ROMID in byte representation */
    if (api->rsp->part_info.romid != api->partRomid) {
        SiTRACE ("INCOMPATIBLE PART error romid %3d (expected %2d)\n", api->rsp->part_info.romid, api->partRomid);
        return_code = ERROR_Si2190_INCOMPATIBLE_PART;
    }
    if (return_code != NO_Si2190_ERROR) return return_code;
#endif /* PART_INTEGRITY_CHECKS */
      /* Load the Firmware */

 //   if (api->rsp->part_info.romid == 0x40) {
	if (api->rsp->part_info.romid == 0x41) {
      /* Load the Firmware */
 //      if ((return_code = Si2190_LoadFirmware(api, Si2190_FW_0_Ab10, FIRMWARE_LINES_0_Ab10)) != NO_Si2190_ERROR) {
       if ((return_code = Si2190_LoadFirmware(api, Si2190_FW_1_1b4, FIRMWARE_LINES_1_1b4)) != NO_Si2190_ERROR) {

		 SiTRACE ("Si2190_LoadFirmware error 0x%02x: %s\n", return_code, Si2190_L1_API_ERROR_TEXT(return_code) );
         return return_code;
       }
    }

    /*Start the Firmware */
    if ((return_code = Si2190_StartFirmware(api)) != NO_Si2190_ERROR) { /* Start firmware */
        SiTRACE ("Si2190_StartFirmware error 0x%02x: %s\n", return_code, Si2190_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2190_Firmware_x_y_build_z.h file into Si2190
              Requires Si2190 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2190 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2190/I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_LoadFirmware        (L1_Si2190_Context *api, firmware_struct fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2190_ERROR;

    SiTRACE ("Si2190_LoadFirmware starting...\n");
    SiTRACE ("Si2190_LoadFirmware nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si2190_BYTES_PER_LINE fw bytes to Si2190 */
//        if ((return_code = Si2190_L1_API_Patch(api, Si2190_BYTES_PER_LINE, fw_table + Si2190_BYTES_PER_LINE*line)) != NO_Si2190_ERROR)
		if ((return_code = Si2190_L1_API_Patch(api, fw_table[line].firmware_len, fw_table[line].firmware_table)) != NO_Si2190_ERROR)
        {
          SiTRACE("Si2190_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2190_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si2190_LOADING_FIRMWARE;
        }
        if (line==3) {SiTraceConfiguration("traces suspend");}
    }
    SiTraceConfiguration("traces resume");
    SiTRACE ("Si2190_LoadFirmware complete...\n");
    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_StartFirmware
  DESCRIPTION: Start Si2190 firmware (put the Si2190 into run mode)
  Parameter:   Si2190 Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_StartFirmware       (L1_Si2190_Context *api)
{

    if (Si2190_L1_EXIT_BOOTLOADER(api, Si2190_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si2190_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si2190_ERROR)
    {
        return ERROR_Si2190_STARTING_FIRMWARE;
    }

    return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_Init
  DESCRIPTION:Reset and Initialize Si2190
  Parameter:  Si2190 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_Init                (L1_Si2190_Context *api)
{
    int return_code;
    SiTRACE("Si2190_Init starting...\n");

    if ((return_code = Si2190_PowerUpWithPatch(api)) != NO_Si2190_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si2190_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si2190_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si2190_Configure(api);
    SiTRACE("Si2190_Init complete...\n");
    return NO_Si2190_ERROR;
}
/* _specific_code_insertion_start */
 /************************************************************************************************************************
  NAME: Si2190_UpdateChannelScanFrequency
  DESCRIPTION:  This routine allows the user to implement an update of the current channel scan operation with
                the current frequency being scanned.
  Parameter:    Current frequency of the scan routine
  Parameter:  channelsFound = 0 if channel not found at that frequency , channelsFound > 0  the number of channels
        currently found( including this frequency )
  Returns:      1 if scan abort requested, 0 if ok.
************************************************************************************************************************/
int Si2190_UpdateChannelScanFrequency(int freq,int channelsFound)
{
  int abort_scan = 0;
  static int previousFrequency;
/*** Insert user code to display realtime updates of the frequency being scanned and channel status (number found ) **/
/* add check for user abort here */
  if (channelsFound)
  {
    /* Terminate the previous scan message */
    printf("Found Frequency %d\n",freq);
  }
  else
  {
    if (freq==previousFrequency)
      printf("Not Found\n");
    else
      printf("Scanning Frequency %d, ",freq);
  }
  previousFrequency=freq;

  if (abort_scan)
    return 1;
  else
    return 0;
  }
 /************************************************************************************************************************
  NAME: Si2190_GetRF
  DESCRIPTIION: Retrieve Si2190 tune freq

  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns  :  frequency (Hz) as an int
************************************************************************************************************************/
int  Si2190_GetRF             (L1_Si2190_Context *api)
{
    Si2190_L1_TUNER_STATUS (api, Si2190_TUNER_STATUS_CMD_INTACK_OK);
        return api->rsp->tuner_status.freq;
}
 /************************************************************************************************************************
  NAME: Si2190_Tune
  DESCRIPTIION: Tune Si2190 in specified mode (ATV/DTV) at center frequency, wait for TUNINT and xTVINT with timeout

  Parameter:  Pointer to Si2190 Context (I2C address)
  Parameter:  Mode (ATV or DTV) use Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV or Si2190_TUNER_TUNE_FREQ_CMD_MODE_DTV constants
  Parameter:  frequency (Hz) as a unsigned long integer
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
 int  Si2190_Tune              (L1_Si2190_Context *api, unsigned char mode, unsigned long freq)
{
    int start_time  = 0;
    int return_code = 0;
    int timeout     = 150;

    start_time = system_time();

    if (Si2190_L1_TUNER_TUNE_FREQ (api,
                                   mode,
                                   freq) != NO_Si2190_ERROR)
    {
        return ERROR_Si2190_SENDING_COMMAND;
    }

    /* wait for TUNINT, timeout is 150ms */
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2190_L1_CheckStatus(api)) != 0)
            return return_code;
        if (api->status->tunint)
            break;
    }
    if (!api->status->tunint) {
      SiTRACE("Timeout waiting for TUNINT\n");
      return ERROR_Si2190_TUNINT_TIMEOUT;
    }

    /* wait for xTVINT, timeout is 350ms for ATVINT and 20 ms for DTVINT */
    start_time = system_time();
    timeout    = ((mode==Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? 350 : 20);
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si2190_L1_CheckStatus(api)) != 0)
            return return_code;
        if (mode==Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV)
        {
         if (api->status->atvint)
            break;
        }
        else
        {
         if (api->status->dtvint)
            break;
        }
    }

    if (mode==Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV)
    {
      if (api->status->atvint)
      {
        SiTRACE("ATV Tune Successful\n");
           return NO_Si2190_ERROR;
        }
      else
        {SiTRACE("Timeout waiting for ATVINT\n");}
    }
    else
    {
        if (api->status->dtvint)
        {
          SiTRACE("DTV Tune Successful\n");
          return NO_Si2190_ERROR;
        }
        else
          {SiTRACE("Timeout waiting for DTVINT\n");}
    }

    return ERROR_Si2190_xTVINT_TIMEOUT;
}
 /************************************************************************************************************************
  NAME: Si2190_ATVTune
  DESCRIPTION:Update ATV_VIDEO_MODE and tune ATV mode at center frequency
  Parameter:  Pointer to Si2190 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  color , e.g. use constant Si2190_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Parameter:  invert_signal, 0= normal, 1= inverted
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2190_ATVTune           (L1_Si2190_Context *api, unsigned long freq, unsigned char video_sys,unsigned char color, unsigned char invert_signal)
{
    /* update ATV_VIDEO_MODE property */
    api->prop->atv_video_mode.video_sys = video_sys;
    api->prop->atv_video_mode.color = color;
    api->prop->atv_video_mode.invert_signal=invert_signal;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_VIDEO_MODE_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }

    return Si2190_Tune (api, Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq);
}
 /************************************************************************************************************************
  NAME: Si2190_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si2190 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si2190_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2190_DTVTune           (L1_Si2190_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum)
{
    int return_code;
    return_code = NO_Si2190_ERROR;

    /* update DTV_MODE_PROP property */
    api->prop->dtv_mode.bw = bw;
    api->prop->dtv_mode.invert_spectrum = invert_spectrum;
    api->prop->dtv_mode.modulation = modulation;
    if (Si2190_L1_SetProperty2(api, Si2190_DTV_MODE_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }

    return_code = Si2190_Tune (api, Si2190_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq);

    return return_code;
}

 /************************************************************************************************************************
  NAME: Si2190_XoutOn
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_XoutOn             (L1_Si2190_Context *api)
{
    int return_code=0;
    SiTRACE("Si2190_XoutOn:  Turning Xout ON\n");

    if ((return_code = Si2190_L1_CONFIG_CLOCKS(api,
                                              Si2190_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              Si2190_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL,
                                              Si2190_CONFIG_CLOCKS_CMD_EN_XOUT_EN_XOUT)) != NO_Si2190_ERROR)
    return return_code;

    return NO_Si2190_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2190_XoutOff
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_XoutOff            (L1_Si2190_Context *api)
{
    int return_code=0;
    SiTRACE("Si2190_XoutOff:  Turning Xout OFF\n");

    if ((return_code = Si2190_L1_CONFIG_CLOCKS(api,
                                              Si2190_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              Si2190_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL,
                                              Si2190_CONFIG_CLOCKS_CMD_EN_XOUT_DIS_XOUT)) != NO_Si2190_ERROR)
    return return_code;

    return NO_Si2190_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2190_Standby
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_Standby         (L1_Si2190_Context *api)
{
    int return_code;
    SiTRACE("Si2190_Standby: Going to Standby.  The part will awake on the next command.\n");

    if ((return_code = Si2190_L1_STANDBY(api, Si2190_STANDBY_CMD_TYPE_LNA_ON)) != NO_Si2190_ERROR)
    return return_code;

    return NO_Si2190_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2190_Powerdown
  Parameter:  Pointer to Si2190 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_Powerdown         (L1_Si2190_Context *api)
{
    int return_code;
    SiTRACE("Si2190_Powerdown: Powering down the part.  Select InitAndConfig to reload.\n");

    if ((return_code = Si2190_L1_POWER_DOWN(api)) != NO_Si2190_ERROR)
    return return_code;

    return NO_Si2190_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2190_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si2190_write_xTV_video_coeffs.h file into Si2190
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si2190 Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array (size in bytes / Si2190_BYTES_PER_LINE)
  Returns:    Si2190/I2C transaction error code, NO_Si2190_ERROR if successful
************************************************************************************************************************/
int Si2190_LoadVideofilter     (L1_Si2190_Context *api,vid_filt_struct vidFiltTable[], int lines)
{
    int line;
     /* for each line in VIDFILT_TABLE (max 16 bytes)  */
    for (line = 0; line < lines ; line++)
    {
        /* send up to 16 byte I2C command to Si2190 */
        if (Si2190_L1_API_Patch(api, vidFiltTable[line].vid_filt_len, vidFiltTable[line].vid_filt_table) != NO_Si2190_ERROR)
        {
            return ERROR_Si2190_SENDING_COMMAND;
        }
    }
    return NO_Si2190_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2190_ATV_Channel_Scan_M
  DESCRIPTION: Performs a channel scan for NTSC (System M) of the band
  Programming Guide Reference:    Flowchart A.11.0 and A11.1 (ATV Channel Scan flowchart for System M)

  Parameter:  Pointer to Si2190 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2190_ATV_Channel_Scan_M (L1_Si2190_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB)
{
    #define SCAN_INTERVAL     1000000
    #define CHANNEL_BANDWIDTH 6000000
    #define CHANNEL_NOT_FOUND       0

    unsigned long freq;
    int i;

    /*Clear the channel list size and channel array */
    api->ChannelListSize=0;

    for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
        api->ChannelList[i]=0;
    /* configure the VideoMode property to System M, NTSC*/
    api->prop->atv_video_mode.video_sys = Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;       /* M ATV demodulation       */
    api->prop->atv_video_mode.color     = Si2190_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system    */
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_VIDEO_MODE_PROP) != NO_Si2190_ERROR)
    {
       return ERROR_Si2190_SENDING_COMMAND;
    }
    /* configure the RSQ / RSSI threshold properties */
    api->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    api->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2190_L1_SetProperty2(api, Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2190_ERROR)
    {
       return ERROR_Si2190_SENDING_COMMAND;
    }

  /* configure the RSQ / SNR threshold properties */
    api->prop->atv_rsq_snr_threshold.lo = minSNRHalfdB;
    api->prop->atv_rsq_snr_threshold.hi = maxSNRHalfdB;

    if (Si2190_L1_SetProperty2(api, Si2190_ATV_RSQ_SNR_THRESHOLD_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }

  /* setup IEN properties to enable TUNINT on TC  */
    api->prop->tuner_ien.tcien     =  Si2190_TUNER_IEN_PROP_TCIEN_ENABLE;
    api->prop->tuner_ien.rssilien  =  Si2190_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    api->prop->tuner_ien.rssihien  =  Si2190_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2190_L1_SetProperty2(api, Si2190_TUNER_IEN_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    api->prop->atv_ien.chlien    =  Si2190_ATV_IEN_PROP_CHLIEN_ENABLE;
    api->prop->atv_ien.pclien    =  Si2190_ATV_IEN_PROP_PCLIEN_DISABLE;
    api->prop->atv_ien.dlien     =  Si2190_ATV_IEN_PROP_DLIEN_DISABLE;
    api->prop->atv_ien.snrlien   =  Si2190_ATV_IEN_PROP_SNRLIEN_DISABLE;
    api->prop->atv_ien.snrhien   =  Si2190_ATV_IEN_PROP_SNRHIEN_DISABLE;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_IEN_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }
    /* setup ATV audio property for wide SIF scanning*/
    api->prop->atv_audio_mode.audio_sys    =  Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
    api->prop->atv_audio_mode.chan_filt_bw    =    Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW_DEFAULT;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_AUDIO_MODE_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    api->prop->atv_afc_range.range_khz    =  1500;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_AFC_RANGE_PROP) != NO_Si2190_ERROR)
    {
       return ERROR_Si2190_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {

    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2190_Tune (api, Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {

            /* Get ATV status */
      if (Si2190_L1_ATV_STATUS (api, Si2190_ATV_STATUS_CMD_INTACK_OK))
      {
        return ERROR_Si2190_SENDING_COMMAND;
      }


      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      api->ChannelList[api->ChannelListSize]= freq + (api->rsp->atv_status.afc_freq * 1000);
      /* Update the callback to indicate the channel is found */
      /* if user requested abort then break from the loop */
      if (Si2190_UpdateChannelScanFrequency(freq + (api->rsp->atv_status.afc_freq * 1000), api->ChannelListSize+1))
        break;

            freq = api->ChannelList[api->ChannelListSize++] + CHANNEL_BANDWIDTH;
         }
         else  /* We didn't find a station at this frequency so increment and move on */
         {
        /* if user requested abort then break from the loop */
      if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
        break;
      /*  channel not found! **/
             freq += SCAN_INTERVAL;
         }
    }
    /* Set AFC Range back to 100  */
    api->prop->atv_afc_range.range_khz    =  100;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_AFC_RANGE_PROP) != NO_Si2190_ERROR)
    {
        return ERROR_Si2190_SENDING_COMMAND;
    }
   return NO_Si2190_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2190_ATV_Channel_Scan_PAL
  DESCRIPTION: Performs a channel scan for PAL (Systems B/G, D/K, L/L', and I) of the band
  Programming Guide Reference:    Flowchart A.10.0 - A10.3 (ATV Channel Scan flowchart for PAL)

  NOTE: this function requires an external sound processor to determine the PAL standard.  The user is
  required to implement the functions: L0_InitSoundProcessor(); and L0_AcquireSoundStandard(..);

  Parameter:  Pointer to Si2190 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2190_ATV_Channel_Scan_PAL(L1_Si2190_Context *api, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm, int minSNRHalfdB, int maxSNRHalfdB)
{

  #define VHF_MAX 300000000
  #define SCAN_INTERVAL 1000000
  #define CHANNEL_NOT_FOUND 0
  char standard = Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
  unsigned long freq;
  unsigned long channelIncrement;
  char posModulation;  /* flag for pos or neg modulation */
  int i;

  /*Clear the channel list size and channel array */
  api->ChannelListSize=0;

  for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
  {
    api->ChannelList[i]=0;
    api->ChannelType[i][0]='\0';
  }
    /* configure the RSQ / RSSI threshold properties */
    api->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    api->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2190_L1_SetProperty2(api, Si2190_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2190_ERROR)
    {
       return ERROR_Si2190_SENDING_COMMAND;
    }
 /* configure the RSQ / SNR threshold properties */
    api->prop->atv_rsq_snr_threshold.lo = minSNRHalfdB;
    api->prop->atv_rsq_snr_threshold.hi = maxSNRHalfdB;

    if (Si2190_L1_SetProperty2(api, Si2190_ATV_RSQ_SNR_THRESHOLD_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }
  /* setup IEN properties to enable TUNINT on TC  */
    api->prop->tuner_ien.tcien     =  Si2190_TUNER_IEN_PROP_TCIEN_ENABLE;
    api->prop->tuner_ien.rssilien  =  Si2190_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    api->prop->tuner_ien.rssihien  =  Si2190_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2190_L1_SetProperty2(api, Si2190_TUNER_IEN_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    api->prop->atv_ien.chlien    =  Si2190_ATV_IEN_PROP_CHLIEN_ENABLE;
    api->prop->atv_ien.pclien    =  Si2190_ATV_IEN_PROP_PCLIEN_DISABLE;
    api->prop->atv_ien.dlien     =  Si2190_ATV_IEN_PROP_DLIEN_DISABLE;
    api->prop->atv_ien.snrlien   =  Si2190_ATV_IEN_PROP_SNRLIEN_DISABLE;
    api->prop->atv_ien.snrhien   =  Si2190_ATV_IEN_PROP_SNRHIEN_DISABLE;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_IEN_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }
   /* setup ATV audio property for wide SIF scanning*/
    api->prop->atv_audio_mode.audio_sys    =  Si2190_ATV_AUDIO_MODE_PROP_AUDIO_SYS_DEFAULT;
    api->prop->atv_audio_mode.chan_filt_bw    =  Si2190_ATV_AUDIO_MODE_PROP_CHAN_FILT_BW_DEFAULT;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_AUDIO_MODE_PROP) != NO_Si2190_ERROR)
    {
      return ERROR_Si2190_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    api->prop->atv_afc_range.range_khz    =  1500;
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_AFC_RANGE_PROP) != NO_Si2190_ERROR)
    {
       return ERROR_Si2190_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {
    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;
    /* set the modulation flag to 0 (neg) */
    posModulation=0;
    /* Negative Modulation configure the VideoMode property to System DK, PAL*/
    api->prop->atv_video_mode.video_sys = Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;    /* M ATV demodulation */
    api->prop->atv_video_mode.color     = Si2190_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;      /* PAL_NTSC color system    */
    if (Si2190_L1_SetProperty2(api, Si2190_ATV_VIDEO_MODE_PROP) != NO_Si2190_ERROR)
    {
       return ERROR_Si2190_SENDING_COMMAND;
    }

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2190_Tune (api, Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {
      posModulation = 0;
    }
    else  /* We didn't find a station so try positive modulation */
     {
      /* Pos Modulation configure the VideoMode property to System DK, PAL*/
      api->prop->atv_video_mode.video_sys = Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;       /* L ATV demodulation       */
      api->prop->atv_video_mode.color     = Si2190_ATV_VIDEO_MODE_PROP_COLOR_SECAM;       /* SECAM color system       */
      if (Si2190_L1_SetProperty2(api, Si2190_ATV_VIDEO_MODE_PROP) != NO_Si2190_ERROR)
      {
         return ERROR_Si2190_SENDING_COMMAND;
      }
      /* Call the Tune command to tune the frequency */
      /* if successful (a station was found) then the return value will be 0. */
      if (!Si2190_Tune (api, Si2190_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
      {
        posModulation=1;
      }
      else
      {
            /* if user requested abort then break from the loop */
          if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

        /* we didn't find any channels goto flowchart section B */
        freq += SCAN_INTERVAL;
        continue;
      }
    }
    /* Initialize the sound processor.   This may or may not be required for your application */
/*    L1_InitSoundProcessor();*/
    /* Run the sound processor and return the standard(s) */
 /*   #define SOUND_PROCESSOR_TIMEOUT 10 */
/*    L1_AcquireSoundStandard(SOUND_PROCESSOR_TIMEOUT , &standard);*/
    if ((standard == Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B) || (standard == Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH))
      {
      /* check for positive modulation */
      if (posModulation)
    {
          /* if user requested abort then break from the loop */
          if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
      else
    {
        if (freq < VHF_MAX)
        {
          api->ChannelType[api->ChannelListSize][0]='B';
          api->ChannelType[api->ChannelListSize][1]='\0';
    }
    else
    {
          api->ChannelType[api->ChannelListSize][0]='G';
          api->ChannelType[api->ChannelListSize][1]='H';
          api->ChannelType[api->ChannelListSize][2]='\0';
    }
    }
    }
    else if (standard == Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
    {
        if (posModulation)
    {
                /* if user requested abort then break from the loop */
              if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
                break;

          /* goto flowchart section B */
          freq += SCAN_INTERVAL;
          continue;
    }
        else
    {
          api->ChannelType[api->ChannelListSize][0]='I';
          api->ChannelType[api->ChannelListSize][1]='\0';
    }
    }
    else if ((standard == Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L) || (standard == Si2190_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK))
    {
        if (posModulation)
    {
          api->ChannelType[api->ChannelListSize][0]='L';
          api->ChannelType[api->ChannelListSize][1]='\0';
    }
        else
    {
          api->ChannelType[api->ChannelListSize][0]='D';
          api->ChannelType[api->ChannelListSize][1]='K';
          api->ChannelType[api->ChannelListSize][2]='\0';
    }
    }
    else
    {
      /* standard not found */
    /* if user requested abort then break from the loop */
    if (Si2190_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
            }
    /* if we got here, then we have a valid channel with a channelType */
                    /* Get ATV status */
              if (Si2190_L1_ATV_STATUS (api, Si2190_ATV_STATUS_CMD_INTACK_OK))
              {
                return ERROR_Si2190_SENDING_COMMAND;
              }
    if (api->ChannelType[api->ChannelListSize][0]=='B')
              {
            /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      api->ChannelList[api->ChannelListSize]= freq + (api->rsp->atv_status.afc_freq * 1000)-500000;
                  channelIncrement = 7000000;
              }
              else
              {
                /* Add the afc_freq (khz) to the center frequency and add to the channel list */
                api->ChannelList[api->ChannelListSize]= freq + (api->rsp->atv_status.afc_freq * 1000);
                channelIncrement = 8000000;
              }
           /* Update the callback to indicate the channel is found */
            /* if user requested abort then break from the loop */
            if (Si2190_UpdateChannelScanFrequency(api->ChannelList[api->ChannelListSize], api->ChannelListSize+1))
              break;
            /* go to the next frequency in the loop */
            freq = api->ChannelList[api->ChannelListSize++] + channelIncrement;
    }


   return NO_Si2190_ERROR;
}
/************************************************************************************************************************
  NAME: Si2190_AGC_Override
  Parameter:  Pointer to Si2190 Context (I2C address)
  Parameter:  Mode 0=Normal, 1= Max, 2=TOP
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2190_AGC_Override    (L1_Si2190_Context *Si2190, unsigned char mode )
{
    int return_code;
    SiTRACE("Si2190_AGC_Override: mode = %d\n",mode);
    switch (mode)
    {
        case  Si2190_FORCE_NORMAL_AGC:
            if ((return_code = Si2190_L1_AGC_OVERRIDE (Si2190, Si2190_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2190_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2190_ERROR)
                return return_code;
            break;
        case  Si2190_FORCE_MAX_AGC:
            if ((return_code = Si2190_L1_AGC_OVERRIDE (Si2190, Si2190_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE,Si2190_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2190_ERROR)
                return return_code;
            break;
        case  Si2190_FORCE_TOP_AGC:
            if ((return_code = Si2190_L1_AGC_OVERRIDE (Si2190, Si2190_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2190_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE)) != NO_Si2190_ERROR)
                return return_code;
            break;

        default:
            return ERROR_Si2190_PARAMETER_OUT_OF_RANGE;

    }

    return NO_Si2190_ERROR;
}



///tqy
int SSVD_AIC_ON(L1_Si2190_Context *Si2190Ct)
{
 unsigned int data[] = { 0x0109, 0x4500, 0xE0BF, 0x0002, 0x00A3, 0xAA00, 0x3020, 0x0103, 0x00A6 };

 if (Si2190_L1_SSVD_MULTI_REG_WR(Si2190Ct, 0,Si2190_SSVD_REG_WR_CMD_UPDATE_UPDATE,7,data[0],data[1],data[2],data[3],data[4],data[5],data[6]) != NO_Si2190_ERROR)
    {
        //printf("Error reading Si2190_L1_SSVD_MULTI_REG_WR\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }

 if (Si2190_L1_SSVD_MULTI_REG_WR(Si2190Ct, 7,Si2190_SSVD_REG_WR_CMD_UPDATE_UPDATE,2,data[7],data[8],0,0,0,0,0) != NO_Si2190_ERROR)
    {
        //printf("Error reading Si2190_L1_SSVD_MULTI_REG_WR\n");
        return ERROR_Si2190_SENDING_COMMAND;
    }

    return NO_Si2190_ERROR;
}

 

int SSVD_AIC_OFF(L1_Si2190_Context *Si2190Ct)
{
    unsigned int data = 0x0101;

 if (Si2190_L1_SSVD_REG_WR(Si2190Ct,0,Si2190_SSVD_REG_WR_CMD_UPDATE_UPDATE,Si2190_SSVD_REG_WR_CMD_IGNORED_MIN,data) != NO_Si2190_ERROR)
 {
     //printf("Error reading Si2190_L1_SSVD_REG_WR\n");
     return ERROR_Si2190_SENDING_COMMAND;
 }

    return NO_Si2190_ERROR;
}

//XuGuang's Functions

unsigned char Si2190_Set_DTV_LIF_FREQ  (L1_Si2190_Context *api, unsigned int IFKHz)
{
	int data;
    data = (IFKHz & Si2190_DTV_LIF_FREQ_PROP_OFFSET_MASK) << Si2190_DTV_LIF_FREQ_PROP_OFFSET_LSB ;
	return Si2190_L1_SetProperty (api,Si2190_DTV_LIF_FREQ_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_DTV_LIF_OUT  (L1_Si2190_Context *api, unsigned char lif_out_offset,  unsigned char lif_out_amp)
{
 	int data;
 	data = (lif_out_offset & Si2190_DTV_LIF_OUT_PROP_OFFSET_MASK) << Si2190_DTV_LIF_OUT_PROP_OFFSET_LSB  |
           (lif_out_amp & Si2190_DTV_LIF_OUT_PROP_AMP_MASK   ) << Si2190_DTV_LIF_OUT_PROP_AMP_LSB ;

	return Si2190_L1_SetProperty (api,Si2190_DTV_LIF_OUT_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_DTV_MODE  (L1_Si2190_Context *api, unsigned char bw, unsigned char invert_spectrum, unsigned char modulation)
{
 	int data;
    data = (bw              & Si2190_DTV_MODE_PROP_BW_MASK             ) << Si2190_DTV_MODE_PROP_BW_LSB  |
           (modulation      & Si2190_DTV_MODE_PROP_MODULATION_MASK     ) << Si2190_DTV_MODE_PROP_MODULATION_LSB  |
           (invert_spectrum & Si2190_DTV_MODE_PROP_INVERT_SPECTRUM_MASK) << Si2190_DTV_MODE_PROP_INVERT_SPECTRUM_LSB ;

	return Si2190_L1_SetProperty (api,Si2190_DTV_MODE_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_ATV_SIF_OUT  (L1_Si2190_Context *api, unsigned char amp, unsigned char offset)
{
 	int data;
    data = (offset & Si2190_ATV_SIF_OUT_PROP_OFFSET_MASK) << Si2190_ATV_SIF_OUT_PROP_OFFSET_LSB  |
           (amp    & Si2190_ATV_SIF_OUT_PROP_AMP_MASK   ) << Si2190_ATV_SIF_OUT_PROP_AMP_LSB ;

	return Si2190_L1_SetProperty (api, Si2190_ATV_SIF_OUT_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_TUNER_LO_INJECTION  (L1_Si2190_Context *api, unsigned char band_1, unsigned char band_2, unsigned char band_3)
{
 	int data;
    data = (band_1 & Si2190_TUNER_LO_INJECTION_PROP_BAND_1_MASK) << Si2190_TUNER_LO_INJECTION_PROP_BAND_1_LSB  |
           (band_2 & Si2190_TUNER_LO_INJECTION_PROP_BAND_2_MASK) << Si2190_TUNER_LO_INJECTION_PROP_BAND_2_LSB  |
           (band_3 & Si2190_TUNER_LO_INJECTION_PROP_BAND_3_MASK) << Si2190_TUNER_LO_INJECTION_PROP_BAND_3_LSB ;

	return Si2190_L1_SetProperty (api, Si2190_TUNER_LO_INJECTION_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_ATV_AGC_SPEED  (L1_Si2190_Context *api, unsigned char if_agc_speed)
{
 	int data;
    data = (if_agc_speed & Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_MASK) << Si2190_ATV_AGC_SPEED_PROP_IF_AGC_SPEED_LSB ;
 
	return Si2190_L1_SetProperty (api, Si2190_ATV_AGC_SPEED_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_ATV_RF_TOP (L1_Si2190_Context *api, unsigned char atv_rf_top)
{
 	int data;
    data = (atv_rf_top & Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP_MASK) << Si2190_ATV_RF_TOP_PROP_ATV_RF_TOP_LSB ;

	return Si2190_L1_SetProperty (api, Si2190_ATV_RF_TOP_PROP_CODE & 0xffff, data);
}

unsigned char Si2190_Set_DTV_RF_TOP (L1_Si2190_Context *api, unsigned char dtv_rf_top)
{
 	int data;
     data = (dtv_rf_top & Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP_MASK) << Si2190_DTV_RF_TOP_PROP_DTV_RF_TOP_LSB ;

	return Si2190_L1_SetProperty (api, Si2190_DTV_RF_TOP_PROP_CODE & 0xffff, data);
}
