////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
///
/// file    apiDigiTuner.c
/// @brief  Digital Tuner Low-Level API
/// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////

#include "Board.h"

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#if (ENABLE_S2)
//#include "MsCommon.h"
#include "Board.h"

#include "drvDish.h"

#include "msAPI_Demod.h"

#include "apiDigiTuner.h"
#include "GPIO.h"
#include "Utl.h"
#include <stdio.h>
#include <string.h>
// INCLUDES
#include <float.h>                 // Properties of FP representation on this

double
acos( double );            // arc cosine i.e. inverse cos

 double
asin( double );            // arc sine i.e. inverse sin

 double
atan( double );            // arc tan i.e. inverse tan

 double
atan2( double, double );   // arc tan of (first arg/second arg) using signs
                           // of args to determine quadrant

 double
cos( double );             // cosine

 double
sin( double );             // sine

 double
tan( double );             // tangent



#define AUTO_TUNE_TIMEOUT       2000
#define MANUAL_TUNE_TIMEOUT     600

#define IF_MIN_FREQ      950
#define IF_MIDDLE_FREQ 1550
#define IF_MAX_FREQ     2150
#define IF_OFFSET_FREQ  25

#define M_PI            3.14159265358979323846
#define TO_RADS (M_PI / 180.0)
#define TO_DEC (180.0 / M_PI)


DISH_LOCATION SetSATLocation[]=
{
    {(MS_U8*)"Manual",0,0},

    //A
    {(MS_U8*)"Abuzaby",542,242},
    {(MS_U8*)"Alger",29,365},

    //B
    {(MS_U8*)"Beirut",356,337},
    {(MS_U8*)"Berlin",133,525},
    {(MS_U8*)"Budapest",190,475},

    //C
    {(MS_U8*)"Cairo",312,300},
    {(MS_U8*)"Casablanka",75,335},

    //D
    {(MS_U8*)"Doha",514,252},

    //F
    {(MS_U8*)"Frankfurt",86,501},

    //H
    {(MS_U8*)"Hochiminh City",1066,107},
    {(MS_U8*)"Hong Kong",1141,224},

    //I
    {(MS_U8*)"Istanbul",290,410},

    //J
    {(MS_U8*)"Jakarta",1067,62},

    //K
    {(MS_U8*)"Karachi",670,248},
    {(MS_U8*)"Kualalumpur",1017,31},
    {(MS_U8*)"Kuwait",480,291},

    //L
    {(MS_U8*)"London",1,514},

    //M
    {(MS_U8*)"Madrid",36,404},
    {(MS_U8*)"Melbourne",1450,378},
    {(MS_U8*)"Moscow",377,557},
    {(MS_U8*)"Muenchen",115,481},
    {(MS_U8*)"Muscat",586,235},

    //N
    {(MS_U8*)"New Delhi",772,285},

    //R
    {(MS_U8*)"Riyadh",467,246},

    //S
    {(MS_U8*)"Seoul",1269,375},
    {(MS_U8*)"Sydney",1510,338},

    //T
    {(MS_U8*)"Teheran",514,357},
    {(MS_U8*)"Telaviv",348,319},
    {(MS_U8*)"Tripoli",132,327},

    //P
    {(MS_U8*)"Paris",24,484},
};


static DTVPROGRAMID_M    _tunerParam;
static MS_SAT_PARAM _stSATParam;
static MS_BOOL bIsHiLOF = FALSE;
//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------
#if(0)
#define TUNER_MUTEX_TIMEOUT         500
#ifdef MS_DEBUG
#define TUNER_DBG_ENABLE            1
#else
#define TUNER_DBG_ENABLE            1
#endif

#define AUTO_TUNE_TIMEOUT       2000
#define MANUAL_TUNE_TIMEOUT     600//6000

#if TUNER_DBG_ENABLE
#define DBG_M(fmt, args...)         printf(fmt, ##args)
#define DBG_E(fmt, args...)         printf(fmt, ##args)
#else
#define DBG_M(fmt, args...)         {}
#define DBG_E(fmt, args...)         {}
#endif



#if 0
//--------------------------------------------------------------------------------------------------
//  Global Variables
//--------------------------------------------------------------------------------------------------
extern MS_U8 dmdConfig[];

//-------------------------------------------------------------------------------------------------
//  General Demod Configuration for Vender Tuners
//-------------------------------------------------------------------------------------------------
//  Note: 1. Please assign IF_BYTE0, IF_BYTE1 (hex) value according to IF frequency.
//	      Example:
//				IF_FREQ = 36000kHz (0x8CA0 in hex)
//				IF_BYTE0 = 0xA0, IF_BYTE1 = 0x8C
//		  2. Please use specific dmdConfig[] table according to RF-AGC configuration
//			 An incorrect selection(or modification) on dmdConfig[] can cause performance
//			 degrade or malfunction of demodulator.
//-------------------------------------------------------------------------------------------------

//  Demodulator settings for EXTERNAL RF-AGC tuner:
//	static MS_U8 dmdConfig[] =
//	{
//		0x00, IF_BYTE0, IF_BYTE1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//	    0x73, 0x00, 0xb3, 0x33, 0x03, 0x05, 0x52, 0x52, 0x73, 0x73, 0x73, 0x31, 0x52, 0x73, 0x73, 0x73,
//	    0x73, 0xc0, 0x24, 0x00, 0x80, 0xff, 0x7f, 0x99, 0xcc, 0xff, 0x7f, 0x0e, 0x2b, 0x0b, 0x47, 0x40,
//	    0xd3, 0x9a, 0xde, 0x11, 0xa4, 0x60, 0x08, 0x08, 0x10, 0x00, 0x02, 0x0b, 0x03, 0x05, 0x03, 0x83,
//	    0x52, 0x52, 0x55,
//	}

//  Demodulator settings for INTERNAL RF-AGC tuner:
//	static MS_U8 dmdConfig[] =
//	{
//		0x01, IF_BYTE0, IF_BYTE1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
//	    0x73, 0x00, 0xb3, 0x33, 0x03, 0x05, 0x52, 0x52, 0x73, 0x73, 0x73, 0x31, 0x52, 0x73, 0x73, 0x73,
//	    0x72, 0xc0, 0x24, 0x00, 0x80, 0xff, 0x7f, 0x00, 0x80, 0xff, 0x7f, 0x0e, 0x2b, 0x0b, 0x47, 0x40,
//	    0xd3, 0x9a, 0xde, 0x11, 0xa4, 0x60, 0x08, 0x08, 0x00, 0x10, 0x02, 0x0b, 0x03, 0x05, 0x03, 0x82,
//	    0x52, 0x52, 0x55,
//	}

