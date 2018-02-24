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
#define _MSTAR_DEBUG_C_
////////////////////////////////////////////////////////////////////////////////
///
/// @file mstar_debug.c
/// @author MStar Semiconductor Inc.
/// @brief MStar Debug Related Functions
///
////////////////////////////////////////////////////////////////////////////////


/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>
#include <string.h>

#if defined(__aeon__)
#include "risc32_spr.h"
#endif

// Global
#include "datatype.h"
#include "debug.h"
#include "sysinfo.h"
#include "SysInit.h"
//...

// Driver Layer
#include "drvUSB.h"
#if(ENABLE_CHECK_MEMORY_CHANGE)
#include "drvBDMA.h"
#endif
//...

// API Layer
//#include "msAPI_Subtitle_Pub.h"
#include "msAPI_FCtrl.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_Timer.h"
#include "msAPI_Global.h"

//...

// MW Layer
#include "mstar_debug.h"
#include "mw_debug.h"

#if(ENABLE_DEBUG_DELAY_TIME&&ENABLE_DTV)
#include "msAPI_DTV_Common.h"
#endif



/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/

//------------------------------------------------------------------------------
/// MStar Debug Initial
/// @param  None
/// @return None
//------------------------------------------------------------------------------
void MStarDebugInitial(void)
{
    //U8 u8HVer[32] = {SUBTITLE_VER()};
    //U8 u8LibVer[32];

    MWDebugInitial();

    //MStarDebugShowVerString(&u8HVer[0], sizeof(u8HVer));
    //msAPI_Subtitle_GetLIBVerString(&u8LibVer[0]);
    //MStarDebugShowVerString(&u8LibVer[0], sizeof(u8LibVer));
    //MStarDebugSameVer(u8LibVer, u8HVer, sizeof(u8LibVer));

#if( ENABLE_LOG_FILE_IN_MEM )
    Debug_Log_Init();
#endif
}

//------------------------------------------------------------------------------
/// MStar Debug Show Version String
/// @param *string \b IN: string pointer
/// @param size \b IN: string length
/// @return None
//------------------------------------------------------------------------------
void MStarDebugShowVerString(U8 *string, U8 size)
{
    U8 i;
    U8 u8GenFlag = TRUE;

    if((string[0]=='M') &&
       (string[1]=='S') &&
       (string[2]=='I') &&
       (string[3]=='F') &&
       (string[4]=='0'))
    {
        switch(string[5])
        {
            // Middleware
            case '3':
                {
                    MWDebugShowVerString(string);
                    u8GenFlag = FALSE;
                }
                break;

            default:
                break;
        }
    }
    else
    {
    }

    if(u8GenFlag)
    {
        MS_DEBUG_MSG(printf("Ver:"));
        for(i=0; i<size; i++)
        {
            if(((string[i]>='A') && (string[i]<='Z')) ||
               ((string[i]>='0') && (string[i]<='9')))

            {
                MS_DEBUG_MSG(printf("%c", string[i]));
            }
            else
            {
                MS_DEBUG_MSG(printf("*"));
            }
        }
        MS_DEBUG_MSG(printf("\n"));
    }
}

//------------------------------------------------------------------------------
/// MStar Debug Show Version String
/// @param *str1 \b IN: string pointer
/// @param *str2 \b IN: string pointer
/// @param size \b IN: compare size
/// @return TRUE, The 2 Version is the same
///        FALSE, The version is different
//------------------------------------------------------------------------------
BOOL MStarDebugSameVer(U8 *str1, U8 *str2, U8 size)
{
    if(memcmp(str1, str2, size))
    {
        printf("FALSE\n");
        return FALSE;
    }
    else
    {
        printf("TRUE\n");
        return TRUE;
    }
}


#if( ENABLE_LOG_FILE_IN_MEM )

#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MARLON) )
  #if(MEMORY_MAP == MMAP_128MB)
   #if ((MIU_DRAM_LEN0-MIU0_END_ADR) < 0x2000ul )
    #error "memory is not enough!!"
   #endif
    #define LOG_FILE_MEM_START          MIU0_END_ADR
  #else
    #define LOG_FILE_MEM_START          0x3FD0000
  #endif
    #define LOG_FILE_GROUP_NUM          1
    #define LOG_FILE_MEM_ADDR_SIZE(GroupIdx)    (0x2000ul) // 8K

#elif(CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)
    #define LOG_FILE_MEM_START          MIU0_END_ADR
    #define LOG_FILE_GROUP_NUM          1
    #define LOG_FILE_MEM_ADDR_SIZE(GroupIdx)    (0x2000ul) // 8K
#else
    #define LOG_FILE_MEM_START          MIU0_END_ADR
    #define LOG_FILE_GROUP_NUM          2
    #define LOG_FILE_MEM_ADDR_SIZE(GroupIdx)    (0x10000ul) // 64K *
#endif

#define LOG_FILE_MEM_ADDR_START(GroupIdx)   ( (LOG_FILE_MEM_START) + ((GroupIdx)*LOG_FILE_MEM_ADDR_SIZE((GroupIdx))) )
#define LOG_FILE_MEM_ADDR_END(GroupIdx)     ( LOG_FILE_MEM_ADDR_START((GroupIdx)) + LOG_FILE_MEM_ADDR_SIZE((GroupIdx)) )

// Check if memory usage valid?
#if( LOG_FILE_MEM_ADDR_END((LOG_FILE_GROUP_NUM-1)) >= MIU_DRAM_LEN0 )
    #error "Over memory range"
#endif

static U32 g_LogFile_u32CurMemAddr[LOG_FILE_GROUP_NUM] = {LOG_FILE_MEM_ADDR_START(0)};
static U32 g_LogFile_u32CharCount[LOG_FILE_GROUP_NUM] = {0};

//void mdrv_uart_putc(char c);

void Debug_Log_Init(void)
{
    U8 u8GroupIdx;

    for( u8GroupIdx = 0; u8GroupIdx < LOG_FILE_GROUP_NUM; ++ u8GroupIdx )
    {
        g_LogFile_u32CurMemAddr[u8GroupIdx] = LOG_FILE_MEM_ADDR_START(u8GroupIdx);
        g_LogFile_u32CharCount[u8GroupIdx] = 0;
    }
}

void Debug_Log_Reset(U8 u8GroupIdx)
{
    g_LogFile_u32CurMemAddr[u8GroupIdx] = LOG_FILE_MEM_ADDR_START(u8GroupIdx);
    g_LogFile_u32CharCount[u8GroupIdx] = 0;
}

U8 Debug_Log_MemReadByte(U32 u32MemAddr )
{
    U32 u32VirAddr;
    U8 u8Data;

    //MsOS_ReadMemory();

    u32VirAddr = MsOS_PA2KSEG1(u32MemAddr);
    //printf("u32MemAddr  %X => %X\n", u32MemAddr, (U32)pu8);

    // non-cache addr to cached addr
    //u32VirAddr = u32VirAddr&0x7FFFFFFF;
    //MsOS_Dcache_Flush( u32VirAddr, 1);

    MsOS_FlushMemory();

    u8Data = *((volatile unsigned char*)u32VirAddr);

    return u8Data;
}

void Debug_Log_MemWriteByte(U32 u32MemAddr, U8 u8Data, BOOLEAN bFlushMemory )
{
    U32 u32VirAddr;

    u32VirAddr = MsOS_PA2KSEG1(u32MemAddr);

    //printf("%X -> %X\n", u32MemAddr, (U32)u32VirAddr);

    // non-cache addr to cached addr
    //u32VirAddr = u32VirAddr&0x7FFFFFFF;

    *((volatile unsigned char*)u32VirAddr) = u8Data;

    //MsOS_Dcache_Flush( u32VirAddr, 1);

    if( bFlushMemory )
    {
        MsOS_FlushMemory();
    }
}

void Debug_Log_PutCharInMem(U8 u8GroupIdx, char ch, BOOLEAN bFlushMemory)
{
    if( u8GroupIdx >= LOG_FILE_GROUP_NUM )
        return;

    // Check if buf full
    if( g_LogFile_u32CharCount[u8GroupIdx] >= LOG_FILE_MEM_ADDR_SIZE(u8GroupIdx) )
    {
        putchar(ch);
        return;
    }


    if( g_LogFile_u32CurMemAddr[u8GroupIdx] >= (LOG_FILE_MEM_ADDR_END(u8GroupIdx)-1) )
    {
        g_LogFile_u32CurMemAddr[u8GroupIdx] = LOG_FILE_MEM_ADDR_START(u8GroupIdx);
    }

    Debug_Log_MemWriteByte( g_LogFile_u32CurMemAddr[u8GroupIdx], ch, bFlushMemory );

    g_LogFile_u32CurMemAddr[u8GroupIdx] += 1;
    //mdrv_uart_putc(ch);

    if( g_LogFile_u32CurMemAddr[u8GroupIdx] >= (LOG_FILE_MEM_ADDR_END(u8GroupIdx)-1) )
    {
        g_LogFile_u32CurMemAddr[u8GroupIdx] = LOG_FILE_MEM_ADDR_START(u8GroupIdx);
    }

    g_LogFile_u32CharCount[u8GroupIdx] += 1;
/*
    if( g_LogFile_u32CharCount[u8GroupIdx] > LOG_FILE_MEM_ADDR_SIZE(u8GroupIdx) )
    {
        g_LogFile_u32CharCount[u8GroupIdx] = LOG_FILE_MEM_ADDR_SIZE(u8GroupIdx);
    }
*/
    //printf("[%X]", g_LogFile_u32CharCount[u8GroupIdx]);
}

void putcharb(MS_U8 byte);

void Debug_Log_PrintAll(U8 u8GroupIdx)
{
    U32 u32Cnt;
    U32 u32Idx;
    U32 u32VirAddr;


    if( u8GroupIdx >= LOG_FILE_GROUP_NUM )
    {
        printf("Unknown groupIdx=%u\n", u8GroupIdx);
        return;
    }

    printf( "\033[%dm\033[%dm", E_FONT_COLOR_WHITE, E_FONT_BACKGROUND_COLOR_BLUE);


    printf("Debug_Log_PrintAll(u8GroupIdx=%u)\n", u8GroupIdx );
    printf(" g_LogFile_u32CharCount=%u\n", g_LogFile_u32CharCount[u8GroupIdx]);


    u32VirAddr = _PA2VA(LOG_FILE_MEM_ADDR_START(u8GroupIdx));
    //printf("u32MemAddr  %X => %X\n", u32MemAddr, (U32)pu8);

    // non-cache addr to cached addr
    //u32VirAddr = u32VirAddr&0x7FFFFFFF;

    if( g_LogFile_u32CharCount[u8GroupIdx] >= LOG_FILE_MEM_ADDR_SIZE(u8GroupIdx) )
    {
        u32Idx = g_LogFile_u32CurMemAddr[u8GroupIdx];
    }
    else
    {
        u32Idx = 0;
    }

    for( u32Cnt = 0; u32Cnt < g_LogFile_u32CharCount[u8GroupIdx]; ++ u32Cnt )
    {
        //mdrv_uart_putc(  ((volatile char*)(u32VirAddr))[u32Idx] );
        putcharb(  ((volatile char*)(u32VirAddr))[u32Idx] );

        u32Idx = (u32Idx + 1) % LOG_FILE_MEM_ADDR_SIZE(u8GroupIdx);
    }

    msDebug_ANSI_AllAttrOffText();
}

