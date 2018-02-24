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

#ifndef MAPP_MAIN_H
#define MAPP_MAIN_H

#include "Board.h"

typedef enum
{
    EN_MSTAR_MAIN_FUNCTION_POWER_ON_INITIATION = 0x00,

    EN_MSTAR_MAIN_FUNCTION_STANDBY2ON,

    EN_MSTAR_MAIN_FUNCTION_PRE_INIT,

    EN_MSTAR_MAIN_FUNCTION_POWERON,

    EN_MSTAR_MAIN_FUNCTION_ENTERING_WHILE_LOOP,

    EN_MSTAR_MAIN_FUNCTION_WHILE_LOOP,

    EN_MSTAR_MAIN_FUNCTION_DONE,
} En_MSTAR_MAIN_FUNCTION_STAGE;

typedef enum
{
    EN_PRE_INIT_INITIATION                      = 0x00,

    EN_PRE_INIT_STAGE_GLOBALVAR_INIT,

    EN_PRE_INIT_STAGE_AUTOTEST_INIT,

    EN_PRE_INIT_STAGE_POWERSETTING_INIT,
    EN_PRE_INIT_STAGE_CHIP_INIT,

    EN_PRE_INIT_STAGE_AUDIO_INIT_1, // Set Amp

    EN_PRE_INIT_STAGE_CUSTOMER_INFO_INIT,

    EN_PRE_INIT_STAGE_PANEL_BACKLIGHT_OFF,

    EN_PRE_INIT_STAGE_READ_DDRPHASE_INIT,

    EN_PRE_INIT_STAGE_DRIVER_STEP1_INIT,

    EN_PRE_INIT_STAGE_INTERRUPT_INIT,

    EN_PRE_INIT_STAGE_DATABASE_INIT, // Init flash driver, init DB_Gen

    EN_PRE_INIT_STAGE_ATVPROC_AUDIO_INIT,

#if (ENABLE_ATSC_TTS)
    EN_PRE_INIT_STAGE_TTS_INIT,
#endif

#if(ENABLE_POWERON_MUSIC)
    EN_PRE_INIT_STAGE_POWER_ON_MUSIC_INIT,
#endif

    EN_PRE_INIT_STAGE_XC_HDMI_INIT,

    EN_PRE_INIT_STAGE_DRIVER_IR_KEYPAD_INIT,

    EN_PRE_INIT_STAGE_CHECK_TO_POWER_DOWN,

    EN_PRE_INIT_STAGE_DRIVER_STEP2_INIT,

    EN_PRE_INIT_STAGE_PANEL_INIT,

    EN_PRE_INIT_STAGE_ENABLE_DCC_DDC2BI_INIT,

    EN_PRE_INIT_STAGE_DATABASE_CHECKING_INIT,

    EN_PRE_INIT_STAGE_ADC_INIT,

    EN_PRE_INIT_STAGE_SSC_SETTING_INIT,

    EN_PRE_INIT_STAGE_TTX_INIT,
    EN_PRE_INIT_STAGE_IMAGE_SETMIRROR_INIT,

    EN_PRE_INIT_STAGE_UI_INPUTSOURCE_INIT,

    EN_PRE_INIT_STAGE_CI_INIT,
    EN_PRE_INIT_STAGE_DevHDMISWITCH_INIT,

    EN_PRE_INIT_STAGE_DB_CH_INIT, //init DB_CH

    EN_PRE_INIT_STAGE_TIME_SETTING_INIT,
    EN_PRE_INIT_STAGE_EPGTIMER_DATA_INIT,
    EN_PRE_INIT_STAGE_CHECKONTIMER_INIT, // After this state, can make first input source

    EN_PRE_INIT_STAGE_HDMI_HDP_INIT,

    EN_PRE_INIT_STAGE_LOGO_INIT,

    EN_PRE_INIT_STAGE_TUNER_DEMOD_INIT,

    EN_PRE_INIT_STAGE_PRINT_SYSTEM_INFO,

    EN_PRE_INIT_STAGE_FONT_INIT,

    EN_PRE_INIT_STAGE_USB_INIT,
#if 0
    EN_PRE_INIT_STAGE_TUNER_INIT,
#endif

    EN_PRE_INIT_STAGE_ATV_SYSTEM_INIT,

    EN_PRE_INIT_STAGE_AVD_INIT,

    EN_PRE_INIT_STAGE_OCP_INIT, // string
#if (ENABLE_KEY_TO_SPEECH)
    EN_PRE_INIT_STAGE_KTS_INIT,
#endif

    EN_PRE_INIT_STAGE_ENVIRONMENT_INIT,

#if(ENABLE_OAD)
    EN_PRE_INIT_STAGE_OAD_INIT,
#endif


    EN_PRE_INIT_STAGE_LOGO_OFF, // Logo off

    EN_PRE_INIT_STAGE_DTV_SYSTEM_INIT,

    EN_PRE_INIT_STAGE_PVR_INIT,

    EN_PRE_INIT_STAGE_BEFORE_CHANGE_SOURCE, // PowerOnMusic-off

    EN_PRE_INIT_STAGE_SORCE_CHANGE_INIT,

    EN_PRE_INIT_STAGE_DISPLAY_STEP2_INIT,
    EN_PRE_INIT_STAGE_OTHERS_INIT,

    EN_PRE_INIT_STAGE_DONE,
}En_PRE_INIT_SUB_STATE;

typedef enum
{
    EN_WHILE_LOOP_INITIATION  = 0x00,

    EN_WHILE_LOOP_UART_PAUSE,
    EN_WHILE_LOOP_MULTITASKS,
    EN_WHILE_LOOP_TOPSTATEMACHINE,
    EN_WHILE_LOOP_INTERMEDIATE_MINI_DUMP,

    EN_WHILE_LOOP_IDLE,

    EN_WHILE_LOOP_DONE,
} En_WHILE_LOOP_SUB_STATE;

//==================================================
BOOL MApp_Main_Is_PowerOnPreInitFinish(void);
BOOL MApp_Main_Is_PowerOnInitFinish(void);

//==================================================

#endif // MAPP_MAIN_H