#endif

#if 1

MS_BOOL MApi_DigiTuner_PowerOnOff(MS_BOOL bEnPower)
{
    ENTRY();

#if   (FRONTEND_TUNER_TYPE == TUNER_PLAYCARD)
#elif ((FRONTEND_TUNER_TYPE == TUNER_PHILIPS_CD1316) || \
		   (FRONTEND_TUNER_TYPE == TUNER_PHILIPS_CD1616LF_GIH_4) || \
		   (FRONTEND_TUNER_TYPE == TUNER_PHILIPS_CD1616LF_GIGH_4) || \
		   (FRONTEND_TUNER_TYPE == TUNER_THOMSON_DCT70707) || \
		   (FRONTEND_TUNER_TYPE == TUNER_THOMSON_DCT7046A) || \
		   (FRONTEND_TUNER_TYPE == TUNER_ALPS_TDAE3C01A))
    MDrv_Tuner_PowerOnOff(bEnPower);
#else
#endif

#if   (FRONTEND_DEMOD_TYPE == DEMOD_PLAYCARD)
#elif (FRONTEND_DEMOD_TYPE == DEMOD_MSDVBC)
    MDrv_Dmd_PowerOnOff(bEnPower);
#else
    MDrv_CofdmDmd_PowerOnOff(bEnPower);
#endif

    RETURN(TRUE);
}

#endif

#if 0
#ifdef DVBS
void MApi_DigiTuner_ForceRetune(void)
{
      CofdmDMD_Param    dmdParam;

      _DigiTuner_SetLNBPower(_stSATParam.eLNBPwrOnOff,_tunerParam.SatParam.u8Polarity);
      _DigiTuner_SwitchSatellite(_stSATParam,_tunerParam.SatParam.u8Polarity,bIsHiLOF);
     #if (FRONTEND_DEMOD_TYPE == DEMOD_AVL2108)
	{
	        _DigiTuner_CalculateIF(_stSATParam,&_tunerParam,&dmdParam);
		 dmdParam.u32SymbolRate = _tunerParam.SatParam.u16SymbolRate;
		 dmdParam.u32SymbolRate *= 1000;
               if (MDrv_CofdmDmd_Restart(&dmdParam) == FALSE)
               {
                   DBG_E("%s: COfdm DMD restart failed.\n", __FUNCTION__);
               }
	}
     #endif
}
#endif
#endif
#if 0

//-------------------------------------------------------------------------------------------------
/// Get tuner lock status
/// @param eFE                      \b IN: Frontend id
/// @return TRUE:  Success
/// @return FALSE: Fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_DigiTuner_GetLock()
{
    MS_BOOL                bRet = FALSE;

    ENTRY();

#if   (FRONTEND_DEMOD_TYPE == DEMOD_PLAYCARD)
    bRet = TRUE;
#elif (FRONTEND_DEMOD_TYPE == DEMOD_MSDVBC)
    MDrv_Dmd_GetLock(&bRet);
#elif (FRONTEND_DEMOD_TYPE == DEMOD_LGS_8G52)
    MDrv_OfdmDmd_GetLock(&bRet);
#else
    MDrv_CofdmDmd_GetLock(&bRet);
#endif
    DEMOD_LOCK_LED_ONOFF(bRet);

    RETURN(bRet);
}

#endif

#if 0




//-------------------------------------------------------------------------------------------------
/// Get tuner BER
/// @param pu32BER                  \b OUT: Bit error ratio (n * 2^-32)
/// @return TRUE:  Success
/// @return FALSE: Fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_DigiTuner_GetBER(float *pfltBER)
{
    ENTRY();

#if   (FRONTEND_DEMOD_TYPE == DEMOD_PLAYCARD)
    *pfltBER = 0;
#elif (FRONTEND_DEMOD_TYPE == DEMOD_MSDVBC)
    MDrv_Dmd_GetBER(pfltBER);
#elif (FRONTEND_DEMOD_TYPE == DEMOD_LGS_8G52)
    MDrv_OfdmDmd_GetBER(pfltBER);
#else
    MDrv_CofdmDmd_GetBER(pfltBER);
#endif

    //DBG_M("%s: %f\n", __FUNCTION__, *pfltBER);

    RETURN(TRUE);
}


//-------------------------------------------------------------------------------------------------
/// Get tuner Signal Power Strength
/// @param pu8PWR                   \b OUT: Signal power strength
/// @return TRUE:  Success
/// @return FALSE: Fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_DigiTuner_GetPWR(MS_S16* ps16PWR)
{
    MS_S32  s32PWR = -97;

    ENTRY();

#if   (FRONTEND_DEMOD_TYPE == DEMOD_PLAYCARD)
    s32PWR = -100;
#elif (FRONTEND_DEMOD_TYPE == DEMOD_MSDVBC)
    if (MDrv_Dmd_GetPWR(&s32PWR) == FALSE)
    {
        RETURN(FALSE);
    }
#elif (FRONTEND_DEMOD_TYPE == DEMOD_LGS_8G52)
    if (MDrv_OfdmDmd_GetPWR(&s32PWR) == FALSE)
    {
        RETURN(FALSE);
    }
#else
    if (MDrv_CofdmDmd_GetPWR(&s32PWR) == FALSE)
    {
        RETURN(FALSE);
    }
#endif

    *ps16PWR = (MS_S16)(s32PWR);
    //DBG_M("%s: %d dBm\n", __FUNCTION__, *ps16PWR);

    RETURN(TRUE);
}

#endif

