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

//****************************************************************************
//                          Header
//****************************************************************************
#include <string.h>
#include "datatype.h"
#include "MsCommon.h"
#include "msAPI_FreqTableCommon.h"

#if ENABLE_DVBC
#include "msAPI_FreqTableCADTV.h"

//****************************************************************************
//                          Definition
//****************************************************************************
#define DVBC_MAX_NIT_FREQ_NUM       50

//****************************************************************************
//                          Structure
//****************************************************************************
typedef struct
{
    U32 *pu32FreqTbl;
    U16 u16FreqTblSize;
    U16 u16CurrentFreqIndex;
}DVBC_BUILTIN_FREQ_TBL_INFO;

typedef struct
{
    U32 u32NewFreqTbl[DVBC_MAX_NIT_FREQ_NUM];
    U16 u16NewFreqTblSize;
    U16 u16NewFreqIndex;
}DVBC_NIT_FREQ_TBL_INFO;

//****************************************************************************
//                          Local variables
//****************************************************************************

/*sibelm_12082009 | Scan Modification: Channel Install modification according to Nordic spec v2.1*/
const U32 Ch_Freq_Nordic[]=
{
/*sibelm_22082009 | Denmark Field Test: 156MHz is added to Nordic Table*/
    114000,    122000,    130000,    138000,
    146000,    154000,    156000,  162000,
    170000,    178000,    186000,    194000,
    202000,    210000,   218000,    226000,
    234000,    242000,    250000,    258000,
    266000,    274000,    282000,    290000,
    298000,    306000,    314000,    322000,
    330000,    338000,    346000,    354000,
    362000,    370000,    378000,    386000,
    394000,    402000,    410000,    418000,
    426000,    434000,    442000,    450000,
    458000,    466000,    474000,    482000,
    490000,    498000,    506000,    514000,
    522000,    530000,    538000,    546000,
    554000,    562000,    570000,    578000,
    586000,    594000,    602000,    610000,
    618000,    626000,    634000,    642000,
    650000,    658000,    666000,    674000,
    682000,    690000,    698000,    706000,
    714000,    722000,    730000,    738000,
    746000,    754000,    762000,    770000,
    778000,    786000,    794000,    802000,
    810000,    818000,    826000,    834000,
    842000,    850000,    858000, NULL,
};


const U32 Ch_Freq_Switzerland[]=
{
//MidBand
     107500,     114000,       114500,     121500,
     122000,     128500,     130000,     135500,
     138000,     142500,     146000,     149500,
     154000,    156500,     162000,      163500,
     170000,    170500,     177500,      178000,
     184500,     186000,     191500,     194000,
     198500,     202000,        205500,     210000,
     212500,     218000,     219500,     226000,
     226500,
//Superband
     233500,    234000,     240500,      242000,
     247500,    250000,      254500,         258000,
     261500,    266000,     268500,      274000,
     275500,    282000,     282500,      289500,
     290000,    296500,      298000,

//Hyperband
     306000,     314000,     322000,     330000,
     338000,     346000,     354000,     362000,
     370000,     378000,     386000,     394000,
     402000,     410000,     418000,     426000,
     434000,     442000,     450000,     458000,
     466000,
//Band IV
     474000,     482000,     490000,     498000,
     506000,     514000,     522000,     530000,
     538000,     546000,     554000,     562000,
     570000,     578000,
//Band V
     586000,     594000,     602000,     610000,
     618000,     626000,     634000,     642000,
     650000,     658000,     666000,     674000,
     682000,     690000,     698000,     706000,
     714000,     722000,     730000,     738000,
     746000,     754000,     762000,     770000,
     778000,     786000,     794000,     802000,
     810000,     818000,     826000,     834000,
     842000,     850000,     858000,        NULL,
};

