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

#if ENABLE_DTV
#include <string.h>
#include "datatype.h"

#include "MApp_GlobalSettingSt.h"

#include "msAPI_FreqTableCommon.h"

#include "msAPI_FreqTableDTV.h"

#include "msAPI_DTVSystem.h"

#define ITALY_USE_EUROPEAN_VHF FALSE
#define FREQ_TABLE_DEG(x)        //x
// ================ Channel Frequency Table ============================
// As you see tables below, channel frequency data is divided by 0.25MHz
// because it is too big to fit in 16bit data type(unsigned int).
// Otherwide it takes 32bit data type(unsigned long).
// This is a kind of compression.
// Refer DecompressFreq().

//****************************************************************************
// Private attributes of this file.
//****************************************************************************

//#define GetVHFBandWidth(country)    (((country)==E_FRANCE)? E_RF_CH_BAND_8MHz : E_RF_CH_BAND_7MHz )

typedef struct
{
    BYTE cRFChannelNumber;
    WORD wCompressedFrequency;
    S8 *PhysicalChannelName;
} PHYSICAL_CHANNEL_INFO;

//#if ENABLE_SBTVD_DTV_SYSTEM
// Bandwidth: 6MHz
/*
static PHYSICAL_CHANNEL_INFO astPCI_Brazil[] =
{
    { (BYTE)7,    (WORD)708,    (S8 *)"7"}, // 177000 KHz / 250 KHz
    { (BYTE)8,    (WORD)732,    (S8 *)"8"}, // 183000 KHz / 250 KHz
    { (BYTE)9,    (WORD)756,    (S8 *)"9"}, // 189000 KHz / 250 KHz
    { (BYTE)10,    (WORD)780,    (S8 *)"10"}, // 195000 KHz / 250 KHz
    { (BYTE)11,    (WORD)804,    (S8 *)"11"}, // 201000 KHz / 250 KHz
    { (BYTE)12,    (WORD)828,    (S8 *)"12"}, // 207000 KHz / 250 KHz
    { (BYTE)13,    (WORD)852,    (S8 *)"13"}, // 213000 KHz / 250 KHz
};
*/
//#elif ( ENABLE_DVB_TAIWAN_APP )
// no VHF channel
//#elif ( ENABLE_DTMB_CHINA_APP )
// Bandwidth: 8MHz
#if ENABLE_DTMB
static PHYSICAL_CHANNEL_INFO astPCI_China[] =
{
    { 1,    210,    (S8 *)"1"}, // 52500 KHz / 250 KHz
    { 2,    242,    (S8 *)"2"}, // 60500 KHz / 250 KHz
    { 3,    274,    (S8 *)"3"}, // 68500 KHz / 250 KHz
    { 4,    320,    (S8 *)"4"}, // 80000 KHz / 250 KHz
    { 5,    352,    (S8 *)"5"}, // 88000 KHz / 250 KHz
    { 6,    684,    (S8 *)"6"}, // 171000 KHz / 250 KHz
    { 7,    716,    (S8 *)"7"}, // 179000 KHz / 250 KHz
    { 8,    748,    (S8 *)"8"}, // 187000 KHz / 250 KHz
    { 9,    780,    (S8 *)"9"}, // 195000 KHz / 250 KHz
    { 10,    812,    (S8 *)"10"},// 203000 KHz / 250 KHz
    { 11,    844,    (S8 *)"11"},// 211000 KHz / 250 KHz
    { 12,    876,    (S8 *)"12"},// 219000 KHz / 250 KHz
};
#endif
//#else
// Austria,
// Bandwidth: 7MHz
static PHYSICAL_CHANNEL_INFO astPCI_Australia[] =
{
#ifndef AUSTRALIA_DTV_NO_5A
    { (BYTE)5,    (WORD)418,    (S8 *)"5"}, // 104500 KHz / 250 KHz
    { (BYTE)90,    (WORD)562,    (S8 *)"5A"},// 140500 KHz / 250 KHz
#endif
    { (BYTE)6,    (WORD)710,    (S8 *)"6"}, // 177500 KHz / 250 KHz
    { (BYTE)7,    (WORD)738,    (S8 *)"7"}, // 184500 KHz / 250 KHz
    { (BYTE)8,    (WORD)766,    (S8 *)"8"}, // 191500 KHz / 250 KHz
    { (BYTE)9,    (WORD)794,    (S8 *)"9"}, // 198500 KHz / 250 KHz
    { (BYTE)154,(WORD)822,    (S8 *)"9A"},// 205500 KHz / 250 KHz
    { (BYTE)10,    (WORD)850,    (S8 *)"10"},// 212500 KHz / 250 KHz
    { (BYTE)11,    (WORD)878,    (S8 *)"11"},// 219500 KHz / 250 KHz
    { (BYTE)12,    (WORD)906,    (S8 *)"12"},// 226500 KHz / 250 KHz
};

static PHYSICAL_CHANNEL_INFO astPCI_VietNam[] =
{
    { (BYTE)6,    (WORD)712,    (S8 *)"6"}, // 178000 KHz / 250 KHz
    { (BYTE)7,    (WORD)744,    (S8 *)"7"}, // 186000 KHz / 250 KHz
    { (BYTE)8,    (WORD)776,    (S8 *)"8"}, // 194000 KHz / 250 KHz
    { (BYTE)9,    (WORD)808,    (S8 *)"9"}, // 202000 KHz / 250 KHz
    { (BYTE)10,    (WORD)840,    (S8 *)"10"}, // 210000 KHz / 250 KHz
    { (BYTE)11,    (WORD)872,    (S8 *)"11"}, // 218000 KHz / 250 KHz
    { (BYTE)12,    (WORD)904,    (S8 *)"12"}, // 226000 KHz / 250 KHz
};
static PHYSICAL_CHANNEL_INFO astPCI_Iran[] =
{
    { (BYTE)5,    (WORD)710,    (S8 *)"5"}, // 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"6"}, // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)766,    (S8 *)"7"}, // 191500 KHz / 250 KHz
    { (BYTE)8,    (WORD)794,    (S8 *)"8"}, // 198500 KHz / 250 KHz
    { (BYTE)9,    (WORD)822,    (S8 *)"9"}, // 205500 KHz / 250 KHz
    { (BYTE)10,   (WORD)850,    (S8 *)"10"}, // 212500 KHz / 250 KHz
    { (BYTE)11,   (WORD)878,    (S8 *)"11"}, // 219500 KHz / 250 KHz
    { (BYTE)12,   (WORD)906,    (S8 *)"12"}, // 226500 KHz / 250 KHz
};

#if ENABLE_SBTVD_DTV_SYSTEM
// Bandwidth: 6MHz
static PHYSICAL_CHANNEL_INFO astPCI_Brazil[] =
{
    { (BYTE)7,    (WORD)708,    (S8 *)"7"}, // 177000 KHz / 250 KHz
    { (BYTE)8,    (WORD)732,    (S8 *)"8"}, // 183000 KHz / 250 KHz
    { (BYTE)9,    (WORD)756,    (S8 *)"9"}, // 189000 KHz / 250 KHz
    { (BYTE)10,    (WORD)780,    (S8 *)"10"}, // 195000 KHz / 250 KHz
    { (BYTE)11,    (WORD)804,    (S8 *)"11"}, // 201000 KHz / 250 KHz
    { (BYTE)12,    (WORD)828,    (S8 *)"12"}, // 207000 KHz / 250 KHz
    { (BYTE)13,    (WORD)852,    (S8 *)"13"}, // 213000 KHz / 250 KHz
};
#endif

