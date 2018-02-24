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
 /*****************************************************************************
Copyright 2009, AltoBeam Inc. All rights reserved.

File Name: atbm883x.c

Version: 2.1

Description: Example programming interface for ATBM8830,ATBM8831

Important funtions:
ATBMInit()
           This funtion initializes the demodulator, all related configurations
           are included.

ATBMLockedFlag()
           This function checks the demodulator locking status

ATBMSignalQuality()
           This function evaluates signal quality
******************************************************************************/


#include <stdio.h>
#include "atbm883x.h"
#include <math.h>

//#define ATBM_DEBUG         /*default no debug output*/
u_int8  ATBMSlaveAddr=0x80;   /*either 0x80 or 0x88 */
u_int8  ATBM_SOFTWARE_VERSION = 21; /*SW guide version*/
static struct custom_config_t custom_config;

 /****************************************************************************

    The following are APIs users need to implement based on their platform.

 ****************************************************************************/
/* static int I2CWrite(u_int8 I2CSlaveAddr, u_int8 *data, int length)
  {
    //I2C write, please port this function
     MDrv_IIC_WriteBytes(ATBMSlaveAddr,1,&I2CSlaveAddr,length,data);
     return 1;
  }

static int  I2CRead(u_int8 I2CSlaveAddr, u_int8 *data, int length)
  {
      // I2C read,please port this function
      MDrv_IIC_ReadBytes(ATBMSlaveAddr,1,&I2CSlaveAddr,length,data);
         return 1;
  }
*/

static void DemodHardwareReset(void) {

     //to do
     mdrv_gpio_set_low(BALL_H6);
     msAPI_Timer_Delayms(10);
     mdrv_gpio_set_high(BALL_H6);
 }


static void Delayms (int ms) {

    // to do
     msAPI_Timer_Delayms(ms);
 }


 /****************************************************************************
Function:       ATBMInit
Parameters:     none
Return:         none
Description:
    Initialize ATBM883x demodulator and configure all necessary registers.
    the demodulator will start processing incoming data after this function is called.

    This function includes Software Reset and demodulator configuration:
       1. Demodulator reset
       2. Demodulator configuration
       3. Configuration done confirm
******************************************************************************/
void ATBMInit(void)
{
     u_int8 config_done = 0x01;
     u_int8 debug_bus = 0xFF;

    /* Configure the tuner according the hardware,select the tuner types
     * options:
     *      TUNER_SHARP,TUNER_ENV59M01D8F ,TUNER_ALPS_TDAD ,TUNER_ALPS_TDAC ,
     *      TUNER_MAX2165 ,TUNER_ADMTV102 ,TUNER_MXL5003S
     */
     custom_config.tuner_config.tuner_type = TUNER_SHARP2093;


    /* The IF output frequency of the Tuner, according the configuration of the tuner,
     * options:
     *       TUNER_IF_FREQ_36_DOT_166_M ,TUNER_IF_FREQ_36_M ,
     *       TUNER_IF_FREQ_36_DOT_125_M ,TUNER_IF_FREQ_0_M
     */
     custom_config.tuner_config.IF_Frequency = TUNER_IF_FREQ_36_M;


    /* Applied to ZIP silcion tuner only, use the default configuration;
     * NO_SWAP_IQ is for silicon tuner,depends on the hardware design,
     * options:NO_SWAP_IQ, SWAP_IQ, default: NO_SWAP_IQ
     */
     custom_config.tuner_config.IQ_mode = NO_SWAP_IQ;


    /* Configure the TS stream interface of the demod
     * select the TS stream output in parallel or serial mode,
     * options:TS_PARALLEL_MODE, TS_SERIAL_MODE,
     */
     custom_config.ts_mode.TS_Transfer_Type = TS_PARALLEL_MODE;




     /* Select the TS stream data output alignment wth clock edge: rising edge or on falling edge.
      * options:TS_OUTPUT_FALLING_EDGE, TS_OUTPUT_RISING_EDGE
      */
      custom_config.ts_mode.output_edge = TS_OUTPUT_FALLING_EDGE;



     /* Configure the output of the TS stream clock pattern: free-running or runinng at only when data is valid.
      * options: TS_CLOCK_CONST_OUTPUT, TS_CLOCK_VALID_OUTPUT
      */
      custom_config.ts_mode.SPI_clock_constant_output = TS_CLOCK_CONST_OUTPUT;



     /* Configure the clock source of the demod
      * select  whether the crystal or the oscillator is used for the clock source of the demod.
      * options: CRYSTAL , OSCILLATOR
      */
      custom_config.CRYSTAL_OR_OSCILLATOR = CRYSTAL;



     /* Select the clock source frequency for the demod. For now,
      * two frequencies are supported,option: CLK_30_DOT_4_M , CLK_28_DOT_6363_M
        please contact FAE if need to support other frequencies.
      */
      custom_config.sample_clk_Frequency = CLK_30_DOT_4_M;



     /* Configure the mobile or static mode according your requirement
      * using in the moving or static situation,option:STATIC_RECEIVING,MOBILE_RECEIVING
      */
      custom_config.receiving_mode= STATIC_RECEIVING;


      ATBMReset(custom_config.CRYSTAL_OR_OSCILLATOR);
      Delayms(10); /*10 ms*/


      ATBMConfig( custom_config);
      ATBMWrite(0x04, 0xA1, &debug_bus);//This will make LOCK and Block_Err signal hooked up to Debug Bus//
      ATBMWrite(0x04, 0xA2, &debug_bus);
     /* All config is done. This will start the DSP processing*/
      ATBMWrite(0x00, 0x04, &config_done);
}



