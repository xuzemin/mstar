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

#define MAPP_VDMODE_C

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include <stdio.h>

#include "Board.h"

#include "datatype.h"
#include "debug.h"


#include "msAPI_Global.h"
#include "msAPI_VD.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Sys.h"
#include "msAPI_Tuning.h"

#include "MApp_GlobalSettingSt.h"
#include "MApp_VDMode.h"
#include "MApp_PCMode.h"
#include "MApp_Scaler.h"

//ZUI_TODO: #include "MApp_UiMenu.h"
#include "MApp_GlobalFunction.h"

#if(ENABLE_ATSC)
#include "MApp_ChannelProc_ATSC.h"
#endif


//#include "ZUI_tables_h.inl"
//#include "ZUI_exefunc.h"
#include "MApp_UI_EventHandler.h"

//------------------------------------------------------------------------------
// Function name:        MApp_VD_IsSyncLock
// Passing parameter:    none
// Return parameter:     BOOLEAN:    video decoder sync lock or not
// Description:          Get video decoder sync lock status
//------------------------------------------------------------------------------
BOOLEAN MApp_VD_IsSyncLock(void)
{
    BOOLEAN bIsSyncDetected;

    //bIsSyncDetected = msAPI_AVD_IsSyncLocked();
    bIsSyncDetected = msAPI_AVD_IsHasStableSignal();

    return bIsSyncDetected;
}

//------------------------------------------------------------------------------
// Function name:        MApp_VD_SetMode
// Passing parameter:    none
// Return parameter:     none
// Description:          Set VD mode settings
//------------------------------------------------------------------------------
BOOLEAN MApp_VD_SetMode ( SCALER_WIN eWindow )
{
    INPUT_SOURCE_TYPE_t eCurINPUT_SOURCE = SYS_INPUT_SOURCE_TYPE(eWindow);
    //U8 u8TurnOffDestination = DISABLE;
    U8 u8ScalerWinOnOff = DISABLE;


    //printf("MApp_VD_SetMode(win=%u)\n", eWindow);

    // Log time for ChangeChannel
#if ( ENABLE_LOG_CHANGE_CHANNEL )
    printf("VD_SetMode at %u\n", g_Debug_u32Time_ChangeChannel);
#endif
#if ( DEBUG_CHG_SRC_TIME)
    //printf("VD_SetMode-1 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("VD_SetMode Start");
#endif


    if( MApp_IsSrcHasSignal(eWindow) )
    {
        u8ScalerWinOnOff = ENABLE;
    }
    else // No signal
    {
    #if ( ENABLE_ATSC )
        #ifdef DISABLE_ATV_NOSIGNAL_SNOW
        if( IsSrcTypeATV(eCurINPUT_SOURCE) && MApp_ChanProc_IsAnyChannelExist() && IsVDHasSignal())
        #else
        if( IsSrcTypeATV(eCurINPUT_SOURCE) && MApp_ChanProc_IsAnyChannelExist())
        #endif
    #else
        if( IsSrcTypeATV(eCurINPUT_SOURCE) )
    #endif
        {
            u8ScalerWinOnOff = ENABLE;
        }
        else
            u8ScalerWinOnOff = DISABLE;
    }


    // Trigger sync event. Make all destination setup its own environment
  #if 1//Has signal || ATV -> framelock
    //if (MApp_IsSrcHasSignal(eWindow) || IsSrcTypeATV(eCurINPUT_SOURCE) )
    if( u8ScalerWinOnOff == ENABLE )
    {
        {
            MApi_XC_ADC_Source_Calibrate(eCurINPUT_SOURCE);
            MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(eCurINPUT_SOURCE, NULL);
        }
    }
  #else//Has signal -> framelock; ATV snow screen -> freerun
    if (MApp_IsSrcHasSignal(eWindow)
    {
        MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(SYS_INPUT_SOURCE_TYPE(eWindow),NULL);
    }
    else if (IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(eWindow)))
    {
        MApi_SC_ForceFreerun(TRUE);
        MAPI_XC_MUX_TRIGGER_PATH_SYNC_EVENT(SYS_INPUT_SOURCE_TYPE(eWindow),NULL);
        MApi_SC_ForceFreerun(FALSE);
    }
  #endif

    //if ( MApp_IsSrcHasSignal(eWindow) || (IsSrcTypeATV(eCurINPUT_SOURCE)) )
    if( u8ScalerWinOnOff == ENABLE )
    {
        //u8TurnOffDestination = ENABLE;

        // signal detected. Enable all destination.
        if( IsSrcTypeDigitalVD(eCurINPUT_SOURCE) )
        {
            MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(eCurINPUT_SOURCE, &u8ScalerWinOnOff);
        }

    #if(PATCH_FOR_V_RANGE)
        if( IsSrcTypeATV(eCurINPUT_SOURCE) )
            MApp_VD_StartRangeHandle();
    #endif
    }
    else
    {
        //u8TurnOffDestination = DISABLE;
        // disable destination

        if( IsSrcTypeDigitalVD(eCurINPUT_SOURCE) )
        {
            MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(eCurINPUT_SOURCE, &u8ScalerWinOnOff);

        #if 0 // Need refinfe!
          #if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_EDEN)  || \
             (CHIP_FAMILY_TYPE == CHIP_FAMILY_NASA)  || \
             (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)) //Set CVBS out ATV for all source without DTV 20100420EL
            u8TurnOffDestination = ENABLE; //SCART out ATV even if no signal 20100421EL
            MAPI_XC_MUX_TRIGGER_DEST_ON_OFF_EVENT(INPUT_SOURCE_TV, &u8ScalerWinOnOff);
          #endif
        #endif
        }
    }



    //if( MApp_IsSrcHasSignal(eWindow) )
    {
        MApp_UI_NotifySysEvent(E_SYS_EVENT_VD_SET_MODE_DONE, NULL);
    }

    // Log time for ChangeChannel
