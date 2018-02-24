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
#define MAPP_BL_DEMUX_C
////////////////////////////////////////////////////////////////////////////////
/// @file MApp_BL_Demux.c
/// @author MStar Semiconductor Inc.
/// @brief small demux for Bootloader OAD
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                              Include files                                 */
/******************************************************************************/
#if (BLOADER && ENABLE_DTV)
// C Library
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "datatype.h"
#include "MApp_BL_SI.h"
#include "MApp_BL_Demux.h"
#include "Board.h"
#include "msAPI_demux.h"
#include "msAPI_Timer.h"

/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#define BL_DMX_PAT         0x01
#define BL_DMX_PMT         0x02

#define BL_DMX_DEBUG       0x00

#if (BL_DMX_DEBUG)
#define BL_DMX_DBG( flag, s )    { if (BL_DMX_DEBUG & flag)    {s;} }
#else
#define BL_DMX_DBG( flag, s )
#endif

#ifndef __ASSERT
#define __ASSERT(expr) (void)((expr) || printf("%s %d\n", __FILE__, __LINE__));
#endif


#define BL_MAPP_DMX_SECTION_1K                1024

#define BL_PAT_SEC_BUF_LEN         0x2000  //8k
#define BL_SEC_4K_BUF_LEN              0x1000  //4K

#define BL_SECTION_TIME_OUT_1000MS     1000    /* ms */

/******************************************************************************/
/*                     Global Variables                                 */
/******************************************************************************/
U32 gu32BL_PAT_SEC_BUF_START_ADR;
U8 *pBLSI4KSectionBuffer = NULL;
ST_BL_DMXSEC_MONITOR gstPatTable;


/******************************************************************************/
/*                     Static Local Variables                                 */
/******************************************************************************/
static U8 _u8BLPatFid=MSAPI_DMX_INVALID_FLT_ID;                       // PAT
static U8 _u8BLPmtFid=MSAPI_DMX_INVALID_FLT_ID;                       // PAT
static U8 _u8BLOADMonitorFID=MSAPI_DMX_INVALID_FLT_ID;
static U8 _u8BLOADDownloadFID=MSAPI_DMX_INVALID_FLT_ID;
static U32 _u32BLMonitorPatTimer;
static BOOLEAN _bBLEnableOADScan;
static U8 _u8BLMonitoringFID;
static U8        _u8BLOpenedFltCounter;                               // Filter
// Parsing result
static U8        _au8BLPsiFID2ItemIdx[MSAPI_DMX_MAX_FILTER_NUMBER];   // PMT (filter id <=> PAT item)
static U8        _au8BLCrcErrorCounter[MSAPI_DMX_MAX_FILTER_NUMBER];  // Filter

static void MApp_BL_Dmx_PAT_Cb(U8 u8FID, DMX_EVENT enEvent);
static void MApp_BL_Dmx_PMT_Cb(U8 u8FID, DMX_EVENT enEvent);

/*****************************************************************************/
/*        Functions to get database information from XX API                  */
/*****************************************************************************/
void MApp_BL_Dmx_Init(U32 u32BufferStart, U32 u32BufferSize)
{
    _u8BLPatFid = MSAPI_DMX_INVALID_FLT_ID;
    _u8BLPmtFid = MSAPI_DMX_INVALID_FLT_ID;
    gu32BL_PAT_SEC_BUF_START_ADR = u32BufferStart;
    pBLSI4KSectionBuffer=(U8*)gu32BL_PAT_SEC_BUF_START_ADR+BL_PAT_SEC_BUF_LEN;

    if ((BL_PAT_SEC_BUF_LEN+BL_SEC_4K_BUF_LEN)>u32BufferSize)
    {
        __ASSERT(0);
    }
}

void MApp_BL_Dmx_ResetPatSecTable(void)
{
    memset(&gstPatTable, 0, sizeof(ST_BL_DMXSEC_MONITOR));
    memset(&_au8BLPsiFID2ItemIdx, 0 , sizeof(U8)*MSAPI_DMX_MAX_FILTER_NUMBER);
    memset(&_au8BLCrcErrorCounter, 0 , sizeof(U8)*MSAPI_DMX_MAX_FILTER_NUMBER);
}

