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
Copyright 2011, AltoBeam Inc. All rights reserved.

File Name: atbm884x.c

Version: 2.9.3
Released 2011-09-05

Description: Example programming interface for ATBM884x

Important struct:

custom_config
           All custom_config parameters should be customized according to system

Important functions:

ATBMInit_DTMB_Mode()
           This function sets the demodulator working in DTMB mode.and calls ATBMInit
           function. it can be used in mode switching between DTBM and DVB-C

ATBMInit_DVBC_Mode()
           This function sets the demodulator working in DVB-C mode.and calls ATBMInit
           function. it can be used in mode switching between DTBM and DVB-C

ATBMInit()
           It is called by ATBMInit_DTMB_Mode or ATBMInit_DVBC_Mode. This function initializes
           the demodulator in DTMB mode or DVB-C mode, all related configurations are included.

ATBMLockedFlag()
           This function checks the demodulator locking status.

ATBMSignalQuality()
           This function evaluates signal quality.

******************************************************************************/
#include <stdio.h>
#include "atbm884x.h"

#define ATBM_DEBUG             0      /*default no debug output*/
#define ATBM_DBINFO(x)        //x

u_int8  ATBMSlaveAddr = 0x80;   /*either 0x80 or 0x88 */
u_int8  ATBM_SOFTWARE_VERSION = 29; /*SW guide version*/

static u_int8 DTMB_Internal[]=
{
    0x0b, 0x03, 0x28,
    0x00, 0x12, 0x01,
    0x09, 0x98, 0x01,
    0x09, 0x99, 0x01,
    0x0d, 0x08, 0x06,
    0x0d, 0x09, 0x03,
    0x0d, 0x0e, 0x20,
    0x14, 0x2f, 0x3f,
    0x14, 0x6f, 0x05,
    0x14, 0x70, 0x18,
    0x14, 0x71, 0x04,
    0x14, 0x72, 0x05,
    0x14, 0x73, 0x0b,
    0x14, 0x74, 0x04,
    0x14, 0x15, 0x01,
    0x14, 0x45, 0x90,
    0x14, 0x46, 0xc0,
    0x14, 0x47, 0x80,
    0x14, 0x49, 0xc0,
    0x09, 0x89, 0x0c,
    0x09, 0x8b, 0x0c,
    0x08, 0xa0, 0x3c,
    0x08, 0xa2, 0x00,
    0x08, 0x52, 0x28,
    0x13, 0x1c, 0x01
};

u_int8 ATBM_ChipID;
struct custom_config_t custom_config;

 /****************************************************************************
 Function:    ATBMInit_DTMB_Mode
 Parameters:  none
 Return:      none

 Description:
    This function initializes ATBM884x in DTMB mode, selects DTMB receiving mode,
    then calls ATBMInit function.
 ******************************************************************************/
 void ATBMInit_DTMB_Mode(void)
 {
     custom_config.dtmb_dvbc_mode = ATBM_DTMB_MODE;

     /* Configure the demod with IF frequency of the tuner, according to the manual of the tuner.
     * Options:
     *       36, 36.1667 is typically used (MHz), support other tuner IF frequency either.
     *       0 (used for ZIF tuner)
     */
     custom_config.tuner_config.IF_Frequency_KHz = 4000; //36000 for 36M IF

     ATBMInit();
 }

  /****************************************************************************
 Function:    ATBMInit_DVBC_Mode
 Parameters:  none
 Return:      none

 Description:
      This function initializes ATBM884x in DVB-C mode, selects DVB-C receiving mode,
      then calls ATBMInit function
 ******************************************************************************/
 void ATBMInit_DVBC_Mode(void)
 {

     custom_config.dtmb_dvbc_mode = ATBM_DVBC_MODE;

     /* Configure the demod with IF frequency of the tuner, according to the manual of the tuner.
     * Options:
     *     36, 36.125 or other tuner IF frequrency (MHz)
     *     0  used for ZIF tuner
     */
     custom_config.tuner_config.IF_Frequency_KHz = 4000; //KHz, 36000 for 36.0M IF

     ATBMInit();
 }

 /****************************************************************************
Function:     ATBMInit
Parameters:   none
Return:       none

Description:
    Initializes ATBM884x demodulator and configures all necessary registers.
    The demodulator will start processing incoming data after this function is called.

    This function includes Software Reset and demodulator configuration:
       1. Demodulator reset
       2. Demodulator configuration
       3. Configure done confirmation
******************************************************************************/
void ATBMInit(void)
{
     u_int8 config_done = 0x01;
     u_int8 debug_bus = 0xFF;

     /***********************************************************/
     /*           Customize begin                                                                 */
     /***********************************************************/

    /* Related with tuner IF signal.
     * The choice between the two options below depends on the hardware design if ZIF Tuner is used.
     * Options:NO_SWAP_IQ, SWAP_IQ, default: NO_SWAP_IQ
     */
     custom_config.tuner_config.IQ_mode = NO_SWAP_IQ;


    /* Configure the TS stream interface of the demod.
     * Select the TS stream output in parallel or serial mode.
     * Options:TS_PARALLEL_MODE, TS_SERIAL_MODE,
     */
     custom_config.ts_mode.TS_Transfer_Type = TS_PARALLEL_MODE;


     /* Select the TS stream data output alignment with clock edge: on rising edge or on falling edge.
      * if TS_OUTPUT_FALLING_EDGE is selected, MPEG decoder should use Rising edge
      * if TS_OUTPUT_RISING_EDGE  is selected, MPEG decoder should use Falling edge
      * Options:TS_OUTPUT_FALLING_EDGE, TS_OUTPUT_RISING_EDGE
      */
      custom_config.ts_mode.output_edge = TS_OUTPUT_FALLING_EDGE;


     /* Configure the output of the TS stream clock pattern: free-running, or running only when data are valid.
      * Options: TS_CLOCK_CONST_OUTPUT, TS_CLOCK_VALID_OUTPUT
      */
      custom_config.ts_mode.SPI_clock_constant_output = TS_CLOCK_CONST_OUTPUT;


     /* Configure the clock source of the demod.
      * Select  whether a crystal or an oscillator is used for the clock source of the demod.
      * Options: CRYSTAL , OSCILLATOR
      */
      custom_config.CRYSTAL_OR_OSCILLATOR = CRYSTAL;


     /* Select the clock source frequency for the demod.
     * Options: 30.4 (MHz)
     *   please contact FAE if need to support other frequencies.
      */
      custom_config.sample_clk_Frequency_KHz = 30400;   //KHz

      /* Configure DVB-C Symbol rate, valid for DVB-C receiving*/
      //custom_config.dvbc_params.symbol_rate = 6875;//default: 6875K, 6.875M

     /***********************************************************/
     /*           Customize end                                 */
     /***********************************************************/

      ATBMReset(custom_config.CRYSTAL_OR_OSCILLATOR); //Check hardware state
      Delayms(10); /*10 ms*/
      ATBM_ChipID = ATBMChipID();

      ATBMWrite(0x00, 0x04, 0x00);
      if(ATBM_ChipID == 0x20)
      {
          ATBMWrite(0x06, 0x06, 0x00); //pll_ctrl_out for ATBM884x and atbm8846e
          ATBMWrite(0x0B, 0x09, 0x00); //DTMB frame count
          ATBMWrite(0x0B, 0x0A, 0x08); //DTMB frame count, size is 2048 Frames
          ATBMWrite(0x04, 0xA1, debug_bus);//This will put LOCK and Block_Err signal on Debug Bus
          ATBMWrite(0x04, 0xA2, debug_bus);
      }
      if(ATBM_ChipID == 0x30)
      {
          ATBMWrite(0x01, 0x0c, 0x01);
          ATBMWrite(0x10, 0xf7, 0xc0);
          ATBMWrite(0x10, 0xfb, 0x00); //0:PWM, 1:PDM
          ATBMWrite(0x0a, 0xf9, 0x00);
      }
      ATBMConfig( custom_config);
      if(custom_config.dtmb_dvbc_mode == ATBM_DTMB_MODE)
      {
          ATBMWrite(0x00, 0x0a, 0x01);
          ATBMWrite(0x00, 0x09, 0x01);
          ATBMWrite(0x00, 0x13, 0x00); //DTMB mode
          ATBMWrite(0x15, 0x18, 0x00);
          ATBMWrite(0x15, 0x15, 0x00);

          ATBMWrite(0x15, 0x11, 0x00);
          ATBMWrite(0x15, 0x12, 0x00);
          if(ATBM_ChipID == 0x30)
          {
              ATBMWrite(0x00, 0x16, 0x1d);
              ATBMWrite(0x09, 0x88, 0x08);
              ATBMWrite(0x09, 0x89, 0x0c);
              ATBMWrite(0x09, 0x9a, 0x40);
              ATBMWrite(0x0c, 0x24, 0x0a);
              ATBMWrite(0x0c, 0x26, 0x0a);
              ATBMWrite(0x0e, 0x01, 0x08);
          }
          if(ATBM_ChipID == 0x20)
          {
              ATBMWriteRegArray(DTMB_Internal,sizeof(DTMB_Internal)/sizeof(unsigned char));
          }
      }

      ATBMWrite(0x09, 0x35, 0x14);
      ATBMWrite(0x08, 0x52, 0x28);
      ATBMWrite(0x08, 0x00, 0x90);
      ATBMWrite(0x08, 0x01, 0x16);
      ATBMWrite(0x00, 0x04, config_done);
#if ATBM_DEBUG
      ATBMDebugRegister();
#endif
}


