/* ----------------------------------------------------------------------------
 File Name: Hdic2311.c

 Description:

 Version 1.0 : Created   2012.03.21  Sharp Wang
         1.1 ：Modified HDIC2311_SetTsFormat and HDIC2311_SetTunerType.
         2.0 ：Modified  2013.03.05  Sharp Wang	 
 ---------------------------------------------------------------------------- */ 
//#include <stdio.h>
//#include "math.h"
/*****************************************************************************
 以下函数是客户根据自己平台情况，需要改写的函数。
*****************************************************************************/
#define HDIC2311_Print0(x)	//printf(x)
#define HDIC2311_Print1(x,y)	//printf(x,y)
#define HDIC2311_Print2(x,y,z)	//printf(x,y,z)
#define HDIC2311_Print3(x,y,z,a)	//printf(x,y,z,a)  

/********************************
 I2C写寄存器
********************************/
UINT8 HDIC2311_WriteRegister(UINT16 Register, UINT8 Data)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 RegisterData[2];

	RegisterData[0] = (UINT8)((Register&0xFF00)>>8);
	RegisterData[1] = (UINT8)(Register&0xFF);

	if(MDrv_IIC_WriteBytes(HDIC2311_I2C_ADDRESS,2,RegisterData,1,&Data) == FALSE)
		{
		printf("WRITE IIC FAIL @@@@\n");
		err = HDIC_OTHER_ERROR;
		}
	return (err);
}

/********************************
 I2C读寄存器
********************************/
UINT8 HDIC2311_ReadRegister(UINT16 Register, UINT8 *Data)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 RegisterData[2];

	RegisterData[0] = (UINT8)((Register&0xFF00)>>8);
	RegisterData[1] = (UINT8)(Register&0xFF);

	if (MDrv_IIC_ReadBytes(HDIC2311_I2C_ADDRESS,2,RegisterData,1,Data) == FALSE)
		{
		printf("READ IIC FAIL @@@@\n");
		err = HDIC_OTHER_ERROR;
		}
	return (err);
}

/********************************
 设置GPIO
********************************/
void HDIC2311_SetGPIO(BOOL HighLow)
{
	UINT8 Output_Level = (HighLow?	0x01:0x00);
	/*  GPIO0打开  */
	HDIC2311_WriteRegister(0x0014,0x01);
	/* GPIO0配置成输出 */
	HDIC2311_WriteRegister(0x0015,0x00);
	/* GPIO0置高/低  */
	HDIC2311_Print1("----------HDIC2311_SetGPIO0 to %d--------\n",Output_Level);
	HDIC2311_WriteRegister(0x0016,Output_Level);
}

/********************************
 设置高频头
********************************/
UINT8 HDIC2311_SetTuner(UINT32 Frequency)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 Address = 0xC2;/*Tuner I2C address*/
#if 0	
	UINT8 TunerData[6],Temp;
	UINT16 tunerDivi;
	UINT8 ReadData = 0;

#endif
	Frequency = Frequency;

	err = HDIC2311_OpenTunerI2C(Address);
	if(err)	return err;

	/****************************
	*
	* 此处应是tuner的锁频操作，具体
	* 需根据客户的实际情况。
	*
	****************************/

	err = HDIC2311_CloseTunerI2C();
	return (err);
}

/********************************
延时函数
********************************/
void HDIC2311_Wait(UINT16 millisecond)
{
	MsOS_DelayTask(millisecond);
}

/********************************
芯片硬复位
********************************/
void HDIC2311_HWReset(void)
{
	/*芯片硬复位，可根据硬件情况实现*/
//	Demod_HW_Reset();
	HDIC2311_Print0("---------------2311 Demod H/W Reset !!!\n");
    mdrv_gpio_set_low( PIN_103 );
    msAPI_Timer_Delayms(10);
    mdrv_gpio_set_high( PIN_103 );
	return;
}   



