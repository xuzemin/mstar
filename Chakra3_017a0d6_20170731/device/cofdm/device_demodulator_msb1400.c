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
 **********************************************************************/
#include "device_demodulator_msb1400.h"
#include <math.h>
#include "Tuner.h"
#include "drvIIC.h"
#include "MsOS.h"
#include "debug.h"

static MS_U8 MSB140X_LIB[]=
{
    #include "msb140x_isdbt.dat"
};
static MS_U16 u16Lib_size = sizeof(MSB140X_LIB);
static MAPI_U8 u8MsbData[6];

#define ERR_DEMOD_MSB(x)                //x
#define DBG_DOMOD_MSB(x)                //x
#define DBG_DEMOD_CHECK_LOCK(x)         //x
#define DBG_DEMOD_INFO(x)               //x
#define DBG_SSI(x)                      //x
#define DBG_SQI(x)                      //x

#define LOW_POWER_COMSUMPTION           1

#define MSB1400_REG_MB_CNTL             0x0C00
#define MSB1400_REG_MB_ADDR_L           0x0C02
#define MSB1400_REG_MB_ADDR_H           0x0C03
#define MSB1400_REG_MB_DATA             0x0C04
#define MSB1400_REG_MCU_RST             0x0B32   //0x0910
#define MSB1400_REG_IIC_BYPASS          0x0910
#define MSB1400_REG_MCU_FSM_EN          0x0C1C
#define MSB1400_REG_DEMOD_SW_RST        0x0B20
#define MSB1400_REG_ISDBT_LOCK_STATUS   0x2AF5 //(0x2a00+(0x7A)*2+1)
#define MSB1400_TDP_REG_BASE            0x0E00
#define MSB1400_FDP_REG_BASE            0x0F00
#define MSB1400_OUTER_REG_BASE          0x1100
#define MSB1400_FDPEXT_REG_BASE         0x1400
#define MSB1400_FE_REG_BASE             0x3E00

#define DEMOD_MSB140X_SLAVE_ID          0xD2

#define SRAM_BASE                       0x8000
#define LOAD_CODE_I2C_BLOCK_NUM         0x80

#define MSB1400_TUNER_IF                5000//3250

#define usleep(x)                       MsOS_DelayTask(x/1000)

MAPI_BOOL MSB1400_FECLock = MAPI_FALSE;
static S_msb1400_func msb1400_func;
S_msb1400_func*       iptr = NULL;
static MAPI_U32 u32ChkScanTimeStart = 0;
static MAPI_BOOL tmcc_ever_lock_flag = 0;
static MAPI_BOOL bDoReset = FALSE;

// For R820T tuner:
// RSSI valid range(E_ISDBT_SSIMethod2): < -48 dBm
#if defined(USE_TUNER_R820T)
static S_MSB_1400_IFAGC_SSI IfagcSsi[] =
{
    {-47,    0x8A},
    {-48,    0x8B},
    {-49,    0x8C},
    {-50,    0x8D},
    {-51,    0x8F},
    {-52,    0x90},
    {-53,    0x91},
    {-54,    0x92},
    {-55,    0x93},
    {-56,    0x95},
    {-57,    0x96},
    {-58,    0x97},
    {-59,    0x98},
    {-60,    0x9A},
    {-61,    0x9B},
    {-62,    0x9C},
    {-63,    0x9E},
    {-64,    0x9F},
    {-65,    0xA0},
    {-66,    0xA1},
    {-67,    0xA2},
    {-68,    0xA3},
    {-69,    0xA4},
    {-70,    0xA4},
    {-71,    0xA5},
    {-72,    0xA6},
    {-73,    0xA7},
    {-74,    0xA7},
    {-75,    0xA8},
    {-76,    0xA9},
    {-77,    0xAA},
    {-78,    0xAB},
    {-79,    0xAC},
    {-80,    0xAE},
    {-81,    0xAF},
    {-82,    0xB0},
    {-83,    0xB2},
    {-84,    0xB3},
    {-85,    0xB5},
    {-86,    0xB6},
    {-87,    0xB8},
    {-88,    0xBA},
    {-89,    0xBC},
    {-90,    0xC1},
    {-99,    0xFF},
};

static S_MSB_1400_RFAGC_SSI RfagcSsi[] =
{
    {-19.40,    0xA9},
    {-20.40,    0xAA},
    {-21.40,    0xAB},
    {-22.40,    0xAC},
    {-23.40,    0xAD},
    {-24.40,    0xAE},
    {-25.20,    0xAF},
    {-26.60,    0xB0},
    {-28.00,    0xB1},
    {-29.20,    0xB2},
    {-31.50,    0xB3},
    {-32.75,    0xB4},
    {-34.00,    0xB5},
    {-35.25,    0xB6},
    {-36.75,    0xB7},
    {-38.50,    0xB9},
    {-40.00,    0xBB},
    {-42.00,    0xBC},
    {-43.50,    0xBE},
    {-44.80,    0xC0},
    {-46.20,    0xC2},
    {-47.40,    0xC6},
    {-48.00,    0xCA},
    {-48.40,    0xD1},
    {-49.00,    0xE1},
    {-99.00,    0xFF},
};
#else
static S_MSB_1400_IFAGC_SSI IfagcSsi[] =
{
    {-47,    0x8A},
    {-48,    0x8B},
    {-49,    0x8C},
    {-50,    0x8D},
    {-51,    0x8F},
    {-52,    0x90},
    {-53,    0x91},
    {-54,    0x92},
    {-55,    0x93},
    {-56,    0x95},
    {-57,    0x96},
    {-58,    0x97},
    {-59,    0x98},
    {-60,    0x9A},
    {-61,    0x9B},
    {-62,    0x9C},
    {-63,    0x9E},
    {-64,    0x9F},
    {-65,    0xA0},
    {-66,    0xA1},
    {-67,    0xA2},
    {-68,    0xA3},
    {-69,    0xA4},
    {-70,    0xA4},
    {-71,    0xA5},
    {-72,    0xA6},
    {-73,    0xA7},
    {-74,    0xA7},
    {-75,    0xA8},
    {-76,    0xA9},
    {-77,    0xAA},
    {-78,    0xAB},
    {-79,    0xAC},
    {-80,    0xAE},
    {-81,    0xAF},
    {-82,    0xB0},
    {-83,    0xB2},
    {-84,    0xB3},
    {-85,    0xB5},
    {-86,    0xB6},
    {-87,    0xB8},
    {-88,    0xBA},
    {-89,    0xBC},
    {-90,    0xC1},
    {-99,    0xFF},
};

static S_MSB_1400_RFAGC_SSI RfagcSsi[] =
{
    {-19.40,    0xA9},
    {-20.40,    0xAA},
    {-21.40,    0xAB},
    {-22.40,    0xAC},
    {-23.40,    0xAD},
    {-24.40,    0xAE},
    {-25.20,    0xAF},
    {-26.60,    0xB0},
    {-28.00,    0xB1},
    {-29.20,    0xB2},
    {-31.50,    0xB3},
    {-32.75,    0xB4},
    {-34.00,    0xB5},
    {-35.25,    0xB6},
    {-36.75,    0xB7},
    {-38.50,    0xB9},
    {-40.00,    0xBB},
    {-42.00,    0xBC},
    {-43.50,    0xBE},
    {-44.80,    0xC0},
    {-46.20,    0xC2},
    {-47.40,    0xC6},
    {-48.00,    0xCA},
    {-48.40,    0xD1},
    {-49.00,    0xE1},
    {-99.00,    0xFF},
};
#endif

static MAPI_BOOL MSB140X_WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data);
static MAPI_BOOL MSB140X_ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data);
static MAPI_BOOL MSB140X_WriteRegs(MS_U16 u16Addr, MS_U8* u8pData, MS_U16 data_size);
MAPI_BOOL LoadDSPCode(void);

BOOLEAN I2c_writebytes(U8 u8AddrSize, U8 *pu8Addr, U16 u16Size, U8 *pu8Data)
{
    return MDrv_IIC_WriteBytes(DEMOD_MSB140X_SLAVE_ID, u8AddrSize, pu8Addr, u16Size, pu8Data);
}

BOOLEAN I2c_readbytes(U8 u8AddrSize, U8 *pu8Addr, U16 u16Size, U8 *pu8Data)
{
    return MDrv_IIC_ReadBytes(DEMOD_MSB140X_SLAVE_ID, u8AddrSize, pu8Addr, u16Size, pu8Data);
}

MAPI_BOOL DeviceDemodCreate(void)
{
    return MAPI_TRUE;
}

MAPI_BOOL Connect(void)
{
    return MAPI_TRUE;
}
MAPI_BOOL Disconnect(void)
{
    return MAPI_TRUE;
}
void Reset(void)
{
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][Reset()]Enter!!\n"));
    MSB140X_WriteReg(MSB1400_REG_DEMOD_SW_RST, 0x01);
    MSB140X_WriteReg(MSB1400_REG_MCU_RST, 0x03);
    usleep(5 *1000);
    MSB140X_WriteReg(MSB1400_REG_MCU_RST, 0x00);
    MSB140X_WriteReg(MSB1400_REG_DEMOD_SW_RST, 0x00);

    u32ChkScanTimeStart = MsOS_GetSystemTime();
    tmcc_ever_lock_flag = 0;
    bDoReset = TRUE;
}

MAPI_BOOL IIC_Bypass_Mode(MAPI_BOOL enable)
{
    MAPI_U8 u8Retry=10;
    MAPI_BOOL bRet = FALSE;
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][IIC_Bypass_Mode()]Enter!! Enable = %d\n", enable));
    while((u8Retry--) && (bRet == FALSE))
    {
        if (enable)
        {
            bRet = MSB140X_WriteReg(MSB1400_REG_IIC_BYPASS, 0x10);// IIC by-pass mode on
        }
        else
        {
            bRet = MSB140X_WriteReg(MSB1400_REG_IIC_BYPASS, 0x00);// IIC by-pass mode off
        }
        //usleep(500*1000);
    }
    return MAPI_TRUE;
}

