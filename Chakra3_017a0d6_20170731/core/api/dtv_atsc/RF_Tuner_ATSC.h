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
/******************************************************************************
 Copyright (c) 2006 MStar Semiconductor, Inc.
 All rights reserved.

 [Module Name]: RF_Tuner_ATSC.h
 [Date]:        28-Aug-2006
 [Comment]:
   TV tuner header file.
 [Reversion History]:
*******************************************************************************/

#ifndef _TUNER_ATSC_H_
#define _TUNER_ATSC_H_

#include "Board.h"



#ifdef _TUNER_ATSC_C_
    #define INTERFACE
#else
    #define INTERFACE extern
#endif

//#ifndef TUNER_IIC_BUS
//#define TUNER_IIC_BUS     E_I2C_BUS_SYS
//#endif

#define TDA18275A_TUNER_PLL_STABLE_TIME     150

#define MXL601SI_TUNER_PLL_STABLE_TIME      100


#if (FRONTEND_TUNER_TYPE == THOMSON_DTT7630_TUNER)
#define Offset_P_62500Hz 13
#define Offset_P_87500Hz 12
#define Offset_P_122500Hz 11
#define Offset_P_137500Hz 10
#define Offset_P_162500Hz 9
#define Offset_P_187500Hz 8
#define Offset_N_62500Hz 2
#define Offset_N_87500Hz 3
#define Offset_N_122500Hz 4
#define Offset_N_137500Hz 5
#define Offset_N_162500Hz 6
#define Offset_N_187500Hz 7

#define TUA6030_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0xC2)
#define FREQ_STEP                                       62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TDA9885_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0x84)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50

#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20

#define _TUNER_I2C_ID   TUA6030_devAddr
#elif (FRONTEND_TUNER_TYPE==MSTAR_MSR1200)

#define Offset_P_62500Hz 13
#define Offset_P_87500Hz 12
#define Offset_P_122500Hz 11
#define Offset_P_137500Hz 10
#define Offset_P_162500Hz 9
#define Offset_P_187500Hz 8
#define Offset_N_62500Hz 2
#define Offset_N_87500Hz 3
#define Offset_N_122500Hz 4
#define Offset_N_137500Hz 5
#define Offset_N_162500Hz 6
#define Offset_N_187500Hz 7

#define MSR1200_TUNER_I2C_ADDR                  (((U16) TUNER_IIC_BUS << 8) | 0xC6)
#define TDA9885_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0x86)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50

#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define FREQ_STEP                       50 //Khz

#define _TUNER_I2C_ID   MSR1200_TUNER_I2C_ADDR
#elif (FRONTEND_TUNER_TYPE == PHILIPS_FQD1236_TUNER)
#define Offset_P_62500Hz 13
#define Offset_P_87500Hz 12
#define Offset_P_122500Hz 11
#define Offset_P_137500Hz 10
#define Offset_P_162500Hz 9
#define Offset_P_187500Hz 8
#define Offset_N_62500Hz 2
#define Offset_N_87500Hz 3
#define Offset_N_122500Hz 4
#define Offset_N_137500Hz 5
#define Offset_N_162500Hz 6
#define Offset_N_187500Hz 7

#define TUA6030_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0xC2)
#define FREQ_STEP                                 62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TDA9885_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0x86)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30

#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define _TUNER_I2C_ID   TUA6030_devAddr

#elif (FRONTEND_TUNER_TYPE == ALPS_TDQU4_TUNER)