// Germany, Sweden, Finland, Denmark, Netherlands,
// Greece, Czech, Luxembourg, Belgium
// Bandwidth: 7MHz
static PHYSICAL_CHANNEL_INFO astPCI_General[] =
{
    { (BYTE)5,    (WORD)710,    (S8 *)"5"}, // 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"6"}, // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)766,    (S8 *)"7"}, // 191500 KHz / 250 KHz
    { (BYTE)8,    (WORD)794,    (S8 *)"8"}, // 198500 KHz / 250 KHz
    { (BYTE)9,    (WORD)822,    (S8 *)"9"}, // 205500 KHz / 250 KHz
    { (BYTE)10,    (WORD)850,    (S8 *)"10"}, // 212500 KHz / 250 KHz
    { (BYTE)11,    (WORD)878,    (S8 *)"11"}, // 219500 KHz / 250 KHz
    { (BYTE)12,    (WORD)906,    (S8 *)"12"}, // 226500 KHz / 250 KHz
};

// Bandwidth: 7MHz
static PHYSICAL_CHANNEL_INFO astPCI_Croatia[] =
{
    { (BYTE)5,    (WORD)710,    (S8 *)"5"}, // 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"6"}, // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)766,    (S8 *)"7"}, // 191500 KHz / 250 KHz
    { (BYTE)8,    (WORD)794,    (S8 *)"8"}, // 198500 KHz / 250 KHz
    { (BYTE)9,    (WORD)822,    (S8 *)"9"}, // 205500 KHz / 250 KHz
    { (BYTE)10,    (WORD)850,    (S8 *)"10"}, // 212500 KHz / 250 KHz
    { (BYTE)11,    (WORD)878,    (S8 *)"11"}, // 219500 KHz / 250 KHz
};

// Bandwidth: 7MHz
static PHYSICAL_CHANNEL_INFO astPCI_France[] =
{
    { (BYTE)5,    (WORD)710,    (S8 *)"L5"}, // 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"L6"}, // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)766,    (S8 *)"L7"}, // 191500 KHz / 250 KHz
    { (BYTE)8,    (WORD)794,    (S8 *)"L8"}, // 198500 KHz / 250 KHz
    { (BYTE)9,    (WORD)822,    (S8 *)"L9"}, // 205500 KHz / 250 KHz
    { (BYTE)10,    (WORD)850,    (S8 *)"L10"}, // 212500 KHz / 250 KHz
    { (BYTE)11,    (WORD)878,    (S8 *)"L11"}, // 219500 KHz / 250 KHz
    { (BYTE)12,    (WORD)906,    (S8 *)"L12"}, // 226500 KHz / 250 KHz

};

static PHYSICAL_CHANNEL_INFO astPCI_Norway_S_BandIII[] =
{
    { (BYTE)121,    (WORD)1224,    (S8 *)"S21"}, // 306000 KHz / 250 KHz
    { (BYTE)122,    (WORD)1256,    (S8 *)"S22"}, // 314000 KHz / 250 KHz
    { (BYTE)123,    (WORD)1288,    (S8 *)"S23"}, // 322000 KHz / 250 KHz
    { (BYTE)124,    (WORD)1320,    (S8 *)"S24"}, // 330000 KHz / 250 KHz
    { (BYTE)125,    (WORD)1352,    (S8 *)"S25"}, // 338000 KHz / 250 KHz
    { (BYTE)126,    (WORD)1384,    (S8 *)"S26"}, // 346000 KHz / 250 KHz
    { (BYTE)127,    (WORD)1416,    (S8 *)"S27"}, // 354000 KHz / 250 KHz
    { (BYTE)128,    (WORD)1448,    (S8 *)"S28"}, // 362000 KHz / 250 KHz
    { (BYTE)129,    (WORD)1480,    (S8 *)"S29"}, // 370000 KHz / 250 KHz
    { (BYTE)130,    (WORD)1512,    (S8 *)"S30"}, // 378000 KHz / 250 KHz
    { (BYTE)131,    (WORD)1544,    (S8 *)"S31"}, // 386000 KHz / 250 KHz
    { (BYTE)132,    (WORD)1576,    (S8 *)"S32"}, // 394000 KHz / 250 KHz
    { (BYTE)133,    (WORD)1608,    (S8 *)"S33"}, // 402000 KHz / 250 KHz
    { (BYTE)134,    (WORD)1640,    (S8 *)"S34"}, // 410000 KHz / 250 KHz
    { (BYTE)135,    (WORD)1672,    (S8 *)"S35"}, // 418000 KHz / 250 KHz
    { (BYTE)136,    (WORD)1704,    (S8 *)"S36"}, // 426000 KHz / 250 KHz
    { (BYTE)137,    (WORD)1736,    (S8 *)"S37"}, // 434000 KHz / 250 KHz
    { (BYTE)138,    (WORD)1768,    (S8 *)"S38"}, // 442000 KHz / 250 KHz
    { (BYTE)139,    (WORD)1800,    (S8 *)"S39"}, // 450000 KHz / 250 KHz
    { (BYTE)140,    (WORD)1832,    (S8 *)"S40"}, // 458000 KHz / 250 KHz
    { (BYTE)141,    (WORD)1864,    (S8 *)"S41"}, // 466000 KHz / 250 KHz
};

// Bandwidth: 8MHz
static PHYSICAL_CHANNEL_INFO astPCI_Norway_VHF8[] =
{
//K channel
    { (BYTE)5,     (WORD)710,    (S8 *)"K5"},// 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"K6"},   // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)766,    (S8 *)"K7"},   // 191500 KHz / 250 KHz
    { (BYTE)8,    (WORD)794,    (S8 *)"K8"},   // 198500 KHz / 250 KHz
    { (BYTE)9,    (WORD)822,    (S8 *)"K9"},   // 205500 KHz / 250 KHz
    { (BYTE)10,    (WORD)850,    (S8 *)"K10"},  // 212500 KHz / 250 KHz
    { (BYTE)11,    (WORD)878,    (S8 *)"K11"},  // 219500 KHz / 250 KHz
    { (BYTE)12,    (WORD)906,    (S8 *)"K12"},  // 226500 KHz / 250 KHz
//S Channel
    { (BYTE)111,    (WORD)934,    (S8 *)"S11"},  // 233500 KHz / 250 KHz
    { (BYTE)112,    (WORD)962,    (S8 *)"S12"},  // 240500 KHz / 250 KHz
    { (BYTE)113,    (WORD)990,    (S8 *)"S13"},  // 247500 KHz / 250 KHz
    { (BYTE)114,    (WORD)1018,    (S8 *)"S14"},  // 254500 KHz / 250 KHz
    { (BYTE)115,    (WORD)1046,    (S8 *)"S15"},  // 261500 KHz / 250 KHz
    { (BYTE)116,    (WORD)1074,    (S8 *)"S16"},  // 268500 KHz / 250 KHz
    { (BYTE)117,    (WORD)1102,    (S8 *)"S17"},  // 275500 KHz / 250 KHz
    { (BYTE)118,    (WORD)1130,    (S8 *)"S18"},  // 282500 KHz / 250 KHz
    { (BYTE)119,    (WORD)1158,    (S8 *)"S19"},  // 289500 KHz / 250 KHz
    { (BYTE)120,    (WORD)1186,    (S8 *)"S20"},  // 296500 KHz / 250 KHz
//D channel
    { (BYTE)209,     (WORD)712,    (S8 *)"D9"},  // 178000 KHz / 250 KHz
    { (BYTE)210,    (WORD)744,    (S8 *)"D10"}, // 186000 KHz / 250 KHz
    { (BYTE)211,    (WORD)776,    (S8 *)"D11"}, // 194000 KHz / 250 KHz
    { (BYTE)212,    (WORD)808,    (S8 *)"D12"}, // 202000 KHz / 250 KHz
    { (BYTE)213,    (WORD)840,    (S8 *)"D13"}, // 210000 KHz / 250 KHz
    { (BYTE)214,    (WORD)872,    (S8 *)"D14"}, // 218000 KHz / 250 KHz
    { (BYTE)215,    (WORD)904,    (S8 *)"D15"}, // 226000 KHz / 250 KHz
    { (BYTE)216,    (WORD)936,    (S8 *)"D16"}, // 234000 KHz / 250 KHz
    { (BYTE)217,    (WORD)968,    (S8 *)"D17"}, // 242000 KHz / 250 KHz
    { (BYTE)218,    (WORD)1000,    (S8 *)"D18"}, // 250000 KHz / 250 KHz
    { (BYTE)219,    (WORD)1032,    (S8 *)"D19"}, // 258000 KHz / 250 KHz
    { (BYTE)220,    (WORD)1064,    (S8 *)"D20"}, // 266000 KHz / 250 KHz
    { (BYTE)221,    (WORD)1096,    (S8 *)"D21"}, // 274000 KHz / 250 KHz
    { (BYTE)222,    (WORD)1128,    (S8 *)"D22"}, // 282000 KHz / 250 KHz
    { (BYTE)223,    (WORD)1160,    (S8 *)"D23"}, // 290000 KHz / 250 KHz
    { (BYTE)224,    (WORD)1192,    (S8 *)"D24"}, // 298000 KHz / 250 KHz

};