const U32 Ch_Freq_Turkey[] =
{
/*
    For testing
    121000,    482000,    490000,    498000,
    506000,    514000,    522000,    458000,
*/
//Midband
     107500,      113000,     114000,     121000,
     122000,     128500,     130000,     135500,
     138000,      142500,     146000,     149500,
     154000,      156500,     162000,     163500,
     170000,     170500,
//Band III
     177500,     178000,       184500,     186000,
     191500,     194000,       198500,     202000,
     205500,     210000,       212500,     218000,
     219500,     226000,     226500,     227000,
//Superband
     233500,     234000,     240500,     242000,
     247500,     250000,       254500,     258000,
     261500,     266000,     268500,     274000,
     275500,     282000,     282500,     289500,
     290000,     296500,     298000,
//Hyperband
     306000,     314000,     322000,     330000,
     338000,     346000,     354000,     362000,
     370000,     378000,     386000,     394000,
     402000,     410000,     418000,     426000,
     434000,     442000,     450000,     458000,
     466000,
//Band IV
     474000,     482000,     490000,     498000,
     506000,     514000,     522000,     530000,
     538000,     546000,     554000,     562000,
     570000,     578000,
//Band V
     586000,     594000,     602000,     610000,
     618000,     626000,     634000,     642000,
     650000,     658000,     666000,     674000,
     682000,     690000,     698000,     706000,
     714000,     722000,     730000,     738000,
     746000,     754000,     762000,     770000,
     778000,     786000,     794000,     802000,
     810000,     818000,     826000,     834000,
     842000,     850000,     858000,        NULL,

};