/**********************************************
** 配置2311的工作模式，
** 地面：HDIC2311_DTMB_SELECT 
** 或 有线：HDIC2311_CABLE_SELECT
**********************************************/
UINT8 HDIC2311_SetWorkMode(UINT8 mode)
{
	UINT8 ReadData = 0;	
	UINT8 err = HDIC_NO_ERROR;
	
	err = HDIC2311_ReadRegister(0x0001,&ReadData);
	if(err)	return err;
	
	ReadData &= 0xFE;
	ReadData |= mode;
	err = HDIC2311_WriteRegister(0x0001,ReadData);
	if(err)	return err;
	
	if(mode==HDIC2311_DTMB_SELECT)
	{
		HDIC2311_Print0("-----------2311 DTMB Selected...\n");
	}
	else if(mode==HDIC2311_CABLE_SELECT)
	{
		HDIC2311_Print0("-----------2311 Cable Selected...\n");
	}
	return err;
	
}

/************************************
** 自动设置地面情况下信号格式
*************************************/
UINT8 HDIC2311_SetAutoMode(void)
{
	UINT8 err = HDIC_NO_ERROR;

	HDIC2311_Print0("-------------Set AutoMode \n");

	/*配置为自动模式*/
	err = HDIC2311_WriteRegister(0x0002,0x00);
	return err;	
}

/**********************************************
判断信号是否锁住
**********************************************/
BOOL HDIC2311_IsDemodLocked(UINT8 *Status)
{
	UINT8 WorkMode = 0;
	UINT8 locked=0;
	UINT8 err = HDIC_NO_ERROR;

	double SNR,BER,LBER;
	UINT8 Carrier,Mode,Rate,InterleaverLength,PnMode,PnVariable;
	UINT32 FieldStrength,NCOValue;
	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);
	if(err)	return FALSE;
	
	WorkMode &= 0x01;

	if(WorkMode == HDIC2311_DTMB_SELECT)
	{
		err = HDIC2311_ReadRegister(0x0011,&locked);
		err = HDIC2311_ReadRegister(0x0010,Status);
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		err = HDIC2311_ReadRegister(0x0110,Status);
		locked = *Status;
	}
	HDIC2311_GetSignalSNR(&SNR);
	HDIC2311_GetSignalBER(&BER);
	HDIC2311_GetAutoParameters(&Carrier,&Mode, &Rate, &InterleaverLength,&PnMode,&PnVariable);
	HDIC2311_GetFieldStrength(&FieldStrength);
	HDIC2311_GetLdpcBER(&LBER);
	HDIC2311_GetNCOValue(&NCOValue);
	//printf(" locked = 0x%X,  Status= 0x%X \n",locked,*Status);
    //rintf("SNR: %d,BER: %d,LBER: %d,FS: %d,NCO: 0x%06x \n",SNR*100,BER,LBER,FieldStrength,NCOValue);
	//printf("Carrier: %d,Mode: %d,Rate: %d,Interleave: %d,PN: %d,PNVariable %d",Carrier,Mode,Rate,InterleaverLength,PnMode,PnVariable);
	if(locked&0x01)	return TRUE;

	if(err)	return FALSE;

	return FALSE;
}

/************************************
** 设置有线情况下的信号模式： 
**	HDIC2311_CABLE_16QAM,			
**	HDIC2311_CABLE_32QAM,			
**	HDIC2311_CABLE_64QAM,			
**	HDIC2311_CABLE_128QAM,			
**	HDIC2311_CABLE_256QAM			
*************************************/
UINT8 HDIC2311_Cable_SetMode(UINT8 Mode)
{
	UINT8 err = HDIC_NO_ERROR;
	
	err = HDIC2311_WriteRegister(0x0170,Mode);

	return err;
}

/************************************
** 设置有线情况下的符号率： 
** Rate:单位K, 如6975或6900
*************************************/
UINT8 HDIC2311_Cable_SetRate(UINT16 Rate)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT32 Value=0;

	Value = Rate;
	Value *= 4000;

	err = HDIC2311_WriteRegister(0x0130,(UINT8)((Value&0xFF000000)>>24));
	err = HDIC2311_WriteRegister(0x0131,(UINT8)((Value&0xFF0000)>>16));
	err = HDIC2311_WriteRegister(0x0132,(UINT8)((Value&0xFF00)>>8));
	err = HDIC2311_WriteRegister(0x0133,(UINT8)(Value&0xFF));
	return err;
}

