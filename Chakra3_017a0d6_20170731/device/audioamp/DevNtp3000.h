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

#ifndef _DEV_NTP3000_
#define _DEV_NTP3000_

#ifdef AUDIO_AMP
    #define  AUDIO_EXT
#else
    #define  AUDIO_EXT  extern
#endif

#define     IIC_SW_NTP3000SLAVE_ADDR       0x54

//__start__  REGISTER  define list -------------
#define NTP_INPUT_FORMAT                 0x00
#define NTP_SERIAL_AUDIO_FORMAT          0x01
#define NTP_CLK_FREQ_CTRL                0x02
#define NTP_MISCELLANEOUS_CTRL           0x03
#define NTP_AUTOMUTE_CTRL_CH1_2          0x04
#define NTP_AUTOMUTE_CTRL_CH3            0x05
#define NTP_VARIOUS_CONFIG               0x06
#define NTP_ALC_CONFIG1                  0x07
#define NTP_ALC_CONFIG2                  0x08
#define NTP_ALC_CONFIG3                  0x09
#define NTP_MASTER_VOL_OVERRIDE          0x0A
#define NTP_PWM_PORT1_CTRL               0x0B
#define NTP_PWM_PORT2_CTRL               0x0C
#define NTP_PWM_PORT3_CTRL               0x0D
#define NTP_DRC_CTRL_CH1_2               0x0E
#define NTP_DRC_CTRL_CH3                 0x0F
#define NTP_DRC_CONFIG_CTRL              0x10
#define NTP_MOD_INDEX_NS_CTRL            0x11
#define NTP_PRESCALER_CTRL_CH1_2         0x12
#define NTP_PRESCALER_CTRL_CH3           0x13
#define NTP_AOUT_RISING_EDGE_DELAY       0x17
#define NTP_AOUT_FALLING_EDGE_DELAY      0x18
#define NTP_BOUT_RISING_EDGE_DELAY       0x19
#define NTP_BOUT_FALLING_EDGE_DELAY      0x1A
#define NTP_PWM_OFF_AUTO_PROTECT_CTRL    0x1B
#define NTP_AUTO_PROTECT_CTRL_MASKING    0x1C
#define NTP_PROTECT_CTRL1                0x1D
#define NTP_PROTECT_CTRL2                0x1E
#define NTP_SWITCHING_OFF_CTRL           0x1F
#define NTP_SOFTMUTE_CTRL                0x20
#define NTP_FBQ_FLAG_CH                  0x2C
#define NTP_MASTER_FINE_VOL              0x2D
#define NTP_MASTER_VOL                   0x2E
#define NTP_CHANNEL1_VOL                 0x2F
#define NTP_CHANNEL2_VOL                 0x30
#define NTP_CHANNEL3_VOL                 0x31
#define NTP_GEQ_GAIN_BAND1               0x32
#define NTP_GEQ_GAIN_BAND2               0x33
#define NTP_GEQ_GAIN_BAND3               0x34
#define NTP_GEQ_GAIN_BAND4               0x35
#define NTP_GEQ_GAIN_BAND5               0x36
#define NTP_GEQ_GAIN_BAND6               0x69
#define NTP_GEQ_GAIN_BAND7               0x6A
#define NTP_MIXER_GAIN1                  0x37
#define NTP_MIXER_GAIN2                  0x38
#define NTP_MIXER_GAIN3                  0x39
#define NTP_MIXER_GAIN4                  0x3A
#define NTP_MIXER_GAIN5                  0x3B
#define NTP_MIXER_GAIN6                  0x3C
#define NTP_BIQUAD_FILTER_CONFIG_CH1     0x3D
#define NTP_BIQUAD_FILTER_CONFIG_CH2     0x3E
#define NTP_BIQUAD_FILTER_COEFF          0x3F
#define NTP_3D_DELAY_AMOUNT              0x60
#define NTP_3D_EFFECT_CTRL_CONFIG        0x61
#define NTP_PWM_MODE_CTRL                0x62
#define NTP_STANDBY_2CH_MODE             0x63
#define NTP_SYSTEM_STATUS                0x75
//__end__  REGISTER  define list ----------------

void DevNtp3000Init(void);
void Ntp3000Mute_ON( void );
void Ntp3000Mute_OFF( void );
//******************************************************************************

#endif
