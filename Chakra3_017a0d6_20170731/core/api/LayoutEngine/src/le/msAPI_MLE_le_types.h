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

#ifndef __MSAPI_MSTAR_LE_TYPES_H__
#define __MSAPI_MSTAR_LE_TYPES_H__

#ifdef __FEATURE_VECTOR_FONT__

typedef U32 LE_Tag;
typedef U16 LE_Offset;
typedef U32 LE_Version;
typedef U16 LE_GlyphId;
typedef U32 LE_FeatureFlags;
typedef U8  LE_ClassCode;
typedef U8  LE_State;

enum
{
    LE_LANGUAGE_TAG_NULL = 0x00000000, /* '' (null) */
    LE_LANGUAGE_TAG_ARA = 0x41524120, /* 'ARA' (Arabic) */
    LE_LANGUAGE_TAG_ASM = 0x41534D20, /* 'ASM' (Assamese) */
    LE_LANGUAGE_TAG_BEN = 0x42454E20, /* 'BEN' (Bengali) */
    LE_LANGUAGE_TAG_FAR = 0x46415220, /* 'FAR' (Farsi) */
    LE_LANGUAGE_TAG_GUJ = 0x47554A20, /* 'GUJ' (Gujarati) */
    LE_LANGUAGE_TAG_HIN = 0x48494E20, /* 'HIN' (Hindi) */
    LE_LANGUAGE_TAG_IWR = 0x49575220, /* 'IWR' (Hebrew) */
    LE_LANGUAGE_TAG_JII = 0x4A494920, /* 'JII' (Yiddish) */
    LE_LANGUAGE_TAG_JAN = 0x4A414E20, /* 'JAN' (Japanese) */
    LE_LANGUAGE_TAG_KAN = 0x4B414E20, /* 'KAN' (Kannada) */
    LE_LANGUAGE_TAG_KOK = 0x4B4F4B20, /* 'KOK' (Konkani) */
    LE_LANGUAGE_TAG_KOR = 0x4B4F5220, /* 'KOR' (Korean) */
    LE_LANGUAGE_TAG_KSH = 0x4B534820, /* 'KSH' (Kashmiri) */
    LE_LANGUAGE_TAG_MAL = 0x4D414C20, /* 'MAL' (Malayalam (Traditional)) */
    LE_LANGUAGE_TAG_MAR = 0x4D415220, /* 'MAR' (Marathi) */
    LE_LANGUAGE_TAG_MLR = 0x4D4C5220, /* 'MLR' (Malayalam (Reformed)) */
    LE_LANGUAGE_TAG_MNI = 0x4D4E4920, /* 'MNI' (Manipuri) */
    LE_LANGUAGE_TAG_ORI = 0x4F524920, /* 'ORI' (Oriya) */
    LE_LANGUAGE_TAG_SAN = 0x53414E20, /* 'SAN' (Sanscrit) */
    LE_LANGUAGE_TAG_SND = 0x534E4420, /* 'SND' (Sindhi) */
    LE_LANGUAGE_TAG_SNH = 0x534E4820, /* 'SNH' (Sinhalese) */
    LE_LANGUAGE_TAG_SYR = 0x53595220, /* 'SYR' (Syriac) */
    LE_LANGUAGE_TAG_TAM = 0x54414D20, /* 'TAM' (Tamil) */
    LE_LANGUAGE_TAG_TEL = 0x54454C20, /* 'TEL' (Telugu) */
    LE_LANGUAGE_TAG_THA = 0x54484120, /* 'THA' (Thai) */
    LE_LANGUAGE_TAG_URD = 0x55524420, /* 'URD' (Urdu) */
    LE_LANGUAGE_TAG_ZHP = 0x5A485020, /* 'ZHP' (Chinese (Phonetic)) */
    LE_LANGUAGE_TAG_ZHS = 0x5A485320, /* 'ZHS' (Chinese (Simplified)) */
    LE_LANGUAGE_TAG_ZHT = 0x5A485420, /* 'ZHT' (Chinese (Traditional)) */
    LE_LANGUAGE_TAG_AFK = 0x41464B20, /* 'AFK' (Afrikaans) */
    LE_LANGUAGE_TAG_BEL = 0x42454C20, /* 'BEL' (Belarussian) */
    LE_LANGUAGE_TAG_BGR = 0x42475220, /* 'BGR' (Bulgarian) */
    LE_LANGUAGE_TAG_CAT = 0x43415420, /* 'CAT' (Catalan) */
    LE_LANGUAGE_TAG_CHE = 0x43484520, /* 'CHE' (Chechen) */
    LE_LANGUAGE_TAG_COP = 0x434F5020, /* 'COP' (Coptic) */
    LE_LANGUAGE_TAG_CSY = 0x43535920, /* 'CSY' (Czech) */
    LE_LANGUAGE_TAG_DAN = 0x44414E20, /* 'DAN' (Danish) */
    LE_LANGUAGE_TAG_DEU = 0x44455520, /* 'DEU' (German) */
    LE_LANGUAGE_TAG_DZN = 0x445A4E20, /* 'DZN' (Dzongkha) */
    LE_LANGUAGE_TAG_ELL = 0x454C4C20, /* 'ELL' (Greek) */
    LE_LANGUAGE_TAG_ENG = 0x454E4720, /* 'ENG' (English) */
    LE_LANGUAGE_TAG_ESP = 0x45535020, /* 'ESP' (Spanish) */
    LE_LANGUAGE_TAG_ETI = 0x45544920, /* 'ETI' (Estonian) */
    LE_LANGUAGE_TAG_EUQ = 0x45555120, /* 'EUQ' (Basque) */
    LE_LANGUAGE_TAG_FIN = 0x46494E20, /* 'FIN' (Finnish) */
    LE_LANGUAGE_TAG_FRA = 0x46524120, /* 'FRA' (French) */
    LE_LANGUAGE_TAG_GAE = 0x47414520, /* 'GAE' (Gaelic) */
    LE_LANGUAGE_TAG_HAU = 0x48415520, /* 'HAU' (Hausa) */
    LE_LANGUAGE_TAG_HRV = 0x48525620, /* 'HRV' (Croation) */
    LE_LANGUAGE_TAG_HUN = 0x48554E20, /* 'HUN' (Hungarian) */
    LE_LANGUAGE_TAG_HYE = 0x48594520, /* 'HYE' (Armenian) */
    LE_LANGUAGE_TAG_IND = 0x494E4420, /* 'IND' (Indonesian) */
    LE_LANGUAGE_TAG_ITA = 0x49544120, /* 'ITA' (Italian) */
    LE_LANGUAGE_TAG_KHM = 0x4B484D20, /* 'KHM' (Khmer) */
    LE_LANGUAGE_TAG_LAO = 0x4C414F20, /* 'LAO' (Lao) */
    LE_LANGUAGE_TAG_MNG = 0x4D4E4720, /* 'MNG' (Mongolian) */
    LE_LANGUAGE_TAG_MTS = 0x4D545320, /* 'MTS' (Maltese) */
    LE_LANGUAGE_TAG_NEP = 0x4E455020, /* 'NEP' (Nepali) */
    LE_LANGUAGE_TAG_NLD = 0x4E4C4420, /* 'NLD' (Dutch) */
    LE_LANGUAGE_TAG_PAS = 0x50415320, /* 'PAS' (Pashto) */
    LE_LANGUAGE_TAG_PLK = 0x504C4B20, /* 'PLK' (Polish) */
    LE_LANGUAGE_TAG_PTG = 0x50544720, /* 'PTG' (Portuguese) */
    LE_LANGUAGE_TAG_ROM = 0x524F4D20, /* 'ROM' (Romanian) */
    LE_LANGUAGE_TAG_RUS = 0x52555320, /* 'RUS' (Russian) */
    LE_LANGUAGE_TAG_SKY = 0x534B5920, /* 'SKY' (Slovak) */
    LE_LANGUAGE_TAG_SLV = 0x534C5620, /* 'SLV' (Slovenian) */
    LE_LANGUAGE_TAG_SQI = 0x53514920, /* 'SQI' (Albanian) */
    LE_LANGUAGE_TAG_SRB = 0x53524220, /* 'SRB' (Serbian) */
    LE_LANGUAGE_TAG_SVE = 0x53564520, /* 'SVE' (Swedish) */
    LE_LANGUAGE_TAG_TIB = 0x54494220, /* 'TIB' (Tibetan) */
    LE_LANGUAGE_TAG_TRK = 0x54524B20, /* 'TRK' (Turkish) */
    LE_LANGUAGE_TAG_UYG = 0x55594720, /* 'UYG' (Uyghur) */
    LE_LANGUAGE_TAG_WEL = 0x57454C20, /* 'WEL' (Welsh) */
    LE_LANGUAGE_TAG_NOR = 0x4E4F5220, /* 'NOR' (Norwegian) */
    LE_LANGUAGE_TAG_IRI = 0x49524920, /* 'IRI' (Irish) */
    LE_LANGUAGE_TAG_MRI = 0x4D524920, /* 'MRI' (Maori) */
    LE_LANGUAGE_TAG_ZHH = 0x5A484820, /* 'ZHH' (Cantonese) */
    LE_LANGUAGE_TAG_KUR = 0x4B555220, /* 'KUR' (Kurdish) */
    LE_LANGUAGE_TAG_PAN = 0x50414E20, /* 'PAN' (Punjabi) */
    LE_LANGUAGE_TAG_BRM = 0x42524D20 /* 'BRM' (Burmese) */
};
typedef U32 LE_LanguageTag_e;

