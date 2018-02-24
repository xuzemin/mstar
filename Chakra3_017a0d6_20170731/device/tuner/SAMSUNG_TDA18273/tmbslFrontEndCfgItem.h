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
/**
  Copyright (C) 2007 NXP B.V.), All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslFrontEndCfgItem.h
 *                %version: CFR_STB#0.12 %
 *
 * \date          %date_modified%
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *
 * Detailled description may be added here.
 *
 * \section info Change Information
 *
 * \verbatim
   Date          Modified by CRPRNr  TASKNr  Maintenance description
   -------------|-----------|-------|-------|-----------------------------------
   <28-Jan-2005>
   \endverbatim
 *
*/

/*
#ifndef TMBSLFRONTENDCFGITEM_H
#define TMBSLFRONTENDCFGITEM_H
*/
/*============================================================================*/
/*                       INCLUDE FILES                                        */
/*============================================================================*/


#ifdef __cplusplus
extern "C" {
#endif



/*============================================================================*/
/*                       MACRO DEFINITION                                     */
/*============================================================================*/
#if !defined(TMBSLFRONTEND_CFG_ITEM_MAKE)
#define TMBSLFRONTEND_CFG_ITEM_MAKE(item)  tmbslFrontEnd##item
#endif
    
/*============================================================================*/
/*                       ENUM OR TYPE DEFINITION                              */
/*============================================================================*/

/******************************************************************************/
/** \brief "This enum are used to choose a configuration item in set/get config bsl"
 *
 *  \sa    "bsl 'cfg' functions"
 *
 ******************************************************************************/
typedef enum {
    /** Board Id */
    TMBSLFRONTEND_CFG_ITEM_MAKE(Board) = 0,
    TMBSLFRONTEND_CFG_ITEM_MAKE(Standard),
    TMBSLFRONTEND_CFG_ITEM_MAKE(LPSel) = 6,
    TMBSLFRONTEND_CFG_ITEM_MAKE(Init) = 100,
    TMBSLFRONTEND_CFG_ITEM_MAKE(I2cSwitch),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CheckIdentity),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadSync),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadIQ),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadAgc),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadTVBER),       /* = 106 - BSD*/
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadTCPTU),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadTMCC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCBER),		/* = 109 - DVB-T*/
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadConfidence),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadRepImpul),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadRepFreq),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCellId),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadDspVersion),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CarrierHigh),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CarrierLow),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CarrierStep),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CarrierCurrent),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StartIQ),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StopIQ),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StartRepImpul),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StopRepImpul),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadACI),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCCI),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadLEE),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCRC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadMSE),			/* = 127 - DVB-C*/
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCOEF),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StartEqual),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StopEqual),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DspCrcVersionOK),    /* return true if OK */
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadRSSI) = 138,		/*138*/
    TMBSLFRONTEND_CFG_ITEM_MAKE(RFTone),	
    TMBSLFRONTEND_CFG_ITEM_MAKE(RFToneIndex),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ToneSearchState),
    TMBSLFRONTEND_CFG_ITEM_MAKE(NbOfUnit) = 200,
    TMBSLFRONTEND_CFG_ITEM_MAKE(OutOfGIEcho),			/*DVB_T*/
    TMBSLFRONTEND_CFG_ITEM_MAKE(DSPDownload),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DSPloadFromHost),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DSPloadFromEEPROM),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Enable4k),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ModePer),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GiveConfigToTuner),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ConfigAttenuator),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCBusEnable),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCExt),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCGainIndex),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCGainValue),
    TMBSLFRONTEND_CFG_ITEM_MAKE(LOFreqIndex),
    TMBSLFRONTEND_CFG_ITEM_MAKE(LOFreqValue),
    TMBSLFRONTEND_CFG_ITEM_MAKE(XtalMode),
    TMBSLFRONTEND_CFG_ITEM_MAKE(EnableLNA),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CutOffIndex),
    TMBSLFRONTEND_CFG_ITEM_MAKE(TunerBandwidth) = 300,
    TMBSLFRONTEND_CFG_ITEM_MAKE(TunerLevel),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Band),
    TMBSLFRONTEND_CFG_ITEM_MAKE(RF),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ID),
    TMBSLFRONTEND_CFG_ITEM_MAKE(POR),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadFEL),
    TMBSLFRONTEND_CFG_ITEM_MAKE(FCC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Temp),
    TMBSLFRONTEND_CFG_ITEM_MAKE(RFAGC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(IFAGC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCandTemp),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PowerState),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Sensibility),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCarrier),
    TMBSLFRONTEND_CFG_ITEM_MAKE(BandAuto) = 330,
    TMBSLFRONTEND_CFG_ITEM_MAKE(ManualBandWidth),

    TMBSLFRONTEND_CFG_ITEM_MAKE(RFCALOK) = 355,
    TMBSLFRONTEND_CFG_ITEM_MAKE(IRCALOK),
    
    
    TMBSLFRONTEND_CFG_ITEM_MAKE(IFLevel) = 362,


    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadInit) = 372,
    TMBSLFRONTEND_CFG_ITEM_MAKE(StatusByte) = 380,
    
    TMBSLFRONTEND_CFG_ITEM_MAKE(StandardMode) = 400,
    TMBSLFRONTEND_CFG_ITEM_MAKE(Sound),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DemodStatus),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadAFC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadHlock),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadVlock),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadDIFAGC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadTIFAGC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SetFI),
    
    TMBSLFRONTEND_CFG_ITEM_MAKE(DemodAdd) = 500,
    TMBSLFRONTEND_CFG_ITEM_MAKE(DemodFct),
    TMBSLFRONTEND_CFG_ITEM_MAKE(MapNb),         /* for 8275AHN), 8274AHN  */
    TMBSLFRONTEND_CFG_ITEM_MAKE(MapIndex),
    TMBSLFRONTEND_CFG_ITEM_MAKE(MapFreq),
    TMBSLFRONTEND_CFG_ITEM_MAKE(MapParam),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ATC),                /* used by TD1316 */
    TMBSLFRONTEND_CFG_ITEM_MAKE(TOP),                /* used by TD1316 */
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadID),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Xtall),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PLLMFactor),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PLLNFactor),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PLLPFactor),
    TMBSLFRONTEND_CFG_ITEM_MAKE(BERDepth),
    TMBSLFRONTEND_CFG_ITEM_MAKE(IQSwapped),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ExtOffset),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Offset125K),
    TMBSLFRONTEND_CFG_ITEM_MAKE(IF),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ProtocolStep),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Watchdog),
    TMBSLFRONTEND_CFG_ITEM_MAKE(NbRetry),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PulseKiller),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Xtall100PPM),
    TMBSLFRONTEND_CFG_ITEM_MAKE(UseAGCTun),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCPolaTun),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCPolaIF),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCTunMax),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCTunMin),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCIFMax),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCIFMin),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out1POClk),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out1ParaSer),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out1SLSB),        /* MSBLSB), configure in serial mode if  MSB or LSB first */
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out1TSMode),      /* Transport stream mode A), B), C... */ 
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out1ParaDiv),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out2POClk),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out2ParaSer),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out2SLSB),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out2TSMODE),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Out2ParaDiv),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SRMax),          /* Sat SR config */
    TMBSLFRONTEND_CFG_ITEM_MAKE(SRMin),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SRMaxMargin),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SRMinMargin),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SearchRange),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PolaAGC),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DeltaThreshold),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ZIFTuner),
    TMBSLFRONTEND_CFG_ITEM_MAKE(FC),                /* tmbsl8262 */
    TMBSLFRONTEND_CFG_ITEM_MAKE(BBGain),
    TMBSLFRONTEND_CFG_ITEM_MAKE(RFATT),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PDPLL),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PDZIF),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PDLoopT),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PDRSSI),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PDLNA),
    TMBSLFRONTEND_CFG_ITEM_MAKE(RefDivider),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CalManual),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CPCurSel),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CPHigh),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Port1),
    TMBSLFRONTEND_CFG_ITEM_MAKE(FSampling),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DVBMCNS),       /* TDA10023 */
    TMBSLFRONTEND_CFG_ITEM_MAKE(AGCThreshold),
    TMBSLFRONTEND_CFG_ITEM_MAKE(EqualType),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PolaPWM1),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PolaPWM2),
    TMBSLFRONTEND_CFG_ITEM_MAKE(BERWindow),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ClkOffsetRange),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SWDyn),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SWStep),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SWLength),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SWPos),
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMMode),
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMReQTS),
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMReQON),
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMGetReg5),
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMGetTSStatus),
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMGetRCVStatus),    
    TMBSLFRONTEND_CFG_ITEM_MAKE(JQAMGetTSON),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CPump),          /* Cdm1316 */
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioInOut0),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioInOut1),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioValue1),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioInOut2),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioValue2),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioInOut3),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioValue3),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SetAntennaPower) = 600,     /* Control GPIO1 in open-drain for Vestel application */
    TMBSLFRONTEND_CFG_ITEM_MAKE(ZapMode) = 601,
    TMBSLFRONTEND_CFG_ITEM_MAKE(ChannelInfo),
    TMBSLFRONTEND_CFG_ITEM_MAKE(TimeErr),
    TMBSLFRONTEND_CFG_ITEM_MAKE(FreqErr),
    TMBSLFRONTEND_CFG_ITEM_MAKE(EnableI2cSwitch),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadFreqFilter),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadChannelType),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCCIDetection),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadDopplerDetection),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCumulatedHS),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadACIDetection),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadPKUse),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadIIRTimeInter),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadEchoType),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadChangeDetect),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadNBPath),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadChannelLength),
    TMBSLFRONTEND_CFG_ITEM_MAKE(EnableIQDetect),
    TMBSLFRONTEND_CFG_ITEM_MAKE(IFTuner) = 619,
    TMBSLFRONTEND_CFG_ITEM_MAKE(IFDemod),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DemodReadFct),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AutoOffsetLock),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PLLStep),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ManualBandwidth),
    TMBSLFRONTEND_CFG_ITEM_MAKE(IsMK3),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DiversitySetMaster),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DiversitySetBridge),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DiversitySetSlave),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ICMode)  = 631,
    TMBSLFRONTEND_CFG_ITEM_MAKE(Enable8295Equal) = 633,
    TMBSLFRONTEND_CFG_ITEM_MAKE(CustomGDCoeff),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CustomCVBSCoeff),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CustomCVBSLevel),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GDEqSect1),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GDEqSect2),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GDEqSect3),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GDEqSect4),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqCoeff0),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqCoeff1),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqCoeff2),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqCoeff3),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqCoeff4),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqCoeff5),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CVBSEqLevel),
    TMBSLFRONTEND_CFG_ITEM_MAKE(StandardCoeff),
    TMBSLFRONTEND_CFG_ITEM_MAKE(LNA1Gain),
    TMBSLFRONTEND_CFG_ITEM_MAKE(LNA2Gain),
    TMBSLFRONTEND_CFG_ITEM_MAKE(MixerGain),
    TMBSLFRONTEND_CFG_ITEM_MAKE(IFGain),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SAClkOutputMode),
    TMBSLFRONTEND_CFG_ITEM_MAKE(BAND),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SpectralInversion),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CBERDepth),
    TMBSLFRONTEND_CFG_ITEM_MAKE(VBERReset),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CBERReset),
    TMBSLFRONTEND_CFG_ITEM_MAKE(PioValue0),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Gpio0Cfg),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Gpio2Cfg),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Gpio0Select),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ITSel),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DeltaSigma0Value),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GpioPolarity),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SetGPI0Analog),
    TMBSLFRONTEND_CFG_ITEM_MAKE(AgcTreshold),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SendI2cStop),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ResetPK),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Spectrum),
    TMBSLFRONTEND_CFG_ITEM_MAKE(DspStop),
    TMBSLFRONTEND_CFG_ITEM_MAKE(WriteFwCode),
    TMBSLFRONTEND_CFG_ITEM_MAKE(WriteFwData),
    TMBSLFRONTEND_CFG_ITEM_MAKE(GiveCfgToTuner),
    TMBSLFRONTEND_CFG_ITEM_MAKE(EEPROMReadFct),
    TMBSLFRONTEND_CFG_ITEM_MAKE(EEPROMWriteFct),
    TMBSLFRONTEND_CFG_ITEM_MAKE(NbSample2Lock),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CarrierSearching),
    TMBSLFRONTEND_CFG_ITEM_MAKE(CARCONF),
    TMBSLFRONTEND_CFG_ITEM_MAKE(Scanning),
    TMBSLFRONTEND_CFG_ITEM_MAKE(SYNCREG),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentFreq),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentBW),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentFFT),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentGI),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentSI),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentHPLP),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentHRCH),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentMOD),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentVRHP),
    TMBSLFRONTEND_CFG_ITEM_MAKE(ReadCurrentVRLP)
} TMBSLFRONTEND_CFG_ITEM_MAKE(Config_t);

#define tmhalRFCALOK TMBSLFRONTEND_CFG_ITEM_MAKE(RFCALOK)
#define tmhalIRCALOK TMBSLFRONTEND_CFG_ITEM_MAKE(IRCALOK)
#define tmhalFELOCK  TMBSLFRONTEND_CFG_ITEM_MAKE(ReadFEL)

#ifdef __cplusplus
}
#endif

//#endif /* TMBSLFRONTENDCFGITEM_H */

/*============================================================================*/
/*                            END OF FILE                                     */
/*============================================================================*/

