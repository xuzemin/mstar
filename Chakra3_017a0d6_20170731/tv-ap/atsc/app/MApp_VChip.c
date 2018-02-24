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

#define MAPP_VCHIP_C

//==============================================================================
/*                 Header Files                                                 */
//==============================================================================
#include <string.h>
#include <stdio.h>
#include "Board.h"
#include "datatype.h"
#include "msAPI_Timer.h"
#include "msAPI_audio.h"
#include "apiGOP.h"
//#include "apiXC.h"
//#include "apiXC_Adc.h"
#include "apiVDEC.h"
#include "msAPI_VD.h"
#include "mapi_cc_monitor.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"

#if (ENABLE_ATSC_VCHIP)
#include "MApp_ChannelProc_ATSC.h"
#include "MApp_Psip.h"
#include "MApp_EpgDB_ATSC.h"
#else
#include "MApp_BlockSys.h"
#endif

//#include "MApp_Audio.h"
#include "MApp_VChip.h"
#include "MApp_ChannelChange.h"
#include "MApp_PCMode.h"
#include "MApp_GlobalFunction.h"
#include "MApp_ZUI_ACTglobal.h"
#include "MApp_ZUI_APIstrings.h"
#include "OSDcp_String_EnumIndex.h"

#if((ENABLE_ATSC_VCHIP)||(ATSC_CC == ATV_CC)||ENABLE_ISDB_ATV_VCHIP)

#define VCHIP_DBINFO(y) //y
//==============================================================================
/*                    Macro                                                     */
//==============================================================================
#define VCHIP_MONITOR_PERIOD    500//100 /* ms */
#define VCHIP_NONE_CHECK_COUNT         20

//==============================================================================
/*                    Local                                                     */
//==============================================================================
static U32 u32MonitorVChipTimer;
static MS_U8 u32MonitorVChipFlag;
static U8 g_ucVChipNoRatingCounter;
static MS_U8 fPreVChipBlockStatus, fCurVChipBlockStatus;
static MS_U8 fRatingUpdateStatus;


