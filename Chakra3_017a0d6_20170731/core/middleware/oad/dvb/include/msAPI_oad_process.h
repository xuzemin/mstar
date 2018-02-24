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
#ifndef _MSAPI_OAD_PROCESS_H_
#define _MSAPI_OAD_PROCESS_H_

/*------------------------------------------------------------------------------
*   include files
*-----------------------------------------------------------------------------*/
#include "datatype.h"
#include "MsTypes.h"
#include "msAPI_Memory.h"
#if defined(BUILD_LIB)
#include "MsVersion.h"
#endif

/*------------------------------------------------------------------------------
*   Local defines
*-----------------------------------------------------------------------------*/
#define MSIF_OAD_LIB_CODE         {'O','A','D','_'} //Lib code
#define MSIF_OAD_LIBVER           {'0','0'} //LIB version
#define MSIF_OAD_BUILDNUM         {'0','0'} //Build Number
#define MSIF_OAD_CHANGELIST       {'0','0','3','6','6','6','4','8'} //P4 ChangeList Number

#define MW_OAD_VER                  /* Character String for DRV/API version             */  \
    MSIF_TAG,                   /* 'MSIF'                                           */  \
    MSIF_CLASS,                 /* '00'                                             */  \
    MSIF_CUS,                   /* 0x0000                                           */  \
    MSIF_MOD,                   /* 0x0000                                           */  \
    MSIF_CHIP,                                                                          \
    MSIF_CPU,                                                                           \
    MSIF_OAD_LIB_CODE,              /* IP__                                             */  \
    MSIF_OAD_LIBVER,                /* 0.0 ~ Z.Z                                        */  \
    MSIF_OAD_BUILDNUM,              /* 00 ~ 99                                          */  \
    MSIF_OAD_CHANGELIST,            /* CL#                                              */  \
    MSIF_OS

#define SECTION_HEADER_SIZE 8
#define BIOP_HEADER_LEN     44

#define DSMMSG_HEADER_SIZE  12
#define DSIMSG_HEADER_SIZE  20
#define DIIMSG_HEADER_SIZE  20
#define DDBMSG_HEADER_SIZE  6

#define OAD_CONTROL_SECTION_TYPE 0x3B   // control sections: DSI, DII
#define OAD_DATA_SECTION_TYPE    0x3C   // data sections:    DDB
#define OAD_UNT_SECTION_TYPE     0x4B

#define OAD_DSMCC_MSGID_DSI     0x1006  // DSI
#define OAD_DSMCC_MSGID_DII     0x1002  // DII
#define OAD_DSMCC_MSGID_DDB     0x1003  // DDB

#define OAD_INVALID_ADDR    0xFFFFFFFFUL

#define OAD_MODE_INVALID    0xFF
#define OAD_MODE_DATACAR    0x00     // Data Carousel
#define OAD_MODE_OBJCAR     0x01     // Object Carousel (specially for UK)
#define MAX_SCHEDULE_COUNT  4

#define GET_2BYTE( cp ) ( ( ( (U16)(*cp) ) << 8 ) | ( ( (U16)(*(cp+1)) ) ) )
#define GET_3BYTE( cp ) ( ( ( (U32)(*cp) )<< 16 ) | ( ( (U32)(*(cp+1)) ) <<  8 ) | ( ( (U32)(*(cp+2)) ) ) )
#define GET_4BYTE( cp ) ( ( ( (U32)(*cp) )<< 24 ) | ( ( (U32)(*(cp+1)) ) << 16 ) | ( ( (U32)(*(cp+2)) ) << 8 ) | ( (U32)(*(cp+3)) ) )


/*------------------------------------------------------------------------------
*   Debug defines
*-----------------------------------------------------------------------------*/
#define ENABLE_OAD_DBG      FALSE
#if ENABLE_OAD_DBG
#define OAD_INFO(x)         x
#define OAD_DEBUG(x)        x
#define OAD_ASSERT(x)       x       // dont turn off this
#else
#define OAD_INFO(x)
#define OAD_DEBUG(x)
#define OAD_ASSERT(x)
#endif

typedef struct
{
    U32 u32StartTime;       // Unit: sec
    U32 u32EndTime;         // Unit: sec
    U8  u8FinalAvail: 1;    // 1: final version, no further update
    U8  u8PeriodFlag: 1;    // 1: Periodicity
    U8  u8PeriodUnit: 2;    // 00: Second, 01: Minute, 10: Hour, 11:Day
    U8  u8DurationUnit: 2;  // 00: Second, 01: Minute, 10: Hour, 11:Day
    U8  u8EstimateUnit: 2;  // 00: Second, 01: Minute, 10: Hour, 11:Day
    U8  u8Period;
    U8  u8Duration;
    U8  u8Estimate;
} UNT_SCHEDULE;

typedef struct
{
   U16 association_tag ;
} UNT_LOCATION;

typedef struct
{
    UNT_LOCATION untLocation ;
    UNT_SCHEDULE untSchedule[MAX_SCHEDULE_COUNT] ;
} UNT_DESCRIPTOR ;

typedef struct
{
    U16 u16Year;
    U8 u8Month;
    U8 u8Day;
    U8 u8Hour;
    U8 u8Min;
    U8 u8Sec;
} ST_TIME_OAD;

typedef enum
{
    OAD_SUCCEED = 0 ,
    OAD_FAIL,
    OAD_COMPLETE,
    OAD_CONTINUE
}OAD_STATUS_REPORT_TYPE;

void msAPI_OAD_ClearData( void );
void msAPI_OAD_SetOui(U8 byte1, U8 byte2, U8 byte3);
void msAPI_OAD_SetDDBBuffer( U32, U32 );
U32 msAPI_OAD_GetDDBBufferAddr( void );
void msAPI_OAD_SetVersionCheck(U8 (*cb)(U16,U8 *));
U8 msAPI_OAD_GetDsiVersionNum(void);
void msAPI_OAD_GetModuleInfo( U32 *startAddr, U32 *moduleSize );
U8 msAPI_OAD_GetProgress( void );
U32 msAPI_OAD_GetMISVersionId( void );
void msAPI_OAD_SetOADFileFound(BOOLEAN bFound);
BOOLEAN msAPI_OAD_IsOADFileFound(void);
U32 msAPI_OAD_MemAlloc ( U32 u32MemSize );
OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessDSI ( U8 * );
OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessDII ( U8 * );
OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessDDB ( U8 * ,U16 *,U16 *,U32 *,U16 *);
OAD_STATUS_REPORT_TYPE msAPI_OAD_ProcessUNT ( U8 * ,UNT_DESCRIPTOR *);
BOOL msAPI_OAD_GetLibVer(const MSIF_Version **ppVersion);
extern MS_U32 MsOS_PA2KSEG1(MS_U32 addr);
U32 msAPI_OAD_GetDownloadId(void);
U32 msAPI_OAD_GetGroupId(void);
U32 msAPI_OAD_GetModuleSize(void);
U32 msAPI_OAD_GetBlockSize(void);
#endif // _MSAPI_OAD_PROCESS_H_
