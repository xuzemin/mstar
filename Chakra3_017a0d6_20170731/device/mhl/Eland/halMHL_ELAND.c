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
///////////////////////////////////////////////////////////////////////////////////////////////////
///
/// file    MST_ELAND_HAL.c.c
/// @author MStar Semiconductor Inc.
/// @brief  MHL HAL Function
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _HAL_MHL_ELAND_C_
#define _HAL_MHL_ELAND_C_

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
// Common Definition
#include "MsCommon.h"
#include "MsVersion.h"
#ifdef MSOS_TYPE_LINUX_KERNEL
#include <linux/string.h>
#else
#include <string.h>
#endif

#include "halMHL_ELAND_Reg.h"
#include "halMHL_ELAND.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define msg_mhl(x) x

#define DMHLInit    0

#define LB(x) x
#define HB(x) x+1

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

typedef struct
{
    MS_U32 addr;
    MS_U16 mask;
    MS_U16 databuf;
} msLoadTbl_S;

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
MS_U8 ucMHLSupportPort = E_MUX_NOT_SUPPORT_MHL;
MS_U8 ucMHLDriver = MHL_DRIVER_VERSION;

static link_mhl_reg_i_func_b s_gpfnMApi_SWI2C_ReadBytes = NULL;
static link_mhl_reg_o_func_b s_gpfnMApi_SWI2C_WriteBytes = NULL;

static MS_U16 s_gu16MHL_I2C_Channel = 0;
// This could be a real ID or a index.
static MS_U8 s_gu8MHL_I2C_Slave_ID_Common = 0;
static MS_U8 s_gu8MHL_I2C_Slave_ID_Config = 0;

#define MHL_I2CBUS_ADDR         (s_gu16MHL_I2C_Channel<<8 | s_gu8MHL_I2C_Slave_ID_Common)
#define MHL_CFG_I2CBUS_ADDR     (s_gu16MHL_I2C_Channel<<8 | s_gu8MHL_I2C_Slave_ID_Config)

