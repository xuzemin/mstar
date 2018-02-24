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
//-----------------------------------------------------
//  
// Filename: R828.c   
//
// This file is R828D tuner driver
// Copyright 2011 by Rafaelmicro., Inc.
//
//-----------------------------------------------------


//#include "stdafx.h"
#include "datatype.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "debug.h"
#include "Utl.h"
#include "MApp_GlobalSettingSt_Common.h"
#include "R840/R840.c"
// #include "R_R840.h"
//#include "..\I2C_Sys.h"

#define DBG_TUNER(x)  //x



// extern EN_ANT_TYPE msAPI_ATV_GetCurrentAntenna(void);

//-----------------------------------------------------------------------------
// #define R828_DEFAULT_FREQ 384000
//static RT810_IF_Type m_u16AtvIF_KHz;
//static RT810_BW_Type m_enAtvBW;
// static R840_Standard_Type m_enStandard;
// R840_Set_Info m_R840_INFO;
// static WORD m_wPLLData;
// extern MS_U16 msAPI_Tuner_GetIF(void);

#define ENABLE_TUNER_INIT_THREAD 0
#define DTMB_SYSTEM_ENABLE       1
static MS_U8 bInit_Rafael = 0;
static UINT32 FREQ_RSSI = 0;

static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

extern IF_FREQ MDrv_IFDM_GetIF(void);

#define R840_ADDRESSADDR (((UINT16)TUNER_IIC_BUS<<8)|0x74 )

// ------------------------------------------------------------
// Other Define
// ------------------------------------------------------------
#if 0
#define DIVIDER_RATIO_50KHz         0x05
#define DIVIDER_RATIO_31_25KHz      0x04
#define DIVIDER_RATIO_62_5KHz       0x03
#define DIVIDER_RATIO_125KHz        0x02
#define DIVIDER_RATIO_142_85KHz     0x01
#define DIVIDER_RATIO_166_7KHz      0x00

#define TN_FREQ_STEP                E_FREQ_STEP_62_5KHz
#define DIVIDER_RATIO               DIVIDER_RATIO_50KHz
#define TUNER_IF_FREQ_KHz           38900L
#define TUNER_L_PRIME_IF_FREQ_KHz   33900L

#define _TUNER_I2C_ID               0xC2
#define DIGITAL_TUNER_IF            (36.0)
#define MIN_FREQ_SUPPORT_KHz        40000
#define MAX_FREQ_SUPPORT_KHz        880000

#define TUNER_DTV_IQ_SWAP           1// iq swap
#define TUNER_VHF_LOWMIN_FREQ       46250L
#define TUNER_VHF_LOWMAX_FREQ       142000L
#define TUNER_VHF_HIGHMIN_FREQ      149000L
#define TUNER_VHF_HIGHMAX_FREQ      426000L
#define TUNER_UHF_MIN_FREQ_UK       470000L
#define TUNER_UHF_MIN_FREQ          434000L
#define TUNER_UHF_MAX_FREQ          863250L

#define DIVIDER_166K                0
#define DIVIDER_142K                1
#define DIVIDER_80K                 2
#define DIVIDER_62K                 3
#define DIVIDER_31K                 4
#define DIVIDER_50K                 5

#define TN_FREQ_SS_INVERSE_625      16      // 1/0.0625
#define TN_RSA_RSB_625              0x06
#define TN_RSA_RSB_50               0x05
#define TN_FREQ_SS_625              62.5    // kHz
#define TN_FREQ_SS_50               50      // kHz
#define TN_FREQ_SS_INVERSE_50       20      // 1/0.05
#define TN_FREQ_SS                  TN_FREQ_SS_625

#define TN_LOW_BAND                 0x01
#define TN_MID_BAND                 0x02
#define TN_HIGH_BAND                0x04

#define IF_OUT_LEVEL_114            0
#define IF_OUT_LEVEL_112            (1<<3)
#define IF_OUT_LEVEL_110            (2<<3)
#define IF_OUT_LEVEL_108            (3<<3)
#define IF_OUT_LEVEL_106            (4<<3)
#define IF_OUT_LEVEL_104            (5<<3)
#define IF_OUT_LEVEL_105            (6<<3)
#define IF_OUT_LEVEL_Disable        (7<<3)


