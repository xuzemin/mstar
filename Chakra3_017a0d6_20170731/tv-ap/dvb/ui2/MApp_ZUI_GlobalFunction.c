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

#define MAPP_ZUI_GLOBALFUNCUTION_C
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "drvXC_HDMI_if.h"
#include "apiXC_Hdmi.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_ZUI_Main.h"
#include "MApp_ZUI_APIcommon.h"
#include "MApp_ZUI_APIstrings.h"
#include "MApp_ZUI_APIwindow.h"
#include "ZUI_tables_h.inl"
#include "MApp_ZUI_APIcontrols.h"
#include "MApp_ZUI_ACTmainpage.h"
#include "MApp_ZUI_ACTeffect.h"
#include "OSDcp_String_EnumIndex.h"
#include "ZUI_exefunc.h"
#include "MApp_CharTable.h"
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_Menu_Main.h"

#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif

#include "msAPI_ATVSystem.h"
#include "MApp_ChannelChange.h"

#if ENABLE_DVB//ENABLE_DTV
#include "MApp_Dvb_SI.h" // "mapp_si.h"
#include "msAPI_DTVSystem.h"
#include "MApp_CIMMI.h"
#endif


#include "MApp_ZUI_GlobalFunction.h"

LPTSTR MApp_ZUI_GetCurrentChNumber(void)
{
#if ENABLE_DVB
    if (IsDTVInUse())
    {
        U16 u16Count, u16Pos=0, u16LCN;
        MEMBER_SERVICETYPE bServiceType;

#if MHEG5_ENABLE // <-<<<
        bServiceType=g_eCurrentUserServiceType;
        u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

        if(bServiceType == E_SERVICETYPE_DTV)
        {
            u16Pos=g_wCurrentTVUserServicePosition;
        }
        else if(bServiceType == E_SERVICETYPE_RADIO)
        {
            u16Pos=g_wCurrentRadioUserServicePosition;
        }
#if NORDIG_FUNC //for Nordig spec v2.0
        else if(bServiceType == E_SERVICETYPE_DATA)
        {
            u16Pos=g_wCurrentDataUserServicePosition;
        }
#endif
        else
            u16Pos=0;
#else
        bServiceType = msAPI_CM_GetCurrentServiceType();
        u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        u16Pos = msAPI_CM_GetCurrentPosition(bServiceType);
#endif
        u16LCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, u16Pos);
        if ((u16Count > 0) && (u16LCN != INVALID_LOGICAL_CHANNEL_NUMBER)
      #if(!DVB_T_C_DIFF_DB)
	  && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
      #endif
        )
        {
            return MApp_ZUI_DTV_ChNumString(u16LCN, CHAR_BUFFER);
        }
        else
        {
            return 0;
        }
    }
    else
#endif
    if (IsATVInUse())
    {
        U8 u8Temp;

        u8Temp = msAPI_ATV_GetCurrentProgramNumber();
        u8Temp++;  //ATV channel number start from 1
        return MApp_ZUI_API_GetU16String(u8Temp);
    }

    return 0;
}

#if ENABLE_DVB
LPTSTR MApp_ZUI_DTV_ChNumString(WORD u16LCN, LPTSTR strNum)
{
#if ENABLE_SBTVD_DTV_SYSTEM
    if(msAPI_SRC_IS_SBTVD_InUse())
    {
        LPTSTR str = strNum;
        LOGICAL_CHANNEL_NUMBER LCN;
        LCN.wLCN = (WORD)u16LCN;
        MApp_UlongToU16String((U32)LCN.stLCN.bPhysicalChannel, str, (S8)MApp_GetNoOfDigit((U32)LCN.stLCN.bPhysicalChannel));
        str += (MApp_GetNoOfDigit((U32)LCN.stLCN.bPhysicalChannel));
        *str ++ = CHAR_DOT;
        MApp_UlongToU16String((U32)LCN.stLCN.bVirtualChannel, str, (S8)MApp_GetNoOfDigit((U32)LCN.stLCN.bVirtualChannel));
    }
    else
#endif
    {
        MApp_UlongToU16String(u16LCN, strNum, MApp_GetNoOfDigit(u16LCN));
    }
    return strNum;
}

