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

#ifndef MAPP_EPGDB_ATSC_H
#define MAPP_EPGDB_ATSC_H


/******************************************************************************/
/*                              Include files                                 */
/******************************************************************************/
#include "datatype.h"
#include "sysinfo.h"
#include <stdio.h>

#include "msAPI_AtscEpgDb.h"

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/


// Features configuration
#define MONITOR_ETT_ALL     TRUE

// Patch for customer requirement
#define EIT_VN_CHANGE_FOR_RRT    TRUE   // patch for rrt5_0.trp which EIT has VN change but MGT does not

#define EPG_PARTIAL_DB    TRUE    // FALSE for display data after receving all 4 tables


#if (MONITOR_ETT_ALL)
// ETT Parameters
#define Max_NUM_OF_REPEAT_ETT       0x50
#endif


// Filter ID Limits
#define EIT_0_TIMEOUT               5000
#define EIT_1_TIMEOUT               6000
#define EIT_TIMEOUT                 60000   //60000
#define ETT_TIMEOUT                 60000   //60000

#if 1//(!ENABLE_ATSC_EPG_DB_2016)
// Service Limits
#define EPG_VCH_IN_DB               1     // number of EPG_SRV_BUF which save in sdram database
#if (ENABLE_ATSC_EPG_DB_2016)
#define EPG_VCH_IN_BUF              100     // number of EPG_SRV_BUF which save in xdata
#else
#define EPG_VCH_IN_BUF              1     // number of EPG_SRV_BUF which save in xdata
#endif
#endif

#if(!ENABLE_ATSC_EPG_DB_2016)
// Table Limits
  #if 0//(ENABLE_DTV_HD_FB)
    #define MAX_TBL_NUM             4  // max number of EIT-i which received
  #else
    #define MAX_TBL_NUM             8  // max number of EIT-i which received
  #endif
#endif

#define ETT_TBL_BIT_WISE            5
#define ETT_MAX_TBL_MASK            (U8)((1 << ETT_TBL_BIT_WISE)-1)

#define BASIC_TBL_NUM               4      // basic number of EIT-i which received


#define MAX_SEG_NUM                 32      // 8 sections are considered as 1 segment

#if(!ENABLE_ATSC_EPG_DB_2016)
#define MAX_EVENT_IN_TBL            50 //10       // max number of event in table
#endif

#define EPG_EITTITLE_MAX_STR_LEN    80 //Store 80 from max length 255
#define EPG_ETT_MAX_STR_LEN         512     //Store 512 from max length 4093

#define SUPPORT_LONG_ETT            ENABLE
#define EPG_LONG_ETT_MAX_STR_LEN    2048     //Store 512 from max length 4093

#if(!ENABLE_ATSC_EPG_DB_2016)
// String Pool Parameters
#define MAX_EIT_TITLE_LEN_OF_STR_POOL   (MAX_TBL_NUM*MAX_EVENT_IN_TBL*EPG_EITTITLE_MAX_STR_LEN) // max number of char save in sdram database
#define MAX_ETT_LEN_OF_STR_POOL         (MAX_TBL_NUM*MAX_EVENT_IN_TBL*EPG_ETT_MAX_STR_LEN)  // max number of char save in sdram database

// Event related parameters
// macro function to calculate the duration length of event
#define EPG_EVENT_LENGTH(x, y, z)   (((U32)((x)&0x0F) << 16) + ((U32)(y) << 8) + (U32)(z))
#endif

#define MAX_TBL_MASK                (U8)( (1 << MAX_TBL_NUM) - 1 )      // max EIT-i and ETT-i table mask
#define BASIC_TBL_MASK              (MAX_TBL_MASK&0x0F)      // EIT-0 and ETT-3 table mask
#define ADVANCE_TBL_MASK            (MAX_TBL_MASK&0xF0)      // EIT-4 and ETT-7 table mask

#if (ENABLE_ATSC_EPG_DB_2016)
#define NEW_EIT_RXOK_NUM            ((NEW_MAX_TAB_NUM+7)/8) //
#endif

#if(!ENABLE_ATSC_EPG_DB_2016)
// Event database map in SDRAM
#define EPG_EVENT_SIZE              (sizeof(MS_EPG_EVENT))