/************************************
** 手动设置地面情况下信号格式
*************************************/
UINT8 HDIC2311_SetManualMode(UINT8 CarrierMode, UINT8 mode,UINT8 rate, UINT8 interleaverLength,UINT8 pnmode,UINT8 PnVariable)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData = 0;

	HDIC2311_Print0("------------Set Manual Mode !------------\n");

	/*配置为手动模式*/
	err = HDIC2311_WriteRegister(0x0002,0xFF);
	if(err)	return err;

	err = HDIC2311_ReadRegister(0x0003,&ReadData);
	if(err)	return err;

	ReadData &= 0xE8;
	ReadData |= pnmode;
	ReadData |= (PnVariable<<2);
	ReadData |= (CarrierMode<<4);
	err = HDIC2311_WriteRegister(0x0003,ReadData);
	HDIC2311_Print1("ReadData = %x!\n",ReadData);

	//HDIC2311_ReadRegister(0x0004,&ReadData);
	ReadData &= 0x88;
	ReadData |= mode;
	ReadData |= (rate<<4);
	ReadData |= (interleaverLength<<6);
	err = HDIC2311_WriteRegister(0x0004,ReadData);
	//HDIC2311_Print1(("0x0004  0x%02x !",ReadData));

	return err;	
}

/************************************
** 获取正常工作时的NCO
*************************************/
UINT8 HDIC2311_GetNCOValue(UINT32 *NCOValue)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData = 0;
	UINT8 WorkMode = 0;

	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);
	WorkMode &= 0x01;

	if(WorkMode == HDIC2311_DTMB_SELECT)
	{	
		err = HDIC2311_ReadRegister(0x0058,&ReadData);
		*NCOValue = ReadData;

		err = HDIC2311_ReadRegister(0x0059,&ReadData);
		*NCOValue <<= 8;
		*NCOValue |= ReadData;

		err = HDIC2311_ReadRegister(0x005A,&ReadData);
		*NCOValue <<= 8;
		*NCOValue |= ReadData;
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		err = HDIC2311_ReadRegister(0x0197,&ReadData);
		*NCOValue = ReadData;

		err = HDIC2311_ReadRegister(0x0198,&ReadData);
		*NCOValue <<= 8;
		*NCOValue |= ReadData;

		err = HDIC2311_ReadRegister(0x0199,&ReadData);
		*NCOValue <<= 8;
		*NCOValue |= ReadData;
	}
	HDIC2311_Print1("----------NCO %x----------\n",*NCOValue);
	return err;
}

/************************************
** 设置初始工作时的NCO
*************************************/
UINT8 HDIC2311_SetNCOValue(UINT32 NCOValue)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 temp1=0,temp2=0,temp3=0;
	UINT8 WorkMode = 0;

	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);
	if(err)	return err;
	WorkMode &= 0x01;

	temp1 = (UINT8)((NCOValue&0x00ff0000)>>16);
	temp2 = (UINT8)((NCOValue&0x0000ff00)>>8);
	temp3 = (UINT8)((NCOValue&0x000000ff));

	HDIC2311_Print3("Updage NCO %x%x%x\n",temp3,temp2,temp1);

	if(WorkMode == HDIC2311_DTMB_SELECT)
	{
		HDIC2311_WriteRegister(0x0028,temp1);
		HDIC2311_WriteRegister(0x0029,temp2);
		HDIC2311_WriteRegister(0x002A,temp3);
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		HDIC2311_WriteRegister(0x0111,temp1);
		HDIC2311_WriteRegister(0x0112,temp2);
		HDIC2311_WriteRegister(0x0113,temp3);
	}
	
	return err;
}

static double HDIC2311_ABS(double x)
{
    return (x < 0) ? -x : x;
}

