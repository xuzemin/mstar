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

#define PM_START_ADDR               0x11D0
#define ADDR_dspVersion             0x11D0      //len = 1;
#define ADDR_fm_stdM_gain           0x11D1      //len = 4;
#define ADDR_fm_stdX_gain           0x11D5      //len = 4;
#define ADDR_nicam_gain             0x11D9      //len = 2;
#define ADDR_am_gain                0x11DB      //len = 3;

#define ADDR_a2_stdM_thr            0x1200      //len = 17
#define ADDR_a2_stdBG_thr           0x1211      //len = 17
#define ADDR_a2_stdDK_thr           0x1222      //len = 17
#define ADDR_a2_stdI_thr            0x1233      //len = 4
#define ADDR_am_thr                 0x1237      //len = 3;
#define ADDR_hidev_stdM_thr         0x123A      //len = 4;
#define ADDR_hidev_stdBG_thr        0x123E      //len = 4;
#define ADDR_hidev_stdDK_thr        0x1242      //len = 4;
#define ADDR_hidev_stdI_thr         0x1246      //len = 4;
#define ADDR_nicam_stdBG_pherr_thr  0x124A      //len = 3;
#define ADDR_nicam_stdI_pherr_thr   0x124D      //len = 3;

#define ADDR_fm_ch1_HW_setting      0x1250      //len = 8;
#define ADDR_fm_ch2_HW_setting      0x1258      //len = 8;
#define ADDR_hidev_HW_setting       0x1260      //len = 8;

#define ADDR_hidev_demfir           0x1270      //len = 15
#define ADDR_fm_ch1_pfir            0x1280      //len = 30
#define ADDR_fm_ch2_pfir            0x129E      //len = 30
#define ADDR_hidev_lv1_pfir         0x12BC      //len = 20
#define ADDR_hidev_lv2_pfir         0x12D0      //len = 20
#define ADDR_hidev_lv3_pfir         0x12E4      //len = 20

/**********************************************************
*
*   DSP DEBUG CMD LIST
*
***********************************************************/
#define    A2_CMD_GET_CARRIER_1_AMP                0x3000
#define    A2_CMD_GET_CARRIER_1_VAR                0x3100
#define    A2_CMD_GET_CARRIER_2_AMP                0x3200
#define    A2_CMD_GET_CARRIER_2_VAR                0x3300
#define    A2_CMD_GET_MONO_AMP                        0x3400
#define    A2_CMD_GET_STEREO_AMP                    0x3500
#define    A2_CMD_GET_DUAL_AMP                        0x3600
#define    A2_CMD_GET_MONO_VAR                        0x3700
#define    A2_CMD_GET_STEREO_VAR                    0x3800
#define    A2_CMD_GET_DUAL_VAR                        0x3900
#define    A2_CMD_SHOW_SNR_MAX_VAL                    0x3A00
#define    A2_CMD_SHOW_SNR_MIN_VAL                    0x3B00
#define    A2_CMD_GET_CH1_SNR                        0x3C00
#define    A2_CMD_GET_CH2_SNR                        0x3D00
#define    A2_CMD_GET_PilotID_VAR                    0x3E00
#define    A2_CMD_GET_PilotID_Diff                    0x3F00
#define    A2_CMD_GET_PilotID_VAR2Diff                0x4000
#define    A2_CMD_GET_STEREO_AMP_2_PilotID_MONO    0x4100
#define    A2_CMD_GET_DUAL_AMP_2_PilotID_MONO      0x4200
#define    A2_CMD_GET_POINTER                        0x4300

