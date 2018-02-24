/***************************************************************************************/
/* FILE: Generic_DTV_Demod.c                                                           */
/* PURPOSE: This file serves as a hook for the external demod to return the lock status */
/* This is called by the DTVTune() function.                                              */
/*                                                                                      */
/***************************************************************************************/
#include "Si2176_Generic_DTV_Demod.h"
/************************************************************************************************************************
  NAME: L1_DigitalDemodLocked
  DESCRIPTION: Calls the external demodulator for DTV.  If the demod is locked on a valid signal then return 0 else 1
  Porting:    Replace with embedded system I2C commands to query the demod lock status
  Returns:    0 if demod locked,  1 otherwise
************************************************************************************************************************/
int L1_DigitalDemodLocked(void)
{
	/*Return a 0 if the demod is locked on to a DTV signal */
    return 0;
}    
