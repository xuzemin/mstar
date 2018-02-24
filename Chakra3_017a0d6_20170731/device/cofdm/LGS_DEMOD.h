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
/***************************************************************************************
*
*                           (c) Copyright 2008, LegendSilicon, beijing, China
*
*                                        All Rights Reserved
*
* Description :
*
* Notice:
*
***************************************************************************************/

#ifndef _LGS_DEMOD_C631FEF2_89A8_4ae5_B22A_04122BA8B12D_H_
#define _LGS_DEMOD_C631FEF2_89A8_4ae5_B22A_04122BA8B12D_H_


#ifdef __cplusplus
extern "C" {
#endif


//#include "memory.h"
#include "LGS_TYPES.h"


////////////////////////////////////////////////////////////////////////////////
/// \brief Data structure of LGS_GetParameters() and LGS_SetParameters()
///
////////////////////////////////////////////////////////////////////////////////
#if((FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD))
typedef struct _st_DEMOD_CONFIG
{
	UINT8	GuardIntvl;							/// Guard interval	0-420, 1-595, 2-945
	UINT8	SubCarrier;						/// Sub carrier		0-4QAM, 1-4QAM_NR, 2-16QAM, 3-32QAM, 4-64QAM
	UINT8	FecRate;							/// FEC			0-0.4, 1-0.6, 2-0.8
	UINT8	TimeDeintvl;						/// TIM			0-240, 1-720
	UINT8	PnNumber;						/// PN Sequence Phase	0-VPN, 1-CPN
	UINT8	CarrierMode;						/// Carrier mode	0-MC, 1-SC
	UINT8	IsMpegClockInvert;			/// MPEG Clock		0-normal, 1-inverted
	UINT8	AdType;								/// AD type		0-internal AD, 1-external AD
	UINT32	BCHCount;							/// BCH Count (read only)
	UINT32	BCHPktErrCount;				/// BCH Packet Error Count (read only)
	UINT32	AFCPhase;							/// AFC Phase value (read only)
	UINT32	AFCPhaseInit;						/// Initial AFC Phase value

	UINT8	GuardIntvl2;							/// Guard interval	0-420, 1-595, 2-945
	UINT8	SubCarrier2;						/// Sub carrier		0-4QAM, 1-4QAM_NR, 2-16QAM, 3-32QAM, 4-64QAM
	UINT8	FecRate2;							/// FEC			0-0.4, 1-0.6, 2-0.8
	UINT8	TimeDeintvl2;						/// TIM			0-240, 1-720
	UINT8	PnNumber2;						/// PN Sequence Phase	0-VPN, 1-CPN
	UINT8	CarrierMode2;						/// Carrier mode	0-MC, 1-SC
	UINT8	IsMpegClockInvert2;			/// MPEG Clock		0-normal, 1-inverted
	UINT8	AdType2;								/// AD type		0-internal AD, 1-external AD
	UINT32	BCHCount2;							/// BCH Count (read only)
	UINT32	BCHPktErrCount2;				/// BCH Packet Error Count (read only)
	UINT32	AFCPhase2;							/// AFC Phase value (read only)
	UINT32	AFCPhaseInit2;						/// Initial AFC Phase value
} DemodConfig;
typedef enum 
{
    DEMOD_WORK_MODE_ANT1_DTMB = 0,
    DEMOD_WORK_MODE_ANT2_DTMB,
    DEMOD_WORK_MODE_ANT1_DVBC,
    DEMOD_WORK_MODE_ANT2_DVBC,
    DEMOD_WORK_MODE_SUPERTV,
    DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC,
    DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB,
    DEMOD_WORK_MODE_INVALID
} DEMOD_WORK_MODE;
typedef enum
{
	TS_Output_Parallel = 0,
	TS_Output_Serial,
	TS_Output_PIP_DTMBTsParallel_DVBCSerial,
	TS_Output_PIP_DTMBTsSerial_DVBCSerial,
	TS_Output_PIP_DVBCTsParallel_DTMBSerial,
	TS_Output_PIP_DVBCTsSerial_DTMBSerial,
	TS_Output_INVALID
} TSOutputType;
typedef enum 
{
	QAM4 = 0,
	QAM16,
    QAM32,
    QAM64,
    QAM128,
    QAM256,
    QAM_INVALID
} DVBC_QAM;
typedef struct _st_DEMOD_INIT_PARA
{
	DEMOD_WORK_MODE	workMode;
	TSOutputType	tsOutputType;
	DVBC_QAM		dvbcQam;
	double			IF;				//Mhz
	double			dvbcSymbolRate;	//Mhz
	UINT8			dvbcIFPolarity; //0: Positive;  1: Negative;  2: Unknown (Autodetect IFPolarity);
	UINT8			dtmbIFSelect;	//0: Tuner is high IF;  1: Tuner is low IF
} DemodInitPara;
#endif

#if((FRONTEND_DEMOD_TYPE != LEGEND_9x_DEMOD))
typedef struct _st_DEMOD_PARAMETERS
{
	UINT8	GuardIntvl;		/// Guard interval	0-420, 1-595, 2-945
	UINT8	SubCarrier;		/// Sub carrier		0-4QAM, 1-4QAM_NR, 2-16QAM, 3-32QAM, 4-64QAM
	UINT8	FecRate;		/// FEC			0-0.4, 1-0.6, 2-0.8
	UINT8	TimeDeintvl;		/// TIM			0-240, 1-720
	UINT8	PnNumber;		/// PN Sequence Phase	0-VPN, 1-CPN
	UINT8	AdcClock;		///
	UINT8	CarrierMode;		/// Carrier mode	0-MC, 1-SC
	UINT8	TsOutputSel;		/// TS outputSel	0-SPI, 1-USB, 2-SDI
	UINT8	IsMpegClkFree;		/// MPEG_CLK		0-MPEG_CLK is internally gated by MPEG_VALID, 1-free running
	UINT8	IsMpegClockInvert;	/// MPEG Clock		0-normal, 1-inverted
	UINT8	IsMpeg2DataOutputSerial;/// MCLKPOL		0-parallel, 1-serial
	UINT8	AdType;			/// AD type		0-internal AD, 1-external AD
	UINT8	XOFrequency;		/// 			0-60.8MHz, 1-30.4MHz
	UINT8	AgcGain;		/// AGC GAIN(only for ADI Tuner)	0-do nothing, 1-set AGC GAIN
	UINT8	AgcOutputVoltage;	/// AGC Output Voltage			0-1.8v, 1-2.5v, 2-3.3v
	UINT8	AntennaMode;		/// Antenna Mode			0-mode0, 1-mode1, 2-mode2, 3-mode3
	UINT32	BCHCount;		/// BCH Count (read only)
	UINT32	BCHPktErrCount;		/// BCH Packet Error Count (read only)
	UINT32	AFCPhase;		/// AFC Phase value (read only)
	UINT32	AFCPhaseInit;		/// Initial AFC Phase value
	UINT8	PnAutoOn;		/// PN auto mode	0-Off, 1-On
	UINT8	SelfReset;		/// Self Reset		0-disable self-reset, 1-Enable self-reset
} DemodParameters;
#endif

#define PARA_IGNORE	0xFF

/// Initialize all members of DemodParameters to PARA_IGNORE
#if (FRONTEND_DEMOD_TYPE == LEGEND_9x_DEMOD)
#define DemodParaIgnoreAll(_x_)		memset( _x_, PARA_IGNORE, sizeof(DemodConfig) )
#else
#define DemodParaIgnoreAll(_x_)		memset( _x_, PARA_IGNORE, sizeof(DemodParameters) )
#endif

/// GuardIntvl index value
#define PARA_GI_420	0
#define PARA_GI_595	1
#define PARA_GI_945	2

/// PN Sequence Phase index value
#define PARA_PN_VPN	0
#define PARA_PN_CPN	1

/// Carrier mode index value
#define PARA_CARRIER_MC		0
#define PARA_CARRIER_SC		1


////////////////////////////////////////////////////////////////
// Register interface prototype
////////////////////////////////////////////////////////////////
void LGS_DemodRegisterRegisterAccess(LGS_REGISTER_READ pread,
				LGS_REGISTER_WRITE pwrite,
				LGS_REGISTER_READ_MULTIBYTE preadm,
				LGS_REGISTER_WRITE_MULTIBYTE pwritem);

void LGS_DemodRegisterWait(LGS_WAIT wait);


#ifdef __cplusplus
}
#endif


#endif
