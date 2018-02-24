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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_GLOBAL_FUNCTION_C

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------

#include <string.h>
#include <math.h>
#include "datatype.h"
#include "sysinfo.h"
#include "MsTypes.h"
#include "drvBDMA.h"
#include "drvCPU.h"
#include "debug.h"

// Common Definition
#include "apiXC.h"
#include "apiXC_Adc.h"

#include "msAPI_CPU.h"

#include "msAPI_Timer.h"
#include "msAPI_Power.h"
#include "msAPI_Memory.h"
#include "msAPI_Video.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_FreqTableCommon.h"
#include "msAPI_DrvInit.h"
#include "msAPI_VD.h"
#include "MApp_ChannelChange.h"

#if(ENABLE_TEST_PATTERN)
#include "msAPI_TestPattern.h"
#endif


#include "MApp_PCMode.h"
#if ENABLE_TTX
#include "msAPI_TTX.h"
#include "mapp_ttx.h"
#endif
#include "MApp_GlobalVar.h"
#include "MApp_GlobalFunction.h"
#include "MApp_RestoreToDefault.h"
#include "MApp_VDMode.h"
#include "MApp_SaveData.h"
#include "MApp_TV.h"

#if (ENABLE_DTV)
#include "mapp_si.h"
#include "mapp_epgdb_public.h"
#endif

#include "MApp_ATVProc.h"
#include "MApp_MVDMode.h"
#if (MHEG5_ENABLE)
#include "msAPI_MHEG5.h"
#include "MApp_MHEG5_Main.h"
#endif
#if ENABLE_DLC
#include "apiXC_Dlc.h"
#endif
#if ENABLE_DBC
#include "apiXC_DBC.h"
#endif

#include "MApp_UiMenuDef.h" //ZUI:
#if(ENABLE_DTV)
#include "mapp_si.h"
#include "msAPI_FreqTableDTV.h"
#endif
#if ENABLE_CI
#include "msAPI_CI.h"
#endif
#if(ENABLE_CEC)
#include "apiCEC.h"
#include "msAPI_CEC.h"
#endif

#include "MApp_LoadFontInit.h"
#include "MApp_Audio.h"

#include "MApp_TopStateMachine.h"

#if(ENABLE_ATSC)
#include "MApp_Audio_ATSC.h"
#endif

#include "ZUI_tables_h.inl"

/***************************************************************************************/
#define    GET_3BYTE( cp )    ( ( ( (U32)(*cp) )<< 16 ) | ( ( (U32)(*(cp+1)) ) <<  8 ) | ( ( (U32)(*(cp+2)) ) ) )
#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif
extern U16 OSD_L;
extern U16 Audio_L;
extern U16 Subtitle_L;

extern BOOLEAN bFontSysInit;

