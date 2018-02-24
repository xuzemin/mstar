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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("; MStar; Confidential; Information;") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//****************************************************
// TCON Drive Chip           : Panasonic_TCON_Driver
// TCON Excel CodeGen Version: 1.06
// TCON Excel SW      Version: 1.00
// TCON Excel update date    : 2011/11/3 23:45
//****************************************************

#ifndef _DRVTCON_TBL_H_
#define _DRVTCON_TBL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define DRV_TCON_REG(reg)       ((reg>>8)&0xFF), (reg&0xFF)
#define REG_ADDR_SIZE           2
#define REG_MASK_SIZE           1
#define REG_TABLE_END           0xFFFF
// #define TCON_PANEL_NUMS         1

#define _TC_PK_L_(bank, addr)     ((U16)(bank << 8) | (addr))
#define _TC_PK_H_(bank, addr)     ((U16)((bank|0x80) << 8) | (addr))

#define  REG_TC_GAMMA_BASE     0x0000
#define  REG_TC_CLK_GEN_BASE     0x0B00
#define  REG_TC_CHIP_TOP_BASE     0x1E00
#define  REG_TC_TCON_BASE     0x3000
#define  REG_TC_LPLL_BASE     0x3100
#define  REG_TC_SC_BASE     0x2F00
#define  REG_TC_MOD_BASE     0x3200

typedef enum
{
    TCON_TABTYPE_GENERAL,
    TCON_TABTYPE_GPIO,
    TCON_TABTYPE_SCALER,
    TCON_TABTYPE_MOD,
    TCON_TABTYPE_GAMMA,
    TCON_TABTYPE_POWER_SEQUENCE_ON,
    TCON_TABTYPE_POWER_SEQUENCE_OFF,
} E_TCON_TAB_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_Panasonic_AX080A076G_POLL_POLR_CPV_LP,
    TCON_SIGNAL_Panasonic_AX080A076G_DATA1,
    TCON_SIGNAL_Panasonic_AX080A076G_DATA2,
    TCON_SIGNAL_Panasonic_AX080A076G_NUMS,
} E_TCON_Panasonic_AX080A076G_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_Hisense_AH080A016G_POLL_POLR_CPV_TP1,
    TCON_SIGNAL_Hisense_AH080A016G_STV,
    TCON_SIGNAL_Hisense_AH080A016G_NUMS,
} E_TCON_Hisense_AH080A016G_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_PVI050VX1_OTHERS,
    TCON_SIGNAL_PVI050VX1_STV,
    TCON_SIGNAL_PVI050VX1_OEN,
    TCON_SIGNAL_PVI050VX1_DEFAULT_DIRECTION,
    TCON_SIGNAL_PVI050VX1_NUMS,
} E_TCON_PVI050VX1_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_PVI035VX2_OTHERS,
    TCON_SIGNAL_PVI035VX2_STV,
    TCON_SIGNAL_PVI035VX2_OEN,
    TCON_SIGNAL_PVI035VX2_DEFAULT_DIRECTION,
    TCON_SIGNAL_PVI035VX2_NUMS,
} E_TCON_PVI035VX2_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_PVI058OX1_OTHERS,
    TCON_SIGNAL_PVI058OX1_STV,
    TCON_SIGNAL_PVI058OX1_OEN,
    TCON_SIGNAL_PVI058OX1_DEFAULT_DIRECTION,
    TCON_SIGNAL_PVI058OX1_NUMS,
} E_TCON_PVI058OX1_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_BOE_BOE_HV320WXC_TP_CPV_OE1_OE2_POL,
    TCON_SIGNAL_BOE_BOE_HV320WXC_STV,
    TCON_SIGNAL_BOE_BOE_HV320WXC_NUMS,
} E_TCON_BOE_BOE_HV320WXC_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_FullHD_Amtran_POLL_POLR_CPV_TP1,
    TCON_SIGNAL_FullHD_Amtran_STV,
    TCON_SIGNAL_FullHD_Amtran_NUMS,
} E_TCON_FullHD_Amtran_PWSEQ_SIGNAL_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_AUO_T420HW09_POLL_POLR_CPV_TP1,
    TCON_SIGNAL_AUO_T420HW09_STV,
    TCON_SIGNAL_AUO_T420HW09_NUMS,
} E_TCON_AUO_T420HW09_PWSEQ_SIGNAL_TYPE;

typedef enum
{
    TCON_SIGNAL_CSOT_TRIGATE_32_POLL_POLR_CPV_TP1,
    TCON_SIGNAL_CSOT_TRIGATE_32_STV,
    TCON_SIGNAL_CSOT_TRIGATE_32_NUMS,
} E_TCON_CSOT_TRIGATE_32_PWSEQ_SIGNAL_TYPE;

typedef enum
{
    TCON_SIGNAL_CSOT_V390HZ1_POLL_POLR_CPV_TP1,
    TCON_SIGNAL_CSOT_V390HZ1_STV,
    TCON_SIGNAL_CSOT_V390HZ1_NUMS,
} E_TCON_CSOT_V390HZ1_PWSEQ_SIGNAL_TYPE;

typedef enum
{
    TCON_SIGNAL_CMO_V390HJ1_POLL_POLR_CPV_TP1,
    TCON_SIGNAL_CMO_V390HJ1_STV,
    TCON_SIGNAL_CMO_V390HJ1_NUMS,
} E_TCON_CMO_V390HJ1_PWSEQ_SIGNAL_TYPE;

/************************************************************************************************************/

typedef enum
{
    TCON_SIGNAL_POL_YOE_OE2_YCLK_STB,
    TCON_SIGNAL_YDIO1,
    TCON_SIGNAL_NUMS,
} E_TCON_PWSEQ_SIGNAL_TYPE;

typedef struct
{
    U8           *pTConInitTab;
    E_TCON_TAB_TYPE eInittype;
    U8           *pTConInit_GPIOTab;
    E_TCON_TAB_TYPE eInit_GPIOtype;
    U8           *pTConInit_SCTab;
    E_TCON_TAB_TYPE eInit_SCtype;
    U8           *pTConInit_MODTab;
    E_TCON_TAB_TYPE eInit_MODtype;
    U8           *pTConGammaTab;
    E_TCON_TAB_TYPE eGammatype;
    U8           *pTConPower_Sequence_OnTab;
    E_TCON_TAB_TYPE ePower_Sequence_Ontype;
    U8           *pTConPower_Sequence_OffTab;
    E_TCON_TAB_TYPE ePower_Sequence_Offtype;
} TCON_TAB_INFO;

/*************************************************************************************************************/

typedef enum
{
    TCON_PANEL_FULLHD,
    TCON_PANEL_Panasonic_AX080A076G,
    TCON_PANEL_Hisense_AH080A016G,
    TCON_PANEL_PVI058OX1,
    TCON_PANEL_PVI050VX1,
    TCON_PANEL_PVI035VX2,
    TCON_PANEL_BOE_HV320WXC,
    TCON_PANEL_FullHD_Amtran,
    TCON_PANEL_FullHD_AUO_T420HW09,
    TCON_PANEL_CSOT_TRIGATE_32,
    TCON_PANEL_CSOT_V390HZ1,
    TCON_PANEL_CMO_V390HJ1,
    TCON_PANEL_NUMS,
} E_TCON_PANEL_INDEX;

/*************************************************************************************************************/

extern TCON_TAB_INFO TConMAP_Main[TCON_PANEL_NUMS];

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_Init_ALL,
    TCON_TAB_Init_NUMS
} E_TCON_Init_TYPE;

typedef enum
{
    TCON_TAB_Init_GPIO_ALL,
    TCON_TAB_Init_GPIO_NUMS
} E_TCON_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_Init_SC_ALL,
    TCON_TAB_Init_SC_NUMS
} E_TCON_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_Init_MOD_ALL,
    TCON_TAB_Init_MOD_NUMS
} E_TCON_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_Power_Sequence_On_ALL,
    TCON_TAB_Power_Sequence_On_Delay_Ready,
    TCON_TAB_Power_Sequence_On_Delay_Time,
    TCON_TAB_Power_Sequence_On_Signal_Type,
    TCON_TAB_Power_Sequence_On_NUMS
} E_TCON_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_Power_Sequence_Off_ALL,
    TCON_TAB_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_Power_Sequence_Off_Delay_Time,
    TCON_TAB_Power_Sequence_Off_Signal_Type,
    TCON_TAB_Power_Sequence_Off_NUMS
} E_TCON_Power_Sequence_Off_TYPE;

typedef enum
{
    TCON_TAB_Panasonic_AX080A076G_Init_ALL,
    TCON_TAB_Panasonic_AX080A076G_Init_NUMS
} E_TCON_Panasonic_AX080A076G_Init_TYPE;

typedef enum
{
    TCON_TAB_Panasonic_AX080A076G_Init_GPIO_ALL,
    TCON_TAB_Panasonic_AX080A076G_Init_GPIO_NUMS
} E_TCON_Panasonic_AX080A076G_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_Panasonic_AX080A076G_Init_SC_ALL,
    TCON_TAB_Panasonic_AX080A076G_Init_SC_NUMS
} E_TCON_Panasonic_AX080A076G_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_Panasonic_AX080A076G_Init_MOD_ALL,
    TCON_TAB_Panasonic_AX080A076G_Init_MOD_NUMS
} E_TCON_Panasonic_AX080A076G_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_On_ALL,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_On_Delay_Ready,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_On_Delay_Time,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_On_Signal_Type,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_On_NUMS
} E_TCON_Panasonic_AX080A076G_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_Off_ALL,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_Off_Delay_Time,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_Off_Signal_Type,
    TCON_TAB_Panasonic_AX080A076G_Power_Sequence_Off_NUMS
} E_TCON_Panasonic_AX080A076G_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_Hisense_AH080A016G_Init_ALL,
    TCON_TAB_Hisense_AH080A016G_Init_NUMS
} E_TCON_Hisense_AH080A016G_Init_TYPE;

typedef enum
{
    TCON_TAB_Hisense_AH080A016G_Init_GPIO_ALL,
    TCON_TAB_Hisense_AH080A016G_Init_GPIO_NUMS
} E_TCON_Hisense_AH080A016G_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_Hisense_AH080A016G_Init_SC_ALL,
    TCON_TAB_Hisense_AH080A016G_Init_SC_NUMS
} E_TCON_Hisense_AH080A016G_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_Hisense_AH080A016G_Init_MOD_ALL,
    TCON_TAB_Hisense_AH080A016G_Init_MOD_NUMS
} E_TCON_Hisense_AH080A016G_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_On_ALL,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_On_Delay_Ready,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_On_Delay_Time,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_On_Signal_Type,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_On_NUMS
} E_TCON_Hisense_AH080A016G_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_Off_ALL,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_Off_Delay_Time,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_Off_Signal_Type,
    TCON_TAB_Hisense_AH080A016G_Power_Sequence_Off_NUMS
} E_TCON_Hisense_AH080A016G_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_PVI050VX1_Init_ALL,
    TCON_TAB_PVI050VX1_Init_NUMS
} E_TCON_PVI050VX1_Init_TYPE;


typedef enum
{
    TCON_TAB_PVI050VX1_Init_GPIO_ALL,
    TCON_TAB_PVI050VX1_Init_GPIO_NUMS
} E_TCON_PVI050VX1_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_PVI050VX1_Init_SC_ALL,
    TCON_TAB_PVI050VX1_Init_SC_NUMS
} E_TCON_PVI050VX1_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_PVI050VX1_Init_MOD_ALL,
    TCON_TAB_PVI050VX1_Init_MOD_NUMS
} E_TCON_PVI050VX1_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_PVI050VX1_Power_Sequence_On_ALL,
    TCON_TAB_PVI050VX1_Power_Sequence_On_Delay_Ready,
    TCON_TAB_PVI050VX1_Power_Sequence_On_Delay_Time,
    TCON_TAB_PVI050VX1_Power_Sequence_On_Signal_Type,
    TCON_TAB_PVI050VX1_Power_Sequence_On_NUMS
} E_TCON_PVI050VX1_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_PVI050VX1_Power_Sequence_Off_ALL,
    TCON_TAB_PVI050VX1_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_PVI050VX1_Power_Sequence_Off_Delay_Time,
    TCON_TAB_PVI050VX1_Power_Sequence_Off_Signal_Type,
    TCON_TAB_PVI050VX1_Power_Sequence_Off_NUMS
} E_TCON_PVI050VX1_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_PVI035VX2_Init_ALL,
    TCON_TAB_PVI035VX2_Init_NUMS
} E_TCON_PVI035VX2_Init_TYPE;

typedef enum
{
    TCON_TAB_PVI035VX2_Init_GPIO_ALL,
    TCON_TAB_PVI035VX2_Init_GPIO_NUMS
} E_TCON_PVI035VX2_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_PVI035VX2_Init_SC_ALL,
    TCON_TAB_PVI035VX2_Init_SC_NUMS
} E_TCON_PVI035VX2_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_PVI035VX2_Init_MOD_ALL,
    TCON_TAB_PVI035VX2_Init_MOD_NUMS
} E_TCON_PVI035VX2_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_PVI035VX2_Power_Sequence_On_ALL,
    TCON_TAB_PVI035VX2_Power_Sequence_On_Delay_Ready,
    TCON_TAB_PVI035VX2_Power_Sequence_On_Delay_Time,
    TCON_TAB_PVI035VX2_Power_Sequence_On_Signal_Type,
    TCON_TAB_PVI035VX2_Power_Sequence_On_NUMS
} E_TCON_PVI035VX2_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_PVI035VX2_Power_Sequence_Off_ALL,
    TCON_TAB_PVI035VX2_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_PVI035VX2_Power_Sequence_Off_Delay_Time,
    TCON_TAB_PVI035VX2_Power_Sequence_Off_Signal_Type,
    TCON_TAB_PVI035VX2_Power_Sequence_Off_NUMS
} E_TCON_PVI035VX2_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_PVI058OX1_Init_ALL,
    TCON_TAB_PVI058OX1_Init_NUMS
} E_TCON_PVI058OX1_Init_TYPE;

typedef enum
{
    TCON_TAB_PVI058OX1_Init_GPIO_ALL,
    TCON_TAB_PVI058OX1_Init_GPIO_NUMS
} E_TCON_PVI058OX1_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_PVI058OX1_Init_SC_ALL,
    TCON_TAB_PVI058OX1_Init_SC_NUMS
} E_TCON_PVI058OX1_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_PVI058OX1_Init_MOD_ALL,
    TCON_TAB_PVI058OX1_Init_MOD_NUMS
} E_TCON_PVI058OX1_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_PVI058OX1_Power_Sequence_On_ALL,
    TCON_TAB_PVI058OX1_Power_Sequence_On_Delay_Ready,
    TCON_TAB_PVI058OX1_Power_Sequence_On_Delay_Time,
    TCON_TAB_PVI058OX1_Power_Sequence_On_Signal_Type,
    TCON_TAB_PVI058OX1_Power_Sequence_On_NUMS
} E_TCON_PVI058OX1_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_PVI058OX1_Power_Sequence_Off_ALL,
    TCON_TAB_PVI058OX1_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_PVI058OX1_Power_Sequence_Off_Delay_Time,
    TCON_TAB_PVI058OX1_Power_Sequence_Off_Signal_Type,
    TCON_TAB_PVI058OX1_Power_Sequence_Off_NUMS
} E_TCON_PVI058OX1_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_BOE_BOE_HV320WXC_Init_ALL,
    TCON_TAB_BOE_BOE_HV320WXC_Init_NUMS
} E_TCON_BOE_BOE_HV320WXC_Init_TYPE;

typedef enum
{
    TCON_TAB_BOE_BOE_HV320WXC_Init_GPIO_ALL,
    TCON_TAB_BOE_BOE_HV320WXC_Init_GPIO_NUMS
} E_TCON_BOE_BOE_HV320WXC_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_BOE_BOE_HV320WXC_Init_SC_ALL,
    TCON_TAB_BOE_BOE_HV320WXC_Init_SC_NUMS
} E_TCON_BOE_BOE_HV320WXC_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_BOE_BOE_HV320WXC_Init_MOD_ALL,
    TCON_TAB_BOE_BOE_HV320WXC_Init_MOD_NUMS
} E_TCON_BOE_BOE_HV320WXC_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_On_ALL,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_On_Delay_Ready,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_On_Delay_Time,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_On_Signal_Type,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_On_NUMS
} E_TCON_BOE_BOE_HV320WXC_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_Off_ALL,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_Off_Delay_Time,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_Off_Signal_Type,
    TCON_TAB_BOE_BOE_HV320WXC_Power_Sequence_Off_NUMS
} E_TCON_BOE_BOE_HV320WXC_Power_Sequence_Off_TYPE;



/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_FullHD_Amtran_Init_ALL,
    TCON_TAB_FullHD_Amtran_Init_NUMS
} E_TCON_FullHD_Amtran_Init_TYPE;

typedef enum
{
    TCON_TAB_FullHD_Amtran_Init_GPIO_ALL,
    TCON_TAB_FullHD_Amtran_Init_GPIO_NUMS
} E_TCON_FullHD_Amtran_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_FullHD_Amtran_Init_SC_ALL,
    TCON_TAB_FullHD_Amtran_Init_SC_NUMS
} E_TCON_FullHD_Amtran_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_FullHD_Amtran_Init_MOD_ALL,
    TCON_TAB_FullHD_Amtran_Init_MOD_NUMS
} E_TCON_FullHD_Amtran_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_FullHD_Amtran_Power_Sequence_On_ALL,
    TCON_TAB_FullHD_Amtran_Power_Sequence_On_Delay_Ready,
    TCON_TAB_FullHD_Amtran_Power_Sequence_On_Delay_Time,
    TCON_TAB_FullHD_Amtran_Power_Sequence_On_Signal_Type,
    TCON_TAB_FullHD_Amtran_Power_Sequence_On_NUMS
} E_TCON_FullHD_Amtran_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_FullHD_Amtran_Power_Sequence_Off_ALL,
    TCON_TAB_FullHD_Amtran_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_FullHD_Amtran_Power_Sequence_Off_Delay_Time,
    TCON_TAB_FullHD_Amtran_Power_Sequence_Off_Signal_Type,
    TCON_TAB_FullHD_Amtran_Power_Sequence_Off_NUMS
} E_TCON_FullHD_Amtran_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_AUO_T420HW09_Init_ALL,
    TCON_TAB_AUO_T420HW09_Init_NUMS
} E_TCON_AUO_T420HW09_Init_TYPE;

typedef enum
{
    TCON_TAB_AUO_T420HW09_Init_GPIO_ALL,
    TCON_TAB_AUO_T420HW09_Init_GPIO_NUMS
} E_TCON_AUO_T420HW09_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_AUO_T420HW09_Init_SC_ALL,
    TCON_TAB_AUO_T420HW09_Init_SC_NUMS
} E_TCON_AUO_T420HW09_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_AUO_T420HW09_Init_MOD_ALL,
    TCON_TAB_AUO_T420HW09_Init_MOD_NUMS
} E_TCON_AUO_T420HW09_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_AUO_T420HW09_Power_Sequence_On_ALL,
    TCON_TAB_AUO_T420HW09_Power_Sequence_On_Delay_Ready,
    TCON_TAB_AUO_T420HW09_Power_Sequence_On_Delay_Time,
    TCON_TAB_AUO_T420HW09_Power_Sequence_On_Signal_Type,
    TCON_TAB_AUO_T420HW09_Power_Sequence_On_NUMS
} E_TCON_AUO_T420HW09_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_AUO_T420HW09_Power_Sequence_Off_ALL,
    TCON_TAB_AUO_T420HW09_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_AUO_T420HW09_Power_Sequence_Off_Delay_Time,
    TCON_TAB_AUO_T420HW09_Power_Sequence_Off_Signal_Type,
    TCON_TAB_AUO_T420HW09_Power_Sequence_Off_NUMS
} E_TCON_AUO_T420HW09_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_CSOT_TRIGATE_32_Init_ALL,
    TCON_TAB_CSOT_TRIGATE_32_Init_NUMS
} E_TCON_CSOT_TRIGATE_32_Init_TYPE;

typedef enum
{
    TCON_TAB_CSOT_TRIGATE_32_Init_GPIO_ALL,
    TCON_TAB_CSOT_TRIGATE_32_Init_GPIO_NUMS
} E_TCON_CSOT_TRIGATE_32_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_CSOT_TRIGATE_32_Init_SC_ALL,
    TCON_TAB_CSOT_TRIGATE_32_Init_SC_NUMS
} E_TCON_CSOT_TRIGATE_32_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_CSOT_TRIGATE_32_Init_MOD_ALL,
    TCON_TAB_CSOT_TRIGATE_32_Init_MOD_NUMS
} E_TCON_CSOT_TRIGATE_32_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_On_ALL,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_On_Delay_Ready,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_On_Delay_Time,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_On_Signal_Type,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_On_NUMS
} E_TCON_CSOT_TRIGATE_32_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_Off_ALL,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_Off_Delay_Time,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_Off_Signal_Type,
    TCON_TAB_CSOT_TRIGATE_32_Power_Sequence_Off_NUMS
} E_TCON_CSOT_TRIGATE_32_Power_Sequence_Off_TYPE;


/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_CSOT_V390HZ1_Init_ALL,
    TCON_TAB_CSOT_V390HZ1_Init_NUMS
} E_TCON_CSOT_V390HZ1_Init_TYPE;

typedef enum
{
    TCON_TAB_CSOT_V390HZ1_Init_GPIO_ALL,
    TCON_TAB_CSOT_V390HZ1_Init_GPIO_NUMS
} E_TCON_CSOT_V390HZ1_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_CSOT_V390HZ1_Init_SC_ALL,
    TCON_TAB_CSOT_V390HZ1_Init_SC_NUMS
} E_TCON_CSOT_V390HZ1_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_CSOT_V390HZ1_Init_MOD_ALL,
    TCON_TAB_CSOT_V390HZ1_Init_MOD_NUMS
} E_TCON_CSOT_V390HZ1_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_On_ALL,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_On_Delay_Ready,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_On_Delay_Time,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_On_Signal_Type,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_On_NUMS
} E_TCON_CSOT_V390HZ1_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_Off_ALL,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_Off_Delay_Time,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_Off_Signal_Type,
    TCON_TAB_CSOT_V390HZ1_Power_Sequence_Off_NUMS
} E_TCON_CSOT_V390HZ1_Power_Sequence_Off_TYPE;

/*************************************************************************************************************/

typedef enum
{
    TCON_TAB_CMO_V390HJ1_Init_ALL,
    TCON_TAB_CMO_V390HJ1_Init_NUMS
} E_TCON_CMO_V390HJ1_Init_TYPE;

typedef enum
{
    TCON_TAB_CMO_V390HJ1_Init_GPIO_ALL,
    TCON_TAB_CMO_V390HJ1_Init_GPIO_NUMS
} E_TCON_CMO_V390HJ1_Init_GPIO_TYPE;

typedef enum
{
    TCON_TAB_CMO_V390HJ1_Init_SC_ALL,
    TCON_TAB_CMO_V390HJ1_Init_SC_NUMS
} E_TCON_CMO_V390HJ1_Init_SC_TYPE;

typedef enum
{
    TCON_TAB_CMO_V390HJ1_Init_MOD_ALL,
    TCON_TAB_CMO_V390HJ1_Init_MOD_NUMS
} E_TCON_CMO_V390HJ1_Init_MOD_TYPE;

typedef enum
{
    TCON_TAB_CMO_V390HJ1_Power_Sequence_On_ALL,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_On_Delay_Ready,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_On_Delay_Time,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_On_Signal_Type,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_On_NUMS
} E_TCON_CMO_V390HJ1_Power_Sequence_On_TYPE;

typedef enum
{
    TCON_TAB_CMO_V390HJ1_Power_Sequence_Off_ALL,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_Off_Delay_Ready,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_Off_Delay_Time,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_Off_Signal_Type,
    TCON_TAB_CMO_V390HJ1_Power_Sequence_Off_NUMS
} E_TCON_CMO_V390HJ1_Power_Sequence_Off_TYPE;