enum
{
    LE_SCRIPT_TAG_NULL = 0x00000000, /* '' (NULL) */
    LE_SCRIPT_TAG_ZYYY = 0x7A797979, /* 'zyyy' (COMMON) */
    LE_SCRIPT_TAG_ZINH = 0x7A696E68, /* 'zinh' (INHERITED) */
    LE_SCRIPT_TAG_ARAB = 0x61726162, /* 'arab' (ARABIC) */
    LE_SCRIPT_TAG_ARMN = 0x61726D6E, /* 'armn' (ARMENIAN) */
    LE_SCRIPT_TAG_BENG = 0x62656E67, /* 'beng' (BENGALI) */
    LE_SCRIPT_TAG_BNG2 = 0x626E6732, /* 'bng2' (BENGALI v.2) (manually added) */
    LE_SCRIPT_TAG_BOPO = 0x626F706F, /* 'bopo' (BOPOMOFO) */
    LE_SCRIPT_TAG_CHER = 0x63686572, /* 'cher' (CHEROKEE) */
    LE_SCRIPT_TAG_COPT = 0x636F7074, /* 'copt' (COPTIC) */
    LE_SCRIPT_TAG_CYRL = 0x6379726C, /* 'cyrl' (CYRILLIC) */
    LE_SCRIPT_TAG_DSRT = 0x64737274, /* 'dsrt' (DESERET) */
    LE_SCRIPT_TAG_DEVA = 0x64657661, /* 'deva' (DEVANAGARI) */
    LE_SCRIPT_TAG_DEV2 = 0x64657632, /* 'dev2' (DEVANAGARI v.2) (manually added) */
    LE_SCRIPT_TAG_ETHI = 0x65746869, /* 'ethi' (ETHIOPIC) */
    LE_SCRIPT_TAG_GEOR = 0x67656F72, /* 'geor' (GEORGIAN) */
    LE_SCRIPT_TAG_GOTH = 0x676F7468, /* 'goth' (GOTHIC) */
    LE_SCRIPT_TAG_GREK = 0x6772656B, /* 'grek' (GREEK) */
    LE_SCRIPT_TAG_GUJR = 0x67756A72, /* 'gujr' (GUJARATI) */
    LE_SCRIPT_TAG_GJR2 = 0x676A7232, /* 'gjr2' (GUJARATI v.2) (manually added) */
    LE_SCRIPT_TAG_GURU = 0x67757275, /* 'guru' (GURMUKHI) */
    LE_SCRIPT_TAG_GUR2 = 0x67757232, /* 'gur2' (GURMUKHI v.2) (manually added) */
    LE_SCRIPT_TAG_HANI = 0x68616E69, /* 'hani' (HAN) */
    LE_SCRIPT_TAG_HANG = 0x68616E67, /* 'hang' (HANGUL) */
    LE_SCRIPT_TAG_HEBR = 0x68656272, /* 'hebr' (HEBREW) */
    LE_SCRIPT_TAG_HIRA = 0x68697261, /* 'hira' (HIRAGANA) */
    LE_SCRIPT_TAG_KNDA = 0x6B6E6461, /* 'knda' (KANNADA) */
    LE_SCRIPT_TAG_KND2 = 0x6B6E6432, /* 'knd2' (KANNADA v.2) (manually added) */
    LE_SCRIPT_TAG_KANA = 0x6B616E61, /* 'kana' (KATAKANA) */
    LE_SCRIPT_TAG_KHMR = 0x6B686D72, /* 'khmr' (KHMER) */
    LE_SCRIPT_TAG_LAOO = 0x6C616F20, /* 'lao ' (LAO) */
    LE_SCRIPT_TAG_LATN = 0x6C61746E, /* 'latn' (LATIN) */
    LE_SCRIPT_TAG_MLYM = 0x6D6C796D, /* 'mlym' (MALAYALAM) */
    LE_SCRIPT_TAG_MLM2 = 0x6D6C6D32, /* 'mlm2' (MALAYALAM v.2) (manually added) */
    LE_SCRIPT_TAG_MONG = 0x6D6F6E67, /* 'mong' (MONGOLIAN) */
    LE_SCRIPT_TAG_MYMR = 0x6D796D72, /* 'mymr' (MYANMAR) */
    LE_SCRIPT_TAG_MYM2 = 0x6D796D32, /* 'mym2' (MYANMAR) (now use this)*/
    LE_SCRIPT_TAG_OGAM = 0x6F67616D, /* 'ogam' (OGHAM) */
    LE_SCRIPT_TAG_ITAL = 0x6974616C, /* 'ital' (OLD_ITALIC) */
    LE_SCRIPT_TAG_ORYA = 0x6F727961, /* 'orya' (ORIYA) */
    LE_SCRIPT_TAG_ORY2 = 0x6F727932, /* 'ory2' (ORIYA v.2) (manually added) */
    LE_SCRIPT_TAG_RUNR = 0x72756E72, /* 'runr' (RUNIC) */
    LE_SCRIPT_TAG_SINH = 0x73696E68, /* 'sinh' (SINHALA) */
    LE_SCRIPT_TAG_SYRC = 0x73797263, /* 'syrc' (SYRIAC) */
    LE_SCRIPT_TAG_TAML = 0x74616D6C, /* 'taml' (TAMIL) */
    LE_SCRIPT_TAG_TML2 = 0x746D6C32, /* 'tml2' (TAMIL v.2) (manually added) */
    LE_SCRIPT_TAG_TELU = 0x74656C75, /* 'telu' (TELUGU) */
    LE_SCRIPT_TAG_TEL2 = 0x74656C32, /* 'tel2' (TELUGU v.2) (manually added) */
    LE_SCRIPT_TAG_THAA = 0x74686161, /* 'thaa' (THAANA) */
    LE_SCRIPT_TAG_THAI = 0x74686169, /* 'thai' (THAI) */
    LE_SCRIPT_TAG_TIBT = 0x74696274, /* 'tibt' (TIBETAN) */
    LE_SCRIPT_TAG_CANS = 0x63616E73, /* 'cans' (CANADIAN_ABORIGINAL) */
    LE_SCRIPT_TAG_YIII = 0x79692020, /* 'yi  ' (YI) */
    LE_SCRIPT_TAG_TGLG = 0x74676C67, /* 'tglg' (TAGALOG) */
    LE_SCRIPT_TAG_HANO = 0x68616E6F, /* 'hano' (HANUNOO) */
    LE_SCRIPT_TAG_BUHD = 0x62756864, /* 'buhd' (BUHID) */
    LE_SCRIPT_TAG_TAGB = 0x74616762, /* 'tagb' (TAGBANWA) */
    LE_SCRIPT_TAG_BRAI = 0x62726169, /* 'brai' (BRAILLE) */
    LE_SCRIPT_TAG_CPRT = 0x63707274, /* 'cprt' (CYPRIOT) */
    LE_SCRIPT_TAG_LIMB = 0x6C696D62, /* 'limb' (LIMBU) */
    LE_SCRIPT_TAG_LINB = 0x6C696E62, /* 'linb' (LINEAR_B) */
    LE_SCRIPT_TAG_OSMA = 0x6F736D61, /* 'osma' (OSMANYA) */
    LE_SCRIPT_TAG_SHAW = 0x73686177, /* 'shaw' (SHAVIAN) */
    LE_SCRIPT_TAG_TALE = 0x74616C65, /* 'tale' (TAI_LE) */
    LE_SCRIPT_TAG_UGAR = 0x75676172, /* 'ugar' (UGARITIC) */
    LE_SCRIPT_TAG_HRKT = 0x68726B74, /* 'hrkt' (KATAKANA_OR_HIRAGANA) */
    LE_SCRIPT_TAG_BUGI = 0x62756769, /* 'bugi' (BUGINESE) */
    LE_SCRIPT_TAG_GLAG = 0x676C6167, /* 'glag' (GLAGOLITIC) */
    LE_SCRIPT_TAG_KHAR = 0x6B686172, /* 'khar' (KHAROSHTHI) */
    LE_SCRIPT_TAG_SYLO = 0x73796C6F, /* 'sylo' (SYLOTI_NAGRI) */
    LE_SCRIPT_TAG_TALU = 0x74616C75, /* 'talu' (NEW_TAI_LUE) */
    LE_SCRIPT_TAG_TFNG = 0x74666E67, /* 'tfng' (TIFINAGH) */
    LE_SCRIPT_TAG_XPEO = 0x7870656F, /* 'xpeo' (OLD_PERSIAN) */
    LE_SCRIPT_TAG_BALI = 0x62616C69, /* 'bali' (BALINESE) */
    LE_SCRIPT_TAG_BATK = 0x6261746B, /* 'batk' (BATK) */
    LE_SCRIPT_TAG_BLIS = 0x626C6973, /* 'blis' (BLIS) */
    LE_SCRIPT_TAG_BRAH = 0x62726168, /* 'brah' (BRAH) */
    LE_SCRIPT_TAG_CHAM = 0x6368616D, /* 'cham' (CHAM) */
    LE_SCRIPT_TAG_CIRT = 0x63697274, /* 'cirt' (CIRT) */
    LE_SCRIPT_TAG_CYRS = 0x63797273, /* 'cyrs' (CYRS) */
    LE_SCRIPT_TAG_EGYD = 0x65677964, /* 'egyd' (EGYD) */
    LE_SCRIPT_TAG_EGYH = 0x65677968, /* 'egyh' (EGYH) */
    LE_SCRIPT_TAG_EGYP = 0x65677970, /* 'egyp' (EGYPTIAN_HIEROGLYPHS) */
    LE_SCRIPT_TAG_GEOK = 0x67656F6B, /* 'geok' (GEOK) */
    LE_SCRIPT_TAG_HANS = 0x68616E73, /* 'hans' (HANS) */
    LE_SCRIPT_TAG_HANT = 0x68616E74, /* 'hant' (HANT) */
    LE_SCRIPT_TAG_HMNG = 0x686D6E67, /* 'hmng' (HMNG) */
    LE_SCRIPT_TAG_HUNG = 0x68756E67, /* 'hung' (HUNG) */
    LE_SCRIPT_TAG_INDS = 0x696E6473, /* 'inds' (INDS) */
    LE_SCRIPT_TAG_JAVA = 0x6A617661, /* 'java' (JAVANESE) */
    LE_SCRIPT_TAG_KALI = 0x6B616C69, /* 'kali' (KAYAH_LI) */
    LE_SCRIPT_TAG_LATF = 0x6C617466, /* 'latf' (LATF) */
    LE_SCRIPT_TAG_LATG = 0x6C617467, /* 'latg' (LATG) */
    LE_SCRIPT_TAG_LEPC = 0x6C657063, /* 'lepc' (LEPCHA) */
    LE_SCRIPT_TAG_LINA = 0x6C696E61, /* 'lina' (LINA) */
    LE_SCRIPT_TAG_MAND = 0x6D616E64, /* 'mand' (MAND) */
    LE_SCRIPT_TAG_MAYA = 0x6D617961, /* 'maya' (MAYA) */
    LE_SCRIPT_TAG_MERO = 0x6D65726F, /* 'mero' (MERO) */
    LE_SCRIPT_TAG_NKOO = 0x6E6B6F20, /* 'nko ' (NKO) */
    LE_SCRIPT_TAG_ORKH = 0x6F726B68, /* 'orkh' (OLD_TURKIC) */
    LE_SCRIPT_TAG_PERM = 0x7065726D, /* 'perm' (PERM) */
    LE_SCRIPT_TAG_PHAG = 0x70686167, /* 'phag' (PHAGS_PA) */
    LE_SCRIPT_TAG_PHNX = 0x70686E78, /* 'phnx' (PHOENICIAN) */
    LE_SCRIPT_TAG_PLRD = 0x706C7264, /* 'plrd' (PLRD) */
    LE_SCRIPT_TAG_RORO = 0x726F726F, /* 'roro' (RORO) */
    LE_SCRIPT_TAG_SARA = 0x73617261, /* 'sara' (SARA) */
    LE_SCRIPT_TAG_SYRE = 0x73797265, /* 'syre' (SYRE) */
    LE_SCRIPT_TAG_SYRJ = 0x7379726A, /* 'syrj' (SYRJ) */
    LE_SCRIPT_TAG_SYRN = 0x7379726E, /* 'syrn' (SYRN) */
    LE_SCRIPT_TAG_TENG = 0x74656E67, /* 'teng' (TENG) */
    LE_SCRIPT_TAG_VAII = 0x76616920, /* 'vai ' (VAI) */
    LE_SCRIPT_TAG_VISP = 0x76697370, /* 'visp' (VISP) */
    LE_SCRIPT_TAG_XSUX = 0x78737578, /* 'xsux' (CUNEIFORM) */
    LE_SCRIPT_TAG_ZXXX = 0x7A787878, /* 'zxxx' (ZXXX) */
    LE_SCRIPT_TAG_ZZZZ = 0x7A7A7A7A, /* 'zzzz' (UNKNOWN) */
    LE_SCRIPT_TAG_CARI = 0x63617269, /* 'cari' (CARIAN) */
    LE_SCRIPT_TAG_JPAN = 0x6A70616E, /* 'jpan' (JPAN) */
    LE_SCRIPT_TAG_LANA = 0x6C616E61, /* 'lana' (TAI_THAM) */
    LE_SCRIPT_TAG_LYCI = 0x6C796369, /* 'lyci' (LYCIAN) */
    LE_SCRIPT_TAG_LYDI = 0x6C796469, /* 'lydi' (LYDIAN) */
    LE_SCRIPT_TAG_OLCK = 0x6F6C636B, /* 'olck' (OL_CHIKI) */
    LE_SCRIPT_TAG_RJNG = 0x726A6E67, /* 'rjng' (REJANG) */
    LE_SCRIPT_TAG_SAUR = 0x73617572, /* 'saur' (SAURASHTRA) */
    LE_SCRIPT_TAG_SGNW = 0x73676E77, /* 'sgnw' (SGNW) */
    LE_SCRIPT_TAG_SUND = 0x73756E64, /* 'sund' (SUNDANESE) */
    LE_SCRIPT_TAG_MOON = 0x6D6F6F6E, /* 'moon' (MOON) */
    LE_SCRIPT_TAG_MTEI = 0x6D746569, /* 'mtei' (MEETEI_MAYEK) */
    LE_SCRIPT_TAG_ARMI = 0x61726D69, /* 'armi' (IMPERIAL_ARAMAIC) */
    LE_SCRIPT_TAG_AVST = 0x61767374, /* 'avst' (AVESTAN) */
    LE_SCRIPT_TAG_CAKM = 0x63616B6D, /* 'cakm' (CAKM) */
    LE_SCRIPT_TAG_KORE = 0x6B6F7265, /* 'kore' (KORE) */
    LE_SCRIPT_TAG_KTHI = 0x6B746869, /* 'kthi' (KAITHI) */
    LE_SCRIPT_TAG_MANI = 0x6D616E69, /* 'mani' (MANI) */
    LE_SCRIPT_TAG_PHLI = 0x70686C69, /* 'phli' (INSCRIPTIONAL_PAHLAVI) */
    LE_SCRIPT_TAG_PHLP = 0x70686C70, /* 'phlp' (PHLP) */
    LE_SCRIPT_TAG_PHLV = 0x70686C76, /* 'phlv' (PHLV) */
    LE_SCRIPT_TAG_PRTI = 0x70727469, /* 'prti' (INSCRIPTIONAL_PARTHIAN) */
    LE_SCRIPT_TAG_SAMR = 0x73616D72, /* 'samr' (SAMARITAN) */
    LE_SCRIPT_TAG_TAVT = 0x74617674, /* 'tavt' (TAI_VIET) */
    LE_SCRIPT_TAG_ZMTH = 0x7A6D7468, /* 'zmth' (ZMTH) */
    LE_SCRIPT_TAG_ZSYM = 0x7A73796D, /* 'zsym' (ZSYM) */
    LE_SCRIPT_TAG_BAMU = 0x62616D75, /* 'bamu' (BAMUM) */
    LE_SCRIPT_TAG_LISU = 0x6C697375, /* 'lisu' (LISU) */
    LE_SCRIPT_TAG_NKGB = 0x6E6B6762, /* 'nkgb' (NKGB) */
    LE_SCRIPT_TAG_SARB = 0x73617262  /* 'sarb' (OLD_SOUTH_ARABIAN) */
};
typedef U32 LE_ScriptTag_e;

