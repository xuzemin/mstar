/***************************************************************************************
*
*			(c) Copyright 2008, LegendSilicon, beijing, China
*
*				         All Rights Reserved
*
* Description :
*
* Notice:
*
***************************************************************************************/

#include "LGS_9X.h"

UINT8 g_AdType = 0;

LGS_RESULT LGS_WriteRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 regVal)
{
    if( MDrv_IIC_WriteByte( slaveAddr, regAddr, regVal ) == FALSE )
    {
        return LGS_I2C_OPEN_ERROR;
    }
    return LGS_NO_ERROR;
}

LGS_RESULT LGS_ReadRegister(UINT8 slaveAddr, UINT8 regAddr, UINT8 *pregVal)
{
    if(MDrv_IIC_ReadByte( slaveAddr, regAddr, pregVal ) == FALSE  )
    {
        return LGS_I2C_OPEN_ERROR;
    }
    return LGS_NO_ERROR;
}
static void LGS_Wait(U32 delay_cnt)
{
    //MDrv_Timer_Delayms(delay_cnt);
    MsOS_DelayTask(delay_cnt);
	//MApp_ProcessUserInput();
}
LGS_RESULT LGS_RegisterSetBit(UINT8 secAddr, UINT8 regAddr, UINT8 bitflg)
{
	UINT8		dat;
	LGS_RESULT	err = LGS_NO_ERROR;

	if (LGS_ReadRegister( secAddr, regAddr, &dat )) goto failed;
	dat |= bitflg;
	if (LGS_WriteRegister( secAddr, regAddr, dat )) goto failed;

failed:
	return err;
}

LGS_RESULT LGS_RegisterClrBit(UINT8 secAddr, UINT8 regAddr, UINT8 bitflg)
{
	UINT8		dat;
	LGS_RESULT	err = LGS_NO_ERROR;

	if (LGS_ReadRegister( secAddr, regAddr, &dat )) goto failed;
	dat &= ~(bitflg);
	if (LGS_WriteRegister( secAddr, regAddr, dat )) goto failed;

failed:
	return err;
}


LGS_RESULT LGS_WaitForLock(UINT8 secAddr, UINT8 regAddr, UINT8 mask, UINT8 val, UINT8 interval,UINT8 times ,UINT8 *real_times)
{
	UINT8	i = 0;
	UINT8	tmp;

	for( i=0; i<times; i++ )
	{
		LGS_Wait(interval);
		LGS_ReadRegister(secAddr, regAddr, &tmp);

		if ( (tmp & mask) == val )
		{
			*real_times = i;
			return LGS_NO_ERROR;
		}
	}
	*real_times = i;
	return LGS_TIMEOUT_ERROR;
}

