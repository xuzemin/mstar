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

#ifndef MS_IR_H
#define MS_IR_H

#include "Board.h"
#include "sysinfo.h"

#define IR_TYPE_FULLDECODE_MODE             1
#define IR_TYPE_RAWDATA_MODE                2
#define IR_TYPE_SWDECODE_MODE               3

#define IR_TYPE_HWDECODE_RC                 0x11

#define IR_TYPE_SWFIFO_MODE                 0x21

#define IR_TYPE_SWDECODE_TEST_MODE          0x31
#define IR_TYPE_SWDECODE_KON_MODE           0x32
#define IR_TYPE_SWDECODE_RC5HAI_MODE        0x33
#define IR_TYPE_SWDECODE_SHA_MODE           0x34
#define IR_TYPE_SWDECODE_MALATA_MODE        0x35
#define IR_TYPE_SWDECODE_RC5_MODE           0x36
#define IR_TYPE_SWDECODE_NEC_MODE           0x37
#define IR_TYPE_SWDECODE_TOSHIBA_MODE       0x38
#define IR_TYPE_SWDECODE_RCA_MODE           0x39
#define IR_TYPE_SWDECODE_CH_MODE            0x3A
#define IR_TYPE_SWDECODE_MITSUBISHI_MODE    0x3B
#define IR_TYPE_SWDECODE_PIONEER            0x3C
#define IR_TYPE_SWDECODE_HSS_MODE           0x3D
#define IR_TYPE_SWDECODE_SKY_MODE           0x3E

#define IR_TYPE_RAWDATA_TEST_MODE           0xA1
#define IR_TYPE_RAWDATA_PANASONIC_MODE      0xA2
#define IR_TYPE_RAWDATA_MITSUBISHI_MODE     0xA3
#define IR_TYPE_RAWDATA_SAMSUNG_MODE        0xA4
#define IR_TYPE_RAWDATA_SONY_12BITS_MODE    0xA5
#define IR_TYPE_RAWDATA_SAMPO_MODE          0xA6

#if (IR_TYPE_SEL == IR_TYPE_OLD)
#include "../include/IR_MSTAR_OLD.h"
#elif (IR_TYPE_SEL == IR_TYPE_NEW)
#include "../include/IR_MSTAR_NEW.h"
#elif (IR_TYPE_SEL == IR_TYPE_MSTAR_DTV)
#include "../include/IR_MSTAR_DTV.h"
#elif (IR_TYPE_SEL == IR_TYPE_RC_V16)
#include "../include/IR_MSTAR_RC_V16.h"
#elif (IR_TYPE_SEL == IR_TYPE_MSTAR_RAW)
#include "../include/IR_MSTAR_RAW.h"
#elif (IR_TYPE_SEL == IR_TYPE_JEAN_RC5)
#include "../include/IR_JEAN_RC5.h"
#elif (IR_TYPE_SEL==IR_TYPE_DC_BN59)
#include "../include/IR_MSTAR_BN59.h"
#elif (IR_TYPE_SEL == IR_TYPE_CUS03_DTV)
#include "../include/IR_CUS03_DTV.h"
#elif (IR_TYPE_SEL == IR_TYPE_P_DTV)
#include "../include/IR_P_DTV.h"
#elif (IR_TYPE_SEL == IR_TYPE_MSTAR_SZ1)
#include "../include/IR_MSTAR_SZ1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_CHO1)
#include "../include/IR_SZ_CHO1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_ALC1)
#include "../include/IR_SZ_ALC1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_TON1)
#include "../include/IR_SZ_TON1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_CTV1)
#include "../include/IR_SZ_CTV1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_KON1)
#include "../include/IR_SZ_KON1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_KON2)
#include "../include/IR_SZ_KON2.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_MTC1)
#include "../include/IR_SZ_MTC1.h"
#elif(IR_TYPE_SEL == IR_TYPE_SZ_HAI1)
#include "../include/IR_SZ_HAI1.h"
#elif (IR_TYPE_SEL == IR_TYPE_SZ_PRI1)
#include "../include/IR_PRI_DTV.h"
#elif(IR_TYPE_SEL == IR_TYPE_SZ_TEN)
#include "../include/IR_SZ_TEN.h"
#elif(IR_TYPE_SEL == IR_TYPE_DC_LWB1)
#include "../include/IR_MSTAR_DC_LWB1.h"
#elif(IR_TYPE_SEL == IR_TYPE_CUS21SH)
#include "../include/IR_MSTAR_CUS21SH.h"
#elif (IR_TYPE_SEL==IR_TYPE_DC_BN59_611)
#include "../include/IR_MSTAR_BN59_611.h"
#elif (IR_TYPE_SEL==IR_TYPE_CUS30_BK)
#include "../include/IR_CUS30_BK.h"
#elif (IR_TYPE_SEL==IR_TYPE_TPV_AOC)
#include "../include/IR_TPV_AOC.h"
#elif(IR_TYPE_SEL == IR_TYPE_HYF_51F)
#include "../include/IR_HYF_51F.h"
#elif(IR_TYPE_SEL == IR_TYPE_HIS_NEC)
#include "../include/IR_HIS_NEC.h"
#elif(IR_TYPE_SEL == IR_TYPE_CUS_KITKING)
#include "../include/IR_CUS_KITKING.h"
#elif(IR_TYPE_SEL == IR_TYPE_SAMSUNG_REMOTE)
#include "../include/IR_SAMSUNG.h"
#else
#include "../include/IR_MSTAR_DTV.h"
#endif