/* ??Cë¤?*/
code U8 SolarCal[12] =
{
    31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

/* ??Cë¤§Ö¿n, ??P?? */
code U16 SolarDays[28] =
{
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365, 396, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366, 397
};

static EN_OSD_COUNTRY_SETTING m_eOSDCountrySetting;
#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
static EN_OSD_CERTIFICATION_SETTING m_eOSDCertificationSetting;
static EN_OSD_UNITYMEDIA_COUNTRY_SETTING m_eOSDUnityMediaCountrySetting;
static EN_OSD_ZIGGO_COUNTRY_SETTING m_eOSDZiggoCountrySetting;
#endif
#if (!ENABLE_DVB)
typedef struct _TimeZone2Country
{
    EN_MENU_TIMEZONE eTimeZone;
    EN_OSD_COUNTRY_SETTING eCountry;
} TimeZone2Country;
static code TimeZone2Country stTimeZone2Country[]=
{
    {TIMEZONE_CANARY,       OSD_COUNTRY_SPAIN},
    {TIMEZONE_LISBON,       OSD_COUNTRY_PORTUGAL},
    {TIMEZONE_LONDON,       OSD_COUNTRY_UK},
    {TIMEZONE_RABAT,        OSD_COUNTRY_MOROCCO},
    {TIMEZONE_AMSTERDAM,    OSD_COUNTRY_NETHERLANDS},
    {TIMEZONE_BEOGRAD,      OSD_COUNTRY_SERBIA},
    {TIMEZONE_BERLIN,       OSD_COUNTRY_GERMANY},
    {TIMEZONE_BRUSSELS,     OSD_COUNTRY_BELGIUM},
    {TIMEZONE_BUDAPEST,     OSD_COUNTRY_HUNGARY},
    {TIMEZONE_COPENHAGEN,   OSD_COUNTRY_DENMARK},
    {TIMEZONE_LIUBLJANA,    OSD_COUNTRY_SLOVENIA},
    {TIMEZONE_LUXEMBOURG,   OSD_COUNTRY_LUXEMBOURG},
    {TIMEZONE_MADRID,       OSD_COUNTRY_SPAIN},
    {TIMEZONE_OSLO,         OSD_COUNTRY_NORWAY},
    {TIMEZONE_PARIS,        OSD_COUNTRY_FRANCE},
    {TIMEZONE_PRAGUE,       OSD_COUNTRY_CZECH},
    {TIMEZONE_BRATISLAVA,   OSD_COUNTRY_SLOVAKIA},
    {TIMEZONE_BERN,         OSD_COUNTRY_SWITZERLAND},
    {TIMEZONE_ROME,         OSD_COUNTRY_ITALY},
    {TIMEZONE_STOCKHOLM,    OSD_COUNTRY_SWEDEN},
    {TIMEZONE_WARSAW,       OSD_COUNTRY_POLAND},
    {TIMEZONE_VIENNA,       OSD_COUNTRY_AUSTRIA},
    {TIMEZONE_ZAGREB,       OSD_COUNTRY_CROATIA},
    {TIMEZONE_TUNIS,        OSD_COUNTRY_TUNIS},
    {TIMEZONE_ALGIERS,      OSD_COUNTRY_ALGERIA},
    {TIMEZONE_ATHENS,       OSD_COUNTRY_GREECE},
    {TIMEZONE_BUCURESTI,    OSD_COUNTRY_ROMANIA},
    {TIMEZONE_HELSINKI,     OSD_COUNTRY_FINLAND},
    {TIMEZONE_SOFIA,        OSD_COUNTRY_BULGARIA},
    {TIMEZONE_CAIRO,        OSD_COUNTRY_EGYPT},
    {TIMEZONE_CAPE_TOWN,    OSD_COUNTRY_SOUTH_AFRICA},
    {TIMEZONE_JERUSSLEM,    OSD_COUNTRY_ISRAEL},
    {TIMEZONE_MOSCOW,       OSD_COUNTRY_RUSSIA},
    {TIMEZONE_TEHERAN,      OSD_COUNTRY_IRAN},
    {TIMEZONE_ABU_DHABI,    OSD_COUNTRY_UNITED_ARAB_EMIRATES},
    {TIMEZONE_KUWAIT,       OSD_COUNTRY_KUWAIT},
    {TIMEZONE_MUSCAT,       OSD_COUNTRY_OMAN},
    {TIMEZONE_DOHA,         OSD_COUNTRY_QATAR},
    {TIMEZONE_RIYADH,       OSD_COUNTRY_SAUDI_ARABIA},
    {TIMEZONE_MANAMA,       OSD_COUNTRY_BAHRAIN},
    {TIMEZONE_BEIJING,      OSD_COUNTRY_CHINA},
//    {TIMEZONE_ESTONIA,      OSD_COUNTRY_ESTONIA},
//    {TIMEZONE_TURKEY,      OSD_COUNTRY_TURKEY},
    {TIMEZONE_WA,           OSD_COUNTRY_AUSTRALIA},
    {TIMEZONE_SA,           OSD_COUNTRY_AUSTRALIA},
    {TIMEZONE_NT,           OSD_COUNTRY_AUSTRALIA},
    {TIMEZONE_NSW,          OSD_COUNTRY_AUSTRALIA},
    {TIMEZONE_VIC,          OSD_COUNTRY_AUSTRALIA},
    {TIMEZONE_QLD,          OSD_COUNTRY_AUSTRALIA},
    {TIMEZONE_TAS,          OSD_COUNTRY_AUSTRALIA},
#if(ENABLE_COUNTRY_SINGAPORE)
    {TIMEZONE_SINGAPORE,       OSD_COUNTRY_SINGAPORE},
#endif
#if(ENABLE_COUNTRY_VIETNAM)
    {TIMEZONE_VIETNAM,       OSD_COUNTRY_VIETNAM},
#endif
#if(ENABLE_COUNTRY_KENYA)
    {TIMEZONE_KENYA,       OSD_COUNTRY_KENYA},
#endif
#if(ENABLE_COUNTRY_MYANMAR)
    {TIMEZONE_MYANMAR,       OSD_COUNTRY_MYANMAR},
#endif
#if ENABLE_SBTVD_DTV_SYSTEM
    {TIMEZONE_AM_WEST,      OSD_COUNTRY_BRAZIL},
    {TIMEZONE_ACRE,         OSD_COUNTRY_BRAZIL},
    {TIMEZONE_M_GROSSO,     OSD_COUNTRY_BRAZIL},
    {TIMEZONE_NORTH,        OSD_COUNTRY_BRAZIL},
    {TIMEZONE_BRASILIA,     OSD_COUNTRY_BRAZIL},
    {TIMEZONE_NORTHEAST,    OSD_COUNTRY_BRAZIL},
    {TIMEZONE_F_NORONHA,    OSD_COUNTRY_BRAZIL},
#endif
};
#endif
//*******************************************************************************
//             Functions
//******************************************************************************
#if ENABLE_DVB
static void MApp_SetSICountry(EN_OSD_COUNTRY_SETTING eOSDCountrySetting);
#else
static EN_MENU_TIMEZONE MApp_GetTimeZoneByCountry(EN_OSD_COUNTRY_SETTING eCountry);
#endif

#if ( ENABLE_ARABIC_OSD || ENABLE_THAI_OSD )
extern void msAPI_OSD_SetOSDLanguage(EN_OSDAPI_LANGUAGE eLanguage);
#endif

//*************************************************************************
//Function name:    MApp_GetNoOfDigit
//Passing parameter:    U32 u32Data: Value need to be calculated
//Return parameter:     U8: number of digit
//Description:      Calculate the digit number of u32Data
//*************************************************************************
U8 MApp_GetNoOfDigit ( U32 u32Data )
{
    U8 u8NoOfDigit;

    u8NoOfDigit = 0;
    do
    {
        u32Data /= 10;
        u8NoOfDigit++;
    }
    while ( u32Data != 0 );

    return u8NoOfDigit;
}
//*************************************************************************
//Function name:    MApp_UlongToU16String
//Passing parameter:    U32 ulValue: Value need to be transfered into string
//              U16* bArrOutput: Transfered string pointer
//              S8 NoOfDigit: The number of digits need to transfer
// Return parameter:    none
//Description:      Transfer numer to u16string
//*************************************************************************
//#if (KEEP_UNUSED_FUNC == 1)
void MApp_UlongToU16String ( U32 ulValue, U16 *pArrOutput, S8 NoOfDigit )
{
    pArrOutput[NoOfDigit] = 0;
    NoOfDigit -= 1;

    while ( ulValue )
    {
        pArrOutput[NoOfDigit--] = ( ulValue % 10 ) + 0x30;
        ulValue /= 10;
    }
    while ( NoOfDigit >= 0 )
    {
        pArrOutput[NoOfDigit] = '0';
        NoOfDigit--;
    }
}
//#endif

//*************************************************************************
//Function name:    MApp_UlongToU8String
//Passing parameter:    U32 ulValue: Value need to be transfered into string
//              U16* bArrOutput: Transfered string pointer
//              S8 NoOfDigit: The number of digits need to transfer
// Return parameter:    none
//Description:      Transfer numer to u8string
//*************************************************************************
void MApp_UlongToU8String ( U32 ulValue, U8 *pArrOutput, S8 NoOfDigit )
{
    pArrOutput[NoOfDigit] = 0;
    NoOfDigit -= 1;

    while ( ulValue )
    {
        pArrOutput[NoOfDigit--] = ( ulValue % 10 ) + 0x30;
        ulValue /= 10;
    }
    while ( NoOfDigit >= 0 )
    {
        pArrOutput[NoOfDigit] = '0';
        NoOfDigit--;
    }
}

#if (ENABLE_ATSC)
//*************************************************************************
//Function name:    MApp_UlongToString
//Passing parameter:    U32 ulValue: Value need to be transfered into string
//              U8* bArrOutput: Transfered string pointer
//              S8 NoOfDigit: The number of digits need to transfer
//Return parameter:     none
//Description:      Transfer numer to string
//*************************************************************************
void MApp_UlongToString ( U32 ulValue, U8 *bArrOutput, S8 NoOfDigit )
{
    bArrOutput[NoOfDigit] = 0;
    NoOfDigit -= 1;

    while ( ulValue )
    {
        bArrOutput[NoOfDigit--] = ( ulValue % 10 ) + 48;
        ulValue /= 10;
    }
    while ( NoOfDigit >= 0 )
    {
        bArrOutput[NoOfDigit] = '0';
        NoOfDigit--;
    }
}
#endif

void MApp_U16StringToU8String ( U16 *pu16Str, U8 *pu8Str, U8 u8Strlen )
{
    U8 u8Index;

    for ( u8Index = 0; u8Index < u8Strlen; u8Index++ )
    {
        pu8Str[u8Index] = (U8)pu16Str[u8Index];
    }
    pu8Str[u8Index] = 0;
}

U16 MApp_UiMenu_u16Strlen(U16 *pu16Str)
{
    U16 u16Count;

    u16Count = 0;
    while(*pu16Str++ != 0)
    {
        u16Count++;
    }
    return u16Count;
}


//*************************************************************************
//Function name:    MApp_GetNoOfHexDigit
//Passing parameter:    U32 u32Data: Value need to be calculated
//Return parameter:     U8: number of digit
//Description:      Calculate the digit number of u32Data
//*************************************************************************
U8 MApp_GetNoOfHexDigit ( U32 u32Data )
{
    U8 u8NoOfDigit;

    u8NoOfDigit = 0;
    do
    {
        u32Data /= 0x10;
        u8NoOfDigit++;
    }
    while ( u32Data != 0 );

    return u8NoOfDigit;
}
//*************************************************************************
//Function name:    MApp_HexUlongToU16String
//Passing parameter:    U32 ulValue: Value need to be transfered into string
//              U16* bArrOutput: Transfered string pointer
//              S8 NoOfDigit: The number of digits need to transfer
// Return parameter:    none
//Description:      Transfer numer to u16string
//*************************************************************************
//#if (KEEP_UNUSED_FUNC == 1)
void MApp_HexUlongToU16String ( U32 ulValue, U16 *pArrOutput, S8 NoOfDigit )
{
    U8 u8NumValue = 0;

    pArrOutput[NoOfDigit] = 0;
    NoOfDigit -= 1;

    while ( ulValue )
    {
        u8NumValue = ulValue % 0x10;
        if(u8NumValue <= 9)
            pArrOutput[NoOfDigit] = u8NumValue + 0x30;
        else
            pArrOutput[NoOfDigit] = (u8NumValue-0x0A) + 'A';
        NoOfDigit--;
        ulValue /= 0x10;
    }
    while ( NoOfDigit >= 0 )
    {
        pArrOutput[NoOfDigit] = '0';
        NoOfDigit--;
    }
}
//#endif

void MApp_HexUlongToU8String ( U32 ulValue, U8 *pArrOutput, S8 NoOfDigit )
{
    U8 u8NumValue = 0;

    pArrOutput[NoOfDigit] = 0;
    NoOfDigit -= 1;

    while ( ulValue )
    {
        u8NumValue = ulValue % 0x10;
        if(u8NumValue <= 9)
            pArrOutput[NoOfDigit] = u8NumValue + 0x30;
        else
            pArrOutput[NoOfDigit] = (u8NumValue-0x0A) + 'A';
        NoOfDigit--;
        ulValue /= 0x10;
    }
    while ( NoOfDigit >= 0 )
    {
        pArrOutput[NoOfDigit] = '0';
        NoOfDigit--;
    }
}


//*************************************************************************
//Function name:    MApp_U8StringToU16String
//Passing parameter:    U8 *pu8Str: string pointer to be transfered
//              U16 *pu16Str: transfered string pointer
//              U8 u8Strlen: the number of characters to be transfered
// Return parameter:    none
//Description:      Transfer u8string to u16string
//*************************************************************************
void MApp_U8StringToU16String ( U8 *pu8Str, U16 *pu16Str, U8 u8Strlen )
{
    U8 u8Index;

    for ( u8Index = 0; u8Index < u8Strlen; u8Index++ )
    {
        pu16Str[u8Index] = pu8Str[u8Index];
    }
    pu16Str[u8Index] = 0;
}

U32 MApp_U8StringToUlong(U8* InputStr, U8 len)
{
    U32 ulValue = 0;
    U8 strIdx = 0;

    if(len<=1)
        return ulValue;

    for(strIdx=0; strIdx<len; strIdx++)
    {
        ulValue *= 10;
        ulValue += InputStr[strIdx] - '0';
    }

    return ulValue;
}

//*************************************************************************
//Function name:    MApp_GetLeap
//Passing parameter:    U16 year :  current solar year
//Return parameter:     U8: Leap year or not
//Description:      Decide leap year
//*************************************************************************
U8 MApp_GetLeap ( U16 u16year )
{
    if ( u16year % 400 == 0 )
    {
        return 1;
    }
    else if ( u16year % 100 == 0 )
    {
        return 0;
    }
    else if ( u16year % 4 == 0 )
    {
        return 1;
    }

    return 0;
}

// Get day of week
U8 MApp_GetDayOfWeek(U16 u16Year, U8 u8Month, U8 u8Day)
{
    U8 i;
    U16 u16days = 0;
    U32 u32sum;

    for(i = 1; i<=(u8Month - 1); i++)
    {
        u16days+=SolarCal[i - 1];
    }

    if(MApp_GetLeap( u16Year )&&u8Month>2)
        u16days+=1;

    u16days+=u8Day;

    u32sum = u16Year -1 + ((u16Year - 1)/4) - ((u16Year - 1)/100) + ((u16Year - 1)/400) + u16days;

    return (U8) (u32sum%7);
}

//*************************************************************************
//Function name:    MApp_GetDaysOfThisYear
//Passing parameter:    U16 u16Year : specific year
//Return parameter:     U16: number of days
//Description:      Get number of days of the specific year
//*************************************************************************
static U16 MApp_GetDaysOfThisYear ( U16 u16Year )
{
    return MApp_GetLeap( u16Year ) ? 366 : 365;
}
//*************************************************************************
//Function name:    MApp_GetDaysOfThisMonth
//Passing parameter:    U16 u16Year : specific year
//              U8 u8Month : specific month (1 ~ 12)
//Return parameter:     U8: number of days
//Description:      Get number of days of the specific month
//*************************************************************************
U8 MApp_GetDaysOfThisMonth ( U16 u16Year, U8 u8Month )
{
    if ( u8Month >= 1 && u8Month <= 12 )
    {
        return ( ( MApp_GetLeap( u16Year ) && u8Month == 2 ) ? 29 : SolarCal[u8Month - 1] );
    }
    else
    {
        return 0;
    }
}
//*************************************************************************
//Function name:    MApp_SetToDefaultSystemTime
//Passing parameter:    ST_TIME *pstTime : pointer of date structure
//Return parameter:     none
//Description:      set to default date
//*************************************************************************
/* the base time starts from DEFAULT_YEAR/DEFAULT_MONTH/DEFAULT_DAY DEFAULT_HOUR:DEFAULT_MIN:DEFAULT_SEC*/
void MApp_SetToDefaultSystemTime ( ST_TIME *pstTime )
{
    pstTime->u16Year = DEFAULT_YEAR;
    pstTime->u8Month = DEFAULT_MONTH;

#if ENABLE_ATSC
    pstTime->u8Day = DEFAULT_DAY_ATSC;
#else
    pstTime->u8Day = DEFAULT_DAY;
#endif
    pstTime->u8Hour = DEFAULT_HOUR;
    pstTime->u8Min = DEFAULT_MIN;
    pstTime->u8Sec = DEFAULT_SEC;
}
/*****************************************************************************/
/* please refer to EN300 468 Annex C */
#if 0
void MApp_MJDUTC2Date(U8 *pau8TDTData, ST_TIME *pstTime)
{
    U8 YY,MM,K;
    U16 u16MJD;

    u16MJD = pau8TDTData[0] << 8 | pau8TDTData[1];
    if(u16MJD > DEFAULT_MJD)
    {
    YY = (U8) ((u16MJD - 15078.2) / 365.25);
    MM = (U8) ((u16MJD - 14956.1 - (YY * 365.25)) / 30.6001);
    K = ((MM == 14) || (MM == 15)) ? 1 : 0;

    pstTime->u16Year = (U16) (1900 + YY + K);
    pstTime->u8Month = (U8) (MM - 1 - (K * 12));
    pstTime->u8Day = (U8) (u16MJD - 14956 - (U16) (YY * 365.25) - (U16) (MM * 30.6001));
    pstTime->u8Hour = BCD2Dec(pau8TDTData[2]);
    pstTime->u8Min = BCD2Dec(pau8TDTData[3]);
    pstTime->u8Sec = BCD2Dec(pau8TDTData[4]);
    }
    else
    {
    /* set to default date */
    MApp_SetToDefaultSystemTime(pstTime);
    }
}
U32 MApp_MJDUTC2Seconds ( U8 *pau8TDTData )
{
    U8 YY, MM, K;
    U16 u16MJD;
    U32 u32TotalSeconds;

    u32TotalSeconds = 0;
    u16MJD = pau8TDTData[0] << 8 | pau8TDTData[1];
    if ( u16MJD > DEFAULT_MJD )
    {
        YY = ( U8 ) ( ( u16MJD - 15078.2 ) / 365.25 );
        MM = ( U8 ) ( ( u16MJD - 14956.1 - ( YY * 365.25 ) ) / 30.6001 );
        K = ( ( MM == 14 ) || ( MM == 15 ) ) ? 1 : 0;

        stDate.u16Year = ( U16 ) ( 1900 + YY + K );
        stDate.u8Month = ( U8 ) ( MM - 1 - ( K * 12 ) );
        stDate.u8Day = ( U8 ) ( u16MJD - 14956 - ( U16 ) ( YY * 365.25 ) - ( U16 ) ( MM * 30.6001 ) );
        stDate.u8Hour = BCD2Dec( pau8TDTData[2] );
        stDate.u8Min = BCD2Dec( pau8TDTData[3] );
        stDate.u8Sec = BCD2Dec( pau8TDTData[4] );

        /* sec */
        u32TotalSeconds += stDate.u8Sec;

        /* min */
        u32TotalSeconds += stDate.u8Min * SECONDS_PER_MIN;

        /* hour */
        u32TotalSeconds += stDate.u8Hour * SECONDS_PER_HOUR;

        /* day */
        u32TotalSeconds += ( stDate.u8Day - 1 ) * SECONDS_PER_DAY;

        /* month */
        u32TotalSeconds += SolarDays[MApp_GetLeap( stDate.u16Year ) * 14 + stDate.u8Month - 1] * SECONDS_PER_DAY;

        /* year */
        while ( stDate.u16Year > DEFAULT_YEAR )
        {
            stDate.u16Year--;
            u32TotalSeconds += MApp_GetDaysOfThisYear( stDate.u16Year ) * SECONDS_PER_DAY;
        }
    }

    return u32TotalSeconds;
}
#endif
//*************************************************************************
//Function name:    MApp_ConvertStTime2Seconds
//Passing parameter:    ST_TIME *pstTime :  date got from TDT
//Return parameter:     U32 u32TotalSeconds : total secounds
//Description:      calculate total seconds which starts from the default date
//*************************************************************************
/* the base time starts from DEFAULT_YEAR/DEFAULT_MONTH/DEFAULT_DAY DEFAULT_HOUR:DEFAULT_MIN:DEFAULT_SEC*/
U32 MApp_ConvertStTime2Seconds ( ST_TIME *pstTime )
{
    U32 u32TotalSeconds;
    U16 u16YearCalc;

    u32TotalSeconds = 0;

    /* sec */
    u32TotalSeconds += pstTime->u8Sec;

    /* min */
    u32TotalSeconds += pstTime->u8Min * SECONDS_PER_MIN;

    /* hour */
    u32TotalSeconds += pstTime->u8Hour * SECONDS_PER_HOUR;

    /* day */
    u32TotalSeconds += ( pstTime->u8Day - 1 ) * SECONDS_PER_DAY;

    /* month */
    u32TotalSeconds += SolarDays[MApp_GetLeap( pstTime->u16Year ) * 14 + pstTime->u8Month - 1] * SECONDS_PER_DAY;

    /* year */
    u16YearCalc = pstTime->u16Year;
    while(u16YearCalc > DEFAULT_YEAR)
    {
        u16YearCalc--;
        u32TotalSeconds += MApp_GetDaysOfThisYear( u16YearCalc ) * SECONDS_PER_DAY;
    }

#if ENABLE_ATSC
    u32TotalSeconds -=  (DEFAULT_DAY_ATSC-1) *SECONDS_PER_DAY;
#endif

    return u32TotalSeconds;
}
//*************************************************************************
//Function name:    MApp_ConvertSeconds2StTime
//Passing parameter:    U32 u32SystemTime : system time + offset time
//              ST_TIME *pstTime : local date
//Return parameter:     none
//Description:      Calculate local date
//*************************************************************************
/* the base time starts from DEFAULT_YEAR/DEFAULT_MONTH/DEFAULT_DAY DEFAULT_HOUR:DEFAULT_MIN:DEFAULT_SEC*/
void MApp_ConvertSeconds2StTime ( U32 u32SystemTime, ST_TIME *pstTime )
{
    U16 u16TotalDays, u16Days;

    //printf("MApp_ConvertSeconds2StTime(%u)\n", u32SystemTime);

    /* set to base date */
    MApp_SetToDefaultSystemTime( pstTime );

    /* u32SystemTime = total accumulative seconds from base date */
    if (u32SystemTime > 0)
    {
        /* sec */
        pstTime->u8Sec = u32SystemTime % SECONDS_PER_MIN;
        u32SystemTime -= pstTime->u8Sec;

        /* min */
        pstTime->u8Min = ( u32SystemTime / SECONDS_PER_MIN ) % MINS_PER_HOUR;
        u32SystemTime -= pstTime->u8Min * SECONDS_PER_MIN;

        /* hour */
        pstTime->u8Hour = ( u32SystemTime / SECONDS_PER_HOUR ) % HOURS_PER_DAY;
        u32SystemTime -= pstTime->u8Hour * SECONDS_PER_HOUR;

        /* days */
    #if ENABLE_ATSC
        u16TotalDays = u32SystemTime / SECONDS_PER_DAY
                       + (U16)SolarDays[MApp_GetLeap( pstTime->u16Year ) * 14 + pstTime->u8Month - 1]
                       + (U16)pstTime->u8Day - 1;
    #else
        u16TotalDays = u32SystemTime / SECONDS_PER_DAY;
    #endif

        /* year */
        u16Days = MApp_GetDaysOfThisYear( pstTime->u16Year );
        while ( u16TotalDays >= u16Days )
        {
            u16TotalDays -= u16Days;
            pstTime->u16Year++;
            u16Days = MApp_GetDaysOfThisYear( pstTime->u16Year );
        }

        /* month */
        u16Days = MApp_GetDaysOfThisMonth( pstTime->u16Year, pstTime->u8Month );
        while ( u16TotalDays >= u16Days )
        {
            u16TotalDays -= u16Days;
            pstTime->u8Month++;
            u16Days = MApp_GetDaysOfThisMonth( pstTime->u16Year, pstTime->u8Month );
        }

        /* day */
        #if ENABLE_ATSC
        pstTime->u8Day = ( U8 ) u16TotalDays + 1;
        #else
        pstTime->u8Day += ( U8 ) u16TotalDays;
        #endif

    /*
        printf("pstTime->u16Year=%u\n", pstTime->u16Year);
        printf("pstTime->u8Month=%u\n", pstTime->u8Month);
        printf("pstTime->u8Day=%u\n", pstTime->u8Day);

        printf("pstTime->u8Hour=%u\n", pstTime->u8Hour);
        printf("pstTime->u8Min=%u\n", pstTime->u8Min);
        printf("pstTime->u8Sec=%u\n", pstTime->u8Sec);
    */
    }
}

void MApp_Time_PrintTimeAndST_Time(U32 u32Time)
{
    ST_TIME stST_Time;

    MApp_ConvertSeconds2StTime(u32Time, &stST_Time );

    printf("{%u => ", u32Time);

    printf("day=%u, ", stST_Time.u8Day);
    printf("%u:", stST_Time.u8Hour);
    printf("%u:", stST_Time.u8Min);
    printf("%u }", stST_Time.u8Sec);
}

//*************************************************************************
//Function name:    MApp_GetTimeZoneOffset
//Passing parameter:    Time Zone
//Return parameter:     offset time    in seconds
//Description:      Calculate Time Zone offset time in seconds
//*************************************************************************
S32 MApp_GetTimeZoneOffset ( U8 u8TimeZone )
{
    S32 s32TempTime = 0;
#if ENABLE_ATSC
    switch ( u8TimeZone )
    {
        case TIME_ZONE_ATLANTIC:
            u8TimeZone = EN_Clock_TimeZone_16;            break;
        case TIME_ZONE_EASTERN:
            u8TimeZone = EN_Clock_TimeZone_14;            break;
        case TIME_ZONE_CENTRAL:
            u8TimeZone = EN_Clock_TimeZone_12;            break;
        case TIME_ZONE_MOUNTAIN:
            u8TimeZone = EN_Clock_TimeZone_10;            break;
        case TIME_ZONE_PACIFIC:
            u8TimeZone = EN_Clock_TimeZone_8;            break;
        case TIME_ZONE_ALASKA:
            u8TimeZone = EN_Clock_TimeZone_6;            break;
        case TIME_ZONE_HAWAII:
            u8TimeZone = EN_Clock_TimeZone_4;            break;
        default:
            u8TimeZone = u8TimeZone;            break;
    }

    //if( stGenSetting.g_SysSetting.fTimeDST )
    if( (stGenSetting.g_SysSetting.fTimeAutoSync)
     && (stGenSetting.g_SysSetting.fTimeDSTStatusControl) )
        u8TimeZone+=2; // one hour
#endif

    s32TempTime = (u8TimeZone - (S32)EN_Clock_TimeZone_24) * SECONDS_PER_HALF_HOUR;
    return s32TempTime;
}

U8 MApp_CalSummerTimeOffset(U8 *L_MJDUTC)
{
#if 1
        L_MJDUTC=L_MJDUTC;
        return 0;
#else
    U32            MJD;
    U8            WD;    // Day of week from Monday (=1) to Sunday (=7)
    U8            First_DST_Transition;    // Before = 0, After = 1;
    U8            Second_DST_Transition;    // Before = 0, After = 1;
    U8            summer_time_offset;

    if ( IS_DTG_COUNTRY(OSD_COUNTRY_SETTING) )//disable for DTG test
        return 0;
    First_DST_Transition = 0;    // Before = 0, After = 1;
    Second_DST_Transition = 0;    // Before = 0, After = 1;



    MJD = GET_3BYTE(L_MJDUTC);
    WD = ((MJD+2)%7) + 1;

    // First DST Transition
    if(stDate.u8Month >= 4)
    {
        First_DST_Transition = 1;
    }
    else if( (stDate.u8Month==3) &&
            (((stDate.u8Day==26)&&(WD==1))            || ((stDate.u8Day==27)&&(WD>=1)&&(WD<=2)) ||
             ((stDate.u8Day==28)&&(WD>=1)&&(WD<=3)) || ((stDate.u8Day==29)&&(WD>=1)&&(WD<=4)) ||
             ((stDate.u8Day==30)&&(WD>=1)&&(WD<=5)) || ((stDate.u8Day==31)&&(WD>=1)&&(WD<=6))) )
    {
        First_DST_Transition = 1;
    }
    else if( (stDate.u8Month==3) &&
            (((stDate.u8Day>=25)&&(stDate.u8Day<=31)) && (WD==7) && (stDate.u8Hour!=0)) )
    {
        First_DST_Transition = 1;
    }

    // Second DST Transition
    if(stDate.u8Month >= 11)
    {
        Second_DST_Transition= 1;
    }
    else if( (stDate.u8Month==10) &&
            (((stDate.u8Day==26)&&(WD==1))            || ((stDate.u8Day==27)&&(WD>=1)&&(WD<=2)) ||
             ((stDate.u8Day==28)&&(WD>=1)&&(WD<=3)) || ((stDate.u8Day==29)&&(WD>=1)&&(WD<=4)) ||
             ((stDate.u8Day==30)&&(WD>=1)&&(WD<=5)) || ((stDate.u8Day==31)&&(WD>=1)&&(WD<=6))) )
    {
        Second_DST_Transition = 1;
    }
    else if( (stDate.u8Month==10) &&
            (((stDate.u8Day>=25)&&(stDate.u8Day<=31)) && (WD==7) && (stDate.u8Hour!=0)) )
    {
        Second_DST_Transition = 1;
    }

    // Summer Time Setting
    if((First_DST_Transition == 1) && (Second_DST_Transition == 0))
    {
        //dbgprint("^y^ Summer~ ^^");
        summer_time_offset = 1;    // 1 Hour
    }
    else
    {
        //dbgprint("^y^ Winter~ ^^");
        summer_time_offset = 0;
    }
    return summer_time_offset;
#endif
}

void MApp_CalDefaultTimeOffest(void)
{
#if ENABLE_DTV
    U8 au8UTCTime[5];
#endif
    U8 summerTimeOffset =0;
    S32 s32TempTime = 0;


    msAPI_Timer_SetOffsetTime(0);
    msAPI_Timer_SetTimeOfChange(0);
    msAPI_Timer_SetNextTimeOffset(0);
#if ENABLE_DTV
    MApp_SI_Get_UTCTime(au8UTCTime);
    summerTimeOffset = MApp_CalSummerTimeOffset(au8UTCTime);
#endif
    s32TempTime = MApp_GetTimeZoneOffset(stGenSetting.g_Time.en_Clock_TimeZone);
    s32TempTime += summerTimeOffset*SECONDS_PER_HOUR;
    msAPI_Timer_SetOffsetTime(s32TempTime);
}
//*************************************************************************
//Function name:        MApp_GetLocalSystemTime
//Passing parameter:    None
//Return parameter:     Local system time in seconds
//Description:          Calculate local system time in seconds
//*************************************************************************
U32 MApp_GetLocalSystemTime(void)
{
    U32 u32SystemTime = msAPI_Timer_GetSystemTime();
    U32 u32OffsetTime = msAPI_Timer_GetOffsetTime();

    DEBUG_WAKE_UP( printf("\e[31;1m SystemTime   : %u \33[m \n", u32SystemTime) );
    DEBUG_WAKE_UP( printf("\e[31;1m OffsetTime   : %u \33[m \n\n", u32OffsetTime) );

    return ( u32SystemTime + u32OffsetTime);
}

//*************************************************************************
//Function name:        MApp_SetLocalSystemTime
//Passing parameter:    Local system time in seconds
//Return parameter:     System time w/o time zone, day light saving offset
//Description:          Calculate local system time in seconds
//*************************************************************************
void MApp_SetLocalSystemTime (U32 u32LocalSystemTime)
{
    DEBUG_WAKE_UP( printf("MApp_SetLocalSystemTime(%u)\n", u32LocalSystemTime) );

    msAPI_Timer_SetSystemTime(u32LocalSystemTime -  msAPI_Timer_GetOffsetTime());
}
//*************************************************************************
//Function name:        MApp_GetLocalWakeUpTime
//Passing parameter:    None
//Return parameter:     Local WakeUp time in seconds
//Description:          Calculate local WakeUp time in seconds
//*************************************************************************
U32 MApp_GetLocalWakeUpTime (void)
{
    U32 u32LocalWakeUpTime = msAPI_Timer_GetWakeupTime() + msAPI_Timer_GetOffsetTime();

    //DEBUG_WAKE_UP( printf("MApp_GetLocalWakeUpTime => %u\n", u32LocalWakeUpTime) );

    return u32LocalWakeUpTime;
}
//*************************************************************************
//Function name:        MApp_SetLocalWakeUpTime
//Passing parameter:    Local WakeUp time in seconds
//Return parameter:     WakeUp time w/o time zone, day light saving offset
//Description:          Calculate local WakeUp time in seconds
//*************************************************************************
void MApp_SetLocalWakeUpTime (U32 u32LocalWakeUpTime)
{
    DEBUG_WAKE_UP( printf("MApp_SetLocalWakeUpTime(u32LocalWakeUpTime=%u)\n", u32LocalWakeUpTime); );
    DEBUG_WAKE_UP( printf("msAPI_Timer_GetOffsetTime()=%u)\n", msAPI_Timer_GetOffsetTime()); );

    //C51
    msAPI_Timer_SetWakeupTime(u32LocalWakeUpTime - msAPI_Timer_GetOffsetTime());
    //RTC
    msAPI_Timer_SetRTCWakeUpTime(u32LocalWakeUpTime - msAPI_Timer_GetOffsetTime());
}

//*************************************************************************
//Function name:    MApp_IsSrcHasSignal
//Passing parameter: eWindow - MAIN_WINDOW, SUB_WINDOW
//Return parameter:
//Description:
//*************************************************************************
BOOLEAN MApp_IsSrcHasSignal(SCALER_WIN eWindow)
{
    INPUT_SOURCE_TYPE_t eInputSourceType = SYS_INPUT_SOURCE_TYPE(eWindow);

#if(ENABLE_TEST_PATTERN)
    if( msAPI_TestPattern_Get_Status() )
    {
        return TRUE;
    }
#endif

    if( IsSrcTypeAnalog(eInputSourceType)
      ||IsSrcTypeHDMI(eInputSourceType)
      ||IsSrcTypeDVI(eInputSourceType)
      )
    {
        if( MApp_PCMode_GetCurrentState(eWindow) == E_PCMODE_STABLE_SUPPORT_MODE) //(g_bInputTimingChange || (g_bUnsupportMode)|| MApp_IsSyncLossFlag())
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#if( ENABLE_DTV )
    else if ( IsSrcTypeDTV(eInputSourceType) )
    {
        VDEC_DispInfo vidStatus;
        if( msAPI_VID_GetVidInfo(&vidStatus) )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#endif
#if ENABLE_DMP
    else if (IsSrcTypeStorage(eInputSourceType))
    {
        return TRUE;
    }
#endif
    else // Digital port: ATV/AV
    {
        if( IsVDHasSignal() )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }

    return TRUE;
}

/*=========================================================================
    FUNCTION    : MApp_ResetTimeLog()
                  MApp_UpdateTimeLog()
    DESCRIPTION : Reset/Update/Dump Channel Change Time Log
=========================================================================*/
/*ZUI_TODO:
void MApp_ResetTimeLog(void)
{
    g_TimeLog.tl_numLogs = 0;
    return;
}

void MApp_UpdateTimeLog(U8 u8TimeLogIndex)
{
    U8 i=0;
    int    nLogs = g_TimeLog.tl_numLogs;

    if (nLogs < 16)
    {
        g_TimeLog.tl_index[nLogs] = u8TimeLogIndex;
        g_TimeLog.tl_time [nLogs] = msAPI_Timer_GetTime0();
        g_TimeLog.tl_numLogs++;
    }
    return;
}

void MApp_DumpTimeLog(void)
{
#if 0    // disable code because of bank size overflow, don't delete
    U8     i, nLogs = g_TimeLog.tl_numLogs;
    U32    firstTicks, prevTicks;

    if (nLogs > 0)
    {
        firstTicks = g_TimeLog.tl_time[0];
        prevTicks  = g_TimeLog.tl_time[0];
        printf("  Num, Index  ,timeStamp,  Delta1,  Delta2\n");
        for (i = 0; i < nLogs; i++)
        {
            printf("  %bu,  %bu,  %9.3f, %6.3f, %6.3f\n", i,
                        g_TimeLog.tl_index[i],
                        (g_TimeLog.tl_time[i]             )/1000.0,
                        (g_TimeLog.tl_time[i] - prevTicks )/1000.0,
                        (g_TimeLog.tl_time[i] - firstTicks)/1000.0);
            prevTicks = g_TimeLog.tl_time[i];
        }
    }
    else
    {
        printf("No Time Log Present\n");
    }
#endif

    return;
}
*/

U32 MApp_UTC2Seconds(U8 *pau8TDTData)
{
    U32 u32TotalSeconds = 0;

    _stDate.u8Hour = BCD2Dec(pau8TDTData[0]);
    _stDate.u8Min  = BCD2Dec(pau8TDTData[1]);
    _stDate.u8Sec  = BCD2Dec(pau8TDTData[2]);

    //printf("\n %bu %bu %bu\n",pau8TDTData[0],pau8TDTData[1],pau8TDTData[2]);
    /* sec */
    u32TotalSeconds += _stDate.u8Sec;

    /* min */
    u32TotalSeconds += _stDate.u8Min * SECONDS_PER_MIN;

    /* hour */
    u32TotalSeconds += _stDate.u8Hour * SECONDS_PER_HOUR;

    return u32TotalSeconds;
}

#if 1    // disable code because of bank size overflow, don't delete
void MApp_Seconds2UTC ( U32 u32TotalSeconds, U8 *pau8TDTData )
{
    ST_TIME stDateTmp;

    memset(&stDateTmp, 0x00, sizeof(ST_TIME));
    memset(pau8TDTData, 0x00, 3);

    /* sec */
    stDateTmp.u8Sec  = u32TotalSeconds % SECONDS_PER_MIN;
    u32TotalSeconds -= stDateTmp.u8Sec;

    /* min */
    stDateTmp.u8Min  = ( u32TotalSeconds / SECONDS_PER_MIN ) % MINS_PER_HOUR;
    u32TotalSeconds -= stDateTmp.u8Min * SECONDS_PER_MIN;

    /* hour */
    stDateTmp.u8Hour = u32TotalSeconds / SECONDS_PER_HOUR ;

    pau8TDTData[0] = DEC2BCD(stDateTmp.u8Hour);
    pau8TDTData[1] = DEC2BCD(stDateTmp.u8Min);
    pau8TDTData[2] = DEC2BCD(stDateTmp.u8Sec);
}
#endif

#if 0
U32 MApp_MJD2Sec(U8 *pu8MJD)
{
    U8 YY,MM,K;
    U16 u16MJD;
    U32 u32TotalSeconds;

    u32TotalSeconds = 0;
    u16MJD = pu8MJD[0] << 8 | pu8MJD[1];

    // 2000/1/1 ~ 2100/1/1
    if ((u16MJD > DEFAULT_MJD) && (u16MJD < (DEFAULT_MJD+36500)))
    {
        YY = (U8) ((u16MJD - 15078.2) / 365.25);
        MM = (U8) ((u16MJD - 14956.1 - (YY * 365.25)) / 30.6001);
        K = ((MM == 14) || (MM == 15)) ? 1 : 0;

        stDate.u16Year = (U16) (1900 + YY + K);
        stDate.u8Month = (U8) (MM - 1 - (K * 12));
        stDate.u8Day = (U8) (u16MJD - 14956 - (U16) (YY * 365.25) - (U16) (MM * 30.6001));

        /* day */
        u32TotalSeconds += (stDate.u8Day - 1) * SECONDS_PER_DAY;

        /* month */
        u32TotalSeconds += SolarDays[MApp_GetLeap(stDate.u16Year) * 14 + stDate.u8Month - 1] * SECONDS_PER_DAY;

        /* year */
        while(stDate.u16Year > DEFAULT_YEAR)
        {
            stDate.u16Year--;
            u32TotalSeconds += MApp_GetDaysOfThisYear(stDate.u16Year) * SECONDS_PER_DAY;
        }
    }

    return u32TotalSeconds;
}
#endif

U32 MApp_MJDUTC2Seconds(U8 *pau8TDTData)
{
    U8 YY,MM,K;
    U16 u16MJD;
    U32 u32TotalSeconds;

    u32TotalSeconds = 0;
    u16MJD = pau8TDTData[0] << 8 | pau8TDTData[1];
    if(u16MJD > DEFAULT_MJD)
    {
        YY = (U8) ((u16MJD - 15078.2) / 365.25);
        MM = (U8) ((u16MJD - 14956.1 - (U16)(YY * 365.25)) / 30.6001);
        K = ((MM == 14) || (MM == 15)) ? 1 : 0;

        _stDate.u16Year = (U16) (1900 + YY + K);
        _stDate.u8Month = (U8) (MM - 1 - (K * 12));
        _stDate.u8Day = (U8) (u16MJD - 14956 - (U16) (YY * 365.25) - (U16) (MM * 30.6001));
        _stDate.u8Hour = BCD2Dec(pau8TDTData[2]);
        _stDate.u8Min = BCD2Dec(pau8TDTData[3]);
        _stDate.u8Sec = BCD2Dec(pau8TDTData[4]);

        /* sec */
        u32TotalSeconds += _stDate.u8Sec;

        /* min */
        u32TotalSeconds += _stDate.u8Min * SECONDS_PER_MIN;

        /* hour */
        u32TotalSeconds += _stDate.u8Hour * SECONDS_PER_HOUR;

        /* day */
        u32TotalSeconds += (_stDate.u8Day - 1) * SECONDS_PER_DAY;

        /* month */
        u32TotalSeconds += SolarDays[MApp_GetLeap(_stDate.u16Year) * 14 + _stDate.u8Month - 1] * SECONDS_PER_DAY;

        /* year */
        while(_stDate.u16Year > DEFAULT_YEAR)
        {
            _stDate.u16Year--;
            u32TotalSeconds += MApp_GetDaysOfThisYear(_stDate.u16Year) * SECONDS_PER_DAY;
        }
    }

    return u32TotalSeconds;
}

//Notice: the output array pau8TDTData size should be 5.
void MApp_Seconds2MJDUTC ( U32 u32TotalSeconds, U8 *pau8TDTData )
{
    //Array should be allocated outside.
    if(!pau8TDTData)
        return;

    ST_TIME stTime;
    MApp_ConvertSeconds2StTime(u32TotalSeconds, &stTime);

    // In leap years, -1 for Jan, Feb, else 0
    double L = ceil(((double)stTime.u8Month - 14.0) / 12.0);
    double p1 = (double)stTime.u8Day - 32075.0 + floor(1461.0 * ((double)stTime.u16Year + 4800.0 + L) / 4.0);

    double p2 =  floor(367.0 * ((double)stTime.u8Month - 2.0 - L * 12.0) / 12.0);
    double p3 = 3.0 *  floor(floor(((double)stTime.u16Year + 4900.0 + L) / 100.0) / 4.0);

    double julian = p1 + p2 - p3 - 0.5;
    U16 mjd = (U16)(julian - 2400000.5);

    pau8TDTData[0] = HIGHBYTE(mjd);
    pau8TDTData[1] = LOWBYTE(mjd);
    pau8TDTData[2] = DEC2BCD(stTime.u8Hour);
    pau8TDTData[3] = DEC2BCD(stTime.u8Min);
    pau8TDTData[4] = DEC2BCD(stTime.u8Sec);
}

#if 1//(ENABLE_ARABIC_OSD || ENABLE_THAI_OSD || ENABLE_INDIA_OSD)
BYTE MApp_GetLanguageForFont(void)
{
    U8 lange = MApp_GetMenuLanguage_DTG();

    switch(lange)
    {
        case LANGUAGE_ARABIC:
        //case LANGUAGE_Urdu:
      //  case LANGUAGE_OSD_KURMANJI:
            return LANGUAGE_OSD_ARABIC;

        //case LANGUAGE_SORANI:
            //return LANGUAGE_OSD_SORANI;

        case LANGUAGE_THAI:
            return LANGUAGE_OSD_THAI;

        //case LANGUAGE_Ibo:
            //return LANGUAGE_OSD_Ibo;

        //case LANGUAGE_Yoruban:
          //  return LANGUAGE_OSD_YOR;
#if(ENABLE_MYANMAR_OSD)
        case LANGUAGE_MYANMAR:
            return LANGUAGE_OSD_MYANMAR;
#endif

#if(ENABLE_KHMER_OSD)
        case LANGUAGE_KHMER:
            return LANGUAGE_OSD_KHMER;
#endif

#if(ENABLE_LAO_OSD)
        case LANGUAGE_LAO:
            return LANGUAGE_OSD_LAO;
#endif

#if(ENABLE_UYGHUR_OSD)
        case LANGUAGE_UYGHUR:
            return LANGUAGE_OSD_UYGHUR;
#endif

#if(ENABLE_INDIA_OSD)
        case LANGUAGE_HINDI:
            return LANGUAGE_OSD_HINDI;

        case LANGUAGE_TELUGU:
            return LANGUAGE_OSD_TELUGU;

        case LANGUAGE_TAMIL:
            return LANGUAGE_OSD_TAMIL;

        case LANGUAGE_MARATHI:
            return LANGUAGE_OSD_MARATHI;

        case LANGUAGE_BENGALI:
            return LANGUAGE_OSD_BENGALI;

        case LANGUAGE_KURDISH:
           return LANGUAGE_OSD_KURDISH;

       // case LANGUAGE_GUJARATI:
        //    return LANGUAGE_OSD_GUJARATI;

        case LANGUAGE_KANNADA:
            return LANGUAGE_OSD_KANNADA;

        case LANGUAGE_MALAYALAM:
            return LANGUAGE_OSD_MALAYALAM;

          //case LANGUAGE_OSD_KURMANJI:
              //return LANGUAGE_KURMANJI;
#endif
        default:
            return LANGUAGE_OSD_UNKNOWN;
    }
}
#endif

EN_OSD_COUNTRY_SETTING MApp_GetOSDCountrySetting(void)
{
#ifdef ROM_FILE
    m_eOSDCountrySetting = OSD_COUNTRY_UK;
    return m_eOSDCountrySetting;
#else
    return m_eOSDCountrySetting;
#endif
}

#if(DVBC_CERTIFICATION_AUTOSCAN_ENABLE)
EN_OSD_CERTIFICATION_SETTING MApp_GetOSDCertificattionSetting(void)
{
    return m_eOSDCertificationSetting;
}

EN_OSD_UNITYMEDIA_COUNTRY_SETTING MApp_GetOSDUnityMediaCountrySetting(void)
{
    return m_eOSDUnityMediaCountrySetting;
}

EN_OSD_ZIGGO_COUNTRY_SETTING MApp_GetOSDZiggoCountrySetting(void)
{
    return m_eOSDZiggoCountrySetting;
}


void MApp_SetOSDCertificationSetting(EN_OSD_CERTIFICATION_SETTING eOSDCertificattionSetting, BOOLEAN bSave)
{
    if(bSave)
    {
        m_eOSDCertificationSetting = eOSDCertificattionSetting;
    }
}
void MApp_SetOSDUnityMediaCountrySetting(EN_OSD_UNITYMEDIA_COUNTRY_SETTING eOSDUnityMediaCountrySetting, BOOLEAN bSave)
{
    if(bSave)
    {
        m_eOSDUnityMediaCountrySetting = eOSDUnityMediaCountrySetting;
    }
}

void MApp_SetOSDZiggoCountrySetting(EN_OSD_ZIGGO_COUNTRY_SETTING eOSDZiggoCountrySetting, BOOLEAN bSave)
{
    if(bSave)
    {
        m_eOSDZiggoCountrySetting = eOSDZiggoCountrySetting;
    }
}

#endif

void MApp_SetSubtAndAudioByCountry(EN_OSD_COUNTRY_SETTING eOSDCountrySetting)
{
    switch(eOSDCountrySetting)
    {
        case OSD_COUNTRY_AUSTRALIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ENGLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_AUSTRIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_GERMAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_GERMAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_BELGIUM:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_GERMAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_FRENCH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_GERMAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_FRENCH;
        }
        break;
        case OSD_COUNTRY_BULGARIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_BULGARIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_BULGARIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_CROATIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_CROATIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_CROATIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_CZECH:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_CZECH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_CZECH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_DENMARK:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_DANISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_DANISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_FINLAND:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_FINNISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_SWEDISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_FINNISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_SWEDISH;
        }
        break;
        case OSD_COUNTRY_FRANCE:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_FRENCH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_FRENCH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_GERMANY:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_GERMAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_GERMAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_GREECE:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_GREEK;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_GREEK;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_HUNGARY:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_HUNGARIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_HUNGARIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_ITALY:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ITALIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ITALIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_LUXEMBOURG:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_GERMAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_FRENCH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_GERMAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_FRENCH;
        }
        break;
        case OSD_COUNTRY_NETHERLANDS:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_DUTCH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_DUTCH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_NORWAY:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_NORWEGIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_NORWEGIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_POLAND:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_POLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_POLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_PORTUGAL:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_PORTUGUESE;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_PORTUGUESE;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_ROMANIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ROMANIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ROMANIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_RUSSIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_RUSSIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_RUSSIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_SERBIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_SERBIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_SERBIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_SLOVENIA:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_SLOVENIAN;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_SLOVENIAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_SPAIN:
         {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_SPANISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_SPANISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_SWEDEN:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_SWEDISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
#if ENABLE_SUBTITLE_SWITCH_MENU
            MENU_OPTION_SUBTITLE_ON = TRUE;
#else
            stGenSetting.g_SysSetting.fEnableSubTitle = TRUE;
#endif
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_SWEDISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_SWITZERLAND:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_FRENCH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_GERMAN;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_FRENCH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_GERMAN;
        }
        break;
        case OSD_COUNTRY_UK:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ENGLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_NEWZEALAND:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ENGLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_MAORI;
        }
        break;
        case OSD_COUNTRY_MOROCCO:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ARABIC;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ARABIC;
        }
        break;
        case OSD_COUNTRY_TUNIS:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ARABIC;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ARABIC;
        }
        break;
        case OSD_COUNTRY_ALGERIA:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ARABIC;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ARABIC;
        }
        break;
        case OSD_COUNTRY_EGYPT:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ARABIC;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ARABIC;
        }
        break;
        case OSD_COUNTRY_SOUTH_AFRICA:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ENGLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_ISRAEL:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_HEBREW;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_HEBREW;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_HEBREW;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_HEBREW;
        }
        break;
        case OSD_COUNTRY_IRAN:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_PARSI;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_PARSI;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_PARSI;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_PARSI;
        }
        break;
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:
        case OSD_COUNTRY_KUWAIT:
        case OSD_COUNTRY_OMAN:
        case OSD_COUNTRY_QATAR:
        case OSD_COUNTRY_SAUDI_ARABIA:
        case OSD_COUNTRY_BAHRAIN:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ARABIC;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ARABIC;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ARABIC;
        }
        break;
        case OSD_COUNTRY_SLOVAKIA:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_SLOVAK;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_SLOVAK;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;
        case OSD_COUNTRY_IRELAND:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ENGLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_IRISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_IRISH;
        }
        break;
        default:
        {
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage = LANGUAGE_ENGLISH;
            stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2= LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = LANGUAGE_ENGLISH;
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = LANGUAGE_ENGLISH;
        }
        break;

    }
}