/************************************
** 根据晶振和tuner中频计算NCO
*************************************/
UINT8 HDIC2311_CalculateNCOValue(double TunerIF,UINT8 CrystalSelect,UINT32 *NCOValue)
{
	UINT8 err = HDIC_NO_ERROR;
	double FrequencySample=0;
	double Temp;

	if(TunerIF == 0)
	{
		*NCOValue = 0;
		return err;
	}

	if(CrystalSelect == HDIC2311_CRYSTAL_27M )
	{
		FrequencySample = 30.375;
	}
	else if(CrystalSelect == HDIC2311_CRYSTAL_304M )
	{
		FrequencySample = 30.4;
	}
	else if(CrystalSelect == HDIC2311_CRYSTAL_24M )
	{
		FrequencySample = 30.75;
	}
	else if(CrystalSelect == HDIC2311_CRYSTAL_16M )
	{
		FrequencySample = 30.5;
	}

	Temp = HDIC2311_ABS(FrequencySample - TunerIF);
	if(Temp<TunerIF)
	{
		*NCOValue =(UINT32)(Temp/FrequencySample * 0x800000);
	}
	else
	{
		*NCOValue =(UINT32)(TunerIF/FrequencySample * 0x800000);
	}
	return err;
}

/************************************
** 获取地面实际信号的格式
*************************************/
UINT8 HDIC2311_GetAutoParameters(UINT8 *CarrierMode, UINT8 *pmode,
		UINT8 *prate, UINT8 *pinterleaverLength,UINT8 *Pnmode,UINT8 *PnVariable)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1,ReadData2;

	err = HDIC2311_ReadRegister(0x0005,&ReadData1);
	err = HDIC2311_ReadRegister(0x0006,&ReadData2);
	if(err)	return 0;
	
	*Pnmode = ReadData1&0x03;
	*PnVariable = ReadData1&0x04;
	*PnVariable >>= 2;
	*CarrierMode = ReadData1&0x10;
	*CarrierMode >>= 4;

	*pmode = ReadData2&0x07;
	*prate = ReadData2&0x30;
	*prate >>= 4;
	*pinterleaverLength = ReadData2&0x40;
	*pinterleaverLength >>= 6;

	return err;
}
/****************************************************************************
  Subject:    Function providing approx. result of Log10(X)
  Function:   Log10Approx
  Parmeter:   Operand X in float
  Return:     Approx. value of Log10(X) in float
  Remark:      Ouput range from 0.0, 0.3 to 9.6 (input 1 to 2^32)
*****************************************************************************/
double Log10Approx(double flt_x)
{
    U32        u32_temp = 1;
    U8        indx = 0;

    do 
    {
        u32_temp = u32_temp << 1;
        if (flt_x < (double)u32_temp)	break;
    }
    while (++indx < 32);

    // 10*log10(X) ~= 0.3*N, when X ~= 2^N
    return (double)0.3 * indx;
}

/****************************
多载波情况下，获取信噪比
****************************/
UINT8 HDIC2311_GetSignalSNRMC(double *SignalSNR)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0, ReadData2 = 0;
	UINT32 value_reg;

	err = HDIC2311_ReadRegister(0x02C9,&ReadData1);
	err = HDIC2311_ReadRegister(0x02C8,&ReadData2);
	if(err)	return 0;
	
	value_reg = ReadData1*256+ReadData2;
	if((value_reg!=0)&&(value_reg!=0xFFFF))
	{
		*SignalSNR = 10*Log10Approx((double)(value_reg)/16);
	}

	HDIC2311_Print1("------------SNR_MC %d -----------\n",(UINT8)(*SignalSNR));

	return err;
}

