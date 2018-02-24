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

#include <string.h>

#include "Board.h"

#if( CHAKRA3_AUTO_TEST )

#include "MApp_AutoTest.h"

//=======================================================================
//
#if (ENABLE_DTV)

MEMBER_SI_SERVICETYPE MApp_AT_ConvertSeviceToSI(MEMBER_SERVICETYPE mServiceType)
{
    MEMBER_SI_SERVICETYPE mSIType;
    switch(mServiceType)
    {
        case E_SERVICETYPE_DTV:
            mSIType = E_TYPE_DTV;
            break;
        case E_SERVICETYPE_RADIO:
            mSIType = E_TYPE_RADIO;
            break;
        case E_SERVICETYPE_DATA:
            mSIType = E_TYPE_DATA;
            break;
        default:
            mSIType = E_TYPE_DTV;
            break;
    }
    return mSIType;
}

#endif // #if (ENABLE_DTV)


EN_LANGUAGE MApp_AT_ConvertATLangToENLang(EN_AT_MEMBER_LANGUAGE mLan)
{
    EN_LANGUAGE enLan;
    switch(mLan)
    {
        case E_LANGUAGE_UNKNOWN:
            enLan = LANGUAGE_UNKNOWN;
            break;
        case E_LANGUAGE_NONE:
            enLan = LANGUAGE_NONE;
            break;
        case E_LANGUAGE_ENGLISH:
            enLan = LANGUAGE_ENGLISH;
            break;
        case E_LANGUAGE_FRENCH:
            enLan = LANGUAGE_FRENCH;
            break;
        case E_LANGUAGE_GERMAN:
            enLan = LANGUAGE_GERMAN;
            break;
        case E_LANGUAGE_ITALIAN:
            enLan = LANGUAGE_ITALIAN;
            break;
        case E_LANGUAGE_SPANISH:
            enLan = LANGUAGE_SPANISH;
            break;
        case E_LANGUAGE_SWEDISH:
            enLan = LANGUAGE_SWEDISH;
            break;
        case E_LANGUAGE_FINNISH:
            enLan = LANGUAGE_FINNISH;
            break;
        case E_LANGUAGE_PORTUGUESE:
            enLan = LANGUAGE_PORTUGUESE;
            break;
        case E_LANGUAGE_TURKISH:
            enLan = LANGUAGE_TURKISH;
            break;
        case E_LANGUAGE_CZECH:
            enLan = LANGUAGE_CZECH;
            break;
        case E_LANGUAGE_DANISH:
            enLan = LANGUAGE_DANISH;
            break;
        case E_LANGUAGE_DUTCH:
            enLan = LANGUAGE_DUTCH;
            break;
        case E_LANGUAGE_POLISH:
            enLan = LANGUAGE_POLISH;
            break;
        case E_LANGUAGE_GREEK:
            enLan = LANGUAGE_GREEK;
            break;
        case E_LANGUAGE_HUNGARIAN:
            enLan = LANGUAGE_HUNGARIAN;
            break;
        case E_LANGUAGE_NORWEGIAN:
            enLan = LANGUAGE_NORWEGIAN;
            break;
        case E_LANGUAGE_ROMANIAN:
            enLan = LANGUAGE_ROMANIAN;
            break;
        case E_LANGUAGE_RUSSIAN:
            enLan = LANGUAGE_RUSSIAN;
            break;
        case E_LANGUAGE_ARABIC:
            enLan = LANGUAGE_ARABIC;
            break;
        case E_LANGUAGE_HEBREW:
            enLan = LANGUAGE_HEBREW;
            break;
        case E_LANGUAGE_QAA:
            enLan = LANGUAGE_QAA;
            break;
        case E_LANGUAGE_SERBIAN:
            enLan = LANGUAGE_SERBIAN;
            break;
        case E_LANGUAGE_SLOVENIAN:
            enLan = LANGUAGE_SLOVENIAN;
            break;
        case E_LANGUAGE_CROATIAN:
            enLan = LANGUAGE_CROATIAN;
            break;
        case E_LANGUAGE_BULGARIAN:
            enLan = LANGUAGE_BULGARIAN;
            break;
        case E_LANGUAGE_WELSH:
            enLan = LANGUAGE_WELSH;
            break;
        case E_LANGUAGE_GAELIC:
            enLan = LANGUAGE_GAELIC;
            break;
        case E_LANGUAGE_IRISH:
            enLan = LANGUAGE_IRISH;
            break;
        case E_LANGUAGE_KOREAN:
            enLan = LANGUAGE_KOREAN;
            break;
        case E_LANGUAGE_MANDARIN:
            enLan = LANGUAGE_MANDARIN;
            break;
        case E_LANGUAGE_CANTONESE:
            enLan = LANGUAGE_CANTONESE;
            break;
        case E_LANGUAGE_HINDI:
            enLan = LANGUAGE_HINDI;
            break;
#if (ENABLE_TTF_FONT)
        case E_LANGUAGE_BURMESE:
            enLan = LANGUAGE_MYANMAR;
            break;
        case E_LANGUAGE_KHMER:
            enLan = LANGUAGE_KHMER;
            break;
        case E_LANGUAGE_LAO:
            enLan = LANGUAGE_LAO;
            break;
#endif
        case E_LANGUAGE_MAORI:
            enLan = LANGUAGE_MAORI;
            break;
        case E_LANGUAGE_SLOVAK:
            enLan = LANGUAGE_SLOVAK;
            break;
        case E_LANGUAGE_LATVIAN:
            enLan = LANGUAGE_LATVIAN;
            break;
        case E_LANGUAGE_ESTONIAN:
            enLan = LANGUAGE_ESTONIAN;
            break;
        case E_LANGUAGE_NETHERLANDS:
            enLan = LANGUAGE_NETHERLANDS;
            break;
        case E_LANGUAGE_ASSAMESE:
            enLan = LANGUAGE_ASSAMESE;
            break;
        case E_LANGUAGE_GALLEGAN:
            enLan = LANGUAGE_GALLEGAN;
            break;
        case E_LANGUAGE_ICELANDIC:
            enLan = LANGUAGE_ICELANDIC;
            break;
        case E_LANGUAGE_KANNADA:
            enLan = LANGUAGE_KANNADA;
            break;
        case E_LANGUAGE_KURDISH:
            enLan = LANGUAGE_KURDISH;
            break;
        case E_LANGUAGE_LITHUANIAN:
            enLan = LANGUAGE_LITHUANIAN;
            break;
        case E_LANGUAGE_MALAYALAM:
            enLan = LANGUAGE_MALAYALAM;
            break;
        case E_LANGUAGE_MARATHI:
            enLan = LANGUAGE_MARATHI;
            break;
        case E_LANGUAGE_SAMI:
            enLan = LANGUAGE_SAMI;
            break;
        case E_LANGUAGE_TAMIL:
            enLan = LANGUAGE_TAMIL;
            break;
        case E_LANGUAGE_TELUGU:
            enLan = LANGUAGE_TELUGU;
            break;
        case E_LANGUAGE_THAI:
            enLan = LANGUAGE_THAI;
            break;
        case E_LANGUAGE_URDU:
            enLan = LANGUAGE_URDU;
            break;
        default:
            enLan = LANGUAGE_UNKNOWN;
            break;
    }
    return enLan;
}

