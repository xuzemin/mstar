/***************************************************************************************
                  Silicon Laboratories Broadcast Si2158  API
   FILE: Si2158_firmware_2_0_build_x.h
   Supported IC : Si2158
   Date: July 26 2012
   (C) Copyright 2012, Silicon Laboratories, Inc. All rights reserved.

   This is a dummy firmware patch for Si2158-A20 devices.
   When a new patch becomes available,  replace this file and all calls to it with the new patch.
   This patch is formatted in the new 16 byte download format.  The future patches will match this structure.
****************************************************************************************/
#ifndef _Si2158_FIRMWARE_2_0_BUILD_X_H_
#define _Si2158_FIRMWARE_2_0_BUILD_X_H_

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
	unsigned char firmware_len;
	unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

firmware_struct Si2158_FW_2_0bx[] = {
{ 0 , { 0x00} }
};

#define FIRMWARE_LINES_2_0bx (sizeof(Si2158_FW_2_0bx)/(sizeof(firmware_struct)))

#endif /* _Si2158_FIRMWARE_2_0_BUILD_X_H_ */