#include <stdio.h>

int Debug_Log_MemPrintf(U8 u8GroupIdx, const char *fmt, ...)
{
    int i, iret;
    char szPrint[PRINTF_CHAR_MAX];
    va_list ap;
    char ch;

    va_start(ap, fmt);
    iret = vsnprintf(szPrint, PRINTF_CHAR_MAX, fmt, ap);
    va_end(ap);

    u8GroupIdx=u8GroupIdx;

    for (i = 0; i < iret; i++)
    {
        //putchar(szPrint[i]);
        ch = szPrint[i];

        if( ch == '\r' )
        {
        }
        else if( ch == '\n' )
        {
            Debug_Log_PutCharInMem(u8GroupIdx, '\r', FALSE);
        }

        Debug_Log_PutCharInMem(u8GroupIdx, ch, FALSE);
    }

    MsOS_FlushMemory();

    return iret;
}

#endif

int printf_2(const char *fmt, ...)
{
    int i, iret;
    char szPrint[PRINTF_CHAR_MAX];
    va_list ap;

    va_start(ap, fmt);
    iret = vsnprintf(szPrint, PRINTF_CHAR_MAX, fmt, ap);
    va_end(ap);

    for (i = 0; i < iret; i++)
    {
        putchar(szPrint[i]);
    }

    return iret;
}


#if(ENABLE_UART_MSG_TO_USB)

#define DEBUG_U2U(x)     // x

#define U2U_CLEAR_WATCHDOG()    MDrv_Sys_ClearWatchDog()

#define UART_TO_USB_FOLDER_NAME_1   "_msLogSaveToUsb"       // Log only save to USB
#define UART_TO_USB_FOLDER_NAME_2   "UART2USB"//"_msLogSaveToUsb_Uart"  // Log save to USB and uart


#define UART_TO_USB_FILE_NAME   "uart" //'u','a','r','t','.','t','x','t',


typedef enum
{
    U2U_MODE_LOG_SAVE_TO_USB_DISABLE,       // Uart On, Usb Off
    U2U_MODE_LOG_SAVE_TO_USB_AND_UART_ON,   // Uart On, Usb On
    U2U_MODE_LOG_SAVE_TO_USB_AND_UART_OFF,  // Uart Off, Usb On
} EnuU2ULogMode;
static EnuU2ULogMode s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;

static BOOL _s_U2U_bFileSystemInited = FALSE;
static U8 _s_U2U_u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;

static U16 _s_U2U_u16FileNameCount = 0;

static FileEntry _s_U2U_FileEntry;
static U8 s_U2U_u8FileHandle = INVALID_FILE_HANDLE;

static BOOL s_U2U_bProtectRecursive = FALSE;

static BOOL s_U2U_bInitDone = FALSE;

static BOOL s_U2U_bEnable = FALSE;

static U16 s_U2U_u16Count_OpenFile = 0;

static U32 s_U2U_u32ErrorCount_WriteFile = 0;

void msDebug_UartToUSB_DeInitFileSystem(void);
BOOL msDebug_UartToUSB_CloseFile(void);

void msDebug_UartToUSB_Init(void)
{
    DEBUG_U2U( printf_2("msDebug_UartToUSB_Init()\n",0); );

    s_U2U_bEnable = FALSE;

    s_U2U_bProtectRecursive = FALSE;

    s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;
    //_s_U2U_FileEntry.EntryType = ENTRY_TYPE_NULL;

    _s_U2U_u16FileNameCount = 0;
    s_U2U_u32ErrorCount_WriteFile = 0;

    s_U2U_bInitDone = TRUE;
}

void msDebug_UartToUSB_Reset(void)
{
    DEBUG_U2U( printf_2("msDebug_UartToUSB_Reset()\n",0); );

    s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;

    //_s_U2U_FileEntry.EntryType = ENTRY_TYPE_NULL;
    //s_U2U_u8FileHandle = 0xFF;
    msDebug_UartToUSB_CloseFile();

    //_s_U2U_bFileSystemInited = FALSE;
    //_s_U2U_u8FileSysEnvironmentID = 0xFF;
    //msDebug_UartToUSB_DeInitFileSystem();

    //_s_U2U_u16FileNameCount = 0;
}

U8 msDebug_UartToUSB_OpenUSBPort(void)
{
#if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
    U8 u8PortEnStatus = 0;
    U8 u8UsbPortNO = 0;

    DEBUG_U2U( printf_2(" msDebug_UartToUSB_OpenUSBPort()\n",0); );

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    //DEBUG_U2U( printf_2("  u8PortEnStatus=0x%X\n", u8PortEnStatus); );

    if((u8PortEnStatus & BIT0) == BIT0)
    {
        /*
        if( !MDrv_UsbDeviceConnect() )
        {
            printf_2("\nWarning: port0 not connect, try again\n", 0);
            U2U_CLEAR_WATCHDOG();
            MsOS_DelayTask(200);
            U2U_CLEAR_WATCHDOG();
        }*/
        if( !MDrv_UsbDeviceConnect() )
        {
            DEBUG_U2U( printf_2("\n Warning: port0 not connect!\n", 0); );
            u8UsbPortNO = 0;
        }
        else
        {
            u8UsbPortNO = 1;
        //MApp_UsbDownload_Init(BIT0, MApp_ZUI_SwUpdate_ProgressBar);
        }
    }
    if((u8PortEnStatus & BIT1) == BIT1)
    {
        /*if (!MDrv_UsbDeviceConnect_Port2())
        {
            printf_2("\nWarning: port1 not connect, try again\n", 0);
            U2U_CLEAR_WATCHDOG();
            MsOS_DelayTask(200);
            U2U_CLEAR_WATCHDOG();
        }*/
        if(u8UsbPortNO != 1)
        {
            if (!MDrv_UsbDeviceConnect_Port2())
            {
                DEBUG_U2U( printf_2("\n Warning: port1 not connect!\n", 0); );
                u8UsbPortNO = 0;
            }
            else
            {
                u8UsbPortNO = 2;
            }
        }
        //MApp_UsbDownload_Init(BIT1, MApp_ZUI_SwUpdate_ProgressBar);
    }
    if(((u8PortEnStatus & BIT0) != BIT0)&&((u8PortEnStatus & BIT1) != BIT1))
    {
        printf_2("\n Error: Unknown USB port\n", 0);
        return 0;
    }
    //DEBUG_U2U( printf_2("u8UsbPortNO=%u\n", u8UsbPortNO); );

    return u8UsbPortNO;
#else
    return 0;
#endif
}

void msDebug_UartToUSB_DeInitFileSystem(void)
{
    DEBUG_U2U( printf_2(" msDebug_UartToUSB_DeInitFileSystem()\n", 0); );

    if( _s_U2U_u8FileSysEnvironmentID != INVALID_FS_ENVIRONMENT_INDEX )
    {
        msAPI_FSEnv_UnRegister(_s_U2U_u8FileSysEnvironmentID);
        _s_U2U_u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;
    }

    _s_U2U_bFileSystemInited = FALSE;

#if 0
    if (_s_U2U_bFileSystemInited)
    {
        _s_U2U_bFileSystemInited = FALSE;

        //msAPI_FCtrl_FileHandleResetAll();

        //MApp_MassStorage_DeviceDisconnect();
        //msAPI_FCtrl_Init();
    }
#endif

}

BOOL msDebug_UartToUSB_InitFileSystem(U8 u8UsbPortNO)
{
    DEBUG_U2U( printf_2(" msDebug_UartToUSB_InitFileSystem(u8UsbPortNO=%u)\n", u8UsbPortNO); );

    if( (u8UsbPortNO != 1) && (u8UsbPortNO != 2) )
    {
        printf_2("\nError: u8UsbPortNO=%u\n", u8UsbPortNO);
        return FALSE;
    }

    // msAPI_FS_Init() already inited
    //msAPI_FS_Init();

    msAPI_MSDCtrl_CheckDevices();

    _s_U2U_bFileSystemInited = FALSE;
    _s_U2U_u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;

    if( (u8UsbPortNO == 1) || (u8UsbPortNO == 2) )
    {
        U8 u8DeviceIdx_Start, u8DeviceIdx_End;
        U8 u8DeviceIdx;

        if( u8UsbPortNO == 1 )
        {
            u8DeviceIdx_Start = MSD_USB_INDEX_START;
            u8DeviceIdx_End = MSD_USB_INDEX_START + MSD_USB_NUM;
        }
        else
        {
            u8DeviceIdx_Start = MSD_USB_2_INDEX_START;
            u8DeviceIdx_End = MSD_USB_2_INDEX_START + MSD_USB_2_NUM;
        }

        for( u8DeviceIdx = u8DeviceIdx_Start; u8DeviceIdx < u8DeviceIdx_End; u8DeviceIdx++)
        {
            EN_MSD_STATUS eMsdStatus = msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIdx);
            //printf("  Dev=%u status=%u\n", u8DeviceIdx, eMsdStatus );
            if( eMsdStatus == MSD_STATUS_INSERTED )
            {
                msAPI_FCtrl_ActiveDevice(u8DeviceIdx);
                eMsdStatus = msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIdx);
                //printf("  status=%u\n", eMsdStatus );
            }

            if( eMsdStatus == MSD_STATUS_IDLE )
            {
                _s_U2U_u8FileSysEnvironmentID = msAPI_FSEnv_Register(0x00 /*'A'*/);
                _s_U2U_bFileSystemInited = msAPI_FCtrl_DirectoryChangeToRoot(_s_U2U_u8FileSysEnvironmentID);
                //printf("  u8DeviceIdx=%u, FSEnvId=%u, init=%u\n", u8DeviceIdx, _s_U2U_u8FileSysEnvironmentID, _s_U2U_bFileSystemInited);
                break;
            }
        }
    }

    if( !_s_U2U_bFileSystemInited )
    {
        printf_2("\nError: Init file system failed! (u8UsbPortNO=%u)\n", u8UsbPortNO);
        return FALSE;
    }

    return TRUE;
}

void _PrintFileName(U16* pu16FileName)
{
    if( pu16FileName == NULL )
        return;

    putchar('[');
    while(1)
    {
        if( *pu16FileName == 0 )
            break;

        if( *pu16FileName < 127 )
            putchar(*pu16FileName);
        else
            //printf("(%X)", *pu16FileName);
            putchar('?');

        //printf(" ");

        pu16FileName += 1;
    }
    putchar(']');
}

void PrintFileEntry_Id(FileEntry* pFileEntry)
{
    printf_2(" EntryID[]: %x %x %x %x\n",
        pFileEntry->EntryID[0], pFileEntry->EntryID[1],
        pFileEntry->EntryID[2], pFileEntry->EntryID[3]);

    printf_2("  EntryID_Ext[]: %x %x %x %x %x %x %x %x\n",
            pFileEntry->EntryID_Ext[0], pFileEntry->EntryID_Ext[1],
            pFileEntry->EntryID_Ext[2], pFileEntry->EntryID_Ext[3],
            pFileEntry->EntryID_Ext[4], pFileEntry->EntryID_Ext[5],
            pFileEntry->EntryID_Ext[6], pFileEntry->EntryID_Ext[7] );
}