/****************************************************************************
Function:     ATBMChipID
Parameters:   none
Return:       ChipID

Description:
     This function checks chip ID,  The chip ID of ATBM8846 is 0x20.
     The chip ID of ATBM8846e is 0x30
******************************************************************************/
u_int8 ATBMChipID(void)
{
    u_int8 chipID;
    chipID = ATBMRead(0x00, 0x00);
    ATBM_DBINFO(printf("Chip ID= 0x%x, chipID ATBM8846:0x20 ATBM8846e:0x30\n",chipID));

    return chipID;
}


 /****************************************************************************
Function:    ATBMConfig
Parameters:  custom_config
Return:      none

Description:
     Set registers according to customer's configuration,
     This function configures ATBM884x.
 ******************************************************************************/
void ATBMConfig(struct custom_config_t tcustom_config)
{

    /*Demodulator default clock 30.4MHz; Tuner IF 36.166Mhz*/
     ATBMSetOSC(tcustom_config.tuner_config,tcustom_config.sample_clk_Frequency_KHz);
    ATBM_ChipID = ATBMChipID();

    /*Set demod AGC control range*/
    if(ATBM_ChipID == 0x20)
    {
        ATBMTunerAGC();
    }
    /*Configures MPEG TS output  mode*/
    ATBMSetTSMode(tcustom_config.ts_mode);
    ATBMWrite(0x01, 0x02, 1);     //I2C related
    ATBMWrite(0x02, 0x0c, ATBM_SOFTWARE_VERSION);
}

 /****************************************************************************
Function:    ATBM_Check_Demod_Status
Parameters:  none
Return:      PLL lock status

Description:
     Call this function when crystal is used. if PLL locked, hardware reset is not needed.
     This function is called before configuring demodulator registers.
     This function check demodulator status after power on or hardware reset
     If 1 is returned, demodulator in ready status.
     If 0 is returned, demodulator need hardware reset or power on.
 ******************************************************************************/
u_int8 ATBM_Check_Demod_Status(void)
{
    u_int8 check_times = 0;
    u_int8 analog, PLL_state, tmp, hardware_state ,chip_id;
    u_int8 step = 0x20;

    hardware_state = ATBMRead(0x06, 0x07);
    if(hardware_state!=5)
    {
        return 0;
    }
    chip_id = ATBMRead(0x00, 0x00);
    if(chip_id == 0x20)
    {
        return 1;
    }
    PLL_state = ATBM_Check_PLL_Status();  //check state 0, no register change
    if(PLL_state == 1)
    {
        return 1;
    }

    tmp = ATBMRead(0x02, 0x14);
    while(check_times<5)
    {
        if((tmp&0x02) == 0x02)
        {
            ATBMWrite(0x06, 0x06, 0x02);
        }else
        {
            ATBMWrite(0x06, 0x06, 0x00);
        }
        analog = check_times*step;
        if(check_times == 4)
        {
            analog = 0x60;
        }
        ATBMWrite(0x06, 0x0d, analog);
        if(check_times == 4)
        {
            ATBMWrite(0x06, 0x05, 0x00);
        }
        Delayms(10);
        PLL_state = ATBM_Check_PLL_Status();
        if(PLL_state == 1)
        {
            return 1;
        }
        check_times = check_times + 1;
    }
    if((tmp&0x02) == 0x02)
    {
        ATBMWrite(0x06, 0x06, 0x02);
    }else
    {
        ATBMWrite(0x06, 0x06, 0x00);
    }
        Delayms(10);
    PLL_state = PLL_Lock_Flag();
    if(PLL_state == 1)
    {
        return 1;
    }
    return 0;
}
/****************************************************************************
Function:    PLL_Lock_Flag
Parameters:  none
Return:      demodulator PLL lock status

Description:
     when internal PLL is locked, the returned value is 1.
******************************************************************************/
 u_int8 PLL_Lock_Flag(void)
 {
     int i = 0;
     u_int8 flag;
     while(i<20)
     {
         flag = ATBMRead(0x06, 0x11);
         if((flag&0x01) != 0x01)
         {
             return 0;
         }
         i++;
     }
     return 1;
 }
/****************************************************************************
Function:    ATBM_Check_PLL_Status
Parameters:  none
Return:      PLL status

Description:
     When demodulator PLL locked and stable, the returned value is 1.
******************************************************************************/
 u_int8 ATBM_Check_PLL_Status(void)
 {
     u_int8 pll_state, tmp;

     pll_state = PLL_Lock_Flag();
     if(pll_state == 1)
     {
         tmp = ATBMRead(0x02, 0x14);
         if((tmp&0x02) != 0x02)
         {
             ATBMWrite(0x06, 0x06, 0x02);
         }
         else
         {
             ATBMWrite(0x06, 0x06, 0x00);
         }
     }
     else
     {
         return 0;
     }
     Delayms(10);
     pll_state = PLL_Lock_Flag();
     if(pll_state == 1)
     {
         return 1;
     }

     return 0;
 }

/****************************************************************************
Function:    ATBMReset
Parameters:  cry_or_osc
Return:      none

Description:
      This function resets ATBM884x demodulator.
 ******************************************************************************/
void ATBMReset(u_int8 cry_or_osc)
{

     u_int8 HardwareState, check_result = 0;
     u_int8 loop, tmp;

    /*
    * After hardware power on properly or reset correctly,
    * HardwareState value should be 0x05 when using crystal, 3.3V PLL
    * HardwareState value should be 0x07 when using oscillator, 3.3V PLL
    */
    if(cry_or_osc==CRYSTAL)
    {
        //Software checking, when power on failed, it will return 0 because I2C error or PLL error
         check_result = ATBM_Check_Demod_Status();
         if(check_result == 1)
         {
             return;
         }
         //Hardware checking, usually used after demodulator resume from suspend mode
         for(loop=0; loop<2; loop++)
         {
             if(check_result != 1)
             {
                 ATBM_DBINFO(printf("I2C Error or it is not properly power up, need hardware reset\n"));
                 DemodHardwareReset();    //hardware check
                 Delayms(50);
                 check_result = ATBM_Check_Demod_Status();
             }
             else
             {
                 return;
             }
         }
     }

    if(cry_or_osc==OSCILLATOR)
    {
        HardwareState = ATBMRead(0x06, 0x07);
        for(loop=0; loop<10; loop++)
        {
            if(HardwareState!=0x07)
            {
                ATBM_DBINFO(printf("I2C Error or it is not properly power up, need hardware reset\n"));
                DemodHardwareReset();
                Delayms(100);
                HardwareState  =ATBMRead(0x06, 0x07);
            }
            else
            {
                tmp = ATBMRead(0x02, 0x14);
                if((tmp&0x02) != 0x02)
                {
                    ATBMWrite(0x06, 0x06, 0x02);
                }
                else
                {
                    ATBMWrite(0x06, 0x06, 0x00);
                }
                break;
            }
        }
    }

}


