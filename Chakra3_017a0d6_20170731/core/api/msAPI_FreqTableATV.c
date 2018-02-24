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

#include "Board.h"
#include "debug.h"
#include "msAPI_FreqTableATV.h"
#include "msAPI_FreqTableCommon.h"
#include "msAPI_Tuning.h"
#include "msAPI_audio.h"
#include "Tuner.h"

//#define DEBUG_CHANNELFREQTABLE    0xFF

#ifdef DEBUG_CHANNELFREQTABLE
    #define debugChannelFreqTablePrint(a,b)    debugPrint(a,b)
#else
    #define debugChannelFreqTablePrint(a,b)
#endif

//****************************************************************************
// Private attributes of this file.
//****************************************************************************

#define MEDIUM_MASK    0xF000
#define _AIR        0x8000
#define _CABLE        0x4000
#define _COMMON        0xC000

#define CHANNEL_BANDWIDTH_MASK        0x0F00
#define CHANNEL_BANDWIDTH_0M        0x0000
#define CHANNEL_BANDWIDTH_6M        0x0100
#define CHANNEL_BANDWIDTH_7M        0x0200
#define CHANNEL_BANDWIDTH_8M        0x0300
#define CHANNEL_BANDWIDTH_9M        0x0400
#define CHANNEL_BANDWIDTH_10M        0x0500
#define CHANNEL_BANDWIDTH_11M        0x0600
#define CHANNEL_BANDWIDTH_12M        0x0700

#define LEAD_CHANNEL_MASK            0x00FF

#define CCIR_UHF_FIRSTCHANNEL        21


// ================ Channel Frequency Table ============================
// As you see tables below, channel frequency data is divided by 0.25MHz
// because it is too big to fit in 16bit data type(unsigned int).
// Otherwide it takes 32bit data type(unsigned long).
// This is a kind of compression.
// This compressed frequency data is converted to Channel PLL data for Tuning.
// Refer two functions. ConvertCompressedFrequencytoPLL, ConvertPLLtoCompressedFrequency

typedef struct
{
    WORD wFrequency;
    WORD wChannel;
} FREQCHANNEL;

static FREQCHANNEL m_FreqChannel_BG[] =
{
    { 1869, _AIR    | 21 | CHANNEL_BANDWIDTH_8M },    //(471.25 MHz - 4.0 MHz) / 0.25 MHz
    { 1195, _CABLE    | 21 | CHANNEL_BANDWIDTH_8M },  //(303.25 MHz - 4.5 MHz) / 0.25 MHz
    { 911 , _CABLE    | 11 | CHANNEL_BANDWIDTH_7M },  //(231.25 MHz - 3.5 MHz) / 0.25 MHz
    { 687 , _AIR    |  5 | CHANNEL_BANDWIDTH_7M },  //(175.25 MHz - 3.5 MHz) / 0.25 MHz
    { 405 , _CABLE    |  1 | CHANNEL_BANDWIDTH_7M },  //(105.25 MHz - 4.0 MHz) / 0.25 MHz
    { 263 , _CABLE    | 42 | CHANNEL_BANDWIDTH_7M },  //( 69.25 MHz - 3.5 MHz) / 0.25 MHz
    { 187 , _AIR    |  2 | CHANNEL_BANDWIDTH_7M },  //( 48.25 MHz - 1.5 MHz) / 0.25 MHz
    { 167 , _AIR    |  1 | CHANNEL_BANDWIDTH_7M }   //( 45.25 MHz - 3.5 MHz) / 0.25 MHz
};

#if 0 // No need for DVB-T project.
static ROM FREQCHANNEL m_FreqChannel_BB[] =
{
    { 1871, _AIR    | 20 | CHANNEL_BANDWIDTH_7M },    //(471.25 MHz -  3.5 MHz) / 0.25 MHz
    { 1195, _CABLE    | 21 | CHANNEL_BANDWIDTH_7M },  //(303.25 MHz -  4.5 MHz) / 0.25 MHz
    { 911 , _CABLE    | 11 | CHANNEL_BANDWIDTH_7M },  //(231.25 MHz -  3.5 MHz) / 0.25 MHz
    { 687 , _AIR    |  8 | CHANNEL_BANDWIDTH_7M },  //(175.25 MHz -  3.5 MHz) / 0.25 MHz
    { 557 , _CABLE    |  6 | CHANNEL_BANDWIDTH_7M },  //(140.25 MHz -  1.0 MHz) / 0.25 MHz
    { 543 , _AIR    |  7 | CHANNEL_BANDWIDTH_7M },  //(138.25 MHz -  2.5 MHz) / 0.25 MHz
    { 429 , _CABLE    |  2 | CHANNEL_BANDWIDTH_7M },  //(112.25 MHz -  5.0 MHz) / 0.25 MHz
    { 363 , _AIR    |  5 | CHANNEL_BANDWIDTH_7M },  //( 95.25 MHz -  4.5 MHz) / 0.25 MHz
    { 301 , _AIR    |  4 | CHANNEL_BANDWIDTH_9M },  //( 86.25 MHz - 11.0 MHz) / 0.25 MHz
    { 207 , _AIR    |  2 | CHANNEL_BANDWIDTH_7M },  //( 57.25 MHz -  5.5 MHz) / 0.25 MHz
    { 163 , _AIR    |  1 | CHANNEL_BANDWIDTH_11M }  //( 46.25 MHz -  5.5 MHz) / 0.25 MHz
};
#endif

static FREQCHANNEL m_FreqChannel_I[] =
{
    { 1869, _AIR    | 21 | CHANNEL_BANDWIDTH_8M },    //(471.25 MHz - 4.0 MHz) / 0.25 MHz
    { 1195, _CABLE    | 21 | CHANNEL_BANDWIDTH_8M },  //(303.25 MHz - 4.5 MHz) / 0.25 MHz
    { 909 , _CABLE    | 11 | CHANNEL_BANDWIDTH_7M },  //(231.25 MHz - 4.0 MHz) / 0.25 MHz
    { 687 , _AIR    |  4 | CHANNEL_BANDWIDTH_8M },  //(175.25 MHz - 3.5 MHz) / 0.25 MHz
    { 405 , _CABLE    |  1 | CHANNEL_BANDWIDTH_7M },  //(105.25 MHz - 4.0 MHz) / 0.25 MHz
    { 262 , _CABLE    | 42 | CHANNEL_BANDWIDTH_7M },  //( 69.25 MHz - 3.75MHz) / 0.25 MHz
    { 167 , _AIR    |  1 | CHANNEL_BANDWIDTH_8M }   //( 45.75 MHz - 4.0 MHz) / 0.25 MHz
};

