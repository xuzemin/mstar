/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmicmn.h
**		This is the Asic common header file.
**
** 
*******************************************************************************/

#ifndef _NMICMN_H_
#define _NMICMN_H_

#include "nmitypes.h"
#include "nmicmndefs.h"
#include "nm131.h"
#include "nmiver.h"

extern void nmi_common_init(tNmiIn *, tTnrVtbl *);
extern void wReg8(uint8_t adr, uint8_t val);

#endif