//==============================================================================
/*                    Functions                                                 */
//==============================================================================
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if (ENABLE_ATSC_VCHIP)
#define DBG_E2R(msg) //msg
void MApp_VChip_EPGRating2RatingInfo(MS_EPG_RATING *pstCurEvn, MS_VCHIP_RATING_INFO *pstVChipRatingInfo)
{
    DBG_E2R(printf("\n[MApp_VChip_EPGRating2RatingInfo] %lx, %bx, %bx", (U32)pstCurEvn, (U8)pstCurEvn->fRatingRxIsOK, (U8)pstCurEvn->u8TVRatingForEntire));

    if (pstVChipRatingInfo)
        memset(pstVChipRatingInfo, 0, sizeof(MS_VCHIP_RATING_INFO));
    else
        return;

    if (pstCurEvn->fRatingRxIsOK)
    {
        if (pstCurEvn->u8TVRatingForEntire == INVALID_TV_RATING_FOR_ENTIRE) // make sure tv rating has received from CAD
        {
            pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_INVALID;
        }
        else
        {
            pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_TV;

            switch (pstCurEvn->u8TVRatingForEntire)
            {
                case 0:
                    if (pstCurEvn->u8TVRatingForChild == 1)
                    {
                        DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_TV_Y"););
                        pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_TV_Y;
                    }
                    else if (pstCurEvn->u8TVRatingForChild == 2)
                    {
                        DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_TV_Y7"););
                        pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_TV_Y7;

                        if (pstCurEvn->fFantasyViolence == 1)
                        {
                            DBG_E2R(printf("\nVCHIP_TVRATING_FV"););
                            pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_FV;
                        }
                    }
                    break;
                case 1:
                    pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_NONE;
                    DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_NONE"););
                    break;
                case 2:
                    pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_TV_G;
                    DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_TV_G"););
                    break;
                case 3:
                    pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_TV_PG;
                    DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_TV_PG"););
                    break;
                case 4:
                    pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_TV_14;
                    DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_TV_14"););
                    break;
                case 5:
                    pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_TV_MA;
                    DBG_E2R(printf("\nRatingLevel = VCHIP_TVRATING_TV_MA"););
                    break;
#if 0
                // Just ignore undefined values. Or TV-NONE is shown. According to CEA-766-A,
                // no message is displayed.
                default:
                    DBG_E2R(printf("\nERROR RatingLevel = VCHIP_TVRATING_NONE"););
                    pstVChipRatingInfo->RatingLevel = VCHIP_TVRATING_NONE;
#endif
            }

            if (pstVChipRatingInfo->RatingLevel == VCHIP_TVRATING_TV_PG
                || pstVChipRatingInfo->RatingLevel == VCHIP_TVRATING_TV_14)
            {
                if (pstCurEvn->fDialog == 1)
                {
                    pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_D;
                    DBG_E2R(printf("\nVCHIP_TVRATING_D"););
                }
            }

            if (pstVChipRatingInfo->RatingLevel == VCHIP_TVRATING_TV_PG
                || pstVChipRatingInfo->RatingLevel == VCHIP_TVRATING_TV_14
                || pstVChipRatingInfo->RatingLevel == VCHIP_TVRATING_TV_MA)
            {
                if (pstCurEvn->fLanguage == 1)
                {
                    DBG_E2R(printf("\nVCHIP_TVRATING_L"););
                    pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_L;
                }
                if (pstCurEvn->fSexualContent == 1)
                {
                    DBG_E2R(printf("\nVCHIP_TVRATING_S"););
                    pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_S;
                }
                if (pstCurEvn->fViolence == 1)
                {
                    DBG_E2R(printf("\nVCHIP_TVRATING_V"););
                    pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_V;
                }
            }
        }

        if (pstCurEvn->u8MPAAFlag)
        {
            pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_MPAA;
            pstVChipRatingInfo->MPAALevel = pstCurEvn->u8MPAARatingD2;
            DBG_E2R(printf("\nRatingType = VCHIP_RATING_TYPE_MPAA %bu", pstVChipRatingInfo->MPAALevel););
        }

        /* Canada */
        if (pstCurEvn->u8CaEngFlag)
        {
            pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_CANADA_ENG;
            pstVChipRatingInfo->CanEngLevel = pstCurEvn->u8CaEngRatingD0;
            DBG_E2R(printf("\nRatingType = VCHIP_RATING_TYPE_CANADA_ENG %bu", pstVChipRatingInfo->CanEngLevel););
        }

        if (pstCurEvn->u8CaFreFlag)
        {
            pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_CANADA_FRE;
            pstVChipRatingInfo->CanFreLevel = pstCurEvn->u8CaFreRatingD1;
            DBG_E2R(printf("\nRatingType = VCHIP_RATING_TYPE_CANADA_FRE %bu", pstVChipRatingInfo->CanFreLevel););
        }

        DBG_E2R(
        printf("\nCa and MPAA: %bu %bu %bu", pstCurEvn->u8CaEngFlag, pstCurEvn->u8CaFreFlag, pstCurEvn->u8MPAAFlag);
        printf("\nReceived RRT lock info: %x %x %x %x %x %x %x %x %x %x",
            (U16)pstCurEvn->u8DownloadableRatingD1,
            (U16)pstCurEvn->u8DownloadableRatingD2,
            (U16)pstCurEvn->u8DownloadableRatingD3,
            (U16)pstCurEvn->u8DownloadableRatingD4,
            (U16)pstCurEvn->u8DownloadableRatingD5,
            (U16)pstCurEvn->u8DownloadableRatingD6,
            (U16)pstCurEvn->u8DownloadableRatingD7,
            (U16)pstCurEvn->u8DownloadableRatingD8,
            (U16)pstCurEvn->u8DownloadableRatingD9,
            (U16)pstCurEvn->u8DownloadableRatingD10););

        // This if sentence is marked out. Because
        // there are posibilities that region 1 and region 5 exists at the same time
        // ex. Sarnoff RRT test stream R24MSR.trp
        // if ( (pstCurEvn->u8CaEngFlag==0) && (pstCurEvn->u8CaFreFlag==0) && (pstCurEvn->u8MPAAFlag==0) ) // Downloadable RRT
        {
            if ( (pstCurEvn->u8DownloadableRatingD1 != 0)||
                 (pstCurEvn->u8DownloadableRatingD2 != 0)||
                 (pstCurEvn->u8DownloadableRatingD3 != 0)||
                 (pstCurEvn->u8DownloadableRatingD4 != 0)||
                 (pstCurEvn->u8DownloadableRatingD5 != 0)||
                 (pstCurEvn->u8DownloadableRatingD6 != 0)||
                 (pstCurEvn->u8DownloadableRatingD7 != 0)||
                 (pstCurEvn->u8DownloadableRatingD8 != 0)||
                 (pstCurEvn->u8DownloadableRatingD9 != 0)||
                 (pstCurEvn->u8DownloadableRatingD10 != 0)
#if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
			  || (pstCurEvn->u8DownloadableRatingD11 != 0)||
                 (pstCurEvn->u8DownloadableRatingD12 != 0)||
                 (pstCurEvn->u8DownloadableRatingD13 != 0)||
                 (pstCurEvn->u8DownloadableRatingD14 != 0)||
                 (pstCurEvn->u8DownloadableRatingD15 != 0)||
                 (pstCurEvn->u8DownloadableRatingD16 != 0)||
                 (pstCurEvn->u8DownloadableRatingD17 != 0)||
                 (pstCurEvn->u8DownloadableRatingD18 != 0)||
                 (pstCurEvn->u8DownloadableRatingD19 != 0)||
                 (pstCurEvn->u8DownloadableRatingD20 != 0)||
                 (pstCurEvn->u8DownloadableRatingD21 != 0)||
                 (pstCurEvn->u8DownloadableRatingD22 != 0)||
                 (pstCurEvn->u8DownloadableRatingD23 != 0)||
                 (pstCurEvn->u8DownloadableRatingD24 != 0)||
                 (pstCurEvn->u8DownloadableRatingD25 != 0)||
                 (pstCurEvn->u8DownloadableRatingD26 != 0)||
                 (pstCurEvn->u8DownloadableRatingD27 != 0)||
                 (pstCurEvn->u8DownloadableRatingD28 != 0)||
                 (pstCurEvn->u8DownloadableRatingD29 != 0)||
	   			 (pstCurEvn->u8DownloadableRatingD30 != 0)||
				 (pstCurEvn->u8DownloadableRatingD31 != 0)||
				 (pstCurEvn->u8DownloadableRatingD32 != 0)||
				 (pstCurEvn->u8DownloadableRatingD33 != 0)||
				 (pstCurEvn->u8DownloadableRatingD34 != 0)||
				 (pstCurEvn->u8DownloadableRatingD35 != 0)||
				 (pstCurEvn->u8DownloadableRatingD36 != 0)||
				 (pstCurEvn->u8DownloadableRatingD37 != 0)||
				 (pstCurEvn->u8DownloadableRatingD38 != 0)||
				 (pstCurEvn->u8DownloadableRatingD39 != 0)||
				 (pstCurEvn->u8DownloadableRatingD40 != 0)
#endif
                 )
            {
                pstVChipRatingInfo->u8DimVal0 = pstCurEvn->u8DownloadableRatingD1;
                pstVChipRatingInfo->u8DimVal1 = pstCurEvn->u8DownloadableRatingD2;
                pstVChipRatingInfo->u8DimVal2 = pstCurEvn->u8DownloadableRatingD3;
                pstVChipRatingInfo->u8DimVal3 = pstCurEvn->u8DownloadableRatingD4;
                pstVChipRatingInfo->u8DimVal4 = pstCurEvn->u8DownloadableRatingD5;
                pstVChipRatingInfo->u8DimVal5 = pstCurEvn->u8DownloadableRatingD6;
                pstVChipRatingInfo->u8DimVal6 = pstCurEvn->u8DownloadableRatingD7;
                pstVChipRatingInfo->u8DimVal7 = pstCurEvn->u8DownloadableRatingD8;
                pstVChipRatingInfo->u8DimVal8 = pstCurEvn->u8DownloadableRatingD9;
                pstVChipRatingInfo->u8DimVal9 = pstCurEvn->u8DownloadableRatingD10;
#if (ENABLE_MAX_RRT_DIMENSION_NUMBER)
				pstVChipRatingInfo->u8DimVal10 = pstCurEvn->u8DownloadableRatingD11;
				pstVChipRatingInfo->u8DimVal11 = pstCurEvn->u8DownloadableRatingD12;
				pstVChipRatingInfo->u8DimVal12 = pstCurEvn->u8DownloadableRatingD13;
				pstVChipRatingInfo->u8DimVal13 = pstCurEvn->u8DownloadableRatingD14;
				pstVChipRatingInfo->u8DimVal14 = pstCurEvn->u8DownloadableRatingD15;
				pstVChipRatingInfo->u8DimVal15 = pstCurEvn->u8DownloadableRatingD16;
				pstVChipRatingInfo->u8DimVal16 = pstCurEvn->u8DownloadableRatingD17;
				pstVChipRatingInfo->u8DimVal17 = pstCurEvn->u8DownloadableRatingD18;
				pstVChipRatingInfo->u8DimVal18 = pstCurEvn->u8DownloadableRatingD19;
				pstVChipRatingInfo->u8DimVal19 = pstCurEvn->u8DownloadableRatingD20;
				pstVChipRatingInfo->u8DimVal20 = pstCurEvn->u8DownloadableRatingD21;
				pstVChipRatingInfo->u8DimVal21 = pstCurEvn->u8DownloadableRatingD22;
				pstVChipRatingInfo->u8DimVal22 = pstCurEvn->u8DownloadableRatingD23;
				pstVChipRatingInfo->u8DimVal23 = pstCurEvn->u8DownloadableRatingD24;
				pstVChipRatingInfo->u8DimVal24 = pstCurEvn->u8DownloadableRatingD25;
				pstVChipRatingInfo->u8DimVal25 = pstCurEvn->u8DownloadableRatingD26;
				pstVChipRatingInfo->u8DimVal26 = pstCurEvn->u8DownloadableRatingD27;
				pstVChipRatingInfo->u8DimVal27 = pstCurEvn->u8DownloadableRatingD28;
				pstVChipRatingInfo->u8DimVal28 = pstCurEvn->u8DownloadableRatingD29;
				pstVChipRatingInfo->u8DimVal29 = pstCurEvn->u8DownloadableRatingD30;
				pstVChipRatingInfo->u8DimVal30 = pstCurEvn->u8DownloadableRatingD31;
				pstVChipRatingInfo->u8DimVal31 = pstCurEvn->u8DownloadableRatingD32;
				pstVChipRatingInfo->u8DimVal32 = pstCurEvn->u8DownloadableRatingD33;
				pstVChipRatingInfo->u8DimVal33 = pstCurEvn->u8DownloadableRatingD34;
				pstVChipRatingInfo->u8DimVal34 = pstCurEvn->u8DownloadableRatingD35;
				pstVChipRatingInfo->u8DimVal35 = pstCurEvn->u8DownloadableRatingD36;
				pstVChipRatingInfo->u8DimVal36 = pstCurEvn->u8DownloadableRatingD37;
				pstVChipRatingInfo->u8DimVal37 = pstCurEvn->u8DownloadableRatingD38;
				pstVChipRatingInfo->u8DimVal38 = pstCurEvn->u8DownloadableRatingD39;
				pstVChipRatingInfo->u8DimVal39 = pstCurEvn->u8DownloadableRatingD40;
				pstVChipRatingInfo->u8DimVal40 = pstCurEvn->u8DownloadableRatingD41;
#endif
                pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
                DBG_E2R(printf("\npstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5\n"));
            }
        }
    }
}
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void MApp_VChip_Init(void)
{
    VDEC_Status vdecStatus;
    memset(&vdecStatus, 0, sizeof(VDEC_Status));
    //MS_BOOL bRet = MApi_VDEC_GetStatus(&vdecStatus);

    u32MonitorVChipFlag = TRUE;
    memset(&g_stVChipRatingInfo, 0, sizeof(g_stVChipRatingInfo));
    if(fCurVChipBlockStatus)
    {
        fCurVChipBlockStatus = FALSE;
        MApp_VChip_SetBlockStatus(fCurVChipBlockStatus); //unblock
    }
#if ENABLE_UNRATED_LOCK
    else if(stGenSetting.g_VChipSetting.u8UnRatedLock && (stGenSetting.g_VChipSetting.u8VChipLockMode!=0) && (!fCurVChipBlockStatus) && IsVBISrcInUse())
    {
        fCurVChipBlockStatus = TRUE;
        MApp_VChip_SetBlockStatus(fCurVChipBlockStatus);
    }
#endif

    fPreVChipBlockStatus = FALSE;

    //if(IsDigitalSourceInUse())
    {
       //CC_SourceFuns.VbiInit();
    }

    u32MonitorVChipTimer = msAPI_Timer_GetTime0();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static BOOLEAN MApp_VChip_EIA608DataToVChipRatingInfo(MS_VCHIP_RATING_INFO *pstVChipRatingInfo)
{
    BOOLEAN bReturn = TRUE;
    pstVChipRatingInfo->RatingType = 0;
    pstVChipRatingInfo->u8DimVal0 = 0;
    pstVChipRatingInfo->u8DimVal1 = 0;
    pstVChipRatingInfo->u8DimVal2 = 0;
    pstVChipRatingInfo->u8DimVal3 = 0;
    pstVChipRatingInfo->u8DimVal4 = 0;
    pstVChipRatingInfo->u8DimVal5 = 0;
    pstVChipRatingInfo->u8DimVal6 = 0;
    pstVChipRatingInfo->u8DimVal7 = 0;
    pstVChipRatingInfo->u8DimVal8 = 0;
    pstVChipRatingInfo->u8DimVal9 = 0;
    pstVChipRatingInfo->RatingLevel = 0;
    pstVChipRatingInfo->MPAALevel = VCHIP_MPAARATING_NA;
    pstVChipRatingInfo->CanEngLevel = 0;
    pstVChipRatingInfo->CanFreLevel = 0;
    pstVChipRatingInfo->TV_FVSLD = 0;

    // Get RatingType
    if (!(pstVChipRatingInfo->u8EIA608Data1&BIT3))
    {
        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_MPAA;
    }
    else if (!(pstVChipRatingInfo->u8EIA608Data1&BIT4))
    {
        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_TV;
    }
    else if (!(pstVChipRatingInfo->u8EIA608Data1&BIT5))
    {
        if (pstVChipRatingInfo->u8EIA608Data2&BIT3)
            return FALSE;
        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_CANADA_ENG;
    }
    else
    {
        if (pstVChipRatingInfo->u8EIA608Data2&BIT3)
            return FALSE;
        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_CANADA_FRE;
    }

    // Get RatingLevel
    if (pstVChipRatingInfo->RatingType==VCHIP_RATING_TYPE_MPAA)
    {
        pstVChipRatingInfo->MPAALevel = 0;
        if((pstVChipRatingInfo->u8EIA608Data1 & 0x07) == 0x7)
            pstVChipRatingInfo->MPAALevel = VCHIP_MPAARATING_NOT_RATED; // MPAA have 0x7 level
        else
            pstVChipRatingInfo->MPAALevel = 1<<((pstVChipRatingInfo->u8EIA608Data1 & 0x07)%7);

        if ( pstVChipRatingInfo->MPAALevel==VCHIP_MPAARATING_NA )
            bReturn = FALSE;
    }
    else if(pstVChipRatingInfo->RatingType==VCHIP_RATING_TYPE_TV) // English/French
    {
        pstVChipRatingInfo->RatingLevel = (pstVChipRatingInfo->u8EIA608Data2 & 0x07)%7;
        if ( pstVChipRatingInfo->RatingLevel==VCHIP_TVRATING_NONE )
            bReturn = FALSE;
    }
    else if (pstVChipRatingInfo->RatingType==VCHIP_RATING_TYPE_CANADA_ENG) // English
    {
        pstVChipRatingInfo->CanEngLevel = (pstVChipRatingInfo->u8EIA608Data2 & 0x07)%7;
        if ( pstVChipRatingInfo->CanEngLevel==VCHIP_ENGRATING_EXEMPT )
            bReturn = FALSE;
    }
    else if (pstVChipRatingInfo->RatingType==VCHIP_RATING_TYPE_CANADA_FRE) // French
    {
        pstVChipRatingInfo->CanFreLevel = (pstVChipRatingInfo->u8EIA608Data2 & 0x07)%7;
        if ( pstVChipRatingInfo->CanFreLevel==VCHIP_FRERATING_EXEMPT )
            bReturn = FALSE;
    }

    // Get TVRating FVSLD
    if (pstVChipRatingInfo->RatingType==VCHIP_RATING_TYPE_TV)
    {                                                                                    //  b4 3 2 1 0
        pstVChipRatingInfo->TV_FVSLD = (pstVChipRatingInfo->u8EIA608Data1&BIT5) >> 5; //           D
        if(pstVChipRatingInfo->u8EIA608Data2&BIT5)
        {
            if(pstVChipRatingInfo->RatingLevel == VCHIP_TVRATING_TV_Y7)
                pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_FV;                       //  FV
            else //VCHIP_TVRATING_TV_PG, VCHIP_TVRATING_TV_14 and VCHIP_TVRATING_TV_MA
                pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_V;                        //     V
        }
        pstVChipRatingInfo->TV_FVSLD |= (pstVChipRatingInfo->u8EIA608Data2&0x18)>> 2;    //  S L
      #if ENABLE_VCHIP_ALL_AS_AGEBASED
       if ((pstVChipRatingInfo->RatingLevel != VCHIP_TVRATING_NONE)
			&& (!(pstVChipRatingInfo->TV_FVSLD&0x1F)))
			pstVChipRatingInfo->TV_FVSLD |= VCHIP_TVRATING_ALL;                          //  ALL
	#endif
    }
    else
    {
        pstVChipRatingInfo->TV_FVSLD = 0;
    }

    return bReturn;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef NEW_VCHIP
#define NEW_VCHIP_DBINFO(y)    //y
void VCHIPRATINGINFO(MS_VCHIP_RATING_INFO *pstVChipRatingInfo)
{
    U8 iloop;
    for(iloop =0; iloop < sizeof(MS_VCHIP_RATING_INFO);iloop++)
    {
        printf("[%2x]",(U16)(((U8*)pstVChipRatingInfo)[iloop]));
    }
}
#endif

static EN_VCHIP_DATA_STATUS MApp_VChip_GetRating(MS_VCHIP_RATING_INFO *pstVChipRatingInfo)
{
    EN_VCHIP_DATA_STATUS status=VCHIP_DATA_NONE;
#if (ENABLE_ATSC)
#if(ENABLE_ATSC_EPG_DB_2016)
    MS_EPG_EVENT_New stEventInfo;
#else
    MS_EPG_EVENT    stEventInfo;
#endif
#endif

#ifdef NEW_VCHIP
#if (ENABLE_ATSC)
    EN_VCHIP_DATA_STATUS status1 = VCHIP_DATA_NONE;
    MS_VCHIP_RATING_INFO stEITRatingInfo;
#endif
    MS_VCHIP_RATING_INFO st608RatingInfo;
	memset(&st608RatingInfo, 0, sizeof(MS_VCHIP_RATING_INFO));
#else
    MS_VCHIP_RATING_INFO  stCurEventInfo;
#endif

    if ( IsDigitalSourceInUse()
#ifndef DISABLE_COMPONENT_VBI
         || IsYPbPrInUse()
#endif
       )
    { //analog channel

        status = CC_SourceFuns.GetEIA608Data(&(pstVChipRatingInfo->u8EIA608Data1), &(pstVChipRatingInfo->u8EIA608Data2));

        if(status == VCHIP_DATA_CHANGE)
        {
            MApp_VChip_EIA608DataToVChipRatingInfo(pstVChipRatingInfo);
#ifdef NEW_VCHIP
            NEW_VCHIP_DBINFO(printf("\r\nEIA608");VCHIPRATINGINFO(pstVChipRatingInfo);printf("\n");)
#endif
        }
    }
#if (ENABLE_ATSC)
    else
    { //digital channel
        if (MApp_EpgDB_GetCurEvent(&stEventInfo) == TRUE)
        {
#ifdef NEW_VCHIP
            BOOLEAN bResult;
            /*digital 608*/

            status1 = CC_SourceFuns.GetEIA608Data(&(pstVChipRatingInfo->u8EIA608Data1), &(pstVChipRatingInfo->u8EIA608Data2));

            st608RatingInfo.u8EIA608Data1 = pstVChipRatingInfo->u8EIA608Data1;
            st608RatingInfo.u8EIA608Data2 = pstVChipRatingInfo->u8EIA608Data2;
            if(status1 != VCHIP_DATA_NONE)
            {
                bResult = MApp_VChip_EIA608DataToVChipRatingInfo(&st608RatingInfo);
                NEW_VCHIP_DBINFO(printf("\r\nEIA608");VCHIPRATINGINFO(&st608RatingInfo);)
            }
            /*Merge & Check VChipData*/
            if(stEventInfo.stRating.fRatingRxIsOK) // having EIT Table Vchip Rating
            {
                /*EIT Table*/
                MApp_VChip_EPGRating2RatingInfo(&stEventInfo.stRating, &stEITRatingInfo);
                NEW_VCHIP_DBINFO(printf("\r\nEIA708");VCHIPRATINGINFO(&stEITRatingInfo);)

                //if(status1==VCHIP_DATA_NONE) //no 608 data, 708 only
                {
                    U8 u8RatingType = pstVChipRatingInfo->RatingType;
                    // back up the current ratingtype, for block menu show it.
                    // and for EIT rating info, the rating type is no use for comparasion
                    pstVChipRatingInfo->RatingType = stEITRatingInfo.RatingType;
                    if(memcmp(pstVChipRatingInfo,&stEITRatingInfo,sizeof(MS_VCHIP_RATING_INFO))==0)
                    {
                        NEW_VCHIP_DBINFO(putchar('=');putchar('1');)
                        if(u8RatingType != VCHIP_RATING_TYPE_NONE)
                        {
                            pstVChipRatingInfo->RatingType = u8RatingType;
                            return VCHIP_DATA_CHANGE;
                        }
                        return VCHIP_DATA_NO_CHANGE;
                    }
                    else
                    {
                        NEW_VCHIP_DBINFO(printf("RaInfo");VCHIPRATINGINFO(pstVChipRatingInfo);)
                        NEW_VCHIP_DBINFO(putchar('!');putchar('1');)
                        memcpy(pstVChipRatingInfo,&stEITRatingInfo,sizeof(MS_VCHIP_RATING_INFO));
                        return VCHIP_DATA_CHANGE;
                    }
                }
            }
            else // 608 only or have Eit but no EIT rating
            {
                if((fSearchRatingfromPMT) &&(stPMTRatinginfo.fRatingRxIsOK))
                {
                    MApp_VChip_EPGRating2RatingInfo(&stPMTRatinginfo, &stEITRatingInfo);
                    if(
                    stEITRatingInfo.RatingType != pstVChipRatingInfo->RatingType ||
                    stEITRatingInfo.RatingLevel != pstVChipRatingInfo->RatingLevel ||
                    stEITRatingInfo.TV_FVSLD != pstVChipRatingInfo->TV_FVSLD ||
                    stEITRatingInfo.u8DimVal0 != pstVChipRatingInfo->u8DimVal0 ||
                    stEITRatingInfo.u8DimVal1 != pstVChipRatingInfo->u8DimVal1 ||
                    stEITRatingInfo.u8DimVal2 != pstVChipRatingInfo->u8DimVal2 ||
                    stEITRatingInfo.u8DimVal3 != pstVChipRatingInfo->u8DimVal3 ||
                    stEITRatingInfo.u8DimVal4 != pstVChipRatingInfo->u8DimVal4 ||
                    stEITRatingInfo.u8DimVal5 != pstVChipRatingInfo->u8DimVal5 ||
                    stEITRatingInfo.u8DimVal6 != pstVChipRatingInfo->u8DimVal6 ||
                    stEITRatingInfo.u8DimVal7 != pstVChipRatingInfo->u8DimVal7 ||
                    stEITRatingInfo.u8DimVal8 != pstVChipRatingInfo->u8DimVal8 ||
                    stEITRatingInfo.u8DimVal9 != pstVChipRatingInfo->u8DimVal9 ||
                    stEITRatingInfo.MPAALevel != pstVChipRatingInfo->MPAALevel ||
                    stEITRatingInfo.CanEngLevel != pstVChipRatingInfo->CanEngLevel ||
                    stEITRatingInfo.CanFreLevel != pstVChipRatingInfo->CanFreLevel )
                    {
                        pstVChipRatingInfo->RatingType = stEITRatingInfo.RatingType;
                        pstVChipRatingInfo->u8DimVal0  = stEITRatingInfo.u8DimVal0;
                        pstVChipRatingInfo->u8DimVal1  = stEITRatingInfo.u8DimVal1;
                        pstVChipRatingInfo->u8DimVal2  = stEITRatingInfo.u8DimVal2;
                        pstVChipRatingInfo->u8DimVal3  = stEITRatingInfo.u8DimVal3;
                        pstVChipRatingInfo->u8DimVal4  = stEITRatingInfo.u8DimVal4;
                        pstVChipRatingInfo->u8DimVal5  = stEITRatingInfo.u8DimVal5;
                        pstVChipRatingInfo->u8DimVal6  = stEITRatingInfo.u8DimVal6;
                        pstVChipRatingInfo->u8DimVal7  = stEITRatingInfo.u8DimVal7;
                        pstVChipRatingInfo->u8DimVal8  = stEITRatingInfo.u8DimVal8;
                        pstVChipRatingInfo->u8DimVal9  = stEITRatingInfo.u8DimVal9;
                        pstVChipRatingInfo->RatingLevel= stEITRatingInfo.RatingLevel;
                        pstVChipRatingInfo->MPAALevel  = stEITRatingInfo.MPAALevel;
                        pstVChipRatingInfo->CanEngLevel= stEITRatingInfo.CanEngLevel;
                        pstVChipRatingInfo->CanFreLevel= stEITRatingInfo.CanFreLevel;
                        pstVChipRatingInfo->TV_FVSLD   = stEITRatingInfo.TV_FVSLD;
                        return VCHIP_DATA_CHANGE;
                    }
                    else
                    {
                        return VCHIP_DATA_NO_CHANGE;
                    }
                }
                else
                {
                    if(status1 == VCHIP_DATA_NONE)
                    {
                        NEW_VCHIP_DBINFO(putchar('=');putchar('0');)
                        return VCHIP_DATA_NONE;
                    }
                    else
                    {
                        if(memcmp(pstVChipRatingInfo, &st608RatingInfo, sizeof(MS_VCHIP_RATING_INFO))==0)
                        {
                            NEW_VCHIP_DBINFO(putchar('=');putchar('3');)
                            return VCHIP_DATA_NO_CHANGE;
                        }
                        else
                        {
                            NEW_VCHIP_DBINFO(printf("RaInfo");VCHIPRATINGINFO(pstVChipRatingInfo);)
                            memcpy(pstVChipRatingInfo, &st608RatingInfo, sizeof(MS_VCHIP_RATING_INFO));
                            NEW_VCHIP_DBINFO(putchar('!');putchar('3');)
                            return VCHIP_DATA_CHANGE;
                        }
                    }
                }
            }

            #else
            {
                /* digital 608 */

                status = CC_SourceFuns.GetEIA608Data(&(pstVChipRatingInfo->u8EIA608Data1), &(pstVChipRatingInfo->u8EIA608Data2));
                if(status == VCHIP_DATA_CHANGE)
                {
                    BOOLEAN bResult;
                    U8 u8PreRatingType = pstVChipRatingInfo->RatingType;
                    bResult = MApp_VChip_EIA608DataToVChipRatingInfo(pstVChipRatingInfo);

                    if ( stEventInfo.stRating.fRatingRxIsOK && MApp_VChip_GetCurVChipBlockStatus() ) // is locked by 708 now....
                    {
                        if ( (u8PreRatingType!=pstVChipRatingInfo->RatingType)&&(!bResult) ) // the incoming new 608 rating is null.....
                            return VCHIP_DATA_NO_CHANGE;
                    }
                    return VCHIP_DATA_CHANGE;
                }
                else if ( (status == VCHIP_DATA_NO_CHANGE) && (!stEventInfo.stRating.fRatingRxIsOK) )
                {
                    return status;
                }

            }

            // rating from EIT....
            MApp_VChip_EPGRating2RatingInfo(&stEventInfo.stRating, &stCurEventInfo);
            if(
                stCurEventInfo.RatingType != pstVChipRatingInfo->RatingType ||
                stCurEventInfo.RatingLevel != pstVChipRatingInfo->RatingLevel ||
                stCurEventInfo.TV_FVSLD != pstVChipRatingInfo->TV_FVSLD ||
                stCurEventInfo.u8DimVal0 != pstVChipRatingInfo->u8DimVal0 ||
                stCurEventInfo.u8DimVal1 != pstVChipRatingInfo->u8DimVal1 ||
                stCurEventInfo.u8DimVal2 != pstVChipRatingInfo->u8DimVal2 ||
                stCurEventInfo.u8DimVal3 != pstVChipRatingInfo->u8DimVal3 ||
                stCurEventInfo.u8DimVal4 != pstVChipRatingInfo->u8DimVal4 ||
                stCurEventInfo.u8DimVal5 != pstVChipRatingInfo->u8DimVal5 ||
                stCurEventInfo.u8DimVal6 != pstVChipRatingInfo->u8DimVal6 ||
                stCurEventInfo.u8DimVal7 != pstVChipRatingInfo->u8DimVal7 ||
                stCurEventInfo.u8DimVal8 != pstVChipRatingInfo->u8DimVal8 ||
                stCurEventInfo.u8DimVal9 != pstVChipRatingInfo->u8DimVal9 ||
                stCurEventInfo.MPAALevel != pstVChipRatingInfo->MPAALevel ||
                stCurEventInfo.CanEngLevel != pstVChipRatingInfo->CanEngLevel ||
                stCurEventInfo.CanFreLevel != pstVChipRatingInfo->CanFreLevel )
            {
                pstVChipRatingInfo->RatingType = stCurEventInfo.RatingType;
                pstVChipRatingInfo->u8DimVal0 = stCurEventInfo.u8DimVal0;
                pstVChipRatingInfo->u8DimVal1 = stCurEventInfo.u8DimVal1;
                pstVChipRatingInfo->u8DimVal2 = stCurEventInfo.u8DimVal2;
                pstVChipRatingInfo->u8DimVal3 = stCurEventInfo.u8DimVal3;
                pstVChipRatingInfo->u8DimVal4 = stCurEventInfo.u8DimVal4;
                pstVChipRatingInfo->u8DimVal5 = stCurEventInfo.u8DimVal5;
                pstVChipRatingInfo->u8DimVal6 = stCurEventInfo.u8DimVal6;
                pstVChipRatingInfo->u8DimVal7 = stCurEventInfo.u8DimVal7;
                pstVChipRatingInfo->u8DimVal8 = stCurEventInfo.u8DimVal8;
                pstVChipRatingInfo->u8DimVal9 = stCurEventInfo.u8DimVal9;
                pstVChipRatingInfo->RatingLevel = stCurEventInfo.RatingLevel;
                pstVChipRatingInfo->MPAALevel = stCurEventInfo.MPAALevel;
                pstVChipRatingInfo->CanEngLevel = stCurEventInfo.CanEngLevel;
                pstVChipRatingInfo->CanFreLevel = stCurEventInfo.CanFreLevel;
                pstVChipRatingInfo->TV_FVSLD = stCurEventInfo.TV_FVSLD;
                status = VCHIP_DATA_CHANGE;
            }
            else
            {
                status = VCHIP_DATA_NO_CHANGE;
            }
            #endif
        }
        else
        {
	    //Rating in PMT
            if(fSearchRatingfromPMT)
            {
                //20120515Max Seperate pmt eit rating storage location
                /*Merge & Check VChipData*/
                if(stPMTRatinginfo.fRatingRxIsOK)
                {
                    MApp_VChip_EPGRating2RatingInfo(&stPMTRatinginfo, &stEITRatingInfo);

                    if(
                    stEITRatingInfo.RatingType != pstVChipRatingInfo->RatingType ||
                    stEITRatingInfo.RatingLevel != pstVChipRatingInfo->RatingLevel ||
                    stEITRatingInfo.TV_FVSLD != pstVChipRatingInfo->TV_FVSLD ||
                    stEITRatingInfo.u8DimVal0 != pstVChipRatingInfo->u8DimVal0 ||
                    stEITRatingInfo.u8DimVal1 != pstVChipRatingInfo->u8DimVal1 ||
                    stEITRatingInfo.u8DimVal2 != pstVChipRatingInfo->u8DimVal2 ||
                    stEITRatingInfo.u8DimVal3 != pstVChipRatingInfo->u8DimVal3 ||
                    stEITRatingInfo.u8DimVal4 != pstVChipRatingInfo->u8DimVal4 ||
                    stEITRatingInfo.u8DimVal5 != pstVChipRatingInfo->u8DimVal5 ||
                    stEITRatingInfo.u8DimVal6 != pstVChipRatingInfo->u8DimVal6 ||
                    stEITRatingInfo.u8DimVal7 != pstVChipRatingInfo->u8DimVal7 ||
                    stEITRatingInfo.u8DimVal8 != pstVChipRatingInfo->u8DimVal8 ||
                    stEITRatingInfo.u8DimVal9 != pstVChipRatingInfo->u8DimVal9 ||
                    stEITRatingInfo.MPAALevel != pstVChipRatingInfo->MPAALevel ||
                    stEITRatingInfo.CanEngLevel != pstVChipRatingInfo->CanEngLevel ||
                    stEITRatingInfo.CanFreLevel != pstVChipRatingInfo->CanFreLevel )
                    {
                        pstVChipRatingInfo->RatingType = stEITRatingInfo.RatingType;
                        pstVChipRatingInfo->u8DimVal0  = stEITRatingInfo.u8DimVal0;
                        pstVChipRatingInfo->u8DimVal1  = stEITRatingInfo.u8DimVal1;
                        pstVChipRatingInfo->u8DimVal2  = stEITRatingInfo.u8DimVal2;
                        pstVChipRatingInfo->u8DimVal3  = stEITRatingInfo.u8DimVal3;
                        pstVChipRatingInfo->u8DimVal4  = stEITRatingInfo.u8DimVal4;
                        pstVChipRatingInfo->u8DimVal5  = stEITRatingInfo.u8DimVal5;
                        pstVChipRatingInfo->u8DimVal6  = stEITRatingInfo.u8DimVal6;
                        pstVChipRatingInfo->u8DimVal7  = stEITRatingInfo.u8DimVal7;
                        pstVChipRatingInfo->u8DimVal8  = stEITRatingInfo.u8DimVal8;
                        pstVChipRatingInfo->u8DimVal9  = stEITRatingInfo.u8DimVal9;
                        pstVChipRatingInfo->RatingLevel= stEITRatingInfo.RatingLevel;
                        pstVChipRatingInfo->MPAALevel  = stEITRatingInfo.MPAALevel;
                        pstVChipRatingInfo->CanEngLevel= stEITRatingInfo.CanEngLevel;
                        pstVChipRatingInfo->CanFreLevel= stEITRatingInfo.CanFreLevel;
                        pstVChipRatingInfo->TV_FVSLD   = stEITRatingInfo.TV_FVSLD;
                        status = VCHIP_DATA_CHANGE;
                    }
                    else
                    {
                        status = VCHIP_DATA_NO_CHANGE;
                    }
                    return status;
                }
            }
            else
            {
                /* digital 608 */

                status = CC_SourceFuns.GetEIA608Data(&(pstVChipRatingInfo->u8EIA608Data1), &(pstVChipRatingInfo->u8EIA608Data2));
                //printf("\r\n CC_SourceFuns.GetEIA608Data = %d",status);
                if(status == VCHIP_DATA_CHANGE)
                    MApp_VChip_EIA608DataToVChipRatingInfo(pstVChipRatingInfo);
                //status = VCHIP_DATA_NONE;

            }
        }
    }
#endif
    return status;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if 0 //ATSC_FIX_C
static U8 MApp_VChip_RatingType2LockMode(U8 u8RatingType)
{
    switch (u8RatingType)
    {
        case VCHIP_RATING_TYPE_CANADA_ENG:
        case VCHIP_RATING_TYPE_CANADA_FRE:
            return VCHIP_RATING_REGION_CANADA;
        case VCHIP_RATING_TYPE_TV:
        case VCHIP_RATING_TYPE_MPAA:
            return VCHIP_RATING_REGION_US;
        case VCHIP_RATING_TYPE_REG5:
            return VCHIP_RATING_REGION_REG5;
        default:
            return VCHIP_RATING_REGION_NONE;
    }
    return VCHIP_RATING_REGION_NONE;
}
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
#define DBG_RRT5(msg) //msg
static BOOLEAN MApp_VChip_CompareRRT5Rating(MS_VCHIP_RATING_INFO *pstVChipRatingInfo)
{
    BOOLEAN bBlockStatus = FALSE;

// 0 based
#define ShouldLockDim(n)  ((stGenSettingVchipRegion5.stRegin5Dimension[n].u32CurrentOption) & (pstVChipRatingInfo->u8DimVal ## n))
#define ValuesDefined(n)    (1 << stGenSettingVchipRegion5.stRegin5Dimension[n].u8Values_Defined)

    // VCHIP_RATING_TYPE_REG5:
    if (ShouldLockDim(0) && (pstVChipRatingInfo->u8DimVal0 < ValuesDefined(0)))
    {
        DBG_RRT5(printf("\nlock dim 0 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[0].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal0
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(1) && (pstVChipRatingInfo->u8DimVal1 < ValuesDefined(1)))
    {
        DBG_RRT5(printf("\nlock dim 1 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[1].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal1
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(2) && (pstVChipRatingInfo->u8DimVal2 < ValuesDefined(2)))
    {
        DBG_RRT5(printf("\nlock dim 2 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[2].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal2
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(3) && (pstVChipRatingInfo->u8DimVal3 < ValuesDefined(3)))
    {
        DBG_RRT5(printf("\nlock dim 3 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[3].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal3
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(4) && (pstVChipRatingInfo->u8DimVal4 < ValuesDefined(4)))
    {
        DBG_RRT5(printf("\nlock dim 4 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[4].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal4
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(5) && (pstVChipRatingInfo->u8DimVal5 < ValuesDefined(5)))
    {
        DBG_RRT5(printf("\nlock dim 5 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[5].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal5
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(6) && (pstVChipRatingInfo->u8DimVal6 < ValuesDefined(6)))
    {
        DBG_RRT5(printf("\nlock dim 6 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[6].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal6
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(7) && (pstVChipRatingInfo->u8DimVal7 < ValuesDefined(7)))
    {
        DBG_RRT5(printf("\nlock dim 7 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[7].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal7
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(8) && (pstVChipRatingInfo->u8DimVal8 < ValuesDefined(8)))
    {
        DBG_RRT5(printf("\nlock dim 8 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[8].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal8
            ));
        bBlockStatus = TRUE;
    }

    if (ShouldLockDim(9) && (pstVChipRatingInfo->u8DimVal9 < ValuesDefined(9)))
    {
        DBG_RRT5(printf("\nlock dim 9 (%x, %x)",
            (U16)stGenSettingVchipRegion5.stRegin5Dimension[9].u32CurrentOption,
            (U16)pstVChipRatingInfo->u8DimVal9
            ));
        bBlockStatus = TRUE;
    }

    return bBlockStatus;

    #undef ShouldLockDim
    #undef ValuesDefined
}
#endif

BOOLEAN MApp_VChip_CompareRating(MS_VCHIP_RATING_INFO *pstVChipRatingInfo, MS_VCHIP_SETTING *pstVChipSetting)
{
    BOOLEAN bBlockStatus;

    VCHIP_DBINFO(printf("\npstVChipSetting->u8VChipLockMode %bu\n", (U8)(pstVChipSetting->u8VChipLockMode)));
    VCHIP_DBINFO(printf("pstVChipRatingInfo->RatingType %bu\n\n", (U8)pstVChipRatingInfo->RatingType));

    bBlockStatus = FALSE;

    if((pstVChipSetting->u8VChipLockMode) && (!fVChipPassWordEntered))
    {
            	//VCHIP_RATING_TYPE_TV:
            #if ENABLE_VCHIP_ALL_AS_AGEBASED
		  switch(pstVChipRatingInfo->RatingLevel)
                {
                    case VCHIP_TVRATING_TV_Y:
                        if(pstVChipSetting->stVChipTVItem.Item_TV_Y & pstVChipRatingInfo->TV_FVSLD)
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_Y7:
                        if(pstVChipSetting->stVChipTVItem.Item_TV_Y7 & pstVChipRatingInfo->TV_FVSLD)
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_G:
                        if(pstVChipSetting->stVChipTVItem.Item_TV_G & pstVChipRatingInfo->TV_FVSLD)
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_PG:
                        if(pstVChipSetting->stVChipTVItem.Item_TV_PG & pstVChipRatingInfo->TV_FVSLD)
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_14:
                        if(pstVChipSetting->stVChipTVItem.Item_TV_14 & pstVChipRatingInfo->TV_FVSLD)
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_MA:
                        if(pstVChipSetting->stVChipTVItem.Item_TV_MA & pstVChipRatingInfo->TV_FVSLD)
                            bBlockStatus = TRUE;
                        break;
                }
		#else
                switch(pstVChipRatingInfo->RatingLevel)
                {
                    case VCHIP_TVRATING_NONE:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_NONE & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_NONE & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_Y:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_Y & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_Y & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_Y7:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_Y7 & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_Y7 & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_G:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_G & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_G & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_PG:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_PG & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_PG & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_14:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_14 & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_14 & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                    case VCHIP_TVRATING_TV_MA:
                        if((pstVChipSetting->stVChipTVItem.Item_TV_MA & VCHIP_TVRATING_ALL) ||
                           (pstVChipSetting->stVChipTVItem.Item_TV_MA & pstVChipRatingInfo->TV_FVSLD))
                            bBlockStatus = TRUE;
                        break;
                }
			#endif
                if (bBlockStatus == TRUE)
                    pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_TV;

            // VCHIP_RATING_TYPE_MPAA:
                if((pstVChipRatingInfo->MPAALevel > VCHIP_MPAARATING_NA /*&& pstVChipRatingInfo->MPAALevel < VCHIP_MPAARATING_NOT_RATED*/))
                {
                    if((pstVChipRatingInfo->MPAALevel & pstVChipSetting->u8VChipMPAAItem) & EXCELUDE_MPAA_NA)
                    {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_MPAA;
                    }
                }

            // VCHIP_RATING_TYPE_CANADA_ENG:
                if(pstVChipRatingInfo->CanEngLevel > VCHIP_ENGRATING_EXEMPT &&
                   pstVChipRatingInfo->CanEngLevel <= VCHIP_ENGRATING_MAX_LEVEL)
                {
                    if (pstVChipSetting->u8VChipCEItem &&
                        pstVChipRatingInfo->CanEngLevel >= pstVChipSetting->u8VChipCEItem)
                    {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_CANADA_ENG;
                    }
                }

            // VCHIP_RATING_TYPE_CANADA_FRE:
                if(pstVChipRatingInfo->CanFreLevel > VCHIP_FRERATING_EXEMPT &&
                   pstVChipRatingInfo->CanFreLevel <= VCHIP_FRERATING_MAX_LEVEL)
                {
                    if (pstVChipSetting->u8VChipCFItem &&
                        pstVChipRatingInfo->CanFreLevel >= pstVChipSetting->u8VChipCFItem)
                    {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_CANADA_FRE;
                    }
                }
            // VCHIP_RATING_TYPE_REG5:
#if (ENABLE_ATSC)
#if defined(ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD) && ENABLE_PARSE_SAME_DIMENSION_IN_RRT5_CAD
            if (MApp_VChip_CompareRRT5Rating(pstVChipRatingInfo))
            {
                bBlockStatus = TRUE;
                pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
            }
#else
            if( (pstVChipRatingInfo->u8DimVal0 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[0].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal0-1)&0x01) )
             {
                    bBlockStatus = TRUE;
                    pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
            }

            if( (pstVChipRatingInfo->u8DimVal1 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[1].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal1-1)&0x01) )
            {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
            }

            if( (pstVChipRatingInfo->u8DimVal2 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[2].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal2-1)&0x01) )
             {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
             }

            if( (pstVChipRatingInfo->u8DimVal3 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[3].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal3-1)&0x01) )
            {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
            }

            if( (pstVChipRatingInfo->u8DimVal4 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[4].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal4-1)&0x01) )
             {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
            }

            if( (pstVChipRatingInfo->u8DimVal5 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[5].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal5-1)&0x01) )
             {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
             }

            if( (pstVChipRatingInfo->u8DimVal6 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[6].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal6-1)&0x01) )
            {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
            }

            if( (pstVChipRatingInfo->u8DimVal7 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[7].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal7-1)&0x01) )
             {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
             }

            if( (pstVChipRatingInfo->u8DimVal8 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[8].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal8-1)&0x01) )
             {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
             }

            if( (pstVChipRatingInfo->u8DimVal9 != 0) &&
                 ((stGenSettingVchipRegion5.stRegin5Dimension[9].u32CurrentOption)>>(pstVChipRatingInfo->u8DimVal9-1)&0x01) )
             {
                        bBlockStatus = TRUE;
                        pstVChipRatingInfo->RatingType = VCHIP_RATING_TYPE_REG5;
             }
#endif
#endif
}
#if ENABLE_UNRATED_LOCK
    if (pstVChipRatingInfo->RatingType == VCHIP_RATING_TYPE_NONE)
    {
        if (stGenSetting.g_VChipSetting.u8UnRatedLock && IsVBISrcInUse() &&
                (stGenSetting.g_VChipSetting.u8VChipLockMode) && (!fVChipPassWordEntered))
        {
            bBlockStatus = TRUE;
        }
        else
            bBlockStatus = FALSE;
    }
#endif
    return bBlockStatus;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MApp_VChip_SetBlockStatus(BOOLEAN bVChipBlockStatus)
{
#if (ENABLE_ATSC)
#if 1//def LOCK_USE_BLACK_VIDEO
    MApp_MuteAvByLock(E_SCREEN_MUTE_BY_VCHIP, bVChipBlockStatus);
#else
    MApp_MuteAvByLock(bVChipBlockStatus);
#endif
#else
    MApp_EnableBlockProgramme(bVChipBlockStatus);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MApp_VChip_MonitorVChip(void)
{
    if(u32MonitorVChipFlag || msAPI_Timer_DiffTimeFromNow(u32MonitorVChipTimer) > VCHIP_MONITOR_PERIOD)
    {
        u32MonitorVChipFlag = FALSE;
        switch( MApp_VChip_GetRating(&g_stVChipRatingInfo) )
        {
            case VCHIP_DATA_NO_CHANGE:
                VCHIP_DBINFO(printf("\nVCHIP_DATA_NO_CHANGE!\r\n"));

                // to avoid a flash black screen after unlock (if taking mixed rating signal). caused by re-Enable AV.
                if (fVChipPassWordEntered)
                {
                    fCurVChipBlockStatus = FALSE;
                }
                g_ucVChipNoRatingCounter = 0;

                //when state change from nono to no change, update current block status
                #if ENABLE_UNRATED_LOCK
                if ( (fCurVChipBlockStatus == FALSE)&& (!fVChipPassWordEntered))
		        #else
                if ((g_stVChipRatingInfo.RatingType != VCHIP_RATING_TYPE_NONE) && (fCurVChipBlockStatus == FALSE)
                    && (!fVChipPassWordEntered))
                #endif
                {
                    fCurVChipBlockStatus = MApp_VChip_CompareRating(&g_stVChipRatingInfo, &stGenSetting.g_VChipSetting);
                }
                break;
            case VCHIP_DATA_CHANGE:
                VCHIP_DBINFO(printf("\nVCHIP_DATA_CHANGE!\r\n"));

                fRatingUpdateStatus = TRUE;
                g_ucVChipNoRatingCounter = 0;
                fCurVChipBlockStatus = MApp_VChip_CompareRating(&g_stVChipRatingInfo, &stGenSetting.g_VChipSetting);
                break;
            case VCHIP_DATA_NONE:
                VCHIP_DBINFO(printf("\nVCHIP_DATA_NONE!\r\n"));
                if( g_ucVChipNoRatingCounter < VCHIP_NONE_CHECK_COUNT )
                {
                    ++ g_ucVChipNoRatingCounter;
                }
                if( g_ucVChipNoRatingCounter == VCHIP_NONE_CHECK_COUNT )
                {
                    g_stVChipRatingInfo.RatingType = VCHIP_RATING_TYPE_NONE;
                    fCurVChipBlockStatus = FALSE;
                    #if ENABLE_UNRATED_LOCK
                    if (stGenSetting.g_VChipSetting.u8UnRatedLock && IsVBISrcInUse() &&
                        (stGenSetting.g_VChipSetting.u8VChipLockMode) && (!fVChipPassWordEntered))
                    {
                        fCurVChipBlockStatus = TRUE;
                    }
                    else
                    {
                        fCurVChipBlockStatus = FALSE;
                    }
                    #endif
                }

                break;
        }

        if(fCurVChipBlockStatus != fPreVChipBlockStatus)
        {
#if 0//(DTV_608_VCHIP_DEBUG == 1)
            printf("\n vc sw, %bd, %bd", (U8)fCurVChipBlockStatus, (U8)fPreVChipBlockStatus);
#endif
            MApp_VChip_SetBlockStatus((BOOLEAN)fCurVChipBlockStatus);
            fPreVChipBlockStatus = fCurVChipBlockStatus;
        }

        u32MonitorVChipTimer = msAPI_Timer_GetTime0();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_VChip_GetCurVChipBlockStatus(void)
{
    return (fCurVChipBlockStatus && (!fVChipPassWordEntered));
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOLEAN MApp_VChip_GetRatingUpdateStatus(void)
{
    BOOLEAN bUpdate = fRatingUpdateStatus;

    fRatingUpdateStatus = FALSE;

    return (fCurVChipBlockStatus && bUpdate);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

U8* VChipTVPGMenuItemName_Text(void)//EN_STRING_CANADACE_TEXT
{
    U16 u16TempStringID;

    switch(g_stVChipRatingInfo.RatingLevel)
    {
        case VCHIP_TVRATING_NONE://MSG_VCHIP_TV_NONE,
            u16TempStringID = en_str_TVdashNone;
            break;

        case VCHIP_TVRATING_TV_Y://MSG_VCHIP_TV_Y,
            u16TempStringID = en_str_TVdashY;
            break;

        case VCHIP_TVRATING_TV_Y7://MSG_VCHIP_TV_Y7,
            u16TempStringID = en_str_TVdashY7;
            break;

        case VCHIP_TVRATING_TV_G://MSG_VCHIP_TV_G,
            u16TempStringID = en_str_TVdashG;
            break;

        case VCHIP_TVRATING_TV_PG://MSG_VCHIP_TV_PG,
            u16TempStringID = en_str_TVdashPG;
            break;

        case VCHIP_TVRATING_TV_14://MSG_VCHIP_TV_14,
            u16TempStringID = en_str_TVdash14;
            break;

        case VCHIP_TVRATING_TV_MA://MSG_VCHIP_TV_MA,
            u16TempStringID = en_str_TVdashMA;
            break;

        default:
           u16TempStringID = Empty;
            break;
    }

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    return  (U8*)CHAR_BUFFER;
}

U8* VChipMPAAOptionName_Text(U8 BitSelect)
{
    U16 u16TempStringID;

    switch(g_stVChipRatingInfo.MPAALevel & BitSelect)
    {
        case VCHIP_MPAARATING_G:
            u16TempStringID = en_str_G;
            break;

        case VCHIP_MPAARATING_PG:
            u16TempStringID = en_str_PG;
            break;

        case VCHIP_MPAARATING_PG_13:
            u16TempStringID = en_str_PGdash13;
            break;

        case VCHIP_MPAARATING_R:
            u16TempStringID = en_str_R;
            break;

        case VCHIP_MPAARATING_NC_17:
            u16TempStringID = en_str_NCdash17;
            break;

        case VCHIP_MPAARATING_X:
            u16TempStringID = en_str_X;
            break;

        case VCHIP_MPAARATING_NOT_RATED:
            u16TempStringID = en_str_NshashR;
            break;

        default:
            snprintf((char*)CHAR_BUFFER, 3, "NA");
            return  (U8*)CHAR_BUFFER;
    }

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    //printf("CHAR_BUFFER = %s\n"), CHAR_BUFFER;
    return  (U8*)CHAR_BUFFER;
}

U8* VChipCanadaEnglishOptionName_Text(void)
{
    U16 u16TempStringID;

    switch(g_stVChipRatingInfo.CanEngLevel)
    {
        case VCHIP_ENGRATING_EXEMPT:
            u16TempStringID = en_str_E;
            break;

        case VCHIP_ENGRATING_C:
            u16TempStringID = en_str_C;
            break;

        case VCHIP_ENGRATING_C8Plus:
            u16TempStringID = en_str_C8plus;
            break;

        case VCHIP_ENGRATING_G:
            u16TempStringID = en_str_G;
            break;

        case VCHIP_ENGRATING_PG:
            u16TempStringID = en_str_PG;
            break;

        case VCHIP_ENGRATING_14Plus:
            u16TempStringID = en_str_14plus;
            break;

        case VCHIP_ENGRATING_18Plus:
            u16TempStringID = en_str_18plus;
            break;

        default:
            u16TempStringID = en_str_E;
            break;
    }

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    return  (U8*)CHAR_BUFFER;
}

U8* enVChipCanadaFrenchOptionName_Text(void)//EN_STRING_CANADACF_MODE_SELECT_TEXT_WHITE,
{
    U16 u16TempStringID;

    switch(g_stVChipRatingInfo.CanFreLevel)
    {
        case VCHIP_FRERATING_EXEMPT:
            u16TempStringID = en_str_E;
            break;

        case VCHIP_FRERATING_G:
            u16TempStringID = en_str_G;
            break;

        case VCHIP_FRERATING_8ansPlus:
            u16TempStringID = en_str_8ansplus;
            break;

        case VCHIP_FRERATING_13ansPlus:
           u16TempStringID = en_str_13ansplus;
            break;

        case VCHIP_FRERATING_16ansPlus:
            u16TempStringID = en_str_16ansplus;
            break;

        case VCHIP_FRERATING_18ansPlus:
            u16TempStringID = en_str_18ansplus;
            break;

        default:
            u16TempStringID = en_str_E;
            break;
    }

    MApp_U16StringToU8String(MApp_ZUI_API_GetString(u16TempStringID),(U8*)CHAR_BUFFER,MApp_UiMenu_u16Strlen(MApp_ZUI_API_GetString(u16TempStringID)));
    return  (U8*)CHAR_BUFFER;
}


static U8 UiMenuStr_GetTVRatingString(U8 *pu8Str)
{
    U8 u8Strlen;

#if 0
    strcpy((S8 *)pu8Str, (S8 *)VChipTVPGMenuItemName_Text());
    u8Strlen = strlen((S8 *)VChipTVPGMenuItemName_Text());
#else
    strncpy((char *)pu8Str, (char *)VChipTVPGMenuItemName_Text(), strlen((char *)VChipTVPGMenuItemName_Text()));
    u8Strlen = strlen((char *)VChipTVPGMenuItemName_Text());
#endif


    pu8Str += u8Strlen;

    switch(g_stVChipRatingInfo.RatingLevel)
    {
        case VCHIP_TVRATING_TV_Y7:
            if(g_stVChipRatingInfo.TV_FVSLD & VCHIP_TVRATING_FV)
            {
                strcat((char *)pu8Str, "-FV"); //strcpy((char *)pu8Str, "-FV");
                //strncpy((char *)pu8Str, "-FV", strlen((char *)pu8Str)+1); //strcpy((char *)pu8Str, "-FV");
                u8Strlen += (strlen("-FV"));
            }
            break;
        case VCHIP_TVRATING_TV_PG:
        case VCHIP_TVRATING_TV_14:
            if(g_stVChipRatingInfo.TV_FVSLD & VCHIP_TVRATING_D)
            {
                strcat((char *)pu8Str, "-D"); //strcpy((char *)pu8Str, "-D");
                //strncpy((char *)pu8Str, "-D", strlen((char *)pu8Str)+1); //strcpy((char *)pu8Str, "-D");
                u8Strlen += (strlen("-D"));
            }
            // do not break here
        case VCHIP_TVRATING_TV_MA:
            if(g_stVChipRatingInfo.TV_FVSLD & VCHIP_TVRATING_L)
            {
                strcat((char *)pu8Str, "-L");//strcpy((S8 *)pu8Str, "-L");
                //strncpy((char *)pu8Str, "-L", strlen((char *)pu8Str)+1);//strcpy((S8 *)pu8Str, "-L");
                u8Strlen += (strlen("-L"));
            }
            if(g_stVChipRatingInfo.TV_FVSLD & VCHIP_TVRATING_S)
            {
                strcat((char *)pu8Str,"-S");//strcpy((S8 *)pu8Str,"-S");
                //strncpy((char *)pu8Str,"-S", strlen((char *)pu8Str)+1);//strcpy((S8 *)pu8Str,"-S");
                u8Strlen += (strlen("-S"));
            }
            if(g_stVChipRatingInfo.TV_FVSLD & VCHIP_TVRATING_V)
            {
                strcat((char *)pu8Str, "-V");//strcpy((S8 *)pu8Str, "-V");
                //strncpy((char *)pu8Str, "-V", strlen((char *)pu8Str)+1);//strcpy((S8 *)pu8Str, "-V");
                u8Strlen += (strlen("-V"));
            }
            break;
    }

    return u8Strlen;
}

U8 UiMenuStr_GetVChip1RatingString(U8* pu8Str)
{
    U8 u8Strlen;

    if (!pu8Str)
    {
        return 0;
    }

    pu8Str[0] = 0;
    u8Strlen = 0;

    //20121023 Max modify the "and" to " or" because the pure 608 TV rating will not display the rating on ui
#if ENABLE_ATSC_VCHIP
    #if ENABLE_ATSC_EPG_DB_2016
    MS_EPG_EVENT_New* pstCurEvent = MApp_EpgDB_Get_CurEvent_Ref();

    if (!(g_stVChipRatingInfo.u8EIA608Data1&BIT4) ||(pstCurEvent->stRating.u8TVRatingForEntire != INVALID_TV_RATING_FOR_ENTIRE))
    #else
    if (!(g_stVChipRatingInfo.u8EIA608Data1&BIT4) ||(g_stUiEvent.stRating.u8TVRatingForEntire != INVALID_TV_RATING_FOR_ENTIRE))
    #endif
#else
    if (!(g_stVChipRatingInfo.u8EIA608Data1&BIT4))
#endif
    {
        //if (u8Strlen)
        //{
        //    strcat((char *)pu8Str, " / ");
        //}
        u8Strlen += UiMenuStr_GetTVRatingString(pu8Str);
    }

    if (g_stVChipRatingInfo.MPAALevel > VCHIP_MPAARATING_NA )
    {
        U8 item,itemBit;
        for(item = 1; item <8 ; item++)
        {
            itemBit = 1<< item;
            if(g_stVChipRatingInfo.MPAALevel & itemBit)
            {
                if(u8Strlen != 0)
                {
                    strcat((char *)pu8Str, "/");
                    strcat((char *)pu8Str, "MPAA-");
                    u8Strlen += (strlen("/MPAA-"));
                }
                else
                {
                    strcat((char *)pu8Str, "MPAA-");
                    u8Strlen += (strlen("MPAA-"));
                }
                strcat((char *)pu8Str, (char *)VChipMPAAOptionName_Text(itemBit));
                u8Strlen += strlen((char *)VChipMPAAOptionName_Text(itemBit));
            }
        }
    }

    if (g_stVChipRatingInfo.CanEngLevel > VCHIP_ENGRATING_EXEMPT && g_stVChipRatingInfo.CanEngLevel <= VCHIP_ENGRATING_MAX_LEVEL)
    {
        if (u8Strlen)
        {
            strcat((char  *)pu8Str, " / ");
            u8Strlen = u8Strlen+3;
        }
        //strcat((S8 *)pu8Str, (S8 *)VChipCanadaEnglishOptionName_Text());
        //u8Strlen += strlen((S8 *)VChipCanadaEnglishOptionName_Text());
        strcat((char *)pu8Str, (char *)VChipCanadaEnglishOptionName_Text());
        u8Strlen += strlen((char *)VChipCanadaEnglishOptionName_Text());
    }

    if (g_stVChipRatingInfo.CanFreLevel > VCHIP_FRERATING_EXEMPT && g_stVChipRatingInfo.CanFreLevel <= VCHIP_FRERATING_MAX_LEVEL)
    {
        if (u8Strlen)
        {
            strcat((char  *)pu8Str, " / ");
            u8Strlen = u8Strlen+3;
        }
        //strcat((S8 *)pu8Str, (S8 *)enVChipCanadaFrenchOptionName_Text());
        //u8Strlen += strlen((S8 *)enVChipCanadaFrenchOptionName_Text());
        strcat((char *)pu8Str, (char *)enVChipCanadaFrenchOptionName_Text());
        u8Strlen += strlen((char *)enVChipCanadaFrenchOptionName_Text());
    }

    return u8Strlen;
}

#endif // ENABLE_ATSC_VCHIP

