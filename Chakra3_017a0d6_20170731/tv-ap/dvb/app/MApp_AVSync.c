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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#define MAPP_AVSYNC_C

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "debug.h"

#include "datatype.h"
#include "sysinfo.h"

// Common Definition
#include "MsCommon.h"
#include "apiXC.h"
#include "msAPI_Video.h"
#include "MApp_AVSync.h"
#include "msAPI_Timer.h"
#include "apiDMX.h"
#include "apiAUDIO.h"

#if (ENABLE_DTV)
#include "mapp_demux.h"
#endif


#define AV_SYNC_DBG(x)      //x

//extern U8 u8PcrFid;
//extern U32 msAPI_DMX_GetStc(U8 );

void MApp_AVSync_ForceSync(void)
{
    static U32 u32PreSyncTimer;
    static U32 u32PrevVideoPTS = 0;
    U32 u32VideoPTS;
    U32 u32SystemSTC,u32SystemSTC_H;
    U32 u32Diff;
    static U8 u8ErrorCount = 0;

    if (msAPI_Timer_DiffTimeFromNow(u32PreSyncTimer) >= 2000)
    {
        //get video pts
        //u32SystemSTC = msAPI_DMX_GetStc();
        MApi_DMX_Stc_Get(&u32SystemSTC_H, &u32SystemSTC);
//        u32VideoPTS = msAPI_VID_GetPTS();
        u32VideoPTS = MApi_VDEC_GetPTS();
        u32VideoPTS*=90;
        if (u32SystemSTC >= u32VideoPTS)
        {
            u32Diff = u32SystemSTC - u32VideoPTS;
        }
        else
        {
            u32Diff = u32VideoPTS - u32SystemSTC;
        }

        if ( (u32VideoPTS != 0) && (u32VideoPTS != u32PrevVideoPTS) )
        {
            if (u32Diff > 0x1000)
            {
                printf("Leo--%s,%d: Force Sync\n",__FUNCTION__,__LINE__);
                MApi_VDEC_AVSyncOn(FALSE, 0, 0);

                if(u32Diff>0x40000)
                {
                    u8ErrorCount++;

                    if(u8ErrorCount == 2)
                    {
                        //msAPI_DMX_SetStc(*MApp_Dmx_GetFid(EN_PCR_FID), u32VideoPTS);
                        MApi_DMX_Stc_Set(u32SystemSTC_H, u32VideoPTS);
                        u8ErrorCount = 0;
                    }
                }
                else
                {
                    if (u32SystemSTC >= u32VideoPTS)
                    {
                        //msAPI_DMX_SetStc(*MApp_Dmx_GetFid(EN_PCR_FID), u32SystemSTC-u32Diff/2);
                        MApi_DMX_Stc_Set(u32SystemSTC_H, u32SystemSTC-u32Diff/2);
                        u8ErrorCount = 0;
                    }
                    else
                    {
                        //msAPI_DMX_SetStc(*MApp_Dmx_GetFid(EN_PCR_FID),  u32VideoPTS-u32Diff/2);
                        MApi_DMX_Stc_Set(u32SystemSTC_H, u32VideoPTS-u32Diff/2);
                        u8ErrorCount = 0;
                    }
                }
                MApi_VDEC_AVSyncOn(TRUE, 180, 0);
            }
        }
        u32PreSyncTimer = msAPI_Timer_GetTime0();
        u32PrevVideoPTS = u32VideoPTS;

        AV_SYNC_DBG(printf("STC = %08lx, ", u32SystemSTC));
        AV_SYNC_DBG(printf("PTS = %08lx, ", u32VideoPTS));

        if (u32SystemSTC >= u32VideoPTS)
        {
            AV_SYNC_DBG(printf("diff = +%08lx ", u32Diff));
        }
        else
        {
            AV_SYNC_DBG(printf("diff = -%08lx ", u32Diff));
        }
    }
}


#if AV_SYNC_ADJUST

#define FRAME_CONTROL_DEBUG_MESSAGE_DURATION    1000 //MS
#define AV_SYNC_ADJUST_TRIGGER_THRESHOLD        50 //ms
#define VDEC_SYNC_TOLERANCE_DEFAULT_VALUE       25 //ms

typedef enum
{
    E_AVSYNC_STATUS_INITIAL,
    E_AVSYNC_STATUS_NORMAL,
    E_AVSYNC_STATUS_ABNORMAL,
} AV_SYNC_STATUS;
AV_SYNC_STATUS m_eAVSyncStatus;


static MS_U64 u64LastDelay = 0;

void MApp_AVSync_ResetAvSyncStatus(void)
{
    m_eAVSyncStatus = E_AVSYNC_STATUS_INITIAL;

    printf("\e[31;1m Reset AV Sync delay status \33[m \n");
}

