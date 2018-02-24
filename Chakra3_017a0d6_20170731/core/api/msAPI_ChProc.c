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
// (MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
/// @file msAPI_ChProc.h
/// This file includes MStar Channel processing Application interface
/// @brief API for Channel Process
/// @author MStar Semiconductor, Inc.
///
////////////////////////////////////////////////////////////////////////////////
#include "Board.h"

#include "datatype.h"
#include "MsCommon.h"
#include "Utl.h"

#include "apiXC.h"
//#include "apiXC_Adc.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_ChProc.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_audio.h"
#include "msAPI_VD.h"
#include "msAPI_Tuning.h"
#include "msAPI_Timer.h"

#include "MApp_ATVProc.h"
#include "MApp_GlobalFunction.h"



#define DEBUG_CH_PROC(x)        //x
#define DEBUG_CH_PROC_FAV(x)    //x


#if ENABLE_CHPROC_ORDINAL_LIST

#if( ENABLE_DVBS )
    #define CHPROC_MAX_DTV_NUM  MAX_DTV_S2_PROGRAM
#elif ( ENABLE_DVBT && ENABLE_DVBC && DVB_T_C_DIFF_DB )
  #if(MAX_DTVPROGRAM_DVBC > MAX_DTVPROGRAM) )
    #define CHPROC_MAX_DTV_NUM  MAX_DTVPROGRAM_DVBC
  #else
    #define CHPROC_MAX_DTV_NUM  MAX_DTVPROGRAM
  #endif
#else
    #define CHPROC_MAX_DTV_NUM  MAX_DTVPROGRAM
#endif

#define MAX_ATV_DTV         (MAX_ATVPROGRAM + CHPROC_MAX_DTV_NUM)

//===========================================================

typedef enum
{
    CH_PROC_SORT_DTV_RADIO_DATA_ATV,
    CH_PROC_SORT_DTV_LCN__ATV,
} EnuChProcSortType;

static EnuChProcSortType g_ChProc_eSortType = CH_PROC_SORT_DTV_RADIO_DATA_ATV;


typedef struct
{
    union
    {
        U16 u16LCN; // For DTV

        U16 u16ProgramNumber; // For ATV

    #if ENABLE_SBTVD_DTV_SYSTEM
        ST_LCN stLCN;
    #endif
    };

    U16 wPosition;

    MEMBER_SERVICETYPE eServicetype : 3;
    U8 bIsFav       : 1;

} StruOrdinalInfo;

#define IS_ORDINAL_LIST_ENABLE      msAPI_SRC_IS_SBTVD_InUse()

#endif

//=======================================================================
#ifdef INVALID_PROGRAM_POSITION
    #define INVALID_POSITION    INVALID_PROGRAM_POSITION
#else
    #define INVALID_POSITION    0xFFFF
#endif


//****************************************************************************
// Private attributes of this file.
//****************************************************************************
#if ENABLE_CHPROC_ORDINAL_LIST
static StruOrdinalInfo aOridinalList[MAX_ATV_DTV];
static WORD wMAX_OridinalCount;
#endif

//****************************************************************************
// Private functions of this file.
//****************************************************************************

#if(!ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
static WORD _GetNextFavoriteOrdinalOfUnitedTV(WORD wBaseOrdinal, BOOLEAN bIncludeSkipped);
#endif

BOOLEAN msAPI_CHPROC_CM_Get_Attr_Favor_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary);


#if ENABLE_CHPROC_ORDINAL_LIST
static BOOLEAN SwapOridinal(WORD wFromOrder, WORD wToOrder);
//static void Set_MAXOridinal(WORD u16Max_Ori);
//static WORD Get_MAXOridinal(void);
//static WORD msAPI_CHPROC_CM_GetOrdinal_Brazil(MEMBER_SERVICETYPE bServiceType,WORD wPosition);
//static void msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(WORD wOridinal,MEMBER_SERVICETYPE * pbServiceType,WORD * pwPosition);
#endif

//****************************************************************************
// Start of public implementation
//****************************************************************************
#if ENABLE_CHPROC_ORDINAL_LIST
#define DEBUG_ORD_LIST(x)   x

static void Set_MAXOridinal(WORD wMax_Ori)
{
    if(wMax_Ori > MAX_ATV_DTV)
    {
        __ASSERT(0);
        wMax_Ori = MAX_ATV_DTV;
    }

    wMAX_OridinalCount = wMax_Ori;
}

static WORD Get_MAXOridinal(void)
{
    if(wMAX_OridinalCount > MAX_ATV_DTV)
    {
        __ASSERT(0);
        wMAX_OridinalCount = MAX_ATV_DTV;
    }

    return wMAX_OridinalCount;
}

MEMBER_SERVICETYPE msAPI_CHPROC_ORD_Get_ServiceType(U16 u16Ordinal)
{
    if( u16Ordinal >= Get_MAXOridinal() )
        return E_SERVICETYPE_INVALID;

    return (MEMBER_SERVICETYPE)aOridinalList[u16Ordinal].eServicetype;
}

U16 msAPI_CHPROC_ORD_Get_Position(U16 u16Ordinal)
{
    if( u16Ordinal >= Get_MAXOridinal() )
        return INVALID_POSITION;

    return aOridinalList[u16Ordinal].wPosition;
}

U8 msAPI_CHPROC_ORD_Get_AtvProgNumber(U16 u16Ordinal)
{
    if( u16Ordinal >= Get_MAXOridinal() )
        return 0xFF;

    U8 u8ProgramNumber;

#if ENABLE_SBTVD_CM_APP
    if(IS_ORDINAL_LIST_ENABLE)
    {
        u8ProgramNumber = aOridinalList[u16Ordinal].wPosition >> 8;
    }
    else
#endif
    {
        u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(aOridinalList[u16Ordinal].wPosition);
    }

    return u8ProgramNumber;
}

U8 msAPI_CHPROC_ORD_Get_Attr_Favor(U16 u16Ordinal)
{
    if( u16Ordinal >= Get_MAXOridinal() )
        return 0;

    MEMBER_SERVICETYPE eServiceType = (MEMBER_SERVICETYPE)aOridinalList[u16Ordinal].eServicetype;
    U8 u8Favor = 0;

    switch( eServiceType )
    {
        case E_SERVICETYPE_ATV:
            {
                U8 u8ProgramNumber = msAPI_CHPROC_ORD_Get_AtvProgNumber(u16Ordinal);
                u8Favor = msAPI_ATV_IsProgramFavorite(u8ProgramNumber);
            }
            break;

    #if(ENABLE_DVB)
        case E_SERVICETYPE_DTV:
        case E_SERVICETYPE_RADIO:
        case E_SERVICETYPE_DATA:
            u8Favor = msAPI_CM_GetProgramAttribute(eServiceType, aOridinalList[u16Ordinal].wPosition, E_ATTRIBUTE_IS_FAVORITE);
            break;
    #endif

        default:
            break;
    }

    return u8Favor;
}

U8 msAPI_CHPROC_ORD_Get_Attr_Skiped(U16 u16Ordinal)
{
    if( u16Ordinal >= Get_MAXOridinal() )
        return 0;

    MEMBER_SERVICETYPE eServiceType = (MEMBER_SERVICETYPE)aOridinalList[u16Ordinal].eServicetype;
    U8 Skiped = 0;

    switch( eServiceType )
    {
        case E_SERVICETYPE_ATV:
            {
                U8 u8ProgramNumber = msAPI_CHPROC_ORD_Get_AtvProgNumber(u16Ordinal);
                Skiped = msAPI_ATV_IsProgramSkipped(u8ProgramNumber);
            }
            break;

    #if(ENABLE_DVB)
        case E_SERVICETYPE_DTV:
        case E_SERVICETYPE_RADIO:
        case E_SERVICETYPE_DATA:
            Skiped = msAPI_CM_GetProgramAttribute(eServiceType, aOridinalList[u16Ordinal].wPosition, E_ATTRIBUTE_IS_SKIPPED);
            break;
    #endif

        default:
            break;
    }

    return Skiped;
}

void msAPI_CHPROC_ORD_PrintOridialList(void)
{
    U16 u16OrdinalCount = Get_MAXOridinal();
    U16 u16Ordinal;

    printf("Ordinal Table[%u]:\n", u16OrdinalCount);
    for( u16Ordinal = 0; u16Ordinal < u16OrdinalCount; ++ u16Ordinal)
    {
        if( aOridinalList[u16Ordinal].eServicetype == E_SERVICETYPE_ATV )
        {
            printf("%3u ATV, Pos=%3u, LCN=%u, Fav=%u\n", u16Ordinal,
                aOridinalList[u16Ordinal].wPosition,
                aOridinalList[u16Ordinal].u16LCN,
                aOridinalList[u16Ordinal].bIsFav );
        }
        else
        {
            printf("%3u Ser=%u, Pos=%3u, LCN=%u, Fav=%u\n", u16Ordinal,
                aOridinalList[u16Ordinal].eServicetype,
                aOridinalList[u16Ordinal].wPosition,
                aOridinalList[u16Ordinal].u16LCN,
                aOridinalList[u16Ordinal].bIsFav );
        }
    }
}

U16 msAPI_CHPROC_ORD_Get_FirstFavoriteOrdinal(BOOLEAN bIncludeSkipped)
{
    DEBUG_CH_PROC_FAV( printf("msAPI_CHPROC_ORD_Get_FirstFavoriteOrdinal(bIncludeSkipped=%u)\n", bIncludeSkipped); );

    U16 u16OrdinalCount = Get_MAXOridinal();
    U16 u16Ordinal;


    for( u16Ordinal=0; u16Ordinal < u16OrdinalCount; u16Ordinal += 1 )
    {
        if( msAPI_CHPROC_ORD_Get_Attr_Favor(u16Ordinal) )
        {
            if( TRUE == bIncludeSkipped )
            {
                DEBUG_CH_PROC_FAV( printf(" ==> %u\n", u16Ordinal); );
                return u16Ordinal;
            }
            else // Check skiped flag
            {
                if( FALSE == msAPI_CHPROC_ORD_Get_Attr_Favor(u16Ordinal) )
                {
                    DEBUG_CH_PROC_FAV( printf(" ==> %u\n", u16Ordinal); );
                    return u16Ordinal;
                }
            }
        }
    }

    return INVALID_ORDINAL;
}

U16 msAPI_CHPROC_ORD_Get_NextFavoriteOrdinal(U16 u16BaseOrdinal, BOOLEAN bIncludeSkipped)
{
    DEBUG_CH_PROC_FAV( printf("msAPI_CHPROC_ORD_Get_NextFavoriteOrdinal(u16BaseOrdinal=%u, bIncludeSkipped=%u)\n", u16BaseOrdinal, bIncludeSkipped); );

    U16 u16OrdinalCountMax = Get_MAXOridinal();
    U16 u16OrdinalCount;
    U16 u16Ordinal;


    u16Ordinal = u16BaseOrdinal;

    for( u16OrdinalCount=0; u16OrdinalCount < u16OrdinalCountMax; u16OrdinalCount += 1 )
    {
        u16Ordinal = (u16Ordinal + 1) % u16OrdinalCountMax;

        if( msAPI_CHPROC_ORD_Get_Attr_Favor(u16Ordinal) )
        {
            if( TRUE == bIncludeSkipped )
            {
                DEBUG_CH_PROC_FAV( printf(" ==> %u\n", u16Ordinal); );
                return u16Ordinal;
            }
            else // Check skiped flag
            {
                if( FALSE == msAPI_CHPROC_ORD_Get_Attr_Favor(u16Ordinal) )
                {
                    DEBUG_CH_PROC_FAV( printf(" ==> %u\n", u16Ordinal); );
                    return u16Ordinal;
                }
            }
        }
    }

    return INVALID_ORDINAL;
}

#endif

U16 msAPI_CHPROC_CM_Get_TotalDtvProgramCount(E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    U16 u16ProgCount = 0;

    eBoundary=eBoundary;

#if (ENABLE_DVB)
    u16ProgCount = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)
                 + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary);

  #if NORDIG_FUNC //for Nordig Spec v2.0
    u16ProgCount += msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary);
  #endif
#endif

    return u16ProgCount;
}

U16 msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    U16 u16AtvCount = msAPI_ATV_GetActiveProgramCount();
    U16 u16UNITED_TV_Count = 0;

    eBoundary=eBoundary;

#if(ENABLE_DVB)
    // include DTV count
    u16UNITED_TV_Count = msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary);
#endif

  #if ENABLE_S2
    if( !IsS2InUse() )
  #endif
    {
        u16UNITED_TV_Count += u16AtvCount;
    }

    return u16UNITED_TV_Count;
}

/******************************************************************************/
/// -This function will get Current Ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param eBoundary \b IN: Boundary
/// - @see E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY
/// @return WORD: Current ordinal
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetCurrentOrdinal(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    U16 u16CurOrdinal = INVALID_ORDINAL;
    U16 u16CurAtvProgNumber = msAPI_ATV_GetCurrentProgramNumber();
#if(ENABLE_DVB||ENABLE_SBTVD_CM_APP)
    U16 u16CurPosition;
#endif

#if (!ENABLE_DVB)
    UNUSED(eBoundary);
#endif

#if (ENABLE_DVB)
    MEMBER_SERVICETYPE eCurDtvServiceType = msAPI_CM_GetCurrentServiceType();
#endif

    //PRINT_CURRENT_LINE();
    DEBUG_CH_PROC( printf("msAPI_CHPROC_CM_GetCurrentOrdinal(bServiceType=%u, eBoundary=%u)\n", bServiceType, eBoundary); );

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        u16CurOrdinal = msAPI_CM_GetCurrentPosition(bServiceType);
        break;
#endif

    case E_SERVICETYPE_ATV:
        u16CurOrdinal = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(u16CurAtvProgNumber);
        break;

    case E_SERVICETYPE_UNITED_TV:

    #if ENABLE_SBTVD_CM_APP
        if( ANT_CATV == msAPI_ATV_GetCurrentAntenna() )
        {
            u16CurOrdinal = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(u16CurAtvProgNumber);
            break;
        }
    #endif

    #if (ENABLE_DVB)
        if( TRUE == IsDTVInUse() )
        {
            if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
            {
                u16CurPosition = msAPI_CM_GetCurrentPosition(eCurDtvServiceType);
                u16CurOrdinal = msAPI_CM_GetListPositionbyPosition(u16CurPosition,eCurDtvServiceType);
                break;
            }

            if(eCurDtvServiceType==E_SERVICETYPE_RADIO)
            {
                if(0==msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary))
                {
                    u16CurOrdinal = INVALID_ORDINAL;
                    break;
                }

              #if ENABLE_SBTVD_CM_APP
                if(IS_ORDINAL_LIST_ENABLE)
                {
                    u16CurPosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_RADIO);
                    u16CurOrdinal = msAPI_CHPROC_CM_GetOrdinal_Brazil(E_SERVICETYPE_RADIO,u16CurPosition);
                }
                else
              #endif
                {
                    u16CurOrdinal = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_RADIO)
                                  + msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary);
                }
            }
          #if NORDIG_FUNC //for Nordig Spec v2.0
            else if(eCurDtvServiceType==E_SERVICETYPE_DATA)
            {
                if(0==msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary))
                {
                    u16CurOrdinal = INVALID_ORDINAL;
                    break;
                }

                u16CurOrdinal = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DATA)
                              + msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)
                              + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary);
            }
          #endif
            else // Service type = DTV
            {
                if(0==msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary))
                {
                    u16CurOrdinal = INVALID_ORDINAL;
                    break;
                }

              #if ENABLE_SBTVD_CM_APP
                if(IS_ORDINAL_LIST_ENABLE)
                {
                    u16CurPosition = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DTV);
                    u16CurOrdinal = msAPI_CHPROC_CM_GetOrdinal_Brazil(E_SERVICETYPE_DTV, u16CurPosition);
                }
                else
              #endif
                {
                    u16CurOrdinal = msAPI_CM_GetCurrentPosition(E_SERVICETYPE_DTV);
                }
            }
        }
        else
    #endif
        if( TRUE == IsATVInUse() )
        {
      #if ENABLE_SBTVD_CM_APP
            if(IS_ORDINAL_LIST_ENABLE)
            {
                u16CurPosition = msAPI_ATV_GetCurrentProgramNumber();
                u16CurOrdinal = msAPI_CHPROC_CM_GetOrdinal_Brazil(E_SERVICETYPE_ATV, u16CurPosition);
            }
            else
      #endif
            {
            #if (ENABLE_DVB)
                u16CurOrdinal = msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary)
                              + msAPI_ATV_ConvertProgramNumberToOrdinalNumber(u16CurAtvProgNumber);
            #else
                u16CurOrdinal = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(u16CurAtvProgNumber);
            #endif
            }
        }
        break;

    default:
        break;
    }

    DEBUG_CH_PROC( printf(" ==> u16CurOrdinal=%u\n", u16CurOrdinal); );

    return u16CurOrdinal;
}

