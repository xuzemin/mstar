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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_Subtitle.h
/// @brief API for subtitle function
/// @author MStar Semiconductor, Inc.
//
////////////////////////////////////////////////////////////////////////////////
#ifndef _MSAPI_SUBTITLE_H
#define _MSAPI_SUBTITLE_H

//-------------------------------------------------------------------------------------------------
// Include files:
//-------------------------------------------------------------------------------------------------
#include "datatype.h"
#include "MsTypes.h"
#if defined (CMODEL)||defined(LIB_SUBTITLE)
#include "msAPI_Subtitle_Decoder.h"
#endif
#if defined(BUILD_LIB)
#include "MsVersion.h"
#endif


#ifdef _MSAPI_SUBTITLE_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

#ifndef DLL_PUBLIC
#define DLL_PUBLIC __attribute__ ((visibility ("default"))) 
#define DLL_LOCAL __attribute__ ((visibility ("hidden")))
#endif

//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
// Version string
#define MSIF_SUB_LIB_CODE           {'S','B','T','L'}                   //Lib code
#define MSIF_SUB_LIBVER             {'0','1'}                           //LIB version
#define MSIF_SUB_BUILDNUM           {'0','2'}                           //Build Number
#define MSIF_SUB_CHANGELIST         {'0','d','9','0','2','d','9','0'}   //P4 ChangeList Number

#define SUBTITLE_VER                  /* Character String for DRV/API version  */ \
    MSIF_TAG,                         /* 'MSIF'                                           */ \
    MSIF_CLASS,                       /* '00'                                              */ \
    MSIF_CUS,                         /* 0x0000                                         */ \
    MSIF_MOD,                         /* 0x0000                                         */ \
    MSIF_CHIP,                                                         \
    MSIF_CPU,                                                          \
    MSIF_SUB_LIB_CODE,                /* IP__                                             */ \
    MSIF_SUB_LIBVER,                  /* 0.0 ~ Z.Z                                      */ \
    MSIF_SUB_BUILDNUM,                /* 00 ~ 99                                        */ \
    MSIF_SUB_CHANGELIST,              /* CL#                                             */ \
    MSIF_OS


//-------------------------------------------------------------------------------------------------
// Macros
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Type and Structure Declaration
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Extern Global Variabls
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// Extern Functions
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC INTERFACE U32 msAPI_Subtitle_SetPTS(U8 *pu8bff, U32 u32STC);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_DeInit(void);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_SetPageIDs(U16 u16CPID, U16 u16APID);
DLL_PUBLIC INTERFACE BOOLEAN msAPI_Subtitle_CheckPTS(U32 u32STC);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_Init_Queue(U32 u32Adr, U32 u32Len);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_Init_Display(U16 u16VideoWidth, U16 u16VideoHeight);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_Init_Display_OP(void);
DLL_PUBLIC INTERFACE BOOLEAN msAPI_Subtitle_GetLibVer(const MSIF_Version **ppVersion);
DLL_PUBLIC INTERFACE void  msAPI_Subtitle_SetFreeRunTime(U8 u8FreeRunTime);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_Remove(U32 u32STC);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_Remove_Expired(U32 u32STC);

//-------------------------------------------------------------------------------------------------
// Decoder library
//-------------------------------------------------------------------------------------------------
DLL_PUBLIC INTERFACE void msAPI_Subtitle_GetLIBVerString( U8 *pVer );
DLL_PUBLIC INTERFACE U32 msAPI_Subtitle_Queue_GetSDRAMAddress(U16 u16Len);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_SetSF(U8 u8SubtitleCurrentAspect); //-jp-20070825
DLL_PUBLIC INTERFACE BOOLEAN msAPI_Subtitle_Decoder_Main(void);
DLL_PUBLIC INTERFACE BOOLEAN msAPI_Subtitle_Queue_Push(U32 u32Address, U16 u16Len, U32 u32PTS);
DLL_PUBLIC INTERFACE BOOLEAN msAPI_Subtitle_Queue_Push_BG(U32 u32Address, U16 u16Len, U32 u32PTS, BOOLEAN bFlag);
DLL_PUBLIC INTERFACE U32 msAPI_Subtitle_GetDemuxBuffer(void);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_Renderer_Clear(void);
DLL_PUBLIC INTERFACE U32 msAPI_Subtitle_GetQueueLength(void);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_SetGOPParameter(BOOLEAN bSet, U32 u32Addr);
DLL_PUBLIC INTERFACE void msAPI_Subtitle_SetReduceGwin(BOOLEAN bSet);

#undef INTERFACE
#endif // _MSAPI_SUBTITLE_H
