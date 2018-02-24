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
/*@ <FileComment ID=1246257763790> @*/
/**********************************************************************
Copyright (c) 2006-2009 MStar Semiconductor, Inc.
All rights reserved.
Unless otherwise stipulated in writing, any and all information contained
herein regardless in any format shall remain the sole proprietary of
MStar Semiconductor Inc. and be kept in strict confidence
(MStar Confidential Information) by the recipient.
Any unauthorized act including without limitation unauthorized disclosure,
copying, use, reproduction, sale, distribution, modification, disassembling,
reverse engineering and compiling of the contents of MStar Confidential
Information is unlawful and strictly prohibited. MStar hereby reserves the
rights to any and all damages, losses, costs and expenses resulting therefrom.
 * Class : mapi_demodulator_msb123x
 * File  : mapi_demodulator_msb123x.cpp
 **********************************************************************/
/*@ </FileComment ID=1246257763790> @*/
/*@ <Include> @*/
//Branch from CL456729
#include <string.h>
#include "drvIIC.h"
#include "demodulator_T2.h"
#include "msb123x.h"
//#include "mdev_tuner_xceive_XC6200.h"
//#include "HwProfile.h"
#include "debug.h"
#include "MApp_Scan.h"
#include <pthread.h>

MAPI_U8 MSB123X_LIB[]={
#include "msb123x_dvbt2.dat"
};

#if defined (MSOS_TYPE_LINUX) || defined (MSOS_TYPE_ECOS)
#include <math.h>
#endif
/*@ </Include> @*/
#define UNUSED(var)     (void)((var) = (var))
#define MSB123X_DEMOD_IIC 1
#define MSB123X_SPI_IIC 2
#define MSB123X_DEBUG_ON 1

ST_MAPI_DEMODULATOR_FUN stMapiDemodulatorFun;
#define usleep(x)                     MsOS_DelayTask(x/1000)

MAPI_BOOL MSB123x_MEM_switch(MAPI_U8 mem_type);
MAPI_BOOL Connect(EN_DEVICE_DEMOD_TYPE enDemodType);
MAPI_BOOL DTV_DVBT2_DSPReg_Init(void);
EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void);
MAPI_BOOL DTV_GetPreBER(float *p_preBer);
MAPI_BOOL DTV_GetPostBER(float *p_postBer);
EN_MSB_123X_LOCK_STATUS DTV_DVB_T_GetLockStatus(void);
MAPI_BOOL I2C_CH_Reset(MAPI_U8 ch_num);
MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
MAPI_BOOL WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size);
MAPI_BOOL WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data);
MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data);
MAPI_BOOL  WriteDspReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
MAPI_BOOL ReadDspReg(MAPI_U16 u16Addr, MAPI_U8* pData);
MAPI_BOOL LoadDSPCode(void);
MAPI_U16 MSB1231_Lock(COFDM_LOCK_STATUS_123X eStatus);
void Driving_Control(MAPI_BOOL bEnable);

#if (MSB123X_DEBUG_ON == 1)
void msb123x_show_version(void)
{

    MAPI_U8  reg = 0;
    MAPI_U16 ver0 = 0;
    MAPI_U8  ver1 = 0;

    ReadDspReg(T2_FW_VER_0,&reg);
    ver0 = reg;
    ReadDspReg(T2_FW_VER_1,&reg);
    ver0 = (ver0<<8)|reg;
    ReadDspReg(T2_FW_VER_2,&reg);
    ver1 = reg;

    printf("\n[msb123x]ver0 = 0x%x, ver1 = 0x%x\n",ver0,ver1);

    return;
}

void msb123x_outer_info(void)
{
 MAPI_U8 reg;
 MAPI_U16 ldpc_err_win;
 MAPI_U8 ldpc_max_iter;
 MAPI_U16 ldpc_err_count;
 MAPI_U16 bch_eflag2_sum;
 MAPI_U16 ldpc_ber_count_plp_l,ldpc_ber_count_plp_h;
 float pre_ber;
 static MAPI_U16 acc_eflag2_num = 0;

 ReadReg(0x2600+0x12*2 + 1,&reg);
 ldpc_err_win = reg;
 ReadReg(0x2600+0x12*2,&reg);
 ldpc_err_win = (ldpc_err_win<<8)|reg;

 ReadReg(0x2600+0x18*2,&reg);
 ldpc_max_iter = reg;

 ReadReg(0x2600+0x19*2 + 1,&reg);
 ldpc_err_count = reg;
 ReadReg(0x2600+0x19*2,&reg);
 ldpc_err_count = (ldpc_err_count<<8)|reg;

 ReadReg(0x2600+0x26*2 + 1,&reg);
 bch_eflag2_sum = reg;
 ReadReg(0x2600+0x26*2,&reg);
 bch_eflag2_sum = (bch_eflag2_sum<<8)|reg;

 ReadReg(0x2600+0x32*2 + 1,&reg);
 ldpc_ber_count_plp_l = reg;
 ReadReg(0x2600+0x32*2,&reg);
 ldpc_ber_count_plp_l = (ldpc_ber_count_plp_l<<8)|reg;

 ReadReg(0x2600+0x33*2 + 1,&reg);
 ldpc_ber_count_plp_h = reg;
 ReadReg(0x2600+0x33*2,&reg);
 ldpc_ber_count_plp_h = (ldpc_ber_count_plp_h<<8)|reg;


 ReadReg(0x2700+0x47*2,&reg);
 if(reg&0x80)
 {
   pre_ber = (float)((((MAPI_U32)ldpc_ber_count_plp_h)<<16)|ldpc_ber_count_plp_l)/(64800.0*(float)ldpc_err_win);
 }
 else
   pre_ber = (float)((((MAPI_U32)ldpc_ber_count_plp_h)<<16)|ldpc_ber_count_plp_l)/(16200.0*(float)ldpc_err_win);


 acc_eflag2_num += bch_eflag2_sum;

 printf("[msb123x][1]ldpc_err_win=%d, ldpc_max_iter=%d, ldpc_err_count=%d\n",ldpc_err_win,ldpc_max_iter,ldpc_err_count);
 printf("[msb123x][2]bch_eflag2_sum=%d, ldpc_ber_count_plp_l=0x%x, ldpc_ber_count_plp_h=0x%x\n",bch_eflag2_sum,ldpc_ber_count_plp_l,ldpc_ber_count_plp_h);
 printf("------------->[msb123x][3]ber=%f\n",pre_ber);
 printf("-------------| %d/%d |-----------\n",bch_eflag2_sum,acc_eflag2_num);


 if(bch_eflag2_sum != 0)
 {
   printf("0000000000\n");
   printf("0000011100\n");
   printf("------1000\n");
   printf("000000----\n");
   printf("------1111\n");
 }


 return;
}

void msb123x_mod_info(void)
{

 MAPI_U8  reg;
 MAPI_U8  plp_id,plp_group_id,plp_mux_sel;
 MAPI_U8  type,bw_ext, s1, s2;
 MAPI_U8  l1_repetition_flag, guard_interval, papr, l1_mod, l1_cod, l1_fec;
 MAPI_U8  pilot_pattern;
 MAPI_U8  cell_id;
 MAPI_U8  network_id;
 MAPI_U8  system_id;
 MAPI_U8  plp_id_a, plp_type,plp_payload_type;
 MAPI_U8  plp_cod, plp_mod, plp_rotation, plp_fec_type;


 ReadReg(0x2700+0x02*2,&reg);
 plp_id = reg;

 ReadReg(0x2700+0x02*2 + 1,&reg);
 plp_group_id = reg;

 ReadReg(0x2700+0x03*2,&reg);
 plp_mux_sel = reg&0x0f;

 ReadReg(0x2700+0x30*2,&reg);
 type = reg;

 ReadReg(0x2700+0x30*2 + 1,&reg);
 bw_ext = reg&0x01;
 s1 = (reg>>1)&0x07;
 s2 = (reg>>4)&0x0f;

 ReadReg(0x2700+0x31*2,&reg);
 l1_repetition_flag = reg&0x01;
 guard_interval = (reg>>1)&0x07;
 papr = (reg>>4)&0x0f;

 ReadReg(0x2700+0x31*2 + 1,&reg);
 l1_mod = reg&0x0f;
 l1_cod = (reg>>4)&0x03;
 l1_fec = (reg>>6)&0x03;

 ReadReg(0x2700+0x36*2,&reg);
 pilot_pattern = reg&0x0f;

 ReadReg(0x2700+0x38*2,&reg);
 cell_id = reg;
 ReadReg(0x2700+0x38*2 + 1,&reg);
 cell_id = (cell_id<<8)|reg;

 ReadReg(0x2700+0x39*2,&reg);
 network_id = reg;
 ReadReg(0x2700+0x39*2 + 1,&reg);
 network_id = (network_id<<8)|reg;

 ReadReg(0x2700+0x3a*2,&reg);
 system_id = reg;
 ReadReg(0x2700+0x3a*2 + 1,&reg);
 system_id = (system_id<<8)|reg;


 ReadReg(0x2700+0x45*2,&reg);
 plp_id_a = reg;
 ReadReg(0x2700+0x45*2 + 1,&reg);
 plp_type = reg&0x07;
 plp_payload_type = (reg>>3)&0x1f;


 ReadReg(0x2700+0x47*2,&reg);
 plp_cod = reg&0x07;
 plp_mod = (reg>>3)&0x07;
 plp_rotation = (reg>>6)&0x01;
 plp_fec_type = (reg>>7)&0x01;

 ReadReg(0x2700+0x47*2 + 1,&reg);
 plp_fec_type |= (reg&0x01<<1);

 printf("[msb123x][mod][1]plp_id=%d, plp_group_id=%d, plp_mux_sel=%d\n",plp_id,plp_group_id,plp_mux_sel);
 printf("[msb123x][mod][2]type=0x%x, bw_ext=0x%x, s1=0x%x, s2=0x%x\n",type,bw_ext,s1,s2);
 printf("[msb123x][mod][3]l1_repetition_flag=0x%x, guard_interval=0x%x, papr=0x%x, l1_mod=0x%x, l1_cod=0x%x, l1_fec=0x%x\n",l1_repetition_flag,guard_interval,papr,l1_mod,l1_cod,l1_fec);
 printf("[msb123x][mod][4]pilot_pattern=%d\n",pilot_pattern);
 printf("[msb123x][mod][5]cell_id=0x%x\n",cell_id);
 printf("[msb123x][mod][6]network_id=0x%x\n",network_id);
 printf("[msb123x][mod][7]system_id=0x%x\n",system_id);
 printf("[msb123x][mod][8]plp_id_a=%d, plp_type=0x%x, plp_payload_type=%d\n",plp_id_a,plp_type,plp_payload_type);
 printf("[msb123x][mod][9]plp_cod=%d, plp_mod=0x%x, plp_rotation=%d, plp_fec_type=0x%x\n",plp_cod,plp_mod,plp_rotation,plp_fec_type);

 return;
}


// ----------------- indicate Fd_function information -----------------------------
// User_var_1 (bank 0, 0x4a) : decoded information that need to be shown on the GUI
//     [0] : ZIF
//   [3:1] : BW(0->1.7, 1->5, 2->6, 3->7, 4->8, 5->10)
//     [4] : Low_Pwr_Det
//     [5] : ACI_Det
//   [8:6] : CCI_Det
//  [10:9] : ACI_Det_Fd (0->no aci, 1->N+1, 2->N-1, 3->N+1 & N-1)
//    [11] : FDSA_Left_align (0->Right, 1->Left)
//    [12] : Large_th_flag (0->small, 1->large)
// [14:13] : Fd_function (0->default, 1->One-Shot, 2->CompareBER, 3->BPF)
// --------------------------------------------------------------------------------
// User_var_0 (bank 0, 0x49) : enable indicator that need to be shown on the GUI
//   [0] : Low_Pwr_en
//   [1] : ACI_en
//   [2] : DCR_en
//   [3] : IIS_en
//   [4] : CCI_en
//   [5] : IQB_en
//   [6] : GI_en
//   [7] : TD_Motion_en
//   [8] : FD_Motion_en
//   [9] : Windowing_en
//  [10] : CE1_Most_Interp
// -------------------------------------------------------------------------------
void msb123x_sw_indicator(void)
{
 MAPI_U8 reg,reg1;
 MAPI_U8 zif,bw,low_pwr_det,aci_det,cci_det;
 MAPI_U8 aci_det_fd,fdsa_align,large_the_flag,fd_function;
 MAPI_U8 windows_en,ce1_most_interp;


 ReadReg(0x0900+0x4a*2,&reg);
 ReadReg(0x0900+0x4a*2 + 1,&reg1);

 zif = reg&0x01;
 bw = (reg>>1)&0x07;
 low_pwr_det = (reg>>4)&0x01;
 aci_det = (reg>>5)&0x01;
 cci_det = (reg>>6)&0x03;
 cci_det = cci_det|((reg1&0x01)<<2);

 aci_det_fd = (reg1>>1)&0x03;
 fdsa_align = (reg1>>3)&0x01;
 large_the_flag = (reg1>>4)&0x01;
 fd_function = (reg1>>5)&0x03;


 ReadReg(0x0900+0x49*2,&reg);
 ReadReg(0x0900+0x49*2 + 1,&reg1);

 windows_en = (reg1>1)&0x01;
 ce1_most_interp = (reg1>2)&0x01;


 printf("[msb123x][sw][1]zif=%d, bw=%d, low_pwr_det=%d\n",zif,bw,low_pwr_det);
 printf("[msb123x][sw][2]aci_det=%d, cci_det=%d, aci_det_fd=%d\n",aci_det,cci_det,aci_det_fd);
 printf("[msb123x][sw][3]fdsa_align=%d, large_the_flag=%d, fd_function=%d\n",fdsa_align,large_the_flag,fd_function);
 printf("[msb123x][sw][4]windows_en=%d, ce1_most_interp=%d\n",windows_en,ce1_most_interp);
 return;
}


void msb123x_top_indicator(void)
{
  MAPI_U8 reg;
  MAPI_U16 ts_pad;

  ReadReg(0x0900+0x2d*2 + 1,&reg);
  ts_pad = reg;
  ReadReg(0x0900+0x2d*2,&reg);
  ts_pad = (ts_pad<<8)|reg;

  printf("[top]ts_pad=0x%x\n",ts_pad);

  return;

}

void msb123x_snr_indicator(void)
{

  MAPI_U8  reg;
  MAPI_U16 snr_bmse_en;
  MAPI_U8 per_tone_choice;
  MAPI_U8 snr_alpha_per_tone;
  MAPI_U8 snr_alpha_dynamic;
  MAPI_U8 snr_method;
  MAPI_U8 snr_accu_num;

  ReadReg(0x2800+0x02*2 + 1,&reg);
  snr_bmse_en = reg;
  ReadReg(0x2800+0x02*2,&reg);
  snr_bmse_en = (snr_bmse_en<<8)|reg;

  per_tone_choice    = (snr_bmse_en>>1)&0x07;
  snr_alpha_per_tone = (snr_bmse_en>>4)&0x07;
  snr_alpha_dynamic  = (snr_bmse_en>>7)&0x0F;
  snr_method         = (snr_bmse_en>>11)&0x03;
  snr_accu_num       = (snr_bmse_en>>13)&0x07;
  snr_bmse_en        = snr_bmse_en&0x01;


  printf("[snr][1]snr_bmse_en=0x%x, per_tone_choice=0x%x,snr_alpha_per_tone=0x%x\n",snr_bmse_en,per_tone_choice,snr_alpha_per_tone);
  printf("[snr][2]snr_alpha_dynamic=0x%x, snr_method=0x%x,snr_accu_num=0x%x\n",snr_alpha_dynamic,snr_method,snr_accu_num);

  return;
}

void msb123x_td_indicator(void)
{

#define DVBT2_TDP 0x2400

 MAPI_U8 reg;
 MAPI_U16 swrst_tdp;
 MAPI_U8 dvbt_en;
 MAPI_U32 type_p1_det_th, type_p2_det_th;
 MAPI_U8 cw_th;
 MAPI_U8 byps_prepk;
 MAPI_U8 s1_s2;
 MAPI_U8 cfo_kp, sfo_kp;
 MAPI_U8 p1;
 MAPI_U16 cwt_done;
 MAPI_U8 mode_det1;
 MAPI_U8 seq_sw_ctrl;
 MAPI_U16 st_seq_ctrl;
 MAPI_U8  seq_ctrl_fsm, seq_ctrl_counting_fsm, seq_p1_fsm,l1_crc_fail,td_cfo_sfo_done;
 MAPI_U32 p1_interval_count;
 MAPI_U8 manual_mode;
 MAPI_U16 short_t2_ofdm;
 MAPI_U8 seq_papr_fail;
 MAPI_U8 fft;
 MAPI_U8 gi;


 ReadReg(DVBT2_TDP+0x00*2 + 1,&reg);
 swrst_tdp = reg&0x1f;
 ReadReg(DVBT2_TDP+0x00*2,&reg);
 swrst_tdp = (swrst_tdp<<8)|reg;

 ReadReg(DVBT2_TDP+0x03*2,&reg);
 dvbt_en = reg&0x01;


 ReadReg(DVBT2_TDP+0x11*2,&reg);
 type_p1_det_th = reg&0x0f;
 ReadReg(DVBT2_TDP+0x10*2 + 1,&reg);
 type_p1_det_th = (type_p1_det_th<<8)|reg;
 ReadReg(DVBT2_TDP+0x10*2,&reg);
 type_p1_det_th = (type_p1_det_th<<8)|reg;

 ReadReg(DVBT2_TDP+0x13*2,&reg);
 type_p2_det_th = reg&0x0f;
 ReadReg(DVBT2_TDP+0x12*2 + 1,&reg);
 type_p2_det_th = (type_p2_det_th<<8)|reg;
 ReadReg(DVBT2_TDP+0x12*2,&reg);
 type_p2_det_th = (type_p2_det_th<<8)|reg;

 ReadReg(DVBT2_TDP+0x16*2,&reg);
 cw_th = reg&0x3f;

 ReadReg(DVBT2_TDP+0x16*2 + 1,&reg);
 byps_prepk = reg&0x0f;

 ReadReg(DVBT2_TDP+0x19*2,&reg);
 s1_s2 = reg;

 ReadReg(DVBT2_TDP+0x21*2,&reg);
 cfo_kp = reg;

 ReadReg(DVBT2_TDP+0x22*2,&reg);
 sfo_kp = reg;

 ReadReg(DVBT2_TDP+0x40*2,&reg);
 p1 = reg;

 ReadReg(DVBT2_TDP+0x40*2 + 1,&reg);
 fft = reg&0x07;
 gi  = (reg&0x70)>>4;

 ReadReg(DVBT2_TDP+0x41*2 + 1,&reg);
 cwt_done = reg&0x07;
 ReadReg(DVBT2_TDP+0x41*2,&reg);
 cwt_done = (cwt_done<<8)|reg;

 ReadReg(DVBT2_TDP+0x42*2,&reg);
 mode_det1 = reg;

 ReadReg(DVBT2_TDP+0x50*2,&reg);
 seq_sw_ctrl = reg&0x1f;

 ReadReg(DVBT2_TDP+0x58*2 + 1,&reg);
 st_seq_ctrl = reg&0x3f;
 ReadReg(DVBT2_TDP+0x58*2,&reg);
 st_seq_ctrl = (st_seq_ctrl<<8)|reg;

 seq_ctrl_fsm          = st_seq_ctrl&0x1f;
 seq_ctrl_counting_fsm = (st_seq_ctrl>>5)&0x0f;
 seq_p1_fsm            = (st_seq_ctrl>>9)&0x07;
 l1_crc_fail           = (st_seq_ctrl>>12)&0x01;
 td_cfo_sfo_done       = (st_seq_ctrl>>13)&0x01;


 ReadReg(DVBT2_TDP+0x5a*2,&reg);
 p1_interval_count = reg&0x3f;
 ReadReg(DVBT2_TDP+0x59*2 + 1,&reg);
 p1_interval_count = (p1_interval_count<<8)|reg;
 ReadReg(DVBT2_TDP+0x59*2,&reg);
 p1_interval_count = (p1_interval_count<<8)|reg;

 ReadReg(DVBT2_TDP+0x5b*2,&reg);
 manual_mode = reg&0x1f;

 ReadReg(DVBT2_TDP+0x5d*2 + 1,&reg);
 short_t2_ofdm = reg;
 ReadReg(DVBT2_TDP+0x5d*2,&reg);
 short_t2_ofdm = (short_t2_ofdm<<8)|reg;

 ReadReg(DVBT2_TDP+0x5e*2,&reg);
 seq_papr_fail = reg&0x1f;


  printf("[td][1]swrst_tdp=0x%x, dvbt_en=0x%x\n",swrst_tdp,dvbt_en);
  printf("[td][2]type_p1_det_th=0x%lx, type_p2_det_th=0x%lx\n",type_p1_det_th,type_p2_det_th);
  printf("[td][3]cw_th=0x%x, byps_prepk=0x%x, s1_s2=0x%x\n",cw_th,byps_prepk,s1_s2);
  printf("[td][4]cfo_kp=0x%x, sfo_kp=0x%x\n",cfo_kp,sfo_kp);
  printf("[td][5]p1=0x%x, cwt_done=0x%x, fft=0x%x, gi=0x%x\n",p1,cwt_done,fft,gi);
  printf("[td][6]mode_det1=0x%x, seq_sw_ctrl=0x%x\n",mode_det1,seq_sw_ctrl);
  printf("[td][7]st_seq_ctrl=0x%x, p1_interval_count=%ld\n",st_seq_ctrl,p1_interval_count);
  printf("[td][7-1]seq_ctrl_fsm=%d, seq_ctrl_counting_fsm=%d, seq_p1_fsm=%d,l1_crc_fail=%d,td_cfo_sfo_done=%d\n",seq_ctrl_fsm, seq_ctrl_counting_fsm, seq_p1_fsm,l1_crc_fail,td_cfo_sfo_done);
  printf("[td][8]manual_mode=0x%x, short_t2_ofdm=0x%x,seq_papr_fail=0x%x\n",manual_mode,short_t2_ofdm,seq_papr_fail);

 return;
}