void msAPI_CHPROC_CM_ChangeAtvProgram(void)
{
    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
    //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);

    msAPI_AVD_TurnOffAutoAV();

    msAPI_Tuner_ChangeProgram();

    //msAPI_VD_ClearSyncCheckCounter();
    msAPI_AVD_ClearAspectRatio();
}

/******************************************************************************/
/// -This function will set Current Ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wOrdinal \b IN: Current ordinal
/// @param eBoundary \b IN: Boundary
/// - @see E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY
/// @return FUNCTION_RESULT: Function execution result
/******************************************************************************/
BOOLEAN msAPI_CHPROC_CM_SetCurrentOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    DEBUG_CH_PROC( printf("msAPI_CHPROC_CM_SetCurrentOrdinal(bServiceType=%u, wOrdinal=%u, eBoundary=%u )\n", bServiceType, wOrdinal, eBoundary); );

  #if ENABLE_SBTVD_CM_APP
    if(ANT_CATV == msAPI_ATV_GetCurrentAntenna())
        bServiceType = E_SERVICETYPE_ATV;
  #endif

#if (!ENABLE_DVB)
    UNUSED(eBoundary);
#endif

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
            msAPI_CM_SetCurrentServiceType(bServiceType);
            msAPI_CM_SetCurrentPosition(bServiceType, wOrdinal);
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
        msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));

    #if 1
        msAPI_CHPROC_CM_ChangeAtvProgram();
    #else
        msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
        //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
        msAPI_AVD_TurnOffAutoAV();
        msAPI_Tuner_ChangeProgram();
        //msAPI_VD_ClearSyncCheckCounter();
        msAPI_AVD_ClearAspectRatio();
    #endif

        //return TRUE;
        break;

    case E_SERVICETYPE_UNITED_TV:  // Service Type Check..
#if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            MEMBER_SERVICETYPE  eServiceType;
            WORD   wPosition;
            BYTE   bPosition = INVALID_ATV_PROGRAM_NUMBER;

            msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(wOrdinal,(MEMBER_SERVICETYPE *)&eServiceType, (WORD *)&wPosition);
            if(eServiceType == E_SERVICETYPE_ATV)
                bPosition = (wPosition >> 8);

            switch(eServiceType)
            {
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DTV:
                //case E_SERVICETYPE_DATA:

                    msAPI_CM_SetCurrentServiceType(eServiceType);
                    msAPI_CM_SetCurrentPosition(eServiceType, wPosition);
                    break;

                case E_SERVICETYPE_ATV:
                default:
                    msAPI_ATV_SetCurrentProgramNumber(bPosition);

                #if 1
                    msAPI_CHPROC_CM_ChangeAtvProgram();
                #else
                    msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
                    msAPI_AVD_TurnOffAutoAV();
                    msAPI_Tuner_ChangeProgram();
                    //msAPI_VD_ClearSyncCheckCounter();
                    msAPI_AVD_ClearAspectRatio();
                #endif
                    break;
            }

            //return TRUE;
            break;
        }
        else
#endif // ENABLE_SBTVD_CM_APP
        {
            // Check if ordinal is valid?
            if( wOrdinal >= msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(eBoundary) )
            {
                // Invalid ordinal!
                return FALSE;
            }

        #if (ENABLE_DVB)
            // If ordinal is in DTV range
            if( wOrdinal < msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary) )
            {
                if( IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING) )
                {
                    WORD wPoistion;
                    MEMBER_SERVICETYPE eServicetype = E_SERVICETYPE_INVALID;
                    wPoistion = msAPI_CM_GetPositionbyListPosition(wOrdinal,&eServicetype);
                    msAPI_CM_SetCurrentServiceType(eServicetype);
                    msAPI_CM_SetCurrentPosition(eServicetype, wPoistion);
                    //return TRUE;
                    break;
                }

                U16 u16ProgCount_DTV = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary);
                U16 u16ProgCount_Radio = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary);

                if( wOrdinal < u16ProgCount_DTV )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV, wOrdinal);
                    //return TRUE;
                    break;
                }
                else if( wOrdinal < (u16ProgCount_DTV + u16ProgCount_Radio) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO, (wOrdinal - u16ProgCount_DTV));
                    //return TRUE;
                    break;
                }
              #if NORDIG_FUNC //for Nordig Spec v2.0
                else if( wOrdinal < (u16ProgCount_DTV + u16ProgCount_Radio + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
                {
                    msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
                    msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA, (wOrdinal - u16ProgCount_DTV - u16ProgCount_Radio));
                    //return TRUE;
                    break;
                }
              #endif
            }
            else
        #endif
            // ordinal is in ATV range?
            { // ATV program
          #if 1
                U16 u16AtvOridinal = wOrdinal - msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary);
                if( u16AtvOridinal >= msAPI_ATV_GetActiveProgramCount() )
                {
                    return FALSE;
                }

                U16 u16AtvProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(u16AtvOridinal);
                DEBUG_CH_PROC( printf("u16AtvOridinal=%u, u16AtvProgramNumber=%u\n", u16AtvOridinal, u16AtvProgramNumber); );

                msAPI_ATV_SetCurrentProgramNumber(u16AtvProgramNumber);
          #else
            #if NORDIG_FUNC //for Nordig Spec v2.0
                msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber((wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary))));
            #else
              #if (ENABLE_DVB)
                msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber((wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary))));
              #else
                msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber((wOrdinal)));
              #endif
            #endif
          #endif

            #if 1
                msAPI_CHPROC_CM_ChangeAtvProgram();
            #else
                msAPI_AUD_AdjustAudioFactor(E_ADJUST_AUDIOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_SIF, E_AUDIOMUTESOURCE_ATV);
                //BY 20090406 msAPI_VD_AdjustVideoFactor(E_ADJUST_VIDEOMUTE_DURING_LIMITED_TIME, DELAY_FOR_STABLE_TUNER);
                msAPI_AVD_TurnOffAutoAV();
                msAPI_Tuner_ChangeProgram();
                //msAPI_VD_ClearSyncCheckCounter();
                msAPI_AVD_ClearAspectRatio();
            #endif
                //return TRUE;
            }
        }
        break;

    default:
        return FALSE;
        break;
    }

    return TRUE;
}

/******************************************************************************/
/// -This function will set Move 2 Ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wOrdinal \b IN: Current ordinal
/// @param eBoundary \b IN: Boundary
/// - @see E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY
/// @return FUNCTION_RESULT: Function execution result
/******************************************************************************/
BOOLEAN msAPI_CHPROC_CM_SetMove2CurrentOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if (!ENABLE_DVB)
    UNUSED(eBoundary);
#endif
    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
    #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
    #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
            msAPI_CM_SetCurrentServiceType(bServiceType);
            msAPI_CM_SetCurrentPosition(bServiceType, wOrdinal);
            return TRUE;
        }
        break;
#endif
    case E_SERVICETYPE_ATV:
        msAPI_ATV_SetCurrentProgramNumber((BYTE)wOrdinal);
        return TRUE;

    case E_SERVICETYPE_UNITED_TV:  // Service Type Check..
#if (ENABLE_DVB)
        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DTV);
            msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DTV, wOrdinal);
            return TRUE;
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_RADIO);
            msAPI_CM_SetCurrentPosition(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary))); //CL191492    ,TRUE);
            return TRUE;
        }
        #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            msAPI_CM_SetCurrentServiceType(E_SERVICETYPE_DATA);
            msAPI_CM_SetCurrentPosition(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
            return TRUE;
        }
        #endif
        else
#endif
        {
            #if NORDIG_FUNC //for Nordig Spec v2.0
            msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber((wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary))));
            #else
#if (ENABLE_DVB)
            msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber((wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary))));
#else
            msAPI_ATV_SetCurrentProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber((wOrdinal)));
#endif

            #endif
            return TRUE;
        }
        break;

    default:
        break;
    }

    return FALSE;
}
/******************************************************************************/
/// -This function will count program
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param eBoundary \b IN: Boundary
/// - @see E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY
/// @return WORD: program count
/******************************************************************************/
WORD msAPI_CHPROC_CM_CountProgram(MEMBER_SERVICETYPE bServiceType, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    U16 u16ProgramCount = 0;

    UNUSED(eBoundary);

    DEBUG_CH_PROC( printf("msAPI_CHPROC_CM_CountProgram(bServiceType=%u, eBoundary=%u)\n", bServiceType, eBoundary); );

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        u16ProgramCount = msAPI_CM_CountProgram(bServiceType, eBoundary);
        break;
#endif

    case E_SERVICETYPE_ATV:
        u16ProgramCount = msAPI_ATV_GetActiveProgramCount();
        break;

    case E_SERVICETYPE_UNITED_TV:
        u16ProgramCount = msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(eBoundary);
        break;

    default:
        printf("\nWarning: Unsupported bServiceType=%u!\n", bServiceType);
        break;
    }

    DEBUG_CH_PROC( printf(" ==> u16ProgramCount=%u\n", u16ProgramCount); );

    return u16ProgramCount;
}

/******************************************************************************/
/// -This function will get next ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wBaseOrdinal \b IN: base ordinal
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// - TRUE: Include skipped program
/// - FALSE: Don't include
/// @return WORD: program count
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetNextOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped)
{
    //printf("msAPI_CHPROC_CM_GetNextOrdinal(bServiceType=%u, wBaseOrdinal=%u, bIncludeSkipped=%u)\n", bServiceType, wBaseOrdinal, bIncludeSkipped);

#if ENABLE_SBTVD_CM_APP
    if(IS_ORDINAL_LIST_ENABLE)
    {
        U16 u16MaxOridinal = Get_MAXOridinal();
        U16 i, u16TotalPgmCount;
        BOOLEAN bSkipCh;

        u16TotalPgmCount = msAPI_CHPROC_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        for(i=0; i<u16TotalPgmCount; i++)
        {
            if(wBaseOrdinal < (u16MaxOridinal-1))
                wBaseOrdinal++;
            else
                wBaseOrdinal = 0;

            if(bIncludeSkipped == TRUE)
            {
                return wBaseOrdinal;
            }
            else
            {
                bSkipCh = FALSE;
                if(msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wBaseOrdinal, (BYTE *)&bSkipCh, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_VISIBLE_ONLY) == TRUE)
                {
                    if(bSkipCh == FALSE)
                        return wBaseOrdinal;
                }
            }
        }
    }
    else
#endif
    {
#if (ENABLE_DVB)
        WORD wProgramPosition=0;
#endif
        BYTE cProgramNumber=0;

        switch(bServiceType)
        {
#if (ENABLE_DVB)
        case E_SERVICETYPE_RADIO:
        case E_SERVICETYPE_DTV:
      #if NORDIG_FUNC //for Nordig Spec v2.0
        case E_SERVICETYPE_DATA:
      #endif
          #if NORDIG_FUNC //for Nordig spec v2.0
            wProgramPosition = msAPI_CM_GetNextProgramPosition(bServiceType, wBaseOrdinal, bIncludeSkipped,E_ALL_LIST,(MEMBER_SERVICETYPE *)NULL);
          #else
            wProgramPosition = msAPI_CM_GetNextProgramPosition(bServiceType, wBaseOrdinal, bIncludeSkipped,(CHANNEL_LIST_TYPE)bServiceType,(MEMBER_SERVICETYPE *)NULL);
          #endif

            if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
                (wProgramPosition <= wBaseOrdinal) )
            {
                printf("=> INVALID_ORDINAL\n");
                return INVALID_ORDINAL;
            }
            else
            {
                //printf(" => wProgramPosition=%u)\n", wProgramPosition);
                return wProgramPosition;
            }
            break;
#endif

        case E_SERVICETYPE_ATV:
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetNextProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wBaseOrdinal), bIncludeSkipped));
            if( (cProgramNumber == INVALID_ATV_PROGRAM_NUMBER) ||
                (cProgramNumber <= (BYTE)wBaseOrdinal) )
            {
                printf("=> INVALID_ORDINAL\n");
                return INVALID_ORDINAL;
            }
            else
            {
                //printf(" => cProgramNumber=%u)\n", cProgramNumber);
                return (WORD) cProgramNumber;
            }
            break;

        default:
            break;

        }
    }

    printf("=> INVALID_ORDINAL\n");

    return INVALID_ORDINAL;
}

