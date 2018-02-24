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

#ifndef _MAPP_ZUI_APICHINESEIMELIB_H
#define _MAPP_ZUI_APICHINESEIMELIB_H

#define PINYIN_ARRAY_LENGTH     402    // PinYinArray[][7] total PINYIN numbers


// Corresponding to PinYinArray. For example 'a' has {"a"}, {"ai"}, {"an"}, {"ang"}, {"ao"}, then PinYinNumber[0] = 5
U8 PinYinNumber[]=
{
    5, 16, 34, 21, 4, 9, 19, 19, 0, 14, 18, 25, 20, 24, 2, 17, 14, 14, 34, 19, 0, 0, 9, 14, 15, 36,
};


U8 PinYinArray[][7]=
{
    {"a"}, {"ai"}, {"an"}, {"ang"}, {"ao"},
    {"ba"}, {"bai"}, {"ban"}, {"bang"}, {"bao"}, {"bei"}, {"ben"}, {"beng"}, {"bi"}, {"bian"}, {"biao"}, {"bie"}, {"bin"}, {"bing"}, {"bo"}, {"bu"},
    {"ca"}, {"cai"}, {"can"}, {"cang"}, {"cao"}, {"ce"}, {"cen"}, {"ceng"}, {"cha"}, {"chai"}, {"chan"}, {"chang"}, {"chao"}, {"che"}, {"chen"}, {"cheng"}, {"chi"}, {"chong"}, {"chou"}, {"chu"}, {"chuai"}, {"chuan"}, {"chuang"}, {"chui"}, {"chun"}, {"chuo"}, {"ci"}, {"cong"}, {"cou"}, {"cu"}, {"cuan"}, {"cui"}, {"cun"}, {"cuo"},
    {"da"}, {"dai"}, {"dan"}, {"dang"}, {"dao"}, {"de"}, {"deng"}, {"di"}, {"dia"}, {"dian"}, {"diao"}, {"die"}, {"ding"}, {"diu"}, {"dong"}, {"dou"}, {"du"}, {"duan"}, {"dui"}, {"dun"}, {"duo"},
    {"e"}, {"ei"}, {"en"}, {"er"},
    {"fa"}, {"fan"}, {"fang"}, {"fei"}, {"fen"}, {"feng"}, {"fo"}, {"fou"}, {"fu"},
    {"ga"}, {"gai"}, {"gan"}, {"gang"}, {"gao"}, {"ge"}, {"gei"}, {"gen"}, {"geng"}, {"gong"}, {"gou"}, {"gu"}, {"gua"}, {"guai"}, {"guan"}, {"guang"}, {"gui"}, {"gun"}, {"guo"},
    {"ha"}, {"hai"}, {"han"}, {"hang"}, {"hao"}, {"he"}, {"hei"}, {"hen"}, {"heng"}, {"hong"}, {"hou"}, {"hu"}, {"hua"}, {"huai"}, {"huan"}, {"huang"}, {"hui"}, {"hun"}, {"huo"},

    {"ji"}, {"jia"}, {"jian"}, {"jiang"}, {"jiao"}, {"jie"}, {"jin"}, {"jing"}, {"jiong"}, {"jiu"}, {"ju"}, {"juan"}, {"jue"}, {"jun"},
    {"ka"}, {"kai"}, {"kan"}, {"kang"}, {"kao"}, {"ke"}, {"ken"}, {"keng"}, {"kong"}, {"kou"}, {"ku"}, {"kua"}, {"kuai"}, {"kuan"}, {"kuang"}, {"kui"}, {"kun"}, {"kuo"},
    {"la"}, {"lai"}, {"lan"}, {"lang"}, {"lao"}, {"le"}, {"lei"}, {"leng"}, {"li"}, {"lia"}, {"lian"}, {"liang"}, {"liao"}, {"lie"}, {"lin"}, {"ling"}, {"liu"}, {"long"}, {"lou"}, {"lu"}, {"luan"}, {"lue"}, {"lun"}, {"luo"}, {"lv"},
    {"m"}, {"ma"}, {"mai"}, {"man"}, {"mang"}, {"mao"}, {"me"}, {"mei"}, {"men"}, {"meng"}, {"mi"}, {"mian"}, {"miao"}, {"mie"}, {"min"}, {"ming"}, {"miu"}, {"mo"}, {"mou"}, {"mu"},
    {"na"}, {"nai"}, {"nan"}, {"nang"}, {"nao"}, {"ne"}, {"nei"}, {"nen"}, {"neng"}, {"ni"}, {"nian"}, {"niang"}, {"niao"}, {"nie"}, {"nin"}, {"ning"}, {"niu"}, {"nong"}, {"nou"}, {"nu"}, {"nuan"}, {"nue"}, {"nuo"}, {"nv"},
    {"o"}, {"ou"},
    {"pa"}, {"pai"}, {"pan"}, {"pang"}, {"pao"}, {"pei"}, {"pen"}, {"peng"}, {"pi"}, {"pian"}, {"piao"}, {"pie"}, {"pin"}, {"ping"}, {"po"}, {"pou"}, {"pu"},
    {"qi"}, {"qia"}, {"qian"}, {"qiang"}, {"qiao"}, {"qie"}, {"qin"}, {"qing"}, {"qiong"}, {"qiu"}, {"qu"}, {"quan"}, {"que"}, {"qun"},
    {"ran"}, {"rang"}, {"rao"}, {"re"}, {"ren"}, {"reng"}, {"ri"}, {"rong"}, {"rou"}, {"ru"}, {"ruan"}, {"rui"}, {"run"}, {"ruo"},
    {"sa"}, {"sai"}, {"san"}, {"sang"}, {"sao"}, {"se"}, {"sen"}, {"seng"}, {"sha"}, {"shai"}, {"shan"}, {"shang"}, {"shao"}, {"she"}, {"shen"}, {"sheng"}, {"shi"}, {"shou"}, {"shu"}, {"shua"}, {"shuai"}, {"shuan"}, {"shuang"}, {"shui"}, {"shun"}, {"shuo"}, {"si"}, {"song"}, {"sou"}, {"su"}, {"suan"}, {"sui"}, {"sun"}, {"suo"},
    {"ta"}, {"tai"}, {"tan"}, {"tang"}, {"tao"}, {"te"}, {"teng"}, {"ti"}, {"tian"}, {"tiao"}, {"tie"}, {"ting"}, {"tong"}, {"tou"}, {"tu"}, {"tuan"}, {"tui"}, {"tun"}, {"tuo"},


    {"wa"}, {"wai"}, {"wan"}, {"wang"}, {"wei"}, {"wen"}, {"weng"}, {"wo"}, {"wu"},
    {"xi"}, {"xia"}, {"xian"}, {"xiang"}, {"xiao"}, {"xie"}, {"xin"}, {"xing"}, {"xiong"}, {"xiu"}, {"xu"}, {"xuan"}, {"xue"}, {"xun"},
    {"ya"}, {"yan"}, {"yang"}, {"yao"}, {"ye"}, {"yi"}, {"yin"}, {"ying"}, {"yo"}, {"yong"}, {"you"}, {"yu"}, {"yuan"}, {"yue"}, {"yun"},
    {"za"}, {"zai"}, {"zan"}, {"zang"}, {"zao"}, {"ze"}, {"zei"}, {"zen"}, {"zeng"}, {"zha"}, {"zhai"}, {"zhan"}, {"zhang"}, {"zhao"}, {"zhe"}, {"zhen"}, {"zheng"}, {"zhi"}, {"zhong"}, {"zhou"}, {"zhu"}, {"zhua"}, {"zhuai"}, {"zhuan"}, {"zhuang"}, {"zhui"}, {"zhun"}, {"zhuo"}, {"zi"}, {"zong"}, {"zou"}, {"zu"}, {"zuan"}, {"zui"}, {"zun"}, {"zuo"},
};


// Corresponding to PinYinArray. For example ¡®a¡¯ has six words  °¢ °¡ ß¹ àÄ ëç ï¹, then WordsNumber[0] = 6
U8 WordsNumber[]=
{
    6, 22, 18, 3, 23, 26, 10, 21, 14, 28, 26, 8, 9, 56, 26, 14, 5, 16, 14, 34, 19, 3, 11, 12, 6, 9, 6, 3, 4, 25, 8, 25, 27, 15, 8, 21,
    26, 38, 12, 17, 29, 6, 12, 7, 9, 10, 6, 17, 12, 4, 12, 8, 15, 5, 15, 17, 20, 30, 9, 16, 5, 13, 39, 1, 26, 12, 15, 18, 2, 19, 13,
    24, 9, 9, 15, 20, 32, 1, 4, 13, 10, 26, 16, 30, 20, 21, 1, 2, 83, 10, 11, 24, 12, 19, 35, 1, 6, 11, 19, 21, 43, 12, 4, 20, 7, 28,
    7, 18, 3, 11, 31, 8, 20, 28, 2, 4, 8, 17, 15, 45, 13, 6, 29, 25, 38, 11, 21, 104, 36, 68, 24, 46, 42, 34, 40, 4, 26, 53, 15, 28,
    15, 7, 13, 13, 10, 8, 33, 6, 3, 7, 10, 12, 6, 11, 3, 16, 28, 11, 5, 13, 12, 22, 12, 19, 7, 19, 5, 77, 1, 26, 19, 21, 13, 24, 27,
    21, 17, 16, 41, 11, 3, 8, 28, 21, 1, 15, 9, 18, 10, 26, 2, 27, 7, 19, 27, 14, 16, 6, 16, 12, 2, 33, 9, 22, 12, 10, 10, 5, 13, 2,
    2, 2, 1, 21, 14, 2, 6, 14, 1, 10, 8, 6, 1, 7, 1, 3, 7, 4, 2, 11, 11, 9, 16, 12, 12, 15, 3, 18, 44, 11, 12, 6, 10, 14, 15, 3, 25, 68,
    7, 44, 21, 29, 13, 23, 23, 9, 23, 34, 22, 11, 4, 7, 7, 6, 3, 16, 2, 1, 15, 6, 20, 3, 8, 2, 4, 7, 5, 9, 6, 9, 7, 1, 1, 18, 3, 33, 14,
    19, 20, 29, 17, 65, 13, 47, 3, 6, 4, 4, 5, 4, 10, 34, 16, 14, 22, 4, 18, 8, 17, 19, 18, 26, 26, 17, 5, 5, 24, 13, 16, 5, 17, 20,
    5, 16, 5, 8, 9, 24, 10, 3, 28, 14, 60, 17, 5, 17, 54, 76, 21, 48, 30, 30, 39, 17, 23, 8, 18, 34, 26, 12, 32, 29, 67, 25, 33, 24,
    106, 33, 39, 2, 25, 43, 93, 35, 19, 24, 6, 10, 10, 6, 15, 14, 1, 2, 9, 24, 9, 20, 24, 17, 22, 33, 20, 76, 17, 24, 48, 3, 1, 10,
    9, 11, 5, 20, 38, 10, 9, 11, 5, 6, 5, 16,
};


#define WORDS_TOTAL_NUMBER     6983