#if ENABLE_DVB
static EN_MENU_TIMEZONE MApp_GetTimeZoneBySITimeZone(EN_SI_TIMEZONE eTimeZone)
{
    switch(eTimeZone)
    {
        case SI_TIMEZONE_CANARY:    return TIMEZONE_CANARY;
        case SI_TIMEZONE_LISBON:    return TIMEZONE_LISBON;
        case SI_TIMEZONE_LONDON:    return TIMEZONE_LONDON;
        case SI_TIMEZONE_RABAT:     return TIMEZONE_RABAT;
        case SI_TIMEZONE_AMSTERDAM:    return TIMEZONE_AMSTERDAM;
        case SI_TIMEZONE_BEOGRAD:    return TIMEZONE_BEOGRAD;
        case SI_TIMEZONE_BERLIN:    return TIMEZONE_BERLIN;
        case SI_TIMEZONE_BRUSSELS:    return TIMEZONE_BRUSSELS;
        case SI_TIMEZONE_BUDAPEST:    return TIMEZONE_BUDAPEST;
        case SI_TIMEZONE_COPENHAGEN:    return TIMEZONE_COPENHAGEN;
        case SI_TIMEZONE_LIUBLJANA:    return TIMEZONE_LIUBLJANA;
        case SI_TIMEZONE_LUXEMBOURG:    return TIMEZONE_LUXEMBOURG;
        case SI_TIMEZONE_MADRID:    return TIMEZONE_MADRID;
        case SI_TIMEZONE_OSLO:    return TIMEZONE_OSLO;
        case SI_TIMEZONE_PARIS:    return TIMEZONE_PARIS;
        case SI_TIMEZONE_PRAGUE:    return TIMEZONE_PRAGUE;
        case SI_TIMEZONE_BRATISLAVA:return TIMEZONE_BRATISLAVA;
        case SI_TIMEZONE_BERN:       return TIMEZONE_BERN;
        case SI_TIMEZONE_ROME:    return TIMEZONE_ROME;
        case SI_TIMEZONE_STOCKHOLM:    return TIMEZONE_STOCKHOLM;
        case SI_TIMEZONE_WARSAW:    return TIMEZONE_WARSAW;
        case SI_TIMEZONE_VIENNA:    return TIMEZONE_VIENNA;
        case SI_TIMEZONE_ZAGREB:    return TIMEZONE_ZAGREB;
        case SI_TIMEZONE_TUNIS:    return TIMEZONE_TUNIS;
        case SI_TIMEZONE_ALGIERS:    return TIMEZONE_ALGIERS;
        case SI_TIMEZONE_ATHENS:    return TIMEZONE_ATHENS;
        case SI_TIMEZONE_BUCURESTI:    return TIMEZONE_BUCURESTI;
        case SI_TIMEZONE_HELSINKI:    return TIMEZONE_HELSINKI;
        case SI_TIMEZONE_SOFIA:    return TIMEZONE_SOFIA;
        case SI_TIMEZONE_CAIRO:    return TIMEZONE_CAIRO;
        case SI_TIMEZONE_CAPE_TOWN:    return TIMEZONE_CAPE_TOWN;
        //case SI_TIMEZONE_ESTONIA:      return TIMEZONE_ESTONIA;
        case SI_TIMEZONE_TURKEY:      return TIMEZONE_TURKEY;
        case SI_TIMEZONE_JERUSSLEM:    return TIMEZONE_JERUSSLEM;
        case SI_TIMEZONE_MOSCOW:    return TIMEZONE_MOSCOW;
        case SI_TIMEZONE_TEHERAN:    return TIMEZONE_TEHERAN;
        case SI_TIMEZONE_ABU_DHABI:    return TIMEZONE_ABU_DHABI;
        case SI_TIMEZONE_KUWAIT:    return TIMEZONE_KUWAIT;
        case SI_TIMEZONE_MUSCAT:    return TIMEZONE_MUSCAT;
        case SI_TIMEZONE_DOHA:    return TIMEZONE_DOHA;
        case SI_TIMEZONE_RIYADH:    return TIMEZONE_RIYADH;
        case SI_TIMEZONE_MANAMA:    return TIMEZONE_MANAMA;
        case SI_TIMEZONE_BEIJING:    return TIMEZONE_BEIJING;
        case SI_TIMEZONE_WA:    return TIMEZONE_WA;
        case SI_TIMEZONE_SA:    return TIMEZONE_SA;
        case SI_TIMEZONE_NT:    return TIMEZONE_NT;
        case SI_TIMEZONE_NSW:    return TIMEZONE_NSW;
        case SI_TIMEZONE_VIC:    return TIMEZONE_VIC;
        case SI_TIMEZONE_QLD:    return TIMEZONE_QLD;
        case SI_TIMEZONE_TAS:    return TIMEZONE_TAS;
        case SI_TIMEZONE_NZST:    return TIMEZONE_NZST;
#if 1 //ENABLE_SBTVD_DTV_SYSTEM
        case SI_TIMEZONE_AM_WEST:    return TIMEZONE_AM_WEST;
        case SI_TIMEZONE_ACRE:    return TIMEZONE_ACRE;
        case SI_TIMEZONE_M_GROSSO:    return TIMEZONE_M_GROSSO;
        case SI_TIMEZONE_NORTH:    return TIMEZONE_NORTH;
        case SI_TIMEZONE_BRASILIA:    return TIMEZONE_BRASILIA;
        case SI_TIMEZONE_NORTHEAST:    return TIMEZONE_NORTHEAST;
        case SI_TIMEZONE_F_NORONHA:    return TIMEZONE_F_NORONHA;
#endif
        case SI_TIMEZONE_AZORES:    return TIMEZONE_AZORES;

        case SI_TIMEZONE_SINGAPORE:         return TIMEZONE_SINGAPORE;
        case SI_TIMEZONE_KUALA_LUMPUR:      return TIMEZONE_KUALA_LUMPUR;
        case SI_TIMEZONE_HCMC:              return TIMEZONE_HCMC;
        case SI_TIMEZONE_BANGKOK:           return TIMEZONE_BANGKOK;
        case SI_TIMEZONE_INDONESIA_WEST:    return TIMEZONE_INDONESIA_WEST;
        case SI_TIMEZONE_INDONESIA_CENTER:  return TIMEZONE_INDONESIA_CENTER;
        case SI_TIMEZONE_INDONESIA_EAST:    return TIMEZONE_INDONESIA_EAST;
        case SI_TIMEZONE_THAILAND:          return TIMEZONE_THAILAND;
        case SI_TIMEZONE_VIETNAM:           return TIMEZONE_VIETNAM;
        case SI_TIMEZONE_KENYA:             return TIMEZONE_KENYA;
        case SI_TIMEZONE_MYANMAR:           return TIMEZONE_MYANMAR;
        //case SI_TIMEZONE_DUBLIN:    return TIMEZONE_DUBLIN;
        case SI_TIMEZONE_NUM:    return TIMEZONE_NUM;
        default:
        ASSERT(0);
        return TIMEZONE_LONDON;
    }
}

#else
static EN_MENU_TIMEZONE MApp_GetTimeZoneByCountry(EN_OSD_COUNTRY_SETTING eCountry)
{
    U8 u8Loop;

    //printf("Total = %bu\n",sizeof(stTimeZone2Country)/sizeof(TimeZone2Country));
    for(u8Loop = 0; u8Loop < sizeof(stTimeZone2Country)/sizeof(TimeZone2Country); u8Loop++)
    {
        if(stTimeZone2Country[u8Loop].eCountry == eCountry)
            return stTimeZone2Country[u8Loop].eTimeZone;
    }
    return TIMEZONE_LONDON; // Unknow timezone, return UK.
}
#endif

static void _MApp_SetOSDCountrySetting(EN_OSD_COUNTRY_SETTING eOSDCountrySetting, BOOLEAN bSave)
{
    m_eOSDCountrySetting = eOSDCountrySetting;

    if(bSave)//
    {
    #if ENABLE_DVB
        msAPI_CM_SetCountry((MEMBER_COUNTRY) eOSDCountrySetting);
        stGenSetting.g_Time.enTimeZone = MApp_GetTimeZoneBySITimeZone(msAPI_SI_GetTimeZoneByCountry(MApp_GetSICountry(OSD_COUNTRY_SETTING)));
    #else
        stGenSetting.g_Time.enTimeZone = MApp_GetTimeZoneByCountry(OSD_COUNTRY_SETTING);
    #endif

        MApp_SetTimeZone(stGenSetting.g_Time.enTimeZone);

        if( OSD_COUNTRY_SETTING == OSD_COUNTRY_FRANCE)
        {
             stGenSetting.stScanMenuSetting.u8LSystem=TRUE;
        }
        else
        {
             stGenSetting.stScanMenuSetting.u8LSystem=FALSE;
        }

        MApp_SetSubtAndAudioByCountry(eOSDCountrySetting);

  #if ENABLE_DTV
        if(IS_NORDIC_COUNTRY(OSD_COUNTRY_SETTING))
        {
    #if ENABLE_SUBTITLE_SWITCH_MENU
            MENU_OPTION_SUBTITLE_ON = 1;
    #else
            stGenSetting.g_SysSetting.fEnableSubTitle = 1;
            stGenSetting.g_SysSetting.fEnableTTXSubTitle = 1;
    #endif
        }
        else
  #endif
        {
    #if ENABLE_SUBTITLE_SWITCH_MENU
            MENU_OPTION_SUBTITLE_ON = 0;
    #else
            stGenSetting.g_SysSetting.fEnableSubTitle = 0;
            stGenSetting.g_SysSetting.fEnableTTXSubTitle = 0;
    #endif
        }

  #if(!BLOADER)
        MApp_SaveSysSetting();
        MApp_SaveSoundSetting();
        MApp_SaveTimeData();
  #endif
    }

  #if ENABLE_TTX
    MApp_TTX_SetCountry((MEMBER_COUNTRY) eOSDCountrySetting);
  #endif

  #if ENABLE_DVB
    MApp_SI_SetTimeZone(MApp_GetSITimeZone(stGenSetting.g_Time.enTimeZone));
    MApp_SI_SetClockTimeZone(MApp_GetSIClockTimeZone(stGenSetting.g_Time.en_Clock_TimeZone));
    stGenSetting.g_Time.en_ClockMode = EN_ClockMode_Auto;
  #endif

  #if ENABLE_DVB
    if ( IS_COUNTRY_SUPPORT_LCN(OSD_COUNTRY_SETTING) )
    {
        fEnableLCN = TRUE;
    }
    else
  #endif
    {
        fEnableLCN = FALSE;

      #if ENABLE_DVBC
        if (IsDVBCInUse() && OSD_COUNTRY_SETTING == OSD_COUNTRY_GERMANY)
            fEnableLCN = TRUE;
      #endif
    }

  #if ENABLE_DVB
    if( OSD_COUNTRY_SETTING == OSD_COUNTRY_NORWAY )
    {
        msAPI_DFT_SetBandwidth(stGenSetting.stScanMenuSetting.u8BandWidth);
    }
    //MApp_SI_ResetNetwork();
  #endif
}