/******************************************************************************/
/// -This function will get previous ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wBaseOrdinal \b IN: base ordinal
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// - TRUE: Include skipped program
/// - FALSE: Don't include
/// @return WORD: program count
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetPrevOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped)
{
#if ENABLE_SBTVD_CM_APP
    if(IS_ORDINAL_LIST_ENABLE)
    {
        U16 u16MaxOridinal = Get_MAXOridinal();
        U16 i, u16TotalPgmCount;
        BOOLEAN bSkipCh;

        u16TotalPgmCount = msAPI_CHPROC_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
        for(i=0; i<u16TotalPgmCount; i++)
        {
            if(wBaseOrdinal > 0)
                wBaseOrdinal--;
            else
                wBaseOrdinal = u16MaxOridinal-1;

            if(bIncludeSkipped == TRUE)
            {
                return wBaseOrdinal;
            }
            else
            {
                bSkipCh = FALSE;
                if(msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wBaseOrdinal, (BYTE *)&bSkipCh, E_SERVICE_ATTR_SKIPPED, E_PROGACESS_INCLUDE_VISIBLE_ONLY) == TRUE)
                {
                    if(bSkipCh == FALSE)
                        return wBaseOrdinal;
                }
            }
        }
    }
    else
#endif
    {
    #if (ENABLE_DVB)
        WORD wProgramPosition;
    #endif
        BYTE cProgramNumber;
        switch(bServiceType)
        {
        #if (ENABLE_DVB)
        case E_SERVICETYPE_RADIO:
        case E_SERVICETYPE_DTV:
        #if NORDIG_FUNC //for Nordig Spec v2.0
        case E_SERVICETYPE_DATA:
        #endif
                    #if NORDIG_FUNC //for Nordig Spec v2.0
                    wProgramPosition = msAPI_CM_GetPrevProgramPosition(bServiceType, wBaseOrdinal, bIncludeSkipped, E_ALL_LIST, NULL);
                    #else
                    wProgramPosition = msAPI_CM_GetPrevProgramPosition(bServiceType, wBaseOrdinal, bIncludeSkipped, (CHANNEL_LIST_TYPE)bServiceType, NULL);
                    #endif
            if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
                (wProgramPosition >= wBaseOrdinal) )
            {
                return INVALID_ORDINAL;
            }
            else
            {
                return wProgramPosition;
            }
            break;
        #endif
        case E_SERVICETYPE_ATV:
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetPrevProgramNumber((BYTE)wBaseOrdinal, bIncludeSkipped));
            if( (cProgramNumber == INVALID_ATV_PROGRAM_NUMBER) ||
                (cProgramNumber >= (BYTE)wBaseOrdinal) )
            {
                return INVALID_ORDINAL;
            }
            else
            {
                return (WORD) cProgramNumber;
            }
            break;

        default:
            break;
        }
    }
    return INVALID_ORDINAL;
}

/******************************************************************************/
/// -This function will count favorite program
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @return WORD: favorite program count
/******************************************************************************/

#if(!ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
U16 msAPI_CHPROC_CM_Get_DtvFavorProgramCount_For_UNITED_TV(void)
{
    U16 u16ProgCount = 0;

#if (ENABLE_DVB)
    u16ProgCount = msAPI_CM_CountFavoriteProgram(E_SERVICETYPE_DTV)
                 + msAPI_CM_CountFavoriteProgram(E_SERVICETYPE_RADIO);

  #if NORDIG_FUNC //for Nordig Spec v2.0
    u16ProgCount += msAPI_CM_CountFavoriteProgram(E_SERVICETYPE_DATA);
  #endif
#endif

    return u16ProgCount;
}
#endif

#if(ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
BOOLEAN msAPI_CHPROC_CM_Is_FavorProgram(U16 u16Ordinal)
{
    BOOLEAN bIsFav = FALSE;

    if( FALSE == msAPI_CHPROC_CM_Get_Attr_Favor_ByOrdinal(E_SERVICETYPE_UNITED_TV, u16Ordinal, &bIsFav, E_PROGACESS_INCLUDE_ALL) )
    {
        return FALSE;
    }

    return bIsFav;
}
#endif

U16 msAPI_CHPROC_CM_Get_UnitedTv_FavorProgramCount(void)
{
#if(ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
    U16 u16OrdinalCount = msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(E_PROGACESS_INCLUDE_ALL);
    U16 u16ProgCount = 0;
    U16 u16Ordinal;

    for( u16Ordinal=0; u16Ordinal < u16OrdinalCount; u16Ordinal += 1 )
    {
        if( msAPI_CHPROC_CM_Is_FavorProgram(u16Ordinal) )
        {
            u16ProgCount += 1;
        }
    }

    return u16ProgCount;

#else

    U16 u16AtvCount = msAPI_ATV_GetTotalFavoriteProgramCount();
    U16 u16UNITED_TV_Count = 0;


#if(ENABLE_DVB)
    // include DTV count
    u16UNITED_TV_Count = msAPI_CHPROC_CM_Get_DtvFavorProgramCount_For_UNITED_TV();
#endif

  #if ENABLE_S2
    if( !IsS2InUse() )
  #endif
    {
        u16UNITED_TV_Count += u16AtvCount;
    }

    return u16UNITED_TV_Count;
#endif
}

WORD msAPI_CHPROC_CM_CountFavoriteProgram(MEMBER_SERVICETYPE bServiceType)  // ^
{
DEBUG_CH_PROC_FAV( printf("msAPI_CHPROC_CM_CountFavoriteProgram(bServiceType=%u)\n", bServiceType); );

    U16 u16FavorProgCount = 0;

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        u16FavorProgCount = msAPI_CM_CountFavoriteProgram(bServiceType);
        break;
#endif

    case E_SERVICETYPE_ATV:
        u16FavorProgCount = msAPI_ATV_GetTotalFavoriteProgramCount();
        break;

    case E_SERVICETYPE_UNITED_TV: // DTV+Radio+(Data)+ATV
        u16FavorProgCount = msAPI_CHPROC_CM_Get_UnitedTv_FavorProgramCount();
        break;

    default:
        break;
    }

    DEBUG_CH_PROC_FAV( printf("=> %u\n", u16FavorProgCount); );

    return u16FavorProgCount;
}

/******************************************************************************/
/// -This function will get first favorite ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// - TRUE: Include skipped program
/// - FALSE: Don't include
/// @return WORD: First favorite program ordinal
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetFirstFavoriteOrdinal(MEMBER_SERVICETYPE bServiceType, BOOLEAN bIncludeSkipped)
{
DEBUG_CH_PROC_FAV( printf("msAPI_CHPROC_CM_GetFirstFavoriteOrdinal(bServiceType=%u, bIncludeSkipped=%u)\n", bServiceType, bIncludeSkipped); );

#if (ENABLE_DVB)
    WORD wProgramPosition = 0;
#endif
    BYTE cProgramNumber = 0;
#if (!ENABLE_DVB)
    UNUSED(bIncludeSkipped);
#endif

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(bServiceType, bIncludeSkipped);
        if( wProgramPosition != INVALID_PROGRAM_POSITION )
        {
            return wProgramPosition;
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
        cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
        if( cProgramNumber != INVALID_ATV_PROGRAM_NUMBER )
        {
            return (WORD) cProgramNumber;
        }
        break;

    case E_SERVICETYPE_UNITED_TV:

#if( ENABLE_DVB && ENABLE_CH_PROC_2015 )
    {
        return msAPI_CHPROC_ORD_Get_FirstFavoriteOrdinal(bIncludeSkipped);
    }

#elif( ENABLE_CHRPOC_NEW_FAVORITE_METHOD )
    {
        U16 u16OrdinalCount = msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(E_PROGACESS_INCLUDE_ALL);
        U16 u16Ordinal;
        DEBUG_CH_PROC_FAV( printf("u16OrdinalCount=%u\n", u16OrdinalCount); );

        for( u16Ordinal=0; u16Ordinal < u16OrdinalCount; u16Ordinal += 1 )
        {
            if( msAPI_CHPROC_CM_Is_FavorProgram(u16Ordinal) )
            {
                return u16Ordinal;
            }
        }
        return INVALID_ORDINAL;
    }

#else
#if ENABLE_SBTVD_CM_APP
        if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
        {
            U16 u16Loop;

            for(u16Loop=0;u16Loop<Get_MAXOridinal();u16Loop++)
            {
                if(aOridinalList[u16Loop].eServicetype == E_SERVICETYPE_ATV)
                {
                    if(TRUE == msAPI_ATV_IsProgramFavorite(aOridinalList[u16Loop].wPosition >> 8))
                        return  u16Loop;
                }
                else
                {
                    if(TRUE == msAPI_CM_GetProgramAttribute(aOridinalList[u16Loop].eServicetype,aOridinalList[u16Loop].wPosition,E_ATTRIBUTE_IS_FAVORITE))
                        return  u16Loop;
               }
            }
        }
        else
        {
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
            {
                return INVALID_ORDINAL;
            }
            else
            {
                return cProgramNumber;
            }
        }


#elif( ENABLE_DVB) //
        if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
        {
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPositionbylistpositon((MEMBER_SERVICETYPE *)&bServiceType,bIncludeSkipped);
            if(wProgramPosition == INVALID_PROGRAM_POSITION)
            {
                cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                if( cProgramNumber != INVALID_ATV_PROGRAM_NUMBER )
                {
#if NORDIG_FUNC //for Nordig Spec v2.0
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
#else
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
#endif
                }
            }
            return msAPI_CM_GetListPositionbyPosition(wProgramPosition,bServiceType);
        }

        wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
        if( wProgramPosition == INVALID_PROGRAM_POSITION )
        {
          #if NORDIG_FUNC //for Nordig Spec v2.0
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION )
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DATA, bIncludeSkipped);
                if( wProgramPosition == INVALID_PROGRAM_POSITION )
                {
                    cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                    if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                    {
                        return INVALID_ORDINAL;
                    }
                    else
                    {
                        return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                    }
                }
                else
                {
                    return wProgramPosition + msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
            }
            else
            {
                return wProgramPosition + msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            }
          #else
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION )
            {
                cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                {
                    return INVALID_ORDINAL;
                }
                else
                {
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                }
            }
            else
            {
                return wProgramPosition + msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
            }
          #endif
        }
        else
        {
            return wProgramPosition;
        }

#else
        { // ATVMM
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
            {
                return INVALID_ORDINAL;
            }
            else
            {
                return cProgramNumber;
            }
        }
#endif // ENABLE_SBTVD_CM_APP
#endif
        break;

    default:
        break;
    }

    return INVALID_ORDINAL;
}

/******************************************************************************/
/// -This function will get next favorite ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wBaseOrdinal \b IN: Base ordinal
/// @param bIncludeSkipped \b IN: Include skipped program or not
/// - TRUE: Include skipped program
/// - FALSE: Don't include
/// @return WORD: Next favorite program ordinal
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetNextFavoriteOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped)
{
DEBUG_CH_PROC_FAV( printf("msAPI_CHPROC_CM_GetNextFavoriteOrdinal(bServiceType=%u, wBaseOrdinal=%u, bIncludeSkipped=%u)\n", bServiceType, wBaseOrdinal, bIncludeSkipped); );
UNUSED(bIncludeSkipped);

#if (ENABLE_DVB)
    WORD wProgramPosition=0;
#endif
    BYTE cProgramNumber=0;

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPosition(bServiceType, wBaseOrdinal, bIncludeSkipped);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= wBaseOrdinal) )
        {
            return INVALID_ORDINAL;
        }
        else
        {
            return wProgramPosition;
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
      #if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wBaseOrdinal);
        }
        else
      #endif
        {
            cProgramNumber = (BYTE)wBaseOrdinal;
        }
        cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetNextFavoriteProgramNumber((BYTE)cProgramNumber));

        if( (cProgramNumber == INVALID_ATV_PROGRAM_NUMBER) ||
            (cProgramNumber <= (BYTE) wBaseOrdinal) )
        {
            return INVALID_ORDINAL;
        }
        else
        {
            return (WORD) cProgramNumber;
        }
        break;

    case E_SERVICETYPE_UNITED_TV:
    #if(ENABLE_DVB&&ENABLE_CH_PROC_2015)
        {
            return msAPI_CHPROC_ORD_Get_NextFavoriteOrdinal(wBaseOrdinal, bIncludeSkipped);
        }
    #elif(ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
        {
            U16 u16OrdinalCountMax = msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(E_PROGACESS_INCLUDE_ALL);
            DEBUG_CH_PROC_FAV( printf("wBaseOrdinal=%u, u16OrdinalCountMax=%u\n", wBaseOrdinal, u16OrdinalCountMax); );

            U16 u16OrdinalCount;
            U16 u16Ordinal;

            u16Ordinal = wBaseOrdinal;

            for( u16OrdinalCount=0; u16OrdinalCount < u16OrdinalCountMax; u16OrdinalCount += 1 )
            {
                u16Ordinal = (u16Ordinal + 1) % u16OrdinalCountMax;

                if( msAPI_CHPROC_CM_Is_FavorProgram(u16Ordinal) )
                {
                    //if( TRUE == bIncludeSkipped )
                    {
                        //DEBUG_CH_PROC_FAV( printf(" ==> %u\n", u16Ordinal); );
                        return u16Ordinal;
                    }
                }
            }
            return INVALID_ORDINAL;
        }
    #else
        {
            return _GetNextFavoriteOrdinalOfUnitedTV(wBaseOrdinal, bIncludeSkipped);
        }
    #endif
        break;

    default:
        break;
    }

    return INVALID_ORDINAL;
}


