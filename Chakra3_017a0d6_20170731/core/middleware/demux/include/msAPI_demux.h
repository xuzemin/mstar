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

#ifndef __MSAPI_DMX_H__
#define __MSAPI_DMX_H__

////////////////////////////////////////////////////////////////////////////////
///
/// @file msAPI_demxu.h
/// @author MStar Semiconductor Inc.
/// @brief Demux API wrapper
///
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                                Include files                               */
/******************************************************************************/
#include "Board.h"

#include "datatype.h"
#include "apiDMX.h"


/******************************************************************************/
/*                                   Define                                   */
/******************************************************************************/
// For New TSP driver
// To Do: This define constant should be remove after test and verification, 2009/04/03
#define ENABLE_NEW_DMX_INTERFACE            TRUE
#define CSA_ENABLE 0//1

#if (ENABLE_NEW_DMX_INTERFACE)
#define MSAPI_DMX_INVALID_PID               0x1fff
#define MSAPI_DMX_INVALID_FLT_ID            DMX_DMXID_NULL
#define MSAPI_DMX_TIMEOUT_INFINITE          0xffff
#define MSAPI_DMX_MATCH_PATTERN_LENGTH      16

#if 0
        #define MSAPI_DMX_SEC1K_FILTER_NUMBER       8
        #define MSAPI_DMX_SEC4K_FILTER_NUMBER       16 //MGT, EAS, Eit Ett
        #define MSAPI_DMX_SEC4K_EIT_FILTER_NUMBER   0 //for Eit/Ett used
        #define MSAPI_DMX_MAX_FILTER_NUMBER         32//Demux filter max number is 32
        #define MSAPI_DMX_USABLE_FILTER_NUMBER      16
#else

// Whisky: Pid filter= 48,  Sec filter=32
// Milan:  Pid filter= 64,  Sec filter=64
// Marlon: Pid filter= 64,  Sec filter=64


        #define MSAPI_DMX_SEC1K_FILTER_START        0
        #define MSAPI_DMX_SEC1K_FILTER_NUMBER       8
        #define MSAPI_DMX_SEC1K_FILTER_END          (MSAPI_DMX_SEC1K_FILTER_START + MSAPI_DMX_SEC1K_FILTER_NUMBER )

        #define MSAPI_DMX_SEC4K_FILTER_START        MSAPI_DMX_SEC1K_FILTER_END
        #define MSAPI_DMX_SEC4K_FILTER_NUMBER       16 //MGT, EAS, Eit, Ett
        #define MSAPI_DMX_SEC4K_FILTER_END          (MSAPI_DMX_SEC4K_FILTER_START + MSAPI_DMX_SEC4K_FILTER_NUMBER )

        //#define MSAPI_DMX_SEC4K_EIT_FILTER_NUMBER   0 //for Eit/Ett used

        #define MSAPI_DMX_SEC_NONE_FILTER_START     MSAPI_DMX_SEC4K_FILTER_END
        #define MSAPI_DMX_SEC_NONE_FILTER_NUMBER    8 // VDEC, Audio, OAD, Subtitle
        #define MSAPI_DMX_SEC_NONE_FILTER_END       (MSAPI_DMX_SEC_NONE_FILTER_START + MSAPI_DMX_SEC_NONE_FILTER_NUMBER )

        #define MSAPI_DMX_MAX_FILTER_NUMBER         32//Demux filter max number is 32

        #define MSAPI_DMX_USABLE_FILTER_NUMBER      32//16
#endif

//#define MSAPI_DEMUX_SEC_FILTER_TOTAL    (MSAPI_DMX_SEC1K_FILTER_NUMBER + MSAPI_DMX_SEC4K_FILTER_NUMBER + MSAPI_DMX_SEC4K_EIT_FILTER_NUMBER)
#define MSAPI_DEMUX_SEC_FILTER_TOTAL    (MSAPI_DMX_SEC1K_FILTER_NUMBER + MSAPI_DMX_SEC4K_FILTER_NUMBER )

#if( (MSAPI_DEMUX_SEC_FILTER_TOTAL + MSAPI_DMX_SEC_NONE_FILTER_NUMBER) > MSAPI_DMX_MAX_FILTER_NUMBER )
    #ERROR "Section filter number is over flow"
#endif


#define MSAPI_DMX_SECTION_1K                1024
#define MSAPI_DMX_SECTION_4K                4096
#endif
#define MSAPI_DMX_RECORD_FILTER_NUMBER      16
#if(CSA_ENABLE == 1)
#define CSA_FILTER_ID 100
#endif
/******************************************************************************/
/*                                   Macro                                    */
/******************************************************************************/
#define ENABLE_DEMUX_SW_CRC_CHECK         FALSE

/******************************************************************************/
/*                                   Enum                                     */
/******************************************************************************/
#if (ENABLE_NEW_DMX_INTERFACE)

