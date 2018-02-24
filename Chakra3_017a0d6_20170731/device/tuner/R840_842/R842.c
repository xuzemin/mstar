//-----------------------------------------------------//
//                                                     //
// Filename: R842.c                                    //
//                                                     //
// This file is R842 tuner driver                      //
// Copyright 2015 by Rafaelmicro., Inc.                //
// Author: Jason Wang                                  //
//-----------------------------------------------------//


//<<SMC jayden.chen add for R842 20150616
#include "drvIIC.h"
#include "msAPI_Timer.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"
#include "apiAUDIO.h"
//>>SMC jayden.chen add for R842 20150616
#include "R842.h"
//#include "..\I2C_Sys.h"    // "I2C_Sys" is only for SW porting reference.

#define  R842_FOR_HIS_S11       FALSE
#define  R842_FOR_SEC           FALSE
#define  R842_FOR_LGIT          FALSE    //LGIT set TRUE
#define  R842_FOR_SEMCO_MODULE  FALSE    //SEMCO module; SEMCO set TRUE
#define  R842_MTK_ATV_TEST      FALSE   
#define  R843_TUNER             FALSE  

#if(R842_FOR_LGIT==TRUE || R842_FOR_SEMCO_MODULE==TRUE)
#define  R842_ALL_IMR_NOR      TRUE    //TRUE: all use IMR normal
#else
#define  R842_ALL_IMR_NOR      TRUE   //TRUE(new CTMR) or FALSE(old CTMR)
#endif

#define  R842_DTV_AGC_SLOW        FALSE  //default FALSE
#define  R842_FILTER_GAIN_DELAY   2    //3 or 2
#define  R842_FILTER_CODE_DELAY   2    //2
#define  R842_XTAL_CHK_DELAY      10
#define  R842_PLL_LOCK_DELAY      10
UINT32 R842_ADC_READ_DELAY = 2;        //3 or 2
UINT8  R842_ADC_READ_COUNT = 1;
UINT32 R842_IMR_IF = 5300;
//----------------- User Parameter (set by user) ---------------//
//*** share Xtal options ***//
//1. R842_NO_SHARE_XTAL
//2. R842_MASTER_TO_SLAVE_XTAL_IN              //R842+RT710
//3. R842_MASTER_TO_SLAVE_XTAL_OUT
//4. R842_SLAVE_XTAL_OUT                                 //pure ATV
UINT8   R842_SHARE_XTAL = R842_NO_SHARE_XTAL;

//*** Internal Xtal cap ***//
//Xtal CL*2 = (R842_XTAL_CAP+External Cap)
//for share Xtal, set to 0. use external cap to tune freq. deviation.
#if(R842_FOR_SEMCO_MODULE==TRUE || R842_FOR_LGIT==TRUE)
UINT8   R842_XTAL_CAP = 13;    //13pF
#else
UINT8   R842_XTAL_CAP = 38;    //range 0~41
#endif

//*** Mid Band TF select ***//
//1. L19=27nH: R842_MID_USING_27NH
//2. L19=39nH: R842_MID_USING_39NH
//3. L19=68nH: R842_MID_USING_68NH
UINT8 R842_DetectMidTfType = R842_MID_USING_39NH;   

//MT4: 39nH(Others) / 68nH(DTMB)
//MT2: 27nH
//------------------------------------------------------------------------//

UINT16 R842_Xtal = 24000;	   //only support 24MHz Xtal
//UINT16 R842_Xtal = 27000;	

UINT8 R842_iniArray[3][R842_REG_NUM] = {                  
	{     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //24M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
           0x84, 0xFE, 0x1C, 0x90, 0x60, 0x26, 0x00, 0xAC, 
	//     0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F                                                   	   													  						  
		   0x00, 0x7F, 0x22, 0x00, 0x70, 0x80, 0x91, 0x79, 
	//     0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17                                                     	   
           0x3A, 0x07, 0x8D, 0xAA, 0xAA, 0x1C, 0x2C, 0x1C, 
	//     0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F  
		   0x01, 0x1E, 0x00, 0x4D, 0xDC, 0x3B, 0x59, 0x59,   //fast deglitch 45ms
//           0x01, 0x1E, 0x00, 0x4C, 0xDC, 0x3B, 0x59, 0x59, //fast deglitch 70ms
	//     0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 
		   0xB6, 0xAB, 0xA2, 0x55, 0x15, 0xF7, 0xED, 0x01 },
	//     0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F 

	{     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //16M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
           0x84, 0xFE, 0x1C, 0x90, 0x60, 0x26, 0x00, 0xAC, 
	//     0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F                                                   	   													  						  
		   0x00, 0x7F, 0x22, 0x00, 0x70, 0x80, 0x91, 0x79, 
	//     0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17                                                     	   
           0x3A, 0x07, 0x95, 0x00, 0x00, 0x1F, 0x2C, 0x1C, 
	//     0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F 
		   0x01, 0x1E, 0x00, 0xCD, 0xDC, 0x3B, 0x59, 0x59,
	//     0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 
		   0xB6, 0xAB, 0xA2, 0x55, 0x15, 0xF7, 0xED, 0x01 },
	//     0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F		

	{     0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //27M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
           0x84, 0xFE, 0x1C, 0x90, 0x60, 0x26, 0x00, 0xAC, 
	//     0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F                                                   	   													  						  
		   0x00, 0x7F, 0x22, 0x00, 0x70, 0x80, 0x91, 0x79, 
	//     0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17                                                     	   
           0x3A, 0x07, 0x8B, 0x5E, 0x42, 0x1C, 0x2C, 0x1C, 
	//     0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F 
		   0x01, 0x1E, 0x00, 0x8D, 0xDC, 0x3B, 0x59, 0x59,
	//     0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 
		   0xB6, 0xAB, 0xA2, 0x55, 0x15, 0xF7, 0xED, 0x01 },
	//     0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F
};

UINT8 R842_XtalDiv = R842_XTAL_DIV1_11;
UINT8 R842_ADDRESS = 0xF6;	               //R843 I2C addr is 0x36
UINT8 R842_Chip = R842_MT;	
UINT8 R842_Poly = R842_Poly_5;
#if(R842_FOR_LGIT==TRUE || R842_FOR_SEMCO_MODULE==TRUE || R842_FOR_SEC==TRUE)		         
UINT8 R842_ATV_IF = R842_8296;             //8296 IF
#else	
UINT8 R842_ATV_IF = R842_NORMAL;       //rafael IF
#endif
UINT8 R842_SetTfType = R842_TF_BEAD_27N;   //default: DTV
UINT8 R842_DetectTfType = R842_UL_USING_BEAD;  //Bead, 270n, 390n
UINT8 R842_Fil_Cal_Gap = 16;  
UINT32 R842_IF_HIGH = 8500;  
UINT8 R842_Xtal_Pwr = R842_XTAL_HIGHEST;         
UINT8 R842_Xtal_Pwr_tmp = R842_XTAL_HIGHEST; 
UINT8 R842_Mixer_Mode = R842_IMR_NOR;

//TF Cal Array
UINT8 R842_TF_CAL_Array[3][R842_REG_NUM] = {   //24M/16M/27M
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x0C, 0xFA, 0x10, 0x90, 0xB0, 0xC1, 0x20, 0xBF,                                                   	   													  						 
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x7F, 0x69,                                                 	   
	   0x00, 0x34, 0x89, 0x55, 0x55, 0x58, 0xBE, 0x5C, 				
	   0x21, 0x3F, 0x52, 0xA3, 0xE6, 0x38, 0x38, 0x08,					
	   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x1C, 0xF2, 0x31, 0x90, 0xB0, 0xC1, 0x20, 0xBF,                                                   	   													  						 
	   0x00, 0x47, 0x86, 0x30, 0x60, 0x00, 0x00, 0x69,                                                 	   
	   0x00, 0x30, 0x90, 0x00, 0x00, 0x5F, 0x9E, 0x42, 				
	   0x29, 0x0F, 0x52, 0x23, 0xC6, 0x38, 0x38, 0x08,					
	   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x0C, 0xFA, 0x10, 0x90, 0xB0, 0xC1, 0x20, 0xBF,                                                   	   													  						 
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x7F, 0x69,                                                 	   
	   0x00, 0x34, 0x88, 0x2F, 0xA1, 0x58, 0xBE, 0x5C, 				
	   0x21, 0x3F, 0x50, 0x23, 0xE6, 0x38, 0x38, 0x08,					
	   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },
};  
//TF Mid Cal Array (no use)
UINT8 R842_TF_MID_CAL_Array[3][R842_REG_NUM] = {   //24M/16M/27M
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x0C, 0xF2, 0x70, 0x90, 0xB0, 0xC1, 0x1B, 0xBE,             
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x7F, 0x69,                                                 	   
	   0x00, 0x34, 0xA4, 0xAB, 0xAA, 0x50, 0xBA, 0x40, 				
	   0x61, 0x1E, 0x71, 0x59, 0xE6, 0x38, 0x38, 0x08,		//R32 div?
	   0x63, 0x70, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x00 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x0C, 0xF2, 0x70, 0x90, 0xB0, 0xC1, 0x07, 0xBE,     
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x7F, 0x69,   
	   0x00, 0x34, 0xB9, 0x00, 0x00, 0x53, 0xBA, 0x40,		
	   0x61, 0x1E, 0x7A, 0x59, 0xE6, 0x38, 0x38, 0x08,					
	   0x63, 0x70, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x00 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x0C, 0xF2, 0x70, 0x90, 0xB0, 0xC1, 0x1B, 0xBE,             
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x7F, 0x69,                                                 	   
	   0x00, 0x34, 0xA0, 0x7B, 0x09, 0x50, 0xBA, 0x40, 				
	   0x61, 0x1E, 0x6F, 0x19, 0xE6, 0x38, 0x38, 0x08,					
	   0x63, 0x70, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x00 }
};  
//LPF Cal Array
UINT8 R842_LPF_CAL_Array[3][R842_REG_NUM] = {   //24M/16M/27M
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x1E, 0xF2, 0x31, 0x90, 0xB0, 0x01, 0x20, 0x8F,                                                   	   													  						 
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x00, 0x69,                                                 	   
	   0x00, 0xB4, 0x8A, 0x88, 0x88, 0x5C, 0xAE, 0x42, 				
	   0x21, 0x1E, 0x52, 0x23, 0xC6, 0x38, 0x38, 0x08,					
	   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x1E, 0xF2, 0x31, 0x90, 0xB0, 0x01, 0x20, 0x8F,                                                   	   													  						 
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x00, 0x69,                                                 	   
	   0x00, 0xB4, 0x90, 0xCD, 0x4C, 0x5C, 0x8E, 0x42, 				
	   0x29, 0x1E, 0x5B, 0xE3, 0xC6, 0x38, 0x38, 0x08,					
	   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only					
	   0x1E, 0xF2, 0x31, 0x90, 0xB0, 0x01, 0x20, 0x8F,                                                   	   													  						 
	   0x00, 0x57, 0x86, 0x30, 0x60, 0x00, 0x00, 0x69,                                                 	   
	   0x00, 0xB4, 0x88, 0xCE, 0x95, 0x5C, 0xAE, 0x42, 				
	   0x21, 0x1E, 0x50, 0xA3, 0xC6, 0x38, 0x38, 0x08,					
	   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 }
};  
//IMR Cal array
UINT8 R842_IMR_CAL_Array[3][R842_REG_NUM] = {   //24M/16M/27M
	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only						   
	   0x0E, 0xF2, 0x35, 0x80, 0xB0, 0x39, 0x27, 0x8F,    
	   0x00, 0x57, 0x86, 0x20, 0x60, 0x00, 0x77, 0x69,
#if(R842_FOR_SEMCO_MODULE==TRUE)
	   0x4A, 0xEC, 0x91, 0x00, 0x00, 0x5F, 0xAE, 0x42, 	
#else
	   0x41, 0xEC, 0x91, 0x00, 0x00, 0x5F, 0xAE, 0x42, 				//ADC_hys no change
#endif
	   0x21, 0x3F, 0x51, 0xEB, 0xDE, 0x38, 0x38, 0xF8,					
	   0x63, 0xF6, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only	
	   0x0E, 0xF2, 0x35, 0x80, 0xB0, 0x39, 0x28, 0x8F,  
	   0x00, 0x57, 0x86, 0x20, 0x60, 0x00, 0x77, 0x69,
#if(R842_FOR_SEMCO_MODULE==TRUE)  
	   0x4A, 0xEC, 0x9B, 0xEB, 0x51, 0x5C, 0x8E, 0x42, 				
#else 
	   0x41, 0xEC, 0x9B, 0xEB, 0x51, 0x5C, 0x8E, 0x42,
#endif
	   0x31, 0x3F, 0x59, 0xAB, 0xDE, 0x38, 0x38, 0xF8,					
	   0x63, 0xF6, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 },

	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //read only
	   0x0E, 0xF2, 0x35, 0x80, 0xB0, 0x39, 0x27, 0x8F,
	   0x00, 0x57, 0x86, 0x20, 0x60, 0x00, 0x77, 0x69,  //poly_gain=12
#if(R842_FOR_SEMCO_MODULE==TRUE)
	   0x4A, 0xEC, 0x91, 0x00, 0x00, 0x5F, 0xAE, 0x42, 	//HPF=10			
#else
	   0x41, 0xEC, 0x91, 0x00, 0x00, 0x5F, 0xAE, 0x42, 	
#endif
	   0x21, 0x3F, 0x51, 0xEB, 0xDE, 0x38, 0x38, 0xF8,					
	   0x63, 0xF6, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x01 }
};  
//----------------------------------------------------------//
//                   Internal Parameters                    //
//----------------------------------------------------------//

UINT8 R842_Array[R842_REG_NUM]={0};
R842_Sect_Type R842_IMR_Data[R842_IMR_POINT_NUM] = 
{
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0},
	{0,0,0,0}
};
I2C_TYPE  R842_I2C;
I2C_LEN_TYPE R842_I2C_Len;

UINT8  R842_IMR_point_num;
UINT8  R842_Initial_done_flag = FALSE;
UINT8  R842_IMR_done_flag = FALSE;
UINT8  R842_Bandwidth = 0;   //8M
UINT8  R842_Lpf_Lsb = 0;   
UINT8  R842_Fil_Cal_flag[R842_STD_SIZE];
static UINT8 R842_Fil_Cal_BW[R842_STD_SIZE];
static UINT8 R842_Fil_Cal_code[R842_STD_SIZE];
static UINT8 R842_Fil_Cal_LpfLsb[R842_STD_SIZE];    
static R842_Standard_Type R842_pre_standard = R842_STD_SIZE;
static UINT8 R842_SBY[R842_REG_NUM];
static UINT8 R842_Standby_flag = FALSE;
//0(8M), 2(7M), 3(6M)
#if(R842_ATV_CIF_5M==TRUE)
static UINT8 R842_Fil_Cal_BW_def[R842_STD_SIZE]={
       3, 3, 0, 2, 2, 2, 2, 2, 0, 0,     //ATV
	   2, 0, 0, 0, 0, 0, 0, 0,           //ATV (CIF 5M)
	   3, 2, 2, 3, 2, 2, 2, 0,           //DVB-T, DVB-T2
	   0, 2, 2, 3, 2, 2, 3, 2,           //DVB-C, J83B, ISDBT, DTMB, ATSC
	   2, 2, 0, 2, 2, 0, 3,              //DVB-T, DVB-T2 (IF 5M)
	   0, 2, 2, 2, 0, 2, 2, 2            //DVB-C, J83B, ISDBT, DTMB, ATSC (IF 5M), FM
       };
static UINT8 R842_Fil_Cal_code_def[R842_STD_SIZE]={
       22, 10, 13,  0, 10,  7, 10,  1,  4, 14,     //ATV
        9,  7,  9, 15,  9,  8,  3,  9,             //ATV (CIF 5M)
        3,  8,  2,  3,  8,  2,  8,  0,             //DVB-T, DVB-T2
	    8,  4,  7,  5, 16,  1,  5,  6,             //DVB-C, J83B, ISDBT, DTMB, ATSC
	   13,  1, 13, 13,  1, 13, 23,                 //DVB-T, DVB-T2 (IF 5M)
	   11,  3, 11, 10, 11,  9,  8, 17              //DVB-C, J83B, ISDBT, DTMB, ATSC (IF 5M), FM
       };
#else //non ATV_CIF_5M
static UINT8 R842_Fil_Cal_BW_def[R842_STD_SIZE]={
       3, 3, 0, 2, 2, 2, 2, 0, 0,        //ATV
	   3, 2, 2, 3, 2, 2, 2, 0,           //DVB-T, DVB-T2
	   0, 2, 2, 3, 2, 2, 3, 2,           //DVB-C, J83B, ISDBT, DTMB, ATSC
	   2, 2, 0, 2, 2, 0, 3,              //DVB-T, DVB-T2 (IF 5M)
	   0, 2, 2, 2, 0, 2, 2, 2            //DVB-C, J83B, ISDBT, DTMB, ATSC (IF 5M), FM
       };
static UINT8 R842_Fil_Cal_code_def[R842_STD_SIZE]={
       22, 10, 13,  0, 10, 10,  1,  4, 14,         //ATV
        3,  8,  2,  3,  8,  2,  8,  0,             //DVB-T, DVB-T2
	    8,  4,  7,  5, 16,  1,  5,  6,             //DVB-C, J83B, ISDBT, DTMB, ATSC
	   13,  1, 13, 13,  1, 13, 23,                 //DVB-T, DVB-T2 (IF 5M)
	   11,  3, 11, 10, 11,  9,  8, 17              //DVB-C, J83B, ISDBT, DTMB, ATSC (IF 5M), FM
       };
#endif
static UINT8 R842_IMR_Cal_Result = 0; //1: fail, 0: ok
static UINT8 R842_TF_Check_Result = 0; //1: fail, 0: ok

//0: L270n/39n  (DTV, ATV/Cable) 
//1: Bead/68n  (China DTMB, DVB-C, ATV) 
//2: L270n/27n (all except DTMB) 
//3: Bead/27n  (China DTMB, DVB-C, ATV) 
//4: L390n/27n  (China DTMB) 
//5: L390n/39n  (for LGIT: China DTMB, DVB-C, ATV) 
UINT8  R842_TF = 0;
#if(R842_FOR_LGIT==TRUE)  //modify L270n/39n
UINT32 R842_LNA_HIGH_MID[R842_TF_SIZE] = { 508000, 484000, 620000, 620000, 620000, 508000}; 
UINT32 R842_LNA_MID_LOW[R842_TF_SIZE] = { 196000, 164000, 292000, 236000, 236000, 220000};
#else
UINT32 R842_LNA_HIGH_MID[R842_TF_SIZE] = { 508000, 484000, 620000, 620000, 620000, 508000}; 
UINT32 R842_LNA_MID_LOW[R842_TF_SIZE] = { 236000, 164000, 292000, 236000, 236000, 220000};
#endif

UINT32 R842_TF_Freq_High[R842_TF_SIZE][R842_TF_HIGH_NUM] = 
{  
	 { 720000, 696000, 664000, 624000, 608000, 560000, 544000, 512000},	 
     { 720000, 664000, 624000, 608000, 560000, 528000, 512000, 488000},
	 { 720000, 704000, 688000, 672000, 656000, 528000, 640000, 624000},
	 { 720000, 704000, 688000, 672000, 656000, 528000, 640000, 624000},
	 { 720000, 704000, 688000, 672000, 656000, 528000, 640000, 624000},
	 { 720000, 696000, 664000, 624000, 608000, 560000, 544000, 512000}
};
UINT32 R842_TF_Freq_Mid[R842_TF_SIZE][R842_TF_MID_NUM] = 
{	 
#if(R842_FOR_LGIT==TRUE)  //modify L270n/39n
      {400000, 384000, 368000, 352000, 320000, 304000, 288000, 272000, 240000, 224000, 208000}, //270n/39n
#else
	  {400000, 384000, 368000, 352000, 336000, 320000, 304000, 288000, 272000, 256000, 240000}, //270n/39n
#endif
	  {320000, 304000, 272000, 264000, 240000, 233000, 216000, 200000, 192000, 184000, 168000}, //Bead/68n 
	  {496000, 464000, 448000, 416000, 400000, 384000, 368000, 352000, 336000, 320000, 296000}, //270n/27n  
	  {496000, 464000, 448000, 416000, 400000, 368000, 336000, 304000, 288000, 272000, 240000}, //Bead/27n
	  {496000, 464000, 448000, 416000, 400000, 368000, 336000, 304000, 288000, 272000, 240000}, //390n/27n
	  {400000, 384000, 368000, 352000, 320000, 304000, 288000, 272000, 256000, 240000, 224000}  //390n/39n
};
UINT32 R842_TF_Freq_Low[R842_TF_SIZE][R842_TF_LOW_NUM] = 
{    
	  {195000, 176000, 144000, 128000, 112000, 96000, 80000, 64000, 48000},  //270n/39n
      {168000, 160000, 144000, 128000, 112000, 96000, 64000, 56000, 48000},  //Bead/68n 
	  {200000, 176000, 144000, 128000, 112000, 96000, 80000, 64000, 48000},  //270n/27n 
	  {168000, 160000, 144000, 128000, 112000, 96000, 64000, 56000, 48000},  //Bead/27n 
	  {144000, 136000, 128000, 104000, 96000, 80000, 64000, 56000, 48000},   //390n/27n
	  {144000, 136000, 128000, 104000, 96000, 80000, 64000, 56000, 48000}    //390n/39n
};


UINT8 R842_TF_Result_High[R842_TF_SIZE][R842_TF_HIGH_NUM] = 
{    
	  {0x00, 0x01, 0x02, 0x04, 0x04, 0x07, 0x09, 0x0B},
	  {0x00, 0x02, 0x04, 0x04, 0x07, 0x0A, 0x0D, 0x0E},
	  {0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04},
	  {0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04},
	  {0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x04},
	  {0x00, 0x01, 0x02, 0x04, 0x04, 0x07, 0x09, 0x0B}
};
UINT8 R842_TF_Result_Mid[R842_TF_SIZE][R842_TF_MID_NUM] = 
{    
#if(R842_FOR_LGIT==TRUE)  //modify L270n/39n
      {0x00, 0x01, 0x03, 0x03, 0x05, 0x07, 0x08, 0x0B, 0x0F, 0x13, 0x17},
#else
	  {0x00, 0x01, 0x03, 0x03, 0x04, 0x05, 0x07, 0x08, 0x0B, 0x0D, 0x0F},
#endif
      {0x00, 0x02, 0x04, 0x04, 0x07, 0x0A, 0x0D, 0x0E, 0x12, 0x12, 0x16},
	  {0x00, 0x02, 0x02, 0x04, 0x04, 0x06, 0x07, 0x09, 0x0B, 0x0C, 0x0F},
      {0x00, 0x02, 0x02, 0x04, 0x04, 0x07, 0x0B, 0x0E, 0x11, 0x13, 0x18},
	  {0x00, 0x02, 0x02, 0x04, 0x04, 0x07, 0x0B, 0x0E, 0x11, 0x13, 0x18},
	  {0x00, 0x01, 0x03, 0x03, 0x05, 0x07, 0x08, 0x0B, 0x0D, 0x0F, 0x13}
};
UINT8 R842_TF_Result_Low[R842_TF_SIZE][R842_TF_LOW_NUM] = 
{  
	  {0x00, 0x01, 0x03, 0x07, 0x0C, 0x11, 0x1B, 0x2F, 0x6D},  //270n/39n
	  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x08},  //Bead/68n
	  {0x00, 0x01, 0x03, 0x07, 0x0C, 0x11, 0x1B, 0x2F, 0x6D},  //270n/27n   
	  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x08},  //Bead/27n
	  {0x00, 0x02, 0x03, 0x03, 0x05, 0x0C, 0x19, 0x26, 0x37},  //390n/27n
	  {0x00, 0x02, 0x03, 0x03, 0x05, 0x0C, 0x19, 0x26, 0x37}   //390n/39n
};

//270n/39n, low/mid Q-on, high Q-off
static UINT16 R842_Lna_Plain_Acc_Gain[7][30] = 
{
 {0,16,30,30,44,58,73,90,106,123,139,157,175,193,214,230,248,261,276,287,296,302,312,330,348,366,382,366,384,399},   //<190
 {0,14,28,28,41,55,71,87,104,120,137,154,172,190,210,225,243,256,271,283,292,299,308,325,341,356,368,358,374,386},   //190~215
 {0,12,25,25,37,51,65,80,96,110,124,139,154,168,182,195,209,225,243,258,269,279,293,305,315,324,329,342,351,356},    //215~236
 {0,13,27,27,41,57,73,90,106,123,138,154,170,185,200,211,223,239,257,273,285,294,309,320,329,338,345,356,364,370},   //236~508
 {0, 0,17,17,52,84,112,138,161,183,202,221,240,256,274,284,295,311,328,344,356,366,381,391,401,410,418,431,440,448}, //508~590
 {0, 0,17,17,37,58,79,100,121,140,157,175,193,208,225,236,247,263,281,296,308,318,333,344,355,365,374,380,391,400},  //590~674
 {0, 0,17,17,31,47,64,81,99,117,133,152,170,188,209,221,234,247,262,274,283,291,301,313,326,339,351,339,351,363}     //>674
};

static UINT16 R842_Lna_Sharp_Acc_Gain[7][30] = 
{
 {130,130,130,130,143,157,172,188,205,222,238,256,274,293,314,314,314,327,342,355,364,371,381,381,381,381,381,365,383,400},
 {117,117,117,117,130,144,160,176,192,209,225,243,261,279,300,300,300,312,328,340,350,357,366,366,366,366,366,356,372,384},
 { 86, 86, 86, 86, 99,113,127,142,157,172,186,201,216,230,244,244,244,260,279,294,306,315,329,329,329,329,329,342,351,356},
 {104,104,104,104,115,129,143,157,172,186,200,215,229,243,257,257,257,273,292,308,320,329,344,344,344,344,344,355,363,369},
 {114,114,114,114,136,156,179,201,222,241,259,278,295,312,329,329,329,345,363,379,391,402,418,418,418,418,418,430,439,448},
 {117,117,117,117,130,145,160,177,193,209,224,240,257,272,287,287,288,304,322,337,350,360,375,375,375,375,375,381,391,400},
 {119,119,119,119,129,141,154,168,183,198,212,229,246,262,281,281,282,295,311,323,332,340,350,350,350,350,350,338,350,362}
};
/*  //Bead/68nH, Q-off
static UINT16 R842_Lna_Plain_Acc_Gain[7][30] = 
{
 {0,13,26,25,41,58,76,94,111,129,146,166,185,205,227,241,257,270,283,294,302,308,317,332,347,363,378,364,380,396},   //<190
 {0,13,27,27,42,58,75,92,110,127,144,162,181,198,218,233,250,264,279,291,300,307,317,333,351,369,387,369,387,405},   //190~215
 {0,11,23,23,38,53,69,85,101,116,130,146,161,175,191,205,221,236,254,269,280,290,304,319,334,348,362,361,376,390},   //215~380
 {0,12,22,22,32,45,58,73, 87,102,115,129,143,156,170,176,182,198,217,233,245,255,271,275,277,279,280,305,306,306},   //380~484
 {0, 0,16,22,51,83,115,140,162,185,204,224,242,259,277,286,297,313,332,347,359,369,384,395,405,414,422,431,441,449}, //484~590
 {0, 0,15,20,32,52,72,92,112,131,149,166,183,199,215,225,237,253,272,287,299,309,324,335,345,356,365,370,380,389},   //590~674
 {0, 0,15,16,30,45,59,77,93,110,126,145,163,181,201,213,226,240,255,267,277,284,295,307,320,333,345,333,345,357}     //>674
};

static UINT16 R842_Lna_Sharp_Acc_Gain[7][30] = 
{
 {116,116,116,116,131,147,165,183,201,219,236,255,275,295,317,317,318,330,344,355,363,369,378,378,378,378,378,364,380,396},
 {127,127,127,127,142,158,175,192,210,228,244,263,281,299,319,319,320,333,349,361,370,377,387,387,387,387,387,369,387,405},
 {110,110,110,110,123,138,154,170,186,202,216,232,247,261,276,276,277,293,312,327,339,348,362,362,362,362,362,361,376,389},
 { 60, 60, 60, 60, 69, 81, 92,104,117,129,141,154,166,178,191,191,191,208,227,242,254,264,280,280,280,280,280,304,306,306},
 {118,118,118,118,137,158,181,204,225,244,262,280,298,315,332,332,333,349,367,383,396,406,422,422,422,422,422,431,440,449},
 {111,111,111,111,125,138,154,169,185,200,215,230,246,260,276,276,277,293,311,326,339,349,365,365,365,365,365,370,380,389},
 {116,116,116,116,126,137,150,164,179,193,208,224,241,257,275,275,277,290,306,318,328,335,345,345,345,345,345,332,345,357} 
};
*/
static UINT8 R842_Lna_Pulse_Comp[7][30] = 
{
 {126,126,126,126,112,95,77,58,69,69,69,69,69,74,56,56,56,56,74,74,47,66,54,54,54,54,54,30,30,30},
 {136,136,136,136,120,103,85,67,77,77,77,77,77,79,56,56,56,56,78,78,78,72,64,64,64,64,64,47,47,47},
 {123,123,123,123,108,92,75,57,68,68,68,68,68,73,55,55,55,55,72,72,72,64,52,52,52,52,52,30,30,30},
 {103,103,103,103,92,79,65,51,60,60,60,60,60,66,51,51,51,51,64,64,64,55,41,41,41,41,41,18,18,18},
 {117,117,117,117,106,93,79,65,73,73,73,73,73,76,57,57,57,57,76,76,76,69,59,59,59,59,59,44,44,44},
 {118,118,118,118,105,91,76,59,66,66,66,66,66,72,54,54,54,54,70,70,70,61,48,48,48,48,48,28,28,28},
 {116,116,116,116,106,94,81,67,73,73,73,73,73,76,59,59,59,59,76,76,76,69,58,58,58,58,58,44,44,44}
};

static UINT8   R842_RfFlag, R842_PulseFlag;
static UINT8   R842_TF_Mode1, R842_TF_Mode2;
static UINT16  R842_Rf_Acc_Gain[16]={0,15,30,45,60,60,60,60,60,75,90,103,117,132,143,154};
static UINT16  R842_Mixer_Acc_Gain[16]={0,0,0,0,11,23,36,48,60,73,85,96,106,126,146,146};
static UINT16  R842_Filter_Acc_Gain[16]={0,15,30,45,60,75,90,105,120,135,150,164,180,196,213,230};
//----------------------------------------------------------//
//                   Internal static struct                 //
//----------------------------------------------------------//
static R842_SysFreq_Info_Type  R842_SysFreq_Info1;
static R842_Sys_Info_Type      R842_Sys_Info1;
static R842_Freq_Info_Type     R842_Freq_Info1;
//----------------------------------------------------------//
//                   Internal Functions                     //
//----------------------------------------------------------//
R842_ErrCode R842_TF_Check(void);
R842_ErrCode R842_Xtal_Check(void);
R842_ErrCode R842_InitReg(void);
R842_ErrCode R842_Cal_Prepare(UINT8 u1CalFlag);
R842_ErrCode R842_IMR(UINT8 IMR_MEM, UINT8 IM_Flag, UINT8 Rev_Mode);
R842_ErrCode R842_PLL(UINT32 LO_Freq, UINT16 IF_Freq, R842_Standard_Type R842_Standard);
R842_ErrCode R842_MUX(UINT32 LO_KHz, UINT32 RF_KHz, R842_Standard_Type R842_Standard);
R842_ErrCode R842_IQ(R842_Sect_Type* IQ_Pont);
R842_ErrCode R842_IQ_Tree(UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R842_Sect_Type* CompareTree);
R842_ErrCode R842_IQ_Tree5(UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R842_Sect_Type* CompareTree);
R842_ErrCode R842_CompreCor(R842_Sect_Type* CorArry);
R842_ErrCode R842_CompreStep(R842_Sect_Type* StepArry, UINT8 Pace);
R842_ErrCode R842_Muti_Read(UINT8* IMR_Result_Data);
R842_ErrCode R842_Section(R842_Sect_Type* SectionArry);
R842_ErrCode R842_F_IMR(R842_Sect_Type* IQ_Pont);
R842_ErrCode R842_IMR_Cross(R842_Sect_Type* IQ_Pont, UINT8* X_Direct);
R842_ErrCode R842_IMR_Iqcap(R842_Sect_Type* IQ_Point);   
R842_ErrCode R842_SetTF(UINT32 u4FreqKHz, UINT8 u1TfType);
R842_ErrCode R842_SetStandard(R842_Standard_Type RT_Standard);
R842_ErrCode R842_SetFrequency(R842_Set_Info R842_INFO);

R842_Sys_Info_Type R842_Sys_Sel_8296(R842_Standard_Type R842_Standard);
R842_Sys_Info_Type R842_Sys_Sel(R842_Standard_Type R842_Standard);
R842_Freq_Info_Type R842_Freq_Sel(UINT32 LO_freq, UINT32 RF_freq, R842_Standard_Type R842_Standard);
R842_SysFreq_Info_Type R842_SysFreq_Sel(R842_Standard_Type R842_Standard,UINT32 RF_freq);

UINT8 R842_Filt_Cal_ADC(UINT32 IF_Freq, UINT8 R842_BW, UINT8 FilCal_Gap);


R842_Sys_Info_Type R842_Sys_Sel(R842_Standard_Type R842_Standard)
{
	R842_Sys_Info_Type R842_Sys_Info;

	switch (R842_Standard)
	{

	case R842_MN_5100:   
		R842_Sys_Info.IF_KHz=5100;           //IF
		R842_Sys_Info.BW=2;	                 //BW=6M
		R842_Sys_Info.FILT_CAL_IF=6030;      //CAL IF
		R842_Sys_Info.HPF_COR=15;	         //R24[3:0]=15 (0.33M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1, R23[7]
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

    case R842_MN_5800: 
		R842_Sys_Info.IF_KHz=5800;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
		R842_Sys_Info.FILT_CAL_IF=6800;      //CAL IF  
		R842_Sys_Info.HPF_COR=11;	         //R24[3:0]=11  
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_I:      
		R842_Sys_Info.IF_KHz=7300;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8650;      //CAL IF  
		R842_Sys_Info.HPF_COR=13;	         //R24[3:0]=13 (0.54M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_DK: 
#if(R842_MTK_ATV_TEST==TRUE) 
		R842_Sys_Info.IF_KHz=7000;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8100;      //CAL IF     
		R842_Sys_Info.HPF_COR=15;	         //R24[3:0]=15 (0.33M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
#else
		R842_Sys_Info.IF_KHz=7300;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8550;      //CAL IF     
		R842_Sys_Info.HPF_COR=13;	         //R24[3:0]=13 (0.54M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
#endif
		break;

	case R842_PAL_B_7M:  
		R842_Sys_Info.IF_KHz=6600;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
		R842_Sys_Info.FILT_CAL_IF=7650;      //CAL IF
		R842_Sys_Info.HPF_COR=13;            //R24[3:0]=13
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

    case R842_PAL_BGH_8M:  
		R842_Sys_Info.IF_KHz=6600;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
		R842_Sys_Info.FILT_CAL_IF=7650;      //CAL IF
		R842_Sys_Info.HPF_COR=13;            //R24[3:0]=13 (0.54M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_SECAM_L: 
		R842_Sys_Info.IF_KHz=7300;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8450;      //CAL IF
		R842_Sys_Info.HPF_COR=13;            //R24[3:0]=13 (0.54M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

    case R842_SECAM_L1:   
        R842_Sys_Info.IF_KHz=2250;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9650;      //CAL IF
		R842_Sys_Info.HPF_COR=10;            //R24[3:0]=10
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

    case R842_SECAM_L1_INV: 
		R842_Sys_Info.IF_KHz=7300;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8600;      //CAL IF
		R842_Sys_Info.HPF_COR=13;            //R24[3:0]=13 (0.54M)
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

#if(R842_ATV_CIF_5M==TRUE)
	case R842_MN_CIF_5M: 
		R842_Sys_Info.IF_KHz=6750;           //IF
		R842_Sys_Info.BW=0x00;               //BW
		R842_Sys_Info.FILT_CAL_IF=7850;      //CAL IF 
		R842_Sys_Info.HPF_COR=8;             //R24[3:0]=8  
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_I_CIF_5M: 
		R842_Sys_Info.IF_KHz=7750;           //IF
		R842_Sys_Info.BW=0x00;               //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9100;      //CAL IF  
		R842_Sys_Info.HPF_COR=10;	         //R24[3:0]=10  
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_DK_CIF_5M: 
		R842_Sys_Info.IF_KHz=7750;           //IF
		R842_Sys_Info.BW=0x00;               //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9050;      //CAL IF     
		R842_Sys_Info.HPF_COR=11;	         //R24[3:0]=11
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_B_7M_6800:  
		R842_Sys_Info.IF_KHz=6800;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
		R842_Sys_Info.FILT_CAL_IF=7900;      //CAL IF
		R842_Sys_Info.HPF_COR=11;            //R24[3:0]=11
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_B_7M_CIF_5M:  
		R842_Sys_Info.IF_KHz=7250;           //IF
		R842_Sys_Info.BW=0x00;               //BW
		R842_Sys_Info.FILT_CAL_IF=8600;      //CAL IF
		R842_Sys_Info.HPF_COR=10;	         //R24[3:0]=10
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_PAL_BGH_8M_CIF_5M:
		R842_Sys_Info.IF_KHz=7750;           //IF
		R842_Sys_Info.BW=0x00;               //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9050;      //CAL IF
		R842_Sys_Info.HPF_COR=8;	         //R24[3:0]=8
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_SECAM_L_CIF_5M:
		R842_Sys_Info.IF_KHz=7750;           //IF
		R842_Sys_Info.BW=0x00;               //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9050;      //CAL IF
		R842_Sys_Info.HPF_COR=11;	         //R24[3:0]=11
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_SECAM_L1_CIF_5M:
        R842_Sys_Info.IF_KHz=2250;           //IF
		R842_Sys_Info.BW=0x00;               //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9650;      //CAL IF
		R842_Sys_Info.HPF_COR=10;	         //R24[3:0]=10
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_SECAM_L1_INV_CIF_5M:
		R842_Sys_Info.IF_KHz=7750;           //IF
		R842_Sys_Info.BW=0x00;               //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9050;      //CAL IF
		R842_Sys_Info.HPF_COR=10;            //R24[3:0]=11
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;
#endif

	case R842_DVB_T_6M: 
	case R842_DVB_T2_6M: 
		R842_Sys_Info.IF_KHz=4570;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7300;      //CAL IF
		R842_Sys_Info.HPF_COR=7;	         //R24[3:0]=7
#else
		R842_Sys_Info.FILT_CAL_IF=7550;      //CAL IF
		R842_Sys_Info.HPF_COR=8;	         //R24[3:0]=8 
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T_7M:  
	case R842_DVB_T2_7M:  
		R842_Sys_Info.IF_KHz=4570;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7920;      //CAL IF
		R842_Sys_Info.HPF_COR=9;	         //R24[3:0]=9
#else
		R842_Sys_Info.FILT_CAL_IF=7920;      //CAL IF
		R842_Sys_Info.HPF_COR=9;	         //R24[3:0]=9
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T_8M: 
	case R842_DVB_T2_8M: 
		R842_Sys_Info.IF_KHz=4570;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8280;      //CAL IF
		R842_Sys_Info.HPF_COR=11;            //R24[3:0]=12 
#else
		R842_Sys_Info.FILT_CAL_IF=8450;      //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12 
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T2_1_7M: 
		R842_Sys_Info.IF_KHz=1900;
		R842_Sys_Info.BW=1;                  //BW=7M
		R842_Sys_Info.FILT_CAL_IF=7920;      //CAL IF
		R842_Sys_Info.HPF_COR=11;	         //R24[3:0]=11
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T2_10M: 
		R842_Sys_Info.IF_KHz=5600;
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=10400;     //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12
#else
		R842_Sys_Info.FILT_CAL_IF=11000;     //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_C_8M:   
		R842_Sys_Info.IF_KHz=5070;
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=9100;      //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=11
#else
		R842_Sys_Info.FILT_CAL_IF=9550;      //CAL IF
		R842_Sys_Info.HPF_COR=11;            //R24[3:0]=11
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_C_6M:  
		R842_Sys_Info.IF_KHz=5070;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8100;      //CAL IF   
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5
#else
		R842_Sys_Info.FILT_CAL_IF=8100;      //CAL IF   
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_J83B:      //always normal for J83B
		R842_Sys_Info.IF_KHz=5070;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8000;      //CAL IF  
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5
#else
		R842_Sys_Info.FILT_CAL_IF=8100;      //CAL IF  
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_ISDB_T_4063: 
		R842_Sys_Info.IF_KHz=4063;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7120;      //CAL IF  //7200
		R842_Sys_Info.HPF_COR=9;             //R24[3:0]=9
#else
		R842_Sys_Info.FILT_CAL_IF=7150;      //CAL IF  //7200
		R842_Sys_Info.HPF_COR=11;            //R24[3:0]=11
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_ISDB_T_4570:
		R842_Sys_Info.IF_KHz=4570;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7350;      //CAL IF
		R842_Sys_Info.HPF_COR=8;             //R24[3:0]=8
#else
		R842_Sys_Info.FILT_CAL_IF=7400;      //CAL IF
		R842_Sys_Info.HPF_COR=8;             //R24[3:0]=8
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=0;           //high
		break;

	case R842_DTMB_8M_4570: 
		R842_Sys_Info.IF_KHz=4570;
		R842_Sys_Info.BW=0;                  //BW=8M		 
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8450;      //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12
#else
		R842_Sys_Info.FILT_CAL_IF=8450;      //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DTMB_6M_4500:
		R842_Sys_Info.IF_KHz=4500;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7120;      //CAL IF  
		R842_Sys_Info.HPF_COR=7;             //R24[3:0]=7
#else
		R842_Sys_Info.FILT_CAL_IF=7200;      //CAL IF  
		R842_Sys_Info.HPF_COR=8;             //R24[3:0]=8
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_ATSC:  
		R842_Sys_Info.IF_KHz=5070;
		R842_Sys_Info.BW=1;                  //BW=7M  
#if(R842_ALL_IMR_NOR==TRUE) //always normal for ATSC
		R842_Sys_Info.FILT_CAL_IF=8050;      //CAL IF   
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#else
		R842_Sys_Info.FILT_CAL_IF=8050;      //CAL IF   
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=0;           //high
		break;

    case R842_DVB_T_6M_IF_5M: 
	case R842_DVB_T2_6M_IF_5M: 
		R842_Sys_Info.IF_KHz=5000;           //IF
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7750;      //CAL IF
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#else
		R842_Sys_Info.FILT_CAL_IF=7920;      //CAL IF
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;	     //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T_7M_IF_5M:  
	case R842_DVB_T2_7M_IF_5M:  
		R842_Sys_Info.IF_KHz=5000;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8450;      //CAL IF
		R842_Sys_Info.HPF_COR=8;             //R24[3:0]=8
#else
		R842_Sys_Info.FILT_CAL_IF=8450;      //CAL IF
		R842_Sys_Info.HPF_COR=8;             //R24[3:0]=8
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T_8M_IF_5M: 
	case R842_DVB_T2_8M_IF_5M: 
		R842_Sys_Info.IF_KHz=5000;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8650;      //CAL IF
		R842_Sys_Info.HPF_COR=9;             //R24[3:0]=9
#else
		R842_Sys_Info.FILT_CAL_IF=8700;      //CAL IF
		R842_Sys_Info.HPF_COR=10;            //R24[3:0]=10
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;	     //buf 10
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_T2_1_7M_IF_5M: 
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=2;                  //BW=6M
		R842_Sys_Info.FILT_CAL_IF=6000;      //CAL IF
		R842_Sys_Info.HPF_COR=1;             //R24[3:0]=1
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_C_8M_IF_5M:  
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8800;      //CAL IF 
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12
#else
		R842_Sys_Info.FILT_CAL_IF=9250;      //CAL IF 
		R842_Sys_Info.HPF_COR=11;            //R24[3:0]=11
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DVB_C_6M_IF_5M:  
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=8200;      //CAL IF   
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#else
		R842_Sys_Info.FILT_CAL_IF=8200;      //CAL IF   
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_J83B_IF_5M:  //always use normal for J83B
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7600;      //CAL IF  
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5 
#else
		R842_Sys_Info.FILT_CAL_IF=7600;      //CAL IF  
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5 
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_ISDB_T_IF_5M: 
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)
		R842_Sys_Info.FILT_CAL_IF=7650;      //CAL IF  
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#else
		R842_Sys_Info.FILT_CAL_IF=7850;      //CAL IF  
		R842_Sys_Info.HPF_COR=3;             //R24[3:0]=3
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=3;		 //buf 10
		R842_Sys_Info.HPF_NOTCH=0;           //high
		break;

	case R842_DTMB_8M_IF_5M: 
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=0;                  //BW=8M
#if(R842_ALL_IMR_NOR==TRUE)  
		R842_Sys_Info.FILT_CAL_IF=8950;      //CAL IF  
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=8
#else
		R842_Sys_Info.FILT_CAL_IF=8800;      //CAL IF  
		R842_Sys_Info.HPF_COR=10;            //R24[3:0]=10
#endif		
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	case R842_DTMB_6M_IF_5M:
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=1;                  //BW=7M
#if(R842_ALL_IMR_NOR==TRUE)  
		R842_Sys_Info.FILT_CAL_IF=7750;      //CAL IF  
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#else
		R842_Sys_Info.FILT_CAL_IF=8100;      //CAL IF  
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;
	
	case R842_ATSC_IF_5M:  
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=1;                  //BW=7M  
#if(R842_ALL_IMR_NOR==TRUE)  
		R842_Sys_Info.FILT_CAL_IF=7920;      //CAL IF   //7900
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#else
		R842_Sys_Info.FILT_CAL_IF=7920;      //CAL IF   
		R842_Sys_Info.HPF_COR=6;             //R24[3:0]=6
#endif
		R842_Sys_Info.FILT_EXT_ENA=0;        //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=0;           //high
		break;

	case R842_FM:  
		R842_Sys_Info.IF_KHz=5000;
		R842_Sys_Info.BW=1;                  //BW=7M
		R842_Sys_Info.FILT_CAL_IF=7200;      //CAL IF
		R842_Sys_Info.HPF_COR=5;             //R24[3:0]=5
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;

	default:  //R842_DVB_T_8M
		R842_Sys_Info.IF_KHz=4570;           //IF
		R842_Sys_Info.BW=0;                  //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8280;      //CAL IF
		R842_Sys_Info.HPF_COR=12;            //R24[3:0]=12
		R842_Sys_Info.FILT_EXT_ENA=0;		 //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;         //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		 //lna=max-1 & Buf 4
		R842_Sys_Info.HPF_NOTCH=1;           //low
		break;
	}

	//Set By DTV/ATV
	if (R842_Standard < R842_ATV_SIZE)  //ATV
	{
		R842_Sys_Info.RFAGC_CTRL = 0;       //manual    (R37[7]=0)
		//R842_Sys_Info.NA_PWR_DET = 0;       //off       (R8[2]=0)
		R842_Sys_Info.RF_LTE_PSG = 0;       //no ps gain(R17[4]=0)
		R842_Sys_Info.DET_LPF_AUTO=0;       //manual    (R36[2]=0)
		R842_Sys_Info.FILT5_MAN_COMP=0;     //0         (R23[4]=0)
		R842_Sys_Info.LPF_CUR=1;            //high      (R10[5:4]=1)

#if(R842_MTK_ATV_TEST==TRUE)
		R842_Sys_Info.FILT3_COMP=0;         //0
		R842_Sys_Info.FILT5_AUTO_COMP=0;    //0   
		R842_Sys_Info.FILT5_FORCEQ=0;       //auto
#else
		R842_Sys_Info.FILT3_COMP=1;         //1         (R36[4:3]=1)
		R842_Sys_Info.FILT5_AUTO_COMP=0;    //0         (R18[6:5]=0)
		R842_Sys_Info.FILT5_FORCEQ=0;       //auto      (R36[7]=0)
#endif
	}
	else  //other DTV
	{
		R842_Sys_Info.RFAGC_CTRL = 1;       //ctrl by slow(R37[7]=1)
		//R842_Sys_Info.NA_PWR_DET = 1;       //on        (R8[2]=1)
		R842_Sys_Info.RF_LTE_PSG = 1;       //psg=7.5   (R17[4]=1)
		R842_Sys_Info.DET_LPF_AUTO=0;       //manual    (R36[2]=0)
		R842_Sys_Info.FILT3_COMP=0;         //0         (R36[4:3]=0)
		R842_Sys_Info.FILT5_AUTO_COMP=0;    //0         (R18[6:5]=0)
		R842_Sys_Info.FILT5_MAN_COMP=0;     //0         (R23[4]=0)
		R842_Sys_Info.LPF_CUR=3;            //lowest    (R10[5:4]=3)
		R842_Sys_Info.FILT5_FORCEQ=1;       //manual    (R36[7]=1)
	}

	//NA
	switch(R842_Standard)
	{
		case R842_DTMB_8M_4570:
		case R842_DTMB_6M_4500:
		case R842_DTMB_8M_IF_5M:
		case R842_DTMB_6M_IF_5M:
		case R842_DVB_C_8M:
		case R842_DVB_C_6M:
        case R842_DVB_C_8M_IF_5M:
		case R842_DVB_C_6M_IF_5M:
		case R842_J83B:
		case R842_J83B_IF_5M:
			R842_Sys_Info.NA_PWR_DET = 1;       //on       (R8[2]=0)
			break;

		default:
			R842_Sys_Info.NA_PWR_DET = 0;       //off       (R8[2]=0)
			break;
	}

	//polyphase current (--> apply to IMR?)
	if((R842_Standard==R842_ATSC) || (R842_Standard==R842_ATSC_IF_5M))
		R842_Sys_Info.POLY_CUR=0;    //high
	else if(R842_Standard<R842_ATV_SIZE)
		R842_Sys_Info.POLY_CUR=0;    //high
	else
		R842_Sys_Info.POLY_CUR=1;    //low	

	//R842_Sys_Info.TEMP=0;

	//Mixer PLL mode
#if(R842_ALL_IMR_NOR==TRUE)
	R842_Mixer_Mode = R842_IMR_NOR;  //mixer up-side tune
#else
	if (R842_Standard < R842_ATV_SIZE)  //ATV
	{
#if(R842_ATV_CIF_5M==TRUE)
		if((R842_Standard==R842_SECAM_L1_INV) || (R842_Standard==R842_SECAM_L1_INV_CIF_5M))
#else
		if(R842_Standard==R842_SECAM_L1_INV)
#endif
			R842_Mixer_Mode = R842_IMR_REV;   //mixer low-side tune
		else
			R842_Mixer_Mode = R842_IMR_NOR;  //mixer up-side tune
	}
	else if((R842_Standard==R842_ATSC) || (R842_Standard==R842_ATSC_IF_5M)) //ATSC
	{
		R842_Mixer_Mode = R842_IMR_NOR;  //mixer up-side tune
	}
	else if((R842_Standard==R842_J83B) || (R842_Standard==R842_J83B_IF_5M))  //J83B
	{
		R842_Mixer_Mode = R842_IMR_NOR;  //mixer up-side tune
	}
	else  //other DTV
	{
		R842_Mixer_Mode = R842_IMR_REV;   //mixer low-side tune
	}
#endif

	switch(R842_Standard)
	{
		//ATV
		case R842_MN_5100:	
		case R842_MN_5800:	
		case R842_PAL_I:
		case R842_PAL_DK:
		case R842_PAL_B_7M:
		case R842_PAL_BGH_8M:
		case R842_SECAM_L:
		case R842_SECAM_L1:
		case R842_SECAM_L1_INV:
#if(R842_ATV_CIF_5M==TRUE)
		case R842_MN_CIF_5M:	
		case R842_PAL_I_CIF_5M:
		case R842_PAL_DK_CIF_5M:
		case R842_PAL_B_7M_CIF_5M:
		case R842_PAL_B_7M_6800:
		case R842_PAL_BGH_8M_CIF_5M:
		case R842_SECAM_L_CIF_5M:
		case R842_SECAM_L1_CIF_5M:
		case R842_SECAM_L1_INV_CIF_5M:	
#endif

			 if(R842_DetectTfType==R842_UL_USING_BEAD) //Low=Bead
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else//Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;		
			 }
			 else  //Low=270n
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;			
			 }

			 break;

		//DVB-C
		case R842_DVB_C_8M:
		case R842_DVB_C_6M:
        case R842_DVB_C_8M_IF_5M:
		case R842_DVB_C_6M_IF_5M:

			if(R842_TF_Check_Result==1)  //fail
			{
				R842_DetectTfType = R842_UL_USING_270NH;
			}
	 
			 if(R842_DetectTfType==R842_UL_USING_BEAD)  //Low=Bead
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else  //Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;		
			 }
			 else  //Low=270n
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;						
			 }
			 break;	

		//J83B
		case R842_J83B:
		case R842_J83B_IF_5M:

			if(R842_TF_Check_Result==1)  //fail
			{
				R842_DetectTfType = R842_UL_USING_270NH;
			}

			 if(R842_DetectTfType==R842_UL_USING_BEAD)  //Low=Bead
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else  //Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;		
			 }
			 else  //Low=270n
			 {
				 R842_SetTfType = R842_TF_270N_39N;		
				 /*
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;		
				*/					
			 }
			break;

		//ATSC
		case R842_ATSC:  
		case R842_ATSC_IF_5M:  

			if(R842_TF_Check_Result==1)  //fail
			{
				R842_DetectTfType = R842_UL_USING_270NH;
			}

			 if(R842_DetectTfType==R842_UL_USING_BEAD) //Low=Bead
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else  //Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;			
			 }
			 else   //Low=270n
			 {
				 R842_SetTfType = R842_TF_270N_39N;		
				 /*
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;		
				*/	
			 }
			 break;

		//DTMB
		case R842_DTMB_8M_4570:
		case R842_DTMB_6M_4500:
		case R842_DTMB_8M_IF_5M:
		case R842_DTMB_6M_IF_5M:

			if(R842_TF_Check_Result==1)  //fail
			{
				R842_DetectTfType = R842_UL_USING_BEAD;
			}

			 if(R842_DetectTfType==R842_UL_USING_BEAD)
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else  //Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;		
			 }
			 else    //Low=270n
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;					 
			 }
			 break;

		//ISDB-T
		case R842_ISDB_T_4063:		
		case R842_ISDB_T_4570:		
		case R842_ISDB_T_IF_5M:

			if(R842_TF_Check_Result==1)  //fail
			{
				R842_DetectTfType = R842_UL_USING_270NH;
			}
				 
			 if(R842_DetectTfType==R842_UL_USING_BEAD) //Low=Bead
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else  //Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;	      	
			 }
			 else    //Low=270n
			 {
				 R842_SetTfType = R842_TF_270N_39N;		
				 /*
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;		
				*/
			 }
			 break;

		default:		//DVB-T/T2

			if(R842_TF_Check_Result==1)  //fail
			{
				R842_DetectTfType = R842_UL_USING_270NH;
			}
			 
			 if(R842_DetectTfType==R842_UL_USING_BEAD)  //Low=Bead
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_BEAD_27N;		
				 else  //Mid=68
					 R842_SetTfType = R842_TF_BEAD_68N;		
			 }
			 else   //Low=270n
			 {
				 if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27
					 R842_SetTfType = R842_TF_270N_27N;		
				 else  //Mid=39
					 R842_SetTfType = R842_TF_270N_39N;			
			 }
			 break;
	}

	return R842_Sys_Info;
}



R842_Freq_Info_Type R842_Freq_Sel(UINT32 LO_freq, UINT32 RF_freq, R842_Standard_Type R842_Standard)
{
	R842_Freq_Info_Type R842_Freq_Info;

	//----- RF dependent parameter --------
	//LNA band 
	if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  
		 R842_Freq_Info.LNA_BAND = 3;   //R15[1:0]=2'b11; low
	else if((RF_freq>=R842_LNA_MID_LOW[R842_SetTfType]) && (RF_freq<R842_LNA_HIGH_MID[R842_SetTfType]))  //388~612
		 R842_Freq_Info.LNA_BAND = 2;   //R15[1:0]=2'b10; mid
	else     // >612
		 R842_Freq_Info.LNA_BAND = 1;   //R15[1:0]=00 or 01; high 

	//----- LO dependent parameter --------
	//IMR point 
	if((LO_freq>0) && (LO_freq<205000))  
	{
         R842_Freq_Info.IMR_MEM_NOR = 0;   
		 R842_Freq_Info.IMR_MEM_REV = 4;   
	}
	else if((LO_freq>=205000) && (LO_freq<400000))  
	{
         R842_Freq_Info.IMR_MEM_NOR = 1;   
		 R842_Freq_Info.IMR_MEM_REV = 5;   
	}
	else if((LO_freq>=400000) && (LO_freq<760000))  
	{
		 R842_Freq_Info.IMR_MEM_NOR = 2;  
		 R842_Freq_Info.IMR_MEM_REV = 6;   
	}
	else 
	{
		 R842_Freq_Info.IMR_MEM_NOR = 3;
		 R842_Freq_Info.IMR_MEM_REV = 7;   
	}

	//RF polyfilter band
	if((LO_freq>0) && (LO_freq<133000))  
         R842_Freq_Info.RF_POLY = 2;   //R17[6:5]=2; low
	else if((LO_freq>=133000) && (LO_freq<205000))  
         R842_Freq_Info.RF_POLY = 1;   //R17[6:5]=1; mid
	else if((LO_freq>=205000) && (LO_freq<760000))  
		 R842_Freq_Info.RF_POLY = 0;   //R17[6:5]=0; highest    
	else
		 R842_Freq_Info.RF_POLY = 3;   //R17[6:5]=3; ultra high

	
	//LPF Cap, Notch
	switch(R842_Standard)
	{
        case R842_MN_5100:	                //ATV
		case R842_MN_5800:	
		case R842_PAL_I:
		case R842_PAL_DK:
		case R842_PAL_B_7M:
		case R842_PAL_BGH_8M:
		case R842_SECAM_L:
		case R842_SECAM_L1:
		case R842_SECAM_L1_INV:
#if(R842_ATV_CIF_5M==TRUE)
		case R842_MN_CIF_5M:	
		case R842_PAL_I_CIF_5M:
		case R842_PAL_DK_CIF_5M:
		case R842_PAL_B_7M_CIF_5M:
		case R842_PAL_B_7M_6800:
		case R842_PAL_BGH_8M_CIF_5M:
		case R842_SECAM_L_CIF_5M:
		case R842_SECAM_L1_CIF_5M:
		case R842_SECAM_L1_INV_CIF_5M:	
#endif
		case R842_DVB_C_8M:                  //Cable
		case R842_DVB_C_6M:
		case R842_J83B:
        case R842_DVB_C_8M_IF_5M:
		case R842_DVB_C_6M_IF_5M:
		case R842_J83B_IF_5M:
			if(LO_freq<77000)  
			{
				R842_Freq_Info.LPF_CAP = 15;
				R842_Freq_Info.LPF_NOTCH = 10;
			}
			else if((LO_freq>=77000) && (LO_freq<85000))
			{
				R842_Freq_Info.LPF_CAP = 15;
				R842_Freq_Info.LPF_NOTCH = 4;
			}
			else if((LO_freq>=85000) && (LO_freq<115000))
			{
				R842_Freq_Info.LPF_CAP = 13;
				R842_Freq_Info.LPF_NOTCH = 3;
			}
			else if((LO_freq>=115000) && (LO_freq<125000))
			{
				R842_Freq_Info.LPF_CAP = 11;
				R842_Freq_Info.LPF_NOTCH = 1;
			}
			else if((LO_freq>=125000) && (LO_freq<141000))
			{
				R842_Freq_Info.LPF_CAP = 9;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=141000) && (LO_freq<157000))
			{
				R842_Freq_Info.LPF_CAP = 8;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=157000) && (LO_freq<181000))
			{
				R842_Freq_Info.LPF_CAP = 6;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=181000) && (LO_freq<205000))
			{
				R842_Freq_Info.LPF_CAP = 3;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else //LO>=201M
			{
				R842_Freq_Info.LPF_CAP = 0;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			break;


		default: 

			if((LO_freq>0) && (LO_freq<73000))  
			{
				R842_Freq_Info.LPF_CAP = 8;
				R842_Freq_Info.LPF_NOTCH = 10;
			}
			else if((LO_freq>=73000) && (LO_freq<81000))
			{
				R842_Freq_Info.LPF_CAP = 8;
				R842_Freq_Info.LPF_NOTCH = 4;
			}
			else if((LO_freq>=81000) && (LO_freq<89000))
			{
				R842_Freq_Info.LPF_CAP = 8;
				R842_Freq_Info.LPF_NOTCH = 3;
			}
			else if((LO_freq>=89000) && (LO_freq<121000))
			{
				R842_Freq_Info.LPF_CAP = 6;
				R842_Freq_Info.LPF_NOTCH = 1;
			}
			else if((LO_freq>=121000) && (LO_freq<145000))
			{
				R842_Freq_Info.LPF_CAP = 4;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=145000) && (LO_freq<153000))
			{
				R842_Freq_Info.LPF_CAP = 3;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=153000) && (LO_freq<177000))
			{
				R842_Freq_Info.LPF_CAP = 2;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else if((LO_freq>=177000) && (LO_freq<201000))
			{
				R842_Freq_Info.LPF_CAP = 1;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			else //LO>=201M
			{
				R842_Freq_Info.LPF_CAP = 0;
				R842_Freq_Info.LPF_NOTCH = 0;
			}
			break;

	}//end switch(standard)

#if(R842_FOR_SEMCO_MODULE==TRUE)
	if(R842_Standard==R842_DVB_T_7M || R842_Standard==R842_DVB_T_7M_IF_5M ||
		R842_Standard==R842_DVB_T2_7M || R842_Standard==R842_DVB_T2_7M)
	{
		if((RF_freq>=195000) && (RF_freq<202000))  //198.5
		{
				R842_Freq_Info.LPF_CAP = 5;
				R842_Freq_Info.LPF_NOTCH = 6;
		}
	}
#endif

	//TF LPF setting
	switch(R842_Standard)
	{
		case R842_DTMB_8M_4570:
		case R842_DTMB_6M_4500:
		case R842_DTMB_8M_IF_5M:
		case R842_DTMB_6M_IF_5M:
			if(R842_SetTfType==R842_TF_BEAD_68N)
			{
				 if(LO_freq<=205000)  
 					 R842_Freq_Info.BYP_LPF = 1;      //low pass  (R15[6]=1)
				 else
					 R842_Freq_Info.BYP_LPF = 0;      //bypass  (R15[6]=0)
			}
			else  //R842_TF_BEAD_27N
			{
				 if(LO_freq<=157000)  
 					 R842_Freq_Info.BYP_LPF = 1;      //low pass  (R15[6]=1)
				 else
					 R842_Freq_Info.BYP_LPF = 0;      //bypass  (R15[6]=0)			
			}
			      
		break;

		default:  //other standard
			 if(LO_freq<=245000)  
 	             R842_Freq_Info.BYP_LPF = 1;      //low pass  (R15[6]=1)
			 else
				 R842_Freq_Info.BYP_LPF = 0;      //bypass  (R15[6]=0)

        break;
	}//end switch

	R842_Freq_Info.TEMP = 0;

	return R842_Freq_Info;

}



R842_SysFreq_Info_Type R842_SysFreq_Sel(R842_Standard_Type R842_Standard,UINT32 RF_freq)
{
	R842_SysFreq_Info_Type R842_SysFreq_Info;
	
	switch(R842_Standard)
	{
	case R842_MN_5100:	                            //ATV
	case R842_MN_5800:	
	case R842_PAL_I:
	case R842_PAL_DK:
	case R842_PAL_B_7M:
	case R842_PAL_BGH_8M:
	case R842_SECAM_L:
    case R842_SECAM_L1:
    case R842_SECAM_L1_INV:
#if(R842_ATV_CIF_5M==TRUE)
	case R842_MN_CIF_5M:	
	case R842_PAL_I_CIF_5M:
	case R842_PAL_DK_CIF_5M:
	case R842_PAL_B_7M_CIF_5M:
	case R842_PAL_B_7M_6800:
	case R842_PAL_BGH_8M_CIF_5M:
	case R842_SECAM_L_CIF_5M:
	case R842_SECAM_L1_CIF_5M:
	case R842_SECAM_L1_INV_CIF_5M:	
#endif

		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band
		{
			if(R842_DetectTfType==R842_UL_USING_270NH) //270nH
			{
				if(RF_freq<60000)  //<60M
				{
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
					R842_SysFreq_Info.Q_CTRL=1;               //1.5k on 
					R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
					R842_SysFreq_Info.RF_TOP=1;               //RF TOP=1     
					R842_SysFreq_Info.MIXER_TOP=15;           //MIXER TOP=15
					R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>	
					R842_SysFreq_Info.MIXER_VTH=0x09;         //MIXER VTH=1.24       
					R842_SysFreq_Info.MIXER_VTL=0x03;         //MIXER VTL=0.64         
				}
				else if((RF_freq>=60000) && (RF_freq<80000)) // 60~80M
				{
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
					R842_SysFreq_Info.Q_CTRL=1;               //1.5k on 
					R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
					R842_SysFreq_Info.RF_TOP=2;               //RF TOP=2   
					R842_SysFreq_Info.MIXER_TOP=15;           //MIXER TOP=15
					R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>								
					R842_SysFreq_Info.MIXER_VTH=0x09;         //MIXER VTH=1.24        
					R842_SysFreq_Info.MIXER_VTL=0x03;         //MIXER VTL=0.64      
				}
				else if((RF_freq>=80000) && (RF_freq<210000))  //80~210M
				{
					R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;  //Plain
					R842_SysFreq_Info.Q_CTRL=1;               //1.5k on
					R842_SysFreq_Info.ENB_ATT=3;              //normal
					R842_SysFreq_Info.RF_TOP=2;               //RF TOP=2					
					R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change>		
					R842_SysFreq_Info.MIXER_TOP=7;            //MIXER TOP=7
					R842_SysFreq_Info.MIXER_VTH=0x09;         //MIXER VTH=1.24         
					R842_SysFreq_Info.MIXER_VTL=0x03;         //MIXER VTL=0.64         
				}
				else  //>210M
				{
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
					R842_SysFreq_Info.Q_CTRL=1;               //1.5k on 
					R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
					R842_SysFreq_Info.RF_TOP=1;               //RF TOP=1     
					R842_SysFreq_Info.MIXER_TOP=15;           //MIXER TOP=15
					R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>
					R842_SysFreq_Info.MIXER_VTH=0x09;         //MIXER VTH=1.24        
					R842_SysFreq_Info.MIXER_VTL=0x03;         //MIXER VTL=0.64      
				}
				
				R842_SysFreq_Info.LNA_TOP=4;                  // LNA TOP=4              (R37[3:0]=4'b1011)
				R842_SysFreq_Info.LNA_VTL_H=0x5B;	          // LNA VTL/H=0.84/1.44    (R38=0x5B)					
				R842_SysFreq_Info.RF_VTL_H=0x38;              // RF VTL/H=0.64/1.14     (R39=0x38)
				R842_SysFreq_Info.NRB_TOP=10;                 // Nrb TOP=10             (R40[7:4]=4'b0101)				
				//R842_SysFreq_Info.MIXER_VTH=0x09;             // MIXER VTH=1.24         (R41[3:0]=0x09)
				//R842_SysFreq_Info.MIXER_VTL=0x03;             // MIXER VTL=0.64         (R43[3:0]=0x03)
				//R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;      // Mixer Gain Limit=8  				

#if(R842_MTK_ATV_TEST==TRUE)
				//MTK test
				if((RF_freq<190000) && (RF_freq>=180000)) 
				{
					R842_SysFreq_Info.LNA_VTL_H=0x6C;	      //LNA VTL/H=0.94/1.54
					R842_SysFreq_Info.NRB_TOP=10;             //Nrb TOP=10
					R842_SysFreq_Info.MIXER_TOP=14;           //MIXER TOP=14          
					//R842_SysFreq_Info.MIXER_VTH=0x0B;         //MIXER VTH=1.44          
					//R842_SysFreq_Info.MIXER_VTL=0x05;         //MIXER VTL=0.84   
					R842_SysFreq_Info.MIXER_VTH=0x0A;         //MIXER VTH=1.34          
					R842_SysFreq_Info.MIXER_VTL=0x04;         //MIXER VTL=0.74   
				}
#endif				
			}
			else if(R842_DetectTfType==R842_UL_USING_BEAD)  //Bead
			{
				if(RF_freq<150000)
				{
					R842_SysFreq_Info.LNA_TOP=5;              // LNA TOP=5              (R37[3:0]=4'b1010)
					R842_SysFreq_Info.LNA_VTL_H=0x4A;	      // LNA VTL/H=0.74/1.34    (R38=0x4A)		
					R842_SysFreq_Info.RF_TOP=1;               // RF TOP=1               (R37[6:4]=3'b110)
					R842_SysFreq_Info.RF_VTL_H=0x38;          // RF VTL/H=0.64/1.14     (R39=0x38)
					R842_SysFreq_Info.NRB_TOP=12;             // Nrb TOP=12             (R40[7:4]=4'b0011)
					R842_SysFreq_Info.MIXER_TOP=7;            // MIXER TOP=7            (R40[3:0]=4'b1000)
					R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24         (R41[3:0]=0x09)
					R842_SysFreq_Info.MIXER_VTL=0x03;         // MIXER VTL=0.64         (R43[3:0]=0x03)
					//R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8   
					R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  // Sharp
					R842_SysFreq_Info.Q_CTRL=0;               // 1.5k off                          
					R842_SysFreq_Info.HYS_MIXTOP=3;           // top<not change>         (R30[3:2]=2'b11)
					R842_SysFreq_Info.ENB_ATT=3;              // normal						
				}
				else  //>150M
				{
					R842_SysFreq_Info.LNA_TOP=4;              // LNA TOP=4              (R37[3:0]=4'b1011)
					R842_SysFreq_Info.LNA_VTL_H=0x5B;	      // LNA VTL/H=0.84/1.44    (R38=0x5B)		
					R842_SysFreq_Info.RF_TOP=2;               // RF TOP=2               (R37[6:4]=3'b101)
					R842_SysFreq_Info.RF_VTL_H=0x38;          // RF VTL/H=0.64/1.14     (R39=0x38)
					R842_SysFreq_Info.NRB_TOP=10;             // Nrb TOP=10                     
					R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24         (R41[3:0]=0x09)
					R842_SysFreq_Info.MIXER_VTL=0x03;         // MIXER VTL=0.64         (R43[3:0]=0x03)
					//R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
					R842_SysFreq_Info.Q_CTRL=1;               //1.5k on   
					R842_SysFreq_Info.MIXER_TOP=15;           //MIXER TOP=15      
					R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>
					R842_SysFreq_Info.ENB_ATT=3;              //normal      												
				}			
			}
			else //390n
			{
				if(RF_freq<180000)
				{
					R842_SysFreq_Info.LNA_TOP=5;              // LNA TOP=5              (R37[3:0]=4'b1010)
					R842_SysFreq_Info.LNA_VTL_H=0x4A;	      // LNA VTL/H=0.74/1.34    (R38=0x4A)		
					R842_SysFreq_Info.RF_TOP=1;               // RF TOP=1               (R37[6:4]=3'b110)
					R842_SysFreq_Info.RF_VTL_H=0x38;          // RF VTL/H=0.64/1.14     (R39=0x38)
					R842_SysFreq_Info.NRB_TOP=12;             // Nrb TOP=12             (R40[7:4]=4'b0011)
					R842_SysFreq_Info.MIXER_TOP=7;            // MIXER TOP=7            (R40[3:0]=4'b1000)
					R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24         (R41[3:0]=0x09)
					R842_SysFreq_Info.MIXER_VTL=0x03;         // MIXER VTL=0.64         (R43[3:0]=0x03)
					//R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8   
					R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  // Sharp
					R842_SysFreq_Info.Q_CTRL=1;               // 1.5k on
					R842_SysFreq_Info.HYS_MIXTOP=3;           // top<not change>         (R30[3:2]=2'b11)
					R842_SysFreq_Info.ENB_ATT=3;              // normal						
				}
				else  //>180M
				{
					R842_SysFreq_Info.LNA_TOP=4;              // LNA TOP=4              (R37[3:0]=4'b1011)
					R842_SysFreq_Info.LNA_VTL_H=0x5B;	      // LNA VTL/H=0.84/1.44    (R38=0x5B)		
					R842_SysFreq_Info.RF_TOP=2;               // RF TOP=2               (R37[6:4]=3'b101)
					R842_SysFreq_Info.RF_VTL_H=0x38;          // RF VTL/H=0.64/1.14     (R39=0x38)
					R842_SysFreq_Info.NRB_TOP=10;             // Nrb TOP=10                     
					R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24         (R41[3:0]=0x09)
					R842_SysFreq_Info.MIXER_VTL=0x03;         // MIXER VTL=0.64         (R43[3:0]=0x03)
					//R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
					R842_SysFreq_Info.Q_CTRL=1;               //1.5k on   
					R842_SysFreq_Info.MIXER_TOP=7;            //MIXER TOP=7
					R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change> 
					R842_SysFreq_Info.ENB_ATT=3;              //normal	       									
				}
			}
		}  //end low band
		else if((RF_freq>=R842_LNA_MID_LOW[R842_SetTfType])&&(RF_freq<R842_LNA_HIGH_MID[R842_SetTfType]))  //Mid band
		{
			if(R842_DetectMidTfType==R842_MID_USING_27NH) //Mid=27nH
			{
				if(RF_freq<410000)  //<410M				
				{
					R842_SysFreq_Info.ENB_ATT=2;        // dis 0~4								
					R842_SysFreq_Info.LNA_VTL_H=0x4A;   // LNA VTL/H=0.74/1.34    (R38=0x4A)		
				}
				else  //>410M				
				{
					R842_SysFreq_Info.ENB_ATT=0;        // dis 0~6
					R842_SysFreq_Info.LNA_VTL_H=0x4A;   // LNA VTL/H=0.74/1.34    (R38=0x4A)		
				}
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;     //Auto
			} 
			else if((R842_DetectMidTfType==R842_MID_USING_39NH) && (R842_DetectTfType==R842_UL_USING_270NH)) //Mid=39n (270n/39n)
			{
				if(RF_freq<250000)  //<250M		
				{
#if(R842_FOR_SEC==TRUE)
					R842_SysFreq_Info.ENB_ATT=3;				// normal
					R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;    // Plain
#else
					R842_SysFreq_Info.ENB_ATT=2;				// dis 0~4
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;     // Auto
#endif
					R842_SysFreq_Info.LNA_VTL_H=0x5B;		    // LNA VTL/H=0.84/1.44    (R38=0x5B)		
				}
				else  //>250M
				{
					R842_SysFreq_Info.ENB_ATT=2;				// dis 0~4
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;     //Auto
					R842_SysFreq_Info.LNA_VTL_H=0x4A;			// LNA VTL/H=0.74/1.34    (R38=0x4A)				
				}			
			}
			else if((R842_DetectMidTfType==R842_MID_USING_68NH) && (R842_DetectTfType==R842_UL_USING_BEAD)) //Mid=68 (bead/68n)
			{
					R842_SysFreq_Info.ENB_ATT=2;        // dis 0~4
					R842_SysFreq_Info.LNA_VTL_H=0x5B;   // LNA VTL/H=0.84/1.44    (R38=0x5B)		
					R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;     //Auto
			}
			else //to give initial value (Mid=27n)
			{
				if(RF_freq<410000)  //<410M				
				{
					R842_SysFreq_Info.ENB_ATT=2;        // dis 0~4								
					R842_SysFreq_Info.LNA_VTL_H=0x4A;   // LNA VTL/H=0.74/1.34    (R38=0x4A)		
				}
				else  //>410M				
				{
					R842_SysFreq_Info.ENB_ATT=0;        // dis 0~6
					R842_SysFreq_Info.LNA_VTL_H=0x4A;   // LNA VTL/H=0.74/1.34    (R38=0x4A)		
				}
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;     //Auto
			}
			
			R842_SysFreq_Info.LNA_TOP=3;                // LNA TOP=3              (R37[3:0]=4'b1100)
			R842_SysFreq_Info.RF_TOP=2;                 // RF TOP=2               (R37[6:4]=3'b101)
			R842_SysFreq_Info.RF_VTL_H=0x38;            // RF VTL/H=0.64/1.14     (R39=0x38)
			R842_SysFreq_Info.NRB_TOP=12;               // Nrb TOP=12             (R40[7:4]=4'b0011)
			R842_SysFreq_Info.MIXER_TOP=15;             // MIXER TOP=15             
			R842_SysFreq_Info.MIXER_VTH=0x09;           // MIXER VTH=1.24         (R41[3:0]=0x09)
			R842_SysFreq_Info.MIXER_VTL=0x03;           // MIXER VTL=0.64         (R43[3:0]=0x03)
//			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;    // Mixer Gain Limit=8
//			R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;     //Auto
			R842_SysFreq_Info.Q_CTRL=1;                 //1.5k on
			R842_SysFreq_Info.HYS_MIXTOP=0;             //top<!32>  
		
		}  //end mid band
		else  //high band
		{

			if(RF_freq<700000)  //<700M		
			{
				R842_SysFreq_Info.LNA_TOP=2;             //LNA TOP=2
				R842_SysFreq_Info.LNA_VTL_H=0x4A;	     //LNA VTL/H=0.74/1.34      (R38=0x4A)	
				R842_SysFreq_Info.RF_VTL_H=0x38;         //RF VTL/H=0.64/1.14       (R39=0x38)
				R842_SysFreq_Info.RF_TOP=2;              //RF TOP=2 
				R842_SysFreq_Info.NRB_TOP=12;            //Nrb TOP=12               (R40[7:4]=4'b0011)
				R842_SysFreq_Info.ENB_ATT=0;             //dis 0~6
				R842_SysFreq_Info.MIXER_VTH=0x09;        //MIXER VTH=1.24           (R41[3:0]=0x09)
				R842_SysFreq_Info.MIXER_VTL=0x03;        //MIXER VTL=0.64           (R43[3:0]=0x03)
			}
			else //>700M
			{
				R842_SysFreq_Info.LNA_TOP=1;             //LNA TOP=1
				R842_SysFreq_Info.LNA_VTL_H=0x4A;	     //LNA VTL/H=0.74/1.34      (R38=0x4A)	
				R842_SysFreq_Info.RF_VTL_H=0x5B;         //RF VTL/H=0.84/1.44       (R39=0x5B)			
				R842_SysFreq_Info.RF_TOP=4;              //RF TOP=4   
				R842_SysFreq_Info.NRB_TOP=12;            //Nrb TOP=12  
				R842_SysFreq_Info.ENB_ATT=3;             //normal			
				R842_SysFreq_Info.MIXER_VTH=0x09;        //MIXER VTH=1.24           (R41[3:0]=0x09)
				R842_SysFreq_Info.MIXER_VTL=0x03;        //MIXER VTL=0.64           (R43[3:0]=0x03)
			}
#if(R842_MTK_ATV_TEST==TRUE)
			//MTK test
			if((RF_freq<710000) && (RF_freq>=690000)) 
			{
				R842_SysFreq_Info.LNA_TOP=3;             //LNA TOP=3
				R842_SysFreq_Info.LNA_VTL_H=0x6C;	     //LNA VTL/H=0.94/1.54    	
				R842_SysFreq_Info.RF_VTL_H=0x5B;         //RF VTL/H=0.84/1.44
				R842_SysFreq_Info.RF_TOP=2;              //RF TOP=2
				R842_SysFreq_Info.NRB_TOP=10;            //Nrb TOP=10
				R842_SysFreq_Info.ENB_ATT=3;             //normal	
				R842_SysFreq_Info.MIXER_VTH=0x0B;        //MIXER VTH=1.44          
				R842_SysFreq_Info.MIXER_VTL=0x05;        //MIXER VTL=0.84    
				//R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00;  // Mixer Gain Limit=6
			}
#endif
			
			//R842_SysFreq_Info.LNA_VTL_H=0x4A;	      //LNA VTL/H=0.74/1.34      (R38=0x4A)		
			//R842_SysFreq_Info.NRB_TOP=12;             //Nrb TOP=12               (R40[7:4]=4'b0011)
			R842_SysFreq_Info.MIXER_TOP=15;           //MIXER TOP=15             
			//R842_SysFreq_Info.MIXER_VTH=0x09;         //MIXER VTH=1.24           (R41[3:0]=0x09)
			//R842_SysFreq_Info.MIXER_VTL=0x03;         //MIXER VTL=0.64           (R43[3:0]=0x03)
			R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
			R842_SysFreq_Info.Q_CTRL=0;               //1.5k off
			R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>     
		}

		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;     // RF Gain Limit=15           (R45[7:6]=2'b11)
		R842_SysFreq_Info.NRB_BW_HPF=0x00;        // Nrb HPF BW=lowest          (R42[3:2]=2'b00)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low             (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=8;           // Filter TOP=8               (R42[7:4]=4'b0111)
		R842_SysFreq_Info.FILTER_VTH=0x90;        // Filter VTH=1.24            (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x30;        // Filter VTL=0.64            (R43[7:4]=3)
//		R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x01; //0.3u/0.9u                   (R44[4:0]=4'b0001)
		R842_SysFreq_Info.BB_DET_MODE=0x00;       //Peak                        (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x04;     //top+6dB                     (R45[3:2]=2'b01)   	
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;       //+4                          (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=0;             //normal  
		R842_SysFreq_Info.FB1_RES=0;              //2K       
		R842_SysFreq_Info.MIXER_AMP_LPF=1;        //1 
		R842_SysFreq_Info.DET_BW_LPF=1;           //enhance amp		
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00;  // Mixer Gain Limit=6
/*
#if(R842_FOR_SEC==TRUE)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8
#else
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00;  // Mixer Gain Limit=6
#endif
*/
		break;

	case R842_DVB_T_6M:
	case R842_DVB_T_7M:
	case R842_DVB_T_8M:
	case R842_DVB_T_6M_IF_5M:
	case R842_DVB_T_7M_IF_5M:
	case R842_DVB_T_8M_IF_5M:
	case R842_DVB_T2_6M:
	case R842_DVB_T2_7M: 
	case R842_DVB_T2_8M:
	case R842_DVB_T2_1_7M:
	case R842_DVB_T2_10M:
    case R842_DVB_T2_6M_IF_5M:
	case R842_DVB_T2_7M_IF_5M:
	case R842_DVB_T2_8M_IF_5M:
	case R842_DVB_T2_1_7M_IF_5M:

		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band (270n)
		{
			if(RF_freq<65000)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;       //Auto
				R842_SysFreq_Info.Q_CTRL=0;                   //1.5k off               
				R842_SysFreq_Info.ENB_ATT=2;                  //dis 0~4
				R842_SysFreq_Info.LNA_VTL_H=0x6B;             //LNA VTL/H=0.94/1.44      (R38=0x6B)
				R842_SysFreq_Info.RF_TOP=3;                   //RF TOP=3
				R842_SysFreq_Info.RF_VTL_H=0x38;              //RF VTL/H=0.64/1.14      
				R842_SysFreq_Info.NRB_TOP=6;                  //Nrb TOP=6
				R842_SysFreq_Info.MIXER_TOP=15;               //MIXER TOP=15             (R40[3:0]=4'b0000)
				R842_SysFreq_Info.HYS_MIXTOP=0;               //top<!32>                 (R30[3:2]=2'b00)
			}
			else if((RF_freq>=65000) && (RF_freq<80000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;      //Plain
				R842_SysFreq_Info.Q_CTRL=1;                   //1.5k on                 (R14[7]=1)
				R842_SysFreq_Info.ENB_ATT=3;                  //normal
				R842_SysFreq_Info.LNA_VTL_H=0x6B;             //LNA VTL/H=0.94/1.44     (R38=0x6B)
				R842_SysFreq_Info.RF_TOP=3;                   //RF TOP=3
				R842_SysFreq_Info.RF_VTL_H=0x38;              //RF VTL/H=0.64/1.14 
				R842_SysFreq_Info.NRB_TOP=6;                  //Nrb TOP=6 
				R842_SysFreq_Info.MIXER_TOP=12;               //MIXER TOP=12           
				R842_SysFreq_Info.HYS_MIXTOP=3;               //top<not change>             
			}
			else if((RF_freq>=80000) && (RF_freq<210000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;      //plain
				R842_SysFreq_Info.Q_CTRL=1;                   //1.5k on                 (R14[7]=1)
				R842_SysFreq_Info.ENB_ATT=3;                  //normal
				R842_SysFreq_Info.LNA_VTL_H=0x5B;             //LNA VTL/H=0.84/1.44      
				R842_SysFreq_Info.RF_TOP=3;                   //RF TOP=3				
				R842_SysFreq_Info.RF_VTL_H=0x38;              //RF VTL/H=0.64/1.14 
				R842_SysFreq_Info.NRB_TOP=6;                  //Nrb TOP=6 
				R842_SysFreq_Info.MIXER_TOP=12;               //MIXER TOP=12
				R842_SysFreq_Info.HYS_MIXTOP=3;               //top<not change>             
			}
			else //>210M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;       //Auto
				R842_SysFreq_Info.Q_CTRL=0;                   //1.5k off               
				R842_SysFreq_Info.ENB_ATT=2;                  //dis 0~4
				R842_SysFreq_Info.LNA_VTL_H=0x6B;             //LNA VTL/H=0.94/1.44      (R38=0x6B)
				R842_SysFreq_Info.RF_TOP=3;                   //RF TOP=3
				R842_SysFreq_Info.RF_VTL_H=0x38;              //RF VTL/H=0.64/1.14      
				R842_SysFreq_Info.NRB_TOP=6;                  //Nrb TOP=6
				R842_SysFreq_Info.MIXER_TOP=15;               //MIXER TOP=15             (R40[3:0]=4'b0000)
				R842_SysFreq_Info.HYS_MIXTOP=0;               //top<!32>                 (R30[3:2]=2'b00)
			}
			//R842_SysFreq_Info.MIXER_VTH=0x0B;         // MIXER VTH=1.44           
			//R842_SysFreq_Info.MIXER_VTL=0x06;         // MIXER VTL=0.94
			R842_SysFreq_Info.MIXER_VTH=0x0A;         // MIXER VTH=1.34           
			R842_SysFreq_Info.MIXER_VTL=0x05;         // MIXER VTL=0.84
			R842_SysFreq_Info.IMG_NRB_ADDER=0x08;     // top+9dB                   (R45[3:2]=2'b10)
			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8				
			R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1	
			//R842_SysFreq_Info.NRB_BW_LPF=0x03;        // Nrb LPF BW=lowest        (R42[1:0]=2'b11)
			R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low           (R42[1:0]=2'b10)

		}
		else if(RF_freq>=R842_LNA_MID_LOW[R842_SetTfType] && RF_freq<R842_LNA_HIGH_MID[R842_SetTfType])  //mid band (236~508)
		{
			R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
			R842_SysFreq_Info.Q_CTRL=1;               //1.5k on                (R14[7]=1)
			R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
			R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34    (R38=0x5A)
			R842_SysFreq_Info.RF_TOP=3;               //RF TOP=3
			R842_SysFreq_Info.RF_VTL_H=0x38;          //RF VTL/H=0.64/1.14   
			R842_SysFreq_Info.NRB_TOP=6;              //Nrb TOP=6
			R842_SysFreq_Info.MIXER_TOP=15;           //MIXER TOP=15           (R40[3:0]=4'b0000)
			R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32> 

			//R842_SysFreq_Info.MIXER_VTH=0x0B;         // MIXER VTH=1.44           
			//R842_SysFreq_Info.MIXER_VTL=0x06;         // MIXER VTL=0.94
			R842_SysFreq_Info.MIXER_VTH=0x0A;         // MIXER VTH=1.34           
			R842_SysFreq_Info.MIXER_VTL=0x05;         // MIXER VTL=0.84
			R842_SysFreq_Info.IMG_NRB_ADDER=0x08;     // top+9dB                   (R45[3:2]=2'b10)
			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8		
			R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1
			//R842_SysFreq_Info.NRB_BW_LPF=0x03;        // Nrb LPF BW=lowest        (R42[1:0]=2'b11)
			R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low           (R42[1:0]=2'b10)

		}
		else  //high band (>508M)
		{
			if(RF_freq>=782000 && RF_freq<790000)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  //sharp
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off                  (R14[7]=1)
				R842_SysFreq_Info.ENB_ATT=3;              //normal
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34       (R38=0x5A)
				R842_SysFreq_Info.RF_TOP=4;               //RF TOP=4
				R842_SysFreq_Info.RF_VTL_H=0x5A;          //RF VTL/H=0.84/1.34 
				R842_SysFreq_Info.NRB_TOP=4;             // Nrb TOP=4 
				R842_SysFreq_Info.MIXER_TOP=9; 
				R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change>    

				R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low           (R42[1:0]=2'b10)
				R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24           
				R842_SysFreq_Info.MIXER_VTL=0x04;         // MIXER VTL=0.74
				R842_SysFreq_Info.MIXER_AMP_LPF=4;        // 4
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x40;  // Mixer Gain Limit=10
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;     // top+9dB 							
			}
			else
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  //sharp
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off                  (R14[7]=1)
				R842_SysFreq_Info.ENB_ATT=3;              //normal				
				R842_SysFreq_Info.LNA_VTL_H=0x6B;         //LNA VTL/H=0.94/1.44       (R38=0x6B)
				R842_SysFreq_Info.RF_TOP=3;               //RF TOP=3
				R842_SysFreq_Info.RF_VTL_H=0x38;          //RF VTL/H=0.64/1.14 
				R842_SysFreq_Info.NRB_TOP=6;              //Nrb TOP=6 
				R842_SysFreq_Info.MIXER_TOP=15; 
				R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change>    

//				R842_SysFreq_Info.NRB_BW_LPF=0x03;        // Nrb LPF BW=lowest        (R42[1:0]=2'b11)
				R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low           (R42[1:0]=2'b10)
				//R842_SysFreq_Info.MIXER_VTH=0x0B;         // MIXER VTH=1.44           
				//R842_SysFreq_Info.MIXER_VTL=0x06;         // MIXER VTL=0.94
				R842_SysFreq_Info.MIXER_VTH=0x0A;         // MIXER VTH=1.34 
				R842_SysFreq_Info.MIXER_VTL=0x05;         // MIXER VTL=0.84
				R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00;  // Mixer Gain Limit=6	
				R842_SysFreq_Info.IMG_NRB_ADDER=0x00;     // top+0dB                   (R45[3:2]=2'b00)
			}					
		
		}  //end of high band

		R842_SysFreq_Info.LNA_TOP=4;              // LNA TOP=4                (R37[3:0]=4'b1011)
//		R842_SysFreq_Info.RF_TOP=3;               // RF TOP=3
//		R842_SysFreq_Info.RF_VTL_H=0x5A;          // RF VTL/H=0.84/1.34       (R39=0x5A)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;     // RF Gain Limit=15         (R45[7:6]=2'b11)	
		R842_SysFreq_Info.NRB_BW_HPF=0x00;        // Nrb HPF BW=lowest        (R42[3:2]=2'b00)
//		R842_SysFreq_Info.NRB_BW_LPF=0x03;        // Nrb LPF BW=lowest        (R42[1:0]=2'b11)
		R842_SysFreq_Info.FILTER_TOP=5;           // Filter TOP=5             (R42[7:4]=4'b1010)
		R842_SysFreq_Info.FILTER_VTH=0x90;        // Filter VTH=1.24          (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;        // Filter VTL=0.74          (R43[7:4]=4)
		R842_SysFreq_Info.BB_DET_MODE=0x00;       // Peak                     (R47[7]=0) 
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;       // +4                       (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=1;             // +1.5    
		R842_SysFreq_Info.FB1_RES=1;              // 8K        
//		R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1	
		R842_SysFreq_Info.DET_BW_LPF=1;           // enhance amp

		break;

    case R842_DVB_C_8M:
	case R842_DVB_C_6M:	
	case R842_DVB_C_8M_IF_5M:
	case R842_DVB_C_6M_IF_5M:	

		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band
		{
			if(R842_DetectTfType==R842_UL_USING_270NH) //low=270n
			{
				if(RF_freq<180000)
				{
					R842_SysFreq_Info.ENB_ATT=0;           //dis 0~6
					R842_SysFreq_Info.Q_CTRL=1;            //1.5k on
					R842_SysFreq_Info.LNA_VTL_H=0x5B;	   //LNA VTL/H=0.84/1.44
				}
				else
				{
					R842_SysFreq_Info.ENB_ATT=2;           //dis 0~4
					R842_SysFreq_Info.Q_CTRL=0;            //1.5k off       
					R842_SysFreq_Info.LNA_VTL_H=0x6B;	   //LNA VTL/H=0.94/1.44 
				}
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;   //plain
				R842_SysFreq_Info.LNA_TOP=4;               //LNA TOP=4				
			}
			else  //low=bead, 390n
			{
				R842_SysFreq_Info.ENB_ATT=0;               //dis 0~6
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;   //plain
				R842_SysFreq_Info.LNA_TOP=4;               //LNA TOP=4
				R842_SysFreq_Info.LNA_VTL_H=0x5B;	       //LNA VTL/H=0.84/1.44 
				R842_SysFreq_Info.Q_CTRL=1;                //1.5k on     
			}
		}
		else if(RF_freq>=R842_LNA_MID_LOW[R842_SetTfType] && RF_freq<R842_LNA_HIGH_MID[R842_SetTfType])  //mid band
		{
			R842_SysFreq_Info.ENB_ATT=0;                   //dis 0~6
			R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;       //plain
			R842_SysFreq_Info.LNA_TOP=4;                   //LNA TOP=4
			R842_SysFreq_Info.LNA_VTL_H=0x5B;	           //LNA VTL/H=0.84/1.44 
			R842_SysFreq_Info.Q_CTRL=1;                    //1.5k on        
		}
		else  //high
		{
			R842_SysFreq_Info.ENB_ATT=0;                   //dis 0~6
			R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;       //sharp
			R842_SysFreq_Info.LNA_TOP=3;                   //LNA TOP=3
			R842_SysFreq_Info.LNA_VTL_H=0x5A;	           //LNA VTL/H=0.84/1.34 
			R842_SysFreq_Info.Q_CTRL=0;                    //1.5k off                              (R14[7]=0)
		}		
		R842_SysFreq_Info.RF_TOP=2;              // RF TOP=2              (R37[6:4]=3'b101)
		R842_SysFreq_Info.RF_VTL_H=0x49;         // RF VTL/H=0.74/1.24    (R39=0x49)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;    // RF Gain Limit=15      (R45[7:6]=2'b11)
		R842_SysFreq_Info.MIXER_TOP=15;          // MIXER TOP=15          (R40[3:0]=4'b0000)
		R842_SysFreq_Info.HYS_MIXTOP=3;          // top<not change>       (R30[3:2]=2'b00)		
		R842_SysFreq_Info.MIXER_VTH=0x09;        // MIXER VTH=1.24        (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;        // MIXER VTL=0.74        (R43[3:0]=4)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20; // Mixer Gain Limit=8    (R20[6:5]=2'b01)
		R842_SysFreq_Info.NRB_TOP=12;            // Nrb TOP=12            (R40[7:4]=4'b0011)
		R842_SysFreq_Info.NRB_BW_HPF=0x00;       // Nrb HPF BW=lowest     (R42[3:2]=2'b00)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;       // Nrb LPF BW=low        (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=8;          // Filter TOP=8          (R42[7:4]=4'b0111)
		R842_SysFreq_Info.FILTER_VTH=0x90;       // Filter VTH=1.24       (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;       // Filter VTL=0.74       (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05;// 0.3u/1.5u             (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;      // Peak                  (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x04;    // top+6dB               (R45[3:2]=2'b01)   
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;      // +4                    (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=1;            // +1.5    
		R842_SysFreq_Info.FB1_RES=1;             // 8K        
#if(R842_ALL_IMR_NOR==TRUE)
		R842_SysFreq_Info.MIXER_AMP_LPF=1;       // 1
#else
		R842_SysFreq_Info.MIXER_AMP_LPF=4;       // 4		
#endif
		R842_SysFreq_Info.DET_BW_LPF=0;          // normal
		break;

	case R842_J83B:
	case R842_J83B_IF_5M:
		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band (270n)
		{
			if(RF_freq<65000)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34 
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off
				R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
				R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>   
			}
			else if((RF_freq>=65000) && (RF_freq<80000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;  //Plain
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34 
				R842_SysFreq_Info.Q_CTRL=1;               //1.5k on      
				R842_SysFreq_Info.ENB_ATT=3;              //normal
				R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change> 			
			}
			else if((RF_freq>=80000) && (RF_freq<210000))
			{
				R842_SysFreq_Info.LNA_VTL_H=0x4A;         //LNA VTL/H=0.74/1.34 
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;  //Plain
				R842_SysFreq_Info.Q_CTRL=1;               //1.5k on
				R842_SysFreq_Info.ENB_ATT=3;              //normal
				R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change> 			
			}
			else //>210M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34 
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off
				R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
				R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>  
			}
		}
		else if(RF_freq>=R842_LNA_MID_LOW[R842_SetTfType] && RF_freq<R842_LNA_HIGH_MID[R842_SetTfType])  //mid band (39n)
		{
			if((RF_freq>=360000) && (RF_freq<=480000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34 
				R842_SysFreq_Info.Q_CTRL=1;               //1.5k on      
				R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
				R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>   
			}
			else // <360M, >480M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;   //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34 
				R842_SysFreq_Info.Q_CTRL=1;               //1.5k on      
				R842_SysFreq_Info.ENB_ATT=2;              //dis 0~4
				R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>   			
			}
		}
		else  //high band
		{
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  //Sharp
				R842_SysFreq_Info.LNA_VTL_H=0x5A;         //LNA VTL/H=0.84/1.34 
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off      
				R842_SysFreq_Info.ENB_ATT=3;              //normal
				R842_SysFreq_Info.HYS_MIXTOP=0;           //top<!32>   			
		}

		R842_SysFreq_Info.LNA_TOP=3;              // LNA TOP=3
//		R842_SysFreq_Info.LNA_VTL_H=0x5A;         // LNA VTL/H=0.84/1.34    (R38=0x5A)
		R842_SysFreq_Info.RF_TOP=2;               // RF TOP=2               (R37[6:4]=3'b101)
		R842_SysFreq_Info.RF_VTL_H=0x49;          // RF VTL/H=0.74/1.24     (R39=0x49)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;     // RF Gain Limit=15       (R45[7:6]=2'b11)
		R842_SysFreq_Info.MIXER_TOP=15;           // MIXER TOP=15             
		R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24         (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;         // MIXER VTL=0.74         (R43[3:0]=4)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8     (R20[6:5]=2'b01)
		R842_SysFreq_Info.NRB_TOP=12;             // Nrb TOP=12             (R40[7:4]=4'b0011)
		R842_SysFreq_Info.NRB_BW_HPF=0x00;        // Nrb HPF BW=lowest      (R42[3:2]=2'b00)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low         (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=8;           // Filter TOP=8           (R42[7:4]=4'b0111)
		R842_SysFreq_Info.FILTER_VTH=0x90;        // Filter VTH=1.24        (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;        // Filter VTL=0.74        (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05; // 0.3u/1.5u              (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;       // Peak                   (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x04;     // top+6dB                (R45[3:2]=2'b01)   
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;       // +4                     (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=0;             // normal
		R842_SysFreq_Info.FB1_RES=0;              // 2K        
		R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1 
		R842_SysFreq_Info.DET_BW_LPF=0;           // normal
		break;

	case R842_ISDB_T_4063:	
	case R842_ISDB_T_4570:	
	case R842_ISDB_T_IF_5M:	
		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band (270n)
		{
			if(RF_freq<65000)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;       //Auto
				R842_SysFreq_Info.Q_CTRL=0;                   //1.5k off
				R842_SysFreq_Info.ENB_ATT=2;                  //dis 0~4
				R842_SysFreq_Info.MIXER_TOP=15;               //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;               //top<!32>   
			}
			else if((RF_freq>=65000) && (RF_freq<80000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;      //Plain
				R842_SysFreq_Info.Q_CTRL=1;                   //1.5k on      
				R842_SysFreq_Info.ENB_ATT=3;                  //normal
				R842_SysFreq_Info.MIXER_TOP=9;                //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;               //top<not change>   		
			}
			else if((RF_freq>=80000) && (RF_freq<210000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;      //plain
				R842_SysFreq_Info.Q_CTRL=1;                   //1.5k on
				R842_SysFreq_Info.ENB_ATT=3;                  //normal
				R842_SysFreq_Info.MIXER_TOP=9;                //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;               //top<not change>   		
			}
			else //>210M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;       //Auto
				R842_SysFreq_Info.Q_CTRL=0;                   //1.5k off
				R842_SysFreq_Info.ENB_ATT=2;                  //dis 0~4
				R842_SysFreq_Info.MIXER_TOP=15;               //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;               //top<!32> 
			}
		}
		else if(RF_freq>=R842_LNA_MID_LOW[R842_SetTfType] && RF_freq<R842_LNA_HIGH_MID[R842_SetTfType])  //mid band (39n)
		{
			if((RF_freq>=360000) && (RF_freq<=480000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;       //Auto
				R842_SysFreq_Info.Q_CTRL=1;                   //1.5k on      
				R842_SysFreq_Info.ENB_ATT=2;                  //dis 0~4
				R842_SysFreq_Info.MIXER_TOP=15;               //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;               //top<!32>   		  
			}
			else // <360M, >480M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;       //Auto
				R842_SysFreq_Info.Q_CTRL=1;                   //1.5k on      
				R842_SysFreq_Info.ENB_ATT=2;                  //dis 0~4
				R842_SysFreq_Info.MIXER_TOP=15;               //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;               //top<!32>   		 			
			}
		}
		else  //high band
		{
			if(RF_freq<620000)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;   //sharp
				R842_SysFreq_Info.Q_CTRL=0;                //1.5k off      
				R842_SysFreq_Info.ENB_ATT=3;               //normal
				R842_SysFreq_Info.MIXER_TOP=9;             //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;            //top<not change> 
			}
			else // >620M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;   //sharp
				R842_SysFreq_Info.Q_CTRL=0;                //1.5k off      
				R842_SysFreq_Info.ENB_ATT=3;               //normal
				R842_SysFreq_Info.MIXER_TOP=9;             //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;            //top<not change>   		   			
			}
		}
		R842_SysFreq_Info.LNA_TOP=5;              // LNA TOP=5                (R37[3:0]=4'b1010)
		R842_SysFreq_Info.LNA_VTL_H=0x4A;	      // LNA VTL/H=0.74/1.34      (R38=0x4A)		
		R842_SysFreq_Info.RF_TOP=4;               // RF TOP=4                 (R37[6:4]=3'b011)
		R842_SysFreq_Info.RF_VTL_H=0x5A;          // RF VTL/H=0.84/1.34       (R39=0x5A)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;     // RF Gain Limit=15         (R45[7:6]=2'b11)
		R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24           (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;         // MIXER VTL=0.74           (R43[3:0]=4)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;  // Mixer Gain Limit=8 
		R842_SysFreq_Info.NRB_TOP=6;              // Nrb TOP=6
		R842_SysFreq_Info.NRB_BW_HPF=0x00;        // Nrb HPF BW=lowest        (R42[3:2]=2'b00)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low           (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=5;           // Filter TOP=5             (R42[7:4]=4'b1010)
		R842_SysFreq_Info.FILTER_VTH=0x90;        // Filter VTH=1.24          (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;        // Filter VTL=0.74          (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05; //0.3u/1.5u                 (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;       //Peak                      (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x08;     //top+9dB                   (R45[3:2]=2'b10)   
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;       //+4                        (R24[6]=1)
		R842_SysFreq_Info.DET_BW_LPF=1;           //enhance amp
		R842_SysFreq_Info.FB1_RES=1;              //8K   
		R842_SysFreq_Info.HPF_COMP=1;             //+1.5          
		R842_SysFreq_Info.MIXER_AMP_LPF=4;        //4

		//LTE band
		if((RF_freq>=692000) && (RF_freq<=700000))
		{
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;   //sharp
				R842_SysFreq_Info.Q_CTRL=0;                //1.5k off      
				R842_SysFreq_Info.ENB_ATT=3;               //normal
				R842_SysFreq_Info.NRB_TOP=5;               //Nrb TOP=5
				R842_SysFreq_Info.MIXER_TOP=9;             //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;            //top<not change>   		

				R842_SysFreq_Info.LNA_VTL_H=0x6B;	       //LNA VTL/H=0.94/1.44     	
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60;   //Mixer Gain Limit=12
				R842_SysFreq_Info.MIXER_AMP_LPF=7;         //7
				R842_SysFreq_Info.HPF_COMP=2;              //+3.0 
		}

		break;

	case R842_DTMB_8M_4570:
	case R842_DTMB_6M_4500:
	case R842_DTMB_8M_IF_5M:
	case R842_DTMB_6M_IF_5M:
		
		if(RF_freq<100000)  //<100M
		{
		R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;  
		R842_SysFreq_Info.Q_CTRL=0;              //1.5k off              (R14[7]=0)
		R842_SysFreq_Info.NRB_TOP=10;            //Nrb TOP=10                     
		R842_SysFreq_Info.NRB_BW_HPF=0x0C;       //Nrb HPF BW=highest    (R42[3:2]=2'b11)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00; //Mixer Gain Limit=6
		R842_SysFreq_Info.MIXER_TOP=9;           //9    
		R842_SysFreq_Info.HYS_MIXTOP=3;          //top<not change>        
		R842_SysFreq_Info.FILT3_GAIN_MAN=0;      //normal                (R24[6]=0)
		R842_SysFreq_Info.ENB_ATT=2;             //dis 0~4
		}
		else if((RF_freq>=100000) && (RF_freq<R842_LNA_MID_LOW[R842_SetTfType])) //100~ (Low/Mid)
		{
			if(R842_DetectTfType==R842_UL_USING_BEAD)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;  //Auto
				R842_SysFreq_Info.MIXER_TOP=15;          //MIXER TOP=15  
				R842_SysFreq_Info.HYS_MIXTOP=0;          //top<!32>  
				R842_SysFreq_Info.Q_CTRL=0;              //1.5k off  
				R842_SysFreq_Info.ENB_ATT=2;             //dis 0~4
			}
			//else if(R842_DetectTfType==R842_UL_USING_390NH)
			else  //390nH (should not have 270nH)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN; //plain
				R842_SysFreq_Info.MIXER_TOP=9;           //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;          //top<not change>  
				R842_SysFreq_Info.Q_CTRL=1;              //1.5k on  
				R842_SysFreq_Info.ENB_ATT=3;             //normal
			}	
			R842_SysFreq_Info.NRB_TOP=10;                //Nrb TOP=10                     
			R842_SysFreq_Info.NRB_BW_HPF=0x0C;           //Nrb HPF BW=highest     (R42[3:2]=2'b11)
			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;     //Mixer Gain Limit=8                  
			R842_SysFreq_Info.FILT3_GAIN_MAN=1;          //+4                      (R24[6]=1)		
	//		R842_SysFreq_Info.ENB_ATT=2;                 //dis 0~4
		}		
		else if((RF_freq>=R842_LNA_MID_LOW[R842_SetTfType]) && RF_freq<R842_LNA_HIGH_MID[R842_SetTfType]) //mid band (27n or 68n)
		{
			R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;     //Plain
			R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5 
			R842_SysFreq_Info.Q_CTRL=0;                  //1.5k off                (R14[7]=0)
			//R842_SysFreq_Info.NRB_TOP=6;               //Nrb TOP=6                     
			R842_SysFreq_Info.NRB_BW_HPF=0x0C;           //Nrb HPF BW=highest     (R42[3:2]=2'b11)
			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;     //Mixer Gain Limit=8   
			R842_SysFreq_Info.MIXER_TOP=9;               //MIXER TOP=9
			R842_SysFreq_Info.HYS_MIXTOP=3;              //top<not change>       
			R842_SysFreq_Info.FILT3_GAIN_MAN=1;          //+4    
			R842_SysFreq_Info.ENB_ATT=3;                 //normal		
		}
		else  //high band
		{
			R842_SysFreq_Info.ENB_ATT=3;                 //normal						
			R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;     //Sharp
			R842_SysFreq_Info.NRB_TOP=5;                 // Nrb TOP=5
			R842_SysFreq_Info.Q_CTRL=0;                 //1.5k off            (R14[7]=0)
			R842_SysFreq_Info.NRB_BW_HPF=0x08;          // Nrb HPF BW=high    (R42[3:2]=2'b10)
			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;    // Mixer Gain Limit=8   
			R842_SysFreq_Info.MIXER_TOP=9;              // MIXER TOP=9  
			R842_SysFreq_Info.HYS_MIXTOP=3;             //top<not change>              
			R842_SysFreq_Info.FILT3_GAIN_MAN=1;         //+4                  (R24[6]=1)
		}
		R842_SysFreq_Info.LNA_TOP=5;              // LNA TOP=5                (R37[3:0]=4'b1011)
		R842_SysFreq_Info.LNA_VTL_H=0x5B;	      // LNA VTL/H=0.84/1.44      (R38=0x4A)		
		R842_SysFreq_Info.RF_TOP=4;               // RF TOP=4                 (R37[6:4]=3'b011)
		R842_SysFreq_Info.RF_VTL_H=0x5A;          // RF VTL/H=0.84/1.34       (R39=0x5A)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;     // RF Gain Limit=15         (R45[7:6]=2'b11)            
		R842_SysFreq_Info.MIXER_VTH=0x09;         // MIXER VTH=1.24           (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;         // MIXER VTL=0.74           (R43[3:0]=4)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;        // Nrb LPF BW=low           (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=5;           // Filter TOP=5             (R42[7:4]=4'b1010)
		R842_SysFreq_Info.FILTER_VTH=0xA0;        // Filter VTH=1.34          (R41[7:4]=10)
		R842_SysFreq_Info.FILTER_VTL=0x40;        // Filter VTL=0.74          (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05; //0.3u/1.5u                 (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;       //Peak                      (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x00;     //top=original              (R45[3:2]=2'b00)   
		//R842_SysFreq_Info.Q_CTRL=0;               //1.5k off                  (R14[7]=0)
		R842_SysFreq_Info.HPF_COMP=0;             //normal
		R842_SysFreq_Info.FB1_RES=1;              //8K        
#if(R842_ALL_IMR_NOR==TRUE)
		R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1
#else
		R842_SysFreq_Info.MIXER_AMP_LPF=4;        // 4		
#endif		
		R842_SysFreq_Info.DET_BW_LPF=1;           //enhance amp
		break;

	case R842_ATSC:
	case R842_ATSC_IF_5M:

		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band (270n)
		{
			if(RF_freq<65000)
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;      //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	         //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.Q_CTRL=0;                  //1.5k off  
				R842_SysFreq_Info.ENB_ATT=2;                 //dis 0~4			
				R842_SysFreq_Info.LNA_TOP=4;                 //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5
				R842_SysFreq_Info.MIXER_TOP=15;	             //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;              //top<!32>   				        				                   
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;		 //top+9dB   
			}
			else if((RF_freq>=65000) && (RF_freq<80000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;     //Plain
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	         //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.Q_CTRL=1;                  //1.5k on  
				R842_SysFreq_Info.ENB_ATT=3;                 //normal
				R842_SysFreq_Info.LNA_TOP=4;                 //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5 
				R842_SysFreq_Info.MIXER_TOP=9;               //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;              //top<not change>      
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;		 //top+9dB  	
			}
			else if((RF_freq>=80000) && (RF_freq<210000))
			{
				R842_SysFreq_Info.LNA_VTL_H=0x5B;            //LNA VTL/H=0.84/1.44   
				R842_SysFreq_Info.TF_MODE=R842_TF_PLAIN;     //plain 
				R842_SysFreq_Info.Q_CTRL=1;                  //1.5k on
				R842_SysFreq_Info.ENB_ATT=3;                 //normal
				R842_SysFreq_Info.LNA_TOP=4;                 //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5 
				R842_SysFreq_Info.MIXER_TOP=9;               //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;              //top<not change>   
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;		 //top+9dB  	
			}
			else //>210M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;      //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	         //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.Q_CTRL=0;                  //1.5k off
				R842_SysFreq_Info.ENB_ATT=2;                 //dis 0~4		
				R842_SysFreq_Info.LNA_TOP=4;                 //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5 
				R842_SysFreq_Info.MIXER_TOP=15;              //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;              //top<!32>   				        				                   
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;		 //top+9dB    
			}
#if(R842_FOR_LGIT==TRUE)
			R842_SysFreq_Info.NRB_TOP=6;
#endif
		}
		else if(RF_freq>=R842_LNA_MID_LOW[R842_SetTfType] && RF_freq<R842_LNA_HIGH_MID[R842_SetTfType])  //mid band (39n)
		{
			if((RF_freq>=360000) && (RF_freq<=480000))
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;      //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	         //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.Q_CTRL=1;                  //1.5k on  
				R842_SysFreq_Info.ENB_ATT=2;                 //dis 0~4
				R842_SysFreq_Info.LNA_TOP=4;                 //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5
				R842_SysFreq_Info.MIXER_TOP=15;              //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;              //top<!32>   				        				                   
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;		 //top+9dB  
			}
			else // <360M, >480M
			{
				R842_SysFreq_Info.TF_MODE=R842_TF_AUTO;      //Auto
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	         //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.Q_CTRL=1;                  //1.5k on  
				R842_SysFreq_Info.ENB_ATT=2;                 //dis 0~4	
				R842_SysFreq_Info.LNA_TOP=4;                 //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;                 //Nrb TOP=5 
				R842_SysFreq_Info.MIXER_TOP=15;              //MIXER TOP=15
				R842_SysFreq_Info.HYS_MIXTOP=0;              //top<!32>   				        				                   
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;		 //top+9dB   			
			}
#if(R842_FOR_LGIT==TRUE)
			R842_SysFreq_Info.NRB_TOP=6;
#endif
		}
		else  //high band
		{
			if(RF_freq<620000)
			{
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	      //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  //sharp
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off  
				R842_SysFreq_Info.ENB_ATT=3;              //normal
				R842_SysFreq_Info.LNA_TOP=4;              //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;              //Nrb TOP=5
				R842_SysFreq_Info.MIXER_TOP=9;            //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change> 
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;     //top+9dB   		  
			}
			else // >620M
			{
				R842_SysFreq_Info.LNA_VTL_H=0x6B;	      //LNA VTL/H=0.94/1.44   
				R842_SysFreq_Info.TF_MODE=R842_TF_SHARP;  //sharp
				R842_SysFreq_Info.Q_CTRL=0;               //1.5k off  
				R842_SysFreq_Info.ENB_ATT=3;              //normal
				R842_SysFreq_Info.LNA_TOP=4;              //LNA TOP=4
				R842_SysFreq_Info.NRB_TOP=5;              //Nrb TOP=5
				R842_SysFreq_Info.MIXER_TOP=9;            //MIXER TOP=9
				R842_SysFreq_Info.HYS_MIXTOP=3;           //top<not change> 
				R842_SysFreq_Info.IMG_NRB_ADDER=0x08;     //top+9dB   	 			
			}
		}

		R842_SysFreq_Info.RF_TOP=5;              // RF TOP=5             
		R842_SysFreq_Info.RF_VTL_H=0x6B;         // RF VTL/H=0.94/1.44   (R39=0x6B)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;    // RF Gain Limit=15     (R45[7:6]=2'b11)
		R842_SysFreq_Info.MIXER_VTH=0x09;        // MIXER VTH=1.24       (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;        // MIXER VTL=0.74       (R43[3:0]=4)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20; // Mixer Gain Limit=8   (R20[6:5]=2'b01)
		R842_SysFreq_Info.NRB_BW_HPF=0x00;       // Nrb HPF BW=lowest    (R42[3:2]=2'b00)
		R842_SysFreq_Info.NRB_BW_LPF=0x03;       // Nrb LPF BW=lowest    (R42[1:0]=2'b11)
		R842_SysFreq_Info.FILTER_TOP=5;          // Filter TOP=5         (R42[7:4]=4'b1010)
		R842_SysFreq_Info.FILTER_VTH=0x90;       // Filter VTH=1.24      (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;       // Filter VTL=0.74      (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05;//0.3u/1.5u             (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;      //Peak                  (R47[7]=0)
//		R842_SysFreq_Info.IMG_NRB_ADDER=0x04;    //top+6dB               (R45[3:2]=2'b01)   
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;      //+4                    (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=0;            //normal  
		R842_SysFreq_Info.FB1_RES=0;             //2K       
//		R842_SysFreq_Info.MIXER_AMP_LPF=1;       //1 
		R842_SysFreq_Info.MIXER_AMP_LPF=1;        // 1	
#if(R842_FOR_LGIT==TRUE)
		R842_SysFreq_Info.MIXER_AMP_LPF=2;
#else
		R842_SysFreq_Info.MIXER_AMP_LPF=1;          //enhance amp
#endif
		R842_SysFreq_Info.DET_BW_LPF=1; 		  // normal  //daifq

		break;

	case R842_FM:
		R842_SysFreq_Info.LNA_TOP=5;             // LNA TOP=5             (R37[3:0]=4'b1011)
		R842_SysFreq_Info.LNA_VTL_H=0x5B;	     // LNA VTL/H=0.84/1.44   (R38=0x5A)		
		R842_SysFreq_Info.RF_TOP=4;              // RF TOP=4              (R37[6:4]=3'b011)
		R842_SysFreq_Info.RF_VTL_H=0x5A;         // RF VTL/H=0.84/1.34    (R39=0x5A)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;    // RF Gain Limit=15      (R45[7:6]=2'b11)
		R842_SysFreq_Info.MIXER_TOP=9;           // MIXER TOP=9           (R40[3:0]=4'b0110)
		R842_SysFreq_Info.MIXER_VTH=0x09;        // MIXER VTH=1.24        (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;        // MIXER VTL=0.74        (R43[3:0]=4)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60; // Mixer Gain Limit=12   (R20[6:5]=2'b11)
		R842_SysFreq_Info.NRB_TOP=4;             // Nrb TOP=4             (R40[7:4]=4'b1011)
		R842_SysFreq_Info.NRB_BW_HPF=0x08;       // Nrb HPF BW=high       (R42[3:2]=2'b10)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;       // Nrb LPF BW=low        (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=5;          // Filter TOP=5          (R42[7:4]=4'b1010)
		R842_SysFreq_Info.FILTER_VTH=0x90;       // Filter VTH=1.24       (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;       // Filter VTL=0.74       (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05;//0.3u/1.5u              (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;      //Peak                   (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x04;    //top+6dB                (R45[3:2]=2'b01)   		
		R842_SysFreq_Info.TF_MODE=R842_TF_SHARP; //Sharp
		R842_SysFreq_Info.HYS_MIXTOP=3;          //top<not change>        (R30[3:2]=2'b11)
		R842_SysFreq_Info.Q_CTRL=0;              //1.5k off               (R14[7]=0)
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;      //+4                     (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=1;            //+1.5    
		R842_SysFreq_Info.FB1_RES=1;             //8K        
		R842_SysFreq_Info.MIXER_AMP_LPF=4;       //4		
		R842_SysFreq_Info.DET_BW_LPF=1;          //enhance amp
		R842_SysFreq_Info.ENB_ATT=3;             //normal
		break;

	default: //DVB-T
		R842_SysFreq_Info.LNA_TOP=4;             // LNA TOP=4             (R37[3:0]=4'b1011)
		R842_SysFreq_Info.LNA_VTL_H=0x5A;	     // LNA VTL/H=0.84/1.34   (R38=0x5A)		
		R842_SysFreq_Info.RF_TOP=4;              // RF TOP=4              (R37[6:4]=3'b011)
		R842_SysFreq_Info.RF_VTL_H=0x5A;         // RF VTL/H=0.84/1.34    (R39=0x5A)
		R842_SysFreq_Info.RF_GAIN_LIMIT=0xC0;    // RF Gain Limit=15      (R45[7:6]=2'b11)
		R842_SysFreq_Info.MIXER_TOP=9;           // MIXER TOP=9           (R40[3:0]=4'b0110)
		R842_SysFreq_Info.MIXER_VTH=0x09;        // MIXER VTH=1.24        (R41[3:0]=9)
		R842_SysFreq_Info.MIXER_VTL=0x04;        // MIXER VTL=0.74        (R43[3:0]=4)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60; // Mixer Gain Limit=12   (R20[6:5]=2'b11)
		R842_SysFreq_Info.NRB_TOP=4;             // Nrb TOP=4             (R40[7:4]=4'b1011)
		R842_SysFreq_Info.NRB_BW_HPF=0x00;       // Nrb HPF BW=lowest     (R42[3:2]=2'b00)
		R842_SysFreq_Info.NRB_BW_LPF=0x02;       // Nrb LPF BW=low        (R42[1:0]=2'b10)
		R842_SysFreq_Info.FILTER_TOP=5;          // Filter TOP=5          (R42[7:4]=4'b1010)
		R842_SysFreq_Info.FILTER_VTH=0x90;       // Filter VTH=1.24       (R41[7:4]=9)
		R842_SysFreq_Info.FILTER_VTL=0x40;       // Filter VTL=0.74       (R43[7:4]=4)
		//R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05;//0.3u/1.5u              (R44[4:0]=4'b0101)
		R842_SysFreq_Info.BB_DET_MODE=0x00;      //Peak                   (R47[7]=0)
		R842_SysFreq_Info.IMG_NRB_ADDER=0x04;    //top+6dB                (R45[3:2]=2'b01)   
		R842_SysFreq_Info.TF_MODE=R842_TF_SHARP; //Sharp
		R842_SysFreq_Info.HYS_MIXTOP=3;          //top<not change>        (R30[3:2]=2'b11)
		R842_SysFreq_Info.Q_CTRL=0;              //1.5k off               (R14[7]=0)
		R842_SysFreq_Info.FILT3_GAIN_MAN=1;      //+4                     (R24[6]=1)
		R842_SysFreq_Info.HPF_COMP=1;            //+1.5    
		R842_SysFreq_Info.FB1_RES=1;             //8K        
		R842_SysFreq_Info.MIXER_AMP_LPF=4;       //4		
		R842_SysFreq_Info.DET_BW_LPF=1;          //enhance amp
		R842_SysFreq_Info.ENB_ATT=3;             //normal
		break;
	
	} //end switch


	if(R842_Standard < R842_ATV_SIZE)
	{
		R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x01;//0.3u/0.9u             (R44[4:0]=4'b0001)
		R842_SysFreq_Info.LNA_RF_DIS_MODE=0;     //normal                (R45[1:0]=2'b01; R9[6]=1)
		R842_SysFreq_Info.LNA_RF_CHARGE = 0;     //6xch                  (R15[5]=0)
		R842_SysFreq_Info.VGA_OUT_ATT=2;         //-4                    (R17[1:0]=2)		
		R842_SysFreq_Info.VGA_PIN_LVL=0;         //+4	                 (R25[4]=0)

//overwrite
#if(R842_FOR_SEC==TRUE)		
		if(RF_freq<R842_LNA_MID_LOW[R842_SetTfType])  //low band
		{
			if(R842_DetectTfType==R842_UL_USING_270NH) //270nH
			{
				if((RF_freq>180000) && (RF_freq<210000))  //180~210M
				{
					R842_SysFreq_Info.FILT3_GAIN_MAN=0; //normal
				}
			}
		}

		if((RF_freq>=R842_LNA_MID_LOW[R842_SetTfType])&&(RF_freq<R842_LNA_HIGH_MID[R842_SetTfType]))  //Mid band
		{
			if((R842_DetectMidTfType==R842_MID_USING_39NH) && (R842_DetectTfType==R842_UL_USING_270NH)) //Mid=39n (270n/39n)
			{
				if(RF_freq<250000)  //<250M		
				{
					R842_SysFreq_Info.FILT3_GAIN_MAN=0; //normal
					R842_SysFreq_Info.VGA_PIN_LVL=1;    //normal	 
				}
			}
		}
#endif
	}
	else //DTV
	{		
		//NA
		if(RF_freq>R842_LNA_HIGH_MID[R842_SetTfType]) //high band		
			R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x00;//0.15u/0.9u 
		else
			R842_SysFreq_Info.LNA_DIS_SLOW_FAST=0x05;//0.3u/1.5u         (R44[4:0]=4'b0101)

		R842_SysFreq_Info.LNA_RF_DIS_MODE=1;     //both(f+s)             (R45[1:0]=2'b11; R9[6]=1)
		R842_SysFreq_Info.LNA_RF_CHARGE = 1;     //4xch                  (R15[5]=1)
		R842_SysFreq_Info.VGA_OUT_ATT=3;         //bypass                (R17[1:0]=3)
		R842_SysFreq_Info.VGA_PIN_LVL=1;         //normal	             (R25[4]=1)
/*
#if(R842_FOR_LGIT==TRUE)
		R842_SysFreq_Info.FILT3_GAIN_MAN=0;      //normal
		if(RF_freq>R842_LNA_MID_LOW[R842_SetTfType]) //mid/high band
		{
			R842_SysFreq_Info.VGA_PIN_LVL=0;     //+4    
		}
#endif
*/
#if(R842_FOR_SEMCO_MODULE==TRUE)
		R842_SysFreq_Info.FILT3_GAIN_MAN=0;      //normal  
#endif
	}

	R842_SysFreq_Info.LNA_RF_DIS_CURR=0x01;      //normal                (R23[0]=1)
	R842_SysFreq_Info.RF_DIS_SLOW_FAST=0x10;     //0.3u/0.9u             (R44[7:4]=4'b0001)
	R842_SysFreq_Info.BB_DIS_CURR=0x00;          //x1                    (R18[4]=0)
	R842_SysFreq_Info.MIXER_FILTER_DIS=0x03;     //lowest                (R30[1:0]=2'b11)
	R842_SysFreq_Info.ENB_POLYG=0;               //disable,12            (R19[4]=0)
	R842_SysFreq_Info.VGA_PIN_DEL=0;             //normal, delta 28    
/*
#if(R842_FOR_LGIT==TRUE)
	if((RF_freq>=480000) && (RF_freq<520000))
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x40; //10
	else if((RF_freq>=520000) && (RF_freq<580000))
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20; //8
	else if(RF_freq>=580000)
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x40; //10
	else
		R842_SysFreq_Info.MIXER_GAIN_LIMIT = R842_SysFreq_Info.MIXER_GAIN_LIMIT;

	if((R842_Standard==R842_ATSC) || (R842_Standard==R842_ATSC_IF_5M))
	{
		if(RF_freq>770000)
		{
			R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60; //12
		}
	}
#endif
*/
	//gain adjust
#if(R842_FOR_LGIT==TRUE)
	switch(R842_Standard)
	{
	case R842_DVB_T_6M:
	case R842_DVB_T_7M:
	case R842_DVB_T_8M:
	case R842_DVB_T_6M_IF_5M:
	case R842_DVB_T_7M_IF_5M:
	case R842_DVB_T_8M_IF_5M:
	case R842_DVB_T2_6M:
	case R842_DVB_T2_7M: 
	case R842_DVB_T2_8M:
	case R842_DVB_T2_1_7M:
	case R842_DVB_T2_10M:
    case R842_DVB_T2_6M_IF_5M:
	case R842_DVB_T2_7M_IF_5M:
	case R842_DVB_T2_8M_IF_5M:
	case R842_DVB_T2_1_7M_IF_5M:

		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60; // Mixer Gain Limit=12   (R20[6:5]=2'b11)
		R842_SysFreq_Info.VGA_PIN_DEL=1;         // +6
		if(RF_freq<464000)
			R842_SysFreq_Info.VGA_PIN_LVL=1;     // normal	 
		else
			R842_SysFreq_Info.VGA_PIN_LVL=0;     // +4

		R842_SysFreq_Info.FILT3_GAIN_MAN=1;      // +4

		break;


    case R842_DVB_C_8M:
	case R842_DVB_C_6M:	
	case R842_DVB_C_8M_IF_5M:
	case R842_DVB_C_6M_IF_5M:	
		
		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60; // Mixer Gain Limit=12   (R20[6:5]=2'b11)
		R842_SysFreq_Info.VGA_PIN_DEL=1;         // +6
		if(RF_freq>R842_LNA_MID_LOW[R842_SetTfType]) //mid/high band
		{
			R842_SysFreq_Info.VGA_PIN_LVL=0;     //+4    
		}
		R842_SysFreq_Info.FILT3_GAIN_MAN=0;      // normal, LGIT

		break;

	case R842_ATSC:
	case R842_ATSC_IF_5M:

		R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x60; // Mixer Gain Limit=12   (R20[6:5]=2'b11)
		R842_SysFreq_Info.VGA_PIN_DEL=1;         // +6
		R842_SysFreq_Info.VGA_PIN_LVL=0;         // +4
		R842_SysFreq_Info.FILT3_GAIN_MAN=0;      // normal, LGIT

		break;

	default:
		break;
	}
#endif
/*
#if(R842_FOR_LGIT==TRUE)
	if((R842_Standard==R842_ATSC) || (R842_Standard==R842_ATSC_IF_5M)) //ATSC
	{
			if(RF_freq<443000)
			{
				R842_SysFreq_Info.ENB_POLYG=0;                   //12
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;         //Mixer Gain Limit=8
				R842_SysFreq_Info.VGA_PIN_DEL=0;                 //normal, delta 28    
			}
			else if((RF_freq>=443000) && (RF_freq<600000))
			{
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14		
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00;         //Mixer Gain Limit=6
				R842_SysFreq_Info.VGA_PIN_DEL=0;                 //normal, delta 28    
			}
			else if((RF_freq>=600000) && (RF_freq<783000))
			{
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14		
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x00;         //Mixer Gain Limit=6
				//R842_SysFreq_Info.VGA_PIN_DEL=1;                 //+10, delta 20    
				R842_SysFreq_Info.VGA_PIN_DEL=0;                 //normal, delta 28 
			}
			else 
			{	
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14		
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x20;         //Mixer Gain Limit=8		
				R842_SysFreq_Info.VGA_PIN_DEL=0;                 //normal, delta 28    
			}
			
			R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	
	}
	else if(R842_Standard >= R842_ATV_SIZE)  //apply on DTV
	{
		if(R842_SetTfType == R842_TF_270N_39N)
		{
			if(RF_freq<65000)
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	     		
			}
			else if((RF_freq>=R842_LNA_MID_LOW[R842_SetTfType]) && (RF_freq<440000))
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	 		
			}
			else if((RF_freq>=440000) && (RF_freq<800000))
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	 	
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14
			}
			else if(RF_freq>=800000)
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	 	
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14		
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x40;         // Mixer Gain Limit=10		
			}
			else  //low band >65M,  >180MHz
			{		
			}
		}
		else  //390/39n
		{
			if(RF_freq<56000)
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	     		
			}
			else if((RF_freq>=180000) && (RF_freq<440000))
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	 		
			}
			else if((RF_freq>=440000) && (RF_freq<800000))
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	 	
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14
			}
			else if(RF_freq>=800000)
			{
				R842_SysFreq_Info.VGA_PIN_LVL=0;                 //+4	 	
				R842_SysFreq_Info.ENB_POLYG=1;                   //13,14		
				R842_SysFreq_Info.MIXER_GAIN_LIMIT=0x40;         // Mixer Gain Limit=10		
			}	
			else  //low, 56~180M
			{
			}
		}
	}
#endif
*/

	R842_SysFreq_Info.TEMP=0;

	return R842_SysFreq_Info;
	
}




R842_ErrCode R842_Init(void)
{
    UINT8 i;

	//Xtal cap 
	if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
	{
		R842_XTAL_CAP = 0;
	}

	if(R842_Initial_done_flag==FALSE)
	{

		  if(R842_InitReg() != R842_Success)        
			  return R842_Fail;

		  R842_IMR_Cal_Result = 0; 
		  R842_TF_Check_Result = 0;

		  //reset filter cal. data
		  for (i=0; i<R842_STD_SIZE; i++)
		  {	  
			  R842_Fil_Cal_flag[i] = FALSE;
			  R842_Fil_Cal_code[i] = 0;      //R22[5:1]
			  R842_Fil_Cal_BW[i] = 0x00;
			  R842_Fil_Cal_LpfLsb[i] = 0;  //R22[0]
		  }

          if(R842_IMR_done_flag==FALSE)
		  {
			  if(R842_TF_Check() != R842_Success)        
				 return R842_Fail;

			  //start IMR calibration
			  if(R842_Cal_Prepare(R842_IMR_CAL) != R842_Success)     
				  return R842_Fail;

			  if(R842_IMR(2, TRUE, R842_IMR_NOR) != R842_Success)       //Full K node 2
				return R842_Fail;

			  if(R842_IMR(1, FALSE, R842_IMR_NOR) != R842_Success)
				return R842_Fail;

			  if(R842_IMR(0, FALSE, R842_IMR_NOR) != R842_Success)
				return R842_Fail;

			  if(R842_IMR(3, FALSE, R842_IMR_NOR) != R842_Success)   //Full K node 3
				return R842_Fail;

#if(R842_ALL_IMR_NOR==FALSE)
			  //Reverse
			  if(R842_IMR(6, TRUE, R842_IMR_REV) != R842_Success)   //Full K node 6, Rev
				return R842_Fail;

			  if(R842_IMR(5, FALSE, R842_IMR_REV) != R842_Success) 
				return R842_Fail;

			  if(R842_IMR(4, FALSE, R842_IMR_REV) != R842_Success)   
				return R842_Fail;

			  if(R842_IMR(7, TRUE, R842_IMR_REV) != R842_Success)   
				return R842_Fail;
#endif
			  R842_IMR_done_flag = TRUE;

		  }

		  //do Xtal check
		  if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
		  {
			  R842_Xtal_Pwr = R842_XTAL_HIGHEST;
		  }
		  else
		  {
			  if(R842_InitReg() != R842_Success)        
				 return R842_Fail;

			  if(R842_Xtal_Check() != R842_Success)        
				 return R842_Fail;


			  if(R842_Xtal_Pwr_tmp==R842_XTAL_HIGHEST)
				  R842_Xtal_Pwr = R842_XTAL_HIGHEST;
			  else if(R842_Xtal_Pwr_tmp<=2)  //<=low, gm=1.5
				  R842_Xtal_Pwr = 2;
			  else
				  R842_Xtal_Pwr = R842_Xtal_Pwr_tmp+1;	

		  }


		  R842_Initial_done_flag = TRUE;

	} //end if(check init flag)

	//write initial reg
	if(R842_InitReg() != R842_Success)        
		return R842_Fail;

	R842_pre_standard = R842_STD_SIZE;

	return R842_Success;
}



R842_ErrCode R842_InitReg(void)
{
	UINT8 InitArrayCunt = 0;
	UINT8 XtalCap, CapTot, Cap_x, Cap_xx;
	
	//Write Full Table, Set Xtal Power = highest at initial
	R842_I2C_Len.RegAddr = 0;
	R842_I2C_Len.Len = R842_REG_NUM;

	if(R842_XTAL_CAP>31)
	{
		CapTot = R842_XTAL_CAP-10;
		XtalCap = 1;  //10
	}
	else
	{
		CapTot = R842_XTAL_CAP;
		XtalCap = 0;  //0
	}
	Cap_x = CapTot >> 1;
	Cap_xx = CapTot & 0x01;

	R842_iniArray[0][33]=(R842_iniArray[0][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;
	R842_iniArray[1][33]=(R842_iniArray[1][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;  //24M
	R842_iniArray[2][33]=(R842_iniArray[2][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;

	//DLDO1 off
	R842_iniArray[0][8]=(R842_iniArray[0][8] & 0xCF) | 0x30;
	R842_iniArray[1][8]=(R842_iniArray[1][8] & 0xCF) | 0x30;
	R842_iniArray[2][8]=(R842_iniArray[2][8] & 0xCF) | 0x30;

	//DLDO2, ALDO, Mixer, IQ_Gen off
	R842_iniArray[0][11]=(R842_iniArray[0][11] & 0xC0) | 0x3F;
	R842_iniArray[1][11]=(R842_iniArray[1][11] & 0xC0) | 0x3F;
	R842_iniArray[2][11]=(R842_iniArray[2][11] & 0xC0) | 0x3F;

	//gm=off, xtal power=highest
	if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
	{
		R842_iniArray[0][32]=(R842_iniArray[0][32] & 0xE1) | 0x18;
		R842_iniArray[1][32]=(R842_iniArray[1][32] & 0xE1) | 0x18;
		R842_iniArray[2][32]=(R842_iniArray[2][32] & 0xE1) | 0x18;
	}

	//update reg
	if(R842_Xtal == 24000)
	{
		for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
		{
			R842_I2C_Len.Data[InitArrayCunt] = R842_iniArray[0][InitArrayCunt];
			R842_Array[InitArrayCunt] = R842_iniArray[0][InitArrayCunt];
		}
	}
	else if(R842_Xtal == 16000)
	{
		for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
		{
			R842_I2C_Len.Data[InitArrayCunt] = R842_iniArray[1][InitArrayCunt];
			R842_Array[InitArrayCunt] = R842_iniArray[1][InitArrayCunt];
		}	
	}
	else if(R842_Xtal == 27000)
	{
		for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
		{
			R842_I2C_Len.Data[InitArrayCunt] = R842_iniArray[2][InitArrayCunt];
			R842_Array[InitArrayCunt] = R842_iniArray[2][InitArrayCunt];
		}	
	}
	else
	{
		//no support now
		return R842_Fail;
	}

	if(R842_I2C_Write_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;

	//Mixer ON
	R842_I2C.RegAddr = 11;
	R842_Array[11] = R842_Array[11] & 0xFD;  //R11[1]=0
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//IQ Gen ON
	R842_I2C.RegAddr = 11;
	R842_Array[11] = R842_Array[11] & 0xFE;  //R11[0]=0
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//DLDO1 ON
	R842_I2C.RegAddr = 8;
	R842_Array[8] = (R842_Array[8] & 0xCF) | 0x00;  //R8[5:4]=00
	R842_I2C.Data = R842_Array[8];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//ALDO, DLDO2 ON
	R842_I2C.RegAddr = 11;
	R842_Array[11] = (R842_Array[11] & 0xC3) | 0x10;  //R11[5:4]=01, R11[3:2]=00
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//LNA manual 0
	R842_I2C.RegAddr = 13;
	R842_Array[13] = (R842_Array[13] & 0xC0) | 0x01;  
	R842_I2C.Data = R842_Array[13];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//LNA Auto
	R842_I2C.RegAddr = 13;
	R842_Array[13] = (R842_Array[13] & 0xFE) | 0x00;  
	R842_I2C.Data = R842_Array[13];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}


R842_ErrCode R842_TF_Check(void)
{
#if(R842_FOR_LGIT==FALSE)
	UINT8   ADC_Read_Value0 = 60;
	UINT8   ADC_Read_Value32 = 0;
#endif

	R842_Delay_MS(R842_XTAL_CHK_DELAY);

	R842_I2C_Len.RegAddr = 0;
	R842_I2C_Len.Len = 2;    
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
	{
		R842_I2C_Read_Len(&R842_I2C_Len);
	}

	//T2:R1[7:6]=00
	//T3:R1[7:6]=01
	//T5:R1[7:6]=11
//if(R842_Chip!=R842_MT1)
//{
	if((R842_I2C_Len.Data[1] & 0xC0)==0x00)
		R842_Chip = R842_MP;	//T2
	else
		R842_Chip = R842_MT;	

//}
//	UINT8   ADC_Read_Value_mid_27 = 0;
//	UINT8   ADC_Read_Value_mid_other = 0;

	if((R842_I2C_Len.Data[1] & 0xC0)==0xC0)
		R842_Poly = R842_Poly_5;
	else
		R842_Poly = R842_Poly_3;


#if(R842_FOR_LGIT==TRUE)
	R842_DetectTfType = R842_UL_USING_270NH;   //DTMB use 390NH; other use 270NH
#else

	//------- Low Band TF detect --------//
	if(R842_Cal_Prepare(R842_TF_LNA_CAL) != R842_Success)     
		return R842_Fail;

	//Set LPF Gain = 0
	R842_I2C.RegAddr = 41;
	R842_Array[41] = (R842_Array[41] & 0x0F) | (0<<4);
	R842_I2C.Data = R842_Array[41];  
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	 //Set LNA TF=(0,0)
	 R842_I2C.RegAddr = 14;
     R842_Array[14] = (R842_Array[14] & 0x80);  	
     R842_I2C.Data = R842_Array[14];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 R842_Delay_MS(10); //

	 if(R842_Muti_Read(&ADC_Read_Value0) != R842_Success)
		  return R842_Fail;

	 //Set LNA TF=32
	 R842_I2C.RegAddr = 14;
     R842_Array[14] = (R842_Array[14] & 0x80) | 32 ;  	
     R842_I2C.Data = R842_Array[14];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 R842_Delay_MS(10); //

	 if(R842_Muti_Read(&ADC_Read_Value32) != R842_Success)
		 return R842_Fail;

	 //if ADC_Read=0, TF_Check_Fail
	 if((ADC_Read_Value0==0) && (ADC_Read_Value32==0))
		 R842_TF_Check_Result = 1;  //fail
	 else
		 R842_TF_Check_Result = 0;

	 if(ADC_Read_Value0 > ADC_Read_Value32)
        R842_DetectTfType = R842_UL_USING_BEAD; //>60
	 else
	    R842_DetectTfType = R842_UL_USING_270NH; //<20

#endif



	return R842_Success;
}

R842_ErrCode R842_Xtal_Check(void)
{
	UINT8 i = 0;
	//UINT8 lock_bank = 45;  //LO=474
	UINT8 lock_bank = 28;  //LO=800

	//set pll autotune = 64kHz (fast)
	R842_I2C.RegAddr = 47;
	R842_Array[47] = R842_Array[47] & 0xFD;  //R47[1]=0
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//Set Ni, Si, DivNum    
	if (R842_Xtal ==16000)  //LO=474MHz, VCO=3792
	{
		R842_Array[26] = (R842_Array[26] & 0x80) | 21;               //Ni=21
		R842_Array[35] = (R842_Array[35] & 0x3F) | (3<<6);           //Si=3
		R842_Array[35] = (R842_Array[35] & 0xC7) | 0x08;             //div 4
		R842_Array[27] = 0x00;                                       //SDM_L
		R842_Array[28] = 0x00;                                       //SDM_H
		R842_Array[32] = (R842_Array[32] & 0x27) | (2<<3) | (0<<6);  //gm=1; Xtal div1
		R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (1<<3);  //gm=1.5;lowest 
		//R842_Array[30] = (R842_Array[30] & 0xDF) | 0x00;           //AGC ref clk (16) => share with VCO manual code, /2
	}
	else if (R842_Xtal ==24000) //LO=800MHz, VCO=3200
	{
		R842_Array[26] = (R842_Array[26] & 0x80) | 13;               //Ni=13
		R842_Array[35] = (R842_Array[35] & 0x3F) | (1<<6);           //Si=1
		R842_Array[35] = (R842_Array[35] & 0xC7) | 0x08;             //div 4
		R842_Array[27] = 0xAA;                                       //SDM_L
		R842_Array[28] = 0xAA;                                       //SDM_H
		R842_Array[32] = (R842_Array[32] & 0x27) | (0<<3) | (0<<6);  //gm=2; Xtal div1
		R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (1<<3);  //gm=1.5; lowest
		//R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;           //AGC ref clk (24) => share with as VCO manual code, /2
	}
	else if (R842_Xtal ==27000) //LO=800MHz, VCO=3200
	{
		R842_Array[26] = (R842_Array[26] & 0x80) | 11;               //Ni=11
		R842_Array[35] = (R842_Array[35] & 0x3F) | (2<<6);           //Si=2
		R842_Array[35] = (R842_Array[35] & 0xC7) | 0x08;             //div 4
		R842_Array[27] = 0x5E;                                       //SDM_L
		R842_Array[28] = 0x42;                                       //SDM_H
		R842_Array[32] = (R842_Array[32] & 0x27) | (0<<3) | (0<<6);  //gm=2; Xtal div1
		R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (1<<3);  //gm=1.5; lowest
		//R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;           //AGC ref clk (24) => share with as VCO manual code, /2
	}
	else  //no support 
	{
		return R842_Fail;
	}
	R842_I2C.RegAddr = 26;
	R842_I2C.Data = R842_Array[26];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 35;
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 32;
	R842_I2C.Data = R842_Array[32];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 27;
	R842_I2C.Data = R842_Array[27];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 28;
	R842_I2C.Data = R842_Array[28];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//set cap = 41p
	R842_I2C.RegAddr = 33;
	R842_Array[33] = (R842_Array[33] & 0xC0) | 0x3F;  
	R842_I2C.Data = R842_Array[33];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//set manual initial reg = 1 000000; 
	R842_I2C.RegAddr = 30;
	R842_Array[30] = (R842_Array[30] & 0x80) | 0x40;  //manual 
	R842_I2C.Data = R842_Array[30];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//set auto
	R842_I2C.RegAddr = 30;
	R842_Array[30] = (R842_Array[30] & 0xBF);
	R842_I2C.Data = R842_Array[30];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;


	for(i=0; i<R842_XTAL_CHECK_SIZE; i++) //0~6
	{
	    // from weak to strong
		if(i==0)  //gm=1.5, lowest
			R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (1<<3);  
		else if(i==1)  //gm=2, lowest
			R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (0<<3);  
		else if(i==2) //gm=1.5, low
			R842_Array[32] = (R842_Array[32] & 0xE1) | (2<<1) | (1<<3);  
		else if(i==3) //gm=2, low
			R842_Array[32] = (R842_Array[32] & 0xE1) | (2<<1) | (0<<3);  
		else if(i==4) //gm=1.5, high
			R842_Array[32] = (R842_Array[32] & 0xE1) | (1<<1) | (1<<3);  
		else if(i==5) //gm=2, high
			R842_Array[32] = (R842_Array[32] & 0xE1) | (1<<1) | (0<<3);  
		else if(i==6) //gm=1.5, highest
			R842_Array[32] = (R842_Array[32] & 0xE1) | (0<<1) | (1<<3);
		else  //gm=2, highest
			R842_Array[32] = (R842_Array[32] & 0xE1) | (0<<1) | (0<<3);			

		//set gm and xtal power
		R842_I2C.RegAddr = 32;		
		R842_I2C.Data = R842_Array[32];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_Delay_MS(R842_XTAL_CHK_DELAY);  //10ms for div1 /1, agc_ref /2

		R842_I2C_Len.RegAddr = 0x00;
		R842_I2C_Len.Len = 3;
		R842_I2C_Read_Len(&R842_I2C_Len);

        if(((R842_I2C_Len.Data[2] & 0x40) == 0x40) && ((R842_I2C_Len.Data[2] & 0x3F) <= (lock_bank+6)) && ((R842_I2C_Len.Data[2] & 0x3F) >= (lock_bank-6))) 
		{
		    R842_Xtal_Pwr_tmp = i;
			break;
		}

	    if(i==(R842_XTAL_CHECK_SIZE-1))  //5
		{
	        R842_Xtal_Pwr_tmp = i;
		}
	}


    return R842_Success;
}	

R842_ErrCode R842_Cal_Prepare(UINT8 u1CalFlag)
{
	 UINT8   InitArrayCunt = 0;
	 UINT8 XtalCap, CapTot, Cap_x, Cap_xx;
	
    //set Xtal cap
	if(R842_XTAL_CAP>31)
	{
		CapTot = R842_XTAL_CAP-10;
		XtalCap = 1;  //10
	}
	else
	{
		CapTot = R842_XTAL_CAP;
		XtalCap = 0;  //0
	}
	Cap_x = CapTot >> 1;
	Cap_xx = CapTot & 0x01;

	 //Write Full Table, include PLL & RingPLL all settings
	 R842_I2C_Len.RegAddr = 0;
	 R842_I2C_Len.Len = R842_REG_NUM;

	 switch(u1CalFlag)
	 {
	    case R842_IMR_CAL:

#if(R842_FOR_LGIT==TRUE)  //IMR_IF=8000, set BW=8M
				R842_IMR_CAL_Array[0][22]=(R842_IMR_CAL_Array[0][22] & 0x9F);
				R842_IMR_CAL_Array[1][22]=(R842_IMR_CAL_Array[1][22] & 0x9F);  
				R842_IMR_CAL_Array[2][22]=(R842_IMR_CAL_Array[2][22] & 0x9F);
#endif
				R842_IMR_CAL_Array[0][33]=(R842_IMR_CAL_Array[0][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;
				R842_IMR_CAL_Array[1][33]=(R842_IMR_CAL_Array[1][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;  //24M
				R842_IMR_CAL_Array[2][33]=(R842_IMR_CAL_Array[2][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;

				//gm=off, xtal power=highest
				if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
				{
					R842_IMR_CAL_Array[0][32]=(R842_IMR_CAL_Array[0][32] & 0xE1) | 0x18;
					R842_IMR_CAL_Array[1][32]=(R842_IMR_CAL_Array[1][32] & 0xE1) | 0x18;
					R842_IMR_CAL_Array[2][32]=(R842_IMR_CAL_Array[2][32] & 0xE1) | 0x18;
				}

				if(R842_Xtal == 24000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_IMR_CAL_Array[0][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_IMR_CAL_Array[0][InitArrayCunt];
					}
				}
				else if(R842_Xtal == 16000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_IMR_CAL_Array[1][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_IMR_CAL_Array[1][InitArrayCunt];
					}	
				}
				else if(R842_Xtal == 27000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_IMR_CAL_Array[2][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_IMR_CAL_Array[2][InitArrayCunt];
					}
				}
				else
				{
				   //no support  now
					return R842_Fail;
				}

			break;

		case R842_IMR_LNA_CAL:						    

			break;

		case R842_TF_MID_LNA_CAL:

				R842_TF_MID_CAL_Array[0][33]=(R842_TF_MID_CAL_Array[0][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;
				R842_TF_MID_CAL_Array[1][33]=(R842_TF_MID_CAL_Array[1][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;  //24M
				R842_TF_MID_CAL_Array[2][33]=(R842_TF_MID_CAL_Array[2][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;

				//gm=off, xtal power=highest
				if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
				{
					R842_TF_MID_CAL_Array[0][32]=(R842_TF_MID_CAL_Array[0][32] & 0xE1) | 0x18;
					R842_TF_MID_CAL_Array[1][32]=(R842_TF_MID_CAL_Array[1][32] & 0xE1) | 0x18;
					R842_TF_MID_CAL_Array[2][32]=(R842_TF_MID_CAL_Array[2][32] & 0xE1) | 0x18;
				}

				if(R842_Xtal == 24000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_TF_MID_CAL_Array[0][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_TF_MID_CAL_Array[0][InitArrayCunt];
					}
				}
				else if(R842_Xtal == 16000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_TF_MID_CAL_Array[1][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_TF_MID_CAL_Array[1][InitArrayCunt];
					}	
				}
				else if(R842_Xtal == 27000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_TF_MID_CAL_Array[2][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_TF_MID_CAL_Array[2][InitArrayCunt];
					}
				}
				else
				{
				   //no support  now
					return R842_Fail;
				}
			break;

        case R842_TF_LNA_CAL:

				R842_TF_CAL_Array[0][33]=(R842_TF_CAL_Array[0][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;
				R842_TF_CAL_Array[1][33]=(R842_TF_CAL_Array[1][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;  //24M
				R842_TF_CAL_Array[2][33]=(R842_TF_CAL_Array[2][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;

				//gm=off, xtal power=highest
				if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
				{
					R842_TF_CAL_Array[0][32]=(R842_TF_CAL_Array[0][32] & 0xE1) | 0x18;
					R842_TF_CAL_Array[1][32]=(R842_TF_CAL_Array[1][32] & 0xE1) | 0x18;
					R842_TF_CAL_Array[2][32]=(R842_TF_CAL_Array[2][32] & 0xE1) | 0x18;
				}

				if(R842_Xtal == 24000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_TF_CAL_Array[0][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_TF_CAL_Array[0][InitArrayCunt];
					}
				}
				else if(R842_Xtal == 16000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_TF_CAL_Array[1][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_TF_CAL_Array[1][InitArrayCunt];
					}	
				}
				else if(R842_Xtal == 27000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_TF_CAL_Array[2][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_TF_CAL_Array[2][InitArrayCunt];
					}	
				}
				else
				{
				   //no support  now
					return R842_Fail;
				}
			break;

		case R842_LPF_CAL: 

				R842_LPF_CAL_Array[0][33]=(R842_LPF_CAL_Array[0][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;
				R842_LPF_CAL_Array[1][33]=(R842_LPF_CAL_Array[1][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;  //24M
				R842_LPF_CAL_Array[2][33]=(R842_LPF_CAL_Array[2][33] & 0xC0) | (Cap_xx<<5) | (XtalCap<<4) | Cap_x;

				//gm=off, xtal power=highest
				if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
				{
					R842_LPF_CAL_Array[0][32]=(R842_LPF_CAL_Array[0][32] & 0xE1) | 0x18;
					R842_LPF_CAL_Array[1][32]=(R842_LPF_CAL_Array[1][32] & 0xE1) | 0x18;
					R842_LPF_CAL_Array[2][32]=(R842_LPF_CAL_Array[2][32] & 0xE1) | 0x18;
				}

				if(R842_Xtal == 24000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_LPF_CAL_Array[0][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_LPF_CAL_Array[0][InitArrayCunt];
					}
				}
				else if(R842_Xtal == 16000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_LPF_CAL_Array[1][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_LPF_CAL_Array[1][InitArrayCunt];
					}	
				}
				else if(R842_Xtal == 27000)
				{
					for(InitArrayCunt = 8; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
					{
						R842_I2C_Len.Data[InitArrayCunt] = R842_LPF_CAL_Array[2][InitArrayCunt];
						R842_Array[InitArrayCunt] = R842_LPF_CAL_Array[2][InitArrayCunt];
					}
				}
				else
				{
				   //no support 27MHz now
					return R842_Fail;
				}
			break;		

		default:

			break;

	 }

	 if(R842_I2C_Write_Len(&R842_I2C_Len) != R842_Success)
		 return R842_Fail;


	//set pll autotune = 64kHz (fast)
	R842_I2C.RegAddr = 47;
	R842_Array[47] = R842_Array[47] & 0xFD;  //R47[1]=0
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
	
	
      return R842_Success;
}




R842_ErrCode R842_IMR(UINT8 IMR_MEM, UINT8 IM_Flag, UINT8 Rev_Mode)
{
	UINT32 RingVCO = 0;
	UINT32 RingFreq = 0;
	UINT32 RingRef = R842_Xtal;
	UINT8  divnum_ring = 0;

	UINT8  IMR_Gain = 0;
	UINT8  IMR_Phase = 0;

	R842_Sect_Type IMR_POINT;

	if(R842_Xtal==16000)  //16M	
         divnum_ring = 25;                    //3200/8/16.  32>divnum>7
	else if(R842_Xtal==24000) //24M
		 divnum_ring = 17;
	else if(R842_Xtal==27000) //27M
		 divnum_ring = 15;
	else //not support
		 return R842_Fail;
	
	 RingVCO = (divnum_ring)* 8 * RingRef;  //VCO=3264/3200/3240 for 24M/16M/27M
	 RingFreq = RingVCO/48;

#if(R842_FOR_SEMCO_MODULE==TRUE)
	 if(IMR_MEM==3 || IMR_MEM==7)
		 R842_IMR_IF = 5300;
	 else
		 R842_IMR_IF = 3300; //666M
#elif(R842_FOR_LGIT==TRUE)
	 R842_IMR_IF = 8000;
#else
	 R842_IMR_IF = 5300;
#endif

	switch(IMR_MEM)
	{
	case 0: // RingFreq = 136.0M
		RingFreq = RingVCO/24;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (2<<5);  // ring_div1 /6 (2)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (2<<0);  // ring_div2 /4 (2)		
		break;
	case 1: // RingFreq = 326.4M
		RingFreq = RingVCO/10;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (1<<5);  // ring_div1 /5 (1)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (1<<0);  // ring_div2 /2 (1)		
		break;
#if(R842_FOR_SEMCO_MODULE==TRUE)
	case 2: // RingFreq = 652.8
		RingFreq = RingVCO/5;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (1<<5);  // ring_div1 /5 (1)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (0);       // ring_div2 /1 (0)		
		break;
#else
	case 2: // RingFreq = 544M
		RingFreq = RingVCO/6;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (2<<5);  // ring_div1 /6 (2)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (0);       // ring_div2 /1 (0)		
		break;
#endif
	case 3: // RingFreq = 816M
		RingFreq = RingVCO/4;
		R842_Array[34] = (R842_Array[34] & 0x9F) | 0;          // ring_div1 /4 (0)
		R842_Array[35] = (R842_Array[35] & 0xFC) | 0;          // ring_div2 /1 (0)		
		break;
	case 4: // RingFreq = 136.0M
		RingFreq = RingVCO/24;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (2<<5);  // ring_div1 /6 (2)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (2<<0);  // ring_div2 /4 (2)		
		break;
	case 5: // RingFreq = 326.4M
		RingFreq = RingVCO/10;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (1<<5);  // ring_div1 /5 (1)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (1<<0);  // ring_div2 /2 (1)		
		break;
#if(R842_FOR_SEMCO_MODULE==TRUE)
	case 6: // RingFreq = 652.8
		RingFreq = RingVCO/5;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (1<<5);  // ring_div1 /5 (1)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (0);       // ring_div2 /1 (0)		
		break;
#else
	case 6: // RingFreq = 544M
		RingFreq = RingVCO/6;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (2<<5);  // ring_div1 /6 (2)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (0);       // ring_div2 /1 (0)		
		break;
#endif
	case 7: // RingFreq = 816M
		RingFreq = RingVCO/4;
		R842_Array[34] = (R842_Array[34] & 0x9F) | 0;          // ring_div1 /4 (0)
		R842_Array[35] = (R842_Array[35] & 0xFC) | 0;          // ring_div2 /1 (0)		
		break;
	default:
		RingFreq = RingVCO/6;
		R842_Array[34] = (R842_Array[34] & 0x9F) | (2<<5);  // ring_div1 /6 (2)
		R842_Array[35] = (R842_Array[35] & 0xFC) | (0);       // ring_div2 /1 (0)		
		break;
	}

	//write RingPLL setting, R34
	R842_Array[34] = (R842_Array[34] & 0xE0) | divnum_ring;   //ring_div_num, R34[4:0]

	if(RingVCO>=3200000)
	    R842_Array[34] = (R842_Array[34] & 0x7F);   //vco_band=high, R34[7]=0
	 else
        R842_Array[34] = (R842_Array[34] | 0x80);      //vco_band=low, R34[7]=1

	//write RingPLL setting, R34
	R842_I2C.RegAddr = 34;
	R842_I2C.Data = R842_Array[34];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
	
    //write RingPLL setting, R35[1:0]
	R842_I2C.RegAddr = 35;
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//Ring PLL power initial at "min_lp"

	//Must do MUX before PLL() 
	if(Rev_Mode==R842_IMR_NOR)  //normal
	{
		if(R842_MUX(RingFreq - R842_IMR_IF, RingFreq, R842_STD_SIZE) != R842_Success)      //IMR MUX (LO, RF)
			return R842_Fail;

		if(R842_PLL((RingFreq - R842_IMR_IF), (UINT16)R842_IMR_IF, R842_STD_SIZE) != R842_Success)  //IMR PLL
			return R842_Fail;

		 //Img_R = normal
		 R842_I2C.RegAddr = 20;
		 R842_Array[20] = (R842_Array[20] & 0x7F);  //R20[7]=0
		 R842_I2C.Data = R842_Array[20];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;

		// Mixer Amp LPF=1 (0 is widest)
		R842_I2C.RegAddr = 19;
		R842_Array[19] = (R842_Array[19] & 0xF1) | (1<<1); 
		R842_I2C.Data = R842_Array[19];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 	 //Set TF, place after R842_MUX( )
		 //TF is dependent to LNA/Mixer Gain setting
		if(R842_SetTF(RingFreq, (UINT8)R842_SetTfType) != R842_Success)
			return R842_Fail;

		//clear IQ_cap
		IMR_POINT.Iqcap = 0;

		if(IM_Flag == TRUE)
		{
			 if(R842_IQ(&IMR_POINT) != R842_Success)
				return R842_Fail;
		}
		else  //IMR_MEM 1, 3
		{
			if((IMR_MEM==1) || (IMR_MEM==3))
			{
				IMR_POINT.Gain_X = R842_IMR_Data[2].Gain_X;   //node 3
				IMR_POINT.Phase_Y = R842_IMR_Data[2].Phase_Y;
				IMR_POINT.Value = R842_IMR_Data[2].Value;
			}
			else if(IMR_MEM==0) //IMR_MEM 0
			{
				IMR_POINT.Gain_X = R842_IMR_Data[1].Gain_X;  
				IMR_POINT.Phase_Y = R842_IMR_Data[1].Phase_Y;
				IMR_POINT.Value = R842_IMR_Data[1].Value;
			}
	
			if(R842_F_IMR(&IMR_POINT) != R842_Success)
				return R842_Fail;
		}
	}
	else  //Reverse Mode
	{
		if(R842_MUX(RingFreq + R842_IMR_IF, RingFreq, R842_STD_SIZE) != R842_Success)      //IMR MUX (LO, RF)
			return R842_Fail;

		if(R842_PLL((RingFreq + R842_IMR_IF), (UINT16)R842_IMR_IF, R842_STD_SIZE) != R842_Success)  //IMR PLL
			return R842_Fail;

		 //Img_R = reverse
		 R842_I2C.RegAddr = 20;
		 R842_Array[20] = (R842_Array[20] | 0x80);  //R20[7]=1
		 R842_I2C.Data = R842_Array[20];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;

		// Mixer Amp LPF=4 (7 is narrowest)
		R842_I2C.RegAddr = 19;
		R842_Array[19] = (R842_Array[19] & 0xF1) | (4<<1); 
		R842_I2C.Data = R842_Array[19];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		if(R842_SetTF(RingFreq, (UINT8)R842_SetTfType) != R842_Success)
			return R842_Fail;

		//clear IQ_cap
		IMR_POINT.Iqcap = 0;

		if(IM_Flag == TRUE)
		{
			 if(R842_IQ(&IMR_POINT) != R842_Success)
				return R842_Fail;
		}
		else  //IMR_MEM 5, 4,   7
		{
			if(IMR_MEM==5)
			{
				IMR_POINT.Gain_X = R842_IMR_Data[6].Gain_X;    //node 6
				IMR_POINT.Phase_Y = R842_IMR_Data[6].Phase_Y;
				IMR_POINT.Value = R842_IMR_Data[6].Value;
			}
			else if(IMR_MEM==4)
			{
				IMR_POINT.Gain_X = R842_IMR_Data[5].Gain_X;    
				IMR_POINT.Phase_Y = R842_IMR_Data[5].Phase_Y;
				IMR_POINT.Value = R842_IMR_Data[5].Value;
			}
			if(R842_F_IMR(&IMR_POINT) != R842_Success)
				return R842_Fail;
		}
	}

	R842_IMR_Data[IMR_MEM].Gain_X  = IMR_POINT.Gain_X;
	R842_IMR_Data[IMR_MEM].Phase_Y = IMR_POINT.Phase_Y;
	R842_IMR_Data[IMR_MEM].Value = IMR_POINT.Value;
	R842_IMR_Data[IMR_MEM].Iqcap = IMR_POINT.Iqcap;	

	IMR_Gain = R842_IMR_Data[IMR_MEM].Gain_X & 0x1F;   //R20[4:0]
	IMR_Phase = R842_IMR_Data[IMR_MEM].Phase_Y & 0x1F; //R21[4:0]

	if(((IMR_Gain & 0x0F)>6) || ((IMR_Phase & 0x0F)>6))
	{		
		R842_IMR_Cal_Result = 1; //fail
	}

	return R842_Success;
}


R842_ErrCode R842_PLL(UINT32 LO_Freq, UINT16 IF_Freq, R842_Standard_Type R842_Standard)//ok
{
	UINT8   MixDiv = 2;
	UINT8   DivBuf = 0;
	UINT8   Ni = 0;
	UINT8   Si = 0;
	UINT8   DivNum = 0;
	UINT16  Nint = 0;
	UINT32  VCO_Min = 2270000;   //2270 in MT2
	UINT32  VCO_Max = VCO_Min*2;
	UINT32  VCO_Freq = 0;
	UINT32  PLL_Ref	= R842_Xtal;		
	UINT32  VCO_Fra	= 0;		
	UINT16  Nsdm = 2;
	UINT16  SDM = 0;
	UINT16  SDM16to9 = 0;
	UINT16  SDM8to1 = 0;
	UINT8   XTAL_POW = 0;     //highest
	UINT8   XTAL_GM = 0;      //gm=2
	UINT16  u2XalDivJudge;
	UINT8   u1XtalDivRemain;
	UINT8   SDM_RES = 0x00;
	UINT8   NS_RES = 0x00;
	UINT8   IQGen_Cur = 0;    //DminDmin
	UINT8   IQBias = 1;       //BiasI
	UINT8   IQLoad = 0;       //3.2k/2
	UINT8   OutBuf_Bias = 0;  //max
	UINT8   BiasHf = 0;       //135u     
	UINT8   CP_Offset = 0;  
	UINT8   XtalDivQ = 0;
	UINT8   ClkOut = 0;
	UINT8   XtalPwrTemp=0;
	UINT32  Spur_pos;
	UINT32  Spur_neg;
	UINT32  RF_Freq = LO_Freq + IF_Freq;

	UINT8   vco_bank_read = 0;
	UINT8   vco_bank_lock = 0;
	UINT8   BoundDiv = 1;
	UINT8   CentBoundDiv = 1;


	if(R842_Chip == R842_MP) 
		VCO_Min = 2270000; 
	else
		VCO_Min = 2200000;
	VCO_Max = VCO_Min*2;


	//set pll autotune = 64kHz (fast)
	R842_I2C.RegAddr = 47;
	R842_Array[47] = R842_Array[47] & 0xFD;  //R47[1]=0
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	// CP current: 0.7 (R31[4:2]=000, largest BW for analog circuit); VCO current=0 (R31[1:0]=00, max)
	R842_I2C.RegAddr = 31;
	R842_Array[31] = (R842_Array[31] & 0xE0) | 0x00; 
	R842_I2C.Data = R842_Array[31];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	// VCO power = auto
	R842_I2C.RegAddr = 26;
	R842_Array[26] = (R842_Array[26] & 0x7F) | 0x80; // R26[7]=1
	R842_I2C.Data = R842_Array[26];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	// HfDiv Buf = 6dB buffer
	R842_I2C.RegAddr = 17;
	R842_Array[17] = (R842_Array[17] & 0x7F) | 0x00; // R17[7]=0
	R842_I2C.Data = R842_Array[17];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	// PFD DLDO=4mA
	R842_I2C.RegAddr = 8;
	R842_Array[8] = (R842_Array[8] & 0xCF) | 0x00; // R8[5:4]=00
	R842_I2C.Data = R842_Array[8];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	// DLDO2=3mA(R11[5:4]=01); PLL LDOA=2.2V(R11[3:2]=00)
	R842_I2C.RegAddr = 11;
	R842_Array[11] = (R842_Array[11] & 0xC3) | 0x10; 
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	// HF Fiv LDO=7mA (new bonding set this off)
	R842_I2C.RegAddr = 12;
	R842_Array[12] = (R842_Array[12] & 0xF9) | 0x00; // R12[2:1]=00
	R842_I2C.Data = R842_Array[12];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	//Divider
	while(MixDiv <= 64)
	{
		if(((LO_Freq * MixDiv) >= VCO_Min) && ((LO_Freq * MixDiv) < VCO_Max))
		{
			DivBuf = MixDiv;
			while(DivBuf > 2)
			{
				DivBuf = DivBuf >> 1;
				DivNum ++;
			}			
			break;
		}
		MixDiv = MixDiv << 1;
	}

	//IQ Gen block & BiasHF & NS_RES & SDM_Res
	if(MixDiv <= 4)  //Div=2,4
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 1;       //BiasI   
		IQLoad = 0;       //3.2k/2 
		OutBuf_Bias = 0;  //0 (max)     
		BiasHf = 0;       //135u
		SDM_RES = 0;      //short  
		NS_RES = 0;       //0R 
	}
	else if(MixDiv == 8) 
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;       //BiasI/2   
		IQLoad = 1;       //3.2k
		OutBuf_Bias = 1;  //1 
		BiasHf = 1;       //110u
		SDM_RES = 0;      //short  
		NS_RES = 1;       //800R 
	}
	else if(MixDiv == 16) 
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;       //BiasI/2   
		IQLoad = 1;       //3.2k
		OutBuf_Bias = 2;  //2 
		BiasHf = 1;       //110u
		SDM_RES = 1;      //790R
		NS_RES = 0;       //0R
	}
	else if(MixDiv >= 32) //32, 64
	{
		IQGen_Cur = 0;    //DminDmin
		IQBias = 0;       //BiasI/2   
		IQLoad = 1;       //3.2k
		OutBuf_Bias = 3;  //3 (min)
		BiasHf = 1;       //110u
		SDM_RES = 1;      //790R
		NS_RES = 0;       //0R
	}
	else
	{
		return R842_Fail;
	}
	

	//Xtal Div setting
	if(R842_Standard == R842_STD_SIZE) //for cal, RingPLL not support xtal div2
	{
		    R842_XtalDiv = R842_XTAL_DIV1_11; //div1 for calibration
			ClkOut = 1;  //off
			XtalPwrTemp = R842_XTAL_HIGHEST;
			CP_Offset = 0;  //off
	}   
	else  
	{
		if(R842_Mixer_Mode == R842_IMR_NOR) 	
			RF_Freq = LO_Freq - IF_Freq;  		
		else  
			RF_Freq = LO_Freq + IF_Freq;  
		
        if(R842_Xtal==16000)
		   u2XalDivJudge = (UINT16) (RF_Freq/1000/8);
		else if(R842_Xtal==24000)
           u2XalDivJudge = (UINT16) (RF_Freq/1000/12);
		else if(R842_Xtal==27000)
           u2XalDivJudge = (UINT16) (RF_Freq/13500);
		else
           return R842_Fail;

		u1XtalDivRemain = (UINT8) (u2XalDivJudge % 2);
		XtalDivQ = (UINT8) (u2XalDivJudge / 2);

		//fine tune for 24MHz Xtal
		if(R842_Standard < R842_ATV_SIZE) //ATV 
		{
			Spur_pos = (UINT32)(R842_Xtal*XtalDivQ + 2000);  //+2M
			Spur_neg = (UINT32)(R842_Xtal*XtalDivQ + R842_Xtal - 6000);     //-6M
		}
		else  //DTV 
		{
			Spur_pos = (UINT32)(R842_Xtal*XtalDivQ + 4000);  //+4M
			Spur_neg = (UINT32)(R842_Xtal*XtalDivQ + R842_Xtal - 4000);   //-4M
		}

		if( (RF_Freq>Spur_pos) && (RF_Freq<Spur_neg) )  //spur-free		
		{
			R842_XtalDiv = R842_XTAL_DIV1_11;	
			SDM_RES = 0;     //off, since no spur in this area
			ClkOut = 1;      //off
			CP_Offset = 0;   //off
			
			if(R842_Xtal_Pwr==2)  //low, gm=1.5
				XtalPwrTemp = 3;
			else
				XtalPwrTemp = R842_Xtal_Pwr;			
			
		}
		else //spur-area
		{
			if(u1XtalDivRemain==1)
				XtalDivQ = XtalDivQ+1;  //rounding
			else
				XtalDivQ = XtalDivQ;


				if(R842_Standard < R842_ATV_SIZE) //ATV 24MHz xtal
				{
					
#if(R842_FOR_LGIT==TRUE)

					switch(XtalDivQ)	//MT ATV 24MHz		
					{	

					case 2: //48M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV4_22;
						else
							R842_XtalDiv = R842_XTAL_DIV2_21;
						
						break;

					case 10: //240M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV4_22;
						else
							R842_XtalDiv = R842_XTAL_DIV2_21;
						
						break;

					case 21: //504M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV4_22;
						else
							R842_XtalDiv = R842_XTAL_DIV1_11;
						
						break;

					case 22: //528M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV2_12;
						else
							R842_XtalDiv = R842_XTAL_DIV4_22;
						
						break;

					case 4:
					case 8:
					case 9:
					case 11:
					case 13:
					case 14:
					case 15:
					case 16:
					case 18:
					case 19:
					case 23:
					case 24:
					case 25:
					case 26:
					case 27:
					case 28:
					case 29:
					case 31:
					case 32:
					case 33:
						R842_XtalDiv = R842_XTAL_DIV4_22;
						break;

					case 12:	
					case 34:
						R842_XtalDiv = R842_XTAL_DIV2_12;
						break;
		
					case 3:				
					case 5:
					case 6:
					case 7:										
					case 20:																								
						R842_XtalDiv = R842_XTAL_DIV2_21;
						break;				

					default:
						R842_XtalDiv = R842_XTAL_DIV1_11;
						break;
					}

	
					switch(XtalDivQ)
					{		
					case 2: //48M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=4;  //high, gm=1.5
						else
							XtalPwrTemp=2;  //low, gm=1.5						
						break;
			
					case 34: //816M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=2;  //low, gm=1.5
						else
							XtalPwrTemp=6;  //highest, gm=1.5						
						break;

					case 21: //504M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=5;  //high, gm=2	
						else
							XtalPwrTemp=7;  //highest, gm=2
						break;

					case 22: //528M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=7;  //highest, gm=2
						else
							XtalPwrTemp=4;  //high, gm=1.5
						break;

					case 4:					
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
					case 14:
					case 18:					
					case 24: 
					case 26:	
					case 30:
					case 37:
						XtalPwrTemp=2;  //low, gm=1.5
						break;
											
					case 12:
					case 13:
					case 15:
					case 16:
					case 17:
					case 19:										
					case 20:
					case 23:
					case 27:
					case 28:									
						XtalPwrTemp=3;  //low, gm=2
						break;

					case 5:															
						XtalPwrTemp=4;  //high, gm=1.5
						break;
					
					case 32:
					case 33:
						XtalPwrTemp=6;  //highest, gm=1.5
						break;
										
					case 25:
					case 29:										
					case 35:
						XtalPwrTemp=7;  //highest, gm=2
						break;							

					default:  
						XtalPwrTemp=5;  //high, gm=2					
						break;
					}

					//Clk Out
					if(XtalDivQ==3 || XtalDivQ==7 || XtalDivQ==10 || XtalDivQ==12 || XtalDivQ==19 || 
						XtalDivQ==21 || XtalDivQ==22 || XtalDivQ==23 || XtalDivQ==26 || XtalDivQ==33)
						ClkOut = 0; //on
					else
						ClkOut = 1; //off

	#if(R842_ATV_CIF_5M==TRUE)
					if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
					if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
					{
						if(XtalDivQ==10 || XtalDivQ==19 || XtalDivQ==22)
							ClkOut = 1; //off					

						if(XtalDivQ==2)
							ClkOut = 0; //on
					}

					//CP offset 
					if(XtalDivQ==4 || XtalDivQ==10 || XtalDivQ==11 || XtalDivQ==14 ||
						XtalDivQ==22 || XtalDivQ==26 || XtalDivQ==33 || XtalDivQ==36 || XtalDivQ==37) 
						CP_Offset = 1;  //30
					else
						CP_Offset = 0;  //off	

#elif (R842_FOR_SEMCO_MODULE==TRUE)

					switch(XtalDivQ)	//MT ATV 24MHz		
					{	
					
					case 10: //240M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV4_22;
						else
							R842_XtalDiv = R842_XTAL_DIV2_21;
						
						break;

					case 21: //504M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV4_22;
						else
							R842_XtalDiv = R842_XTAL_DIV1_11;
						
						break;

					case 22: //528M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							R842_XtalDiv = R842_XTAL_DIV2_12;
						else
							R842_XtalDiv = R842_XTAL_DIV4_22;
						
						break;

					case 4:
					case 5:
					case 6:
					case 8:					
					case 11:
					case 12:
					case 13:
					case 14:
					case 15:
					case 16:
					case 17:
					case 18:
					case 19:
					case 20:	
					case 23:
					case 24:
					case 25:
					case 26:
					case 27:
					case 28:
					case 29:
					case 31:
					case 32:
					case 33:
					case 34:	
					case 35:	
						R842_XtalDiv = R842_XTAL_DIV4_22;
						break;

					case 2: //48M											
						R842_XtalDiv = R842_XTAL_DIV2_12;
						break;
		
					case 3:									
					case 7:		
					case 9:																												
						R842_XtalDiv = R842_XTAL_DIV2_21;
						break;				

					default:
						R842_XtalDiv = R842_XTAL_DIV1_11;
						break;
					}

	
					switch(XtalDivQ)
					{							
			
					case 34: //816M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=2;  //low, gm=1.5
						else
							XtalPwrTemp=6;  //highest, gm=1.5						
						break;

					case 21: //504M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=5;  //high, gm=2	
						else
							XtalPwrTemp=7;  //highest, gm=2
						break;

					case 22: //528M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=7;  //highest, gm=2
						else
							XtalPwrTemp=4;  //high, gm=1.5
						break;

					case 4:					
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
					case 14:
					case 18:					
					case 24: 
					case 26:	
					case 30:
					case 37:
						XtalPwrTemp=2;  //low, gm=1.5
						break;
											
					case 12:
					case 13:
					case 15:
					case 16:
					case 17:
					case 19:										
					case 20:
					case 23:
					case 27:
					case 28:									
						XtalPwrTemp=3;  //low, gm=2
						break;

					case 2: //48M
					case 5:															
						XtalPwrTemp=4;  //high, gm=1.5
						break;
					
					case 3:
					case 32:
					case 33:
						XtalPwrTemp=6;  //highest, gm=1.5
						break;
										
					case 25:
					case 29:										
					case 35:
						XtalPwrTemp=7;  //highest, gm=2
						break;							

					default:  
						XtalPwrTemp=5;  //high, gm=2					
						break;
					}

					//Clk Out
					if(XtalDivQ==2 || XtalDivQ==3 || XtalDivQ==7 || XtalDivQ==10 || XtalDivQ==12 || XtalDivQ==19 || 
						XtalDivQ==21 || XtalDivQ==22 || XtalDivQ==23 || XtalDivQ==26 || XtalDivQ==33)
						ClkOut = 0; //on
					else
						ClkOut = 1; //off

	#if(R842_ATV_CIF_5M==TRUE)
					if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
					if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
					{
						if(XtalDivQ==10 || XtalDivQ==19 || XtalDivQ==22)
							ClkOut = 1; //off						
					}

					//CP offset 
					if(XtalDivQ==4 || XtalDivQ==10 || XtalDivQ==11 || XtalDivQ==14 ||
						XtalDivQ==22 || XtalDivQ==26 || XtalDivQ==33 || XtalDivQ==36 || XtalDivQ==37) 
						CP_Offset = 1;  //30
					else
						CP_Offset = 0;  //off	
#else  //MTK based
					switch(XtalDivQ)					
					{
					case 2:
					case 4:
					case 6:
					case 7:
					case 8:
					case 9:
					case 10:
					case 11:
					case 14:
					case 15:
					case 17:
					case 18:
					case 19:
					case 20:
					case 24:					
					case 27:
					case 28:
					case 29:
					case 30:
					case 31:
					case 32:
					case 33:
					case 35:
					case 36:
						R842_XtalDiv = R842_XTAL_DIV4_22;
						break;


					case 22: //528
	#if(R842_FOR_SEC==TRUE)						
		#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
		#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
		#endif
							R842_XtalDiv = R842_XTAL_DIV2_12;
						else
							R842_XtalDiv = R842_XTAL_DIV4_22;
	#else
						R842_XtalDiv = R842_XTAL_DIV2_12;
	#endif
						break;

					case 12:					
					//case 22: //528
					case 25:
					case 34:
						R842_XtalDiv = R842_XTAL_DIV2_12;
						break;

					case 3:
					case 5:
					case 23:
					case 26:
						R842_XtalDiv = R842_XTAL_DIV2_21;
						break;

					default:
						R842_XtalDiv = R842_XTAL_DIV1_11;
						break;
					}
	
					switch(XtalDivQ)
					{			
					case 4:
#if(R842_FOR_SEC==TRUE)
					//case 5:
					case 12:
#else
					case 5:
					//case 12:
#endif
					case 6:
					case 7:
					case 8:
					case 9:
//					case 12:
					case 19:
					case 20:
					case 23:
					case 24:
					case 26:
					case 30:					
					case 36:
						XtalPwrTemp=2;  //low, gm=1.5
						break;
					
					case 3:
					case 10:
					case 11:					
					case 15:					
					case 21:					
					case 27:
					case 28:
					case 32:
					case 34:
					case 35:
						XtalPwrTemp=3;  //low, gm=2
						break;

					case 2:	
#if(R842_FOR_SEC==TRUE)
					case 5:
#endif
					case 14:
					case 17:					
						XtalPwrTemp=4;  //high, gm=1.5
						break;

#if(R842_FOR_SEC==TRUE)
					//case 12:
					//	XtalPwrTemp=6;  //highest, gm=1.5			
					//	break;
#else
					case 12:
						XtalPwrTemp=6;  //highest, gm=1.5			
						break;
#endif

					case 13:
					case 16:
					case 18:
						XtalPwrTemp=7;  //highest, gm=2			
						break;

					case 22: //528M
	#if(R842_ATV_CIF_5M==TRUE)
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800) || (R842_Standard==R842_MN_CIF_5M))
	#else
						if((R842_Standard==R842_MN_5100) || (R842_Standard==R842_MN_5800))
	#endif
							XtalPwrTemp=4;  //high, gm=1.5
						else
							XtalPwrTemp=2;  //low, gm=1.5 
						break;

					default:  
						XtalPwrTemp=5;  //high, gm=2					
						break;
					}

					//Clk Out
					if(XtalDivQ==7 || XtalDivQ==19 || 
						XtalDivQ==23 || XtalDivQ==27)
						ClkOut = 0; //on
					else
						ClkOut = 1; //off

					if((R842_Standard==R842_ATSC) || (R842_Standard==R842_ATSC_IF_5M))
					{
						if(XtalDivQ==22)
							ClkOut = 1; //off					
					}

					//CP offset 
#if(R842_FOR_SEC==TRUE)
					if(XtalDivQ==10 || XtalDivQ==11 || XtalDivQ==14 || XtalDivQ==17 || 
						XtalDivQ==22 || XtalDivQ==36)
#else
					if(XtalDivQ==4 || XtalDivQ==10 || XtalDivQ==11 || XtalDivQ==14 || XtalDivQ==17 || 
						XtalDivQ==22 || XtalDivQ==36)
#endif
						CP_Offset = 1;  //30
					else
						CP_Offset = 0;  //off	

					if(RF_Freq<=528000 && RF_Freq>522000)  //528, +0/-6
					{
						R842_XtalDiv = R842_XTAL_DIV4_22;
						XtalPwrTemp=6;  //highest, gm=1.5
						ClkOut = 0;     //on
						CP_Offset = 1;  //30
					}

	#if(R843_TUNER==TRUE)  //overwrite
					if(XtalDivQ==3)
						R842_XtalDiv = R842_XTAL_DIV4_22;

					if(XtalDivQ==4)
						R842_XtalDiv = R842_XTAL_DIV2_12;

					if(XtalDivQ==12 || XtalDivQ==16 || XtalDivQ==25)
						R842_XtalDiv = R842_XTAL_DIV2_21;

					if(XtalDivQ==22)
					{
						R842_XtalDiv = R842_XTAL_DIV1_11;
						XtalPwrTemp=3;  //low, gm=2
						ClkOut = 1;     //off
						CP_Offset = 0;  //off	
					}
	#endif

#endif
				}
				else //DTV 24MHz Xtal
				{
				
#if(R842_FOR_LGIT==TRUE || R842_FOR_SEMCO_MODULE==TRUE)

					switch(XtalDivQ)
					{
					case 2:					
					case 4:
					case 7:
					case 8:
					case 11:
					case 14:
					case 18:
					case 19:
					case 22:
					case 28:
					case 29:
					case 30:
					case 36:
						R842_XtalDiv = R842_XTAL_DIV4_22;
						break;
						
					case 3:
					case 5:
					case 6:											
					case 9:
					case 10:												
					case 17:
					case 20:
					case 24:
					case 26:										
					case 31:
					case 33:					
						R842_XtalDiv = R842_XTAL_DIV2_21;
						break;		
						
					case 23:
					case 25:
					case 27:															
					case 32:
					case 34:
						R842_XtalDiv = R842_XTAL_DIV2_12;
						break;

					default: //12,13,14,15,16,19,21,35,37
						R842_XtalDiv = R842_XTAL_DIV1_11;
						break;
					}
	
					switch(XtalDivQ)
					{						
					case 4:
					case 5:
					case 6:					
					case 8:								
					case 19:	
					case 21:	
					case 22:	
					case 34:
						XtalPwrTemp=2;  //low, gm=1.5
						break;
								
					case 7:
					case 12:		
					case 24:
					case 25:
					case 29:
					case 31:
					case 33:
						XtalPwrTemp=4;  //high, gm=1.5
						break;

					case 13:
					case 16:																
						XtalPwrTemp=6;  //highest, gm=1.5
						break;

					case 9:		
					case 17:
					case 18:	
					case 23:
					case 26:
					case 27:
						XtalPwrTemp=5;  //high, gm=2
						break;
										
					case 30:
					case 32:
					case 35:
						XtalPwrTemp=7;  //highest, gm=2
						break;

					default:
						XtalPwrTemp=3;  //low, gm=2
						break;
					}

					//Clk Out
					if(XtalDivQ==16 || XtalDivQ==23 || XtalDivQ==24 || XtalDivQ==29 || XtalDivQ==34)
						ClkOut = 0; //on
					else
						ClkOut = 1; //off

					//CP offset 
					switch(XtalDivQ)
					{					
					case 2:
					case 4:
					case 6:					
					case 10:	
					case 22:	
					case 25:					
						CP_Offset = 1;  //30
						break;

					default:
						CP_Offset = 0;  //off	
						break;
					}		
#else  //DTV, normal case
					switch(XtalDivQ)
					{
					case 2:
					case 4:	
					case 11:
					case 15:
						R842_XtalDiv = R842_XTAL_DIV4_22;
						break;
					case 3:
					case 5:
					case 6:					
					case 10:		
						R842_XtalDiv = R842_XTAL_DIV2_21;
						break;
					case 7:			
					case 8:			
					case 9:													
						R842_XtalDiv = R842_XTAL_DIV2_12;
						break;

					default:
						R842_XtalDiv = R842_XTAL_DIV1_11;
						break;
					}
	
					switch(XtalDivQ)
					{
					case 3:
					case 4:
					case 7:
					case 17:
					case 19:
					case 22:
					case 26:
					case 29:
					case 31:
					case 33:
						XtalPwrTemp=2;  //low, gm=1.5
						break;

					case 2:
					case 5:
					case 8:
						XtalPwrTemp=4;  //high, gm=1.5
						break;

					case 23:
					case 25:
					case 27:
						XtalPwrTemp=6;  //highest, gm=1.5
						break;

					case 20:
					case 34:
						XtalPwrTemp=5;  //high, gm=2
						break;

					case 12:
					case 16:
					case 30:
					case 32:
						XtalPwrTemp=7;  //highest, gm=2
						break;

					default:
						XtalPwrTemp=3;  //low, gm=2
						break;
					}

					//Clk Out
					if(XtalDivQ==7 || XtalDivQ==12 || XtalDivQ==13 
						|| XtalDivQ==15 || XtalDivQ==18 || XtalDivQ==22 || XtalDivQ==23)
						ClkOut = 0; //on
					else
						ClkOut = 1; //off

					//CP offset 
					switch(XtalDivQ)
					{
					case 4:
					case 6:
					case 8:
					case 9:
					case 10:							
					case 23:
					case 25:
					case 28:
					case 29:
					case 32:
						CP_Offset = 1;  //30
						break;

					default:
						CP_Offset = 0;  //off	
						break;
					}	

	#if(R843_TUNER==TRUE)  //overwrite
					if(XtalDivQ==3)
					{
						XtalPwrTemp=4;  //high, gm=1.5
						CP_Offset = 1;  //30						
					}

					if(XtalDivQ==4 || XtalDivQ==9 || XtalDivQ==16 || XtalDivQ==20
						|| XtalDivQ==24 || XtalDivQ==25 || XtalDivQ==26 || XtalDivQ==28 || XtalDivQ==32)
					{
						R842_XtalDiv = R842_XTAL_DIV2_21;
					}

					if(XtalDivQ==18)
					{
						XtalPwrTemp=5;  //high, gm=2
						CP_Offset = 1;  //30
						ClkOut = 1;     //off
					}

					if(XtalDivQ==23)
					{
						XtalPwrTemp=4;  //high, gm=1.5								
					}


	


					if(XtalDivQ==22)
					{
						R842_XtalDiv = R842_XTAL_DIV1_11;
						XtalPwrTemp=3;  //low, gm=2
						ClkOut = 1;     //off
						CP_Offset = 0;  //off	
					}
	#endif

#endif
					
				} //end MT DTV

		} //end of spur area
	}


    //------ Xtal freq depend setting: Xtal Gm --------//
	if(R842_SHARE_XTAL==R842_SLAVE_XTAL_OUT)
	{	
			XTAL_POW = 0; //highest
			XTAL_GM = 3;  //off
	}
	else 
	{
		if(R842_Initial_done_flag==TRUE)
		{		
			if(XtalPwrTemp<R842_Xtal_Pwr)	
				XtalPwrTemp = R842_Xtal_Pwr;

//read VCO and check again when next channel is gm=1.5, low

	//read PLL lock
	R842_I2C_Len.RegAddr = 0x00;
	R842_I2C_Len.Len = 3;
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;

	vco_bank_read = R842_I2C_Len.Data[2] & 0x3F;

	if((XtalPwrTemp<=2) && (R842_Standard!=R842_STD_SIZE)) //gm=1.5, low
	{
		while((vco_bank_lock==0) && (XtalPwrTemp<7))
		{
			//set manual VCO bank; 
			R842_I2C.RegAddr = 30;
			if(vco_bank_read<32)
				R842_Array[30] = (R842_Array[30] & 0x80) | 0x40;  //manual 0
			else
				R842_Array[30] = (R842_Array[30] & 0x80) | 0x60;  //manual 32
			R842_I2C.Data = R842_Array[30];
			if(R842_I2C_Write(&R842_I2C) != R842_Success)
				return R842_Fail;

			//set auto
			R842_I2C.RegAddr = 30;
			R842_Array[30] = (R842_Array[30] & 0xBF);
			R842_I2C.Data = R842_Array[30];
			if(R842_I2C_Write(&R842_I2C) != R842_Success)
				return R842_Fail;

			R842_Delay_MS(R842_XTAL_CHK_DELAY*2);  //10ms for div1 /1, agc_ref /2

			R842_I2C_Len.RegAddr = 0x00;
			R842_I2C_Len.Len = 3;
			if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
				return R842_Fail;

			if(((R842_I2C_Len.Data[2] & 0x40) == 0x40) && ((R842_I2C_Len.Data[2] & 0x3F) <= (vco_bank_read+5)) && ((R842_I2C_Len.Data[2] & 0x3F) >= (vco_bank_read-5))) 			
			{
				vco_bank_lock = 1;		
				break;
			}
			else  //unlock
			{
				XtalPwrTemp++;

				if(XtalPwrTemp==0)  //gm=1.5, lowest
					R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (1<<3);  
				else if(XtalPwrTemp==1)  //gm=2, lowest
					R842_Array[32] = (R842_Array[32] & 0xE1) | (3<<1) | (0<<3);  
				else if(XtalPwrTemp==2) //gm=1.5, low
					R842_Array[32] = (R842_Array[32] & 0xE1) | (2<<1) | (1<<3);  
				else if(XtalPwrTemp==3) //gm=2, low
					R842_Array[32] = (R842_Array[32] & 0xE1) | (2<<1) | (0<<3);  
				else if(XtalPwrTemp==4) //gm=1.5, high
					R842_Array[32] = (R842_Array[32] & 0xE1) | (1<<1) | (1<<3);  
				else if(XtalPwrTemp==5) //gm=2, high
					R842_Array[32] = (R842_Array[32] & 0xE1) | (1<<1) | (0<<3);  
				else if(XtalPwrTemp==6) //gm=1.5, highest
					R842_Array[32] = (R842_Array[32] & 0xE1) | (0<<1) | (1<<3);
				else  //gm=2, highest
					R842_Array[32] = (R842_Array[32] & 0xE1) | (0<<1) | (0<<3);			
			
				//set gm & xtal power
				R842_I2C.RegAddr = 32;		
				R842_I2C.Data = R842_Array[32];
				if(R842_I2C_Write(&R842_I2C) != R842_Success)
					return R842_Fail;				
			}
		}//end while loop
	}

				//for 16/24/27M
				if(XtalPwrTemp==0)	
				{
					XTAL_GM = 1;    //gm=1.5
					XTAL_POW = 3;   //lowest				
				}
				else if(XtalPwrTemp==1)	
				{
					XTAL_GM = 0;    //gm=2
					XTAL_POW = 3;   //lowest				
				}
				else if(XtalPwrTemp==2)	
				{
					XTAL_GM = 1;    //gm=1.5
					XTAL_POW = 2;   //low			
				}
				else if(XtalPwrTemp==3)	
				{
					XTAL_GM = 0;    //gm=2
					XTAL_POW = 2;   //low				
				}
				else if(XtalPwrTemp==4)	
				{
					XTAL_GM = 1;    //gm=1.5
					XTAL_POW = 1;   //high				
				}
				else if(XtalPwrTemp==5)	
				{
					XTAL_GM = 0;    //gm=2
					XTAL_POW = 1;   //high				
				}
				else if(XtalPwrTemp==6)	
				{
					XTAL_GM = 1;    //gm=1.5
					XTAL_POW = 0;   //highest				
				}
				else  //XtalPwrTemp=7
				{
					XTAL_GM = 0;    //gm=2
					XTAL_POW = 0;   //highest
				}
			
		}  //end of if(R842_Initial_done_flag==TRUE)
		else   //init fail
		{
				XTAL_POW = 0;      //highest,       R32[2:1]=0	
				XTAL_GM = 0;       //gm=2
		}
	}
    //Xtal power & gm & clk_out
	R842_I2C.RegAddr = 32;
	R842_Array[32] = (R842_Array[32] & 0xE0) | (XTAL_POW<<1) | (XTAL_GM<<3) | ClkOut; 
	R842_I2C.Data = R842_Array[32];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

    //Set CP offset
	R842_I2C.RegAddr = 46;
	R842_Array[46] = (R842_Array[46] & 0xEF) | (CP_Offset<<4); // R46[4]
	R842_I2C.Data = R842_Array[46];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	//------ Xtal freq depend setting: AGC ref clk --------//
	if(R842_Xtal==16000)
	{		
		R842_Array[30] = (R842_Array[30] & 0xDF) | 0x00;  //clk(16)/1 /2  = 8M 
	}
	else if(R842_Xtal==24000)
	{
		if((R842_XtalDiv==R842_XTAL_DIV1_11) || (R842_XtalDiv==R842_XTAL_DIV2_12))
			R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;  //clk(24)/1 /3 = 8M
		else
			R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;  //clk(24)/2 /3 = 4M   //related to AGC clk speed 
	}
	else if(R842_Xtal==27000)
	{
		if((R842_XtalDiv==R842_XTAL_DIV1_11) || (R842_XtalDiv==R842_XTAL_DIV2_12))
			R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;  //clk(24)/1 /3 = 8M
		else
			R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;  //clk(24)/2 /3 = 4M   //related to AGC clk speed 
	}
	else  //not support Xtal freq
	{
		return R842_Fail;
	}
	//Set AGC ref clk
	R842_I2C.RegAddr = 30;
	R842_I2C.Data = R842_Array[30];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
/*
#if(R842_FOR_SEMCO_MODULE==TRUE || R842_FOR_LGIT==TRUE) //TBD??
	if(R842_Standard < R842_ATV_SIZE) //ATV 
	{
		//72M, div2_21
		if((LO_Freq==73500) || (LO_Freq==74250) || (LO_Freq==75000) || (LO_Freq==75750) || (LO_Freq==76500)
			|| (LO_Freq==77250) || (LO_Freq==78000) || (LO_Freq==78750) || (LO_Freq==79500))
		{
			LO_Freq = LO_Freq + 6;
		}
	}
#endif
*/
	//------ Xtal divider 1 & 2 --------//
	if(R842_XtalDiv==R842_XTAL_DIV1_11)
	{
		PLL_Ref = R842_Xtal;	         
		R842_Array[32] = (R842_Array[32] & 0x3F) | 0x00; //b7:2nd_div2=0, b6:1st_div2=0
	}
	else if(R842_XtalDiv==R842_XTAL_DIV2_12)
	{
		PLL_Ref = R842_Xtal/2;	         
		R842_Array[32] = (R842_Array[32] & 0x3F) | 0x80; //b7:2nd_div2=1, b6:1st_div2=0
	}
	else if(R842_XtalDiv==R842_XTAL_DIV2_21)
	{
		PLL_Ref = R842_Xtal/2;	         
		R842_Array[32] = (R842_Array[32] & 0x3F) | 0x40; //b7:2nd_div2=0, b6:1st_div2=1
	}
	else if(R842_XtalDiv==R842_XTAL_DIV4_22)  //not use
	{
		PLL_Ref = R842_Xtal/4;	         
		R842_Array[32] = (R842_Array[32] & 0x3F) | 0xC0; //b7:2nd_div2=1, b6:1st_div2=1
	}
	//Xtal divider setting
	R842_I2C.RegAddr = 32;
	R842_I2C.Data = R842_Array[32];
    if(R842_I2C_Write(&R842_I2C) != R842_Success)
	   return R842_Fail;

	//IQ gen current; Out Buf Bias; Divider HfDiv current=135u(R10[1:0]=00)
	R842_I2C.RegAddr = 10;
	R842_Array[10] = (R842_Array[10] & 0x1C) | (IQGen_Cur<<7) | (OutBuf_Bias<<5) | 0x00; 
	R842_I2C.Data = R842_Array[10];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	//BiasI(R29[2]); BiasHF(R29[7:6])
	R842_I2C.RegAddr = 29;
	R842_Array[29] = (R842_Array[29] & 0x3B) | (IQBias<<2) | (BiasHf<<6); 
	R842_I2C.Data = R842_Array[29];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	//force SDM_res=0 if Xtal div1
	if(R842_XtalDiv==R842_XTAL_DIV1_11)	
	{
		SDM_RES = 0;	
	}
	//SDM_RES
	R842_I2C.RegAddr = 30;
	R842_Array[30] = (R842_Array[30] & 0x7F) | (SDM_RES<<7); 
	R842_I2C.Data = R842_Array[30];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	//Divider num
	R842_I2C.RegAddr = 35;
	R842_Array[35] = (R842_Array[35] & 0xC7) | (DivNum << 3);  //R35[5:3]
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	VCO_Freq = LO_Freq * MixDiv;
	Nint = (UINT16) (VCO_Freq / 2 / PLL_Ref);
	VCO_Fra = (UINT16) (VCO_Freq - 2 * PLL_Ref * Nint);

	//max offset = (2*PLL_Ref)/MixDiv

	//NS_RES & IQLoad
	if(VCO_Freq>4200000)
		NS_RES = 0; 
	R842_I2C.RegAddr = 36;
	R842_Array[36] = (R842_Array[36] & 0xDE) | (NS_RES) | (IQLoad<<5); 
	R842_I2C.Data = R842_Array[36];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	if(PLL_Ref==16000)  
	{
		if(MixDiv==2)
		{
			BoundDiv = 4;
			CentBoundDiv = 2;
		}
		else if(MixDiv==4)
		{
			BoundDiv = 2;
			CentBoundDiv = 1;
		}
		else
		{
			BoundDiv = 1;
			CentBoundDiv = 1;
		}
	}
	else if(PLL_Ref==8000)
	{
		if(MixDiv==2)
		{
			BoundDiv = 2;
			CentBoundDiv = 1;
		}
		else if(MixDiv==4)
		{
			BoundDiv = 1;
			CentBoundDiv = 1;
		}
		else
		{
			BoundDiv = 1;
			CentBoundDiv = 1;
		}
	}
	else if((PLL_Ref==24000) || (PLL_Ref==27000))
	{
		if(MixDiv==2)
		{
			BoundDiv = 6;
			CentBoundDiv = 3;
		}
		else if(MixDiv==4)
		{
			BoundDiv = 3;
			CentBoundDiv = 2;
		}
		else if(MixDiv==8)
		{
			BoundDiv = 2;
			CentBoundDiv = 1;
		}
		else
		{
			BoundDiv = 1;
			CentBoundDiv = 1;
		}
	}		
	else if((PLL_Ref==12000) || (PLL_Ref==13500))
	{
		if(MixDiv==2)
		{
			BoundDiv = 3;
			CentBoundDiv = 2;
		}
		else if(MixDiv==4)
		{
			BoundDiv = 2;
			CentBoundDiv = 1;
		}
		else if(MixDiv==8)
		{
			BoundDiv = 1;
			CentBoundDiv = 1;
		}
		else
		{
			BoundDiv = 1;
			CentBoundDiv = 1;
		}
	}
	else
	{
		BoundDiv = 1;
		CentBoundDiv = 1;
	}

	//Boundary spur prevention
	if (VCO_Fra < PLL_Ref/64/BoundDiv)  //2*PLL_Ref/128/BoundDiv
	{
		VCO_Fra = 0;
	}
	else if (VCO_Fra > (2*PLL_Ref - PLL_Ref/64/BoundDiv))  //2*PLL_Ref*(1-1/128/BoundDiv)
	{
		VCO_Fra = 0;
		Nint ++;
	}
	else if((VCO_Fra > (PLL_Ref - PLL_Ref/128/CentBoundDiv)) && (VCO_Fra < PLL_Ref)) //> 2*PLL_Ref*(1-1/128/CentBoundDiv)*0.5,  < 2*PLL_Ref*128/256
	{
		VCO_Fra = (PLL_Ref - PLL_Ref/128/CentBoundDiv);      // VCO_Fra = 2*PLL_Ref*(1-1/128/CentBoundDiv)*0.5
	}
	else if((VCO_Fra > PLL_Ref) && (VCO_Fra < (PLL_Ref + PLL_Ref/128/CentBoundDiv))) //> 2*PLL_Ref*128/256,  < 2*PLL_Ref*(1+1/128/CentBoundDiv)*0.5
	{
		VCO_Fra = (PLL_Ref + PLL_Ref/128/CentBoundDiv);      // VCO_Fra = 2*PLL_Ref*(1+1/128/CentBoundDiv)*0.5
	}
	else
	{
		VCO_Fra = VCO_Fra;
	}
	
/*
	//Boundary spur prevention
	if (VCO_Fra < PLL_Ref/64)           //2*PLL_Ref/128, boundary spur offset = (2*PLL_Ref)/128/Mix_Div
		VCO_Fra = 0;
	else if (VCO_Fra > PLL_Ref*127/64)  //2*PLL_Ref*127/128
	{
		VCO_Fra = 0;
		Nint ++;
	}
	else if((VCO_Fra > PLL_Ref*127/128) && (VCO_Fra < PLL_Ref)) //> 2*PLL_Ref*127/256,  < 2*PLL_Ref*128/256
		VCO_Fra = PLL_Ref*127/128;      // VCO_Fra = 2*PLL_Ref*127/256
	else if((VCO_Fra > PLL_Ref) && (VCO_Fra < PLL_Ref*129/128)) //> 2*PLL_Ref*128/256,  < 2*PLL_Ref*129/256
		VCO_Fra = PLL_Ref*129/128;      // VCO_Fra = 2*PLL_Ref*129/256
	else
		VCO_Fra = VCO_Fra;
*/
	//Ni & Si	
	Ni = (UINT8) ((Nint - 13) / 4);
	Si = (UINT8) (Nint - 4 *Ni - 13);

	R842_I2C.RegAddr = 26;
	R842_Array[26] = (R842_Array[26] & 0x80) | Ni;     //R26[6:0]
	R842_I2C.Data = R842_Array[26];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	  return R842_Fail;

	R842_I2C.RegAddr = 35;
	R842_Array[35] = (R842_Array[35] & 0x3F) | (Si<<6);  //R35[7:6]
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	  return R842_Fail;
         	
	//pw_sdm & pw_dither
	R842_I2C.RegAddr = 29;
	R842_Array[29] &= 0xFC;    //R29[1:0]
	if(VCO_Fra == 0)
	{
		R842_Array[29] |= 0x03;
	}

#if(R842_FOR_LGIT==TRUE)
	if(R842_Standard >= R842_ATV_SIZE) //DTV 
	{
		if(R842_Xtal==24000)
		{
			if(RF_Freq>=68000 && RF_Freq<=76000)
				R842_Array[29] = (R842_Array[29] & 0xFC);  //SDM on
		}
	}
#endif

	R842_I2C.Data = R842_Array[29];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//SDM calculator
	while(VCO_Fra > 1)
	{			
		if (VCO_Fra > (2*PLL_Ref / Nsdm))
		{		
			SDM = SDM + 32768 / (Nsdm/2);
			VCO_Fra = VCO_Fra - 2*PLL_Ref / Nsdm;
			if (Nsdm >= 0x8000)
				break;
		}
		Nsdm = Nsdm << 1;
	}

	SDM16to9 = SDM >> 8;
	SDM8to1 =  SDM - (SDM16to9 << 8);

	R842_I2C.RegAddr = 28;
	R842_Array[28] = (UINT8) SDM16to9;  //R28
	R842_I2C.Data = R842_Array[28];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 27;
	R842_Array[27] = (UINT8) SDM8to1;    //R27
	R842_I2C.Data = R842_Array[27];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

 //move to end of R842_SetFreq( )??
	//PLL_lock delay time & AGC clk
	//Xtal freq/div1/agc_ref/pll_atune(2^10)*64
	if(R842_Xtal==24000 || R842_Xtal==27000)  //24M, 27M
	{
		if((R842_XtalDiv == R842_XTAL_DIV4_22) || (R842_XtalDiv == R842_XTAL_DIV2_21))
		{
			R842_Delay_MS(R842_PLL_LOCK_DELAY*2);  //agc_ref: /3  (4M)
			R842_Array[47] = (R842_Array[47] & 0xF3) | 0x00;  //R47[3:2]=00 (1KHz)
		}
		else
		{
			R842_Delay_MS(R842_PLL_LOCK_DELAY);      //agc_ref: /3 (8M)
			R842_Array[47] = (R842_Array[47] & 0xF3) | 0x04;  //R47[3:2]=01 (512Hz)
		}
	}
	else  //16M
	{
		if((R842_XtalDiv == R842_XTAL_DIV4_22) || (R842_XtalDiv == R842_XTAL_DIV2_21))
		{
			R842_Delay_MS(R842_PLL_LOCK_DELAY*2);	//agc_ref: /2  (4M)
			R842_Array[47] = (R842_Array[47] & 0xF3) | 0x00;  //R47[3:2]=00 (1KHz)
		}
		else 
		{
			R842_Delay_MS(R842_PLL_LOCK_DELAY);     //agc_ref: /2  (8M)
			R842_Array[47] = (R842_Array[47] & 0xF3) | 0x04;  //R47[3:2]=01 (512Hz)
		}
	}

	//Set AGC clk
	R842_I2C.RegAddr = 47;	
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//read PLL lock
	R842_I2C_Len.RegAddr = 0x00;
	R842_I2C_Len.Len = 3;
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;

	if( (R842_I2C_Len.Data[2] & 0x40) == 0x00 ) 
	{
		R842_I2C.RegAddr = 32;
		R842_Array[32] = (R842_Array[32] & 0xE7) | 0x00;  //gm2
		R842_I2C.Data = R842_Array[32];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;
	}


	//set pll autotune = 1khz (1)
	R842_I2C.RegAddr = 47;
	R842_Array[47] = (R842_Array[47] & 0xFD) | 0x02;  //R47[1]=1
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;

}


R842_ErrCode R842_MUX(UINT32 LO_KHz, UINT32 RF_KHz, R842_Standard_Type R842_Standard)
{	
	UINT8 Reg_IMR_Gain   = 0;
	UINT8 Reg_IMR_Phase  = 0;
	UINT8 Reg_IMR_Iqcap  = 0;

	//Freq_Info_Type R842_Freq_Info1;
	R842_Freq_Info1 = R842_Freq_Sel(LO_KHz, RF_KHz, R842_Standard);

	// LNA band, TF LPF
	R842_I2C.RegAddr = 15;
	R842_Array[15] = (R842_Array[15] & 0xBC) | (R842_Freq_Info1.LNA_BAND) | (R842_Freq_Info1.BYP_LPF<<6);  //R15[1:0], R15[6]
	R842_I2C.Data = R842_Array[15];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	// RF Polyfilter
	R842_I2C.RegAddr = 17;
	R842_Array[17] = (R842_Array[17] & 0x9F) | (R842_Freq_Info1.RF_POLY<<5);  //R17[6:5]
	R842_I2C.Data = R842_Array[17];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	// LNA Cap, Notch
	R842_I2C.RegAddr = 16;
	R842_Array[16] = (R842_Array[16] & 0x00) | (R842_Freq_Info1.LPF_CAP)  | (R842_Freq_Info1.LPF_NOTCH<<4);	 //R16
	R842_I2C.Data = R842_Array[16];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
/*
	// LNA Notch
	R842_I2C.RegAddr = 16;
	R842_Array[16] = (R842_Array[16] & 0x0F) | (R842_Freq_Info1.LPF_NOTCH<<4);  //R16[7:4]
	R842_I2C.Data = R842_Array[16];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	 // Set TF LPF
	 R842_I2C.RegAddr = 15;
	 R842_Array[15] = (R842_Array[15] & 0xBF) | (R842_Freq_Info1.BYP_LPF<<6);  //R15[6]
     R842_I2C.Data = R842_Array[15];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
        return R842_Fail;
*/
	//Set_IMR
	if(R842_IMR_done_flag == TRUE)
	{
		if(R842_Mixer_Mode==R842_IMR_NOR)
		{
			Reg_IMR_Gain = R842_IMR_Data[R842_Freq_Info1.IMR_MEM_NOR].Gain_X & 0x1F;   //R20[4:0]
			Reg_IMR_Phase = R842_IMR_Data[R842_Freq_Info1.IMR_MEM_NOR].Phase_Y & 0x1F; //R21[4:0]
			Reg_IMR_Iqcap = R842_IMR_Data[R842_Freq_Info1.IMR_MEM_NOR].Iqcap;          //0,1,2
		}
		else
		{
			Reg_IMR_Gain = R842_IMR_Data[R842_Freq_Info1.IMR_MEM_REV].Gain_X & 0x1F;   //R20[4:0]
			Reg_IMR_Phase = R842_IMR_Data[R842_Freq_Info1.IMR_MEM_REV].Phase_Y & 0x1F; //R21[4:0]
			Reg_IMR_Iqcap = R842_IMR_Data[R842_Freq_Info1.IMR_MEM_REV].Iqcap;          //0,1,2		
		}
/*
		if(((Reg_IMR_Gain & 0x0F)>6) || ((Reg_IMR_Phase & 0x0F)>6))
		{
			Reg_IMR_Gain = 0;
			Reg_IMR_Phase = 0;
			Reg_IMR_Iqcap = 0; 		
			R842_IMR_Cal_Result = 1; //fail
		}
		else
		{
			R842_IMR_Cal_Result = 0; //ok
		}
*/		
		if(R842_IMR_Cal_Result==1)  //fail
		{
			Reg_IMR_Gain = 0;
			Reg_IMR_Phase = 0;
			Reg_IMR_Iqcap = 0;
		}
	}
	else
	{
		Reg_IMR_Gain = 0;
	    Reg_IMR_Phase = 0;
		Reg_IMR_Iqcap = 0;
	}

	//Gain, R20[4:0]
	R842_I2C.RegAddr = R842_IMR_GAIN_REG;                  
	R842_Array[R842_IMR_GAIN_REG] = (R842_Array[R842_IMR_GAIN_REG] & 0xE0) | (Reg_IMR_Gain & 0x1F);
	R842_I2C.Data = R842_Array[R842_IMR_GAIN_REG];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

    //Phase, R21[4:0]
	R842_I2C.RegAddr = R842_IMR_PHASE_REG;                  
	R842_Array[R842_IMR_PHASE_REG] = (R842_Array[R842_IMR_PHASE_REG] & 0xE0) | (Reg_IMR_Phase & 0x1F);
	R842_I2C.Data = R842_Array[R842_IMR_PHASE_REG];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//Iqcap, R19[7:6]
	R842_I2C.RegAddr = R842_IMR_IQCAP_REG;
	R842_Array[R842_IMR_IQCAP_REG] = (R842_Array[R842_IMR_IQCAP_REG] & 0x3F) | (Reg_IMR_Iqcap<<6);
	R842_I2C.Data =R842_Array[R842_IMR_IQCAP_REG]  ;
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}


R842_ErrCode R842_SetTF(UINT32 u4FreqKHz, UINT8 u1TfType)
{
    UINT8    u1FreqCount = 0;
	UINT32  u4Freq1 = 0;
	UINT32  u4Freq2 = 0;
	UINT32  u4Ratio;
	UINT8    u1TF_Set_Result1 = 0;
	UINT8    u1TF_Set_Result2 = 0;
	UINT8    u1TF_tmp1, u1TF_tmp2;
	UINT16   u2Int;
	
	if((u4FreqKHz>0) && (u4FreqKHz<R842_LNA_MID_LOW[R842_SetTfType]))  //Low
	{
         while((u4FreqKHz < R842_TF_Freq_Low[u1TfType][u1FreqCount]) && (u1FreqCount<R842_TF_LOW_NUM))
		 {
            u1FreqCount++;
		 }

		 if(u1FreqCount==0)
		 {
			 R842_TF = R842_TF_Result_Low[u1TfType][0];
		 }
		 else if(u1FreqCount==R842_TF_LOW_NUM)
        {
			 R842_TF = R842_TF_Result_Low[u1TfType][R842_TF_LOW_NUM-1];
		 }
		 else
		 {
			 u1TF_Set_Result1 = R842_TF_Result_Low[u1TfType][u1FreqCount-1]; 
		     u1TF_Set_Result2 = R842_TF_Result_Low[u1TfType][u1FreqCount]; 
		     u4Freq1 = R842_TF_Freq_Low[u1TfType][u1FreqCount-1];
		     u4Freq2 = R842_TF_Freq_Low[u1TfType][u1FreqCount]; 

			 u1TF_tmp1 = ((u1TF_Set_Result1 & 0x40)>>2)*3 + (u1TF_Set_Result1 & 0x3F);  //b6 is 3xb4
			 u1TF_tmp2 = ((u1TF_Set_Result2 & 0x40)>>2)*3 + (u1TF_Set_Result2 & 0x3F);		
				 
			 u4Ratio = (u4Freq1- u4FreqKHz)*100/(u4Freq1 - u4Freq2);

			 u2Int = (UINT16)((u1TF_tmp2 - u1TF_tmp1)*u4Ratio/100);
			 R842_TF = u1TF_tmp1 + (UINT8)u2Int;
			 if(((u1TF_tmp2 - u1TF_tmp1)*u4Ratio - u2Int*100) > 50)			 
			     R842_TF = R842_TF + 1;	
			
			 if(R842_TF>=0x40)
			 {
				 R842_TF = (R842_TF + 0x10);
			 }
		 }
	}
	else if((u4FreqKHz>=R842_LNA_MID_LOW[R842_SetTfType]) && (u4FreqKHz<R842_LNA_HIGH_MID[R842_SetTfType]))  //Mid
    {
         while((u4FreqKHz < R842_TF_Freq_Mid[u1TfType][u1FreqCount]) && (u1FreqCount<R842_TF_MID_NUM))
		 {
            u1FreqCount++;
		 }

		 if(u1FreqCount==0)
		 {
			 R842_TF = R842_TF_Result_Mid[u1TfType][0];
		 }
		 else if(u1FreqCount==R842_TF_MID_NUM)
        {
			 R842_TF = R842_TF_Result_Mid[u1TfType][R842_TF_MID_NUM-1];
		 }
		 else
		 {
			 u1TF_Set_Result1 = R842_TF_Result_Mid[u1TfType][u1FreqCount-1]; 
		     u1TF_Set_Result2 = R842_TF_Result_Mid[u1TfType][u1FreqCount]; 
		     u4Freq1 = R842_TF_Freq_Mid[u1TfType][u1FreqCount-1];
		     u4Freq2 = R842_TF_Freq_Mid[u1TfType][u1FreqCount]; 

			 u1TF_tmp1 = ((u1TF_Set_Result1 & 0x40)>>2) + (u1TF_Set_Result1 & 0x3F);  //b6 is 1xb4
			 u1TF_tmp2 = ((u1TF_Set_Result2 & 0x40)>>2) + (u1TF_Set_Result2 & 0x3F);	

			 u4Ratio = (u4Freq1- u4FreqKHz)*100/(u4Freq1 - u4Freq2);

			 u2Int = (UINT16)((u1TF_tmp2 - u1TF_tmp1)*u4Ratio/100);
			 R842_TF = u1TF_tmp1 + (UINT8)u2Int;
			 if(((u1TF_tmp2 - u1TF_tmp1)*u4Ratio - u2Int*100) > 50)			 
			     R842_TF = R842_TF + 1;			 

			 if(R842_TF>=0x40)
			 {
				 R842_TF = (R842_TF + 0x30);
			 }
		 }
	}
	else  //HIGH
	{
         while((u4FreqKHz < R842_TF_Freq_High[u1TfType][u1FreqCount]) && (u1FreqCount<R842_TF_HIGH_NUM))
		 {
            u1FreqCount++;
		 }

		 if(u1FreqCount==0)
		 {
			 R842_TF = R842_TF_Result_High[u1TfType][0];
		 }
		 else if(u1FreqCount==R842_TF_HIGH_NUM)
        {
			 R842_TF = R842_TF_Result_High[u1TfType][R842_TF_HIGH_NUM-1];
		 }
		 else
		 {
			 u1TF_Set_Result1 = R842_TF_Result_High[u1TfType][u1FreqCount-1]; 
		     u1TF_Set_Result2 = R842_TF_Result_High[u1TfType][u1FreqCount]; 
		     u4Freq1 = R842_TF_Freq_High[u1TfType][u1FreqCount-1];
		     u4Freq2 = R842_TF_Freq_High[u1TfType][u1FreqCount]; 
			 u4Ratio = (u4Freq1- u4FreqKHz)*100/(u4Freq1 - u4Freq2);

			 u2Int = (UINT16)((u1TF_Set_Result2 - u1TF_Set_Result1)*u4Ratio/100);
			 R842_TF = u1TF_Set_Result1 + (UINT8)u2Int;
			 if(((u1TF_Set_Result2 - u1TF_Set_Result1)*u4Ratio - u2Int*100) > 50)			 
			     R842_TF = R842_TF + 1;	             
		 }
	}
  
    //Set TF: R14[6:0]
	R842_I2C.RegAddr = 14;
	R842_Array[14] = (R842_Array[14] & 0x80) | R842_TF;
	R842_I2C.Data = R842_Array[14]  ;
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

    return R842_Success;
}


R842_ErrCode R842_IQ(R842_Sect_Type* IQ_Pont)
{
	R842_Sect_Type Compare_IQ[3];
	UINT8   X_Direction;  // 1:X, 0:Y

	 //------- increase Filter gain to let ADC read value significant ---------//
	UINT8   LPF_Count = 0;
	UINT8   ADC_Read_Value = 0;

	 for(LPF_Count=5; LPF_Count < 16; LPF_Count=LPF_Count+2)  //start from 5
	 {
		R842_I2C.RegAddr = 41;
		R842_Array[41] = (R842_Array[41] & 0x0F) | (LPF_Count<<4);
		R842_I2C.Data = R842_Array[41];  
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_Delay_MS(R842_FILTER_GAIN_DELAY); //
		
		if(R842_Muti_Read(&ADC_Read_Value) != R842_Success)
			return R842_Fail;

		if(ADC_Read_Value > 40*R842_ADC_READ_COUNT)
			break;
	 }

/*
	//Filter Gain 15
	R842_I2C.RegAddr = 41;
	R842_Array[41] = (R842_Array[41] & 0x0F) | (15<<4);
	R842_I2C.Data = R842_Array[41];  
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
*/
	//give a initial value, no useful
	Compare_IQ[0].Gain_X  = R842_Array[R842_IMR_GAIN_REG] & 0xE0; 
	Compare_IQ[0].Phase_Y = R842_Array[R842_IMR_PHASE_REG] & 0xE0;	

	    // Determine X or Y
	    if(R842_IMR_Cross(&Compare_IQ[0], &X_Direction) != R842_Success)
			return R842_Fail;

		if(X_Direction==1)
		{
			//compare and find min of 3 points. determine I/Q direction
		    if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
			  return R842_Fail;

		    //increase step to find min value of this direction
		    if(R842_CompreStep(&Compare_IQ[0], R842_IMR_GAIN_REG) != R842_Success)  //X
			  return R842_Fail;
		}
		else
		{
		   //compare and find min of 3 points. determine I/Q direction
		   if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		   	 return R842_Fail;

		   //increase step to find min value of this direction
		   if(R842_CompreStep(&Compare_IQ[0], R842_IMR_PHASE_REG) != R842_Success)  //Y
			 return R842_Fail;
		}

		//Another direction
		if(X_Direction==1) //Y-direct
		{	    
           if(R842_IQ_Tree5(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success) //Y
		     return R842_Fail;

		   //compare and find min of 3 points. determine I/Q direction
		   if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		   	 return R842_Fail;

		   //increase step to find min value of this direction
		   if(R842_CompreStep(&Compare_IQ[0], R842_IMR_PHASE_REG) != R842_Success)  //Y
			 return R842_Fail;
		}
		else //X-direct
		{
		   if(R842_IQ_Tree5(Compare_IQ[0].Phase_Y, Compare_IQ[0].Gain_X, R842_IMR_PHASE_REG, &Compare_IQ[0]) != R842_Success) //X
		     return R842_Fail;
        
		   //compare and find min of 3 points. determine I/Q direction
		   if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		     return R842_Fail;

	       //increase step to find min value of this direction
		   if(R842_CompreStep(&Compare_IQ[0], R842_IMR_GAIN_REG) != R842_Success) //X
		     return R842_Fail;
		}
		

		//--- Check 3 points again---//
		if(X_Direction==1)  //X-direct
		{
		    if(R842_IQ_Tree(Compare_IQ[0].Phase_Y, Compare_IQ[0].Gain_X, R842_IMR_PHASE_REG, &Compare_IQ[0]) != R842_Success) //X
			  return R842_Fail;
		}
		else  //Y-direct
		{
		   if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success) //Y
			return R842_Fail;
		}

		if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
			return R842_Fail;

    //Section-9 check
	if(R842_Section(&Compare_IQ[0]) != R842_Success)
			return R842_Fail;

	//clear IQ_Cap = 0
	//Compare_IQ[0].Iqcap = R842_Array[R842_IMR_IQCAP_REG] & 0x3F;
	Compare_IQ[0].Iqcap = 0;

	if(R842_IMR_Iqcap(&Compare_IQ[0]) != R842_Success)
			return R842_Fail;

	*IQ_Pont = Compare_IQ[0];

	//reset gain/phase/iqcap control setting
	R842_I2C.RegAddr = R842_IMR_GAIN_REG;
	R842_Array[R842_IMR_GAIN_REG] = R842_Array[R842_IMR_GAIN_REG] & 0xE0;
	R842_I2C.Data = R842_Array[R842_IMR_GAIN_REG];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = R842_IMR_PHASE_REG;
	R842_Array[R842_IMR_PHASE_REG] = R842_Array[R842_IMR_PHASE_REG] & 0xE0;
	R842_I2C.Data = R842_Array[R842_IMR_PHASE_REG];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = R842_IMR_IQCAP_REG;
	R842_Array[R842_IMR_IQCAP_REG] = R842_Array[R842_IMR_IQCAP_REG] & 0x3F;
	R842_I2C.Data = R842_Array[R842_IMR_IQCAP_REG];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}



//--------------------------------------------------------------------------------------------
// Purpose: record IMR results by input gain/phase location
//          then adjust gain or phase positive 1 step and negtive 1 step, both record results
// input: FixPot: phase or gain
//        FlucPot phase or gain
//        PotReg: Reg20 or Reg21
//        CompareTree: 3 IMR trace and results
// output: TREU or FALSE
//--------------------------------------------------------------------------------------------
R842_ErrCode R842_IQ_Tree(UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R842_Sect_Type* CompareTree)
{
	UINT8 TreeCunt  = 0;
	UINT8 PntReg = 0;
		
	//PntReg is reg to change; FlucPot is change value
	if(PotReg == R842_IMR_GAIN_REG)
		PntReg = R842_IMR_PHASE_REG; //phase control
	else
		PntReg = R842_IMR_GAIN_REG; //gain control

	for(TreeCunt = 0; TreeCunt<3; TreeCunt ++)
	{
		R842_I2C.RegAddr = PotReg;
		R842_I2C.Data = FixPot;
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_I2C.RegAddr = PntReg;
		R842_I2C.Data = FlucPot;
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		if(R842_Muti_Read(&CompareTree[TreeCunt].Value) != R842_Success)
			return R842_Fail;
	
		if(PotReg == R842_IMR_GAIN_REG)
		{
			CompareTree[TreeCunt].Gain_X  = FixPot;
			CompareTree[TreeCunt].Phase_Y = FlucPot;
		}
		else
		{
			CompareTree[TreeCunt].Phase_Y  = FixPot;
			CompareTree[TreeCunt].Gain_X = FlucPot;
		}
		
		if(TreeCunt == 0)   //try right-side point
			FlucPot ++; 
		else if(TreeCunt == 1) //try left-side point
		{
			if((FlucPot & 0x0F) == 1) //if absolute location is 1, change I/Q direction
			{
				if(FlucPot & 0x10) //b[4]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;			
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;
				}
			}
			else
				FlucPot = FlucPot - 2;  
				
		}
	}

	return R842_Success;
}




R842_ErrCode R842_IQ_Tree5(UINT8 FixPot, UINT8 FlucPot, UINT8 PotReg, R842_Sect_Type* CompareTree)
{
	UINT8 TreeCunt  = 0;
	UINT8 TreeTimes = 5;
	UINT8 TempPot   = 0;
	UINT8 PntReg = 0;
	UINT8 CompCunt = 0;
	R842_Sect_Type CorTemp[5];
    R842_Sect_Type Compare_Temp;
	UINT8 CuntTemp = 0;

	//memset(&Compare_Temp,0, sizeof(R842_Sect_Type));
	Compare_Temp.Gain_X = 0;
	Compare_Temp.Phase_Y = 0;
	Compare_Temp.Iqcap = 0;
	Compare_Temp.Value = 255;
		
	for(CompCunt=0; CompCunt<3; CompCunt++)
	{
		CorTemp[CompCunt].Gain_X = CompareTree[CompCunt].Gain_X;
		CorTemp[CompCunt].Phase_Y = CompareTree[CompCunt].Phase_Y;
		CorTemp[CompCunt].Value = CompareTree[CompCunt].Value;
	}

	//PntReg is reg to change; FlucPot is change value
	if(PotReg == R842_IMR_GAIN_REG)
		PntReg = R842_IMR_PHASE_REG; //phase control
	else
		PntReg = R842_IMR_GAIN_REG; //gain control

	for(TreeCunt = 0; TreeCunt<TreeTimes; TreeCunt ++)
	{
		R842_I2C.RegAddr = PotReg;
		R842_I2C.Data = FixPot;
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_I2C.RegAddr = PntReg;
		R842_I2C.Data = FlucPot;
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		if(R842_Muti_Read(&CorTemp[TreeCunt].Value) != R842_Success)
			return R842_Fail;
	
		if(PotReg == R842_IMR_GAIN_REG)
		{
			CorTemp[TreeCunt].Gain_X  = FixPot;
			CorTemp[TreeCunt].Phase_Y = FlucPot;
		}
		else
		{
			CorTemp[TreeCunt].Phase_Y  = FixPot;
			CorTemp[TreeCunt].Gain_X = FlucPot;
		}
		
		if(TreeCunt == 0)   //next try right-side 1 point
			FlucPot ++;     //+1
		else if(TreeCunt == 1)   //next try right-side 2 point
			FlucPot ++;     //1+1=2
		else if(TreeCunt == 2)   //next try left-side 1 point
		{
			if((FlucPot & 0x0F) == 0x02) //if absolute location is 2, change I/Q direction and set to 1
			{
				TempPot = 1;
				if((FlucPot & 0x10)==0x10) //b[4]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;  //Q1
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;  //I1
				}
			}
			else
				FlucPot -= 3;  //+2-3=-1
		}
		else if(TreeCunt == 3) //next try left-side 2 point
		{
			if(TempPot==1)  //been chnaged I/Q
			{
				FlucPot += 1;
			}
			else if((FlucPot & 0x0F) == 0x00) //if absolute location is 0, change I/Q direction
			{
				TempPot = 1;
				if((FlucPot & 0x10)==0x10) //b[4]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;  //Q1
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;  //I1
				}
			}
			else
				FlucPot -= 1;  //-1-1=-2
		}

		if(CorTemp[TreeCunt].Value < Compare_Temp.Value)
		{
		  Compare_Temp.Value = CorTemp[TreeCunt].Value;
		  Compare_Temp.Gain_X = CorTemp[TreeCunt].Gain_X;
		  Compare_Temp.Phase_Y = CorTemp[TreeCunt].Phase_Y;		
		  CuntTemp = TreeCunt; 
		}
/*
		if(TreeCunt == 0)   //try right-side point
			FlucPot ++; 
		else if(TreeCunt == 1) //try left-side point
		{
			if((FlucPot & 0x0F) == 1) //if absolute location is 1, change I/Q direction
			{
				if(FlucPot & 0x10) //b[4]:I/Q selection. 0:Q-path, 1:I-path
				{
					FlucPot = (FlucPot & 0xE0) | 0x01;			
				}
				else
				{
					FlucPot = (FlucPot & 0xE0) | 0x11;
				}
			}
			else
				FlucPot = FlucPot - 2;  
				
		}
*/
	}

	for(CompCunt=0; CompCunt<3; CompCunt++)
	{
		if(CuntTemp==3 || CuntTemp==4)
		{
			CompareTree[CompCunt].Gain_X = CorTemp[2+CompCunt].Gain_X;  //2,3,4
			CompareTree[CompCunt].Phase_Y = CorTemp[2+CompCunt].Phase_Y;
			CompareTree[CompCunt].Value = CorTemp[2+CompCunt].Value;
		}
		else
		{
			CompareTree[CompCunt].Gain_X = CorTemp[CompCunt].Gain_X;    //0,1,2
			CompareTree[CompCunt].Phase_Y = CorTemp[CompCunt].Phase_Y;
			CompareTree[CompCunt].Value = CorTemp[CompCunt].Value;
		}
		
	}

	return R842_Success;
}




//-----------------------------------------------------------------------------------/ 
// Purpose: compare IMR result aray [0][1][2], find min value and store to CorArry[0]
// input: CorArry: three IMR data array
// output: TRUE or FALSE
//-----------------------------------------------------------------------------------/
R842_ErrCode R842_CompreCor(R842_Sect_Type* CorArry)
{
	UINT8 CompCunt = 0;
	R842_Sect_Type CorTemp;

	for(CompCunt=3; CompCunt > 0; CompCunt --)
	{
		if(CorArry[0].Value > CorArry[CompCunt - 1].Value) //compare IMR result [0][1][2], find min value
		{
			CorTemp = CorArry[0];
			CorArry[0] = CorArry[CompCunt - 1];
			CorArry[CompCunt - 1] = CorTemp;
		}
	}

	return R842_Success;
}


//-------------------------------------------------------------------------------------//
// Purpose: if (Gain<9 or Phase<9), Gain+1 or Phase+1 and compare with min value
//          new < min => update to min and continue
//          new > min => Exit
// input: StepArry: three IMR data array
//        Pace: gain or phase register
// output: TRUE or FALSE 
//-------------------------------------------------------------------------------------//
R842_ErrCode R842_CompreStep(R842_Sect_Type* StepArry, UINT8 Pace)
{
	R842_Sect_Type StepTemp;
	
	//min value already saved in StepArry[0]
	StepTemp.Phase_Y = StepArry[0].Phase_Y;  //whole byte data
	StepTemp.Gain_X = StepArry[0].Gain_X;
	//StepTemp.Iqcap  = StepArry[0].Iqcap;

	while(((StepTemp.Gain_X & 0x0F) < R842_IMR_TRIAL) && ((StepTemp.Phase_Y & 0x0F) < R842_IMR_TRIAL))  
	{
		if(Pace == R842_IMR_GAIN_REG)
			StepTemp.Gain_X ++;
		else
			StepTemp.Phase_Y ++;
	
		R842_I2C.RegAddr = R842_IMR_GAIN_REG;
		R842_I2C.Data = StepTemp.Gain_X ;
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_I2C.RegAddr = R842_IMR_PHASE_REG;
		R842_I2C.Data = StepTemp.Phase_Y;
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		if(R842_Muti_Read(&StepTemp.Value) != R842_Success)
			return R842_Fail;

		if(StepTemp.Value <= StepArry[0].Value)
		{
			StepArry[0].Gain_X  = StepTemp.Gain_X;
			StepArry[0].Phase_Y = StepTemp.Phase_Y;
			//StepArry[0].Iqcap = StepTemp.Iqcap;
			StepArry[0].Value   = StepTemp.Value;
		}
		else if((StepTemp.Value - 2*R842_ADC_READ_COUNT) > StepArry[0].Value)
		{
			break;		
		}
		
	} //end of while()
	
	return R842_Success;
}


//-----------------------------------------------------------------------------------/ 
// Purpose: read multiple IMR results for stability
// input: IMR_Reg: IMR result address
//        IMR_Result_Data: result 
// output: TRUE or FALSE
//-----------------------------------------------------------------------------------/
R842_ErrCode R842_Muti_Read(UINT8* IMR_Result_Data) //ok
{
    R842_Delay_MS(R842_ADC_READ_DELAY);//2

	R842_I2C_Len.RegAddr = 0;
	R842_I2C_Len.Len = 2;              // read 0x01
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
	{
		R842_I2C_Read_Len(&R842_I2C_Len);
	}

	*IMR_Result_Data = (R842_I2C_Len.Data[1] & 0x3F);

	return R842_Success;
}

 
R842_ErrCode R842_Section(R842_Sect_Type* IQ_Pont)
{
	R842_Sect_Type Compare_IQ[3];
	R842_Sect_Type Compare_Bet[3];

	//Try X-1 column and save min result to Compare_Bet[0]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)
	{
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) & 0xEF) + 1;  //Q-path, Gain=1
	}
	else
	{
		Compare_IQ[0].Gain_X  = IQ_Pont->Gain_X - 1;  //left point
	}
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success)  // y-direction
		return R842_Fail;

	if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	Compare_Bet[0].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[0].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[0].Value = Compare_IQ[0].Value;

	//Try X column and save min result to Compare_Bet[1]
	Compare_IQ[0].Gain_X = IQ_Pont->Gain_X;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	Compare_Bet[1].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[1].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[1].Value = Compare_IQ[0].Value;

	//Try X+1 column and save min result to Compare_Bet[2]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)		
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) | 0x10) + 1;  //I-path, Gain=1
	else
	    Compare_IQ[0].Gain_X = IQ_Pont->Gain_X + 1;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	Compare_Bet[2].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[2].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[2].Value = Compare_IQ[0].Value;

	if(R842_CompreCor(&Compare_Bet[0]) != R842_Success)
		return R842_Fail;

	*IQ_Pont = Compare_Bet[0];
	
	return R842_Success;
}


R842_ErrCode R842_IMR_Cross(R842_Sect_Type* IQ_Pont, UINT8* X_Direct)
{

	R842_Sect_Type Compare_Cross[9]; //(0,0)(0,Q-1)(0,I-1)(Q-1,0)(I-1,0)+(0,Q-2)(0,I-2)(Q-2,0)(I-2,0)
	R842_Sect_Type Compare_Temp;
	UINT8 CrossCount = 0;
	UINT8 RegGain = R842_Array[R842_IMR_GAIN_REG] & 0xE0;
	UINT8 RegPhase = R842_Array[R842_IMR_PHASE_REG] & 0xE0;

	Compare_Temp.Gain_X = 0;
	Compare_Temp.Phase_Y = 0;
	Compare_Temp.Iqcap = 0;
	Compare_Temp.Value = 255;

	for(CrossCount=0; CrossCount<9; CrossCount++)
	{

		if(CrossCount==0)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==1)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;       //0
		  Compare_Cross[CrossCount].Phase_Y = RegPhase + 1;  //Q-1
		}
		else if(CrossCount==2)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;               //0
		  Compare_Cross[CrossCount].Phase_Y = (RegPhase | 0x10) + 1; //I-1
		}
		else if(CrossCount==3)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain + 1; //Q-1
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==4)
		{
		  Compare_Cross[CrossCount].Gain_X = (RegGain | 0x10) + 1; //I-1
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==5)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;       //0
		  Compare_Cross[CrossCount].Phase_Y = RegPhase + 2;  //Q-2
		}
		else if(CrossCount==6)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain;               //0
		  Compare_Cross[CrossCount].Phase_Y = (RegPhase | 0x10) + 2; //I-2
		}
		else if(CrossCount==7)
		{
		  Compare_Cross[CrossCount].Gain_X = RegGain + 2; //Q-2
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}
		else if(CrossCount==8)
		{
		  Compare_Cross[CrossCount].Gain_X = (RegGain | 0x10) + 2; //I-2
		  Compare_Cross[CrossCount].Phase_Y = RegPhase;
		}

    	R842_I2C.RegAddr = R842_IMR_GAIN_REG;
	    R842_I2C.Data = Compare_Cross[CrossCount].Gain_X;
	    if(R842_I2C_Write(&R842_I2C) != R842_Success)
		   return R842_Fail;

	    R842_I2C.RegAddr = R842_IMR_PHASE_REG;
	    R842_I2C.Data = Compare_Cross[CrossCount].Phase_Y;
	    if(R842_I2C_Write(&R842_I2C) != R842_Success)
		  return R842_Fail;
	
        if(R842_Muti_Read(&Compare_Cross[CrossCount].Value) != R842_Success)
		  return R842_Fail;

		if( Compare_Cross[CrossCount].Value < Compare_Temp.Value)
		{
		  Compare_Temp.Value = Compare_Cross[CrossCount].Value;
		  Compare_Temp.Gain_X = Compare_Cross[CrossCount].Gain_X;
		  Compare_Temp.Phase_Y = Compare_Cross[CrossCount].Phase_Y;		
		}
	} //end for loop


    if(((Compare_Temp.Phase_Y & 0x1F)==0x01) || (Compare_Temp.Phase_Y & 0x1F)==0x02)  //phase Q1 or Q2
	{
      *X_Direct = (UINT8) 0;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[1].Gain_X;    //0
	  IQ_Pont[1].Phase_Y = Compare_Cross[1].Phase_Y; //Q1
	  IQ_Pont[1].Value = Compare_Cross[1].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[5].Gain_X;   //0
	  IQ_Pont[2].Phase_Y = Compare_Cross[5].Phase_Y;//Q2
	  IQ_Pont[2].Value = Compare_Cross[5].Value;
	}
	else if(((Compare_Temp.Phase_Y & 0x1F)==0x11) || (Compare_Temp.Phase_Y & 0x1F)==0x12)  //phase I1 or I2
	{
      *X_Direct = (UINT8) 0;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[2].Gain_X;    //0
	  IQ_Pont[1].Phase_Y = Compare_Cross[2].Phase_Y; //Q1
	  IQ_Pont[1].Value = Compare_Cross[2].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[6].Gain_X;   //0
	  IQ_Pont[2].Phase_Y = Compare_Cross[6].Phase_Y;//Q2
	  IQ_Pont[2].Value = Compare_Cross[6].Value;
	}
	else if(((Compare_Temp.Gain_X & 0x1F)==0x01) || (Compare_Temp.Gain_X & 0x1F)==0x02)  //gain Q1 or Q2
	{
      *X_Direct = (UINT8) 1;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[3].Gain_X;    //Q1
	  IQ_Pont[1].Phase_Y = Compare_Cross[3].Phase_Y; //0
	  IQ_Pont[1].Value = Compare_Cross[3].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[7].Gain_X;   //Q2
	  IQ_Pont[2].Phase_Y = Compare_Cross[7].Phase_Y;//0
	  IQ_Pont[2].Value = Compare_Cross[7].Value;
	}
	else if(((Compare_Temp.Gain_X & 0x1F)==0x11) || (Compare_Temp.Gain_X & 0x1F)==0x12)  //gain I1 or I2
	{
      *X_Direct = (UINT8) 1;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;    //0
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y; //0
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[4].Gain_X;    //I1
	  IQ_Pont[1].Phase_Y = Compare_Cross[4].Phase_Y; //0
	  IQ_Pont[1].Value = Compare_Cross[4].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[8].Gain_X;   //I2
	  IQ_Pont[2].Phase_Y = Compare_Cross[8].Phase_Y;//0
	  IQ_Pont[2].Value = Compare_Cross[8].Value;
	}
	else //(0,0) 
	{	
	  *X_Direct = (UINT8) 1;
	  IQ_Pont[0].Gain_X = Compare_Cross[0].Gain_X;
	  IQ_Pont[0].Phase_Y = Compare_Cross[0].Phase_Y;
	  IQ_Pont[0].Value = Compare_Cross[0].Value;

	  IQ_Pont[1].Gain_X = Compare_Cross[3].Gain_X;    //Q1
	  IQ_Pont[1].Phase_Y = Compare_Cross[3].Phase_Y; //0
	  IQ_Pont[1].Value = Compare_Cross[3].Value;

	  IQ_Pont[2].Gain_X = Compare_Cross[4].Gain_X;   //I1
	  IQ_Pont[2].Phase_Y = Compare_Cross[4].Phase_Y; //0
	  IQ_Pont[2].Value = Compare_Cross[4].Value;
	}
	return R842_Success;
}


//----------------------------------------------------------------------------------------//
// purpose: search surrounding points from previous point 
//          try (x-1), (x), (x+1) columns, and find min IMR result point
// input: IQ_Pont: previous point data(IMR Gain, Phase, ADC Result, RefRreq)
//                 will be updated to final best point                 
// output: TRUE or FALSE
//----------------------------------------------------------------------------------------//
R842_ErrCode R842_F_IMR(R842_Sect_Type* IQ_Pont)
{
	R842_Sect_Type Compare_IQ[3];
	R842_Sect_Type Compare_Bet[3];

	 //------- increase Filter gain to let ADC read value significant ---------//
	UINT8   LPF_Count = 0;
	UINT8   ADC_Read_Value = 0;

	 for(LPF_Count=6; LPF_Count < 16; LPF_Count=LPF_Count+3)  //start from 6
	 {
		R842_I2C.RegAddr = 41;
		R842_Array[41] = (R842_Array[41] & 0x0F) | (LPF_Count<<4);
		R842_I2C.Data = R842_Array[41];  
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_Delay_MS(R842_FILTER_GAIN_DELAY); //
		
		if(R842_Muti_Read(&ADC_Read_Value) != R842_Success)
			return R842_Fail;

		if(ADC_Read_Value > 40*R842_ADC_READ_COUNT)
			break;
	 }
/*
	//Filter Gain 15
	R842_I2C.RegAddr = 41;
	R842_Array[41] = (R842_Array[41] & 0x0F) | (15<<4);
	R842_I2C.Data = R842_Array[41];  
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
*/
	//Try X-1 column and save min result to Compare_Bet[0]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)
	{
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) & 0xEF) + 1;  //Q-path, Gain=1
	}
	else
	{
		Compare_IQ[0].Gain_X  = IQ_Pont->Gain_X - 1;  //left point
	}
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success)  // y-direction
		return R842_Fail;

	if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	Compare_Bet[0].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[0].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[0].Value = Compare_IQ[0].Value;

	//Try X column and save min result to Compare_Bet[1]
	Compare_IQ[0].Gain_X = IQ_Pont->Gain_X;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	Compare_Bet[1].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[1].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[1].Value = Compare_IQ[0].Value;

	//Try X+1 column and save min result to Compare_Bet[2]
	if((IQ_Pont->Gain_X & 0x0F) == 0x00)		
		Compare_IQ[0].Gain_X = ((IQ_Pont->Gain_X) | 0x10) + 1;  //I-path, Gain=1
	else
	    Compare_IQ[0].Gain_X = IQ_Pont->Gain_X + 1;
	Compare_IQ[0].Phase_Y = IQ_Pont->Phase_Y;

	if(R842_IQ_Tree(Compare_IQ[0].Gain_X, Compare_IQ[0].Phase_Y, R842_IMR_GAIN_REG, &Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	if(R842_CompreCor(&Compare_IQ[0]) != R842_Success)
		return R842_Fail;

	Compare_Bet[2].Gain_X = Compare_IQ[0].Gain_X;
	Compare_Bet[2].Phase_Y = Compare_IQ[0].Phase_Y;
	Compare_Bet[2].Value = Compare_IQ[0].Value;

	if(R842_CompreCor(&Compare_Bet[0]) != R842_Success)
		return R842_Fail;

	//clear IQ_Cap = 0
	//Compare_Bet[0].Iqcap = R842_Array[3] & 0xFC;
	Compare_Bet[0].Iqcap = 0;

	if(R842_IMR_Iqcap(&Compare_Bet[0]) != R842_Success)
		return R842_Fail;

	*IQ_Pont = Compare_Bet[0];
	
	return R842_Success;
}


R842_ErrCode R842_IMR_Iqcap(R842_Sect_Type* IQ_Point)   
{
    R842_Sect_Type Compare_Temp;
	int i = 0;

	//Set Gain/Phase to right setting
	R842_I2C.RegAddr = R842_IMR_GAIN_REG;
	R842_I2C.Data = IQ_Point->Gain_X; 
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = R842_IMR_PHASE_REG;
	R842_I2C.Data = IQ_Point->Phase_Y;
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//try iqcap
	for(i=0; i<3; i++)
	{
		Compare_Temp.Iqcap = (UINT8) i;  
		R842_I2C.RegAddr = R842_IMR_IQCAP_REG;
		R842_Array[R842_IMR_IQCAP_REG] = (R842_Array[R842_IMR_IQCAP_REG] & 0x3F) | (Compare_Temp.Iqcap<<6);  
		R842_I2C.Data = R842_Array[R842_IMR_IQCAP_REG];  
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			   return R842_Fail;

		if(R842_Muti_Read(&(Compare_Temp.Value)) != R842_Success)
			   return R842_Fail;

		if(Compare_Temp.Value < IQ_Point->Value)
		{
			IQ_Point->Value = Compare_Temp.Value; 
			IQ_Point->Iqcap = Compare_Temp.Iqcap;  //0, 1, 2
		}
	}

    return R842_Success;
}




R842_ErrCode R842_SetStandard(R842_Standard_Type RT_Standard)
{	 
	UINT8 u1FilCalGap = R842_Fil_Cal_Gap;

if(R842_ATV_IF==R842_NORMAL)
	R842_Sys_Info1 = R842_Sys_Sel(RT_Standard);
else if((R842_ATV_IF==R842_8296) && (RT_Standard<R842_ATV_SIZE))
    R842_Sys_Info1 = R842_Sys_Sel_8296(RT_Standard);  //not release, LGIT?
else
    R842_Sys_Info1 = R842_Sys_Sel(RT_Standard);

	// Filter Calibration	
    if(R842_Fil_Cal_flag[RT_Standard] == FALSE)
	{
		R842_Fil_Cal_code[RT_Standard] = R842_Filt_Cal_ADC(R842_Sys_Info1.FILT_CAL_IF, R842_Sys_Info1.BW, u1FilCalGap);
		R842_Fil_Cal_BW[RT_Standard] = R842_Bandwidth;
        R842_Fil_Cal_flag[RT_Standard] = TRUE;
        R842_Fil_Cal_LpfLsb[RT_Standard] = R842_Lpf_Lsb;  

		//protection
		if(R842_IMR_Cal_Result==1) //fail
		{
			if((R842_Fil_Cal_BW[RT_Standard]==3) && (R842_Fil_Cal_code[RT_Standard]==15))  //6M/15
			{
				R842_Fil_Cal_BW[RT_Standard] = R842_Fil_Cal_BW_def[RT_Standard];
				R842_Fil_Cal_code[RT_Standard] = (R842_Fil_Cal_code_def[RT_Standard]>>1);
				R842_Fil_Cal_LpfLsb[RT_Standard] = (R842_Fil_Cal_code_def[RT_Standard] & 0x01);
			}
		}

	    //Reset register and Array 
	    if(R842_InitReg() != R842_Success)        
		   return R842_Fail;
	}

	//HPF ext protection
	if(R842_Sys_Info1.FILT_EXT_ENA==1)
	{
		if(R842_Sys_Info1.HPF_EXT_SEL==1) //+3
		{
			if(R842_Sys_Info1.HPF_COR>12)  
			{    R842_Sys_Info1.HPF_COR = 12; }
		}
		else  //+1
		{
			if(R842_Sys_Info1.HPF_COR>14)  
			{    R842_Sys_Info1.HPF_COR = 15; }
		}
	}

	//Re-set Registers when change standard
	if(RT_Standard != R842_pre_standard)
	{
		 if(R842_InitReg() != R842_Success)      
		     return R842_Fail;

		// Set Filter_Ext_Ena(bit1); Ext_cond(bit6:5); HPF_ext_sel(bit7); 5th Filter Manual Comp(bit4)
		R842_I2C.RegAddr = 23;
		R842_Array[23] = (R842_Array[23] & 0x0D) | (R842_Sys_Info1.HPF_EXT_SEL<<7) | (R842_Sys_Info1.FILT_EXT_POINT<<5) | (R842_Sys_Info1.FILT5_MAN_COMP<<4) | (R842_Sys_Info1.FILT_EXT_ENA<<1);
		R842_I2C.Data = R842_Array[23];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// Set HPF notch 
		R842_I2C.RegAddr = 21;
		R842_Array[21] = (R842_Array[21] & 0x7F) | (R842_Sys_Info1.HPF_NOTCH<<7);  
		R842_I2C.Data = R842_Array[21];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// Set LPF coarse BW(R22[6:5]), LPF fine code(R22[4:1]), Lsb bit(R22[0])
		R842_I2C.RegAddr = 22;
		R842_Array[22] = (R842_Array[22] & 0x80) | (R842_Fil_Cal_BW[RT_Standard]<<5) | (R842_Fil_Cal_code[RT_Standard]<<1) | (R842_Fil_Cal_LpfLsb[RT_Standard]);
		R842_I2C.Data = R842_Array[22];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// Set HPF corner 
		R842_I2C.RegAddr = 24;
		R842_Array[24] = (R842_Array[24] & 0xF0) | R842_Sys_Info1.HPF_COR;
		R842_I2C.Data = R842_Array[24];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// Set NA det power
		R842_I2C.RegAddr = 8;
		R842_Array[8] = (R842_Array[8] & 0xFB) | (R842_Sys_Info1.NA_PWR_DET<<2); 
		R842_I2C.Data = R842_Array[8];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// Set AGC RF LTE PS Gain
		R842_I2C.RegAddr = 17;
		R842_Array[17] = (R842_Array[17] & 0xEF) | (R842_Sys_Info1.RF_LTE_PSG<<4); 
		R842_I2C.Data = R842_Array[17];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// Polyphase current(R10[2]); LPF Current(R10[4:3])
		R842_I2C.RegAddr = 10;
		R842_Array[10] = (R842_Array[10] & 0xE3) | (R842_Sys_Info1.POLY_CUR<<2) | (R842_Sys_Info1.LPF_CUR<<3); 
		R842_I2C.Data = R842_Array[10];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;	

		// 5th Filter Auto Comp
		R842_I2C.RegAddr = 18;
		R842_Array[18] = (R842_Array[18] & 0x9F) | (R842_Sys_Info1.FILT5_AUTO_COMP<<5); 
		R842_I2C.Data = R842_Array[18];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// 5th Filter Force Q(bit7); Det LPF Auto(bit2); 3th Filter Comp(bit4:3)
		R842_I2C.RegAddr = 36;
		R842_Array[36] = (R842_Array[36] & 0x63) | (R842_Sys_Info1.FILT5_FORCEQ<<7) | (R842_Sys_Info1.FILT3_COMP<<3) | (R842_Sys_Info1.DET_LPF_AUTO<<2); 
		R842_I2C.Data = R842_Array[36];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		// RF AGC ctrl
		R842_I2C.RegAddr = 37;
		R842_Array[37] = (R842_Array[37] & 0x7F) | (R842_Sys_Info1.RFAGC_CTRL<<7); 
		R842_I2C.Data = R842_Array[37];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;
	}
    R842_pre_standard = RT_Standard;

	return R842_Success;
}


UINT8  R842_Filt_Cal_ADC(UINT32 IF_Freq, UINT8 R842_BW, UINT8 FilCal_Gap)
{
	UINT8     u1FilterCodeResult = 0;
	UINT8     u1FilterCode = 0;
	UINT8     u1FilterCalValue = 0;
	UINT8     u1FilterCalValuePre = 0;
	UINT8     initial_cnt = 0;
	UINT8     i = 0;
	UINT32    RingFreq = 72000;
	UINT8     ADC_Read_Value = 0;
	UINT8     LPF_Count = 0;

	
	 if(R842_Cal_Prepare(R842_LPF_CAL) != R842_Success)      
	      return R842_Fail;

	 //Set PLL (normal)
	 if(R842_PLL((RingFreq + IF_Freq), (UINT16)IF_Freq, R842_STD_SIZE) != R842_Success)   //FilCal PLL
	       return R842_Fail;

	 for(LPF_Count=5; LPF_Count < 16; LPF_Count ++)  //start from 5
	 {
		R842_I2C.RegAddr = 41;
		R842_Array[41] = (R842_Array[41] & 0x0F) | (LPF_Count<<4);
		R842_I2C.Data = R842_Array[41];  
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

		R842_Delay_MS(R842_FILTER_GAIN_DELAY); //
		
		if(R842_Muti_Read(&ADC_Read_Value) != R842_Success)
			return R842_Fail;

		if(ADC_Read_Value > 40*R842_ADC_READ_COUNT)
			break;
	 }

	 //------- Try suitable BW --------//
	 if(R842_BW==2) //6M
         initial_cnt = 1;  //try 7M first
	 else
		 initial_cnt = 0;  //try 8M first

	 for(i=initial_cnt; i<3; i++)
	 {
         if(i==0)
             R842_Bandwidth = 0; //8M
		 else if(i==1)
			 R842_Bandwidth = 2; //7M
		 else
			 R842_Bandwidth = 3; //6M, (not 2!!!!!)

		 //Set BW
		 R842_I2C.RegAddr = 22;	
		 R842_Array[22] = (R842_Array[22] & 0x9F) | (R842_Bandwidth<<5);   
		 R842_I2C.Data = R842_Array[22];		
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;	

		 // read code 0
		 R842_I2C.RegAddr = 22;
		 R842_Array[22] = (R842_Array[22] & 0xE1);  //code 0
		 R842_I2C.Data = R842_Array[22];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			  return R842_Fail;

		 R842_Delay_MS(R842_FILTER_CODE_DELAY); //delay ms
	     
		 if(R842_Muti_Read(&u1FilterCalValuePre) != R842_Success)
			  return R842_Fail;

		 //read code 13
		 R842_I2C.RegAddr = 22;
		 R842_Array[22] = (R842_Array[22] & 0xE1) | (13<<1);  //code 13
		 R842_I2C.Data = R842_Array[22];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			  return R842_Fail;

		 R842_Delay_MS(R842_FILTER_CODE_DELAY); //delay ms
	     
		 if(R842_Muti_Read(&u1FilterCalValue) != R842_Success)
			  return R842_Fail;

		 if(u1FilterCalValuePre > (u1FilterCalValue+8))  //suitable BW found
			 break;
	 }

     //-------- Try LPF filter code ---------//
	 u1FilterCalValuePre = 0;
	 for(u1FilterCode=0; u1FilterCode<16; u1FilterCode++)
	 {
         R842_I2C.RegAddr = 22;
         R842_Array[22] = (R842_Array[22] & 0xE1) | (u1FilterCode<<1);
         R842_I2C.Data = R842_Array[22];
         if(R842_I2C_Write(&R842_I2C) != R842_Success)
              return R842_Fail;

		 R842_Delay_MS(R842_FILTER_CODE_DELAY); //delay ms

		 if(R842_Muti_Read(&u1FilterCalValue) != R842_Success)
		      return R842_Fail;

		 if(u1FilterCode==0)
              u1FilterCalValuePre = u1FilterCalValue;

		 if((u1FilterCalValue+FilCal_Gap*R842_ADC_READ_COUNT) < u1FilterCalValuePre)
		 {
			 u1FilterCodeResult = u1FilterCode;
			  break;
		 }
	 }

     //Try LSB bit
	 if(u1FilterCodeResult>0)   //try code-1 & lsb=1
	 {		 
		 R842_I2C.RegAddr = 22;
         R842_Array[22] = (R842_Array[22] & 0xE0) | ((u1FilterCodeResult-1)<<1) | 0x01;
         R842_I2C.Data = R842_Array[22];
         if(R842_I2C_Write(&R842_I2C) != R842_Success)
              return R842_Fail;

		 R842_Delay_MS(R842_FILTER_CODE_DELAY); //delay ms

		 if(R842_Muti_Read(&u1FilterCalValue) != R842_Success)
			  return R842_Fail;

		 if((u1FilterCalValue+FilCal_Gap*R842_ADC_READ_COUNT) < u1FilterCalValuePre)
		 {
			 u1FilterCodeResult = u1FilterCodeResult - 1;
			 R842_Lpf_Lsb = 1;
		 }
		 else
		 {
		 	 //u1FilterCodeResult = u1FilterCodeResult;
			 R842_Lpf_Lsb = 0;
		 }
	 }
     
	 if(u1FilterCode==16)
	 {
          u1FilterCodeResult = 15;
		  R842_Lpf_Lsb = 1;
	 }

	  return u1FilterCodeResult;

}

R842_ErrCode R842_SetFrequency(R842_Set_Info R842_INFO)
{

	 UINT32	  LO_KHz;
	 UINT8    Img_R;
	 UINT8    i = 0;
	 UINT8    vco_bank_read = 0;

	 //Get Sys-Freq parameter
     R842_SysFreq_Info1 = R842_SysFreq_Sel(R842_INFO.R842_Standard, R842_INFO.RF_KHz);

	 R842_IMR_point_num = R842_Freq_Info1.IMR_MEM_NOR;

	 //AGC Ctrl (clk,R842_DTV_AGC_SLOW=FALSE; ctrl_by_slow)
	 //AGC Ctrl reset
	 R842_I2C.RegAddr = 46;
	 R842_Array[46] = (R842_Array[46] | 0x40);
	 R842_I2C.Data = R842_Array[46];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		 return R842_Fail;

     // Check Input Frequency Range
	 if((R842_INFO.RF_KHz<40000) || (R842_INFO.RF_KHz>1002000))
	 {
		 return R842_Fail;
	 }	 

	 if(R842_Mixer_Mode==R842_IMR_REV)
	 {
		 LO_KHz = R842_INFO.RF_KHz - R842_Sys_Info1.IF_KHz;
		 Img_R = 1;
	 }
	 else
	 {
		 LO_KHz = R842_INFO.RF_KHz + R842_Sys_Info1.IF_KHz;
		 Img_R = 0;
	 }
	  R842_I2C.RegAddr = 20;
	  R842_Array[20] = (R842_Array[20] & 0x7F) | (Img_R<<7);  //R20[7]
	  R842_I2C.Data = R842_Array[20];
	  if(R842_I2C_Write(&R842_I2C) != R842_Success)
		 return R842_Fail;

	 //Set MUX dependent var. Must do before PLL( ) 
     if(R842_MUX(LO_KHz, R842_INFO.RF_KHz, R842_INFO.R842_Standard) != R842_Success)   //normal MUX
        return R842_Fail;

     //Set PLL
     if(R842_PLL(LO_KHz, R842_Sys_Info1.IF_KHz, R842_INFO.R842_Standard) != R842_Success) //noraml PLL
        return R842_Fail;

	 //Set TF
	 if(R842_SetTF(R842_INFO.RF_KHz, R842_SetTfType) != R842_Success)
		return R842_Fail;

	 // LNA TF Q-Ctrl (depend on RF_KHz)
	 R842_Array[14] = (R842_Array[14] & 0x7F) | (R842_SysFreq_Info1.Q_CTRL<<7);  //R14[7]

     // LNA_TOP
     R842_Array[37] = (R842_Array[37] & 0xF0) | (15 - R842_SysFreq_Info1.LNA_TOP);

	 // LNA VTL/H
     R842_Array[38] = (R842_Array[38] & 0x00) | R842_SysFreq_Info1.LNA_VTL_H;

	 // RF TOP
	 R842_Array[37] = (R842_Array[37] & 0x8F) | ((7 - R842_SysFreq_Info1.RF_TOP)<<4);

	 // RF VTL/H
	 R842_Array[39] = (R842_Array[39] & 0x00) | R842_SysFreq_Info1.RF_VTL_H;

	 // RF Gain Limt
	 R842_Array[45] = (R842_Array[45] & 0x3F) | R842_SysFreq_Info1.RF_GAIN_LIMIT;

     // MIXER TOP
     R842_Array[40] = (R842_Array[40] & 0xF0) | (15 - R842_SysFreq_Info1.MIXER_TOP); 

     // MIXER VTH & Filter VTH
	 R842_Array[41] = (R842_Array[41] & 0x00) | R842_SysFreq_Info1.MIXER_VTH | (R842_SysFreq_Info1.FILTER_VTH);

     // MIXER VTL & Filter VTL
     R842_Array[43] = (R842_Array[43] & 0x00) | R842_SysFreq_Info1.MIXER_VTL | (R842_SysFreq_Info1.FILTER_VTL);

     // HYS_MIXER TOP	 
	 R842_Array[30] = (R842_Array[30] & 0xF3) | (R842_SysFreq_Info1.HYS_MIXTOP<<2); 

	 // Filter TOP
	 R842_Array[42] = (R842_Array[42] & 0x0F) | ((15-R842_SysFreq_Info1.FILTER_TOP)<<4);

	 // Mixer Gain Limt
	 R842_Array[20] = (R842_Array[20] & 0x9F) | R842_SysFreq_Info1.MIXER_GAIN_LIMIT;

	 // NRB TOP
	 R842_Array[40] = (R842_Array[40] & 0x0F) | ((15 - R842_SysFreq_Info1.NRB_TOP)<<4);

	 // NRB HPF & LPF BW
	 R842_Array[42] = (R842_Array[42] & 0xF0) | R842_SysFreq_Info1.NRB_BW_HPF | R842_SysFreq_Info1.NRB_BW_LPF;

	 //LNA slow disch(1:0) / fast disch(3:2)
	 R842_Array[44] = (R842_Array[44] & 0xF0) | R842_SysFreq_Info1.LNA_DIS_SLOW_FAST;  

	 //BB Det Mode
	 R842_Array[47] = (R842_Array[47] & 0x7F) | R842_SysFreq_Info1.BB_DET_MODE;  

	 //NBR Image TOP adder
	 R842_Array[45] = (R842_Array[45] & 0xF3) | R842_SysFreq_Info1.IMG_NRB_ADDER;  

	 //LNA_RF Discharge Mode
	 if(R842_SysFreq_Info1.LNA_RF_DIS_MODE==0)  //auto
	 {
	     R842_Array[45] = (R842_Array[45] & 0xFC) | 0x01;   //01
		 R842_Array[9] = (R842_Array[9] & 0xBF) | 0x40;     //1
	 }
	 else if(R842_SysFreq_Info1.LNA_RF_DIS_MODE==1)  //both(fast+slow)
	 {
		 R842_Array[45] = (R842_Array[45] & 0xFC) | 0x03;   //11
		 R842_Array[9] = (R842_Array[9] & 0xBF) | 0x40;     //1
	 }
	 else if(R842_SysFreq_Info1.LNA_RF_DIS_MODE==2)  //both(slow)
	 {
		 R842_Array[45] = (R842_Array[45] & 0xFC) | 0x02;   //10
		 R842_Array[9] = (R842_Array[9] & 0xBF) | 0x00;     //0
	 }
	 else if(R842_SysFreq_Info1.LNA_RF_DIS_MODE==3)  //LNA(slow)
	 {
		 R842_Array[45] = (R842_Array[45] & 0xFC) | 0x03;   //11
		 R842_Array[9] = (R842_Array[9] & 0xBF) | 0x00;     //0
	 }
	 else if(R842_SysFreq_Info1.LNA_RF_DIS_MODE==4)  //RF(slow)
	 {
		 R842_Array[45] = (R842_Array[45] & 0xFC) | 0x02;   //10
		 R842_Array[9] = (R842_Array[9] & 0xBF) | 0x40;     //1
	 }
	 else
	 {
	 	 R842_Array[45] = (R842_Array[45] & 0xFC) | 0x01;   //01
		 R842_Array[9] = (R842_Array[9] & 0xBF) | 0x40;     //1
	 }

	 //LNA_RF_dis current
	 R842_Array[23] = (R842_Array[23] & 0xFE) | R842_SysFreq_Info1.LNA_RF_DIS_CURR;  

	 //LNA_RF charge
	 R842_Array[15] = (R842_Array[15] & 0xDF) | (R842_SysFreq_Info1.LNA_RF_CHARGE<<5);  

	 //RF_slow disch(5:4) / fast disch(7:6)
	 R842_Array[44] = (R842_Array[44] & 0x0F) | R842_SysFreq_Info1.RF_DIS_SLOW_FAST;  

	 //BB disch current
	 R842_Array[18] = (R842_Array[18] & 0xEF) | R842_SysFreq_Info1.BB_DIS_CURR;  

	 //Mixer/Filter disch 
	 R842_Array[30] = (R842_Array[30] & 0xFC) | R842_SysFreq_Info1.MIXER_FILTER_DIS;  

	 //Enable Poly Gain 
	 R842_Array[19] = (R842_Array[19] & 0xEF) | (R842_SysFreq_Info1.ENB_POLYG<<4);  

	 //VGA Pin level; delta; 
	 R842_Array[25] = (R842_Array[25] & 0xAF) | (R842_SysFreq_Info1.VGA_PIN_LVL<<4) | (R842_SysFreq_Info1.VGA_PIN_DEL<<6);  

	 //VGA Out att. 
	 R842_Array[17] = (R842_Array[17] & 0xFC) | (R842_SysFreq_Info1.VGA_OUT_ATT);  

	 //3th LPF gain (man)
	 R842_Array[24] = (R842_Array[24] & 0xBF) | (R842_SysFreq_Info1.FILT3_GAIN_MAN<<6);  

	// VGA HPF Comp
	R842_Array[21] = (R842_Array[21] & 0x9F) | (R842_SysFreq_Info1.HPF_COMP<<5); 

	// VGA 1st FB res
	R842_Array[33] = (R842_Array[33] & 0xBF) | (R842_SysFreq_Info1.FB1_RES<<6); 

	// Mixer Amp LPF
	R842_Array[19] = (R842_Array[19] & 0xF1) | (R842_SysFreq_Info1.MIXER_AMP_LPF<<1); 

	//Det BW LPF
	R842_Array[36] = (R842_Array[36] & 0xFD) | (R842_SysFreq_Info1.DET_BW_LPF<<1); 

	 //IF AGC 1/2
	 if(R842_INFO.R842_IfAgc_Select==R842_IF_AGC2)
         R842_Array[18] = R842_Array[18] | 0x01;
     else
         R842_Array[18] = R842_Array[18] & 0xFE;

	 //TF Mode
	 if(R842_SysFreq_Info1.TF_MODE==R842_TF_AUTO)
	 {
		 R842_Array[13] = (R842_Array[13] & 0x3F) | 0x00;  //TF auto
		 R842_Array[30] = (R842_Array[30] & 0xEF) | 0x00;  //auto
	 }
	 else if(R842_SysFreq_Info1.TF_MODE==R842_TF_PLAIN)
	 {
		 R842_Array[13] = (R842_Array[13] & 0x3F) | 0x40;  //TF plain
		 R842_Array[30] = (R842_Array[30] & 0xEF) | 0x00;  //auto
	 }
	 else if(R842_SysFreq_Info1.TF_MODE==R842_TF_SHARP)
	 {
		 R842_Array[13] = (R842_Array[13] & 0x3F) | 0xC0;  //TF sharp
		 R842_Array[30] = (R842_Array[30] & 0xEF) | 0x10;  //force sharp
	 }
	 else
	 {
		 R842_Array[13] = (R842_Array[13] & 0x3F) | 0x00;  //TF auto
		 R842_Array[30] = (R842_Array[30] & 0xEF) | 0x00;  //auto
	 }

	 //Set LNA enable atten.	
	 R842_Array[45] = (R842_Array[45] & 0xCF) | (R842_SysFreq_Info1.ENB_ATT<<4);

	//Write I2C R8~R47
	R842_I2C_Len.RegAddr = 8;
	R842_I2C_Len.Len = R842_REG_NUM - 8;
	for(i=8; i<R842_REG_NUM; i++)
	{
		R842_I2C_Len.Data[i-8] = R842_Array[i];	
	}	
	if(R842_I2C_Write_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;

	R842_I2C_Len.RegAddr = 0x00;
	R842_I2C_Len.Len = 3;
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;

	vco_bank_read = R842_I2C_Len.Data[2] & 0x3F;

	 if(R842_INFO.R842_Standard<R842_ATV_SIZE)  //ATV
	 {
		 R842_I2C.RegAddr = 8;		
		 R842_Array[8] = (R842_Array[8] & 0xBF) | 0x40; //R8[6]=1, ADC off
		 R842_I2C.Data = R842_Array[8];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;	
	 }
	 else
	 {
		 R842_I2C.RegAddr = 8;		
		 R842_Array[8] = (R842_Array[8] & 0xBF) | 0x00; //R8[6]=0, ADC on
		 R842_I2C.Data = R842_Array[8];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;	
	 }

#if(R842_FOR_LGIT == TRUE)

	//Set AGC clk 
	R842_I2C.RegAddr = 47;	
	R842_Array[47] = (R842_Array[47] & 0xF3) | 0x08;  //R47[3:2]=10 (4KHz)
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//swcap_clk
	R842_I2C.RegAddr = 47;
	R842_Array[47] = (R842_Array[47] & 0xCF) | 0x10;  //64kHz
	R842_I2C.Data = R842_Array[47];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
#endif

	 if(R842_INFO.R842_Standard<R842_ATV_SIZE)  //ATV
	 {
		 //LPF_Q enhance
		 if((R842_INFO.RF_KHz<183250) && (R842_INFO.RF_KHz>=179250)) 
			 R842_Array[15] = (R842_Array[15] & 0x7F);  //Q enhance
		 else
			 R842_Array[15] = (R842_Array[15] | 0x80);  //normal

		 R842_I2C.RegAddr = 15;			
		 R842_I2C.Data = R842_Array[15];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;	
		
		
#if(R842_FOR_LGIT==TRUE || R842_FOR_SEMCO_MODULE==TRUE)
			 if((R842_INFO.RF_KHz>42000) && (R842_INFO.RF_KHz<50000))	//48, +2/-6	 
			 {
				 if(R842_FOR_SEMCO_MODULE==TRUE)
				 {
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
				 }
				 else  //LGIT
				 {
	#if(R842_ATV_CIF_5M==TRUE)
					 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800) || (R842_INFO.R842_Standard==R842_MN_CIF_5M))
	#else
					 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800))
	#endif
						 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
					 else
						 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x1C;  //auto,111
				 }
			 }
			 else if((R842_INFO.RF_KHz>90000) && (R842_INFO.RF_KHz<98000))	//96, +2/-6	 		 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x08;  //0.5mA,010		
			 else if((R842_INFO.RF_KHz>138000) && (R842_INFO.RF_KHz<146000))	//144, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011	
			 else if((R842_INFO.RF_KHz>234000) && (R842_INFO.RF_KHz<242000))	//240, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011	
			 else if((R842_INFO.RF_KHz>258000) && (R842_INFO.RF_KHz<266000))	//264, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
			 else if((R842_INFO.RF_KHz>330000) && (R842_INFO.RF_KHz<338000))	//336, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,010
			 else if((R842_INFO.RF_KHz>354000) && (R842_INFO.RF_KHz<362000))	//360, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
			 else if((R842_INFO.RF_KHz>378000) && (R842_INFO.RF_KHz<386000))	//384, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000
			 else if((R842_INFO.RF_KHz>426000) && (R842_INFO.RF_KHz<434000))	//432, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
			 else if((R842_INFO.RF_KHz>450000) && (R842_INFO.RF_KHz<458000))	//456, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
			 else if((R842_INFO.RF_KHz>474000) && (R842_INFO.RF_KHz<482000))	//480, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
			 else if((R842_INFO.RF_KHz>498000) && (R842_INFO.RF_KHz<506000))	//504, +2/-6	 
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000
			 else if((R842_INFO.RF_KHz>522000) && (R842_INFO.RF_KHz<530000))	//528, +2/-6	 		 
			 {
	#if(R842_ATV_CIF_5M==TRUE)
				 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800) || (R842_INFO.R842_Standard==R842_MN_CIF_5M))
	#else
				 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800))
	#endif
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000				 
				 else
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101  			 
			 }
			 else if(R842_INFO.RF_KHz<482000)	 //480+2
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x1C;  //auto,111
			 else
				 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101	

			 //Xtal cap
			 if((R842_INFO.RF_KHz>42000) && (R842_INFO.RF_KHz<50000))	//48, +2/-6
			 {		
				 if(R842_FOR_SEMCO_MODULE==TRUE)
				 {
					 R842_SetXtalCap(15);
				 }
				 else  //LGIT
				 {
	#if(R842_ATV_CIF_5M==TRUE)
					 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800) || (R842_INFO.R842_Standard==R842_MN_CIF_5M))
	#else
					 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800))
	#endif
						 R842_SetXtalCap(26);
					 else
						 R842_SetXtalCap(13);
				 }
			 }
			 else if((R842_INFO.RF_KHz>66000) && (R842_INFO.RF_KHz<74000))	//72, +2/-6
			 {				 
				 if(R842_FOR_SEMCO_MODULE==TRUE)
					 R842_SetXtalCap(32);
				 else
					 R842_SetXtalCap(28);
			 }
			 else if((R842_INFO.RF_KHz>114000) && (R842_INFO.RF_KHz<122000))	//120, +2/-6
			 {
				 R842_SetXtalCap(36);		

				 //SDM on
				 R842_I2C.RegAddr = 29;
				 R842_Array[29] = (R842_Array[29] & 0xFC) | 0x00;  
				 R842_I2C.Data = R842_Array[29];
				 if(R842_I2C_Write(&R842_I2C) != R842_Success)
					return R842_Fail;
			 }
			 else if((R842_INFO.RF_KHz>138000) && (R842_INFO.RF_KHz<146000))	//144, +2/-6
			 {				 
				 R842_SetXtalCap(19);
			 }
			 else if((R842_INFO.RF_KHz>162000) && (R842_INFO.RF_KHz<170000))	//168, +2/-6
			 {				 
				 R842_SetXtalCap(22);
			 }
			 else if((R842_INFO.RF_KHz>522000) && (R842_INFO.RF_KHz<530000))	//528, +2/-6
			 {				 
	#if(R842_ATV_CIF_5M==TRUE)
				 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800) || (R842_INFO.R842_Standard==R842_MN_CIF_5M))
	#else
				 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800))
	#endif
					 R842_SetXtalCap(16);
				 else
					 R842_SetXtalCap(13);

			 }
			 else if((R842_INFO.RF_KHz>714000) && (R842_INFO.RF_KHz<722000))	//720, +2/-6
			 {				 
				 R842_SetXtalCap(11);
			 }
			 else
			 {
				 R842_SetXtalCap(R842_XTAL_CAP);
			 }
#else  //normal (ATV)
			if(R842_Xtal==16000) //16MHz Xtal
			{
				 if((R842_INFO.RF_KHz>42000) && (R842_INFO.RF_KHz<50000))	//48, +2/-6	 		 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x1C;  //auto,111	 
				 else if((R842_INFO.RF_KHz>362000) && (R842_INFO.RF_KHz<370000))	//368, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011			
				 else if((R842_INFO.RF_KHz>410000) && (R842_INFO.RF_KHz<418000))	//416, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100
				 else if((R842_INFO.RF_KHz>458000) && (R842_INFO.RF_KHz<466000))	//464, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100
				 else
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101			
			}
			else  //24/27M
			{
				 if((R842_INFO.RF_KHz>90000) && (R842_INFO.RF_KHz<98000))	//96, +2/-6	 		 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x08;  //0.5mA,010	
				 else if((R842_INFO.RF_KHz>114000) && (R842_INFO.RF_KHz<122000))	//120, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101	
				 else if((R842_INFO.RF_KHz>138000) && (R842_INFO.RF_KHz<146000))	//144, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101	
				 else if((R842_INFO.RF_KHz>162000) && (R842_INFO.RF_KHz<170000))	//168, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101	
				 else if((R842_INFO.RF_KHz>234000) && (R842_INFO.RF_KHz<242000))	//240, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011	
				 else if((R842_INFO.RF_KHz>258000) && (R842_INFO.RF_KHz<266000))	//264, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000
				 else if((R842_INFO.RF_KHz>282000) && (R842_INFO.RF_KHz<290000))	//288, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000
				 else if((R842_INFO.RF_KHz>330000) && (R842_INFO.RF_KHz<338000))	//336, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100
				 else if((R842_INFO.RF_KHz>354000) && (R842_INFO.RF_KHz<362000))	//360, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
				 else if((R842_INFO.RF_KHz>378000) && (R842_INFO.RF_KHz<386000))	//384, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000
				 else if((R842_INFO.RF_KHz>402000) && (R842_INFO.RF_KHz<410000))	//408, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011	
				 else if((R842_INFO.RF_KHz>426000) && (R842_INFO.RF_KHz<434000))	//432, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
				 else if((R842_INFO.RF_KHz>450000) && (R842_INFO.RF_KHz<458000))	//456, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100				 
				 else if((R842_INFO.RF_KHz>498000) && (R842_INFO.RF_KHz<506000))	//504, +2/-6	 
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000
				 else if((R842_INFO.RF_KHz>=528000) && (R842_INFO.RF_KHz<530000))	//528, +2/0
				 {
#if(R842_ATV_CIF_5M==TRUE)
					 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800) || (R842_INFO.R842_Standard==R842_MN_CIF_5M))
#else
					 if((R842_INFO.R842_Standard==R842_MN_5100) || (R842_INFO.R842_Standard==R842_MN_5800))
#endif
					 {
						 if(vco_bank_read==55)
							 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x08;  //0.5mA,010
						 else //56
							 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
					 }
					 else
						 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
				 }
				 else if((R842_INFO.RF_KHz>522000) && (R842_INFO.RF_KHz<528000))	//528, +0/-6
				 {
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101
				 }
				 else if(R842_INFO.RF_KHz<482000)	 //480+2
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x1C;  //auto,111
				 else
					 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101	

				 //Xtal cap
				 if((R842_INFO.RF_KHz>66000) && (R842_INFO.RF_KHz<74000))	//72, +2/-6
				 {				 
					 if(R842_SHARE_XTAL!=R842_SLAVE_XTAL_OUT)
					 {					 
						R842_SetXtalCap(38);
					 }
				 }
				 else if((R842_INFO.RF_KHz>114000) && (R842_INFO.RF_KHz<122000))	//120, +2/-6
				 {
					 if(R842_SHARE_XTAL!=R842_SLAVE_XTAL_OUT)
					 {					 
						R842_SetXtalCap(38);
					 }		

					 //SDM on
					 R842_I2C.RegAddr = 29;
					 R842_Array[29] = (R842_Array[29] & 0xFC) | 0x00;  
					 R842_I2C.Data = R842_Array[29];
					 if(R842_I2C_Write(&R842_I2C) != R842_Success)
						return R842_Fail;
				 }
				 else
				 {
					 R842_SetXtalCap(R842_XTAL_CAP);
				 }	

				 //mixer top=6 (528, 720)
				 if((R842_INFO.RF_KHz>522000) && (R842_INFO.RF_KHz<530000))	//528, +2/-6
				 {
					 R842_I2C.RegAddr = 40;			
					 R842_Array[40] = (R842_Array[40] & 0xF0) | (15 - 6);
					 R842_I2C.Data = R842_Array[40];
					 if(R842_I2C_Write(&R842_I2C) != R842_Success)
						 return R842_Fail;	
				 }
				 
				 if((R842_INFO.RF_KHz>716000) && (R842_INFO.RF_KHz<722000)) //720, +2,-6
				 {
					 R842_I2C.RegAddr = 40;			
					 R842_Array[40] = (R842_Array[40] & 0xF0) | (15 - 6);
					 R842_I2C.Data = R842_Array[40];
					 if(R842_I2C_Write(&R842_I2C) != R842_Success)
						 return R842_Fail;
				 }

		   } //end 24/27M
#endif
		
		 R842_I2C.RegAddr = 31;			
		 R842_I2C.Data = R842_Array[31];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;	


	 }
	 else  //DTV  
	 {		 		
#if(R842_DTV_AGC_SLOW == TRUE)

		//Set AGC clk slow
		R842_I2C.RegAddr = 47;	
		R842_Array[47] = (R842_Array[47] & 0xF3) | 0x0C;  //R47[3:2]=11 (64Hz->128Hz)
		R842_I2C.Data = R842_Array[47];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;
#endif
/*  //A+D all set 4K
#if(R842_FOR_LGIT == TRUE)

		//Set AGC clk 
		R842_I2C.RegAddr = 47;	
		R842_Array[47] = (R842_Array[47] & 0xF3) | 0x08;  //R47[3:2]=10 (4KHz)
		R842_I2C.Data = R842_Array[47];
		if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;
#endif
*/
		 //TF LPF_Q enhance
		 R842_I2C.RegAddr = 15;			
		 R842_Array[15] = (R842_Array[15] | 0x80);  //normal
		 R842_I2C.Data = R842_Array[15];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;	

#if(R842_FOR_LGIT==TRUE || R842_FOR_SEMCO_MODULE==TRUE)
		 if((R842_INFO.RF_KHz>44000) && (R842_INFO.RF_KHz<52000))	//48, +4/-4			 
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
		 else if((R842_INFO.RF_KHz>68000) && (R842_INFO.RF_KHz<76000))	//72, +4/-4			 
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011	
		 else if((R842_INFO.RF_KHz>92000) && (R842_INFO.RF_KHz<100000))	//96, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x00;  //0.7mA,000		 
		 else if((R842_INFO.RF_KHz>212000) && (R842_INFO.RF_KHz<220000))	//216, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x08;  //0.5mA,010	
		 else if((R842_INFO.RF_KHz>236000) && (R842_INFO.RF_KHz<240000))	//240, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011			
		 else if((R842_INFO.RF_KHz>548000) && (R842_INFO.RF_KHz<556000))	//552, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
		 else if((R842_INFO.RF_KHz>572000) && (R842_INFO.RF_KHz<580000))	//576, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
		 else if((R842_INFO.RF_KHz>596000) && (R842_INFO.RF_KHz<604000))	//600, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
		 else if((R842_INFO.RF_KHz>620000) && (R842_INFO.RF_KHz<628000))	//624, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
		 else if((R842_INFO.RF_KHz>788000) && (R842_INFO.RF_KHz<796000))	//792, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100
		 else if((R842_INFO.RF_KHz>836000) && (R842_INFO.RF_KHz<844000))	//840, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100
		 else if((R842_INFO.RF_KHz>860000) && (R842_INFO.RF_KHz<868000))	//864, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
		 else if((R842_INFO.RF_KHz>884000) && (R842_INFO.RF_KHz<892000))	//888, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x10;  //0.3mA,100
		 else 
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x1C;  //auto,111


		 if((R842_INFO.RF_KHz>68000) && (R842_INFO.RF_KHz<76000))	//72, +4/-4
		 {
			 R842_SetXtalCap(33);	

			 //SDM on
			 R842_I2C.RegAddr = 29;
			 R842_Array[29] = (R842_Array[29] & 0xFC) | 0x00;  
			 R842_I2C.Data = R842_Array[29];
			 if(R842_I2C_Write(&R842_I2C) != R842_Success)
				return R842_Fail;
		 }
		 else if((R842_INFO.RF_KHz>116000) && (R842_INFO.RF_KHz<124000))	//120, +4/-4
			 R842_SetXtalCap(22);	
		 else if((R842_INFO.RF_KHz>164000) && (R842_INFO.RF_KHz<172000))	//168, +4/-4
			 R842_SetXtalCap(13);	
		 else if((R842_INFO.RF_KHz>236000) && (R842_INFO.RF_KHz<244000))	//240, +4/-4
			 R842_SetXtalCap(13);	
		 else
			 R842_SetXtalCap(R842_XTAL_CAP);

#else
		 if((R842_INFO.RF_KHz>92000) && (R842_INFO.RF_KHz<100000))	//96, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101		 
		 else if((R842_INFO.RF_KHz>212000) && (R842_INFO.RF_KHz<220000))	//216, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x04;  //0.6mA,001	
		 else if((R842_INFO.RF_KHz>236000) && (R842_INFO.RF_KHz<240000))	//240, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011			
		 else if(R842_INFO.RF_KHz<508000)	 //504+4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x1C;  //auto,111
		 else
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101	

	#if(R843_TUNER==TRUE) //overwrite
		 if((R842_INFO.RF_KHz>72000) && (R842_INFO.RF_KHz<76000))	//72, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x14;  //0.2mA,101

		 if((R842_INFO.RF_KHz>92000) && (R842_INFO.RF_KHz<100000))	//96, +4/-4
			 R842_Array[31] = (R842_Array[31] & 0xE3) | 0x0C;  //0.4mA,011
	#endif
#endif

		 R842_I2C.RegAddr = 31;			
		 R842_I2C.Data = R842_Array[31];
		 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			 return R842_Fail;	


		if(R842_Chip==R842_MP)
		{
			//ATSC special, overwrite previous setting
			if(R842_INFO.R842_Standard==R842_ATSC || R842_INFO.R842_Standard==R842_ATSC_IF_5M)
			{
				//539~545, Mid band, TF=0
				if((R842_INFO.RF_KHz<=545000) && (R842_INFO.RF_KHz>=539000))
				{
					//Set TF: R14[6:0]=0
					R842_I2C.RegAddr = 14;
					R842_Array[14] = (R842_Array[14] & 0x80) | 0;
					R842_I2C.Data = R842_Array[14]  ;
					if(R842_I2C_Write(&R842_I2C) != R842_Success)
						return R842_Fail;			

					//Set LNA Mid band: R15[1:0]=10
					R842_I2C.RegAddr = 15;
					R842_Array[15] = (R842_Array[15] & 0xFC) | 0x02;
					R842_I2C.Data = R842_Array[15]  ;
					if(R842_I2C_Write(&R842_I2C) != R842_Success)
						return R842_Fail;	
				
				}		
			} //end of ATSC special setting
		}


		switch(R842_INFO.R842_Standard)
		{
		 case R842_DVB_T_6M:
		 case R842_DVB_T_7M:
		 case R842_DVB_T_8M:
		 case R842_DVB_T_6M_IF_5M:
		 case R842_DVB_T_7M_IF_5M:
		 case R842_DVB_T_8M_IF_5M:
		 case R842_DVB_T2_6M:
		 case R842_DVB_T2_7M:
		 case R842_DVB_T2_8M:
		 case R842_DVB_T2_6M_IF_5M:
		 case R842_DVB_T2_7M_IF_5M:
		 case R842_DVB_T2_8M_IF_5M:

			 if((R842_INFO.RF_KHz<R842_LNA_MID_LOW[R842_SetTfType]) || (R842_INFO.RF_KHz>R842_LNA_HIGH_MID[R842_SetTfType])) //low, high band
			 {
				 //RF_buf_cur=high
				 R842_I2C.RegAddr = 9;
				 R842_Array[9] = (R842_Array[9] & 0xF7) | 0x00; 
				 R842_I2C.Data = R842_Array[9];
				 if(R842_I2C_Write(&R842_I2C) != R842_Success)
					return R842_Fail;
			 }
			 else
			 {
				//RF_buf_cur=low
				 R842_I2C.RegAddr = 9;
				 R842_Array[9] = (R842_Array[9] & 0xF7) | 0x08;  
				 R842_I2C.Data = R842_Array[9];
				 if(R842_I2C_Write(&R842_I2C) != R842_Success)
					return R842_Fail;					 
			 }

			 break;

		 case R842_DTMB_8M_4570:
		 case R842_DTMB_6M_4500:
		 case R842_DTMB_8M_IF_5M:
		 case R842_DTMB_6M_IF_5M:

				 //RF_buf_cur=high
				 R842_I2C.RegAddr = 9;
				 R842_Array[9] = (R842_Array[9] & 0xF7) | 0x00; 
				 R842_I2C.Data = R842_Array[9];
				 if(R842_I2C_Write(&R842_I2C) != R842_Success)
					return R842_Fail;

			 break;

		 default:
			 break;
		}			

	 }  //end of DTV

    //------- filter gain comp -------//
	if(R842_INFO.R842_Standard<R842_ATV_SIZE)  //ATV
	{
		R842_Array[23] = (R842_Array[23] & 0xF7) | 0x08;   //manual
		R842_Array[24] = (R842_Array[24] & 0x7F) | 0x00;   //normal
	}
	else //DTV
	{
		if(R842_Poly==R842_Poly_3)
		{
			R842_Array[23] = (R842_Array[23] & 0xF7) | 0x08;   //manual
			R842_Array[24] = (R842_Array[24] & 0x7F) | 0x00;   //normal
			R842_Array[9] = R842_Array[9] | 0x02;   //R9[2]=1
			R842_Array[19] = R842_Array[19] & 0xEF; //R19[4]=0
		}
		else
		{
#if(R842_FOR_LGIT==TRUE) 

			//pul gcomp enable
			R842_Array[23] = (R842_Array[23] & 0xF7) | 0x08;   //manual

			//filter gcomp
			R842_Array[24] = (R842_Array[24] & 0x7F) | 0x80;   //+1dB

			//poly gcomp 
			R842_Array[9] = R842_Array[9] | 0x02;    //4/2
			R842_Array[19] = R842_Array[19] & 0xEF;

#elif (R842_FOR_SEMCO_MODULE==TRUE)

		//pul gcomp enable
		R842_Array[23] = (R842_Array[23] & 0xF7) | 0x00;   //enable
		
		//filter gcomp
		if((R842_INFO.RF_KHz>300000) && (R842_INFO.RF_KHz<800000))
			R842_Array[24] = (R842_Array[24] & 0x7F) | 0x80;   //+1dB
		else
			R842_Array[24] = (R842_Array[24] & 0x7F) | 0x00;   //normal

		//poly gcomp (4/2)
		R842_Array[9] = R842_Array[9] | 0x02;   
		R842_Array[19] = R842_Array[19] & 0xEF;

#else  //Normal
		//pul gcomp enable
		R842_Array[23] = (R842_Array[23] & 0xF7) | 0x00;   //enable

		//filter gcomp
		if(R842_INFO.RF_KHz>350000)
			R842_Array[24] = (R842_Array[24] & 0x7F) | 0x80;   //+1dB
		else
			R842_Array[24] = (R842_Array[24] & 0x7F) | 0x00;   //normal

		//poly gcomp (4/2)
		R842_Array[9] = R842_Array[9] | 0x02;   
		R842_Array[19] = R842_Array[19] & 0xEF;
#endif
		}
	}	
	R842_I2C.RegAddr = 23;
	R842_I2C.Data = R842_Array[23];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 24;
	R842_I2C.Data = R842_Array[24];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 9;
	R842_I2C.Data = R842_Array[9];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_I2C.RegAddr = 19;
	R842_I2C.Data = R842_Array[19];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//-------- end filter comp ----------//

#if(R842_FOR_LGIT==TRUE) 

	//NA fast deglitch
	R842_I2C.RegAddr = 35;
	R842_Array[35] = (R842_Array[35] & 0xFC) | 0x02;  //20ms
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//deglitch clk
	R842_I2C.RegAddr = 36;
	R842_Array[36] = (R842_Array[36] & 0xBF) | 0x00;  //4KHz
	R842_I2C.Data = R842_Array[36];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//gain freeze ctrl by pul_flag (DTV only)
	R842_I2C.RegAddr = 34;
	R842_Array[34] = (R842_Array[34] & 0xDF) | 0x20;  
	R842_I2C.Data = R842_Array[34];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

#elif(R842_FOR_SEMCO_MODULE==TRUE) 

	//NA fast deglitch
	R842_I2C.RegAddr = 35;
	R842_Array[35] = (R842_Array[35] & 0xFC) | 0x01;  //45ms
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//deglitch clk
	R842_I2C.RegAddr = 36;
	R842_Array[36] = (R842_Array[36] & 0xBF) | 0x40;  //1KHz
	R842_I2C.Data = R842_Array[36];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//gain freeze ctrl by pul_flag (DTV only)
	R842_I2C.RegAddr = 34;
	R842_Array[34] = (R842_Array[34] & 0xDF) | 0x20;  
	R842_I2C.Data = R842_Array[34];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
#elif(R842_FOR_HIS_S11==TRUE)  //test for Hisilicon S11
		//NA fast deglitch
	R842_I2C.RegAddr = 35;
	R842_Array[35] = (R842_Array[35] & 0xFC) | 0x03;  //10ms
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//deglitch clk
	R842_I2C.RegAddr = 36;
	R842_Array[36] = (R842_Array[36] & 0xBF) | 0x00;  //4KHz
	R842_I2C.Data = R842_Array[36];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//gain freeze ctrl by pul_flag (DTV only)
	R842_I2C.RegAddr = 34;
	R842_Array[34] = (R842_Array[34] & 0xDF) | 0x20;  
	R842_I2C.Data = R842_Array[34];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	 //NAT hys = on hys
	 R842_I2C.RegAddr = 29;
	 R842_Array[29] = (R842_Array[29] & 0xE7) | 0x00;  
	 R842_I2C.Data = R842_Array[29];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	 //pulse range
	 R842_I2C.RegAddr = 46;
	 R842_Array[46] = (R842_Array[46] & 0xD3) | 0x24;  
	 R842_I2C.Data = R842_Array[46];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
#endif

	//LNA manual 0
	R842_I2C.RegAddr = 13;
	R842_Array[13] = (R842_Array[13] & 0xC0) | 0x01;  
	R842_I2C.Data = R842_Array[13];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

#if(R842_FOR_LGIT==TRUE)
	//LNA fast swl = 5.1u
	R842_I2C.RegAddr = 44;
	R842_Array[44] = (R842_Array[44] & 0xF3) | 0x0C;  
	R842_I2C.Data = R842_Array[44];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

//	R842_Delay_MS(delay_tmp);  //for LGIT test, 10 is ok
	R842_Delay_MS(10);

	//LNA fast swl = original
	R842_I2C.RegAddr = 44;
	R842_Array[44] = (R842_Array[44] & 0xF3) | (R842_SysFreq_Info1.LNA_DIS_SLOW_FAST & 0x0C);  
	R842_I2C.Data = R842_Array[44];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
#endif

	//LNA Auto
	R842_I2C.RegAddr = 13;
	R842_Array[13] = (R842_Array[13] & 0xFE) | 0x00;  
	R842_I2C.Data = R842_Array[13];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	 //AGC Ctrl
	 if(R842_INFO.R842_Standard<R842_ATV_SIZE)  //ATV
		 R842_Array[46] = (R842_Array[46] | 0x40);
	 else
		 R842_Array[46] = (R842_Array[46] & 0xBF); 

	 R842_I2C.RegAddr = 46;
	 R842_I2C.Data = R842_Array[46];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		 return R842_Fail;

	 return R842_Success;
}




R842_ErrCode R842_SetPllData(R842_Set_Info R842_INFO)
{	  
	  if(R842_Initial_done_flag==FALSE)
	  {
	      R842_Init();
	  }

      if(R842_SetStandard(R842_INFO.R842_Standard) != R842_Success)
		  return R842_Fail;

      if(R842_SetFrequency(R842_INFO) != R842_Success)
          return R842_Fail;

      return R842_Success;
}

R842_ErrCode R842_SetPllData_Mode(R842_Set_Info R842_INFO, R842_TuneMode_Type R842_TuningMode)
{
	UINT8 count = 0;
	UINT8 LNA_gain;

	LNA_gain = 31;

    if(R842_SetPllData(R842_INFO) != R842_Success)
        return R842_Fail;

	if(R842_TuningMode==R842_CHANNEL_CHANGE) //adjust to slow clk
	{	  
	  if(R842_INFO.R842_Standard>=R842_ATV_SIZE) //DTV
	  {
		  R842_I2C_Len.RegAddr = 0x00;
		  R842_I2C_Len.Len = 4;
		  if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
			  return R842_Fail;		

		  do
		  {
			  LNA_gain = (R842_I2C_Len.Data[3] & 0x1F);
			  R842_Delay_MS(10);
			  if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
				  return R842_Fail;	
			  count++;
		  
		  }while(((R842_I2C_Len.Data[3] & 0x1F)!=LNA_gain) && (count<5));

		  R842_AGC_Slow();
	  }
	}

	return R842_Success;
}

R842_ErrCode R842_Standby(void)
{
	UINT8 i;

	if(R842_Initial_done_flag==FALSE)
	{
		for(i=0; i<R842_REG_NUM; i++)
		{		
			if(R842_Xtal==24000)
				R842_Array[i]=R842_iniArray[0][i];		//24M
			else if(R842_Xtal==16000)
				R842_Array[i]=R842_iniArray[1][i];		//16M
			else
				R842_Array[i]=R842_iniArray[2][i];		//27M

		}
	}
	
	for(i=0; i<R842_REG_NUM; i++)
	{		
		R842_SBY[i]=R842_Array[i];		
	}

	 //All, RF_Buf, NAT, LNA, PFD_Dldo, ADC, Ring
	 R842_I2C.RegAddr = 8;
	 R842_Array[8] = 0xFB;  
	 R842_I2C.Data = R842_Array[8];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //LDO, TF_buf_cur=low, mpcr_cur=low
	 R842_I2C.RegAddr = 9;
	 R842_Array[9] = R842_Array[9] | 0x94;  
	 R842_I2C.Data = R842_Array[9];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //IQ Gen, Mixer, PLL_LDOA, Dldo2, Xtal LDO 
	 if(R842_SHARE_XTAL==R842_NO_SHARE_XTAL)  //not share xtal
		R842_Array[11] = 0xFF;    
	 else  //share xtal case
		R842_Array[11] = 0xBF;     //xtal ldo on

	 R842_I2C.RegAddr = 11;
	 R842_I2C.Data = R842_Array[11];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //LNA Det, PLL HF_Div_ldo_cur,  AGC
	 R842_I2C.RegAddr = 12;
	 R842_Array[12] = (R842_Array[12] & 0xF0) | 0x0F;    
	 R842_I2C.Data = R842_Array[12];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;
	
	 //LNA manual 31; TF sharp
	 R842_I2C.RegAddr = 13;
	 R842_Array[13] = (R842_Array[13] & 0x00) | 0xFF; 
	 R842_I2C.Data = R842_Array[13];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //Q1.5 off; TF code=0
	 R842_I2C.RegAddr = 14;
	 R842_Array[14] = (R842_Array[14] & 0x00); 
	 R842_I2C.Data = R842_Array[14];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //Byp-LPF = bypass
	 R842_I2C.RegAddr = 15;
	 R842_Array[15] = (R842_Array[15] & 0xBF) | 0x00; 
	 R842_I2C.Data = R842_Array[15];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //VGA code mode
	 R842_I2C.RegAddr = 25;
	 R842_Array[25] = (R842_Array[25] & 0xDF) | 0x20; 
	 R842_I2C.Data = R842_Array[25];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //Rf Buf manual 0
	 R842_I2C.RegAddr = 12;
	 R842_Array[12] = (R842_Array[12] & 0x7F) | 0x80; 
	 R842_I2C.Data = R842_Array[12];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 R842_I2C.RegAddr = 39;
	 R842_Array[39] = (R842_Array[39] & 0x0F) | 0x00; 
	 R842_I2C.Data = R842_Array[39];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 //force sharp
	 R842_I2C.RegAddr = 30;
	 R842_Array[30] = (R842_Array[30] & 0xEF) | 0x10; 
	 R842_I2C.Data = R842_Array[30];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
			return R842_Fail;

	 R842_Standby_flag = TRUE;

	return R842_Success;
}

//-----------------------------------------------------------------------//
//  This function is used to wake up tuner from Standby mode             //
//-----------------------------------------------------------------------//
R842_ErrCode R842_WakeUp(void)
{
	UINT8 i;
	UINT8 Pll_Dldo, Pll_Aldo;

    Pll_Dldo = R842_SBY[8] & 0x30;
	Pll_Aldo = R842_SBY[11] & 0x3C;


	if(R842_Standby_flag == FALSE)
	{
		return R842_Success;
	}

	R842_SBY[8] = (R842_SBY[8] & 0xCF) | 0x30;   //PLL_LDO_D1 off, R8[5:4]=11
	R842_SBY[11] = (R842_SBY[11] & 0xC0) | 0x3F; //PLL_LDO, Mixer, IQ_Gen off, R11[5:0]=111111

	R842_I2C_Len.RegAddr = 0;
	R842_I2C_Len.Len = R842_REG_NUM;
	for(i = 0; i<R842_REG_NUM; i ++)
	{
		R842_I2C_Len.Data[i] = R842_SBY[i];
		R842_Array[i] = R842_SBY[i];
	}
	if(R842_I2C_Write_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;

	//Mixer ON
	R842_I2C.RegAddr = 11;
	R842_Array[11] = R842_Array[11] & 0xFD;  //R11[1]=0
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//IQ Gen ON
	R842_I2C.RegAddr = 11;
	R842_Array[11] = R842_Array[11] & 0xFE;  //R11[0]=0
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//DLDO1 ON
	R842_I2C.RegAddr = 8;
	//R842_Array[8] = (R842_Array[8] & 0xCF) | 0x00;  //R8[5:4]=00
	R842_Array[8] = (R842_Array[8] & 0xCF) | Pll_Dldo;
	R842_I2C.Data = R842_Array[8];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//ALDO, DLDO2 ON
	R842_I2C.RegAddr = 11;
	//R842_Array[11] = (R842_Array[11] & 0xC3) | 0x10;  //R11[5:4]=01, R11[3:2]=00
	R842_Array[11] = (R842_Array[11] & 0xC3) | Pll_Aldo;
	R842_I2C.Data = R842_Array[11];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	R842_Standby_flag = FALSE;

	return R842_Success;
}

R842_ErrCode R842_GetRfGain(R842_RF_Gain_Info *pR842_rf_gain)
{
	R842_I2C_Len.RegAddr = 0x00;
	R842_I2C_Len.Len = 8;
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
	{
		R842_I2C_Read_Len(&R842_I2C_Len);
	}
	pR842_rf_gain->RF_gain1 = (R842_I2C_Len.Data[3] & 0x1F);          //lna
	pR842_rf_gain->RF_gain2 = (R842_I2C_Len.Data[4] & 0x0F);          //rf
	pR842_rf_gain->RF_gain3 = (R842_I2C_Len.Data[4] & 0xF0)>>4;       //mixer
	pR842_rf_gain->RF_gain4 = (R842_I2C_Len.Data[5] & 0x0F);          //filter

	pR842_rf_gain->RF_gain_comb = pR842_rf_gain->RF_gain1*15
		                                              + pR842_rf_gain->RF_gain2*7 
		                                              + pR842_rf_gain->RF_gain3*8
													  + pR842_rf_gain->RF_gain4*15;

    return R842_Success;
}


R842_ErrCode R842_RfGainMode(R842_RF_Gain_Type R842_RfGainType)
{
    UINT8 MixerGain = 0;
	UINT8 RfGain = 0;
	UINT8 LnaGain = 0;
	UINT8 FilterGain = 0;

	if(R842_RfGainType==R842_RF_MANUAL)
	{
		R842_I2C_Len.RegAddr = 0;
		R842_I2C_Len.Len = 8; 
		if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
		{
		    R842_I2C_Read_Len(&R842_I2C_Len);
		}

		LnaGain = R842_I2C_Len.Data[3] & 0x1F;
		RfGain = ((R842_I2C_Len.Data[4] & 0x0F) >> 0);
		MixerGain = ((R842_I2C_Len.Data[4] & 0xF0) >> 4); 
		FilterGain = ((R842_I2C_Len.Data[5] & 0x0F) >> 0);

		//LNA auto off
	     R842_I2C.RegAddr = 13;
	     R842_Array[13] = R842_Array[13] | 0x01;
		 R842_I2C.Data = R842_Array[13];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Mixer buffer & Mixer off
	     R842_I2C.RegAddr = 12;
	     R842_Array[12] = (R842_Array[12] & 0x3F) | 0x80;
		 R842_I2C.Data = R842_Array[12];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Filter auto off
	     R842_I2C.RegAddr = 22;
	     R842_Array[22] = R842_Array[22] & 0x7F;
		 R842_I2C.Data = R842_Array[22];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		//set LNA gain
	     R842_I2C.RegAddr = 13;
	     R842_Array[13] = (R842_Array[13] & 0xC1) | LnaGain<<1;
		 R842_I2C.Data = R842_Array[13];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //set Mixer Buffer gain
	     R842_I2C.RegAddr = 39;
	     R842_Array[39] = (R842_Array[39] & 0x0F) | RfGain<<4;
		 R842_I2C.Data = R842_Array[39];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //set Mixer & Filter gain
	     R842_I2C.RegAddr = 41;
	     R842_Array[41] = (R842_Array[41] & 0x00) | (FilterGain<<4) | MixerGain;
		 R842_I2C.Data = R842_Array[41];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;
	}
	else
	{
	    //LNA auto on
	     R842_I2C.RegAddr = 13;
	     R842_Array[13] = R842_Array[13] & 0xFE;
		 R842_I2C.Data = R842_Array[13];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Mixer buffer & Mixer on
	     R842_I2C.RegAddr = 12;
	     R842_Array[12] = (R842_Array[12] & 0x3F) | 0x40;
		 R842_I2C.Data = R842_Array[12];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Filter auto on
	     R842_I2C.RegAddr = 22;
	     R842_Array[22] = R842_Array[22] | 0x80;
		 R842_I2C.Data = R842_Array[22];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;
	}

    return R842_Success;
}

//------------------------------------------------------------------//
//  R842_PLL_Lock( ): Read PLL lock status (R3[6])                  //
//  Return: 1: PLL lock                                             //
//          0: PLL unlock                                           //
//------------------------------------------------------------------//
UINT8 R842_PLL_Lock(void)
{
	UINT8 fg_lock = 0;

	R842_I2C_Len.RegAddr = 0x00;
	R842_I2C_Len.Len = 3;
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
	{
	    R842_I2C_Read_Len(&R842_I2C_Len);
	}

	if( (R842_I2C_Len.Data[2] & 0x40) == 0x00 ) 		
		fg_lock = 0;		
	else
        fg_lock = 1;

	return fg_lock;
}

R842_ErrCode R842_AGC_Slow(void)
{
	 //Set AGC ref clk	
	 if(R842_Xtal==16000)			
		 R842_Array[30] = (R842_Array[30] & 0xDF) | 0x00;  //clk(16)/Xtaldiv/2  
	 else
		 R842_Array[30] = (R842_Array[30] & 0xDF) | 0x20;  //clk(24)/Xtaldiv/3 

	 R842_I2C.RegAddr = 30;
	 R842_I2C.Data = R842_Array[30];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		 return R842_Fail;

	 //AGC CLK slow
	 R842_I2C.RegAddr = 47;			
	 R842_Array[47] = (R842_Array[47] & 0xF3) | 0x0C;  //R47[3:2]=11
	 R842_I2C.Data = R842_Array[47];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		 return R842_Fail;

	 return R842_Success;
}
//------------------------------------------------------------------//
//  R842_SetIfFreq( ): Update tuner IF parameter                    //
//  Input para1: desired IF output freq                             //
//  Input para2: RF freq                                            //
//  Input para3: TV system number                                   //
//------------------------------------------------------------------//
R842_ErrCode R842_SetIfFreq(UINT16 IF_KHz, UINT32 RF_KHz, R842_Standard_Type u1SystemStd)
{
	R842_Sys_Info_Type     Sys_Info_temp;
	R842_Set_Info     R842_Info;

	R842_Info.R842_IfAgc_Select = R842_IF_AGC1;
	R842_Info.R842_Standard = u1SystemStd;

	Sys_Info_temp = R842_Sys_Sel(u1SystemStd);
	R842_Info.RF_KHz = RF_KHz + IF_KHz - Sys_Info_temp.IF_KHz;

	R842_SetFrequency(R842_Info);

	return R842_Success;
}

//-------------------------------------------------------------------------------//
//  R842_SetLpfBw( ): Set LPF coarse tune parameter: LPF_BW                      //
//  cover range if LPF_BW is:                                                    //
//		0: 7.60M~11.30MHz                                                        //
//		1: 6.45M~ 9.00MHz                                                        //
//		2: 5.60M~ 7.45MHz                                                        // 
//-------------------------------------------------------------------------------//
R842_ErrCode R842_SetLpfBw(UINT8 LPF_BW)  
{
	UINT8 u1LpfBw;

	if(LPF_BW==0)
         u1LpfBw = 0x00;     //8M
    else if(LPF_BW==1)
         u1LpfBw = 0x40;     //7M
	else
         u1LpfBw = 0x60;     //6M

	// Set LPF coarse BW, R22[6:5]
	R842_I2C.RegAddr = 22;
	R842_Array[22] = (R842_Array[22] & 0x9F) | u1LpfBw;
	R842_I2C.Data = R842_Array[22];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}

//------------------------------------------------------------------------------- //
//  R842_SetLpfOffset( ): Set LPF fine tune parameter: LPF_Offset                 //
//  range: 0x00~0x1F    (R22[4:0])                                                //
//  31 is narrowest; 0 is widest                                                  //
//--------------------------------------------------------------------------------//
R842_ErrCode R842_SetLpfOffset(UINT8 LPF_Offset)  
{
	// Set LPF fine code
	R842_I2C.RegAddr = 22;
	R842_Array[22] = (R842_Array[22] & 0xE0) | (LPF_Offset);  //R22[4:0]
	R842_I2C.Data = R842_Array[22];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}

//---------------------------------------------------------------------//
//  R842_SetHpfOffset( ): Set HPF parameter: HPF_Offset                //
//  range is: 0x00~0x0F    (R24[3:0])                                  //
//  0 is narrowest; 15 is widest                                       //
//	0: 4.80M		4: 2.25M		8: 1.45M		12: 0.67M          //
//	1: 2.97M		5: 2.00M		9: 1.15M		13: 0.54M          //
//	2: 2.65M		6: 1.78M		10: 0.90M		14: 0.41M          //
//	3: 2.50M		7: 1.67M		11: 0.79M		15: 0.33M          //
//---------------------------------------------------------------------//
R842_ErrCode R842_SetHpfOffset(UINT8 HPF_Offset)  
{

	// Set HPF corner 
	R842_I2C.RegAddr = 24;
	R842_Array[24] = (R842_Array[24] & 0xF0) | HPF_Offset;
	R842_I2C.Data = R842_Array[24];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}

//------------------------------------------------------------------//
//  R842_SetIfLpf( ): Set LPF                                       //
//  Input parameter: LPF_Cor_Freq    (unit: KHz)                    //
//------------------------------------------------------------------//
R842_ErrCode R842_SetIfLpf(UINT32 LPF_Cor_Freq) //TBD
{
	UINT8     u1FilterCode;

	u1FilterCode = R842_Filt_Cal_ADC(LPF_Cor_Freq, 1, 8);

	// Set LPF fine code
	R842_I2C.RegAddr = 22;
	R842_Array[22] = (R842_Array[22] & 0xE1) | (u1FilterCode<<1);  //R22[4:1]
	R842_I2C.Data = R842_Array[22];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	// Set LPF Lsb bit
	R842_I2C.RegAddr = 22;
	R842_Array[22] = (R842_Array[22] & 0xFE) | (R842_Lpf_Lsb);  //R22[0]
	R842_I2C.Data = R842_Array[22];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
	    return R842_Fail;

	// Set LPF coarse BW
	R842_I2C.RegAddr = 22;
	R842_Array[22] = (R842_Array[22] & 0x9F) | (R842_Bandwidth<<2);  //R22[6:5]
	R842_I2C.Data = R842_Array[22];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}

//----------------------------------------------------------------------//
//  R842_GetRfRssi( ): Get RF RSSI                                      //
//  1st parameter: input RF Freq    (KHz)                               //
//  2nd parameter: input Standard                                       //
//  3rd parameter: output RF gain (dB*100)                              //
//----------------------------------------------------------------------//
R842_ErrCode R842_GetRfRssi(UINT32 RF_Freq_Khz, R842_Standard_Type RT_Standard, INT32 *RfGain)
{ 
	UINT8   lna_max=29; 
	UINT8   lna_min=0;
	UINT8   rf_max=15;
	UINT8   mixer_max=14;
	UINT8   RF_gain1, RF_gain2, RF_gain3, RF_gain4;
	UINT8   u1FreqIndex = 0;
	INT16   u2FreqFactor;
	UINT16  acc_lna_gain;
	UINT16  acc_mixer_gain;
	INT16   rf_total_gain;
	INT32   rf_rssi;
	UINT8   pulse_comp;

	RT_Standard = RT_Standard;

	R842_I2C_Len.RegAddr = 0x00;
	R842_I2C_Len.Len = 8;
	if(R842_I2C_Read_Len(&R842_I2C_Len) != R842_Success)
	{
		R842_I2C_Read_Len(&R842_I2C_Len);
	}
	RF_gain1 = (R842_I2C_Len.Data[3] & 0x1F);          //lna
	RF_gain2 = (R842_I2C_Len.Data[4] & 0x0F);          //rf
	RF_gain3 = (R842_I2C_Len.Data[4] & 0xF0)>>4;       //mixer
	RF_gain4 = (R842_I2C_Len.Data[5] & 0x0F);          //filter
	R842_RfFlag = ((R842_I2C_Len.Data[5] & 0x10) >> 4);
	R842_PulseFlag = ((R842_I2C_Len.Data[5] & 0x40) >> 6);
	R842_TF_Mode1 = (R842_Array[13] & 0x40) >> 6;          //R13[6], 0:auto    1:manuel
	R842_TF_Mode2 = (R842_Array[13] & 0x80) >> 7;          //R13[7], 0:plain   1:sharp

	//max LNA gain
	if(R842_Array[17]&0x08)
		lna_max = 29;
	else
		lna_max = 28;

	//min LNA gain (enb_att)
	if((R842_Array[45]&0x30)==0x30)
		lna_min=0;
	else if((R842_Array[45]&0x30)==0x20) //disable 0~4
		lna_min=5;
	else if((R842_Array[45]&0x30)==0x00) //disable 0~6
		lna_min=7;
	else
		lna_min=0;

	//min LNA gain (gain_1_2)
	if(((R842_Array[19]&0x20)==0x20) && (lna_min==0))
	{
		if(	RF_gain3!=0)
		{
			lna_min = 3;
		}
	}

	//max RF buffer gain limit (MT6)
	if((R842_Array[45]&0xC0)==0xC0)
		rf_max = 15;
	else if((R842_Array[45]&0xC0)==0x80)
		rf_max = 11;
	else if((R842_Array[45]&0xC0)==0x40)
		rf_max = 3;
	else
		rf_max = 0;

	//max Mixer gain limit
	if((R842_Array[20]&0x60)==0x60)  //gain_limit=12
		mixer_max = 12;
	else if((R842_Array[20]&0x60)==0x40)  //gain_limit=10
		mixer_max = 10;
	else if((R842_Array[20]&0x60)==0x20)  //gain_limit=8
		mixer_max = 8;
	else
		mixer_max = 6;

	if(RF_gain1>lna_max)
		RF_gain1=lna_max;

	if(RF_gain1<lna_min)
		RF_gain1=lna_min;

	if(RF_gain2>rf_max)
		RF_gain2=rf_max;

	//if(RF_gain2>mixer_max)
	//	RF_gain3=mixer_max;

	if(RF_gain3>mixer_max)
	{
		/*
		//enb poly_gain 13,14
		if((R842_Array[19]&0x10)==0x10)
		{
			if(RF_gain3==13)
				acc_mixer_gain = R842_Mixer_Acc_Gain[mixer_max]+20;
			else if((RF_gain3==14) || (RF_gain3==15))
				acc_mixer_gain = R842_Mixer_Acc_Gain[mixer_max]+40;
			else
				acc_mixer_gain = R842_Mixer_Acc_Gain[mixer_max];
		}
		else
		{		
			acc_mixer_gain = R842_Mixer_Acc_Gain[mixer_max];
		}
		*/
		acc_mixer_gain = R842_Mixer_Acc_Gain[mixer_max];
		RF_gain3=mixer_max;
	}
	else
	{
		acc_mixer_gain = R842_Mixer_Acc_Gain[RF_gain3];
	}
		
	//Select LNA freq table
	if(RF_Freq_Khz<190000)   //<190M
	{
		u1FreqIndex = 0;
		u2FreqFactor = -10; //10
	}
	else if(RF_Freq_Khz>=190000 && RF_Freq_Khz<215000)   // 190~215M
	{
		u1FreqIndex = 1;
		u2FreqFactor = -10; //10
	}
	else if(RF_Freq_Khz>=215000 && RF_Freq_Khz<236000)   // 215~236M
	{
		u1FreqIndex = 2;
		u2FreqFactor = -10; //20
	}
	else if(RF_Freq_Khz>=236000 && RF_Freq_Khz<508000)   // 236~508M
	{
		u1FreqIndex = 3;
		u2FreqFactor = 70; 
	}
	else if(RF_Freq_Khz>=508000 && RF_Freq_Khz<590000)   // 508~590M
	{
		u1FreqIndex = 4;
		u2FreqFactor = 160; 
	}
	else if(RF_Freq_Khz>=590000 && RF_Freq_Khz<674000)   // 590~674M
	{
		u1FreqIndex = 5;
		u2FreqFactor = 100; //130
	}
	else   //>674M
	{
		u1FreqIndex = 6;
		u2FreqFactor = 100; //130
	}

	//LNA Gain
	if((R842_RfFlag==1 && R842_TF_Mode1==0) || (R842_TF_Mode1 & R842_TF_Mode2))   //Sharp
		acc_lna_gain = R842_Lna_Sharp_Acc_Gain[u1FreqIndex][RF_gain1];
	else
		acc_lna_gain = R842_Lna_Plain_Acc_Gain[u1FreqIndex][RF_gain1];
	
    //Pulse Flag
	if(R842_PulseFlag==1)	
		pulse_comp =  R842_Lna_Pulse_Comp[u1FreqIndex][RF_gain1];
	else
		pulse_comp = 0;

	acc_lna_gain = (UINT16)(acc_lna_gain + pulse_comp);


	rf_total_gain = acc_lna_gain + R842_Rf_Acc_Gain[RF_gain2] + 
		acc_mixer_gain + R842_Filter_Acc_Gain[RF_gain4];

	rf_total_gain = rf_total_gain - (INT16)u2FreqFactor;

    //VGA pin level
	if((R842_Array[25]&0x10)==0x00)
	{
		rf_total_gain = rf_total_gain + 40;  //+4.0dB
	}

    //3rd LPF gain(man)
	if((R842_Array[24]&0x40)==0x00)
	{
		rf_total_gain = rf_total_gain - 37;  //normal (for DTMB, <100M)
	}

	//filter comp
	if(((R842_Array[23]&0x08)==0x08) && ((R842_Array[24]&0x80)==0x80))  
	{
		if((R842_Array[24]&0x40)==0x40)
			rf_total_gain = rf_total_gain + 6;  //+0.6dB
		else
			rf_total_gain = rf_total_gain + 10;  //+1.0dB
	}

	rf_rssi = rf_total_gain*10;

	*RfGain = rf_rssi;

    return R842_Success;
}

//----------------------------------------------------------------------//
//  R842_GetIfRssi( ): Get IF VGA GAIN                                  //
//  1st parameter: return IF VGA Gain     (dB*100)                      //
//----------------------------------------------------------------------//
R842_ErrCode R842_GetIfRssi(UINT32 *VgaGain)
{
	UINT8   adc_read;
	I2C_LEN_TYPE Dlg_I2C_Len;
	INT32   vga_table[64] = {                        //*100
		0, 0, 0, 0, 0, 10, 20, 30, 40, 60,   //0~9
		90, 150, 180, 210, 250, 275, 300, 345, 390, 480,   //10~19
		500, 550, 600, 620, 650, 670, 710, 760, 780, 810,   //20~29
		850, 870, 880, 900, 940, 1000, 1030, 1070, 1130, 1170,   //30~39
		1220, 1270, 1360, 1500, 1550, 1620, 1720, 1770, 1820, 1880,   //40~49
		1970, 2060, 2095, 2140, 2190, 2205, 2240, 2270, 2320, 2390,   //50~59
		2450, 2480, 2530, 2580              //60~63
	};
    //pin_level:+4, delta=28, out_att:off

	//read adc value
	Dlg_I2C_Len.RegAddr = 0x00;
	Dlg_I2C_Len.Len = 2;
	if(R842_I2C_Read_Len(&Dlg_I2C_Len) != R842_Success) // read data length
	{
		R842_I2C_Read_Len(&Dlg_I2C_Len);
	}
	adc_read = (Dlg_I2C_Len.Data[1] & 0x3F);

	*VgaGain = vga_table[adc_read];

	return R842_Success;
}

//----------------------------------------------------------------------//
//  R842_GetTotalRssi( ): Get Total RSSI. Resolution 1dB                //
//  1st parameter: input RF Freq    (KHz)                               //
//  2nd parameter: input Standard                                       //
//  3rd parameter: return signal level indicator (dBm)                  //
//----------------------------------------------------------------------//
R842_ErrCode R842_GetTotalRssi(UINT32 RF_Freq_Khz, R842_Standard_Type RT_Standard, INT32 *RssiDbm)
{
	INT32   rf_rssi;
	UINT32  if_rssi;
	INT32   rem, total_rssi;
	INT32   ssi_offset = 0;   //need to fine tune by platform
	INT32   total_rssi_dbm;

	R842_GetRfRssi(RF_Freq_Khz, RT_Standard, &rf_rssi);

	R842_GetIfRssi(&if_rssi);  //vga gain        

    total_rssi = (INT32) (rf_rssi + if_rssi);
	rem = total_rssi - (total_rssi/100)*100; //for rounding
	if((rem>-50) && (rem<50))
		total_rssi_dbm = (total_rssi/100);
	else if(rem<=-50)
		total_rssi_dbm = (total_rssi/100)-1;
	else
		total_rssi_dbm = (total_rssi/100)+1;

	//for different platform, need to fine tune offset value
	*RssiDbm = (-1)*total_rssi_dbm + ssi_offset;   

	return R842_Success;
}

//----------------------------------------------------------------------//
//  R842_GetTotalRssi2( ): Get Total RSSI. Resolution 0.1dB             //
//  1st parameter: input RF Freq    (KHz)                               //
//  2nd parameter: input Standard                                       //
//  3rd parameter: return signal level indicator (dBm*10)               //
//----------------------------------------------------------------------//
R842_ErrCode R842_GetTotalRssi2(UINT32 RF_Freq_Khz, R842_Standard_Type RT_Standard, INT32 *RssiDbm)
{
	INT32   rf_rssi;
	UINT32  if_rssi;
	INT32   rem, total_rssi;
	INT32   ssi_offset = 0;   //need to fine tune by platform
	INT32   total_rssi_dbm;

	R842_GetRfRssi(RF_Freq_Khz, RT_Standard, &rf_rssi);

	R842_GetIfRssi(&if_rssi);  //vga gain        

    total_rssi = (INT32) (rf_rssi + if_rssi);

	//total_rssi_dbm = total_rssi/10;
	rem = total_rssi - (total_rssi/10)*10; //for rounding
	if((rem>-5) && (rem<5))
		total_rssi_dbm = (total_rssi/10);
	else if(rem<=-5)
		total_rssi_dbm = (total_rssi/10)-1;
	else
		total_rssi_dbm = (total_rssi/10)+1;

	//for different platform, need to fine tune offset value
	*RssiDbm = (-1)*total_rssi_dbm + ssi_offset;   

	return R842_Success;
}
//----------------------------------------------------------------------//
//  R842_SetXtalCap( ): Set R842 Internal Xtal Cap                      //
//  1st parameter: Xtal Cap value; range 0~41(pF)                       //
//----------------------------------------------------------------------//
R842_ErrCode R842_SetXtalCap(UINT8 u8XtalCap)
{
	UINT8 XtalCap;
	UINT8 Capx;
	UINT8 Capx_3_0, Capxx;

	if(u8XtalCap>31)
	{
		XtalCap = 1;  //10
		Capx = u8XtalCap-10;
	}
	else
	{
		XtalCap = 0; //0
        Capx = u8XtalCap;
	}

	Capxx = Capx & 0x01;
    Capx_3_0 = Capx >> 1;
		
	// Set Xtal Cap
	R842_I2C.RegAddr = 33;
	R842_Array[33] = (R842_Array[33] & 0xC0) | (Capxx<<5) | (XtalCap<<4) | Capx_3_0;  
	R842_I2C.Data = R842_Array[33];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	return R842_Success;
}

R842_ErrCode R842_CheckMaxGain(void)
{

	 //VGA Pin level(+4); delta(20dBc); MT6 change to 24dBc
	 R842_I2C.RegAddr = 25;
	 R842_Array[25] = (R842_Array[25] & 0xAF) | (0<<4) | (1<<6);  
     R842_I2C.Data = R842_Array[25];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
        return R842_Fail;

	 //3th LPF gain (man)(+4)
	 R842_I2C.RegAddr = 24;
	 R842_Array[24] = (R842_Array[24] & 0xBF) | (1<<6);  
     R842_I2C.Data = R842_Array[24];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
        return R842_Fail;

	 // Mixer Gain Limt (12)
	 R842_I2C.RegAddr = 20;
	 R842_Array[20] = (R842_Array[20] & 0x9F) | 0x60;
     R842_I2C.Data = R842_Array[20];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
        return R842_Fail;

	return R842_Success;
}

R842_Sys_Info_Type R842_Sys_Sel_8296(R842_Standard_Type R842_Standard)
{
	R842_Sys_Info_Type R842_Sys_Info;

	 R842_Sys_Info = R842_Sys_Sel(R842_Standard);

	switch (R842_Standard)
	{

    case R842_MN_5800: 
	case R842_MN_5100:   
#if(R842_ATV_CIF_5M==TRUE)
	case R842_MN_CIF_5M:  
#endif
		R842_Sys_Info.IF_KHz=5400;               //IF
		R842_Sys_Info.BW=0x60;                   //BW=6M
		R842_Sys_Info.FILT_CAL_IF=6600;          //CAL IF  (%)
		R842_Sys_Info.HPF_COR=0x0F;	             //R24[3:0]=15 
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

	case R842_PAL_I:         
#if(R842_ATV_CIF_5M==TRUE)
	case R842_PAL_I_CIF_5M: 
#endif
		R842_Sys_Info.IF_KHz=7250;               //IF
		R842_Sys_Info.BW=0x00;                   //BW=8M
		R842_Sys_Info.FILT_CAL_IF=9100;          //CAL IF  
		R842_Sys_Info.HPF_COR=0x0D;	             //R24[3:0]=13
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

	case R842_PAL_DK: 
#if(R842_ATV_CIF_5M==TRUE)
	case R842_PAL_DK_CIF_5M: 
#endif
		R842_Sys_Info.IF_KHz=6850;               //IF
		R842_Sys_Info.BW=0x40;                   //BW=7M
		R842_Sys_Info.FILT_CAL_IF=8000;          //CAL IF     
		R842_Sys_Info.HPF_COR=0x0F;	             //R24[3:0]=15
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

	case R842_PAL_B_7M:  
#if(R842_ATV_CIF_5M==TRUE)
	case R842_PAL_B_7M_6800:  
	case R842_PAL_B_7M_CIF_5M: 
#endif
		R842_Sys_Info.IF_KHz=6400;               //IF
		R842_Sys_Info.BW=0x40;                   //BW=7M
		R842_Sys_Info.FILT_CAL_IF=7650;          //CAL IF
		R842_Sys_Info.HPF_COR=0x0D;	             //R24[3:0]=13
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

    case R842_PAL_BGH_8M: 
#if(R842_ATV_CIF_5M==TRUE)
	case R842_PAL_BGH_8M_CIF_5M:
#endif
		R842_Sys_Info.IF_KHz=6750;               //IF
		R842_Sys_Info.BW=0x40;                   //BW=7M
		R842_Sys_Info.FILT_CAL_IF=8000;          //CAL IF
		R842_Sys_Info.HPF_COR=0x0C;	             //R24[3:0]=12
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

	case R842_SECAM_L: 
#if(R842_ATV_CIF_5M==TRUE)
	case R842_SECAM_L_CIF_5M:
#endif
		R842_Sys_Info.IF_KHz=6750;               //IF
		R842_Sys_Info.BW=0x40;                   //BW=7M
		R842_Sys_Info.FILT_CAL_IF=8100;          //CAL IF
		R842_Sys_Info.HPF_COR=0x0F;	             //R24[3:0]=15
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

    case R842_SECAM_L1:   
#if(R842_ATV_CIF_5M==TRUE)
	case R842_SECAM_L1_CIF_5M:
#endif
        R842_Sys_Info.IF_KHz=1250;               //IF
		R842_Sys_Info.BW=0x00;                   //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8900;          //CAL IF
		R842_Sys_Info.HPF_COR=0x0E;	             //R24[3:0]=14
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

    case R842_SECAM_L1_INV: 
#if(R842_ATV_CIF_5M==TRUE)
	case R842_SECAM_L1_INV_CIF_5M:
#endif
		R842_Sys_Info.IF_KHz=7300;               //IF
		R842_Sys_Info.BW=0x00;                   //BW=8M
		R842_Sys_Info.FILT_CAL_IF=8950;          //CAL IF
		R842_Sys_Info.HPF_COR=0x0D;	             //R24[3:0]=13
		R842_Sys_Info.FILT_EXT_ENA=0;            //ext disable
		R842_Sys_Info.HPF_EXT_SEL=0;             //+1
		R842_Sys_Info.FILT_EXT_POINT=2;		     //lna=max-1 & Buf 4
		break;

	default:
		break;
	}

	return R842_Sys_Info;
}



R842_ErrCode R842_RfGainCtrl(R842_RF_Gain_Type R842_RfGainType, UINT8 LnaGain, UINT8 RfGain, UINT8 MixerGain, UINT8 FilterGain)
{
	if(R842_RfGainType==R842_RF_MANUAL)
	{
		//LNA auto off
	     R842_I2C.RegAddr = 13;
	     R842_Array[13] = R842_Array[13] | 0x01;
		 R842_I2C.Data = R842_Array[13];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Mixer buffer & Mixer off
	     R842_I2C.RegAddr = 12;
	     R842_Array[12] = (R842_Array[12] & 0x3F) | 0x80;
		 R842_I2C.Data = R842_Array[12];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Filter auto off
	     R842_I2C.RegAddr = 22;
	     R842_Array[22] = R842_Array[22] & 0x7F;
		 R842_I2C.Data = R842_Array[22];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		//set LNA gain
	     R842_I2C.RegAddr = 13;
	     R842_Array[13] = (R842_Array[13] & 0xC1) | LnaGain<<1;
		 R842_I2C.Data = R842_Array[13];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //set Mixer Buffer gain
	     R842_I2C.RegAddr = 39;
	     R842_Array[39] = (R842_Array[39] & 0x0F) | RfGain<<4;
		 R842_I2C.Data = R842_Array[39];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //set Mixer & Filter gain
	     R842_I2C.RegAddr = 41;
	     R842_Array[41] = (R842_Array[41] & 0x00) | (FilterGain<<4) | MixerGain;
		 R842_I2C.Data = R842_Array[41];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;
	}
	else
	{
	    //LNA auto on
	     R842_I2C.RegAddr = 13;
	     R842_Array[13] = R842_Array[13] & 0xFE;
		 R842_I2C.Data = R842_Array[13];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Mixer buffer & Mixer on
	     R842_I2C.RegAddr = 12;
	     R842_Array[12] = (R842_Array[12] & 0x3F) | 0x40;
		 R842_I2C.Data = R842_Array[12];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;

		 //Filter auto on
	     R842_I2C.RegAddr = 22;
	     R842_Array[22] = R842_Array[22] | 0x80;
		 R842_I2C.Data = R842_Array[22];
	     if(R842_I2C_Write(&R842_I2C) != R842_Success)
		       return R842_Fail;
	}

    return R842_Success;
}
R842_ErrCode R842_Dump_Data(void) 
{
/*
 	UINT8   R842_RfFlag, R842_PulseFlag;
	//UINT8   R842_TF_Mode1, R842_TF_Mode2;
	UINT8   RF_gain1, RF_gain2, RF_gain3, RF_gain4;

	R842_Delay_MS(10);

	R842_I2C_Len.RegAddr = 0;
	R842_I2C_Len.Len = R842_REG_NUM;
	R842_I2C_Read_Len(&R842_I2C_Len);

	RF_gain1 = (R842_I2C_Len.Data[3] & 0x1F);          //lna
	RF_gain2 = (R842_I2C_Len.Data[4] & 0x0F);          //rf
	RF_gain3 = (R842_I2C_Len.Data[4] & 0xF0)>>4;       //mixer
	RF_gain4 = (R842_I2C_Len.Data[5] & 0x0F);          //filter
	R842_RfFlag = ((R842_I2C_Len.Data[5] & 0x10) >> 4);
	R842_PulseFlag = ((R842_I2C_Len.Data[5] & 0x40) >> 6);
	//R842_TF_Mode1 = (R842_Array[13] & 0x40) >> 6;          //R13[6], 0:auto    1:manuel
	//R842_TF_Mode2 = (R842_Array[13] & 0x80) >> 7;          //R13[7], 0:plain   1:sharp

	//for customer to dump data
	int i ;

	printf("Start Tuner Log...\n");
	printf("LNA=%d, RF=%d, Mixer=%d, Filter=%d\n", RF_gain1, RF_gain2, RF_gain3, RF_gain4);
	printf("RF_flag=%d, Pulse_flag=%d\n", R842_RfFlag, R842_PulseFlag);

	for(i=0;i<R842_REG_NUM;i++)
	{
		printf("R%d=0x%X\n",i,R842_I2C_Len.Data[i]);
	}
	printf("\n");
*/
	return R842_Success;
}


//---------------Test Function------------------------//
UINT8 R842_IC_Check(void) //for CTMR testing
{
    UINT8  CheckResult = 0;   //0:ok;  1:IMR fail; 2:TF_check fail; 3:ADC fail; 4:I2C fail;  5:Gain fail
	//UINT8  result = 0; 

	//I2C check
	CheckResult = R842_I2C_Check();
	if(CheckResult!=0)
	{
		return CheckResult;  //I2C fail
	}

	//IMR cal check
	if(R842_Cal_Prepare(R842_IMR_CAL) != R842_Success)     
	{
		CheckResult=4;   //I2C
		return CheckResult;
	}

	CheckResult = R842_IMR_Check(); 
	if(CheckResult!=0)
	{
		return CheckResult;  //IMR fail 
	}

	//Gain check
	CheckResult = R842_Gain_Check(); 
	if(CheckResult!=0)
	{
		return CheckResult;  //Gain fail 
	}

	//do UL TF check
	if(R842_InitReg() != R842_Success)        
	{
		CheckResult=4;   //I2C
		return CheckResult;
	}

	CheckResult = R842_UL_TF_Check();
	if(CheckResult!=0)  
	{
		return CheckResult;  //TF fail or ADC too low
	}


	R842_Initial_done_flag = FALSE;
	R842_IMR_done_flag = FALSE;
	R842_pre_standard = R842_STD_SIZE;

	return CheckResult;
}

UINT8 R842_Gain_Check(void) //for CTMR testing
{
    UINT8  result = 0;   //1:fail;  0: ok

	UINT8 R842_GainCheckArray[R842_REG_NUM] = {                  
	       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  //24M
	  //   0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07
           0x00, 0xF6, 0x10, 0x90, 0xB0, 0xC1, 0x00, 0xBC, 
	//     0x08  0x09  0x0A  0x0B  0x0C  0x0D  0x0E  0x0F                                                   	   													  						  
		   0x00, 0x77, 0x86, 0x30, 0x60, 0x00, 0x77, 0x69, 
	//     0x10  0x11  0x12  0x13  0x14  0x15  0x16  0x17                                                     	   
           0x41, 0x34, 0x8D, 0x11, 0x71, 0x1C, 0x3E, 0x40, 
	//     0x18  0x19  0x1A  0x1B  0x1C  0x1D  0x1E  0x1F 
		   0x21, 0x3F, 0x11, 0xC8, 0xDE, 0x38, 0x38, 0x08,
	//     0x20  0x21  0x22  0x23  0x24  0x25  0x26  0x27 
		   0x63, 0x00, 0xC2, 0x45, 0x55, 0xFB, 0x6C, 0x05 };
	//     0x28  0x29  0x2A  0x2B  0x2C  0x2D  0x2E  0x2F 

	UINT8 InitArrayCunt = 0;
	UINT8 ADC_Read1 = 0;
	UINT8 ADC_Read2 = 0;

	UINT32 RingVCO = 0;
	UINT32 RingFreq = 0;
	UINT32 RingRef = R842_Xtal;
	UINT8  divnum_ring = 0;

	R842_I2C_Len.RegAddr = 0;
	R842_I2C_Len.Len = R842_REG_NUM;
	for(InitArrayCunt = 0; InitArrayCunt<R842_REG_NUM; InitArrayCunt ++)
	{
		R842_I2C_Len.Data[InitArrayCunt] = R842_GainCheckArray[InitArrayCunt];
		R842_Array[InitArrayCunt] = R842_GainCheckArray[InitArrayCunt];
	}
	if(R842_I2C_Write_Len(&R842_I2C_Len) != R842_Success)
		return R842_Fail;   

	if(R842_Xtal==16000)  //16M	
         divnum_ring = 25;                    //3200/8/16.  32>divnum>7
	else if(R842_Xtal==24000) //24M
		 divnum_ring = 17;
	else if(R842_Xtal==27000) //27M
		 divnum_ring = 15;
	else //not support
		 return R842_Fail;
	
	RingVCO = (divnum_ring)* 8 * RingRef;  //VCO=3264/3200/3240 for 24M/16M/27M
	RingFreq = RingVCO/48;

	// RingFreq = 816M
	RingFreq = RingVCO/4;
	R842_Array[34] = (R842_Array[34] & 0x9F) | 0;          // ring_div1 /4 (0)
	R842_Array[35] = (R842_Array[35] & 0xFC) | 0;          // ring_div2 /1 (0)		

	//write RingPLL setting, R34
	R842_Array[34] = (R842_Array[34] & 0xE0) | divnum_ring;   //ring_div_num, R34[4:0]

	if(RingVCO>=3200000)
	    R842_Array[34] = (R842_Array[34] & 0x7F);   //vco_band=high, R34[7]=0
	 else
        R842_Array[34] = (R842_Array[34] | 0x80);      //vco_band=low, R34[7]=1

	//write RingPLL setting, R34
	R842_I2C.RegAddr = 34;
	R842_I2C.Data = R842_Array[34];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
	
    //write RingPLL setting, R35[1:0]
	R842_I2C.RegAddr = 35;
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	if(R842_MUX(RingFreq + R842_IMR_IF, RingFreq, R842_STD_SIZE) != R842_Success)      //RF MUX (LO, RF)
		return R842_Fail;

	if(R842_PLL((RingFreq + R842_IMR_IF), (UINT16)R842_IMR_IF, R842_STD_SIZE) != R842_Success)  //RF PLL
		return R842_Fail;

	 //Set LNA TF=(0,0)
	 R842_I2C.RegAddr = 14;
     R842_Array[14] = (R842_Array[14] & 0x80);  	
     R842_I2C.Data = R842_Array[14];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 R842_Delay_MS(10);

	 if(R842_Muti_Read(&ADC_Read1) != R842_Success)
		 return R842_Fail;

	 //Set RF Gain=15
	 R842_I2C.RegAddr = 39;
     R842_Array[39] = (R842_Array[39] & 0x0F) | (15<<4);  	
     R842_I2C.Data = R842_Array[39];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 R842_Delay_MS(10);

	 if(R842_Muti_Read(&ADC_Read2) != R842_Success)
		 return R842_Fail;

	 if((ADC_Read2-ADC_Read1)<20)
		 result = 5;    //RF gain fail
	 else
		 result = 0;

	 R842_I2C.RegAddr = 39;
     R842_Array[39] = (R842_Array[39] & 0x0F);  	//RF Gain=0
     R842_I2C.Data = R842_Array[39];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 //Set Mixer Gain=15
	 R842_I2C.RegAddr = 41;
     R842_Array[41] = (R842_Array[41] & 0xF0) | 15;  	
     R842_I2C.Data = R842_Array[41];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 if(R842_Muti_Read(&ADC_Read2) != R842_Success)
		 return R842_Fail;

	 if((ADC_Read2-ADC_Read1)<20)
		 result = 5;    //Mixer gain fail
	 else
		 result = 0;

	 R842_I2C.RegAddr = 41;
     R842_Array[41] = (R842_Array[41] & 0xF0) | 0;  	//Mixer Gain=0
     R842_I2C.Data = R842_Array[41];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 //Set Filter Gain=15
	 R842_I2C.RegAddr = 41;
     R842_Array[41] = (R842_Array[41] & 0x0F) | (15<<4);  	
     R842_I2C.Data = R842_Array[41];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 if(R842_Muti_Read(&ADC_Read2) != R842_Success)
		 return R842_Fail;

	 if((ADC_Read2-ADC_Read1)<20)
		 result = 5;    //Filter gain fail
	 else
		 result = 0;

	return result;
}

UINT8 R842_UL_TF_Check(void)
{
	UINT8   result = 0;   //0: ok
	UINT8   ADC_Read_Value0 = 60;
	UINT8   ADC_Read_Value32 = 0;

	//------- Low Band TF detect --------//
	if(R842_Cal_Prepare(R842_TF_LNA_CAL) != R842_Success)     
		return R842_Fail;

	//Set LPF Gain = 0
	R842_I2C.RegAddr = 41;
	R842_Array[41] = (R842_Array[41] & 0x0F) | (0<<4);
	R842_I2C.Data = R842_Array[41];  
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	 //Set LNA TF=(0,0)
	 R842_I2C.RegAddr = 14;
     R842_Array[14] = (R842_Array[14] & 0x80);  	
     R842_I2C.Data = R842_Array[14];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 R842_Delay_MS(10); //

	 if(R842_Muti_Read(&ADC_Read_Value0) != R842_Success)
		  return R842_Fail;

	 //Set LNA TF=32
	 R842_I2C.RegAddr = 14;
     R842_Array[14] = (R842_Array[14] & 0x80) | 32 ;  	
     R842_I2C.Data = R842_Array[14];
     if(R842_I2C_Write(&R842_I2C) != R842_Success)
          return R842_Fail;

	 R842_Delay_MS(10); //

	 if(R842_Muti_Read(&ADC_Read_Value32) != R842_Success)
		 return R842_Fail;

	 //if ADC_Read=0, TF_Check_Fail
	 if((ADC_Read_Value0<=3) && (ADC_Read_Value32<=3))
		 result = 3;  //ADC fail
	 else
		 result = 0;

	 //if ADC_Read=63, TF_Check_Fail
	 if((ADC_Read_Value0>=60) && (ADC_Read_Value32>=60))
		 result = 3;  //ADC fail
	 else
		 result = 0;

	return result;
}


UINT8 R842_I2C_Check(void)
{
	UINT8    result = 0;   //4:fail;  0: ok
	int      i;
	I2C_LEN_TYPE Dlg_I2C_Len;

	//write 0 and read
	Dlg_I2C_Len.RegAddr = 8;
	Dlg_I2C_Len.Len = R842_REG_NUM-8;

	for(i=0; i<R842_REG_NUM; i++)
	{
		Dlg_I2C_Len.Data[i] = 0;
	}
	R842_I2C_Write_Len(&Dlg_I2C_Len);

	R842_Delay_MS(50);

	Dlg_I2C_Len.RegAddr = 0;
	Dlg_I2C_Len.Len = R842_REG_NUM;
	R842_I2C_Read_Len(&Dlg_I2C_Len);
	
	result = 0;
	for(i=8; i<R842_REG_NUM; i++)
	{ 
	   if(Dlg_I2C_Len.Data[i]!=0)
	   {
		   result=4;
		   return result;
	   }
	}
		
	//write 1 and read
	Dlg_I2C_Len.RegAddr = 8;
	Dlg_I2C_Len.Len = R842_REG_NUM-8;

	for(i=0; i<R842_REG_NUM; i++)
	{
		Dlg_I2C_Len.Data[i] = 0xFF;
	}
	R842_I2C_Write_Len(&Dlg_I2C_Len);

	R842_Delay_MS(50);

	Dlg_I2C_Len.RegAddr = 0;
	Dlg_I2C_Len.Len = R842_REG_NUM;
	R842_I2C_Read_Len(&Dlg_I2C_Len);
	
	result = 0;
	for(i=8; i<R842_REG_NUM; i++)
	{ 
	   if(Dlg_I2C_Len.Data[i]!=0xFF)
	   {
		   result=4;
		   return result;
	   }
	}

	return result;

}
UINT8 R842_IMR_Check(void)
{
	UINT8  result = 0;   //1:fail;  0: ok
	UINT32 RingVCO = 0;
	UINT32 RingFreq = 0;
	UINT32 RingRef = R842_Xtal;
	UINT8  divnum_ring = 0;

	UINT8  IMR_Gain = 0;
	UINT8  IMR_Phase = 0;

	R842_Sect_Type IMR_POINT;

	if(R842_Xtal==16000)  //16M	
         divnum_ring = 25;                    //3200/8/16.  32>divnum>7
	else if(R842_Xtal==24000) //24M
		 divnum_ring = 17;
	else if(R842_Xtal==27000) //27M
		 divnum_ring = 15;
	else //not support
		 return R842_Fail;
	
	RingVCO = (divnum_ring)* 8 * RingRef;  //VCO=3264/3200/3240 for 24M/16M/27M
	RingFreq = RingVCO/48;


	// RingFreq = 544M
	RingFreq = RingVCO/6;
	R842_Array[34] = (R842_Array[34] & 0x9F) | (2<<5);  // ring_div1 /6 (2)
	R842_Array[35] = (R842_Array[35] & 0xFC) | (0);       // ring_div2 /1 (0)		

	//write RingPLL setting, R34
	R842_Array[34] = (R842_Array[34] & 0xE0) | divnum_ring;   //ring_div_num, R34[4:0]

	if(RingVCO>=3200000)
	    R842_Array[34] = (R842_Array[34] & 0x7F);   //vco_band=high, R34[7]=0
	 else
        R842_Array[34] = (R842_Array[34] | 0x80);      //vco_band=low, R34[7]=1

	//write RingPLL setting, R34
	R842_I2C.RegAddr = 34;
	R842_I2C.Data = R842_Array[34];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;
	
    //write RingPLL setting, R35[1:0]
	R842_I2C.RegAddr = 35;
	R842_I2C.Data = R842_Array[35];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

	//Normal mode 

	if(R842_MUX(RingFreq - R842_IMR_IF, RingFreq, R842_STD_SIZE) != R842_Success)      //IMR MUX (LO, RF)
		return R842_Fail;

	if(R842_PLL((RingFreq - R842_IMR_IF), (UINT16)R842_IMR_IF, R842_STD_SIZE) != R842_Success)  //IMR PLL
		return R842_Fail;

	 //Img_R = normal
	 R842_I2C.RegAddr = 20;
	 R842_Array[20] = (R842_Array[20] & 0x7F);  //R20[7]=0
	 R842_I2C.Data = R842_Array[20];
	 if(R842_I2C_Write(&R842_I2C) != R842_Success)
		 return R842_Fail;

	// Mixer Amp LPF=1 (0 is widest)
	R842_I2C.RegAddr = 19;
	R842_Array[19] = (R842_Array[19] & 0xF1) | (1<<1); 
	R842_I2C.Data = R842_Array[19];
	if(R842_I2C_Write(&R842_I2C) != R842_Success)
		return R842_Fail;

 	 //Set TF, place after R842_MUX( )
	 //TF is dependent to LNA/Mixer Gain setting
	if(R842_SetTF(RingFreq, (UINT8)R842_SetTfType) != R842_Success)
		return R842_Fail;

	//clear IQ_cap
	IMR_POINT.Iqcap = 0;
	
	if(R842_IQ(&IMR_POINT) != R842_Success)
		return R842_Fail;

	IMR_Gain = IMR_POINT.Gain_X & 0x1F;   //R20[4:0]
	IMR_Phase = IMR_POINT.Phase_Y & 0x1F; //R21[4:0]

	if(((IMR_Gain & 0x0F)>6) || ((IMR_Phase & 0x0F)>6))	
		result = 1; //fail
	else
		result = 0;

	return result;
}

UINT8 R842_Chip_Detect(void)
{
	I2C_LEN_TYPE Dlg_I2C_Len;
	Dlg_I2C_Len.RegAddr = 0;
	Dlg_I2C_Len.Len = 1;
	memset(Dlg_I2C_Len.Data,0,50);
	if(R842_I2C_Read_Len(&Dlg_I2C_Len))
	{
		if(Dlg_I2C_Len.Data[0]== R842_CHIP_ID)
		return R842_CHIP_ID;
	}
	return 0xFF;
}

//<<SMC jayden.chen add for R842 20150616
/********************************************************************************/
int R842_Convert(int InvertNum)
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

bool R842_I2C_Write_Len(I2C_LEN_TYPE *I2C_Info)
{
	int i = 0,count;
	unsigned char regAddr;
	unsigned char i2cData[50];
	BOOLEAN WRITE_OK = TRUE;

	regAddr = I2C_Info->RegAddr;
	count	= I2C_Info->Len;

	for(i = 0;i < I2C_Info->Len;i ++)
	{
		i2cData[i] = I2C_Info->Data[i];
	}

	if(MDrv_IIC_WriteBytes(R842_ADDRESS, 1, &regAddr, count, i2cData)==FALSE)
	{
		printf("\t ---->>RF R842 iic failed[%d]\n", regAddr);
		WRITE_OK = FALSE;
	}
	else
	{
		//xc_Check_Busy();
	}

	return WRITE_OK;
}

bool R842_I2C_Read_Len(I2C_LEN_TYPE *I2C_Info)
{
	int i = 0,count;
	unsigned char regAddr;
	unsigned char i2cData[50];
	BOOLEAN READ_OK = TRUE;

	regAddr = I2C_Info->RegAddr;
	count	= I2C_Info->Len;

    if ( MDrv_IIC_ReadBytes(R842_ADDRESS, 1, &regAddr,count, i2cData) == FALSE )
    {
		printf("\t ---->>Read RF R842 iic failed[%d]\n", regAddr);
		READ_OK = FALSE;
    }

	for(i = 0; i < count; i ++)
	{
		I2C_Info->Data[i] = R842_Convert(i2cData[i]);
	}
	return READ_OK;
}



bool R842_I2C_Write(I2C_TYPE *I2C_Info)
{
	unsigned char regAddr;
	unsigned char i2cData;
	BOOLEAN WRITE_OK = TRUE;

	regAddr = I2C_Info->RegAddr;
	i2cData = I2C_Info->Data;

	if(MDrv_IIC_WriteBytes(R842_ADDRESS, 1, &regAddr, 1, &i2cData)==FALSE)
	{
		printf("\t ---->>RF R842 iic failed[%d]\n", regAddr);
		WRITE_OK = FALSE;
	}
	else
	{
		//xc_Check_Busy();
	}

	return WRITE_OK;

}

BOOLEAN R842_devTunerInit(void)
{
    R842_ErrCode ret;
	ret = R842_Init();
	if(ret == R842_Success)
	{
		printf("\r\n-->>R842 init ok\n");
		return TRUE;
	}	
	else
	{
		printf("\r\n-->>R842 init !!!Error!!!\n");
		return FALSE;
	}	
}

