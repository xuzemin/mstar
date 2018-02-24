//-----------------------------------------------------//
//
// Filename: R840.c
//
// This file is R840 tuner driver
//-----------------------------------------------------//
#ifndef RAFAEL_840_842_C
#define RAFAEL_840_842_C
#include <stdio.h>
#include <string.h>
#include "R840_842.h"
#include "R840.c"
#include "R842.c"
#define DBG_TUNER(x)  //x

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


#define DTMB_SYSTEM_ENABLE       1
extern IF_FREQ MDrv_IFDM_GetIF(void);



static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;
R842_Set_Info m_stR842_Info;
R840_Set_Info m_stR840_Info;


UINT8 RFChipId = 0xFF;			        
BOOLEAN devTunerInit(void)
{
	if(RFChipId == 0xff)
	{
		RFChipId = R842_Chip_Detect();
	}
	if(RFChipId == 0xff)
	{
		RFChipId = R840_Chip_Detect();
	}
	if(RFChipId == R840_CHIP_ID)
	{
		return R840_devTunerInit();
	}
	else
	{
		return R842_devTunerInit();
	}
	memset(&m_stR840_Info, 0, sizeof(m_stR840_Info));
	memset(&m_stR842_Info, 0, sizeof(m_stR842_Info));
}
void devDigitalTuner_Init(void)
{
	if(RFChipId == 0xff)
	{
		RFChipId = R842_Chip_Detect();
	}
	if(RFChipId == 0xff)
	{
		RFChipId = R840_Chip_Detect();
	}
	if(RFChipId == R840_CHIP_ID)
	{
		R840_devTunerInit();
	}
	else
	{
		R842_devTunerInit();
	}
	memset(&m_stR840_Info, 0, sizeof(m_stR840_Info));
	memset(&m_stR842_Info, 0, sizeof(m_stR842_Info));
}


BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",m_eMode,OtherMode);)

    return bRet;
}