#if 0
/******************************************************************************/
/// -This function will get Similar ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wPressedNumber \b IN: Pressed Number
/// @param pwOrdinal \b IN: Ordinal
/// @param cSizeOfBuffer \b IN: Size Of Buffer
/// @return WORD: Similar program ordinal
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetSimilarOrdinals(MEMBER_SERVICETYPE bServiceType, WORD wPressedNumber, WORD * pwOrdinal, BYTE cSizeOfBuffer)
{
    WORD wProgramCount,wLoop,wTempOrdinal;
    WORD wOrdinal,wOrdina2,wMinOrdinal = 0,wMinOrder,wCompareOrdinal=0;
    WORD wServiceNumber = 0;
    BYTE acServiceNumber[4];
    BYTE acPressedNumber[4];
    BYTE cLength;
    BYTE cCursor;
    BYTE bVisibleFlag;
    BYTE bNumericSelection;

    cCursor = 0;

    cLength = _AlignDecimalToLeft(acPressedNumber, wPressedNumber);

    if( 0 < cLength )
    {
        wProgramCount = msAPI_CHPROC_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

        for(wOrdinal=0; wOrdinal < wProgramCount; wOrdinal++)
        {
            // Exclude Empty or Skiped Program
            if(TRUE == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, (BYTE *)&wServiceNumber, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
            {
                if(TRUE == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, &bVisibleFlag, E_SERVICE_ATTR_VISIBLE, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
                    && TRUE == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, &bNumericSelection, E_SERVICE_ATTR_NUMERIC, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
                {
                    if(FALSE == bVisibleFlag && FALSE == bNumericSelection)
                        continue;
                }

                if(wServiceNumber >= wPressedNumber)
                {
                    _AlignDecimalToLeft(acServiceNumber, wServiceNumber);
                    if( TRUE == _IsAlignedDecimalSame(acPressedNumber, acServiceNumber, cLength) )
                    {
                        pwOrdinal[cCursor] = wOrdinal;
                        cCursor++;
                        if( cSizeOfBuffer <= cCursor )
                        break;
                    }
                }
            }
        }
    }

    // Sorting
    for(wOrdinal=0; wOrdinal < cCursor; wOrdinal++)
    {
        msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, pwOrdinal[wOrdinal], (BYTE *)&wMinOrdinal, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
        wMinOrder = wOrdinal;
        for(wOrdina2=wOrdinal+1; wOrdina2 < cCursor; wOrdina2++)
        {
            msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, pwOrdinal[wOrdina2], (BYTE *)&wCompareOrdinal, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
            if(wCompareOrdinal < wMinOrdinal)
            {
                wMinOrdinal = wCompareOrdinal;
                wMinOrder = wOrdina2;
            }
            else if(wMinOrdinal == wCompareOrdinal)
            {

                if(pwOrdinal[wOrdina2] < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
                {
                    wMinOrdinal = wCompareOrdinal;
                    wMinOrder = wOrdina2;
                }
            }
        }

        if(wMinOrder != wOrdinal)
        {
            wTempOrdinal = pwOrdinal[wMinOrder];
            if(wMinOrder > wOrdinal)
            {
                for(wLoop=wMinOrder; wLoop > wOrdinal; wLoop--)
                    pwOrdinal[wLoop] = pwOrdinal[wLoop-1];
            }
            else
            {
                for(wLoop=wMinOrder; wLoop < wOrdinal; wLoop++)
                    pwOrdinal[wLoop] = pwOrdinal[wLoop+1];
            }
            pwOrdinal[wOrdinal] = wTempOrdinal;
        }
    }
    return cCursor;
}
#endif
/******************************************************************************/
/// -This function will get Matched ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param wPressedNumber \b IN: Pressed Number
/// @return WORD: Matched program ordinal
/******************************************************************************/
WORD msAPI_CHPROC_CM_GetMatchedOrdinals(MEMBER_SERVICETYPE bServiceType, WORD wPressedNumber)
{
    WORD wOrdinal;
    U16 u16DtvCount=0,u16RadioCount=0,u16AtvCount;
    #if NORDIG_FUNC //for Nordig Spec v2.0
    U16 u16DataCount=0;
    #endif
    U16 u16SearchFrom, u16SearchTo;
    U16 u16Number = 0;
#if (ENABLE_DVB)
    u16DtvCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
    u16RadioCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
    #if NORDIG_FUNC //for Nordig Spec v2.0
    u16DataCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
    #endif
#endif
    u16AtvCount = msAPI_CHPROC_CM_CountProgram(E_SERVICETYPE_ATV, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

  #if ENABLE_SBTVD_CM_APP
    if(IS_ORDINAL_LIST_ENABLE)
    {
        WORD wGotOridinal = 0;

        if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
        {
            wOrdinal=u16DtvCount =u16RadioCount=u16AtvCount=0;

          #if NORDIG_FUNC //for Nordig Spec v2.0
            u16DataCount=0;
          #endif
            u16SearchFrom=u16SearchTo=u16Number=0;

            if(bServiceType == msAPI_CHPROC_CM_GetServiceTypeByLCN_Brazil(wPressedNumber,(WORD *) &wGotOridinal))
                return wGotOridinal;
        }
        else
        {
            wPressedNumber--;
            for (wOrdinal = 0; wOrdinal <= msAPI_ATV_GetActiveProgramCount(); wOrdinal++)
            {
                msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

                if (u16Number == wPressedNumber)
                    return wOrdinal;
            }
        }
    }
    else
  #endif
    {
        #if(ENABLE_DVB)
        if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&((bServiceType == E_SERVICETYPE_DTV)||(bServiceType == E_SERVICETYPE_RADIO)||(bServiceType == E_SERVICETYPE_DATA)))
        {
            u16SearchFrom = 0;
            #if NORDIG_FUNC //for Nordig Spec v2.0
            u16SearchTo = u16DtvCount + u16RadioCount + u16DataCount;
            #else
            u16SearchTo = u16DtvCount + u16RadioCount;
            #endif
        }
        else
        #endif
            if(bServiceType == E_SERVICETYPE_DTV)
            {
                u16SearchFrom = 0;
                u16SearchTo = u16DtvCount;
            }
            else if(bServiceType == E_SERVICETYPE_RADIO)
            {
                u16SearchFrom = u16DtvCount;
                u16SearchTo = u16DtvCount + u16RadioCount;
            }
        #if NORDIG_FUNC //for Nordig Spec v2.0
            else if(bServiceType == E_SERVICETYPE_DATA)
            {
                u16SearchFrom = u16DtvCount + u16RadioCount;
                u16SearchTo = u16DtvCount + u16RadioCount + u16DataCount;
            }
        #endif
            else if(bServiceType == E_SERVICETYPE_ATV)
            {
                #if NORDIG_FUNC //for Nordig Spec v2.0
                u16SearchFrom = u16DtvCount + u16DataCount + u16RadioCount;
                u16SearchTo = u16DtvCount + u16DataCount + u16RadioCount + u16AtvCount;
                #else
                u16SearchFrom = u16DtvCount + u16RadioCount;
                u16SearchTo = u16DtvCount + u16RadioCount + u16AtvCount;
                #endif
            }
            else // bServiceType == E_SERVICETYPE_UNITED_TV
            {
                u16SearchFrom = 0;
                #if NORDIG_FUNC //for Nordig Spec v2.0
                u16SearchTo = u16DtvCount + u16DataCount + u16RadioCount + u16AtvCount;
                #else
                u16SearchTo = u16DtvCount + u16RadioCount + u16AtvCount;
                #endif
            }

        if(u16SearchFrom == u16SearchTo ) //channel number equal zero
            return INVALID_ORDINAL;
        else
            u16SearchTo--;

        if(bServiceType == E_SERVICETYPE_ATV)
            wPressedNumber--;
        for (wOrdinal = u16SearchFrom; wOrdinal <= u16SearchTo; wOrdinal++)
        {
#if(ENABLE_DVB)

            if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
            {
                msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wOrdinal-u16SearchFrom, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
            }
            else
#endif
            {
                msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal-u16SearchFrom, (BYTE*)&u16Number, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
            }
            if (u16Number == wPressedNumber)
            {
                return wOrdinal;
            }
        }
    }
    return INVALID_ORDINAL;
}
/*
// Sequencial search from DTV, Radio to ATV
WORD msAPI_CHPROC_CM_GetMatchedOrdinals(MEMBER_SERVICETYPE bServiceType, WORD wPressedNumber)
{
    WORD wProgramCount;
    WORD wOrdinal;
    WORD wServiceNumber;
    BYTE bVisibleFlag;
    BYTE bNumericSelection;
    MEMBER_SERVICETYPE eServiceType;

    wProgramCount = msAPI_CHPROC_CM_CountProgram(bServiceType, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
    for (wOrdinal=0; wOrdinal<wProgramCount; wOrdinal++)
    {
        if (E_RESULT_SUCCESS == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, (BYTE *)&wServiceNumber, E_SERVICE_ATTR_NUMBER, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
        {
            if(E_RESULT_SUCCESS == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, &bVisibleFlag, E_SERVICE_ATTR_VISIBLE, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO)
                && E_RESULT_SUCCESS == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, &bNumericSelection, E_SERVICE_ATTR_NUMERIC, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
            {
                if(FALSE == bVisibleFlag && FALSE == bNumericSelection)
                    continue;
            }

            if(E_RESULT_SUCCESS == msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType, wOrdinal, (BYTE *)&eServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO))
            {
                if(eServiceType == E_SERVICETYPE_ATV)
                   wServiceNumber++;
            }

            if (wServiceNumber == wPressedNumber)
            {
                return wOrdinal;
            }
        }
    }

    return INVALID_ORDINAL;
}*/


/******************************************************************************/
/// -This function will get Attribute Of ordinal
/// @param bServiceType \b IN: Service type
/// - @see MEMBER_SERVICETYPE
/// @param pwOrdinal \b IN: Ordinal
/// @param pcBuffer \b IN: pointer to Buffer for return
/// @param eAttributeMember \b IN: Attribute Member
/// - @see SERVICE_ATTRIBUTE_MEMBER
/// @param eBoundary \b IN: Boundary
/// - @see E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY
/// @return FUNCTION_RESULT: Function execution result
/******************************************************************************/
typedef enum
{
    E_CHPROC_DB_ATV,
#if (ENABLE_DVB)
    E_CHPROC_DB_DVB,
#endif
    E_CHPROC_DB_UNKNOWN,

} EnuChProcTvDBType;

EnuChProcTvDBType msAPI_CHPROC_CM_Get_DBTypeForUnitedTvOrdinal(U16 u16Ordinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if( ENABLE_CHPROC_ORDINAL_LIST )
//    UNUSED(eBoundary);

    if(IS_ORDINAL_LIST_ENABLE)
    {
        if( u16Ordinal >= Get_MAXOridinal() )
            return E_CHPROC_DB_UNKNOWN;

        switch(aOridinalList[u16Ordinal].eServicetype)
        {
        #if (ENABLE_DVB)
            case E_SERVICETYPE_DTV:
            case E_SERVICETYPE_RADIO:
            case E_SERVICETYPE_DATA:
                return E_CHPROC_DB_DVB;
                break;
        #endif

            case E_SERVICETYPE_ATV:
                return E_CHPROC_DB_ATV;
                break;

            default:
                break;
        }

        return E_CHPROC_DB_UNKNOWN;
    }
    else
#endif
    {
        if( u16Ordinal >= msAPI_CHPROC_CM_Get_UnitedTv_ProgramCount(eBoundary) )
            return E_CHPROC_DB_UNKNOWN;

      #if (ENABLE_DVB)
        if( u16Ordinal < msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary) )
            return E_CHPROC_DB_DVB;
      #endif

        return E_CHPROC_DB_ATV;
    }
}

typedef struct
{
    MEMBER_SERVICETYPE eServiceType;
    U16 u16Position;

} StruChProcProgIndex;

BOOL msAPI_CHPROC_CM_ConvertOrdinalToPosition(
    MEMBER_SERVICETYPE eServiceType, WORD u16Ordinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary,
    StruChProcProgIndex* pstChProcProgIndex )
{
    DEBUG_CH_PROC( printf("msAPI_CHPROC_CM_ConvertOrdinalToPosition(bServiceType=%u, u16Ordinal=%u, eBoundary=%u)\n", eServiceType, u16Ordinal, eBoundary); );

#if 1//ENABLE_SBTVD_CM_APP
    UNUSED(eBoundary);
#endif

    pstChProcProgIndex->eServiceType = E_SERVICETYPE_INVALID;

    pstChProcProgIndex->u16Position = INVALID_POSITION;

    switch(eServiceType)
    {
    #if (ENABLE_DVB)
        case E_SERVICETYPE_RADIO:
        case E_SERVICETYPE_DTV:
      #if NORDIG_FUNC //for Nordig Spec v2.0
        case E_SERVICETYPE_DATA:
      #endif
            pstChProcProgIndex->eServiceType = eServiceType;
            pstChProcProgIndex->u16Position = u16Ordinal;
            break;
    #endif

        case E_SERVICETYPE_ATV:
            pstChProcProgIndex->eServiceType = eServiceType;
            pstChProcProgIndex->u16Position = u16Ordinal;
            break;

        case E_SERVICETYPE_UNITED_TV:
        #if ENABLE_SBTVD_CM_APP
            if(IS_ORDINAL_LIST_ENABLE)
            {
                if( ANT_CATV == msAPI_ATV_GetCurrentAntenna() )
                {
                    pstChProcProgIndex->eServiceType = E_SERVICETYPE_ATV;
                    pstChProcProgIndex->u16Position = u16Ordinal;
                }
                else
                {
                    pstChProcProgIndex->eServiceType = msAPI_CHPROC_ORD_Get_ServiceType(u16Ordinal);
                    pstChProcProgIndex->u16Position = msAPI_CHPROC_ORD_Get_Position(u16Ordinal);
                }
            }
            else
        #elif(ENABLE_CHPROC_ORDINAL_LIST)
            {
                pstChProcProgIndex->eServiceType = msAPI_CHPROC_ORD_Get_ServiceType(u16Ordinal);
                pstChProcProgIndex->u16Position = msAPI_CHPROC_ORD_Get_Position(u16Ordinal);
            }
        #endif
            {
                EnuChProcTvDBType eChProcTvDBType = msAPI_CHPROC_CM_Get_DBTypeForUnitedTvOrdinal(u16Ordinal, eBoundary);
                if( eChProcTvDBType >= E_CHPROC_DB_UNKNOWN )
                {
                    pstChProcProgIndex->eServiceType = E_SERVICETYPE_ATV;
                    break;
                }
            #if (ENABLE_DVB)
                else if( eChProcTvDBType == E_CHPROC_DB_DVB )
                {
                    if( (IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
                      &&(u16Ordinal < msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary))
                      )
                    {
                        MEMBER_SERVICETYPE eServiceTypeResult;
                        pstChProcProgIndex->u16Position = msAPI_CM_GetPositionbyListPosition(u16Ordinal, &eServiceTypeResult);
                        if( pstChProcProgIndex->u16Position == INVALID_PROGRAM_POSITION )
                        { // Get position failed
                            break;
                        }
                        pstChProcProgIndex->eServiceType = eServiceTypeResult;
                    }
                    else
                    {
                        U16 u16DtvProgCount = msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary);
                        U16 u16DtvProgCount_Radio = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary);
                     #if (NORDIG_FUNC) //for Nordig Spec v2.0
                        U16 u16DtvProgCount_Data = msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary);
                     #endif

                        if( u16Ordinal < u16DtvProgCount )
                        {
                            pstChProcProgIndex->eServiceType = E_SERVICETYPE_DTV;
                            pstChProcProgIndex->u16Position = u16Ordinal;
                        }
                        else if( u16Ordinal < (u16DtvProgCount + u16DtvProgCount_Radio) )
                        {
                            pstChProcProgIndex->eServiceType = E_SERVICETYPE_RADIO;
                            pstChProcProgIndex->u16Position = u16Ordinal - u16DtvProgCount;
                        }
                      #if NORDIG_FUNC //for Nordig Spec v2.0
                        else if( u16Ordinal < (u16DtvProgCount + u16DtvProgCount_Radio + u16DtvProgCount_Data) )
                        {
                            pstChProcProgIndex->eServiceType = E_SERVICETYPE_DATA;
                            pstChProcProgIndex->u16Position = u16Ordinal - (u16DtvProgCount+u16DtvProgCount_Radio);
                        }
                      #endif
                        else
                        {
                            // Invalid case...
                            pstChProcProgIndex->eServiceType = E_SERVICETYPE_DTV;
                            break;
                        }
                    }
                }
            #endif
                else //if( eChProcTvDBType == E_CHPROC_DB_ATV )
                {
                    pstChProcProgIndex->eServiceType = E_SERVICETYPE_ATV;
                    pstChProcProgIndex->u16Position = u16Ordinal - msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary);
                      //msAPI_ATV_ConvertOrdinalNumberToProgramNumber(u16Ordinal - msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary));
                }
            }

            break;

        default:
            //return FALSE;
            break;
    }

    DEBUG_CH_PROC( printf(" ==> eService=%u, u16Position=%u\n", pstChProcProgIndex->eServiceType, pstChProcProgIndex->u16Position); );

    if( pstChProcProgIndex->eServiceType >= E_SERVICETYPE_UNITED_TV )
    {
        printf("\nError: Convert Ordinal(%u) to Pos failed! eServiceType=%u\n", u16Ordinal, pstChProcProgIndex->eServiceType);
        return FALSE;
    }

    if( pstChProcProgIndex->u16Position == INVALID_POSITION )
    {
        printf("\nError: Convert Ordinal(%u) to Pos failed! INVALID_POSITION\n", u16Ordinal);
        return FALSE;
    }

    return TRUE;
}

