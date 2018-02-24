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
#ifndef MSVIF_H
#define MSVIF_H
#endif

#if (CHIP_FAMILY_TYPE!=CHIP_FAMILY_A7)
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#ifdef _MSVIF_C_
    #define _MSVIF_DEC_
#else
    #define _MSVIF_DEC_ extern
#endif

#define msWriteByteMask(x,y,z)          MDrv_WriteByteMask(x,y,z)
#define msWriteByte(x,y)                MDrv_WriteByte(x,y)
#define msWriteBit(x,y,z)               MDrv_WriteRegBit(x,y,z)
#define msRead2Bytes(x)                 MDrv_Read2Byte(x)
#define msReadByte(x)                   MDrv_ReadByte(x)
#define Delay1ms(x)                     MsOS_DelayTask(x)
#define Delay1us(x)                     MsOS_DelayTaskUs(x)
#define BOOL                            BOOLEAN
#define RegUnitType                     MS_VIF_REG_TYPE

#define AGC_MEAN16_UPBOUND              0x8C     // 1.256*0xE0/2
#define AGC_MEAN16_LOWBOUND             0x13     // (1/4)*0x9A/2
#define AGC_MEAN16_UPBOUND_SECAM        0x28     // 1.256*0x40/2
#define AGC_MEAN16_LOWBOUND_SECAM       0x08     // (1/4)*0x40/2

#ifndef _BIT0
#define _BIT0  0x0001
#endif
#ifndef _BIT1
#define _BIT1  0x0002
#endif
#ifndef _BIT2
#define _BIT2  0x0004
#endif
#ifndef _BIT3
#define _BIT3  0x0008
#endif
#ifndef _BIT4
#define _BIT4  0x0010
#endif
#ifndef _BIT5
#define _BIT5  0x0020
#endif
#ifndef _BIT6
#define _BIT6  0x0040
#endif
#ifndef _BIT7
#define _BIT7  0x0080
#endif
#ifndef _BIT8
#define _BIT8  0x0100
#endif
#ifndef _BIT9
#define _BIT9  0x0200
#endif
#ifndef _BIT10
#define _BIT10 0x0400
#endif
#ifndef _BIT11
#define _BIT11 0x0800
#endif
#ifndef _BIT12
#define _BIT12 0x1000
#endif
#ifndef _BIT13
#define _BIT13 0x2000
#endif
#ifndef _BIT14
#define _BIT14 0x4000
#endif
#ifndef _BIT15
#define _BIT15 0x8000
#endif

// register
typedef struct
{
    U32 u32Address;   // register index
    U8  u8Value;      // register value
} MS_VIF_REG_TYPE;

typedef enum
{
    VIF_START,
    VIF_AGC_STATUS,
    VIF_AFC_STATUS,
    VIF_AFC_STATUS2,
    VIF_STEADY_STATUS,
    VIF_NUMS
}VIFStatus;

typedef enum
{
    VCO_CAL_START,
    VCO_CAL_FINISH,
    VCO_CAL_CHECK,
    VCO_CAL_END,
    VCO_NUMS
}VCOCalStatus;

typedef enum
{
    VIF_SOUND_BG,
    VIF_SOUND_I,
    VIF_SOUND_DK1,
    VIF_SOUND_DK2,
    VIF_SOUND_DK3,
    VIF_SOUND_L,
    VIF_SOUND_LL,
    VIF_SOUND_MN,
    VIF_SOUND_NUMS
}VIFSoundSystem;

typedef enum
{
    IF_FREQ_3395, // SECAM-L'
    IF_FREQ_3800, // PAL
    IF_FREQ_3890, // PAL
    IF_FREQ_3950, // only for PAL-I
    IF_FREQ_4575, // NTSC-M/N
    IF_FREQ_5875, // NTSC-M/N
    IF_FREQ_NUMS
}IfFrequencyType;