#define DIGITAL_IF_AGC_ON           0x00
#define DIGITAL_IF_AGC_OFF          0x08

#define CHARGE_PUMP_1               (1<<6)
#define CHARGE_PUMP_2               (2<<6)

#define CHARGE_PUMP_3               (1<<1)

#define ANALOG_IF_OUT               0x04
#define DIGITAL_IF_OUT              0x00

#define FAST_LOCK                   0x20

#define BAND_SWITCH_UHF             0x04
#define BAND_SWITCH_VHF_HIGH        0x02
#define BAND_SWITCH_VHF_LOW         0x01

#define TUNER_HIBYTE(w)             ((MAPI_U8) (((MAPI_U16) (w) >> 8) & 0xFF))
#define TUNER_LOBYTE(w)             ((MAPI_U8) (w & 0xFF))
#endif





// VideoIF = 7.25M
const U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
 0x03A4,0x063C,0x0421,
 0x03AB,0x063C,0x0419,
 0x011B,0x063C,0x0200,0x06D3,0x0200,
 0x03A4,0x063C,0x0200,0x0421,0x0200
};

// VideoIF = 7.25M
const U16 VIF_A1_A2_SOS11_SOS12_B_Mono_NICAM[16]=
{
 0x03A3,0x063C,0x0421,
 0x03AF,0x063C,0x0415,
 0x011B,0x063C,0x0200,0x06D3,0x0200,
 0x03A4,0x063C,0x0200,0x0421,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
 0x038F,0x063C,0x0436,
 0x039A,0x063C,0x042B,
 0x004D,0x063C,0x0200,0x07AE,0x0200,
 0x038F,0x063C,0x0200,0x0436,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_GH_Mono_NICAM[16]=
{
 0x038F,0x063C,0x0436,
 0x039E,0x063C,0x0427,
 0x004D,0x063C,0x0200,0x07AE,0x0200,
 0x038F,0x063C,0x0200,0x0436,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
 0x03B3,0x063C,0x0411,
 0x03AC,0x063C,0x0418,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
 0x03B3,0x063C,0x0411,
 0x03B3,0x063C,0x040B,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
 0x03B3,0x063C,0x0411,
 0x039A,0x063C,0x042B,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_DK_Mono_NICAM[16]=
{
 0x03B3,0x063C,0x0411,
 0x039E,0x063C,0x0427,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
 0x03A4,0x063C,0x0421,
 0x03B4,0x063C,0x0410,
 0x0092,0x063C,0x0200,0x0764,0x0200,
 0x03A4,0x063C,0x0200,0x0421,0x0200
};

// VideoIF = 6.75M
const U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
 0x038F,0x063C,0x0436,
 0x0399,0x063C,0x042C,
 0x015D,0x063C,0x0200,0x068D,0x0200,
 0x038F,0x063C,0x0200,0x0436,0x0200
};

// VideoIF = 7.75M
const U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
 0x03B3,0x063C,0x0411,
 0x039E,0x063C,0x0427,
 0x00D7,0x063C,0x0200,0x071B,0x0200,
 0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 2.25M
const U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
 0x011B,0x063C,0x06D3,
 0x0170,0x063C,0x0678,
 0x03BD,0x063C,0x0200,0x0406,0x0200,
 0x011B,0x063C,0x0200,0x06D3,0x0200
};

int R828_Convert(int InvertNum)
{
    int ReturnNum = 0;
    int AddNum    = 0x80;
    int BitNum    = 0x01;
    int CuntNum   = 0;

    for(CuntNum = 0;CuntNum < 8;CuntNum ++)
    {
        if(BitNum & InvertNum)
        	ReturnNum += AddNum;

        AddNum /= 2;
        BitNum *= 2;
    }

    return ReturnNum;
}

