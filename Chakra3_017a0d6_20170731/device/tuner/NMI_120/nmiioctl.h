/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmiiioctl.h
**	
** 
*******************************************************************************/

#ifndef _NMIIOCTL_PLTFRM_H_
#define _NMIIOCTL_PLTFRM_H_

#include "nmitypes.h"
#include "nmicmndefs.h"
#include "nm131.h"

/******************************************************************************
**
**	Includes common IOCTLs.
**
*******************************************************************************/
#include "nmiioctl_cmn.h"

/******************************************************************************
**
**	Application Interface 
**
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#ifdef _WIN32 
#define NMI_DRV_CTL_EXPORT __declspec(dllexport) 
#else
#define NMI_DRV_CTL_EXPORT 
#endif

NMI_DRV_CTL_EXPORT int nmi_drv_ctl(uint32_t, void *);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif
