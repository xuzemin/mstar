/***************************************************************************************/
/* FILE: Si2158_L0_TV_Chassis.c                                                        */
/*                                                                                     */
/*                                                                                     */
/*                                                                                     */
/***************************************************************************************/

#include "Silabs_L0_Si2158_API.h"

/************************************************************************************************************************
	NAME: Si2158_L0_Init function
	DESCRIPTION:layer 0 initialization function
              Used to sets the layer 0 context parameters to startup values.
			  The I2C address of the Si2173 is set in the Si2158_L1_API_Init procedure.              
              It is automatically called by the Layer 1 init function.
	Parameter:	Pointer to L0 (I2C) Context - 
	Porting:	In most cases, no modifications should be required.
	Returns:    void
************************************************************************************************************************/

void   Si2158_L0_Init  (Si2158_L0_Context *pContext) 
{
	(pContext)->address       = 0;
	(pContext)->indexSize     = 0;
    return;
}

void   Si2158_L0_SetAddress  (Si2158_L0_Context *pContext, unsigned int add, int addSize)
{
	(pContext)->address   = add;
    (pContext)->indexSize = addSize;
	return;
}

/************************************************************************************************************************
  NAME: system_wait_ms
  DESCRIPTION:	Delay for time_ms (milliseconds)
  Parameter:  time in milliseconds
  Porting:		Replace with embedded system delay function
  Returns:		nothing
************************************************************************************************************************/
void system_wait_ms_si2158(int time_ms)
{
	/* add a delay of time_ms based on you embedded system delay */
	LGIT_sleep(time_ms);	//LGIT
}
/************************************************************************************************************************
  NAME:		   Si2158_L0_ReadCommandBytes function
  DESCRIPTION:Read iNbBytes from the i2c device into pucDataBuffer, return number of bytes read
  Parameter: pointer to the Layer 0 context.
  Parameter: iNbBytes, the number of bytes to read.
  Parameter: *pucDataBuffer, a pointer to a buffer used to store the bytes
  Porting:    Replace with embedded system I2C read function
  Returns:    Actual number of bytes read.  
************************************************************************************************************************/
int Si2158_L0_ReadCommandBytes(Si2158_L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer)
{
	int nbReadBytes;
	/* Your I2C read function should return the actual number of bytes read.  */
	/* Alternatively return the number of bytes requested (iNbBytes)     */
	nbReadBytes = iNbBytes;

	LGIT_bsp_i2c_read(i2c->address, pucDataBuffer, iNbBytes); //LGIT 

    return nbReadBytes;
}

/************************************************************************************************************************
  NAME:  Si2158_L0_WriteCommandBytes
  DESCRIPTION:  Write iNbBytes from pucDataBuffer to the i2c device, return number of bytes written
  Parameter: pointer to the Layer 0 context.
  Parameter: iNbBytes, the number of bytes to write.
  Parameter: *pucDataBuffer, a pointer to a buffer used to store the bytes
  Porting:    Replace with embedded system I2C write function
  Returns:    Number of bytes written
************************************************************************************************************************/
int Si2158_L0_WriteCommandBytes(Si2158_L0_Context* i2c, int iNbBytes, unsigned char *pucDataBuffer)
{
	int nbWrittenBytes;
	/* Your I2C write function should return the actual number of bytes written.  */
	/* Alternatively return the number of bytes requested (iNbBytes)     */
	nbWrittenBytes = iNbBytes;

	LGIT_bsp_i2c_write(i2c->address, pucDataBuffer,iNbBytes); //LGIT 

    return nbWrittenBytes;
}    

/************************************************************************************************************************/

int     system_time_si2158        (void)        {
	/* <porting> Replace 'clock' by whatever is necessary to return the system time in milliseconds */
	return LGIT_time();
}