#define EPGBUF_START_ADR            (EVENTDB_SDRAM_ADR)
// A Table contain a program 3 hour event number ,event number experience value is small than 9
#define EVENTDB_EVENTBUF_START_ADR  (EPGBUF_START_ADR)
#define EPG_EVENTBUF_LEN            (MAX_TBL_NUM*MAX_EVENT_IN_TBL*EPG_EVENT_SIZE) // 8(Table)x50(Event)x124(Event structure)*1 Channel Number   must less than EPGSTR_LEN (~48K)
#define ATSC_EPG_EVENTBUF_END_ADR   (EVENTDB_EVENTBUF_START_ADR + EPG_EVENTBUF_LEN)

#define EPGSTR_EITTITLE_START_ADR   (ATSC_EPG_EVENTBUF_END_ADR)
#define EPGSTR_EITTITLE_LEN         (MAX_TBL_NUM*MAX_EVENT_IN_TBL*EPG_EITTITLE_MAX_STR_LEN) // 8(Table)x50(Event)x80(Event Title)+)*1 Channel Number   must less than EPGSTR_LEN (~31.25K)
#define ATSC_EPG_EITTITLE_END_ADR   (EPGSTR_EITTITLE_START_ADR + EPGSTR_EITTITLE_LEN)

#define EPGSTR_ETT_START_ADR        (ATSC_EPG_EITTITLE_END_ADR)
#define EPGSTR_ETT_LEN              (MAX_TBL_NUM*MAX_EVENT_IN_TBL*EPG_ETT_MAX_STR_LEN) // 8(Table)x50(Event)x512(Event ETT Max)*1 Channel Number  must less than EPGSTR_LEN (~200K)
#define ATSC_EPG_ETT_END_ADR        (EPGSTR_ETT_START_ADR + EPGSTR_ETT_LEN)
#endif


// According to CEA-766-A Table 3
// Valid value for 'TV Parental Guideline Age-Based Rating for Entire Audience '
// is 0~5
// Set MS_EPG_RATING.u8TVRatingForEntire as INVALID_TV_RATING_FOR_ENTIRE
// to indicate that no TV rating is received from CAD
#define INVALID_TV_RATING_FOR_ENTIRE    7

/******************************************************************************/
/*                                 Enum                                       */
/******************************************************************************/


/******************************************************************************/
/*                                 Structure                                  */
/******************************************************************************/
//
// Total 29 Bytes
typedef struct ATSC_EPGDB_PACK//__attribute__ ((__packed__))
{
    U8              fIsEttRxOk          : 1;    // check if extended event info is received
    //U8              fIsEttTimeout       : 1;    // check if extended event info is timeout
    //U8              fIsSingleVchMode    : 1;    // switch single/multiple service mode
    U8              RESERVED            : 5;

#if (!ENABLE_ATSC_EPG_DB_2016)
    U8              u8EitRxOK;                  // check if EIT-0 ~ EIT-7 is received
    U8              u8EitIsReceiving;           // check if EIT-0 ~ EIT-7 is receiving
#endif

    U8              u8MgtVersionNumber;         // check if there is MGT version number changed
    U8              u8CntFID;                   // count how many filter ID we have set to receive EIT

#if (ENABLE_ATSC_EPG_DB_2016)
    U8              au8FID[NEW_MAX_TAB_NUM];        // store the value of filter ID which demux return
    U8              au8CntSource[NEW_MAX_TAB_NUM];  // count how many virtual channel in EIT[i] we have received
    U8              au8SourceMask[NEW_MAX_TAB_NUM]; // check which virtual channel in EIT[i] we have received
#else
    U8              au8FID[MAX_TBL_NUM];        // store the value of filter ID which demux return
    U8              au8CntSource[MAX_TBL_NUM];  // count how many virtual channel in EIT[i] we have received
    U8              au8SourceMask[MAX_TBL_NUM]; // check which virtual channel in EIT[i] we have received
#endif

    U8              u8CntSourceNum;             // store how many virtual channel in this physical channel
#if (MONITOR_ETT_ALL)
  #if (!ENABLE_ATSC_EPG_DB_2016)
    U8              u8EttRxOK;                  // check if ETT-0 ~ ETT-7 is received
    U8              u8EttIsReceiving;           // check if ETT-0 ~ ETT-7 is receiving
    U16             au16CntEttRpt[MAX_TBL_NUM]; // check ETT repeat counter to decide when to close filter for ETT
  #endif
    U8              u8EttCntFID;                   // count how many filter ID we have set to receive Ett

  #if (ENABLE_ATSC_EPG_DB_2016)
    U8              au8EttFID[NEW_MAX_TAB_NUM];        // store the value of filter ID which Ett demux retur
  #else
    U8              au8EttFID[MAX_TBL_NUM];        // store the value of filter ID which Ett demux retur
  #endif
#endif

#if (ENABLE_ATSC_EPG_DB_2016)
    U8              u8EitRxOKNew[NEW_EIT_RXOK_NUM]; // check if EiT-0 ~ EiT-56 is received
    U8              u8EttRxOKNew[NEW_EIT_RXOK_NUM]; // check if ETT-0 ~ ETT-56 is received
    U8              u8EitIsReceivingNew[NEW_EIT_RXOK_NUM]; // check if EiT-0 ~ EiT-56 is receiving
    U8              u8EttIsReceivingNew[NEW_EIT_RXOK_NUM]; // check if EiT-0 ~ EiT-56 is receiving
    U16             au16CntEttRpt[NEW_MAX_TAB_NUM]; // check ETT repeat counter to decide when to close filter for ETT
#endif

#if (EIT_VN_CHANGE_FOR_RRT==TRUE)
    U8              u8FID_EitMonitorForRRT;
#endif

#if (ENABLE_ATSC_EPG_DB_2016)
    U16             au16SrcID[ATSC_EPG_VIR_CH_NUM];  // store source id of this physical channel, must list at the last
#else
    U16             au16SrcID[EPG_VCH_IN_BUF];  // store source id of this physical channel, must list at the last
#endif
} MS_EPG_DB_INFO;

