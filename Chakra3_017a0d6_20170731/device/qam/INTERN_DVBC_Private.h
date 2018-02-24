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

#ifndef _INTERN_DVBC_PRIVATE_H_
#define _INTERN_DVBC_PRIVATE_H_

//--------------------------------------------------------------------

// #define     DEMOD_DYNAMIC_SLAVE_ID_1          0x32
// #define     DEMOD_DYNAMIC_SLAVE_ID_2          0x72
// #define     DEMOD_DYNAMIC_SLAVE_ID_3          0xB2
// #define     DEMOD_DYNAMIC_SLAVE_ID_4          0xF2

#define     DEMOD_ADDR_H            0x00
#define     DEMOD_ADDR_L            0x01
#define     DEMOD_WRITE_REG         0x02
#define     DEMOD_WRITE_REG_EX      0x03
#define     DEMOD_READ_REG          0x04
#define     DEMOD_RAM_CONTROL       0x05

// #define INTERN_DVBC_IIC_CONTROL                 0x8400
// #define INTERN_DVBC_IIC_SCL_CLK                 0x8401
// #define INTERN_DVBC_IIC_READ_DATA               0x8402
// #define INTERN_DVBC_IIC_STATUS                  0x8403
// #define INTERN_DVBC_IIC_WRITE_DATA              0x8404

// #define     COFDM_DEM_I2C_ID            DEMOD_DYNAMIC_SLAVE_ID_1
// #define     COFDM_DEM_I2C_ID_2          DEMOD_DYNAMIC_SLAVE_ID_2
// #define     COFDM_DEM_I2C_ID_3          DEMOD_DYNAMIC_SLAVE_ID_3
// #define     COFDM_DEM_I2C_ID_4          DEMOD_DYNAMIC_SLAVE_ID_4

// #define INTERN_DVBC_REG_INVERSION              0x8024
#define BOOL    BOOLEAN

#if  DTV_SCAN_AUTO_FINE_TUNE_ENABLE
    //INTERN_DVBC_ Capture Range fix to 500K
    #define DEMOD_CAPTURE_RANGE_500_K            500
        #define DEMOD_CAPTURE_RANGE_SIZE                                      DEMOD_CAPTURE_RANGE_500_K
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

typedef enum
{
    agc_ref_small,
    agc_ref_large,
    agc_ref_aci,
    ripple_switch_th_l,
    ripple_switch_th_h,

    TUNED_PARAM_MAX_NUM
}E_TUNED_PARAM;


typedef struct
{
    U8        cmd_code;
    U8        param[64];
} S_CMDPKTREG;

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) 		//T3
	#define REG_CMD_CTRL    0x20CC
	#define REG_DTA_CTRL    0x20CD
	#define REG_CMD_ADDR    0x20CE
	#define REG_CMD_DATA    0x20CF
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) 	//T4
	#define REG_CMD_CTRL    0x2F1C
	#define REG_DTA_CTRL    0x2F1D
	#define REG_CMD_ADDR    0x2F1E
	#define REG_CMD_DATA    0x2F1F
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) 	//A7
	#define REG_CMD_CTRL    0x2F1C
	#define REG_DTA_CTRL    0x2F1D
	#define REG_CMD_ADDR    0x2F1E
	#define REG_CMD_DATA    0x2F1F
#endif

#define _REG_START      REG_CMD_CTRL
#define _REG_END        REG_CMD_CTRL
#define _REG_DRQ        REG_DTA_CTRL
#define _REG_FSM        REG_CMD_CTRL
#define _REG_ERR        REG_DTA_CTRL

#define _BIT_START      BIT1
#define _BIT_END        BIT0
#define _BIT_DRQ        BIT0
#define _BIT_FSM        BIT3
#define _BIT_ERR        BIT7