//-------------------------------------------------------------------------------------------------
//  MHL initial table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_INITIAL_TABLE[] =
{
#if DMHLInit
    {REG_CHIPTOP_06, 0xFFFF, 0x1080}, // [12:8]: ckg_mhl_out, MHL 24 bits mode, Eland internal 12M RC clock **
#else
    {REG_CHIPTOP_06, 0xFFEF, 0x0000}, // [12:8]: ckg_mhl_out, MHL packed-pixel mode
#endif
//Vincent comment
//    {REG_CHIPTOP_2C, 0xFFFF, 0x0480}, // JunoE MHL Rx and HDMITx pad mux setting **
//    {REG_CHIPTOP_2D, 0xFFFF, 0x2103}, // JunoE MHL Rx and HDMITx pad mux setting **
//    {REG_CHIPTOP_2E, 0xFFFF, 0x0006}, // JunoE MHL Rx and HDMITx pad mux setting **
//Vincent add
    {REG_CHIPTOP_2D, BIT(13)|BIT(10), BIT(13)}, // [13]: reg_mhlrx_cable_det_en, [10]: reg_all_pad_in
    {REG_CHIPTOP_2E, BIT(5), BIT(5)}, // [5]: reg_qfn40_mode(SI mode)

#if DMHLInit
    {REG_DVI_DTOP_27, 0xFFFF, 0x016D/*0x2C6D*/}, // [7]: MHL HW mode, [1]: MHL pack-pixel mode, [0]: MHL enable
#else // HDMIBypass
    {REG_DVI_DTOP_27, 0xFFFF, 0x2C6C}, // [7]: MHL HW mode, [1]: MHL pack-pixel mode, [0]: MHL enable
#endif
    {REG_DVI_DTOP_28, 0xFFFF, 0x0000}, // [14]: MHL pack to HDMI, [13]: MHL pack video swap
    {REG_DVI_DTOP_13, 0x7FFF, 0x2C80}, // [14:12]: the comp value is reg_comp_tol * 4, [11:0]: 300MHz
    {REG_DVI_DTOP_12, 0xF000, 0xF000}, // [15]: reg_comp_tol_en, [14:12]: reg_comp_tol = 0x7
    {REG_DVI_DTOP_1F, 0x0700, 0x0700}, // [10:8] : clock unstable count threshold = 0x07
    {REG_DVI_ATOP_00, 0xFFFF, 0x0010}, // [4]: enable DVI
    {REG_DVI_ATOP_03, BIT(13)|BIT(8)|BIT(0), 0x0000}, // clock powe on, [13]: PD_ICLK, [8]: PD_CLKD_DVI
    {REG_DVI_ATOP_60, 0xFFFF, 0x0000}, // DVI port A PLL power on
//Vincent comment    {REG_DVI_ATOP_61, 0x000F, 0x000A}, // [3:2]: [1:0] RX swap for JunoE **
    {REG_DVI_ATOP_69, 0xC7FF, 0x0000}, // DVI port C PLL power on
    {REG_DVI_ATOP_6C, BIT(1), BIT(1)}, // reg_en_cal2=1b1
    {REG_DVI_ATOP_6D, 0xFBFF, 0x0000}, // DVI PM port C power on
    {REG_DVI_ATOP_7F, 0xFFFF, 0x0000}, // DVI DPL power on
    {REG_HDMITX_MISC_5A, 0xFFFF, 0x001F}, // [13:12]: Tx div mode
    {REG_HDMITX_MISC_1E, 0xFFFF, 0xFFFF}, // enable clock gen
    {REG_HDMITX_MISC_2A, 0xFFFF, 0x0000}, // [3:0]: TMDS Tx power down
    {REG_HDMITX_MISC_2B, 0xFFFF, 0x0000}, // analog test register
    {REG_HDMITX_MISC_2C, 0xFFFF, 0x0001}, // analog test register
    {REG_HDMITX_MISC_2D, 0xFFFF, 0x0000}, // analog test register
    {REG_HDMITX_MISC_58, 0xFFFF, 0x0002}, // [1]: enable new FIFO
  //#if HDMI_TX_SWAP
    //{REG_HDMITX_MISC_5B, 0x1800, 0x1800}, // [12:11] = 2'b 11 HDMI Tx swap for JunoE **
  //#endif
    {REG_HDMITX_MISC_2E, 0xFFFF, 0x000F}, // [3:0]: enable TMDS Tx
    {REG_MHL_CBUS_18, BIT(7), BIT(7)}, // [7]: reg_hdcp_mhlcbus2iic_en, HDCP bypass mode

    {REG_CBUS2I2C_08, 0xFFFF, 0x000A}, // reg_stop_cnt = 'ha
    {REG_CBUS2I2C_09, 0xFFFF, 0x0014}, // reg_hcnt = h14
    {REG_CBUS2I2C_0A, 0xFFFF, 0x000A}, // reg_lcnt =ha
    {REG_CBUS2I2C_0B, 0xFFFF, 0x0002}, // reg_sda_cnt = h2
    {REG_CBUS2I2C_0C, 0xFFFF, 0x000A}, // reg_start_cnt = ha
    {REG_CBUS2I2C_0D, 0xFFFF, 0x0004}, // reg_data_lat_cnt = h4
    {REG_CBUS2I2C_00, BIT(0), BIT(0)}, // [0]: soft reset
    {REG_CBUS2I2C_00, BIT(0), 0}, // [0]: soft reset

    {REG_DVI_ATOP_65, BIT(1), BIT(1)},  //0465[1]=1
    {REG_DVI_ATOP_5B, BMASK(7:4), BIT(5)},  // 045B[7:4]=4'b0010

    // Set accepted discover pulse high pulse width to ignore USB pulse
    {REG_PM_MHL_CBUS_0C, BMASK(15:0), 0x0046}, // reject cbus discovery pulse below this limit
    {REG_PM_MHL_CBUS_0D, BMASK(15:0), 0x0082}, // reject cbus discovery pulse above this limit
    // CTS 4.3.7.1
    {REG_MHL_CBUS_55, BMASK(7:4), BIT(4)}, // [7:4]: cbus requester transmit opportunity after arbitration
    {REG_MHL_CBUS_70, BIT(14), BIT(14)}, // [14]: let edid current read initial address add 1
    {REG_PM_MHL_CBUS_21, BIT(1), BIT(1)}, // [1]: output mhl_zxsense_tmds inv

#if DMHL_INT_ENABLE
    // Mask unused interrupt events
    {REG_PM_MHL_CBUS_16, BIT(13)|BIT(9), BIT(13)|BIT(9)}, // [13]: lnk_lay_en_chg_int mask, [9]: conn_state_chg_int mask
    {REG_PM_MHL_CBUS_18, BIT(9)|BIT(5)|BIT(1), BIT(9)|BIT(5)|BIT(1)}, // [9]: cbus_discover_pul_confirm_int mask, [5]: wakeup_pul_confirm_int mask, [1]: cbus_stuck_to_low_int mask.
    {REG_PM_MHL_CBUS_30, BIT(1), BIT(1)}, // [1]: cbus conflict_int mask
    {REG_PM_MHL_CBUS_38, BIT(13)|BIT(9)|BIT(5)|BIT(1), BIT(13)|BIT(9)|BIT(5)|BIT(1)}, // [13]: unused mask, [9]: unused mask, [5]: unused mask, [1]: unused mask.
    {REG_MHL_CBUS_14, BIT(13), BIT(13)}, // [13]: int mask for monitor_sram_full
    {REG_MHL_CBUS_18, BIT(13), BIT(13)}, // [13]: send rcv_pkt_ddc_sw_overwrite_err_in mask
    {REG_MHL_CBUS_19, BIT(5)|BIT(1), BIT(5)|BIT(1)}, // [5]: send ddc send complete interrupt mask, [1]: send ddc error interrupt mask
    {REG_MHL_CBUS_1B, BIT(1), BIT(1)}, // [1]: receive ddc packet valid mask
    {REG_MHL_CBUS_1F, BIT(5)|BIT(1), BIT(5)|BIT(1)}, // [5]: ddc access edid timeout int mask, [1]: client_wrt_ddc_ram interrupt mask
    {REG_MHL_CBUS_21, BIT(5), BIT(5)}, // [5]: ddc error interrupt mask
    {REG_MHL_CBUS_22, BIT(9)|BIT(5)|BIT(1), BIT(9)|BIT(5)|BIT(1)}, // [9]: ddc access hdcp timeout int mask, [5]: receive nack pkt int_mask, [1]: receive abort pkt int mask
    {REG_MHL_CBUS_23, BIT(13), BIT(13)}, // [13]: send rcv_pkt_msc_sw_overwrite_err_in mask
    {REG_MHL_CBUS_24, BIT(1), BIT(1)}, // [1]: send error interrupt mask
    {REG_MHL_CBUS_25, BIT(9)|BIT(5)|BIT(1), BIT(9)|BIT(5)|BIT(1)}, // [9]: response_pkt_msc_hw_int mask, [5]: snd_pkt_msc_hw_int mask, [1]: msc sw send complete interrupt mask
    {REG_MHL_CBUS_63, BIT(9), BIT(9)}, // [9]: dytycycle_bad_int mask
    {REG_MHL_CBUS_65, BIT(9)|BIT(5)|BIT(1), BIT(9)|BIT(5)|BIT(1)}, // [9]: rcv_parity_err_int mask, [5]: rcv_data_err_int mask, [1]: rcv_sync_err_int mask
    {REG_MHL_CBUS_78, BIT(13)|BIT(9)|BIT(5)|BIT(1), BIT(13)|BIT(9)|BIT(5)|BIT(1)}, // [13]: unused mask, [9]: unused mask, [5]: unused mask, [1]: unused mask.
#endif
};

//-------------------------------------------------------------------------------------------------
//  MHL HDMI bypass table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_HDMI_BYPASS_TABLE[] =
{
    {REG_CHIPTOP_06, 0xFFEF, 0x0000}, // [12:8]: ckg_mhl_out, MHL packed-pixel mode
    // switch to CDR mode
    {REG_DVI_DTOP_0E, BIT(4), BIT(4)}, // auto clear phase accumulator
    {REG_DVI_DTOP_3B, BIT(4), 0}, // overwirte enable
    {REG_DVI_DTOP_3D, BIT(4), 0}, // overwirte enable
    {REG_DVI_DTOP_3F, BIT(4), 0}, // overwirte enable
    {REG_DVI_DTOP_41, 0x7FFF, 0x1CE7}, // Fix long HDMI cable problem(EQ strength)
    {REG_DVI_ATOP_64, BIT(9)|BIT(7), 0}, // DVI DPL test register [39][9][7] = 1
    {REG_DVI_ATOP_66, BIT(7), 0},
    {REG_DVI_ATOP_69, BIT(7), 0}, // [7]: power on DVI PLL
//Vincent comment    {REG_DVI_ATOP_61, 0x000F, 0x000A}, // [3:2]: [1:0] RX swap for JunoE **
    {REG_DVI_ATOP_69, 0x0007, 0}, // [2:0]: power on TMDS ch1/2 EQ
    {REG_DVI_ATOP_7F, 0x3F00, 0x0000}, // power on TMDS ch1&2 phase dac, [13:11]: PDN_DPLPH_Q2, [10:8]: PDN_DPLPH_I2
//Vincent comment    {REG_DVI_DTOP_0C, BIT(9)|BIT(1)|BIT(0), 0x0000}, // R-term overwrite disable
    {REG_DVI_DTOP_27, 0xFFFF, 0x2C6C}, // [7]: MHL HW mode, [1]: MHL pack-pixel mode, [0]: MHL enable
    {REG_DVI_DTOP_28, 0xFFFF, 0x0000}, // [14]: MHL pack to HDMI, [13]: MHL pack video swap
    {REG_HDMITX_MISC_5A, 0xFFFF, 0x001F}, // [13:12]: Tx div mode
};

