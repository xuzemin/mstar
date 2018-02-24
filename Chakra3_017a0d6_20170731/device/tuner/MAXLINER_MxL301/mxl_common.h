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
/*******************************************************************************
 *
 * FILE NAME          : MxL_Common.h
 * 
 * AUTHOR             : hchan
 * DATE CREATED       : Nov. 9, 2009
 *
 * DESCRIPTION        : MxL Common Header file
 *
 *******************************************************************************
 *                Copyright (c) 2009, MaxLinear, Inc.
 ******************************************************************************/
 
#ifndef __MxL_COMMON_H
#define __MxL_COMMON_H



/******************************************************************************
*						User-Defined Types (Typedefs)
******************************************************************************/


/****************************************************************************
*       Imports and definitions for WIN32                             
****************************************************************************/
/*#include <windows.h> */
/*
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
*/
typedef char           SINT8;
typedef short          SINT16;
typedef int            SINT32;
typedef float          REAL32;

/****************************************************************************\
*      Imports and definitions for non WIN32 platforms                   *
\****************************************************************************/
/*
typedef unsigned char  UINT8;
typedef unsigned short UINT16;
typedef unsigned int   UINT32;
typedef char           SINT8;
typedef short          SINT16;
typedef int            SINT32;
typedef float          REAL32;

// create a boolean  
#ifndef __boolean__
#define __boolean__
typedef enum {FALSE=0,TRUE} BOOL;
#endif 
*/


/****************************************************************************\
*          Definitions for all platforms					                 *
\****************************************************************************/
#ifndef NULL
#define NULL (void*)0
#endif



/******************************/
/*	MxL Err message  	  */
/******************************/
typedef enum{
	MxL_OK				=   0,
	MxL_ERR_INIT		=   1,
	MxL_ERR_RFTUNE		=   2,
	MxL_ERR_SET_REG		=   3,
	MxL_ERR_GET_REG		=	4,
	MxL_ERR_OTHERS		=   10,
	MxL_GET_ID_FAIL		= 0xFF
}MxL_ERR_MSG;

/******************************/
/*	MxLF Chip verstion     */
/******************************/
typedef enum{
	MxL_UNKNOWN_ID		= 0x00,
	MxL_30xRF_V8		= 0x08,
	MxL_30xRF_V9		= 0x09
}MxLxxxRF_ChipVersion;


/******************************************************************************
    CONSTANTS
******************************************************************************/

#ifndef MHz
	#define MHz 1000000
#endif

#define MAX_ARRAY_SIZE 100


/* Enumeration of Tuner Types supported */
typedef enum
{
	MxL_TunerID_MxL202RF = 0,
	MxL_TunerID_MxL301RF = 1,
	MxL_TunerID_MxL302RF = 2
} MxLxxxRF_TunerID;

typedef enum
{
	MxL_I2C_ADDR_96 = 96 ,
	MxL_I2C_ADDR_97 = 97 ,
	MxL_I2C_ADDR_98 = 98 ,
	MxL_I2C_ADDR_99 = 99 	
} MxLxxxRF_I2CAddr ;

/* Enumeration of Mode */
typedef enum 
{
	MxL_MODE_DVBT = 1,
	MxL_MODE_ATSC = 2,
	MxL_MODE_CAB_STD = 0x10,
	MxL_MODE_ANA_MN = 0x20, 
	MxL_MODE_ANA_BG = 0x21,
	MxL_MODE_ANA_I  = 0x22,
	MxL_MODE_ANA_DKL = 0x23,
	MxL_MODE_ANA_SECAM = 0x24,
	MxL_MODE_ANA_SECAM_ACC = 0x25
} MxLxxxRF_Mode ;

typedef enum
{
	MxL_IF_4_MHZ	  = 4000000,
	MxL_IF_4_5_MHZ	  = 4500000,
	MxL_IF_4_57_MHZ	  =	4570000,
	MxL_IF_5_MHZ	  =	5000000,
	MxL_IF_5_38_MHZ	  =	5380000,
	MxL_IF_6_MHZ	  =	6000000,
	MxL_IF_6_28_MHZ	  =	6280000,
	MxL_IF_7_2_MHZ    = 7200000,
	MxL_IF_8_25_MHZ	  = 8250000,
	MxL_IF_35_25_MHZ  = 35250000,
	MxL_IF_36_MHZ	  = 36000000,
	MxL_IF_36_15_MHZ  = 36150000,
	MxL_IF_36_65_MHZ  = 36650000,
	MxL_IF_44_MHZ	  = 44000000
} MxLxxxRF_IF_Freq ;

typedef enum
{
	MxL_XTAL_16_MHZ		= 16000000,
	MxL_XTAL_20_MHZ		= 20000000,
	MxL_XTAL_20_25_MHZ	= 20250000,
	MxL_XTAL_20_48_MHZ	= 20480000,
	MxL_XTAL_24_MHZ		= 24000000,
	MxL_XTAL_25_MHZ		= 25000000,
	MxL_XTAL_25_14_MHZ	= 25140000,
	MxL_XTAL_27_MHZ		= 27000000,
	MxL_XTAL_28_8_MHZ	= 28800000,
	MxL_XTAL_32_MHZ		= 32000000,
	MxL_XTAL_40_MHZ		= 40000000,
	MxL_XTAL_44_MHZ		= 44000000,
	MxL_XTAL_48_MHZ		= 48000000,
	MxL_XTAL_49_3811_MHZ = 49381100	
} MxLxxxRF_Xtal_Freq ;

