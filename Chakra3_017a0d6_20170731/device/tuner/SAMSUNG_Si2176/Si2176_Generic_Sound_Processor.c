/***************************************************************************************/
/* FILE: Generic_Sound_Processor.c                                                     */
/* PURPOSE: This file serves as a hook for user-supplied code to interface to the      */
/* sound processor for ATV.  This is required in the ChannelScanPAL() function to      */
/* decode the PAL standard                                                             */
/***************************************************************************************/
#include "Si2176_Generic_Sound_Processor.h"
/************************************************************************************************************************
  NAME: L1_InitSoundProcessor
  DESCRIPTION: Initialization of sound processor required for System detection for ChannelScanPAL function
  Porting:    Replace with embedded system I2C commands to initialize the Sound processor
  Returns:    0 if ok
************************************************************************************************************************/
int L1_InitSoundProcessor(void)
{
  /* Initialize and reset the sound processor */
    return 0;
}    
/************************************************************************************************************************/
/************************************************************************************************************************
  NAME: L1_AcquireSoundStandard
  DESCRIPTION: Initialization of sound processor required for System detection for ChannelScanPAL function
  Porting:    Replace with embedded system I2C commands to initialize the Sound processor
  Parameters: timeout_ms - timeout (milliseconds) 
  Parameters: char* for possible standards;    B,GH,M,N,I,DK,L,LP
  where 
   0 = Standard B
   1 = Standard G/H
   2 = Standard M
   3 = Standard N
   4 = Standard I
   5 = Standard D/K
   6 = Standard L
   7 = Standard L'
  Returns: 0 = command successful,  else read error or timeout.
************************************************************************************************************************/
int L1_AcquireSoundStandard(int timeout_ms , char* possible_standards)
{
  /*Return byte with possible standards set with the pattern above */
    return 0;
}    
/************************************************************************************************************************/