LGS_RESULT LGS9X_Init(DemodInitPara *para)
{
	double		dAfc = 0.0;
	double		dSymbolRate = 0.0;
	int			i;
	UINT32		u32Afc = 0;
	UINT32		u32SymbolRate = 0;
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		addr = LGS9XSECADDR1;
	UINT8		data = 0x0;
	UINT8		reg_03 = 0x0;
	UINT8		reg_07 = 0x0;
	UINT8		reg_08 = 0x0;
	UINT8		reg_09 = 0x0;
	UINT8		reg_0A = 0x0;
	UINT8		reg_0B = 0x0;
	UINT8		reg_10 = 0x0;
	UINT8		reg_11 = 0x0;
	UINT8		reg_12 = 0x0;
	UINT8		reg_1C = 0x0;
	UINT8		reg_30 = 0x0;
	UINT8		reg_31 = 0x0;
	UINT8		reg_D6 = 0x80;

	if (g_AdType == 1)
	{
		reg_03 = 0x80;		//extern ADC
		reg_07 = 0x02;		//extern ADC output two¡¯s-complement
	}
	
	if (para == NULL)
	{
		printf("HYQ errinit NULL");
		return LGS_PARA_ERROR;
	}

	if (para->workMode >= DEMOD_WORK_MODE_INVALID)
	{
		printf("HYQ errinit WORK_MODE_INVALID");
		return LGS_PARA_ERROR;
	}

	if (para->tsOutputType >= TS_Output_INVALID)
	{		
		printf("HYQ errinit TS_Output_INVALID");
		return LGS_PARA_ERROR;
	}

	if ((para->workMode == DEMOD_WORK_MODE_ANT1_DVBC) ||
		(para->workMode == DEMOD_WORK_MODE_ANT2_DVBC) ||
		(para->workMode == DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC) ||
		(para->workMode == DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB))
	{
		if (para->dvbcQam >= QAM_INVALID)
		{
					printf("HYQ errinit QAM_INVALID");
			return LGS_PARA_ERROR;
		}

		if (para->dvbcIFPolarity >= 3)
		{
			printf("HYQ errinit dvbcIFPolarity err");
			return LGS_PARA_ERROR;
		}

		if ((para->dvbcSymbolRate == 0.0) || (para->dvbcSymbolRate > 7.6))
		{
			printf("HYQ errinit dvbcSymbolRate err");
			return LGS_PARA_ERROR;
		}

	}

	//Disable Firmware
	err = LGS_ReadRegister(addr, 0x39, &data);	if(err) goto failed;
	data &= 0xF1;
	err = LGS_WriteRegister(addr, 0x39, data);	if(err) goto failed;

	if (para->IF >= 4.0 && para->IF <= 10.0)
	{
		reg_07 |= 0x15;

		dAfc = 65536.0 / 30.4 * 65536.0 * para->IF;
		u32Afc = (UINT32)dAfc;
		reg_08 = (UINT8)(u32Afc & 0xff);
		reg_09 = (UINT8)((u32Afc >> 8) & 0xff);
		reg_0A = (UINT8)((u32Afc >> 16) & 0xff);
		reg_0B = (UINT8)((u32Afc >> 24) & 0xff);
	}
	else if (para->IF >= 35.4 && para->IF <= 40.6)
	{
		reg_07 |= 0x11;

		dAfc = 65536.0 / 30.4 * 65536.0 * (para->IF - 30.4);
		u32Afc = (UINT32)dAfc;
		reg_08 = (UINT8)(u32Afc & 0xff);
		reg_09 = (UINT8)((u32Afc >> 8) & 0xff);
		reg_0A = (UINT8)((u32Afc >> 16) & 0xff);
		reg_0B = (UINT8)((u32Afc >> 24) & 0xff);
	}
	else if (para->IF == 0.0)
	{
		reg_07 |= 0x1D;

		reg_08 = 0x0;
		reg_09 = 0x0;
		reg_0A = 0x0;
		reg_0B = 0x0;

		reg_D6 = 0x80;
	}
	else
	{
		printf("HYQ errinit dvbcSymbolRate err2");
		return LGS_PARA_ERROR;
	}

	if (para->dtmbIFSelect == 0)
	{
		reg_07 &= 0xFB;
	}
	else
	{
		reg_07 |= 0x4;
	}

	switch(para->workMode)
	{
		case DEMOD_WORK_MODE_ANT1_DVBC:
		case DEMOD_WORK_MODE_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
		{
			//modify DVBC noise gate
			err = LGS_WriteRegister(LGS9XSECADDR2, 0xFF, 0x0C);if (err)	goto failed;
			err = LGS_WriteRegister(LGS9XSECADDR2, 0x34, 0x60);if (err)	goto failed;

			if (para->dvbcSymbolRate >= 3.8 && para->dvbcSymbolRate <= 7.6)
			{
				reg_1C |= 0x80;

				dSymbolRate = (7.6 / para->dvbcSymbolRate - 1) * 4194304.0;
				u32SymbolRate = (UINT32)dSymbolRate;
			}
			else if (para->dvbcSymbolRate >= 1.9 && para->dvbcSymbolRate <= 3.8)
			{
				reg_1C |= 0x81;

				dSymbolRate = (3.8 / para->dvbcSymbolRate - 1) * 4194304.0;
				u32SymbolRate = (UINT32)dSymbolRate;
			}
			else if (para->dvbcSymbolRate < 1.9)
			{
				reg_1C |= 0x82;

				dSymbolRate = (1.9 / para->dvbcSymbolRate - 1) * 4194304.0;
				u32SymbolRate = (UINT32)dSymbolRate;
			}
			else
			{
				return LGS_PARA_ERROR;
			}

			reg_10 = (UINT8)(u32SymbolRate & 0xff);
			reg_11 = (UINT8)((u32SymbolRate >> 8) & 0xff);
			reg_12 = (UINT8)((u32SymbolRate >> 16) & 0xff);
			reg_12 |= 0x80;

			switch(para->dvbcQam)
			{
				case QAM4:
				{
					//reg_1C |= 0x00 << 4;
					break;
				}
				case QAM16:
				{
					reg_1C |= 0x02 << 4;
					break;
				}
				case QAM32:
				{
					reg_1C |= 0x03 << 4;
					break;
				}
				case QAM64:
				{
					reg_1C |= 0x04 << 4;
					break;
				}
				case QAM128:
				{
					reg_1C |= 0x05 << 4;
					break;
				}
				case QAM256:
				{
					reg_1C |= 0x06 << 4;
					break;
				}
				default:break;
			}

			break;
		}
		default:
		{
			//modify DVBC noise gate to initial value
			err = LGS_WriteRegister(LGS9XSECADDR2, 0xFF, 0x0C);if (err)	goto failed;
			err = LGS_WriteRegister(LGS9XSECADDR2, 0x34, 0xF0);if (err)	goto failed;
			break;
		}
	}

	err = LGS_WriteRegister(addr, 0x35, 0x40);if (err) goto failed;

	err = LGS_WriteRegister(addr, 0x83, 0xC0);if (err) goto failed;

 switch(para->workMode)
 {
  case DEMOD_WORK_MODE_ANT1_DTMB:
  {
   //GB
			if (para->IF == 0.0)
			{
				reg_D6 = 0x80;
			}
			else
			{
				reg_D6 = 0x84;
			}
   if (err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x01)) goto failed;
   if (err = LGS_WriteRegister(addr, 0xD6, reg_D6)) goto failed;
   if (err = LGS_WriteRegister(addr, 0xFF, 0x00)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x07, reg_07)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x08, reg_08)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x09, reg_09)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x0A, reg_0A)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x0B, reg_0B)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x12, 0x00)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x1C, 0x00)) goto failed;
 
            //disable ant 2 DVBC
   if (err = LGS_WriteRegister(addr, 0xFF, 0x01)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x1C, 0x00)) goto failed;
   if (err = LGS_WriteRegister(addr, 0xFF, 0x00)) goto failed;
 
   //Disable MCU,Enable MCU,Reset MCU
   if (err = LGS_ReadRegister(addr, 0x39, &data)) goto failed;
   data &=0xF8;
   if (err = LGS_WriteRegister(addr, 0x39, data)) goto failed;
   data |= 0x2;
   if (err = LGS_WriteRegister(addr, 0x39, data)) goto failed;
   data |= 0x1;
   if (err = LGS_WriteRegister(addr, 0x39, data)) goto failed;
 
   reg_30 = (para->tsOutputType == TS_Output_Parallel)? 0x92 : 0x93;
   if (err = LGS_WriteRegister(addr, 0x30, reg_30)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x31, 0x02)) goto failed;
   break;
  }
 
  case DEMOD_WORK_MODE_ANT2_DTMB:
  {
   //GB
   if (err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x02)) goto failed;
   if (err = LGS_WriteRegister(addr, 0xD6, reg_D6)) goto failed;
   if (err = LGS_WriteRegister(addr, 0xFF, 0x01)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x07, reg_07)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x08, reg_08)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x09, reg_09)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x0A, reg_0A)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x0B, reg_0B)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x12, 0x00)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x1C, 0x00)) goto failed;
 
            //disable ant 1 DVBC
   if (err = LGS_WriteRegister(addr, 0xFF, 0x00)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x1C, 0x00)) goto failed;
   
   //Disable MCU,Enable MCU,Reset MCU
   if (err = LGS_ReadRegister(addr, 0x39, &data)) goto failed;
   data &=0xF8;
   if (err = LGS_WriteRegister(addr, 0x39, data)) goto failed;
   data |= 0x2;
   if (err = LGS_WriteRegister(addr, 0x39, data)) goto failed;
   data |= 0x1;
   if (err = LGS_WriteRegister(addr, 0x39, data)) goto failed;
 
   reg_30 = (para->tsOutputType == TS_Output_Parallel)? 0x92 : 0x93;
   if (err = LGS_WriteRegister(addr, 0x30, reg_30)) goto failed;
   if (err = LGS_WriteRegister(addr, 0x31, 0x02)) goto failed;
   break;
  }

		case DEMOD_WORK_MODE_ANT1_DVBC:
		{
			//DVBC
			switch(para->dvbcIFPolarity)
			{
				case 0:
				case 2:
				{
					reg_07 &= 0xFB;
					break;
				}
				case 1:
				{
					reg_07 |= 0x4;
					break;
				}
			}

			if (para->IF == 0.0)
			{
				reg_D6 = 0x80;
			}
			else
			{
				reg_D6 = 0x84;
			}

			err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x01);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xD6, reg_D6);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x10, reg_10);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x11, reg_11);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, reg_12);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, reg_1C);if (err) goto failed;

			reg_30 = (para->tsOutputType == TS_Output_Parallel)? 0x92 : 0x93;
			err = LGS_WriteRegister(addr, 0x30, reg_30);if (err) goto failed;
			reg_31 = (para->tsOutputType == TS_Output_Parallel)? 0x32 : 0x33;
			err = LGS_WriteRegister(addr, 0x31, reg_31);if (err) goto failed;
			break;
		}

		case DEMOD_WORK_MODE_ANT2_DVBC:
		{
			//DVBC
			switch(para->dvbcIFPolarity)
			{
				case 0:
				case 2:
				{
					reg_07 &= 0xFB;
					break;
				}
				case 1:
				{
					reg_07 |= 0x4;
					break;
				}
			}

			err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x02);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xD6, 0x80);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x10, reg_10);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x11, reg_11);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, reg_12);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, reg_1C);if (err) goto failed;

			reg_30 = (para->tsOutputType == TS_Output_Parallel)? 0x92 : 0x93;
			err = LGS_WriteRegister(addr, 0x30, reg_30);if (err) goto failed;
			reg_31 = (para->tsOutputType == TS_Output_Parallel)? 0x32 : 0x33;
			err = LGS_WriteRegister(addr, 0x31, reg_31);if (err) goto failed;
			break;
		}

		case DEMOD_WORK_MODE_SUPERTV:
		{
			//Diversity
			err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x03);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xD6, 0x80);if (err) goto failed;

			err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, 0x00);if (err) goto failed;

			err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, 0x00);if (err) goto failed;

			reg_30 = (para->tsOutputType == TS_Output_Parallel)? 0x92 : 0x93;
			err = LGS_WriteRegister(addr, 0x30, reg_30);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x31, 0x02);if (err) goto failed;
			break;
		}

		case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
		{
			//pip
			err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x04);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xD6, 0x80);if (err) goto failed;

			//GB
			err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, 0x00);if (err) goto failed;

			//DVBC
			switch(para->dvbcIFPolarity)
			{
				case 0:
				case 2:
				{
					reg_07 &= 0xFB;
					break;
				}
				case 1:
				{
					reg_07 |= 0x4;
					break;
				}
			}

			err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x10, reg_10);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x11, reg_11);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, reg_12);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, reg_1C);if (err) goto failed;

			switch (para->tsOutputType)
			{
				case TS_Output_PIP_DTMBTsParallel_DVBCSerial:
				{
					reg_31 = 0x92;
					break;
				}
				case TS_Output_PIP_DTMBTsSerial_DVBCSerial:
				{
					reg_31 = 0x93;
					break;
				}
				case TS_Output_PIP_DVBCTsParallel_DTMBSerial:
				{
					reg_31 = 0xD2;
					break;
				}
				case TS_Output_PIP_DVBCTsSerial_DTMBSerial:
				{
					reg_31 = 0xD3;
					break;
				}
				default:
				{
					reg_31 = 0x92;
					break;
				}

			}
			err = LGS_WriteRegister(addr, 0x31, reg_31);if (err) goto failed;
			break;
		}

		case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
		{
			//pip
			err = LGS_WriteRegister(addr, 0x03, reg_03 | 0x04);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0xD6, 0x80);if (err) goto failed;

			//GB
			err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, 0x00);if (err) goto failed;

			//DVBC
			switch(para->dvbcIFPolarity)
			{
				case 0:
				case 2:
				{
					reg_07 &= 0xFB;
					break;
				}
				case 1:
				{
					reg_07 |= 0x4;
					break;
				}
			}

			err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x08, reg_08);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x09, reg_09);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0A, reg_0A);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x0B, reg_0B);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x10, reg_10);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x11, reg_11);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x12, reg_12);if (err) goto failed;
			err = LGS_WriteRegister(addr, 0x1C, reg_1C);if (err) goto failed;

			switch (para->tsOutputType)
			{
				case TS_Output_PIP_DTMBTsParallel_DVBCSerial:
				{
					reg_31 = 0x92;
					break;
				}
				case TS_Output_PIP_DTMBTsSerial_DVBCSerial:
				{
					reg_31 = 0x93;
					break;
				}
				case TS_Output_PIP_DVBCTsParallel_DTMBSerial:
				{
					reg_31 = 0xD2;
					break;
				}
				case TS_Output_PIP_DVBCTsSerial_DTMBSerial:
				{
					reg_31 = 0xD3;
					break;
				}
				default:
				{
					reg_31 = 0x92;
					break;
				}

			}
			err = LGS_WriteRegister(addr, 0x31, reg_31);if (err) goto failed;
			break;
		}
		default:break;
	}

	switch (para->workMode)
	{
		case DEMOD_WORK_MODE_ANT1_DVBC:
		case DEMOD_WORK_MODE_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
		{
			//check DVBC lock
			for(i = 0; i < 4; i++)
			{
				LGS9X_SoftReset();

				if (para->dvbcSymbolRate >= 5.0 && para->dvbcSymbolRate <= 7.6)
				{
					LGS_Wait(300);
				}
				else if (para->dvbcSymbolRate >= 3.5 && para->dvbcSymbolRate <= 5.0)
				{
					LGS_Wait(500);
				}
				else if (para->dvbcSymbolRate >= 2.5 && para->dvbcSymbolRate <= 3.5)
				{
					LGS_Wait(800);
				}
				else if (para->dvbcSymbolRate >= 1.5 && para->dvbcSymbolRate <= 2.5)
				{
					LGS_Wait(1100);
				}
				else if (para->dvbcSymbolRate < 1.5)
				{
					LGS_Wait(1500);
				}

				err = LGS_ReadRegister(addr, 0xDA, &data);if (err) goto failed;
				if (data & 0x80)
				{
					break;	//lock
				}

				if (para->dvbcIFPolarity == 2)
				{
					if (reg_07 & 0x4)
					{
						reg_07 &= 0xFB;;
						err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
					}
					else
					{
						reg_07 |= 0x4;;
						err = LGS_WriteRegister(addr, 0x07, reg_07);if (err) goto failed;
					}
				}
			}

			break;
		}
		default:
		{
			LGS9X_SoftReset();
			break;
		}
	}

	//Enable Firmware
	err = LGS_ReadRegister(addr, 0x39, &data);if (err) goto failed;
	data |= 0x4;
	err = LGS_WriteRegister(addr, 0x39, data);if (err) goto failed;
	data |= 0x2;
	err = LGS_WriteRegister(addr, 0x39, data);if (err) goto failed;
	data |= 0x1;
	err = LGS_WriteRegister(addr, 0x39, data);if (err) goto failed;

	return LGS_NO_ERROR;