//-------------------------------------------------------------------------------------------------
// register define used for TCON table
//-------------------------------------------------------------------------------------------------

#define  REG_TC_GAMMA_00           (REG_TC_GAMMA_BASE + 0x00)
#define  REG_TC_GAMMA_01           (REG_TC_GAMMA_BASE + 0x01)
#define  REG_TC_GAMMA_02           (REG_TC_GAMMA_BASE + 0x02)
#define  REG_TC_GAMMA_03           (REG_TC_GAMMA_BASE + 0x03)
#define  REG_TC_GAMMA_04           (REG_TC_GAMMA_BASE + 0x04)
#define  REG_TC_GAMMA_05           (REG_TC_GAMMA_BASE + 0x05)
#define  REG_TC_GAMMA_06           (REG_TC_GAMMA_BASE + 0x06)
#define  REG_TC_GAMMA_07           (REG_TC_GAMMA_BASE + 0x07)
#define  REG_TC_GAMMA_08           (REG_TC_GAMMA_BASE + 0x08)
#define  REG_TC_GAMMA_09           (REG_TC_GAMMA_BASE + 0x09)
#define  REG_TC_GAMMA_0A           (REG_TC_GAMMA_BASE + 0x0A)
#define  REG_TC_GAMMA_0B           (REG_TC_GAMMA_BASE + 0x0B)
#define  REG_TC_GAMMA_0C           (REG_TC_GAMMA_BASE + 0x0C)
#define  REG_TC_GAMMA_0D           (REG_TC_GAMMA_BASE + 0x0D)
#define  REG_TC_GAMMA_0E           (REG_TC_GAMMA_BASE + 0x0E)
#define  REG_TC_GAMMA_0F           (REG_TC_GAMMA_BASE + 0x0F)
#define  REG_TC_GAMMA_10           (REG_TC_GAMMA_BASE + 0x10)
#define  REG_TC_GAMMA_11           (REG_TC_GAMMA_BASE + 0x11)
#define  REG_TC_GAMMA_12           (REG_TC_GAMMA_BASE + 0x12)
#define  REG_TC_GAMMA_13           (REG_TC_GAMMA_BASE + 0x13)
#define  REG_TC_GAMMA_14           (REG_TC_GAMMA_BASE + 0x14)
#define  REG_TC_GAMMA_15           (REG_TC_GAMMA_BASE + 0x15)
#define  REG_TC_GAMMA_16           (REG_TC_GAMMA_BASE + 0x16)
#define  REG_TC_GAMMA_17           (REG_TC_GAMMA_BASE + 0x17)
#define  REG_TC_GAMMA_18           (REG_TC_GAMMA_BASE + 0x18)
#define  REG_TC_GAMMA_19           (REG_TC_GAMMA_BASE + 0x19)
#define  REG_TC_GAMMA_1A           (REG_TC_GAMMA_BASE + 0x1A)
#define  REG_TC_GAMMA_1B           (REG_TC_GAMMA_BASE + 0x1B)
#define  REG_TC_GAMMA_1C           (REG_TC_GAMMA_BASE + 0x1C)
#define  REG_TC_GAMMA_1D           (REG_TC_GAMMA_BASE + 0x1D)
#define  REG_TC_GAMMA_1E           (REG_TC_GAMMA_BASE + 0x1E)
#define  REG_TC_GAMMA_1F           (REG_TC_GAMMA_BASE + 0x1F)
#define  REG_TC_GAMMA_20           (REG_TC_GAMMA_BASE + 0x20)
#define  REG_TC_GAMMA_21           (REG_TC_GAMMA_BASE + 0x21)
#define  REG_TC_GAMMA_22           (REG_TC_GAMMA_BASE + 0x22)
#define  REG_TC_GAMMA_23           (REG_TC_GAMMA_BASE + 0x23)
#define  REG_TC_GAMMA_24           (REG_TC_GAMMA_BASE + 0x24)
#define  REG_TC_GAMMA_25           (REG_TC_GAMMA_BASE + 0x25)
#define  REG_TC_GAMMA_26           (REG_TC_GAMMA_BASE + 0x26)
#define  REG_TC_GAMMA_27           (REG_TC_GAMMA_BASE + 0x27)
#define  REG_TC_GAMMA_28           (REG_TC_GAMMA_BASE + 0x28)
#define  REG_TC_GAMMA_29           (REG_TC_GAMMA_BASE + 0x29)
#define  REG_TC_GAMMA_2A           (REG_TC_GAMMA_BASE + 0x2A)
#define  REG_TC_GAMMA_2B           (REG_TC_GAMMA_BASE + 0x2B)
#define  REG_TC_GAMMA_2C           (REG_TC_GAMMA_BASE + 0x2C)
#define  REG_TC_GAMMA_2D           (REG_TC_GAMMA_BASE + 0x2D)
#define  REG_TC_GAMMA_2E           (REG_TC_GAMMA_BASE + 0x2E)
#define  REG_TC_GAMMA_2F           (REG_TC_GAMMA_BASE + 0x2F)
#define  REG_TC_GAMMA_30           (REG_TC_GAMMA_BASE + 0x30)
#define  REG_TC_GAMMA_31           (REG_TC_GAMMA_BASE + 0x31)
#define  REG_TC_GAMMA_32           (REG_TC_GAMMA_BASE + 0x32)
#define  REG_TC_GAMMA_33           (REG_TC_GAMMA_BASE + 0x33)
#define  REG_TC_GAMMA_34           (REG_TC_GAMMA_BASE + 0x34)
#define  REG_TC_GAMMA_35           (REG_TC_GAMMA_BASE + 0x35)
#define  REG_TC_GAMMA_36           (REG_TC_GAMMA_BASE + 0x36)
#define  REG_TC_GAMMA_37           (REG_TC_GAMMA_BASE + 0x37)
#define  REG_TC_GAMMA_38           (REG_TC_GAMMA_BASE + 0x38)
#define  REG_TC_GAMMA_39           (REG_TC_GAMMA_BASE + 0x39)
#define  REG_TC_GAMMA_3A           (REG_TC_GAMMA_BASE + 0x3A)
#define  REG_TC_GAMMA_3B           (REG_TC_GAMMA_BASE + 0x3B)
#define  REG_TC_GAMMA_3C           (REG_TC_GAMMA_BASE + 0x3C)
#define  REG_TC_GAMMA_3D           (REG_TC_GAMMA_BASE + 0x3D)
#define  REG_TC_GAMMA_3E           (REG_TC_GAMMA_BASE + 0x3E)
#define  REG_TC_GAMMA_3F           (REG_TC_GAMMA_BASE + 0x3F)

#define  REG_TC_CLK_GEN_00_L       (REG_TC_CLK_GEN_BASE + 0x00)
#define  REG_TC_CLK_GEN_00_H       (REG_TC_CLK_GEN_BASE + 0x01)
#define  REG_TC_CLK_GEN_01_L       (REG_TC_CLK_GEN_BASE + 0x02)
#define  REG_TC_CLK_GEN_01_H       (REG_TC_CLK_GEN_BASE + 0x03)
#define  REG_TC_CLK_GEN_02_L       (REG_TC_CLK_GEN_BASE + 0x04)
#define  REG_TC_CLK_GEN_02_H       (REG_TC_CLK_GEN_BASE + 0x05)
#define  REG_TC_CLK_GEN_03_L       (REG_TC_CLK_GEN_BASE + 0x06)
#define  REG_TC_CLK_GEN_03_H       (REG_TC_CLK_GEN_BASE + 0x07)
#define  REG_TC_CLK_GEN_04_L       (REG_TC_CLK_GEN_BASE + 0x08)
#define  REG_TC_CLK_GEN_04_H       (REG_TC_CLK_GEN_BASE + 0x09)
#define  REG_TC_CLK_GEN_05_L       (REG_TC_CLK_GEN_BASE + 0x0A)
#define  REG_TC_CLK_GEN_05_H       (REG_TC_CLK_GEN_BASE + 0x0B)
#define  REG_TC_CLK_GEN_06_L       (REG_TC_CLK_GEN_BASE + 0x0C)
#define  REG_TC_CLK_GEN_06_H       (REG_TC_CLK_GEN_BASE + 0x0D)
#define  REG_TC_CLK_GEN_07_L       (REG_TC_CLK_GEN_BASE + 0x0E)
#define  REG_TC_CLK_GEN_07_H       (REG_TC_CLK_GEN_BASE + 0x0F)
#define  REG_TC_CLK_GEN_08_L       (REG_TC_CLK_GEN_BASE + 0x10)
#define  REG_TC_CLK_GEN_08_H       (REG_TC_CLK_GEN_BASE + 0x11)
#define  REG_TC_CLK_GEN_09_L       (REG_TC_CLK_GEN_BASE + 0x12)
#define  REG_TC_CLK_GEN_09_H       (REG_TC_CLK_GEN_BASE + 0x13)
#define  REG_TC_CLK_GEN_0A_L       (REG_TC_CLK_GEN_BASE + 0x14)
#define  REG_TC_CLK_GEN_0A_H       (REG_TC_CLK_GEN_BASE + 0x15)
#define  REG_TC_CLK_GEN_0B_L       (REG_TC_CLK_GEN_BASE + 0x16)
#define  REG_TC_CLK_GEN_0B_H       (REG_TC_CLK_GEN_BASE + 0x17)
#define  REG_TC_CLK_GEN_0C_L       (REG_TC_CLK_GEN_BASE + 0x18)
#define  REG_TC_CLK_GEN_0C_H       (REG_TC_CLK_GEN_BASE + 0x19)
#define  REG_TC_CLK_GEN_0D_L       (REG_TC_CLK_GEN_BASE + 0x1A)
#define  REG_TC_CLK_GEN_0D_H       (REG_TC_CLK_GEN_BASE + 0x1B)
#define  REG_TC_CLK_GEN_0E_L       (REG_TC_CLK_GEN_BASE + 0x1C)
#define  REG_TC_CLK_GEN_0E_H       (REG_TC_CLK_GEN_BASE + 0x1D)
#define  REG_TC_CLK_GEN_0F_L       (REG_TC_CLK_GEN_BASE + 0x1E)
#define  REG_TC_CLK_GEN_0F_H       (REG_TC_CLK_GEN_BASE + 0x1F)
#define  REG_TC_CLK_GEN_10_L       (REG_TC_CLK_GEN_BASE + 0x20)
#define  REG_TC_CLK_GEN_10_H       (REG_TC_CLK_GEN_BASE + 0x21)
#define  REG_TC_CLK_GEN_11_L       (REG_TC_CLK_GEN_BASE + 0x22)
#define  REG_TC_CLK_GEN_11_H       (REG_TC_CLK_GEN_BASE + 0x23)
#define  REG_TC_CLK_GEN_12_L       (REG_TC_CLK_GEN_BASE + 0x24)
#define  REG_TC_CLK_GEN_12_H       (REG_TC_CLK_GEN_BASE + 0x25)
#define  REG_TC_CLK_GEN_13_L       (REG_TC_CLK_GEN_BASE + 0x26)
#define  REG_TC_CLK_GEN_13_H       (REG_TC_CLK_GEN_BASE + 0x27)
#define  REG_TC_CLK_GEN_14_L       (REG_TC_CLK_GEN_BASE + 0x28)
#define  REG_TC_CLK_GEN_14_H       (REG_TC_CLK_GEN_BASE + 0x29)
#define  REG_TC_CLK_GEN_15_L       (REG_TC_CLK_GEN_BASE + 0x2A)
#define  REG_TC_CLK_GEN_15_H       (REG_TC_CLK_GEN_BASE + 0x2B)
#define  REG_TC_CLK_GEN_16_L       (REG_TC_CLK_GEN_BASE + 0x2C)
#define  REG_TC_CLK_GEN_16_H       (REG_TC_CLK_GEN_BASE + 0x2D)
#define  REG_TC_CLK_GEN_17_L       (REG_TC_CLK_GEN_BASE + 0x2E)
#define  REG_TC_CLK_GEN_17_H       (REG_TC_CLK_GEN_BASE + 0x2F)
#define  REG_TC_CLK_GEN_18_L       (REG_TC_CLK_GEN_BASE + 0x30)
#define  REG_TC_CLK_GEN_18_H       (REG_TC_CLK_GEN_BASE + 0x31)
#define  REG_TC_CLK_GEN_19_L       (REG_TC_CLK_GEN_BASE + 0x32)
#define  REG_TC_CLK_GEN_19_H       (REG_TC_CLK_GEN_BASE + 0x33)
#define  REG_TC_CLK_GEN_1A_L       (REG_TC_CLK_GEN_BASE + 0x34)
#define  REG_TC_CLK_GEN_1A_H       (REG_TC_CLK_GEN_BASE + 0x35)
#define  REG_TC_CLK_GEN_1B_L       (REG_TC_CLK_GEN_BASE + 0x36)
#define  REG_TC_CLK_GEN_1B_H       (REG_TC_CLK_GEN_BASE + 0x37)
#define  REG_TC_CLK_GEN_1C_L       (REG_TC_CLK_GEN_BASE + 0x38)
#define  REG_TC_CLK_GEN_1C_H       (REG_TC_CLK_GEN_BASE + 0x39)
#define  REG_TC_CLK_GEN_1D_L       (REG_TC_CLK_GEN_BASE + 0x3A)
#define  REG_TC_CLK_GEN_1D_H       (REG_TC_CLK_GEN_BASE + 0x3B)
#define  REG_TC_CLK_GEN_1E_L       (REG_TC_CLK_GEN_BASE + 0x3C)
#define  REG_TC_CLK_GEN_1E_H       (REG_TC_CLK_GEN_BASE + 0x3D)
#define  REG_TC_CLK_GEN_1F_L       (REG_TC_CLK_GEN_BASE + 0x3E)
#define  REG_TC_CLK_GEN_1F_H       (REG_TC_CLK_GEN_BASE + 0x3F)
#define  REG_TC_CLK_GEN_20_L       (REG_TC_CLK_GEN_BASE + 0x40)
#define  REG_TC_CLK_GEN_20_H       (REG_TC_CLK_GEN_BASE + 0x41)
#define  REG_TC_CLK_GEN_21_L       (REG_TC_CLK_GEN_BASE + 0x42)
#define  REG_TC_CLK_GEN_21_H       (REG_TC_CLK_GEN_BASE + 0x43)
#define  REG_TC_CLK_GEN_22_L       (REG_TC_CLK_GEN_BASE + 0x44)
#define  REG_TC_CLK_GEN_22_H       (REG_TC_CLK_GEN_BASE + 0x45)
#define  REG_TC_CLK_GEN_23_L       (REG_TC_CLK_GEN_BASE + 0x46)
#define  REG_TC_CLK_GEN_23_H       (REG_TC_CLK_GEN_BASE + 0x47)
#define  REG_TC_CLK_GEN_24_L       (REG_TC_CLK_GEN_BASE + 0x48)
#define  REG_TC_CLK_GEN_24_H       (REG_TC_CLK_GEN_BASE + 0x49)
#define  REG_TC_CLK_GEN_25_L       (REG_TC_CLK_GEN_BASE + 0x4A)
#define  REG_TC_CLK_GEN_25_H       (REG_TC_CLK_GEN_BASE + 0x4B)
#define  REG_TC_CLK_GEN_26_L       (REG_TC_CLK_GEN_BASE + 0x4C)
#define  REG_TC_CLK_GEN_26_H       (REG_TC_CLK_GEN_BASE + 0x4D)
#define  REG_TC_CLK_GEN_27_L       (REG_TC_CLK_GEN_BASE + 0x4E)
#define  REG_TC_CLK_GEN_27_H       (REG_TC_CLK_GEN_BASE + 0x4F)
#define  REG_TC_CLK_GEN_28_L       (REG_TC_CLK_GEN_BASE + 0x50)
#define  REG_TC_CLK_GEN_28_H       (REG_TC_CLK_GEN_BASE + 0x51)
#define  REG_TC_CLK_GEN_29_L       (REG_TC_CLK_GEN_BASE + 0x52)
#define  REG_TC_CLK_GEN_29_H       (REG_TC_CLK_GEN_BASE + 0x53)
#define  REG_TC_CLK_GEN_2A_L       (REG_TC_CLK_GEN_BASE + 0x54)
#define  REG_TC_CLK_GEN_2A_H       (REG_TC_CLK_GEN_BASE + 0x55)
#define  REG_TC_CLK_GEN_2B_L       (REG_TC_CLK_GEN_BASE + 0x56)
#define  REG_TC_CLK_GEN_2B_H       (REG_TC_CLK_GEN_BASE + 0x57)
#define  REG_TC_CLK_GEN_2C_L       (REG_TC_CLK_GEN_BASE + 0x58)
#define  REG_TC_CLK_GEN_2C_H       (REG_TC_CLK_GEN_BASE + 0x59)
#define  REG_TC_CLK_GEN_2D_L       (REG_TC_CLK_GEN_BASE + 0x5A)
#define  REG_TC_CLK_GEN_2D_H       (REG_TC_CLK_GEN_BASE + 0x5B)
#define  REG_TC_CLK_GEN_2E_L       (REG_TC_CLK_GEN_BASE + 0x5C)
#define  REG_TC_CLK_GEN_2E_H       (REG_TC_CLK_GEN_BASE + 0x5D)
#define  REG_TC_CLK_GEN_2F_L       (REG_TC_CLK_GEN_BASE + 0x5E)
#define  REG_TC_CLK_GEN_2F_H       (REG_TC_CLK_GEN_BASE + 0x5F)
#define  REG_TC_CLK_GEN_30_L       (REG_TC_CLK_GEN_BASE + 0x60)
#define  REG_TC_CLK_GEN_30_H       (REG_TC_CLK_GEN_BASE + 0x61)
#define  REG_TC_CLK_GEN_31_L       (REG_TC_CLK_GEN_BASE + 0x62)
#define  REG_TC_CLK_GEN_31_H       (REG_TC_CLK_GEN_BASE + 0x63)
#define  REG_TC_CLK_GEN_32_L       (REG_TC_CLK_GEN_BASE + 0x64)
#define  REG_TC_CLK_GEN_32_H       (REG_TC_CLK_GEN_BASE + 0x65)
#define  REG_TC_CLK_GEN_33_L       (REG_TC_CLK_GEN_BASE + 0x66)
#define  REG_TC_CLK_GEN_33_H       (REG_TC_CLK_GEN_BASE + 0x67)
#define  REG_TC_CLK_GEN_34_L       (REG_TC_CLK_GEN_BASE + 0x68)
#define  REG_TC_CLK_GEN_34_H       (REG_TC_CLK_GEN_BASE + 0x69)
#define  REG_TC_CLK_GEN_35_L       (REG_TC_CLK_GEN_BASE + 0x6A)
#define  REG_TC_CLK_GEN_35_H       (REG_TC_CLK_GEN_BASE + 0x6B)
#define  REG_TC_CLK_GEN_36_L       (REG_TC_CLK_GEN_BASE + 0x6C)
#define  REG_TC_CLK_GEN_36_H       (REG_TC_CLK_GEN_BASE + 0x6D)
#define  REG_TC_CLK_GEN_37_L       (REG_TC_CLK_GEN_BASE + 0x6E)
#define  REG_TC_CLK_GEN_37_H       (REG_TC_CLK_GEN_BASE + 0x6F)
#define  REG_TC_CLK_GEN_38_L       (REG_TC_CLK_GEN_BASE + 0x70)
#define  REG_TC_CLK_GEN_38_H       (REG_TC_CLK_GEN_BASE + 0x71)
#define  REG_TC_CLK_GEN_39_L       (REG_TC_CLK_GEN_BASE + 0x72)
#define  REG_TC_CLK_GEN_39_H       (REG_TC_CLK_GEN_BASE + 0x73)
#define  REG_TC_CLK_GEN_3A_L       (REG_TC_CLK_GEN_BASE + 0x74)
#define  REG_TC_CLK_GEN_3A_H       (REG_TC_CLK_GEN_BASE + 0x75)
#define  REG_TC_CLK_GEN_3B_L       (REG_TC_CLK_GEN_BASE + 0x76)
#define  REG_TC_CLK_GEN_3B_H       (REG_TC_CLK_GEN_BASE + 0x77)
#define  REG_TC_CLK_GEN_3C_L       (REG_TC_CLK_GEN_BASE + 0x78)
#define  REG_TC_CLK_GEN_3C_H       (REG_TC_CLK_GEN_BASE + 0x79)
#define  REG_TC_CLK_GEN_3D_L       (REG_TC_CLK_GEN_BASE + 0x7A)
#define  REG_TC_CLK_GEN_3D_H       (REG_TC_CLK_GEN_BASE + 0x7B)
#define  REG_TC_CLK_GEN_3E_L       (REG_TC_CLK_GEN_BASE + 0x7C)
#define  REG_TC_CLK_GEN_3E_H       (REG_TC_CLK_GEN_BASE + 0x7D)
#define  REG_TC_CLK_GEN_3F_L       (REG_TC_CLK_GEN_BASE + 0x7E)
#define  REG_TC_CLK_GEN_3F_H       (REG_TC_CLK_GEN_BASE + 0x7F)
#define  REG_TC_CLK_GEN_40_L       (REG_TC_CLK_GEN_BASE + 0x80)
#define  REG_TC_CLK_GEN_40_H       (REG_TC_CLK_GEN_BASE + 0x81)
#define  REG_TC_CLK_GEN_41_L       (REG_TC_CLK_GEN_BASE + 0x82)
#define  REG_TC_CLK_GEN_41_H       (REG_TC_CLK_GEN_BASE + 0x83)
#define  REG_TC_CLK_GEN_42_L       (REG_TC_CLK_GEN_BASE + 0x84)
#define  REG_TC_CLK_GEN_42_H       (REG_TC_CLK_GEN_BASE + 0x85)
#define  REG_TC_CLK_GEN_43_L       (REG_TC_CLK_GEN_BASE + 0x86)
#define  REG_TC_CLK_GEN_43_H       (REG_TC_CLK_GEN_BASE + 0x87)
#define  REG_TC_CLK_GEN_44_L       (REG_TC_CLK_GEN_BASE + 0x88)
#define  REG_TC_CLK_GEN_44_H       (REG_TC_CLK_GEN_BASE + 0x89)
#define  REG_TC_CLK_GEN_45_L       (REG_TC_CLK_GEN_BASE + 0x8A)
#define  REG_TC_CLK_GEN_45_H       (REG_TC_CLK_GEN_BASE + 0x8B)
#define  REG_TC_CLK_GEN_46_L       (REG_TC_CLK_GEN_BASE + 0x8C)
#define  REG_TC_CLK_GEN_46_H       (REG_TC_CLK_GEN_BASE + 0x8D)
#define  REG_TC_CLK_GEN_47_L       (REG_TC_CLK_GEN_BASE + 0x8E)
#define  REG_TC_CLK_GEN_47_H       (REG_TC_CLK_GEN_BASE + 0x8F)
#define  REG_TC_CLK_GEN_48_L       (REG_TC_CLK_GEN_BASE + 0x90)
#define  REG_TC_CLK_GEN_48_H       (REG_TC_CLK_GEN_BASE + 0x91)
#define  REG_TC_CLK_GEN_49_L       (REG_TC_CLK_GEN_BASE + 0x92)
#define  REG_TC_CLK_GEN_49_H       (REG_TC_CLK_GEN_BASE + 0x93)
#define  REG_TC_CLK_GEN_4A_L       (REG_TC_CLK_GEN_BASE + 0x94)
#define  REG_TC_CLK_GEN_4A_H       (REG_TC_CLK_GEN_BASE + 0x95)
#define  REG_TC_CLK_GEN_4B_L       (REG_TC_CLK_GEN_BASE + 0x96)
#define  REG_TC_CLK_GEN_4B_H       (REG_TC_CLK_GEN_BASE + 0x97)
#define  REG_TC_CLK_GEN_4C_L       (REG_TC_CLK_GEN_BASE + 0x98)
#define  REG_TC_CLK_GEN_4C_H       (REG_TC_CLK_GEN_BASE + 0x99)
#define  REG_TC_CLK_GEN_4D_L       (REG_TC_CLK_GEN_BASE + 0x9A)
#define  REG_TC_CLK_GEN_4D_H       (REG_TC_CLK_GEN_BASE + 0x9B)
#define  REG_TC_CLK_GEN_4E_L       (REG_TC_CLK_GEN_BASE + 0x9C)
#define  REG_TC_CLK_GEN_4E_H       (REG_TC_CLK_GEN_BASE + 0x9D)
#define  REG_TC_CLK_GEN_4F_L       (REG_TC_CLK_GEN_BASE + 0x9E)
#define  REG_TC_CLK_GEN_4F_H       (REG_TC_CLK_GEN_BASE + 0x9F)
#define  REG_TC_CLK_GEN_50_L       (REG_TC_CLK_GEN_BASE + 0xA0)
#define  REG_TC_CLK_GEN_50_H       (REG_TC_CLK_GEN_BASE + 0xA1)
#define  REG_TC_CLK_GEN_51_L       (REG_TC_CLK_GEN_BASE + 0xA2)
#define  REG_TC_CLK_GEN_51_H       (REG_TC_CLK_GEN_BASE + 0xA3)
#define  REG_TC_CLK_GEN_52_L       (REG_TC_CLK_GEN_BASE + 0xA4)
#define  REG_TC_CLK_GEN_52_H       (REG_TC_CLK_GEN_BASE + 0xA5)
#define  REG_TC_CLK_GEN_53_L       (REG_TC_CLK_GEN_BASE + 0xA6)
#define  REG_TC_CLK_GEN_53_H       (REG_TC_CLK_GEN_BASE + 0xA7)
#define  REG_TC_CLK_GEN_54_L       (REG_TC_CLK_GEN_BASE + 0xA8)
#define  REG_TC_CLK_GEN_54_H       (REG_TC_CLK_GEN_BASE + 0xA9)
#define  REG_TC_CLK_GEN_55_L       (REG_TC_CLK_GEN_BASE + 0xAA)
#define  REG_TC_CLK_GEN_55_H       (REG_TC_CLK_GEN_BASE + 0xAB)
#define  REG_TC_CLK_GEN_56_L       (REG_TC_CLK_GEN_BASE + 0xAC)
#define  REG_TC_CLK_GEN_56_H       (REG_TC_CLK_GEN_BASE + 0xAD)
#define  REG_TC_CLK_GEN_57_L       (REG_TC_CLK_GEN_BASE + 0xAE)
#define  REG_TC_CLK_GEN_57_H       (REG_TC_CLK_GEN_BASE + 0xAF)
#define  REG_TC_CLK_GEN_58_L       (REG_TC_CLK_GEN_BASE + 0xB0)
#define  REG_TC_CLK_GEN_58_H       (REG_TC_CLK_GEN_BASE + 0xB1)
#define  REG_TC_CLK_GEN_59_L       (REG_TC_CLK_GEN_BASE + 0xB2)
#define  REG_TC_CLK_GEN_59_H       (REG_TC_CLK_GEN_BASE + 0xB3)
#define  REG_TC_CLK_GEN_5A_L       (REG_TC_CLK_GEN_BASE + 0xB4)
#define  REG_TC_CLK_GEN_5A_H       (REG_TC_CLK_GEN_BASE + 0xB5)
#define  REG_TC_CLK_GEN_5B_L       (REG_TC_CLK_GEN_BASE + 0xB6)
#define  REG_TC_CLK_GEN_5B_H       (REG_TC_CLK_GEN_BASE + 0xB7)
#define  REG_TC_CLK_GEN_5C_L       (REG_TC_CLK_GEN_BASE + 0xB8)
#define  REG_TC_CLK_GEN_5C_H       (REG_TC_CLK_GEN_BASE + 0xB9)
#define  REG_TC_CLK_GEN_5D_L       (REG_TC_CLK_GEN_BASE + 0xBA)
#define  REG_TC_CLK_GEN_5D_H       (REG_TC_CLK_GEN_BASE + 0xBB)
#define  REG_TC_CLK_GEN_5E_L       (REG_TC_CLK_GEN_BASE + 0xBC)
#define  REG_TC_CLK_GEN_5E_H       (REG_TC_CLK_GEN_BASE + 0xBD)
#define  REG_TC_CLK_GEN_5F_L       (REG_TC_CLK_GEN_BASE + 0xBE)
#define  REG_TC_CLK_GEN_5F_H       (REG_TC_CLK_GEN_BASE + 0xBF)
#define  REG_TC_CLK_GEN_60_L       (REG_TC_CLK_GEN_BASE + 0xC0)
#define  REG_TC_CLK_GEN_60_H       (REG_TC_CLK_GEN_BASE + 0xC1)
#define  REG_TC_CLK_GEN_61_L       (REG_TC_CLK_GEN_BASE + 0xC2)
#define  REG_TC_CLK_GEN_61_H       (REG_TC_CLK_GEN_BASE + 0xC3)
#define  REG_TC_CLK_GEN_62_L       (REG_TC_CLK_GEN_BASE + 0xC4)
#define  REG_TC_CLK_GEN_62_H       (REG_TC_CLK_GEN_BASE + 0xC5)
#define  REG_TC_CLK_GEN_63_L       (REG_TC_CLK_GEN_BASE + 0xC6)
#define  REG_TC_CLK_GEN_63_H       (REG_TC_CLK_GEN_BASE + 0xC7)
#define  REG_TC_CLK_GEN_64_L       (REG_TC_CLK_GEN_BASE + 0xC8)
#define  REG_TC_CLK_GEN_64_H       (REG_TC_CLK_GEN_BASE + 0xC9)
#define  REG_TC_CLK_GEN_65_L       (REG_TC_CLK_GEN_BASE + 0xCA)
#define  REG_TC_CLK_GEN_65_H       (REG_TC_CLK_GEN_BASE + 0xCB)
#define  REG_TC_CLK_GEN_66_L       (REG_TC_CLK_GEN_BASE + 0xCC)
#define  REG_TC_CLK_GEN_66_H       (REG_TC_CLK_GEN_BASE + 0xCD)
#define  REG_TC_CLK_GEN_67_L       (REG_TC_CLK_GEN_BASE + 0xCE)
#define  REG_TC_CLK_GEN_67_H       (REG_TC_CLK_GEN_BASE + 0xCF)
#define  REG_TC_CLK_GEN_68_L       (REG_TC_CLK_GEN_BASE + 0xD0)
#define  REG_TC_CLK_GEN_68_H       (REG_TC_CLK_GEN_BASE + 0xD1)
#define  REG_TC_CLK_GEN_69_L       (REG_TC_CLK_GEN_BASE + 0xD2)
#define  REG_TC_CLK_GEN_69_H       (REG_TC_CLK_GEN_BASE + 0xD3)
#define  REG_TC_CLK_GEN_6A_L       (REG_TC_CLK_GEN_BASE + 0xD4)
#define  REG_TC_CLK_GEN_6A_H       (REG_TC_CLK_GEN_BASE + 0xD5)
#define  REG_TC_CLK_GEN_6B_L       (REG_TC_CLK_GEN_BASE + 0xD6)
#define  REG_TC_CLK_GEN_6B_H       (REG_TC_CLK_GEN_BASE + 0xD7)
#define  REG_TC_CLK_GEN_6C_L       (REG_TC_CLK_GEN_BASE + 0xD8)
#define  REG_TC_CLK_GEN_6C_H       (REG_TC_CLK_GEN_BASE + 0xD9)
#define  REG_TC_CLK_GEN_6D_L       (REG_TC_CLK_GEN_BASE + 0xDA)
#define  REG_TC_CLK_GEN_6D_H       (REG_TC_CLK_GEN_BASE + 0xDB)
#define  REG_TC_CLK_GEN_6E_L       (REG_TC_CLK_GEN_BASE + 0xDC)
#define  REG_TC_CLK_GEN_6E_H       (REG_TC_CLK_GEN_BASE + 0xDD)
#define  REG_TC_CLK_GEN_6F_L       (REG_TC_CLK_GEN_BASE + 0xDE)
#define  REG_TC_CLK_GEN_6F_H       (REG_TC_CLK_GEN_BASE + 0xDF)
#define  REG_TC_CLK_GEN_70_L       (REG_TC_CLK_GEN_BASE + 0xE0)
#define  REG_TC_CLK_GEN_70_H       (REG_TC_CLK_GEN_BASE + 0xE1)
#define  REG_TC_CLK_GEN_71_L       (REG_TC_CLK_GEN_BASE + 0xE2)
#define  REG_TC_CLK_GEN_71_H       (REG_TC_CLK_GEN_BASE + 0xE3)
#define  REG_TC_CLK_GEN_72_L       (REG_TC_CLK_GEN_BASE + 0xE4)
#define  REG_TC_CLK_GEN_72_H       (REG_TC_CLK_GEN_BASE + 0xE5)
#define  REG_TC_CLK_GEN_73_L       (REG_TC_CLK_GEN_BASE + 0xE6)
#define  REG_TC_CLK_GEN_73_H       (REG_TC_CLK_GEN_BASE + 0xE7)
#define  REG_TC_CLK_GEN_74_L       (REG_TC_CLK_GEN_BASE + 0xE8)
#define  REG_TC_CLK_GEN_74_H       (REG_TC_CLK_GEN_BASE + 0xE9)
#define  REG_TC_CLK_GEN_75_L       (REG_TC_CLK_GEN_BASE + 0xEA)
#define  REG_TC_CLK_GEN_75_H       (REG_TC_CLK_GEN_BASE + 0xEB)
#define  REG_TC_CLK_GEN_76_L       (REG_TC_CLK_GEN_BASE + 0xEC)
#define  REG_TC_CLK_GEN_76_H       (REG_TC_CLK_GEN_BASE + 0xED)
#define  REG_TC_CLK_GEN_77_L       (REG_TC_CLK_GEN_BASE + 0xEE)
#define  REG_TC_CLK_GEN_77_H       (REG_TC_CLK_GEN_BASE + 0xEF)
#define  REG_TC_CLK_GEN_78_L       (REG_TC_CLK_GEN_BASE + 0xF0)
#define  REG_TC_CLK_GEN_78_H       (REG_TC_CLK_GEN_BASE + 0xF1)
#define  REG_TC_CLK_GEN_79_L       (REG_TC_CLK_GEN_BASE + 0xF2)
#define  REG_TC_CLK_GEN_79_H       (REG_TC_CLK_GEN_BASE + 0xF3)
#define  REG_TC_CLK_GEN_7A_L       (REG_TC_CLK_GEN_BASE + 0xF4)
#define  REG_TC_CLK_GEN_7A_H       (REG_TC_CLK_GEN_BASE + 0xF5)
#define  REG_TC_CLK_GEN_7B_L       (REG_TC_CLK_GEN_BASE + 0xF6)
#define  REG_TC_CLK_GEN_7B_H       (REG_TC_CLK_GEN_BASE + 0xF7)
#define  REG_TC_CLK_GEN_7C_L       (REG_TC_CLK_GEN_BASE + 0xF8)
#define  REG_TC_CLK_GEN_7C_H       (REG_TC_CLK_GEN_BASE + 0xF9)
#define  REG_TC_CLK_GEN_7D_L       (REG_TC_CLK_GEN_BASE + 0xFA)
#define  REG_TC_CLK_GEN_7D_H       (REG_TC_CLK_GEN_BASE + 0xFB)
#define  REG_TC_CLK_GEN_7E_L       (REG_TC_CLK_GEN_BASE + 0xFC)
#define  REG_TC_CLK_GEN_7E_H       (REG_TC_CLK_GEN_BASE + 0xFD)
#define  REG_TC_CLK_GEN_7F_L       (REG_TC_CLK_GEN_BASE + 0xFE)
#define  REG_TC_CLK_GEN_7F_H       (REG_TC_CLK_GEN_BASE + 0xFF)

