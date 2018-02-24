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

#define MAPP_CHANNEL_LIST_C

/******************************************************************************/
/*                 Header Files                                               */
/* ****************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "MsCommon.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "msAPI_ATVSystem.h"
#include "msAPI_ChProc.h"
#include "msAPI_DTVSystem.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
#include "msAPI_Timer.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif

#include "MApp_DataBase.h"
#include "MApp_InputSource.h"
#include "MApp_GlobalVar.h"
#include "MApp_ChannelList.h"
#include "MApp_ChannelChange.h"
#include "MApp_ChannelList.h"
#include "MApp_UiMenuDef.h"
#include "MApp_TV.h"
#include "MApp_ATVProc.h"
#include "MApp_GlobalFunction.h"

#if (ENABLE_PIP)
#include "MApp_PIP.h"
#endif

#if ENABLE_ISDBT
extern E_ANTENNA_SOURCE_TYPE enLastWatchAntennaType;
#endif
/********************************************************************************/
/*                    Macro                                                     */
/********************************************************************************/
#define CHANNEL_LIST_DBINFO(y)    //y
#define FAVORITE_LIST_DBINFO(y)   //y
#define RECENT_LIST_DBINFO(y)     //y

U16 volatile u16LastWatchedOridinal;

void _MApp_ChannelList_ChannelChange(U16 u16ListOrdinal, U8 u8CMType, BOOLEAN bShowInfo, E_MEMBER_PROGRAM_ACCESSIBLE_BOUNDARY eProgramAccessibleBoundary)
{
#if (ENABLE_DTV)
    EN_SERVICE_TYPE u8ListType, u8CurrentType = SERVICE_TYPE_INVALIDE;

#if(ENABLE_PIP)
    if (IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
        ||(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))&& (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
#else
    if ( IsDTVInUse() )
#endif
    {
        u8CurrentType = (EN_SERVICE_TYPE)msAPI_CM_GetCurrentServiceType();
    }
  #if(ENABLE_PIP)
    else if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW))
            ||(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))&& (MApp_Get_PIPMode() != EN_PIP_MODE_OFF)))
  #else
    else if ( IsATVInUse() )
  #endif
    {
        u8CurrentType = SERVICE_TYPE_ATV;
    }

#if (ENABLE_CI && MEDIASET_PREMIUM_SMART_CAM)
    if ( IsDTVInUse() )
    {
        msAPI_CI_HSS_Active(TRUE);
    }
#endif

    //Cancel Freeze
    if(g_bIsImageFrozen)
    {
        g_bIsImageFrozen = FALSE;
        MApi_XC_FreezeImg(g_bIsImageFrozen, MAIN_WINDOW);
    }

    msAPI_CHPROC_CM_GetAttributeOfOrdinal((MEMBER_SERVICETYPE)u8CMType, u16ListOrdinal, (BYTE *)&u8ListType, E_SERVICE_ATTR_TYPE, eProgramAccessibleBoundary);

    if (u8ListType != u8CurrentType)
    {
        #if (ENABLE_PIP)
        BOOLEAN bCompatible = TRUE;
        //Check compatibility
        if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
        {
            if(u8ListType == SERVICE_TYPE_ATV && u8CurrentType != SERVICE_TYPE_ATV)
            {
                CHANNEL_LIST_DBINFO(printf("DTV --> ATV     "));
                if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
                {
                    CHANNEL_LIST_DBINFO(printf("[MAIN_WINDOW]\n"));
                    bCompatible = MApp_InputSource_PIP_IsSrcCompatible(INPUT_SOURCE_TV, SYS_INPUT_SOURCE_TYPE(SUB_WINDOW));
                }
                else if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
                {
                    CHANNEL_LIST_DBINFO(printf("[SUB_WINDOW]\n"));
                    bCompatible = MApp_InputSource_PIP_IsSrcCompatible(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), INPUT_SOURCE_TV);
                }
                CHANNEL_LIST_DBINFO(printf("    - bCompatible = 0x%x\n", (U16)bCompatible));
            }
        }
        #endif

        if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
        {
            //PIP behavior: If main window will switch from DTV to ATV and sub source is not
            //                compatible with main source, sub window should be closed.
            #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && !bCompatible)
            {
                CHANNEL_LIST_DBINFO(printf("[Action] Close sub window.\n"));
                //Close sub window and set compatible source type to sub win
                MApp_ClosePIPSubWindowSource();
            }
            #endif
            MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
        }

        #if (ENABLE_PIP)
        if(IsPIPSupported())
        {
            if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
            {
                //PIP behavior: If sub window will switch from DTV to ATV, need to check compatibility with main window.
                //                If not compatible, do not allow switch sub window to ATV.
                if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
                {
                    if(!bCompatible)
                    {
                        CHANNEL_LIST_DBINFO(printf("[Action] Do not allow sub window switch to ATV\n"));
                    }
                    else
                    {
                        MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                    }
                }
            }
        }
        #endif

        dmSetLastWatchedOrdinal();
        if (u8CurrentType == SERVICE_TYPE_ATV)
        {
            // I think : No need close filter here!
            //MApp_Dmx_CloseAllFilters();

            if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
            #if 1 // 20150908
                MApp_InputSrc_ChangeToLastUiDtvSrc();
            #else
                #if ENABLE_S2
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                #elif ENABLE_DVBT
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                #elif ENABLE_DVBC
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                #elif ENABLE_DTMB
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                #elif ENABLE_ISDBT
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                #endif

                MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
            #endif
            }
            #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
            {
                if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && bCompatible)
                {
                    #if ENABLE_S2
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                    #elif ENABLE_DVBT
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                    #elif ENABLE_DVBC
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                    #elif ENABLE_DTMB
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                    #elif ENABLE_ISDBT
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                    #else
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                    #endif

                    MApp_InputSource_SwitchSource(UI_SUB_INPUT_SOURCE_TYPE, SUB_WINDOW);
                }
            }
            #endif

        #if(ENABLE_API_DTV_SYSTEM)
            msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)u8ListType);
        #endif
        }
        else if (u8ListType == SERVICE_TYPE_ATV)
        {
            if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                UI_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ATV;
                MApp_InputSource_SwitchSource(UI_INPUT_SOURCE_TYPE, MAIN_WINDOW);
            }
            #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
            {
                if(IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) && bCompatible)
                {
                    #if ENABLE_S2
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_S2;
                    #elif ENABLE_DVBT
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                    #elif ENABLE_DVBC
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBC;
                    #elif ENABLE_DTMB
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DTMB;
                    #elif ENABLE_ISDBT
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_ISDBT;
                    #else
                    UI_SUB_INPUT_SOURCE_TYPE = UI_INPUT_SOURCE_DVBT;
                    #endif

                    MApp_InputSource_SwitchSource(UI_SUB_INPUT_SOURCE_TYPE, SUB_WINDOW);
                }
            }
            #endif
        }
        else
        {
        #if(ENABLE_API_DTV_SYSTEM)
            msAPI_CM_SetCurrentServiceType((MEMBER_SERVICETYPE)u8ListType);
        #endif
        }

        msAPI_CHPROC_CM_SetCurrentOrdinal((MEMBER_SERVICETYPE)u8CMType, u16ListOrdinal, eProgramAccessibleBoundary);

        if (bShowInfo)
        {
            bNextEvent = FALSE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
        }

        #if (ENABLE_PIP)
        if(IsPIPSupported())
        {
            if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
            {
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            }
            else if(IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)))
            {
                if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF) && bCompatible)
                {
                    MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                }
            }
        }
        else
        #endif
        {
            MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
        }
    }
    else