typedef struct
{
    BYTE VifTop;
    BYTE VifIfBaseFreq;
    BYTE VifTunerStepSize;
    BOOL VifFlatSaw;
    WORD VifVgaMaximum;
    WORD VifVgaMinimum;
    WORD GainDistributionThr;
    BYTE VifAgcVgaBase;
    BYTE VifAgcVgaOffs;
    BYTE VifAgcRefNegative;
    BYTE VifAgcRefPositive;
    BYTE VifDagc1Ref;
    BYTE VifDagc2Ref;
    WORD VifDagc1GainOv;
    WORD VifDagc2GainOv;
    BYTE VifCrKf1;
    BYTE VifCrKp1;
    BYTE VifCrKi1;
    BYTE VifCrKp2;
    BYTE VifCrKi2;
    BYTE VifCrKp;
    BYTE VifCrKi;
    WORD VifCrLockThr;
    WORD VifCrThr;
    DWORD VifCrLockNum;
    DWORD VifCrUnlockNum;
    WORD VifCrPdErrMax;
    BOOL VifCrLockLeakySel;
    BOOL VifCrPdX2;
    BOOL VifCrLpfSel;
    BOOL VifCrPdModeSel;
    BOOL VifCrKpKiAdjust;
    BYTE VifCrKpKiAdjustGear; 	
    BYTE VifCrKpKiAdjustThr1; 	
    BYTE VifCrKpKiAdjustThr2; 	
    BYTE VifCrKpKiAdjustThr3; 	
    BOOL VifDynamicTopAdjust;
    BYTE VifDynamicTopMin;
    BOOL VifAmHumDetection;
    BOOL VifClampgainClampSel;
    BYTE VifClampgainSyncbottRef;
    BYTE VifClampgainSyncheightRef;
    BYTE VifClampgainKc;
    BYTE VifClampgainKg;
    BOOL VifClampgainClampOren;
    BOOL VifClampgainGainOren;
    WORD VifClampgainClampOvNegative;
    WORD VifClampgainGainOvNegative;
    WORD VifClampgainClampOvPositive;
    WORD VifClampgainGainOvPositive;
    BYTE VifClampgainClampMin;
    BYTE VifClampgainClampMax;
    BYTE VifClampgainGainMin;
    BYTE VifClampgainGainMax;
    WORD VifClampgainPorchCnt;
    BYTE VifPeakingFilterBG;
    BYTE VifYcDelayFilterBG;
    BYTE VifGroupDelayFilterBG;
    BYTE VifPeakingFilterDK;
    BYTE VifYcDelayFilterDK;    
    BYTE VifGroupDelayFilterDK;
    BYTE VifPeakingFilterI;
    BYTE VifYcDelayFilterI;
    BYTE VifGroupDelayFilterI;
    BYTE VifPeakingFilterL;
    BYTE VifYcDelayFilterL;
    BYTE VifGroupDelayFilterL;
    BYTE VifPeakingFilterLL;
    BYTE VifYcDelayFilterLL;
    BYTE VifGroupDelayFilterLL;
    BYTE VifPeakingFilterMN;
    BYTE VifYcDelayFilterMN;
    BYTE VifGroupDelayFilterMN;
    BOOL ChinaDescramblerBox;
    BYTE VifDelayReduce;
    BOOL VifOverModulation;
    WORD VifSos21FilterC0;
    WORD VifSos21FilterC1;
    WORD VifSos21FilterC2;
    WORD VifSos21FilterC3;
    WORD VifSos21FilterC4;
    WORD VifSos22FilterC0;
    WORD VifSos22FilterC1;
    WORD VifSos22FilterC2;
    WORD VifSos22FilterC3;
    WORD VifSos22FilterC4;
    WORD VifSos31FilterC0;
    WORD VifSos31FilterC1;
    WORD VifSos31FilterC2;
    WORD VifSos31FilterC3;
    WORD VifSos31FilterC4;
    WORD VifSos32FilterC0;
    WORD VifSos32FilterC1;
    WORD VifSos32FilterC2;
    WORD VifSos32FilterC3;
    WORD VifSos32FilterC4;
}VIFInitialIn;

BYTE g_ucVifStatusStep;
BYTE g_ucVifSoundSystemType;
BOOL g_bCheckModulationType;  // 0: negative; 1: positive
BOOL g_bCheckIFFreq;          // 0: 38.9 MHz (PAL/SECAM L); 1: 33.9 MHz (SECAM L')
DWORD g_VifCrLfFfMaxDiff;
DWORD g_VifCrLfFfMaxInstDiff;
BOOL g_bCrSeriousDrift;
BYTE g_VifCrKp;
BYTE g_VifCrKi;

#define FORCE_SWITCH_BANK 0
#if FORCE_SWITCH_BANK
    BOOL g_bBypassVIF;
#endif

extern VIFInitialIn xdata VIFInitialIn_inst;

void msVifSetIfFreq(IfFrequencyType ucIfFreq);
void msVifInitial(void);
void msVifHandler(BOOL bVifDbbAcq);
void msVifSetSoundSystem(VIFSoundSystem ucSoundSystem);
void msVIFversion(void);
void msVifAdcInitial(void);
void msVifTopAdjust(void);

// ========== Register Definition =====================
#define ADC_REG_BASE                0x0E00
#define RF_REG_BASE                 0x0800
#define DBB1_REG_BASE               0x1000
#define DBB2_REG_BASE               0x2b00
#define DBB3_REG_BASE               0x3c00