MAPI_BOOL WriteDspReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;
    status &= MSB140X_WriteReg(MSB1400_REG_MB_DATA, u8Data);
    status &= MSB140X_WriteReg(MSB1400_REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= MSB140X_WriteReg(MSB1400_REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= MSB140X_WriteReg(MSB1400_REG_MB_CNTL, 0x04);

    do
    {
        status &= MSB140X_ReadReg(MSB1400_REG_MB_CNTL, &cntl);
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
    MAPI_U8     status = true;
    MAPI_U8     cntl = 0x00;
    MAPI_U16    cntr = 0x00;

    status &= MSB140X_WriteReg(MSB1400_REG_MB_ADDR_H, (MAPI_U8)(u16Addr >> 8));
    status &= MSB140X_WriteReg(MSB1400_REG_MB_ADDR_L, (MAPI_U8)(u16Addr));
    status &= MSB140X_WriteReg(MSB1400_REG_MB_CNTL, 0x03);

    do
    {
        status &= MSB140X_ReadReg(MSB1400_REG_MB_CNTL, &cntl);
        if(cntr++ > 0x7ff)
        {
            ERR_DEMOD_MSB(printf("MSB123X_MB_READ_FAILURE\n"));
            return false;
        }
    }
    while(cntl != 0xff);

    status &= MSB140X_ReadReg(MSB1400_REG_MB_DATA, pData);
    return status;
}

// MxL136 => FS: 24000 = 0x5DC0
#define ISDBT_FS_L_VAL    0x88
#define ISDBT_FS_H_VAL  0x13

// MxL136 => FC: 4000 = 0x0FA0
#define ISDBT_FC_L_VAL   (MSB1400_TUNER_IF&0xff)
#define ISDBT_FC_H_VAL   ((MSB1400_TUNER_IF>>8)&0xff)

// Auto IQ Swap
#define ISDBT_AUTO_IQ_SWAP_EN   0x01

#if defined(USE_TUNER_R820T)
// IQ Swap
#define ISDBT_IQ_SWAP   0x01
// AGC Ref for normal case
#define ISDBT_IFAGC_REF   0x38
#elif defined(USE_TUNER_MxL136)
// IQ Swap
#define ISDBT_IQ_SWAP   0x01
// AGC Ref for normal case
#define ISDBT_IFAGC_REF   0x58
#else
// IQ Swap
#define ISDBT_IQ_SWAP   0x01
// AGC Ref for normal case
#define ISDBT_IFAGC_REF   0x58
#endif

// ACI Enable
#define ISDBT_ACI_EN      0x01
// AGC Ref for ACI case
#define ISDBT_IFAGC_REF_ACI   0x58

// TS data inversion
#define ISDBT_TS_DATA_SWAP  0x00
// TS clock inverseion
#define ISDBT_TS_CLK_INV      0x01
// TS Series mode
#define ISDBT_TS_SERIAL      0x01

MAPI_BOOL ISDBT_DSPReg_Init(void)
{
    if(WriteDspReg((MAPI_U16)E_ISDBT_FS_L, ISDBT_FS_L_VAL) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_FS_H, ISDBT_FS_H_VAL) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_FC_L, ISDBT_FC_L_VAL) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_FC_H, ISDBT_FC_H_VAL) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_AUTO_IQ_SWAP_EN, ISDBT_AUTO_IQ_SWAP_EN) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_IQ_SWAP, ISDBT_IQ_SWAP) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_ACI_EN, ISDBT_ACI_EN) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_IFAGC_REF, ISDBT_IFAGC_REF) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_IFAGC_REF_ACI, ISDBT_IFAGC_REF_ACI) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_TS_DATA_SWAP, ISDBT_TS_DATA_SWAP) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }
    if(WriteDspReg((MAPI_U16)E_ISDBT_TS_SERIAL, ISDBT_TS_SERIAL) != TRUE)
    {
        printf("ISDBT dsp reg init NG\n");
    }

    return MAPI_TRUE;
}

MS_BOOL  I2C_Channel_Set(MS_U8 ch_num)
{
    MS_BOOL bRet=TRUE;
    MS_U8 Data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};

    if (iptr == NULL)
    {
        return FALSE;
    }
    DBG_DOMOD_MSB(printf("=======================>[Device_demodulator_msb1400.cpp][I2C_Channel_Set()]Enter channel %d!!\n", ch_num));

    //Exit
    Data[0] = 0x34;
    bRet &= iptr->WriteBytes(0, NULL, 1, Data);
    Data[0]=(ch_num & 0x01)? 0x36 : 0x45;
    bRet &= iptr->WriteBytes(0, NULL, 1, Data);
    //Init
    Data[0] = 0x53;
    bRet &= iptr->WriteBytes(0, NULL, 5, Data);
    Data[0]=(ch_num & 0x04)? 0x80 : 0x81;
    bRet &= iptr->WriteBytes(0, NULL, 1, Data);
    if ((ch_num==4)||(ch_num==5)||(ch_num==1))
        Data[0]=0x82;
    else
        Data[0] = 0x83;
     bRet &= iptr->WriteBytes(0, NULL, 1, Data);

    if ((ch_num==4)||(ch_num==5))
        Data[0]=0x85;
    else
        Data[0] = 0x84;

     bRet &= iptr->WriteBytes(0, NULL, 1, Data);
     Data[0]=(ch_num & 0x01)? 0x51 : 0x53;
     bRet &= iptr->WriteBytes(0, NULL, 1, Data);
     Data[0]=(ch_num & 0x01)? 0x37 : 0x7F;
     bRet &= iptr->WriteBytes(0, NULL, 1, Data);
     Data[0] = 0x35;
     bRet &= iptr->WriteBytes(0, NULL, 1, Data);
     Data[0] = 0x71;
     bRet &= iptr->WriteBytes(0, NULL, 1, Data);
     return bRet;
}