static FREQCHANNEL m_FreqChannel_DK[] =
{
    { 1869, _AIR    | 21 | CHANNEL_BANDWIDTH_8M },    //(471.25 MHz - 4.0 MHz) / 0.25 MHz
    { 1195, _CABLE    | 21 | CHANNEL_BANDWIDTH_8M },  //(303.25 MHz - 4.5 MHz) / 0.25 MHz
    { 909 , _CABLE    | 11 | CHANNEL_BANDWIDTH_7M },  //(231.25 MHz - 4.0 MHz) / 0.25 MHz
    { 687 , _AIR    |  6 | CHANNEL_BANDWIDTH_8M },  //(175.25 MHz - 3.5 MHz) / 0.25 MHz
    { 397 , _CABLE    |  1 | CHANNEL_BANDWIDTH_7M },  //(105.25 MHz - 6.0 MHz) / 0.25 MHz
    { 293 , _AIR    |  3 | CHANNEL_BANDWIDTH_8M },  //( 77.25 MHz - 4.0 MHz) / 0.25 MHz
    { 257 , _CABLE    | 42 | CHANNEL_BANDWIDTH_8M },  //( 69.25 MHz - 5.0 MHz) / 0.25 MHz
    { 179 , _AIR    |  1 | CHANNEL_BANDWIDTH_10M }  //( 49.75 MHz - 5.0 MHz) / 0.25 MHz
};

#if 0 // No need for DVB-T project.
static ROM FREQCHANNEL m_FreqChannel_ChinaDK[] =
{
    { 2413, _AIR    | 25 | CHANNEL_BANDWIDTH_8M },    //(607.25 MHz - 4.0 MHz) / 0.25 MHz
    { 2253, _AIR    | 58 | CHANNEL_BANDWIDTH_8M },  //(567.25 MHz - 4.0 MHz) / 0.25 MHz
    { 1869, _AIR    | 13 | CHANNEL_BANDWIDTH_8M },  //(471.25 MHz - 4.0 MHz) / 0.25 MHz
    { 881 , _CABLE    |  8 | CHANNEL_BANDWIDTH_8M },  //(224.25 MHz - 4.0 MHz) / 0.25 MHz
    { 657 , _AIR    |  6 | CHANNEL_BANDWIDTH_8M },  //(168.25 MHz - 4.0 MHz) / 0.25 MHz
    { 433 , _CABLE    |  1 | CHANNEL_BANDWIDTH_8M },  //(112.25 MHz - 4.0 MHz) / 0.25 MHz
    { 363 , _CABLE    | 40 | CHANNEL_BANDWIDTH_8M },  //( 96.25 MHz - 5.5 MHz) / 0.25 MHz
    { 286 , _AIR    |  4 | CHANNEL_BANDWIDTH_8M },  //( 77.25 MHz - 5.75MHz) / 0.25 MHz
    { 183 , _AIR    |  1 | CHANNEL_BANDWIDTH_8M }   //( 49.75 MHz - 4.0 MHz) / 0.25 MHz
};
#endif

static FREQCHANNEL m_FreqChannel_L[] =
{
    { 1869, _AIR    | 21 | CHANNEL_BANDWIDTH_8M },    //(471.25 MHz - 4.00 MHz) / 0.25 MHz
    { 1200, _CABLE    | 21 | CHANNEL_BANDWIDTH_8M },  //(303.25 MHz - 3.25 MHz) / 0.25 MHz
    { 1182, _CABLE    | 19 | CHANNEL_BANDWIDTH_7M },  //(296.75 MHz - 1.25 MHz) / 0.25 MHz
    { 1158, _CABLE    | 20 | CHANNEL_BANDWIDTH_7M },  //(294.25 MHz - 4.75 MHz) / 0.25 MHz
    { 882 , _CABLE    | 13 | CHANNEL_BANDWIDTH_12M }, //(224.75 MHz - 4.25 MHz) / 0.25 MHz
    { 857 , _AIR    | 10 | CHANNEL_BANDWIDTH_9M },  //(216.00 MHz - 1.75 MHz) / 0.25 MHz
    { 842 , _CABLE    | 12 | CHANNEL_BANDWIDTH_7M },  //(212.75 MHz - 2.25 MHz) / 0.25 MHz
    { 817 , _AIR    |  9 | CHANNEL_BANDWIDTH_7M },  //(208.00 MHz - 3.75 MHz) / 0.25 MHz
    { 802 , _CABLE    | 11 | CHANNEL_BANDWIDTH_8M },  //(200.75 MHz - 0.25 MHz) / 0.25 MHz
    { 761 , _AIR    |  7 | CHANNEL_BANDWIDTH_8M },  //(192.00 MHz - 1.75 MHz) / 0.25 MHz
    { 746 , _CABLE    | 10 | CHANNEL_BANDWIDTH_7M },  //(188.75 MHz - 2.25 MHz) / 0.25 MHz
    { 721 , _AIR    |  6 | CHANNEL_BANDWIDTH_7M },  //(184.00 MHz - 3.75 MHz) / 0.25 MHz
    { 706 , _CABLE    |  9 | CHANNEL_BANDWIDTH_8M },  //(176.75 MHz - 0.25 MHz) / 0.25 MHz
    { 681 , _AIR    |  5 | CHANNEL_BANDWIDTH_7M },  //(176.00 MHz - 5.75 MHz) / 0.25 MHz
    { 451 , _CABLE    |  4 | CHANNEL_BANDWIDTH_12M }, //(116.75 MHz - 4.00 MHz) / 0.25 MHz
    { 352 , _CABLE    |  1 | CHANNEL_BANDWIDTH_8M },  //( 92.75 MHz - 4.75 MHz) / 0.25 MHz
    { 266 , _CABLE    | 42 | CHANNEL_BANDWIDTH_7M },  //( 69.25 MHz - 2.75 MHz) / 0.25 MHz
    { 248 , _AIR    |  4 | CHANNEL_BANDWIDTH_7M },  //( 63.75 MHz - 1.75 MHz) / 0.25 MHz
    { 233 , _AIR    |  3 | CHANNEL_BANDWIDTH_7M },  //( 60.50 MHz - 2.25 MHz) / 0.25 MHz
    { 175 , _AIR    |  1 | CHANNEL_BANDWIDTH_8M }   //( 47.75 MHz - 4.00 MHz) / 0.25 MHz
};