failed:
	return err;
}

LGS_RESULT LGS9701B1_Patch(void)
{
	LGS_RESULT  err = LGS_NO_ERROR;
	UINT8       addr = LGS9XSECADDR1;

	err = LGS_WriteRegister(addr, 0x33, 0x90);

	return err;
}

LGS_RESULT ClearBER(void)
{
	UINT8	err = LGS_NO_ERROR;
	UINT8	addr = LGS9XSECADDR1;

	// PKTRUN: 1-running and can be cleared, 0-stoped and can be read but not cleared
	err = LGS_RegisterSetBit( addr, 0x30, 0x10 );if (err)	goto failed;	// running
	err = LGS_RegisterSetBit( addr, 0x30, 0x08 );if (err)	goto failed;	// clear
	err = LGS_RegisterClrBit( addr, 0x30, 0x08 );if (err)	goto failed;	// normal

	return LGS_NO_ERROR;

failed:
	return err;
}
#if 0
LGS_RESULT LGS9X_CheckBCH(DEMOD_WORK_MODE workMode, UINT16 waitTime, UINT32 *pPkgCount, UINT32 *pPkgErr)
{
	//DemodConfig		para;
	//UINT32			pktCount, pktErr;

	LGS9X_CheckBCHreturn LGS_NO_DEFINE;

/*
	ClearBER();

	if (waitTime != 0)
	{
		LGS_Wait(waitTime);
	}

	// Get count
	DemodParaIgnoreAll(&para); para.BCHCount = 0; para.BCHPktErrCount = 0;
	LGS9X_GetConfig(workMode, &para);
	pktCount = para.BCHCount;
	pktErr = para.BCHPktErrCount;

	if ( pPkgCount )
		*pPkgCount = pktCount;

	if ( pPkgErr )
		*pPkgErr = pktErr;

	if ( (pktCount == 0) || (pktErr > (pktCount/4) ) )
		return LGS_ERROR;
	else
		return LGS_NO_ERROR;
*/
}
#endif