#define ALPS_TDQU4_devAddr                      (((U16) TUNER_IIC_BUS << 8) | 0xc0)
#define FREQ_STEP                                 62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define RANGE_OF_AFT_WIN 24//1500   //KHz
#define LEFT_OF_AFT_WIN      6//400 //KHz
#define LARGE_FREQ_OFFSET_CHECK    8//500   //62.5*8 KHz,    FREQ_STEP=62.5
#define MEDIUM_FREQ_OFFSET_CHECK    5//250   //62.5*4 KHz,    FREQ_STEP=62.5
#define SMALL_FREQ_OFFSET_CHECK 2//125     //62.5*2KHz,    FREQ_STEP=62.5
#define RANGE_OF_AFT_COUNT RANGE_OF_AFT_WIN/LARGE_FREQ_OFFSET_CHECK+1
#define RANGE_OF_AFT_COUNT2 LARGE_FREQ_OFFSET_CHECK/SMALL_FREQ_OFFSET_CHECK
#define AFT_SIGNAL_EXIST_THR    0x24
#define AFT_WAIT_TIME       10  //ms
#define AFT_LARGE_FREQ_OFFSET 0x06
#define AFT_HB_NO_FREQ_OFFSET 0x2E
#define AFT_LB_NO_FREQ_OFFSET 0x18
#define AFT_FORCE_LEAVE_DEADLOCK 15

#define _TUNER_I2C_ID   ALPS_TDQU4_devAddr
#elif (FRONTEND_TUNER_TYPE == ALPS_TDQU6_TUNER)
#define ALPS_TDQU6_devAddr                      (((U16) TUNER_IIC_BUS << 8) | 0xc0)
#define FREQ_STEP                                   50//62.5 //Khz
#define IF_FREQ_A                                         45750  //44MHz
#define IF_STEP                                         915//704     //IF_FREQ/FREQ_STEP
#define TUNER_PLL_STABLE_TIME           50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//for Tuner 5V => 4.85V, -1 Step=32, 0 Step=27, +1 Step=22
//for Tuner 5V => 5.00V, -1 Step=36, 0 Step=31, +1 Step=27
//for Tuner 5V => 5.32V, -1 Step=39, 0 Step=34, +1 Step=30
#define MIN_AFT_VALUE               24
#define MAX_AFT_VALUE               38
#define FINE_MIN_AFT_VALUE               30
#define CENTER_AFT_VALUE                    31
#define FINE_MAX_AFT_VALUE               32

#define MAX_ZIG_ZAG_NUM                         7

#define _TUNER_I2C_ID   ALPS_TDQU6_devAddr
#elif (FRONTEND_TUNER_TYPE==SAMSUNG_S205_TUNER)
#define SAMSUNG_TUNER_I2C_ADDR                  (((U16) TUNER_IIC_BUS << 8) | 0xC2)

#define FREQ_STEP                                     50 //Khz
#define IF_FREQ_A                                         45750  //44MHz
#define IF_STEP                                         915//704     //IF_FREQ/FREQ_STEP
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//Modify for Saturn2 SAR is 3.3V
#define MIN_AFT_VALUE                    0x7//        0x0E//0x1A//0x20
#define MAX_AFT_VALUE                    0x19//        0x2B//0x2B
#define MAX_ZIG_ZAG_NUM 7

#define _TUNER_I2C_ID   SAMSUNG_TUNER_I2C_ADDR
#elif (FRONTEND_TUNER_TYPE==SAMSUNG_S203FH201B_TUNER)
#define SAMSUNG_TUNER_I2C_ADDR                  (((U16) TUNER_IIC_BUS << 8) | 0xC2)

#define FREQ_STEP                                     62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//Modify for Saturn2 SAR is 3.3V
#define MIN_AFT_VALUE                    24//        0x0E//0x1A//0x20
#define MAX_AFT_VALUE                    40//        0x2B//0x2B
#define MAX_ZIG_ZAG_NUM 7

#define _TUNER_I2C_ID   SAMSUNG_TUNER_I2C_ADDR
#elif (FRONTEND_TUNER_TYPE==SAMSUNG_EH201A_TUNER)
#define SAMSUNG_TUNER_I2C_ADDR                  0xC2

