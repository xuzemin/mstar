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
#ifndef _MAPP_BL_DEMUX_H_
#define _MAPP_BL_DEMUX_H_

/******************************************************************************/
/*                     macro                                 */
/******************************************************************************/
#define TSGetBitFromU8(ptr, bitn)           (((*(U8 *)ptr) >> bitn) & 0x01)
#define TSGetBitsFromU8(ptr, lsb, mask)     (((*(U8 *)ptr) >> lsb) & mask)
#define TSGetU16(ptr)                       ((((U8 *)ptr)[0] << 8) + ((U8 *)ptr)[1])
#define TSGetBitsFromU16(ptr, lsb, mask)    ((TSGetU16(ptr) >> lsb) & mask)
#define TSGetU32(ptr)                       ((((U8 *)ptr)[0] << 24) + (((U8 *)ptr)[1] << 16) + (((U8 *)ptr)[2] << 8) + (((U8 *)ptr)[3] << 0))
#define TSGetBitsFromU32(ptr, lsb, mask)    ((TSGetU32(ptr) >> lsb) & mask)


/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/
/* PID definition */
typedef enum
{
    BL_PID_PAT         = 0x0000,
} EN_BL_PSIP_PID;

/* A/V/PCR/TTX/SUBT */
typedef enum
{
    EN_BL_OAD_MONITOR_FID,
    EN_BL_OAD_DOWNLOAD_FID
} EN_BL_FID;
/******************************************************************************/
/*                     struct                                 */
/******************************************************************************/
typedef struct
{
    U32 u32SecMask;
    U8  u8LastSecNum;
    U8  u8SecCount;
    U16 u16SecLengthCount:15;
    U16 fIsTblReceived:1;
} ST_BL_DMXSEC_MONITOR;

/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_BL_DEMUX_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
INTERFACE void MApp_BL_Dmx_Init(U32 u32BufferStart, U32 u32BufferSize);
INTERFACE void MApp_BL_Dmx_CloseAllFilters(void);
INTERFACE void MApp_BL_Dmx_ResetPatSecTable(void);
INTERFACE void MApp_BL_Dmx_SetOadScan(BOOLEAN bEnable);
INTERFACE U8 MApp_BL_Dmx_GetTableFilterID(EN_BL_PSIP_TABLE enTable);
INTERFACE U8 MApp_BL_Dmx_GetOpenFilterChNums(void);
INTERFACE U8 *MApp_BL_Dmx_GetSI4KSectionBuffer(void);
INTERFACE U8 *MApp_BL_Dmx_GetFid(EN_BL_FID eFid);
INTERFACE void MApp_BL_Dmx_SetFid(U8 u8Fid, EN_BL_FID eFid);
INTERFACE void MApp_BL_Dmx_PAT_Monitor(void);
INTERFACE void MApp_BL_Dmx_PMTs_Monitor(void);
#undef INTERFACE
#endif

