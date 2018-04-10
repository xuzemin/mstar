//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _MSTAR_DEBUG_H_
#define _MSTAR_DEBUG_H_

#include "Board.h"

#include "mw_debug.h"

#ifdef _MSTAR_DEBUG_C_
#define INTERFACE
#else
#define INTERFACE  extern
#endif


#define ENABLE_DEBUG_BOOT_TIME   0 //MP333

#if( ENABLE_DEBUG_BOOT_TIME )
    #define DEBUG_BOOT_TIME(x)  x
#else
    #define DEBUG_BOOT_TIME(x)
#endif

#if(!BLOADER)
    #define ENABLE_DEBUG_DELAY_TIME 1
#else
    #define ENABLE_DEBUG_DELAY_TIME 0
#endif

#define ENABLE_UART_MSG_COLOR   1

#define ENABLE_LOG_FILE_IN_MEM  0

//-----------------------------------------------------------------
void msDebugFuncTime_PrintPreStr(U8 u8Flag);

#if(ENABLE_LOG_FILE_IN_MEM)

#define LOG_MEM_GROUP_BOOT  0

#define DEBUG_FUNC_TIME_START()         U32 u32FuncTimeStart = MsOS_GetSystemTime(); \
    msDebugFuncTime_PrintPreStr(1);  \
    Debug_Log_MemPrintf(LOG_MEM_GROUP_BOOT, "%s() start at %u\n", __FUNCTION__, u32FuncTimeStart)

#define DEBUG_FUNC_TIME_END()           do{ \
    U32 u32DbgCurTime = MsOS_GetSystemTime();   \
    msDebugFuncTime_PrintPreStr(0);             \
    Debug_Log_MemPrintf(LOG_MEM_GROUP_BOOT,"%s() end at %u ", __FUNCTION__, u32DbgCurTime); \
    Debug_Log_MemPrintf(LOG_MEM_GROUP_BOOT,"use %u\n", u32DbgCurTime - u32FuncTimeStart); \
}while(0)

#else
#define DEBUG_FUNC_TIME_START()         U32 u32FuncTimeStart = MsOS_GetSystemTime(); \
    msDebugFuncTime_PrintPreStr(1);  \
    printf("%s() start at %u\n", __FUNCTION__, u32FuncTimeStart)

#define DEBUG_FUNC_TIME_END()           do{ \
    U32 u32DbgCurTime = MsOS_GetSystemTime();   \
    msDebugFuncTime_PrintPreStr(0);             \
    printf("%s() end at %u ", __FUNCTION__, u32DbgCurTime); \
    printf("use %s%u%s\n", ANSI_COLOR_GREEN, u32DbgCurTime - u32FuncTimeStart, ANSI_COLOR_RESET); \
}while(0)
#endif

//-----------------------------------------------------------------

INTERFACE U32   g_Debug_u32Time_ChangeChannel;

#define DEBUG_CHG_SRC_TIME  0
#if(DEBUG_CHG_SRC_TIME)
#define LOG_MEM_GROUP_CHG_SRC   0
INTERFACE BOOL g_Debug_bChangeSrc;
INTERFACE U32 g_Debug_u32Time_ChangeSrc;
void msDebug_PrintChgSrcTime(char* pStr);
#endif

INTERFACE U32 g_Debug_u32LastTunerFreq;

//-----------------------------------------------------------------------------
// Function
//-----------------------------------------------------------------------------
INTERFACE void MStarDebugInitial(void);
INTERFACE void MStarDebugShowVerString(U8 *string, U8 size);
INTERFACE BOOL MStarDebugSameVer(U8 *str1, U8 *str2, U8 size);

//==========================================================================

#if(ENABLE_LOG_FILE_IN_MEM)
void Debug_Log_Init(void);
void Debug_Log_Reset(U8 u8GroupIdx);
void Debug_Log_PutCharInMem(U8 u8GroupIdx, char ch, BOOLEAN bFlushMemory);
void Debug_Log_PrintAll(U8 u8GroupIdx);
int Debug_Log_MemPrintf(U8 u8GroupIdx, const char *fmt, ...);
#endif


