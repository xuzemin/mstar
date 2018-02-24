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

#ifndef _MSTAR_USBSCRIPT_H_
#define _MSTAR_USBSCRIPT_H_

#include "Board.h"

#include "mw_debug.h"

#ifdef _MSTAR_USBSCRIPT_C_
#define INTERFACE
#else
#define INTERFACE  extern
#endif

//==============================================================//

#ifndef ENABLE_SCRIPT_EXECUTE
    #define ENABLE_SCRIPT_EXECUTE   0
#endif

#if (ENABLE_SCRIPT_EXECUTE)

typedef enum
{
    EN_SCRIPT_EVENT_INIT,
    EN_SCRIPT_EVENT_INPUTSOURCE_SWITCHSOURCE,
    EN_SCRIPT_EVENT_CHANNELCHANGE,
    EN_SCRIPT_EVENT_PROCESSUSERINPUT,
    EN_SCRIPT_EVENT_NONE=0xFF,
}EN_SCRIPT_EVENT_TYPE;

typedef struct
{
    EN_SCRIPT_EVENT_TYPE EventType;
    char* name;
}EVENT_NAME_TABLE;

typedef enum
{
    EN_SCRIPT_COMMAND_RRIU,
    EN_SCRIPT_COMMAND_WRIU,
    EN_SCRIPT_COMMAND_CHECK,
    EN_SCRIPT_COMMAND_LOG,
    EN_SCRIPT_COMMAND_MCUPAUSE,
    EN_SCRIPT_COMMAND_DUMPBANK,
    EN_SCRIPT_COMMAND_DELAY,
    EN_SCRIPT_COMMAND_UART2USBON,
    EN_SCRIPT_COMMAND_DBGATVSCAN,
}EN_SCRIPT_COMMAND_TYPE;

typedef union
{
    U8 Address[3];
    U8 frequency1[3];
    U16 MessagePoint;
    U16 Second;
}UN_MSUS_COMMAND_PARAMETER;

typedef union
{
    U8 frequency2[3];
    U8 mask;
}UN_MSUS_COMMAND_PARAMETER2;

typedef struct
{
    EN_SCRIPT_EVENT_TYPE event;
    U8 u8CommandStart;
    U8 u8CommandLength;
}MSUS_SCRIPT_EVENT;

typedef struct
{
    EN_SCRIPT_COMMAND_TYPE CommandType;
    UN_MSUS_COMMAND_PARAMETER CommonParameter;
    UN_MSUS_COMMAND_PARAMETER2 CommonParameter2;
    U8 u8value;
}MSUS_SCRIPT_COMMAND;

void msUS_ExecuteScript_Task(void);
BOOL msUS_ReadScript(void);
void msUS_ScriptExecute(EN_SCRIPT_EVENT_TYPE tEventType);
void msUS_UseScript(EN_SCRIPT_EVENT_TYPE tEventType);
void msUS_EventInit(void);
BOOL msUS_CheckEventPoolEmpty(void);
void msUS_CloseScript(void);
BOOL msUS_CommandRriu(MSUS_SCRIPT_COMMAND command);
BOOL msUS_CommandWriu(MSUS_SCRIPT_COMMAND command);
BOOL msUS_CommandCheck(MSUS_SCRIPT_COMMAND command);
BOOL msUS_CommandLog(MSUS_SCRIPT_COMMAND command);
void msUS_CommandMcuPause(void);
BOOL msUS_CommandDumpBank(MSUS_SCRIPT_COMMAND command);
BOOL msUS_CommandDelay(MSUS_SCRIPT_COMMAND command);
BOOL msUS_CommandUart2USBOn(void);
BOOL msUS_CommandDbgATVScan(MSUS_SCRIPT_COMMAND command);

#endif //#if (ENABLE_SCRIPT_EXECUTE)

#undef INTERFACE
#endif

