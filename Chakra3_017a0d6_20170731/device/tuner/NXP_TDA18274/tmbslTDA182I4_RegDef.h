/*
  Copyright (C) 2011 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4_RegDef.h
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


#pragma once
#ifndef _TMBSL_TDA182I4_REGDEF_H
#define _TMBSL_TDA182I4_REGDEF_H

#ifdef __cplusplus
extern "C"
{
#endif


/*============================================================================*/
/* Registers definitions:                                                     */
/*============================================================================*/

#define TDA182I4_REG_ADD_SZ                             (0x01)
#define TDA182I4_REG_DATA_MAX_SZ                        (0x01)
#define TDA182I4_REG_MAP_NB_BYTES                       (0x7E)

#define TDA182I4_REG_DATA_LEN(_FIRST_REG, _LAST_REG)    ( (_LAST_REG.Address - _FIRST_REG.Address) + 1)

/* TDA182I4 Register ID_byte_1 0x00 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_1;
/* Master_Not_Slave bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_1__Master_Not_Slave;
/* Ident_1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_1__Ident_1;


/* TDA182I4 Register ID_byte_2 0x01 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_2;
/* Ident_2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_2__Ident_2;


/* TDA182I4 Register ID_byte_3 0x02 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3;
/* Major_rev bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3__Major_rev;
/* Fab_rev bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3__Fab_rev;
/* Minor_rev bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_ID_byte_3__Minor_rev;


/* TDA182I4 Register Thermo_byte_1 0x03 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_1;
/* TM_D bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_1__TM_D;


/* TDA182I4 Register Thermo_byte_2 0x04 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_2;
/* TM_ON bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Thermo_byte_2__TM_ON;


/* TDA182I4 Register Power_state_byte_1 0x05 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1;
/* POR bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__POR;
/* AGCs_Max bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__AGCs_Max;
/* AGCs_Lock bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__AGCs_Lock;
/* Vsync_Lock bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__Vsync_Lock;
/* LO_Lock bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_1__LO_Lock;


typedef enum _TDA182I4_power_state_mode_Item_t {
    TDA182I4_power_state_mode_NORMAL_MODE_VALUE_0 = 0,		/*  Normal mode  */
    TDA182I4_power_state_mode_STDBY_PLUS16M_VALUE_1 = 1,		/*  Stdby +16M  */
    TDA182I4_power_state_mode_STDBY_PLUS16M_PLUS_LT_VALUE_2 = 2,		/*  Stdby +16M + LT  */
    TDA182I4_power_state_mode_STDBY_PLUS16M_PLUS_PLL_VALUE_3 = 3,		/*  Stdby +16M + PLL  */
    TDA182I4_power_state_mode_STDBY_PLUS_16M_PLUS_LT_PLUS_PLL_VALUE_4 = 4		/*  Stdby + 16M + LT + PLL  */
} TDA182I4_power_state_mode_t, *pTDA182I4_power_state_mode_t;

/* TDA182I4 Register Power_state_byte_2 0x06 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_2;
/* power_state_mode bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_state_byte_2__power_state_mode;


/* TDA182I4 Register Power_Level_byte_1 0x07 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_1;
/* Power_Level_ bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_1__Power_Level_;


/* TDA182I4 Register IRQ_status 0x08 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status;
/* IRQ_status bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__IRQ_status;
/* XtalCal_End bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__XtalCal_End;
/* MSM_RSSI_End bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_RSSI_End;
/* MSM_LOCalc_End bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_LOCalc_End;
/* MSMRFCal_End bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSMRFCal_End;
/* MSM_IRCAL_End bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_IRCAL_End;
/* MSM_RCCal_End bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_status__MSM_RCCal_End;


/* TDA182I4 Register IRQ_enable 0x09 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable;
/* IRQ_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__IRQ_Enable;
/* XtalCal_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__XtalCal_Enable;
/* MSM_RSSI_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_RSSI_Enable;
/* MSM_LOCalc_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_LOCalc_Enable;
/* MSMRFCal_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSMRFCal_Enable;
/* MSM_IRCAL_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_IRCAL_Enable;
/* MSM_RCCal_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_enable__MSM_RCCal_Enable;


/* TDA182I4 Register IRQ_clear 0x0A */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear;
/* IRQ_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__IRQ_Clear;
/* XtalCal_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__XtalCal_Clear;
/* MSM_RSSI_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_RSSI_Clear;
/* MSM_LOCalc_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_LOCalc_Clear;
/* MSMRFCal_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSMRFCal_Clear;
/* MSM_IRCAL_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_IRCAL_Clear;
/* MSM_RCCal_Clear bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_clear__MSM_RCCal_Clear;


/* TDA182I4 Register IRQ_set 0x0B */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set;
/* IRQ_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__IRQ_Set;
/* XtalCal_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__XtalCal_Set;
/* MSM_RSSI_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_RSSI_Set;
/* MSM_LOCalc_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_LOCalc_Set;
/* MSMRFCal_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSMRFCal_Set;
/* MSM_IRCAL_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_IRCAL_Set;
/* MSM_RCCal_Set bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_set__MSM_RCCal_Set;


/* TDA182I4 Register Gpio_ctrl_byte 0x0C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Gpio_ctrl_byte;
/* GPIO2 bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Gpio_ctrl_byte__GPIO2;
/* GPIO1 bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Gpio_ctrl_byte__GPIO1;


typedef enum _TDA182I4_AGC1_Top_Strategy_Item_t {
    TDA182I4_AGC1_Top_Strategy_N0_NO_DYNAMIC_TOP_CHANGE_VALUE_0 = 0,		/*  n0: no dynamic top change  */
    TDA182I4_AGC1_Top_Strategy_N1_1_STEP_10DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_1 = 1,		/*  n1: 1 step 10dB top decrease at high LNA gain value&quot;  */
    TDA182I4_AGC1_Top_Strategy_N2_1_STEP_10DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_2 = 2,		/*  n2:1 step 10dB top decrease at high LNA gain value&quot;  */
    TDA182I4_AGC1_Top_Strategy_N3_1_STEP_10DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_3 = 3,		/*  n3:1 step 10dB top decrease at high LNA gain value&quot;  */
    TDA182I4_AGC1_Top_Strategy_N4_2_STEPS_10DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_4 = 4,		/*  n4:2 steps 10dB top decrease at high LNA gain value&quot;  */
    TDA182I4_AGC1_Top_Strategy_N5_2_STEPS_10DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_5 = 5,		/*  n5:2 steps 10dB top decrease at high LNA gain value&quot;  */
    TDA182I4_AGC1_Top_Strategy_N6_1_STEP_5DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_6 = 6,		/*  n6:1 step 5dB top decrease at high LNA gain value  */
    TDA182I4_AGC1_Top_Strategy_N7_1_STEP_5DB_TOP_DECREASE_AT_HIGH_LNA_GAIN_VALUE_VALUE_7 = 7		/*  n7:1 step 5dB top decrease at high LNA gain value  */
} TDA182I4_AGC1_Top_Strategy_t, *pTDA182I4_AGC1_Top_Strategy_t;

typedef enum _TDA182I4_AGC1_Top_Item_t {
    TDA182I4_AGC1_Top_85_79_VALUE_1 = 1,		/*  85/79  */
    TDA182I4_AGC1_Top_88_82_VALUE_2 = 2,		/*  88/82  */
    TDA182I4_AGC1_Top_90_84_VALUE_4 = 4,		/*  90/84  */
    TDA182I4_AGC1_Top_92_86_VALUE_10 = 10,		/*  92/86  */
    TDA182I4_AGC1_Top_95_89_VALUE_0 = 0,		/*  95/89  */
    TDA182I4_AGC1_Top_97_91_VALUE_3 = 3,		/*  97/91  */
    TDA182I4_AGC1_Top_100_94_VALUE_5 = 5,		/*  100/94  */
    TDA182I4_AGC1_Top_100_94_VALUE_6 = 6		/*  100/94  */
} TDA182I4_AGC1_Top_t, *pTDA182I4_AGC1_Top_t;

/* TDA182I4 Register AGC1_byte_1 0x0D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1;
/* PD_LNA bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1__PD_LNA;
/* AGC1_Top_Strategy bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1__AGC1_Top_Strategy;
/* AGC1_Top bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_1__AGC1_Top;


typedef enum _TDA182I4_LNA_Range_Item_t {
    TDA182I4_LNA_Range_MINUS11DB_MINUS_22DB_VALUE_0 = 0,		/*  -11dB -&gt; 22dB  */
    TDA182I4_LNA_Range_MINUS8DB_MINUS_22DB_VALUE_1 = 1,		/*  -8dB -&gt; 22dB  */
    TDA182I4_LNA_Range_7DB_MINUS_22DB_VALUE_2 = 2		/*  7dB -&gt; 22dB  */
} TDA182I4_LNA_Range_t, *pTDA182I4_LNA_Range_t;

/* TDA182I4 Register AGC1_byte_2 0x0E */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2;
/* AGC1_FastStbyLT_Enable bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__AGC1_FastStbyLT_Enable;
/* LNA_Zin bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__LNA_Zin;
/* AGC1_Vsync_Enable bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__AGC1_Vsync_Enable;
/* AGC1_cc_freeze bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__AGC1_cc_freeze;
/* LNA_Range bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_2__LNA_Range;


typedef enum _TDA182I4_AGCs_Do_Step_asym_Item_t {
    TDA182I4_AGCs_Do_Step_asym_SYM_SYM_VALUE_0 = 0,		/*  Sym / Sym  */
    TDA182I4_AGCs_Do_Step_asym_SYM_ASYM_VALUE_1 = 1,		/*  Sym / Asym  */
    TDA182I4_AGCs_Do_Step_asym_ASYM_SYM_VALUE_2 = 2,		/*  Asym / Sym  */
    TDA182I4_AGCs_Do_Step_asym_ASYM_ASYM_VALUE_3 = 3		/*  Asym / Asym  */
} TDA182I4_AGCs_Do_Step_asym_t, *pTDA182I4_AGCs_Do_Step_asym_t;

typedef enum _TDA182I4_AGCs_Up_step_Item_t {
    TDA182I4_AGCs_Up_step_262_262_262_VALUE_0 = 0,		/*  262/262/262  */
    TDA182I4_AGCs_Up_step_262_131_131_VALUE_1 = 1,		/*  262/131/131  */
    TDA182I4_AGCs_Up_step_262_262_65_VALUE_2 = 2		/*  262/262/65  */
} TDA182I4_AGCs_Up_step_t, *pTDA182I4_AGCs_Up_step_t;

typedef enum _TDA182I4_AGC2_TOP_Item_t {
    TDA182I4_AGC2_TOP_88_81_VALUE_0 = 0,		/*  88 / 81  */
    TDA182I4_AGC2_TOP_90_83_VALUE_1 = 1,		/*  90 / 83  */
    TDA182I4_AGC2_TOP_93_86_VALUE_2 = 2,		/*  93 / 86  */
    TDA182I4_AGC2_TOP_95_88_VALUE_3 = 3,		/*  95 / 88  */
    TDA182I4_AGC2_TOP_88_82_VALUE_4 = 4,		/*  88 / 82  */
    TDA182I4_AGC2_TOP_90_84_VALUE_5 = 5,		/*  90 / 84  */
    TDA182I4_AGC2_TOP_93_87_VALUE_6 = 6,		/*  93 / 87  */
    TDA182I4_AGC2_TOP_95_89_VALUE_7 = 7		/*  95 / 89  */
} TDA182I4_AGC2_TOP_t, *pTDA182I4_AGC2_TOP_t;