const U32 Ch_Freq_Turkey_All[] =
{
	113000,    114000,    115000,    116000,
    117000,    118000,    119000,    120000,
    121000,    122000,    123000,    124000,
    125000,    126000,    127000,    128000,
    129000,    130000,    131000,    132000,
    133000,    134000,    135000,    136000,
    137000,    138000,    139000,    140000,
    141000,    142000,    143000,    144000,
    145000,    146000,    147000,    148000,
    149000,    150000,    151000,    152000,
    153000,    154000,    155000,    156000,
    157000,    158000,    159000,    160000,
    161000,    162000,    163000,    164000,
    165000,    166000,    167000,    168000,
    169000,    170000,    171000,    172000,
    173000,    174000,    175000,    176000,
    177000,    178000,    179000,    180000,
    181000,    182000,    183000,    184000,
    185000,    186000,    187000,    188000,
    189000,    190000,    191000,    192000,
    193000,    194000,    195000,    196000,
    197000,    198000,    199000,    200000,
    201000,    202000,    203000,    204000,
    205000,    206000,    207000,    208000,
    209000,    210000,    211000,    212000,
    213000,    214000,    215000,    216000,
    217000,    218000,    219000,    220000,
    221000,    222000,    223000,    224000,
    225000,    226000,    227000,    228000,
    229000,    230000,    231000,    232000,
    233000,    234000,    235000,    236000,
    237000,    238000,    239000,    240000,
    241000,    242000,    243000,    244000,
    245000,    246000,    247000,    248000,
    249000,    250000,    251000,    252000,
    253000,    254000,    255000,    256000,
    257000,    258000,    259000,    260000,
    261000,    262000,    263000,    264000,
    265000,    266000,    267000,    268000,
    269000,    270000,    271000,    272000,
    273000,    274000,    275000,    276000,
    277000,    278000,    279000,    280000,
    281000,    282000,    283000,    284000,
    285000,    286000,    287000,    288000,
    289000,    290000,    291000,    292000,
    293000,    294000,    295000,    296000,
    297000,    298000,    299000,    300000,
    301000,    302000,    303000,    304000,
    305000,    306000,    307000,    308000,
    309000,    310000,    311000,    312000,
    313000,    314000,    315000,    316000,
    317000,    318000,    319000,    320000,
    321000,    322000,    323000,    324000,
    325000,    326000,    327000,    328000,
    329000,    330000,    331000,    332000,
    333000,    334000,    335000,    336000,
    337000,    338000,    339000,    340000,
    341000,    342000,    343000,    344000,
    345000,    346000,    347000,    348000,
    349000,    350000,    351000,    352000,
    353000,    354000,    355000,    356000,
    357000,    358000,    359000,    360000,
    361000,    362000,    363000,    364000,
    365000,    366000,    367000,    368000,
    369000,    370000,    371000,    372000,
    373000,    374000,    375000,    376000,
    377000,    378000,    379000,    380000,
    381000,    382000,    383000,    384000,
    385000,    386000,    387000,    388000,
    389000,    390000,    391000,    392000,
    393000,    394000,    395000,    396000,
    397000,    398000,    399000,    400000,
    401000,    402000,    403000,    404000,
    405000,    406000,    407000,    408000,
    409000,    410000,    411000,    412000,
    413000,    414000,    415000,    416000,
    417000,    418000,    419000,    420000,
    421000,    422000,    423000,    424000,
    425000,    426000,    427000,    428000,
    429000,    430000,    431000,    432000,
    433000,    434000,    435000,    436000,
    437000,    438000,    439000,    440000,
    441000,    442000,    443000,    444000,
    445000,    446000,    447000,    448000,
    449000,    450000,    451000,    452000,
    453000,    454000,    455000,    456000,
    457000,    458000,    459000,    460000,
    461000,    462000,    463000,    464000,
    465000,    466000,    467000,    468000,
    469000,    470000,    471000,    472000,
    473000,    474000,    475000,    476000,
    477000,    478000,    479000,    480000,
    481000,    482000,    483000,    484000,
    485000,    486000,    487000,    488000,
    489000,    490000,    491000,    492000,
    493000,    494000,    495000,    496000,
    497000,    498000,    499000,    500000,
    501000,    502000,    503000,    504000,
    505000,    506000,    507000,    508000,
    509000,    510000,    511000,    512000,
    513000,    514000,    515000,    516000,
    517000,    518000,    519000,    520000,
    521000,    522000,    523000,    524000,
    525000,    526000,    527000,    528000,
    529000,    530000,    531000,    532000,
    533000,    534000,    535000,    536000,
    537000,    538000,    539000,    540000,
    541000,    542000,    543000,    544000,
    545000,    546000,    547000,    548000,
    549000,    550000,    551000,    552000,
    553000,    554000,    555000,    556000,
    557000,    558000,    559000,    560000,
    561000,    562000,    563000,    564000,
    565000,    566000,    567000,    568000,
    569000,    570000,    571000,    572000,
    573000,    574000,    575000,    576000,
    577000,    578000,    579000,    580000,
    581000,    582000,    583000,    584000,
    585000,    586000,    587000,    588000,
    589000,    590000,    591000,    592000,
    593000,    594000,    595000,    596000,
    597000,    598000,    599000,    600000,
    601000,    602000,    603000,    604000,
    605000,    606000,    607000,    608000,
    609000,    610000,    611000,    612000,
    613000,    614000,    615000,    616000,
    617000,    618000,    619000,    620000,
    621000,    622000,    623000,    624000,
    625000,    626000,    627000,    628000,
    629000,    630000,    631000,    632000,
    633000,    634000,    635000,    636000,
    637000,    638000,    639000,    640000,
    641000,    642000,    643000,    644000,
    645000,    646000,    647000,    648000,
    649000,    650000,    651000,    652000,
    653000,    654000,    655000,    656000,
    657000,    658000,    659000,    660000,
    661000,    662000,    663000,    664000,
    665000,    666000,    667000,    668000,
    669000,    670000,    671000,    672000,
    673000,    674000,    675000,    676000,
    677000,    678000,    679000,    680000,
    681000,    682000,    683000,    684000,
    685000,    686000,    687000,    688000,
    689000,    690000,    691000,    692000,
    693000,    694000,    695000,    696000,
    697000,    698000,    699000,    700000,
    701000,    702000,    703000,    704000,
    705000,    706000,    707000,    708000,
    709000,    710000,    711000,    712000,
    713000,    714000,    715000,    716000,
    717000,    718000,    719000,    720000,
    721000,    722000,    723000,    724000,
    725000,    726000,    727000,    728000,
    729000,    730000,    731000,    732000,
    733000,    734000,    735000,    736000,
    737000,    738000,    739000,    740000,
    741000,    742000,    743000,    744000,
    745000,    746000,    747000,    748000,
    749000,    750000,    751000,    752000,
    753000,    754000,    755000,    756000,
    757000,    758000,    759000,    760000,
    761000,    762000,    763000,    764000,
    765000,    766000,    767000,    768000,
    769000,    770000,    771000,    772000,
    773000,    774000,    775000,    776000,
    777000,    778000,    779000,    780000,
    781000,    782000,    783000,    784000,
    785000,    786000,    787000,    788000,
    789000,    790000,    791000,    792000,
    793000,    794000,    795000,    796000,
    797000,    798000,    799000,    800000,
    801000,    802000,    803000,    804000,
    805000,    806000,    807000,    808000,
    809000,    810000,    811000,    812000,
    813000,    814000,    815000,    816000,
    817000,    818000,    819000,    820000,
    821000,    822000,    823000,    824000,
    825000,    826000,    827000,    828000,
    829000,    830000,    831000,    832000,
    833000,    834000,    835000,    836000,
    837000,    838000,    839000,    840000,
    841000,    842000,    843000,    844000,
    845000,    846000,    847000,    848000,
    849000,    850000,    851000,    852000,
    853000,    854000,    855000,    856000,
    857000,    858000,	  NULL,

};