// This function is only for UnitedTV
BOOLEAN msAPI_CHPROC_CM_Get_ServiceType_Position_ByOrdinal
  ( MEMBER_SERVICETYPE eServiceType, U16 u16Ordinal, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary,
    MEMBER_SERVICETYPE* peServiceType, U16* pu16Position )
{
    StruChProcProgIndex stChProcProgIndex;

    BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
            eServiceType, u16Ordinal,
             eBoundary, &stChProcProgIndex );

    //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

    if( bResult == FALSE )
    {
        *peServiceType = E_SERVICETYPE_INVALID;
        *pu16Position = INVALID_POSITION;
        return FALSE;
    }

    *peServiceType = stChProcProgIndex.eServiceType;
    *pu16Position = stChProcProgIndex.u16Position;
    return TRUE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_ServiceType_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    MEMBER_SERVICETYPE eServiceType = E_SERVICETYPE_ATV;

#if ENABLE_SBTVD_CM_APP
    UNUSED(eBoundary);
#endif

#if (ENABLE_DVB)
    switch(bServiceType)
    {
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
    case E_SERVICETYPE_ATV:
    case E_SERVICETYPE_UNITED_TV:
        if (bServiceType != E_SERVICETYPE_UNITED_TV)
        {
            eServiceType = bServiceType;
        }
        else // E_SERVICETYPE_UNITED_TV
        {
    #if 0//ENABLE_SBTVD_CM_APP
            if( ANT_CATV == msAPI_ATV_GetCurrentAntenna() )
                eServiceType = E_SERVICETYPE_ATV;
            else
                eServiceType = aOridinalList[wOrdinal].eServicetype;

    #else //ENABLE_SBTVD_CM_APP

            {
                StruChProcProgIndex stChProcProgIndex;
                if( FALSE == msAPI_CHPROC_CM_ConvertOrdinalToPosition(bServiceType, wOrdinal, eBoundary, &stChProcProgIndex) )
                {
                    printf("\nError: Convert Ordinal failed!\n");
                    return FALSE;
                }
                else
                {
                    eServiceType = stChProcProgIndex.eServiceType;
                }
            }

    #endif // ENABLE_SBTVD_CM_APP
        }

        break;

    default:
        return FALSE;
        break;
    }

#else
    UNUSED(bServiceType);
    UNUSED(wOrdinal);
    UNUSED(pcBuffer);
    UNUSED(eBoundary);
#endif

    //printf("Ordinal=%u => Svc=%u\n", wOrdinal, eServiceType);

    memcpy(pcBuffer, &eServiceType, sizeof(MEMBER_SERVICETYPE));

    return TRUE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_LCN_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    BYTE cProgramNumber=0;
    WORD wTempBuf = 0;
#if (ENABLE_DVB)
    WORD wLCN=0;
#endif

    //printf("msAPI_CHPROC_CM_Get_Attr_LCN_ByOrdinal(bServiceType=%u, wOrdinal=%u, eBoundary=%u)\n", bServiceType, wOrdinal, eBoundary);

    UNUSED(eBoundary);

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        wLCN = msAPI_CM_GetLogicalChannelNumber(bServiceType, wOrdinal);
        if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER )
        {
            memcpy(pcBuffer,&wLCN,sizeof(WORD));
            return TRUE;
        }
        else
        {
            memcpy(pcBuffer,&wLCN,sizeof(WORD));
            return FALSE;
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
        if( wOrdinal < msAPI_ATV_GetChannelMax() )
        {
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal);

            if( TRUE == msAPI_ATV_IsProgramNumberActive(cProgramNumber) )
            {
                wTempBuf = cProgramNumber;
                memcpy(pcBuffer,&wTempBuf,sizeof(WORD));
                return TRUE;
            }
        }
        break;

    case E_SERVICETYPE_UNITED_TV:
#if ENABLE_SBTVD_CM_APP
    if(IS_ORDINAL_LIST_ENABLE)
    {
        if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
        {
            if(aOridinalList[wOrdinal].eServicetype == E_SERVICETYPE_ATV)
                wLCN = (aOridinalList[wOrdinal].u16LCN>>8);
            else
                wLCN = aOridinalList[wOrdinal].u16LCN;
            if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER   )
            {
                memcpy(pcBuffer,&wLCN,sizeof(WORD));
                return TRUE;
            }
        }
        else if( wOrdinal < msAPI_ATV_GetChannelMax())
        {
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal);

            if( TRUE == msAPI_ATV_IsProgramNumberActive(cProgramNumber) )
            {
                wTempBuf = (WORD)cProgramNumber;
                memcpy(pcBuffer,&wTempBuf,sizeof(WORD));
                return TRUE;
            }
        }
    }
    else
#endif
#if 1
    {
        StruChProcProgIndex stChProcProgIndex;

        BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                E_SERVICETYPE_UNITED_TV, wOrdinal,
                 eBoundary, &stChProcProgIndex );
        //printf("wOrdinal=%u\n", wOrdinal);
        //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

        if( bResult == FALSE )
        {
            break;
        }

        if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
        {
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(stChProcProgIndex.u16Position);
            if( TRUE == msAPI_ATV_IsProgramNumberActive(cProgramNumber) )
            {
                wTempBuf = (WORD)cProgramNumber;
                memcpy(pcBuffer,&wTempBuf,sizeof(WORD));
                return TRUE;
            }
        }
        else
        {
        #if (ENABLE_DVB)
            wLCN = msAPI_CM_GetLogicalChannelNumber(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);
            if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER )
            {
                //printf("wLCN=%u\n", wLCN);
                memcpy(pcBuffer,&wLCN,sizeof(WORD));
                return TRUE;
            }
        #else
            break;
        #endif
        }
    }
#else
    {
    #if (ENABLE_DVB)
        if((IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))&&( wOrdinal < (msAPI_CHPROC_CM_Get_TotalDtvProgramCount(eBoundary)) ))
        {
            wLCN = msAPI_CM_GetLogicalChannelNumberbyListPosition(wOrdinal);
            if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER )
            {
                memcpy(pcBuffer,&wLCN,sizeof(WORD));
                return TRUE;
            }
            return FALSE;
        }

        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV, wOrdinal);
            if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER   )
            {
                memcpy(pcBuffer,&wLCN,sizeof(WORD));
                return TRUE;
            }
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)));
            if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER   )
            {
                memcpy(pcBuffer,&wLCN,sizeof(WORD));
                return TRUE;
            }
        }
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            wLCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
            if( wLCN != INVALID_LOGICAL_CHANNEL_NUMBER   )
            {
                memcpy(pcBuffer,&wLCN,sizeof(WORD));
                return TRUE;
            }
        }
      #endif
        else
    #endif
        {
            // Exclude Empty or Skiped Program
          #if NORDIG_FUNC //for Nordig Spec v2.0
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary));
          #else
    #if (ENABLE_DVB)
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary));
    #else
            cProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal);
    #endif
          #endif
            if( TRUE == msAPI_ATV_IsProgramNumberActive(cProgramNumber) )
            {
                wTempBuf = (WORD)cProgramNumber;
                memcpy(pcBuffer,&wTempBuf,sizeof(WORD));
                return TRUE;
            }
        }
    }
#endif

    default:
        break;
    }

    return FALSE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_Name_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    //printf("msAPI_CHPROC_CM_Get_Attr_Name_ByOrdinal(bServiceType=%u, wOrdinal=%u, eBoundary=%u)\n", bServiceType, wOrdinal, eBoundary);

    UNUSED(eBoundary);

    U8 u8ProgramNumber;

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
    #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
    #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
            return msAPI_CM_GetServiceName(bServiceType, wOrdinal, pcBuffer);
        break;
#endif

    case E_SERVICETYPE_ATV:
    #if 1//ENABLE_SBTVD_DTV_SYSTEM
        if( wOrdinal < msAPI_ATV_GetChannelMax() )
    #elif ( ENABLE_DVB_TAIWAN_APP )
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #else
        if( wOrdinal < MAX_ATVPROGRAM )
    #endif
        {
            u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal);
            return msAPI_ATV_GetStationName(u8ProgramNumber, pcBuffer);
        }
        break;

    case E_SERVICETYPE_UNITED_TV:
  #if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            switch(aOridinalList[wOrdinal].eServicetype)
            {
                case E_SERVICETYPE_DTV:
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DATA:
                    msAPI_CM_GetServiceName(aOridinalList[wOrdinal].eServicetype,aOridinalList[wOrdinal].wPosition, pcBuffer);
                break;

                case E_SERVICETYPE_ATV:
                default:
                    return msAPI_ATV_GetStationName(aOridinalList[wOrdinal].wPosition >> 8, pcBuffer);
            }
        }
        else
  #endif
  #if 1 //  Use new method
        {
            StruChProcProgIndex stChProcProgIndex;

            BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                    E_SERVICETYPE_UNITED_TV, wOrdinal,
                     eBoundary, &stChProcProgIndex );

            //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

            if( bResult == FALSE )
            {
                break;
            }

            if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
            {
                u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(stChProcProgIndex.u16Position);
                return msAPI_ATV_GetStationName(u8ProgramNumber, pcBuffer);
            }
            else
            {
            #if (ENABLE_DVB)
                return msAPI_CM_GetServiceName(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position, pcBuffer);
            #else
                break;
            #endif
            }
        }

  #else
    {
    #if (ENABLE_DVB)
        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            return msAPI_CM_GetServiceName(E_SERVICETYPE_DTV, wOrdinal, pcBuffer);
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            return msAPI_CM_GetServiceName(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), pcBuffer);
        }
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            return msAPI_CM_GetServiceName(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), pcBuffer);
        }
      #endif
        else
    #endif
        {
            #if NORDIG_FUNC //for Nordig Spec v2.0
            return msAPI_ATV_GetStationName(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), pcBuffer);
            #else
        #if (ENABLE_DVB)
            return msAPI_ATV_GetStationName(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), pcBuffer);
        #else
            return msAPI_ATV_GetStationName(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal), pcBuffer);
        #endif
            #endif
        }
    }
  #endif
        break;

    default:
        break;
    }

    return FALSE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_Skip_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
    UNUSED(eBoundary);


    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
   #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
   #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_SKIPPED);
            return TRUE;
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
    #if 1//ENABLE_SBTVD_DTV_SYSTEM
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #elif ( ENABLE_DVB_TAIWAN_APP )
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #else
        if( wOrdinal < MAX_ATVPROGRAM )
    #endif
        {
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramSkipped(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));
            return TRUE;
        }
        break;

    case E_SERVICETYPE_UNITED_TV:
  #if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            switch(aOridinalList[wOrdinal].eServicetype)
            {
                case E_SERVICETYPE_DTV:
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DATA:
                    *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(aOridinalList[wOrdinal].eServicetype, aOridinalList[wOrdinal].wPosition, E_ATTRIBUTE_IS_SKIPPED);
                break;

                case E_SERVICETYPE_ATV:
                default:
                    *(BOOLEAN *)pcBuffer =  msAPI_ATV_IsProgramSkipped(aOridinalList[wOrdinal].wPosition >> 8);
            }
            return TRUE;
        }
        else
  #endif
  #if 1 // 20151126 Use new method
        {
            StruChProcProgIndex stChProcProgIndex;

            BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                    E_SERVICETYPE_UNITED_TV, wOrdinal,
                     eBoundary, &stChProcProgIndex );

            //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

            if( bResult == FALSE )
            {
                break;
            }

            if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
            {
                U8 u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(stChProcProgIndex.u16Position);
                *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramSkipped(u8ProgramNumber);
                return TRUE;
            }
            else
            {
            #if (ENABLE_DVB)
                *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position, E_ATTRIBUTE_IS_SKIPPED);
                return TRUE;
            #else
                break;
            #endif
            }
        }

  #else
    {
    #if (ENABLE_DVB)
        if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
        {
            MEMBER_SERVICETYPE eServiceType;
            WORD wPosition;

            wPosition = msAPI_CM_GetPositionbyListPosition(wOrdinal,&eServiceType);
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(eServiceType, wPosition, E_ATTRIBUTE_IS_SKIPPED);
            return TRUE;
        }

        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_SKIPPED);
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_SKIPPED);
        }
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)- msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_SKIPPED);
        }
      #endif
        else
    #endif
        {
          #if NORDIG_FUNC //for Nordig Spec v2.0
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramSkipped(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
          #else
        #if (ENABLE_DVB)
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramSkipped(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
        #else
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramSkipped(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));
        #endif
          #endif
        }
    }
  #endif
        return TRUE;

    default:
        break;
    }

    return FALSE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_Favor_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if(!ENABLE_DVB)
    UNUSED(eBoundary);
#endif

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
        #if 0//ENABLE_S2_CHANNEL_FAV_NEWSTYLE
            *(BOOLEAN *)pcBuffer = (msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_FAVORITE1)
                                ||msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_FAVORITE2)
                                ||msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_FAVORITE3)
                                ||msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_FAVORITE4));
        #else
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_FAVORITE);
        #endif
            return TRUE;
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
    #if 1//ENABLE_SBTVD_DTV_SYSTEM
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #elif ( ENABLE_DVB_TAIWAN_APP )
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #else
        if( wOrdinal < MAX_ATVPROGRAM )
    #endif
        {
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramFavorite(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));
            return TRUE;
        }
        break;

    case E_SERVICETYPE_UNITED_TV:
