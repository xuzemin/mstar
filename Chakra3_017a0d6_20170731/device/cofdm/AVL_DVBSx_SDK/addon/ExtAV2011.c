/*****************************************************************************
* Tuner sample code
*
* History:
* Date Athor Version Reason
* ============ ============= ========= =================
* 1.Apr.29.2010 Version1.0
*****************************************************************************/
#include "Board.h"
#include "MsCommon.h"
//#include "HbCommon.h"
#if (FRONTEND_DEMOD_S2_TYPE == DEMOD_AVL6211)
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/IBase.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/II2C.h"
#include "AVL_DVBSx_SDK/BSP/IBSP.h"
#include "AVL_DVBSx_SDK/addon/ExtAV2011.h"


#define AV2011_R0_PLL_LOCK 0x01
#define AV2011_Tuner

static AVL_uint16 tuner_crystal = 27; //unit is MHz
static AVL_uchar auto_scan=0; //0 for normal mode, 1 for Blindscan mode
static void Time_DELAY_MS(AVL_uint32 ms);
 //Main function at tuner control
static AVL_DVBSx_ErrorCode Tuner_control(AVL_uint32 channel_freq,AVL_uint32 bb_sym,struct AVL_Tuner * pTuner);
// I2C write function ( start register, register array pointer, register length)
static AVL_DVBSx_ErrorCode AV2011_I2C_write(AVL_uchar reg_start,AVL_uchar* buff,AVL_uchar len,struct AVL_Tuner * pTuner);
static AVL_DVBSx_ErrorCode AV2011_I2C_Check(struct AVL_Tuner * pTuner);
AVL_uint16 AVL_DVBSx_AV2011_CalculateLPF(AVL_uint16 uiSymbolRate_10kHz);
AVL_DVBSx_ErrorCode ExtAV2011_RegInit(struct AVL_Tuner * pTuner);

AVL_DVBSx_ErrorCode AVL_DVBSx_ExtAV2011_GetLockStatus(struct AVL_Tuner * pTuner)
{
	AVL_DVBSx_ErrorCode r;
	AVL_uchar uilock;

	//Send register address
		r = AVL_DVBSx_II2CRepeater_GetOPStatus(pTuner->m_pAVLChip);
		if( AVL_DVBSx_EC_OK != r )
		{
			return(r);
		}
		AVL_DVBSx_IBSP_Delay(1);
		r = AVL_DVBSx_II2CRepeater_ReadData_Multi(  pTuner->m_uiSlaveAddress, &uilock, 0x0B, 1, pTuner->m_pAVLChip );
		if( AVL_DVBSx_EC_OK == r )
		{
			if( 0 == (uilock & AV2011_R0_PLL_LOCK) )
			{
				r = AVL_DVBSx_EC_Running;
			}
		}
	return(r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_ExtAV2011_Initialize(struct AVL_Tuner * pTuner) {
       printf("Javy --- AVL_DVBSx_ExtAV2011_Initialize!!!\n");
       AVL_DVBSx_ErrorCode r;

       r = AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_slave_addr_addr, pTuner->m_uiSlaveAddress);
       r |= AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_use_internal_control_addr, 0);
       r |= AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_LPF_margin_100kHz_addr, 0);	//clean up the LPF margin for blind scan. for external driver, this must be zero.
       r |= AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_max_LPF_100kHz_addr, 360);	//set up the right LPF for blind scan to regulate the freq_step. This field should corresponding the flat response part of the LPF.
       r |= AVL_DVBSx_II2CRepeater_Initialize(pTuner->m_uiI2CBusClock_kHz, pTuner->m_pAVLChip);
       r |= AV2011_I2C_Check(pTuner);
       r |= ExtAV2011_RegInit(pTuner);
       return(r);
}

