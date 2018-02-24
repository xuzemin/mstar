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
#define MAPP_BL_SI_C
////////////////////////////////////////////////////////////////////////////////
/// @file MApp_BL_SI.c
/// @author MStar Semiconductor Inc.
/// @brief compact si parser for bootloader OAD
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
#include "msAPI_DTVSystem.h"
#include "MApp_GlobalFunction.h"
#include "MApp_BL_SI.h"
#include "MApp_BL_Demux.h"
#include "MApp_OAD.h"
/******************************************************************************/
/*                                 Macro                                      */
/******************************************************************************/
#define BL_SI_PAT         0x01
#define BL_SI_PMT         0x02

#define BL_SI_DEBUG       0x00

#if (BL_SI_DEBUG)
#define BL_SI_DBG( flag, s )    { if (BL_SI_DEBUG & flag)    {s;} }
#else
#define BL_SI_DBG( flag, s )
#endif



/******************************************************************************/
/*                     Global Variables                                 */
/******************************************************************************/
BL_SI_PAT_INFO g_stPatInfo;

/******************************************************************************/
/*                     Static Local Variables                                 */
/******************************************************************************/
EN_SI_PARSE_STATE _enSIParseState = EN_SI_PARSE_INIT;

/*****************************************************************************/
/*        Functions to get database information from XX API                  */
/*****************************************************************************/
static U8 *MApp_BL_SI_FindLoopHead(U8 *pu8Section, EN_BL_PSIP_TABLE enTable, EN_BL_LOOP_TYPE enType)
{
    U16                  u16TotalDescriptorLength;
    U16                  u16SectionLength;
    U8    *iu8Ptr=NULL;

    /*[01]check error condition =============================================*/
    if( pu8Section == NULL )
    {
      return NULL;
    }

    /*[02]get section length ================================================*/
    u16SectionLength = ((pu8Section[1] & 0x0f) << 8) | pu8Section[2];
    u16SectionLength += 3;

    /*[03]find first item position ==========================================*/
    switch(enTable)
    {
        case EN_BL_PMT:
        {
            if(enType == EN_BL_FIRSTLOOP)
            {
                iu8Ptr = pu8Section + 12;
            }
            else if(enType == EN_BL_SECONDLOOP)
            {
                /* skip all descriptors in program info. loop */
                u16TotalDescriptorLength = ((pu8Section[10] & 0x0f) << 8) | pu8Section[11];
                iu8Ptr = pu8Section + 12 + u16TotalDescriptorLength;
            }
            break;
        }
        default:
        {
            iu8Ptr = NULL;
            break;
        }
    }

    /*[04]check error condition ==============================================*/
    if((U32) iu8Ptr >= ((U32)pu8Section + u16SectionLength - 4))
    {
       iu8Ptr = NULL;
    }

    return iu8Ptr;
}

static U8 *MApp_BL_SI_FindNextLoop(U8 *pu8Section, U8 *pu8LoopPosition, U16 u16TotalDescriptorLength, EN_BL_PSIP_TABLE enTable)
{
    U16                  u16SectionLength;

    /*[01]check error condition ===================================================*/
    if( pu8Section == NULL || pu8LoopPosition == NULL )
    {
        return NULL;
    }

    /*[02]get section length ================================================*/
    u16SectionLength = ((pu8Section[1] & 0x0f) << 8) | pu8Section[2];
    u16SectionLength += 3;

    /*[03]for each kind of table ============================================*/
    switch(enTable)
    {
       case EN_BL_PMT:
       {
          pu8LoopPosition += (5 + u16TotalDescriptorLength);

          /*[04]check error condition ==============================================*/
          if((U32) pu8LoopPosition >= ((U32)pu8Section + u16SectionLength - 4))
             pu8LoopPosition = NULL;
          break;
       }
       default:
       {
          pu8LoopPosition = NULL;
          break;
       }
    }

    // Check if end of section
    if((U32) pu8LoopPosition >= ((U32)pu8Section + u16SectionLength - 4))
    {
        pu8LoopPosition = NULL;
    }

    return pu8LoopPosition;
}
void MApp_BL_SI_PAT_Parse(U8 *pu8Section)
{
    U16 u16ProgramNumber, u16SectionLength;
    U8 u8NumOfItem;
    U8 *pu8SecIter;
    U8 i;

    u16SectionLength    = (pu8Section[1] & 0x0f) << 8;
    u16SectionLength   |= pu8Section[2];
    u8NumOfItem = (u16SectionLength - 9) / 4;

    pu8SecIter = pu8Section + 8;
    for (i = 0; i < u8NumOfItem; i++)
    {
        u16ProgramNumber = TSGetU16(pu8SecIter);
        if (u16ProgramNumber == 0)
        {
            pu8SecIter += 4;
            continue;
        }

        if(g_stPatInfo.u8NumOfPatItems < BL_SI_MAX_VC_PER_PHYSICAL)
        {
            g_stPatInfo.u16ProgNum[g_stPatInfo.u8NumOfPatItems] = u16ProgramNumber;
            g_stPatInfo.u16PmtPID[g_stPatInfo.u8NumOfPatItems] = TSGetBitsFromU16(&pu8SecIter[2], 0, 0x1fff);
            g_stPatInfo.u8NumOfPatItems++;
            pu8SecIter += 4;
            BL_SI_DBG(BL_SI_PAT, printf("PAT Parser>> ProgNum:%d; ProgPmtPID:%d\n",u16ProgramNumber, TSGetBitsFromU16(&pu8SecIter[2], 0, 0x1fff)));
        }
        else
        {
            break;
        }
    }
    BL_SI_DBG(BL_SI_PAT, printf("PAT Parser>> Numbers of program in sec[%d]: %d\n",pu8Section[6], g_stPatInfo.u8NumOfPatItems));
}

