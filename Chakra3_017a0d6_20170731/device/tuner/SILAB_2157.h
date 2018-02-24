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
/**********************************************************************
 Copyright (c) 2006-2009 MStar Semiconductor, Inc.
 All rights reserved.

 Unless otherwise stipulated in writing, any and all information contained
 herein regardless in any format shall remain the sole proprietary of
 MStar Semiconductor Inc. and be kept in strict confidence
 (MStar Confidential Information) by the recipient.
 Any unauthorized act including without limitation unauthorized disclosure,
 copying, use, reproduction, sale, distribution, modification, disassembling,
 reverse engineering and compiling of the contents of MStar Confidential
 Information is unlawful and strictly prohibited. MStar hereby reserves the
 rights to any and all damages, losses, costs and expenses resulting therefrom.

* Class : device_tuner_si_2157
* File  : device_tuner_si_2157.h
**********************************************************************/

#ifndef __SILAB_2157_H__
#define __SILAB_2157_H__

#ifdef __SILAB_2157_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

// #include "mapi_base.h"
// #include "mapi_tuner.h"

#define mcSHOW_HW_MSG(x)   // printf x
#define mcSHOW_DBG_MSG4(x) // printf x
// #define SiTRACE               Si2157_printf
#define printTun_dev(x)    // printf x

#ifdef VIF_TUNER_TYPE
#undef VIF_TUNER_TYPE
#endif
#ifdef VIF_CR_RATE_B
#undef VIF_CR_RATE_B
#endif
#ifdef VIF_CR_INVERT_B
#undef VIF_CR_INVERT_B
#endif
#ifdef VIF_CR_RATE_GH
#undef VIF_CR_RATE_GH
#endif
#ifdef VIF_CR_INVERT_GH
#undef VIF_CR_INVERT_GH
#endif
#ifdef VIF_CR_RATE_DK
#undef VIF_CR_RATE_DK
#endif
#ifdef VIF_CR_INVERT_DK
#undef VIF_CR_INVERT_DK
#endif
#ifdef VIF_CR_RATE_I
#undef VIF_CR_RATE_I
#endif
#ifdef VIF_CR_INVERT_I
#undef VIF_CR_INVERT_I
#endif
#ifdef VIF_CR_RATE_L
#undef VIF_CR_RATE_L
#endif
#ifdef VIF_CR_INVERT_L
#undef VIF_CR_INVERT_L
#endif
#ifdef VIF_CR_RATE_LL
#undef VIF_CR_RATE_LL
#endif
#ifdef VIF_CR_INVERT_LL
#undef VIF_CR_INVERT_LL
#endif
#ifdef VIF_CR_RATE_MN
#undef VIF_CR_RATE_MN
#endif
#ifdef VIF_CR_INVERT_MN
#undef VIF_CR_INVERT_MN
#endif

#ifdef  D_DMD_IF_DVBT_8M
#undef D_DMD_IF_DVBT_8M
#endif
#ifdef  D_DMD_IF_DVBT_7M
#undef D_DMD_IF_DVBT_7M
#endif
#ifdef  D_DMD_IF_DVBT_6M
#undef D_DMD_IF_DVBT_6M
#endif
#ifdef  D_DMD_IF_DVBC_8M
#undef D_DMD_IF_DVBC_8M
#endif
#ifdef  D_DMD_IF_DVBC_7M
#undef D_DMD_IF_DVBC_7M
#endif
#ifdef  D_DMD_IF_DVBC_6M
#undef D_DMD_IF_DVBC_6M
#endif
#ifdef  D_DMD_IF_DVBT2_8M
#undef D_DMD_IF_DVBT2_8M
#endif
#ifdef  D_DMD_IF_DVBT2_7M
#undef D_DMD_IF_DVBT2_7M
#endif
#ifdef  D_DMD_IF_DVBT2_6M
#undef D_DMD_IF_DVBT2_6M
#endif
#ifdef  D_DMD_TUNER_IQSWAP
#undef D_DMD_TUNER_IQSWAP
#endif

#define C_Si2157_IF_FREQUENCY          ((U16)  6000)  /* kHz */

// Digital IF
#define QAM_6M     C_Si2157_IF_FREQUENCY
#define QAM_8M     C_Si2157_IF_FREQUENCY
#define ATSC_6M    C_Si2157_IF_FREQUENCY
#define ISDBT_6M   C_Si2157_IF_FREQUENCY
#define DVBT_1p7M  C_Si2157_IF_FREQUENCY
#define DVBT_6M    C_Si2157_IF_FREQUENCY 
#define DVBT_7M    C_Si2157_IF_FREQUENCY
#define DVBT_8M    C_Si2157_IF_FREQUENCY
#define DVBT_10M   C_Si2157_IF_FREQUENCY
#define DMBT_8M    C_Si2157_IF_FREQUENCY