/****************************************************************************
Function:       ATBMChipID
Parameters:     none
Return:         ChipID
Description:
     This function Check ATBM chip ID
     the chip ID of ATBM883x is 0x10
******************************************************************************/
u_int8 ATBMChipID(void)
{
  u_int8 chipID;
  ATBMRead(0x00, 0x00, &chipID);
  printf("chip ID= 0x%x, chipID should be 0x10 or there must have I2C error\n",chipID);
  return chipID;
}


 /****************************************************************************
Function:       ATBMConfig
Parameters:  custom_config_t
Return:         none
Description:
     Set registers for customer's configuration
     this function configure ATBM883x
 ******************************************************************************/
 void ATBMConfig(struct custom_config_t cus_cfg)
 {

    u_int8  dsp_reset;

    /*Demodulator default configure 30.4MHz; Tuner IF 36.166Mhz*/
    ATBMSetOSC(cus_cfg.tuner_config,cus_cfg.sample_clk_Frequency);

   /*set demod AGC control range for defferent tuner*/
    ATBMTunerAGC(cus_cfg.tuner_config.tuner_type);

    /*configure  MPEG TS output  mode*/
    ATBMSetTSMode(cus_cfg.ts_mode);

   if(cus_cfg.receiving_mode == STATIC_RECEIVING)
     {
       ATBM_Static_channel();
     }

   if(cus_cfg.receiving_mode == MOBILE_RECEIVING)
	{
        ATBM_Mobile_channel();
	}

    dsp_reset = 0;
    ATBMWrite(0x00,0x0A, &dsp_reset);

    ATBMWrite(0x02, 0x0c, &ATBM_SOFTWARE_VERSION);
 }




/****************************************************************************
Function:    ATBMReset
Parameters:  cry_or_osc
Return:      none
Description:
     This function Reset ATBM883x demodulator:
 ******************************************************************************/
void ATBMReset(u_int8 cry_or_osc)
{

    u_int8 HardwareState;

    u_int8 loop;

    ATBMRead(0x06, 0x07, &HardwareState);

        /*
	 * After hardware reset correctly,
	 * HardwareState should be 0x05 when using crystal,
	 * HardwareState should be 0x07 when using oscillator.
        */

	if(cry_or_osc==CRYSTAL)
	{
	       for(loop=0; loop<10; loop++)
	      {
			  if(HardwareState!=0x05)
			  {
				    DemodHardwareReset();
				    Delayms(100);
				    ATBMRead(0x06, 0x07, &HardwareState);
			  }
			  else
			  {
			           break;
			  }
	       }
	}

	if(cry_or_osc==OSCILLATOR)
	{
	      for(loop=0; loop<10; loop++)
	      {
		        if(HardwareState!=0x07)
		        {
				    DemodHardwareReset();
				    Delayms(100);
				    ATBMRead(0x06, 0x07, &HardwareState);
		        }
		        else
		        {
			         break;
		        }
	      	}
	 }

}


/****************************************************************************
Function:       ATBMSetTSMode
Parameters:  ts_mode
Return:         none
Description:
     This function configure Transport stream interface mode:
******************************************************************************/
void ATBMSetTSMode(struct MPEG_TS_mode_t ts_mode)
{
    u_int8 SerialEnabled =0x0;/*parallel clock out */
    u_int8 ClockOutSelect=0x0;/*disable serial TS mode */

    u_int8 TSOutputEdegeMode =ts_mode.output_edge;
    u_int8 TsClockMode = ts_mode.SPI_clock_constant_output;

    /*0x00: SPI data aligns with rising edge of TSBCLK; 0x01: SPI data aligns with falling edge of TSBCLK*/
    ATBMWrite(0x03,0x01, &TSOutputEdegeMode);
    ATBMWrite(0x03,0x06, &TsClockMode);  /*either free running or only active when data is valid*/



    if(ts_mode.TS_Transfer_Type==TS_SERIAL_MODE)
      {
    	ClockOutSelect = 0x01;  /*serial clock out */
    	SerialEnabled = 0x01;    /*enable serial TS mode */


       /* 0x01: For Serial mode, data always aligns with falling edge by design*/
        TSOutputEdegeMode = 0x01;
    	ATBMWrite(0x03,0x01, &TSOutputEdegeMode);


        /*0:disable serial mode; 1: enable serial mode */
    	ATBMWrite(0x03,0x05, &SerialEnabled);

    	 /*0: SPI clock output  1: TS serial clock output */
    	ATBMWrite(0x03,0x0b, &ClockOutSelect);

      }
    else
	 {
	   ClockOutSelect = 0x00;  /*SPI clock out */

          /*0: disable serial mode; 1:enable serial mode */
            ATBMWrite(0x03,0x05, &SerialEnabled);

           /*0: SPI clock output  1: TS serial clock output */
	   ATBMWrite(0x03,0x0b, &ClockOutSelect);
	 }
}