/****************************************************************************
Function:    ATBMSetTSMode
Parameters:  ts_mode
Return:      none

Description:
      This function configures Transport stream interface mode.
******************************************************************************/
void ATBMSetTSMode(struct MPEG_TS_mode_t ts_mode)
{
    u_int8 SerialEnabled =0x0;/*parallel clock out */
    //u_int8 SSI_sync_hold_cycle = 0x00;
    u_int8 TSOutputEdegeMode =ts_mode.output_edge;
    u_int8 TsClockMode = ts_mode.SPI_clock_constant_output;

    /*0x00: SPI data align with rising edge of TSBCLK; 0x01: SPI data align with falling edge of TSBCLK*/
    ATBMWrite(0x03, 0x01, TSOutputEdegeMode);
    ATBMWrite(0x03, 0x06, TsClockMode);  /*either free running or only active when data are valid*/

    if(ts_mode.TS_Transfer_Type==TS_SERIAL_MODE)
    {
        SerialEnabled = 0x01;    /*enable serial TS mode */

        //SSI_sync_hold_cycle = 0x00; //0x00:1 bit sync;0x01: 8 bit sync
        /*0: serial sync  holds 1 cycle; 1: serial sync holds 8 cycles*/
        //ATBMWrite(0x03,0x0f, SSI_sync_hold_cycle);

        /*0:disable serial mode; 1: enable serial mode */
        ATBMWrite(0x03, 0x05, SerialEnabled);
    }
    else
    {
        SerialEnabled =0x0; /*parallel clock output */
        /*0: disable serial mode; 1:enable serial mode */
        ATBMWrite(0x03, 0x05, SerialEnabled);

    }
}

/****************************************************************************
Function:    ATBMSetOSC
Parameters:  tuner_config, sample_clk_Frequency
Return:      1 for success,0 for error

Description:
     This function configures ATBM884x according to external Clock source
     and  Tuner IF frequency.
 ******************************************************************************/
int ATBMSetOSC(struct tuner_config_t tuner_config, u_int32 sample_clk_Frequency)
{
    /*
    * Demodulator default registers are for 30.4 MHz crystal, no need to list here.
    */
    u_int8  u8RXFLT[6];
    u_int32 tuner_if_frequency = tuner_config.IF_Frequency_KHz;
    u_int32 CLK_Freq = sample_clk_Frequency;
    u_int32 freq_lif_tmp;
    u_int32 rate_ratio_tmp;
    u_int8  IF_tuner_on= 0;
    u_int8 ADC_config= 0x16;
    u_int8 swap_iq;
    u_int8 adc_tmp, chip_id;


    if(tuner_config.IQ_mode == SWAP_IQ)
    {
        swap_iq = 0x03;
        ATBMWrite(0x0c, 0x01, swap_iq);
    }

    if(tuner_if_frequency==0)
    {
        /*Tuner selection. 0: ZIF tuner; 1: IF tuner*/
        ATBMWrite(0x00, 0x01, IF_tuner_on);

        /*ADC config*/
        ATBMWrite(0x06, 0x02, ADC_config);
        chip_id = ATBMRead(0x00, 0x00);
        if(chip_id == 0x30)
        {
            adc_tmp = ATBMRead(0x06, 0x0d);
            adc_tmp|=0x04;
            ATBMWrite(0x06, 0x0d, adc_tmp);
        }
    }
    else
    {
        /*
        * 0x0A03~0x0A05 are only related to sampling frequency;
        * 0x0A00~0x0A02 are related to sampling frequency and tuner IF frequency.
        */
        if(tuner_if_frequency>CLK_Freq)
        {
            freq_lif_tmp=(u_int32)((16*13176794/CLK_Freq)*(tuner_if_frequency-CLK_Freq)/8);
        }
        else //low IF
        {
            freq_lif_tmp=(u_int32)((2*13176794/CLK_Freq)*tuner_if_frequency);
        }
        u8RXFLT[0] = (u_int8)(freq_lif_tmp&0xff);
        u8RXFLT[1] = (u_int8)((freq_lif_tmp>>8)&0xff);
        u8RXFLT[2] = (u_int8)((freq_lif_tmp>>16)&0xff);

        ATBMWrite(0x0A, 0x00, u8RXFLT[0]);
        ATBMWrite(0x0A, 0x01, u8RXFLT[1]);
        ATBMWrite(0x0A, 0x02, u8RXFLT[2]);
        ATBM_DBINFO(printf("IF freq_lif: 0x%x 0x%x  0x%x\n", u8RXFLT[0], u8RXFLT[1], u8RXFLT[2]));
    }

    rate_ratio_tmp=(u_int32)(CLK_Freq*68985/2000);
    u8RXFLT[3] = (u_int8)(rate_ratio_tmp&0xff);
    u8RXFLT[4] = (u_int8)((rate_ratio_tmp>>8)&0xff);
    u8RXFLT[5] = (u_int8)((rate_ratio_tmp>>16)&0x1f);
    if(CLK_Freq ==30400)
    {
        u8RXFLT[3]= 0x00;
        u8RXFLT[4]= 0x00;
        u8RXFLT[5]= 0x10;
    }
    ATBMWrite(0x0A, 0x03, u8RXFLT[3]);
    ATBMWrite(0x0A, 0x04, u8RXFLT[4]);
    ATBMWrite(0x0A, 0x05, u8RXFLT[5]);
    ATBM_DBINFO(printf("ADC rate ratio: 0x%x 0x%x  0x%x\n", u8RXFLT[3], u8RXFLT[4], u8RXFLT[5]));
    return 1;
}


/****************************************************************************
Function:    ATBMTunerAGC
Parameters:  none
Return:      none

Description:
      Sets the range of tuner's IF AGC control voltage to the demod.
******************************************************************************/
void ATBMTunerAGC(void)
{
    /*loop_min_agc,  tuner AGC limit, This value can be measured*/
    u_int8 tuner_AGC_Min;
    u_int8 tuner_AGC_Max_M,tuner_AGC_Max_H;

    tuner_AGC_Min = 0x00;    //0
    tuner_AGC_Max_M = 0x00;
    tuner_AGC_Max_H = 0x02; // 3.3V

    ATBMWrite(0x10, 0x20, tuner_AGC_Min);
    ATBMWrite(0x10, 0x23, tuner_AGC_Max_M);
    ATBMWrite(0x10, 0x24, tuner_AGC_Max_H);

}