void DisplayLanguage(const EN_LANGUAGE enLan)
{
    char tmp[32];
    switch(enLan)
    {
        case LANGUAGE_UNKNOWN:
            //snprintf(tmp, sizeof(tmp), "UNKNOWN\n");
            snprintf(tmp, sizeof(tmp), "UND\n");
            break;
        case LANGUAGE_NONE:
            snprintf(tmp, sizeof(tmp), "NONE\n");
            break;
        case LANGUAGE_ENGLISH:
            snprintf(tmp, sizeof(tmp), "ENGLISH\n");
            break;
        case LANGUAGE_FRENCH:
            snprintf(tmp, sizeof(tmp), "FRENCH\n");
            break;
        case LANGUAGE_GERMAN:
            snprintf(tmp, sizeof(tmp), "GERMAN\n");
            break;
        case LANGUAGE_ITALIAN:
            snprintf(tmp, sizeof(tmp), "ITALIAN\n");
            break;
        case LANGUAGE_SPANISH:
            snprintf(tmp, sizeof(tmp), "SPANISH\n");
            break;
        case LANGUAGE_SWEDISH:
            snprintf(tmp, sizeof(tmp), "SWEDISH\n");
            break;
        case LANGUAGE_FINNISH:
            snprintf(tmp, sizeof(tmp), "FINNISH\n");
            break;
        case LANGUAGE_PORTUGUESE:
            snprintf(tmp, sizeof(tmp), "PORTUGUESE\n");
            break;
        case LANGUAGE_TURKISH:
            snprintf(tmp, sizeof(tmp), "TURKISH\n");
            break;
        case LANGUAGE_CZECH:
            snprintf(tmp, sizeof(tmp), "CZECH\n");
            break;
        case LANGUAGE_DANISH:
            snprintf(tmp, sizeof(tmp), "DANISH\n");
            break;
        case LANGUAGE_DUTCH:
            snprintf(tmp, sizeof(tmp), "DUTCH\n");
            break;
        case LANGUAGE_POLISH:
            snprintf(tmp, sizeof(tmp), "POLISH\n");
            break;
        case LANGUAGE_GREEK:
            snprintf(tmp, sizeof(tmp), "GREEK\n");
            break;
        case LANGUAGE_HUNGARIAN:
            snprintf(tmp, sizeof(tmp), "HUNGARIAN\n");
            break;
        case LANGUAGE_NORWEGIAN:
            snprintf(tmp, sizeof(tmp), "NORWEGIAN\n");
            break;
        case LANGUAGE_ROMANIAN:
            snprintf(tmp, sizeof(tmp), "ROMANIAN\n");
            break;
        case LANGUAGE_RUSSIAN:
            snprintf(tmp, sizeof(tmp), "RUSSIAN\n");
            break;
        case LANGUAGE_ARABIC:
            snprintf(tmp, sizeof(tmp), "ARABIC\n");
            break;
        case LANGUAGE_HEBREW:
            snprintf(tmp, sizeof(tmp), "HEBREW\n");
            break;
        case LANGUAGE_QAA:
            snprintf(tmp, sizeof(tmp), "QAA\n");
            break;
        case LANGUAGE_SERBIAN:
            snprintf(tmp, sizeof(tmp), "SERBIAN\n");
            break;
        case LANGUAGE_SLOVENIAN:
            snprintf(tmp, sizeof(tmp), "SLOVENIAN\n");
            break;
        case LANGUAGE_CROATIAN:
            snprintf(tmp, sizeof(tmp), "CROATIAN\n");
            break;
        case LANGUAGE_BULGARIAN:
            snprintf(tmp, sizeof(tmp), "BULGARIAN\n");
            break;
        case LANGUAGE_WELSH:
            snprintf(tmp, sizeof(tmp), "WELSH\n");
            break;
        case LANGUAGE_GAELIC:
            snprintf(tmp, sizeof(tmp), "GAELIC\n");
            break;
        case LANGUAGE_IRISH:
            snprintf(tmp, sizeof(tmp), "IRISH\n");
            break;
        case LANGUAGE_KOREAN:
            snprintf(tmp, sizeof(tmp), "KOREAN\n");
            break;
        case LANGUAGE_MANDARIN:
            snprintf(tmp, sizeof(tmp), "MANDARIN\n");
            break;
        case LANGUAGE_CANTONESE:
            snprintf(tmp, sizeof(tmp), "CANTONESE\n");
            break;
        case LANGUAGE_HINDI:
            snprintf(tmp, sizeof(tmp), "HINDI\n");
            break;
        case LANGUAGE_MAORI:
            snprintf(tmp, sizeof(tmp), "MAORI\n");
            break;
        case LANGUAGE_SLOVAK:
            snprintf(tmp, sizeof(tmp), "SLOVAK\n");
            break;
        case LANGUAGE_LATVIAN:
            snprintf(tmp, sizeof(tmp), "LATVIAN\n");
            break;
        case LANGUAGE_ESTONIAN:
            snprintf(tmp, sizeof(tmp), "ESTONIAN\n");
            break;
        case LANGUAGE_NETHERLANDS:
            snprintf(tmp, sizeof(tmp), "NETHERLANDS\n");
            break;
        case LANGUAGE_ASSAMESE:
            snprintf(tmp, sizeof(tmp), "ASSAMESE\n");
            break;
        case LANGUAGE_GALLEGAN:
            snprintf(tmp, sizeof(tmp), "GALLEGAN\n");
            break;
        case LANGUAGE_ICELANDIC:
            snprintf(tmp, sizeof(tmp), "ICELANDIC\n");
            break;
        case LANGUAGE_KANNADA:
            snprintf(tmp, sizeof(tmp), "KANNADA\n");
            break;
        case LANGUAGE_KURDISH:
            snprintf(tmp, sizeof(tmp), "KURDISH\n");
            break;
        case LANGUAGE_LITHUANIAN:
            snprintf(tmp, sizeof(tmp), "LITHUANIAN\n");
            break;
        case LANGUAGE_MALAYALAM:
            snprintf(tmp, sizeof(tmp), "MALAYALAM\n");
            break;
        case LANGUAGE_MARATHI:
            snprintf(tmp, sizeof(tmp), "MARATHI\n");
            break;
        case LANGUAGE_SAMI:
            snprintf(tmp, sizeof(tmp), "SAMI\n");
            break;
        case LANGUAGE_TAMIL:
            snprintf(tmp, sizeof(tmp), "TAMIL\n");
            break;
        case LANGUAGE_TELUGU:
            snprintf(tmp, sizeof(tmp), "TELUGU\n");
            break;
        case LANGUAGE_THAI:
            snprintf(tmp, sizeof(tmp), "THAI\n");
            break;
        case LANGUAGE_URDU:
            snprintf(tmp, sizeof(tmp), "URDU\n");
            break;
#if (ENABLE_TTF_FONT)
        case LANGUAGE_MYANMAR:
            snprintf(tmp, sizeof(tmp), "MYANMAR\n");
            break;
        case LANGUAGE_KHMER:
            snprintf(tmp, sizeof(tmp), "KHM\n");
            break;
        case LANGUAGE_LAO:
            snprintf(tmp, sizeof(tmp), "LAO\n");
            break;
#endif //__MYANMAR_FONT__
        default:
            snprintf(tmp, sizeof(tmp), "UND\n");
            break;
    }
    MApp_AT_Msg_Add((U8*)tmp);
}