/****************************
单载波情况下，获取信噪比
****************************/
UINT8 HDIC2311_GetSignalSNRSC(double *SignalSNR)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0, ReadData2 = 0;
	UINT32 value_reg;
	UINT8 Pnmode;
	UINT32 PnValue = 0;

	err = HDIC2311_ReadRegister(0x0005,&ReadData1);
	if(err)	return 0;
	Pnmode = ReadData1&0x03;

	if(Pnmode == HDIC_PN_945)
	{
		PnValue = 945;
	}
	else if(Pnmode == HDIC_PN_595)
	{
		PnValue = 595;
	}
	else if(Pnmode == HDIC_PN_420)
	{
		PnValue = 420;
	}

	err = HDIC2311_ReadRegister(0x02A5,&ReadData1);
	err = HDIC2311_ReadRegister(0x02A4,&ReadData2);
	if(err)	return err;
	
	value_reg = ReadData1*256+ReadData2;
	if((value_reg!=0)&&(value_reg!=0xFFFF))
	{
		*SignalSNR = 10*Log10Approx(40.5*(double)(PnValue)/value_reg);
	}
	else
	{
		*SignalSNR = 0;
	}

	HDIC2311_Print1("-----------SNR_SC %d --------------\n",(UINT8)(*SignalSNR));
	return (err);
}

/****************************
获取信噪比
****************************/
UINT8 HDIC2311_GetSignalSNR(double *SignalSNR)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0;
	UINT8 CarrierMode;
	UINT8 WorkMode = 0;

	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);
	if(err)	return 0;
	WorkMode &= 0x01;
	
	if(WorkMode == HDIC2311_DTMB_SELECT)
	{
		err = HDIC2311_ReadRegister(0x0005,&ReadData1);
		if(err)	return 0;
		CarrierMode = ReadData1&0x10;
		CarrierMode >>= 4;

		if(CarrierMode == HDIC_CARRIER_SINGLE)
		{
			err = HDIC2311_GetSignalSNRSC(SignalSNR);
		}
		else if(CarrierMode == HDIC_CARRIER_MULTI)
		{
			err = HDIC2311_GetSignalSNRMC(SignalSNR);
		}
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		err = HDIC2311_GetCableSignalSNR(SignalSNR);
	}
	return err;
}

/****************************
有线信号情况下获取信噪比
****************************/
UINT8 HDIC2311_GetCableSignalSNR(double *SignalSNR)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0;

	err = HDIC2311_ReadRegister(0x0196,&ReadData1);
	if(err)	return 0;

	*SignalSNR = 37.35 - 10*Log10Approx((double)(ReadData1 + 1));
	
	return (err);
}

/****************************
有线信号情况下获取LDPC误码率
****************************/
UINT8 HDIC2311_GetCableLdpcBER(double *pLdpcBER)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0, ReadData2 = 0;

	err = HDIC2311_ReadRegister(0x0194,&ReadData1);
	err = HDIC2311_ReadRegister(0x0195,&ReadData2);
	if(err)	return 0;
	HDIC2311_Print2("------------Block BER 0x94,0x95: %02x,%02x------------\n",ReadData1,ReadData2);
	
	*pLdpcBER =(double)((double)(ReadData1*256+ReadData2)/65536);

	return (err);
}

/****************************
有线信号情况下获取误码率
****************************/
UINT8 HDIC2311_GetCableSignalBER (double *pSignalBER)
{
	UINT8 err = HDIC_NO_ERROR; 
	UINT8 ReadData1 = 0, ReadData2 = 0,ReadData3 = 0;

	err = HDIC2311_ReadRegister(0x0191,&ReadData1);
	err = HDIC2311_ReadRegister(0x0192,&ReadData2);
	err = HDIC2311_ReadRegister(0x0193,&ReadData3);
	if(err)	return 0;

	HDIC2311_Print3("------------BER 0x91,0x92,0x93: %02x,%02x,%02x---------------\n",ReadData1,ReadData2,ReadData3);
	*pSignalBER = (double)((double)((ReadData1%0x0f)*65536+ReadData2*256+ReadData3)/96468992);

	return (err);
}