static BOOLEAN _MApp_ZUI_ACT_GetServiceNameToUCS2(MEMBER_SERVICETYPE bServiceType, WORD wPosition, WORD * bChannelName, U8 ControlCodes)
{
    U8 tempBuffer[MAX_SERVICE_NAME];
  #if (ENABLE_CI_PLUS)
    U8 tempBuffer2[MAX_SERVICE_NAME];
  #endif
    U8 *tempBuf2;
    tempBuf2=(U8*)bChannelName;
    if(msAPI_CM_GetServiceName(bServiceType, wPosition, tempBuf2)==TRUE)
    {
#if (ENABLE_CI_PLUS)
        if((TRUE == MApp_CI_IsOpMode()) && (TRUE == MApp_CI_SetCharCodeTableToSrvName(tempBuf2, MAX_SERVICE_NAME, tempBuffer2, MAX_SERVICE_NAME, MApp_CI_GetCurrentOpCicamId())))
        {
            MApp_SI_GetString(tempBuffer, MAX_SERVICE_NAME, tempBuffer2, MAX_SERVICE_NAME, ControlCodes);
            MApp_CharTable_MappingDVBTextToUCS2(tempBuffer, bChannelName, MAX_SERVICE_NAME, MAX_SERVICE_NAME, REMOVE_00AD_SOFT_HYPHEN);
        }
        else
        {
            MApp_SI_GetString(tempBuffer, MAX_SERVICE_NAME, tempBuf2, MAX_SERVICE_NAME, ControlCodes);
            MApp_CharTable_MappingDVBTextToUCS2(tempBuffer, bChannelName, MAX_SERVICE_NAME, MAX_SERVICE_NAME, REMOVE_00AD_SOFT_HYPHEN);
        }
#else
        MApp_SI_GetString(tempBuffer, MAX_SERVICE_NAME, tempBuf2, MAX_SERVICE_NAME, ControlCodes);
        MApp_CharTable_MappingDVBTextToUCS2(tempBuffer, bChannelName, MAX_SERVICE_NAME, MAX_SERVICE_NAME, REMOVE_00AD_SOFT_HYPHEN);
#endif
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#endif

U16 MApp_ZUI_GetCurrentInputSourceStringID(E_UI_INPUT_SOURCE src)
{
    U16 u16TempID = Empty;

    //from function SourceTypeText():
    {
        switch(src)
        {
            case UI_INPUT_SOURCE_RGB:
                u16TempID= en_str_PCdashRGB;
                break;

            /*
            case UI_INPUT_SOURCE_DTV:
                u16TempID=en_str_DTV;
                break;
            case UI_INPUT_SOURCE_ATV:
                u16TempID=en_str_ATV;
                break;
            */

        #if (INPUT_AV_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_AV:
                u16TempID=en_str_AV;
                break;
        #elif (INPUT_AV_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_AV:
                u16TempID=en_str_AV_1;
                break;
            case UI_INPUT_SOURCE_AV2:
                u16TempID=en_str_AV_2;
                break;
        #endif

        #if (INPUT_AV_VIDEO_COUNT >= 3)
            case UI_INPUT_SOURCE_AV3:
                u16TempID=en_str_AV_3;
                break;
        #endif

        #if (INPUT_SV_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_SVIDEO:
                u16TempID=en_str_SdashVideo;
                break;
        #endif

        #if (INPUT_SV_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_SVIDEO:
                u16TempID=en_str_SdashVideo_1;
                break;
            case UI_INPUT_SOURCE_SVIDEO2:
                u16TempID=en_str_SdashVideo_2;
                break;
        #endif

        #if (INPUT_YPBPR_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_COMPONENT:
                u16TempID=en_str_Component;
                break;
        #elif (INPUT_YPBPR_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_COMPONENT:
                u16TempID=en_str_Component1;
                break;
            case UI_INPUT_SOURCE_COMPONENT2:
                u16TempID=en_str_Component2;
                break;
        #endif

        #if   (INPUT_SCART_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_SCART:
                u16TempID=en_str_SCART;
                break;
        #elif (INPUT_SCART_VIDEO_COUNT == 2)
            case UI_INPUT_SOURCE_SCART:
                u16TempID=en_str_SCART_1;
                break;
            case UI_INPUT_SOURCE_SCART2:
                u16TempID=en_str_SCART_2;
                break;
        #endif

        #if (INPUT_HDMI_VIDEO_COUNT == 1)
            case UI_INPUT_SOURCE_HDMI:
                if (g_HdmiPollingStatus.bIsHDMIMode)
                    u16TempID=en_str_HDMI;
                else
                    u16TempID=en_str_DVI1;

                break;
        #endif

        #if (INPUT_HDMI_VIDEO_COUNT >= 2)
            case UI_INPUT_SOURCE_HDMI:
                 if (g_HdmiPollingStatus.bIsHDMIMode)
                    u16TempID=en_str_HDMI1;
                 else
                    u16TempID=en_str_DVI1;

                break;

            case UI_INPUT_SOURCE_HDMI2:
                if (g_HdmiPollingStatus.bIsHDMIMode)
                    u16TempID=en_str_HDMI2;
                else
                    u16TempID=en_str_DVI2;

                break;
        #endif

        #if (INPUT_HDMI_VIDEO_COUNT >= 3)
            case UI_INPUT_SOURCE_HDMI3:
                if (g_HdmiPollingStatus.bIsHDMIMode)
                    u16TempID=en_str_HDMI3;
                else
                    u16TempID=en_str_DVI3;

                break;
        #endif

        #if (INPUT_HDMI_VIDEO_COUNT >= 4)
            case UI_INPUT_SOURCE_HDMI4:
                if (g_HdmiPollingStatus.bIsHDMIMode)
                    u16TempID=en_str_HDMI4;
                else
                    u16TempID=en_str_DVI;

                break;
        #endif


        #if(ENABLE_FM_RADIO)
            case UI_INPUT_SOURCE_FMRADIO:
                u16TempID=en_str_FM_Radio;
        #endif

            default:
                //u16TempID=en_str_DTV;
                break;
        }
    }
    return u16TempID;
}


LPTSTR MApp_ZUI_GetCurrentChName(SCALER_WIN eWindow)
{
    LPTSTR str = CHAR_BUFFER;
    str[0] = 0;

#if ENABLE_DVB
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(eWindow))
  #if(!DVB_T_C_DIFF_DB)
	 && (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
  #endif
    )
    {
        U16 u16Count, u16Pos=0;
        MEMBER_SERVICETYPE bServiceType;

    #if MHEG5_ENABLE // <-<<<
       bServiceType=g_eCurrentUserServiceType;

       u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

        if(bServiceType == E_SERVICETYPE_DTV)
        {
            u16Pos=g_wCurrentTVUserServicePosition;
        }
        else if(bServiceType == E_SERVICETYPE_RADIO)
        {
            u16Pos=g_wCurrentRadioUserServicePosition;
        }
        #if NORDIG_FUNC //for Nordig spec v2.0
        else if(bServiceType == E_SERVICETYPE_DATA)
        {
            u16Pos=g_wCurrentDataUserServicePosition;
        }
        #endif
        else
            u16Pos=0;

    #else
        bServiceType = msAPI_CM_GetCurrentServiceType();
        u16Count = msAPI_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        u16Pos = msAPI_CM_GetCurrentPosition(bServiceType);
    #endif
        if (u16Count > 0)
        {
            _MApp_ZUI_ACT_GetServiceNameToUCS2(bServiceType, u16Pos, str, KEEP_CONTROL_CODE_NONE);
            {
                str[MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN] = 0;
            }
            return str;
        }
        else
        {
            return 0;
        }
    }
    else
#endif
    if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        U8 u8Temp[MAX_STATION_NAME]={0,0,0,0,0,0,0,0};

        msAPI_ATV_GetStationName(msAPI_ATV_GetCurrentProgramNumber(), u8Temp);

        MApp_ZUI_API_StringBuffU8toU16(CHAR_BUFFER, u8Temp, MAX_STATION_NAME);

        CHAR_BUFFER[MAX_MANUALSCAN_MENU_PROGRAMNAME_LEN] = 0;

        return CHAR_BUFFER;
    }

#if (ENABLE_PIP)
    if(IsPIPSupported())
    {
        if(eWindow==MAIN_WINDOW)
            return (MApp_ZUI_API_GetString(MApp_ZUI_GetCurrentInputSourceStringID(UI_INPUT_SOURCE_TYPE)));
        else
            return (MApp_ZUI_API_GetString(MApp_ZUI_GetCurrentInputSourceStringID(stGenSetting.g_stPipSetting.enSubInputSourceType)));
    }
    else
#endif
    {
        return (MApp_ZUI_API_GetString(MApp_ZUI_GetCurrentInputSourceStringID(UI_INPUT_SOURCE_TYPE)));
    }
}

