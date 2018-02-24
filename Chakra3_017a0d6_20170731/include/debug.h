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

#ifndef _DEBUG_H
#define _DEBUG_H

#include "datatype.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "mstar_debug.h"
#include "Mstar_USBScript.h"


/*definition ====================================================================================*/
#define WINDOWS        1
#define CYGWIN        2
#define SIMULATOR    3
#define MCU8051        4
#define OPENRISC    5
#define LINUX        6
#define PLATFORM    MCU8051
/*===============================================================================================*/

#define BUILD_SYSDEBUG  0
#define USER_DEBUG      0
#define SYSTEM_DEBUG    0
#define SHOW_MEMORY_MAP 0    // print memory at system startup
#define STACK_GUARD     0    // put a sentinel to stack and report if it is changed
#define TIMING_DBG      0




#define ENABLE_DLC_TEST_BY_MSTVTOOL     1
#define CHANNEL_SCAN_AUTO_TEST          0
#define SFU_AUTO_TEST                   0

//-----------type "uu" to udpate software by USB--------------------------------

#define STATE_PRINT         0

#ifdef ENABLE_DEBUG
#define DEBUG_INFO(y) y
#else
#define DEBUG_INFO(y)
#endif

#if STATE_PRINT
#define DEBUG_STATE(y) y
#else
#define DEBUG_STATE(y)
#endif

#define ERR_NONE                        0x0000
#define ERR_OUT_OF_MEMORY               0x0001
#define ERR_MEMORY_NOT_ALLOCATED        0x0002
#define ERR_BIN_ID_NOT_FOUND            0x0003

#define ERR_FONT_GENERIC_ERROR          0x0100
#define ERR_FONT_BIN_NOT_FOUND          0x0101
#define ERR_FONT_OUT_OF_BUFFER          0x0102
#define ERR_FONT_WRONG_FORMAT           0x0103

#define ERR_BMP_GENERIC_ERROR           0x0200
#define ERR_BMP_BIN_NOT_FOUND           0x0201
#define ERR_BMP_OUT_OF_BUFFER           0x0202

#define ERR_FB_ID_OUT_OF_RANGE          0x0300
#define ERR_FB_ID_NOT_ALLOCATED         0x0301
#define ERR_FB_ID_ALREADY_ALLOCATED     0x0302
#define ERR_FB_OUT_OF_MEMORY            0x0303
#define ERR_FB_OUT_OF_ENTRY             0x0304

#define ERR_MVD_GENERIC_ERROR           0x1000
#define ERR_MVD_BOOT_TIMEOUT            0x1001
#define ERR_MVD_MODE_UNSUPPORTED        0x1002

#define ERR_MAD_GENERIC_ERROR           0x1100

#define ERR_DEMUX_GENERIC_ERROR         0x1200

#define ERR_GWIN_GENERIC_ERROR          0x1300
#define ERR_GWIN_ID_OUT_OF_RANGE        0x1301
#define ERR_GWIN_ID_NOT_ALLOCATED       0x1302
#define ERR_GWIN_ID_ALREADY_ALLOCATED   0x1303
#define ERR_GWIN_ID_ALREADY_MAPPED      0x1304

#define ERR_GE_GENERIC_ERROR            0x1400
#define ERR_GE_OUT_OF_FONT_TABLE        0x1401
#define ERR_GE_OUT_OF_BITMAP_TABLE      0x1402

#define ERR_UIMENU_GENERIC_ERROR        0x8000

// You can add FUNCTION_RESULT's member below for any result of operation
// to describe why function could not finish operation successfully.
// [NOTICE] Do not compare return value of function with E_RESULT_FAILURE.
//          Because there are many kinds of failure.
//          For example,
//          ex1)    if( E_RESULT_FAILURE == msAPI_CM_AddProgram(...) )
//          Instead of using above, use like below.
//          ex2)    if( E_RESULT_SUCCESS != msAPI_CM_AddProgram(...) )
/// Function result enumerate
typedef enum
{
    E_RESULT_SUCCESS = 0,                 ///< Result Success
    E_RESULT_FAILURE,                     ///< Result Failure
    E_RESULT_INVALID_PARAMETER,         ///< Result Invalid Parameter
    E_RESULT_OUTOF_MEMORY,               ///< Result Out of memory
    E_RESULT_OUTOF_EEPROM,               ///< Result Out of EEPROM
    E_RESULT_COMMUNICATION_ERROR,       ///< Result Communication Error
    E_RESULT_SAVE_TO_EEPROM_FAIL,       ///< Result Save to EEPROM fail
    E_RESULT_NOTHING,                    ///< Result Nothing
    E_RESULT_ILLEGAL_ACCESS,            ///< Result Illegal access
    E_RESULT_UNSUPPORTED                ///< Result unsupported
} FUNCTION_RESULT;

#if 0
void msWarning(unsigned int ErrCode);
void msFatal(unsigned int ErrCode);
#else
#define msWarning(c)    do {} while (0)
#define msFatal(c)      do {} while (0)
#endif

#define MS_CRITICAL_MSG(x)      x

//extern char code g_str_assert[]; // defined in STARTUP.A51
/*
#ifdef MSOS_TYPE_LINUX
#define __ASSERT(expr) (void)((expr) || printf("%s %d\n", __FILE__, __LINE__));
#else
#define __ASSERT(expr)  (void)((expr) || printf(g_str_assert, __FILE__, (int)__LINE__))
#endif
*/


