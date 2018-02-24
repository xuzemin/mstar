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
#ifndef MSAPI_NR_H
#define MSAPI_NR_H

/********************************************************************************/
/*                  Macro                                                       */
/* ******************************************************************************/

/********************************************************************************/
/*                  Struct                                                      */
/* ******************************************************************************/
#define DYNAMIC_NR_TBL_MOTION_LEVEL_NUM    6
#define DYNAMIC_NR_TBL_LUMA_LEVEL_NUM      8
#define DYNAMIC_NR_TBL_NOISE_LEVEL_NUM     5

#define DYNAMIC_NR_TBL_REG_NUM      8

#define  NoiseMagTh0    0
#define  NoiseMagTh1    1
#define  NoiseMagTh2    2
#define  NoiseMagTh3    3
#define  NoiseMagTh4    4
#define  NoiseMagTh5    5
#define  NoiseMagTh6    6
#define  NoiseMagTh7    7
#define  NoiseMagTh8    8

#if (ENABLE_NEW_AUTO_NR)
    typedef enum
    {
        E_MAPI_AUTO_NR_STATUS_OFF = 0x00,
        E_MAPI_AUTO_NR_STATUS_LOW = 0x01,
        E_MAPI_AUTO_NR_STATUS_MID = 0x02,
        E_MAPI_AUTO_NR_STATUS_HIGH = 0x03,
    } MAPI_PQL_AUTO_NR_STATUS;
#endif

typedef struct
{
    MS_U8 u8CoringOffset;
    MS_U8 u8SNROffset;
}MS_DYNAMIC_NR_MISC_PARAM_LUMA;

typedef struct
{
    MS_U8 u8Spike_NR_0;
    MS_U8 u8Spike_NR_1;
    MS_U8 u8Gray_Guard_En;
    MS_U8 u8Gray_Guard_Gain;
}MS_DYNAMIC_NR_MISC_PARAM;

typedef struct
{
    MS_U8 u8CoringOffset;
    MS_U8 u8SharpnessOffset;
    MS_U8 u8NM_V;
    MS_U8 u8NM_H_0;
    MS_U8 u8NM_H_1;
    MS_U8 u8SC_Coring;
    MS_U8 u8GNR_0;
    MS_U8 u8GNR_1;
    MS_U8 u8SpikeNR_0;
    MS_U8 u8SpikeNR_1;
    MS_U8 u8CP;
    MS_U8 u8DP;
    MS_U8 u8AGC_Gain_Offset;
    MS_U8 u8Gray_Guard_En;
    MS_U8 u8Gray_Guard_Gain;
}MS_DYNAMIC_NR_MISC_PARAM_NOISE;


typedef struct
{
    MS_U8 u8DeFlicker_Step1;
    MS_U8 u8DeFlicker_Step2;
    MS_U8 u8M_DeFi_Th;
    MS_U8 u8L_DeFi_Th;
    MS_U8 u8NoiseThreshold[DYNAMIC_NR_TBL_NOISE_LEVEL_NUM-1];
    MS_U8 u8NoiseMag;
    MS_BOOL bMotionEn;
    MS_BOOL bLumaEn;
    MS_U8 u8MotionStartLvl;
    MS_U8 u8MotionEndLvl;
    MS_U8 u8LumaStartLvl;
    MS_U8 u8LumaEndLvl;
}MS_DYNAMIC_NR_PARAM;

/********************************************************************************/
/*                  Global varialbe                                             */
/********************************************************************************/

/********************************************************************************/
/*                  Function Prototypes                                         */
/********************************************************************************/
extern void mAPI_DynamicNR_GetGuassinSNR(void);
extern void msAPI_DynamicNR_GetSharpness(void);
extern void msAPI_DynamicNR_GetCoring(void);
extern void msAPI_DynamicNR_Handler(E_XC_PQ_3D_NR en3DNRType);
#if (ENABLE_NEW_AUTO_NR)
extern void msAPI_NR_SetDNRDefault(void);
extern void msAPI_NR_SetDNRStatus(MAPI_PQL_AUTO_NR_STATUS Status_NR,MAPI_PQL_AUTO_NR_STATUS PreStatus_NR);
extern void msAPI_DNR_Handler(void);
#endif

#endif