#endif
    {
       // if (u16ListOrdinal != u16CurrentOrdinal)
        {
            if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)) )
            {
                MApp_ChannelChange_DisableChannel(TRUE,MAIN_WINDOW);
            }
            #if (ENABLE_PIP)
            if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF))
            {
                if( IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) )
                {
                    MApp_ChannelChange_DisableChannel(TRUE,SUB_WINDOW);
                }
            }
            #endif
            dmSetLastWatchedOrdinal();
            msAPI_CHPROC_CM_SetCurrentOrdinal((MEMBER_SERVICETYPE)u8CMType, u16ListOrdinal,  eProgramAccessibleBoundary);

            if (bShowInfo)
            {
                bNextEvent = FALSE;
                u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            }
            #if (ENABLE_PIP)
            if(IsPIPSupported())
            {
                if((MApp_Get_PIPMode() != EN_PIP_MODE_OFF)
                    && (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW)) || IsSrcTypeDTV(SYS_INPUT_SOURCE_TYPE(SUB_WINDOW))))
                {
                    MApp_ChannelChange_EnableChannel(SUB_WINDOW);
                }
                else
                {
                    MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
                }
            }
            else
            #endif
            {
                MApp_ChannelChange_EnableChannel(MAIN_WINDOW);
            }
        }
    }
}

// ========== temp, wait for CM to give this value ==========
void dmSetLastWatchedOrdinal(void)
{
  #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM )
    BOOLEAN  PerDirectTuneFlag=msAPI_ATV_GetDirectTuneFlag();
    msAPI_ATV_SetDirectTuneFlag(TRUE);
  #endif

    U16 u16CurrentOrdinal = msAPI_CHPROC_CM_GetCurrentOrdinal(E_SERVICETYPE_UNITED_TV, E_PROGACESS_INCLUDE_VISIBLE_ONLY);
    if(u16CurrentOrdinal==INVALID_ORDINAL)
    {
        u16CurrentOrdinal=0;
    }

  #if ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM )
    msAPI_ATV_SetDirectTuneFlag(PerDirectTuneFlag);
  #endif

    RECENT_LIST_DBINFO(printf("Set %u to last watched ordinal.\n", u16CurrentOrdinal););
    u16LastWatchedOridinal = u16CurrentOrdinal;

#if( ENABLE_ISDBT )
  #if( ENABLE_ISDBT_AND_DVB )
    if( IS_COUNTRY_USE_SBTVD() )
  #endif
    {
        if( msAPI_ATV_GetCurrentAntenna() == ANT_AIR )
        {
            if( IsDTVInUse())
            {
                enLastWatchAntennaType = ANTENNA_DTV_TYPE;
            }
            else if( IsATVInUse())
            {
                enLastWatchAntennaType = ANTENNA_ATV_TYPE;
            }
            else
            {
            }
        }
    }
#endif
}

U16 dmGetLastWatchOrdinal(void)
{
    return u16LastWatchedOridinal;
}

#undef MAPP_CHANNEL_LIST_C

