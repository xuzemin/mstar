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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INTERN_DVBT_H_
#define _INTERN_DVBT_H_
#include "COFDM_Demodulator.h"
#ifdef _INTERN_DVBT_C_
#define EXTSEL
#else
#define EXTSEL extern
#endif


//--------------------------------------------------------------------

 #define     DEMOD_DYNAMIC_SLAVE_ID_1          0x32
// #define     DEMOD_DYNAMIC_SLAVE_ID_2          0x72
// #define     DEMOD_DYNAMIC_SLAVE_ID_3          0xB2
// #define     DEMOD_DYNAMIC_SLAVE_ID_4          0xF2

#define     DEMOD_ADDR_H            0x00
#define     DEMOD_ADDR_L            0x01
#define     DEMOD_WRITE_REG         0x02
#define     DEMOD_WRITE_REG_EX      0x03
#define     DEMOD_READ_REG          0x04
#define     DEMOD_RAM_CONTROL       0x05

#define BOOL    BOOLEAN

#ifndef VIF_SAW_ARCH
#define VIF_SAW_ARCH                    0                   // 0: Dual SAW; 1: external Single SAW; 2:silicon tuner; 3: no saw (not support); 4: internal single SAW
#endif


//#if ( FRONTEND_DEMOD_TYPE == MSTAR_MSB1400_DEMOD || FRONTEND_DEMOD_TYPE == ALTOBEAM_884X  )

//#else

  #if  DTV_SCAN_AUTO_FINE_TUNE_ENABLE
    //INTERN_DVBT_ Capture Range fix to 500K
    #define DEMOD_CAPTURE_RANGE_500_K               500
    #define DEMOD_CAPTURE_RANGE_SIZE                DEMOD_CAPTURE_RANGE_500_K
  #endif

#if 0 // Use COFDM_Demodulator.h
typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_PSYNC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_DCR_LOCK,
    COFDM_AGC_LOCK,
    COFDM_MODE_DET,
} COFDM_LOCK_STATUS;
#endif

//--------------------------------------------------------------------
typedef enum
{
    E_SYS_UNKOWN = -1,
    E_SYS_DVBT,
    E_SYS_DVBC,
    E_SYS_ATSC,
    E_SYS_VIF,

    E_SYS_NUM
}E_SYSTEM;

typedef enum
{
    CMD_SYSTEM_INIT = 0,
    CMD_DAC_CALI,
    CMD_DVBT_CONFIG,
    CMD_DVBC_CONFIG,
    CMD_VIF_CTRL,
    CMD_FSM_CTRL,
    CMD_INDIR_RREG,
    CMD_INDIR_WREG,
    CMD_GET_INFO,
    CMD_TS_CTRL,
    CMD_TUNER_CFG,
    CMD_TUNER_GET,
    CMD_TUNED_VALUE,

    CMD_MAX_NUM
}E_CMD_CODE;

typedef enum
{
    pc_op_code = 0,
    pc_if_freq,
    pc_sound_sys,
    pc_vif_vga_maximum_l,
    pc_vif_vga_maximum_h,
    pc_scan_mode,
    pc_vif_top,
    pc_gain_distribution_thr_l,
    pc_gain_distribution_thr_h,

    VIF_PARAM_MAX_NUM
}E_VIF_PARAM;

typedef enum
{
    pc_system = 0,

    SYS_PARAM_MAX_NUM
}E_SYS_PARAM;

typedef enum
{
    SET_IF_FREQ = 0,
    SET_SOUND_SYS,
    VIF_INIT,
    SET_VIF_HANDLER,
    VIF_TOP_ADJUST,

    VIF_CMD_MAX_NUM
}E_VIF_CMD;

typedef enum
{
    TS_PARALLEL = 0,
    TS_SERIAL = 1,

    TS_MODE_MAX_NUM
}E_TS_MODE;

typedef enum
{
    dac_op_code = 0,
    dac_idac_ch0,
    dac_idac_ch1,

    DAC_PARAM_MAX_NUM
}
E_DAC_PARAM;

typedef enum
{
    DAC_RUN_CALI = 0,
    DAC_IDAC_ASSIGN,

    DAC_CMD_MAX_NUM
}
E_DAC_CMD;



typedef struct
{
    U8        cmd_code;
    U8        param[64];
} S_CMDPKTREG;

