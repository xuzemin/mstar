/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmitnr.c
**	
**		This module implements the necessary functions for driving the NMI 120,13x  Chipset.
**		Porting driver for NTK 310/216. It can be used as an example for other boards
**
** 
*******************************************************************************/

#include "nmicfg.h"
#include "nmicmn.h"
#include "nmiver.h"
#include "nmiioctl.h"


/******************************************************************************
**
**	Includes Platform ASIC Help and Platform bus function
**
*******************************************************************************/
#ifdef AVOID_INCLUDE_C_FROM_C
/* For NTK build system, do not use extension ".c" */
#include "nmiport.c_"
#else 
#include "nmiport.c"
#endif

/******************************************************************************
**
**	Includes Driver Tnr Functions
**
*******************************************************************************/

#ifdef AVOID_INCLUDE_C_FROM_C
/* For NTK build system, do not use extension ".c" */
#include "nmiioctl_cmn.c_"
#else 
#include "nmiioctl_cmn.c"
#endif


/******************************************************************************
**
**	Dll Exported Function
**
*******************************************************************************/


int nmi_drv_ctl(uint32_t icode, void *inp)
{
	tNmiDrv *pd = &drv;
	int result = 0;

	switch (icode) {
	case NMI_DRV_INIT:
		result = nmi_tnr_init(inp);
		break;
	case NMI_DRV_DEINIT:
		nmi_tnr_deinit();
		break;
	case NMI_DRV_VERSION:		
		nmi_tnr_get_version((tNmiDriverVer *)inp);		
		break;
	case NMI_DRV_GET_CHIPID:
		*((uint32_t *)inp) = nmi_tnr_get_chipid();	
		break;
	case NMI_DRV_TUNE:
		result = nmi_tnr_tune((tTnrTune *)inp);
			break;
	case NMI_DRV_SCAN:
		result = nmi_tnr_scan((tTnrScan*)inp);
		break;
	case NMI_DRV_SET_SCAN_TH:
		pd->tnr.setscanlevel(*((int*)inp));
		break;
	case NMI_DRV_RESET_DEMOD:
		nmi_tnr_reset_demod();
		break;
	case NMI_DRV_RESET_DEMOD_MOSAIC:
		nmi_tnr_reset_demod_mosaic();
		break;
	case NMI_DRV_GET_STATUS:
		nmi_tnr_get_status((tTnrStatus *)inp);
		break;
	case NMI_DRV_SET_LNA_GAIN:
		pd->tnr.setgain((tNmiLnaGain)inp);
		break;
	case NMI_DRV_INVERT_SPECTRUM:
		pd->tnr.invertspectum(*((int*)inp));
		break;
	case NMI_DRV_SET_IF_OUTPUT_VOLTAGE:
		pd->tnr.setifoutvoltage(*((int*)inp));
		break;	
	case NMI_DRV_SLEEP:
		pd->tnr.sleep_lt();
		break;	
	case NMI_DRV_WAKE_UP_LT:
		pd->tnr.wake_up_lt();
		break;
	case NMI_DRV_LT_CTRL:
		nmi_tnr_lt_ctrl((tTnrLtCtrl *)inp);
		break;
	default:
		result = -1;
		break;
	}
	
	return result;
}