#define  REG_TC_CHIP_TOP_00_L       (REG_TC_CHIP_TOP_BASE + 0x00)
#define  REG_TC_CHIP_TOP_00_H       (REG_TC_CHIP_TOP_BASE + 0x01)
#define  REG_TC_CHIP_TOP_01_L       (REG_TC_CHIP_TOP_BASE + 0x02)
#define  REG_TC_CHIP_TOP_01_H       (REG_TC_CHIP_TOP_BASE + 0x03)
#define  REG_TC_CHIP_TOP_02_L       (REG_TC_CHIP_TOP_BASE + 0x04)
#define  REG_TC_CHIP_TOP_02_H       (REG_TC_CHIP_TOP_BASE + 0x05)
#define  REG_TC_CHIP_TOP_03_L       (REG_TC_CHIP_TOP_BASE + 0x06)
#define  REG_TC_CHIP_TOP_03_H       (REG_TC_CHIP_TOP_BASE + 0x07)
#define  REG_TC_CHIP_TOP_04_L       (REG_TC_CHIP_TOP_BASE + 0x08)
#define  REG_TC_CHIP_TOP_04_H       (REG_TC_CHIP_TOP_BASE + 0x09)
#define  REG_TC_CHIP_TOP_05_L       (REG_TC_CHIP_TOP_BASE + 0x0A)
#define  REG_TC_CHIP_TOP_05_H       (REG_TC_CHIP_TOP_BASE + 0x0B)
#define  REG_TC_CHIP_TOP_06_L       (REG_TC_CHIP_TOP_BASE + 0x0C)
#define  REG_TC_CHIP_TOP_06_H       (REG_TC_CHIP_TOP_BASE + 0x0D)
#define  REG_TC_CHIP_TOP_07_L       (REG_TC_CHIP_TOP_BASE + 0x0E)
#define  REG_TC_CHIP_TOP_07_H       (REG_TC_CHIP_TOP_BASE + 0x0F)
#define  REG_TC_CHIP_TOP_08_L       (REG_TC_CHIP_TOP_BASE + 0x10)
#define  REG_TC_CHIP_TOP_08_H       (REG_TC_CHIP_TOP_BASE + 0x11)
#define  REG_TC_CHIP_TOP_09_L       (REG_TC_CHIP_TOP_BASE + 0x12)
#define  REG_TC_CHIP_TOP_09_H       (REG_TC_CHIP_TOP_BASE + 0x13)
#define  REG_TC_CHIP_TOP_0A_L       (REG_TC_CHIP_TOP_BASE + 0x14)
#define  REG_TC_CHIP_TOP_0A_H       (REG_TC_CHIP_TOP_BASE + 0x15)
#define  REG_TC_CHIP_TOP_0B_L       (REG_TC_CHIP_TOP_BASE + 0x16)
#define  REG_TC_CHIP_TOP_0B_H       (REG_TC_CHIP_TOP_BASE + 0x17)
#define  REG_TC_CHIP_TOP_0C_L       (REG_TC_CHIP_TOP_BASE + 0x18)
#define  REG_TC_CHIP_TOP_0C_H       (REG_TC_CHIP_TOP_BASE + 0x19)
#define  REG_TC_CHIP_TOP_0D_L       (REG_TC_CHIP_TOP_BASE + 0x1A)
#define  REG_TC_CHIP_TOP_0D_H       (REG_TC_CHIP_TOP_BASE + 0x1B)
#define  REG_TC_CHIP_TOP_0E_L       (REG_TC_CHIP_TOP_BASE + 0x1C)
#define  REG_TC_CHIP_TOP_0E_H       (REG_TC_CHIP_TOP_BASE + 0x1D)
#define  REG_TC_CHIP_TOP_0F_L       (REG_TC_CHIP_TOP_BASE + 0x1E)
#define  REG_TC_CHIP_TOP_0F_H       (REG_TC_CHIP_TOP_BASE + 0x1F)
#define  REG_TC_CHIP_TOP_10_L       (REG_TC_CHIP_TOP_BASE + 0x20)
#define  REG_TC_CHIP_TOP_10_H       (REG_TC_CHIP_TOP_BASE + 0x21)
#define  REG_TC_CHIP_TOP_11_L       (REG_TC_CHIP_TOP_BASE + 0x22)
#define  REG_TC_CHIP_TOP_11_H       (REG_TC_CHIP_TOP_BASE + 0x23)
#define  REG_TC_CHIP_TOP_12_L       (REG_TC_CHIP_TOP_BASE + 0x24)
#define  REG_TC_CHIP_TOP_12_H       (REG_TC_CHIP_TOP_BASE + 0x25)
#define  REG_TC_CHIP_TOP_13_L       (REG_TC_CHIP_TOP_BASE + 0x26)
#define  REG_TC_CHIP_TOP_13_H       (REG_TC_CHIP_TOP_BASE + 0x27)
#define  REG_TC_CHIP_TOP_14_L       (REG_TC_CHIP_TOP_BASE + 0x28)
#define  REG_TC_CHIP_TOP_14_H       (REG_TC_CHIP_TOP_BASE + 0x29)
#define  REG_TC_CHIP_TOP_15_L       (REG_TC_CHIP_TOP_BASE + 0x2A)
#define  REG_TC_CHIP_TOP_15_H       (REG_TC_CHIP_TOP_BASE + 0x2B)
#define  REG_TC_CHIP_TOP_16_L       (REG_TC_CHIP_TOP_BASE + 0x2C)
#define  REG_TC_CHIP_TOP_16_H       (REG_TC_CHIP_TOP_BASE + 0x2D)
#define  REG_TC_CHIP_TOP_17_L       (REG_TC_CHIP_TOP_BASE + 0x2E)
#define  REG_TC_CHIP_TOP_17_H       (REG_TC_CHIP_TOP_BASE + 0x2F)
#define  REG_TC_CHIP_TOP_18_L       (REG_TC_CHIP_TOP_BASE + 0x30)
#define  REG_TC_CHIP_TOP_18_H       (REG_TC_CHIP_TOP_BASE + 0x31)
#define  REG_TC_CHIP_TOP_19_L       (REG_TC_CHIP_TOP_BASE + 0x32)
#define  REG_TC_CHIP_TOP_19_H       (REG_TC_CHIP_TOP_BASE + 0x33)
#define  REG_TC_CHIP_TOP_1A_L       (REG_TC_CHIP_TOP_BASE + 0x34)
#define  REG_TC_CHIP_TOP_1A_H       (REG_TC_CHIP_TOP_BASE + 0x35)
#define  REG_TC_CHIP_TOP_1B_L       (REG_TC_CHIP_TOP_BASE + 0x36)
#define  REG_TC_CHIP_TOP_1B_H       (REG_TC_CHIP_TOP_BASE + 0x37)
#define  REG_TC_CHIP_TOP_1C_L       (REG_TC_CHIP_TOP_BASE + 0x38)
#define  REG_TC_CHIP_TOP_1C_H       (REG_TC_CHIP_TOP_BASE + 0x39)
#define  REG_TC_CHIP_TOP_1D_L       (REG_TC_CHIP_TOP_BASE + 0x3A)
#define  REG_TC_CHIP_TOP_1D_H       (REG_TC_CHIP_TOP_BASE + 0x3B)
#define  REG_TC_CHIP_TOP_1E_L       (REG_TC_CHIP_TOP_BASE + 0x3C)
#define  REG_TC_CHIP_TOP_1E_H       (REG_TC_CHIP_TOP_BASE + 0x3D)
#define  REG_TC_CHIP_TOP_1F_L       (REG_TC_CHIP_TOP_BASE + 0x3E)
#define  REG_TC_CHIP_TOP_1F_H       (REG_TC_CHIP_TOP_BASE + 0x3F)
#define  REG_TC_CHIP_TOP_20_L       (REG_TC_CHIP_TOP_BASE + 0x40)
#define  REG_TC_CHIP_TOP_20_H       (REG_TC_CHIP_TOP_BASE + 0x41)
#define  REG_TC_CHIP_TOP_21_L       (REG_TC_CHIP_TOP_BASE + 0x42)
#define  REG_TC_CHIP_TOP_21_H       (REG_TC_CHIP_TOP_BASE + 0x43)
#define  REG_TC_CHIP_TOP_22_L       (REG_TC_CHIP_TOP_BASE + 0x44)
#define  REG_TC_CHIP_TOP_22_H       (REG_TC_CHIP_TOP_BASE + 0x45)
#define  REG_TC_CHIP_TOP_23_L       (REG_TC_CHIP_TOP_BASE + 0x46)
#define  REG_TC_CHIP_TOP_23_H       (REG_TC_CHIP_TOP_BASE + 0x47)
#define  REG_TC_CHIP_TOP_24_L       (REG_TC_CHIP_TOP_BASE + 0x48)
#define  REG_TC_CHIP_TOP_24_H       (REG_TC_CHIP_TOP_BASE + 0x49)
#define  REG_TC_CHIP_TOP_25_L       (REG_TC_CHIP_TOP_BASE + 0x4A)
#define  REG_TC_CHIP_TOP_25_H       (REG_TC_CHIP_TOP_BASE + 0x4B)
#define  REG_TC_CHIP_TOP_26_L       (REG_TC_CHIP_TOP_BASE + 0x4C)
#define  REG_TC_CHIP_TOP_26_H       (REG_TC_CHIP_TOP_BASE + 0x4D)
#define  REG_TC_CHIP_TOP_27_L       (REG_TC_CHIP_TOP_BASE + 0x4E)
#define  REG_TC_CHIP_TOP_27_H       (REG_TC_CHIP_TOP_BASE + 0x4F)
#define  REG_TC_CHIP_TOP_28_L       (REG_TC_CHIP_TOP_BASE + 0x50)
#define  REG_TC_CHIP_TOP_28_H       (REG_TC_CHIP_TOP_BASE + 0x51)
#define  REG_TC_CHIP_TOP_29_L       (REG_TC_CHIP_TOP_BASE + 0x52)
#define  REG_TC_CHIP_TOP_29_H       (REG_TC_CHIP_TOP_BASE + 0x53)
#define  REG_TC_CHIP_TOP_2A_L       (REG_TC_CHIP_TOP_BASE + 0x54)
#define  REG_TC_CHIP_TOP_2A_H       (REG_TC_CHIP_TOP_BASE + 0x55)
#define  REG_TC_CHIP_TOP_2B_L       (REG_TC_CHIP_TOP_BASE + 0x56)
#define  REG_TC_CHIP_TOP_2B_H       (REG_TC_CHIP_TOP_BASE + 0x57)
#define  REG_TC_CHIP_TOP_2C_L       (REG_TC_CHIP_TOP_BASE + 0x58)
#define  REG_TC_CHIP_TOP_2C_H       (REG_TC_CHIP_TOP_BASE + 0x59)
#define  REG_TC_CHIP_TOP_2D_L       (REG_TC_CHIP_TOP_BASE + 0x5A)
#define  REG_TC_CHIP_TOP_2D_H       (REG_TC_CHIP_TOP_BASE + 0x5B)
#define  REG_TC_CHIP_TOP_2E_L       (REG_TC_CHIP_TOP_BASE + 0x5C)
#define  REG_TC_CHIP_TOP_2E_H       (REG_TC_CHIP_TOP_BASE + 0x5D)
#define  REG_TC_CHIP_TOP_2F_L       (REG_TC_CHIP_TOP_BASE + 0x5E)
#define  REG_TC_CHIP_TOP_2F_H       (REG_TC_CHIP_TOP_BASE + 0x5F)
#define  REG_TC_CHIP_TOP_30_L       (REG_TC_CHIP_TOP_BASE + 0x60)
#define  REG_TC_CHIP_TOP_30_H       (REG_TC_CHIP_TOP_BASE + 0x61)
#define  REG_TC_CHIP_TOP_31_L       (REG_TC_CHIP_TOP_BASE + 0x62)
#define  REG_TC_CHIP_TOP_31_H       (REG_TC_CHIP_TOP_BASE + 0x63)
#define  REG_TC_CHIP_TOP_32_L       (REG_TC_CHIP_TOP_BASE + 0x64)
#define  REG_TC_CHIP_TOP_32_H       (REG_TC_CHIP_TOP_BASE + 0x65)
#define  REG_TC_CHIP_TOP_33_L       (REG_TC_CHIP_TOP_BASE + 0x66)
#define  REG_TC_CHIP_TOP_33_H       (REG_TC_CHIP_TOP_BASE + 0x67)
#define  REG_TC_CHIP_TOP_34_L       (REG_TC_CHIP_TOP_BASE + 0x68)
#define  REG_TC_CHIP_TOP_34_H       (REG_TC_CHIP_TOP_BASE + 0x69)
#define  REG_TC_CHIP_TOP_35_L       (REG_TC_CHIP_TOP_BASE + 0x6A)
#define  REG_TC_CHIP_TOP_35_H       (REG_TC_CHIP_TOP_BASE + 0x6B)
#define  REG_TC_CHIP_TOP_36_L       (REG_TC_CHIP_TOP_BASE + 0x6C)
#define  REG_TC_CHIP_TOP_36_H       (REG_TC_CHIP_TOP_BASE + 0x6D)
#define  REG_TC_CHIP_TOP_37_L       (REG_TC_CHIP_TOP_BASE + 0x6E)
#define  REG_TC_CHIP_TOP_37_H       (REG_TC_CHIP_TOP_BASE + 0x6F)
#define  REG_TC_CHIP_TOP_38_L       (REG_TC_CHIP_TOP_BASE + 0x70)
#define  REG_TC_CHIP_TOP_38_H       (REG_TC_CHIP_TOP_BASE + 0x71)
#define  REG_TC_CHIP_TOP_39_L       (REG_TC_CHIP_TOP_BASE + 0x72)
#define  REG_TC_CHIP_TOP_39_H       (REG_TC_CHIP_TOP_BASE + 0x73)
#define  REG_TC_CHIP_TOP_3A_L       (REG_TC_CHIP_TOP_BASE + 0x74)
#define  REG_TC_CHIP_TOP_3A_H       (REG_TC_CHIP_TOP_BASE + 0x75)
#define  REG_TC_CHIP_TOP_3B_L       (REG_TC_CHIP_TOP_BASE + 0x76)
#define  REG_TC_CHIP_TOP_3B_H       (REG_TC_CHIP_TOP_BASE + 0x77)
#define  REG_TC_CHIP_TOP_3C_L       (REG_TC_CHIP_TOP_BASE + 0x78)
#define  REG_TC_CHIP_TOP_3C_H       (REG_TC_CHIP_TOP_BASE + 0x79)
#define  REG_TC_CHIP_TOP_3D_L       (REG_TC_CHIP_TOP_BASE + 0x7A)
#define  REG_TC_CHIP_TOP_3D_H       (REG_TC_CHIP_TOP_BASE + 0x7B)
#define  REG_TC_CHIP_TOP_3E_L       (REG_TC_CHIP_TOP_BASE + 0x7C)
#define  REG_TC_CHIP_TOP_3E_H       (REG_TC_CHIP_TOP_BASE + 0x7D)
#define  REG_TC_CHIP_TOP_3F_L       (REG_TC_CHIP_TOP_BASE + 0x7E)
#define  REG_TC_CHIP_TOP_3F_H       (REG_TC_CHIP_TOP_BASE + 0x7F)
#define  REG_TC_CHIP_TOP_40_L       (REG_TC_CHIP_TOP_BASE + 0x80)
#define  REG_TC_CHIP_TOP_40_H       (REG_TC_CHIP_TOP_BASE + 0x81)
#define  REG_TC_CHIP_TOP_41_L       (REG_TC_CHIP_TOP_BASE + 0x82)
#define  REG_TC_CHIP_TOP_41_H       (REG_TC_CHIP_TOP_BASE + 0x83)
#define  REG_TC_CHIP_TOP_42_L       (REG_TC_CHIP_TOP_BASE + 0x84)
#define  REG_TC_CHIP_TOP_42_H       (REG_TC_CHIP_TOP_BASE + 0x85)
#define  REG_TC_CHIP_TOP_43_L       (REG_TC_CHIP_TOP_BASE + 0x86)
#define  REG_TC_CHIP_TOP_43_H       (REG_TC_CHIP_TOP_BASE + 0x87)
#define  REG_TC_CHIP_TOP_44_L       (REG_TC_CHIP_TOP_BASE + 0x88)
#define  REG_TC_CHIP_TOP_44_H       (REG_TC_CHIP_TOP_BASE + 0x89)
#define  REG_TC_CHIP_TOP_45_L       (REG_TC_CHIP_TOP_BASE + 0x8A)
#define  REG_TC_CHIP_TOP_45_H       (REG_TC_CHIP_TOP_BASE + 0x8B)
#define  REG_TC_CHIP_TOP_46_L       (REG_TC_CHIP_TOP_BASE + 0x8C)
#define  REG_TC_CHIP_TOP_46_H       (REG_TC_CHIP_TOP_BASE + 0x8D)
#define  REG_TC_CHIP_TOP_47_L       (REG_TC_CHIP_TOP_BASE + 0x8E)
#define  REG_TC_CHIP_TOP_47_H       (REG_TC_CHIP_TOP_BASE + 0x8F)
#define  REG_TC_CHIP_TOP_48_L       (REG_TC_CHIP_TOP_BASE + 0x90)
#define  REG_TC_CHIP_TOP_48_H       (REG_TC_CHIP_TOP_BASE + 0x91)
#define  REG_TC_CHIP_TOP_49_L       (REG_TC_CHIP_TOP_BASE + 0x92)
#define  REG_TC_CHIP_TOP_49_H       (REG_TC_CHIP_TOP_BASE + 0x93)
#define  REG_TC_CHIP_TOP_4A_L       (REG_TC_CHIP_TOP_BASE + 0x94)
#define  REG_TC_CHIP_TOP_4A_H       (REG_TC_CHIP_TOP_BASE + 0x95)
#define  REG_TC_CHIP_TOP_4B_L       (REG_TC_CHIP_TOP_BASE + 0x96)
#define  REG_TC_CHIP_TOP_4B_H       (REG_TC_CHIP_TOP_BASE + 0x97)
#define  REG_TC_CHIP_TOP_4C_L       (REG_TC_CHIP_TOP_BASE + 0x98)
#define  REG_TC_CHIP_TOP_4C_H       (REG_TC_CHIP_TOP_BASE + 0x99)
#define  REG_TC_CHIP_TOP_4D_L       (REG_TC_CHIP_TOP_BASE + 0x9A)
#define  REG_TC_CHIP_TOP_4D_H       (REG_TC_CHIP_TOP_BASE + 0x9B)
#define  REG_TC_CHIP_TOP_4E_L       (REG_TC_CHIP_TOP_BASE + 0x9C)
#define  REG_TC_CHIP_TOP_4E_H       (REG_TC_CHIP_TOP_BASE + 0x9D)
#define  REG_TC_CHIP_TOP_4F_L       (REG_TC_CHIP_TOP_BASE + 0x9E)
#define  REG_TC_CHIP_TOP_4F_H       (REG_TC_CHIP_TOP_BASE + 0x9F)
#define  REG_TC_CHIP_TOP_50_L       (REG_TC_CHIP_TOP_BASE + 0xA0)
#define  REG_TC_CHIP_TOP_50_H       (REG_TC_CHIP_TOP_BASE + 0xA1)
#define  REG_TC_CHIP_TOP_51_L       (REG_TC_CHIP_TOP_BASE + 0xA2)
#define  REG_TC_CHIP_TOP_51_H       (REG_TC_CHIP_TOP_BASE + 0xA3)
#define  REG_TC_CHIP_TOP_52_L       (REG_TC_CHIP_TOP_BASE + 0xA4)
#define  REG_TC_CHIP_TOP_52_H       (REG_TC_CHIP_TOP_BASE + 0xA5)
#define  REG_TC_CHIP_TOP_53_L       (REG_TC_CHIP_TOP_BASE + 0xA6)
#define  REG_TC_CHIP_TOP_53_H       (REG_TC_CHIP_TOP_BASE + 0xA7)
#define  REG_TC_CHIP_TOP_54_L       (REG_TC_CHIP_TOP_BASE + 0xA8)
#define  REG_TC_CHIP_TOP_54_H       (REG_TC_CHIP_TOP_BASE + 0xA9)
#define  REG_TC_CHIP_TOP_55_L       (REG_TC_CHIP_TOP_BASE + 0xAA)
#define  REG_TC_CHIP_TOP_55_H       (REG_TC_CHIP_TOP_BASE + 0xAB)
#define  REG_TC_CHIP_TOP_56_L       (REG_TC_CHIP_TOP_BASE + 0xAC)
#define  REG_TC_CHIP_TOP_56_H       (REG_TC_CHIP_TOP_BASE + 0xAD)
#define  REG_TC_CHIP_TOP_57_L       (REG_TC_CHIP_TOP_BASE + 0xAE)
#define  REG_TC_CHIP_TOP_57_H       (REG_TC_CHIP_TOP_BASE + 0xAF)
#define  REG_TC_CHIP_TOP_58_L       (REG_TC_CHIP_TOP_BASE + 0xB0)
#define  REG_TC_CHIP_TOP_58_H       (REG_TC_CHIP_TOP_BASE + 0xB1)
#define  REG_TC_CHIP_TOP_59_L       (REG_TC_CHIP_TOP_BASE + 0xB2)
#define  REG_TC_CHIP_TOP_59_H       (REG_TC_CHIP_TOP_BASE + 0xB3)
#define  REG_TC_CHIP_TOP_5A_L       (REG_TC_CHIP_TOP_BASE + 0xB4)
#define  REG_TC_CHIP_TOP_5A_H       (REG_TC_CHIP_TOP_BASE + 0xB5)
#define  REG_TC_CHIP_TOP_5B_L       (REG_TC_CHIP_TOP_BASE + 0xB6)
#define  REG_TC_CHIP_TOP_5B_H       (REG_TC_CHIP_TOP_BASE + 0xB7)
#define  REG_TC_CHIP_TOP_5C_L       (REG_TC_CHIP_TOP_BASE + 0xB8)
#define  REG_TC_CHIP_TOP_5C_H       (REG_TC_CHIP_TOP_BASE + 0xB9)
#define  REG_TC_CHIP_TOP_5D_L       (REG_TC_CHIP_TOP_BASE + 0xBA)
#define  REG_TC_CHIP_TOP_5D_H       (REG_TC_CHIP_TOP_BASE + 0xBB)
#define  REG_TC_CHIP_TOP_5E_L       (REG_TC_CHIP_TOP_BASE + 0xBC)
#define  REG_TC_CHIP_TOP_5E_H       (REG_TC_CHIP_TOP_BASE + 0xBD)
#define  REG_TC_CHIP_TOP_5F_L       (REG_TC_CHIP_TOP_BASE + 0xBE)
#define  REG_TC_CHIP_TOP_5F_H       (REG_TC_CHIP_TOP_BASE + 0xBF)
#define  REG_TC_CHIP_TOP_60_L       (REG_TC_CHIP_TOP_BASE + 0xC0)
#define  REG_TC_CHIP_TOP_60_H       (REG_TC_CHIP_TOP_BASE + 0xC1)
#define  REG_TC_CHIP_TOP_61_L       (REG_TC_CHIP_TOP_BASE + 0xC2)
#define  REG_TC_CHIP_TOP_61_H       (REG_TC_CHIP_TOP_BASE + 0xC3)
#define  REG_TC_CHIP_TOP_62_L       (REG_TC_CHIP_TOP_BASE + 0xC4)
#define  REG_TC_CHIP_TOP_62_H       (REG_TC_CHIP_TOP_BASE + 0xC5)
#define  REG_TC_CHIP_TOP_63_L       (REG_TC_CHIP_TOP_BASE + 0xC6)
#define  REG_TC_CHIP_TOP_63_H       (REG_TC_CHIP_TOP_BASE + 0xC7)
#define  REG_TC_CHIP_TOP_64_L       (REG_TC_CHIP_TOP_BASE + 0xC8)
#define  REG_TC_CHIP_TOP_64_H       (REG_TC_CHIP_TOP_BASE + 0xC9)
#define  REG_TC_CHIP_TOP_65_L       (REG_TC_CHIP_TOP_BASE + 0xCA)
#define  REG_TC_CHIP_TOP_65_H       (REG_TC_CHIP_TOP_BASE + 0xCB)
#define  REG_TC_CHIP_TOP_66_L       (REG_TC_CHIP_TOP_BASE + 0xCC)
#define  REG_TC_CHIP_TOP_66_H       (REG_TC_CHIP_TOP_BASE + 0xCD)
#define  REG_TC_CHIP_TOP_67_L       (REG_TC_CHIP_TOP_BASE + 0xCE)
#define  REG_TC_CHIP_TOP_67_H       (REG_TC_CHIP_TOP_BASE + 0xCF)
#define  REG_TC_CHIP_TOP_68_L       (REG_TC_CHIP_TOP_BASE + 0xD0)
#define  REG_TC_CHIP_TOP_68_H       (REG_TC_CHIP_TOP_BASE + 0xD1)
#define  REG_TC_CHIP_TOP_69_L       (REG_TC_CHIP_TOP_BASE + 0xD2)
#define  REG_TC_CHIP_TOP_69_H       (REG_TC_CHIP_TOP_BASE + 0xD3)
#define  REG_TC_CHIP_TOP_6A_L       (REG_TC_CHIP_TOP_BASE + 0xD4)
#define  REG_TC_CHIP_TOP_6A_H       (REG_TC_CHIP_TOP_BASE + 0xD5)
#define  REG_TC_CHIP_TOP_6B_L       (REG_TC_CHIP_TOP_BASE + 0xD6)
#define  REG_TC_CHIP_TOP_6B_H       (REG_TC_CHIP_TOP_BASE + 0xD7)
#define  REG_TC_CHIP_TOP_6C_L       (REG_TC_CHIP_TOP_BASE + 0xD8)
#define  REG_TC_CHIP_TOP_6C_H       (REG_TC_CHIP_TOP_BASE + 0xD9)
#define  REG_TC_CHIP_TOP_6D_L       (REG_TC_CHIP_TOP_BASE + 0xDA)
#define  REG_TC_CHIP_TOP_6D_H       (REG_TC_CHIP_TOP_BASE + 0xDB)
#define  REG_TC_CHIP_TOP_6E_L       (REG_TC_CHIP_TOP_BASE + 0xDC)
#define  REG_TC_CHIP_TOP_6E_H       (REG_TC_CHIP_TOP_BASE + 0xDD)
#define  REG_TC_CHIP_TOP_6F_L       (REG_TC_CHIP_TOP_BASE + 0xDE)
#define  REG_TC_CHIP_TOP_6F_H       (REG_TC_CHIP_TOP_BASE + 0xDF)
#define  REG_TC_CHIP_TOP_70_L       (REG_TC_CHIP_TOP_BASE + 0xE0)
#define  REG_TC_CHIP_TOP_70_H       (REG_TC_CHIP_TOP_BASE + 0xE1)
#define  REG_TC_CHIP_TOP_71_L       (REG_TC_CHIP_TOP_BASE + 0xE2)
#define  REG_TC_CHIP_TOP_71_H       (REG_TC_CHIP_TOP_BASE + 0xE3)
#define  REG_TC_CHIP_TOP_72_L       (REG_TC_CHIP_TOP_BASE + 0xE4)
#define  REG_TC_CHIP_TOP_72_H       (REG_TC_CHIP_TOP_BASE + 0xE5)
#define  REG_TC_CHIP_TOP_73_L       (REG_TC_CHIP_TOP_BASE + 0xE6)
#define  REG_TC_CHIP_TOP_73_H       (REG_TC_CHIP_TOP_BASE + 0xE7)
#define  REG_TC_CHIP_TOP_74_L       (REG_TC_CHIP_TOP_BASE + 0xE8)
#define  REG_TC_CHIP_TOP_74_H       (REG_TC_CHIP_TOP_BASE + 0xE9)
#define  REG_TC_CHIP_TOP_75_L       (REG_TC_CHIP_TOP_BASE + 0xEA)
#define  REG_TC_CHIP_TOP_75_H       (REG_TC_CHIP_TOP_BASE + 0xEB)
#define  REG_TC_CHIP_TOP_76_L       (REG_TC_CHIP_TOP_BASE + 0xEC)
#define  REG_TC_CHIP_TOP_76_H       (REG_TC_CHIP_TOP_BASE + 0xED)
#define  REG_TC_CHIP_TOP_77_L       (REG_TC_CHIP_TOP_BASE + 0xEE)
#define  REG_TC_CHIP_TOP_77_H       (REG_TC_CHIP_TOP_BASE + 0xEF)
#define  REG_TC_CHIP_TOP_78_L       (REG_TC_CHIP_TOP_BASE + 0xF0)
#define  REG_TC_CHIP_TOP_78_H       (REG_TC_CHIP_TOP_BASE + 0xF1)
#define  REG_TC_CHIP_TOP_79_L       (REG_TC_CHIP_TOP_BASE + 0xF2)
#define  REG_TC_CHIP_TOP_79_H       (REG_TC_CHIP_TOP_BASE + 0xF3)
#define  REG_TC_CHIP_TOP_7A_L       (REG_TC_CHIP_TOP_BASE + 0xF4)
#define  REG_TC_CHIP_TOP_7A_H       (REG_TC_CHIP_TOP_BASE + 0xF5)
#define  REG_TC_CHIP_TOP_7B_L       (REG_TC_CHIP_TOP_BASE + 0xF6)
#define  REG_TC_CHIP_TOP_7B_H       (REG_TC_CHIP_TOP_BASE + 0xF7)
#define  REG_TC_CHIP_TOP_7C_L       (REG_TC_CHIP_TOP_BASE + 0xF8)
#define  REG_TC_CHIP_TOP_7C_H       (REG_TC_CHIP_TOP_BASE + 0xF9)
#define  REG_TC_CHIP_TOP_7D_L       (REG_TC_CHIP_TOP_BASE + 0xFA)
#define  REG_TC_CHIP_TOP_7D_H       (REG_TC_CHIP_TOP_BASE + 0xFB)
#define  REG_TC_CHIP_TOP_7E_L       (REG_TC_CHIP_TOP_BASE + 0xFC)
#define  REG_TC_CHIP_TOP_7E_H       (REG_TC_CHIP_TOP_BASE + 0xFD)
#define  REG_TC_CHIP_TOP_7F_L       (REG_TC_CHIP_TOP_BASE + 0xFE)
#define  REG_TC_CHIP_TOP_7F_H       (REG_TC_CHIP_TOP_BASE + 0xFF)

