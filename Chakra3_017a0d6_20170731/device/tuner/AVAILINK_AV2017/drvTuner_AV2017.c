/*****************************************************************************
*    Airoha DVB-S2 AV2017 Tuner sample code (Mulitple API Version)
*
*    History:
*      	Date         Version    Reason
*
*	  ============	=========	=================
*	1.May.25.2015	 Ver 1.0	Separate different application interfaces
*****************************************************************************/
#include <math.h>
#include "MsCommon.h"
#include "drvIIC.h"
#include "Board.h"
#include "drvTuner_AV2017.h"
#include "msAPI_Demod.h"
#include "msAPI_Tuner.h"

#if (FRONTEND_TUNER_S2_TYPE==AVAILINK_AV2017)

#define  TUNER_AV2017_SLAVE_ID      0xC6
#define  AV2017_DEBUG_LOG(x) //x

static TunerPara AVtuner;
typedef struct
{
    float    LvdBm;
    MS_U16 u16_if_agc;
}S_RSSI_TABLE;

#define RSSI_ARRAY_NUM 30
/*
static S_RSSI_TABLE rssi_AV2017_131x[]=
{//19*10-4 = 186
{-92.5, 0xF253},{-92.0, 0xF1EA},{-91.5, 0xF145},{-91.0, 0xF0C8},{-90.5, 0xF05A},{-90.0, 0xEFE2},{-89.5, 0xEF2E},{-89.0, 0xEEAC},{-88.5, 0xEE34},{-88.0, 0xEDB2},
{-87.5, 0xECFE},{-87.0, 0xEC63},{-86.5, 0xEBE6},{-86.0, 0xEB28},{-85.5, 0xEA92},{-85.0, 0xE9F7},{-84.5, 0xE970},{-84.0, 0xE894},{-83.5, 0xE7E5},{-83.0, 0xE6EB},
{-82.5, 0xE62D},{-82.0, 0xE5A1},{-81.5, 0xE510},{-81.0, 0xE443},{-80.5, 0xE3A8},{-80.0, 0xE303},{-79.5, 0xE236},{-79.0, 0xE1A0},{-78.5, 0xE0EC},{-78.0, 0xE024},
{-77.5, 0xDFB6},{-77.0, 0xDF57},{-76.5, 0xDEF3},{-76.0, 0xDE67},{-75.5, 0xDDF9},{-75.0, 0xDD86},{-74.5, 0xDD2C},{-74.0, 0xDCD2},{-73.5, 0xDC73},{-73.0, 0xDC14},
{-72.5, 0xDBB5},{-72.0, 0xDB38},{-71.5, 0xDA5C},{-71.0, 0xD99E},{-70.5, 0xD8D6},{-70.0, 0xD7E6},{-69.5, 0xD728},{-69.0, 0xD660},{-68.5, 0xD584},{-68.0, 0xD4B2},
{-67.5, 0xD3F4},{-67.0, 0xD32C},{-66.5, 0xD26E},{-66.0, 0xD1C4},{-65.5, 0xD12E},{-65.0, 0xD0A7},{-64.5, 0xD03E},{-64.0, 0xCFD0},{-63.5, 0xCF71},{-63.0, 0xCF12},
{-62.5, 0xCEBD},{-62.0, 0xCE68},{-61.5, 0xCE18},{-61.0, 0xCDC8},{-60.5, 0xCD82},{-60.0, 0xCD37},{-59.5, 0xCCE2},{-59.0, 0xCC9C},{-58.5, 0xCC4C},{-58.0, 0xCBFC},
{-57.5, 0xCBAC},{-57.0, 0xCB5C},{-56.5, 0xCAEE},{-56.0, 0xCA44},{-55.5, 0xC97C},{-55.0, 0xC850},{-54.5, 0xC73D},{-54.0, 0xC670},{-53.5, 0xC5D0},{-53.0, 0xC53F},
{-52.5, 0xC4C2},{-52.0, 0xC445},{-51.5, 0xC3CD},{-51.0, 0xC350},{-50.5, 0xC2DD},{-50.0, 0xC26A},{-49.5, 0xC1DE},{-49.0, 0xC152},{-48.5, 0xC0BC},{-48.0, 0xC021},
{-47.5, 0xBF9A},{-47.0, 0xBF09},{-46.5, 0xBE73},{-46.0, 0xBE05},{-45.5, 0xBD74},{-45.0, 0xBCED},{-44.5, 0xBC70},{-44.0, 0xBBE4},{-43.5, 0xBB7B},{-43.0, 0xBAF9},
{-42.5, 0xBA6D},{-42.0, 0xB9BE},{-41.5, 0xB90A},{-41.0, 0xB838},{-40.5, 0xB77F},{-40.0, 0xB6DF},{-39.5, 0xB635},{-39.0, 0xB568},{-38.5, 0xB4C8},{-38.0, 0xB43C},
{-37.5, 0xB3C4},{-37.0, 0xB333},{-36.5, 0xB2B6},{-36.0, 0xB239},{-35.5, 0xB1A8},{-35.0, 0xB12B},{-34.5, 0xB09F},{-34.0, 0xB022},{-33.5, 0xAFA5},{-33.0, 0xAF28},
{-32.5, 0xAEB0},{-32.0, 0xAE42},{-31.5, 0xADD9},{-31.0, 0xAD75},{-30.5, 0xAD02},{-30.0, 0xAC80},{-29.5, 0xABFE},{-29.0, 0xAB77},{-28.5, 0xAB04},{-28.0, 0xAA87},
{-27.5, 0xAA1E},{-27.0, 0xA9BF},{-26.5, 0xA965},{-26.0, 0xA91A},{-25.5, 0xA8A2},{-25.0, 0xA820},{-24.5, 0xA7B2},{-24.0, 0xA753},{-23.5, 0xA6DB},{-23.0, 0xA64F},
{-22.5, 0xA5D7},{-22.0, 0xA564},{-21.5, 0xA4E7},{-21.0, 0xA82F},{-20.5, 0xA3B6},{-20.0, 0xA2F8},{-19.5, 0xA24E},{-19.0, 0xA1C7},{-18.5, 0xA145},{-18.0, 0xA096},
{-17.5, 0xA00A},{-17.0, 0x9F83},{-16.5, 0x9ED4},{-16.0, 0x9E4D},{-15.5, 0x9DD0},{-15.0, 0x9CEA},{-14.5, 0x9C72},{-14.0, 0x9BFA},{-13.5, 0x9B6E},{-13.0, 0x9ACE},
{-12.5, 0x9A60},{-12.0, 0x9A0B},{-11.5, 0x99A2},{-11.0, 0x992F},{-10.5, 0x98D0},{-10.0, 0x9871},{-9.5, 0x982B},{-9.0, 0x97D6},{-8.5, 0x9772},{-8.0, 0x9722},
{-7.5, 0x96E1},{-7.0, 0x96A5},{-6.5, 0x965A},{-6.0, 0x960A},{-5.5, 0x95B5},{-5.0, 0x9560},{-4.5, 0x951F},{-4.0, 0x94E3},{-3.5, 0x94A2},{-3.0, 0x9452},
{-2.5, 0x93F8},{-2.0, 0x939E},{-1.5, 0x934E},{-1.0, 0x9312},{-0.5, 0x92D1},{-0.0, 0x9286}
};
*/
static S_RSSI_TABLE rssi_AV2017_1240[]=
{
{-95.0,0xFF00},
{-90.0,0xFF00},
{-85.0,0x8B5C},
{-80.0,0x81DC},
{-75.0,0x7D44},
{-70.0,0x7B88},
{-65.0,0x770F},
{-60.0,0x74FB},
{-55.0,0x7256},
{-50.0,0x6C8F},
{-45.0,0x6986},
{-40.0,0x6753},
{-35.0,0x64E6},
{-30.0,0x6295},
{-25.0,0x606E},
{-20.0,0x5E5B},
{-15.0,0x5BF8},
{-10.0,0x5A1F},
{- 5.0,0x5971},
{- 0.0,0x591D},
};