#if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            switch(aOridinalList[wOrdinal].eServicetype)
            {
                case E_SERVICETYPE_DTV:
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DATA:
                    *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(aOridinalList[wOrdinal].eServicetype, aOridinalList[wOrdinal].wPosition, E_ATTRIBUTE_IS_FAVORITE);
                break;

                case E_SERVICETYPE_ATV:
                default:
                    *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramFavorite(aOridinalList[wOrdinal].wPosition >> 8 );
            }
        }
        else
#endif
#if 1 // 20151126
        {
            StruChProcProgIndex stChProcProgIndex;

            BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                    E_SERVICETYPE_UNITED_TV, wOrdinal,
                     eBoundary, &stChProcProgIndex );

            //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

            if( bResult == FALSE )
            {
                break;
            }

            if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
            {
                U8 u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(stChProcProgIndex.u16Position);
                *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramFavorite(u8ProgramNumber);
                return TRUE;
            }
            else
            {
            #if (ENABLE_DVB)
                *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position, E_ATTRIBUTE_IS_FAVORITE);
                return TRUE;
            #else
                break;
            #endif
            }

        }
#else
    {
    #if (ENABLE_DVB)
        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
        #if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
            *(BOOLEAN *)pcBuffer = (msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_FAVORITE1)
                                    ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_FAVORITE2)
                                    ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_FAVORITE3)
                                    ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_FAVORITE4));
        #else
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_FAVORITE);
        #endif
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)))
        {
        #if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
            *(BOOLEAN *)pcBuffer = (msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_FAVORITE1)
                                        ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_FAVORITE2)
                                        ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_FAVORITE3)
                                        ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_FAVORITE4));
        #else
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_FAVORITE);
        #endif
        }
        #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)))
        {
        #if ENABLE_S2_CHANNEL_FAV_NEWSTYLE
            *(BOOLEAN *)pcBuffer = (msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_FAVORITE1)
                                ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_FAVORITE2)
                                ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_FAVORITE3)
                                ||msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_FAVORITE4));
        #else
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_FAVORITE);
        #endif
        }
        #endif
        else
    #endif
        {
          #if NORDIG_FUNC //for Nordig Spec v2.0
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramFavorite(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
          #else
        #if (ENABLE_DVB)
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramFavorite(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
        #else
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramFavorite(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));
        #endif
           #endif
        }
    }
#endif
        return TRUE;

    default:
        break;

    }

    return FALSE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_Locked_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if (ENABLE_DVB)
    //MEMBER_SERVICETYPE eServiceType;
#else
    UNUSED(eBoundary);
#endif

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_LOCKED);
            return TRUE;
        }
        break;
#endif

    case E_SERVICETYPE_ATV:
    #if 1//ENABLE_SBTVD_DTV_SYSTEM
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #elif ( ENABLE_DVB_TAIWAN_APP )
        if( wOrdinal < msAPI_ATV_GetChannelMax())
    #else
        if( wOrdinal < MAX_ATVPROGRAM )
    #endif
        {
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramLocked(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));
            return TRUE;
        }
        break;

    case E_SERVICETYPE_UNITED_TV:
#if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            switch(aOridinalList[wOrdinal].eServicetype)
            {
                case E_SERVICETYPE_DTV:
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DATA:
                    *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(aOridinalList[wOrdinal].eServicetype, aOridinalList[wOrdinal].wPosition, E_ATTRIBUTE_IS_LOCKED);
                break;

                case E_SERVICETYPE_ATV:
                default:
                    *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramLocked(aOridinalList[wOrdinal].wPosition >> 8);
            }
        }
        else
#endif
#if 1 // 20151201
        {
            StruChProcProgIndex stChProcProgIndex;

            BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                    E_SERVICETYPE_UNITED_TV, wOrdinal,
                     eBoundary, &stChProcProgIndex );

            //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

            if( bResult == FALSE )
            {
                break;
            }

            if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
            {
                U8 u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(stChProcProgIndex.u16Position);
                *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramLocked(u8ProgramNumber);
                return TRUE;
            }
            else
            {
            #if (ENABLE_DVB)
                *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position, E_ATTRIBUTE_IS_LOCKED);
                return TRUE;
            #else
                break;
            #endif
            }
        }
#else
    {
    #if (ENABLE_DVB)
        if(IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING))
        {
            MEMBER_SERVICETYPE eServiceType;
            WORD wPosition;

            wPosition = msAPI_CM_GetPositionbyListPosition(wOrdinal,&eServiceType);
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(eServiceType, wPosition, E_ATTRIBUTE_IS_LOCKED);
            return TRUE;
        }

        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_LOCKED);
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_LOCKED);
        }
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_LOCKED);
        }
      #endif
        else
    #endif
        {
        #if NORDIG_FUNC //for Nordig Spec v2.0
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramLocked(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
        #else
          #if (ENABLE_DVB)
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramLocked(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)));
          #else
            *(BOOLEAN *)pcBuffer = msAPI_ATV_IsProgramLocked(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wOrdinal));
          #endif
        #endif
        }
    }
#endif
        return TRUE;

    default:
        break;
    }

    return FALSE;
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_Visible_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if( ENABLE_DVB )

    switch(bServiceType)
    {
#if 1//ENABLE_S2_PREDIT_SWITCH_LIST
    case E_SERVICETYPE_ATV:
        *(BOOLEAN *)pcBuffer = TRUE;
        return TRUE;
#endif

#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_VISIBLE);
            return TRUE;
        }
        break;
#endif

    case E_SERVICETYPE_UNITED_TV:
#if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            switch(aOridinalList[wOrdinal].eServicetype)
            {
                case E_SERVICETYPE_DTV:
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DATA:
                    *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(aOridinalList[wOrdinal].eServicetype, aOridinalList[wOrdinal].wPosition, E_ATTRIBUTE_IS_VISIBLE);
                break;
                default:
                    *(BOOLEAN *)pcBuffer = TRUE;
            }
        }
        else
#endif
#if 1 // 20151201
        {
            StruChProcProgIndex stChProcProgIndex;

            BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                    E_SERVICETYPE_UNITED_TV, wOrdinal,
                     eBoundary, &stChProcProgIndex );

            //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

            if( bResult == FALSE )
            {
                break;
            }

            if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
            {
                *(BOOLEAN *)pcBuffer = TRUE;
                return TRUE;
            }
            else
            {
            #if (ENABLE_DVB)
                *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position, E_ATTRIBUTE_IS_VISIBLE);
                return TRUE;
            #else
                break;
            #endif
            }
        }
#else

    #if (ENABLE_DVB)
        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_VISIBLE);
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_VISIBLE);
        }
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_VISIBLE);
        }
      #endif
        else
    #endif
        {
            *(BOOLEAN *)pcBuffer = TRUE;
        }
#endif
        return TRUE;
    default:
        break;
    }

    return FALSE;

#else

    UNUSED(bServiceType);
    UNUSED(wOrdinal);
    UNUSED(eBoundary);

    // ATV is always visible
    *(BOOLEAN *)pcBuffer = TRUE;
    return TRUE;
#endif
}

BOOLEAN msAPI_CHPROC_CM_Get_Attr_NUMERIC_ByOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if( ENABLE_DVB )

    switch(bServiceType)
    {
#if (ENABLE_DVB)
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
  #if NORDIG_FUNC //for Nordig Spec v2.0
    case E_SERVICETYPE_DATA:
  #endif
        if( wOrdinal < msAPI_CM_CountProgram(bServiceType, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(bServiceType, wOrdinal, E_ATTRIBUTE_IS_NUMERIC_SELECTION);
            return TRUE;
        }
        break;
#endif

    case E_SERVICETYPE_UNITED_TV:
#if ENABLE_SBTVD_CM_APP
        if(IS_ORDINAL_LIST_ENABLE)
        {
            switch(aOridinalList[wOrdinal].eServicetype)
            {
                case E_SERVICETYPE_DTV:
                case E_SERVICETYPE_RADIO:
                case E_SERVICETYPE_DATA:
                    *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(aOridinalList[wOrdinal].eServicetype, aOridinalList[wOrdinal].wPosition, E_ATTRIBUTE_IS_NUMERIC_SELECTION);
                    break;
                default:
                    *(BOOLEAN *)pcBuffer = TRUE;
                    break;
            }
        }
        else
#endif
#if 1 // 20151201
        {
            StruChProcProgIndex stChProcProgIndex;

            BOOL bResult = msAPI_CHPROC_CM_ConvertOrdinalToPosition(
                    E_SERVICETYPE_UNITED_TV, wOrdinal,
                     eBoundary, &stChProcProgIndex );

            //printf("bResult=%u, eServiceType=%u, u16Position=%u\n", bResult, stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position);

            if( bResult == FALSE )
            {
                break;
            }

            if( stChProcProgIndex.eServiceType == E_SERVICETYPE_ATV )
            {
                *(BOOLEAN *)pcBuffer = TRUE;
                return TRUE;
            }
            else
            {
            #if (ENABLE_DVB)
                *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(stChProcProgIndex.eServiceType, stChProcProgIndex.u16Position, E_ATTRIBUTE_IS_NUMERIC_SELECTION);
                return TRUE;
            #else
                break;
            #endif
            }
        }

#else

    #if( ENABLE_DVB ) //(ENABLE_DTV)
        if( wOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DTV, wOrdinal, E_ATTRIBUTE_IS_NUMERIC_SELECTION);
        }
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_RADIO, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)), E_ATTRIBUTE_IS_NUMERIC_SELECTION);
        }
      #if NORDIG_FUNC //for Nordig Spec v2.0
        else if( wOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, eBoundary)) )
        {
            *(BOOLEAN *)pcBuffer = msAPI_CM_GetProgramAttribute(E_SERVICETYPE_DATA, (wOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, eBoundary)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, eBoundary)), E_ATTRIBUTE_IS_NUMERIC_SELECTION);
        }
      #endif
        else
    #endif
        {
            *(BOOLEAN *)pcBuffer = TRUE;
        }
#endif
        return TRUE;

    default:
        break;
    }

    return FALSE;

#else

    UNUSED(bServiceType);
    UNUSED(wOrdinal);
    UNUSED(eBoundary);

    // ATV is always NUMERIC = TRUE
    *(BOOLEAN *)pcBuffer = TRUE;
    return TRUE;
#endif
}