///////////////////////////////////////////////////////
// [ADC bank register]
///////////////////////////////////////////////////////
#define VIF_VCO_PWR      	        0x100E00L
#define VIF_VCOREG_PWR      	    0x100E00L
#define VIF_PLL_PWR      	        0x100E00L
#define VIF_CBC_PWR      	        0x100E00L
#define VIF_CBC_PWRS      	        0x100E00L
#define VIF_TAGC_PWR      	        0x100E00L
#define VIF_PWR_PGA2S      	        0x100E01L
#define VIF_PWR_LPFS      	        0x100E01L
#define VIF_MXPWRS      	        0x100E01L
#define VIF_PGPWRS      	        0x100E01L
#define VIF_PWR_PGA2V      	        0x100E01L
#define VIF_PWR_LPFV      	        0x100E01L
#define VIF_MXPWRV      	        0x100E01L
#define VIF_PGPWRV      	        0x100E01L
#define VIF_PLL_R      	            0x100E02L
#define VIF_CBC_BGR0      	        0x100E02L
#define VIF_CBC_BGR1      	        0x100E02L
#define VIF_PLL_RSTZ      	        0x100E02L
#define VIF_PLLTPEN      	        0x100E02L
#define VIF_PLL_TEST      	        0x100E03L
#define VIF_PLL_ICPSW      	        0x100E03L
#define VIF_PLL_ENLCKDET      	    0x100E03L
#define VIF_PLL_M      	            0x100E04L
#define VIF_PLL_MTEST      	        0x100E04L
#define VIF_PLL_MSEL      	        0x100E04L
#define VIF_TAGC_ODMODE      	    0x100E04L
#define VIF_PLL_N      	            0x100E05L
#define VIF_PLL_RDIV      	        0x100E05L
#define VIF_PLL_RSEL      	        0x100E05L
#define VIF_PLL_ICTRL      	        0x100E06L
#define VIF_PLL_LPEX      	        0x100E06L
#define VIF_PLL_ADD128U      	    0x100E06L
#define VIF_PLL_PBYP      	        0x100E06L
#define VIF_PLL_PSEL      	        0x100E06L
#define VIF_PLL_FBBYP      	        0x100E06L
#define VIF_VCO_R      	            0x100E07L
#define VIF_VCOREG_SBIAS      	    0x100E07L
#define VIF_VCO_REF      	        0x100E07L
#define VIF_PLL_SBIAS     	        0x100E07L
#define VIF_VCO_LP      	        0x100E08L
#define VIF_VCO_LK      	        0x100E08L
#define VIF_FCODE_EXT      	        0x100E0BL
#define VIF_RN_TUNE      	        0x100E0BL
#define VIF_FORCE_TUNE      	    0x100E0BL
#define VIF_CALIB_TUNE      	    0x100E0BL
#define VIF_MXCR             	    0x100E0CL
#define VIF_MXLOR           	    0x100E0CL
#define VIF_PGCR               	    0x100E0DL
#define VIF_TINENS           	    0x100E0DL
#define VIF_TINENV           	    0x100E0DL
#define VIF_ISW_PGA2           	    0x100E0EL
#define VIF_ISW_LPF           	    0x100E0EL
#define VIF_ISW_TUNE           	    0x100E0EL
#define VIF_IFTPENS           	    0x100E0FL
#define VIF_IFTPENV           	    0x100E0FL
#define VIF_MXTPENS           	    0x100E0FL
#define VIF_MXTPENV           	    0x100E0FL
#define VIF_PGTPENS           	    0x100E0FL
#define VIF_PGTPENV           	    0x100E0FL
#define VIF_MXTPS           	    0x100E10L
#define VIF_PGTPA           	    0x100E10L
#define VIF_TAGC_TAFC_NRZDATA       0x100E10L
#define VIF_TESTENBS           	    0x100E11L
#define VIF_TESTENBV           	    0x100E11L
#define VIF_TEN_LPFS           	    0x100E11L
#define VIF_TEN_LPFV           	    0x100E11L
#define VIF_XTAL_BYP                0x100E11L
#define TAGC_EN_KEY                 0x100E14L
#define TAGC_INVCLK      		    0x100E16L
#define TAGC_TAFC_OUTR      		0x100E16L
#define VIF_BYPASS      		    0x100E19L
#define SIF_BYPASS      		    0x100E19L
#define VIF_TB      	            0x100E22L
#define VIF_TESTPGA1ENBS      	    0x100E23L
#define VIF_TESTPGA1ENBV      	    0x100E23L
#define VIF_VREF      	            0x100E24L
#define VIF_CBCTPEN      	        0x100E26L
#define VIF_LPFS_BW                 0x100E2AL
#define VIF_LPFTUNE_XSEL            0x100E2AL
#define VIF_PGA1GAINS_SRC           0x100E2AL
#define VIF_PGA2S_HG                0x100E2AL
#define VIF_PGA2_GCTRLS             0x100E2BL
#define VIF_PGA2_GCTRLV             0x100E2BL
#define VIF_MX_GAIN_SWS             0x100E2BL
#define VIF_MX_GAIN_SWV             0x100E2BL
#define VIF_FCAL_DIV                0x100E2CL
#define VIF_TUNEC                   0x100E2DL

