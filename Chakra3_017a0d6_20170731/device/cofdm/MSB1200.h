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

#ifndef _MSB1200_H_
#define _MSB1200_H_


#define MSB1200_EXT_Base(x)                 (0xCF00+x)

#define MSB1200_EXT_CONTROL                 MSB1200_EXT_Base(0)
#define MSB1200_EXT_STATUS                  MSB1200_EXT_Base(0x1)
#define MSB1200_EXT_TST                     MSB1200_EXT_Base(0x2)
#define MSB1200_EXT_ADC_0                   MSB1200_EXT_Base(0x3)
#define MSB1200_EXT_ADC_1                   MSB1200_EXT_Base(0x4)
#define MSB1200_EXT_ADC_V0                  MSB1200_EXT_Base(0x5)
#define MSB1200_EXT_ADC_V1                  MSB1200_EXT_Base(0x6)
#define MSB1200_EXT_ADC_RX0                 MSB1200_EXT_Base(0x7)
#define MSB1200_EXT_ADC_RX1                 MSB1200_EXT_Base(0x8)
#define MSB1200_EXT_ADC_INV                 MSB1200_EXT_Base(0x9)
#define MSB1200_EXT_ADC_FILTER0             MSB1200_EXT_Base(0xA)
#define MSB1200_EXT_ADC_FILTER1             MSB1200_EXT_Base(0xB)
#define MSB1200_EXT_ADC_C1                  MSB1200_EXT_Base(0xC)


#define MSB1200_TS_ENABLE                   BIT0
#define MSB1200_TS_CLK_POLARTY              BIT1


#define MSB1200_SW_RESET                    BIT0
//--------------------------------------------------------------------
#define MSB1200_VI_Base(x)                  (0xC800+x)

#define MSB1200_VI_COR_CTL                  MSB1200_VI_Base(0)
#define MSB1200_VI_SYNC_CTL                 MSB1200_VI_Base(0x4)
#define MSB1200_VI_SYNC_STATUS              MSB1200_VI_Base(0x8)
#define MSB1200_VI_COR_INTEN                MSB1200_VI_Base(0xC)
#define MSB1200_VI_COR_INTSTAT              MSB1200_VI_Base(0x10)
#define MSB1200_VI_COR_INTACTIVE            MSB1200_VI_Base(0x14)
#define MSB1200_VI_SYNC_THRESHOLD           MSB1200_VI_Base(0x18)
#define MSB1200_VI_SYNC_COUNT               MSB1200_VI_Base(0x1C)
#define MSB1200_VI_BER_TIMER_2              MSB1200_VI_Base(0x20)
#define MSB1200_VI_BER_TIMER_1              MSB1200_VI_Base(0x24)
#define MSB1200_VI_BER_TIMER_0              MSB1200_VI_Base(0x28)
#define MSB1200_VI_BER_1                    MSB1200_VI_Base(0x2C)
#define MSB1200_VI_BER_0                    MSB1200_VI_Base(0x30)

#define MSB1200_VI_INT_GOT_SYNC             BIT0
#define MSB1200_VI_INT_LOST_SYNC            BIT1
#define PHOENIC_VI_INT_SYNC_FAIL            BIT2
#define MSB1200_VI_INT_BER                  BIT3
#define MSB1200_VI_INT_BER_OVF              BIT4
#define MSB1200_VI_INT_FIFO_OVF             BIT5
#define MSB1200_VI_INT_GLOBAL               BIT7

//--------------------------------------------------------------------
//Define Register for BER-12282007
#define MSB1200_VIT_Base(x)                    (0xCC00+x)
#define MSB1200_PACKET_ERROR_COUNT_REG         MSB1200_VIT_Base(0x24)
#define MSB1200_PRE_VIT_STATUS_REG             MSB1200_VIT_Base(0x28)
#define MSB1200_PRE_VIT_VALUE_REG_BYTE1        MSB1200_VIT_Base(0x2C)
#define MSB1200_PRE_VIT_VALUE_REG_BYTE0        MSB1200_VIT_Base(0x30)
#define MSB1200_PRE_VIT_PERIOD_REG_BYTE2       MSB1200_VIT_Base(0x34)
#define MSB1200_PRE_VIT_PERIOD_REG_BYTE1       MSB1200_VIT_Base(0x38)
#define MSB1200_PRE_VIT_PERIOD_REG_BYTE0       MSB1200_VIT_Base(0x3C)
#define MSB1200_POST_VIT_STATUS_REG            MSB1200_VIT_Base(0x40)
#define MSB1200_POST_VIT_VALUE_REG_BYTE1       MSB1200_VIT_Base(0x44)
#define MSB1200_POST_VIT_VALUE_REG_BYTE0       MSB1200_VIT_Base(0x48)
#define MSB1200_POST_VIT_PERIOD_REG_BYTE2      MSB1200_VIT_Base(0x4C)
#define MSB1200_POST_VIT_PERIOD_REG_BYTE1      MSB1200_VIT_Base(0x50)
#define MSB1200_POST_VIT_PERIOD_REG_BYTE0      MSB1200_VIT_Base(0x54)
#define MSB1200_VIT_STATUS_NG                  (0X00)
#define MSB1200_VIT_STATUS_BUSY                (0X01)
#define MSB1200_VIT_STATUS_OK                  (0X02)
#define MSB1200_VIT_STATUS_OVER                (0X03)
#define MSB1200_SIGNAL_BASE_100                (0x00) //Post BER Value High Byte
#define MSB1200_SIGNAL_BASE_60                 (0x40) //Post BER Value High Byte
#define MSB1200_SIGNAL_BASE_10                 (0x80) //Post BER Value High Byte

