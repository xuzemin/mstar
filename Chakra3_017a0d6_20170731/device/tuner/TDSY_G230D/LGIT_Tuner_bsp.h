/****************************************************************************
*
* 							LG Innotek Co.,Ltd.
*
* Copyright (C) 2012, LG Innotek, Gwangju, Korea, All Rights Reserved.
*
* File: LGIT_Tuner_bsp.h
*
* version: 1.00.00
*
* Description: I2C function prototype  
*
* Description			Version		Date		Author
* ---------------------------------------------------------------------
* Create				1.00.00		2012.03.28	JH.KIM
****************************************************************************/

#ifndef _LGIT_TUNER_BSP_H
#define _LGIT_TUNER_BSP_H

// #include <stdio.h>
// #include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

int LGIT_bsp_i2c_init(void);
int LGIT_bsp_i2c_write(unsigned char I2cAddr, unsigned char *pData, unsigned int nBytes);
int LGIT_bsp_i2c_read(unsigned char I2cAddr, unsigned char *pData, unsigned int nBytes);
void LGIT_sleep(unsigned int mSec);
int LGIT_time(void);
void LGIT_dbg(const char *dbg, ...);
void LGIT_bsp_i2c_close(void);

#ifdef __cplusplus
}
#endif

#endif /* _LGIT_TUNER_BSP_H */