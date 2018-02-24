/***************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 2 API
   L2 API for commands and properties
   FILE: Si2158_L2_API.c
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_1_build_9
   Revision: 0.1
   Tag:  ROM33_2_1_build_9_V0.1
   Date: March 20 2013
  (C) Copyright 2013, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/
#include <string.h>
/* Si2158 API Defines */
/* define this if using the ATV video filter */
#undef USING_ALIF_FILTER
/* define this if using the DTV video filter */
#undef USING_DLIF_FILTER
/************************************************************************************************************************/
/* Si2158 API Specific Includes */
#include "Si2158_L2_API.h"               /* Include file for this code */
#include "Si2158_firmware_0_E_build_15.h"       /* firmware compatible with Si2158-marking */
#include "Si2158_firmware_2_1_build_9.h"
#define Si2158_BYTES_PER_LINE 8
#ifdef USING_ALIF_FILTER
#include "write_ALIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
/************************************************************************************************************************
  NAME: Si2158_Configure
  DESCRIPTION: Setup Si2158 video filters, GPIOs/clocks, Common Properties startup, etc.
  Parameter:  Pointer to Si2158 Context
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_Configure           (L1_Si2158_Context *api)
{
    int return_code;
    return_code = NO_Si2158_ERROR;
/* _specific_configure_insertion_start */
 #ifdef USING_ALIF_FILTER
    if ((return_code = Si2158_LoadVideofilter(api,ALIF_VIDFILT_TABLE,ALIF_VIDFILT_LINES)) != NO_Si2158_ERROR)
       return return_code;
  #endif
     /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = Si2158_LoadVideofilter(api,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != NO_Si2158_ERROR)
       return return_code;
  #endif
    /* _specific_configure_insertion_point */
    /* Set All Properties startup configuration */
    Si2158_setupAllDefaults     (api);
    Si2158_downloadAllProperties(api);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2158_PowerUpWithPatch
  DESCRIPTION: Send Si2158 API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si2158 Context
  Returns:    Si2158/I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_PowerUpWithPatch    (L1_Si2158_Context *api)
{
    int return_code;
    return_code = NO_Si2158_ERROR;

    /* always wait for CTS prior to POWER_UP command */
    if ((return_code = Si2158_pollForCTS  (api)) != NO_Si2158_ERROR) {
        SiTRACE ("Si2158_pollForCTS error 0x%02x\n", return_code);
        return return_code;
    }

    if ((return_code = Si2158_L1_POWER_UP (api,
                            Si2158_POWER_UP_CMD_SUBCODE_CODE,
                            Si2158_POWER_UP_CMD_CLOCK_MODE_XTAL,
                            Si2158_POWER_UP_CMD_EN_XOUT_DIS_XOUT,
                            Si2158_POWER_UP_CMD_PD_LDO_LDO_POWER_UP,
                            Si2158_POWER_UP_CMD_RESERVED2_RESERVED,
                            Si2158_POWER_UP_CMD_RESERVED3_RESERVED,
                            Si2158_POWER_UP_CMD_RESERVED4_RESERVED,
                            Si2158_POWER_UP_CMD_RESERVED5_RESERVED,
                            Si2158_POWER_UP_CMD_RESERVED6_RESERVED,
                            Si2158_POWER_UP_CMD_RESERVED7_RESERVED,
                            Si2158_POWER_UP_CMD_RESET_RESET,
                            Si2158_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                            Si2158_POWER_UP_CMD_RESERVED8_RESERVED,
                            Si2158_POWER_UP_CMD_FUNC_BOOTLOADER,
                            Si2158_POWER_UP_CMD_CTSIEN_DISABLE,
                            Si2158_POWER_UP_CMD_WAKE_UP_WAKE_UP
                            )) != NO_Si2158_ERROR)
    {
        SiTRACE ("Si2158_L1_POWER_UP error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
    if ((return_code = Si2158_L1_PART_INFO(api)) != NO_Si2158_ERROR) {
        SiTRACE ("Si2158_L1_PART_INFO error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
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
        return_code = ERROR_Si2158_INCOMPATIBLE_PART;
    }
    /* Part Number is represented as the last 2 digits */
    if (api->rsp->part_info.part != api->part) {
        SiTRACE ("INCOMPATIBLE PART error part   %d (expected %d)\n", api->rsp->part_info.part, api->part);
        return_code = ERROR_Si2158_INCOMPATIBLE_PART;
    }
    /* Part Major Version in ASCII */
    if (api->rsp->part_info.pmajor != api->partMajorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pmajor %d (expected %d)\n", api->rsp->part_info.pmajor, api->partMajorVersion);
        return_code = ERROR_Si2158_INCOMPATIBLE_PART;
    }
    /* Part Minor Version in ASCII */
    if (api->rsp->part_info.pminor != api->partMinorVersion) {
        SiTRACE ("INCOMPATIBLE PART error pminor %d (expected %d)\n", api->rsp->part_info.pminor, api->partMinorVersion);
        return_code = ERROR_Si2158_INCOMPATIBLE_PART;
    }
    /* ROMID in byte representation */
    if (api->rsp->part_info.romid != api->partRomid) {
        SiTRACE ("INCOMPATIBLE PART error romid %3d (expected %2d)\n", api->rsp->part_info.romid, api->partRomid);
        return_code = ERROR_Si2158_INCOMPATIBLE_PART;
    }
    if (return_code != NO_Si2158_ERROR) return return_code;
#endif /* PART_INTEGRITY_CHECKS */
      /* Load the Firmware based on ROMID */
    if (api->rsp->part_info.romid == 0x32)
    {
      /* Load the Firmware */
        if ((return_code = Si2158_LoadFirmware(api, Si2158_FW_0_Eb15, FIRMWARE_LINES_0_Eb15)) != NO_Si2158_ERROR) {
         SiTRACE ("Si2158_LoadFirmware error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
         return return_code;
       }
    }
    else if (api->rsp->part_info.romid == 0x33) /* if Si2158-A20 part load firmware patch (currently a dummy patch , 20bx) */
    {
        /* This dummy patch (20bx) will skip the loadFirmware function and boot from NVM only.
           When a new patch is available for the Si2158-A20, include the patch file and replace the firmware array and size in the function below */
        if ((return_code = Si2158_LoadFirmware_16(api, Si2158_FW_2_1b9, FIRMWARE_LINES_2_1b9)) != NO_Si2158_ERROR)
        {
          SiTRACE ("Si2158_LoadFirmware_16 error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
          return return_code;
        }
    }
    else
    {
        SiTRACE ("INCOMPATIBLE PART error ROMID 0x%02x (expected 0x%02x)\n", api->rsp->part_info.romid, api->partRomid);
        return ERROR_Si2158_INCOMPATIBLE_PART;
    }
   /* Check the RAM_CRC value and compare with the expected value */
    /* If they match then move on,  otherwise indicate error */
    /* This check is bypassed by default to speed boot time. */

#ifdef   RAM_CRC_CHECK
    if ((return_code = Si2158_L1_RAM_CRC(api)) != NO_Si2158_ERROR)
    {
         SiTRACE ("Si2158_L1_RAM_CRC error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
         return return_code;
    }
    SiTRACE("RAM CRC = 0x%X\n",api->rsp->ram_crc.crc);
    if (api->rsp->ram_crc.crc != RAM_CRC_2_1b9)
    {
        return_code = ERROR_Si2158_CRC_CHECK_ERROR;
        SiTRACE ("RAM_CRC (0x%X) does not match expected (0x%X) error 0x%02x: %s\n",api->rsp->ram_crc.crc,RAM_CRC_2_1b9,return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
#endif /* RAM_CRC_CHECK */
    /*Start the Firmware */
    if ((return_code = Si2158_StartFirmware(api)) != NO_Si2158_ERROR) { /* Start firmware */
        SiTRACE ("Si2158_StartFirmware error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    return NO_Si2158_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158_LoadFirmware_16
  DESCRIPTON: Load firmware from firmware_struct array in Si2158_Firmware_x_y_build_z.h file into Si2158
              Requires Si2158 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2158 Context (I2C address)
  Parameter:  pointer to firmware_struct array
  Parameter:  number of lines in firmware table array (size in bytes / firmware_struct)
  Returns:    Si2158/I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_LoadFirmware_16        (L1_Si2158_Context *api, firmware_struct fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2158_ERROR;

    SiTRACE ("Si2158_LoadFirmware_16 starting...\n");
    SiTRACE ("Si2158_LoadFirmware_16 nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
		if (fw_table[line].firmware_len > 0)  /* don't download if length is 0 , e.g. dummy firmware */
		{
			/* send firmware_len bytes (up to 16) to Si2158 */
			if ((return_code = Si2158_L1_API_Patch(api, fw_table[line].firmware_len, fw_table[line].firmware_table)) != NO_Si2158_ERROR)
			{
			  SiTRACE("Si2158_LoadFirmware_16 error 0x%02x patching line %d: %s\n", return_code, line, Si2158_L1_API_ERROR_TEXT(return_code) );
			  if (line == 0) {
			  SiTRACE("The firmware is incompatible with the part!\n");
			  }
			  return ERROR_Si2158_LOADING_FIRMWARE;
			}
			// if (line==3) SiTraceConfiguration("traces suspend");
		}
    }
    // SiTraceConfiguration("traces resume");
    SiTRACE ("Si2158_LoadFirmware_16 complete...\n");
    return NO_Si2158_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si2158_Firmware_x_y_build_z.h file into Si2158
              Requires Si2158 to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si2158 Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si2158/I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_LoadFirmware        (L1_Si2158_Context *api, unsigned char fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si2158_ERROR;

    SiTRACE ("Si2158_LoadFirmware starting...\n");
    SiTRACE ("Si2158_LoadFirmware nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si2158_BYTES_PER_LINE fw bytes to Si2158 */
        if ((return_code = Si2158_L1_API_Patch(api, Si2158_BYTES_PER_LINE, fw_table + Si2158_BYTES_PER_LINE*line)) != NO_Si2158_ERROR)
        {
          SiTRACE("Si2158_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si2158_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si2158_LOADING_FIRMWARE;
        }
        // if (line==3) SiTraceConfiguration("traces suspend");
    }
    // SiTraceConfiguration("traces resume");
    SiTRACE ("Si2158_LoadFirmware complete...\n");
    return NO_Si2158_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158_StartFirmware
  DESCRIPTION: Start Si2158 firmware (put the Si2158 into run mode)
  Parameter:   Si2158 Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_StartFirmware       (L1_Si2158_Context *api)
{

    if (Si2158_L1_EXIT_BOOTLOADER(api, Si2158_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si2158_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si2158_ERROR)
    {
        return ERROR_Si2158_STARTING_FIRMWARE;
    }

    return NO_Si2158_ERROR;
}
/************************************************************************************************************************
  NAME: Si2158_Init
  DESCRIPTION:Reset and Initialize Si2158
  Parameter:  Si2158 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_Init                (L1_Si2158_Context *api)
{
    int return_code;
    SiTRACE("Si2158_Init starting...\n");

    if ((return_code = Si2158_PowerUpWithPatch(api)) != NO_Si2158_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si2158_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si2158_Configure(api);
    SiTRACE("Si2158_Init complete...\n");
    return NO_Si2158_ERROR;
}
/* _specific_code_insertion_start */
 /************************************************************************************************************************
  NAME: Si2158_UpdateChannelScanFrequency
  DESCRIPTION:  This routine allows the user to implement an update of the current channel scan operation with
                the current frequency being scanned.
  Parameter:    Current frequency of the scan routine
  Parameter:  channelsFound = 0 if channel not found at that frequency , channelsFound > 0  the number of channels
        currently found( including this frequency )
  Returns:      1 if scan abort requested, 0 if ok.
************************************************************************************************************************/
int Si2158_UpdateChannelScanFrequency(int freq,int channelsFound)
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
  NAME: Si2158_GetRF
  DESCRIPTIION: Retrieve Si2158 tune freq

  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns  :  frequency (Hz) as an int
************************************************************************************************************************/
int  Si2158_GetRF             (L1_Si2158_Context *api)
{
    Si2158_L1_TUNER_STATUS (api, Si2158_TUNER_STATUS_CMD_INTACK_OK);
        return api->rsp->tuner_status.freq;
}
 /************************************************************************************************************************
  NAME: Si2158_Tune
  DESCRIPTIION: Tune Si2158 in specified mode (ATV/DTV) at center frequency, wait for TUNINT and xTVINT with timeout

  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  Mode (ATV or DTV) use Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV or Si2158_TUNER_TUNE_FREQ_CMD_MODE_DTV constants
  Parameter:  frequency (Hz) as a unsigned long integer
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
 int  Si2158_Tune              (L1_Si2158_Context *api, unsigned char mode, unsigned long freq)
{
    int start_time  = 0;
    int return_code = 0;
    int timeout     = 36;

    start_time =MsOS_GetSystemTime();

    if (Si2158_L1_TUNER_TUNE_FREQ (api,
                                   mode,
                                   freq) != NO_Si2158_ERROR)
    {
        return ERROR_Si2158_SENDING_COMMAND;
    }

    /* wait for TUNINT, timeout is 36ms */
    while ( ((int)MsOS_GetSystemTime() - start_time) < timeout )
    {
        if ((return_code = Si2158_L1_CheckStatus(api)) != 0)
            return return_code;
        if (api->status->tunint)
            break;
    }
    if (!api->status->tunint) {
      SiTRACE("Timeout waiting for TUNINT\n");
      return ERROR_Si2158_TUNINT_TIMEOUT;
    }

    /* wait for xTVINT, timeout is 150ms for ATVINT and 10 ms for DTVINT */
    start_time = MsOS_GetSystemTime();
    timeout    = ((mode==Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? 150 : 10);
    while ( ((int)MsOS_GetSystemTime() - start_time) < timeout )
    {
        if ((return_code = Si2158_L1_CheckStatus(api)) != 0)
            return return_code;
        if (mode==Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV)
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

    if (mode==Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV)
    {
      if (api->status->atvint)
      {
        SiTRACE("ATV Tune Successful\n");
               return NO_Si2158_ERROR;
            }
      else
        SiTRACE("Timeout waiting for ATVINT\n");
    }
    else
    {
        if (api->status->dtvint)
        {
          SiTRACE("DTV Tune Successful\n");
          return NO_Si2158_ERROR;
        }
        else
          SiTRACE("Timeout waiting for DTVINT\n");
    }

    return ERROR_Si2158_xTVINT_TIMEOUT;
}
 /************************************************************************************************************************
  NAME: Si2158_ATVTune
  DESCRIPTION:Update ATV_VIDEO_MODE and tune ATV mode at center frequency
  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  transport,  e.g. use constant Si2158_ATV_VIDEO_MODE_PROP_TRANS_TERRESTRIAL for terrestrial
  Parameter:  color , e.g. use constant Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Parameter:  invert_signal, 0= normal, 1= inverted
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2158_ATVTune           (L1_Si2158_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color, unsigned char invert_spectrum)
{
    /* update ATV_VIDEO_MODE property */
    api->prop->atv_video_mode.video_sys = video_sys;
    api->prop->atv_video_mode.color = color;
    api->prop->atv_video_mode.invert_spectrum=invert_spectrum;
    if (Si2158_L1_SetProperty2(api, Si2158_ATV_VIDEO_MODE_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

    if( Si2158_ATV_Channel_Spur_Shifting(api, freq, video_sys, color)!= NO_Si2158_ERROR)
    {
        return ERROR_Si2158_SENDING_COMMAND;
    }

    return Si2158_Tune (api, Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq);
}
 /************************************************************************************************************************
  NAME: Si2158_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si2158_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si2158_DTVTune           (L1_Si2158_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum)
{
    int return_code;
    return_code = NO_Si2158_ERROR;

    /* update DTV_MODE_PROP property */
    api->prop->dtv_mode.bw = bw;
    api->prop->dtv_mode.invert_spectrum = invert_spectrum;
    api->prop->dtv_mode.modulation = modulation;
    if (Si2158_L1_SetProperty2(api, Si2158_DTV_MODE_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

   /* Make sure the sample freq is auto for all DTV tunes */
    api->prop->debug_sample_freq.fs_mhz = 0;
    /* update DEBUG_SAMPLE_FREQ property */
   if (Si2158_L1_SetProperty2(api, Si2158_DEBUG_SAMPLE_FREQ_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

    return_code = Si2158_Tune (api, Si2158_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si2158_XoutOn
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_XoutOn             (L1_Si2158_Context *api)
{
    int return_code;
    SiTRACE("Si2158_XoutOn:  Turning Xout ON\n");

     if ((return_code = Si2158_L1_CONFIG_CLOCKS(api,
                                              Si2158_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL,
                                              Si2158_CONFIG_CLOCKS_CMD_EN_XOUT_EN_XOUT)) != NO_Si2158_ERROR)
    return return_code;

    return NO_Si2158_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158_XoutOff
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_XoutOff            (L1_Si2158_Context *api)
{
    int return_code;
    SiTRACE("Si2158_XoutOff:  Turning Xout OFF\n");
    if ((return_code = Si2158_L1_CONFIG_CLOCKS(api,
                                              Si2158_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              Si2158_CONFIG_CLOCKS_CMD_CLOCK_MODE_XTAL,
                                              Si2158_CONFIG_CLOCKS_CMD_EN_XOUT_DIS_XOUT)) != NO_Si2158_ERROR)

    return return_code;

    return NO_Si2158_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158_Standby
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_Standby         (L1_Si2158_Context *api)
{
    int return_code;
    SiTRACE("Si2158_CLOCK_OFF: Turning clock OFF\n");

    if ((return_code = Si2158_L1_STANDBY(api, Si2158_STANDBY_CMD_TYPE_LNA_ON)) != NO_Si2158_ERROR)
    return return_code;

    return NO_Si2158_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158_Powerdown
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_Powerdown         (L1_Si2158_Context *api)
{
    int return_code;
    SiTRACE("Si2158_CLOCK_OFF: Turning clock OFF\n");

    if ((return_code = Si2158_L1_POWER_DOWN(api)) != NO_Si2158_ERROR)
    return return_code;

    return NO_Si2158_ERROR;
}

  /************************************************************************************************************************
  NAME: Si2158_Powerdown
  Parameter:  Pointer to Si2158 Context (I2C address)
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_Powerdown_HW (L1_Si2158_Context *api)
{
    int return_code;
    SiTRACE("Si2158_HW_Powerdown_HW: Turning clock OFF\n");
    if ((return_code = Si2158_L1_POWER_DOWN_HW (api,
                            Si2158_POWER_DOWN_HW_CMD_SUBCODE_CODE,
                            Si2158_POWER_DOWN_HW_CMD_PD_XO_OSC_XO_OSC_POWER_DOWN,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED1_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_EN_XOUT_DIS_XOUT,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED2_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_PD_LDO_LDO_POWER_DOWN,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED3_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED4_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED5_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED6_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED7_RESERVED,
                            Si2158_POWER_DOWN_HW_CMD_RESERVED8_RESERVED
                            )) != NO_Si2158_ERROR)
    {
        //printf ("11_Si2158_L1_POWER_DOWN_HW error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
       // return return_code;
    }
    if((return_code=Si2158_pollForResetState(api))!=NO_Si2158_ERROR)
    {
        printf ("22_Si2158_L1_POWER_DOWN_HW error 0x%02x: %s\n", return_code, Si2158_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }

    return NO_Si2158_ERROR;
}

/************************************************************************************************************************
  NAME: Si2158_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si2158_write_xTV_video_coeffs.h file into Si2158
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si2158 Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array (size in bytes / atv_vid_filt_struct)
  Returns:    Si2158/I2C transaction error code, NO_Si2178_ERROR if successful
************************************************************************************************************************/
int Si2158_LoadVideofilter     (L1_Si2158_Context *api, vid_filt_struct vidFiltTable[], int lines)
{
    int line;
     /* for each line in VIDFILT_TABLE (max 16 bytes)  */
    for (line = 0; line < lines ; line++)
    {
        /* send up to 16 byte I2C command to Si2178 */
        if (Si2158_L1_API_Patch(api, vidFiltTable[line].vid_filt_len, vidFiltTable[line].vid_filt_table) != NO_Si2158_ERROR)
        {
            return ERROR_Si2158_SENDING_COMMAND;
        }
    }
    return NO_Si2158_ERROR;
}
 /************************************************************************************************************************
  NAME: Si2158_ATV_Channel_Scan_M
  DESCRIPTION: Performs a channel scan for NTSC (System M) of the band
  Programming Guide Reference:    Flowchart A.11.0 and A11.1 (ATV Channel Scan flowchart for System M)

  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2158_ATV_Channel_Scan_M(L1_Si2158_Context *Si2158, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm)
{
    #define SCAN_INTERVAL     1000000
    #define CHANNEL_BANDWIDTH 6000000
    #define CHANNEL_NOT_FOUND       0

    unsigned long freq;
    int i;

    /*Clear the channel list size and channel array */
    Si2158->ChannelListSize=0;

    for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
    Si2158->ChannelList[i]=0;
    /* configure the VideoMode property to System M, NTSC*/
    Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M;    /* M ATV demodulation */
    Si2158->prop->atv_video_mode.color     = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_VIDEO_MODE_PROP) != NO_Si2158_ERROR)
    {
       return ERROR_Si2158_SENDING_COMMAND;
    }
    /* configure the RSQ / RSSI threshold properties */
    Si2158->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    Si2158->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

  /* setup IEN properties to enable TUNINT on TC  */
    Si2158->prop->tuner_ien.tcien     =  Si2158_TUNER_IEN_PROP_TCIEN_ENABLE;
    Si2158->prop->tuner_ien.rssilien  =  Si2158_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    Si2158->prop->tuner_ien.rssihien  =  Si2158_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2158_L1_SetProperty2(Si2158, Si2158_TUNER_IEN_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    Si2158->prop->atv_ien.chlien    =  Si2158_ATV_IEN_PROP_CHLIEN_ENABLE;
    Si2158->prop->atv_ien.pclien    =  Si2158_ATV_IEN_PROP_PCLIEN_DISABLE;
    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_IEN_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    Si2158->prop->atv_afc_range.range_khz    =  1500;
    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_AFC_RANGE_PROP) != NO_Si2158_ERROR)
    {
       return ERROR_Si2158_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {

    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2158_Tune (Si2158, Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {

            /* Get ATV status */
      if (Si2158_L1_ATV_STATUS (Si2158, Si2158_ATV_STATUS_CMD_INTACK_OK))
      {
        return ERROR_Si2158_SENDING_COMMAND;
      }


      /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2158->ChannelList[Si2158->ChannelListSize]= freq + (Si2158->rsp->atv_status.afc_freq * 1000);
      /* Update the callback to indicate the channel is found */
      /* if user requested abort then break from the loop */
      if (Si2158_UpdateChannelScanFrequency(freq + (Si2158->rsp->atv_status.afc_freq * 1000), Si2158->ChannelListSize+1))
        break;

            freq = Si2158->ChannelList[Si2158->ChannelListSize++] + CHANNEL_BANDWIDTH;
         }
         else  /* We didn't find a station at this frequency so increment and move on */
         {
        /* if user requested abort then break from the loop */
      if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
        break;
      /*  channel not found! **/
             freq += SCAN_INTERVAL;
         }
    }


 return 0;
}
/************************************************************************************************************************
  NAME: Si2158_ATV_Channel_Scan_PAL
  DESCRIPTION: Performs a channel scan for PAL (Systems B/G, D/K, L/L', and I) of the band
  Programming Guide Reference:    Flowchart A.10.0 - A10.3 (ATV Channel Scan flowchart for PAL)

  NOTE: this function requires an external sound processor to determine the PAL standard.  The user is
  required to implement the functions: L0_InitSoundProcessor(); and L0_AcquireSoundStandard(..);

  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  starting Frequency Hz
  Parameter:  ending Frequency Hz
  Parameter:  min RSSI dBm
  Parameter:  max RSSI dBm
  Parameter:  min SNR 1/2 dB
  Parameter:  max SNR 1/2 dB
  Returns:    0 if successful, otherwise an error.
************************************************************************************************************************/
int Si2158_ATV_Channel_Scan_PAL(L1_Si2158_Context *Si2158, unsigned long rangeMinHz, unsigned long rangeMaxHz, int minRSSIdBm, int maxRSSIdBm)
{

  #define VHF_MAX 300000000
  #define SCAN_INTERVAL 1000000
  #define CHANNEL_NOT_FOUND 0
  char standard = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B;
  unsigned long freq;
  unsigned long channelIncrement;
  char posModulation;  /* flag for pos or neg modulation */
  int i;

  /*Clear the channel list size and channel array */
  Si2158->ChannelListSize=0;

  for (i=0; i< MAX_POSSIBLE_CHANNELS;i++)
  {
    Si2158->ChannelList[i]=0;
    Si2158->ChannelType[i][0]='\0';
  }
    /* configure the RSQ / RSSI threshold properties */
    Si2158->prop->atv_rsq_rssi_threshold.lo = minRSSIdBm;
    Si2158->prop->atv_rsq_rssi_threshold.hi = maxRSSIdBm;

    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_RSQ_RSSI_THRESHOLD_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }
  /* setup IEN properties to enable TUNINT on TC  */
    Si2158->prop->tuner_ien.tcien     =  Si2158_TUNER_IEN_PROP_TCIEN_ENABLE;
    Si2158->prop->tuner_ien.rssilien  =  Si2158_TUNER_IEN_PROP_RSSILIEN_DISABLE;
    Si2158->prop->tuner_ien.rssihien  =  Si2158_TUNER_IEN_PROP_RSSIHIEN_DISABLE;

    if (Si2158_L1_SetProperty2(Si2158, Si2158_TUNER_IEN_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

   /* setup IEN properties to enable ATVINT on CHL  */
    Si2158->prop->atv_ien.chlien    =  Si2158_ATV_IEN_PROP_CHLIEN_ENABLE;
    Si2158->prop->atv_ien.pclien    =  Si2158_ATV_IEN_PROP_PCLIEN_DISABLE;
    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_IEN_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }
   /* setup AFC acquistion range property to 1.5MHz for scanning */
    Si2158->prop->atv_afc_range.range_khz    =  1500;
    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_AFC_RANGE_PROP) != NO_Si2158_ERROR)
    {
       return ERROR_Si2158_SENDING_COMMAND;
    }
   /* Start Scanning */
    for (freq=rangeMinHz; freq < rangeMaxHz; )
    {
    /* before calling tune provide a callback stub that the user can update the frequency */
    /* if user requested abort then break from the loop */
    if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;
    /* set the modulation flag to 0 (neg) */
    posModulation=0;
    /* Negative Modulation configure the VideoMode property to System DK, PAL*/
    Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK;    /* M ATV demodulation */
    Si2158->prop->atv_video_mode.color     = Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC;    /* PAL_NTSC color system */
    if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_VIDEO_MODE_PROP) != NO_Si2158_ERROR)
    {
       return ERROR_Si2158_SENDING_COMMAND;
    }

    /* Call the Tune command to tune the frequency */
    /* if successful (a station was found) then the return value will be 0. */
    if (!Si2158_Tune (Si2158, Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
    {
      posModulation = 0;
    }
    else  /* We didn't find a station so try positive modulation */
     {
      /* Pos Modulation configure the VideoMode property to System DK, PAL*/
      Si2158->prop->atv_video_mode.video_sys = Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L;    /* L ATV demodulation */
      Si2158->prop->atv_video_mode.color     = Si2158_ATV_VIDEO_MODE_PROP_COLOR_SECAM;    /* SECAM color system */
      if (Si2158_L1_SetProperty2(Si2158, Si2158_ATV_VIDEO_MODE_PROP) != NO_Si2158_ERROR)
      {
         return ERROR_Si2158_SENDING_COMMAND;
      }
      /* Call the Tune command to tune the frequency */
      /* if successful (a station was found) then the return value will be 0. */
      if (!Si2158_Tune (Si2158, Si2158_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq))
      {
        posModulation=1;
      }
      else
      {
            /* if user requested abort then break from the loop */
          if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

        /* we didn't find any channels goto flowchart section B */
        freq += SCAN_INTERVAL;
        continue;
      }
    }
    /* Initialize the sound processor.   This may or may not be required for your application */
/*    L1_InitSoundProcessor();*/
    /* Run the sound processor and return the standard(s) */
    #define SOUND_PROCESSOR_TIMEOUT 10
/*    L1_AcquireSoundStandard(SOUND_PROCESSOR_TIMEOUT , &standard);*/
    if ((standard == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_B) || (standard == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH))
      {
      /* check for positive modulation */
      if (posModulation)
    {
          /* if user requested abort then break from the loop */
          if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
            break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
      else
      {
        if (freq < VHF_MAX)
    {
          Si2158->ChannelType[Si2158->ChannelListSize][0]='B';
          Si2158->ChannelType[Si2158->ChannelListSize][1]='\0';
    }
    else
    {
          Si2158->ChannelType[Si2158->ChannelListSize][0]='G';
          Si2158->ChannelType[Si2158->ChannelListSize][1]='H';
          Si2158->ChannelType[Si2158->ChannelListSize][2]='\0';
    }
    }
    }
    else if (standard == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I)
    {
        if (posModulation)
    {
                /* if user requested abort then break from the loop */
              if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
                break;

          /* goto flowchart section B */
          freq += SCAN_INTERVAL;
          continue;
    }
        else
    {
          Si2158->ChannelType[Si2158->ChannelListSize][0]='I';
          Si2158->ChannelType[Si2158->ChannelListSize][1]='\0';
    }
    }
    else if ((standard == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_L) || (standard == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK))
    {
        if (posModulation)
    {
          Si2158->ChannelType[Si2158->ChannelListSize][0]='L';
          Si2158->ChannelType[Si2158->ChannelListSize][1]='\0';
    }
        else
    {
          Si2158->ChannelType[Si2158->ChannelListSize][0]='D';
          Si2158->ChannelType[Si2158->ChannelListSize][1]='K';
          Si2158->ChannelType[Si2158->ChannelListSize][2]='\0';
    }
    }
    else
    {
      /* standard not found */
    /* if user requested abort then break from the loop */
    if (Si2158_UpdateChannelScanFrequency(freq, CHANNEL_NOT_FOUND))
      break;

      /* goto flowchart section B */
      freq += SCAN_INTERVAL;
      continue;
    }
    /* if we got here, then we have a valid channel with a channelType */
            /* Get ATV status */
    if (Si2158_L1_ATV_STATUS (Si2158, Si2158_ATV_STATUS_CMD_INTACK_OK))
            {
               return ERROR_Si2158_SENDING_COMMAND;
            }
    if (Si2158->ChannelType[Si2158->ChannelListSize][0]=='B')
              {
            /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2158->ChannelList[Si2158->ChannelListSize]= freq + (Si2158->rsp->atv_status.afc_freq * 1000)-500000;
                  channelIncrement = 7000000;
              }
              else
              {
                /* Add the afc_freq (khz) to the center frequency and add to the channel list */
      Si2158->ChannelList[Si2158->ChannelListSize]= freq + (Si2158->rsp->atv_status.afc_freq * 1000);
                channelIncrement = 8000000;
              }
           /* Update the callback to indicate the channel is found */
            /* if user requested abort then break from the loop */
    if (Si2158_UpdateChannelScanFrequency(Si2158->ChannelList[Si2158->ChannelListSize], Si2158->ChannelListSize+1))
              break;
            /* go to the next frequency in the loop */
    freq = Si2158->ChannelList[Si2158->ChannelListSize++] + channelIncrement;
    }

 return 0;
}
/************************************************************************************************************************
  NAME: Si2158_AGC_Override
  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  Mode 0=Normal, 1= Max, 2=TOP
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si2158_AGC_Override    (L1_Si2158_Context *Si2158, unsigned char mode )
{
    int return_code;
    SiTRACE("Si2158_AGC_Override: mode = %d\n",mode);
    switch (mode)
    {
        case  Si2158_FORCE_NORMAL_AGC:
            if ((return_code = Si2158_L1_AGC_OVERRIDE (Si2158, Si2158_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2158_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2158_ERROR)
                return return_code;
            break;
        case  Si2158_FORCE_MAX_AGC:
            if ((return_code = Si2158_L1_AGC_OVERRIDE (Si2158, Si2158_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE,Si2158_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si2158_ERROR)
                return return_code;
            break;
        case  Si2158_FORCE_TOP_AGC:
            if ((return_code = Si2158_L1_AGC_OVERRIDE (Si2158, Si2158_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si2158_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE)) != NO_Si2158_ERROR)
                return return_code;
            break;

        default:
            return ERROR_Si2158_PARAMETER_OUT_OF_RANGE;

    }

    return NO_Si2158_ERROR;
}

/* _specific_code_insertion_point */
/************************************************************************************************************************
  NAME: Si2158_ATV_Channel_Spur_Shifting
  DESCRIPTION: Shift spur out of ATV channel if needed
  Parameter:  Pointer to Si2158 Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  color , e.g. use constant Si2158_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Returns:    I2C transaction error code, NO_Si2158_ERROR if successful
************************************************************************************************************************/
int Si2158_ATV_Channel_Spur_Shifting(L1_Si2158_Context *api, unsigned long freq, unsigned char video_sys, unsigned char color)
{
    unsigned char i;
    unsigned char maxSpurChannelNTSC = 4;
    unsigned char maxSpurChannelPAL = 1;

    color=color;
    spurshiftingtable_struct Si2158_SST_NTSC[]=
    {
        {753000000, 198},
        {789000000, 206},
        {797000000, 191},
        {803000000, 191},
    };
    spurshiftingtable_struct Si2158_SST_PAL[]=
    {
        {794000000, 191},
    };

    api->prop->debug_sample_freq.fs_mhz = 0;

    if (video_sys == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M || video_sys == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_N)
    {
        for (i=0; i< maxSpurChannelNTSC;i++)
        {
            if (freq == Si2158_SST_NTSC[i].ChannelFreq)
            {
                api->prop->debug_sample_freq.fs_mhz = Si2158_SST_NTSC[i].DebugSampleFreq;
                break;
            }
        }

    }
    else if (video_sys == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_DK || video_sys == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_I || video_sys == Si2158_ATV_VIDEO_MODE_PROP_VIDEO_SYS_GH)
    {
        for (i=0; i< maxSpurChannelPAL;i++)
        {
            if (freq == Si2158_SST_PAL[i].ChannelFreq)
            {
                api->prop->debug_sample_freq.fs_mhz = Si2158_SST_PAL[i].DebugSampleFreq;
                break;
            }
        }
    }
    else
    {
        api->prop->debug_sample_freq.fs_mhz = 0;
    }

    SiTRACE("Frequency:%dHz, Debug_Sample_freq:%dMHz\n",freq,api->prop->debug_sample_freq.fs_mhz);
    /* update DEBUG_SAMPLE_FREQ property */
   if (Si2158_L1_SetProperty2(api, Si2158_DEBUG_SAMPLE_FREQ_PROP) != NO_Si2158_ERROR)
    {
      return ERROR_Si2158_SENDING_COMMAND;
    }

    return NO_Si2158_ERROR;
}