void msb123x_fd_indicator(void)
{
  MAPI_U8 reg;

  MAPI_U16 a_right, b_left, hw_chlen,hw_bd_shift, hw_add_cir_shift;
  MAPI_U8  symali_histoy;

  MAPI_U8  icfo_done;
  MAPI_U8  fcfo_kp, fsfo_kp;
  MAPI_U16 symali_offset;
  MAPI_U8  coarse_symbol_align;
  MAPI_U8  symali_det_peak_num;
  MAPI_U16 symali_echo_location;
  MAPI_U16 symali_midpoint;
  MAPI_U16 no_image_range_sel;

  MAPI_U8  seq_sa_force_on, cir_shift_force_on;
  MAPI_U16 f_bd_shift, f_chlen, f_cir_shift;
  MAPI_U8  windows_en;
  MAPI_U16 windows_chlen;

  MAPI_U8 icfo_pp,icfo_ext, icfo_fsm,cpe_fsm;

  MAPI_U16 symali_st_fsym;
  MAPI_U8  symali_st_search,symali_st_read, symali_lock, symali_one_shot_done;


  ReadReg(0x2500+0x40*2 + 1,&reg);
  a_right = reg&0x1f;
  ReadReg(0x2500+0x40*2,&reg);
  a_right = (a_right<<8)|reg;

  ReadReg(0x2500+0x41*2 + 1,&reg);
  b_left = reg&0x1f;
  ReadReg(0x2500+0x41*2,&reg);
  b_left = (b_left<<8)|reg;

  ReadReg(0x2500+0x42*2 + 1,&reg);
  hw_chlen = reg&0x0f;
  ReadReg(0x2500+0x42*2,&reg);
  hw_chlen = (hw_chlen<<8)|reg;

  ReadReg(0x2500+0x43*2 + 1,&reg);
  hw_bd_shift = reg&0x0f;
  ReadReg(0x2500+0x43*2,&reg);
  hw_bd_shift = (hw_bd_shift<<8)|reg;

  ReadReg(0x2500+0x44*2 + 1,&reg);
  hw_add_cir_shift = reg&0x0f;
  ReadReg(0x2500+0x44*2,&reg);
  hw_add_cir_shift = (hw_add_cir_shift<<8)|reg;

  ReadReg(0x2500+0x45*2,&reg);
  symali_histoy = reg&0x1f;

  ReadReg(0x2500+0x0a*2,&reg);
  icfo_done = (reg>>7)&0x01;

  ReadReg(0x2500+0x0c*2,&reg);
  fcfo_kp = reg;

  ReadReg(0x2500+0x0c*2 + 1,&reg);
  fsfo_kp = reg;

  ReadReg(0x2500+0x25*2 + 1,&reg);
  symali_offset = reg&0x0f;
  ReadReg(0x2500+0x25*2,&reg);
  symali_offset = (symali_offset<<8)|reg;

  ReadReg(0x2500+0x33*2,&reg);
  coarse_symbol_align = reg;


  ReadReg(0x2500+0x4e*2,&reg);
  symali_det_peak_num = reg|0x0f;

  ReadReg(0x2500+0x4f*2 + 1,&reg);
  symali_echo_location = reg&0x0f;
  ReadReg(0x2500+0x4f*2,&reg);
  symali_echo_location = (symali_echo_location<<8)|reg;


  ReadReg(0x2500+0x5a*2 + 1,&reg);
  symali_midpoint = reg&0x1f;
  ReadReg(0x2500+0x5a*2,&reg);
  symali_midpoint = (symali_midpoint<<8)|reg;


  ReadReg(0x2500+0x5e*2 + 1,&reg);
  no_image_range_sel = reg;
  ReadReg(0x2500+0x5e*2,&reg);
  no_image_range_sel = (no_image_range_sel<<8)|reg;

  ReadReg(0x2400+0x56*2 + 1,&reg);
  f_bd_shift = reg;
  ReadReg(0x2400+0x56*2,&reg);
  f_bd_shift = (f_bd_shift<<8)|reg;

  seq_sa_force_on = f_bd_shift & 0x03;
  f_bd_shift = f_bd_shift>>4;

  ReadReg(0x2500+0x0e*2 + 1,&reg);
  f_cir_shift = reg;
  ReadReg(0x2500+0x0e*2,&reg);
  f_cir_shift = (f_cir_shift<<8)|reg;

  cir_shift_force_on = f_cir_shift & 0x03;
  f_cir_shift = f_cir_shift>>4;

  ReadReg(0x2500+0x27*2 + 1,&reg);
  f_chlen = reg&0x0f;
  ReadReg(0x2500+0x27*2,&reg);
  f_chlen = (f_chlen<<8)|reg;


  ReadReg(0x2500+0x01*2 + 1,&reg);
  windows_chlen = reg;
  ReadReg(0x2500+0x01*2,&reg);
  windows_chlen = (windows_chlen<<8)|reg;
  windows_en = windows_chlen&0x07;
  windows_chlen = windows_chlen>>3;


  ReadReg(0x2500+0x08*2,&reg);
  icfo_pp = reg&0x07;
  icfo_ext = (reg>>3)&0x01;

  ReadReg(0x2500+0x09*2,&reg);
  icfo_fsm = reg&0x0f;
  cpe_fsm = (reg>>4)&0x0f;

  ReadReg(0x2500+0x3f*2 + 1,&reg);
  symali_st_fsym = reg & 0x0f;
  ReadReg(0x2500+0x3f*2,&reg);
  symali_st_fsym = (symali_st_fsym<<8)|reg;

  symali_st_search = (symali_st_fsym >> 4) & 0x0f;
  symali_st_read   = (symali_st_fsym >> 8) & 0x03;
  symali_lock      = (symali_st_fsym >>10) & 0x01;
  symali_one_shot_done = (symali_st_fsym >>11) & 0x01;
  symali_st_fsym   = symali_st_fsym&0x0f;

  printf("[fd][1]a_right=%d, b_left=%d, hw_chlen=%d,hw_bd_shift=0x%x, hw_add_cir_shift=0x%x\n",a_right, b_left, hw_chlen,hw_bd_shift, hw_add_cir_shift);
  printf("[fd][1-1]seq_sa_force_on=0x%x, cir_shift_force_on=0x%x, f_chlen=%d, f_bd_shift=0x%x, f_cir_shift=0x%x\n",seq_sa_force_on,cir_shift_force_on,f_chlen,f_bd_shift,f_cir_shift);
  printf("[fd][1-2]symali_st_fsym=%d, symali_st_search=%d, symali_st_read=%d, symali_lock=%d, symali_one_shot_done=%d\n",symali_st_fsym, symali_st_search, symali_st_read, symali_lock, symali_one_shot_done);
  printf("[fd][2]symali_histoy=0x%x\n",symali_histoy);
  printf("[fd][3]icfo_done=0x%x\n",icfo_done);
  printf("[fd][3-1]icfo_pp=%d,icfo_ext=%d, icfo_fsm=%d,cpe_fsm=%d\n",icfo_pp,icfo_ext, icfo_fsm,cpe_fsm);
  printf("[fd][4]fcfo_kp=0x%x, fsfo_kp=0x%x, symali_offset=0x%x,coarse_symbol_align=0x%x\n",fcfo_kp, fsfo_kp, symali_offset,coarse_symbol_align);
  printf("[fd][5]symali_det_peak_num=%d, symali_echo_location=%d, symali_midpoint=%d,no_image_range_sel=0x%x\n",symali_det_peak_num, symali_echo_location, symali_midpoint,no_image_range_sel);
  printf("[fd][6]windows_en=0x%x, windows_chlen=%d\n",windows_en,windows_chlen);
  return;
}

void msb123x_fd_ext_info(void)
{
  MAPI_U8  reg;
  MAPI_U8  ce2_en;
  MAPI_U8  td_2p2;
  MAPI_U8  td_manual;
  MAPI_U8  fd_manual;
  // MAPI_U16  fd_coef_0,fd_coef_1;

  ReadReg(0x1900+0x30*2,&reg);
  ce2_en = (reg&0x10)>>4;

  ReadReg(0x1900+0x14*2,&reg);
  td_2p2 = reg&0x01;

  ReadReg(0x1900+0x20*2,&reg);
  td_manual = reg&0x07;

  ReadReg(0x1900+0x21*2,&reg);
  fd_manual = reg&0x07;
/*
  WriteReg(0x1900+0x15*2 + 1,0x00);
  ReadReg(0x1900+0x17*2 + 1,&reg);
  fd_coef_0 = reg&0x0f;
  ReadReg(0x1900+0x17*2,&reg);
  fd_coef_0 = (fd_coef_0<<8)|reg;

  WriteReg(0x1900+0x15*2 + 1,0x01);
  ReadReg(0x1900+0x17*2 + 1,&reg);
  fd_coef_1 = reg&0x0f;
  ReadReg(0x1900+0x17*2,&reg);
  fd_coef_1 = (fd_coef_1<<8)|reg;
*/


  printf("[fd_ext][1]ce2_en=%d, td_2p2=%d, td_manual=0x%x, fd_manual=0x%x\n",ce2_en, td_2p2, td_manual, fd_manual);
  // printf("[fd_ext][2]fd_coef=0x%x, 0x%x\n",fd_coef_0, fd_coef_1);
  return;
}

void msb123x_front_info(void)
{
  MAPI_U8 reg;
  MAPI_U8 agc_k, agc_ref, agc_lock;
  MAPI_U8 d0_k, d0_ref, d0_lock;
  MAPI_U8 d1_k, d1_ref, d1_lock;
  MAPI_U8 d2_k, d2_ref, d2_lock;
  MAPI_U16 agc_gain, d0_gain,d1_gain,d2_gain;
  MAPI_U8 iis_reg;

  ReadReg(0x3E00+0x08*2 + 1,&reg);
  agc_k = reg;
  ReadReg(0x3E00+0x09*2 + 1,&reg);
  agc_ref = reg;
  ReadReg(0x3E00+0x17*2 + 1,&reg);
  agc_lock = reg&0x01;

  ReadReg(0x3E00+0x38*2,&reg);
  d0_k = reg;
  ReadReg(0x3E00+0x38*2 + 1,&reg);
  d0_ref = reg;
  ReadReg(0x3E00+0x3b*2,&reg);
  d0_lock = reg&0x01;

  ReadReg(0x3E00+0x58*2,&reg);
  d1_k = reg;
  ReadReg(0x3E00+0x58*2 + 1,&reg);
  d1_ref = reg;
  ReadReg(0x3E00+0x5b*2,&reg);
  d1_lock = reg&0x01;

  ReadReg(0x3E00+0x60*2,&reg);
  d2_k = reg;
  ReadReg(0x3E00+0x60*2 + 1,&reg);
  d2_ref = reg;
  ReadReg(0x3E00+0x63*2,&reg);
  d2_lock = reg&0x01;

  // read gain value, sel = 0x03

  WriteReg(0x3E00+0x13*2,0x03);

  ReadReg(0x3E00+0x14*2 + 1,&reg);
  agc_gain = reg;
  ReadReg(0x3E00+0x14*2,&reg);
  agc_gain = (agc_gain<<8)|reg;

  ReadReg(0x3E00+0x3c*2 + 1,&reg);
  d0_gain = reg&0x0f;
  ReadReg(0x3E00+0x3c*2,&reg);
  d0_gain = (d0_gain<<8)|reg;


  ReadReg(0x3E00+0x5c*2 + 1,&reg);
  d1_gain = reg&0x0f;
  ReadReg(0x3E00+0x5c*2,&reg);
  d1_gain = (d1_gain<<8)|reg;


  ReadReg(0x3E00+0x64*2 + 1,&reg);
  d2_gain = reg&0x0f;
  ReadReg(0x3E00+0x64*2,&reg);
  d2_gain = (d2_gain<<8)|reg;

  ReadReg(0x3E00+0x50*2,&reg);
  iis_reg = reg;

  printf("[ft][1]agc_k=0x%x,agc_ref=0x%x,agc_lock=0x%x,agc_gain=0x%x\n",agc_k,agc_ref, agc_lock,agc_gain);
  printf("[ft][2]d0_k=0x%x,d0_ref=0x%x,d0_lock=0x%x,d0_gain=0x%x\n",d0_k,d0_ref, d0_lock,d0_gain);
  printf("[ft][3]d1_k=0x%x,d1_ref=0x%x,d1_lock=0x%x,d1_gain=0x%x\n",d1_k,d1_ref, d1_lock,d1_gain);
  printf("[ft][4]d2_k=0x%x,d2_ref=0x%x,d2_lock=0x%x,d2_gain=0x%x\n",d2_k,d2_ref, d2_lock,d2_gain);
  printf("[ft][5]iis=0x%x\n",iis_reg);

  return;
}


void msb123x_dummy_reg(void)
{

 MAPI_U8 reg = 0;
 MAPI_U16 reg_c3 = 0, reg_c5 = 0, reg_c6 = 0, reg_c9 = 0;
 MAPI_U16 reg_ca = 0, reg_cb = 0, reg_cc = 0;

 ReadReg(0x0c00+0x03*2 + 1,&reg);
 reg_c3 = reg;
 ReadReg(0x0c00+0x03*2,&reg);
 reg_c3 = (reg_c3<<8)|reg;

 ReadReg(0x0c00+0x05*2 + 1,&reg);
 reg_c5 = reg;
 ReadReg(0x0c00+0x05*2,&reg);
 reg_c5 = (reg_c5<<8)|reg;

 ReadReg(0x0c00+0x06*2 + 1,&reg);
 reg_c6 = reg;
 ReadReg(0x0c00+0x06*2,&reg);
 reg_c6 = (reg_c6<<8)|reg;

 ReadReg(0x0c00+0x09*2 + 1,&reg);
 reg_c9 = reg;
 ReadReg(0x0c00+0x09*2,&reg);
 reg_c9 = (reg_c9<<8)|reg;

 ReadReg(0x0c00+0x0a*2 + 1,&reg);
 reg_ca = reg;
 ReadReg(0x0c00+0x0a*2,&reg);
 reg_ca = (reg_ca<<8)|reg;

 ReadReg(0x0c00+0x0b*2 + 1,&reg);
 reg_cb = reg;
 ReadReg(0x0c00+0x0b*2,&reg);
 reg_cb = (reg_cb<<8)|reg;

 ReadReg(0x0c00+0x0c*2 + 1,&reg);
 reg_cc = reg;
 ReadReg(0x0c00+0x0c*2,&reg);
 reg_cc = (reg_cc<<8)|reg;

 printf("[dum][1]reg_c3=0x%x, reg_c5=0x%x, reg_c6=0x%x, reg_c9=0x%x\n",reg_c3, reg_c5, reg_c6, reg_c9);
 printf("[dum][2]reg_ca=0x%x, reg_cb=0x%x, reg_cc=0x%x\n",reg_ca, reg_cb, reg_cc);

 return;
}



void msb123x_sw_info(void)
{

 MAPI_U8 reg = 0;
 static MAPI_U8 counter = 0;
 ReadReg(0x0900+0x48*2,&reg);

 // printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
 printf("[msb123x]state = 0x%x.[%ld]\n",reg,MsOS_GetSystemTime());

#if 1
 if(reg < 0x09)
 {
   // msb123x_show_version();
   // msb123x_front_info();
   // msb123x_sw_indicator();
   // msb123x_top_indicator();
   // msb123x_snr_indicator();
   // msb123x_td_indicator();
   // msb123x_fd_indicator();
   // msb123x_fd_ext_info();
   // msb123x_dummy_reg();
   // msb123x_mod_info();
 }
 else
 {
   // msb123x_show_version();
   // msb123x_front_info();
   // msb123x_td_indicator();
   // msb123x_outer_info();
   // if ((counter%4) == 0)
   {
     // msb123x_front_info();
     msb123x_mod_info();
     // msb123x_sw_indicator();
     // msb123x_top_indicator();
     // msb123x_snr_indicator();
     // msb123x_td_indicator();
     // msb123x_fd_indicator();
     // msb123x_fd_ext_info();
     // msb123x_dummy_reg();
   }
 }
 printf("====================================\n");
#endif
 counter++;

 return;
}

#endif


void mapi_gpio_msb123x_On(void)
{
    //GPIO_EXT_RESET_NORMAL();
    Demodulator_ON();
    printf("MSB123X working\n");
}

void mapi_gpio_msb123x_Off(void)
{
    //GPIO_EXT_RESET_RESET();
    Demodulator_OFF();
    printf("MSB123X resetting\n");
}

typedef struct
{
    void (*SetOn)(void);
    void (*SetOff)(void);
}mapi_gpio;

mapi_gpio GPIOhandler;
mapi_gpio* mapi_gpio_GetGPIO_Dev(void)
{
    mapi_gpio *handler=&GPIOhandler;
    handler->SetOn= mapi_gpio_msb123x_On;
    handler->SetOff = mapi_gpio_msb123x_Off;
    return handler;
}

MAPI_BOOL mapi_i2c_WriteBytes_demod(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr, MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_WriteBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_123X_1, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

MAPI_BOOL mapi_i2c_ReadBytes_demod(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr,MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_ReadBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_123X_1, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

MAPI_BOOL mapi_i2c_WriteBytes_spi(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr, MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_WriteBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_123X_2, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

MAPI_BOOL mapi_i2c_ReadBytes_spi(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr,MAPI_U16 u16Size, MAPI_U8 *pu8Data)
{
    BOOLEAN bRet = 0;
    bRet = MDrv_IIC_ReadBytes(DEMOD_DYNAMIC_SLAVE_ID_MSB_123X_2, u8AddrSize, pu8Addr, u16Size, pu8Data);
    return bRet;
}

typedef struct
{
    MAPI_BOOL (*WriteBytes)(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr, MAPI_U16 u16Size, MAPI_U8 *pu8Data);
    MAPI_BOOL (*ReadBytes)(MAPI_U8 u8AddrSize, MAPI_U8 *pu8Addr,MAPI_U16 u16Size, MAPI_U8 *pu8Data);
}mapi_i2c;

mapi_i2c DemodI2Chandler;
mapi_i2c SpiI2Chandler;
mapi_i2c* mapi_i2c_GetI2C_Dev(MAPI_U32 u32gID)
{
    mapi_i2c *handler;
    switch(u32gID)
    {
        default:
            printf("iic device not supported\n");
        case MSB123X_DEMOD_IIC:
            handler=&DemodI2Chandler;
            handler->WriteBytes= mapi_i2c_WriteBytes_demod;
            handler->ReadBytes = mapi_i2c_ReadBytes_demod;
            break;
        case MSB123X_SPI_IIC:
            handler=&SpiI2Chandler;
            handler->WriteBytes= mapi_i2c_WriteBytes_spi;
            handler->ReadBytes = mapi_i2c_ReadBytes_spi;
            break;
    }
    return handler;
}
/*@ </Include> @*/
/*@ <Definitions> @*/
#define ERR_DEMOD_MSB(x)    //x
#define DBG_DEMOD_MSB(x)    //x
#define DBG_DEMOD_FLOW(x)   //x
#define DBG_GET_SIGNAL(x)    //x
#define DBG_DEMOD_LOAD_I2C(x) //x
#define DBG_DEMOD_CHECKSUM(x) //x
#define DBG_FLASH_WP(x)       //x
#define DBG_SIGNAL_TPS(x)     //x
#define DBG_DUMP_LOAD_DSP_TIME 0
#define MDrv_Timer_Delayms OS_DELAY_TASK
#define MDrv_Timer_GetTime0 OS_SYSTEM_TIME
//#define TS_CLK_INV 1

#define PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 0
#define LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C 0
#define SDRAM_DATA_CHECK                 0
#define LOAD_CODE_I2C_BLOCK_NUM          0x80
#define TIMING_VERIFICATION              0
#define SDRAM_BASE                       0x5000

// msb123x flash size: 1Mbits
#define MAX_MSB123X_LIB_LEN              131072
#define FLASH_WP_ENABLE                  1

#define MSB123x_BOOT  0x01
#define MSB123x_DVBT2 0x02
#define MSB123x_DVBT  0x04
#define MSB123x_DVBC  0x08
#define MSB123x_ALL   0x0F

#define WIMBLEDON_BOOT_START_ADDR     0x00000
#define WIMBLEDON_BOOT_END_ADDR       0x00FFF
#define WIMBLEDON_DVBT2_P1_START_ADDR 0x01000
#define WIMBLEDON_DVBT2_P1_END_ADDR   0x08FFF
#define WIMBLEDON_DVBT2_P2_START_ADDR 0x09000
#define WIMBLEDON_DVBT2_P2_END_ADDR   0x0FFFF
#define WIMBLEDON_DVBT_START_ADDR     0x10000
#define WIMBLEDON_DVBT_END_ADDR       0x17FFF
#define WIMBLEDON_DVBC_START_ADDR     0x18000
#define WIMBLEDON_DVBC_END_ADDR       0x1FFFF

#define WIMBLEDON_WINDOWS_BASE                0x100
#define WIMBLEDON_BOOT_WINDOWS_OFFSET         WIMBLEDON_WINDOWS_BASE
#define WIMBLEDON_DVBT2_P2_WINDOWS_OFFSET    (WIMBLEDON_WINDOWS_BASE + 0x08)
#define WIMBLEDON_DVBT2_P1_WINDOWS_OFFSET    (WIMBLEDON_DVBT2_P2_WINDOWS_OFFSET + 0x08)
#define WIMBLEDON_DVBT_WINDOWS_OFFSET        (WIMBLEDON_DVBT2_P1_WINDOWS_OFFSET + 0x08)
#define WIMBLEDON_DVBC_WINDOWS_OFFSET        (WIMBLEDON_DVBT_WINDOWS_OFFSET + 0x08)

static MAPI_U8 g_msb123x_plp_id   = 0xff;
static MAPI_U8 g_msb123x_group_id = 0xff;

static float g_msb123x_fSNR = 0.0;

static S_DVBT2_SQI_CN_NORDIGP1 g_msb123x_dvbt2_sqi_cn_nordigp1[] =
{
    {_T2_QPSK, _T2_CR1Y2, 3.5},
    {_T2_QPSK, _T2_CR3Y5, 4.7},
    {_T2_QPSK, _T2_CR2Y3, 5.6},
    {_T2_QPSK, _T2_CR3Y4, 6.6},
    {_T2_QPSK, _T2_CR4Y5, 7.2},
    {_T2_QPSK, _T2_CR5Y6, 7.7},

    {_T2_16QAM, _T2_CR1Y2, 8.7},
    {_T2_16QAM, _T2_CR3Y5, 10.1},
    {_T2_16QAM, _T2_CR2Y3, 11.4},
    {_T2_16QAM, _T2_CR3Y4, 12.5},
    {_T2_16QAM, _T2_CR4Y5, 13.3},
    {_T2_16QAM, _T2_CR5Y6, 13.8},

    {_T2_64QAM, _T2_CR1Y2, 13.0},
    {_T2_64QAM, _T2_CR3Y5, 14.8},
    {_T2_64QAM, _T2_CR2Y3, 16.2},
    {_T2_64QAM, _T2_CR3Y4, 17.7},
    {_T2_64QAM, _T2_CR4Y5, 18.7},
    {_T2_64QAM, _T2_CR5Y6, 19.4},

    {_T2_256QAM, _T2_CR1Y2, 17.0},
    {_T2_256QAM, _T2_CR3Y5, 19.4},
    {_T2_256QAM, _T2_CR2Y3, 20.8},
    {_T2_256QAM, _T2_CR3Y4, 22.9},
    {_T2_256QAM, _T2_CR4Y5, 24.3},
    {_T2_256QAM, _T2_CR5Y6, 25.1},
    {_T2_QAM_UNKNOWN, _T2_CR_UNKNOWN, 0.0}
};

typedef enum
{
    DEV_MSB123x_FFT_2K      = 0x0,
    DEV_MSB123x_FFT_8K      = 0x1,
    DEV_MSB123x_FFT_4K      = 0x2,
    DEV_MSB123x_FFT_1K      = 0x3,
    DEV_MSB123x_FFT_16K      = 0x4,
    DEV_MSB123x_FFT_32K      = 0x5,
    DEV_MSB123x_FFT_8K_     = 0x6,
    DEV_MSB123x_FFT_32K_    = 0x7,
} DEV_MSB123x_FFT_VAL;

/*@ </Definitions> @*/
MAPI_U8 u8DeviceBusy = 0;
//MAPI_BOOL m_bSerialOut = MAPI_FALSE;
//MAPI_U8 gVifTop = VIF_TOP;
//MAPI_U8 gVifSoundSystem = (MAPI_U8)VIF_SOUND_DK2;
//MAPI_U8 gVifIfFreq = (MAPI_U8)IF_FREQ_3890;
MAPI_U8 g_u8MsbData[6];
MAPI_U8 gu8ChipRevId = 0;
//MAPI_U8 gCalIdacCh0 = 0;
//MAPI_U8 gCalIdacCh1 = 0;
//S_CMDPKTREG gsCmdPacket;
//MAPI_U8 gu8DemoDynamicI2cAddress = DEMOD_DYNAMIC_SLAVE_ID_1; //0x32;//Default
MAPI_BOOL FECLock = MAPI_FALSE;
//MAPI_BOOL gbTVAutoScanEn = MAPI_FALSE; //init value=MAPI_FALSE, follow with auto/manual scan
EN_DEVICE_DEMOD_TYPE m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_DVB_T2;
static MAPI_U32 u32ChkScanTimeStart = 0;
static MAPI_BOOL bPower_init_en = MAPI_FALSE;
//static MAPI_U32 g_u32Frequency = 0;
static MAPI_BOOL p1_ever_lock_flag = 0;

#if(TIMING_VERIFICATION == 1)
static MAPI_U32 tmm_1 = 0x00;
static MAPI_U32 tmm_2 = 0x00;
static MAPI_U32 tmm_3 = 0x00;
static MAPI_U32 tmm_4 = 0x00;
static MAPI_U32 tmm_5 = 0x00;
static MAPI_U32 tmm_6 = 0x00;
static MAPI_U32 tmm_7 = 0x00;
static MAPI_U32 tmm_8 = 0x00;
static MAPI_U32 tmm_9 = 0x00;
static MAPI_U32 tmm_10 = 0x00;
static MAPI_U32 tmm_11 = 0x00;
static MAPI_U32 tmm_12 = 0x00;
static MAPI_U32 tmm_13 = 0x00;
static MAPI_U32 tmm_14 = 0x00;
static MAPI_U32 tmm_15 = 0x00;
static MAPI_U32 tmm_16 = 0x00;
static MAPI_U32 tmm_17 = 0x00;
static MAPI_U32 tmm_18 = 0x00;
static MAPI_U32 tmm_19 = 0x00;
static MAPI_U32 tmm_20 = 0x00;

#define GIVE_ME_TIME MsOS_GetSystemTime();
#endif

static MAPI_BOOL bDoReset = MAPI_FALSE;
static MAPI_U32 u32StartTime = 0;
MAPI_U8 gQamVal;

#define resetDemodTime  50
#define waitFlashTime   50

#if (LOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
static MAPI_U8 g_WO_SPI_FLASH = 1;
#else
static MAPI_U8 g_WO_SPI_FLASH = 0;
#endif

// ONLY wo flash procedure used.
static MAPI_U8 g_sdram_code = 0x0;
static MAPI_U8 g_sram_code  = 0x0;

#if(TIMING_VERIFICATION == 1)
static void show_timer(void)
{
    printf("***************************\n");
    printf("[tmm1]t2-t1 = %ld (%ld - %ld)\n", tmm_2 - tmm_1, tmm_2, tmm_1);
    printf("[tmm2]t4-t3 = %ld (%ld - %ld)\n", tmm_4 - tmm_3, tmm_4, tmm_3);
    printf("[tmm3]t6-t5 = %ld (%ld - %ld)\n", tmm_6 - tmm_5, tmm_6, tmm_5);
    printf("[tmm4]t8-t7 = %ld (%ld - %ld)\n", tmm_8 - tmm_7, tmm_8, tmm_7);
    printf("[tmm5]t10-t9 = %ld (%ld - %ld)\n", tmm_10 - tmm_9, tmm_10, tmm_9);
    printf("[tmm6]t12-t11 = %ld (%ld - %ld)\n", tmm_12 - tmm_11, tmm_12, tmm_11);
    printf("[tmm7]t14-t13 = %ld (%ld - %ld)\n", tmm_14 - tmm_13, tmm_14, tmm_13);
    printf("[tmm8]t16-t15 = %ld (%ld - %ld)\n", tmm_16 - tmm_15, tmm_16, tmm_15);
    printf("[tmm9]t18-t17 = %ld (%ld - %ld)\n", tmm_18 - tmm_17, tmm_18, tmm_17);
    printf("[tmm10]t20-t19 = %ld (%ld - %ld)\n", tmm_20 - tmm_19, tmm_20, tmm_19);
    printf("[tmm11]lock_time# = %ld (%ld - %ld)\n", tmm_14 - u32StartTime, tmm_14, u32StartTime);
    printf("[tmm12]lock-setf = %ld (%ld - %ld)\n", tmm_14 - tmm_11, tmm_14, tmm_11);
    printf("[tmm13]lock-loaddsp = %ld (%ld - %ld)\n", tmm_14 - tmm_9, tmm_14, tmm_9);
    printf("***************************\n");
}
#endif

#if 1 //FIXME - 2009.11.08 by chunlun.lai
/****************************************************************************
Subject:    Function providing approx. result of Log10(X)
Function:   Log10Approx
Parmeter:   Operand X in float
Return:     Approx. value of Log10(X) in float
Remark:      Ouput range from 0.0, 0.3 to 9.6 (input 1 to 2^32)
 *******:**********************************************************************/
static float Log10Approx(float flt_x)
{
    MAPI_U32 u32_temp = 1;
    MAPI_U8 indx = 0;
    do
    {
        u32_temp = u32_temp << 1;
        if(flt_x < (float)u32_temp)
            break;
    }
    while(++indx < 32);
    // 10*log10(X) ~= 0.3*N, when X ~= 2^N
    return (float)0.3 * indx;
}
#endif

static MAPI_BOOL IspCheckVer(MAPI_U8* pLibData, MAPI_BOOL* pMatch)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8  bReadData[VERSION_CODE_SIZE];
    MAPI_U32  indx = 0;
    *pMatch = true;

    MAPI_U8 bWriteData[5] = {0x4D, 0x53, 0x54, 0x41, 0x52};
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);

    MAPI_U8    bAddr[1], bError = true;
    //MAPI_U16   Count;

    memset(bReadData, 0 , sizeof(bReadData));

    bAddr[0] = 0x10;
    //dwStartAddr=0;

    bWriteData[0] = 0x03;
    bWriteData[1] = VERSION_CODE_ADDR >> 16;
    bWriteData[2] = VERSION_CODE_ADDR >> 8;
    bWriteData[3] = VERSION_CODE_ADDR & 0xFF;

    bError &=  iptr->WriteBytes(1, bAddr, 4, bWriteData);

    bAddr[0] = 0x11;
    bError &= iptr->ReadBytes(1, bAddr, VERSION_CODE_SIZE, bReadData);

    bWriteData[0] = 0x12;
    bError &= iptr->WriteBytes(0, NULL, 1,  bWriteData);

    if(MAPI_FALSE == bError)
    {
        bWriteData[0] = 0x24 ;
        iptr->WriteBytes(0, NULL, 1, bWriteData);

        return MAPI_FALSE;
    }

    bWriteData[0] = 0x24 ;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    printf("sttest version data = ");
    for(indx = 0; indx < (VERSION_CODE_SIZE); indx++)
    {
        printf(" %x ,", bReadData[indx]);
        if(pLibData[indx+VERSION_CODE_ADDR] != bReadData[indx])
        {
            *pMatch = false;
            //break;
        }
    }
    printf(" \n");

    return MAPI_TRUE;
}

static MAPI_BOOL dram_crc_check(MAPI_U16 chksum_lib, MAPI_BOOL* pMatch)
{
    MAPI_U16  chksum = 0;
    // MAPI_U16  chksum_lib = 0;
    MAPI_U16  u16Addr = 0;
    MAPI_U8   u8MsbData[5];
    MAPI_U8   reg = 0;
    MAPI_BOOL bRet;
    MAPI_U8   mcu_status = 0;

    *pMatch = false;

    // MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);
    // iptr->WriteBytes(0, NULL, 5, bWriteData);

/// crc H byte
    u16Addr = 0x0c00+0x0d*2+1;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, &reg);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);


   chksum = reg;

