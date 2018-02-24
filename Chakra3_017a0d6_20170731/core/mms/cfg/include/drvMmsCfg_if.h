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
///@file drvMmsDbg_if.h
///@brief System functions:
//
///////////////////////////////////////////////////////////////////////////////
#ifndef _DRV_MMSCFG_IF_H_
#define _DRV_MMSCFG_IF_H_



//$
#define CFG_FUN_MAX   20
#define CFG_LEVEL_MAX 10
//$
#define CFG_LEVEL_0   0
#define CFG_LEVEL_1   1
#define CFG_LEVEL_2   2
#define CFG_LEVEL_3   3
#define CFG_LEVEL_4   4
#define CFG_LEVEL_5   5
#define CFG_LEVEL_6   6
#define CFG_LEVEL_7   7
#define CFG_LEVEL_8   8


#define GET_LEVLEL0_CFG_ACT_INDEX    Cfg0ActIndex
#define GET_LEVLEL1_CFG_ACT_INDEX    Cfg1ActIndex
#define GET_LEVLEL2_CFG_ACT_INDEX    Cfg2ActIndex
#define GET_LEVLEL3_CFG_ACT_INDEX    Cfg3ActIndex
#define GET_LEVLEL4_CFG_ACT_INDEX    Cfg4ActIndex
#define GET_LEVLEL5_CFG_ACT_INDEX    Cfg5ActIndex
#define GET_LEVLEL6_CFG_ACT_INDEX    Cfg6ActIndex
#define GET_LEVLEL7_CFG_ACT_INDEX    Cfg7ActIndex
#define GET_LEVLEL8_CFG_ACT_INDEX    Cfg8ActIndex

typedef enum {
    BOARD = 1,
    CHIP,
    SW,
}CFG_TYPE_T;

//$
void CfgLevel0Decode(void);
void CfgLevel1Decode(void);
void CfgLevel2Decode(void);
void CfgLevel3Decode(void);
void CfgLevel4Decode(void);
void CfgLevel5Decode(void);

void MDrv_CfgMainPagePrint(void); // page 1
void MCfg_BoardMainPagePrint(void); // page 2




//$
extern int DbgMenuLevel;
extern int CatMenuLevel;
extern int CfgMenuLevel;
extern int cfg_act;
extern U16 cfg_level;
extern U16 cfg_type;

void MDrv_Cfg_SWMenuPrint(void);
void MDrv_Cfg_ChipMenuPrint(void);
void MDrv_Cfg_BoardMenuPrint(void);


void MDrv_Cfg_Act(CFG_TYPE_T type,
                  U8 level,
                  void (*func)(void),
                  void (*help)(void)
                  );


void MDrv_CfgGotoCfgMainPage(void);
void MDrv_CfgGotoCfgMainPagePrint(void);
void MDrv_CfgGotoSWMainPage(void);
void MDrv_CfgGotoSWMainPagePrint(void);
void MDrv_CfgGotoBoardMainPage(void);
void MDrv_CfgGotoBoardMainPagePrint(void);
void MDrv_CfgGotoChipMainPage(void);
void MDrv_CfgGotoChipMainPagePrint(void);

void MDrv_Cfg_ActInit(void);
void MDrv_Cfg_UserActInit(void);


void MCfg_BoardDbg2PrePage(void);
void MDrv_Cfg_SetType(CFG_TYPE_T type);

#endif //_DRV_MMSCFG_IF_H_