/****************************
地面信号情况下获取LDPC误码率
****************************/
UINT8 HDIC2311_GetLdpcBER(double *pLdpcBER)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0, ReadData2 = 0;
	UINT8 WorkMode = 0;

	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);
	if(err)	return 0;
	WorkMode &= 0x01;
	
	if(WorkMode == HDIC2311_DTMB_SELECT)
	{
		err = HDIC2311_ReadRegister(0x00AA,&ReadData1);
		err = HDIC2311_ReadRegister(0x00A9,&ReadData2);
		if(err)	return 0;
	
		*pLdpcBER = (double)((ReadData2&0x0f)*256+ReadData1)/4096;
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		err = HDIC2311_GetCableLdpcBER(pLdpcBER);
	}
	return (err);
}

/****************************
地面信号情况下获取误码率
****************************/
UINT8 HDIC2311_GetSignalBER (double *pSignalBER)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0, ReadData2 = 0;
	UINT8 WorkMode = 0;

	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);
	if(err)	return 0;
	WorkMode &= 0x01;
	
	if(WorkMode == HDIC2311_DTMB_SELECT)
	{
		err = HDIC2311_ReadRegister(0x00A7,&ReadData1);
		err = HDIC2311_ReadRegister(0x00A8,&ReadData2);
		if(err)	return 0;

		*pSignalBER = (double)(ReadData1*256+ReadData2)/6666664;
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		err = HDIC2311_GetCableSignalBER(pSignalBER);
	}
	return (err);
}
/****************************
地面信号情况下获取信号场强
****************************/
UINT8 HDIC2311_GetFieldStrength(UINT32 *FieldStrength)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData1 = 0, ReadData2 = 0;

	err = HDIC2311_ReadRegister(0x0061,&ReadData1);
	err = HDIC2311_ReadRegister(0x0062,&ReadData2);
	if(err)	return 0;
	
	*FieldStrength = (UINT16)(ReadData1*256 + ReadData2);

	HDIC2311_Print1("---------------FieldStrength %d--------------\n",*FieldStrength);
	
	return (err);
}
/****************************
地面信号情况下获取TimingRecovery
****************************/
UINT8 HDIC2311_GetTimingRecovery(UINT32 *ControlWord)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData = 0;

	err = HDIC2311_ReadRegister(0x005C,&ReadData);
	if(err)	return err;
	*ControlWord = ReadData;

	err = HDIC2311_ReadRegister(0x005D,&ReadData);
	if(err)	return err;
	*ControlWord <<= 8;
	*ControlWord |= ReadData;

	err = HDIC2311_ReadRegister(0x005E,&ReadData);
	if(err)	return err;
	*ControlWord <<= 8;
	*ControlWord |= ReadData;

	err = HDIC2311_ReadRegister(0x0060,&ReadData);
	if(err)	return err;
	*ControlWord <<= 8;
	*ControlWord |= ReadData;
	HDIC2311_Print1("----------------ControlWord %x------------\n",(*ControlWord));

	return (err);
}

/************************************
** 芯片软复位
*************************************/
UINT8 HDIC2311_SoftReset(void)
{
	UINT8 err = HDIC_NO_ERROR;
//	UINT8 ReadData = 0,ReadData1=0;
	UINT8 WorkMode = 0;

	/*获取工作模式,DTMB或Cable*/
	err = HDIC2311_ReadRegister(0x0001,&WorkMode);

	if (err) return err;
	
	WorkMode &= 0x01;
	
	if(WorkMode == HDIC2311_DTMB_SELECT)
	{
		err = HDIC2311_WriteRegister(0x0009,0x10);
		HDIC2311_Wait(10); /* wait 1 ms */
		err = HDIC2311_WriteRegister(0x0009,0x00);	
	}
	else if(WorkMode == HDIC2311_CABLE_SELECT)
	{
		err = HDIC2311_WriteRegister(0x0103,0x01);
		HDIC2311_Wait(10); /* wait 10 ms */
		err = HDIC2311_WriteRegister(0x0103,0x00);
	}
	return (err);
}

