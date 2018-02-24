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

#if 0//def OBA_MSTV_DEBUG
#include <stdio.h>
#include <string.h>

//#include "MsCommon.h"// for RIU read write
//#include "Enum_Device.h"
#include "drvUartDebug.h"// for MSTV_Tool
//#include "drvMMIO.h"
#include "madp.h"

//#define UNUSED(x) x=x
extern void MDrv_UART_RecvHandler(int c);


typedef enum
{
    MSTV_DBG_MSG_START,
    MSTV_DBG_MSG_END,
    MSTV_DBG_MSG_CMD,
}MSTV_DBG_MSG;


static U8 _u8ChIndex;
static pid_t _MstvAppPid;

BOOLEAN MApp_MSTV_ReceiveMsg(unsigned char * pu8InData, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    UNUSED(pu8OutData);
    UNUSED(u16OutDataSize);

//    printf("MApp_MSTV_ReceiveMsg. pu8InData[0]:%d\n", pu8InData[0]);
    switch (pu8InData[0])
    {
        case MSTV_DBG_MSG_START:
        {
            // app pid
            memcpy((unsigned char*)&_MstvAppPid, &pu8InData[1], sizeof(pid_t));

            //printf("_MstvAppPid: %d\n", _MstvAppPid);
#if 1
            if( freopen("file.txt", "w", stdout) == NULL)    // use "w" to keep file small, "a+" to log all.
            {
                printf("MApp_MSTV_ReceiveMsg:stdout redirect fail\n");
            }
#endif
            //reset command buffer for MSTV_Tool
            //MDrv_UART_DebugInit();

            break;
        }

        case MSTV_DBG_MSG_CMD: //uart message
        {
            int i;
//            printf("MApp_MSTV_ReceiveMsg: MSTV_DBG_MSG_CMD\n");
            for (i=1; i < u16InDataSize; i++)
            {
//                printf("%x ", pu8InData[i]);
                MDrv_UART_RecvHandler(pu8InData[i]);
            }

            // command packet valid. process the cooamd.
            if(g_bUart0Detected == TRUE)
            {
                if (UART_EXT)   // DLC & DBC
                {
                    MDrv_UART_DecodeExtCommand();
                }
                else    // Normal command: XDATA read/write
                {
                    MDrv_UART_DecodeNormalCommand();
                }
                g_bUart0Detected = FALSE;

                //reset command buffer
                //MDrv_UART_DebugInit();
            }
            break;
        }

        case MSTV_DBG_MSG_END:
        {
#if 1
            if( freopen("/dev/ttyS0", "w", stdout) == NULL)    // use "w" to keep file small, "a+" to log all.
            {
                printf("MApp_MSTV_ReceiveMsg:stdout redirect fail\n");
            }
#endif
            break;
        }

    }

    return TRUE;
}

BOOLEAN MApp_MSTV_SendMsg(unsigned char * pu8InData, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    UNUSED(pu8OutData);
    UNUSED(u16OutDataSize);
//    printf("MApp_MSTV_SendMsg\n");
    return MAdp_MSGCH_SendSignal(_MstvAppPid, _u8ChIndex, pu8InData, u16InDataSize);
}

void MApp_MSTV_Debug_Init(void)
{
    printf("MApp_MSTV_Debug_Init\n");

    MAdp_MSGCH_Init();

    _u8ChIndex = MAdp_MSGCH_GetChannelIndex("MSTV_DEBUG");
    MAdp_MSGCH_SetCallBack(_u8ChIndex, MApp_MSTV_ReceiveMsg);
}
#endif

