/***************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 2 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   L2 API for commands and properties
   FILE: Si21XXC_L2_API.c
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
****************************************************************************************/
#include <string.h>
/* Si21XXC API Defines */
/* define this to use the TUNINT interrupt only and bypass the ATVINT/DTVINT interrupt waits */
#undef SSVD_TUNE_PROCESS
/* define this if using the ATV video filter */
#undef USING_ATV_FILTER
/* define this if using the DTV video filter */
#undef USING_DLIF_FILTER
/************************************************************************************************************************/
/* Si21XXC API Specific Includes */
#include "Si21XXC_L2_API.h"               /* Include file for this code */
#include "Si2190B_firmware_2_1_build_15_full.h" /* firmware for Si2190-B20 */
#include "Si2190B_firmware_3_0_build_2_nvm.h"     /* firmware for Si2190-B30 */
#include "Si2190B_firmware_3_0_build_2.h"     /* firmware for Si2190-B30 */
#include "Si2178B_firmware_4_2_build_7.h"     /* firmware for Si2191-B40 */
#define Si21XXC_BYTES_PER_LINE 8
#ifdef USING_ATV_FILTER
#include "write_ATV_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
#ifdef USING_DLIF_FILTER
#include "write_DLIF_video_coeffs.h"   /* .h file from custom Video filter Tool output */
#endif
/***********************************************************************************************************************
  publishFirmwarePointer function
  Use:        provides a pointer to the required firmware
  Parameter: *api     the Si21XXC context
uses the structure defined in Si21XXC_typedefs.h
  typedef struct  {
    firmware_struct *fw;
    int firmware_size;
} fw_pointer_struct;

fw_pointer_struct ssvd_firmware;

  Returns:    0
 ***********************************************************************************************************************/
void  publishFirmwarePointer(L1_Si21XXC_Context *api,unsigned long *fw_addr,unsigned long *fw_size)
{
    switch (api->rsp->part_info.romid)
    {
        case 0x51: *fw_addr=(unsigned long)Si2178B_FW_4_2b7;
            *fw_size=sizeof(Si2178B_FW_4_2b7);
		break;
        case 0x70:
                *fw_addr=(unsigned long)Si2190B_FW_2_1b15_FULL;
                *fw_size=sizeof(Si2190B_FW_2_1b15_FULL);
		break;

        case 0x71:
            if ((api->rsp->part_info.pmajor=='0') && (api->rsp->part_info.pminor =='A'))  // Si2190-B2A
			{
                *fw_addr=(unsigned long)Si2190B_FW_3_0b2;
                *fw_size=sizeof(Si2190B_FW_3_0b2);
			}
			else if ((api->rsp->part_info.pmajor=='3') && (api->rsp->part_info.pminor =='0'))  // Si2190-B30
			{
                *fw_addr=(unsigned long)Si2190B_FW_3_0b2_NVM;
                *fw_size=sizeof(Si2190B_FW_3_0b2_NVM);
			}
			else{}


		break;

        default:
		break;
    }
}