/* TDA182I4 Register AGC2_byte_1 0x0F */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1;
/* AGCs_Do_Step_asym bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1__AGCs_Do_Step_asym;
/* AGCs_Up_step bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1__AGCs_Up_step;
/* AGC2_TOP bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC2_byte_1__AGC2_TOP;


typedef enum _TDA182I4_AGCs_Up_Step_asym_Item_t {
    TDA182I4_AGCs_Up_Step_asym_UP_12_SYM_4_ASYM_5_ASYM_VALUE_0 = 0,		/*  UP 12 Sym / 4 Asym / 5 Asym  */
    TDA182I4_AGCs_Up_Step_asym_UP_12_SYM_4_ASYM_5_ASYM_VALUE_1 = 1,		/*  UP 12 Sym / 4 Asym / 5 Asym  */
    TDA182I4_AGCs_Up_Step_asym_UP_12_SYM_4_ASYM_5_ASYM_VALUE_2 = 2,		/*  UP 12 Sym / 4 Asym / 5 Asym  */
    TDA182I4_AGCs_Up_Step_asym_UP_12_SYM_4_ASYM_5_ASYM_VALUE_3 = 3		/*  UP 12 Sym / 4 Asym / 5 Asym  */
} TDA182I4_AGCs_Up_Step_asym_t, *pTDA182I4_AGCs_Up_Step_asym_t;

typedef enum _TDA182I4_AGCK_Step_Item_t {
    TDA182I4_AGCK_Step_0_2_DB_VALUE_0 = 0,		/*  0&quot;2 dB  */
    TDA182I4_AGCK_Step_0_4_DB_VALUE_1 = 1,		/*  0&quot;4 dB  */
    TDA182I4_AGCK_Step_0_6_DB_VALUE_2 = 2,		/*  0&quot;6 dB  */
    TDA182I4_AGCK_Step_0_8_DB_VALUE_3 = 3		/*  0&quot;8 dB  */
} TDA182I4_AGCK_Step_t, *pTDA182I4_AGCK_Step_t;

typedef enum _TDA182I4_AGCK_Mode_Item_t {
    TDA182I4_AGCK_Mode_1_STEP_EACH_VSYNC_RISING_EDGE_VALUE_0 = 0,		/*  1 step each VSYNC rising edge  */
    TDA182I4_AGCK_Mode_0_512_MS_VALUE_1 = 1,		/*  0&quot;512 ms  */
    TDA182I4_AGCK_Mode_8_192_MS_VALUE_2 = 2,		/*  8&quot;192 ms  */
    TDA182I4_AGCK_Mode_32_768_MS_VALUE_3 = 3		/*  32&quot;768 ms  */
} TDA182I4_AGCK_Mode_t, *pTDA182I4_AGCK_Mode_t;

/* TDA182I4 Register AGCK_byte_1 0x10 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1;
/* AGCs_Up_Step_asym bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__AGCs_Up_Step_asym;
/* Pulse_Shaper_Disable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__Pulse_Shaper_Disable;
/* AGCK_Step bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__AGCK_Step;
/* AGCK_Mode bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCK_byte_1__AGCK_Mode;


typedef enum _TDA182I4_RFAGC_Adapt_TOP_Item_t {
    TDA182I4_RFAGC_Adapt_TOP_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_RFAGC_Adapt_TOP_1_VALUE_1 = 1,		/*  1  */
    TDA182I4_RFAGC_Adapt_TOP_2_VALUE_2 = 2,		/*  2  */
    TDA182I4_RFAGC_Adapt_TOP_3_VALUE_3 = 3		/*  3  */
} TDA182I4_RFAGC_Adapt_TOP_t, *pTDA182I4_RFAGC_Adapt_TOP_t;

typedef enum _TDA182I4_RFAGC_Low_BW_Item_t {
    TDA182I4_RFAGC_Low_BW_100_HZ_10_MICROA_VALUE_0 = 0,		/*  100 Hz (10 microA)  */
    TDA182I4_RFAGC_Low_BW_3_HZ_250_NA_VALUE_1 = 1		/*  3 Hz (250 nA)  */
} TDA182I4_RFAGC_Low_BW_t, *pTDA182I4_RFAGC_Low_BW_t;

typedef enum _TDA182I4_RFAGC_Top_Item_t {
    TDA182I4_RFAGC_Top_94_VALUE_0 = 0,		/*  94  */
    TDA182I4_RFAGC_Top_96_VALUE_1 = 1,		/*  96  */
    TDA182I4_RFAGC_Top_98_VALUE_2 = 2,		/*  98  */
    TDA182I4_RFAGC_Top_100_VALUE_3 = 3,		/*  100  */
    TDA182I4_RFAGC_Top_102_VALUE_4 = 4,		/*  102  */
    TDA182I4_RFAGC_Top_104_VALUE_5 = 5,		/*  104  */
    TDA182I4_RFAGC_Top_106_VALUE_6 = 6,		/*  106  */
    TDA182I4_RFAGC_Top_107_VALUE_7 = 7		/*  107  */
} TDA182I4_RFAGC_Top_t, *pTDA182I4_RFAGC_Top_t;

/* TDA182I4 Register RF_AGC_byte_1 0x11 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1;
/* PD_AGC_Adapt35 bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__PD_AGC_Adapt35;
/* PD_AGC_Adapt34 bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__PD_AGC_Adapt34;
/* RFAGC_Adapt_TOP bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Adapt_TOP;
/* RFAGC_Low_BW bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Low_BW;
/* RFAGC_Top bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_1__RFAGC_Top;


typedef enum _TDA182I4_RFAGC_Peak_Val_Item_t {
    TDA182I4_RFAGC_Peak_Val_108_VALUE_0 = 0,		/*  108  */
    TDA182I4_RFAGC_Peak_Val_109_VALUE_1 = 1,		/*  109  */
    TDA182I4_RFAGC_Peak_Val_110_VALUE_2 = 2,		/*  110  */
    TDA182I4_RFAGC_Peak_Val_111_VALUE_3 = 3,		/*  111  */
    TDA182I4_RFAGC_Peak_Val_112_VALUE_4 = 4,		/*  112  */
    TDA182I4_RFAGC_Peak_Val_113_VALUE_5 = 5,		/*  113  */
    TDA182I4_RFAGC_Peak_Val_114_VALUE_6 = 6,		/*  114  */
    TDA182I4_RFAGC_Peak_Val_115_VALUE_7 = 7,		/*  115  */
    TDA182I4_RFAGC_Peak_Val_116_VALUE_8 = 8		/*  116  */
} TDA182I4_RFAGC_Peak_Val_t, *pTDA182I4_RFAGC_Peak_Val_t;

typedef enum _TDA182I4_RFAGC_Adapt_TOP_ovld_Item_t {
    TDA182I4_RFAGC_Adapt_TOP_ovld_94_VALUE_0 = 0,		/*  94  */
    TDA182I4_RFAGC_Adapt_TOP_ovld_96_VALUE_1 = 1,		/*  96  */
    TDA182I4_RFAGC_Adapt_TOP_ovld_98_VALUE_2 = 2,		/*  98  */
    TDA182I4_RFAGC_Adapt_TOP_ovld_100_VALUE_3 = 3		/*  100  */
} TDA182I4_RFAGC_Adapt_TOP_ovld_t, *pTDA182I4_RFAGC_Adapt_TOP_ovld_t;

typedef enum _TDA182I4_RFAGC_det_mode_Item_t {
    TDA182I4_RFAGC_det_mode_RMS_VALUE_0 = 0,		/*  Rms  */
    TDA182I4_RFAGC_det_mode_RMS_PLUS_PEAK_OVLD_DETECTION_VALUE_1 = 1,		/*  Rms + Peak (ovld detection)  */
    TDA182I4_RFAGC_det_mode_PEAK_VALUE_2 = 2		/*  Peak  */
} TDA182I4_RFAGC_det_mode_t, *pTDA182I4_RFAGC_det_mode_t;

/* TDA182I4 Register RF_AGC_byte_2 0x12 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2;
/* RFAGC_Peak_Val bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_Peak_Val;
/* RFAGC_Adapt_TOP_ovld bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_Adapt_TOP_ovld;
/* RFAGC_det_mode bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_2__RFAGC_det_mode;


/* TDA182I4 Register RF_AGC_byte_3 0x13 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3;
/* RFAGC_Ovld_window_size bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_window_size;
/* RFAGC_Ovld_Tcst bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_Tcst;
/* RFAGC_Ovld_nb bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_AGC_byte_3__RFAGC_Ovld_nb;


typedef enum _TDA182I4_W_Filter_Item_t {
    TDA182I4_W_Filter_2_4_MINUS_2_6_GHZ_VALUE_0 = 0,		/*  2&quot;4 - 2&quot;6 GHz  */
    TDA182I4_W_Filter_1_98_MINUS_2_17_GHZ_VALUE_1 = 1,		/*  1&quot;98 - 2&quot;17 GHz  */
    TDA182I4_W_Filter_1_7_MINUS_1_98_GHZ_VALUE_2 = 2		/*  1&quot;7 - 1&quot;98 GHz  */
} TDA182I4_W_Filter_t, *pTDA182I4_W_Filter_t;

typedef enum _TDA182I4_W_Filter_Offset_Item_t {
    TDA182I4_W_Filter_Offset_4_purcent_VALUE_0 = 0,		/*  4%  */
    TDA182I4_W_Filter_Offset_NOMINAL_VALUE_1 = 1,		/*  Nominal  */
    TDA182I4_W_Filter_Offset_MINUS4_purcent_VALUE_2 = 2,		/*  -4%  */
    TDA182I4_W_Filter_Offset_MINUS8_purcent_VALUE_3 = 3		/*  -8%  */
} TDA182I4_W_Filter_Offset_t, *pTDA182I4_W_Filter_Offset_t;

/* TDA182I4 Register W_Filter_byte 0x14 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte;
/* VHF_III_mode bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__VHF_III_mode;
/* RF_Atten_3dB bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__RF_Atten_3dB;
/* W_Filter_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter_Enable;
/* W_Filter_Bypass bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter_Bypass;
/* W_Filter bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter;
/* W_Filter_Offset bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_W_Filter_byte__W_Filter_Offset;


typedef enum _TDA182I4_S2D_Gain_Item_t {
    TDA182I4_S2D_Gain_3_VALUE_0 = 0,		/*  3  */
    TDA182I4_S2D_Gain_6_VALUE_1 = 1,		/*  6  */
    TDA182I4_S2D_Gain_9_VALUE_2 = 2		/*  9  */
} TDA182I4_S2D_Gain_t, *pTDA182I4_S2D_Gain_t;

typedef enum _TDA182I4_IR_Mixer_Top_Item_t {
    TDA182I4_IR_Mixer_Top_105_100_VALUE_1 = 1,		/*  105 / 100  */
    TDA182I4_IR_Mixer_Top_107_102_VALUE_4 = 4,		/*  107 / 102  */
    TDA182I4_IR_Mixer_Top_108_103_VALUE_6 = 6,		/*  108 / 103  */
    TDA182I4_IR_Mixer_Top_109_104_VALUE_8 = 8,		/*  109 / 104  */
    TDA182I4_IR_Mixer_Top_110_104_VALUE_10 = 10,		/*  110 / 104  */
    TDA182I4_IR_Mixer_Top_110_105_VALUE_11 = 11,		/*  110 / 105  */
    TDA182I4_IR_Mixer_Top_112_107_VALUE_14 = 14,		/*  112 / 107  */
    TDA182I4_IR_Mixer_Top_105_99_VALUE_0 = 0,		/*  105 / 99  */
    TDA182I4_IR_Mixer_Top_105_101_VALUE_2 = 2,		/*  105 / 101  */
    TDA182I4_IR_Mixer_Top_107_101_VALUE_3 = 3,		/*  107 / 101  */
    TDA182I4_IR_Mixer_Top_107_103_VALUE_5 = 5,		/*  107 / 103  */
    TDA182I4_IR_Mixer_Top_109_103_VALUE_7 = 7,		/*  109 / 103  */
    TDA182I4_IR_Mixer_Top_109_105_VALUE_9 = 9,		/*  109 / 105  */
    TDA182I4_IR_Mixer_Top_110_106_VALUE_12 = 12,		/*  110 / 106  */
    TDA182I4_IR_Mixer_Top_112_106_VALUE_13 = 13,		/*  112 / 106  */
    TDA182I4_IR_Mixer_Top_112_108_VALUE_15 = 15		/*  112 / 108  */
} TDA182I4_IR_Mixer_Top_t, *pTDA182I4_IR_Mixer_Top_t;