MS_BOOL I2C_Write_Len(I2C_LEN_TYPE *I2C_Info)
{
//	MDrv_IIC_WriteBytes(R828_ADDRESS, 1, &I2C_Info->RegAddr, I2C_Info->Len, I2C_Info->Data);
    if(MDrv_IIC_WriteBytes(R840_ADDRESSADDR, 1, &I2C_Info->RegAddr, I2C_Info->Len, I2C_Info->Data)==FALSE)
    {
        printf("\r\n-----I2C_Write_Len error------");
        return FALSE;
    }
    return TRUE;
}



MS_BOOL I2C_Read_Len(I2C_LEN_TYPE *I2C_Info)
{
    int DataCunt = 0;

    MDrv_IIC_ReadBytes(R840_ADDRESSADDR, 0, NULL, I2C_Info->Len, &I2C_Info->Data[0]);

    for(DataCunt = 0;DataCunt < I2C_Info->Len;DataCunt ++)
    {
        I2C_Info->Data[DataCunt] = R828_Convert(I2C_Info->Data[DataCunt]);
    }

    return true;
}


MS_BOOL I2C_Write(I2C_TYPE *I2C_Info)
{
       //printf("\r\nADDR %d = %x", I2C_Info->RegAddr,I2C_Info->Data);
    if(MDrv_IIC_WriteByte(R840_ADDRESSADDR, I2C_Info->RegAddr, I2C_Info->Data)==FALSE)
        printf("\r\n-----IIC error------");
    return TRUE;
}

bool device_tuner_R840_init(void)
{
    if (bInit_Rafael == 1) return true;

    DBG_TUNER(printf("[The Tuner is R840 TUNER!!!!!!!!!!!!!!!]\n");)
    if(R840_Init() == false)
        printf("R840_Init error \n");
    else
        bInit_Rafael = 1;

    // R840_Delay_MS(10 * 100);
    return (bInit_Rafael==1)?true:false;
}



bool ATV_SetTune( U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,U8 u8OtherMode )
{
    R840_Set_Info stR840_Info;
    R840_Standard_Type StandardMode;

    UNUSED(eBand);
    #if ENABLE_TUNER_INIT_THREAD
        if(bInitializing)
            return MAPI_FALSE;
    #endif

    if(!bInit_Rafael) //double check lock
    {
        #if ENABLE_TUNER_INIT_THREAD
            mapi_scope_lock(scopeLock, &m_mutexTunerInit);
        #endif
        if(!bInit_Rafael)
        {
            if (R840_Init() == RT_Success)
            {
                bInit_Rafael = 1;
            }
        }
    }

    //printf("ATV_SetTune, freq=%ld, a=0x%x,b=0x%x\n",u32FreqKHz,(U8)eMode,u8OtherMode);

    if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
        StandardMode = R840_SECAM_L1_CIF_5M;
    }
    else if(eMode == E_TUNER_ATV_NTSC_MODE)
    {
    #if DTMB_SYSTEM_ENABLE
        StandardMode = R840_MN_CIF_5M; 
    #else
        StandardMode = R840_MN_CIF_5M;
    #endif
    }
    else
    {
        //printf("OtherMode[%d]\r\n",u8OtherMode);
        if(u8OtherMode == 0xff)
        {
        #if DTMB_SYSTEM_ENABLE
            StandardMode = R840_PAL_DK_CIF_5M;  
        #else
            StandardMode = R840_PAL_DK_CIF_5M;
        #endif
        }
        else
        {
            switch((AUDIOSTANDARD_TYPE_)u8OtherMode)
            {
            case E_AUDIOSTANDARD_BG_:
            case E_AUDIOSTANDARD_BG_A2_:
            case E_AUDIOSTANDARD_BG_NICAM_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R840_PAL_BGH_8M_CIF_5M; 
            #else
                StandardMode = R840_PAL_BGH_8M_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_I_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R840_PAL_I_CIF_5M; 
            #else
                StandardMode = R840_PAL_I_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_DK_:
            case E_AUDIOSTANDARD_DK1_A2_:
            case E_AUDIOSTANDARD_DK2_A2_:
            case E_AUDIOSTANDARD_DK3_A2_:
            case E_AUDIOSTANDARD_DK_NICAM_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R840_PAL_DK_CIF_5M; 
            #else
                StandardMode = R840_PAL_DK_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_L_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R840_SECAM_L_CIF_5M;
            #else
                StandardMode = R840_SECAM_L_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_M_:
            case E_AUDIOSTANDARD_M_BTSC_:
            case E_AUDIOSTANDARD_M_A2_:
            case E_AUDIOSTANDARD_M_EIA_J_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R840_MN_CIF_5M;  
            #else
                StandardMode = R840_MN_CIF_5M;
            #endif
                break;

            default:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R840_PAL_DK_CIF_5M;  
            #else
                StandardMode = R840_PAL_DK_CIF_5M;
            #endif
                break;
            }
        }

    }

    memset(&stR840_Info, 0, sizeof(stR840_Info));
    stR840_Info.R840_Standard =StandardMode;
    stR840_Info.RF_KHz = u32FreqKHz;

    if(R840_SetPllData(stR840_Info)== RT_Fail)
    {
        printf("R840_SetFrequency error \n"); 
        return false;
    }
    //return MAPI_TRUE;
    return true;
}

