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
#ifndef _MSAPI_OAD_PARSER_C_
#define _MSAPI_OAD_PARSER_C_

/*------------------------------------------------------------------------------
*   include files
*-----------------------------------------------------------------------------*/

#include <string.h>
#include "Board.h"
#include "debug.h"
#include "datatype.h"
#include "msAPI_oad_parser.h"
#include "msAPI_oad_process.h"

#if ENABLE_OAD

extern U8 g_OAD_OUI[3];
static  void    msAPI_OAD_RestartSectionFilter(U8  u08OadFID);

/******************************************************************************/
// The following functions is used by AP code.
/******************************************************************************/
U8 *msAPI_OAD_PollingSectionFilter(U8  u08OadFID,U8  *sectionBuffer)
{
    U32 u32ActualSize,u32RmnSize;
    U8 *pu8SecBuf = NULL;
    DMX_FILTER_STATUS procRet ;
    DMX_EVENT eEvent = DMX_EVENT_DATA_READY;

    if( u08OadFID == MSAPI_DMX_INVALID_FLT_ID ) return pu8SecBuf;

    procRet = MApi_DMX_Proc(u08OadFID,&eEvent) ;

    OAD_INFO(printf("eEvent = %bu\n",(U8)eEvent)) ;

    OAD_INFO(printf("procRet = %bu\n",(U8)procRet));

    if (procRet==DMX_FILTER_STATUS_OK)
    {
        if (eEvent == DMX_EVENT_DATA_READY)
        {
            OAD_DEBUG(memset(sectionBuffer, 0xBB, MSAPI_DMX_SECTION_4K));
            OAD_DEBUG(printf("section Addr: 0x%08LX\n", (sectionBuffer)));

            if( MApi_DMX_CopyData(u08OadFID, sectionBuffer, MSAPI_DMX_SECTION_4K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_OK )
            {
                if(msAPI_DMX_CheckCRC32(sectionBuffer)== FALSE)
                {
                    OAD_ASSERT(printf("crc error %s %d \n",__FUNCTION__,__LINE__));
                    msAPI_OAD_RestartSectionFilter(u08OadFID);
                    pu8SecBuf = NULL ;
                }
                else
                {
                    pu8SecBuf = sectionBuffer;
                }
            }
            else
            {
                OAD_ASSERT( printf("Error> msAPI_OAD_PollingSectionFilter : MApi_DMX_CopyData Error.\n") );
                msAPI_OAD_RestartSectionFilter(u08OadFID);
            }
        }
        else
        {
            OAD_ASSERT( printf("Polling OVERFLOW = %u\n", (U8)u08OadFID); );
            msAPI_OAD_RestartSectionFilter(u08OadFID);
        }
    }
    return pu8SecBuf;
}

BOOLEAN msAPI_OAD_CreateSectionFilter( U32 u32Type,U8 u08TableId,U16 u16MsgId, UINT16 u16Pid,U8  *u08OadFID, U8 u8VerNum)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;
    U32 u32GroupId = 0;
    U32 u32DownloadId = 0;

    memset(stSectionMonitor.au8MaskByte,     0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
    memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

    stSectionMonitor.u32SectionFltType   = u32Type;
    stSectionMonitor.au8MatchByte[0]    = u08TableId;              // table id
    stSectionMonitor.au8MaskByte[0]     = 0xFF;
    if (u08TableId!=OAD_UNT_SECTION_TYPE)
    {
        stSectionMonitor.au8MatchByte[8] = 0x11;//protocolDiscriminator
        stSectionMonitor.au8MaskByte[8] = 0xFF;
        stSectionMonitor.au8MatchByte[9] = 0x03;//dsmccType
        stSectionMonitor.au8MaskByte[9] = 0xFF;
        stSectionMonitor.au8MatchByte[10] = HIGHBYTE(u16MsgId);//HIGHBYTE(OAD_DSMCC_MSGID_DDB);//messageId[1]
        stSectionMonitor.au8MatchByte[11] = LOWBYTE(u16MsgId) ;//LOWBYTE(OAD_DSMCC_MSGID_DDB); //messageId[0]
        stSectionMonitor.au8MaskByte[10] = 0xFF;
        stSectionMonitor.au8MaskByte[11] = 0xFF;
        stSectionMonitor.pfNotify           = NULL;
        stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
        stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;

        if(u16MsgId == OAD_DSMCC_MSGID_DSI)
        {
            if(u8VerNum != 0xFF)
            {
                stSectionMonitor.au8MatchByte[5] = (u8VerNum << 1);
                stSectionMonitor.au8MaskByte[5] = 0x3E;
            }
        }
        else if(u16MsgId == OAD_DSMCC_MSGID_DII)
        {
            u32GroupId = msAPI_OAD_GetGroupId();

            stSectionMonitor.au8MatchByte[12] = u32GroupId >> 24;
            stSectionMonitor.au8MaskByte[12] = 0xFF;
            stSectionMonitor.au8MatchByte[13] = (u32GroupId >> 16) & 0xFF;
            stSectionMonitor.au8MaskByte[13] = 0xFF;
            stSectionMonitor.au8MatchByte[14] = (u32GroupId >> 8) & 0xFF;
            stSectionMonitor.au8MaskByte[14] = 0xFF;
            stSectionMonitor.au8MatchByte[15] = (u32GroupId & 0xFF);
            stSectionMonitor.au8MaskByte[15] = 0xFF;
        }
        else if(u16MsgId == OAD_DSMCC_MSGID_DDB)
        {
            u32DownloadId = msAPI_OAD_GetDownloadId();

            stSectionMonitor.au8MatchByte[12] = u32DownloadId >> 24;
            stSectionMonitor.au8MaskByte[12] = 0xFF;
            stSectionMonitor.au8MatchByte[13] = (u32DownloadId >> 16) & 0xFF;
            stSectionMonitor.au8MaskByte[13] = 0xFF;
            stSectionMonitor.au8MatchByte[14] = (u32DownloadId >> 8) & 0xFF;
            stSectionMonitor.au8MaskByte[14] = 0xFF;
            stSectionMonitor.au8MatchByte[15] = (u32DownloadId & 0xFF);
            stSectionMonitor.au8MaskByte[15] = 0xFF;

        }
    }
    else
    {
       stSectionMonitor.au8MatchByte[8] = (GET_3BYTE(g_OAD_OUI)&0xff0000)>>16 ;
       stSectionMonitor.au8MaskByte[8] = 0xFF;
       stSectionMonitor.au8MatchByte[9] = (GET_3BYTE(g_OAD_OUI)&0x00ff00)>>8 ;
       stSectionMonitor.au8MaskByte[9] = 0xFF;
       stSectionMonitor.au8MatchByte[10] = (GET_3BYTE(g_OAD_OUI)&0x0000ff) ;
       stSectionMonitor.au8MaskByte[10] = 0xFF;
       stSectionMonitor.pfNotify           = NULL;
       stSectionMonitor.u16TimeoutMilliSec = MSAPI_DMX_TIMEOUT_INFINITE;
       stSectionMonitor.SectMode           = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;
    }
    stSectionMonitor.u16PID             = u16Pid;
    stSectionMonitor.pu8FID             = u08OadFID;

    if(msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) == DMX_FILTER_STATUS_OK)
    {
        return TRUE ;
    }
    else
    {
        return FALSE ;
    }

}

void msAPI_OAD_DeleteSectionFilter(U8  *u08OadFID)
{
    if( *u08OadFID == MSAPI_DMX_INVALID_FLT_ID ) return;

    msAPI_DMX_Stop(*u08OadFID);
    msAPI_DMX_Close(*u08OadFID);

    *u08OadFID = MSAPI_DMX_INVALID_FLT_ID;
}

static void msAPI_OAD_RestartSectionFilter(U8  u08OadFID)
{
    if( u08OadFID == MSAPI_DMX_INVALID_FLT_ID ) return;

    msAPI_DMX_Stop(u08OadFID);
    msAPI_DMX_Reset(u08OadFID);
    msAPI_DMX_Start(u08OadFID);
}
#else
//static U8 code l_u8Dummy;
#endif //ENABLE_OAD

#undef _MSAPI_OAD_PARSER_C_
#endif //_MSAPI_OAD_PARSER_C_