// Bandwidth: 7MHz
static PHYSICAL_CHANNEL_INFO astPCI_Norway_VHF7[] =
{
    { (BYTE)5,     (WORD)710,    (S8 *)"K5"},// 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"K6"},   // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)766,    (S8 *)"K7"},   // 191500 KHz / 250 KHz
    { (BYTE)8,    (WORD)794,    (S8 *)"K8"},   // 198500 KHz / 250 KHz
    { (BYTE)9,    (WORD)822,    (S8 *)"K9"},   // 205500 KHz / 250 KHz
    { (BYTE)10,    (WORD)850,    (S8 *)"K10"},  // 212500 KHz / 250 KHz
    { (BYTE)11,    (WORD)878,    (S8 *)"K11"},  // 219500 KHz / 250 KHz
    { (BYTE)12,    (WORD)906,    (S8 *)"K12"},  // 226500 KHz / 250 KHz
    { (BYTE)111,    (WORD)934,    (S8 *)"S11"},  // 233500 KHz / 250 KHz
    { (BYTE)112,    (WORD)962,    (S8 *)"S12"},  // 240500 KHz / 250 KHz
    { (BYTE)113,    (WORD)990,    (S8 *)"S13"},  // 247500 KHz / 250 KHz
    { (BYTE)114,    (WORD)1018,    (S8 *)"S14"},  // 254500 KHz / 250 KHz
    { (BYTE)115,    (WORD)1046,    (S8 *)"S15"},  // 261500 KHz / 250 KHz
    { (BYTE)116,    (WORD)1074,    (S8 *)"S16"},  // 268500 KHz / 250 KHz
    { (BYTE)117,    (WORD)1102,    (S8 *)"S17"},  // 275500 KHz / 250 KHz
    { (BYTE)118,    (WORD)1130,    (S8 *)"S18"},  // 282500 KHz / 250 KHz
    { (BYTE)119,    (WORD)1158,    (S8 *)"S19"},  // 289500 KHz / 250 KHz
    { (BYTE)120,    (WORD)1186,    (S8 *)"S20"},  // 296500 KHz / 250 KHz
};


#if (ITALY_USE_EUROPEAN_VHF == FALSE)
// Bandwidth: 7MHz
static PHYSICAL_CHANNEL_INFO astPCI_ITALY[] =
{
    { (BYTE)5,    (WORD)710,    (S8 *)"D"}, // 177500 KHz / 250 KHz
    { (BYTE)6,    (WORD)738,    (S8 *)"D1"}, // 184500 KHz / 250 KHz
    { (BYTE)7,    (WORD)744,    (S8 *)"E"}, // 186000 KHz / 250 KHz
    { (BYTE)8,    (WORD)766,    (S8 *)"E1"}, // 191500 KHz / 250 KHz
    { (BYTE)9,    (WORD)778,    (S8 *)"F"}, // 194500 KHz / 250 KHz
    { (BYTE)10,    (WORD)794,    (S8 *)"F1"}, // 198500 KHz / 250 KHz
    { (BYTE)11,    (WORD)814,    (S8 *)"G"}, // 203500 KHz / 250 KHz
    { (BYTE)12,    (WORD)822,    (S8 *)"G1"}, // 205500 KHz / 250 KHz
    { (BYTE)13,    (WORD)850,    (S8 *)"H"}, // 212500 KHz / 250 KHz
    { (BYTE)14,    (WORD)878,    (S8 *)"H1"}, // 219500 KHz / 250 KHz
    { (BYTE)15,    (WORD)906,    (S8 *)"H2"}, // 226500 KHz / 250 KHz
};
#endif
//#endif

//****************************************************************************
// Private functions of this file.
//****************************************************************************

static DWORD DecompressFreq(WORD wCompressedFreq);
static BOOLEAN IsPhysicalChannelNumberValid(MEMBER_COUNTRY eCountry, BYTE cRFChannelNumber);
static BOOLEAN IsVHFExist(MEMBER_COUNTRY eCountry);
static BYTE GetFirstPhysicalChannelNumber(MEMBER_COUNTRY eCountry);
static BYTE GetPhysicalChannelInfoTableForVHF(MEMBER_COUNTRY eCountry, PHYSICAL_CHANNEL_INFO ROM ** ppastPhysicalChannelInfoTable);
//#if (! ((ENABLE_DTMB_CHINA_APP)||( ENABLE_SBTVD_DTV_SYSTEM)))
static RF_CHANNEL_BANDWIDTH GetVHFBandWidth(MEMBER_COUNTRY eCountry);
//#endif
static BOOLEAN _CrossBandwidth;
static U8 _u8Terr_BandWidth;
static BOOLEAN _bDynamicBandScanFinished;
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
static BYTE GetPhysicalChannelInfoTableForUHF_S_BandIII(MEMBER_COUNTRY eCountry, PHYSICAL_CHANNEL_INFO ROM ** ppastPhysicalChannelInfoTable);
//#endif

//****************************************************************************
// Start of public implementation
//****************************************************************************

/******************************************************************************/
/// -This function will Get TS Setting
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @param pstTPSetting \b IN: TP Setting
/// -@see MS_TP_SETTING
/// @return BOOLEAN: Function execution result
/******************************************************************************/
U8 MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(MEMBER_COUNTRY eCountry)
{
#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
        return MIN_UHF_PHYSICAL_CHANNEL_NUMBER_DTMB;
    }
    else
#endif
#if (ENABLE_ISDBT)
    if(IsISDBTInUse())
    {
        return MIN_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT(eCountry);
    }
    else