#if 0 // No need for DVB-T project.
/* if priority is cable, you can use the table below.
static ROM FREQCHANNEL m_FreqChannel_M[] =
{
    { 3193, _AIR    | 69 | CHANNEL_BANDWIDTH_6M },   //(801.25 MHz - 3.0 MHz) / 0.25 MHz
    { 2585, _CABLE    |100 | CHANNEL_BANDWIDTH_6M },   //(649.25 MHz - 3.0 MHz) / 0.25 MHz
    { 857 , _CABLE    | 23 | CHANNEL_BANDWIDTH_6M },   //(217.25 MHz - 3.0 MHz) / 0.25 MHz
    { 689 , _CABLE    |  7 | CHANNEL_BANDWIDTH_6M },   //(175.25 MHz - 3.0 MHz) / 0.25 MHz
    { 473 , _CABLE    | 14 | CHANNEL_BANDWIDTH_6M },   //(121.25 MHz - 3.0 MHz) / 0.25 MHz
    { 353 , _CABLE    | 95 | CHANNEL_BANDWIDTH_6M },   //( 91.25 MHz - 3.0 MHz) / 0.25 MHz
    { 297 , _CABLE    |  5 | CHANNEL_BANDWIDTH_6M },   //( 77.25 MHz - 3.0 MHz) / 0.25 MHz
    { 285 , _CABLE    |  1 | CHANNEL_BANDWIDTH_6M },   //( 73.25 MHz - 2.0 MHz) / 0.25 MHz
    { 209 , _CABLE    |  2 | CHANNEL_BANDWIDTH_6M }    //( 55.25 MHz - 3.0 MHz) / 0.25 MHz
};
*/
static ROM FREQCHANNEL m_FreqChannel_M[] =
{
    { 1873, _AIR    | 14 | CHANNEL_BANDWIDTH_6M },   //(471.25 MHz - 3.0 MHz) / 0.25 MHz
    { 857 , _CABLE    | 23 | CHANNEL_BANDWIDTH_6M },   //(217.25 MHz - 3.0 MHz) / 0.25 MHz
    { 689 , _AIR    |  7 | CHANNEL_BANDWIDTH_6M },   //(175.25 MHz - 3.0 MHz) / 0.25 MHz
    { 473 , _CABLE    | 14 | CHANNEL_BANDWIDTH_6M },   //(121.25 MHz - 3.0 MHz) / 0.25 MHz
    { 353 , _CABLE    | 95 | CHANNEL_BANDWIDTH_6M },   //( 91.25 MHz - 3.0 MHz) / 0.25 MHz
    { 297 , _AIR    |  5 | CHANNEL_BANDWIDTH_6M },   //( 77.25 MHz - 3.0 MHz) / 0.25 MHz
    { 285 , _CABLE    |  1 | CHANNEL_BANDWIDTH_6M },   //( 73.25 MHz - 2.0 MHz) / 0.25 MHz
    { 209 , _AIR    |  2 | CHANNEL_BANDWIDTH_6M }    //( 55.25 MHz - 3.0 MHz) / 0.25 MHz
};
#endif

typedef struct
{
    WORD wChannel;
    WORD wFrequency;
} CHANNELFREQ;

static CHANNELFREQ m_ChannelFreq_UHF_BGIDKL[] = //BG,I,DK,L
{
    { 21 | CHANNEL_BANDWIDTH_8M, 1885 }, // 471.25 MHz / 0.25 MHz
};

static ROM CHANNELFREQ m_ChannelFreq_VHF_BG[] =
{
    { 17 | CHANNEL_BANDWIDTH_9M, 733 }, // 183.25 MHz / 0.25 MHz
    { 16 | CHANNEL_BANDWIDTH_0M, 701 }, // 175.25 MHz / 0.25 MHz
    { 15 | CHANNEL_BANDWIDTH_0M, 329 }, //  82.25 MHz / 0.25 MHz
    { 14 | CHANNEL_BANDWIDTH_0M, 249 }, //  62.25 MHz / 0.25 MHz
    { 13 | CHANNEL_BANDWIDTH_0M, 215 }, //  53.75 MHz / 0.25 MHz
    {  5 | CHANNEL_BANDWIDTH_7M, 701 }, // 175.25 MHz / 0.25 MHz
    {  2 | CHANNEL_BANDWIDTH_7M, 193 }, //  48.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_0M, 181 }  //  45.25 MHz / 0.25 MHz
};

#if 0 // No need for DVB-T project.
static CHANNELFREQ m_ChannelFreq_BB[] =
{
    { 20 | CHANNEL_BANDWIDTH_7M, 1885 }, // 471.25 MHz / 0.25MHz
    { 18 | CHANNEL_BANDWIDTH_7M, 981  }, // 245.25 MHz / 0.25MHz
    { 17 | CHANNEL_BANDWIDTH_0M, 941  }, // 235.25 MHz / 0.25MHz
    {  8 | CHANNEL_BANDWIDTH_7M, 701  }, // 175.25 MHz / 0.25MHz
    {  7 | CHANNEL_BANDWIDTH_0M, 553  }, // 138.25 MHz / 0.25MHz
    {  5 | CHANNEL_BANDWIDTH_7M, 381  }, //  95.25 MHz / 0.25MHz
    {  4 | CHANNEL_BANDWIDTH_0M, 345  }, //  86.25 MHz / 0.25MHz
    {  2 | CHANNEL_BANDWIDTH_7M, 229  }, //  57.25 MHz / 0.25MHz
    {  1 | CHANNEL_BANDWIDTH_0M, 185  }  //  46.25 MHz / 0.25MHz
};
#endif

static CHANNELFREQ m_ChannelFreq_VHF_I[] =
{
    { 14 | CHANNEL_BANDWIDTH_8M, 1021 }, // 255.25 MHz / 0.25 MHz
    { 13 | CHANNEL_BANDWIDTH_0M, 991  }, // 247.75 MHz / 0.25 MHz
    {  4 | CHANNEL_BANDWIDTH_8M, 701  }, // 175.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_8M, 183  }  //  45.75 MHz / 0.25 MHz
};

static CHANNELFREQ m_ChannelFreq_VHF_DK[] =
{
    { 18 | CHANNEL_BANDWIDTH_8M, 673 }, // 168.25 MHz / 0.25 MHz
    { 16 | CHANNEL_BANDWIDTH_8M, 309 }, //  77.25 MHz / 0.25 MHz
    { 13 | CHANNEL_BANDWIDTH_8M, 199 }, //  49.75 MHz / 0.25 MHz
    {  6 | CHANNEL_BANDWIDTH_8M, 701 }, // 175.25 MHz / 0.25 MHz
    {  3 | CHANNEL_BANDWIDTH_8M, 309 }, //  77.25 MHz / 0.25 MHz
    {  2 | CHANNEL_BANDWIDTH_0M, 237 }, //  59.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_0M, 199 }  //  49.75 MHz / 0.25 MHz
};