/***Tuner Control Functions********************************************************************/
static TUNER_ErrorCode Tuner_Parameter_Initial (pTunerPara pAVtuner);
static TUNER_ErrorCode Tuner_Register_Initial (pTunerPara pAVtuner);
static TUNER_ErrorCode Tuner_Set_Channel_Frequency (pTunerPara pAVtuner, MS_U32 channel_freq_mhz);
static TUNER_ErrorCode Tuner_Set_Filter_Bandwith (pTunerPara pAVtuner, MS_U32 filter_BW_khz);
static TUNER_ErrorCode Tuner_Set_RFLP_PD (pTunerPara pAVtuner);
static TUNER_ErrorCode Tuner_Set_Fine_Tune (pTunerPara pAVtuner);
//static TUNER_ErrorCode Tuner_Set_RXout_PGA (pTunerPara pAVtuner);
static TUNER_ErrorCode Tuner_Get_Channel_Lock (pTunerPara pAVtuner);
static TUNER_ErrorCode Tuner_Get_Filter_Lock (pTunerPara pAVtuner);

/***Customer define Functions********************************************************************/
static TUNER_ErrorCode Tuner_I2C_Write (pTunerPara pAVtuner, MS_U8 reg_start, MS_U8* buff, MS_U8 length);
static TUNER_ErrorCode Tuner_I2C_Read (pTunerPara pAVtuner, MS_U8 reg_start, MS_U8* buff, MS_U8 length);
static TUNER_ErrorCode Time_DELAY_MS (MS_U32 ms);