///////////////////////////////////////////////////////
// [RF bank register]
///////////////////////////////////////////////////////
#define VIF_VCO_BANK_W      	    0x100808L
#define VIF_PLL_CPINIT_W      	    0x100808L
#define VIF_CAL_START      	        0x100808L
#define VIF_PGA1GAINS_W      	    0x100809L
#define VIF_PGA1GAINV_W      	    0x100809L
#define VIF_GAIN_PGA2S_W      	    0x10080AL
#define VIF_GAIN_PGA2V_W      	    0x10080AL
#define TAGC_W_L      		        0x100812L
#define TAGC_W_H      		        0x100813L
#define TAGC_TEST_EN      		    0x100816L
#define TAGC_POLARITY      		    0x100816L
#define TAGC_SEL_DECIMATE_NUM      	0x100817L
#define TAGC_DITHER_SHIFT      		0x100817L
#define TAGC_SEL_SECONDER      		0x100817L
#define TAGC_DITHER_EN      		0x100817L
#define OREN_PGA2_S      		    0x100819L
#define OREN_PGA1_S      		    0x100819L
#define OREN_PGA2_V      		    0x100819L
#define OREN_PGA1_V      		    0x100819L
#define OREN_VCO_BANK      		    0x100819L
#define OREN_TAGC      		        0x100819L
#define VIF_VCO_BANK      	        0x10081AL
#define VIF_PLL_CPINIT      	    0x10081AL
#define VIF_LOCK      	            0x10081AL
#define VIF_VCTRL_UNDER      	    0x10081AL
#define VIF_VCTRL_OVER      	    0x10081AL
#define VIF_VCOCAL_FAIL      	    0x10081AL
#define VIF_PGA1GAINS         	    0x10081BL
#define VIF_PGA1GAINV         	    0x10081BL
#define VIF_GAIN_PGA2S      	    0x10081CL
#define VIF_GAIN_PGA2V      	    0x10081CL
#define VIF_FCODE_OUT      	        0x10081DL
#define VIF_STOPCAL_TUNE      	    0x10081DL
#define VIF_CAL_FINISH      	    0x10081DL
#define VIF_CAL_GAP      	        0x10081EL
#define VSYNC_VD_MASK      	        0x100820L
#define VSYNC_VD_POLARITY      	    0x100820L
#define VSYNC_OVERRIDE      	    0x100821L
#define TAGC_DAC_TESTBUS      	    0x100828L

#define CLAMPGAIN_RSTZ      	    0x100840L
#define CLAMPGAIN_BYPASS      	    0x100840L
#define CLAMPGAIN_EN          	    0x100840L
#define CLAMPGAIN_SEL         	    0x100840L
#define CLAMPGAIN_STATUS_FREEZE	    0x100840L
#define CLAMPGAIN_SYNCBOTT_REF 	    0x100842L
#define CLAMPGAIN_SYNCHEIGHT_REF 	0x100843L
#define CLAMPGAIN_KC          	    0x100844L
#define CLAMPGAIN_KG          	    0x100844L
#define CLAMPGAIN_CLAMP_OREN   	    0x100845L
#define CLAMPGAIN_GAIN_OREN   	    0x100845L
#define CLAMPGAIN_CLAMP_OVERWRITE   0x100846L
#define CLAMPGAIN_GAIN_OVERWRITE    0x100848L
#define CLAMPGAIN_CLAMP_MIN   	    0x10084AL
#define CLAMPGAIN_CLAMP_MAX   	    0x10084BL
#define CLAMPGAIN_GAIN_MIN   	    0x10084CL
#define CLAMPGAIN_GAIN_MAX   	    0x10084DL
#define CLAMPGAIN_SYNCBOTTOM_OFFSET 0x10084EL
#define CLAMPGAIN_RATIO             0x10084FL
#define CLAMPGAIN_SYNCBOTTOM_CNT    0x100850L
#define CLAMPGAIN_PORCH_CNT         0x100852L
#define CLAMPGAIN_PEAK_MEAN         0x100854L
#define CLAMPGAIN_SYNCBOTTOM_MEAN   0x100856L
#define CLAMPGAIN_PORCH_MEAN        0x100858L
#define CLAMPGAIN_CLAMP             0x10085AL
#define CLAMPGAIN_GAIN              0x10085CL

#define VSYNC_RSTZ      	        0x100880L
#define VSYNC_ENABLE      	        0x100880L
#define VSYNC_LPF_SEL      	        0x100880L
#define VSYNC_DET_DATAIN_SEL      	0x100880L
#define VSYNC_EXT      	            0x100880L
#define VSYNC_OFFSET      	        0x100882L
#define VSYNC_CNT      	            0x100883L
#define VSYNC_VSYNC_CNT      	    0x100884L
#define VSYNC_BYPASS_CNT      	    0x100885L
#define VSYNC_MIN_CNT      	        0x100886L

#define VIF_VADC_DEC      	        0x1008AAL
#define VIF_AADC_DEC      	        0x1008AAL
#define VIFDAC_OUT_SEL      	    0x1008C0L
#define VIFDAC_ENABLE      	        0x1008C0L
#define VIFDAC_MSB_INV      	    0x1008C0L
#define VIFDAC_CLK_INV      	    0x1008C0L
#define VIFDAC_TB_SWAP      	    0x1008C0L
#define VIFDAC_RAMP_OUT_MAX_L      	0x1008C2L
#define VIFDAC_RAMP_OUT_MAX_H      	0x1008C3L
#define VIFDAC_RAMP_OUT_MIN_L      	0x1008C4L
#define VIFDAC_RAMP_OUT_MIN_H      	0x1008C5L
#define VIFDAC_FORCE_DATA_L      	0x1008C6L
#define VIFDAC_FORCE_DATA_H      	0x1008C7L