MAPI_BOOL MSB140x_HW_init(void)
{
    MAPI_BOOL bRet = true;

    // [0]        reg_mpll_clk_dp_pd    dummy
    // [1]        reg_adc_clk_pd        ADC output clock power down
    // [2]        reg_mpll_div2_pd    MPLL_DIV2 power down
    // [3]        reg_mpll_div3_pd    MPLL_DIV3 power down
    // [4]        reg_mpll_div4_pd    MPLL_DIV4 power down
    // [5]        reg_mpll_div8_pd    MPLL_DIV8 power down
    // [6]        reg_mpll_div10_pd    MPLL_DIV10 power down
    // [13:8]    reg_mpll_adc_div_sel    select the ADC clock divide ratio,ADC clk=XTAL_IN * (LOOP_DIV_FIRST*LOOP_DIV_SECOND)/div_ratio
    // divide ADC clock to 48Mhz = 24*36/18
    // wreg 0x0a 0x30 0x1200
    // divide ADC clock to 24Mhz = 24*36/36
    bRet &= MSB140X_WriteReg(0x0a00+0x30*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x30*2+1, 0x24);

    // -------------------------------------------------------------------
    // Initialize DMD_ANA_MISC
    // -------------------------------------------------------------------
    // [1:0]    reg_mpll_loop_div_first       feedback divider 00:div by 1 01:div by 2 10:div by 4 11:div by 8
    // [15:8]    reg_mpll_loop_div_second      feedback divider, div by binary data number
    // Loop divider ; VCO = 24*(2^2)*9 = 864
    bRet &= MSB140X_WriteReg(0x0a00+0x33*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x33*2+1, 0x12);

    // [15:0]    reg_mpll_test
    // [14]     mpll reset
    bRet &= MSB140X_WriteReg(0x0a00+0x34*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x34*2+1, 0x40);

    bRet &= MSB140X_WriteReg(0x0a00+0x34*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x34*2+1, 0x00);

    // [2:0]    reg_mpll_ictrl            charge pump current control
    // [3]        reg_mpll_in_sel         1.8V or 3.3V reference clock domain select (1'b0=0==>3.3 V reference clock domain)
    // [4]        reg_mpll_xtal2adc_sel        select the XTAL clock bypass to MPLL_ADC_CLK
    // [5]        reg_mpll_xtal2next_pll_sel    crystal clock bypass to next PLL select
    // [6]        reg_mpll_vco_offset     set VCO initial offset frequency
    // [7]        reg_mpll_pd         gated reference clock and power down PLL analog_3v: 1=power down
    // [8]        reg_xtal_en         XTAL enable register; 1: enable
    // [10:9]    reg_xtal_sel            XTAL driven strength select.
    // [11]     reg_mpll_porst            MPLL input    power on reset, connect to reg as MPLL_RESET
    // [12]     reg_mpll_reset            PLL software reset; 1:reset
    // [13]     reg_pd_dmpll_clk        XTAL to MPLL clock reference power down
    // [14]     reg_pd_3p3_1            XTAL to CLK_24M_3P3_1 power down
    // [15]     reg_pd_3p3_2            XTAL to CLK_24M_3P3_2 power down
    // MPLL reset
    bRet &= MSB140X_WriteReg(0x0a00+0x35*2, 0x04);
    bRet &= MSB140X_WriteReg(0x0a00+0x35*2+1, 0x18);

    // release MPLl reset
    bRet &= MSB140X_WriteReg(0x0a00+0x35*2, 0x04);
    bRet &= MSB140X_WriteReg(0x0a00+0x35*2+1, 0x00);

    // --- SAR_ADC ---
    // [0]        reg_sar_pd
    // [4]        reg_sar_freerun
    // [5]        reg_sar_cksamp
    // enable SAR
    bRet &= MSB140X_WriteReg(0x0a00+0x3C*2, 0x10);
    bRet &= MSB140X_WriteReg(0x0a00+0x3C*2+1, 0x00);

    // -------------------------------------------------------------------
    // Initialize ADC I/Q
    // -------------------------------------------------------------------
    // [2]        reg_mux_clpz        I channel clamp enable. 0:enable, 1:disable
    // [6:4]    reg_muxs        I channel input mux control;
    //                    3'b000=I channel ADC calibration mode input
    //                    3'b001=VIF signal from VIFPGA
    //                    3'b100=DVB or ATSC mode input from PAD_I(Q)P(M)
    //                    all the other combination are only for test mode, don't use without understanding.
    // [12]     reg_iq_swap     ADC I,Q swap enable; 1: swap
    // [13]     reg_iqclk_sel        ADC clock out select; 1: ADC_CLKQ
    // [14]     reg_lincal_bypass    ADC linear calibration bypass enable; 1:enable
    // [15]     reg_pwr_sel     ADC internal 1.2v regulator control always 0 in T3
    // Set IMUXS QMUXS
    bRet &= MSB140X_WriteReg(0x0a00+0x01*2, 0x40);
    bRet &= MSB140X_WriteReg(0x0a00+0x01*2+1, 0x04);

    // [4:0]    reg_adc_gain
    // [6:5]    reg_iclpstr
    // [14:13]    reg_qclpstr
    // Set ADC gain is 1
    bRet &= MSB140X_WriteReg(0x0a00+0x0b*2, 0x0E);        //0x05;
    bRet &= MSB140X_WriteReg(0x0a00+0x0b*2+1, 0x00);    //0x05;

    // [0]        reg_pwdn_adci        Channel I ADC power down: 1=power dwon
    // [1]        reg_pwdn_adcq        Channel Q ADC power down: 1=power dwon
    // [2]        reg_pwdn_clpbuf     power down clamp buffer for test mode
    // [3]        reg_adc_refv_s        change ADC reference voltage for SSIF
    // [6:4]    reg_adc_bias_ctrl    ADC source bias current control
    // [9:8]    reg_amp_gain        XTAL receiver amp gain
    // Set enable ADC clock
    bRet &= MSB140X_WriteReg(0x0a00+0x0C*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x0C*2+1, 0x00);

    //=========LOW_POWER_COMSUMPTION=========//
#if (LOW_POWER_COMSUMPTION)
    bRet &= MSB140X_WriteReg(0x0a00+0x08*2, 0x01);

    bRet &= MSB140X_WriteReg(0x0a00+0x09*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x09*2+1, 0x01);

    // [0]        reg_pwdn_adci        Channel I ADC power down: 1=power dwon
    // [1]        reg_pwdn_adcq        Channel Q ADC power down: 1=power dwon
    // [2]        reg_pwdn_clpbuf     power down clamp buffer for test mode
    // [3]        reg_adc_refv_s        change ADC reference voltage for SSIF
    // [6:4]    reg_adc_bias_ctrl    ADC source bias current control
    // [9:8]    reg_amp_gain        XTAL receiver amp gain
    // Set enable ADC clock
    bRet &= MSB140X_WriteReg(0x0a00+0x0C*2, 0x50);
#else
    bRet &= MSB140X_WriteReg(0x0a00+0x08*2, 0x00);

    bRet &= MSB140X_WriteReg(0x0a00+0x09*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x09*2+1, 0x00);

    // [0]        reg_pwdn_adci        Channel I ADC power down: 1=power dwon
    // [1]        reg_pwdn_adcq        Channel Q ADC power down: 1=power dwon
    // [2]        reg_pwdn_clpbuf     power down clamp buffer for test mode
    // [3]        reg_adc_refv_s        change ADC reference voltage for SSIF
    // [6:4]    reg_adc_bias_ctrl    ADC source bias current control
    // [9:8]    reg_amp_gain        XTAL receiver amp gain
    // Set enable ADC clock
    bRet &= MSB140X_WriteReg(0x0a00+0x0C*2, 0x00);
#endif
    // [3:0]    reg_vclp        clamp voltage control
    //                    3'b000 = 0.7v
    //                    3'b001 = 0.75v
    //                    3'b010 = 0.5v
    //                    3'b011 = 0.4v
    //                    3'b100 = 0.8v
    //                    3'b101 = 0.9v
    //                    3'b110 = 0.65v
    //                    3'b111 = 0.60v
    // [4]        reg_pwdn_ref        REFERENCE power down
    // Disable PWDN_REF
    bRet &= MSB140X_WriteReg(0x0a00+0x20*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x20*2+1, 0x00);

    // [11:0]    reg_adc_offset_i
    // ADC I channel offset
    bRet &= MSB140X_WriteReg(0x0a00+0x2a*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x2a*2+1, 0x0c);

    // [11:0]    reg_adc_offset_q
    // ADC Q channel offset
    bRet &= MSB140X_WriteReg(0x0a00+0x2b*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x2b*2+1, 0x0c);

    // [0]        reg_adcin_sign
    // [4]        reg_ext_adc
    // [5]        reg_adc_iq_swap
    // [8]        reg_adcd_frz
    // [9]        reg_adc_rdsel
    // [14:12]    reg_adc_pll_debug_sel
    // Disable ADC Sign bit
    bRet &= MSB140X_WriteReg(0x0a00+0x2e*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x2e*2+1, 0x00);

    // [15:0]    reg_mpll_test
    // [4]        mpll lock detector enable
    bRet &= MSB140X_WriteReg(0x0a00+0x34*2, 0x10);
    bRet &= MSB140X_WriteReg(0x0a00+0x34*2+1, 0x00);
    // -------------------------------------------------------------------
    // Release clock gating
    // -------------------------------------------------------------------
    // [1:0]    reg_iicm_pad_sel
    // [4]        reg_i2c_sbpm_en
    // [12:8]    reg_i2c_sbpm_idle_num
    bRet &= MSB140X_WriteReg(0x0900+0x08*2, 0x01);
    bRet &= MSB140X_WriteReg(0x0900+0x08*2+1, 0x0a);

    // [0]        reg_xtal_en
    // [9:8]    reg_clk_pd_iic
    // [10]     reg_clk_pd_all
    bRet &= MSB140X_WriteReg(0x0900+0x09*2, 0x01);
    bRet &= MSB140X_WriteReg(0x0900+0x09*2+1, 0x01);

    // [3:0]    reg_ckg_adcd
    // [7:4]    reg_ckg_sadc
    // [11:8]    reg_ckg_iicm
    // [13:12]    reg_ckg_sbus
    bRet &= MSB140X_WriteReg(0x0900+0x0a*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x0a*2+1, 0x04);

    // [5:0]    reg_ckg_mcu
    // [6]        reg_power_good_mask
    // [11:8]    reg_ckg_inner
    // [15:12]    reg_ckg_adcd_d2
    // [4:2]    mcu clk setting
    // [5] 1:Clk from cystal(24M Hz).  0: Select Clk from [4:2] Registers.
    // This setting only works for "After a period time of MCU reset"
    // Dynamic Mcu clk setting usage:
    // 1. FW code need to run with crystal clk for a period time.
    // 2. set [4:2] Registers.
    // 3. set [5] from 1 to 0.
    bRet &= MSB140X_WriteReg(0x0900+0x0b*2, 0x30);
    bRet &= MSB140X_WriteReg(0x0900+0x0b*2+1, 0x00);

    // @0x09 0x10
    // [3:0]    reg_ckg_isdbt_adc
    // [6:4]    reg_ckg_isdbt_inner1x
    // [10:8]    reg_ckg_isdbt_inner2x
    // [14:12]    reg_ckg_isdbt_inner4x
    bRet &= MSB140X_WriteReg(0x0900+0x10*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x10*2+1, 0x00);

    // @0x09 0x11
    // [2:0]    reg_ckg_isdbt_outer1x
    // [6:4]    reg_ckg_isdbt_outer4x
    // [10:8]    reg_ckg_isdbt_outer6x
    // [10:8]    reg_ckg_isdbt_outer12x
    bRet &= MSB140X_WriteReg(0x0900+0x11*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x11*2+1, 0x00);

    // @0x09 0x12
    // [3:0]    reg_ckg_isdbt_ts
    // [4]        reg_isdbt_ts_out_mode
    // [5]        reg_isdbt_ts_clk_pol
    // [15:8]    reg_isdbt_ts_clk_divnum; TS Clk Rate= 216 MHz/reg_isdbt_ts_clk_divnum
    // TS Clk = 216/31= 6.967 MHz
    bRet &= MSB140X_WriteReg(0x0900+0x12*2, 0x08|(ISDBT_TS_CLK_INV<<5));
    bRet &= MSB140X_WriteReg(0x0900+0x12*2+1, 0x1F);    //0x00);

    // [3:0]    reg_ckg_isdbt_sram_tdi
    // [7:4]    reg_ckg_isdbt_outer_rs
    bRet &= MSB140X_WriteReg(0x0900+0x14*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x14*2+1, 0x00);

    // [14:12]    reg_ckg_syn_ts
    bRet &= MSB140X_WriteReg(0x0900+0x1b*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x1b*2+1, 0x00);

    // [8]        reg_turn_off_pad
    bRet &= MSB140X_WriteReg(0x0900+0x28*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x28*2+1, 0x00);

    // --- TS PAD_MUX ---
    // [15:0]    reg_en_ts_pad
    bRet &= MSB140X_WriteReg(0x0900+0x2d*2, 0xff);
    bRet &= MSB140X_WriteReg(0x0900+0x2d*2+1, 0xff);

    // [0]        reg_en_ts_err_pad
    // [4]        reg_ts_err_pol
    bRet &= MSB140X_WriteReg(0x0900+0x2e*2, 0x01);
    bRet &= MSB140X_WriteReg(0x0900+0x2e*2+1, 0x00);

    // IF AGC Enable
    bRet &= MSB140X_WriteReg(0x0a00+0x18*2, 0x10);

    // --- IF ADC ---
    // [2:0]    reg_acl_ref
    // [5:4]    reg_acl_isel
    // [8]        reg_xtal_pm_isel
    // [9]        reg_bond_mode
    // [10]     reg_clk_bond_mode
    // [11]     reg_clk_usb_3p3_en
    // [13:12]    reg_iq_ctrl = 2'd1
    bRet &= MSB140X_WriteReg(0x0a00+0x19*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0a00+0x19*2+1, 0x1e);

    // // --- ZIF ADC ---
    // // [5:0] reg_ckg_mcu
    // // [6]    reg_power_good_mask
    // // [11:8]    reg_ckg_inner
    // // [15:12]    reg_ckg_adcd_d2
    // wreg 0x09 0x0b 0x4430
    //
    // // [3:0] reg_ckg_isdbt_adc
    // // [6:4] reg_ckg_isdbt_inner1x
    // // [10:8]    reg_ckg_isdbt_inner2x
    // // [14:12]    reg_ckg_isdbt_inner4x
    // wreg 0x09 0x10 0x0004
    //
    // // [1:0] reg_chanout_sel
    // // [2]    reg_iq_filter_enable    = 1
    // // [3]    reg_iq_filter_sel
    // // [5:4] reg_adc_debug_clk_sel
    // wreg 0x0a 0x17 0x0004
    // -------------------------------------------------------------------
    // Initialize Transport Stream synthesizer and APLL
    // -------------------------------------------------------------------
    // [0]        reg_synth_reset
    // [1]        reg_synth_ssc_en
    // [2]        reg_synth_ssc_mode
    // [4]        reg_synth_sld
    bRet &= MSB140X_WriteReg(0x0900+0x50*2, 0x10);
    bRet &= MSB140X_WriteReg(0x0900+0x50*2+1, 0x00);

    bRet &= MSB140X_WriteReg(0x0900+0x50*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x50*2+1, 0x00);

    // [15:0]    reg_synth_set[15: 0]
    // [ 7:0]    reg_synth_set[23:16]
    // SET = clk_ref(216MHz) * 524288 / clk_out(36MHz)
    bRet &= MSB140X_WriteReg(0x0900+0x51*2, 0x00);
    bRet &= MSB140X_WriteReg(0x0900+0x51*2+1, 0x00);

    bRet &= MSB140X_WriteReg(0x0900+0x52*2, 0x30);
    bRet &= MSB140X_WriteReg(0x0900+0x52*2+1, 0x00);

    // [0]        reg_apll_pd
    // [1]        reg_apll_reset
    // [2]        reg_apll_porst
    // [3]        reg_apll_vco_offset
    // [6]        reg_apll_clkin_sel
    // [12:8]    reg_apll_postdiv    // div = 2 * reg_apll_postdiv
    bRet &= MSB140X_WriteReg(0x0900+0x55*2, 0x06);
    bRet &= MSB140X_WriteReg(0x0900+0x55*2+1, 0x14);

    bRet &= MSB140X_WriteReg(0x0900+0x55*2, 0x10);
    bRet &= MSB140X_WriteReg(0x0900+0x55*2+1, 0x14);

    // [1:0]    reg_apll_loop_div_first
    // [15:8]    reg_apll_loop_div_second
    bRet &= MSB140X_WriteReg(0x0900+0x57*2, 0x01);
    bRet &= MSB140X_WriteReg(0x0900+0x57*2+1, 0x01);

    // [16:0]    reg_apll_test
    // [4]        lock detector enable
    bRet &= MSB140X_WriteReg(0x0900+0x59*2, 0x10);
    bRet &= MSB140X_WriteReg(0x0900+0x59*2+1, 0x00);

    return bRet;
}

