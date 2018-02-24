/*
  Copyright (C) 2010 NXP B.V., All Rights Reserved.
  This source code and any compilation or derivative thereof is the proprietary
  information of NXP B.V. and is confidential in nature. Under no circumstances
  is this software to be  exposed to or placed under an Open Source License of
  any type without the expressed written permission of NXP B.V.
 *
 * \file          tmbslTDA182I4_Local.h
 *
 * \date          %modify_time%
 *
 * \author        David LEGENDRE
 *                Michael VANNIER
 *
 * \brief         Describe briefly the purpose of this file.
 *
 * REFERENCE DOCUMENTS :
 *                TDA182I4_Driver_User_Guide.pdf
 *
 * TVFE SW Arch V4 Template: Author Christophe CAZETTES
 *
 * \section info Change Information
 * \par Changelog
 *
 *
 * \par Version_Definition
 *  VERSION_TAG:TDA182I4_COMP_NUM.TDA182I4_MAJOR_VER.TDA182I4_MINOR_VER
 *
*/

#ifndef _TMBSL_TDA182I4_LOCAL_H
#define _TMBSL_TDA182I4_LOCAL_H

#ifdef __cplusplus
extern "C"
{
#endif

/*============================================================================*/
/* Types and defines:                                                         */
/*============================================================================*/


/* Driver version definition */
#define TDA182I4_COMP_NUM  1  /* Major protocol change - Specification change required */
#define TDA182I4_MAJOR_VER 0  /* Minor protocol change - Specification change required */
#define TDA182I4_MINOR_VER 8  /* Software update - No protocol change - No specification change required */

/* Instance macros */
#define P_OBJ_VALID                             (pObj != Null)

/* I/O Functions macros */
#define P_SIO                                   pObj->sIo
#define P_SIO_READ                              P_SIO.Read
#define P_SIO_WRITE                             P_SIO.Write
#define P_SIO_READ_VALID                        (P_OBJ_VALID && (P_SIO_READ != Null))
#define P_SIO_WRITE_VALID                       (P_OBJ_VALID && (P_SIO_WRITE != Null))

/* Time Functions macros */
#define P_STIME                                 pObj->sTime
#define P_STIME_WAIT                            P_STIME.Wait
#define P_STIME_WAIT_VALID                      (P_OBJ_VALID && (P_STIME_WAIT != Null))

/* Debug Functions macros */
#define P_SDEBUG                                pObj->sDebug
#define P_DBGPRINTEx                            P_SDEBUG.Print
#define P_DBGPRINTVALID                         (P_OBJ_VALID && (P_DBGPRINTEx != Null))

/* Mutex Functions macros */
#define P_SMUTEX                                pObj->sMutex
#ifdef _TVFE_SW_ARCH_V4
 #define P_SMUTEX_OPEN                           P_SMUTEX.Open
 #define P_SMUTEX_CLOSE                          P_SMUTEX.Close
#else
 #define P_SMUTEX_OPEN                           P_SMUTEX.Init
 #define P_SMUTEX_CLOSE                          P_SMUTEX.DeInit
#endif
#define P_SMUTEX_ACQUIRE                        P_SMUTEX.Acquire
#define P_SMUTEX_RELEASE                        P_SMUTEX.Release

#define P_SMUTEX_OPEN_VALID                     (P_OBJ_VALID && (P_SMUTEX_OPEN != Null))
#define P_SMUTEX_CLOSE_VALID                    (P_OBJ_VALID && (P_SMUTEX_CLOSE != Null))
#define P_SMUTEX_ACQUIRE_VALID                  (P_OBJ_VALID && (P_SMUTEX_ACQUIRE != Null))
#define P_SMUTEX_RELEASE_VALID                  (P_OBJ_VALID && (P_SMUTEX_RELEASE != Null))

/* Driver Mutex macros */
#define TDA182I4_MUTEX_TIMEOUT                  (5000)
#define P_MUTEX                                 pObj->pMutex
#define P_MUTEX_VALID                           (P_MUTEX != Null)

#ifdef _TVFE_IMPLEMENT_MUTEX
 #define _MUTEX_ACQUIRE(_NAME) \
     if(err == TM_OK) \
     { \
         /* Try to acquire driver mutex */ \
         err = i##_NAME##_MutexAcquire(pObj, _NAME##_MUTEX_TIMEOUT); \
     } \
     if(err == TM_OK) \
     {

 #define _MUTEX_RELEASE(_NAME) \
         (void)i##_NAME##_MutexRelease(pObj); \
     }
#else
 #define _MUTEX_ACQUIRE(_NAME) \
     if(err == TM_OK) \
     {

 #define _MUTEX_RELEASE(_NAME) \
     }
#endif

    
#define TDA182I4_INSTANCE_REGMAP_DEF \
    { \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
        0, 0, 0, 0, 0, 0 \
    }


/* TDA182I4 Driver State Machine */
typedef enum _TDA182I4HwState_t {
    TDA182I4_HwState_Unknown = 0,   /* Hw State Unknown */
    TDA182I4_HwState_InitNotDone,   /* Hw Init Not Done */
    TDA182I4_HwState_InitPending,   /* Hw Init Pending */
    TDA182I4_HwState_InitDone,      /* Hw Init Done */
    TDA182I4_HwState_SetStdDone,    /* Set Standard Done */
    TDA182I4_HwState_SetRFDone,     /* Set RF Done */
    TDA182I4_HwState_SetFineRFDone, /* Set Fine RF Done */
    TDA182I4_HwState_Max
} TDA182I4HwState_t, *pTDA182I4HwState_t;

typedef enum _TDA182I4HwStateCaller_t {
    TDA182I4_HwStateCaller_Unknown = 0, /* Caller Unknown */
    TDA182I4_HwStateCaller_SetPower,    /* Caller SetPowerState */
    TDA182I4_HwStateCaller_HwInit,      /* Caller HwInit */
    TDA182I4_HwStateCaller_SetStd,      /* Caller SetStandardMode */
    TDA182I4_HwStateCaller_SetRF,       /* Caller SetRF */
    TDA182I4_HwStateCaller_SetFineRF,   /* Caller SetFineRF */
    TDA182I4_HwStateCaller_GetRSSI,     /* Caller GetRSSI */
    TDA182I4_HwStateCaller_SetRawRF,    /* Caller SetRawRF */
    TDA182I4_HwStateCaller_Max
} TDA182I4HwStateCaller_t, *pTDA182I4HwStateCaller_t;

/* TDA182I4 specific IRQ clear: */
typedef enum _TDA182I4IRQ_t {
    TDA182I4_IRQ_MSM_RCCal      = 0x01, /* MSM_RCCal bit */
    TDA182I4_IRQ_MSM_IRCAL      = 0x02, /* MSM_IRCAL bit */
    TDA182I4_IRQ_MSM_RFCal      = 0x04, /* MSM_RFCal bit */
    TDA182I4_IRQ_MSM_LOCalc     = 0x08, /* MSM_LOCalc bit */
    TDA182I4_IRQ_MSM_RSSI       = 0x10, /* MSM_RSSI bit */
    TDA182I4_IRQ_XtalCal        = 0x20, /* XtalCal bit */
    TDA182I4_IRQ_Global         = 0x80, /* IRQ_status bit */
    TDA182I4_IRQ_HwInit         =   TDA182I4_IRQ_MSM_RCCal\
                                    |TDA182I4_IRQ_MSM_IRCAL\
                                    |TDA182I4_IRQ_MSM_RFCal\
                                    |TDA182I4_IRQ_MSM_LOCalc\
                                    |TDA182I4_IRQ_MSM_RSSI,
    TDA182I4_IRQ_IrCal          = TDA182I4_IRQ_MSM_IRCAL\
                                    |TDA182I4_IRQ_MSM_LOCalc\
                                    |TDA182I4_IRQ_MSM_RSSI,
    TDA182I4_IRQ_SetRF          = TDA182I4_IRQ_MSM_RFCal\
                                    |TDA182I4_IRQ_MSM_LOCalc,
    TDA182I4_IRQ_GetPowerLevel  = TDA182I4_IRQ_MSM_RSSI
} TDA182I4IRQ_t, *pTDA182I4IRQ_t;

/* TDA182I4 specific MSM: */
typedef enum _TDA182I4MSM_t {
    TDA182I4_MSM_Calc_PLL       = 0x01, /* Calc_PLL  bit */
    TDA182I4_MSM_RC_Cal         = 0x02, /* RC_Cal bit */ 
    TDA182I4_MSM_RF_CAL         = 0x04, /* RF_CAL bit */ 
    TDA182I4_MSM_RF_CAL_AV      = 0x08, /* RF_CAL_AV bit */
    TDA182I4_MSM_IR_CAL_Wanted  = 0x10, /* IR_CAL_Wanted bit */
    TDA182I4_MSM_IR_Cal_Image   = 0x20, /* IR_Cal_Image bit */
    TDA182I4_MSM_IR_CAL_Loop    = 0x40, /* IR_CAL_Loop bit */
    TDA182I4_MSM_RSSI_Meas      = 0x80, /* RSSI_Meas bit */
    /* Performs all CALs */
    TDA182I4_MSM_HwInit         = \
                                    TDA182I4_MSM_RC_Cal \
                                    |TDA182I4_MSM_RF_CAL\
                                    |TDA182I4_MSM_IR_Cal_Image\
                                    |TDA182I4_MSM_IR_CAL_Loop,
    /* Performs all IR_CAL */
    TDA182I4_MSM_IrCal          = TDA182I4_MSM_IR_Cal_Image\
                                    |TDA182I4_MSM_IR_CAL_Loop,
    TDA182I4_MSM_SetRF          = TDA182I4_MSM_Calc_PLL\
                                    |TDA182I4_MSM_RF_CAL_AV,
    TDA182I4_MSM_GetPowerLevel  = TDA182I4_MSM_RSSI_Meas
} TDA182I4MSM_t, *pTDA182I4MSM_t;

/* TDA182I4 Standard settings: */
typedef enum _TDA182I4LPF_t {
    TDA182I4_LPF_6MHz = 0,  /* 6MHz LPFc */
    TDA182I4_LPF_7MHz,      /* 7MHz LPFc */
    TDA182I4_LPF_8MHz,      /* 8MHz LPFc */
    TDA182I4_LPF_9MHz,      /* 9MHz LPFc */
    TDA182I4_LPF_10MHz,     /* 10MHz LPFc */
    TDA182I4_LPF_11_2MHz,   /* 11.2MHz LPFc */
    TDA182I4_LPF_1_5MHz,    /* 1.5MHz LPFc */
    TDA182I4_LPF_1_5MHzbis, /* 1.5MHz LPFc */
    TDA182I4_LPF_Max
} TDA182I4LPF_t, *pTDA182I4LPF_t;

typedef enum _TDA182I4LPFOffset_t {
    TDA182I4_LPFOffset_0pc = 0,    /* LPFc 0%   */
    TDA182I4_LPFOffset_plus_4pc = 0x10,   /* LPFc 4%   */
    TDA182I4_LPFOffset_plus_8pc = 0x20,   /* LPFc 8%   */
    TDA182I4_LPFOffset_plus_12pc = 0x30,  /* LPFc 12%  */
    TDA182I4_LPFOffset_0pcbis = 0x01,     /* LPFc 0%   */
    TDA182I4_LPFOffset_min_4pc = 0x11,    /* LPFc -4%  */
    TDA182I4_LPFOffset_min_8pc = 0x21,    /* LPFc -8%  */
    TDA182I4_LPFOffset_min_12pc = 0x31 ,   /* LPFc -12% */
    TDA182I4_LPFOffset_Max
} TDA182I4LPFOffset_t, *pTDA182I4LPFOffset_t;

typedef enum TDA182I4DC_Notch_IF_PPF_t {
    TDA182I4_DC_Notch_IF_PPF_Disabled = 0,  /* IF Notch Disabled */
    TDA182I4_DC_Notch_IF_PPF_Enabled,       /* IF Notch Enabled */
    TDA182I4_DC_Notch_IF_PPF_Max
} TDA182I4DC_Notch_IF_PPF_t, *pTDA182I4DC_Notch_IF_PPF_t;

typedef enum _TDA182I4HPF_t {
    TDA182I4_HPF_Disabled = 0x00,   /* IF HPF disabled */
    TDA182I4_HPF_0_5MHz = 0x01,         /* IF HPF 0.5MHz   */
    TDA182I4_HPF_1MHz = 0x11,           /* IF HPF 1MHz     */
    TDA182I4_HPF_1_6MHz = 0x21,         /* IF HPF 1.6MHz   */
    TDA182I4_HPF_2_3MHz = 0x31,         /* IF HPF 2.3MHz   */
    TDA182I4_HPF_3_5MHz = 0x41,         /* IF HPF 3.5MHz   */
    TDA182I4_HPF_Max
} TDA182I4HPF_t, *pTDA182I4HPF_t;

typedef enum _TDA182I4HPFOffset_t {
    TDA182I4_HPFOffset_0pc = 0,    /* LPFc 0%   */
    TDA182I4_HPFOffset_plus_4pc = 0x10,   /* LPFc 4%   */
    TDA182I4_HPFOffset_plus_8pc = 0x20,   /* LPFc 8%   */
    TDA182I4_HPFOffset_plus_12pc = 0x30,  /* LPFc 12%  */
    TDA182I4_HPFOffset_0pcbis = 0x01,     /* LPFc 0%   */
    TDA182I4_HPFOffset_min_4pc = 0x11,    /* LPFc -4%  */
    TDA182I4_HPFOffset_min_8pc = 0x21,    /* LPFc -8%  */
    TDA182I4_HPFOffset_min_12pc = 0x31,   /* LPFc -12% */
    TDA182I4_HPFOffset_Max
} TDA182I4HPFOffset_t, *pTDA182I4HPFOffset_t;

typedef enum _TDA182I4IF_Notch_Freq_t {
    TDA182I4_IF_Notch_Freq_6_25MHz = 0,     /* IF Notch Freq 6.25MHz   */
    TDA182I4_IF_Notch_Freq_7_25MHz,         /* IF Notch Freq 7.25MHz   */
    TDA182I4_IF_Notch_Freq_8_25MHz,         /* IF Notch Freq 8.25MHz   */
    TDA182I4_IF_Notch_Freq_9_25MHz,         /* IF Notch Freq 9.25MHz   */
    TDA182I4_IF_Notch_Freq_10_25MHz,        /* IF Notch Freq 10.25MHz  */
    TDA182I4_IF_Notch_Freq_11_45MHz,        /* IF Notch Freq 11.45MHz  */
    TDA182I4_IF_Notch_Freq_Max
} TDA182I4IF_Notch_Freq_t, *pTDA182I4IF_Notch_Freq_t;

typedef enum _TDA182I4IF_Notch_Offset_t {
    TDA182I4_IF_Notch_Offset_0pc = 0,    /* IF Notch Offset 0%   */
    TDA182I4_IF_Notch_Offset_plus_4pc = 0x10,   /* IF Notch Offset 4%   */
    TDA182I4_IF_Notch_Offset_plus_8pc = 0x20,   /* IF Notch Offset 8%   */
    TDA182I4_IF_Notch_Offset_plus_12pc = 0x30,  /* IF Notch Offset 12%  */
    TDA182I4_IF_Notch_Offset_0pcbis = 0x01,     /* IF Notch Offset 0%   */
    TDA182I4_IF_Notch_Offset_min_4pc = 0x11,    /* IF Notch Offset -4%  */
    TDA182I4_IF_Notch_Offset_min_8pc = 0x21,    /* IF Notch Offset -8%  */
    TDA182I4_IF_Notch_Offset_min_12pc = 0x31 ,  /* IF Notch Offset -12% */
    TDA182I4_IF_Notch_Offset_Max
} TDA182I4IF_Notch_Offset_t, *pTDA182I4IF_Notch_Offset_t;

typedef enum _TDA182I4IF_Notch_Enable_t {
    TDA182I4_IF_Notch_Disabled = 0, /* IF Notch Disabled */
    TDA182I4_IF_Notch_Enabled,      /* IF Notch Enabled */
    TDA182I4_IF_Notch_Max
} TDA182I4IF_Notch_Enable_t, *pTDA182I4IF_Notch_Enable_t;

typedef enum _TDA182I4IFnotchToRSSI_t {
    TDA182I4_IFnotchToRSSI_Disabled = 0,    /* IFnotchToRSSI Disabled */
    TDA182I4_IFnotchToRSSI_Enabled,         /* IFnotchToRSSI Enabled */
    TDA182I4_IFnotchToRSSI_Max
} TDA182I4IFnotchToRSSI_t, *pTDA182I4IFnotchToRSSI_t;

typedef enum _TDA182I4AGC1_TOP_I2C_DN_UP_t {
    TDA182I4_AGC1_TOP_I2C_DN_UP_d85_u79dBuV = 0,    /* AGC1 TOP I2C DN/UP down 85 up 79 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d88_u82dBuV,        /* AGC1 TOP I2C DN/UP down 88 up 82 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d90_u84wdBuV,       /* AGC1 TOP I2C DN/UP down 90 up 84 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d92_u86dBuV,        /* AGC1 TOP I2C DN/UP down 92 up 86 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d95_u89dBuV,        /* AGC1 TOP I2C DN/UP down 95 up 89 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d97_u91dBuV,        /* AGC1 TOP I2C DN/UP down 97 up 91 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d100_u94dBuV,       /* AGC1 TOP I2C DN/UP down 100 up 94 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_d100_u94bisdBuV,    /* AGC1 TOP I2C DN/UP down 100 up 94 dBuV */
    TDA182I4_AGC1_TOP_I2C_DN_UP_Max
} TDA182I4AGC1_TOP_I2C_DN_UP_t, *pTDA182I4AGC1_TOP_I2C_DN_UP_t;

typedef enum _TDA182I4AGC1_TOP_STRATEGY_t {
    TDA182I4_AGC1_TOP_STRATEGY_0 = 0,               /* AGC1 TOP STRATEGY 0 */
    TDA182I4_AGC1_TOP_STRATEGY_1,                   /* AGC1 TOP STRATEGY 1 */
    TDA182I4_AGC1_TOP_STRATEGY_2,                   /* AGC1 TOP STRATEGY 2 */
    TDA182I4_AGC1_TOP_STRATEGY_3,                   /* AGC1 TOP STRATEGY 3 */
    TDA182I4_AGC1_TOP_STRATEGY_4,                   /* AGC1 TOP STRATEGY 4 */
    TDA182I4_AGC1_TOP_STRATEGY_5,                   /* AGC1 TOP STRATEGY 5 */
    TDA182I4_AGC1_TOP_STRATEGY_6,                   /* AGC1 TOP STRATEGY 6 */
    TDA182I4_AGC1_TOP_STRATEGY_7,                   /* AGC1 TOP STRATEGY 7 */
    TDA182I4_AGC1_TOP_STRATEGY_Max
} TDA182I4AGC1_TOP_STRATEGY_t, *pTDA182I4AGC1_TOP_STRATEGY_t;

typedef enum _TDA182I4LNA_RANGE_t {
    TDA182I4_LNA_RANGE_Minus11dB_Plus22dB = 0,      /* LNA RANGE -11dB 22dB */
    TDA182I4_LNA_RANGE_Minus8dB_Plus22dB,           /* LNA RANGE -8dB 22dB  */
    TDA182I4_LNA_RANGE_Plus7dB_Plus22dB,            /* LNA RANGE 7dB 22dB   */
    TDA182I4_LNA_RANGE_Plus7dB_Plus22dBbis,         /* LNA RANGE 7dB 22dB   */
    TDA182I4_LNA_RANGE_Max
} TDA182I4LNA_RANGE_t, *pTDA182I4LNA_RANGE_t;

typedef enum _TDA182I4AGC3_TOP_I2C_t {
    TDA182I4_AGC3_TOP_I2C_94dBuV = 0,   /* AGC3 TOP I2C 94 dBuV */
    TDA182I4_AGC3_TOP_I2C_96dBuV,       /* AGC3 TOP I2C 96 dBuV */
    TDA182I4_AGC3_TOP_I2C_98dBuV,       /* AGC3 TOP I2C 98 dBuV */
    TDA182I4_AGC3_TOP_I2C_100dBuV,      /* AGC3 TOP I2C 100 dBuV */
    TDA182I4_AGC3_TOP_I2C_102dBuV,      /* AGC3 TOP I2C 102 dBuV */
    TDA182I4_AGC3_TOP_I2C_104dBuV,      /* AGC3 TOP I2C 104 dBuV */
    TDA182I4_AGC3_TOP_I2C_106dBuV,      /* AGC3 TOP I2C 106 dBuV */
    TDA182I4_AGC3_TOP_I2C_107dBuV,      /* AGC3 TOP I2C 107 dBuV */
    TDA182I4_AGC3_TOP_I2C_Max
} TDA182I4AGC3_TOP_I2C_t, *pTDA182I4AGC3_TOP_I2C_t;

typedef enum _TDA182I4AGC4_TOP_DN_UP_t {
    TDA182I4_AGC4_TOP_DN_UP_d105_u99dBuV = 0,   /* AGC4 TOP DN/UP down 105 up 99 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d105_u100dBuV,      /* AGC4 TOP DN/UP down 105 up 100 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d105_u101dBuV,      /* AGC4 TOP DN/UP down 105 up 101 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d107_u101dBuV,      /* AGC4 TOP DN/UP down 107 up 101 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d107_u102dBuV,      /* AGC4 TOP DN/UP down 107 up 102 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d107_u103dBuV,      /* AGC4 TOP DN/UP down 107 up 103 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d108_u102dBuV,      /* AGC4 TOP DN/UP down 108 up 102 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d109_u103dBuV,      /* AGC4 TOP DN/UP down 109 up 103 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d109_u104dBuV,      /* AGC4 TOP DN/UP down 109 up 104 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d109_u105dBuV,      /* AGC4 TOP DN/UP down 109 up 105 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d110_u104dBuV,      /* AGC4 TOP DN/UP down 110 up 104 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d110_u105dBuV,      /* AGC4 TOP DN/UP down 110 up 105 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d110_u106dBuV,      /* AGC4 TOP DN/UP down 110 up 106 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d112_u106dBuV,      /* AGC4 TOP DN/UP down 112 up 106 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d112_u107dBuV,      /* AGC4 TOP DN/UP down 112 up 107 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_d112_u108dBuV,      /* AGC4 TOP DN/UP down 112 up 108 dBuV */
    TDA182I4_AGC4_TOP_DN_UP_Max
} TDA182I4AGC4_TOP_DN_UP_t, *pTDA182I4AGC4_TOP_DN_UP_t;

typedef enum _TDA182I4AGC5_TOP_DN_UP_t {
    TDA182I4_AGC5_TOP_DN_UP_d105_u99dBuV = 0,   /* AGC5 TOP DN/UP down 105 up 99 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d105_u100dBuV,      /* AGC5 TOP DN/UP down 105 up 100 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d105_u101dBuV,      /* AGC5 TOP DN/UP down 105 up 101 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d107_u101dBuV,      /* AGC5 TOP DN/UP down 107 up 101 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d107_u102dBuV,      /* AGC5 TOP DN/UP down 107 up 102 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d107_u103dBuV,      /* AGC5 TOP DN/UP down 107 up 103 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d108_u102dBuV,      /* AGC5 TOP DN/UP down 108 up 102 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d109_u103dBuV,      /* AGC5 TOP DN/UP down 109 up 103 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d109_u104dBuV,      /* AGC5 TOP DN/UP down 109 up 104 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d109_u105dBuV,      /* AGC5 TOP DN/UP down 109 up 105 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d110_u104dBuV,      /* AGC5 TOP DN/UP down 108 up 104 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d110_u105dBuV,      /* AGC5 TOP DN/UP down 108 up 105 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d110_u106dBuV,      /* AGC5 TOP DN/UP down 108 up 106 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d112_u106dBuV,      /* AGC5 TOP DN/UP down 108 up 106 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d112_u107dBuV,      /* AGC5 TOP DN/UP down 108 up 107 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_d112_u108dBuV,      /* AGC5 TOP DN/UP down 108 up 108 dBuV */
    TDA182I4_AGC5_TOP_DN_UP_Max
} TDA182I4AGC5_TOP_DN_UP_t, *pTDA182I4AGC5_TOP_DN_UP_t;

typedef enum _TDA182I4RSSI_HP_FC_t {
    TDA182I4_RSSI_HP_FC_0_3M = 0,               /* RSSI_HP_FC 0.3MHz  */
    TDA182I4_RSSI_HP_FC_2_25M,                  /* RSSI_HP_FC 2.25MHz */
    TDA182I4_RSSI_HP_FC_5M,                     /* RSSI_HP_FC 5MHz    */
    TDA182I4_RSSI_HP_FC_5Mbis,                  /* RSSI_HP_FC 5MHz    */
    TDA182I4_RSSI_HP_FC_Max
} TDA182I4RSSI_HP_FC_t, *pTDA182I4RSSI_HP_FC_t;

typedef enum _TDA182I4AGC5_HP_FC_t {
    TDA182I4_AGC5_HP_FC_0_3M = 0,               /* RSSI_HP_FC 0.3MHz  */
    TDA182I4_AGC5_HP_FC_2_25M,                  /* RSSI_HP_FC 2.25MHz */
    TDA182I4_AGC5_HP_FC_5M,                     /* RSSI_HP_FC 5MHz    */
    TDA182I4_AGC5_HP_FC_5Mbis,                  /* RSSI_HP_FC 5MHz    */
    TDA182I4_AGC5_HP_FC_Max 
} TDA182I4AGC5_HP_FC_t, *pTDA182I4AGC5_HP_FC_t;

typedef enum _TDA182I4AGC3_Top_Adapt_Algorithm {
    TDA182I4_Top_Adapt_NO_TOP_ADAPT = 0,    /* NO TOP ADAPT */
    TDA182I4_Top_Adapt_TOP_ADAPT35,         /* TOP ADAPT35  */
    TDA182I4_Top_Adapt_TOP_ADAPT34,         /* TOP ADAPT34  */
    TDA182I4_Top_Adapt_Max
} TDA182I4AGC3_Top_Adapt_Algorithm, *pTDA182I4AGC3_Top_Adapt_Algorithm;

typedef enum _TDA182I4AGC3_Adapt_TOP_t {
    TDA182I4_AGC3_Adapt_TOP_0_Step = 0, /* same level as AGC3 TOP  */
    TDA182I4_AGC3_Adapt_TOP_1_Step,     /* 1 level below AGC3 TOP  */
    TDA182I4_AGC3_Adapt_TOP_2_Step,     /* 2 level below AGC3 TOP  */
    TDA182I4_AGC3_Adapt_TOP_3_Step      /* 3 level below AGC3 TOP  */
} TDA182I4AGC3_Adapt_TOP_t, *pTDA182I4AGC3_Adapt_TOP_t;

#define TDA182I4_AGC3_ADAPT_TOP_FREQ_LIM 291000000

#define TDA182I4_Mode_LTO_Used 0x01
#define TDA182I4_Mode_STO_Used 0x02
#define TDA182I4_Mode_LTO_Not_Used 0x00
#define TDA182I4_Mode_STO_Not_Used 0x00

typedef enum _TDA182I4AGC_Overload_TOP_t {
    TDA182I4_AGC_Overload_TOP_plus_9_plus_3_5_min_3_5 = 0,  /* +9/+3.5/-3.5 */
    TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_4_5,      /* +9/+4.5/-4.5 */
    TDA182I4_AGC_Overload_TOP_plus_9_plus_4_5_min_3_5,      /* +9/+4.5/-3.5 */
    TDA182I4_AGC_Overload_TOP_plus_9_plus_6_min_4_5,        /* +9/+6/-4.5   */
    TDA182I4_AGC_Overload_TOP_plus_9_plus_6_min_6,          /* +9/+6/-6     */
    TDA182I4_AGC_Overload_TOP_plus_9_plus_6_min_9,          /* +9/+6/-9     */
    TDA182I4_AGC_Overload_TOP_plus_9_plus_7_5_min_9,        /* +9/+7.5/-9   */
    TDA182I4_AGC_Overload_TOP_plus_12_plus_7_5_min_9        /* +12/+7.5/-9   */
} TDA182I4AGC_Overload_TOP_t, *pTDA182I4AGC_Overload_TOP_t;

typedef enum _TDA182I4RF_Atten_3dB_t {
    TDA182I4_RF_Atten_3dB_Disabled = 0, /* RF_Atten_3dB Disabled */
    TDA182I4_RF_Atten_3dB_Enabled,      /* RF_Atten_3dB Enabled */
    TDA182I4_RF_Atten_3dB_Max
} TDA182I4RF_Atten_3dB_t, *pTDA182I4RF_Atten_3dB_t;

typedef enum _TDA182I4IF_Output_Level_t {
    TDA182I4_IF_Output_Level_2Vpp_0_30dB = 0,           /* 2Vpp       0 - 30dB      */
    TDA182I4_IF_Output_Level_1_25Vpp_min_4_26dB,        /* 1.25Vpp   -4 - 26dB      */
    TDA182I4_IF_Output_Level_1Vpp_min_6_24dB,           /* 1Vpp      -6 - 24dB      */
    TDA182I4_IF_Output_Level_0_8Vpp_min_8_22dB,         /* 0.8Vpp    -8 - 22dB      */
    TDA182I4_IF_Output_Level_0_85Vpp_min_7_5_22_5dB,    /* 0.85Vpp   -7.5 - 22.5dB  */
    TDA182I4_IF_Output_Level_0_7Vpp_min_9_21dB,         /* 0.7Vpp    -9 - 21dB      */
    TDA182I4_IF_Output_Level_0_6Vpp_min_10_3_19_7dB,    /* 0.6Vpp    -10.3 - 19.7dB */
    TDA182I4_IF_Output_Level_0_5Vpp_min_12_18dB,        /* 0.5Vpp    -12 - 18dB     */
    TDA182I4_IF_Output_Level_Max
} TDA182I4IF_Output_Level_t, *pTDA182I4IF_Output_Level_t;

typedef enum _TDA182I4S2D_Gain_t {
    TDA182I4_S2D_Gain_3dB = 0,  /* 3dB */
    TDA182I4_S2D_Gain_6dB,      /* 6dB */
    TDA182I4_S2D_Gain_9dB,      /* 9dB */
    TDA182I4_S2D_Gain_Max
} TDA182I4S2D_Gain_t, *pTDA182I4S2D_Gain_t;

typedef enum _TDA182I4Negative_Modulation_t {
    TDA182I4_Negative_Modulation_Disabled = 0,
    TDA182I4_Negative_Modulation_Enabled,
    TDA182I4_Negative_Modulation_Max
} TDA182I4Negative_Modulation_t, *pTDA182I4Negative_Modulation_t;

typedef enum _TDA182I4AGCK_Time_Constant_t {
    TDA182I4_AGCK_Time_Constant_1_STEP_EACH_VSYNC_RISING_EDGE = 0,  /* 1 Step Each VSYNC Rising Edge */
    TDA182I4_AGCK_Time_Constant_0_512ms,                            /* 0.512ms                       */
    TDA182I4_AGCK_Time_Constant_8_192ms,                            /* 8.192ms                       */
    TDA182I4_AGCK_Time_Constant_32_768ms,                           /* 32.768ms                      */
    TDA182I4_AGCK_Time_Constant_Max
} TDA182I4AGCK_Time_Constant_t, *pTDA182I4AGCK_Time_Constant_t;

typedef enum _TDA182I4VHF_III_Mode_t {
    TDA182I4_VHF_III_Mode_Disabled = 0, /* VHF_III_Mode Disabled */
    TDA182I4_VHF_III_Mode_Enabled,      /* VHF_III_Mode Enabled  */
    TDA182I4_VHF_III_Mode_Max
} TDA182I4VHF_III_Mode_t, *pTDA182I4VHF_III_Mode_t;

typedef enum _TDA182I4XTOutAmp_t {
    TDA182I4_XTOUT_Amp_400mV = 0,   /* 400mV */
    TDA182I4_XTOUT_Amp_800mV        /* 800mV */
} TDA182I4XTOutAmp_t, *pTDA182I4XTOutAmp_t;

typedef enum _TDA182I4PowerSavingMode_t {
    TDA182I4PowerSavingMode_normal = 0,   /* Set of normal consumption */
    TDA182I4PowerSavingMode_Low,          /* Set of low level comsuption   */
    TDA182I4PowerSavingMode_Max
} TDA182I4PowerSavingMode_t, *pTDA182I4PowerSavingMode_t;

typedef enum _TDA182I4AGC1_LNA_Zin_t {
    TDA182I4_AGC1_LNA_Zin_NF = 0,    /* NF optimzed  */
    TDA182I4_AGC1_LNA_Zin_S11,    /* S11 optimzed  */
    TDA182I4AGC1_LNA_ZinMax
} TDA182I4AGC1_LNA_Zin_t, *pTDA182I4AGC1_LNA_Zin_t;

typedef struct _TDA182I4StdCoefficients
{
    /****************************************************************/
    /* IF Settings                                                  */
    /****************************************************************/
    UInt32                                      IF;                         /* IF Frequency */
    Int32                                       CF_Offset;

    /****************************************************************/
    /* IF SELECTIVITY Settings                                      */
    /****************************************************************/
    TDA182I4LPF_t                               LPF;                        /* LPF Cut off */
    TDA182I4LPFOffset_t                         LPF_Offset;                 /* LPF offset */
    TDA182I4DC_Notch_IF_PPF_t                   DC_Notch_IF_PPF;            /* DC notch IF PPF */
    TDA182I4HPF_t                               HPF;                        /* Hi Pass */
    TDA182I4HPFOffset_t                         HPF_Offset;                 /* HPF offset */
    TDA182I4IF_Notch_Freq_t                     IF_Notch_Freq;              /* IF Notch Freq */
    TDA182I4IF_Notch_Offset_t                   IF_Notch_Offset;            /* IF Notch Offset */
    TDA182I4IF_Notch_Enable_t                   IF_Notch_Enable;            /* IF notch enable */
    TDA182I4IFnotchToRSSI_t                     IFnotchToRSSI;              /* IFnotchToRSSI */

    /****************************************************************/
    /* AGC TOP Settings                                             */
    /****************************************************************/
    TDA182I4AGC1_TOP_I2C_DN_UP_t                AGC1_TOP_I2C_DN_UP;         /* AGC1 TOP I2C DN/UP */
    TDA182I4AGC1_TOP_STRATEGY_t                 AGC1_TOP_STRATEGY;          /* AGC1 TOP STRATEGY */
    TDA182I4AGC1_LNA_Zin_t                      LNA_Zin;                    /* LNA_Zin */
    TDA182I4_RFAGC_Peak_Val_t					RFAGC_Peak_Val;				/* RFAGC Peak Val */
    TDA182I4_RFAGC_Adapt_TOP_ovld_t				RFAGC_Adapt_TOP_ovld;		/* RFAGC Adapt TOP ovld */
    TDA182I4_RFAGC_det_mode_t					RFAGC_det_mode;				/* RFAGC det mode */
    TDA182I4AGC3_TOP_I2C_t                      AGC3_TOP_I2C;               /* AGC3 TOP I2C */
    TDA182I4AGC4_TOP_DN_UP_t                    AGC4_TOP_DN_UP;             /* AGC4 TOP DN/UP */
    TDA182I4AGC5_TOP_DN_UP_t                    AGC5_TOP_DN_UP;             /* AGC5 TOP DN/UP */
    TDA182I4RSSI_HP_FC_t                        RSSI_HP_FC;                 /* RSSI HP FC */
    TDA182I4AGC5_HP_FC_t                        AGC5_HP_FC;                 /* AGC5 HP FC */
    TDA182I4AGC3_Top_Adapt_Algorithm            AGC3_Top_Adapt_Algorithm;   /* AGC3_Top_Adapt_Algorithm */
    TDA182I4AGC3_Adapt_TOP_t                    AGC3_Adapt_TOP;             /* AGC3 Adapt TOP */
    TDA182I4AGC_Overload_TOP_t                  AGC_Overload_TOP;           /* AGC Overload TOP */
    TDA182I4RF_Atten_3dB_t                      RF_Atten_3dB;               /* RF atten 3dB */
    TDA182I4IF_Output_Level_t                   IF_Output_Level;            /* IF Output Level */
    TDA182I4S2D_Gain_t                          S2D_Gain;                   /* S2D gain */
    TDA182I4Negative_Modulation_t               Negative_Modulation;        /* Negative modulation */

    /****************************************************************/
    /* GSK Settings                                                 */
    /****************************************************************/
    TDA182I4AGCK_Time_Constant_t                AGCK_Time_Constant;         /* AGCK Time Constant */

    /****************************************************************/
    /* H3H5 Settings                                                */
    /****************************************************************/
    TDA182I4VHF_III_Mode_t                      VHF_III_Mode;               /* VHF_III_Mode */

	/****************************************************************/
    /*RSSI Settings                                                 */
    /****************************************************************/
	UInt8										RSSI_Ck_Speed;				/* 0:31.25   1:62.5 Khz */
	UInt8										RSSI_Cap_Val;				/* 0: 0.5  1: 3 pF */

	TDA182I4PowerSavingMode_t					PowerSavingMode;            /* normal or low */

} TDA182I4StdCoefficients, *pTDA182I4StdCoefficients;



typedef struct _TDA182I4Object_t
{
    tmUnitSelect_t                  tUnit;
    tmUnitSelect_t                  tUnitW;
    ptmbslFrontEndMutexHandle       pMutex;
    Bool                            init;
    tmbslFrontEndIoFunc_t           sIo;
    tmbslFrontEndTimeFunc_t         sTime;
    tmbslFrontEndDebugFunc_t        sDebug;
    tmbslFrontEndMutexFunc_t        sMutex;
    /* Device specific part: */
    tmPowerState_t                  curPowerState;
    TDA182I4PowerState_t            curLLPowerState;
    TDA182I4PowerState_t            mapLLPowerState[tmPowerMax];
    TDA182I4PowerSavingMode_t       curPowerSavingMode;       
    UInt32                          uRF;
    UInt32                          uProgRF;
    TDA182I4StandardMode_t          StandardMode;
    pTDA182I4StdCoefficients        pStandard;
    Bool                            bOverridePLL;       /* Indicates if PLL is put into manual mode during setRF */
    Bool                            bFefEnable;         /* Indicates if FEF settings enable for DVB/T/T2 */
	Bool                            bHalfRfImmunity;    /* Indicates if Half RF Immunity mode is enabled */
	Bool                            bCenelecMargin;     /* Indicates if Cenelec Margin improvement is enabled */
	UInt8                           TunerModeInUse;     /* define LTO/STO option */
    /* Settings independant of standard */
    TDA182I4XTOutAmp_t              curXTOutAmp;             /* Current XTOUT Amplitude */
	TDA182I4LNA_RANGE_t             curLNA_Range;            /* Current LNA_RANGE */
    TDA182I4HwState_t               eHwState;                /* Indicates HwInit state */
    /* Settings dependant of standard */
    TDA182I4StdCoefficients         Std_Array[TDA182I4_StandardMode_Max-1];
#ifdef _TDA182I4_REGMAP_BITFIELD_DEFINED
    TDA182I4_Reg_Map_t              RegMap;
#else
    UInt8                           RegMap[TDA182I4_REG_MAP_NB_BYTES];
#endif
} TDA182I4Object_t, *pTDA182I4Object_t, **ppTDA182I4Object_t;


/*============================================================================*/
/* Internal Prototypes:                                                       */
/*============================================================================*/

extern tmErrorCode_t
iTDA182I4_CheckCalcPLL(pTDA182I4Object_t pObj);

extern tmErrorCode_t
iTDA182I4_CheckHwState(pTDA182I4Object_t pObj, TDA182I4HwStateCaller_t caller);

extern tmErrorCode_t
iTDA182I4_SetRF(pTDA182I4Object_t pObj);

extern tmErrorCode_t
iTDA182I4_SetRF_Freq(pTDA182I4Object_t pObj, UInt32 uRF);

extern tmErrorCode_t
iTDA182I4_SetMSM(pTDA182I4Object_t pObj, UInt8 uValue, Bool bLaunch);

extern tmErrorCode_t
iTDA182I4_WaitIRQ(pTDA182I4Object_t pObj, UInt32 timeOut, UInt32 waitStep, UInt8 irqStatus);

extern tmErrorCode_t
iTDA182I4_Write(pTDA182I4Object_t pObj, const TDA182I4_BitField_t* pBitField, UInt8 uData, tmbslFrontEndBusAccess_t eBusAccess);

extern tmErrorCode_t
iTDA182I4_Read(pTDA182I4Object_t pObj, const TDA182I4_BitField_t* pBitField, UInt8* puData, tmbslFrontEndBusAccess_t eBusAccess);

extern tmErrorCode_t
iTDA182I4_WriteRegMap(pTDA182I4Object_t pObj, UInt8 uAddress, UInt32 uWriteLen);

extern tmErrorCode_t
iTDA182I4_ReadRegMap(pTDA182I4Object_t pObj, UInt8 uAddress, UInt32 uReadLen);

extern tmErrorCode_t
iTDA182I4_Wait(pTDA182I4Object_t pObj, UInt32 Time);

extern tmErrorCode_t 
iTDA182I4_PowerSavingMode( pTDA182I4Object_t   pObj, TDA182I4PowerSavingMode_t PowerSavingMode);

#ifdef _TVFE_IMPLEMENT_MUTEX
 extern tmErrorCode_t iTDA182I4_MutexAcquire(pTDA182I4Object_t pObj, UInt32 timeOut);
 extern tmErrorCode_t iTDA182I4_MutexRelease(pTDA182I4Object_t pObj);
#endif

#ifdef __cplusplus
}
#endif

#endif /* _TMBSL_TDA182I4_LOCAL_H */