enum
{
    LE_FEATURE_TAG_NULL = 0x00000000, /* '' (NULL) */
    LE_FEATURE_TAG_AALT = 0x61616C74, /* 'aalt' */
    LE_FEATURE_TAG_ABVF = 0x61627666, /* 'abvf' */
    LE_FEATURE_TAG_ABVM = 0x6162766D, /* 'abvm' */
    LE_FEATURE_TAG_ABVS = 0x61627673, /* 'abvs' */
    LE_FEATURE_TAG_AFRC = 0x61667263, /* 'afrc' */
    LE_FEATURE_TAG_AKHN = 0x616B686E, /* 'akhn' */
    LE_FEATURE_TAG_BLWF = 0x626C7766, /* 'blwf' */
    LE_FEATURE_TAG_BLWM = 0x626C776D, /* 'blwm' */
    LE_FEATURE_TAG_BLWS = 0x626C7773, /* 'blws' */
    LE_FEATURE_TAG_CALT = 0x63616C74, /* 'calt' */
    LE_FEATURE_TAG_CASE = 0x63617365, /* 'case' */
    LE_FEATURE_TAG_CCMP = 0x63636D70, /* 'ccmp' */
    LE_FEATURE_TAG_CJCT = 0x636A6374, /* 'cjct' */
    LE_FEATURE_TAG_CLIG = 0x636C6967, /* 'clig' */
    LE_FEATURE_TAG_CPSP = 0x63707370, /* 'cpsp' */
    LE_FEATURE_TAG_CSWH = 0x63737768, /* 'cswh' */
    LE_FEATURE_TAG_CURS = 0x63757273, /* 'curs' */
    LE_FEATURE_TAG_C2SC = 0x63327363, /* 'c2sc' */
    LE_FEATURE_TAG_C2PC = 0x63327063, /* 'c2pc' */
    LE_FEATURE_TAG_DIST = 0x64697374, /* 'dist' */
    LE_FEATURE_TAG_DLIG = 0x646C6967, /* 'dlig' */
    LE_FEATURE_TAG_DNOM = 0x646E6F6D, /* 'dnom' */
    LE_FEATURE_TAG_EXPT = 0x65787074, /* 'expt' */
    LE_FEATURE_TAG_FALT = 0x66616C74, /* 'falt' */
    LE_FEATURE_TAG_FIN2 = 0x66696E32, /* 'fin2' */
    LE_FEATURE_TAG_FIN3 = 0x66696E33, /* 'fin3' */
    LE_FEATURE_TAG_FINA = 0x66696E61, /* 'fina' */
    LE_FEATURE_TAG_FRAC = 0x66726163, /* 'frac' */
    LE_FEATURE_TAG_FWID = 0x66776964, /* 'fwid' */
    LE_FEATURE_TAG_HALF = 0x68616C66, /* 'half' */
    LE_FEATURE_TAG_HALN = 0x68616C6E, /* 'haln' */
    LE_FEATURE_TAG_HALT = 0x68616C74, /* 'halt' */
    LE_FEATURE_TAG_HIST = 0x68697374, /* 'hist' */
    LE_FEATURE_TAG_HKNA = 0x686B6E61, /* 'hkna' */
    LE_FEATURE_TAG_HLIG = 0x686C6967, /* 'hlig' */
    LE_FEATURE_TAG_HNGL = 0x686E676C, /* 'hngl' */
    LE_FEATURE_TAG_HWID = 0x68776964, /* 'hwid' */
    LE_FEATURE_TAG_INIT = 0x696E6974, /* 'init' */
    LE_FEATURE_TAG_ISOL = 0x69736F6C, /* 'isol' */
    LE_FEATURE_TAG_ITAL = 0x6974616C, /* 'ital' */
    LE_FEATURE_TAG_JALT = 0x6A616C74, /* 'jalt' */
    LE_FEATURE_TAG_JP78 = 0x6A703738, /* 'jp78' */
    LE_FEATURE_TAG_JP83 = 0x6A703833, /* 'jp83' */
    LE_FEATURE_TAG_JP90 = 0x6A703930, /* 'jp90' */
    LE_FEATURE_TAG_KERN = 0x6B65726E, /* 'kern' */
    LE_FEATURE_TAG_LFBD = 0x6C666264, /* 'lfbd' */
    LE_FEATURE_TAG_LIGA = 0x6C696761, /* 'liga' */
    LE_FEATURE_TAG_LJMO = 0x6C6A6D6F, /* 'ljmo' */
    LE_FEATURE_TAG_LNUM = 0x6C6E756D, /* 'lnum' */
    LE_FEATURE_TAG_LOCL = 0x6C6F636C, /* 'locl' */
    LE_FEATURE_TAG_MARK = 0x6D61726B, /* 'mark' */
    LE_FEATURE_TAG_MED2 = 0x6D656432, /* 'med2' */
    LE_FEATURE_TAG_MEDI = 0x6D656469, /* 'medi' */
    LE_FEATURE_TAG_MGRK = 0x6D67726B, /* 'mgrk' */
    LE_FEATURE_TAG_MKMK = 0x6D6B6D6B, /* 'mkmk' */
    LE_FEATURE_TAG_MSET = 0x6D736574, /* 'mset' */
    LE_FEATURE_TAG_NALT = 0x6E616C74, /* 'nalt' */
    LE_FEATURE_TAG_NLCK = 0x6E6C636B, /* 'nlck' */
    LE_FEATURE_TAG_NUKT = 0x6E756B74, /* 'nukt' */
    LE_FEATURE_TAG_NUMR = 0x6E756D72, /* 'numr' */
    LE_FEATURE_TAG_ONUM = 0x6F6E756D, /* 'onum' */
    LE_FEATURE_TAG_OPBD = 0x6F706264, /* 'opbd' */
    LE_FEATURE_TAG_ORDN = 0x6F72646E, /* 'ordn' */
    LE_FEATURE_TAG_ORNM = 0x6F726E6D, /* 'ornm' */
    LE_FEATURE_TAG_PALT = 0x70616C74, /* 'palt' */
    LE_FEATURE_TAG_PCAP = 0x70636170, /* 'pcap' */
    LE_FEATURE_TAG_PNUM = 0x706E756D, /* 'pnum' */
    LE_FEATURE_TAG_PREF = 0x70726566, /* 'pref' */
    LE_FEATURE_TAG_PRES = 0x70726573, /* 'pres' */
    LE_FEATURE_TAG_PSTF = 0x70737466, /* 'pstf' */
    LE_FEATURE_TAG_PSTS = 0x70737473, /* 'psts' */
    LE_FEATURE_TAG_PWID = 0x70776964, /* 'pwid' */
    LE_FEATURE_TAG_QWID = 0x71776964, /* 'qwid' */
    LE_FEATURE_TAG_RAND = 0x72616E64, /* 'rand' */
    LE_FEATURE_TAG_RLIG = 0x726C6967, /* 'rlig' */
    LE_FEATURE_TAG_RPHF = 0x72706866, /* 'rphf' */
    LE_FEATURE_TAG_RKRF = 0x726B7266, /* 'rkrf' */
    LE_FEATURE_TAG_RTBD = 0x72746264, /* 'rtbd' */
    LE_FEATURE_TAG_RTLA = 0x72746C61, /* 'rtla' */
    LE_FEATURE_TAG_RUBY = 0x72756279, /* 'ruby' */
    LE_FEATURE_TAG_SALT = 0x73616C74, /* 'salt' */
    LE_FEATURE_TAG_SINF = 0x73696E66, /* 'sinf' */
    LE_FEATURE_TAG_SIZE = 0x73697A65, /* 'size' */
    LE_FEATURE_TAG_SMCP = 0x736D6370, /* 'smcp' */
    LE_FEATURE_TAG_SMPL = 0x736D706C, /* 'smpl' */
    LE_FEATURE_TAG_SS01 = 0x73733031, /* 'ss01' */
    LE_FEATURE_TAG_SS02 = 0x73733032, /* 'ss02' */
    LE_FEATURE_TAG_SS03 = 0x73733033, /* 'ss03' */
    LE_FEATURE_TAG_SS04 = 0x73733034, /* 'ss04' */
    LE_FEATURE_TAG_SS05 = 0x73733035, /* 'ss05' */
    LE_FEATURE_TAG_SS06 = 0x73733036, /* 'ss06' */
    LE_FEATURE_TAG_SS07 = 0x73733037, /* 'ss07' */
    LE_FEATURE_TAG_SS08 = 0x73733038, /* 'ss08' */
    LE_FEATURE_TAG_SS09 = 0x73733039, /* 'ss09' */
    LE_FEATURE_TAG_SS10 = 0x73733130, /* 'ss10' */
    LE_FEATURE_TAG_SS11 = 0x73733131, /* 'ss11' */
    LE_FEATURE_TAG_SS12 = 0x73733132, /* 'ss12' */
    LE_FEATURE_TAG_SS13 = 0x73733133, /* 'ss13' */
    LE_FEATURE_TAG_SS14 = 0x73733134, /* 'ss14' */
    LE_FEATURE_TAG_SS15 = 0x73733135, /* 'ss15' */
    LE_FEATURE_TAG_SS16 = 0x73733136, /* 'ss16' */
    LE_FEATURE_TAG_SS17 = 0x73733137, /* 'ss17' */
    LE_FEATURE_TAG_SS18 = 0x73733138, /* 'ss18' */
    LE_FEATURE_TAG_SS19 = 0x73733139, /* 'ss19' */
    LE_FEATURE_TAG_SS20 = 0x73733230, /* 'ss20' */
    LE_FEATURE_TAG_SUBS = 0x73756273, /* 'subs' */
    LE_FEATURE_TAG_SUPS = 0x73757073, /* 'sups' */
    LE_FEATURE_TAG_SWSH = 0x73777368, /* 'swsh' */
    LE_FEATURE_TAG_TITL = 0x7469746C, /* 'titl' */
    LE_FEATURE_TAG_TJMO = 0x746A6D6F, /* 'tjmo' */
    LE_FEATURE_TAG_TNAM = 0x746E616D, /* 'tnam' */
    LE_FEATURE_TAG_TNUM = 0x746E756D, /* 'tnum' */
    LE_FEATURE_TAG_TRAD = 0x74726164, /* 'trad' */
    LE_FEATURE_TAG_TWID = 0x74776964, /* 'twid' */
    LE_FEATURE_TAG_UNIC = 0x756E6963, /* 'unic' */
    LE_FEATURE_TAG_VALT = 0x76616C74, /* 'valt' */
    LE_FEATURE_TAG_VATU = 0x76617475, /* 'vatu' */
    LE_FEATURE_TAG_VERT = 0x76657274, /* 'vert' */
    LE_FEATURE_TAG_VHAL = 0x7668616C, /* 'vhal' */
    LE_FEATURE_TAG_VJMO = 0x766A6D6F, /* 'vjmo' */
    LE_FEATURE_TAG_VKNA = 0x766B6E61, /* 'vkna' */
    LE_FEATURE_TAG_VKRN = 0x766B726E, /* 'vkrn' */
    LE_FEATURE_TAG_VPAL = 0x7670616C, /* 'vpal' */
    LE_FEATURE_TAG_VRT2 = 0x76727432, /* 'vrt2' */
    LE_FEATURE_TAG_ZERO = 0x7A65726F  /* 'zero' */
};
typedef U32 LE_FeatureTag_e;

