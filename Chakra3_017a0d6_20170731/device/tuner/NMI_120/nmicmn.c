/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmicmn.c
**		This module is used to wrap the ASIC configuration file.  
**
** 
*******************************************************************************/

#include "nmicmn.h"

#include <stdio.h>
#include <string.h>
/******************************************************************************
**
**	Private Data Structure
**
*******************************************************************************/
typedef struct {
	uint32_t            chipid;
	uint32_t            frequency;
	tNmiTvStd            std;	
	tNmiOutput			output;	

	uint32_t            dconotch_ctl;
	uint32_t            lofrequency;

	int16_t             alocklevelth;
	uint32_t            clk_off_f;

	int                 fmscanth;
	
	tTnrTuneMode        tuneMode;
	
	uint8_t             cvbsVol; /* Range 0 to 16. */
	uint8_t             cvbsVideoAmp; /* Range 0 to 15. */
	uint8_t				cvbsBrt; /* Range 0 to 32.*/
	uint8_t             rf_reg_0x05;
	tNmiDacSel			dacsel;
	uint8_t				mute;
	uint8_t				cvbsMaxVol; /* Some ATV frequencies suffer from noise when reg0x35 has max gain i.e. 0x50.
									This parameter should limit it to a maximum of 0x51 for these frequencies*/

	struct {
		uint8_t reg_0x00;
		uint8_t reg_0x34;
		uint8_t reg_0x35;		
	} sleep_lt_backup; /* See nm131_software_wake_up_lt() */

	bool_t              rfinvert;
} tNmiPriv;

typedef struct {
	tNmiIn				inp;
	tNmiPriv			priv;		
	bool_t              buserror;
} tNmiAsic;

static tNmiAsic chip;

/******************************************************************************
**
**	Debug 
**
*******************************************************************************/

static void nmi_debug(uint32_t zone, char *fmt,...)
{
	char buf[256];
	va_list args;
	int len;

	if (zone & chip.inp.zone) {
		va_start(args, fmt);
		strcpy(buf, "[Nmi Asic]: "); 
		len = vsnprintf(&buf[12], (256 - 12), fmt, args);
		va_end(args);

		if (chip.inp.hlp.log) {
			chip.inp.hlp.log(buf);
		}
	}

	return;
}

/******************************************************************************
**
**	Os Help Functions
**
*******************************************************************************/
static void nmi_delay(uint32_t msec)
{
	if (chip.inp.hlp.delay) {
		chip.inp.hlp.delay(msec);
	}
}

static uint32_t nmi_get_tick(void)
{
	uint32_t tick = 0;

	if (chip.inp.hlp.gettick) {
		tick = chip.inp.hlp.gettick();
	}

	return tick;
}

/******************************************************************************
**
**	Bus Read/Write Functions
**
*******************************************************************************/

static uint8_t rReg8(uint8_t adr)
{
	uint8_t b[2];		

	if (!(chip.inp.hlp.c.write && chip.inp.hlp.c.read) ||
			chip.buserror) {
		nmi_debug(N_ERR, "Error, read register(32), can't access chipset\n");
		return 0;
	}		 

	b[0] = 0;
	b[1] = (uint8_t)(adr);
	if (chip.inp.hlp.c.write(chip.inp.ai2c, b, 2) < 0) {
		nmi_debug(N_ERR, "Failed, bus write...\n");
		chip.buserror = 1;
		return 0;
	}

	if (chip.inp.hlp.c.read(chip.inp.ai2c, &b[0], 1) < 0) {
		nmi_debug(N_ERR, "Failed, bus read...\n");
		chip.buserror = 1;
	}

	return b[0]; 
}

uint32_t rReg32(uint16_t adr)
{
	uint8_t b[4];

	if (!(chip.inp.hlp.c.write && chip.inp.hlp.c.read) ||
			chip.buserror) {
		nmi_debug(N_ERR, "Error, read register(32), can't access chipset\n");
		return 0;
	}		 

	b[0] = (uint8_t)(adr >> 8);
	b[1] = (uint8_t)(adr);
	if (chip.inp.hlp.c.write(chip.inp.ai2c, b, 2) < 0) {
		nmi_debug(N_ERR, "Failed, bus write...\n");
		chip.buserror = 1;
		return 0;
	}

	if (chip.inp.hlp.c.read(chip.inp.ai2c, b, 4) < 0) {
		nmi_debug(N_ERR, "Failed, bus read...\n");
		chip.buserror = 1;
	}

	return (b[0] | (b[1] << 8) | (b[2] << 16) | (b[3] << 24)); 
}