/********************************************************************************
* INT32 Tuner_control(AVL_uint32 channel_freq, AVL_uint32 bb_sym)
*
* Arguments:
* Parameter1: AVL_uint32 channel_freq : Channel freqency
* Parameter2: AVL_uint32 bb_sym : Baseband Symbol Rate
*
* Return Value: INT32 : Result
*****************************************************************************/
AVL_DVBSx_ErrorCode ExtAV2011_RegInit(struct AVL_Tuner * pTuner)
{
	AVL_uchar reg[50];
	AVL_uchar reg_start;
	AVL_DVBSx_ErrorCode r;
	// Register initial flag
	//when sym is 0 or 45000, means auto-scan channel.
	// At Power ON, tuner_initial = 0
	// do the initial if not do yet.
		//Tuner Initail registers R0~R41
		reg[0]=(char) (0x38);
		reg[1]=(char) (0x00);
		reg[2]=(char) (0x00);
		reg[3]=(char) (0x50);
		reg[4]=(char) (0x1f);
		reg[5]=(char) (0xa3);
		reg[6]=(char) (0xfd);
		reg[7]=(char) (0x58);
		reg[8]=(char) (0x0e);
		reg[9]=(char) (0xc2);//0x82 change into 0xc2- Fixed crystal issue
		reg[10]=(char) (0x88);
		reg[11]=(char) (0xb4);
		reg[12]=(char) (0xd6); //RFLP=ON at Power on initial
		reg[13]=(char) (0x40);
#ifdef AV2011_Tuner
		reg[14]=(char) (0x94);
		reg[15]=(char) (0x9a);
#else
		reg[14]=(char) (0x5b);
		reg[15]=(char) (0x6a);
#endif
		reg[16]=(char) (0x66);
		reg[17]=(char) (0x40);
		reg[18]=(char) (0x80);
		reg[19]=(char) (0x2b);
		reg[20]=(char) (0x6a);
		reg[21]=(char) (0x50);
		reg[22]=(char) (0x91);
		reg[23]=(char) (0x27);
		reg[24]=(char) (0x8f);
		reg[25]=(char) (0xcc);
		reg[26]=(char) (0x21);
		reg[27]=(char) (0x10);
		reg[28]=(char) (0x80);
		reg[29]=(char) (0x02);
		reg[30]=(char) (0xf5);
		reg[31]=(char) (0x7f);
		reg[32]=(char) (0x4a);
		reg[33]=(char) (0x9b);
		reg[34]=(char) (0xe0);
		reg[35]=(char) (0xe0);
		reg[36]=(char) (0x36);
		//monsen 20080710. Disble FT-function at Power on initial
		//reg[37]=(char) (0x02);
		reg[37]=(char) (0x00);
		reg[38]=(char) (0xab);
		reg[39]=(char) (0x97);
		reg[40]=(char) (0xc5);
		reg[41]=(char) (0xa8);
		//monsen 20080709. power on initial at first "Tuner_control()" call
		// Sequence 1
		// Send Reg0 ->Reg11
		reg_start = 0;
		r =  AV2011_I2C_write(reg_start,reg,12,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
			return(r);
		}
		// Time delay 1ms
		Time_DELAY_MS(1);
		// Sequence 2
		// Send Reg13 ->Reg24
		reg_start = 13;
		r = AV2011_I2C_write(reg_start,reg+13,12,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
			return(r);
		}
		// Send Reg25 ->Reg35
		reg_start = 25;
		r = AV2011_I2C_write(reg_start,reg+25,11,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
			return(r);
		}
		// Send Reg36 ->Reg41
		reg_start = 36;
		r = AV2011_I2C_write(reg_start,reg+36,6,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
			return(r);
		}
		// Time delay 1ms
		Time_DELAY_MS(1);
		// Sequence 3
		// send reg12
		reg_start = 12;
		r = AV2011_I2C_write(reg_start,reg+12,1,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
			return(r);
		}
		//monsen 20081125, Wait 100 ms
		Time_DELAY_MS(100);
		//monsen 20081030, Reinitial again
		{
			// Sequence 1
			// Send Reg0 ->Reg11
			reg_start = 0;
			r = AV2011_I2C_write(reg_start,reg,12,pTuner);
			if(r!=AVL_DVBSx_EC_OK){
			return(r);
			}
			// Time delay 1ms
			Time_DELAY_MS(1);
			// Sequence 2
			// Send Reg13 ->Reg24
			reg_start = 13;
			r = AV2011_I2C_write(reg_start,reg+13,12,pTuner);
			if(r!=AVL_DVBSx_EC_OK){
			return(r);
		    }
			// Send Reg25 ->Reg35
			reg_start = 25;
			r = AV2011_I2C_write(reg_start,reg+25,11,pTuner);
			if(r!=AVL_DVBSx_EC_OK){
			return(r);
		    }
			// Send Reg36 ->Reg41
			reg_start = 36;
			r = AV2011_I2C_write(reg_start,reg+36,6,pTuner);
			if(r!=AVL_DVBSx_EC_OK){
			return(r);
			}
			// Time delay 1ms
			Time_DELAY_MS(1);
			// Sequence 3
			// send reg12
			reg_start = 12;
			r = AV2011_I2C_write(reg_start,reg+12,1,pTuner);
			if(r!=AVL_DVBSx_EC_OK){
			return(r);
			}
		Time_DELAY_MS(50);
		return(r);
	}
}