#define TIMER_MAX                   0x1008E0L
#define TIMER                       0x1008E2L
#define DCXO_RSTZ      	            0x1008EAL
#define DCXO_MODE      	            0x1008EAL
#define DCXO_SYNC             	    0x1008EBL
#define DCXO_TRI_ANG_MIN      	    0x1008ECL
#define DCXO_TRI_ANG_MAX      	    0x1008EDL
#define DCXO_FORCE      	        0x1008EEL
#define DCXO_STEP_CNT               0x1008F0L
#define DCXO_CODE         	        0x1008F4L

/////////////////////////////////////////////////////////
// [DBB1 bank register]
/////////////////////////////////////////////////////////
#define VIF_SOFT_RSTZ         		0x101000L
#define AFC_SOFT_RSTZ         		0x101000L
#define FILTER_SOFT_RSTZ         	0x101000L
#define AGC_SOFT_RSTZ         		0x101000L
#define DAGC1_SOFT_RSTZ         	0x101000L
#define DAGC2_SOFT_RSTZ         	0x101000L
#define AAGC_SOFT_RSTZ         		0x101000L
#define ADAGC_SOFT_RSTZ             0x101000L
#define MODULATION_TYPE     		0x101002L
#define CR_LF_FF_LAT                0x101002L
#define DEBUG_CLK_FINAL_SEL         0x101002L
#define BYPASS_N_A4         		0x101002L
#define BYPASS_CR_NOTCH2       		0x101002L
#define AUDIO_BYPASS        		0x101004L
#define LOCK_LEAKY_FF_SEL       	0x101006L
#define VNCO_INV_OREN       		0x101006L
#define VNCO_INV_OV		       		0x101006L
#define CR_CODIC_TH  		     	0x101008L
#define BYPASS_SOS11		  		0x10100AL
#define BYPASS_SOS12		  		0x10100AL
#define BYPASS_SOS21		  		0x10100AL
#define BYPASS_SOS22		  		0x10100AL
#define BYPASS_SOS31		  		0x10100AL
#define BYPASS_SOS32		  		0x10100AL
#define	BYPASS_IMAGE_REJ_IIR		0x10100BL
#define IMAGE_REJ_OUT_SEL  	  		0x10100BL

#define CR_DL_A		  		     	0x101014L
#define CR_DL_A_BYPASS	     	    0x101014L
#define CR_F_OFFSET	 		     	0x101015L
#define CR_PD_ERR_MAX_L		        0x101016L
#define CR_PD_ERR_MAX_H		     	0x101017L
#define CR_KL_L		     			0x101018L
#define CR_KL_H		     			0x101019L
#define CR_NOTCH_A1_L		     	0x10101AL
#define CR_NOTCH_A1_H		     	0x10101BL
#define CR_NOTCH_A2_L		     	0x10101CL
#define CR_NOTCH_A2_H		     	0x10101DL
#define CR_NOTCH_B1_L		     	0x10101EL
#define CR_NOTCH_B1_H		     	0x10101FL
#define CR_ANCO_SEL		     		0x101020L
#define CR_PD_MODE		     		0x101020L
#define CR_PD_X2		     		0x101020L
#define CR_INV			     		0x101020L
#define CR_LPF_SEL		     		0x101020L
#define CR_LF_FF_RSTZ   		    0x101020L
#define CR_K_SEL   					0x101020L
#define CR_PD_LIMITER   			0x101020L
#define CR_KP_SW   					0x101022L
#define CR_KI_SW   					0x101022L
#define CR_KF_SW   					0x101023L
#define CR_RATE					    0x101024L
#define CR_KP1_HW   				0x101028L
#define CR_KI1_HW   				0x101028L
#define CR_KF1_HW   				0x101029L
#define CR_KP2_HW   				0x10102AL
#define CR_KI2_HW   				0x10102AL
#define CR_KF2_HW   				0x10102BL
#define CR_LOCK_TH_L   				0x10102CL
#define CR_LOCK_TH_H   				0x10102DL
#define CR_FOE_SCAL_FACTOR_L        0x10102EL
#define CR_FOE_SCAL_FACTOR_H   		0x10102FL
#define CR_LOCK_NUM		   			0x101030L
#define CR_UNLOCK_NUM		   		0x101034L
#define CR_FOE		   				0x101038L
#define CR_LOCK_STATUS		   		0x101039L
#define CR_LOCK_LEAKY_FF_I		   	0x10103AL
#define CR_LOCK_LEAKY_FF_Q		   	0x10103CL
#define CR_NOTCH2_A1_L		   		0x10103EL
#define CR_NOTCH2_A1_H		   		0x10103FL
#define CR_NOTCH2_A2_L		   		0x101040L
#define CR_NOTCH2_A2_H		   		0x101041L
#define CR_NOTCH2_B1_L		   		0x101042L
#define CR_NOTCH2_B1_H		   		0x101043L
#define CR_LF_FF_RPT                0x101044L