/****************************************************************************
Function:    ATBMI2CByPassOn
Parameters:  none
Return:      none

Description:
      Enable demod to pass I2C commands between tuner and host.
 ****************************************************************************/
 void ATBMI2CByPassOn(void)
{
	ATBMWrite(0x01,0x03,1); /* the 3st parameter:1-> Enable demod to pass I2C commands between tuner and host. */
}

 /****************************************************************************
Function:    ATBMI2CByPassOff
Parameters:  none
Return:      none

Description:
     Disable the I2C pass-through. Tuner is disconnected from the I2C BUS after this
     function is called.
 ****************************************************************************/
 void ATBMI2CByPassOff(void)
 {
     Delayms(10);   //Some tuners need this.
	 ATBMWrite(0x01,0x03,0); /*the 3st parameter:0-> Disable demod to pass I2C commands between tuner and host*/
 }

 /****************************************************************************
Function:    ATBMHoldDSP
Parameters:  none
Return:      none

Description:
    This function should be called before set tuner DTMB frequency.
 ****************************************************************************/
 void ATBMHoldDSP(void)
 {
     ATBMWrite(0x00, 0x05, 0x01);
 }

  /****************************************************************************
Function:    ATBMStartDSP
Parameters:  none
Return:      none

Description:
    This function should be called after set tuner DTMB frequency.
    Attention: ATBMHoldDSP and ATBMStartDSP should be used together.
    For example:
        ATBMHoldDSP();
        SetTunerFrequency(Frequency_KHz);
        ATBMStartDSP();
 ****************************************************************************/
 void ATBMStartDSP(void)
 {
     ATBMWrite(0x00, 0x05, 0x00);
 }
 /****************************************************************************
 Function:    ATBMLockedFlag
 Parameters:  none
 Return:      1: locked, 0:unlocked

   Description:
   This function checks ATBM884x Demod locking status, i.e., whether demod has
  decoded DTMB or DVB-C signal.
 ****************************************************************************/
 int ATBMLockedFlag(void)
 {
     u_int8 dtmb_fec = 0;
     u_int8 cur_receiving_mode;

     cur_receiving_mode = ATBMRead(0x00, 0x13); //0:DTMB, 1:DVB-C
     if(cur_receiving_mode==0x00) //DTMB
     {
         dtmb_fec = ATBMRead(0x0b, 0x08);
         if((dtmb_fec&0x01)==0x01) //FER locked:bit0
         {
             ATBMSignalStrength();
              ATBM_DBINFO(printf("\r\n ATBMLockedFlag:%x\n",dtmb_fec));
             return 1;
         }
     }
      return 0;
 }


/****************************************************************************
Function:    ATBMLockedLoopCheck()
Parameters:  none
Return:      1: locked, 0:unlocked

Description:
      This function keeps checking signal locking status until it's Locked or time out.
      recommended timeout value
      DTMB: 2000 milliseconds, usually locked in 300-400 Milliseconds if DTMB signal is detected
      DVB-C: 600 milliseconds, usually locked in 100-200 Milliseconds if DVB-C signal is detected.
****************************************************************************/
int ATBMLockedLoopCheck(void)
{
    unsigned char dtmb_fec = 0;
    unsigned int dvbc_status = 0;
    int i;
    unsigned char cur_receiving_mode;
    int check_times;
    unsigned int dtmb_time_out = 2000;  //2000 millisecond
    unsigned int dvbc_time_out = 600;

    cur_receiving_mode = ATBMRead(0x00, 0x13); //0:DTMB, 1:DVB-C
    if(cur_receiving_mode == 0) //DTMB
    {
        check_times = dtmb_time_out/50;
        for(i=0; i<check_times; i++)
        {
            dtmb_fec = ATBMRead(0x0b, 0x08);
            if(dtmb_fec&0x01) //bit 0
            {
                return 1;           //DTMB FEC locked
            }
            Delayms(50);
        }
    }
    if(cur_receiving_mode == 1) //DVB-C
    {
        check_times = dvbc_time_out/50;
        for(i=0; i<check_times; i++)
        {
            dvbc_status = ATBM_DVBC_Read(0x08);       //read DVB-C internal register
            if(dvbc_status&0x20) //bit 5
            {
                return 1;           //DVB-C FEC locked
            }
            Delayms(50);
        }
    }
    return 0; //FEC not locked
}

/****************************************************************************
Function:    ATBM_LDPC_FrameErrorRatio
Parameters:  none
Return:      frame error per 1024 frames

Description:
      This function counts post LDPC error frames every 2048 frames
      (set 0x0B09 to 0x00 and  0x0B0A to 0x08 when initialized)
****************************************************************************/
u_int16 ATBMFrameErrorRatio(void)
{

    u_int8 frame_error0 = 0, frame_error1 = 0, LockValue;
    u_int16 frame_error_ratio;
    ATBM_ChipID = ATBMChipID();
    LockValue =1;
    ATBMWrite(0x08, 0x4d, LockValue);  /*latch read only registers*/
    if(ATBM_ChipID == 0x20)
    {
        frame_error0 = ATBMRead(0x0B, 0x04);
        frame_error1 = ATBMRead(0x0b, 0x05);
    }
    if(ATBM_ChipID == 0x30)
    {
        frame_error0 = ATBMRead(0x0B, 0x14);
        frame_error1 = ATBMRead(0x0b, 0x15);
    }
    LockValue = 0;
    ATBMWrite(0x08, 0x4d, LockValue);

    frame_error_ratio = ((frame_error1&0x7f)*256 + frame_error0)/2;

    ATBM_DBINFO(printf("frames with error = %d per thousand\n",frame_error_ratio));
    return  frame_error_ratio;

}

/****************************************************************************
Function:        ATBMSignalStrength
Parameters:      none
Return:          pwm_value, unsigned short PWM value, in the range of 0--1023

Description:
     This function checks ATBM884x DTMB signal strength related pwm_value:
     when signal is weak pwm_value will be bigger; The smaller the pwm_value
     is, the stronger the signal strength detected.
 ****************************************************************************/
u_int16 ATBMSignalStrength(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;

    LockValue =1;
    ATBMWrite(0x08, 0x4d, LockValue); /*latch read only registers*/

    pwm0 = ATBMRead(0x10, 0x28);
    pwm1 = ATBMRead(0x10, 0x29);

    LockValue = 0;
    ATBMWrite(0x08, 0x4d, LockValue);

    pwm_value = (u_int16)(((pwm1&0x03)<<8)|pwm0);
    ATBM_DBINFO(printf(" ABtm884x signal strength pwm_value = %d\n", pwm_value));

    if(pwm_value <= 160)
        pwm_value = (u_int16)(90 + (160 - pwm_value)/16);
    else if(pwm_value<=290)
        pwm_value = (u_int16)(30 + (290 - pwm_value)*60/290);
    else
        pwm_value = (u_int16)(0 + (1023 - pwm_value)*30/733);

    return pwm_value;
}


/****************************************************************************
Function:           ATBM8846SignalDivideNoise
Parameters:      none
Return:             SNR

Description:
     This function is an internal function called by ATBMSignalNoiseRatio()
 ****************************************************************************/
u_int32 ATBM8846SignalDivideNoise(void)
{
    u_int8 LockValue;

    u_int8 pn_value,PN;
    u_int8 tmp_noise;
    u_int8 is_sc;
    u_int32 SNR = 0;

    u_int8 signal_h, signal_m, signal_l;
    u_int8 noise_h,noise_m, noise_l;
    u_int32 signal_power, noise_power;


    LockValue =1; /*lock register value*/
    ATBMWrite(0x08,0x4d, LockValue);

    pn_value = ATBMRead(0x08,0x2d);
    PN = (u_int8)((pn_value&0x03));

    tmp_noise = ATBMRead(0x14,0xAF);
    //tmp_c = ATBMRead(0x08,0xab);

    if(PN==2) //PN595
    {
        signal_l = ATBMRead(0x14,0xdc);
        signal_m = ATBMRead(0x14,0xdd);
        signal_h = ATBMRead(0x14,0xde);

        signal_power = ((signal_h&0x0f)<<16)+(signal_m<<8)+signal_l;
        signal_power = signal_power/16;
        if(tmp_noise!=3)
        {
            noise_l = ATBMRead(0x14,0xf8);
            noise_h = ATBMRead(0x14,0xf9);
            noise_power = ((noise_h&0x3f)<<8) + noise_l;
        }
        else
        {
            noise_l = ATBMRead(0x13,0x40);
            noise_h = ATBMRead(0x13,0x41);
            noise_power = ((noise_h&0x3f)<<8) + noise_l;
        }

        if(signal_power ==0)
        {
            signal_power =1; //signal_power should >0 in log calculation;
        }

        SNR = (u_int32) (signal_power/(noise_power+1));

    }

    if( (PN==1)||(PN==3) ) //PN420 & PN945
    {
        is_sc = ATBMRead(0x0d,0x0f);
        if(is_sc!=1)
        {
            signal_l = ATBMRead(0x0f,0x1d);
            signal_m = ATBMRead(0x0f,0x1e);
            signal_h = ATBMRead(0x0f,0x1f);

            noise_l = ATBMRead(0x0f,0x1a);
            noise_m = ATBMRead(0x0f,0x1b);
            noise_h = ATBMRead(0x0f,0x1c);

            signal_power = ((signal_h&0x0f)<<16)+(signal_m<<8)+signal_l;
            noise_power  = ((noise_h&0x07)<<16)+(noise_m<<8)+noise_l;
        }
        if(is_sc==1)
        {
            signal_l = ATBMRead(0x09,0xcc);
            signal_h = ATBMRead(0x09,0xcd);
            noise_l = ATBMRead(0x09,0xde);
            noise_h = ATBMRead(0x09,0xdf);
            signal_power = (signal_h<<8) + signal_l;
            noise_power  = (noise_h<<8)+ noise_l;
        }
        if(signal_power ==0)
        {
            signal_power =1; //signal_power >0;
        }

        if(noise_power==0)
        {
            // printf("noise_power is 0,  error!");
            SNR = (u_int32)(signal_power/(noise_power+1));
        }
        else
        {
            SNR = (u_int32)(signal_power/noise_power);
        }

    }
    LockValue = 0; /*cancel the lock*/
    ATBMWrite(0x08,0x4d, LockValue);
    return SNR;
}
 /****************************************************************************
 Function:           ATBM8846ESignalDivideNoise
 Parameters:      none
 Return:             SNR

   Description:
   This function is an internal function called by ATBMSignalNoiseRatio()
   ****************************************************************************/
