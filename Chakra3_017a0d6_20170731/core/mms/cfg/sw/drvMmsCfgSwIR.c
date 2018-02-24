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
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///@file drvMmsCfgSWIR.c
///@brief System functions:
//
///////////////////////////////////////////////////////////////////////////////


#include "MsCommon.h"
#include "drvUartDebug.h"
#if ( ENABLE_MMS)
#include "drvMmsCfg_if.h"
#include "drvMmsCfgSw_if.h"
#include "drvMmsDisp_if.h"

#include "drvUART.h"

U8 g_DisableIr = 0;

void MDrv_DisableIR(void)
{
    g_DisableIr = 1;
}

void MDrv_EnableIR(void)
{
   g_DisableIr  = 0;
}


void MDrv_Cfg_SwIR(void)
{
    if (MDrv_GetPara(1))
    {
        if(1 == para[0])
        {
            printf("execute turn off IR\n");
            MDrv_DisableIR();
        }
        else if(0 == para[0])
        {
            printf("execute turn on IR\n");
            MDrv_EnableIR();

        }
    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_SwIREntry(void)
{
    cfg_level = IR;
    dynLevel = 1;
    MDrv_Cfg_SWMenuPrint();
}

void MDrv_Cfg_SwIRPrint(void)
{
    printf("Turn off IR \"-1\"; Turn on IR \"-0\" \n");
}

void MDrv_Cfg_SwIREntryPrint(void)
{
    printf("Enter IR page\n");
}

void MDrv_Cfg_SWIRInit(void)
{
    //(1)main page list
    MDrv_Cfg_Act(SW, SW_MAIN, MDrv_Cfg_SwIREntry, MDrv_Cfg_SwIREntryPrint);

    //(2)Action function(s)
    MDrv_Cfg_Act(SW, IR, MDrv_Cfg_SwIR, MDrv_Cfg_SwIRPrint);

    //(3)jump to SW main page
    MDrv_Cfg_Act(SW, IR, MDrv_CfgGotoSWMainPage, MDrv_CfgGotoSWMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(SW, IR, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}

void MDrv_Cfg_SwUART(void)
{
    if (MDrv_GetPara(1))
    {
        if(0 == para[0])
        {
             mdrv_uart_connect(E_UART_PORT0, E_UART_OFF);
        }
        else if(1 == para[0])
        {
            mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
            printf("print in HK\n");
        }
        else if(2 == para[0])
        {
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
#else
            mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
#endif
            printf("print in MM\n");

        }
        else if(3 == para[0] )
        {
            mdrv_uart_connect(E_UART_PORT0, E_UART_VDEC);
            printf("print in VDEC\n");
        }

    }
    MDrv_ClearParaTbl();
}

void MDrv_Cfg_SwUARTEntry(void)
{
    cfg_level = UART;
    dynLevel = 1;
    MDrv_Cfg_SWMenuPrint();
}

void MDrv_Cfg_SwUARTPrint(void)
{
    printf("-no \" -hk \" -mm \" -vdec \n");
}

void MDrv_Cfg_SwUARTEntryPrint(void)
{
    printf("Enter UART swithc page\n");
}

void MDrv_Cfg_SWUARTInit(void)
{
    MDrv_Cfg_Act(SW, SW_MAIN, MDrv_Cfg_SwUARTEntry, MDrv_Cfg_SwUARTEntryPrint);
    MDrv_Cfg_Act(SW, UART, MDrv_Cfg_SwUART, MDrv_Cfg_SwUARTPrint);
    MDrv_Cfg_Act(SW, UART, MDrv_CfgGotoSWMainPage, MDrv_CfgGotoSWMainPagePrint);
    MDrv_Cfg_Act(SW, UART, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}


#endif //ENABLE_MSTV_UART_DEBUG