BOOL CompareFileEntry(FileEntry* pFileEntry1, FileEntry* pFileEntry2)
{
    U8 i;
    BOOL bIsTheSame = TRUE;


    for( i = 0; i < 8; ++ i )
    {
        if( pFileEntry1->EntryID_Ext[i] != pFileEntry2->EntryID_Ext[i] )
        {
            bIsTheSame = FALSE;
            break;
        }
    }

    if( bIsTheSame == FALSE )
    {
        PrintFileEntry_Id(pFileEntry1);
        PrintFileEntry_Id(pFileEntry2);
    }

    return bIsTheSame;
}

static BOOL _CompareString_U8_U16(char* pcStr, U16* pu16Str, U8 u8MaxLen)
{
    U8 i;
    BOOL bRtn = TRUE;
    U16 c1, c2;


    for( i = 0; i < u8MaxLen; ++ i )
    {
        c1 = pcStr[i];
        c2 = pu16Str[i];

    /*
        if ((c1 >= 'a') && (c1 <= 'z'))
        {
            c1 -= 'a' - 'A';
        }

        if ((c2 >= 'a') && (c2 <= 'z'))
        {
            c2 -= 'a' - 'A';
        }
        */

        if( c1 != c2 )
        {
            bRtn = FALSE;
            break;
        }

        if( c1 == 0 )
            break;

    }

    return bRtn;
}

BOOL msDebug_UartToUSB_SearchFile(U8 u8FSEnvId, char* pcTargetFileName, BOOL bFindFolder, FileEntry* pFileEntry)
{
    U16 u16EntryIdx;

    U8 u8TargetFileNameLen = strlen(pcTargetFileName);
    BOOL bFolderFound = FALSE;
    FileEntry tmpFileEntry;
    EN_ENTRY_TYPE tmpEntryType;
    U16 au16CurFileName[128];
    U8 u8CurFileNameLen;


    DEBUG_U2U( printf_2(" msDebug_UartToUSB_SearchFile(%s)\n", pcTargetFileName); );

    //DEBUG_U2U( printf("  u8TargetFileNameLen=%u\n", u8TargetFileNameLen ); );

    if( u8TargetFileNameLen == 0 )
        return FALSE;

    msAPI_FCtrl_EntryFirst(u8FSEnvId);

    // Find out the special folder
    u16EntryIdx = 0;
    while( msAPI_FCtrl_EntryNext(u8FSEnvId, &tmpFileEntry) == ENTRY_NEXT_RESULT_SUCCESS )
    {
        U2U_CLEAR_WATCHDOG();

        tmpEntryType = tmpFileEntry.EntryType;

        if( bFindFolder ) // Check directory
        {
            if( tmpEntryType != ENTRY_TYPE_DIR )
                continue;
        }
        else // Check file
        {
            if( tmpEntryType != ENTRY_TYPE_FILE)
                continue;
        }

        u8CurFileNameLen = msAPI_FCtrl_EntryGetCurrentName(u8FSEnvId, (U32)(au16CurFileName), 127);

    #if 0
        printf("%u) %s %u ", u16EntryIdx, (tmpEntryType == ENTRY_TYPE_DIR)?"D":"F",u8CurFileNameLen);
        _PrintFileName(au16CurFileName);
        printf("\n");
    #endif

        if( u8CurFileNameLen == u8TargetFileNameLen )
        {
            if( _CompareString_U8_U16(pcTargetFileName, au16CurFileName, u8TargetFileNameLen) )
            {
                printf_2(" =====> \"%s\" found!\n", pcTargetFileName);
                bFolderFound = TRUE;
                break;
            }
            else
            {
                //printf(" =====> Not Found\n");
            }
        }

        u16EntryIdx += 1;
    }

    if( FALSE == bFolderFound )
    {
        //printf("\nWarning: %s not found\n", pcTargetFileName);
        return FALSE;
    }

    *pFileEntry = tmpFileEntry;

    return TRUE;
}

BOOL msDebug_UartToUSB_CreatFile(U8 u8FSEnvId, char* pcTargetFileName, U8* pu8FileHandle)
{
    char acFileName[32];
    U16 au16FileName[32];
    int i = 0;
    int iSearchTime = 0;
    FileEntry tmpFileEntry;
    BOOL bFoundValidName = FALSE;


    if( s_U2U_bInitDone == FALSE )
        return FALSE;

    if( pcTargetFileName == NULL )
        return FALSE;

    if( strlen(pcTargetFileName) > 20 )
        return FALSE;

    // Check a valid file name ...
    for( iSearchTime = 0; iSearchTime < 1000; iSearchTime += 1 )
    {
        // Prepare filename
        sprintf(acFileName, "%s_%04u.txt", pcTargetFileName, _s_U2U_u16FileNameCount );

        _s_U2U_u16FileNameCount += 1;

        //printf("Check %s\n", acFileName);

        // Copy char array to U16 array
        for( i = 0; i < 32; ++ i )
        {
            au16FileName[i] = acFileName[i];
            if( acFileName[i] == 0 )
                break;
        }

        // Check if the file exist...
        if( msAPI_FCtrl_EntrySearchByName(u8FSEnvId, au16FileName, strlen(acFileName), &tmpFileEntry) )
        {
            //printf("%s is exist\n", acFileName);
        }
        else
        {
            //printf("%s is not exist\n", acFileName);
            bFoundValidName = TRUE;
            break;
        }
    }


    if( FALSE == bFoundValidName )
    {
        return FALSE;
    }

    // Create file
    U8 u8FileHandle = msAPI_FCtrl_FileCreate(u8FSEnvId, au16FileName, strlen(acFileName), CREATE_MODE_NEW);
    if (u8FileHandle == INVALID_FILE_HANDLE)
    {
        printf_2("\nError: Create file failed\n", 0);
        return FALSE;
    }

    printf_2("%s created\n", acFileName);

    *pu8FileHandle = u8FileHandle;

/*
    //FileEntry tmpFileEntry;
    if( FALSE == msAPI_FCtrl_EntryGetByHandle(u8FileHandle, &tmpFileEntry) )
    {
        printf_2("\nError: Get file entry failed\n", 0);
        //msDebug_UartToUSB_CloseFile();
        return FALSE;
    }
    PrintFileEntry_Id(&tmpFileEntry);
*/

    return TRUE;
}

#define U2U_ENABLE_CHECK_TIME   0

#if( U2U_ENABLE_CHECK_TIME )
    static U32 s_U2U_au32Time[10][2];
    #define U2U_SAVE_TIME_START(index)  do{s_U2U_au32Time[index][0]=MsOS_GetSystemTime();}while(0)
    #define U2U_SAVE_TIME_END(index)    do{s_U2U_au32Time[index][1]=MsOS_GetSystemTime();}while(0)
#else
    #define U2U_SAVE_TIME_START(index)
    #define U2U_SAVE_TIME_END(index)
#endif