#ifndef ENABLE_UART_MSG_TO_USB
#define ENABLE_UART_MSG_TO_USB  0
#endif

#if(ENABLE_UART_MSG_TO_USB)
void msDebug_UartToUSB_Init(void);
void msDebug_UartToUSB_Reset(void);
BOOL msDebug_UartToUSB_OpenFile(void);
void msDebug_UartToUSB_Task(void);
void msDebug_UartToUSB_FileWrite(char* pcBuffer, U32 u32Length);
void msDebug_UartToUSB_Set_Enable(BOOL bEnable);
BOOL msDebug_UartToUSB_Get_Enable(void);
#endif



#define ENABLE_LOG_TO_FILE    0
#if( ENABLE_LOG_TO_FILE )
typedef enum
{
    E_LOG_FILE_OK = 0,
    E_LOG_FILE_ERR_OPEN_USB_FAILED,
    E_LOG_FILE_ERR_GET_FILE_ENV_FAILED,
    E_LOG_FILE_ERR_CHANGE_DIR_FAILED,
    E_LOG_FILE_ERR_CREATE_NEW_FILE_FAILED,
    E_LOG_FILE_ERR_WRITE_FILE_FAILED,
} EnuLogFileErrCode;

EnuLogFileErrCode msDebug_LogFile_GenFileAndWriteInfo(void);

#endif

typedef enum
{
    E_FONT_ATTRIBUTE_NONE                       = 0,
    E_FONT_ATTRIBUTE_BOLD                       = 1,
    E_FONT_ATTRIBUTE_UNDERSCORE                 = 4,
} EnuFontAttributeType;

typedef enum
{
    E_FONT_COLOR_BLACK                          = 30,
    E_FONT_COLOR_RED                            = 31,
    E_FONT_COLOR_GREEN                          = 32,
    E_FONT_COLOR_YELLOW                         = 33,
    E_FONT_COLOR_BLUE                           = 34,
    E_FONT_COLOR_PURPLE                         = 35,
    E_FONT_COLOR_CYAN                           = 36,
    E_FONT_COLOR_WHITE                          = 37,
} EnuFontColorType;

typedef enum
{
    E_FONT_BACKGROUND_COLOR_BLACK               = 40,
    E_FONT_BACKGROUND_COLOR_RED                 = 41,
    E_FONT_BACKGROUND_COLOR_GREEN               = 42,
    E_FONT_BACKGROUND_COLOR_YELLOW              = 43,
    E_FONT_BACKGROUND_COLOR_BLUE                = 44,
    E_FONT_BACKGROUND_COLOR_PURPLE              = 45,
    E_FONT_BACKGROUND_COLOR_CYAN                = 46,
    E_FONT_BACKGROUND_COLOR_WHITE               = 47,
} EnuFontBackgroundColorType;

#if defined(__aeon__)
#define DUMP_R2_REG(i)  do{ \
    MDrv_WriteByte(0x100201, (i)); \
    printf("%u R%u=%x\n", __LINE__, (i), MDrv_Read4Byte(0x100218));\
}while(0)

#define DUMP_R2_REGS()  do{ \
    int i;  \
    for( i = 18; i < 24; i += 1 ) \
    { \
        DUMP_R2_REG(i); \
    } \
}while(0)

void Print_R2_SPR_PICMR(U32 u32, const char* pcStr);
#endif


void Print_Buffer(U8* pu8Buf, U32 u32Size );

//==================================================================================
void msDebug_ANSI_SetColorText(U8 u8FontColor);
void msDebug_ANSI_SetColorText_2(U8 u8FontColor, U8 u8BGColor);
void msDebug_ANSI_AllAttrOffText(void);