//--------------------------------------------------------------------
typedef enum
{	

#if ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7 ) //T3
    // OP Mode Settings
    p_opmode_rfagc_en = 0,
    p_opmode_humdet_en,
    p_opmode_dcr_en,
    p_opmode_iqb_en,
    p_opmode_auto_iq_swap,
    p_opmode_auto_fsa_left,
    p_opmode_auto_rfmax,
    p_opmode_mode_forced,
    p_opmode_cp_forced,

    // Config Params
    pc_config_rssi,
    pc_config_zif,
    pc_config_fc_l,
    pc_config_fc_h,
    pc_config_fs_l,
    pc_config_fs_h,
    pc_config_bw,
    pc_config_fsa_left,
    pc_config_rfmax,
    pc_config_lp_sel,
    pc_config_cp,
    pc_config_mode,
    pc_config_iq_swap,
    pc_config_atv_system,
    pc_config_serial_ts,
    pc_config_ts_out_inv,
    pc_config_ts_data_swap,
    pc_config_icfo_range,

	DVBT_PARAM_LEN,

#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S7LD ) //T4	

	// Operation Mode Settings
	p_opmode_rfagc_en,
	p_opmode_humdet_en,
	p_opmode_dcr_en,
	p_opmode_iqb_en,
	p_opmode_auto_iq,
	p_opmode_auto_rfmax,
	p_opmode_auto_aci,
	p_opmode_auto_scan,
	p_opmode_auto_scan_sym_rate,
	p_opmode_auto_scan_qam,
	p_opmode_rsv_0x0A,
	p_opmode_rsv_0x0B,
	p_opmode_rsv_0x0C,
	p_opmode_rsv_0x0D,
	p_opmode_rsv_0x0E,
	p_opmode_rsv_0x0F,

	// Config Params
	pc_config_rssi,
	pc_config_zif,
	pc_config_freq,
	pc_config_fc_l,
	pc_config_fc_h,
	pc_config_fs_l,
	pc_config_fs_h,
	pc_config_bw_l,
	pc_config_bw_h,
	pc_config_bw1_l,
	pc_config_bw1_h,
	pc_config_bw2_l,
	pc_config_bw2_h,
	pc_config_bw3_l,
	pc_config_bw3_h,    
	pc_config_rsv_0x1F,
	pc_config_rfmax,
	pc_config_qam,
	pc_config_iq_swap,
	pc_config_cci,
	pc_config_ts_serial,
	pc_config_ts_clk_rate,
	pc_config_ts_out_inv,
	pc_config_ts_data_swap,
	pc_config_post_dagc_gain_diff_th,
	pc_config_pre_dagc_gain_diff_th,
	
	DVBC_PARAM_LEN,
#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_A7 ) //A7	

	// Operation Mode Settings
	p_opmode_rfagc_en,
	p_opmode_humdet_en,
	p_opmode_dcr_en,
	p_opmode_iqb_en,
	p_opmode_auto_iq,
	p_opmode_auto_rfmax,
	p_opmode_auto_aci,
	p_opmode_auto_scan,
	p_opmode_auto_scan_sym_rate,
	p_opmode_auto_scan_qam,
	p_opmode_rsv_0x0A,
	p_opmode_rsv_0x0B,
	p_opmode_rsv_0x0C,
	p_opmode_rsv_0x0D,
	p_opmode_rsv_0x0E,
	p_opmode_rsv_0x0F,

	// Config Params
	pc_config_rssi,
	pc_config_zif,
	pc_config_freq,
	pc_config_fc_l,
	pc_config_fc_h,
	pc_config_fs_l,
	pc_config_fs_h,
	pc_config_bw_l,
	pc_config_bw_h,
	pc_config_bw1_l,
	pc_config_bw1_h,
	pc_config_bw2_l,
	pc_config_bw2_h,
	pc_config_bw3_l,
	pc_config_bw3_h,    
	pc_config_rsv_0x1F,
	pc_config_rfmax,
	pc_config_qam,
	pc_config_iq_swap,
	pc_config_cci,
	pc_config_ts_serial,
	pc_config_ts_clk_rate,
	pc_config_ts_out_inv,
	pc_config_ts_data_swap,
       pc_config_lif,			// 0x28
       pc_config_Fif_L,					// 0x29
       pc_config_Fif_H,					// 0x2A
	
	DVBC_PARAM_LEN,
	
	#elif ( CHIP_FAMILY_TYPE == CHIP_FAMILY_S8 ) //T8
	// Operation Mode Settings
	p_opmode_rfagc_en,
	p_opmode_humdet_en,
	p_opmode_dcr_en,
	p_opmode_iqb_en,
	p_opmode_auto_iq,
	p_opmode_auto_rfmax,
	p_opmode_auto_aci,
	p_opmode_auto_scan,
	p_opmode_auto_scan_sym_rate,
	p_opmode_auto_scan_qam,
	p_opmode_rsv_0x0A,
	p_opmode_rsv_0x0B,
	p_opmode_rsv_0x0C,
	p_opmode_rsv_0x0D,
	p_opmode_rsv_0x0E,
	p_opmode_rsv_0x0F,

	// Config Params
	pc_config_rssi,
	pc_config_zif,
	pc_config_freq,
	pc_config_fc_l,
	pc_config_fc_h,
	pc_config_fs_l,
	pc_config_fs_h,
	pc_config_bw_l,
	pc_config_bw_h,
	pc_config_bw1_l,
	pc_config_bw1_h,
	pc_config_bw2_l,
	pc_config_bw2_h,
	pc_config_bw3_l,
	pc_config_bw3_h,    
	pc_config_rsv_0x1F,
	pc_config_rfmax,
	pc_config_qam,
	pc_config_iq_swap,
	pc_config_cci,
	pc_config_ts_serial,
	pc_config_ts_clk_rate,
	pc_config_ts_out_inv,
	pc_config_ts_data_swap,

	DVBC_PARAM_LEN,
#endif 

} DVBT_Param;

//--------------------------------------------------------------------
BOOLEAN INTERN_DVBC_Reset ( void );
BOOLEAN INTERN_DVBC_Cmd_Packet_Send(S_CMDPKTREG* pCmdPacket, U8 param_cnt);
BOOLEAN INTERN_DVBC_Get_TPS_Parameter_Const( WORD * TSP_parameter);
//--------------------------------------------------------------------

#endif

