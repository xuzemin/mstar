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

#define _MSR1200_C

// System

// Common
#include <stdio.h>

#include "Board.h"
#include "datatype.h"
#include "Drviic.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "COFDM_Demodulator.h"
//#include "Tuner.h"
#include "msAPI_Tuning.h"


#define MSR1200_DEBUG       0
//#define USE_NRESET


#define TV_TYPE_DTV    0
#define TV_TYPE_ATV    1


#if (FRONTEND_DEMOD_TYPE == ZARLINK_ZL10353_DEMODE)
#define MSR1200_IIC_WriteBytes(slave, addr_count, addr_buf, data_count, data_buf) \
            MDrv_IIC_WriteBytes(slave, addr_count, addr_buf, data_count, data_buf)

#define MSR1200_IIC_ReadBytes(slave, addr_count, addr_buf, data_count, data_buf) \
            MDrv_IIC_ReadBytes(slave, addr_count, addr_buf, data_count, data_buf)
#elif (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD)
#define MSR1200_IIC_WriteBytes(slave, addr_count, addr_buf, data_count, data_buf) \
            devCOFDM_PassThroughI2C_WriteBytes(slave, addr_count, addr_buf, data_count, data_buf)

#define MSR1200_IIC_ReadBytes(slave, addr_count, addr_buf, data_count, data_buf) \
            devCOFDM_PassThroughI2C_ReadBytes(slave, addr_count, addr_buf, data_count, data_buf)

#endif

static FREQSTEP m_eFrequencyStep;
#ifndef USE_NRESET
static U8 gu8CurTvType;
#endif

BOOLEAN MSR1200_WriteByte(U8 addr, U8 u8Data)
{
    return MSR1200_IIC_WriteBytes(_TUNER_I2C_ID, 1, &addr, 1, &u8Data);
}

U8 MSR1200_ReadByte(U8 addr)
{
    U8 u8Ret;
    MSR1200_IIC_ReadBytes(_TUNER_I2C_ID, 1, &addr, 1, &u8Ret);
    return u8Ret;
}

U8 MSR1200_ATV_TBL[106]=
{
0x00,0x01,0x27,0x1D,0xC8,0x77,0x72,0x7E,0x20,0x09,0xE4,0xBF,0x7F,0xD9,0x98,0x04, //15
0x7B,0x02,0xFF,0x17,0xFF,0xFF,0xFF,0x03,0xFF,0x7F,0x01,0x22,0x6F,0x34,0x20,0x2F, //31
0x4C,0x1F,0x2D,0x3F,0x00,0x33,0x93,0x09,0x8D,0x0E,0x0B,0x6A,0x35,0x87,0x00,0x00, //47
0x00,0x00,0xE3,0x09,0x23,0x13,0x0B,0x8C,0x00,0x10,0x10,0x00,0x06,0x04,0x02,0x00, //63
0x50,0x00,0x4E,0x09,0x01,0x00,0x08,0x47,0x13,0x0B,0x80,0x00,0x0C,0x13,0x00,0x18, //79
0x18,0x02,0x08,0x00,0x00,0x14,0x01,0x17,0x06,0x7D,0x07,0x00,0x10,0x27,0x1C,0x23, //95
0x03,0xAA,0x02,0x0A,0x01,0x67,0x00,0x00,0x2A,0x00,
};

U8 MSR1200_DTV_TBL[106]=
{
0x00,0x01,0x23,0x5D,0xC8,0x77,0x72,0x7D,0x20,0x09,0xC4,0xC8,0xDC,0x2B,0x88,0x02, //15
0x54,0x01,0xFF,0x7B,0xFF,0xFF,0xFF,0x03,0xFF,0x7F,0x00,0x22,0x6F,0x34,0x10,0x2F, //31
0x74,0x1F,0x2D,0x3F,0x02,0x82,0xBE,0x7A,0xCD,0x0D,0x0B,0x69,0x30,0x87,0x00,0x00, //47
0x00,0x00,0xE3,0x09,0x23,0x13,0x0B,0x8C,0x00,0x10,0x10,0x00,0x06,0x04,0x02,0x00, //63
0x70,0x00,0x4E,0x09,0x01,0x00,0x08,0x47,0x13,0x0B,0x80,0x00,0x0C,0x13,0x00,0x18, //79
0x18,0x02,0x40,0x04,0x00,0x14,0x13,0x16,0x06,0x0D,0x00,0x00,0x3C,0x27,0x1C,0x23, //95
0x03,0xAA,0x02,0x0A,0x00,0x67,0x0D,0x00,0x16,0x00,
};

