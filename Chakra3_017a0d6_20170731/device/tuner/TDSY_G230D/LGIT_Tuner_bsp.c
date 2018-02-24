/****************************************************************************
*
* 							LG Innotek Co.,Ltd.
*
* Copyright (C) 2012, LG Innotek, Gwangju, Korea, All Rights Reserved.
*
* File: LGIT_Tuner_bsp.c
*
* version: 1.00.00
*
* Description: I2C function
*
* Description			Version		Date		Author
* ---------------------------------------------------------------------
* Create				1.00.00		2012.03.28	JH.KIM
****************************************************************************/

#define LGIT_DBG 0
#define LGIT_I2C_LOG 0

#include "LGIT_Tuner_bsp.h"
// #include "../LGIT_I2C.h" /* Porting : Modify I2C Header here */
// #include <windows.h> /* Porting : Modify Sleep Header here */
// #include <time.h> /* Porting : Modify Time Header here */

#ifdef __cplusplus
extern "C"
{
#endif

int I2cLogFlag = 0;

int LGIT_bsp_i2c_init(void)
{
	// return LGIT_I2cInit(0);  /* Porting : Modify I2C Init function here or return 0*/
	return 0;
}

int LGIT_bsp_i2c_write(unsigned char I2cAddr, unsigned char *pData, unsigned int nBytes)
{
	int result = 0;
#if LGIT_I2C_LOG    
	unsigned int i = 0;
#endif    
    result = (int)platform_I2CWrite(0, I2cAddr, NULL, 0, pData, nBytes);

	// result = LGIT_I2cWrite(I2cAddr, pData, nBytes); /* Porting :  Modify I2C Write function here */

#if LGIT_I2C_LOG
	I2cLogFlag = 1;
	LGIT_dbg("[Tuner][W] Addr: 0x%x, Bytes: %d\n[Tuner]", I2cAddr, nBytes);
	for(i=0; i<nBytes; i++)  
	{
		LGIT_dbg("Data[%d]: 0x%x, ", i, pData[i]);
	}
	LGIT_dbg("\n");
	I2cLogFlag = 0;
#endif

	return result;
}

int LGIT_bsp_i2c_read(unsigned char I2cAddr, unsigned char *pData, unsigned int nBytes)
{
	int result = 0;
#if LGIT_I2C_LOG    
	unsigned int i = 0;
#endif
	// result = LGIT_I2cRead(I2cAddr,pData,nBytes); /* Porting : Modify I2C Read function here */

    result = (int)platform_I2CRead(0, I2cAddr, NULL, 0, pData, nBytes);

#if LGIT_I2C_LOG
	I2cLogFlag = 1;
	LGIT_dbg("[Tuner][R] Addr: 0x%x, Bytes: %d\n[Tuner]", I2cAddr, nBytes);
	for(i=0; i<nBytes; i++)  
	{
		LGIT_dbg("Data[%d]: 0x%x, ", i, pData[i]);
	}
	LGIT_dbg("\n");
	I2cLogFlag = 0;
#endif

	return result;
}

void LGIT_sleep(unsigned int mSec)
{
	// Sleep(mSec);  /* Porting : Modify Sleep function here */
	platform_ms_delay(mSec);
}

int LGIT_time(void)
{
    return MsOS_GetSystemTime();
	// return (int)clock()*1000/CLOCKS_PER_SEC; /* Porting : Modify Time function here, return the system time in milliseconds */
}

void LGIT_dbg(const char *dbg, ...)
{
UNUSED(dbg);
#if 0
	char buffer[1024];
	va_list args;
   	va_start(args, dbg);
	vsprintf(buffer, dbg, args);
	va_end(args);

#if LGIT_DBG | LGIT_I2C_LOG
	if(I2cLogFlag == 0)
	{
		printf("[Tuner]"); /* Porting : Modify Debug function here */
	}
	printf(buffer); /* Porting : Modify Debug function here */
#endif
#endif
}

void LGIT_bsp_i2c_close(void)
{
	;
}

#ifdef __cplusplus
}
#endif



