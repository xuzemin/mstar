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

#ifndef _LGS_9X_H_
#define _LGS_9X_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "LGS_TYPES.h"
#include "LGS_DEMOD.h"


#define  LGS9XSECADDR1       0x3A
#define  LGS9XSECADDR2       0x3E

LGS_RESULT LGS9X_Init(DemodInitPara *para);
//LGS_RESULT LGS9X_CheckBCH(DEMOD_WORK_MODE workMode, UINT16 waitTime, UINT32 *pPkgCount, UINT32 *pPkgErr);
LGS_RESULT LGS9X_CheckLocked(DEMOD_WORK_MODE workMode, UINT8 *locked1, UINT8 *locked2, UINT16 waitms);
LGS_RESULT LGS9X_I2CEchoOn(void);
LGS_RESULT LGS9X_I2CEchoOff(void);
LGS_RESULT LGS9X_GetConfig(DEMOD_WORK_MODE workMode, DemodConfig *pDemodConfig);
LGS_RESULT LGS9X_SetConfig(DEMOD_WORK_MODE workMode, DemodConfig *pDemodConfig);
LGS_RESULT LGS9X_GetSignalQuality(DEMOD_WORK_MODE workMode, UINT16 *pSignalQuality);
LGS_RESULT LGS9X_GetSignalStrength(DEMOD_WORK_MODE workMode, UINT32 *pSignalStrength);
LGS_RESULT LGS9X_SoftReset(void);
void LGS9X_SetDtmbMode(void);//yanxi added 110723
U8 LGS9X_SetGPIO(BOOLEAN GPIO_staut1,BOOLEAN GPIO1eable,BOOLEAN GPIO_staut0,BOOLEAN GPIO0eable);
void LGS9X_GetRegistersForDebug(void);
U8 LGS9X_SetGPIO0(BOOLEAN GPIOFLG);
#ifdef __cplusplus
}
#endif

#endif