MAPI_BOOL Power_On_Initialization(void)
{
    MAPI_U8 status = true;
    MSB1400_FECLock = MAPI_FALSE;
    DBG_DOMOD_MSB(printf("=======================>[Device_demodulator_msb1400.cpp][Power_On_Initialization()]Enter!!\n"));
    printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    // Initialize I2C to channel 0
    status &= I2C_Channel_Set(0);

    //// Firmware download //////////
    // Load Dsp code from Lib
    if (LoadDSPCode() == MAPI_FALSE)
    {
        DBG_DOMOD_MSB(printf(">>>Load MSB140x DSP:Fail \n"));
        return MAPI_FALSE;
    }
    else
    {
        DBG_DOMOD_MSB(printf(">>>Load MSB140x DSP:OK \n"));
    }
    usleep(10 * 1000);

    // Initialize HW Setting
    status &= MSB140x_HW_init();

    // Initialize parameters by SW MailBox
    status = ISDBT_DSPReg_Init();

    return status;
}

MAPI_BOOL Set_PowerOn(void)
{
    return TRUE;
}

MAPI_BOOL Set_PowerOff(void)
{
    return TRUE;
}

MAPI_BOOL Active(MAPI_BOOL bEnable)
{
    MAPI_U8 status = true;
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][Active()] Enter !!\n"));
    if (bEnable)
        status &= MSB140X_WriteReg(MSB1400_REG_MCU_FSM_EN, 0x01);
    else
        status &= MSB140X_WriteReg(MSB1400_REG_MCU_FSM_EN, 0x00);
    return status;
}

U8 GetCurrentDemodulatorType(void)
{
    return 0;
}

MAPI_BOOL DTV_GetPacketError(void)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data, u8FrzData;
    MAPI_U16 u16PacketErrA = 0, u16PacketErrB = 0, u16PacketErrC = 0;

    // Read packet errors of three layers
    // OUTER_FUNCTION_ENABLE
    // [8] reg_biterr_num_pcktprd_freeze
    // Freeze Packet error
    status &= MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x01*2+1, &u8FrzData);
    u8Data = u8FrzData | _BIT0;
    status &= MSB140X_WriteReg(MSB1400_OUTER_REG_BASE+0x01*2+1, u8Data);

    // [15:0] OUTER_UNCRT_PKT_NUM_PCKTPRD_A
    status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x08*2+1, &u8Data);
    u16PacketErrA = u8Data << 8;
    status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x08*2, &u8Data);
    u16PacketErrA = u16PacketErrA | u8Data;

    // [15:0] OUTER_UNCRT_PKT_NUM_PCKTPRD_B
    status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x21*2+1, &u8Data);
    u16PacketErrB = u8Data << 8;
    status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x21*2, &u8Data);
    u16PacketErrB = u16PacketErrB | u8Data;

    // [15:0] OUTER_UNCRT_PKT_NUM_PCKTPRD_C
    status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x42*2+1, &u8Data);
    u16PacketErrC = u8Data << 8;
    status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x42*2, &u8Data);
    u16PacketErrC = u16PacketErrC | u8Data;

    // Unfreeze Packet error
    status &= MSB140X_WriteReg(MSB1400_OUTER_REG_BASE+0x01*2+1, u8FrzData);

    printf("[device_demodulator_msb1400.cpp][ DTV_GetPacketError()]PacketError A = %d, PacketError B = %d, PacketError C = %d\n", u16PacketErrA, u16PacketErrB, u16PacketErrC);

    return status;
}

MAPI_BOOL ExtendCmd(MAPI_U8 SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void *pvParam3)
{
    u32Param1 = u32Param1;
    u32Param2 = u32Param2;

    // Check if demod lock or not.
    if(SubCmd == 0xFF)  // temp solution, only for internal use, can't be called by upper layer
    {
        MAPI_U32    u32Timeout = 0;
        MAPI_U8     u8Data = 0;
        MAPI_BOOL   bCheckPass = FALSE;
        MAPI_U32    u32NowTime = MsOS_GetSystemTime();

        // Fast Timeout of Demod Lock
        u32Timeout = 300;    //200

        // ISDBT_LOCK_STATUS
        // [0] F_FSATRACK_LOCKED
        // [1] F_FEC_LOCKED
        // [2] F_PSYNC_LOCKED
        // [7] F_ICFO_CH_EXIST_FLAG
        MSB140X_ReadReg(MSB1400_REG_ISDBT_LOCK_STATUS, &u8Data);
        //  DBG_DOMOD_MSB(printf("*****************>[device_demodulator_msb1400.cpp][ExtendCmd()] Lock Status = 0x%x\n", u8Data));
        //  Check FEC Lock Flag
        if((u8Data & 0x02) != 0x00)
            bCheckPass = MAPI_TRUE;
        else
        {
            // Now tmcc_ever_lock_flag is not used.
            if (tmcc_ever_lock_flag == 0)
            {
                // Check if CH exists
                if((u8Data & 0x80) != 0x00)
                {
                    u32Timeout=2000;//2000;
                    if (bDoReset)
                    {
                        DBG_DOMOD_MSB(printf("---------------------->DTV_ISDB_GetLockStatus(ICFO do 2nd) TIME = %ld(=%ld-%ld) ms\n", u32NowTime - u32ChkScanTimeStart, u32NowTime, u32ChkScanTimeStart)); //to measure time
                    }
                }
            }
        }

        if(bCheckPass)
        {
            if (bDoReset)
            {
                DBG_DOMOD_MSB(printf("---------------------->DTV_ISDB_GetLockStatus(LOCK) TIME = %ld(=%ld-%ld) ms\n", u32NowTime - u32ChkScanTimeStart, u32NowTime, u32ChkScanTimeStart)); //to measure time
            }

            //  DTV_GetPacketError();

            bDoReset = FALSE;
            MSB1400_FECLock = MAPI_TRUE;
            *((EN_MSB_1400_LOCK_STATUS *)pvParam3) = E_MSB_1400_DEMOD_LOCK;
        }
        else if(u32NowTime - u32ChkScanTimeStart < u32Timeout)
        {
            MSB1400_FECLock = MAPI_FALSE;
            *((EN_MSB_1400_LOCK_STATUS *)pvParam3) = E_MSB_1400_DEMOD_CHECKING;
        }
        else
        {
            MSB1400_FECLock = MAPI_FALSE;
            *((EN_MSB_1400_LOCK_STATUS *)pvParam3) = E_MSB_1400_DEMOD_UNLOCK;
        }
    }
    return MAPI_TRUE;
}

MAPI_BOOL DTV_SetFrequency(MAPI_U32 u32Frequency, RF_CHANNEL_BANDWIDTH eBandWidth, MAPI_BOOL bPalBG, MAPI_BOOL bLPsel)
{
    //MAPI_BOOL b_pal_bg;
    MAPI_BOOL bStatus = MAPI_FALSE;
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][DTV_SetFrequency()] Enter!!\n"));
    MSB1400_FECLock = MAPI_FALSE;

    u32Frequency = u32Frequency;
    eBandWidth = eBandWidth;
    bPalBG = bPalBG;
    bLPsel = bLPsel;

    // Reset
    Reset();
    usleep(500);

    bStatus = Active(MAPI_TRUE);
    if (bStatus == MAPI_FALSE)
    {
        printf("Demod Active failed \n");
        return MAPI_FALSE;
    }
    u32ChkScanTimeStart = MsOS_GetSystemTime();
    return MAPI_TRUE;
}

