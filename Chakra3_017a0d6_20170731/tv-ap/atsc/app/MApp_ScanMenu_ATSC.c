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

#define MAPP_SCAN_MENU_C

//==============================================================================
/*                 Header Files                                                 */
//==============================================================================
#include <string.h>
#include <stdlib.h>
#include "datatype.h"
#include "msAPI_OSD.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalVar.h"
#include "MApp_Exit.h"
#include "MApp_Key.h"
#include "MApp_Scan.h"
#include "MApp_ScanMenu_ATSC.h"
#include "MApp_GlobalFunction.h"
#include "RF_Tuner_ATSC.h"

//==============================================================================
/*                      Functions                                               */
//==============================================================================

 /////////////////////////////////////////////////////////////////////////////
// MapChanToFreq
//
// Inputs:
//      void *Instance, points to device instance
//      U8 u8Channel - channel to convert to frequency
//
// Outputs:
//      MS_TP_SETTING_ATSC *pstTPSetting - frequency corresponding to specified channel KHz
//
// Returns:
//      TRUE = no error
//      FALSE = channel out of range
/////////////////////////////////////////////////////////////////////////////
BOOLEAN MapChanToFreq(U8 u8Channel, U16 *pu16Frequency, U8 u8CableSystem)
{
    U16 u16Freq = 0;

    if((CHAN_MIN > u8Channel) || (CHAN_MAX < u8Channel))
    {
        // channel out of range
        return FALSE;
    }

    if( ANT_TYPE == ANT_AIR )
    {
        switch(u8Channel)
        {
            /* UHF */
            default: u16Freq = (U16)((u8Channel * 6000L + 387250L)/FREQ_STEP); break;
            /* Lo VHF */
            case 2:  u16Freq = (U16)(55250L/FREQ_STEP);     break;
            case 3:  u16Freq = (U16)(61250L/FREQ_STEP);     break;
            case 4:  u16Freq = (U16)(67250L/FREQ_STEP);     break;
            case 5:  u16Freq = (U16)(77250L/FREQ_STEP);     break;
            case 6:  u16Freq = (U16)(83250L/FREQ_STEP);     break;
            /* Hi VHF */
            case 7:  u16Freq = (U16)(175250L/FREQ_STEP);    break;
            case 8:  u16Freq = (U16)(181250L/FREQ_STEP);    break;
            case 9:  u16Freq = (U16)(187250L/FREQ_STEP);    break;
            case 10: u16Freq = (U16)(193250L/FREQ_STEP);    break;
            case 11: u16Freq = (U16)(199250L/FREQ_STEP);    break;
            case 12: u16Freq = (U16)(205250L/FREQ_STEP);    break;
            case 13: u16Freq = (U16)(211250L/FREQ_STEP);    break;
        }
    }
    else //ANT_CATV
    {
        /* Freq_STD/Freq_IRC */
        switch(u8Channel)
        {
            default:
                if((u8Channel >= 7) && (u8Channel <= 13))
                    u16Freq = (U16)(((u8Channel - 7) * 6000L + 175250L)/FREQ_STEP);
                else if((u8Channel >= 14) && (u8Channel <= 22))
                    u16Freq = (U16)(((u8Channel - 14) * 6000L + 121262L)/FREQ_STEP);
                else if((u8Channel >= 25) && (u8Channel <= 41))
                    u16Freq = (U16)(((u8Channel - 25) * 6000L + 229262L)/FREQ_STEP);
                else if((u8Channel >= 43) && (u8Channel <= 53))
                    u16Freq = (U16)(((u8Channel - 43) * 6000L + 337262L)/FREQ_STEP);
                else if((u8Channel >= 54) && (u8Channel <= 94))
                    u16Freq = (U16)(((u8Channel - 54) * 6000L + 403250L)/FREQ_STEP);
                else if((u8Channel >= 100) && (u8Channel <= 158))
                    u16Freq = (U16)(((u8Channel - 100) * 6000L + 649250L)/FREQ_STEP);
                break;

            case 1:  u16Freq = (U16)(73250L/FREQ_STEP);   break;
            case 2:  u16Freq = (U16)(55250L/FREQ_STEP);   break;
            case 3:  u16Freq = (U16)(61250L/FREQ_STEP);   break;
            case 4:  u16Freq = (U16)(67250L/FREQ_STEP);   break;
            case 5:  u16Freq = (U16)(77250L/FREQ_STEP);   break;
            case 6:  u16Freq = (U16)(83250L/FREQ_STEP);   break;
            case 23: u16Freq = (U16)(217250L/FREQ_STEP);  break;
            case 24: u16Freq = (U16)(223250L/FREQ_STEP);  break;
            case 42: u16Freq = (U16)(331275L/FREQ_STEP);  break;
            case 95: u16Freq = (U16)(91250L/FREQ_STEP);   break;
            case 96: u16Freq = (U16)(97250L/FREQ_STEP);   break;
            case 97: u16Freq = (U16)(103250L/FREQ_STEP);  break;
            case 98: u16Freq = (U16)(109275L/FREQ_STEP);  break;
            case 99: u16Freq = (U16)(115275L/FREQ_STEP);  break;
        }

        /* map to HRC system: Freq_HRC = Freq_STD - 1.25 Mhz*/
        if(u8CableSystem == CABLE_SYSTEM_HRC)
        {
            u16Freq -= (U16)(1250/FREQ_STEP);
        }
        if(u8Channel==5 || u8Channel==6)
        {
            //if(CableSystem != CABLE_SYSTEM_STD)
            if( (u8CableSystem == CABLE_SYSTEM_IRC)||(u8CableSystem == CABLE_SYSTEM_HRC) )
                u16Freq += (U16)(2000/FREQ_STEP);
        }

        /* Center_carrier = Video_carrier + 1.75 Mhz */
        //if(pstTPSetting->fModulation != DEMOD_ATSC_MODE_NTSC)
       //     u16Freq += (U16)(1750/FREQ_STEP); // add offset from Peak-of-sync
    }


    // Check if pu16Frequency is not alignment to 2
    // Patch AeonR2 unalignment exception
    if( ((U32)pu16Frequency) & 1)
    {
        PRINT_CURRENT_LINE();
        printf("MapChanToFreq: pu16Frequency=0x%X is not alignment!\n", (U32)pu16Frequency);

        U8 * pu8Freq = (U8*)pu16Frequency;
        pu8Freq[0] = u16Freq&0xFF;
        pu8Freq[1] = u16Freq>>8;
    }
    else
    {
        *pu16Frequency = u16Freq;
    }

    return TRUE;
}