/// crc L byte
    u16Addr = 0x0c00+0x0d*2;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, &reg);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);


   chksum = (chksum<<8)|reg;

// get mcu status

    u16Addr = 0x0900+0x4f*2;

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, &reg);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);


    mcu_status = reg;


/// check the crc in dsp lib array

    if ((mcu_status == 0xaa) && ((chksum_lib&0xff00) == (chksum&0xff00)) )
      *pMatch = true;
    else if(chksum_lib == chksum)
      *pMatch = true;

    DBG_DEMOD_CHECKSUM(printf("[crc]chksum_lib=0x%x, chksum=0x%x, bRet=%d, Match=%d, mcu_status=0x%x\n",chksum_lib,chksum,bRet,*pMatch,mcu_status));

    return bRet;
}

#if (FLASH_WP_ENABLE == 1)
static MAPI_BOOL msb123x_flash_WP_reg_read(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    MAPI_BOOL bRet;
    MAPI_U8   u8MsbData[5];
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);

    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, u8MsbData);
    iptr->ReadBytes(0, NULL, 1, pu8Data);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);
    return bRet;
}

static MAPI_BOOL msb123x_flash_WP_reg_write(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_BOOL bRet;
    MAPI_U8   u8MsbData[6];
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);

    //bRet &= iptr->SetSpeed(0);


    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;
    u8MsbData[5] = u8Data;

    u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 6, u8MsbData);

    u8MsbData[0] = 0x34;
    bRet=iptr->WriteBytes(0, NULL, 1, u8MsbData);
    return bRet;
}

static MAPI_BOOL msb123x_flash_WRSR(MAPI_U8 reg)
{
    MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
    MAPI_U8     bAddr[1];
    MAPI_BOOL   rbet = true;

    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);

    // WREN
    bAddr[0] = 0x10;
    bWriteData[0] = 0x06;
    iptr->WriteBytes(1, bAddr, 1, bWriteData);

    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    // WRSR
    bAddr[0] = 0x10;
    bWriteData[0] = 0x01;
    bWriteData[1] = reg;
    iptr->WriteBytes(1, bAddr, 2, bWriteData);

    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    // WRDI
    bAddr[0] = 0x10;
    bWriteData[0] = 0x04;
    iptr->WriteBytes(1, bAddr, 1, bWriteData);

    bWriteData[0] = 0x12;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    // end
    bWriteData[0] = 0x24;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    DBG_FLASH_WP(printf("[wb]msb123x_flash_WRSR, reg=0x%x\n",reg);)

    return rbet;
}

static MAPI_BOOL msb123x_flash_SRSR(MAPI_U8 *p_reg)
{

  MAPI_U8 bWriteData[5]={0x4D, 0x53, 0x54, 0x41, 0x52};
  MAPI_U8   bAddr[1];
  MAPI_BOOL   bRet = true;

  mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_SPI_IIC);
  iptr->WriteBytes(0, NULL, 5, bWriteData);

  bAddr[0] = 0x10;
  bWriteData[0] = 0x05;
  iptr->WriteBytes(1, bAddr, 1, bWriteData);

  bAddr[0] = 0x11;
  iptr->ReadBytes(1, bAddr, 1, p_reg);

  bWriteData[0] = 0x12;
  iptr->WriteBytes(0, NULL, 1, bWriteData);

  // end
  bWriteData[0] = 0x24 ;
  iptr->WriteBytes(0, NULL, 1, bWriteData);

  DBG_FLASH_WP(printf("[wb]msb123x_flash_SRSR, reg=0x%x\n",*p_reg);)

  return bRet;
}

static MAPI_BOOL msb123x_flash_WP(MAPI_U8 enable)
{
    MAPI_U8 reg;
    MAPI_BOOL bRet = true;
    MAPI_U8 u8_count = 0;

    DBG_FLASH_WP(printf("[wb]msb123x_flash_WP_Enable=%d\n",enable);)

    if (enable == 1)
    {
      u8_count = 20;
      do
      {
        msb123x_flash_SRSR(&reg);
        usleep(1*1000);
      }while((reg&0x01) && (u8_count--));

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }

      msb123x_flash_WRSR(reg|0x9c);


      u8_count = 20;
      do
      {
        msb123x_flash_SRSR(&reg);
        usleep(1*1000);
      }while((reg&0x01) && (u8_count--));

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }

      // active low
      // pull low
      bRet &= msb123x_flash_WP_reg_read(0x0900+0x63*2+1, &reg);
      bRet &= msb123x_flash_WP_reg_write(0x0900+0x63*2+1, reg&(~0x08));

      // gpio11 output enable
      bRet &= msb123x_flash_WP_reg_read(0x0900+0x64*2+1, &reg);
      bRet &= msb123x_flash_WP_reg_write(0x0900+0x64*2+1, reg&(~0x08));
    }
    else
    {
      // unactive high
      // pull high
      bRet &= msb123x_flash_WP_reg_read(0x0900+0x63*2+1, &reg);
      bRet &= msb123x_flash_WP_reg_write(0x0900+0x63*2+1, reg|0x08);

      // gpio11 output enable
      bRet &= msb123x_flash_WP_reg_read(0x0900+0x64*2+1, &reg);
      bRet &= msb123x_flash_WP_reg_write(0x0900+0x64*2+1, reg&(~0x08));

      u8_count = 20;
      do
      {
        msb123x_flash_SRSR(&reg);
        usleep(1*1000);
      }while((reg&0x01) && (u8_count--));

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }

      msb123x_flash_WRSR(reg&(~0x9c));

      u8_count = 20;
      do
      {
        msb123x_flash_SRSR(&reg);
        usleep(1*1000);
      }while((reg&0x01) && (u8_count--));

      if (u8_count == 0)
      {
        bRet = false;
        DBG_FLASH_WP(printf("[wb]Err, flash_SRSR timeout!!!\n");)
        return bRet;
      }
    }

    return bRet;
}
#endif

// 144 ms roughly
MAPI_BOOL MSB123x_HW_init(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8 u8_tmp = 0;
    MAPI_U8 u8_timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]MSB123x_HW_init\n"));

#if(TIMING_VERIFICATION == 1)
    tmm_1 = GIVE_ME_TIME
#endif

    // Reset MCU
    bRet &= WriteReg2bytes(0x0b00 + (0x19) * 2, 0x0003);

    bRet &= WriteReg2bytes(0x1200, 0x0000);

    // miu software reset for pwr down tolerance
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0c01);

    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0c00);

    // -------------------------------------------------------------------
    // Initialize DMD_ANA_MISC
    // -------------------------------------------------------------------

    // [1:0]    reg_mpll_loop_div_first
    // [15:8]   reg_mpll_loop_div_second
    bRet &= WriteReg2bytes(0x0A00 + (0x33) * 2, 0x0902);

    // [2:0]    reg_mpll_ictrl
    // [3]  reg_mpll_in_sel
    // [4]  reg_mpll_xtal2adc_sel
    // [5]  reg_mpll_xtal2next_pll_sel
    // [6]  reg_mpll_vco_offset
    // [7]  reg_mpll_pd
    // [8]  reg_xtal_en
    // [10:9]   reg_xtal_sel
    // [11]     reg_mpll_porst
    // [12]     reg_mpll_reset
    // [13]     reg_pd_dmpll_clk
    // [14]     reg_pd_3p3_1
    // [15]     reg_pd_3p3_2

    bRet &= WriteReg2bytes(0x0A00 + (0x35) * 2, 0x1804);
    bRet &= WriteReg2bytes(0x0A00 + (0x35) * 2, 0x0004);

    // [0]  reg_mpll_clk_dp_pd  dummy
    // [1]  reg_adc_clk_pd      ADC output clock power down
    // [2]  reg_mpll_div2_pd    MPLL_DIV2 power down
    // [3]  reg_mpll_div3_pd    MPLL_DIV3 power down
    // [4]  reg_mpll_div4_pd    MPLL_DIV4 power down
    // [5]  reg_mpll_div8_pd    MPLL_DIV8 power down
    // [6]  reg_mpll_div10_pd   MPLL_DIV10 power down
    // [13:8]  reg_mpll_adc_div_sel select the ADC clock divide ratio,ADC clk=XTAL_IN * (LOOP_DIV_FIRST*LOOP_DIV_SECOND)/div_ratio

    bRet &= WriteReg2bytes(0x0A00 + (0x30) * 2, 0x1200);

    // -------------------------------------------------------------------
    // Begin Initialize Initialize ADC I/Q
    // -------------------------------------------------------------------
    // [0]  Q channel ADC power down
    // [1]  I channel ADC power down
    // [2]  Q channel clamp enable. 0:enable, 1:disable
    // [3]  I channel clamp enable. 0:enable, 1:disable
    // [6:4]    I channel input mux control;
    //      3'b000=I channel ADC calibration mode input
    //          3'b001=VIF signal from VIFPGA
    //          3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //          all the other combination are only for test mode, don't use without understanding.
    // [10:8]   Q channel input mux control;
    //      3'b000=Q channel ADC calibration mode input
    //          3'b001=VIF signal from VIFPGA 3'b010 = SSIF signal from PAD_SIFP(M)
    //          3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //          all the other combination are only for test mode, don't use without understanding.
    // [12] ADC I,Q swap enable; 1: swap
    // [13] ADC clock out select; 1: ADC_CLKQ
    // [14] ADC linear calibration bypass enable; 1:enable
    // [15] ADC internal 1.2v regulator control always 0 in T3
    bRet &= WriteReg2bytes(0x0A00 + (0x01) * 2, 0x0440);


    // [0]  Channel I ADC power down: 1=power dwon
    // [1]  Channel Q ADC power down: 1=power dwon
    // [2]  power down clamp buffer for test mode
    // [3]  change ADC reference voltage for SSIF
    // [6:4]    ADC source bias current control
    // [9:8]    XTAL receiver amp gain
    bRet &= WriteReg2bytes(0x0A00 + (0x0c) * 2, 0x0002);

    // [3:0]    clamp voltage control
    //          3'b000 = 0.7v
    //          3'b001 = 0.75v
    //          3'b010 = 0.5v
    //          3'b011 = 0.4v
    //          3'b100 = 0.8v
    //          3'b101 = 0.9v
    //          3'b110 = 0.65v
    //          3'b111 = 0.60v
    // [4]  REFERENCE power down
    bRet &= WriteReg2bytes(0x0A00 + (0x20) * 2, 0x0000);

    // Set ADC gain is 1
    bRet &= WriteReg2bytes(0x0A00 + (0x0b) * 2, 0x0909);

    // Disable ADC Sign bit
    bRet &= WriteReg2bytes(0x0A00 + (0x2e) * 2, 0x0200);

    // ADC I channel offset
    bRet &= WriteReg2bytes(0x0A00 + (0x2a) * 2, 0x0c00);

    // ADC Q channel offset
    bRet &= WriteReg2bytes(0x0A00 + (0x2b) * 2, 0x0c00);
    // -------------------------------------------------------------------
    // End Initialize Initialize ADC I/Q
    // -------------------------------------------------------------------


    // [15:0]   reg_mpll_test
    // [4]  mpll lock detector enable
    bRet &= WriteReg2bytes(0x0A00 + (0x34) * 2, 0x0010);


    // @0x0919
    // [5:0]    reg_ckg_spif
    // [15:8]   reg_ckg_miu
    bRet &= WriteReg2bytes(0x0900 + (0x19) * 2, 0x3c0c);


    // @0x091b
    // [2:0]    reg_ckg_dvbt2_outer1x
    // [6:4]    reg_ckg_dvbt2_outer2x
    // [10:8]   reg_ckg_syn_miu
    // [14:12]  reg_ckg_syn_ts
    bRet &= WriteReg2bytes(0x0900 + (0x1b) * 2, 0x0000);


    /*Beg initialize MIU*/

    // dummy register setting
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0000);

    // dummy register setting
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0000);

    // dummy register setting
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0000);

    // miu software reset
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0c01);
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0c00);


    // APLL PORST
    bRet &= WriteReg2bytes(0x1200 + (0x11) * 2, 0x60cc);

    bRet &= WriteReg2bytes(0x1200 + (0x11) * 2, 0x00cc);

    // set frequence 180MHz
    bRet &= WriteReg2bytes(0x1200 + (0x11) * 2, 0x0000);

    bRet &= WriteReg2bytes(0x1200 + (0x10) * 2, 0x4200); //0x4200 //0x4220 NG //0x4a20 for IQ.TS debugg
    // bRet &= WriteReg2bytes(0x1200+(0x10)*2, 0x3a20);  // miu b/w issue djb fail, michael huang


    // 0x4220 -> 0x5220 for hi/low temp test.

    bRet &= WriteReg2bytes(0x1200 + (0x12) * 2, 0x4000);

    bRet &= WriteReg2bytes(0x1200 + (0x13) * 2, 0x0500);

    bRet &= WriteReg2bytes(0x1200 + (0x16) * 2, 0x0030);

    bRet &= WriteReg2bytes(0x1200 + (0x01) * 2, 0x8100);
    bRet &= WriteReg2bytes(0x1200 + (0x01) * 2, 0xe100);
    bRet &= WriteReg2bytes(0x1200 + (0x01) * 2, 0x8100);

    // in_phase
    bRet &= WriteReg2bytes(0x1200 + (0x02) * 2, 0x0371);

    // tREFRESH                      : [7:0] * 16
    bRet &= WriteReg2bytes(0x1200 + (0x03) * 2, 0x0040);

    // reg_tRAS                      : [3:0]         // 48.00 / 6.0ns = 8
    // reg_tRC                       : [7:4]         // 90.00 / 7.5ns = 12
    // reg_tRCD                      : [11:8]        // (min  12.50 ns) / 2.5ns = 5   // 5
    // reg_tRCD                      : [11:8]   // 22.50 / 7.5ns = 3
    // reg_tRP                       : [15:12]       // 22.50 / 7.5ns = 3
    bRet &= WriteReg2bytes(0x1200 + (0x04) * 2, 0x44c8);

    // reg_tRRD                      : [3:0]         3
    // tWR                           : [7:4]         2
    // reg_tMRD                      : [11:8]        2
    // reg_tRTP                      : [15:12]  0
    // reg_tRAS                      : [3:0]         // 48.00 / 6.0ns = 8
    bRet &= WriteReg2bytes(0x1200 + (0x05) * 2, 0x0233);


    // reg_w2r_dly(tWTR)             : [3:0]         3
    // reg_w2r_oen_dly               : [7:4]         6
    // reg_r2w_dly                   : [11:8]        6
    // reg_r2w_oen_dly               : [15:12]       8
    bRet &= WriteReg2bytes(0x1200 + (0x06) * 2, 0x5634);

    // tRFC                          : [5:0]         e
    // reg_tRAS[4]                   : [6]           0
    // reg_tRC[4]                    : [7]           0
    // reg_write_latency             : [10:8]        1
    // reg_tCCD                      : [15:14]       1
    bRet &= WriteReg2bytes(0x1200 + (0x07) * 2, 0x410e);

    bRet &= WriteReg2bytes(0x1200 + (0x0e) * 2, 0x1800);

    bRet &= WriteReg2bytes(0x1200 + (0x1b) * 2, 0x0161); // 0x0167);

    bRet &= WriteReg2bytes(0x1200 + (0x1c) * 2, 0x00b0);

    /*Beg SIM SPIF initialize*/

    // mask other request
    bRet &= WriteReg2bytes(0x1200 + (0x23) * 2, 0x0000);

    // reg_rq0_round_robin : [0]
    bRet &= WriteReg2bytes(0x1200 + (0x20) * 2, 0xc001);

    // miu software reset
    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0c01);


    bRet &= WriteReg2bytes(0x1200 + (0x0f) * 2, 0x0c00);

    bRet &= WriteReg2bytes(0x1200 + (0x01) * 2, 0x010d);

    /*Beg Initial DRAM start here!!!*/

    bRet &= WriteReg2bytes(0x1200 + (0x00) * 2, 0x0001);

    // wait init_done

    bRet &= ReadReg(0x1201, &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb123x]MIU wait init done, u8_tmp=0x%x, bRet=0x%x\n", u8_tmp, bRet));
    while(u8_tmp != 0x80)
    {
        if(u8_timeout++ > 200)
        {
            ERR_DEMOD_MSB(printf("[msb123x][err]MIU init failure...\n"));
            return MAPI_FALSE;
        }
        // 10us delay
        usleep(10);
        bRet &= ReadReg(0x1201, &u8_tmp);
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x]MIU init done, u8_tmp=0x%x, bRet=0x%x\n", u8_tmp, bRet));
    /*Beg set MIU self test parameter*/

    bRet &= WriteReg2bytes(0x1200 + (0x71) * 2, 0x0000);

    // length
    bRet &= WriteReg2bytes(0x1200 + (0x72) * 2, 0x0010);

    // test data
    bRet &= WriteReg2bytes(0x1200 + (0x74) * 2, 0x5aa5);

    // reg_test_en                   : [0]
    // reg_test_mode                 : [2:1] 00 : address,
    //                                       01 : test data
    //                                       10 : shift data
    // reg_inv_data                  : [3]
    // reg_test_loop                 : [4]
    // reg_force_out                 : [5]
    // reg_force_in                  : [6]
    // reg_read_only                 : [8]
    // reg_write_only                : [9]
    bRet &= WriteReg2bytes(0x1200 + (0x70) * 2, 0x0001);

    // wait for test done

    bRet &= ReadReg((0x1200 + (0x70) * 2 + 1), &u8_tmp);
    DBG_DEMOD_LOAD_I2C(printf("[msb123x]MIU wait test done, u8_tmp=0x%x,bRet=0x%x\n", u8_tmp, bRet));
    while(u8_tmp != 0x80)
    {
        bRet &= ReadReg((0x1200 + (0x70) * 2 + 1), &u8_tmp);
    }
    // test done.

    // test result check

    bRet &= ReadReg((0x1200 + (0x70) * 2 + 1), &u8_tmp);

    if(u8_tmp == 0x40)
    {
        ERR_DEMOD_MSB(printf("@msb123x, error, MIU self test fail !!!!\n"));
        bRet = false;
    }
    else
    {
        DBG_DEMOD_LOAD_I2C(printf("@msb123x, MIU self test successful.\n"));
    }

    bRet &= WriteReg2bytes(0x1200 + (0x70) * 2, 0x0000);

    /*End initialize MIU*/

    /* Beg Turn on pads */
    // ------Turn off all pad in
    // [0] reg_set_pad_low
    // [1] reg_set_pad_high
    // [2] reg_set_i2cs_pad_low
    // [3] reg_set_i2cs_pad_high
    // [8] reg_turn_off_pad
    bRet &= WriteReg2bytes(0x0900 + (0x28) * 2, 0x0000);

    // ------IF AGC PWM pad on
    // [0]      reg_rf_agc_pad_oen
    // [1]      reg_if_agc_pad_oen
    // [9:8]    reg_rf_agc_sel[1:0]
    // [11:10]  reg_if_agc_sel[1:0]
    // [13:12]  reg_rf_agc_ctrl_sel[1:0] 1:PWN on 2:UP GPIO on
    // [15:14]  reg_if_agc_ctrl_sel[1:0] 1:PWN on 2:DOWN GPIO on
    bRet &= WriteReg2bytes(0x0900 + (0x2a) * 2, 0x8001);

    // ------I2CM pad on
    // [1:0]    reg_iicm_pad_sel[1:0]   1:iicm enable 2:UART enable
    // [4]      reg_i2c_sbpm_en     1: enable I2CS bypass to I2CM function
    // [12:8]   reg_i2c_sbpm_idle_num[4:0]  a: default
    bRet &= WriteReg2bytes(0x0900 + (0x08) * 2, 0x0a01);

    // ------Transport Stream pad on (except TS ERR pad)
    // [15:0]   reg_en_ts_pad[15:0] 0x00ff:normal TS location 0xff00:reverse TS location
    bRet &= WriteReg2bytes(0x0900 + (0x2d) * 2, 0x00ff);

    // ------Transport Stream pad on (TS ERR pad)
    // [0]      reg_en_ts_err_pad   1: enable
    // [4]      reg_ts_err_pol  1: inverse 0:normal
    bRet &= WriteReg2bytes(0x0900 + (0x2e) * 2, 0x0001);

    // Initialize special registers

    bRet &= WriteReg(0x0C0E, 0x00);
    bRet &= WriteReg(0x0C0F, 0x00);
    bRet &= WriteReg(0x0C10, 0x00);
    bRet &= WriteReg(0x0C11, 0x00);