#define ADC_43M             		0x101080L
#define BYPASS_DC           		0x101080L
#define BYPASS_N_A1         		0x101080L
#define BYPASS_N_A2         		0x101080L
#define BYPASS_IMAGE_REJ1           0x101080L
#define ACI_REJ_NTSC                0x101080L
#define A_BP_OUT_X2            		0x101080L
#define BYPASS_A_DC         		0x101081L
#define BYPASS_A_BPF       		  	0x101081L
#define AD_SIGNED_UNSIGNED      	0x101081L
#define VD_SIGNED_UNSIGNED      	0x101081L
#define BYPASS_N_A3         		0x101081L
#define BYPASS_IMAGE_REJ2           0x101081L
#define DC_C         		        0x101082L
#define A_DC_C         		        0x101083L
#define N_A1_C0_L         		    0x101084L
#define N_A1_C0_H         		    0x101085L
#define N_A1_C1_L         		    0x101086L
#define N_A1_C1_H         		    0x101087L
#define N_A1_C2_L         		    0x101088L
#define N_A1_C2_H         		    0x101089L
#define N_A2_C0_L         		    0x10108AL
#define N_A2_C0_H         		    0x10108BL
#define N_A2_C1_L         		    0x10108CL
#define N_A2_C1_H         		    0x10108DL
#define N_A2_C2_L         		    0x10108EL
#define N_A2_C2_H         		    0x10108FL
#define AN_C0_L         		    0x101090L
#define AN_C0_H         		    0x101091L
#define AN_C1_L         		    0x101092L
#define AN_C1_H         		    0x101093L
#define AN_C2_L         		    0x101094L
#define AN_C2_H         		    0x101095L
#define SOS11_C0_L         		    0x101096L
#define SOS11_C0_H         		    0x101097L
#define SOS11_C1_L         		    0x101098L
#define SOS11_C1_H         		    0x101099L
#define SOS11_C2_L         		    0x10109AL
#define SOS11_C2_H         		    0x10109BL
#define SOS11_C3_L         		    0x10109CL
#define SOS11_C3_H         		    0x10109DL
#define SOS11_C4_L         		    0x10109EL
#define SOS11_C4_H         		    0x10109FL
#define SOS12_C0_L         		    0x1010A0L
#define SOS12_C0_H         		    0x1010A1L
#define SOS12_C1_L         		    0x1010A2L
#define SOS12_C1_H         		    0x1010A3L
#define SOS12_C2_L         		    0x1010A4L
#define SOS12_C2_H         		    0x1010A5L
#define N_A3_C0_L         		    0x1010A6L
#define N_A3_C0_H         		    0x1010A7L
#define N_A3_C1_L         		    0x1010A8L
#define N_A3_C1_H         		    0x1010A9L
#define N_A3_C2_L         		    0x1010AAL
#define N_A3_C2_H         		    0x1010ABL
#define N_A4_C0_L         		    0x1010ACL
#define N_A4_C0_H         		    0x1010ADL
#define N_A4_C1_L         		    0x1010AEL
#define N_A4_C1_H         		    0x1010AFL
#define N_A4_C2_L         		    0x1010B0L
#define N_A4_C2_H         		    0x1010B1L
#define SOS12_C3_L         		    0x1010B2L
#define SOS12_C3_H         		    0x1010B3L
#define SOS12_C4_L         		    0x1010B4L
#define SOS12_C4_H         		    0x1010B5L
#define SOS21_C0_L         		    0x1010B6L
#define SOS21_C0_H         		    0x1010B7L
#define SOS21_C1_L         		    0x1010B8L
#define SOS21_C1_H         		    0x1010B9L
#define SOS21_C2_L         		    0x1010BAL
#define SOS21_C2_H         		    0x1010BBL
#define SOS21_C3_L         		    0x1010BCL
#define SOS21_C3_H         		    0x1010BDL
#define SOS21_C4_L         		    0x1010BEL
#define SOS21_C4_H         		    0x1010BFL
#define SOS22_C0_L         		    0x1010C0L
#define SOS22_C0_H         		    0x1010C1L
#define SOS22_C1_L         		    0x1010C2L
#define SOS22_C1_H         		    0x1010C3L
#define SOS22_C2_L         		    0x1010C4L
#define SOS22_C2_H         		    0x1010C5L
#define SOS22_C3_L         		    0x1010C6L
#define SOS22_C3_H         		    0x1010C7L
#define SOS22_C4_L         		    0x1010C8L
#define SOS22_C4_H         		    0x1010C9L
#define SOS31_C0_L         		    0x1010CAL
#define SOS31_C0_H         		    0x1010CBL
#define SOS31_C1_L         		    0x1010CCL
#define SOS31_C1_H         		    0x1010CDL
#define SOS31_C2_L         		    0x1010CEL
#define SOS31_C2_H         		    0x1010CFL
#define SOS31_C3_L         		    0x1010D0L
#define SOS31_C3_H         		    0x1010D1L
#define SOS31_C4_L         		    0x1010D2L
#define SOS31_C4_H         		    0x1010D3L
#define SOS32_C0_L         		    0x1010D4L
#define SOS32_C0_H         		    0x1010D5L
#define SOS32_C1_L         		    0x1010D6L
#define SOS32_C1_H         		    0x1010D7L
#define SOS32_C2_L         		    0x1010D8L
#define SOS32_C2_H         		    0x1010D9L
#define SOS32_C3_L         		    0x1010DAL
#define SOS32_C3_H         		    0x1010DBL
#define SOS32_C4_L         		    0x1010DCL
#define SOS32_C4_H         		    0x1010DDL
#define FIRMWARE_VERSION_L          0x1010FEL
#define FIRMWARE_VERSION_H          0x1010FFL