#define  REG_TC_TCON_00_L       (REG_TC_TCON_BASE + 0x00)
#define  REG_TC_TCON_00_H       (REG_TC_TCON_BASE + 0x01)
#define  REG_TC_TCON_01_L       (REG_TC_TCON_BASE + 0x02)
#define  REG_TC_TCON_01_H       (REG_TC_TCON_BASE + 0x03)
#define  REG_TC_TCON_02_L       (REG_TC_TCON_BASE + 0x04)
#define  REG_TC_TCON_02_H       (REG_TC_TCON_BASE + 0x05)
#define  REG_TC_TCON_03_L       (REG_TC_TCON_BASE + 0x06)
#define  REG_TC_TCON_03_H       (REG_TC_TCON_BASE + 0x07)
#define  REG_TC_TCON_04_L       (REG_TC_TCON_BASE + 0x08)
#define  REG_TC_TCON_04_H       (REG_TC_TCON_BASE + 0x09)
#define  REG_TC_TCON_05_L       (REG_TC_TCON_BASE + 0x0A)
#define  REG_TC_TCON_05_H       (REG_TC_TCON_BASE + 0x0B)
#define  REG_TC_TCON_06_L       (REG_TC_TCON_BASE + 0x0C)
#define  REG_TC_TCON_06_H       (REG_TC_TCON_BASE + 0x0D)
#define  REG_TC_TCON_07_L       (REG_TC_TCON_BASE + 0x0E)
#define  REG_TC_TCON_07_H       (REG_TC_TCON_BASE + 0x0F)
#define  REG_TC_TCON_08_L       (REG_TC_TCON_BASE + 0x10)
#define  REG_TC_TCON_08_H       (REG_TC_TCON_BASE + 0x11)
#define  REG_TC_TCON_09_L       (REG_TC_TCON_BASE + 0x12)
#define  REG_TC_TCON_09_H       (REG_TC_TCON_BASE + 0x13)
#define  REG_TC_TCON_0A_L       (REG_TC_TCON_BASE + 0x14)
#define  REG_TC_TCON_0A_H       (REG_TC_TCON_BASE + 0x15)
#define  REG_TC_TCON_0B_L       (REG_TC_TCON_BASE + 0x16)
#define  REG_TC_TCON_0B_H       (REG_TC_TCON_BASE + 0x17)
#define  REG_TC_TCON_0C_L       (REG_TC_TCON_BASE + 0x18)
#define  REG_TC_TCON_0C_H       (REG_TC_TCON_BASE + 0x19)
#define  REG_TC_TCON_0D_L       (REG_TC_TCON_BASE + 0x1A)
#define  REG_TC_TCON_0D_H       (REG_TC_TCON_BASE + 0x1B)
#define  REG_TC_TCON_0E_L       (REG_TC_TCON_BASE + 0x1C)
#define  REG_TC_TCON_0E_H       (REG_TC_TCON_BASE + 0x1D)
#define  REG_TC_TCON_0F_L       (REG_TC_TCON_BASE + 0x1E)
#define  REG_TC_TCON_0F_H       (REG_TC_TCON_BASE + 0x1F)
#define  REG_TC_TCON_10_L       (REG_TC_TCON_BASE + 0x20)
#define  REG_TC_TCON_10_H       (REG_TC_TCON_BASE + 0x21)
#define  REG_TC_TCON_11_L       (REG_TC_TCON_BASE + 0x22)
#define  REG_TC_TCON_11_H       (REG_TC_TCON_BASE + 0x23)
#define  REG_TC_TCON_12_L       (REG_TC_TCON_BASE + 0x24)
#define  REG_TC_TCON_12_H       (REG_TC_TCON_BASE + 0x25)
#define  REG_TC_TCON_13_L       (REG_TC_TCON_BASE + 0x26)
#define  REG_TC_TCON_13_H       (REG_TC_TCON_BASE + 0x27)
#define  REG_TC_TCON_14_L       (REG_TC_TCON_BASE + 0x28)
#define  REG_TC_TCON_14_H       (REG_TC_TCON_BASE + 0x29)
#define  REG_TC_TCON_15_L       (REG_TC_TCON_BASE + 0x2A)
#define  REG_TC_TCON_15_H       (REG_TC_TCON_BASE + 0x2B)
#define  REG_TC_TCON_16_L       (REG_TC_TCON_BASE + 0x2C)
#define  REG_TC_TCON_16_H       (REG_TC_TCON_BASE + 0x2D)
#define  REG_TC_TCON_17_L       (REG_TC_TCON_BASE + 0x2E)
#define  REG_TC_TCON_17_H       (REG_TC_TCON_BASE + 0x2F)
#define  REG_TC_TCON_18_L       (REG_TC_TCON_BASE + 0x30)
#define  REG_TC_TCON_18_H       (REG_TC_TCON_BASE + 0x31)
#define  REG_TC_TCON_19_L       (REG_TC_TCON_BASE + 0x32)
#define  REG_TC_TCON_19_H       (REG_TC_TCON_BASE + 0x33)
#define  REG_TC_TCON_1A_L       (REG_TC_TCON_BASE + 0x34)
#define  REG_TC_TCON_1A_H       (REG_TC_TCON_BASE + 0x35)
#define  REG_TC_TCON_1B_L       (REG_TC_TCON_BASE + 0x36)
#define  REG_TC_TCON_1B_H       (REG_TC_TCON_BASE + 0x37)
#define  REG_TC_TCON_1C_L       (REG_TC_TCON_BASE + 0x38)
#define  REG_TC_TCON_1C_H       (REG_TC_TCON_BASE + 0x39)
#define  REG_TC_TCON_1D_L       (REG_TC_TCON_BASE + 0x3A)
#define  REG_TC_TCON_1D_H       (REG_TC_TCON_BASE + 0x3B)
#define  REG_TC_TCON_1E_L       (REG_TC_TCON_BASE + 0x3C)
#define  REG_TC_TCON_1E_H       (REG_TC_TCON_BASE + 0x3D)
#define  REG_TC_TCON_1F_L       (REG_TC_TCON_BASE + 0x3E)
#define  REG_TC_TCON_1F_H       (REG_TC_TCON_BASE + 0x3F)
#define  REG_TC_TCON_20_L       (REG_TC_TCON_BASE + 0x40)
#define  REG_TC_TCON_20_H       (REG_TC_TCON_BASE + 0x41)
#define  REG_TC_TCON_21_L       (REG_TC_TCON_BASE + 0x42)
#define  REG_TC_TCON_21_H       (REG_TC_TCON_BASE + 0x43)
#define  REG_TC_TCON_22_L       (REG_TC_TCON_BASE + 0x44)
#define  REG_TC_TCON_22_H       (REG_TC_TCON_BASE + 0x45)
#define  REG_TC_TCON_23_L       (REG_TC_TCON_BASE + 0x46)
#define  REG_TC_TCON_23_H       (REG_TC_TCON_BASE + 0x47)
#define  REG_TC_TCON_24_L       (REG_TC_TCON_BASE + 0x48)
#define  REG_TC_TCON_24_H       (REG_TC_TCON_BASE + 0x49)
#define  REG_TC_TCON_25_L       (REG_TC_TCON_BASE + 0x4A)
#define  REG_TC_TCON_25_H       (REG_TC_TCON_BASE + 0x4B)
#define  REG_TC_TCON_26_L       (REG_TC_TCON_BASE + 0x4C)
#define  REG_TC_TCON_26_H       (REG_TC_TCON_BASE + 0x4D)
#define  REG_TC_TCON_27_L       (REG_TC_TCON_BASE + 0x4E)
#define  REG_TC_TCON_27_H       (REG_TC_TCON_BASE + 0x4F)
#define  REG_TC_TCON_28_L       (REG_TC_TCON_BASE + 0x50)
#define  REG_TC_TCON_28_H       (REG_TC_TCON_BASE + 0x51)
#define  REG_TC_TCON_29_L       (REG_TC_TCON_BASE + 0x52)
#define  REG_TC_TCON_29_H       (REG_TC_TCON_BASE + 0x53)
#define  REG_TC_TCON_2A_L       (REG_TC_TCON_BASE + 0x54)
#define  REG_TC_TCON_2A_H       (REG_TC_TCON_BASE + 0x55)
#define  REG_TC_TCON_2B_L       (REG_TC_TCON_BASE + 0x56)
#define  REG_TC_TCON_2B_H       (REG_TC_TCON_BASE + 0x57)
#define  REG_TC_TCON_2C_L       (REG_TC_TCON_BASE + 0x58)
#define  REG_TC_TCON_2C_H       (REG_TC_TCON_BASE + 0x59)
#define  REG_TC_TCON_2D_L       (REG_TC_TCON_BASE + 0x5A)
#define  REG_TC_TCON_2D_H       (REG_TC_TCON_BASE + 0x5B)
#define  REG_TC_TCON_2E_L       (REG_TC_TCON_BASE + 0x5C)
#define  REG_TC_TCON_2E_H       (REG_TC_TCON_BASE + 0x5D)
#define  REG_TC_TCON_2F_L       (REG_TC_TCON_BASE + 0x5E)
#define  REG_TC_TCON_2F_H       (REG_TC_TCON_BASE + 0x5F)
#define  REG_TC_TCON_30_L       (REG_TC_TCON_BASE + 0x60)
#define  REG_TC_TCON_30_H       (REG_TC_TCON_BASE + 0x61)
#define  REG_TC_TCON_31_L       (REG_TC_TCON_BASE + 0x62)
#define  REG_TC_TCON_31_H       (REG_TC_TCON_BASE + 0x63)
#define  REG_TC_TCON_32_L       (REG_TC_TCON_BASE + 0x64)
#define  REG_TC_TCON_32_H       (REG_TC_TCON_BASE + 0x65)
#define  REG_TC_TCON_33_L       (REG_TC_TCON_BASE + 0x66)
#define  REG_TC_TCON_33_H       (REG_TC_TCON_BASE + 0x67)
#define  REG_TC_TCON_34_L       (REG_TC_TCON_BASE + 0x68)
#define  REG_TC_TCON_34_H       (REG_TC_TCON_BASE + 0x69)
#define  REG_TC_TCON_35_L       (REG_TC_TCON_BASE + 0x6A)
#define  REG_TC_TCON_35_H       (REG_TC_TCON_BASE + 0x6B)
#define  REG_TC_TCON_36_L       (REG_TC_TCON_BASE + 0x6C)
#define  REG_TC_TCON_36_H       (REG_TC_TCON_BASE + 0x6D)
#define  REG_TC_TCON_37_L       (REG_TC_TCON_BASE + 0x6E)
#define  REG_TC_TCON_37_H       (REG_TC_TCON_BASE + 0x6F)
#define  REG_TC_TCON_38_L       (REG_TC_TCON_BASE + 0x70)
#define  REG_TC_TCON_38_H       (REG_TC_TCON_BASE + 0x71)
#define  REG_TC_TCON_39_L       (REG_TC_TCON_BASE + 0x72)
#define  REG_TC_TCON_39_H       (REG_TC_TCON_BASE + 0x73)
#define  REG_TC_TCON_3A_L       (REG_TC_TCON_BASE + 0x74)
#define  REG_TC_TCON_3A_H       (REG_TC_TCON_BASE + 0x75)
#define  REG_TC_TCON_3B_L       (REG_TC_TCON_BASE + 0x76)
#define  REG_TC_TCON_3B_H       (REG_TC_TCON_BASE + 0x77)
#define  REG_TC_TCON_3C_L       (REG_TC_TCON_BASE + 0x78)
#define  REG_TC_TCON_3C_H       (REG_TC_TCON_BASE + 0x79)
#define  REG_TC_TCON_3D_L       (REG_TC_TCON_BASE + 0x7A)
#define  REG_TC_TCON_3D_H       (REG_TC_TCON_BASE + 0x7B)
#define  REG_TC_TCON_3E_L       (REG_TC_TCON_BASE + 0x7C)
#define  REG_TC_TCON_3E_H       (REG_TC_TCON_BASE + 0x7D)
#define  REG_TC_TCON_3F_L       (REG_TC_TCON_BASE + 0x7E)
#define  REG_TC_TCON_3F_H       (REG_TC_TCON_BASE + 0x7F)
#define  REG_TC_TCON_40_L       (REG_TC_TCON_BASE + 0x80)
#define  REG_TC_TCON_40_H       (REG_TC_TCON_BASE + 0x81)
#define  REG_TC_TCON_41_L       (REG_TC_TCON_BASE + 0x82)
#define  REG_TC_TCON_41_H       (REG_TC_TCON_BASE + 0x83)
#define  REG_TC_TCON_42_L       (REG_TC_TCON_BASE + 0x84)
#define  REG_TC_TCON_42_H       (REG_TC_TCON_BASE + 0x85)
#define  REG_TC_TCON_43_L       (REG_TC_TCON_BASE + 0x86)
#define  REG_TC_TCON_43_H       (REG_TC_TCON_BASE + 0x87)
#define  REG_TC_TCON_44_L       (REG_TC_TCON_BASE + 0x88)
#define  REG_TC_TCON_44_H       (REG_TC_TCON_BASE + 0x89)
#define  REG_TC_TCON_45_L       (REG_TC_TCON_BASE + 0x8A)
#define  REG_TC_TCON_45_H       (REG_TC_TCON_BASE + 0x8B)
#define  REG_TC_TCON_46_L       (REG_TC_TCON_BASE + 0x8C)
#define  REG_TC_TCON_46_H       (REG_TC_TCON_BASE + 0x8D)
#define  REG_TC_TCON_47_L       (REG_TC_TCON_BASE + 0x8E)
#define  REG_TC_TCON_47_H       (REG_TC_TCON_BASE + 0x8F)
#define  REG_TC_TCON_48_L       (REG_TC_TCON_BASE + 0x90)
#define  REG_TC_TCON_48_H       (REG_TC_TCON_BASE + 0x91)
#define  REG_TC_TCON_49_L       (REG_TC_TCON_BASE + 0x92)
#define  REG_TC_TCON_49_H       (REG_TC_TCON_BASE + 0x93)
#define  REG_TC_TCON_4A_L       (REG_TC_TCON_BASE + 0x94)
#define  REG_TC_TCON_4A_H       (REG_TC_TCON_BASE + 0x95)
#define  REG_TC_TCON_4B_L       (REG_TC_TCON_BASE + 0x96)
#define  REG_TC_TCON_4B_H       (REG_TC_TCON_BASE + 0x97)
#define  REG_TC_TCON_4C_L       (REG_TC_TCON_BASE + 0x98)
#define  REG_TC_TCON_4C_H       (REG_TC_TCON_BASE + 0x99)
#define  REG_TC_TCON_4D_L       (REG_TC_TCON_BASE + 0x9A)
#define  REG_TC_TCON_4D_H       (REG_TC_TCON_BASE + 0x9B)
#define  REG_TC_TCON_4E_L       (REG_TC_TCON_BASE + 0x9C)
#define  REG_TC_TCON_4E_H       (REG_TC_TCON_BASE + 0x9D)
#define  REG_TC_TCON_4F_L       (REG_TC_TCON_BASE + 0x9E)
#define  REG_TC_TCON_4F_H       (REG_TC_TCON_BASE + 0x9F)
#define  REG_TC_TCON_50_L       (REG_TC_TCON_BASE + 0xA0)
#define  REG_TC_TCON_50_H       (REG_TC_TCON_BASE + 0xA1)
#define  REG_TC_TCON_51_L       (REG_TC_TCON_BASE + 0xA2)
#define  REG_TC_TCON_51_H       (REG_TC_TCON_BASE + 0xA3)
#define  REG_TC_TCON_52_L       (REG_TC_TCON_BASE + 0xA4)
#define  REG_TC_TCON_52_H       (REG_TC_TCON_BASE + 0xA5)
#define  REG_TC_TCON_53_L       (REG_TC_TCON_BASE + 0xA6)
#define  REG_TC_TCON_53_H       (REG_TC_TCON_BASE + 0xA7)
#define  REG_TC_TCON_54_L       (REG_TC_TCON_BASE + 0xA8)
#define  REG_TC_TCON_54_H       (REG_TC_TCON_BASE + 0xA9)
#define  REG_TC_TCON_55_L       (REG_TC_TCON_BASE + 0xAA)
#define  REG_TC_TCON_55_H       (REG_TC_TCON_BASE + 0xAB)
#define  REG_TC_TCON_56_L       (REG_TC_TCON_BASE + 0xAC)
#define  REG_TC_TCON_56_H       (REG_TC_TCON_BASE + 0xAD)
#define  REG_TC_TCON_57_L       (REG_TC_TCON_BASE + 0xAE)
#define  REG_TC_TCON_57_H       (REG_TC_TCON_BASE + 0xAF)
#define  REG_TC_TCON_58_L       (REG_TC_TCON_BASE + 0xB0)
#define  REG_TC_TCON_58_H       (REG_TC_TCON_BASE + 0xB1)
#define  REG_TC_TCON_59_L       (REG_TC_TCON_BASE + 0xB2)
#define  REG_TC_TCON_59_H       (REG_TC_TCON_BASE + 0xB3)
#define  REG_TC_TCON_5A_L       (REG_TC_TCON_BASE + 0xB4)
#define  REG_TC_TCON_5A_H       (REG_TC_TCON_BASE + 0xB5)
#define  REG_TC_TCON_5B_L       (REG_TC_TCON_BASE + 0xB6)
#define  REG_TC_TCON_5B_H       (REG_TC_TCON_BASE + 0xB7)
#define  REG_TC_TCON_5C_L       (REG_TC_TCON_BASE + 0xB8)
#define  REG_TC_TCON_5C_H       (REG_TC_TCON_BASE + 0xB9)
#define  REG_TC_TCON_5D_L       (REG_TC_TCON_BASE + 0xBA)
#define  REG_TC_TCON_5D_H       (REG_TC_TCON_BASE + 0xBB)
#define  REG_TC_TCON_5E_L       (REG_TC_TCON_BASE + 0xBC)
#define  REG_TC_TCON_5E_H       (REG_TC_TCON_BASE + 0xBD)
#define  REG_TC_TCON_5F_L       (REG_TC_TCON_BASE + 0xBE)
#define  REG_TC_TCON_5F_H       (REG_TC_TCON_BASE + 0xBF)
#define  REG_TC_TCON_60_L       (REG_TC_TCON_BASE + 0xC0)
#define  REG_TC_TCON_60_H       (REG_TC_TCON_BASE + 0xC1)
#define  REG_TC_TCON_61_L       (REG_TC_TCON_BASE + 0xC2)
#define  REG_TC_TCON_61_H       (REG_TC_TCON_BASE + 0xC3)
#define  REG_TC_TCON_62_L       (REG_TC_TCON_BASE + 0xC4)
#define  REG_TC_TCON_62_H       (REG_TC_TCON_BASE + 0xC5)
#define  REG_TC_TCON_63_L       (REG_TC_TCON_BASE + 0xC6)
#define  REG_TC_TCON_63_H       (REG_TC_TCON_BASE + 0xC7)
#define  REG_TC_TCON_64_L       (REG_TC_TCON_BASE + 0xC8)
#define  REG_TC_TCON_64_H       (REG_TC_TCON_BASE + 0xC9)
#define  REG_TC_TCON_65_L       (REG_TC_TCON_BASE + 0xCA)
#define  REG_TC_TCON_65_H       (REG_TC_TCON_BASE + 0xCB)
#define  REG_TC_TCON_66_L       (REG_TC_TCON_BASE + 0xCC)
#define  REG_TC_TCON_66_H       (REG_TC_TCON_BASE + 0xCD)
#define  REG_TC_TCON_67_L       (REG_TC_TCON_BASE + 0xCE)
#define  REG_TC_TCON_67_H       (REG_TC_TCON_BASE + 0xCF)
#define  REG_TC_TCON_68_L       (REG_TC_TCON_BASE + 0xD0)
#define  REG_TC_TCON_68_H       (REG_TC_TCON_BASE + 0xD1)
#define  REG_TC_TCON_69_L       (REG_TC_TCON_BASE + 0xD2)
#define  REG_TC_TCON_69_H       (REG_TC_TCON_BASE + 0xD3)
#define  REG_TC_TCON_6A_L       (REG_TC_TCON_BASE + 0xD4)
#define  REG_TC_TCON_6A_H       (REG_TC_TCON_BASE + 0xD5)
#define  REG_TC_TCON_6B_L       (REG_TC_TCON_BASE + 0xD6)
#define  REG_TC_TCON_6B_H       (REG_TC_TCON_BASE + 0xD7)
#define  REG_TC_TCON_6C_L       (REG_TC_TCON_BASE + 0xD8)
#define  REG_TC_TCON_6C_H       (REG_TC_TCON_BASE + 0xD9)
#define  REG_TC_TCON_6D_L       (REG_TC_TCON_BASE + 0xDA)
#define  REG_TC_TCON_6D_H       (REG_TC_TCON_BASE + 0xDB)
#define  REG_TC_TCON_6E_L       (REG_TC_TCON_BASE + 0xDC)
#define  REG_TC_TCON_6E_H       (REG_TC_TCON_BASE + 0xDD)
#define  REG_TC_TCON_6F_L       (REG_TC_TCON_BASE + 0xDE)
#define  REG_TC_TCON_6F_H       (REG_TC_TCON_BASE + 0xDF)
#define  REG_TC_TCON_70_L       (REG_TC_TCON_BASE + 0xE0)
#define  REG_TC_TCON_70_H       (REG_TC_TCON_BASE + 0xE1)
#define  REG_TC_TCON_71_L       (REG_TC_TCON_BASE + 0xE2)
#define  REG_TC_TCON_71_H       (REG_TC_TCON_BASE + 0xE3)
#define  REG_TC_TCON_72_L       (REG_TC_TCON_BASE + 0xE4)
#define  REG_TC_TCON_72_H       (REG_TC_TCON_BASE + 0xE5)
#define  REG_TC_TCON_73_L       (REG_TC_TCON_BASE + 0xE6)
#define  REG_TC_TCON_73_H       (REG_TC_TCON_BASE + 0xE7)
#define  REG_TC_TCON_74_L       (REG_TC_TCON_BASE + 0xE8)
#define  REG_TC_TCON_74_H       (REG_TC_TCON_BASE + 0xE9)
#define  REG_TC_TCON_75_L       (REG_TC_TCON_BASE + 0xEA)
#define  REG_TC_TCON_75_H       (REG_TC_TCON_BASE + 0xEB)
#define  REG_TC_TCON_76_L       (REG_TC_TCON_BASE + 0xEC)
#define  REG_TC_TCON_76_H       (REG_TC_TCON_BASE + 0xED)
#define  REG_TC_TCON_77_L       (REG_TC_TCON_BASE + 0xEE)
#define  REG_TC_TCON_77_H       (REG_TC_TCON_BASE + 0xEF)
#define  REG_TC_TCON_78_L       (REG_TC_TCON_BASE + 0xF0)
#define  REG_TC_TCON_78_H       (REG_TC_TCON_BASE + 0xF1)
#define  REG_TC_TCON_79_L       (REG_TC_TCON_BASE + 0xF2)
#define  REG_TC_TCON_79_H       (REG_TC_TCON_BASE + 0xF3)
#define  REG_TC_TCON_7A_L       (REG_TC_TCON_BASE + 0xF4)
#define  REG_TC_TCON_7A_H       (REG_TC_TCON_BASE + 0xF5)
#define  REG_TC_TCON_7B_L       (REG_TC_TCON_BASE + 0xF6)
#define  REG_TC_TCON_7B_H       (REG_TC_TCON_BASE + 0xF7)
#define  REG_TC_TCON_7C_L       (REG_TC_TCON_BASE + 0xF8)
#define  REG_TC_TCON_7C_H       (REG_TC_TCON_BASE + 0xF9)
#define  REG_TC_TCON_7D_L       (REG_TC_TCON_BASE + 0xFA)
#define  REG_TC_TCON_7D_H       (REG_TC_TCON_BASE + 0xFB)
#define  REG_TC_TCON_7E_L       (REG_TC_TCON_BASE + 0xFC)
#define  REG_TC_TCON_7E_H       (REG_TC_TCON_BASE + 0xFD)
#define  REG_TC_TCON_7F_L       (REG_TC_TCON_BASE + 0xFE)
#define  REG_TC_TCON_7F_H       (REG_TC_TCON_BASE + 0xFF)