void AV2017_SlaveID_Check(pTunerPara pAVtuner)
{

#if 1
     MS_U8 regValue;

      pAVtuner->I2C_ADDR      = (TUNER_I2C_ADDRESS)0xC0;
      do
      {
          regValue=(char) (0x38);

          if(Tuner_I2C_Write (pAVtuner, 0, &regValue, 1) == Tuner_No_Error)
          {
               regValue = 0;
               if(Tuner_I2C_Read (pAVtuner, 0, &regValue, 1) == Tuner_No_Error)
               {
                     if(regValue == 0x38)
                     {
                         break;
                     }
               }
          }
          pAVtuner->I2C_ADDR =(TUNER_I2C_ADDRESS)(pAVtuner->I2C_ADDR+0x02);
      } while(pAVtuner->I2C_ADDR <= 0xC6);
      if(pAVtuner->I2C_ADDR > 0xC6)
      {
           pAVtuner->I2C_ADDR = (TUNER_I2C_ADDRESS)TUNER_AV2017_SLAVE_ID;
      }
#else
      pAVtuner->I2C_ADDR = (TUNER_I2C_ADDRESS)TUNER_AV2017_SLAVE_ID;

#endif
      AV2017_DEBUG_LOG(printf("\r\n DVBS TUNER SLAVE ID = %x", pAVtuner->I2C_ADDR);)
}

MS_BOOL MDrv_Tuner_Initial(void)
{
    return MDrv_DVBS_Tuner_Initial();
}
MS_BOOL MDrv_Tuner_SetFreq(MS_U16 u16CenterFreqMHz, MS_U32 u32SymbolRate_kHz)
{
    return MDrv_DVBS_Tuner_SetFreq(u16CenterFreqMHz, u32SymbolRate_kHz);
}
MS_BOOL MDrv_Tuner_CheckLock(void)
{
    return MDrv_DVBS_Tuner_CheckLock();
}

