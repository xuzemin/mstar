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

#if( CHAKRA3_AUTO_TEST )

#include "MApp_AutoTest.h"
#include "apiVDEC.h"
#include "msAPI_Timer.h"
#include "msAPI_Video.h"
#include "MApp_MVDMode.h"
#include "string.h"

#if (ENABLE_DTV)
#include "mapp_eit.h"
#include "mapp_demux.h"
#endif

//
//=======================================================================
//
#if (ENABLE_DTV)

EN_AT_RESULT GetCurrentServiceName(void)
{
    char tmp[MAX_EVENT_NAME+2];
    BYTE name[MAX_SERVICE_NAME];
    WORD u16CurPosIdx;
    MEMBER_SERVICETYPE mServiceType;

    memset(tmp, 0, MAX_EVENT_NAME+2);

    mServiceType = msAPI_CM_GetCurrentServiceType();
    u16CurPosIdx = msAPI_CM_GetCurrentPosition(mServiceType);
    if(!msAPI_CM_GetServiceName(mServiceType, u16CurPosIdx, name))
    {
        printf("Get Current Service Name Error!!!\n");
        return EN_AT_RESULT_ER;
    }
    snprintf(tmp, sizeof(tmp), "%s\n", name);
    MApp_AT_Msg_Add((U8*)tmp);

    return EN_AT_RESULT_OK;
}

EN_AT_RESULT GetAllLogicalNumber(AT_CMD ATCmd)
{
    char tmp[MAX_EVENT_NAME+2];
    WORD i=0;
    WORD DTVChannelCnt;
    WORD RadioChannelCnt;
    WORD DataChannelCnt;
    WORD wLCN;
    MEMBER_SERVICETYPE eGotServiceType;
    WORD wGotPosition, wTS_ID, wON_ID, wService_ID;
    BYTE name[MAX_SERVICE_NAME];

    memset(tmp, 0, MAX_EVENT_NAME+2);

    DTVChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DTV, INCLUDE_ALL);
    RadioChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_RADIO, INCLUDE_ALL);
    DataChannelCnt = msAPI_DTV_GetProgramCount(E_SERVICETYPE_DATA, INCLUDE_ALL);

    DEBUG_AUTOTEST(printf("DTV channel count:%d\n",DTVChannelCnt));
    DEBUG_AUTOTEST(printf("Radio channel count:%d\n",RadioChannelCnt));
    DEBUG_AUTOTEST(printf("Data channel count:%d\n",DataChannelCnt));

    switch(ATCmd.iCmdPara[0])
    {
        case E_LCN_LIST:
            printf("E_LCN_LIST\n");
            for(i=0; i < DTVChannelCnt; i++)
            {
                wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV,i);
                snprintf(tmp, sizeof(tmp), "%d\n",wLCN);
                MApp_AT_Msg_Add((U8*)tmp);
            }
            for(i=0; i < RadioChannelCnt; i++)
            {
                wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_RADIO,i);
                snprintf(tmp, sizeof(tmp), "%d\n",wLCN);
                MApp_AT_Msg_Add((U8*)tmp);
            }
            for(i=0; i < DataChannelCnt; i++)
            {
                wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DATA,i);
                snprintf(tmp, sizeof(tmp), "%d\n",wLCN);
                MApp_AT_Msg_Add((U8*)tmp);
            }
            break;
        case E_SERVICE_TYPE_LIST:
            printf("E_SERVICE_TYPE_LIST\n");
            for(i=0; i < DTVChannelCnt; i++)
            {
                wTS_ID = msAPI_CM_GetTS_ID(E_SERVICETYPE_DTV, i);
                wON_ID = msAPI_CM_GetON_ID(E_SERVICETYPE_DTV, i);
                wService_ID = msAPI_CM_GetService_ID(E_SERVICETYPE_DTV, i);

                if(!msAPI_CM_GetServiceTypeAndPositionWithIDs(wTS_ID, wON_ID, wService_ID, 1, &eGotServiceType, &wGotPosition, TRUE))
                {
                    printf("Get service type and positions with IDs error,Position:%d\n",i);
                    continue;
                }
                DisplayServiceType(eGotServiceType);
            }
            for(i=0; i < RadioChannelCnt; i++)
            {
                wTS_ID = msAPI_CM_GetTS_ID(E_SERVICETYPE_RADIO, i);
                wON_ID = msAPI_CM_GetON_ID(E_SERVICETYPE_RADIO, i);
                wService_ID = msAPI_CM_GetService_ID(E_SERVICETYPE_RADIO, i);

                if(!msAPI_CM_GetServiceTypeAndPositionWithIDs(wTS_ID, wON_ID, wService_ID, 1, &eGotServiceType, &wGotPosition, TRUE))
                {
                    printf("Get service type and positions with IDs error,Position:%d\n",i);
                    continue;
                }
                DisplayServiceType(eGotServiceType);
            }
            for(i=0; i < DataChannelCnt; i++)
            {
                wTS_ID = msAPI_CM_GetTS_ID(E_SERVICETYPE_DATA, i);
                wON_ID = msAPI_CM_GetON_ID(E_SERVICETYPE_DATA, i);
                wService_ID = msAPI_CM_GetService_ID(E_SERVICETYPE_DATA, i);

                if(!msAPI_CM_GetServiceTypeAndPositionWithIDs(wTS_ID, wON_ID, wService_ID, 1, &eGotServiceType, &wGotPosition, TRUE))
                {
                    printf("Get service type and positions with IDs error,Position:%d\n",i);
                    continue;
                }
                DisplayServiceType(eGotServiceType);
            }
            break;
        case E_SERVICE_NAME_LIST:
            printf("E_SERVICE_NAME_LIST\n");
            for(i=0; i < DTVChannelCnt; i++)
            {
                if(!msAPI_CM_GetServiceName(E_SERVICETYPE_DTV, i, name))
                {
                    printf("Get Service Name Error,Postion:%d\n",i);
                    continue;
                }
                snprintf(tmp, sizeof(tmp), "%s\n",name);
                MApp_AT_Msg_Add((U8*)tmp);
            }
            for(i=0; i < RadioChannelCnt; i++)
            {
                if(!msAPI_CM_GetServiceName(E_SERVICETYPE_RADIO, i, name))
                {
                    printf("Get Service Name Error,Postion:%d\n",i);
                    continue;
                }
                snprintf(tmp, sizeof(tmp), "%s\n",name);
                MApp_AT_Msg_Add((U8*)tmp);
            }
            for(i=0; i < DataChannelCnt; i++)
            {
                if(!msAPI_CM_GetServiceName(E_SERVICETYPE_DATA, i, name))
                {
                    printf("Get Service Name Error,Postion:%d\n",i);
                    continue;
                }
                snprintf(tmp, sizeof(tmp), "%s\n",name);
                MApp_AT_Msg_Add((U8*)tmp);
            }
            break;
        default:
            printf("Wrong iCmdPara!!!\n");
            return EN_AT_RESULT_ER;
            break;
    }
    return EN_AT_RESULT_OK;
}

