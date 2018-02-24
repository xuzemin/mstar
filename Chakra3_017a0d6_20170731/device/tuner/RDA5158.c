//*****************************************************************************
// File:    device_tuner_R840.cpp
// Owner:   Smart-core
// Author:  Steven wang
// Date:    2013-07-08
//*****************************************************************************


#ifndef RDA5158_C
#define RDA5158_C

/*@ <Include> @*/
#include "debug.h"
#include "RDA5158.h"
#include "MsTypes.h"
#include "datatype.h"
#include "drvIIC.h"
#include "drvDMD_common.h"
#include "drvDMD_INTERN_DVBT.h"
#include "drvDMD_INTERN_DVBC.h"

#include "RDA5158/rda5158_drv.c"
#include "RDA5158/rda5158_drv.h"




#define DBG_TUNER(x)  x

//#define TN_FREQ_STEP                E_FREQ_STEP_62_5KHz


#define MIN_FREQ_SUPPORT_KHz        40000
#define MAX_FREQ_SUPPORT_KHz        880000

#define TUNER_DTV_IQ_SWAP           1// iq swap

BOOLEAN  m_bDeviceBusy = FALSE;
static EN_TUNER_MODE m_eMode = E_TUNER_DTV_DVB_T_MODE;//E_TUNER_INVALID;
static AUDIOSTANDARD_TYPE_ m_OtherMode = E_AUDIOSTANDARD_NOTSTANDARD_;

#define C_RDA5158_LO_ADDRESS           ((U8)  0xC0)
#define RDA_5158_I2C_ADDR (((U16)TUNER_IIC_BUS<<8)| C_RDA5158_LO_ADDRESS)

// Analog picture carrier
#define ATV_VC_MN  6000L
#define ATV_VC_B   6600L
#define ATV_VC_GH  6600L
#define ATV_VC_I   7300L
#define ATV_VC_DK  7300L
#define ATV_VC_L   7000L
#define ATV_VC_LL  7000L

// [21:0], CR_RATE for Video_Carrier_BBB KHz, HEX((Video_Carrier_BBB/43200.0) * (2^22))
#define VIF_TUNER_TYPE                  1                   // 0: RF Tuner; 1: Silicon Tuner
#define VIF_CR_RATE_B                   (MAPI_U32)(ATV_VC_B*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_B                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_GH                  (MAPI_U32)(ATV_VC_GH*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_GH                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_DK                  (MAPI_U32)(ATV_VC_DK*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_DK                0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_I                   (MAPI_U32)(ATV_VC_I*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_I                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_L                   (MAPI_U32)(ATV_VC_L*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_L                 0                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_LL                  (MAPI_U32)(ATV_VC_LL*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_LL                1                   // Video carrier position; 0: high side; 1:low side
#define VIF_CR_RATE_MN                  (MAPI_U32)(ATV_VC_MN*4194304.0/43200.0+0.5)
#define VIF_CR_INVERT_MN                0                   // Video carrier position; 0: high side; 1:low side


//B_Stereo_A2 ========================
// VideoIF = 7.0M
const U16 VIF_A1_A2_SOS11_SOS12_B_Stereo_A2[16]=
{
// 1.75Mhz
0x03A4,0x063C,0x0421,
// 1.51Mhz
0x03AB,0x063C,0x0419,
// 8.75Mhz
0x011B,0x063C,0x0200,0x06D3,0x0200,
// 1.75Mhz
0x03A4,0x063C,0x0200,0x0421,0x0200
};



//B_Mono_NICAM ====================
// 1.75Mhz
#define N_A1_C0_B_NICAM 0x03A3
#define N_A1_C1_B_NICAM 0x063C
#define N_A1_C2_B_NICAM 0x0421
// 1.4Mhz
#define N_A2_C0_B_NICAM 0x03AF
#define N_A2_C1_B_NICAM 0x063C
#define N_A2_C2_B_NICAM 0x0415
// 8.75Mhz
#define S_11_C0_B_NICAM 0x011B
#define S_11_C1_B_NICAM 0x063C
#define S_11_C2_B_NICAM 0x0200
#define S_11_C3_B_NICAM 0x06D3
#define S_11_C4_B_NICAM 0x0200
// 1.75Mhz
#define S_12_C0_B_NICAM 0x03A4
#define S_12_C1_B_NICAM 0x063C
#define S_12_C2_B_NICAM 0x0200
#define S_12_C3_B_NICAM 0x0421
#define S_12_C4_B_NICAM 0x0200


const MS_U16 VIF_A1_A2_SOS11_SOS12_GH_Stereo_A2[16]=
{
//GH_Stereo_A2 ======================
// 2.25Mhz
0x038F,0x063C,0x0436,
// 2.01Mhz
0x039A,0x063C,0x042B,
// 10.25Mhz
0x004D,0x063C,0x0200,0x07AE,0x0200,
// 2.25Mhz
0x038F,0x063C,0x0200,0x0436,0x0200
};


//GH_Mono_NICAM ===================
// 2.25Mhz
#define N_A1_C0_GHMN 0x038F
#define N_A1_C1_GHMN 0x063C
#define N_A1_C2_GHMN 0x0436
// 1.9Mhz
#define N_A2_C0_GHMN 0x039E
#define N_A2_C1_GHMN 0x063C
#define N_A2_C2_GHMN 0x0427
// 10.25Mhz
#define S_11_C0_GHMN 0x004D
#define S_11_C1_GHMN 0x063C
#define S_11_C2_GHMN 0x0200
#define S_11_C3_GHMN 0x07AE
#define S_11_C4_GHMN 0x0200
// 2.25Mhz
#define S_12_C0_GHMN 0x038F
#define S_12_C1_GHMN 0x063C
#define S_12_C2_GHMN 0x0200
#define S_12_C3_GHMN 0x0436
#define S_12_C4_GHMN 0x0200


