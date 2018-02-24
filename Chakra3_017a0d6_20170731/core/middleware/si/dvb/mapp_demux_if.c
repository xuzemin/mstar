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

#define MAPP_DEMUX_IF_C
/******************************************************************************/
/*                       Header Files                                         */
/******************************************************************************/
#include "Board.h"
#if(ENABLE_DTV)

// C Library
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Global Layer
#include "datatype.h"

// MW Layer
#include "msAPI_demux.h"
#include "mapp_demux_if.h"


/******************************************************************************/
/*                                 Functions                                  */
/******************************************************************************/
static SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Filter_Status(DMX_FILTER_STATUS eStatus);



SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Stop(U8 u8FltID)
{
	DMX_FILTER_STATUS eStatus;

	eStatus = msAPI_DMX_Stop(u8FltID);
	return msAPI_SI_Dmx_Filter_Status(eStatus);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Close(U8 u8FltID)
{
    DMX_FILTER_STATUS eStatus;

    eStatus = msAPI_DMX_Close(u8FltID);
    return msAPI_SI_Dmx_Filter_Status(eStatus);
}

void msAPI_SI_Dmx_CloseFilter(U8 u8FID)
{
	msAPI_DMX_CloseFilter(u8FID);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_CopyData(U8 u8DmxId, U8* pu8Buf, U32 u32BufSize, U32* pu32ActualSize, U32* pu32RmnSize)
{
	DMX_FILTER_STATUS eStatus;

	eStatus = msAPI_DMX_CopyData(u8DmxId, pu8Buf, u32BufSize, pu32ActualSize, pu32RmnSize, NULL);
	return msAPI_SI_Dmx_Filter_Status(eStatus);
}

void msAPI_SI_Dmx_RestartFilter(U8 u8FID)
{
	msAPI_DMX_RestartFilter(u8FID);
}

BOOL msAPI_SI_Dmx_CheckCRC32(U8* pu8Section)
{
	return msAPI_DMX_CheckCRC32(pu8Section);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_SectionMonitor(SI_DMX_SECTIONMONITOR_PARA *pstSectionMonitor, BOOL bFileIn)
{
	DMX_FILTER_STATUS eStatus;
	MS_DMX_SECTIONMONITOR_PARA stSectionMonitor;

	stSectionMonitor.u16PID = pstSectionMonitor->u16PID;
	stSectionMonitor.u32SectionFltType = pstSectionMonitor->u32SectionFltType;
	memcpy(stSectionMonitor.au8MatchByte, pstSectionMonitor->au8MatchByte, (SI_DMX_MATCH_PATTERN_LENGTH > MSAPI_DMX_MATCH_PATTERN_LENGTH) ? MSAPI_DMX_MATCH_PATTERN_LENGTH : SI_DMX_MATCH_PATTERN_LENGTH);
	memcpy(stSectionMonitor.au8MaskByte, pstSectionMonitor->au8MaskByte, (SI_DMX_MATCH_PATTERN_LENGTH > MSAPI_DMX_MATCH_PATTERN_LENGTH) ? MSAPI_DMX_MATCH_PATTERN_LENGTH : SI_DMX_MATCH_PATTERN_LENGTH);
	memcpy(stSectionMonitor.au8NotMatchByte, pstSectionMonitor->au8NotMatchByte, (SI_DMX_MATCH_PATTERN_LENGTH > MSAPI_DMX_MATCH_PATTERN_LENGTH) ? MSAPI_DMX_MATCH_PATTERN_LENGTH : SI_DMX_MATCH_PATTERN_LENGTH);
	stSectionMonitor.pfNotify = pstSectionMonitor->pfNotify;
	stSectionMonitor.u16TimeoutMilliSec = pstSectionMonitor->u16TimeoutMilliSec;
	stSectionMonitor.SectMode = pstSectionMonitor->SectMode;
	stSectionMonitor.pu8FID = pstSectionMonitor->pu8FID;

	eStatus = msAPI_DMX_SectionMonitor(&stSectionMonitor, bFileIn);

	return msAPI_SI_Dmx_Filter_Status(eStatus);

}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_SectionGet(SI_DMX_SECTIONGET_PARA * pstSectionGet)
{
	DMX_FILTER_STATUS eStatus;
	MS_DMX_SECTIONGET_PARA stSectionGet;

	stSectionGet.u16PID = pstSectionGet->u16PID;
	stSectionGet.u32SectionFltType = pstSectionGet->u32SectionFltType;
	memcpy(stSectionGet.au8MatchByte, pstSectionGet->au8MatchByte, (SI_DMX_MATCH_PATTERN_LENGTH > MSAPI_DMX_MATCH_PATTERN_LENGTH) ? MSAPI_DMX_MATCH_PATTERN_LENGTH : SI_DMX_MATCH_PATTERN_LENGTH);
	memcpy(stSectionGet.au8MaskByte, pstSectionGet->au8MaskByte, (SI_DMX_MATCH_PATTERN_LENGTH > MSAPI_DMX_MATCH_PATTERN_LENGTH) ? MSAPI_DMX_MATCH_PATTERN_LENGTH : SI_DMX_MATCH_PATTERN_LENGTH);
	memcpy(stSectionGet.au8NotMatchByte, pstSectionGet->au8NotMatchByte, (SI_DMX_MATCH_PATTERN_LENGTH > MSAPI_DMX_MATCH_PATTERN_LENGTH) ? MSAPI_DMX_MATCH_PATTERN_LENGTH : SI_DMX_MATCH_PATTERN_LENGTH);
	stSectionGet.pu8Section = pstSectionGet->pu8Section;
	stSectionGet.u16MaxSecSize = pstSectionGet->u16MaxSecSize;
	stSectionGet.u16TimeoutMilliSec = pstSectionGet->u16TimeoutMilliSec;
	stSectionGet.bCheckCrc = pstSectionGet->bCheckCrc;

	eStatus = msAPI_DMX_SectionGet(&stSectionGet);

	return msAPI_SI_Dmx_Filter_Status(eStatus);

}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Proc(U8 u8DmxId)
{
	DMX_FILTER_STATUS eStatus;

	eStatus = msAPI_DMX_Proc(u8DmxId);
	return msAPI_SI_Dmx_Filter_Status(eStatus);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Start(U8 u8FltID)
{
	DMX_FILTER_STATUS eStatus;

	eStatus = msAPI_DMX_Start(u8FltID);
	return msAPI_SI_Dmx_Filter_Status(eStatus);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Reset(U8 u8FltID)
{
	DMX_FILTER_STATUS eStatus;

	eStatus = msAPI_DMX_Reset(u8FltID);
	return msAPI_SI_Dmx_Filter_Status(eStatus);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Pid(U8 u8FltID, U16* pu16Pid, BOOL bSet)
{
    DMX_FILTER_STATUS eStatus;

    eStatus = msAPI_DMX_Pid(u8FltID, pu16Pid, bSet);
    return msAPI_SI_Dmx_Filter_Status(eStatus);
}

SI_DMX_FILTER_STATUS msAPI_SI_Dmx_Filter_Status(DMX_FILTER_STATUS eStatus)
{
	switch(eStatus)
	{
		case DMX_FILTER_STATUS_OK:
		    return SI_DMX_FILTER_STATUS_OK;

		case DMX_FILTER_STATUS_ERROR:
			return SI_DMX_FILTER_STATUS_ERROR;

		default:
			return SI_DMX_FILTER_STATUS_ERROR;
	}
}

SI_DMX_FILTER_CB_STATUS msAPI_SI_Dmx_Filter_Cb_Status(U32 u8Event)
{
	MSAPI_DMX_FILTER_STATUS eStatus = (MSAPI_DMX_FILTER_STATUS)u8Event;

	switch(eStatus)
	{
		case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
			return SI_DMX_FILTER_CB_STATUS_SECAVAILABLE;

		//case MSAPI_DMX_FILTER_STATUS_PESAVAILABLE:
				//return SI_DMX_FILTER_CB_STATUS_PESAVAILABLE;

		case MSAPI_DMX_FILTER_STATUS_OVERFLOW:
			return SI_DMX_FILTER_CB_STATUS_OVERFLOW;

		case MSAPI_DMX_FILTER_STATUS_OK:
			return SI_DMX_FILTER_CB_STATUS_OK;

		case MSAPI_DMX_FILTER_STATUS_TIMEOUT:
			return SI_DMX_FILTER_CB_STATUS_TIMEOUT;

		case MSAPI_DMX_FILTER_STATUS_CRCINCORRECT:
			return SI_DMX_FILTER_CB_STATUS_CRCINCORRECT;

		case MSAPI_DMX_FILTER_STATUS_REQUESTMEET:
			return SI_DMX_FILTER_CB_STATUS_REQUESTMEET;

		case MSAPI_DMX_FILTER_STATUS_COPYSECERR:
			return SI_DMX_FILTER_CB_STATUS_COPYSECERR;

		default:
			return SI_DMX_FILTER_CB_STATUS_ERROR;
	}

}

U32 msAPI_SI_Dmx_Get_FilterType(U32 u32FilterType)
{
	switch(u32FilterType)
	{
		case SI_DMX_FILTER_TYPE_VIDEO:
			return MSAPI_DMX_FILTER_TYPE_VIDEO;

		case SI_DMX_FILTER_TYPE_AUDIO:
			return MSAPI_DMX_FILTER_TYPE_AUDIO;

		case SI_DMX_FILTER_TYPE_AUDIO2:
			return MSAPI_DMX_FILTER_TYPE_AUDIO2;

		case SI_DMX_FILTER_TYPE_SUBTITLE:
			return MSAPI_DMX_FILTER_TYPE_SUBTITLE;

		case SI_DMX_FILTER_TYPE_TELETEXT:
			return MSAPI_DMX_FILTER_TYPE_TELETEXT;

		case SI_DMX_FILTER_TYPE_PES:
			return MSAPI_DMX_FILTER_TYPE_PES;

		case SI_DMX_FILTER_TYPE_SECTION_1K:
			return MSAPI_DMX_FILTER_TYPE_SECTION_1K;

		case SI_DMX_FILTER_TYPE_SECTION_4K:
			return MSAPI_DMX_FILTER_TYPE_SECTION_4K;

		case SI_DMX_FILTER_TYPE_SECTION_VERSION:
			return MSAPI_DMX_FILTER_TYPE_SECTION_VERSION;

		case SI_DMX_FILTER_TYPE_SECTION_CRC:
			return MSAPI_DMX_FILTER_TYPE_SECTION_CRC;

		case SI_DMX_FILTER_TYPE_PCR:
			return MSAPI_DMX_FILTER_TYPE_PCR;

		case SI_DMX_FILTER_TYPE_PACKET:
			return MSAPI_DMX_FILTER_TYPE_PACKET;

		case SI_DMX_FILTER_TYPE_PACKET_PUSI:
			return MSAPI_DMX_FILTER_TYPE_PACKET_PUSI;

		case SI_DMX_FILTER_TYPE_PACKET_AF:
			return MSAPI_DMX_FILTER_TYPE_PACKET_AF;

		case SI_DMX_FILTER_TYPE_OAD_MONITOR:
			return MSAPI_DMX_FILTER_TYPE_OAD_MONITOR;

		case SI_DMX_FILTER_TYPE_OAD_DOWNLOAD:
			return MSAPI_DMX_FILTER_TYPE_OAD_DOWNLOAD;

		case SI_DMX_FILTER_TYPE_RECORD:
			return MSAPI_DMX_FILTER_TYPE_RECORD;

		case SI_DMX_FILTER_TYPE_SECTION_EIT:
			return MSAPI_DMX_FILTER_TYPE_SECTION_EIT;

		case SI_DMX_FILTER_TYPE_CSA_PACKET:
			return MSAPI_DMX_FILTER_TYPE_CSA_PACKET;

		case SI_DMX_FILTER_SOURCE_TYPE_MASK:
			return MSAPI_DMX_FILTER_SOURCE_TYPE_MASK;

		case SI_DMX_FILTER_SOURCE_TYPE_LIVE:
			return MSAPI_DMX_FILTER_SOURCE_TYPE_LIVE;

		case SI_DMX_FILTER_SOURCE_TYPE_FILE:
			return MSAPI_DMX_FILTER_SOURCE_TYPE_FILE;

		default:
			return SI_DMX_FILTER_SOURCE_TYPE_ERROR;
	}

}

U32 msAPI_SI_Dmx_Get_SecMode(U32 u32SecMode)
{
	switch(u32SecMode)
	{
		case SI_DMX_SECT_MODE_CONTI:
			return DMX_SECT_MODE_CONTI;

		case SI_DMX_SECT_MODE_ONESHOT:
			return DMX_SECT_MODE_CONTI;

		case SI_DMX_SECT_MODE_CRCCHK:
			return DMX_SECT_MODE_CRCCHK;

		case SI_DMX_SECT_MODE_AUTO_ADDR:
			return DMX_SECT_MODE_AUTO_ADDR;

		default:
			return DMX_SECT_MODE_ONESHOT;
	}
}


#endif//#if(ENABLE_DTV)
#undef MAPP_DEMUX_IF_C