//-------------------------------------------------------------------------------------------------
//  MHL 24 bit mode table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_24BIT_MODE_TABLE[] =
{
    {REG_CHIPTOP_06, 0xFFEF, 0x1000}, // [12:8]: ckg_mhl_out, MHL 24 bits mode
    // switch to CDR mode
    {REG_DVI_DTOP_0E, BIT(4), 0}, // auto clear phase accumulator
    {REG_DVI_DTOP_3A, 0xFFFF, 0x18}, // phase code = 0x18
    {REG_DVI_DTOP_3B, BIT(4), BIT(4)}, // overwirte enable
    {REG_DVI_DTOP_3C, 0xFFFF, 0x18}, // phase code = 0x18
    {REG_DVI_DTOP_3D, BIT(4), BIT(4)}, // overwirte enable
    {REG_DVI_DTOP_3E, 0xFFFF, 0x18}, // phase code = 0x18
    {REG_DVI_DTOP_3F, BIT(4), BIT(4)}, // overwirte enable    
    {REG_DVI_DTOP_41, 0x7FFF, 0x0842}, // Fix long HDMI cable problem(EQ strength)
    {REG_DVI_ATOP_64, BIT(9)|BIT(7), BIT(9)|BIT(7)}, // DVI DPL test register [39][9][7] = 1
    {REG_DVI_ATOP_66, BIT(7), BIT(7)},
    {REG_DVI_ATOP_69, 0x0007, 0x06}, // [2:0]: power down TMDS ch1/2 EQ
    {REG_DVI_ATOP_7F, 0x3F00, 0x3600}, // power down TMDS ch1&2 phase dac, [13:11]: PDN_DPLPH_Q2, [10:8]: PDN_DPLPH_I2
    {REG_DVI_DTOP_27, 0xFFFF, 0x016D/*0x2C6D*/}, // [7]: MHL HW mode, [1]: MHL pack-pixel mode, [0]: MHL enable
    {REG_DVI_DTOP_28, 0xFFFF, 0x0000}, // [14]: MHL pack to HDMI, [13]: MHL pack video swap
    {REG_HDMITX_MISC_5A, 0xFFFF, 0x201F}, // [13:12]: Tx div mode
};

//-------------------------------------------------------------------------------------------------
//  MHL packet pixel mode table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_PACKET_PIXEL_MODE_TABLE[] =
{
    {REG_CHIPTOP_06, 0xFFEF, 0x0800}, // [12:8]: ckg_mhl_out, MHL packed-pixel mode
//Vincent comment    {REG_DVI_DTOP_0C, BIT(9)|BIT(1)|BIT(0), BIT(9)|BIT(0)}, // R-term overwrite to MHL R-term
    {REG_DVI_DTOP_27, 0xFFFF, 0x2C6F}, // [7]: MHL HW mode, [1]: MHL pack-pixel mode, [0]: MHL enable
    {REG_DVI_DTOP_28, 0xFFFF, 0x4000}, // [14]: MHL pack to HDMI, [13]: MHL pack video swap
    {REG_HDMITX_MISC_5A, 0xFFFF, 0x101F}, // [13:12]: Tx div mode
};

//-------------------------------------------------------------------------------------------------
//  MHL power on table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_POWER_ON_TABLE[] =
{
    {REG_DVI_ATOP_03, BIT(13)|BIT(8)|BIT(0), 0}, // clock powe on
    //{REG_DVI_ATOP_69, 0x38A7, 0}, // DVI port C PLL power on
    {REG_DVI_ATOP_69, 0x00A7, 0}, // DVI port C PLL power on
    {REG_DVI_ATOP_7F, 0x3F00, 0}, // DVI DPL power on
    //{REG_DVI_ATOP_6D, 0x0D00, 0}, // DVI PM port C power on
    {REG_DVI_ATOP_6D, 0x0900, 0}, // DVI PM port C power on
    //{REG_DVI_DTOP_27, BIT(0), 0}, // [0]: MHL enable
    {REG_HDMITX_MISC_1E, 0x0006, 0x0006}, // [2]: PD_TX_XTAL, [1]: PD_TX_ICLK
    {REG_HDMITX_MISC_2A, 0x000F, 0}, // [3:0]: TMDS Tx power down
    {REG_HDMITX_MISC_2B, 0x0007, 0x0000}, // analog test register
    {REG_CHIPTOP_06, 0x0178, 0x0010}, // [8]: reg_ckg_mhl_out, [6]: reg_ckg_cbus, [5]: reg_ckg_ddc, [4]: reg_ckg_cec, [3]: reg_ckg_efuse
};

//-------------------------------------------------------------------------------------------------
//  MHL power down table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_POWER_DOWN_TABLE[] =
{
    {REG_DVI_ATOP_03, BIT(13)|BIT(8)|BIT(0), BIT(13)|BIT(8)}, // clock powe on
    //{REG_DVI_ATOP_69, 0x38A7, 0x38A7}, // DVI port C PLL power on
    {REG_DVI_ATOP_69, 0x00A7, 0x00A7}, // DVI port C PLL power on
    {REG_DVI_ATOP_7F, 0x3F00, 0x3F00}, // DVI DPL power on
    //{REG_DVI_ATOP_6D, 0x0D00, 0x0D00}, // DVI PM port C power on
    {REG_DVI_ATOP_6D, 0x0900, 0x0900}, // DVI PM port C power on
    //{REG_DVI_DTOP_27, BIT(0), BIT(0)}, // [0]: MHL enable
    {REG_HDMITX_MISC_1E, 0x0006, 0}, // [2]: PD_TX_XTAL, [1]: PD_TX_ICLK
    {REG_HDMITX_MISC_2A, 0x000F, 0x000F}, // [3:0]: TMDS Tx power down
    {REG_HDMITX_MISC_2B, 0x0007, 0x0007}, // analog test register
    {REG_CHIPTOP_06, 0x0178, 0x0178}, // [8]: reg_ckg_mhl_out, [6]: reg_ckg_cbus, [5]: reg_ckg_ddc, [4]: reg_ckg_cec, [3]: reg_ckg_efuse
};