/* TDA182I4 Register IR_Mixer_byte_1 0x15 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_1;
/* S2D_Gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_1__S2D_Gain;
/* IR_Mixer_Top bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_1__IR_Mixer_Top;


typedef enum _TDA182I4_RSSI_HP_Fc_Item_t {
    TDA182I4_RSSI_HP_Fc_0_3M_VALUE_0 = 0,		/*  0&quot;3M  */
    TDA182I4_RSSI_HP_Fc_2_25M_VALUE_1 = 1,		/*  2&quot;25M  */
    TDA182I4_RSSI_HP_Fc_5M_VALUE_2 = 2		/*  5M  */
} TDA182I4_RSSI_HP_Fc_t, *pTDA182I4_RSSI_HP_Fc_t;

typedef enum _TDA182I4_AGC5_HP_Fc_Item_t {
    TDA182I4_AGC5_HP_Fc_0_3M_VALUE_0 = 0,		/*  0&quot;3M  */
    TDA182I4_AGC5_HP_Fc_2_25M_VALUE_1 = 1,		/*  2&quot;25M  */
    TDA182I4_AGC5_HP_Fc_5M_VALUE_2 = 2		/*  5M  */
} TDA182I4_AGC5_HP_Fc_t, *pTDA182I4_AGC5_HP_Fc_t;

typedef enum _TDA182I4_AGC5_TOP_Item_t {
    TDA182I4_AGC5_TOP_105_100_VALUE_1 = 1,		/*  105 / 100  */
    TDA182I4_AGC5_TOP_107_102_VALUE_4 = 4,		/*  107 / 102  */
    TDA182I4_AGC5_TOP_108_103_VALUE_6 = 6,		/*  108 / 103  */
    TDA182I4_AGC5_TOP_109_104_VALUE_8 = 8,		/*  109 / 104  */
    TDA182I4_AGC5_TOP_110_104_VALUE_10 = 10,		/*  110 / 104  */
    TDA182I4_AGC5_TOP_110_105_VALUE_11 = 11,		/*  110 / 105  */
    TDA182I4_AGC5_TOP_112_107_VALUE_14 = 14,		/*  112 / 107  */
    TDA182I4_AGC5_TOP_105_99_VALUE_0 = 0,		/*  105 / 99  */
    TDA182I4_AGC5_TOP_105_101_VALUE_2 = 2,		/*  105 / 101  */
    TDA182I4_AGC5_TOP_107_101_VALUE_3 = 3,		/*  107 / 101  */
    TDA182I4_AGC5_TOP_107_103_VALUE_5 = 5,		/*  107 / 103  */
    TDA182I4_AGC5_TOP_109_103_VALUE_7 = 7,		/*  109 / 103  */
    TDA182I4_AGC5_TOP_109_105_VALUE_9 = 9,		/*  109 / 105  */
    TDA182I4_AGC5_TOP_110_106_VALUE_12 = 12,		/*  110 / 106  */
    TDA182I4_AGC5_TOP_112_106_VALUE_13 = 13,		/*  112 / 106  */
    TDA182I4_AGC5_TOP_112_108_VALUE_15 = 15		/*  112 / 108  */
} TDA182I4_AGC5_TOP_t, *pTDA182I4_AGC5_TOP_t;

/* TDA182I4 Register AGC5_byte_1 0x16 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1;
/* RSSI_HP_Fc bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1__RSSI_HP_Fc;
/* AGC5_HP_Fc bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1__AGC5_HP_Fc;
/* AGC5_TOP bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_1__AGC5_TOP;


typedef enum _TDA182I4_IF_level_Item_t {
    TDA182I4_IF_level_0_MINUS_30_DB_2_VPP_VALUE_0 = 0,		/*  0 -&gt; 30 dB (2 Vpp)  */
    TDA182I4_IF_level_MINUS4_MINUS_26_DB_1_25_VPP_VALUE_1 = 1,		/*  -4 -&gt; 26 dB (1&quot;25 Vpp)  */
    TDA182I4_IF_level_MINUS6_MINUS_24_DB_1_VPP_VALUE_2 = 2,		/*  -6 -&gt; 24 dB (1 Vpp)  */
    TDA182I4_IF_level_MINUS8_MINUS_22_DB_0_8_VPP_VALUE_3 = 3,		/*  -8 -&gt; 22 dB (0&quot;8 Vpp)  */
    TDA182I4_IF_level_MINUS7_50_MINUS_22_5_DB_0_85_VPP_VALUE_4 = 4,		/*  -7&quot;50 -&gt; 22&quot;5 dB (0&quot;85 Vpp)  */
    TDA182I4_IF_level_MINUS9_MINUS_21_DB_0_7_VPP_VALUE_5 = 5,		/*  -9 -&gt; 21 dB (0&quot;7 Vpp)  */
    TDA182I4_IF_level_MINUS10_30_MINUS_19_7_DB_0_6_VPP_VALUE_6 = 6,		/*  -10&quot;30 -&gt; 19&quot;7 dB (0&quot;6 Vpp)  */
    TDA182I4_IF_level_MINUS12_MINUS_18_DB_0_5_VPP_VALUE_7 = 7		/*  -12 -&gt; 18 dB (0&quot;5 Vpp)  */
} TDA182I4_IF_level_t, *pTDA182I4_IF_level_t;

/* TDA182I4 Register IF_AGC_byte 0x17 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte;
/* IFnotchToRSSI bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte__IFnotchToRSSI;
/* LPF_DCOffset_Corr bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte__LPF_DCOffset_Corr;
/* IF_level bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_AGC_byte__IF_level;


typedef enum _TDA182I4_IF_LPF_Offset_Item_t {
    TDA182I4_IF_LPF_Offset_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_IF_LPF_Offset_4_VALUE_1 = 1,		/*  4  */
    TDA182I4_IF_LPF_Offset_8_VALUE_2 = 2,		/*  8  */
    TDA182I4_IF_LPF_Offset_12_VALUE_3 = 3		/*  12  */
} TDA182I4_IF_LPF_Offset_t, *pTDA182I4_IF_LPF_Offset_t;

typedef enum _TDA182I4_LP_Fc_Item_t {
    TDA182I4_LP_Fc_6_VALUE_0 = 0,		/*  6  */
    TDA182I4_LP_Fc_7_VALUE_1 = 1,		/*  7  */
    TDA182I4_LP_Fc_8_VALUE_2 = 2,		/*  8  */
    TDA182I4_LP_Fc_9_VALUE_3 = 3,		/*  9  */
    TDA182I4_LP_Fc_10_VALUE_4 = 4,		/*  10  */
    TDA182I4_LP_Fc_11_2_VALUE_5 = 5,		/*  11&quot;2  */
    TDA182I4_LP_Fc_1_5_VALUE_6 = 6		/*  1&quot;5  */
} TDA182I4_LP_Fc_t, *pTDA182I4_LP_Fc_t;

/* TDA182I4 Register IF_Byte_1 0x18 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1;
/* IF_LPF_Offset bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1__IF_LPF_Offset;
/* IF_LPF_sign bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1__IF_LPF_sign;
/* LP_Fc bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_1__LP_Fc;


typedef enum _TDA182I4_IF_HPF_Offset_Item_t {
    TDA182I4_IF_HPF_Offset_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_IF_HPF_Offset_4_VALUE_1 = 1,		/*  4  */
    TDA182I4_IF_HPF_Offset_8_VALUE_2 = 2,		/*  8  */
    TDA182I4_IF_HPF_Offset_12_VALUE_3 = 3		/*  12  */
} TDA182I4_IF_HPF_Offset_t, *pTDA182I4_IF_HPF_Offset_t;

typedef enum _TDA182I4_IF_HP_Fc_Item_t {
    TDA182I4_IF_HP_Fc_0_5_VALUE_0 = 0,		/*  0&quot;5  */
    TDA182I4_IF_HP_Fc_1_VALUE_1 = 1,		/*  1  */
    TDA182I4_IF_HP_Fc_1_6_VALUE_2 = 2,		/*  1&quot;6  */
    TDA182I4_IF_HP_Fc_2_3_VALUE_3 = 3,		/*  2&quot;3  */
    TDA182I4_IF_HP_Fc_3_5_VALUE_4 = 4		/*  3&quot;5  */
} TDA182I4_IF_HP_Fc_t, *pTDA182I4_IF_HP_Fc_t;

/* TDA182I4 Register IF_Byte_2 0x19 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2;
/* IF_HPF_Offset bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HPF_Offset;
/* IF_HPF_sign bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HPF_sign;
/* IF_HP_Fc bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HP_Fc;
/* IF_HP_Enable bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_2__IF_HP_Enable;


typedef enum _TDA182I4_IF_Notch_Offset_Item_t {
    TDA182I4_IF_Notch_Offset_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_IF_Notch_Offset_4_VALUE_1 = 1,		/*  4  */
    TDA182I4_IF_Notch_Offset_8_VALUE_2 = 2,		/*  8  */
    TDA182I4_IF_Notch_Offset_12_VALUE_3 = 3		/*  12  */
} TDA182I4_IF_Notch_Offset_t, *pTDA182I4_IF_Notch_Offset_t;

typedef enum _TDA182I4_IF_Notch_Freq_Item_t {
    TDA182I4_IF_Notch_Freq_6_25_VALUE_0 = 0,		/*  6&quot;25  */
    TDA182I4_IF_Notch_Freq_7_25_VALUE_1 = 1,		/*  7&quot;25  */
    TDA182I4_IF_Notch_Freq_8_25_VALUE_2 = 2,		/*  8&quot;25  */
    TDA182I4_IF_Notch_Freq_9_25_VALUE_3 = 3,		/*  9&quot;25  */
    TDA182I4_IF_Notch_Freq_10_25_VALUE_4 = 4,		/*  10&quot;25  */
    TDA182I4_IF_Notch_Freq_11_45_VALUE_5 = 5		/*  11&quot;45  */
} TDA182I4_IF_Notch_Freq_t, *pTDA182I4_IF_Notch_Freq_t;

/* TDA182I4 Register IF_Byte_3 0x1A */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3;
/* IF_Notch_Offset bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_Offset;
/* IF_Notch_sign bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_sign;
/* IF_Notch_Freq bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_Freq;
/* IF_Notch_Enable bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Byte_3__IF_Notch_Enable;


typedef enum _TDA182I4_Dig_Clock_Item_t {
    TDA182I4_Dig_Clock_16_MHZ_XTAL_VALUE_0 = 0,		/*  16 MHz Xtal   */
    TDA182I4_Dig_Clock_SIGMA_DELTA_CLOCK_VALUE_1 = 1,		/*  sigma delta clock  */
    TDA182I4_Dig_Clock_16_MHZ_XTAL_VALUE_2 = 2,		/*  16 MHz Xtal   */
    TDA182I4_Dig_Clock_SUB_LO_VALUE_3 = 3		/*  sub LO  */
} TDA182I4_Dig_Clock_t, *pTDA182I4_Dig_Clock_t;

typedef enum _TDA182I4_Xtout_Amp_Item_t {
    TDA182I4_Xtout_Amp_400MVPP_DIFF_VALUE_0 = 0,		/*  400mVpp diff  */
    TDA182I4_Xtout_Amp_800MVPP_DIFF_VALUE_1 = 1		/*  800mVpp diff  */
} TDA182I4_Xtout_Amp_t, *pTDA182I4_Xtout_Amp_t;

/* TDA182I4 Register Reference_Byte 0x1B */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte;
/* Dig_Clock bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte__Dig_Clock;
/* Xtout_Amp bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte__Xtout_Amp;
/* XTout bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Reference_Byte__XTout;


/* TDA182I4 Register IF_Frequency_byte 0x1C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Frequency_byte;
/* IF_Freq bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IF_Frequency_byte__IF_Freq;


typedef enum _TDA182I4_switch_smooth_t_cst_Item_t {
    TDA182I4_switch_smooth_t_cst_0_5_VALUE_0 = 0,		/*  0&quot;5  */
    TDA182I4_switch_smooth_t_cst_2_5_VALUE_1 = 1,		/*  2&quot;5  */
    TDA182I4_switch_smooth_t_cst_5_VALUE_2 = 2,		/*  5  */
    TDA182I4_switch_smooth_t_cst_9_VALUE_3 = 3,		/*  9  */
    TDA182I4_switch_smooth_t_cst_18_VALUE_4 = 4,		/*  18  */
    TDA182I4_switch_smooth_t_cst_36_VALUE_5 = 5,		/*  36  */
    TDA182I4_switch_smooth_t_cst_72_VALUE_6 = 6,		/*  72  */
    TDA182I4_switch_smooth_t_cst_224_VALUE_7 = 7		/*  224  */
} TDA182I4_switch_smooth_t_cst_t, *pTDA182I4_switch_smooth_t_cst_t;