#define MSAPI_DMX_FILTER_TYPE_VIDEO             1           // to   video    fifo
#define MSAPI_DMX_FILTER_TYPE_AUDIO             2           // to   audio    fifo
#define MSAPI_DMX_FILTER_TYPE_AUDIO2            3           // to   audio2   fifo
#define MSAPI_DMX_FILTER_TYPE_SUBTITLE          4           // to   subtitle buffer
#define MSAPI_DMX_FILTER_TYPE_TELETEXT          5           // to   teletext buffer
#define MSAPI_DMX_FILTER_TYPE_PES               6           // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_SECTION_1K        7           // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_SECTION_4K        8           // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_SECTION_VERSION   9           // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_SECTION_CRC       10          // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_PCR               11          // no   output
#define MSAPI_DMX_FILTER_TYPE_PACKET            12          // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_PACKET_PUSI       13          // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_PACKET_AF         14          // to   section  buffer
#define MSAPI_DMX_FILTER_TYPE_OAD_MONITOR       15          // to   oad      buffer
#define MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD      16          // to   oad      buffer
#define MSAPI_DMX_FILTER_TYPE_RECORD            17          // to   record   buffer
#define MSAPI_DMX_FILTER_TYPE_SECTION_EIT       19        // to dedicated eit buf

#define MSAPI_DMX_FILTER_TYPE_CSA_PACKET            0xFF

#define MSAPI_DMX_FILTER_SOURCE_TYPE_MASK       0xC0000000  // DMX filter source mask
#define MSAPI_DMX_FILTER_SOURCE_TYPE_LIVE       0x00000000  // DMX live stream filter source
#define MSAPI_DMX_FILTER_SOURCE_TYPE_FILE       0x80000000  // DMX file in filter type
#define MSAPI_DMX_FILTER_TYPE U32

typedef enum
{
    MSAPI_DMX_FILTER_STATUS_SECAVAILABLE    =  DMX_EVENT_DATA_READY,
    MSAPI_DMX_FILTER_STATUS_PESAVAILABLE    =  DMX_EVENT_DATA_READY,
    MSAPI_DMX_FILTER_STATUS_OVERFLOW        =  DMX_EVENT_BUF_OVERFLOW,
    MSAPI_DMX_FILTER_STATUS_OK,
    MSAPI_DMX_FILTER_STATUS_TIMEOUT,
    MSAPI_DMX_FILTER_STATUS_CRCINCORRECT,
    MSAPI_DMX_FILTER_STATUS_REQUESTMEET,
    MSAPI_DMX_FILTER_STATUS_COPYSECERR,
    MSAPI_DMX_FILTER_STATUS_ERROR
} MSAPI_DMX_FILTER_STATUS;

#endif

typedef enum
{
    MSAPI_DMX_SCRAMBLING_SOURCE_NONE            =  0x00,       // no scrambling
    MSAPI_DMX_SCRAMBLING_SOURCE_TS_VIDEO        =  0x01,       // packet layer scrambling
    MSAPI_DMX_SCRAMBLING_SOURCE_TS_AUDIO        =  0x02,       // pes layer scrambling
    MSAPI_DMX_SCRAMBLING_SOURCE_PES_VIDEO       =  0x04,       // packet layer scrambling
    MSAPI_DMX_SCRAMBLING_SOURCE_PES_AUDIO       =  0x08,       // pes layer scrambling
    MSAPI_DMX_SCRAMBLING_SOURCE_TIMEOUT         =  0x10,       // no scrambling

    MSAPI_DMX_SCRAMBLING_SOURCE_NO_FILTER       =  0x20,       // no scrambling

} MSAPI_DMX_SCRAMBLING_SOURCE;

#if 0
#define MSAPI_DMX_BYPASS_PID                0x1fff


//<<filter status>>==============================================================================//
typedef enum
{
    MSAPI_DMX_FILTER_STATUS_OK              =  1,
    MSAPI_DMX_FILTER_STATUS_TIMEOUT         =  2,
    MSAPI_DMX_FILTER_STATUS_SECAVAILABLE    =  3,
    MSAPI_DMX_FILTER_STATUS_CRCINCORRECT    =  4,
    MSAPI_DMX_FILTER_STATUS_REQUESTMEET     =  5,
    MSAPI_DMX_FILTER_STATUS_PESAVAILABLE    =  6,
    MSAPI_DMX_FILTER_STATUS_COPYSECERR      =  7,
    MSAPI_DMX_FILTER_STATUS_OVERFLOW        =  8,
    MSAPI_DMX_FILTER_STATUS_ERROR           =  9
} MSAPI_DMX_FILTER_STATUS;