void MApp_BL_SI_PMT_Parse(U8 *pu8Section)
{
    U8 *pu8LoopPosition;
    U16 u16TotalDescriptorLength, u16DescriptorLength, u16TotalParseLength;
    U8 *pu8Descriptor;
    U16 u16DSMCC_PID = MSAPI_DMX_INVALID_PID;
    U8 u8Tag;
    U16 u16Service_ID;
    u16Service_ID = TSGetU16(&pu8Section[3]);
	
    pu8LoopPosition = MApp_BL_SI_FindLoopHead(pu8Section,EN_BL_PMT,EN_BL_SECONDLOOP);
    while(pu8LoopPosition != NULL)
    {
        u16TotalDescriptorLength = TSGetBitsFromU16(&pu8LoopPosition[3], 0, 0x0fff);
        // Go through the descriptors part.
        pu8Descriptor = pu8LoopPosition + 5;
        u16TotalParseLength = 0;

        switch(pu8LoopPosition[0]) //stream type
        {
            case ST_BL_DSMCC_DATA_TYPE_A:
            case ST_BL_DSMCC_DATA_TYPE_B:
            case ST_BL_DSMCC_DATA_TYPE_C:
            case ST_BL_DSMCC_DATA_TYPE_D:
            case ST_BL_DSMCC_DATA_TYPE_E:
            case ST_BL_OP_MPEG2_VID:
            {
                u16DSMCC_PID = TSGetBitsFromU16(&pu8LoopPosition[1],0,0x1fff);
                u16TotalParseLength = 0;
                while(u16TotalParseLength<u16TotalDescriptorLength)
                {
                    u8Tag= pu8Descriptor[0];   //descripter Tag
                    switch(u8Tag)
                    {
                        case TAG_BL_DBID:
                        {
                            BL_SI_DBG(BL_SI_PMT, printf("PMT Parser>> DBID got\n"));
                            #if ENABLE_OAD
                            #define DATA_BC_ID_SSU              0x000A // DVB-SSU
                            #define DATA_BC_ID_UK_EC        0x0111 // UK Engineering Channel
                            if(((pu8Descriptor[1] - 2) >0) && TSGetU16(&pu8Descriptor[2]) == DATA_BC_ID_SSU)
                            {
                                // Send OAD info & Update Status to OAD module.
                                WORD wONId;

                                wONId = msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));

                                if((IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                    ||((wONId == 0x2242 && OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)
                                        ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING==OSD_COUNTRY_DENMARK)
                                        ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING==OSD_COUNTRY_SWEDEN)
                                        ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING==OSD_COUNTRY_FINLAND)
                                        ||(wONId == 0x2174 && OSD_COUNTRY_SETTING==OSD_COUNTRY_IRELAND)))
                                {
                                    BL_SI_DBG(BL_SI_PMT, printf("PMT Parser>> OSD PMT Singal 1: [PID:%d][BdID:%d][SelectType:%d]\n", u16DSMCC_PID, DATA_BC_ID_SSU, TAG_DBID));
                                    MApp_OAD_SetPmtSignal(u16DSMCC_PID,DATA_BC_ID_SSU, &pu8Descriptor[4],TAG_DBID, u16Service_ID);
                                }
                            }
                            else if(((pu8Descriptor[1] - 2) >=0)  && TSGetU16(&pu8Descriptor[2]) == DATA_BC_ID_UK_EC)
                            {
                                // Send OAD info & Update Status to OAD module.
                                BL_SI_DBG(BL_SI_PMT, printf("PMT Parser>> OSD PMT Singal 2: [PID:%d][BdID:%d][SelectType:%d]\n", u16DSMCC_PID, DATA_BC_ID_UK_EC, TAG_DBID));
                                MApp_OAD_SetPmtSignal(u16DSMCC_PID,DATA_BC_ID_UK_EC, &pu8Descriptor[4],TAG_DBID, u16Service_ID);
                            }
                            #endif
                            break;
                        }
                        case TAG_BL_SID:
                        {
                            #if ENABLE_OAD
                            WORD wONId;

                            wONId = msAPI_CM_GetON_ID(msAPI_CM_GetCurrentServiceType(),msAPI_CM_GetCurrentPosition(msAPI_CM_GetCurrentServiceType()));
                            if((IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING)== FALSE)
                                ||((wONId == 0x2242 && OSD_COUNTRY_SETTING==OSD_COUNTRY_NORWAY)
                                    ||(wONId == 0x20D0 && OSD_COUNTRY_SETTING==OSD_COUNTRY_DENMARK)
                                    ||(wONId == 0x22F1 && OSD_COUNTRY_SETTING==OSD_COUNTRY_SWEDEN)
                                    ||(wONId == 0x20F6 && OSD_COUNTRY_SETTING==OSD_COUNTRY_FINLAND)
                                    ||(wONId == 0x2174 && OSD_COUNTRY_SETTING==OSD_COUNTRY_IRELAND)))
                            {
                                BL_SI_DBG(BL_SI_PMT, printf("PMT Parser>> OSD PMT Singal 3: [PID:%d][BdID:%d][SelectType:%d]\n", u16DSMCC_PID, DATA_BC_ID_SSU, TAG_SID));
                                MApp_OAD_SetPmtSignal(u16DSMCC_PID,DATA_BC_ID_SSU, &pu8Descriptor[2],TAG_SID, u16Service_ID);
                            }
                            #endif
                            break;
                        }
                        default: break;
                    }
                    /* move to next descriptor */
                    u16DescriptorLength = pu8Descriptor[1] + 2;
                    u16TotalParseLength += u16DescriptorLength;
                    pu8Descriptor += u16DescriptorLength;
                }
                break;
            }
            default:
            {
                break;
            }
        }
        pu8LoopPosition = MApp_BL_SI_FindNextLoop(pu8Section, pu8LoopPosition, u16TotalDescriptorLength, EN_BL_PMT);
    }
}

