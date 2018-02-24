#ifndef _SI2190B_FIRMWARE_3_0_BUILD_2_NVM_H_
#define _SI2190B_FIRMWARE_3_0_BUILD_2_NVM_H_

#define FIRMWARE_MAJOR        3
#define FIRMWARE_MINOR        0
#define BUILD_VERSION         2

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
	unsigned char firmware_len;
	unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

firmware_struct Si2190B_FW_3_0b2_NVM[] = {
{ 8 , { 0x05,0x11,0xF6,0x30,0x73,0x4F,0x64,0xA1 } } // Unpack the NVM into RAM
};

#define FIRMWARE_LINES_3_0b2_NVM (sizeof(Si2190B_FW_3_0b2_NVM)/(sizeof(firmware_struct)))
#define RAM_SIG_3_0b2 0xA1644F73
#define RAM_CRC_3_0b2 0x3131

#endif /* _SI2190B_FIRMWARE_3_0_BUILD_2_NVM_H_ */
