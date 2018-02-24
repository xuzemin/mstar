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

#include "Board.h"
#include <string.h>

#if ( CHAKRA3_AUTO_TEST && ENABLE_DTV_EPG)

#include "MApp_AutoTest.h"
#include "mapp_epgdb_public.h"
#include "msAPI_Timer.h"
#include "MApp_EpgTimer.h"

//=======================================================================
EN_AT_RESULT _MApp_AT_EPGCmdHandler(AT_CMD ATCmd)
{
    char tmp[MAX_EVENT_NAME+2]={0};
    WORD ChannelCnt;
    MEMBER_SERVICETYPE mServiceType;
    MEMBER_SI_SERVICETYPE mSIType;
    WORD u16CurPosIdx;
    WORD wLCN;
    BYTE name[MAX_SERVICE_NAME];
    EventIndex pEvent;
    EventIndex pNextEvent;
    U16 u16EventName[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U8 u8EventName[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U32 u32SrcLength;
    U16 u16DetailDescription[MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN];
    U8 u8DetailDescription[MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN];
    U16 u16DetailSrcLength;
    EventTime pEventTime;
    U32 u32StartTime;
    U32 u32EndTime;
    ST_TIME stStartTime;
    ST_TIME stEndTime;
    WORD i;
    U32 u32EventCount = 0;
    BOOL isLastEvent = FALSE;

    memset(tmp, 0, MAX_EVENT_NAME+2);
    
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_EPG_CMD_GET_TIME_MODE: // 1
        {
            printf("EN_AUTO_TEST_EPG_CMD_GET_TIME_MODE \n");
            
            for (mServiceType=E_SERVICETYPE_DTV; mServiceType<=E_SERVICETYPE_DATA; mServiceType++)
            {
                ChannelCnt = msAPI_DTV_GetProgramCount(mServiceType, EXCLUDE_NOT_VISIBLE_AND_DELETED);
                for(i=0; i < ChannelCnt; i++)
                {
                    wLCN = msAPI_CM_GetLogicalChannelNumber(mServiceType,i);
                    if(!msAPI_CM_GetServiceName(mServiceType, i, name))
                    {
                        printf("Get Service Name Error,Postion:%d\n",i);
                        continue;
                    }
                    mSIType = MApp_AT_ConvertSeviceToSI(mServiceType);
                    
                    MApp_Epg_GetPresentEventIdx(mSIType, i, &pEvent);
                    
                    memset(u16EventName, 0, sizeof(u16EventName));
                    memset(u8EventName, 0, sizeof(u8EventName));
                    memset(u16DetailDescription, 0, sizeof(u16DetailDescription));
                    memset(u8DetailDescription, 0, sizeof(u8DetailDescription));
                    
                    MApp_Epg_GetEventName(pEvent, u16EventName, EPG_TIMER_MAX_EVT_NAME_LEN);
                    MApp_Epg_GetDetailDescription(pEvent, u16DetailDescription, &u16DetailSrcLength, MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN);
                    
                    u32SrcLength = msAPI_U16BufToU8Buf(u16EventName, u8EventName, EPG_TIMER_MAX_EVT_NAME_LEN);
                    u32SrcLength = msAPI_U16BufToU8Buf(u16DetailDescription, u8DetailDescription, MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN);
                    
                    switch(ATCmd.iCmdPara[0])
                    {
                        case E_EPG_TOTAL_INFO:
                            // channel index, channel name, program name
                            snprintf(tmp, sizeof(tmp), "%d, %s, %s\n", wLCN, name, u8EventName);
                            MApp_AT_Msg_Add((U8*)tmp);
                            // extended descriptor of the presen event
                            snprintf(tmp, sizeof(tmp), "%s\n",u8DetailDescription);
                            MApp_AT_Msg_Add((U8*)tmp);
                            break;
                        case E_EPG_LCN:
                            // channel index
                            snprintf(tmp, sizeof(tmp), "%d,\n", wLCN);
                            MApp_AT_Msg_Add((U8*)tmp);
                            break;
                        case E_EPG_CHANNEL_NAME:
                            // channel name
                            snprintf(tmp, sizeof(tmp), "%s,\n", name);
                            MApp_AT_Msg_Add((U8*)tmp);
                            break;
                        default:
                            printf("Wrong iCmdPara!!!\n");
                            return EN_AT_RESULT_ER;
                            break;
                    }
                }
            }
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_EPG_CMD_GET_CHANNEL_MODE: // 2
        {
            printf("EN_AUTO_TEST_EPG_CMD_GET_CHANNEL_MODE \n");

            mServiceType = msAPI_CM_GetCurrentServiceType();
            u16CurPosIdx = msAPI_CM_GetCurrentPosition(mServiceType);
            mSIType = MApp_AT_ConvertSeviceToSI(mServiceType);
            if(MW_EN_EPG_FUNC_STATUS_SUCCESS != MApp_Epg_GetPresentEventIdx(mSIType, u16CurPosIdx, &pEvent))
            {
                printf("Get present event index error\n");
                return EN_AT_RESULT_ER;
            }
            
            while(FALSE == isLastEvent)
            {   
                u32EventCount++;
                if(MW_EN_EPG_FUNC_STATUS_SUCCESS != MApp_Epg_EventFindNext(mSIType, u16CurPosIdx, pEvent, &pNextEvent))
                {
                    printf("last event:%d\n",u32EventCount);
                    isLastEvent = TRUE;
                }
                MApp_Epg_GetEventTime(pEvent, &pEventTime);

              #if ENABLE_NZ_EIT_TIME_DISPLAY
                if (IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
                {
                    BOOLEAN bDayLightTimeStart,bDayLightTimeEnd,bGotTOT;
                    u32StartTime = pEventTime.u32StartTime - msAPI_Timer_GetOffsetTime();
                    u32EndTime = u32StartTime + pEventTime.u32Duration;
                    u32StartTime +=  MApp_SI_Get_OffsetTime(u32StartTime, &bDayLightTimeStart, &bGotTOT, TRUE);
                    u32EndTime = u32EndTime + MApp_SI_Get_OffsetTime(u32EndTime, &bDayLightTimeEnd, &bGotTOT, FALSE);
                }
                else
              #endif
                {
                    u32StartTime = pEventTime.u32StartTime;
                    u32EndTime = pEventTime.u32StartTime + pEventTime.u32Duration;
                }

                MApp_ConvertSeconds2StTime( u32StartTime, &stStartTime);
                MApp_ConvertSeconds2StTime( u32EndTime, &stEndTime);
                
                memset(u16EventName, 0, sizeof(u16EventName));
                memset(u8EventName, 0, sizeof(u8EventName));
                memset(u16DetailDescription, 0, sizeof(u16DetailDescription));
                memset(u8DetailDescription, 0, sizeof(u8DetailDescription));
                
                MApp_Epg_GetEventName(pEvent, u16EventName, EPG_TIMER_MAX_EVT_NAME_LEN);
                MApp_Epg_GetDetailDescription(pEvent, u16DetailDescription, &u16DetailSrcLength, MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN);
                
                u32SrcLength = msAPI_U16BufToU8Buf(u16EventName, u8EventName, EPG_TIMER_MAX_EVT_NAME_LEN);
                u32SrcLength = msAPI_U16BufToU8Buf(u16DetailDescription, u8DetailDescription, MW_MAX_EXTEND_EVENT_DESCRIPTOR_LEN);

                snprintf(tmp, sizeof(tmp), "%02d:%02d - %02d:%02d, %s\n", stStartTime.u8Hour, stStartTime.u8Min, stEndTime.u8Hour, stEndTime.u8Min, u8EventName);
                MApp_AT_Msg_Add((U8*)tmp);
                snprintf(tmp, sizeof(tmp), "%s\n", u8DetailDescription);
                MApp_AT_Msg_Add((U8*)tmp);

                pEvent = pNextEvent;
            }
            return EN_AT_RESULT_OK;
        }


        default:
        {
            printf("Wrong SubCmdType! \n");
            return EN_AT_RESULT_ER;
        }
    }
}


#endif // #if ( CHAKRA3_AUTO_TEST && ENABLE_DTV_EPG)