LGS_RESULT LGS9X_CheckLocked(DEMOD_WORK_MODE workMode, UINT8 *locked1, UINT8 *locked2, UINT16 waitms)
{
	UINT8	err = LGS_NO_ERROR;
	UINT8	addr = LGS9XSECADDR1;
	UINT8	data = 0x0;
	UINT32  Timer;

	if ((workMode != DEMOD_WORK_MODE_ANT1_DVBC) && (workMode != DEMOD_WORK_MODE_ANT2_DVBC))
	{
		if (locked1 == NULL)
		{
			return LGS_PARA_ERROR;
		}
		else
		{
			*locked1 = 1;		//unlock
		}
	}

	if ((workMode != DEMOD_WORK_MODE_ANT1_DTMB) && (workMode != DEMOD_WORK_MODE_ANT2_DTMB))
	{
		if (locked2 == NULL)
		{
			return LGS_PARA_ERROR;
		}
		else
		{
			*locked2 = 1;		//unlock
		}
	}
#if 0  //yanxi 110802 marked [6035]
	if (waitms != 0)
	{
		LGS_Wait(waitms);
	}
#endif
	 Timer = msAPI_Timer_GetTime0();//yanxi 110802  [6035]
	 do{
	 	LGS_Wait(10);
		switch(workMode)
		{
			case DEMOD_WORK_MODE_ANT1_DTMB:
			{			
				//GB check lock status
				err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err)		return err;
				err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

				data &= 0x90;		//Check Flag CA_Locked and AFC_Locked
				if (data == 0x90)
				{
					*locked1 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					if(data == 0x80||data == 0x10)
						*locked1 = 2;
					else
						*locked1 = 1;	//unlock
				}

				break;
			}

			case DEMOD_WORK_MODE_ANT2_DTMB:
			{
				//GB check lock status
				err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err)		return err;
				err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

				data &= 0x90;		//Check Flag CA_Locked and AFC_Locked
				if (data == 0x90)
				{
					*locked1 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked1 = 1;	//unlock
				}

				break;
			}

			case DEMOD_WORK_MODE_ANT1_DVBC:
			case DEMOD_WORK_MODE_ANT2_DVBC:
			{
				//DVBC check lock status
				err = LGS_ReadRegister(addr, 0xDA, &data);if (err)		return err;
				if (data & 0x80)
				{
					*locked2 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked2 = 1;	//unlock
				}
				break;
			}

			case DEMOD_WORK_MODE_SUPERTV:
			{
				//GB check lock status
				err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err)		return err;
				err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

				data &= 0x90;		//Check Flag CA_Locked and AFC_Locked
				if (data == 0x90)
				{
					*locked1 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked1 = 1;	//unlock
					
				}

				//GB check lock status
				err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err)		return err;
				err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

				data &= 0x90;		//Check Flag CA_Locked and AFC_Locked
				if (data == 0x90)
				{
					*locked2 = 0;	//lock
				}
				else
				{
					*locked2 = 1;	//unlock
				}
				break;
			}

			case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
			{
				//GB check lock status
				err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err)		return err;
				err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

				data &= 0x90;	//Check Flag CA_Locked and AFC_Locked
				if (data == 0x90)
				{
					*locked1 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked1 = 1;	//unlock
				}

				//DVBC check lock status
				err = LGS_ReadRegister(addr, 0xDA, &data);if (err)		return err;
				if (data & 0x80)
				{
					*locked2 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked2 = 1;	//unlock
				}
				break;
			}

			case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
			{
				//GB check lock status
				err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err)		return err;
				err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

				data &= 0x90;	//Check Flag CA_Locked and AFC_Locked
				if (data == 0x90)
				{
					*locked1 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked1 = 1;	//unlock
				}

				//DVBC check lock status
				err = LGS_ReadRegister(addr, 0xDA, &data);if (err)		return err;
				if (data & 0x80)
				{
					*locked2 = 0;	//lock
					return LGS_NO_ERROR;
				}
				else
				{
					*locked2 = 1;	//unlock
				}
				break;
			}
			default:break;
		}
 		}while(msAPI_Timer_DiffTimeFromNow(Timer) < waitms);
	 
	if(*locked1 == 2)
	{
	//printf("lock 2\n");
	Timer = msAPI_Timer_GetTime0();//yanxi 110802  [6035]
	waitms = waitms<<1;
	do{
	 	LGS_Wait(10);
	 	//GB check lock status
	 	err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err)		return err;
	 	err = LGS_ReadRegister(addr, 0x13, &data);if (err)		return err;

	 	data &= 0x90;		//Check Flag CA_Locked and AFC_Locked
	 	if (data == 0x90)
		{
			*locked1 = 0;	//lock
			return LGS_NO_ERROR;
		}
	  }while(msAPI_Timer_DiffTimeFromNow(Timer) < waitms);
	}
	return LGS_NO_ERROR;
}


