#ifndef __MBX_REG_TBL__
#define __MBX_REG_TBL__

#define MBX_START_ADDR  (0x103300)

#define MBX_OFFSET_MM_START  (0x80)
#define MBX_OFFSET_MM_END  (0x9f)


#define MBX_SECR2_ADDR     (MBX_START_ADDR + 0x80)
#define MBX_SECRANGE_ADDR  (MBX_START_ADDR + 0x90)
	#define OFFSET_COMMAND_HEAD_0 (0x00)
	#define OFFSET_COMMAND_HEAD_1 (0x01)
	#define OFFSET_COMMAND_HEAD_2 (0x02)
	#define OFFSET_COMMAND_HEAD_3 (0x03)
	#define OFFSET_START_ADDR     (0x04)
	#define OFFSET_LENGTHE        (0x08)
	#define OFFSET_ACK_STATUS     (0x0C)
	     #define ACK_OK     (0xbabe)
		 #define ACK_DEAD   (0xdead)
	     #define ACK_FAIL   (0xffee)

//Secure R2 with ROM, 0xA0~0xDF
#define CHECK_Init_Supervisor     (MBX_START_ADDR + 0xA0)
#define CHECK_Init_Cache          (MBX_START_ADDR + 0xA2)
#define CHECK_Jump_Start          (MBX_START_ADDR + 0xA4)
#define CHECK_Mailbox_Head        (MBX_START_ADDR + 0xA6)
#define CHECK_DRAMOBF_DONE        (MBX_START_ADDR + 0xA8)
#define CHECK_RC_LOCK             (MBX_START_ADDR + 0xAA)
#define CHECK_DRAM_SIZE           (MBX_START_ADDR + 0xAC)
#define CHECK_SecureRange         (MBX_START_ADDR + 0xAE)
#define CHECK_Init_RSA            (MBX_START_ADDR + 0xB0)
#define CHECK_SHA_Calculate       (MBX_START_ADDR + 0xB2)
#define CHECK_RSA_Calculate       (MBX_START_ADDR + 0xB4)
#define CHECK_RSA_SHA_Result      (MBX_START_ADDR + 0xB6)
#define CHECK_Jump_DRAM           (MBX_START_ADDR + 0xB8)

#define SecureRange_Base_Addr_L   (MBX_START_ADDR + 0xC0)
#define SecureRange_Base_Addr_H   (MBX_START_ADDR + 0xC2)
#define SecureRange_Size_L        (MBX_START_ADDR + 0xC4)
#define SecureRange_Size_H        (MBX_START_ADDR + 0xC6)
#define SecureR2_DRAM_Base_Addr_L (MBX_START_ADDR + 0xC8)
#define SecureR2_DRAM_Base_Addr_H (MBX_START_ADDR + 0xCA)
#define SecureR2_DRAM_SIZE_DATA   (MBX_START_ADDR + 0xCC)

//Secure R2 with ROM, 0xE0~0xFF
#define CHECK_Rest_Entry_DRAM     (MBX_START_ADDR + 0xE0)
#define CHECK_Jump_Start_DRAM     (MBX_START_ADDR + 0xE2)
#define CHECK_Console_Init_DRAM   (MBX_START_ADDR + 0xE4)
#define CHECK_Cache_Init_DRAM     (MBX_START_ADDR + 0xE6)
#define CHECK_Interrupt_Init_DRAM (MBX_START_ADDR + 0xE8)

#define Porgram_Counter_SecureR2_RAM_L     (MBX_START_ADDR + 0xF0)
#define Porgram_Counter_SecureR2_RAM_H     (MBX_START_ADDR + 0xF2)


#define R_Check_Not_Ready (0x0000)  // the mbox value is inited to 0x0000 by default

#define R_Check_OK (0xBABE)
#define R_Check_Unknown_Err (0xFFFF)
#define R_Check_RSA_Busy (0x4E47)
#define R_Check_RSA_ERROR (0x3E22)
#define R_Check_SHA_ERROR (0x2E11)
#define R_Check_SHA_RSA_COMP_ERROR (0x1E00)
#define R_Check_SEC_STAR_ADDR_ERROR (0x3D22)
#define R_Check_SEC_END_ADDR_ERROR  (0x2D11)
#define R_Check_SEC_DRAMSIZE_LOCK_ERROR  (0x3C22)
#define R_Check_SEC_DRAMSIZE_COMP_ERROR   (0x2C11)
#define R_Check_SEC_RC_CLOCK_ENABLE_ERROR   (0x3B22)
#define R_Check_SEC_RC_LOCK_ERROR   (0x2B11)

#endif