#ifndef IR_MODE_SEL
#define IR_MODE_SEL             IR_TYPE_FULLDECODE_MODE
#endif

#if (IR_TYPE_SEL==IR_TYPE_DC_BN59_611 || IR_TYPE_SEL==IR_TYPE_DC_BN59)
#define IR_FILTER_REPEAT_NUM    5
#else
#define IR_FILTER_REPEAT_NUM    4
#endif

#ifdef  MS_IR_C
#define INTERFACE
  #else
#define INTERFACE extern
#endif

INTERFACE void msIR_ProcessUserKey(BOOLEAN bEnable);
INTERFACE BOOLEAN msIR_IsProcessUserKey(void);
INTERFACE void msIR_Clear_FIFO(void);
INTERFACE U8   msIR_ReadByte( U16 u16RegIndex );
INTERFACE void msIR_WriteByte(U16 u16RegIndex, U8 u8Value);
INTERFACE void msIR_Write2Byte ( U16 u16RegIndex, U16 u16Value );
INTERFACE void msIR_Write3Byte ( U16 u16Regndex, U32 u32Value );
INTERFACE void msIR_Initialize(U8 irclk_mhz);
INTERFACE void msIR_PowerDown_Init(void);
INTERFACE BOOLEAN msIR_GetIRKeyCode(U8 *pkey, U8 *pu8flag);

extern U8 g_ucIrRepeatTimer;
INTERFACE BOOLEAN MDrv_Power_CheckPowerOnSWIRKey(void);
INTERFACE BOOLEAN MDrv_IR_CheckPowerOnKey(void);
INTERFACE void msIR_ResetSoftWareModeVariables(void);
INTERFACE void msIR_SwitchIRMode(U8 mode);

#if (IR_MODE_SEL == IR_TYPE_SWDECODE_SHA_MODE)
    INTERFACE BOOLEAN MDrv_CheckSWIRKey(void);
    INTERFACE BOOLEAN MDrv_CheckSWIRRepeatKey(void);
#endif

BOOLEAN MDrv_IR_IsIRkeyEnabled(U8 u8IRkey);

#define IR_CODE                     (g_ucIrCode[2])
INTERFACE U8 g_bIrDetect;//!<IR command detect flag
    INTERFACE U8 g_ucIrCode[10];

#if (IR_MODE_SEL == IR_TYPE_FULLDECODE_MODE)
// Variables and fuctions used in IR SWDECODE MODE for TVLINK-Loader ----------------------------
    #define IR_SW_COUNT_BIT_NUM         8
    #define IR_SW_REPEAT_TIMEOUT        110//110ms
    #define IR_REPEAT_SKIP_COUNT        2
#define IR_MAX_IR_DATA_NUM            10

    INTERFACE U16 g_wIrLoaderCnt;