//-------------------------------------------------------------------------------------------------
/// Get tuner parameter setting
/// @param eFE                      \b IN: Frontend id
/// @param pstParam                 \b OUT: TPS carrier parameters
/// @return TRUE:  Success
/// @return FALSE: Fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_DigiTuner_GetTPSInfo(MS_FE_CARRIER_PARAM* pParam)
{
    ENTRY();

    // Get current frequency
    pParam->u32Frequency = _tunerParam.u32Frequency;

    // Update demodulator tuned parameter
    memcpy(pParam, &_tunerParam, sizeof(MS_FE_CARRIER_PARAM));

    RETURN(TRUE);
}
#if 0
MS_BOOL MApi_DigiTuner_GetRollOff(EN_SAT_ROLL_OFF_TYPE *pRollOff)
{
    MS_BOOL bRet = FALSE;
    ENTRY();

    bRet = MDrv_CofdmDmd_GetRollOff((MS_U8*)pRollOff);

    RETURN(bRet);
}
#endif
MS_BOOL MApi_DigiTuner_GetSatInfo(MS_SAT_PARAM* pSatInfo)
{
    ENTRY();

    memcpy(pSatInfo, &_stSATParam, sizeof(MS_SAT_PARAM));

    RETURN(TRUE);
}

MS_BOOL MApi_DigiTuner_GetCurrentLOF(MS_U16* pLOF)
{
    ENTRY();

    if(bIsHiLOF)
    {
           *pLOF = _stSATParam.u16HiLOF;
    }
    else
    {
           *pLOF = _stSATParam.u16LoLOF;
    }

    RETURN(TRUE);
}

//---------------------------
// Function For Satellite
//----------------------------
MS_BOOL MApi_DigiTuner_Satellite_Set22K(MS_BOOL b22KOn)
{
     MS_BOOL bRet = TRUE;
     ENTRY();
     bRet = MDrv_DiSEqC_Set22kOnOff(b22KOn);
     RETURN(bRet);
}

//---------------------------
// Function For Blind scan
//----------------------------
#if 0
MS_BOOL MApi_DigiTuner_DiSEqC_SwitchPort(MS_U8 u8Port,MS_BOOL bUnCommited)
{

      MS_BOOL bRet = TRUE;
      ENTRY();
      MDrv_DiSEqC_Set22kOnOff(FALSE);
      bRet = _DiSEqC_SwitchPort(u8Port,bUnCommited);
      if(_stSATParam.e22KOnOff == EN_22K_OFF )
       {
             MDrv_DiSEqC_Set22kOnOff(FALSE);
       }
       else if(_stSATParam.e22KOnOff == EN_22K_ON)
       {
             MDrv_DiSEqC_Set22kOnOff(TRUE);
       }
       else
       {
           if( bIsHiLOF == FALSE )
           {
               MDrv_DiSEqC_Set22kOnOff(FALSE);
           }
           else
           {
               MDrv_DiSEqC_Set22kOnOff(TRUE);
           }
      }
      RETURN(bRet);
}

#endif

#endif
static MS_BOOL _DigiTuner_DiSEqC_SendCmd(MS_U8* pCmd,MS_U8 u8CmdSize)
{
	MS_BOOL bRet = TRUE;

	bRet = MDrv_DiSEqC_SendCmd(pCmd,u8CmdSize);
	return bRet;
}

static MS_BOOL _DiSEqC_GotoSatPosition(MS_U8 u8Pos)
{
	MS_U8 u8Cmd[]={0xE0,0x31,0x6B,u8Pos};
	u8Pos &= DISEQC12_USALS_POSITION_MASK;
	if(u8Pos == 0)
	{
		return FALSE;
	}
	_stSATParam.u8Position = u8Pos;
	return  _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
}

MS_BOOL MApi_DigiTuner_DiSEqC_GoSatPos(MS_U8 u8SatPos)
{
	u8SatPos &= DISEQC12_USALS_POSITION_MASK;
	return _DiSEqC_GotoSatPosition(u8SatPos);
}

void MApi_Demod_HWReset(MS_BOOL bReset)
{
	DEMOD_RESET(bReset);
}
MS_BOOL MApi_DigiTuner_MPEGGetLock()
{
    MS_BOOL  bRet = FALSE;
    MDrv_CofdmDmd_GetLock(&bRet);
    return bRet;
}
static MS_BOOL _DiSEqC_SwitchPort(MS_U8 u8Port,MS_BOOL bUncommitted)
{
    MS_U8 u8Cmd[]={0xE0,0x10,0x38,0xF0};

    if(bUncommitted)
    {
      u8Cmd[2] = 0x39;
    }
    u8Cmd[3] = 0xF0+u8Port;

   return  _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
}

static MS_BOOL _MultiDiSEqc_SwitchPort(MS_SAT_PARAM stSATParam,MS_U8 u8Polarity,MS_BOOL bflagIsHiLOF)
{
     MS_U8 u8SubPort = 0;

     if(u8Polarity == 0)
          u8SubPort |= 0x02;
     if(bflagIsHiLOF)
          u8SubPort |= 0x01;
     switch(stSATParam.eSwt10Port)
     {
          case EN_SWT_PORT_1:
                u8SubPort = u8SubPort;
                break;
          case EN_SWT_PORT_2:
                u8SubPort = 0x04+ u8SubPort;
                break;
          case EN_SWT_PORT_3:
                u8SubPort = 0x08+ u8SubPort;
                break;
          case EN_SWT_PORT_4:
                u8SubPort = 0x0C+ u8SubPort;
                break;
          default:
                break;
     }

     if(stSATParam.eSwt11Port >= EN_SWT_PORT_1 && stSATParam.eSwt11Port <= EN_SWT_PORT_16)
     {
          _DiSEqC_SwitchPort((MS_U8)(stSATParam.eSwt11Port)-1,TRUE);
     }
     MsOS_DelayTask(50);
     if(stSATParam.eSwt10Port >= EN_SWT_PORT_1 && stSATParam.eSwt10Port <= EN_SWT_PORT_4)
     {
          _DiSEqC_SwitchPort(u8SubPort,FALSE);
     }
     return TRUE;
}