const MS_U16 VIF_A1_A2_SOS11_SOS12_DK1_Stereo_A2[16]=
{
//DK1_Stero_A2 ======================
// 1.25Mhz
0x03B3,0x063C,0x0411,
// 1.49Mhz
0x03AC,0x063C,0x0418,
// 9.25Mhz
0x00D7,0x063C,0x0200,0x071B,0x0200,
// 1.25Mhz
0x03B3,0x063C,0x0200,0x0411,0x0200
};

const MS_U16 VIF_A1_A2_SOS11_SOS12_DK2_Stereo_A2[16]=
{
//DK2_Stero_A2 ======================
// 1.25Mhz
0x03B3,0x063C,0x0411,
// 1.01Mhz
0x03B3,0x063C,0x040B,
// 9.25Mhz
0x00D7,0x063C,0x0200,0x071B,0x0200,
// 1.25Mhz
0x03B3,0x063C,0x0200,0x0411,0x0200
};

const MS_U16 VIF_A1_A2_SOS11_SOS12_DK3_Stereo_A2[16]=
{
//DK3_Stero_A2 ======================
// 1.25Mhz
0x03B3,0x063C,0x0411,
// 2.01Mhz
0x039A,0x063C,0x042B,
// 9.25Mhz
0x00D7,0x063C,0x0200,0x071B,0x0200,
// 1.25Mhz
0x03B3,0x063C,0x0200,0x0411,0x0200
};


//DK_Mono_NICAM===================
// 1.25Mhz
#define N_A1_C0_DKMN 0x03B3
#define N_A1_C1_DKMN 0x063C
#define N_A1_C2_DKMN 0x0411
// 1.9Mhz
#define N_A2_C0_DKMN 0x039E
#define N_A2_C1_DKMN 0x063C
#define N_A2_C2_DKMN 0x0427
// 9.25Mhz
#define S_11_C0_DKMN 0x00D7
#define S_11_C1_DKMN 0x063C
#define S_11_C2_DKMN 0x0200
#define S_11_C3_DKMN 0x071B
#define S_11_C4_DKMN 0x0200
// 1.25Mhz
#define S_12_C0_DKMN 0x03B3
#define S_12_C1_DKMN 0x063C
#define S_12_C2_DKMN 0x0200
#define S_12_C3_DKMN 0x0411
#define S_12_C4_DKMN 0x0200

const MS_U16 VIF_A1_A2_SOS11_SOS12_I[16]=
{
//Sound : I ======================
// 1.75Mhz
0x03A4,0x063C,0x0421,
// 1.2Mhz
0x03B4,0x063C,0x0410,
// 9.75Mhz
0x0092,0x063C,0x0200,0x0764,0x0200,
// 1.75Mhz
0x03A4,0x063C,0x0200,0x0421,0x0200
};

const U16 VIF_A1_A2_SOS11_SOS12_MN[16]=
{
//Sound : MN=========================
// 2.25Mhz
0x038F,0x063C,0x0436,
// 2.03Mhz
0x0399,0x063C,0x042C,
// 8.25Mhz
0x015D,0x063C,0x0200,0x068D,0x0200,
// 2.25Mhz
0x038F,0x063C,0x0200,0x0436,0x0200
};


// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_LP[16]=
{
//Sound : L ==========================
// 1.25Mhz
0x03B3,0x063C,0x0411,
// 1.9Mhz
0x039E,0x063C,0x0427,
// 9.25Mhz
0x00D7,0x063C,0x0200,0x071B,0x0200,
// 1.25Mhz
0x03B3,0x063C,0x0200,0x0411,0x0200
};

// VideoIF = 8.0M
const U16 VIF_A1_A2_SOS11_SOS12_L[16]=
{
//Sound : L ==========================
// 8.75Mhz
0x011B,0x063C,0x06D3,
// 8.1Mhz
0x0170,0x063C,0x0678,
// 0.75Mhz
0x03BD,0x063C,0x0200,0x0406,0x0200,
// 8.75Mhz
0x011B,0x063C,0x0200,0x06D3,0x0200
};



//End of Table===================

#define VIF_SOS_21_FILTER_C0        0x0268
#define VIF_SOS_21_FILTER_C1        0x071E
#define VIF_SOS_21_FILTER_C2        0x01D6
#define VIF_SOS_21_FILTER_C3        0x0598
#define VIF_SOS_21_FILTER_C4        0x010C
#define VIF_SOS_22_FILTER_C0        0x027C
#define VIF_SOS_22_FILTER_C1        0x0707
#define VIF_SOS_22_FILTER_C2        0x01E5
#define VIF_SOS_22_FILTER_C3        0x0584
#define VIF_SOS_22_FILTER_C4        0x0114

#define VIF_SOS_31_FILTER_C0        0x022A
#define VIF_SOS_31_FILTER_C1        0x0754
#define VIF_SOS_31_FILTER_C2        0x00AC
#define VIF_SOS_31_FILTER_C3        0x05D6
#define VIF_SOS_31_FILTER_C4        0x0200
#define VIF_SOS_32_FILTER_C0        0x01EB
#define VIF_SOS_32_FILTER_C1        0x078A
#define VIF_SOS_32_FILTER_C2        0x0076
#define VIF_SOS_32_FILTER_C3        0x0615
#define VIF_SOS_32_FILTER_C4        0x0200

// I2C define start