MEMBER_COUNTRY MApp_AT_ConvertATCountryToMemCountry(const EN_AT_MEMBER_COUNTRY enCountry)
{
    MEMBER_COUNTRY mCountry;
    switch(enCountry)
    {
        case EN_AT_AUSTRALIA:
            mCountry = E_AUSTRALIA;
            break;
        case EN_AT_AUSTRIA:
            mCountry = E_AUSTRIA;
            break;
        case EN_AT_BELGIUM:
            mCountry = E_BELGIUM;
            break;
        case EN_AT_BULGARIA:
            mCountry = E_BULGARIA;
            break;
        case EN_AT_CROATIA:
            mCountry = E_CROATIA;
            break;
        case EN_AT_CZECH:
            mCountry = E_CZECH;
            break;
        case EN_AT_DENMARK:
            mCountry = E_DENMARK;
            break;
        case EN_AT_FINLAND:
            mCountry = E_FINLAND;
            break;
        case EN_AT_FRANCE:
            mCountry = E_FRANCE;
            break;
        case EN_AT_GERMANY:
            mCountry = E_GERMANY;
            break;
        case EN_AT_GREECE:
            mCountry = E_GREECE;
            break;
        case EN_AT_HUNGARY:
            mCountry = E_HUNGARY;
            break;
        case EN_AT_ITALY:
            mCountry = E_ITALY;
            break;
        case EN_AT_IRELAND:
            mCountry = E_IRELAND;
            break;
        case EN_AT_LUXEMBOURG:
            mCountry = E_LUXEMBOURG;
            break;
        case EN_AT_NETHERLANDS:
            mCountry = E_NETHERLANDS;
            break;
        case EN_AT_NORWAY:
            mCountry = E_NORWAY;
            break;
        case EN_AT_POLAND:
            mCountry = E_POLAND;
            break;
        case EN_AT_PORTUGAL:
            mCountry = E_PORTUGAL;
            break;
        case EN_AT_ROMANIA:
            mCountry = E_ROMANIA;
            break;
        case EN_AT_RUSSIA:
            mCountry = E_RUSSIA;
            break;
        case EN_AT_SERBIA:
            mCountry = E_SERBIA;
            break;
        case EN_AT_SLOVENIA:
            mCountry = E_SLOVENIA;
            break;
        case EN_AT_SPAIN:
            mCountry = E_SPAIN;
            break;
        case EN_AT_SWEDEN:
            mCountry = E_SWEDEN;
            break;
        case EN_AT_SWITZERLAND:
            mCountry = E_SWITZERLAND;
            break;
        case EN_AT_UK:
            mCountry = E_UK;
            break;
        case EN_AT_NEWZEALAND:
            mCountry = E_NEWZEALAND;
            break;
        case EN_AT_CHINA:
            mCountry = E_CHINA;
            break;
        case EN_AT_ESTONIA:
            mCountry = E_ESTONIA;
            break;
        case EN_AT_TURKEY:
            mCountry = E_TURKEY;
            break;
        case EN_AT_MOROCCO:
            mCountry = E_MOROCCO;
            break;
        case EN_AT_TUNIS:
            mCountry = E_TUNIS;
            break;
        case EN_AT_ALGERIA:
            mCountry = E_ALGERIA;
            break;
        case EN_AT_EGYPT:
            mCountry = E_EGYPT;
            break;
        case EN_AT_SOUTHAFRICA:
            mCountry = E_SOUTH_AFRICA;
            break;
        case EN_AT_ISRAEL:
            mCountry = E_ISRAEL;
            break;
        case EN_AT_IRAN:
            mCountry = E_IRAN;
            break;
        case EN_AT_SLOVAKIA:
            mCountry = E_SLOVAKIA;
            break;
        case EN_AT_THAILAND:
            mCountry = E_THAILAND;
            break;
        case EN_AT_INDONESIA:
            mCountry = E_INDONESIA;
            break;
#if (ENABLE_DVB_TAIWAN_APP)
        case EN_AT_TAIWAN:
            mCountry = E_TAIWAN;
            break;
#endif
        case EN_AT_BRAZIL:
            mCountry = E_BRAZIL;
            break;

        default:
            mCountry = E_COUNTRY_MIN;
            break;
    }
    return mCountry;
}