MS_BOOL  _DigiTuner_SwitchSatellite(MS_SAT_PARAM stSATParam,MS_U8 u8Polarity,MS_BOOL bflagIsHiLOF)
{
	// switch the port
	MDrv_DiSEqC_Set22kOnOff(FALSE);
	MsOS_DelayTask(30);

	switch(stSATParam.eDiseqcLevel)
	{
		default:
		case EN_DISEQC_LVL_OFF:
		{
			break;
		}

		case EN_DISEQC_LVL_10:
		{
			MS_U8 u8SubPort = 0;
			
			if(u8Polarity == 0)
			{
				u8SubPort |= 0x02;
			}
			if(bflagIsHiLOF)
			{
				u8SubPort |= 0x01;
			}
			switch(stSATParam.eSwt10Port)
			{
				case EN_SWT_PORT_1:
					u8SubPort = u8SubPort;
					break;
				case EN_SWT_PORT_2:
					u8SubPort = 0x04+ u8SubPort;
					break;
				case EN_SWT_PORT_3:
					u8SubPort = 0x08+ u8SubPort;
					break;
				case EN_SWT_PORT_4:
					u8SubPort = 0x0C+ u8SubPort;
					break;
				default:
					break;
			}
			if(stSATParam.eSwt10Port >= EN_SWT_PORT_1 && stSATParam.eSwt10Port <= EN_SWT_PORT_4)
			{
				printf("\r\n_________eSwt10Port=%d",stSATParam.eSwt10Port);
				_DiSEqC_SwitchPort(u8SubPort,FALSE);
			}
			break;
		}
		case EN_DISEQC_LVL_11:
		{
			if(stSATParam.eSwt11Port >= EN_SWT_PORT_1 && stSATParam.eSwt11Port <= EN_SWT_PORT_16)
			{
				_DiSEqC_SwitchPort((MS_U8)(stSATParam.eSwt11Port)-1,TRUE);
			}
			break;
		}

		case EN_DISEQC_LVL_12:
		case EN_DISEQC_LVL_13:
		{
			if((_stSATParam.u8Position&DISEQC12_USALS_POSITION_MASK) != (stSATParam.u8Position&DISEQC12_USALS_POSITION_MASK))
			{
				_DiSEqC_GotoSatPosition(stSATParam.u8Position&DISEQC12_USALS_POSITION_MASK);
			}
			break;
		}

		case EN_DISEQC_LVL_MULTI:
		{
			_MultiDiSEqc_SwitchPort(stSATParam,u8Polarity,bIsHiLOF);
			break;
		}
	}

    MsOS_DelayTask(50);
    if(stSATParam.eToneburstType == EN_TONEBURST_1)
	{
		MDrv_DiSEqC_SetTone(1);
	}
	else if(stSATParam.eToneburstType == EN_TONEBURST_0)
	{
		MDrv_DiSEqC_SetTone(0);
	}
    MsOS_DelayTask(50);

	if(stSATParam.e22KOnOff == EN_22K_OFF )
	{
		MDrv_DiSEqC_Set22kOnOff(FALSE);
	}
	else if(stSATParam.e22KOnOff == EN_22K_ON)
	{
		MDrv_DiSEqC_Set22kOnOff(TRUE);
	}
	else
	{
		if( bflagIsHiLOF == FALSE )
		{
			MDrv_DiSEqC_Set22kOnOff(FALSE);
		}
		else
		{
			MDrv_DiSEqC_Set22kOnOff(TRUE);
		}
	}

	return TRUE;
}

static  MS_BOOL  _DigiTuner_CalculateIF(MS_SAT_PARAM stSATParam,DTVPROGRAMID_M *pParam,CofdmDMD_Param* pdmdParam)
{
	MS_S32 s32Freq;
	printf("\r\nu16LoLOF=%d,u16HiLOF=%d  [%d]",stSATParam.u16LoLOF,stSATParam.u16HiLOF,pParam->u8Polarity);
	if(stSATParam.u16LoLOF == stSATParam.u16HiLOF)
	{
		printf("\r\naaaaaaaaaa");
		s32Freq  = pParam->u32S2Frequency;
		s32Freq -= stSATParam.u16LoLOF;
		if(s32Freq < 0) s32Freq = -s32Freq;
		pdmdParam->u32TunerFreq = s32Freq;
		bIsHiLOF = FALSE;
	}
	else // 2LOF
	{
		if(stSATParam.u16LoLOF <MAX_C_LOF_FREQ)  // c band
		{
			printf("\r\nbbbbbbbbb");
			s32Freq  = pParam->u32S2Frequency;
			if(pParam->u8Polarity == 0) //H ---> use low LOF
			{
				bIsHiLOF = FALSE;
				pdmdParam->u32TunerFreq = abs(stSATParam.u16LoLOF - s32Freq);
			}
			else   //V --->use high LOF
			{
				bIsHiLOF = TRUE;
				pdmdParam->u32TunerFreq =	abs(stSATParam.u16HiLOF - s32Freq) ;
			}
		}
		else //Ku band
		{
			printf("\r\ncccccccccc");
			MS_U32 u32MidFreq;
			s32Freq  = pParam->u32S2Frequency;
			u32MidFreq =	abs(s32Freq - stSATParam.u16LoLOF) ;
			if( s32Freq <= 11700)//universal (9750/10600)
			{
				bIsHiLOF = FALSE;
				pdmdParam->u32TunerFreq = u32MidFreq;
			}
			else
			{
				bIsHiLOF = TRUE;
				pdmdParam->u32TunerFreq =	abs(s32Freq - stSATParam.u16HiLOF) ;
			}
		}
	}
	return TRUE;
}

static MS_BOOL _DigiTuner_SetLNBPower(MS_EN_LNBPWR_ONOFF enLNBPower,MS_U8 u8Polarity,MS_BOOL bPorInvert)
{
#if(DISH_TYPE!=DISH_NONE)
	switch(enLNBPower)
    {
    	default:
    	case  EN_LNBPWR_13OR18V:
    	{
			if( (!bPorInvert && u8Polarity) || (bPorInvert && u8Polarity == 0)) //V
         	{
				return MDrv_Dish_SetLNBPower(EN_LNBPWR_TYPE_13V);
         	}
			else  //H
         	{
				return MDrv_Dish_SetLNBPower(EN_LNBPWR_TYPE_18V);
         	}
         	break;
    	}

    	case EN_LNBPWR_OFF:
    	{
			return MDrv_Dish_SetLNBPower(EN_LNBPWR_TYPE_OFF);
        	break;
    	}

    	case EN_LNBPWR_13V:
      	{
			return MDrv_Dish_SetLNBPower(EN_LNBPWR_TYPE_13V);
       		break;
     	}
     	case EN_LNBPWR_18V:
     	{
			return MDrv_Dish_SetLNBPower(EN_LNBPWR_TYPE_18V);
         	break;
     	}
	}
	MsOS_DelayTask(100);
#else
    UNUSED(enLNBPower);
    UNUSED(u8Polarity);
    UNUSED(bPorInvert);
#endif
	return TRUE;
}