/************************************
** 设置tuner类型，
** 零中频HDIC_TUNER_ZERO_IF
** 或其他
*************************************/
UINT8 HDIC2311_SetTunerType(UINT8 Type)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 ReadData = 0;
	
	err = HDIC2311_ReadRegister(0x0007,&ReadData);

	if (err) return err;
		
	if(Type==HDIC_TUNER_ZERO_IF)
	{
		ReadData|=0x20;
	}
	else
	{
		ReadData&=0xDF;
	}
	err = HDIC2311_WriteRegister(0x0007,ReadData);

	return (err);
}
/************************************
** 设置TS的输出格式
*************************************/
UINT8 HDIC2311_SetTsFormat(UINT8 Serial, UINT8 CLK_Polarity, UINT8 CLK_Valid, UINT8 Null_Packet, UINT8 Serial_Output)
	{
		UINT8 err = HDIC_NO_ERROR;
		UINT8 ReadData = 0,WriteData = 0;
	
		HDIC2311_ReadRegister(0x0007,&ReadData);
		WriteData = ReadData&0xE0;
	
		if(Serial==HDIC_TS_OUTPUT_SERIAL)
		{
			WriteData |= 0x01;
		}
	
		if(CLK_Polarity==HDIC_TS_DATA_SAMPLE_FALLING)
		{
			WriteData |= 0x02;
		}
		
		if(CLK_Valid==HDIC_TS_CLK_WITH_TSVLD)
		{
			WriteData |= 0x04;
		}	
	
		if(Null_Packet == HDIC_TS_NULLPACKET_DELETED )
		{
			WriteData |= 0x08;
		}
	
		if(Serial_Output == HDIC_TS_SERIAL_OUTPUT_D0)
		{
			WriteData |= 0x10;
		}
	
		HDIC2311_WriteRegister(0x0007,WriteData);
	
//		HDICTBX_Print(("TS Format 0x%02x\n",WriteData));	
	
		return (err);
	}


/****************************
打开I2C转发功能
****************************/
UINT8 HDIC2311_OpenTunerI2C(UINT8 Address)
{
	UINT8 err = HDIC_NO_ERROR;
//	UINT8 ReadData = 0;

	HDIC2311_Print1("--------------Set 2311 Tuner I2C Address 0x%x!!--------------\n",Address);
	Address &= 0xFE;
	err = HDIC2311_WriteRegister(0x000F,Address);
	err = HDIC2311_WriteRegister(0x000E,0x01);
	return (err);

}
/****************************
关闭I2C转发功能
****************************/
UINT8 HDIC2311_CloseTunerI2C(void)
{
	UINT8 err = HDIC_NO_ERROR;

	HDIC2311_Print0("------------2311 Close Tuner I2C!----------------");

	err = HDIC2311_WriteRegister(0x000E,0x00);

	return (err);
}


/********************************
获取信号强度
********************************/
UINT8 HDIC2311_GetSignalStrength(UINT16 *SignalStrength)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT32 FieldStrength;

	err = HDIC2311_GetFieldStrength(&FieldStrength);

	if(FieldStrength>=0x800)
		FieldStrength = 0x800;
	if(FieldStrength<=0x418)
		FieldStrength = 0x418;
	*SignalStrength = (0x800 - FieldStrength)/12; //注意!!!需要数值转换

	HDIC2311_Print1("------------SignalStrength %d !!!------------\n",*SignalStrength);
	
	return err;
}

/********************************
获取信号质量
********************************/
UINT8 HDIC2311_GetSignalQuality(UINT16 *SignalQuality)
{
	UINT8 err = HDIC_NO_ERROR;
	double SignalSNR;

	err = HDIC2311_GetSignalSNR(&SignalSNR);

	*SignalQuality = (UINT16)SignalSNR;
	(*SignalQuality) *= 3;
	if(*SignalQuality>=98)
	{
		*SignalQuality = 98;
	}
	HDIC2311_Print1("------------SignalQuality %d !!!-----------\n",*SignalQuality);
	return err;
}

