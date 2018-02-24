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
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MSAPI_DMX_IF_H__
#define __MSAPI_DMX_IF_H__

////////////////////////////////////////////////////////////////////////////////
///
/// @file msAPI_demxu.h
/// @author MStar Semiconductor Inc.
/// @brief Demux API wrapper
///
////////////////////////////////////////////////////////////////////////////////
#if(ENABLE_DTV)
/******************************************************************************/
/*                                Include files                               */
/******************************************************************************/
#include "datatype.h"

#include "mapp_demux.h"


/******************************************************************************/
/*                                   Define                                   */
/******************************************************************************/
// For New TSP driver
// To Do: This define constant should be remove after test and verification, 2009/04/03
#define SI_DMX_INVALID_FLT_ID						0xff
#define SI_DMX_MAX_FILTER_NUMBER         32
#define SI_DMX_MATCH_PATTERN_LENGTH			16
#define SI_DMX_INVALID_PID               0x1fff
#define SI_DMX_TIMEOUT_INFINITE          0xffff
#if (M7_DVBS_FAST_SCAN_ENABLE)
#define SI_DMX_FST_FNT_TIMEOUT 10000
#endif   // #if (M7_DVBS_FAST_SCAN_ENABLE)

#define SI_DMX_FILTER_TYPE_VIDEO             1           // to   video    fifo
#define SI_DMX_FILTER_TYPE_AUDIO             2           // to   audio    fifo
#define SI_DMX_FILTER_TYPE_AUDIO2            3           // to   audio2   fifo
#define SI_DMX_FILTER_TYPE_SUBTITLE          4           // to   subtitle buffer
#define SI_DMX_FILTER_TYPE_TELETEXT          5           // to   teletext buffer
#define SI_DMX_FILTER_TYPE_PES               6           // to   section  buffer
#define SI_DMX_FILTER_TYPE_SECTION_1K        7           // to   section  buffer
#define SI_DMX_FILTER_TYPE_SECTION_4K        8           // to   section  buffer
#define SI_DMX_FILTER_TYPE_SECTION_VERSION   9           // to   section  buffer
#define SI_DMX_FILTER_TYPE_SECTION_CRC       10          // to   section  buffer
#define SI_DMX_FILTER_TYPE_PCR               11          // no   output
#define SI_DMX_FILTER_TYPE_PACKET            12          // to   section  buffer
#define SI_DMX_FILTER_TYPE_PACKET_PUSI       13          // to   section  buffer
#define SI_DMX_FILTER_TYPE_PACKET_AF         14          // to   section  buffer
#define SI_DMX_FILTER_TYPE_OAD_MONITOR       15          // to   oad      buffer
#define SI_DMX_FILTER_TYPE_OAD_DOWNLOAD      16          // to   oad      buffer
#define SI_DMX_FILTER_TYPE_RECORD            17          // to   record   buffer
#define SI_DMX_FILTER_TYPE_SECTION_EIT 19        // to dedicated eit buf
#define SI_DMX_FILTER_TYPE_CSA_PACKET            0xFF
#define SI_DMX_FILTER_SOURCE_TYPE_MASK       0xC0000000  // DMX filter source mask
#define SI_DMX_FILTER_SOURCE_TYPE_LIVE       0x00000000  // DMX live stream filter source
#define SI_DMX_FILTER_SOURCE_TYPE_FILE       0x80000000  // DMX file in filter type
#define SI_DMX_FILTER_SOURCE_TYPE_ERROR			 0xFFFFFFFF

#define SI_DMX_SECT_MODE_CONTI        0x00000000 ///< DMX receive section contiguously
#define SI_DMX_SECT_MODE_ONESHOT      0x00000001 ///< DMX only receive one section
// optional
#define SI_DMX_SECT_MODE_CRCCHK       0x00000002 ///< DMX enables CRC check
#define SI_DMX_SECT_MODE_AUTO_ADDR    0x00000004 ///< DMX align read pointer to write pointer when get write pointer // OBSOLETE