#elif ((IR_MODE_SEL == IR_TYPE_SWDECODE_MODE)||(IR_MODE_SEL == IR_TYPE_SWFIFO_MODE))
#define IR_SW_COUNT_BIT_NUM         8
#define IR_SW_REPEAT_TIMEOUT        110//110ms
#define IR_REPEAT_SKIP_COUNT        2
#define IR_MAX_IR_DATA_NUM            10

#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_KON_MODE)
    INTERFACE U8 g_u8IrKonRepeatTimeout;
#elif (IR_MODE_SEL == IR_TYPE_SWDECODE_RC5_MODE)
    // Fixed pulse width format: Start(1.5)+Control(1)+System(5)+Data(6)
    #define IR_RC5_DATA_BITS                 26

    #define IR_RC5_DETECT_START         BIT0   // start to detect IR int
    #define IR_RC5_DETECT_END             BIT1   // end to detect IR int
    #define IR_RC5_LAST_BIT                 BIT2    // last bit detect IR int

    #define IR_RC5_DECODING                 BIT6   // sw decoding
    #define IR_RC5_TOGGLE_BIT              BIT7       // for control bit

    INTERFACE U16 volatile data g_u16IrRc5Data;          // for store shift ir data
    INTERFACE U8 volatile data g_u8IrRc5Bits;                // for store bit count
    INTERFACE U16 volatile data g_u16IrRc5Counter;         // for read counter from register
    INTERFACE U8 volatile data g_u8IrRc5Flag;            // for store bit var
    INTERFACE U8 volatile data g_u8IrRc5RepeatCount;

#elif (IR_MODE_SEL == IR_TYPE_HWDECODE_RC)
//IR HW_FULL: Time Interval & Timeout
#define HAL_IR_NEC_INTERVAL             108
#define HAL_IR_NEC_TIMEOUT              120
//IR HW_RC5: Time Interval & Timeout
#define HAL_IR_RC5_INTERVAL             29//ms
#define HAL_IR_RC5_TIMEOUT              116//ms
//IR HW_RC6: Time Interval & Timeout
#define HAL_IR_RC6_INTERVAL             26//ms
#define HAL_IR_RC6_TIMEOUT              104//ms
//IR decode mode
#define HAL_IR_DECODE_FULL          0x03//0x00
#define HAL_IR_DECODE_RAW           0x02//0x00
#define HAL_IR_DECODE_SW            0x01//0x00
//IR FIFO
#define HAL_IR_FIFO_DEPTH_MAX       7
#define HAL_IR_RC_FIFO_DEPTH_MAX    7
//IR control
#define HAL_IR_CTRL_0               0
#define HAL_IR_CTRL_1               1
#define HAL_IR_RC_CTRL_0            2
#define HAL_IR_RC_CTRL_1            3
//IR RC Decode Type
#define HAL_IR_RC_RC5               0
#define HAL_IR_RC_RC5X              1
#define HAL_IR_RC_RC6               2
#define HAL_IR_RC_DISABLE           3
//IR RC Wakeup key
#define HAL_IR_RC_WKUP_KEY1         0
#define HAL_IR_RC_WKUP_KEY2         1

typedef struct
{
    U8 u8Valid : 1;
    U8 u8Toggle : 1;
    U8 u8Repeat : 1;
    U8 u8RC6Mode : 3;  //Only for RC6
    U8 u8Reserved : 2;
    U8 u8Address; //system bits: RC5[4:0], RC6[7:0]
    U8 u8Command; //command bits: RC5[5:0], RC5X[6:0], RC6[7:0]
} HAL_IR_RC_KeyData;

//##############################
// For Hardware RC Decode
//##############################
#define IR_REG_BASEMENT                         (0x1E80*2) //(0x1EC0*2)
#define REG_IR_RC_CTRL0                         ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2))
#define REG_IR_RC_RC6_LDPS_THR_L                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2))    //BIT[4:0]
    #define _IR_RC_RC6_LDPS_THR_L_MSK           (0x1F) //BIT[4:0]
    #define _IR_RC_AUTOCONFIG                   (BIT5)
    #define _IR_RC_FIFO_CLR                     (BIT6)
    #define _IR_RC_FIFO_WFST                    (BIT7)