/////////////////////////////////////////////////////////
// [DBB2 bank register]
/////////////////////////////////////////////////////////
#define AGC_ENABLE          		0x102B00L
#define AGC_MODE            		0x102B00L
#define AGC_MEAN_SEL        		0x102B00L
#define AGC_GAIN_SLOPE      		0x102B00L
#define AGC_VSYNC_ENA      		    0x102B00L
#define AGC_VSYNC_ENB      		    0x102B00L
#define AGC_VSYNC_SEL      		    0x102B00L
#define AGC_VSYNC_POL      		    0x102B01L
#define AGC_IN_SEL      		  	0x102B01L
#define AGC_ABS_DATA_IN_SEL         0x102B01L
#define AGC_DBB_VVGA_SEL   		  	0x102B01L
#define AGC_DBB_AVGA_SEL   		  	0x102B01L
#define AGC_VSYNC_PULSE   		  	0x102B01L
#define AGC_LINE_CNT_L      		0x102B02L
#define AGC_LINE_CNT_H      		0x102B03L
#define AGC_PORCH_CNT_L     		0x102B04L
#define AGC_PORCH_CNT_H     		0x102B05L
#define AGC_PEAK_CNT_L      		0x102B06L
#define AGC_PEAK_CNT_H      		0x102B07L
#define AGC_REF                		0x102B08L
#define AGC_K               		0x102B0AL
#define AGC_OFFSET                  0x102B0BL
#define AGC_GAIN_OREN       		0x102B0CL
#define AGC_DBB_VVGA_OREN     		0x102B0CL
#define AAGC_DBB_VVGA_OREN      	0x102B0CL
#define AGC_PGA1_OV         		0x102B0EL
#define AGC_PGA2_OV         		0x102B0FL
#define AGC_VGA_OV_L        		0x102B10L
#define AGC_VGA_OV_H        		0x102B11L
#define AGC_PGA1_MIN        		0x102B12L
#define AGC_PGA1_MAX        		0x102B13L
#define AGC_PGA2_MIN        		0x102B14L
#define AGC_PGA2_MAX        		0x102B15L
#define AGC_VGA_MIN_L       		0x102B16L
#define AGC_VGA_MIN_H       		0x102B17L
#define AGC_VGA_MAX_L       		0x102B18L
#define AGC_VGA_MAX_H       		0x102B19L
#define AGC_DBB_VVGA_OV_L     		0x102B1AL
#define AGC_DBB_VVGA_OV_H     		0x102B1BL
#define AAGC_DBB_VVGA_OV_L         	0x102B1CL
#define AAGC_DBB_VVGA_OV_H         	0x102B1DL

#define AGC_MEAN0          		    0x102B20L
#define AGC_MEAN16         		    0x102B22L
#define AGC_MEAN256        		    0x102B24L
#define AGC_DIFF            		0x102B26L
#define AGC_VGA             		0x102B28L
#define AGC_PGA1A            		0x102B2AL
#define AGC_PGA2A            		0x102B2BL
#define AGC_PGA1B            		0x102B2CL
#define AGC_PGA2B            		0x102B2DL
#define AGC_PGA1C            		0x102B2EL
#define AGC_PGA2C            		0x102B2FL
#define AGC_VSYNC_IN                0x102B30L
#define AGC_HS_FOUND                0x102B30L
#define AGC_MAX_MEAN                0x102B31L
#define AGC_VGA_THR                 0x102B46L
#define AGC_VGA_BASE                0x102B48L
#define AGC_VGA_OFFS                0x102B49L

#define ACI_REJ_NTSC_SEL 			0x102B5CL
#define A_LPF_BG_SEL 				0x102B5CL
#define A_DAGC_SEL 					0x102B5CL
#define FILTER_DEBUG_SEL 			0x102B5DL
#define BYPASS_CO_A_REJ 			0x102B5EL
#define BYPASS_CO_A_REJ_NTSC 		0x102B5EL
#define BYPASS_A_NOTCH 				0x102B5EL
#define BYPASS_A_SOS 				0x102B5EL
#define BYPASS_2ND_A_BP 			0x102B5FL
#define BYPASS_A_LPF_BG 			0x102B5FL