#if ENABLE_DTV
EN_SI_COUNTRY_SETTING MApp_GetSICountry(EN_OSD_COUNTRY_SETTING eOSDCountrySetting)
{
    EN_SI_COUNTRY_SETTING eSICountry=SI_COUNTRY_UK;
    switch(eOSDCountrySetting)
    {
        case OSD_COUNTRY_AUSTRALIA:       eSICountry = SI_COUNTRY_AUSTRALIA; break;
        case OSD_COUNTRY_AUSTRIA:            eSICountry= SI_COUNTRY_AUSTRIA; break;
        case OSD_COUNTRY_BELGIUM:            eSICountry= SI_COUNTRY_BELGIUM; break;
        case OSD_COUNTRY_BULGARIA:        eSICountry= SI_COUNTRY_BULGARIA; break;
        case OSD_COUNTRY_CROATIA:            eSICountry= SI_COUNTRY_CROATIA; break;
        case OSD_COUNTRY_CZECH:            eSICountry= SI_COUNTRY_CZECH; break;
        case OSD_COUNTRY_DENMARK:            eSICountry= SI_COUNTRY_DENMARK; break;
        case OSD_COUNTRY_FINLAND:            eSICountry= SI_COUNTRY_FINLAND; break;
        case OSD_COUNTRY_FRANCE:            eSICountry= SI_COUNTRY_FRANCE; break;
        case OSD_COUNTRY_GERMANY:            eSICountry= SI_COUNTRY_GERMANY; break;
        case OSD_COUNTRY_GREECE:            eSICountry= SI_COUNTRY_GREECE; break;
        case OSD_COUNTRY_HUNGARY:            eSICountry= SI_COUNTRY_HUNGARY; break;
        case OSD_COUNTRY_ITALY:        eSICountry= SI_COUNTRY_ITALY; break;
        case OSD_COUNTRY_IRELAND:            eSICountry= SI_COUNTRY_IRELAND; break;
        case OSD_COUNTRY_LUXEMBOURG:        eSICountry= SI_COUNTRY_LUXEMBOURG; break;
        case OSD_COUNTRY_NETHERLANDS:        eSICountry= SI_COUNTRY_NETHERLANDS; break;
        case OSD_COUNTRY_NORWAY:            eSICountry= SI_COUNTRY_NORWAY; break;
        case OSD_COUNTRY_POLAND:            eSICountry= SI_COUNTRY_POLAND; break;
        case OSD_COUNTRY_PORTUGAL:        eSICountry= SI_COUNTRY_PORTUGAL; break;
        case OSD_COUNTRY_ROMANIA:            eSICountry= SI_COUNTRY_ROMANIA; break;
        case OSD_COUNTRY_RUSSIA:            eSICountry= SI_COUNTRY_RUSSIA; break;
        case OSD_COUNTRY_SERBIA:            eSICountry= SI_COUNTRY_SERBIA; break;
        case OSD_COUNTRY_SLOVENIA:        eSICountry= SI_COUNTRY_SLOVENIA; break;
        case OSD_COUNTRY_SPAIN:            eSICountry= SI_COUNTRY_SPAIN; break;
        case OSD_COUNTRY_SWEDEN:            eSICountry= SI_COUNTRY_SWEDEN; break;
        case OSD_COUNTRY_SWITZERLAND:        eSICountry= SI_COUNTRY_SWITZERLAND; break;
        case OSD_COUNTRY_UK:             eSICountry = SI_COUNTRY_UK; break;
        case OSD_COUNTRY_NEWZEALAND:             eSICountry = SI_COUNTRY_NEWZEALAND; break;
        case OSD_COUNTRY_CHINA:           eSICountry= SI_COUNTRY_CHINA; break;
        case OSD_COUNTRY_MOROCCO:            eSICountry = SI_COUNTRY_MOROCCO; break;
        case OSD_COUNTRY_TUNIS:              eSICountry = SI_COUNTRY_TUNIS; break;
        case OSD_COUNTRY_ALGERIA:            eSICountry = SI_COUNTRY_ALGERIA; break;
        case OSD_COUNTRY_EGYPT:              eSICountry = SI_COUNTRY_EGYPT; break;
        case OSD_COUNTRY_SOUTH_AFRICA:       eSICountry = SI_COUNTRY_SOUTH_AFRICA; break;
        case OSD_COUNTRY_ISRAEL:             eSICountry = SI_COUNTRY_ISRAEL; break;
        case OSD_COUNTRY_IRAN:               eSICountry = SI_COUNTRY_IRAN; break;
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:   eSICountry = SI_COUNTRY_UNITED_ARAB_EMIRATES; break;
        case OSD_COUNTRY_KUWAIT:             eSICountry = SI_COUNTRY_KUWAIT;         break;
        case OSD_COUNTRY_OMAN:               eSICountry = SI_COUNTRY_OMAN;           break;
        case OSD_COUNTRY_QATAR:              eSICountry = SI_COUNTRY_QATAR;          break;
        case OSD_COUNTRY_SAUDI_ARABIA:       eSICountry = SI_COUNTRY_SAUDI_ARABIA;   break;
        case OSD_COUNTRY_BAHRAIN:            eSICountry = SI_COUNTRY_BAHRAIN;        break;
        case OSD_COUNTRY_SLOVAKIA:                eSICountry= SI_COUNTRY_SLOVAKIA;             break;
        #if (ENABLE_DVB_TAIWAN_APP)
        case OSD_COUNTRY_TAIWAN:          eSICountry= SI_COUNTRY_TAIWAN; break;
        #endif
        case OSD_COUNTRY_BRAZIL:          eSICountry= SI_COUNTRY_BRAZIL; break;
        case OSD_COUNTRY_ESTONIA:           eSICountry = SI_COUNTRY_ESTONIA; break;
        case OSD_COUNTRY_TURKEY:           eSICountry = SI_COUNTRY_TURKEY; break;
        case OSD_COUNTRY_MALAYSIA:         eSICountry = SI_COUNTRY_MALAYSIA; break;
        case OSD_COUNTRY_THAILAND:          eSICountry = SI_COUNTRY_THAILAND; break;
        case OSD_COUNTRY_INDONESIA:        eSICountry = SI_COUNTRY_INDONESIA; break;
        case OSD_COUNTRY_GHANA:            eSICountry = SI_COUNTRY_GHANA; break;
        case OSD_COUNTRY_SINGAPORE:         eSICountry = SI_COUNTRY_SINGAPORE;  break;
        case OSD_COUNTRY_VIETNAM:         eSICountry = SI_COUNTRY_VIETNAM;  break;
        case OSD_COUNTRY_KENYA:         eSICountry = SI_COUNTRY_KENYA;  break;
        case OSD_COUNTRY_MYANMAR:         eSICountry = SI_COUNTRY_MYANMAR;  break;

        default:
        ASSERT(0);
        break;
    }
    return eSICountry;
}
#endif

void MApp_SetOSDCountrySetting(EN_OSD_COUNTRY_SETTING eOSDCountrySetting, BOOLEAN bSave)
{
    _MApp_SetOSDCountrySetting(eOSDCountrySetting, bSave);


  #if(ENABLE_DVB)
    MApp_SetSICountry(eOSDCountrySetting);
    #if (ENABLE_CI && ENABLE_CI_PLUS)
    {
        EN_SI_COUNTRY_SETTING eCountryCodeId;
        U8 u8aCountryCode[MAX_ISO639CODE_LENGTH] = { 0 };

        eCountryCodeId = MApp_GetSICountry(eOSDCountrySetting);
        if (TRUE == msAPI_SI_GetISO3166CountryCodeFromIndex(eCountryCodeId, u8aCountryCode))
        {
            msAPI_CI_HLC_SetCountry(u8aCountryCode);
     }
    }
    #endif
  #endif
}

EN_LANGUAGE MApp_GetMenuLanguage(void)
{
    if (stGenSetting.g_SysSetting.Language > LANGUAGE_MAX)
    {
        MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U16)stGenSetting.g_SysSetting.Language));
        stGenSetting.g_SysSetting.Language = DEFAULT_MENU_LANG;
#if ( ENABLE_ARABIC_OSD || ENABLE_THAI_OSD || ENABLE_INDIA_OSD )
        //msAPI_OSD_SetOSDLanguage((EN_OSDAPI_LANGUAGE)DEFAULT_MENU_LANG);
#endif
    }

    return stGenSetting.g_SysSetting.Language;
}

EN_LANGUAGE MApp_GetMenuLanguage_DTG(void)
{
    if (stGenSetting.g_SysSetting.Language > LANGUAGE_MAX)
    {
        MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U16)stGenSetting.g_SysSetting.Language));
        stGenSetting.g_SysSetting.Language = DEFAULT_MENU_LANG;
#if ( ENABLE_ARABIC_OSD || ENABLE_THAI_OSD || ENABLE_INDIA_OSD )
        //msAPI_OSD_SetOSDLanguage((EN_OSDAPI_LANGUAGE)DEFAULT_MENU_LANG);
#endif
    }
    return stGenSetting.g_SysSetting.Language;
}

EN_MENU_TIMEZONE MApp_GetTimeZone_DTG(void)
{
    if (stGenSetting.g_Time.enTimeZone >= TIMEZONE_NUM)
    {
        MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U16)stGenSetting.g_Time.enTimeZone));

    #if(ENABLE_SBTVD_DTV_SYSTEM)
        if( IS_COUNTRY_USE_SBTVD() )
        {
            stGenSetting.g_Time.enTimeZone = TIMEZONE_GMT_Minus3_START;
        }
        else
    #endif
        {
            stGenSetting.g_Time.enTimeZone = TIMEZONE_GMT_0_START;
        }

    }
    return stGenSetting.g_Time.enTimeZone;
}

EN_LANGUAGE MApp_GetAudioLangMenuLanguage_DTG(void)
{
    if(!stGenSetting.g_SoundSetting.Primary_Flag)
    {
        if (stGenSetting.g_SoundSetting.enSoundAudioLan1 > LANGUAGE_MAX)
        {
            MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U8)stGenSetting.g_SoundSetting.enSoundAudioLan1));
            stGenSetting.g_SoundSetting.enSoundAudioLan1 = DEFAULT_MENU_LANG;
        }
        return (EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan1;
    }
    else
    {
        if (stGenSetting.g_SoundSetting.enSoundAudioLan2 > LANGUAGE_MAX)
        {
            MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U8)stGenSetting.g_SoundSetting.enSoundAudioLan2));
            stGenSetting.g_SoundSetting.enSoundAudioLan2 = DEFAULT_MENU_LANG;
        }
        return (EN_LANGUAGE)stGenSetting.g_SoundSetting.enSoundAudioLan2;
    }
}

EN_LANGUAGE MApp_GetSubLangMenuLanguage_DTG(void)
{
    if(!stGenSetting.g_SysSetting.fSUBLANG_FLAG)
    {
        if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
        {
            if (stGenSetting.g_SysSetting.SubtitleDefaultLanguage > LANGUAGE_SUBTITLE_MAX_NZ)
            {
                MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U8)stGenSetting.g_SysSetting.SubtitleDefaultLanguage));
                stGenSetting.g_SysSetting.SubtitleDefaultLanguage = DEFAULT_SUB_LANG;
            }
        }
        else
        {
            if (stGenSetting.g_SysSetting.SubtitleDefaultLanguage > LANGUAGE_SUBTITLE_MAX_EU)
            {
                MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U8)stGenSetting.g_SysSetting.SubtitleDefaultLanguage));
                stGenSetting.g_SysSetting.SubtitleDefaultLanguage = DEFAULT_SUB_LANG;
            }
        }
        return stGenSetting.g_SysSetting.SubtitleDefaultLanguage;
    }
    else
    {
        if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
        {
            if (stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2 > LANGUAGE_SUBTITLE_MAX_NZ)
            {
                MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U8)stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2));
                stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2 = DEFAULT_SUB_LANG;
            }
        }
        else
        {
            if (stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2 > LANGUAGE_SUBTITLE_MAX_EU)
            {
                MS_DEBUG_MSG(printf("Get Lang Overflow: %u\n", (U8)stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2));
                stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2 = DEFAULT_SUB_LANG;
            }
        }
        return stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2;
    }
}



#if(ENABLE_CEC)
// array of iso 639 language code



static code ST_MENU_LANG_ISO639 MENU_ISO639_LanguageCode[] =
{

        {{'c','z','e'}, LANGUAGE_CZECH},
        {{'d','a','n'}, LANGUAGE_DANISH},
        {{'g','e','r'}, LANGUAGE_GERMAN},
        {{'e','n','g'}, LANGUAGE_ENGLISH},
        {{'s','p','a'}, LANGUAGE_SPANISH},
        {{'e','l','l'}, LANGUAGE_GREEK},
        {{'f','r','a'}, LANGUAGE_FRENCH},
        {{'s','c','r'}, LANGUAGE_CROATIAN},
        {{'i','t','a'}, LANGUAGE_ITALIAN},
        {{'h','u','n'}, LANGUAGE_HUNGARIAN},
        {{'d','u','t'}, LANGUAGE_DUTCH},
        {{'n','o','r'}, LANGUAGE_NORWEGIAN},
        {{'p','o','l'}, LANGUAGE_POLISH},
        {{'p','o','r'}, LANGUAGE_PORTUGUESE},
        {{'r','u','s'}, LANGUAGE_RUSSIAN},
        {{'r','o','n'}, LANGUAGE_ROMANIAN},
        {{'s','l','v'}, LANGUAGE_SLOVENIAN},
        {{'s','c','c'}, LANGUAGE_SERBIAN},
        {{'f','i','n'}, LANGUAGE_FINNISH},
        {{'s','w','e'}, LANGUAGE_SWEDISH},
        {{'b','u','l'}, LANGUAGE_BULGARIAN},
        {{'s','l','o'}, LANGUAGE_SLOVAK},
        {{'i','c','e'}, LANGUAGE_ICELANDIC},
        {{'s','m','i'}, LANGUAGE_SAMI},
#if (ENABLE_DTMB_CHINA_APP          \
                || ENABLE_ATV_CHINA_APP         \
                || ENABLE_DVBC_PLUS_DTMB_CHINA_APP  \
                ||CHINESE_SIMP_FONT_ENABLE      \
                ||ENABLE_DVB_TAIWAN_APP         \
                ||CHINESE_BIG5_FONT_ENABLE)
    #if(ENABLE_COUNTRY_SINGAPORE)
        {{'z','h','o'}, LANGUAGE_CHINESE},
    #endif
        {{'c','h','i'}, LANGUAGE_CHINESE},
#endif
#if((UI_SKIN_SEL != UI_SKIN_960X540X565) && (UI_SKIN_SEL != UI_SKIN_960X540XI8))
        {{'h','c','a'}, LANGUAGE_HINDI},
        {{'u','r','d'}, LANGUAGE_URDU},
        {{'t','e','l'}, LANGUAGE_TELUGU},
        {{'t','a','m'}, LANGUAGE_TAMIL},
        {{'m','a','r'}, LANGUAGE_MARATHI},
        {{'b','e','n'}, LANGUAGE_BENGALI},
        {{'a','s','m'}, LANGUAGE_ASSAMESE},
        {{'g','u','j'}, LANGUAGE_GUJARATI},
        {{'k','a','n'}, LANGUAGE_KANNADA},
        {{'m','a','l'}, LANGUAGE_MALAYALAM},
        {{'p','a','n'}, LANGUAGE_PUNJABI},
#endif

};







BOOL MApp_GetOSDLangCodeFromIndex(EN_LANGUAGE eLanguage, U8 *pBuf)
{
    U8 i, nums;

    nums=sizeof(MENU_ISO639_LanguageCode)/sizeof(ST_MENU_LANG_ISO639);
    for(i=0; i<nums; i++)
    {
        if(MENU_ISO639_LanguageCode[i].enLangIndex == eLanguage)
        {
            memcpy(pBuf,MENU_ISO639_LanguageCode[i].au8LangCode,MAX_ISO639CODE_LENGTH);
            return TRUE;
        }
    }
    return FALSE;
}

#endif

#if(!BLOADER)
void MApp_SetMenuLanguage(EN_LANGUAGE eLanguage)
{
    if (eLanguage > LANGUAGE_MAX)
    {
        MS_DEBUG_MSG(printf("Set Lang Overflow: %u\n", (U16)eLanguage));
        eLanguage = DEFAULT_MENU_LANG;
    }

    stGenSetting.g_SysSetting.Language = eLanguage;

#if ( ENABLE_ARABIC_OSD || ENABLE_THAI_OSD )
  #if (ENABLE_ARABIC_TEST_UI)
    if ( eLanguage == LANGUAGE_SPANISH )
    {
        msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_ARABIC);
        msAPI_OSD_EnterDivxSubtitleMode(TRUE);
    }
    else
  #endif
    {
        msAPI_OSD_SetOSDLanguage(msAPI_OSD_APILanguage2OSDLanguage(eLanguage));
        if(eLanguage == LANGUAGE_ARABIC)
        {
            #if(ENABLE_TTF_FONT)
               msAPI_OSD_EnterDivxSubtitleMode(FALSE);
            #endif
        }
    }
#endif

#if ( ENABLE_TTF_FONT )
    //if ( bFontSysInit )
    {
        switch ( eLanguage )
        {
#if 0
        case LANGUAGE_HINDI:
            {
                switch ( msAPI_OSD_GetOSDLanguage() )
                {
                case LANGUAGE_OSD_HINDI:
                case LANGUAGE_OSD_BENGALI:
                case LANGUAGE_OSD_TELUGU:
                    msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_HINDI);
                    printf("%d Skip reload TTF Font Hindi\n", __LINE__);
                    break;
                default:
                    msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_HINDI);
                    printf("%d Reload TTF Font Hindi\n", __LINE__);
                    MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_HINDI, TRUE);
                    break;
                }
            }
            break;
        case LANGUAGE_URDU:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_URDU )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_URDU);
                printf("%d Reload TTF Font Urdu\n", __LINE__);
                MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_URDU, TRUE);
            }
            break;
        case LANGUAGE_BENGALI:
            {
                switch ( msAPI_OSD_GetOSDLanguage() )
                {
                    case LANGUAGE_OSD_HINDI:
                    case LANGUAGE_OSD_BENGALI:
                    case LANGUAGE_OSD_TELUGU:
                        msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_BENGALI);
                        printf("%d Skip reload TTF Font Bengali\n", __LINE__);
                        break;
                    default:
                        msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_BENGALI);
                        printf("%d Reload TTF Font Bengali\n", __LINE__);
                        MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_HINDI, TRUE);
                        break;
                }
            }
            break;
        case LANGUAGE_TELUGU:
            {
                switch ( msAPI_OSD_GetOSDLanguage() )
                {
                    case LANGUAGE_OSD_HINDI:
                    case LANGUAGE_OSD_BENGALI:
                    case LANGUAGE_OSD_TELUGU:
                        msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_TELUGU);
                        printf("%d Skip reload TTF Font Telugu\n", __LINE__);
                        break;
                    default:
                        msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_TELUGU);
                        printf("%d Reload TTF Font Telugu\n", __LINE__);
                        MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_HINDI, TRUE);
                        break;
                }
            }
            break;
        case LANGUAGE_MARATHI:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_MARATHI )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_MARATHI);
                printf("%d Reload TTF Font Marathi\n", __LINE__);
                MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_MARATHI, TRUE);
            }
            break;
        case LANGUAGE_TAMIL:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_TAMIL )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_TAMIL);
                printf("%d Reload TTF Font Tamil\n", __LINE__);
                MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_TAMIL, TRUE);
            }
            break;
#endif

    #if(ENABLE_MYANMAR_OSD)
        case LANGUAGE_MYANMAR:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_MYANMAR )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_MYANMAR);
                printf("%d Reload TTF Font Myanmar\n", __LINE__);
                MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_MYMR, TRUE);
            }
            break;
    #endif
        case LANGUAGE_UYGHUR:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_UYGHUR )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_UYGHUR);
                //msAPI_OSD_EnterDivxSubtitleMode(TRUE);
            }
            break;
    #if(ENABLE_KHMER_OSD)
        case LANGUAGE_KHMER:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_KHMER )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_KHMER);
                printf("%d Reload TTF Font Khmer\n", __LINE__);
                MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_KHMER, TRUE);
            }
            break;
    #endif
    #if(ENABLE_LAO_OSD)
        case LANGUAGE_LAO:
            if ( msAPI_OSD_GetOSDLanguage() != LANGUAGE_OSD_LAO )
            {
                msAPI_OSD_SetOSDLanguage(LANGUAGE_OSD_LAO);
                printf("%d Reload TTF Font Lao\n", __LINE__);
                MApp_LoadFontInit_TTF(BIN_ID_FONT_UI_TTF_LAO, TRUE);
            }
            break;
    #endif

        default:
            msAPI_OSD_SetOSDLanguage(msAPI_OSD_APILanguage2OSDLanguage(eLanguage));
            break;
        }
    }
#endif

  #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(OSD_L != stGenSetting.g_SysSetting.Language)
        {
            printf("71_OSD_Change_Language\n");
        }
        OSD_L = stGenSetting.g_SysSetting.Language;
    }
  #endif