#if 0 // No need for DVB-T project.
static CHANNELFREQ m_ChannelFreq_ChinaDK[] =
{
    { 58 | CHANNEL_BANDWIDTH_8M, 2269 }, // 567.25 MHz / 0.25 MHz
    { 25 | CHANNEL_BANDWIDTH_8M, 2429 }, // 607.25 MHz / 0.25 MHz
    { 13 | CHANNEL_BANDWIDTH_8M, 1885 }, // 471.25 MHz / 0.25 MHz
    {  6 | CHANNEL_BANDWIDTH_8M, 673  }, // 168.25 MHz / 0.25 MHz
    {  4 | CHANNEL_BANDWIDTH_8M, 309  }, //  77.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_8M, 199  }  //  49.75 MHz / 0.25 MHz
};
#endif

static CHANNELFREQ m_ChannelFreq_VHF_L[] =
{
    { 14 | CHANNEL_BANDWIDTH_8M, 765 }, // 191.25 MHz / 0.25MHz
    { 13 | CHANNEL_BANDWIDTH_0M, 757 }, // 189.25 MHz / 0.25MHz
    { 11 | CHANNEL_BANDWIDTH_8M, 701 }, // 175.25 MHz / 0.25MHz
    {  5 | CHANNEL_BANDWIDTH_8M, 704 }, // 176.00 MHz / 0.25MHz
    {  4 | CHANNEL_BANDWIDTH_0M, 255 }, //  63.75 MHz / 0.25MHz
    {  3 | CHANNEL_BANDWIDTH_0M, 242 }, //  60.50 MHz / 0.25MHz
    {  1 | CHANNEL_BANDWIDTH_8M, 191 }  //  47.75 MHz / 0.25MHz
};

#if 0 // No need for DVB-T project.
static ROM CHANNELFREQ m_ChannelFreq_M[] =
{
    { 14 | CHANNEL_BANDWIDTH_6M, 1885 },  // 471.25 MHz / 0.25MHz
    {  7 | CHANNEL_BANDWIDTH_6M, 701  },  // 175.25 MHz / 0.25MHz
    {  5 | CHANNEL_BANDWIDTH_6M, 309  },  //  77.25 MHz / 0.25MHz
    {  2 | CHANNEL_BANDWIDTH_6M, 221  }   //  55.25 MHz / 0.25MHz
};
#endif

static CHANNELFREQ m_ChannelFreq_Cable_BGIDK[] =
{
    { 42 | CHANNEL_BANDWIDTH_7M, 277  }, //  69.25 MHz / 0.25 MHz
    { 21 | CHANNEL_BANDWIDTH_8M, 1213 }, // 303.25 MHz / 0.25 MHz
    { 11 | CHANNEL_BANDWIDTH_7M, 925  }, // 231.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_7M, 421  }  // 105.25 MHz / 0.25 MHz
};

#if 0 // No need for DVB-T project.
static CHANNELFREQ m_ChannelFreq_Cable_BB[] =
{
    { 21 | CHANNEL_BANDWIDTH_7M, 1213 }, // 303.25 MHz / 0.25 MHz
    { 11 | CHANNEL_BANDWIDTH_7M, 925  }, // 231.25 MHz / 0.25 MHz
    {  2 | CHANNEL_BANDWIDTH_7M, 449  }  // 112.25 MHz / 0.25 MHz
};
#endif

#if 0 // No need for DVB-T project.
static CHANNELFREQ m_ChannelFreq_Cable_ChinaDK[] =
{
    { 39 | CHANNEL_BANDWIDTH_8M, 353 }, //  88.25 MHz / 0.25 MHz
    {  8 | CHANNEL_BANDWIDTH_8M, 897 }, // 224.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_8M, 449 }  // 112.25 MHz / 0.25 MHz
};
#endif

static CHANNELFREQ m_ChannelFreq_Cable_L[] =
{
    { 42 | CHANNEL_BANDWIDTH_7M,  277  }, //  69.25 MHz / 0.25 MHz
    { 21 | CHANNEL_BANDWIDTH_8M,  1213 }, // 303.25 MHz / 0.25 MHz
    { 20 | CHANNEL_BANDWIDTH_0M,  1177 }, // 294.25 MHz / 0.25 MHz
    {  4 | CHANNEL_BANDWIDTH_12M, 467  }, // 116.75 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_8M,  371  }  //  92.75 MHz / 0.25 MHz
};

#if 0 // No need for DVB-T project.
static CHANNELFREQ m_ChannelFreq_Cable_M[] =
{
    {100 | CHANNEL_BANDWIDTH_6M, 2597 },  // 649.25 MHz / 0.25 MHz
    { 95 | CHANNEL_BANDWIDTH_6M, 365  },  //  91.25 MHz / 0.25 MHz
    { 23 | CHANNEL_BANDWIDTH_6M, 869  },  // 217.25 MHz / 0.25 MHz
    { 14 | CHANNEL_BANDWIDTH_6M, 485  },  // 121.25 MHz / 0.25 MHz
    {  7 | CHANNEL_BANDWIDTH_6M, 701  },  // 175.25 MHz / 0.25 MHz
    {  5 | CHANNEL_BANDWIDTH_6M, 309  },  //  77.25 MHz / 0.25 MHz
    {  2 | CHANNEL_BANDWIDTH_6M, 221  },  //  55.25 MHz / 0.25 MHz
    {  1 | CHANNEL_BANDWIDTH_6M, 293  }   //  73.25 MHz / 0.25 MHz
};
#endif

//****************************************************************************
// Private functions of this file.
//****************************************************************************
static BYTE GetChannelFreqTable(CHANNELFREQ ROM ** ppChannelFreq, MEDIUM eMedium, BYTE cChannel);
static BYTE GetFreqChannelTable(FREQCHANNEL ROM ** ppFreqChannel);
static WORD ConvertPLLtoCompressedFrequency(WORD wPLLData);
static WORD ConvertCompressedFrequencytoPLL(WORD wFreq);

//****************************************************************************
// Start of public implementation
//****************************************************************************

void msAPI_CFT_InitChannelFreqTable(void)
{
    // need touch.
}

