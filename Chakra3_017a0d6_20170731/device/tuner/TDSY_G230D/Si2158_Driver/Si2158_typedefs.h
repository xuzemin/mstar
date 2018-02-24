/*************************************************************************************
                  Silicon Laboratories Broadcast Si2158 Layer 1 API
   API types used by commands and properties
   FILE: Si2158_typedefs.h
   Supported IC : Si2158
   Compiled for ROM 33 firmware 2_0_build_4
   Revision: 0.1
   Date: July 30 2012
  (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.
**************************************************************************************/
#ifndef   Si2158_TYPEDEFS_H
#define   Si2158_TYPEDEFS_H

#if defined (__cplusplus)
extern "C" {
#endif

#define BUF_SIZE 1000
/* define the maximum possible channels (1002MHz - 43MHz) / 6MHz  (required for the channelscan array)*/
#define MAX_POSSIBLE_CHANNELS 160
#define MAX_LENGTH             80

typedef struct Si2158_L0_Context {
    unsigned char   address;
	int             indexSize;
} Si2158_L0_Context;

typedef struct L1_Si2158_Context {
  Si2158_L0_Context                 *i2c;
  Si2158_L0_Context                  i2cObj;
  Si2158_CmdObj              *cmd;
  Si2158_CmdObj               cmdObj;
  Si2158_CmdReplyObj         *rsp;
  Si2158_CmdReplyObj          rspObj;
  Si2158_PropObj             *prop;
  Si2158_PropObj              propObj;
  Si2158_COMMON_REPLY_struct *status;
  Si2158_COMMON_REPLY_struct  statusObj;
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
} L1_Si2158_Context;


/* struct to read video filter file with varying line lengths */
typedef struct  {
	char vid_filt_len;
	unsigned char vid_filt_table [16];
} vid_filt_struct_58;
typedef struct  {
	unsigned char firmware_len;
	unsigned char firmware_table[16];
} firmware_struct58;
#if defined (__cplusplus)
};
#endif

#endif /* Si2158_TYPEDEFS_H */