#if ENABLE_DBG
    #define MS_DEBUG_MSG(x)         x
    #define __ASSERT(expr)  do { \
        if(expr)        \
            { printf("\nAssert! at %s : %u", __FILE__, (int)__LINE__); } \
    } while(0)

#else
    #define MS_DEBUG_MSG(x)
    //#undef ASSERT
    //#define ASSERT(x)
    //#undef __ASSERT
    #define __ASSERT(x)
#endif

#undef ASSERT
#define ASSERT(expr)    __ASSERT(expr)

#undef STATIC_ASSERT
#define STATIC_ASSERT(_x_)                  \
    do {                                    \
        char c[(_x_)?(-1):(1)];             \
        c[0]='\0';                          \
        c[0]= c[0];                         \
    } while (0)


#define HERE            MS_DEBUG_MSG(printf("\n%s %s Line %d:\n", __FILE__, __FUNCTION__, __LINE__));
#define BOOT_TIME_DBG() printf("[%s] %lu -- %lu\n",__FILE__,(U32)__LINE__, msAPI_Timer_GetTime0())

#define debugPrint(a,b)

#define PRINT_VAR(var)      printf(#var "=%u\n", var)

#define PRINT_CUR_FUNCTION()    printf("%s()\n", __FUNCTION__)
#define PRINT_CURRENT_LINE()    do { \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);              \
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_GREEN);   \
    printf("%u : %s : %s() at %u\n", __LINE__, __FILE__, __FUNCTION__, MsOS_GetSystemTime()); \
    msDebug_ANSI_AllAttrOffText();          \
  } while(0)


#define DEBUG_INIT_FLOW(x)  //x

#define CHECK_POINT_FUNC()  msDebug_CheckPoint()//0

#define DEBUG_CHECK_POINT() //do { if( CHECK_POINT_FUNC() ) {PRINT_CURRENT_LINE();} } while(0)

#define BUILD_BUG_ON(condition)     ((void)sizeof(char[1 - 2*!!(condition)]))

#define BUILD_ERROR_IF_TRUE(condition)  BUILD_BUG_ON((condition))


#define FATAL_ERROR_HAPPEN(id, para)  do { \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);              \
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);   \
    printf("\nFatal Error: %u : %s : %s()\n", __LINE__, __FILE__, __FUNCTION__); \
    msDebug_FatalErrorHandler((id),(para));    \
    msDebug_ANSI_AllAttrOffText();          \
  } while(0)



#define PRINT_TODO()    do { \
    msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);              \
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_PURPLE);   \
    printf("%u : %s : %s() at %u\n", __LINE__, __FILE__, __FUNCTION__, MsOS_GetSystemTime()); \
    msDebug_ANSI_AllAttrOffText();          \
  } while(0)



//===============================================================================

extern U32 g_Debug_u32Time_ChangeChannel;

int Debug_Log_MemPrintf(U8 u8GroupIdx, const char *fmt, ...);

#define ENABLE_LOG_CHANGE_CHANNEL   0

#if( ENABLE_LOG_CHANGE_CHANNEL )

  #define PRINT_FUNC_START_TIME()   do { \
    printf("{{ %s() Start at %u(%u)\n", __FUNCTION__, MsOS_GetSystemTime(), g_Debug_u32Time_ChangeChannel); \
  } while(0)

  #define PRINT_FUNC_END_TIME()   do { \
    printf("}} %s() End at %u(%u)\n", __FUNCTION__, MsOS_GetSystemTime(), g_Debug_u32Time_ChangeChannel); \
  } while(0)

#else
    #define PRINT_FUNC_START_TIME()
    #define PRINT_FUNC_END_TIME()

#endif


#if( ENABLE_LOG_CHANGE_CHANNEL&&ENABLE_LOG_FILE_IN_MEM )
    #define LOG_CHANGE_CHANNEL_TIME_FUNC_START()    Debug_Log_MemPrintf(0, "{{ %s() Start at %u\n", __FUNCTION__, g_Debug_u32Time_ChangeChannel)
    #define LOG_CHANGE_CHANNEL_TIME_FUNC_END()      Debug_Log_MemPrintf(0, "}} %s() End at %u\n", __FUNCTION__, g_Debug_u32Time_ChangeChannel)
    #define LOG_CHANGE_CHANNEL_TIME(str)            do { \
        Debug_Log_MemPrintf(0, str); \
        Debug_Log_MemPrintf(0, ":%u at %u\n", __LINE__, g_Debug_u32Time_ChangeChannel); \
      } while(0)
#else
    #define LOG_CHANGE_CHANNEL_TIME_FUNC_START()
    #define LOG_CHANGE_CHANNEL_TIME_FUNC_END()
    #define LOG_CHANGE_CHANNEL_TIME(str)
#endif

//========================================================================
#if( CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA )
    #define IF_PHY_ADDR_INVALID(PhyAdr)     ( (PhyAdr) > 0xFF00000 )
#else
    #define IF_PHY_ADDR_INVALID(PhyAdr)     ( (PhyAdr) > 0x8000000 )
#endif

#define CHECK_PHY_ADDR(adr) do { \
    if( IF_PHY_ADDR_INVALID((adr)) ) \
    {   \
        PRINT_CURRENT_LINE();   \
        printf("\nError: Invalid PhyAddr=0x%X\n", (adr));   \
        msDebug_FatalErrorHandler(FATAL_ERR_ID_INVALID_PHY_ADDR, (adr));   \
    }   \
} while(0)

//
//******************************************************************************
//

#define ENABLE_TIME_LOG     ENABLE//ENABLE//DISABLE

//
//******************************************************************************
//

#endif    /*_DEBUG_H END */