MS_BOOL MApi_DigiTuner_Tune2RfCh(MS_SAT_PARAM stSatInfor,DTVPROGRAMID_M *pParam, EN_FE_TUNE_MODE eMode)
{
	CofdmDMD_Param    dmdParam;
	eMode=eMode;

	bIsHiLOF = FALSE;
	_DigiTuner_CalculateIF(stSatInfor,pParam,&dmdParam);
#if (SUPPORT_UNICABLE)
	if (_stSATParam.eLNBType != EN_LNBTYPE_UNICABLE)
#endif
	{
		_DigiTuner_SetLNBPower(stSatInfor.eLNBPwrOnOff,pParam->u8Polarity,stSatInfor.bPorInvert);
	}
	_DigiTuner_SwitchSatellite(stSatInfor,pParam->u8Polarity,bIsHiLOF);
	_tunerParam = *pParam; //Must move here
	_stSATParam = stSatInfor;

	//printf("\r\n dmdParam= frequency [%d] u16SymbolRate [%d].\n", dmdParam.u32TunerFreq, pParam->u16SymbolRate);
	dmdParam.u32SymbolRate = pParam->u16SymbolRate;
	dmdParam.u32SymbolRate *= 1000;

#if (SUPPORT_UNICABLE)
	if (_stSATParam.eLNBType == EN_LNBTYPE_UNICABLE)
	{
		FrontEnd_DVBS2_Set(_tunerParam.u32S2Frequency, _tunerParam.u16SymbolRate, _tunerParam.u8Polarity, &_stSATParam);
	}
	else
#endif
	{
		if (MDrv_CofdmDmd_Restart(&dmdParam) == FALSE)
		{
			return FALSE;
		}
	}
	return TRUE;
}
MS_BOOL MApi_DigiTuner_GetMaxLockTime(EN_FE_TUNE_MODE eMode, MS_U32 *u32LockTime)
{
	if(_tunerParam.u16SymbolRate<3000)
	{
		*u32LockTime=3000*2;
	}
	else if(_tunerParam.u16SymbolRate<5000)
	{
		*u32LockTime=2000*2;
	}
	else if(_tunerParam.u16SymbolRate<10000)
	{
		*u32LockTime=1500*2;
	}
	else
	{
		*u32LockTime=1000*2;
	}
	if (FE_TUNE_AUTO == eMode && *u32LockTime < AUTO_TUNE_TIMEOUT)
	{
		*u32LockTime = AUTO_TUNE_TIMEOUT;
	}

	return TRUE;
}
MS_BOOL MApi_DigiTuner_TPSGetLock()
{
    MS_BOOL  bRet = FALSE;
    MDrv_CofdmDmd_GetLock(&bRet);
    return bRet;
}
MS_BOOL MApi_DigiTuner_GetRFOffset(MS_S16 *ps16RFOffset)
{
    MS_BOOL bRet = FALSE;
    bRet = MDrv_CofdmDmd_GetRFOffset(ps16RFOffset);
    return bRet;
}
MS_BOOL MApi_DigiTuner_BlindScan_Start(MS_SAT_PARAM stSATParam,MS_U8 u8Polarity,MS_BOOL bFlagIsHiLOF)
{
	MS_U16 u16StartFreq = IF_MIN_FREQ, u16EndFreq = IF_MAX_FREQ;
	MS_U16 u16maxfreq,u16minfreq,u16TempFreq;
	_DigiTuner_SwitchSatellite(stSATParam,u8Polarity,bFlagIsHiLOF);
	printf("stSATParam.eLNBPwrOnOff = %d\n", stSATParam.eLNBPwrOnOff);
	_DigiTuner_SetLNBPower(stSATParam.eLNBPwrOnOff,u8Polarity,stSATParam.bPorInvert);
	_stSATParam = stSATParam;
	if(stSATParam.u16LoLOF != stSATParam.u16HiLOF) // 2LOF
	{
		if(stSATParam.u16HiLOF <MAX_C_LOF_FREQ)  // c band
		{
			if(bFlagIsHiLOF)
			{
				u16StartFreq = IF_MIDDLE_FREQ;
				u16EndFreq = IF_MAX_FREQ;
			}
			else
			{
				u16StartFreq = IF_MIN_FREQ;
				u16EndFreq = IF_MIDDLE_FREQ;
			}
		}
		else  // Ku band
		{
			if( stSATParam.u16HiLOF>=stSATParam.u16LoLOF)
			{
				u16maxfreq = stSATParam.u16HiLOF;
				u16minfreq = stSATParam.u16LoLOF;
			}
			else
			{
				u16maxfreq = stSATParam.u16LoLOF;
				u16minfreq = stSATParam.u16HiLOF;
			}

			u16TempFreq = u16maxfreq;
			u16maxfreq = u16minfreq + IF_MAX_FREQ;
			u16minfreq =  u16TempFreq + IF_MIN_FREQ;

			if(u16maxfreq > u16minfreq)
			{
				u16minfreq = (u16maxfreq - u16minfreq) /2;
			}
			else
			{
				u16minfreq = 0;
			}

			if(bFlagIsHiLOF)
			{
				u16StartFreq = IF_MIN_FREQ + u16minfreq;
				u16EndFreq = IF_MAX_FREQ;
				if(u16minfreq > 0)
				{
					u16StartFreq -= IF_OFFSET_FREQ;
				}
			}
			else
			{
				u16StartFreq = u16StartFreq;
				u16EndFreq = IF_MAX_FREQ - u16minfreq;
				if(u16minfreq > 0)
				{
					u16EndFreq += IF_OFFSET_FREQ;
				}
			}

			if( stSATParam.u16HiLOF < stSATParam.u16LoLOF)
			{
				u16minfreq = u16StartFreq;
				u16StartFreq = u16EndFreq;
				u16EndFreq = u16minfreq;
			}
		}
		MDrv_DiSEqC_Set22kOnOff(bFlagIsHiLOF);
	}
	else
	{
		if(stSATParam.e22KOnOff == EN_22K_ON)
		{
			MDrv_DiSEqC_Set22kOnOff(TRUE);
		}
		else
		{
			MDrv_DiSEqC_Set22kOnOff(FALSE);
		}
	}
	//printf("\r\n~~~~~~u16StartFreq=%d,u16EndFreq=%d",u16StartFreq,u16EndFreq);
#if(SUPPORT_UNICABLE)
	if(stSATParam.eLNBType == EN_LNBTYPE_UNICABLE)
		return MDrv_CofdmDmd_BlindScan_Start(stSATParam.u16IFreq,u16EndFreq,TRUE);
	else
#endif
	return MDrv_CofdmDmd_BlindScan_Start(u16StartFreq,u16EndFreq,FALSE);
}