#if( ENABLE_UART_MSG_COLOR )
    #define ANSI_COLOR_RED      "\x1b[31m"
    #define ANSI_COLOR_GREEN    "\x1b[32m"
    #define ANSI_COLOR_YELLOW   "\x1b[33m"
    #define ANSI_COLOR_BLUE     "\x1b[34m"
    #define ANSI_COLOR_MAGENTA  "\x1b[35m"
    #define ANSI_COLOR_CYAN     "\x1b[36m"
    #define ANSI_COLOR_RESET    "\x1b[0m"

    #define ANSI_COLOR_OFF_STR  "\033[0m"
#else

    #define ANSI_COLOR_RED      ""
    #define ANSI_COLOR_GREEN    ""
    #define ANSI_COLOR_YELLOW   ""
    #define ANSI_COLOR_BLUE     ""
    #define ANSI_COLOR_MAGENTA  ""
    #define ANSI_COLOR_CYAN     ""
    #define ANSI_COLOR_RESET    ""

    #define ANSI_COLOR_OFF_STR  ""
#endif
//==================================================================================

#if( defined(__mips__) )

void msDebug_mips_BackTrace(MS_U32 pHalReg);
void mips_Exception_Handler(MHAL_SavedRegisters *regs, MS_U32 vector);

#endif

BOOL msDebug_CheckPoint(void);

U32 msDebug_PA2VA(U32 u32PA);


//-----------------------------------------------------------------------
typedef enum
{
    FATAL_ERR_ID_UNKNOEN            = 0,
    FATAL_ERR_ID_MEMORY_ALLOC_FAILED = 1,
    FATAL_ERR_ID_INVALID_PHY_ADDR   = 2,

    FATAL_ERR_ID_FLASH_SIZE_INVALID    = 10,
    FATAL_ERR_ID_FLASH_WRITE_ADDR_INVALID = 11, // When write flash, the address is invalid
    FATAL_ERR_ID_BIN_FILE_CRC_ERROR         = 12, // Check bin file CRC error

    FATAL_ERR_ID_OCP_BMP_BIN_FILE_TOO_BIG       = 20, // bmp.bin is too big
    FATAL_ERR_ID_OCP_STRING_BIN_FILE_TOO_BIG    = 21, // string.bin is too big

    FATAL_ERR_ID_AUDIO_MEM_SIZE_ERROR = 30,

    FATAL_ERR_ID_VIF = 100,
    FATAL_ERR_ID_TUNER_FREQ_INVALID = 101,

    FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR    = 110,
    FATAL_ERR_ID_SI_LIB_VERSION_ERROR           = 111,

} EnuFatalErrorId;

void msDebug_FatalErrorHandler(U32 u32Id, U32 u32Para);
void msDebug_FatalErrorHandler_Para_2(U32 u32Id, U32 u32Para, U32 u32Para2);
//-----------------------------------------------------------------------

#define ENABLE_DBG_SAVE_USB 0
#if(ENABLE_DBG_SAVE_USB)
BOOL msDebug_SaveDataToUSB(char* pcFileName, U8* pu8Data, U32 u32DataSize);
#endif
//--------------------------------------------------------------------------------
#define ENABLE_CHECK_MEMORY_CHANGE  0

#if(ENABLE_CHECK_MEMORY_CHANGE)
void msDebug_CheckMemChg_Init(U32 u32MemAddr, U32 u32Size);
BOOLEAN msDebug_CheckMemChg_Check(U32 u32Flag);

#define CHECK_MEM_CHANGE() do { \
    if( FALSE == msDebug_CheckMemChg_Check(__LINE__) )\
    {\
        PRINT_CURRENT_LINE();\
    }\
} while(0)

#else

#endif

//--------------------------------------------------------------------------------
#ifdef __arm__
void msDebug_ARM_BackTrace(MS_U32 pHalReg);
#endif

//=======================================================================

#undef INTERFACE
#endif  //_MSTAR_DEBUG_H_