//PLL lock check parameters
#define C_Si2157_PF_TO_CF_SHIFT_B 2250 /*KHZ*/
#define C_Si2157_PF_TO_CF_SHIFT_G 2750 /*KHZ*/
#define C_Si2157_PF_TO_CF_SHIFT_DK 2750 /*KHZ*/
#define C_Si2157_PF_TO_CF_SHIFT_I  2750 /*KHZ*/
#define C_Si2157_PF_TO_CF_SHIFT_L  2750 /*KHZ*/
#define C_Si2157_PF_TO_CF_SHIFT_M  1750 /*KHZ*/
#define C_Si2157_PF_TO_CF_SHIFT_L1 2750 /*KHZ*/

// center frequencies
#define C_Si2157_IF_CENTER_B  4750 /*KHZ*/
#define C_Si2157_IF_CENTER_GH 4250 /*KHZ*/
#define C_Si2157_IF_CENTER_DK 5250 /*KHZ*/
#define C_Si2157_IF_CENTER_I  4750 /*KHZ*/
#define C_Si2157_IF_CENTER_L  5250 /*KHZ*/
#define C_Si2157_IF_CENTER_L1 5250 /*KHZ*/
#define C_Si2157_IF_CENTER_M  4250 /*KHZ*/
#define C_Si2157_IF_CENTER_N  4250 /*KHZ*/


// Analog picture carrier
#define ATV_VC_MN  (double)(C_Si2157_IF_CENTER_M  + C_Si2157_PF_TO_CF_SHIFT_M)
#define ATV_VC_B   (double)(C_Si2157_IF_CENTER_B  + C_Si2157_PF_TO_CF_SHIFT_B)
#define ATV_VC_GH  (double)(C_Si2157_IF_CENTER_GH + C_Si2157_PF_TO_CF_SHIFT_G)
#define ATV_VC_I   (double)(C_Si2157_IF_CENTER_I  + C_Si2157_PF_TO_CF_SHIFT_I)
#define ATV_VC_DK  (double)(C_Si2157_IF_CENTER_DK + C_Si2157_PF_TO_CF_SHIFT_DK)
#define ATV_VC_L   (double)(C_Si2157_IF_CENTER_L  + C_Si2157_PF_TO_CF_SHIFT_L)
#define ATV_VC_LL  (double)(C_Si2157_IF_CENTER_L1 + C_Si2157_PF_TO_CF_SHIFT_L1)

// [21:0], CR_RATE for Video_Carrier_BBB KHz, HEX((Video_Carrier_BBB/43200.0) * (2^22))
#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   (MS_U32)(ATV_VC_B*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  (MS_U32)(ATV_VC_GH*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  (MS_U32)(ATV_VC_DK*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   (MS_U32)(ATV_VC_I*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   (MS_U32)(ATV_VC_L*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  (MS_U32)(ATV_VC_LL*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_LL                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  (MS_U32)(ATV_VC_MN*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side

#define D_DMD_IF_DVBT_8M  DVBT_8M
#define D_DMD_IF_DVBT_7M  DVBT_7M
#define D_DMD_IF_DVBT_6M  DVBT_6M
#define D_DMD_IF_DVBC_8M  QAM_8M
#define D_DMD_IF_DVBC_7M  QAM_8M
#define D_DMD_IF_DVBC_6M  QAM_8M
#define D_DMD_IF_DVBT2_8M  DVBT_8M
#define D_DMD_IF_DVBT2_7M  DVBT_7M
#define D_DMD_IF_DVBT2_6M  DVBT_6M
#define D_DMD_TUNER_IQSWAP 1


#define VHF_LOWMIN_FREQ              46250L    // KHz
#define VHF_LOWMAX_FREQ             142000L    // KHz
#define VHF_HIGHMIN_FREQ            149000L    // KHz
#define VHF_HIGHMAX_FREQ            426000L    // KHz
#define UHF_MIN_FREQ                434000L    // KHz
#define UHF_MAX_FREQ                865250L    // KHz
#define TUNER_IF_FREQ_KHz            38900L    // KHz
#define TUNER_L_PRIME_IF_FREQ_KHz    33950L    // KHz

/// the tuner mode
typedef enum
{
    /// DTV, DVBT
    E_TUNER_DTV_DVB_T_MODE = 0x00,
    /// DTV, DVBC
    E_TUNER_DTV_DVB_C_MODE ,
    /// DTV, DVBS
    E_TUNER_DTV_DVB_S_MODE ,
    /// DTV, DTMB
    E_TUNER_DTV_DTMB_MODE ,
    /// DTV, ATSC
    E_TUNER_DTV_ATSC_MODE ,
    /// ATV, PAL
    E_TUNER_ATV_PAL_MODE ,
    /// ATV, SECAM-L'
    E_TUNER_ATV_SECAM_L_PRIME_MODE ,
    /// ATV, NTSC
    E_TUNER_ATV_NTSC_MODE ,
    /// DTV, ISDB
    E_TUNER_DTV_ISDB_MODE ,
    /// DTV, DVBT2
    E_TUNER_DTV_DVB_T2_MODE,
    /// ATV, SECAM-L
    E_TUNER_ATV_SECAM_L_MODE ,
    /// ATV, SECAM-L
    E_TUNER_DTV_QAM_US_MODE ,
    /// invalid
    E_TUNER_INVALID
} EN_TUNER_MODE;