MS_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks)
{
    bool bRet = true;
    TUNER_ErrorCode error_code = Tuner_No_Error;

	error_code = Tuner_Set_Channel_Frequency (&AVtuner, (MS_U32)u16CenterFreq_MHz*1000);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Set_Channel_Frequency fail, error_code=%d\n",error_code);
        bRet = false;
    }
	error_code = Tuner_Set_Filter_Bandwith (&AVtuner, u32SymbolRate_Ks);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Set_Filter_Bandwith fail, error_code=%d\n",error_code);
        bRet = false;
    }
	AVtuner.RFLP_EN = RFLP_ON;
	error_code = Tuner_Set_RFLP_PD (&AVtuner);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Set_RFLP_PD fail, error_code=%d\n",error_code);
        bRet = false;
    }

    if (bRet == false)
    {
        printf("AIROHA_AV2017_ConfigTuner fail\n");
    }

    return bRet;
}
MS_BOOL MDrv_DVBS_Tuner_Initial(void)
{
    bool bRet = true;
    TUNER_ErrorCode error_code = Tuner_No_Error;

    error_code = Tuner_Parameter_Initial (&AVtuner);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Parameter_Initial fail, error_code=%d\n",error_code);
        bRet = false;
    }

    AV2017_SlaveID_Check(&AVtuner);


	error_code = Tuner_Register_Initial (&AVtuner);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Register_Initial fail, error_code=%d\n",error_code);
        bRet = false;
    }

    if(bRet==false)
    {
        printf("AIROHA_AV2017_init fail\n");
    }

    return bRet;
}
MS_BOOL MDrv_DVBS_Tuner_CheckLock(void)
{
    bool bRet = true;
    TUNER_ErrorCode error_code = Tuner_No_Error;

    error_code = Tuner_Get_Channel_Lock (&AVtuner);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Get_Channel_Lock fail, error_code=%d\n",error_code);
        bRet = false;
    }
    error_code = Tuner_Get_Filter_Lock (&AVtuner);
    if (error_code != Tuner_No_Error)
    {
        printf("Tuner_Get_Filter_Lock fail, error_code=%d\n",error_code);
        bRet = false;
    }
    return bRet;
}
// input IF_AGC,
// return dBm.
float MDrv_DVBS_Tuner_Get_RSSI(MS_U16 u16_gain)
{
    MS_U8 indx = 0;
    MS_U8 arry_size = 0;
    float rf_dbm = 0.0;
    S_RSSI_TABLE *rssi_AV2017;

#if 1  //demod 1240
    arry_size = sizeof(rssi_AV2017_1240)/sizeof(S_RSSI_TABLE);
    rssi_AV2017 = rssi_AV2017_1240;
#else  //demod 131x
    arry_size = sizeof(rssi_AV2017_131x)/sizeof(S_RSSI_TABLE);
    rssi_AV2017 = rssi_AV2017_131x;
#endif


    // printf("array_size = %d, gain=0x%x\n",arry_size,u16_gain);
    if (u16_gain > rssi_AV2017[0].u16_if_agc)
    {
        rf_dbm = (float)(u16_gain - rssi_AV2017[1].u16_if_agc)/(float)(rssi_AV2017[0].u16_if_agc - rssi_AV2017[1].u16_if_agc)*(rssi_AV2017[0].LvdBm - rssi_AV2017[1].LvdBm)+rssi_AV2017[1].LvdBm;
    }
    else if (u16_gain <= rssi_AV2017[arry_size-1].u16_if_agc)
    {
        rf_dbm = (float)(u16_gain - rssi_AV2017[arry_size-2].u16_if_agc)/(float)(rssi_AV2017[arry_size-1].u16_if_agc - rssi_AV2017[arry_size-2].u16_if_agc)*(rssi_AV2017[arry_size-1].LvdBm - rssi_AV2017[arry_size-2].LvdBm)+rssi_AV2017[arry_size-2].LvdBm;
    }
    else
    {
        for(indx = 0;indx<arry_size;indx++)
        {
            if (u16_gain > rssi_AV2017[indx].u16_if_agc) break;
        }
        if(indx < arry_size)
        {
            rf_dbm = (float)(u16_gain - rssi_AV2017[indx].u16_if_agc)/(float)(rssi_AV2017[indx-1].u16_if_agc - rssi_AV2017[indx].u16_if_agc)*(rssi_AV2017[indx-1].LvdBm - rssi_AV2017[indx].LvdBm)+rssi_AV2017[indx].LvdBm;
        }
    }

    AV2017_DEBUG_LOG(printf("gain=0x%x,rf_dbm=%f, indx=%d, arry_size=%d\n",u16_gain,rf_dbm,indx,arry_size);)

    return rf_dbm;
}

/*******************************************************************
* Tuner parameter initialization:
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description: Initialize all the parameters in the data structure of pAVtuner
********************************************************************/
static TUNER_ErrorCode Tuner_Parameter_Initial (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;

	pAVtuner->crystal_khz   = 27000;				// (Unit: KHz)Tuner_crystal

	pAVtuner->I2C_ADDR      = ADDR1_H_ADDR0_H;	// Tuner I2C address at write mode
	pAVtuner->IQmode	    = Differential;     // IQ_MODE
	pAVtuner->PGA_Gain      = PGA_1_5dB ;		// PGA_GAIN
	pAVtuner->PGA_Current   = PGA_1_5mA ;		// PGA_DRIVE_CURRENT
	pAVtuner->XO_Current    = HIGH_AV2017;             // XO_DRIVE_CURRENT
	pAVtuner->XO_EN		    = XO_ON;			// XO_ENABLE Setting
    pAVtuner->RFLP_EN       = RFLP_OFF;			// RFLP_ENABLE Setting
	pAVtuner->PD_EN         = Wake_Up;			// SOFTWARE_POWERDOWN
	pAVtuner->FT            = FT_ON;				// TUNER_Fine_Tune
	pAVtuner->blind_scan    = 0;					// blind_scan

	return result;
}