#if( ENABLE_LOG_CHANGE_CHANNEL )
    printf("VD_SetMode end %u\n", g_Debug_u32Time_ChangeChannel);
#endif
#if ( DEBUG_CHG_SRC_TIME)
    //printf("VD_SetMode-10 %u\n", g_Debug_u32Time_ChangeSrc);
    msDebug_PrintChgSrcTime("VD_SetMode End");
#endif

    return TRUE;
}


#if(PATCH_FOR_V_RANGE)
static U16 u16PreVtotal;
#define    VD_NONST_DEBUG(x)       x
void MApp_VD_RangeReset(void)
{
    u16PreVtotal = 0;
}

void MApp_VD_StartRangeHandle(void)
{
    U16 wVtotal = msAPI_Scaler_VD_GetVTotal(MAIN_WINDOW, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), GET_SYNC_DIRECTLY, NULL);
    if ((wVtotal < 675 ) && (wVtotal > 570))
        u16PreVtotal = 625;
    else
        u16PreVtotal = 525;
}
#define SYNC_STABLE_COUNTER  10

void MApp_VD_SyncRangeHandler(void)
{
    U16 wVtotal = msAPI_Scaler_VD_GetVTotal(MAIN_WINDOW, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), GET_SYNC_DIRECTLY, NULL);
    U16 g_cVSizeShift = 0;
    U16 u16V_CapSize;
    U16 u16_VCapSt;
    MS_WINDOW_TYPE stCaptureWin;
    static U8 u8SyncStableCounter = SYNC_STABLE_COUNTER;

    if (!IsSrcTypeATV(SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW)))
        return;
    if (!MApp_IsSrcHasSignal(MAIN_WINDOW))
        return;
    if(msAPI_Tuner_IsTuningProcessorBusy())
        return;
    if (u16PreVtotal == 0)
        return;

    if ((wVtotal < 620) && (wVtotal > 570))
    {
        if (u16PreVtotal != wVtotal)
        {
            u16PreVtotal  = wVtotal;
            u8SyncStableCounter = 0;
        }
        else if (u8SyncStableCounter < SYNC_STABLE_COUNTER)
        {
            u8SyncStableCounter ++;
        }
    }
    else if (((wVtotal < 520) && (wVtotal > 470)) || ((wVtotal > 530) && (wVtotal < 570)))
    {
        if (u16PreVtotal != wVtotal)
        {
            u16PreVtotal  = wVtotal;
            u8SyncStableCounter = 0;
        }
        else if (u8SyncStableCounter < SYNC_STABLE_COUNTER)
        {
            u8SyncStableCounter ++;
        }
    }
    else if(((wVtotal <= 630) && (wVtotal >= 620)) || ((wVtotal <= 530) && (wVtotal >= 520)))
    {
        if((u16PreVtotal > (wVtotal + 5)) || (u16PreVtotal < (wVtotal - 5)))
        {
            u16PreVtotal  = wVtotal;
            u8SyncStableCounter = 0;
        }
        else if (u8SyncStableCounter < SYNC_STABLE_COUNTER)
        {
            u8SyncStableCounter ++;
        }
    }

    if(u8SyncStableCounter == SYNC_STABLE_COUNTER)
    {
        VD_NONST_DEBUG(printf("VR: Vtotal[%d]\n",wVtotal));
        MApi_XC_GetCaptureWindow(&stCaptureWin, MAIN_WINDOW);
        u8SyncStableCounter = (SYNC_STABLE_COUNTER + 1);
        u16V_CapSize = stCaptureWin.height;
		u16_VCapSt = stCaptureWin.y;

        if (((wVtotal < 620) && (wVtotal > 570)) || ((wVtotal > 630) && (wVtotal < 670)))
        {
            if (wVtotal > 625)
            {
                g_cVSizeShift = wVtotal - 625;
                u16V_CapSize = 576 + g_cVSizeShift;
            }
            else
            {
                g_cVSizeShift = 625 - wVtotal;
                u16V_CapSize = 576 - g_cVSizeShift;     //576 is waite factory menu
            }
        }
        else if (((wVtotal < 520) && (wVtotal > 470)) || ((wVtotal > 530) && (wVtotal < 570)))
        {
            if (wVtotal > 525)
            {
                g_cVSizeShift = wVtotal - 525;
                u16V_CapSize = 480 + g_cVSizeShift;
            }
            else
            {
                g_cVSizeShift = 525 - wVtotal;
                u16V_CapSize = 480 - g_cVSizeShift;
            }
        }

        if(wVtotal == 625 )
        {
	        u16V_CapSize=576 ;
        }
        else if(wVtotal == 525)
        {
	        u16V_CapSize=480;
        }

        VD_NONST_DEBUG(printf("x:%d,y:%d,w:%d,h:%d\n",stCaptureWin.x,stCaptureWin.y,stCaptureWin.width,stCaptureWin.height));
        stCaptureWin.height =  u16V_CapSize;
        printf("%s,%d,stCaptureWin.height=%d\n",__FILE__,__LINE__,stCaptureWin.height);

        MApp_Scaler_SetCustomerWindow(&stCaptureWin, NULL, NULL, MAIN_WINDOW);
    }
}
#endif

#undef MAPP_VDMODE_C