/************************************************************************************************************************
  NAME: Si21XXC_Configure
  DESCRIPTION: Setup Si21XXC video filters, GPIOs/clocks, Common Properties startup, etc.
  Parameter:  Pointer to Si21XXC Context
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_Configure           (L1_Si21XXC_Context *api)
{
    int return_code;
    return_code = NO_Si21XXC_ERROR;

/* _specific_configure_insertion_start */
 #ifdef USING_ATV_FILTER
    if ((return_code = Si21XXC_LoadVideofilter(api,ATV_VIDFILT_TABLE,ATV_VIDFILT_LINES)) != NO_Si21XXC_ERROR)
       return return_code;
  #endif
     /* load DTV video filter file */
  #ifdef USING_DLIF_FILTER
     if ((return_code = Si21XXC_LoadVideofilter(api,DLIF_VIDFILT_TABLE,DLIF_VIDFILT_LINES)) != NO_Si21XXC_ERROR)
       return return_code;
  #endif
    /* _specific_configure_insertion_point */

    /* Set All Properties startup configuration */
    /* Edit the Si2178B_storeUserProperties if you have any properties settings different from the standard defaults */
    Si21XXC_storeUserProperties     (api->prop);

    /* Download properties different from 'propShadow' if api->propertyWriteMode = Si2178B_DOWNLOAD_ON_CHANGE */
    /* Download properties in any case                 if api->propertyWriteMode = Si2178B_DOWNLOAD_ALWAYS    */
    Si21XXC_downloadAllProperties(api);

    return return_code;
}
/************************************************************************************************************************
  NAME: Si21XXC_PowerUpOnly
  DESCRIPTION: Send Si21XXC API PowerUp Command with PowerUp to bootloader
  Parameter:  pointer to Si21XXC Context
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_PowerUpOnly         (L1_Si21XXC_Context *api)//20130628,csm,13'
{
	int return_code;
    return_code = NO_Si21XXC_ERROR;

    /* always wait for CTS prior to POWER_UP command */
        if ((return_code = Si21XXC_pollForCTS  (api)) != NO_Si21XXC_ERROR) {
            SiTRACE ("Si21XXC_pollForCTS error 0x%02x\n", return_code);
            return return_code;
        }


        if ((return_code = Si21XXC_L1_POWER_UP (api,
                                Si21XXC_POWER_UP_CMD_SUBCODE_CODE,
                                api->cmd->power_up.clock_mode,
                                api->cmd->power_up.en_xout,
                                Si21XXC_POWER_UP_CMD_PD_LDO_LDO_POWER_DOWN,
                                Si21XXC_POWER_UP_CMD_RESERVED2_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED3_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED4_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED5_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED6_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED7_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESET_RESET,
                                Si21XXC_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                                Si21XXC_POWER_UP_CMD_RESERVED8_RESERVED,
                                Si21XXC_POWER_UP_CMD_FUNC_BOOTLOADER,
                                Si21XXC_POWER_UP_CMD_CTSIEN_DISABLE,
                                Si21XXC_POWER_UP_CMD_WAKE_UP_WAKE_UP
                                )) != NO_Si21XXC_ERROR)
        {
            SiTRACE ("Si21XXC_L1_POWER_UP error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }

     /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
    if ((return_code = Si21XXC_L1_PART_INFO(api)) != NO_Si21XXC_ERROR) {
        SiTRACE ("Si21XXC_L1_PART_INFO error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    SiTRACE("chiprev %d\n",        api->rsp->part_info.chiprev);
    SiTRACE("part    Si21%d\n",    api->rsp->part_info.part   );
    SiTRACE("romid   %d\n",        api->rsp->part_info.romid  );
    SiTRACE("pmajor  %d\n",        api->rsp->part_info.pmajor );
    SiTRACE("pminor  %d\n",        api->rsp->part_info.pminor );
    SiTRACE("pbuild  %d\n",        api->rsp->part_info.pbuild );
    if ((api->rsp->part_info.pmajor >= 0x30) & (api->rsp->part_info.pminor >= 0x30)) {
    SiTRACE("pmajor  '%c'\n",    api->rsp->part_info.pmajor );
    SiTRACE("pminor  '%c'\n",    api->rsp->part_info.pminor );
    SiTRACE("Full Info       'Si21%02d-%c%c%c ROM%x NVM%c_%cb%d'\n\n\n", api->rsp->part_info.part, api->rsp->part_info.chiprev + 0x40, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.romid, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
    }
	return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si21XXC_PowerUpWithPatch
  DESCRIPTION: Send Si21XXC API PowerUp Command with PowerUp to bootloader,
  Check the Chip rev and part, and ROMID are compared to expected values.
  Load the Firmware Patch then Start the Firmware.
  Programming Guide Reference:    Flowchart A.2 (POWER_UP with patch flowchart)

  Parameter:  pointer to Si21XXC Context
  Returns:    Si21XXC/I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/

int Si21XXC_PowerUpWithPatch    (L1_Si21XXC_Context *api)
{
    int return_code;
    return_code = NO_Si21XXC_ERROR;

    if (!(api->load_control & SKIP_POWERUP))
    {
    /* always wait for CTS prior to POWER_UP command */
        if ((return_code = Si21XXC_pollForCTS  (api)) != NO_Si21XXC_ERROR) {
            SiTRACE ("Si21XXC_pollForCTS error 0x%02x\n", return_code);
            return return_code;
        }

         if ((return_code = Si21XXC_L1_POWER_UP (api,
                                Si21XXC_POWER_UP_CMD_SUBCODE_CODE,
                                api->cmd->power_up.clock_mode,
                                api->cmd->power_up.en_xout,
                                Si21XXC_POWER_UP_CMD_PD_LDO_LDO_POWER_DOWN,
                                Si21XXC_POWER_UP_CMD_RESERVED2_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED3_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED4_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED5_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED6_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESERVED7_RESERVED,
                                Si21XXC_POWER_UP_CMD_RESET_RESET,
                                Si21XXC_POWER_UP_CMD_CLOCK_FREQ_CLK_24MHZ,
                                Si21XXC_POWER_UP_CMD_RESERVED8_RESERVED,
                                Si21XXC_POWER_UP_CMD_FUNC_BOOTLOADER,
                                Si21XXC_POWER_UP_CMD_CTSIEN_DISABLE,
                                Si21XXC_POWER_UP_CMD_WAKE_UP_WAKE_UP
                                )) != NO_Si21XXC_ERROR)
        {
            SiTRACE ("Si21XXC_L1_POWER_UP error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }

        /* Get the Part Info from the chip.   This command is only valid in Bootloader mode */
        if ((return_code = Si21XXC_L1_PART_INFO(api)) != NO_Si21XXC_ERROR) {
            SiTRACE ("Si21XXC_L1_PART_INFO error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }
	//20121016,csm,SSVD REQUEST
	api->part             = api->rsp->part_info.part;
	api->chiprev          = api->rsp->part_info.chiprev;
	api->partMajorVersion = api->rsp->part_info.pmajor;
    api->partMinorVersion = api->rsp->part_info.pminor;
    api->partRomid        = api->rsp->part_info.romid;
	//end
        SiTRACE("chiprev %d\n",        api->rsp->part_info.chiprev);
        SiTRACE("part    Si21%d\n",    api->rsp->part_info.part   );
        SiTRACE("romid   %d\n",        api->rsp->part_info.romid  );
        SiTRACE("pmajor  %d\n",        api->rsp->part_info.pmajor );
        SiTRACE("pminor  %d\n",        api->rsp->part_info.pminor );
        SiTRACE("pbuild  %d\n",        api->rsp->part_info.pbuild );
        if ((api->rsp->part_info.pmajor >= 0x30) & (api->rsp->part_info.pminor >= 0x30)) {
        SiTRACE("pmajor  '%c'\n",    api->rsp->part_info.pmajor );
        SiTRACE("pminor  '%c'\n",    api->rsp->part_info.pminor );
        SiTRACE("Full Info       'Si21%02d-%c%c%c ROM%x NVM%c_%cb%d'\n\n\n", api->rsp->part_info.part, api->rsp->part_info.chiprev + 0x40, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.romid, api->rsp->part_info.pmajor, api->rsp->part_info.pminor, api->rsp->part_info.pbuild );
        }
    }
     if (!(api->load_control & SKIP_LOADFIRMWARE))
     {
        /* Check part info values and load the proper firmware */
          if (api->rsp->part_info.romid == 0x71)
          {
            if ((api->rsp->part_info.pmajor=='2') && (api->rsp->part_info.pminor =='A'))  // Si2190-B2A
			{
             if ((return_code = Si21XXC_LoadFirmware_16(api, Si2190B_FW_3_0b2, FIRMWARE_LINES_3_0b2)) != NO_Si21XXC_ERROR) {
               SiTRACE ("Si21XXC_LoadFirmware error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
               return return_code;
             }
			}
			else if ((api->rsp->part_info.pmajor=='3') && (api->rsp->part_info.pminor =='0'))  // Si2190-B30
			{
             if ((return_code = Si21XXC_LoadFirmware_16(api, Si2190B_FW_3_0b2_NVM, FIRMWARE_LINES_3_0b2_NVM)) != NO_Si21XXC_ERROR) {
               SiTRACE ("Si21XXC_LoadFirmware error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
               return return_code;
             }
			}
			else{}
          }		
          else if (api->rsp->part_info.romid == 0x70)
          {
             if ((return_code = Si21XXC_LoadFirmware_16(api, Si2190B_FW_2_1b15_FULL, FIRMWARE_LINES_2_1b15_FULL)) != NO_Si21XXC_ERROR) {
               SiTRACE ("Si21XXC_LoadFirmware error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
               return return_code;
             }
         }
         else if (api->rsp->part_info.romid == 0x51)
          {
             if ((return_code = Si21XXC_LoadFirmware_16(api, Si2178B_FW_4_2b7, FIRMWARE_LINES_4_2b7)) != NO_Si21XXC_ERROR) {
               SiTRACE ("Si21XXC_LoadFirmware error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
               return return_code;
             }
          }
          else
          {
              SiTRACE ("INCOMPATIBLE PART error ROMID 0x%02x\n", api->rsp->part_info.romid);
              return ERROR_Si21XXC_INCOMPATIBLE_PART;
          }
     }
     if (!(api->load_control & SKIP_STARTFIRMWARE))
     {
        /*Start the Firmware */
        if ((return_code = Si21XXC_StartFirmware(api)) != NO_Si21XXC_ERROR) { /* Start firmware */
            SiTRACE ("Si21XXC_StartFirmware error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
            return return_code;
        }

        Si21XXC_L1_GET_REV (api);
        SiTRACE("Si21%2d Part running 'FW_%c_%cb%d'\n", api->rsp->part_info.part, api->rsp->get_rev.cmpmajor, api->rsp->get_rev.cmpminor, api->rsp->get_rev.cmpbuild );
     }

    return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si21XXC_PowerUpUsingBroadcastI2C
  DESCRIPTION: This is similar to PowerUpWithPatch() for tuner_count tuners but it uses the I2C Broadcast
  command to allow the firmware download simultaneously to all tuners.

  Parameter:  tuners, a pointer to a table of L1 Si21XXC Contexts
  Parameter:  tuner_count, the number of tuners in the table
  Returns:    Si21XXC/I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_PowerUpUsingBroadcastI2C    (L1_Si21XXC_Context *tuners[], int tuner_count )
{

  int return_code;
  int t;
  #define Si21XXC_TUNER_BROADCAST_INDEX 0
  unsigned char logged_i2c_address;
  return_code = NO_Si21XXC_ERROR;

  /* for each tuner execute the powerup and part_info command but not the firmware download. */
  for (t = 0; t < tuner_count; t++)
  {
      tuners[t]->load_control = SKIP_LOADFIRMWARE | SKIP_STARTFIRMWARE;
      /* Si21XXC_PowerUpWithPatch will return right after Si21XXC_L1_PART_INFO, because SKIP_LOADFIRMWARE and SKIP_STARTFIRMWARE are set */
      if ( (return_code = Si21XXC_PowerUpWithPatch(tuners[t])) != NO_Si21XXC_ERROR) {
        SiTRACE ("Tuner %d Si21XXC_PowerUpWithPatch error 0x%02x\n", t,return_code);
        return return_code;
      }
       if ( (return_code = Si21XXC_L1_CONFIG_I2C(tuners[t], Si21XXC_CONFIG_I2C_CMD_SUBCODE_CODE, Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_ENABLED)) != NO_Si21XXC_ERROR )
       {
          SiTRACE("Tuner %d L1_CONFIG_I2C error 0x%02x\n", t, return_code);
          return return_code;
       }
   }

  /* At this stage, all tuners are connected/powered up and in 'broadcast i2c' mode */

  /* store the address of tuner0 to the broadcast address and restore the original address after we're done.  */
  logged_i2c_address = tuners[Si21XXC_TUNER_BROADCAST_INDEX]->i2c->address;
  tuners[Si21XXC_TUNER_BROADCAST_INDEX]->i2c->address = Si21XXC_BROADCAST_ADDRESS;
  /* set the load_control flag to SKIP_POWERUP so the firmware is downloaded and started on all tuners only */
  tuners[Si21XXC_TUNER_BROADCAST_INDEX]->load_control = SKIP_POWERUP;

  /* Si21XXC_PowerUpWithPatch will now broadcast the tuner fw and return
      when all is completed, because load_fw is now '1'                               */
  if ( (return_code = Si21XXC_PowerUpWithPatch(tuners[Si21XXC_TUNER_BROADCAST_INDEX])) != NO_Si21XXC_ERROR) {
    SiTRACE("Tuner %d Si21XXC_PowerUpWithPatch error 0x%02x\n", t,return_code);
    return return_code;
  }

  /* At this stage, all tuners have received the patch, and have been issued
     'Si21XXC_StartFirmware'                                                          */
     if ((return_code = Si21XXC_Configure    (tuners[Si21XXC_TUNER_BROADCAST_INDEX])) != NO_Si21XXC_ERROR)
     {
         return return_code;
     }

  /* Return the broadcast tuner address to its 'normal' value                         */
  tuners[Si21XXC_TUNER_BROADCAST_INDEX]->i2c->address = logged_i2c_address;

  for (t = 0; t < tuner_count; t++)
  {
    if ( (return_code = Si21XXC_L1_CONFIG_I2C(tuners[t], Si21XXC_CONFIG_I2C_CMD_SUBCODE_CODE, Si21XXC_CONFIG_I2C_CMD_I2C_BROADCAST_DISABLED)) != NO_Si21XXC_ERROR )
     {
      SiTRACE("Tuner %d L1_CONFIG_I2C error 0x%02x\n", t, return_code);
         return return_code;
     }
  }
  for (t = 0; t < tuner_count; t++)
  {
    /* Set Properties startup configuration         */
    Si21XXC_storePropertiesDefaults (tuners[t]->propShadow);
    /* Edit the Si21XXC_storeUserProperties if you have any properties settings different from the standard defaults */
    Si21XXC_storeUserProperties     (tuners[t]->prop);

   /* Reset the load_control flag to execute all phases of PowerUpWithPatch */
      tuners[t]->load_control =  SKIP_NONE;

 /* Check CTS for all tuners */
    if ( (return_code = Si21XXC_pollForCTS(tuners[t])) != NO_Si21XXC_ERROR ) {
      SiTRACE("Tuner %d pollForCTS error 0x%02x\n", t, return_code);
      return return_code;
    }

/* If this part is a Si2191C then we enable the Inter-Die Serial Link (ISL) here */
if ((tuners[t]->rsp->part_info.part == 91) && (tuners[t]->rsp->part_info.chiprev == Si21XXC_PART_INFO_RESPONSE_CHIPREV_C))
    {
        if ((return_code = Si2191C_SetupISL(tuners, t )) != NO_Si21XXC_ERROR)
        {
              SiTRACE("Error setting up ISL Link error 0x%02x\n", return_code);
              return return_code;
        }
    }

  }
  return NO_Si21XXC_ERROR;
}

/************************************************************************************************************************
  NAME: Si2191C_SetupISL
  DESCRIPTION: This function will setup the Inter-die serial link (ISL) between the tuners.
  This function assumes that the GPIO2 pins are connected and the AGC1 pins are connected.
  Parameter:  tuners, a pointer to a table of L1 Si2191C Contexts
  Parameter:  tuner_no,  call tuner[0] first and then tuner[1]

  Returns:    Si2191C/I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si2191C_SetupISL(L1_Si21XXC_Context *tuners[], int tuner_no )
{
    int return_code = NO_Si21XXC_ERROR;
    if (tuner_no==0)
    {
/* set tuner[0] to transmit on gpio2 */
        if ( (return_code = Si2190B_L1_CONFIG_PINS(tuners[0],Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_ISL_TX,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_AGC1_MODE_DISABLE,
                                                   Si2190B_CONFIG_PINS_CMD_AGC1_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_AGC2_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_AGC2_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_RESERVED3_RESERVED
                                                   )) != NO_Si21XXC_ERROR )
        {
          SiTRACE("Tuner %d CONFIG_PINS error 0x%02x\n", tuner_no, return_code);
          return return_code;
        }

    }
    else if (tuner_no==1)
    {
/* set tuner[1] to transmit on AGC1 and receive on gpio2 */
        if ( (return_code = Si2190B_L1_CONFIG_PINS(tuners[1],Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_ISL_RX,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_AGC1_MODE_ISL_TX,
                                                   Si2190B_CONFIG_PINS_CMD_AGC1_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_AGC2_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_AGC2_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_RESERVED3_RESERVED
                                                   )) != NO_Si21XXC_ERROR )
        {
          SiTRACE("Tuner %d CONFIG_PINS error 0x%02x\n", tuner_no, return_code);
          return return_code;
        }
/* set tuner[0] to receive on AGC1 */
        if ( (return_code = Si2190B_L1_CONFIG_PINS(tuners[0],Si2190B_CONFIG_PINS_CMD_GPIO1_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO1_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO2_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_GPIO2_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_AGC1_MODE_ISL_RX,
                                                   Si2190B_CONFIG_PINS_CMD_AGC1_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_AGC2_MODE_NO_CHANGE,
                                                   Si2190B_CONFIG_PINS_CMD_AGC2_READ_DO_NOT_READ,
                                                   Si2190B_CONFIG_PINS_CMD_RESERVED3_RESERVED
                                                   )) != NO_Si21XXC_ERROR )
        {
          SiTRACE("Tuner %d CONFIG_PINS error 0x%02x\n", tuner_no, return_code);
          return return_code;
        }
    }
    return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si2191C_TestISL
  DESCRIPTION:        This command checks to make sure the inter-die serial link (ISL) is working.
  Parameter:  Pointer to tuner1 Context
  Parameter:  Pointer to tuner2 Context
  Parameter:  Tuner1 Frequency (Hz)
  Parameter:  Tuner2 Frequency (Hz)
  Returns:    NO_Si21XXC_ERROR if ok,  ERROR_Si21XXC_ERR if error.
************************************************************************************************************************/
#if 0
int Si2191C_TestISL (L1_Si21XXC_Context *Tuner1,L1_Si21XXC_Context *Tuner2,unsigned long T1freq, unsigned long T2freq)
{
    int t1Count_rx1;
    int t1Count_tx1;
    int t1Count_rx2;
    int t1Count_tx2;
    int t2Count_rx1;
    int t2Count_tx1;
    int t2Count_rx2;
    int t2Count_tx2;
    int return_code = NO_Si21XXC_ERROR;

/* clear status counters on both tuners*/
   if (Si2191C_L1_ISL_STATUS(Tuner1,Si2191C_ISL_STATUS_CMD_CLEAR_CLEAR) != NO_Si21XXC_ERROR)
   {
        safe_printf("Error sending Si2191C_L1_ISL_STATUS\n");
        return ERROR_Si21XXC_SENDING_COMMAND;
   }

   if (Si2191C_L1_ISL_STATUS(Tuner2,Si2191C_ISL_STATUS_CMD_CLEAR_CLEAR) != NO_Si21XXC_ERROR)
   {
        safe_printf("Error sending Si2191C_L1_ISL_STATUS\n");
        return ERROR_Si21XXC_SENDING_COMMAND;
   }

/* tune the first tuner */
    return_code = Si21XXC_Tune (Tuner1, Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_DTV, T1freq, 1, 110);
    if ((return_code == ERROR_Si21XXC_xTVINT_TIMEOUT) || (return_code == NO_Si21XXC_ERROR))
    {
        safe_printf("Tuner1 tuned to %ld Hz\n",T1freq);
    }
    else
    {
        safe_printf("Error tuning Tuner1 code=%d\n",return_code);
        return return_code;
    }
    /* get the isl status counters for both tuners */
   if (Si2191C_L1_ISL_STATUS(Tuner1,Si2191C_ISL_STATUS_CMD_CLEAR_NO_CLEAR) != NO_Si21XXC_ERROR)
   {
        safe_printf("Error sending Si2191C_L1_ISL_STATUS\n");
        return ERROR_Si21XXC_SENDING_COMMAND;
   }
   if (Si2191C_L1_ISL_STATUS(Tuner2,Si2191C_ISL_STATUS_CMD_CLEAR_NO_CLEAR) != NO_Si21XXC_ERROR)
   {
        safe_printf("Error sending Si2191C_L1_ISL_STATUS\n");
        return ERROR_Si21XXC_SENDING_COMMAND;
   }
  t1Count_rx1 = Tuner1->rsp->isl_status.rx;
  t1Count_tx1 = Tuner1->rsp->isl_status.tx;
  t2Count_rx1 = Tuner2->rsp->isl_status.rx;
  t2Count_tx1 = Tuner2->rsp->isl_status.tx;
  safe_printf ("T1 rx = %d, T1 tx = %d, T2 rx =%d, T2 tx = %d\n",t1Count_rx1,t1Count_tx1,t2Count_rx1,t2Count_tx1) ;
  /* check for expected values */
  if ((t1Count_tx1 == t2Count_rx1) && (t1Count_tx1 > 0) && (t2Count_rx1 > 0) )
  {
      safe_printf("ISL link ok for Tuner1\n");
  }
  else
  {
      safe_printf("ISL link FAILED for Tuner1!!!!\n");
  }

  /* tune the second tuner */
    return_code = Si21XXC_Tune (Tuner2, Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_DTV, T2freq, 1, 110);
    if ((return_code == ERROR_Si21XXC_xTVINT_TIMEOUT) || (return_code == NO_Si21XXC_ERROR))
    {
        safe_printf("Tuner2 tuned to %ld Hz\n",T2freq);
    }
    else
    {
        safe_printf("Error tuning Tuner2 code=%d\n",return_code);
        return return_code;
    }
    /* get the isl status counters for both tuners */
   if (Si2191C_L1_ISL_STATUS(Tuner1,Si2191C_ISL_STATUS_CMD_CLEAR_NO_CLEAR) != NO_Si21XXC_ERROR)
   {
        safe_printf("Error sending Si2191C_L1_ISL_STATUS\n");
        return ERROR_Si21XXC_SENDING_COMMAND;
   }
   if (Si2191C_L1_ISL_STATUS(Tuner2,Si2191C_ISL_STATUS_CMD_CLEAR_NO_CLEAR) != NO_Si21XXC_ERROR)
   {
        safe_printf("Error sending Si2191C_L1_ISL_STATUS\n");
        return ERROR_Si21XXC_SENDING_COMMAND;
   }
  t1Count_rx2 = Tuner1->rsp->isl_status.rx;
  t1Count_tx2 = Tuner1->rsp->isl_status.tx;
  t2Count_rx2 = Tuner2->rsp->isl_status.rx;
  t2Count_tx2 = Tuner2->rsp->isl_status.tx;
  safe_printf ("T1 rx = %d, T1 tx = %d, T2 rx =%d, T2 tx = %d\n",t1Count_rx2,t1Count_tx2,t2Count_rx2,t2Count_tx2) ;
  /* check for expected values */
  if ((t2Count_tx2 == t1Count_rx2) && (t2Count_tx2 > 0) && (t1Count_rx2 > 0) )
  {
      safe_printf("ISL link ok for Tuner2\n");
  }
  else
  {
      safe_printf("ISL link FAILED for Tuner1!!!!\n");
  }
  /* final check */
  if ((t1Count_tx2 == t2Count_rx2) && (t2Count_tx2 == t1Count_rx2))
  {
       safe_printf("ISL link ok for both Tuners\n");
  }
  else
  {
       safe_printf("ISL link Failed\n");
       return ERROR_Si21XXC_ERR;
  }

return NO_Si21XXC_ERROR;
}
#endif

/************************************************************************************************************************
  NAME: Si21XXC_LoadFirmware_16
  DESCRIPTON: Load firmware from firmware_struct array in Si2178_Firmware_x_y_build_z.h file into Si21XXC
              Requires Si21XXC to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si21XXC Context
  Parameter:  pointer to firmware_struct array
  Parameter:  number of lines in firmware table array (size in bytes / firmware_struct)
  Returns:    Si21XXC/I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_LoadFirmware_16        (L1_Si21XXC_Context *api, firmware_struct fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si21XXC_ERROR;

    SiTRACE ("Si21XXC_LoadFirmware_16 starting...\n");
    SiTRACE ("Si21XXC_LoadFirmware_16 nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
		if (fw_table[line].firmware_len > 0)  /* don't download if length is 0 , e.g. dummy firmware */
		{
            /* send firmware_len bytes (up to 16) to Si21XXC */
            if ((return_code = Si21XXC_L1_API_Patch(api, fw_table[line].firmware_len, fw_table[line].firmware_table)) != NO_Si21XXC_ERROR)
            {
              SiTRACE("Si21XXC_LoadFirmware_16 error 0x%02x patching line %d: %s\n", return_code, line, Si21XXC_L1_API_ERROR_TEXT(return_code) );
              if (line == 0) {
              SiTRACE("The firmware is incompatible with the part!\n");
              }
              return ERROR_Si21XXC_LOADING_FIRMWARE;
            }
#ifdef SiTRACES
            if (line==3) SiTraceConfiguration("traces suspend");
#endif
		}
    }
    SiTraceConfiguration("traces resume");
    /* Storing Properties startup configuration in propShadow                              */
    /* !! Do NOT change the content of Si2151_storePropertiesDefaults                   !! */
    /* !! It should reflect the part internal property settings after firmware download !! */
    Si21XXC_storePropertiesDefaults (api->propShadow);
    SiTRACE ("Si21XXC_LoadFirmware_16 complete...\n");
    return NO_Si21XXC_ERROR;
}

/************************************************************************************************************************
  NAME: Si21XXC_LoadFirmware
  DESCRIPTON: Load firmware from FIRMWARE_TABLE array in Si21XXC_Firmware_x_y_build_z.h file into Si21XXC
              Requires Si21XXC to be in bootloader mode after PowerUp
  Programming Guide Reference:    Flowchart A.3 (Download FW PATCH flowchart)

  Parameter:  Si21XXC Context (I2C address)
  Parameter:  pointer to firmware table array
  Parameter:  number of lines in firmware table array (size in bytes / BYTES_PER_LINE)
  Returns:    Si21XXC/I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_LoadFirmware        (L1_Si21XXC_Context *api, unsigned char fw_table[], int nbLines)
{
    int return_code;
    int line;
    return_code = NO_Si21XXC_ERROR;

    SiTRACE ("Si21XXC_LoadFirmware starting...\n");
    SiTRACE ("Si21XXC_LoadFirmware nbLines %d\n", nbLines);

    /* for each line in fw_table */
    for (line = 0; line < nbLines; line++)
    {
        /* send Si21XXC_BYTES_PER_LINE fw bytes to Si21XXC */
        if ((return_code = Si21XXC_L1_API_Patch(api, Si21XXC_BYTES_PER_LINE, fw_table + Si21XXC_BYTES_PER_LINE*line)) != NO_Si21XXC_ERROR)
        {
          SiTRACE("Si21XXC_LoadFirmware error 0x%02x patching line %d: %s\n", return_code, line, Si21XXC_L1_API_ERROR_TEXT(return_code) );
          if (line == 0) {
          SiTRACE("The firmware is incompatible with the part!\n");
          }
          return ERROR_Si21XXC_LOADING_FIRMWARE;
        }
#ifdef SiTRACES
        if (line==3) SiTraceConfiguration("traces suspend");
#endif
    }
    SiTraceConfiguration("traces resume");
    SiTRACE ("Si21XXC_LoadFirmware complete...\n");
    return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si21XXC_StartFirmware
  DESCRIPTION: Start Si21XXC firmware (put the Si21XXC into run mode)
  Parameter:   Si21XXC Context (I2C address)
  Parameter (passed by Reference):   ExitBootloadeer Response Status byte : tunint, atvint, dtvint, err, cts
  Returns:     I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_StartFirmware       (L1_Si21XXC_Context *api)
{

    if (Si21XXC_L1_EXIT_BOOTLOADER(api, Si21XXC_EXIT_BOOTLOADER_CMD_FUNC_TUNER, Si21XXC_EXIT_BOOTLOADER_CMD_CTSIEN_OFF) != NO_Si21XXC_ERROR)
    {
        return ERROR_Si21XXC_STARTING_FIRMWARE;
    }

    return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si21XXC_Init
  DESCRIPTION:Reset and Initialize Si21XXC
  Parameter:  Si21XXC Context (I2C address)
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_Init                (L1_Si21XXC_Context *api)
{
    int return_code;
    SiTRACE("Si21XXC_Init starting...\n");

    if ((return_code = Si21XXC_PowerUpWithPatch(api)) != NO_Si21XXC_ERROR) {   /* PowerUp into bootloader */
        SiTRACE ("Si21XXC_PowerUpWithPatch error 0x%02x: %s\n", return_code, Si21XXC_L1_API_ERROR_TEXT(return_code) );
        return return_code;
    }
    /* At this point, FW is loaded and started.  */
    Si21XXC_Configure(api);
    SiTRACE("Si21XXC_Init complete...\n");
    return NO_Si21XXC_ERROR;
}
/* _specific_code_insertion_start */
 /************************************************************************************************************************
  NAME: Si21XXC_UpdateChannelScanFrequency
  DESCRIPTION:  This routine allows the user to implement an update of the current channel scan operation with
                the current frequency being scanned.
  Parameter:    Current frequency of the scan routine
  Parameter:  channelsFound = 0 if channel not found at that frequency , channelsFound > 0  the number of channels
        currently found( including this frequency )
  Returns:      1 if scan abort requested, 0 if ok.
************************************************************************************************************************/
#if 0
int Si21XXC_UpdateChannelScanFrequency(int freq,int channelsFound)
{
  //int abort_scan = 0;
  static int previousFrequency;
/*** Insert user code to display realtime updates of the frequency being scanned and channel status (number found ) **/
/* add check for user abort here */
  if (channelsFound)
  {
    /* Terminate the previous scan message */
    safe_printf("Found Frequency %d\n",freq);
  }
  else
  {
    if (freq==previousFrequency)
      safe_printf("Not Found\n");
    else
      safe_printf("Scanning Frequency %d, ",freq);
  }
  previousFrequency=freq;

  //if (abort_scan)//20131120,SSVD,prevent tool
  //  return 1;
  //else
    return 0;
  }
#endif

 /************************************************************************************************************************
  NAME: Si21XXC_GetRF
  DESCRIPTIION: Retrieve Si21XXC tune freq

  Parameter:  Pointer to Si21XXC Context (I2C address)
  Returns  :  frequency (Hz) as an int
************************************************************************************************************************/
int  Si21XXC_GetRF             (L1_Si21XXC_Context *api)
{
    Si21XXC_L1_TUNER_STATUS (api, Si21XXC_TUNER_STATUS_CMD_INTACK_OK);
        return api->rsp->tuner_status.freq;
}
 /************************************************************************************************************************
  NAME: Si21XXC_Tune
  DESCRIPTIION: Tune Si21XXC in specified mode (ATV/DTV) at center frequency, wait for TUNINT and xTVINT with timeout

  Parameter:  Pointer to Si21XXC Context (I2C address)
  Parameter:  Mode (ATV or DTV) use Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV or Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_DTV constants
  Parameter:  frequency (Hz) as a unsigned long integer
  Returns:    0 if channel found.  A nonzero value means either an error occurred or channel not locked.
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
 //int  Si21XXC_Tune              (L1_Si21XXC_Context *api, unsigned char mode, unsigned long freq)
 int  Si21XXC_Tune              (L1_Si21XXC_Context *api, unsigned char mode, unsigned long freq,unsigned char tunint_check,unsigned int AtvTimeout)
{
    int start_time  = 0;
    int return_code = 0;
    int timeout     = 36;

    if (Si21XXC_L1_TUNER_TUNE_FREQ (api,
                                   mode,
                                   freq) != NO_Si21XXC_ERROR)
    {
        return ERROR_Si21XXC_SENDING_COMMAND;
    }
    start_time = system_time();
	// Only wait for TUNINT, ATVINT and SDINT if tunint_check variable is set
	// tunint_check: 0(Analog Scan), 1(others)
	if(tunint_check == 1)
	{
    /* wait for TUNINT, timeout is 36 ms */
    while ( (system_time() - start_time) < timeout)
    {
        if ((return_code = Si21XXC_L1_CheckStatus(api)) != NO_Si21XXC_ERROR)
        {
            return return_code;
        }
        if (api->status->tunint)
            break;
    }
    if (!api->status->tunint)
    {
      SiTRACE("Timeout waiting for TUNINT \n");
        return ERROR_Si21XXC_TUNINT_TIMEOUT;
    }

#ifdef SSVD_TUNE_PROCESS
// if using the current SSVD tuning implementation (as in the Si2176), then bypass the ATVINT / DTVINT check and
// use the SSVD video processor for channel present decision making.
    return NO_Si21XXC_ERROR;
#else
    /* wait for xTVINT, timeout is 110ms for ATVINT and 10 ms for DTVINT */
    start_time = system_time();
    //timeout    = ((mode==Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? 110 : 10);
	//20130115, to improve 'Brazil no-signal locking': add 'AtvTimeout'
	timeout    = ((mode==Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV) ? AtvTimeout : 10);
    while ( (system_time() - start_time) < timeout )
    {
        if ((return_code = Si21XXC_L1_CheckStatus(api)) != NO_Si21XXC_ERROR)
            return return_code;
        if (mode==Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV)
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

    if (mode==Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV)
    {
      if (api->status->atvint)
      {
            SiTRACE("ATV Tune Successful\n");
            return_code = NO_Si21XXC_ERROR;
      }
      else
      {
        SiTRACE("Timeout waiting for ATVINT\n");
        return_code = ERROR_Si21XXC_xTVINT_TIMEOUT;
      }
    }
    else
    {
        if (api->status->dtvint)
        {
          SiTRACE("DTV Tune Successful\n");
          return_code = NO_Si21XXC_ERROR;
        }
        else
        {
          SiTRACE("Timeout waiting for DTVINT\n");
          return_code = ERROR_Si21XXC_xTVINT_TIMEOUT;
        }
    }

     /* Get TUNER status */
     if (Si21XXC_L1_TUNER_STATUS (api,Si21XXC_TUNER_STATUS_CMD_INTACK_CLEAR) != NO_Si21XXC_ERROR)
     {
       SiTRACE("Error sending Si21XXC_L1_TUNER_STATUS\n");
       return ERROR_Si21XXC_SENDING_COMMAND;
     }
#endif /* SSVD_TUNE_PROCESS */
	}//end of 'if(tunint_check == 1)'
	return NO_Si21XXC_ERROR;
}
 /************************************************************************************************************************
  NAME: Si21XXC_ATVTune
  DESCRIPTION:Update ATV_VIDEO_MODE and tune ATV mode at center frequency
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  Video system , e.g. use constant Si21XXC_ATV_VIDEO_MODE_PROP_VIDEO_SYS_M for system M
  Parameter:  color , e.g. use constant Si21XXC_ATV_VIDEO_MODE_PROP_COLOR_PAL_NTSC for PAL or NTSC
  Parameter:  invert_signal, 0= normal, 1= inverted
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si21XXC_ATVTune           (L1_Si21XXC_Context *api, unsigned long freq, unsigned char video_sys,unsigned char color, unsigned char invert_signal,unsigned char tunint_check,unsigned int AtvTimeout)
{
    /* update ATV_VIDEO_MODE property */
    api->prop->atv_video_mode.video_sys = video_sys;
    api->prop->atv_video_mode.color = color;
    api->prop->atv_video_mode.invert_signal=invert_signal;
    if (Si21XXC_L1_SetProperty2(api, Si21XXC_ATV_VIDEO_MODE_PROP) != NO_Si21XXC_ERROR)
    {
      return ERROR_Si21XXC_SENDING_COMMAND;
    }

    return Si21XXC_Tune (api, Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_ATV, freq, tunint_check, AtvTimeout);
}
 /************************************************************************************************************************
  NAME: Si21XXC_DTVTune
  DESCRIPTION: Update DTV_MODE and tune DTV mode at center frequency
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Parameter:  frequency (Hz)
  Parameter:  bandwidth , 6,7 or 8 MHz
  Parameter:  modulation,  e.g. use constant Si21XXC_DTV_MODE_PROP_MODULATION_DVBT for DVBT mode
  Parameter:  rsp - commandResp structure to returns tune status info.
  Returns:    I2C transaction error code, 0 if successful
  Programming Guide Reference:    Flowchart A.7 (Tune flowchart)
************************************************************************************************************************/
int  Si21XXC_DTVTune           (L1_Si21XXC_Context *api, unsigned long freq, unsigned char bw, unsigned char modulation, unsigned char invert_spectrum)
{
    int return_code;
    return_code = NO_Si21XXC_ERROR;

    /* update DTV_MODE_PROP property */
    api->prop->dtv_mode.bw = bw;
    api->prop->dtv_mode.invert_spectrum = invert_spectrum;
    api->prop->dtv_mode.modulation = modulation;
    if (Si21XXC_L1_SetProperty2(api, Si21XXC_DTV_MODE_PROP) != NO_Si21XXC_ERROR)
    {
      return ERROR_Si21XXC_SENDING_COMMAND;
    }
/*  The tuner_return_loss_optimize properties are only supported for the Si2190B / Si2191C parts*/
    if (api->rsp->part_info.romid == 0x70 || api->rsp->part_info.romid == 0x71)
    {
        /* Set the Tuner return loss optimize if in DTMB mode, otherwise reset it to default values */
        if (modulation==Si21XXC_DTV_MODE_PROP_MODULATION_DTMB)
        {
            api->prop->tuner_return_loss_optimize.config               =    91;
            api->prop->tuner_return_loss_optimize_2.thld               =    15; /* (default    31) */
            api->prop->tuner_return_loss_optimize_2.window             =     5; /* (default     0) */
            api->prop->tuner_return_loss_optimize_2.engagement_delay   =    3; /* (default    15) */
        }
        else
        {
            api->prop->tuner_return_loss_optimize.config               = Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP_CONFIG_DISABLE;
            api->prop->tuner_return_loss_optimize_2.thld               =    31; /* (default    31) */
            api->prop->tuner_return_loss_optimize_2.window             =     0; /* (default     0) */
            api->prop->tuner_return_loss_optimize_2.engagement_delay   =    15; /* (default    15) */
        }
        /* set the remaining optimize values to their defaults */
        api->prop->tuner_return_loss_optimize.thld                 =     0;
        api->prop->tuner_return_loss_optimize.engagement_delay     =     7;
        api->prop->tuner_return_loss_optimize.disengagement_delay  =    10;

        if (Si21XXC_L1_SetProperty2(api, Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_PROP) != NO_Si21XXC_ERROR)
        {
          return ERROR_Si21XXC_SENDING_COMMAND;
        }
        if (Si21XXC_L1_SetProperty2(api, Si2190B_TUNER_RETURN_LOSS_OPTIMIZE_2_PROP) != NO_Si21XXC_ERROR)
        {
          return ERROR_Si21XXC_SENDING_COMMAND;
        }
    }
    return_code = Si21XXC_Tune (api, Si21XXC_TUNER_TUNE_FREQ_CMD_MODE_DTV, freq, 1, 110);

    return return_code;
}

 /************************************************************************************************************************
  NAME: Si21XXC_XoutOn
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_XoutOn             (L1_Si21XXC_Context *api)
{
    int return_code=0;
    SiTRACE("Si21XXC_XoutOn:  Turning Xout ON\n");

    if ((return_code = Si21XXC_L1_CONFIG_CLOCKS(api,
                                              Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              api->cmd->config_clocks.clock_mode,
                                              Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_EN_XOUT)) != NO_Si21XXC_ERROR)
    return return_code;

    return NO_Si21XXC_ERROR;
}
 /************************************************************************************************************************
  NAME: Si21XXC_XoutOff
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_XoutOff            (L1_Si21XXC_Context *api)
{
    int return_code=0;
    SiTRACE("Si21XXC_XoutOff:  Turning Xout OFF\n");

    if ((return_code = Si21XXC_L1_CONFIG_CLOCKS(api,
                                              Si21XXC_CONFIG_CLOCKS_CMD_SUBCODE_CODE,
                                              api->cmd->config_clocks.clock_mode,
                                              Si21XXC_CONFIG_CLOCKS_CMD_EN_XOUT_DIS_XOUT)) != NO_Si21XXC_ERROR)
    return return_code;

    return NO_Si21XXC_ERROR;
}

//#if defined(MODEL_CN)//20140115,ssvd req
int Si21XXC_ReadPropertyArray            (L1_Si21XXC_Context *api)
{
    int return_code=0;
	int i = 0;
	unsigned short property = 0x0701;
	for(i =0; i<9; i++)
	{
  		Si21XXC_L1_GET_PROPERTY (api, 0, property);
 		property= property +1;
	}
   Si21XXC_L1_SET_PROPERTY      (api,   0, 0x0708, 121);
   Si21XXC_L1_SET_PROPERTY      (api,   0, 0x0507, 0x79);
    return return_code;
}
//#endif

 /************************************************************************************************************************
  NAME: Si21XXC_Standby
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_Standby         (L1_Si21XXC_Context *api)
{
    int return_code;
    SiTRACE("Si21XXC_Standby: Going to Standby.  The part will awake on the next command.\n");

    if ((return_code = Si21XXC_L1_STANDBY(api, Si21XXC_STANDBY_CMD_TYPE_LNA_ON)) != NO_Si21XXC_ERROR)
    return return_code;

    return NO_Si21XXC_ERROR;
}
 /************************************************************************************************************************
  NAME: Si21XXC_Powerdown
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Returns:    I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_Powerdown         (L1_Si21XXC_Context *api)
{
    int return_code;
    SiTRACE("Si21XXC_Powerdown: Powering down the part.  Select InitAndConfig to reload.\n");

    if ((return_code = Si21XXC_L1_POWER_DOWN_HW(api,Si21XXC_POWER_DOWN_HW_CMD_SUBCODE_CODE,
                                                Si21XXC_POWER_DOWN_HW_CMD_PD_XO_OSC_XO_OSC_POWER_DOWN,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED1_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_EN_XOUT_DIS_XOUT,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED2_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_PD_LDO_LDO_POWER_DOWN,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED3_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED4_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED5_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED6_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED7_RESERVED,
                                                Si21XXC_POWER_DOWN_HW_CMD_RESERVED8_RESERVED)) != NO_Si21XXC_ERROR)
    return return_code;

    return NO_Si21XXC_ERROR;
}
 /************************************************************************************************************************
  NAME: Si21XXC_LoadVideofilter
  DESCRIPTION:        Load video filters from vidfiltTable in Si21XXC_write_xTV_video_coeffs.h file into Si21XXC
  Programming Guide Reference:    Flowchart A.4 (Download Video Filters flowchart)

  Parameter:  Si21XXC Context (I2C address)
  Parameter:  pointer to video filter table array
  Parameter:  number of lines in video filter table array (size in bytes / Si21XXC_BYTES_PER_LINE)
  Returns:    Si21XXC/I2C transaction error code, NO_Si21XXC_ERROR if successful
************************************************************************************************************************/
int Si21XXC_LoadVideofilter     (L1_Si21XXC_Context *api,vid_filt_struct vidFiltTable[], int lines)
{
    int line;
     /* for each line in VIDFILT_TABLE (max 16 bytes)  */
    for (line = 0; line < lines ; line++)
    {
        /* send up to 16 byte I2C command to Si21XXC */
        if (Si21XXC_L1_API_Patch(api, vidFiltTable[line].vid_filt_len, vidFiltTable[line].vid_filt_table) != NO_Si21XXC_ERROR)
        {
            return ERROR_Si21XXC_SENDING_COMMAND;
        }
    }
    return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si21XXC_AGC_Override
  Parameter:  Pointer to Si21XXC Context (I2C address)
  Parameter:  Mode 0=Normal, 1= Max, 2=TOP
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int Si21XXC_AGC_Override    (L1_Si21XXC_Context *Si21XXC, unsigned char mode )
{
    int return_code;
    SiTRACE("Si21XXC_AGC_Override: mode = %d\n",mode);
    switch (mode)
    {
        case  Si21XXC_FORCE_NORMAL_AGC:
            if ((return_code = Si21XXC_L1_AGC_OVERRIDE (Si21XXC, Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si21XXC_ERROR)
                return return_code;
            break;
        case  Si21XXC_FORCE_MAX_AGC:
            if ((return_code = Si21XXC_L1_AGC_OVERRIDE (Si21XXC, Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_ENABLE,Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_DISABLE)) != NO_Si21XXC_ERROR)
                return return_code;
            break;
        case  Si21XXC_FORCE_TOP_AGC:
            if ((return_code = Si21XXC_L1_AGC_OVERRIDE (Si21XXC, Si21XXC_AGC_OVERRIDE_CMD_FORCE_MAX_GAIN_DISABLE,Si21XXC_AGC_OVERRIDE_CMD_FORCE_TOP_GAIN_ENABLE)) != NO_Si21XXC_ERROR)
                return return_code;
            break;

        default:
            return ERROR_Si21XXC_PARAMETER_OUT_OF_RANGE;

    }

    return NO_Si21XXC_ERROR;
}
/************************************************************************************************************************
  NAME: Si21XXC_Tuner_Block_VCO
  Parameter:  Pointer to Si21XXC Context (I2C address) of the OTHER tuner
  Parameter:  vco_code from TUNER_STATUS
  Returns:    I2C transaction error code, 0 if successful
************************************************************************************************************************/
int  Si21XXC_Tuner_Block_VCO      (L1_Si21XXC_Context *api, int vco_code)
{
        /* configure the TUNER_BLOCKED_VCO for the other tuner. */
    api->prop->tuner_blocked_vco.vco_code = vco_code;

    if (Si21XXC_L1_SetProperty2(api, Si21XXC_TUNER_BLOCKED_VCO_PROP) != NO_Si21XXC_ERROR)
    {
       return ERROR_Si21XXC_SENDING_COMMAND;
    }
    return NO_Si21XXC_ERROR;
}