#if( !ENABLE_ATSC_EPG_DB_2016 )
// Total 134 Bytes      -> sizeof (MS_EPG_VCH_MASK) * (EPG_VCH_IN_DB) should not excess 1 KBytes as defined in sysinfo.h
typedef struct
{
    // used to check if all sections of virtual channel has received
    U8              au8SecMask [MAX_TBL_NUM][MAX_SEG_NUM];          // 4 X 32 Bytes = 128 Bytes
    U8              u8CntSec[MAX_TBL_NUM];                          // 4 Bytes
    U8              u8TblMask;                  // check if EIT-i of virtual channel has received
    U8              fIsInSDRAM          : 1;    // if event info of this virutal channel has saved to sdram database
    U8              Reserved            : 7;
} MS_EPG_VCH_MASK;
#endif

// ===================================================================
#if( !ENABLE_ATSC_EPG_DB_2016 )

typedef struct ATSC_EPGDB_PACK // __attribute__ ((__packed__))
{
    U16             event_id            : 15;
    U16             fHasCCInfo          : 1;
    U32             start_time;
    U8              length[3];
    U16             u16DbTitlePos;      // offset of event title in sdram database
    U16             u16DbEttPos;        // offset of event extented text in sdram database
    U8              fIsEitUTF16         : 1;
    U8              fIsEttUTF16         : 1;
    U8              Reserved             :6;
    MS_EPG_RATING   stRating;
    MS_EPG_Caption_Service    stCaptionService;
} MS_EPG_EVENT;

typedef struct ATSC_EPGDB_PACK //__attribute__ ((__packed__))
{
    U16             u16Title_length;
    U8*             pu8Title_content;
} MS_EPG_EVENT_TITILE;

typedef struct ATSC_EPGDB_PACK
{
    U16             u16ETT_length;
    U8*             pu8ETT_content;
} MS_EPG_EVENT_ETT;
#endif

#if( !ENABLE_ATSC_EPG_DB_2016 )
// Total 976 Bytes      -> should less than EPG_DB_VCH_BUF_LEN in sysinfo.h
typedef struct ATSC_EPGDB_PACK //__attribute__ ((__packed__))
{
    U8              fIsFirstTime        : 1;
    U8              Reserved            : 7;
    U8              u8SrcIdx;
    U16             u16DBOffset;
    U16             u16DBOffsetETT;
    U32             u32MinStartTime;
    U32             u32MaxEndTime;
    U8              au8CntEvent_InTbl[MAX_TBL_NUM];                 // 4 Bytes
} MS_EPG_VCH_BUF;
#endif