#endif
    {
    #if ( ENABLE_DVB_TAIWAN_APP )
        return MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
    #else
        return MIN_UHF_PHYSICAL_CHANNEL_NUMBER_DVBT(eCountry);
    #endif
    }

    UNUSED(eCountry);
}

U8 MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER(void)
{
#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
        return MAX_UHF_PHYSICAL_CHANNEL_NUMBER_DTMB;
    }
    else
#endif
#if (ENABLE_ISDBT)
    if(IsISDBTInUse())
    {
        return MAX_UHF_PHYSICAL_CHANNEL_NUMBER_ISDBT;
    }
    else
#endif
    {
        return MAX_UHF_PHYSICAL_CHANNEL_NUMBER_DVBT;
    }


}

BOOLEAN msAPI_DFT_GetTSSetting(BYTE cRFChannelNumber, MS_TP_SETTING * pstTPSetting)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize;
    BYTE i;

    {
        #define ENABLE_MAX_CM_TEST  0
        #if ENABLE_MAX_CM_TEST
            #define RF_CH_NO_ON_PLAYCARD    47
            cRFChannelNumber = RF_CH_NO_ON_PLAYCARD;  //20100720EL
        #endif
    }

    memset(pstTPSetting,0,sizeof(MS_TP_SETTING));
    pstTPSetting->u8PLPID = 0xFF;
    eCountry = msAPI_CM_GetCountry();

    if( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
    {
        return FALSE;
    }

    if (  (MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber)
       && (cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()) )
    {
      #if ENABLE_DTMB
        if (IsDTMBInUse())
        {
        #if ENABLE_DTMB_ADD_FREQUENCY
            //13~73
            pstTPSetting->u32Frequency = 474000L + (cRFChannelNumber - MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)) * 8000L;
        #else
            //13~68
            if (cRFChannelNumber < 25)
                pstTPSetting->u32Frequency = 474000L + (cRFChannelNumber - MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)) * 8000L;
            else
                pstTPSetting->u32Frequency = 610000L + (cRFChannelNumber - 25) * 8000L;
        #endif
            pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;

        }
        else
      #endif
        {
            switch (eCountry)
            {
                case E_AUSTRALIA:
                    pstTPSetting->u32Frequency = 522500L + (cRFChannelNumber - (MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry))) * 7000L;
                    pstTPSetting->enBandWidth = E_RF_CH_BAND_7MHz;
                    break;

              #if ( ENABLE_DVB_TAIWAN_APP )
                case E_TAIWAN:
                    //14~69 = 473 + (RF-14)x6
                    pstTPSetting->u32Frequency = 473000L + (cRFChannelNumber - MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)) * 6000L;
                    pstTPSetting->enBandWidth = E_RF_CH_BAND_6MHz;
                    break;
              #endif

              #if ENABLE_SBTVD_DTV_SYSTEM
                case E_BRAZIL:
                    //14~69 = 473 + (RF-14)x6 + 1/7
                    pstTPSetting->u32Frequency = 473000L + (cRFChannelNumber - MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)) * 6000L + 143;
                    pstTPSetting->enBandWidth = E_RF_CH_BAND_6MHz;
                    break;
              #endif

                case E_SWEDEN:
				if(cRFChannelNumber >= MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) && cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER())
				{
				    pstTPSetting->u32Frequency = 474000L + (cRFChannelNumber - MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)) * 8000L;
				    pstTPSetting->enBandWidth = (RF_CHANNEL_BANDWIDTH)_u8Terr_BandWidth;
				}
				break;

                default:
                    if (  cRFChannelNumber >= MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)
                       && cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER() ) //21~69
                    {
                        pstTPSetting->u32Frequency = 474000L + (cRFChannelNumber - MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)) * 8000L;
                        pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
                    }
                    break;
            }
        }

    #if ENABLE_SZ_DTV_OFFSET_FUNCTION
        pstTPSetting->u32Frequency +=((S16)stGenSetting.s8DTVFrequencyOffset[cRFChannelNumber]*125)/4;
    #endif

        FREQ_TABLE_DEG(printf("\n eCountry: %bu, enBandWidth: %bu ", eCountry, pstTPSetting->enBandWidth));
        FREQ_TABLE_DEG(printf("\n cRFChannelNumber: %lu ", cRFChannelNumber));
        FREQ_TABLE_DEG(printf("\n u32Frequency: %lu ", pstTPSetting->u32Frequency));

        return TRUE;
     }
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
     else if( MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER <= cRFChannelNumber &&
         cRFChannelNumber <= MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER  && (!IsDTMBInUse()))
     {
         cTableSize = GetPhysicalChannelInfoTableForUHF_S_BandIII(eCountry, &pastPhysicalChannelInfoTable);
         for(i=0; i < cTableSize; i++)
         {
             if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
             {
                 pstTPSetting->u32Frequency = DecompressFreq(pastPhysicalChannelInfoTable[i].wCompressedFrequency);
                 pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
                 FREQ_TABLE_DEG(printf("UHF S III :>> pstTPSetting->u32Frequency %lu, pstTPSetting->enBandWidth  %bu\n",pstTPSetting->u32Frequency,pstTPSetting->enBandWidth));
                 return TRUE;
             }
         }
     }
//#endif
     {
         cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

         for(i=0; i < cTableSize; i++)
         {
             if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
             {
                pstTPSetting->u32Frequency = DecompressFreq(pastPhysicalChannelInfoTable[i].wCompressedFrequency);
                #if 0
             #if ( ENABLE_DTMB_CHINA_APP )
                   pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
             #elif(ENABLE_SBTVD_DTV_SYSTEM)
                    pstTPSetting->u32Frequency += 143;//Brazil freq is .143Mhz
                    pstTPSetting->enBandWidth = E_RF_CH_BAND_6MHz;
             #else
                  pstTPSetting->enBandWidth = GetVHFBandWidth(eCountry);
            #endif
            #else
                #if ENABLE_DTMB
                if(IsDTMBInUse())
                    pstTPSetting->enBandWidth = E_RF_CH_BAND_8MHz;
                else
                #endif
                #if ENABLE_ISDBT
                    if (IsISDBTInUse())
                    {
                        pstTPSetting->u32Frequency += 143;//Brazil freq is .143Mhz
                        pstTPSetting->enBandWidth = E_RF_CH_BAND_6MHz;
                    }
                    else
                #endif
                        pstTPSetting->enBandWidth = GetVHFBandWidth(eCountry);
            #endif

            #if ENABLE_SZ_DTV_OFFSET_FUNCTION
                pstTPSetting->u32Frequency +=((S16)stGenSetting.s8DTVFrequencyOffset[cRFChannelNumber]*125)/4;
            #endif
                FREQ_TABLE_DEG(printf("VHF III~ S II :>> pstTPSetting->u32Frequency %lu, pstTPSetting->enBandWidth  %bu\n",pstTPSetting->u32Frequency,pstTPSetting->enBandWidth));
                return TRUE;
             }
         }
    }

    return FALSE;
}