/****************************************************************************
Function:       ATBMSetOSC
Parameters:  tuner_config_t, sample_clk_Frequency
Return:         1 for success
                    0 for error
Description:
     This function configure ATBM883x according to external Clock source
     and  Tuner IF frequency.
 ******************************************************************************/
int ATBMSetOSC(struct tuner_config_t tuner_config, u_int8 sample_clk_Frequency)
{
    /* The following listed register configuration are for 28.6363 crystal
     * Demodulator default registers are for 30.4M crystal, no need to list here
     */
    u_int8  u8RXFLT[6]={0xCA,0xBE,0x69,0x5D,0x12,0xF};
    u_int8 tuner_if_frequency = tuner_config.IF_Frequency;
    u_int8 CLK_Freq = sample_clk_Frequency;

    u_int8 silicon_tuner_on= 0;
    u_int8 ADC_config= 0x16;
    u_int8 swap_iq;

 /*
  * 0x0A03~0x0A05 only related with sample frequency; default is for 30.4Mhz;
  * if sample freqency  is 28.6363Mhz,we need to reconfigure these three registers.
  */
     if(CLK_Freq == CLK_28_DOT_6363_M)
    {
        ATBMWrite(0x0A,0x03, &u8RXFLT[3]);
    	ATBMWrite(0x0A,0x04, &u8RXFLT[4]);
    	ATBMWrite(0x0A,0x05, &u8RXFLT[5]);
    }
	if(tuner_config.IQ_mode == SWAP_IQ)
	 	{
		swap_iq = 0x03;
		ATBMWrite(0x0c,0x01, &swap_iq);
	 	}

  /*
  * 0x0A00~0x0A02  related with sample frequency and tuner IF frequency.
  */
   if(tuner_if_frequency==TUNER_IF_FREQ_0_M)
   {
        /*tuner select .0: ZIF silicon tuner, 1: IF tuner*/
        ATBMWrite(0x00,0x01, &silicon_tuner_on);

        /*ADC config*/
        ATBMWrite(0x06,0x02, &ADC_config);
	     return 1;
   }
   else
   {
       if(CLK_Freq == CLK_30_DOT_4_M)
        {
                 /*Default for OSC:30.4, Tuner IF 36.166,so we do nothing*/
	           if(tuner_if_frequency  == TUNER_IF_FREQ_36_DOT_166_M)
	           {
		       return 1;
	           }

		    /*for tuner IF 36Mhz or 36.125Mhz,need to reconfigure these three registers*/
		     if(tuner_if_frequency  == TUNER_IF_FREQ_36_M)
		       {
		         u8RXFLT[0] = 0x50;
		         u8RXFLT[1] = 0x13;
		         u8RXFLT[2] = 0x4A;
		        }
	           if(tuner_if_frequency  == TUNER_IF_FREQ_36_DOT_125_M)
		       {
	             u8RXFLT[0] = 0x9a;
		         u8RXFLT[1] = 0xba;
		         u8RXFLT[2] = 0x4b;
		        }
		         ATBMWrite(0x0A,0x00, &u8RXFLT[0]);
		         ATBMWrite(0x0A,0x01, &u8RXFLT[1]);
		    	 ATBMWrite(0x0A,0x02, &u8RXFLT[2]);
			  return 1;
      }

    if(CLK_Freq == CLK_28_DOT_6363_M)
    {
               /*if tuner IF is 36.1667 , we use default data in u8RXFLT[]*/
	    	 if(tuner_if_frequency  == TUNER_IF_FREQ_36_DOT_166_M)
	         {
	         }

		/*for tuner IF 36Mhz or 36.125Mhz, we need to reconfigure these three registers*/
	     	 if(tuner_if_frequency  == TUNER_IF_FREQ_36_M)
		       {
		         u8RXFLT[0] = 0x86;
		         u8RXFLT[1] = 0x67;
		         u8RXFLT[2] = 0x67;
		        }
	         if(tuner_if_frequency  == TUNER_IF_FREQ_36_DOT_125_M)
		       {
	             u8RXFLT[0] = 0xE2;
		         u8RXFLT[1] = 0x28;
		         u8RXFLT[2] = 0x69;
		        }
		        ATBMWrite(0x0A,0x00, &u8RXFLT[0]);
	    	    ATBMWrite(0x0A,0x01, &u8RXFLT[1]);
	    	    ATBMWrite(0x0A,0x02, &u8RXFLT[2]);
	    	    return 1;
    }
  }
	return 0;
}