// 6 Bytes
typedef struct
{
    U16             u16SourceID;
    U16             u16EventID;
    U8              u8Tbl;
    U8              u8FID;
} MS_EPG_ETT;

/******************************************************************************/
/*                       Global Variable Declarations                         */
/******************************************************************************/
#ifdef MAPP_EPGDB_A_C
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE MS_EPG_DB_INFO    stEpgDBInfo;

#if( !ENABLE_ATSC_EPG_DB_2016 )
INTERFACE MS_EPG_ETT        stEpgETT;
#endif


#if( !ENABLE_ATSC_EPG_DB_2016 )
INTERFACE MS_EPG_VCH_BUF    astEpgDbVchBuf[EPG_VCH_IN_DB];
INTERFACE MS_EPG_VCH_MASK   astEpgDbVchMask[EPG_VCH_IN_DB];
#endif


INTERFACE U8                au8EpgUiBuf[EPG_ETT_MAX_STR_LEN];

#if SUPPORT_LONG_ETT
INTERFACE U8                pu8EpgString[EPG_LONG_ETT_MAX_STR_LEN];
#else
INTERFACE U8                au8ETT[EPG_ETT_MAX_STR_LEN];
INTERFACE U8                pu8EpgString[EPG_ETT_MAX_STR_LEN];
#endif

#if( !ENABLE_ATSC_EPG_DB_2016 )
INTERFACE MS_EPG_EVENT      g_stRxEvent;
INTERFACE MS_EPG_EVENT      g_stUiEvent;
#endif


/******************************************************************************/
/*                       Global Function Prototypes                           */
/******************************************************************************/
INTERFACE void MApp_EpgDB_Init(void);
#if( !ENABLE_ATSC_EPG_DB_2016 )
INTERFACE void MApp_EpgDB_ContentInit(MS_EPG_VCH_BUF* pVch);
#endif
INTERFACE void MApp_EpgDB_Reset(void);
INTERFACE void MApp_EPG_Demux_Reset(void);
#if( !ENABLE_ATSC_EPG_DB_2016 )
INTERFACE void MApp_EpgDB_LoadEvent(U16 u16VchIdx, U8 u8EitIdx, U8 u8EventIdx, MS_EPG_EVENT *pstEvent);
INTERFACE BOOLEAN MApp_EpgDB_SaveEvent(U16 u16VchIdx, U8 u8EitIdx, U8 u8EventIdx, MS_EPG_EVENT * pstEvent);
INTERFACE void MApp_EpgDB_LoadEventTitle(U16 u16VchIdx, U32 u32srcaddr, MS_EPG_EVENT_TITILE* pSrcEventTitle, U16 u16MaxBufSize);
INTERFACE void MApp_EpgDB_SaveEventTitle(U16 u16VchIdx, U32 u32dstaddr, MS_EPG_EVENT_TITILE* pSrcEventTitle);
INTERFACE void MApp_EpgDB_LoadEventETT(U16 u16VchIdx, U32 u32srcaddr, MS_EPG_EVENT_ETT* pSrcEventETT, U16 u16MaxBufSize);
INTERFACE void MApp_EpgDB_SaveEventETT(U16 u16VchIdx, U32 u32dstaddr, MS_EPG_EVENT_ETT* pSrcEventETT);
#endif

#if( ENABLE_ATSC_EPG_DB_2016 )
MS_EPG_EVENT_New* MApp_EpgDB_Get_CurEvent_Ref(void);
 BOOLEAN MApp_EpgDB_GetCurEvent(MS_EPG_EVENT_New * pDstEvent);
#else
 BOOLEAN MApp_EpgDB_GetCurEvent(MS_EPG_EVENT *pDstEvent);
#endif

//INTERFACE U8 MApp_EpgDB_GetCurProgramEventIndex(void);

#if 1//( !ENABLE_ATSC_EPG_DB_2016 )
INTERFACE BOOLEAN MApp_EpgDB_GetResetStatus(void);
INTERFACE void MApp_EpgDB_SetResetStatus(BOOLEAN bReset);
#endif

#if( ENABLE_ATSC_EPG_DB_2016 )
void MApp_ATSC_EpgDb_DeleteEvents_CB(void);
#endif

#undef INTERFACE

#endif /* MAPP_EPGDB_A_H */