/*******************************************************************************
* Tuner Power-ON registers initialization
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description: Initialize all registers of the Tuner
********************************************************************************/
static TUNER_ErrorCode Tuner_Register_Initial (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 reg[50];

	reg[0]= 0x50; //2150M
	reg[1]= 0xA1; //2150M
	reg[2]= 0x2F; //2150M
	reg[3]= 0x50; //2150M
	reg[4]= 0x1f;
	reg[5]= 0xa3;
	reg[6]= 0xfd;
	reg[7]= 0x58;
	reg[8]= (0x04)|(pAVtuner->PGA_Gain <<3)|(pAVtuner->PGA_Current);

	if( pAVtuner->crystal_khz < 25000 )
       reg[9]= (0x00)|(pAVtuner->XO_Current<<6); // ctrl_clk Divider=/1
	else
	   reg[9]= (0x02)|(pAVtuner->XO_Current<<6); // ctrl_clk Divider=/2

	reg[10]= 0x88;
	reg[11]= 0xb4;
	reg[12]= (0x16)|(pAVtuner->XO_EN <<7)|(pAVtuner->RFLP_EN <<6)|(pAVtuner->PD_EN <<5);
	reg[13]= 0x40;
	reg[14]= 0x94;
	reg[15]= 0x4a;
	reg[16]= 0x66;
	reg[17]= 0x40;
	reg[18]= 0x80;
	reg[19]= 0x2b;
	reg[20]= 0x6a;
	reg[21]= 0x50;
	reg[22]= 0x91;
	reg[23]= 0x27;
	reg[24]= 0x8f;
	reg[25]= 0xcc;
	reg[26]= 0x21;
	reg[27]= 0x10;
	reg[28]= 0x80;
	reg[29]= 0xE2;
	reg[30]= 0xf5;
	reg[31]= 0x7f;
	reg[32]= 0x4a;
	reg[33]= 0x9b;
	reg[34]= 0xe0;
	reg[35]= 0xe0;
	reg[36]= 0x36;
	reg[37]= (MS_U8)(pAVtuner->FT);
	reg[38]= 0xab;
	reg[39]= 0x97;
	reg[40]= 0xc5;
	reg[41]= 0xa8;

	/* Sequence 1*/
	/* Send Reg0 ->Reg11*/
	result = Tuner_I2C_Write(pAVtuner,0,reg,12);
	if(result!=Tuner_No_Error){ return result; }

	/* Sequence 2*/
	/* Send Reg13 ->Reg24*/
	result = Tuner_I2C_Write(pAVtuner,13,reg+13,12);
	if(result!=Tuner_No_Error){ return result; }

  	/* Send Reg25 ->Reg35*/
	result = Tuner_I2C_Write(pAVtuner,25,reg+25,11);
	if(result!=Tuner_No_Error){ return result; }

	/* Send Reg36 ->Reg41*/
	result = Tuner_I2C_Write(pAVtuner,36,reg+36,6);
	if(result!=Tuner_No_Error){ return result; }

    /* Sequence 3*/
	/* Send reg12*/
	result = Tuner_I2C_Write(pAVtuner,12,reg+12,1);
	if(result!=Tuner_No_Error){ return result; }

	/* Time delay ms*/
	Time_DELAY_MS(100);
	/*Reinitial again*/
	{
		/* Sequence 1*/
		/* Send Reg0 ->Reg11*/
		result = Tuner_I2C_Write(pAVtuner,0,reg,12);
		if(result!=Tuner_No_Error){ return result; }

		/* Sequence 2*/
		/* Send Reg13 ->Reg24*/
		result = Tuner_I2C_Write(pAVtuner,13,reg+13,12);
		if(result!=Tuner_No_Error){ return result; }

		/* Send Reg25 ->Reg35*/
		result = Tuner_I2C_Write(pAVtuner,25,reg+25,11);
		if(result!=Tuner_No_Error){ return result; }

		/* Send Reg36 ->Reg41*/
		result = Tuner_I2C_Write(pAVtuner,36,reg+36,6);
		if(result!=Tuner_No_Error){ return result; }

 		/* Sequence 3*/
 		/* Send reg12*/
 		result = Tuner_I2C_Write(pAVtuner,12,reg+12,1);
	}
 	/* Time delay ms*/
	Time_DELAY_MS(5);
	return result;
}