/********************************
芯片初始化，在系统初始化时调用
********************************/
UINT8 HDIC2311_Init(void)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT32 NCOValue = 0;
	HDIC2311_Init_Info InitInfo;

	/*初始化配置HD2311*/
	InitInfo.WorkMode = HDIC2311_DTMB_SELECT;
	InitInfo.TunerType = HDIC_TUNER_NORMAL;//HDIC_TUNER_ZERO_IF;//yqx modify 2013-5-24
	/*高频头的中频，单位MHz，零中频高频头请直接赋值0*/
	InitInfo.TunerIF = 5;//4.57;//0; //yqx modify 2013-5-24
	InitInfo.CrystalSelect = HDIC2311_CRYSTAL_24M;
	InitInfo.TsType = HDIC_TS_OUTPUT_SERIAL;
	InitInfo.TsClockPolarity = HDIC_TS_DATA_SAMPLE_RISING;
	InitInfo.TsClockValid = HDIC_TS_CLK_ALWAYS;
	InitInfo.TsNullPacket = HDIC_TS_NULLPACKET_ENABLED;
	InitInfo.TsSerialOutPut = HDIC_TS_SERIAL_OUTPUT_D0;
	
	/*硬复位2311*/
	HDIC2311_HWReset();
	/*设置工作模式，地面或有线*/
	err = HDIC2311_SetWorkMode(InitInfo.WorkMode);
	/*设置tuner类型，零中频或其他*/
	err = HDIC2311_SetTunerType(InitInfo.TunerType);
	/*根据tuner IF和晶振计算NCO*/
	err = HDIC2311_CalculateNCOValue(InitInfo.TunerIF,InitInfo.CrystalSelect,&NCOValue);
	/*设置NCO*/
	err = HDIC2311_SetNCOValue(NCOValue);
	/*设置TS输出格式*/
	err = HDIC2311_SetTsFormat(InitInfo.TsType,InitInfo.TsClockPolarity,InitInfo.TsClockValid,InitInfo.TsNullPacket,InitInfo.TsSerialOutPut);
	
	return (err);
}

/********************************
地面信号时锁频函数
********************************/
UINT8 HDIC2311_DTMB_SetFrequency(UINT32 Frequency)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 CheckLockTemp,LockResult,status;
	BOOL SignalDetect = FALSE;
	
	/********************
	** 需要首先设置高频头
	********************/
//	HDIC2311_SetTuner(Frequency);

	Frequency = Frequency;
	
	HDIC2311_SetAutoMode();
	HDIC2311_SoftReset();

	for (CheckLockTemp=0; CheckLockTemp<50; CheckLockTemp++)
	{
	//    MApp_ProcessUserInput();
		LockResult = HDIC2311_IsDemodLocked(&status);
		HDIC2311_Wait(100); /* wait 100 ms */
		if(status > 0x20)
		{
			SignalDetect = TRUE;
		}
		if((SignalDetect == FALSE)&&(CheckLockTemp == 20))
		{
			printf("---> [2311] 2311 DTMB No Signal ----------\n");
			break;	
		}
		if (LockResult == 1)
		{
			printf("---> [2311] 2311 DTMB is locked --------------\n");
			break;
		}
	}
	return err;	
}

/********************************
有线信号时锁频函数
********************************/
UINT8 HDIC2311_Cable_SetFrequency(UINT32 Frequency, UINT8 CableMode, UINT16 CableRate)
{
	UINT8 err = HDIC_NO_ERROR;
	UINT8 CheckLockTemp,LockResult,status;

	/********************
	** 需要首先设置高频头
	********************/
//	HDIC2311_SetTuner(Frequency);
	Frequency = Frequency;
	
	/*设置信号参数*/
	HDIC2311_Cable_SetMode(CableMode);
	HDIC2311_Cable_SetRate(CableRate);
	HDIC2311_SoftReset();
	for (CheckLockTemp=0; CheckLockTemp<40; CheckLockTemp++)
	{
		LockResult = HDIC2311_IsDemodLocked(&status);
		HDIC2311_Wait(50); /* wait 50 ms */

		if (LockResult == 1)
		{
			HDIC2311_Print0("---> [2311] 2311 Cable is locked ---------------\n");
			break;
		}
	}
	return err;
}