#define REG_IR_RC_CTRL1                         ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2) +1)
#define REG_IR_RC_WKUP_DEBUG_SEL                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x00*2) +1) //BIT[6:4]
    #define _IR_RC_WKUP_DEBUG_SEL_MSK           (BIT6|BIT5|BIT4) //BIT[6:4]
    #define _IR_RC_ENABLE                       (BIT0)
    #define _IR_RC_RC6_EN                       (BIT1)
    #define _IR_RC_RC5X_EN                      (BIT2)
    #define _IR_RC_MODE_MSK                     (_IR_RC_RC5X_EN|_IR_RC_RC6_EN|_IR_RC_ENABLE)
    #define _IR_RC_WKUP_EN                      (BIT3)
    #define _IR_RC_DGB_SEL                      (BIT6|BIT5|BIT4)
    #define _IR_RC_IN_INV                       (BIT7)
#define REG_IR_RC_LGPS_THR_L                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x01*2))    //BIT[7:0]
#define REG_IR_RC_LGPS_THR_H                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x01*2) +1) //BIT[4:0]
    #define _IR_RC_LGPS_THR_L_MSK               (0xFF)
    #define _IR_RC_LGPS_THR_H_MSK               (0x1F)
#define REG_IR_RC_RC6_LGPS_MAR_L                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x02*2))    //BIT[7:0]
#define REG_IR_RC_RC6_LGPS_MAR_H                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x02*2) +1) //BIT[1:0]
    #define _IR_RC_RC6_LGPS_MAR_L_MSK           (0xFF)
    #define _IR_RC_RC6_LGPS_MAR_H_MSK           (0x03)
#define REG_IR_RC_RC6_LDPS_THR_H                ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x02*2) +1) //BIT[4:2]
    #define _IR_RC_RC6_LDPS_THR_H_MSK           (BIT4|BIT3|BIT2) //BIT[4:2]
#define REG_IR_RC_RC6_ECO_EN                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x03*2))    //BIT[0]
    #define _IR_RC_RC6_ECO_EN                   (BIT0)
#define REG_IR_RC_INTG_THR                      ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x03*2))    //BIT[7:1]
    #define _IR_RC_INTG_THR_MSK                 (0xFE)
#define REG_IR_RC_CLK_DIV                       ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x03*2) +1) //BIT[4:0]
    #define _IR_RC_CLK_DIV_MSK                  (0x1F)
#define REG_IR_RC_WDOG_COUNT                    ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x04*2))    //BIT[7:0]
#define REG_IR_RC_TIMEOUT_COUNT                 ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x04*2) +1) //BIT[7:0]
#define REG_IR_RC_COMP_KEY1                     ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x05*2))    //BIT[7:0]
#define REG_IR_RC_COMP_KEY2                     ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x05*2) +1) //BIT[7:0]

//Registers: Read Only
#define REG_IR_RC_KEY_ADDR                      ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x06*2))    //BIT[7:0]
    #define _IR_RC_RC5_KEY_ADDR_MSK             (0x1F) //{[7:6]:2'b00, [5]:toggle, [4:0]:address}
    #define _IR_RC_RC5_KEY_ADDR_TGL             (BIT5)
    #define _IR_RC_RC6_KEY_ADDR_MSK             (0xFF) //[7:0]:address
#define REG_IR_RC_KEY_CMD                       ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x06*2) +1) //BIT[7:0]
    #define _IR_RC_RC5_KEY_CMD_MSK              (0x3F)//{[7]:repeat, [6]:1'b0, [5:0]:command}
    #define _IR_RC_RC5_KEY_CMD_RPT              (BIT7)
    #define _IR_RC_RC5X_KEY_CMD_MSK             (0x7F)//{[7]:repeat, [6:0]:command}
    #define _IR_RC_RC5X_KEY_CMD_RPT             (BIT7)
    #define _IR_RC_RC6_KEY_CMD_MSK              (0xFF)//[7:0]:command
