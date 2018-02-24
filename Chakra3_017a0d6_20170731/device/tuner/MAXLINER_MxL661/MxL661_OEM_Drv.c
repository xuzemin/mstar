/*****************************************************************************************
 *
 * FILE NAME          : MxL661_OEM_Drv.c
 *
 * AUTHOR             : Dong Liu
 *
 * DATE CREATED       : 01/23/2011
 *
 * DESCRIPTION        : This file contains I2C driver and Sleep functins that
 *                      OEM should implement for MxL661 APIs
 *
 *****************************************************************************************
 *                Copyright (c) 2010, MaxLinear, Inc.
 ****************************************************************************************/

#include "MxL661_OEM_Drv.h"
#include "MaxLinearDataTypes.h"
#include "drvIIC.h"
#include "msAPI_Timer.h"

//#define MxL_I2CBUS_ADDR 0x0200
#define MxL_I2CBUS_ADDR			((TUNER_IIC_BUS << 8) | 0xC0)
/*----------------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_OEM_WriteRegister
--|
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C write operation.
--|
--| RETURN VALUE  : True or False
--|
--|-------------------------------------------------------------------------------------*/

MXL_STATUS MxLWare661_OEM_WriteRegister(UINT8 I2cSlaveAddr, UINT8 RegAddr, UINT8 RegData)
{
//  MXL_STATUS status = MXL_TRUE;
//  U8 *PBUF;
//	U8 *PADDR;
//	UINT8 REG[1];
//	REG[0] = RegData;
    UNUSED(I2cSlaveAddr);
//	PBUF = REG;
//	PADDR = &RegAddr;
//	printf("Mxl I2C wirte RegAddr=%d,RegData=%d\n",RegAddr,RegData);
  // OEM should implement I2C write protocol that complies with MxL601 I2C
  // format.

  // 8 bit Register Write Protocol:
  // +------+-+-----+-+-+----------+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |RegAddr(H)| |RegAddr(L)| |RegData(L)| |P|
  // +------+-+-----+-+-+----------+-+----------+-+----------+-+-+
  // |SLAVE |         |A|          |A|          |A|          |A| |
  // +------+---------+-+----------+-+----------+-+----------+-+-+
  // Legends: SADDR (I2c slave address), S (Start condition), A (Ack), N(NACK),
  // P(Stop condition)
//	if(MDrv_IIC_WriteBytes((U16)(MxL_I2CBUS_ADDR|(I2cSlaveAddr<<1)), 0, PADDR, (U16) 1, &RegData))
    if(MDrv_IIC_WriteBytes((U16)(MxL_I2CBUS_ADDR), 1, &RegAddr, (U16) 1, &RegData))
        return MXL_TRUE;
    else
        printf("Mxl I2C wirte error. slaveid=0x%x, RegAddr=%d,RegData=%d\n",MxL_I2CBUS_ADDR,RegAddr,RegData);

    return MXL_FALSE;

 // return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_OEM_ReadRegister
--|
--| AUTHOR        : Brenndon Lee
--|
--| DATE CREATED  : 7/30/2009
--|
--| DESCRIPTION   : This function does I2C read operation.
--|
--| RETURN VALUE  : True or False
--|
--|---------------------------------------------------------------------------*/

MXL_STATUS MxLWare661_OEM_ReadRegister(UINT8 I2cSlaveAddr, UINT8 RegAddr, UINT8 *DataPtr)
{
    UINT8 u8addr=0xFB;

    UNUSED(I2cSlaveAddr);

    if(!MDrv_IIC_WriteBytes((U16)(MxL_I2CBUS_ADDR),1, &u8addr,1,&RegAddr))
    {
        printf("Mxl I2C read 1 error. slaveid=0x%x\n",MxL_I2CBUS_ADDR);
        return MXL_FALSE;
    }
    if(MDrv_IIC_ReadBytes((U16)(MxL_I2CBUS_ADDR),0,NULL,1,DataPtr))
        return MXL_TRUE;

    printf("Mxl I2C read 2 error. slaveid=0x%x\n",MxL_I2CBUS_ADDR);

    return MXL_FALSE;


  // OEM should implement I2C read protocol that complies with MxL601 I2C
  // format.

  // 16 Register Read Protocol:
  // +------+-+-----+-+-+----+-+----------+-+----------+-+-+
  // |MASTER|S|SADDR|W| |0xFB| |RegAddr(H)| |RegAddr(L)| |P|
  // +------+-+-----+-+-+----+-+----------+-+----------+-+-+
  // |SLAVE |         |A|    |A|          |A|          |A| |
  // +------+-+-----+-+-+----+-+----------+-+----------+-+-+
  // +------+-+-----+-+-+-----+--+-+
  // |MASTER|S|SADDR|R| |     |MN|P|
  // +------+-+-----+-+-+-----+--+-+
  // |SLAVE |         |A|Data |  | |
  // +------+---------+-+-----+--+-+
  // Legends: SADDR(I2c slave address), S(Start condition), MA(Master Ack), MN(Master NACK),
  // P(Stop condition)

 // return status;
}

/*------------------------------------------------------------------------------
--| FUNCTION NAME : MxLWare661_OEM_Sleep
--|
--| AUTHOR        : Dong Liu
--|
--| DATE CREATED  : 01/10/2010
--|
--| DESCRIPTION   : This function complete sleep operation. WaitTime is in ms unit
--|
--| RETURN VALUE  : None
--|
--|-------------------------------------------------------------------------------------*/

void MxLWare661_OEM_Sleep(UINT16 DelayTimeInMs)
{
  msAPI_Timer_Delayms(DelayTimeInMs);
  // OEM should implement sleep operation
}