const U32 Ch_Freq_China[] =
{
//Z1~Z7
     115000,     123000,     131000,     139000,
     147000,     155000,     163000,
//DS6~DS12
     171000,     179000,     187000,     195000,
     203000,     211000,     219000,
//Z8~Z37
     227000,     235000,     243000,     251000,
     259000,     267000,     275000,     283000,
     291000,     299000,     307000,     315000,
     323000,     331000,     339000,     347000,
     355000,     363000,     371000,     379000,
     387000,     395000,     403000,     411000,
     419000,     427000,     435000,     443000,
     451000,     459000,
//ZZ
     466000,
//DS13~DS24
     474000,     482000,     490000,     498000,
     506000,     514000,     522000,     530000,
     538000,     546000,     554000,     562000,
//Z38~Z42
     570000,     578000,     586000,     594000,
     602000,
//DS25~DS56
     610000,     618000,     626000,     634000,
     642000,     650000,     658000,     666000,
     674000,     682000,     690000,     698000,
     706000,     714000,     722000,     730000,
     738000,     746000,     754000,     762000,
     770000,     778000,     786000,     794000,
     802000,     810000,     818000,     826000,
     834000,     842000,     850000,     858000,
     NULL,

};

//****************************************************************************
//                          Global variables
//****************************************************************************
DVBC_BUILTIN_FREQ_TBL_INFO stDVBCBuiltInFreqTbl;
DVBC_NIT_FREQ_TBL_INFO stDVBCNitFreqTbl;
//****************************************************************************
//                          Private function prototype
//****************************************************************************

//****************************************************************************
//                          Private functions
//****************************************************************************


//****************************************************************************
//                          Global functions
//****************************************************************************
void msAPI_DCFT_SelectBuiltInFreqTableforCountry(EN_OSD_COUNTRY_SETTING eCountry)
{
    switch(eCountry)
    {
        case OSD_COUNTRY_BELGIUM:
        case OSD_COUNTRY_CROATIA:
        case OSD_COUNTRY_ESTONIA:
        case OSD_COUNTRY_SLOVENIA:
        case OSD_COUNTRY_SPAIN:
        case OSD_COUNTRY_FINLAND:
        case OSD_COUNTRY_SWEDEN:
        case OSD_COUNTRY_DENMARK:
        case OSD_COUNTRY_NORWAY:
        {
            stDVBCBuiltInFreqTbl.pu32FreqTbl= (U32 *)Ch_Freq_Nordic;
            stDVBCBuiltInFreqTbl.u16FreqTblSize=sizeof(Ch_Freq_Nordic)/sizeof(U32);
            stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = 0;
        }
        break;

        case OSD_COUNTRY_SWITZERLAND:
        {
            stDVBCBuiltInFreqTbl.pu32FreqTbl = (U32 *)Ch_Freq_Switzerland;
            stDVBCBuiltInFreqTbl.u16FreqTblSize=sizeof(Ch_Freq_Switzerland)/sizeof(U32);
            stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = 0;
        }
        break;

        case OSD_COUNTRY_TURKEY:
        case OSD_COUNTRY_GERMANY:
        {
            stDVBCBuiltInFreqTbl.pu32FreqTbl = (U32 *)Ch_Freq_Turkey;
            stDVBCBuiltInFreqTbl.u16FreqTblSize=sizeof(Ch_Freq_Turkey)/sizeof(U32);
            stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = 0;
        }
        break;

        case OSD_COUNTRY_NETHERLANDS:
        {
            stDVBCBuiltInFreqTbl.pu32FreqTbl = (U32 *)Ch_Freq_Turkey_All;
            stDVBCBuiltInFreqTbl.u16FreqTblSize=sizeof(Ch_Freq_Turkey_All)/sizeof(U32);
            stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = 0;
        }
        break;
        case OSD_COUNTRY_CHINA:
        {
            stDVBCBuiltInFreqTbl.pu32FreqTbl = (U32 *)Ch_Freq_China;
            stDVBCBuiltInFreqTbl.u16FreqTblSize=sizeof(Ch_Freq_China)/sizeof(U32);
            stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = 0;
        }
        break;

        default:
            stDVBCBuiltInFreqTbl.pu32FreqTbl = (U32 *)Ch_Freq_Turkey;
            stDVBCBuiltInFreqTbl.u16FreqTblSize=sizeof(Ch_Freq_Turkey)/sizeof(U32);
            stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = 0;
        break;
    }
}