//Wake_Up = 0 Power_Down = 1
void Tuner_Set_PD (AVL_uint32 val, struct AVL_Tuner * pTuner)
{
       AVL_uchar reg12 = 0 ;

       reg12 = (0xd6 & 0xDF) | (val << 5);

       printf("Javy Set Reg12 : 0x%x\n",reg12);

       AV2011_I2C_write(12, &reg12,1,pTuner);
        /* Time delay ms*/
       Time_DELAY_MS(5);
}


AVL_DVBSx_ErrorCode Tuner_control(AVL_uint32 channel_freq, AVL_uint32 bb_sym, struct AVL_Tuner * pTuner)
{
	AVL_uchar reg[50];
	AVL_uint32 fracN;
	AVL_uint32 BW;
	AVL_uint32 BF;
	AVL_DVBSx_ErrorCode r;
	//AVL_uchar auto_scan = 0;// Add flag for "’ßÌ¨"
	// Register initial flag;

	//when sym is 0 or 45000, means auto-scan channel.
	if (bb_sym == 0 || bb_sym == 45000) //auto-scan mode
	{
		auto_scan = 1;
	}
	Time_DELAY_MS(50);
   	fracN = (channel_freq + tuner_crystal/2)/tuner_crystal;
   	if(fracN > 0xff)
   	fracN = 0xff;
   	reg[0]=(char) (fracN & 0xff);
   	fracN = (channel_freq<<17)/tuner_crystal;
   	fracN = fracN & 0x1ffff;
   	reg[1]=(char) ((fracN>>9)&0xff);
   	reg[2]=(char) ((fracN>>1)&0xff);
   	// reg[3]_D7 is frac<0>, D6~D0 is 0x50
   	reg[3]=(char) (((fracN<<7)&0x80) | 0x50); // default is 0x50
   	// Channel Filter Bandwidth Setting.
   	//"sym" unit is Hz;
   	if(auto_scan)//’ßÌ¨ requested by BB
   	{
   		reg[5] = 0xA3; //BW=27MHz
   	}
   	else
   	{
   		// rolloff is 35%
   		BW = bb_sym*135/200;
   		// monsen 20080726, BB request low IF when sym < 6.5MHz
   		// add 6M when Rs<6.5M,
   		if(bb_sym<6500)
   		{
   			BW = BW + 6000;
   		}
   			// add 2M for LNB frequency shifting
   		BW = BW + 2000;
   			// add 8% margin since fc is not very accurate
   		BW = BW*108/100;
   			// Bandwidth can be tuned from 4M to 40M
   		if( BW< 4000)
   		{
   			BW = 4000;
   		}
   		if( BW> 40000)
   		{
   			BW = 40000;
   		}
   		BF = (BW*127 + 21100/2) / (21100); // BW(MHz) * 1.27 / 211KHz
   		reg[5] = (AVL_uchar)BF;
   	}
   	// Sequence 4
   	// Send Reg0 ->Reg4
   	Time_DELAY_MS(5);
   	r = AV2011_I2C_write(0,reg,4,pTuner);
   	if(r!=AVL_DVBSx_EC_OK)
      {
           return(r);
      }
	Time_DELAY_MS(5);
	// Sequence 5
	// Send Reg5
	r = AV2011_I2C_write(5, reg+5, 1,pTuner);
	if(r!=AVL_DVBSx_EC_OK)
      {
            return(r);
      }
	Time_DELAY_MS(5);
	// Fine-tune Function Control
	//Tuner fine-tune gain function block. bit2.
	//not auto-scan case. enable block function. FT_block=1, FT_EN=1
	if (!auto_scan)
	{
		reg[37] = 0x06;
		r = AV2011_I2C_write(37, reg+37, 1,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
		return(r);
		}
		Time_DELAY_MS(5);
		//Disable RFLP at Lock Channel sequence after reg[37]
		//RFLP=OFF at Lock Channel sequence
		// RFLP can be Turned OFF, only at Receving mode.
		reg[12] = 0x96 + ((1)<<6);	//Loop through
		//reg[12] = 0x96;
		r = AV2011_I2C_write(12, reg+12, 1,pTuner);
		if(r!=AVL_DVBSx_EC_OK){
		return(r);
		Time_DELAY_MS(5);
		}
	}
	return r;
}
static void Time_DELAY_MS(AVL_uint32 ms)
{
	AVL_DVBSx_IBSP_Delay(ms);
}