#define SI_DMX_SEC1K_FILTER_NUMBER       8
#define SI_DMX_SEC4K_FILTER_NUMBER       6
#define SI_DMX_SEC4K_EIT_FILTER_NUMBER 2 //for eit schedule
#define SI_DMX_MAX_FILTER_NUMBER         32//(MSAPI_DMX_SEC1K_FILTER_NUMBER+MSAPI_DMX_SEC4K_FILTER_NUMBER)
#define SI_DMX_USABLE_FILTER_NUMBER      16

/******************************************************************************/
/*                                   Macro                                    */
/******************************************************************************/


/******************************************************************************/
/*                                   Enum                                     */
/******************************************************************************/
/// DMX status indicator
typedef enum
{
    SI_DMX_FILTER_STATUS_OK,
    SI_DMX_FILTER_STATUS_ERROR,
} SI_DMX_FILTER_STATUS;

typedef enum
{
    SI_DMX_FILTER_CB_STATUS_SECAVAILABLE,
    SI_DMX_FILTER_CB_STATUS_PESAVAILABLE = SI_DMX_FILTER_CB_STATUS_SECAVAILABLE,
    SI_DMX_FILTER_CB_STATUS_OVERFLOW,
    SI_DMX_FILTER_CB_STATUS_OK,
    SI_DMX_FILTER_CB_STATUS_TIMEOUT,
    SI_DMX_FILTER_CB_STATUS_CRCINCORRECT,
    SI_DMX_FILTER_CB_STATUS_REQUESTMEET,
    SI_DMX_FILTER_CB_STATUS_COPYSECERR,
    SI_DMX_FILTER_CB_STATUS_ERROR
} SI_DMX_FILTER_CB_STATUS;


/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/
typedef struct _SI_DMX_SECTIONMONITOR_PARA
{
    U16 u16PID;
    U32 u32SectionFltType;
    U8 au8MatchByte[SI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8MaskByte[SI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8NotMatchByte[SI_DMX_MATCH_PATTERN_LENGTH];
    void (*pfNotify)(U8 u8FID, U32 enEvent);
    U16 u16TimeoutMilliSec;
    U32 SectMode;
    U8* pu8FID;
} SI_DMX_SECTIONMONITOR_PARA;

typedef struct _SI_DMX_SECTIONGET_PARA
{
    U16 u16PID;
    U32 u32SectionFltType;
    U8 au8MatchByte[SI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8MaskByte[SI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8NotMatchByte[SI_DMX_MATCH_PATTERN_LENGTH];
    U8* pu8Section;
    U16 u16MaxSecSize;
    U16 u16TimeoutMilliSec;
    BOOLEAN bCheckCrc;
} SI_DMX_SECTIONGET_PARA;



/******************************************************************************/
/*                                 Variables                                  */
/******************************************************************************/


/******************************************************************************/
/*                            Function Prototypes                             */
/******************************************************************************/
#ifdef MSAPI_DEMUX_C
#define INTERFACE
#else
#define INTERFACE extern
#endif


INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Stop(U8 u8FltID);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Close(U8 u8FltID);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_CopyData(U8 u8DmxId, U8* pu8Buf, U32 u32BufSize, U32* pu32ActualSize, U32* pu32RmnSize);
INTERFACE void msAPI_SI_Dmx_RestartFilter(U8 u8FID);
INTERFACE BOOL msAPI_SI_Dmx_CheckCRC32(U8* pu8Section);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_SectionMonitor(SI_DMX_SECTIONMONITOR_PARA *pstSectionMonitor, BOOL bFileIn);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_SectionGet(SI_DMX_SECTIONGET_PARA * pstSectionGet);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Proc(U8 u8DmxId);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Start(U8 u8FltID);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Reset(U8 u8FltID);
INTERFACE void msAPI_SI_Dmx_CloseFilter(U8 u8FID);
INTERFACE SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Pid(U8 u8FltID, U16* pu16Pid, BOOL bSet);
INTERFACE SI_DMX_FILTER_CB_STATUS msAPI_SI_Dmx_Filter_Cb_Status(U32 u8Event);
INTERFACE U32 msAPI_SI_Dmx_Get_FilterType(U32 u8FilterType);
INTERFACE U32 msAPI_SI_Dmx_Get_SecMode(U32 u32SecMode);

#undef INTERFACE

#endif
#endif  /* MSAPI_DEMUX_H */