BOOLEAN msAPI_CHPROC_CM_GetAttributeOfOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wOrdinal, BYTE * pcBuffer, SERVICE_ATTRIBUTE_MEMBER eAttributeMember, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eBoundary)
{
#if 1//(!ENABLE_DVB)
    UNUSED(eBoundary);
#endif


    //PRINT_CURRENT_LINE();
    DEBUG_CH_PROC( printf("msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType=%u, wOrdinal=%u, eBoundary=%u, Attr=0x%X)\n", bServiceType, wOrdinal, eBoundary, eAttributeMember); );
    //DEBUG_CH_PROC( printf(" Dtv_C=%u, Radio_C=%u, Data_C=%u, ATV_C=%u\n", u16DtvProgCount, u16DtvProgCount_Audio, u16DtvProgCount_Data, msAPI_ATV_GetActiveProgramCount()); );

    if( bServiceType != E_SERVICETYPE_UNITED_TV )
    {
        printf("msAPI_CHPROC_CM_GetAttributeOfOrdinal(bServiceType=%u, wOrdinal=%u, eBoundary=%u, Attr=0x%X)\n", bServiceType, wOrdinal, eBoundary, eAttributeMember);
    }

    switch(eAttributeMember)
    {
    case E_SERVICE_ATTR_TYPE:
        return msAPI_CHPROC_CM_Get_Attr_ServiceType_ByOrdinal(bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_NUMBER:
        return msAPI_CHPROC_CM_Get_Attr_LCN_ByOrdinal(bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_NAME:
        return msAPI_CHPROC_CM_Get_Attr_Name_ByOrdinal(bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_SKIPPED:
        return msAPI_CHPROC_CM_Get_Attr_Skip_ByOrdinal(bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_FAVORITE:
        return msAPI_CHPROC_CM_Get_Attr_Favor_ByOrdinal( bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_LOCKED:
        return msAPI_CHPROC_CM_Get_Attr_Locked_ByOrdinal( bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_VISIBLE:
        return msAPI_CHPROC_CM_Get_Attr_Visible_ByOrdinal(bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    case E_SERVICE_ATTR_NUMERIC:
        return msAPI_CHPROC_CM_Get_Attr_NUMERIC_ByOrdinal(bServiceType, wOrdinal, pcBuffer, eBoundary);
        break;

    default:
        return FALSE;
    }

    return FALSE;
}

#if 0
//****************************************************************************
// Start of private implementation
//****************************************************************************
static BYTE _AlignDecimalToLeft(BYTE *pcBuffer, WORD wNumber)
{
    WORD wDecreasedNumber;
    BYTE cCursor;
    WORD wMultipleOf10;

    wDecreasedNumber = wNumber;
    cCursor = 0;

    for( wMultipleOf10 = 1000; wMultipleOf10 > 0; wMultipleOf10 /= 10 )
    {
        if( 0 != (wNumber / wMultipleOf10) || 0 == wNumber )
        {
            pcBuffer[cCursor] = (wDecreasedNumber / wMultipleOf10);
            cCursor++;
            wDecreasedNumber %= wMultipleOf10;
        }
    }

    return cCursor;
}

static BOOLEAN _IsAlignedDecimalSame(BYTE *pcBuffer1, BYTE *pcBuffer2, BYTE cLength)
{
    BYTE i;

    for(i=0; i < cLength; i++)
    {
        if( pcBuffer1[i] != pcBuffer2[i] )
            return FALSE;
    }

    return TRUE;
}
#endif

#if(!ENABLE_CHRPOC_NEW_FAVORITE_METHOD)
#if( ENABLE_DVB&&NORDIG_FUNC )//for Nordig Spec v2.0
static WORD _GetNextFavoriteOrdinalOfUnitedTV(WORD wBaseOrdinal, BOOLEAN bIncludeSkipped)
{
    WORD wProgramPosition=0;
    BYTE cProgramNumber=0;
    MEMBER_SERVICETYPE  u8Type,bServiceType;

    DEBUG_CH_PROC_FAV( printf("_GetNextFavoriteOrdinalOfUnitedTV(wBaseOrdinal=%u, bIncludeSkipped=%u)\n", wBaseOrdinal, bIncludeSkipped); );

    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wBaseOrdinal, (BYTE *)&bServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);

    if((bServiceType != E_SERVICETYPE_ATV) && (IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)))
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPositionbyListPosition(wBaseOrdinal,(MEMBER_SERVICETYPE *)&u8Type,bIncludeSkipped);
        if(wProgramPosition == INVALID_PROGRAM_POSITION)
        {
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if(cProgramNumber == INVALID_ATV_PROGRAM_NUMBER)
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPositionbylistpositon((MEMBER_SERVICETYPE *)&u8Type,bIncludeSkipped);
                if( wProgramPosition == INVALID_PROGRAM_POSITION )
                {
                    return INVALID_ORDINAL;
                }
                else
                {
                    return msAPI_CM_GetListPositionbyPosition(wProgramPosition,u8Type);
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
            }
        }
        return msAPI_CM_GetListPositionbyPosition(wProgramPosition,u8Type);
    }
    else if( wBaseOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) )
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPosition(E_SERVICETYPE_DTV, wBaseOrdinal, bIncludeSkipped);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= wBaseOrdinal) )
        {
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION)
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DATA, bIncludeSkipped);
                if( wProgramPosition == INVALID_PROGRAM_POSITION)
                {
                    cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                    if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                    {
                        wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                        if( wProgramPosition == INVALID_PROGRAM_POSITION )
                        {
                            return INVALID_ORDINAL;
                        }
                        else
                        {
                            return wProgramPosition;
                        }
                    }
                    else
                    {
                        return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+ msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                    }
                }
                else
                {
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+wProgramPosition;
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + wProgramPosition;
            }
        }
        else
        {
            return wProgramPosition;
        }
    }
    else if( wBaseOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)) )    // 070626 DHShin
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPosition(E_SERVICETYPE_RADIO, (wBaseOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)), bIncludeSkipped);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= (wBaseOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY))) )
        {
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DATA, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION )
            {
                cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                {
                    wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                    if( wProgramPosition == INVALID_PROGRAM_POSITION )
                    {
                        wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
                        if( wProgramPosition == INVALID_PROGRAM_POSITION )
                        {
                            return INVALID_ORDINAL;
                        }
                        else
                        {
                            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) +wProgramPosition;
                        }
                    }
                    else
                    {
                        return wProgramPosition;
                    }
                }
                else
                {
                    return cProgramNumber + msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + wProgramPosition;
            }
        }
        else
        {
            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + wProgramPosition;
        }
    }
    else if( wBaseOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)) )    // 070626 DHShin
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPosition(E_SERVICETYPE_DATA, (wBaseOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)), bIncludeSkipped);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= (wBaseOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY))) )
        {
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                if( wProgramPosition == INVALID_PROGRAM_POSITION )
                {
                    wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
                    if( wProgramPosition == INVALID_PROGRAM_POSITION )
                    {
                        wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DATA, bIncludeSkipped);
                        if( wProgramPosition == INVALID_PROGRAM_POSITION )
                        {
                            return INVALID_ORDINAL;
                        }
                        else
                        {
                            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+wProgramPosition;
                        }
                    }
                    else
                    {
                        return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+wProgramPosition;
                    }
                }
                else
                {
                    return wProgramPosition;
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+cProgramNumber;
            }
        }
        else
        {
            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+wProgramPosition;
        }
    }
    else
    {
        cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetNextFavoriteProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wBaseOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) - msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY))));
        if( (cProgramNumber == INVALID_ATV_PROGRAM_NUMBER) ||
            (cProgramNumber <= (BYTE)(wBaseOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) - msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)-msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY))) )
        {
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION )
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
                if( wProgramPosition == INVALID_PROGRAM_POSITION )
                {
                    wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DATA, bIncludeSkipped);
                    if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                    {
                        cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                        if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                        {
                            return INVALID_ORDINAL;
                        }
                        else
                        {
                            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                        }
                    }
                    else
                    {
                        return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+cProgramNumber;
                    }
                }
                else
                {
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) +cProgramNumber;
                }
            }
            else
            {
                return wProgramPosition;
            }
        }
        else
        {
            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_DATA, E_PROGACESS_INCLUDE_VISIBLE_ONLY)+msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
        }
    }
    return INVALID_ORDINAL;
}
#else
static WORD _GetNextFavoriteOrdinalOfUnitedTV(WORD wBaseOrdinal, BOOLEAN bIncludeSkipped)
{
DEBUG_CH_PROC_FAV( printf("_GetNextFavoriteOrdinalOfUnitedTV(wBaseOrdinal=%u, bIncludeSkipped=%u)\n", wBaseOrdinal, bIncludeSkipped); );

#if (ENABLE_DVB)
    WORD wProgramPosition=0;
    MEMBER_SERVICETYPE  u8Type,bServiceType;
    bServiceType = E_SERVICETYPE_ATV; //Fix coverity 182985
#endif
    BYTE cProgramNumber=0;

#if (!ENABLE_DVB)
    UNUSED(bIncludeSkipped);
#endif

  #if ENABLE_SBTVD_CM_APP
    if(ANT_AIR == msAPI_ATV_GetCurrentAntenna())
    {
        U16 u16Loop;

        bIncludeSkipped = bIncludeSkipped;

        for(u16Loop=wBaseOrdinal+1;u16Loop<Get_MAXOridinal();u16Loop++)
        {
            if(aOridinalList[u16Loop].eServicetype == E_SERVICETYPE_ATV)
            {
                if(TRUE == msAPI_ATV_IsProgramFavorite(aOridinalList[u16Loop].wPosition >> 8))
                    return  u16Loop;
            }
            else
            {
                if(TRUE == msAPI_CM_GetProgramAttribute(aOridinalList[u16Loop].eServicetype,aOridinalList[u16Loop].wPosition,E_ATTRIBUTE_IS_FAVORITE))
                    return  u16Loop;
            }
        }
    }
    else
  #endif // ENABLE_SBTVD_CM_APP

#if (ENABLE_DVB)
    msAPI_CHPROC_CM_GetAttributeOfOrdinal(E_SERVICETYPE_UNITED_TV, wBaseOrdinal, (BYTE *)&bServiceType, E_SERVICE_ATTR_TYPE, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    if((bServiceType != E_SERVICETYPE_ATV) && (IS_LCN_RANK_COUNTRY(OSD_COUNTRY_SETTING)))
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPositionbyListPosition(wBaseOrdinal,(MEMBER_SERVICETYPE *)&u8Type,bIncludeSkipped);
        if(wProgramPosition == INVALID_PROGRAM_POSITION)
        {
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if(cProgramNumber == INVALID_ATV_PROGRAM_NUMBER)
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPositionbylistpositon((MEMBER_SERVICETYPE *)&u8Type,bIncludeSkipped);
                if( wProgramPosition == INVALID_PROGRAM_POSITION )
                {
                    return INVALID_ORDINAL;
                }
                else
                {
                    return msAPI_CM_GetListPositionbyPosition(wProgramPosition,u8Type);
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
            }
        }
        return msAPI_CM_GetListPositionbyPosition(wProgramPosition,u8Type);
    }
    else if( wBaseOrdinal < msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) )
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPosition(E_SERVICETYPE_DTV, wBaseOrdinal, bIncludeSkipped);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= wBaseOrdinal) )
        {
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION)
            {
                cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                {
                    wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                    if( wProgramPosition == INVALID_PROGRAM_POSITION )
                    {
                        return INVALID_ORDINAL;
                    }
                    else
                    {
                        return wProgramPosition;
                    }
                }
                else
                {
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + wProgramPosition;
            }
        }
        else
        {
            return wProgramPosition;
        }
    }
    else if( wBaseOrdinal < (msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)) )    // 070626 DHShin
    {
        wProgramPosition = msAPI_CM_GetNextFavoriteProgramPosition(E_SERVICETYPE_RADIO, (wBaseOrdinal-msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY)), bIncludeSkipped);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= (wBaseOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY))) )
        {
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
            {
                cProgramNumber = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
                if( cProgramNumber == 0xFF )
                {
                    cProgramNumber = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
                    if( cProgramNumber == 0xFF )
                    {
                        return INVALID_ORDINAL;
                    }
                    else
                    {
                        return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + wProgramPosition;
                    }
                }
                else
                {
                    return cProgramNumber;
                }
            }
            else
            {
                return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
            }
        }
        else
        {
            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + wProgramPosition;
        }
    }
    else
#endif
    {
#if (ENABLE_DVB)
        cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetNextFavoriteProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wBaseOrdinal - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY))));
#else
        cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetNextFavoriteProgramNumber(msAPI_ATV_ConvertOrdinalNumberToProgramNumber(wBaseOrdinal )));
#endif
        if( (cProgramNumber == INVALID_ATV_PROGRAM_NUMBER) ||
            (cProgramNumber <= (BYTE)(wBaseOrdinal
#if (ENABLE_DVB)
            - msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) - msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY)
#endif
            )) )
        {
#if (!ENABLE_DVB)
            cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
            if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
            {
                return INVALID_ORDINAL;
            }
            else
            {
                return cProgramNumber;
            }
#else
            wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_DTV, bIncludeSkipped);
            if( wProgramPosition == INVALID_PROGRAM_POSITION )
            {
                wProgramPosition = msAPI_CM_GetFirstFavoriteProgramPosition(E_SERVICETYPE_RADIO, bIncludeSkipped);
                if( cProgramNumber == 0xFF )
                {
                    cProgramNumber = msAPI_ATV_ConvertProgramNumberToOrdinalNumber(msAPI_ATV_GetFirstFavoriteProgramNumber());
                    if( cProgramNumber == INVALID_ATV_PROGRAM_NUMBER )
                    {
                        return INVALID_ORDINAL;
                    }
                    else
                    {
                        return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                    }
                }
                else
                {
                    return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
                }
            }
            else
            {
                return wProgramPosition;
            }
#endif
        }
        else
        {
#if (ENABLE_DVB)
            return msAPI_CM_CountProgram(E_SERVICETYPE_DTV, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + msAPI_CM_CountProgram(E_SERVICETYPE_RADIO, E_PROGACESS_INCLUDE_VISIBLE_ONLY) + cProgramNumber;
#else
            return cProgramNumber;
#endif
        }
    }
    return INVALID_ORDINAL;
}
#endif
#endif // (!ENABLE_CHRPOC_NEW_FAVORITE_METHOD)


#if ENABLE_CHPROC_ORDINAL_LIST//ENABLE_SBTVD_CM_APP

U32 msAPI_CHPROC_CM_Get_Weighting(U16 u16Ordinal)
{
    U32 u32Weighting = (aOridinalList[u16Ordinal].u16LCN);

    if( g_ChProc_eSortType == CH_PROC_SORT_DTV_LCN__ATV )
    {
        if( aOridinalList[u16Ordinal].eServicetype == E_SERVICETYPE_ATV )
            u32Weighting += 30000;
    }
    else // g_ChProc_eSortType = CH_PROC_SORT_DTV_RADIO_DATA_ATV;
    {
        switch( aOridinalList[u16Ordinal].eServicetype )
        {
            case E_SERVICETYPE_DTV:
                break;

            case E_SERVICETYPE_RADIO:
                u32Weighting += 10000;
                break;

            case E_SERVICETYPE_DATA:
                u32Weighting += 20000;
                break;

            case E_SERVICETYPE_ATV:
                u32Weighting += 30000;
                break;

            default:
                u32Weighting += 40000;
                break;
        }
    }

    return u32Weighting;
}

// Change this function to change sorting type
// If WEIGHT(u16Ordinal1) > WEIGHT(u16Ordinal1), return 1
int msAPI_CHPROC_CM_Compare(U16 u16Ordinal1, U16 u16Ordinal2)
{
    if( msAPI_CHPROC_CM_Get_Weighting(u16Ordinal1) > msAPI_CHPROC_CM_Get_Weighting(u16Ordinal2) )
        return 1;
    else
        return -1;
}

#define DEBUG_SORT(x)   //x
void msAPI_CHPROC_CM_SortOridinalList(void)
{
    DEBUG_ORD_LIST( printf("msAPI_CHPROC_CM_SortOridinalList()\n"); );


    // Sort
    U16 u16ProgCount = Get_MAXOridinal();

    U16 u16Ord1, u16Ord2;
    for( u16Ord1 = 0; u16Ord1 < (u16ProgCount-1); u16Ord1 += 1 ) // For 0 ~ N-1
    {
        for( u16Ord2 = u16Ord1+1; u16Ord2 < u16ProgCount; u16Ord2 += 1 )
        {
            //printf("%u %u\n", u16Ord1, u16Ord2 );

            if( msAPI_CHPROC_CM_Compare(u16Ord1, u16Ord2) > 0 )
            { // If u16Ord1 < u16Ord2, swap it
                SwapOridinal(u16Ord1, u16Ord2);
            }
        }
    }

    //DEBUG_SORT(msAPI_CHPROC_ORD_PrintOridialList(););
}

/******************************************************************************/
/// -This function will reset ordinalList
/// @param \b IN:
/// - None
/// @return
/// - None
/******************************************************************************/
void msAPI_CHPROC_CM_ResetOridial(void)
{
    U16 u16Loop;

    Set_MAXOridinal(0);

    memset( aOridinalList, 0, sizeof(aOridinalList) );

    for(u16Loop=0; u16Loop < MAX_ATV_DTV ;u16Loop++)
    {
        aOridinalList[u16Loop].u16LCN = INVALID_LOGICAL_CHANNEL_NUMBER;
        aOridinalList[u16Loop].eServicetype = E_SERVICETYPE_INVALID;
        aOridinalList[u16Loop].wPosition = INVALID_POSITION;
    }
}

#if( ENABLE_SBTVD_CM_APP )
extern BYTE msAPI_ATV_GetNextActiveProgNum(BYTE u8ProgramNumber);

