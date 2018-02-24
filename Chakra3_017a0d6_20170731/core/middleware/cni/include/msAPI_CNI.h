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
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
/// @file  msApi_CNI.h
/// @brief Interface for CNI database
/// @author MStar Semiconductor Inc.
////////////////////////////////////////////////////////////////////////////////


#ifndef __MSAPI_CNI_H
#define __MSAPI_CNI_H

// CNI Lib v3.0 (549 Channels)

#ifdef __cplusplus
  extern "C" {
#endif

// StationId can be used to find out the station information from tStationTbl[]
// The order must equal to tStationTbl[]
typedef enum _EnuStationId
{
/*1  */  STATION_101TV,
/*2  */  STATION_105TV,
/*3  */  STATION_123TV,
/*4  */  STATION_1AFER,
/*5  */  STATION_1P1,
/*6  */  STATION_1TV,
/*7  */  STATION_24HOR,
/*8  */  STATION_3PLUS,
/*9  */  STATION_3SAT,
/*10 */  STATION_40LAT,
/*11 */  STATION_7GOLDT,
/*12 */  STATION_7GSR,
/*13 */  STATION_8TV,
/*14 */  STATION_A1,
/*15 */  STATION_AB1,
/*16 */  STATION_AB3,
/*17 */  STATION_AB4E,
/*18 */  STATION_ABCH,
/*19 */  STATION_ACHT,
/*20 */  STATION_ALICE,
/*21 */  STATION_ANGLIA,
/*22 */  STATION_ANIMA,
/*23 */  STATION_ANIMP,
/*24 */  STATION_ANIPL,
/*25 */  STATION_ANTEC,
/*26 */  STATION_ANTENA,
/*27 */  STATION_AQUIT,
/*28 */  STATION_ARD,
/*29 */  STATION_ARTE,
/*30 */  STATION_ATV,
/*31 */  STATION_ATVP,
/*32 */  STATION_AVRAS,
/*33 */  STATION_AVSE,
/*34 */  STATION_B1,
/*35 */  STATION_BARRA,
/*36 */  STATION_BASTV,
/*37 */  STATION_BBC1,
/*38 */  STATION_BBC1NI,
/*39 */  STATION_BBC1SCO,
/*40 */  STATION_BBC1WAL,
/*41 */  STATION_BBC2,
/*42 */  STATION_BBC2NI,
/*43 */  STATION_BBC2SCO,
/*44 */  STATION_BBC2WAL,
/*45 */  STATION_BBCN,
/*46 */  STATION_BBCP,
/*47 */  STATION_BBCW,
/*48 */  STATION_BE,
/*49 */  STATION_BLN1,
/*50 */  STATION_BLN2,
/*51 */  STATION_BOING,
/*52 */  STATION_BOK,
/*53 */  STATION_BOORG,
/*54 */  STATION_BORDER,
/*55 */  STATION_BR,
/*56 */  STATION_BR1,
/*57 */  STATION_BR3,
/*58 */  STATION_BRABN,
/*59 */  STATION_BRALP,
/*60 */  STATION_BRAVO,
/*61 */  STATION_BRESC,
/*62 */  STATION_BRUG,
/*63 */  STATION_BST24,
/*64 */  STATION_C_PLUS,
/*65 */  STATION_C33,
/*66 */  STATION_CAMERAD,
/*67 */  STATION_CAN5,
/*68 */  STATION_CANA9,
/*69 */  STATION_CANAC,
/*70 */  STATION_CANAJ,
/*71 */  STATION_CANAJIM,
/*72 */  STATION_CANAL,
/*73 */  STATION_CANALEX,
/*74 */  STATION_CANV,
/*75 */  STATION_CANZO,
/*76 */  STATION_CANZR,
/*77 */  STATION_CARLTON,
/*78 */  STATION_CARLTSE,
/*79 */  STATION_CARNK,
/*80 */  STATION_CARNP,
/*81 */  STATION_CARTO,
/*82 */  STATION_CCV,
/*83 */  STATION_CENTRAL,
/*84 */  STATION_CH4,
/*85 */  STATION_CH5,
/*86 */  STATION_CHANNEL,
/*87 */  STATION_CHDCH,
/*88 */  STATION_CINE5,
/*89 */  STATION_CLATV,
/*90 */  STATION_CLUBR,
/*91 */  STATION_CNBCE,
/*92 */  STATION_CNN,
/*93 */  STATION_COMED,
/*94 */  STATION_CONSUM,
/*95 */  STATION_CT1,
/*96 */  STATION_CT2,
/*97 */  STATION_CT24,
/*98 */  STATION_CT4,
/*99 */  STATION_CUATR,
/*100*/  STATION_CULTU24,
/*101*/  STATION_CYL7,
/*102*/  STATION_CYL8,
/*103*/  STATION_DISC1,
/*104*/  STATION_DISCOVE,
/*105*/  STATION_DISNC,
/*106*/  STATION_DISNEY,
/*107*/  STATION_DMAX,
/*108*/  STATION_DR1,
/*109*/  STATION_DR2,
/*110*/  STATION_DSF,
/*111*/  STATION_DUNA,
/*112*/  STATION_DVIER,
/*113*/  STATION_DWFB,
/*114*/  STATION_EDC2,
/*115*/  STATION_EDC3,
/*116*/  STATION_EET,
/*117*/  STATION_EKOTV,
/*118*/  STATION_ESPAN,
/*119*/  STATION_ESPCS,
/*120*/  STATION_ET1,
/*121*/  STATION_ET3,
/*122*/  STATION_ETB1,
/*123*/  STATION_ETB2,
/*124*/  STATION_EURNW,
/*125*/  STATION_EUROD,
/*126*/  STATION_EURSP,
/*127*/  STATION_EUSP2,
/*128*/  STATION_EUSPN,
/*129*/  STATION_EXQI,
/*130*/  STATION_EXTRA,
/*131*/  STATION_EXTREMA,
/*132*/  STATION_FAMIL,
/*133*/  STATION_FAMILY,
/*134*/  STATION_FESTI,
/*135*/  STATION_FILFR,
/*136*/  STATION_FOCTV,
/*137*/  STATION_FOX,
/*138*/  STATION_FOXKD,
/*139*/  STATION_FOXKI,
/*140*/  STATION_FOXLF,
/*141*/  STATION_FR2,
/*142*/  STATION_FR3,
/*143*/  STATION_FR5,
/*144*/  STATION_FUNTV,
/*145*/  STATION_GALA,
/*146*/  STATION_GALAS,
/*147*/  STATION_GAYTV,
/*148*/  STATION_GELRE,
/*149*/  STATION_GESCH,
/*150*/  STATION_GMTV,
/*151*/  STATION_GPTV,
/*152*/  STATION_GRAAF,
/*153*/  STATION_GRAMPIA,
/*154*/  STATION_GRANADA,
/*155*/  STATION_GRANAPL,
/*156*/  STATION_GRANATI,
/*157*/  STATION_GTV,
/*158*/  STATION_GXT,
/*159*/  STATION_HETG,
/*160*/  STATION_HISC1,
/*161*/  STATION_HISCH,
/*162*/  STATION_HOLLN,
/*163*/  STATION_HR,
/*164*/  STATION_HR1,
/*165*/  STATION_HR3,
/*166*/  STATION_HRT,
/*167*/  STATION_HSE,
/*168*/  STATION_HTV,
/*169*/  STATION_HUMOR,
/*170*/  STATION_ICTV,
/*171*/  STATION_INFOK,
/*172*/  STATION_INFOT,
/*173*/  STATION_INTTV,
/*174*/  STATION_IRIS,
/*175*/  STATION_ITA1,
/*176*/  STATION_ITA8,
/*177*/  STATION_ITALI,
/*178*/  STATION_ITV,
/*179*/  STATION_JIMMY,
/*180*/  STATION_JIMTV,
/*181*/  STATION_JOURNA,
/*182*/  STATION_KABEL,
/*183*/  STATION_KANA2,
/*184*/  STATION_KANA3,
/*185*/  STATION_KANALA,
/*186*/  STATION_KANL5,
/*187*/  STATION_KANL6,
/*188*/  STATION_KANLD,
/*189*/  STATION_KANLRI,
/*190*/  STATION_KANZL,
/*191*/  STATION_KAPIT,
/*192*/  STATION_KC,
/*193*/  STATION_KDGIN,
/*194*/  STATION_KIKA,
/*195*/  STATION_L1,
/*196*/  STATION_LA7,
/*197*/  STATION_LACHM,
/*198*/  STATION_LAOTR,
/*199*/  STATION_LASEX,
/*200*/  STATION_LCI,
/*201*/  STATION_LEACH,
/*202*/  STATION_LEOND,
/*203*/  STATION_LIBER,
/*204*/  STATION_LIFE,
/*205*/  STATION_LIVE,
/*206*/  STATION_LWT,
/*207*/  STATION_M1,
/*208*/  STATION_M6,
/*209*/  STATION_MACPL,
/*210*/  STATION_MATMU,
/*211*/  STATION_MAXIM,
/*212*/  STATION_MCM,
/*213*/  STATION_MCMB,
/*214*/  STATION_MDR,
/*215*/  STATION_MDR1,
/*216*/  STATION_MDR3,
/*217*/  STATION_MDRD,
/*218*/  STATION_MEDPR,
/*219*/  STATION_MEDSH,
/*220*/  STATION_MERIDIA,
/*221*/  STATION_MOVCH,
/*222*/  STATION_MOZAI,
/*223*/  STATION_MTV,
/*224*/  STATION_MTV1,
/*225*/  STATION_MTV2,
/*226*/  STATION_MTVB,
/*227*/  STATION_MTVH,
/*228*/  STATION_MTVI,
/*229*/  STATION_MTVNL,
/*230*/  STATION_MTVSW,
/*231*/  STATION_MUBOX,
/*232*/  STATION_MUXX,
/*233*/  STATION_N_TV,
/*234*/  STATION_N24,
/*235*/  STATION_N3,
/*236*/  STATION_NBCEU,
/*237*/  STATION_NDR,
/*238*/  STATION_NDR1,
/*239*/  STATION_NDR3,
/*240*/  STATION_NED1,
/*241*/  STATION_NED2,
/*242*/  STATION_NED3,
/*243*/  STATION_NEOX,
/*244*/  STATION_NET,
/*245*/  STATION_NET2,
/*246*/  STATION_NET5,
/*247*/  STATION_NGC,
/*248*/  STATION_NGP1,
/*249*/  STATION_NICK,
/*250*/  STATION_NICK1,
/*251*/  STATION_NICKE,
/*252*/  STATION_NICKS,
/*253*/  STATION_NICKU,
/*254*/  STATION_NICKV,
/*255*/  STATION_NICLD,
/*256*/  STATION_NIT,
/*257*/  STATION_NOTLE,
/*258*/  STATION_NOVA,
/*259*/  STATION_NOVAC,
/*260*/  STATION_NOVAT,
/*261*/  STATION_NOVYK,
/*262*/  STATION_NPO,
/*263*/  STATION_NRK1,
/*264*/  STATION_NRK2,
/*265*/  STATION_NUVLI,
/*266*/  STATION_NUVR,
/*267*/  STATION_OCKO,
/*268*/  STATION_OK54BT,
/*269*/  STATION_OKTO,
/*270*/  STATION_OMROP,
/*271*/  STATION_ONYX,
/*272*/  STATION_ORB,
/*273*/  STATION_ORB1,
/*274*/  STATION_ORB3,
/*275*/  STATION_ORF1,
/*276*/  STATION_ORF2,
/*277*/  STATION_ORF3,
/*278*/  STATION_ORFSP,
/*279*/  STATION_OTV,
/*280*/  STATION_OWL3,
/*281*/  STATION_PARIP,
/*282*/  STATION_PARLAME,
/*283*/  STATION_PCCU,
/*284*/  STATION_PEOTV,
/*285*/  STATION_PHOEN,
/*286*/  STATION_PLAHD,
/*287*/  STATION_PLALI,
/*288*/  STATION_PLANE,
/*289*/  STATION_PLANT,
/*290*/  STATION_PLAYH,
/*291*/  STATION_PLAYT,
/*292*/  STATION_PLUGT,
/*293*/  STATION_POLIT,
/*294*/  STATION_POPTV,
/*295*/  STATION_PREMIER,
/*296*/  STATION_PRIMA,
/*297*/  STATION_PRIME,
/*298*/  STATION_PRITV,
/*299*/  STATION_PRO7,
/*300*/  STATION_PUNT2,
/*301*/  STATION_QOOB,
/*302*/  STATION_QVC,
/*303*/  STATION_R8VGA,
/*304*/  STATION_RACCH,
/*305*/  STATION_RADCV,
/*306*/  STATION_RADIT,
/*307*/  STATION_RADTE,
/*308*/  STATION_RAI,
/*309*/  STATION_RAI1,
/*310*/  STATION_RAI2,
/*311*/  STATION_RAI3,
/*312*/  STATION_RAISA,
/*313*/  STATION_RB,
/*314*/  STATION_RB1,
/*315*/  STATION_RB3,
/*316*/  STATION_REGIO22,
/*317*/  STATION_RETE4,
/*318*/  STATION_RETE7,
/*319*/  STATION_RETEA,
/*320*/  STATION_RFO1,
/*321*/  STATION_RFO2,
/*322*/  STATION_RIKIS,
/*323*/  STATION_RINTV,
/*324*/  STATION_RITV,
/*325*/  STATION_RNEWS,
/*326*/  STATION_RNN7,
/*327*/  STATION_ROBTV,
/*328*/  STATION_RTBF1,
/*329*/  STATION_RTBF2,
/*330*/  STATION_RTBFS,
/*331*/  STATION_RTCTL,
/*332*/  STATION_RTE1,
/*333*/  STATION_RTL,
/*334*/  STATION_RTL2,
/*335*/  STATION_RTL4,
/*336*/  STATION_RTL5,
/*337*/  STATION_RTL7,
/*338*/  STATION_RTL8,
/*339*/  STATION_RTLC,
/*340*/  STATION_RTLL,
/*341*/  STATION_RTLP,
/*342*/  STATION_RTLSH,
/*343*/  STATION_RTLT,
/*344*/  STATION_RTLTL,
/*345*/  STATION_RTP1,
/*346*/  STATION_RTP2,
/*347*/  STATION_RTPAF,
/*348*/  STATION_RTPAZ,
/*349*/  STATION_RTPI,
/*350*/  STATION_RTPM,
/*351*/  STATION_RTV,
/*352*/  STATION_RTV38,
/*353*/  STATION_RTVR,
/*354*/  STATION_S4C,
/*355*/  STATION_SA2000,
/*356*/  STATION_SAILC,
/*357*/  STATION_SAT1,
/*358*/  STATION_SATAS,
/*359*/  STATION_SBS6,
/*360*/  STATION_SCHAF,
/*361*/  STATION_SCIFC,
/*362*/  STATION_SCIFI,
/*363*/  STATION_SCLUB,
/*364*/  STATION_SCOTV,
/*365*/  STATION_SENATO,
/*366*/  STATION_SF_INFO,
/*367*/  STATION_SF1,
/*368*/  STATION_SF2,
/*369*/  STATION_SFB,
/*370*/  STATION_SFB1,
/*371*/  STATION_SHOW,
/*372*/  STATION_SHOWE,
/*373*/  STATION_SITCO,
/*374*/  STATION_SK224,
/*375*/  STATION_SKYC,
/*376*/  STATION_SKYCA,
/*377*/  STATION_SKYCI,
/*378*/  STATION_SKYCM,
/*379*/  STATION_SKYDG,
/*380*/  STATION_SKYGOLD,
/*381*/  STATION_SKYME,
/*382*/  STATION_SKYMP,
/*383*/  STATION_SKYNEWS,
/*384*/  STATION_SKYONE,
/*385*/  STATION_SKYS,
/*386*/  STATION_SKYSOAP,
/*387*/  STATION_SKYSP,
/*388*/  STATION_SKYSP2,
/*389*/  STATION_SKYSP3,
/*390*/  STATION_SKYTRAV,
/*391*/  STATION_SKYTV,
/*392*/  STATION_SKYTW,
/*393*/  STATION_SLO,
/*394*/  STATION_SMTS,
/*395*/  STATION_SPIRTIT,
/*396*/  STATION_SPITL,
/*397*/  STATION_SPORZ,
/*398*/  STATION_SR,
/*399*/  STATION_SR1,
/*400*/  STATION_SRGS,
/*401*/  STATION_SRTL,
/*402*/  STATION_SSF,
/*403*/  STATION_SSVC,
/*404*/  STATION_STAR,
/*405*/  STATION_STAR4,
/*406*/  STATION_STAR5,
/*407*/  STATION_STAR6,
/*408*/  STATION_STAR7,
/*409*/  STATION_STAR8,
/*410*/  STATION_STARM,
/*411*/  STATION_STELE,
/*412*/  STATION_STERRE,
/*413*/  STATION_STUD1,
/*414*/  STATION_STUUV,
/*415*/  STATION_STV1,
/*416*/  STATION_STV2,
/*417*/  STATION_STV3,
/*418*/  STATION_STV4,
/*419*/  STATION_SUPCH,
/*420*/  STATION_SUPSP,
/*421*/  STATION_SVT1,
/*422*/  STATION_SVT2,
/*423*/  STATION_SVTEST,
/*424*/  STATION_SWR1,
/*425*/  STATION_SWRBW,
/*426*/  STATION_SWRMA,
/*427*/  STATION_SWRREG,
/*428*/  STATION_SWRRHPF,
/*429*/  STATION_SWRRP,
/*430*/  STATION_SWRSAAR,
/*431*/  STATION_TBOX,
/*432*/  STATION_TCM,
/*433*/  STATION_TCST,
/*434*/  STATION_TEBRU,
/*435*/  STATION_TEING,
/*436*/  STATION_TELCE,
/*437*/  STATION_TELE1,
/*438*/  STATION_TELE3,
/*439*/  STATION_TELE5,
/*440*/  STATION_TELEB,
/*441*/  STATION_TELEC,
/*442*/  STATION_TELED,
/*443*/  STATION_TELEG,
/*444*/  STATION_TELEL,
/*445*/  STATION_TELEM,
/*446*/  STATION_TELEN,
/*447*/  STATION_TELER,
/*448*/  STATION_TELES,
/*449*/  STATION_TELEZ,
/*450*/  STATION_TELL,
/*451*/  STATION_TELSA,
/*452*/  STATION_TELST,
/*453*/  STATION_TELVE,
/*454*/  STATION_TELZI,
/*455*/  STATION_TEMB,
/*456*/  STATION_TEMPO,
/*457*/  STATION_TEOP,
/*458*/  STATION_TESAM,
/*459*/  STATION_TETI,
/*460*/  STATION_TEVA,
/*461*/  STATION_TF1,
/*462*/  STATION_TGNOR,
/*463*/  STATION_TGRT,
/*464*/  STATION_TIEN,
/*465*/  STATION_TLM,
/*466*/  STATION_TLT,
/*467*/  STATION_TMCMC,
/*468*/  STATION_TMF,
/*469*/  STATION_TMSAT,
/*470*/  STATION_TNTC,
/*471*/  STATION_TNTEL,
/*472*/  STATION_TONDS,
/*473*/  STATION_TOON,
/*474*/  STATION_TP9TE,
/*475*/  STATION_TRSTV,
/*476*/  STATION_TRT_1,
/*477*/  STATION_TRT_2,
/*478*/  STATION_TRT_3,
/*479*/  STATION_TRT_4,
/*480*/  STATION_TRT_I,
/*481*/  STATION_TSI1,
/*482*/  STATION_TSI2,
/*483*/  STATION_TSR1,
/*484*/  STATION_TSR2,
/*485*/  STATION_TV1,
/*486*/  STATION_TV2,
/*487*/  STATION_TV2_,
/*488*/  STATION_TV2__,
/*489*/  STATION_TV2_Z,
/*490*/  STATION_TV3,
/*491*/  STATION_TV4,
/*492*/  STATION_TV5,
/*493*/  STATION_TVB,
/*494*/  STATION_TVBRN,
/*495*/  STATION_TVBRU,
/*496*/  STATION_TVC,
/*497*/  STATION_TVCOM,
/*498*/  STATION_TVDAN,
/*499*/  STATION_TVE1,
/*500*/  STATION_TVE2,
/*501*/  STATION_TVEIE,
/*502*/  STATION_TVHK,
/*503*/  STATION_TVJ,
/*504*/  STATION_TVJOJ,
/*505*/  STATION_TVL,
/*506*/  STATION_TVLIM,
/*507*/  STATION_TVLUX,
/*508*/  STATION_TVN,
/*509*/  STATION_TVNOR,
/*510*/  STATION_TVNOV,
/*511*/  STATION_TVOS,
/*512*/  STATION_TVP,
/*513*/  STATION_TVP1,
/*514*/  STATION_TVP2,
/*515*/  STATION_TVPAR,
/*516*/  STATION_TVPPL,
/*517*/  STATION_TVPR,
/*518*/  STATION_TVSIB,
/*519*/  STATION_TVSO,
/*520*/  STATION_TW1,
/*521*/  STATION_TYNE,
/*522*/  STATION_U1,
/*523*/  STATION_UKGLD,
/*524*/  STATION_UKLIV,
/*525*/  STATION_ULSTER,
/*526*/  STATION_UTU,
/*527*/  STATION_V8,
/*528*/  STATION_VDOIT,
/*529*/  STATION_VDOLI,
/*530*/  STATION_VH1,
/*531*/  STATION_VIDSC,
/*532*/  STATION_VIJFT,
/*533*/  STATION_VITAY,
/*534*/  STATION_VIVA,
/*535*/  STATION_VOX,
/*536*/  STATION_VT4,
/*537*/  STATION_VTM,
/*538*/  STATION_VTVV,
/*539*/  STATION_WDR1,
/*540*/  STATION_WDR3,
/*541*/  STATION_WDRL,
/*542*/  STATION_WESTCOU,
/*543*/  STATION_WIRTV,
/*544*/  STATION_WTV,
/*545*/  STATION_YLE1,
/*546*/  STATION_YLE2,
/*547*/  STATION_YORKSHI,
/*548*/  STATION_Z1,
/*549*/  STATION_ZDF,

         STATION_NUM,
         STATION_NONE = 0xFFFF
} EnuStationId;

typedef enum _EnuCountryLanguageId
{
    COUNTRYID_AUSTRIA,      // 奧地利
    COUNTRYID_GERMANY,      // 德國
    COUNTRYID_SWITZERLAND,  // 瑞士
    COUNTRYID_BELGIUM,      // 比利時
    COUNTRYID_NETHERLANDS,  // 荷蘭
    COUNTRYID_UK,           // 英國
    COUNTRYID_IRELAND,      // 愛爾蘭
    COUNTRYID_DENMARK,      // 丹麥
    COUNTRYID_FINLAND,      // 芬蘭
    COUNTRYID_ITALY,        // 義大利
    COUNTRYID_NORWAY,       // 挪威
    COUNTRYID_SPAIN,        // 西班牙
    COUNTRYID_SWEDEN,       // 瑞典
    COUNTRYID_LUXEMBURG,    // 盧森堡
    COUNTRYID_FRANCE,       // 法國
    COUNTRYID_CZECH,        // 捷克
    COUNTRYID_POLAND,       // 波蘭
    COUNTRYID_HUNGARY,      // 匈牙利
    COUNTRYID_NUM,

    COUNTRYID_SWI1_GERMAN = 0,  // 瑞士, 德語區
    COUNTRYID_SWI2_FRENCH = 1,  // 瑞士, 法語區
    COUNTRYID_SWI3_ITALIAN = 2, // 瑞士, 義語區
    COUNTRYID_BEL1_FRENCH = 0,  // 比利時, 法語區
    COUNTRYID_BEL2_DUTCH = 1    // 比利時, 荷語區
} EnuCountryLanguageId;

// compare CNI status
#define CNI_OTHER_COUNTRY   0x80
#define CNI_NOT_FOUND       0xff
#define CNI_NULL            0xfefe

// Use VPS CNI code or 8/30/format 1 CNI code to find out the station.
// Return value: the priority of the station
//   1 - 0x7f: local country station
//   CNI_OTHER_COUNTRY  : Other country station
//   CNI_NOT_FOUND      : Can't find the station
// If we can find the station, store the station id in the "pStationId"
void msAPI_CNI_SetCountryLangId( unsigned char ucCountryId, unsigned char ucLanguageId);
unsigned char msAPI_CNI_FindStationInfo( unsigned short wVPSCode, unsigned short wF1Code, unsigned short wF2Code, unsigned short* pStationId, unsigned short* pcStationIdList );
void msAPI_CNI_GetStationName( unsigned short wStationId, unsigned char *sStationName );

unsigned char msAPI_CNI_LibVersionCheck(void);

extern unsigned char g_ucCountryId;
extern unsigned char g_ucLanguageId;

#ifdef __cplusplus
  }
#endif

#endif