typedef enum
{
	MxL_BW_6MHz = 6,
	MxL_BW_7MHz = 7,
	MxL_BW_8MHz = 8
} MxLxxxRF_BW_MHz;

typedef enum
{
	MxL_NORMAL_IF = 0 ,
	MxL_INVERT_IF

} MxLxxxRF_IF_Spectrum ;


typedef enum
{
	MxL_CLKOUT_DISABLE = 0 ,
	MxL_CLKOUT_ENABLE

} MxLxxxRF_ClkOut;

typedef enum
{
	MxL_CLKOUT_AMP_0 = 0 ,
	MxL_CLKOUT_AMP_1,
	MxL_CLKOUT_AMP_2,
	MxL_CLKOUT_AMP_3,
	MxL_CLKOUT_AMP_4,
	MxL_CLKOUT_AMP_5,
	MxL_CLKOUT_AMP_6,
	MxL_CLKOUT_AMP_7,
	MxL_CLKOUT_AMP_8,
	MxL_CLKOUT_AMP_9,
	MxL_CLKOUT_AMP_10,
	MxL_CLKOUT_AMP_11,
	MxL_CLKOUT_AMP_12,
	MxL_CLKOUT_AMP_13,
	MxL_CLKOUT_AMP_14,
	MxL_CLKOUT_AMP_15
} MxLxxxRF_ClkOut_Amp;

typedef enum
{
	MxL_AGC_SEL1 = 0,
	MxL_AGC_SEL2
} MxLxxxRF_AGC_Sel;

/* Enumeration of Acceptable Crystal Capacitor values */
typedef enum
{
	MxL_XTAL_CAP_0_PF = 0,
	MxL_XTAL_CAP_1_PF = 1,
	MxL_XTAL_CAP_2_PF = 2,
	MxL_XTAL_CAP_3_PF = 3,
	MxL_XTAL_CAP_4_PF = 4,
	MxL_XTAL_CAP_5_PF = 5,
	MxL_XTAL_CAP_6_PF = 6,
	MxL_XTAL_CAP_7_PF = 7,
	MxL_XTAL_CAP_8_PF = 8,
	MxL_XTAL_CAP_9_PF = 9,
	MxL_XTAL_CAP_10_PF = 10,
	MxL_XTAL_CAP_11_PF = 11,
	MxL_XTAL_CAP_12_PF = 12,
	MxL_XTAL_CAP_13_PF = 13,
	MxL_XTAL_CAP_14_PF = 14,
	MxL_XTAL_CAP_15_PF = 15,
	MxL_XTAL_CAP_16_PF = 16,
	MxL_XTAL_CAP_17_PF = 17,
	MxL_XTAL_CAP_18_PF = 18,
	MxL_XTAL_CAP_19_PF = 19,
	MxL_XTAL_CAP_20_PF = 20,
	MxL_XTAL_CAP_21_PF = 21,
	MxL_XTAL_CAP_22_PF = 22,
	MxL_XTAL_CAP_23_PF = 23,
	MxL_XTAL_CAP_24_PF = 24,
	MxL_XTAL_CAP_25_PF = 25
}	MxLxxxRF_Xtal_Cap;

typedef enum
{
	MxL_IF_SPLIT_DISABLE = 0,
	MxL_IF_SPLIT_ENABLE
}	MxLxxxRF_Analog_IF_Split;

typedef enum
{
	MxL_IF_PATH1 = 0,
	MxL_IF_PATH2
}	MxLxxxRF_IF_Path;


/* MxLxxxRF TunerConfig Struct */
typedef struct _MxLxxxRF_TunerConfigS
{
	MxLxxxRF_I2CAddr		I2C_Addr;
	MxLxxxRF_Mode			Mode;
	MxLxxxRF_Xtal_Freq		Xtal_Freq;
	MxLxxxRF_IF_Freq	    IF_Freq;
	MxLxxxRF_IF_Spectrum	IF_Spectrum;
	MxLxxxRF_ClkOut			ClkOut_Setting;
    MxLxxxRF_ClkOut_Amp		ClkOut_Amp;
	MxLxxxRF_Xtal_Cap		Xtal_Cap;
	MxLxxxRF_BW_MHz			BW_MHz;
	MxLxxxRF_TunerID		TunerID;
	MxLxxxRF_AGC_Sel		AGC;
	MxLxxxRF_Analog_IF_Split IF_Split;		/* Valid for MxL302RF only */
	MxLxxxRF_IF_Path		IF_Path;
	UINT32					RF_Freq_Hz;
} MxLxxxRF_TunerConfigS;


/* typedef  *MxLxxxRF_TunerConfigS pMxLxxxRF_TunerConfigS; */

typedef struct
{
	UINT8 Num;	/*Register number */
	UINT8 Val;	/*Register value */
} IRVType, *PIRVType;


/* Common functions */
UINT32 SetIRVBit(PIRVType pIRV, UINT8 Num, UINT8 Mask, UINT8 Val);
UINT32 SetIRVBit_Ext(PIRVType pIRV, UINT8 Num1, UINT8 Mask, UINT8 Val1, UINT8 Val2);
/* SINT32 round_d(double inVal); */ 
UINT32 div_rnd_uint32(UINT32 numerator, UINT32 denominator);




#endif /* __MxLxxxRF_COMMON_H__*/