/* TDA182I4 Register smooth_cc_byte_1 0x1D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_smooth_cc_byte_1;
/* smooth_cc bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_smooth_cc_byte_1__smooth_cc;
/* switch_smooth_t_cst bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_smooth_cc_byte_1__switch_smooth_t_cst;


/* TDA182I4 Register RF_Frequency_byte_1 0x1E */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_1;
/* RF_Freq_1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_1__RF_Freq_1;


/* TDA182I4 Register RF_Frequency_byte_2 0x1F */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_2;
/* RF_Freq_2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_2__RF_Freq_2;


/* TDA182I4 Register RF_Frequency_byte_3 0x20 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_3;
/* RF_Freq_3 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Frequency_byte_3__RF_Freq_3;


/* TDA182I4 Register MSM_byte_1 0x21 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1;
/* RSSI_Meas bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RSSI_Meas;
/* IR_CAL_Loop bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__IR_CAL_Loop;
/* IR_Cal_Image bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__IR_Cal_Image;
/* IR_CAL_Wanted bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__IR_CAL_Wanted;
/* RF_CAL_AV bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RF_CAL_AV;
/* RF_CAL bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RF_CAL;
/* RC_Cal bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__RC_Cal;
/* Calc_PLL bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_1__Calc_PLL;


/* TDA182I4 Register MSM_byte_2 0x22 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_2;
/* XtalCal_Launch bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_2__XtalCal_Launch;
/* MSM_Launch bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_MSM_byte_2__MSM_Launch;


typedef enum _TDA182I4_AGC1_boost_Item_t {
    TDA182I4_AGC1_boost_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_AGC1_boost_5_MA_VALUE_1 = 1,		/*  5 mA  */
    TDA182I4_AGC1_boost_11_MA_VALUE_2 = 2,		/*  11 mA  */
    TDA182I4_AGC1_boost_15_MA_VALUE_3 = 3		/*  15 mA  */
} TDA182I4_AGC1_boost_t, *pTDA182I4_AGC1_boost_t;

typedef enum _TDA182I4_PSM_IM2_Filter_Item_t {
    TDA182I4_PSM_IM2_Filter_PLUS5_MA_VALUE_0 = 0,		/*  +5 mA  */
    TDA182I4_PSM_IM2_Filter_PLUS2_5_MA_VALUE_1 = 1,		/*  +2&quot;5 mA  */
    TDA182I4_PSM_IM2_Filter_NOMINAL_VALUE_2 = 2,		/*  nominal  */
    TDA182I4_PSM_IM2_Filter_MINUS3_9_MA_VALUE_3 = 3		/*  -3&quot;9 mA  */
} TDA182I4_PSM_IM2_Filter_t, *pTDA182I4_PSM_IM2_Filter_t;

typedef enum _TDA182I4_PSM_RF_BUF_LTO_Item_t {
    TDA182I4_PSM_RF_BUF_LTO_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_RF_BUF_LTO_MINUS2_7_MA_VALUE_1 = 1,		/*  -2&quot;7 mA  */
    TDA182I4_PSM_RF_BUF_LTO_MINUS5_4_MA_VALUE_2 = 2,		/*  -5&quot;4 mA  */
    TDA182I4_PSM_RF_BUF_LTO_MINUS8_1_MA_VALUE_3 = 3		/*  -8&quot;1 mA  */
} TDA182I4_PSM_RF_BUF_LTO_t, *pTDA182I4_PSM_RF_BUF_LTO_t;

typedef enum _TDA182I4_PSM_RFfilter_Item_t {
    TDA182I4_PSM_RFfilter_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_PSM_RFfilter_MINUS5_VHF_MINUS3_UHF_VALUE_1 = 1,		/*  -5 (VHF) / -3(UHF)  */
    TDA182I4_PSM_RFfilter_MINUS6_5_VHF_MINUS4_UHF_VALUE_2 = 2,		/*  -6&quot;5 (VHF) / -4(UHF)  */
    TDA182I4_PSM_RFfilter_MINUS8_VHF_MINUS5_UHF_VALUE_3 = 3		/*  -8 (VHF) / -5(UHF)  */
} TDA182I4_PSM_RFfilter_t, *pTDA182I4_PSM_RFfilter_t;

/* TDA182I4 Register PowerSavingMode_byte_1 0x23 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1;
/* AGC1_boost bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__AGC1_boost;
/* PSM_IM2_Filter bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_IM2_Filter;
/* PSM_RF_BUF_LTO bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_RF_BUF_LTO;
/* PSM_RFfilter bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_1__PSM_RFfilter;


typedef enum _TDA182I4_PSM_VCO_Item_t {
    TDA182I4_PSM_VCO_PLUS1_MA_VALUE_0 = 0,		/*  +1 mA  */
    TDA182I4_PSM_VCO_PLUS0_4_MA_VALUE_1 = 1,		/*  +0&quot;4 mA  */
    TDA182I4_PSM_VCO_0_MA_VALUE_2 = 2,		/*  0 mA  */
    TDA182I4_PSM_VCO_MINUS0_4_MA_VALUE_3 = 3		/*  -0&quot;4 mA  */
} TDA182I4_PSM_VCO_t, *pTDA182I4_PSM_VCO_t;

typedef enum _TDA182I4_PSM_IFfilter_Item_t {
    TDA182I4_PSM_IFfilter_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_PSM_IFfilter_MINUS4_2_MA_VALUE_1 = 1,		/*  -4&quot;2 mA  */
    TDA182I4_PSM_IFfilter_MINUS7_0_MA_VALUE_2 = 2,		/*  -7&quot;0 mA  */
    TDA182I4_PSM_IFfilter_MINUS8_9_MA_VALUE_3 = 3		/*  -8&quot;9 mA  */
} TDA182I4_PSM_IFfilter_t, *pTDA182I4_PSM_IFfilter_t;

typedef enum _TDA182I4_PSM_IFLPF_Item_t {
    TDA182I4_PSM_IFLPF_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_IFLPF_MINUS2_3_MA_VALUE_1 = 1,		/*  -2&quot;3 mA  */
    TDA182I4_PSM_IFLPF_MINUS3_8_MA_VALUE_2 = 2,		/*  -3&quot;8 mA  */
    TDA182I4_PSM_IFLPF_MINUS_4_9_MA_VALUE_3 = 3		/*  - 4&quot;9 mA  */
} TDA182I4_PSM_IFLPF_t, *pTDA182I4_PSM_IFLPF_t;

typedef enum _TDA182I4_PSM_H3H5_Item_t {
    TDA182I4_PSM_H3H5_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_H3H5_MINUS2_MA_VALUE_1 = 1,		/*  -2 mA  */
    TDA182I4_PSM_H3H5_MINUS4_MA_VALUE_2 = 2,		/*  -4 mA  */
    TDA182I4_PSM_H3H5_MINUS6_MA_VALUE_3 = 3		/*  -6 mA  */
} TDA182I4_PSM_H3H5_t, *pTDA182I4_PSM_H3H5_t;

/* TDA182I4 Register PowerSavingMode_byte_2 0x24 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2;
/* PSM_VCO bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_VCO;
/* PSM_IFfilter bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_IFfilter;
/* PSM_IFLPF bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_IFLPF;
/* PSM_H3H5 bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_2__PSM_H3H5;


typedef enum _TDA182I4_PSM_RFpoly_Item_t {
    TDA182I4_PSM_RFpoly_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_RFpoly_MINUS4_2_MA_VALUE_1 = 1,		/*  -4&quot;2 mA  */
    TDA182I4_PSM_RFpoly_MINUS7_2_MA_VALUE_2 = 2,		/*  -7&quot;2 mA  */
    TDA182I4_PSM_RFpoly_MINUS9_3_MA_VALUE_3 = 3		/*  -9&quot;3 mA  */
} TDA182I4_PSM_RFpoly_t, *pTDA182I4_PSM_RFpoly_t;

typedef enum _TDA182I4_PSM_Mixer_Item_t {
    TDA182I4_PSM_Mixer_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_Mixer_MINUS1_2_MA_VALUE_1 = 1,		/*  -1&quot;2 mA  */
    TDA182I4_PSM_Mixer_MINUS1_8_MA_VALUE_2 = 2,		/*  -1&quot;8 mA  */
    TDA182I4_PSM_Mixer_MINUS2_3_MA_VALUE_3 = 3		/*  -2&quot;3 mA  */
} TDA182I4_PSM_Mixer_t, *pTDA182I4_PSM_Mixer_t;

typedef enum _TDA182I4_PSM_Ifpoly_Item_t {
    TDA182I4_PSM_Ifpoly_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_Ifpoly_MINUS1_8_MA_VALUE_1 = 1,		/*  -1&quot;8 mA  */
    TDA182I4_PSM_Ifpoly_MINUS3_2_MA_VALUE_2 = 2,		/*  -3&quot;2 mA  */
    TDA182I4_PSM_Ifpoly_MINUS4_1_MA_VALUE_3 = 3		/*  -4&quot;1 mA  */
} TDA182I4_PSM_Ifpoly_t, *pTDA182I4_PSM_Ifpoly_t;

typedef enum _TDA182I4_PSM_Lodriver_Item_t {
    TDA182I4_PSM_Lodriver_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_Lodriver_MINUS3_MA_VALUE_1 = 1,		/*  -3 mA  */
    TDA182I4_PSM_Lodriver_MINUS4_5_MA_VALUE_2 = 2,		/*  -4&quot;5 mA  */
    TDA182I4_PSM_Lodriver_MINUS6_MA_VALUE_3 = 3		/*  -6 mA  */
} TDA182I4_PSM_Lodriver_t, *pTDA182I4_PSM_Lodriver_t;

/* TDA182I4 Register PowerSavingMode_byte_3 0x25 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3;
/* PSM_RFpoly bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_RFpoly;
/* PSM_Mixer bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_Mixer;
/* PSM_Ifpoly bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_Ifpoly;
/* PSM_Lodriver bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_3__PSM_Lodriver;


typedef enum _TDA182I4_PSM_DCC_Item_t {
    TDA182I4_PSM_DCC_0_MA_VALUE_0 = 0,		/*  0 mA  */
    TDA182I4_PSM_DCC_MINUS4_5_MA_VALUE_1 = 1		/*  -4&quot;5 mA  */
} TDA182I4_PSM_DCC_t, *pTDA182I4_PSM_DCC_t;

/* TDA182I4 Register PowerSavingMode_byte_4 0x26 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_4;
/* PSM_DCC bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_PowerSavingMode_byte_4__PSM_DCC;


/* TDA182I4 Register Power_Level_byte_2 0x27 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2;
/* PD_PLD_read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2__PD_PLD_read;
/* PLD_Temp_Slope bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2__PLD_Temp_Slope;
/* PLD_Gain_Corr bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Level_byte_2__PLD_Gain_Corr;


/* TDA182I4 Register Adapt_Top_byte 0x28 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Adapt_Top_byte;
/* Fast_Mode_AGC bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Adapt_Top_byte__Fast_Mode_AGC;
/* Ovld_Udld_FastUp bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Adapt_Top_byte__Ovld_Udld_FastUp;


typedef enum _TDA182I4_Tracer_Step_Item_t {
    TDA182I4_Tracer_Step_1_8DB_PER_PERIOD_VALUE_0 = 0,		/*  1/8dB per period  */
    TDA182I4_Tracer_Step_1_DB_PER_PERIOD_VALUE_1 = 1,		/*  1 dB per period  */
    TDA182I4_Tracer_Step_1_2DB_PER_PERIOD_VALUE_2 = 2,		/*  1/2dB per period  */
    TDA182I4_Tracer_Step_1_4DB_PER_PERIOD_VALUE_3 = 3		/*  1/4dB per period  */
} TDA182I4_Tracer_Step_t, *pTDA182I4_Tracer_Step_t;

