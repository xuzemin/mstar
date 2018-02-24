/*************************************************************************************
                  Silicon Laboratories Broadcast Si21XXC Layer 1 API

   EVALUATION AND USE OF THIS SOFTWARE IS SUBJECT TO THE TERMS AND CONDITIONS OF
     THE SOFTWARE LICENSE AGREEMENT IN THE DOCUMENTATION FILE CORRESPONDING
     TO THIS SOURCE FILE.
   IF YOU DO NOT AGREE TO THE LIMITED LICENSE AND CONDITIONS OF SUCH AGREEMENT,
     PLEASE RETURN ALL SOURCE FILES TO SILICON LABORATORIES.

   API types used by commands and properties
   FILE: Si21XXC_typedefs.h
   Supported IC : Si2178B,Si2190B,Si2191B,Si2191C
   Compiled for ROM 71 firmware 3_0_build_1
   Revision: 0.1
   Tag:  Si2190B_30b1_Si2178B_42b7_Si2191C_30b1_Si2191B_42b7_V0.1
   Date: August 12 2015
  (C) Copyright 2014, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   Si21XXC_TYPEDEFS_H
#define   Si21XXC_TYPEDEFS_H

#define BUF_SIZE 1000
#define MAX_LENGTH             80
#define MAX_POSSIBLE_CHANNELS 160

#define DOWNLOAD_ON_CHANGE 1
#define DOWNLOAD_ALWAYS    0

/* The following defines are to allow use of PowerUpWithPatch function with the powerUpUsingBroadcastI2C function. */
#define SKIP_NONE 0x00
#define SKIP_POWERUP 0x01
#define SKIP_LOADFIRMWARE 0x02
#define SKIP_STARTFIRMWARE 0x04
/* define the tuner broadcast address for common patch download. */
#define Si21XXC_BROADCAST_ADDRESS 0xc4
typedef struct L1_Si21XXC_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si21XXC_CmdObj              *cmd;
  Si21XXC_CmdObj               cmdObj;
  Si21XXC_CmdReplyObj         *rsp;
  Si21XXC_CmdReplyObj          rspObj;
  Si21XXC_PropObj             *prop;
  Si21XXC_PropObj              propObj;
  Si21XXC_PropObj             *propShadow;
  Si21XXC_PropObj              propShadowObj;
  Si21XXC_COMMON_REPLY_struct *status;
  Si21XXC_COMMON_REPLY_struct  statusObj;
  /* global variable for property settings mode
     Possible values:
         Si2178B_DOWNLOAD_ON_CHANGE (recommended)
      or Si2178B_DOWNLOAD_ALWAYS.                 */
  int propertyWriteMode;
  /*chip rev constants for integrity checking */
  unsigned char chiprev;
  unsigned char part;
  /* Last 2 digits of part number */
  unsigned char partMajorVersion;
  unsigned char partMinorVersion;
  unsigned char partRomid;
 /* Channel Scan Globals */
  /* Global array to store the list of found channels */
  unsigned long ChannelList[MAX_POSSIBLE_CHANNELS];
  /* ChannelScanPal needs to store the PAL type also so allocate 4 chars each for that */
  char ChannelType[MAX_POSSIBLE_CHANNELS][4];
  /* Number of found channels from a channel scan */
  int ChannelListSize;
  char load_control;
  /* _additional_struct_members_point */
} L1_Si21XXC_Context;

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

#endif /* Si21XXC_TYPEDEFS_H */