//<<filter type>>================================================================================//
typedef enum
{
    MSAPI_DMX_FILTER_TYPE_VIDEO             =  1,       // to   video    fifo
    MSAPI_DMX_FILTER_TYPE_AUDIO             =  2,       // to   audio    fifo
    MSAPI_DMX_FILTER_TYPE_AUDIO2             =  3,        // to   audio2    fifo
    MSAPI_DMX_FILTER_TYPE_SUBTITLE          =  4,       // to   subtitle buffer
    MSAPI_DMX_FILTER_TYPE_TELETEXT          =  5,       // to   teletext buffer
    MSAPI_DMX_FILTER_TYPE_PES               =  6,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_SECTION_1K        =  7,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_SECTION_4K        =  8,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_SECTION_VERSION   =  9,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_SECTION_CRC       = 10,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_PCR                = 11,        // no   output
    MSAPI_DMX_FILTER_TYPE_PACKET            = 12,        // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_PACKET_PUSI       = 13,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_PACKET_AF         = 14,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_OAD                = 15,        // to   oad      buffer
    MSAPI_DMX_FILTER_TYPE_RECORD            = 16,       // to   record   buffer
    MSAPI_DMX_FILTER_TYPE_SECTION_VER_1K    = 17,       // to   section  buffer
    MSAPI_DMX_FILTER_TYPE_SECTION_CRC_1K    = 18        // to   section  buffer
} MSAPI_DMX_FILTER_TYPE;

#endif


/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/
#if (ENABLE_NEW_DMX_INTERFACE)
typedef struct _MS_DMX_SECTIONMONITOR_PARA
{
    U16 u16PID;
    U32 u32SectionFltType;
    U8 au8MatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8MaskByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8NotMatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    void (*pfNotify)(U8 u8FID, DMX_EVENT enEvent);
    U16 u16TimeoutMilliSec;
    DMX_SECT_MODE SectMode;
    U8* pu8FID;
} MS_DMX_SECTIONMONITOR_PARA;

typedef struct _MS_DMX_SECTIONGET_PARA
{
    U16 u16PID;
    U32 u32SectionFltType;
    U8 au8MatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8MaskByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8NotMatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8* pu8Section;
    U16 u16MaxSecSize;
    U16 u16TimeoutMilliSec;
    BOOLEAN bCheckCrc;
} MS_DMX_SECTIONGET_PARA;
#endif

#if 0
/*data structure ================================================================================*/
//<<section monitor parameter>>==================================================================//
typedef struct msAPI_Dmx_SectionMonitor_Para
{
    U16 u16PID;
    MSAPI_DMX_FILTER_TYPE enSectionFltType;
    U8 au8MatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8MaskByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8NotMatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    void (*pfNotify)(U8 u8FID, MSAPI_DMX_FILTER_STATUS enFilterStatus);
    U16 u16TimeoutMilliSec;
    BOOLEAN bOneShot;
    U8* pu8FID;
} _msAPI_Dmx_SectionMonitor_Para;

//<<section get parameter>>======================================================================//
typedef struct msAPI_Dmx_SectionGet_Para
{
    U16 u16PID;
    MSAPI_DMX_FILTER_TYPE enSectionFltType;
    U8 au8MatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8MaskByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8 au8NotMatchByte[MSAPI_DMX_MATCH_PATTERN_LENGTH];
    U8* pu8Section;
    U16 u16MaxSecSize;
    U16 u16TimeoutMilliSec;
    BOOLEAN bCheckCrc;
} _msAPI_Dmx_SectionGet_Para;
#endif


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

INTERFACE BOOL msAPI_DMX_CheckCRC32(U8* pu8Section);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Close(U8 u8FltID);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Stop(U8 u8FltID);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Reset(U8 u8FltID);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Start(U8 u8FltID);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Pid(U8 u8FltID, U16* pu16Pid, BOOL bSet);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Proc(U8 u8DmxId);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_StartFilter(U16 u16Pid, U32 u32FltType, U8 *pu8FID);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_SectionMonitor(MS_DMX_SECTIONMONITOR_PARA * pstSectionMonitor, BOOL bFileIn);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_SectionGet(MS_DMX_SECTIONGET_PARA * pstSectionGet);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_Open(MS_DMX_SECTIONMONITOR_PARA * pstSectionMonitor, U32 *u32StartAddress, U32 *u32Size);

// Function to manage demux filter
INTERFACE void msAPI_DMX_CloseFilter(U8 u8FltID);
INTERFACE void msAPI_DMX_RestartFilter(U8 u8FltID);
INTERFACE DMX_FILTER_STATUS msAPI_DMX_CopyData(MS_U8 u8DmxId, MS_U8* pu8Buf, MS_U32 u32BufSize, MS_U32* pu32ActualSize, MS_U32* pu32RmnSize, DMX_CheckCb pfCheckCB);

INTERFACE BOOLEAN msAPI_DMX_IsCSA_ON(void);
#if(CSA_ENABLE == 1)
INTERFACE void msAPI_DMX_CSA_Enable(BOOLEAN bEnable, U8 u8FilterGroup);
#endif

#if(ENABLE_ATSC)
INTERFACE MSAPI_DMX_SCRAMBLING_SOURCE msAPI_DMX_ScramblingGet(U16 u16VideoPID, U16 u16AudioPID, U16 u16TimeoutMilliSec, BOOLEAN bEnPesScramble);
#endif

void msAPI_DMX_Print_AllFilter(void);
U8 msAPI_DMX_GetMatchByte_ByFid(U8 u8Fid);

U8 msAPI_DMX_Get_FreeSec4KFilterCount(void);

void msAPI_DMX_Init(void);

#undef INTERFACE
#endif  /* MSAPI_DEMUX_H */