typedef enum _TDA182I4_Vsync_Thresh_Item_t {
    TDA182I4_Vsync_Thresh_48MICROS_12_PERIODS_VALUE_0 = 0,		/*  48micros (12 periods)  */
    TDA182I4_Vsync_Thresh_16MICROS_4_PERIODS_VALUE_1 = 1,		/*  16micros (4 periods)  */
    TDA182I4_Vsync_Thresh_32MICROS_8_PERIODS_VALUE_2 = 2,		/*  32micros (8 periods)  */
    TDA182I4_Vsync_Thresh_64MICROS_16_PERIODS_VALUE_3 = 3		/*  64micros (16 periods)  */
} TDA182I4_Vsync_Thresh_t, *pTDA182I4_Vsync_Thresh_t;

typedef enum _TDA182I4_Vsync_Len_Item_t {
    TDA182I4_Vsync_Len_256MICROS_64_PERIODS_VALUE_0 = 0,		/*  256micros (64 periods)  */
    TDA182I4_Vsync_Len_64MICROS_16_PERIODS_VALUE_1 = 1,		/*  64micros (16 periods)  */
    TDA182I4_Vsync_Len_128MICROS_32_PERIODS_VALUE_2 = 2,		/*  128micros (32 periods)  */
    TDA182I4_Vsync_Len_512MICROS_128_PERIODS_VALUE_3 = 3		/*  512micros (128 periods)  */
} TDA182I4_Vsync_Len_t, *pTDA182I4_Vsync_Len_t;

/* TDA182I4 Register Vsync_byte 0x29 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte;
/* Neg_Modulation bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Neg_Modulation;
/* Tracer_Step bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Tracer_Step;
/* vsync_Int bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__vsync_Int;
/* Vsync_Thresh bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Vsync_Thresh;
/* Vsync_Len bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_byte__Vsync_Len;


typedef enum _TDA182I4_AGC_Ovld_TOP_Item_t {
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS3_5_MINUS3_5_VALUE_0 = 0,		/*  +9/+3&quot;5/-3&quot;5  */
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS4_5_MINUS4_5_VALUE_1 = 1,		/*  +9/+4&quot;5/-4&quot;5  */
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS4_5_MINUS3_5_VALUE_2 = 2,		/*  +9/+4&quot;5/-3&quot;5  */
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS6_MINUS4_5_VALUE_3 = 3,		/*  +9/+6/-4&quot;5  */
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS6_MINUS6_VALUE_4 = 4,		/*  +9/+6/-6  */
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS6_MINUS9_VALUE_5 = 5,		/*  +9/+6/-9  */
    TDA182I4_AGC_Ovld_TOP_PLUS9_PLUS7_5_MINUS9_VALUE_6 = 6,		/*  +9/+7&quot;5/-9  */
    TDA182I4_AGC_Ovld_TOP_PLUS12_PLUS7_5_MINUS9_VALUE_7 = 7		/*  +12/+7&quot;5/-9  */
} TDA182I4_AGC_Ovld_TOP_t, *pTDA182I4_AGC_Ovld_TOP_t;

/* TDA182I4 Register Vsync_Mgt_byte 0x2A */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte;
/* PD_Vsync_Mgt bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Vsync_Mgt;
/* PD_Ovld bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld;
/* PD_Ovld_RF bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Ovld_RF;
/* PD_Udld bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__PD_Udld;
/* AGC_Ovld_TOP bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__AGC_Ovld_TOP;
/* AGC_Ovld_Timer bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Vsync_Mgt_byte__AGC_Ovld_Timer;


typedef enum _TDA182I4_IR_Mixer_Do_step_Item_t {
    TDA182I4_IR_Mixer_Do_step_8_176_VALUE_0 = 0,		/*  8&quot;176  */
    TDA182I4_IR_Mixer_Do_step_2_044_VALUE_1 = 1,		/*  2&quot;044  */
    TDA182I4_IR_Mixer_Do_step_1_022_VALUE_2 = 2,		/*  1&quot;022  */
    TDA182I4_IR_Mixer_Do_step_0_512_VALUE_3 = 3		/*  0&quot;512  */
} TDA182I4_IR_Mixer_Do_step_t, *pTDA182I4_IR_Mixer_Do_step_t;

/* TDA182I4 Register IR_Mixer_byte_2 0x2B */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2;
/* IR_Mixer_loop_off bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2__IR_Mixer_loop_off;
/* IR_Mixer_Do_step bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2__IR_Mixer_Do_step;
/* DC_Notch bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Mixer_byte_2__DC_Notch;


typedef enum _TDA182I4_LT_Gain_Item_t {
    TDA182I4_LT_Gain_MINUS4_5_VALUE_0 = 0,		/*  -4&quot;5  */
    TDA182I4_LT_Gain_MINUS4_5_VALUE_1 = 1,		/*  -4&quot;5  */
    TDA182I4_LT_Gain_MINUS4_5_VALUE_2 = 2,		/*  -4&quot;5  */
    TDA182I4_LT_Gain_MINUS7_5_VALUE_3 = 3,		/*  -7&quot;5  */
    TDA182I4_LT_Gain_MINUS10_5_VALUE_4 = 4,		/*  -10&quot;5  */
    TDA182I4_LT_Gain_MINUS13_5_VALUE_5 = 5,		/*  -13&quot;5  */
    TDA182I4_LT_Gain_MINUS16_5_VALUE_6 = 6,		/*  -16&quot;5  */
    TDA182I4_LT_Gain_MINUS19_5_VALUE_7 = 7		/*  -19&quot;5  */
} TDA182I4_LT_Gain_t, *pTDA182I4_LT_Gain_t;

/* TDA182I4 Register LT_byte_1 0x2C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1;
/* PD_LT bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__PD_LT;
/* PD_RF_BUF_LTO bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__PD_RF_BUF_LTO;
/* Force_LT_gain bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__Force_LT_gain;
/* LT_Gain bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_1__LT_Gain;


typedef enum _TDA182I4_LT_smooth_t_cst_fast_Item_t {
    TDA182I4_LT_smooth_t_cst_fast_0_MS_VALUE_0 = 0,		/*  0 ms  */
    TDA182I4_LT_smooth_t_cst_fast_5_MS_VALUE_1 = 1,		/*  5 ms  */
    TDA182I4_LT_smooth_t_cst_fast_9_MS_VALUE_2 = 2,		/*  9 ms  */
    TDA182I4_LT_smooth_t_cst_fast_18_M_VALUE_3 = 3,		/*  18 m  */
    TDA182I4_LT_smooth_t_cst_fast_36_MS_VALUE_4 = 4,		/*  36 ms  */
    TDA182I4_LT_smooth_t_cst_fast_72_MS_VALUE_5 = 5,		/*  72 ms  */
    TDA182I4_LT_smooth_t_cst_fast_144_MS_VALUE_6 = 6,		/*  144 ms  */
    TDA182I4_LT_smooth_t_cst_fast_448_MS_VALUE_7 = 7		/*  448 ms  */
} TDA182I4_LT_smooth_t_cst_fast_t, *pTDA182I4_LT_smooth_t_cst_fast_t;

typedef enum _TDA182I4_LT_smooth_t_cst_Item_t {
    TDA182I4_LT_smooth_t_cst_0_MS_VALUE_0 = 0,		/*  0 ms  */
    TDA182I4_LT_smooth_t_cst_5_MS_VALUE_1 = 1,		/*  5 ms  */
    TDA182I4_LT_smooth_t_cst_9_MS_VALUE_2 = 2,		/*  9 ms  */
    TDA182I4_LT_smooth_t_cst_18_M_VALUE_3 = 3,		/*  18 m  */
    TDA182I4_LT_smooth_t_cst_36_MS_VALUE_4 = 4,		/*  36 ms  */
    TDA182I4_LT_smooth_t_cst_72_MS_VALUE_5 = 5,		/*  72 ms  */
    TDA182I4_LT_smooth_t_cst_144_MS_VALUE_6 = 6,		/*  144 ms  */
    TDA182I4_LT_smooth_t_cst_448_MS_VALUE_7 = 7		/*  448 ms  */
} TDA182I4_LT_smooth_t_cst_t, *pTDA182I4_LT_smooth_t_cst_t;

/* TDA182I4 Register LT_byte_2 0x2D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_2;
/* LT_smooth_t_cst_fast bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst_fast;
/* LT_smooth_t_cst bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_byte_2__LT_smooth_t_cst;


typedef enum _TDA182I4_AGC1_Do_step_Item_t {
    TDA182I4_AGC1_Do_step_8_176_VALUE_0 = 0,		/*  8&quot;176  */
    TDA182I4_AGC1_Do_step_2_044_VALUE_1 = 1,		/*  2&quot;044  */
    TDA182I4_AGC1_Do_step_1_022_VALUE_2 = 2,		/*  1&quot;022  */
    TDA182I4_AGC1_Do_step_0_512_VALUE_3 = 3		/*  0&quot;512  */
} TDA182I4_AGC1_Do_step_t, *pTDA182I4_AGC1_Do_step_t;

typedef enum _TDA182I4_AGC1_Gain_Item_t {
    TDA182I4_AGC1_Gain_MINUS11_VALUE_0 = 0,		/*  -11  */
    TDA182I4_AGC1_Gain_MINUS8_VALUE_1 = 1,		/*  -8  */
    TDA182I4_AGC1_Gain_MINUS5_VALUE_2 = 2,		/*  -5  */
    TDA182I4_AGC1_Gain_MINUS2_VALUE_3 = 3,		/*  -2  */
    TDA182I4_AGC1_Gain_1_VALUE_4 = 4,		/*  1  */
    TDA182I4_AGC1_Gain_4_VALUE_5 = 5,		/*  4  */
    TDA182I4_AGC1_Gain_7_VALUE_6 = 6,		/*  7  */
    TDA182I4_AGC1_Gain_10_VALUE_7 = 7,		/*  10  */
    TDA182I4_AGC1_Gain_13_VALUE_8 = 8,		/*  13  */
    TDA182I4_AGC1_Gain_16_VALUE_9 = 9,		/*  16  */
    TDA182I4_AGC1_Gain_19_VALUE_10 = 10,		/*  19  */
    TDA182I4_AGC1_Gain_22_VALUE_10 = 10		/*  22  */
} TDA182I4_AGC1_Gain_t, *pTDA182I4_AGC1_Gain_t;

/* TDA182I4 Register AGC1_byte_3 0x2E */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3;
/* AGC1_loop_off bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__AGC1_loop_off;
/* AGC1_Do_step bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__AGC1_Do_step;
/* Force_AGC1_gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__Force_AGC1_gain;
/* AGC1_Gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_3__AGC1_Gain;


typedef enum _TDA182I4_AGC1_smooth_t_cst_fast_Item_t {
    TDA182I4_AGC1_smooth_t_cst_fast_INSTANTANEOUS_VALUE_0 = 0,		/*  Instantaneous  */
    TDA182I4_AGC1_smooth_t_cst_fast_14_MS_VALUE_1 = 1,		/*  14 ms  */
    TDA182I4_AGC1_smooth_t_cst_fast_25_MS_VALUE_2 = 2,		/*  25 ms  */
    TDA182I4_AGC1_smooth_t_cst_fast_47_MS_VALUE_3 = 3,		/*  47 ms  */
    TDA182I4_AGC1_smooth_t_cst_fast_92_MS_VALUE_4 = 4,		/*  92 ms  */
    TDA182I4_AGC1_smooth_t_cst_fast_182_MS_VALUE_5 = 5,		/*  182 ms  */
    TDA182I4_AGC1_smooth_t_cst_fast_361_MS_VALUE_6 = 6,		/*  361 ms  */
    TDA182I4_AGC1_smooth_t_cst_fast_1123_MS_VALUE_7 = 7		/*  1123 ms  */
} TDA182I4_AGC1_smooth_t_cst_fast_t, *pTDA182I4_AGC1_smooth_t_cst_fast_t;