/*********************************************************************************
* Channel frequency setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Paramter2:    MS_U32 : channel frequency (unit: MHz)
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. Send reg3,2,1,0 to set tuner at the channel frequency.
*    reg0 is int<7:0>; reg1 is frac<16:9>; reg2 is frac<8:1>; reg3_D7 is frac<0>
*	 For Tuner model name =1, reg3_D2 is IQ mode selection.
* 2. If XO is not default 27MHz, need to manually select VCO Divider.
*    The VCO Divider switching point is freqency=1167.75MHz,
*    and send Reg16 before Reg0~3
**********************************************************************************/
static TUNER_ErrorCode Tuner_Set_Channel_Frequency (pTunerPara pAVtuner, MS_U32 channel_freq_khz)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 reg0;
	MS_U8 reg1;
	MS_U8 reg2;
	MS_U8 reg3;
	MS_U8 reg16;
	MS_U8 reg30;
	MS_U32 fracN;
	MS_U32 XO_khz;

	XO_khz = pAVtuner->crystal_khz;

    if((channel_freq_khz%XO_khz) > (XO_khz-501))
    {
		  channel_freq_khz /= 1000;
		  channel_freq_khz *= 1000;
		  channel_freq_khz += 1000;
    }
	else if((channel_freq_khz%XO_khz) < 500)
    {
		  channel_freq_khz /= 1000;
		  channel_freq_khz *= 1000;
	}
	else
	{}

	if( XO_khz != 27000 )
    {
		if(channel_freq_khz > 1167750)
           reg16 = 0x56; // VCO Divider=/2
        else
           reg16 = 0x46; // VCO Divider=/4

	    /* Send Reg16*/
        result=Tuner_I2C_Write(pAVtuner,16,&reg16,1);
		if(result!=Tuner_No_Error){ return result; }
    }

	fracN = (channel_freq_khz + XO_khz/2)/XO_khz;
	if(fracN > 0xff)
  	   fracN = 0xff;
    reg0=(MS_U8) (fracN & 0xff);
  	fracN = ((channel_freq_khz/100)<<17)/(XO_khz/100);
  	fracN = fracN & 0x1ffff;
  	reg1=(MS_U8) ((fracN>>9)&0xff);
  	reg2=(MS_U8) ((fracN>>1)&0xff);

  	reg3= (0x50)|(fracN<<7)|(pAVtuner->IQmode<<2);
    /* Sequence 4*/

	/* Send Reg3*/
    result = Tuner_I2C_Write(pAVtuner,3,&reg3,1);
	if(result!=Tuner_No_Error){ return result; }
	/* Send Reg2*/
    result = Tuner_I2C_Write(pAVtuner,2,&reg2,1);
	if(result!=Tuner_No_Error){ return result; }
	/* Send Reg1*/
    result = Tuner_I2C_Write(pAVtuner,1,&reg1,1);
	if(result!=Tuner_No_Error){ return result; }
	/* Send Reg0*/
    result = Tuner_I2C_Write(pAVtuner,0,&reg0,1);
    /* Time delay ms*/

	Time_DELAY_MS(100);

    /* Send Reg3*/
    result = Tuner_I2C_Write(pAVtuner,3,&reg3,1);
	if(result!=Tuner_No_Error){ return result; }
	/* Send Reg2*/
    result = Tuner_I2C_Write(pAVtuner,2,&reg2,1);
	if(result!=Tuner_No_Error){ return result; }
	/* Send Reg1*/
    result = Tuner_I2C_Write(pAVtuner,1,&reg1,1);
	if(result!=Tuner_No_Error){ return result; }
	/* Send Reg0*/
    result = Tuner_I2C_Write(pAVtuner,0,&reg0,1);
    /* Time delay ms*/

	Time_DELAY_MS(4);

	if( (channel_freq_khz%XO_khz)==0)
	{
		reg30 = 0xe5;
	}
	else
	{
		reg30 = 0xf5;
	}
	result = Tuner_I2C_Write(pAVtuner,30,&reg30,1);
	if(result!=Tuner_No_Error){ return result; }

	Time_DELAY_MS(4);

	return result;
}

/*********************************************************************************
* ZIF low pass filter bandwidth setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Paramter2:    MS_U32 : LPF bandwidth (unit: kHz)
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. Calculate the filter reference clk from XO. Transfer Filter BW setting to register5
* 2. Add Fine-tune function after Bandwidth setting.
**********************************************************************************/
static TUNER_ErrorCode Tuner_Set_Filter_Bandwith (pTunerPara pAVtuner, MS_U32 filter_BW_khz)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U32 ctrl_clk_khz;
	MS_U32 BW_CLK_khz;
	MS_U32 XO_khz;
	MS_U32 filter_khz;
	MS_U32 BF;
	MS_U8 reg5;

	XO_khz = pAVtuner->crystal_khz;
	filter_khz = filter_BW_khz;
	if( XO_khz < 25000 )
        ctrl_clk_khz = XO_khz;
	else
	    ctrl_clk_khz = XO_khz/2;
	/* Filter Bandwidth reference CLK calculation */
	BW_CLK_khz = (ctrl_clk_khz +64/2)/64;
	/* BF = filter_BW (KHz) * 1.27 / BW_CLK (KHz)*/
    BF = (filter_khz*127 + 100*BW_CLK_khz/2)/(100*BW_CLK_khz);
	if(BF > 0xff)
  	   BF = 0xff;
	reg5 = (MS_U8)BF;
    /* Sequence 5*/
    /* Send Reg5*/
    result = Tuner_I2C_Write(pAVtuner,5, &reg5, 1);
	if(result!=Tuner_No_Error){ return result; }
    /* Time delay ms*/
    Time_DELAY_MS(4);

	/* Reset FT after Filter BW setting */
	if (pAVtuner->blind_scan == 1)
	{
	    /* choose one for different blind scan mechanism */
		// pAVtuner->FT = FT_OFF;
	    // pAVtuner->FT = FT_Hold;
		pAVtuner->FT = FT_ON;
	}
	else
	{
		pAVtuner->FT = FT_Delay_ON;
	}
	result = Tuner_Set_Fine_Tune (pAVtuner);
	if(result!=Tuner_No_Error){ return result; }

	return result;
}