BOOL msDebug_UartToUSB_OpenFile(void)
{
    DEBUG_U2U( printf_2("msDebug_UartToUSB_OpenFile()\n", 0); );

    U8 u8UsbPortNO = 0;
    FileEntry fFolderFileEntry;
    EnuU2ULogMode eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;
    BOOL bSearchFileResult;


    if( s_U2U_bInitDone == FALSE )
        return FALSE;


    // Close file if needed
    if( s_U2U_u8FileHandle != INVALID_FILE_HANDLE )
    {
        msDebug_UartToUSB_CloseFile();
    }

    s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;

    U2U_SAVE_TIME_START(0);
    u8UsbPortNO = msDebug_UartToUSB_OpenUSBPort();
    U2U_SAVE_TIME_END(0);
    DEBUG_U2U( printf_2("  u8UsbPortNO=%u\n", u8UsbPortNO); );
    if( 0 == u8UsbPortNO )
    {
        DEBUG_U2U( printf_2("\n Warning: Open USB port failed\n", 0); );
        return FALSE;
    }

    U2U_SAVE_TIME_START(1);
    // Init file system => Get fileEnv
    if( FALSE == msDebug_UartToUSB_InitFileSystem(u8UsbPortNO) )
    {
        printf_2("\nError: Init file system failed\n", 0);
        return FALSE;
    }
    U2U_SAVE_TIME_END(1);

    U2U_SAVE_TIME_START(2);
    // Change to root
    if( FALSE == msAPI_FCtrl_DirectoryChangeToRoot(_s_U2U_u8FileSysEnvironmentID) )
    {
        printf_2("\nError: msAPI_FCtrl_DirectoryChangeToRoot failed\n", 0);
        msDebug_UartToUSB_DeInitFileSystem();
        return FALSE;
    }
    U2U_SAVE_TIME_END(2);



    // Find folder
    U2U_SAVE_TIME_START(3);
    bSearchFileResult = msDebug_UartToUSB_SearchFile(_s_U2U_u8FileSysEnvironmentID, UART_TO_USB_FOLDER_NAME_1, TRUE, &fFolderFileEntry);
    U2U_SAVE_TIME_END(3);

    if( FALSE == bSearchFileResult )
    {
        DEBUG_U2U( printf_2("  Search %s file failed\n", UART_TO_USB_FOLDER_NAME_1); );

        U2U_SAVE_TIME_START(4);
        bSearchFileResult = msDebug_UartToUSB_SearchFile(_s_U2U_u8FileSysEnvironmentID, UART_TO_USB_FOLDER_NAME_2, TRUE, &fFolderFileEntry);
        U2U_SAVE_TIME_END(4);
        if( FALSE == bSearchFileResult )
        {
            DEBUG_U2U( printf_2("  Search %s file failed\n", UART_TO_USB_FOLDER_NAME_2); );
            msDebug_UartToUSB_DeInitFileSystem();
            return FALSE;
        }
        else
        {
            eLogMode = U2U_MODE_LOG_SAVE_TO_USB_AND_UART_ON;
            //DEBUG_U2U( printf_2("  Log save to USB and uart on\n", 0); );
            printf_2("\n===== Save log to Uart and File =====\n", 0);
        }
    }
    else
    {
        eLogMode = U2U_MODE_LOG_SAVE_TO_USB_AND_UART_OFF;
        //DEBUG_U2U( printf_2("  Log save to USB and uart off\n", 0); );
        printf_2("\n===== Save log to File only =====\n", 0);
    }


#if 0
    { // Print folder name
        U16 au16CurFileName[64];
        BOOLEAN bShortNameOnly;
        U8 u8FileLen = msAPI_FCtrl_EntryGetLongNameByFileEntry(_s_U2U_u8FileSysEnvironmentID, &fFolderFileEntry, (U32)au16CurFileName, 127, &bShortNameOnly);

        //printf("%u %u\n", bShortNameOnly, u8FileLen);
        if( !bShortNameOnly && (u8FileLen>0) )
        {
            _PrintFileName(au16CurFileName);
        }
    }
#endif

    // Change dir into ...
    if( FALSE == msAPI_FCtrl_DirectoryChange(_s_U2U_u8FileSysEnvironmentID, &fFolderFileEntry) )
    {
        printf_2("\nError: Change dir failed\n", 0);
        msDebug_UartToUSB_DeInitFileSystem();
        return FALSE;
    }


    // Create file ..., ==> get file handle
    if( FALSE == msDebug_UartToUSB_CreatFile(_s_U2U_u8FileSysEnvironmentID, UART_TO_USB_FILE_NAME, &s_U2U_u8FileHandle) )
    {
        printf_2("\nError: Create file failed\n", 0);
        msDebug_UartToUSB_DeInitFileSystem();
        return FALSE;
    }
    DEBUG_U2U( printf_2("   s_U2U_u8FileHandle=%u\n",  s_U2U_u8FileHandle); );


    // No need file env anymore
    msDebug_UartToUSB_DeInitFileSystem();


    s_U2U_u16Count_OpenFile += 1;


    // Must write some data to file for getting valid EntryId
#if 1
    { // This is the first time write to file
        // Write test ...
        char au8WriteBuf[128];

        snprintf(au8WriteBuf, 127, "File created for Saving log to USB\r\n FileNameCount=%u\r\n OpenFileCount=%u\r\n WriteFileErrCnt=%u\r\n\r\n",
            _s_U2U_u16FileNameCount,
            s_U2U_u16Count_OpenFile,
            s_U2U_u32ErrorCount_WriteFile);
        //printf_2("    strlen(au8WriteBuf)=%u\n", strlen(au8WriteBuf));
        MsOS_Dcache_Flush( (U32)au8WriteBuf, strlen(au8WriteBuf));
        MsOS_FlushMemory();
        U32 u32FileWriteResult = msAPI_FCtrl_FileWrite(s_U2U_u8FileHandle, MsOS_VA2PA((U32)au8WriteBuf), strlen(au8WriteBuf) );
        if( u32FileWriteResult != 0 )
        {
            printf_2("  u32FileWriteResult=%u\n", u32FileWriteResult);
            printf_2("\nError: msAPI_FCtrl_FileWrite() failed\n", 0);
            msDebug_UartToUSB_CloseFile();
            return FALSE;
        }
    }
#endif

    // Get FileEntry by using FileHandle
    if( FALSE == msAPI_FCtrl_EntryGetByHandle(s_U2U_u8FileHandle, &_s_U2U_FileEntry) )
    {
        printf_2("\nError: Get Entry failed\n", 0 );
        msDebug_UartToUSB_CloseFile();
        return FALSE;
    }

    DEBUG_U2U( PrintFileEntry_Id(&_s_U2U_FileEntry); );

    s_U2U_eLogMode = eLogMode;


#if 0
    { // Print file name
        U16 au16CurFileName[64];
        BOOLEAN bShortNameOnly;
        U8 u8FileLen = msAPI_FCtrl_EntryGetLongNameByFileEntry(_s_U2U_u8FileSysEnvironmentID, &_s_U2U_FileEntry, (U32)au16CurFileName, 127, &bShortNameOnly);

        //printf("%u %u\n", bShortNameOnly, u8FileLen);
        if( !bShortNameOnly && (u8FileLen>0) )
        {
            _PrintFileName(au16CurFileName);
        }
    }
#endif


#if 0
    {
        // Write test ...
        char au8WriteBuf[] = "Write test~~\r\n";

    #if 1
        msDebug_UartToUSB_FileWrite(au8WriteBuf, strlen(au8WriteBuf));
    #else
        MsOS_Dcache_Flush( (U32)au8WriteBuf, 16);
        MsOS_FlushMemory();
        U32 u32FileWriteResult = msAPI_FCtrl_FileWrite(s_U2U_u8FileHandle, MsOS_VA2PA((U32)au8WriteBuf), strlen(au8WriteBuf) );
        if( u32FileWriteResult != 0 )
        {
            printf("u32FileWriteResult=%u\n", u32FileWriteResult);
        }
    #endif
    }
#endif


#if 0 // Testing for time cal
    {
        U32 tt1, tt2;
        // Write test ...
        char au8WriteBuf[32] = "12345678901234567890\r\n";
        MsOS_Dcache_Flush( (U32)au8WriteBuf, 32);
        MsOS_FlushMemory();

        U16 u16Cnt;
        U32 u32FileWriteResult;
        printf("\nWrite test...\n");
        U8 u8TestMode;
        U32 au32WriteLen[] = {1, 2, 4,10,20,40, 100,200,400, 1000,2000, 4000, 10000, 20000, 0x10000, 0x20000};
        U32 u32WriteLen = 0;


        for( u8TestMode = 0; u8TestMode < (sizeof(au32WriteLen)/sizeof(U32) ); u8TestMode += 1 )
        {
            U2U_CLEAR_WATCHDOG();

            u32WriteLen = au32WriteLen[u8TestMode];

            tt1 = MsOS_GetSystemTime();
            for( u16Cnt = 0; u16Cnt < 10; u16Cnt += 1 )
            {
                u32FileWriteResult = msAPI_FCtrl_FileWrite(s_U2U_u8FileHandle, MsOS_VA2PA((U32)au8WriteBuf), u32WriteLen );
                if( u32FileWriteResult != 0 )
                    break;
                //printf("u32WriteLenResult=%u\n", u32WriteLenResult);
            }
            tt2 = MsOS_GetSystemTime();
            printf("Write %u done use %u\n", u32WriteLen, (tt2-tt1)/10);
        }
    }
#endif


    return TRUE;
}

BOOL msDebug_UartToUSB_CloseFile(void)
{
    DEBUG_U2U( printf_2("msDebug_UartToUSB_CloseFile()\n", 0); );

    if( s_U2U_u8FileHandle != INVALID_FILE_HANDLE )
    {
        msAPI_FCtrl_FileClose(s_U2U_u8FileHandle);
        s_U2U_u8FileHandle = INVALID_FILE_HANDLE;
    }

    return TRUE;
}

void msDebug_UartToUSB_Task(void)
{
#if 1
    static U32 _s_u32LastTime = 0;
    U32 u32CurTime;

    if( s_U2U_bInitDone == FALSE )
        return;

    if( s_U2U_bEnable == FALSE )
        return;

    u32CurTime = MsOS_GetSystemTime();

    if( msAPI_Timer_DiffTime_2(_s_u32LastTime, u32CurTime) < 2000 )
    {
        return;
    }

    _s_u32LastTime = u32CurTime;


    //printf_2(" tt=%u\n", u32CurTime);
    //printf(" t=%u\n", u32CurTime);

    if( (s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_DISABLE)
      ||(s_U2U_u8FileHandle == INVALID_FILE_HANDLE)
      )
    {
        DEBUG_U2U( printf_2(" Try to OpenFile ...\n"); );

        U32 t1 = MsOS_GetSystemTime();

        U8 u8UsbPortNO = msDebug_UartToUSB_OpenUSBPort();

        U32 t2 = MsOS_GetSystemTime();

        //DEBUG_U2U( printf_2("  u8UsbPortNO=%u\n", u8UsbPortNO); );
        if( 0 == u8UsbPortNO ) // No use connected!!
        {
            DEBUG_U2U( printf_2("\n Warning: Open USB port failed\n", 0); );
        }
        else
        {
            msDebug_UartToUSB_OpenFile();
        }

        U32 t3 = MsOS_GetSystemTime();

        U32 tt = msAPI_Timer_DiffTime_2( t1, t2 );
        if( tt > 1 )
        {
            printf_2("U2U-1 task use %u\n", tt);
        }
        tt = msAPI_Timer_DiffTime_2( t2, t3 );
        if( tt > 1 )
        {
            printf_2("U2U-2 task use %u\n", tt);
        }

    #if( U2U_ENABLE_CHECK_TIME )
        {
            U8 i;
            for( i = 0; i < 10; ++ i )
            {
                printf_2(" %u %u\n", i, msAPI_Timer_DiffTime_2(s_U2U_au32Time[i][0], s_U2U_au32Time[i][1]) );
            }
        }
    #endif
    }
    else
    {
        // Normal case ..
        //putchar('.');
    }

#endif
}

static U8 msDebug_UartToUSB_CheckFileHandle(void)
{
    if( s_U2U_bInitDone == FALSE )
        return 1; // nothing

    if( s_U2U_bEnable == FALSE )
        return 1; // nothing

    if( s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_DISABLE )
        return 1; // nothing

    if( s_U2U_u8FileHandle == INVALID_FILE_HANDLE )
        return 1; // nothing


    FileEntry tmpFileEntry;

    // Get FileEntry from FileHandle
    if( FALSE == msAPI_FCtrl_EntryGetByHandle(s_U2U_u8FileHandle, &tmpFileEntry) )
    {
        printf_2("\nError: Get Entry failed\n", 0 );
        return 2;
    }


    // Check if file entry is the same...
    //U32 time1, time2;
    //time1 = MsOS_GetSystemTime();

    //PrintFileEntry_Id(&_s_U2U_FileEntry);
    //PrintFileEntry_Id(&tmpFileEntry);

    if( FALSE == CompareFileEntry(&_s_U2U_FileEntry, &tmpFileEntry) )
    {
        printf_2("\nError: File Entry changed\n", 0 );
        return 3;
    }
    //time2 = MsOS_GetSystemTime();
    //printf_2("   Check entry use %u\n", time2-time1);

    return 0;
}

void msDebug_UartToUSB_FileWrite(char* pcBuffer, U32 u32Length)
{
    if( s_U2U_bInitDone == FALSE )
        return;

    if( s_U2U_bEnable == FALSE )
        return;

    if( s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_DISABLE )
        return;

    if( s_U2U_u8FileHandle == INVALID_FILE_HANDLE )
        return;

#if 0
    {
        U16 i;
        putchar('[');
        putchar('W');
        putchar('F');
        putchar(':');
        for( i = 0; i < u32Length; ++ i )
        {
            putchar(pcBuffer[i]);
        }
        putchar(']');
    }
#endif

    // Check file handle valid?
    if( 0 != msDebug_UartToUSB_CheckFileHandle() )
    {
        // Maybe the file handle is changed
        s_U2U_u8FileHandle = INVALID_FILE_HANDLE;
        s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;
        s_U2U_u32ErrorCount_WriteFile += 1;
        return;
    }


    MsOS_Dcache_Flush( (U32)pcBuffer, u32Length);
    MsOS_FlushMemory();
    U32 u32FileWriteResult = msAPI_FCtrl_FileWrite(s_U2U_u8FileHandle, MsOS_VA2PA((U32)pcBuffer), u32Length );
    if( u32FileWriteResult != 0 )
    {
        DEBUG_U2U( printf_2("u32FileWriteResult=%u\n", u32FileWriteResult); );
        printf_2("\nError: FileWrite failed\n", u32FileWriteResult);
        //s_U2U_u8FileHandle = INVALID_FILE_HANDLE;
        msDebug_UartToUSB_CloseFile();
        s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;
        s_U2U_u32ErrorCount_WriteFile += 1;
    }
}

void msDebug_UartToUSB_Set_Enable(BOOL bEnable)
{
    printf_2("msDebug_UartToUSB_Set_Enable(bEn=%u)\n", bEnable);

    if( s_U2U_bInitDone == FALSE )
        return;

    //if( s_U2U_bEnable == bEnable )
    //    return;

    if( bEnable )
    {
        if( (s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_DISABLE)
          ||(s_U2U_u8FileHandle == INVALID_FILE_HANDLE)
          )
        {
            if( FALSE == msDebug_UartToUSB_OpenFile() )
            {
                printf_2("\nError: Open log file failed!\n", 0);
            }
            else
            {

            }
        }
    }
    else
    {
        //if( s_U2U_eLogMode != U2U_MODE_LOG_SAVE_TO_USB_DISABLE )
        {
            s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;
            msDebug_UartToUSB_CloseFile();
        }
    }

    s_U2U_bEnable = bEnable;
}