BOOLEAN DTV_ISDB_GetLockStatus(COFDM_LOCK_STATUS eStatus)
{
    BOOLEAN ret_lock = FALSE;
    U8      u8Data = 0;
    DBG_DEMOD_INFO(EN_ISDBT_Layer LayerIndex = E_ISDBT_Layer_A;)
    DBG_DEMOD_INFO(EN_ISDBT_FFT_VAL eFFTValue;)
    DBG_DEMOD_INFO(EN_ISDBT_CONSTEL_TYPE eQamValue;)
    DBG_DEMOD_INFO(EN_ISDBT_CODE_RATE eCodeRate;)
    DBG_DEMOD_INFO(EN_ISDBT_GUARD_INTERVAL eGI;)
    DBG_DEMOD_INFO(EN_ISDBT_TIME_INTERLEAVING eTdi;)

    DBG_DEMOD_CHECK_LOCK(EN_ISDBT_Layer LayerIndex = E_ISDBT_Layer_A;)
    DBG_DEMOD_CHECK_LOCK(float p_postBer = 1.0;)
    DBG_DEMOD_CHECK_LOCK(MAPI_U16 p_PktErr = 0xFFFF;)

    // ISDBT_LOCK_STATUS
    // [0] F_FSATRACK_LOCKED
    // [1] F_FEC_LOCKED
    // [2] F_PSYNC_LOCKED
    // [7] F_ICFO_CH_EXIST_FLAG
    MSB140X_ReadReg(MSB1400_REG_ISDBT_LOCK_STATUS, &u8Data);
    printf("DTV_ISDB_GetLockStatus : 0x%X \n", u8Data);

    DBG_DEMOD_CHECK_LOCK(MSB140X_GetPacketError(LayerIndex, &p_PktErr);)
    DBG_DEMOD_CHECK_LOCK(DTV_GetSNR();)
    DBG_DEMOD_CHECK_LOCK(MSB140X_GetPostBER(LayerIndex, &p_postBer);)
    DBG_DEMOD_INFO(eFFTValue = DTV_ISDBT_GetSignalFFTValue();)
    DBG_DEMOD_INFO(eQamValue = DTV_ISDBT_GetSignalModulation(LayerIndex);)
    DBG_DEMOD_INFO(eCodeRate = DTV_ISDBT_GetSignalCodeRate(LayerIndex);)
    DBG_DEMOD_INFO(eGI = DTV_ISDBT_GetSignalGuardInterval();)
    DBG_DEMOD_INFO(eTdi = DTV_ISDBT_GetSignalTimeInterleaving(LayerIndex);)
//    DBG_SQI(DTV_GetSignalQuality();)
//    DBG_SSI(DTV_GetSignalStrength();)


    switch (eStatus)
    {
        case COFDM_FSATRACK_LOCK:
            if (u8Data & BIT0) ret_lock = TRUE;
            break;
        case COFDM_FEC_LOCK:
            if (u8Data & BIT1) ret_lock = TRUE;
            break;
        case COFDM_PSYNC_LOCK:
            if (u8Data & BIT2) ret_lock = TRUE;
            break;
        case COFDM_ICFO_CH_EXIST_FLAG:
        case COFDM_TPS_LOCK:
            if (u8Data & BIT7) ret_lock = TRUE;
            break;
        default:
            break;
    }

    return ret_lock;
}

MAPI_BOOL MSB140X_GetPostBER(EN_ISDBT_Layer LayerIndex, float *p_postBer)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data, u8FrzData;
    MAPI_U32 u32RegPostVitbiA = 0, u32RegPostVitbiB = 0, u32RegPostVitbiC = 0;
    MAPI_U16 u16RegPcktprdA = 0, u16RegPcktprdB = 0, u16RegPcktprdC = 0;
//    float PostVitBER_A = 1.0, PostVitBER_B = 1.0, PostVitBER_C = 1.0;

    // Read post-Viterbi of three layers
    // [4] reg_rd_freezeber
    // biterr num pcktprd freeze
    status &= MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x01*2+1, &u8FrzData);
    u8Data = u8FrzData | _BIT0;
    status &= MSB140X_WriteReg(MSB1400_OUTER_REG_BASE+0x01*2+1, u8Data);

    switch(LayerIndex) {
        case E_ISDBT_Layer_A:
            // ==============Post-ViterbiBER of Layer A===============//
            // [31:0] reg_biterr_num_pcktprd_a
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x0b*2+1, &u8Data);
            u32RegPostVitbiA = u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x0b*2, &u8Data);
            u32RegPostVitbiA = (u32RegPostVitbiA<<8) | u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x0a*2+1, &u8Data);
            u32RegPostVitbiA = (u32RegPostVitbiA<<8) | u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x0a*2, &u8Data);
            u32RegPostVitbiA = (u32RegPostVitbiA<<8) | u8Data;

            // [15:0] reg_biterr_pcktprd_a
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x05*2+1, &u8Data);
            u16RegPcktprdA = u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x05*2, &u8Data);
            u16RegPcktprdA = (u16RegPcktprdA<<8) | u8Data;

            if (u16RegPcktprdA == 0)
                u16RegPcktprdA = 1;

            *p_postBer = (float)u32RegPostVitbiA/(u16RegPcktprdA*128*188*8); // pkt, symb, bit
            break;
         case E_ISDBT_Layer_B:
            // ==============Post-ViterbiBER of Layer B===============//
            // [31:0] reg_biterr_num_pcktprd_b
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x24*2+1, &u8Data);
            u32RegPostVitbiB = u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x24*2, &u8Data);
            u32RegPostVitbiB = (u32RegPostVitbiB<<8) | u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x23*2+1, &u8Data);
            u32RegPostVitbiB = (u32RegPostVitbiB<<8) | u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x23*2, &u8Data);
            u32RegPostVitbiB = (u32RegPostVitbiB<<8) | u8Data;

            // [15:0] reg_biterr_pcktprd_b
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x1d*2+1, &u8Data);
            u16RegPcktprdB = u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x1d*2, &u8Data);
            u16RegPcktprdB = (u16RegPcktprdB<<8) | u8Data;

            if (u16RegPcktprdB == 0)
                u16RegPcktprdB = 1;

            *p_postBer = (float)u32RegPostVitbiB/(u16RegPcktprdB*128*188*8); // pkt, symb, bit
            break;
         case E_ISDBT_Layer_C:
            // ==============Post-ViterbiBER of Layer C===============//
            // [31:0] reg_biterr_num_pcktprd_C
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x45*2+1, &u8Data);
            u32RegPostVitbiC = u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x45*2, &u8Data);
            u32RegPostVitbiC = (u32RegPostVitbiC<<8) | u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x44*2+1, &u8Data);
            u32RegPostVitbiC = (u32RegPostVitbiC<<8) | u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x44*2, &u8Data);
            u32RegPostVitbiC = (u32RegPostVitbiC<<8) | u8Data;

            // [15:0] reg_biterr_pcktprd_c
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x1f*2+1, &u8Data);
            u16RegPcktprdC = u8Data;
            status = MSB140X_ReadReg(MSB1400_OUTER_REG_BASE+0x1f*2, &u8Data);
            u16RegPcktprdC = (u16RegPcktprdC<<8) | u8Data;

            if (u16RegPcktprdC == 0)
                u16RegPcktprdC = 1;

            *p_postBer = (float)u32RegPostVitbiC/(u16RegPcktprdC*128*188*8); // pkt, symb, bit
            break;
         default:
            *p_postBer = (float)1.0;
            break;
    }

    // Unfreeze biterr num pcktprd
    status &= MSB140X_WriteReg(MSB1400_OUTER_REG_BASE+0x01*2+1, u8FrzData);

#if 0
    if (LayerIndex == mapi_demodulator::E_ISDBT_Layer_A)
        DBG_DEMOD_CHECK_LOCK(printf("[device_demodulator_msb1400.cpp][MSB140X_GetPostBER()]PostViterbi A = %f\n", *p_postBer);)
    else if (LayerIndex == mapi_demodulator::E_ISDBT_Layer_B)
        DBG_DEMOD_CHECK_LOCK(printf("[device_demodulator_msb1400.cpp][MSB140X_GetPostBER()]PostViterbi B = %f\n", *p_postBer);)
    else if (LayerIndex == mapi_demodulator::E_ISDBT_Layer_C)
        DBG_DEMOD_CHECK_LOCK(printf("[device_demodulator_msb1400.cpp][MSB140X_GetPostBER()]PostViterbi C = %f\n", *p_postBer);)
    else
        DBG_DEMOD_CHECK_LOCK(printf("[device_demodulator_msb1400.cpp][MSB140X_GetPostBER()]Layer Index is wrong!!\n");)
#endif
    return status;
}

EN_ISDBT_FFT_VAL DTV_ISDBT_GetSignalFFTValue(void)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data = 0, u8Mode = 0;
    EN_ISDBT_FFT_VAL eFFTValue = E_ISDBT_FFT_INVALID;

    // [5:4]    reg_mcd_out_mode
    // output mode  -> 00: 2k
    //                         01: 4k
    //                         10: 8k
    status &= MSB140X_ReadReg(MSB1400_TDP_REG_BASE+0x34*2, &u8Data);
    u8Mode  = (u8Data >> 4) & 0x03;

    switch(u8Mode) {
        case 0:
            eFFTValue = E_ISDBT_FFT_2K;
            break;
        case 1:
            eFFTValue = E_ISDBT_FFT_4K;
            break;
        case 2:
            eFFTValue = E_ISDBT_FFT_8K;
            break;
        default:
            break;
    }

    DBG_DEMOD_INFO(printf("[device_demodulator_msb1400.cpp][DTV_ISDBT_GetSignalFFTValue()]FFT Mode = %d\n", eFFTValue);)

    return eFFTValue;
}