#if(TIMING_VERIFICATION == 1)
    tmm_2 = GIVE_ME_TIME
#endif
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]MSB123x_HW_init, bRet=0x%x\n", bRet));
    return bRet;

}

// i2c 150Kb/s, average rate 110Kb/s, 32KB, 2436ms.
MAPI_BOOL Load2Sdram(MAPI_U8 *u8_ptr, MAPI_U16 data_length, MAPI_U16 sdram_win_offset_base)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  sdram_win_offset = sdram_win_offset_base;
    MAPI_U16  x_data_offset = 0;
    MAPI_U16  y_cir_addr = 0;


    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]Load2Sdram, len=0x%x, win_offset=0x%x\n", data_length, sdram_win_offset_base));

#if(TIMING_VERIFICATION == 1)
    tmm_3 = GIVE_ME_TIME
#endif


    if(I2C_CH_Reset(0) == MAPI_FALSE)
    {
        ERR_DEMOD_MSB(printf(">>>MSB123x CH0 Reset:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {

        // set xData map upper and low bound for 64k DRAM window
        bRet &= WriteReg2bytes(0x2B00 + (0x63) * 2, 0x3F24);

        // set xData map offset for 64k DRAM window, 64kbytes alignment
        bRet &= WriteReg2bytes(0x2B00 + (0x64) * 2, 0x0000);

        // set xData map upper and low bound for 4k DRAM window
        bRet &= WriteReg2bytes(0x2B00 + (0x65) * 2, 0x2014);

        // set xData map offset for 4k DRAM window, 4kbytes alignment
        bRet &= WriteReg2bytes(0x2B00 + (0x66) * 2, sdram_win_offset++);

        // enable xData map for DRAM
        bRet &= WriteReg2bytes(0x2B00 + (0x62) * 2, 0x0007);

        for(x_data_offset = 0, y_cir_addr = SDRAM_BASE; x_data_offset < data_length;)
        {
            if(y_cir_addr == 0x6000)
            {
                //set xData map offset for 4k DRAM window, 4kbytes alignment
                // 0x1000, 4096 bytes
                bRet &= WriteReg2bytes(0x2B00 + (0x66) * 2, sdram_win_offset++);
                y_cir_addr = SDRAM_BASE;
            }

            // max 0x200, error above.....

            if((data_length - x_data_offset) >= LOAD_CODE_I2C_BLOCK_NUM)
            {
                bRet &= WriteRegs(y_cir_addr, (u8_ptr + x_data_offset), LOAD_CODE_I2C_BLOCK_NUM);
                y_cir_addr += LOAD_CODE_I2C_BLOCK_NUM;
                x_data_offset += LOAD_CODE_I2C_BLOCK_NUM;
            }
            else
            {
                bRet &= WriteRegs(y_cir_addr, (u8_ptr + x_data_offset), data_length - x_data_offset);
                y_cir_addr += (data_length - x_data_offset);
                x_data_offset += (data_length - x_data_offset);
            }
        }
        DBG_DEMOD_LOAD_I2C(printf("[msb123x]x_data_offset=%d,y_cir_addr=%d,z_block_num=%d\n", x_data_offset, y_cir_addr, sdram_win_offset));
#if (SDRAM_DATA_CHECK == 1)
        // beg data check.
        DBG_DEMOD_LOAD_I2C(printf("[msb123x]SDRAM data check...\n"));

        sdram_win_offset = sdram_win_offset_base;

        // set xData map offset for 4k DRAM window, 4kbytes alignment
        bRet &= WriteReg2bytes(0x2B00 + (0x66) * 2, sdram_win_offset++);

        for(x_data_offset = 0, y_cir_addr = SDRAM_BASE; x_data_offset < data_length;)
        {
            MAPI_U8 u8_tmp;
            if(y_cir_addr == 0x6000)
            {
                //set xData map offset for 4k DRAM window, 4kbytes alignment
                // 0x1000, 4096 bytes
                bRet &= WriteReg2bytes(0x2B00 + (0x66) * 2, sdram_win_offset++);
                y_cir_addr = SDRAM_BASE;
            }

            bRet &= ReadReg(y_cir_addr++, &u8_tmp);
            if(u8_tmp != *(u8_ptr + x_data_offset++))
            {
                ERR_DEMOD_MSB(printf("[msb123x]error, idx=0x%x, y=0x%x, x=0x%x\n", y_cir_addr - 1, u8_tmp, *(u8_ptr + x_data_offset - 1)));
            }
        }

        DBG_DEMOD_LOAD_I2C(printf("[msb123x]SDRAM data check...Done\n"));

        // end data check
#endif
        //  Release xData map for SDRAM
        bRet &= WriteReg2bytes(0x2B00 + (0x62) * 2, 0x0000);

        // Channel changed from CH 0x00 to CH 0x03
        if(I2C_CH_Reset(3) == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf(">>>MSB123x CH3 Reset:Fail\n"));
            return MAPI_FALSE;
        }
    }

#if(TIMING_VERIFICATION == 1)
    tmm_4 = GIVE_ME_TIME
            show_timer();
#endif

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]Load2Sdram, len=0x%x, win_offset=0x%x\n", data_length, sdram_win_offset_base));
    return bRet;
}

// 92~95ms roughly
MAPI_BOOL LoadSdram2Sram(MAPI_U8 CodeNum)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8   u8_tmp = 0;
    MAPI_U8   u8DoneFlag = 0;
    MAPI_U32  u32Timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadSdram2Sram, g_sram_code=0x%x, codeNum=0x%x\n", g_sram_code, CodeNum));

#if(TIMING_VERIFICATION == 1)
    tmm_17 = GIVE_ME_TIME
#endif

    if(CodeNum == g_sram_code)
    {
        DBG_DEMOD_LOAD_I2C(printf("[msb123x]LoadSdram2Sram, code is available.\n"));
        return bRet;
    }

    bRet &= MSB123x_MEM_switch(0);

    if(CodeNum == MSB123x_DVBT2)
        u8_tmp = 1 | 0x10;
    else if(CodeNum == MSB123x_DVBT)
        u8_tmp = 2 | 0x10;
    else if(CodeNum == MSB123x_DVBC)
        u8_tmp = 3 | 0x10;
    else
        u8_tmp = 0 | 0x10;

    // Assign f/w code type to load => 0x11: dvbt2, 0x12: dvbt, 0x13: dvbc
    bRet &= WriteReg(0x0900 + (0x4f) * 2, u8_tmp);

    // enable miu mask, miu, mcu, gdma
    bRet &= WriteReg(0x1200 + (0x23) * 2 + 1, 0x0f);
    bRet &= WriteReg(0x1200 + (0x23) * 2, 0xf0);

    usleep(10);

    // enable mcu
    bRet &= WriteReg(0x0b00 + (0x19) * 2, 0x00);

    do
    {
        bRet &= ReadReg(0x0900 + (0x4f) * 2, &u8DoneFlag);

        if(u32Timeout++ > 500)
        {
            printf("@msb123x, LoadSdram2Sram boot move code fail.!!!\n");
            return MAPI_FALSE;
        }
        usleep(1 * 1000);

    }
    while(u8DoneFlag != 0xaa);

    // mask miu access of mcu
    bRet &= WriteReg(0x1200 + (0x23) * 2, 0xf2);

    // 10us delay
    usleep(10);

    // Disable MCU
    bRet &= WriteReg(0x0b00 + (0x19) * 2, 0x03);

    // enable miu mask, miu, mcu, gdma
    bRet &= WriteReg(0x1200 + (0x23) * 2 + 1, 0x0f);
    bRet &= WriteReg(0x1200 + (0x23) * 2, 0xf0);

    bRet &= MSB123x_MEM_switch(1);

    if(bRet == false)
    {
        g_sram_code = 0x00;
    }
    else
    {
        g_sram_code = CodeNum;
    }

#if(TIMING_VERIFICATION == 1)
    tmm_18 = GIVE_ME_TIME
#endif

             DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadSdram2Sram, codeNum=0x%x, g_sram_code=0x%x, bRet=0x%x\n", CodeNum, g_sram_code, bRet));

    return bRet;
}


MAPI_BOOL LoadDspCodeToSDRAM_Boot(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_Boot\n"));

    if(!(g_sdram_code & MSB123x_BOOT))
    {
        if(sizeof(MSB123X_LIB) > WIMBLEDON_BOOT_START_ADDR)
        {
            // boot code
            data_ptr = MSB123X_LIB + WIMBLEDON_BOOT_START_ADDR;
            code_size = WIMBLEDON_BOOT_END_ADDR - WIMBLEDON_BOOT_START_ADDR + 1;
            win_offset = WIMBLEDON_BOOT_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr, code_size, win_offset);
            if(bRet == true)
            {
                g_sdram_code |= MSB123x_BOOT;
            }
        }
        else
        {
            printf("@msb123x, boot code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_Boot\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbt2(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_dvbt2\n"));

    if(!(g_sdram_code & MSB123x_DVBT2))
    {
        if(sizeof(MSB123X_LIB) > WIMBLEDON_DVBT2_P1_START_ADDR)
        {
            // dvbt2_p2
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBT2_P2_START_ADDR;
            code_size = WIMBLEDON_DVBT2_P2_END_ADDR - WIMBLEDON_DVBT2_P2_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBT2_P2_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr, code_size, win_offset);

            // dvbt2_p1
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBT2_P1_START_ADDR;
            code_size = WIMBLEDON_DVBT2_P1_END_ADDR - WIMBLEDON_DVBT2_P1_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBT2_P1_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr, code_size, win_offset);

            if(bRet == true)
            {
                g_sdram_code |= MSB123x_DVBT2;
            }
        }
        else
        {
            ERR_DEMOD_MSB(printf("@msb123x, dvbt2 code is unavailable!!!\n"));
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_dvbt2\n"));

    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbt(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_dvbt\n"));

    if(!(g_sdram_code & MSB123x_DVBT))
    {
        // dvbt code
        if(sizeof(MSB123X_LIB) > WIMBLEDON_DVBT_START_ADDR)
        {
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBT_START_ADDR;
            code_size = WIMBLEDON_DVBT_END_ADDR - WIMBLEDON_DVBT_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBT_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr, code_size, win_offset);
            if(bRet == true)
            {
                g_sdram_code |= MSB123x_DVBT;
            }
        }
        else
        {
            printf("@msb123x, dvbt code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_dvbt\n"));
    return bRet;
}

MAPI_BOOL LoadDspCodeToSDRAM_dvbc(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL bRet = true;
    MAPI_U16  code_size, win_offset;
    MAPI_U8   *data_ptr;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM_dvbc\n"));
    if(!(g_sdram_code & MSB123x_DVBC))
    {
        // dvbc code
        if(sizeof(MSB123X_LIB) > WIMBLEDON_DVBC_START_ADDR)
        {
            data_ptr = MSB123X_LIB + WIMBLEDON_DVBC_START_ADDR;
            code_size = WIMBLEDON_DVBC_END_ADDR - WIMBLEDON_DVBC_START_ADDR + 1;
            win_offset = WIMBLEDON_DVBC_WINDOWS_OFFSET;
            bRet &= Load2Sdram(data_ptr, code_size, win_offset);
            if(bRet == true)
            {
                g_sdram_code |= MSB123x_DVBC;
            }
        }
        else
        {
            printf("@msb123x, dvbc code is unavailable!!!\n");
        }
    }
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM_dvbc\n"));
    return bRet;
}

// [0] bootloader [1] dvbt2, [2] dvbt, [3] dvbc [4] all
MAPI_BOOL LoadDspCodeToSDRAM(MAPI_U8 code_n)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL bRet = true;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCodeToSDRAM, code_n=0x%x\n", code_n));

#if(TIMING_VERIFICATION == 1)
    tmm_7 = GIVE_ME_TIME
#endif

            switch(code_n)
    {
        case MSB123x_BOOT:
        {
            // boot code
            bRet &= LoadDspCodeToSDRAM_Boot();
        }
        break;
        case MSB123x_DVBT2:
        {
            // dvbt2 code
            bRet &= LoadDspCodeToSDRAM_dvbt2();
        }
        break;
        case MSB123x_DVBT:
        {
            // dvbt
            bRet &= LoadDspCodeToSDRAM_dvbt();
        }
        break;
        case MSB123x_DVBC:
        {
            // dvbtc
            bRet &= LoadDspCodeToSDRAM_dvbc();
        }
        break;
        case MSB123x_ALL:
        default:
        {
            // boot+dvbt2+dvbt+dvbc

            // boot code
            bRet &= LoadDspCodeToSDRAM_Boot();
            // dvbt2
            bRet &= LoadDspCodeToSDRAM_dvbt2();
            // dvbt
            bRet &= LoadDspCodeToSDRAM_dvbt();
            // dvbtc
            bRet &= LoadDspCodeToSDRAM_dvbc();
        }
        break;
    }

#if(TIMING_VERIFICATION == 1)
    tmm_8 = GIVE_ME_TIME
            show_timer();
#endif

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCodeToSDRAM, code_n=0x%x, bRet=0x%x\n", code_n, bRet));
    return bRet;
}

// mem_type 0: dram, 1:dram+sram
// 28 ms roughly
MAPI_BOOL MSB123x_MEM_switch(MAPI_U8 mem_type)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

    MAPI_BOOL bRet = true;
    MAPI_U8 u8_tmp = 0;
    MAPI_U16 timeout = 0;

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]MSB123x_MEM_switch, mem_type=0x%x\n", mem_type));

#if(TIMING_VERIFICATION == 1)
    tmm_15 = GIVE_ME_TIME
#endif

             if(mem_type == 1)
    {

        bRet &= WriteReg(0x2B80, 0x10);

        // SRAM_START_ADDR 0x0000
        bRet &= WriteReg2bytes(0x1000, 0x0000);
        bRet &= WriteReg2bytes(0x1004, 0x0000);

        // SRAM_END_ADDR 0x7FFF
        bRet &= WriteReg2bytes(0x1002, 0x0000);
        bRet &= WriteReg2bytes(0x1006, 0x7FFF);

        // DRAM_START_ADDR 0x8000
        bRet &= WriteReg2bytes(0x1008, 0x0000);
        bRet &= WriteReg2bytes(0x100C, 0x8000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= WriteReg2bytes(0x100A, 0x0000);
        bRet &= WriteReg2bytes(0x100E, 0xFFFF);

        // Enable SRAM&SDRAM memory map
        bRet &= WriteReg(0x1018, 0x05);

        // Wait memory map to be enabled
        do
        {
            bRet &= ReadReg(0x1018, &u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb123x, D+S memory mapping failure.!!!\n");
                return MAPI_FALSE;
            }
        }
        while(u8_tmp != 0x05);
    }
    else if(mem_type == 0)
    {
        // Enable SRAM&SDRAM memory map

        bRet &= WriteReg(0x2B80, 0x10);

        // DRAM_START_ADDR 0x8000
        bRet &= WriteReg2bytes(0x1008, 0x0000);
        bRet &= WriteReg2bytes(0x100C, 0x0000);


        // DRAM_END_ADDR    0xFFFF
        bRet &= WriteReg2bytes(0x100A, 0x0000);
        bRet &= WriteReg2bytes(0x100E, 0x7FFF);

        // Enable SRAM&SDRAM memory map
        bRet &= WriteReg(0x1018, 0x04);

        // Wait memory map to be enabled
        do
        {
            bRet &= ReadReg(0x1018, &u8_tmp);
            if(timeout++ > 500)
            {
                printf("@msb123x, D memory mapping failure.!!!\n");
                return MAPI_FALSE;
            }
        }
        while(u8_tmp != 0x04);
    }
    else
    {
        printf("@msb123x, invalid mem type mapping.\n");
        return MAPI_FALSE;
    }
#if(TIMING_VERIFICATION == 1)
    tmm_16 = GIVE_ME_TIME
#endif

             DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]MSB123x_MEM_switch, , mem_type=0x%x, bRet=0x%x\n", mem_type, bRet));

    return bRet;
}
static MAPI_BOOL IspProcFlash(MAPI_U8* pLibArry, MAPI_U32 dwLibSize)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U32    dwLoop, dwTimeOut;
    MAPI_U32    dwStartAddr, dwEndAddr;
    //MAPI_U16    wLoop;
    MAPI_U8     bError = false;//, bWriteData[PAGE_WRITE_SIZE];

    MAPI_U8 bWriteData[5] = {0x4D, 0x53, 0x54, 0x41, 0x52};
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_SPI_IIC);
    iptr->WriteBytes(0, NULL, 5, bWriteData);

    dwStartAddr = (MAPI_U32) 0;
    dwEndAddr = dwLibSize;


    MAPI_U8     bAddr[1];
    MAPI_U8     bReadData = 0;
    for(dwLoop = dwStartAddr; (dwLoop < dwEndAddr); dwLoop += PAGE_WRITE_SIZE)
    {

        dwTimeOut = 10000;

        while(dwTimeOut--)
        {
            bAddr[0] = 0x10;
            bWriteData[0] = 0x05;
            iptr->WriteBytes(1, bAddr, 1, bWriteData);

            bAddr[0] = 0x11;
            iptr->ReadBytes(1, bAddr, 1, &bReadData);

            bWriteData[0] = 0x12;
            iptr->WriteBytes(0, NULL, 1, bWriteData);

            if(!(bReadData & 0x01))
                break;

            if(dwTimeOut == 1)
            {
                bError = 1;
                break;
            }
            usleep(0);
        }

        if(!bError)
        {

            MAPI_U8    bAddr_w[5], bWriteData_1[1];
            MAPI_BOOL bError_1 = MAPI_TRUE;

            mapi_i2c *iptr_1 = mapi_i2c_GetI2C_Dev(MSB123X_SPI_IIC);

            bAddr[0] = 0x10;
            bWriteData_1[0] = 0x06;
            bError_1 &= iptr_1->WriteBytes(1, bAddr_w, 1, bWriteData_1);

            bWriteData_1[0] = 0x12;
            bError_1 &= iptr_1->WriteBytes(0, NULL, 1, bWriteData_1);

            // Page Program
            bAddr_w[0] = 0x10;
            bAddr_w[1] = 0x02;
            bAddr_w[2] = dwLoop >> 16;
            bAddr_w[3] = dwLoop >> 8;
            bAddr_w[4] = dwLoop;

            bError_1 &= iptr_1->WriteBytes(5, bAddr_w, PAGE_WRITE_SIZE, (pLibArry + dwLoop));

            bWriteData_1[0] = 0x12;
            bError_1 &=  iptr_1->WriteBytes(0, NULL, 1, bWriteData_1);

            bAddr_w[0] = 0x10;
            bWriteData_1[0] = 0x04;
            bError_1 &=  iptr_1->WriteBytes(1, bAddr_w, 1, bWriteData_1);

            bWriteData_1[0] = 0x12;
            bError_1 &=  iptr_1->WriteBytes(0, NULL, 1, bWriteData_1);

            if(bError_1 == MAPI_FALSE)
            {
                break;
            }
        }
    }

    bWriteData[0] = 0x24 ;
    iptr->WriteBytes(0, NULL, 1, bWriteData);

    if(bError == false)
        return MAPI_TRUE;
    else
        return MAPI_FALSE;

}
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
void* PreLoadDSPcode(void *arg)
{
    arg = NULL;
}
#endif
MAPI_BOOL Connect(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    DBG_DEMOD_MSB(printf("device_demodulator_msb123x: Connect type=%d\n", (int)enDemodType));
    UNUSED(enDemodType);
    if(u8DeviceBusy == 1)
        return MAPI_FALSE;
    m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_DVB_T2;
    u8DeviceBusy = 1;
    return MAPI_TRUE;
}

MAPI_BOOL Disconnect(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    DBG_DEMOD_MSB(printf("device_demodulator_msb123x: Disconnect\n"));
    u8DeviceBusy = 0;
    return MAPI_TRUE;
}

#include "drvXC_IOPort.h"
#include "apiXC.h"

void Reset(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8     u8Data = 0x00;
    MAPI_U32    u32Retry = 0x00;

    DBG_DEMOD_MSB(printf(">>>MSB123x: Reset()\n"));
    u32StartTime = MsOS_GetSystemTime();
    DBG_DEMOD_MSB(printf("\t\t\tRESET TIME   %ld\n", u32StartTime));//to measure time
    bDoReset = MAPI_TRUE;

    printf("Set TSP0 registers...\n");

    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        // mask miu access for all and mcu
        WriteReg(0x1200+(0x23)*2 + 1,0x7f);
        WriteReg(0x1200+(0x23)*2,0xfe);
        // 10us delay
        usleep(10);

        WriteReg(0x0B00 + (0x10) * 2, 0x01);
        WriteReg(0x0B00 + (0x19) * 2, 0x03);
        WriteReg(0x0C00, 0x00);             //clear MB_CNTL
        usleep(5 * 100);

        // enable miu access of mcu gdma
        WriteReg(0x1200+(0x23)*2,0xf0);
        // 10us delay
        usleep(10);

        WriteReg(0x0B00 + (0x19) * 2, 0x00);
        WriteReg(0x0B00 + (0x10) * 2, 0x00);
        usleep(5 * 1000);
        ReadReg(0x0C00, &u8Data);           //check MB_CNTL ready
        while(u8Data != 0xff)
        {
            usleep(50 * 1000);
            ReadReg(0x0C00, &u8Data);       //check MB_CNTL ready
            if(u32Retry++ > 200)
            {
                ERR_DEMOD_MSB(printf(">>>MSB123x: Reset Fail!\n"));
                break;
            }
        }
    }
    else if((m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T) ||
            (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C))
    {
        // mask miu access for all and mcu
        WriteReg(0x1200+(0x23)*2 + 1,0x7f);
        WriteReg(0x1200+(0x23)*2,0xfe);
        // 10us delay
        usleep(10);

        WriteReg(0x0B00 + (0x19) * 2, 0x01);
        WriteReg(0x0B00 + (0x10) * 2, 0x01);
        WriteReg(0x0C00, 0x00);             //clear MB_CNTL

        usleep(5 * 1000);

        // enable miu access of mcu gdma
        WriteReg(0x1200+(0x23)*2,0xf0);
        // 10us delay
        usleep(10);

        WriteReg(0x0B00 + (0x10) * 2, 0x00);
        WriteReg(0x0B00 + (0x19) * 2, 0x00);

        ReadReg(0x0C00, &u8Data);       //check MB_CNTL ready
        while(u8Data != 0xff)
        {
            usleep(50 * 1000);
            ReadReg(0x0C00, &u8Data);       //check MB_CNTL ready
            if(u32Retry++ > 200)
            {
                ERR_DEMOD_MSB(printf(">>>MSB123x: Reset Fail!\n"));
                break;
            }
        }

    }
    //printf(">>>MSB123x: Reset ok!\n");

    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();
    p1_ever_lock_flag = 0;

}