//--------------------------------------------------------------------
#define MSB1200_RS_Base(x)                  (0xCC00+x)
#define MSB1200_RS_FEC_CTL                  MSB1200_RS_Base(0)
#define MSB1200_RS_FEC_STAT                 MSB1200_RS_Base(0x4)
#define MSB1200_RS_FEC_INTEN                MSB1200_RS_Base(0x8)
#define MSB1200_RS_FEC_INSTAT               MSB1200_RS_Base(0xC)
#define MSB1200_RS_FEC_SYNC_PARAM           MSB1200_RS_Base(0x10)
#define MSB1200_RS_FEC_ERROR_ACC_L          MSB1200_RS_Base(0x14)
#define MSB1200_RS_FEC_ERROR_ACC_H          MSB1200_RS_Base(0x18)
#define MSB1200_RS_FEC_PERIOD_L             MSB1200_RS_Base(0x1C)
#define MSB1200_RS_FEC_PERIOD_H             MSB1200_RS_Base(0x20)


#define MSB1200_RS_INT_GOT_SYNC            BIT0
#define MSB1200_RS_INT_LOST_SYNC           BIT1
#define MSB1200_RS_INT_DECODE_FAIL         BIT2
#define MSB1200_RS_INT_BER                 BIT3
#define MSB1200_RS_INT_GLOBAL              BIT7

//-------------------------------------------------------------------- // kk 0320-1 0329
#define MSB1200_RT_Base(x)                    (0xC400+x)
#define    MSB1200_COR_STAT_ADDR                MSB1200_RT_Base(0x04)
#define    MSB1200_TPS_RCVD_1_ADDR                MSB1200_RT_Base(0x9C)
#define    MSB1200_TPS_RCVD_2_ADDR                MSB1200_RT_Base(0xA0)
#define    MSB1200_TPS_RCVD_3_ADDR                MSB1200_RT_Base(0xA4)
#define    MSB1200_TPS_RCVD_4_ADDR                MSB1200_RT_Base(0xA8)

//--------------------------------------------------------------------
#define     DEMOD_SLAVE_ID          0x1E
#define     DEMOD_ADDR_H            0x00
#define     DEMOD_ADDR_L            0x01
#define     DEMOD_WRITE_REG         0x02
#define     DEMOD_WRITE_REG_EX      0x03
#define     DEMOD_READ_REG          0x04
#define     DEMOD_RAM_CONTROL       0x05

#define MSB1200_IIC_CONTROL                 0x8400
#define MSB1200_IIC_SCL_CLK                 0x8401
#define MSB1200_IIC_READ_DATA               0x8402
#define MSB1200_IIC_STATUS                  0x8403
#define MSB1200_IIC_WRITE_DATA              0x8404

typedef enum
{
    COFDM_FEC_LOCK,
    COFDM_TPS_LOCK,
    COFDM_SYMBOL_TIMING_LOCK,
    COFDM_AGC_LOCK,
    COFDM_DESCRAMBLER_LOCK,
    COFDM_BYTE_ALIGNER_LOCK
} COFDM_LOCK_STATUS;

typedef enum
{    //Hierarchy
    NON_HIER = 0x00,
    ALPHA_1 = 0x01,
    ALPHA_2 = 0x02,
    ALPHA_4 = 0x03,
    INVALID_HIER = 0xff,
} EN_TPS_HIERARCHY;

typedef enum
{    //Constellation
    QPSK = 0x00,
    QAM_16 = 0x01,
    QAM_64 = 0x02,
    INVALID_CNSL = 0xff,
} EN_TPS_CONSTELLATION;

typedef enum
{    //High Priority Stream Code Rate
    HP_1Y2 = 0x00,
    HP_2Y3 = 0x01,
    HP_3Y4 = 0x02,
    HP_5Y6 = 0x03,
    HP_7Y8 = 0x04,
    INVALID_HP = 0xff,
} EN_TPS_HP_CODE;

typedef enum
{    //Low Priority Stream Code Rate
    LP_1Y2 = 0x00,
    LP_2Y3 = 0x01,
    LP_3Y4 = 0x02,
    LP_5Y6 = 0x03,
    LP_7Y8 = 0x04,
    INVALID_LP = 0xff,
} EN_TPS_LP_CODE;

typedef enum
{    //Transmission Mode
    MODE_2K = 0x00,
    MODE_8K = 0x01,
    INVALID_MODE = 0xff,
} EN_TPS_MODEDET;

typedef enum
{    //Guard Interval
    GI_1Y32 = 0x00,
    GI_1Y16 = 0x01,
    GI_1Y8 = 0x02,
    GI_1Y4 = 0x03,
    INVALID_GI = 0xff,
} EN_TPS_GUARD_INTV;

#define COFDM_DEM_I2C_ID            DEMOD_SLAVE_ID
#endif