#if(ENABLE_CEC)
    //fixed 11.1.6-4
    U8 u8CecLangCode[MAX_ISO639CODE_LENGTH] = { 0 };

    if( MApp_GetOSDLangCodeFromIndex(eLanguage, u8CecLangCode)==TRUE)
    {
        msAPI_CEC_PostMsg_SetMenuLang(DIRECTMSG, u8CecLangCode);
    }

#endif

#if(ENABLE_DVB) //ENABLE_DTV
    MApp_SetSILanguage(eLanguage);

    if( IsDTVInUse() )
    {
    #if(ENABLE_DTV_EPG)
        MApp_Epg_Init();
    #endif
    }

  #if (ENABLE_CI && ENABLE_CI_PLUS)
    {
        EN_SI_LANGUAGE eLangCodeId;
        U8 u8aLangCode[MAX_ISO639CODE_LENGTH] = { 0 };

        eLangCodeId = MApp_GetSILanguage(eLanguage);
        if (TRUE == msAPI_SI_GetISOLangCodeFromIndex(eLangCodeId, u8aLangCode))
            msAPI_CI_HLC_SetLanguage(u8aLangCode);
    }
  #endif

  #if ENABLE_TTX
    MApp_TTX_NotifyPMTTTXInfoChanged();
  #endif
#endif
}
#endif

void MApp_SetTimeZone(EN_MENU_TIMEZONE eTimezone)
{
    if (eTimezone >= TIMEZONE_NUM)
    {
        MS_DEBUG_MSG(printf("Set Lang Overflow: %u\n", (U16)eTimezone));
        eTimezone = TIMEZONE_GMT_0_START;
    }

    stGenSetting.g_Time.enTimeZone = eTimezone;


    if( (MENU_TIMEZONE>=TIMEZONE_GMT_Minus5_START)&&(MENU_TIMEZONE<=TIMEZONE_GMT_Minus5_END) )
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_14;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus4_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus4_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_16;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus3_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus3_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_18;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus2_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus2_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_20;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_Minus1_START && MENU_TIMEZONE<=TIMEZONE_GMT_Minus1_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_22;
    }
    else if( (MENU_TIMEZONE>=TIMEZONE_GMT_0_START) && (MENU_TIMEZONE<=TIMEZONE_GMT_0_END))
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_24;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_1_START && MENU_TIMEZONE<=TIMEZONE_GMT_1_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_26;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_2_START && MENU_TIMEZONE<=TIMEZONE_GMT_2_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_28;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_3_START && MENU_TIMEZONE<=TIMEZONE_GMT_3_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_30;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_3Point5_START && MENU_TIMEZONE<=TIMEZONE_GMT_3Point5_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_31;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_4_START && MENU_TIMEZONE<=TIMEZONE_GMT_4_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_32;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_6Point5_START && MENU_TIMEZONE<=TIMEZONE_GMT_6Point5_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_37;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_7_START && MENU_TIMEZONE<=TIMEZONE_GMT_7_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_38;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_8_START && MENU_TIMEZONE<=TIMEZONE_GMT_8_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_40;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_9_START && MENU_TIMEZONE<=TIMEZONE_GMT_9_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_42;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_9Point5_START && MENU_TIMEZONE<=TIMEZONE_GMT_9Point5_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_43;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_10_START && MENU_TIMEZONE<=TIMEZONE_GMT_10_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_44;
    }
    else if(MENU_TIMEZONE>=TIMEZONE_GMT_12_START && MENU_TIMEZONE<=TIMEZONE_GMT_12_END)
    {
        stGenSetting.g_Time.en_Clock_TimeZone=EN_Clock_TimeZone_48;
    }
    else
    {
        printf("\nError: Unknown timezone=%u\n", MENU_TIMEZONE);
    }

}

#if ENABLE_CI
 void MApp_SetCIDebugLevelInit(void)
{
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_RM,stGenSetting.g_CISetting.UResource_Manager);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_APPINFO,stGenSetting.g_CISetting.UApplication_Information);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_CAS,stGenSetting.g_CISetting.UConditional_Access_Support);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_HC,stGenSetting.g_CISetting.UHost_Control);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_DT,stGenSetting.g_CISetting.UDate_Time);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_MMI,stGenSetting.g_CISetting.UMan_Machine_Interface);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_LSC,stGenSetting.g_CISetting.ULow_Speed_Communication);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_CC,stGenSetting.g_CISetting.UContent_Control);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_HLC,stGenSetting.g_CISetting.UHost_Language_Control);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_CU,stGenSetting.g_CISetting.UCAM_Upgrade);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_OP,stGenSetting.g_CISetting.UOperate_Profile);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_SAS,stGenSetting.g_CISetting.USpecific_Application_Support);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_APPMMI,stGenSetting.g_CISetting.UApplication_Man_Machine_Interface);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_HSS,stGenSetting.g_CISetting.UHost_Service_Shunning);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_PMT,stGenSetting.g_CISetting.UProgram_Map_Table);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_AUTH,stGenSetting.g_CISetting.UCanal_Ready_Authentication);
     msAPI_CI_SetDebugLevel((EN_CI_FUNCTION)EN_CI_FUNCTION_DEFAULT,stGenSetting.g_CISetting.UDEFAULT);


}
#endif

void MApp_SetAudioLangMenuLanguage(EN_LANGUAGE eLanguage)
{
    if (eLanguage > LANGUAGE_MAX)
    {
        MS_DEBUG_MSG(printf("Set Lang Overflow: %u\n", (U8)eLanguage));
        eLanguage = DEFAULT_MENU_LANG;
    }
    if(!stGenSetting.g_SoundSetting.Primary_Flag)
    {
        stGenSetting.g_SoundSetting.enSoundAudioLan1 = eLanguage;
    #if (ENABLE_DVB)
        MApp_ChannelChange_SearchDefaultAudioLang();
        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
    #endif
    }
    else
    {
        stGenSetting.g_SoundSetting.enSoundAudioLan2 = eLanguage;
    #if (ENABLE_DVB)
        MApp_ChannelChange_SearchDefaultAudioLang();
        MApp_Audio_SetAudioLanguage(g_u8AudLangSelected);
    #endif
    }

  #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(Audio_L != stGenSetting.g_SoundSetting.enSoundAudioLan1)
        {
            printf("71_Audio_Change_Language\n");
        }
        Audio_L = stGenSetting.g_SoundSetting.enSoundAudioLan1;
    }
  #endif
}

void MApp_SetSubLangMenuLanguage(EN_LANGUAGE eLanguage)
{
    if(OSD_COUNTRY_SETTING == E_NEWZEALAND)
    {
        if (eLanguage > LANGUAGE_SUBTITLE_MAX_NZ)
        {
            MS_DEBUG_MSG(printf("Set Lang Overflow: %u\n", (U8)eLanguage));
            eLanguage = DEFAULT_MENU_LANG;
        }
    }
    else
    {
        if (eLanguage > LANGUAGE_SUBTITLE_MAX_EU)
        {
            MS_DEBUG_MSG(printf("Set Lang Overflow: %u\n", (U8)eLanguage));
            eLanguage = DEFAULT_MENU_LANG;
        }
    }
    if(!stGenSetting.g_SysSetting.fSUBLANG_FLAG)
    {
        stGenSetting.g_SysSetting.SubtitleDefaultLanguage = eLanguage;
    #if (ENABLE_SUBTITLE)
        MApp_TV_Menu_SelectSubtileLang();
        MApp_TV_SelectSubtileLang();
    #endif
    }
    else
    {
        stGenSetting.g_SysSetting.SubtitleDefaultLanguage_2 = eLanguage;
    #if (ENABLE_SUBTITLE)
        MApp_TV_Menu_SelectSubtileLang();
        MApp_TV_SelectSubtileLang();
    #endif
    }
    #if ENABLE_AUTOTEST
    if(g_bAutobuildDebug)
    {
        if(Audio_L != stGenSetting.g_SoundSetting.enSoundAudioLan1)
        {
            printf("71_Subtitle_Change_Language\n");
        }
        Audio_L = stGenSetting.g_SoundSetting.enSoundAudioLan1;
    }
    #endif
}


BOOLEAN MApp_CmpMenuLanguage(EN_LANGUAGE eLanguage)
{
#if 1 // (MS_BOARD_TYPE_SEL == BD_P_001A)
    U8 u8UnSelect = FALSE;
    switch (eLanguage)
    {
        //case LANGUAGE_CZECH:
        //case LANGUAGE_DANISH:
        //case LANGUAGE_GERMAN:
        //case LANGUAGE_ENGLISH:
        //case LANGUAGE_SPANISH:
        //case LANGUAGE_GREEK:
        //case LANGUAGE_FRENCH:
        //case LANGUAGE_CROATIAN:
        //case LANGUAGE_ITALIAN:
        //case LANGUAGE_HUNGARIAN:
        //case LANGUAGE_DUTCH:
        //case LANGUAGE_NORWEGIAN:
        //case LANGUAGE_POLISH:
        //case LANGUAGE_PORTUGUESE:
        //case LANGUAGE_RUSSIAN:
        //case LANGUAGE_ROMANIAN:
        case LANGUAGE_SLOVENIAN:
        //case LANGUAGE_SERBIAN:
        //case LANGUAGE_FINNISH:
        //case LANGUAGE_SWEDISH:
        //case LANGUAGE_BULGARIAN:
      #if (ENABLE_DTMB_CHINA_APP || ENABLE_ATV_CHINA_APP || ENABLE_DVBC_PLUS_DTMB_CHINA_APP||CHINESE_SIMP_FONT_ENABLE ||CHINESE_BIG5_FONT_ENABLE)
        case LANGUAGE_CHINESE:
      #endif

        case LANGUAGE_GAELIC:
        case LANGUAGE_WELSH:
            u8UnSelect = TRUE;
        default:
            break;
    }
    return u8UnSelect;
#else
    eLanguage = eLanguage;
    return FALSE;
#endif
}

void MApp_SetOnTimer(MENU_OnTimer eOnTimerDate)
{
    msAPI_Power_SetOnTimer(eOnTimerDate);
}

MENU_OnTimer MApp_GetOnTimer(void)
{
    return msAPI_Power_GetOnTimer();
}

void MApp_SetDayOfWeek(DAYOFWEEK eDayOfWeek)
{
    msAPI_Power_SetDayOfWeek(eDayOfWeek);
}

/*/ZUI: unused:
U8 MApp_ASCII2INT(U8 buf)
{

    U8 value;

    if((buf>=0x30) && (buf <=0x39 )) // 0~9
    {
        value=buf-0x30;
    }
    else if((buf >=0x41) && (buf <=0x46))    // A~F
    {
        value=buf-0x37;
    }
    else if((buf >=0x61) && (buf <=0x66))    // a~f
    {
        value=buf-0x57;
    }
    else
        value=0x00;

    return value;
}
*/

void MApp_AddDay2StTime ( U16 u16DaysToAdd, ST_TIME *pstTime )
{
    U16 u16DaysInYear;
    U16 u16Days;

    //Year
    u16Days = MApp_GetDaysOfThisYear(pstTime->u16Year);
    u16DaysInYear = SolarDays[MApp_GetLeap( pstTime->u16Year ) * 14 + pstTime->u8Month - 1]+ pstTime->u8Day;

    if(u16DaysToAdd > (u16Days - u16DaysInYear))  //leap year
    {
        u16DaysToAdd -= (u16Days - u16DaysInYear + 1);
        pstTime->u16Year++;

        //Advancing Year
        while(u16DaysToAdd > (u16Days = MApp_GetDaysOfThisYear(pstTime->u16Year)))
        {
            u16DaysToAdd -= u16Days;
            pstTime->u16Year++;
        }
    }
    else
    {
        u16DaysToAdd += u16DaysInYear - 1;
    }

    pstTime->u8Month = 1;
    pstTime->u8Day= 1;

    //Advancing Month
    while(u16DaysToAdd > (u16Days = MApp_GetDaysOfThisMonth(pstTime->u16Year, pstTime->u8Month)))
    {
        u16DaysToAdd -= u16Days;
        pstTime->u8Month++;
    }
    pstTime->u8Day += u16DaysToAdd;
}

#if ENABLE_DVB
void MApp_SILogoSetup(void)
{
#if ASTRA_HD_ENABLE
    if(ISDVBS2Source()) // && MApp_GetSICountry(OSD_COUNTRY_SETTING) == SI_COUNTRY_GERMANY)
    {
        SetASTRA_HD_ENABLE(ENABLE);
    }
    else
    {
        SetASTRA_HD_ENABLE(DISABLE);
    }
#endif

}

BOOLEAN MApp_UiMenuFunc_IsSystemClockSet(void)
{
    BOOLEAN bRtn = TRUE;

    //printf("g_u8TimeInfo_Flag=%X\n", g_u8TimeInfo_Flag);
    //printf("MApp_SI_IsAutoClockValid()=%u\n", MApp_SI_IsAutoClockValid());

    bRtn = ((g_u8TimeInfo_Flag & UI_TIME_MINUTE_SET) || MApp_SI_IsAutoClockValid());

    //printf("IsSystemClockSet=%u\n", bRtn);

    return bRtn;
}

static void MApp_SetSICountry(EN_OSD_COUNTRY_SETTING eOSDCountrySetting)
{
    EN_SI_COUNTRY_SETTING eSICountry = SI_COUNTRY_UK;
    switch(eOSDCountrySetting)
    {
        case OSD_COUNTRY_AUSTRALIA:         eSICountry = SI_COUNTRY_AUSTRALIA; break;
        case OSD_COUNTRY_AUSTRIA:           eSICountry = SI_COUNTRY_AUSTRIA; break;
        case OSD_COUNTRY_BELGIUM:           eSICountry = SI_COUNTRY_BELGIUM; break;
        case OSD_COUNTRY_BULGARIA:          eSICountry = SI_COUNTRY_BULGARIA; break;
        case OSD_COUNTRY_CROATIA:           eSICountry = SI_COUNTRY_CROATIA; break;
        case OSD_COUNTRY_CZECH:             eSICountry = SI_COUNTRY_CZECH; break;
        case OSD_COUNTRY_DENMARK:           eSICountry = SI_COUNTRY_DENMARK; break;
        case OSD_COUNTRY_FINLAND:           eSICountry = SI_COUNTRY_FINLAND; break;
        case OSD_COUNTRY_FRANCE:            eSICountry = SI_COUNTRY_FRANCE; break;
        case OSD_COUNTRY_GERMANY:           eSICountry = SI_COUNTRY_GERMANY; break;
        case OSD_COUNTRY_GREECE:            eSICountry = SI_COUNTRY_GREECE; break;
        case OSD_COUNTRY_HUNGARY:            eSICountry = SI_COUNTRY_HUNGARY; break;
        case OSD_COUNTRY_ITALY:             eSICountry = SI_COUNTRY_ITALY; break;
        case OSD_COUNTRY_IRELAND:            eSICountry = SI_COUNTRY_IRELAND; break;
        case OSD_COUNTRY_LUXEMBOURG:        eSICountry = SI_COUNTRY_LUXEMBOURG; break;
        case OSD_COUNTRY_NETHERLANDS:       eSICountry = SI_COUNTRY_NETHERLANDS; break;
        case OSD_COUNTRY_NORWAY:            eSICountry = SI_COUNTRY_NORWAY; break;
        case OSD_COUNTRY_POLAND:            eSICountry = SI_COUNTRY_POLAND; break;
        case OSD_COUNTRY_PORTUGAL:          eSICountry = SI_COUNTRY_PORTUGAL; break;
        case OSD_COUNTRY_ROMANIA:           eSICountry = SI_COUNTRY_ROMANIA; break;
        case OSD_COUNTRY_RUSSIA:           eSICountry = SI_COUNTRY_RUSSIA; break;
        case OSD_COUNTRY_SERBIA:            eSICountry = SI_COUNTRY_SERBIA; break;
        case OSD_COUNTRY_SLOVENIA:          eSICountry = SI_COUNTRY_SLOVENIA; break;
        case OSD_COUNTRY_SPAIN:             eSICountry = SI_COUNTRY_SPAIN; break;
        case OSD_COUNTRY_SWEDEN:            eSICountry = SI_COUNTRY_SWEDEN; break;
        case OSD_COUNTRY_SWITZERLAND:       eSICountry = SI_COUNTRY_SWITZERLAND; break;
        case OSD_COUNTRY_UK:                eSICountry = SI_COUNTRY_UK; break;
        case OSD_COUNTRY_NEWZEALAND:        eSICountry = SI_COUNTRY_NEWZEALAND; break;
        case OSD_COUNTRY_CHINA:             eSICountry = SI_COUNTRY_CHINA; break;
        case OSD_COUNTRY_MOROCCO:            eSICountry = SI_COUNTRY_MOROCCO; break;
        case OSD_COUNTRY_TUNIS:              eSICountry = SI_COUNTRY_TUNIS; break;
        case OSD_COUNTRY_ALGERIA:            eSICountry = SI_COUNTRY_ALGERIA; break;
        case OSD_COUNTRY_EGYPT:              eSICountry = SI_COUNTRY_EGYPT; break;
        case OSD_COUNTRY_SOUTH_AFRICA:       eSICountry = SI_COUNTRY_SOUTH_AFRICA; break;
        case OSD_COUNTRY_ISRAEL:             eSICountry = SI_COUNTRY_ISRAEL; break;
        case OSD_COUNTRY_IRAN:               eSICountry = SI_COUNTRY_IRAN; break;
        case OSD_COUNTRY_UNITED_ARAB_EMIRATES:   eSICountry = SI_COUNTRY_UNITED_ARAB_EMIRATES; break;
        case OSD_COUNTRY_KUWAIT:             eSICountry = SI_COUNTRY_KUWAIT;         break;
        case OSD_COUNTRY_OMAN:               eSICountry = SI_COUNTRY_OMAN;           break;
        case OSD_COUNTRY_QATAR:              eSICountry = SI_COUNTRY_QATAR;          break;
        case OSD_COUNTRY_SAUDI_ARABIA:       eSICountry = SI_COUNTRY_SAUDI_ARABIA;   break;
        case OSD_COUNTRY_BAHRAIN:            eSICountry = SI_COUNTRY_BAHRAIN;        break;
        case OSD_COUNTRY_SLOVAKIA:               eSICountry = SI_COUNTRY_SLOVAKIA;                 break;
        case OSD_COUNTRY_THAILAND:          eSICountry = SI_COUNTRY_THAILAND;   break;
        case OSD_COUNTRY_VIETNAM:           eSICountry = SI_COUNTRY_VIETNAM;    break;
        case OSD_COUNTRY_SINGAPORE:         eSICountry = SI_COUNTRY_SINGAPORE;  break;
        case OSD_COUNTRY_MALAYSIA:          eSICountry = SI_COUNTRY_MALAYSIA;   break;
        case OSD_COUNTRY_INDONESIA:         eSICountry = SI_COUNTRY_INDONESIA;  break;

      #if (ENABLE_DVB_TAIWAN_APP)
        case OSD_COUNTRY_TAIWAN:            eSICountry = SI_COUNTRY_TAIWAN; break;
      #endif
        case OSD_COUNTRY_BRAZIL:            eSICountry = SI_COUNTRY_BRAZIL; break;
     case OSD_COUNTRY_ESTONIA:          eSICountry = SI_COUNTRY_ESTONIA; break;
     case OSD_COUNTRY_TURKEY:           eSICountry = SI_COUNTRY_TURKEY; break;
     case OSD_COUNTRY_GHANA:            eSICountry = SI_COUNTRY_GHANA; break;
     case OSD_COUNTRY_KENYA:            eSICountry = SI_COUNTRY_KENYA; break;
     case OSD_COUNTRY_MYANMAR:            eSICountry = SI_COUNTRY_MYANMAR; break;

        default:
            ASSERT(0);
        break;
    }

    MApp_SI_SetDefaultCountry(eSICountry);

    MApp_SILogoSetup();
}



