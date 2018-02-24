/***************************************************************************************/
/* FILE: Si2176_L0_TV_Chassis.c                                                        */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/
//#include "Si2176_Typedefs.h"
#include "Si2176_L0_TV_Chassis.h"
#include "UserDefinedIIC.h"

unsigned char registerDataBuffer[8];
unsigned char pucAddressBuffer[4];
unsigned int  puiAddressBuffer[4];
unsigned char pucBuffer[256];
unsigned char pbtBuffer[256];



#include <time.h>

/************************************************************************************************************************
  system_wait function
  Use:        current system wait function
              Used to wait for time_ms milliseconds while doing nothing
  Porting:    Needs to use the final system call for time retrieval
  Parameter:  time_ms the wait duration in milliseconds
  Returns:    The current system time in milliseconds
************************************************************************************************************************/
 int  system_wait(int time_ms) {
//For linux    return (int)(LINUX wait for time_ms);
    clock_t ticks1, ticks2;
    ticks1=clock();
    ticks2=ticks1;
    /* <porting> Replace 'clock' by whatever is necessary to return the system time in milliseconds */
    while((unsigned int)(ticks2*1000/CLOCKS_PER_SEC-ticks1*1000/CLOCKS_PER_SEC)<(unsigned int)time_ms) {ticks2=clock();}
    return (int)ticks2*1000/CLOCKS_PER_SEC;
}
/************************************************************************************************************************
  system_time function
  Use:        current system time retrieval function
              Used to retrieve the current system time in milliseconds
  Porting:    Needs to use the final system call
  Returns:    The current system time in milliseconds
************************************************************************************************************************/
 int  system_time(void) {
    /* <porting> Replace 'clock' by whatever is necessary to return the system time in milliseconds */
    return (int)clock()*1000/CLOCKS_PER_SEC;
//For linux    return (int)(LINUX time in ms unit);
}


/************************************************************************************************************************
  NAME: L0_Init function
  DESCRIPTION:layer 0 initialization function
              Used to sets the layer 0 context parameters to startup values.
        The I2C address of the Si2173 is set in the Si2176_L1_API_Init procedure.              
              It is automatically called by the Layer 1 init function.
  Parameter:  Pointer to L0 (I2C) Context - 
  Porting:  In most cases, no modifications should be required.
  Returns:    void
************************************************************************************************************************/
void   L0_Init  (L0_Context *pContext) 
{
  (pContext)->address       = SI2176_ADDRESS;
  (pContext)->indexSize     = 0;
    return;
}

/************************************************************************************************************************
  NAME: SendRSTb
  DESCRIPTION: Set Si2176 RSTb from low for 1 ms, then return high to reset Si2176
  Porting:    Replace with system GPIO that resets Si2176
  Parameters:  nothing
  Returns:    nothing
************************************************************************************************************************/
void SendRSTb (void) 
{
  /* wait for 1 ms */
    system_wait(1);              /* wait at least 100us */ 
    return;                             
}
/************************************************************************************************************************
  NAME:      L0_ReadCommandBytes function
  DESCRIPTION:Read iNbBytes from the i2c device into pucDataBuffer, return number of bytes read
  Parameter: pointer to the Layer 0 context.
  Parameter: iNbBytes, the number of bytes to read.
  Parameter: *pucDataBuffer, a pointer to a buffer used to store the bytes
  Porting:    Replace with embedded system I2C read function
  Returns:    Actual number of bytes read.  
************************************************************************************************************************/
int L0_ReadCommandBytes(L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer)
{
  unsigned char   nRegAddrSize;
  unsigned int    byteAddress;
  unsigned int   *lpRegAddr;
  unsigned short  nDataSize;

  byteAddress    = 0;
  lpRegAddr      = &(byteAddress);
  //nRegAddrSize   = (unsigned char)(i2c->indexSize);
  nRegAddrSize = 0;
  nDataSize      = (unsigned short)iNbBytes;

  if(Si2176_I2cRead(i2c->address, nRegAddrSize, lpRegAddr, nDataSize, pucDataBuffer) !=0) 
  {
  return 0;
  }else{
  return iNbBytes;
  }
}

/************************************************************************************************************************
  NAME:  L0_WriteCommandBytes
  DESCRIPTION:  Write iNbBytes from pucDataBuffer to the i2c device, return number of bytes written
  Parameter: pointer to the Layer 0 context.
  Parameter: iNbBytes, the number of bytes to write.
  Parameter: *pucDataBuffer, a pointer to a buffer used to store the bytes
  Porting:    Replace with embedded system I2C write function
  Returns:    Number of bytes written
************************************************************************************************************************/
int L0_WriteCommandBytes(L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer)
{
  unsigned char   nRegAddrSize;
  unsigned int    byteAddress;
  unsigned int   *lpRegAddr;
  unsigned short  nDataSize;


  byteAddress    = 0;  
  lpRegAddr      = &(byteAddress);
  //nRegAddrSize   = (unsigned char)(i2c->indexSize);
  nRegAddrSize = 0;
  nDataSize      = (unsigned short)iNbBytes;; 

  if(Si2176_I2cWrite(i2c->address,nRegAddrSize, lpRegAddr, nDataSize, pucDataBuffer) != 0){
    return 0;
  }else{
    return iNbBytes;
  }
}    

/************************************************************************************************************************/