//static void wReg8(uint8_t adr, uint8_t val)
void wReg8(uint8_t adr, uint8_t val)
{
	uint8_t b[3];

	/**
		Check Read/Write pointers. Don't access chip while it is sleep.
	**/
	if (!(chip.inp.hlp.c.write && chip.inp.hlp.c.read) ||
			chip.buserror) {
		nmi_debug(N_ERR, "Error, write register(32), can't access chipset\n");
		return;
	}	
	/**	
	Warning: make sure LDO bypass setting is correct
	so that the chip is not damaged.
	**/
	if(adr == 0x36) {
		if(chip.inp.ldobypass) {
			val |= (1 << 7);
		} else {
			val &= ~(1 << 7);
		}
	/* Save the loop through sleep/wake up registers shadow copy. */
	} else if (adr == 0x00) {
		chip.priv.sleep_lt_backup.reg_0x00 = val;	
	} else if (adr == 0x34) {
		chip.priv.sleep_lt_backup.reg_0x34 = val;	
	} else if (adr == 0x35) {
		chip.priv.sleep_lt_backup.reg_0x35 = val;	
	}



	b[0] = 0;
	b[1] = (uint8_t)(adr);
	b[2] = (uint8_t)(val);

	if (chip.inp.hlp.c.write(chip.inp.ai2c, b, 3) < 0) {
		nmi_debug(N_ERR, "Failed, bus write...\n");
		chip.buserror = 1;
	}

	return; 
}

void wReg32(uint16_t adr, uint32_t val)
{
	uint8_t b[6];

	/**
		Check Read/Write pointers. Don't access chip while it is sleep.
	**/
	if (!(chip.inp.hlp.c.write && chip.inp.hlp.c.read) ||
			chip.buserror) {
		nmi_debug(N_ERR, "Error, write register(32), can't access chipset\n");
		return;
	}		 

	b[0] = (uint8_t)(adr >> 8);
	b[1] = (uint8_t)(adr);
	b[2] = (uint8_t)(val);
	b[3] = (uint8_t)(val >> 8);
	b[4] = (uint8_t)(val >> 16);
	b[5] = (uint8_t)(val >> 24);

	if (chip.inp.hlp.c.write(chip.inp.ai2c, b, 6) < 0) {
		nmi_debug(N_ERR, "Failed, bus write...\n");
		chip.buserror = 1;
	}

#if 0
	wReg8(adr, (uint8_t)(val));
	wReg8((adr+1), (uint8_t)(val>>8));
	wReg8((adr+2), (uint8_t)(val>>16));
	wReg8((adr+3), (uint8_t)(val>>24));
#endif

	return; 
}

static void wRegBurst(uint32_t adr, uint8_t *bd, int sz)
{
#define OVERHEAD (2)

	int retVal;	
	int i;
	uint32_t sz2, sz3, blksz = 4;
	uint8_t b[256+OVERHEAD];

	if (sz > 0x400/* Maximum allowed length for NM131. */) {
		nmi_debug(N_ERR, "Failed, bus burst write, size too big...(%d)\n", sz);
		return; 
	}

	if( (sizeof(b)/sizeof(b[0])) <= OVERHEAD ) {
		nmi_debug(N_ERR, "temporary buffer size must be > 2 bytes.\n");
		return;
	}
	
	/**	
	Warning: make sure LDO bypass setting is correct
	so that the chip is not damaged.
	**/
	if((0x36 >= adr) && (0x36 < (adr+sz))) {
		
		if(chip.inp.ldobypass) {
			bd[0x36-adr] |= (1 << 7);
		} else {
			bd[0x36-adr] &= ~(1 << 7);
		}
	}

	/* Discover bus block size. */
	if(chip.inp.hlp.c.getwriteblksz) {
		blksz  = chip.inp.hlp.c.getwriteblksz() - OVERHEAD;
		/* Usable block size should be <= size of b buffer for I2C. */
		if( blksz > ((sizeof(b)/sizeof(b[0]))-OVERHEAD) ) {
			blksz = (sizeof(b)/sizeof(b[0]))-OVERHEAD;
		}
	} else {	
		/** 
		If bus block size is unknown, it is safe to that wRegBurst behaves 
		like wReg8. 
		**/
		blksz = 1;
	}

	retVal = 0;		
	sz2 = sz;
	i = 0;
	while (((int)sz2)  > 0)
	{
		if (sz2 <= blksz)
			sz3 = sz2;
		else
			sz3 = blksz;
		b[0] = (uint8_t)(adr >> 8);
		b[1] = (uint8_t)(adr);
		memcpy(&b[OVERHEAD], &bd[i], sz3*sizeof(b[0]));	

		if (chip.inp.hlp.c.write(chip.inp.ai2c, b, sz3+OVERHEAD) < 0) {
			nmi_debug(N_ERR, "Failed, bus burst write...\n");
			chip.buserror = 1;
			retVal = -1;
			break;
		}
		
		retVal += sz3;
		adr +=sz3;
		sz2 -=sz3;
		i+= sz3;
	}

	return;
}


/******************************************************************************
**
**	Includes Asic implementation
**
*******************************************************************************/
#ifdef AVOID_INCLUDE_C_FROM_C
/* For NTK build system, do not use extension ".c" */
#include "nm131.c_"
#else
#include "nm131.c"
#endif


/******************************************************************************
**
**	Global Exported Initialization Function
**
*******************************************************************************/

void nmi_common_init(tNmiIn *inp, tTnrVtbl *ptv)
{
	memset((void *)&chip, 0, sizeof(tNmiAsic));

	if (inp != NULL)
		memcpy((void *)&chip.inp, (void *)inp, sizeof(tNmiIn));

	if (ptv != NULL) {
		nm131_vtbl_init(ptv);
	}
	
	return;
}