/*********************************************************************************
* Fine-tune function setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. Fine-tune the gain for sensitivity and linearity.
*    reg[37]_D2 is FT_block,Tp=12ms. reg[37]_D1 is FT_EN. reg[37]_D0 is FT_hold.
* 2. FT_OFF      = 0x00  : FT_block=0, FT_EN=0, FT_hold=0. The Gain is at best sensitivity gain.
* 3. FT_ON       = 0x02  : FT_block=0, FT_EN=1, FT_hold=0. Turn on to fine-tuned gain continuously between sensitivity and linearity.
* 4. FT_Hold     = 0x03  : FT_block=0, FT_EN=1, FT_hold=1. Stop fine-tuning the gain and hold the current fine-tuned gain
* 5. FT_Delay_ON = 0x06	 : FT_block=1, FT_EN=1, FT_hold=0. FT_block=1 trigger the FT hardware delay.
*    After the  delay time 12ms, Fine-tune Function is turned on. And,the chip hardware resets FT_block=1 to FT_block=0 internally.
*    Then, FT function is continuously fine-tuning the gain by the voltage level of pin RFAGC
* 6. Fint-tune function take a reference to RFAGC voltage level of Hardware Pin5.
*	 When Fine-tune is enable, make sure the RFAGC do not have a sharp jump that cause a longer AGC settling time.
***********************************************************************************/
static TUNER_ErrorCode Tuner_Set_Fine_Tune (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U32 pre_delay;
	MS_U32 post_delay;
	MS_U8 reg37;

	switch ( pAVtuner->FT )
	{
        case  FT_ON:{
				pre_delay  = 1;
				post_delay = 5;
				break;}
        case  FT_Hold:{
				pre_delay  = 10;
				post_delay = 1;
				break;}
		case  FT_Delay_ON:{
				pre_delay  = 1;
				post_delay = 15;
				break;}
        default:{ //OFF
				pre_delay  = 1;
				post_delay = 1;}
	}

	reg37 = pAVtuner->FT;
	/* Time delay ms*/
	Time_DELAY_MS(pre_delay);
    /* Send Fine-tune Function Control*/
	result = Tuner_I2C_Write(pAVtuner,37, &reg37, 1);
	/* Time delay ms*/
	Time_DELAY_MS(post_delay);
	return result;
}

/*********************************************************************************
* Loopthrough and power-down setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[12]_D7 is xocore_ena. Enable/disable XO section
* 2. reg[12]_D6 is RFLP_ena.   Enable/disable Loop-through section
* 3. reg[12]_D5 is PD_soft.	   Power ON/OFF Receiver,Synthesizer,VCO section
* 4. For tuner model name =1, hardware Power-down is controled by Hardware Pin13, which turn off Receiver,Synthesizer,VCO,XO,Control section.
*	 For tuner model name =1, make sure Pin13 is at low when sending registers.
**********************************************************************************/
static TUNER_ErrorCode Tuner_Set_RFLP_PD (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 reg12;

	reg12 = (0x16)|( pAVtuner->XO_EN <<7)|(pAVtuner->RFLP_EN <<6)|(pAVtuner->PD_EN <<5);

	result = Tuner_I2C_Write(pAVtuner,12, &reg12, 1);
   	/* Time delay ms*/
	Time_DELAY_MS(5);
	return result;
}

/*********************************************************************************
* RX output baseband programmable gain amplifier setting
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[8]_D6~D3 is gc. PGA gain setting
* 2. reg[8]_D1~0  is PGAout_cs. PGA output driving current setting
**********************************************************************************/
#if 0
static TUNER_ErrorCode Tuner_Set_RXout_PGA (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 reg8;

	reg8 = (0x04)|(pAVtuner->PGA_Gain <<3)|(pAVtuner->PGA_Current);

	result = Tuner_I2C_Write(pAVtuner,8, &reg8, 1);
	return result;
}
#endif