/******************************************************************************/
/// -This function will check is medium and channel valid
/// @param eMedium \b IN: Medium
/// - @see MEDIUM
/// @param cChannelNumber \b IN: Channel Number
/// @return BOOLEAN:
/// - TRUE: Default is valid
/// - FALSE: NO
/******************************************************************************/
BOOLEAN msAPI_CFT_IsValidMediumAndChannel(MEDIUM eMedium, BYTE cChannelNumber)
{
    BYTE cMinChannel, cMaxChannel;

    msAPI_CFT_GetMinMaxChannel(eMedium, &cMinChannel, &cMaxChannel);

    if( cChannelNumber < cMinChannel || cMaxChannel < cChannelNumber )
        return FALSE;

    return TRUE;
}

/******************************************************************************/
/// -This function will Get Medium type
/// @param wChannelPLLData \b IN: Channel PLL Data
/// @return MEDIUM: Medium type
/// - @see MEDIUM
/******************************************************************************/
MEDIUM msAPI_CFT_GetMedium(WORD wChannelPLLData)
{
    BYTE i;
    BYTE cTableSize;
    FREQCHANNEL * pFreqChannel;
    BYTE cLeadChannelIndex;
    WORD wCompressedFrequency;
    MEDIUM eMedium;

    wCompressedFrequency = ConvertPLLtoCompressedFrequency(wChannelPLLData);
    cTableSize = GetFreqChannelTable(&pFreqChannel);

      cLeadChannelIndex = 0;

      for(i=0; i < cTableSize; i++)
    {
        if( wCompressedFrequency >= pFreqChannel[i].wFrequency )
        {
            cLeadChannelIndex = i;
            break;
        }
    }

    if(i == cTableSize)
    {
        debugChannelFreqTablePrint("Hi. correct me.",0);
        return MEDIUM_AIR;
    }

    if( (pFreqChannel[cLeadChannelIndex].wChannel & MEDIUM_MASK) == _CABLE )
        eMedium = MEDIUM_CABLE;
    else
        eMedium= MEDIUM_AIR;

    return eMedium;
}

/******************************************************************************/
/// -This function will Get Channel Number
/// @param wChannelPLLData \b IN: wChannelPLLData
/// @return BYTE: Channel Number
/******************************************************************************/
BYTE msAPI_CFT_GetChannelNumber(WORD wChannelPLLData)
{
    FREQCHANNEL * pFreqChannel;
    BYTE i;
    BYTE cTableSize;
    WORD wBandWidth;
    BYTE cChannelNumber;
    BYTE cMinChannel, cMaxChannel;
    BYTE cLeadChannelIndex;
    WORD wCompressedFrequency;
    MEDIUM eMedium;

    wCompressedFrequency = ConvertPLLtoCompressedFrequency(wChannelPLLData);

    cTableSize = GetFreqChannelTable(&pFreqChannel);

      cLeadChannelIndex = 0;

    for(i=0; i < cTableSize; i++)
    {
        if( wCompressedFrequency >= pFreqChannel[i].wFrequency )
        {
            cLeadChannelIndex = i;
            break;
        }
    }

    if(i == cTableSize)
    {
        debugChannelFreqTablePrint("Hello. correct me.",0);
        return 1;
    }

    switch( (pFreqChannel[cLeadChannelIndex].wChannel & CHANNEL_BANDWIDTH_MASK) )
    {
    case CHANNEL_BANDWIDTH_6M:
        wBandWidth = 24;    // 6MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_7M:
        wBandWidth = 28;    // 7MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_8M:
        wBandWidth = 32;    // 8MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_9M:
        wBandWidth = 36;    // 9MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_10M:
        wBandWidth = 40;    // 10MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_11M:
        wBandWidth = 44;    // 11MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_12M:
        wBandWidth = 48;    // 12MHz/0.25MHz;
        break;
    default:
        wBandWidth = 32;    // 8MHz/0.25MHz;
        break;
    }

    if( (pFreqChannel[cLeadChannelIndex].wChannel & MEDIUM_MASK) == _CABLE )
        eMedium = MEDIUM_CABLE;
    else
        eMedium = MEDIUM_AIR;

    cChannelNumber = ( (BYTE)(pFreqChannel[cLeadChannelIndex].wChannel & LEAD_CHANNEL_MASK) + ((wCompressedFrequency - pFreqChannel[cLeadChannelIndex].wFrequency) / wBandWidth) );

    msAPI_CFT_GetMinMaxChannel(eMedium, &cMinChannel, &cMaxChannel);

    if( cChannelNumber < cMinChannel )
    {
        cChannelNumber = cMinChannel;
    }
    else if( cChannelNumber > cMaxChannel )
    {
        cChannelNumber = cMaxChannel;
    }

    return cChannelNumber;
}

/******************************************************************************/
/// -This function will Get Channel PLL Data
/// @param eMedium \b IN: Medium type
/// -@see MEDIUM
/// @param cChannel \b IN: Channel
/// @return WORD: PLL data
/******************************************************************************/
WORD msAPI_CFT_GetChannelPLLData(MEDIUM eMedium, BYTE cChannel)
{
    CHANNELFREQ * pChannelFreq = 0;
    BYTE cTableSize;
    BYTE i;
    BYTE cLeadChannelIndex = 0;
    BYTE cLeadChannel;
    WORD wBandWidth;
    BYTE cMinChannel, cMaxChannel;
    WORD wCompressedFrequency;

    msAPI_CFT_GetMinMaxChannel(eMedium, &cMinChannel, &cMaxChannel);

    if(cChannel < cMinChannel)
        cChannel = cMinChannel;
    else if(cChannel > cMaxChannel)
        cChannel = cMaxChannel;

    cTableSize = GetChannelFreqTable(&pChannelFreq, eMedium, cChannel);

    for(i=0; i < cTableSize; i++)
    {
        if( cChannel >= (BYTE)(pChannelFreq[i].wChannel & LEAD_CHANNEL_MASK) )
        {
            cLeadChannelIndex = i;
            break;
        }
    }

    if(i == cTableSize)
    {
        cLeadChannelIndex = cTableSize - 1;
        cChannel = (BYTE)(pChannelFreq[cLeadChannelIndex].wChannel & LEAD_CHANNEL_MASK);
    }

    cLeadChannel = (BYTE)(pChannelFreq[cLeadChannelIndex].wChannel & LEAD_CHANNEL_MASK);

    switch( (pChannelFreq[cLeadChannelIndex].wChannel & CHANNEL_BANDWIDTH_MASK) )
    {
    case CHANNEL_BANDWIDTH_6M:
        wBandWidth = 24;    // 6MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_7M:
        wBandWidth = 28;    // 7MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_8M:
        wBandWidth = 32;    // 8MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_9M:
        wBandWidth = 36;    // 9MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_10M:
        wBandWidth = 40;    // 10MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_11M:
        wBandWidth = 44;    // 11MHz/0.25MHz;
        break;
    case CHANNEL_BANDWIDTH_12M:
        wBandWidth = 48;    // 12MHz/0.25MHz;
        break;
    default:
        wBandWidth = 32;    // 8MHz/0.25MHz;
        break;
    }

    wCompressedFrequency = (pChannelFreq[cLeadChannelIndex].wFrequency + (cChannel - cLeadChannel) * wBandWidth);
    return ConvertCompressedFrequencytoPLL(wCompressedFrequency);
}