#define FREQ_STEP                    62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//Modify for Saturn2 SAR is 3.3V
#define MIN_AFT_VALUE                    0x7//        0x0E//0x1A//0x20
#define MAX_AFT_VALUE                    0x19//        0x2B//0x2B
#define MAX_ZIG_ZAG_NUM 7

#define _TUNER_I2C_ID   SAMSUNG_TUNER_I2C_ADDR

#elif (FRONTEND_TUNER_TYPE==NXP_FQD1136_TUNER)

#define NXP_TUNER_I2C_ADDR                      (((U16) TUNER_IIC_BUS << 8) | 0xC0)//0xC2)
#define FREQ_STEP                        62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME         50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//Modify for Saturn2 SAR is 3.3V
#define MIN_AFT_VALUE                    0x01//0x30//0x18//0x7//        0x0E//0x1A//0x20
#define MAX_AFT_VALUE                    0x03//0x3F//0x25//0x2B//        0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7

#define TDA9885_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0xC0)

#define _TUNER_I2C_ID   NXP_TUNER_I2C_ADDR

#elif(FRONTEND_TUNER_TYPE == SAMSUNG_DVTA50_TUNER)

#define SAMSUNG_TUNER_I2C_ADDR          (((U16) TUNER_IIC_BUS << 8) | 0xC0)
#define FREQ_STEP                       62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME           50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
#define MIN_AFT_VALUE               24
#define MAX_AFT_VALUE               38
#define FINE_MIN_AFT_VALUE                  30
#define CENTER_AFT_VALUE                    31
#define FINE_MAX_AFT_VALUE                   2
#define MAX_ZIG_ZAG_NUM                      7
#define _TUNER_I2C_ID   SAMSUNG_TUNER_I2C_ADDR

#elif(FRONTEND_TUNER_TYPE == SAMSUNG_DTVS20CVL081A_TUNER)

#define SAMSUNG_TUNER_I2C_ADDR              (((U16) TUNER_IIC_BUS << 8) | 0xC0)
#define FREQ_STEP                           62.5    //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME               50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
#define MIN_AFT_VALUE                       24
#define MAX_AFT_VALUE                       38
#define FINE_MIN_AFT_VALUE                  30
#define CENTER_AFT_VALUE                    31
#define FINE_MAX_AFT_VALUE                  2
#define MAX_ZIG_ZAG_NUM                     7
#define _TUNER_I2C_ID                       SAMSUNG_TUNER_I2C_ADDR

#elif(FRONTEND_TUNER_TYPE == TCL_DA91WT_13_E_TUNER)

#define TCL_TUNER_I2C_ADDR                  (((U16) TUNER_IIC_BUS << 8) | 0xC0)
#define FREQ_STEP                           50      //Setp: 50KHz
#define IF_FREQ_A                                         45750  //44MHz
#define IF_STEP                                         915//704     //IF_FREQ/FREQ_STEP
#define TUNER_PLL_STABLE_TIME               50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
#define MIN_AFT_VALUE                       24
#define MAX_AFT_VALUE                       38
#define FINE_MIN_AFT_VALUE                  30
#define CENTER_AFT_VALUE                    31
#define FINE_MAX_AFT_VALUE                  2
#define MAX_ZIG_ZAG_NUM                     7
#define _TUNER_I2C_ID                       TCL_TUNER_I2C_ADDR

#elif ( FRONTEND_TUNER_TYPE == MxL_661SI_TUNER) ||(FRONTEND_TUNER_TYPE == SILAB_2157_TUNER)||(FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
#define FREQ_STEP	62.5
#define TUNER_PLL_STABLE_TIME      100
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10
#define MIN_AFT_VALUE                   0x10
#define MAX_AFT_VALUE                   0x28
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8

#elif (FRONTEND_TUNER_TYPE==SILAB_2190B_TUNER)
#define FREQ_STEP				   62.5//Khz
#define TUNER_PLL_STABLE_TIME      50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10//0x30//0x18//0x7//0x0E//0x1A//0x20
#define MAX_AFT_VALUE                   0x28//0x3F//0x25//0x2B//0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8