#if(ENABLE_DVB)
EN_AT_RESULT GetCurrentEventInfo(BOOL bPresent)
{
    char tmp[MAX_EVENT_NAME+2];
    MS_EIT_CUR_EVENT_PF astEventInfo[2];
    char sGenreTyp[50];
    U32 u32StartTime;
    U32 u32EndTime;
    ST_TIME stStartTime;
    ST_TIME stEndTime;
    ST_TIME stDuration;
    U16 u16EventName[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U8 u8EventName[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U16 u16EventText[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U8 u8EventText[MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN];
    U32 u32NameSrcLength;
    U32 u32TextSrcLength;
    U8 idx = (bPresent == TRUE) ? 0 : 1;// Present event informaiton

    memset(tmp, 0, MAX_EVENT_NAME+2);

#if(ENABLE_S2)
    if( (MApp_EIT_GetCurPFInfo(astEventInfo)) && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM) && (IsDTVInUse()||IsS2InUse()))
#else
    if( (MApp_EIT_GetCurPFInfo(astEventInfo)) && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM) && IsDTVInUse())
#endif
    {
        if (astEventInfo[idx].start_time[0] != 0 || astEventInfo[idx].start_time[1] != 0 ||
            astEventInfo[idx].start_time[2] != 0 || astEventInfo[idx].start_time[3] != 0 ||
            astEventInfo[idx].start_time[4] != 0 )
        {
            GetGenreType(astEventInfo[idx].u8Content_nibble_level1, sGenreTyp);

#if ENABLE_NZ_EIT_TIME_DISPLAY
            BOOLEAN bDayLightTime,bDayLightTimeEnd,bGotTOT;
            if(IS_DTG_COUNTRY(OSD_COUNTRY_SETTING))
            {
                u32StartTime = MApp_MJDUTC2Seconds(astEventInfo[idx].start_time);
                u32StartTime += MApp_SI_Get_OffsetTime(u32StartTime,&bDayLightTime,&bGotTOT,TRUE);
                u32EndTime = MApp_MJDUTC2Seconds(astEventInfo[idx].start_time) + MApp_UTC2Seconds(astEventInfo[idx].duration);
                u32EndTime += MApp_SI_Get_OffsetTime(u32EndTime,&bDayLightTimeEnd,&bGotTOT,FALSE);
            }
            else
            {
                u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[idx].start_time[0]))+ msAPI_Timer_GetOffsetTime();
                u32EndTime = u32StartTime + MApp_UTC2Seconds(astEventInfo[idx].duration);
            }
#else
            u32StartTime = MApp_MJDUTC2Seconds(&(astEventInfo[idx].start_time[0]))+ msAPI_Timer_GetOffsetTime();
            u32EndTime = u32StartTime + MApp_UTC2Seconds(astEventInfo[idx].duration);
#endif
            MApp_ConvertSeconds2StTime(u32StartTime, &stStartTime);
            MApp_ConvertSeconds2StTime(u32EndTime, &stEndTime);
            MApp_ConvertSeconds2StTime(u32EndTime-u32StartTime, &stDuration);


            MApp_Epg_EventName_LoadFromSED(u16EventName, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN, astEventInfo[idx].short_event_descriptor);
            MApp_Epg_EventText_LoadFromSED(u16EventText, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN, astEventInfo[idx].short_event_descriptor);

            u32NameSrcLength = msAPI_U16BufToU8Buf(u16EventName, u8EventName, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);
            u32TextSrcLength = msAPI_U16BufToU8Buf(u16EventText, u8EventText, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN);

            if (strlen((char*)u8EventName)==0)
            {
                printf("No event name\n");
                return EN_AT_RESULT_OK;
            }

            snprintf(tmp, sizeof(tmp), "%s\n%02d:%02d:%02d-%02d:%02d:%02d (%02d hours %02d minutes)",
                    sGenreTyp,stStartTime.u8Hour,stStartTime.u8Min,stStartTime.u8Sec,
                    stEndTime.u8Hour,stEndTime.u8Min,stEndTime.u8Sec,
                    stDuration.u8Hour,stDuration.u8Min);
            MApp_AT_Msg_Add((U8*)tmp);
            snprintf(tmp, sizeof(tmp), "%s\n",u8EventName);
            MApp_AT_Msg_Add((U8*)tmp);
            snprintf(tmp, sizeof(tmp), "%s\n",u8EventText);
            MApp_AT_Msg_Add((U8*)tmp);
        }
    }

    return EN_AT_RESULT_OK;
}
#endif
EN_AT_RESULT GetLocalTime(void)
{
    char tmp[MAX_EVENT_NAME+2];
    ST_TIME stTime;

    memset(tmp, 0, MAX_EVENT_NAME+2);

    MApp_ConvertSeconds2StTime(MApp_GetLocalSystemTime(), &stTime);
    snprintf(tmp, sizeof(tmp), "%02u/%02u/%u %02u:%02u\n",stTime.u8Day ,stTime.u8Month ,stTime.u16Year ,stTime.u8Hour ,stTime.u8Min);
    MApp_AT_Msg_Add((U8*)tmp);

    return EN_AT_RESULT_OK;
}