void MSR1200_Init(U8 tvType)
{
    U8 addr;
    U8 *pTVTbl;

#ifndef USE_NRESET
    gu8CurTvType = tvType;
#endif

    addr = 0x00;

    if (tvType == TV_TYPE_ATV)
    {
        pTVTbl = MSR1200_ATV_TBL;
    }
    else
    {
        pTVTbl = MSR1200_DTV_TBL;
    }

    if (MSR1200_IIC_WriteBytes(_TUNER_I2C_ID, 1, &addr, 106, pTVTbl) == FALSE)
    {
#if MSR1200_DEBUG
        printf(" Fail init MSR1200\n");
#endif
    }

#if 0
    {

        U8 TempArray[106];

        if (MSR1200_IIC_ReadBytes(_TUNER_I2C_ID, 1, &addr, 106, TempArray) == FALSE)
        {
            printf(" Fail init MSR1200\n");
        }

        for ( addr = 0 ; addr < 106 ; addr++)
        {
            if (TempArray[addr] != MSR1200_DTV_TBL[addr])
            {
                printf("Reg[%d] = %x\n", (int)addr, (int)TempArray[addr]);
            }
        }
    }
#endif
}

void MSR1200_VCOs_Calibration(void)
{
    U8 u8Reg61, u8Reg77;

    u8Reg61  = MSR1200_ReadByte(61); //VCO1_Cal
    u8Reg77  = MSR1200_ReadByte(77); //VCO3_Cal

    MSR1200_WriteByte(61, u8Reg61|0x04);
    MSR1200_WriteByte(77, u8Reg77|0x02);

    MSR1200_WriteByte(61, u8Reg61&0xFB);
    MSR1200_WriteByte(77, u8Reg77&0xFD);

    MSR1200_WriteByte(61, u8Reg61|0x04);
    MSR1200_WriteByte(77, u8Reg77|0x02);

    //VCO2_Cal
    MSR1200_WriteByte(100, MSR1200_ReadByte(100)&0xFE); //clr bit0
    MSR1200_WriteByte(99, MSR1200_ReadByte(99)|0x01);   //set bit0
}

typedef struct
{
    U8 Reg5;
    U8 Reg6;
} MSR_REG56;

code MSR_REG56 tblRegister[] =
{
    {0x00, 0x02},
    {0x54, 0x52},
    {0x77, 0x72},
    {0x99, 0x92},
    {0xcc, 0xc2},
    {0xee, 0xe2},
    {0xcc, 0xc2},
    {0x99, 0x92},
    {0x77, 0x72},
    {0x54, 0x52},
    {0x00, 0x02},
};

typedef struct
{
    U8 Address;
    U8 Value;
} MSR_REG;

code MSR_REG tblNFReg[]=
{
    {30, 0x20}, //Address, Value
    {35, 0x30},
    {36, 0x02},
    {37, 0x82},
    {38, 0xBE},
    {39, 0x7A},
    {40, 0xCD},
    {43, 0x69},
    {44, 0x30},
    {87, 0x13},
};

code MSR_REG tblNoNFReg[]=
{
    {30, 0x10}, //Address, Value
    {35, 0x27},
    {36, 0x01},
    {37, 0xB3},
    {38, 0xD3},
    {39, 0x39},
    {40, 0x8D},
    {43, 0x6A},
    {44, 0x35},
    {87, 0x17},
};