//-------------------------------------------------------------------------------------------------
//  MHL power saving table
//-------------------------------------------------------------------------------------------------
static msLoadTbl_S tMHL_POWER_SAVING_TABLE[] =
{
    //{REG_DVI_ATOP_03, BIT(13)|BIT(8)|BIT(0), 0}, // clock powe on
    //{REG_DVI_ATOP_69, 0x38A7, 0}, // DVI port C PLL power on
    {REG_DVI_ATOP_7F, 0x3F00, 0x3F00}, // DVI DPL power on
    //{REG_DVI_ATOP_69, 0x38A7, 0x30A6}, // [2:0]: power down TMDS ch1/2 EQ
  #if 0
    {REG_DVI_ATOP_69, 0x00A7, 0x00A6}, // [2:0]: power down TMDS ch1/2 EQ
  #else
    {REG_DVI_ATOP_69, 0x38A7, 0x38A7}, // DVI port C PLL power on
    {REG_DVI_ATOP_6D, 0x0D00, 0x0000},
    {REG_DVI_DTOP_27, 0x0001, 0x0000},
    {REG_DVI_ATOP_03, 0x7F80, 0x7F80},
    {REG_HDMI2_78,    0x0008, 0x0008}, //REG_HDMI2_78
  #endif
    //{REG_DVI_ATOP_6D, 0x0D00, 0x0C00}, // [11]: PD_BG, [10]: PD_RCK, [8]: PD_CLKIN
    //{REG_DVI_DTOP_27, BIT(0), BIT(0)}, // [0]: MHL enable
    {REG_HDMITX_MISC_1E, 0x0006, 0}, // [2]: PD_TX_XTAL, [1]: PD_TX_ICLK
    {REG_HDMITX_MISC_2A, 0x000F, 0x000F}, // [3:0]: TMDS Tx power down
    {REG_HDMITX_MISC_2B, 0x0007, 0x0007}, // analog test register
    {REG_CHIPTOP_06, 0x0178, 0x0010}, // [8]: reg_ckg_mhl_out, [6]: reg_ckg_cbus, [5]: reg_ckg_ddc, [4]: reg_ckg_cec, [3]: reg_ckg_efuse
};

//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------

//**************************************************************************
//  [Function Name]:
//                  _mhal_mhl_IsCbusBusy()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

// MHL 16bits mode
void mhal_mhl_SWI2C_WriteWord(MS_U16 u16BusNumSlaveID, MS_U16 u16addr, MS_U16 u16data)
{
    MS_U8 u8Addr[2];
    MS_U8 u8Data[2];

    //SWI2C_DBG_FUNC();

    u8Addr[0] = (u16addr>>8) & 0xFF; //HiByte
    u8Addr[1] = (u16addr) & 0xFF; //LowByte

    u8Data[0] = (u16data) & 0xFF; //LowByte
    u8Data[1] = (u16data>>8) & 0xFF; //HiByte

    //MApi_SWI2C_WriteBytes(u16BusNumSlaveID, 2, u8Addr, 2, u8Data);
    //MDrv_IIC_WriteBytes(u16BusNumSlaveID, 2, u8Addr, 2, u8Data);
    s_gpfnMApi_SWI2C_WriteBytes(u16BusNumSlaveID, 2, u8Addr, 2, u8Data);
}

MS_U16 mhal_mhl_SWI2C_ReadWord(MS_U16 u16BusNumSlaveID, MS_U16 u16addr)
{
    //SWI2C_DBG_FUNC();

    MS_U8 u8Addr[2]={0,0};
    MS_U8 u8Data[2]={0,0};

    u8Addr[0] = (u16addr>>8) & 0xFF; //HiByte
    u8Addr[1] = (u16addr) & 0xFF; //LowByte
    //MApi_SWI2C_ReadBytes(u16BusNumSlaveID, 2, u8Addr, 2, u8Data);
    //MDrv_IIC_ReadBytes(u16BusNumSlaveID, 2, u8Addr, 2, u8Data);
    s_gpfnMApi_SWI2C_ReadBytes(u16BusNumSlaveID, 2, u8Addr, 2, u8Data);

	//u8Data[0]  LowByte
	//u8Data[1]  HiByte
    return ( (((MS_U16)u8Data[1])<<8)|u8Data[0] );
}

void mhal_mhl_SWI2C_Direct_WriteWord(MS_U16 u16addr, MS_U16 u16data)
{
	mhal_mhl_SWI2C_WriteWord(MHL_I2CBUS_ADDR, u16addr, u16data);
}

MS_U16 mhal_mhl_SWI2C_Direct_ReadWord(MS_U16 u16addr)
{
	return mhal_mhl_SWI2C_ReadWord(MHL_I2CBUS_ADDR, u16addr);
}

void msWriteWord(MS_U16 reg, MS_U16 val)
{
	mhal_mhl_SWI2C_Direct_WriteWord(reg,val);
}
MS_U16 msReadWord(MS_U16 reg)
{
	return mhal_mhl_SWI2C_Direct_ReadWord(reg);
}
void msWriteWordMask(MS_U16 reg, MS_U16 val, MS_U16 mask)
{
	MS_U16 temp;

	if(mask !=0xFFFF)
	{
	    temp=msReadWord(reg) & (~mask);
	    msWriteWord(reg,( temp | (val & mask)));
	}
	else
	{
	   msWriteWord(reg, val);
	}
}


MS_BOOL _mhal_mhl_IsCbusBusy(void)
{
    return ((msReadWord(REG_MHL_CBUS_5D) & 0x00F0) != 0 ? TRUE : FALSE);
}