//
// check VPTS and APTS
//
void MApp_AVSync_Adjust(void)
{
    MS_U32 u32DecodeCnt = 0;

    MS_U32 u32STC_H, u32STC_L;
    MS_U64 u64STC = 0;

    MS_U32 u32VPTS, u32APTS;
    MS_U64 u64ADelayUpperLimit;
    MS_U64 u64VPTS_STC_Diff, u64APTS_STC_Diff;
    BOOL bIsNegative = 0;
    MS_U64 u64CurrentDelay = 0;

    static MS_U32 u32PrevTime;


#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA) // currently only support NASA

    if (msAPI_Timer_DiffTimeFromNow(u32PrevTime) >= FRAME_CONTROL_DEBUG_MESSAGE_DURATION)
    {
        u32DecodeCnt = MApi_VDEC_GetFrameCnt();

        MApi_DMX_Stc_Get(&u32STC_H, &u32STC_L);
        u64STC = (((MS_U64)u32STC_H << 32) + u32STC_L)/90; //from 90KHz to ms

        u32VPTS = MApi_VDEC_GetPTS();    // ms

        u32APTS = MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_getlatest_PTS);
        u32APTS = u32APTS / 90; //from 90KHz to ms

        u64ADelayUpperLimit =
            MApi_AUDIO_GetCommAudioInfo(Audio_Comm_infoType_ADEC1_avsync_delay_upperlimit);

        u64VPTS_STC_Diff = (u64STC >= u32VPTS) ? (u64STC - u32VPTS) : (u32VPTS - u64STC);
        u64APTS_STC_Diff = (u64STC >= u32APTS) ? (u64STC - u32APTS) : (u32APTS - u64STC);

      #if 1 // debug log
        msDebug_ANSI_SetColorText(E_FONT_COLOR_BLACK);
        msDebug_ANSI_SetColorText(E_FONT_BACKGROUND_COLOR_YELLOW);

        printf("\n u32DecodeCnt        : 0x%X \n", u32DecodeCnt);
        printf(" u64STC              : 0x%X \n", u64STC);
        printf(" u32VPTS             : 0x%X \n", u32VPTS);
        printf(" u32APTS             : 0x%X \n", u32APTS);
        printf(" u64ADelayUpperLimit : 0x%X \n", u64ADelayUpperLimit);
        printf(" u64VPTS_STC_Diff    : 0x%X \n", u64VPTS_STC_Diff);
        printf(" u64APTS_STC_Diff    : 0x%X \n", u64APTS_STC_Diff);

        msDebug_ANSI_AllAttrOffText();
      #endif

        if ( u32DecodeCnt != 0)
        {
            if ((m_eAVSyncStatus == E_AVSYNC_STATUS_INITIAL) && (u64LastDelay != 0))
            {
                u64LastDelay = 0;

                MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_ADEC1_avsync_delay, 0, 0 );

                //default vdec delay 185ms
                MApi_VDEC_AVSyncOn(TRUE, VDEC_SYNC_TOLERANCE_DEFAULT_VALUE, VDEC_SYNC_TOLERANCE_DEFAULT_VALUE);

                printf("\e[31;1m Reset AV Sync delay time \33[m \n");
            }

            if ( (u64VPTS_STC_Diff >= AV_SYNC_ADJUST_TRIGGER_THRESHOLD)
               ||(u64APTS_STC_Diff >= AV_SYNC_ADJUST_TRIGGER_THRESHOLD) )
            {
                //video master case
                if (u32VPTS < u32APTS)
                {
                    m_eAVSyncStatus = E_AVSYNC_STATUS_ABNORMAL;
                    u64CurrentDelay = u64VPTS_STC_Diff;
                    if (u64STC < u32VPTS)
                    {
                        bIsNegative = 1;
                    }
                }
                //audio master case
                else if (u32VPTS > u32APTS)
                {
                    m_eAVSyncStatus = E_AVSYNC_STATUS_ABNORMAL;
                    u64CurrentDelay = u64APTS_STC_Diff;
                    if (u64STC < u32APTS)
                    {
                        bIsNegative = 1;
                    }
                }
                else
                {
                    m_eAVSyncStatus = E_AVSYNC_STATUS_NORMAL;
                }
            }

            switch (m_eAVSyncStatus)
            {
                case E_AVSYNC_STATUS_NORMAL:
                    break;

                case E_AVSYNC_STATUS_ABNORMAL:
                    if (u64CurrentDelay >= u64ADelayUpperLimit)
                    {
                        u64CurrentDelay = u64ADelayUpperLimit - 1;
                    }

                    if (u64CurrentDelay > u64LastDelay)
                    {
                        MApi_AUDIO_SetCommAudioInfo(Audio_Comm_infoType_ADEC1_avsync_delay, u64CurrentDelay, 0 );

                        MApi_VDEC_AVSyncOn(TRUE, u64CurrentDelay, VDEC_SYNC_TOLERANCE_DEFAULT_VALUE);

                        u64LastDelay = u64CurrentDelay;

                        printf("Updated AV Sync delay time = %s %llu ms.\n",
                                        (bIsNegative ? "-" : " "), u64LastDelay);
                    }
                    break;

                default:
                    break;
            }
        } // if ( u32DecodeCnt != 0)

        u32PrevTime = msAPI_Timer_GetTime0();
    }
#endif
}

#endif // #if AV_SYNC_ADJUST



//******************************************************************************
//
#undef MAPP_AVSYNC_C