/****************************************************************************
Function:        ATBMTunerAGC
Parameters:   tuner_type
Return:          none
Description:
     Set demod AGC control range for different tuner types.
******************************************************************************/
void ATBMTunerAGC( u_int8 tuner_type){
    /*loop_min_agc,  tuner AGC limit, This value can be measured*/
    u_int8 tuner_AGC_Min;
    u_int8 tuner_AGC_Max;
    u_int8 hold_loop;

    switch(tuner_type){

		case TUNER_ENV59M01D8F:
		case TUNER_SHARP2093:
	    case TUNER_SHARP6093 :
		case TUNER_SHARP5093 :
		case TUNER_SHARP6092 :
		case TUNER_SHARP6060 :
		case TUNER_SHARP5060 :
	    case TUNER_SHARP6402 :
		case TUNER_SHARP1402 :
		case TUNER_SHARP5402 :
		case TUNER_ALPS_TDAC:
		case TUNER_ALPS_TDAD:
		case TUNER_ADMTV803:
		case TUNER_MXL5003S:
		case TUNER_MXL5007:
		        tuner_AGC_Min = 0x00;	//0
     	        tuner_AGC_Max = 0xFF;   // 3.3
		        break;

		case TUNER_MAX2165:
	            tuner_AGC_Min = 0x2E;	//0.4
		        tuner_AGC_Max = 0x80;	// 2.3
		        break;

	    case TUNER_ADMTV102:
		       tuner_AGC_Min = 0x00;	//0
		       tuner_AGC_Max = 0x40;    // 1.9
                     break;

	}

	ATBMWrite(0x10,0x20, &tuner_AGC_Min);
	ATBMWrite(0x10,0x23, &tuner_AGC_Max);

	hold_loop = 0x00;
    ATBMWrite(0x10,0x31, &hold_loop);
}


/****************************************************************************
Function:    ATBM_Mobile_channel
Params:     none
Return:      none
Description:
     This function optimize ATBM8831 Mobile receiving
 ****************************************************************************/
void ATBM_Mobile_channel(void)
{
	u_int8   reg_data[5]={0x00,0x04,0x04,0x00,0x00};
    u_int8   frame_count_max0, frame_count_max1;
    u_int8   reg_offset;
    u_int8   reg_data_ce;
    u_int8   i;

    for(i=0; i<5; i++)
    {
        reg_offset = i + 0x9b;
    	ATBMWrite(0x09, reg_offset, &reg_data[i]);
    }
	reg_data_ce = 0x7f;
	ATBMWrite(0x09, 0x5B, &reg_data_ce);
	reg_data_ce = 0x01;
	ATBMWrite(0x09, 0xCB, &reg_data_ce);
	reg_data_ce = 0x7f;
	ATBMWrite(0x09, 0xCC, &reg_data_ce);
	reg_data_ce = 0x7f;
	ATBMWrite(0x09, 0xCD, &reg_data_ce);
       reg_data_ce = 0x07;	 /*0x080x07*/
	ATBMWrite(0x09, 0xC2, &reg_data_ce);
       reg_data_ce = 0x03;	 /*0x02:0x03*/
	ATBMWrite(0x13, 0x16, &reg_data_ce);

	reg_data_ce = 0x20;
	ATBMWrite(0x0e, 0x01, &reg_data_ce); /*frame dealy*/
	reg_data_ce = 0x0a;
	ATBMWrite(0x0b, 0x03, &reg_data_ce); /*consec_frm_err_thre:128*/

       reg_data_ce = 0x00;
	ATBMWrite(0x09, 0x37, &reg_data_ce); /*alpha:0x0c:0x00*/
       reg_data_ce = 0x10;
	ATBMWrite(0x09, 0x35, &reg_data_ce); /*0x18:0x10*/
       reg_data_ce = 0x08;
	ATBMWrite(0x09, 0x36, &reg_data_ce); /*0x0c:0x08*/
       reg_data_ce = 0x08;
	ATBMWrite(0x09, 0x3e, &reg_data_ce); /*0x04:0x08*/
       reg_data_ce = 0x06;
	ATBMWrite(0x09, 0x6e, &reg_data_ce); /*0x08:0x06*/

       frame_count_max0 =0x00;
       frame_count_max1 =0x08;
       ATBMWrite(0x0B,0x09, &frame_count_max0);
       ATBMWrite(0x0B,0x0A, &frame_count_max1);
}


/****************************************************************************
Function:    ATBM_Static_channel
Params:      none
Return:      none
Description:
     This function optimize ATBM8831 static receiving
 ****************************************************************************/
