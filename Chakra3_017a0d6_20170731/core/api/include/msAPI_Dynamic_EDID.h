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

///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file   msApi_Dynamic_EDID.h
/// @brief  Scaler API layer Interface
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////
#if ENABLE_DYNAMIC_EDID
#ifndef _MSAPI_DYNAMIC_EDID_H_
#define _MSAPI_DYNAMIC_EDID_H_

#ifdef _MSAPI_DYNAMIC_EDID_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define Vendor_4K2K_1   1   // 4K*2K 29.97 30HZ
#define Vendor_4K2K_2   2   // 4K*2K 25HZ
#define Vendor_4K2K_3   3   // 4K*2k 24HZ
#define Vendor_4K2K_4   4   // 4K*2K 24HZ(SMPTE)

#define EDID_Audio      0
#define EDID_Video      1
#define EDID_Vendor     2
#define EDID_Speaker    3

#define EDID_Start      0x80

#define DYN_EDID_DEFAULT        0
#define DYN_EDID_SUPPORT        1
#define DYN_EDID_NOT_SUPPORT    2

#define EDID_TYPE(X)    (((X)>>5) & 0x07)
#define EDID_LEN(X)     ((X) & 0x1F)

#define AudioTypeLen    3
#define COLSIZE         32
#define ROWSIZE         4
//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------
#define EDID_AUDIO_FORMAT_SHIFT 3
#define EDID_AUDIO_FORMAT_MASK  (0x78)//BMASK(6:3)
typedef struct
{
    U8 au8Type[AudioTypeLen];
    // u8Type[0]    bit 6:3
        #define AUDIO_LPCM          (0x01<<3)
        #define AUDIO_AC3           (0x02<<3)
        #define AUDIO_MPEG1         (0x03<<3)
        #define AUDIO_MP3           (0x04<<3)
        #define AUDIO_MPEG2         (0x05<<3)
        #define AUDIO_AAC           (0x06<<3)
        #define AUDIO_DTS           (0x07<<3)
        #define AUDIO_ATRAC         (0x08<<3)
        #define AUDIO_SACD          (0x09<<3)
        #define AUDIO_DDP           (0x0A<<3)
        #define AUDIO_DTS_HD        (0x0B<<3)
        #define AUDIO_DOLBY_TRUEHD  (0x0C<<3)
        #define AUDIO_DST           (0x0D<<3)
        #define AUDIO_WMA_PRO       (0x0E<<3)
    // u8Type[0]    bit 2:0
        #define AUDIO_CH_1      0
        #define AUDIO_CH_2      1
        #define AUDIO_CH_3      2
        #define AUDIO_CH_4      3
        #define AUDIO_CH_5      4
        #define AUDIO_CH_6      5
        #define AUDIO_CH_7      6
        #define AUDIO_CH_8      7
    // u8Type[1]    bit 6:0
        #define AUDIO_192kHZ    (0x01<<6)
        #define AUDIO_176kHZ    (0x01<<5)
        #define AUDIO_96kHZ     (0x01<<4)
        #define AUDIO_88kHZ     (0x01<<3)
        #define AUDIO_48kHZ     (0x01<<2)
        #define AUDIO_44kHZ     (0x01<<1)
        #define AUDIO_32kHZ     (0x01<<0)
    // u8Type[2]    bit 2:0
        #define AUDIO_24BIT     (0x01<<2)
        #define AUDIO_20BIT     (0x01<<1)
        #define AUDIO_16BIT     (0x01<<0)
}ST_EDID_Audio;


#define EDID_HDMI_PORT1 0x10
#define EDID_HDMI_PORT2 0x20
#define EDID_HDMI_PORT3 0x30
#define EDID_HDMI_PORT4 0x40

typedef struct
{
    U8 bSAD;
    U8 b4K2K;
    U8 b3D;
    U8 u8PAPort;    // Set HDMI Port
    U8 u8PAOut;     // Return PA Address
    ST_EDID_Audio stAudio;
}ST_EDID_Control;

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------
//INTERFACE U8 msApi_Dynamic_EDID(U8* au8In, U8* au8Out);

MS_BOOL msApi_Dynamic_EDID_main(U8* au8In, U8* au8Out, ST_EDID_Control *pStatus);
MS_BOOL msApi_Dynamic_EDID_Init(U8* au8In, U8 (*au8Temp)[COLSIZE]);
void msApi_Dynamic_EDID_Audio(U8 bSAD, ST_EDID_Audio *pStatus, U8 (*au8Temp)[COLSIZE]);
void msApi_Dynamic_EDID_Vendor_PA(U8 u8Add, U8 (*au8Temp)[COLSIZE]);
void msApi_Dynamic_EDID_Vendor_4K2K(U8 b4K2K, U8 (*au8Temp)[COLSIZE]);
void msApi_Dynamic_EDID_Vendor_3D(U8 b3D, U8 (*au8Temp)[COLSIZE]);
U8 msApi_Dynamic_EDID_CheckSum(U8* au8In,U8 u8Start, U8 u8End);
U8 msApi_Dynamic_EDID_Merger(U8* au8In, U8* au8Out, U8 (*au8Temp)[COLSIZE]);

#undef INTERFACE
#endif  // _MSAPI_DYNAMIC_EDID_H_
#endif  //ENABLE_DYNAMIC_EDID