void DisplayCountry(const MEMBER_COUNTRY enCountry)
{
    char tmp[32];
    switch(enCountry)
    {
        case E_AUSTRALIA:
            snprintf(tmp, sizeof(tmp), "AUSTRALIA\n");
            break;
        case E_AUSTRIA:
            snprintf(tmp, sizeof(tmp), "AUSTRIA\n");
            break;
        case E_BELGIUM:
            snprintf(tmp, sizeof(tmp), "BELGIUM\n");
            break;
        case E_BULGARIA:
            snprintf(tmp, sizeof(tmp), "BULGARIA\n");
            break;
        case E_CROATIA:
            snprintf(tmp, sizeof(tmp), "CROATIA\n");
            break;
        case E_CZECH:
            snprintf(tmp, sizeof(tmp), "CZECH\n");
            break;
        case E_DENMARK:
            snprintf(tmp, sizeof(tmp), "DENMARK\n");
            break;
        case E_FINLAND:
            snprintf(tmp, sizeof(tmp), "FINLAND\n");
            break;
        case E_FRANCE:
            snprintf(tmp, sizeof(tmp), "FRANCE\n");
            break;
        case E_GERMANY:
            snprintf(tmp, sizeof(tmp), "GERMANY\n");
            break;
        case E_GREECE:
            snprintf(tmp, sizeof(tmp), "GREECE\n");
            break;
        case E_HUNGARY:
            snprintf(tmp, sizeof(tmp), "HUNGARY\n");
            break;
        case E_ITALY:
            snprintf(tmp, sizeof(tmp), "ITALY\n");
            break;
        case E_IRELAND:
            snprintf(tmp, sizeof(tmp), "E_IRELAND\n");
            break;
        case E_LUXEMBOURG:
            snprintf(tmp, sizeof(tmp), "LUXEMBOURG\n");
            break;
        case E_NETHERLANDS:
            snprintf(tmp, sizeof(tmp), "NETHERLANDS\n");
            break;
        case E_NORWAY:
            snprintf(tmp, sizeof(tmp), "NORWAY\n");
            break;
        case E_POLAND:
            snprintf(tmp, sizeof(tmp), "POLAND\n");
            break;
        case E_PORTUGAL:
            snprintf(tmp, sizeof(tmp), "PORTUGAL\n");
            break;
        case E_ROMANIA:
            snprintf(tmp, sizeof(tmp), "ROMANIA\n");
            break;
        case E_RUSSIA:
            snprintf(tmp, sizeof(tmp), "RUSSIA\n");
            break;
        case E_SERBIA:
            snprintf(tmp, sizeof(tmp), "SERBIA\n");
            break;
        case E_SLOVENIA:
            snprintf(tmp, sizeof(tmp), "SLOVENIA\n");
            break;
        case E_SPAIN:
            snprintf(tmp, sizeof(tmp), "SPAIN\n");
            break;
        case E_SWEDEN:
            snprintf(tmp, sizeof(tmp), "SWEDEN\n");
            break;
        case E_SWITZERLAND:
            snprintf(tmp, sizeof(tmp), "SWITZERLAND\n");
            break;
        case E_UK:
            snprintf(tmp, sizeof(tmp), "UK\n");
            break;
        case E_UNITED_ARAB_EMIRATES:
            snprintf(tmp, sizeof(tmp), "United Arab Emirates\n");
            break;
        case E_KUWAIT:
            snprintf(tmp, sizeof(tmp), "KUWAIT\n");
            break;
        case E_OMAN:
            snprintf(tmp, sizeof(tmp), "OMAN\n");
            break;
        case E_QATAR:
            snprintf(tmp, sizeof(tmp), "QATAR\n");
            break;
        case E_SAUDI_ARABIA:
            snprintf(tmp, sizeof(tmp), "Saudi Arabia\n");
            break;
        case E_BAHRAIN:
            snprintf(tmp, sizeof(tmp), "Bahrain\n");
            break;
        case E_NEWZEALAND:
            snprintf(tmp, sizeof(tmp), "NEWZEALAND\n");
            break;
        case E_CHINA:
            snprintf(tmp, sizeof(tmp), "China\n");
            break;
        case E_ESTONIA:
            snprintf(tmp, sizeof(tmp), "ESTONIA\n");
            break;
        case E_TURKEY:
            snprintf(tmp, sizeof(tmp), "TURKEY\n");
            break;
        case E_MOROCCO:
            snprintf(tmp, sizeof(tmp), "Morocco\n");
            break;
        case E_TUNIS:
            snprintf(tmp, sizeof(tmp), "Tunis\n");
            break;
        case E_ALGERIA:
            snprintf(tmp, sizeof(tmp), "Algeria\n");
            break;
        case E_EGYPT:
            snprintf(tmp, sizeof(tmp), "Egypt\n");
            break;
        case E_SOUTH_AFRICA:
            snprintf(tmp, sizeof(tmp), "South Africa\n");
            break;
        case E_ISRAEL:
            snprintf(tmp, sizeof(tmp), "Israel\n");
            break;
        case E_IRAN:
            snprintf(tmp, sizeof(tmp), "Iran\n");
            break;
        case E_SLOVAKIA:
            snprintf(tmp, sizeof(tmp), "Slovakia\n");
            break;
        case E_THAILAND:
            snprintf(tmp, sizeof(tmp), "Thailand\n");
            break;
        case E_VIETNAM:
            snprintf(tmp, sizeof(tmp), "Vietnam\n");
            break;
        case E_SINGAPORE:
            snprintf(tmp, sizeof(tmp), "Singapore\n");
            break;
#if (ENABLE_COUNTRY_KENYA)
        case E_KENYA:
            snprintf(tmp, sizeof(tmp), "Kenya\n");
            break;
#endif
#if (ENABLE_COUNTRY_MYANMAR)
        case E_MYANMAR:
            snprintf(tmp, sizeof(tmp), "Myanmar\n");
            break;
#endif
        case E_MALAYSIA:
            snprintf(tmp, sizeof(tmp), "Malaysia\n");
            break;
        case E_INDONESIA:
            snprintf(tmp, sizeof(tmp), "Indonesia\n");
            break;
#if (ENABLE_DVB_TAIWAN_APP)
        case E_TAIWAN:
            snprintf(tmp, sizeof(tmp), "Taiwan\n");
            break;
#endif

        case E_BRAZIL:
            snprintf(tmp, sizeof(tmp), "Brazil\n");
            break;

        default:
            snprintf(tmp, sizeof(tmp), "UND\n");
            break;
    }
    MApp_AT_Msg_Add((U8*)tmp);
}