void ATBM_Static_channel(void)
{
    u_int8   reg_data[5]={0x08,0x08,0x08,0x08,0x08};
    u_int8   frame_count_max0, frame_count_max1;
    u_int8   reg_offset;
    u_int8   reg_data_ce;
    u_int8   i;

    for(i=0; i<5; i++)
    {
        reg_offset = i + 0x9b;
    	ATBMWrite(0x09, reg_offset, &reg_data[i]);
    }
	reg_data_ce = 0x7f;
	ATBMWrite(0x09, 0x5B, &reg_data_ce);
	reg_data_ce = 0x01;
	ATBMWrite(0x09, 0xCB, &reg_data_ce);
	reg_data_ce = 0x7f;
	ATBMWrite(0x09, 0xCC, &reg_data_ce);
	reg_data_ce = 0x7f;
	ATBMWrite(0x09, 0xCD, &reg_data_ce);
       reg_data_ce = 0x07;	 /*0x08:0x07*/
	ATBMWrite(0x09, 0xC2, &reg_data_ce);
       reg_data_ce = 0x03;	 /*0x02:0x03*/
	ATBMWrite(0x13, 0x16, &reg_data_ce);

	reg_data_ce = 0x20;
	ATBMWrite(0x0e, 0x01, &reg_data_ce); /*frame dealy*/
	reg_data_ce = 0x0a;
	ATBMWrite(0x0b, 0x03, &reg_data_ce); /*consec_frm_err_thre:128*/

       reg_data_ce = 0x0c;
	ATBMWrite(0x09, 0x37, &reg_data_ce); /*alpha:0x0c:0x0c*/
       reg_data_ce = 0x10;
	ATBMWrite(0x09, 0x35, &reg_data_ce); /*0x18:0x10*/
       reg_data_ce = 0x08;
	ATBMWrite(0x09, 0x36, &reg_data_ce); /*0x0c:0x08*/
       reg_data_ce = 0x08;
	ATBMWrite(0x09, 0x3e, &reg_data_ce); /*0x04:0x08*/
       reg_data_ce = 0x06;
	ATBMWrite(0x09, 0x6e, &reg_data_ce); /*0x08:0x06*/

       frame_count_max0 =0x00;
       frame_count_max1 =0x08;
       ATBMWrite(0x0B,0x09, &frame_count_max0);
       ATBMWrite(0x0B,0x0A, &frame_count_max1);

}


/****************************************************************************
Function:       ATBMI2CByPassOn
Parameters:  none
Return:         none
Description:
    Enable the I2c Pass through to tuner via demod.
 ****************************************************************************/
 void ATBMI2CByPassOn(void)
{
	ATBMWrite(0x01,0x03,1); /* the 3st parameter:1-> Enable demod to pass I2C commands between tuner and host. */
}


 /****************************************************************************
Function:      ATBMI2CByPassOff
Parameters:       none
Return:         none
Description:
     Diable the i2c pass-through. Tuner is discoonected from the i2c BUS after this
     function is called.
 ****************************************************************************/
 void ATBMI2CByPassOff(void)
 {
	 ATBMWrite(0x01,0x03,0); /*the 3st parameter:0-> Disable demod to pass I2C commands between tuner and host*/
 }


/****************************************************************************
Function:        ATBMLockedFlag
Parameters:   none
Return:          1: locked, 0:unlocked
Description:
     This function check ATBM883x Demod locking status, i.e whether demod has
     correctly decoding and find the 0x47 TS stream header.
****************************************************************************/
int ATBMLockedFlag(void)
{

      u_int8 TS_sync = 0;

	  #ifdef ATBM_DEBUG
         ATBMDebugRegiseter();
         #endif
	  ATBMRead(0x03, 0x0d, &TS_sync);
	  if(TS_sync == 1)
	         {
	                //printf("valid broadcasting DTMB signal TS_sync =%d\n", TS_sync);
			  return 1;

	  }
        return 0;
}


/****************************************************************************
Function:        ATBMLockedLoopCheck()
Parameters:   none
Return:          1: locked, 0:unlocked
Description:
     This function keep checking ATBM883x signal locking status until it's LOCKED or time out;
     if signal is week, it may takes 1200ms+ at most ;this function can be used for normal scanning
****************************************************************************/
int ATBMLockedLoopCheck(void)
{

         u_int8 TS_sync = 0;
	  u_int8  i;
	  #ifdef ATBM_DEBUG
         ATBMDebugRegiseter();
         #endif
	  ATBMRead(0x03, 0x0d, &TS_sync);
	  for(i=0;i<12;i++)
	  {
		  if(TS_sync == 1)
	         {
	          //printf("valid broadcasting DTMB signal TS_sync =%d\n", TS_sync);
			  return 1;
		   }
		  Delayms(100); /*100 ms*/
	  }
        return 0;
}


/****************************************************************************
Function:    ATBMFrameErrorRatio
Params:     none
Return:      frame error per 1000 frames
Description:
     This function count error frame every 1000 frames
     (set 0x0B09 to 0x08 and  0x0B0A to 0x00)
****************************************************************************/
u_int16 ATBMFrameErrorRatio(void)
{

       u_int8 frame_error0, frame_error1, LockValue;
       u_int16 frame_error_ratio;

	LockValue =1;
   	ATBMWrite(0x08,0x4d, &LockValue);  /*read only latch register*/
        ATBMRead(0x0B,0x04, &frame_error0);
        ATBMRead(0x0b,0x05, &frame_error1);
	LockValue = 0;
	ATBMWrite(0x08,0x4d, &LockValue);

	frame_error_ratio = ((frame_error1&0x3f)*256 + frame_error0)/2;

	printf("frame_error_ratio = %d per thousand\n",frame_error_ratio);
	return  frame_error_ratio;

}


/****************************************************************************
Function:           ATBMSignalStrength
Parameters:      none
Return:             unsigned short PWM value
Description:
     This function check ATBM883x signal strength:     .
 ****************************************************************************/
u_int16 ATBMSignalStrength(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;

    LockValue =1;
    ATBMWrite(0x08,0x4d, &LockValue); /*read only latch register*/

    ATBMRead(0x10,0x28, &pwm0);
    ATBMRead(0x10,0x29, &pwm1);

    LockValue = 0;
    ATBMWrite(0x08,0x4d, &LockValue);
    pwm_value = ((pwm1&0x03)<<8)|pwm0;

    return pwm_value;
}