MS_BOOL MApi_DigiTuner_BlindScan_NextFreq(MS_BOOL* bBlindScanEnd,MS_U8* u8Progress)
{
     MS_BOOL bRet = TRUE;
     _tunerParam.u32S2Frequency = 0;// force to set tuner after blindscan
     bRet = MDrv_CofdmDmd_BlindScan_NextFreq(bBlindScanEnd,u8Progress);
     return bRet;
}
MS_BOOL MApi_DigiTuner_BlindScan_WaitCurFeqFinished(MS_U8* u8Progress,MS_U8* u8FindNum)
{
     return MDrv_CofdmDmd_BlindScan_WaitCurFreqFinished(u8Progress,u8FindNum);
}

MS_BOOL MApi_DigiTuner_BlindScan_GetChannel(MS_U16 u16ReadStart,MS_U16* u16TPNum,DTVPROGRAMID_M *pTPTable)
{
     MS_BOOL bRet = TRUE;
     MS_U16 idx;
     DTVPROGRAMID_M TPList[MAX_TPSOFSAT];

     memset(TPList, 0, sizeof(TPList));

     bRet = MDrv_CofdmDmd_BlindScan_GetChannel(u16ReadStart,u16TPNum,TPList);
     if(bRet && *u16TPNum > 0)
     {
          for(idx = 0;idx < *u16TPNum;idx ++)
          {
                pTPTable[idx].u32S2Frequency = TPList[idx].u32S2Frequency;
                pTPTable[idx].u16SymbolRate = TPList[idx].u16SymbolRate;
          }
     }
     return bRet;
}
MS_BOOL MApi_DigiTuner_BlindScan_Cancel(void)
{
     MS_BOOL bRet = TRUE;
     bRet = MDrv_CofdmDmd_BlindScan_Cancel();
     return bRet;
}

MS_BOOL MApi_DigiTuner_BlindScan_End(void)
{
     MS_BOOL bRet = TRUE;
     bRet = MDrv_CofdmDmd_BlindScan_End();
     return bRet;
}

MS_BOOL MApi_DigiTuner_Satellite_SetLNBPower(MS_EN_LNBPWR_ONOFF enLNBPowe,MS_U8 u8Polarity,MS_BOOL bPorInvert)
{
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_SetLNBPower(enLNBPowe,u8Polarity,bPorInvert);
     return (bRet);
}
#define DEFAULT_SNR_MIN 0
#define DEFAULT_SNR_MAX 35

void MApi_DigiTuner_GetSNR(MS_U16* pu16SNR)
{
    MS_U32  u32SNR = 0;
    if (MDrv_CofdmDmd_GetSNR(&u32SNR) != TRUE)
    {
        u32SNR = 0;
    }
    *pu16SNR = (MS_U16)(u32SNR);
}

MS_U16 MApi_DigiTuner_getCurRFSignalSNR_Persent(void)
{
    MS_U16 _u16snr = 0;
    MApi_DigiTuner_GetSNR(&_u16snr);
    return _u16snr * 100 / (DEFAULT_SNR_MAX - DEFAULT_SNR_MIN);
}
MS_BOOL MApi_DigiTuner_DiSEqC_MotorConinuteWest(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x69,0x00};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return bRet;
}
MS_BOOL MApi_DigiTuner_DiSEqC_MotorConinuteEast(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x68,0x00};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}



MS_BOOL MApi_DigiTuner_DiSEqC_MotorStepEast(MS_U8 u8Step)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x68,0xFE};
     MS_BOOL bRet = TRUE;
     u8Cmd[3] = 0xFF - u8Step;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}

MS_BOOL MApi_DigiTuner_DiSEqC_MotorStepWest(MS_U8 u8Step)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x69,0xFE};
     MS_BOOL bRet = TRUE;
     u8Cmd[3] = 0xFF - u8Step;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}

MS_BOOL MApi_DigiTuner_DiSEqC_HaltMotor(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x60};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}
MS_BOOL MApi_DigiTuner_DiSEqC_Reset(void)
{
       MS_U8 u8Cmd[]={0xE0,0x31,0x00};
       MS_BOOL bRet = TRUE;
       bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
       return (bRet);
}
MS_BOOL MApi_DigiTuner_DiSEqC_SetEastLimit(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x66};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}

MS_BOOL MApi_DigiTuner_DiSEqC_SetWestLimit(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x67};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
    return (bRet);
}

MS_BOOL MApi_DigiTuner_DiSEqC_DisableLimit(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x63};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}

MS_BOOL MApi_DigiTuner_DiSEqC_GoReferencePoint(void)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x6B,0x00};
     MS_BOOL bRet = TRUE;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
    return (bRet);
}

