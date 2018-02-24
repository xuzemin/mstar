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
// Copyright (c) 2008 MStar Semiconductor, Inc.
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
// File Name: DrvAuTAS5706API.h
// Description: TI I2S Audio Amplifier
// Revision History:
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __DRV_URSA_API_H__
#define __DRV_URSA_API_H__
#include"MApp_GlobalSettingSt.h"

//*************************************************************************
//          Structures
//*************************************************************************

#ifdef DRV_URSAMFC_C
#define INTERFACE
#else
#define INTERFACE extern
#endif
#define MDrv_Ursa_Debug(x)    x

#if(ENABLE_MFC_6M20)

typedef enum
{
	EN_URSA_CMD_NULL = 0,
	EN_URSA_CMD_ENABLE_MFC,
	EN_URSA_CMD_ENABLE_FILM22,
	EN_URSA_CMD_ENABLE_FILM32,
	EN_URSA_CMD_ENABLE_MFC_ALL,
	EN_URSA_CMD_DEMO_POS_INV,
	EN_URSA_CMD_DEMO_POS_LINE,
	EN_URSA_CMD_DEMO_POS_X,
	EN_URSA_CMD_DEMO_POS_Y,
	EN_URSA_CMD_DEMO_STATUS,
	EN_URSA_CMD_ENABLE_BLACKSCREEN,

       EN_URSA_CMD_MAX,
} EN_URSA_CMD_INDEX;

typedef enum
{
    EN_URSA_MEMC_LEVEL_OFF=0,
    EN_URSA_MEMC_LEVEL_LOW,
    EN_URSA_MEMC_LEVEL_NORMAL,
    EN_URSA_MEMC_LEVEL_HIHT,
    EN_URSA_MEMC_LEVEL_NUMS,
}MST6M20_MEMC_LEVEL;


INTERFACE BOOLEAN MDrv_Ursa_Cmd(EN_URSA_CMD_INDEX CmdIndex, BOOLEAN bEnable);
INTERFACE BOOLEAN MDrv_Ursa_SetOsdArea(U16 u16StartX,U16 u16StartY, U16 u16Width, U16 u16Height);
INTERFACE U8 MDrv_Ursa_Get_Value_16BitMode(U16 U16Addr, BOOLEAN bHigh);
INTERFACE void MDrv_Ursa_Init(void);//(BOOLEAN bEnable);
INTERFACE void MDrv_Ursa_OsdWinHandler(BOOLEAN flag);
INTERFACE BOOLEAN MDrv_Ursa_Demo_Cmd(EN_MFC_DEMO enMFCDemo);
INTERFACE void MDrv_Ursa_DisableOsdArea(BOOLEAN bEnable);
INTERFACE void MDrv_Ursa_IIC_DebugSetting(BOOLEAN bEnable);
INTERFACE BOOLEAN MDrv_Ursa_Set_Value(U16 u16addr, BOOLEAN bHigh, U8 u8Buf);
INTERFACE U8 MDrv_Ursa_Get_Value_8BitMode(U16 U16Addr, BOOLEAN bHigh);
INTERFACE void MDrv_Ursa_Ctrl(BOOLEAN bCtrl);
INTERFACE void MDrv_Ursa_LVDS_Output(BOOLEAN bEnable ); //ht v&a 090226
INTERFACE void MDrv_Ursa_Reset_LVDS(void); //ht v&a 090226
INTERFACE  BYTE MstarToolsBurstReadByte(WORD wSubAdr);
INTERFACE void MstarToolsBurstWriteBytes(WORD wSubAdr, BYTE *pBuf, WORD wBufLen);
INTERFACE void MstarToolsWriteByte(WORD wSubAdr, BYTE ucVal);
INTERFACE void MstarToolsDebug6M10Start(void);
INTERFACE void MstarToolsDebug6M10End(void);
INTERFACE void MDrv_Ursa_SetFrameLock(BOOLEAN flag);
INTERFACE void MDrv_Ursa_BlackScreen(void);
INTERFACE void MDrv_Ursa_InputFormatChangeNotify(void);
INTERFACE void MDrv_Ursa_MemcLevelSetting(U8 u8Level);
INTERFACE U16 MDrv_Ursa_GetVersion(void);
INTERFACE void MDrv_Ursa_DemoLine_Show(BOOLEAN bEnable, BOOLEAN bVEnable);
#endif  //(MST6M20S_120HZ_ENABLE)

#undef INTERFACE

#endif // __DRV_URSA_API_H__