void MApp_BL_SI_Init(U32 u32BufferStart, U32 u32BufferSize)
{
    MApp_BL_Dmx_CloseAllFilters();
    MApp_BL_Dmx_Init(u32BufferStart, u32BufferSize);
}

void MApp_BL_SI_ParseStateInit(void)
{
    _enSIParseState = EN_SI_PARSE_INIT;
    MApp_BL_Dmx_SetOadScan(TRUE);
}

BL_SI_PAT_INFO* MApp_BL_SI_GetPatScanInfo(void)
{
    return &g_stPatInfo;
}

void MApp_BL_SI_DisableTableMonitor(void)
{
    _enSIParseState = EN_SI_PARSE_INIT;
    MApp_BL_Dmx_SetOadScan(FALSE);
    MApp_BL_Dmx_CloseAllFilters();
}

BOOLEAN MApp_BL_SI_Table_Monitor(void)
{
    BOOLEAN bReturn = FALSE;

    switch(_enSIParseState)
    {
        case EN_SI_PARSE_INIT:
            MApp_BL_Dmx_CloseAllFilters();
            memset(&g_stPatInfo, 0, sizeof(BL_SI_PAT_INFO));
            MApp_BL_Dmx_ResetPatSecTable();
            MApp_BL_Dmx_PAT_Monitor();
            _enSIParseState = EN_SI_PARSE_WAIT_PAT_READY;
            break;
        case EN_SI_PARSE_WAIT_PAT_READY:
            if (MApp_BL_Dmx_GetTableFilterID(EN_BL_PAT) != MSAPI_DMX_INVALID_FLT_ID)
            {
                msAPI_DMX_Proc(0xFF);
            }
            else
            {
                MApp_BL_Dmx_PMTs_Monitor();
                _enSIParseState = EN_SI_PARSE_WAIT_ALL_PMT_READY;
            }
            break;
        case EN_SI_PARSE_WAIT_ALL_PMT_READY:
            msAPI_DMX_Proc(0xFF);
            if ( MApp_BL_Dmx_GetOpenFilterChNums() <= 0 )
            {
                _enSIParseState = EN_SI_PARSE_INIT;
                bReturn= TRUE;
            }
            break;
        default:
            _enSIParseState = EN_SI_PARSE_INIT;
            bReturn = TRUE;
            break;
    }

    return bReturn;
}

#endif//#if(ENABLE_DTV)
#undef MAPP_BL_SI_C