MAPI_BOOL IIC_Bypass_Mode(MAPI_BOOL enable)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8 u8Retry = 10;
    MS_BOOL bResult;

    DBG_DEMOD_MSB(printf(">>>MSB123x: IIC_bypass() set %x\n", enable));

    while(u8Retry--)
    {
        if(enable)
            bResult = WriteReg(0x0900 + (0x08) * 2, 0x10); // IIC by-pass mode on
        else
            bResult = WriteReg(0x0900 + (0x08) * 2, 0x00); // IIC by-pass mode off

        if(bResult)
            break;
    }
    return MAPI_TRUE;
}

MAPI_BOOL Power_On_Initialization(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    return MAPI_TRUE;
#endif
    MAPI_U8     status = MAPI_TRUE;
    MAPI_BOOL   bMatch = false;
    MAPI_U8     u8RetryCnt = 6;

    DBG_DEMOD_MSB(printf(">>>MSB123x: Enter Power_On_Initialization()\n"));
    if(bPower_init_en == MAPI_TRUE)
    {
        return  MAPI_TRUE;
    }
    else
    {
        bPower_init_en = MAPI_TRUE;
    }

    if(g_WO_SPI_FLASH == 1)
    {
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
#else
        status &= I2C_CH_Reset(3);

        status &= MSB123x_HW_init();

        status &= LoadDspCodeToSDRAM(MSB123x_ALL);

        if(LoadDSPCode() == MAPI_FALSE)
        {
            ERR_DEMOD_MSB(printf(">>>>MSB123x:Fail\n"));
            status = MAPI_FALSE;
        }
#endif
    }
    else
    {

        MAPI_U8     u8DoneFlag = 0;
        MAPI_U16    u16_counter = 0;

        MAPI_U16    crc16 = 0;

        crc16 = MSB123X_LIB[sizeof(MSB123X_LIB)-2];
        crc16 = (crc16<<8)|MSB123X_LIB[sizeof(MSB123X_LIB)-1];

        do
        {
            u8RetryCnt--;

            if(status == MAPI_FALSE)
            {
#ifndef T3_Winbledon
                DBG_DEMOD_MSB(printf(">>>MSB123x: Reset Demodulator\n"));
                mapi_gpio *gptr = mapi_gpio_GetGPIO_Dev();
                if(gptr != NULL)
                {
                    gptr->SetOff();
                }

                usleep(resetDemodTime * 1000);

                if(gptr != NULL)
                {
                    gptr->SetOn();
                }

                usleep(waitFlashTime * 1000);
                if (I2C_CH_Reset(3) == MAPI_FALSE)
                {
                  DBG_DEMOD_MSB(printf(">>>MSB123x CH Reset:Fail\n"));
                  status= MAPI_FALSE;
                  continue;
                }

                u16_counter = 1000;
                do
                {
                  // 10 ms
                  usleep(10*1000);
                  u16_counter--;
                  ReadReg(0x0900+(0x4f)*2, &u8DoneFlag);
                } while((u8DoneFlag != 0x99) && (u16_counter != 0));

                if((u16_counter == 0) && (u8DoneFlag != 0x99))
                {
                  DBG_DEMOD_MSB(printf("[wb]Err, MSB123x didn't ready yet\n"));
                  status = false;
                }
                else
                  status = MAPI_TRUE;

#endif
            }
            {
                DBG_DEMOD_MSB(printf(">>>MSB123x: Check Version..."));

                if(IspCheckVer(MSB123X_LIB, &bMatch) == MAPI_FALSE)
                {
                    ERR_DEMOD_MSB(printf(">>> ISP read FAIL!\n"));
                    status = MAPI_FALSE;
                    continue;
                }

                if(bMatch == false)
                {
                  ERR_DEMOD_MSB(printf(">>> IspCheckVer FAIL!\n"));
                }
                else
                {

                  if (I2C_CH_Reset(3) == MAPI_FALSE)
                  {
                    ERR_DEMOD_MSB(printf(">>>MSB123x CH Reset:Fail\n"));
                    status= MAPI_FALSE;
                    continue;
                  }
                  else
                  {
                    ERR_DEMOD_MSB(printf(">>>MSB123x CH Reset:OK\n"));
                  }

                  if (dram_crc_check(crc16, &bMatch) == MAPI_FALSE)
                  {
                      ERR_DEMOD_MSB(printf(">>> reg read fail!\n"));
                      status= MAPI_FALSE;
                      continue;
                  }

                  if(bMatch == false)
                  {
                    DBG_DEMOD_CHECKSUM(printf(">>> dram crc check FAIL!\n"));
                  }
                  else
                  {
                    DBG_DEMOD_CHECKSUM(printf(">>> dram crc check OK!\n"));
                  }
                }

#if (FLASH_WP_ENABLE == 1)
                if (bMatch == false)
                {
                  // disable flash WP, pull high.
                  if(msb123x_flash_WP(0) == false)
                  {
                    DBG_FLASH_WP(printf("[wb]Err, FLASH WP Disable Fail!!!\n"));
                  }
                  usleep(100*1000);
                }
#endif
                ////bMatch = true; //FIXME : Remove this to enable auto FW reload.
                if(bMatch == false) // Version or crc not match
                {
                    MAPI_U8     bAddr[1];
                    MAPI_U8 bWriteData[5] = {0x4D, 0x53, 0x54, 0x41, 0x52};

                    printf("*****T2 DEMOD SPI FLASH DOWNLOAD START****\n");
                    if((sizeof(MSB123X_LIB) % 256) != 0)
                    {
                        printf(" MSB123X_LIB 256byte alignment error!%u \n", sizeof(MSB123X_LIB));
                    }

                    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_SPI_IIC);
                    iptr->WriteBytes(0, NULL, 5, bWriteData);

                    bAddr[0] = 0x10;
                    bWriteData[0] = 0x06;
                    iptr->WriteBytes(1, bAddr, 1, bWriteData);

                    bWriteData[0] = 0x12;
                    iptr->WriteBytes(0, NULL, 1, bWriteData);

                    bAddr[0] = 0x10;

                    bWriteData[0] = 0xC7;
                    iptr->WriteBytes(1, bAddr, 1, bWriteData);

                    bWriteData[0] = 0x12;
                    iptr->WriteBytes(0, NULL, 1, bWriteData);

                    bWriteData[0] = 0x24 ;
                    iptr->WriteBytes(0, NULL, 1, bWriteData);
                    DBG_DEMOD_MSB(printf("\t\t\tStart   %ld\n", MsOS_GetSystemTime()));//to measure time

                    if ( (sizeof(MSB123X_LIB) - 2) > MAX_MSB123X_LIB_LEN)
                    {
                      DBG_DEMOD_CHECKSUM(printf("Err, msb123x_lib size(%d) is larger than flash size(%d)\n",sizeof(MSB123X_LIB),MAX_MSB123X_LIB_LEN));
                    }

                    // if (IspProcFlash(MSB123X_LIB, sizeof(MSB123X_LIB)) == MAPI_FALSE)
                    if (IspProcFlash(MSB123X_LIB, sizeof(MSB123X_LIB)-2) == MAPI_FALSE)
                    {
                        ERR_DEMOD_MSB(printf(" ISP write FAIL\n"));
                        status = MAPI_FALSE;
                        continue;
                    }
                    else
                    {
                        printf("*****T2 DEMOD SPI FLASH DOWNLOAD END****\n");
                        DBG_DEMOD_MSB(printf("\t\t\tEnd   %ld\n", MsOS_GetSystemTime()));//to measure time
                        //check again
                        if((IspCheckVer(MSB123X_LIB, &bMatch) == MAPI_FALSE) || (bMatch == false))
                        {
                            ERR_DEMOD_MSB(printf(">>> ISP read FAIL! bMatch %d \n", bMatch));
                            status = MAPI_FALSE;
                            continue;
                        }
                        else // reset again
                        {
#ifndef T3_Winbledon
                            DBG_DEMOD_MSB(printf(">>>MSB123x: Reset Demodulator\n"));
                            mapi_gpio *gptr = mapi_gpio_GetGPIO_Dev();

                            if(gptr != NULL)
                            {
                                gptr->SetOff();
                            }

                            usleep(resetDemodTime * 1000);

                            if(gptr != NULL)
                            {
                                gptr->SetOn();
                            }

                            usleep(waitFlashTime * 1000);

                            if (I2C_CH_Reset(3) == MAPI_FALSE)
                            {
                              ERR_DEMOD_MSB(printf(">>>MSB123x CH Reset:Fail\n"));
                              status= MAPI_FALSE;
                              continue;
                            }

                            u16_counter = 1000;
                            do
                            {
                              // 10 ms
                              usleep(10*1000);
                              u16_counter--;
                              ReadReg(0x0900+(0x4f)*2, &u8DoneFlag);
                            } while((u8DoneFlag != 0x99) && (u16_counter != 0));

                            if((u16_counter == 0) && (u8DoneFlag != 0x99))
                            {
                              ERR_DEMOD_MSB(printf("[wb]Err, MSB123x didn't ready yet\n"));
                              status = false;
                            }
                            else
                              status = MAPI_TRUE;
#endif

                            if (I2C_CH_Reset(3) == MAPI_FALSE)
                            {
                              ERR_DEMOD_MSB(printf(">>>MSB123x CH Reset:Fail\n"));
                              status= MAPI_FALSE;
                              continue;
                            }
                            else
                            {
                              ERR_DEMOD_MSB(printf(">>>MSB123x CH Reset:OK\n"));
                            }

                            if (dram_crc_check(crc16, &bMatch) == MAPI_FALSE)
                            {
                              ERR_DEMOD_MSB(printf(">>> reg read fail!\n"));
                              status= MAPI_FALSE;
                              continue;
                            }

                            if(bMatch == false)
                            {
                              DBG_DEMOD_CHECKSUM(printf(">>> dram crc check FAIL!\n"));
                            }
                            else
                            {
                              DBG_DEMOD_CHECKSUM(printf(">>> dram crc check OK!\n"));
                            }
                        }
                        DBG_DEMOD_MSB(printf(" OK\n"));
                    }
                }
                else
                {
                    // Version match, do nothing
                    DBG_DEMOD_MSB(printf(">>> Match\n"));
                }

#if (FLASH_WP_ENABLE == 1)
                if (bMatch == true)
                {
                  // Enable flash WP, pull high.
                  if(msb123x_flash_WP(1) == false)
                  {
                    DBG_FLASH_WP(printf("[wb]Err, FLASH WP Enable Fail!!!\n"));
                  }
                  usleep(100*1000);
                }
#endif
            }
            if(I2C_CH_Reset(3) == MAPI_FALSE)
            {
                ERR_DEMOD_MSB(printf(">>>MSB123x CH Reset:Fail\n"));
                status = MAPI_FALSE;
                continue;
            }
            else
            {
                DBG_DEMOD_MSB(printf(">>>MSB123x CH Reset:OK\n"));
            }


            if(LoadDSPCode() == MAPI_FALSE)
            {
                ERR_DEMOD_MSB(printf(">>>>MSB123x:Fail\n"));
                status = MAPI_FALSE;
                continue;
            }
            else
            {
                DBG_DEMOD_MSB(printf(">>>MSB123x:OK\n"));
            }

            ReadReg(0x0900 + (0x01) * 2, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB123x:Wimbledon RevID:%x\n", gu8ChipRevId));

            ReadReg(0x0900 + (0x49) * 2, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB123x:Wimbledon 0x49_L:%x\n", gu8ChipRevId));

            ReadReg(0x0900 + (0x49) * 2 + 1, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB123x:Wimbledon 0x49_H:%x\n", gu8ChipRevId));

            ReadReg(0x0900 + (0x4A) * 2, &gu8ChipRevId);
            DBG_DEMOD_MSB(printf(">>>MSB123x:Wimbledon 0x4A_L:%x\n", gu8ChipRevId));

        }
        while((u8RetryCnt > 0) && (status == MAPI_FALSE));
    }

    if(status == MAPI_FALSE)
    {
        ERR_DEMOD_MSB(printf("msb123x power_on_init FAIL !!!!!! \n\n"));
        stMapiDemodulatorFun.bMSB123X_Ready = FALSE;
    }
    else
    {
        printf("msb123x power_on_init OK !!!!!! \n\n");
        stMapiDemodulatorFun.bMSB123X_Ready = TRUE;
    }
    return status;
}

MAPI_BOOL Set_PowerOn(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    return MAPI_TRUE;
}
MAPI_BOOL Set_PowerOff(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    return MAPI_TRUE;
}
//--------------------------------------------------------------------- for DVB-T
//operation
#define RFAGC_EN                0x00
#define HUMDET_EN               0x00
#define DCR_EN                  0x01
#define IIS_EN                  0x01
#define CCI_EN                  0x01
#define ACI_EN                  0x01
#define IQB_EN                  0x00
#define AUTO_IQ_SWAP            0x01
#define AUTO_RFMAX              0x00
#define AUTO_ACI                0x00
#define MODE_CP_FORCED          0x00
#define TPS_FORCED              0x00
#define AUTO_SCAN               0x00
#define RSV_0D                  0x00
#define RSV_0E                  0x00
#define RSV_0F                  0x00

//configure
#define RSSI                    0x00
#define ZIF                     0x00
#define FREQ                    0x00
#define FC_L                        0xE0
#define FC_H                    0x2E
#define FS_L                    0x80
#define FS_H                    0xBB
#define BW                      0x03
#define MODE                    0x01
#define CP                      0x03
#define LP_SEL                  0x00
#define CSTL                    0x00
#define HIER                    0x00
#define HPCR                    0x00
#define LPCR                    0x00
#define IQ_SWAP                 0x00
#define RFMAX                   0x01
#define ATV_SYSTEM              0x01
#define ICFO_RANGE              0x01
#define RFAGC_REF               0x64
#define IFAGC_REF_2K            0x4B
#define IFAGC_REF_8K            0x4B
#define IFAGC_REF_ACI           0x4B
#define IFAGC_REF_IIS_2K        0xA0
#define IFAGC_REF_IIS_8K        0xA0
#define IFAGC_ACI_DET_TH_L      0x9A
#define IFAGC_ACI_DET_TH_H      0x01
#define SERIAL_TS               0x00
#define TS_CLK_SEL              0x06
#define TS_OUT_INV              0x01
#define TS_DATA_SWAP            0x00
#define SFO_2K_H                0x00
#define SFO_2K_L                0xC8
#define SFO_8K_H                0x00
#define SFO_8K_L                0xC8
#define CHECK_CHANNEL           0x00
#define SNR_POS                 0x00
#define CCI_KP                  0x00
#define CCI_FSWEEP              0x00
#define TS_CLK_RATE_AUTO        0x00
#define DVBT_IF_INV_PWM_OUT_EN  0x00
#define DVBT_CRC                0x00


MAPI_U8 MSB1231_DVBT_DSPREG_TABLE[] = // andy 2009-12-15  3:55:03 TW model
{
    RFAGC_EN,     HUMDET_EN,    DCR_EN,     IIS_EN,         CCI_EN,      ACI_EN,
    IQB_EN,       AUTO_IQ_SWAP, AUTO_RFMAX, AUTO_ACI,       MODE_CP_FORCED, TPS_FORCED,
    AUTO_SCAN,    RSV_0D,       RSV_0E,     RSV_0F,
    RSSI,         ZIF,          FREQ,       FC_L,           FC_H,        FS_L,      FS_H,
    BW,           MODE,         CP,         LP_SEL,         CSTL,        HIER,      HPCR,
    LPCR,         IQ_SWAP,      RFMAX,      ATV_SYSTEM,     ICFO_RANGE,  RFAGC_REF,
    IFAGC_REF_2K, IFAGC_REF_8K, IFAGC_REF_ACI,  IFAGC_REF_IIS_2K,  IFAGC_REF_IIS_8K, IFAGC_ACI_DET_TH_L,
    IFAGC_ACI_DET_TH_H,         SERIAL_TS,  TS_CLK_SEL,  TS_OUT_INV,  TS_DATA_SWAP,
    SFO_2K_H,     SFO_2K_L,     SFO_8K_H,   SFO_8K_L,       CHECK_CHANNEL,          SNR_POS,
    CCI_KP,       CCI_FSWEEP    , TS_CLK_RATE_AUTO, DVBT_IF_INV_PWM_OUT_EN, DVBT_CRC
};

#define T2_TS_SERIAL_VAL        0x00
#define T2_TS_CLK_RATE_VAL      0x06
#define T2_TS_OUT_INV_VAL       0x01
#define T2_TS_DATA_SWAP_VAL     0x00
#define T2_TS_ERR_POL_VAL       0x00
#define T2_IF_AGC_INV_PWM_EN_VAL    0x00
#define T2_TH_A_NP1_VAL         60

MAPI_BOOL DTV_DVBT2_DSPReg_Init(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8    idx = 0;
    MAPI_U8    T2_FC_L_VAL;
    MAPI_U8    T2_FC_H_VAL;
    MAPI_U8    T2_BW_VAL;
    SawArchitecture eSAWType;
    T2_BW_VAL  =  0x04;
    eSAWType = SILICON_TUNER;  //todo
    // FC: FC = FS - IF = 48000 - 4800 = 0xA9A6     (4.50MHz IF)
    // FC: FC = FS - IF = 48000 - 36000 = 0x2EE0    (36.0MHz IF)
    if( eSAWType == SILICON_TUNER)//for slicon tuner IF 4570
    {
        T2_FC_L_VAL      =   0xC0;
        T2_FC_H_VAL      =   0xA8;
    }
    else
    {
        T2_FC_L_VAL      =   0xE0;
        T2_FC_H_VAL      =   0x2E;
    }
    MAPI_U8 MSB1231_DVBT2_DSPREG_TABLE[] =
    {
       T2_BW_VAL,     T2_FC_L_VAL,     T2_FC_H_VAL
   };
    for(idx = 0; idx < sizeof(MSB1231_DVBT2_DSPREG_TABLE); idx++)
    {
        if(WriteDspReg(idx + 0x40, MSB1231_DVBT2_DSPREG_TABLE[idx]) != MAPI_TRUE)
        {
            printf("T2 dsp reg init NG\n");
            return MAPI_FALSE;
        }
    }

    if(WriteDspReg((MAPI_U16)T2_TS_SERIAL, T2_TS_SERIAL_VAL) != MAPI_TRUE)
    {
        printf("T2 dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)T2_TS_CLK_RATE, T2_TS_CLK_RATE_VAL) != MAPI_TRUE)
    {
        printf("T2 dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)T2_TS_OUT_INV, T2_TS_OUT_INV_VAL) != MAPI_TRUE)
    {
        printf("T2 dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)T2_TS_DATA_SWAP, T2_TS_DATA_SWAP_VAL) != MAPI_TRUE)
    {
        printf("T2 dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)T2_TS_ERR_POL, T2_TS_ERR_POL_VAL) != MAPI_TRUE)
    {
        printf("T2 dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)T2_IF_AGC_INV_PWM_EN, T2_IF_AGC_INV_PWM_EN_VAL) != MAPI_TRUE)
    {
        printf("T2 dsp reg init NG\n");
    }

    printf("T2 dsp reg init ok\n");

    return MAPI_TRUE;
}
//--------------------------------------------------------------------- for DVB-C
#define SR0_H_AUTO              0x0F
#define SR0_L_AUTO              0xA0
#define SR0_H                   0x1A
#define SR0_L                   0xDB
#define AUTO_SCAN               0x00
#define AUTO_SCAN_SYM_RATE      0x00 //0x28
#define AUTO_SCAN_QAM           0x00
#define ATV_DET_EN              0x01 //0x2A
#define C_IF_INV_PWM_OUT_EN     0x00
#define RSSI                    0x00 //0x30
#define ZIF                     0x00
#define FREQ                    0x00
#define FC_L                    0xE0
#define FC_H                    0x2E
#define FS_L                    0x80
#define FS_H                    0xBB
#define BW_L                    0xDB
#define BW_H                    0x1A
#define BW1_L                   0xF4
#define BW1_H                   0x1A
#define BW2_L                   0xDB
#define BW2_H                   0x1A
#define BW3_L                   0xDB
#define BW3_H                   0x1A
#define QAM                     0x02
#define IQ_SWAP_C               0x01
#define CCI                     0x00
#define SERIAL_TS               0x00 //0: parallel 1:serial
#define TS_OUT_INV              0x01 //
#define TS_DATA_SWAP            0x00

MAPI_U8 MSB1231_DVBC_DSPREG_TABLE[] =
{
    00,     00,     01,     00,     01,     00,     01,       AUTO_SCAN,
    AUTO_SCAN_SYM_RATE, AUTO_SCAN_QAM,  ATV_DET_EN,     C_IF_INV_PWM_OUT_EN,     00,     00,     00,     00,
    00,     00,     00,     FC_L,           FC_H,           FS_L,           FS_H,
    BW_L,       BW_H,       BW1_L,      BW1_H,      BW2_L,      BW2_H,      BW3_L,      BW3_H,      00,
    00,     QAM,        IQ_SWAP_C,      CCI,        SERIAL_TS,      05,
    TS_OUT_INV,     TS_DATA_SWAP
};

MAPI_BOOL Active(MAPI_BOOL bEnable)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

    UNUSED(bEnable);

    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        return MAPI_TRUE;
    }
    else if((m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
            || (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C))
    {
        printf(" @MSB1231_active\n");

        MAPI_BOOL status = WriteReg(0x0C00 + (0x0E) * 2, 0x0001); // FSM_EN

        if(status)
        {
            printf(" @MSB1231_Active OK\n");
        }
        else
        {
            printf(" @MSB1231_Active NG\n");
        }
        return status;
    }
    return MAPI_FALSE;
}

EN_DEVICE_DEMOD_TYPE GetCurrentDemodulatorType(void)
{
    return m_enCurrentDemodulator_Type;
}

#if (MSB123x_T2MI_DJB_RST_EN == 1)
MAPI_BOOL MSB123x_DJB_RST(void)
{
    MAPI_BOOL bRet = FALSE;

    if(!mdev_Cofdm_MSB123X_Ready() && (DVB_T2_DEMOD != MApp_DTV_Scan_T2_ScanCheckSignal()))
    {
          return bRet;
    }

    if ( MSB1231_Lock(COFDM_FEC_LOCK_T2_123X) == TRUE )
    {
        MS_U16 bch_eflag2_sum = 0;
        MS_U8  reg = 0;
        static MS_U32 t1  = 0;

        ReadReg(0x2600+0x26*2 + 1,&reg);
        bch_eflag2_sum = reg;
        ReadReg(0x2600+0x26*2,&reg);
        bch_eflag2_sum = (bch_eflag2_sum<<8)|reg;

        if (bch_eflag2_sum == 0x00 && ((MsOS_GetSystemTime() - t1) > 1000))
        {
            //djb rst
            ReadReg(0x2900+0x00*2,&reg);
            reg |= 0x01;
            WriteReg(0x2900+0x00*2,reg);
            usleep(1000);
            ReadReg(0x2900+0x00*2,&reg);
            reg &= (0xff-0x01);
            WriteReg(0x2900+0x00*2,reg);
            t1 = MsOS_GetSystemTime();
            DBG_DEMOD_MSB(printf("\n[msb123x]Warning!!!, djb rst......\n");)
            bRet = TRUE;
        }
    }
    return bRet;
}
#endif

MAPI_BOOL ExtendCmd(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3)
{
    MAPI_U8 u8Data = 0;
    MAPI_U8 u8Status = MAPI_TRUE;


    SubCmd = SubCmd;
    u32Param1 = u32Param1;
    u32Param2 = u32Param2;
    pvParam3 = pvParam3;

    if (SubCmd ==3)
    {
        if (u32Param1 == 0x2123)
        {
            /************************************************
            * Force u8RFAGC 150 due to unknown SAR port for each demo board.
            ************************************************/
            *((MAPI_U16*)pvParam3) = 150;
            printf("DVB-T2: SAR VALUE=0x%x \n",*((MAPI_U16*)pvParam3));
            return MAPI_TRUE;
        }
        else
        {
            return ReadReg((MAPI_U16)u32Param1,(MAPI_U8*)pvParam3); // _UTOPIA
        }
    }

    if (SubCmd ==4)
    {
        return WriteReg((MAPI_U32) u32Param1,(MAPI_U8) u32Param2); // _UTOPIA
    }

    if (SubCmd == 0x10) // GetSNR
    {
        *((EN_FRONTEND_SIGNAL_CONDITION *)pvParam3) = DTV_GetSNR();
        return MAPI_TRUE;
    }
    if (SubCmd == 0x11) // GetPreBER
    {
        return DTV_GetPreBER((float *)pvParam3);
    }
    if (SubCmd == 0x12) // GetPostBER
    {
        return DTV_GetPostBER((float *)pvParam3);
    }
    if (SubCmd == 0x13) // GetPktErr
    {
        MAPI_BOOL status = MAPI_TRUE;
        MAPI_U8   reg = 0;
        MAPI_U16  PktErr=0;

        //freeze
        status &= WriteReg(0x2604, 0x01);
        //read packet error
        status &= ReadReg(0x265B, &reg);
        PktErr = reg;
        status &= ReadReg(0x265A, &reg);
        PktErr = (PktErr << 8)|reg;
        status &= WriteReg(0x2604, 0x00);
        *((MAPI_U16*)pvParam3) = PktErr;
        //release
        //printf("[dvbt2]GetPktErr = %d\n",PktErr);
        return status;
    }
    if (SubCmd == 0x40)
    {
        MAPI_U32 u32Data = 0;
        MAPI_U16 u16Addr = 0, u16Data = 0;
        MAPI_U8 u8Data_1 = 0;

        const char* const u8GIInfo[]={"GI_1_32","GI_1_16","GI_1_8","GI_1_4","GI_1_128","GI_19_128","GI_19_256"};
        const char* const u8FFTInfo[]={"2k","8k","4k","1k","16k","32k","8k","32k"};


        if(ReadReg(0x2400+0x40*2+1,&u8Data_1) == MAPI_FALSE) return MAPI_FALSE;
          printf("[dvbt2]gi=0x%x %s\n",u8Data_1, u8GIInfo[((u8Data_1>>4) & 0x07)]);

        printf("[dvbt2]fft=0x%x %s\n",u8Data_1, u8FFTInfo[((u8Data_1) & 0x07)]);

        printf("\nPlp_id_array: ");
        for (u16Addr=0x1F; u16Addr>=0x10; u16Addr--)
        {
            if(ReadReg(0x2700+(u16Addr*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
              u16Data = u8Data << 8;

            if(ReadReg(0x2700+(u16Addr*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
              u16Data |= u8Data_1;
            printf("%04x ", u16Data);
        }


        printf("\nK_sig: ");
        for (u16Addr=0x24; u16Addr>=0x23; u16Addr--)
        {
            if(ReadReg(0x2700+(u16Addr*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
              u16Data = u8Data_1 << 8;
            if (u16Addr == 0x24) u16Data &=0x3FFF;

            if(ReadReg(0x2700+(u16Addr*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
              u16Data |= u8Data_1;
            printf("%04x ", u16Data);
        }


        if(ReadReg(0x2700+(0x31*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x31*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data |= u8Data_1;
        if((u16Data&0x0F00) == 0x0000) printf("\nL1_mod: BPSK");
        else if((u16Data&0x0F00) == 0x0100) printf("\nL1_mod: QPSK");
        else if((u16Data&0x0F00) == 0x0200) printf("\nL1_mod: 16QAM");
        else if((u16Data&0x0F00) == 0x0300) printf("\nL1_mod: 64QAM");
        else printf("\nL1_mod: none");

        if((u16Data&0x3000) == 0x0000) printf("\nL1_cod: 1/2");
        else printf("\nL1_cod: none");

        if((u16Data&0xC000) == 0x0000) printf("\nL1_fec_type: 16k");
        else printf("\nL1_fec_type: none");


        if(ReadReg(0x2700+(0x42*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x42*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data |= u8Data_1;
        printf("\nConf_num_plp: %d", (u16Data&0x00FF));
        printf("\nConf_fef_type: %d", ((u16Data&0xF000)>>12));

        if(ReadReg(0x2700+(0x44*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u32Data = u8Data_1 << 24;
        if(ReadReg(0x2700+(0x44*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u32Data |= u8Data_1 << 16;
        if(ReadReg(0x2700+(0x43*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u32Data |= u8Data_1 << 8;
        if(ReadReg(0x2700+(0x43*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u32Data |= u8Data_1;
        printf("\nConf_fef_len: %lx", (u32Data&0x3FFFFF));
        printf("\nConf_fef_interval: %lx", ((u32Data&0xFF800000)>>24));


        if(ReadReg(0x2700+(0x45*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x45*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data |= u8Data_1;
        printf("\nPlp_id: %d",(u16Data&0x00FF));


        if((u16Data&0x0700) == 0x0000) printf("\nPlp_type: common");
        else if((u16Data&0x0700) == 0x0100) printf("\nPlp_type: type1");
        else if((u16Data&0x0700) == 0x0200) printf("\nPlp_type: type2");
        else printf("\nPlp_type: none");

        if((u16Data&0xF800) == 0x0000) printf("\nPlp_payload: GFPS");
        else if((u16Data&0xF800) == 0x0800) printf("\nPlp_payload: GCS");
        else if((u16Data&0xF800) == 0x1000) printf("\nPlp_payload: GSE");
        else if((u16Data&0xF800) == 0x1800) printf("\nPlp_payload: TS");
        else printf("\nPlp_payload: none");


        if(ReadReg(0x2700+(0x46*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x46*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
          u16Data |= u8Data_1;
        printf("\nPlp_first_frame_ind: %d",(u16Data&0x00FF));
        printf("\nPlp_group_id: %d",((u16Data&0xFF00)>>8));


        if(ReadReg(0x2700+(0x47*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x47*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data |= u8Data_1;

        if((u16Data&0x0007) == 0x0000) printf("\nPlp_cod: 1/2");
        else if((u16Data&0x0007) == 0x0001) printf("\nPlp_cod: 3/5");
        else if((u16Data&0x0007) == 0x0002) printf("\nPlp_cod: 2/3");
        else if((u16Data&0x0007) == 0x0003) printf("\nPlp_cod: 3/4");
        else if((u16Data&0x0007) == 0x0004) printf("\nPlp_cod: 4/5");
        else if((u16Data&0x0007) == 0x0005) printf("\nPlp_cod: 5/6");
        else printf("\nPlp_cod: none");

        if((u16Data&0x0038) == 0x0000) printf("\nPlp_mod: QPSK");
        else if((u16Data&0x0038) == 0x0008) printf("\nlp_mod: 16QAM");
        else if((u16Data&0x0038) == 0x0010) printf("\nPlp_mod: 64QAM");
        else if((u16Data&0x0038) == 0x0018) printf("\nPlp_mod: 256QAM");
        else printf("\nPlp_mod: none");

        printf("\nPlp_rotation: %x",((u16Data&0x0040)>>6));

        if((u16Data&0x0180) == 0x0000) printf("\nPlp_fec_type: 16k");
        else if((u16Data&0x0180) == 0x0080) printf("\nPlp_fec_type: 64k");
        else printf("\nPlp_fec_type: none");


        if(ReadReg(0x2700+(0x48*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x48*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data |= u8Data_1;
        printf("\nTime_IL_type: %x",((u16Data&0x1000)>>12));


        if(ReadReg(0x2700+(0x49*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x49*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data |= u8Data_1;
        printf("\nFrame_interval: %d",(u16Data&0x00FF));
        printf("\nTime_IL_len: %d",((u16Data&0xFF00)>>8));


        if(ReadReg(0x2700+(0x55*2)+1, &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data = u8Data_1 << 8;
        if(ReadReg(0x2700+(0x55*2), &u8Data_1)==MAPI_FALSE) return MAPI_FALSE;
        u16Data |= u8Data_1;
        printf("\nPlp_num_blocks: %d",(u16Data&0x03FF));
    }

    if(SubCmd == 0x80)  // temp solution, to turn on/off IF AGC
    {
        if(u32Param1 == 1)          // turn on
        {
            u8Status &= WriteReg2bytes(0x0900 + (0x2a) * 2, 0x8001);
            ReadReg(0x0900 + (0x2a) * 2 + 1, &u8Data);
            DBG_DEMOD_MSB(printf("MSB123x: Turn on IF AGC: %02x\n", u8Data));
        }
        else if(u32Param1 == 0)     // turn off
        {
            u8Status &= ReadReg(0x0900 + (0x2a) * 2 + 1, &u8Data);
            u8Status &= WriteReg(0x0900 + (0x2a) * 2 + 1, (u8Data & 0x3F));
            u8Status &= ReadReg(0x0900 + (0x2a) * 2 + 1, &u8Data);
            DBG_DEMOD_MSB(printf("MSB123x: Turn off IF AGC: %02x\n", u8Data));
            UNUSED(u8Data);
            UNUSED(u8Status);
        }
    }

    if(SubCmd == 0x81)
    {
        if(u32Param1 == 1)
        {
            WriteReg2bytes(0x0900 + (0x2d) * 2, 0x00ff);
        }
        else
        {
            WriteReg2bytes(0x0900 + (0x2d) * 2, 0x0000);
        }
    }

    if(SubCmd == 0x82)  // to turn on/off null packet insert
    {
        if(u32Param1 == 1)  // null packet on
        {
            //DVBT2
            u8Status &= ReadReg(0x2a00 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x2a00 + (0x20) * 2 , (u8Data |0x80));
            //DVBT/C
            u8Status &= ReadReg(0x1100 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x1100 + (0x20) * 2 , (u8Data |0x80));
        }
        else if(u32Param1 == 0)     // null packet off
        {
            //DVBT2
            u8Status &= ReadReg(0x2a00 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x2a00 + (0x20) * 2 , (u8Data & (~0x80)));
            //DVBT/C
            u8Status &= ReadReg(0x1100 + (0x20) * 2 , &u8Data);
            u8Status &= WriteReg(0x1100 + (0x20) * 2 , (u8Data & (~0x80)));
        }
    }

    if(SubCmd == 0xFF)  // temp solution, only for internal use, can't be called by upper layer
    {
        MAPI_U32    u32Timeout = 0;
        MAPI_U32    u32LockTimeout = 2000;
        MAPI_U8     u8Data_2 = 0;
        MAPI_U16    u16RegAddress = 0;
        MAPI_U8     u8LockState = 0;
        MAPI_U8     u8BitMask = 0;
        MAPI_BOOL   bCheckPass = MAPI_FALSE;
        static MAPI_U32 u32LockTimeStartDVBT = 0;
        static MAPI_U32 u32LockTimeStartDVBC = 0;//mick
        static MAPI_U32 u32LockTimeStartDVBT2 = 0;
        MAPI_U32 u32NowTime = MsOS_GetSystemTime();

        switch(m_enCurrentDemodulator_Type)
        {
            case E_DEVICE_DEMOD_DVB_T2:
            {
                u32Timeout = 8000;

                ReadDspReg(0x00f0, &u8Data_2);

                if((u8Data_2 & BIT7) != 0x00)
                  bCheckPass = MAPI_TRUE;
                else
                {
                  if (p1_ever_lock_flag == 0)
                  {
                    u16RegAddress =  0x00f0; //P1 Lock History
                    u8BitMask = BIT5;
                    ReadDspReg(u16RegAddress, &u8Data_2);
                    if((u8Data_2&u8BitMask) == 0)
                    {
                      u32Timeout=1500;//2000;
                    }
                    else
                    {
                      p1_ever_lock_flag = 1;
                    }
                  }
                  else
                  {;}
                }

                if(bCheckPass)
                {

                    u32LockTimeStartDVBT2 = MsOS_GetSystemTime();

                    FECLock = MAPI_TRUE;
                    if(bDoReset == MAPI_TRUE)
                    {
                        //printf("[msb123x]++++DVBT2 lock, freq=%ld\n", g_u32Frequency);
                        DBG_DEMOD_MSB(printf("\t\t\tDTV_DVB_T_GetLockStatus(LOCK/T2) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBT2 - u32StartTime, u32LockTimeStartDVBT2, u32StartTime)); //to measure time
#if (TIMING_VERIFICATION==1)
                        tmm_14 = GIVE_ME_TIME
                        show_timer();
#endif
                    }
                    bDoReset = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_LOCK;
                }
                else if((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                        || (u32NowTime - u32LockTimeStartDVBT2 < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
                }
            }
            break;
            case E_DEVICE_DEMOD_DVB_T:
            {
                u32Timeout = 1500;
                u16RegAddress = 0x11E0;
                u8LockState = 0x0B;
                ReadReg(u16RegAddress, &u8Data_2);
                if(u8Data_2 == u8LockState)
                    bCheckPass = MAPI_TRUE;
                else if(u8Data_2 == 0xBB)
                {
                    // dsp_table_crc_error
                    ERR_DEMOD_MSB(printf("@msb123x Dsp table init param crc error !!!\n"));
                }
                else
                {
                    u16RegAddress =  0x0990; //TPS his Lock,
                    u8BitMask = BIT3;
                    ReadReg(u16RegAddress, &u8Data_2);
                    if((u8Data_2 & u8BitMask) > 0)
                        u32Timeout = 6000;
                }
                //DBG_DEMOD_MSB(printf(">>>MSB123x: [%s] Lock Status = %d\n", __FUNCTION__, u8Data));
                if(bCheckPass)
                {
                    u32LockTimeStartDVBT = MsOS_GetSystemTime();
                    FECLock = MAPI_TRUE;
                    if(bDoReset == MAPI_TRUE)
                    {
                        //printf("[msb123x]++++DVBT lock, freq=%ld\n", g_u32Frequency);
                        DBG_DEMOD_MSB(printf("\t\t\tDTV_DVB_T_GetLockStatus(LOCK/T) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBT - u32StartTime, u32LockTimeStartDVBT, u32StartTime)); //to measure time
#if (TIMING_VERIFICATION==1)
                        tmm_14 = GIVE_ME_TIME
                                 show_timer();
#endif
                    }
                    bDoReset = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_LOCK;
                }
                else if((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                        || (u32NowTime - u32LockTimeStartDVBT < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
                }
            }
            break;
            case E_DEVICE_DEMOD_DVB_C://mick
            {
                u32Timeout = 1500;
                u16RegAddress = 0x11E0;
                u8LockState = 0x0C;
                ReadReg(u16RegAddress, &u8Data_2);
                //printf("[msb123x]+++++++++DVBC State---->%d\n",u8Data);//mick
                if(u8Data_2 == u8LockState)
                    bCheckPass = MAPI_TRUE;
                else
                {
                    u16RegAddress =  0x0990; //TPS his Lock,
                    u8BitMask = BIT3;
                    ReadReg(u16RegAddress, &u8Data_2);
                    if((u8Data_2 & u8BitMask) > 0)
                        u32Timeout = 6000;
                }
                if(bCheckPass)
                {
                    u32LockTimeStartDVBC = MsOS_GetSystemTime();
                    FECLock = MAPI_TRUE;
                    if(bDoReset == MAPI_TRUE)
                    {
                        //printf("[msb123x]++++DVBC lock, freq=%ld\n", g_u32Frequency);
                        DBG_DEMOD_MSB(printf("\t\t\tDTV_DVB_C_GetLockStatus(LOCK/C) TIME   %ld(=%ld-%ld)\n", u32LockTimeStartDVBC - u32StartTime, u32LockTimeStartDVBC, u32StartTime)); //to measure time
#if (TIMING_VERIFICATION==1)
                        tmm_14 = GIVE_ME_TIME
                                 show_timer();
#endif
                    }
                    bDoReset = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_LOCK;
                }
                else if((u32NowTime - u32ChkScanTimeStart < u32Timeout)
                        || (u32NowTime - u32LockTimeStartDVBC < u32LockTimeout))
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_CHECKING;
                }
                else
                {
                    FECLock = MAPI_FALSE;
                    *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
                }
            }
            break;
            default:
                *((EN_MSB_123X_LOCK_STATUS *)pvParam3) = E_DEMOD_UNLOCK;
        }
    }
    return MAPI_TRUE;
}


//##########################################################################################################
//##########################################################################################################
//########################################  Public:DTV Implementation ######################################
//##########################################################################################################
//##########################################################################################################
// DVBT2 95~101ms, DVBT 38~39ms
MAPI_BOOL DTV_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth, MAPI_BOOL bPalBG, MAPI_BOOL bLPsel)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    UNUSED(u32Frequency);
    UNUSED(bPalBG);
    UNUSED(bLPsel);
    DBG_DEMOD_MSB(printf("DTV_SetFrequency %d ,%d \n", (int)u32Frequency, (int)eBandWidth));
    MAPI_U8 bw = E_DEMOD_BW_8M;
    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

#if(TIMING_VERIFICATION == 1)
    tmm_11 = GIVE_ME_TIME
#endif

    printf("\r\n SetFreq m_enCurrentDemodulator_Type:%d\n",m_enCurrentDemodulator_Type);
    switch(eBandWidth)
    {
        case E_RF_CH_BAND_6MHz:
            bw = E_DEMOD_BW_6M;
            break;
        case E_RF_CH_BAND_7MHz:
            bw = E_DEMOD_BW_7M;
            break;
        case E_RF_CH_BAND_8MHz:
            bw = E_DEMOD_BW_8M;
            break;
        default:
            bw = E_DEMOD_BW_8M;
            break;
    }
    Reset();
    usleep(500);
    printf("\r\n msb123x g_msb123x_plp_id:%d,bw:%d\n",g_msb123x_plp_id,bw);
    WriteDspReg((MAPI_U16)T2_BW, bw);      // BW: 0->1.7M, 1->5M, 2->6M, 3->7M, 4->8M, 5->10M
    WriteDspReg((MAPI_U16)T2_PLP_ID, g_msb123x_plp_id);
    WriteDspReg((MAPI_U16)T2_TH_A_NP1, T2_TH_A_NP1_VAL);

    WriteReg(0x0C00 + (0x0E) * 2, 0x0001); // FSM_EN
    msb123x_show_version();
#if(TIMING_VERIFICATION == 1)
    tmm_12 = GIVE_ME_TIME
             show_timer();
#endif
    return MAPI_TRUE;
}

EN_FRONTEND_SIGNAL_CONDITION DTV_GetSNR(void)
{
    MAPI_U32  snr_out = 0;
    MAPI_U16  snr_ave_num = 0;
    MAPI_U8   reg = 0;
    float   f_snr = (float)0.0;
    float   fSNRDivider[]={1024*2, 2048*2, 4096*2, 8192*2, 16384*2, 32768*2, 32768*2, 32768*2};

    //float   fsnr= 0;
    MAPI_U8 status = MAPI_TRUE;
    EN_FRONTEND_SIGNAL_CONDITION eSignalCondition;
    switch (m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:

            // freeze
            status &= ReadReg(0x2802, &reg);
            reg |= 0x02;
            status &= WriteReg(0x2802, reg);

            // load
            status &= ReadReg(0x2802, &reg);
            reg |= 0x04;
            status &= WriteReg(0x2802, reg);

            status &= ReadReg(0x280D, &reg);
            snr_out = reg;
            status &= ReadReg(0x280C, &reg);
            snr_out = (snr_out << 8) | reg;
            status &= ReadReg(0x280B, &reg);
            snr_out = (snr_out << 8) | reg;
            status &= ReadReg(0x280A, &reg);
            snr_out = (snr_out << 8) | reg;
            snr_out &= 0x1FFFFFFF;
            if (snr_out==0)
            {
                snr_out=1;
            }
            status &= ReadReg(0x2805, &reg);
            snr_ave_num = (reg>>5)&0x07;

            // unfreeze
            status &= ReadReg(0x2802, &reg);
            reg &= (0xff-0x02);
            status &= WriteReg(0x2802, reg);

            f_snr = (float)10.0*Log10Approx((float)snr_out/fSNRDivider[snr_ave_num]);
            g_msb123x_fSNR = f_snr;
            if (f_snr > 42) f_snr = 42;
            if (f_snr < 0) f_snr=0;
            if (f_snr > 25)
                eSignalCondition = E_FE_SIGNAL_STRONG;
            else if (f_snr > 20)
                eSignalCondition = E_FE_SIGNAL_MODERATE;
            else if (f_snr > 15)
                eSignalCondition = E_FE_SIGNAL_WEAK;
            else
                eSignalCondition = E_FE_SIGNAL_NO;
            break;
        default:
            eSignalCondition = E_FE_SIGNAL_NO;
            break;
    }
    return eSignalCondition;
}

MAPI_BOOL DTV_GetPreBER(float *p_preBer)
{
    MAPI_U16 BitErrPeriod = 0;
    MAPI_U16 BitErr = 0;
    MAPI_U8  reg = 0;
    float fber = 0;
    MAPI_U8 status = MAPI_TRUE;

    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        default:
            /////////// Data BER /////////////

            status &= ReadReg(0x2625, &reg);
            BitErrPeriod = reg;
            status &= ReadReg(0x2624, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;

            status &= ReadReg(0x2633, &reg);
            BitErr = reg;
            status &= ReadReg(0x2632, &reg);
            BitErr = (BitErr << 8) | reg;


            if(BitErrPeriod == 0)
            {
                BitErrPeriod = 1;
            }
            status &= ReadReg(0x278e, &reg);    //FEC Type[8:7]

            if((reg & 0x80) == 0x80)
            {
                fber = (float)BitErr / (BitErrPeriod * 64800);
            }
            else
            {
                fber = (float)BitErr / (BitErrPeriod * 16200);
            }

            if(BitErr == 0)
            {
                fber = 1E-8;
            }

            *p_preBer = fber;
            printf("MSB123x Extend Data Pre BER = %8.3e \n ", fber);

            printf("[DVBT2] preber=%f, Err_num=%d, block_count=%d, reg=0x%x\n", fber, BitErr, BitErrPeriod, reg);
            break;
    }
    return status;
}


MAPI_BOOL DTV_GetPostBER(float *p_postBer)
{
    MAPI_U16 BitErrPeriod = 0;
    MAPI_U16 BitErr = 0;
    MAPI_U8  reg = 0;
    float fber = 0;
    MAPI_U8 status = MAPI_TRUE;
    MAPI_U16 block_size = 1;

    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        default:
            /////////// Data BER /////////////

            status &= ReadReg(0x264b, &reg);
            BitErrPeriod = reg;
            status &= ReadReg(0x264a, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;

            status &= ReadReg(0x264d, &reg);
            BitErr = reg;
            status &= ReadReg(0x264c, &reg);
            BitErr = (BitErr << 8) | reg;

            status &= ReadReg(0x278e, &reg);    //FEC Type[8:7]

            if((reg & 0x80) == 0x80)
            {
                // 64800
                switch(reg & 0x07)
                {
                    case 0:
                        block_size = 32400;
                        break;
                    case 1:
                        block_size = 38880;
                        break;
                    case 2:
                        block_size = 43200;
                        break;
                    case 3:
                        block_size = 48600;
                        break;
                    case 4:
                        block_size = 51840;
                        break;
                    case 5:
                        block_size = 54000;
                        break;
                    default:
                        block_size = 1;
                        break;
                }
            }
            else
            {
                // 16200
                switch(reg & 0x07)
                {
                    case 0:
                        block_size = 7200;
                        break;
                    case 1:
                        block_size = 9720;
                        break;
                    case 2:
                        block_size = 10800;
                        break;
                    case 3:
                        block_size = 11880;
                        break;
                    case 4:
                        block_size = 12600;
                        break;
                    case 5:
                        block_size = 13320;
                        break;
                    default:
                        block_size = 1;
                }
            }

            if(BitErrPeriod == 0)
            {
                BitErrPeriod = 1;
            }

            fber = (float)BitErr / (BitErrPeriod * block_size);

            if(BitErr == 0)
            {
                fber = 1E-8;
            }

            *p_postBer = fber;

            printf("[DVBT2] postber=%f, Err_num=%d, block_count=%d, block_size=%d\n", fber, BitErr, BitErrPeriod, block_size);
            break;
    }

    return MAPI_TRUE;
}

MAPI_U32 DTV_GetBER(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8         status = MAPI_TRUE;
    MAPI_U8             reg = 0, reg_frz = 0;
    MAPI_U16            BitErrPeriod = 0;
    MAPI_U32            BitErr = 0;
    MAPI_U16            PktErr = 0;

    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        return 0;
    }
    else if((m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
            || (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C))
    {
        /////////// Post-Viterbi BER /////////////

        // bank 7 0x32 [7] reg_bit_err_num_freeze
        status &= ReadReg(0x1132, &reg_frz);
        status &= WriteReg(0x1132, reg_frz | 0x80);

        // bank 7 0x30 [7:0] reg_bit_err_sblprd_7_0
        //             [15:8] reg_bit_err_sblprd_15_8
        status &= ReadReg(0x1131, &reg);
        BitErrPeriod = reg;

        status &= ReadReg(0x1130, &reg);
        BitErrPeriod = (BitErrPeriod << 8) | reg;

        // bank 7 0x3a [7:0] reg_bit_err_num_7_0
        //             [15:8] reg_bit_err_num_15_8
        // bank 7 0x3c [7:0] reg_bit_err_num_23_16
        //             [15:8] reg_bit_err_num_31_24

        status &= ReadReg(0x113D, &reg);
        BitErr = reg;

        status &= ReadReg(0x113C, &reg);
        BitErr = (BitErr << 8) | reg;

        status &= ReadReg(0x113B, &reg);
        BitErr = (BitErr << 8) | reg;

        status &= ReadReg(0x113A, &reg);
        BitErr = (BitErr << 8) | reg;

#if 1
        // bank 7 0x3e [7:0] reg_uncrt_pkt_num_7_0
        //             [15:8] reg_uncrt_pkt_num_15_8
        status &= ReadReg(0x113F, &reg);
        PktErr = reg;

        status &= ReadReg(0x113E, &reg);
        PktErr = (PktErr << 8) | reg;
#endif

        // bank 7 0x32 [7] reg_bit_err_num_freeze
        status &= WriteReg(0x1132, reg_frz);

        if(BitErrPeriod == 0)   //protect 0
        {
            BitErrPeriod = 1;
        }
        if(status)
        {
            printf(" @MSB1231_GetPostViterbiBer OK\n");
            return  MAPI_TRUE;
        }
        else
        {
            printf(" @MSB1231_GetPostViterbiBer NG\n");
            return MAPI_FALSE;
        }
    }
    return MAPI_FALSE;
}

MAPI_BOOL DTV_DVB_T_Get_TPS_Parameter(MAPI_U16 * pu16TPS_parameter, E_SIGNAL_TYPE eSignalType)
{
    MAPI_U8         u8Data = 0;

    if(DTV_DVB_T_GetLockStatus() == E_DEMOD_LOCK)
    {

        if(eSignalType == TS_MODUL_MODE)
        {

            if(ReadReg(0x2700 + (0x47 * 2), &u8Data) == MAPI_FALSE)
                return MAPI_FALSE;

            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT5 | BIT4 | BIT3)) >> 3;

        }

        else  if(eSignalType == TS_CODE_RATE)
        {
            if(ReadReg(0x2700 + (0x47 * 2), &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT2 | BIT1 | BIT0));

        }

        else if(eSignalType == TS_GUARD_INTERVAL)
        {
            if(ReadReg(0x2400 + 0x40 * 2 + 1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter |= (((MAPI_U16) u8Data) & (BIT6 | BIT5 | BIT4)) >> 4 ;

        }

        else if(eSignalType == TS_FFT_VALUE)
        {
            if(ReadReg(0x2400 + 0x40 * 2 + 1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter |= ((MAPI_U16) u8Data) & (BIT2 | BIT1 | BIT0);

            if((*pu16TPS_parameter) == DEV_MSB123x_FFT_32K_)
                *pu16TPS_parameter = DEV_MSB123x_FFT_32K;

            if((*pu16TPS_parameter) == DEV_MSB123x_FFT_8K_)
                *pu16TPS_parameter = DEV_MSB123x_FFT_8K;

            if(ReadReg(0x2510, &u8Data)  == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }

            *pu16TPS_parameter |= (((MAPI_U16) u8Data) & BIT3) ;
            return MAPI_FALSE;
        }
        else if(eSignalType == TS_PREAMBLE)
        {
            if(ReadReg(0x2700 + (0x30 * 2)+1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT4)) >> 4;
        }
        else if(eSignalType == TS_S1_SIGNALLING)
        {
            if(ReadReg(0x2700 + (0x30 * 2)+1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT3|BIT2|BIT1)) >> 1;
        }
        else if(eSignalType == TS_PILOT_PATTERN)
        {
            if(ReadReg(0x2700 + (0x36 * 2), &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & 0x0F);
        }
        else if(eSignalType == TS_BW_EXT)
        {
            if(ReadReg(0x2700 + (0x30 * 2)+1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT0));
        }
        else if(eSignalType == TS_PAPR_REDUCTION)
        {
            if(ReadReg(0x2700 + (0x31 * 2), &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & 0xF0)>>4;
        }
        else if(eSignalType == TS_OFDM_SYMBOLS_PER_FRAME)
        {
            if(ReadReg(0x2700 + (0x3C * 2), &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (MAPI_U16) u8Data;
            if(ReadReg(0x2700 + (0x3C * 2)+1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter |= (((MAPI_U16) u8Data) & 0x0F)<<8;
        }
        else if(eSignalType == TS_T2_FFT_VALUE)
        {
            if(ReadReg(0x2700 + (0x30 * 2)+1, &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            if((u8Data & (BIT3|BIT2)) >> 2)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT7|BIT6|BIT5)) >> 5;
        }
        else if(eSignalType == TS_T2_GUARD_INTERVAL)
        {
            if(ReadReg(0x2700 + (0x31 * 2), &u8Data) == MAPI_FALSE)
            {
                return MAPI_FALSE;
            }
            *pu16TPS_parameter  = (((MAPI_U16) u8Data) & (BIT3|BIT2|BIT1)) >> 1;
        }
        else
        {
            return MAPI_FALSE;
        }

        return MAPI_TRUE;

    }
    return MAPI_FALSE;
}

MS_BOOL DTV_DVB_T2_GetSignalTpsInfo(MS_U64 *TPS_Info)
{
    MS_BOOL bRet = TRUE;
    MS_U16    u16Data = 0;
    //const char* const cConStr[]={"qpsk","16qam","64qam","256qam"};
    //const char* const cCRStr[]={"1_2","3_5","2_3","3_4","4_5","5_6"};
    //const char* const cGIStr[]={"1_32","1_16","1_8","1_4","1_128","19_128","19_256"};
    //const char* const cFFTStr[]={"2k","8k","4k","1k","16k","32k","8k","32k"};
    //const char* const cPreAStr[]={"mixed","not_mixed"};
    //const char* const cS1SStr[]={"t2_siso","t2_miso","non_t2","reserved"};
    //const char* const cPPSStr[]={"PP1","PP2","PP3","PP4","PP5","PP6","PP7","PP8","reserved"};
    //const char* const cBWStr[]={"normal","extension"};
    //const char* const cPAPRStr[]={"none","ace","tr","tr_and_ace","reserved"};
    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_MODUL_MODE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_MODUL_MODE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info = (MS_U64)(u16Data);
    DBG_SIGNAL_TPS(printf("Constellation:%s\n",cConStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_CODE_RATE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_CODE_RATE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info |= (MS_U64)(u16Data<<3);
    DBG_SIGNAL_TPS(printf("Code Rate:%s\n",cCRStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_T2_GUARD_INTERVAL) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_T2_GUARD_INTERVAL Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info |= (MS_U64)(u16Data<<6);
    DBG_SIGNAL_TPS(printf("GI:%s\n",cGIStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_T2_FFT_VALUE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_T2_FFT_VALUE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    *TPS_Info |= (MS_U64)(u16Data<<9);
    DBG_SIGNAL_TPS(printf("FFT:%s\n",cFFTStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_PREAMBLE) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_PREAMBLE Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x01;
    *TPS_Info |= (MS_U64)(u16Data<<12);
    DBG_SIGNAL_TPS(printf("Preamble:%s\n",cPreAStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_S1_SIGNALLING) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_S1_SIGNALLING Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x03;
    if(u16Data>2)
        u16Data = 3;
    *TPS_Info |= (MS_U64)(u16Data<<13);
    DBG_SIGNAL_TPS(printf("S1Signalling:%s\n",cS1SStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_PILOT_PATTERN) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_PILOT_PATTERN Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x0F;
    if(u16Data>7)
        u16Data = 8;
    *TPS_Info |= (MS_U64)(u16Data<<15);
    DBG_SIGNAL_TPS(printf("PilotPattern:%s\n",cPPSStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_BW_EXT) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_BW_EXT Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x01;
    *TPS_Info |= (MS_U64)(u16Data<<19);
    DBG_SIGNAL_TPS(printf("BW EXT:%s\n",cBWStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_PAPR_REDUCTION) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_PAPR_REDUCTION Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0x07;
    if(u16Data>3)
        u16Data = 4;
    *TPS_Info |= (MS_U64)(u16Data<<20);
    DBG_SIGNAL_TPS(printf("PAPR:%s\n",cPAPRStr[u16Data]));

    if(DTV_DVB_T_Get_TPS_Parameter(&u16Data, TS_OFDM_SYMBOLS_PER_FRAME) == MAPI_FALSE)
    {
        DBG_SIGNAL_TPS(printf("TS_OFDM_SYMBOLS_PER_FRAME Error!\n"));
        bRet = FALSE;
    }
    u16Data &= 0xFFF;
    *TPS_Info |= (MS_U64)(u16Data<<23);
    DBG_SIGNAL_TPS(printf("OFDM Symbols:%u\n",u16Data));

    return bRet;
}

MAPI_U16 DTV_GetSignalQuality(void)
{
    MAPI_U8     status = true;
    MAPI_U8     reg = 0; //, reg_frz;
    MAPI_U16    BitErrPeriod = 0;
    MAPI_U32    BitErr = 0;
    MAPI_U16    FecType = 0;
    MAPI_U8     u8_index = 0;
    float       fber = (float)0.0;
    float       log_ber = (float)0.0;
    float       SQI = (float)0.0;
    float       BER_SQI = (float)0.0;
    float       cn_ref = (float)0.0;
    float       cn_rec = (float)0.0;
    float       cn_rel = (float)0.0;
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        {
            E_T2_CONSTEL  constel =  _T2_QAM_UNKNOWN;
            E_T2_CODERATE coderate = _T2_CR_UNKNOWN;

            /////////// Check lock status /////////////
            ReadDspReg(0x00f0, &reg);
            if((reg & BIT7) == 0x00)
            {
                return 0;
            }
            /////////// Data BER /////////////
            // bank 38 0x02 [0] freeze
            status &= WriteReg(0x2604, 0x01);    // avoid confliction

            // bank 38 0x12 Data BER Window[15:0]
            status &= ReadReg(0x2625, &reg);
            BitErrPeriod = reg;
            status &= ReadReg(0x2624, &reg);
            BitErrPeriod = (BitErrPeriod << 8) | reg;

            // bank 38 0x32 Data BER count[15:0]
            // bank 38 0x33 Data BER count[31:16]
            status &= ReadReg(0x2667, &reg);
            BitErr = reg;
            status &= ReadReg(0x2666, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= ReadReg(0x2665, &reg);
            BitErr = (BitErr << 8) | reg;
            status &= ReadReg(0x2664, &reg);
            BitErr = (BitErr << 8) | reg;

            // bank 38 0x02 [0] freeze
            // status &= WriteReg(0x2604, 0x00);     // avoid confliction

            if(BitErrPeriod == 0)
                //protect 0
                BitErrPeriod = 1;

            // status &= ReadReg(0x268e, &reg);    //FEC Type[8:7]
            status &= ReadReg(0x278f, &reg);    //FEC Type[8:7]
            FecType = reg;
            status &= ReadReg(0x278e, &reg);    //FEC Type[8:7]
            FecType = (FecType << 8) | reg;
            // if (reg&0x080)
            if (FecType&0x0180)
            {
                fber = (float)BitErr / (BitErrPeriod * 64800);
            }
            else
            {
                fber = (float)BitErr / (BitErrPeriod * 16200);
            }
            if(status == MAPI_FALSE)
            {
                DBG_DEMOD_MSB(printf("DTV_GetSignalQuality_DVBT2_GetPostViterbiBer Fail!\n"));
                return 0;
            }

            log_ber = Log10Approx((float)1.0/fber);  // provide 1~2^32 input range only
            if (log_ber >= 2.2)
            // PostVit BER < 0.006
            {
                BER_SQI = (float)100.0;
            }
            else if (log_ber >= 1.1)
            {               // 0.07
                BER_SQI= (float)100.0 - ((log_ber - 2.2)/(1.1-2.2)*100.0);
            }
            else
            {
                BER_SQI = (float)0.0;
            }

            ReadReg(0x2700+0x47*2, &reg);
            coderate = (E_T2_CODERATE)(reg&0x07);
            constel = (E_T2_CONSTEL)((reg>>3)&0x07);

            DTV_GetSNR();
            cn_rec = g_msb123x_fSNR;
            cn_ref = (float)-1.0;
            while(g_msb123x_dvbt2_sqi_cn_nordigp1[u8_index].constel != _T2_QAM_UNKNOWN)
            {
                if (g_msb123x_dvbt2_sqi_cn_nordigp1[u8_index].constel == constel
                    && g_msb123x_dvbt2_sqi_cn_nordigp1[u8_index].code_rate == coderate)
                {
                   cn_ref = g_msb123x_dvbt2_sqi_cn_nordigp1[u8_index].cn_ref;
                   break;
                }
                else
                {
                   u8_index++;
                }
            }
            if (cn_ref == -1.0)
            {
                SQI = (float)0.0;
            }
            else
            {
                cn_rel = cn_rec - cn_ref;
                if (cn_rel >= 3.0)
                {
                    SQI = BER_SQI;
                }
                else if (cn_rel >= -7)
                {
                    SQI = ((cn_rel-3)/10+1)*BER_SQI;
                }
                else
                {
                    SQI = (float)0.0;
                }
            }
            // printf("[msb123x]signalquality, coderate=%d, constel=%d,cn_rec=%f, cn_ref=%f, BER_SQI=%f, SQI=%f,log_ber=%f\n",coderate,constel,cn_rec,cn_ref,BER_SQI,SQI,log_ber);
            return SQI;
            break;
        }
        default:
            break;
    }  // end of switch
    return 0;
}

MAPI_U16 DTV_GetSignalStrength(void)
{
    //MAPI_U8    status = true;
    MAPI_U8    reg_tmp = 0;
    //MAPI_U8    rf_agc_val = 0;
    MAPI_U8    if_agc_val = 0;
    //MAPI_U8    i = 0;
    //MAPI_U8    ssi_tbl_len = 0;
    //MAPI_U8    tps_cnstl = 0;
    //MAPI_U8    tps_cr = 0;
    MAPI_U8    ssi = 0;
    MAPI_U8    u8RFAGC = 0;
    MAPI_U16   ypIFAGC1 = 0, ypIFAGC2 = 0;
    float    ch_power_db = 0;
    float    ch_power_rf = 0;
    float    ch_power_if = 0;
    //float    ch_power_ref = 0;
    //float    ch_power_rel = 0;
    //EN_MSB_123X_LOCK_STATUS eLockStatus = E_DEMOD_CHECKING;
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
        {
            /***************************************
            * Force u8RFAGC 150 due to unknown SAR port for each demo board.
            ***************************************/
            // u8RFAGC=MDrv_SAR_Adc_GetValue(2);
            u8RFAGC = 150;
            DBG_GET_SIGNAL(printf(">>> RFAGC = %d <<<\n", (int)u8RFAGC));
            if ( u8RFAGC < 89)
            {
                ch_power_rf = -45;
            }
            else if ( u8RFAGC < 111)
            {
                ch_power_rf = (-45) - (float)((u8RFAGC - 89)*5) /(111-89);
            }
            else if ( u8RFAGC < 149)
            {
                ch_power_rf = (-50) - (float)((u8RFAGC - 111)*5) /(148-111);
            }
            else
            {
                ch_power_rf = -55;
            }
            // IFAGC
            // debug select
            WriteReg(0x3e00 + 0x13 * 2, 0x03);
            WriteReg(0x3e00 + 0x02 * 2, 0x00); //set freeze & dump [Write]
            WriteReg(0x3e00 + 0x02 * 2 + 1, 0x80);

            // agc gain2 24 Bit
            //ReadReg(0x3e00+0x14*2+1, &reg_tmp);
            ReadReg(0x3e00+0x14*2+2, &reg_tmp);
            ypIFAGC2 = reg_tmp;
            ReadReg(0x3e00+0x14*2+1, &reg_tmp);
            ypIFAGC1 = reg_tmp;
            ReadReg(0x3e00+0x14*2+0, &reg_tmp);
            ypIFAGC1 = (ypIFAGC1 << 8) | reg_tmp;
            // printf("============================>[YP] IFAGC_2 = %x, IFAGC_1 = %x\n", ypIFAGC2, ypIFAGC1);
            ReadReg(0x3e00 + 0x14 * 2 + 1, &reg_tmp);

            WriteReg(0x3e00+0x02*2, 0x00);   //set freeze & dump [Write]
            WriteReg(0x3e00+0x02*2+1, 0x00);
            DBG_GET_SIGNAL(printf(">>> reg_tmp = %x <<<\n", (int)reg_tmp));
            if_agc_val = reg_tmp;
            DBG_GET_SIGNAL(printf(">>> if_agc_val = %d <<<\n", (int)if_agc_val));

            if ( if_agc_val < 67)
            {
                ch_power_if = -55;
            }
            else if ( if_agc_val < 76)
            {
                ch_power_if = (-55) - (float)((if_agc_val - 67)*5) /(76-67);
            }
            else if ( if_agc_val < 88)
            {
                ch_power_if = (-60) - (float)((if_agc_val - 76)*5) /(88-76);
            }
            else if ( if_agc_val < 99)
            {
                ch_power_if = (-65) - (float)((if_agc_val - 88)*5) /(99-88);
            }
            else if ( if_agc_val < 113)
            {
                ch_power_if = (-70) - (float)((if_agc_val - 99)*5) /(113-99);
            }
            else if ( if_agc_val < 128)
            {
                ch_power_if = (-75) - (float)((if_agc_val - 113)*5) /(128-113);
            }
            else if ( if_agc_val < 145)
            {
                ch_power_if = (-80) - (float)((if_agc_val - 128)*5) /(145-128);
            }
            else if ( if_agc_val < 165)
            {
                ch_power_if = (-85) - (float)((if_agc_val - 145)*5) /(165-145);
            }
            else if ( if_agc_val < 183)
            {
                ch_power_if = (-90) - (float)((if_agc_val - 165)*5) /(183-165);
            }
            else
            {
                ch_power_if = -96;
            }
            if(ch_power_rf > (-55.0 + 0.5))
            {
                ch_power_db = ch_power_rf;
            }
            else if(ch_power_if < (-55.0 - 0.5))
            {
                ch_power_db = ch_power_if;
            }
            else
            {
                ch_power_db = (ch_power_if + ch_power_rf)/2;
            }
            DBG_GET_SIGNAL(printf("ch_power_rf = %f\n", ch_power_rf));
            DBG_GET_SIGNAL(printf("ch_power_if = %f\n", ch_power_if));
            DBG_GET_SIGNAL(printf("ch_power_db = %f\n", ch_power_db));
            // -50 dB ~ -95 dB
            // 100 ~ 0

            if(ch_power_db > -50)
            {
              ssi = 100;
            }
            else if(ch_power_db < -95)
            {
              ssi = 0;;
            }
            else
            {
              ssi = 100 - ((-50 - ch_power_db) * 2.22);
            }
            DBG_GET_SIGNAL(printf(">>> SSI = %d <<<\n", (int)ssi));
        }
        break;
        case E_DEVICE_DEMOD_DVB_T:
        case E_DEVICE_DEMOD_DVB_C:
        default:
            ssi = 0;
            DBG_GET_SIGNAL(printf("Undefined!!!\n"));
            break;
    }
    return ssi;
}

void Driving_Control(MAPI_BOOL bEnable)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8 u8Temp;
    ReadReg(0x0958, &u8Temp);
    if(bEnable)
    {
        u8Temp = 0xFF;
    }
    else
    {
        u8Temp = 0x00;
    }
    WriteReg(0x0958, u8Temp);

    ReadReg(0x0959, &u8Temp);
    if(bEnable)
    {
        u8Temp = u8Temp | 0x0F;
    }
    else
    {
        u8Temp = u8Temp & (~0x0F);
    }
    WriteReg(0x0959, u8Temp);
}

MAPI_BOOL DTV_Serial_Control(MAPI_BOOL bEnable)
{
    UNUSED(bEnable);
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        //FRA_T2_BRINGUP
    }
    Driving_Control(1);
    return MAPI_TRUE;
}

EN_MSB_123X_LOCK_STATUS DTV_DVB_T_GetLockStatus(void)
{
    EN_MSB_123X_LOCK_STATUS eLockStatus = E_DEMOD_CHECKING;
    ExtendCmd(0xFF, 0, 0, (void *)&eLockStatus);
    return eLockStatus;
}

MAPI_BOOL I2C_CH_Reset(MAPI_U8 ch_num)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_U8         data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};

    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]I2C_CH_Reset, CH=0x%x\n", ch_num));
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);

    if (iptr == NULL)
    {
        printf("%s(),%d Init Fail\n",__func__,__LINE__);
        return MAPI_FALSE;
    }
    // 8'hb2(SRID)->8,h53(PWD1)->8,h45(PWD2)->8,h52(PWD3)->8,h44(PWD4)->8,h42(PWD5)
    data[0] = 0x53;
  // Don't check Ack because this passward only ack one time for the first time.
    iptr->WriteBytes(0, NULL, 5, data);

    // 8'hb2(SRID)->8,h71(CMD)  //TV.n_iic_
    data[0] = 0x71;
    bRet&=iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h81(CMD)  //TV.n_iic_sel_b0
    data[0] = ((ch_num & 0x01) != 0) ? 0x81 : 0x80;
    bRet&=iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h83(CMD)  //TV.n_iic_sel_b1
    data[0] = ((ch_num & 0x02) != 0) ? 0x83 : 0x82;
    bRet&=iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h84(CMD)  //TV.n_iic_sel_b2
    data[0] = ((ch_num & 0x04) != 0) ? 0x85 : 0x84;
    bRet&=iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h53(CMD)  //TV.n_iic_ad_byte_en2, 32bit read/write
    data[0] = 0x53;
    bRet&=iptr->WriteBytes(0, NULL, 1, data);

    // 8'hb2(SRID)->8,h7f(CMD)  //TV.n_iic_sel_use_cfg
    data[0] = 0x7f;
    bRet&=iptr->WriteBytes(0, NULL, 1, data);

    /*
        // 8'hb2(SRID)->8,h35(CMD)  //TV.n_iic_use
        data[0] = 0x35;
        iptr->WriteBytes(0, NULL, 1, data);

        // 8'hb2(SRID)->8,h71(CMD)  //TV.n_iic_Re-shape
        data[0] = 0x71;
        iptr->WriteBytes(0, NULL, 1, data);
    */
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]I2C_CH_Reset, CH=0x%x\n", ch_num));
    return bRet;
}

MAPI_BOOL WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_BOOL bRet=MAPI_TRUE;
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);
    if (iptr == NULL)
    {
        printf("%s(),%d Init Fail\n",__func__,__LINE__);
        return MAPI_FALSE;
    }
    g_u8MsbData[0] = 0x10;
    g_u8MsbData[1] = 0x00;
    g_u8MsbData[2] = 0x00;
    g_u8MsbData[3] = (u16Addr >> 8) & 0xff;
    g_u8MsbData[4] = u16Addr & 0xff;
    g_u8MsbData[5] = u8Data;

    g_u8MsbData[0] = 0x35;
    bRet&=iptr->WriteBytes(0, NULL, 1, g_u8MsbData);

    g_u8MsbData[0] = 0x10;
    bRet&=iptr->WriteBytes(0, NULL, 6, g_u8MsbData);

    g_u8MsbData[0] = 0x34;
    bRet = iptr->WriteBytes(0, NULL, 1, g_u8MsbData);
    return bRet;

}

MAPI_BOOL WriteRegs(MAPI_U16 u16Addr, MAPI_U8* u8pData, MAPI_U16 data_size)
{
    MAPI_BOOL bRet = true;
    MAPI_U8   u8MsbDataValue[LOAD_CODE_I2C_BLOCK_NUM + 5];
    MAPI_U16   idx = 0;

    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);
    if (iptr == NULL)
    {
        printf("%s(),%d Init Fail\n",__func__,__LINE__);
        return MAPI_FALSE;
    }
    u8MsbDataValue[0] = 0x10;
    u8MsbDataValue[1] = 0x00;
    u8MsbDataValue[2] = 0x00;
    u8MsbDataValue[3] = (u16Addr >> 8) & 0xff;
    u8MsbDataValue[4] = u16Addr & 0xff;
    for(idx = 0; idx < data_size ; idx++)
    {
        u8MsbDataValue[5+idx] = u8pData[idx];
    }

    u8MsbDataValue[0] = 0x35;
    bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbDataValue);

    u8MsbDataValue[0] = 0x10;
    bRet &= iptr->WriteBytes(0, NULL, 5 + data_size, u8MsbDataValue);

    u8MsbDataValue[0] = 0x34;
    bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbDataValue);

    return bRet;
}

MAPI_BOOL WriteReg2bytes(MAPI_U16 u16Addr, MAPI_U16 u16Data)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL ret = true;
    ret &= WriteReg(u16Addr, (MAPI_U8)u16Data & 0x00ff);
    ret &= WriteReg(u16Addr + 0x0001, (MAPI_U8)(u16Data >> 8) & 0x00ff);
    return ret;
}

MAPI_BOOL ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_BOOL bRet;
    mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(MSB123X_DEMOD_IIC);
    if (iptr == NULL)
    {
        printf("%s(),%d Init Fail\n",__func__,__LINE__);
        return MAPI_FALSE;
    }
    g_u8MsbData[0] = 0x10;
    g_u8MsbData[1] = 0x00;
    g_u8MsbData[2] = 0x00;
    g_u8MsbData[3] = (u16Addr >> 8) & 0xff;
    g_u8MsbData[4] = u16Addr & 0xff;

    g_u8MsbData[0] = 0x35;
    iptr->WriteBytes(0, NULL, 1, g_u8MsbData);

    g_u8MsbData[0] = 0x10;
    iptr->WriteBytes(0, NULL, 5, g_u8MsbData);
    iptr->ReadBytes(0, NULL, 1, pu8Data);

    g_u8MsbData[0] = 0x34;
    bRet = iptr->WriteBytes(0, NULL, 1, g_u8MsbData);
    return bRet;
}

#define REG_MB_CNTL     0x0C00
#define REG_MB_ADDR_L   0x0C02
#define REG_MB_ADDR_H   0x0C03
#define REG_MB_DATA     0x0C04
MAPI_BOOL  WriteDspReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    status &= WriteReg(REG_MB_DATA, u8Data);
    status &= WriteReg(REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= WriteReg(REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= WriteReg(REG_MB_CNTL, 0x04);

    do
    {
        status &= ReadReg(REG_MB_CNTL, &cntl);
        if(cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB123X_MB_WRITE_FAILURE\n"));
            return false;
        }
    }
    while(cntl != 0xff);
    return status;
}

MAPI_BOOL ReadDspReg(MAPI_U16 u16Addr, MAPI_U8* pData)
{
    //DBG_DEMOD_FLOW(printf("%s(),%d\n",__func__,__LINE__));
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;

    status &= WriteReg(REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= WriteReg(REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= WriteReg(REG_MB_CNTL, 0x03);

    do
    {
        status &= ReadReg(REG_MB_CNTL, &cntl);
        if(cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB123X_MB_READ_FAILURE\n"));
            return false;
        }
    }
    while(cntl != 0xff);

    status &= ReadReg(REG_MB_DATA, pData);
    return status;
}

/*@ <Operation ID=I2b28dd03m121c8cf959bmm6faa> @*/
MAPI_BOOL Cmd_Packet_Send(S_CMDPKTREG *pCmdPacket, MAPI_U8 param_cnt)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

    MAPI_U8 status = true, indx;
    //MAPI_U8             reg_val, timeout = 0;
    MAPI_U16 timeout = 0;
    MAPI_U8 reg_val = 0;
    // ==== Command Phase ===================
    DBG_DEMOD_MSB(printf(">>>MSB123x: (cmd=0x%x)(0x%x,0x%x,0x%x,0x%x,0x%x,0x%x,) \n", pCmdPacket->cmd_code, pCmdPacket->param[0], pCmdPacket->param[1], pCmdPacket->param[2], pCmdPacket->param[3], pCmdPacket->param[4], pCmdPacket->param[5]));
    do
    {
        status &= ReadReg(REG_CMD_CTRL, &reg_val);
        if((reg_val & _BIT_END) != _BIT_END)
            break;
        //MDrv_Timer_Delayms(5);
        usleep(5 * 1000);
        if(timeout++ > 200)
        {
            DBG_DEMOD_MSB(printf(">>>MSB123x: MSB123x_Cmd_Packet_Send fail on 'wait _BIT_END clear' \n"));
            return false;
        }
    }
    while(1);

    // set cmd_3:0 and _BIT_START
    status &= ReadReg(REG_CMD_CTRL, &reg_val);
    reg_val = (reg_val & 0x0f) | (pCmdPacket->cmd_code << 4) | _BIT_START;
    status &= WriteReg(REG_CMD_CTRL, reg_val);

    // wait _BIT_START clear
    do
    {
        status &= ReadReg(REG_CMD_CTRL, &reg_val);
        if((reg_val & _BIT_START) != _BIT_START)
            break;
        usleep(5 * 1000);
        if(timeout++ > 200)
        {
            DBG_DEMOD_MSB(printf(">>>MSB123x: MSB123x_Cmd_Packet_Send fail on 'wait _BIT_START clear' \n"));
            return false;
        }
    }
    while(1);

    // ==== Data Phase ======================
    status &= WriteReg(REG_CMD_ADDR, 0x00);
    for(indx = 0; indx < param_cnt; indx++)
    {
        status &= ReadReg(REG_CMD_ADDR, &reg_val);
        DBG_DEMOD_MSB(printf("demod_config: param[%d] = %x\n", reg_val, pCmdPacket->param[indx]));
        // set param[indx] and _BIT_DRQ
        status &= WriteReg(REG_CMD_DATA, pCmdPacket->param[indx]);
        status &= ReadReg(REG_DTA_CTRL, &reg_val);
        status &= WriteReg(REG_DTA_CTRL, reg_val | _BIT_DRQ);

        // wait _BIT_DRQ clear
        do
        {
            status &= ReadReg(REG_DTA_CTRL, &reg_val);
            if((reg_val & _BIT_DRQ) != _BIT_DRQ)
                break;
            usleep(5 * 1000);
            if(timeout++ > 200)
            {
                DBG_DEMOD_MSB(printf(">>>MSB123x: MSB123x_Cmd_Packet_Send fail on 'wait _BIT_DRQ clear' \n"));
                return false;
            }
        }
        while(1);
    }

    // ==== End Phase =======================
    // set _BIT_END to finish command
    status &= ReadReg(REG_CMD_CTRL, &reg_val);
    status &= WriteReg(REG_CMD_CTRL, reg_val | _BIT_END);
    return status;
}

MAPI_BOOL LoadDSPCode(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][beg]LoadDspCode\n"));
    MAPI_U32        u32Timeout = 0;
    MAPI_U8         u8DoneFlag = 0;
    MAPI_U8         u8Data = 0;
    MAPI_BOOL       bRet = true;
    DBG_DEMOD_MSB(printf(">>>MSB123x: Load DSP...\n"));
#if(TIMING_VERIFICATION == 1)
    tmm_9 = GIVE_ME_TIME
#endif

    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            u8Data = 1;
            break;
        case E_DEVICE_DEMOD_DVB_T:
            u8Data = 2;
            break;
        case E_DEVICE_DEMOD_DVB_C:
            u8Data = 3;
            break;
        default:
            u8Data = 2;
            return MAPI_FALSE;
    }

    if(g_WO_SPI_FLASH == 1)
    {
        MAPI_U8 u8FirmwareType = MSB123x_DVBT;

        // mask miu access for all and mcu
        bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
        bRet &= WriteReg(0x1200+(0x23)*2,0xfe);
        // 10us delay
        usleep(10);

        // Disable MCU
        bRet &= WriteReg(0x0b00 + (0x19) * 2, 0x03);

        switch(u8Data)
        {
            case 1:
                u8FirmwareType = MSB123x_DVBT2;
                break;
            case 2:
            default:
                u8FirmwareType = MSB123x_DVBT;
                break;
            case 3:
                u8FirmwareType = MSB123x_DVBC;
                break;
        }

        bRet &= LoadDspCodeToSDRAM(u8FirmwareType);

        bRet &= LoadSdram2Sram(u8FirmwareType);

        // enable miu access of mcu gdma
        bRet &= WriteReg(0x1200+(0x23)*2,0xf0);
        // 10us delay
        usleep(10);

        // Enable MCU
        bRet &= WriteReg(0x0b00 + (0x19) * 2, 0x00);
    }
    else
    {
        printf("\r\n >>> LoadDSPCode u8Data : %x\n",u8Data);
        // mask miu access for all and mcu
        bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
        bRet &= WriteReg(0x1200+(0x23)*2,0xfe);
        // 10us delay
        usleep(10);

        // Disable MCU
        WriteReg(0x0b00 + (0x19) * 2, 0x03);

        // Run code on bootloader
        WriteReg(0x1000 + (0x0c) * 2, 0x02);

        // Assign f/w code type to load => 0: boot-loader 1: dvbt2, 2: dvbt, 3: dvbc
        WriteReg(0x0900 + (0x4f) * 2, u8Data);


        // enable miu access of mcu gdma
        bRet &= WriteReg(0x1200+(0x23)*2,0xf0);
        // 10us delay
        usleep(10);

        // Enable MCU
        WriteReg(0x0b00 + (0x19) * 2, 0x00);

        do
        {
            ReadReg(0x0900 + (0x4f) * 2, &u8DoneFlag);

            if(u32Timeout++ > 500)
            {
                return MAPI_FALSE;
            }

            usleep(1 * 1000);
            printf("\r\n >>>Init timeout u8DoneFlag:%x\n",u8DoneFlag);
        }
        while(u8DoneFlag != 0xaa);

        // mask miu access for all and mcu
        bRet &= WriteReg(0x1200+(0x23)*2 + 1,0x7f);
        bRet &= WriteReg(0x1200+(0x23)*2,0xfe);
        // 10us delay
        usleep(10);

        // Disable MCU
        WriteReg(0x0b00 + (0x19) * 2, 0x03);

        // Run code on loaded firmware
        WriteReg(0x1000 + (0x0c) * 2, 0x05);

        do
        {
            ReadReg(0x1000 + (0x0c) * 2, &u8DoneFlag);

            if(u32Timeout++ > 500)
                return MAPI_FALSE;

            usleep(1 * 1000);

        }
        while(u8DoneFlag != 0x05);

        // enable miu access of mcu gdma
        bRet &= WriteReg(0x1200+(0x23)*2,0xf0);
        // 10us delay
        usleep(10);

        // Enable MCU
        WriteReg(0x0b00 + (0x19) * 2, 0x00);
    }
    switch(m_enCurrentDemodulator_Type)
    {
        case E_DEVICE_DEMOD_DVB_T2:
            DTV_DVBT2_DSPReg_Init();
            break;
        default:
            return MAPI_FALSE;
    }

#if(TIMING_VERIFICATION == 1)
    tmm_10 = GIVE_ME_TIME
#endif
    DBG_DEMOD_LOAD_I2C(printf("[msb123x][end]LoadDspCode\n"));
    return bRet;
}

MAPI_BOOL SetCurrentDemodulatorType(EN_DEVICE_DEMOD_TYPE enDemodType)
{
    UNUSED(enDemodType);
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));

#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    if(enDemodType == m_enCurrentDemodulator_Type)
    {
        return MAPI_TRUE;
    }
#endif
    u32ChkScanTimeStart = MsOS_GetSystemTime();
    m_enCurrentDemodulator_Type = E_DEVICE_DEMOD_DVB_T2;
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    if(bPower_init_en != MAPI_TRUE)
    {
        return MAPI_TRUE;
    }
#endif
    if(LoadDSPCode() == MAPI_FALSE)
    {

        ERR_DEMOD_MSB(printf(">>>>MSB123x:Fail\n"));
        return MAPI_FALSE;
    }
    else
    {
        DBG_DEMOD_MSB(printf(">>>MSB123x:OK\n"));
    }
    return MAPI_TRUE;
}


/************************************************************************************************
Subject:    Get PLP-ID Bit Map
Function:   DTV_GetPlpBitMap
Parmeter:   u32PlpBitMap
Return:     BOOLEAN :
Remark:     32 byte of data to show PLP-ID existense
            |00000000|00000000|...|00000000|00011111|11111111|
             byte31   byte30   ... byte2    byte1    byte0   => 256 bit in total
*************************************************************************************************/

MAPI_BOOL DTV_GetPlpBitMap(MAPI_U8* u8PlpBitMap)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL   status = MAPI_TRUE;
    MAPI_U8     u8Data = 0;
    MAPI_U8     indx = 0;

    status &= ReadDspReg(0x0120, &u8Data);     // check L1 ready
    if(u8Data != 0x30)
        return MAPI_FALSE;

    while(indx < 32)
    {
        status &= ReadDspReg(0x0100 + indx, &u8Data);
        u8PlpBitMap[indx] = u8Data;
        indx++;
    }

    return status;
}

MAPI_BOOL DTV_GetPlpGroupID(MAPI_U8 u8PlpID, MAPI_U8* u8GroupID)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    MAPI_BOOL   status = MAPI_TRUE;
    MAPI_U8 u8Data = 0;
    status &= ReadDspReg(0x0120, &u8Data);         // check L1 ready
    if(u8Data != 0x30)
    {
        ERR_DEMOD_MSB(printf("[msb123x]dvbt2 L1 not ready yet\n"));
        return MAPI_FALSE;
    }
    ReadDspReg(0x00f0, &u8Data);

    if((u8Data & BIT7) == 0x00)
    {
        ERR_DEMOD_MSB(printf("[msb123x]dvbt2 is un-lock\n"));
        return MAPI_FALSE;
    }
    // assign PLP-ID value
    status &= WriteReg(0x2700 + (0x78) * 2, u8PlpID);
    status &= WriteReg(0x2700 + (0x01) * 2 + 1, 0x01); // MEM_EN
    usleep(1000);
    status &= ReadReg(0x2700 + (0x79) * 2, u8GroupID);
    status &= WriteReg(0x2700 + (0x01) * 2 + 1, 0x00); // ~MEM_EN

    return status;
}

MAPI_BOOL DTV_SetPlpGroupID(MAPI_U8 u8PlpID, MAPI_U8 u8GroupID)
{
    MAPI_BOOL   status = MAPI_TRUE;
    FECLock = MAPI_FALSE;
    u32ChkScanTimeStart = MsOS_GetSystemTime();

    g_msb123x_plp_id = u8PlpID;
    g_msb123x_group_id = u8GroupID;
    return status;
}
MAPI_U16 DTV_GetCellID(void)
{
    MAPI_U8 id = 0;
    MAPI_U8 status = MAPI_TRUE;
    MAPI_U16  cell_id  = 0;
    if(m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T2)
    {
        return 0;
    }
    else if((m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_T)
            || (m_enCurrentDemodulator_Type == E_DEVICE_DEMOD_DVB_C))
    {
        status &= WriteReg(0x0ffe, 0x01);

        status &= ReadReg(0x0f2b, &id);
        cell_id = (MAPI_U16)id;

        status &= ReadReg(0x0f2a, &id);
        cell_id |= (MAPI_U16)id << 8;

        status &= WriteReg(0x0ffe, 0x00);

        if(status)
        {
            printf(" @MSB1231_GetCellId OK\n");
            return  MAPI_TRUE;
        }
        else
        {
            printf(" @MSB1231_GetCellId NG\n");
            return MAPI_FALSE;
        }
    }
    return cell_id;

}

MAPI_U16 MSB1231_Lock(COFDM_LOCK_STATUS_123X eStatus)
{
    MAPI_U16        u16Address = 0;
    MAPI_U8         cData = 0;
    MAPI_U8         cBitMask = 0;
    MAPI_U8         use_dsp_reg = 0;
    switch(eStatus)
    {
        case COFDM_P1_LOCK_123X:
            u16Address =  0x2482; //Pl lock,
            cBitMask = BIT3;
            break;

        case COFDM_P1_LOCK_HISTORY_123X:
            use_dsp_reg = 1;
            u16Address =  0x00F0; //Pl ever lock,
            cBitMask = BIT5;//BIT3;
            break;

        case COFDM_L1_CRC_LOCK_123X:
            u16Address =  0x2741; //L1 CRC check,
            cBitMask = BIT5 | BIT6 | BIT7;
            break;

        case COFDM_FEC_LOCK_T2_123X:
            use_dsp_reg = 1;
            u16Address =  0x00F0; //FEC lock,
            cBitMask = BIT7;
            break;
        default:
            return MAPI_FALSE;
    }
    if(!use_dsp_reg)
    {
        if(ReadReg(u16Address, &cData) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
    }
    else
    {
        if(ReadDspReg(u16Address, &cData) == MAPI_FALSE)
        {
            return MAPI_FALSE;
        }
    }
    //printf("\r\n >>> MSB1231_Lock cData = %x\n",cData);
    if((cData & cBitMask) == cBitMask)
    {
        return MAPI_TRUE;
    }
    return MAPI_FALSE;
}
MAPI_BOOL DTV_IsHierarchyOn(void)
{
    return MAPI_FALSE;
}

MS_BOOL DTV_GetSNR_F(float *fSNR)
{
    DTV_GetSNR();
    *fSNR = g_msb123x_fSNR;
    return TRUE;
}

MS_BOOL DTV_Get_Current_Plp_Id(MS_U8 *plp_id)
{
    MS_BOOL  rbet = true;
    MS_U8    reg;

    rbet &= ReadDspReg((MAPI_U16)T2_PLP_ID, &reg);
    *plp_id = reg;
    return rbet;
}

void DTV_ControlTsOutput(BOOLEAN bEnable)
{
    if(bEnable)
    {
        WriteReg(0x0900 + (0x2D*2), 0xFF);
    }
    else
    {
        WriteReg(0x0900 + (0x2D*2), 0x00);
    }
}



MAPI_BOOL DTV_GetPacketErr(MAPI_U16 *pu16BitErr)
{
    MAPI_BOOL status = MAPI_TRUE;
    MAPI_U8   reg = 0;
    MAPI_U16  PktErr=0;

    if (FECLock == TRUE)
    {

       //read packet error
       status &= ReadReg(0x2600+(0x2d<<1)+1, &reg);
       PktErr = reg;
       status &= ReadReg(0x2600+(0x2d<<1), &reg);
       PktErr = (PktErr << 8)|reg;
       *pu16BitErr = PktErr;
       DBG_DEMOD_MSB(printf("[dvbt2]GetPktErr = %d\n",PktErr);)
    }
    else
       *pu16BitErr = 65535;

    return status;
}


ST_MAPI_DEMODULATOR_FUN* DeviceDemodCreate(void)
{
    DBG_DEMOD_FLOW(printf("%s(),%d\n", __func__, __LINE__));
    memset(&stMapiDemodulatorFun, 0, sizeof(ST_MAPI_DEMODULATOR_FUN));

    //Public:Common
    stMapiDemodulatorFun.Connect = Connect;
    stMapiDemodulatorFun.Disconnect = Disconnect;
    stMapiDemodulatorFun.Reset = Reset;
    stMapiDemodulatorFun.IIC_Bypass_Mode = IIC_Bypass_Mode;
    stMapiDemodulatorFun.Power_On_Initialization = Power_On_Initialization;
    stMapiDemodulatorFun.Set_PowerOn = Set_PowerOn;
    stMapiDemodulatorFun.Set_PowerOff = Set_PowerOff;
    stMapiDemodulatorFun.Active = Active;
    stMapiDemodulatorFun.GetCurrentDemodulatorType = GetCurrentDemodulatorType;
    stMapiDemodulatorFun.SetCurrentDemodulatorType = SetCurrentDemodulatorType;
    stMapiDemodulatorFun.ExtendCmd = ExtendCmd;

    //Public:DTV
    stMapiDemodulatorFun.DTV_SetFrequency = DTV_SetFrequency;
    stMapiDemodulatorFun.DTV_GetSNR = DTV_GetSNR;
    stMapiDemodulatorFun.DTV_GetBER = DTV_GetBER;
    // stMapiDemodulatorFun.DTV_GetPacketErr = DTV_GetPacketErr;
    stMapiDemodulatorFun.DTV_GetSignalQuality = DTV_GetSignalQuality;
    stMapiDemodulatorFun.DTV_GetPostBER = DTV_GetPostBER;
    stMapiDemodulatorFun.DTV_GetSignalStrength = DTV_GetSignalStrength;
    stMapiDemodulatorFun.DTV_GetCellID = DTV_GetCellID;
    stMapiDemodulatorFun.DTV_Serial_Control = DTV_Serial_Control;
    stMapiDemodulatorFun.DTV_IsHierarchyOn = DTV_IsHierarchyOn;

    //Public:DTV-DVB-T
    stMapiDemodulatorFun.DTV_DVB_T_GetLockStatus = DTV_DVB_T_GetLockStatus;

    //Public:DTV-DVB-T2
    stMapiDemodulatorFun.DTV_DVB_T2_GetPlpBitMap = DTV_GetPlpBitMap;
    stMapiDemodulatorFun.DTV_DVB_T2_GetPlpGroupID = DTV_GetPlpGroupID;
    stMapiDemodulatorFun.DTV_DVB_T2_SetPlpGroupID = DTV_SetPlpGroupID;
    stMapiDemodulatorFun.DTV_DVB_T2_GetCurrentPlpId = DTV_Get_Current_Plp_Id;

    //custom
    stMapiDemodulatorFun.DTV_GetSNR_F = DTV_GetSNR_F;
    stMapiDemodulatorFun.DTV_GetLock = MSB1231_Lock;
    stMapiDemodulatorFun.bMSB123X_Ready = FALSE;
    stMapiDemodulatorFun.DTV_DVB_T2_GetSignalTpsInfo = DTV_DVB_T2_GetSignalTpsInfo;
#if (PRELOAD_DSP_CODE_FROM_MAIN_CHIP_I2C == 1)
    int intPTHChk;

    pthread_t pthread_id;
    pthread_attr_t attr1;
    pthread_attr_init(&attr1);
    pthread_attr_setdetachstate(&attr1, PTHREAD_CREATE_DETACHED);

    intPTHChk = PTH_RET_CHK(pthread_create(&pthread_id, &attr1, PreLoadDSPcode, NULL));

    if(intPTHChk != 0)
    {
        ASSERT(0);
    }
#endif

    return &stMapiDemodulatorFun;
}
void DTV_ControlAGCOutput(BOOLEAN bEnable)
{
    bEnable = bEnable;//Not define yet
}