void DisplayServiceType(const MEMBER_SERVICETYPE enServiceType)
{
    char tmp[32];
    switch(enServiceType)
    {
        case E_SERVICETYPE_ATV:
            snprintf(tmp, sizeof(tmp), "ATV\n");
            break;
        case E_SERVICETYPE_DTV:
            snprintf(tmp, sizeof(tmp), "DTV\n");
            break;
        case E_SERVICETYPE_RADIO:
            snprintf(tmp, sizeof(tmp), "RADIO\n");

            break;
        case E_SERVICETYPE_DATA:
            snprintf(tmp, sizeof(tmp), "DATA\n");
            break;
        case E_SERVICETYPE_UNITED_TV:
            snprintf(tmp, sizeof(tmp), "UNITED_TV\n");
            break;
        case E_SERVICETYPE_INVALID:
            snprintf(tmp, sizeof(tmp), "INVALID\n");
            break;
        default:
            snprintf(tmp, sizeof(tmp), "None\n");
            break;
    }
    MApp_AT_Msg_Add((U8*)tmp);
}

#if (ENABLE_DTV)

void DisplayVideoType(const VIDEO_TYPE enVideoType)
{
    char tmp[32];
    switch(enVideoType)
    {
        case E_VIDEOTYPE_MPEG:
            snprintf(tmp, sizeof(tmp), "MPEG");
            break;
        case E_VIDEOTYPE_H264:
            snprintf(tmp, sizeof(tmp), "H264");
            break;
        case E_VIDEOTYPE_AVS:
            snprintf(tmp, sizeof(tmp), "AVS");
            break;
        case E_VIDEOTYPE_VC1:
            snprintf(tmp, sizeof(tmp), "VC1");
            break;
        case E_VIDEOTYPE_H265:
            snprintf(tmp, sizeof(tmp), "H265");
            break;
        default:
            snprintf(tmp, sizeof(tmp), "None");
            break;
    }
    MApp_AT_Msg_Add((U8*)tmp);
}

