//#include "avl.h"
//#include "IBSP.h"
//#include <windows.h> 
//-----------
//#include "avl2108.h"
//#include "avl2108_Board.h"
//#include "IDVBSxRx.h"

#include "MsTypes.h"
#include "LNB_Controler.h"
//#include "globalvariable.h"

//extern AVL_semaphore gI2CSem;
//++++++++++++++++++++++++++++yanxd+++++++++++++++++++++++++++++++++++++++
AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CRead_LNBC(  AVL_uint16 uiSlaveAddr,  AVL_puchar pucBuff, AVL_puint16 puiSize )
{
	uiSlaveAddr = uiSlaveAddr;
	//uiSlaveAddr = 0x11;
	if (IIC_Read_LNBC(uiSlaveAddr,pucBuff,(*puiSize)))
	{
    	//printf("\r\n Read OK!\n");
    	return(AVL_DVBSx_EC_OK);
	}
	//printf("\r\n Read Fail!\n");
	return(AVL_DVBSx_EC_GeneralFail);
}

MS_BOOL AVL_DVBSx_IBSP_I2CWrite_LNBC(  unsigned short uiSlaveAddr,  unsigned char * pucBuff,  unsigned short *  puiSize )
{
	uiSlaveAddr = uiSlaveAddr;
	//uiSlaveAddr = 0x10;
	if(IIC_WRITE_LNBC(uiSlaveAddr,NULL,0,pucBuff,(*puiSize)))
	{
    	//printf("\r\n Write OK!\n");
		return(AVL_DVBSx_EC_OK);
	}
  	//printf("\r\n Write Fail!\n");
	return(AVL_DVBSx_EC_GeneralFail);
}

//++++++++++++++++++++++++++++end+++++++++++++++++++++++++++++++++++++

#if 1
//AVL_puchar pucBuff, AVL_puint16 puiSize
MS_BOOL AVL_LNBC_I2C_Read(AVL_uint16 LNBCAddr, AVL_puchar pucBuff, AVL_puint16 puiSize)
{
	
	AVL_DVBSx_ErrorCode r;	
	LNBCAddr=0x11;
	//AVL_DVBSx_Chip LNBCChip;
	if( *puiSize > 2 )
	{
		return(AVL_DVBSx_EC_GeneralFail);	 //one  byte
	}
    //LNBCChip.m_SlaveAddr = LNBCAddr; //A9832 READ ADDRESS
	//r = AVL_DVBSx_IBSP_WaitSemaphore(&(gI2CSem));		
	//r = AVL_DVBSx_IBSP_I2CRead(&LNBCChip, pucBuff, puiSize);	 
	r = AVL_DVBSx_IBSP_I2CRead_LNBC(LNBCAddr, pucBuff, puiSize);
	//printf("\r\n 8205 read i2c ack=%d\n", r);
	//r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(gI2CSem)); 
	return r;	
}
#endif

MS_BOOL AVL_LNBC_I2C_Write(unsigned short LNBCAddr,  unsigned char * pucBuff,  unsigned short *puiSize)
{
	MS_BOOL r;
	//AVL_DVBSx_Chip LNBCChip;	
	//r = AVL_DVBSx_IBSP_WaitSemaphore(&(gI2CSem));	
	//LNBCChip.m_SlaveAddr = LNBCAddr;
	//r = AVL_DVBSx_IBSP_I2CWrite(&LNBCChip, pucBuff, puiSize);
	LNBCAddr=0x10;
	//printf("\r\n device=0x%x,regist =0x%x, data=0x%x",LNBCAddr,*pucBuff, *puiSize); 
	r = AVL_DVBSx_IBSP_I2CWrite_LNBC(LNBCAddr, pucBuff, puiSize);
	//printf("\r\n 8205 write i2c ack=%d\n", r);
	//r |= AVL_DVBSx_IBSP_ReleaseSemaphore(&(gI2CSem)); 
	return r;	
}

AVL_DVBSx_ErrorCode A8293_Control(unsigned char Level) //true is 13V, otherwise 18V
{
	AVL_DVBSx_ErrorCode r;
	unsigned short uiSize = 1; //write one byte
	unsigned char LNBCRgister1; // first register
	unsigned char readdata;
	unsigned short LNBCWriteAddr = LNBC_WRITE_ADD;
	r = AVL_LNBC_I2C_Read(LNBCWriteAddr, &readdata, &uiSize); 
	if(Level == 2)  //Horizontal 18v
	{
      	printf("\r\nLNB 18V output\n");
    	LNBCRgister1 = 0x3A;//0x3B;
 	}
  	else if(Level == 1)  //Vertical  13v
  	{
      	printf("\r\nLNB 13v output\n");
      	LNBCRgister1 = 0x34;//0x37;
 	}
  	else if(Level == 0)  //LNB supply off  0v
  	{
      	printf("\r\nLNB 0v output\n");
      	LNBCRgister1 = 0x10;
 	}
	else
		printf("\r\nLNB error..............\n");

	r |= AVL_LNBC_I2C_Write(LNBCWriteAddr, &LNBCRgister1, &uiSize);
	
	//bit0: TMODE  0-intel tone   1-extern tone        bit1: TGATE  0-Tone gated off   1-Tone gate on
	LNBCRgister1 = 0x82;
	r |= AVL_LNBC_I2C_Write(LNBCWriteAddr, &LNBCRgister1, &uiSize); 
	
	return r;
}