void MApp_BL_Dmx_CloseAllFilters(void)
{
    U8 filter = 0;
    for(filter = 0; filter < MSAPI_DMX_MAX_FILTER_NUMBER; filter++)
    {
        msAPI_DMX_CloseFilter(filter);
    }
    _u8BLPatFid = MSAPI_DMX_INVALID_FLT_ID;
    _u8BLPmtFid = MSAPI_DMX_INVALID_FLT_ID;
}

void MApp_BL_Dmx_SetOadScan(BOOLEAN bEnable)
{
    _bBLEnableOADScan = bEnable;
}

U8 MApp_BL_Dmx_GetTableFilterID(EN_BL_PSIP_TABLE enTable)
{
    switch(enTable)
    {
        case EN_BL_PAT: return _u8BLPatFid;
        case EN_BL_PMT: return _u8BLPmtFid;
        default: return MSAPI_DMX_INVALID_FLT_ID;
    }
}

U8 MApp_BL_Dmx_GetOpenFilterChNums(void)
{
    return _u8BLOpenedFltCounter;
}

U8 *MApp_BL_Dmx_GetSI4KSectionBuffer(void)
{
    return pBLSI4KSectionBuffer;
}
//****************************************************************************
/// Get  filter ID
/// @param eFid \b IN: filter
/// -@see EN_FID
/// @return U8*: point of filter id
/******************************************************************************/
U8 *MApp_BL_Dmx_GetFid(EN_BL_FID eFid)
{
    switch(eFid)
    {
        case EN_BL_OAD_MONITOR_FID:
            return &_u8BLOADMonitorFID;
        case EN_BL_OAD_DOWNLOAD_FID:
            return &_u8BLOADDownloadFID;
        default:
             break;
    }
    return NULL;
}
//****************************************************************************
/// Set  filter ID
/// @param u8Fid \b IN: filter id
/// @param eFid \b IN: filter
/// -@see EN_FID
/// @return none
/******************************************************************************/
void MApp_BL_Dmx_SetFid(U8 u8Fid, EN_BL_FID eFid)
{
    switch(eFid)
    {
        case EN_BL_OAD_MONITOR_FID:
            _u8BLOADMonitorFID = u8Fid;
            break;
        case EN_BL_OAD_DOWNLOAD_FID:
            _u8BLOADDownloadFID = u8Fid;
            break;
        default:
             break;
    }

}
static void MApp_BL_Dmx_PAT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    U16 u16SectionLength;
    U8 u8Loop;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;

    BL_DMX_DBG(BL_DMX_PAT,printf("\n pat cb>> u8FID %bu enStatus %bu\n", u8FID, (U8)enStatus));

    switch (enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            // get section data
            if (MApi_DMX_CopyData(u8FID, pBLSI4KSectionBuffer, BL_MAPP_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
            {
                BL_DMX_DBG(BL_DMX_PAT, printf("[FID=%bu] PAT copy section fail!! \n", u8FID));
                msAPI_DMX_RestartFilter(u8FID);
                _au8BLCrcErrorCounter[u8FID]++;
                break;
            }
            if (_bBLEnableOADScan)
            {
                if(GETBIT(gstPatTable.u32SecMask, pBLSI4KSectionBuffer[6]) == 0)
                {
                    u16SectionLength = TSGetBitsFromU16(&pBLSI4KSectionBuffer[1], 0, 0x0fff) + 3;
                    memcpy((U8*)(gu32BL_PAT_SEC_BUF_START_ADR+gstPatTable.u16SecLengthCount), pBLSI4KSectionBuffer, u16SectionLength);
                    gstPatTable.u16SecLengthCount += u16SectionLength;

                    SETBIT(gstPatTable.u32SecMask, pBLSI4KSectionBuffer[6]);
                    gstPatTable.u8SecCount++;
                    gstPatTable.u8LastSecNum = pBLSI4KSectionBuffer[7];
                }
            }
            break;
        }
        default:
        {
            BL_DMX_DBG(BL_DMX_PAT, printf("[FID=%bu] PAT get section unknow error!! \n", u8FID));
            _au8BLCrcErrorCounter[u8FID] = BL_MAX_NUM_OF_CRC_ERROR;
            break;
        }
    }

    if (_bBLEnableOADScan)
    {
        if(gstPatTable.fIsTblReceived==FALSE && gstPatTable.u8SecCount>gstPatTable.u8LastSecNum)
        {
            gstPatTable.fIsTblReceived = TRUE;
        }

        if((gstPatTable.fIsTblReceived == TRUE)
           || _au8BLCrcErrorCounter[u8FID]>=BL_MAX_NUM_OF_CRC_ERROR
           /* This timer is to avoid dead loop in scan when we fail to receive all multisection. */
           || (msAPI_Timer_DiffTimeFromNow(_u32BLMonitorPatTimer) > BL_PAT_MONITOR_PERIOD * 3)
          )
        {
            msAPI_DMX_CloseFilter(u8FID);
            _u8BLPatFid = MSAPI_DMX_INVALID_FLT_ID;
            _u8BLOpenedFltCounter--;
            _au8BLCrcErrorCounter[u8FID] = 0;

            gstPatTable.u16SecLengthCount = 0;
            for(u8Loop=0; u8Loop<gstPatTable.u8SecCount; u8Loop++)
            {
                msAPI_Timer_ResetWDT();

                memcpy( pBLSI4KSectionBuffer, (void*)(gu32BL_PAT_SEC_BUF_START_ADR+gstPatTable.u16SecLengthCount),BL_MAPP_DMX_SECTION_1K);
                MApp_BL_SI_PAT_Parse(pBLSI4KSectionBuffer);
                gstPatTable.u16SecLengthCount += TSGetBitsFromU16(&pBLSI4KSectionBuffer[1], 0, 0x0fff) + 3;
            }
        }
    }
}
static void MApp_BL_Dmx_PMT_Cb(U8 u8FID, DMX_EVENT enEvent)
{
    U32 u32ActualSize,u32RmnSize;
    MSAPI_DMX_FILTER_STATUS enStatus;
    enStatus=(MSAPI_DMX_FILTER_STATUS)enEvent;
    BL_DMX_DBG(BL_DMX_PMT,printf("\n pmt cb>> u8FID %bu enStatus %bu\n", u8FID, (U8)enStatus));

    switch(enStatus)
    {
        case MSAPI_DMX_FILTER_STATUS_SECAVAILABLE:
        {
            /* get section data */
            if(MApi_DMX_CopyData(u8FID, pBLSI4KSectionBuffer, BL_MAPP_DMX_SECTION_1K,&u32ActualSize,&u32RmnSize,NULL) == DMX_FILTER_STATUS_ERROR)
            {
                msAPI_DMX_RestartFilter(u8FID);
                BL_DMX_DBG(BL_DMX_PMT, printf("[FID=%bu] PMT %bu Prog# 0x%x get section fail\n", u8FID, _au8BLPsiFID2ItemIdx[u8FID], ((BL_SI_PAT_INFO *)MApp_BL_SI_GetPatScanInfo())->u16ProgNum[_au8BLPsiFID2ItemIdx[u8FID]]));
                break;
            }
            if (_bBLEnableOADScan)
            {
                MApp_BL_SI_PMT_Parse(pBLSI4KSectionBuffer);
            }
            break;
        }
        default:
        {
           BL_DMX_DBG(BL_DMX_PMT, printf("[FID=%bu] PMT %bu Prog# 0x%x unknow error\n", u8FID, _au8BLPsiFID2ItemIdx[u8FID], ((BL_SI_PAT_INFO *)MApp_BL_SI_GetPatScanInfo())->u16ProgNum[_au8BLPsiFID2ItemIdx[u8FID]]));
           break;
        }
    }

    msAPI_DMX_CloseFilter(u8FID);
    _u8BLOpenedFltCounter--;
    _au8BLPsiFID2ItemIdx[u8FID] = MSAPI_DMX_INVALID_FLT_ID;
}
void MApp_BL_Dmx_PAT_Monitor(void)
{
    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;
    //MAPI_DMX_FILTER_STATUS enStatus;
    if (_bBLEnableOADScan == TRUE)
    {
        if (_u8BLPatFid == MSAPI_DMX_INVALID_FLT_ID)
        {
            BL_DMX_DBG(BL_DMX_PAT, printf("Trigger PAT monitor time: %ld(ms) enpat(%bd)\n", msAPI_Timer_GetTime0(), (U8)_bBLEnableOADScan));
            memset(stSectionMonitor.au8MaskByte,     0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);
            stSectionMonitor.u16PID             = BL_PID_PAT;
            stSectionMonitor.u32SectionFltType   = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            stSectionMonitor.au8MatchByte[0]    = BL_TID_PAS;              // table id
            stSectionMonitor.au8MaskByte[0]     = 0xFF;
            stSectionMonitor.pfNotify           = MApp_BL_Dmx_PAT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = BL_PAT_MONITOR_PERIOD;
            stSectionMonitor.pu8FID             = &_u8BLPatFid;
            stSectionMonitor.SectMode = DMX_SECT_MODE_CONTI|DMX_SECT_MODE_CRCCHK;
            while (msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) != DMX_FILTER_STATUS_OK)
            {
                msAPI_DMX_Proc(0xFF);
            }
            BL_DMX_DBG(BL_DMX_PAT, printf("Monitoring PAT at Filter# %bu\n", _u8BLPatFid));
            _u8BLOpenedFltCounter++;
            _u32BLMonitorPatTimer=msAPI_Timer_GetTime0();
        }
    }
}