BOOLEAN MSR1200_Set_Freq(U32 freq, U8 tvType)
{
#define R_reg     (MSR1200_ReadByte(15) & 0x1F)
#define XTAL_freq 16

    U8 reset_count;
    U16 step_num;
    U8 dataTune[3];
    U16 lo2,fStep;
    float lo3,if1,if3;
    U32 lo3_frac;
    WORD wTunerIF;
    U8 i;
    U8 u8Reg31;

#ifdef USE_NRESET
    MSR1200_WriteByte(2, 0); // Nreset
    MSR1200_WriteByte(2, 1);
#endif

#if 1 //20080410, LNA+VGA1 gain calibration
    u8Reg31 = MSR1200_ReadByte(31);
    MSR1200_WriteByte(31, u8Reg31 & 0xDF);
    MSR1200_WriteByte(31, u8Reg31 | 0x20);
#endif

    //freq = 55250;

    if (tvType == TV_TYPE_ATV)
    {
        wTunerIF = msAPI_Tuner_GetIF();

    #if TN_FREQ_STEP == FREQ_STEP_62_5KHz
        wTunerIF *= 62.5;
    #elif TN_FREQ_STEP == FREQ_STEP_50KHz
        wTunerIF *= 50;
    #else
        wTunerIF *= 31.25;
    #endif // TN_FREQ_STEP

        if(wTunerIF <= 33950)
            if3 = 33.95;
        else
            if3 = 38.9;
        //freq -= 1750;
    }
    else
    {
        if3 = 36.17;
    }

#ifdef USE_NRESET
    MSR1200_Init(tvType);

    MSR1200_VCOs_Calibration();
#else
    if(gu8CurTvType != tvType)
    {
        MSR1200_Init(tvType);
    }
#endif

    reset_count = 0;

    do
    {

        if(freq < 450000) // low band
        {
            MSR1200_WriteByte( 2, 0x27);
            MSR1200_WriteByte( 3, 0x1D);
            MSR1200_WriteByte( 7, 0x7E);
            MSR1200_WriteByte(12, 0xBF);

        }
        else // high band
        {
            MSR1200_WriteByte( 2, 0x23);
            MSR1200_WriteByte( 3, 0x5D);
            MSR1200_WriteByte( 7, 0x7D);
            MSR1200_WriteByte(12, 0xBC);
        }

        if (freq < 110000)
        {
            step_num = 0;
        }
        else if (freq < 190000)
        {
            step_num = 1;
        }
        else if (freq < 290000)
        {
            step_num = 2;
        }
        else if (freq < 360000)
        {
            step_num = 3;
        }
        else if (freq < 420000)
        {
            step_num = 4;
        }
        else if (freq < 490000)
        {
            step_num = 5;
        }
        else if (freq < 540000)
        {
            step_num = 6;
        }
        else if (freq < 610000)
        {
            step_num = 7;
        }
        else if (freq < 700000)
        {
            step_num = 8;
        }
        else if (freq < 780000)
        {
            step_num = 9;
        }
        else
        {
            step_num = 10;
        }

        MSR1200_WriteByte( 5, tblRegister[step_num].Reg5);
        MSR1200_WriteByte( 6, tblRegister[step_num].Reg6);

        fStep = XTAL_freq/R_reg;

        if ( freq < 450000)
        {
            // Calc LO2
            if1   = 908 + (float)freq/1000;

            lo2 = (U16)((1575 + if1)/fStep)*fStep-fStep;

            // lo3 = lo2 - if1 - IF3
            lo3 = ((float)lo2 - if1 - if3);

        }
        else
        {
            // Calc LO2
            //fStep = XTAL_freq/R_reg;
            if1   = 1816 - (float)freq/1000;

            lo2 = (U16)((1575 + if1)/fStep)*fStep;

            // lo3 = lo2 - if1 + IF3
            lo3 = ((float)lo2 - if1 + if3);

        }
    #if MSR1200_DEBUG
        printf("lo2 = %d\n", (int)lo2);
    #endif
    #if MSR1200_DEBUG
        printf("lo3 = %f\n", lo3);
    #endif
        lo3 /= (XTAL_freq/2);
        lo2 /= fStep;


        dataTune[1] = (U8)(lo2 >> 8);
        dataTune[0] = (U8)(lo2 & 0xff);

        MSR1200_WriteByte( 16, dataTune[0]);
        MSR1200_WriteByte( 17, dataTune[1]);


        dataTune[0] = (U8) lo3;
        MSR1200_WriteByte( 11, dataTune[0]);

        //printf("lo3_int = %x\n", (int)dataTune[0]);

        lo3 = lo3 - (float)dataTune[0];

        lo3_frac = (U32)(lo3 * 524288);

        dataTune[0] = (U8)((lo3_frac >> 11)& 0xE0) | (MSR1200_ReadByte(12) & 0x1F);
        dataTune[1] = (U8)(lo3_frac >> 8);
        dataTune[2] = (U8)(lo3_frac);

        //printf("lo3_frac = %lx\n", lo3_frac);
        //printf("lo3 = %x, %x, %x\n", (int)dataTune[0], (int)dataTune[1], (int)dataTune[2]);
        MSR1200_WriteByte( 12, dataTune[0]);
        MSR1200_WriteByte( 13, dataTune[1]);
        MSR1200_WriteByte( 14, dataTune[2]);

        if(tvType == TV_TYPE_DTV)
        {
            //Only 810, 850 and 858MHz will apply Noise Figure Optimum
            if((freq == 810000) || (freq == 850000) || (freq == 858000))
            {
                //printf("NF_opt\n");
                for(i=0; i<sizeof(tblNFReg)/sizeof(MSR_REG); i++)
                    MSR1200_WriteByte(tblNFReg[i].Address, tblNFReg[i].Value);
            }
            else
            {
                //printf("No NF_opt\n");
                for(i=0; i<sizeof(tblNoNFReg)/sizeof(MSR_REG); i++)
                    MSR1200_WriteByte(tblNoNFReg[i].Address, tblNoNFReg[i].Value);
            }
        }

    #ifndef USE_NRESET
        MSR1200_VCOs_Calibration();
    #endif

        MsOS_DelayTask(40);// tuner response time

        //Check PLL1/3 lock
        if((MSR1200_ReadByte(64)&0x0C) || (MSR1200_ReadByte(82)&0x30))
        {
        #if MSR1200_DEBUG
            printf("MSR1200 PLL1/PLL3 unlock: PLL1[2:3]=0x%bX, PLL3[4:5]=0x%bX\n", MSR1200_ReadByte(64), MSR1200_ReadByte(82));
        #endif

            //1. NReset
            MSR1200_WriteByte(2, 0);
            MSR1200_WriteByte(2, 1);

            //2. Write 106 bytes
            MSR1200_Init(TV_TYPE_DTV);
        }
        else if((MSR1200_ReadByte(104)&0x80) || (MSR1200_ReadByte(105)&0x01))
        {
        #if MSR1200_DEBUG
            printf("MSR1200 PLL2 unlock\n");
        #endif

            //1.Turn on VCO turbo mode
            //MSR1200_WriteByte(101, MSR1200_ReadByte(101)|0x60); //set bit6,7

            //2.VCO2_Cal
            MSR1200_WriteByte(100, MSR1200_ReadByte(100)&0xFE); //clr bit0
            MSR1200_WriteByte(99, MSR1200_ReadByte(99)|0x01);   //set bit0

            break;
        }
        else
        {
            //printf("PLL1/2/3 lock (%bX, %bX, %bX, %bX)\n", MSR1200_ReadByte(64), MSR1200_ReadByte(82), MSR1200_ReadByte(104), MSR1200_ReadByte(105));
            break;
        }
    }while(++reset_count <= 2);

#if MSR1200_DEBUG
    dataTune[0] = (MSR1200_ReadByte(64)>>2)&3;
    dataTune[1] = ((MSR1200_ReadByte(104)>>6)&2) + (MSR1200_ReadByte(105)&1);
    dataTune[2] = (MSR1200_ReadByte(82)>>4)&3;

    for ( step_num = 0 ; step_num < 3 ; step_num++)
    {
        printf("PLL%d:", (int)step_num+1);
        if (dataTune[step_num] == 0)
        {
            printf("Lock\n");
        }
        else
        {
            printf("Unlock\n");
        }
    }
#endif

    return TRUE;
}