enum
{
    LE_TABLEE_TAG_NULL = 0x00000000, /* '' (NULL) */
    LE_TABLE_TAG_ACNT = 0x61636E74, /* 'acnt' */
    LE_TABLE_TAG_AVAR = 0x61766172, /* 'avar' */
    LE_TABLE_TAG_BASE = 0x42415345, /* 'BASE' */
    LE_TABLE_TAG_BDAT = 0x62646174, /* 'bdat' */
    LE_TABLE_TAG_BHED = 0x62686564, /* 'bhed' */
    LE_TABLE_TAG_BLOC = 0x626C6F63, /* 'bloc' */
    LE_TABLE_TAG_BSLN = 0x62736C6E, /* 'bsln' */
    LE_TABLE_TAG_CFF  = 0x43464620, /* 'CFF ' */
    LE_TABLE_TAG_CMAP = 0x636D6170, /* 'cmap' */
    LE_TABLE_TAG_CVAR = 0x63766172, /* 'cvar' */
    LE_TABLE_TAG_CVT  = 0x63767420, /* 'cvt ' */
    LE_TABLE_TAG_DSIG = 0x44534947, /* 'DSIG' */
    LE_TABLE_TAG_EBDT = 0x45424454, /* 'EBDT' */
    LE_TABLE_TAG_EBLC = 0x45424C43, /* 'EBLC' */
    LE_TABLE_TAG_EBSC = 0x45425343, /* 'EBSC' */
    LE_TABLE_TAG_FDSC = 0x66647363, /* 'fdsc' */
    LE_TABLE_TAG_FEAT = 0x66656174, /* 'feat' */
    LE_TABLE_TAG_FMTX = 0x666D7478, /* 'fmtx' */
    LE_TABLE_TAG_FPGM = 0x6670676D, /* 'fpgm' */
    LE_TABLE_TAG_FVAR = 0x66766172, /* 'fvar' */
    LE_TABLE_TAG_GASP = 0x67617370, /* 'gasp' */
    LE_TABLE_TAG_GDEF = 0x47444546, /* 'GDEF' */
    LE_TABLE_TAG_GLYF = 0x676C7966, /* 'glyf' */
    LE_TABLE_TAG_GPOS = 0x47504F53, /* 'GPOS' */
    LE_TABLE_TAG_GSUB = 0x47535542, /* 'GSUB' */
    LE_TABLE_TAG_GVAR = 0x67766172, /* 'gvar' */
    LE_TABLE_TAG_HDMX = 0x68646D78, /* 'hdmx' */
    LE_TABLE_TAG_HEAD = 0x68656164, /* 'head' */
    LE_TABLE_TAG_HHEA = 0x68686561, /* 'hhea' */
    LE_TABLE_TAG_HMTX = 0x686D7478, /* 'hmtx' */
    LE_TABLE_TAG_HSTY = 0x68737479, /* 'hsty' */
    LE_TABLE_TAG_JUST = 0x6A757374, /* 'just' */
    LE_TABLE_TAG_JSTF = 0x4A535446, /* 'JSTF' */
    LE_TABLE_TAG_KERN = 0x6B65726E, /* 'kern' */
    LE_TABLE_TAG_LCAR = 0x6C636172, /* 'lcar' */
    LE_TABLE_TAG_LOCA = 0x6C6F6361, /* 'loca' */
    LE_TABLE_TAG_LTSH = 0x4C545348, /* 'LTSH' */
    LE_TABLE_TAG_MAXP = 0x6D617870, /* 'maxp' */
    LE_TABLE_TAG_MORT = 0x6D6F7274, /* 'mort' */
    LE_TABLE_TAG_MORX = 0x6D6F7278, /* 'morx' */
    LE_TABLE_TAG_NAME = 0x6E616D65, /* 'name' */
    LE_TABLE_TAG_OPBD = 0x6F706264, /* 'opbd' */
    LE_TABLE_TAG_OS_2 = 0x4F532F32, /* 'OS/2' */
    LE_TABLE_TAG_PCLT = 0x50434C54, /* 'PCLT' */
    LE_TABLE_TAG_POST = 0x706F7374, /* 'post' */
    LE_TABLE_TAG_PREP = 0x70726570, /* 'prep' */
    LE_TABLE_TAG_PROP = 0x70726F70, /* 'prop' */
    LE_TABLE_TAG_TRAK = 0x7472616B, /* 'trak' */
    LE_TABLE_TAG_VDMX = 0x56444D58, /* 'VDMX' */
    LE_TABLE_TAG_VHEA = 0x76686561, /* 'vhea' */
    LE_TABLE_TAG_VMTX = 0x766D7478, /* 'vmtx' */
    LE_TABLE_TAG_VORG = 0x564F5247, /* 'VORG' */
    LE_TABLE_TAG_ZAPF = 0x5A617066  /* 'Zapf' */
};
typedef U32 LE_TableTag_e;