#elif (FRONTEND_TUNER_TYPE == RDA5158_TUNER)
#define RDA_TUNER_I2C_ADDR                      (((U16) TUNER_IIC_BUS << 8) | 0xC0)//0xC2)
#define FREQ_STEP                        62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME         80
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#elif (FRONTEND_TUNER_TYPE==NXP_TD1136_TUNER)

#define NXP_TUNER_I2C_ADDR                      (((U16) TUNER_IIC_BUS << 8) | 0xC0)//0xC2)
#define FREQ_STEP                        62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME         80
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//Modify for Saturn2 SAR is 3.3V
#define MIN_AFT_VALUE                    0x10//0x30//0x18//0x7//        0x0E//0x1A//0x20
#define MAX_AFT_VALUE                    0x28//0x3F//0x25//0x2B//        0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM                 8

#define _TUNER_I2C_ID   NXP_TUNER_I2C_ADDR

typedef enum TD_1136_ADC_PATTERN
{
    ADC_BOTTOM_UNSTABLE_POINT = 0x35,     // 4.3V
    ADC_BOTTOM_STABLE_POINT = 0x21,             // 2.9v
    ADC_LOW_STABLE_POINT = 0x1D,             // 2.6v
    ADC_MATCH_STABLE_POINT = 0x1B,      // 2.5v
    ADC_HIGH_STABLE_POINT = 0x1A,      ////2.4V
    ADC_TOP_STABLE_POINT = 0x15,      ////2.1V
    //ADC_TOP_STABLE_POINT = 0x0A,         // 1.3v
    ADC_TOP_UNSTABLE_POINT = 0x05         ////1.0V
} TD_1136_ADC_PATTERN;

#elif (FRONTEND_TUNER_TYPE==NXP_TD1636ALMK2_TUNER)

#define NXP_TUNER_I2C_ADDR                      (((U16) TUNER_IIC_BUS << 8) | 0xC2)
#define FREQ_STEP                        50 //Khz
#define IF_FREQ_A                                         45750  //44MHz
#define IF_STEP                                         915//704     //IF_FREQ/FREQ_STEP
#define TUNER_PLL_STABLE_TIME         50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
//Modify for Saturn2 SAR is 3.3V
#define MIN_AFT_VALUE                    0x18//0x7//        0x0E//0x1A//0x20
#define MAX_AFT_VALUE                    0x25//0x2B//        0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7

#define _TUNER_I2C_ID   NXP_TUNER_I2C_ADDR

#elif (FRONTEND_TUNER_TYPE == SHARP_VA1Y2UR2201_TUNER)    //1031angus
#define SHARP_TUNER_I2C_ADDR                    (((U16) TUNER_IIC_BUS << 8) | 0xC2)
#define FREQ_STEP                             62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value    //should be modify after get the demo board
#define MIN_AFT_VALUE                        0x1A//0x20
#define MAX_AFT_VALUE                        0x2B//0x2B

#define JUMP_NUMBER 12
#define FOUR_TIMES_SAMPLING_FREQ 4//250    //62.5*4
    const S8 code JUMP_TABLE[ JUMP_NUMBER ]
        = {
            -FOUR_TIMES_SAMPLING_FREQ, FOUR_TIMES_SAMPLING_FREQ,
              -FOUR_TIMES_SAMPLING_FREQ*2, FOUR_TIMES_SAMPLING_FREQ*2,
              -FOUR_TIMES_SAMPLING_FREQ*3, FOUR_TIMES_SAMPLING_FREQ*3,
              -FOUR_TIMES_SAMPLING_FREQ*4, FOUR_TIMES_SAMPLING_FREQ*4,
              -FOUR_TIMES_SAMPLING_FREQ*5, FOUR_TIMES_SAMPLING_FREQ*5,
              -FOUR_TIMES_SAMPLING_FREQ*6, FOUR_TIMES_SAMPLING_FREQ*6
            };