static MS_S16 _CulculateAzimuth(MS_U16 u16SatLongitude,MS_S16 s16MyLongitude,MS_S16 s16MyLatitude)
{
	double P, Ue, Us, az, x, el, Azimuth;
	MS_S16 s16Azimuth;

	P = s16MyLatitude/10 + ((double)(s16MyLatitude%10)*0.1);
	P = P*TO_RADS;           // Earth Station Latitude
	Ue = s16MyLongitude/10 + ((double)(s16MyLongitude%10)*0.1);
	Ue = Ue*TO_RADS;           // Earth Station Longitude

	if(P < 0)
	{
		P = -P;
	}

	if(u16SatLongitude >1800)
	{
		u16SatLongitude = 3600 - u16SatLongitude;
		Us = -( u16SatLongitude/10 + ((double)(u16SatLongitude%10)*0.1));
	}
	else
	{
		Us = u16SatLongitude/10 + ((double)(u16SatLongitude%10)*0.1);
	}
	Us = Us*TO_RADS;          // Satellite Longitude

    // Fix coverity
	printf(" sin90=%lf\n", sin( 90 ) );
	printf(" tan90=%lf\n", sin( 45 ) );

	az = M_PI+atan( tan( Us-Ue )/sin( P ) );
	x = acos( cos(Us-Ue)*cos(P) );
	el = atan( ( cos( x )-0.1513 )/sin( x ) );
	Azimuth = atan( ( -cos(el)*sin(az) )/( sin(el)*cos(P)-cos(el)*sin(P)*cos(az)) )* TO_DEC;
	s16Azimuth = (MS_S16)((Azimuth+0.05)*10);

	if(s16MyLatitude < 0)
	{
		s16Azimuth = -s16Azimuth;
	}
	return s16Azimuth;
}

static MS_BOOL _DiSEqC_GotoX(MS_U16 u16SatLongitude,MS_S16 s16MyLongitude,MS_S16 s16MyLatitude)
{
	MS_U8 u8Cmd[5]={0xE0,0x31,0x6E,0x00,0x00};
	MS_U8 DecimalLookup[10] = { 0x00, 0x02, 0x03, 0x05, 0x06, 0x08, 0x0A, 0x0B, 0x0D, 0x0E };
	MS_S16 s16Azimuth;
	MS_U16 u16Integer,u16Fraction;

	s16Azimuth = _CulculateAzimuth(u16SatLongitude,s16MyLongitude,s16MyLatitude);
	printf("\n s16Azimuth = %d",s16Azimuth);
	if ( s16Azimuth > 0 )
		u8Cmd[3] = 0xE0;    // East
	else
		u8Cmd[3] = 0xD0;      // West

	u16Integer = abs( s16Azimuth );
	u16Fraction = u16Integer%10;
	u16Integer = u16Integer /10;

	while (u16Integer >= 16)
	{
		u8Cmd[3]++;
		u16Integer-= 16;
	}
	while (u16Integer >= 1)
	{
		u8Cmd[4]+=0x10;
		u16Integer--;
	}
	u8Cmd[4]+= DecimalLookup[u16Fraction];
	printf("\nu8Cmd[3] = 0x%X",u8Cmd[3]);
	printf("\nu8Cmd[4] = 0x%X",u8Cmd[4]);

	return _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
}

MS_BOOL MApi_DigiTuner_DiSEqC_GotoX(MS_U16 u16SatLongitude,MS_S16 s16MyLongitude,MS_S16 s16MyLatitude)
{
     MS_BOOL bRet = TRUE;
    bRet = _DiSEqC_GotoX(u16SatLongitude,s16MyLongitude,s16MyLatitude);
    return (bRet);
}