/****************************************************************************
Function:           ATBMSignalNoiseRatio
Parameters:      none
Return:             float (dB)
Description:
     This function check ATBM883x signal noise ratio,
     can be used for signal quality evaluation, refer ATBMSignalQuality:
 ****************************************************************************/
float ATBMSignalNoiseRatio(void)
{
   u_int8 LockValue;

   u_int8 signal_h, signal_m, signal_l;
   u_int8 noise_h, noise_l;
   u_int32 signal_power, noise_power,snr_bias;

   u_int8 pn_value,PN;

   u_int8 bias_h, bias_l;
   float SNR = 0;

   LockValue =1; /*lock register value*/
   ATBMWrite(0x08,0x4d, &LockValue);

   ATBMRead(0x09,0xa0, &signal_l);
   ATBMRead(0x09,0xa1, &signal_m);
   ATBMRead(0x09,0xa2, &signal_h);

   ATBMRead(0x09,0xa3, &noise_l);
   ATBMRead(0x09,0xa4, &noise_h);

   ATBMRead(0x13,0x1b, &bias_l);
   ATBMRead(0x13,0x1c, &bias_h);

   LockValue = 0; /*cancel the lock*/
   ATBMWrite(0x08,0x4d, &LockValue);

   signal_power = ((signal_h&0x07)<<16)+(signal_m<<8)+signal_l;
   noise_power = ((noise_h&0xff)<<8)+noise_l;

   ATBMRead(0x08,0x2d, &pn_value);
   PN = (pn_value&0x03);


   if(noise_power==0)
   {
        // printf("noise_power is 0, something error!");
   }
   else
   {
   	     /*PN 420, multi carrier*/
	     if (PN==1)
	     {
	           SNR = (float) (10*(log10(signal_power*1.0/noise_power)));
	     }

	     /*PN 945, multi carrier*/
	     if (PN==3)
	    {
	          SNR = (float) (10*(log10(signal_power*1.0/noise_power)));
	     }

   }
   /*PN 595, Single carrier*/
	if(PN==2)
	   {
	          snr_bias = bias_h*256+bias_l;
	          if((snr_bias>512)&&(snr_bias<1024))
	         {
	                  SNR = (float) (10*(log10(512/(bias_h*256+bias_l-512))));
	         }else
	     	  {
	     	          SNR =0;
	     	 }
	   }
   return SNR;
}


/****************************************************************************
Function:           ATBMSignalQuality
Parameters:      none
Return:             the signal quality reference value.
Description:
     This function check ATBM883x signal noise ratio,
     can be used for signal quality evaluation:
	 max value:100, min:0
 ****************************************************************************/
int ATBMSignalQuality(void)	//Refer to ATBMSignalNoiseRatio()
{
   unsigned long SNR = 0;
   int SNR100per = 0;
   u_int8 tps_code = 0;
   int lock_flag;
   u_int16 frame_error;

   u_int8 LockValue;
   u_int8 signal_h, signal_m, signal_l;
   u_int8 noise_h, noise_l;
   u_int32 signal_power, noise_power,snr_bias;

   u_int8 pn_value,PN;

   u_int8 bias_h, bias_l;

   LockValue =1; /*lock register value*/
   ATBMWrite(0x08,0x4d, &LockValue);

   ATBMRead(0x09,0xa0, &signal_l);
   ATBMRead(0x09,0xa1, &signal_m);
   ATBMRead(0x09,0xa2, &signal_h);

   ATBMRead(0x09,0xa3, &noise_l);
   ATBMRead(0x09,0xa4, &noise_h);

   ATBMRead(0x013,0x1b, &bias_l);
   ATBMRead(0x013,0x1c, &bias_h);

   LockValue = 0; /*cancel the lock*/
   ATBMWrite(0x08,0x4d, &LockValue);

   signal_power = ((signal_h&0x07)<<16)+(signal_m<<8)+signal_l;
   noise_power = ((noise_h&0xff)<<8)+noise_l;

   ATBMRead(0x08,0x2d, &pn_value);
   PN = (pn_value&0x03);

  if(noise_power==0)
   {
//         printf("noise_power is 0, something error!");
           SNR = 0;
   }
   else
   {
   	     /*PN 420, multi carrier*/
	     if (PN==1)
	     {
	           SNR = (unsigned long)(signal_power/noise_power);
	     }

	     /*PN 945, multi carrier*/
	     if (PN==3)
	    {
	          SNR = (unsigned long)(signal_power/noise_power);
	     }


   }
   /*PN 595, Single carrier*/
	if(PN==2)
		{
			snr_bias = bias_h*256+bias_l;
			if((snr_bias>512)&&(snr_bias<1024))
			   {
					SNR = (unsigned long)(512/(bias_h*256+bias_l-512));

			   }
			else
			   {
						SNR =0;
			   }

		   }

   tps_code = ATBMGetTPS();
   lock_flag = ATBMLockedFlag();
   frame_error = ATBMFrameErrorRatio();

  if((tps_code <11)&&(tps_code>4))/*4QAM FEC:0.4 0.6 0.8*/
   	{
   	  if(SNR>45)
   	  	{
   	  	 SNR100per = 90;
   	  	}
	  else
	  	{
	  	SNR100per = SNR*2;
	  	}
   	}

   if((tps_code <17)&&(tps_code>10)) /*For 16QAM FEC:0.8*/
   	{
   	  if(SNR>200)
   	  	{
   	  	SNR100per = 95;
   	  	}
   	  else if(SNR>100)
   	  	{
   	  	 SNR100per = 75 + SNR/10 ;
   	  	}
	  else if(SNR>60)
	 	{
	 	 SNR100per = 35 + SNR/2;
	 	}
	  else if(SNR>15)
	  	{
	     SNR100per = SNR+5;

	  	}
	  else
	    {
	     SNR100per = 20;
	    }
   	}
   if((tps_code <25)&&(tps_code>16))/*64QAM FEC:0.6; 32QAM 0.8*/
   	{

	   if(SNR>200)
   	  	{
   	  	SNR100per = 90;
   	  	}
   	  else if(SNR>100)
   	  	{
   	  	 SNR100per = 70 + SNR/10 ;
   	  	}
	  else if(SNR>60)
	 	{
	 	 SNR100per = 30 + SNR/2;
	 	}
	  else if(SNR>20)
	  	{
	     SNR100per = SNR;
	  	}
	  else
	    {
	     SNR100per = 20;
	    }
   	}

    //re-evaluation
	if((lock_flag ==1)&&(frame_error ==0))
   		{
   		//default:25, you can change this value form 0--50, for evaluation
   		SNR100per += 25;
   		}
	else if((lock_flag ==1)&&(frame_error > 0))
	 	{
	 	  SNR100per = SNR100per;
	 	}
  if(SNR100per>90)
	{
	  SNR100per = 90;
	}

	//DbgPrint("TPS =%d, SNR = %d SNR100per = %d\n",tps_code, SNR, SNR100per);
   return SNR100per;
}