void MApp_SetSILanguage(EN_LANGUAGE eLanguage)
{
    EN_SI_LANGUAGE eSILanguage = SI_LANGUAGE_ENGLISH;
    switch(eLanguage)
    {
        case LANGUAGE_CZECH:                eSILanguage = SI_LANGUAGE_CZECH; break;
        case LANGUAGE_DANISH:               eSILanguage = SI_LANGUAGE_DANISH; break;
        case LANGUAGE_GERMAN:               eSILanguage = SI_LANGUAGE_GERMAN; break;
        case LANGUAGE_ENGLISH:              eSILanguage = SI_LANGUAGE_ENGLISH; break;
        case LANGUAGE_SPANISH:              eSILanguage = SI_LANGUAGE_SPANISH; break;
        case LANGUAGE_GREEK:                eSILanguage = SI_LANGUAGE_GREEK; break;
        case LANGUAGE_FRENCH:               eSILanguage = SI_LANGUAGE_FRENCH; break;
        case LANGUAGE_CROATIAN:             eSILanguage = SI_LANGUAGE_CROATIAN; break;
        case LANGUAGE_ITALIAN:              eSILanguage = SI_LANGUAGE_ITALIAN; break;
        case LANGUAGE_HUNGARIAN:            eSILanguage = SI_LANGUAGE_HUNGARIAN; break;
        case LANGUAGE_DUTCH:                eSILanguage = SI_LANGUAGE_DUTCH; break;
        case LANGUAGE_NORWEGIAN:            eSILanguage = SI_LANGUAGE_NORWEGIAN; break;
        case LANGUAGE_POLISH:               eSILanguage = SI_LANGUAGE_POLISH; break;
        case LANGUAGE_PORTUGUESE:           eSILanguage = SI_LANGUAGE_PORTUGUESE; break;
        case LANGUAGE_RUSSIAN:              eSILanguage = SI_LANGUAGE_RUSSIAN; break;
        case LANGUAGE_ROMANIAN:             eSILanguage = SI_LANGUAGE_ROMANIAN; break;
        case LANGUAGE_SLOVENIAN:            eSILanguage = SI_LANGUAGE_SLOVENIAN; break;
        case LANGUAGE_SERBIAN:              eSILanguage = SI_LANGUAGE_SERBIAN; break;
        case LANGUAGE_FINNISH:              eSILanguage = SI_LANGUAGE_FINNISH; break;
        case LANGUAGE_SWEDISH:              eSILanguage = SI_LANGUAGE_SWEDISH; break;
        case LANGUAGE_BULGARIAN:            eSILanguage = SI_LANGUAGE_BULGARIAN; break;
        case LANGUAGE_SLOVAK:               eSILanguage = SI_LANGUAGE_SLOVAK; break;
        case LANGUAGE_CHINESE:              eSILanguage = SI_LANGUAGE_CHINESE; break;
        case LANGUAGE_CHINESE_TRAD:         eSILanguage = SI_LANGUAGE_CHINESE_TRAD; break;
        case LANGUAGE_THAI:                 eSILanguage = SI_LANGUAGE_THAILAND; break;
        case LANGUAGE_GAELIC:               eSILanguage = SI_LANGUAGE_GAELIC; break;
        case LANGUAGE_AKAN:                 eSILanguage = SI_LANGUAGE_AKAN; break;
        case LANGUAGE_EWE:                  eSILanguage = SI_LANGUAGE_EWE; break;
        case LANGUAGE_TWI:                  eSILanguage = SI_LANGUAGE_TWI; break;
        case LANGUAGE_NZEMA:                eSILanguage = SI_LANGUAGE_NZEMA; break;
        case LANGUAGE_HAUSA:                eSILanguage = SI_LANGUAGE_HAUSA; break;
        case LANGUAGE_KASEM:                eSILanguage = SI_LANGUAGE_KASEM; break;
        case LANGUAGE_WELSH:                eSILanguage = SI_LANGUAGE_WELSH; break;
        case LANGUAGE_IRISH:                eSILanguage = SI_LANGUAGE_IRISH; break;
        case LANGUAGE_TURKISH:              eSILanguage = SI_LANGUAGE_TURKISH; break;
        case LANGUAGE_NETHERLANDS:          eSILanguage = SI_LANGUAGE_NETHERLANDS; break;
        case LANGUAGE_GALLEGAN:             eSILanguage = SI_LANGUAGE_GALLEGAN; break;
        case LANGUAGE_BASQUE:               eSILanguage = SI_LANGUAGE_BASQUE; break;
        case LANGUAGE_LUXEMBOURGISH:        eSILanguage = SI_LANGUAGE_LUXEMBOURGISH; break;
        case LANGUAGE_ICELANDIC:            eSILanguage = SI_LANGUAGE_ICELANDIC; break;
        case LANGUAGE_LATVIAN:              eSILanguage = SI_LANGUAGE_LATVIAN; break;
        case LANGUAGE_ESTONIAN:             eSILanguage = SI_LANGUAGE_ESTONIAN; break;
        case LANGUAGE_LITHUANIAN:           eSILanguage = SI_LANGUAGE_LITHUANIAN; break;
        case LANGUAGE_UKRANIAN:             eSILanguage = SI_LANGUAGE_UKRANIAN; break;
        case LANGUAGE_BELARUSIAN:           eSILanguage = SI_LANGUAGE_BELARUSIAN; break;
        case LANGUAGE_SPANISH_CAT:          eSILanguage = SI_LANGUAGE_SPANISH_CAT; break;
        case LANGUAGE_SAMI:                 eSILanguage = SI_LANGUAGE_SAMI; break;
        case LANGUAGE_ARABIC:               eSILanguage = SI_LANGUAGE_ARABIC; break;
        case LANGUAGE_HEBREW:               eSILanguage = SI_LANGUAGE_HEBREW; break;
        case LANGUAGE_KOREAN:               eSILanguage = SI_LANGUAGE_KOREAN; break;
        case LANGUAGE_JAPAN:                eSILanguage = SI_LANGUAGE_JAPAN; break;
        case LANGUAGE_HINDI:                eSILanguage = SI_LANGUAGE_HINDI; break;
        case LANGUAGE_MANDARIN:             eSILanguage = SI_LANGUAGE_MANDARIN; break;
        case LANGUAGE_CANTONESE:            eSILanguage = SI_LANGUAGE_CANTONESE; break;
        case LANGUAGE_MAORI:                eSILanguage = SI_LANGUAGE_MAORI; break;
        case LANGUAGE_TAMIL:                eSILanguage = SI_LANGUAGE_TAMIL; break;
        case LANGUAGE_INDONESIA:            eSILanguage = SI_LANGUAGE_INDONESIA; break;
        case LANGUAGE_MALAYSIA:             eSILanguage = SI_LANGUAGE_MALAYSIA; break;
        case LANGUAGE_VIETNAM:              eSILanguage =  SI_LANGUAGE_VIETNAM; break;
        case LANGUAGE_SWAHILI:              eSILanguage =  SI_LANGUAGE_SWAHILI; break;
        case LANGUAGE_MYANMAR:              eSILanguage =  SI_LANGUAGE_MYANMAR; break;

        default:
            ASSERT(0);
        break;
    }

    MApp_SI_SetDefaultLanguage(eSILanguage);
}

EN_SI_TIMEZONE MApp_GetSITimeZone(EN_MENU_TIMEZONE eTimeZone)
{
    switch(eTimeZone)
    {
        case TIMEZONE_CANARY:               return SI_TIMEZONE_CANARY;
        case TIMEZONE_LISBON:               return SI_TIMEZONE_LISBON;
        case TIMEZONE_LONDON:               return SI_TIMEZONE_LONDON;
        case TIMEZONE_RABAT:                return SI_TIMEZONE_RABAT;
        case TIMEZONE_AMSTERDAM:            return SI_TIMEZONE_AMSTERDAM;
        case TIMEZONE_BEOGRAD:              return SI_TIMEZONE_BEOGRAD;
        case TIMEZONE_BERLIN:               return SI_TIMEZONE_BERLIN;
        case TIMEZONE_BRUSSELS:             return SI_TIMEZONE_BRUSSELS;
        case TIMEZONE_BUDAPEST:             return SI_TIMEZONE_BUDAPEST;
        case TIMEZONE_COPENHAGEN:           return SI_TIMEZONE_COPENHAGEN;
        case TIMEZONE_LIUBLJANA:            return SI_TIMEZONE_LIUBLJANA;
        case TIMEZONE_LUXEMBOURG:           return SI_TIMEZONE_LUXEMBOURG;
        case TIMEZONE_MADRID:               return SI_TIMEZONE_MADRID;
        case TIMEZONE_OSLO:                 return SI_TIMEZONE_OSLO;
        case TIMEZONE_PARIS:                return SI_TIMEZONE_PARIS;
        case TIMEZONE_PRAGUE:               return SI_TIMEZONE_PRAGUE;
        case TIMEZONE_BRATISLAVA:           return SI_TIMEZONE_BRATISLAVA;
        case TIMEZONE_BERN:                 return SI_TIMEZONE_BERN;
        case TIMEZONE_ROME:                 return SI_TIMEZONE_ROME;
        case TIMEZONE_STOCKHOLM:            return SI_TIMEZONE_STOCKHOLM;
        case TIMEZONE_WARSAW:               return SI_TIMEZONE_WARSAW;
        case TIMEZONE_VIENNA:               return SI_TIMEZONE_VIENNA;
        case TIMEZONE_ZAGREB:               return SI_TIMEZONE_ZAGREB;
        case TIMEZONE_TUNIS:                return SI_TIMEZONE_TUNIS;
        case TIMEZONE_ALGIERS:              return SI_TIMEZONE_ALGIERS;
        case TIMEZONE_ATHENS:               return SI_TIMEZONE_ATHENS;
        case TIMEZONE_BUCURESTI:            return SI_TIMEZONE_BUCURESTI;
        case TIMEZONE_HELSINKI:             return SI_TIMEZONE_HELSINKI;
        case TIMEZONE_SOFIA:                return SI_TIMEZONE_SOFIA;
        case TIMEZONE_CAIRO:                return SI_TIMEZONE_CAIRO;
        case TIMEZONE_CAPE_TOWN:            return SI_TIMEZONE_CAPE_TOWN;
        //case TIMEZONE_ESTONIA:              return SI_TIMEZONE_ESTONIA;
        //case TIMEZONE_TURKEY:              return SI_TIMEZONE_TURKEY;
        case TIMEZONE_JERUSSLEM:            return SI_TIMEZONE_JERUSSLEM;
        case TIMEZONE_MOSCOW:               return SI_TIMEZONE_MOSCOW;
        case TIMEZONE_TEHERAN:              return SI_TIMEZONE_TEHERAN;
        case TIMEZONE_ABU_DHABI:            return SI_TIMEZONE_ABU_DHABI;
        case TIMEZONE_KUWAIT:               return SI_TIMEZONE_KUWAIT;
        case TIMEZONE_MUSCAT:               return SI_TIMEZONE_MUSCAT;
        case TIMEZONE_DOHA:                 return SI_TIMEZONE_DOHA;
        case TIMEZONE_RIYADH:               return SI_TIMEZONE_RIYADH;
        case TIMEZONE_MANAMA:               return SI_TIMEZONE_MANAMA;
        case TIMEZONE_BEIJING:              return SI_TIMEZONE_BEIJING;
        case TIMEZONE_WA:                   return SI_TIMEZONE_WA;
        case TIMEZONE_SA:                   return SI_TIMEZONE_SA;
        case TIMEZONE_NT:                   return SI_TIMEZONE_NT;
        case TIMEZONE_NSW:                  return SI_TIMEZONE_NSW;
        case TIMEZONE_VIC:                  return SI_TIMEZONE_VIC;
        case TIMEZONE_QLD:                  return SI_TIMEZONE_QLD;
        case TIMEZONE_TAS:                  return SI_TIMEZONE_TAS;
        case TIMEZONE_NZST:                 return SI_TIMEZONE_NZST;

      #if 1//ENABLE_SBTVD_DTV_SYSTEM
        case TIMEZONE_AM_WEST:              return SI_TIMEZONE_AM_WEST;
        case TIMEZONE_ACRE:                 return SI_TIMEZONE_ACRE;
        case TIMEZONE_M_GROSSO:             return SI_TIMEZONE_M_GROSSO;
        case TIMEZONE_NORTH:                return SI_TIMEZONE_NORTH;
        case TIMEZONE_BRASILIA:             return SI_TIMEZONE_BRASILIA;
        case TIMEZONE_NORTHEAST:            return SI_TIMEZONE_NORTHEAST;
        case TIMEZONE_F_NORONHA:            return SI_TIMEZONE_F_NORONHA;
      #endif
        case TIMEZONE_AZORES:                    return SI_TIMEZONE_AZORES;
        //case TIMEZONE_DUBLIN:                return SI_TIMEZONE_DUBLIN;
        case TIMEZONE_NUM:                  return SI_TIMEZONE_NUM;
        case TIMEZONE_INDONESIA_WEST:       return SI_TIMEZONE_INDONESIA_WEST;
        case TIMEZONE_KUALA_LUMPUR:         return SI_TIMEZONE_KUALA_LUMPUR;
        case TIMEZONE_SINGAPORE:            return SI_TIMEZONE_SINGAPORE;
        case TIMEZONE_MYANMAR:              return SI_TIMEZONE_MYANMAR;

        default:
            ASSERT(0);
        return SI_TIMEZONE_LONDON;
    }
}

EN_SI_Clock_TimeZone MApp_GetSIClockTimeZone(EN_MENU_Clock_TimeZone eClockTimeZone)
{
    switch(eClockTimeZone)
    {
        case EN_Clock_TimeZone_0:           return EN_SI_Clock_TimeZone_0;
        case EN_Clock_TimeZone_1:           return EN_SI_Clock_TimeZone_1;
        case EN_Clock_TimeZone_2:           return EN_SI_Clock_TimeZone_2;
        case EN_Clock_TimeZone_3:           return EN_SI_Clock_TimeZone_3;
        case EN_Clock_TimeZone_4:           return EN_SI_Clock_TimeZone_4;
        case EN_Clock_TimeZone_5:           return EN_SI_Clock_TimeZone_5;
        case EN_Clock_TimeZone_6:           return EN_SI_Clock_TimeZone_6;
        case EN_Clock_TimeZone_7:           return EN_SI_Clock_TimeZone_7;
        case EN_Clock_TimeZone_8:           return EN_SI_Clock_TimeZone_8;
        case EN_Clock_TimeZone_9:           return EN_SI_Clock_TimeZone_9;
        case EN_Clock_TimeZone_10:          return EN_SI_Clock_TimeZone_10;
        case EN_Clock_TimeZone_11:          return EN_SI_Clock_TimeZone_11;
        case EN_Clock_TimeZone_12:          return EN_SI_Clock_TimeZone_12;
        case EN_Clock_TimeZone_13:          return EN_SI_Clock_TimeZone_13;
        case EN_Clock_TimeZone_14:          return EN_SI_Clock_TimeZone_14;
        case EN_Clock_TimeZone_15:          return EN_SI_Clock_TimeZone_15;
        case EN_Clock_TimeZone_16:          return EN_SI_Clock_TimeZone_16;
        case EN_Clock_TimeZone_17:          return EN_SI_Clock_TimeZone_17;
        case EN_Clock_TimeZone_18:          return EN_SI_Clock_TimeZone_18;
        case EN_Clock_TimeZone_19:          return EN_SI_Clock_TimeZone_19;
        case EN_Clock_TimeZone_20:          return EN_SI_Clock_TimeZone_20;
        case EN_Clock_TimeZone_21:          return EN_SI_Clock_TimeZone_21;
        case EN_Clock_TimeZone_22:          return EN_SI_Clock_TimeZone_22;
        case EN_Clock_TimeZone_23:          return EN_SI_Clock_TimeZone_23;
        case EN_Clock_TimeZone_24:          return EN_SI_Clock_TimeZone_24;
        case EN_Clock_TimeZone_25:          return EN_SI_Clock_TimeZone_25;
        case EN_Clock_TimeZone_26:          return EN_SI_Clock_TimeZone_26;
        case EN_Clock_TimeZone_27:          return EN_SI_Clock_TimeZone_27;
        case EN_Clock_TimeZone_28:          return EN_SI_Clock_TimeZone_28;
        case EN_Clock_TimeZone_29:          return EN_SI_Clock_TimeZone_29;
        case EN_Clock_TimeZone_30:          return EN_SI_Clock_TimeZone_30;
        case EN_Clock_TimeZone_31:          return EN_SI_Clock_TimeZone_31;
        case EN_Clock_TimeZone_32:          return EN_SI_Clock_TimeZone_32;
        case EN_Clock_TimeZone_33:          return EN_SI_Clock_TimeZone_33;
        case EN_Clock_TimeZone_34:          return EN_SI_Clock_TimeZone_34;
        case EN_Clock_TimeZone_35:          return EN_SI_Clock_TimeZone_35;
        case EN_Clock_TimeZone_36:          return EN_SI_Clock_TimeZone_36;
        case EN_Clock_TimeZone_37:          return EN_SI_Clock_TimeZone_37;
        case EN_Clock_TimeZone_38:          return EN_SI_Clock_TimeZone_38;
        case EN_Clock_TimeZone_39:          return EN_SI_Clock_TimeZone_39;
        case EN_Clock_TimeZone_40:          return EN_SI_Clock_TimeZone_40;
        case EN_Clock_TimeZone_41:          return EN_SI_Clock_TimeZone_41;
        case EN_Clock_TimeZone_42:          return EN_SI_Clock_TimeZone_42;
        case EN_Clock_TimeZone_43:          return EN_SI_Clock_TimeZone_43;
        case EN_Clock_TimeZone_44:          return EN_SI_Clock_TimeZone_44;
        case EN_Clock_TimeZone_45:          return EN_SI_Clock_TimeZone_45;
        case EN_Clock_TimeZone_46:          return EN_SI_Clock_TimeZone_46;
        case EN_Clock_TimeZone_47:          return EN_SI_Clock_TimeZone_47;
        case EN_Clock_TimeZone_48:          return EN_SI_Clock_TimeZone_48;
        case EN_Clock_TimeZone_Num:         return EN_SI_Clock_TimeZone_Num;

        default:
            ASSERT(0);
        return EN_SI_Clock_TimeZone_24;
    }
}