BOOL msDebug_UartToUSB_Get_Enable(void)
{
    if( s_U2U_bInitDone == FALSE )
        return FALSE;

    return s_U2U_bEnable;
}

#if 1
// Copy from prana2
int printf(const char *fmt, ...)
{
    BOOL bToUart = FALSE;
    BOOL bToUsb = FALSE;
    int i, iret;
    char szPrint[PRINTF_CHAR_MAX];
    va_list ap;

    va_start(ap, fmt);
    iret = vsnprintf(szPrint, PRINTF_CHAR_MAX, fmt, ap);
    va_end(ap);


//    U2U_MODE_LOG_SAVE_TO_USB_DISABLE,       // Uart On, Usb Off
//    U2U_MODE_LOG_SAVE_TO_USB_AND_UART_ON,   // Uart On, Usb On
//    U2U_MODE_LOG_SAVE_TO_USB_AND_UART_OFF,  // Uart Off, Usb On


    if( (s_U2U_bEnable == FALSE)
      ||(s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_DISABLE)
      ||s_U2U_bProtectRecursive
      )
    {
        bToUart = TRUE;
        bToUsb = FALSE;
    }
    else // s_U2U_bEnable == TRUE
    {
        if( s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_AND_UART_ON )
        {
            bToUart = TRUE;
        }
        else // if( s_U2U_eLogMode == U2U_MODE_LOG_SAVE_TO_USB_AND_UART_OFF )
        {
            bToUart = FALSE;
        }
        bToUsb = TRUE;
    }


    if( bToUart )
    {
        //putchar('<');
        //putchar('<');
        for (i = 0; i < iret; i++)
        {
            putchar(szPrint[i]);
        }
        //putchar('>');
        //putchar('>');
    }

    if( bToUsb )
    {
        if( s_U2U_bProtectRecursive == FALSE )
        {
            s_U2U_bProtectRecursive = TRUE;
            msDebug_UartToUSB_FileWrite(szPrint, iret);
            s_U2U_bProtectRecursive = FALSE;
        }
    }

    return iret;
}

int puts(const char *s)
{
#if 1
    if( s )
    {
        printf("%s\r\n", s);
    }
#else
    int i;

    //putchar('[');
    //putchar('[');

    for (; (i = *s); s++)
    {
        putchar(i);
    }

    //putchar(']');
    //putchar(']');

    putchar('\n');
#endif

    return 0;
}
#endif

#endif // ENABLE_UART_MSG_TO_USB

#define DEBUG_OPEN_USB_PORT(x)  //x

U8 msDebug_OpenUSBPort(void)
{
#if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
    U8 u8PortEnStatus = 0;
    U8 u8UsbPortNO = 0;


    DEBUG_OPEN_USB_PORT( printf(" msDebug_OpenUSBPort()\n"); );

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    DEBUG_OPEN_USB_PORT( printf("  u8PortEnStatus=0x%X\n", u8PortEnStatus); );

    if( (u8PortEnStatus & BIT0) )
    {
        if( !MDrv_UsbDeviceConnect() )
        {
            //DEBUG_U2U( printf_2("\n Warning: port0 not connect!\n", 0); );
            u8UsbPortNO = 0;
        }
        else
        {
            u8UsbPortNO = 1;
        }
    }

    if( (u8PortEnStatus & BIT1) )
    {
        if(u8UsbPortNO != 1)
        {
            if (!MDrv_UsbDeviceConnect_Port2())
            {
                //DEBUG_U2U( printf_2("\n Warning: port1 not connect!\n", 0); );
                u8UsbPortNO = 0;
            }
            else
            {
                u8UsbPortNO = 2;
            }
        }
    }

    DEBUG_OPEN_USB_PORT( printf("u8UsbPortNO=%u\n", u8UsbPortNO); );

    if( u8UsbPortNO == 0 )
    {
        printf_2("\n Error: Unknown USB port\n", 0);
    }

    return u8UsbPortNO;
#else
    return 0;
#endif
}

U8 msDebug_Get_FileSysEnvironment(U8 u8UsbPortNO, U8 u8DriveID)
{
    U8 u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;


    //printf_2(" msDebug_Get_FileSysEnvironment(u8UsbPortNO=%u,u8DriveID=%u)\n", u8UsbPortNO, u8DriveID);

    if( (u8UsbPortNO != 1) && (u8UsbPortNO != 2) )
    {
        printf_2("\nError: u8UsbPortNO=%u\n", u8UsbPortNO);
        return INVALID_FS_ENVIRONMENT_INDEX;
    }

    msAPI_MSDCtrl_CheckDevices();

    if( (u8UsbPortNO == 1) || (u8UsbPortNO == 2) )
    {
        U8 u8DeviceIdx_Start, u8DeviceIdx_End;
        U8 u8DeviceIdx;

        if( u8UsbPortNO == 1 )
        {
            u8DeviceIdx_Start = MSD_USB_INDEX_START;
            u8DeviceIdx_End = MSD_USB_INDEX_START + MSD_USB_NUM;
        }
        else
        {
            u8DeviceIdx_Start = MSD_USB_2_INDEX_START;
            u8DeviceIdx_End = MSD_USB_2_INDEX_START + MSD_USB_2_NUM;
        }

        for( u8DeviceIdx = u8DeviceIdx_Start; u8DeviceIdx < u8DeviceIdx_End; u8DeviceIdx++)
        {
            EN_MSD_STATUS eMsdStatus = msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIdx);
            //printf("  Dev=%u status=%u\n", u8DeviceIdx, eMsdStatus );
            if( eMsdStatus == MSD_STATUS_INSERTED )
            {
                msAPI_FCtrl_ActiveDevice(u8DeviceIdx);
                eMsdStatus = msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIdx);
                //printf("  status=%u\n", eMsdStatus );
            }

            if( eMsdStatus == MSD_STATUS_IDLE )
            {
                u8FileSysEnvironmentID = msAPI_FSEnv_Register(u8DriveID /*'A'*/);
                //_s_U2U_bFileSystemInited = msAPI_FCtrl_DirectoryChangeToRoot(_s_U2U_u8FileSysEnvironmentID);
                //printf("  u8DeviceIdx=%u, FSEnvId=%u, init=%u\n", u8DeviceIdx, _s_U2U_u8FileSysEnvironmentID, _s_U2U_bFileSystemInited);
                if( u8FileSysEnvironmentID != INVALID_FS_ENVIRONMENT_INDEX )
                {
                    break;
                }
            }
        }
    }

    return u8FileSysEnvironmentID;
}

BOOL msDebug_CreatNewFile_ByNameAndNumberRange(U8 u8FSEnvId,
    char* pcTargetFileName, U16 u16Number_Start, U16 u16Number_End, U8* pu8FileHandle, U16* pu16NumberFound)
{
    char acFileName[32];
    U16 au16FileName[32];
    int i = 0;
    FileEntry tmpFileEntry;
    BOOL bFoundValidName = FALSE;
    U16 u16CurNumber = u16Number_Start;



    if( pcTargetFileName == NULL )
        return FALSE;

    if( strlen(pcTargetFileName) > 20 )
        return FALSE;

    // Check a valid file name ...
    for( u16CurNumber = u16Number_Start; u16CurNumber < u16Number_End; u16CurNumber += 1 )
    {
        // Prepare filename
        //sprintf(acFileName, "%s_%04u.txt", pcTargetFileName, u16CurNumber );
        snprintf(acFileName,sizeof(acFileName), "%s_%04u.txt", pcTargetFileName, u16CurNumber );
        //printf("Check %s\n", acFileName);

        // Copy char array to U16 array
        for( i = 0; i < 32; ++ i )
        {
            au16FileName[i] = acFileName[i];
            if( acFileName[i] == 0 )
                break;
        }

        // Check if the file exist...
        if( msAPI_FCtrl_EntrySearchByName(u8FSEnvId, au16FileName, strlen(acFileName), &tmpFileEntry) )
        {
            //printf("%s is exist\n", acFileName);
        }
        else
        {
            //printf("%s is not exist\n", acFileName);
            bFoundValidName = TRUE;
            break;
        }
    }

    if( FALSE == bFoundValidName )
    {
        return FALSE;
    }

    // Create file
    U8 u8FileHandle = msAPI_FCtrl_FileCreate(u8FSEnvId, au16FileName, strlen(acFileName), CREATE_MODE_NEW);
    if( u8FileHandle == INVALID_FILE_HANDLE )
    {
        printf_2("\nError: Create file failed\n", 0);
        return FALSE;
    }

    printf_2("%s created\n", acFileName);

    *pu8FileHandle = u8FileHandle;
    *pu16NumberFound = u16CurNumber;

/*
    //FileEntry tmpFileEntry;
    if( FALSE == msAPI_FCtrl_EntryGetByHandle(u8FileHandle, &tmpFileEntry) )
    {
        printf_2("\nError: Get file entry failed\n", 0);
        //msDebug_UartToUSB_CloseFile();
        return FALSE;
    }
    PrintFileEntry_Id(&tmpFileEntry);
*/

    return TRUE;
}

#if( ENABLE_DBG_SAVE_USB )

#define DEBUG_SAVE_USB(x)   x

U8 msDebug_OpenFile(char* pcFileName)
{
    printf("msDebug_OpenFile(%s)\n", pcFileName);

    // Open USB port
    U8 u8UsbPortNO = msDebug_OpenUSBPort();
    DEBUG_SAVE_USB( printf("  u8UsbPortNO=%u\n", u8UsbPortNO); );
    if( 0 == u8UsbPortNO )
    {
        printf("\n Error: Open USB port failed\n");
        return INVALID_FILE_HANDLE;
    }

    // Get first partition file env ...
    U8 u8FileSysEnvironmentID = msDebug_Get_FileSysEnvironment( u8UsbPortNO, 0);
    if( u8FileSysEnvironmentID == INVALID_FS_ENVIRONMENT_INDEX )
    {
        printf("\n Error: Get file environment failed\n");
        return INVALID_FILE_HANDLE;
    }

    // Change to root
    if( FALSE == msAPI_FCtrl_DirectoryChangeToRoot(u8FileSysEnvironmentID) )
    {
        printf_2("\nError: msAPI_FCtrl_DirectoryChangeToRoot failed\n", 0);
        msAPI_FSEnv_UnRegister(u8FileSysEnvironmentID);
        return INVALID_FILE_HANDLE;
    }

    static U32 _s_u32SearchFileNumberStart = 0;
    U8 u8FileHandle = INVALID_FILE_HANDLE;
    U16 u16NumberFound = 0;

    // Open new file, get file handle
    if( FALSE == msDebug_CreatNewFile_ByNameAndNumberRange(u8FileSysEnvironmentID,
        pcFileName, _s_u32SearchFileNumberStart, _s_u32SearchFileNumberStart+1000, &u8FileHandle, &u16NumberFound) )
    {
        printf_2("\nError: Create new file failed(start=%u)\n", _s_u32SearchFileNumberStart);
        msAPI_FSEnv_UnRegister(u8FileSysEnvironmentID);
        return INVALID_FILE_HANDLE;
    }

    _s_u32SearchFileNumberStart = u16NumberFound + 1;

    // Not need file-env any more
    msAPI_FSEnv_UnRegister(u8FileSysEnvironmentID);

    return u8FileHandle;
}

BOOL msDebug_WriteBufferToFile(U8 u8FileHandle, U8* pu8WriteBuf, U32 u32WriteSize)
{
    DEBUG_SAVE_USB( printf_2(" msDebug_LogFile_WriteBufferToFile(size=%u)\r\n", u32WriteSize); );

    MsOS_Dcache_Flush( (U32)pu8WriteBuf, u32WriteSize);
    MsOS_FlushMemory();

    U32 u32FileWriteResult = msAPI_FCtrl_FileWrite(u8FileHandle, MsOS_VA2PA((U32)pu8WriteBuf), u32WriteSize );
    if( u32FileWriteResult != 0 )
    {
        printf_2("  u32FileWriteResult=%u\n", u32FileWriteResult);
        printf_2("\nError: msAPI_FCtrl_FileWrite() failed\n", 0);
        return FALSE;
    }

    return TRUE;
}

BOOL msDebug_SaveDataToUSB(char* pcFileName, U8* pu8Data, U32 u32DataSize)
{
    printf("msDebug_SaveDataToUSB(%s, u32DataSize=%u)\n", pcFileName, u32DataSize);

    U8 u8FileHandle = msDebug_OpenFile(pcFileName);

    if( u8FileHandle == INVALID_FILE_HANDLE )
        return FALSE;

    msDebug_WriteBufferToFile( u8FileHandle, pu8Data, u32DataSize);

    printf("Write data finished\n");

    msAPI_FCtrl_FileClose(u8FileHandle);

    return TRUE;
}

#endif


#if(ENABLE_LOG_TO_FILE)

#define DEBUG_LOGFILE(x)    //x

#define LOG_FILE_CONTENT_ALSO_PRINT_IN_UART 1

#define LOG_FILE_PRE_NAME   "msDebugLog"

static BOOL s_LogFile_bContentAlsoPrintInUart = LOG_FILE_CONTENT_ALSO_PRINT_IN_UART;
static U8 s_LogFile_u8FileHandle = INVALID_FILE_HANDLE;

#define LOG_FILE_TMP_BUF_SIZE   512
static U8 s_LogFile_au8TmpBuffer[LOG_FILE_TMP_BUF_SIZE];
static U16 s_LogFile_u16TmpBuffer_Count = 0;

void PrintBuf(char* pcWriteBuf, U32 u32WriteSize)
{
    U32 i;

    for( i = 0; i < u32WriteSize; i += 1 )
    {
        if( pcWriteBuf[i] )
            putchar(pcWriteBuf[i]);
        else
            printf_2("(%u)", pcWriteBuf[i]);
    }
}

static BOOL msDebug_LogFile_WriteBufferToFile(U8 u8FileHandle, char* pcWriteBuf, U32 u32WriteSize)
{
    if( s_LogFile_bContentAlsoPrintInUart )
    {
        //printf_2(" [msDebug_LogFile_WriteBufferToFile(size=%u)] ", u32WriteSize);
        PrintBuf(pcWriteBuf, u32WriteSize);
    }
    else
    {
        DEBUG_LOGFILE( printf_2(" msDebug_LogFile_WriteBufferToFile(size=%u)\r\n", u32WriteSize); );
    }

    MsOS_Dcache_Flush( (U32)pcWriteBuf, u32WriteSize);
    MsOS_FlushMemory();

    U32 u32FileWriteResult = msAPI_FCtrl_FileWrite(u8FileHandle, MsOS_VA2PA((U32)pcWriteBuf), u32WriteSize );
    if( u32FileWriteResult != 0 )
    {
        printf_2("  u32FileWriteResult=%u\n", u32FileWriteResult);
        printf_2("\nError: msAPI_FCtrl_FileWrite() failed\n", 0);
        return FALSE;
    }

    return TRUE;
}

#if 0
BOOL msDebug_LogFile_WriteFormatToFile(U8 u8FileHandle, const char *fmt, ...)
{
    int i, iret;
    char szPrint[PRINTF_CHAR_MAX];
    va_list ap;

    va_start(ap, fmt);
    iret = vsnprintf(szPrint, PRINTF_CHAR_MAX, fmt, ap);
    va_end(ap);

    /*for (i = 0; i < iret; i++)
    {
        putchar(szPrint[i]);
    }*/


    if( s_LogFile_bUartDebugEn )
    {
        PrintBuf(szPrint, iret);
    }

    MsOS_Dcache_Flush( (U32)szPrint, iret);
    MsOS_FlushMemory();

    U32 u32FileWriteResult = msAPI_FCtrl_FileWrite(u8FileHandle, MsOS_VA2PA((U32)szPrint), iret );
    if( u32FileWriteResult != 0 )
    {
        return FALSE;
    }

    return TRUE;
    //return iret;
}
#endif

U16 msDebug_LogFile_TmpBufToFile(void)
{
    if( INVALID_FILE_HANDLE == s_LogFile_u8FileHandle )
        return 0;

    U16 u16WriteCount = s_LogFile_u16TmpBuffer_Count;
    s_LogFile_u16TmpBuffer_Count = 0;

    if( FALSE == msDebug_LogFile_WriteBufferToFile(s_LogFile_u8FileHandle, (char*)s_LogFile_au8TmpBuffer, u16WriteCount ) )
    {
        return 0;
    }

    return u16WriteCount;
}

BOOL msDebug_LogFile_WriteBufferToTmpBuf(char* pcBuffer, U32 u32BufSize)
{
    U32 i;


    for( i = 0; i < u32BufSize; i += 1 )
    {
        if( s_LogFile_u16TmpBuffer_Count < LOG_FILE_TMP_BUF_SIZE )
        {
            s_LogFile_au8TmpBuffer[s_LogFile_u16TmpBuffer_Count] = pcBuffer[i];
            s_LogFile_u16TmpBuffer_Count += 1;
        }

        // If buffer full, write to file
        if( s_LogFile_u16TmpBuffer_Count >= LOG_FILE_TMP_BUF_SIZE )
        {
            if( 0 == msDebug_LogFile_TmpBufToFile() )
                return FALSE;
        }
    }

    return TRUE;
}

BOOL msDebug_LogFile_WriteFormatToTmpBuf(const char *fmt, ...)
{
    int iret;
    char szPrint[PRINTF_CHAR_MAX];
    va_list ap;

    va_start(ap, fmt);
    iret = vsnprintf(szPrint, PRINTF_CHAR_MAX, fmt, ap);
    va_end(ap);

    /*for (i = 0; i < iret; i++)
    {
        putchar(szPrint[i]);
    }*/


    return msDebug_LogFile_WriteBufferToTmpBuf(szPrint, iret);
}

MS_U16  MApi_XC_R2BYTE(MS_U32 u32Reg);

#define LOG_FILE_BANK_TYPE_GEN      0
#define LOG_FILE_BANK_TYPE_SCALER   1

BOOL msDebug_LogFile_GenBankInfo(U8 u8BankType, U32 u32Bank )
{
    BOOL bWriteRtn;
    U16 u16Reg;
    U32 u32FinalReg;
    U16 u16RegValue;


    if( u8BankType == LOG_FILE_BANK_TYPE_GEN )
    {
        bWriteRtn = msDebug_LogFile_WriteFormatToTmpBuf( "  ----- Bank %X -----\r\n", u32Bank);
    }
    else if( u8BankType == LOG_FILE_BANK_TYPE_SCALER )
    {
        bWriteRtn = msDebug_LogFile_WriteFormatToTmpBuf( "  ----- Scaler Bank %X -----\r\n", u32Bank);
    }
    else
    {
        return FALSE;
    }

    if( bWriteRtn == FALSE )
        return FALSE;


    if( FALSE == msDebug_LogFile_WriteFormatToTmpBuf( "    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n  -------------------------------------------------\r\n") )
    {
        return FALSE;
    }

    for( u16Reg = 0; u16Reg < 256; u16Reg += 2 )
    {
        if( (u16Reg%16) == 0 )
        {
            msDebug_LogFile_WriteFormatToTmpBuf( "%02X|", u16Reg );
        }

        if( u8BankType == LOG_FILE_BANK_TYPE_SCALER )
        {
        #if 0 // Use utopia driver
            u32FinalReg = (u32Bank<<8) + u16Reg;
            u16RegValue = MApi_XC_R2BYTE(u32FinalReg);
        #else
            u32FinalReg = 0x130000 + (u32Bank<<8) + u16Reg;
            u16RegValue = MDrv_Read2Byte(u32FinalReg);
        #endif
        }
        else if( u8BankType == LOG_FILE_BANK_TYPE_GEN )
        {
            u32FinalReg = (u32Bank<<8) + u16Reg;
            u16RegValue = MDrv_Read2Byte(u32FinalReg);
        }
        else
        {
            u16RegValue = 0xFF;
        }

        if( FALSE == msDebug_LogFile_WriteFormatToTmpBuf(" %02X %02X", u16RegValue&0xFF, u16RegValue>>8) )
        {
            return FALSE;
        }

        if( (u16Reg%16) == 14 )
        {
            msDebug_LogFile_WriteFormatToTmpBuf("\r\n");
        }

    }

    if( FALSE == msDebug_LogFile_WriteFormatToTmpBuf( "\r\n") )
    {
        return FALSE;
    }

    return TRUE;
}

static BOOL msDebug_LogFile_WriteInfo(void)
{
    U16 u16BankIdx;
    U32 u32RegBank;
    //U16 u16Reg;
    //U32 u32FinalReg;
    //16 u16Tmp;



    if( FALSE == msDebug_LogFile_WriteFormatToTmpBuf( "MStar log file:\r\n") )
    {
        return FALSE;
    }


    // Dump XC register ...
    msDebug_LogFile_WriteFormatToTmpBuf( "===== Scaler Reg =====\r\n");

    U32 au32ScalerRegBank[] = { 0x01, 0x02, 0x12, 0x23 };

    for( u16BankIdx = 0; u16BankIdx < (sizeof(au32ScalerRegBank)/sizeof(U32)); u16BankIdx += 1 )
    {
        u32RegBank = au32ScalerRegBank[u16BankIdx];

        if( FALSE == msDebug_LogFile_GenBankInfo(LOG_FILE_BANK_TYPE_SCALER, u32RegBank) )
        {
            return FALSE;
        }
    }


    U32 au32RegBank[] = { 0x1035, 0x1036 };

    // Dump register ...
    msDebug_LogFile_WriteFormatToTmpBuf( "===== Reg =====\r\n");

    for( u16BankIdx = 0; u16BankIdx < (sizeof(au32RegBank)/sizeof(U32)); u16BankIdx += 1 )
    {
        u32RegBank = au32RegBank[u16BankIdx];

        if( FALSE == msDebug_LogFile_GenBankInfo(LOG_FILE_BANK_TYPE_GEN, u32RegBank) )
        {
            return FALSE;
        }
    }


    msDebug_LogFile_TmpBufToFile();


    return TRUE;
}