/// Audio SIF Standard Type
typedef enum
{
    ///< Audio standard BG
    E_AUDIOSTANDARD_BG_                     = 0x00,
    ///< Audio standard BG A2
    E_AUDIOSTANDARD_BG_A2_                  = 0x01,
    ///< Audio standard BG NICAM
    E_AUDIOSTANDARD_BG_NICAM_               = 0x02,
    ///< Audio standard I
    E_AUDIOSTANDARD_I_                      = 0x03,
    ///< Audio standard DK
    E_AUDIOSTANDARD_DK_                     = 0x04,
    ///< Audio standard DK1 A2
    E_AUDIOSTANDARD_DK1_A2_                 = 0x05,
    ///< Audio standard DK2 A2
    E_AUDIOSTANDARD_DK2_A2_                 = 0x06,
    ///< Audio standard DK3 A2
    E_AUDIOSTANDARD_DK3_A2_                 = 0x07,
    ///< Audio standard DK NICAM
    E_AUDIOSTANDARD_DK_NICAM_               = 0x08,
    ///< Audio standard L
    E_AUDIOSTANDARD_L_                      = 0x09,
    ///< Audio standard M
    E_AUDIOSTANDARD_M_                      = 0x0A,
    ///< Audio standard M BTSC
    E_AUDIOSTANDARD_M_BTSC_                 = 0x0B,
    ///< Audio standard M A2
    E_AUDIOSTANDARD_M_A2_                   = 0x0C,
    ///< Audio standard M EIA J
    E_AUDIOSTANDARD_M_EIA_J_                = 0x0D,
    ///< Not Audio standard
    E_AUDIOSTANDARD_NOTSTANDARD_            = 0x0F
} AUDIOSTANDARD_TYPE_;


INTERFACE void devTunerInit(void);
INTERFACE void devDigitalTuner_Init(void);
INTERFACE void devTunerSetFreq(U32 u32Freq);
INTERFACE void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth);
INTERFACE BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode);
INTERFACE BOOLEAN mdev_GetSignalStrength(float* f_strength);

#undef INTERFACE

#if 0
class device_tuner_si_2157 : public mapi_tuner
{
private:

    MAPI_BOOL m_bDeviceBusy;
public:

    // ------------------------------------------------------------
    // public operations
    // ------------------------------------------------------------
    device_tuner_si_2157(void);
    
    //-------------------------------------------------------------------------------------------------
    /// To connect this tuner module
    /// @param None
    /// @return             \b OUT: MAPI_TRUE or MAPI_FALSE
    //-------------------------------------------------------------------------------------------------
    MAPI_BOOL Connect(void);

    //-------------------------------------------------------------------------------------------------
    /// To disconnect this tuner module
    /// @param None
    /// @return             \b OUT: MAPI_TRUE or MAPI_FALSE
    //-------------------------------------------------------------------------------------------------
    MAPI_BOOL Disconnect(void);

    //-------------------------------------------------------------------------------------------------
    /// Set the frequency to the tuner module for ATV
    /// @param u32FreqKHz   \b IN: Input the frequency with the unit = KHz
    /// @param eBand        \b IN: Input the band (E_RFBAND_VHF_LOW, E_RFBAND_VHF_HIGH, or E_RFBAND_UHF)
    /// @return             \b OUT: MAPI_TRUE or MAPI_FALSE
    //-------------------------------------------------------------------------------------------------
    MAPI_BOOL ATV_SetTune(MAPI_U32 u32FreqKHz, RFBAND eBand, EN_TUNER_MODE eMode,MAPI_U8 u8OtherMode = 0xff);

    //-------------------------------------------------------------------------------------------------
    /// Set the frequency to the tuner module for DTV
    /// @param Freq         \b IN: Input the frequency with the unit = KHz
    /// @param eBandWidth   \b IN: Input the BandWidth (E_RF_CH_BAND_6MHz E_RF_CH_BAND_7MHz, or E_RF_CH_BAND_8MHz)
    /// @return             \b OUT: MAPI_TRUE or MAPI_FALSE
    //-------------------------------------------------------------------------------------------------
    MAPI_BOOL DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode);

    //-------------------------------------------------------------------------------------------------
    /// Reserve extend command for customer. If you don't need it, you skip it.
    /// @param u8SubCmd     \b IN: Commad defined by the customer.
    /// @param u32Param1    \b IN: Defined by the customer.
    /// @param u32Param2    \b IN: Defined by the customer.
    /// @param u32Param3    \b IN: Defined by the customer.
    /// @return             \b OUT: MAPI_TRUE or MAPI_FALSE
    //-------------------------------------------------------------------------------------------------
    MAPI_BOOL ExtendCommand(MAPI_U8 u8SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void* pvoidParam3);

    //-------------------------------------------------------------------------------------------------
    /// Init tuner
    /// @return 			\b OUT: MAPI_TRUE or MAPI_FALSE
    //-------------------------------------------------------------------------------------------------
    MAPI_BOOL InitTuner( void );

};
#endif
#endif // __SILAB_2157_H__