void msAPI_CHPROC_CM_InitOridial_Brazil(void)
{
    U16 u16_DTVcount,u16_RADIOcount,u16Loop,u16Loop_1,u16ListIndex,u16MAX_Count;
    U8  u8_ATVcount, U8ATV_Index, u8DTV_Index;
    WORD wMinOrder,wMinLCN,wCurrentLCN;
    BYTE bMinPHY,bCurrentPhy;

    u8_ATVcount = msAPI_ATV_GetActiveProgramCount();
    u16_DTVcount = msAPI_CM_CountProgram(E_SERVICETYPE_DTV,E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
    u16_RADIOcount = msAPI_CM_CountProgram(E_SERVICETYPE_RADIO,E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);

    if(u8_ATVcount > MAX_ATVPROGRAM || u16_DTVcount > MAX_DTVPROGRAM || u16_RADIOcount > MAX_DTVPROGRAM)
    {
        __ASSERT(0);
    }

    //printf("\n Isaac u8_ATVcount= %bu   %u  %u \n",u8_ATVcount,u16_DTVcount,u16_RADIOcount);
    if(!(u8_ATVcount | u16_DTVcount | u16_RADIOcount))
        return;

    U8ATV_Index = u8DTV_Index = 0;
    u16ListIndex =0;

    for(u16Loop=0;u16Loop< MAX_ATV_DTV ;u16Loop++)
    {
        aOridinalList[u16Loop].eServicetype = E_SERVICETYPE_INVALID;
        aOridinalList[u16Loop].u16LCN = INVALID_LOGICAL_CHANNEL_NUMBER;
        aOridinalList[u16Loop].wPosition = INVALID_POSITION;
    }

    u16MAX_Count = MAX(MAX(u8_ATVcount,u16_DTVcount),u16_RADIOcount);

    for(u16Loop=0;u16Loop< u16MAX_Count ;u16Loop++)
    {
        if(u8_ATVcount && (u16Loop < u8_ATVcount))
        {
            aOridinalList[u16Loop].eServicetype = E_SERVICETYPE_ATV;
            if(!u16Loop)
                aOridinalList[u16Loop].u16LCN = (U16)(msAPI_ATV_GetFirstProgramNumber(FALSE)<< 8);
            else
                aOridinalList[u16Loop].u16LCN = (U16)(msAPI_ATV_GetNextActiveProgNum(aOridinalList[u16Loop-1].u16LCN >> 8)<< 8);
            aOridinalList[u16Loop].wPosition = aOridinalList[u16Loop].u16LCN; //INVALID_POSITION;
        }

        if(u16_DTVcount && ( u16Loop < u16_DTVcount))
        {
            aOridinalList[u16Loop+u8_ATVcount].eServicetype = E_SERVICETYPE_DTV;
            aOridinalList[u16Loop+u8_ATVcount].u16LCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_DTV,u16Loop);
            aOridinalList[u16Loop+u8_ATVcount].wPosition = u16Loop;
        }

        if(u16_RADIOcount && (u16Loop < u16_RADIOcount))
        {
            aOridinalList[u16Loop+u8_ATVcount+u16_DTVcount].eServicetype = E_SERVICETYPE_RADIO;
            aOridinalList[u16Loop+u8_ATVcount+u16_DTVcount].u16LCN = msAPI_CM_GetLogicalChannelNumber(E_SERVICETYPE_RADIO,u16Loop);
            aOridinalList[u16Loop+u8_ATVcount+u16_DTVcount].wPosition = u16Loop;
        }
    }

    u16MAX_Count = u8_ATVcount+u16_DTVcount+u16_RADIOcount;
    Set_MAXOridinal(u16MAX_Count);

    /*for(u16Loop_1=0; u16Loop_1 < u16MAX_Count; u16Loop_1++)
        printf("\n Isaac Before u16Loop= %u eServicetype=%bu  u16LCN= %u  wPosition= %u  PHY= %bu \n",u16Loop_1,aOridinalList[u16Loop_1].eServicetype,aOridinalList[u16Loop_1].u16LCN,aOridinalList[u16Loop_1].wPosition,aOridinalList[u16Loop_1].stLCN.bPhysicalChannel);
    */
    for(u16Loop= 0;u16Loop < u16MAX_Count;u16Loop++)
    {
        wMinOrder = u16Loop;
        if(aOridinalList[u16Loop].eServicetype == E_SERVICETYPE_ATV)
            wMinLCN = aOridinalList[u16Loop].u16LCN + 0x100;
        else
            wMinLCN = aOridinalList[u16Loop].u16LCN;
        bMinPHY = aOridinalList[u16Loop].stLCN.bPhysicalChannel;

        for(u16Loop_1=u16Loop+1; u16Loop_1 < u16MAX_Count; u16Loop_1++)
        {
            if(aOridinalList[u16Loop_1].eServicetype == E_SERVICETYPE_ATV)
                wCurrentLCN = aOridinalList[u16Loop_1].u16LCN + 0x100;
            else
                wCurrentLCN = aOridinalList[u16Loop_1].u16LCN;
            bCurrentPhy = aOridinalList[u16Loop_1].stLCN.bPhysicalChannel;

            if(wMinLCN > wCurrentLCN)
            {
                wMinLCN =  wCurrentLCN;
                wMinOrder =  u16Loop_1;
            }
            else if(wMinLCN == wCurrentLCN)
            {
                if(msAPI_CM_GetPhysicalChannelNumber(aOridinalList[u16Loop].eServicetype,aOridinalList[u16Loop].wPosition)
                    >msAPI_CM_GetPhysicalChannelNumber(aOridinalList[u16Loop_1].eServicetype,aOridinalList[u16Loop].wPosition))
                {
                    wMinLCN =  wCurrentLCN;
                    wMinOrder =  u16Loop_1;
                }
            }
        }

        if( wMinOrder != u16Loop )
        {
            #if ( WATCH_DOG == ENABLE )
            msAPI_Timer_ResetWDT();
            #endif

            SwapOridinal(wMinOrder, u16Loop);
        }
    }
    /*
    for(u16Loop_1=0; u16Loop_1 < u16MAX_Count; u16Loop_1++)
        printf("\n Isaac After u16Loop= %u eServicetype=%bu  u16LCN= %u  wPosition= %u \n",u16Loop_1,aOridinalList[u16Loop_1].eServicetype,aOridinalList[u16Loop_1].u16LCN,aOridinalList[u16Loop_1].wPosition);
    */
}
#endif

void msAPI_CHPROC_CM_InitOridial(void)
{
    DEBUG_ORD_LIST( PRINT_CURRENT_LINE(); );

    if( msAPI_DtvSys_Is_SortByLCN() )
        g_ChProc_eSortType = CH_PROC_SORT_DTV_LCN__ATV;
    else
        g_ChProc_eSortType = CH_PROC_SORT_DTV_RADIO_DATA_ATV;


#if( ENABLE_SBTVD_CM_APP )
    msAPI_CHPROC_CM_InitOridial_Brazil();

#elif(ENABLE_DVB)

    // Get all TV program data
    MEMBER_SERVICETYPE eServiceType;
    U8 u8DtvServiceIdx;
    U16 u16ProgCount;
    U16 u16Position;
    U16 u16OrdinalCount = 0;
    U16 u16LCN;


    // Reset all
    msAPI_CHPROC_CM_ResetOridial();

    // Get all DTV data...
    for(u8DtvServiceIdx = E_SERVICETYPE_DTV; u8DtvServiceIdx <= E_SERVICETYPE_DATA; ++ u8DtvServiceIdx )
    {
        eServiceType = (MEMBER_SERVICETYPE)u8DtvServiceIdx;

    #if(!NORDIG_FUNC)
        if( eServiceType == E_SERVICETYPE_DATA )
            break;
    #endif

        u16ProgCount = msAPI_CM_CountProgram(eServiceType,E_PROGACESS_INCLUDE_NOT_VISIBLE_ALSO);
        printf("Get Sevice=%u, count=%u\n", eServiceType, u16ProgCount );
        for( u16Position = 0; u16Position < u16ProgCount; ++ u16Position )
        {
            if( u16OrdinalCount >= (MAX_ATV_DTV-1) )
            {
                break;
            }

            aOridinalList[u16OrdinalCount].eServicetype = eServiceType;
            aOridinalList[u16OrdinalCount].wPosition = u16Position;

            u16LCN = msAPI_CM_GetLogicalChannelNumber(eServiceType, u16Position);
            aOridinalList[u16OrdinalCount].u16LCN = u16LCN;

            aOridinalList[u16OrdinalCount].bIsFav = msAPI_CM_GetProgramAttribute(eServiceType, u16Position, E_ATTRIBUTE_IS_FAVORITE);
            DEBUG_ORD_LIST( printf("%u Pos=%u, LCN=%u, Fav=%u\n", u16OrdinalCount, u16Position, u16LCN, aOridinalList[u16OrdinalCount].bIsFav ); );

            u16OrdinalCount += 1;
        }
    }


    // Get all ATV data...
    if( !IsS2InUse() )
    {
        U8 u8ProgramNumber;

        u16ProgCount = msAPI_ATV_GetActiveProgramCount();
        printf("Get Sevice_ATV, count=%u\n", u16ProgCount );
        for( u16Position = 0; u16Position < u16ProgCount; ++ u16Position )
        {
            if( u16OrdinalCount >= (MAX_ATV_DTV-1) )
            {
                break;
            }

            aOridinalList[u16OrdinalCount].eServicetype = E_SERVICETYPE_ATV;
            aOridinalList[u16OrdinalCount].wPosition = u16Position;

            u8ProgramNumber = msAPI_ATV_ConvertOrdinalNumberToProgramNumber(u16Position);
            aOridinalList[u16OrdinalCount].u16ProgramNumber = u8ProgramNumber;

            aOridinalList[u16OrdinalCount].bIsFav = msAPI_ATV_IsProgramFavorite(u8ProgramNumber);

            DEBUG_ORD_LIST( printf("%u Pos=%u, ProgNum=%u, Fav=%u\n", u16OrdinalCount, u16Position, u8ProgramNumber, aOridinalList[u16OrdinalCount].bIsFav); );

            u16OrdinalCount += 1;
        }
    }

    Set_MAXOridinal(u16OrdinalCount);

    DEBUG_SORT( msAPI_CHPROC_ORD_PrintOridialList(); );

    msAPI_CHPROC_CM_SortOridinalList();

    DEBUG_ORD_LIST( msAPI_CHPROC_ORD_PrintOridialList(); );

#endif
}

static BOOLEAN SwapOridinal(WORD wFromOrder, WORD wToOrder)
{
    if( wFromOrder >= Get_MAXOridinal() )
        return FALSE;

    if( wToOrder >= Get_MAXOridinal() )
        return FALSE;

    if( wFromOrder == wToOrder )
    {
        return TRUE;
    }

    StruOrdinalInfo stOridinalTmp;

    stOridinalTmp = aOridinalList[wFromOrder];
    aOridinalList[wFromOrder] = aOridinalList[wToOrder];
    aOridinalList[wToOrder] = stOridinalTmp;

    return TRUE;
}

#if( ENABLE_SBTVD_CM_APP )

WORD msAPI_CHPROC_CM_GetOrdinal_Brazil(MEMBER_SERVICETYPE bServiceType,WORD wPosition)
{
    U16 u16Max_Ori,u16Loop;

    u16Max_Ori = Get_MAXOridinal();

    if(bServiceType == E_SERVICETYPE_ATV )
        wPosition = (U16)(wPosition << 8);

    for(u16Loop=0;u16Loop<u16Max_Ori;u16Loop++)
    {
         if(aOridinalList[u16Loop].eServicetype == bServiceType &&
            aOridinalList[u16Loop].wPosition == wPosition )
         return  u16Loop;
    }
    return INVALID_POSITION;
}

MEMBER_SERVICETYPE msAPI_CHPROC_CM_GetServiceTypeByLCN_Brazil(WORD wLCN,WORD * wOridinal)
{
    U16 u16Max_Ori,u16Loop;
    //MEMBER_SERVICETYPE bServiceType;

    if(ANT_CATV == msAPI_ATV_GetCurrentAntenna())
    {
        return E_SERVICETYPE_ATV;
    }

    u16Max_Ori = Get_MAXOridinal();

    for(u16Loop=0;u16Loop<u16Max_Ori;u16Loop++)
    {
         if( aOridinalList[u16Loop].u16LCN == wLCN )
         {
            *wOridinal = u16Loop;
            return  aOridinalList[u16Loop].eServicetype;
         }
    }

    if(u16Loop == u16Max_Ori)
    {
        wLCN = (U16)((wLCN -1) << 8);

        for(u16Loop=0;u16Loop<u16Max_Ori;u16Loop++)
        {
             if( aOridinalList[u16Loop].u16LCN == wLCN )
             {
                *wOridinal = u16Loop;
                return  aOridinalList[u16Loop].eServicetype;
             }
        }
    }

    UNUSED(*wOridinal);

    return E_SERVICETYPE_INVALID;
}

BOOLEAN msAPI_CHPROC_CM_GetOrdinal_SerType_Position_Brazil(WORD wOridinal,MEMBER_SERVICETYPE * pbServiceType,WORD * pwPosition)
{
    if( wOridinal >= Get_MAXOridinal() )
    {
        *pbServiceType = E_SERVICETYPE_INVALID;
        return FALSE;
    }

    //*pbServiceType = E_SERVICETYPE_INVALID;
    *pbServiceType = aOridinalList[wOridinal].eServicetype;
    *pwPosition =    aOridinalList[wOridinal].wPosition;

    if( *pbServiceType == E_SERVICETYPE_INVALID)
        return FALSE;
    else
        return TRUE;
}
#endif

#endif // ENABLE_CHPROC_ORDINAL_LIST// ENABLE_SBTVD_CM_APP


#if(ENABLE_S2_FIND_PROGRAM_BYNAME)
WORD msAPI_CHPROC_CM_CountFindProgramByName(MEMBER_SERVICETYPE bServiceType,BYTE *bProgramName)
{
    switch(bServiceType)
    {
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
    case E_SERVICETYPE_DATA:
    case E_SERVICETYPE_UNITED_TV:
        return msAPI_CM_CountFindProgramByName(bServiceType,bProgramName);
    //case E_SERVICETYPE_UNITED_TV:
        //return msAPI_CM_CountFindProgramByName(E_SERVICETYPE_DTV,bProgramName) +  msAPI_CM_CountFindProgramByName(E_SERVICETYPE_DATA,bProgramName) + msAPI_CM_CountFindProgramByName(E_SERVICETYPE_RADIO,bProgramName);
    default:
        break;

    }

    return 0;
}

WORD msAPI_CHPROC_CM_GetPrevFindProgramByNameOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped,BYTE *bProgramName)
{
    WORD wProgramPosition=0;
    switch(bServiceType)
    {
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
    case E_SERVICETYPE_DATA:
    case E_SERVICETYPE_UNITED_TV:

        wProgramPosition = msAPI_CM_GetPrevFindProgramByNamePosition(bServiceType, wBaseOrdinal, bIncludeSkipped,bProgramName);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition >= wBaseOrdinal) )
        {
            return INVALID_ORDINAL;
        }
        else
        {
            return wProgramPosition;
        }
        break;
    default:
        break;
    }
    return INVALID_ORDINAL;
}

WORD msAPI_CHPROC_CM_GetNextFindProgramByNameOrdinal(MEMBER_SERVICETYPE bServiceType, WORD wBaseOrdinal, BOOLEAN bIncludeSkipped,BYTE *bProgramName)
{
    WORD wProgramPosition=0;
    switch(bServiceType)
    {
    case E_SERVICETYPE_RADIO:
    case E_SERVICETYPE_DTV:
    case E_SERVICETYPE_DATA:
    case E_SERVICETYPE_UNITED_TV:

        wProgramPosition = msAPI_CM_GetNextFindProgramByNamePosition(bServiceType, wBaseOrdinal, bIncludeSkipped,bProgramName);
        if( (wProgramPosition == INVALID_PROGRAM_POSITION) ||
            (wProgramPosition <= wBaseOrdinal) )
        {
            return INVALID_ORDINAL;
        }
        else
        {
            return wProgramPosition;
        }
        break;
    default:
        break;
    }
    return INVALID_ORDINAL;
}
#endif