#if 0
typedef enum
{
    _QPSK        = 0x0,
    _16QAM        = 0x1,
    _64QAM        = 0x2,
}E_CONSTEL;

typedef enum
{
    _CR1Y2        = 0x0,
    _CR2Y3        = 0x1,
    _CR3Y4        = 0x2,
    _CR5Y6        = 0x3,
    _CR7Y8        = 0x4,
}E_CODERATE;
#endif

typedef enum
{
    E_DMD_DVBT_N_PARAM_VERSION = 0x00,    //0x00
    E_DMD_DVBT_N_OP_RFAGC_EN,
    E_DMD_DVBT_N_OP_HUMDET_EN,
    E_DMD_DVBT_N_OP_DCR_EN,
    E_DMD_DVBT_N_OP_IIS_EN,
    E_DMD_DVBT_N_OP_CCI_EN,
    E_DMD_DVBT_N_OP_ACI_EN,
    E_DMD_DVBT_N_OP_IQB_EN,
    E_DMD_DVBT_N_OP_AUTO_IQ_SWAP_EN,      //0x08
    E_DMD_DVBT_N_OP_AUTO_RF_MAX_EN,
    E_DMD_DVBT_N_OP_FORCE_ACI_EN,
    E_DMD_DVBT_N_OP_FIX_MODE_CP_EN,
    E_DMD_DVBT_N_OP_FIX_TPS_EN,
    E_DMD_DVBT_N_OP_AUTO_SCAN_MODE_EN,
    E_DMD_DVBT_N_CFG_RSSI,
    E_DMD_DVBT_N_CFG_ZIF,                 //0x0F

    E_DMD_DVBT_N_CFG_NIF,                 //0x10
    E_DMD_DVBT_N_CFG_LIF,
    E_DMD_DVBT_N_CFG_SAWLESS,
    E_DMD_DVBT_N_CFG_FS_L,
    E_DMD_DVBT_N_CFG_FS_H,
    E_DMD_DVBT_N_CFG_FIF_L,
    E_DMD_DVBT_N_CFG_FIF_H,
    E_DMD_DVBT_N_CFG_FC_L,
    E_DMD_DVBT_N_CFG_FC_H,                //0x18
    E_DMD_DVBT_N_CFG_BW,
    E_DMD_DVBT_N_CFG_MODE,
    E_DMD_DVBT_N_CFG_CP,
    E_DMD_DVBT_N_CFG_LP_SEL,
    E_DMD_DVBT_N_CFG_CSTL,
    E_DMD_DVBT_N_CFG_HIER,
    E_DMD_DVBT_N_CFG_HPCR,                //0x1F

    E_DMD_DVBT_N_CFG_LPCR,                //0x20
    E_DMD_DVBT_N_CFG_IQ_SWAP,
    E_DMD_DVBT_N_CFG_RFMAX,
    E_DMD_DVBT_N_CFG_CCI,
    E_DMD_DVBT_N_CFG_ICFO_RANGE,
    E_DMD_DVBT_N_CFG_RFAGC_REF,
    E_DMD_DVBT_N_CFG_IFAGC_REF_2K,
    E_DMD_DVBT_N_CFG_IFAGC_REF_8K,
    E_DMD_DVBT_N_CFG_IFAGC_REF_ACI,       //0x28
    E_DMD_DVBT_N_CFG_IFAGC_REF_IIS,
    E_DMD_DVBT_N_CFG_IFAGC_REF_2K_H,
    E_DMD_DVBT_N_CFG_IFAGC_REF_8K_H,
    E_DMD_DVBT_N_CFG_IFAGC_REF_ACI_H,
    E_DMD_DVBT_N_CFG_IFAGC_REF_IIS_H,
    E_DMD_DVBT_N_CFG_TS_SERIAL,
    E_DMD_DVBT_N_CFG_TS_CLK_INV,          //0x2F

    E_DMD_DVBT_N_CFG_TS_DATA_SWAP,        //0x30
    E_DMD_DVBT_N_CFG_8M_DACI_DET_TH_L,
    E_DMD_DVBT_N_CFG_8M_DACI_DET_TH_H,
    E_DMD_DVBT_N_CFG_8M_ANM1_DET_TH_L,
    E_DMD_DVBT_N_CFG_8M_ANM1_DET_TH_H,
    E_DMD_DVBT_N_CFG_8M_ANP1_DET_TH_L,
    E_DMD_DVBT_N_CFG_8M_ANP1_DET_TH_H,
    E_DMD_DVBT_N_CFG_7M_DACI_DET_TH_L,
    E_DMD_DVBT_N_CFG_7M_DACI_DET_TH_H,    //0x38
    E_DMD_DVBT_N_CFG_7M_ANM1_DET_TH_L,
    E_DMD_DVBT_N_CFG_7M_ANM1_DET_TH_H,
    E_DMD_DVBT_N_CFG_7M_ANP1_DET_TH_L,
    E_DMD_DVBT_N_CFG_7M_ANP1_DET_TH_H,
    E_DMD_DVBT_N_IFAGC_REF_READ,
    E_DMD_DVBT_N_IFAGC_K,
    E_DMD_DVBT_N_AGC_IF_GAIN_MIN,         //0x3F

    E_DMD_DVBT_N_AGC_IF_GAIN_MAX,         //0x40
    E_DMD_DVBT_N_AGC_LOCK_TH,
    E_DMD_DVBT_N_AGC_LOCK_NUM,
    E_DMD_DVBT_N_ADC_PGA_GAIN_I,
    E_DMD_DVBT_N_ADC_PGA_GAIN_Q,
    E_DMD_DVBT_N_PWDN_ADCI,
    E_DMD_DVBT_N_PWDN_ADCQ,
    E_DMD_DVBT_N_MPLL_ADC_DIV_SEL,
    E_DMD_DVBT_N_DCR_LOCK,                //0x48
    E_DMD_DVBT_N_MIXER_IQ_SWAP_MODE,
    E_DMD_DVBT_N_CCI_BYPASS,
    E_DMD_DVBT_N_CCI_LOCK_DET,
    E_DMD_DVBT_N_CCI_FSWEEP_L,
    E_DMD_DVBT_N_CCI_FSWEEP_H,
    E_DMD_DVBT_N_CCI_KPKI,
    E_DMD_DVBT_N_INTP_RATEM1_0,           //0x4F

    E_DMD_DVBT_N_INTP_RATEM1_1,           //0x50
    E_DMD_DVBT_N_INTP_RATEM1_2,
    E_DMD_DVBT_N_INTP_RATEM1_3,
    E_DMD_DVBT_N_8K_MC_MODE,
    E_DMD_DVBT_N_8K_MC_CP,
    E_DMD_DVBT_N_8K_MC_CPOBS_NUM,
    E_DMD_DVBT_N_8K_MODECP_DET,
    E_DMD_DVBT_N_2K_MC_MODE,
    E_DMD_DVBT_N_2K_MC_CP,                //0x58
    E_DMD_DVBT_N_2K_MC_CPOBS_NUM,
    E_DMD_DVBT_N_2K_MODECP_DET,
    E_DMD_DVBT_N_ICFO_SCAN_WINDOW_L,
    E_DMD_DVBT_N_ICFO_SCAN_WINDOW_H,
    E_DMD_DVBT_N_ICFO_MAX_OFFSET_L,
    E_DMD_DVBT_N_ICFO_MAX_OFFSET_H,
    E_DMD_DVBT_N_ICFO_DONE,               //0x5F

    E_DMD_DVBT_N_TPS_SYNC_LOCK,           //0x60
    E_DMD_DVBT_N_CONSTELLATION,
    E_DMD_DVBT_N_HIERARCHY,
    E_DMD_DVBT_N_HP_CODE_RATE,
    E_DMD_DVBT_N_LP_CODE_RATE,
    E_DMD_DVBT_N_GUARD_INTERVAL,
    E_DMD_DVBT_N_TRANSMISSION_MODE,
    E_DMD_DVBT_N_OFDM_SYMBOL_NUMBER,
    E_DMD_DVBT_N_LENGTH_INDICATOR,        //0x68
    E_DMD_DVBT_N_FRAME_NUMBER,
    E_DMD_DVBT_N_CELL_IDENTIFIER,
    E_DMD_DVBT_N_DVBH_SIGNALLING,
    E_DMD_DVBT_N_SNR_2K_ALPHA,
    E_DMD_DVBT_N_SNR_8K_ALPHA,
    E_DMD_DVBT_N_TS_EN,
    E_DMD_DVBT_N_2K_DAGC1_REF,            //0x6F

    E_DMD_DVBT_N_8K_DAGC1_REF,            //0x70
    E_DMD_DVBT_N_2K_8K_DAGC2_REF,
    E_DMD_DVBT_N_IF_INV_PWM_OUT_EN,
    E_DMD_DVBT_N_RESERVE_0,
    E_DMD_DVBT_N_RESERVE_1,
    E_DMD_DVBT_N_RESERVE_2,
    E_DMD_DVBT_N_RESERVE_3,
    E_DMD_DVBT_N_RESERVE_4,
    E_DMD_DVBT_N_RESERVE_5,               //0x78
    E_DMD_DVBT_N_RESERVE_6,
    E_DMD_DVBT_N_RESERVE_7,
    E_DMD_DVBT_N_RESERVE_8,
    E_DMD_DVBT_N_RESERVE_9,
    E_DMD_DVBT_N_RESERVE_10,
    E_DMD_DVBT_N_RESERVE_11,              //0x7E
}DVBT_N_Param;
//--------------------------------------------------------------------
typedef struct
{
    U8        constel;
    U8        code_rate;
    float    cn_ref;
}S_SQI_CN_NORDIGP1_INTERN_DVBT;