//*************************************************************************
//Function name:    MApp_ScanMenu_GetTPSetting
//Passing parameter:    MS_TP_SETTING_ATSC *pstTPSetting
//Return parameter:     none
//Description:      Get the selected TP setting in Scan Menu
//*************************************************************************
BOOLEAN MApp_ScanMenu_GetTPSetting(U8 u8RF_CH, MS_TP_SETTING_ATSC *pstTPSetting, U8 CableSystem)
{
    //printf("MApp_ScanMenu_GetTPSetting(u8RF_CH=%u,CableSystem=%u)\n", u8RF_CH, CableSystem);

    //try this modulation first
    if(ANT_TYPE == ANT_CATV)
    {
      #if (FRONTEND_DEMOD_ATSC_TYPE==SAMSUNG_S5H1409_DEMODE || FRONTEND_DEMOD_ATSC_TYPE==SAMSUNG_S5H1410_DEMODE)
        pstTPSetting->fSpectrum=DEMOD_SPECTRUM_AUTO;
      #else
        pstTPSetting->fSpectrum=DEMOD_ATSC_SPECTRUM_NORMAL;
      #endif
    }

    U16 u16StdFreq = 0;

    BOOLEAN bRtn = MapChanToFreq(u8RF_CH, &u16StdFreq, CableSystem);

    if( bRtn )
    {
        pstTPSetting->u16Frequency = u16StdFreq;
        //printf(" => TP: Freq=%u)\n", pstTPSetting->u16Frequency );
    }

    return bRtn;
}


#undef MAPP_SCAN_MENU_C

