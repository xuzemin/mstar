/*************************************************************************************
                  Silicon Laboratories Broadcast Si2151 Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API types used by commands and properties
   FILE: Si2151_typedefs.h
   Supported IC : Si2151
   Compiled for ROM 61 firmware 1_1_build_6
   Revision: 0.2
   Date: October 29 2014
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   Si2151_TYPEDEFS_H
#define   Si2151_TYPEDEFS_H

 #define BUF_SIZE 1000
/* define the maximum possible channels (1002MHz - 43MHz) / 6MHz  (required for the channelscan array)*/
#define MAX_POSSIBLE_CHANNELS 160
/* _additional_defines_point */
#define MAX_LENGTH         80

#define DOWNLOAD_ON_CHANGE 1
#define DOWNLOAD_ALWAYS    0

/* The following defines are to allow use of PowerUpWithPatch function with the powerUpUsingBroadcastI2C function. */
#define SKIP_NONE 0x00
#define SKIP_POWERUP 0x01
#define SKIP_LOADFIRMWARE 0x02
#define SKIP_STARTFIRMWARE 0x04
/* define the tuner broadcast address for common patch download. */
#define Si2151_BROADCAST_ADDRESS 0xc4

typedef struct L1_Si2151_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si2151_CmdObj              *cmd;
  Si2151_CmdObj               cmdObj;
  Si2151_CmdReplyObj         *rsp;
  Si2151_CmdReplyObj          rspObj;
  Si2151_PropObj             *prop;
  Si2151_PropObj              propObj;
  Si2151_PropObj             *propShadow;
  Si2151_PropObj              propShadowObj;
  Si2151_COMMON_REPLY_struct *status;
  Si2151_COMMON_REPLY_struct  statusObj;
  /* global variable for property settings mode
     Possible values:
         Si2151_DOWNLOAD_ON_CHANGE (recommended)
      or Si2151_DOWNLOAD_ALWAYS.                 */
  int propertyWriteMode;
  /* allows reuse of PowerUpWithPatch function by PowerUpUsingBroadcastI2C function */
  char load_control;
 /* Channel Scan Globals */
  /* Global array to store the list of found channels */
  unsigned long ChannelList[MAX_POSSIBLE_CHANNELS];
  /* ChannelScanPal needs to store the PAL type also so allocate 4 chars each for that */
  char ChannelType[MAX_POSSIBLE_CHANNELS][4];
  /* Number of found channels from a channel scan */
  int ChannelListSize;

  /* _additional_struct_members_point */
} L1_Si2151_Context;

/* _additional_definitions_start */
#ifndef __VID_FILT_STRUCT__
#define __VID_FILT_STRUCT__
/* struct to read video filter file with varying line lengths */
typedef struct  {
  char vid_filt_len;
  unsigned char vid_filt_table [16];
} vid_filt_struct;
#endif /* __VID_FILT_STRUCT__ */

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct  {
  unsigned char firmware_len;
  unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

/* _additional_definitions_point */

#endif /* Si2151_TYPEDEFS_H */