/*********************************************************************************
* Channel lock status
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[11]_D0 is CHLF. Read-only bit. Lock=1. Unlock=0.
**********************************************************************************/
TUNER_ErrorCode Tuner_Get_Channel_Lock (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 reg11;
	MS_U8 lock;

	Tuner_I2C_Read (pAVtuner, 11, &reg11, 1);
	lock = reg11 &0x01;
	if ( lock != 1)
		result = PLL_Lock_Error;
	return result;
}

/*********************************************************************************
* Filter bandwidth lock status
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. reg[11]_D1 is BWLF. Read-only bit. Lock=1. Unlock=0.
**********************************************************************************/
static TUNER_ErrorCode Tuner_Get_Filter_Lock (pTunerPara pAVtuner)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 reg11;
	MS_U8 lock;

	Tuner_I2C_Read (pAVtuner, 11, &reg11, 1);
	lock = (reg11>>1) &0x01;
	if ( lock != 1)
		result = Filter_Lock_Error;
	return result;
}

/*********************************************************************************
* Tuner IIC interface writting function
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Paramter2:    MS_U8      : register start address
* Paramter3:    MS_U8*     : pointer of sending register data buffer
* Paramter4:    MS_U8      : the length of sending register data
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. User define
**********************************************************************************/
static TUNER_ErrorCode Tuner_I2C_Write (pTunerPara pAVtuner, MS_U8 reg_start, MS_U8* buff, MS_U8 length)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 queue[16];
	MS_U8 i;

	queue[0]=pAVtuner->I2C_ADDR; // I2C write address
	queue[1]=reg_start;         // register start address

	for (i=0;i<length;i++)
	{
		queue[2+i]= buff[i];
	}

    if(MDrv_IIC_WriteBytes((U16)((DVBS_TUNER_IIC_BUS<<8)|queue[0]), 0, queue+1, (U16)length+1,queue+1) == false)
    {
        printf("\nTuner IIC WFail");
        result = I2C_Error;
    }

	AV2017_DEBUG_LOG(printf("I2C write queue");)
	for (i=0;i<length+2;i++)
	{
		AV2017_DEBUG_LOG(printf("_%02x_", queue[i]);)
	}
	AV2017_DEBUG_LOG(printf("\n");)

	return result;
}

/*********************************************************************************
* Tuner IIC interface reading function
* Paramter1:    pTunerPara : pointer of Tuner parameter structure
* Paramter2:    MS_U8      : register start address
* Paramter3:    MS_U8*     : pointer of reading register data buffer
* Paramter4:    MS_U8      : the length of reading register data
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. User define
**********************************************************************************/
static TUNER_ErrorCode Tuner_I2C_Read (pTunerPara pAVtuner, MS_U8 reg_start, MS_U8* buff, MS_U8 length)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MS_U8 queue[16];
	MS_U8 i;

	queue[0]=pAVtuner->I2C_ADDR; // I2C write address
	queue[1]=reg_start;			// register start address
	queue[2]=pAVtuner->I2C_ADDR | 0x01; // I2C read address

    if(MDrv_IIC_WriteBytes((U16)((DVBS_TUNER_IIC_BUS<<8)|queue[0]), 0, queue+1, 1,queue+1) == false)
    {
        result = I2C_Error;
        printf("\nTuner_IIC write  fail\n");
    }

    if(MDrv_IIC_ReadBytes((U16)((DVBS_TUNER_IIC_BUS<<8)|queue[0]), 0, queue+1,(U16)length,queue+3) == false)
    {
        result = I2C_Error;
        printf("\nTuner_IIC read  fail\n");
    }

	AV2017_DEBUG_LOG(printf("I2C read queue");)
	for (i=0;i<length+3;i++)
	{
        AV2017_DEBUG_LOG(printf("_%02x_", queue[i]);)
	}
	AV2017_DEBUG_LOG(printf("\n");)

	for (i=0;i<length;i++)
	{
		buff[i] = queue[3+i];
	}

	return result;
}

/*********************************************************************************
* Time delay function
* Paramter1:    MS_U32     : delay time. Unit is millisecond
* Return value: TUNER_ErrorCode : error code of definition
* Description:
* 1. User define
**********************************************************************************/
static TUNER_ErrorCode Time_DELAY_MS (MS_U32 ms)
{
	TUNER_ErrorCode result = Tuner_No_Error;
	MsOS_DelayTask(ms);
	AV2017_DEBUG_LOG(printf("Time dalay %02d ms\n",ms);)
	return result;
}


#endif