BOOLEAN R842_ATV_SetTune( U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,U8 u8OtherMode )
{
    R842_Set_Info stR842_Info;
    R842_Standard_Type StandardMode;
    R842_ErrCode err = R842_Fail;
    UNUSED(eBand);
	#if 1
	if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
        StandardMode = R842_SECAM_L1_CIF_5M;
    }
    else if(eMode == E_TUNER_ATV_NTSC_MODE)
    {
    #if DTMB_SYSTEM_ENABLE
        StandardMode = R842_MN_CIF_5M; 
    #else
        StandardMode = R842_MN_CIF_5M;
    #endif
    }
    else
    {
        if(u8OtherMode == 0xff)
        {
        #if DTMB_SYSTEM_ENABLE
            StandardMode = R842_PAL_DK_CIF_5M;  
        #else
            StandardMode = R842_PAL_DK_CIF_5M;
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
                StandardMode = R842_PAL_BGH_8M_CIF_5M; 
            #else
                StandardMode = R842_PAL_BGH_8M_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_I_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_PAL_I_CIF_5M; 
            #else
                StandardMode = R842_PAL_I_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_DK_:
            case E_AUDIOSTANDARD_DK1_A2_:
            case E_AUDIOSTANDARD_DK2_A2_:
            case E_AUDIOSTANDARD_DK3_A2_:
            case E_AUDIOSTANDARD_DK_NICAM_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_PAL_DK_CIF_5M; 
            #else
                StandardMode = R842_PAL_DK_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_L_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_SECAM_L_CIF_5M;
            #else
                StandardMode = R842_SECAM_L_CIF_5M;
            #endif
                break;

            case E_AUDIOSTANDARD_M_:
            case E_AUDIOSTANDARD_M_BTSC_:
            case E_AUDIOSTANDARD_M_A2_:
            case E_AUDIOSTANDARD_M_EIA_J_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_MN_CIF_5M;  
            #else
                StandardMode = R842_MN_CIF_5M;
            #endif
                break;

            default:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_PAL_DK_CIF_5M;  
            #else
                StandardMode = R842_PAL_DK_CIF_5M;
            #endif
                break;
            }
        }

    }
	#else
    if(eMode == E_TUNER_ATV_SECAM_L_PRIME_MODE)
    {
        StandardMode = R842_SECAM_L1;
    }
    else if(eMode == E_TUNER_ATV_NTSC_MODE)
    {
    #if DTMB_SYSTEM_ENABLE
        StandardMode = R842_MN_5800; 
    #else
        StandardMode = R842_MN_5800;
    #endif
    }
    else
    {
        //printf("OtherMode[%d]\r\n",u8OtherMode);
        if(u8OtherMode == 0xff)
        {
        #if DTMB_SYSTEM_ENABLE
            StandardMode = R842_PAL_DK;  
        #else
            StandardMode = R842_PAL_DK;
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
                StandardMode = R842_PAL_BGH_8M; 
            #else
                StandardMode = R842_PAL_BGH_8M;
            #endif
                break;

            case E_AUDIOSTANDARD_I_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_PAL_I; 
            #else
                StandardMode = R842_PAL_I;
            #endif
                break;

            case E_AUDIOSTANDARD_DK_:
            case E_AUDIOSTANDARD_DK1_A2_:
            case E_AUDIOSTANDARD_DK2_A2_:
            case E_AUDIOSTANDARD_DK3_A2_:
            case E_AUDIOSTANDARD_DK_NICAM_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_PAL_DK; 
            #else
                StandardMode = R842_PAL_DK;
            #endif
                break;

            case E_AUDIOSTANDARD_L_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_SECAM_L;
            #else
                StandardMode = R842_SECAM_L;
            #endif
                break;

            case E_AUDIOSTANDARD_M_:
            case E_AUDIOSTANDARD_M_BTSC_:
            case E_AUDIOSTANDARD_M_A2_:
            case E_AUDIOSTANDARD_M_EIA_J_:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_MN_5800;  
            #else
                StandardMode = R842_MN_5800;
            #endif
                break;

            default:
            #if DTMB_SYSTEM_ENABLE
                StandardMode = R842_PAL_DK;  
            #else
                StandardMode = R842_PAL_DK;
            #endif
                break;
            }
        }

    }
	#endif
    memset(&stR842_Info, 0, sizeof(stR842_Info));
	memset(&m_stR842_Info, 0, sizeof(m_stR842_Info));
    stR842_Info.R842_Standard =StandardMode;
    stR842_Info.RF_KHz = u32FreqKHz;
	printf("$$$--2-- >>> stR842_Info.RF_KHz =%ld ,stR842_Info.R842_Standard = %d",stR842_Info.RF_KHz,stR842_Info.R842_Standard);
    err = R842_SetPllData(stR842_Info);

    if(err == R842_Fail)
    {
         printf("\n ====> R842_ATV_SetTune error \n"); 
		 return FALSE;
    }
	memcpy(&m_stR842_Info, &stR842_Info, sizeof(m_stR842_Info));
    return TRUE;
}