#define REG_IR_RC_RC6_KEY_MISC                  ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x07*2))    //BIT[4:0]
    #define _IR_RC_RC6_KEY_MISC_MOD_MSK         (BIT2|BIT1|BIT0)//{[4]:repeat, [3]:toggle, [2:0]:mode}
    #define _IR_RC_RC6_KEY_MISC_TGL             (BIT3)
    #define _IR_RC_RC6_KEY_MISC_RPT             (BIT4)
#define REG_IR_RC_FIFO_STATUS1                  ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x08*2))
    #define _IR_RC_FIFO_EMPTY                   (BIT0)
    #define _IR_RC_TIMEOUT_FLAG                 (BIT1)
    #define _IR_RC_FIFO_FULL                    (BIT2)
    #define _IR_RC_FIFO_WPTR_MSK                (BIT6|BIT5|BIT4)
#define REG_IR_RC_FIFO_STATUS2                  ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x08*2) +1)
    #define _IR_RC_FIFO_RPTR_MSK                (BIT2|BIT1|BIT0)

//Registers: Write Only
#define REG_IR_RC_FIFO_READ_PULSE               ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x09*2))
    #define _IR_RC_FIFO_RD_PULSE                (BIT0)
#define REG_IR_RC_WKUP_CLR                      ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x09*2) +1)
    #define _IR_RC_WKUP_CLR                     (BIT0)


#define REG_IR_CTRL0                            ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x40*2))
    #define _IR_HWDEC_EN                        (BIT0)
    #define _IR_LDCCHK_EN                       (BIT1)
    #define _IR_CCODE_CHK_EN                    (BIT2)
    #define _IR_DCODE_PCHK_EN                   (BIT3)
    #define _IR_LG01H_CHK_EN                    (BIT4)
    #define _IR_RPCODE_EN                       (BIT5)
    #define _IR_INT_MSK                         (BIT6)
    #define _IR_INV                             (BIT7)

