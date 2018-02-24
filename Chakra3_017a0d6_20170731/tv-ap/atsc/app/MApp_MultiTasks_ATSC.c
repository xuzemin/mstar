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


#include "Board.h"

#if(ENABLE_ATSC)

#include "msAPI_Global.h"
#include "msAPI_IR.h"


#include "MApp_GlobalVar.h"
#include "MApp_MultiTasks_ATSC.h"
#include "MApp_MVDMode.h"
#include "MApp_Psip.h"
#include "MApp_SignalMonitor.h"
#include "MApp_VChip.h"
#include "MApp_Audio.h"
#include "msAPI_VD.h"
#include "msAPI_Timer.h"
#if (ENABLE_EASMONITOR)
#include "MApp_TV.h"
#endif

//static MS_U8 fVDStable = FALSE;
//static U32 u32VDStableTimer = 0;
//#define VD_STABLE_PERIOD                2000


#define DEBUG_MT_ATSC(x)    x

#define MT_ATSC_CHECK_POINT()   //PRINT_CURRENT_LINE()

void MApp_MultiTasks_ATSC(void)
{
    if( IsAtscInUse() ) // ATSC
    {
        MT_ATSC_CHECK_POINT();
        //printf("Src=ATSC\n");

        if(fEnableSignalCheck==TRUE)
        {
            MT_ATSC_CHECK_POINT();

            MApp_SignalCheckMonitor();

            MT_ATSC_CHECK_POINT();

            MApp_AUD_PreferSoundTrack_Checker();

            MT_ATSC_CHECK_POINT();

            if (MApp_GetSignalLockStatus() == FE_LOCK)
            {
            #if (STORE_RD_CH_ENABLE == 1)
                if(fEnableMvdTimingMonitor==TRUE)
            #endif
                {
                #if (ENABLE_CHCHANGETIME)
                     if(gbReadyTimingMonitorFlag)
                     {
                         printf("\n>>>[ChChangeTime][Start_TimingMonitor]=[%d]\r\n",msAPI_Timer_DiffTimeFromNow(gU32ChChangeTime));
                         gbReadyTimingMonitorFlag = FALSE;
                     }
                #endif
                    MApp_VID_TimingMonitor(MAIN_WINDOW);
                    fTVSetModeDone = MApp_VID_SetMode(MAIN_WINDOW);

            #if (ENABLE_BOOTTIME) //(ENABLE_AUTOTEST)
                    if (gbBootTimeFinish == FALSE && fTVSetModeDone)
                    {
                        PRINT_AUTOTEST_CHECKPT_TIME("start unmute");
                    }
            #endif

                    if(fTVSetModeDone==TRUE)    // S.G.HAN 061222
                        msAPI_ClearIRFIFO();

                #if (ENABLE_MVDMONITOR)
                    MVD_Monitor();
                #endif

                    //if( (stGenSetting.g_CaptionSetting.u8CCMode == CS_OFF) && (fIsDCCInitialized == TRUE) )
                    msAPI_CC_DigitalCC_Parser(fEnableClosedCaptionFunc);

                }

                MT_ATSC_CHECK_POINT();

                if (fEnableTableMonitor )
                {
                    /* Monitor PSIP Table */
                    MApp_Dmx_STT_Monitor();     // STT
                    MApp_Dmx_MGT_Monitor();     // MGT
                    MApp_Dmx_EIT_Monitor();     // EIT
                    MApp_Dmx_VCT_Monitor();     // VCT
                    MApp_Dmx_PAT_Monitor_ATSC();     // PAT
                    MApp_Dmx_PMT_Monitor_ATSC();    //PMT

                    MT_ATSC_CHECK_POINT();

                #if ENABLE_OAD
                    MApp_Dmx_PMT_Other_Monitor_ATSC();
                #endif

                    MT_ATSC_CHECK_POINT();

                    MApp_Dmx_RRT_Monitor();     // RRT

                    MT_ATSC_CHECK_POINT();

                #if (ENABLE_EASMONITOR)
                    MApp_Dmx_EAS_Monitor();     //EAS
                    MAPP_TV_ProcessEAS();
                #endif

                    MT_ATSC_CHECK_POINT();

                    msAPI_DMX_Proc(0xFF);

                    MT_ATSC_CHECK_POINT();

                #if(ENABLE_ATSC_VCHIP)
                    MApp_VChip_MonitorVChip();  // VChip
                #endif

                #if (ENABLE_DMXMONITOR)
                    DMX_Monitor();
                #endif

                    MT_ATSC_CHECK_POINT();

                    MApp_AudioStreamMonitor();

                    MT_ATSC_CHECK_POINT();

                }

                MT_ATSC_CHECK_POINT();
            }
        }

    }
    else if (IsATVInUse())              // 2. ATV
    {
        //printf("Src=ATV\n");
        if( fEnableSignalCheck == TRUE )
        {
            /*fTVSetModeDone =*/
            //if( fTVSetModeDone == TRUE )
            //    msAPI_ClearIRFIFO();

            /* monitor mts */
        #if 0//(MTS_MONITOR_BY_HOUSEKEEPING)
            MApp_Aud_MonitorMts();
        #endif

            //printf("fVDStable=%u\n", fVDStable);

        #if 0 // Daniel refine
            if (fTVSetModeDone)
            {
                if ( (fVDStable==FALSE) && (msAPI_Timer_DiffTimeFromNow(u32VDStableTimer)>VD_STABLE_PERIOD) )
                {
                    u32VDStableTimer = msAPI_Timer_GetTime0();
                    fVDStable = TRUE;
                }
                else
                {
                    fVDStable = FALSE;
                }
            }
            else if (msAPI_Timer_DiffTimeFromNow(u32VDStableTimer)>VD_STABLE_PERIOD)
            {
                fVDStable = FALSE;
            }


            if ( msAPI_AVD_IsSyncLocked() )
            {
                /* monitor VBI data*/
                CC_SourceFuns.MonitorVBIData( (EN_EIA608_SRV_TYPE)(stGenSetting.g_CaptionSetting.u8CaptionServiceMode&0x0F) ); //analog

            #if(ENABLE_ATSC_VCHIP)
                /* monitor V-Chip lock status */
                MApp_VChip_MonitorVChip();
            #endif

            #if 0
                // to remove dummy channel when vd lock stable
                if( fVDStable
                #if 1//ATSC_READY
                    && IS_DIR_CH(MApp_ChanProc_GetCurMainListProgIndex())
                    && IS_HIDE_CH(MApp_ChanProc_GetCurMainListProgIndex())
                #endif
                    )
                {
                #if 1//ATSC_READY
                    SET_HIDE_CH(MApp_ChanProc_GetCurProgIndex(), FALSE);
                    SET_DIR_CH(MApp_ChanProc_GetCurProgIndex(), FALSE);
                #endif
                    stChSetting.u16TotalHideSrvNum--;
                    stChSetting.u16TotalDirTuneSrvNum--;
                    fVDStable = FALSE;
                }
            #endif

            }
            else
            {
            #if(ENABLE_ATSC_VCHIP)
                if(MApp_VChip_GetCurVChipBlockStatus())
                {
                    MApp_VChip_Init();  // > For no signal After rating Blocking.
                }
            #endif
            }
        #endif

            MT_ATSC_CHECK_POINT();

            MApp_SignalCheckMonitor();

            MT_ATSC_CHECK_POINT();

        }
    }
    else if( IsAVInUse() &&(!IsATVInUse()) )  // 5. if(IsDigitalSourceInUse()) w/o ATV - AV, S-Video or Scart
    {

    }


    // CC/VChip monitor ...
    if( (IsATVInUse()&&(fEnableSignalCheck)) //   ATV && Enable Channel
      ||(IsAVInUse()) // AV
      )
    {
        //printf("Src=ATV or AV\n");

        // If VD HW lock and stable
        if( //msAPI_AVD_IsSyncLocked()
          //&&(E_VIDEOSTANDARD_NOTSTANDARD != msAPI_AVD_GetCurrentVideoStandard())
            msAPI_AVD_IsHasStableSignal()
          )
        {
            //printf(" VD lock\n");

            MT_ATSC_CHECK_POINT();

            /* monitor VBI data*/
            CC_SourceFuns.MonitorVBIData( (EN_EIA608_SRV_TYPE)(stGenSetting.g_CaptionSetting.u8CaptionServiceMode&0x0F) ); //analog

            MT_ATSC_CHECK_POINT();

        #if(ENABLE_ATSC_VCHIP)
            /* monitor V-Chip lock status */
            MApp_VChip_MonitorVChip();

            MT_ATSC_CHECK_POINT();
        #endif
        }
        else
        {
            //printf(" VD unlock\n");
        #if(ENABLE_ATSC_VCHIP)
            if(MApp_VChip_GetCurVChipBlockStatus())
            {
                MT_ATSC_CHECK_POINT();

                MApp_VChip_Init();  //  For no signal After rating Blocking.

                MT_ATSC_CHECK_POINT();
            }
        #endif
        }

    }

    MT_ATSC_CHECK_POINT();

}

#endif