EN_SI_LANGUAGE MApp_GetSILanguage(EN_LANGUAGE eLanguage)
{
    switch(eLanguage)
    {
        case LANGUAGE_CZECH:                return SI_LANGUAGE_CZECH;
        case LANGUAGE_DANISH:               return SI_LANGUAGE_DANISH;
        case LANGUAGE_GERMAN:               return SI_LANGUAGE_GERMAN;
        case LANGUAGE_ENGLISH:              return SI_LANGUAGE_ENGLISH;
        case LANGUAGE_SPANISH:              return SI_LANGUAGE_SPANISH;
        case LANGUAGE_GREEK:                return SI_LANGUAGE_GREEK;
        case LANGUAGE_FRENCH:               return SI_LANGUAGE_FRENCH;
        case LANGUAGE_CROATIAN:             return SI_LANGUAGE_CROATIAN;
        case LANGUAGE_ITALIAN:              return SI_LANGUAGE_ITALIAN;
        case LANGUAGE_HUNGARIAN:            return SI_LANGUAGE_HUNGARIAN;
        case LANGUAGE_DUTCH:                return SI_LANGUAGE_DUTCH;
        case LANGUAGE_NORWEGIAN:            return SI_LANGUAGE_NORWEGIAN;
        case LANGUAGE_POLISH:               return SI_LANGUAGE_POLISH;
        case LANGUAGE_PORTUGUESE:           return SI_LANGUAGE_PORTUGUESE;
        case LANGUAGE_RUSSIAN:              return SI_LANGUAGE_RUSSIAN;
        case LANGUAGE_ROMANIAN:             return SI_LANGUAGE_ROMANIAN;
        case LANGUAGE_SLOVENIAN:            return SI_LANGUAGE_SLOVENIAN;
        case LANGUAGE_SERBIAN:              return SI_LANGUAGE_SERBIAN;
        case LANGUAGE_FINNISH:              return SI_LANGUAGE_FINNISH;
        case LANGUAGE_SWEDISH:              return SI_LANGUAGE_SWEDISH;
        case LANGUAGE_BULGARIAN:            return SI_LANGUAGE_BULGARIAN;
        case LANGUAGE_SLOVAK:               return SI_LANGUAGE_SLOVAK;
        case LANGUAGE_CHINESE:              return SI_LANGUAGE_CHINESE;
        case LANGUAGE_CHINESE_TRAD:         return SI_LANGUAGE_CHINESE_TRAD;
        case LANGUAGE_THAI:                 return SI_LANGUAGE_THAILAND;
        case LANGUAGE_GAELIC:               return SI_LANGUAGE_GAELIC;
        case LANGUAGE_AKAN:                 return SI_LANGUAGE_AKAN;
        case LANGUAGE_EWE:                  return SI_LANGUAGE_EWE;
        case LANGUAGE_TWI:                  return SI_LANGUAGE_TWI;
        case LANGUAGE_NZEMA:                return SI_LANGUAGE_NZEMA;
        case LANGUAGE_HAUSA:                return SI_LANGUAGE_HAUSA;
        case LANGUAGE_KASEM:                return SI_LANGUAGE_KASEM;
        case LANGUAGE_WELSH:                return SI_LANGUAGE_WELSH;
        case LANGUAGE_IRISH:                return SI_LANGUAGE_IRISH;
        case LANGUAGE_TURKISH:              return SI_LANGUAGE_TURKISH;
        case LANGUAGE_NETHERLANDS:          return SI_LANGUAGE_NETHERLANDS;
        case LANGUAGE_GALLEGAN:             return SI_LANGUAGE_GALLEGAN;
        case LANGUAGE_BASQUE:               return SI_LANGUAGE_BASQUE;
        case LANGUAGE_LUXEMBOURGISH:        return SI_LANGUAGE_LUXEMBOURGISH;
        case LANGUAGE_ICELANDIC:            return SI_LANGUAGE_ICELANDIC;
        case LANGUAGE_LATVIAN:              return SI_LANGUAGE_LATVIAN;
        case LANGUAGE_ESTONIAN:             return SI_LANGUAGE_ESTONIAN;
        case LANGUAGE_LITHUANIAN:           return SI_LANGUAGE_LITHUANIAN;
        case LANGUAGE_UKRANIAN:             return SI_LANGUAGE_UKRANIAN;
        case LANGUAGE_BELARUSIAN:           return SI_LANGUAGE_BELARUSIAN;
        case LANGUAGE_SPANISH_CAT:          return SI_LANGUAGE_SPANISH_CAT;
        case LANGUAGE_SAMI:                 return SI_LANGUAGE_SAMI;
        case LANGUAGE_ARABIC:               return SI_LANGUAGE_ARABIC;
        case LANGUAGE_HEBREW:               return SI_LANGUAGE_HEBREW;
        case LANGUAGE_KOREAN:               return SI_LANGUAGE_KOREAN;
        case LANGUAGE_JAPAN:                return SI_LANGUAGE_JAPAN;
        case LANGUAGE_HINDI:                return SI_LANGUAGE_HINDI;
        case LANGUAGE_MANDARIN:             return SI_LANGUAGE_MANDARIN;
        case LANGUAGE_CANTONESE:            return SI_LANGUAGE_CANTONESE;
        case LANGUAGE_MAORI:                return SI_LANGUAGE_MAORI;
        case LANGUAGE_TAMIL:                return SI_LANGUAGE_TAMIL;
        case LANGUAGE_INDONESIA:            return SI_LANGUAGE_INDONESIA;
        case LANGUAGE_MALAYSIA:             return SI_LANGUAGE_MALAYSIA;
        case LANGUAGE_VIETNAM:              return SI_LANGUAGE_VIETNAM;
        case LANGUAGE_SWAHILI:              return SI_LANGUAGE_SWAHILI;
        case LANGUAGE_MYANMAR:              return SI_LANGUAGE_MYANMAR;
        case LANGUAGE_UND:                  return SI_LANGUAGE_UND;
        case LANGUAGE_QAA:                  return SI_LANGUAGE_QAA;
        case LANGUAGE_QAB:                  return SI_LANGUAGE_QAB;
        case LANGUAGE_QAC:                  return SI_LANGUAGE_QAC;
        case LANGUAGE_UNKNOWN:              return SI_LANGUAGE_UNKNOWN;

        default:
            ASSERT(0);
        return SI_LANGUAGE_UNKNOWN;
    }
}
EN_LANGUAGE MApp_GetLanguageBySILanguage(EN_SI_LANGUAGE eLanguage)
{
    switch(eLanguage)
    {
        case SI_LANGUAGE_CZECH:             return LANGUAGE_CZECH;
        case SI_LANGUAGE_DANISH:            return LANGUAGE_DANISH;
        case SI_LANGUAGE_GERMAN:            return LANGUAGE_GERMAN;
        case SI_LANGUAGE_ENGLISH:           return LANGUAGE_ENGLISH;
        case SI_LANGUAGE_SPANISH:           return LANGUAGE_SPANISH;
        case SI_LANGUAGE_GREEK:             return LANGUAGE_GREEK;
        case SI_LANGUAGE_FRENCH:            return LANGUAGE_FRENCH;
        case SI_LANGUAGE_CROATIAN:          return LANGUAGE_CROATIAN;
        case SI_LANGUAGE_ITALIAN:           return LANGUAGE_ITALIAN;
        case SI_LANGUAGE_HUNGARIAN:         return LANGUAGE_HUNGARIAN;
        case SI_LANGUAGE_DUTCH:             return LANGUAGE_DUTCH;
        case SI_LANGUAGE_NORWEGIAN:         return LANGUAGE_NORWEGIAN;
        case SI_LANGUAGE_POLISH:            return LANGUAGE_POLISH;
        case SI_LANGUAGE_PORTUGUESE:        return LANGUAGE_PORTUGUESE;
        case SI_LANGUAGE_RUSSIAN:           return LANGUAGE_RUSSIAN;
        case SI_LANGUAGE_ROMANIAN:          return LANGUAGE_ROMANIAN;
        case SI_LANGUAGE_SLOVENIAN:         return LANGUAGE_SLOVENIAN;
        case SI_LANGUAGE_SERBIAN:           return LANGUAGE_SERBIAN;
        case SI_LANGUAGE_FINNISH:           return LANGUAGE_FINNISH;
        case SI_LANGUAGE_SWEDISH:           return LANGUAGE_SWEDISH;
        case SI_LANGUAGE_BULGARIAN:         return LANGUAGE_BULGARIAN;
        case SI_LANGUAGE_SLOVAK:            return LANGUAGE_SLOVAK;
        case SI_LANGUAGE_CHINESE:           return LANGUAGE_CHINESE;
        case SI_LANGUAGE_CHINESE_TRAD:      return LANGUAGE_CHINESE_TRAD;
        case SI_LANGUAGE_GAELIC:            return LANGUAGE_GAELIC;
        case SI_LANGUAGE_AKAN:              return LANGUAGE_AKAN;
        case SI_LANGUAGE_EWE:               return LANGUAGE_EWE;
        case SI_LANGUAGE_TWI:               return LANGUAGE_TWI;
        case SI_LANGUAGE_NZEMA:             return LANGUAGE_NZEMA;
        case SI_LANGUAGE_HAUSA:             return LANGUAGE_HAUSA;
        case SI_LANGUAGE_KASEM:             return LANGUAGE_KASEM;
        case SI_LANGUAGE_WELSH:             return LANGUAGE_WELSH;
        case SI_LANGUAGE_IRISH:             return LANGUAGE_IRISH;
        case SI_LANGUAGE_TURKISH:           return LANGUAGE_TURKISH;
        case SI_LANGUAGE_NETHERLANDS:       return LANGUAGE_NETHERLANDS;
        case SI_LANGUAGE_GALLEGAN:          return LANGUAGE_GALLEGAN;
        case SI_LANGUAGE_BASQUE:            return LANGUAGE_BASQUE;
        case SI_LANGUAGE_LUXEMBOURGISH:     return LANGUAGE_LUXEMBOURGISH;
        case SI_LANGUAGE_ICELANDIC:         return LANGUAGE_ICELANDIC;
        case SI_LANGUAGE_LATVIAN:           return LANGUAGE_LATVIAN;
        case SI_LANGUAGE_ESTONIAN:          return LANGUAGE_ESTONIAN;
        case SI_LANGUAGE_LITHUANIAN:        return LANGUAGE_LITHUANIAN;
        case SI_LANGUAGE_UKRANIAN:          return LANGUAGE_UKRANIAN;
        case SI_LANGUAGE_BELARUSIAN:        return LANGUAGE_BELARUSIAN;
        case SI_LANGUAGE_SPANISH_CAT:       return LANGUAGE_SPANISH_CAT;
        case SI_LANGUAGE_SAMI:              return LANGUAGE_SAMI;
        case SI_LANGUAGE_ARABIC:            return LANGUAGE_ARABIC;
        case SI_LANGUAGE_HEBREW:            return LANGUAGE_HEBREW;
        case SI_LANGUAGE_KOREAN:            return LANGUAGE_KOREAN;
        case SI_LANGUAGE_JAPAN:             return LANGUAGE_JAPAN;
        case SI_LANGUAGE_HINDI:             return LANGUAGE_HINDI;
        case SI_LANGUAGE_MANDARIN:          return LANGUAGE_MANDARIN;
        case SI_LANGUAGE_CANTONESE:         return LANGUAGE_CANTONESE;
        case SI_LANGUAGE_MAORI:             return LANGUAGE_MAORI;
        case SI_LANGUAGE_TAMIL:             return LANGUAGE_TAMIL;
        case SI_LANGUAGE_INDONESIA:         return LANGUAGE_INDONESIA;
        case SI_LANGUAGE_MALAYSIA:          return LANGUAGE_MALAYSIA;
        case SI_LANGUAGE_VIETNAM:           return LANGUAGE_VIETNAM;
        case SI_LANGUAGE_SWAHILI:           return LANGUAGE_SWAHILI;
        case SI_LANGUAGE_MYANMAR:           return LANGUAGE_MYANMAR;
        case SI_LANGUAGE_UND:               return LANGUAGE_UND;
        case SI_LANGUAGE_QAA:               return LANGUAGE_QAA;
        case SI_LANGUAGE_QAB:               return LANGUAGE_QAB;
        case SI_LANGUAGE_QAC:               return LANGUAGE_QAC;
        case SI_LANGUAGE_SGA:               return LANGUAGE_SGA;
        case SI_LANGUAGE_THAILAND:          return LANGUAGE_THAI;
        case SI_LANGUAGE_UNKNOWN:           return LANGUAGE_UNKNOWN;
        case SI_LANGUAGE_NONE:              return LANGUAGE_UNKNOWN;

        default:
            ASSERT(0);
        return LANGUAGE_UNKNOWN;
    }
}
#endif

#if (ENABLE_NONLINEAR_CURVE)
U8 MApp_NonLinearCalculate(P_MS_USER_NONLINEAR_CURVE pNonLinearCurve, U8 AdjustValue)
{
    //dual direction
    BYTE rValue,ucY0,ucY1,ucX0,ucX1,ucIntercept;
    WORD wDistanceOfY, wDistanceOfX;

    //if (AdjustValue < stNonLinearCurve.u8OSD_25)
    if (AdjustValue < 25)
    {
          ucY0 = pNonLinearCurve->u8OSD_0;
          ucY1 = pNonLinearCurve->u8OSD_25;
          ucX0 = 0;
          ucX1 = 25;
    }
    //else if (AdjustValue < stNonLinearCurve.u8OSD_50)
    else if (AdjustValue < 50)
    {
          ucY0 = pNonLinearCurve->u8OSD_25;
          ucY1 = pNonLinearCurve->u8OSD_50;
          ucX0 = 25;
          ucX1 = 50;
    }
    //else if (AdjustValue < stNonLinearCurve.u8OSD_75)
    else if (AdjustValue < 75)
    {
          ucY0 = pNonLinearCurve->u8OSD_50;
          ucY1 = pNonLinearCurve->u8OSD_75;
          ucX0 = 50;
          ucX1 = 75;
    }
    else
    {
          ucY0 = pNonLinearCurve->u8OSD_75;
          ucY1 = pNonLinearCurve->u8OSD_100;
          ucX0 = 75;
          ucX1 = 100;
    }

    if (ucY1 > ucY0)
    {
        wDistanceOfY = ucY1 - ucY0;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY0;
        AdjustValue  = AdjustValue - ucX0;
    }
    else
    {
        wDistanceOfY = ucY0 - ucY1;
        wDistanceOfX = ucX1 - ucX0;
        ucIntercept  = ucY1;
        AdjustValue  = ucX1 - AdjustValue;
    }

 // printf("wDistanceOfY %u\n", wDistanceOfY);
 // printf("wDistanceOfX %u\n", wDistanceOfX);
 // printf("ucIntercept %bu\n", ucIntercept);
 // printf("AdjustValue %bu\n", AdjustValue);

    rValue = ((WORD)wDistanceOfY*AdjustValue/(wDistanceOfX)) + ucIntercept;
    return rValue;
}