BOOLEAN MSR1200_Set_Bandwidth(RF_CHANNEL_BANDWIDTH eBandWidth)
{
    if(eBandWidth == E_RF_CH_BAND_8MHz)
        MSR1200_WriteByte(39, MSR1200_ReadByte(39)|0x08);
    else
        MSR1200_WriteByte(39, MSR1200_ReadByte(39)&(~0x08));

    return TRUE;
}

DWORD ConvertPLLtoIntegerOfFrequency(WORD wPLL)
{
    DWORD u32IntegerOfFreq;

#if TN_FREQ_STEP == FREQ_STEP_62_5KHz
    u32IntegerOfFreq = ( ( (DWORD)wPLL*625/10 ));
#elif TN_FREQ_STEP == FREQ_STEP_50KHz
    u32IntegerOfFreq = ( ( (DWORD)wPLL*50 ) );
#else
    u32IntegerOfFreq = ( ( (DWORD)wPLL*3125/100 ));
#endif // TN_FREQ_STEP

    return u32IntegerOfFreq;
}

void devTunerSetFreqStep(FREQSTEP eFreqStep)
{
    switch(eFreqStep)
    {
    case FREQSTEP_31_25KHz:
    case FREQSTEP_62_5KHz:
    case FREQSTEP_50KHz:
        m_eFrequencyStep = eFreqStep;
        break;

    default:
        m_eFrequencyStep = FREQSTEP_31_25KHz;
        break;
    }
}