u_int32 ATBM8846ESignalDivideNoise(void)
 {
     u_int8 LockValue;

     u_int8 pn_value,PN;
     u_int8 tmp_noise;
     u_int8 is_sc;
     u_int32 SNR = 0;

     u_int8 signal_h, signal_m, signal_l;
     u_int8 noise_h,noise_m, noise_l;
     u_int32 signal_power = 0;
     u_int32 noise_power = 0;

     LockValue =1; /*lock register value*/
     ATBMWrite(0x08, 0x4d, LockValue);

     pn_value = ATBMRead(0x08, 0x2d);
     PN = (u_int8)(pn_value&0x03);

     tmp_noise = ATBMRead(0x14, 0xAF);
     is_sc = ATBMRead(0x0d, 0x0f);
     if(is_sc!=1)
     {
         signal_l = ATBMRead(0x0f, 0x1d);
         signal_m = ATBMRead(0x0f, 0x1e);
         signal_h = ATBMRead(0x0f, 0x1f);
         noise_l = ATBMRead(0x0f, 0x1a);
         noise_m = ATBMRead(0x0f, 0x1b);
         noise_h = ATBMRead(0x0f, 0x1c);
         signal_power = ((signal_h&0x0f)<<16)+(signal_m<<8)+signal_l;
         noise_power  = ((noise_h&0x07)<<16)+(noise_m<<8)+noise_l;
         if(signal_power ==0)
         {
             signal_power =1; //signal_power should >0 in log calculation;
         }
         SNR = (u_int32) (signal_power/(noise_power+1));
     }
     if(is_sc==1)
     {
         if(PN==2) //PN595
         {
             signal_l = ATBMRead(0x14, 0xdc);
             signal_m = ATBMRead(0x14, 0xdd);
             signal_h = ATBMRead(0x14, 0xde);
             signal_power = ((signal_h&0x0f)<<16)+(signal_m<<8)+signal_l;
             signal_power = signal_power/16;
             if(tmp_noise!=3)
             {
                 noise_l = ATBMRead(0x14, 0xf8);
                 noise_h = ATBMRead(0x14, 0xf9);
                 noise_power = ((noise_h&0x3f)<<8) + noise_l;
             }
             else
             {
                 noise_l = ATBMRead(0x13, 0x40);
                 noise_h = ATBMRead(0x13, 0x41);
                 noise_power = ((noise_h&0x3f)<<8) + noise_l;
             }
             if(signal_power ==0)
             {
                 signal_power =1; //signal_power should >0 in log calculation;
             }
             SNR = (u_int32)(signal_power/(noise_power+1));

         }

         if( (PN==1)||(PN==3) ) //PN420 & PN945
         {

             signal_l = ATBMRead(0x09, 0xcc);
             signal_h = ATBMRead(0x09, 0xcd);
             signal_power = (signal_h<<8) + signal_l;
             noise_l = ATBMRead(0x09, 0xed);
             noise_h = ATBMRead(0x09, 0xee);
             noise_power = ((noise_h&0x3f)<<8) + noise_l;

             if(signal_power ==0)
             {
                 signal_power =1; //signal_power >0;
             }
             if(noise_power==0)
             {
                 // printf("noise_power is 0,  signal error!");
                 SNR = (u_int32)(signal_power/(noise_power + 1));
             }
             else
             {
                 SNR = (u_int32)(signal_power/noise_power);
             }
         }
     }
     LockValue = 0; /*cancel the lock*/
     ATBMWrite(0x08,0x4d, LockValue);
     return SNR;
 }
 /****************************************************************************
 Function:           ATBMSignalNoiseRatio
 Parameters:      none
 Return:             SNR (dB)

   Description:
   This function checks ATBM8846 or ATBM8846E signal-to-noise ratio and return SNR in dB format.
   Can be used for signal quality evaluation.
 ****************************************************************************/
 u_int32 ATBMSignalNoiseRatio(void)
 {
     u_int32 SNR = 0;
     u_int32 SNR_dB;
     ATBM_ChipID = ATBMChipID();
     if(ATBM_ChipID == 0x20)
     {
         SNR= ATBM8846SignalDivideNoise(); //ATBM884x
     }
     if(ATBM_ChipID == 0x30)
     {
         SNR= ATBM8846ESignalDivideNoise(); //ATBM8846E
     }
     SNR_dB = (u_int32) (Log10_Convert(SNR));
     return SNR_dB;
 }
/****************************************************************************
Function:    ATBMSignalQuality
Parameters:  none
Return:      SNR100per, the signal quality evaluated value.

Description:
     This function checks ATBM884x signal-to-noise ratio and evaluated in range of 30--100.
     Can be used for signal quality evaluation:
     max value:99, min:30
 ****************************************************************************/
int ATBMSignalQuality(void)
{
    u_int8 tps_code, ts_sync;
    double frame_error;
    int SNR100per;
    u_int32 SNR = 0;
     ATBM_ChipID = ATBMChipID();
     if(ATBM_ChipID == 0x20)
     {
         SNR = ATBM8846SignalDivideNoise(); //ATBM884x
     }
     if(ATBM_ChipID == 0x30)
     {
         SNR = ATBM8846ESignalDivideNoise(); //ATBM8846E
     }
    tps_code = ATBMGetTPS();
    ts_sync = ATBMRead(0x03, 0x0d);
    if(ts_sync !=1)
    {
        ts_sync = ATBMRead(0x03, 0x0d);
    }
    frame_error = ATBMFrameErrorRatio();

    SNR100per = 20;
     if((tps_code <11)&&(tps_code>2))/*4QAM FEC:0.6 0.8*/
       {
        if(SNR>100)
             {
             SNR100per = 90+ SNR/100;
             }
         else if(SNR>60)
             {
               SNR100per = 80 + (SNR-60)/4 ;
             }
      else if(SNR>20)
         {
          SNR100per = 60 + (SNR-20)/2;
         }
      else if(SNR>5)
          {
             SNR100per = 40 + SNR;
          }
      else
        {
         SNR100per = 40;
        }
       }

   if((tps_code <17)&&(tps_code>10)) /*For 16QAM FEC:0.6 0.8*/
       {
         if(SNR>100)
             {
             SNR100per = 90+ SNR/100;
             }
         else if(SNR>70)
             {
               SNR100per = 80 + (SNR-70)/3 ;
             }
      else if(SNR>30)
         {
          SNR100per = 60 + (SNR-30)/2;
         }
      else if(SNR>10)
          {
             SNR100per = 50 + (SNR-10)/2;
          }
      else
        {
         SNR100per = 40;
        }
       }
   if((tps_code <25)&&(tps_code>16))/*64QAM FEC:0.6; 32QAM 0.8*/
       {

       if(SNR>100)
             {
             SNR100per = 90+ SNR/100;
             }
         else if(SNR>70)
             {
              SNR100per = 80 + (SNR-70)/3 ;
             }
      else if(SNR>30)
         {
          SNR100per = 60 + (SNR-30)/2;
         }
      else if(SNR>20)
          {
             SNR100per = 30+ SNR;
          }
      else
        {
         SNR100per = 40;
        }
       }

    //re-evaluation
    if((ts_sync ==1)&&(frame_error ==0)) //no error
           {
           //default:5, you can change this value form 0--10, for evaluation
           SNR100per +=5;
           }
    else if((ts_sync ==1)&&(frame_error > 0))
         {
           SNR100per = SNR100per - 10;
         }
    else
        {
          SNR100per = 30;
        }
   if(SNR100per>99)
    {
      SNR100per = 99;
    }
   ATBM_DBINFO(printf("TPS =%d, SNR = %d SNR100per = %d\n",tps_code, SNR, SNR100per));
   return SNR100per;
}