#if (!BLOADER)
/******************************************************************************/
/// -This function will Get Physical Channel Name
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @param sPhysicalChannelName \b IN: pointer to Physical Channel Name for return
/// @param cBufferSize \b IN: Buffer Size
/// @return BOOLEAN: Function execution result
/******************************************************************************/
BOOLEAN msAPI_DFT_GetPhysicalChannelName(BYTE cRFChannelNumber, BYTE * sPhysicalChannelName, BYTE cBufferSize)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize;
    BYTE i,j;

    eCountry = msAPI_CM_GetCountry();

    if( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
        return FALSE;

    if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber &&
         cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER() )
    {
        if( cBufferSize < 3 )
        {
            return FALSE;
        }
        else
        {
            sPhysicalChannelName[0] = (cRFChannelNumber/10) + '0';
            sPhysicalChannelName[1] = (cRFChannelNumber%10) + '0';
            sPhysicalChannelName[2] = 0;

            return TRUE;
        }
     }
    //UHF S-BandIII
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
        else if((!IsDTMBInUse()) &&(eCountry == E_NORWAY) && ( MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER <= cRFChannelNumber &&
             cRFChannelNumber <= MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER ))
    {
         pastPhysicalChannelInfoTable = astPCI_Norway_S_BandIII;
         cTableSize = (sizeof(astPCI_Norway_S_BandIII)/sizeof(PHYSICAL_CHANNEL_INFO));

         for(i=0; i < cTableSize; i++)
         {
             //printf("2 sizeof %bu: %bu \n", eCountry, pastPhysicalChannelInfoTable[i].cRFChannelNumber);
             if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
             {
                if( cBufferSize <= strlen((const char *)pastPhysicalChannelInfoTable[i].PhysicalChannelName) )
                {
                    return FALSE;
                }
                else
                {
                    for(j=0; j <= strlen((const char *)pastPhysicalChannelInfoTable[i].PhysicalChannelName); j++)
                    {
                        sPhysicalChannelName[j] = pastPhysicalChannelInfoTable[i].PhysicalChannelName[j];
                    }
                    return TRUE;
                }
             }
         }
    }
//#endif
     else
     {
         cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

         for(i=0; i < cTableSize; i++)
         {
             //printf("2 sizeof %bu: %bu \n", eCountry, pastPhysicalChannelInfoTable[i].cRFChannelNumber);
             if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
             {
                if( cBufferSize <= strlen((const char *)pastPhysicalChannelInfoTable[i].PhysicalChannelName) )
                {
                    return FALSE;
                }
                else
                {
                    for(j=0; j <= strlen((const char *)pastPhysicalChannelInfoTable[i].PhysicalChannelName); j++)
                    {
                        sPhysicalChannelName[j] = pastPhysicalChannelInfoTable[i].PhysicalChannelName[j];
                    }
                    return TRUE;
                }
             }
         }
    }

    return FALSE;
}
#endif //(!BLOADER)

/******************************************************************************/
/// -This function will Get First Physical Channel Number
/// @return BYTE: First Physical Channel Number by country
/******************************************************************************/
BYTE msAPI_DFT_GetFirstPhysicalChannelNumber(void)
{
    return GetFirstPhysicalChannelNumber(msAPI_CM_GetCountry());
}

#if (!BLOADER)
/******************************************************************************/
/// -This function will Get previous Physical Channel Number
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @return BYTE: previous Physical Channel Number
/******************************************************************************/
BYTE msAPI_DFT_GetPrevPhysicalChannelNumber(BYTE cRFChannelNumber)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable_V=NULL;
    BYTE cTableSize_V=0;
    BYTE i;
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable1_U=NULL;
    BYTE cTableSize_U=0;
//#endif
    eCountry = msAPI_CM_GetCountry();

    if( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
        return INVALID_PHYSICAL_CHANNEL_NUMBER;

    if(!IsDTMBInUse())
    {
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
        cTableSize_U = GetPhysicalChannelInfoTableForUHF_S_BandIII(eCountry, &pastPhysicalChannelInfoTable1_U);
//#endif
    }
        cTableSize_V = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable_V);
     if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) < cRFChannelNumber &&
         cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER() )
     {
         FREQ_TABLE_DEG(printf("Previous RF Channel    %bu\n",(cRFChannelNumber-1)));
         return (cRFChannelNumber-1);
     }
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    else if((!IsDTMBInUse()) && (cTableSize_U > 0)&&((MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) == cRFChannelNumber)
        ||( MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER < cRFChannelNumber &&
         cRFChannelNumber <= MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER )))
    {
        if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) == cRFChannelNumber )
        {
            FREQ_TABLE_DEG(printf("Previous RF Channel    %bu\n",pastPhysicalChannelInfoTable1_U[cTableSize_U-1].cRFChannelNumber));
            return pastPhysicalChannelInfoTable1_U[cTableSize_U-1].cRFChannelNumber;
        }

        for(i=0; i < cTableSize_U; i++)
        {
            if( cRFChannelNumber == pastPhysicalChannelInfoTable1_U[i].cRFChannelNumber )
            {
                FREQ_TABLE_DEG(printf("Previous RF Channel    %bu\n",pastPhysicalChannelInfoTable1_U[i-1].cRFChannelNumber));
                return pastPhysicalChannelInfoTable1_U[i-1].cRFChannelNumber;
            }
        }

    }
//#endif
     else
     {
          if( 0 == cTableSize_V )
          {
              FREQ_TABLE_DEG(printf("Previous RF Channel  %bu\n",(INVALID_PHYSICAL_CHANNEL_NUMBER)));
              return INVALID_PHYSICAL_CHANNEL_NUMBER;
          }

         if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) == cRFChannelNumber )
         {
             FREQ_TABLE_DEG(printf("Previous RF Channel  %bu\n",pastPhysicalChannelInfoTable_V[cTableSize_V-1].cRFChannelNumber));
             return pastPhysicalChannelInfoTable_V[cTableSize_V-1].cRFChannelNumber;
         }
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
        if (NULL != pastPhysicalChannelInfoTable1_U && (!IsDTMBInUse()))
        {
             if( pastPhysicalChannelInfoTable1_U[0].cRFChannelNumber == cRFChannelNumber )
             {
                 FREQ_TABLE_DEG(printf("Previous RF Channel  %bu\n",pastPhysicalChannelInfoTable_V[cTableSize_V-1].cRFChannelNumber));
                 return pastPhysicalChannelInfoTable_V[cTableSize_V-1].cRFChannelNumber;
             }
        }
//#endif
         for(i=0; i < cTableSize_V; i++)
         {
             if( cRFChannelNumber == pastPhysicalChannelInfoTable_V[i].cRFChannelNumber )
             {
                 if( i == 0 )
                 {
                     FREQ_TABLE_DEG(printf("Previous RF Channel  %bu\n",(INVALID_PHYSICAL_CHANNEL_NUMBER)));
                     return INVALID_PHYSICAL_CHANNEL_NUMBER;
                 }
                 FREQ_TABLE_DEG(printf("Previous RF Channel  %bu\n",pastPhysicalChannelInfoTable_V[i-1].cRFChannelNumber));
                 return pastPhysicalChannelInfoTable_V[i-1].cRFChannelNumber;
             }
         }
     }
     return INVALID_PHYSICAL_CHANNEL_NUMBER;
}
#endif //(!BLOADER)

