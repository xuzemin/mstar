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

#ifndef _RAM_H_
#define _RAM_H_

#include "datatype.h"
#include "Board.h"

#ifndef RM_DEVICE_ADR
#define RM_DEVICE_ADR    0xA0
#endif

#ifndef RM_HDCP_ADR
#define RM_HDCP_ADR    0xA4
#endif

#if (ENABLE_OAD || (INPUT_HDMI_VIDEO_COUNT > 0))

#ifdef _RAM_C_
#define _RAMDEC_
#else
#define _RAMDEC_ extern
#endif

// debug
//#define RAM_DEBUG_EN

#ifdef RAM_DEBUG_EN
#define RAM_PUTSTR(str)            putstr(str)
#define RAM_PRINTF(str,para)    printf(str,para)
#else
#define RAM_PUTSTR(str)            printf(str)           //jaly
#define RAM_PRINTF(str,para)    printf(str,para)    //jaly
#endif

//_RAMDEC_ bit g_bDebugRam;

/////////////////////////////////////
// Definition
/////////////////////////////////////


#if (RM_EEPROM_TYPE <= RM_TYPE_24C02)
#define RM_PAGE_WRITE_LEN    8
#elif (RM_EEPROM_TYPE == RM_TYPE_24C16)
#define RM_PAGE_WRITE_LEN    16
#elif (RM_EEPROM_TYPE == RM_TYPE_24C32 || RM_EEPROM_TYPE == RM_TYPE_24C64)
#define RM_PAGE_WRITE_LEN    32
#elif  ( RM_EEPROM_TYPE == RM_TYPE_24C512 )
#define RM_PAGE_WRITE_LEN    128
#else
#define RM_PAGE_WRITE_LEN    16
#endif

// <24c16 EEPROM>      ------------------------------------
// [Device Address] = | 1 | 0 | 1 | 0 | P2 | P1 | P0 | R/W |
//                     ------------------------------------
#define rmCalDeviceAdr(rmID, wIndex)    (rmID | ((HIBYTE(wIndex) & 0x07)) << 1)

/////////////////////////////////////
// Subroutines
/////////////////////////////////////
_RAMDEC_ U8 msAPI_rmReadByte(U16 wIndex);
_RAMDEC_ void msAPI_rmBurstReadBytes(U16 wIndex, U8 *pBuf, U16 ucBufLen);

_RAMDEC_ void msAPI_rmPageWrite(U16 wIndex, U8 *pBuf, U8 ucBufLen);
_RAMDEC_ void msAPI_rmWriteByte(U16 wIndex, U8 ucVal);
_RAMDEC_ void msAPI_rmBurstWriteBytes(U16 wIndex, U8 *pBuf, U16 ucBufLen);

_RAMDEC_ void msAPI_hdcpkeyBurstReadBytes(U16 wIndex, U8 *pBuf, U16 ucBufLen);
_RAMDEC_ void msAPI_hdcpkeyBurstWriteBytes(U16 wIndex, U8 *pBuf, U16 ucBufLen);
_RAMDEC_ void msAPI_hdcpkeyReadByte(U16 wIndex, U8 *pBuf);
_RAMDEC_ void msAPI_hdcpkeyWriteByte(U16 wIndex, U8 ucVal);

#endif
#endif
