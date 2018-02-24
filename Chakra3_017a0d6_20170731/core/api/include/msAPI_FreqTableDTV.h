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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __API_FREQTABLEDTV_H__
#define __API_FREQTABLEDTV_H__

#include "Board.h"

#if ENABLE_DTV

#include "MApp_GlobalSettingSt.h"
#include "msAPI_Tuner.h"

//****************************************************************************
// Public attributes.
//****************************************************************************
#if 0
#if ENABLE_SBTVD_DTV_SYSTEM
#define MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)   14
#define MAX_UHF_PHYSICAL_CHANNEL_NUMBER                69
#elif( ENABLE_DVB_TAIWAN_APP )
#define MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)   14
#define MAX_UHF_PHYSICAL_CHANNEL_NUMBER                69
#elif ( ENABLE_DTMB_CHINA_APP )
#if ENABLE_DTMB_ADD_FREQUENCY
#define MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)   13
#define MAX_UHF_PHYSICAL_CHANNEL_NUMBER                73
#else
#define MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)   13
#define MAX_UHF_PHYSICAL_CHANNEL_NUMBER                68
#endif
#else
#define MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)   ((eCountry==E_AUSTRALIA)? 27 : 21)
#define MAX_UHF_PHYSICAL_CHANNEL_NUMBER        69
#endif

#else

    #define MIN_UHF_PHYSICAL_CHANNEL_NUMBER_DTMB                13

#if ENABLE_DTMB_ADD_FREQUENCY
    #define MAX_UHF_PHYSICAL_CHANNEL_NUMBER_DTMB                73
#else
    #define MAX_UHF_PHYSICAL_CHANNEL_NUMBER_DTMB                68
#endif

#if ENABLE_SBTVD_DTV_SYSTEM
    #define MIN_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT(eCountry)     14
#else
    #define MIN_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT(eCountry)     ((eCountry==E_AUSTRALIA)? 27 : 21)
#endif
    #define MAX_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT               69

#if ( ENABLE_DVB_TAIWAN_APP )
    #define MIN_UHF_PHYSICAL_CHANNEL_NUMBER_DVBT(eCountry)           14
#else
    #define MIN_UHF_PHYSICAL_CHANNEL_NUMBER_DVBT(eCountry)      ((eCountry==E_AUSTRALIA)? 27 : 21)
#endif
    #define MAX_UHF_PHYSICAL_CHANNEL_NUMBER_DVBT                69

#endif

#define MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER   121
#define MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER   141

//#define MAX_PHYSICAL_CHANNEL_NUMBER        MAX_UHF_PHYSICAL_CHANNEL_NUMBER
#define MAX_PHYSICAL_CHANNEL_NUM        99
//****************************************************************************
// Public functions.
//****************************************************************************

BOOLEAN msAPI_DFT_GetTSSetting(BYTE cRFChannelNumber, MS_TP_SETTING * pstTPSetting);
BOOLEAN msAPI_DFT_GetPhysicalChannelName(BYTE cRFChannelNumber, BYTE * sPhysicalChannelName, BYTE cBufferSize);
BYTE msAPI_DFT_GetFirstPhysicalChannelNumber(void);
BYTE msAPI_DFT_GetPrevPhysicalChannelNumber(BYTE cRFChannelNumber);
BYTE msAPI_DFT_GetNextPhysicalChannelNumber(BYTE cRFChannelNumber);
#if 0 //ENABLE_SZ_DTV_ADDCH_SCAN_FUNCTION
BYTE msAPI_GetNextEmptyPhysicalChannelNumber(BYTE cRFChannelNumber);
#endif
BYTE msAPI_DFT_GetPercentWithPhysicalChannelNumber(BYTE cRFChannelNumber);
BOOLEAN msAPI_DFT_Get_PHYSICAL_CHANNEL_NUMBER(U32 u32Frequency, U8 *u8RFIndex);
void msAPI_DFT_SetBandwidth(U8 u8BandWidth);
void msAPI_SetCrossBandwidth(BOOLEAN bIsCross);
U8 msAPI_DFT_GetBandwidth(void);
void msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(BOOLEAN bOneFreqScanFinished);
BOOLEAN msAPI_DFT_VHF_CrossBWFreq_GetFinishScanStatus(void);
#endif
#endif // __API_FREQTABLEDTV_H__