void devTunerSetPLLData(WORD wPLLData, RFBAND eBand)
{
    U32 u32Freq;

#if MSR1200_DEBUG
    {
        extern WORD msAPI_CFT_ConvertPLLtoIntegerOfFrequency(WORD wPLL);
        extern WORD msAPI_CFT_ConvertPLLtoFractionOfFrequency(WORD wPLL);

        printf("<%03u.%03u>\n",
                  msAPI_CFT_ConvertPLLtoIntegerOfFrequency(wPLLData-msAPI_Tuner_GetIF()),
                  msAPI_CFT_ConvertPLLtoFractionOfFrequency(wPLLData-msAPI_Tuner_GetIF()));
    }
#endif

    u32Freq = ConvertPLLtoIntegerOfFrequency(wPLLData-msAPI_Tuner_GetIF());
    devCOFDM_PassThroughI2C(TRUE);
    MSR1200_Set_Freq(u32Freq, TV_TYPE_ATV);
    devCOFDM_PassThroughI2C(FALSE);
    eBand = eBand;
}


void devTunerInit(void)
{
    devCOFDM_PassThroughI2C(TRUE);
    MSR1200_Init(TV_TYPE_ATV);
    devCOFDM_PassThroughI2C(FALSE);
}


/*************************************************************************
  Subject:    MSR1200 tuner initialized function
  Function:   MDrv_Tuner_Init
  Parmeter:   CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/

void devDigitalTuner_Init()
{
    devCOFDM_PassThroughI2C(TRUE);
    MSR1200_Init(TV_TYPE_DTV);
    devCOFDM_PassThroughI2C(FALSE);
}

/*************************************************************************
  Subject:    FQD1216 tuner paremeter write
  Function:   Set_Digital_TUNER
  Parmeter:   Freq: "RF+IF" in MHz
                 eBandWidth: 6MHZ, 7MHZ, 8MHZ
                 CONFIG: pointer to tuner address
  Return :    NONE
  Remark:
**************************************************************************/
void devDigitalTuner_SetFreq ( double Freq, RF_CHANNEL_BANDWIDTH eBandWidth)
{
    //eBandWidth = eBandWidth;
#if MSR1200_DEBUG
    printf("<%d.000>\n", (int)Freq);
#endif
    devCOFDM_PassThroughI2C(TRUE);
    MSR1200_Set_Freq((U32)(Freq*1000), TV_TYPE_DTV);
    MSR1200_Set_Bandwidth(eBandWidth);
    devCOFDM_PassThroughI2C(FALSE);
}

#undef _MSR1200_C