typedef enum _TDA182I4_AGC1_smooth_t_cst_Item_t {
    TDA182I4_AGC1_smooth_t_cst_INSTANTANEOUS_VALUE_0 = 0,		/*  Instantaneous  */
    TDA182I4_AGC1_smooth_t_cst_14_MS_VALUE_1 = 1,		/*  14 ms  */
    TDA182I4_AGC1_smooth_t_cst_25_MS_VALUE_2 = 2,		/*  25 ms  */
    TDA182I4_AGC1_smooth_t_cst_47_MS_VALUE_3 = 3,		/*  47 ms  */
    TDA182I4_AGC1_smooth_t_cst_92_MS_VALUE_4 = 4,		/*  92 ms  */
    TDA182I4_AGC1_smooth_t_cst_182_MS_VALUE_5 = 5,		/*  182 ms  */
    TDA182I4_AGC1_smooth_t_cst_361_MS_VALUE_6 = 6,		/*  361 ms  */
    TDA182I4_AGC1_smooth_t_cst_1123_MS_VALUE_7 = 7		/*  1123 ms  */
} TDA182I4_AGC1_smooth_t_cst_t, *pTDA182I4_AGC1_smooth_t_cst_t;

/* TDA182I4 Register AGC1_byte_4 0x2F */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4;
/* AGC1_rst_do_enable bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_rst_do_enable;
/* AGC1_rst_up_enable bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_rst_up_enable;
/* AGC1_smooth_t_cst_fast bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst_fast;
/* AGC1_smooth_t_cst bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_byte_4__AGC1_smooth_t_cst;


typedef enum _TDA182I4_PLD_DAC_Scale_Item_t {
    TDA182I4_PLD_DAC_Scale_2V_VALUE_0 = 0,		/*  2V  */
    TDA182I4_PLD_DAC_Scale_2_4V_VALUE_1 = 1		/*  2&quot;4V  */
} TDA182I4_PLD_DAC_Scale_t, *pTDA182I4_PLD_DAC_Scale_t;

/* TDA182I4 Register RFAGCs_Gain_byte_1 0x30 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1;
/* PLD_DAC_Scale bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__PLD_DAC_Scale;
/* PLD_CC_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__PLD_CC_Enable;
/* PLD_Temp_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__PLD_Temp_Enable;
/* TH_AGC_Adapt34 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__TH_AGC_Adapt34;
/* RFAGC_Sense_Enable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__RFAGC_Sense_Enable;
/* RFAGC_K_Bypass bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__RFAGC_K_Bypass;
/* RFAGC_K_8 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_1__RFAGC_K_8;


/* TDA182I4 Register RFAGCs_Gain_byte_2 0x31 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_2;
/* RFAGC_K bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_2__RFAGC_K;


typedef enum _TDA182I4_AGC5_Do_step_Item_t {
    TDA182I4_AGC5_Do_step_8_176_VALUE_0 = 0,		/*  8&quot;176  */
    TDA182I4_AGC5_Do_step_2_044_VALUE_1 = 1,		/*  2&quot;044  */
    TDA182I4_AGC5_Do_step_1_022_VALUE_2 = 2,		/*  1&quot;022  */
    TDA182I4_AGC5_Do_step_0_512_VALUE_3 = 3		/*  0&quot;512  */
} TDA182I4_AGC5_Do_step_t, *pTDA182I4_AGC5_Do_step_t;

typedef enum _TDA182I4_AGC5_Gain_Item_t {
    TDA182I4_AGC5_Gain_MINUS6_VALUE_0 = 0,		/*  -6  */
    TDA182I4_AGC5_Gain_MINUS3_VALUE_1 = 1,		/*  -3  */
    TDA182I4_AGC5_Gain_0_VALUE_2 = 2,		/*  0  */
    TDA182I4_AGC5_Gain_3_VALUE_3 = 3,		/*  3  */
    TDA182I4_AGC5_Gain_6_VALUE_4 = 4,		/*  6  */
    TDA182I4_AGC5_Gain_9_VALUE_5 = 5,		/*  9  */
    TDA182I4_AGC5_Gain_12_VALUE_6 = 6,		/*  12  */
    TDA182I4_AGC5_Gain_15_VALUE_7 = 7		/*  15  */
} TDA182I4_AGC5_Gain_t, *pTDA182I4_AGC5_Gain_t;

/* TDA182I4 Register AGC5_byte_2 0x32 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2;
/* AGC5_loop_off bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__AGC5_loop_off;
/* AGC5_Do_step bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__AGC5_Do_step;
/* Force_AGC5_gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__Force_AGC5_gain;
/* AGC5_Gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC5_byte_2__AGC5_Gain;


typedef enum _TDA182I4_RFCAL_Offset_Cprog0_Item_t {
    TDA182I4_RFCAL_Offset_Cprog0_15_VALUE_0 = 0,		/*  15  */
    TDA182I4_RFCAL_Offset_Cprog0_0_VALUE_1 = 1,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog0_10_VALUE_2 = 2,		/*  10  */
    TDA182I4_RFCAL_Offset_Cprog0_17_VALUE_3 = 3		/*  17  */
} TDA182I4_RFCAL_Offset_Cprog0_t, *pTDA182I4_RFCAL_Offset_Cprog0_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog1_Item_t {
    TDA182I4_RFCAL_Offset_Cprog1_1_VALUE_0 = 0,		/*  1  */
    TDA182I4_RFCAL_Offset_Cprog1_0_VALUE_1 = 1,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog1_MINUS2_VALUE_2 = 2,		/*  -2  */
    TDA182I4_RFCAL_Offset_Cprog1_MINUS3_VALUE_3 = 3		/*  -3  */
} TDA182I4_RFCAL_Offset_Cprog1_t, *pTDA182I4_RFCAL_Offset_Cprog1_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog2_Item_t {
    TDA182I4_RFCAL_Offset_Cprog2_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog2_MINUS1_VALUE_1 = 1,		/*  -1  */
    TDA182I4_RFCAL_Offset_Cprog2_1_VALUE_2 = 2,		/*  1  */
    TDA182I4_RFCAL_Offset_Cprog2_2_VALUE_3 = 3		/*  2  */
} TDA182I4_RFCAL_Offset_Cprog2_t, *pTDA182I4_RFCAL_Offset_Cprog2_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog3_Item_t {
    TDA182I4_RFCAL_Offset_Cprog3_3_VALUE_0 = 0,		/*  3  */
    TDA182I4_RFCAL_Offset_Cprog3_0_VALUE_1 = 1,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog3_1_VALUE_2 = 2,		/*  1  */
    TDA182I4_RFCAL_Offset_Cprog3_2_VALUE_3 = 3		/*  2  */
} TDA182I4_RFCAL_Offset_Cprog3_t, *pTDA182I4_RFCAL_Offset_Cprog3_t;

/* TDA182I4 Register RF_Cal_byte_1 0x33 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1;
/* RFCAL_Offset_Cprog0 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog0;
/* RFCAL_Offset_Cprog1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog1;
/* RFCAL_Offset_Cprog2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog2;
/* RFCAL_Offset_Cprog3 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_1__RFCAL_Offset_Cprog3;


typedef enum _TDA182I4_RFCAL_Offset_Cprog4_Item_t {
    TDA182I4_RFCAL_Offset_Cprog4_3_VALUE_0 = 0,		/*  3  */
    TDA182I4_RFCAL_Offset_Cprog4_0_VALUE_1 = 1,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog4_1_VALUE_2 = 2,		/*  1  */
    TDA182I4_RFCAL_Offset_Cprog4_2_VALUE_3 = 3		/*  2  */
} TDA182I4_RFCAL_Offset_Cprog4_t, *pTDA182I4_RFCAL_Offset_Cprog4_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog5_Item_t {
    TDA182I4_RFCAL_Offset_Cprog5_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog5_MINUS1_VALUE_1 = 1,		/*  -1  */
    TDA182I4_RFCAL_Offset_Cprog5_1_VALUE_2 = 2,		/*  1  */
    TDA182I4_RFCAL_Offset_Cprog5_2_VALUE_3 = 3		/*  2  */
} TDA182I4_RFCAL_Offset_Cprog5_t, *pTDA182I4_RFCAL_Offset_Cprog5_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog6_Item_t {
    TDA182I4_RFCAL_Offset_Cprog6_MINUS2_VALUE_0 = 0,		/*  -2  */
    TDA182I4_RFCAL_Offset_Cprog6_0_VALUE_1 = 1,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog6_MINUS1_VALUE_2 = 2,		/*  -1  */
    TDA182I4_RFCAL_Offset_Cprog6_1_VALUE_3 = 3		/*  1  */
} TDA182I4_RFCAL_Offset_Cprog6_t, *pTDA182I4_RFCAL_Offset_Cprog6_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog7_Item_t {
    TDA182I4_RFCAL_Offset_Cprog7_0_VALUE_0 = 0,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog7_MINUS2_VALUE_1 = 1,		/*  -2  */
    TDA182I4_RFCAL_Offset_Cprog7_MINUS3_VALUE_2 = 2,		/*  -3  */
    TDA182I4_RFCAL_Offset_Cprog7_1_VALUE_3 = 3		/*  1  */
} TDA182I4_RFCAL_Offset_Cprog7_t, *pTDA182I4_RFCAL_Offset_Cprog7_t;

/* TDA182I4 Register RF_Cal_byte_2 0x34 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2;
/* RFCAL_Offset_Cprog4 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog4;
/* RFCAL_Offset_Cprog5 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog5;
/* RFCAL_Offset_Cprog6 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog6;
/* RFCAL_Offset_Cprog7 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_2__RFCAL_Offset_Cprog7;


typedef enum _TDA182I4_RFCAL_Offset_Cprog8_Item_t {
    TDA182I4_RFCAL_Offset_Cprog8_MINUS1_VALUE_0 = 0,		/*  -1  */
    TDA182I4_RFCAL_Offset_Cprog8_0_VALUE_1 = 1,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog8_MINUS3_VALUE_2 = 2,		/*  -3  */
    TDA182I4_RFCAL_Offset_Cprog8_MINUS2_VALUE_3 = 3		/*  -2  */
} TDA182I4_RFCAL_Offset_Cprog8_t, *pTDA182I4_RFCAL_Offset_Cprog8_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog9_Item_t {
    TDA182I4_RFCAL_Offset_Cprog9_MINUS6_VALUE_0 = 0,		/*  -6  */
    TDA182I4_RFCAL_Offset_Cprog9_MINUS3_VALUE_1 = 1,		/*  -3  */
    TDA182I4_RFCAL_Offset_Cprog9_0_VALUE_2 = 2,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog9_MINUS5_VALUE_3 = 3		/*  -5  */
} TDA182I4_RFCAL_Offset_Cprog9_t, *pTDA182I4_RFCAL_Offset_Cprog9_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog10_Item_t {
    TDA182I4_RFCAL_Offset_Cprog10_MINUS6_VALUE_0 = 0,		/*  -6  */
    TDA182I4_RFCAL_Offset_Cprog10_MINUS3_VALUE_1 = 1,		/*  -3  */
    TDA182I4_RFCAL_Offset_Cprog10_0_VALUE_2 = 2,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog10_MINUS5_VALUE_3 = 3		/*  -5  */
} TDA182I4_RFCAL_Offset_Cprog10_t, *pTDA182I4_RFCAL_Offset_Cprog10_t;

typedef enum _TDA182I4_RFCAL_Offset_Cprog11_Item_t {
    TDA182I4_RFCAL_Offset_Cprog11_MINUS5_VALUE_0 = 0,		/*  -5  */
    TDA182I4_RFCAL_Offset_Cprog11_MINUS2_VALUE_1 = 1,		/*  -2  */
    TDA182I4_RFCAL_Offset_Cprog11_0_VALUE_2 = 2,		/*  0  */
    TDA182I4_RFCAL_Offset_Cprog11_MINUS4_VALUE_3 = 3		/*  -4  */
} TDA182I4_RFCAL_Offset_Cprog11_t, *pTDA182I4_RFCAL_Offset_Cprog11_t;