bool DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{

    R840_Set_Info stR840_Info;
    R840_Standard_Type StandardMode;
    #if ENABLE_TUNER_INIT_THREAD
        if(bInitializing)
            return MAPI_FALSE;
    #endif

    if(!bInit_Rafael) //double check lock
    {
        #if ENABLE_TUNER_INIT_THREAD
            mapi_scope_lock(scopeLock, &m_mutexTunerInit);
        #endif
        if(!bInit_Rafael)
        {
            if (R840_Init() == RT_Success)
            {
                bInit_Rafael = 1;
            }
        }
    }

// printf("DTV_SetTune, freq=%ld, a=0x%x,b=0x%x\n",(U32)(Freq*1000),eBandWidth,eMode);
    FREQ_RSSI=(UINT32)(Freq*1000);
	switch(eMode)
    {
    case E_TUNER_DTV_ATSC_MODE:
        StandardMode = R840_ATSC_IF_5M;
        break;
    case E_TUNER_DTV_DTMB_MODE:
        StandardMode = R840_DTMB_8M_IF_5M;
        break;
    case E_TUNER_DTV_DVB_C_MODE:
        if(eBandWidth == E_RF_CH_BAND_6MHz)
        {
            StandardMode = R840_DVB_C_6M_IF_5M;
        }
        else
        {
            StandardMode = R840_DVB_C_8M_IF_5M;
        }
        break;
    case E_TUNER_DTV_DVB_T_MODE:
        if(eBandWidth == E_RF_CH_BAND_6MHz)
        {
            StandardMode = R840_DVB_T_6M_IF_5M;
        }
        else if(eBandWidth == E_RF_CH_BAND_7MHz)
        {
            StandardMode = R840_DVB_T_7M_IF_5M;
        }
        else
        {
            StandardMode = R840_DVB_T_8M_IF_5M;
        }
        break;
    case E_TUNER_DTV_DVB_T2_MODE:
        if(eBandWidth == E_RF_CH_BAND_6MHz)
        {
            StandardMode = R840_DVB_T2_6M_IF_5M;
        }
        else if(eBandWidth == E_RF_CH_BAND_7MHz)
        {
            StandardMode = R840_DVB_T2_7M_IF_5M;
        }
        else
        {
            StandardMode = R840_DVB_T2_8M_IF_5M;
        }
        break;
    case E_TUNER_DTV_ISDB_MODE:
        StandardMode = R840_ISDB_T_IF_5M;
        break;

    default:
        StandardMode = R840_DTMB_8M_IF_5M;
        ////// TODO: error happened
        break;
    }

    memset(&stR840_Info, 0, sizeof(stR840_Info));
    stR840_Info.R840_Standard =StandardMode;
    stR840_Info.RF_KHz = Freq * 1000L;

    if(R840_SetPllData(stR840_Info)== RT_Fail)
    {
        printf("R840_SetFrequency error \n"); 
        return false;
    }

    //return MAPI_TRUE;
    return true;
}


void devTunerInit(void)
{
    device_tuner_R840_init();
}

void devDigitalTuner_Init()
{
    device_tuner_R840_init();
}