LGS_RESULT LGS9X_I2CEchoOn()
{
	UINT8		addr = LGS9XSECADDR1;
	LGS_RESULT	err = LGS_NO_ERROR;

	err = LGS_RegisterSetBit(addr, 0x01, 0x80);
	return err;
}


LGS_RESULT LGS9X_I2CEchoOff()
{
	UINT8		addr = LGS9XSECADDR1;
	LGS_RESULT	err = LGS_NO_ERROR;

	err = LGS_RegisterClrBit(addr, 0x01, 0x80);
	return err;
}


LGS_RESULT LGS9X_GetConfig(DEMOD_WORK_MODE workMode, DemodConfig *pDemodConfig)
{
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		addr = LGS9XSECADDR1;
	UINT8		dat;
	DemodConfig	*pPara = pDemodConfig;

	switch(workMode)
	{
		case DEMOD_WORK_MODE_ANT1_DTMB:
		case DEMOD_WORK_MODE_ANT2_DTMB:
		case DEMOD_WORK_MODE_SUPERTV:
		case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
		{
			switch(workMode)
			{
				case DEMOD_WORK_MODE_ANT1_DTMB:
				case DEMOD_WORK_MODE_SUPERTV:
				case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
				{
					err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err)			goto failed;

					break;
				}

				case DEMOD_WORK_MODE_ANT2_DTMB:
				case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
				{
					err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err)			goto failed;
					
					break;
				}
				default:break;
			}

			// SubCarrier, FecRate, TimeDeintvl
			err = LGS_ReadRegister(addr, 0x1F, &dat);if (err)			goto failed;
			if ( PARA_IGNORE != pPara->SubCarrier )		pPara->SubCarrier	= (dat & 0x1C) >> 2;
			if ( PARA_IGNORE != pPara->FecRate )		pPara->FecRate		= (dat & 0x03);
			if ( PARA_IGNORE != pPara->TimeDeintvl )	pPara->TimeDeintvl	= (dat & 0x20) >> 5;

			// GuardIntvl CarrierMode, PnNumber
			err = LGS_ReadRegister(addr, 0x13, &dat);if (err)			goto failed;
			if ( PARA_IGNORE != pPara->GuardIntvl )		pPara->GuardIntvl	= (dat & 0x60) >> 5;
			if ( PARA_IGNORE != pPara->CarrierMode )	pPara->CarrierMode	= (dat & 0x08) >> 3;
			if ( PARA_IGNORE != pPara->PnNumber )		pPara->PnNumber		= (dat & 0x01);

			// IsMpegClockInvert
			err = LGS_ReadRegister(addr, 0x30, &dat);if (err)					goto failed;
			if ( PARA_IGNORE != pPara->IsMpegClockInvert )		pPara->IsMpegClockInvert	= (dat & 0x02) >> 1;

			// BCHCount, BCHPktErrCount
			if ( PARA_IGNORE != (pPara->BCHCount&0xff)
				|| PARA_IGNORE != (pPara->BCHPktErrCount&0xff) )
			{
				LGS_RegisterClrBit( addr, 0x31, 0x20 );	// GB receive TS block numbers
				LGS_RegisterClrBit( addr, 0x30, 0x10 );	// stop counter

				//Total block count and Error block count
				if ( PARA_IGNORE != (pPara->BCHCount & 0xff) )
				{
					pPara->BCHCount = 0;
					err = LGS_ReadRegister(addr, 0x2B, &dat);if (err)			goto failed;
					pPara->BCHCount |= dat;
					pPara->BCHCount <<= 8;
					err = LGS_ReadRegister(addr, 0x2A, &dat);if (err)			goto failed;
					pPara->BCHCount |= dat;
					pPara->BCHCount <<= 8;
					err = LGS_ReadRegister(addr, 0x29, &dat);if (err)			goto failed;
					pPara->BCHCount |= dat;
					pPara->BCHCount <<= 8;
					err = LGS_ReadRegister(addr, 0x28, &dat);if (err)			goto failed;
					pPara->BCHCount |= dat;
				}

				if ( PARA_IGNORE != (pPara->BCHPktErrCount & 0xff) )
				{
					pPara->BCHPktErrCount = 0;
					err = LGS_ReadRegister(addr, 0x2F, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount |= dat;
					pPara->BCHPktErrCount <<= 8;
					err = LGS_ReadRegister(addr, 0x2E, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount |= dat;
					pPara->BCHPktErrCount <<= 8;
					err = LGS_ReadRegister(addr, 0x2D, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount |= dat;
					pPara->BCHPktErrCount <<= 8;
					err = LGS_ReadRegister(addr, 0x2C, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount |= dat;
				}

				LGS_RegisterSetBit( addr, 0x30, 0x10 );	// running
			}

			// AFCPhase
			if ( PARA_IGNORE != (pPara->AFCPhase & 0xff) )
			{
				pPara->AFCPhase = 0;
				err = LGS_ReadRegister(addr, 0x23, &dat);if (err)			goto failed;
				pPara->AFCPhase |= dat;
				pPara->AFCPhase <<= 8;
				err = LGS_ReadRegister(addr, 0x22, &dat);if (err)			goto failed;
				pPara->AFCPhase |= dat;
				pPara->AFCPhase <<= 8;
				err = LGS_ReadRegister(addr, 0x21, &dat);if (err)			goto failed;
				pPara->AFCPhase |= dat;
			}

			// AFCPhaseInit
			if ( PARA_IGNORE != (pPara->AFCPhaseInit & 0xff) )
			{
				pPara->AFCPhaseInit = 0;
				err = LGS_ReadRegister(addr, 0x0B, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit |= dat;
				pPara->AFCPhaseInit <<= 8;
				err = LGS_ReadRegister(addr, 0x0A, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit |= dat;
				pPara->AFCPhaseInit <<= 8;
				err = LGS_ReadRegister(addr, 0x09, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit |= dat;
				pPara->AFCPhaseInit <<= 8;
				err = LGS_ReadRegister(addr, 0x08, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit |= dat;
			}

			break;
		}
		default:break;
	}

	switch(workMode)
	{
		case DEMOD_WORK_MODE_ANT1_DVBC:
		case DEMOD_WORK_MODE_ANT2_DVBC:
		case DEMOD_WORK_MODE_SUPERTV:
		case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
		{
			switch(workMode)
			{
				case DEMOD_WORK_MODE_SUPERTV:
				{
					err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err)			goto failed;

					// SubCarrier, FecRate, TimeDeintvl
					err = LGS_ReadRegister(addr, 0x1F, &dat);if (err)			goto failed;
					if ( PARA_IGNORE != pPara->SubCarrier2 )	pPara->SubCarrier2	= (dat & 0x1C) >> 2;
					if ( PARA_IGNORE != pPara->FecRate2 )		pPara->FecRate2		= (dat & 0x03);
					if ( PARA_IGNORE != pPara->TimeDeintvl2 )	pPara->TimeDeintvl2	= (dat & 0x20) >> 5;

					// GuardIntvl CarrierMode, PnNumber
					err = LGS_ReadRegister(addr, 0x13, &dat);if (err)			goto failed;
					if ( PARA_IGNORE != pPara->GuardIntvl2 )	pPara->GuardIntvl	= (dat & 0x60) >> 5;
					if ( PARA_IGNORE != pPara->CarrierMode2 )	pPara->CarrierMode2	= (dat & 0x08) >> 3;
					if ( PARA_IGNORE != pPara->PnNumber2 )		pPara->PnNumber2	= (dat & 0x01);

					// IsMpegClockInvert
					err = LGS_ReadRegister(addr, 0x30, &dat);if (err)					goto failed;
					if ( PARA_IGNORE != pPara->IsMpegClockInvert2 )		pPara->IsMpegClockInvert2	= (dat & 0x02) >> 1;
					break;
				}

				case DEMOD_WORK_MODE_ANT1_DVBC:
				case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
				{
					err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err)			goto failed;
					LGS_RegisterSetBit( addr, 0x31, 0x20 );	// DVBC receive TS block numbers
					
					break;
				}
				case DEMOD_WORK_MODE_ANT2_DVBC:
				case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
				{
					err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err)			goto failed;
					LGS_RegisterSetBit( addr, 0x31, 0x20 );	// DVBC receive TS block numbers
					
					break;
				}
				default:break;
			}

			// BCHCount, BCHPktErrCount
			if ( PARA_IGNORE != (pPara->BCHCount2 & 0xff)
				|| PARA_IGNORE != (pPara->BCHPktErrCount2 & 0xff) )
			{
				LGS_RegisterClrBit( addr, 0x30, 0x10 );	// stop counter

				//Total block count and Error block count
				if ( PARA_IGNORE != (pPara->BCHCount2 & 0xff) )
				{
					pPara->BCHCount2 = 0;
					err = LGS_ReadRegister(addr, 0x2B, &dat);if (err)			goto failed;
					pPara->BCHCount2 |= dat;
					pPara->BCHCount2 <<= 8;
					err = LGS_ReadRegister(addr, 0x2A, &dat);if (err)			goto failed;
					pPara->BCHCount2 |= dat;
					pPara->BCHCount2 <<= 8;
					err = LGS_ReadRegister(addr, 0x29, &dat);if (err)			goto failed;
					pPara->BCHCount2 |= dat;
					pPara->BCHCount2 <<= 8;
					err = LGS_ReadRegister(addr, 0x28, &dat);if (err)			goto failed;
					pPara->BCHCount2 |= dat;
				}

				if ( PARA_IGNORE != (pPara->BCHPktErrCount2 & 0xff) )
				{
					pPara->BCHPktErrCount2 = 0;
					err = LGS_ReadRegister(addr, 0x2F, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount2 |= dat;
					pPara->BCHPktErrCount2 <<= 8;
					err = LGS_ReadRegister(addr, 0x2E, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount2 |= dat;
					pPara->BCHPktErrCount2 <<= 8;
					err = LGS_ReadRegister(addr, 0x2D, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount2 |= dat;
					pPara->BCHPktErrCount2 <<= 8;
					err = LGS_ReadRegister(addr, 0x2C, &dat);if (err)			goto failed;
					pPara->BCHPktErrCount2 |= dat;
				}

				LGS_RegisterSetBit( addr, 0x30, 0x10 );	// running
			}

			// AFCPhase
			if ( PARA_IGNORE != (pPara->AFCPhase2 & 0xff) )
			{
				pPara->AFCPhase2 = 0;
				err = LGS_ReadRegister(addr, 0x23, &dat);if (err)			goto failed;
				pPara->AFCPhase2 |= dat;
				pPara->AFCPhase2 <<= 8;
				err = LGS_ReadRegister(addr, 0x22, &dat);if (err)			goto failed;
				pPara->AFCPhase2 |= dat;
				pPara->AFCPhase2 <<= 8;
				err = LGS_ReadRegister(addr, 0x21, &dat);if (err)			goto failed;
				pPara->AFCPhase2 |= dat;
			}

			// AFCPhaseInit
			if ( PARA_IGNORE != (pPara->AFCPhaseInit2 & 0xff) )
			{
				pPara->AFCPhaseInit2 = 0;
				err = LGS_ReadRegister(addr, 0x0B, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit2 |= dat;
				pPara->AFCPhaseInit2 <<= 8;
				err = LGS_ReadRegister(addr, 0x0A, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit2 |= dat;
				pPara->AFCPhaseInit2 <<= 8;
				err = LGS_ReadRegister(addr, 0x09, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit2 |= dat;
				pPara->AFCPhaseInit2 <<= 8;
				err = LGS_ReadRegister(addr, 0x08, &dat);if (err)			goto failed;
				pPara->AFCPhaseInit2 |= dat;
			}

			break;
		}
		default:break;
	}

	return LGS_NO_ERROR;

failed:
	return err;
}

LGS_RESULT LGS9X_SetConfig(DEMOD_WORK_MODE workMode, DemodConfig *pDemodConfig)
{
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		addr = LGS9XSECADDR1;
	UINT8		dat;
	UINT8		reg_14;
	DemodConfig	*pPara = pDemodConfig;
	workMode = workMode;
	if( PARA_IGNORE != pPara->AdType )
	{
		g_AdType = pPara->AdType;

		switch (pPara->AdType)
		{
		case 0:
			// is internal ad , so far do not write any register.
			break;
		case 1:			
			 //is external ad9203 , need write any register.

			err = LGS_ReadRegister(addr, 0xf9, &dat);if(err)			goto failed;
			dat |= 0x01; // f9[0] = 1
			err = LGS_WriteRegister(addr, 0xf9, dat);if(err)			goto failed;
			
			LGS_Wait(100);
				
			err = LGS_ReadRegister(addr, 0x14, &reg_14);if(err)		goto failed;
			dat = reg_14 & 0xf0;
			dat = reg_14 | 0x03;
			err = LGS_WriteRegister(addr, 0x14, dat);if(err)			goto failed;

			dat = dat    & 0xfC;
			dat = dat    | 0x02;
			err = LGS_WriteRegister(addr, 0x14, dat);if(err)			goto failed;

			dat = dat    & 0xfC;
			err = LGS_WriteRegister(addr, 0x14, dat);if(err)			goto failed;
			
			LGS_Wait(10);
			
			err = LGS_ReadRegister(addr, 0xd3, &dat);if(err)			goto failed;
			dat |= 0x08; // d3[3] = 1
			err = LGS_WriteRegister(addr, 0xd3, dat);if(err)			goto failed;

			err = LGS_ReadRegister(addr, 0x03, &dat);if(err)			goto failed;
			dat |= 0x80; // 03[7] = 1
			err = LGS_WriteRegister(addr, 0x03, dat);if(err)			goto failed;
			err = LGS_ReadRegister(addr, 0xd6, &dat);if(err)			goto failed;
			dat |= 0x04; // d6[2] = 1
			err = LGS_WriteRegister(addr, 0xd6, dat);if(err)			goto failed;

			err = LGS_ReadRegister(addr, 0x30, &dat);if(err)			goto failed;
			dat |= 0x01; // 30[0] = 1 
			err = LGS_WriteRegister(addr, 0x30, dat);if(err)			goto failed;

			err = LGS_WriteRegister(addr, 0xc7, 0x94);if(err)		goto failed;

			err = LGS_WriteRegister(addr, 0xcf, 0x55);if(err)		goto failed;

			err = LGS_WriteRegister(addr, 0x14, reg_14);if(err)		goto failed;

			break;
		case 2:
			// is external ad, reserved.
			break;
		default:
			break;
		}
	}

	return LGS_NO_ERROR;

failed:
	return err;
}


LGS_RESULT LGS9X_GetSignalQuality(DEMOD_WORK_MODE workMode, UINT16 *pSignalQuality)
{
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		data = 0x0;

	if (pSignalQuality == NULL)
	{
		return LGS_PARA_ERROR;
	}
	else
	{
		*pSignalQuality = 0;
	}
	workMode = workMode;
	switch (workMode)
	{
		case DEMOD_WORK_MODE_ANT1_DTMB:
		case DEMOD_WORK_MODE_ANT2_DTMB:
		case DEMOD_WORK_MODE_SUPERTV:
		{
			err = LGS_WriteRegister(LGS9XSECADDR2, 0xFF, 0x0D);if (err)	goto failed;
			err = LGS_ReadRegister(LGS9XSECADDR2, 0x38, &data);if (err)	goto failed;
			*pSignalQuality |= (UINT16)data;
			break;
		}
		case DEMOD_WORK_MODE_ANT1_DVBC:
		case DEMOD_WORK_MODE_ANT2_DVBC:
		{
			err = LGS_WriteRegister(LGS9XSECADDR2, 0xFF, 0x0D);if (err)	goto failed;
			err = LGS_ReadRegister(LGS9XSECADDR2, 0x3C, &data);if (err)	goto failed;
			*pSignalQuality |= (UINT16)data << 8;
			break;
		}
		case DEMOD_WORK_MODE_PIP_ANT1_DTMB_ANT2_DVBC:
		case DEMOD_WORK_MODE_PIP_ANT1_DVBC_ANT2_DTMB:
		{
			err = LGS_WriteRegister(LGS9XSECADDR2, 0xFF, 0x0D);if (err)	goto failed;
			err = LGS_ReadRegister(LGS9XSECADDR2, 0x38, &data);if (err)	goto failed;
			*pSignalQuality |= (UINT16)data;

			err = LGS_ReadRegister(LGS9XSECADDR2, 0x3C, &data);if (err)	goto failed;
			*pSignalQuality |= (UINT16)data << 8;
			break;
		}
		default:break;
	}

	return LGS_NO_ERROR;

failed:
	return err;
}

LGS_RESULT LGS9X_GetSignalStrength(DEMOD_WORK_MODE workMode, UINT32 *pSignalStrength)
{
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		addr = LGS9XSECADDR1;
	UINT8		reg_B1 = 0x0;
	workMode = workMode;

	if (pSignalStrength == NULL)
	{
		return LGS_PARA_ERROR;
	}

	err = LGS_WriteRegister(addr, 0xFF, 0x00);if (err) goto failed;
	err = LGS_ReadRegister(addr, 0xB1, &reg_B1);if (err) goto failed;

	*pSignalStrength = 0;
	*pSignalStrength |= (INT32)reg_B1;
#if 0  //yanxi 110802 marked [6035]
	err = LGS_WriteRegister(addr, 0xFF, 0x01);if (err) goto failed;
	err = LGS_ReadRegister(addr, 0xB1, &reg_B1);if (err) goto failed;

	*pSignalStrength |= (INT32)reg_B1 << 8;
#endif
	return LGS_NO_ERROR;

failed:
	return err;
}

LGS_RESULT LGS9X_SoftReset()
{
	printf("HYQ LGS9X_SoftReset>>>\n");
	LGS_RESULT	err = LGS_NO_ERROR;
	UINT8		addr = LGS9XSECADDR1;
	UINT8		dat;

	err = LGS_ReadRegister(addr, 0x02, &dat);
	if (err != LGS_NO_ERROR)
	{
		printf("HYQ err type11[%d]>>>\n",err);
		return err;
	}

	dat = dat & 0xFE;

	err = LGS_WriteRegister(addr, 0x02, dat);
	if (err != LGS_NO_ERROR)
	{
		printf("HYQ err type22[%d]>>>\n",err);
		return err;
	}

	dat = dat | 0x01;
	err = LGS_WriteRegister(addr, 0x02, dat);
	if (err != LGS_NO_ERROR)
	{
		printf("HYQ err type33[%d]>>>\n",err);
		return err;
	}

	return LGS_NO_ERROR;
}

void LGS9X_SetDtmbMode(void)//yanxi added 110723
{
	U8 temp;
	DemodInitPara para;
	para.workMode = DEMOD_WORK_MODE_ANT1_DTMB;
	para.IF = 5.0; //Mhz
	para.dtmbIFSelect = 1; //0: Tuner is high IF
	#if(BOARD_CSTM_SEL == BD_ST6306PUM_D1)
	para.tsOutputType = TS_Output_Serial;
	#else
	para.tsOutputType = TS_Output_Parallel;
	#endif
	temp = LGS9X_Init(&para);
		printf("HYQ lgs9x init error = [%d]\n",temp);

	temp=LGS9701B1_Patch();
		printf("HYQ LGS9701B1_Patch error = [%d]\n",temp);
}
#if 0
U8 LGS9X_SetGPIO(BOOLEAN GPIO_staut1,BOOLEAN GPIO1eable,BOOLEAN GPIO_staut0,BOOLEAN GPIO0eable)
{
	LGS_RESULT	err     = LGS_NO_ERROR;
	UINT8		addr    = LGS9XSECADDR1;
	U8			DateToSet = 0x50;
	DateToSet = GPIO_staut1?(DateToSet|BIT3):DateToSet;
	DateToSet = GPIO1eable?(DateToSet|BIT2):DateToSet;
	DateToSet = GPIO_staut0?(DateToSet|BIT1):DateToSet;
	DateToSet = GPIO0eable?(DateToSet|BIT0):DateToSet;
	printf("HYQ DateToSet[%d]\n",DateToSet);
	
	err = LGS_WriteRegister(addr,0x14,DateToSet);
	if(err)
		printf("HYQ err in set gpio\n");
	return err;
}
#endif
U8 LGS9X_SetGPIO0(BOOLEAN GPIOFLG)
{
	LGS_RESULT	err     = LGS_NO_ERROR;
	UINT8		addr    = LGS9XSECADDR1;
	U8			DateToSet = 0x60;
	DateToSet = GPIOFLG?(DateToSet|BIT1):DateToSet;
	err = LGS_WriteRegister(addr,0x14,DateToSet);
	if(err)
		printf("HYQ err in set gpio[%d]\n",DateToSet);
	return err;

}
void LGS9X_GetRegistersForDebug(void)
{
	LGS_RESULT	err     = LGS_NO_ERROR;
	UINT8		addr    = LGS9XSECADDR1;
	U8 i;
	UINT8       RegAdd[]={0x04,  0x07,0x08,0x09,0x0a,0x0b,  0x13,0x14,  
								0x10,0x11,0x12,0x1c,0x15,0x16,0x17,0x30,0x31,0x33};
	U8 			Registers[18];
	printf("=======LGS_DEBUG=======\n");
	for(i = 0;i < 18;i++)
	{
			err = LGS_ReadRegister(addr,RegAdd[i],&Registers[i]);
			if(err)
				printf("[0x%x] Read err\n",RegAdd[i]);
			else
				printf("[0x%x] = [0x%x]\n",RegAdd[i],Registers[i]);
	}
	printf("=======================\n");

	return;
}



