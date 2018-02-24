/*
  Copyright (C) 2011 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4_RegDef.c
 *
 * \date          %modify_time%
 *
 * \author        TVFE SW Group
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA182I4_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template
 *
 * \section info Change Information
 *
*/

/* File generated automatically from register description file */


/*============================================================================*/
/* Standard include files:                                                    */
/*============================================================================*/
#include "tmNxTypes.h"
#include "tmCompId.h"
#include "tmFrontEnd.h"
#include "tmbslFrontEndTypes.h"

/*============================================================================*/
/* Project include files:                                                     */
/*============================================================================*/
#include "tmbslTDA182I4.h"
#include "tmbslTDA182I4_RegDef.h"

/*============================================================================*/
/* Global data:                                                               */
/*============================================================================*/

/* TDA182I4 Register ID_byte_1 0x00 */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_1 = { 0x00, 0x00, 0x08, 0x00 };
/* Master_Not_Slave bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_1__Master_Not_Slave = { 0x00, 0x07, 0x01, 0x00 };
/* Ident_1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_1__Ident_1 = { 0x00, 0x00, 0x07, 0x00 };


/* TDA182I4 Register ID_byte_2 0x01 */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_2 = { 0x01, 0x00, 0x08, 0x00 };
/* Ident_2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_2__Ident_2 = { 0x01, 0x00, 0x08, 0x00 };


/* TDA182I4 Register ID_byte_3 0x02 */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3 = { 0x02, 0x00, 0x08, 0x00 };
/* Major_rev bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3__Major_rev = { 0x02, 0x04, 0x04, 0x00 };
/* Fab_rev bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3__Fab_rev = { 0x02, 0x03, 0x01, 0x00 };
/* Minor_rev bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3__Minor_rev = { 0x02, 0x00, 0x03, 0x00 };


/* TDA182I4 Register Thermo_byte_1 0x03 */
const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_1 = { 0x03, 0x00, 0x08, 0x00 };
/* TM_D bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_1__TM_D = { 0x03, 0x00, 0x07, 0x00 };


/* TDA182I4 Register Thermo_byte_2 0x04 */
const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_2 = { 0x04, 0x00, 0x08, 0x00 };
/* TM_ON bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_2__TM_ON = { 0x04, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Power_state_byte_1 0x05 */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1 = { 0x05, 0x00, 0x08, 0x00 };
/* POR bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__POR = { 0x05, 0x07, 0x01, 0x00 };
/* AGCs_Max bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__AGCs_Max = { 0x05, 0x03, 0x01, 0x00 };
/* AGCs_Lock bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__AGCs_Lock = { 0x05, 0x02, 0x01, 0x00 };
/* Vsync_Lock bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__Vsync_Lock = { 0x05, 0x01, 0x01, 0x00 };
/* LO_Lock bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__LO_Lock = { 0x05, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Power_state_byte_2 0x06 */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_2 = { 0x06, 0x00, 0x08, 0x00 };
/* power_state_mode bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_2__power_state_mode = { 0x06, 0x00, 0x03, 0x00 };


/* TDA182I4 Register Power_Level_byte_1 0x07 */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_1 = { 0x07, 0x00, 0x08, 0x00 };
/* Power_Level_ bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_1__Power_Level_ = { 0x07, 0x00, 0x08, 0x00 };


/* TDA182I4 Register IRQ_status 0x08 */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status = { 0x08, 0x00, 0x08, 0x00 };
/* IRQ_status bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__IRQ_status = { 0x08, 0x07, 0x01, 0x00 };
/* XtalCal_End bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__XtalCal_End = { 0x08, 0x05, 0x01, 0x00 };
/* MSM_RSSI_End bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_RSSI_End = { 0x08, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_End bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_LOCalc_End = { 0x08, 0x03, 0x01, 0x00 };
/* MSMRFCal_End bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSMRFCal_End = { 0x08, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_End bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_IRCAL_End = { 0x08, 0x01, 0x01, 0x00 };
/* MSM_RCCal_End bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_RCCal_End = { 0x08, 0x00, 0x01, 0x00 };


/* TDA182I4 Register IRQ_enable 0x09 */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable = { 0x09, 0x00, 0x08, 0x00 };
/* IRQ_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__IRQ_Enable = { 0x09, 0x07, 0x01, 0x00 };
/* XtalCal_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__XtalCal_Enable = { 0x09, 0x05, 0x01, 0x00 };
/* MSM_RSSI_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_RSSI_Enable = { 0x09, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_LOCalc_Enable = { 0x09, 0x03, 0x01, 0x00 };
/* MSMRFCal_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSMRFCal_Enable = { 0x09, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_IRCAL_Enable = { 0x09, 0x01, 0x01, 0x00 };
/* MSM_RCCal_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_RCCal_Enable = { 0x09, 0x00, 0x01, 0x00 };


/* TDA182I4 Register IRQ_clear 0x0A */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear = { 0x0A, 0x00, 0x08, 0x00 };
/* IRQ_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__IRQ_Clear = { 0x0A, 0x07, 0x01, 0x00 };
/* XtalCal_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__XtalCal_Clear = { 0x0A, 0x05, 0x01, 0x00 };
/* MSM_RSSI_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_RSSI_Clear = { 0x0A, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_LOCalc_Clear = { 0x0A, 0x03, 0x01, 0x00 };
/* MSMRFCal_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSMRFCal_Clear = { 0x0A, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_IRCAL_Clear = { 0x0A, 0x01, 0x01, 0x00 };
/* MSM_RCCal_Clear bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_RCCal_Clear = { 0x0A, 0x00, 0x01, 0x00 };


/* TDA182I4 Register IRQ_set 0x0B */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set = { 0x0B, 0x00, 0x08, 0x00 };
/* IRQ_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__IRQ_Set = { 0x0B, 0x07, 0x01, 0x00 };
/* XtalCal_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__XtalCal_Set = { 0x0B, 0x05, 0x01, 0x00 };
/* MSM_RSSI_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_RSSI_Set = { 0x0B, 0x04, 0x01, 0x00 };
/* MSM_LOCalc_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_LOCalc_Set = { 0x0B, 0x03, 0x01, 0x00 };
/* MSMRFCal_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSMRFCal_Set = { 0x0B, 0x02, 0x01, 0x00 };
/* MSM_IRCAL_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_IRCAL_Set = { 0x0B, 0x01, 0x01, 0x00 };
/* MSM_RCCal_Set bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_RCCal_Set = { 0x0B, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Gpio_ctrl_byte 0x0C */
const TDA182I4_BitField_t gTDA182I4_Reg_Gpio_ctrl_byte = { 0x0C, 0x00, 0x08, 0x00 };
/* GPIO2 bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Gpio_ctrl_byte__GPIO2 = { 0x0C, 0x01, 0x01, 0x00 };
/* GPIO1 bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Gpio_ctrl_byte__GPIO1 = { 0x0C, 0x00, 0x01, 0x00 };


/* TDA182I4 Register AGC1_byte_1 0x0D */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1 = { 0x0D, 0x00, 0x08, 0x00 };
/* PD_LNA bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1__PD_LNA = { 0x0D, 0x07, 0x01, 0x00 };
/* AGC1_Top_Strategy bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1__AGC1_Top_Strategy = { 0x0D, 0x04, 0x03, 0x00 };
/* AGC1_Top bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1__AGC1_Top = { 0x0D, 0x00, 0x03, 0x00 };


/* TDA182I4 Register AGC1_byte_2 0x0E */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2 = { 0x0E, 0x00, 0x08, 0x00 };
/* AGC1_FastStbyLT_Enable bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable = { 0x0E, 0x05, 0x01, 0x00 };
/* LNA_Zin bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__LNA_Zin = { 0x0E, 0x04, 0x01, 0x00 };
/* AGC1_Vsync_Enable bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__AGC1_Vsync_Enable = { 0x0E, 0x03, 0x01, 0x00 };
/* AGC1_cc_freeze bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__AGC1_cc_freeze = { 0x0E, 0x02, 0x01, 0x00 };
/* LNA_Range bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__LNA_Range = { 0x0E, 0x00, 0x02, 0x00 };


/* TDA182I4 Register AGC2_byte_1 0x0F */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1 = { 0x0F, 0x00, 0x08, 0x00 };
/* AGCs_Do_Step_asym bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1__AGCs_Do_Step_asym = { 0x0F, 0x06, 0x02, 0x00 };
/* AGCs_Up_step bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1__AGCs_Up_step = { 0x0F, 0x04, 0x02, 0x00 };
/* AGC2_TOP bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1__AGC2_TOP = { 0x0F, 0x00, 0x03, 0x00 };


/* TDA182I4 Register AGCK_byte_1 0x10 */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1 = { 0x10, 0x00, 0x08, 0x00 };
/* AGCs_Up_Step_asym bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__AGCs_Up_Step_asym = { 0x10, 0x06, 0x02, 0x00 };
/* Pulse_Shaper_Disable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__Pulse_Shaper_Disable = { 0x10, 0x04, 0x01, 0x00 };
/* AGCK_Step bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__AGCK_Step = { 0x10, 0x02, 0x02, 0x00 };
/* AGCK_Mode bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__AGCK_Mode = { 0x10, 0x00, 0x02, 0x00 };


/* TDA182I4 Register RF_AGC_byte_1 0x11 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1 = { 0x11, 0x00, 0x08, 0x00 };
/* PD_AGC_Adapt35 bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__PD_AGC_Adapt35 = { 0x11, 0x07, 0x01, 0x00 };
/* PD_AGC_Adapt34 bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__PD_AGC_Adapt34 = { 0x11, 0x06, 0x01, 0x00 };
/* RFAGC_Adapt_TOP bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Adapt_TOP = { 0x11, 0x04, 0x02, 0x00 };
/* RFAGC_Low_BW bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Low_BW = { 0x11, 0x03, 0x01, 0x00 };
/* RFAGC_Top bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Top = { 0x11, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RF_AGC_byte_2 0x12 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2 = { 0x12, 0x00, 0x08, 0x00 };
/* RFAGC_Peak_Val bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_Peak_Val = { 0x12, 0x04, 0x04, 0x00 };
/* RFAGC_Adapt_TOP_ovld bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_Adapt_TOP_ovld = { 0x12, 0x02, 0x02, 0x00 };
/* RFAGC_det_mode bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_det_mode = { 0x12, 0x00, 0x02, 0x00 };


/* TDA182I4 Register RF_AGC_byte_3 0x13 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3 = { 0x13, 0x00, 0x08, 0x00 };
/* RFAGC_Ovld_window_size bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_window_size = { 0x13, 0x06, 0x02, 0x00 };
/* RFAGC_Ovld_Tcst bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_Tcst = { 0x13, 0x04, 0x02, 0x00 };
/* RFAGC_Ovld_nb bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_nb = { 0x13, 0x00, 0x04, 0x00 };


/* TDA182I4 Register W_Filter_byte 0x14 */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte = { 0x14, 0x00, 0x08, 0x00 };
/* VHF_III_mode bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__VHF_III_mode = { 0x14, 0x07, 0x01, 0x00 };
/* RF_Atten_3dB bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__RF_Atten_3dB = { 0x14, 0x06, 0x01, 0x00 };
/* W_Filter_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter_Enable = { 0x14, 0x05, 0x01, 0x00 };
/* W_Filter_Bypass bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter_Bypass = { 0x14, 0x04, 0x01, 0x00 };
/* W_Filter bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter = { 0x14, 0x02, 0x02, 0x00 };
/* W_Filter_Offset bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter_Offset = { 0x14, 0x00, 0x02, 0x00 };


/* TDA182I4 Register IR_Mixer_byte_1 0x15 */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_1 = { 0x15, 0x00, 0x08, 0x00 };
/* S2D_Gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_1__S2D_Gain = { 0x15, 0x04, 0x02, 0x00 };
/* IR_Mixer_Top bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_1__IR_Mixer_Top = { 0x15, 0x00, 0x04, 0x00 };


/* TDA182I4 Register AGC5_byte_1 0x16 */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1 = { 0x16, 0x00, 0x08, 0x00 };
/* RSSI_HP_Fc bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1__RSSI_HP_Fc = { 0x16, 0x06, 0x02, 0x00 };
/* AGC5_HP_Fc bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1__AGC5_HP_Fc = { 0x16, 0x04, 0x02, 0x00 };
/* AGC5_TOP bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1__AGC5_TOP = { 0x16, 0x00, 0x04, 0x00 };


/* TDA182I4 Register IF_AGC_byte 0x17 */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte = { 0x17, 0x00, 0x08, 0x00 };
/* IFnotchToRSSI bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte__IFnotchToRSSI = { 0x17, 0x07, 0x01, 0x00 };
/* LPF_DCOffset_Corr bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte__LPF_DCOffset_Corr = { 0x17, 0x06, 0x01, 0x00 };
/* IF_level bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte__IF_level = { 0x17, 0x00, 0x03, 0x00 };


/* TDA182I4 Register IF_Byte_1 0x18 */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1 = { 0x18, 0x00, 0x08, 0x00 };
/* IF_LPF_Offset bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1__IF_LPF_Offset = { 0x18, 0x05, 0x02, 0x00 };
/* IF_LPF_sign bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1__IF_LPF_sign = { 0x18, 0x04, 0x01, 0x00 };
/* LP_Fc bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1__LP_Fc = { 0x18, 0x00, 0x03, 0x00 };


/* TDA182I4 Register IF_Byte_2 0x19 */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2 = { 0x19, 0x00, 0x08, 0x00 };
/* IF_HPF_Offset bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HPF_Offset = { 0x19, 0x05, 0x02, 0x00 };
/* IF_HPF_sign bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HPF_sign = { 0x19, 0x04, 0x01, 0x00 };
/* IF_HP_Fc bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HP_Fc = { 0x19, 0x01, 0x03, 0x00 };
/* IF_HP_Enable bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HP_Enable = { 0x19, 0x00, 0x01, 0x00 };


/* TDA182I4 Register IF_Byte_3 0x1A */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3 = { 0x1A, 0x00, 0x08, 0x00 };
/* IF_Notch_Offset bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_Offset = { 0x1A, 0x05, 0x02, 0x00 };
/* IF_Notch_sign bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_sign = { 0x1A, 0x04, 0x01, 0x00 };
/* IF_Notch_Freq bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_Freq = { 0x1A, 0x01, 0x03, 0x00 };
/* IF_Notch_Enable bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_Enable = { 0x1A, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Reference_Byte 0x1B */
const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte = { 0x1B, 0x00, 0x08, 0x00 };
/* Dig_Clock bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte__Dig_Clock = { 0x1B, 0x06, 0x02, 0x00 };
/* Xtout_Amp bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte__Xtout_Amp = { 0x1B, 0x02, 0x01, 0x00 };
/* XTout bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte__XTout = { 0x1B, 0x00, 0x02, 0x00 };


/* TDA182I4 Register IF_Frequency_byte 0x1C */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Frequency_byte = { 0x1C, 0x00, 0x08, 0x00 };
/* IF_Freq bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IF_Frequency_byte__IF_Freq = { 0x1C, 0x00, 0x08, 0x00 };


/* TDA182I4 Register smooth_cc_byte_1 0x1D */
const TDA182I4_BitField_t gTDA182I4_Reg_smooth_cc_byte_1 = { 0x1D, 0x00, 0x08, 0x00 };
/* smooth_cc bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_smooth_cc_byte_1__smooth_cc = { 0x1D, 0x04, 0x01, 0x00 };
/* switch_smooth_t_cst bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_smooth_cc_byte_1__switch_smooth_t_cst = { 0x1D, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RF_Frequency_byte_1 0x1E */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_1 = { 0x1E, 0x00, 0x08, 0x00 };
/* RF_Freq_1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_1__RF_Freq_1 = { 0x1E, 0x00, 0x04, 0x00 };


/* TDA182I4 Register RF_Frequency_byte_2 0x1F */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_2 = { 0x1F, 0x00, 0x08, 0x00 };
/* RF_Freq_2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_2__RF_Freq_2 = { 0x1F, 0x00, 0x08, 0x00 };


/* TDA182I4 Register RF_Frequency_byte_3 0x20 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_3 = { 0x20, 0x00, 0x08, 0x00 };
/* RF_Freq_3 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_3__RF_Freq_3 = { 0x20, 0x00, 0x08, 0x00 };


/* TDA182I4 Register MSM_byte_1 0x21 */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1 = { 0x21, 0x00, 0x08, 0x00 };
/* RSSI_Meas bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RSSI_Meas = { 0x21, 0x07, 0x01, 0x00 };
/* IR_CAL_Loop bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__IR_CAL_Loop = { 0x21, 0x06, 0x01, 0x00 };
/* IR_Cal_Image bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__IR_Cal_Image = { 0x21, 0x05, 0x01, 0x00 };
/* IR_CAL_Wanted bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__IR_CAL_Wanted = { 0x21, 0x04, 0x01, 0x00 };
/* RF_CAL_AV bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RF_CAL_AV = { 0x21, 0x03, 0x01, 0x00 };
/* RF_CAL bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RF_CAL = { 0x21, 0x02, 0x01, 0x00 };
/* RC_Cal bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RC_Cal = { 0x21, 0x01, 0x01, 0x00 };
/* Calc_PLL bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__Calc_PLL = { 0x21, 0x00, 0x01, 0x00 };


/* TDA182I4 Register MSM_byte_2 0x22 */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_2 = { 0x22, 0x00, 0x08, 0x00 };
/* XtalCal_Launch bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_2__XtalCal_Launch = { 0x22, 0x01, 0x01, 0x00 };
/* MSM_Launch bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_2__MSM_Launch = { 0x22, 0x00, 0x01, 0x00 };


/* TDA182I4 Register PowerSavingMode_byte_1 0x23 */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1 = { 0x23, 0x00, 0x08, 0x00 };
/* AGC1_boost bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__AGC1_boost = { 0x23, 0x06, 0x02, 0x00 };
/* PSM_IM2_Filter bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_IM2_Filter = { 0x23, 0x04, 0x02, 0x00 };
/* PSM_RF_BUF_LTO bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_RF_BUF_LTO = { 0x23, 0x02, 0x02, 0x00 };
/* PSM_RFfilter bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_RFfilter = { 0x23, 0x00, 0x02, 0x00 };


/* TDA182I4 Register PowerSavingMode_byte_2 0x24 */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2 = { 0x24, 0x00, 0x08, 0x00 };
/* PSM_VCO bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_VCO = { 0x24, 0x06, 0x02, 0x00 };
/* PSM_IFfilter bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_IFfilter = { 0x24, 0x04, 0x02, 0x00 };
/* PSM_IFLPF bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_IFLPF = { 0x24, 0x02, 0x02, 0x00 };
/* PSM_H3H5 bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_H3H5 = { 0x24, 0x00, 0x02, 0x00 };


/* TDA182I4 Register PowerSavingMode_byte_3 0x25 */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3 = { 0x25, 0x00, 0x08, 0x00 };
/* PSM_RFpoly bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_RFpoly = { 0x25, 0x06, 0x02, 0x00 };
/* PSM_Mixer bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_Mixer = { 0x25, 0x04, 0x02, 0x00 };
/* PSM_Ifpoly bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_Ifpoly = { 0x25, 0x02, 0x02, 0x00 };
/* PSM_Lodriver bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_Lodriver = { 0x25, 0x00, 0x02, 0x00 };


/* TDA182I4 Register PowerSavingMode_byte_4 0x26 */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_4 = { 0x26, 0x00, 0x08, 0x00 };
/* PSM_DCC bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_4__PSM_DCC = { 0x26, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Power_Level_byte_2 0x27 */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2 = { 0x27, 0x00, 0x08, 0x00 };
/* PD_PLD_read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2__PD_PLD_read = { 0x27, 0x07, 0x01, 0x00 };
/* PLD_Temp_Slope bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2__PLD_Temp_Slope = { 0x27, 0x05, 0x02, 0x00 };
/* PLD_Gain_Corr bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2__PLD_Gain_Corr = { 0x27, 0x00, 0x05, 0x00 };


/* TDA182I4 Register Adapt_Top_byte 0x28 */
const TDA182I4_BitField_t gTDA182I4_Reg_Adapt_Top_byte = { 0x28, 0x00, 0x08, 0x00 };
/* Fast_Mode_AGC bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Adapt_Top_byte__Fast_Mode_AGC = { 0x28, 0x06, 0x01, 0x00 };
/* Ovld_Udld_FastUp bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Adapt_Top_byte__Ovld_Udld_FastUp = { 0x28, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Vsync_byte 0x29 */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte = { 0x29, 0x00, 0x08, 0x00 };
/* Neg_Modulation bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Neg_Modulation = { 0x29, 0x07, 0x01, 0x00 };
/* Tracer_Step bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Tracer_Step = { 0x29, 0x05, 0x02, 0x00 };
/* vsync_Int bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__vsync_Int = { 0x29, 0x04, 0x01, 0x00 };
/* Vsync_Thresh bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Vsync_Thresh = { 0x29, 0x02, 0x02, 0x00 };
/* Vsync_Len bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Vsync_Len = { 0x29, 0x00, 0x02, 0x00 };


/* TDA182I4 Register Vsync_Mgt_byte 0x2A */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte = { 0x2A, 0x00, 0x08, 0x00 };
/* PD_Vsync_Mgt bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Vsync_Mgt = { 0x2A, 0x07, 0x01, 0x00 };
/* PD_Ovld bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld = { 0x2A, 0x06, 0x01, 0x00 };
/* PD_Ovld_RF bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld_RF = { 0x2A, 0x05, 0x01, 0x00 };
/* PD_Udld bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Udld = { 0x2A, 0x04, 0x01, 0x00 };
/* AGC_Ovld_TOP bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__AGC_Ovld_TOP = { 0x2A, 0x01, 0x03, 0x00 };
/* AGC_Ovld_Timer bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__AGC_Ovld_Timer = { 0x2A, 0x00, 0x01, 0x00 };


/* TDA182I4 Register IR_Mixer_byte_2 0x2B */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2 = { 0x2B, 0x00, 0x08, 0x00 };
/* IR_Mixer_loop_off bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2__IR_Mixer_loop_off = { 0x2B, 0x07, 0x01, 0x00 };
/* IR_Mixer_Do_step bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2__IR_Mixer_Do_step = { 0x2B, 0x05, 0x02, 0x00 };
/* DC_Notch bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2__DC_Notch = { 0x2B, 0x00, 0x01, 0x00 };


/* TDA182I4 Register LT_byte_1 0x2C */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1 = { 0x2C, 0x00, 0x08, 0x00 };
/* PD_LT bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__PD_LT = { 0x2C, 0x07, 0x01, 0x00 };
/* PD_RF_BUF_LTO bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__PD_RF_BUF_LTO = { 0x2C, 0x06, 0x01, 0x00 };
/* Force_LT_gain bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__Force_LT_gain = { 0x2C, 0x04, 0x01, 0x00 };
/* LT_Gain bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__LT_Gain = { 0x2C, 0x00, 0x03, 0x00 };


/* TDA182I4 Register LT_byte_2 0x2D */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_2 = { 0x2D, 0x00, 0x08, 0x00 };
/* LT_smooth_t_cst_fast bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst_fast = { 0x2D, 0x03, 0x03, 0x00 };
/* LT_smooth_t_cst bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst = { 0x2D, 0x00, 0x03, 0x00 };


/* TDA182I4 Register AGC1_byte_3 0x2E */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3 = { 0x2E, 0x00, 0x08, 0x00 };
/* AGC1_loop_off bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__AGC1_loop_off = { 0x2E, 0x07, 0x01, 0x00 };
/* AGC1_Do_step bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__AGC1_Do_step = { 0x2E, 0x05, 0x02, 0x00 };
/* Force_AGC1_gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__Force_AGC1_gain = { 0x2E, 0x04, 0x01, 0x00 };
/* AGC1_Gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__AGC1_Gain = { 0x2E, 0x00, 0x04, 0x00 };


/* TDA182I4 Register AGC1_byte_4 0x2F */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4 = { 0x2F, 0x00, 0x08, 0x00 };
/* AGC1_rst_do_enable bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_rst_do_enable = { 0x2F, 0x07, 0x01, 0x00 };
/* AGC1_rst_up_enable bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_rst_up_enable = { 0x2F, 0x06, 0x01, 0x00 };
/* AGC1_smooth_t_cst_fast bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst_fast = { 0x2F, 0x03, 0x03, 0x00 };
/* AGC1_smooth_t_cst bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst = { 0x2F, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RFAGCs_Gain_byte_1 0x30 */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1 = { 0x30, 0x00, 0x08, 0x00 };
/* PLD_DAC_Scale bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__PLD_DAC_Scale = { 0x30, 0x07, 0x01, 0x00 };
/* PLD_CC_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable = { 0x30, 0x06, 0x01, 0x00 };
/* PLD_Temp_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__PLD_Temp_Enable = { 0x30, 0x05, 0x01, 0x00 };
/* TH_AGC_Adapt34 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__TH_AGC_Adapt34 = { 0x30, 0x04, 0x01, 0x00 };
/* RFAGC_Sense_Enable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__RFAGC_Sense_Enable = { 0x30, 0x02, 0x01, 0x00 };
/* RFAGC_K_Bypass bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__RFAGC_K_Bypass = { 0x30, 0x01, 0x01, 0x00 };
/* RFAGC_K_8 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__RFAGC_K_8 = { 0x30, 0x00, 0x01, 0x00 };


/* TDA182I4 Register RFAGCs_Gain_byte_2 0x31 */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_2 = { 0x31, 0x00, 0x08, 0x00 };
/* RFAGC_K bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_2__RFAGC_K = { 0x31, 0x00, 0x08, 0x00 };


/* TDA182I4 Register AGC5_byte_2 0x32 */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2 = { 0x32, 0x00, 0x08, 0x00 };
/* AGC5_loop_off bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__AGC5_loop_off = { 0x32, 0x07, 0x01, 0x00 };
/* AGC5_Do_step bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__AGC5_Do_step = { 0x32, 0x05, 0x02, 0x00 };
/* Force_AGC5_gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__Force_AGC5_gain = { 0x32, 0x03, 0x01, 0x00 };
/* AGC5_Gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__AGC5_Gain = { 0x32, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RF_Cal_byte_1 0x33 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1 = { 0x33, 0x00, 0x08, 0x00 };
/* RFCAL_Offset_Cprog0 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog0 = { 0x33, 0x06, 0x02, 0x00 };
/* RFCAL_Offset_Cprog1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog1 = { 0x33, 0x04, 0x02, 0x00 };
/* RFCAL_Offset_Cprog2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog2 = { 0x33, 0x02, 0x02, 0x00 };
/* RFCAL_Offset_Cprog3 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog3 = { 0x33, 0x00, 0x02, 0x00 };


/* TDA182I4 Register RF_Cal_byte_2 0x34 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2 = { 0x34, 0x00, 0x08, 0x00 };
/* RFCAL_Offset_Cprog4 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog4 = { 0x34, 0x06, 0x02, 0x00 };
/* RFCAL_Offset_Cprog5 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog5 = { 0x34, 0x04, 0x02, 0x00 };
/* RFCAL_Offset_Cprog6 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog6 = { 0x34, 0x02, 0x02, 0x00 };
/* RFCAL_Offset_Cprog7 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog7 = { 0x34, 0x00, 0x02, 0x00 };


/* TDA182I4 Register RF_Cal_byte_3 0x35 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3 = { 0x35, 0x00, 0x08, 0x00 };
/* RFCAL_Offset_Cprog8 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog8 = { 0x35, 0x06, 0x02, 0x00 };
/* RFCAL_Offset_Cprog9 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog9 = { 0x35, 0x04, 0x02, 0x00 };
/* RFCAL_Offset_Cprog10 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog10 = { 0x35, 0x02, 0x02, 0x00 };
/* RFCAL_Offset_Cprog11 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog11 = { 0x35, 0x00, 0x02, 0x00 };


/* TDA182I4 Register Bandsplit_Filter_byte 0x36 */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte = { 0x36, 0x00, 0x08, 0x00 };
/* IM2_Filter_Bypass bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_Filter_Bypass = { 0x36, 0x07, 0x01, 0x00 };
/* IM2_LPF_Fc bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_LPF_Fc = { 0x36, 0x05, 0x02, 0x00 };
/* IM2_HPF_Fc bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_HPF_Fc = { 0x36, 0x04, 0x01, 0x00 };
/* IM2_LPF_PD bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_LPF_PD = { 0x36, 0x03, 0x01, 0x00 };
/* IM2_HPF_PD bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_HPF_PD = { 0x36, 0x02, 0x01, 0x00 };
/* IM2_Filter_SubBand bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_Filter_SubBand = { 0x36, 0x00, 0x02, 0x00 };


/* TDA182I4 Register RF_Filters_byte_1 0x37 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1 = { 0x37, 0x00, 0x08, 0x00 };
/* RF_Filter_Bypass bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__RF_Filter_Bypass = { 0x37, 0x07, 0x01, 0x00 };
/* AGC2_loop_off bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__AGC2_loop_off = { 0x37, 0x05, 0x01, 0x00 };
/* Force_AGC2_gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__Force_AGC2_gain = { 0x37, 0x04, 0x01, 0x00 };
/* RF_Filter_Gv bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__RF_Filter_Gv = { 0x37, 0x02, 0x02, 0x00 };
/* RF_Filter_Band bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__RF_Filter_Band = { 0x37, 0x00, 0x02, 0x00 };


/* TDA182I4 Register RF_Filters_byte_2 0x38 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_2 = { 0x38, 0x00, 0x08, 0x00 };
/* RF_Filter_Cap bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_2__RF_Filter_Cap = { 0x38, 0x00, 0x08, 0x00 };


/* TDA182I4 Register RF_Filters_byte_3 0x39 */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_3 = { 0x39, 0x00, 0x08, 0x00 };
/* AGC2_Do_step bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_3__AGC2_Do_step = { 0x39, 0x06, 0x02, 0x00 };
/* Gain_Taper bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_3__Gain_Taper = { 0x39, 0x00, 0x06, 0x00 };


/* TDA182I4 Register RF_Band_Pass_Filter_byte 0x3A */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Band_Pass_Filter_byte = { 0x3A, 0x00, 0x08, 0x00 };
/* RF_BPF_Bypass bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Band_Pass_Filter_byte__RF_BPF_Bypass = { 0x3A, 0x07, 0x01, 0x00 };
/* RF_BPF bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RF_Band_Pass_Filter_byte__RF_BPF = { 0x3A, 0x00, 0x03, 0x00 };


/* TDA182I4 Register AGCs_DetOut_byte 0x3B */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte = { 0x3B, 0x00, 0x08, 0x00 };
/* Up_AGC5 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC5 = { 0x3B, 0x07, 0x01, 0x00 };
/* Do_AGC5 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC5 = { 0x3B, 0x06, 0x01, 0x00 };
/* Up_AGC4 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC4 = { 0x3B, 0x05, 0x01, 0x00 };
/* Do_AGC4 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC4 = { 0x3B, 0x04, 0x01, 0x00 };
/* Up_AGC2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC2 = { 0x3B, 0x03, 0x01, 0x00 };
/* Do_AGC2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC2 = { 0x3B, 0x02, 0x01, 0x00 };
/* Up_AGC1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC1 = { 0x3B, 0x01, 0x01, 0x00 };
/* Do_AGC1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC1 = { 0x3B, 0x00, 0x01, 0x00 };


/* TDA182I4 Register AGC1_Top_byte 0x3C */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte = { 0x3C, 0x00, 0x08, 0x00 };
/* AGC1_Smooth_Transition_ON bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte__AGC1_Smooth_Transition_ON = { 0x3C, 0x07, 0x01, 0x00 };
/* AGC1_Top_Do_Read bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte__AGC1_Top_Do_Read = { 0x3C, 0x04, 0x03, 0x00 };
/* AGC1_Top_Up_Read bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte__AGC1_Top_Up_Read = { 0x3C, 0x00, 0x03, 0x00 };


/* TDA182I4 Register LT_Gain_byte_1 0x3D */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_Gain_byte_1 = { 0x3D, 0x00, 0x08, 0x00 };
/* LT_Gain_Read bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_LT_Gain_byte_1__LT_Gain_Read = { 0x3D, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RFAGCs_Gain_byte_3 0x3E */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_3 = { 0x3E, 0x00, 0x08, 0x00 };
/* AGC2_Gain_Read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_3__AGC2_Gain_Read = { 0x3E, 0x04, 0x02, 0x00 };
/* AGC1_Gain_Read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_3__AGC1_Gain_Read = { 0x3E, 0x00, 0x04, 0x00 };


/* TDA182I4 Register RFAGCs_Gain_byte_4 0x3F */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_4 = { 0x3F, 0x00, 0x08, 0x00 };
/* Cprog_Read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_4__Cprog_Read = { 0x3F, 0x00, 0x08, 0x00 };


/* TDA182I4 Register RFAGCs_Gain_byte_5 0x40 */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5 = { 0x40, 0x00, 0x08, 0x00 };
/* RFAGC_Read_K_8 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__RFAGC_Read_K_8 = { 0x40, 0x07, 0x01, 0x00 };
/* Do_AGC1bis bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__Do_AGC1bis = { 0x40, 0x06, 0x01, 0x00 };
/* Do_AGC3_Peak bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__Do_AGC3_Peak = { 0x40, 0x03, 0x01, 0x00 };
/* TOP_Agc3_read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__TOP_Agc3_read = { 0x40, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RFAGCs_Gain_byte_6 0x41 */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_6 = { 0x41, 0x00, 0x08, 0x00 };
/* RFAGC_Read_K bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_6__RFAGC_Read_K = { 0x41, 0x00, 0x08, 0x00 };


/* TDA182I4 Register IFAGCs_Gain_byte 0x42 */
const TDA182I4_BitField_t gTDA182I4_Reg_IFAGCs_Gain_byte = { 0x42, 0x00, 0x08, 0x00 };
/* AGC5_Gain_Read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IFAGCs_Gain_byte__AGC5_Gain_Read = { 0x42, 0x03, 0x03, 0x00 };
/* AGC4_Gain_Read bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IFAGCs_Gain_byte__AGC4_Gain_Read = { 0x42, 0x00, 0x03, 0x00 };


/* TDA182I4 Register RSSI_byte_1 0x43 */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_1 = { 0x43, 0x00, 0x08, 0x00 };
/* RSSI bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_1__RSSI = { 0x43, 0x00, 0x08, 0x00 };


/* TDA182I4 Register RSSI_byte_2 0x44 */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2 = { 0x44, 0x00, 0x08, 0x00 };
/* RSSI_AV bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_AV = { 0x44, 0x05, 0x01, 0x00 };
/* RSSI_Cap_Reset_En bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Cap_Reset_En = { 0x44, 0x03, 0x01, 0x00 };
/* RSSI_Cap_Val bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Cap_Val = { 0x44, 0x02, 0x01, 0x00 };
/* RSSI_Ck_Speed bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Ck_Speed = { 0x44, 0x01, 0x01, 0x00 };
/* RSSI_Dicho_not bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Dicho_not = { 0x44, 0x00, 0x01, 0x00 };


/* TDA182I4 Register IRQ_Ctrl_byte 0x45 */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte = { 0x45, 0x00, 0x08, 0x00 };
/* DDS_Polarity bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte__DDS_Polarity = { 0x45, 0x04, 0x01, 0x00 };
/* IRQ_Mode bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte__IRQ_Mode = { 0x45, 0x01, 0x01, 0x00 };
/* IRQ_Polarity bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte__IRQ_Polarity = { 0x45, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Dummy_byte 0x46 */
const TDA182I4_BitField_t gTDA182I4_Reg_Dummy_byte = { 0x46, 0x00, 0x08, 0x00 };
/* Dummy bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Dummy_byte__Dummy = { 0x46, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_0 0x47 */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_0 = { 0x47, 0x00, 0x08, 0x00 };
/* rfcal_log_0 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_0__rfcal_log_0 = { 0x47, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_1 0x48 */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_1 = { 0x48, 0x00, 0x08, 0x00 };
/* rfcal_log_1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_1__rfcal_log_1 = { 0x48, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_2 0x49 */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_2 = { 0x49, 0x00, 0x08, 0x00 };
/* rfcal_log_2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_2__rfcal_log_2 = { 0x49, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_3 0x4A */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_3 = { 0x4A, 0x00, 0x08, 0x00 };
/* rfcal_log_3 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_3__rfcal_log_3 = { 0x4A, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_4 0x4B */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_4 = { 0x4B, 0x00, 0x08, 0x00 };
/* rfcal_log_4 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_4__rfcal_log_4 = { 0x4B, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_5 0x4C */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_5 = { 0x4C, 0x00, 0x08, 0x00 };
/* rfcal_log_5 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_5__rfcal_log_5 = { 0x4C, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_6 0x4D */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_6 = { 0x4D, 0x00, 0x08, 0x00 };
/* rfcal_log_6 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_6__rfcal_log_6 = { 0x4D, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_7 0x4E */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_7 = { 0x4E, 0x00, 0x08, 0x00 };
/* rfcal_log_7 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_7__rfcal_log_7 = { 0x4E, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_8 0x4F */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_8 = { 0x4F, 0x00, 0x08, 0x00 };
/* rfcal_log_8 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_8__rfcal_log_8 = { 0x4F, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_9 0x50 */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_9 = { 0x50, 0x00, 0x08, 0x00 };
/* rfcal_log_9 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_9__rfcal_log_9 = { 0x50, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_10 0x51 */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_10 = { 0x51, 0x00, 0x08, 0x00 };
/* rfcal_log_10 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_10__rfcal_log_10 = { 0x51, 0x00, 0x08, 0x00 };


/* TDA182I4 Register rfcal_log_11 0x52 */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_11 = { 0x52, 0x00, 0x08, 0x00 };
/* rfcal_log_11 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_11__rfcal_log_11 = { 0x52, 0x00, 0x08, 0x00 };


/* TDA182I4 Register Main_Post_Divider_byte 0x5B */
const TDA182I4_BitField_t gTDA182I4_Reg_Main_Post_Divider_byte = { 0x5B, 0x00, 0x08, 0x00 };
/* LOPostDiv bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Main_Post_Divider_byte__LOPostDiv = { 0x5B, 0x04, 0x03, 0x00 };
/* LOPresc bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Main_Post_Divider_byte__LOPresc = { 0x5B, 0x00, 0x04, 0x00 };


/* TDA182I4 Register Sigma_delta_byte_1 0x5C */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_1 = { 0x5C, 0x00, 0x08, 0x00 };
/* LO_Int bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_1__LO_Int = { 0x5C, 0x00, 0x07, 0x00 };


/* TDA182I4 Register Sigma_delta_byte_2 0x5D */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_2 = { 0x5D, 0x00, 0x08, 0x00 };
/* LO_Frac_2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_2__LO_Frac_2 = { 0x5D, 0x00, 0x07, 0x00 };


/* TDA182I4 Register Sigma_delta_byte_3 0x5E */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_3 = { 0x5E, 0x00, 0x08, 0x00 };
/* LO_Frac_1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_3__LO_Frac_1 = { 0x5E, 0x00, 0x08, 0x00 };


/* TDA182I4 Register Sigma_delta_byte_4 0x5F */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_4 = { 0x5F, 0x00, 0x08, 0x00 };
/* LO_Frac_0 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_4__LO_Frac_0 = { 0x5F, 0x00, 0x08, 0x00 };


/* TDA182I4 Register Sigma_delta_byte_5 0x60 */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5 = { 0x60, 0x00, 0x08, 0x00 };
/* LO_SetAll bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5__LO_SetAll = { 0x60, 0x02, 0x02, 0x00 };
/* N_K_correct_manual bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual = { 0x60, 0x01, 0x01, 0x00 };
/* LO_Calc_Disable bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable = { 0x60, 0x00, 0x01, 0x00 };


/* TDA182I4 Register RC_Cal_byte_1 0x66 */
const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1 = { 0x66, 0x00, 0x08, 0x00 };
/* RC_Cal_bypass bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_bypass = { 0x66, 0x07, 0x01, 0x00 };
/* RC_Cal_Offset bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_Offset = { 0x66, 0x05, 0x02, 0x00 };
/* RC_Cal_force bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_force = { 0x66, 0x00, 0x05, 0x00 };


/* TDA182I4 Register IR_Cal_byte_5 0x69 */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5 = { 0x69, 0x00, 0x08, 0x00 };
/* Mixer_Gain_Bypass bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__Mixer_Gain_Bypass = { 0x69, 0x07, 0x01, 0x00 };
/* IR_Mixer_Gain bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__IR_Mixer_Gain = { 0x69, 0x04, 0x03, 0x00 };
/* IR_FreqPtr bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__IR_FreqPtr = { 0x69, 0x02, 0x02, 0x00 };
/* IR_RxPtr bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__IR_RxPtr = { 0x69, 0x00, 0x02, 0x00 };


/* TDA182I4 Register IR_Cal_byte_6 0x6A */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6 = { 0x6A, 0x00, 0x08, 0x00 };
/* Rx_Force bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6__Rx_Force = { 0x6A, 0x07, 0x01, 0x00 };
/* IR_target bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6__IR_target = { 0x6A, 0x05, 0x02, 0x00 };
/* Rx_bp bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6__Rx_bp = { 0x6A, 0x00, 0x05, 0x00 };


/* TDA182I4 Register Power_Down_byte_1 0x6C */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1 = { 0x6C, 0x00, 0x08, 0x00 };
/* S2B_Dcboost bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__S2B_Dcboost = { 0x6C, 0x06, 0x02, 0x00 };
/* PD_Lotest bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__PD_Lotest = { 0x6C, 0x02, 0x01, 0x00 };
/* PD_Synthe bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__PD_Synthe = { 0x6C, 0x01, 0x01, 0x00 };
/* PD_VCO bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__PD_VCO = { 0x6C, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Power_Down_byte_2 0x6D */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2 = { 0x6D, 0x00, 0x08, 0x00 };
/* PDRF_filter bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PDRF_filter = { 0x6D, 0x06, 0x01, 0x00 };
/* PD_STOB_IF bit(s):  */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_STOB_IF = { 0x6D, 0x05, 0x01, 0x00 };
/* PD_Det5 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det5 = { 0x6D, 0x04, 0x01, 0x00 };
/* PD_Det4 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det4 = { 0x6D, 0x03, 0x01, 0x00 };
/* PD_Det3 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det3 = { 0x6D, 0x02, 0x01, 0x00 };
/* PD_Det2 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det2 = { 0x6D, 0x01, 0x01, 0x00 };
/* PD_Det1 bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det1 = { 0x6D, 0x00, 0x01, 0x00 };


/* TDA182I4 Register Charge_pump_byte 0x71 */
const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte = { 0x71, 0x00, 0x08, 0x00 };
/* ICP_Force_Sink bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP_Force_Sink = { 0x71, 0x05, 0x01, 0x00 };
/* ICP_Force_Src bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP_Force_Src = { 0x71, 0x04, 0x01, 0x00 };
/* ICP_offset bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP_offset = { 0x71, 0x02, 0x02, 0x00 };
/* ICP bit(s): ??? */
const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP = { 0x71, 0x00, 0x02, 0x00 };


