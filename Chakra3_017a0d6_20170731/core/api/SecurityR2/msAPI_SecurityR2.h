#ifndef _MSAPI_SECURITYR2_H_
#define _MSAPI_SECURITYR2_H_

#include "Board.h"

#if( ENABLE_SECURITY_R2 )

#include "MsTypes.h"
#include "datatype.h"
#include "drvXC_IOPort.h"


#ifdef _MSAPI_SECURITYR2_C_
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

//******************************************************************************

enum
{
    EN_SPU_RETAIL_MODE,
    EN_SPU_DEBUG_MODE
};

#define SECURITY_R2_DRAM_CODE_SIZE (80L*1024+4+256)

// patch area

#define HDCP22_PATCH_IN_MAYA        1
#define E_IRQ_HOST3_TO_HOST2_INT    E_INT_IRQ_0x00_START


#define DEF_HDCP2_EKPUBKM_SIZE              128

// compliance with U11 code base
//#define ENABLE_SECU_R2 1
#define ENABLE_HDCP22 1

#define EN_LC_INIT_MSG          (0x80)
#define EN_SKE_MSG              (0x81)

typedef enum
{
    EN_HDCP22_RECEIVE,
    EN_HDCP22_INT_A_B,
    EN_HDCP22_INT_B_A,
    EN_HDCP22_ACK
} EN_HDCP_LOG_DIR;

typedef struct
{
    EN_HDCP_LOG_DIR enHdcpLogDirection;
    U8 u8MsgID;
    U32 u32Time;

} ST_HDCP_LOG;

// Export functions for HK_APP(HDCP2.2)
// HDCP2.2
void msAPI_SecurityR2_Start(void);
void msAPI_SecurityR2_Handler(void);
void msAPI_HDCP22_log(EN_HDCP_LOG_DIR enHDCP22_TYPE,U8 u8MsgID);
void msAPI_HDCP22_log_reset(void);
void msAPI_HDCP22_log_print(void);
void msAPI_HDCP22_SendKeyToSecurityR2(void);
void msAPI_HDCP22_UseEfuseKey(void);
void msAPI_SecurityR2_MISCInit(void);

extern ST_HDCP_LOG ST_HDCP_LOG_ARRAY[];
INTERFACE U16 g_u16HdcpDedicatedTimeMs;
INTERFACE U8 u8PrintHdcp22DebugInfo;



#define ST_HDCP_LOG_MAX (1000)
//-------------------------------------------------------------------
// key information

#define HDCP22_AES_KEY_SIZE (16)
#define HDCP22_AES_KEY_DISCARD_ID_SIZE (4)
#define HDCP22_AES_READ_FROM_SPI_SIZE (HDCP22_AES_KEY_SIZE+HDCP22_AES_KEY_DISCARD_ID_SIZE)
#define HDCP22_KEY_SIZE (1044)                    // HDCP22_KEY_ENCRYPTED_SIZE

#define RESERVED_HDCP14_SIZE  (0x1000)
#define RESERVED_HDCP22_AES_SIZE  (0x100)
#define RESERVED_HDCP22_KEY_SIZE  (0x500)

#define HDCP22_AES_START RESERVED_HDCP14_SIZE

#define HDCP22_ENCRYPTED_BY_EX_AES_KEY_START (RESERVED_HDCP14_SIZE+RESERVED_HDCP22_AES_SIZE)
#define HDCP22_ENCRYPTED_BY_EFUSE_KEY_START (RESERVED_HDCP14_SIZE+RESERVED_HDCP22_AES_SIZE)

#define HDCP_AES_MAGIC_0 0x5a
#define HDCP_AES_MAGIC_1 0xa5
#define HDCP_AES_MAGIC_2 0x3c
#define HDCP_AES_MAGIC_3 0xc3


//-------------------------------------------------------------------------------------------
// HDCP SPI flash bank (64 KB) allocation
// 0x0000~0x0FFF, 4 KB reserve for HDCP1.4 (use 296 bytes in real)
// 0x1000~0x10FF, 256 B reserve for HDCP22 AES key (use 16 bytes in real)
// 0x1100~0x15FF, 1280 B reserve for HDCP22 encrytped key (use 1044 bytes in real)
// 0x1600~0x1AFF, 1280 B reserve for HDCP22 encrytped key (use 1044 bytes in real)
//-------------------------------------------------------------------------------------------

#define HDCP22_MBX_BASE_ADDR 0x1033C0

#define HDCP22_MBX_CONFIRM_ADR (HDCP22_MBX_BASE_ADDR+0x18)  // ocupied 4 bytes
#define HDCP22_MBX_CONFIRM_LEN (HDCP22_MBX_BASE_ADDR+0x1C)   // ocupied 4 bytes


extern  U8  _u8Hdcp22Key[];
extern  U8 _u8AesKey[];


#define HDCP22_ANSI_COLOR_OK  ANSI_COLOR_YELLOW
#define HDCP22_ANSI_COLOR_ERROR  ANSI_COLOR_RED
#define HDCP22_ANSI_COLOR_STAGE  ANSI_COLOR_GREEN


#define DEBUG_SECURIT_R2_BY_2ND_UART 0
#define DEBUG_SECURIT_R2_BY_1ST_UART_DEBUG_PORT 0
#define SKIP_HDCP22 0

#define HDCP22_CHECK_KEY_SIGN 1
#define DEBUG_HDCP22_KEY_IN_DDR 0
#define DEBUG_HDCP22_KEY_IN_DB 0
#define DEBUG_SECURITY_R2_STOP 0


//******************************************************************************

#undef INTERFACE

#endif // #if( ENABLE_SECURITY_R2 )
#endif // #if( _MSAPI_SECURITYR2_H_ )

//------------------------------------------------------------------
// TTS
// to be defined late