MS_BOOL i2c0SendData(MAPI_U8 addr, MAPI_U16 rdata)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    /* Variable declarations */
    //mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(RDA_5158_I2C_ADDR);
    bRet &= MDrv_IIC_WriteBytes((U16)((TUNER_IIC_BUS<<8)|RDA_5158_I2C_ADDR), 0, NULL, 2,u8Value);
    if (bRet ==FALSE)
    {
        printf(" ERROR in RDA5158_WriteReg !!! \n");
    }
    return bRet;	

	
    //MAPI_U8 i;
    MAPI_U8 pAddr[1]={0};
	MAPI_U8 pdata[2]={0,0};

    // make address
	pAddr[0]=(addr&0xff);

    // make send data
	pdata[0]=(rdata>>8&0xff);
	pdata[1]=(rdata&0xff);

	if(iptr != NULL)
		{
          if(iptr->WriteBytes(1, pAddr, 2, pdata) == FALSE)
          {
              DBG_TUNER(printf("RDA5158 i2c0SendData Fail\n"));
          }
		}
	else
		{
          DBG_TUNER(printf("RDA5158 i2c0SendData config fail\n"));
		}

}

MAPI_U16 i2c0GetData(MAPI_U8 addr)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    /* Variable declarations */
    //mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(RDA_5158_I2C_ADDR);
    bRet &= MDrv_IIC_WriteBytes((U16)((TUNER_IIC_BUS<<8)|RDA_5158_I2C_ADDR), 0, NULL, 2,u8Value);
    if (bRet ==FALSE)
    {
        printf(" ERROR in RDA5158_WriteReg !!! \n");
    }
    return bRet;	

    MAPI_U16 rdata=0;
	MAPI_U8 pAddr[2]={0,0};
	MAPI_U8 pdata[2]={0,0};

    // make address
	pAddr[0]=(addr&0xff);

    if(iptr != NULL)
    	{
          if(iptr->ReadBytes(1, pAddr, 2, pdata) == FALSE)
          {
              DBG_TUNER(printf("RDA5158 i2c0GetData  fail\n"));
          }
    	}
	else
		{
          DBG_TUNER(printf("RDA5158 i2c0GetData  config fail\n"));
		}

    rdata = (pdata[0])<<8;
    rdata |= pdata[1];

	return rdata;
}

MS_BOOL i2c1SendData(MAPI_U16 page, MAPI_U32 offset, MAPI_U16 wdata)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    /* Variable declarations */
    //mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(RDA_5158_I2C_ADDR);
    bRet &= MDrv_IIC_WriteBytes((U16)((TUNER_IIC_BUS<<8)|RDA_5158_I2C_ADDR), 0, NULL, 2,u8Value);
    if (bRet ==FALSE)
    {
        printf(" ERROR in RDA5158_WriteReg !!! \n");
    }
    return bRet;	
    //MAPI_U8 i;
    MAPI_U8 pAddr[4]={0,0,0,0};
	MAPI_U8 pdata[2]={0,0};
	
    MAPI_U32 addr = 0;
    addr = page;
    addr <<= 20;
    addr |= offset;

    // make address
	pAddr[0]=((addr<<1|0x01));
	pAddr[1]=((addr>>16));
	pAddr[2]=((addr>>24));
	pAddr[3]=((addr>>7));

    // make send data
	pdata[0]=(wdata);
	pdata[1]=((wdata>>8));

	if(iptr != NULL)
		{
          if(iptr->WriteBytes(4, pAddr, 2, pdata) == FALSE)
          {
              DBG_TUNER(printf("RDA5158 i2c1SendData Fail\n"));
          }
		}
	else
		{
         DBG_TUNER(printf("RDA5158 i2c1SendData config fail\n"));
		}
}

MS_BOOL i2c1SendDataA(MAPI_U32 addr, MAPI_U16 wdata)
{   
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    /* Variable declarations */
    //mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(RDA_5158_I2C_ADDR);
    bRet &= MDrv_IIC_WriteBytes((U16)((TUNER_IIC_BUS<<8)|RDA_5158_I2C_ADDR), 0, NULL, 2,u8Value);
    if (bRet ==FALSE)
    {
        printf(" ERROR in RDA5158_WriteReg !!! \n");
    }
    return bRet;	
    //MAPI_U8 i;
    MAPI_U8 pAddr[4]={0,0,0,0};
	MAPI_U8 pdata[2]={0,0};
	
    // make address
	pAddr[0]=((addr<<1|0x01));
	pAddr[1]=((addr>>16));
	pAddr[2]=((addr>>24));
	pAddr[3]=((addr>>7));

    // make send data
	pdata[0]=(wdata);
	pdata[1]=((wdata>>8));

	if(iptr != NULL)
		{
           if(iptr->WriteBytes(4, pAddr, 2, pdata) == FALSE)
           {
               DBG_TUNER(printf("RDA5158 i2c1SendDataA Fail\n"));
           }
		}
	else
		{
         DBG_TUNER(printf("RDA5158 i2c1SendDataA config Fail\n"));
		}

	
}

MAPI_U16 i2c1GetData(MAPI_U16 page, MAPI_U32 offset)
{
    MS_BOOL bRet=TRUE;
    MS_U8 u8Value[2];
    /* Variable declarations */
    //mapi_i2c *iptr = mapi_i2c_GetI2C_Dev(RDA_5158_I2C_ADDR);
    bRet &= MDrv_IIC_WriteBytes((U16)((TUNER_IIC_BUS<<8)|RDA_5158_I2C_ADDR), 0, NULL, 2,u8Value);
    if (bRet ==FALSE)
    {
        printf(" ERROR in RDA5158_WriteReg !!! \n");
    }
    return bRet;	

	MAPI_U8 pAddr[4]={0,0,0,0};
	MAPI_U8 pdata[2]={0,0};

    MAPI_U32 addr = 0;
    MAPI_U16 rdata = 0;

    addr = page;
    addr <<= 20;
    addr |= offset;


    // make address
	pAddr[0]=((addr<<1|0x01));
	pAddr[1]=((addr>>16));
	pAddr[2]=((addr>>24));
	pAddr[3]=((addr>>7));

    if(iptr != NULL)
    	{
          if(iptr->ReadBytes(4, pAddr, 2, pdata) == FALSE)
          {
              DBG_TUNER(printf("RDA5158 i2c1GetData  fail\n"));
          }
    	}
	else
		{
          DBG_TUNER(printf("RDA5158 i2c1GetData config fail\n"));
		}

    rdata = pdata[0];
    rdata |= (pdata[1]<<8);

    return rdata;
}