/* TDA182I4 Register RF_Cal_byte_3 0x35 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3;
/* RFCAL_Offset_Cprog8 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog8;
/* RFCAL_Offset_Cprog9 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog9;
/* RFCAL_Offset_Cprog10 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog10;
/* RFCAL_Offset_Cprog11 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Cal_byte_3__RFCAL_Offset_Cprog11;


typedef enum _TDA182I4_IM2_LPF_Fc_Item_t {
    TDA182I4_IM2_LPF_Fc_LPF2_VALUE_0 = 0,		/*  LPF2  */
    TDA182I4_IM2_LPF_Fc_NOT_USED_VALUE_1 = 1,		/*  Not used  */
    TDA182I4_IM2_LPF_Fc_LPF1_VALUE_2 = 2,		/*  LPF1  */
    TDA182I4_IM2_LPF_Fc_LPF0_VALUE_3 = 3		/*  LPF0  */
} TDA182I4_IM2_LPF_Fc_t, *pTDA182I4_IM2_LPF_Fc_t;

typedef enum _TDA182I4_IM2_HPF_Fc_Item_t {
    TDA182I4_IM2_HPF_Fc_HPF0_VALUE_0 = 0,		/*  HPF0  */
    TDA182I4_IM2_HPF_Fc_HPF1_VALUE_1 = 1		/*  HPF1  */
} TDA182I4_IM2_HPF_Fc_t, *pTDA182I4_IM2_HPF_Fc_t;

typedef enum _TDA182I4_IM2_Filter_SubBand_Item_t {
    TDA182I4_IM2_Filter_SubBand_LPF0_135_7MHZ_LPF1_210_4MHZ_HPF0_431_6MHZ_VALUE_0 = 0,		/*  LPF0_135&quot;7MHz_LPF1_210&quot;4MHz_HPF0_431&quot;6MHz  */
    TDA182I4_IM2_Filter_SubBand_LPF0_141_8MHZ_LPF1_222_7MHZ_HPF0_456_2MHZ_VALUE_1 = 1,		/*  LPF0_141&quot;8MHz_LPF1_222&quot;7MHz_HPF0_456&quot;2MHz  */
    TDA182I4_IM2_Filter_SubBand_LPF0_148_0MHZ_LPF1_235_0MHZ_HPF0_480_8MHZ_VALUE_2 = 2,		/*  LPF0_148&quot;0MHz _LPF1_235&quot;0MHz_HPF0_480&quot;8MHz  */
    TDA182I4_IM2_Filter_SubBand_LPF0_154_1MHZ_LPF1_247_3MHZ_HPF0_505_3MHZ_VALUE_3 = 3		/*  LPF0_154&quot;1MHz_LPF1_247&quot;3MHz_HPF0_505&quot;3MHz  */
} TDA182I4_IM2_Filter_SubBand_t, *pTDA182I4_IM2_Filter_SubBand_t;

/* TDA182I4 Register Bandsplit_Filter_byte 0x36 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte;
/* IM2_Filter_Bypass bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_Filter_Bypass;
/* IM2_LPF_Fc bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_LPF_Fc;
/* IM2_HPF_Fc bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_HPF_Fc;
/* IM2_LPF_PD bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_LPF_PD;
/* IM2_HPF_PD bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_HPF_PD;
/* IM2_Filter_SubBand bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Bandsplit_Filter_byte__IM2_Filter_SubBand;


typedef enum _TDA182I4_RF_Filter_Gv_Item_t {
    TDA182I4_RF_Filter_Gv_MINUS11_VALUE_0 = 0,		/*  -11  */
    TDA182I4_RF_Filter_Gv_MINUS8_VALUE_1 = 1,		/*  -8  */
    TDA182I4_RF_Filter_Gv_MINUS5_VALUE_2 = 2,		/*  -5  */
    TDA182I4_RF_Filter_Gv_MINUS2_VALUE_3 = 3		/*  -2  */
} TDA182I4_RF_Filter_Gv_t, *pTDA182I4_RF_Filter_Gv_t;

typedef enum _TDA182I4_RF_Filter_Band_Item_t {
    TDA182I4_RF_Filter_Band_VHF_LOW_VALUE_0 = 0,		/*  VHF Low  */
    TDA182I4_RF_Filter_Band_VHF_HIGH_VALUE_1 = 1,		/*  VHF High  */
    TDA182I4_RF_Filter_Band_UHF_LOW_VALUE_2 = 2,		/*  UHF Low  */
    TDA182I4_RF_Filter_Band_UHF_HIGH_VALUE_3 = 3		/*  UHF High  */
} TDA182I4_RF_Filter_Band_t, *pTDA182I4_RF_Filter_Band_t;

/* TDA182I4 Register RF_Filters_byte_1 0x37 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1;
/* RF_Filter_Bypass bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__RF_Filter_Bypass;
/* AGC2_loop_off bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__AGC2_loop_off;
/* Force_AGC2_gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__Force_AGC2_gain;
/* RF_Filter_Gv bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__RF_Filter_Gv;
/* RF_Filter_Band bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_1__RF_Filter_Band;


/* TDA182I4 Register RF_Filters_byte_2 0x38 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_2;
/* RF_Filter_Cap bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_2__RF_Filter_Cap;


typedef enum _TDA182I4_AGC2_Do_step_Item_t {
    TDA182I4_AGC2_Do_step_8_176_VALUE_0 = 0,		/*  8&quot;176  */
    TDA182I4_AGC2_Do_step_2_044_VALUE_1 = 1,		/*  2&quot;044  */
    TDA182I4_AGC2_Do_step_1_022_VALUE_2 = 2,		/*  1&quot;022  */
    TDA182I4_AGC2_Do_step_0_512_VALUE_3 = 3		/*  0&quot;512  */
} TDA182I4_AGC2_Do_step_t, *pTDA182I4_AGC2_Do_step_t;

/* TDA182I4 Register RF_Filters_byte_3 0x39 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_3;
/* AGC2_Do_step bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_3__AGC2_Do_step;
/* Gain_Taper bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Filters_byte_3__Gain_Taper;


typedef enum _TDA182I4_RF_BPF_Item_t {
    TDA182I4_RF_BPF_FILTER1_0MINUS62MHZ_VALUE_0 = 0,		/*  Filter1 (0-62MHz)  */
    TDA182I4_RF_BPF_FILTER2_62MINUS87MHZ_VALUE_1 = 1,		/*  Filter2 (62-87MHz)  */
    TDA182I4_RF_BPF_FILTER3_87MINUS123MHZ_VALUE_2 = 2,		/*  Filter3 (87-123MHz)  */
    TDA182I4_RF_BPF_FILTER4_123MINUS173MHZ_VALUE_3 = 3,		/*  Filter4 (123-173MHz)  */
    TDA182I4_RF_BPF_FILTER5_173MINUS244MHZ_VALUE_4 = 4,		/*  Filter5 (173-244MHz)  */
    TDA182I4_RF_BPF_FILTER6_244MINUS290MHZ_VALUE_5 = 5,		/*  Filter6 (244-290MHz)  */
    TDA182I4_RF_BPF_FILTER7_290MINUS999MHZ_VALUE_6 = 6		/*  Filter7 (290-999MHz)  */
} TDA182I4_RF_BPF_t, *pTDA182I4_RF_BPF_t;

/* TDA182I4 Register RF_Band_Pass_Filter_byte 0x3A */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Band_Pass_Filter_byte;
/* RF_BPF_Bypass bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Band_Pass_Filter_byte__RF_BPF_Bypass;
/* RF_BPF bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RF_Band_Pass_Filter_byte__RF_BPF;


/* TDA182I4 Register AGCs_DetOut_byte 0x3B */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte;
/* Up_AGC5 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC5;
/* Do_AGC5 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC5;
/* Up_AGC4 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC4;
/* Do_AGC4 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC4;
/* Up_AGC2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC2;
/* Do_AGC2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC2;
/* Up_AGC1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Up_AGC1;
/* Do_AGC1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGCs_DetOut_byte__Do_AGC1;


typedef enum _TDA182I4_AGC1_Top_Do_Read_Item_t {
    TDA182I4_AGC1_Top_Do_Read_85_MS_VALUE_0 = 0,		/*  85 ms  */
    TDA182I4_AGC1_Top_Do_Read_88_MS_VALUE_1 = 1,		/*  88 ms  */
    TDA182I4_AGC1_Top_Do_Read_90_MS_VALUE_2 = 2,		/*  90 ms  */
    TDA182I4_AGC1_Top_Do_Read_92_MS_VALUE_3 = 3,		/*  92 ms  */
    TDA182I4_AGC1_Top_Do_Read_94_MS_VALUE_4 = 4,		/*  94 ms  */
    TDA182I4_AGC1_Top_Do_Read_95_MS_VALUE_5 = 5,		/*  95 ms  */
    TDA182I4_AGC1_Top_Do_Read_97_MS_VALUE_6 = 6,		/*  97 ms  */
    TDA182I4_AGC1_Top_Do_Read_100_MS_VALUE_7 = 7		/*  100 ms  */
} TDA182I4_AGC1_Top_Do_Read_t, *pTDA182I4_AGC1_Top_Do_Read_t;

typedef enum _TDA182I4_AGC1_Top_Up_Read_Item_t {
    TDA182I4_AGC1_Top_Up_Read_79_MS_VALUE_0 = 0,		/*  79 ms  */
    TDA182I4_AGC1_Top_Up_Read_82_MS_VALUE_1 = 1,		/*  82 ms  */
    TDA182I4_AGC1_Top_Up_Read_84_MS_VALUE_2 = 2,		/*  84 ms  */
    TDA182I4_AGC1_Top_Up_Read_86_MS_VALUE_3 = 3,		/*  86 ms  */
    TDA182I4_AGC1_Top_Up_Read_89_MS_VALUE_4 = 4,		/*  89 ms  */
    TDA182I4_AGC1_Top_Up_Read_91_MS_VALUE_5 = 5,		/*  91 ms  */
    TDA182I4_AGC1_Top_Up_Read_94_MS_VALUE_6 = 6		/*  94 ms  */
} TDA182I4_AGC1_Top_Up_Read_t, *pTDA182I4_AGC1_Top_Up_Read_t;

/* TDA182I4 Register AGC1_Top_byte 0x3C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte;
/* AGC1_Smooth_Transition_ON bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte__AGC1_Smooth_Transition_ON;
/* AGC1_Top_Do_Read bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte__AGC1_Top_Do_Read;
/* AGC1_Top_Up_Read bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_AGC1_Top_byte__AGC1_Top_Up_Read;


typedef enum _TDA182I4_LT_Gain_Read_Item_t {
    TDA182I4_LT_Gain_Read_MINUS4_5_DB_VALUE_0 = 0,		/*  -4&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS4_5_DB_VALUE_1 = 1,		/*  -4&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS4_5_DB_VALUE_2 = 2,		/*  -4&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS7_5_DB_VALUE_3 = 3,		/*  -7&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS10_5_DB_VALUE_4 = 4,		/*  -10&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS13_5_DB_VALUE_5 = 5,		/*  -13&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS16_5_DB_VALUE_6 = 6,		/*  -16&quot;5 dB  */
    TDA182I4_LT_Gain_Read_MINUS19_5_DB_VALUE_7 = 7		/*  -19&quot;5 dB  */
} TDA182I4_LT_Gain_Read_t, *pTDA182I4_LT_Gain_Read_t;