typedef enum
{
    LE_CLASS_DEF_NO        = 0,
    LE_CLASS_DEF_SIMPLE    = 1,
    LE_CLASS_DEF_LIGATURE  = 2,
    LE_CLASS_DEF_MARK      = 3,
    LE_CLASS_DEF_COMPONENT = 4
} LE_ClassDefinitionType_e;

enum
{
    LE_VECTOR_TYPE_TTF = 0,
    LE_VECTOR_TYPE_OTF = 1,
};
typedef U8 LE_VectorType_e;

typedef struct
{
    LE_VectorType_e eType;
    U16 u16OutBufferSize;
    U32 *pau32OutGlyph;
    U16 *pau16Sequence;
    U16 *pau16ComposedSize;
    U16 u16OutLen;
    U16 u16Consumed;
    U16 u16Produced;
    U16 u16OffsetInOutput;
    U16 u16OffsetInConposed;
} LE_ProcessSubstHeader_t;

typedef struct
{
    LE_VectorType_e eType;
    U32 *pau32InGlyph;
    U16 u16InLen;
    U16 u16BaseOffset;
    U16 u16NextOffset;
} LE_ProcessPosHeader_t;


#define LE_GLYPH_ID_MASK 0x0000FFFF
#define LE_GLYPH_FEATURE_MASK 0xFFFF0000