EN_ISDBT_CONSTEL_TYPE DTV_ISDBT_GetSignalModulation(EN_ISDBT_Layer LayerIndex)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data = 0, u8QAM = 0;
    EN_ISDBT_CONSTEL_TYPE eQamValue = E_ISDBT_QAM_INVALID;

    switch(LayerIndex) {
        case E_ISDBT_Layer_A:
            // [6:4] reg_tmcc_cur_carrier_modulation_a
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x04*2, &u8Data);
            u8QAM = (u8Data >> 4) & 0x07;
            break;
        case E_ISDBT_Layer_B:
            // [6:4] reg_tmcc_cur_carrier_modulation_b
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x05*2, &u8Data);
            u8QAM = (u8Data >> 4) & 0x07;
            break;
        case E_ISDBT_Layer_C:
            // [6:4] reg_tmcc_cur_carrier_modulation_c
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x06*2, &u8Data);
            u8QAM = (u8Data >> 4) & 0x07;
            break;
        default:
            u8QAM = 15;
            break;
    }

    switch(u8QAM) {
        case 0:
            eQamValue = E_ISDBT_DQPSK;
            break;
        case 1:
            eQamValue = E_ISDBT_QPSK;
            break;
        case 2:
            eQamValue = E_ISDBT_16QAM;
            break;
        case 3:
            eQamValue = E_ISDBT_64QAM;
            break;
        default:
            break;
    }
    DBG_DEMOD_INFO(printf("[device_demodulator_msb1400.cpp][DTV_ISDBT_GetSignalModulation()]Modulation = %d\n", eQamValue);)

    return eQamValue;
}

EN_ISDBT_CODE_RATE DTV_ISDBT_GetSignalCodeRate(EN_ISDBT_Layer LayerIndex)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data = 0, u8CodeRate = 0;
    EN_ISDBT_CODE_RATE eCodeRate = E_ISDBT_CODERATE_INVALID;

    switch(LayerIndex) {
        case E_ISDBT_Layer_A:
            // [10:8] reg_tmcc_cur_convolution_code_rate_a
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x04*2+1, &u8Data);
            u8CodeRate = u8Data & 0x07;
            break;
        case E_ISDBT_Layer_B:
            // [10:8] reg_tmcc_cur_convolution_code_rate_b
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x05*2+1, &u8Data);
            u8CodeRate = u8Data & 0x07;
            break;
       case E_ISDBT_Layer_C:
            // [10:8] reg_tmcc_cur_convolution_code_rate_c
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x06*2+1, &u8Data);
            u8CodeRate = u8Data & 0x07;
            break;
      default:
            u8CodeRate = 15;
            break;
    }

    switch(u8CodeRate) {
        case 0:
            eCodeRate = E_ISDBT_CODERATE_1_2;
            break;
        case 1:
            eCodeRate = E_ISDBT_CODERATE_2_3;
            break;
        case 2:
            eCodeRate = E_ISDBT_CODERATE_3_4;
            break;
        case 3:
            eCodeRate = E_ISDBT_CODERATE_5_6;
            break;
        case 4:
            eCodeRate = E_ISDBT_CODERATE_7_8;
            break;
        default:
            break;
    }
    DBG_DEMOD_INFO(printf("[device_demodulator_msb1400.cpp][DTV_ISDBT_GetSignalCodeRate()]Code Rate = %d\n", eCodeRate);)

    return eCodeRate;
}

EN_ISDBT_GUARD_INTERVAL DTV_ISDBT_GetSignalGuardInterval(void)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data = 0, u8CP = 0;
    EN_ISDBT_GUARD_INTERVAL eGuardInterval = E_ISDBT_GUARD_INTERVAL_INVALID;

    // [7:6] reg_mcd_out_cp
    // output cp -> 00: 1/4
    //                    01: 1/8
    //                    10: 1/16
    //                    11: 1/32
    status &= MSB140X_ReadReg(MSB1400_TDP_REG_BASE+0x34*2, &u8Data);
    u8CP  = (u8Data >> 6) & 0x03;
    switch(u8CP) {
        case 0:
            eGuardInterval = E_ISDBT_GUARD_INTERVAL_1_4;
            break;
        case 1:
            eGuardInterval = E_ISDBT_GUARD_INTERVAL_1_8;
            break;
        case 2:
            eGuardInterval = E_ISDBT_GUARD_INTERVAL_1_16;
            break;
        case 3:
            eGuardInterval = E_ISDBT_GUARD_INTERVAL_1_32;
            break;
        default:
            break;
    }
    DBG_DEMOD_INFO(printf("[device_demodulator_msb1400.cpp][DTV_ISDBT_GetSignalGuardInterval()]Guard Interval = %d\n", eGuardInterval);)

    return eGuardInterval;
}

EN_ISDBT_TIME_INTERLEAVING DTV_ISDBT_GetSignalTimeInterleaving(EN_ISDBT_Layer LayerIndex)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data = 0, u8Mode = 0, u8Tdi = 0;
    EN_ISDBT_TIME_INTERLEAVING eTimeInterleaving = E_ISDBT_TDI_INVALID;

    // [5:4] reg_mcd_out_mode
    // output mode  -> 00: 2k
    //                         01: 4k
    //                         10: 8k
    status &= MSB140X_ReadReg(MSB1400_TDP_REG_BASE+0x34*2, &u8Data);
    u8Mode  = (u8Data >> 4) & 0x03;

    switch(LayerIndex) {
        case E_ISDBT_Layer_A:
            // [14:12] reg_tmcc_cur_interleaving_length_a
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x04*2+1, &u8Data);
            u8Tdi = (u8Data >> 4) & 0x07;
            break;
        case E_ISDBT_Layer_B:
            // [14:12] reg_tmcc_cur_interleaving_length_b
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x05*2+1, &u8Data);
            u8Tdi = (u8Data >> 4) & 0x07;
            break;
       case E_ISDBT_Layer_C:
            // [14:12] reg_tmcc_cur_interleaving_length_c
            status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x06*2+1, &u8Data);
            u8Tdi = (u8Data >> 4) & 0x07;
            break;
      default:
            u8Tdi = 15;
            break;
    }

    // u8Tdi+u8Mode*4
    // => 0~3: 2K
    // => 4~7: 4K
    // => 8~11:8K
    switch(u8Tdi+u8Mode*4) {
        case 0:
            eTimeInterleaving = E_ISDBT_2K_TDI_0;
            break;
        case 1:
            eTimeInterleaving = E_ISDBT_2K_TDI_4;
            break;
        case 2:
            eTimeInterleaving = E_ISDBT_2K_TDI_8;
            break;
        case 3:
            eTimeInterleaving = E_ISDBT_2K_TDI_16;
            break;
        case 4:
            eTimeInterleaving = E_ISDBT_4K_TDI_0;
            break;
        case 5:
            eTimeInterleaving = E_ISDBT_4K_TDI_2;
            break;
        case 6:
            eTimeInterleaving = E_ISDBT_4K_TDI_4;
            break;
        case 7:
            eTimeInterleaving = E_ISDBT_4K_TDI_8;
            break;
        case 8:
            eTimeInterleaving = E_ISDBT_8K_TDI_0;
            break;
        case 9:
            eTimeInterleaving = E_ISDBT_8K_TDI_1;
            break;
        case 10:
            eTimeInterleaving = E_ISDBT_8K_TDI_2;
            break;
        case 11:
            eTimeInterleaving = E_ISDBT_8K_TDI_4;
            break;
        default:
            break;
    }
    DBG_DEMOD_INFO(printf("[device_demodulator_msb1400.cpp][DTV_ISDBT_GetSignalTimeInterleaving()]Time InterIeaving = %d\n", eTimeInterleaving);)

    return eTimeInterleaving;
}


float DTV_GetSNR(void)
{
    MAPI_U8 status = true;
    MAPI_U8 u8Data = 0, u8FrzData = 0;
    MAPI_U32 u32RegSNR = 0;
    MAPI_U16 u16RegSnrObsNum = 0;
    float SNRAvg = 0.0;

    //set freeze
    status &= MSB140X_ReadReg(MSB1400_FDP_REG_BASE+0x7f*2, &u8FrzData);
    u8Data = u8FrzData | _BIT0;
    status &= MSB140X_WriteReg(MSB1400_FDP_REG_BASE+0x7f*2, u8Data);
    //set load
    status &= MSB140X_WriteReg(MSB1400_FDP_REG_BASE+0x7f*2+1, 0x01);

    // ==============Average SNR===============//
    // [26:0] reg_snr_accu
    status = MSB140X_ReadReg(MSB1400_FDPEXT_REG_BASE+0x2d*2+1, &u8Data);
    u32RegSNR = u8Data&0x07;
    status = MSB140X_ReadReg(MSB1400_FDPEXT_REG_BASE+0x2d*2, &u8Data);
    u32RegSNR = (u32RegSNR<<8) | u8Data;
    status = MSB140X_ReadReg(MSB1400_FDPEXT_REG_BASE+0x2c*2+1, &u8Data);
    u32RegSNR = (u32RegSNR<<8) | u8Data;
    status = MSB140X_ReadReg(MSB1400_FDPEXT_REG_BASE+0x2c*2, &u8Data);
    u32RegSNR = (u32RegSNR<<8) | u8Data;

    // [12:0] reg_snr_observe_sum_num
    status = MSB140X_ReadReg(MSB1400_FDPEXT_REG_BASE+0x2a*2+1, &u8Data);
    u16RegSnrObsNum = u8Data&0x1f;
    status = MSB140X_ReadReg(MSB1400_FDPEXT_REG_BASE+0x2a*2, &u8Data);
    u16RegSnrObsNum = (u16RegSnrObsNum<<8) | u8Data;

    //release freeze
    status &= MSB140X_WriteReg(MSB1400_FDP_REG_BASE+0x7f*2, u8FrzData);
    //set load
    status &= MSB140X_WriteReg(MSB1400_FDP_REG_BASE+0x7f*2+1, 0x01);

    if (u16RegSnrObsNum == 0)
     u16RegSnrObsNum = 1;

    SNRAvg = (float)u32RegSNR/u16RegSnrObsNum;

    if (SNRAvg == 0)                 //protect value 0
    SNRAvg=0.01;

    SNRAvg=10*(float)log10((double)SNRAvg/2);

    DBG_DEMOD_CHECK_LOCK(printf("[device_demodulator_msb1400.cpp][DTV_GetSNR] SNR = %f\n", SNRAvg);)
    return SNRAvg;

}

MAPI_U32 DTV_GetBER(void)
{
    return 0;
}