#if 1
    const S8 code TRACK_TABLE[ JUMP_NUMBER ]
        = {
            -1, 1,
              -2, 2,
              -3, 3,
              -4, 4,
              -5, 5,
              -6, 6
            };
#else
    const S32 code TRACK_TABLE[ JUMP_NUMBER ]
        = {
            -FREQ_STEP, FREQ_STEP,
              -FREQ_STEP*2, FREQ_STEP*2,
              -FREQ_STEP*3, FREQ_STEP*3,
              -FREQ_STEP*4, FREQ_STEP*4,
              -FREQ_STEP*5, FREQ_STEP*5,
              -FREQ_STEP*6, FREQ_STEP*6
            };
#endif

#define _TUNER_I2C_ID   SHARP_TUNER_I2C_ADDR
#elif (FRONTEND_TUNER_TYPE == LG_TDVS_H703P_TUNER)

#define Offset_P_62500Hz 13
#define Offset_P_87500Hz 12
#define Offset_P_122500Hz 11
#define Offset_P_137500Hz 10
#define Offset_P_162500Hz 9
#define Offset_P_187500Hz 8
#define Offset_N_62500Hz 2
#define Offset_N_87500Hz 3
#define Offset_N_122500Hz 4
#define Offset_N_137500Hz 5
#define Offset_N_162500Hz 6
#define Offset_N_187500Hz 7

#define LG_TUNER_I2C_ADDR                       (((U16) TUNER_IIC_BUS << 8) | 0xC2)
#define FREQ_STEP                             62.5 //Khz
#define TDA9885_devAddr                         (((U16) TUNER_IIC_BUS << 8) | 0x86)
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME 50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define _TUNER_I2C_ID   LG_TUNER_I2C_ADDR

#elif (FRONTEND_TUNER_TYPE == XUGUANG_DVT_8ADC1_W41F2) // BY 20090727
#define FREQ_STEP                       62.5 //Khz
#define IF_FREQ_A                         45750  //44MHz
#define IF_STEP                         732     // =(IF_FREQ/FREQ_STEP)
#define TUNER_PLL_STABLE_TIME           50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

//define lock range of AFT value
#define MIN_AFT_VALUE               24
#define MAX_AFT_VALUE               38
#define FINE_MIN_AFT_VALUE                  30
#define CENTER_AFT_VALUE                    31
#define FINE_MAX_AFT_VALUE                   2
#define MAX_ZIG_ZAG_NUM                      7

#elif (FRONTEND_TUNER_TYPE==NXP_TDA18273_TUNER)
#define FREQ_STEP				   50 //Khz
#define TUNER_PLL_STABLE_TIME      150
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10//0x30//0x18//0x7//0x0E//0x1A//0x20
#define MAX_AFT_VALUE                   0x28//0x3F//0x25//0x2B//0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8
#elif (FRONTEND_TUNER_TYPE==NXP_TDA18274_TUNER)
#define FREQ_STEP				   50//50 //Khz
#define TUNER_PLL_STABLE_TIME      150
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10//0x30//0x18//0x7//0x0E//0x1A//0x20
#define MAX_AFT_VALUE                   0x28//0x3F//0x25//0x2B//0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8
#elif (FRONTEND_TUNER_TYPE==NXP_TDA18275_TUNER)
#define FREQ_STEP				   50//50 //Khz
#define TUNER_PLL_STABLE_TIME      30  //abu 1226
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10//0x30//0x18//0x7//0x0E//0x1A//0x20
#define MAX_AFT_VALUE                   0x28//0x3F//0x25//0x2B//0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8
#elif (FRONTEND_TUNER_TYPE==NXP_TDA18275A_TUNER)
#define FREQ_STEP				   62.5 //Khz
#define TUNER_PLL_STABLE_TIME      TDA18275A_TUNER_PLL_STABLE_TIME
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50//30
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10//0x30//0x18//0x7//0x0E//0x1A//0x20
#define MAX_AFT_VALUE                   0x28//0x3F//0x25//0x2B//0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8
#elif (FRONTEND_TUNER_TYPE==RAFAEL_R828_TUNER)
#define FREQ_STEP				   62.5//Khz
#define TUNER_PLL_STABLE_TIME      50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10
#define MAX_AFT_VALUE                   0x28
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8


#elif (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER||FRONTEND_TUNER_TYPE == RAFAEL_R842_TUNER)
#define FREQ_STEP				   62.5//Khz
#define TUNER_PLL_STABLE_TIME      50
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10
#define MAX_AFT_VALUE                   0x28
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8

#elif (FRONTEND_TUNER_TYPE==SILAB_2151_TUNER || FRONTEND_TUNER_TYPE==SILAB_2158_TUNER)
#define FREQ_STEP				   50//Khz
#define TUNER_PLL_STABLE_TIME      30//20
#define QAM_TUNER_PLL_STABLE_TIME 50
#define VSB_TUNER_PLL_STABLE_TIME 50
#define QAM_DEMOD_STABLE_TIME 100
#define VSB_DEMOD_STABLE_TIME 20
#define VD_STABLE_TIME     100
#define VIF_STABLE_TIME    10

#define MIN_AFT_VALUE                   0x10//0x30//0x18//0x7//0x0E//0x1A//0x20
#define MAX_AFT_VALUE                   0x28//0x3F//0x25//0x2B//0x19//0x2B
#define MAX_ZIG_ZAG_NUM                 7
#define MAX_AFT_CHECK_NUM               8
#endif


#if ((FRONTEND_TUNER_TYPE == THOMSON_DTT7630_TUNER) \
     ||(FRONTEND_TUNER_TYPE == PHILIPS_FQD1236_TUNER)  \
     ||(FRONTEND_TUNER_TYPE==MSTAR_MSR1200))
INTERFACE BOOLEAN TDA9885_Init(void);
#endif

#if (FRONTEND_TUNER_TYPE==NXP_TDA18273_TUNER)
INTERFACE BOOLEAN NUTUNE_FK1602_Init(void);
#endif
#if (FRONTEND_TUNER_TYPE==NXP_TDA18274_TUNER)
INTERFACE BOOLEAN NXP_TDA18274_Init(void);
#endif
#if (FRONTEND_TUNER_TYPE==NXP_TDA18275_TUNER)
INTERFACE BOOLEAN NUTUNE_18275_Init(void);
#endif
#if (FRONTEND_TUNER_TYPE==NXP_TDA18275A_TUNER)
BOOLEAN NXP_TDA18275A_Init(void);
#endif

#if (FRONTEND_TUNER_TYPE==RAFAEL_R828_TUNER)
INTERFACE BOOLEAN Rafael_R828_Initial(void);
#endif
#if (FRONTEND_TUNER_TYPE == RAFAEL_R840_TUNER)
INTERFACE BOOLEAN Rafael_R840_Initial(void);
#endif

#if (FRONTEND_TUNER_TYPE==SILAB_2151_TUNER)
INTERFACE BOOLEAN SILAB_2151_TUNER_Init(void);
#endif

#if (FRONTEND_TUNER_TYPE==SAMSUNG_S205_TUNER)
INTERFACE U8 DRV_TDA6651_GetChargePumpData(U32 u32freq);
#endif

//INTERFACE BOOLEAN Set_Tuner_Freq(U32 u32FreqKHz, EN_DEMOD_ATSC_MODE enModulation);
INTERFACE BOOLEAN NTSC_IF_ReadStatus(U8 * AFT_Status);

#undef INTERFACE


#endif