BOOLEAN R842_DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    R842_Set_Info stR842_Info;
    R842_Standard_Type StandardMode;
    R842_ErrCode err = R842_Fail;
    switch(eMode)
    {
    case E_TUNER_DTV_ATSC_MODE:
        StandardMode = R842_ATSC_IF_5M;
        break;
    case E_TUNER_DTV_DTMB_MODE:
        StandardMode = R842_DTMB_8M_IF_5M;
        break;
    case E_TUNER_DTV_DVB_C_MODE:
        if(eBandWidth == E_RF_CH_BAND_6MHz)
        {
            StandardMode = R842_DVB_C_6M_IF_5M;
        }
        else
        {
            StandardMode = R842_DVB_C_8M_IF_5M;
        }
        break;
    case E_TUNER_DTV_DVB_T_MODE:
        if(eBandWidth == E_RF_CH_BAND_6MHz)
        {
            StandardMode = R842_DVB_T_6M_IF_5M;
        }
        else if(eBandWidth == E_RF_CH_BAND_7MHz)
        {
            StandardMode = R842_DVB_T_7M_IF_5M;
        }
        else
        {
            StandardMode = R842_DVB_T_8M_IF_5M;
        }
        break;
    case E_TUNER_DTV_DVB_T2_MODE:
        if(eBandWidth == E_RF_CH_BAND_6MHz)
        {
            StandardMode = R842_DVB_T2_6M_IF_5M;
        }
        else if(eBandWidth == E_RF_CH_BAND_7MHz)
        {
            StandardMode = R842_DVB_T2_7M_IF_5M;
        }
        else
        {
            StandardMode = R842_DVB_T2_8M_IF_5M;
        }
        break;
    case E_TUNER_DTV_ISDB_MODE:
        StandardMode = R842_ISDB_T_IF_5M;
        break;

    default:
        StandardMode = R842_DTMB_8M_IF_5M;
        // TODO: error happened
        break;
    }

    memset(&stR842_Info, 0, sizeof(stR842_Info));
	memset(&m_stR842_Info, 0, sizeof(m_stR842_Info));
    stR842_Info.R842_Standard =StandardMode;
	//<<SMC daifq 20170808
	if (eMode == E_TUNER_DTV_ATSC_MODE || eMode == E_TUNER_DTV_QAM_US_MODE)
		stR842_Info.RF_KHz = Freq;
	else
	//<<
      stR842_Info.RF_KHz =Freq * 1000L;
    err = R842_SetPllData(stR842_Info);

    if(err == R842_Fail)
    {
       printf("\n ====> R842_DTV_SetTune error \n"); 
	   return FALSE;
    }
	memcpy(&m_stR842_Info, &stR842_Info, sizeof(m_stR842_Info));
    return TRUE;
}

BOOLEAN R840_ATV_SetTune( U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,U8 u8OtherMode )
{
    R840_Set_Info stR840_Info;
    R840_Standard_Type StandardMode;
    R840_ErrCode err = RT_Fail;
    UNUSED(eBand);
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
	memset(&m_stR840_Info, 0, sizeof(m_stR840_Info));
    stR840_Info.R840_Standard =StandardMode;
    stR840_Info.RF_KHz = u32FreqKHz;
    err = R840_SetPllData(stR840_Info);
	
	if(err == RT_Fail)
    {
         printf("\n ====>> R840_ATV_SetTune error \n"); 
		 return FALSE;
    }
	
	memcpy(&m_stR840_Info, &stR840_Info, sizeof(m_stR840_Info));
    return TRUE;

}

BOOLEAN R840_DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    R840_Set_Info stR840_Info;
    R840_Standard_Type StandardMode;
    R840_ErrCode err = RT_Fail;

    switch(eMode)
    {
    case E_TUNER_DTV_ATSC_MODE:
        StandardMode = R840_ATSC_IF_5M;
        break;
    case E_TUNER_DTV_DTMB_MODE:
        StandardMode = R840_DTMB_8M_IF_5M;
		printf("\n ====>> DTV_SetTune R840_DTMB_8M_IF_5M ===>>/n");
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
        // TODO: error happened
        break;
    }

    memset(&stR840_Info, 0, sizeof(stR840_Info));
	memset(&m_stR840_Info, 0, sizeof(m_stR840_Info));
    stR840_Info.R840_Standard =StandardMode;
	//<<SMC daifq 20170808
	if (eMode == E_TUNER_DTV_ATSC_MODE || eMode == E_TUNER_DTV_QAM_US_MODE)
		stR840_Info.RF_KHz = Freq;
	else
	//<<
     stR840_Info.RF_KHz = Freq * 1000L;

	//printf("111111111 %d\n", (int)stR840_Info.RF_KHz);
    err = R840_SetPllData(stR840_Info);
	
    if(err == RT_Fail)
    {
         printf("\n ====>> R840_DTV_SetTune error \n"); 
		 return FALSE;
    }
	memcpy(&m_stR840_Info, &stR840_Info, sizeof(m_stR840_Info));
    return TRUE;
}