#if ENABLE_DTV_EPG //ENABLE_DTV
LPTSTR MApp_ZUI_GetCurrentEventName(void)
{
    MS_EIT_CUR_EVENT_PF astEventInfo[2];

    if ( (MApp_EIT_GetCurPFInfo(astEventInfo) ) && (MApp_Dmx_EIT_Get_CurPfVer()!=INVALID_VERSION_NUM) && IsDTVInUse()
  #if(!DVB_T_C_DIFF_DB)
	&& (DB_PROGRAM_SOURCE_TYPE == UI_INPUT_SOURCE_TYPE)
  #endif
    )
    {
#if MHEG5_ENABLE // <-<<<
        if( g_eCurrentUserServiceType != g_eCurrentRealServiceType
            || (g_eCurrentRealServiceType == E_SERVICETYPE_DTV && g_wCurrentTVUserServicePosition != g_wCurrentTVRealServicePosition)
            || (g_eCurrentRealServiceType == E_SERVICETYPE_RADIO && g_wCurrentRadioUserServicePosition != g_wCurrentRadioRealServicePosition)
#if NORDIG_FUNC //for Nordig spec v2.0
            || (g_eCurrentRealServiceType == E_SERVICETYPE_DATA && g_wCurrentDataUserServicePosition != g_wCurrentDataRealServicePosition)
#endif
          )
        {
            return 0;
        }
#endif
        MApp_Epg_EventName_LoadFromSED(CHAR_BUFFER, MW_MAX_SHORT_EVENT_DESCRIPTOR_LEN, astEventInfo[bNextEvent].short_event_descriptor);
        if (CHAR_BUFFER[0] != 0)
        {
            return CHAR_BUFFER;
        }
    }

    //return 0;//show nothing, if there is no even name
    return (MApp_ZUI_API_GetString(en_str_No_Information));
}
#endif
#undef MAPP_ZUI_GLOBALFUNCUTION_C