AVL_uint16 AVL_DVBSx_AV2011_CalculateLPF(AVL_uint16 uiSymbolRate_10kHz) {
	AVL_int32 lpf = uiSymbolRate_10kHz;
	//lpf *= 81;
	//lpf /= 100;
	//lpf += 500;
	return((AVL_uint16)lpf);
}

static AVL_DVBSx_ErrorCode AV2011_I2C_write(AVL_uchar reg_start,AVL_uchar* buff,AVL_uchar len,struct AVL_Tuner * pTuner)
{
	AVL_DVBSx_ErrorCode r=0;
	AVL_uchar ucTemp[2];
	int i,uiTimeOut=0;
	AVL_DVBSx_IBSP_Delay(5);

      for(i = 0; i < len; i ++)
      {
             ucTemp[0] = reg_start+i;
             r = AVL_DVBSx_II2CRepeater_GetOPStatus( pTuner->m_pAVLChip);
             while( r != AVL_DVBSx_EC_OK)
             {
                if( uiTimeOut++>200)
                {
                     break;
                }
                AVL_DVBSx_IBSP_Delay(1);
                r = AVL_DVBSx_II2CRepeater_GetOPStatus( pTuner->m_pAVLChip);
             }
             ucTemp[1]=*(buff+i);
             r = AVL_DVBSx_II2CRepeater_SendData(pTuner->m_uiSlaveAddress,ucTemp, 2, pTuner->m_pAVLChip );
             if(r != AVL_DVBSx_EC_OK)
             {
                 return(r);
             }
      }
	AVL_DVBSx_IBSP_Delay(5);
	return(r);
}

static AVL_DVBSx_ErrorCode AV2011_I2C_Read(AVL_uchar regAddr,AVL_uchar* buff,struct AVL_Tuner * pTuner)
{
	AVL_DVBSx_ErrorCode r=0;
	int uiTimeOut=0;
	UNUSED(regAddr);
	r = AVL_DVBSx_II2CRepeater_GetOPStatus( pTuner->m_pAVLChip );
	while( r != AVL_DVBSx_EC_OK)
	{
		if( uiTimeOut++>200)
		{
			break;
		}
		AVL_DVBSx_IBSP_Delay(1);
		r = AVL_DVBSx_II2CRepeater_GetOPStatus( pTuner->m_pAVLChip );
	}
	r = AVL_DVBSx_II2CRepeater_ReadData_Multi(pTuner->m_uiSlaveAddress, buff, 0x00, 1, pTuner->m_pAVLChip);
	if(r != AVL_DVBSx_EC_OK)
	{
		return(r);
	}
	return(r);
}

static AVL_DVBSx_ErrorCode AV2011_I2C_Check(struct AVL_Tuner * pTuner)
{
      AVL_uchar regValue,AV2011_address;

      AV2011_address = 0xC0;
      do
      {
          pTuner->m_uiSlaveAddress = AV2011_address;
          AVL_DVBSx_II2C_Write16(pTuner->m_pAVLChip, rc_tuner_slave_addr_addr, pTuner->m_uiSlaveAddress);
          regValue=(char) (0x38);
          if(AV2011_I2C_write(0,&regValue,1,pTuner) == AVL_DVBSx_EC_OK)
          {
               regValue = 0;
               if(AV2011_I2C_Read(0,&regValue,pTuner) == AVL_DVBSx_EC_OK)
               {
                     if(regValue == 0x38)
                     {
                         break;
                     }
               }
          }
          AV2011_address += 0x02;
      }while(AV2011_address <= 0xC6);
      if(AV2011_address > 0xC6)
      {
           printf("\n Not find tuner slave address");
           AV2011_address = tuner_slave_address;
      }
      pTuner->m_uiSlaveAddress = AV2011_address;
      printf("\n Tuner slave address = 0x%X\n",AV2011_address);
      return AVL_DVBSx_EC_OK;
}
AVL_DVBSx_ErrorCode AVL_DVBSx_ExtAV2011_Lock(struct AVL_Tuner * pTuner)
{
	AVL_DVBSx_ErrorCode r;

	r = Tuner_control((AVL_uint32)((pTuner->m_uiFrequency_100kHz)/10), (AVL_uint32)((pTuner->m_uiLPF_100kHz)*100), pTuner);
	return(r);
}
#endif