#define REG_IR_CTRL1                            ((0x00*0x10000)+ (IR_REG_BASEMENT + 0x40*2) +1)
    #define _IR_TIMEOUT_CHK_EN                  (BIT0)
    #define _IR_SEP_CODE_CHK_EN                 (BIT1)
    #define _IR_CODE_BIT_LSB_EN                 (BIT2)
    #define _IR_NEC_WKUP_EN                     (BIT3)
    #define _IR_TSTBUS_SEL_MSK                  (BIT5|BIT4)
    #define _IR_RAW_RPT_INT_MSK                 (BIT6)
    #define _IR_INT_CRC_MSK                     (BIT7)

    //#######################################
    //#  For Hardware RC Decode
    //#######################################
    INTERFACE void HAL_IR_CfgSetControl(U32 u32Reg,U8 u8CtrlData,U8 u8Mask);
    INTERFACE void HAL_IR_CfgControl(U8 u8Index, U8 u8CtrlData,U8 u8Mask);
    INTERFACE void HAL_IR_CfgHwDecode(U8 u8Enable);
    INTERFACE void HAL_IR_CfgIntrMask(U8 u8Enable);

    INTERFACE U8 HAL_IR_RC_GetDecode(void);
    INTERFACE void HAL_IR_RC_CfgClkDiv(U8 u8ClkMhz);
    INTERFACE void HAL_IR_RC_CfgAutoConfig(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgFifoClear(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgFifoWFirst(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgDecMode(U8 u8DecMode);
    INTERFACE void HAL_IR_RC_CfgWakeup(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgOutputSelect(U8 u8OutputSel);
    INTERFACE void HAL_IR_RC_CfgInputInvert(U8 u8Enable);
    INTERFACE void HAL_IR_RC_CfgLgpsThr(void);
    INTERFACE void HAL_IR_RC_CfgIntgThr(void);
    INTERFACE void HAL_IR_RC_CfgWdogCount(void);
    INTERFACE void HAL_IR_RC_CfgTimeoutCount(void);//U16 u16TimeoutUs
    INTERFACE void HAL_IR_RC_CfgLgpsMar(void);//Only for RC6
    INTERFACE void HAL_IR_RC_CfgLdpsThr(void);//Only for RC6
    INTERFACE void HAL_IR_RC_CfgEcoFunc(BOOLEAN bEnable);//Only for RC6
    INTERFACE BOOLEAN HAL_IR_RC_IsTimeout(void);
    INTERFACE BOOLEAN HAL_IR_RC_IsFIFOEmpty(void);
    INTERFACE BOOLEAN HAL_IR_RC_IsFIFOFull(void);
    INTERFACE void HAL_IR_RC_ClearFIFO(void);
    INTERFACE U8 HAL_IR_RC_GetWakeupKey(U8 u8KeyNum);
    INTERFACE void HAL_IR_RC_GetKeyData(HAL_IR_RC_KeyData *pIRRCKeyData);

#endif



/***************************************************************************************/

#define IR_LEARNING_MODE    0

#if IR_LEARNING_MODE

//========================================================
//
//  Register arrangement
//
//========================================================
//

#define IR_REG_REC_BASEMENT                     (0x1E80*2) //(0x1EC0*2)
#define REG_IR_REC_KEYLEN                       ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x70*2))
#define REG_IR_REC_CTRL                         ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x70*2) +1)
    #define _IR_REC_DIFFMGRN                    (BIT4|BIT3|BIT2|BIT1|BIT0) //lcomparing
    #define _IR_REC_ADRCLR                      (BIT5)
    #define _IR_REC_CMPCLR                      (BIT6)
    #define _IR_REC_LEARN                       (BIT7)
#define REG_IR_REC_CMPKEYEN                     ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x71*2)) //lcomparing
    #define _IR_REC_CMPKEYEN0                   (BIT0)
    #define _IR_REC_CMPKEYEN1                   (BIT1)
    #define _IR_REC_CMPKEYEN2                   (BIT2)
    #define _IR_REC_CMPKEYEN3                   (BIT3)
    #define _IR_REC_CMPKEYEN4                   (BIT4)
    #define _IR_REC_CMPKEYEN5                   (BIT5)
#define REG_IR_REC_KEYFLAG                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x71*2) +1) //Write Only
    #define _IR_REC_KEYFLAG0                    (BIT0)
    #define _IR_REC_KEYFLAG1                    (BIT1)
    #define _IR_REC_KEYFLAG2                    (BIT2)
    #define _IR_REC_KEYFLAG3                    (BIT3)
    #define _IR_REC_KEYFLAG4                    (BIT4)
    #define _IR_REC_KEYFLAG5                    (BIT5)
#define REG_IR_REC_KEYLEN0                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x72*2))
#define REG_IR_REC_KEYLEN1                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x72*2) +1)
#define REG_IR_REC_KEYLEN2                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x73*2))
#define REG_IR_REC_KEYLEN3                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x73*2) +1)
#define REG_IR_REC_KEYLEN4                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x74*2))
#define REG_IR_REC_KEYLEN5                      //recorded in IP

// for learning mode
#define REG_IR_REC_INITADR                      ((0x00*0x10000)+ (IR_REG_REC_BASEMENT + 0x72*2))
    #define _IR_REC_INITADR_MSK                 0x1FF //[8:0] = KEYLEN1[0] | KEYLEN0[7:0]


//
//========================================================
//
//  Type definition
//
//========================================================
//
typedef enum
{
    IR_REC_KEY0 = 0,
    IR_REC_KEY1,
    IR_REC_KEY2,
    IR_REC_KEY3,
    IR_REC_KEY4,
    IR_REC_KEY5,

    IR_REC_KEYMAX
} E_IR_REC_KEY;

typedef struct _IR_RecBackup
{
    U32 u32TimeOutCycle;
    U8 u8ShotMode : 2;
    U8 u8DecodeMode : 2;
    U8 u8Reserved : 4;
    U8 u8ClkDivNum;

}IR_RecBackup;

//
//========================================================
//
//  Function declaration
//
//========================================================
//

void msIR_Rec_Finalize(IR_RecBackup* pstRecBkp);

void msIR_Rec_ComparingRoutine(void);

void msIR_Rec_LearningRoutine(void);

#endif // IR_LEARNING_MODE

/*****************************************************************************/


//----------------------------------------------------------------------------
#undef INTERFACE

#endif