#if 0 //ENABLE_SZ_DTV_ADDCH_SCAN_FUNCTION
BYTE msAPI_GetNextEmptyPhysicalChannelNumber(BYTE cRFChannelNumber)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize;
    BYTE i,j,number;

    eCountry = msAPI_CM_GetCountry();

    if( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
        return INVALID_PHYSICAL_CHANNEL_NUMBER;

        if( MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber &&
            cRFChannelNumber <= MAX_UHF_PHYSICAL_CHANNEL_NUMBER )
        {
            if( cRFChannelNumber == MAX_UHF_PHYSICAL_CHANNEL_NUMBER )
                return INVALID_PHYSICAL_CHANNEL_NUMBER;

            for(number=cRFChannelNumber+1;number<=MAX_UHF_PHYSICAL_CHANNEL_NUMBER;number++)
            {
                j=msAPI_CM_Get_RFChannelIndex(number);
                if(j==MAX_MUX_NUMBER)
             return (number);
            }

            return INVALID_PHYSICAL_CHANNEL_NUMBER;
     }
     else
     {
            cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

            for(i=0; i < cTableSize; i++)
            {
                if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
                {
                    if( (i+1) == cTableSize )
                    {
                        return MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
                    }
                }
            }

            for(i=i+1; i < cTableSize; i++)
            {
                number=pastPhysicalChannelInfoTable[i].cRFChannelNumber;
                j=msAPI_CM_Get_RFChannelIndex(number);
                if(j==MAX_MUX_NUMBER)
                {
                    return number;
                }
            }
            return MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
    }

    return INVALID_PHYSICAL_CHANNEL_NUMBER;
}
#endif
/******************************************************************************/
/// -This function will Get Next Physical Channel Number
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @return BYTE: Next Physical Channel Number
/******************************************************************************/
BYTE msAPI_DFT_GetNextPhysicalChannelNumber(BYTE cRFChannelNumber)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable_V;
    BYTE cTableSize_U = 0, cTableSize_V=0;
    BYTE i;
    BYTE bNexPhyChNum = INVALID_PHYSICAL_CHANNEL_NUMBER;

    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable1_U;
    eCountry = msAPI_CM_GetCountry();

    if ( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
        return INVALID_PHYSICAL_CHANNEL_NUMBER;

    if (!IsDTMBInUse())
    {
        cTableSize_U = GetPhysicalChannelInfoTableForUHF_S_BandIII(eCountry, &pastPhysicalChannelInfoTable1_U);
    }
    cTableSize_V = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable_V);

    if (  (MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber)
       && (cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()) )
    {
        if( cRFChannelNumber == MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER() )
        {
            bNexPhyChNum = INVALID_PHYSICAL_CHANNEL_NUMBER;
            FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
            return bNexPhyChNum;
        }

        bNexPhyChNum = (cRFChannelNumber+1);
        FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
        return bNexPhyChNum;
     }
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    else if (  (!IsDTMBInUse()) && (cTableSize_U > 0)
            && ( (MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER <= cRFChannelNumber)
               &&(cRFChannelNumber <= MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER) )  )
    {
        for(i=0; i < cTableSize_U; i++)
        {
            if( cRFChannelNumber == pastPhysicalChannelInfoTable1_U[i].cRFChannelNumber )
            {
                if( (i+1) == cTableSize_U )
                {
                    bNexPhyChNum = MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
                    FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
                    return bNexPhyChNum;
                }

                bNexPhyChNum = pastPhysicalChannelInfoTable1_U[i+1].cRFChannelNumber;
                FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
                return bNexPhyChNum;
            }
        }
    }
//#endif
    else
    {
        for(i=0; i < cTableSize_V; i++)
        {
            if( cRFChannelNumber == pastPhysicalChannelInfoTable_V[i].cRFChannelNumber )
            {
                if( (i+1) == cTableSize_V )
                {
                    if((eCountry == E_NORWAY))
                    {
                        if(_CrossBandwidth &&(_u8Terr_BandWidth == E_RF_CH_BAND_7MHz) )
                        {
                            _u8Terr_BandWidth = E_RF_CH_BAND_8MHz;
                            if(GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable_V))
                            {
                                bNexPhyChNum = msAPI_DFT_GetFirstPhysicalChannelNumber();
                                FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
                                return bNexPhyChNum;
                            }
                        }
                        //#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
                        else
                        {
                            if ( (cTableSize_U > 0) && (!IsDTMBInUse()) )
                            {
                                bNexPhyChNum = pastPhysicalChannelInfoTable1_U[0].cRFChannelNumber;
                                FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
                                return bNexPhyChNum;
                            }
                        }
                        //#endif
                    }

                    bNexPhyChNum = MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
                    FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
                    return bNexPhyChNum;
                }

                bNexPhyChNum = pastPhysicalChannelInfoTable_V[i+1].cRFChannelNumber;
                FREQ_TABLE_DEG(printf("[%d] Next RF Channel: %bu\n", __LINE__, bNexPhyChNum));
                return bNexPhyChNum;
            }
        }
     }

     return INVALID_PHYSICAL_CHANNEL_NUMBER;
}


/******************************************************************************/
/// -This function will Get Percent With Physical Channel Number
/// @param cRFChannelNumber \b IN: RF Channel Number
/// @return BYTE: Percent
/******************************************************************************/
BYTE msAPI_DFT_GetPercentWithPhysicalChannelNumber(BYTE cRFChannelNumber)
{
    MEMBER_COUNTRY eCountry;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize=0;
    BYTE i;
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable_U;
    BYTE cTableSize_U=0;
//#endif

    eCountry = msAPI_CM_GetCountry();

    if( FALSE == IsPhysicalChannelNumberValid(eCountry, cRFChannelNumber) )
        return 0;
    if(!IsDTMBInUse())
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    cTableSize_U = GetPhysicalChannelInfoTableForUHF_S_BandIII(eCountry, &pastPhysicalChannelInfoTable_U);
//#endif
    cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

    //if( FALSE == IsVHFExist(eCountry) )
    {
        if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber &&
            cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER() )
        {
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
        if(!IsDTMBInUse())
        {
            if(_CrossBandwidth &&(_u8Terr_BandWidth == E_RF_CH_BAND_8MHz) )
                return (BYTE)(((WORD)(cRFChannelNumber-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)+2*cTableSize+cTableSize_U)*100)/(MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)+2*cTableSize+cTableSize_U));
            else
                return (BYTE)(((WORD)(cRFChannelNumber-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)+cTableSize+cTableSize_U)*100)/(MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)+cTableSize+cTableSize_U));
        }
        else
//#else
            return (BYTE)(((WORD)(cRFChannelNumber-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)+cTableSize)*100)/(MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)+cTableSize));
//#endif
        }
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
        else if((!IsDTMBInUse()) &&(cTableSize_U > 0) && ( MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER <= cRFChannelNumber &&
            cRFChannelNumber <= MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER ))
        {
            for(i=0; i < cTableSize_U; i++)
            {
                if( cRFChannelNumber == pastPhysicalChannelInfoTable_U[i].cRFChannelNumber )
                {
                    break;
                }
            }
            if( i < cTableSize_U )
            {
                if(_CrossBandwidth &&(_u8Terr_BandWidth == E_RF_CH_BAND_8MHz) )
                    return (BYTE)(((WORD)(i+2*cTableSize)*100)/((MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry))+2*cTableSize+cTableSize_U));
                else
                    return (BYTE)(((WORD)(i+cTableSize)*100)/((MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry))+cTableSize+cTableSize_U));
            }
        }
//#endif
    }


     for(i=0; i < cTableSize; i++)
     {
         if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
         {
            break;
         }
     }

     if( i < cTableSize )
     {
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
if(!IsDTMBInUse())
{
        if(_CrossBandwidth &&(_u8Terr_BandWidth == E_RF_CH_BAND_8MHz) )
            return (BYTE)(((WORD)(i+cTableSize)*100)/((MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry))+cTableSize+cTableSize_U));
        else
            return (BYTE)(((WORD)i*100)/((MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry))+cTableSize+cTableSize_U));
}
else
//#else
         return (BYTE)(((WORD)i*100)/((MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER()-MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry))+cTableSize));