void GetGenreType(MS_U8 u8Type, char* pstr)
{
    MEMBER_COUNTRY u8country;
    BOOL isUKCountry;
    u8country = msAPI_CM_GetCountry();

    if( u8country == E_UK )
    {
        isUKCountry = TRUE;
    }
    else
    {
        isUKCountry = FALSE;
    }

    switch( u8Type )
    {
        case 0x1: // Genre type is movie.
            strcpy(pstr, (TRUE == isUKCountry?  "Movie": "Movie/Drama"));
            break;
        case 0x2: // Genre type is news.
            strcpy(pstr, (TRUE == isUKCountry?  "News and Factual": "News/Current affairs"));
            break;
        case 0x3: // Genre type is show.
            strcpy(pstr, (TRUE == isUKCountry?  "Entertainment": "Show/Game show"));
          break;
        case 0x4: // Genre type is sport
            strcpy(pstr, (TRUE == isUKCountry?  "Sport": "Sports"));
            break;
        case 0x5: // Genre type is children.
            strcpy(pstr, (TRUE == isUKCountry?  "Children's": "Children's/Youth programmes"));
            break;
        case 0x6: // Genre type is music.
            strcpy(pstr, (TRUE == isUKCountry?  "Entertainment": "Music/Ballet/Dance"));
            break;
        case 0x7: // Genre type is arts.
            strcpy(pstr, (TRUE == isUKCountry?  "News and Factual": "Art/Culture(without music)"));
            break;
        case 0x8: // Genre type is social.
            strcpy(pstr, (TRUE == isUKCountry?  "News and Factual": "Social/Political Issues/Economics"));
            break;
        case 0x9: // Genre type is education.
            strcpy(pstr, (TRUE == isUKCountry?  "Education": "Education/Science/Factual Topics"));
            break;
        case 0x10: // Genre type is leisure.
            strcpy(pstr, (TRUE == isUKCountry?  "Lifestyle": "leisure Hobbis"));
            break;
        case 0x11: // Genre type is special.
            strcpy(pstr, (TRUE == isUKCountry?  "not supported": "Special Characteristics"));
            break;
        case 0x12: // Reserved constant.
        case 0x13: // Reserved constant.
        case 0x14: // Reserved constant.
            strcpy(pstr, (TRUE == isUKCountry?  "not supported": "Reserved for future use"));
            break;
        case 0x15: // Genre type is user defined.
            strcpy(pstr, (TRUE == isUKCountry?  "Drama": "user defined"));
            break;
        default:
            strcpy(pstr, (TRUE == isUKCountry?  "Unclassified": "Unclassified"));
            break;
        }
}