MS_BOOL MApi_DigiTuner_DiSEqC_SaveSatPos(MS_U8 u8SatPos)
{
     MS_U8 u8Cmd[]={0xE0,0x31,0x6A,u8SatPos};
     MS_BOOL bRet = TRUE;
     u8SatPos &= DISEQC12_USALS_POSITION_MASK;
     u8Cmd[3] = u8SatPos;
     bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd,sizeof(u8Cmd));
     return (bRet);
}
WORD MApi_GetLocationNum(void)
{
     return (sizeof(SetSATLocation)/sizeof(DISH_LOCATION));
}
void Int_DigiTuner_Tp_Sat(void)
{
	_stSATParam.u8Position=0;
	_tunerParam.SatelliteId=0xff;
	_tunerParam.u32S2Frequency=0xffff;
}
//-------------------------------------------------------------------------------------------------
/// Get tuner Signal Power Strength
/// @param pu8PWR                   \b OUT: Signal power strength
/// @return TRUE:  Success
/// @return FALSE: Fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_DigiTuner_GetPWR(MS_S16* ps16PWR)
{
    MS_S32  s32PWR = -97;

    if (MDrv_CofdmDmd_GetPWR(&s32PWR) == FALSE)
    {
        return (FALSE);
    }

    *ps16PWR = (MS_S16)(s32PWR);
    printf("%s: %d dBm\n", __FUNCTION__, *ps16PWR);

    return (TRUE);
}
#if (SUPPORT_UNICABLE)
MS_BOOL MApi_DigiTuner_DiSEqC_SendCmd(EN_DVBS_ACTION_TYPE eDiseqcCmd, U16 u16Param1, S16 s16Param2, S16 s16Param3)
{
    U8 u8Cmd[6] = {0};
    U8 u8CmdSize = 0;
    U8 u8Param;
    BOOL b22KOn, bRet = TRUE;
    BOOL bUnicableCmd = FALSE;

    u8Param = u16Param1 % 0x100;
    switch(eDiseqcCmd)
    {
        //UNICABLE
        case E_ACT_DISEQC_ODU_CHCHG:
        {
			printf("[Gaven],[CMD][E_ACT_DISEQC_ODU_CHCHG]\n");

            bUnicableCmd = TRUE;
            U8 u8UBand = (u16Param1>>8)&0x7;
            U8 u8Bank =  u16Param1&0x7;
            U16 u16Tune = ((U16)s16Param2)&0x3FF;

            u8Cmd[0] = DISEQC_FRM;
            u8Cmd[1] = DISEQC_ADR_SW_ALL; //DISEQC_ADR_ALL; //GavenYang
            u8Cmd[2] = DISEQC_CMD_ODU_CHCHG;
            u8Cmd[3] = (u8UBand<<5) | (u8Bank<<2) | (u16Tune>>8);
            u8Cmd[4] = (U8)u16Tune;
            u8CmdSize = 5;
            if (s16Param3)
            {
                u8Cmd[2] = DISEQC_CMD_ODU_CHCHG_MDU;
                u8Cmd[5] = 0;
                u8CmdSize = 6;
            }
            break;
        }
        case E_ACT_DISEQC_ODU_PWROFF:
        {
            printf("[Gaven],[CMD][E_ACT_DISEQC_ODU_PWROFF]\n");
            bUnicableCmd = TRUE;
            U8 u8UBand = u16Param1&0x7;
            u8Cmd[0] = DISEQC_FRM;
            u8Cmd[1] = DISEQC_ADR_ALL;
            u8Cmd[2] = DISEQC_CMD_ODU_PWROFF;
            u8Cmd[3] = u8UBand<<5;
            u8Cmd[4] = 0;
            u8CmdSize = 5;
            if (s16Param3)
            {
                u8Cmd[2] = DISEQC_CMD_ODU_PWROFF_MDU;
                u8Cmd[5] = 0;
                u8CmdSize = 6;
            }
            break;
        }
        case E_ACT_DISEQC_ODU_UBXSIGNAL:
        {
            printf("[Gaven],[CMD][E_ACT_DISEQC_ODU_UBXSIGNAL]\n");
            bUnicableCmd = TRUE;
            u8Cmd[0] = DISEQC_FRM;
            u8Cmd[1] = DISEQC_ADR_ALL;
            u8Cmd[2] = DISEQC_CMD_ODU_UBXSIGNAL;
            u8Cmd[3] = 0;
            u8Cmd[4] = 0;
            u8CmdSize = 5;
            if (s16Param3)
            {
                u8Cmd[2] = DISEQC_CMD_ODU_UBXSIGNAL_MDU;
                u8Cmd[5] = 0;
                u8CmdSize = 6;
            }
            break;
        }
        case E_ACT_DISEQC_ODU_CONFIG:
        {
            printf("[Gaven],[CMD][E_ACT_DISEQC_ODU_CONFIG]\n");
            bUnicableCmd = TRUE;
            U8 u8UBand = u16Param1&0x7;
            u8Cmd[0] = DISEQC_FRM;
            u8Cmd[1] = DISEQC_ADR_ALL;
            u8Cmd[2] = DISEQC_CMD_ODU_CONFIG;
            u8Cmd[3] = (u8UBand<<5) | 0x1;
            u8Cmd[4] = (U8)s16Param2;
            u8CmdSize = 5;
            if (s16Param3)
            {
                u8Cmd[2] = DISEQC_CMD_ODU_CONFIG_MDU;
                u8Cmd[5] = 0;
                u8CmdSize = 6;
            }
            break;
        }
        case E_ACT_DISEQC_ODU_LOFREQ:
        {
            printf("[Gaven],[CMD][E_ACT_DISEQC_ODU_LOFREQ]\n");
            bUnicableCmd = TRUE;
            U8 u8UBand = u16Param1&0x7;
            u8Cmd[0] = DISEQC_FRM;
            u8Cmd[1] = DISEQC_ADR_ALL;
            u8Cmd[2] = DISEQC_CMD_ODU_LOFREQ;
            u8Cmd[3] = (u8UBand<<5) | 0x2;
            u8Cmd[4] = (U8)s16Param2;
            u8CmdSize = 5;
            if (s16Param3)
            {
                u8Cmd[2] = DISEQC_CMD_ODU_LOFREQ_MDU;
                u8Cmd[5] = 0;
                u8CmdSize = 6;
            }
            break;
        }
        default:
            bRet = FALSE;
            break;
    }
    if(bRet)
    {
        bRet &= MDrv_DiSEqC_Get22kOnOff(&b22KOn);
    }
    if(bRet)
    {
        MDrv_DiSEqC_Set22kOnOff(FALSE);

        {
            printf("\n[Gaven], Cmd 0x%x,0x%x,0x%x,0x%x,0x%x, 0x%x, size = %d\n",u8Cmd[0], u8Cmd[1], u8Cmd[2], u8Cmd[3], u8Cmd[4], u8Cmd[5], u8CmdSize);

            if (bUnicableCmd)
            {
                //4ms < td < 22ms
				_DigiTuner_SetLNBPower(EN_LNBPWR_18V,_tunerParam.u8Polarity,0);
            }
            bRet = _DigiTuner_DiSEqC_SendCmd(u8Cmd, u8CmdSize);
        }

        if (bUnicableCmd)
        {
           MsOS_DelayTask(100); //MsOS_DelayTask(40); //10ms. 2ms < ta < 60ms
           _DigiTuner_SetLNBPower(EN_LNBPWR_13V,_tunerParam.u8Polarity,0);
        }
        MDrv_DiSEqC_Set22kOnOff(b22KOn);

    }
    return bRet;
}

MS_BOOL ODU_ChChg(MS_U8 u8UbId, MS_U8 u8Bank, MS_U16 u16TuneWord, MS_BOOL bMDU)
{
    MApi_DigiTuner_DiSEqC_SendCmd(E_ACT_DISEQC_ODU_CHCHG, (MS_U16)((u8UbId<<8)|u8Bank), u16TuneWord, (MS_U16)bMDU);
    return TRUE;
}

void MApi_DigiTuner_Uni_SetFreq(void)
{
	MS_U32 m_u32Frequency;
	MDrv_CofdmDmd_BlindScan_GetCurrentFreq(&m_u32Frequency);
	S16 u16TuneWord = ((m_u32Frequency)/4) - 350;
	printf("[Gaven],[Unicable][%s] m_u32Frequency = %ld, TuningWord = %d\n", __FUNCTION__, m_u32Frequency, u16TuneWord);
	ODU_ChChg(0, 0, u16TuneWord, (U16)0);
}
#endif
/*
//-------------------------------------------------------------------------------------------------
/// Get tuner BER
/// @param pu32BER                  \b OUT: Bit error ratio (n * 2^-32)
/// @return TRUE:  Success
/// @return FALSE: Fail
//-------------------------------------------------------------------------------------------------
MS_BOOL MApi_DigiTuner_GetBER(float *pfltBER)
{
    MDrv_CofdmDmd_GetBER(pfltBER);

    printf("%s: %f\n", __FUNCTION__, *pfltBER);

    return (TRUE);
}*/

void MApi_DigiTuner_Get_CurSATInfo(MS_SAT_PARAM* pstSAT_PARAM)
{
    *pstSAT_PARAM = _stSATParam;
}

#endif