U16 WordsUnicode[]=
{
// a  °¡          °¢          ß¹          àÄ          ëç          ï¹
    0x554a,  0x963f,  0x5416,  0x55c4,  0x814c,  0x9515,
// ai  °£          °¤          °¥          °¦          °§          °¨          °©          °ª          °«          °¬          °­          °®          °¯          Þß          àÈ          àÉ          æÈ          è¨          êÓ          íÁ          ïÍ          ö°
    0x57c3,  0x6328,  0x54ce,  0x5509,  0x54c0,  0x7691,  0x764c,  0x853c,  0x77ee,  0x827e,  0x788d,  0x7231,  0x9698,  0x6371,  0x55f3,  0x55cc,  0x5ad2,  0x7477,  0x66a7,  0x7839,  0x953f,  0x972d,
// an  °°          °±          °²          °³          °´          °µ          °¶          °·          °¸          ÚÏ          Ûû          Þî          áí          âÖ          èñ          ï§          ðÆ          ÷ö
    0x978d,  0x6c28,  0x5b89,  0x4ffa,  0x6309,  0x6697,  0x5cb8,  0x80fa,  0x6848,  0x8c19,  0x57ef,  0x63de,  0x72b4,  0x5eb5,  0x6849,  0x94f5,  0x9e4c,  0x9eef,
// ang  °¹          °º          °»
    0x80ae,  0x6602,  0x76ce,
// ao  °¼          °½          °¾          °¿          °À          °Á          °Â          °Ã          °Ä          Ûê          ÞÖ          à»          á®          âÚ          åÛ          æÁ          æñ          éá          ñú          òü          öË          ÷¡          ÷é
    0x51f9,  0x6556,  0x71ac,  0x7ff1,  0x8884,  0x50b2,  0x5965,  0x61ca,  0x6fb3,  0x5773,  0x62d7,  0x55f7,  0x5c99,  0x5ed2,  0x9068,  0x5aaa,  0x9a9c,  0x7352,  0x8071,  0x87af,  0x93ca,  0x9ccc,  0x93d6,
// ba  °Å          °Æ          °Ç          °È          °É          °Ê          °Ë          °Ì          °Í          °Î          °Ï          °Ð          °Ñ          °Ò          °Ó          °Ô          °Õ          °Ö          ÜØ          ÝÃ          á±          å±          îÙ          ôÎ          öÑ          ÷É
    0x82ad,  0x634c,  0x6252,  0x53ed,  0x5427,  0x7b06,  0x516b,  0x75a4,  0x5df4,  0x62d4,  0x8dcb,  0x9776,  0x628a,  0x8019,  0x575d,  0x9738,  0x7f62,  0x7238,  0x8307,  0x83dd,  0x5c9c,  0x705e,  0x94af,  0x7c91,  0x9c85,  0x9b43,
// bai  °×          °Ø          °Ù          °Ú          °Û          °Ü          °Ý          °Þ          Þã          êþ
    0x767d,  0x67cf,  0x767e,  0x6446,  0x4f70,  0x8d25,  0x62dc,  0x7a17,  0x636d,  0x63b0,
// ban  °ß          °à          °á          °â          °ã          °ä          °å          °æ          °ç          °è          °é          °ê          °ë          °ì          °í          Úæ          Ûà          îÓ          ñ£          ñ­          ô²
    0x6591,  0x73ed,  0x642c,  0x6273,  0x822c,  0x9881,  0x677f,  0x7248,  0x626e,  0x62cc,  0x4f34,  0x74e3,  0x534a,  0x529e,  0x7eca,  0x962a,  0x5742,  0x94a3,  0x7622,  0x764d,  0x8228,
// bang  °î          °ï          °ð          °ñ          °ò          °ó          °ô          °õ          °ö          °÷          °ø          °ù          Ýò          äº
    0x90a6,  0x5e2e,  0x6886,  0x699c,  0x8180,  0x7ed1,  0x68d2,  0x78c5,  0x868c,  0x9551,  0x508d,  0x8c24,  0x84a1,  0x6d5c,
// bao  °ú          °û          °ü          °ý          °þ          ±¡          ±¢          ±£          ±¤          ±¥          ±¦          ±§          ±¨          ±©          ±ª          ±«          ±¬          ÅÚ          ÆØ          ÆÙ          Ùè          Ýá          æß          ìÒ          ð±          ñÙ          õÀ          öµ
    0x82de,  0x80de,  0x5305,  0x8912,  0x5265,  0x8584,  0x96f9,  0x4fdd,  0x5821,  0x9971,  0x5b9d,  0x62b1,  0x62a5,  0x66b4,  0x8c79,  0x9c8d,  0x7206,  0x70ae,  0x66dd,  0x7011,  0x52f9,  0x8446,  0x5b62,  0x7172,  0x9e28,  0x8913,  0x8db5,  0x9f85,
// bei  ±­          ±®          ±¯          ±°          ±±          ±²          ±³          ±´          ±µ          ±¶          ±·          ±¸          ±¹          ±º          ±»          ØÃ          Úé          Úý          Ýí          ßÂ          ã£          íÕ          ðÇ          ñØ          öÍ          ÷¹
    0x676f,  0x7891,  0x60b2,  0x5351,  0x5317,  0x8f88,  0x80cc,  0x8d1d,  0x94a1,  0x500d,  0x72c8,  0x5907,  0x60eb,  0x7119,  0x88ab,  0x5b5b,  0x9642,  0x90b6,  0x84d3,  0x5457,  0x6096,  0x789a,  0x9e4e,  0x8919,  0x943e,  0x97b4,
// ben  ±¼          ±½          ±¾          ±¿          º»          ÛÎ          ÛÐ          ï¼
    0x5954,  0x82ef,  0x672c,  0x7b28,  0x592f,  0x755a,  0x574c,  0x951b,
// beng  °ö          ±À          ±Á          ±Â          ±Ã          ±Ä          ±Å          àÔ          ê´
    0x868c,  0x5d29,  0x7ef7,  0x752d,  0x6cf5,  0x8e66,  0x8ff8,  0x5623,  0x750f,
// bi  ±Æ          ±Ç       ±È       ±É        ±Ê        ±Ë        ±Ì        ±Í        ±Î        ±Ï        ±Ð        ±Ñ        ±Ò        ±Ó        ±Ô        ±Õ        ±Ö        ±×        ±Ø        ±Ù        ±Ú
    0x903c,  0x9f3b,  0x6bd4,  0x9119,  0x7b14,  0x5f7c,  0x78a7,  0x84d6,  0x853d,  0x6bd5,  0x6bd9,  0x6bd6,  0x5e01,  0x5e87,  0x75f9,  0x95ed,  0x655d,  0x5f0a,  0x5fc5,  0x8f9f,  0x58c1,
//  ±Û          ±Ü          ±Ý          Ø°        ÙÂ       ÜÅ        Üê        Ý©        ÝÉ        Þµ       ßÁ       ßÙ          áù       âØ        ã¹          ää        å¨      åö       åþ          æ¾       æÔ          èµ     êÚ          î¢       î¯          îé      ïõ        ñÔ        óÙ        óë        ó÷        ô°       ôÅ        õÏ          ÷Â
    0x81c2,  0x907f,  0x965b,  0x5315,  0x4ffe,  0x8298,  0x835c,  0x8378,  0x8406,  0x859c,  0x5421,  0x54d4,  0x72f4,  0x5eb3,  0x610e,  0x6ed7,  0x6fde,  0x5f3c,  0x59a3,  0x5a62,  0x5b16,  0x74a7,  0x8d32,  0x7765,  0x7540,  0x94cb,  0x79d5,  0x88e8,  0x7b5a,  0x7b85,  0x7be6,  0x822d,  0x895e,  0x8df8,  0x9ac0,
// bian  ±Þ          ±ß          ±à          ±á          ±â          ±ã          ±ä          ±å          ±æ          ±ç          ±è          ±é          ØÒ          ÛÍ          ÜÐ          âí          ãê          çÂ          ìÔ          í¾          íÜ          ñ¹          ñÛ          òù          óÖ          öý
    0x97ad,  0x8fb9,  0x7f16,  0x8d2c,  0x6241,  0x4fbf,  0x53d8,  0x535e,  0x8fa8,  0x8fa9,  0x8fab,  0x904d,  0x533e,  0x5f01,  0x82c4,  0x5fed,  0x6c74,  0x7f0f,  0x7178,  0x782d,  0x78a5,  0x7a86,  0x890a,  0x8759,  0x7b3e,  0x9cca,
// biao  ±ê          ±ë          ±ì          ±í          æ»          æô          ì©          ì­          ì®          ïÚ          ïð          ñ¦          ñÑ          ÷§
    0x6807,  0x5f6a,  0x8198,  0x8868,  0x5a4a,  0x9aa0,  0x98d1,  0x98d9,  0x98da,  0x9556,  0x9573,  0x762d,  0x88f1,  0x9cd4,
// bie  ±î          ±ï          ±ð          ±ñ          õ¿
    0x9cd6,  0x618b,  0x522b,  0x762a,  0x8e69,
// bin  ±ò          ±ó          ±ô          ±õ          ±ö          ±÷          ÙÏ          áÙ          çÍ          çã          éÄ          éë          ë÷          ïÙ          ÷Æ          ÷Þ
    0x5f6c,  0x658c,  0x6fd2,  0x6ee8,  0x5bbe,  0x6448,  0x50a7,  0x8c73,  0x7f24,  0x73a2,  0x69df,  0x6ba1,  0x8191,  0x9554,  0x9acc,  0x9b13,
// bing  ±ø          ±ù          ±ú          ±û          ±ü          ±ý          ±þ          ²¡          ²¢          ÆÁ          Ù÷          Úû          Þð          éÄ
    0x5175,  0x51b0,  0x67c4,  0x4e19,  0x79c9,  0x997c,  0x70b3,  0x75c5,  0x5e76,  0x5c4f,  0x7980,  0x90b4,  0x6452,  0x69df,
// bo  °Ø          °þ          ±¡          ²£          ²¤          ²¥          ²¦          ²§          ²¨          ²©          ²ª          ²«          ²¬          ²­          ²®          ²¯          ²°          ²±          ²²          ²³          ²´          ²µ          ²·          Ùñ          à£          âÄ          éÞ          ë¢          íç          îà          ð¾          ô¤          õË          õÛ
    0x67cf,  0x5265,  0x8584,  0x73bb,  0x83e0,  0x64ad,  0x62e8,  0x94b5,  0x6ce2,  0x535a,  0x52c3,  0x640f,  0x94c2,  0x7b94,  0x4f2f,  0x5e1b,  0x8236,  0x8116,  0x818a,  0x6e24,  0x6cca,  0x9a73,  0x535c,  0x4eb3,  0x5575,  0x997d,  0x6a97,  0x64d8,  0x7934,  0x94b9,  0x9e41,  0x7c38,  0x8ddb,  0x8e23,
// bu  ²¶          ²·          ²¸          ²¹          ²º          ²»          ²¼          ²½          ²¾          ²¿          ²À          ÆÒ          ß²          åÍ          ê³          êÎ          îÐ          îß          õ³
    0x6355,  0x535c,  0x54fa,  0x8865,  0x57e0,  0x4e0d,  0x5e03,  0x6b65,  0x7c3f,  0x90e8,  0x6016,  0x57d4,  0x535f,  0x900b,  0x74ff,  0x6661,  0x949a,  0x94b8,  0x91ad,
// ca  ²Á          àê          íå
    0x64e6,  0x5693,  0x7924,
// cai  ²Â          ²Ã          ²Ä          ²Å          ²Æ          ²Ç          ²È          ²É          ²Ê          ²Ë          ²Ì
    0x731c,  0x88c1,  0x6750,  0x624d,  0x8d22,  0x776c,  0x8e29,  0x91c7,  0x5f69,  0x83dc,  0x8521,
// can  ²Í          ²Î          ²Ï          ²Ð          ²Ñ          ²Ò          ²Ó          åî          æî          è²          ôÓ          ÷õ
    0x9910,  0x53c2,  0x8695,  0x6b8b,  0x60ed,  0x60e8,  0x707f,  0x5b71,  0x9a96,  0x74a8,  0x7cb2,  0x9eea,
// cang  ²Ô          ²Õ          ²Ö          ²×          ²Ø          Ø÷
    0x82cd,  0x8231,  0x4ed3,  0x6ca7,  0x85cf,  0x4f27,
// cao  ²Ù          ²Ú          ²Û          ²Ü          ²Ý          àÐ          äî          ó©          ô½
    0x64cd,  0x7cd9,  0x69fd,  0x66f9,  0x8349,  0x5608,  0x6f15,  0x87ac,  0x825a,
// ce  ²Þ          ²ß          ²à          ²á          ²â          âü
    0x5395,  0x7b56,  0x4fa7,  0x518c,  0x6d4b,  0x607b,
// cen  ²Î          á¯          ä¹
    0x53c2,  0x5c91,  0x6d94,
// ceng  ²ã          ²ä          Ôø          àá
    0x5c42,  0x8e6d,  0x66fe,  0x564c,
// cha  ²å          ²æ          ²ç          ²è          ²é          ²ê          ²ë          ²ì          ²í          ²î          ²ï          É²          Ôû          àê          âª          âÇ          ãâ          æ±          è¾          é«          é¶          éß          ïÊ          ïï          ñÃ
    0x63d2,  0x53c9,  0x832c,  0x8336,  0x67e5,  0x78b4,  0x643d,  0x5bdf,  0x5c94,  0x5dee,  0x8be7,  0x5239,  0x55b3,  0x5693,  0x7339,  0x9987,  0x6c4a,  0x59f9,  0x6748,  0x6942,  0x69ce,  0x6aab,  0x9538,  0x9572,  0x8869,
// chai  ²î          ²ð          ²ñ          ²ò          Ù­          îÎ          ðû          ò²
    0x5dee,  0x62c6,  0x67f4,  0x8c7a,  0x4faa,  0x9497,  0x7625,  0x867f,
// chan  ²ó          ²ô          ²õ          ²ö          ²÷          ²ø          ²ù          ²ú          ²û          ²ü          Ùæ          ÚÆ          ÝÛ          âÜ          âã          äý          å¤          åî          åñ          æ¿          æö          êè          ìø          ó¸          õð
    0x6400,  0x63ba,  0x8749,  0x998b,  0x8c17,  0x7f20,  0x94f2,  0x4ea7,  0x9610,  0x98a4,  0x5181,  0x8c04,  0x8487,  0x5edb,  0x5fcf,  0x6f7a,  0x6fb6,  0x5b71,  0x7fbc,  0x5a75,  0x9aa3,  0x89c7,  0x7985,  0x87fe,  0x8e94,
// chang  ²ý          ²þ          ³¡          ³¢          ³£          ³¤          ³¥          ³¦          ³§          ³¨          ³©          ³ª          ³«          ÉÑ          Øö          ÛË          ÜÉ          ÝÅ          áä          âê          ã®          ãÑ          æ½          æÏ          êÆ          ë©          öð
    0x660c,  0x7316,  0x573a,  0x5c1d,  0x5e38,  0x957f,  0x507f,  0x80a0,  0x5382,  0x655e,  0x7545,  0x5531,  0x5021,  0x88f3,  0x4f25,  0x9b2f,  0x82cc,  0x83d6,  0x5f9c,  0x6005,  0x60dd,  0x960a,  0x5a3c,  0x5ae6,  0x6636,  0x6c05,  0x9cb3,
// chao  ³¬          ³­          ³®          ³¯          ³°          ³±          ³²          ³³          ³´          ´Â          ½Ë          â÷          êË          ìÌ          ñé
    0x8d85,  0x6284,  0x949e,  0x671d,  0x5632,  0x6f6e,  0x5de2,  0x5435,  0x7092,  0x7ef0,  0x527f,  0x600a,  0x6641,  0x712f,  0x8016,
// che  ³µ          ³¶          ³·          ³¸          ³¹          ³º          Ûå          íº
    0x8f66,  0x626f,  0x64a4,  0x63a3,  0x5f7b,  0x6f88,  0x577c,  0x7817,
// chen  ³»          ³¼          ³½          ³¾          ³¿          ³À          ³Á          ³Â          ³Ã          ³Ä          ³Æ          Éò          ÚÈ          Úß          ÞÓ          àÁ          å·          è¡          é´          í×          ö³
    0x90f4,  0x81e3,  0x8fb0,  0x5c18,  0x6668,  0x5ff1,  0x6c89,  0x9648,  0x8d81,  0x886c,  0x79f0,  0x6c88,  0x8c0c,  0x8c36,  0x62bb,  0x55d4,  0x5bb8,  0x741b,  0x6987,  0x789c,  0x9f80,
// cheng  ³Å          ³Æ          ³Ç          ³È          ³É          ³Ê          ³Ë          ³Ì          ³Í          ³Î          ³Ï          ³Ð          ³Ñ          ³Ò          ³Ó          Ø©          Ûô          èÇ          èß          ëó          îª          îñ          îõ          ñÎ          òÉ          õ¨
    0x6491,  0x79f0,  0x57ce,  0x6a59,  0x6210,  0x5448,  0x4e58,  0x7a0b,  0x60e9,  0x6f84,  0x8bda,  0x627f,  0x901e,  0x9a8b,  0x79e4,  0x4e1e,  0x57d5,  0x67a8,  0x67fd,  0x584d,  0x77a0,  0x94d6,  0x94db,  0x88ce,  0x86cf,  0x9172,
// chi  ³Ô          ³Õ    ³Ö          ³×       ³Ø       ³Ù        ³Ú        ³Û        ³Ü        ³Ý        ³Þ        ³ß        ³à        ³á        ³â         ³ã       ÙÑ        Ü¯        ÜÝ         ß³        ßê       à´          àÍ       áÜ       âÁ       æÊ          ë·
    0x5403,  0x75f4,  0x6301,  0x5319,  0x6c60,  0x8fdf,  0x5f1b,  0x9a70,  0x803b,  0x9f7f,  0x4f88,  0x5c3a,  0x8d64,  0x7fc5,  0x65a5,  0x70bd,  0x50ba,  0x5880,  0x830c,  0x53f1,  0x54e7,  0x557b,  0x55e4,  0x5f73,  0x996c,  0x5ab8,  0x6555,
//  í÷          ð·          ñ¡          ñÝ       ò¿     ó¤          ó×        óø        ôù        õØ        ÷Î
    0x7735,  0x9e31,  0x761b,  0x892b,  0x86a9,  0x87ad,  0x7b1e,  0x7bea,  0x8c49,  0x8e1f,  0x9b51,
// chong  ³ä          ³å          ³æ          ³ç          ³è          ÖØ          Üû          âç          ã¿          ï¥          ô©          ô¾
    0x5145,  0x51b2,  0x866b,  0x5d07,  0x5ba0,  0x91cd,  0x833a,  0x5fe1,  0x61a7,  0x94f3,  0x8202,  0x825f,
// chou  ³é          ³ê          ³ë          ³ì          ³í          ³î          ³ï          ³ð          ³ñ          ³ò          ³ó          ³ô          Ù±          àü          ã°          ñ¬          öÅ
    0x62bd,  0x916c,  0x7574,  0x8e0c,  0x7a20,  0x6101,  0x7b79,  0x4ec7,  0x7ef8,  0x7785,  0x4e11,  0x81ed,  0x4fe6,  0x5e31,  0x60c6,  0x7633,  0x96e0,
// chu  ³õ          ³ö          ³÷          ³ø          ³ù          ³ú          ³û          ³ü          ³ý          ³þ          ´¡          ´¢          ´£          ´¤          ´¥          ´¦          Ðó          Ø¡          Û»          âð          ãÀ          ç©          èÆ          èú          éË          ñÒ          òÜ          õé          ÷í
    0x521d,  0x51fa,  0x6a71,  0x53a8,  0x8e87,  0x9504,  0x96cf,  0x6ec1,  0x9664,  0x695a,  0x7840,  0x50a8,  0x77d7,  0x6410,  0x89e6,  0x5904,  0x755c,  0x4e8d,  0x520d,  0x6035,  0x61b7,  0x7ecc,  0x6775,  0x696e,  0x6a17,  0x891a,  0x870d,  0x8e70,  0x9edc,
// chuai  ´§          Þõ          à¨          àÜ          ëú          õß
    0x63e3,  0x640b,  0x555c,  0x562c,  0x81aa,  0x8e39,
// chuan  ´¨          ´©          ´ª          ´«          ´¬          ´­          ´®          â¶          å×          ë°          îË          ô­
    0x5ddd,  0x7a7f,  0x693d,  0x4f20,  0x8239,  0x5598,  0x4e32,  0x821b,  0x9044,  0x6c1a,  0x948f,  0x8221,
// chuang  ´¯          ´°          ´±          ´²          ´³          ´´          âë
    0x75ae,  0x7a97,  0x5e62,  0x5e8a,  0x95ef,  0x521b,  0x6006,
// chui  ´µ          ´¶          ´·          ´¸          ´¹          ×µ          Úï          é¢          é³
    0x5439,  0x708a,  0x6376,  0x9524,  0x5782,  0x690e,  0x9672,  0x68f0,  0x69cc,
// chun  ´º          ´»          ´¼          ´½          ´¾          ´¿          ´À          Ý»          ðÈ          òí
    0x6625,  0x693f,  0x9187,  0x5507,  0x6df3,  0x7eaf,  0x8822,  0x83bc,  0x9e51,  0x877d,
// chuo  ´Á          ´Â          à¨          ê¡          õÖ          öº
    0x6233,  0x7ef0,  0x555c,  0x8f8d,  0x8e14,  0x9f8a,
// ci  ²î          ´Ã          ´Ä          ´Å          ´Æ          ´Ç          ´È          ´É          ´Ê          ´Ë          ´Ì          ´Í          ´Î          Üë          ìô          ðË          ôÙ
    0x5dee,  0x75b5,  0x8328,  0x78c1,  0x96cc,  0x8f9e,  0x6148,  0x74f7,  0x8bcd,  0x6b64,  0x523a,  0x8d50,  0x6b21,  0x8308,  0x7960,  0x9e5a,  0x7ccd,
// cong  ´Ï          ´Ð          ´Ñ          ´Ò          ´Ó          ´Ô          ÜÊ          äÈ          æõ          çý          è®          èÈ
    0x806a,  0x8471,  0x56f1,  0x5306,  0x4ece,  0x4e1b,  0x82c1,  0x6dd9,  0x9aa2,  0x742e,  0x7481,  0x679e,
// cou  ´Õ          é¨          ê£          ëí
    0x51d1,  0x6971,  0x8f8f,  0x8160,
// cu  ´Ö          ´×          ´Ø          ´Ù          ×ä          Ýý          áÞ          â§          éã          õ¡          õ¾          õí
    0x7c97,  0x918b,  0x7c07,  0x4fc3,  0x5352,  0x851f,  0x5f82,  0x731d,  0x6b82,  0x9162,  0x8e59,  0x8e74,
// cuan  ´Ú          ´Û          ´Ü          ÔÜ          Ùà          ß¥          ìà          ïé
    0x8e7f,  0x7be1,  0x7a9c,  0x6512,  0x6c46,  0x64ba,  0x7228,  0x9569,
// cui  ´Ý          ´Þ          ´ß          ´à          ´á          ´â          ´ã          ´ä          Ë¥          ÝÍ          ßý          ã²          è­          éÁ          ë¥
    0x6467,  0x5d14,  0x50ac,  0x8106,  0x7601,  0x7cb9,  0x6dec,  0x7fe0,  0x8870,  0x8403,  0x5550,  0x60b4,  0x7480,  0x69b1,  0x6bf3,
// cun  ´å          ´æ          ´ç          ââ          ñå
    0x6751,  0x5b58,  0x5bf8,  0x5fd6,  0x76b4,
// cuo  ´è          ´é          ´ê          ´ë          ´ì          ´í          ØÈ          áÏ          ëâ          ï±          ïó          ðî          ðû          õº          õã
    0x78cb,  0x64ae,  0x6413,  0x63aa,  0x632b,  0x9519,  0x539d,  0x5d6f,  0x811e,  0x9509,  0x77ec,  0x75e4,  0x7625,  0x9e7e,  0x8e49,
// da  ´î          ´ï          ´ð          ´ñ          ´ò          ´ó          ÞÇ          ßÕ          àª          àí          âò          æ§          í³          ñ×          óÎ          ÷°          ÷²
    0x642d,  0x8fbe,  0x7b54,  0x7629,  0x6253,  0x5927,  0x8037,  0x54d2,  0x55d2,  0x56d7,  0x601b,  0x59b2,  0x6c93,  0x8921,  0x7b2a,  0x977c,  0x9791,
// dai  ´ô          ´õ          ´ö          ´÷          ´ø          ´ù          ´ú          ´û          ´ü          ´ý          ´þ          µ¡          Ü¤          ß°          ß¾          á·          åÊ          çª          çé          ÷ì
    0x5446,  0x6b79,  0x50a3,  0x6234,  0x5e26,  0x6b86,  0x4ee3,  0x8d37,  0x888b,  0x5f85,  0x902e,  0x6020,  0x57ed,  0x7519,  0x5454,  0x5cb1,  0x8fe8,  0x7ed0,  0x73b3,  0x9edb,
// dan  µ¢          µ£          µ¤          µ¥          µ¦          µ§          µ¨          µ©          µª          µ«          µ¬          µ­          µ®          µ¯          µ°          Ê¯          ÙÙ          ÛÊ          ÝÌ          ÝÐ          à¢          å£          å´          éé          êæ          íñ          ðã          ð÷          ñõ          óì
    0x803d,  0x62c5,  0x4e39,  0x5355,  0x90f8,  0x63b8,  0x80c6,  0x65e6,  0x6c2e,  0x4f46,  0x60ee,  0x6de1,  0x8bde,  0x5f39,  0x86cb,  0x77f3,  0x510b,  0x51fc,  0x840f,  0x83ea,  0x5556,  0x6fb9,  0x5b95,  0x6b9a,  0x8d55,  0x7708,  0x75b8,  0x7605,  0x8043,  0x7baa,
// dang  µ±          µ²          µ³          µ´          µµ          ÚÔ          í¸          îõ          ñÉ
    0x5f53,  0x6321,  0x515a,  0x8361,  0x6863,  0x8c20,  0x7800,  0x94db,  0x88c6,
// dao  µ¶          µ·          µ¸          µ¹          µº          µ»          µ¼          µ½          µ¾          µ¿          µÀ          µÁ          ß¶          ë®          ìâ          ôî
    0x5200,  0x6363,  0x8e48,  0x5012,  0x5c9b,  0x7977,  0x5bfc,  0x5230,  0x7a3b,  0x60bc,  0x9053,  0x76d7,  0x53e8,  0x6c18,  0x7118,  0x7e9b,
// de  µÂ          µÃ          µÄ          µØ          ï½
    0x5fb7,  0x5f97,  0x7684,  0x5730,  0x951d,
// deng  µÅ          µÆ          µÇ          µÈ          µÉ          µÊ          µË          àâ          áØ          ê­          íã          ïë          ô£
    0x8e6c,  0x706f,  0x767b,  0x7b49,  0x77aa,  0x51f3,  0x9093,  0x5654,  0x5d9d,  0x6225,  0x78f4,  0x956b,  0x7c26,
// di  µÄ        µÌ       µÍ        µÎ       µÏ       µÐ        µÑ        µÒ        µÓ       µÔ         µÕ          µÖ       µ×          µØ      µÙ       µÚ         µÛ       µÜ        µÝ       µÞ           Øµ       Ùá        Ú®        ÚÐ        Û¡        Ûæ        Ý¶        àÖ          æ·
    0x7684,  0x5824,  0x4f4e,  0x6ef4,  0x8fea,  0x654c,  0x7b1b,  0x72c4,  0x6da4,  0x7fdf,  0x5ae1,  0x62b5,  0x5e95,  0x5730,  0x8482,  0x7b2c,  0x5e1d,  0x5f1f,  0x9012,  0x7f14,  0x6c10,  0x7c74,  0x8bcb,  0x8c1b,  0x90b8,  0x577b,  0x837b,  0x5600,  0x5a23,
//    èÜ          é¦          êë     ìó        íÆ        íÚ       íû          ïá       ôÆ        ÷¾
    0x67e2,  0x68e3,  0x89cc,  0x7957,  0x7825,  0x78b2,  0x7747,  0x955d,  0x7f9d,  0x9ab6,
// dia  àÇ
    0x55f2,
// dian  µß          µà          µá          µâ          µã          µä          µå          µæ          µç          µè          µé          µê          µë          µì          µí          µî          Ø¼          Úç          Ûã          áÛ          çè          îä          ñ°          ñ²          ô¡          õÚ
    0x98a0,  0x6382,  0x6ec7,  0x7898,  0x70b9,  0x5178,  0x975b,  0x57ab,  0x7535,  0x4f43,  0x7538,  0x5e97,  0x60e6,  0x5960,  0x6dc0,  0x6bbf,  0x4e36,  0x963d,  0x576b,  0x5dc5,  0x73b7,  0x94bf,  0x765c,  0x766b,  0x7c1f,  0x8e2e,
// diao  µï          µð          µñ          µò          µó          µô          µõ          µö          µ÷          îö          õõ          öô
    0x7889,  0x53fc,  0x96d5,  0x51cb,  0x5201,  0x6389,  0x540a,  0x9493,  0x8c03,  0x94de,  0x8c82,  0x9cb7,
// die  µø          µù          µú          µû          µü          µý          µþ          Ûì          Ü¦          Þé          à©          ëº          ð¬          ñó          öø
    0x8dcc,  0x7239,  0x789f,  0x8776,  0x8fed,  0x8c0d,  0x53e0,  0x57a4,  0x581e,  0x63f2,  0x558b,  0x7252,  0x74de,  0x800b,  0x9cbd,
// ding  ¶¡          ¶¢          ¶£          ¶¤          ¶¥          ¶¦          ¶§          ¶¨          ¶©          Øê          à¤          çà          ëë          íÖ          î®          ðÛ          ñô          ôú
    0x4e01,  0x76ef,  0x53ee,  0x9489,  0x9876,  0x9f0e,  0x952d,  0x5b9a,  0x8ba2,  0x4ec3,  0x5576,  0x738e,  0x815a,  0x7887,  0x753a,  0x7594,  0x8035,  0x914a,
// diu  ¶ª          îû
    0x4e22,  0x94e5,
// dong  ¶«          ¶¬          ¶­          ¶®          ¶¯          ¶°          ¶±          ¶²          ¶³          ¶´          Ûí          ßË          á´          á¼          ë±          ëË          ëØ          íÏ          ð´
    0x4e1c,  0x51ac,  0x8463,  0x61c2,  0x52a8,  0x680b,  0x4f97,  0x606b,  0x51bb,  0x6d1e,  0x578c,  0x549a,  0x5cbd,  0x5cd2,  0x6c21,  0x80e8,  0x80f4,  0x7850,  0x9e2b,
// dou  ¶µ          ¶¶          ¶·          ¶¸          ¶¹          ¶º          ¶»          ¶¼          Ýú          î×          ñ¼          ò½          óû
    0x515c,  0x6296,  0x6597,  0x9661,  0x8c46,  0x9017,  0x75d8,  0x90fd,  0x8538,  0x94ad,  0x7aa6,  0x86aa,  0x7bfc,
// du  ¶¼          ¶½          ¶¾          ¶¿          ¶À          ¶Á          ¶Â          ¶Ã          ¶Ä          ¶Å          ¶Æ          ¶Ç          ¶È          ¶É          ¶Ê          Ü¶          à½          äÂ          èü          ë¹          ó¼          óÆ          ÷Ç          ÷ò
    0x90fd,  0x7763,  0x6bd2,  0x728a,  0x72ec,  0x8bfb,  0x5835,  0x7779,  0x8d4c,  0x675c,  0x9540,  0x809a,  0x5ea6,  0x6e21,  0x5992,  0x828f,  0x561f,  0x6e0e,  0x691f,  0x724d,  0x8839,  0x7b03,  0x9ad1,  0x9ee9,
// duan  ¶Ë          ¶Ì          ¶Í          ¶Î          ¶Ï          ¶Ð          é²          ìÑ          óý
    0x7aef,  0x77ed,  0x953b,  0x6bb5,  0x65ad,  0x7f0e,  0x6934,  0x7145,  0x7c16,
// dui  ¶Ñ          ¶Ò          ¶Ó          ¶Ô          ¶Ø          í¡          í­          íÔ          ïæ
    0x5806,  0x5151,  0x961f,  0x5bf9,  0x6566,  0x603c,  0x619d,  0x7893,  0x9566,
// dun  ¶Õ          ¶Ö          ¶×          ¶Ø          ¶Ù          ¶Ú          ¶Û          ¶Ü          ¶Ý          ãç          ìÀ          í»          íâ          íï          õ»
    0x58a9,  0x5428,  0x8e72,  0x6566,  0x987f,  0x56e4,  0x949d,  0x76fe,  0x9041,  0x6c8c,  0x7096,  0x7818,  0x7905,  0x76f9,  0x8db8,
// duo  ¶È          ¶Þ          ¶ß          ¶à          ¶á          ¶â          ¶ã          ¶ä          ¶å          ¶æ          ¶ç          ¶è          ¶é          ßÍ          ßá          ãõ          ç¶          îì          ñÖ          õâ
    0x5ea6,  0x6387,  0x54c6,  0x591a,  0x593a,  0x579b,  0x8eb2,  0x6735,  0x8dfa,  0x8235,  0x5241,  0x60f0,  0x5815,  0x5484,  0x54da,  0x6cb2,  0x7f0d,  0x94ce,  0x88f0,  0x8e31,
// e  °¢          ¶ê          ¶ë          ¶ì          ¶í          ¶î          ¶ï          ¶ð          ¶ñ          ¶ò          ¶ó          ¶ô          ¶õ          ¶ö          Å¶          Ø¬          ÚÌ          ÛÑ          ÜÃ          Ý­          Ýà          ßÀ          ãµ          åí          æ¹          éî          ëñ          ï°          ïÉ          ðÊ          ò¦          öù
    0x963f,  0x86fe,  0x5ce8,  0x9e45,  0x4fc4,  0x989d,  0x8bb9,  0x5a25,  0x6076,  0x5384,  0x627c,  0x904f,  0x9102,  0x997f,  0x54e6,  0x5669,  0x8c14,  0x57a9,  0x82ca,  0x83aa,  0x843c,  0x5443,  0x6115,  0x5c59,  0x5a40,  0x8f6d,  0x816d,  0x9507,  0x9537,  0x9e57,  0x989a,  0x9cc4,
// ei  ÚÀ
    0x8bf6,
// en  ¶÷          Ýì          Þô          àÅ
    0x6069,  0x84bd,  0x6441,  0x55ef,
// er  ¶ø          ¶ù          ¶ú          ¶û          ¶ü          ¶ý          ¶þ          ·¡          åÇ          çí          îï          ð¹          öÜ
    0x800c,  0x513f,  0x8033,  0x5c14,  0x9975,  0x6d31,  0x4e8c,  0x8d30,  0x8fe9,  0x73e5,  0x94d2,  0x9e38,  0x9c95,
// fa  ·¢          ·£          ·¤          ·¥          ·¦          ·§          ·¨          ·©          ÛÒ          íÀ
    0x53d1,  0x7f5a,  0x7b4f,  0x4f10,  0x4e4f,  0x9600,  0x6cd5,  0x73d0,  0x57a1,  0x781d,
// fan  ·ª          ·«          ·¬          ·­          ·®          ·¯          ·°          ·±          ·²          ·³          ·´          ·µ          ·¶          ··          ·¸          ·¹          ·º          Þ¬          ÞÀ          á¦          âº          èó          ë¶          ìÜ          î²          õì
    0x85e9,  0x5e06,  0x756a,  0x7ffb,  0x6a0a,  0x77fe,  0x9492,  0x7e41,  0x51e1,  0x70e6,  0x53cd,  0x8fd4,  0x8303,  0x8d29,  0x72af,  0x996d,  0x6cdb,  0x8543,  0x8629,  0x5e61,  0x5902,  0x68b5,  0x6535,  0x71d4,  0x7548,  0x8e6f,
// fang  ·»          ·¼          ·½          ·¾          ·¿          ·À          ·Á          ·Â          ·Ã          ·Ä          ·Å          Úú          èÊ          îÕ          ô³          öÐ
    0x574a,  0x82b3,  0x65b9,  0x80aa,  0x623f,  0x9632,  0x59a8,  0x4eff,  0x8bbf,  0x7eba,  0x653e,  0x90a1,  0x678b,  0x94ab,  0x822b,  0x9c82,
// fei  ·Æ          ·Ç          ·È          ·É          ·Ê          ·Ë          ·Ì          ·Í          ·Î          ·Ï          ·Ð          ·Ñ          ÜÀ          áô          ã­          äÇ          åú          ç³          é¼          ëè          ì³          ìé          íÉ          ïÐ          ðò          òã          óõ          ôä          ö­          öî
    0x83f2,  0x975e,  0x5561,  0x98de,  0x80a5,  0x532a,  0x8bfd,  0x5420,  0x80ba,  0x5e9f,  0x6cb8,  0x8d39,  0x82be,  0x72d2,  0x60b1,  0x6ddd,  0x5983,  0x7eef,  0x69a7,  0x8153,  0x6590,  0x6249,  0x7829,  0x9544,  0x75f1,  0x871a,  0x7bda,  0x7fe1,  0x970f,  0x9cb1,
// fen  ·Ò          ·Ó          ·Ô          ·Õ          ·Ö          ·×          ·Ø          ·Ù          ·Ú          ·Û          ·Ü          ·Ý          ·Þ          ·ß          ·à          ÙÇ          å¯          èû          ö÷          ÷÷
    0x82ac,  0x915a,  0x5429,  0x6c1b,  0x5206,  0x7eb7,  0x575f,  0x711a,  0x6c7e,  0x7c89,  0x594b,  0x4efd,  0x5fff,  0x6124,  0x7caa,  0x507e,  0x7035,  0x68fc,  0x9cbc,  0x9f22,
// feng  ·á          ·â          ·ã          ·ä          ·å          ·æ          ·ç          ·è          ·é          ·ê          ·ë          ·ì          ·í          ·î          ·ï          Ùº          Ûº          Ý×          ßô          ãã          í¿
    0x4e30,  0x5c01,  0x67ab,  0x8702,  0x5cf0,  0x950b,  0x98ce,  0x75af,  0x70fd,  0x9022,  0x51af,  0x7f1d,  0x8bbd,  0x5949,  0x51e4,  0x4ff8,  0x9146,  0x8451,  0x552a,  0x6ca3,  0x781c,
// fo  ·ð
    0x4f5b,
// fou  ·ñ          ó¾
    0x5426,  0x7f36,
// fu  ·ò          ·ó      ·ô       ·õ        ·ö          ·÷      ·ø       ·ù          ·ú       ·û          ·ü      ·ý          ·þ       ¸¡        ¸¢        ¸£        ¸¤        ¸¥       ¸¦        ¸§        ¸¨       ¸©         ¸ª        ¸«        ¸¬        ¸­
    0x592b,  0x6577,  0x80a4,  0x5b75,  0x6276,  0x62c2,  0x8f90,  0x5e45,  0x6c1f,  0x7b26,  0x4f0f,  0x4fd8,  0x670d,  0x6d6e,  0x6daa,  0x798f,  0x88b1,  0x5f17,  0x752b,  0x629a,  0x8f85,  0x4fef,  0x91dc,  0x65a7,  0x812f,  0x8151,
//  ¸®          ¸¯          ¸°        ¸±        ¸²        ¸³        ¸´        ¸µ        ¸¶        ¸·        ¸¸        ¸¹        ¸º       ¸»        ¸¼        ¸½        ¸¾          ¸¿       ¸À        ÆÎ       Ùë       Ùì        Û®        Ü½         ÜÀ        ÜÞ
    0x5e9c,  0x8150,  0x8d74,  0x526f,  0x8986,  0x8d4b,  0x590d,  0x5085,  0x4ed8,  0x961c,  0x7236,  0x8179,  0x8d1f,  0x5bcc,  0x8ba3,  0x9644,  0x5987,  0x7f1a,  0x5490,  0x8386,  0x5310,  0x51eb,  0x90db,  0x8299,  0x82be,  0x82fb,
//  Üò          Ý³          ÝÊ         ÞÔ       ß»        ß¼        á¥       âö        äæ        åõ        æÚ        æâ        ç¦        ç¨        èõ        êç         ìð        íê        íë        î·        ïû        ð¥        ò¶        òÝ        òð        òó        ôï        õÃ       õÆ        öÖ        öû
    0x832f,  0x83a9,  0x83d4,  0x62ca,  0x544b,  0x5452,  0x5e5e,  0x602b,  0x6ecf,  0x8274,  0x5b5a,  0x9a78,  0x7ec2,  0x7ecb,  0x6874,  0x8d59,  0x7953,  0x9efb,  0x9efc,  0x7f58,  0x7a03,  0x99a5,  0x86a8,  0x8709,  0x8760,  0x876e,  0x9eb8,  0x8dba,  0x8dd7,  0x9c8b,  0x9cc6,
// ga  ¸Á          ¸Â          ¼Ð          Ôþ          Ûò          ÞÎ          æØ          æÙ          ê¸          îÅ
    0x5676,  0x560e,  0x5939,  0x8f67,  0x5793,  0x5c2c,  0x5c15,  0x5c1c,  0x65ee,  0x9486,
// gai  ¸Ã          ¸Ä          ¸Å          ¸Æ          ¸Ç          ¸È          ½æ          Ø¤          Úë          ê®          êà
    0x8be5,  0x6539,  0x6982,  0x9499,  0x76d6,  0x6e89,  0x82a5,  0x4e10,  0x9654,  0x6224,  0x8d45,
// gan  ¸É          ¸Ê          ¸Ë          ¸Ì          ¸Í          ¸Î          ¸Ï          ¸Ð          ¸Ñ          ¸Ò          ¸Ó          Ûá          ÜÕ          ÞÏ          ß¦          ãï          äÆ          ä÷          ç¤          éÏ          êº          í·          ðá          ôû
    0x5e72,  0x7518,  0x6746,  0x67d1,  0x7aff,  0x809d,  0x8d76,  0x611f,  0x79c6,  0x6562,  0x8d63,  0x5769,  0x82f7,  0x5c34,  0x64c0,  0x6cd4,  0x6de6,  0x6f89,  0x7ec0,  0x6a44,  0x65f0,  0x77f8,  0x75b3,  0x9150,
// gang  ¸Ô          ¸Õ          ¸Ö          ¸×          ¸Ø          ¸Ù          ¸Ú          ¸Û          ¸Ü          í°          î¸          óà
    0x5188,  0x521a,  0x94a2,  0x7f38,  0x809b,  0x7eb2,  0x5c97,  0x6e2f,  0x6760,  0x6206,  0x7f61,  0x7b7b,
// gao  ¸Ý          ¸Þ          ¸ß          ¸à          ¸á          ¸â          ¸ã          ¸ä          ¸å          ¸æ          Øº          Ú¾          Û¬          Þ»          çÉ          éÀ          éÂ          ê½          ï¯
    0x7bd9,  0x768b,  0x9ad8,  0x818f,  0x7f94,  0x7cd5,  0x641e,  0x9550,  0x7a3f,  0x544a,  0x777e,  0x8bf0,  0x90dc,  0x85c1,  0x7f1f,  0x69d4,  0x69c1,  0x6772,  0x9506,
// ge  ¸ç          ¸è          ¸é          ¸ê          ¸ë          ¸ì          ¸í          ¸î          ¸ï          ¸ð          ¸ñ          ¸ò          ¸ó          ¸ô          ¸õ          ¸ö          ¸÷          ºÏ          ¿©          Øª          Øî          ÛÁ          ÛÙ          Üª          àÃ          æü          ë¡          ëõ          íÑ          ïÓ          ñË          ò¢          ò´          ô´          ÷À
    0x54e5,  0x6b4c,  0x6401,  0x6208,  0x9e3d,  0x80f3,  0x7599,  0x5272,  0x9769,  0x845b,  0x683c,  0x86e4,  0x9601,  0x9694,  0x94ec,  0x4e2a,  0x5404,  0x5408,  0x54af,  0x9b32,  0x4ee1,  0x54ff,  0x572a,  0x5865,  0x55dd,  0x7ea5,  0x643f,  0x8188,  0x784c,  0x9549,  0x88bc,  0x988c,  0x867c,  0x8238,  0x9abc,
// gei  ¸ø
    0x7ed9,
// gen  ¸ù          ¸ú          Ø¨          Ý¢          ßç          ôÞ
    0x6839,  0x8ddf,  0x4e98,  0x831b,  0x54cf,  0x826e,
// geng  ¸û          ¸ü          ¸ý          ¸þ          ¹¡          ¹¢          ¹£          ßì          âÙ          ç®          öá
    0x8015,  0x66f4,  0x5e9a,  0x7fb9,  0x57c2,  0x803f,  0x6897,  0x54fd,  0x8d53,  0x7ee0,  0x9ca0,
// gong  ¹¤          ¹¥          ¹¦          ¹§          ¹¨          ¹©          ¹ª          ¹«          ¹¬          ¹­          ¹®          ¹¯          ¹°          ¹±          ¹²          çî          ëÅ          ò¼          ö¡
    0x5de5,  0x653b,  0x529f,  0x606d,  0x9f9a,  0x4f9b,  0x8eac,  0x516c,  0x5bab,  0x5f13,  0x5de9,  0x6c5e,  0x62f1,  0x8d21,  0x5171,  0x73d9,  0x80b1,  0x86a3,  0x89e5,
// gou  ¹³          ¹´          ¹µ          ¹¶          ¹·          ¹¸          ¹¹          ¹º          ¹»          Øþ          Ú¸          á¸          åÜ          æÅ          çÃ          èÛ          êí          ì°          óÑ          óô          ÷¸
    0x94a9,  0x52fe,  0x6c9f,  0x82df,  0x72d7,  0x57a2,  0x6784,  0x8d2d,  0x591f,  0x4f5d,  0x8bdf,  0x5ca3,  0x9058,  0x5abe,  0x7f11,  0x67b8,  0x89cf,  0x5f40,  0x7b31,  0x7bdd,  0x97b2,
// gu  ¸æ          ¹¼       ¹½       ¹¾       ¹¿          ¹À        ¹Á       ¹Â        ¹Ã       ¹Ä        ¹Å        ¹Æ        ¹Ç        ¹È        ¹É        ¹Ê        ¹Ë        ¹Ì        ¹Í        ¼Ö        ØÅ        Ú¬
    0x544a,  0x8f9c,  0x83c7,  0x5495,  0x7b8d,  0x4f30,  0x6cbd,  0x5b64,  0x59d1,  0x9f13,  0x53e4,  0x86ca,  0x9aa8,  0x8c37,  0x80a1,  0x6545,  0x987e,  0x56fa,  0x96c7,  0x8d3e,  0x560f,  0x8bc2,
//  ÝÔ          áÄ          ãé          èô          éï          êô          êö          ëû          ì±          î­          î¹          îÜ          ïÀ          ð³          ðÀ          ðó          òÁ          ôþ          õý          öñ          ÷½
    0x83f0,  0x5d2e,  0x6c69,  0x688f,  0x8f71,  0x726f,  0x727f,  0x81cc,  0x6bc2,  0x77bd,  0x7f5f,  0x94b4,  0x9522,  0x9e2a,  0x9e44,  0x75fc,  0x86c4,  0x9164,  0x89da,  0x9cb4,  0x9e58,
// gua  ¹Î          ¹Ï          ¹Ð          ¹Ñ          ¹Ò          ¹Ó          ØÔ          Ú´          ßÉ          èé          ëÒ          ð»
    0x522e,  0x74dc,  0x5250,  0x5be1,  0x6302,  0x8902,  0x5366,  0x8bd6,  0x5471,  0x681d,  0x80cd,  0x9e39,
// guai  ¹Ô          ¹Õ          ¹Ö          Þâ
    0x4e56,  0x62d0,  0x602a,  0x63b4,
// guan  ¹×          ¹Ø          ¹Ù          ¹Ú          ¹Û          ¹Ü          ¹Ý          ¹Þ          ¹ß          ¹à          ¹á          ÂÚ          ÙÄ          Ý¸          Þè          äÊ          îÂ          ðÙ          ñæ          ÷¤
    0x68fa,  0x5173,  0x5b98,  0x51a0,  0x89c2,  0x7ba1,  0x9986,  0x7f50,  0x60ef,  0x704c,  0x8d2f,  0x7eb6,  0x500c,  0x839e,  0x63bc,  0x6dab,  0x76e5,  0x9e73,  0x77dc,  0x9ccf,
// guang  ¹â          ¹ã          ¹ä          ßÛ          áî          èæ          ë×
    0x5149,  0x5e7f,  0x901b,  0x54a3,  0x72b7,  0x6844,  0x80f1,
// gui  ¹å          ¹æ          ¹ç          ¹è          ¹é          ¹ê          ¹ë          ¹ì          ¹í          ¹î          ¹ï          ¹ð          ¹ñ          ¹ò          ¹ó          ¹ô          ØÐ          ØÛ          âÑ          å³          æ£          èí          êÁ          êÐ          ð§          óþ          öÙ          ÷¬
    0x7470,  0x89c4,  0x572d,  0x7845,  0x5f52,  0x9f9f,  0x95fa,  0x8f68,  0x9b3c,  0x8be1,  0x7678,  0x6842,  0x67dc,  0x8dea,  0x8d35,  0x523d,  0x5326,  0x523f,  0x5e8b,  0x5b84,  0x59ab,  0x6867,  0x7085,  0x6677,  0x7688,  0x7c0b,  0x9c91,  0x9cdc,
// gun  ¹õ          ¹ö          ¹÷          Ùò          çµ          íÞ          öç
    0x8f8a,  0x6eda,  0x68cd,  0x886e,  0x7ef2,  0x78d9,  0x9ca7,
// guo  ¹ø          ¹ù          ¹ú          ¹û          ¹ü          ¹ý          Ùå          Ûö          Þâ          ßÃ          àþ          áÆ          â£          é¤          ë½          ñø          òä          òå
    0x9505,  0x90ed,  0x56fd,  0x679c,  0x88f9,  0x8fc7,  0x9998,  0x57da,  0x63b4,  0x5459,  0x5e3c,  0x5d1e,  0x7313,  0x6901,  0x8662,  0x8052,  0x873e,  0x8748,
// ha  ¸ò          ¹þ          îþ
    0x86e4,  0x54c8,  0x94ea,
// hai  º¡          º¢          º£          º¤          º¥          º¦          º§          »¹          àË          ëÜ          õ°
    0x9ab8,  0x5b69,  0x6d77,  0x6c26,  0x4ea5,  0x5bb3,  0x9a87,  0x8fd8,  0x55e8,  0x80f2,  0x91a2,
// han  º¨          º©          ºª          º«          º¬          º­          º®          º¯          º°          º±          º²          º³          º´          ºµ          º¶          º·          º¸          º¹          ºº          Úõ          ÝÕ          Þþ          áí          ãÛ          å«          êÏ          ìÊ          ñü          ò¥          òÀ          ÷ý
    0x9163,  0x61a8,  0x90af,  0x97e9,  0x542b,  0x6db5,  0x5bd2,  0x51fd,  0x558a,  0x7f55,  0x7ff0,  0x64bc,  0x634d,  0x65f1,  0x61be,  0x608d,  0x710a,  0x6c57,  0x6c49,  0x9097,  0x83e1,  0x6496,  0x72b4,  0x961a,  0x701a,  0x6657,  0x7113,  0x9878,  0x9894,  0x86b6,  0x9f3e,
// hang  º»          º¼          º½          ¿Ô          ÐÐ          ãì          ç¬          ñþ
    0x592f,  0x676d,  0x822a,  0x542d,  0x884c,  0x6c86,  0x7ed7,  0x9883,
// hao  º¾          º¿          ºÀ          ºÁ          ºÂ          ºÃ          ºÄ          ºÅ          ºÆ          ºÑ          Ýï          Þ¶          àÆ          àã          å©          å°          ê»          ð©          ò«          òº
    0x58d5,  0x568e,  0x8c6a,  0x6beb,  0x90dd,  0x597d,  0x8017,  0x53f7,  0x6d69,  0x8c89,  0x84bf,  0x8585,  0x55e5,  0x5686,  0x6fe0,  0x704f,  0x660a,  0x7693,  0x98a2,  0x869d,
// he  ºÇ          ºÈ          ºÉ          ºÊ          ºË          ºÌ          ºÍ          ºÎ          ºÏ          ºÐ          ºÑ          ºÒ          ºÓ          ºÔ          ºÕ          ºÖ          º×          ºØ          Ú­          ÛÀ          ÛÖ          àÀ          ãØ          êÂ          îÁ          ò¢          òÂ          ôç
    0x5475,  0x559d,  0x8377,  0x83cf,  0x6838,  0x79be,  0x548c,  0x4f55,  0x5408,  0x76d2,  0x8c89,  0x9602,  0x6cb3,  0x6db8,  0x8d6b,  0x8910,  0x9e64,  0x8d3a,  0x8bc3,  0x52be,  0x58d1,  0x55ec,  0x9616,  0x66f7,  0x76cd,  0x988c,  0x86b5,  0x7fee,
// hei  ºÙ          ºÚ
    0x563f,  0x9ed1,
// hen  ºÛ          ºÜ          ºÝ          ºÞ
    0x75d5,  0x5f88,  0x72e0,  0x6068,
// heng  ºß          ºà          ºá          ºâ          ºã          Þ¿          çñ          èì
    0x54fc,  0x4ea8,  0x6a2a,  0x8861,  0x6052,  0x8605,  0x73e9,  0x6841,
// hong  ºä          ºå          ºæ          ºç          ºè          ºé          ºê          ºë          ºì          Ùä          Ùê          Ú§          Ý¦          Þ®          Þ°          ãÈ          ãü
    0x8f70,  0x54c4,  0x70d8,  0x8679,  0x9e3f,  0x6d2a,  0x5b8f,  0x5f18,  0x7ea2,  0x9ec9,  0x8a07,  0x8ba7,  0x836d,  0x857b,  0x85a8,  0x95f3,  0x6cd3,
// hou  ºí          ºî          ºï          ºð          ºñ          ºò          ºó          Ü©          áá          åË          ðú          óó          ô×          ö×          ÷¿
    0x5589,  0x4faf,  0x7334,  0x543c,  0x539a,  0x5019,  0x540e,  0x5820,  0x5f8c,  0x9005,  0x760a,  0x7bcc,  0x7cc7,  0x9c8e,  0x9aba,
// hu  ºÍ          ºô       ºõ       ºö       º÷        ºø        ºù        ºú        ºû        ºü       ºý         ºþ        »¡        »¢        »£        »¤        »¥        »¦
    0x548c,  0x547c,  0x4e4e,  0x5ffd,  0x745a,  0x58f6,  0x846b,  0x80e1,  0x8774,  0x72d0,  0x7cca,  0x6e56,  0x5f27,  0x864e,  0x552c,  0x62a4,  0x4e92,  0x6caa,
//  »§          Ùü          ßü          àñ          á²          â©          âï          ã±          ä°          äï          çú          éÎ          éõ          ì²          ìÃ          ìÎ          ìæ          ìè          ìï          ð­          ðÀ          ðÉ          ð×          óË          õ­          õú          ÷½
    0x6237,  0x51b1,  0x553f,  0x56eb,  0x5cb5,  0x7322,  0x6019,  0x60da,  0x6d52,  0x6ef9,  0x7425,  0x69f2,  0x8f77,  0x89f3,  0x70c0,  0x7173,  0x623d,  0x6248,  0x795c,  0x74e0,  0x9e44,  0x9e55,  0x9e71,  0x7b0f,  0x9190,  0x659b,  0x9e58,
// hua  »¨          »©          »ª          »«          »¬          »­          »®          »¯          »°          æè          èë          í¹          îü
    0x82b1,  0x54d7,  0x534e,  0x733e,  0x6ed1,  0x753b,  0x5212,  0x5316,  0x8bdd,  0x9a85,  0x6866,  0x7809,  0x94e7,
// huai  »±          »²          »³          »´          »µ          õ×
    0x69d0,  0x5f8a,  0x6000,  0x6dee,  0x574f,  0x8e1d,
// huan  »¶          »·          »¸          »¹          »º          »»          »¼          »½          »¾          »¿          »À          »Á          »Â          »Ã          Û¨          Û¼          ÝÈ          ß§          à÷          âµ          ä¡          ä½          äñ          å¾          åÕ          çÙ          ïÌ          öé          ÷ß
    0x6b22,  0x73af,  0x6853,  0x8fd8,  0x7f13,  0x6362,  0x60a3,  0x5524,  0x75ea,  0x8c62,  0x7115,  0x6da3,  0x5ba6,  0x5e7b,  0x90c7,  0x5942,  0x8411,  0x64d0,  0x571c,  0x737e,  0x6d39,  0x6d63,  0x6f36,  0x5bf0,  0x902d,  0x7f33,  0x953e,  0x9ca9,  0x9b1f,
// huang  »Ä          »Å          »Æ          »Ç          »È          »É          »Ê          »Ë          »Ì          »Í          »Î          »Ï          »Ð          »Ñ          Úò          áå          äÒ          äê          åØ          è«          ëÁ          ñ¥          ó¨          óò          öü
    0x8352,  0x614c,  0x9ec4,  0x78fa,  0x8757,  0x7c27,  0x7687,  0x51f0,  0x60f6,  0x714c,  0x6643,  0x5e4c,  0x604d,  0x8c0e,  0x968d,  0x5fa8,  0x6e5f,  0x6f62,  0x9051,  0x749c,  0x8093,  0x7640,  0x87e5,  0x7bc1,  0x9cc7,
// hui  »Ò        »Ó        »Ô        »Õ       »Ö        »×        »Ø        »Ù       »Ú        »Û        »Ü        »Ý        »Þ        »ß        »à        »á        »â        »ã        »ä        »å         »æ       Ú¶       Üî        Üö        Þ¥         ßÔ        à¹        ãÄ        ä§
    0x7070,  0x6325,  0x8f89,  0x5fbd,  0x6062,  0x86d4,  0x56de,  0x6bc1,  0x6094,  0x6167,  0x5349,  0x60e0,  0x6666,  0x8d3f,  0x79fd,  0x4f1a,  0x70e9,  0x6c47,  0x8bb3,  0x8bf2,  0x7ed8,  0x8bd9,  0x8334,  0x835f,  0x8559,  0x54b4,  0x5599,  0x96b3,  0x6d04,
//  åç          çÀ          çõ          èí          êÍ          í£          ò³          ó³          ÷â
    0x5f57,  0x7f0b,  0x73f2,  0x6867,  0x6656,  0x605a,  0x867a,  0x87ea,  0x9ebe,
// hun  »ç          »è          »é          »ê          »ë          »ì          Ú»          âÆ          ãÔ          äã          çõ
    0x8364,  0x660f,  0x5a5a,  0x9b42,  0x6d51,  0x6df7,  0x8be8,  0x9984,  0x960d,  0x6eb7,  0x73f2,
// huo  ºÍ          »í          »î          »ï          »ð          »ñ          »ò          »ó          »ô          »õ          »ö          Øå          Þ½          ß«          àë          â·          îØ          ïÁ          ïì          ñë          ó¶
    0x548c,  0x8c41,  0x6d3b,  0x4f19,  0x706b,  0x83b7,  0x6216,  0x60d1,  0x970d,  0x8d27,  0x7978,  0x5290,  0x85ff,  0x6509,  0x56af,  0x5925,  0x94ac,  0x952a,  0x956c,  0x8020,  0x8816,
// ji  ¸ø          »÷       »ø        »ù        »ú        »û        »ü        »ý        »þ        ¼¡        ¼¢        ¼£        ¼¤        ¼¥        ¼¦        ¼§        ¼¨        ¼©        ¼ª        ¼«        ¼¬        ¼­        ¼®        ¼¯
    0x7ed9,  0x51fb,  0x573e,  0x57fa,  0x673a,  0x7578,  0x7a3d,  0x79ef,  0x7b95,  0x808c,  0x9965,  0x8ff9,  0x6fc0,  0x8ba5,  0x9e21,  0x59ec,  0x7ee9,  0x7f09,  0x5409,  0x6781,  0x68d8,  0x8f91,  0x7c4d,  0x96c6,
//  ¼°          ¼±          ¼²          ¼³       ¼´        ¼µ       ¼¶        ¼·        ¼¸        ¼¹        ¼º        ¼»        ¼¼        ¼½        ¼¾        ¼¿        ¼À        ¼Á        ¼Â        ¼Ã        ¼Ä        ¼Å        ¼Æ        ¼Ç
    0x53ca,  0x6025,  0x75be,  0x6c72,  0x5373,  0x5ac9,  0x7ea7,  0x6324,  0x51e0,  0x810a,  0x5df1,  0x84df,  0x6280,  0x5180,  0x5b63,  0x4f0e,  0x796d,  0x5242,  0x60b8,  0x6d4e,  0x5bc4,  0x5bc2,  0x8ba1,  0x8bb0,
//  ¼È          ¼É          ¼Ê          ¼Ë       ¼Ì        ¼Í       ½å       Æï        Ïµ        Ø½        ØÀ        ØÞ        Ù¥        ÙÊ        ÛÔ        Ü¸        ÜÁ        Üù        Ýð        Þª        Þá        ß´        ßÒ        ßâ        ßó
    0x65e2,  0x5fcc,  0x9645,  0x5993,  0x7ee7,  0x7eaa,  0x85c9,  0x9a91,  0x7cfb,  0x4e9f,  0x4e69,  0x525e,  0x4f76,  0x5048,  0x58bc,  0x82a8,  0x82b0,  0x8360,  0x84ba,  0x857a,  0x638e,  0x53fd,  0x54ad,  0x54dc,  0x5527,
//  á§          áÕ          ä©          åì          æ÷          çÜ          çá          é®          éê          êª          ê«          êå          êé          ê÷          ì´          í¶          î¿          ïú          ð¢          ñ¤          ò±          óÅ          óÇ          ôß          õÒ          õÕ          ö«          öÝ          öê          ÷Ù          ÷ä
    0x5c8c,  0x5d74,  0x6d0e,  0x5c50,  0x9aa5,  0x757f,  0x7391,  0x696b,  0x6b9b,  0x621f,  0x6222,  0x8d4d,  0x89ca,  0x7284,  0x9f51,  0x77f6,  0x7f81,  0x5d47,  0x7a37,  0x7620,  0x866e,  0x7b08,  0x7b04,  0x66a8,  0x8dfb,  0x8dfd,  0x9701,  0x9c9a,  0x9cab,  0x9afb,  0x9e82,
// jia  ¼Î          ¼Ï          ¼Ð          ¼Ñ          ¼Ò          ¼Ó          ¼Ô          ¼Õ          ¼Ö          ¼×          ¼Ø          ¼Ù          ¼Ú          ¼Û          ¼Ü          ¼Ý          ¼Þ          ÇÑ          Ù¤          Û£          Ýç          áµ          ä¤          åÈ          çì          ê©          ëÎ          í¢          îò          ïØ          ðè          ðý          òÌ          óÕ          ôÂ          õÊ
    0x5609,  0x67b7,  0x5939,  0x4f73,  0x5bb6,  0x52a0,  0x835a,  0x988a,  0x8d3e,  0x7532,  0x94be,  0x5047,  0x7a3c,  0x4ef7,  0x67b6,  0x9a7e,  0x5ac1,  0x8304,  0x4f3d,  0x90cf,  0x846d,  0x5cac,  0x6d43,  0x8fe6,  0x73c8,  0x621b,  0x80db,  0x605d,  0x94d7,  0x9553,  0x75c2,  0x7615,  0x86f1,  0x7b33,  0x8888,  0x8dcf,
// jian  ¼ß        ¼à       ¼á        ¼â        ¼ã        ¼ä       ¼å        ¼æ       ¼ç        ¼è        ¼é        ¼ê        ¼ë        ¼ì        ¼í        ¼î        ¼ï        ¼ð        ¼ñ        ¼ò        ¼ó        ¼ô        ¼õ        ¼ö        ¼÷        ¼ø        ¼ù        ¼ú        ¼û        ¼ü        ¼ý        ¼þ        ½¡        ½¢
    0x6b7c,  0x76d1,  0x575a,  0x5c16,  0x7b3a,  0x95f4,  0x714e,  0x517c,  0x80a9,  0x8270,  0x5978,  0x7f04,  0x8327,  0x68c0,  0x67ec,  0x78b1,  0x7877,  0x62e3,  0x6361,  0x7b80,  0x4fed,  0x526a,  0x51cf,  0x8350,  0x69db,  0x9274,  0x8df5,  0x8d31,  0x89c1,  0x952e,  0x7bad,  0x4ef6,  0x5065,  0x8230,
//  ½£          ½¤          ½¥          ½¦          ½§          ½¨          ÙÔ          ÚÉ          ÚÙ          ÝÑ          Ýó          Þö          àî          äÕ          å¿          åÀ          çÌ          èÅ          é¥          ê§          ê¯          êð          êù          ë¦          ëì          íú          ïµ          ðÏ          ñÐ          óÈ          ôå          õÝ          öä          ÷µ
    0x5251,  0x996f,  0x6e10,  0x6e85,  0x6da7,  0x5efa,  0x50ed,  0x8c0f,  0x8c2b,  0x83c5,  0x84b9,  0x641b,  0x56dd,  0x6e54,  0x8e47,  0x8b07,  0x7f23,  0x67a7,  0x6957,  0x620b,  0x622c,  0x726e,  0x728d,  0x6bfd,  0x8171,  0x7751,  0x950f,  0x9e63,  0x88e5,  0x7b15,  0x7fe6,  0x8e3a,  0x9ca3,  0x97af,
// jiang  ½©          ½ª          ½«          ½¬          ½­          ½®          ½¯          ½°          ½±          ½²          ½³          ½´          ½µ          Ç¿          Üü          ä®          ç­          çÖ          êñ          íä          ñð          ôÝ          ôø          ö¦
    0x50f5,  0x59dc,  0x5c06,  0x6d46,  0x6c5f,  0x7586,  0x848b,  0x6868,  0x5956,  0x8bb2,  0x5320,  0x9171,  0x964d,  0x5f3a,  0x8333,  0x6d1a,  0x7edb,  0x7f30,  0x729f,  0x7913,  0x8029,  0x7ce8,  0x8c47,  0x9753,
// jiao  ½¶       ½·        ½¸        ½¹        ½º        ½»        ½¼        ½½        ½¾        ½¿        ½À        ½Á        ½Â       ½Ã        ½Ä        ½Å        ½Æ       ½Ç       ½È         ½É        ½Ê        ½Ë        ½Ì        ½Í        ½Î        ½Ï
    0x8549,  0x6912,  0x7901,  0x7126,  0x80f6,  0x4ea4,  0x90ca,  0x6d47,  0x9a84,  0x5a07,  0x56bc,  0x6405,  0x94f0,  0x77eb,  0x4fa5,  0x811a,  0x72e1,  0x89d2,  0x997a,  0x7f34,  0x7ede,  0x527f,  0x6559,  0x9175,  0x8f7f,  0x8f83,
//  ½Ð          ½Ñ          Ð£          Ù®          ÙÕ          Ü´          Üú          ÞØ          àÝ          á½          áè          äÐ          æ¯          ë¸          ð¨          ðÔ          òÔ          õ´          õÓ          öÞ
    0x53eb,  0x7a96,  0x6821,  0x4f7c,  0x50ec,  0x827d,  0x832d,  0x6322,  0x564d,  0x5ce4,  0x5fbc,  0x6e6b,  0x59e3,  0x656b,  0x768e,  0x9e6a,  0x86df,  0x91ae,  0x8de4,  0x9c9b,
// jie  ½Ò        ½Ó        ½Ô       ½Õ        ½Ö        ½×        ½Ø        ½Ù        ½Ú        ½Û        ½Ü        ½Ý        ½Þ        ½ß        ½à        ½á        ½â        ½ã        ½ä        ½å        ½æ
    0x63ed,  0x63a5,  0x7686,  0x79f8,  0x8857,  0x9636,  0x622a,  0x52ab,  0x8282,  0x6854,  0x6770,  0x6377,  0x776b,  0x7aed,  0x6d01,  0x7ed3,  0x89e3,  0x59d0,  0x6212,  0x85c9,  0x82a5,
//  ½ç          ½è          ½é          ½ê          ½ë          ½ì          Ú¦          Úµ          Þ×          à®          àµ          æ¼          æÝ          èî          íÙ          ðÜ          ò¡          ò»          ôÉ          öÚ          ÷º
    0x754c,  0x501f,  0x4ecb,  0x75a5,  0x8beb,  0x5c4a,  0x8ba6,  0x8bd8,  0x62ee,  0x5588,  0x55df,  0x5a55,  0x5b51,  0x6840,  0x78a3,  0x7596,  0x9889,  0x86a7,  0x7faf,  0x9c92,  0x9ab1,
// jin  ½í          ½î          ½ï          ½ð          ½ñ          ½ò          ½ó          ½ô          ½õ          ½ö          ½÷          ½ø          ½ù          ½ú          ½û          ½ü          ½ý          ½þ          ¾¡          ¾¢          Úá          Ý£          ÝÀ          àä          âË          âÛ          æ¡          çÆ          èª          éÈ          êá          êî          ñÆ          ñæ
    0x5dfe,  0x7b4b,  0x65a4,  0x91d1,  0x4eca,  0x6d25,  0x895f,  0x7d27,  0x9526,  0x4ec5,  0x8c28,  0x8fdb,  0x9773,  0x664b,  0x7981,  0x8fd1,  0x70ec,  0x6d78,  0x5c3d,  0x52b2,  0x537a,  0x8369,  0x5807,  0x5664,  0x9991,  0x5ed1,  0x5997,  0x7f19,  0x747e,  0x69ff,  0x8d46,  0x89d0,  0x887f,  0x77dc,
// jing  ¾£        ¾¤       ¾¥       ¾¦        ¾§        ¾¨        ¾©        ¾ª        ¾«        ¾¬        ¾­        ¾®        ¾¯        ¾°       ¾±       ¾²        ¾³        ¾´        ¾µ        ¾¶        ¾·        ¾¸        ¾¹        ¾º        ¾»
    0x8346,  0x5162,  0x830e,  0x775b,  0x6676,  0x9cb8,  0x4eac,  0x60ca,  0x7cbe,  0x7cb3,  0x7ecf,  0x4e95,  0x8b66,  0x666f,  0x9888,  0x9759,  0x5883,  0x656c,  0x955c,  0x5f84,  0x75c9,  0x9756,  0x7adf,  0x7ade,  0x51c0,
//  ØÙ          ÙÓ          Úå          Ý¼          â°          ã½          ãþ          åÉ          åò          æº          ëÂ          ëÖ          ëæ          ìº          óä
    0x522d,  0x5106,  0x9631,  0x83c1,  0x734d,  0x61ac,  0x6cfe,  0x8ff3,  0x5f2a,  0x5a67,  0x80bc,  0x80eb,  0x8148,  0x65cc,  0x7b90,
// jiong  ¾¼          ¾½          åÄ          ìç
    0x70af,  0x7a98,  0x8fe5,  0x6243,
// jiu  ¾¾          ¾¿          ¾À          ¾Á          ¾Â          ¾Ã          ¾Ä          ¾Å          ¾Æ          ¾Ç          ¾È          ¾É          ¾Ê          ¾Ë          ¾Ì          ¾Í          ¾Î          ÙÖ          à±          ãÎ          èÑ          èê          ð¯          ðÕ          ôñ          ÷Ý
    0x63ea,  0x7a76,  0x7ea0,  0x7396,  0x97ed,  0x4e45,  0x7078,  0x4e5d,  0x9152,  0x53a9,  0x6551,  0x65e7,  0x81fc,  0x8205,  0x548e,  0x5c31,  0x759a,  0x50e6,  0x557e,  0x9604,  0x67e9,  0x6855,  0x9e20,  0x9e6b,  0x8d73,  0x9b0f,
// ju  ³µ          ¾Ï        ¾Ð       ¾Ñ        ¾Ò       ¾Ó       ¾Ô        ¾Õ        ¾Ö        ¾×        ¾Ø         ¾Ù        ¾Ú        ¾Û        ¾Ü        ¾Ý       ¾Þ        ¾ß        ¾à          ¾á          ¾â      ¾ã        ¾ä       ¾å       ¾æ          ¾ç       ÇÒ        ÙÆ
    0x8f66,  0x97a0,  0x62d8,  0x72d9,  0x75bd,  0x5c45,  0x9a79,  0x83ca,  0x5c40,  0x5480,  0x77e9,  0x4e3e,  0x6cae,  0x805a,  0x62d2,  0x636e,  0x5de8,  0x5177,  0x8ddd,  0x8e1e,  0x952f,  0x4ff1,  0x53e5,  0x60e7,  0x70ac,  0x5267,  0x4e14,  0x5028,
//  Úª          ÜÄ          ÜÚ          Üì          Þä          åá          åð          è¢          èÛ          é§          é°          é·          éÙ          êø          ì«          îÒ          ï¸          ñÀ          ñÕ          ôò          õ¶          õá          ö´          öÂ          ÷¶
    0x8bb5,  0x82e3,  0x82f4,  0x8392,  0x63ac,  0x907d,  0x5c66,  0x741a,  0x67b8,  0x6910,  0x6998,  0x6989,  0x6a58,  0x728b,  0x98d3,  0x949c,  0x9514,  0x7aad,  0x88fe,  0x8d84,  0x91b5,  0x8e3d,  0x9f83,  0x96ce,  0x97ab,
// juan  ¾è          ¾é          ¾ê          ¾ë          ¾ì          ¾í          ¾î          Û²          áú          ä¸          èð          îÃ          ïÃ          ïÔ          öÁ
    0x6350,  0x9e43,  0x5a1f,  0x5026,  0x7737,  0x5377,  0x7ee2,  0x9104,  0x72f7,  0x6d93,  0x684a,  0x8832,  0x9529,  0x954c,  0x96bd,
// jue  ½À          ¾ï          ¾ð          ¾ñ          ¾ò          ¾ó          ¾ô          ¾õ          ¾ö          ¾÷          ¾ø          ØÊ          Øã          ÚÜ          ÛÇ          Þ§          àÙ          àå          áÈ          â±          æÞ          çå          èö          éÓ          ìß          ïã          õê          õû
    0x56bc,  0x6485,  0x652b,  0x6289,  0x6398,  0x5014,  0x7235,  0x89c9,  0x51b3,  0x8bc0,  0x7edd,  0x53a5,  0x5282,  0x8c32,  0x77cd,  0x8568,  0x5658,  0x5671,  0x5d1b,  0x7357,  0x5b53,  0x73cf,  0x6877,  0x6a5b,  0x721d,  0x9562,  0x8e76,  0x89d6,
// jun  ¾ù          ¾ú          ¾û          ¾ü          ¾ý          ¾þ          ¿¡          ¿¢          ¿£          ¿¤          ¿¥          ÞÜ          ñä          óÞ          ÷å
    0x5747,  0x83cc,  0x94a7,  0x519b,  0x541b,  0x5cfb,  0x4fca,  0x7ae3,  0x6d5a,  0x90e1,  0x9a8f,  0x6343,  0x76b2,  0x7b60,  0x9e87,
// ka  ¿¦          ¿§          ¿¨          ¿©          Øû          ßÇ          ëÌ
    0x5580,  0x5496,  0x5361,  0x54af,  0x4f67,  0x5494,  0x80e9,
// kai  ¿ª          ¿«          ¿¬          ¿­          ¿®          ØÜ          Ûî          ÝÜ          âé          âý          îø          ï´          ïÇ
    0x5f00,  0x63e9,  0x6977,  0x51ef,  0x6168,  0x5240,  0x57b2,  0x8488,  0x5ffe,  0x607a,  0x94e0,  0x950e,  0x9534,
// kan  ¼÷          ¿¯          ¿°          ¿±          ¿²          ¿³          ¿´          Ù©          Ý¨          ãÛ          ê¬          íè          î«
    0x69db,  0x520a,  0x582a,  0x52d8,  0x574e,  0x780d,  0x770b,  0x4f83,  0x83b0,  0x961a,  0x6221,  0x9f9b,  0x77b0,
// kang  ¿µ          ¿¶          ¿·          ¿¸          ¿¹          ¿º          ¿»          Øø          ãÊ          îÖ
    0x5eb7,  0x6177,  0x7ce0,  0x625b,  0x6297,  0x4ea2,  0x7095,  0x4f09,  0x95f6,  0x94aa,
// kao  ¿¼          ¿½          ¿¾          ¿¿          åê          èà          êû          îí
    0x8003,  0x62f7,  0x70e4,  0x9760,  0x5c3b,  0x6832,  0x7292,  0x94d0,
// ke  ¿À          ¿Á          ¿Â          ¿Ã          ¿Ä          ¿Å          ¿Æ          ¿Ç          ¿È          ¿É          ¿Ê          ¿Ë          ¿Ì          ¿Í          ¿Î          à¾          á³          ã¡          äÛ          æì          ç¼          çæ          éð          ë´          î§          îÝ          ï¾          ïý          ðâ          ñ½          ò¤          òò          ÷Á
    0x5777,  0x82db,  0x67ef,  0x68f5,  0x78d5,  0x9897,  0x79d1,  0x58f3,  0x54b3,  0x53ef,  0x6e34,  0x514b,  0x523b,  0x5ba2,  0x8bfe,  0x55d1,  0x5ca2,  0x606a,  0x6e98,  0x9a92,  0x7f02,  0x73c2,  0x8f72,  0x6c2a,  0x778c,  0x94b6,  0x951e,  0x7a1e,  0x75b4,  0x7aa0,  0x988f,  0x874c,  0x9ac1,
// ken  ¿Ï          ¿Ð          ¿Ñ          ¿Ò          ñÌ          ö¸
    0x80af,  0x5543,  0x57a6,  0x6073,  0x88c9,  0x9f88,
// keng  ¿Ó          ¿Ô          ï¬
    0x5751,  0x542d,  0x94ff,
// kong  ¿Õ          ¿Ö          ¿×          ¿Ø          ÙÅ          áÇ          óí
    0x7a7a,  0x6050,  0x5b54,  0x63a7,  0x5025,  0x5d06,  0x7b9c,
// kou  ¿Ù          ¿Ú          ¿Û          ¿Ü          ÜÒ          Þ¢          ßµ          àí          íî          óØ
    0x62a0,  0x53e3,  0x6263,  0x5bc7,  0x82a4,  0x853b,  0x53e9,  0x56d7,  0x770d,  0x7b58,
// ku  ¿Ý          ¿Þ          ¿ß          ¿à          ¿á          ¿â          ¿ã          ØÚ          Ü¥          à·          ç«          ÷¼
    0x67af,  0x54ed,  0x7a9f,  0x82e6,  0x9177,  0x5e93,  0x88e4,  0x5233,  0x5800,  0x55be,  0x7ed4,  0x9ab7,
// kua  ¿ä          ¿å          ¿æ          ¿ç          ¿è          Ù¨
    0x5938,  0x57ae,  0x630e,  0x8de8,  0x80ef,  0x4f89,
// kuai  »á          ¿é          ¿ê          ¿ë          ¿ì          Øá          Û¦          ßà          áö          ä«          ëÚ
    0x4f1a,  0x5757,  0x7b77,  0x4fa9,  0x5feb,  0x84af,  0x90d0,  0x54d9,  0x72ef,  0x6d4d,  0x810d,
// kuan  ¿í          ¿î          ÷Å
    0x5bbd,  0x6b3e,  0x9acb,
// kuang  ¿ï          ¿ð          ¿ñ          ¿ò          ¿ó          ¿ô          ¿õ          ¿ö          Ú²          Ú¿          Ú÷          ÛÛ          ÞÅ          ßÑ          æþ          êÜ
    0x5321,  0x7b50,  0x72c2,  0x6846,  0x77ff,  0x7736,  0x65f7,  0x51b5,  0x8bd3,  0x8bf3,  0x909d,  0x5739,  0x593c,  0x54d0,  0x7ea9,  0x8d36,
// kui  ¿÷          ¿ø          ¿ù          ¿ú          ¿û          ¿ü          ¿ý          ¿þ          À¡          À¢          À£          Ø¸          ØÑ          Ùç          Úó          ÝÞ          Þñ          à­          à°          ã¦          ã´          åÓ          êÒ          î¥          ñù          òñ          óñ          õÍ
    0x4e8f,  0x76d4,  0x5cbf,  0x7aa5,  0x8475,  0x594e,  0x9b41,  0x5080,  0x9988,  0x6127,  0x6e83,  0x9997,  0x532e,  0x5914,  0x9697,  0x8489,  0x63c6,  0x55b9,  0x559f,  0x609d,  0x6126,  0x9035,  0x668c,  0x777d,  0x8069,  0x8770,  0x7bd1,  0x8dec,
// kun  À¤          À¥          À¦          À§          ã§          ãÍ          çû          ï¿          õ«          öï          ÷Õ
    0x5764,  0x6606,  0x6346,  0x56f0,  0x6083,  0x9603,  0x7428,  0x951f,  0x918c,  0x9cb2,  0x9ae1,
// kuo  À¨          À©          Àª          À«          òÒ
    0x62ec,  0x6269,  0x5ed3,  0x9614,  0x86de,
// la  À¬          À­          À®          À¯          À°          À±          À²          Âä          ØÝ          åå          ê¹          íÇ          ðø
    0x5783,  0x62c9,  0x5587,  0x8721,  0x814a,  0x8fa3,  0x5566,  0x843d,  0x524c,  0x908b,  0x65ef,  0x782c,  0x760c,
// lai  À³          À´          Àµ          áÁ          áâ          äµ          äþ          êã          íù          ïª          ñ®          ô¥
    0x83b1,  0x6765,  0x8d56,  0x5d03,  0x5f95,  0x6d9e,  0x6fd1,  0x8d49,  0x7750,  0x94fc,  0x765e,  0x7c41,
// lan  À¶          À·          À¸          À¹          Àº          À»          À¼          À½          À¾          À¿          ÀÀ          ÀÁ          ÀÂ          ÀÃ          ÀÄ          á°          äí          é­          ìµ          î½          ïç          ñÜ
    0x84dd,  0x5a6a,  0x680f,  0x62e6,  0x7bee,  0x9611,  0x5170,  0x6f9c,  0x8c30,  0x63fd,  0x89c8,  0x61d2,  0x7f06,  0x70c2,  0x6ee5,  0x5c9a,  0x6f24,  0x6984,  0x6593,  0x7f71,  0x9567,  0x8934,
// lang  ÀÅ          ÀÆ          ÀÇ          ÀÈ          ÀÉ          ÀÊ          ÀË          Ýõ          à¥          ãÏ          ïü          òë
    0x7405,  0x6994,  0x72fc,  0x5eca,  0x90ce,  0x6717,  0x6d6a,  0x8497,  0x5577,  0x9606,  0x7a02,  0x8782,
// lao  ÀÌ          ÀÍ          ÀÎ          ÀÏ          ÀÐ          ÀÑ          ÀÒ          ÀÓ          ÀÔ          ÁÊ          ßë          áÀ          âá          èá          îî          ï©          ðì          ñì          õ²
    0x635e,  0x52b3,  0x7262,  0x8001,  0x4f6c,  0x59e5,  0x916a,  0x70d9,  0x6d9d,  0x6f66,  0x5520,  0x5d02,  0x5fc9,  0x6833,  0x94d1,  0x94f9,  0x75e8,  0x8022,  0x91aa,
// le  ÀÕ          ÀÖ          ÁË          Øì          ß·          ãî          ÷¦
    0x52d2,  0x4e50,  0x4e86,  0x4ec2,  0x53fb,  0x6cd0,  0x9cd3,
// lei  À×          ÀØ          ÀÙ          ÀÚ          ÀÛ          ÀÜ          ÀÝ          ÀÞ          Àß          Àà          Àá          Ùú          Ú³          àÏ          æÐ          çÐ          éÛ          ñç          õª
    0x96f7,  0x956d,  0x857e,  0x78ca,  0x7d2f,  0x5121,  0x5792,  0x64c2,  0x808b,  0x7c7b,  0x6cea,  0x7fb8,  0x8bd4,  0x561e,  0x5ad8,  0x7f27,  0x6a91,  0x8012,  0x9179,
// leng  Àâ          Àã          Àä          Ü¨          ã¶
    0x68f1,  0x695e,  0x51b7,  0x5844,  0x6123,
// li  Àå          Àæ        Àç        Àè        Àé        Àê        Àë        Àì        Àí        Àî        Àï        Àð       Àñ        Àò        Àó        Àô        Àõ        Àö        À÷        Àø        Àù
    0x5398,  0x68a8,  0x7281,  0x9ece,  0x7bf1,  0x72f8,  0x79bb,  0x6f13,  0x7406,  0x674e,  0x91cc,  0x9ca4,  0x793c,  0x8389,  0x8354,  0x540f,  0x6817,  0x4e3d,  0x5389,  0x52b1,  0x783e,
//  Àú          Àû          Àü        Àý        Àþ          Á¡       Á¢        Á£        Á¤        Á¥       Á¦        Á§        Á¨        Ù³        Ùµ        Ûª        ÛÞ        ÜÂ        Ý°       Ýñ        Þ¼
    0x5386,  0x5229,  0x5088,  0x4f8b,  0x4fd0,  0x75e2,  0x7acb,  0x7c92,  0x6ca5,  0x96b6,  0x529b,  0x7483,  0x54e9,  0x4fea,  0x4fda,  0x90e6,  0x575c,  0x82c8,  0x8385,  0x84e0,  0x85dc,
//  ß¿          à¦          à¬          áû          äà          å¢          åÎ          æ²          æË          æê          çÊ          èÀ          èÝ          éö          ì¢          ìå          íÂ          îº          î¾          ï®          ð¿          ðÝ          ðß          òÃ          òÛ          ó»          óÒ          óö          ôÏ          õ·          õÈ          ö¨          öâ          ÷¯          ÷ó
    0x5456,  0x5533,  0x55b1,  0x7301,  0x6ea7,  0x6fa7,  0x9026,  0x5a0c,  0x5ae0,  0x9a8a,  0x7f21,  0x67a5,  0x680e,  0x8f79,  0x81a6,  0x623e,  0x783a,  0x8a48,  0x7f79,  0x9502,  0x9e42,  0x75a0,  0x75ac,  0x86ce,  0x870a,  0x8821,  0x7b20,  0x7be5,  0x7c9d,  0x91b4,  0x8dde,  0x96f3,  0x9ca1,  0x9ce2,  0x9ee7,
// lia  Á©
    0x4fe9,
// lian  Áª          Á«          Á¬          Á­          Á®          Á¯          Á°          Á±          Á²          Á³          Á´          Áµ          Á¶          Á·          Ýü          ÞÆ          äò          å¥          çö          é¬          éç          ì¡          ñÍ          ñÏ          ó¹          öã
    0x8054,  0x83b2,  0x8fde,  0x9570,  0x5ec9,  0x601c,  0x6d9f,  0x5e18,  0x655b,  0x8138,  0x94fe,  0x604b,  0x70bc,  0x7ec3,  0x8539,  0x5941,  0x6f4b,  0x6fc2,  0x740f,  0x695d,  0x6b93,  0x81c1,  0x88e2,  0x88e3,  0x880a,  0x9ca2,
// liang  Á©          Á¸          Á¹          Áº          Á»          Á¼          Á½          Á¾          Á¿          ÁÀ          ÁÁ          ÁÂ          Ü®          Ý¹          é£          ï¶          õÔ          ö¦          ÷Ë
    0x4fe9,  0x7cae,  0x51c9,  0x6881,  0x7cb1,  0x826f,  0x4e24,  0x8f86,  0x91cf,  0x667e,  0x4eae,  0x8c05,  0x589a,  0x83a8,  0x690b,  0x9512,  0x8e09,  0x9753,  0x9b49,
// liao  ÁÃ          ÁÄ          ÁÅ          ÁÆ          ÁÇ          ÁÈ          ÁÉ          ÁÊ          ÁË          ÁÌ          ÁÍ          ÁÎ          ÁÏ          Þ¤          ÞÍ          àÚ          â²          å¼          çÔ          îÉ          ðÓ
    0x64a9,  0x804a,  0x50da,  0x7597,  0x71ce,  0x5be5,  0x8fbd,  0x6f66,  0x4e86,  0x6482,  0x9563,  0x5ed6,  0x6599,  0x84fc,  0x5c25,  0x5639,  0x7360,  0x5bee,  0x7f2d,  0x948c,  0x9e69,
// lie  ÁÐ          ÁÑ          ÁÒ          ÁÓ          ÁÔ          Ùý          Ûø          Þæ          ßÖ          ä£          ôó          õñ          ÷à
    0x5217,  0x88c2,  0x70c8,  0x52a3,  0x730e,  0x51bd,  0x57d2,  0x6369,  0x54a7,  0x6d0c,  0x8d94,  0x8e90,  0x9b23,
// lin  ÁÕ          ÁÖ          Á×          ÁØ          ÁÙ          ÁÚ          ÁÛ          ÁÜ          ÁÝ          ÁÞ          Áß          Áà          Ýþ          ßø          á×          âÞ          ãÁ          åà          éÝ          ê¥          î¬          ôÔ          õï          ÷ë
    0x7433,  0x6797,  0x78f7,  0x9716,  0x4e34,  0x90bb,  0x9cde,  0x6dcb,  0x51db,  0x8d41,  0x541d,  0x62ce,  0x853a,  0x5549,  0x5d99,  0x5eea,  0x61d4,  0x9074,  0x6aa9,  0x8f9a,  0x77b5,  0x7cbc,  0x8e8f,  0x9e9f,
// ling  Áá          Áâ          Áã          Áä          Áå          Áæ          Áç          Áè          Áé          Áê          Áë          Áì          Áí          Áî          Û¹          Üß          ßÊ          àò          ãö          ç±          èÚ          èù          ê²          ñö          òÈ          ôá          öì
    0x73b2,  0x83f1,  0x96f6,  0x9f84,  0x94c3,  0x4f36,  0x7f9a,  0x51cc,  0x7075,  0x9675,  0x5cad,  0x9886,  0x53e6,  0x4ee4,  0x9143,  0x82d3,  0x5464,  0x56f9,  0x6ce0,  0x7eeb,  0x67c3,  0x68c2,  0x74f4,  0x8046,  0x86c9,  0x7fce,  0x9cae,
// liu  Áï          Áð          Áñ          Áò          Áó          Áô          Áõ          Áö          Á÷          Áø          Áù          ä¯          åÞ          æò          ç¸          ì¼          ìÖ          ï³          ïÖ          ðÒ          öÌ
    0x6e9c,  0x7409,  0x69b4,  0x786b,  0x998f,  0x7559,  0x5218,  0x7624,  0x6d41,  0x67f3,  0x516d,  0x6d4f,  0x905b,  0x9a9d,  0x7efa,  0x65d2,  0x7198,  0x950d,  0x954f,  0x9e68,  0x938f,
// long  Áú          Áû          Áü          Áý          Áþ          Â¡          Â¢          Â£          Â¤          Ûâ          Ü×          ãñ          çç          èÐ          ëÊ          íÃ          ñª
    0x9f99,  0x804b,  0x5499,  0x7b3c,  0x7abf,  0x9686,  0x5784,  0x62e2,  0x9647,  0x5785,  0x830f,  0x6cf7,  0x73d1,  0x680a,  0x80e7,  0x783b,  0x7643,
// lou  Â¥          Â¦          Â§          Â¨          Â©          Âª          Â¶          ÙÍ          Ýä          à¶          áÐ          ïÎ          ðü          ñï          ò÷          ÷Ã
    0x697c,  0x5a04,  0x6402,  0x7bd3,  0x6f0f,  0x964b,  0x9732,  0x507b,  0x848c,  0x55bd,  0x5d5d,  0x9542,  0x7618,  0x8027,  0x877c,  0x9ac5,
// lu  Â«        Â¬        Â­        Â®       Â¯        Â°        Â±        Â²        Â³        Â´        Âµ          Â¶        Â·       Â¸        Â¹        Âº        Â»
    0x82a6,  0x5362,  0x9885,  0x5e90,  0x7089,  0x63b3,  0x5364,  0x864f,  0x9c81,  0x9e93,  0x788c,  0x9732,  0x8def,  0x8d42,  0x9e7f,  0x6f5e,  0x7984,
//  Â¼          Â½          Â¾          Ûä          ß£          àà          ãò          äË          äõ          åÖ          è´          èÓ          éÖ          éñ          éû          ê¤          ëª          ëÍ          ïå          ðµ          ðØ          óü          ôµ          öÔ
    0x5f55,  0x9646,  0x622e,  0x5786,  0x64b8,  0x565c,  0x6cf8,  0x6e0c,  0x6f09,  0x902f,  0x7490,  0x680c,  0x6a79,  0x8f73,  0x8f82,  0x8f98,  0x6c07,  0x80ea,  0x9565,  0x9e2c,  0x9e6d,  0x7c0f,  0x823b,  0x9c88,
// luan  ÂÍ          ÂÎ          ÂÏ          ÂÐ          ÂÑ          ÂÒ          Ùõ          æ®          èï          ð½          öÇ
    0x5ce6,  0x631b,  0x5b6a,  0x6ee6,  0x5375,  0x4e71,  0x8114,  0x5a08,  0x683e,  0x9e3e,  0x92ae,
// lue  ÂÓ          ÂÔ          ï²
    0x63a0,  0x7565,  0x950a,
// lun  ÂÕ          ÂÖ          Â×          ÂØ          ÂÙ          ÂÚ          ÂÛ          àð
    0x62a1,  0x8f6e,  0x4f26,  0x4ed1,  0x6ca6,  0x7eb6,  0x8bba,  0x56f5,
// luo  ¿©          ÀÓ          ÂÜ          ÂÝ          ÂÞ          Âß          Âà          Âá          Ââ          Âã          Âä          Âå          Âæ          Âç          ÙÀ          Ùù          Üý          Þû          â¤          ãø          äð          çó          é¡          ëá          ïÝ          ñ§          õÈ          öÃ
    0x54af,  0x70d9,  0x841d,  0x87ba,  0x7f57,  0x903b,  0x9523,  0x7ba9,  0x9aa1,  0x88f8,  0x843d,  0x6d1b,  0x9a86,  0x7edc,  0x502e,  0x8803,  0x8366,  0x645e,  0x7321,  0x6cfa,  0x6f2f,  0x73de,  0x6924,  0x8136,  0x9559,  0x7630,  0x8dde,  0x96d2,
// lv  Â¿          ÂÀ          ÂÁ          ÂÂ          ÂÃ          ÂÄ          ÂÅ          ÂÆ          ÂÇ          ÂÈ          ÂÉ          ÂÊ          ÂË          ÂÌ          ÙÍ          ÞÛ          ãÌ          éµ          ëö          ïù          ñÚ
    0x9a74,  0x5415,  0x94dd,  0x4fa3,  0x65c5,  0x5c65,  0x5c61,  0x7f15,  0x8651,  0x6c2f,  0x5f8b,  0x7387,  0x6ee4,  0x7eff,  0x507b,  0x634b,  0x95fe,  0x6988,  0x8182,  0x7a06,  0x891b,
// m  ß¼
    0x5452,
// ma  Âè          Âé          Âê          Âë          Âì          Âí          Âî          Âï          Âð          Ä¨          ßé          áï          è¿          ó¡          ÷á
    0x5988,  0x9ebb,  0x739b,  0x7801,  0x8682,  0x9a6c,  0x9a82,  0x561b,  0x5417,  0x62b9,  0x551b,  0x72b8,  0x6769,  0x87c6,  0x9ebd,
// mai  Âñ          Âò          Âó          Âô          Âõ          Âö          Û½          Ý¤          ö²
    0x57cb,  0x4e70,  0x9ea6,  0x5356,  0x8fc8,  0x8109,  0x52a2,  0x836c,  0x973e,
// man  Â÷          Âø          Âù          Âú          Âû          Âü          Âý          Âþ          Ã¡          Ü¬          á£          çÏ          ì×          ïÜ          ò©          òý          ÷©          ÷´
    0x7792,  0x9992,  0x86ee,  0x6ee1,  0x8513,  0x66fc,  0x6162,  0x6f2b,  0x8c29,  0x5881,  0x5e54,  0x7f26,  0x71b3,  0x9558,  0x989f,  0x87a8,  0x9cd7,  0x9794,
// mang  Ã¢          Ã£          Ã¤          Ã¥          Ã¦          Ã§          Úø          äÝ          íË          òþ
    0x8292,  0x832b,  0x76f2,  0x6c13,  0x5fd9,  0x83bd,  0x9099,  0x6f2d,  0x786d,  0x87d2,
// mao  Ã¨          Ã©          Ãª          Ã«          Ã¬          Ã­          Ã®          Ã¯          Ã°          Ã±          Ã²          Ã³          Ùó          Üâ          á¹          ã÷          è£          êÄ          êó          ë£          ì¸          í®          î¦          òú          ó±          ÷Ö
    0x732b,  0x8305,  0x951a,  0x6bdb,  0x77db,  0x94c6,  0x536f,  0x8302,  0x5192,  0x5e3d,  0x8c8c,  0x8d38,  0x88a4,  0x8306,  0x5cc1,  0x6cd6,  0x7441,  0x6634,  0x7266,  0x8004,  0x65c4,  0x61cb,  0x7780,  0x8765,  0x87ca,  0x9ae6,
// me  Ã´          ÷á
    0x4e48,  0x9ebd,
// mei  Ãµ          Ã¶          Ã·          Ã¸          Ã¹          Ãº          Ã»          Ã¼          Ã½          Ã¾          Ã¿          ÃÀ          ÃÁ          ÃÂ          ÃÃ          ÃÄ          ÃÓ          Ý®          áÒ          â­          ä¼          äØ          é¹          ïÑ          ðÌ          ñÇ          ÷È
    0x73ab,  0x679a,  0x6885,  0x9176,  0x9709,  0x7164,  0x6ca1,  0x7709,  0x5a92,  0x9541,  0x6bcf,  0x7f8e,  0x6627,  0x5bd0,  0x59b9,  0x5a9a,  0x7cdc,  0x8393,  0x5d4b,  0x7338,  0x6d7c,  0x6e44,  0x6963,  0x9545,  0x9e5b,  0x8882,  0x9b45,
// men  ÃÅ          ÃÆ          ÃÇ          ÞÑ          ìË          í¯          îÍ
    0x95e8,  0x95f7,  0x4eec,  0x626a,  0x7116,  0x61d1,  0x9494,
// meng  ÃÈ          ÃÉ          ÃÊ          ÃË          ÃÌ          ÃÍ          ÃÎ          ÃÏ          ÛÂ          Ýù          Þ«          ãÂ          ëü          íæ          òµ          òì          ó·          ô»          ô¿
    0x840c,  0x8499,  0x6aac,  0x76df,  0x9530,  0x731b,  0x68a6,  0x5b5f,  0x52d0,  0x750d,  0x77a2,  0x61f5,  0x6726,  0x791e,  0x867b,  0x8722,  0x8813,  0x824b,  0x8268,
// mi  ÃÐ          ÃÑ          ÃÒ          ÃÓ          ÃÔ          ÃÕ          ÃÖ          Ã×          ÃØ          ÃÙ          ÃÚ          ÃÛ          ÃÜ          ÃÝ          ØÂ          Ú×          ßä          à×          â¨          ãè          åµ          åô          ëß          ìò          ôÍ          ÷ã          ÷ç
    0x772f,  0x919a,  0x9761,  0x7cdc,  0x8ff7,  0x8c1c,  0x5f25,  0x7c73,  0x79d8,  0x89c5,  0x6ccc,  0x871c,  0x5bc6,  0x5e42,  0x8288,  0x8c27,  0x54aa,  0x5627,  0x7315,  0x6c68,  0x5b93,  0x5f2d,  0x8112,  0x7962,  0x6549,  0x7e3b,  0x9e8b,
// mian  ÃÞ          Ãß          Ãà          Ãá          Ãâ          Ãã          Ãä          Ãå          Ãæ          ãæ          äÅ          äÏ          ëï          íí
    0x68c9,  0x7720,  0x7ef5,  0x5195,  0x514d,  0x52c9,  0x5a29,  0x7f05,  0x9762,  0x6c94,  0x6e11,  0x6e4e,  0x817c,  0x7704,
// miao  Ãç          Ãè          Ãé          Ãê          Ãë          Ãì          Ãí          Ãî          ß÷          åã          ç¿          çÑ          èÂ          íµ          íð          ðÅ
    0x82d7,  0x63cf,  0x7784,  0x85d0,  0x79d2,  0x6e3a,  0x5e99,  0x5999,  0x55b5,  0x9088,  0x7f08,  0x7f2a,  0x676a,  0x6dfc,  0x7707,  0x9e4b,
// mie  Ãï          Ãð          Ø¿          ßã          óº          óú
    0x8511,  0x706d,  0x4e5c,  0x54a9,  0x881b,  0x7bfe,
// min  Ãñ          Ãò          Ãó          Ãô          Ãõ          Ãö          Üå          áº          ãÉ          ãý          çÅ          çä          çë          íª          ö¼          ÷ª
    0x6c11,  0x62bf,  0x76bf,  0x654f,  0x60af,  0x95fd,  0x82e0,  0x5cb7,  0x95f5,  0x6cef,  0x7f17,  0x739f,  0x73c9,  0x610d,  0x9efe,  0x9cd8,
// ming  Ã÷          Ãø          Ãù          Ãú          Ãû          Ãü          Ú¤          Üø          äé          êÔ          î¨          õ¤
    0x660e,  0x879f,  0x9e23,  0x94ed,  0x540d,  0x547d,  0x51a5,  0x8317,  0x6e9f,  0x669d,  0x7791,  0x9169,
// miu  Ãý          çÑ
    0x8c2c,  0x7f2a,
// mo  Âö          Ã»          Ãþ          Ä¡          Ä¢          Ä£          Ä¤          Ä¥          Ä¦          Ä§          Ä¨          Ä©          Äª          Ä«          Ä¬          Ä­          Ä®          Ä¯          Ä°          ÚÓ          ÜÔ          Ýë          âÉ          æÆ          æÖ          éâ          ïÒ          ï÷          ñ¢          ñò          õö          õø          ÷á
    0x8109,  0x6ca1,  0x6478,  0x6479,  0x8611,  0x6a21,  0x819c,  0x78e8,  0x6469,  0x9b54,  0x62b9,  0x672b,  0x83ab,  0x58a8,  0x9ed8,  0x6cab,  0x6f20,  0x5bde,  0x964c,  0x8c1f,  0x8309,  0x84e6,  0x998d,  0x5aeb,  0x5b37,  0x6b81,  0x9546,  0x79e3,  0x763c,  0x8031,  0x8c8a,  0x8c98,  0x9ebd,
// mou  Ä±          Ä²          Ä³          Ù°          ßè          çÑ          íø          òÖ          öÊ
    0x8c0b,  0x725f,  0x67d0,  0x4f94,  0x54de,  0x7f2a,  0x7738,  0x86d1,  0x936a,
// mu  Ä²          Ä´          Äµ          Ä¶          Ä·          Ä¸          Ä¹          Äº          Ä»          Ä¼          Ä½          Ä¾          Ä¿          ÄÀ          ÄÁ          ÄÂ          Øï          Ûé          ÜÙ          ãå          ë¤          îâ
    0x725f,  0x62c7,  0x7261,  0x4ea9,  0x59c6,  0x6bcd,  0x5893,  0x66ae,  0x5e55,  0x52df,  0x6155,  0x6728,  0x76ee,  0x7766,  0x7267,  0x7a46,  0x4eeb,  0x5776,  0x82dc,  0x6c90,  0x6bea,  0x94bc,
// na  ÄÃ          ÄÄ          ÄÅ          ÄÆ          ÄÇ          ÄÈ          ÄÉ          Ú«          Þà          ëÇ          ïÕ          ñÄ
    0x62ff,  0x54ea,  0x5450,  0x94a0,  0x90a3,  0x5a1c,  0x7eb3,  0x8bb7,  0x637a,  0x80ad,  0x954e,  0x8872,
// nai  ÄÊ          ÄË          ÄÌ          ÄÍ          ÄÎ          Ø¾          Ù¦          Üµ          ÝÁ          èÍ
    0x6c16,  0x4e43,  0x5976,  0x8010,  0x5948,  0x9f10,  0x4f74,  0x827f,  0x8418,  0x67f0,
// nan  ÄÏ          ÄÐ          ÄÑ          à«          àî          àï          éª          ëî          òï          ôö
    0x5357,  0x7537,  0x96be,  0x5583,  0x56dd,  0x56e1,  0x6960,  0x8169,  0x877b,  0x8d67,
// nang  ÄÒ          ß­          àì          âÎ          êÙ
    0x56ca,  0x652e,  0x56d4,  0x9995,  0x66e9,
// nao  ÄÓ          ÄÔ          ÄÕ          ÄÖ          Ä×          Ø«          Ûñ          ßÎ          â®          è§          íÐ          îó          òÍ
    0x6320,  0x8111,  0x607c,  0x95f9,  0x6dd6,  0x5b6c,  0x57b4,  0x5476,  0x7331,  0x7459,  0x7847,  0x94d9,  0x86f2,
// ne  ÄØ          Ú«
    0x5462,  0x8bb7,
// nei  ÄÙ          ÄÚ
    0x9981,  0x5185,
// nen  ÄÛ          í¥
    0x5ae9,  0x6041,
// neng  ÄÜ
    0x80fd,
// ni  ÄÝ          ÄÞ          Äß          Äà          Äá          Äâ          Äã          Ää          Äå          Äæ          Äç          Ù£          Ûè          ÞÂ          â¥          âõ          êÇ          ì»          íþ          îê          öò
    0x59ae,  0x9713,  0x502a,  0x6ce5,  0x5c3c,  0x62df,  0x4f60,  0x533f,  0x817b,  0x9006,  0x6eba,  0x4f32,  0x576d,  0x863c,  0x730a,  0x6029,  0x6635,  0x65ce,  0x7768,  0x94cc,  0x9cb5,
// nian  Äè          Äé          Äê          Äë          Äì          Äí          Äî          Õ³          Ø¥          Ûþ          éý          ð¤          öÓ          öó
    0x852b,  0x62c8,  0x5e74,  0x78be,  0x64b5,  0x637b,  0x5ff5,  0x7c98,  0x5eff,  0x57dd,  0x8f87,  0x9ecf,  0x9c87,  0x9cb6,
// niang  Äï          Äð
    0x5a18,  0x917f,
// niao  Äñ          Äò          Üà          æÕ          ëå          ôÁ
    0x9e1f,  0x5c3f,  0x8311,  0x5b32,  0x8132,  0x8885,
// nie  Äó          Äô          Äõ          Äö          Ä÷          Äø          Äù          Ø¿          Úí          ÞÁ          à¿          ò¨          ô«          õæ
    0x634f,  0x8042,  0x5b7d,  0x556e,  0x954a,  0x954d,  0x6d85,  0x4e5c,  0x9667,  0x8616,  0x55eb,  0x989e,  0x81ec,  0x8e51,
// nin  Äú
    0x60a8,
// ning  Äû          Äü          Äý          Äþ          Å¡          Å¢          Øú          ßÌ          å¸          ñ÷
    0x67e0,  0x72de,  0x51dd,  0x5b81,  0x62e7,  0x6cde,  0x4f5e,  0x549b,  0x752f,  0x804d,
// niu  Å£          Å¤          Å¥          Å¦          ÞÖ          áð          âî          æ¤
    0x725b,  0x626d,  0x94ae,  0x7ebd,  0x62d7,  0x72c3,  0x5ff8,  0x599e,
// nong  Å§          Å¨          Å©          Åª          Ù¯          ßæ
    0x8113,  0x6d53,  0x519c,  0x5f04,  0x4fac,  0x54dd,
// nou  ññ
    0x8028,
// nu  Å«          Å¬          Å­          åó          æÀ          æÛ          æå
    0x5974,  0x52aa,  0x6012,  0x5f29,  0x80ec,  0x5b65,  0x9a7d,
// nuan  Å¯
    0x6696,
// nue  Å°          Å±          Å²
    0x8650,  0x759f,  0x632a,
// nuo  Å³          Å´          Åµ          ÙÐ          Þù          ßö          ï»
    0x61e6,  0x7cef,  0x8bfa,  0x50a9,  0x6426,  0x558f,  0x9518,
// nv  Å®          í¤          îÏ          ô¬
    0x5973,  0x6067,  0x9495,  0x8844,
// o  Å¶          àÞ
    0x54e6,  0x5662,
// ou  Å·          Å¸          Å¹          Åº          Å»          Å¼          Å½          Ú©          âæ          ê±          ñî
    0x6b27,  0x9e25,  0x6bb4,  0x85d5,  0x5455,  0x5076,  0x6ca4,  0x8bb4,  0x6004,  0x74ef,  0x8026,
// pa  °Ç          °Ò          Å¾          Å¿          ÅÀ          ÅÁ          ÅÂ          ÅÃ          Ýâ          èË          óá
    0x6252,  0x8019,  0x556a,  0x8db4,  0x722c,  0x5e15,  0x6015,  0x7436,  0x8469,  0x6777,  0x7b62,
// pai  ÅÄ          ÅÅ          ÅÆ          ÅÇ          ÅÈ          ÅÉ          Ù½          Ýå          ßß
    0x62cd,  0x6392,  0x724c,  0x5f98,  0x6e43,  0x6d3e,  0x4ff3,  0x848e,  0x54cc,
// pan  ÅÊ          ÅË          ÅÌ          ÅÍ          ÅÎ          ÅÏ          ÅÐ          ÅÑ          ÅÖ          ÞÕ          ãÝ          ãú          ñÈ          ñá          ó´          õç
    0x6500,  0x6f58,  0x76d8,  0x78d0,  0x76fc,  0x7554,  0x5224,  0x53db,  0x80d6,  0x62da,  0x723f,  0x6cee,  0x88a2,  0x897b,  0x87e0,  0x8e52,
// pang  °õ          ÅÒ          ÅÓ          ÅÔ          ÅÕ          ÅÖ          áÝ          âº          äè          åÌ          ë¶          ó¦
    0x78c5,  0x4e53,  0x5e9e,  0x65c1,  0x802a,  0x80d6,  0x5f77,  0x5902,  0x6ec2,  0x9004,  0x6535,  0x8783,
// pao  Å×          ÅØ          ÅÙ          ÅÚ          ÅÛ          ÅÜ          ÅÝ          ÞË          áó          âÒ          ëã          ðå
    0x629b,  0x5486,  0x5228,  0x70ae,  0x888d,  0x8dd1,  0x6ce1,  0x530f,  0x72cd,  0x5e96,  0x812c,  0x75b1,
// pei  ÅÞ          Åß          Åà          Åá          Åâ          Åã          Åä          Åå          Åæ          àÎ          àú          ì·          ïÂ          õ¬          ö¬
    0x5478,  0x80da,  0x57f9,  0x88f4,  0x8d54,  0x966a,  0x914d,  0x4f69,  0x6c9b,  0x8f94,  0x5e14,  0x65c6,  0x952b,  0x9185,  0x9708,
// pen  Åç          Åè          äÔ
    0x55b7,  0x76c6,  0x6e53,
// peng  Åé          Åê          Åë          Åì          Åí          Åî          Åï          Åð          Åñ          Åò          Åó          Åô          Åõ          Åö          Ü¡          àØ          âñ          ó²
    0x7830,  0x62a8,  0x70f9,  0x6f8e,  0x5f6d,  0x84ec,  0x68da,  0x787c,  0x7bf7,  0x81a8,  0x670b,  0x9e4f,  0x6367,  0x78b0,  0x580b,  0x562d,  0x6026,  0x87db,
// pi  ±»          ±Ù        ·ñ       Å÷      Åø          Åù        Åú       Åû        Åü        Åý        Åþ        Æ¡        Æ¢        Æ£        Æ¤        Æ¥       Æ¦       Æ§        Æ¨          Æ©
    0x88ab,  0x8f9f,  0x5426,  0x576f,  0x7812,  0x9739,  0x6279,  0x62ab,  0x5288,  0x7435,  0x6bd7,  0x5564,  0x813e,  0x75b2,  0x76ae,  0x5339,  0x75de,  0x50fb,  0x5c41,  0x8b6c,
//  Ø§          Øò          Úð          Úü          Û¯          ÛÜ          Ûý          Ü±          ÜÅ          ß¨          àè          âÏ          äÄ          æÇ          ç¢          èÁ          ê¶          î¼          îë          ñ±          ñâ          ò·          òç          õù
    0x4e15,  0x4ef3,  0x9674,  0x90b3,  0x90eb,  0x572e,  0x57e4,  0x9f19,  0x8298,  0x64d7,  0x567c,  0x5e80,  0x6de0,  0x5ab2,  0x7eb0,  0x6787,  0x7513,  0x7f74,  0x94cd,  0x7656,  0x758b,  0x868d,  0x8731,  0x8c94,
// pian  ±ã          Æª          Æ«          Æ¬          Æ­          ÚÒ          æé          êú          ëÝ          ôæ          õä
    0x4fbf,  0x7bc7,  0x504f,  0x7247,  0x9a97,  0x8c1d,  0x9a88,  0x728f,  0x80fc,  0x7fe9,  0x8e41,
// piao  Æ®          Æ¯          Æ°          Æ±          Øâ          Ý³          àÑ          æÎ          çÎ          éè          î©          óª
    0x98d8,  0x6f02,  0x74e2,  0x7968,  0x527d,  0x83a9,  0x560c,  0x5ad6,  0x7f25,  0x6b8d,  0x779f,  0x87b5,
// pie  Æ²          Æ³          Ø¯          ÜÖ          áê          ë­
    0x6487,  0x77a5,  0x4e3f,  0x82e4,  0x5f61,  0x6c15,
// pin  Æ´          Æµ          Æ¶          Æ·          Æ¸          æ°          æÉ          é¯          êò          ò­
    0x62fc,  0x9891,  0x8d2b,  0x54c1,  0x8058,  0x59d8,  0x5ad4,  0x6980,  0x725d,  0x98a6,
// ping  ·ë          Æ¹          Æº          Æ»          Æ¼          Æ½          Æ¾          Æ¿          ÆÀ          ÆÁ          Ù·          æ³          èÒ          öÒ
    0x51af,  0x4e52,  0x576a,  0x82f9,  0x840d,  0x5e73,  0x51ed,  0x74f6,  0x8bc4,  0x5c4f,  0x4fdc,  0x5a09,  0x67b0,  0x9c86,
// po  ÆÂ          ÆÃ          ÆÄ          ÆÅ          ÆÆ          ÆÇ          ÆÈ          ÆÉ          ØÏ          Û¶          çê          îÇ          îÞ          ð«          óÍ
    0x5761,  0x6cfc,  0x9887,  0x5a46,  0x7834,  0x9b44,  0x8feb,  0x7c95,  0x53f5,  0x9131,  0x73c0,  0x948b,  0x94b7,  0x76a4,  0x7b38,
// pou  ÆÊ          Ùö          Þå
    0x5256,  0x88d2,  0x638a,
// pu  ±©          ÆË          ÆÌ          ÆÍ          ÆÎ          ÆÏ          ÆÐ          ÆÑ          ÆÒ          ÆÓ          ÆÔ          ÆÕ          ÆÖ          Æ×          ÆØ          ÆÙ          Ùé          àÛ          äß          å§          è±          ë«          ïä          ïè          õë
    0x66b4,  0x6251,  0x94fa,  0x4ec6,  0x8386,  0x8461,  0x83e9,  0x84b2,  0x57d4,  0x6734,  0x5703,  0x666e,  0x6d66,  0x8c31,  0x66dd,  0x7011,  0x530d,  0x5657,  0x6ea5,  0x6fee,  0x749e,  0x6c06,  0x9564,  0x9568,  0x8e7c,
// qi  ¼©        ÆÚ        ÆÛ       ÆÜ         ÆÝ        ÆÞ       Æß       Æà          Æá       Æâ        Æã        Æä        Æå        Ææ        Æç        Æè        Æé        Æê        Æë          Æì        Æí        Æî       Æï       Æð        Æñ
    0x7f09,  0x671f,  0x6b3a,  0x6816,  0x621a,  0x59bb,  0x4e03,  0x51c4,  0x6f06,  0x67d2,  0x6c8f,  0x5176,  0x68cb,  0x5947,  0x6b67,  0x7566,  0x5d0e,  0x8110,  0x9f50,  0x65d7,  0x7948,  0x7941,  0x9a91,  0x8d77,  0x5c82,
//  Æò          Æó          Æô          Æõ       Æö        Æ÷        Æø        Æù       Æú        Æû        Æü        Æý        ØÁ        Ù¹        Ûß       Ü»        ÜÎ        Ý½        ÝÂ        ÝÝ       Þ­        àÒ        á¨        áª       ãà
    0x4e5e,  0x4f01,  0x542f,  0x5951,  0x780c,  0x5668,  0x6c14,  0x8fc4,  0x5f03,  0x6c7d,  0x6ce3,  0x8bab,  0x4e93,  0x4fdf,  0x573b,  0x8291,  0x82aa,  0x8401,  0x840b,  0x847a,  0x8572,  0x5601,  0x5c7a,  0x5c90,  0x6c54,
//  ä¿          æë          ç²          ç÷          çù          è½          èç          éÊ          êÈ          ì÷          í¬          íÓ          ñý          òÓ          òà          ôë          ÷¢          ÷è
    0x6dc7,  0x9a90,  0x7eee,  0x742a,  0x7426,  0x675e,  0x6864,  0x69ed,  0x8006,  0x797a,  0x61a9,  0x789b,  0x9880,  0x86f4,  0x871e,  0x7da6,  0x9ccd,  0x9e92,
// qia  ¼Ð          Æþ          Ç¡          Ç¢          ÝÖ          ñÊ          ÷Ä
    0x5939,  0x6390,  0x6070,  0x6d3d,  0x845c,  0x88b7,  0x9ac2,
// qian  Ç£       Ç¤       Ç¥       Ç¦        Ç§        Ç¨        Ç©        Çª        Ç«       Ç¬       Ç­        Ç®          Ç¯        Ç°        Ç±        Ç²        Ç³        Ç´        Çµ        Ç¶        Ç·        Ç¸        ÏË        Ù»       ÙÝ
    0x7275,  0x6266,  0x948e,  0x94c5,  0x5343,  0x8fc1,  0x7b7e,  0x4edf,  0x8c26,  0x4e7e,  0x9ed4,  0x94b1,  0x94b3,  0x524d,  0x6f5c,  0x9063,  0x6d45,  0x8c34,  0x5811,  0x5d4c,  0x6b20,  0x6b49,  0x7ea4,  0x5029,  0x4f65,
//  Úä          Ü·          ÜÍ          Üç          Ý¡          Þç          á©          ã¥          ã»          å¹          åº          å½          ç×          èý          ëÉ          í©          îÔ          ò¯          óé
    0x9621,  0x828a,  0x82a1,  0x831c,  0x8368,  0x63ae,  0x5c8d,  0x60ad,  0x614a,  0x9a9e,  0x6434,  0x8930,  0x7f31,  0x6920,  0x80b7,  0x6106,  0x94a4,  0x8654,  0x7b9d,
// qiang  ½«          Ç¹          Çº          Ç»          Ç¼          Ç½          Ç¾          Ç¿          ÇÀ          ãÞ          æÍ          éÉ          ê¨          ìÁ          ïº          ïÏ          ïê          ñß          òÞ          ôÇ          õÄ
    0x5c06,  0x67aa,  0x545b,  0x8154,  0x7f8c,  0x5899,  0x8537,  0x5f3a,  0x62a2,  0x6215,  0x5af1,  0x6a2f,  0x6217,  0x709d,  0x9516,  0x9535,  0x956a,  0x8941,  0x8723,  0x7f9f,  0x8dc4,
// qiao  ¿Ç          ÇÁ          ÇÂ          ÇÃ          ÇÄ          ÇÅ          ÇÆ          ÇÇ          ÇÈ          ÇÉ          ÇÊ          ÇË          ÇÌ          ÇÍ          ÇÎ          ÇÏ          Ï÷          Øä          Ú½          ÚÛ          Üñ          á½          ã¸          ã¾          çØ          éÔ          íÍ          õÎ          ÷³
    0x58f3,  0x6a47,  0x9539,  0x6572,  0x6084,  0x6865,  0x77a7,  0x4e54,  0x4fa8,  0x5de7,  0x9798,  0x64ac,  0x7fd8,  0x5ced,  0x4fcf,  0x7a8d,  0x524a,  0x5281,  0x8bee,  0x8c2f,  0x835e,  0x5ce4,  0x6100,  0x6194,  0x7f32,  0x6a35,  0x7857,  0x8df7,  0x9792,
// qie  ÇÐ          ÇÑ          ÇÒ          ÇÓ          ÇÔ          Û§          ã«          ã»          æª          êü          ïÆ          óæ          ôò
    0x5207,  0x8304,  0x4e14,  0x602f,  0x7a83,  0x90c4,  0x60ec,  0x614a,  0x59be,  0x6308,  0x9532,  0x7ba7,  0x8d84,
// qin  ÇÕ          ÇÖ          Ç×          ÇØ          ÇÙ          ÇÚ          ÇÛ          ÇÜ          ÇÝ          ÇÞ          Çß          ÜË          Þì          ßÄ          àº          àß          äÚ          éÕ          ï·          ñæ          ñû          òû          ôÀ
    0x94a6,  0x4fb5,  0x4eb2,  0x79e6,  0x7434,  0x52e4,  0x82b9,  0x64d2,  0x79bd,  0x5bdd,  0x6c81,  0x82a9,  0x63ff,  0x5423,  0x55ea,  0x5659,  0x6eb1,  0x6a8e,  0x9513,  0x77dc,  0x8983,  0x8793,  0x887e,
// qing  Çà          Çá          Çâ          Çã          Çä          Çå          Çæ          Çç          Çè          Çé          Çê          Çë          Çì          ÜÜ          àõ          éÑ          íà          òß          óÀ          ôì          ö¥          öë          ÷ô
    0x9752,  0x8f7b,  0x6c22,  0x503e,  0x537f,  0x6e05,  0x64ce,  0x6674,  0x6c30,  0x60c5,  0x9877,  0x8bf7,  0x5e86,  0x82d8,  0x570a,  0x6aa0,  0x78ec,  0x873b,  0x7f44,  0x7dae,  0x8b26,  0x9cad,  0x9ee5,
// qiong  Çí          Çî          Úö          Üä          ñ·          òË          óÌ          õ¼          öÆ
    0x743c,  0x7a77,  0x909b,  0x8315,  0x7a79,  0x86e9,  0x7b47,  0x8deb,  0x928e,
// qiu  Çï          Çð          Çñ          Çò          Çó          Çô          Çõ          Çö          Ù´          ÛÏ          áì          äÐ          åÏ          åÙ          é±          êä          ò°          òÇ          òø          ôÃ          ôÜ          öú          ÷ü
    0x79cb,  0x4e18,  0x90b1,  0x7403,  0x6c42,  0x56da,  0x914b,  0x6cc5,  0x4fc5,  0x5def,  0x72b0,  0x6e6b,  0x9011,  0x9052,  0x6978,  0x8d47,  0x866c,  0x86af,  0x8764,  0x88d8,  0x7cd7,  0x9cc5,  0x9f3d,
// qu  Ç÷          Çø          Çù          Çú          Çû          Çü          Çý          Çþ          È¡          È¢          È£          È¤          È¥          Ú°          Û¾          ÜÄ          Þ¡          Þ¾          á«          áé          ãÖ          è³          êï          ë¬          ëÔ          ìî          íá          ð¶          ñ³          òÐ          ó½          ôð          öÄ          ÷ñ
    0x8d8b,  0x533a,  0x86c6,  0x66f2,  0x8eaf,  0x5c48,  0x9a71,  0x6e20,  0x53d6,  0x5a36,  0x9f8b,  0x8da3,  0x53bb,  0x8bce,  0x52ac,  0x82e3,  0x8556,  0x8627,  0x5c96,  0x8862,  0x9612,  0x74a9,  0x89d1,  0x6c0d,  0x6710,  0x795b,  0x78f2,  0x9e32,  0x766f,  0x86d0,  0x883c,  0x9eb4,  0x77bf,  0x9ee2,
// quan  È¦          È§          È¨          È©          Èª          È«          È¬          È­          È®          È¯          È°          Ú¹          Üõ          áë          ãª          ç¹          éú          î°          îý          òé          óÜ          ÷Ü
    0x5708,  0x98a7,  0x6743,  0x919b,  0x6cc9,  0x5168,  0x75ca,  0x62f3,  0x72ac,  0x5238,  0x529d,  0x8be0,  0x8343,  0x72ad,  0x609b,  0x7efb,  0x8f81,  0x754e,  0x94e8,  0x8737,  0x7b4c,  0x9b08,
// que  È±          È²          È³          È´          Èµ          È¶          È·          È¸          ã×          ãÚ          í¨
    0x7f3a,  0x7094,  0x7638,  0x5374,  0x9e4a,  0x69b7,  0x786e,  0x96c0,  0x9615,  0x9619,  0x60ab,
// qun  È¹          Èº          åÒ          ÷å
    0x88d9,  0x7fa4,  0x9021,  0x9e87,
// ran  È»          È¼          È½          È¾          ÜÛ          òÅ          ÷×
    0x7136,  0x71c3,  0x5189,  0x67d3,  0x82d2,  0x86ba,  0x9aef,
// rang  È¿          ÈÀ          ÈÁ          ÈÂ          ÈÃ          ìü          ð¦
    0x74e4,  0x58e4,  0x6518,  0x56b7,  0x8ba9,  0x79b3,  0x7a70,
// rao  ÈÄ          ÈÅ          ÈÆ          Üé          æ¬          èã
    0x9976,  0x6270,  0x7ed5,  0x835b,  0x5a06,  0x6861,
// re  ÈÇ          ÈÈ          ßö
    0x60f9,  0x70ed,  0x558f,
// ren  ÈÉ          ÈÊ          ÈË          ÈÌ          ÈÍ          ÈÎ          ÈÏ          ÈÐ          ÈÑ          ÈÒ          Øð          Üó          â¿          éí          ïþ          ñÅ
    0x58ec,  0x4ec1,  0x4eba,  0x5fcd,  0x97e7,  0x4efb,  0x8ba4,  0x5203,  0x598a,  0x7eab,  0x4ede,  0x834f,  0x996a,  0x8f6b,  0x7a14,  0x887d,
// reng  ÈÓ          ÈÔ
    0x6254,  0x4ecd,
// ri  ÈÕ
    0x65e5,
// rong  ÈÖ          È×          ÈØ          ÈÙ          ÈÚ          ÈÛ          ÈÜ          ÈÝ          ÈÞ          Èß          áÉ          áõ          éÅ          ëÀ          òî
    0x620e,  0x8338,  0x84c9,  0x8363,  0x878d,  0x7194,  0x6eb6,  0x5bb9,  0x7ed2,  0x5197,  0x5d58,  0x72e8,  0x6995,  0x809c,  0x877e,
// rou  Èà          Èá          Èâ          ôÛ          õå          ÷·
    0x63c9,  0x67d4,  0x8089,  0x7cc5,  0x8e42,  0x97a3,
// ru  Èã          Èä          Èå          Èæ          Èç          Èè          Èé          Èê          Èë          Èì          Ýê          Þ¸          àé          ä²          äá          å¦          çÈ          ï¨          ñà          ò¬
    0x8339,  0x8815,  0x5112,  0x5b7a,  0x5982,  0x8fb1,  0x4e73,  0x6c5d,  0x5165,  0x8925,  0x84d0,  0x85b7,  0x5685,  0x6d33,  0x6ebd,  0x6fe1,  0x7f1b,  0x94f7,  0x8966,  0x98a5,
// ruan  Èí          Èî          ëÃ
    0x8f6f,  0x962e,  0x670a,
// rui  Èï          Èð          Èñ          ÜÇ          Þ¨          èÄ          î£          ò¸
    0x854a,  0x745e,  0x9510,  0x82ae,  0x8564,  0x6798,  0x777f,  0x868b,
// run  Èò          Èó
    0x95f0,  0x6da6,
// ruo  Èô          Èõ          Ù¼          óè
    0x82e5,  0x5f31,  0x504c,  0x7bac,
// sa  Èö          È÷          Èø          Ø¦          êý          ëÛ          ìª
    0x6492,  0x6d12,  0x8428,  0x5345,  0x6332,  0x810e,  0x98d2,
// sai  Èù          Èú          Èû          Èü          àç
    0x816e,  0x9cc3,  0x585e,  0x8d5b,  0x567b,
// san  Èý          Èþ          É¡          É¢          Øí          áê          âÌ          ë§          ôÖ
    0x4e09,  0x53c1,  0x4f1e,  0x6563,  0x4ee8,  0x5f61,  0x9993,  0x6bf5,  0x7cc1,
// sang  É£          É¤          É¥          Þú          íß          òª
    0x6851,  0x55d3,  0x4e27,  0x6421,  0x78c9,  0x98a1,
// sao  É¦          É§          É¨          É©          Ü£          çÒ          ëý          ðþ          öþ
    0x6414,  0x9a9a,  0x626b,  0x5ac2,  0x57fd,  0x7f2b,  0x81ca,  0x7619,  0x9ccb,
// se  Èû          Éª          É«          É¬          ØÄ          ï¤          ð£
    0x585e,  0x745f,  0x8272,  0x6da9,  0x556c,  0x94ef,  0x7a51,
// sen  É­
    0x68ee,
// seng  É®
    0x50e7,
// sha  É¯          É°          É±          É²          É³          É´          Éµ          É¶          É·          ÏÃ          ßþ          êý          ì¦          ï¡          ðð          ôÄ          ö®          öè
    0x838e,  0x7802,  0x6740,  0x5239,  0x6c99,  0x7eb1,  0x50bb,  0x5565,  0x715e,  0x53a6,  0x553c,  0x6332,  0x6b43,  0x94e9,  0x75e7,  0x88df,  0x970e,  0x9ca8,
// shai  É¸          É¹          õ§
    0x7b5b,  0x6652,  0x917e,
// shan  Éº          É»          É¼          É½          É¾          É¿          ÉÀ          ÉÁ          ÉÂ          ÉÃ          ÉÄ          ÉÅ          ÉÆ          ÉÇ          ÉÈ          ÉÉ          Õ¤          Øß          Ú¨          Û·          Ûï          ÜÏ          äú          æ©          æÓ          æó          ëþ          îÌ          ðÞ          óµ          ô®          õÇ          ÷­
    0x73ca,  0x82eb,  0x6749,  0x5c71,  0x5220,  0x717d,  0x886b,  0x95ea,  0x9655,  0x64c5,  0x8d61,  0x81b3,  0x5584,  0x6c55,  0x6247,  0x7f2e,  0x6805,  0x5261,  0x8baa,  0x912f,  0x57cf,  0x829f,  0x6f78,  0x59d7,  0x5b17,  0x9a9f,  0x81bb,  0x9490,  0x759d,  0x87ee,  0x8222,  0x8dda,  0x9cdd,
// shang  ÉÊ          ÉË          ÉÌ          ÉÍ          ÉÎ          ÉÏ          ÉÐ          ÉÑ          Ûð          ãñ          ç´          éä          ìØ          õü
    0x5892,  0x4f24,  0x5546,  0x8d4f,  0x664c,  0x4e0a,  0x5c1a,  0x88f3,  0x57a7,  0x6cf7,  0x7ef1,  0x6b87,  0x71b5,  0x89de,
// shao  ÇÊ          ÉÒ          ÉÓ          ÉÔ          ÉÕ          ÉÖ          É×          ÉØ          ÉÙ          ÉÚ          ÉÛ          ÉÜ          Û¿          Üæ          äû          è¼          òÙ          óâ          ô¹
    0x9798,  0x68a2,  0x634e,  0x7a0d,  0x70e7,  0x828d,  0x52fa,  0x97f6,  0x5c11,  0x54e8,  0x90b5,  0x7ecd,  0x52ad,  0x82d5,  0x6f72,  0x6753,  0x86f8,  0x7b72,  0x8244,
// she  ÉÝ          ÉÞ          Éß          Éà          Éá          Éâ          Éã          Éä          Éå          Éæ          Éç          Éè          ØÇ          ÙÜ          Þé          â¦          äÜ          ì¨          î´          ÷ê
    0x5962,  0x8d4a,  0x86c7,  0x820c,  0x820d,  0x8d66,  0x6444,  0x5c04,  0x6151,  0x6d89,  0x793e,  0x8bbe,  0x538d,  0x4f58,  0x63f2,  0x731e,  0x6ee0,  0x6b59,  0x7572,  0x9e9d,
// shen  ²Î          Éé          Éê          Éë          Éì          Éí          Éî          Éï          Éð          Éñ          Éò          Éó          Éô          Éõ          Éö          É÷          Éø          Ê²          Ú·          ÚÅ          Ý·          ÝØ          ßÓ          äÉ          é©          ëÏ          ïò          ò×          ôÖ
    0x53c2,  0x7837,  0x7533,  0x547b,  0x4f38,  0x8eab,  0x6df1,  0x5a20,  0x7ec5,  0x795e,  0x6c88,  0x5ba1,  0x5a76,  0x751a,  0x80be,  0x614e,  0x6e17,  0x4ec0,  0x8bdc,  0x8c02,  0x8398,  0x845a,  0x54c2,  0x6e16,  0x6939,  0x80c2,  0x77e7,  0x8703,  0x7cc1,
// sheng  ³Ë          Éù          Éú          Éû          Éü          Éý          Éþ          Ê¡          Ê¢          Ê£          Ê¤          Ê¥          áÓ          äÅ          êÉ          íò          óÏ
    0x4e58,  0x58f0,  0x751f,  0x7525,  0x7272,  0x5347,  0x7ef3,  0x7701,  0x76db,  0x5269,  0x80dc,  0x5723,  0x5d4a,  0x6e11,  0x665f,  0x771a,  0x7b19,
// shi  ³×       Ê¦        Ê§        Ê¨        Ê©       Êª       Ê«          Ê¬       Ê­       Ê®        Ê¯        Ê°          Ê±        Ê²        Ê³       Ê´        Êµ        Ê¶          Ê·          Ê¸
    0x5319,  0x5e08,  0x5931,  0x72ee,  0x65bd,  0x6e7f,  0x8bd7,  0x5c38,  0x8671,  0x5341,  0x77f3,  0x62fe,  0x65f6,  0x4ec0,  0x98df,  0x8680,  0x5b9e,  0x8bc6,  0x53f2,  0x77e2,
//  Ê¹          Êº          Ê»          Ê¼        Ê½       Ê¾        Ê¿       ÊÀ        ÊÁ        ÊÂ        ÊÃ        ÊÄ        ÊÅ        ÊÆ          ÊÇ        ÊÈ        ÊÉ        ÊÊ        ÊË        ÊÌ
    0x4f7f,  0x5c4e,  0x9a76,  0x59cb,  0x5f0f,  0x793a,  0x58eb,  0x4e16,  0x67ff,  0x4e8b,  0x62ed,  0x8a93,  0x901d,  0x52bf,  0x662f,  0x55dc,  0x566c,  0x9002,  0x4ed5,  0x4f8d,
//  ÊÍ          ÊÎ          ÊÏ          ÊÐ          ÊÑ          ÊÒ          ÊÓ          ÊÔ          Ðê          ÚÖ          Ûõ          Ýª          Ýé          ß±          éø          êÛ          ìÂ          ìê          îæ          ó§          óÂ          óß          õ¹          öå          öõ
    0x91ca,  0x9970,  0x6c0f,  0x5e02,  0x6043,  0x5ba4,  0x89c6,  0x8bd5,  0x5618,  0x8c25,  0x57d8,  0x83b3,  0x84cd,  0x5f11,  0x8f7c,  0x8d33,  0x70bb,  0x793b,  0x94c8,  0x87ab,  0x8210,  0x7b6e,  0x8c55,  0x9ca5,  0x9cba,
// shou  ÊÕ          ÊÖ          Ê×          ÊØ          ÊÙ          ÊÚ          ÊÛ          ÊÜ          ÊÝ          ÊÞ          á÷          ç·          ô¼
    0x6536,  0x624b,  0x9996,  0x5b88,  0x5bff,  0x6388,  0x552e,  0x53d7,  0x7626,  0x517d,  0x72e9,  0x7ef6,  0x824f,
// shu  Êß       Êà       Êá        Êâ        Êã        Êä        Êå        Êæ        Êç        Êè        Êé        Êê        Êë        Êì        Êí        Êî
    0x852c,  0x67a2,  0x68b3,  0x6b8a,  0x6292,  0x8f93,  0x53d4,  0x8212,  0x6dd1,  0x758f,  0x4e66,  0x8d4e,  0x5b70,  0x719f,  0x85af,  0x6691,
//  Êï          Êð          Êñ          Êò          Êó          Êô          Êõ          Êö          Ê÷          Êø          Êù          Êú          Êû          Êü          Êý          Êþ          Ë¡          Óá          Ø­          Ù¿          ÛÓ          ÝÄ          Þó          ãð          äø          æ­          ç£          ë¨          ëò          ì¯          ïø
    0x66d9,  0x7f72,  0x8700,  0x9ecd,  0x9f20,  0x5c5e,  0x672f,  0x8ff0,  0x6811,  0x675f,  0x620d,  0x7ad6,  0x5885,  0x5eb6,  0x6570,  0x6f31,  0x6055,  0x4fde,  0x4e28,  0x500f,  0x587e,  0x83fd,  0x6445,  0x6cad,  0x6f8d,  0x59dd,  0x7ebe,  0x6bf9,  0x8167,  0x6bb3,  0x79eb,
// shua  Ë¢          Ë£          à§
    0x5237,  0x800d,  0x5530,
// shuai  ÂÊ          Ë¤          Ë¥          Ë¦          Ë§          ó°
    0x7387,  0x6454,  0x8870,  0x7529,  0x5e05,  0x87c0,
// shuan  Ë¨          Ë©          ãÅ          äÌ
    0x6813,  0x62f4,  0x95e9,  0x6dae,
// shuang  Ëª          Ë«          Ë¬          æ×
    0x971c,  0x53cc,  0x723d,  0x5b40,
// shui  Ë­          Ë®          Ë¯          Ë°          Ëµ
    0x8c01,  0x6c34,  0x7761,  0x7a0e,  0x8bf4,
// shun  Ë±          Ë²          Ë³          Ë´
    0x542e,  0x77ac,  0x987a,  0x821c,
// shuo  Êý          Ëµ          Ë¶          Ë·          Ë¸          Ýô          Þ÷          åù          éÃ          îå
    0x6570,  0x8bf4,  0x7855,  0x6714,  0x70c1,  0x84b4,  0x6420,  0x5981,  0x69ca,  0x94c4,
// si  Ê³          Ë¹          Ëº          Ë»          Ë¼          Ë½          Ë¾          Ë¿          ËÀ          ËÁ          ËÂ          ËÃ          ËÄ          ËÅ          ËÆ          ËÇ          ËÈ          ØË          Ù¹          Ùî          ÛÌ          ßÐ          ãá          ãô          äù          æ¦          æá          çÁ          ìë          ïÈ          ð¸          ñê          òÏ          óÓ
    0x98df,  0x65af,  0x6495,  0x5636,  0x601d,  0x79c1,  0x53f8,  0x4e1d,  0x6b7b,  0x8086,  0x5bfa,  0x55e3,  0x56db,  0x4f3a,  0x4f3c,  0x9972,  0x5df3,  0x53ae,  0x4fdf,  0x5155,  0x53b6,  0x549d,  0x6c5c,  0x6cd7,  0x6f8c,  0x59d2,  0x9a77,  0x7f0c,  0x7940,  0x9536,  0x9e36,  0x801c,  0x86f3,  0x7b25,
// song  ËÉ          ËÊ          ËË          ËÌ          ËÍ          ËÎ          ËÏ          ËÐ          Ú¡          Ý¿          áÂ          áÔ          âì          ã¤          äÁ          ñµ
    0x677e,  0x8038,  0x6002,  0x9882,  0x9001,  0x5b8b,  0x8bbc,  0x8bf5,  0x51c7,  0x83d8,  0x5d27,  0x5d69,  0x5fea,  0x609a,  0x6dde,  0x7ae6,
// sou  ËÑ          ËÒ          ËÓ          ËÔ          ÛÅ          Þ´          à²          àÕ          âÈ          äÑ          ì¬          î¤          ïË          òô
    0x641c,  0x8258,  0x64de,  0x55fd,  0x53df,  0x85ae,  0x55d6,  0x55fe,  0x998a,  0x6eb2,  0x98d5,  0x778d,  0x953c,  0x878b,
// su  ËÕ          ËÖ          Ë×          ËØ          ËÙ          ËÚ          ËÛ          ËÜ          ËÝ          ËÞ          Ëß          Ëà          Ëõ          Ùí          ÚÕ          Ýø          à¼          ãº          ä³          óù          ö¢          öÕ
    0x82cf,  0x9165,  0x4fd7,  0x7d20,  0x901f,  0x7c9f,  0x50f3,  0x5851,  0x6eaf,  0x5bbf,  0x8bc9,  0x8083,  0x7f29,  0x5919,  0x8c21,  0x850c,  0x55c9,  0x612b,  0x6d91,  0x7c0c,  0x89eb,  0x7a23,
// suan  Ëá          Ëâ          Ëã          â¡
    0x9178,  0x849c,  0x7b97,  0x72fb,
// sui  Ëä          Ëå          Ëæ          Ëç          Ëè          Ëé          Ëê          Ëë          Ëì          Ëí          Ëî          ÚÇ          Ý´          å¡          åä          ìÝ          íõ          î¡
    0x867d,  0x968b,  0x968f,  0x7ee5,  0x9ad3,  0x788e,  0x5c81,  0x7a57,  0x9042,  0x96a7,  0x795f,  0x8c07,  0x837d,  0x6fc9,  0x9083,  0x71e7,  0x772d,  0x7762,
// sun  Ëï          Ëð          Ëñ          Ý¥          áø          â¸          é¾          öÀ
    0x5b59,  0x635f,  0x7b0b,  0x836a,  0x72f2,  0x98e7,  0x69ab,  0x96bc,
// suo  É¯          Ëò          Ëó          Ëô          Ëõ          Ëö          Ë÷          Ëø          Ëù          ßï          àÂ          àÊ          æ¶          èø          êý          íü          ôÈ
    0x838e,  0x84d1,  0x68ad,  0x5506,  0x7f29,  0x7410,  0x7d22,  0x9501,  0x6240,  0x5522,  0x55e6,  0x55cd,  0x5a11,  0x686b,  0x6332,  0x7743,  0x7fa7,
// ta  Ëú          Ëû          Ëü          Ëý          Ëþ          Ì¡          Ì¢          Ì£          Ì¤          àª          ãË          äâ          äð          åÝ          é½          í³          îè          õÁ          ÷£
    0x584c,  0x4ed6,  0x5b83,  0x5979,  0x5854,  0x736d,  0x631e,  0x8e4b,  0x8e0f,  0x55d2,  0x95fc,  0x6ebb,  0x6f2f,  0x9062,  0x69bb,  0x6c93,  0x94ca,  0x8dbf,  0x9cce,
// tai  ´ó          Ì¥          Ì¦          Ì§          Ì¨          Ì©          Ìª          Ì«          Ì¬          Ì­          Û¢          Þ·          ææ          ëÄ          ìÆ          îÑ          õÌ          öØ
    0x5927,  0x80ce,  0x82d4,  0x62ac,  0x53f0,  0x6cf0,  0x915e,  0x592a,  0x6001,  0x6c70,  0x90b0,  0x85b9,  0x9a80,  0x80bd,  0x70b1,  0x949b,  0x8dc6,  0x9c90,
// tan  µ¯          Ì®          Ì¯          Ì°          Ì±          Ì²          Ì³          Ì´          Ìµ          Ì¶          Ì·          Ì¸          Ì¹          Ìº          Ì»          Ì¼          Ì½          Ì¾          Ì¿          Û°          å£          ê¼          ìþ          îã          ïÄ          ñû
    0x5f39,  0x574d,  0x644a,  0x8d2a,  0x762b,  0x6ee9,  0x575b,  0x6a80,  0x75f0,  0x6f6d,  0x8c2d,  0x8c08,  0x5766,  0x6bef,  0x8892,  0x78b3,  0x63a2,  0x53f9,  0x70ad,  0x90ef,  0x6fb9,  0x6619,  0x5fd0,  0x94bd,  0x952c,  0x8983,
// tang  ÌÀ          ÌÁ          ÌÂ          ÌÃ          ÌÄ          ÌÅ          ÌÆ          ÌÇ          ÌÈ          ÌÉ          ÌÊ          ÌË          ÌÌ          ÙÎ          àû          ã®          äç          è©          éÌ          ï¦          ïÛ          ñí          ó¥          ó«          ôÊ          õ±
    0x6c64,  0x5858,  0x642a,  0x5802,  0x68e0,  0x819b,  0x5510,  0x7cd6,  0x5018,  0x8eba,  0x6dcc,  0x8d9f,  0x70eb,  0x50a5,  0x5e11,  0x60dd,  0x6e8f,  0x746d,  0x6a18,  0x94f4,  0x9557,  0x8025,  0x8797,  0x87b3,  0x7fb0,  0x91a3,
// tao  ÌÍ          ÌÎ          ÌÏ          ÌÐ          ÌÑ          ÌÒ          ÌÓ          ÌÔ          ÌÕ          ÌÖ          Ì×          Ø»          ß¶          ßû          ä¬          èº          ÷Ò
    0x638f,  0x6d9b,  0x6ed4,  0x7ee6,  0x8404,  0x6843,  0x9003,  0x6dd8,  0x9676,  0x8ba8,  0x5957,  0x9f17,  0x53e8,  0x5555,  0x6d2e,  0x97ec,  0x9955,
// te  ÌØ          ß¯          ìý          í«          ï«
    0x7279,  0x5fd2,  0x5fd1,  0x615d,  0x94fd,
// teng  ÌÙ          ÌÚ          ÌÛ          ÌÜ          ëø
    0x85e4,  0x817e,  0x75bc,  0x8a8a,  0x6ed5,
// ti  ÌÝ          ÌÞ          Ìß          Ìà          Ìá          Ìâ          Ìã          Ìä          Ìå          Ìæ          Ìç          Ìè          Ìé          Ìê          Ìë          ÙÃ          Üè          ã©          åÑ          ç°          ç¾          ðÃ          ñÓ          õ®
    0x68af,  0x5254,  0x8e22,  0x9511,  0x63d0,  0x9898,  0x8e44,  0x557c,  0x4f53,  0x66ff,  0x568f,  0x60d5,  0x6d95,  0x5243,  0x5c49,  0x501c,  0x8351,  0x608c,  0x9016,  0x7ee8,  0x7f07,  0x9e48,  0x88fc,  0x918d,
// tian  Ìì          Ìí          Ìî          Ìï          Ìð          Ìñ          Ìò          Ìó          ÞÝ          ãÃ          ãÙ          éå          î±
    0x5929,  0x6dfb,  0x586b,  0x7530,  0x751c,  0x606c,  0x8214,  0x8146,  0x63ad,  0x5fdd,  0x9617,  0x6b84,  0x754b,
// tiao  µ÷          Ìô          Ìõ          Ìö          Ì÷          Ìø          Ù¬          Üæ          ìö          ñ»          òè          óÔ          ôÐ          ö¶          öæ          ÷Ø
    0x8c03,  0x6311,  0x6761,  0x8fe2,  0x773a,  0x8df3,  0x4f7b,  0x82d5,  0x7967,  0x7a95,  0x8729,  0x7b24,  0x7c9c,  0x9f86,  0x9ca6,  0x9aeb,
// tie  Ìù          Ìú          Ìû          ÝÆ          ÷Ñ
    0x8d34,  0x94c1,  0x5e16,  0x841c,  0x992e,
// ting  Ìü          Ìý          Ìþ          Í¡          Í¢          Í£          Í¤          Í¥          Í¦          Í§          Üð          Ýã          æÃ          èè          îú          òÑ          öª
    0x5385,  0x542c,  0x70c3,  0x6c40,  0x5ef7,  0x505c,  0x4ead,  0x5ead,  0x633a,  0x8247,  0x839b,  0x8476,  0x5a77,  0x6883,  0x94e4,  0x8713,  0x9706,
// tong  Í¨          Í©          Íª          Í«          Í¬          Í­          Í®          Í¯          Í°          Í±          Í²          Í³          Í´          Ù¡          ÙÚ          Üí          àÌ          âú          äü          íÅ
    0x901a,  0x6850,  0x916e,  0x77b3,  0x540c,  0x94dc,  0x5f64,  0x7ae5,  0x6876,  0x6345,  0x7b52,  0x7edf,  0x75db,  0x4f5f,  0x4edd,  0x833c,  0x55f5,  0x6078,  0x6f7c,  0x783c,
// tou  Íµ          Í¶          Í·          Í¸          ÷»
    0x5077,  0x6295,  0x5934,  0x900f,  0x9ab0,
// tu  Í¹          Íº          Í»          Í¼          Í½          Í¾          Í¿          ÍÀ          ÍÁ          ÍÂ          ÍÃ          Ü¢          Ý±          ÝË          îÊ          õ©
    0x51f8,  0x79c3,  0x7a81,  0x56fe,  0x5f92,  0x9014,  0x6d82,  0x5c60,  0x571f,  0x5410,  0x5154,  0x580d,  0x837c,  0x83df,  0x948d,  0x9174,
// tuan  ÍÄ          ÍÅ          ÞÒ          åè          î¶
    0x6e4d,  0x56e2,  0x629f,  0x5f56,  0x7583,
// tui  ÍÆ          ÍÇ          ÍÈ          ÍÉ          ÍÊ          ÍË          ß¯          ìÕ
    0x63a8,  0x9893,  0x817f,  0x8715,  0x892a,  0x9000,  0x5fd2,  0x717a,
// tun  ¶Ú          ÍÊ          ÍÌ          ÍÍ          ÍÎ          ÙÛ          â½          êÕ          ëà
    0x56e4,  0x892a,  0x541e,  0x5c6f,  0x81c0,  0x6c3d,  0x9968,  0x66be,  0x8c5a,
// tuo  ÍÏ          ÍÐ          ÍÑ          ÍÒ          ÍÓ          ÍÔ          ÍÕ          ÍÖ          Í×          ÍØ          ÍÙ          Ø±          Ù¢          Ûç          âÕ          ãû          èØ          èÞ          éÒ          íÈ          óê          õ¢          õÉ          ö¾
    0x62d6,  0x6258,  0x8131,  0x9e35,  0x9640,  0x9a6e,  0x9a7c,  0x692d,  0x59a5,  0x62d3,  0x553e,  0x4e47,  0x4f57,  0x5768,  0x5eb9,  0x6cb1,  0x67dd,  0x67c1,  0x6a50,  0x7823,  0x7ba8,  0x9161,  0x8dce,  0x9f0d,
// wa  ÍÚ          ÍÛ          ÍÜ          ÍÝ          ÍÞ          Íß          Íà          Øô          æ´          ëð
    0x6316,  0x54c7,  0x86d9,  0x6d3c,  0x5a03,  0x74e6,  0x889c,  0x4f64,  0x5a32,  0x817d,
// wai  Íá          Íâ          áË
    0x6b6a,  0x5916,  0x5d34,
// wan  Âû          Íã          Íä          Íå          Íæ          Íç          Íè          Íé          Íê          Íë          Íì          Íí          Íî          Íï          Íð          Íñ          Íò          Íó          Øà          Ü¹          Ý¸          ÝÒ          æý          çº          çþ          ëä          îµ          òê
    0x8513,  0x8c4c,  0x5f2f,  0x6e7e,  0x73a9,  0x987d,  0x4e38,  0x70f7,  0x5b8c,  0x7897,  0x633d,  0x665a,  0x7696,  0x60cb,  0x5b9b,  0x5a49,  0x4e07,  0x8155,  0x525c,  0x8284,  0x839e,  0x83c0,  0x7ea8,  0x7efe,  0x742c,  0x8118,  0x7579,  0x873f,
// wang  Íô          Íõ          Íö          Í÷          Íø          Íù          Íú          Íû          Íü          Íý          Øè          ã¯          éþ          ÷Í
    0x6c6a,  0x738b,  0x4ea1,  0x6789,  0x7f51,  0x5f80,  0x65fa,  0x671b,  0x5fd8,  0x5984,  0x7f54,  0x60d8,  0x8f8b,  0x9b4d,
// wei  Íþ        Î¡       Î¢       Î£       Î¤          Î¥       Î¦          Î§       Î¨          Î©       Îª        Î«       Î¬        Î­        Î®        Î¯        Î°
    0x5a01,  0x5dcd,  0x5fae,  0x5371,  0x97e6,  0x8fdd,  0x6845,  0x56f4,  0x552f,  0x60df,  0x4e3a,  0x6f4d,  0x7ef4,  0x82c7,  0x840e,  0x59d4,  0x4f1f,
//  Î±          Î²          Î³          Î´        Îµ       Î¶        Î·        Î¸        Î¹        Îº        Î»        Î¼        Î½        Î¾        Î¿        ÎÀ        ÙË
    0x4f2a,  0x5c3e,  0x7eac,  0x672a,  0x851a,  0x5473,  0x754f,  0x80c3,  0x5582,  0x9b4f,  0x4f4d,  0x6e2d,  0x8c13,  0x5c09,  0x6170,  0x536b,  0x504e,
//  ÚÃ          Úñ          Úó          Û×          ÝÚ          Þ±          àø          á¡          áË          áÍ          â«          â¬          ãÇ          ãí          ä¢          ä¶          åÔ          æ¸          çâ          è¸          ê¦          ì¿          ìÐ          ðô          ôº          öÛ
    0x8bff,  0x9688,  0x9697,  0x5729,  0x8473,  0x8587,  0x5e0f,  0x5e37,  0x5d34,  0x5d6c,  0x7325,  0x732c,  0x95f1,  0x6ca9,  0x6d27,  0x6da0,  0x9036,  0x5a13,  0x73ae,  0x97ea,  0x8ece,  0x709c,  0x7168,  0x75ff,  0x8249,  0x9c94,
// wen  ÎÁ          ÎÂ          ÎÃ          ÎÄ          ÎÅ          ÎÆ          ÎÇ          ÎÈ          ÎÉ          ÎÊ          ØØ          âº          ãÓ          ãë          è·          ë¶          ö©
    0x761f,  0x6e29,  0x868a,  0x6587,  0x95fb,  0x7eb9,  0x543b,  0x7a33,  0x7d0a,  0x95ee,  0x520e,  0x5902,  0x960c,  0x6c76,  0x74ba,  0x6535,  0x96ef,
// weng  ÎË          ÎÌ          ÎÍ          Ýî          Þ³
    0x55e1,  0x7fc1,  0x74ee,  0x84ca,  0x8579,
// wo  ÎÎ          ÎÏ          ÎÐ          ÎÑ          ÎÒ          ÎÓ          ÎÔ          ÎÕ          ÎÖ          ÙÁ          Ý«          à¸          á¢          ä×          ë¿          íÒ          ö»
    0x631d,  0x8717,  0x6da1,  0x7a9d,  0x6211,  0x65a1,  0x5367,  0x63e1,  0x6c83,  0x502d,  0x83b4,  0x5594,  0x5e44,  0x6e25,  0x809f,  0x786a,  0x9f8c,
// wu  ¶ñ       Î×        ÎØ        ÎÙ        ÎÚ        ÎÛ        ÎÜ       ÎÝ        ÎÞ          Îß       Îà          Îá       Îâ        Îã        Îä        Îå        Îæ
    0x6076,  0x5deb,  0x545c,  0x94a8,  0x4e4c,  0x6c61,  0x8bec,  0x5c4b,  0x65e0,  0x829c,  0x68a7,  0x543e,  0x5434,  0x6bcb,  0x6b66,  0x4e94,  0x6342,
//  Îç          Îè          Îé          Îê       Îë        Îì       Îí        Îî        Îï        Îð        Îñ       Îò        Îó        Ø£        Øõ        Úã        Úù
    0x5348,  0x821e,  0x4f0d,  0x4fae,  0x575e,  0x620a,  0x96fe,  0x6664,  0x7269,  0x52ff,  0x52a1,  0x609f,  0x8bef,  0x5140,  0x4ef5,  0x9622,  0x90ac,
//  ÛØ          ÜÌ          ßí          âÐ          âä          âè          å»          åÃ          åü          æÄ          æð          è»          êõ          ìÉ          ðÄ          ðÍ          ðí          òÚ          öÈ          ÷ù
    0x572c,  0x82b4,  0x5514,  0x5e91,  0x6003,  0x5fe4,  0x5be4,  0x8fd5,  0x59a9,  0x5a7a,  0x9a9b,  0x674c,  0x727e,  0x7110,  0x9e49,  0x9e5c,  0x75e6,  0x8708,  0x92c8,  0x9f2f,
// xi  ÆÜ        Îô        Îõ        Îö        Î÷        Îø        Îù        Îú        Îû        Îü        Îý        Îþ        Ï¡        Ï¢        Ï£        Ï¤
    0x6816,  0x6614,  0x7199,  0x6790,  0x897f,  0x7852,  0x77fd,  0x6670,  0x563b,  0x5438,  0x9521,  0x727a,  0x7a00,  0x606f,  0x5e0c,  0x6089,
//  Ï¥          Ï¦          Ï§          Ï¨      Ï©    Ïª          Ï«          Ï¬          Ï­      Ï®      Ï¯          Ï°      Ï±       Ï²        Ï³          Ï´
    0x819d,  0x5915,  0x60dc,  0x7184,  0x70ef,  0x6eaa,  0x6c50,  0x7280,  0x6a84,  0x88ad,  0x5e2d,  0x4e60,  0x5ab3,  0x559c,  0x94e3,  0x6d17,
//  Ïµ          Ï¶          Ï·          Ï¸    ÙÒ          Ùâ          Úô    Û­          Üç   Ý¾          Ýß          Ýû          ÞÉ     ßñ          áã          â¾
    0x7cfb,  0x9699,  0x620f,  0x7ec6,  0x50d6,  0x516e,  0x96b0,  0x90d7,  0x831c,  0x83e5,  0x8478,  0x84f0,  0x595a,  0x550f,  0x5f99,  0x9969,
//  ãÒ          ä»          äÀ          åï          æÒ          çô          éØ          êØ          êê          ì¤          ì¨          ìä          ìù          ìû          ðª          ñ¶          ñÓ          òá          ó£          ó¬          ôª          ô¸          ôË          ôÑ          ôâ          õµ          õè          ÷û
    0x960b,  0x6d60,  0x6dc5,  0x5c63,  0x5b09,  0x73ba,  0x6a28,  0x66e6,  0x89cb,  0x6b37,  0x6b59,  0x71b9,  0x798a,  0x79a7,  0x7699,  0x7a78,  0x88fc,  0x8725,  0x8785,  0x87cb,  0x8204,  0x823e,  0x7fb2,  0x7c9e,  0x7fd5,  0x91af,  0x8e4a,  0x9f37,
// xia  Ï¹          Ïº          Ï»          Ï¼          Ï½          Ï¾          Ï¿          ÏÀ          ÏÁ          ÏÂ          ÏÃ          ÏÄ          ÏÅ          ßÈ          áò          åÚ          è¦          èÔ          íÌ          óÁ          ÷ï
    0x778e,  0x867e,  0x5323,  0x971e,  0x8f96,  0x6687,  0x5ce1,  0x4fa0,  0x72ed,  0x4e0b,  0x53a6,  0x590f,  0x5413,  0x5477,  0x72ce,  0x9050,  0x7455,  0x67d9,  0x7856,  0x7f45,  0x9ee0,
// xian  ¼û  Ï³          ÏÆ          ÏÇ         ÏÈ      ÏÉ        ÏÊ       ÏË       ÏÌ          ÏÍ        ÏÎ     ÏÏ          ÏÐ          ÏÑ      ÏÒ         ÏÓ      ÏÔ          ÏÕ
    0x89c1,  0x94e3,  0x6380,  0x9528,  0x5148,  0x4ed9,  0x9c9c,  0x7ea4,  0x54b8,  0x8d24,  0x8854,  0x8237,  0x95f2,  0x6d8e,  0x5f26,  0x5acc,  0x663e,  0x9669,
//  ÏÖ          Ï×          ÏØ          ÏÙ          ÏÚ          ÏÛ          ÏÜ          ÏÝ          ÏÞ          Ïß          Ùþ          ÜÈ          Ý²          Þº          á­          áý          åß          æµ          ë¯          ìÞ          ìì          ðÂ          ðï          ò¹          óÚ          ôÌ          õ£          õÐ          õÑ          ö±
    0x73b0,  0x732e,  0x53bf,  0x817a,  0x9985,  0x7fa1,  0x5baa,  0x9677,  0x9650,  0x7ebf,  0x51bc,  0x82cb,  0x83b6,  0x85d3,  0x5c98,  0x7303,  0x66b9,  0x5a34,  0x6c19,  0x71f9,  0x7946,  0x9e47,  0x75eb,  0x86ac,  0x7b45,  0x7c7c,  0x9170,  0x8de3,  0x8df9,  0x9730,
// xiang  ½µ          Ïà          Ïá          Ïâ          Ïã          Ïä          Ïå          Ïæ          Ïç          Ïè          Ïé          Ïê          Ïë          Ïì          Ïí          Ïî          Ïï          Ïð          Ïñ          Ïò          Ïó          Ü¼          ÝÙ          âÃ          âÔ          æø          ç½          ó­          öß          ÷Ï
    0x964d,  0x76f8,  0x53a2,  0x9576,  0x9999,  0x7bb1,  0x8944,  0x6e58,  0x4e61,  0x7fd4,  0x7965,  0x8be6,  0x60f3,  0x54cd,  0x4eab,  0x9879,  0x5df7,  0x6a61,  0x50cf,  0x5411,  0x8c61,  0x8297,  0x8459,  0x9977,  0x5ea0,  0x9aa7,  0x7f03,  0x87d3,  0x9c9e,  0x98e8,
// xiao  Ïô          Ïõ          Ïö          Ï÷          Ïø          Ïù          Ïú          Ïû          Ïü          Ïý          Ïþ          Ð¡          Ð¢          Ð£          Ð¤          Ð¥          Ð¦          Ð§          ßØ          áÅ          äì          åÐ          æç          ç¯          èÉ          èÕ          òÙ          óã          óï          ÷Ì
    0x8427,  0x785d,  0x9704,  0x524a,  0x54ee,  0x56a3,  0x9500,  0x6d88,  0x5bb5,  0x6dc6,  0x6653,  0x5c0f,  0x5b5d,  0x6821,  0x8096,  0x5578,  0x7b11,  0x6548,  0x54d3,  0x5d24,  0x6f47,  0x900d,  0x9a81,  0x7ee1,  0x67ad,  0x67b5,  0x86f8,  0x7b71,  0x7bab,  0x9b48,
// xie  Ð¨      Ð©         Ðª      Ð«          Ð¬     Ð­          Ð®        Ð¯         Ð°       Ð±     Ð²          Ð³          Ð´     Ðµ          Ð¶    Ð·          Ð¸          Ð¹
    0x6954,  0x4e9b,  0x6b47,  0x874e,  0x978b,  0x534f,  0x631f,  0x643a,  0x90aa,  0x659c,  0x80c1,  0x8c10,  0x5199,  0x68b0,  0x5378,  0x87f9,  0x61c8,  0x6cc4,
//  Ðº          Ð»          Ð¼          ÙÉ          Ùô          ÛÄ          ÛÆ          Þ¯          ß¢          â³          âÝ          äÍ          å¬          åâ          ç¥          çÓ          é¿          éÇ          ò¡          õÞ          õó
    0x6cfb,  0x8c22,  0x5c51,  0x5055,  0x4eb5,  0x52f0,  0x71ee,  0x85a4,  0x64b7,  0x736c,  0x5ee8,  0x6e2b,  0x7023,  0x9082,  0x7ec1,  0x7f2c,  0x69ad,  0x698d,  0x9889,  0x8e40,  0x8e9e,
// xin  Ð½          Ð¾          Ð¿          ÐÀ          ÐÁ          ÐÂ          ÐÃ          ÐÄ          ÐÅ          ÐÆ          Ø¶          Ü°          Ý·          ê¿          ì§          ïâ          öÎ
    0x85aa,  0x82af,  0x950c,  0x6b23,  0x8f9b,  0x65b0,  0x5ffb,  0x5fc3,  0x4fe1,  0x8845,  0x56df,  0x99a8,  0x8398,  0x6615,  0x6b46,  0x9561,  0x946b,
// xing  Ê¡          ÐÇ          ÐÈ          ÐÉ          ÐÊ          ÐË          ÐÌ          ÐÍ          ÐÎ          ÐÏ          ÐÐ          ÐÑ          ÐÒ          ÐÓ          ÐÔ          ÐÕ          Úê          Üô          Üþ          ß©          â¼          ã¬          íÊ
    0x7701,  0x661f,  0x8165,  0x7329,  0x60fa,  0x5174,  0x5211,  0x578b,  0x5f62,  0x90a2,  0x884c,  0x9192,  0x5e78,  0x674f,  0x6027,  0x59d3,  0x9649,  0x8347,  0x8365,  0x64e4,  0x9967,  0x60bb,  0x784e,
// xiong  ÐÖ          Ð×          ÐØ          ÐÙ          ÐÚ          ÐÛ          ÐÜ          Üº
    0x5144,  0x51f6,  0x80f8,  0x5308,  0x6c79,  0x96c4,  0x718a,  0x828e,
// xiu  ³ô          ÐÝ          ÐÞ          Ðß          Ðà          Ðá          Ðâ          Ðã          Ðä          Ðå          ßÝ          á¶          âÊ          âÓ          äå          ð¼          õ÷          ÷Û
    0x81ed,  0x4f11,  0x4fee,  0x7f9e,  0x673d,  0x55c5,  0x9508,  0x79c0,  0x8896,  0x7ee3,  0x54bb,  0x5cab,  0x9990,  0x5ea5,  0x6eb4,  0x9e3a,  0x8c85,  0x9af9,
// xu  Ðæ          Ðç          Ðè          Ðé          Ðê          Ðë          Ðì          Ðí          Ðî          Ðï          Ðð          Ðñ          Ðò          Ðó          Ðô          Ðõ          Ðö          Ð÷          Ðø          Óõ          Ú¼          ÛÃ          Û×          Þ£          äª          äÓ          çï          èò          ëÉ          ìã          íì          ñã          ôÚ          õ¯
    0x589f,  0x620c,  0x9700,  0x865a,  0x5618,  0x987b,  0x5f90,  0x8bb8,  0x84c4,  0x9157,  0x53d9,  0x65ed,  0x5e8f,  0x755c,  0x6064,  0x7d6e,  0x5a7f,  0x7eea,  0x7eed,  0x5401,  0x8be9,  0x52d6,  0x5729,  0x84ff,  0x6d2b,  0x6e86,  0x987c,  0x6829,  0x80b7,  0x7166,  0x76f1,  0x80e5,  0x7cc8,  0x9191,
// xuan  Ðù          Ðú          Ðû          Ðü          Ðý          Ðþ          Ñ¡          Ñ¢          Ñ£          Ñ¤          ÙØ          ÚÎ          Ýæ          Þï          ãù          äÖ          äö          è¯          é¸          êÑ          ìÅ          ìÓ          íÛ          îç          ïà          ðç
    0x8f69,  0x55a7,  0x5ba3,  0x60ac,  0x65cb,  0x7384,  0x9009,  0x7663,  0x7729,  0x7eda,  0x5107,  0x8c16,  0x8431,  0x63ce,  0x6ceb,  0x6e32,  0x6f29,  0x7487,  0x6966,  0x6684,  0x70ab,  0x714a,  0x78b9,  0x94c9,  0x955f,  0x75c3,
// xue  Ï÷          Ñ¥          Ñ¦          Ñ§          Ñ¨          Ñ©          Ñª          ÚÊ          àå          í´          õ½          ÷¨
    0x524a,  0x9774,  0x859b,  0x5b66,  0x7a74,  0x96ea,  0x8840,  0x8c11,  0x5671,  0x6cf6,  0x8e05,  0x9cd5,
// xun  ¿£          Ñ«          Ñ¬          Ñ­          Ñ®          Ñ¯          Ñ°          Ñ±          Ñ²          Ñ³          Ñ´          Ñµ          Ñ¶          Ñ·          Ñ¸          Ùã          Û¨          Û÷          Ü÷          Ý¡          Þ¦          Þ¹          á¾          áß          â´          âþ          ä­          ä±          êÖ          ñ¿          õ¸          öà
    0x6d5a,  0x52cb,  0x718f,  0x5faa,  0x65ec,  0x8be2,  0x5bfb,  0x9a6f,  0x5de1,  0x6b89,  0x6c5b,  0x8bad,  0x8baf,  0x900a,  0x8fc5,  0x5dfd,  0x90c7,  0x57d9,  0x8340,  0x8368,  0x8548,  0x85b0,  0x5ccb,  0x5f87,  0x736f,  0x6042,  0x6d35,  0x6d54,  0x66db,  0x7aa8,  0x91ba,  0x9c9f,
// ya  Ñ¹          Ñº          Ñ»          Ñ¼          Ñ½          Ñ¾          Ñ¿          ÑÀ          ÑÁ          ÑÂ          ÑÃ          ÑÄ          ÑÅ          ÑÆ          ÑÇ          ÑÈ          Ôþ          Øó          Ûë          Þë          á¬          åÂ          æ«          çð          èâ          ë²          í¼          íý          ðé
    0x538b,  0x62bc,  0x9e26,  0x9e2d,  0x5440,  0x4e2b,  0x82bd,  0x7259,  0x869c,  0x5d16,  0x8859,  0x6daf,  0x96c5,  0x54d1,  0x4e9a,  0x8bb6,  0x8f67,  0x4f22,  0x57ad,  0x63e0,  0x5c88,  0x8fd3,  0x5a05,  0x740a,  0x6860,  0x6c29,  0x7811,  0x775a,  0x75d6,
// yan  ÑÉ     ÑÊ        ÑË          ÑÌ       ÑÍ       ÑÎ         ÑÏ        ÑÐ        ÑÑ       ÑÒ        ÑÓ        ÑÔ        ÑÕ        ÑÖ       Ñ×         ÑØ        ÑÙ        ÑÚ
    0x7109,  0x54bd,  0x9609,  0x70df,  0x6df9,  0x76d0,  0x4e25,  0x7814,  0x8712,  0x5ca9,  0x5ef6,  0x8a00,  0x989c,  0x960e,  0x708e,  0x6cbf,  0x5944,  0x63a9,
//  ÑÛ          ÑÜ         ÑÝ        ÑÞ       Ñß          Ñà          Ñá      Ñâ        Ñã       Ñä          Ñå        Ñæ        Ñç        Ñè        Ñé       Òó        ØÉ        ØÍ
    0x773c,  0x884d,  0x6f14,  0x8273,  0x5830,  0x71d5,  0x538c,  0x781a,  0x96c1,  0x5501,  0x5f66,  0x7130,  0x5bb4,  0x8c1a,  0x9a8c,  0x6bb7,  0x53a3,  0x8d5d,
//  Øß          Ù²          ÙÈ          Ùð          ÚÝ          Û±          Û³          Ûï          Ü¾          ÝÎ          áÃ          âû          ãÆ          ãÕ          äÎ          äÙ          åû          æÌ          çü          éÜ          êÌ          ëÙ          ëç          ìÍ          î»          óÛ          õ¦          õÂ          ÷Ê          ÷Ð          ÷ú
    0x5261,  0x4fe8,  0x5043,  0x5156,  0x8c33,  0x90fe,  0x9122,  0x57cf,  0x82ab,  0x83f8,  0x5d26,  0x6079,  0x95eb,  0x960f,  0x6e6e,  0x6edf,  0x598d,  0x5ae3,  0x7430,  0x6a90,  0x664f,  0x80ed,  0x814c,  0x7131,  0x7f68,  0x7b75,  0x917d,  0x8dbc,  0x9b47,  0x990d,  0x9f39,
// yang  Ñê          Ñë          Ñì          Ñí          Ñî          Ñï          Ñð          Ññ          Ñò          Ñó          Ñô          Ñõ          Ñö          Ñ÷          Ñø          Ñù          Ñú          áà          âó          ãó          ì¾          ìÈ          í¦          òÕ          ÷±
    0x6b83,  0x592e,  0x9e2f,  0x79e7,  0x6768,  0x626c,  0x4f6f,  0x75a1,  0x7f8a,  0x6d0b,  0x9633,  0x6c27,  0x4ef0,  0x75d2,  0x517b,  0x6837,  0x6f3e,  0x5f89,  0x600f,  0x6cf1,  0x7080,  0x70ca,  0x6059,  0x86d8,  0x9785,
// yao  Ñû          Ñü          Ñý          Ñþ          Ò¡          Ò¢          Ò£          Ò¤          Ò¥          Ò¦          Ò§          Ò¨          Ò©          Òª          Ò«          Ô¿          Ø²          Ø³          ßº          áÊ          áæ          çÛ          çò          èÃ          é÷          ê×          ëÈ          ï¢          ðÎ          ñº          ôí          ÷¥          ÷á
    0x9080,  0x8170,  0x5996,  0x7476,  0x6447,  0x5c27,  0x9065,  0x7a91,  0x8c23,  0x59da,  0x54ac,  0x8200,  0x836f,  0x8981,  0x8000,  0x94a5,  0x592d,  0x723b,  0x5406,  0x5d3e,  0x5fad,  0x5e7a,  0x73e7,  0x6773,  0x8f7a,  0x66dc,  0x80b4,  0x94eb,  0x9e5e,  0x7a88,  0x7e47,  0x9cd0,  0x9ebd,
// ye  Ò¬          Ò­          Ò®          Ò¯          Ò°          Ò±          Ò²          Ò³          Ò´          Òµ          Ò¶          Ò·          Ò¸          Ò¹          Òº          ×§          ØÌ          ÚË          Úþ          ÞÞ          Þé          êÊ          ìÇ          îô
    0x6930,  0x564e,  0x8036,  0x7237,  0x91ce,  0x51b6,  0x4e5f,  0x9875,  0x6396,  0x4e1a,  0x53f6,  0x66f3,  0x814b,  0x591c,  0x6db2,  0x62fd,  0x9765,  0x8c12,  0x90ba,  0x63f6,  0x63f2,  0x6654,  0x70e8,  0x94d8,
// yi  °¬          Éß     Ò»          Ò¼       Ò½          Ò¾      Ò¿        ÒÀ        ÒÁ       ÒÂ        ÒÃ        ÒÄ        ÒÅ        ÒÆ         ÒÇ        ÒÈ        ÒÉ        ÒÊ
    0x827e,  0x86c7,  0x4e00,  0x58f9,  0x533b,  0x63d6,  0x94f1,  0x4f9d,  0x4f0a,  0x8863,  0x9890,  0x5937,  0x9057,  0x79fb,  0x4eea,  0x80f0,  0x7591,  0x6c82,
//  ÒË          ÒÌ          ÒÍ          ÒÎ      ÒÏ       ÒÐ       ÒÑ        ÒÒ        ÒÓ        ÒÔ        ÒÕ        ÒÖ        Ò×         ÒØ        ÒÙ        ÒÚ        ÒÛ        ÒÜ
    0x5b9c,  0x59e8,  0x5f5d,  0x6905,  0x8681,  0x501a,  0x5df2,  0x4e59,  0x77e3,  0x4ee5,  0x827a,  0x6291,  0x6613,  0x9091,  0x5c79,  0x4ebf,  0x5f79,  0x81c6,
//  ÒÝ          ÒÞ          Òß          Òà       Òá       Òâ       Òã        Òä        Òå        Òæ        Òç        Òè        Òé        Òê        Òë        Òì        Òí        Òî
    0x9038,  0x8084,  0x75ab,  0x4ea6,  0x88d4,  0x610f,  0x6bc5,  0x5fc6,  0x4e49,  0x76ca,  0x6ea2,  0x8be3,  0x8bae,  0x8c0a,  0x8bd1,  0x5f02,  0x7ffc,  0x7fcc,
//  Òï          Ø×          Øæ          Øý      Ù«        Ú±        ÛÝ        Ûü        Ü²        ÜÓ        Üè       Þ²        ÞÄ        ÞÈ        ÞÚ        ß®        ß½        ß×
    0x7ece,  0x5208,  0x5293,  0x4f5a,  0x4f7e,  0x8bd2,  0x572f,  0x57f8,  0x61ff,  0x82e1,  0x8351,  0x858f,  0x5f08,  0x5955,  0x6339,  0x5f0b,  0x5453,  0x54a6,
//  ßÞ          àÉ          àæ          á»          áÚ          â¢          âÂ          âø          âù          ã¨          äô          åÆ          æä          çË          éì          éó          êÝ          ì¥          ì½          ìÚ          íô          îÆ          ï×          ïî          ðê          ðù          ñ¯          ñ´          òæ          ô¯          ôà          ôè          ôý          ÷ð
    0x54bf,  0x55cc,  0x566b,  0x5cc4,  0x5db7,  0x7317,  0x9974,  0x603f,  0x6021,  0x6092,  0x6f2a,  0x8fe4,  0x9a7f,  0x7f22,  0x6baa,  0x8f76,  0x8d3b,  0x6b39,  0x65d6,  0x71a0,  0x7719,  0x9487,  0x9552,  0x9571,  0x75cd,  0x7617,  0x7654,  0x7fca,  0x8734,  0x8223,  0x7fbf,  0x7ff3,  0x914f,  0x9edf,
// yin  Òð          Òñ          Òò          Òó          Òô          Òõ          Òö          Ò÷          Òø          Òù          Òú          Òû          Òü          Òý          Òþ          Ó¡          Ø·          Û´          Ûó          Ü§          Üá          ßÅ          à³          áþ          â¹          ä¦          ë³          î÷          ñ«          ñ¿          ò¾          ö¯          ö¸
    0x8335,  0x836b,  0x56e0,  0x6bb7,  0x97f3,  0x9634,  0x59fb,  0x541f,  0x94f6,  0x6deb,  0x5bc5,  0x996e,  0x5c39,  0x5f15,  0x9690,  0x5370,  0x80e4,  0x911e,  0x57a0,  0x5819,  0x831a,  0x5432,  0x5591,  0x72fa,  0x5924,  0x6d07,  0x6c24,  0x94df,  0x763e,  0x7aa8,  0x8693,  0x972a,  0x9f88,
// ying  Ó¢      Ó£       Ó¤        Ó¥        Ó¦        Ó§       Ó¨        Ó©        Óª        Ó«        Ó¬        Ó­        Ó®       Ó¯        Ó°        Ó±        Ó²        Ó³
    0x82f1,  0x6a31,  0x5a74,  0x9e70,  0x5e94,  0x7f28,  0x83b9,  0x8424,  0x8425,  0x8367,  0x8747,  0x8fce,  0x8d62,  0x76c8,  0x5f71,  0x9896,  0x786c,  0x6620,
//  Ùø          Û«          Üã          Üþ          Ýº          ÝÓ          Ýö          Þü          àÓ          âß          äÞ          äë          å­          çø          è¬          éº          ëô          ðÐ          ñ¨          ò£          ó¿
    0x5b34,  0x90e2,  0x8314,  0x8365,  0x83ba,  0x8426,  0x84e5,  0x6484,  0x5624,  0x81ba,  0x6ee2,  0x6f46,  0x701b,  0x745b,  0x748e,  0x6979,  0x5ab5,  0x9e66,  0x763f,  0x988d,  0x7f42,
// yo  Ó´          à¡
    0x54df,  0x5537,
// yong  Óµ          Ó¶          Ó·          Ó¸          Ó¹          Óº          Ó»          Ó¼          Ó½          Ó¾          Ó¿          ÓÀ          ÓÁ          ÓÂ          ÓÃ          Ù¸          ÛÕ          Ü­          à¯          ã¼          çß          ïÞ          ð®          ÷«          ÷Ó
    0x62e5,  0x4f63,  0x81c3,  0x75c8,  0x5eb8,  0x96cd,  0x8e0a,  0x86f9,  0x548f,  0x6cf3,  0x6d8c,  0x6c38,  0x607f,  0x52c7,  0x7528,  0x4fd1,  0x58c5,  0x5889,  0x5581,  0x6175,  0x9095,  0x955b,  0x752c,  0x9cd9,  0x9954,
// you  ÓÄ       ÓÅ       ÓÆ       ÓÇ        ÓÈ        ÓÉ        ÓÊ        ÓË        ÓÌ        ÓÍ        ÓÎ        ÓÏ        ÓÐ       ÓÑ        ÓÒ        ÓÓ        ÓÔ        ÓÕ        ÓÖ
    0x5e7d,  0x4f18,  0x60a0,  0x5fe7,  0x5c24,  0x7531,  0x90ae,  0x94c0,  0x72b9,  0x6cb9,  0x6e38,  0x9149,  0x6709,  0x53cb,  0x53f3,  0x4f51,  0x91c9,  0x8bf1,  0x53c8,
//  Ó×          ØÕ          Øü          Ù§          Ý¬          Ý¯          Ýµ          ÞÌ          ßÏ          àó          å¶          èÖ          éà          ë»          îð          ðà          òÄ          òÊ          òö          òø          ôí          öÏ          ÷î          ÷ø
    0x5e7c,  0x5363,  0x6538,  0x4f91,  0x83a0,  0x839c,  0x83b8,  0x5c22,  0x5466,  0x56ff,  0x5ba5,  0x67da,  0x7337,  0x7256,  0x94d5,  0x75a3,  0x86b0,  0x86b4,  0x8763,  0x8764,  0x7e47,  0x9c7f,  0x9edd,  0x9f2c,
// yu  Î¾      ÓØ        ÓÙ        ÓÚ        ÓÛ        ÓÜ        ÓÝ        ÓÞ        Óß        Óà        Óá        Óâ        Óã        Óä        Óå        Óæ        Óç        Óè        Óé        Óê        Óë        Óì        Óí        Óî
    0x5c09,  0x8fc2,  0x6de4,  0x4e8e,  0x76c2,  0x6986,  0x865e,  0x611a,  0x8206,  0x4f59,  0x4fde,  0x903e,  0x9c7c,  0x6109,  0x6e1d,  0x6e14,  0x9685,  0x4e88,  0x5a31,  0x96e8,  0x4e0e,  0x5c7f,  0x79b9,  0x5b87,
//  Óï          Óð          Óñ          Óò     Óó          Óô    Óõ          Óö       Ó÷         Óø       Óù        Óú        Óû          Óü      Óý          Óþ      Ô¡          Ô¢        Ô£
    0x8bed,  0x7fbd,  0x7389,  0x57df,  0x828b,  0x90c1,  0x5401,  0x9047,  0x55bb,  0x5cea,  0x5fa1,  0x6108,  0x6b32,  0x72f1,  0x80b2,  0x8a89,  0x6d74,  0x5bd3,  0x88d5,
//  Ô¤          Ô¥          Ô¦          Öà      Ø®        Ø¹        Øñ       Ù¶          ÚÄ       ÚÍ       ÝÇ         Ý÷        Þí       àô        àö       áÎ        áü          âÀ          âÅ
    0x9884,  0x8c6b,  0x9a6d,  0x7ca5,  0x79ba,  0x6bd3,  0x4f1b,  0x4fe3,  0x8c00,  0x8c15,  0x8438,  0x84e3,  0x63c4,  0x5704,  0x5709,  0x5d5b,  0x72f3,  0x996b,  0x9980,
//  â×          ãÐ          å÷          åý          æ¥          æú          è¤          êÅ          êì          ëé          ì£          ì¶          ìÏ          ìÙ          ìÛ          í²          î´          îÚ          ðÁ          ðÖ          ðõ          ðö          ñ¾          ñÁ          òâ          òõ          óÄ          ô§          ô¨          ö§          ö¹
    0x5ebe,  0x9608,  0x9b3b,  0x59aa,  0x59a4,  0x7ea1,  0x745c,  0x6631,  0x89ce,  0x8174,  0x6b24,  0x65bc,  0x715c,  0x71a8,  0x71e0,  0x807f,  0x7572,  0x94b0,  0x9e46,  0x9e6c,  0x7610,  0x7600,  0x7aac,  0x7ab3,  0x872e,  0x8753,  0x7afd,  0x81fe,  0x8201,  0x96e9,  0x9f89,
// yuan  Ô§          Ô¨          Ô©          Ôª          Ô«          Ô¬          Ô­          Ô®          Ô¯          Ô°          Ô±          Ô²          Ô³          Ô´          Ôµ          Ô¶          Ô·          Ô¸          Ô¹          Ôº          Ûù          Ü«          Ü¾          Þò          à÷          ãä          æÂ          è¥          éÚ          ë¼          íó          ð°          ó¢          óî          ö½
    0x9e33,  0x6e0a,  0x51a4,  0x5143,  0x57a3,  0x8881,  0x539f,  0x63f4,  0x8f95,  0x56ed,  0x5458,  0x5706,  0x733f,  0x6e90,  0x7f18,  0x8fdc,  0x82d1,  0x613f,  0x6028,  0x9662,  0x57b8,  0x586c,  0x82ab,  0x63be,  0x571c,  0x6c85,  0x5a9b,  0x7457,  0x6a7c,  0x7230,  0x7722,  0x9e22,  0x8788,  0x7ba2,  0x9f0b,
// yue  ÀÖ          Ëµ          Ô»          Ô¼          Ô½          Ô¾          Ô¿          ÔÀ          ÔÁ          ÔÂ          ÔÃ          ÔÄ          Ùß          ßÜ          å®          èÝ          éÐ          ë¾          îá
    0x4e50,  0x8bf4,  0x66f0,  0x7ea6,  0x8d8a,  0x8dc3,  0x94a5,  0x5cb3,  0x7ca4,  0x6708,  0x60a6,  0x9605,  0x9fa0,  0x54d5,  0x7039,  0x680e,  0x6a3e,  0x5216,  0x94ba,
// yun  ÔÅ          ÔÆ          ÔÇ          ÔÈ          ÔÉ          ÔÊ          ÔË          ÔÌ          ÔÍ          ÔÎ          ÔÏ          ÔÐ          Û©          Ü¿          áñ          ã¢          ã³          ç¡          è¹          éæ          êÀ          ëµ          ìÙ          óÞ
    0x8018,  0x4e91,  0x90e7,  0x5300,  0x9668,  0x5141,  0x8fd0,  0x8574,  0x915d,  0x6655,  0x97f5,  0x5b55,  0x90d3,  0x82b8,  0x72c1,  0x607d,  0x6120,  0x7ead,  0x97eb,  0x6b92,  0x6600,  0x6c32,  0x71a8,  0x7b60,
// za  ÔÑ          ÔÒ          ÔÓ          Õ¦          ÞÙ          ßÆ
    0x531d,  0x7838,  0x6742,  0x548b,  0x62f6,  0x5482,
// zai  ÔÔ          ÔÕ          ÔÖ          Ô×          ÔØ          ÔÙ          ÔÚ          ×Ó          áÌ          çÞ
    0x683d,  0x54c9,  0x707e,  0x5bb0,  0x8f7d,  0x518d,  0x5728,  0x5b50,  0x5d3d,  0x753e,
// zan  ÔÛ          ÔÜ          ÔÝ          ÔÞ          è¶          êÃ          ô¢          ôØ          ôõ          öÉ
    0x54b1,  0x6512,  0x6682,  0x8d5e,  0x74d2,  0x661d,  0x7c2a,  0x7ccc,  0x8db1,  0x933e,
// zang  Ôß          Ôà          Ôá          ÞÊ          æà          ê°
    0x8d43,  0x810f,  0x846c,  0x5958,  0x9a75,  0x81e7,
// zao  Ôâ          Ôã          Ôä          Ôå          Ôæ          Ôç          Ôè          Ôé          Ôê          Ôë          Ôì          Ôí          Ôî          Ôï          ßð
    0x906d,  0x7cdf,  0x51ff,  0x85fb,  0x67a3,  0x65e9,  0x6fa1,  0x86a4,  0x8e81,  0x566a,  0x9020,  0x7682,  0x7076,  0x71e5,  0x5523,
// ze  Ôð          Ôñ          Ôò          Ôó          Õ¦          ØÆ          ØÓ          ßõ          àý          åÅ          ê¾          óÐ          óå          ô·
    0x8d23,  0x62e9,  0x5219,  0x6cfd,  0x548b,  0x4ec4,  0x8d5c,  0x5567,  0x5e3b,  0x8fee,  0x6603,  0x7b2e,  0x7ba6,  0x8234,
// zei  Ôô
    0x8d3c,
// zen  Ôõ          ÚÚ
    0x600e,  0x8c2e,
// zeng  Ôö          Ô÷          Ôø          Ôù          ×Û          çÕ          êµ          îÀ          ï­
    0x589e,  0x618e,  0x66fe,  0x8d60,  0x7efc,  0x7f2f,  0x7511,  0x7f7e,  0x9503,
// zha  Ôú          Ôû          Ôü          Ôý          Ôþ          Õ¡          Õ¢          Õ£          Õ¤          Õ¥          Õ¦          Õ§          Õ¨          Õ©          ×õ          Þê          ß¸          ßå          ßî          é«          íÄ          ðä          òÆ          ÷þ
    0x624e,  0x55b3,  0x6e23,  0x672d,  0x8f67,  0x94e1,  0x95f8,  0x7728,  0x6805,  0x69a8,  0x548b,  0x4e4d,  0x70b8,  0x8bc8,  0x67de,  0x63f8,  0x5412,  0x54a4,  0x54f3,  0x6942,  0x781f,  0x75c4,  0x86b1,  0x9f44,
// zhai  µÔ          Õª          Õ«          Õ¬          Õ­          Õ®          Õ¯          íÎ          ñ©
    0x7fdf,  0x6458,  0x658b,  0x5b85,  0x7a84,  0x503a,  0x5be8,  0x7826,  0x7635,
// zhan  Õ°          Õ±          Õ²          Õ³          Õ´          Õµ          Õ¶          Õ·          Õ¸          Õ¹          Õº          Õ»          Õ¼          Õ½          Õ¾          Õ¿          ÕÀ          ÚÞ          Þø          ì¹
    0x77bb,  0x6be1,  0x8a79,  0x7c98,  0x6cbe,  0x76cf,  0x65a9,  0x8f97,  0x5d2d,  0x5c55,  0x8638,  0x6808,  0x5360,  0x6218,  0x7ad9,  0x6e5b,  0x7efd,  0x8c35,  0x640c,  0x65c3,
// zhang  ³¤          ÕÁ          ÕÂ          ÕÃ          ÕÄ          ÕÅ          ÕÆ          ÕÇ          ÕÈ          ÕÉ          ÕÊ          ÕË          ÕÌ          ÕÍ          ÕÎ          ÕÏ          Øë          Ûµ          á¤          áÖ          â¯          æÑ          è°          ó¯
    0x957f,  0x6a1f,  0x7ae0,  0x5f70,  0x6f33,  0x5f20,  0x638c,  0x6da8,  0x6756,  0x4e08,  0x5e10,  0x8d26,  0x4ed7,  0x80c0,  0x7634,  0x969c,  0x4ec9,  0x9123,  0x5e5b,  0x5d82,  0x7350,  0x5adc,  0x748b,  0x87d1,
// zhao  ³¯          ÕÐ          ÕÑ          ÕÒ          ÕÓ          ÕÔ          ÕÕ          ÕÖ          Õ×          ÕØ          ÕÙ          ×¦          ×Å          Ú¯          èþ          îÈ          óÉ
    0x671d,  0x62db,  0x662d,  0x627e,  0x6cbc,  0x8d75,  0x7167,  0x7f69,  0x5146,  0x8087,  0x53ec,  0x722a,  0x7740,  0x8bcf,  0x68f9,  0x948a,  0x7b0a,
// zhe  ÕÚ          ÕÛ          ÕÜ          ÕÝ          ÕÞ          Õß          Õà          Õá          Õâ          Õã          ×Å          Ø±          ÚØ          ß¡          èÏ          éü          íÝ          ðÑ          ñÞ          òØ          ó§          ô÷
    0x906e,  0x6298,  0x54f2,  0x86f0,  0x8f99,  0x8005,  0x9517,  0x8517,  0x8fd9,  0x6d59,  0x7740,  0x4e47,  0x8c2a,  0x647a,  0x67d8,  0x8f84,  0x78d4,  0x9e67,  0x8936,  0x8707,  0x87ab,  0x8d6d,
// zhen  Õä          Õå          Õæ          Õç          Õè          Õé          Õê          Õë          Õì          Õí          Õî          Õï          Õð          Õñ          Õò          Õó          Ö¡          ÛÚ          Ýè          ä¥          çÇ          èå          é©          é»          éô          êâ          ëÓ          ëÞ          ìõ          î³          ð¡          ð²          óð
    0x73cd,  0x659f,  0x771f,  0x7504,  0x7827,  0x81fb,  0x8d1e,  0x9488,  0x4fa6,  0x6795,  0x75b9,  0x8bca,  0x9707,  0x632f,  0x9547,  0x9635,  0x5e27,  0x5733,  0x84c1,  0x6d48,  0x7f1c,  0x6862,  0x6939,  0x699b,  0x8f78,  0x8d48,  0x80d7,  0x6715,  0x796f,  0x755b,  0x7a39,  0x9e29,  0x7bb4,
// zheng  Õô          Õõ          Õö          Õ÷          Õø          Õù          Õú          Õû          Õü          Õý          Õþ          Ö¢          Ö£          Ö¤          Úº          á¿          áç          îÛ          ï£          óÝ
    0x84b8,  0x6323,  0x7741,  0x5f81,  0x72f0,  0x4e89,  0x6014,  0x6574,  0x62ef,  0x6b63,  0x653f,  0x75c7,  0x90d1,  0x8bc1,  0x8be4,  0x5ce5,  0x5fb5,  0x94b2,  0x94ee,  0x7b5d,
// zhi  Ö¥       Ö¦        Ö§        Ö¨        Ö©       Öª        Ö«       Ö¬         Ö­        Ö®        Ö¯       Ö°       Ö±        Ö²        Ö³         Ö´         Öµ         Ö¶         Ö·
    0x829d,  0x679d,  0x652f,  0x5431,  0x8718,  0x77e5,  0x80a2,  0x8102,  0x6c41,  0x4e4b,  0x7ec7,  0x804c,  0x76f4,  0x690d,  0x6b96,  0x6267,  0x503c,  0x4f84,  0x5740,
//  Ö¸          Ö¹          Öº          Ö»       Ö¼        Ö½       Ö¾        Ö¿        ÖÀ        ÖÁ        ÖÂ        ÖÃ        ÖÄ        ÖÅ        ÖÆ        ÖÇ        ÖÈ        ÖÉ        ÖÊ
    0x6307,  0x6b62,  0x8dbe,  0x53ea,  0x65e8,  0x7eb8,  0x5fd7,  0x631a,  0x63b7,  0x81f3,  0x81f4,  0x7f6e,  0x5e1c,  0x5cd9,  0x5236,  0x667a,  0x79e9,  0x7a1a,  0x8d28,
//  ÖË          ÖÌ          ÖÍ          ÖÎ       ÖÏ        Ø´        Úì        Û¤        Ûú        ÜÆ        Þý        àù        âå        åé        åë        æï        èÎ        è×        èÙ
    0x7099,  0x75d4,  0x6ede,  0x6cbb,  0x7a92,  0x536e,  0x965f,  0x90c5,  0x57f4,  0x82b7,  0x646d,  0x5e19,  0x5fee,  0x5f58,  0x54ab,  0x9a98,  0x6809,  0x67b3,  0x6800,
//  èä          éò          éù          êÞ          ëÕ          ëù          ìí          íé          ïô          ðº          ðë          òÎ          ôê          õ¥          õÅ          õÙ          õÜ          õô          ö£
    0x684e,  0x8f75,  0x8f7e,  0x8d3d,  0x80dd,  0x81a3,  0x7949,  0x9ef9,  0x96c9,  0x9e37,  0x75e3,  0x86ed,  0x7d77,  0x916f,  0x8dd6,  0x8e2c,  0x8e2f,  0x8c78,  0x89ef,
// zhong  ÖÐ          ÖÑ          ÖÒ          ÖÓ          ÖÔ          ÖÕ          ÖÖ          Ö×          ÖØ          ÖÙ          ÖÚ          Ú£          âì          ïñ          ó®          ô±          õà
    0x4e2d,  0x76c5,  0x5fe0,  0x949f,  0x8877,  0x7ec8,  0x79cd,  0x80bf,  0x91cd,  0x4ef2,  0x4f17,  0x51a2,  0x5fea,  0x953a,  0x87bd,  0x822f,  0x8e35,
// zhou  ÖÛ          ÖÜ          ÖÝ          ÖÞ          Öß          Öà          Öá          Öâ          Öã          Öä          Öå          Öæ          Öç          Öè          Ý§          ßú          æ¨          æû          ç§          ëÐ          íØ          ô¦          ôí          ôü
    0x821f,  0x5468,  0x5dde,  0x6d32,  0x8bcc,  0x7ca5,  0x8f74,  0x8098,  0x5e1a,  0x5492,  0x76b1,  0x5b99,  0x663c,  0x9aa4,  0x836e,  0x5541,  0x59af,  0x7ea3,  0x7ec9,  0x80c4,  0x78a1,  0x7c40,  0x7e47,  0x914e,
// zhu  Êô      Öé          Öê    Öë          Öì       Öí          Öî      Öï      Öð        Öñ        Öò        Öó         Öô          Öõ       Öö        Ö÷        Öø          Öù        Öú
    0x5c5e,  0x73e0,  0x682a,  0x86db,  0x6731,  0x732a,  0x8bf8,  0x8bdb,  0x9010,  0x7af9,  0x70db,  0x716e,  0x62c4,  0x77a9,  0x5631,  0x4e3b,  0x8457,  0x67f1,  0x52a9,
//  Öû          Öü          Öý          Öþ          ×¡          ×¢          ×£          ×¤          Øù          Ùª          Û¥          ÜÑ          Üï          ä¨          ä¾          äó          èÌ          éÆ          éÍ          ìÄ          îù          ðæ          ðñ          óÃ          óç          ô¶          ôã          õî          ÷æ
    0x86c0,  0x8d2e,  0x94f8,  0x7b51,  0x4f4f,  0x6ce8,  0x795d,  0x9a7b,  0x4f2b,  0x4f8f,  0x90be,  0x82ce,  0x8331,  0x6d19,  0x6e1a,  0x6f74,  0x677c,  0x69e0,  0x6a65,  0x70b7,  0x94e2,  0x75b0,  0x7603,  0x7afa,  0x7bb8,  0x8233,  0x7fe5,  0x8e85,  0x9e88,
// zhua  ÎÎ          ×¥          ×¦
    0x631d,  0x6293,  0x722a,
// zhuai  ×§
    0x62fd,
// zhuan  ´«          ×¨          ×©          ×ª          ×«          ×¬          ×­          ßù          âÍ          ò§
    0x4f20,  0x4e13,  0x7816,  0x8f6c,  0x64b0,  0x8d5a,  0x7bc6,  0x556d,  0x9994,  0x989b,
// zhuang  ´±          ×®          ×¯          ×°          ×±          ×²          ×³          ×´          Ù×
    0x5e62,  0x6869,  0x5e84,  0x88c5,  0x5986,  0x649e,  0x58ee,  0x72b6,  0x50ee,
// zhui  ×µ          ×¶          ×·          ×¸          ×¹          ×º          ÝÈ          ã·          æí          çÄ          ö¿
    0x690e,  0x9525,  0x8ffd,  0x8d58,  0x5760,  0x7f00,  0x8411,  0x60f4,  0x9a93,  0x7f12,  0x96b9,
// zhun  ÍÍ          ×»          ×¼          ëÆ          ñ¸
    0x5c6f,  0x8c06,  0x51c6,  0x80ab,  0x7a80,
// zhuo  ×½          ×¾          ×¿          ×À          ×Á          ×Â          ×Ã          ×Ä          ×Å          ×Æ          ×Ç          Ù¾          ÚÂ          ßª          ä·          äÃ          åª          ìú          í½          ïí
    0x6349,  0x62d9,  0x5353,  0x684c,  0x7422,  0x8301,  0x914c,  0x5544,  0x7740,  0x707c,  0x6d4a,  0x502c,  0x8bfc,  0x64e2,  0x6d5e,  0x6dbf,  0x6fef,  0x799a,  0x65ab,  0x956f,
// zi  ×È          ×É        ×Ê       ×Ë        ×Ì       ×Í        ×Î        ×Ï        ×Ð        ×Ñ        ×Ò        ×Ó        ×Ô        ×Õ        ×Ö        ÚÑ        Üë        ßÚ          áÑ
    0x5179,  0x54a8,  0x8d44,  0x59ff,  0x6ecb,  0x6dc4,  0x5b5c,  0x7d2b,  0x4ed4,  0x7c7d,  0x6ed3,  0x5b50,  0x81ea,  0x6e0d,  0x5b57,  0x8c18,  0x8308,  0x5472,  0x5d6b,
//  æ¢          æÜ          ç»          è÷          ê¢          êß          í§          íö          ïÅ          ïö          ñè          óÊ          ôÒ          ôô          õþ          ö¤          ö·          öö          ÷Ú
    0x59ca,  0x5b73,  0x7f01,  0x6893,  0x8f8e,  0x8d40,  0x6063,  0x7726,  0x9531,  0x79ed,  0x8014,  0x7b2b,  0x7ca2,  0x8d91,  0x89dc,  0x8a3e,  0x9f87,  0x9cbb,  0x9aed,
// zong  ××          ×Ø          ×Ù          ×Ú          ×Û          ×Ü          ×Ý          ÙÌ          ëê          ôÕ
    0x9b03,  0x68d5,  0x8e2a,  0x5b97,  0x7efc,  0x603b,  0x7eb5,  0x506c,  0x8159,  0x7cbd,
// zou  ×Þ          ×ß          ×à          ×á          ÚÁ          Úî          Û¸          æã          öí
    0x90b9,  0x8d70,  0x594f,  0x63cd,  0x8bf9,  0x966c,  0x9139,  0x9a7a,  0x9cb0,
// zu  ×â          ×ã          ×ä          ×å          ×æ          ×ç          ×è          ×é          ÙÞ          ÝÏ          ïß
    0x79df,  0x8db3,  0x5352,  0x65cf,  0x7956,  0x8bc5,  0x963b,  0x7ec4,  0x4fce,  0x83f9,  0x955e,
// zuan  ×ê          ×ë          ß¬          çÚ          õò
    0x94bb,  0x7e82,  0x6525,  0x7f35,  0x8e9c,
// zui  ×ì          ×í          ×î          ×ï          Þ©          õþ
    0x5634,  0x9189,  0x6700,  0x7f6a,  0x855e,  0x89dc,
// zun  ×ð          ×ñ          ß¤          é×          ÷®
    0x5c0a,  0x9075,  0x6499,  0x6a3d,  0x9cdf,
// zuo  ×ò          ×ó          ×ô          ×õ          ×ö          ×÷          ×ø          ×ù          Úè          ßò          àÜ          âô          ëÑ          ìñ          óÐ          õ¡
    0x6628,  0x5de6,  0x4f50,  0x67de,  0x505a,  0x4f5c,  0x5750,  0x5ea7,  0x963c,  0x5511,  0x562c,  0x600d,  0x80d9,  0x795a,  0x7b2e,  0x9162,
};



#endif