void devTunerSetFreq(U32 u32Freq)
{
    BOOLEAN retb = TRUE;

    if (bInit_Rafael == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }
    
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();

    //printf("[CurrentStandard],%d\n",CurrentStandard);
    if(CurrentStandard==IF_FREQ_B)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_G)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }
    else if  (CurrentStandard==IF_FREQ_I)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_I_;
    }
    else if  (CurrentStandard==IF_FREQ_DK)
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_DK_;
    }
    else if  (CurrentStandard==IF_FREQ_L)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_L_PRIME)
    {
        m_eMode = E_TUNER_ATV_SECAM_L_PRIME_MODE;
        m_OtherMode = E_AUDIOSTANDARD_L_;
    }
    else if  (CurrentStandard==IF_FREQ_MN)
    {
        m_eMode = E_TUNER_ATV_NTSC_MODE;
        m_OtherMode = E_AUDIOSTANDARD_M_;
    }
    else
    {
        m_eMode = E_TUNER_ATV_PAL_MODE;
        m_OtherMode = E_AUDIOSTANDARD_BG_;
    }

    DBG_TUNER(printf("[devTunerSetFreq]%s, %d,  m_OtherMode=%d, u32Freq=%ld, CurrentStandard=%d\n",__FILE__,__LINE__,m_OtherMode,u32Freq,CurrentStandard);)

    retb &= ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(U8)m_OtherMode);

    if (retb == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}
void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
    BOOLEAN bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(UINT16)Freq,(U8)eBandWidth,(U8)m_eMode);)

    if (bInit_Rafael == FALSE)
    {
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;

}

BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}

// return dBm....
BOOLEAN mdev_GetSignalStrength(S_RSSI_TABLE* ssi_table, U16 u16_gain, float* f_strength)
{
     R840_ErrCode err = RT_Fail;
     
     R840_RF_Gain_Info pRfGain;
     INT32 RfLevelDbm;
     R840_Standard_Type RT_Standard=R840_DVB_T_8M;
     U8 u8RfMaxGain;

     err = R840_GetRfGain(&pRfGain);
     err = R840_GetRfRssi(FREQ_RSSI, RT_Standard, &RfLevelDbm, &u8RfMaxGain);

     if(err != RT_Success)
     {
         *f_strength=-10.0f;
         printf("\n xhw R840 RF Level Get Error\n");
         return FALSE;
     }
     else
     {
         if (pRfGain.RF_gain_comb > 592)
         {
             U8 indx = 0;
             U8 arry_size = 0;
             float rf_dbm = 0.0;

             for(arry_size = 0;;arry_size++)
             {
                 if (ssi_table[arry_size].u16_if_agc == 0xFFFF) break;
             }
             arry_size--;
 
             if (u16_gain > ssi_table[0].u16_if_agc)
             {
                 rf_dbm = (float)(u16_gain - ssi_table[1].u16_if_agc)/(float)(ssi_table[0].u16_if_agc - ssi_table[1].u16_if_agc)*(ssi_table[0].LvdBm - ssi_table[1].LvdBm)+ssi_table[1].LvdBm;
             }
             else if (u16_gain <= ssi_table[arry_size-1].u16_if_agc)
             {
                 rf_dbm = (float)(u16_gain - ssi_table[arry_size-2].u16_if_agc)/(float)(ssi_table[arry_size-1].u16_if_agc - ssi_table[arry_size-2].u16_if_agc)*(ssi_table[arry_size-1].LvdBm - ssi_table[arry_size-2].LvdBm)+ssi_table[arry_size-2].LvdBm;
             }
             else
             {
                 for(indx = 0;indx<arry_size;indx++)
                 {
                     if (u16_gain > ssi_table[indx].u16_if_agc) break;
                 }
                 rf_dbm = (float)(u16_gain - ssi_table[indx].u16_if_agc)/(float)(ssi_table[indx-1].u16_if_agc - ssi_table[indx].u16_if_agc)*(ssi_table[indx-1].LvdBm - ssi_table[indx].LvdBm)+ssi_table[indx].LvdBm;
             }
             *f_strength=rf_dbm;
         }
         else
         {
             *f_strength= RfLevelDbm;
         }
    }
    return true;
}