//#endif
     }

     return 0;
}


//****************************************************************************
// Start of private implementation
//****************************************************************************

static DWORD DecompressFreq(WORD wCompressedFreq)
{
    return (DWORD)wCompressedFreq * 250;
}

static BOOLEAN IsPhysicalChannelNumberValid(MEMBER_COUNTRY eCountry, BYTE cRFChannelNumber)
{
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize;
    BYTE i;

    if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) <= cRFChannelNumber &&
         cRFChannelNumber <= MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER() )
     {
         return TRUE;
     }
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    else if(!IsDTMBInUse())
    {
        cTableSize = GetPhysicalChannelInfoTableForUHF_S_BandIII(eCountry, &pastPhysicalChannelInfoTable);

        for(i=0; i < cTableSize; i++)
        {
            if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
            {
                return TRUE;
            }
        }
    }
//#endif
    if( TRUE == IsVHFExist(eCountry) )
    {
        cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

        for(i=0; i < cTableSize; i++)
         {
             if( cRFChannelNumber == pastPhysicalChannelInfoTable[i].cRFChannelNumber )
             {
                return TRUE;
             }
         }
    }
    FREQ_TABLE_DEG(printf(">>> Invalid RF Channel\n"));
    return FALSE;
}

static BOOLEAN IsVHFExist(MEMBER_COUNTRY eCountry)
{
    if( MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry) == GetFirstPhysicalChannelNumber(eCountry) )
        return FALSE;
    else if((MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER <= GetFirstPhysicalChannelNumber(eCountry))
        &&(MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER >= GetFirstPhysicalChannelNumber(eCountry)))
    {
        return FALSE;
    }
    FREQ_TABLE_DEG(printf(">>>>> VHF Exist\n"));
    return TRUE;
}

static BYTE GetFirstPhysicalChannelNumber(MEMBER_COUNTRY eCountry)
{
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize;

    cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);

    if( 0 == cTableSize )
    {
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
        if(GetPhysicalChannelInfoTableForUHF_S_BandIII(eCountry, &pastPhysicalChannelInfoTable) &&(!IsDTMBInUse()))
        {
            FREQ_TABLE_DEG(printf(">>>Get first RF Channel    %bu\n",pastPhysicalChannelInfoTable[0].cRFChannelNumber));
            return pastPhysicalChannelInfoTable[0].cRFChannelNumber;
        }
//#endif
        FREQ_TABLE_DEG(printf(">>>Get first RF Channel    %bu\n",MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry)));
        return MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);
    }

    return pastPhysicalChannelInfoTable[0].cRFChannelNumber;
}

//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
static BYTE GetPhysicalChannelInfoTableForUHF_S_BandIII(MEMBER_COUNTRY eCountry, PHYSICAL_CHANNEL_INFO ROM ** ppastPhysicalChannelInfoTable)
{
    BYTE cTableSize=0;

    switch(eCountry)
    {
        case E_NORWAY:
            *ppastPhysicalChannelInfoTable = astPCI_Norway_S_BandIII;
            cTableSize = (sizeof(astPCI_Norway_S_BandIII)/sizeof(PHYSICAL_CHANNEL_INFO));
            break;
        default:
            break;
    }

    return cTableSize;
}
//#endif
static BYTE GetPhysicalChannelInfoTableForVHF(MEMBER_COUNTRY eCountry, PHYSICAL_CHANNEL_INFO ROM ** ppastPhysicalChannelInfoTable)
{
    BYTE cTableSize=0;
#if 0
#if ENABLE_SBTVD_DTV_SYSTEM
    UNUSED(eCountry);
    *ppastPhysicalChannelInfoTable = astPCI_Brazil;
    cTableSize = (sizeof(astPCI_Brazil)/sizeof(PHYSICAL_CHANNEL_INFO));

#elif ( ENABLE_DVB_TAIWAN_APP )
    cTableSize = 0;
    UNUSED(eCountry);
    UNUSED(ppastPhysicalChannelInfoTable);
#elif ( ENABLE_DTMB_CHINA_APP )
    UNUSED(eCountry);
    *ppastPhysicalChannelInfoTable = astPCI_China;
    cTableSize = (sizeof(astPCI_China)/sizeof(PHYSICAL_CHANNEL_INFO));
#else

    switch(eCountry)
    {
    case E_AUSTRALIA:
         *ppastPhysicalChannelInfoTable = astPCI_Australia;
         cTableSize = (sizeof(astPCI_Australia)/sizeof(PHYSICAL_CHANNEL_INFO));
        break;
    case E_NEWZEALAND:
    case E_UK:
    case E_SPAIN:
    case E_HUNGARY:
    case E_MOROCCO:
        cTableSize = 0;
        break;

    case E_CROATIA:
        *ppastPhysicalChannelInfoTable = astPCI_Croatia;
         cTableSize = (sizeof(astPCI_Croatia)/sizeof(PHYSICAL_CHANNEL_INFO));
         break;

    case E_FRANCE:
        *ppastPhysicalChannelInfoTable = astPCI_France;
         cTableSize = (sizeof(astPCI_France)/sizeof(PHYSICAL_CHANNEL_INFO));
         break;
#if (ITALY_USE_EUROPEAN_VHF == FALSE)
    case E_ITALY:
        *ppastPhysicalChannelInfoTable = astPCI_ITALY;
         cTableSize = (sizeof(astPCI_ITALY)/sizeof(PHYSICAL_CHANNEL_INFO));
         break;
#endif
    case E_NORWAY:
        if(GetVHFBandWidth(E_NORWAY) == E_RF_CH_BAND_7MHz)// 7 Mhz
        {
            *ppastPhysicalChannelInfoTable = astPCI_Norway_VHF7;
            cTableSize = (sizeof(astPCI_Norway_VHF7)/sizeof(PHYSICAL_CHANNEL_INFO));
        }
        else if(GetVHFBandWidth(E_NORWAY) == E_RF_CH_BAND_8MHz) // 8 Mhz
        {
            *ppastPhysicalChannelInfoTable = astPCI_Norway_VHF8;
            cTableSize = (sizeof(astPCI_Norway_VHF8)/sizeof(PHYSICAL_CHANNEL_INFO));
        }
        break;

    case E_VIETNAM:
        *ppastPhysicalChannelInfoTable = astPCI_VietNam;
        cTableSize = (sizeof(astPCI_VietNam)/sizeof(PHYSICAL_CHANNEL_INFO));
        break;

    case E_IRAN:
         *ppastPhysicalChannelInfoTable = astPCI_Iran;
         cTableSize = (sizeof(astPCI_Iran)/sizeof(PHYSICAL_CHANNEL_INFO));
        break;

     default:
         *ppastPhysicalChannelInfoTable = astPCI_General;
         cTableSize = (sizeof(astPCI_General)/sizeof(PHYSICAL_CHANNEL_INFO));
         break;
    }

#endif
#else
#if ENABLE_DTMB
    if(IsDTMBInUse())
    {
        UNUSED(eCountry);
        *ppastPhysicalChannelInfoTable = astPCI_China;
        cTableSize = (sizeof(astPCI_China)/sizeof(PHYSICAL_CHANNEL_INFO));
    }
    else
#endif
#endif
    {

        switch(eCountry)
        {
        case E_AUSTRALIA:
             *ppastPhysicalChannelInfoTable = astPCI_Australia;
             cTableSize = (sizeof(astPCI_Australia)/sizeof(PHYSICAL_CHANNEL_INFO));
            break;
        case E_NEWZEALAND:
        case E_UK:
        case E_SPAIN:
        case E_HUNGARY:
        case E_MOROCCO:
            cTableSize = 0;
            break;

        case E_CROATIA:
            *ppastPhysicalChannelInfoTable = astPCI_Croatia;
             cTableSize = (sizeof(astPCI_Croatia)/sizeof(PHYSICAL_CHANNEL_INFO));
             break;

        case E_FRANCE:
            *ppastPhysicalChannelInfoTable = astPCI_France;
             cTableSize = (sizeof(astPCI_France)/sizeof(PHYSICAL_CHANNEL_INFO));
             break;
#if (ITALY_USE_EUROPEAN_VHF == FALSE)
        case E_ITALY:
            *ppastPhysicalChannelInfoTable = astPCI_ITALY;
             cTableSize = (sizeof(astPCI_ITALY)/sizeof(PHYSICAL_CHANNEL_INFO));
             break;
#endif
        case E_NORWAY:
            if(GetVHFBandWidth(E_NORWAY) == E_RF_CH_BAND_7MHz)// 7 Mhz
            {
                *ppastPhysicalChannelInfoTable = astPCI_Norway_VHF7;
                cTableSize = (sizeof(astPCI_Norway_VHF7)/sizeof(PHYSICAL_CHANNEL_INFO));
            }
            else if(GetVHFBandWidth(E_NORWAY) == E_RF_CH_BAND_8MHz) // 8 Mhz
            {
                *ppastPhysicalChannelInfoTable = astPCI_Norway_VHF8;
                cTableSize = (sizeof(astPCI_Norway_VHF8)/sizeof(PHYSICAL_CHANNEL_INFO));
            }
            break;

        case E_VIETNAM:
            *ppastPhysicalChannelInfoTable = astPCI_VietNam;
            cTableSize = (sizeof(astPCI_VietNam)/sizeof(PHYSICAL_CHANNEL_INFO));
            break;

        case E_IRAN:
            *ppastPhysicalChannelInfoTable = astPCI_Iran;
            cTableSize = (sizeof(astPCI_Iran)/sizeof(PHYSICAL_CHANNEL_INFO));
            break;

#if ENABLE_SBTVD_DTV_SYSTEM
        case E_BRAZIL:
            *ppastPhysicalChannelInfoTable = astPCI_Brazil;
            cTableSize = (sizeof(astPCI_Brazil)/sizeof(PHYSICAL_CHANNEL_INFO));
            break;

#endif
         default:
             *ppastPhysicalChannelInfoTable = astPCI_General;
             cTableSize = (sizeof(astPCI_General)/sizeof(PHYSICAL_CHANNEL_INFO));
             break;
        }

    }
//    printf("1 sizeof %bu:%bu \n",eCountry, cTableSize);

    return cTableSize;
}