#define  REG_TC_LPLL_00_L       (REG_TC_LPLL_BASE + 0x00)
#define  REG_TC_LPLL_00_H       (REG_TC_LPLL_BASE + 0x01)
#define  REG_TC_LPLL_01_L       (REG_TC_LPLL_BASE + 0x02)
#define  REG_TC_LPLL_01_H       (REG_TC_LPLL_BASE + 0x03)
#define  REG_TC_LPLL_02_L       (REG_TC_LPLL_BASE + 0x04)
#define  REG_TC_LPLL_02_H       (REG_TC_LPLL_BASE + 0x05)
#define  REG_TC_LPLL_03_L       (REG_TC_LPLL_BASE + 0x06)
#define  REG_TC_LPLL_03_H       (REG_TC_LPLL_BASE + 0x07)
#define  REG_TC_LPLL_04_L       (REG_TC_LPLL_BASE + 0x08)
#define  REG_TC_LPLL_04_H       (REG_TC_LPLL_BASE + 0x09)
#define  REG_TC_LPLL_05_L       (REG_TC_LPLL_BASE + 0x0A)
#define  REG_TC_LPLL_05_H       (REG_TC_LPLL_BASE + 0x0B)
#define  REG_TC_LPLL_06_L       (REG_TC_LPLL_BASE + 0x0C)
#define  REG_TC_LPLL_06_H       (REG_TC_LPLL_BASE + 0x0D)
#define  REG_TC_LPLL_07_L       (REG_TC_LPLL_BASE + 0x0E)
#define  REG_TC_LPLL_07_H       (REG_TC_LPLL_BASE + 0x0F)
#define  REG_TC_LPLL_08_L       (REG_TC_LPLL_BASE + 0x10)
#define  REG_TC_LPLL_08_H       (REG_TC_LPLL_BASE + 0x11)
#define  REG_TC_LPLL_09_L       (REG_TC_LPLL_BASE + 0x12)
#define  REG_TC_LPLL_09_H       (REG_TC_LPLL_BASE + 0x13)
#define  REG_TC_LPLL_0A_L       (REG_TC_LPLL_BASE + 0x14)
#define  REG_TC_LPLL_0A_H       (REG_TC_LPLL_BASE + 0x15)
#define  REG_TC_LPLL_0B_L       (REG_TC_LPLL_BASE + 0x16)
#define  REG_TC_LPLL_0B_H       (REG_TC_LPLL_BASE + 0x17)
#define  REG_TC_LPLL_0C_L       (REG_TC_LPLL_BASE + 0x18)
#define  REG_TC_LPLL_0C_H       (REG_TC_LPLL_BASE + 0x19)
#define  REG_TC_LPLL_0D_L       (REG_TC_LPLL_BASE + 0x1A)
#define  REG_TC_LPLL_0D_H       (REG_TC_LPLL_BASE + 0x1B)
#define  REG_TC_LPLL_0E_L       (REG_TC_LPLL_BASE + 0x1C)
#define  REG_TC_LPLL_0E_H       (REG_TC_LPLL_BASE + 0x1D)
#define  REG_TC_LPLL_0F_L       (REG_TC_LPLL_BASE + 0x1E)
#define  REG_TC_LPLL_0F_H       (REG_TC_LPLL_BASE + 0x1F)
#define  REG_TC_LPLL_10_L       (REG_TC_LPLL_BASE + 0x20)
#define  REG_TC_LPLL_10_H       (REG_TC_LPLL_BASE + 0x21)
#define  REG_TC_LPLL_11_L       (REG_TC_LPLL_BASE + 0x22)
#define  REG_TC_LPLL_11_H       (REG_TC_LPLL_BASE + 0x23)
#define  REG_TC_LPLL_12_L       (REG_TC_LPLL_BASE + 0x24)
#define  REG_TC_LPLL_12_H       (REG_TC_LPLL_BASE + 0x25)
#define  REG_TC_LPLL_13_L       (REG_TC_LPLL_BASE + 0x26)
#define  REG_TC_LPLL_13_H       (REG_TC_LPLL_BASE + 0x27)
#define  REG_TC_LPLL_14_L       (REG_TC_LPLL_BASE + 0x28)
#define  REG_TC_LPLL_14_H       (REG_TC_LPLL_BASE + 0x29)
#define  REG_TC_LPLL_15_L       (REG_TC_LPLL_BASE + 0x2A)
#define  REG_TC_LPLL_15_H       (REG_TC_LPLL_BASE + 0x2B)
#define  REG_TC_LPLL_16_L       (REG_TC_LPLL_BASE + 0x2C)
#define  REG_TC_LPLL_16_H       (REG_TC_LPLL_BASE + 0x2D)
#define  REG_TC_LPLL_17_L       (REG_TC_LPLL_BASE + 0x2E)
#define  REG_TC_LPLL_17_H       (REG_TC_LPLL_BASE + 0x2F)
#define  REG_TC_LPLL_18_L       (REG_TC_LPLL_BASE + 0x30)
#define  REG_TC_LPLL_18_H       (REG_TC_LPLL_BASE + 0x31)
#define  REG_TC_LPLL_19_L       (REG_TC_LPLL_BASE + 0x32)
#define  REG_TC_LPLL_19_H       (REG_TC_LPLL_BASE + 0x33)
#define  REG_TC_LPLL_1A_L       (REG_TC_LPLL_BASE + 0x34)
#define  REG_TC_LPLL_1A_H       (REG_TC_LPLL_BASE + 0x35)
#define  REG_TC_LPLL_1B_L       (REG_TC_LPLL_BASE + 0x36)
#define  REG_TC_LPLL_1B_H       (REG_TC_LPLL_BASE + 0x37)
#define  REG_TC_LPLL_1C_L       (REG_TC_LPLL_BASE + 0x38)
#define  REG_TC_LPLL_1C_H       (REG_TC_LPLL_BASE + 0x39)
#define  REG_TC_LPLL_1D_L       (REG_TC_LPLL_BASE + 0x3A)
#define  REG_TC_LPLL_1D_H       (REG_TC_LPLL_BASE + 0x3B)
#define  REG_TC_LPLL_1E_L       (REG_TC_LPLL_BASE + 0x3C)
#define  REG_TC_LPLL_1E_H       (REG_TC_LPLL_BASE + 0x3D)
#define  REG_TC_LPLL_1F_L       (REG_TC_LPLL_BASE + 0x3E)
#define  REG_TC_LPLL_1F_H       (REG_TC_LPLL_BASE + 0x3F)
#define  REG_TC_LPLL_20_L       (REG_TC_LPLL_BASE + 0x40)
#define  REG_TC_LPLL_20_H       (REG_TC_LPLL_BASE + 0x41)
#define  REG_TC_LPLL_21_L       (REG_TC_LPLL_BASE + 0x42)
#define  REG_TC_LPLL_21_H       (REG_TC_LPLL_BASE + 0x43)
#define  REG_TC_LPLL_22_L       (REG_TC_LPLL_BASE + 0x44)
#define  REG_TC_LPLL_22_H       (REG_TC_LPLL_BASE + 0x45)
#define  REG_TC_LPLL_23_L       (REG_TC_LPLL_BASE + 0x46)
#define  REG_TC_LPLL_23_H       (REG_TC_LPLL_BASE + 0x47)
#define  REG_TC_LPLL_24_L       (REG_TC_LPLL_BASE + 0x48)
#define  REG_TC_LPLL_24_H       (REG_TC_LPLL_BASE + 0x49)
#define  REG_TC_LPLL_25_L       (REG_TC_LPLL_BASE + 0x4A)
#define  REG_TC_LPLL_25_H       (REG_TC_LPLL_BASE + 0x4B)
#define  REG_TC_LPLL_26_L       (REG_TC_LPLL_BASE + 0x4C)
#define  REG_TC_LPLL_26_H       (REG_TC_LPLL_BASE + 0x4D)
#define  REG_TC_LPLL_27_L       (REG_TC_LPLL_BASE + 0x4E)
#define  REG_TC_LPLL_27_H       (REG_TC_LPLL_BASE + 0x4F)
#define  REG_TC_LPLL_28_L       (REG_TC_LPLL_BASE + 0x50)
#define  REG_TC_LPLL_28_H       (REG_TC_LPLL_BASE + 0x51)
#define  REG_TC_LPLL_29_L       (REG_TC_LPLL_BASE + 0x52)
#define  REG_TC_LPLL_29_H       (REG_TC_LPLL_BASE + 0x53)
#define  REG_TC_LPLL_2A_L       (REG_TC_LPLL_BASE + 0x54)
#define  REG_TC_LPLL_2A_H       (REG_TC_LPLL_BASE + 0x55)
#define  REG_TC_LPLL_2B_L       (REG_TC_LPLL_BASE + 0x56)
#define  REG_TC_LPLL_2B_H       (REG_TC_LPLL_BASE + 0x57)
#define  REG_TC_LPLL_2C_L       (REG_TC_LPLL_BASE + 0x58)
#define  REG_TC_LPLL_2C_H       (REG_TC_LPLL_BASE + 0x59)
#define  REG_TC_LPLL_2D_L       (REG_TC_LPLL_BASE + 0x5A)
#define  REG_TC_LPLL_2D_H       (REG_TC_LPLL_BASE + 0x5B)
#define  REG_TC_LPLL_2E_L       (REG_TC_LPLL_BASE + 0x5C)
#define  REG_TC_LPLL_2E_H       (REG_TC_LPLL_BASE + 0x5D)
#define  REG_TC_LPLL_2F_L       (REG_TC_LPLL_BASE + 0x5E)
#define  REG_TC_LPLL_2F_H       (REG_TC_LPLL_BASE + 0x5F)
#define  REG_TC_LPLL_30_L       (REG_TC_LPLL_BASE + 0x60)
#define  REG_TC_LPLL_30_H       (REG_TC_LPLL_BASE + 0x61)
#define  REG_TC_LPLL_31_L       (REG_TC_LPLL_BASE + 0x62)
#define  REG_TC_LPLL_31_H       (REG_TC_LPLL_BASE + 0x63)
#define  REG_TC_LPLL_32_L       (REG_TC_LPLL_BASE + 0x64)
#define  REG_TC_LPLL_32_H       (REG_TC_LPLL_BASE + 0x65)
#define  REG_TC_LPLL_33_L       (REG_TC_LPLL_BASE + 0x66)
#define  REG_TC_LPLL_33_H       (REG_TC_LPLL_BASE + 0x67)
#define  REG_TC_LPLL_34_L       (REG_TC_LPLL_BASE + 0x68)
#define  REG_TC_LPLL_34_H       (REG_TC_LPLL_BASE + 0x69)
#define  REG_TC_LPLL_35_L       (REG_TC_LPLL_BASE + 0x6A)
#define  REG_TC_LPLL_35_H       (REG_TC_LPLL_BASE + 0x6B)
#define  REG_TC_LPLL_36_L       (REG_TC_LPLL_BASE + 0x6C)
#define  REG_TC_LPLL_36_H       (REG_TC_LPLL_BASE + 0x6D)
#define  REG_TC_LPLL_37_L       (REG_TC_LPLL_BASE + 0x6E)
#define  REG_TC_LPLL_37_H       (REG_TC_LPLL_BASE + 0x6F)
#define  REG_TC_LPLL_38_L       (REG_TC_LPLL_BASE + 0x70)
#define  REG_TC_LPLL_38_H       (REG_TC_LPLL_BASE + 0x71)
#define  REG_TC_LPLL_39_L       (REG_TC_LPLL_BASE + 0x72)
#define  REG_TC_LPLL_39_H       (REG_TC_LPLL_BASE + 0x73)
#define  REG_TC_LPLL_3A_L       (REG_TC_LPLL_BASE + 0x74)
#define  REG_TC_LPLL_3A_H       (REG_TC_LPLL_BASE + 0x75)
#define  REG_TC_LPLL_3B_L       (REG_TC_LPLL_BASE + 0x76)
#define  REG_TC_LPLL_3B_H       (REG_TC_LPLL_BASE + 0x77)
#define  REG_TC_LPLL_3C_L       (REG_TC_LPLL_BASE + 0x78)
#define  REG_TC_LPLL_3C_H       (REG_TC_LPLL_BASE + 0x79)
#define  REG_TC_LPLL_3D_L       (REG_TC_LPLL_BASE + 0x7A)
#define  REG_TC_LPLL_3D_H       (REG_TC_LPLL_BASE + 0x7B)
#define  REG_TC_LPLL_3E_L       (REG_TC_LPLL_BASE + 0x7C)
#define  REG_TC_LPLL_3E_H       (REG_TC_LPLL_BASE + 0x7D)
#define  REG_TC_LPLL_3F_L       (REG_TC_LPLL_BASE + 0x7E)
#define  REG_TC_LPLL_3F_H       (REG_TC_LPLL_BASE + 0x7F)
#define  REG_TC_LPLL_40_L       (REG_TC_LPLL_BASE + 0x80)
#define  REG_TC_LPLL_40_H       (REG_TC_LPLL_BASE + 0x81)
#define  REG_TC_LPLL_41_L       (REG_TC_LPLL_BASE + 0x82)
#define  REG_TC_LPLL_41_H       (REG_TC_LPLL_BASE + 0x83)
#define  REG_TC_LPLL_42_L       (REG_TC_LPLL_BASE + 0x84)
#define  REG_TC_LPLL_42_H       (REG_TC_LPLL_BASE + 0x85)
#define  REG_TC_LPLL_43_L       (REG_TC_LPLL_BASE + 0x86)
#define  REG_TC_LPLL_43_H       (REG_TC_LPLL_BASE + 0x87)
#define  REG_TC_LPLL_44_L       (REG_TC_LPLL_BASE + 0x88)
#define  REG_TC_LPLL_44_H       (REG_TC_LPLL_BASE + 0x89)
#define  REG_TC_LPLL_45_L       (REG_TC_LPLL_BASE + 0x8A)
#define  REG_TC_LPLL_45_H       (REG_TC_LPLL_BASE + 0x8B)
#define  REG_TC_LPLL_46_L       (REG_TC_LPLL_BASE + 0x8C)
#define  REG_TC_LPLL_46_H       (REG_TC_LPLL_BASE + 0x8D)
#define  REG_TC_LPLL_47_L       (REG_TC_LPLL_BASE + 0x8E)
#define  REG_TC_LPLL_47_H       (REG_TC_LPLL_BASE + 0x8F)
#define  REG_TC_LPLL_48_L       (REG_TC_LPLL_BASE + 0x90)
#define  REG_TC_LPLL_48_H       (REG_TC_LPLL_BASE + 0x91)
#define  REG_TC_LPLL_49_L       (REG_TC_LPLL_BASE + 0x92)
#define  REG_TC_LPLL_49_H       (REG_TC_LPLL_BASE + 0x93)
#define  REG_TC_LPLL_4A_L       (REG_TC_LPLL_BASE + 0x94)
#define  REG_TC_LPLL_4A_H       (REG_TC_LPLL_BASE + 0x95)
#define  REG_TC_LPLL_4B_L       (REG_TC_LPLL_BASE + 0x96)
#define  REG_TC_LPLL_4B_H       (REG_TC_LPLL_BASE + 0x97)
#define  REG_TC_LPLL_4C_L       (REG_TC_LPLL_BASE + 0x98)
#define  REG_TC_LPLL_4C_H       (REG_TC_LPLL_BASE + 0x99)
#define  REG_TC_LPLL_4D_L       (REG_TC_LPLL_BASE + 0x9A)
#define  REG_TC_LPLL_4D_H       (REG_TC_LPLL_BASE + 0x9B)
#define  REG_TC_LPLL_4E_L       (REG_TC_LPLL_BASE + 0x9C)
#define  REG_TC_LPLL_4E_H       (REG_TC_LPLL_BASE + 0x9D)
#define  REG_TC_LPLL_4F_L       (REG_TC_LPLL_BASE + 0x9E)
#define  REG_TC_LPLL_4F_H       (REG_TC_LPLL_BASE + 0x9F)
#define  REG_TC_LPLL_50_L       (REG_TC_LPLL_BASE + 0xA0)
#define  REG_TC_LPLL_50_H       (REG_TC_LPLL_BASE + 0xA1)
#define  REG_TC_LPLL_51_L       (REG_TC_LPLL_BASE + 0xA2)
#define  REG_TC_LPLL_51_H       (REG_TC_LPLL_BASE + 0xA3)
#define  REG_TC_LPLL_52_L       (REG_TC_LPLL_BASE + 0xA4)
#define  REG_TC_LPLL_52_H       (REG_TC_LPLL_BASE + 0xA5)
#define  REG_TC_LPLL_53_L       (REG_TC_LPLL_BASE + 0xA6)
#define  REG_TC_LPLL_53_H       (REG_TC_LPLL_BASE + 0xA7)
#define  REG_TC_LPLL_54_L       (REG_TC_LPLL_BASE + 0xA8)
#define  REG_TC_LPLL_54_H       (REG_TC_LPLL_BASE + 0xA9)
#define  REG_TC_LPLL_55_L       (REG_TC_LPLL_BASE + 0xAA)
#define  REG_TC_LPLL_55_H       (REG_TC_LPLL_BASE + 0xAB)
#define  REG_TC_LPLL_56_L       (REG_TC_LPLL_BASE + 0xAC)
#define  REG_TC_LPLL_56_H       (REG_TC_LPLL_BASE + 0xAD)
#define  REG_TC_LPLL_57_L       (REG_TC_LPLL_BASE + 0xAE)
#define  REG_TC_LPLL_57_H       (REG_TC_LPLL_BASE + 0xAF)
#define  REG_TC_LPLL_58_L       (REG_TC_LPLL_BASE + 0xB0)
#define  REG_TC_LPLL_58_H       (REG_TC_LPLL_BASE + 0xB1)
#define  REG_TC_LPLL_59_L       (REG_TC_LPLL_BASE + 0xB2)
#define  REG_TC_LPLL_59_H       (REG_TC_LPLL_BASE + 0xB3)
#define  REG_TC_LPLL_5A_L       (REG_TC_LPLL_BASE + 0xB4)
#define  REG_TC_LPLL_5A_H       (REG_TC_LPLL_BASE + 0xB5)
#define  REG_TC_LPLL_5B_L       (REG_TC_LPLL_BASE + 0xB6)
#define  REG_TC_LPLL_5B_H       (REG_TC_LPLL_BASE + 0xB7)
#define  REG_TC_LPLL_5C_L       (REG_TC_LPLL_BASE + 0xB8)
#define  REG_TC_LPLL_5C_H       (REG_TC_LPLL_BASE + 0xB9)
#define  REG_TC_LPLL_5D_L       (REG_TC_LPLL_BASE + 0xBA)
#define  REG_TC_LPLL_5D_H       (REG_TC_LPLL_BASE + 0xBB)
#define  REG_TC_LPLL_5E_L       (REG_TC_LPLL_BASE + 0xBC)
#define  REG_TC_LPLL_5E_H       (REG_TC_LPLL_BASE + 0xBD)
#define  REG_TC_LPLL_5F_L       (REG_TC_LPLL_BASE + 0xBE)
#define  REG_TC_LPLL_5F_H       (REG_TC_LPLL_BASE + 0xBF)
#define  REG_TC_LPLL_60_L       (REG_TC_LPLL_BASE + 0xC0)
#define  REG_TC_LPLL_60_H       (REG_TC_LPLL_BASE + 0xC1)
#define  REG_TC_LPLL_61_L       (REG_TC_LPLL_BASE + 0xC2)
#define  REG_TC_LPLL_61_H       (REG_TC_LPLL_BASE + 0xC3)
#define  REG_TC_LPLL_62_L       (REG_TC_LPLL_BASE + 0xC4)
#define  REG_TC_LPLL_62_H       (REG_TC_LPLL_BASE + 0xC5)
#define  REG_TC_LPLL_63_L       (REG_TC_LPLL_BASE + 0xC6)
#define  REG_TC_LPLL_63_H       (REG_TC_LPLL_BASE + 0xC7)
#define  REG_TC_LPLL_64_L       (REG_TC_LPLL_BASE + 0xC8)
#define  REG_TC_LPLL_64_H       (REG_TC_LPLL_BASE + 0xC9)
#define  REG_TC_LPLL_65_L       (REG_TC_LPLL_BASE + 0xCA)
#define  REG_TC_LPLL_65_H       (REG_TC_LPLL_BASE + 0xCB)
#define  REG_TC_LPLL_66_L       (REG_TC_LPLL_BASE + 0xCC)
#define  REG_TC_LPLL_66_H       (REG_TC_LPLL_BASE + 0xCD)
#define  REG_TC_LPLL_67_L       (REG_TC_LPLL_BASE + 0xCE)
#define  REG_TC_LPLL_67_H       (REG_TC_LPLL_BASE + 0xCF)
#define  REG_TC_LPLL_68_L       (REG_TC_LPLL_BASE + 0xD0)
#define  REG_TC_LPLL_68_H       (REG_TC_LPLL_BASE + 0xD1)
#define  REG_TC_LPLL_69_L       (REG_TC_LPLL_BASE + 0xD2)
#define  REG_TC_LPLL_69_H       (REG_TC_LPLL_BASE + 0xD3)
#define  REG_TC_LPLL_6A_L       (REG_TC_LPLL_BASE + 0xD4)
#define  REG_TC_LPLL_6A_H       (REG_TC_LPLL_BASE + 0xD5)
#define  REG_TC_LPLL_6B_L       (REG_TC_LPLL_BASE + 0xD6)
#define  REG_TC_LPLL_6B_H       (REG_TC_LPLL_BASE + 0xD7)
#define  REG_TC_LPLL_6C_L       (REG_TC_LPLL_BASE + 0xD8)
#define  REG_TC_LPLL_6C_H       (REG_TC_LPLL_BASE + 0xD9)
#define  REG_TC_LPLL_6D_L       (REG_TC_LPLL_BASE + 0xDA)
#define  REG_TC_LPLL_6D_H       (REG_TC_LPLL_BASE + 0xDB)
#define  REG_TC_LPLL_6E_L       (REG_TC_LPLL_BASE + 0xDC)
#define  REG_TC_LPLL_6E_H       (REG_TC_LPLL_BASE + 0xDD)
#define  REG_TC_LPLL_6F_L       (REG_TC_LPLL_BASE + 0xDE)
#define  REG_TC_LPLL_6F_H       (REG_TC_LPLL_BASE + 0xDF)
#define  REG_TC_LPLL_70_L       (REG_TC_LPLL_BASE + 0xE0)
#define  REG_TC_LPLL_70_H       (REG_TC_LPLL_BASE + 0xE1)
#define  REG_TC_LPLL_71_L       (REG_TC_LPLL_BASE + 0xE2)
#define  REG_TC_LPLL_71_H       (REG_TC_LPLL_BASE + 0xE3)
#define  REG_TC_LPLL_72_L       (REG_TC_LPLL_BASE + 0xE4)
#define  REG_TC_LPLL_72_H       (REG_TC_LPLL_BASE + 0xE5)
#define  REG_TC_LPLL_73_L       (REG_TC_LPLL_BASE + 0xE6)
#define  REG_TC_LPLL_73_H       (REG_TC_LPLL_BASE + 0xE7)
#define  REG_TC_LPLL_74_L       (REG_TC_LPLL_BASE + 0xE8)
#define  REG_TC_LPLL_74_H       (REG_TC_LPLL_BASE + 0xE9)
#define  REG_TC_LPLL_75_L       (REG_TC_LPLL_BASE + 0xEA)
#define  REG_TC_LPLL_75_H       (REG_TC_LPLL_BASE + 0xEB)
#define  REG_TC_LPLL_76_L       (REG_TC_LPLL_BASE + 0xEC)
#define  REG_TC_LPLL_76_H       (REG_TC_LPLL_BASE + 0xED)
#define  REG_TC_LPLL_77_L       (REG_TC_LPLL_BASE + 0xEE)
#define  REG_TC_LPLL_77_H       (REG_TC_LPLL_BASE + 0xEF)
#define  REG_TC_LPLL_78_L       (REG_TC_LPLL_BASE + 0xF0)
#define  REG_TC_LPLL_78_H       (REG_TC_LPLL_BASE + 0xF1)
#define  REG_TC_LPLL_79_L       (REG_TC_LPLL_BASE + 0xF2)
#define  REG_TC_LPLL_79_H       (REG_TC_LPLL_BASE + 0xF3)
#define  REG_TC_LPLL_7A_L       (REG_TC_LPLL_BASE + 0xF4)
#define  REG_TC_LPLL_7A_H       (REG_TC_LPLL_BASE + 0xF5)
#define  REG_TC_LPLL_7B_L       (REG_TC_LPLL_BASE + 0xF6)
#define  REG_TC_LPLL_7B_H       (REG_TC_LPLL_BASE + 0xF7)
#define  REG_TC_LPLL_7C_L       (REG_TC_LPLL_BASE + 0xF8)
#define  REG_TC_LPLL_7C_H       (REG_TC_LPLL_BASE + 0xF9)
#define  REG_TC_LPLL_7D_L       (REG_TC_LPLL_BASE + 0xFA)
#define  REG_TC_LPLL_7D_H       (REG_TC_LPLL_BASE + 0xFB)
#define  REG_TC_LPLL_7E_L       (REG_TC_LPLL_BASE + 0xFC)
#define  REG_TC_LPLL_7E_H       (REG_TC_LPLL_BASE + 0xFD)
#define  REG_TC_LPLL_7F_L       (REG_TC_LPLL_BASE + 0xFE)
#define  REG_TC_LPLL_7F_H       (REG_TC_LPLL_BASE + 0xFF)