EN_AT_RESULT GetVideoInfo(AT_CMD ATCmd)
{
    char tmp[MAX_EVENT_NAME+2];

    memset(tmp, 0, MAX_EVENT_NAME+2);

    if(!msAPI_CM_GetCurrentServiceType() == E_SERVICETYPE_DTV)
    {
        printf("Current service type is not DTV!!!\n");
        return EN_AT_RESULT_ER;
    }

    switch(ATCmd.iCmdPara[0])
    {
        case E_GET_VIDEO_AUDIO_TYPE:
            printf("E_GET_VIDEO_AUDIO_TYPE\n");

            DTV_CHANNEL_INFO CurrentChannelInfo;
            WORD wCurrentPosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DTV);
            if(!msAPI_CM_GetProgramInfo(E_SERVICETYPE_DTV,wCurrentPosition,&CurrentChannelInfo))
            {
                printf("Get program info error!!!\n");
                return EN_AT_RESULT_ER;
            }
            DisplayVideoType(msAPI_CM_GetProgramVideoType(E_SERVICETYPE_DTV ,wCurrentPosition));
            MApp_AT_Msg_Add((U8*)"/");
            //DisplayAudioType((AUDIOSTREAM_TYPE)CurrentChannelInfo.stAudInfo[g_u8AudLangSelected].wAudType);
            DisplayAudioType( msAPI_CM_Get_AudStreamType_By_AudInfo( &(CurrentChannelInfo.stAudInfo[g_u8AudLangSelected]) ) );
            MApp_AT_Msg_Add((U8*)"\n");
            break;
        case E_GET_VIDEO_RESOLUTION:
            printf("E_GET_VIDEO_RESOLUTION\n");
            DisplayResolution(ResolutionRemapping(gstVidStatus.u16HorSize, gstVidStatus.u16VerSize, gstVidStatus.u8Interlace, gstVidStatus.u32FrameRate));
            break;
        case E_GET_VIDEO_QUALITY:
            printf("E_GET_VIDEO_QUALITY\n");
            if(gstVidStatus.u16HorSize >= 1200 && gstVidStatus.u16VerSize >= 700)
                snprintf(tmp, sizeof(tmp), "HD\n");
            else if(gstVidStatus.u16HorSize == 0)
                snprintf(tmp, sizeof(tmp), "UNDEFINED\n");
            else
                snprintf(tmp, sizeof(tmp), "SD\n");
            MApp_AT_Msg_Add((U8*)tmp);
            break;
        default:
            printf("Wrong iCmdPara!!!\n");
            return EN_AT_RESULT_ER;
            break;
    }
    return EN_AT_RESULT_OK;
}