#define AAGC_ENABLE         		0x102BA0L
#define AAGC_PGA1_IGN_PGA2          0x102BA0L
#define AAGC_PGA2_IGN_PGA1          0x102BA0L
#define AAGC_PEAK_MEAN_SEL          0x102BA0L
#define AAGC_LINE_CNT          		0x102BA2L
#define AAGC_GAIN_OREN      		0x102BA4L
#define AAGC_VPGA1_OREN      		0x102BA4L
#define AAGC_VPGA2_OREN      		0x102BA4L
#define AAGC_DEC			      	0x102BA5L
#define AAGC_PGA1_OV        		0x102BA6L
#define AAGC_PGA2_OV        		0x102BA7L
#define AAGC_PGA1_MIN       		0x102BA8L
#define AAGC_PGA1_MAX       		0x102BA9L
#define AAGC_PGA2_MIN       		0x102BAAL
#define AAGC_PGA2_MAX       		0x102BABL
#define AAGC_MEAN_MIN       		0x102BACL
#define AAGC_MEAN_MAX       		0x102BADL
#define AAGC_MEAN           		0x102BAEL
#define AAGC_PEAKMEAN       		0x102BB0L
#define AAGC_PGA1           		0x102BB2L
#define AAGC_PGA2           		0x102BB3L
#define AAGC_CNT          			0x102BB4L

#define DEBUG_PORT          		0x102BE0L
#define DEBUG_CLK_SEL       		0x102BE0L
#define DEBUG_CLK_INV       		0x102BE0L
#define DEBUG_SIGNED_UNSIGNED   	0x102BE0L
#define DEBUG_MODULE        		0x102BE1L
#define DEBUG_SWITCH        		0x102BE1L
#define DEBUG_V_A        		    0x102BE1L
#define TESTBUS_INV                 0x102BE1L
#define DEBUG2_EN                   0x102BE1L
#define DEBUG_FREQ_L        		0x102BE2L
#define DEBUG_FREQ_H        		0x102BE3L

/////////////////////////////////////////////////////////
// [DBB3 bank register]
/////////////////////////////////////////////////////////
#define DAGC1_ENABLE          		0x103C00L
#define DAGC1_BYPASS          		0x103C00L
#define DAGC1_GAIN0_FB_EN           0x103C00L
#define DAGC1_DL_BYPASS             0x103C00L
#define DAGC2_ENABLE          		0x103C01L
#define DAGC2_BYPASS          		0x103C01L
#define DAGC2_GAIN0_FB_EN           0x103C01L
#define DAGC2_DL_BYPASS             0x103C01L
#define DAGC1_GAIN_OVERWRITE_L      0x103C02L
#define DAGC1_GAIN_OVERWRITE_H      0x103C03L
#define DAGC1_OREN                  0x103C03L
#define DAGC2_GAIN_OVERWRITE_L      0x103C04L
#define DAGC2_GAIN_OVERWRITE_H      0x103C05L
#define DAGC2_OREN                  0x103C05L
#define DAGC1_REF                   0x103C06L
#define DAGC2_REF                   0x103C07L
#define DAGC1_LEVEL_SHIFT           0x103C08L
#define DAGC2_LEVEL_SHIFT           0x103C09L
#define DAGC1_RATIO                 0x103C0AL
#define DAGC2_RATIO                 0x103C0BL
#define DAGC1_PEAK_CNT_L            0x103C0CL
#define DAGC1_PEAK_CNT_H            0x103C0DL
#define DAGC2_PEAK_CNT_L            0x103C0EL
#define DAGC2_PEAK_CNT_H            0x103C0FL
#define DAGC1_PORCH_CNT_L           0x103C10L
#define DAGC1_PORCH_CNT_H           0x103C11L
#define DAGC2_PORCH_CNT_L           0x103C12L
#define DAGC2_PORCH_CNT_H           0x103C13L
#define DAGC1_MEAN                  0x103C14L
#define DAGC1_VAR                   0x103C16L
#define DAGC2_MEAN                  0x103C18L
#define DAGC2_VAR                   0x103C1AL
#define DAGC1_GAIN                  0x103C1CL
#define DAGC2_GAIN                  0x103C1EL
#define DAGC1_SYNCHEIGHT            0x103C20L
#define DAGC1_VSYNC                 0x103C21L
#define DAGC2_SYNCHEIGHT            0x103C22L
#define DAGC2_VSYNC                 0x103C23L
#define DAGC1_LPF_DELAY_0           0x103C24L
#define DAGC2_LPF_DELAY_0           0x103C26L
#define DAGC1_OFFSET                0x103C28L
#define DAGC2_OFFSET                0x103C29L

#define ADAGC_ENABLE                0x103C80L
#define ADAGC_BYPASS                0x103C80L
#define ADAGC_PEAK_MEAN_SEL         0x103C80L
#define ADAGC_K                     0x103C81L
#define ADAGC_CNT                   0x103C82L
#define ADAGC_DEC                   0x103C86L
#define ADAGC_LINE_CNT              0x103C87L
#define ADAGC_REF                   0x103C88L
#define ADAGC_GAIN_OREN             0x103C8AL
#define ADAGC_GAIN_OV               0x103C8CL
#define ADAGC_MEAN                  0x103CA0L
#define ADAGC_PEAK                  0x103CA1L
#define ADAGC_GAIN                  0x103CA2L
#endif