void MApp_BL_Dmx_PMTs_Monitor(void)
{
    U8 u8Loop;
    BL_SI_PAT_INFO *pstPatInfo = NULL;

    MS_DMX_SECTIONMONITOR_PARA   stSectionMonitor;
    pstPatInfo = MApp_BL_SI_GetPatScanInfo();
    if (NULL == pstPatInfo)
    {
        BL_DMX_DBG(BL_DMX_PMT, printf("PMTs monitor>>PAT Info is NULL\n"));
        return;
    }
    if (_bBLEnableOADScan == TRUE)
    {
        if (pstPatInfo->u8NumOfPatItems > 0)
        {
            memset(stSectionMonitor.au8MaskByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

            memset(stSectionMonitor.au8NotMatchByte, 0x00, MSAPI_DMX_MATCH_PATTERN_LENGTH);

            stSectionMonitor.u32SectionFltType = MSAPI_DMX_FILTER_TYPE_SECTION_1K;
            stSectionMonitor.pfNotify = MApp_BL_Dmx_PMT_Cb;
            stSectionMonitor.u16TimeoutMilliSec = BL_SECTION_TIME_OUT_1000MS;
            stSectionMonitor.pu8FID = &_u8BLMonitoringFID;
            stSectionMonitor.SectMode = DMX_SECT_MODE_ONESHOT|DMX_SECT_MODE_CRCCHK;
            stSectionMonitor.au8MatchByte[0] = BL_TID_PMS; //table id
            stSectionMonitor.au8MaskByte[0] = 0xFF;
            stSectionMonitor.au8MaskByte[3] = 0xFF;
            stSectionMonitor.au8MaskByte[4] = 0xFF;

            BL_DMX_DBG(BL_DMX_PMT, printf("\nPMT u8NumOfPatItem= %bu \n",pstPatInfo->u8NumOfPatItems));
            for (u8Loop = 0; u8Loop < pstPatInfo->u8NumOfPatItems; u8Loop++)
            {
                msAPI_Timer_ResetWDT();

                /* skip Network PID (service id = 0) */
                if (pstPatInfo->u16ProgNum[u8Loop] == 0 || pstPatInfo->u16PmtPID[u8Loop] == 0)
                {
                    continue;
                }
                stSectionMonitor.u16PID = pstPatInfo->u16PmtPID[u8Loop];
                stSectionMonitor.au8MatchByte[3] = HIGHBYTE(pstPatInfo->u16ProgNum[u8Loop]); //subtable id
                stSectionMonitor.au8MatchByte[4] = LOWBYTE(pstPatInfo->u16ProgNum[u8Loop]);
                while (msAPI_DMX_SectionMonitor(&stSectionMonitor, FALSE) != DMX_FILTER_STATUS_OK)
                {
                    msAPI_DMX_Proc(0xFF);
                }

                BL_DMX_DBG(BL_DMX_PMT, printf("Monitoring PMT PID 0x%x, SID 0x%x at Filter# %bu \n", pstPatInfo->u16PmtPID[u8Loop], pstPatInfo->u16ProgNum[u8Loop], _u8BLMonitoringFID));
                _au8BLPsiFID2ItemIdx[_u8BLMonitoringFID] = u8Loop;
                _au8BLCrcErrorCounter[_u8BLMonitoringFID] = 0;
                _u8BLOpenedFltCounter++;
            }
        }
    }
}
#endif
#undef MAPP_BL_DEMUX_C