P_MS_USER_NONLINEAR_CURVE MApp_GetNonLinearCurve(EN_MS_NONLINEAR_CURVE eNonLinearCurveIndex)
{
    P_MS_USER_NONLINEAR_CURVE pNonLinearCurve = NULL;

    switch(eNonLinearCurveIndex)
    {
#if(ENABLE_SOUND_NONLINEAR_CURVE)
        case NONLINEAR_CURVE_VOLUME:
#if ENABLE_DTV
            if(IsDTVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVSoundCurve);
            else
#endif
            if(IsATVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVSoundCurve);
            else if(IsStorageInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StorageSoundCurve);
            else
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVSoundCurve);
            break;
#endif

#if(ENABLE_PICTURE_NONLINEAR_CURVE)
        case NONLINEAR_CURVE_CONTRAST:
#if ENABLE_DTV
            if(IsDTVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else
#endif
            if(IsATVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else if(IsAVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else if(IsSVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.SVPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else if(IsYPbPrInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.YPbPrPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else if(IsHDMIInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.HDMIPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else if(IsVgaInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.PCPictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else if(IsStorageInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StoragePictureCurve[NONLINEAR_CURVE_CONTRAST]);
            else
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_CONTRAST]);

            break;
        case NONLINEAR_CURVE_BRIGHTNESS:
#if ENABLE_DTV
            if(IsDTVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else
#endif
            if(IsATVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else if(IsAVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else if(IsSVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.SVPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else if(IsYPbPrInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.YPbPrPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else if(IsHDMIInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.HDMIPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else if(IsVgaInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.PCPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else if(IsStorageInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StoragePictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);
            else
               pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_BRIGHTNESS]);

            break;
        case NONLINEAR_CURVE_SATURATION:
#if ENABLE_DTV
            if(IsDTVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else
#endif
            if(IsATVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else if(IsAVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else if(IsSVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.SVPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else if(IsYPbPrInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.YPbPrPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else if(IsHDMIInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.HDMIPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else if(IsVgaInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.PCPictureCurve[NONLINEAR_CURVE_SATURATION]);
            else if(IsStorageInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StoragePictureCurve[NONLINEAR_CURVE_SATURATION]);
            else
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_SATURATION]);
            break;
        case NONLINEAR_CURVE_SHARPNESS:
#if ENABLE_DTV
            if(IsDTVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else
#endif
            if(IsATVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else if(IsAVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else if(IsSVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.SVPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else if(IsYPbPrInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.YPbPrPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else if(IsHDMIInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.HDMIPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else if(IsVgaInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.PCPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else if(IsStorageInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StoragePictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            else
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_SHARPNESS]);
            break;

        case NONLINEAR_CURVE_HUE:
#if ENABLE_DTV
            if(IsDTVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVPictureCurve[NONLINEAR_CURVE_HUE]);
            else
#endif
            if(IsATVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVPictureCurve[NONLINEAR_CURVE_HUE]);
            else if(IsAVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_HUE]);
            else if(IsSVInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.SVPictureCurve[NONLINEAR_CURVE_HUE]);
            else if(IsYPbPrInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.YPbPrPictureCurve[NONLINEAR_CURVE_HUE]);
            else if(IsHDMIInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.HDMIPictureCurve[NONLINEAR_CURVE_HUE]);
            else if(IsVgaInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.PCPictureCurve[NONLINEAR_CURVE_HUE]);
            else if(IsStorageInUse())
                pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StoragePictureCurve[NONLINEAR_CURVE_HUE]);
            else
              pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_HUE]);
            break;

            case NONLINEAR_CURVE_BACKLIGHT:
#if ENABLE_DTV
                if(IsDTVInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.DTVPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else
#endif
                if(IsATVInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.ATVPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else if(IsAVInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else if(IsSVInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.SVPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else if(IsYPbPrInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.YPbPrPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else if(IsHDMIInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.HDMIPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else if(IsVgaInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.PCPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else if(IsStorageInUse())
                    pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.StoragePictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                else
                  pNonLinearCurve = &(stGenSetting.g_NonLinearCurveSetting.AVPictureCurve[NONLINEAR_CURVE_BACKLIGHT]);
                break;
#endif
    }

    return pNonLinearCurve;
}
#endif

BOOLEAN MApp_IsImageFrozen()
{
    return g_bIsImageFrozen;
}

void MApp_SetImageFrozen(BOOLEAN bFrozen)
{
    g_bIsImageFrozen = bFrozen;
}

BOOL MApp_IsInputSrcUseAVD(BOOL bWindow )
{
    if( bWindow >= 2 )
        return FALSE;

    if( IsSrcTypeDigitalVD(SYS_INPUT_SOURCE_TYPE(bWindow)) )
    {
        return TRUE;
    }

    return FALSE;
}

BOOL MApp_IsInputSrcUseHDMIPort(BOOL bWindow )
{
    if( bWindow >= 2 )
        return FALSE;

    if( IsSrcTypeHDMI(SYS_INPUT_SOURCE_TYPE(bWindow)) )
    {
        return TRUE;
    }

    return FALSE;
}

#define FATAL_ERROR_DISPLAY_TIME (2000)

void MApp_Fatal_Error(char *msg, const char *func)
{
    printf(ANSI_COLOR_RED     "Fatal Error: %s %s()"     ANSI_COLOR_RESET "\n", msg, func);
    printf(ANSI_COLOR_RED     "Fatal Error: %s %s()"     ANSI_COLOR_RESET "\n", msg, func);
    printf(ANSI_COLOR_RED     "Fatal Error: %s %s()"     ANSI_COLOR_RESET "\n", msg, func);
    msAPI_Timer_Delayms(FATAL_ERROR_DISPLAY_TIME);
}



#if (ENABLE_ATSC)
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_Psip.h"

#define DBG_VideoDescription(x)     //x
static U16 u16AudioStreamType;
static U8 u8AudioLanguageType;

#if ENABLE_ATV_CHANNEL_CHANGE_FINETUNING
static BOOLEAN bIsChannelChangeProcessing = FALSE;
#endif


static void MApp_GetDefaultAudioSoundTrackPID(U16 *pu16AudioPID, U8 u8AudioLangIdx)
{
    U8 u8Loop_i;
    if ((astgSoundTrack[u8AudioLangIdx].u8AudAc3Bsmod == EN_PSIP_AC3_BSMOD_VI)) //vi
    {
        for ( u8Loop_i = 0; u8Loop_i < pstVirtualCh->u8AudLangNum; u8Loop_i++ )
        {
            if ((astgSoundTrack[u8AudioLangIdx].u16AudStreamType == astgSoundTrack[u8Loop_i].u16AudStreamType)
                && (astgSoundTrack[u8Loop_i].u8AudAc3Bsmod == EN_PSIP_AC3_BSMOD_CM)) //main
            {
                    *pu16AudioPID = astgSoundTrack[u8Loop_i].u16AudioPid;
                    return;
            }
        }
    }
}

//*************************************************************************
//Function name:    MApp_GetAudioSoundTrackPID
//Passing parameter:    U8 u8CurrentSelect  current selected sound track
//Return parameter:     U16 audio PID
//Description:      get audio PID according to sound track
//*************************************************************************
U16 MApp_GetAudioSoundTrackPID( U8 u8CurrentSelect )
{
    DEBUG_ATSC_AUDIO_SYS( printf("MApp_GetAudioSoundTrackPID(u8CurrentSelect=%u)\n", u8CurrentSelect); );

    u16AudioStreamType = astgSoundTrack[u8CurrentSelect].u16AudStreamType;
    DEBUG_ATSC_AUDIO_STREAM_TYPE( printf("u16AudioStreamType=%u\n", u16AudioStreamType); );

    u8AudioLanguageType = astgSoundTrack[u8CurrentSelect].u8AudLangIdx;
    return astgSoundTrack[u8CurrentSelect].u16AudioPid;
}

//Select Process
U8 MApp_ReMapAudioLanguage_SelectProcess(BOOLEAN bSelectProcess)
{
    BOOLEAN bFound = FALSE;
    U8 u8AudLangSelected = 0;

    DBG_VideoDescription(printf("\033[42;30m  [Select process] bSelectProcess=%u, u8CandidateAudioNum=%u \033[0m\n", bSelectProcess, u8CandidateAudioNum));

    if (bSelectProcess)
    {
        if(u8CandidateAudioNum == 1)
        {
            u8AudLangSelected = u8CandidateAudioIndex[0];
        }
        else
        {
            //2 11.2.2.2.1. Select process by Priority value
            for(iu8Loop_i = 0; iu8Loop_i< u8CandidateAudioNum; iu8Loop_i++)
            {
                if(astgSoundTrack[u8CandidateAudioIndex[iu8Loop_i]].u8Priority == 0x01)
                {
                    u8AudLangSelected = u8CandidateAudioIndex[iu8Loop_i];
                    bFound = TRUE;
                    break;
                }
            }

            //2 11.2.2.2.2. Select process by listed order
            if (!bFound)
            {
                if (iu8Loop_i == u8CandidateAudioNum)
                {
                    u8AudLangSelected = u8CandidateAudioIndex[0];
                }
            }
        }
    }
    else
    {
        //no candidate audio sound tracks
        //2 11.2.2.2.1. Select process by Priority value
        for(iu8Loop_i = 0; iu8Loop_i< MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum; iu8Loop_i++)
        {
            if(astgSoundTrack[iu8Loop_i].u8Priority ==0x01)
            {
                u8AudLangSelected = iu8Loop_i;
                bFound = TRUE;
                break;
            }
        }

        //2 11.2.2.2.2. Select process by listed order
        if (!bFound)
        {
            for(iu8Loop_i = 0; iu8Loop_i< MApp_ChanProc_GetCurChannelPointer()->u8AudLangNum; iu8Loop_i++)
            {
                DBG_VideoDescription(printf("\033[45;37m [%u] u16AudLangIdx=%u, Bsmod=[%u] u8AudLangNum=%u, u8IsAudLangGetinPMT=%u \033[0m\n",iu8Loop_i
                                                                                                                        ,astgSoundTrack[iu8Loop_i].u16AudLangIdx
                                                                                                                        , (U8)astgSoundTrack[iu8Loop_i].u8AudAc3Bsmod
                                                                                                                        , MApp_ChanProc_GetCurChannelSoundTrackPointer()->u8AudLangNum
                                                                                                                        ,astgSoundTrack[iu8Loop_i].u8IsAudLangGetinPMT));

                if ((astgSoundTrack[iu8Loop_i].u8AudAc3Bsmod == EN_PSIP_AC3_BSMOD_NUM) //no ac3ad descriptor
                    && ((!astgSoundTrack[iu8Loop_i].u16IsAudLangGetinPMT)&&(astgSoundTrack[iu8Loop_i].u8AudLangIdx == AUD_LANG_UND)))  //no ¡§language¡¨ and ¡§ISO_639_language¡¨ exists
                {
                    continue;
                }

                u8AudLangSelected = iu8Loop_i;
                break;
            }
        }
    }

    return u8AudLangSelected;
}


//*************************************************************************
//Function name:    MApp_GetAudioSoundTrackPID
//Passing parameter:    none
//Return parameter:     U16    audio stream type
//Description:      get audio stream type according to sound track
//*************************************************************************
//U16 MApp_GetAudioStreamType ( void )
EN_AUD_STREAM_TYPE MApp_ATSC_Get_AudioStreamType(void)
{
    if( u16AudioStreamType > AUD_STREAM_TYPE_NUMS )
    {
        printf("\nWarning: u16AudioStreamType=%u!\n", u16AudioStreamType);
    }

    return (EN_AUD_STREAM_TYPE)u16AudioStreamType;
}

void MApp_ATSC_ReMapAudioLanguage(void)
{
    EN_ADUIO_LAN enAudLangNum = SOUND_AUDIO_LAN_NUM;

    DEBUG_ATSC_AUDIO_SYS( printf("MApp_ATSC_ReMapAudioLanguage()\n"); );

    //memset( astgSoundTrack, 0, sizeof(MS_SOUND_TRACK_ATSC)*MAX_AUD_LANG_NUM );
    memset( astgSoundTrack, 0, sizeof(astgSoundTrack) );

    //iu8Loop_i = 0;
    U8 u8SrcAuLangIdx;

    //iu8Loop_j = 0;
    U8 u8DestAuLangIdx = 0;

    // Start sorting: Eng, Fre, Spa, Other
    for(enAudLangNum = SOUND_AUDIO_LAN_ENGLISH; enAudLangNum < SOUND_AUDIO_LAN_NUM; enAudLangNum++)
    {
        //for(iu8Loop_i = 0; iu8Loop_i< pstVirtualCh->u8AudLangNum; iu8Loop_i++)
        for(u8SrcAuLangIdx = 0; u8SrcAuLangIdx < pstVirtualCh->u8AudLangNum; u8SrcAuLangIdx ++)
        {
            //if(pstVirtualCh->astSoundTrack[iu8Loop_i].u8AudLangIdx == enAudLangNum)
            if( pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx == enAudLangNum )
            {
                //memcpy( &astgSoundTrack[iu8Loop_j],&pstVirtualCh->astSoundTrack[iu8Loop_i],sizeof( MS_SOUND_TRACK_ATSC ) );
                memcpy( &astgSoundTrack[u8DestAuLangIdx],&pstVirtualCh->astSoundTrack[u8SrcAuLangIdx],sizeof( MS_SOUND_TRACK_ATSC ) );
                //iu8Loop_j ++;
                u8DestAuLangIdx ++;
            }
        }

        //if(iu8Loop_j==pstVirtualCh->u8AudLangNum)
        if( u8DestAuLangIdx == pstVirtualCh->u8AudLangNum )
            return;
    }

    // other language.....
    //for(iu8Loop_i = 0; iu8Loop_i< pstVirtualCh->u8AudLangNum; iu8Loop_i++)
    for(u8SrcAuLangIdx = 0; u8SrcAuLangIdx < pstVirtualCh->u8AudLangNum; u8SrcAuLangIdx ++)
    {
        if( (pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx != SOUND_AUDIO_LAN_ENGLISH)&&
            (pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx != SOUND_AUDIO_LAN_FRENCH)&&
            (pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx != SOUND_AUDIO_LAN_SPANISH)&&
            (pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx != SOUND_AUDIO_LAN_KOREA)&&
            (pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx != SOUND_AUDIO_LAN_JAPAN)&&
            (pstVirtualCh->astSoundTrack[u8SrcAuLangIdx].u8AudLangIdx != SOUND_AUDIO_LAN_CHINESE)
        )
        {
            //memcpy( &astgSoundTrack[iu8Loop_j],&pstVirtualCh->astSoundTrack[iu8Loop_i],sizeof( MS_SOUND_TRACK_ATSC ) );
            memcpy( &astgSoundTrack[u8DestAuLangIdx], &pstVirtualCh->astSoundTrack[u8SrcAuLangIdx], sizeof( MS_SOUND_TRACK_ATSC ) );

            //iu8Loop_j ++;
            u8DestAuLangIdx ++;
        }
    }
}

U16 MApp_SetPreferAudioSoundTrackPIDNew(void)
{
    U16 u16AudioPID_temp = 0;

    //PRINT_CURRENT_LINE();
    DEBUG_ATSC_AUDIO_SYS( printf("MApp_SetPreferAudioSoundTrackPIDNew()\n"); );

    for ( iu8Loop_i = 0; iu8Loop_i < pstVirtualCh->u8AudLangNum; iu8Loop_i++ )
    {
        if ( astgSoundTrack[iu8Loop_i].u8AudLangIdx == stGenSetting.g_SoundSetting.enSoundAudioLan )
        {
            if ( astgSoundTrack[iu8Loop_i].u8AudPidInPMT )
            {
                u16AudioStreamType = astgSoundTrack[iu8Loop_i].u16AudStreamType;
                DEBUG_ATSC_AUDIO_STREAM_TYPE( printf("2 u16AudioStreamType=%u\n", u16AudioStreamType); );

                u8AudioLanguageType = astgSoundTrack[iu8Loop_i].u8AudLangIdx;
                u16AudioPID_temp = astgSoundTrack[iu8Loop_i].u16AudioPid;
                g_u8AudLangSelected = iu8Loop_i;
#if (ENABLE_AUDIO_LANGUAGE_HOT_KEY)
          stGenSetting.g_SoundSetting.u8AudioLanguageNumber = g_u8AudLangSelected;
#endif
                return u16AudioPID_temp;
            }
        }
    }

    //set default lauguage Audio Info
    u16AudioStreamType = astgSoundTrack[0].u16AudStreamType;
    DEBUG_ATSC_AUDIO_STREAM_TYPE( printf("3 u16AudioStreamType=%u\n", u16AudioStreamType); );

    u8AudioLanguageType = astgSoundTrack[0].u8AudLangIdx;
    u16AudioPID_temp = astgSoundTrack[0].u16AudioPid;
    g_u8AudLangSelected = 0;

#if (ENABLE_AUDIO_LANGUAGE_HOT_KEY)
    stGenSetting.g_SoundSetting.u8AudioLanguageNumber = g_u8AudLangSelected;
#endif

    return u16AudioPID_temp;

}

U16 MApp_SetPreferAudioSoundTrackPID(U8 u8Enable)
{
    U16 u16AudioPID_temp = 0;
    BOOLEAN bViFound = FALSE;

    DEBUG_ATSC_AUDIO_SYS( printf("MApp_SetPreferAudioSoundTrackPID(u8Enable=%u)\n", u8Enable); );

    //Get prefer lauguage Audio Info
    for ( iu8Loop_i = 0; iu8Loop_i < pstVirtualCh->u8AudLangNum; iu8Loop_i++ )
    {
        //if ( astgSoundTrack[iu8Loop_i].u8AudLangIdx == stGenSetting.g_SoundSetting.enSoundAudioLan )
        if(astgSoundTrack[iu8Loop_i].u8AudAc3Bsmod == EN_PSIP_AC3_BSMOD_VI)
        {
            bViFound = TRUE;
            if ( astgSoundTrack[iu8Loop_i].u8AudPidInPMT )
            {
                u16AudioStreamType = astgSoundTrack[iu8Loop_i].u16AudStreamType;
                DEBUG_ATSC_AUDIO_STREAM_TYPE( printf("4 u16AudioStreamType=%u\n", u16AudioStreamType); );

                u8AudioLanguageType = astgSoundTrack[iu8Loop_i].u8AudLangIdx;
                u16AudioPID_temp = astgSoundTrack[iu8Loop_i].u16AudioPid;
                g_u8AudLangSelected = iu8Loop_i;

            #if (ENABLE_AUDIO_LANGUAGE_HOT_KEY)
                stGenSetting.g_SoundSetting.u8AudioLanguageNumber = g_u8AudLangSelected;
            #endif

                if (u8Enable)
                {
                    MApp_GetDefaultAudioSoundTrackPID(&u16AudioPID_temp, iu8Loop_i);
                }
                return u16AudioPID_temp;
            }
        }
    }

    //if not found vi language...select the language track which ui selected
    if(bViFound == FALSE)
    {
        for ( iu8Loop_i = 0; iu8Loop_i < pstVirtualCh->u8AudLangNum; iu8Loop_i++)
        {
            if ( astgSoundTrack[iu8Loop_i].u8AudLangIdx == stGenSetting.g_SoundSetting.enSoundAudioLan )
            {
                {
                    u16AudioStreamType = astgSoundTrack[iu8Loop_i].u16AudStreamType;
                    DEBUG_ATSC_AUDIO_STREAM_TYPE( printf("5 u16AudioStreamType=%u\n", u16AudioStreamType); );

                    u8AudioLanguageType = astgSoundTrack[iu8Loop_i].u8AudLangIdx;
                    u16AudioPID_temp = astgSoundTrack[iu8Loop_i].u16AudioPid;
                    g_u8AudLangSelected = iu8Loop_i;

                #if (ENABLE_AUDIO_LANGUAGE_HOT_KEY)
                    stGenSetting.g_SoundSetting.u8AudioLanguageNumber = g_u8AudLangSelected;
                #endif

                    if (u8Enable)
                    {
                        MApp_GetDefaultAudioSoundTrackPID(&u16AudioPID_temp, iu8Loop_i);
                    }
                    return u16AudioPID_temp;
                }
            }
        }
    }


    //set default lauguage Audio Info
    u16AudioStreamType = astgSoundTrack[0].u16AudStreamType;
    DEBUG_ATSC_AUDIO_STREAM_TYPE( printf("6 u16AudioStreamType=%u\n", u16AudioStreamType); );

    u8AudioLanguageType = astgSoundTrack[0].u8AudLangIdx;
    u16AudioPID_temp = astgSoundTrack[0].u16AudioPid;
    g_u8AudLangSelected = 0;
#if (ENABLE_AUDIO_LANGUAGE_HOT_KEY)
    stGenSetting.g_SoundSetting.u8AudioLanguageNumber = g_u8AudLangSelected;
#endif

    if (u8Enable)
    {
        MApp_GetDefaultAudioSoundTrackPID(&u16AudioPID_temp, 0);
    }
    return u16AudioPID_temp;
}


void MApp_SetChChangeState(BOOLEAN bChProcess)
{
    bIsChannelChangeProcessing = bChProcess;
}

BOOLEAN MApp_GetChChangeState(void)
{
    return bIsChannelChangeProcessing;
}

void MApp_Set2DefaultDate ( ST_TIME *pstDate )
{
    pstDate->u16Year = DEFAULT_YEAR;
    pstDate->u8Month = DEFAULT_MONTH;
    pstDate->u8Day = DEFAULT_DAY_ATSC;
    pstDate->u8Hour = DEFAULT_HOUR;
    pstDate->u8Min = DEFAULT_MIN;
    pstDate->u8Sec = DEFAULT_SEC;
}

#if ENABLE_ATSC
//*************************************************************************
//Function name:    MApp_ConvertDate2Seconds
//Passing parameter:    ST_TIME *pstDate :  date got from TDT
//Return parameter:     U32 u32TotalSeconds : total secounds
//Description:      calculate total seconds which starts from the default date
//*************************************************************************
/* the base time starts from DEFAULT_YEAR/DEFAULT_MONTH/DEFAULT_DAY DEFAULT_HOUR:DEFAULT_MIN:DEFAULT_SEC*/
U32 MApp_ConvertDate2Seconds ( ST_TIME *pstDate )
{
    U32 u32TotalSeconds;
    U16 u16Year;

    u32TotalSeconds = 0;
    u16Year =  pstDate->u16Year;

    /* sec */
    u32TotalSeconds += pstDate->u8Sec;

    /* min */
    u32TotalSeconds += pstDate->u8Min * SECONDS_PER_MIN;

    /* hour */
    u32TotalSeconds += pstDate->u8Hour * SECONDS_PER_HOUR;

    /* day */
    u32TotalSeconds += ( pstDate->u8Day - 1 ) * SECONDS_PER_DAY;

    /* month */
    u32TotalSeconds += SolarDays[MApp_GetLeap( u16Year ) * 14 + pstDate->u8Month - 1] * SECONDS_PER_DAY;

    /* year */
    while ( u16Year > DEFAULT_YEAR )
    {
        u16Year--;
        u32TotalSeconds += MApp_GetDaysOfThisYear( u16Year ) * SECONDS_PER_DAY;
    }

    u32TotalSeconds -=  (DEFAULT_DAY_ATSC-1) *SECONDS_PER_DAY;

    //   u32TotalSeconds += DEFAULT_SYSTEM_TIME;

    return u32TotalSeconds;
}
#endif
//*************************************************************************
//Function name:    MApp_ConvertLocalTime2Date
//Passing parameter:    S32 s32SystemTime : system time + offset time
//              ST_TIME *pstDate : local date
//Return parameter:     none
//Description:      Calculate local date
//*************************************************************************
/* the base time starts from 2005/1/1 00:00:00 */
void MApp_ConvertLocalTime2Date ( S32 s32SystemTime, ST_TIME *pstDate )
{
    U16 u16TotalDays, u16Days;

    /* set to base date */
    MApp_Set2DefaultDate( pstDate );

    /* s32SystemTime = total accumulative seconds from base date */
    if ( s32SystemTime > 0 )
    {
        /* sec */
        pstDate->u8Sec = s32SystemTime % SECONDS_PER_MIN;
        s32SystemTime -= pstDate->u8Sec;

        /* min */
        pstDate->u8Min = ( s32SystemTime / SECONDS_PER_MIN ) % MINS_PER_HOUR;
        s32SystemTime -= pstDate->u8Min * SECONDS_PER_MIN;

        /* hour */
        pstDate->u8Hour = ( s32SystemTime / SECONDS_PER_HOUR ) % HOURS_PER_DAY;
        s32SystemTime -= pstDate->u8Hour * SECONDS_PER_HOUR;

        /* days */
        u16TotalDays = s32SystemTime / SECONDS_PER_DAY
                       + (U16)SolarDays[MApp_GetLeap( pstDate->u16Year ) * 14 + pstDate->u8Month - 1]
                       + (U16)pstDate->u8Day - 1;

        /* year */
        u16Days = MApp_GetDaysOfThisYear( pstDate->u16Year );
        while ( u16TotalDays >= u16Days )
        {
            u16TotalDays -= u16Days;
            pstDate->u16Year++;
            u16Days = MApp_GetDaysOfThisYear( pstDate->u16Year );
        }

        /* month */
        u16Days = MApp_GetDaysOfThisMonth( pstDate->u16Year, pstDate->u8Month );
        pstDate->u8Month = 1;
        while ( u16TotalDays >= u16Days )
        {
            u16TotalDays -= u16Days;
            pstDate->u8Month++;
            u16Days = MApp_GetDaysOfThisMonth( pstDate->u16Year, pstDate->u8Month );
        }

        /* day */
        pstDate->u8Day = ( U8 ) u16TotalDays + 1;
    }

}

// for V-Chip and Input-Block use only...........
void MApp_MuteAvByLock(E_SCREEN_MUTE_STATUS eScreenMute, BOOLEAN bMuteEnable)
{
    U16 u16AudioMuteClient_On = 0;
    U16 u16AudioMuteClient_Off = 0;

    //PRINT_CURRENT_LINE();
    //printf("MApp_MuteAvByLock(u8ScreenMute=0x%X, bMuteEnable=%u)\n", eScreenMute, bMuteEnable);


    if( eScreenMute == E_SCREEN_MUTE_BY_VCHIP )
    {
        u16AudioMuteClient_On = E_AUDIO_BYVCHIP_MUTEON;
        u16AudioMuteClient_Off = E_AUDIO_BYVCHIP_MUTEOFF;
    }
    else if( eScreenMute == E_SCREEN_MUTE_BY_UI )
    {
        u16AudioMuteClient_On = E_AUDIO_UI_FUNC_MUTEON;
        u16AudioMuteClient_Off = E_AUDIO_UI_FUNC_MUTEOFF;
    }
    else
    {
        printf("\nWarning: MApp_MuteAvByLock not support eScreenMute=0x%X\n", eScreenMute);
        return;
    }


    //if ( u8ScreenMute & (E_SCREEN_MUTE_RATING|E_SCREEN_MUTE_INPUT) )
    {
        if (bMuteEnable) // Enable mute
        {
            // mute the aduio.......
            msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, u16AudioMuteClient_On, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            //MApi_AUDIO_SPDIF_SetMute(TRUE);

            // mute the video.......
            msAPI_Scaler_SetScreenMute( eScreenMute, ENABLE, NULL, MAIN_WINDOW);
            //msAPI_Scaler_SetCVBSMute(ENABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),OUTPUT_CVBS1);

        #if ENABLE_ATV_CHANNEL_CHANGE_FINETUNING
            MApp_SetChChangeState(FALSE);
        #endif
        }
        else // Unmute
        {
            // mute the aduio.......
            //if( (!g_bInputBlocked) && ( !MApp_VChip_GetCurVChipBlockStatus()) )
            {
                // un-mute the video.......
                //if (MApp_IsSrcHasSignal(MAIN_WINDOW))
                {
                    //msAPI_Scaler_SetBlueScreen(DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                    //msAPI_Scaler_SetCVBSMute(DISABLE,  E_VE_MUTE_GEN,SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW),OUTPUT_CVBS1);
                }

                //MApi_AUDIO_SPDIF_SetMute(FALSE);
                /*
                if( !MApp_Aud_GetUserMuteStatus() )
                {
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYBLOCK_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                else
                {
                     msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, E_AUDIO_BYBLOCK_MUTEOFF, E_AUDIOMUTESOURCE_ACTIVESOURCE);
                }
                */
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE, u16AudioMuteClient_Off, E_AUDIOMUTESOURCE_ACTIVESOURCE);
            }

            // un-mute the video.......
            msAPI_Scaler_SetScreenMute( eScreenMute, DISABLE, NULL, MAIN_WINDOW);

        }
    }
}

#endif // ENABLE_ATSC

#if(ENABLE_ATSC)
BOOL MApp_Is_InAutoScan_ATSC(void)
{
    if( IsAtscInUse() || IsATVInUse() )
    {
        if( (MApp_TopStateMachine_GetTopState() == STATE_TOP_ATSC_SCAN )
    #if(ENABLE_ATSC_SCAN_NEW_MODE)
         || (MApp_TopStateMachine_GetTopState() == STATE_TOP_DTV_MANUAL_TUNING )
    #endif
        )
        {
            return TRUE;
        }
    }
    return FALSE;
}
#endif

BOOL MApp_Is_InAutoScan_ATV(void)
{
    if( IsATVInUse() )
    {
        EN_TOP_STATE enCurTopState = MApp_TopStateMachine_GetTopState();

        if( (enCurTopState == STATE_TOP_ATV_SCAN)
        #if ENABLE_SBTVD_ATV_SYSTEM
          ||(enCurTopState == STATE_TOP_CATV_SCAN)
        #endif
          ||(enCurTopState == STATE_TOP_ATV_MANUAL_TUNING)
          )
        {
            return TRUE;
        }
    }
    return FALSE;
}

BOOL MApp_Is_InAutoScan_DTV(void)
{
#if(ENABLE_ATSC)
    if( MApp_Is_InAutoScan_ATSC() )
    {
        return TRUE;
    }
    else
#endif
    {
#if(ENABLE_DTV)
    #if ENABLE_DVB
        if( IsDVBInUse() )
        {
            EN_TOP_STATE enCurTopState = MApp_TopStateMachine_GetTopState();
            if( (enCurTopState == STATE_TOP_DTV_SCAN)
              ||(enCurTopState == STATE_TOP_DTV_MANUAL_TUNING)
            #if ENABLE_DVBC
              ||(enCurTopState == STATE_TOP_CADTV_MANUAL_TUNING)
            #endif
              )
            {
                return TRUE;
            }
        }
    #endif
#endif
    }

    return FALSE;
}

BOOL MApp_Is_InFactoryMode(void)
{
    if( MApp_ZUI_GetActiveOSD() == E_OSD_FACTORY_MENU )
        return TRUE;

    return FALSE;
}

//===================================================================
#if( ENABLE_DTV )
DMX_FILTER_STATUS MApp_Demux_Stop_Filter_Audio(void)
{
    DMX_FILTER_STATUS eDMX_FILTER_STATUS = DMX_FILTER_STATUS_OK;

#if(ENABLE_ATSC)
    if( IsAtscInUse()|| IsATVInUse() )
    {

    }
    else
#endif
#if(ENABLE_DVB)
    if( IsDVBInUse() )
    {
        eDMX_FILTER_STATUS = msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_AUDIO_FID) );
    }
    else
#endif
    {
        // Do nothing
    }

    return eDMX_FILTER_STATUS;
}

DMX_FILTER_STATUS MApp_Demux_Start_Filter_Audio(U16 u16Pid)
{
    DMX_FILTER_STATUS eDMX_FILTER_STATUS = DMX_FILTER_STATUS_OK;

    u16Pid=u16Pid;

#if(ENABLE_ATSC)
    if( IsAtscInUse()|| IsATVInUse() )
    {

    }
    else
#endif
#if(ENABLE_DVB)
    if( IsDVBInUse() )
    {
        eDMX_FILTER_STATUS = msAPI_DMX_StartFilter( u16Pid, MSAPI_DMX_FILTER_TYPE_AUDIO, MApp_Dmx_GetFid(EN_AUDIO_FID));
    }
    else
#endif
    {
        // Do nothing
    }

    return eDMX_FILTER_STATUS;
}

DMX_FILTER_STATUS MApp_Demux_Stop_Filter_AudioDesc(void)
{
    DMX_FILTER_STATUS eDMX_FILTER_STATUS = DMX_FILTER_STATUS_OK;

#if(ENABLE_ATSC)
    if( IsAtscInUse()|| IsATVInUse() )
    {

    }
    else
#endif
#if(ENABLE_DVB)
    if( IsDVBInUse() )
    {
        eDMX_FILTER_STATUS = msAPI_DMX_Stop( *MApp_Dmx_GetFid(EN_AD_FID) );
    }
    else
#endif
    {
        // Do nothing
    }

    return eDMX_FILTER_STATUS;
}

DMX_FILTER_STATUS MApp_Demux_Start_Filter_AudioDesc(U16 u16Pid)
{
    DMX_FILTER_STATUS eDMX_FILTER_STATUS = DMX_FILTER_STATUS_OK;

    u16Pid=u16Pid;

#if(ENABLE_ATSC)
    if( IsAtscInUse()|| IsATVInUse() )
    {

    }
    else
#endif
#if(ENABLE_DVB)
    if( IsDVBInUse() )
    {
        eDMX_FILTER_STATUS = msAPI_DMX_StartFilter(u16Pid, MSAPI_DMX_FILTER_TYPE_AUDIO2, MApp_Dmx_GetFid(EN_AD_FID));
    }
    else
#endif
    {
        // Do nothing
    }

    return eDMX_FILTER_STATUS;
}
#endif

#if ENABLE_FM_RADIO
BOOLEAN MApp_Is_CruSrcFMRadio(void)
{
    if(UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_FMRADIO)
    {
        return TRUE;
    }

    return FALSE;
}
#endif

// For coverity test
BOOLEAN MApp_AlwaysReturnTrue(void)
{
    return TRUE;
}

//******************************************************************************

#undef MAPP_GLOBAL_FUNCTION_C