// SQI value is divided into two parts to get.
// Part 1: get ber value from demod.
// Part 2: transfer ber value to SQI value.
MAPI_U16 DTV_GetSignalQuality(void)
{
    float fber = 1.0;
    float log_ber = 1.0;
    MAPI_U8 status = true;
    EN_ISDBT_Layer LayerIndex;
    MAPI_U16 SQI = 0;

    // Tmp solution
    LayerIndex = E_ISDBT_Layer_A;

    // Part 1: get ber value from demod.
    status &= MSB140X_GetPostBER(LayerIndex, &fber);
    log_ber = (float)log10((double)fber);

    // Part 2: transfer ber value to SQI value.
    if (log_ber <= ( - 7.0))
    {
        SQI = 100;    //*quality = 100;
    }
    else if(log_ber < -6.0)
    {
         SQI = (90+((( - 6.0) - log_ber) / (( - 6.0) - ( - 7.0))*(100-90)));
    }
    else if(log_ber < -5.5)
    {
         SQI = (80+((( - 5.5) - log_ber) / (( - 5.5) - ( - 6.0))*(90-80)));
    }
    else if(log_ber < -5.0)
    {
         SQI = (70+((( - 5.0) - log_ber) / (( - 5.0) - ( - 5.5))*(80-70)));
    }
    else if(log_ber < -4.5)
    {
         SQI = (60+((( - 4.5) - log_ber) / (( -4.5) - ( - 5.0))*(70-50)));
    }
    else if(log_ber < -4.0)
    {
         SQI = (50+((( - 4.0) - log_ber) / (( - 4.0) - ( - 45))*(60-50)));
    }
    else if(log_ber < -3.5)
    {
         SQI = (40+((( - 3.5) - log_ber) / (( - 3.5) - ( - 4.0))*(50-40)));
    }
    else if(log_ber < -3.0)
    {
         SQI = (30+((( - 3.0) - log_ber) / (( - 3.0) - ( - 3.5))*(40-30)));
    }
    else if(log_ber < -2.5)
    {
         SQI = (20+((( - 2.5) - log_ber) / (( - 2.5) - ( -3.0))*(30-20)));
    }
    else if(log_ber < -2.0)
    {
         SQI = (0+((( - 2.0) - log_ber) / (( - 2.0) - ( - 2.5))*(20-0)));
    }
    else
    {
        SQI = 0;
    }
    DBG_SQI(printf("[device_demodulator_msb1400.cpp][DTV_GetSignalQuality()]LayerIndex = %d, BER = %f, log(BER) = %f, SQI = %d\n", LayerIndex, fber, log_ber, SQI);)
    return SQI;
}


// If you want to use this api, you need to connect to api getting signal level of tuner driver
float GetSignalLevelFromTuner(void)
{
    float fRFLevel=0.0f;
#if 0
    mapi_tuner *pTuner=NULL;
    float fRFLevel=0.0f;
//   Tmp solution
    pTuner = mapi_interface::Get_mapi_pcb()->GetDvbtTuner(0);

    if (pTuner!=NULL)
    {
        if ( MAPI_FALSE == pTuner->ExtendCommand(mapi_tuner::E_TUNER_SUBCMD_GET_RF_LEVEL, 0, 0, &fRFLevel))
        {
            fRFLevel=200.0f;
        }
    }
    else
    {
        fRFLevel=200.0f;
        DBG_SSI(printf("%s Line:%d Error!!\n",__func__, __LINE__);)
    }
#endif
    return fRFLevel;
}

// If you want to use this api, you need to add one talbe(IfagcSsi[]) which is depending on tuner.
float GetSignalLevelFromDemodIF(void)
{
    MAPI_U8  status = true;
    MAPI_U8  u8Data = 0, i = 0;
//   MAPI_U16 u16IfAgc, if_agc_val;
    MAPI_U8  u8IfAgc = 0, if_agc_val = 0;
    float    ch_power_if = 0.0, ch_power_dbm = 0.0;

    ////////// IF-AGC Gain Out /////////////
    //debug select
    //select agc gain2, dagc0 gain, dagc1 gain, dagc2 gain
    status &= MSB140X_WriteReg(MSB1400_FE_REG_BASE+0x13*2, 0x03);

    //set freeze & dump [Write]
    status &= MSB140X_WriteReg(MSB1400_FE_REG_BASE+0x02*2+1, 0x80);

#if 0
    // Read IF AGC
    status = MSB140X_ReadReg(MSB1400_FE_REG_BASE+0x14*2+1, &u8Data);
    u16IfAgc = u8Data;
    status = MSB140X_ReadReg(MSB1400_FE_REG_BASE+0x14*2, &u8Data);
    u16IfAgc = (u16IfAgc<<8) | u8Data;
    if_agc_val = u16IfAgc;
#endif
    // Read High Byte of IF AGC
    status = MSB140X_ReadReg(MSB1400_FE_REG_BASE+0x14*2+1, &u8Data);
    u8IfAgc = u8Data;
    if_agc_val = u8IfAgc;

    //Unfreeze & dump [Write]
    status &= MSB140X_WriteReg(MSB1400_FE_REG_BASE+0x02*2+1, 0x00);

    DBG_SSI(printf("[device_demodulator_msb1400.cpp][GetSignalLevelFromDemodIF]SSI_IFAGC = 0x%x\n", if_agc_val);)

    for(i = 0; i < sizeof(IfagcSsi)/sizeof(S_MSB_1400_IFAGC_SSI); i++)
    {
        if (if_agc_val <= IfagcSsi[i].agc_val)
        {
            ch_power_if = IfagcSsi[i].power_db;
            break;
        }
    }

    DBG_SSI(printf("[device_demodulator_msb1400.cpp][GetSignalLevelFromDemodIF]ch_power_if = %f\n", ch_power_if);)

    ch_power_dbm = ch_power_if;

    return ch_power_dbm;
}

// If you want to use this api, you need to read RF AGC from ADC and add two talbes(RfagcSsi[] /IfagcSsi[]) which are depending on tuner.
float GetSignalLevelFromDemodIFandRF(void)
{
    MAPI_U8  status = true;
    MAPI_U8  u8Data = 0, i = 0;
//   MAPI_U16 u16IfAgc, if_agc_val, rf_agc_val;
    MAPI_U8  u8IfAgc = 0, if_agc_val = 0, rf_agc_val = 0;
    float    ch_power_rf = 0.0, ch_power_if = 0.0, ch_power_dbm = 0.0;

// Tmp remove
    ////////// RF-AGC Gain Out /////////////
//    rf_agc_val = MDrv_SAR_Adc_GetValue(2);

    ////////// IF-AGC Gain Out /////////////
    //debug select
    //select agc gain2, dagc0 gain, dagc1 gain, dagc2 gain
    status &= MSB140X_WriteReg(MSB1400_FE_REG_BASE+0x13*2, 0x03);

    //set freeze & dump [Write]
    status &= MSB140X_WriteReg(MSB1400_FE_REG_BASE+0x02*2+1, 0x80);

#if 0
    // Read IF AGC
    status = MSB140X_ReadReg(MSB1400_FE_REG_BASE+0x14*2+1, &u8Data);
    u16IfAgc = u8Data;
    status = MSB140X_ReadReg(MSB1400_FE_REG_BASE+0x14*2, &u8Data);
    u16IfAgc = (u16IfAgc<<8) | u8Data;
    if_agc_val = u16IfAgc;
#endif
    // Read High Byte of IF AGC
    status = MSB140X_ReadReg(MSB1400_FE_REG_BASE+0x14*2+1, &u8Data);
    u8IfAgc = u8Data;
    if_agc_val = u8IfAgc;

    //Unfreeze & dump [Write]
    status &= MSB140X_WriteReg(MSB1400_FE_REG_BASE+0x02*2+1, 0x00);

    DBG_SSI(printf("[device_demodulator_msb1400.cpp][GetSignalLevelFromDemodIFandRF]SSI_RFAGC (SAR-3) = 0x%x\n", rf_agc_val);)
    DBG_SSI(printf("[device_demodulator_msb1400.cpp][GetSignalLevelFromDemodIFandRF]SSI_IFAGC = 0x%x\n", if_agc_val);)

    for(i = 0; i < sizeof(RfagcSsi)/sizeof(S_MSB_1400_RFAGC_SSI); i++)
    {
        if (rf_agc_val <= RfagcSsi[i].sar3_val)
        {
            ch_power_rf = RfagcSsi[i].power_db;
            break;
        }
    }

    for(i = 0; i < sizeof(IfagcSsi)/sizeof(S_MSB_1400_IFAGC_SSI); i++)
    {
        if (if_agc_val <= IfagcSsi[i].agc_val)
        {
            ch_power_if = IfagcSsi[i].power_db;
            break;
        }
    }

    DBG_SSI(printf("[device_demodulator_msb1400.cpp][GetSignalLevelFromDemodIFandRF]ch_power_rf = %f\n", ch_power_rf);)
    DBG_SSI(printf("[device_demodulator_msb1400.cpp][GetSignalLevelFromDemodIFandRF]ch_power_if = %f\n", ch_power_if);)

    ch_power_dbm = (ch_power_rf > ch_power_if)? ch_power_rf : ch_power_if;

    return ch_power_dbm;
}

// SSI value is divided into two parts to get.
// Part 1: get signal level(dBm)
// Part 2: transfer signal level to SSI values.

// There are three methods to get Signal level(dBm) :
// 1). E_ISDBT_SSIMethod1: get signal lever from Tuner directly.
// 2). E_ISDBT_SSIMethod2: get IF AGC from demod, then transfer to signal level.
// 3). E_ISDBT_SSIMethod3: get IF AGC from demod and RF AGC from ADC SAR, then transfer to signal level.

