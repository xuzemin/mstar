/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmiport.c
**
**		This module implements the necessary functions OS and bus function for
**		NM131 tuner.
**
**
*******************************************************************************/

#ifndef _NMIPORT_C_
#define _NMIPORT_C_
#include <string.h>
#include "nmicmn.h"
#include "nmiver.h"
#include "nmiioctl.h"
#include "drvIIC.h"
#include "MsOS.h"


/******************************************************************************
**
**	ASIC Helper Functions
**
*******************************************************************************/
static void nmi_log(char *str)
{
	printf(str);
}

static void nmi_delay(uint32_t msec)
{
    MsOS_DelayTask(msec);
}

static uint32_t nmi_get_tick(void)
{
	uint32_t time;
	time = MsOS_GetSystemTime();
	return time;
}


static int nmi_bus_read(unsigned char DeviceAddr, unsigned char* pArray, unsigned long count)
{
	int status = 0;
    if(MDrv_IIC_ReadBytes(((U16)TUNER_IIC_BUS<<8)|DeviceAddr , 0, 0, count, pArray))
    {
        status = NMI_S_OK;
    }
    else
    {
        status =NMI_E_BUS_READ;
    }

	return (status);    //success
}


static int nmi_bus_write(unsigned char DeviceAddr, unsigned char* pArray, unsigned long count)
{
	int status = 0;
    if(MDrv_IIC_WriteBytes(((U16)TUNER_IIC_BUS<<8)|DeviceAddr , 0, 0, count, pArray))
    {
        status = NMI_S_OK;
    }
    else
    {
        status =NMI_E_BUS_WRITE;
    }
	return (status);
}

static unsigned long nmi_bus_get_read_blksz(void)
{
	//return UINT_MAX;
	return (~0);
}

static unsigned long nmi_bus_get_write_blksz(void)
{
	return 14;
}
#endif
