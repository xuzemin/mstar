#ifndef _DRVTUNER_AV2017_H_
#define _DRVTUNER_AV2017_H_

/***enumerator structures************************************************************/
typedef enum
{							// I2C Write Address setting by Hardware pins
	ADDR1_L_ADDR0_L = 0xC0, // Hardware Pin17 ADDR1 = GND , Pin14 ADDR0 = GND 
	ADDR1_L_ADDR0_H = 0xC2, // Hardware Pin17 ADDR1 = GND , Pin14 ADDR0 = OPEN
	ADDR1_H_ADDR0_L = 0xC4, // Hardware Pin17 ADDR1 = OPEN, Pin14 ADDR0 = GND
	ADDR1_H_ADDR0_H = 0xC6	// Hardware Pin17 ADDR1 = OPEN, Pin14 ADDR0 = OPEN
} 
TUNER_I2C_ADDRESS; 

typedef enum           
{                      // For Tuner model name =1 only
	Differential = 0,  // IQ Differential mode
	Single = 1         // IQ Single end mode, only output at RXIP, RXQP
}
TUNER_IQ_MODE;

typedef enum          // BaseBand programmable amplifier gain setting
{
	PGA_0dB     =0,
	PGA_1_5dB   =1,
	PGA_3dB     =2,
	PGA_4_5dB   =3,
	PGA_6dB     =4,
	PGA_7_5dB   =5,
	PGA_9dB     =6,
	PGA_10_5dB  =7,
	PGA_12dB    =8
}
TUNER_PGA_GAIN;

typedef enum		 // BaseBand programmable amplifier output driving current setting
{
	PGA_500uA =0,
	PGA_1mA   =1,
	PGA_1_5mA =2,
	PGA_2mA   =3
}
TUNER_PGA_DRIVE_CURRENT;

typedef enum
{
	LOW_AV2017       =0,
	MEDIUM_AV2017    =1,
	HIGH_AV2017      =2,
	MAXIMUM_AV2017   =3
}
TUNER_XO_DRIVE_CURRENT;

typedef enum          // Crystal oscillator ON/OFF for stand-by
{
	XO_OFF = 0,
	XO_ON = 1 
}
TUNER_XO_ENABLE;

typedef enum         // RF loop through ON/OFF
{
	RFLP_OFF = 0,  
	RFLP_ON = 1    
}
TUNER_RFLP_ENABLE;

typedef enum        // power down setting for stand-by
{
	Wake_Up = 0,    //0 = Wake up Tuner
	Power_Down = 1  //1 = Power down Tuner	
}
TUNER_SOFTWARE_POWERDOWN;

typedef enum            // Fine-tune function setting
{
	FT_OFF      = 0x00,	// FT_block=0, FT_EN=0, FT_hold=0. The Gain is at best sensitivity gain. 
	FT_ON       = 0x02,	// FT_block=0, FT_EN=1, FT_hold=0. Turn on to fine-tuned gain continuously between sensitivity and linearity.
	FT_Hold     = 0x03, // FT_block=0, FT_EN=1, FT_hold=1. Stop fine-tuning the gain and hold the current fine-tuned gain
	FT_Delay_ON = 0x06	// FT_block=1, FT_EN=1, FT_hold=0. Turn on Fine-tune Function after 12ms delay	
}
TUNER_FINE_TUNE;

typedef enum            // Error code of tuner at different error status 
{
	Tuner_No_Error    =0,
	Tuner_Error		  =1,	
	PLL_Lock_Error    =3,
	Filter_Lock_Error =5,
	I2C_Error         =9
}
TUNER_ErrorCode;


/***tuner parameter structures************************************************************/
typedef struct
{                                              
	/** Tuner Hardware variables**/
	UINT32                   crystal_khz;	 // (Unit:KHz) Tuner_crystal supporting range: 13000~37000KHz 	
	
	TUNER_I2C_ADDRESS        I2C_ADDR;		 // Tuner I2C address at write mode 

	/** Tuner Register varaibles**/
	TUNER_IQ_MODE            IQmode;		 // RXIQ differential out or Single out 
	TUNER_PGA_GAIN           PGA_Gain;       // RXout BaseBand Programmable gain 
	TUNER_PGA_DRIVE_CURRENT  PGA_Current;    // RXout BaseBand PGA output driving current
	TUNER_XO_DRIVE_CURRENT   XO_Current;     // Crystal oscillator driving current 
	TUNER_XO_ENABLE          XO_EN;			 // Crystal oscillator ON/OFF	
	TUNER_RFLP_ENABLE        RFLP_EN;		 // Loopthrough ON/OFF   
	TUNER_SOFTWARE_POWERDOWN PD_EN;          // Tuner software power down ON/OFF  
	TUNER_FINE_TUNE          FT;	         // Front-end Gain fine tune between linearity and sensitvity

	UINT8			         blind_scan;     // System Blind Scan indication for fine-tune function
}
TunerPara, *pTunerPara;

MS_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);
MS_BOOL MDrv_DVBS_Tuner_Initial(void);
MS_BOOL MDrv_DVBS_Tuner_CheckLock(void);

#endif