EnuLogFileErrCode msDebug_LogFile_GenFileAndWriteInfo(void)
{
    U8 u8UsbPortNO = 0;
    U8 u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;
    U8 u8FileHandle = INVALID_FILE_HANDLE;
    U16 u16NumberFound = 0;
    static U32 _s_u32SearchFileNumberStart = 0;


    DEBUG_LOGFILE( printf_2("  msDebug_WriteInfoToFile()\n"); );

    // Open USB port
    u8UsbPortNO = msDebug_OpenUSBPort();
    DEBUG_LOGFILE( printf_2("  u8UsbPortNO=%u\n", u8UsbPortNO); );
    if( 0 == u8UsbPortNO )
    {
        printf_2("\n Error: Open USB port failed\n", 0);
        return E_LOG_FILE_ERR_OPEN_USB_FAILED;
    }


    // Get first partition file env ...
    u8FileSysEnvironmentID =  msDebug_Get_FileSysEnvironment( u8UsbPortNO, 0);
    if( u8FileSysEnvironmentID == INVALID_FS_ENVIRONMENT_INDEX )
    {
        printf_2("\n Error: Get file environment failed\n", 0);
        return E_LOG_FILE_ERR_GET_FILE_ENV_FAILED;
    }

    // Change to root
    if( FALSE == msAPI_FCtrl_DirectoryChangeToRoot(u8FileSysEnvironmentID) )
    {
        printf_2("\nError: msAPI_FCtrl_DirectoryChangeToRoot failed\n", 0);
        msAPI_FSEnv_UnRegister(u8FileSysEnvironmentID);
        return E_LOG_FILE_ERR_CHANGE_DIR_FAILED;
    }

    // Open new file, get file handle
    if( FALSE == msDebug_CreatNewFile_ByNameAndNumberRange(u8FileSysEnvironmentID,
        LOG_FILE_PRE_NAME, _s_u32SearchFileNumberStart, _s_u32SearchFileNumberStart+1000, &u8FileHandle, &u16NumberFound) )
    {
        printf_2("\nError: Create new file failed(start=%u)\n", _s_u32SearchFileNumberStart);
        msAPI_FSEnv_UnRegister(u8FileSysEnvironmentID);
        return E_LOG_FILE_ERR_CREATE_NEW_FILE_FAILED;
    }

    _s_u32SearchFileNumberStart = u16NumberFound + 1;

    // Not need file-env any more
    msAPI_FSEnv_UnRegister(u8FileSysEnvironmentID);


    s_LogFile_u8FileHandle = u8FileHandle;
    // Write data to log file ...
    if( FALSE == msDebug_LogFile_WriteInfo() )
    {
        printf_2("\nError: Write file failed\n", 0);
        msAPI_FCtrl_FileClose(u8FileHandle);
        return E_LOG_FILE_ERR_WRITE_FILE_FAILED;
    }

    printf("Write log file finished\n");

    msAPI_FCtrl_FileClose(u8FileHandle);
    u8FileHandle = INVALID_FILE_HANDLE;
    s_LogFile_u8FileHandle = INVALID_FILE_HANDLE;

    return E_LOG_FILE_OK;
}

#endif

#if defined(__aeon__)
void Print_R2_SPR_PICMR(U32 u32, const char* pcStr)
{
    U32 u32SPR_Val;

    printf(" %u, ", u32);

    if( pcStr )
    {
        printf(" %s ", pcStr);
    }

    printf("\n");

    u32SPR_Val = mfspr(SPR_PICMR);
    printf("  SPR_PICMR=0x%X\n", u32SPR_Val);
}
#endif

void Print_Buffer(U8* pu8Buf, U32 u32Size )
{
    U32 i;

    printf("\n==========  Memory %u(0x%X)  ==========\n", (U32)pu8Buf, (U32)pu8Buf);

    for( i = 0; i < u32Size; ++ i )
    {
        if( (i % 16) == 0 )
        {
            printf("%X(%02X) : ", ((U32)pu8Buf)+i, i);
        }

        printf("%02X ", pu8Buf[i]);

        if( (i % 16) == 15 )
        {
            printf("\n");
        }
    }

    printf("\n--------------------------------------------------\n");

}

//********************************************************************************************
// Set the the colors and attributes of Uart debug massage displayed on the screen.
//
// Parameter:
//    - u8FontColor : Text attributes or Font Foreground color or Font Background color.
//    0       :  Reset / Normal.
//    1       :  Bold or increased intensity.
//    4       :  Underline: Single.
//    30-37 : Set text color (foreground).
//    40-37 : Set background color (Background).
//********************************************************************************************
void msDebug_ANSI_SetColorText(U8 u8FontColor)
{
#if( ENABLE_UART_MSG_COLOR )
    printf("\033[%dm", u8FontColor);
#else
    UNUSED( u8FontColor );
#endif
}

void msDebug_ANSI_SetColorText_2(U8 u8FontColor, U8 u8BGColor)
{
#if( ENABLE_UART_MSG_COLOR )
    printf("\033[%d;%dm", u8FontColor, u8BGColor);
#else
    UNUSED( u8FontColor );
    UNUSED( u8BGColor );
#endif
}

void msDebug_ANSI_AllAttrOffText(void)
{
#if( ENABLE_UART_MSG_COLOR )
    printf("\033[0m \n");
#else
    printf(" \n");
#endif
}

#if( defined(__mips__) )

BOOLEAN msDebug_Mips_Is_RA_Valid(U32 u32RA)
{
    extern U8  _readonly_start[];
    extern U8  _readonly_end[];

    if( ((unsigned long)u32RA < (unsigned long)_readonly_start)
      ||((unsigned long)u32RA > (unsigned long)_readonly_end)
      )
    {
        return FALSE;
    }

    return TRUE;
}

#define MIPS_BT_DEPTH_MAX       20  // Only print out depth 20 call stack
#define MIPS_BT_CMD_ADDR2LINE   "aeon-addr2line"
void msDebug_mips_BackTrace(MS_U32 pHalReg)
{
    unsigned long *addr;
    unsigned long *ra;
    unsigned long *sp;

    unsigned short ra_offset;
    unsigned short stack_size;

    U32 u32RA_1st;
    unsigned long * pu32SP_1st;


    u32RA_1st = (U32)(((MHAL_SavedRegisters *) pHalReg)->d[31]);
    pu32SP_1st = (unsigned long *)(((MHAL_SavedRegisters *) pHalReg)->d[29]);

    ra = (unsigned long *)u32RA_1st;
    sp = pu32SP_1st;

    printf("=================================================\n");
    printf("MIPS stack backtrace\n");

    printf("pc = %08lx\n", ((MHAL_SavedRegisters *) pHalReg)->pc);
    printf("#stack frame #0: ra = %08lx, sp = %08lx\n", u32RA_1st, (unsigned long)pu32SP_1st);

    if( FALSE == msDebug_Mips_Is_RA_Valid( u32RA_1st ) )
    {
        return;
    }

    unsigned short depth;

    // Stop when *sp = 0xDEADBEEF (0xDEADBEEF is set in the head stack memory)
    ra = (unsigned long *)u32RA_1st;
    sp = pu32SP_1st;
    for (depth = 0; (depth < MIPS_BT_DEPTH_MAX) && (*sp != 0xDEADBEEF); ++depth)
    {
        ra_offset = 0;
        stack_size = 0;

        for( addr = ra; !ra_offset || !stack_size; --addr)
        {
            switch(*addr & 0xffff0000)
            {
                case 0x27bd0000: // 0x27bdxxxx: addiu sp, sp, xxxx
                    stack_size = abs((short)(*addr & 0xffff));
                    break;
                case 0xafbf0000: // 0xafbfxxxx: sw ra ,xxxx(sp)
                    ra_offset = (unsigned short)(*addr & 0xffff);
                    break;
                default:
                    break;
            }
        }

        ra = *(unsigned long **)((unsigned long)sp + (unsigned long)ra_offset);
        sp = (unsigned long *)((unsigned long)sp + (unsigned long)stack_size);

        printf("#stack frame #%d: ra = %08lx, sp = %08lx\n", depth+1, (unsigned long)ra, (unsigned long)sp);
        //printf(" %s -e AP.elf -f 0x%x\n", MIPS_BT_CMD_ADDR2LINE,  ra);

        if( FALSE == msDebug_Mips_Is_RA_Valid((U32)ra) )
        {
            printf("!!wrong ra!! Try again\n");
            break;
        }
    }

    printf("===================================================\n");

    printf(" %s -e AP.elf -f 0x%x\n", MIPS_BT_CMD_ADDR2LINE, u32RA_1st);

    ra = (unsigned long *)u32RA_1st;
    sp = pu32SP_1st;

    // Stop when *sp = 0xDEADBEEF (0xDEADBEEF is set in the head stack memory)
    for (depth = 0; (depth < MIPS_BT_DEPTH_MAX) && (*sp != 0xDEADBEEF); ++depth)
    {
        ra_offset = 0;
        stack_size = 0;

        for (addr = ra; !ra_offset || !stack_size; --addr)
        {
            switch(*addr & 0xffff0000)
            {
                case 0x27bd0000: // 0x27bdxxxx: addiu sp, sp, xxxx
                    stack_size = abs((short)(*addr & 0xffff));
                    break;
                case 0xafbf0000: // 0xafbfxxxx: sw ra ,xxxx(sp)
                    ra_offset = (unsigned short)(*addr & 0xffff);
                    break;
                default:
                    break;
            }
        }

        ra = *(unsigned long **)((unsigned long)sp + (unsigned long)ra_offset);
        sp = (unsigned long *)((unsigned long)sp + (unsigned long)stack_size);

        printf(" %s -e AP.elf -f 0x%x\n", MIPS_BT_CMD_ADDR2LINE,  ra);

        if( FALSE == msDebug_Mips_Is_RA_Valid((U32)ra) )
        {
            printf("!!wrong ra!! Try again\n");
            break;
        }
    }

}

void mips_Exception_Handler(MHAL_SavedRegisters *regs, MS_U32 vector)
{
    printf("mips_Exception_Handler(vector=%u)\n", vector);
    //vector=vector;
    msDebug_mips_BackTrace((U32)regs);

    MDrv_Sys_StopCpu(1);
}
#endif

#ifdef __arm__
unsigned long ARM_Get_FP(void)
{
    unsigned long fp = 0;
    __asm__(
        " mov %0,fp\n\t"
        : "=r" (fp)
        :
        :
        );

    return fp;
}