typedef struct
{
    float    power_db;
    U8        sar3_val;
}S_INTERN_DVBT_RFAGC_SSI;

typedef struct
{
    float    power_db;
    U8        agc_val;
}S_INTERN_DVBT_IFAGC_SSI;

typedef struct
{
    U8        constel;
    U8        code_rate;
    float    p_ref;
}S_INTERN_DVBT_SSI_PREF;

typedef struct
{
    float    attn_db;
    U8        agc_err;
}S_INTERN_DVBT_IFAGC_ERR;
//--------------------------------------------------------------------
EXTSEL BOOLEAN INTERN_DVBT_Reset ( void );
EXTSEL BOOLEAN INTERN_DVBT_Active(BOOLEAN bEnable);
EXTSEL BOOLEAN INTERN_DVBT_Cmd_Packet_Send(S_CMDPKTREG* pCmdPacket, U8 param_cnt);
EXTSEL BOOLEAN INTERN_DVBT_Get_TPS_Parameter_Const( WORD * TSP_parameter);
EXTSEL BOOLEAN INTERN_DVBT_Exit ( void );
EXTSEL BOOLEAN INTERN_DVBT_ReadReg(U16 u16Addr, U8 *pu8Data);
EXTSEL BOOLEAN INTERN_DVBT_WriteReg(U32 u16Addr, U8 u8Data);
EXTSEL U8 INTERN_DVBT_GetDspStatus(void);
EXTSEL BOOLEAN INTERN_DVBT_GetPostViterbiBer(float *ber);
EXTSEL BOOLEAN INTERN_DVBT_Power_On_Initialization ( void );
EXTSEL void INTERN_DVBT_Power_ON_OFF(U8 bPowerOn);
EXTSEL BOOLEAN INTERN_DVBT_Lock( COFDM_LOCK_STATUS eStatus );
EXTSEL BOOLEAN INTERN_DVBT_Config ( RF_CHANNEL_BANDWIDTH BW, BOOLEAN bSerialTS, BOOLEAN bPalBG, BOOLEAN bLPSel);
EXTSEL FUNCTION_RESULT INTERN_DVBT_GetSignalQuality(U16 *quality);
EXTSEL float INTERN_DVBT_GetSNR (void);
EXTSEL BOOLEAN INTERN_DVBT_Serial_Control(BOOLEAN bEnable);
EXTSEL void INTERN_DVBT_PAD_TS1_Enable(BOOLEAN flag);
EXTSEL FUNCTION_RESULT INTERN_DVBT_GetSignalStrength(U16 *strength);

//EXTSEL void MDrv_1210_IIC_Bypass_Mode(BOOLEAN enable);
//--------------------------------------------------------------------

//#endif

/* Use new option to control load code ==> INTERN_DVBT_LOAD_CODE_FROM_SEL
#if(  (CHIP_FAMILY_TYPE == CHIP_FAMILY_EULER)   \
    ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_EMERALD) \
   )
    #define INTERN_DVBT_LOAD_FW_FROM_CODE_MEMORY
#endif
*/

#undef EXTSEL
#endif