void devTunerSetFreq(U32 u32Freq)
{
    BOOLEAN retb = FALSE;
    IF_FREQ CurrentStandard = MDrv_IFDM_GetIF();
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
	
	if(RFChipId == 0xff)
	{
		RFChipId = R842_Chip_Detect();
		if(RFChipId == 0xff)
		{
			RFChipId = R840_Chip_Detect();
		}
		if(RFChipId == R840_CHIP_ID)
		{
			R840_devTunerInit();
		}
		else
		{
			R842_devTunerInit();
		}
	}
	if(RFChipId == R840_CHIP_ID)
	{
		retb = R840_ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(U8)m_OtherMode);
	}
	else
	{
		retb = R842_ATV_SetTune(u32Freq/1000,(RFBAND)0, m_eMode,(U8)m_OtherMode);
	}
		 
    if (retb == FALSE)
    {
        DBG_TUNER(printf("\n ====>> [Error]%s,%d,devTunerSetFreq Fail \n",__FILE__,__LINE__));
    }
 }

void devDigitalTuner_SetFreq( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{
    BOOLEAN bRet = FALSE;

	if(RFChipId == 0xff)
	{
		RFChipId = R842_Chip_Detect();
		if(RFChipId == 0xff)
		{
			RFChipId = R840_Chip_Detect();
		}
		if(RFChipId == R840_CHIP_ID)
		{
			R840_devTunerInit();
		}
		else
		{
			R842_devTunerInit();
		}
	}
	if(RFChipId == R840_CHIP_ID)
	{
		bRet = R840_DTV_SetTune(Freq, eBandWidth, m_eMode);
	}
	else
	{
	     printf("m_eMode=%d\n",m_eMode);
		bRet = R842_DTV_SetTune(Freq, eBandWidth, m_eMode);
	}
		 
    if (bRet == FALSE)
    {
        DBG_TUNER(printf("\n ====>> [Error]%s,%d,devDigitalTuner_SetFreq Fail \n",__FILE__,__LINE__));
    }
}



BOOLEAN mdev_GetSignalStrength(float* f_strength)
{

	INT32 s32RFLevelDbm;
	BOOLEAN err = TRUE;
	if(RFChipId == R840_CHIP_ID)
    {	if(m_stR840_Info.RF_KHz > 0)
		{
		 	if(R840_GetTotalRssi(m_stR840_Info.RF_KHz, m_stR840_Info.R840_Standard,&s32RFLevelDbm) != RT_Success)
		 	{
		 		err = FALSE;
				printf("\n R840 s32RFLevelDbm========>> %d",s32RFLevelDbm);
		 	}
		}
	}
	else
	{
		if(m_stR842_Info.RF_KHz > 0)
		{
		 	if(R842_GetTotalRssi(m_stR842_Info.RF_KHz, m_stR842_Info.R842_Standard,&s32RFLevelDbm) != RT_Success)
		 	{
		 		err = FALSE;
				printf("\n R842 s32RFLevelDbm========>> %d",s32RFLevelDbm);
		 	}
		}
	}
	
	if(err == FALSE)
	{
        // temporary formula, (-55 ~ 0)dBm to (50% ~ 100%)
        *f_strength = (float)s32RFLevelDbm / 55.0f * (66.0f - 41.0f) - 41.0f;
	}
    else
    {
    	*f_strength = -10.0f;
		printf("RF Level Get Error\n");
    }
    return true;
}

#undef RAFAEL_840_842_C

#endif