#endif // #if (ENABLE_DTV)


void DisplayAudioType(const AUDIOSTREAM_TYPE enAudioType)
{
    char tmp[32];
    switch(enAudioType)
    {
        case E_AUDIOSTREAM_MPEG:
            snprintf(tmp, sizeof(tmp), "MPEG");
            break;
        case E_AUDIOSTREAM_AC3:
            snprintf(tmp, sizeof(tmp), "AC3");
            break;
        case E_AUDIOSTREAM_AAC:
            snprintf(tmp, sizeof(tmp), "AAC");
            break;
        case E_AUDIOSTREAM_AC3P:
            snprintf(tmp, sizeof(tmp), "AC3P");
            break;
        default:
            break;
    }
    MApp_AT_Msg_Add((U8*)tmp);
}

EN_VIDEO_RESOLUTION ResolutionRemapping(MS_U16 u16HorSize, MS_U16 u16VerSize, MS_U8 u8Interlace, MS_U32 u32FrameRate)
{
    EN_VIDEO_RESOLUTION enRes = E_DTV_UND;
    if(((u16HorSize >= 710) && (u16HorSize <= 730)) && ((u16VerSize >= 470) && (u16VerSize <= 490)))
    {
        //720
        if(u8Interlace == 1)
        {
            enRes = E_DTV480i_60;// 480i
        }
        else
        {
            enRes = E_DTV480p_60;// 480p
        }
    }
    else if(((u16HorSize >= 710) && (u16HorSize <= 730)) && ((u16VerSize >= 566) && (u16VerSize <= 586)))
    {
        // 720
        if(u8Interlace == 1)
        {
            enRes = E_DTV576i_50;// 576i
        }
        else
        {
            enRes = E_DTV576p_50;// 576p
        }
    }
    else if(((u16HorSize >= 1270) && (u16HorSize <= 1290)) && ((u16VerSize >= 710) && (u16VerSize <= 730)))
    {
        // 1280
        // 720P
        if(u32FrameRate > 550)
        {
            enRes = E_DTV720p_60;
        }
        else
        {
            enRes = E_DTV720p_50;
        }
    }
    else if(((u16HorSize >= 1910) && (u16HorSize <= 1930)) && ((u16VerSize >= 1070) && (u16VerSize <= 1090)))
    {
        // 1920
        if(u8Interlace == 1)
        {
            if(u32FrameRate > 550)//1080i
            {
                enRes = E_DTV1080i_60;
            }
            else
            {
                enRes = E_DTV1080i_50;
            }
        }
        else
        {
            if(u32FrameRate > 550)// 1080P (60)
            {
                enRes = E_DTV1080p_60;
            }
            else if(u32FrameRate > 450)// 1080P (50)
            {
                enRes = E_DTV1080p_50;
            }
            else if(u32FrameRate > 275)// 1080P (30)
            {
                enRes = E_DTV1080p_30;
            }
            else if(u32FrameRate > 200)// 1080P (24P)
            {
                enRes = E_DTV1080p_24;
            }
        }
    }
    return enRes;

}