//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_MHLSupportPath()
//  [Description]
//                  MHL support path
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_MHLSupportPath(MS_U8 ucSelect)
{
    ucMHLSupportPort = ucSelect;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_LoadHdmiBypassTbl()
//  [Description]
//                  MHL HDMI bypass setting
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_LoadHdmiBypassTbl(void)
{
    MS_U8 uctemp = 0;

    for(uctemp = 0; uctemp <(sizeof(tMHL_HDMI_BYPASS_TABLE) /sizeof(msLoadTbl_S)); uctemp++)
    {
        msWriteWordMask(tMHL_HDMI_BYPASS_TABLE[uctemp].addr, tMHL_HDMI_BYPASS_TABLE[uctemp].databuf, tMHL_HDMI_BYPASS_TABLE[uctemp].mask);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_LoadMhl24bitsModeTbl()
//  [Description]
//                  MHL 24 bits mode setting
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_LoadMhl24bitsModeTbl(void)
{
    MS_U8 uctemp = 0;

    for(uctemp = 0; uctemp <(sizeof(tMHL_24BIT_MODE_TABLE) /sizeof(msLoadTbl_S)); uctemp++)
    {
        msWriteWordMask(tMHL_24BIT_MODE_TABLE[uctemp].addr, tMHL_24BIT_MODE_TABLE[uctemp].databuf, tMHL_24BIT_MODE_TABLE[uctemp].mask);
    }

    if(ucMHLDriver <= MHL_DRIVER_U02)
    {
        msWriteWordMask(REG_DVI_DTOP_0C, BIT(9)|BIT(0), BIT(9)|BIT(1)|BIT(0));
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_LoadMhlPackedPixelModeTbl()
//  [Description]
//                  MHL packed pixel mode setting
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_LoadMhlPackedPixelModeTbl(void)
{
    MS_U8 uctemp = 0;

    for(uctemp = 0; uctemp <(sizeof(tMHL_PACKET_PIXEL_MODE_TABLE) /sizeof(msLoadTbl_S)); uctemp++)
    {
        msWriteWordMask(tMHL_PACKET_PIXEL_MODE_TABLE[uctemp].addr, tMHL_PACKET_PIXEL_MODE_TABLE[uctemp].databuf, tMHL_PACKET_PIXEL_MODE_TABLE[uctemp].mask);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CbusIsolate()
//  [Description]
//                  MHL cable isolate
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_CbusIsolate(MS_BOOL bFlag)
{
    if(bFlag)
    {
        msWriteWordMask(REG_PM_MHL_CBUS_00, BIT(9), BIT(9) | BIT(8));
    }
    else
    {
        msWriteWordMask(REG_PM_MHL_CBUS_00, 0, BIT(9) | BIT(8));
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CbusFloating()
//  [Description]
//                  MHL cable isolate
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_CbusFloating(MS_BOOL bFlag)
{
    if(bFlag)
    {
        msWriteWordMask(REG_PM_MHL_CBUS_17, BIT(5), BIT(5));
    }
    else
    {
        msWriteWordMask(REG_PM_MHL_CBUS_17, 0, BIT(5));
    }
}

MS_BOOL mhal_mhl_SWI2C_WriteConfigBytes(MS_U8 u8DataA,MS_U8 u8DataB)
{
    MS_U8 u8Addr[1];
    MS_U8 u8Data[1];

    u8Addr[0] = u8DataA;
    u8Data[0] = u8DataB;

    //return MApi_SWI2C_WriteBytes(MsMHL_CONFIG_ID, 1, u8Addr, 1, u8Data);
    //return MDrv_IIC_WriteBytes(MHL_CFG_I2CBUS_ADDR, 1, u8Addr, 1, u8Data);
    return s_gpfnMApi_SWI2C_WriteBytes(MHL_CFG_I2CBUS_ADDR, 1, u8Addr, 1, u8Data);
}

void mhal_mhl_Set_IIC_16BMode(void)
{
	 mhal_mhl_SWI2C_WriteConfigBytes(0x00,MsMHL_DEVICE_ID);	// Set Slave ID
	 mhal_mhl_SWI2C_WriteConfigBytes(0x01,0x01);				  // Set 16Bits Mode
}

void mhal_mhl_Set_IIC_8BMode(void)
{
     mhal_mhl_SWI2C_WriteConfigBytes(0x00,MsMHL_DEVICE_ID);  // Set Slave ID
     mhal_mhl_SWI2C_WriteConfigBytes(0x01,0x00);                 // Set 8Bits Mode
}

void mhal_mhl_Set_Bank(MS_U8 u8bank)
{
     mhal_mhl_SWI2C_WriteConfigBytes(0x02,u8bank);            // Set Bank
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_init()
//  [Description]
//                  MHL init
//  [Arguments]:
//                  *edid: MHL EDID data
//                  *devcap: MHL device capability
//  [Return]:
//
//**************************************************************************
void mhal_mhl_init(MS_U8 *edid, MS_U8 *devcap)
{
    MS_U16 uctemp = 0;

    // Initial setting
    for(uctemp = 0; uctemp<(sizeof(tMHL_INITIAL_TABLE) /sizeof(msLoadTbl_S)); uctemp++)
    {
        msWriteWordMask(tMHL_INITIAL_TABLE[uctemp].addr, tMHL_INITIAL_TABLE[uctemp].databuf, tMHL_INITIAL_TABLE[uctemp].mask);
    }

    msWriteWordMask(REG_CHIPTOP_55, (BIT(15) |BIT(14) |BIT(13) |BIT(8)), BMASK(15:8));
    ucMHLDriver = (msReadWord(REG_CHIPTOP_04) >>8);
    msWriteWordMask(REG_CHIPTOP_55, 0, BMASK(15:8));

    // load EDID
    msg_mhl(printf("**Load MHL EDID...\r\n"));

    msWriteWordMask(REG_DDC_22, BIT(15), BIT(15)); // [15]: DDC function enable
    msWriteWordMask(REG_DDC_21, 0, BIT(9)); // [9]: DDC write enable

    for(uctemp = 0; uctemp < 256; uctemp++)
    {
        msWriteWord(HB(REG_DDC_23), (edid[uctemp] <<8) |uctemp); // [15:8]:edid, [7:0]:address
        msWriteWordMask(REG_DDC_21, BIT(15), BIT(15)); // write trigger
        msWriteWordMask(REG_DDC_21, 0, BIT(15));
    }

    msWriteWordMask(REG_DDC_21, BIT(9), BIT(9)); // CPU write disable

    // Load vendor ID
    msWriteWordMask(REG_MHL_CBUS_00, DMHL_VENDOR_ID, BMASK(7:0));

    // Load DevCap
    mhal_mhl_LoadDevCap(devcap);

    // modified Cbus related setting for Eland 12M RC clock - 10MHz
    if(!(msReadWord(REG_CHIPTOP_02) & BIT(15))) // [15:8]: efuse output data
    {
#if DMHL_CTS
        msWriteWord(REG_CHIPTOP_01, 0x8C); // 9.8MHz
#else
        msWriteWord(REG_CHIPTOP_01, 0x91); // 9.8MHz
#endif
    }

    // Enable INT
//Vincent add if
#if DMHL_INT_ENABLE
    msWriteWordMask(REG_CHIPTOP_2C, BIT(12), BIT(12)|BIT(11)|BIT(10)); // INT pad mux
//Vincent decomment
	msWriteWordMask(REG_CHIPTOP_0B, 0, BIT(0)); // Chiptop INT mask
#endif

#if(DMHL_WAKE_UP_PULSE_INT)
    msWriteWordMask(REG_PM_MHL_CBUS_18, 0, BIT(5));

#endif

    // clear Cbus received interrupt status
    msWriteWordMask(REG_MHL_CBUS_3A, BIT(4)|BIT(0), BIT(4)|BIT(1)|BIT(0));
    msWriteWordMask(REG_MHL_CBUS_3A, 0, BIT(1)); // [1]: receive packet valid mask

    //SW mode response Devcap
    msWriteWordMask(REG_MHL_CBUS_23, 0, BIT(4)|BIT(10)); // [10]: disable HW auto response Devcap, [4]:disable wrt_grt_int
    //HW mode response Devcap
    //msWriteWordMask(REG_MHL_CBUS_23, BIT(10), BIT(4)|BIT(10)); // [10]: enable HW auto response Devcap, [4]:disable wrt_grt_int

    msWriteWordMask(REG_DVI_DTOP_37, BIT(12), BIT(12)); // [12]: Support DVI mode

    if(ucMHLDriver >= MHL_DRIVER_U03)
    {
        // Enable DVI mode support
        msWriteWordMask(REG_DVI_DTOP_37, BIT(14), BIT(14));

        // Detect discover pulse low width for CTS 4.3.15.1/2
        msWriteWordMask(REG_PM_MHL_CBUS_31, BIT(4), BIT(4));

        // Modify burst write time out timer for CTS 6.3.10.6[1]
        // For CTS 6.3.21.1/2[5][3] and CTS 6.3.22.2[4]
        msWriteWordMask(REG_MHL_CBUS_71, (BIT(1) |BIT(3) |BIT(4) |BIT(5)), BMASK(5:3) |BIT(1));

        // power down dvi pll till clock stable
        msWriteWordMask(REG_DVI_ATOP_6A, BIT(2), BIT(2));
    }

    if(ucMHLDriver >= MHL_DRIVER_U04)
    {
        // 0x0f5b[15] : DC Balance enable
        // 0x0f5b[14] : DC Balance mode, 0 : div2 mode; 1 : lfsr mode
        msWriteWordMask(REG_HDMITX_MISC_5B, BMASK(15:14), BMASK(15:14));

        // fix send abort issue
        msWriteWordMask(REG_MHL_CBUS_71, BIT(7), BIT(7));
    }

    //set PsCtrl to HW mode
    msWriteWordMask(REG_PM_MHL_CBUS_01, 0, BIT(1));

    // DVI clock detection in 40M count value
    msWriteWordMask(REG_DVI_DTOP_0F, 0x01AA, BMASK(11:0));

    // DVI clock detection in 80M count value
    msWriteWordMask(REG_DVI_DTOP_10, 0x0355, BMASK(11:0));

    // DVI clock detection in 160M count value
    msWriteWordMask(REG_DVI_DTOP_11, 0x06AA, BMASK(11:0));

    msWriteWordMask(REG_DVI_ATOP_64, BMASK(15:14), BMASK(15:14));

    //fix AC on/off problem.
    //mhal_mhl_CbusIsolate(TRUE);
    mhal_mhl_CbusFloating(TRUE);

}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_LoadDevCap()
//  [Description]
//                  Load Device Capacity Value
//  [Arguments]:
//                  devcap
//  [Return]:
//
//**************************************************************************

// Aldrich ToDo: Check pre-Settings for Loading?
void mhal_mhl_LoadDevCap(MS_U8 *devcap)
{
    MS_U8 u8index = 0;
    MS_U16 u16temp = 0;

    // load DevCap
    msg_mhl(printf("**Load DevCap...\r\n"));

    // load MHL device capability
    for(u16temp = 0; u16temp <8; u16temp++)
    {
        if(u16temp == 2)
        {
            u8index = 1;
        }

        msWriteWord(REG_MHL_CBUS_01 +(u16temp *2), (devcap[(u16temp *2) +1 -u8index] <<8) | devcap[u16temp *2 -u8index]);
    }

    msWriteWord(REG_MHL_CBUS_03, (devcap[3] <<8) | devcap[4]);
    msWriteWord(REG_MHL_CBUS_07, (devcap[11] <<8) | devcap[12]);
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_GetDevCap()
//  [Description]
//                  Read Device Capacity Value
//  [Arguments]:
//                  u8Idx: 0~15
//  [Return]:
//
//**************************************************************************

MS_U8 mhal_mhl_GetDevCap(MS_U8 u8Idx)
{
    MS_U8 u8RetVal=0;
    if (u8Idx >= 16)
    {
        msg_mhl(printf("Read DevCap Idx Wrong...\r\n"));
        u8RetVal = 0;
    }
    else
    {
        if (u8Idx >= 2)
        {
            u8Idx=+1;
        }

        u8RetVal = (MS_U8)(0xFF & msReadWord(REG_MHL_CBUS_01+u8Idx));
    }

    return u8RetVal;
}

#if(DMHL_WAKE_UP_PULSE_INT)
//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_MHLForceToStandby()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_MHLForceToStandby(void)
{
    msWriteWordMask(REG_MHL_CBUS_3A, BIT(4), BIT(4)); // clear received FIFO
    msWriteWordMask(REG_PM_MHL_CBUS_17, BIT(15), BIT(15)); // force enter PM mode
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_ClearWakeupIntFlag()
//  [Description]
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_ClearWakeupIntFlag(void)
{
    msWriteWordMask(REG_PM_MHL_CBUS_18, BIT(4), BIT(4));
}

#endif

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CBusWrite()
//  [Description]
//                  MHL Cbus write trigger
//  [Arguments]:
//                  *pdatabuf: Cbus tx data
//  [Return]:
//
//**************************************************************************
MS_BOOL mhal_mhl_CBusWrite(mhalCbusFifo_S *pdatabuf)
{
    MS_U8 uctemp = 0;

    for(uctemp = 0; uctemp < pdatabuf->lens; uctemp++)
    {
        msWriteWord(REG_MHL_CBUS_26 +uctemp *2, pdatabuf->databuf[uctemp]);
    }

    // clear the unsed parts
    msWriteWord(REG_MHL_CBUS_26 +((pdatabuf->lens)*2), 0);

    if(_mhal_mhl_IsCbusBusy())
    {
        return FALSE;
    }

    msWriteWordMask(REG_MHL_CBUS_25, BIT(12), BIT(12)); // trigger to send

    return TRUE;
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CableDetect()
//  [Description]
//                  MHL cable detection
//  [Arguments]:
//
//  [Return]:
//                  TRUE: MHL cable plugged
//                  FALSE: MHL cable unplugged
//**************************************************************************
MS_BOOL mhal_mhl_CableDetect(void)
{
    return ((msReadWord(REG_PM_MHL_CBUS_00) & BIT(10)) ? TRUE : FALSE);
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_mhl_Cbus_SetPathEn()
//  [Description]:
//                  MHL Cbus set path enable
//  [Arguments]:
//                  TRUE: Enable
//                  FALSE: Disable
//  [Return]:
//
//**************************************************************************
void mhal_mhl_Cbus_SetPathEn(MS_BOOL bflag)
{
    if(bflag) // set state to PATH_EN
    {
        msWriteWordMask(REG_PM_MHL_CBUS_17, BIT(12), BIT(12));
    }
    else // clear state to not PATH_EN
    {
        msWriteWordMask(REG_PM_MHL_CBUS_17, BIT(13), BIT(13));
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CbusIsMscMsgReceived()
//  [Description]
//                  MHL Cbus check whether msc message is received or not
//  [Arguments]:
//
//  [Return]:
//                  TRUE: recieved
//                  FALSE: not yet
//**************************************************************************
MS_BOOL mhal_mhl_CbusIsMscMsgReceived(void)
{
    return((msReadWord(REG_MHL_CBUS_3A) & BIT(3)) ? TRUE : FALSE);
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CbusIntCB()
//  [Description]
//                  MHL Cbus Interrupt Call Back function
//  [Arguments]:
//                  *rcstate: recevied state, 0:normal / 1:timeout
//                  *rccmd: recevied command
//                  *rcdata: recevied data
//                  *rclen: received length
//                  *bIsCmdInData: Is command in data field
//  [Return]:
//
//**************************************************************************
void mhal_mhl_CbusIntCB(MS_U8 *rcstate, MS_U8 *rccmd, MS_U8 *rcdata, MS_U8 *rclen, MS_U8 *bIsCmdInData)
{
    MS_U8 uctemp = 0;
    MS_U16 reg_val;

    *rcstate = msReadWord(REG_MHL_CBUS_3B) & 0x000F; // received state, 0: normal, 1: timeout

    msWriteWordMask(REG_MHL_CBUS_3A, BIT(0), BIT(0)); // clear INT

    *rccmd = msReadWord(REG_MHL_CBUS_3C) & 0x00FF;
    *bIsCmdInData = FALSE;

    for(uctemp = 0; uctemp <=(MHL_CBUS_DATA_SIZE +1); uctemp++) // offset+16bytes+EOF
    {
        reg_val = msReadWord(REG_MHL_CBUS_3D +(uctemp *2));

        if(reg_val & BIT(15))
        {
            rcdata[uctemp] = reg_val & 0x00FF;

            if(((uctemp <= 2) ||(uctemp == (MHL_CBUS_DATA_SIZE +1))) && !(*bIsCmdInData))
            {
                *bIsCmdInData = (reg_val & BIT(8)) ? TRUE : FALSE;
            }
        }
        else
        {
            *rclen = uctemp;
            break;
        }
    }

    // CTS 6.3.11.19
    if(uctemp >(MHL_CBUS_DATA_SIZE +1))
    {
        *rclen = MHL_CBUS_DATA_SIZE +2;
    }

    msWriteWordMask(REG_MHL_CBUS_3A, BIT(4), BIT(4)); // clear received FIFO
}

//**************************************************************************
//  [Function Name]:
//                  _mhal_mhl_CbusStatus()
//  [Description]:
//                  MHL Cbus status
//  [Arguments]:
//
//  [Return]:
//                  Cbus status value
//**************************************************************************
MS_U16 mhal_mhl_CbusStatus(void)
{
    return (msReadWord(REG_PM_MHL_CBUS_17));
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_CDRModeMonitor()
//  [Description]:
//                  MHL CDR mode monitor
//  [Arguments]:
//                  isCbusConnected: Cbus is at connected state or not
//  [Return]:
//
//**************************************************************************
MS_BOOL mhal_mhl_CDRModeMonitor(MS_BOOL bPathEnable)
{
    static MS_BOOL bPLLPower = FALSE;
    static MS_U16 wpre_val = 0;
    MS_U16 wcur_val;
    static MS_U8 u8count = 1;

    if(ucMHLDriver <= MHL_DRIVER_U02)
    {
        if(bPathEnable)
        {
            // pixel rate must large than 25MHz then power on DVI PLL
            wcur_val = msReadWord(REG_DVI_DTOP_17) & 0x0FFF;

            if(wcur_val > CBUS_CLOCK_DETECT_LEVEL)
            {
                if((wcur_val >= (wpre_val -CBUS_CLOCK_DETECT_OFFSET)) && (wcur_val <= (wpre_val +CBUS_CLOCK_DETECT_OFFSET)))
                {
                    if(u8count < MHL_CDR_STABLE_THRESHOLD)
                    {
                        u8count++;
                    }

                    if(u8count == (MHL_CDR_STABLE_THRESHOLD -1))
                    {
                        msWriteWordMask(REG_DVI_ATOP_69, 0, BIT(7)); // power on DVI PLL
                        msWriteWordMask(REG_DVI_ATOP_66, BIT(7), BIT(7)); // [13]: enable CDR mode

            #if DMHL_CTS_HDCP_PATCH
                        msWriteWordMask(REG_DVI_DTOP_27, 0, BIT(6) |BIT(5)); // [5]: sequential check disable
            #endif

                        bPLLPower = TRUE;
                    }
                }
            }
            else
            {
                bPathEnable = FALSE;
            }

            wpre_val = wcur_val;
        }

        if(!bPathEnable)
        {
            if(u8count > 0 || bPLLPower)
            {
                u8count = 0;

                msWriteWordMask(REG_DVI_ATOP_66, 0, BIT(7)); // [13]: disable CDR mode
                msWriteWordMask(REG_DVI_ATOP_69, BIT(7), BIT(7)); // [7]: power down DVI PLL

            #if DMHL_CTS_HDCP_PATCH
                msWriteWordMask(REG_DVI_DTOP_27, BIT(6) |BIT(5), BIT(6) |BIT(5)); // [5]: sequential check enable
            #endif

                bPLLPower = FALSE;
            }
        }
    }

    return FALSE;
}

//**************************************************************************
//  [Function Name]:
//                  mdrv_mhl_CBusCheckBCHError()
//  [Description]:
//                  MHL Cbus check BCH error
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_BOOL mhal_mhl_CBusCheckBCHError(void)
{
    return FALSE;
}

#if(DMHL_LG_PRADA_PATCH)
//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_AdjustCommonModeResistor()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_MHLForceToAttach(void)
{
    msWriteWordMask(REG_PM_MHL_CBUS_17, BIT(14), BIT(14));
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_AdjustCommonModeResistor()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_AdjustCommonModeResistor(MS_BOOL bflag)
{
//Vincent change line
    msWriteWordMask(REG_DVI_ATOP_61, bflag ? 0 : BIT(1), BIT(1));    // Common-mode resistor open
 //   msWriteWordMask(REG_DVI_ATOP_61, bflag ? 0 : BIT(3), BIT(3));    // Common-mode resistor open

    if(bflag)
    {
        mhal_mhl_MHLForceToAttach();
    }
}

#endif

#if(DMHL_TEST_SIGNAL_SUPPORT)
//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_AdjustCommonModeResistor()
//  [Description]:
//
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_TestSignal(MS_BOOL bflag)
{
    // No such function
}

#endif

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_RxRtermControl()
//  [Description]
//                  MHL TMDS termination resistor control
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_RxRtermControl(RXRtermControl_T rctrl)
{
    if (rctrl == RX_HDMI_RTERM)
    {
        msWriteWordMask(REG_DVI_ATOP_69, 0, BIT(13)|BIT(12)|BIT(11));// data R-term
        msWriteWordMask(REG_DVI_ATOP_6D, 0, BIT(10));// clock R-term
    }
    else if (rctrl == RX_MHL_RTERM)
    {
//Vincent change two lines
        msWriteWordMask(REG_DVI_ATOP_69, BIT(13)|BIT(12), BIT(13)|BIT(12)|BIT(11));// data R-term
        msWriteWordMask(REG_DVI_ATOP_6D, BIT(10), BIT(10));// clock R-term
//        msWriteWordMask(REG_DVI_ATOP_69, 0, BIT(13)|BIT(12)|BIT(11));// data R-term
//        msWriteWordMask(REG_DVI_ATOP_6D, 0, BIT(10));// clock R-term
    }
    else if (rctrl == RX_RTERM_OFF)
    {
        msWriteWordMask(REG_DVI_ATOP_69, BIT(13)|BIT(12)|BIT(11), BIT(13)|BIT(12)|BIT(11));// data R-term
        msWriteWordMask(REG_DVI_ATOP_6D, BIT(10), BIT(10));// clock R-term
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_PowerControl()
//  [Description]
//                  MHL power control
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************

// MHL power control
void mhal_mhl_LoadPowerOnTbl(void)
{
    MS_U8 i;
    for(i=0; i<(sizeof(tMHL_POWER_ON_TABLE) /sizeof(msLoadTbl_S)); i++)
    {
        msWriteWordMask(tMHL_POWER_ON_TABLE[i].addr, tMHL_POWER_ON_TABLE[i].databuf, tMHL_POWER_ON_TABLE[i].mask);
    }
}
void mhal_mhl_LoadPowerStandbyTbl(void)
{
    MS_U8 i;
    for(i=0; i<(sizeof(tMHL_POWER_SAVING_TABLE) /sizeof(msLoadTbl_S)); i++)
    {
        msWriteWordMask(tMHL_POWER_SAVING_TABLE[i].addr, tMHL_POWER_SAVING_TABLE[i].databuf, tMHL_POWER_SAVING_TABLE[i].mask);
    }

    if(ucMHLDriver <= MHL_DRIVER_U03)
    {
        msWriteWordMask(REG_DVI_ATOP_6D, 0x0800, 0x0900);
    }
}

void mhal_mhl_LoadPowerDownTbl(void)
{
    MS_U8 i;
    for(i=0; i<(sizeof(tMHL_POWER_DOWN_TABLE) /sizeof(msLoadTbl_S)); i++)
    {
        msWriteWordMask(tMHL_POWER_DOWN_TABLE[i].addr, tMHL_POWER_DOWN_TABLE[i].databuf, tMHL_POWER_DOWN_TABLE[i].mask);
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_SetHPD()
//  [Description]
//                  config HPD in combo(MHL/HDMI) port A
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
void mhal_mhl_SetHPD(MS_BOOL bflag)
{
    if(bflag) // HPD is high
    {
        msWriteWordMask(REG_PM_MHL_CBUS_20, BIT(3), BMASK(4:3)); // [4]: output val, [3]: oen
        //msg_mhl(printf("**MHL_HPD is High"));
    }
    else // hpd is low
    {
        msWriteWordMask(REG_PM_MHL_CBUS_20, 0, BMASK(4:3)); // [4]: output val, [3]: oen
        //msg_mhl(printf("**MHL_HPD is Low"));
    }
}

//**************************************************************************
//  [Function Name]:
//                  mhal_mhl_GetDDCErrorCode()
//  [Description]
//                  Get DDC error code
//  [Arguments]:
//
//  [Return]:
//
//**************************************************************************
MS_U8 mhal_mhl_GetDDCErrorCode(void)
{
    return (msReadWord(REG_MHL_CBUS_21)>>8);
}

MS_U16 mhal_mhl_GetTMDSClk(void)
{
    return (msReadWord(REG_DVI_DTOP_17) & 0x0FFF);
}

void mhal_mhl_SetPsCtrl(MS_U8 u8Ctrl)
{
    msWriteWordMask(REG_PM_MHL_CBUS_01, BIT(1), BIT(1));

    if(u8Ctrl == 0)
    {
        msWriteWordMask(REG_PM_MHL_CBUS_01, 0, BIT(0));
    }
    else
    {
        msWriteWordMask(REG_PM_MHL_CBUS_01, 1, BIT(0));
    }
}

void mhal_mhl_SetPsCtrl_HDMImode(MS_U8 u8Ctrl)
{
    //Aldrich ToDo
    u8Ctrl=u8Ctrl;
}

void mhal_mhl_TxSwap_Settings(MS_BOOL bTxSwapEnable)
{
    //{REG_HDMITX_MISC_5B, 0x1800, 0x1800}, // [12:11] = 2'b 11 HDMI Tx swap for JunoE **
    if (bTxSwapEnable)
    {
        msWriteWordMask(REG_HDMITX_MISC_5B, BIT(11)|BIT(12), BIT(11)|BIT(12));
    }
    else
    {
        msWriteWordMask(REG_HDMITX_MISC_5B, 0, BIT(11)|BIT(12));
    }

}

void mhal_mhl_RegisterCallBackFunctions(link_mhl_reg_i_func_b pfnRead, link_mhl_reg_o_func_b pfnWrite)
{
    s_gpfnMApi_SWI2C_ReadBytes = pfnRead;
    s_gpfnMApi_SWI2C_WriteBytes = pfnWrite;
}

void mhal_mhl_I2C_Channel_Settings(MS_U16 u16Channel, MS_U8 u8CommonID, MS_U8 u8ConfigID)
{
    s_gu16MHL_I2C_Channel = u16Channel;
    s_gu8MHL_I2C_Slave_ID_Common = u8CommonID;
    s_gu8MHL_I2C_Slave_ID_Config = u8ConfigID;
}

#endif // _HAL_MHL_ELAND_C_