/*****************************************************************************
Function:    ATBMSignalStrength_Sharp2093
Parameters:  none
Return:      signal_percent

Description:
     This function checks ATBM884x IF AGC power. It can be used for Sharp2093 Tuner
     signal strength evaluation.
     This is reference code for Sharp2093 DTT Can tuner.
     Range:  20--80.This is for reference only. For specific Tuner the AGC range may be changed.
*****************************************************************************/
u_int16 ATBMSignalStrength_Sharp2093(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;
    u_int16 signal_percent;

    LockValue =1; /*lock register value*/
    ATBMWrite(0x08,0x4d, LockValue);

    pwm0 = ATBMRead(0x10, 0x28);
    pwm1 = ATBMRead(0x10, 0x29);

    LockValue = 0;
    ATBMWrite(0x08,0x4d, LockValue);
    pwm_value = (u_int8)(((pwm1&0x03)<<8)|pwm0);

    /*Sharp 2093 Reference*/
    if(pwm_value <352)
    {
        signal_percent = 80;
    }
    else if(pwm_value <492)
    {
        signal_percent = (u_int16)((532 - pwm_value)/2);
    }
    else
    {
        signal_percent = 20;
    }
    /*************************************/
    return signal_percent;
}

/*****************************************************************************
Function:    ATBMSignalStrength_TDAC2_C02A
Parameters:  none
Return:      signal_percent

Description:
     This function checks ATBM884x IF AGC power. It can be used for ALPS TDAC2-C02A Tuner
     signal strength evaluation.
     This is reference code for ALPS TDAC2-C02A DTMB(DVB-C) Can tuner.
     Range:  20--90.This is for reference only. For specific Tuner the AGC range may be changed.
*****************************************************************************/
u_int16 ATBMSignalStrength_TDAC2_C02A(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;
    u_int16 signal_percent;

    LockValue =1; /*lock register value*/
    ATBMWrite(0x08,0x4d, LockValue);

    pwm0 = ATBMRead(0x10, 0x28);
    pwm1 = ATBMRead(0x10, 0x29);

    LockValue = 0;
    ATBMWrite(0x08,0x4d, LockValue);
    pwm_value = (u_int16)(((pwm1&0x03)<<8)|pwm0);

    /*ALPS TDAC2-C02A tuner Reference evaluation*/
    if(pwm_value <=380)
    {
        signal_percent = 90;
    }
    else if(pwm_value <=870)
    {
        signal_percent = (u_int16)((870 - pwm_value)/7 + 20);
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
Parameters:  none
Return:      signal_percent

Description:
      This function checks ATBM884x IF AGC power. It can be used for Maxim2165 signal
      strength evaluation.
      This is reference code for maxim silicon tuner(maxim2165).
      Range:  20--80. This is for reference only. For specific Tuner the range may be changed
*****************************************************************************/
u_int16 ATBMSignalStrength_Maxim2165(void)
{
    u_int8 pwm0, pwm1,LockValue;
    u_int16 pwm_value;
    u_int16 signal_percent;

    LockValue =1; /*lock register value*/
    ATBMWrite(0x08,0x4d, LockValue);

    pwm0 = ATBMRead(0x10, 0x28);
    pwm1 = ATBMRead(0x10, 0x29);

    LockValue = 0;
    ATBMWrite(0x08, 0x4d, LockValue);
    pwm_value = (u_int16)(((pwm1&0x03)<<8)|pwm0);

    /*maxim2165 Reference*/
    if(pwm_value <235)
    {
        signal_percent = 80;
    }
    else if(pwm_value <655)
    {
        signal_percent = (u_int16)((775 - pwm_value) /6);
    }
    else
    {
        signal_percent = 20;
    }

    return signal_percent;
}


/****************************************************************************
Function:    ATBMGetTPS
Parameters:  none
Return:      TPS_index

Description:
      This function checks signal TPS. The return value is TPS index in GB20600-2006
 ****************************************************************************/
u_int8 ATBMGetTPS(void)
{
    u_int8 TPS_index;

    TPS_index = ATBMRead(0x0d, 0x04);

    return TPS_index;
}

/****************************************************************************
Function:    ATBM_Standby
Parameters:  none
Return:      none

Description:
      This function put demodulator in standby mode, it can cut off part power,
      the demodulator can wake up at once by calling ATBM_Standby_WakeUp.
      two goals:
      1, cut off part power when demodulator put in standby mode
      2, put TS output pin in high-z state.
 ****************************************************************************/
void ATBM_Standby(void)
{
    u_int8 adc_pd;
    u_int8 ts_edge;
    u_int8 ref_stdby;
    u_int8 adc_rfv;
    u_int8 gpo_reg;
    ATBM_ChipID = ATBMChipID();
    ref_stdby = ATBMRead(0x06, 0x00);
    adc_pd = ATBMRead(0x06, 0x02);
    ts_edge = ATBMRead(0x03, 0x01);

    ref_stdby|= 0x02; //bit1 set 1
    adc_pd|=0x01;     //bit0 set 1
    ts_edge|= 0x02;   //bit1 set 1
    //The following registers' sequency should not be changed
    ATBMWrite(0x00, 0x05, 0x01);
    if(ATBM_ChipID == 0x30)
    {
        adc_rfv = ATBMRead(0x06, 0x0d);
        adc_rfv|=0x08;
        ATBMWrite(0x06, 0x0d, adc_rfv);
    }
    ATBMWrite(0x06, 0x00, ref_stdby);
    ATBMWrite(0x06, 0x02, adc_pd);
    ATBMWrite(0x15, 0x00, 0x00);
    ATBMWrite(0x03, 0x01, ts_edge); //all TS output PINs will be high-z
    if(ATBM_ChipID == 0x20)
    {
        ATBMWrite(0x00, 0x08, 0x01);
    }
    if(ATBM_ChipID == 0x30)
    {
        gpo_reg = ATBMRead(0x10, 0xf7);
        gpo_reg|=0x01;  //bit0 set 1
        ATBMWrite(0x10, 0xf7, gpo_reg);
        ATBMWrite(0x00, 0x19, 0x00);

    }

}

/****************************************************************************
Function:    ATBM_Standby_WakeUp
Parameters:  none
Return:      none

Description:
      Put demodulator in previous normal working mode from standby mode
 ****************************************************************************/
void ATBM_Standby_WakeUp(void)
{
    u_int8 adc_pd;
    u_int8 ts_edge;
    u_int8 ref_stdby;
    u_int8 adc_rfv;
    u_int8 gpo_reg;
    ATBM_ChipID = ATBMChipID();
    ref_stdby = ATBMRead(0x06, 0x00);
    adc_pd = ATBMRead(0x06, 0x02);
    ts_edge = ATBMRead(0x03, 0x01);

    ref_stdby&=0xfd;  //bit1 set 0
    adc_pd&=0xfe;     //bit0 set 0
    ts_edge&=0xfd;    //bit1 set 0
    //The following registers' sequency should not be changed
    ATBMWrite(0x06, 0x00, ref_stdby);
    ATBMWrite(0x06, 0x02, adc_pd);
    ATBMWrite(0x15, 0x00, 0x01);
    ATBMWrite(0x03, 0x01, ts_edge); //all TS output PINs will be in normal mode
    if(ATBM_ChipID == 0x20)
    {
        ATBMWrite(0x00, 0x08, 0x00);
    }
    if(ATBM_ChipID == 0x30)
    {
        gpo_reg = ATBMRead(0x10, 0xf7);
        adc_rfv = ATBMRead(0x06, 0x0d);
        gpo_reg&=0xfe; //bit 0 set 0
        adc_rfv&=0xf7;
        ATBMWrite(0x10, 0xf7, gpo_reg);
        ATBMWrite(0x06, 0x0d, adc_rfv);
        ATBMWrite(0x00, 0x19, 0x01);
    }
    ATBMWrite(0x00, 0x05, 0x00);
}

/****************************************************************************
Function:    ATBMDebugRegister
Parameters:  none
Return:      none

Description:
      This function checks Demodulator registers,  used for debug purpose
 ****************************************************************************/
void ATBMDebugRegister(void)
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
    /*tuner AGC limit*/
    u_int8 tuner_AGC_Min;
    u_int8 tuner_AGC_Maxm, tuner_AGC_Maxh;
    u_int8 fatal_rst, weak_rst;
    /*TS interface configuration*/
    u_int8 SamplingEdegeMode;
    u_int8 SerialEnabled;
    u_int8 ClockOutSelect;

    software_version = ATBMRead(0x02, 0x0c);
    demod_state = ATBMRead(0x06, 0x07);
    config_done = ATBMRead(0x00, 0x04);
    dsp_reset = ATBMRead(0x00, 0x0A);
    printf("Current software version: %d\n", software_version);
    printf("demod_state:0x%x configure done:0x%x dsp_reset:0x%x\n",demod_state, config_done,dsp_reset);

    /*Demod passing I2C commands between host and tuner. 0:disable 1:enable.*/
    i2c_bybass_state = ATBMRead(0x01, 0x03);
       CAN_Tuner = ATBMRead(0x00, 0x01);
    printf("bypass state:0x%x; CAN Tuner used(silicon tuner=0):0x%x\n", i2c_bybass_state, CAN_Tuner);

    ADC_config = ATBMRead(0x06, 0x02);
    LNA_on_off = ATBMRead(0x10, 0x30);
    printf("For silicon tuner ADC_config: 0x%x; LNA_on_off: 0x%x\n", ADC_config, LNA_on_off);

       freq_offset = ATBMRead(0x08, 0x00);
    printf("freq_offset 0x08_0x00: 0x%x\n", freq_offset);
    freq_offset = ATBMRead(0x08, 0x01);
    printf("freq_offset 0x08_0x01: 0x%x\n", freq_offset);

    u8RXFLT[0] = ATBMRead(0x0A, 0x00);
    u8RXFLT[1] = ATBMRead(0x0A, 0x01);
    u8RXFLT[2] = ATBMRead(0x0A, 0x02);
    u8RXFLT[3] = ATBMRead(0x0A, 0x03);
    u8RXFLT[4] = ATBMRead(0x0A, 0x04);
    u8RXFLT[5] = ATBMRead(0x0A, 0x05);
    printf("IF freq_lif: 0x%x 0x%x  0x%x\n", u8RXFLT[0], u8RXFLT[1], u8RXFLT[2]);
    printf("ADC rate ratio: 0x%x 0x%x  0x%x\n", u8RXFLT[3], u8RXFLT[4], u8RXFLT[5]);

    tuner_AGC_Min = ATBMRead(0x10, 0x20);
    tuner_AGC_Maxm = ATBMRead(0x10, 0x23);
    tuner_AGC_Maxh = ATBMRead(0x10, 0x24);
    printf("tuner_AGC_Min:0x%x; tuner_AGC_Max_M:0x%x,tuner_AGC_Max_H:0x%x\n", tuner_AGC_Min,tuner_AGC_Maxm, tuner_AGC_Maxh);

    fatal_rst = ATBMRead(0x00, 0x09);
    weak_rst = ATBMRead(0x00, 0x0a);
    printf("DSP reset options fatal_rst = 0x%x, weak_rst =  0x%x\n", fatal_rst, weak_rst);

    SamplingEdegeMode = ATBMRead(0x03, 0x01);/*0x00: rising edge TS output; 0x01: falling edge TS output*/
    SerialEnabled = ATBMRead(0x03, 0x05);    /*0: disable serial mode; 1: enable serial mode */
    ClockOutSelect = ATBMRead(0x03, 0x0b);   /*0: SPI clock output; 1: TS serial clock output */

    printf("TS interface SerialEnabled= %d SamplingEdegeMode =%d, clock select ClockOutSelect%d\n",\
        SerialEnabled,SamplingEdegeMode, ClockOutSelect);

}

/****************************************************************************
Function:      ATBMCarrierOffset
Parameters:    none
Return:        double(KHz)

Description:
      This function checks DTMB signal carrier offset on field testing environment.
      This function is not meant to be used by customers. It's a debug utility to be used by FAEs.
 ****************************************************************************/
u_int32 ATBMCarrierOffset(void)
{
    u_int32 mCarrierOffset = 0;
    u_int8 pbuff[4];
    u_int8 LockValue, chip_id;
    chip_id = ATBMRead(0x00, 0x00);

    LockValue =1; /*lock register value*/
    ATBMWrite(0x08, 0x4d, LockValue);

    pbuff[0]=ATBMRead(0x08, 0x27);//carrier_offset_est[7:0]
    pbuff[1]=ATBMRead(0x08, 0x28);//carrier_offset_est[15:8]
    pbuff[2]=ATBMRead(0x08, 0x29);//carrier_offset_est[21:16]

    LockValue = 0; /*lock register value*/
    ATBMWrite(0x08, 0x4d, LockValue);
    /*=  carrier offset  =*/
    if(chip_id == 0x20)
    {
        if(pbuff[2]&0x20)
        {
            mCarrierOffset = (0x3fffff+1- (((pbuff[2]&0x3f)<<16)+(pbuff[1]<<8)+pbuff[0]))*1434/10000;
            mCarrierOffset = (mCarrierOffset/1000);
            ATBM_DBINFO(printf("DTMB signal  Carrier Offset = -%d KHz\n", mCarrierOffset));
        }
        else
        {
            mCarrierOffset= ((((pbuff[2]&0x3f)<<16)+(pbuff[1]<<8)+pbuff[0]))*1434/10000;
            mCarrierOffset = mCarrierOffset/1000;
            ATBM_DBINFO(printf("DTMB signal Carrier Offset = %d KHz\n", mCarrierOffset));
        }
    }
    if(chip_id == 0x30)
    {
        if(pbuff[2]&0x80)
        {
            mCarrierOffset = (0xffffff+1- (((pbuff[2]&0xff)<<16)+(pbuff[1]<<8)+pbuff[0]))*1434/10000;
            mCarrierOffset = (mCarrierOffset/1000);
            ATBM_DBINFO(printf("DTMB signal  Carrier Offset = -%d KHz\n", mCarrierOffset));
        }
        else
        {
            mCarrierOffset= ((((pbuff[2]&0xff)<<16)+(pbuff[1]<<8)+pbuff[0]))*1434/10000;
            mCarrierOffset = mCarrierOffset/1000;
            ATBM_DBINFO(printf("DTMB signal Carrier Offset = %d KHz\n", mCarrierOffset));
        }
    }
    return mCarrierOffset;
}

/****************************************************************************
Function:    ATBMWriteRegArray
Parameters:  *reg_table, table_len
Return:      none

Description:
      This function writes a group of registers to demodulator
 ****************************************************************************/
void ATBMWriteRegArray(u_int8 *reg_table, u_int32 table_len)
{
   u_int32 i;
   for(i=0;i<table_len;i+=3)
   {
         ATBMWrite(reg_table[i],reg_table[i+1],reg_table[i+2]);
         //printf("%x %x %x\n", reg_table[i],reg_table[i+1], reg_table[i+2]);
   }
}


/****************************************************************************
Function:    ATBMDebugRegArray
Parameters:  *reg_table, table_len
Return:      none

Description:
     This function reads a group of registers from demodulator and prints them
     for debug purposes.
 ****************************************************************************/
void ATBMDebugRegArray(u_int8 *reg_table, u_int32 table_len)
{
   u_int32 i;
   u_int8 reg_data;
   for(i=0;i<table_len;i+=3)
   {
        reg_data = ATBMRead(reg_table[i],reg_table[i+1]);

        ATBM_DBINFO(printf("%x %x  %x\n", reg_table[i], reg_table[i+1], reg_data));
   }
}

 /******************************************************************************/
///Read bytes, be able to read 1 byte or several bytes from several register offsets in same slave address.
///@param u16BusNumSlaveID \b IN: Bus Number (high byte) and Slave ID (Address) (low byte)
///@param u8AddrNum \b IN:  register NO to read, this parameter is the NO of register offsets in pu8addr buffer,
///it should be 0 when *paddr = NULL.
///@param *paddr \b IN: pointer to a buffer containing target register offsets to read
///@param u16size \b IN: Data length (in byte) to read
///@param *pu8data \b IN: pointer to retun data buffer.
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
#define SWIIC_READ      0
#define SWIIC_WRITE     1

BOOLEAN MDrv_IIC_A7_ReadBytes(U16 u16BusNumSlaveID, U8 ucSubAdr, U8* paddr, U16 ucBufLen, U8* pBuf)
{
    U8 u8Dummy; // loop dummy
    BOOLEAN bRet;

    u8Dummy = 3;
    bRet = FALSE;
    ucSubAdr = 0;
    paddr = NULL;

  #if 1
    printf("\n !!! %s, %d TO DO \n",__FILE__, __LINE__);
  #else
    IIC_UseBus(HIBYTE(u16BusNumSlaveID));
  #endif

    while (u8Dummy--)
    {
        if (IIC_AccessStart(LOBYTE(u16BusNumSlaveID), SWIIC_READ) == FALSE)
        {
            continue;
        }
        MsOS_DelayTask(1);

        while (ucBufLen--) // loop to burst read
        {
            *pBuf = IIC_GetByte(ucBufLen); // receive byte
            pBuf++; // next byte pointer
        }

        break;
    }
    bRet = TRUE;

    return bRet;
}

/****************************************************************************
Function:    ATBMRead
Parameters:  base_address, register_address
Return:      reg_data[0]

Description:
     ATBM884x demodulator register Reading API, decoder platform independent.
     It calls I2Cwrite and i2CRead functions that should be implemented by
     customers based on customers' platforms.

****************************************************************************/
u_int8  ATBMRead(u_int8 base_addr, u_int8 register_addr)
{
    int retval = 0;
    u_int8 addr_data[2];
    u_int8 reg_data[1];
    //Add mutex lock here if there is multi-thread operation of demodulator's I2C
    //the following I2C operations will not be interrupted.
    addr_data[0] = base_addr;
    addr_data[1] = register_addr;

    //returned status from low level I2C interface shoud be processsed here if needed.
    retval = I2CWrite(ATBMSlaveAddr, addr_data, 2);
    retval = I2CRead(ATBMSlaveAddr, reg_data, 1);

    //Release mutex lock.
    return(reg_data[0]);
}


/****************************************************************************
Function:        ATBMWrite
Parameters:  base_address, register_address, data
Return:      none

Description:
     ATBM884x demodulator register Writing API, decoder platform independent.
     It calls I2Cwrite and i2CRead functions that should be implemented by
     customers based on customers' platforms.

****************************************************************************/
void ATBMWrite(u_int8 base_addr, u_int8 register_addr, u_int8 data)
{
    int retval = 0;
    u_int8 addr_data[2];
    u_int8 reg_data[1];
    //Add mutex lock here if there is multi-thread operation of demodulator's I2C
    //the following I2C operations will not be interrupted.

    addr_data[0] = base_addr;
    addr_data[1] = register_addr;
    reg_data[0] = data;

    //returned status from low level I2C interface shoud be processsed here if needed.
    retval = I2CWrite(ATBMSlaveAddr, addr_data, 2);
    retval = I2CWrite(ATBMSlaveAddr, reg_data, 1);

    //Release mutex lock

}

/****************************************************************************
Function:    ATBMTransRead
Parameters:  base_address, register_address
Return:      reg_data[0]

Description:
     ATBM884x demodulator register Reading API, decoder platform independent.
     It calls I2Cwrite and i2CRead functions that should be implemented by
     customers based on customers' platforms.

     This function is used for DVB-C transfer. it use two step I2C operations
     as ATBMWRead.
     **Should not add I2C mutex lock in this API. refer ATBM_DVBC_Write and ATBM_DVBC_Read
****************************************************************************/
u_int8  ATBMTransRead(u_int8 base_addr, u_int8 register_addr)
{
    int retval = 0;
    u_int8 addr_data[2];
    u_int8 reg_data[1];

    addr_data[0] = base_addr;
    addr_data[1] = register_addr;

    //returned status from low level I2C interface shoud be processsed here if needed.
    retval = I2CWrite(ATBMSlaveAddr, addr_data, 2);
    retval = I2CRead(ATBMSlaveAddr, reg_data, 1);

    return(reg_data[0]);
}


/****************************************************************************
Function:        ATBMTransWrite
Parameters:  base_address, register_address, data
Return:      none

Description:
     ATBM884x demodulator register Writing API, decoder platform independent.
     It calls I2Cwrite and I2CRead functions that should be implemented by
     customers based on customers' platforms.

     This function is used for DVB-C transfer. it use two step I2C operations
     as ATBMWrite.
     **Should not add I2C mutex lock in this API. refer ATBM_DVBC_Write and ATBM_DVBC_Read
****************************************************************************/
void ATBMTransWrite(u_int8 base_addr, u_int8 register_addr, u_int8 data)
{
    int retval = 0;
    u_int8 addr_data[2];
    u_int8 reg_data[1];

    addr_data[0] = base_addr;
    addr_data[1] = register_addr;
    reg_data[0] = data;

    //returned status from low level I2C interface shoud be processsed here if needed.
    retval = I2CWrite(ATBMSlaveAddr, addr_data, 2);
    retval = I2CWrite(ATBMSlaveAddr, reg_data, 1);

    //printf("%x %x %x\n", base_addr, register_addr, data);

}

/****************************************************************************

   The following are APIs users need to implement based on their platform.

****************************************************************************/
extern int I2CWrite(u_int8 I2CSlaveAddr, u_int8 *data, int length)  
{
    int retval = 0;
    retval=MDrv_IIC_WriteBytes(((U16)DEMOD_IIC_BUS<<8)|I2CSlaveAddr,length,data,0,NULL);
    if(!retval)
    {
        printf("\r\n I2C Write Fail!!\n"); 
    }
    return(retval);
}

extern int  I2CRead(u_int8 I2CSlaveAddr, u_int8 *data, int length)  
{
     int retval = 0;
     retval=MDrv_IIC_A7_ReadBytes(((U16)DEMOD_IIC_BUS<<8)|I2CSlaveAddr,0,NULL,length,data);
     if(!retval)
     {
         printf("\r\n I2C Read Fail!!\n");
     }
     return(retval);
}

extern void DemodHardwareReset(void)
{
   // <to be implemented by user>
   Demodulator_OFF();
   msAPI_Timer_Delayms(15);
   Demodulator_ON();
}

extern void Delayms (int ms)
{
 //  <to be implemented by user>
  msAPI_Timer_Delayms(ms);
}