void DisplayResolution(const EN_VIDEO_RESOLUTION enResolution)
{
    char tmp[16];
    switch(enResolution)
    {
        case E_DTV480i_60:
            snprintf(tmp, sizeof(tmp), "480i\n");
            break;
        case E_DTV480p_60:
            snprintf(tmp, sizeof(tmp), "480p\n");
            break;
        case E_DTV576i_50:
            snprintf(tmp, sizeof(tmp), "576i\n");
            break;
        case E_DTV576p_50:
            snprintf(tmp, sizeof(tmp), "576p\n");
            break;
        case E_DTV720p_60:
        case E_DTV720p_50:
            snprintf(tmp, sizeof(tmp), "720p\n");
            break;
        case E_DTV1080i_60:
        case E_DTV1080i_50:
            snprintf(tmp, sizeof(tmp), "1080i\n");
            break;
        case E_DTV1080p_60:
        case E_DTV1080p_50:
        case E_DTV1080p_30:
        case E_DTV1080p_24:
            snprintf(tmp, sizeof(tmp), "1080p\n");
            break;
        case E_DTV_MAX:
            snprintf(tmp, sizeof(tmp), "MAX\n");
            break;
        default:
            snprintf(tmp, sizeof(tmp), "None\n");
            break;
    }
    MApp_AT_Msg_Add((U8*)tmp);
}

U32 msAPI_U16BufToU8Buf(U16* pu16Buf, U8* pu8Buf, U32 u32Size)
{
    U32 i;
    U16 u16Char;
    U32 u16StrLen = 0;

    for( i = 0; i < u32Size; ++ i )
    {
        u16Char = pu16Buf[i];

        if( u16Char == 0 )
            break;

        if( (u16Char >= 20)&&(u16Char < 128) )
        {
            pu8Buf[i] = u16Char;
        }
        else
        {
            pu8Buf[i] = '?';
        }

        u16StrLen += 1;
    }

    return u16StrLen;
}

#endif