#define  REG_TC_SC_BK10_00_L       _TC_PK_L_(0x10, 0x00)
#define  REG_TC_SC_BK10_00_H       _TC_PK_H_(0x10, 0x00)
#define  REG_TC_SC_BK10_01_L       _TC_PK_L_(0x10, 0x01)
#define  REG_TC_SC_BK10_01_H       _TC_PK_H_(0x10, 0x01)
#define  REG_TC_SC_BK10_02_L       _TC_PK_L_(0x10, 0x02)
#define  REG_TC_SC_BK10_02_H       _TC_PK_H_(0x10, 0x02)
#define  REG_TC_SC_BK10_03_L       _TC_PK_L_(0x10, 0x03)
#define  REG_TC_SC_BK10_03_H       _TC_PK_H_(0x10, 0x03)
#define  REG_TC_SC_BK10_04_L       _TC_PK_L_(0x10, 0x04)
#define  REG_TC_SC_BK10_04_H       _TC_PK_H_(0x10, 0x04)
#define  REG_TC_SC_BK10_05_L       _TC_PK_L_(0x10, 0x05)
#define  REG_TC_SC_BK10_05_H       _TC_PK_H_(0x10, 0x05)
#define  REG_TC_SC_BK10_06_L       _TC_PK_L_(0x10, 0x06)
#define  REG_TC_SC_BK10_06_H       _TC_PK_H_(0x10, 0x06)
#define  REG_TC_SC_BK10_07_L       _TC_PK_L_(0x10, 0x07)
#define  REG_TC_SC_BK10_07_H       _TC_PK_H_(0x10, 0x07)
#define  REG_TC_SC_BK10_08_L       _TC_PK_L_(0x10, 0x08)
#define  REG_TC_SC_BK10_08_H       _TC_PK_H_(0x10, 0x08)
#define  REG_TC_SC_BK10_09_L       _TC_PK_L_(0x10, 0x09)
#define  REG_TC_SC_BK10_09_H       _TC_PK_H_(0x10, 0x09)
#define  REG_TC_SC_BK10_0A_L       _TC_PK_L_(0x10, 0x0A)
#define  REG_TC_SC_BK10_0A_H       _TC_PK_H_(0x10, 0x0A)
#define  REG_TC_SC_BK10_0B_L       _TC_PK_L_(0x10, 0x0B)
#define  REG_TC_SC_BK10_0B_H       _TC_PK_H_(0x10, 0x0B)
#define  REG_TC_SC_BK10_0C_L       _TC_PK_L_(0x10, 0x0C)
#define  REG_TC_SC_BK10_0C_H       _TC_PK_H_(0x10, 0x0C)
#define  REG_TC_SC_BK10_0D_L       _TC_PK_L_(0x10, 0x0D)
#define  REG_TC_SC_BK10_0D_H       _TC_PK_H_(0x10, 0x0D)
#define  REG_TC_SC_BK10_0E_L       _TC_PK_L_(0x10, 0x0E)
#define  REG_TC_SC_BK10_0E_H       _TC_PK_H_(0x10, 0x0E)
#define  REG_TC_SC_BK10_0F_L       _TC_PK_L_(0x10, 0x0F)
#define  REG_TC_SC_BK10_0F_H       _TC_PK_H_(0x10, 0x0F)
#define  REG_TC_SC_BK10_10_L       _TC_PK_L_(0x10, 0x10)
#define  REG_TC_SC_BK10_10_H       _TC_PK_H_(0x10, 0x10)
#define  REG_TC_SC_BK10_11_L       _TC_PK_L_(0x10, 0x11)
#define  REG_TC_SC_BK10_11_H       _TC_PK_H_(0x10, 0x11)
#define  REG_TC_SC_BK10_12_L       _TC_PK_L_(0x10, 0x12)
#define  REG_TC_SC_BK10_12_H       _TC_PK_H_(0x10, 0x12)
#define  REG_TC_SC_BK10_13_L       _TC_PK_L_(0x10, 0x13)
#define  REG_TC_SC_BK10_13_H       _TC_PK_H_(0x10, 0x13)
#define  REG_TC_SC_BK10_14_L       _TC_PK_L_(0x10, 0x14)
#define  REG_TC_SC_BK10_14_H       _TC_PK_H_(0x10, 0x14)
#define  REG_TC_SC_BK10_15_L       _TC_PK_L_(0x10, 0x15)
#define  REG_TC_SC_BK10_15_H       _TC_PK_H_(0x10, 0x15)
#define  REG_TC_SC_BK10_16_L       _TC_PK_L_(0x10, 0x16)
#define  REG_TC_SC_BK10_16_H       _TC_PK_H_(0x10, 0x16)
#define  REG_TC_SC_BK10_17_L       _TC_PK_L_(0x10, 0x17)
#define  REG_TC_SC_BK10_17_H       _TC_PK_H_(0x10, 0x17)
#define  REG_TC_SC_BK10_18_L       _TC_PK_L_(0x10, 0x18)
#define  REG_TC_SC_BK10_18_H       _TC_PK_H_(0x10, 0x18)
#define  REG_TC_SC_BK10_19_L       _TC_PK_L_(0x10, 0x19)
#define  REG_TC_SC_BK10_19_H       _TC_PK_H_(0x10, 0x19)
#define  REG_TC_SC_BK10_1A_L       _TC_PK_L_(0x10, 0x1A)
#define  REG_TC_SC_BK10_1A_H       _TC_PK_H_(0x10, 0x1A)
#define  REG_TC_SC_BK10_1B_L       _TC_PK_L_(0x10, 0x1B)
#define  REG_TC_SC_BK10_1B_H       _TC_PK_H_(0x10, 0x1B)
#define  REG_TC_SC_BK10_1C_L       _TC_PK_L_(0x10, 0x1C)
#define  REG_TC_SC_BK10_1C_H       _TC_PK_H_(0x10, 0x1C)
#define  REG_TC_SC_BK10_1D_L       _TC_PK_L_(0x10, 0x1D)
#define  REG_TC_SC_BK10_1D_H       _TC_PK_H_(0x10, 0x1D)
#define  REG_TC_SC_BK10_1E_L       _TC_PK_L_(0x10, 0x1E)
#define  REG_TC_SC_BK10_1E_H       _TC_PK_H_(0x10, 0x1E)
#define  REG_TC_SC_BK10_1F_L       _TC_PK_L_(0x10, 0x1F)
#define  REG_TC_SC_BK10_1F_H       _TC_PK_H_(0x10, 0x1F)
#define  REG_TC_SC_BK10_20_L       _TC_PK_L_(0x10, 0x20)
#define  REG_TC_SC_BK10_20_H       _TC_PK_H_(0x10, 0x20)
#define  REG_TC_SC_BK10_21_L       _TC_PK_L_(0x10, 0x21)
#define  REG_TC_SC_BK10_21_H       _TC_PK_H_(0x10, 0x21)
#define  REG_TC_SC_BK10_22_L       _TC_PK_L_(0x10, 0x22)
#define  REG_TC_SC_BK10_22_H       _TC_PK_H_(0x10, 0x22)
#define  REG_TC_SC_BK10_23_L       _TC_PK_L_(0x10, 0x23)
#define  REG_TC_SC_BK10_23_H       _TC_PK_H_(0x10, 0x23)
#define  REG_TC_SC_BK10_24_L       _TC_PK_L_(0x10, 0x24)
#define  REG_TC_SC_BK10_24_H       _TC_PK_H_(0x10, 0x24)
#define  REG_TC_SC_BK10_25_L       _TC_PK_L_(0x10, 0x25)
#define  REG_TC_SC_BK10_25_H       _TC_PK_H_(0x10, 0x25)
#define  REG_TC_SC_BK10_26_L       _TC_PK_L_(0x10, 0x26)
#define  REG_TC_SC_BK10_26_H       _TC_PK_H_(0x10, 0x26)
#define  REG_TC_SC_BK10_27_L       _TC_PK_L_(0x10, 0x27)
#define  REG_TC_SC_BK10_27_H       _TC_PK_H_(0x10, 0x27)
#define  REG_TC_SC_BK10_28_L       _TC_PK_L_(0x10, 0x28)
#define  REG_TC_SC_BK10_28_H       _TC_PK_H_(0x10, 0x28)
#define  REG_TC_SC_BK10_29_L       _TC_PK_L_(0x10, 0x29)
#define  REG_TC_SC_BK10_29_H       _TC_PK_H_(0x10, 0x29)
#define  REG_TC_SC_BK10_2A_L       _TC_PK_L_(0x10, 0x2A)
#define  REG_TC_SC_BK10_2A_H       _TC_PK_H_(0x10, 0x2A)
#define  REG_TC_SC_BK10_2B_L       _TC_PK_L_(0x10, 0x2B)
#define  REG_TC_SC_BK10_2B_H       _TC_PK_H_(0x10, 0x2B)
#define  REG_TC_SC_BK10_2C_L       _TC_PK_L_(0x10, 0x2C)
#define  REG_TC_SC_BK10_2C_H       _TC_PK_H_(0x10, 0x2C)
#define  REG_TC_SC_BK10_2D_L       _TC_PK_L_(0x10, 0x2D)
#define  REG_TC_SC_BK10_2D_H       _TC_PK_H_(0x10, 0x2D)
#define  REG_TC_SC_BK10_2E_L       _TC_PK_L_(0x10, 0x2E)
#define  REG_TC_SC_BK10_2E_H       _TC_PK_H_(0x10, 0x2E)
#define  REG_TC_SC_BK10_2F_L       _TC_PK_L_(0x10, 0x2F)
#define  REG_TC_SC_BK10_2F_H       _TC_PK_H_(0x10, 0x2F)
#define  REG_TC_SC_BK10_30_L       _TC_PK_L_(0x10, 0x30)
#define  REG_TC_SC_BK10_30_H       _TC_PK_H_(0x10, 0x30)
#define  REG_TC_SC_BK10_31_L       _TC_PK_L_(0x10, 0x31)
#define  REG_TC_SC_BK10_31_H       _TC_PK_H_(0x10, 0x31)
#define  REG_TC_SC_BK10_32_L       _TC_PK_L_(0x10, 0x32)
#define  REG_TC_SC_BK10_32_H       _TC_PK_H_(0x10, 0x32)
#define  REG_TC_SC_BK10_33_L       _TC_PK_L_(0x10, 0x33)
#define  REG_TC_SC_BK10_33_H       _TC_PK_H_(0x10, 0x33)
#define  REG_TC_SC_BK10_34_L       _TC_PK_L_(0x10, 0x34)
#define  REG_TC_SC_BK10_34_H       _TC_PK_H_(0x10, 0x34)
#define  REG_TC_SC_BK10_35_L       _TC_PK_L_(0x10, 0x35)
#define  REG_TC_SC_BK10_35_H       _TC_PK_H_(0x10, 0x35)
#define  REG_TC_SC_BK10_36_L       _TC_PK_L_(0x10, 0x36)
#define  REG_TC_SC_BK10_36_H       _TC_PK_H_(0x10, 0x36)
#define  REG_TC_SC_BK10_37_L       _TC_PK_L_(0x10, 0x37)
#define  REG_TC_SC_BK10_37_H       _TC_PK_H_(0x10, 0x37)
#define  REG_TC_SC_BK10_38_L       _TC_PK_L_(0x10, 0x38)
#define  REG_TC_SC_BK10_38_H       _TC_PK_H_(0x10, 0x38)
#define  REG_TC_SC_BK10_39_L       _TC_PK_L_(0x10, 0x39)
#define  REG_TC_SC_BK10_39_H       _TC_PK_H_(0x10, 0x39)
#define  REG_TC_SC_BK10_3A_L       _TC_PK_L_(0x10, 0x3A)
#define  REG_TC_SC_BK10_3A_H       _TC_PK_H_(0x10, 0x3A)
#define  REG_TC_SC_BK10_3B_L       _TC_PK_L_(0x10, 0x3B)
#define  REG_TC_SC_BK10_3B_H       _TC_PK_H_(0x10, 0x3B)
#define  REG_TC_SC_BK10_3C_L       _TC_PK_L_(0x10, 0x3C)
#define  REG_TC_SC_BK10_3C_H       _TC_PK_H_(0x10, 0x3C)
#define  REG_TC_SC_BK10_3D_L       _TC_PK_L_(0x10, 0x3D)
#define  REG_TC_SC_BK10_3D_H       _TC_PK_H_(0x10, 0x3D)
#define  REG_TC_SC_BK10_3E_L       _TC_PK_L_(0x10, 0x3E)
#define  REG_TC_SC_BK10_3E_H       _TC_PK_H_(0x10, 0x3E)
#define  REG_TC_SC_BK10_3F_L       _TC_PK_L_(0x10, 0x3F)
#define  REG_TC_SC_BK10_3F_H       _TC_PK_H_(0x10, 0x3F)
#define  REG_TC_SC_BK10_40_L       _TC_PK_L_(0x10, 0x40)
#define  REG_TC_SC_BK10_40_H       _TC_PK_H_(0x10, 0x40)
#define  REG_TC_SC_BK10_41_L       _TC_PK_L_(0x10, 0x41)
#define  REG_TC_SC_BK10_41_H       _TC_PK_H_(0x10, 0x41)
#define  REG_TC_SC_BK10_42_L       _TC_PK_L_(0x10, 0x42)
#define  REG_TC_SC_BK10_42_H       _TC_PK_H_(0x10, 0x42)
#define  REG_TC_SC_BK10_43_L       _TC_PK_L_(0x10, 0x43)
#define  REG_TC_SC_BK10_43_H       _TC_PK_H_(0x10, 0x43)
#define  REG_TC_SC_BK10_44_L       _TC_PK_L_(0x10, 0x44)
#define  REG_TC_SC_BK10_44_H       _TC_PK_H_(0x10, 0x44)
#define  REG_TC_SC_BK10_45_L       _TC_PK_L_(0x10, 0x45)
#define  REG_TC_SC_BK10_45_H       _TC_PK_H_(0x10, 0x45)
#define  REG_TC_SC_BK10_46_L       _TC_PK_L_(0x10, 0x46)
#define  REG_TC_SC_BK10_46_H       _TC_PK_H_(0x10, 0x46)
#define  REG_TC_SC_BK10_47_L       _TC_PK_L_(0x10, 0x47)
#define  REG_TC_SC_BK10_47_H       _TC_PK_H_(0x10, 0x47)
#define  REG_TC_SC_BK10_48_L       _TC_PK_L_(0x10, 0x48)
#define  REG_TC_SC_BK10_48_H       _TC_PK_H_(0x10, 0x48)
#define  REG_TC_SC_BK10_49_L       _TC_PK_L_(0x10, 0x49)
#define  REG_TC_SC_BK10_49_H       _TC_PK_H_(0x10, 0x49)
#define  REG_TC_SC_BK10_4A_L       _TC_PK_L_(0x10, 0x4A)
#define  REG_TC_SC_BK10_4A_H       _TC_PK_H_(0x10, 0x4A)
#define  REG_TC_SC_BK10_4B_L       _TC_PK_L_(0x10, 0x4B)
#define  REG_TC_SC_BK10_4B_H       _TC_PK_H_(0x10, 0x4B)
#define  REG_TC_SC_BK10_4C_L       _TC_PK_L_(0x10, 0x4C)
#define  REG_TC_SC_BK10_4C_H       _TC_PK_H_(0x10, 0x4C)
#define  REG_TC_SC_BK10_4D_L       _TC_PK_L_(0x10, 0x4D)
#define  REG_TC_SC_BK10_4D_H       _TC_PK_H_(0x10, 0x4D)
#define  REG_TC_SC_BK10_4E_L       _TC_PK_L_(0x10, 0x4E)
#define  REG_TC_SC_BK10_4E_H       _TC_PK_H_(0x10, 0x4E)
#define  REG_TC_SC_BK10_4F_L       _TC_PK_L_(0x10, 0x4F)
#define  REG_TC_SC_BK10_4F_H       _TC_PK_H_(0x10, 0x4F)
#define  REG_TC_SC_BK10_50_L       _TC_PK_L_(0x10, 0x50)
#define  REG_TC_SC_BK10_50_H       _TC_PK_H_(0x10, 0x50)
#define  REG_TC_SC_BK10_51_L       _TC_PK_L_(0x10, 0x51)
#define  REG_TC_SC_BK10_51_H       _TC_PK_H_(0x10, 0x51)
#define  REG_TC_SC_BK10_52_L       _TC_PK_L_(0x10, 0x52)
#define  REG_TC_SC_BK10_52_H       _TC_PK_H_(0x10, 0x52)
#define  REG_TC_SC_BK10_53_L       _TC_PK_L_(0x10, 0x53)
#define  REG_TC_SC_BK10_53_H       _TC_PK_H_(0x10, 0x53)
#define  REG_TC_SC_BK10_54_L       _TC_PK_L_(0x10, 0x54)
#define  REG_TC_SC_BK10_54_H       _TC_PK_H_(0x10, 0x54)
#define  REG_TC_SC_BK10_55_L       _TC_PK_L_(0x10, 0x55)
#define  REG_TC_SC_BK10_55_H       _TC_PK_H_(0x10, 0x55)
#define  REG_TC_SC_BK10_56_L       _TC_PK_L_(0x10, 0x56)
#define  REG_TC_SC_BK10_56_H       _TC_PK_H_(0x10, 0x56)
#define  REG_TC_SC_BK10_57_L       _TC_PK_L_(0x10, 0x57)
#define  REG_TC_SC_BK10_57_H       _TC_PK_H_(0x10, 0x57)
#define  REG_TC_SC_BK10_58_L       _TC_PK_L_(0x10, 0x58)
#define  REG_TC_SC_BK10_58_H       _TC_PK_H_(0x10, 0x58)
#define  REG_TC_SC_BK10_59_L       _TC_PK_L_(0x10, 0x59)
#define  REG_TC_SC_BK10_59_H       _TC_PK_H_(0x10, 0x59)
#define  REG_TC_SC_BK10_5A_L       _TC_PK_L_(0x10, 0x5A)
#define  REG_TC_SC_BK10_5A_H       _TC_PK_H_(0x10, 0x5A)
#define  REG_TC_SC_BK10_5B_L       _TC_PK_L_(0x10, 0x5B)
#define  REG_TC_SC_BK10_5B_H       _TC_PK_H_(0x10, 0x5B)
#define  REG_TC_SC_BK10_5C_L       _TC_PK_L_(0x10, 0x5C)
#define  REG_TC_SC_BK10_5C_H       _TC_PK_H_(0x10, 0x5C)
#define  REG_TC_SC_BK10_5D_L       _TC_PK_L_(0x10, 0x5D)
#define  REG_TC_SC_BK10_5D_H       _TC_PK_H_(0x10, 0x5D)
#define  REG_TC_SC_BK10_5E_L       _TC_PK_L_(0x10, 0x5E)
#define  REG_TC_SC_BK10_5E_H       _TC_PK_H_(0x10, 0x5E)
#define  REG_TC_SC_BK10_5F_L       _TC_PK_L_(0x10, 0x5F)
#define  REG_TC_SC_BK10_5F_H       _TC_PK_H_(0x10, 0x5F)
#define  REG_TC_SC_BK10_60_L       _TC_PK_L_(0x10, 0x60)
#define  REG_TC_SC_BK10_60_H       _TC_PK_H_(0x10, 0x60)
#define  REG_TC_SC_BK10_61_L       _TC_PK_L_(0x10, 0x61)
#define  REG_TC_SC_BK10_61_H       _TC_PK_H_(0x10, 0x61)
#define  REG_TC_SC_BK10_62_L       _TC_PK_L_(0x10, 0x62)
#define  REG_TC_SC_BK10_62_H       _TC_PK_H_(0x10, 0x62)
#define  REG_TC_SC_BK10_63_L       _TC_PK_L_(0x10, 0x63)
#define  REG_TC_SC_BK10_63_H       _TC_PK_H_(0x10, 0x63)
#define  REG_TC_SC_BK10_64_L       _TC_PK_L_(0x10, 0x64)
#define  REG_TC_SC_BK10_64_H       _TC_PK_H_(0x10, 0x64)
#define  REG_TC_SC_BK10_65_L       _TC_PK_L_(0x10, 0x65)
#define  REG_TC_SC_BK10_65_H       _TC_PK_H_(0x10, 0x65)
#define  REG_TC_SC_BK10_66_L       _TC_PK_L_(0x10, 0x66)
#define  REG_TC_SC_BK10_66_H       _TC_PK_H_(0x10, 0x66)
#define  REG_TC_SC_BK10_67_L       _TC_PK_L_(0x10, 0x67)
#define  REG_TC_SC_BK10_67_H       _TC_PK_H_(0x10, 0x67)
#define  REG_TC_SC_BK10_68_L       _TC_PK_L_(0x10, 0x68)
#define  REG_TC_SC_BK10_68_H       _TC_PK_H_(0x10, 0x68)
#define  REG_TC_SC_BK10_69_L       _TC_PK_L_(0x10, 0x69)
#define  REG_TC_SC_BK10_69_H       _TC_PK_H_(0x10, 0x69)
#define  REG_TC_SC_BK10_6A_L       _TC_PK_L_(0x10, 0x6A)
#define  REG_TC_SC_BK10_6A_H       _TC_PK_H_(0x10, 0x6A)
#define  REG_TC_SC_BK10_6B_L       _TC_PK_L_(0x10, 0x6B)
#define  REG_TC_SC_BK10_6B_H       _TC_PK_H_(0x10, 0x6B)
#define  REG_TC_SC_BK10_6C_L       _TC_PK_L_(0x10, 0x6C)
#define  REG_TC_SC_BK10_6C_H       _TC_PK_H_(0x10, 0x6C)
#define  REG_TC_SC_BK10_6D_L       _TC_PK_L_(0x10, 0x6D)
#define  REG_TC_SC_BK10_6D_H       _TC_PK_H_(0x10, 0x6D)
#define  REG_TC_SC_BK10_6E_L       _TC_PK_L_(0x10, 0x6E)
#define  REG_TC_SC_BK10_6E_H       _TC_PK_H_(0x10, 0x6E)
#define  REG_TC_SC_BK10_6F_L       _TC_PK_L_(0x10, 0x6F)
#define  REG_TC_SC_BK10_6F_H       _TC_PK_H_(0x10, 0x6F)
#define  REG_TC_SC_BK10_70_L       _TC_PK_L_(0x10, 0x70)
#define  REG_TC_SC_BK10_70_H       _TC_PK_H_(0x10, 0x70)
#define  REG_TC_SC_BK10_71_L       _TC_PK_L_(0x10, 0x71)
#define  REG_TC_SC_BK10_71_H       _TC_PK_H_(0x10, 0x71)
#define  REG_TC_SC_BK10_72_L       _TC_PK_L_(0x10, 0x72)
#define  REG_TC_SC_BK10_72_H       _TC_PK_H_(0x10, 0x72)
#define  REG_TC_SC_BK10_73_L       _TC_PK_L_(0x10, 0x73)
#define  REG_TC_SC_BK10_73_H       _TC_PK_H_(0x10, 0x73)
#define  REG_TC_SC_BK10_74_L       _TC_PK_L_(0x10, 0x74)
#define  REG_TC_SC_BK10_74_H       _TC_PK_H_(0x10, 0x74)
#define  REG_TC_SC_BK10_75_L       _TC_PK_L_(0x10, 0x75)
#define  REG_TC_SC_BK10_75_H       _TC_PK_H_(0x10, 0x75)
#define  REG_TC_SC_BK10_76_L       _TC_PK_L_(0x10, 0x76)
#define  REG_TC_SC_BK10_76_H       _TC_PK_H_(0x10, 0x76)
#define  REG_TC_SC_BK10_77_L       _TC_PK_L_(0x10, 0x77)
#define  REG_TC_SC_BK10_77_H       _TC_PK_H_(0x10, 0x77)
#define  REG_TC_SC_BK10_78_L       _TC_PK_L_(0x10, 0x78)
#define  REG_TC_SC_BK10_78_H       _TC_PK_H_(0x10, 0x78)
#define  REG_TC_SC_BK10_79_L       _TC_PK_L_(0x10, 0x79)
#define  REG_TC_SC_BK10_79_H       _TC_PK_H_(0x10, 0x79)
#define  REG_TC_SC_BK10_7A_L       _TC_PK_L_(0x10, 0x7A)
#define  REG_TC_SC_BK10_7A_H       _TC_PK_H_(0x10, 0x7A)
#define  REG_TC_SC_BK10_7B_L       _TC_PK_L_(0x10, 0x7B)
#define  REG_TC_SC_BK10_7B_H       _TC_PK_H_(0x10, 0x7B)
#define  REG_TC_SC_BK10_7C_L       _TC_PK_L_(0x10, 0x7C)
#define  REG_TC_SC_BK10_7C_H       _TC_PK_H_(0x10, 0x7C)
#define  REG_TC_SC_BK10_7D_L       _TC_PK_L_(0x10, 0x7D)
#define  REG_TC_SC_BK10_7D_H       _TC_PK_H_(0x10, 0x7D)
#define  REG_TC_SC_BK10_7E_L       _TC_PK_L_(0x10, 0x7E)
#define  REG_TC_SC_BK10_7E_H       _TC_PK_H_(0x10, 0x7E)
#define  REG_TC_SC_BK10_7F_L       _TC_PK_L_(0x10, 0x7F)
#define  REG_TC_SC_BK10_7F_H       _TC_PK_H_(0x10, 0x7F)