U32 msAPI_DCFT_GetBuiltInNextFreq(U32 u32Freq)
{
    U16 u16i;
    if ((NULL == stDVBCBuiltInFreqTbl.pu32FreqTbl) ||(0 == stDVBCBuiltInFreqTbl.u16FreqTblSize))
    {
        return NULL;
    }

    if (u32Freq)
    {
        for (u16i=0;u16i<stDVBCBuiltInFreqTbl.u16FreqTblSize;u16i++)
        {
            if (NULL == stDVBCBuiltInFreqTbl.pu32FreqTbl[u16i])
                return NULL;
            if (stDVBCBuiltInFreqTbl.pu32FreqTbl[u16i]>u32Freq)
            {
                stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = u16i+1;
                return stDVBCBuiltInFreqTbl.pu32FreqTbl[u16i];
            }
        }
    }
    else
    {
        if ((stDVBCBuiltInFreqTbl.u16CurrentFreqIndex+1)<stDVBCBuiltInFreqTbl.u16FreqTblSize)
        {
            return stDVBCBuiltInFreqTbl.pu32FreqTbl[stDVBCBuiltInFreqTbl.u16CurrentFreqIndex++];
        }
    }
    return NULL;
}

BOOLEAN msAPI_DCFT_IsThisFreqInBuiltinFreqTbl(U32 u32Freq)
{
    U16 u16i;

    if ((NULL == stDVBCBuiltInFreqTbl.pu32FreqTbl) ||(0 == stDVBCBuiltInFreqTbl.u16FreqTblSize))
    {
        return FALSE;
    }

    for(u16i=0;u16i<stDVBCBuiltInFreqTbl.u16FreqTblSize;u16i++)
    {
        if (NULL == stDVBCBuiltInFreqTbl.pu32FreqTbl[u16i])
        {
            return FALSE;
        }
        if (stDVBCBuiltInFreqTbl.pu32FreqTbl[u16i] == u32Freq)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void msAPI_DCFT_ResetNITNewFreqTbl(void)
{
    memset(&stDVBCNitFreqTbl, 0 , sizeof(DVBC_NIT_FREQ_TBL_INFO));
}

void msAPI_DCFT_SetFreqToNITNewFreqTbl(U32 u32Freq)
{
    if ((stDVBCNitFreqTbl.u16NewFreqTblSize) < DVBC_MAX_NIT_FREQ_NUM)
    {
        stDVBCNitFreqTbl.u32NewFreqTbl[stDVBCNitFreqTbl.u16NewFreqTblSize++] = u32Freq;
    }
}

U32 msAPI_DCFT_GetNITNextFreq(void)
{
    if (0 == stDVBCNitFreqTbl.u16NewFreqTblSize)
    {
        return NULL;
    }
    if ((stDVBCNitFreqTbl.u16NewFreqIndex)<stDVBCNitFreqTbl.u16NewFreqTblSize)
    {
        return stDVBCNitFreqTbl.u32NewFreqTbl[stDVBCNitFreqTbl.u16NewFreqIndex++];
    }
    else
    {
        return NULL;
    }
}

U8 msAPI_DCFT_CalculatePercentTbl(void)
{
    U8 OutputVal = 0;
    if(stDVBCBuiltInFreqTbl.u16CurrentFreqIndex > stDVBCBuiltInFreqTbl.u16FreqTblSize)
        OutputVal = (U8)(((stDVBCBuiltInFreqTbl.u16CurrentFreqIndex + stDVBCNitFreqTbl.u16NewFreqIndex) *100) /
        (stDVBCBuiltInFreqTbl.u16FreqTblSize +stDVBCNitFreqTbl.u16NewFreqTblSize));
    else
        OutputVal = (U8)((stDVBCBuiltInFreqTbl.u16CurrentFreqIndex* 100) /
        (stDVBCBuiltInFreqTbl.u16FreqTblSize +stDVBCNitFreqTbl.u16NewFreqTblSize));
    #if 0
    printf("#########################################\n");
    printf("#### stDVBCBuiltInFreqTbl.u16CurrentFreqIndex = %d\n",stDVBCBuiltInFreqTbl.u16CurrentFreqIndex);
    printf("#### stDVBCNitFreqTbl.u16NewFreqIndex = %d\n",stDVBCNitFreqTbl.u16NewFreqIndex);
    printf("#### stDVBCBuiltInFreqTbl.u16FreqTblSize = %d\n",stDVBCBuiltInFreqTbl.u16FreqTblSize);
    printf("#### stDVBCNitFreqTbl.u16NewFreqTblSize = %d\n",stDVBCNitFreqTbl.u16NewFreqTblSize);
    printf("####  OutputVal = %d\n", OutputVal);
    #endif
    return OutputVal;
}

#endif
#endif