enum
{
    LE_CHAR_FEATURE_NONE = 0x0000,
    LE_CHAR_FEATURE_BLWF = 0x0001,
    LE_CHAR_FEATURE_RPHF = 0x0002,
    LE_CHAR_FEATURE_PSTF = 0x0004,
    LE_CHAR_FEATURE_HALN = 0x0008,
    LE_CHAR_FEATURE_ABVS = 0x0010,
    LE_CHAR_FEATURE_NO_HALF = 0x0020
};
typedef U16 LE_CharFeatures_e;

typedef U32 LeGlyphId;

#define LE_GET_GLYPH_ID(_gid) ((U16)(_gid & LE_GLYPH_ID_MASK))
#define LE_GET_GLYPH_FEATURE(_gid) ((U16)((_gid & LE_GLYPH_FEATURE_MASK) >> 16))

#define LE_SET_GLYPH_ID(_gid, _g) ((U32)((_gid & LE_GLYPH_FEATURE_MASK) | ((U32)(_g) & LE_GLYPH_ID_MASK)))
#define LE_SET_GLYPH_FEATURE(_gid, _f) ((U32)(_gid | ((U32)(_f) << 16)))

#endif //__FEATURE_VECTOR_FONT__

#endif //__MSAPI_MSTAR_LE_TYPES_H__
