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
///@file drvMmsCfgBoardPanel.c
///@brief System functions:
//
///////////////////////////////////////////////////////////////////////////////

#include "MsCommon.h"
#include "drvUartDebug.h"
#if ( ENABLE_MMS)
#include "drvMmsCfg_if.h"
#include "drvMmsCfgBoard_if.h"
#include "drvMmsDisp_if.h"

#include "SysInit.h"
#include "Panel.h"

#if 0
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_SaveData.h"
#endif
void test_panel_set(U16 RES)
{
#if 1
    RES = RES;
#else
    //write value to eeprom
    printf("input %u\n", RES);

    stGenSetting.g_SysSetting.enPanelResType = (PANEL_RESOLUTION_TYPE) RES;
    //stGenSetting.g_SysSetting.u32CfgFlag = 1;
    MApp_SaveSysSetting();
    printf("stGenSetting.g_SysSetting.enPanelResType = %d\n", stGenSetting.g_SysSetting.enPanelResType);

    //cpu reset
    MDrv_Sys_WholeChipReset(); //<-- aeon reset????
#endif
}


void MDrv_Cfg_BoardPanelSXGA(void)
{
    test_panel_set(PNL_WXGA_AU20_T200XW02);
}

void MDrv_Cfg_BoardPanelSXGAEntry(void)
{
    cfg_level = SXGA;
    dynLevel = 1;
    MDrv_Cfg_BoardMenuPrint();
}

void MDrv_Cfg_BoardPanelSXGAPrint(void)
{
    printf("Execute Change panel type to SXGA(1280x1024), Pnl_AU17_EN05_SXGA\n");
}

void MDrv_Cfg_BoardPanelSXGAEntryPrint(void)
{
    printf("Change panel type to SXGA(1280x1024), Pnl_AU17_EN05_SXGA\n");
}


void MDrv_Cfg_BoardPanelWXGA(void)
{
    test_panel_set(PNL_WXGA_AU20_T200XW02);
}
void MDrv_Cfg_BoardPanelWXGAEntry(void)
{
    cfg_level = WXGA;
    dynLevel = 1;
    MDrv_Cfg_BoardMenuPrint();
}

void MDrv_Cfg_BoardPanelWXGAPrint(void)
{
    printf("Execute Change panel type to WXGA(1366x76), Pnl_AU20_T200XW02_WXGA\n");
}

void MDrv_Cfg_BoardPanelWXGAEntryPrint(void)
{
    printf("Change panel type to WXGA(1366x76), Pnl_AU20_T200XW02_WXGA\n");
}


void MDrv_Cfg_BoardPanelWXGA_P(void)
{
    test_panel_set(PNL_WXGA_PLUS_CMO190_M190A1);
}

void MDrv_Cfg_BoardPanelWXGA_PEntry(void)
{
    cfg_level = WXGA_PLUS;
    dynLevel = 1;
    MDrv_Cfg_BoardMenuPrint();
}

void MDrv_Cfg_BoardPanelWXGA_PPrint(void)
{
    printf("Execute Change panel type to WXGA_PLUS(1440x900), Pnl_CMO19_M190A1_WXGA, Pnl_AU19PW01_WXGA\n");
}

void MDrv_Cfg_BoardPanelWXGA_PEntryPrint(void)
{
    printf("Change panel type to WXGA_PLUS(1440x900), Pnl_CMO19_M190A1_WXGA, Pnl_AU19PW01_WXGA\n");
}


void MDrv_Cfg_BoardPanelWSXGA(void)
{
    test_panel_set(PNL_WSXGA_AU22_M201EW01);
}
void MDrv_Cfg_BoardPanelWSXGAEntry(void)
{
    cfg_level = WSXGA;
    dynLevel = 1;
    MDrv_Cfg_BoardMenuPrint();
}

void MDrv_Cfg_BoardPanelWSXGAPrint(void)
{
    printf("Change panel type to WSXGA(1680x1050), Pnl_AU20_M201EW01_WSXGA\n");
}

void MDrv_Cfg_BoardPanelWSXGAEntryPrint(void)
{
    printf("Change panel type to WSXGA(1680x1050), Pnl_AU20_M201EW01_WSXGA\n");
}

void MDrv_Cfg_BoardPanelFHD(void)
{
    test_panel_set(PNL_FULLHD_CMO216_H1L01);
}
void MDrv_Cfg_BoardPanelFHDEntry(void)
{
    cfg_level = FULL_HD;
    dynLevel = 1;
    MDrv_Cfg_BoardMenuPrint();
}