void msDebug_ARM_BackTrace(MS_U32 pHalReg)
{
    printf("===========================================================\n");
    printf("msDebug_ARM_BackTrace(%X)\n", pHalReg);

    unsigned long topfp = ARM_Get_FP();
    int cnt = 0;

    printf("topfp= %X\n", topfp);

    if( topfp == 0 )
    {
        printf("No back trace : FramePoint is NULL\n");
        return;
    }

    U32 u32CurFP = topfp;

    {
        printf("backtrace_dump begin:\n");
        while(cnt < 20)
        {
            long fp = *(((long*)u32CurFP) -3);
            long lr = *(((long*)u32CurFP) -1);
            u32CurFP = fp;
            if((fp == 0) ||(lr == 0))
            {
                printf("Frame:#%d , unknow address :lr = 0x%x , fp = %x \n", cnt,lr,fp);
                break;
            }
            else
            {
                printf("Frame:#%d , address :lr = %x , fp = %x \n", cnt, lr, fp);
                //printf(" aeon-addr2line -e AP.elf -f 0x%x\n", lr);
            }

            cnt++;
        }
        printf("backtrace_dump done. cnt = %d \n",cnt);
    }


    printf("-----------------------------------------------------------------\n");

    {
        u32CurFP = topfp;
        while(cnt < 20)
        {
            long fp = *(((long*)u32CurFP) -3);
            long lr = *(((long*)u32CurFP) -1);
            u32CurFP = fp;
            if((fp == 0) ||(lr == 0))
            {
                //printf("Frame:#%d , unknow address :lr = 0x%x , fp = %x \n", cnt,lr,fp);
                break;
            }
            else
            {
                //printf("# Frame:#%d , address :lr = %x , fp = %x \n", cnt, lr, fp);
                printf(" arm-none-eabi-addr2line -e AP.elf -f 0x%x\n", (unsigned int)lr);
            }
            cnt++;
        }
    }


//=======================================================================
#if 0
    U8 i;
    for( i = 0; i < 18; ++ i)
    {
        printf("%u) %08X\n", i, g_ARM_au32Regs[i]);
    }
#endif
//=======================================================================
    //unsigned long *ra;
    //unsigned long *sp;
    //printf("pc = %08lx\n", ((MHAL_SavedRegisters *) pHalReg)->pc);
    //ra = (unsigned long *)(((MHAL_SavedRegisters *) pHalReg)->d[31]);
    //sp = (unsigned long *)(((MHAL_SavedRegisters *) pHalReg)->d[29]);
    //printf("#stack frame #0: ra = %08lx, sp = %08lx\n", (unsigned long)ra, (unsigned long)sp);
//=======================================================================

    //return cnt;
}

#endif


// MsOS_DelayTask() will call this function frist
// Then get this function return value, and delay
#if ( ENABLE_DEBUG_DELAY_TIME )
static U32 s_MsDebug_u32TotalDelay = 0;
#endif

MS_U32 MsOS_DelayTask_Debug(MS_U32 u32Ms)
{
#if (ENABLE_DEBUG_DELAY_TIME)
    s_MsDebug_u32TotalDelay += u32Ms;

    BOOL bPrintDelayTime = TRUE;

  #if ( ENABLE_DEBUG_DELAY_ID )

    if( (g_Timer_eCurDelayId == E_DELAY_ID_WAIT_POWER_ON_MUSIC_DONE)
     //|| (g_Timer_eCurDelayId == E_DELAY_ID_API_TIMER_DELAY)
      )
    {
        bPrintDelayTime = FALSE;
    }

    if( bPrintDelayTime )
    {
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        if( g_Timer_eCurDelayId == E_DELAY_ID_UNKNOWN )
            msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);
        else
            msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_PURPLE);

        //printf("[Delay %u/%u]", u32Ms, s_MsDebug_u32TotalDelay);
        printf("[%u Delay %u/%u]", g_Timer_eCurDelayId, u32Ms, s_MsDebug_u32TotalDelay );

        msDebug_ANSI_AllAttrOffText(); // Color off
        //printf(ANSI_COLOR_OFF_STR); // Color off
    }

  #else


  #if(ENABLE_DTV)
    if( msAPI_DTV_Comm_IsInDTVScan() )
    {
        bPrintDelayTime = FALSE;
    }
  #endif

    if( u32Ms < 20 )
    {
        bPrintDelayTime = FALSE;
    }

    if( bPrintDelayTime )
    {
        printf("[Delay %u]", u32Ms);
    }

  #endif

#endif

    return u32Ms;
}

BOOL msDebug_CheckPoint(void)
{
/*
    U8 u8Tmp = MDrv_ReadByte(0x101eF9);

    if( (u8Tmp&1) == 0 )
    {
        printf("0x101eF9=%X\n", u8Tmp);
        return 1;
    }
    */

    return FALSE;
}

// R2/Aeon:
// TODO
// MIPS:
// TODO
// ARM:
// MIU0:     cache: 20000000 ~ 2FFFFFFF
// MIU0: non-cache: 60000000 ~ 6FFFFFFF
// MIU1:     cache: A0000000 ~ A7FFFFFF
// MIU1: non-cache: C0000000 ~ C7FFFFFF
U32 msDebug_PA2VA(U32 u32PA)
{
    U32 u32VA = 0;

    if( u32PA > (0x100000*128) )
    {
        printf("\nError: u32PA=0x%X\n", u32PA);
    }

    u32VA = MsOS_PA2KSEG1(u32PA);

    if( (u32VA >= (0x80000000|(0x100000*128)))
      ||(u32VA < (0x80000000))
      )
    {
        printf("\nError: u32VA=0x%X\n", u32VA);
    }

    return u32VA;
}

#define FATAL_ERR_MSG_DELAY     3000

void msDebug_FatalErrorHandler_Para_2(U32 u32Id, U32 u32Para, U32 u32Para2)
{
    //msDebug_ANSI_SetColorText(E_FONT_COLOR_RED);
    //msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW);

    printf("\n");

    msDebug_ANSI_SetColorText(E_FONT_COLOR_YELLOW);
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_RED);

    printf("Fatal Error: ID=%u, Para=%u(0x%X), para2=%u(0x%X), happen at %u\n", u32Id, u32Para, u32Para, u32Para2, u32Para2, MsOS_GetSystemTime());

#if(ENABLE_DVB)
    if( FATAL_ERR_ID_SI_LIB_STRUCTURE_SIZE_ERROR == u32Id )
    {
        printf(" => SI lib structure size is wrong!\n");
    }
#endif

    msAPI_Timer_Delayms(FATAL_ERR_MSG_DELAY);

    msDebug_ANSI_AllAttrOffText();
}

void msDebug_FatalErrorHandler(U32 u32Id, U32 u32Para)
{
    msDebug_FatalErrorHandler_Para_2( u32Id, u32Para, 0);
}


#if(DEBUG_CHG_SRC_TIME)

#define CHG_SRC_LOG_GROUP   0
void msDebug_PrintChgSrcTime(char* pStr)
{
    static U32 s_u32LastTime = 0;

#if(ENABLE_LOG_FILE_IN_MEM)
    U32 u32CurTime = MsOS_GetSystemTime();

    //Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, "\033[%dm\033[%dm", E_FONT_COLOR_WHITE, E_FONT_BACKGROUND_COLOR_BLUE);

    Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, "[ChgSrc] ");

    if( pStr )
    {
        Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, "%s", pStr);
    }

    Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, " at %u(%u)", g_Debug_u32Time_ChangeSrc, u32CurTime );
    //Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, "(%u)", u32CurTime );

    if( g_Debug_u32Time_ChangeSrc > 1 )
    {
        Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, " diff=%u\n", u32CurTime-s_u32LastTime );
    }
    else
    {
        Debug_Log_MemPrintf(CHG_SRC_LOG_GROUP, "\n" );
    }

#else

  #if( ENABLE_UART_MSG_COLOR )
    msDebug_ANSI_SetColorText(E_FONT_COLOR_WHITE);
    msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_BLUE);
  #else
    printf(">>>>>>>>");
  #endif

    printf("[ChgSrc] ");

    if( pStr )
    {
        printf("%s", pStr);
    }

    printf(" at %u(%u) diff=%u %s\n", g_Debug_u32Time_ChangeSrc,
            MsOS_GetSystemTime(), MsOS_GetSystemTime()-s_u32LastTime,
            ANSI_COLOR_OFF_STR );

#endif

    s_u32LastTime = MsOS_GetSystemTime();

}
#endif

static U8 g_Dbg_u8FuncDeep = 0;
void msDebugFuncTime_PrintPreStr(U8 u8Flag)
{
    if(u8Flag)
    {
        g_Dbg_u8FuncDeep += 1;
    }

#if(ENABLE_LOG_FILE_IN_MEM)
    //Debug_Log_MemPrintf(LOG_MEM_GROUP_BOOT, "\n");
#else
    printf("\n");
#endif

    U8 i;

    for( i = 0; i < g_Dbg_u8FuncDeep; ++ i )
    {
    #if(ENABLE_LOG_FILE_IN_MEM)
        //Debug_Log_MemPrintf(LOG_MEM_GROUP_BOOT, ">");
        Debug_Log_PutCharInMem(LOG_MEM_GROUP_BOOT, '>', FALSE);
    #else
        printf(">");
    #endif
    }

#if(ENABLE_LOG_FILE_IN_MEM)
    Debug_Log_MemPrintf(LOG_MEM_GROUP_BOOT, "[Boot] ");
#else
    printf("[Boot] ");
#endif

    if(u8Flag)
    {
    }
    else
    {
        g_Dbg_u8FuncDeep -= 1;
    }

}

#if(ENABLE_CHECK_MEMORY_CHANGE)

static U32 s_CheckMemChg_u32MemAddr = 0;
static U32 s_CheckMemChg_u32Size = 0;
static U32 s_CheckMemChg_u32CRC = 0;

U32 msDebug_CheckMemChg_CalCrc(void)
{
    if( s_CheckMemChg_u32Size == 0 )
        return 0;

    //return MDrv_BDMA_CRC32(s_CheckMemChg_u32MemAddr, s_CheckMemChg_u32Size, BDMA_CRC32_POLY, BDMA_CRC_SEED_0, E_BDMA_SRCDEV_MIU0, FALSE);
    return msAPI_CRC_Cal( (U8*)MsOS_PA2KSEG0(s_CheckMemChg_u32MemAddr), s_CheckMemChg_u32Size);
}

void msDebug_CheckMemChg_Init(U32 u32MemAddr, U32 u32Size)
{
    PRINT_CURRENT_LINE();
    printf(" msDebug_CheckMemChg_Init(0x%X,0x%X)\n", u32MemAddr, u32Size);

    s_CheckMemChg_u32MemAddr = u32MemAddr;
    s_CheckMemChg_u32Size = u32Size;

    if( s_CheckMemChg_u32Size )
    {
        s_CheckMemChg_u32CRC = msDebug_CheckMemChg_CalCrc();
        printf(" s_CheckMemChg_u32CRC=0x%X\n", s_CheckMemChg_u32CRC);
    }
}

BOOLEAN msDebug_CheckMemChg_Check(U32 u32Flag)
{
    if( s_CheckMemChg_u32Size )
    {
        U32 u32CrcTmp = msDebug_CheckMemChg_CalCrc();
        //PRINT_CURRENT_LINE();
        //printf(" u32CrcTmp=0x%X\n", u32CrcTmp);
        if( u32CrcTmp != s_CheckMemChg_u32CRC )
        {
            msDebug_ANSI_SetColorText_2(E_FONT_COLOR_BLACK, E_FONT_BACKGROUND_COLOR_RED);
            printf("\nError: CheckMemChg: Memory changed! (%u)\n", u32Flag);
            msDebug_ANSI_AllAttrOffText();
            return FALSE;
        }
    }

    return TRUE;
}
#endif