EN_AT_RESULT _MApp_AT_SICmdHandler(AT_CMD ATCmd)
{
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_SI_CMD_GET_CURRENT_SERVERICE_NAME: // 1
        {
            printf("EN_AUTO_TEST_SI_CMD_GET_CURRENT_SERVERICE_NAME \n");
            return GetCurrentServiceName();
        }
        case EN_AUTO_TEST_SI_CMD_GET_ALL_LOGICAL_NUMBER: // 2
        {
            printf("EN_AUTO_TEST_SI_CMD_GET_ALL_LOGICAL_NUMBER \n");
            return GetAllLogicalNumber(ATCmd);
        }
    #if (ENABLE_DVB)
        case EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NOW: // 3
        {
            printf("EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NOW \n");
            return GetCurrentEventInfo(TRUE);

        }
        case EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NEXT: // 4
        {
            printf("EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NEXT \n");
            return GetCurrentEventInfo(FALSE);
        }
    #else
        case EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NOW: // 3
        {
            printf("ERROR---EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NOW \n");
            return EN_AT_RESULT_ER;
        }
        case EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NEXT: // 4
        {
            printf("ERROR---EN_AUTO_TEST_SI_CMD_GET_CURRENT_EVENT_INFO_NEXT \n");
            return EN_AT_RESULT_ER;
        }
    #endif
        case EN_AUTO_TEST_SI_CMD_GET_LOCAL_TIME: // 5
        {
            printf("EN_AUTO_TEST_SI_CMD_GET_LOCAL_TIME \n");
            return GetLocalTime();
        }
        case EN_AUTO_TEST_SI_CMD_GET_VIDEO_INFO: // 17
        {
            printf("EN_AUTO_TEST_SI_CMD_GET_VIDEO_INFO \n");
            return GetVideoInfo(ATCmd);
        }
        default:
        {
            printf("Wrong SubCmdType! \n");
            return EN_AT_RESULT_ER;
        }
    }
}

#endif // #if (ENABLE_DTV)


#endif // #if( CHAKRA3_AUTO_TEST )