// I2C define end


/*
MAPI_BOOL Disconnect(void)
{
    DBG_TUNER(printf("device_tuner_RDA5158: Disconnect\n"));

    m_bDeviceBusy = 0;

    return TRUE;
}
*/


BOOLEAN ATV_SetTune( MAPI_U32 u32FreqKHz,RFBAND eBand, EN_TUNER_MODE eMode,MAPI_U8 u8OtherMode )
{
 RDA_TV_MODE tv_mode;

    switch((AUDIOSTANDARD_TYPE_)u8OtherMode)
    {
    case E_AUDIOSTANDARD_BG_:
    case E_AUDIOSTANDARD_BG_A2_:
    case E_AUDIOSTANDARD_BG_NICAM_:
        tv_mode = RDA_B;
        break;

    case E_AUDIOSTANDARD_I_:
        tv_mode = RDA_I;
        break;

    case E_AUDIOSTANDARD_DK_:
    case E_AUDIOSTANDARD_DK1_A2_:
    case E_AUDIOSTANDARD_DK2_A2_:
    case E_AUDIOSTANDARD_DK3_A2_:
    case E_AUDIOSTANDARD_DK_NICAM_:
        tv_mode = RDA_DK;
        break;

    case E_AUDIOSTANDARD_L_:
        tv_mode = RDA_L;
        break;

    case E_AUDIOSTANDARD_M_:
    case E_AUDIOSTANDARD_M_BTSC_:
    case E_AUDIOSTANDARD_M_A2_:
    case E_AUDIOSTANDARD_M_EIA_J_:
        tv_mode = RDA_M;
        break;

    default:
        tv_mode = RDA_M;
        break;
    }

    rdaTVAtvFreqTuneSet(u32FreqKHz,tv_mode);
    return TRUE;
}

BOOLEAN DTV_SetTune(double Freq, RF_CHANNEL_BANDWIDTH eBandWidth, EN_TUNER_MODE eMode)
{
    MAPI_U16 band;

	//UNUSED(eMode);

    switch(eBandWidth)
    	{
         case E_RF_CH_BAND_6MHz:
		 	band = 6000;
			break;
			
         case E_RF_CH_BAND_7MHz:
		 	band = 7000;
			break;
			
         case E_RF_CH_BAND_8MHz:
		 	band = 8000;
			break;
			
		 default:
		 	band = 6000;
			break;
    	}
	
    rdaTVDtvFreqTuneSet(Freq,band,eMode);
    return TRUE;
}

