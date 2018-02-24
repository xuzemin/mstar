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
//-----------------------------------------------------------------------------
// $Header: 
// (C) Copyright 2007 NXP Semiconductors, All rights reserved
//
// This source code and any compilation or derivative thereof is the sole
// property of NXP Corporation and is provided pursuant to a Software
// License Agreement.  This code is the proprietary information of NXP
// Corporation and is confidential in nature.  Its use and dissemination by
// any party other than NXP Corporation is strictly limited by the
// confidential information provisions of the Agreement referenced above.
//-----------------------------------------------------------------------------
// FILE NAME:    tmddTDA182I2local.h
//
// DESCRIPTION:  define the Object for the TDA182I2
//
// DOCUMENT REF: DVP Software Coding Guidelines v1.14
//               DVP Board Support Library Architecture Specification v0.5
//
// NOTES:        
//-----------------------------------------------------------------------------
//
#ifndef _TMDD_TDA182I2LOCAL_H //-----------------
#define _TMDD_TDA182I2LOCAL_H

//-----------------------------------------------------------------------------
// Standard include files:
//-----------------------------------------------------------------------------

#include "tmddTDA182I2.h"

/*------------------------------------------------------------------------------*/
/* Project include files:                                                       */
/*------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif

    //-----------------------------------------------------------------------------
    // Types and defines:
    //-----------------------------------------------------------------------------
    //

#define ddTDA182I2_MUTEX_TIMEOUT       TMBSL_FRONTEND_MUTEX_TIMEOUT_INFINITE

#define _SYSTEMFUNC (pObj->SystemFunc)

#define POBJ_SRVFUNC_SIO pObj->sRWFunc
#define POBJ_SRVFUNC_STIME pObj->sTime
//#define P_DBGPRINTEx pObj->sDebug.Print
//#define P_DBGPRINTVALID ((pObj != Null) && (pObj->sDebug.Print != Null))

#define TDA182I2_DD_COMP_NUM    2 // Major protocol change - Specification change required
#define TDA182I2_DD_MAJOR_VER   4 // Minor protocol change - Specification change required
#define TDA182I2_DD_MINOR_VER   7 // Software update - No protocol change - No specification change required

#define TDA182I2_POWER_LEVEL_MIN  40
#define TDA182I2_POWER_LEVEL_MAX  110

#define TDA182I2_MAX_UNITS                  2
#define TDA182I2_I2C_MAP_NB_BYTES           68

#define TDA182I2_DEVICE_ID_MASTER  1
#define TDA182I2_DEVICE_ID_SLAVE   0


    typedef struct _TDA182I2_I2C_Map_t
    {
        union
        {
            UInt8 ID_byte_1;
            struct       
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 MS:1;
                UInt8 Ident_1:7;
#else
                UInt8 Ident_1:7;
                UInt8 MS:1;
#endif
            }bF;
        }uBx00;

        union
        {
            UInt8 ID_byte_2;
            struct
            {
                UInt8 Ident_2:8;
            }bF;
        }uBx01;

        union
        {
            UInt8 ID_byte_3;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 Major_rev:4;
				UInt8 Minor_rev:4;
#else
				UInt8 Minor_rev:4;
                UInt8 Major_rev:4;
#endif                
            }bF;
        }uBx02;

        union
        {
            UInt8 Thermo_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
				UInt8 TM_D:7;
#else
				UInt8 TM_D:7;
                UInt8 UNUSED_I0_D0:1;
#endif                
            }bF;
        }uBx03;

        union
        {
            UInt8 Thermo_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:7;
				UInt8 TM_ON:1;
#else
				UInt8 TM_ON:1;
                UInt8 UNUSED_I0_D0:7;
#endif                
            }bF;
        }uBx04;

        union
        {
            UInt8 Power_state_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:6;
                UInt8 POR:1;
				UInt8 LO_Lock:1;
#else
				UInt8 LO_Lock:1;
                UInt8 POR:1;
                UInt8 UNUSED_I0_D0:6;
#endif                
            }bF;
        }uBx05;

        union
        {
            UInt8 Power_state_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:4;
                UInt8 SM:1;
                UInt8 SM_Synthe:1;
                UInt8 SM_LT:1;
				UInt8 SM_XT:1;
#else
				UInt8 SM_XT:1;
                UInt8 SM_LT:1;
                UInt8 SM_Synthe:1;
                UInt8 SM:1;
                UInt8 UNUSED_I0_D0:4;
#endif                
            }bF;
        }uBx06;

        union
        {
            UInt8 Input_Power_Level_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
				UInt8 Power_Level:7;
#else
				UInt8 Power_Level:7;
                UInt8 UNUSED_I0_D0:1;
#endif                
            }bF;
        }uBx07;

        union
        {
            UInt8 IRQ_status;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IRQ_status:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 MSM_XtalCal_End:1;
                UInt8 MSM_RSSI_End:1;
                UInt8 MSM_LOCalc_End:1;
                UInt8 MSM_RFCal_End:1;
                UInt8 MSM_IRCAL_End:1;
				UInt8 MSM_RCCal_End:1;				    
#else
				UInt8 MSM_RCCal_End:1;
                UInt8 MSM_IRCAL_End:1;
                UInt8 MSM_RFCal_End:1;
                UInt8 MSM_LOCalc_End:1;
                UInt8 MSM_RSSI_End:1;
                UInt8 MSM_XtalCal_End:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_status:1;
#endif                
            }bF;
        }uBx08;

        union
        {
            UInt8 IRQ_enable;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IRQ_Enable:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 XtalCal_Enable:1;
                UInt8 MSM_RSSI_Enable:1;
                UInt8 MSM_LOCalc_Enable:1;
                UInt8 MSM_RFCAL_Enable:1;
                UInt8 MSM_IRCAL_Enable:1;
				UInt8 MSM_RCCal_Enable:1;
#else
				UInt8 MSM_RCCal_Enable:1;
                UInt8 MSM_IRCAL_Enable:1;
                UInt8 MSM_RFCAL_Enable:1;
                UInt8 MSM_LOCalc_Enable:1;
                UInt8 MSM_RSSI_Enable:1;
                UInt8 XtalCal_Enable:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_Enable:1;
#endif                
            }bF;
        }uBx09;

        union
        {
            UInt8 IRQ_clear;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IRQ_Clear:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 XtalCal_Clear:1;
                UInt8 MSM_RSSI_Clear:1;
                UInt8 MSM_LOCalc_Clear:1;
                UInt8 MSM_RFCal_Clear:1;
                UInt8 MSM_IRCAL_Clear:1;
				UInt8 MSM_RCCal_Clear:1;
#else
				UInt8 MSM_RCCal_Clear:1;
                UInt8 MSM_IRCAL_Clear:1;
                UInt8 MSM_RFCal_Clear:1;
                UInt8 MSM_LOCalc_Clear:1;
                UInt8 MSM_RSSI_Clear:1;
                UInt8 XtalCal_Clear:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_Clear:1;
#endif                
            }bF;
        }uBx0A;

        union
        {
            UInt8 IRQ_set;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IRQ_Set:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 XtalCal_Set:1;
                UInt8 MSM_RSSI_Set:1;
                UInt8 MSM_LOCalc_Set:1;
                UInt8 MSM_RFCal_Set:1;
                UInt8 MSM_IRCAL_Set:1;
				UInt8 MSM_RCCal_Set:1;
#else
				UInt8 MSM_RCCal_Set:1;
                UInt8 MSM_IRCAL_Set:1;
                UInt8 MSM_RFCal_Set:1;
                UInt8 MSM_LOCalc_Set:1;
                UInt8 MSM_RSSI_Set:1;
                UInt8 XtalCal_Set:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 IRQ_Set:1;
#endif                
            }bF;
        }uBx0B;

        union
        {
            UInt8 AGC1_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 LT_Enable:1;
                UInt8 AGC1_6_15dB:1;
                UInt8 UNUSED_I0_D0:2;
				UInt8 AGC1_TOP:4;
#else
				UInt8 AGC1_TOP:4;
                UInt8 UNUSED_I0_D0:2;
                UInt8 AGC1_6_15dB:1;
                UInt8 LT_Enable:1;
#endif                
            }bF;
        }uBx0C;

        union
        {
            UInt8 AGC2_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:3;
				UInt8 AGC2_TOP:5;
#else
				UInt8 AGC2_TOP:5;
                UInt8 UNUSED_I0_D0:3;
#endif                
            }bF;
        }uBx0D;

        union
        {
            UInt8 AGCK_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 AGCs_Up_Step_assym:2;
                UInt8 AGCs_Up_Step:1;
                UInt8 Pulse_Shaper_Disable:1;
                UInt8 AGCK_Step:2;
				UInt8 AGCK_Mode:2;
#else
				UInt8 AGCK_Mode:2;
                UInt8 AGCK_Step:2;
                UInt8 Pulse_Shaper_Disable:1;
                UInt8 AGCs_Up_Step:1;
                UInt8 AGCs_Up_Step_assym:2;
#endif                
            }bF;
        }uBx0E;

        union
        {
            UInt8 RF_AGC_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 PD_RFAGC_Adapt:1;
                UInt8 RFAGC_Adapt_TOP:2;
                UInt8 RFAGC_Low_BW:1;
                UInt8 RF_Atten_3dB:1;
				UInt8 RFAGC_Top:3;
#else
				UInt8 RFAGC_Top:3;
                UInt8 RF_Atten_3dB:1;
                UInt8 RFAGC_Low_BW:1;
                UInt8 RFAGC_Adapt_TOP:2;
                UInt8 PD_RFAGC_Adapt:1;
#endif                
            }bF;
        }uBx0F;

        union
        {
            UInt8 IR_Mixer_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:4;
				UInt8 IR_Mixer_Top:4;
#else
				UInt8 IR_Mixer_Top:4;
                UInt8 UNUSED_I0_D0:4;
#endif                
            }bF;
        }uBx10;

        union
        {
            UInt8 AGC5_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
                UInt8 AGCs_Do_Step_assym:2;
                UInt8 AGC5_Ana:1;
				UInt8 AGC5_TOP:4;
#else
				UInt8 AGC5_TOP:4;
                UInt8 AGC5_Ana:1;
                UInt8 AGCs_Do_Step_assym:2;
                UInt8 UNUSED_I0_D0:1;
#endif                
            }bF;
        }uBx11;

        union
        {
            UInt8 IF_AGC_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:5;
				UInt8 IF_level:3;
#else
				UInt8 IF_level:3;
                UInt8 UNUSED_I0_D0:5;
#endif                
            }bF;
        }uBx12;

        union
        {
            UInt8 IF_Byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IF_HP_Fc:2;
                UInt8 IF_ATSC_Notch:1;
                UInt8 LP_FC_Offset:2;
				UInt8 LP_Fc:3;
#else
				UInt8 LP_Fc:3;
                UInt8 LP_FC_Offset:2;
                UInt8 IF_ATSC_Notch:1;
                UInt8 IF_HP_Fc:2;
#endif                
            }bF;
        }uBx13;

        union
        {
            UInt8 Reference_Byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 I2C_Clock_Mode:1;
                UInt8 Digital_Clock_Mode:1;
                UInt8 UNUSED_I1_D0:1;
                UInt8 XtalOsc_AnaReg_En:1;
                UInt8 UNUSED_I0_D0:2;
				UInt8 XTout:2;
#else
				UInt8 XTout:2;
                UInt8 UNUSED_I0_D0:2;
                UInt8 XtalOsc_AnaReg_En:1;
                UInt8 UNUSED_I1_D0:1;
                UInt8 Digital_Clock_Mode:1;
                UInt8 I2C_Clock_Mode:1;
#endif
            }bF;
        }uBx14;

        union
        {
            UInt8 IF_Frequency_byte;
            struct
            {
                UInt8 IF_Freq:8;
            }bF;
        }uBx15;

        union
        {
            UInt8 RF_Frequency_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:4;
				UInt8 RF_Freq_1:4;
#else
				UInt8 RF_Freq_1:4;
                UInt8 UNUSED_I0_D0:4;
#endif
            }bF;
        }uBx16;

        union
        {
            UInt8 RF_Frequency_byte_2;
            struct
            {
                UInt8 RF_Freq_2:8;
            }bF;
        }uBx17;


        union
        {
            UInt8 RF_Frequency_byte_3;
            struct
            {
                UInt8 RF_Freq_3:8;
            }bF;
        }uBx18;

        union
        {
            UInt8 MSM_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RSSI_Meas:1;
                UInt8 RF_CAL_AV:1;
                UInt8 RF_CAL:1;
                UInt8 IR_CAL_Loop:1;
                UInt8 IR_Cal_Image:1;
                UInt8 IR_CAL_Wanted:1;
                UInt8 RC_Cal:1;
				UInt8 Calc_PLL:1;
#else
				UInt8 Calc_PLL:1;
                UInt8 RC_Cal:1;
                UInt8 IR_CAL_Wanted:1;
                UInt8 IR_Cal_Image:1;
                UInt8 IR_CAL_Loop:1;
                UInt8 RF_CAL:1;
                UInt8 RF_CAL_AV:1;
                UInt8 RSSI_Meas:1;
#endif
            }bF;
        }uBx19;

        union
        {
            UInt8 MSM_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:6;
                UInt8 XtalCal_Launch:1;
				UInt8 MSM_Launch:1;
#else
				UInt8 MSM_Launch:1;
                UInt8 XtalCal_Launch:1;
                UInt8 UNUSED_I0_D0:6;
#endif
            }bF;
        }uBx1A;

        union
        {
            UInt8 PowerSavingMode;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 PSM_AGC1:2;
                UInt8 PSM_StoB:1;
                UInt8 PSMRFpoly:1;
                UInt8 PSM_Mixer:1;
                UInt8 PSM_Ifpoly:1;
				UInt8 PSM_Lodriver:2;
#else
				UInt8 PSM_Lodriver:2;
                UInt8 PSM_Ifpoly:1;
                UInt8 PSM_Mixer:1;
                UInt8 PSMRFpoly:1;
                UInt8 PSM_StoB:1;
                UInt8 PSM_AGC1:2;
#endif
            }bF;
        }uBx1B;

        union
        {
            UInt8 DCC_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 DCC_Bypass:1;
                UInt8 DCC_Slow:1;
                UInt8 DCC_psm:1;
                UInt8 UNUSED_I0_D0:5;
#else
                UInt8 UNUSED_I0_D0:5;
                UInt8 DCC_psm:1;
                UInt8 DCC_Slow:1;
                UInt8 DCC_Bypass:1;
#endif
            }bF;
        }uBx1C;

        union
        {
            UInt8 FLO_max_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:2;
                UInt8 Fmax_Lo:6;
#else
                UInt8 Fmax_Lo:6;
                UInt8 UNUSED_I0_D0:2;
#endif
            }bF;
        }uBx1D;

        union
        {
            UInt8 IR_Cal_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IR_Loop:2;  
                UInt8 IR_Target:3;
                UInt8 IR_GStep:3;
#else
                UInt8 IR_GStep:3;
                UInt8 IR_Target:3;
                UInt8 IR_Loop:2;  
#endif
            }bF;
        }uBx1E;

        union
        {
            UInt8 IR_Cal_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IR_Corr_Boost:1;
                UInt8 IR_FreqLow_Sel:1;
                UInt8 IR_mode_ram_store:1;
                UInt8 IR_FreqLow:5;
#else
                UInt8 IR_FreqLow:5;
                UInt8 IR_mode_ram_store:1;
                UInt8 IR_FreqLow_Sel:1;
                UInt8 IR_Corr_Boost:1;
#endif
            }bF;
        }uBx1F;

        union
        {
            UInt8 IR_Cal_byte_3;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:3;
                UInt8 IR_FreqMid:5;
#else
                UInt8 IR_FreqMid:5;
                UInt8 UNUSED_I0_D0:3;
#endif
            }bF;
        }uBx20;

        union
        {
            UInt8 IR_Cal_byte_4;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:2;
                UInt8 Coarse_IR_FreqHigh:1;
                UInt8 IR_FreqHigh:5;
#else
                UInt8 IR_FreqHigh:5;
                UInt8 Coarse_IR_FreqHigh:1;
                UInt8 UNUSED_I0_D0:2;
#endif
            }bF;
        }uBx21;

        union
        {
            UInt8 Vsync_Mgt_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 PD_Vsync_Mgt:1;
                UInt8 PD_Ovld:1;
                UInt8 PD_Udld:1;
                UInt8 AGC_Ovld_TOP:3;
                UInt8 AGC_Ovld_Timer:2;
#else
                UInt8 AGC_Ovld_Timer:2;
                UInt8 AGC_Ovld_TOP:3;
                UInt8 PD_Udld:1;
                UInt8 PD_Ovld:1;
                UInt8 PD_Vsync_Mgt:1;
#endif
            }bF;
        }uBx22;

        union
        {
            UInt8 IR_Mixer_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 IR_Mixer_loop_off:1;
                UInt8 IR_Mixer_Do_step:2;
                UInt8 UNUSED_I0_D0:3;
                UInt8 Hi_Pass:1;
                UInt8 IF_Notch:1;
#else
                UInt8 IF_Notch:1;
                UInt8 Hi_Pass:1;
                UInt8 UNUSED_I0_D0:3;
                UInt8 IR_Mixer_Do_step:2;
                UInt8 IR_Mixer_loop_off:1;
#endif
            }bF;
        }uBx23;

        union
        {
            UInt8 AGC1_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 AGC1_loop_off:1;
                UInt8 AGC1_Do_step:2;
                UInt8 Force_AGC1_gain:1;
                UInt8 AGC1_Gain:4;
#else
                UInt8 AGC1_Gain:4;
                UInt8 Force_AGC1_gain:1;
                UInt8 AGC1_Do_step:2;
                UInt8 AGC1_loop_off:1;
#endif
            }bF;
        }uBx24;

        union
        {
            UInt8 AGC5_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 AGC5_loop_off:1;
                UInt8 AGC5_Do_step:2;
                UInt8 UNUSED_I1_D0:1;
                UInt8 Force_AGC5_gain:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 AGC5_Gain:2;
#else
                UInt8 AGC5_Gain:2;
                UInt8 UNUSED_I0_D0:1;
                UInt8 Force_AGC5_gain:1;
                UInt8 UNUSED_I1_D0:1;
                UInt8 AGC5_Do_step:2;
                UInt8 AGC5_loop_off:1;
#endif
            }bF;
        }uBx25;

        union
        {
            UInt8 RF_Cal_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Offset_Cprog0:2;
                UInt8 RFCAL_Freq0:2;
                UInt8 RFCAL_Offset_Cprog1:2;
                UInt8 RFCAL_Freq1:2;
#else
                UInt8 RFCAL_Freq1:2;
                UInt8 RFCAL_Offset_Cprog1:2;
                UInt8 RFCAL_Freq0:2;
                UInt8 RFCAL_Offset_Cprog0:2;
#endif
            }bF;
        }uBx26;

        union
        {
            UInt8 RF_Cal_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Offset_Cprog2:2;
                UInt8 RFCAL_Freq2:2;
                UInt8 RFCAL_Offset_Cprog3:2;
                UInt8 RFCAL_Freq3:2;
#else
                UInt8 RFCAL_Freq3:2;
                UInt8 RFCAL_Offset_Cprog3:2;
                UInt8 RFCAL_Freq2:2;
                UInt8 RFCAL_Offset_Cprog2:2;
#endif
            }bF;
        }uBx27;

        union
        {
            UInt8 RF_Cal_byte_3;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Offset_Cprog4:2;
                UInt8 RFCAL_Freq4:2;
                UInt8 RFCAL_Offset_Cprog5:2;
                UInt8 RFCAL_Freq5:2;
#else
                UInt8 RFCAL_Freq5:2;
                UInt8 RFCAL_Offset_Cprog5:2;
                UInt8 RFCAL_Freq4:2;
                UInt8 RFCAL_Offset_Cprog4:2;
#endif
            }bF;
        }uBx28;

        union
        {
            UInt8 RF_Cal_byte_4;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Offset_Cprog6:2;
                UInt8 RFCAL_Freq6:2;
                UInt8 RFCAL_Offset_Cprog7:2;
                UInt8 RFCAL_Freq7:2;
#else
                UInt8 RFCAL_Freq7:2;
                UInt8 RFCAL_Offset_Cprog7:2;
                UInt8 RFCAL_Freq6:2;
                UInt8 RFCAL_Offset_Cprog6:2;
#endif
            }bF;
        }uBx29;

        union
        {
            UInt8 RF_Cal_byte_5;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Offset_Cprog8:2;
                UInt8 RFCAL_Freq8:2;
                UInt8 RFCAL_Offset_Cprog9:2;
                UInt8 RFCAL_Freq9:2;
#else
                UInt8 RFCAL_Freq9:2;
                UInt8 RFCAL_Offset_Cprog9:2;
                UInt8 RFCAL_Freq8:2;
                UInt8 RFCAL_Offset_Cprog8:2;
#endif
            }bF;
        }uBx2A;

        union
        {
            UInt8 RF_Cal_byte_6;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Offset_Cprog10:2;
                UInt8 RFCAL_Freq10:2;
                UInt8 RFCAL_Offset_Cprog11:2;
                UInt8 RFCAL_Freq11:2;
#else
                UInt8 RFCAL_Freq11:2;
                UInt8 RFCAL_Offset_Cprog11:2;
                UInt8 RFCAL_Freq10:2;
                UInt8 RFCAL_Offset_Cprog10:2;
#endif
            }bF;
        }uBx2B;

        union
        {
            UInt8 RF_Filters_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RF_Filter_Bypass:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 AGC2_loop_off:1;
                UInt8 Force_AGC2_gain:1;
                UInt8 RF_Filter_Gv:2;
                UInt8 RF_Filter_Band:2;
#else
                
				UInt8 RF_Filter_Band:2;
                UInt8 RF_Filter_Gv:2;
                UInt8 Force_AGC2_gain:1;
                UInt8 AGC2_loop_off:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 RF_Filter_Bypass:1;
#endif
            }bF;
        }uBx2C;

        union
        {
            UInt8 RF_Filters_byte_2;
            struct
            {
                UInt8 RF_Filter_Cap:8;
            }bF;
        }uBx2D;

        union
        {
            UInt8 RF_Filters_byte_3;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 AGC2_Do_step:2;
                UInt8 Gain_Taper:6;
#else
                UInt8 Gain_Taper:6;
                UInt8 AGC2_Do_step:2;
#endif
            }bF;
        }uBx2E;

        union
        {
            UInt8 RF_Band_Pass_Filter_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RF_BPF_Bypass:1;
                UInt8 UNUSED_I0_D0:4;
                UInt8 RF_BPF:3;
#else
                UInt8 RF_BPF:3;
                UInt8 UNUSED_I0_D0:4;
                UInt8 RF_BPF_Bypass:1;
#endif
            }bF;
        }uBx2F;

        union
        {
            UInt8 CP_Current_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:1;
                UInt8 N_CP_Current:7;
#else
                UInt8 N_CP_Current:7;
                UInt8 UNUSED_I0_D0:1;
#endif
            }bF;
        }uBx30;

        union
        {
            UInt8 AGCs_DetOut_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 Up_AGC5:1;
                UInt8 Do_AGC5:1;
                UInt8 Up_AGC4:1;
                UInt8 Do_AGC4:1;
                UInt8 Up_AGC2:1;
                UInt8 Do_AGC2:1;
                UInt8 Up_AGC1:1;
                UInt8 Do_AGC1:1;
#else
                UInt8 Do_AGC1:1;
                UInt8 Up_AGC1:1;
                UInt8 Do_AGC2:1;
                UInt8 Up_AGC2:1;
                UInt8 Do_AGC4:1;
                UInt8 Up_AGC4:1;
                UInt8 Do_AGC5:1;
                UInt8 Up_AGC5:1;
#endif
            }bF;
        }uBx31;

        union
        {
            UInt8 RFAGCs_Gain_byte_1;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:2;
                UInt8 AGC2_Gain_Read:2;
                UInt8 AGC1_Gain_Read:4;
#else
                UInt8 AGC1_Gain_Read:4;
                UInt8 AGC2_Gain_Read:2;
                UInt8 UNUSED_I0_D0:2;
#endif
            }bF;
        }uBx32;

        union
        {
            UInt8 RFAGCs_Gain_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:5;
                UInt8 TOP_AGC3_Read:3;
#else
                UInt8 TOP_AGC3_Read:3;
                UInt8 UNUSED_I0_D0:5;
#endif
            }bF;
        }uBx33;

        union
        {
            UInt8 IFAGCs_Gain_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I0_D0:3;
                UInt8 AGC5_Gain_Read:2;
                UInt8 AGC4_Gain_Read:3;
#else
                UInt8 AGC4_Gain_Read:3;
                UInt8 AGC5_Gain_Read:2;
                UInt8 UNUSED_I0_D0:3;
#endif
            }bF;
        }uBx34;

        union
        {
#ifdef _TARGET_PLATFORM_MSB_FIRST
#else
#endif
            UInt8 RSSI_byte_1;
            UInt8 RSSI;
        }uBx35;

        union
        {
            UInt8 RSSI_byte_2;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 UNUSED_I1_D0:2;
                UInt8 RSSI_AV:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 RSSI_Cap_Reset_En:1;
                UInt8 RSSI_Cap_Val:1;
                UInt8 RSSI_Ck_Speed:1;
                UInt8 RSSI_Dicho_not:1;
#else
                UInt8 RSSI_Dicho_not:1;
                UInt8 RSSI_Ck_Speed:1;
                UInt8 RSSI_Cap_Val:1;
                UInt8 RSSI_Cap_Reset_En:1;
                UInt8 UNUSED_I0_D0:1;
                UInt8 RSSI_AV:1;
                UInt8 UNUSED_I1_D0:2;
#endif
            }bF;
        }uBx36;

        union
        {
            UInt8 Misc_byte;
            struct
            {
#ifdef _TARGET_PLATFORM_MSB_FIRST
                UInt8 RFCAL_Phi2:2;
                UInt8 DDS_Polarity:1;
                UInt8 RFCAL_DeltaGain:4;
                UInt8 IRQ_Polarity:1;
#else
                UInt8 IRQ_Polarity:1;
                UInt8 RFCAL_DeltaGain:4;
                UInt8 DDS_Polarity:1;
                UInt8 RFCAL_Phi2:2;
#endif
            }bF;
        }uBx37;

        union
        {
            UInt8 rfcal_log_0;
            struct       
            {
                UInt8 rfcal_log_0:8;
            }bF;
        }uBx38;

        union
        {
            UInt8 rfcal_log_1;
            struct       
            {
                UInt8 rfcal_log_1:8;
            }bF;
        }uBx39;

        union
        {
            UInt8 rfcal_log_2;
            struct       
            {
                UInt8 rfcal_log_2:8;
            }bF;
        }uBx3A;

        union
        {
            UInt8 rfcal_log_3;
            struct       
            {
                UInt8 rfcal_log_3:8;
            }bF;
        }uBx3B;

        union
        {
            UInt8 rfcal_log_4;
            struct       
            {
                UInt8 rfcal_log_4:8;
            }bF;
        }uBx3C;

        union
        {
            UInt8 rfcal_log_5;
            struct       
            {
                UInt8 rfcal_log_5:8;
            }bF;
        }uBx3D;

        union
        {
            UInt8 rfcal_log_6;
            struct       
            {
                UInt8 rfcal_log_6:8;
            }bF;
        }uBx3E;

        union
        {
            UInt8 rfcal_log_7;
            struct       
            {
                UInt8 rfcal_log_7:8;
            }bF;
        }uBx3F;

        union
        {
            UInt8 rfcal_log_8;
            struct       
            {
                UInt8 rfcal_log_8:8;
            }bF;
        }uBx40;

        union
        {
            UInt8 rfcal_log_9;
            struct       
            {
                UInt8 rfcal_log_9:8;
            }bF;
        }uBx41;

        union
        {
            UInt8 rfcal_log_10;
            struct       
            {
                UInt8 rfcal_log_10:8;
            }bF;
        }uBx42;

        union
        {
            UInt8 rfcal_log_11;
            struct       
            {
                UInt8 rfcal_log_11:8;
            }bF;
        }uBx43;

    } TDA182I2_I2C_Map_t, *pTDA182I2_I2C_Map_t;

    typedef struct _tmTDA182I2_RFCalProg_t {
        UInt8   Cal_number;
        Int8    DeltaCprog;
        Int8    CprogOffset;
    } tmTDA182I2_RFCalProg_t, *ptmTDA182I2_RFCalProg_t;

    typedef struct _tmTDA182I2_RFCalCoeffs_t {
        UInt8   Sub_band;
        UInt8   Cal_number;
        Int32   RF_A1;
        Int32   RF_B1;
    } tmTDA182I2_RFCalCoeffs_t, *ptmTDA182I2_RFCalCoeffs_t;

#define TDA182I2_RFCAL_PROG_ROW (12)
#define TDA182I2_RFCAL_COEFFS_ROW (8)

    typedef struct _tmddTDA182I2Object_t {
        tmUnitSelect_t              tUnit;
        tmUnitSelect_t              tUnitW;
        ptmbslFrontEndMutexHandle   pMutex;
        Bool                        init;
        tmbslFrontEndIoFunc_t       sRWFunc;
        tmbslFrontEndTimeFunc_t     sTime;
        tmbslFrontEndDebugFunc_t    sDebug;
        tmbslFrontEndMutexFunc_t    sMutex;
        tmddTDA182I2PowerState_t    curPowerState;
        Bool                        bIRQWait;
        TDA182I2_I2C_Map_t          I2CMap;
    } tmddTDA182I2Object_t, *ptmddTDA182I2Object_t, **pptmddTDA182I2Object_t;


    extern tmErrorCode_t ddTDA182I2GetIRQ_status(ptmddTDA182I2Object_t pObj, UInt8* puValue);
    extern tmErrorCode_t ddTDA182I2GetMSM_XtalCal_End(ptmddTDA182I2Object_t pObj, UInt8* puValue);

    extern tmErrorCode_t ddTDA182I2WaitIRQ(ptmddTDA182I2Object_t pObj, UInt32 timeOut, UInt32 waitStep, UInt8 irqStatus);
    extern tmErrorCode_t ddTDA182I2WaitXtalCal_End(ptmddTDA182I2Object_t pObj, UInt32 timeOut, UInt32 waitStep);

    extern tmErrorCode_t ddTDA182I2Write(ptmddTDA182I2Object_t pObj, UInt8 uSubAddress, UInt8 uNbData);
    extern tmErrorCode_t ddTDA182I2Read(ptmddTDA182I2Object_t pObj, UInt8 uSubAddress, UInt8 uNbData);
    extern tmErrorCode_t ddTDA182I2Wait(ptmddTDA182I2Object_t pObj, UInt32 Time);

    extern tmErrorCode_t ddTDA182I2MutexAcquire(ptmddTDA182I2Object_t   pObj, UInt32 timeOut);
    extern tmErrorCode_t ddTDA182I2MutexRelease(ptmddTDA182I2Object_t   pObj);
	extern tmErrorCode_t tmddTDA182I2AGC1_Adapt(tmUnitSelect_t tUnit);

#ifdef __cplusplus
}
#endif

#endif // _TMDD_TDA182I2LOCAL_H //---------------