// Order of Suggestion Usage:
// Frist order: E_ISDBT_SSIMethod1.
// => Comment: High accuracy. Tuner driver needs to provide api to read signal level.
// Second order: E_ISDBT_SSIMethod3.
// => Comment: Middle accuracy. Board(ADC SAR) needs to provide RF AGC gain.
// Third order: E_ISDBT_SSIMethod2.
// => Comment: Low accuracy.
#define  SSIMethodUsed      E_ISDBT_SSIMethod2   //E_ISDBT_SSIMethod1
MAPI_U16 DTV_GetSignalStrength(void)
{
    float        ch_power_dbm = 0.0;
    MAPI_U16     u16Strength = 0;
    MAPI_U8      status = true;

    // Part 1: get signal level(dBm)
    switch(SSIMethodUsed) {
        // Method 1: get signal lever from Tuner directly.
        case E_ISDBT_SSIMethod1:
            ch_power_dbm = GetSignalLevelFromTuner();
            break;

        // Method 2: get IF AGC from demod, then transfer to signal level.
        case E_ISDBT_SSIMethod2:
            ch_power_dbm = GetSignalLevelFromDemodIF();
            break;

        // Method 3: get IF AGC from demod and RF AGC from ADC SAR, then transfer to signal level.
        case E_ISDBT_SSIMethod3:
        default:
            ch_power_dbm = GetSignalLevelFromDemodIFandRF();
            break;
    }

    // Part 2: transfer signal level to SSI values.
    if (ch_power_dbm < -90.0)
        u16Strength = 0;
    else if (ch_power_dbm < -70.0)
        u16Strength = (MAPI_U16)((ch_power_dbm + 90.0)*(50.0/20.0)+0.0);
    else if (ch_power_dbm < -60.0)
        u16Strength = (MAPI_U16)((ch_power_dbm + 70.0)*(30.0/10.0)+ 50.0);
    else if (ch_power_dbm < -50.0)
        u16Strength = (MAPI_U16)((ch_power_dbm + 60.0)*(20.0/10.0) + 80.0);
    else
        u16Strength = 100;

    DBG_SSI(printf("[device_demodulator_msb1400.cpp][DTV_GetSignalStrength()]SSIMethodUsed = %d, Channel Power = %f dBm, SSI = %d\n", SSIMethodUsed, ch_power_dbm, u16Strength));

    if (status == true)
        return u16Strength;
    else
        return 0;
}


MAPI_BOOL DTV_Serial_Control(MAPI_BOOL bEnable)
{
    bEnable = bEnable;
    return true;
}

static MAPI_BOOL MSB140X_WriteReg(MAPI_U16 u16Addr, MAPI_U8 u8Data)
{
    MAPI_BOOL bRet=TRUE;
    if (iptr == NULL) return FALSE;
    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;
    u8MsbData[5] = u8Data;

    u8MsbData[0] = 0x35;
    bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbData);
    u8MsbData[0] = 0x10;
    bRet &= iptr->WriteBytes(0, NULL, 6, u8MsbData);
    u8MsbData[0] = 0x34;
    bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

    return bRet;
}

static MAPI_BOOL MSB140X_ReadReg(MAPI_U16 u16Addr, MAPI_U8 *pu8Data)
{
    MAPI_BOOL bRet=TRUE;
    if (iptr == NULL) return FALSE;
    u8MsbData[0] = 0x10;
    u8MsbData[1] = 0x00;
    u8MsbData[2] = 0x00;
    u8MsbData[3] = (u16Addr >> 8) &0xff;
    u8MsbData[4] = u16Addr &0xff;

    u8MsbData[0] = 0x35;
    bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

    u8MsbData[0] = 0x10;
    bRet &= iptr->WriteBytes(0, NULL, 5, u8MsbData);
    bRet &= iptr->ReadBytes(0, NULL, 1, pu8Data);

    u8MsbData[0] = 0x34;
    bRet &= iptr->WriteBytes(0, NULL, 1, u8MsbData);

    return bRet;
}

static MAPI_BOOL MSB140X_WriteRegs(MS_U16 u16Addr, MS_U8* u8pData, MS_U16 data_size)
{
    MAPI_BOOL bRet=TRUE;
    MS_U16 index;
    MS_U8 Data[LOAD_CODE_I2C_BLOCK_NUM+5];
    if (iptr == NULL)
    {
        return FALSE;
    }
    Data[0] = 0x10;
    Data[1] = 0x00;
    Data[2] = 0x00;
    Data[3] = (u16Addr >> 8) &0xff;
    Data[4] = u16Addr &0xff;

    for(index = 0; index < data_size ; index++)
    {
        Data[5+index] = u8pData[index];
    }

    Data[0] = 0x35;
    bRet &= iptr->WriteBytes(0, NULL, 1, Data);
    Data[0] = 0x10;
    bRet &= iptr->WriteBytes(0, NULL, (5 + data_size), Data);
    Data[0] = 0x34;
    bRet &= iptr->WriteBytes(0, NULL, 1, Data);
    return bRet;
}

MAPI_BOOL I2C_Channel_Change(MS_U8 ch_num)
{
    MAPI_BOOL bRet=TRUE;
    MS_U8 Data[5] = {0x53, 0x45, 0x52, 0x44, 0x42};
    if (iptr == NULL)
    {
        return FALSE;
    }
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][I2C_Channel_Change()]Enter!! Channel Num = %d\n", ch_num));
    Data[0] = (ch_num & 0x01)? 0x81 : 0x80;
    bRet&= iptr->WriteBytes(0, NULL, 1, Data);
    Data[0] = (ch_num & 0x02)? 0x83 : 0x82;
    bRet&= iptr->WriteBytes(0, NULL, 1, Data);
    Data[0] = (ch_num & 0x04)? 0x85 : 0x84;
    bRet&= iptr->WriteBytes(0, NULL, 1, Data);
    return bRet;
}

MAPI_BOOL LoadDSPCode(void)
{
    MS_BOOL bRet=TRUE;
    MS_U16 index;
    MS_U16 SRAM_Address;
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][LoadDSPCode()]Enter!!\n"));

    bRet&=I2C_Channel_Change(3);
    // MCU Reset
    bRet&=MSB140X_WriteReg(MSB1400_REG_MCU_RST, 0x03);

    bRet&=I2C_Channel_Change(0);
    bRet&=MSB140X_WriteReg(0x3008, 0x00);
    bRet&=MSB140X_WriteReg(0x3009, 0x00);
    bRet&=MSB140X_WriteReg(0x300A, 0x00);
    bRet&=MSB140X_WriteReg(0x300B, 0x00);

    bRet&=I2C_Channel_Change(3);
    bRet&=MSB140X_WriteReg(0x10E1, 0x20);
    bRet&=MSB140X_WriteReg(0x10E0, 0x3F);
    bRet&=MSB140X_WriteReg(0x10E6, 0x08);

    bRet&=I2C_Channel_Change(0);
    // Load Code to Sram
    for (index = 0; index < u16Lib_size; )
    {
        SRAM_Address = SRAM_BASE + index;
        if (index+LOAD_CODE_I2C_BLOCK_NUM-1<u16Lib_size)
        {
            bRet&= MSB140X_WriteRegs(SRAM_Address,MSB140X_LIB+index,LOAD_CODE_I2C_BLOCK_NUM);
            index=index+LOAD_CODE_I2C_BLOCK_NUM-1;
        }
        else
        {
            bRet&=MSB140X_WriteRegs(SRAM_Address,MSB140X_LIB+index,u16Lib_size-index);
            index=u16Lib_size;
        }
    }
    bRet&=I2C_Channel_Change(3);

    // MCU Reset
    bRet&=MSB140X_WriteReg(0x10E6, 0x00);
    bRet&=MSB140X_WriteReg(0x1004, 0x00);
    bRet&=MSB140X_WriteReg(0x1005, 0x00);
    bRet&=MSB140X_WriteReg(0x1000, 0x00);
    bRet&=MSB140X_WriteReg(0x1006, 0x7F);
    bRet&=MSB140X_WriteReg(0x1007, 0xFF);
    bRet&=MSB140X_WriteReg(0x1002, 0x00);
    bRet&=MSB140X_WriteReg(0x1018, 0x01);

    bRet&=MSB140X_WriteReg(MSB1400_REG_MCU_RST, 0x00);

    return bRet;
}

MAPI_BOOL DTV_Config(RF_CHANNEL_BANDWIDTH BW, MAPI_BOOL bSerialTS, MAPI_BOOL bPalBG)
{
    MAPI_U8 status = true;
    BW = BW;
    bSerialTS = bSerialTS;
    bPalBG = bPalBG;
    DBG_DOMOD_MSB(printf("=======================>[device_demodulator_msb1400.cpp][DTV_Config()] Enter!!\n"));

    return status;
}

BOOLEAN MSB1400_WriteReg(U16 RegAddr, U8 u8Data)
{
    return MSB140X_WriteReg(RegAddr, u8Data);
}
BOOLEAN MSB1400_ReadReg(U16 RegAddr, U8* pu8Data)
{
    return MSB140X_ReadReg(RegAddr, pu8Data);
}
BOOLEAN MSB1400_Power_On_Initialization(void)
{
    printf("\e[31;1m >> %s \33[m \n", __FUNCTION__);

    if (iptr == NULL)
    {
        msb1400_func.ReadBytes  =  I2c_readbytes;
        msb1400_func.WriteBytes =  I2c_writebytes;
        iptr = &msb1400_func;
    }

    return Power_On_Initialization();
}

BOOLEAN MSB1400_Lock(COFDM_LOCK_STATUS eStatus)
{
    return DTV_ISDB_GetLockStatus(eStatus);
}
BOOLEAN MSB1400_Config(RF_CHANNEL_BANDWIDTH BW, BOOLEAN bSerialTS, BOOLEAN bPalBG, BOOLEAN bLPSel)
{
    bSerialTS = bSerialTS;
    return DTV_SetFrequency(0, BW, bPalBG, bLPSel);
}

BOOLEAN MSB1400_Active(BOOLEAN bEnable)
{
    return Active(bEnable);
}

BOOLEAN MSB1400_Serial_Control(BOOLEAN bEnable)
{
    return DTV_Serial_Control(bEnable);
}

float MSB1400_GetSNR(void)
{
    return DTV_GetSNR();
}

void MDrv_1400_IIC_Bypass_Mode(BOOLEAN enable)
{
    IIC_Bypass_Mode(enable);
    return;
}

FUNCTION_RESULT MSB1400_GetSignalStrength(WORD *strength)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;
    *strength = DTV_GetSignalStrength();
    if ( *strength > 100 )
        ret = E_RESULT_FAILURE;
    return ret;
}
FUNCTION_RESULT MSB1400_GetSignalQuality(WORD *quality)
{
    FUNCTION_RESULT ret = E_RESULT_SUCCESS;
    *quality = DTV_GetSignalQuality();
    if ( *quality > 100 )
        ret = E_RESULT_FAILURE;
    return ret;
}