/* TDA182I4 Register LT_Gain_byte_1 0x3D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_Gain_byte_1;
/* LT_Gain_Read bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_LT_Gain_byte_1__LT_Gain_Read;


/* TDA182I4 Register RFAGCs_Gain_byte_3 0x3E */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_3;
/* AGC2_Gain_Read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_3__AGC2_Gain_Read;
/* AGC1_Gain_Read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_3__AGC1_Gain_Read;


/* TDA182I4 Register RFAGCs_Gain_byte_4 0x3F */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_4;
/* Cprog_Read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_4__Cprog_Read;


/* TDA182I4 Register RFAGCs_Gain_byte_5 0x40 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5;
/* RFAGC_Read_K_8 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__RFAGC_Read_K_8;
/* Do_AGC1bis bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__Do_AGC1bis;
/* Do_AGC3_Peak bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__Do_AGC3_Peak;
/* TOP_Agc3_read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_5__TOP_Agc3_read;


/* TDA182I4 Register RFAGCs_Gain_byte_6 0x41 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_6;
/* RFAGC_Read_K bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RFAGCs_Gain_byte_6__RFAGC_Read_K;


/* TDA182I4 Register IFAGCs_Gain_byte 0x42 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IFAGCs_Gain_byte;
/* AGC5_Gain_Read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IFAGCs_Gain_byte__AGC5_Gain_Read;
/* AGC4_Gain_Read bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IFAGCs_Gain_byte__AGC4_Gain_Read;


/* TDA182I4 Register RSSI_byte_1 0x43 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_1;
/* RSSI bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_1__RSSI;


typedef enum _TDA182I4_RSSI_Cap_Val_Item_t {
    TDA182I4_RSSI_Cap_Val_0_5PF_VALUE_0 = 0,		/*  0&quot;5pF  */
    TDA182I4_RSSI_Cap_Val_3PF_VALUE_1 = 1		/*  3pF  */
} TDA182I4_RSSI_Cap_Val_t, *pTDA182I4_RSSI_Cap_Val_t;

typedef enum _TDA182I4_RSSI_Ck_Speed_Item_t {
    TDA182I4_RSSI_Ck_Speed_31_25KHZ_VALUE_0 = 0,		/*  31&quot;25kHz  */
    TDA182I4_RSSI_Ck_Speed_62_5KHZ_VALUE_1 = 1		/*  62&quot;5kHz  */
} TDA182I4_RSSI_Ck_Speed_t, *pTDA182I4_RSSI_Ck_Speed_t;

/* TDA182I4 Register RSSI_byte_2 0x44 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2;
/* RSSI_AV bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_AV;
/* RSSI_Cap_Reset_En bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Cap_Reset_En;
/* RSSI_Cap_Val bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Cap_Val;
/* RSSI_Ck_Speed bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Ck_Speed;
/* RSSI_Dicho_not bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RSSI_byte_2__RSSI_Dicho_not;


/* TDA182I4 Register IRQ_Ctrl_byte 0x45 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte;
/* DDS_Polarity bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte__DDS_Polarity;
/* IRQ_Mode bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte__IRQ_Mode;
/* IRQ_Polarity bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IRQ_Ctrl_byte__IRQ_Polarity;


/* TDA182I4 Register Dummy_byte 0x46 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Dummy_byte;
/* Dummy bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Dummy_byte__Dummy;


/* TDA182I4 Register rfcal_log_0 0x47 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_0;
/* rfcal_log_0 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_0__rfcal_log_0;


/* TDA182I4 Register rfcal_log_1 0x48 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_1;
/* rfcal_log_1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_1__rfcal_log_1;


/* TDA182I4 Register rfcal_log_2 0x49 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_2;
/* rfcal_log_2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_2__rfcal_log_2;


/* TDA182I4 Register rfcal_log_3 0x4A */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_3;
/* rfcal_log_3 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_3__rfcal_log_3;


/* TDA182I4 Register rfcal_log_4 0x4B */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_4;
/* rfcal_log_4 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_4__rfcal_log_4;


/* TDA182I4 Register rfcal_log_5 0x4C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_5;
/* rfcal_log_5 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_5__rfcal_log_5;


/* TDA182I4 Register rfcal_log_6 0x4D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_6;
/* rfcal_log_6 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_6__rfcal_log_6;


/* TDA182I4 Register rfcal_log_7 0x4E */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_7;
/* rfcal_log_7 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_7__rfcal_log_7;


/* TDA182I4 Register rfcal_log_8 0x4F */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_8;
/* rfcal_log_8 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_8__rfcal_log_8;


/* TDA182I4 Register rfcal_log_9 0x50 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_9;
/* rfcal_log_9 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_9__rfcal_log_9;


/* TDA182I4 Register rfcal_log_10 0x51 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_10;
/* rfcal_log_10 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_10__rfcal_log_10;


/* TDA182I4 Register rfcal_log_11 0x52 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_11;
/* rfcal_log_11 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_rfcal_log_11__rfcal_log_11;


typedef enum _TDA182I4_LOPostDiv_Item_t {
    TDA182I4_LOPostDiv_FORBIDDEN_VALUE_0 = 0,		/*  Forbidden  */
    TDA182I4_LOPostDiv_1_VALUE_1 = 1,		/*  1  */
    TDA182I4_LOPostDiv_2_VALUE_2 = 2,		/*  2  */
    TDA182I4_LOPostDiv_4_VALUE_3 = 3,		/*  4  */
    TDA182I4_LOPostDiv_8_VALUE_4 = 4,		/*  8  */
    TDA182I4_LOPostDiv_16_VALUE_5 = 5,		/*  16  */
    TDA182I4_LOPostDiv_TEST_MODE_6_VALUE_6 = 6,		/*  Test mode 6  */
    TDA182I4_LOPostDiv_TEST_MODE_7_VALUE_7 = 7		/*  Test mode 7  */
} TDA182I4_LOPostDiv_t, *pTDA182I4_LOPostDiv_t;

/* TDA182I4 Register Main_Post_Divider_byte 0x5B */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Main_Post_Divider_byte;
/* LOPostDiv bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Main_Post_Divider_byte__LOPostDiv;
/* LOPresc bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Main_Post_Divider_byte__LOPresc;


/* TDA182I4 Register Sigma_delta_byte_1 0x5C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_1;
/* LO_Int bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_1__LO_Int;


/* TDA182I4 Register Sigma_delta_byte_2 0x5D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_2;
/* LO_Frac_2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_2__LO_Frac_2;


/* TDA182I4 Register Sigma_delta_byte_3 0x5E */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_3;
/* LO_Frac_1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_3__LO_Frac_1;


/* TDA182I4 Register Sigma_delta_byte_4 0x5F */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_4;
/* LO_Frac_0 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_4__LO_Frac_0;


typedef enum _TDA182I4_LO_SetAll_Item_t {
    TDA182I4_LO_SetAll_NO_SYNCHONISATION_VALUE_0 = 0,		/*  No Synchonisation  */
    TDA182I4_LO_SetAll_SYNCHONISATION_WITH_REGISTER_AND_VSYNC_VALUE_1 = 1,		/*  Synchonisation with register &amp; VSYNC  */
    TDA182I4_LO_SetAll_SYNCHONISATION_WITH_REGISTER_ONLY_VALUE_2 = 2,		/*  Synchonisation with register only  */
    TDA182I4_LO_SetAll_NO_SYNCHONISATION_VALUE_3 = 3		/*  No Synchonisation  */
} TDA182I4_LO_SetAll_t, *pTDA182I4_LO_SetAll_t;

/* TDA182I4 Register Sigma_delta_byte_5 0x60 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5;
/* LO_SetAll bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5__LO_SetAll;
/* N_K_correct_manual bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5__N_K_correct_manual;
/* LO_Calc_Disable bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Sigma_delta_byte_5__LO_Calc_Disable;


/* TDA182I4 Register RC_Cal_byte_1 0x66 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1;
/* RC_Cal_bypass bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_bypass;
/* RC_Cal_Offset bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_Offset;
/* RC_Cal_force bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_RC_Cal_byte_1__RC_Cal_force;


typedef enum _TDA182I4_IR_Mixer_Gain_Item_t {
    TDA182I4_IR_Mixer_Gain_2_VALUE_0 = 0,		/*  2  */
    TDA182I4_IR_Mixer_Gain_5_VALUE_1 = 1,		/*  5  */
    TDA182I4_IR_Mixer_Gain_8_VALUE_2 = 2,		/*  8  */
    TDA182I4_IR_Mixer_Gain_11_VALUE_3 = 3,		/*  11  */
    TDA182I4_IR_Mixer_Gain_14_VALUE_4 = 4		/*  14  */
} TDA182I4_IR_Mixer_Gain_t, *pTDA182I4_IR_Mixer_Gain_t;

typedef enum _TDA182I4_IR_FreqPtr_Item_t {
    TDA182I4_IR_FreqPtr_NOT_USED_VALUE_0 = 0,		/*  NOT USED  */
    TDA182I4_IR_FreqPtr_LOW_VALUE_1 = 1,		/*  Low  */
    TDA182I4_IR_FreqPtr_MID_VALUE_2 = 2,		/*  Mid  */
    TDA182I4_IR_FreqPtr_HIGH_VALUE_3 = 3		/*  high  */
} TDA182I4_IR_FreqPtr_t, *pTDA182I4_IR_FreqPtr_t;

typedef enum _TDA182I4_IR_RxPtr_Item_t {
    TDA182I4_IR_RxPtr_R2I_VALUE_0 = 0,		/*  R2I  */
    TDA182I4_IR_RxPtr_R2Q_VALUE_1 = 1,		/*  R2Q  */
    TDA182I4_IR_RxPtr_R3IQN_VALUE_2 = 2,		/*  R3IQn  */
    TDA182I4_IR_RxPtr_R3INQ_VALUE_3 = 3		/*  R3InQ  */
} TDA182I4_IR_RxPtr_t, *pTDA182I4_IR_RxPtr_t;

/* TDA182I4 Register IR_Cal_byte_5 0x69 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5;
/* Mixer_Gain_Bypass bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__Mixer_Gain_Bypass;
/* IR_Mixer_Gain bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__IR_Mixer_Gain;
/* IR_FreqPtr bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__IR_FreqPtr;
/* IR_RxPtr bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_5__IR_RxPtr;


typedef enum _TDA182I4_IR_target_Item_t {
    TDA182I4_IR_target_67_DB_VALUE_0 = 0,		/*  67 dB  */
    TDA182I4_IR_target_69_DB_VALUE_1 = 1,		/*  69 dB  */
    TDA182I4_IR_target_71_DB_VALUE_2 = 2,		/*  71 dB  */
    TDA182I4_IR_target_73_DB_VALUE_3 = 3		/*  73 dB  */
} TDA182I4_IR_target_t, *pTDA182I4_IR_target_t;

/* TDA182I4 Register IR_Cal_byte_6 0x6A */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6;
/* Rx_Force bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6__Rx_Force;
/* IR_target bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6__IR_target;
/* Rx_bp bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_IR_Cal_byte_6__Rx_bp;


typedef enum _TDA182I4_S2B_Dcboost_Item_t {
    TDA182I4_S2B_Dcboost_1_87_VALUE_0 = 0,		/*  1&quot;87  */
    TDA182I4_S2B_Dcboost_1_77_VALUE_1 = 1,		/*  1&quot;77  */
    TDA182I4_S2B_Dcboost_2_06_VALUE_2 = 2,		/*  2&quot;06  */
    TDA182I4_S2B_Dcboost_2_05_VALUE_3 = 3		/*  2&quot;05  */
} TDA182I4_S2B_Dcboost_t, *pTDA182I4_S2B_Dcboost_t;

/* TDA182I4 Register Power_Down_byte_1 0x6C */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1;
/* S2B_Dcboost bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__S2B_Dcboost;
/* PD_Lotest bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__PD_Lotest;
/* PD_Synthe bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__PD_Synthe;
/* PD_VCO bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_1__PD_VCO;


/* TDA182I4 Register Power_Down_byte_2 0x6D */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2;
/* PDRF_filter bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PDRF_filter;
/* PD_STOB_IF bit(s):  */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_STOB_IF;
/* PD_Det5 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det5;
/* PD_Det4 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det4;
/* PD_Det3 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det3;
/* PD_Det2 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det2;
/* PD_Det1 bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Power_Down_byte_2__PD_Det1;


/* TDA182I4 Register Charge_pump_byte 0x71 */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte;
/* ICP_Force_Sink bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP_Force_Sink;
/* ICP_Force_Src bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP_Force_Src;
/* ICP_offset bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP_offset;
/* ICP bit(s): ??? */
extern const TDA182I4_BitField_t gTDA182I4_Reg_Charge_pump_byte__ICP;



#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA182I4_REGDEF_H */