#define  REG_TC_MOD_BK00_00_L       _TC_PK_L_(0x00, 0x00)
#define  REG_TC_MOD_BK00_00_H       _TC_PK_H_(0x00, 0x00)
#define  REG_TC_MOD_BK00_01_L       _TC_PK_L_(0x00, 0x01)
#define  REG_TC_MOD_BK00_01_H       _TC_PK_H_(0x00, 0x01)
#define  REG_TC_MOD_BK00_02_L       _TC_PK_L_(0x00, 0x02)
#define  REG_TC_MOD_BK00_02_H       _TC_PK_H_(0x00, 0x02)
#define  REG_TC_MOD_BK00_03_L       _TC_PK_L_(0x00, 0x03)
#define  REG_TC_MOD_BK00_03_H       _TC_PK_H_(0x00, 0x03)
#define  REG_TC_MOD_BK00_04_L       _TC_PK_L_(0x00, 0x04)
#define  REG_TC_MOD_BK00_04_H       _TC_PK_H_(0x00, 0x04)
#define  REG_TC_MOD_BK00_05_L       _TC_PK_L_(0x00, 0x05)
#define  REG_TC_MOD_BK00_05_H       _TC_PK_H_(0x00, 0x05)
#define  REG_TC_MOD_BK00_06_L       _TC_PK_L_(0x00, 0x06)
#define  REG_TC_MOD_BK00_06_H       _TC_PK_H_(0x00, 0x06)
#define  REG_TC_MOD_BK00_07_L       _TC_PK_L_(0x00, 0x07)
#define  REG_TC_MOD_BK00_07_H       _TC_PK_H_(0x00, 0x07)
#define  REG_TC_MOD_BK00_08_L       _TC_PK_L_(0x00, 0x08)
#define  REG_TC_MOD_BK00_08_H       _TC_PK_H_(0x00, 0x08)
#define  REG_TC_MOD_BK00_09_L       _TC_PK_L_(0x00, 0x09)
#define  REG_TC_MOD_BK00_09_H       _TC_PK_H_(0x00, 0x09)
#define  REG_TC_MOD_BK00_0A_L       _TC_PK_L_(0x00, 0x0A)
#define  REG_TC_MOD_BK00_0A_H       _TC_PK_H_(0x00, 0x0A)
#define  REG_TC_MOD_BK00_0B_L       _TC_PK_L_(0x00, 0x0B)
#define  REG_TC_MOD_BK00_0B_H       _TC_PK_H_(0x00, 0x0B)
#define  REG_TC_MOD_BK00_0C_L       _TC_PK_L_(0x00, 0x0C)
#define  REG_TC_MOD_BK00_0C_H       _TC_PK_H_(0x00, 0x0C)
#define  REG_TC_MOD_BK00_0D_L       _TC_PK_L_(0x00, 0x0D)
#define  REG_TC_MOD_BK00_0D_H       _TC_PK_H_(0x00, 0x0D)
#define  REG_TC_MOD_BK00_0E_L       _TC_PK_L_(0x00, 0x0E)
#define  REG_TC_MOD_BK00_0E_H       _TC_PK_H_(0x00, 0x0E)
#define  REG_TC_MOD_BK00_0F_L       _TC_PK_L_(0x00, 0x0F)
#define  REG_TC_MOD_BK00_0F_H       _TC_PK_H_(0x00, 0x0F)
#define  REG_TC_MOD_BK00_10_L       _TC_PK_L_(0x00, 0x10)
#define  REG_TC_MOD_BK00_10_H       _TC_PK_H_(0x00, 0x10)
#define  REG_TC_MOD_BK00_11_L       _TC_PK_L_(0x00, 0x11)
#define  REG_TC_MOD_BK00_11_H       _TC_PK_H_(0x00, 0x11)
#define  REG_TC_MOD_BK00_12_L       _TC_PK_L_(0x00, 0x12)
#define  REG_TC_MOD_BK00_12_H       _TC_PK_H_(0x00, 0x12)
#define  REG_TC_MOD_BK00_13_L       _TC_PK_L_(0x00, 0x13)
#define  REG_TC_MOD_BK00_13_H       _TC_PK_H_(0x00, 0x13)
#define  REG_TC_MOD_BK00_14_L       _TC_PK_L_(0x00, 0x14)
#define  REG_TC_MOD_BK00_14_H       _TC_PK_H_(0x00, 0x14)
#define  REG_TC_MOD_BK00_15_L       _TC_PK_L_(0x00, 0x15)
#define  REG_TC_MOD_BK00_15_H       _TC_PK_H_(0x00, 0x15)
#define  REG_TC_MOD_BK00_16_L       _TC_PK_L_(0x00, 0x16)
#define  REG_TC_MOD_BK00_16_H       _TC_PK_H_(0x00, 0x16)
#define  REG_TC_MOD_BK00_17_L       _TC_PK_L_(0x00, 0x17)
#define  REG_TC_MOD_BK00_17_H       _TC_PK_H_(0x00, 0x17)
#define  REG_TC_MOD_BK00_18_L       _TC_PK_L_(0x00, 0x18)
#define  REG_TC_MOD_BK00_18_H       _TC_PK_H_(0x00, 0x18)
#define  REG_TC_MOD_BK00_19_L       _TC_PK_L_(0x00, 0x19)
#define  REG_TC_MOD_BK00_19_H       _TC_PK_H_(0x00, 0x19)
#define  REG_TC_MOD_BK00_1A_L       _TC_PK_L_(0x00, 0x1A)
#define  REG_TC_MOD_BK00_1A_H       _TC_PK_H_(0x00, 0x1A)
#define  REG_TC_MOD_BK00_1B_L       _TC_PK_L_(0x00, 0x1B)
#define  REG_TC_MOD_BK00_1B_H       _TC_PK_H_(0x00, 0x1B)
#define  REG_TC_MOD_BK00_1C_L       _TC_PK_L_(0x00, 0x1C)
#define  REG_TC_MOD_BK00_1C_H       _TC_PK_H_(0x00, 0x1C)
#define  REG_TC_MOD_BK00_1D_L       _TC_PK_L_(0x00, 0x1D)
#define  REG_TC_MOD_BK00_1D_H       _TC_PK_H_(0x00, 0x1D)
#define  REG_TC_MOD_BK00_1E_L       _TC_PK_L_(0x00, 0x1E)
#define  REG_TC_MOD_BK00_1E_H       _TC_PK_H_(0x00, 0x1E)
#define  REG_TC_MOD_BK00_1F_L       _TC_PK_L_(0x00, 0x1F)
#define  REG_TC_MOD_BK00_1F_H       _TC_PK_H_(0x00, 0x1F)
#define  REG_TC_MOD_BK00_20_L       _TC_PK_L_(0x00, 0x20)
#define  REG_TC_MOD_BK00_20_H       _TC_PK_H_(0x00, 0x20)
#define  REG_TC_MOD_BK00_21_L       _TC_PK_L_(0x00, 0x21)
#define  REG_TC_MOD_BK00_21_H       _TC_PK_H_(0x00, 0x21)
#define  REG_TC_MOD_BK00_22_L       _TC_PK_L_(0x00, 0x22)
#define  REG_TC_MOD_BK00_22_H       _TC_PK_H_(0x00, 0x22)
#define  REG_TC_MOD_BK00_23_L       _TC_PK_L_(0x00, 0x23)
#define  REG_TC_MOD_BK00_23_H       _TC_PK_H_(0x00, 0x23)
#define  REG_TC_MOD_BK00_24_L       _TC_PK_L_(0x00, 0x24)
#define  REG_TC_MOD_BK00_24_H       _TC_PK_H_(0x00, 0x24)
#define  REG_TC_MOD_BK00_25_L       _TC_PK_L_(0x00, 0x25)
#define  REG_TC_MOD_BK00_25_H       _TC_PK_H_(0x00, 0x25)
#define  REG_TC_MOD_BK00_26_L       _TC_PK_L_(0x00, 0x26)
#define  REG_TC_MOD_BK00_26_H       _TC_PK_H_(0x00, 0x26)
#define  REG_TC_MOD_BK00_27_L       _TC_PK_L_(0x00, 0x27)
#define  REG_TC_MOD_BK00_27_H       _TC_PK_H_(0x00, 0x27)
#define  REG_TC_MOD_BK00_28_L       _TC_PK_L_(0x00, 0x28)
#define  REG_TC_MOD_BK00_28_H       _TC_PK_H_(0x00, 0x28)
#define  REG_TC_MOD_BK00_29_L       _TC_PK_L_(0x00, 0x29)
#define  REG_TC_MOD_BK00_29_H       _TC_PK_H_(0x00, 0x29)
#define  REG_TC_MOD_BK00_2A_L       _TC_PK_L_(0x00, 0x2A)
#define  REG_TC_MOD_BK00_2A_H       _TC_PK_H_(0x00, 0x2A)
#define  REG_TC_MOD_BK00_2B_L       _TC_PK_L_(0x00, 0x2B)
#define  REG_TC_MOD_BK00_2B_H       _TC_PK_H_(0x00, 0x2B)
#define  REG_TC_MOD_BK00_2C_L       _TC_PK_L_(0x00, 0x2C)
#define  REG_TC_MOD_BK00_2C_H       _TC_PK_H_(0x00, 0x2C)
#define  REG_TC_MOD_BK00_2D_L       _TC_PK_L_(0x00, 0x2D)
#define  REG_TC_MOD_BK00_2D_H       _TC_PK_H_(0x00, 0x2D)
#define  REG_TC_MOD_BK00_2E_L       _TC_PK_L_(0x00, 0x2E)
#define  REG_TC_MOD_BK00_2E_H       _TC_PK_H_(0x00, 0x2E)
#define  REG_TC_MOD_BK00_2F_L       _TC_PK_L_(0x00, 0x2F)
#define  REG_TC_MOD_BK00_2F_H       _TC_PK_H_(0x00, 0x2F)
#define  REG_TC_MOD_BK00_30_L       _TC_PK_L_(0x00, 0x30)
#define  REG_TC_MOD_BK00_30_H       _TC_PK_H_(0x00, 0x30)
#define  REG_TC_MOD_BK00_31_L       _TC_PK_L_(0x00, 0x31)
#define  REG_TC_MOD_BK00_31_H       _TC_PK_H_(0x00, 0x31)
#define  REG_TC_MOD_BK00_32_L       _TC_PK_L_(0x00, 0x32)
#define  REG_TC_MOD_BK00_32_H       _TC_PK_H_(0x00, 0x32)
#define  REG_TC_MOD_BK00_33_L       _TC_PK_L_(0x00, 0x33)
#define  REG_TC_MOD_BK00_33_H       _TC_PK_H_(0x00, 0x33)
#define  REG_TC_MOD_BK00_34_L       _TC_PK_L_(0x00, 0x34)
#define  REG_TC_MOD_BK00_34_H       _TC_PK_H_(0x00, 0x34)
#define  REG_TC_MOD_BK00_35_L       _TC_PK_L_(0x00, 0x35)
#define  REG_TC_MOD_BK00_35_H       _TC_PK_H_(0x00, 0x35)
#define  REG_TC_MOD_BK00_36_L       _TC_PK_L_(0x00, 0x36)
#define  REG_TC_MOD_BK00_36_H       _TC_PK_H_(0x00, 0x36)
#define  REG_TC_MOD_BK00_37_L       _TC_PK_L_(0x00, 0x37)
#define  REG_TC_MOD_BK00_37_H       _TC_PK_H_(0x00, 0x37)
#define  REG_TC_MOD_BK00_38_L       _TC_PK_L_(0x00, 0x38)
#define  REG_TC_MOD_BK00_38_H       _TC_PK_H_(0x00, 0x38)
#define  REG_TC_MOD_BK00_39_L       _TC_PK_L_(0x00, 0x39)
#define  REG_TC_MOD_BK00_39_H       _TC_PK_H_(0x00, 0x39)
#define  REG_TC_MOD_BK00_3A_L       _TC_PK_L_(0x00, 0x3A)
#define  REG_TC_MOD_BK00_3A_H       _TC_PK_H_(0x00, 0x3A)
#define  REG_TC_MOD_BK00_3B_L       _TC_PK_L_(0x00, 0x3B)
#define  REG_TC_MOD_BK00_3B_H       _TC_PK_H_(0x00, 0x3B)
#define  REG_TC_MOD_BK00_3C_L       _TC_PK_L_(0x00, 0x3C)
#define  REG_TC_MOD_BK00_3C_H       _TC_PK_H_(0x00, 0x3C)
#define  REG_TC_MOD_BK00_3D_L       _TC_PK_L_(0x00, 0x3D)
#define  REG_TC_MOD_BK00_3D_H       _TC_PK_H_(0x00, 0x3D)
#define  REG_TC_MOD_BK00_3E_L       _TC_PK_L_(0x00, 0x3E)
#define  REG_TC_MOD_BK00_3E_H       _TC_PK_H_(0x00, 0x3E)
#define  REG_TC_MOD_BK00_3F_L       _TC_PK_L_(0x00, 0x3F)
#define  REG_TC_MOD_BK00_3F_H       _TC_PK_H_(0x00, 0x3F)
#define  REG_TC_MOD_BK00_40_L       _TC_PK_L_(0x00, 0x40)
#define  REG_TC_MOD_BK00_40_H       _TC_PK_H_(0x00, 0x40)
#define  REG_TC_MOD_BK00_41_L       _TC_PK_L_(0x00, 0x41)
#define  REG_TC_MOD_BK00_41_H       _TC_PK_H_(0x00, 0x41)
#define  REG_TC_MOD_BK00_42_L       _TC_PK_L_(0x00, 0x42)
#define  REG_TC_MOD_BK00_42_H       _TC_PK_H_(0x00, 0x42)
#define  REG_TC_MOD_BK00_43_L       _TC_PK_L_(0x00, 0x43)
#define  REG_TC_MOD_BK00_43_H       _TC_PK_H_(0x00, 0x43)
#define  REG_TC_MOD_BK00_44_L       _TC_PK_L_(0x00, 0x44)
#define  REG_TC_MOD_BK00_44_H       _TC_PK_H_(0x00, 0x44)
#define  REG_TC_MOD_BK00_45_L       _TC_PK_L_(0x00, 0x45)
#define  REG_TC_MOD_BK00_45_H       _TC_PK_H_(0x00, 0x45)
#define  REG_TC_MOD_BK00_46_L       _TC_PK_L_(0x00, 0x46)
#define  REG_TC_MOD_BK00_46_H       _TC_PK_H_(0x00, 0x46)
#define  REG_TC_MOD_BK00_47_L       _TC_PK_L_(0x00, 0x47)
#define  REG_TC_MOD_BK00_47_H       _TC_PK_H_(0x00, 0x47)
#define  REG_TC_MOD_BK00_48_L       _TC_PK_L_(0x00, 0x48)
#define  REG_TC_MOD_BK00_48_H       _TC_PK_H_(0x00, 0x48)
#define  REG_TC_MOD_BK00_49_L       _TC_PK_L_(0x00, 0x49)
#define  REG_TC_MOD_BK00_49_H       _TC_PK_H_(0x00, 0x49)
#define  REG_TC_MOD_BK00_4A_L       _TC_PK_L_(0x00, 0x4A)
#define  REG_TC_MOD_BK00_4A_H       _TC_PK_H_(0x00, 0x4A)
#define  REG_TC_MOD_BK00_4B_L       _TC_PK_L_(0x00, 0x4B)
#define  REG_TC_MOD_BK00_4B_H       _TC_PK_H_(0x00, 0x4B)
#define  REG_TC_MOD_BK00_4C_L       _TC_PK_L_(0x00, 0x4C)
#define  REG_TC_MOD_BK00_4C_H       _TC_PK_H_(0x00, 0x4C)
#define  REG_TC_MOD_BK00_4D_L       _TC_PK_L_(0x00, 0x4D)
#define  REG_TC_MOD_BK00_4D_H       _TC_PK_H_(0x00, 0x4D)
#define  REG_TC_MOD_BK00_4E_L       _TC_PK_L_(0x00, 0x4E)
#define  REG_TC_MOD_BK00_4E_H       _TC_PK_H_(0x00, 0x4E)
#define  REG_TC_MOD_BK00_4F_L       _TC_PK_L_(0x00, 0x4F)
#define  REG_TC_MOD_BK00_4F_H       _TC_PK_H_(0x00, 0x4F)
#define  REG_TC_MOD_BK00_50_L       _TC_PK_L_(0x00, 0x50)
#define  REG_TC_MOD_BK00_50_H       _TC_PK_H_(0x00, 0x50)
#define  REG_TC_MOD_BK00_51_L       _TC_PK_L_(0x00, 0x51)
#define  REG_TC_MOD_BK00_51_H       _TC_PK_H_(0x00, 0x51)
#define  REG_TC_MOD_BK00_52_L       _TC_PK_L_(0x00, 0x52)
#define  REG_TC_MOD_BK00_52_H       _TC_PK_H_(0x00, 0x52)
#define  REG_TC_MOD_BK00_53_L       _TC_PK_L_(0x00, 0x53)
#define  REG_TC_MOD_BK00_53_H       _TC_PK_H_(0x00, 0x53)
#define  REG_TC_MOD_BK00_54_L       _TC_PK_L_(0x00, 0x54)
#define  REG_TC_MOD_BK00_54_H       _TC_PK_H_(0x00, 0x54)
#define  REG_TC_MOD_BK00_55_L       _TC_PK_L_(0x00, 0x55)
#define  REG_TC_MOD_BK00_55_H       _TC_PK_H_(0x00, 0x55)
#define  REG_TC_MOD_BK00_56_L       _TC_PK_L_(0x00, 0x56)
#define  REG_TC_MOD_BK00_56_H       _TC_PK_H_(0x00, 0x56)
#define  REG_TC_MOD_BK00_57_L       _TC_PK_L_(0x00, 0x57)
#define  REG_TC_MOD_BK00_57_H       _TC_PK_H_(0x00, 0x57)
#define  REG_TC_MOD_BK00_58_L       _TC_PK_L_(0x00, 0x58)
#define  REG_TC_MOD_BK00_58_H       _TC_PK_H_(0x00, 0x58)
#define  REG_TC_MOD_BK00_59_L       _TC_PK_L_(0x00, 0x59)
#define  REG_TC_MOD_BK00_59_H       _TC_PK_H_(0x00, 0x59)
#define  REG_TC_MOD_BK00_5A_L       _TC_PK_L_(0x00, 0x5A)
#define  REG_TC_MOD_BK00_5A_H       _TC_PK_H_(0x00, 0x5A)
#define  REG_TC_MOD_BK00_5B_L       _TC_PK_L_(0x00, 0x5B)
#define  REG_TC_MOD_BK00_5B_H       _TC_PK_H_(0x00, 0x5B)
#define  REG_TC_MOD_BK00_5C_L       _TC_PK_L_(0x00, 0x5C)
#define  REG_TC_MOD_BK00_5C_H       _TC_PK_H_(0x00, 0x5C)
#define  REG_TC_MOD_BK00_5D_L       _TC_PK_L_(0x00, 0x5D)
#define  REG_TC_MOD_BK00_5D_H       _TC_PK_H_(0x00, 0x5D)
#define  REG_TC_MOD_BK00_5E_L       _TC_PK_L_(0x00, 0x5E)
#define  REG_TC_MOD_BK00_5E_H       _TC_PK_H_(0x00, 0x5E)
#define  REG_TC_MOD_BK00_5F_L       _TC_PK_L_(0x00, 0x5F)
#define  REG_TC_MOD_BK00_5F_H       _TC_PK_H_(0x00, 0x5F)
#define  REG_TC_MOD_BK00_60_L       _TC_PK_L_(0x00, 0x60)
#define  REG_TC_MOD_BK00_60_H       _TC_PK_H_(0x00, 0x60)
#define  REG_TC_MOD_BK00_61_L       _TC_PK_L_(0x00, 0x61)
#define  REG_TC_MOD_BK00_61_H       _TC_PK_H_(0x00, 0x61)
#define  REG_TC_MOD_BK00_62_L       _TC_PK_L_(0x00, 0x62)
#define  REG_TC_MOD_BK00_62_H       _TC_PK_H_(0x00, 0x62)
#define  REG_TC_MOD_BK00_63_L       _TC_PK_L_(0x00, 0x63)
#define  REG_TC_MOD_BK00_63_H       _TC_PK_H_(0x00, 0x63)
#define  REG_TC_MOD_BK00_64_L       _TC_PK_L_(0x00, 0x64)
#define  REG_TC_MOD_BK00_64_H       _TC_PK_H_(0x00, 0x64)
#define  REG_TC_MOD_BK00_65_L       _TC_PK_L_(0x00, 0x65)
#define  REG_TC_MOD_BK00_65_H       _TC_PK_H_(0x00, 0x65)
#define  REG_TC_MOD_BK00_66_L       _TC_PK_L_(0x00, 0x66)
#define  REG_TC_MOD_BK00_66_H       _TC_PK_H_(0x00, 0x66)
#define  REG_TC_MOD_BK00_67_L       _TC_PK_L_(0x00, 0x67)
#define  REG_TC_MOD_BK00_67_H       _TC_PK_H_(0x00, 0x67)
#define  REG_TC_MOD_BK00_68_L       _TC_PK_L_(0x00, 0x68)
#define  REG_TC_MOD_BK00_68_H       _TC_PK_H_(0x00, 0x68)
#define  REG_TC_MOD_BK00_69_L       _TC_PK_L_(0x00, 0x69)
#define  REG_TC_MOD_BK00_69_H       _TC_PK_H_(0x00, 0x69)
#define  REG_TC_MOD_BK00_6A_L       _TC_PK_L_(0x00, 0x6A)
#define  REG_TC_MOD_BK00_6A_H       _TC_PK_H_(0x00, 0x6A)
#define  REG_TC_MOD_BK00_6B_L       _TC_PK_L_(0x00, 0x6B)
#define  REG_TC_MOD_BK00_6B_H       _TC_PK_H_(0x00, 0x6B)
#define  REG_TC_MOD_BK00_6C_L       _TC_PK_L_(0x00, 0x6C)
#define  REG_TC_MOD_BK00_6C_H       _TC_PK_H_(0x00, 0x6C)
#define  REG_TC_MOD_BK00_6D_L       _TC_PK_L_(0x00, 0x6D)
#define  REG_TC_MOD_BK00_6D_H       _TC_PK_H_(0x00, 0x6D)
#define  REG_TC_MOD_BK00_6E_L       _TC_PK_L_(0x00, 0x6E)
#define  REG_TC_MOD_BK00_6E_H       _TC_PK_H_(0x00, 0x6E)
#define  REG_TC_MOD_BK00_6F_L       _TC_PK_L_(0x00, 0x6F)
#define  REG_TC_MOD_BK00_6F_H       _TC_PK_H_(0x00, 0x6F)
#define  REG_TC_MOD_BK00_70_L       _TC_PK_L_(0x00, 0x70)
#define  REG_TC_MOD_BK00_70_H       _TC_PK_H_(0x00, 0x70)
#define  REG_TC_MOD_BK00_71_L       _TC_PK_L_(0x00, 0x71)
#define  REG_TC_MOD_BK00_71_H       _TC_PK_H_(0x00, 0x71)
#define  REG_TC_MOD_BK00_72_L       _TC_PK_L_(0x00, 0x72)
#define  REG_TC_MOD_BK00_72_H       _TC_PK_H_(0x00, 0x72)
#define  REG_TC_MOD_BK00_73_L       _TC_PK_L_(0x00, 0x73)
#define  REG_TC_MOD_BK00_73_H       _TC_PK_H_(0x00, 0x73)
#define  REG_TC_MOD_BK00_74_L       _TC_PK_L_(0x00, 0x74)
#define  REG_TC_MOD_BK00_74_H       _TC_PK_H_(0x00, 0x74)
#define  REG_TC_MOD_BK00_75_L       _TC_PK_L_(0x00, 0x75)
#define  REG_TC_MOD_BK00_75_H       _TC_PK_H_(0x00, 0x75)
#define  REG_TC_MOD_BK00_76_L       _TC_PK_L_(0x00, 0x76)
#define  REG_TC_MOD_BK00_76_H       _TC_PK_H_(0x00, 0x76)
#define  REG_TC_MOD_BK00_77_L       _TC_PK_L_(0x00, 0x77)
#define  REG_TC_MOD_BK00_77_H       _TC_PK_H_(0x00, 0x77)
#define  REG_TC_MOD_BK00_78_L       _TC_PK_L_(0x00, 0x78)
#define  REG_TC_MOD_BK00_78_H       _TC_PK_H_(0x00, 0x78)
#define  REG_TC_MOD_BK00_79_L       _TC_PK_L_(0x00, 0x79)
#define  REG_TC_MOD_BK00_79_H       _TC_PK_H_(0x00, 0x79)
#define  REG_TC_MOD_BK00_7A_L       _TC_PK_L_(0x00, 0x7A)
#define  REG_TC_MOD_BK00_7A_H       _TC_PK_H_(0x00, 0x7A)
#define  REG_TC_MOD_BK00_7B_L       _TC_PK_L_(0x00, 0x7B)
#define  REG_TC_MOD_BK00_7B_H       _TC_PK_H_(0x00, 0x7B)
#define  REG_TC_MOD_BK00_7C_L       _TC_PK_L_(0x00, 0x7C)
#define  REG_TC_MOD_BK00_7C_H       _TC_PK_H_(0x00, 0x7C)
#define  REG_TC_MOD_BK00_7D_L       _TC_PK_L_(0x00, 0x7D)
#define  REG_TC_MOD_BK00_7D_H       _TC_PK_H_(0x00, 0x7D)
#define  REG_TC_MOD_BK00_7E_L       _TC_PK_L_(0x00, 0x7E)
#define  REG_TC_MOD_BK00_7E_H       _TC_PK_H_(0x00, 0x7E)
#define  REG_TC_MOD_BK00_7F_L       _TC_PK_L_(0x00, 0x7F)
#define  REG_TC_MOD_BK00_7F_H       _TC_PK_H_(0x00, 0x7F)

#ifdef __cplusplus
}
#endif

#undef _DRVADCTBL_H_
#endif