void MDrv_Cfg_BoardPanelFHDPrint(void)
{
    printf("Execute Change panel type to FULL_HD(1920x1080), Pnl_AU37_T370HW01_HD, Pnl_CMO216H1_L01_HD\n");
}

void MDrv_Cfg_BoardPanelFHDEntryPrint(void)
{
    printf("Change panel type to FULL_HD(1920x1080), Pnl_AU37_T370HW01_HD, Pnl_CMO216H1_L01_HD\n");
}

void MDrv_Cfg_BoardPanelSEC_FULL(void)
{
    test_panel_set(PNL_FULLHD_SEC_LE32A);
}

void MDrv_Cfg_BoardPanelSEC_FULLEntry(void)
{
    cfg_level = SEC32_LE32A_FULL;
    MDrv_Cfg_BoardMenuPrint();
}

void MDrv_Cfg_BoardPanelSEC_FULLPrint(void)
{
    printf("Execute Change panel type to SEC32_LE32A_FULLHD(1920x1080), Pnl_AU37_T370HW01_HD, Pnl_CMO216H1_L01_HD\n");
}

void MDrv_Cfg_BoardPanelSEC_FULLEntryPrint(void)
{
    printf("Change panel type to SEC32_LE32A_FULLHD(1920x1080), Pnl_AU37_T370HW01_HD, Pnl_CMO216H1_L01_HD\n");
}


void MDrv_Cfg_BoardPanelInit(void)
{
    //SXGA
    MDrv_Cfg_Act(BOARD, BOARD_MAIN, MDrv_Cfg_BoardPanelSXGAEntry, MDrv_Cfg_BoardPanelSXGAEntryPrint);
    MDrv_Cfg_Act(BOARD, SXGA, MDrv_Cfg_BoardPanelSXGA, MDrv_Cfg_BoardPanelSXGAPrint);

    //WXGA
    MDrv_Cfg_Act(BOARD, BOARD_MAIN, MDrv_Cfg_BoardPanelWXGAEntry, MDrv_Cfg_BoardPanelWXGAEntryPrint);
    MDrv_Cfg_Act(BOARD, WXGA, MDrv_Cfg_BoardPanelWXGA, MDrv_Cfg_BoardPanelWXGAPrint);

    //WXGA- PLUS
    MDrv_Cfg_Act(BOARD, BOARD_MAIN, MDrv_Cfg_BoardPanelWXGA_PEntry, MDrv_Cfg_BoardPanelWXGA_PEntryPrint);
    MDrv_Cfg_Act(BOARD, WXGA_PLUS, MDrv_Cfg_BoardPanelWXGA_P, MDrv_Cfg_BoardPanelWXGA_PPrint);

    //WSXGA
    MDrv_Cfg_Act(BOARD, BOARD_MAIN, MDrv_Cfg_BoardPanelWSXGAEntry, MDrv_Cfg_BoardPanelWSXGAEntryPrint);
    MDrv_Cfg_Act(BOARD, WSXGA, MDrv_Cfg_BoardPanelWSXGA, MDrv_Cfg_BoardPanelWSXGAPrint);

    //FHD
    MDrv_Cfg_Act(BOARD, BOARD_MAIN, MDrv_Cfg_BoardPanelFHDEntry, MDrv_Cfg_BoardPanelFHDEntryPrint);
    MDrv_Cfg_Act(BOARD, FULL_HD, MDrv_Cfg_BoardPanelFHD, MDrv_Cfg_BoardPanelFHDPrint);

    //SEC_FULL
    MDrv_Cfg_Act(BOARD, BOARD_MAIN, MDrv_Cfg_BoardPanelSEC_FULLEntry, MDrv_Cfg_BoardPanelSEC_FULLEntryPrint);
    MDrv_Cfg_Act(BOARD, SEC32_LE32A_FULL, MDrv_Cfg_BoardPanelSEC_FULL, MDrv_Cfg_BoardPanelSEC_FULLPrint);


    //(3)jump to Board main page
    MDrv_Cfg_Act(BOARD, SXGA, MDrv_CfgGotoBoardMainPage, MDrv_CfgGotoBoardMainPagePrint);

    //(4)jump to config system main page
    MDrv_Cfg_Act(BOARD, SXGA, MDrv_CfgGotoCfgMainPage, MDrv_CfgGotoCfgMainPagePrint);
}

#endif //ENABLE_MSTV_UART_DEBUG