/*****************************************************************************
Function:    ATBMSignalStrength_Sharp2093
Params:      none
Return:      signal_percent
Description:
     This function check ATBM883x IF AGC power, It can be used for signal
     strength evaluation:
     This is reference code for Sharp2093 DTT Can tuner
     range:  20--80, this is for reference, for specific requirement the range
             may be changed
*****************************************************************************/
u_int16 ATBMSignalStrength_Sharp2093(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;
   	u_int16 signal_percent;

    LockValue =1; /*lock register value*/
    ATBMWrite(0x08,0x4d, &LockValue);

    ATBMRead(0x10,0x28, &pwm0);
    ATBMRead(0x10,0x29, &pwm1);

	LockValue = 0;
	ATBMWrite(0x08,0x4d, &LockValue);
    pwm_value = ((pwm1&0x03)<<8)|pwm0;

	/*Sharp 2093 Reference*/
	if(pwm_value <352)
	{
		signal_percent = 80;
	}
	else if(pwm_value <492)
	{
		signal_percent = (532 - pwm_value)/2;
	}
	else
	{
		signal_percent = 20;
	}
	/*************************************/
	return signal_percent;
}

/*****************************************************************************
Function:    ATBMSignalStrength_Maxim2165
Params:      none
Return:      signal_percent
Description:
     This function check ATBM883x IF AGC power,It can be used for signal
     strength evaluation:
     This is reference code for maxim silicon tuner(maxim2165)
     range:  20--80, this is for reference, for specific requirement the range
             may be changed
*****************************************************************************/

u_int16 ATBMSignalStrength_Maxim2165(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;
   	u_int16 signal_percent;

    LockValue =1; /*lock register value*/
    ATBMWrite(0x08,0x4d, &LockValue);

    ATBMRead(0x10,0x28, &pwm0);
    ATBMRead(0x10,0x29, &pwm1);

	LockValue = 0;
	ATBMWrite(0x08,0x4d, &LockValue);
    pwm_value = ((pwm1&0x03)<<8)|pwm0;

	/*maxim2165 Reference*/
	if(pwm_value <235)
	{
		signal_percent = 80;
	}
	else if(pwm_value <655)
			 {
		       signal_percent = (unsigned int)((775 - pwm_value) /6);
			 }
			 else
			 {
				 signal_percent = 20;
			 }

	 return signal_percent;
}

/****************************************************************************
Function:    ATBMGetTPS
Params:     none
Return:      TPS_index
Description:
     This function check signal TPS, the return value is TPS index in GB20600-2006
 ****************************************************************************/
u_int8 ATBMGetTPS(void)
{
    u_int8 TPS_index;

    ATBMRead(0x0d,0x04, &TPS_index);

    return TPS_index;
}


/****************************************************************************
Function:    ATBMDebugRegiseter
Params:      none
Return:      none
Description:
     This function check Demodulator registers,  used for debug
 ****************************************************************************/