#if 0
BOOLEAN ExtendCommand(MAPI_U8 u8SubCmd, MAPI_U32 u32Param1, MAPI_U32 u32Param2, void* pvoidParam3)
{
    switch(u8SubCmd)
    {
        case E_TUNER_SUBCMD_GET_FREQ_STEP:
            {
                EN_FREQ_STEP *eFreqStep = (EN_FREQ_STEP*)pvoidParam3;
                *eFreqStep = TN_FREQ_STEP;
            }
            break;

        case E_TUNER_SUBCMD_GET_IF_FREQ:
            {
                MAPI_U16 *u16IFFreq = (MAPI_U16 *)pvoidParam3;
                *u16IFFreq = TUNER_IF_FREQ_KHz;
            }
            break;

        case E_TUNER_SUBCMD_GET_L_PRIME_IF_FREQ:
            {
                MAPI_U16 *u16IFFreq = (MAPI_U16 *)pvoidParam3;
                *u16IFFreq = TUNER_L_PRIME_IF_FREQ_KHz;
            }
            break;

        case E_TUNER_SUBCMD_GET_VHF_LOWMIN_FREQ:
            {
                MAPI_U32 *u32Freq = (MAPI_U32 *)pvoidParam3;
                *u32Freq = VHF_LOWMIN_FREQ;
            }
            break;

        case E_TUNER_SUBCMD_GET_VHF_LOWMAX_FREQ:
            {
                MAPI_U32 *u32Freq = (MAPI_U32 *)pvoidParam3;
                *u32Freq = VHF_LOWMAX_FREQ;
            }
            break;

        case E_TUNER_SUBCMD_GET_VHF_HIGHMIN_FREQ:
            {
                MAPI_U32 *u32Freq = (MAPI_U32 *)pvoidParam3;
                *u32Freq = VHF_HIGHMIN_FREQ;
            }
            break;

        case E_TUNER_SUBCMD_GET_VHF_HIGHMAX_FREQ:
            {
                MAPI_U32 *u32Freq = (MAPI_U32 *)pvoidParam3;
                *u32Freq = VHF_HIGHMAX_FREQ;
            }
            break;

        case E_TUNER_SUBCMD_GET_UHF_MIN_FREQ:
            {
                MAPI_U32 *u32Freq = (MAPI_U32 *)pvoidParam3;
                *u32Freq = UHF_MIN_FREQ;
            }
            break;

        case E_TUNER_SUBCMD_GET_UHF_MAX_FREQ:
            {
                MAPI_U32 *u32Freq = (MAPI_U32 *)pvoidParam3;
                *u32Freq = UHF_MAX_FREQ;
            }
            break;

        case E_TUNER_SUBCMD_GET_VIF_TUNER_TYPE:
        {
            MAPI_U8 *u8VifTunerType = (MAPI_U8 *)pvoidParam3;
            *u8VifTunerType = VIF_TUNER_TYPE;
        }
            break;

        case E_TUNER_SUBCMD_GET_VIF_PARA:
        {
            mapi_vif_datatype::stVIFInitialIn *p_stVIFInitialIn = (mapi_vif_datatype::stVIFInitialIn *)pvoidParam3;

            p_stVIFInitialIn->VifCrRate_B = VIF_CR_RATE_B;
            p_stVIFInitialIn->VifCrInvert_B = VIF_CR_INVERT_B;
            p_stVIFInitialIn->VifCrRate_GH = VIF_CR_RATE_GH;
            p_stVIFInitialIn->VifCrInvert_GH = VIF_CR_INVERT_GH;
            p_stVIFInitialIn->VifCrRate_DK = VIF_CR_RATE_DK;
            p_stVIFInitialIn->VifCrInvert_DK = VIF_CR_INVERT_DK;
            p_stVIFInitialIn->VifCrRate_I = VIF_CR_RATE_I;
            p_stVIFInitialIn->VifCrInvert_I = VIF_CR_INVERT_I;
            p_stVIFInitialIn->VifCrRate_L = VIF_CR_RATE_L;
            p_stVIFInitialIn->VifCrInvert_L = VIF_CR_INVERT_L;
            p_stVIFInitialIn->VifCrRate_LL = VIF_CR_RATE_LL;
            p_stVIFInitialIn->VifCrInvert_LL = VIF_CR_INVERT_LL;
            p_stVIFInitialIn->VifCrRate_MN = VIF_CR_RATE_MN;
            p_stVIFInitialIn->VifCrInvert_MN = VIF_CR_INVERT_MN;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_VIF_NOTCH_SOSFILTER:
        {
            MAPI_U32 u32NotchDataLength = u32Param2;
            MAPI_U16* pu16NotchData = (MAPI_U16 *)pvoidParam3;
            MAPI_U16* pu16SOSFilterData = ((MAPI_U16 *)pvoidParam3) + u32NotchDataLength;
            switch((mapi_vif_datatype::EN_VIF_SOUND_SYSTEM)u32Param1)
            {
               case mapi_vif_datatype::E_VIF_SOUND_B_STEREO_A2:
                    pu16NotchData[0] = N_A1_C0_B_A2;
                    pu16NotchData[1] = N_A1_C1_B_A2;
                    pu16NotchData[2] = N_A1_C2_B_A2;

                    pu16NotchData[3] = N_A2_C0_B_A2;
                    pu16NotchData[4] = N_A2_C1_B_A2;
                    pu16NotchData[5] = N_A2_C2_B_A2;

                    pu16SOSFilterData[0] = S_11_C0_B_A2;
                    pu16SOSFilterData[1] = S_11_C1_B_A2;
                    pu16SOSFilterData[2] = S_11_C2_B_A2;
                    pu16SOSFilterData[3] = S_11_C3_B_A2;
                    pu16SOSFilterData[4] = S_11_C4_B_A2;

                    pu16SOSFilterData[5] = S_12_C0_B_A2;
                    pu16SOSFilterData[6] = S_12_C1_B_A2;
                    pu16SOSFilterData[7] = S_12_C2_B_A2;
                    pu16SOSFilterData[8] = S_12_C3_B_A2;
                    pu16SOSFilterData[9] = S_12_C4_B_A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_B_MONO_NICAM:
                    pu16NotchData[0] = N_A1_C0_B_NICAM;
                    pu16NotchData[1] = N_A1_C1_B_NICAM;
                    pu16NotchData[2] = N_A1_C2_B_NICAM;

                    pu16NotchData[3] = N_A2_C0_B_NICAM;
                    pu16NotchData[4] = N_A2_C1_B_NICAM;
                    pu16NotchData[5] = N_A2_C2_B_NICAM;

                    pu16SOSFilterData[0] = S_11_C0_B_NICAM;
                    pu16SOSFilterData[1] = S_11_C1_B_NICAM;
                    pu16SOSFilterData[2] = S_11_C2_B_NICAM;
                    pu16SOSFilterData[3] = S_11_C3_B_NICAM;
                    pu16SOSFilterData[4] = S_11_C4_B_NICAM;

                    pu16SOSFilterData[5] = S_12_C0_B_NICAM;
                    pu16SOSFilterData[6] = S_12_C1_B_NICAM;
                    pu16SOSFilterData[7] = S_12_C2_B_NICAM;
                    pu16SOSFilterData[8] = S_12_C3_B_NICAM;
                    pu16SOSFilterData[9] = S_12_C4_B_NICAM;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_STEREO_A2:
                    pu16NotchData[0] = N_A1_C0_GHA2;
                    pu16NotchData[1] = N_A1_C1_GHA2;
                    pu16NotchData[2] = N_A1_C2_GHA2;

                    pu16NotchData[3] = N_A2_C0_GHA2;
                    pu16NotchData[4] = N_A2_C1_GHA2;
                    pu16NotchData[5] = N_A2_C2_GHA2;

                    pu16SOSFilterData[0] = S_11_C0_GHA2;
                    pu16SOSFilterData[1] = S_11_C1_GHA2;
                    pu16SOSFilterData[2] = S_11_C2_GHA2;
                    pu16SOSFilterData[3] = S_11_C3_GHA2;
                    pu16SOSFilterData[4] = S_11_C4_GHA2;

                    pu16SOSFilterData[5] = S_12_C0_GHA2;
                    pu16SOSFilterData[6] = S_12_C1_GHA2;
                    pu16SOSFilterData[7] = S_12_C2_GHA2;
                    pu16SOSFilterData[8] = S_12_C3_GHA2;
                    pu16SOSFilterData[9] = S_12_C4_GHA2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_GH_MONO_NICAM:
                    pu16NotchData[0] = N_A1_C0_GHMN;
                    pu16NotchData[1] = N_A1_C1_GHMN;
                    pu16NotchData[2] = N_A1_C2_GHMN;

                    pu16NotchData[3] = N_A2_C0_GHMN;
                    pu16NotchData[4] = N_A2_C1_GHMN;
                    pu16NotchData[5] = N_A2_C2_GHMN;

                    pu16SOSFilterData[0] = S_11_C0_GHMN;
                    pu16SOSFilterData[1] = S_11_C1_GHMN;
                    pu16SOSFilterData[2] = S_11_C2_GHMN;
                    pu16SOSFilterData[3] = S_11_C3_GHMN;
                    pu16SOSFilterData[4] = S_11_C4_GHMN;

                    pu16SOSFilterData[5] = S_12_C0_GHMN;
                    pu16SOSFilterData[6] = S_12_C1_GHMN;
                    pu16SOSFilterData[7] = S_12_C2_GHMN;
                    pu16SOSFilterData[8] = S_12_C3_GHMN;
                    pu16SOSFilterData[9] = S_12_C4_GHMN;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_I:
                    pu16NotchData[0] = N_A1_C0_I;
                    pu16NotchData[1] = N_A1_C1_I;
                    pu16NotchData[2] = N_A1_C2_I;

                    pu16NotchData[3] = N_A2_C0_I;
                    pu16NotchData[4] = N_A2_C1_I;
                    pu16NotchData[5] = N_A2_C2_I;

                    pu16SOSFilterData[0] = S_11_C0_I;
                    pu16SOSFilterData[1] = S_11_C1_I;
                    pu16SOSFilterData[2] = S_11_C2_I;
                    pu16SOSFilterData[3] = S_11_C3_I;
                    pu16SOSFilterData[4] = S_11_C4_I;

                    pu16SOSFilterData[5] = S_12_C0_I;
                    pu16SOSFilterData[6] = S_12_C1_I;
                    pu16SOSFilterData[7] = S_12_C2_I;
                    pu16SOSFilterData[8] = S_12_C3_I;
                    pu16SOSFilterData[9] = S_12_C4_I;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK1_STEREO_A2:
                    pu16NotchData[0] = N_A1_C0_DK1A2;
                    pu16NotchData[1] = N_A1_C1_DK1A2;
                    pu16NotchData[2] = N_A1_C2_DK1A2;

                    pu16NotchData[3] = N_A2_C0_DK1A2;
                    pu16NotchData[4] = N_A2_C1_DK1A2;
                    pu16NotchData[5] = N_A2_C2_DK1A2;

                    pu16SOSFilterData[0] = S_11_C0_DK1A2;
                    pu16SOSFilterData[1] = S_11_C1_DK1A2;
                    pu16SOSFilterData[2] = S_11_C2_DK1A2;
                    pu16SOSFilterData[3] = S_11_C3_DK1A2;
                    pu16SOSFilterData[4] = S_11_C4_DK1A2;

                    pu16SOSFilterData[5] = S_12_C0_DK1A2;
                    pu16SOSFilterData[6] = S_12_C1_DK1A2;
                    pu16SOSFilterData[7] = S_12_C2_DK1A2;
                    pu16SOSFilterData[8] = S_12_C3_DK1A2;
                    pu16SOSFilterData[9] = S_12_C4_DK1A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK2_STEREO_A2:
                    pu16NotchData[0] = N_A1_C0_DK2A2;
                    pu16NotchData[1] = N_A1_C1_DK2A2;
                    pu16NotchData[2] = N_A1_C2_DK2A2;

                    pu16NotchData[3] = N_A2_C0_DK2A2;
                    pu16NotchData[4] = N_A2_C1_DK2A2;
                    pu16NotchData[5] = N_A2_C2_DK2A2;

                    pu16SOSFilterData[0] = S_11_C0_DK2A2;
                    pu16SOSFilterData[1] = S_11_C1_DK2A2;
                    pu16SOSFilterData[2] = S_11_C2_DK2A2;
                    pu16SOSFilterData[3] = S_11_C3_DK2A2;
                    pu16SOSFilterData[4] = S_11_C4_DK2A2;

                    pu16SOSFilterData[5] = S_12_C0_DK2A2;
                    pu16SOSFilterData[6] = S_12_C1_DK2A2;
                    pu16SOSFilterData[7] = S_12_C2_DK2A2;
                    pu16SOSFilterData[8] = S_12_C3_DK2A2;
                    pu16SOSFilterData[9] = S_12_C4_DK2A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK3_STEREO_A2:
                    pu16NotchData[0] = N_A1_C0_DK3A2;
                    pu16NotchData[1] = N_A1_C1_DK3A2;
                    pu16NotchData[2] = N_A1_C2_DK3A2;

                    pu16NotchData[3] = N_A2_C0_DK3A2;
                    pu16NotchData[4] = N_A2_C1_DK3A2;
                    pu16NotchData[5] = N_A2_C2_DK3A2;

                    pu16SOSFilterData[0] = S_11_C0_DK3A2;
                    pu16SOSFilterData[1] = S_11_C1_DK3A2;
                    pu16SOSFilterData[2] = S_11_C2_DK3A2;
                    pu16SOSFilterData[3] = S_11_C3_DK3A2;
                    pu16SOSFilterData[4] = S_11_C4_DK3A2;

                    pu16SOSFilterData[5] = S_12_C0_DK3A2;
                    pu16SOSFilterData[6] = S_12_C1_DK3A2;
                    pu16SOSFilterData[7] = S_12_C2_DK3A2;
                    pu16SOSFilterData[8] = S_12_C3_DK3A2;
                    pu16SOSFilterData[9] = S_12_C4_DK3A2;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_DK_MONO_NICAM:
                    pu16NotchData[0] = N_A1_C0_DKMN;
                    pu16NotchData[1] = N_A1_C1_DKMN;
                    pu16NotchData[2] = N_A1_C2_DKMN;

                    pu16NotchData[3] = N_A2_C0_DKMN;
                    pu16NotchData[4] = N_A2_C1_DKMN;
                    pu16NotchData[5] = N_A2_C2_DKMN;

                    pu16SOSFilterData[0] = S_11_C0_DKMN;
                    pu16SOSFilterData[1] = S_11_C1_DKMN;
                    pu16SOSFilterData[2] = S_11_C2_DKMN;
                    pu16SOSFilterData[3] = S_11_C3_DKMN;
                    pu16SOSFilterData[4] = S_11_C4_DKMN;

                    pu16SOSFilterData[5] = S_12_C0_DKMN;
                    pu16SOSFilterData[6] = S_12_C1_DKMN;
                    pu16SOSFilterData[7] = S_12_C2_DKMN;
                    pu16SOSFilterData[8] = S_12_C3_DKMN;
                    pu16SOSFilterData[9] = S_12_C4_DKMN;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_L:
                    pu16NotchData[0] = N_A1_C0_L;
                    pu16NotchData[1] = N_A1_C1_L;
                    pu16NotchData[2] = N_A1_C2_L;

                    pu16NotchData[3] = N_A2_C0_L;
                    pu16NotchData[4] = N_A2_C1_L;
                    pu16NotchData[5] = N_A2_C2_L;

                    pu16SOSFilterData[0] = S_11_C0_L;
                    pu16SOSFilterData[1] = S_11_C1_L;
                    pu16SOSFilterData[2] = S_11_C2_L;
                    pu16SOSFilterData[3] = S_11_C3_L;
                    pu16SOSFilterData[4] = S_11_C4_L;

                    pu16SOSFilterData[5] = S_12_C0_L;
                    pu16SOSFilterData[6] = S_12_C1_L;
                    pu16SOSFilterData[7] = S_12_C2_L;
                    pu16SOSFilterData[8] = S_12_C3_L;
                    pu16SOSFilterData[9] = S_12_C4_L;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_LL:
                    pu16NotchData[0] = N_A1_C0_LL;
                    pu16NotchData[1] = N_A1_C1_LL;
                    pu16NotchData[2] = N_A1_C2_LL;

                    pu16NotchData[3] = N_A2_C0_LL;
                    pu16NotchData[4] = N_A2_C1_LL;
                    pu16NotchData[5] = N_A2_C2_LL;

                    pu16SOSFilterData[0] = S_11_C0_LL;
                    pu16SOSFilterData[1] = S_11_C1_LL;
                    pu16SOSFilterData[2] = S_11_C2_LL;
                    pu16SOSFilterData[3] = S_11_C3_LL;
                    pu16SOSFilterData[4] = S_11_C4_LL;

                    pu16SOSFilterData[5] = S_12_C0_LL;
                    pu16SOSFilterData[6] = S_12_C1_LL;
                    pu16SOSFilterData[7] = S_12_C2_LL;
                    pu16SOSFilterData[8] = S_12_C3_LL;
                    pu16SOSFilterData[9] = S_12_C4_LL;
                    break;

                case mapi_vif_datatype::E_VIF_SOUND_MN:
                    pu16NotchData[0] = N_A1_C0_NTSC;
                    pu16NotchData[1] = N_A1_C1_NTSC;
                    pu16NotchData[2] = N_A1_C2_NTSC;

                    pu16NotchData[3] = N_A2_C0_NTSC;
                    pu16NotchData[4] = N_A2_C1_NTSC;
                    pu16NotchData[5] = N_A2_C2_NTSC;

                    pu16SOSFilterData[0] = S_11_C0_NTSC;
                    pu16SOSFilterData[1] = S_11_C1_NTSC;
                    pu16SOSFilterData[2] = S_11_C2_NTSC;
                    pu16SOSFilterData[3] = S_11_C3_NTSC;
                    pu16SOSFilterData[4] = S_11_C4_NTSC;

                    pu16SOSFilterData[5] = S_12_C0_NTSC;
                    pu16SOSFilterData[6] = S_12_C1_NTSC;
                    pu16SOSFilterData[7] = S_12_C2_NTSC;
                    pu16SOSFilterData[8] = S_12_C3_NTSC;
                    pu16SOSFilterData[9] = S_12_C4_NTSC;
                    break;

                default:
                    printf("Warning:%s(),%d\n",__func__,__LINE__);
                    break;
            }
        }
            break;


        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DTV_IF_FREQ:
        {
			printf("~~~~~~~~~~~~~~ rda get DTV if fre:");
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                case E_TUNER_DTV_DVB_T2_MODE:
                case E_TUNER_DTV_DTMB_MODE:
                    *((MAPI_U32 *)pvoidParam3)=5000L;
					printf("5000 Khz\n");
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((MAPI_U32 *)pvoidParam3)=5000L;
					printf("5000 Khz\n");
                    break;
                case E_TUNER_DTV_ATSC_MODE:
                    *((MAPI_U32 *)pvoidParam3)=5000L;
					printf("5000 Khz\n");
                    break;
                case E_TUNER_DTV_ISDB_MODE:
                    *((MAPI_U32 *)pvoidParam3)=5000L;
					printf("5000 Khz\n");
                    break;

                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_IQ_SWAP:
        {
            MAPI_U8 *u8IqSwap = (MAPI_U8 *)pvoidParam3;
            *u8IqSwap = TUNER_DTV_IQ_SWAP;
            if ( u32Param1 )
            {
                *u8IqSwap ^= 0x01;
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_TABLE:
        {
            (*(DMD_SSI_TABLE **)pvoidParam3)=NULL; // if not used, should return NULL;
            return FALSE;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_RF_LEVEL:
        {
            MAPI_U16 level = rdaTVSingalStrength();
			*((MAPI_U16 *)pvoidParam3)=level;
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_DEMOD_CONFIG:
        {
            switch (u32Param1) // demod mode
            {
                case E_TUNER_DTV_DVB_T_MODE:
                    *((MS_U8 **)pvoidParam3)=NULL;
                    break;
                case E_TUNER_DTV_DVB_C_MODE:
                    *((MS_U8 **)pvoidParam3)=NULL;
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;

        case mapi_tuner_datatype::E_TUNER_SUBCMD_GET_PEAKING_PARAMETER:
        {
            mapi_vif_datatype::stVIFUserFilter *VIF_UserFilter = (mapi_vif_datatype::stVIFUserFilter *)pvoidParam3;
            ASSERT(VIF_UserFilter);
            switch (u32Param1)
            {
                case E_RFBAND_VHF_LOW:
                    if((u32Param2==(MAPI_U32)mapi_demodulator_datatype::IF_FREQ_B)||(u32Param2==(MAPI_U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2==(MAPI_U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2==(MAPI_U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                    break;
                case E_RFBAND_VHF_HIGH:
                    if((u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_B) || (u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                    break;
                case E_RFBAND_UHF:
                    if((u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_B) || (u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_G))
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_DK)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_I)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_L)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else if(u32Param2 == (MAPI_U32)mapi_demodulator_datatype::IF_FREQ_L_PRIME)
                    {
                        VIF_UserFilter->VifSos21FilterC0  = VIF_SOS_21_FILTER_C0;
                        VIF_UserFilter->VifSos21FilterC1  = VIF_SOS_21_FILTER_C1;
                        VIF_UserFilter->VifSos21FilterC2  = VIF_SOS_21_FILTER_C2;
                        VIF_UserFilter->VifSos21FilterC3  = VIF_SOS_21_FILTER_C3;
                        VIF_UserFilter->VifSos21FilterC4  = VIF_SOS_21_FILTER_C4;

                        VIF_UserFilter->VifSos22FilterC0  = VIF_SOS_22_FILTER_C0;
                        VIF_UserFilter->VifSos22FilterC1  = VIF_SOS_22_FILTER_C1;
                        VIF_UserFilter->VifSos22FilterC2  = VIF_SOS_22_FILTER_C2;
                        VIF_UserFilter->VifSos22FilterC3  = VIF_SOS_22_FILTER_C3;
                        VIF_UserFilter->VifSos22FilterC4  = VIF_SOS_22_FILTER_C4;

                        VIF_UserFilter->VifSos31FilterC0  = VIF_SOS_31_FILTER_C0;
                        VIF_UserFilter->VifSos31FilterC1  = VIF_SOS_31_FILTER_C1;
                        VIF_UserFilter->VifSos31FilterC2  = VIF_SOS_31_FILTER_C2;
                        VIF_UserFilter->VifSos31FilterC3  = VIF_SOS_31_FILTER_C3;
                        VIF_UserFilter->VifSos31FilterC4  = VIF_SOS_31_FILTER_C4;
                        VIF_UserFilter->VifSos32FilterC0  = VIF_SOS_32_FILTER_C0;
                        VIF_UserFilter->VifSos32FilterC1  = VIF_SOS_32_FILTER_C1;
                        VIF_UserFilter->VifSos32FilterC2  = VIF_SOS_32_FILTER_C2;
                        VIF_UserFilter->VifSos32FilterC3  = VIF_SOS_32_FILTER_C3;
                        VIF_UserFilter->VifSos32FilterC4  = VIF_SOS_32_FILTER_C4;
                    }
                    else
                    {
                        printf("Error:%s(),%d\n",__func__,__LINE__);
                        return FALSE;
                    }
                    break;
                default:
                    printf("Error:%s(),%d\n",__func__,__LINE__);
                    return FALSE;
                    break;
            }
        }
            break;

        default:
            UNUSED(u8SubCmd);
            UNUSED(u32Param1);
            UNUSED(u32Param2);
            UNUSED(pvoidParam3);
            return FALSE;
            break;
    }

    return TRUE;
}
#endif

void devDigitalTuner_SetFreq ( double Freq,  RF_CHANNEL_BANDWIDTH eBandWidth)
{

    BOOLEAN bRet = TRUE;

    DBG_TUNER(printf("[devDigitalTuner_SetFreq]Freq=%d, eBandWidth=%d, m_eMode=%d\n",(U16)Freq,(U8)eBandWidth,(U8)m_eMode);)

    if (m_bDeviceBusy == FALSE)
    {
        // devDigitalTuner_Init should be called first.
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

    // Freq (MHz)
    bRet &= DTV_SetTune(Freq, eBandWidth, m_eMode);

    if (bRet == FALSE)
        printf("[Error]%s,%d\n",__FILE__,__LINE__);

    return;
}

extern IF_FREQ MDrv_IFDM_GetIF(void);
void devTunerSetFreq(U32 u32Freq)
{
    BOOLEAN retb = TRUE;
    IF_FREQ CurrentStandard;
    CurrentStandard= MDrv_IFDM_GetIF();

    if (m_bDeviceBusy == FALSE)
    {
        retb = FALSE;
        printf("[Error]%s,%d\n",__FILE__,__LINE__);
        return;
    }

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
        m_eMode = E_TUNER_ATV_PAL_MODE;
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


//extern  devTuner_Std_set(void);
BOOLEAN devTuner_Std_set(EN_TUNER_MODE eMode, AUDIOSTANDARD_TYPE_ OtherMode)
{
    BOOLEAN bRet = TRUE;
    m_eMode = eMode;
    m_OtherMode = OtherMode;

    DBG_TUNER(printf("devTuner_Std_set, eMode=%d, OtherMode=%d\n",eMode,OtherMode);)

    return bRet;
}



void devTunerInit(void)
{
    if (rdaTVInitial() == false)
    {
        printf("[Error]RDA init fail...\n");
    }
    return;
}


BOOLEAN TunerInit(void)
{
    rdaTVInitial();
    return TRUE;
}

#endif
