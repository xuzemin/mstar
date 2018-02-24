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