BOOLEAN msAPI_DFT_Get_PHYSICAL_CHANNEL_NUMBER(U32 u32Frequency, U8 *u8RFIndex)
{
    BYTE i;
    MEMBER_COUNTRY eCountry;
    MS_TP_SETTING stTPSetting;
    S32 s32Offset;
    PHYSICAL_CHANNEL_INFO * pastPhysicalChannelInfoTable;
    BYTE cTableSize=0;

    eCountry = msAPI_CM_GetCountry();
    //UHF IV ~ V
    for(i=MApp_Get_MIN_UHF_PHYSICAL_CHANNEL_NUMBER(eCountry);i<=MApp_Get_MAX_UHF_PHYSICAL_CHANNEL_NUMBER();i++)
    {
        msAPI_DFT_GetTSSetting(i,&stTPSetting);
        s32Offset=stTPSetting.u32Frequency-u32Frequency;
        if(s32Offset>=-1000 && s32Offset <= 1000 )
        {
            *u8RFIndex=i;
            //printf("get RF index %lu(%lu) %bu\n",u32Frequency,stTPSetting.u32Frequency,i);
            return TRUE;
        }
    }
    //UHF S III
    if(!IsDTMBInUse())
    {
//#if ( ENABLE_DTMB_CHINA_APP ==0 && ENABLE_SBTVD_DTV_SYSTEM == 0 && ENABLE_DVB_TAIWAN_APP ==0)
    for(i=MIN_UHF_PHYSICAL_S_CHANNEL_NUMBER;i<=MAX_UHF_PHYSICAL_S_CHANNEL_NUMBER;i++)
    {
        msAPI_DFT_GetTSSetting(i,&stTPSetting);
        s32Offset=stTPSetting.u32Frequency-u32Frequency;
        if(s32Offset>=-1000 && s32Offset <= 1000 )
        {
            *u8RFIndex=i;
            printf("get RF index %lu(%lu) %u\n",u32Frequency,stTPSetting.u32Frequency,i);
            return TRUE;
        }
    }
    }
//#endif
    //VHF III ~ VHF S II
    cTableSize = GetPhysicalChannelInfoTableForVHF(eCountry, &pastPhysicalChannelInfoTable);
    for(i=0; i<cTableSize; i++)
    {
        s32Offset = DecompressFreq(pastPhysicalChannelInfoTable[i].wCompressedFrequency)-u32Frequency;
        if(s32Offset>=-1000 && s32Offset <= 1000 )
        {
            *u8RFIndex=pastPhysicalChannelInfoTable[i].cRFChannelNumber;
            printf("get RF index %lu(%lu) %u\n",u32Frequency,stTPSetting.u32Frequency,i);
            return TRUE;
        }

    }
    //printf("not get RF index %lu\n",u32Frequency);
    return FALSE;
}
void msAPI_SetCrossBandwidth(BOOLEAN bIsCross)
{
    _CrossBandwidth = bIsCross;
}

void msAPI_DFT_SetBandwidth(U8 u8BandWidth)
{
    _u8Terr_BandWidth = u8BandWidth;
}

U8 msAPI_DFT_GetBandwidth(void)
{
    return _u8Terr_BandWidth;
}

void msAPI_DFT_VHF_CrossBWFreq_SetFinishScanStatus(BOOLEAN bOneFreqScanFinished)
{
    _bDynamicBandScanFinished = bOneFreqScanFinished;
}

BOOLEAN msAPI_DFT_VHF_CrossBWFreq_GetFinishScanStatus(void)
{
    return _bDynamicBandScanFinished;
}

//#if (! ((ENABLE_DTMB_CHINA_APP)||( ENABLE_SBTVD_DTV_SYSTEM)))
static RF_CHANNEL_BANDWIDTH GetVHFBandWidth(MEMBER_COUNTRY eCountry)
{
    RF_CHANNEL_BANDWIDTH eBandWidth = E_RF_CH_BAND_8MHz;

    switch(eCountry)
    {
/*
     case E_FRANCE:
        eBandWidth = E_RF_CH_BAND_8MHz;
        break;
*/
     case E_NORWAY:
     case E_SWEDEN:
        if(_u8Terr_BandWidth == E_RF_CH_BAND_8MHz)
            eBandWidth = E_RF_CH_BAND_8MHz;
        else if(_u8Terr_BandWidth == E_RF_CH_BAND_7MHz)
            eBandWidth = E_RF_CH_BAND_7MHz;
        break;
     default:
        eBandWidth = E_RF_CH_BAND_7MHz;
        break;
    }

    return eBandWidth;
}
//#endif
#endif

