/*************************************************************************************
                  Silicon Laboratories Broadcast Si2190 Layer 1 API
   API types used by commands and properties
   FILE: Si2190_typedefs.h
   Supported IC : Si2190
   Compiled for ROM 40 firmware 0_A_build_10
   Revision: 0.1
   Date: August 13 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   Si2190_TYPEDEFS_H
#define   Si2190_TYPEDEFS_H

#define BUF_SIZE 1000
#define MAX_LENGTH             80
#define MAX_POSSIBLE_CHANNELS 160
typedef struct L1_Si2190_Context {
  L0_Context                 *i2c;
  L0_Context                  i2cObj;
  Si2190_CmdObj              *cmd;
  Si2190_CmdObj               cmdObj;
  Si2190_CmdReplyObj         *rsp;
  Si2190_CmdReplyObj          rspObj;
  Si2190_PropObj             *prop;
  Si2190_PropObj              propObj;
  Si2190_COMMON_REPLY_struct *status;
  Si2190_COMMON_REPLY_struct  statusObj;
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
} L1_Si2190_Context;

/* _additional_definitions_start */
#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
	unsigned char firmware_len;
	unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */



 #ifndef __VID_FILT_STRUCT__
#define __VID_FILT_STRUCT__
/* struct to read video filter file with varying line lengths */
typedef struct  {
  char vid_filt_len;
  unsigned char vid_filt_table [16];
} vid_filt_struct;
#endif /* __VID_FILT_STRUCT__ */
/* _additional_definitions_point */

#endif /* Si2190_TYPEDEFS_H */