/******************************************************************************/
/// -This function will Get Min and Max Channel
/// @param eMedium \b IN: Medium type
/// -@see MEDIUM
/// @param pcMin \b IN: pointer to Min
/// @param pcMax \b IN: pointer to Max
/******************************************************************************/
void msAPI_CFT_GetMinMaxChannel(MEDIUM eMedium, BYTE * pcMin, BYTE * pcMax)
{
    BYTE cMin =0;
    BYTE cMax =0;

    if(eMedium == MEDIUM_CABLE)
    {
        switch( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
        {
        case E_AUDIOSTANDARD_BG:
            #if 0 // No need for DVB-T project.
            if ( IS_RF_TABLE_ENABLED == TRUE )
            {
                cMin = 2;
                cMax = 44;
            }
            else
            #endif
            {
                cMin = 1;
                cMax = 47;
            }
            break;

        case E_AUDIOSTANDARD_I:
            cMin = 1;
            cMax = 47;
            break;
        case E_AUDIOSTANDARD_DK:
            #if 0 // No need for DVB-T project.
            if ( IS_RF_TABLE_ENABLED == TRUE )
            {
                cMin = 1;
                cMax = 42;
            }
            else
            #endif
            {
                cMin = 1;
                cMax = 47;
            }
            break;
        case E_AUDIOSTANDARD_L:
            cMin = 1;
            cMax = 47;
            break;
#if 0 // No need for DVB-T project.
        case E_AUDIOSTANDARD_M:
            cMin = 1;
            cMax = 125;
            break;
#endif
        default:
            break;
        }
    }
    else
    {
        switch( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(msAPI_AUD_GetAudioStandard()) )
        {
        case E_AUDIOSTANDARD_BG:
            #if 0 // No need for DVB-T project.
            if ( IS_RF_TABLE_ENABLED == TRUE )
            {
                cMin = 1;
                cMax = 75;
            }
            else
            #endif
            {
                cMin = 1;
                cMax = 69;
            }
            break;
        case E_AUDIOSTANDARD_I:
            cMin = 1;
            cMax = 69;
            break;
        case E_AUDIOSTANDARD_DK:
            #if 0 // No need for DVB-T project.
            if ( IS_RF_TABLE_ENABLED == TRUE )
            {
                cMin = 1;
                cMax = 62;
            }
            else
            #endif
            {
                cMin = 1;
                cMax = 69;
            }
            break;
        case E_AUDIOSTANDARD_L:
            cMin = 1;
            cMax = 69;
            break;
        #if 0 // No need for DVB-T project.
        case E_AUDIOSTANDARD_M:
            cMin = 2;
            cMax = 83;
            break;
        #endif
        default:
            break;
        }
    }

    if( pcMin != NULL )
        *pcMin = cMin;
    if( pcMax != NULL )
        *pcMax = cMax;
}

#if 1 //
/******************************************************************************/
/// -This function will Get VHF Low Min PLL
/// @return WORD: PLL data
/******************************************************************************/
WORD msAPI_CFT_VHFLowMinPLL(void)
{
#if (ENABLE_DVB)
extern MEMBER_COUNTRY msAPI_CM_GetCountry(void);

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    if (E_UK == msAPI_CM_GetCountry())
        return (WORD) (((UK_MIN_ATV_FREQ ) * 10) / 625);        // 62.5KHz
    else
        return (WORD) (((VHF_LOWMIN_FREQ - 3000L) * 10) / 625);        // 62.5KHz

#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    if(E_UK == msAPI_CM_GetCountry())
        return (WORD) ((UK_MIN_ATV_FREQ ) / 50);             // 50KHz
    else
        return (WORD) ((VHF_LOWMIN_FREQ - 3000L) / 50);             // 50KHz
#else
    if(E_UK == msAPI_CM_GetCountry())
        return (WORD) (((UK_MIN_ATV_FREQ ) * 100) / 3125);     // 31.25KHz
    else
        return (WORD) (((VHF_LOWMIN_FREQ - 3000L) * 100) / 3125);     // 31.25KHz
#endif // TN_FREQ_STEP
#else
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (WORD) (((VHF_LOWMIN_FREQ - 3000L) * 10) / 625);        // 62.5KHz
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (WORD) ((VHF_LOWMIN_FREQ - 3000L) / 50);             // 50KHz
#else
    return (WORD) (((VHF_LOWMIN_FREQ - 3000L) * 100) / 3125);     // 31.25KHz
#endif // TN_FREQ_STEP
#endif

}
#else
/******************************************************************************/
/// -This function will Get VHF Low Min PLL
/// @return WORD: PLL data
/******************************************************************************/
WORD msAPI_CFT_VHFLowMinPLL(void)
{
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (WORD) (((VHF_LOWMIN_FREQ - 3000L) * 10) / 625);        // 62.5KHz
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (WORD) ((VHF_LOWMIN_FREQ - 3000L) / 50);             // 50KHz
#else
    return (WORD) (((VHF_LOWMIN_FREQ - 3000L) * 100) / 3125);     // 31.25KHz
#endif // TN_FREQ_STEP
}
#endif

/******************************************************************************/
/// -This function will Get VHF High Min PLL
/// @return WORD: PLL data
/******************************************************************************/
WORD msAPI_CFT_VHFHighMinPLL(void)
{
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (WORD) (((VHF_LOWMAX_FREQ + (VHF_HIGHMIN_FREQ - VHF_LOWMAX_FREQ)/2) * 10) / 625);        // 62.5KHz
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (WORD) ((VHF_LOWMAX_FREQ + (VHF_HIGHMIN_FREQ - VHF_LOWMAX_FREQ)/2) / 50);                 // 50KHz
#else
    return (WORD) (((VHF_LOWMAX_FREQ + (VHF_HIGHMIN_FREQ - VHF_LOWMAX_FREQ)/2) * 100) / 3125);     // 31.25KHz
#endif // TN_FREQ_STEP
}

/******************************************************************************/
/// -This function will Get VHF High Min PLL
/// @return WORD: PLL data
/******************************************************************************/
WORD msAPI_CFT_UHFMinPLL(void)
{
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (WORD) (((VHF_HIGHMAX_FREQ + (UHF_MIN_FREQ - VHF_HIGHMAX_FREQ)/2) * 10) / 625);        // 62.5KHz
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (WORD) ((VHF_HIGHMAX_FREQ + (UHF_MIN_FREQ - VHF_HIGHMAX_FREQ)/2) / 50);                 // 50KHz
#else
    return (WORD) (((VHF_HIGHMAX_FREQ + (UHF_MIN_FREQ - VHF_HIGHMAX_FREQ)/2) * 100) / 3125);     // 31.25KHz
#endif // TN_FREQ_STEP
}

/******************************************************************************/
/// -This function will Get UHF MAX PLL
/// @return WORD: PLL data
/******************************************************************************/
WORD msAPI_CFT_UHFMaxPLL(void)
{
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (WORD) (((UHF_MAX_FREQ + 4000L) * 10) / 625);    // 62.5KHz
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (WORD) ((UHF_MAX_FREQ + 4000L) / 50);             // 50KHz
#else
    return (WORD) (((UHF_MAX_FREQ + 4000L) * 100) / 3125);     // 31.25KHz
#endif // TN_FREQ_STEP
}

/******************************************************************************/
/// -This function will Convert PLL to Integer Of Frequency
/// @param wPLL \b IN: PLL
/// @return WORD: Integer Of Frequency
/******************************************************************************/
WORD msAPI_CFT_ConvertPLLtoIntegerOfFrequency(WORD wPLL)
{
    WORD wIntegerOfFreq;

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    wIntegerOfFreq = (WORD)( ( (DWORD)wPLL*625/10 )/1000 );
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    wIntegerOfFreq = (WORD)( ( (DWORD)wPLL*50 )/1000 );
#else
    wIntegerOfFreq = (WORD)( ( (DWORD)wPLL*3125/100 )/1000 );
#endif // TN_FREQ_STEP

    return wIntegerOfFreq;
}

/******************************************************************************/
/// -This function will Convert PLL to Fraction Of Frequency
/// @param wPLL \b IN: PLL
/// @return WORD: Fraction Of Frequency
/******************************************************************************/
WORD msAPI_CFT_ConvertPLLtoFractionOfFrequency(WORD wPLL)
{
    WORD wFractionOfFreq;

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    wFractionOfFreq = (WORD)( ( (DWORD)wPLL*625/10 )%1000 );
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    wFractionOfFreq = (WORD)( ( (DWORD)wPLL*50 )%1000 );
#else
    wFractionOfFreq = (WORD)( ( (DWORD)wPLL*3125/100 )%1000 );
#endif // TN_FREQ_STEP

    return wFractionOfFreq;
}

/******************************************************************************/
/// -This function will Convert Frequncy To PLL
/// @param wIntegerOfFreq \b IN: Integer Of Frequency
/// @param wFractionOfFreq \b IN: Fraction Of Frequency
/// @return WORD: Tuner PLL
/******************************************************************************/
WORD msAPI_CFT_ConvertFrequncyToPLL(WORD wIntegerOfFreq, WORD wFractionOfFreq)
{
    WORD wTunerPLL;
    WORD wCompensationForFraction;

    if( wFractionOfFreq < 10 )
        wCompensationForFraction = 100;
    else if( wFractionOfFreq < 100 )
        wCompensationForFraction = 10;
    else if( wFractionOfFreq < 1000 )
        wCompensationForFraction = 1;
    else if( wFractionOfFreq < 10000 )
    {
        wFractionOfFreq = wFractionOfFreq / 10;
        wCompensationForFraction = 1;
    }
    else
    {
        wFractionOfFreq = wFractionOfFreq / 100;
        wCompensationForFraction = 1;
    }

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    wTunerPLL = (WORD) (((((DWORD)wIntegerOfFreq * 1000)+((DWORD)wFractionOfFreq * wCompensationForFraction)) * 10) / 625);
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    wTunerPLL = (WORD) (((((DWORD)wIntegerOfFreq * 1000)+((DWORD)wFractionOfFreq * wCompensationForFraction)) * 1) / 50);
#else
    wTunerPLL = (WORD) (((((DWORD)wIntegerOfFreq * 1000)+((DWORD)wFractionOfFreq * wCompensationForFraction)) * 100) / 3125);
#endif // TN_FREQ_STEP

    return wTunerPLL;
}

//*****************************************************************************
// Start of private implementation
//****************************************************************************

static BYTE GetChannelFreqTable(CHANNELFREQ ROM ** ppChannelFreq, MEDIUM eMedium, BYTE cChannel)
{
    AUDIOSTANDARD_TYPE eAudioStandard;
    BYTE cTableSize =0;

    eAudioStandard = msAPI_AUD_GetAudioStandard();

    if(eMedium == MEDIUM_AIR)
    {
        if( cChannel >= CCIR_UHF_FIRSTCHANNEL &&
            eAudioStandard != E_AUDIOSTANDARD_M_BTSC &&
            eAudioStandard != E_AUDIOSTANDARD_M_A2 &&
            eAudioStandard != E_AUDIOSTANDARD_M_EIA_J &&
            IS_RF_TABLE_ENABLED == FALSE )
        {
            if( ppChannelFreq != NULL )
                *ppChannelFreq = m_ChannelFreq_UHF_BGIDKL;
            cTableSize = sizeof(m_ChannelFreq_UHF_BGIDKL)/sizeof(CHANNELFREQ);
        }
        else
        {
            switch( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(eAudioStandard) )
            {
            case E_AUDIOSTANDARD_BG:
                #if 0 // No need for DVB-T project.
                if ( IS_RF_TABLE_ENABLED == TRUE )
                {
                    if( ppChannelFreq != NULL )
                        *ppChannelFreq = m_ChannelFreq_BB;

                    cTableSize = sizeof(m_ChannelFreq_BB)/sizeof(CHANNELFREQ);
                }
                else
                #endif
                {
                    if( ppChannelFreq != NULL )
                        *ppChannelFreq = m_ChannelFreq_VHF_BG;
                    cTableSize = sizeof(m_ChannelFreq_VHF_BG)/sizeof(CHANNELFREQ);
                }
                break;

            case E_AUDIOSTANDARD_I:
                if( ppChannelFreq != NULL )
                    *ppChannelFreq = m_ChannelFreq_VHF_I;
                cTableSize = sizeof(m_ChannelFreq_VHF_I)/sizeof(CHANNELFREQ);
                break;

            case E_AUDIOSTANDARD_DK:
                #if 0 // No need for DVB-T project.
                if ( IS_RF_TABLE_ENABLED == TRUE )
                {
                    if( ppChannelFreq != NULL )
                        *ppChannelFreq = m_ChannelFreq_ChinaDK;

                    cTableSize = sizeof(m_ChannelFreq_ChinaDK)/sizeof(CHANNELFREQ);
                }
                else
                #endif
                {
                    if( ppChannelFreq != NULL )
                        *ppChannelFreq = m_ChannelFreq_VHF_DK;
                    cTableSize = sizeof(m_ChannelFreq_VHF_DK)/sizeof(CHANNELFREQ);
                }
                break;

            case E_AUDIOSTANDARD_L:
                if( ppChannelFreq != NULL )
                    *ppChannelFreq = m_ChannelFreq_VHF_L;
                cTableSize = sizeof(m_ChannelFreq_VHF_L)/sizeof(CHANNELFREQ);
                break;
#if 0 // No need for DVB-T project.
            case E_AUDIOSTANDARD_M:
                if( ppChannelFreq != NULL )
                    *ppChannelFreq = m_ChannelFreq_M;
                cTableSize = sizeof(m_ChannelFreq_M)/sizeof(CHANNELFREQ);
                break;
#endif
            default:
                break;
            }
        }
    }
    else
    {
        switch( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(eAudioStandard) )
        {
        case E_AUDIOSTANDARD_BG:
            #if 0 // No need for DVB-T project.
            if ( IS_RF_TABLE_ENABLED == TRUE )
            {
                if( ppChannelFreq != NULL )
                    *ppChannelFreq = m_ChannelFreq_Cable_BB;
                cTableSize = sizeof(m_ChannelFreq_Cable_BB)/sizeof(CHANNELFREQ);
            }
            else
            #endif
            {
                if ( ppChannelFreq != NULL )
                {
                    *ppChannelFreq = m_ChannelFreq_Cable_BGIDK;
                }

                cTableSize = sizeof(m_ChannelFreq_Cable_BGIDK)/sizeof(CHANNELFREQ);
            }
            break;

        case E_AUDIOSTANDARD_I:
            if( ppChannelFreq != NULL )
                *ppChannelFreq = m_ChannelFreq_Cable_BGIDK;
            cTableSize = sizeof(m_ChannelFreq_Cable_BGIDK)/sizeof(CHANNELFREQ);
            break;

        case E_AUDIOSTANDARD_DK:
            #if 0 // No need for DVB-T project.
            if ( IS_RF_TABLE_ENABLED == TRUE )
            {
                if( ppChannelFreq != NULL )
                    *ppChannelFreq = m_ChannelFreq_Cable_ChinaDK;
                cTableSize = sizeof(m_ChannelFreq_Cable_ChinaDK)/sizeof(CHANNELFREQ);
            }
            else
            #endif
            {
                if( ppChannelFreq != NULL )
                    *ppChannelFreq = m_ChannelFreq_Cable_BGIDK;
                cTableSize = sizeof(m_ChannelFreq_Cable_BGIDK)/sizeof(CHANNELFREQ);
            }
            break;

        case E_AUDIOSTANDARD_L:
            if( ppChannelFreq != NULL )
                *ppChannelFreq = m_ChannelFreq_Cable_L;
            cTableSize = sizeof(m_ChannelFreq_Cable_L)/sizeof(CHANNELFREQ);
            break;
#if 0 // No need for DVB-T project.
        case E_AUDIOSTANDARD_M:
            if( ppChannelFreq != NULL )
                *ppChannelFreq = m_ChannelFreq_Cable_M;
            cTableSize = sizeof(m_ChannelFreq_Cable_M)/sizeof(CHANNELFREQ);
            break;
#endif
        default:
            break;
        }
    }

    return cTableSize;
}

static BYTE GetFreqChannelTable(FREQCHANNEL ROM ** ppFreqChannel)
{
    AUDIOSTANDARD_TYPE eAudioStandard;
    BYTE cTableSize;

    eAudioStandard = msAPI_AUD_GetAudioStandard();

    switch( MApi_AUDIO_SIF_ConvertToBasicAudioStandard(eAudioStandard) )
    {
    case E_AUDIOSTANDARD_BG:
        #if 0 // No need for DVB-T project.
        if ( IS_RF_TABLE_ENABLED == TRUE )
        {
            *ppFreqChannel = m_FreqChannel_BB;
            cTableSize = sizeof(m_FreqChannel_BB)/sizeof(FREQCHANNEL);
        }
        else
        #endif
        {
            *ppFreqChannel = m_FreqChannel_BG;
            cTableSize = sizeof(m_FreqChannel_BG)/sizeof(FREQCHANNEL);
        }
        break;

    case E_AUDIOSTANDARD_I:
        *ppFreqChannel = m_FreqChannel_I;
        cTableSize = sizeof(m_FreqChannel_I)/sizeof(FREQCHANNEL);
        break;

    case E_AUDIOSTANDARD_DK:
        #if 0 // No need for DVB-T project.
        if ( IS_RF_TABLE_ENABLED == TRUE )
        {
            *ppFreqChannel = m_FreqChannel_ChinaDK;
            cTableSize = sizeof(m_FreqChannel_DK)/sizeof(FREQCHANNEL);
        }
        else
        #endif
        {
            *ppFreqChannel = m_FreqChannel_DK;
            cTableSize = sizeof(m_FreqChannel_DK)/sizeof(FREQCHANNEL);
        }
        break;

    case E_AUDIOSTANDARD_L:
        *ppFreqChannel = m_FreqChannel_L;
        cTableSize = sizeof(m_FreqChannel_L)/sizeof(FREQCHANNEL);
        break;
#if 0 // No need for DVB-T project.
    case E_AUDIOSTANDARD_M:
        *ppFreqChannel = m_FreqChannel_M;
        cTableSize = sizeof(m_FreqChannel_M)/sizeof(FREQCHANNEL);
        break;
#endif

    default:
        *ppFreqChannel = m_FreqChannel_BG;
        cTableSize = sizeof(m_FreqChannel_BG)/sizeof(FREQCHANNEL);
        break;
    }

    return cTableSize;
}

static WORD ConvertPLLtoCompressedFrequency(WORD wPLLData)
{
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (wPLLData / 4);
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (wPLLData / 5);
#else
    return (wPLLData / 8);
#endif // TN_FREQ_STEP
}

static WORD ConvertCompressedFrequencytoPLL(WORD wCompressedFrequency)
{
#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    return (wCompressedFrequency * 4);
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    return (wCompressedFrequency * 5);
#else
    return (wCompressedFrequency * 8);
#endif // TN_FREQ_STEP
}