void ATBMDebugRegiseter(void)
{
   /*common register*/
	u_int8 software_version;

	u_int8  demod_state;
       u_int8  config_done;
 	u_int8  freq_offset;
 	u_int8  dsp_reset;
	u_int8  i2c_bybass_state;
	u_int8  CAN_Tuner;
	u_int8  u8RXFLT[6];
	/*silicon tuner config*/
	u_int8  ADC_config;
	u_int8  LNA_on_off;
	u_int8  single_alpha;
	/*tuner AGC limit*/
	u_int8 tuner_AGC_Min;
    u_int8 tuner_AGC_Max;

   /*TS interface configure*/
	u_int8 SamplingEdegeMode;
    u_int8 SerialEnabled;
	u_int8 ClockOutSelect;

    ATBMRead(0x02,0x0c, &software_version);
	ATBMRead(0x06,0x07, &demod_state);
    ATBMRead(0x00,0x04, &config_done);
	ATBMRead(0x00,0x0A, &dsp_reset);
	printf("ATBM883x Current software version: %d\n", software_version);
	printf("demod_state:%d config done:%d dsp_reset:%d\n",demod_state, config_done,dsp_reset);

	/*I2C bypass to master ports.0:disable 1:enable*/
	ATBMRead(0x01,0x03, &i2c_bybass_state);
   	ATBMRead(0x00,0x01, &CAN_Tuner);
	printf("bypass state:%d; CAN Tuner used(silicon tuner=0):%d\n", i2c_bybass_state, CAN_Tuner);

	ATBMRead(0x09,0x37, &single_alpha);
    printf("single carrier alpha = 0x%x\n", single_alpha);

	ATBMRead(0x06,0x02, &ADC_config);
    ATBMRead(0x10,0x30, &LNA_on_off);
	printf("For silicon tuner ADC_config:%d; LNA_on_off:%d\n", ADC_config, LNA_on_off);

   	ATBMRead(0x08,0x00, &freq_offset);
	printf("freq_offset 0x08_0x00: 0x%x\n", freq_offset);
       ATBMRead(0x08,0x01, &freq_offset);
	printf("freq_offset 0x08_0x01: 0x%x\n", freq_offset);

    ATBMRead(0x0A,0x00, &u8RXFLT[0]);
    ATBMRead(0x0A,0x01, &u8RXFLT[1]);
    ATBMRead(0x0A,0x02, &u8RXFLT[2]);
    ATBMRead(0x0A,0x03, &u8RXFLT[3]);
    ATBMRead(0x0A,0x04, &u8RXFLT[4]);
    ATBMRead(0x0A,0x05, &u8RXFLT[5]);
    printf("IF freq_lif: 0x%x 0x%x  0x%x\n", u8RXFLT[0], u8RXFLT[1], u8RXFLT[2]);
    printf("ADC rate ratio: 0x%x 0x%x  0x%x\n", u8RXFLT[3], u8RXFLT[4], u8RXFLT[5]);

	ATBMRead(0x10,0x20, &tuner_AGC_Min);
	ATBMRead(0x10,0x23, &tuner_AGC_Max);
	printf("tuner_AGC_Min:0x%x; tuner_AGC_Max:0x%x\n", tuner_AGC_Min,tuner_AGC_Max);

	ATBMRead(0x03,0x01, &SamplingEdegeMode);/*0x00: rising edge TS output; 0x01: falling edge TS output*/
    ATBMRead(0x03,0x05, &SerialEnabled);    /*0x1 enable serial mode */
    ATBMRead(0x03,0x0b, &ClockOutSelect);   /*0: SPI clock output  1: TS serial clock output */

	printf("TS interface SerialEnabled= %d SamplingEdegeMode =%d, clock select ClockOutSelect%d",\
		SerialEnabled,SamplingEdegeMode, ClockOutSelect);
}


/****************************************************************************
Function:            ATBMRead
Parameters:       base_address, register_address, *data
Return:              1:success, 0:failed
Description:
    ATBM883x demodulator register Read API, decoder platform independent.
   It calls I2Cwrite and i2CRead fucntions that should be implemenetd by
   customers based on customers' platforms.

   the read back data is in *data.
****************************************************************************/
int  ATBMRead(u_int8 base_addr, u_int8 register_addr, u_int8 *data)
{
    int retval = 0;
    u_int8 addr_data[2];

    addr_data[0] = base_addr;
    addr_data[1] = register_addr;

     retval=MDrv_IIC_ReadBytes(ATBMSlaveAddr|0x0200,2,addr_data,1,data);

     return(retval);
}


/****************************************************************************
Function:       ATBMWrite
Parameters:  base_address, register_address, *data
Return:         1:success, 0:failed
Description:
     ATBM883x demodulator register Write API, decoder platform independent.
   It calls I2Cwrite and i2CRead fucntions that should be implemenetd by
   customers based on customers' platforms.


****************************************************************************/
int  ATBMWrite(u_int8 base_addr, u_int8 register_addr, u_int8 *data)
{
    int retval = 0;
    u_int8 addr_data[2];

    addr_data[0] = base_addr;
    addr_data[1] = register_addr;

     retval=MDrv_IIC_WriteBytes(ATBMSlaveAddr|0x0200,1,&base_addr,1,&register_addr);
     retval=MDrv_IIC_WriteBytes(ATBMSlaveAddr|0x0200,1,data,0,NULL);

     return(retval);
}

