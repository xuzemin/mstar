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

#ifndef _MAPP_GLOBAL_SETTING_ST_TV_H_
#define _MAPP_GLOBAL_SETTING_ST_TV_H_


#define MAX_DTV_PHYSICAL_CH_NUM         70  // 2~69
#define MAX_ATV_PHYSICAL_CH_NUM         1  // 2~69
#define MAX_PHYSICAL_CH_NUM             (MAX_DTV_PHYSICAL_CH_NUM + MAX_ATV_PHYSICAL_CH_NUM)

#define DTV_BASE_PHYSICAL_IDX           (0)
//#define ATV_BASE_PHYSICAL_IDX           (DTV_BASE_PHYSICAL_IDX+MAX_DTV_PHYSICAL_CH_NUM)

#if (ENABLE_ATSC)
    #define CHAN_AIR_MIN            2
    #define CHAN_AIR_MAX            69

    #define CHAN_CATV_MIN           1
    #define CHAN_CATV_MAX           135

    #define CHAN_MAX        ((ANT_TYPE == ANT_AIR) ? CHAN_AIR_MAX : CHAN_CATV_MAX )
    #define CHAN_MIN        ((ANT_TYPE == ANT_AIR) ? CHAN_AIR_MIN : CHAN_CATV_MIN )

#elif ( ENABLE_DVB_TAIWAN_APP || ENABLE_SBTVD_ATV_SYSTEM|| (TV_SYSTEM == TV_NTSC) )
    #define CHAN_AIR_MIN                24
    #define CHAN_AIR_MAX                36

#elif (  TV_SYSTEM == TV_NTSC )
    #define CHAN_AIR_MIN                1
    #define CHAN_AIR_MAX                99

#else
    #define CHAN_AIR_MIN                21
    #define CHAN_AIR_MAX                69
#endif


//=======================================================================

#if ENABLE_ISDBT
typedef enum
{
    ANTENNA_DTV_TYPE,
    ANTENNA_ATV_TYPE,
    ANTENNA_TYPE_NUM
}E_ANTENNA_SOURCE_TYPE;
#endif


#if( (BRAZIL_CC)||(ATSC_CC == ATV_CC) )
typedef enum
{
    ATV_CAPTION_TYPE_OFF,
    ATV_CAPTION_TYPE_CC1,
    ATV_CAPTION_TYPE_CC2,
    ATV_CAPTION_TYPE_CC3,
    ATV_CAPTION_TYPE_CC4,
    ATV_CAPTION_TYPE_TEXT1,
    ATV_CAPTION_TYPE_TEXT2,
    ATV_CAPTION_TYPE_TEXT3,
    ATV_CAPTION_TYPE_TEXT4,
    ATV_CAPTION_TYPE_NUM
} EN_ATV_CAPTION_TYPE;

typedef enum
{
    DTV_CAPTION_OFF,
    DTV_CAPTION_ON
} EN_DTV_CAPTION_TYPE;
#endif

//=======================================================================


//#include "MApp_GlobalSettingSt_dvb.h"

#if(ENABLE_S2)
    #include "MApp_GlobalSettingSt_tv_S2.h"
#endif



//******************************************************************************

#endif // #ifndef _MAPP_GLOBAL_SETTING_ST_TV_H_

