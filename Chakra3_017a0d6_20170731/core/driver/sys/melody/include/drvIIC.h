////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _IIC_H_
#define _IIC_H_

#ifdef _IIC_C_
#define _IICDEC_
#else
#define _IICDEC_ extern
#endif

#include "Board.h"
#include "apiSWI2C.h"

  // Speed Mapping: Base on the Driver loading, maybe you must to use the oscilloscope to measure this Value
  // 250K => SwIicDly =1
  // 200K => SwIicDly =10
  // 150K => SwIicDly =20
  // 100K => SwIicDly =40
#ifdef USE_SW_I2C_HIGHSPEED
#undef USE_SW_I2C_HIGHSPEED
#define USE_SW_I2C_HIGHSPEED 1 //Force SWI2C in High Speed Mode
#endif

#if (USE_SW_I2C_HIGHSPEED==1)
#define I2C_SPEED_MAPPING_400K           4 //OK
#define I2C_SPEED_MAPPING_350K           7 //OK
#define I2C_SPEED_MAPPING_300K          11 //OK //13:278 //10:313 // 8
#define I2C_SPEED_MAPPING_250K          16 //OK //17:240 // 20:220 // 12
#define I2C_SPEED_MAPPING_200K          25 //OK
#define I2C_SPEED_MAPPING_150K          37 //OK //40:140
#define I2C_SPEED_MAPPING_100K          60 //OK
#define I2C_SPEED_MAPPING_ISP_400K          240
#else
//base on CPU running at 384MHz
#define I2C_SPEED_MAPPING_400K           50
#define I2C_SPEED_MAPPING_350K           60
#define I2C_SPEED_MAPPING_300K           70
#define I2C_SPEED_MAPPING_250K           80
#define I2C_SPEED_MAPPING_200K          100
#define I2C_SPEED_MAPPING_150K          135
#define I2C_SPEED_MAPPING_100K          135//200
#define I2C_SPEED_MAPPING_ISP_400K          240
#endif

typedef enum {
    E_I2C_BUS_DDCROM,
    E_I2C_BUS_SYS = E_I2C_BUS_DDCROM,
    E_I2C_BUS_DDCA0,
    E_I2C_BUS_DDCD0,
    E_I2C_BUS_ISP,
    E_I2C_BUS_DDCD1,
    E_I2C_BUS_DDCD2,
    //E_I2C_BUS_USR0,
    //E_I2C_BUS_USR1,
    //E_I2C_BUS_USR2,
    //E_I2C_BUS_USR3,
} E_I2C_BUS_CHANNEL;

_IICDEC_ void MDrv_IIC_Init(void);
_IICDEC_ BOOLEAN MDrv_IIC_WriteBytes(U16 u16BusNumSlaveID, U8 u8addrcount, U8* pu8addr, U16 u16size, U8* pu8data);
_IICDEC_ BOOLEAN MDrv_IIC_ReadBytes(U16 u16BusNumSlaveID, U8 u8AddrNum, U8* paddr, U16 u16size, U8* pu8data);
_IICDEC_ BOOLEAN MDrv_IIC_ReadByte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 *pu8Data);
_IICDEC_ BOOLEAN MDrv_IIC_WriteByte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 u8Data);

_IICDEC_ BOOLEAN MDrv_IIC_Write2Bytes(U16 u16BusNumSlaveID, U8 u8addr, U16 u16data);
_IICDEC_ U16 MDrv_IIC_Read2Bytes(U16 u16BusNumSlaveID, U8 u8addr);
_IICDEC_ BOOLEAN MDrv_IIC_Write4Bytes(U16 u16BusNumSlaveID, U32 u32Data, U8 u8EndData);

_IICDEC_ BOOLEAN MDrv_IIC_ReadByteDirectly(U16 u16BusNumSlaveID, U8 * pu8Data);

_IICDEC_ BOOLEAN MDrv_IIC_WriteGroupBytes(U16 u16BusNumSlaveID, U8 u8SubGroup, U16 u16Addr, U16 u16Data);
_IICDEC_ U16 MDrv_IIC_ReadGroupBytes(U16 u16BusNumSlaveID, U8 u8SubGroup, U16 u16Addr);

_IICDEC_ U32 MDrv_IIC_Speed_Setting(U8 u8BusNum, U32 u32Speed_K);

_IICDEC_ U8 IIC_GetByte (U16  bAck);
_IICDEC_ BOOLEAN IIC_SendByte(U8 u8dat);
_IICDEC_ BOOLEAN IIC_AccessStart(U8 ucSlaveAdr, U8 trans_t);
_IICDEC_ void IIC_Stop(void);
_IICDEC_ bool I2C_Write_Byte(U8 DataByte);
_IICDEC_ BOOL I2C_Start (void);
_IICDEC_ U8 I2C_Read_Byte(U8 ack);
_IICDEC_ void I2C_Stop (void);
_IICDEC_ void IIC_UseBus( U8 u8BusChn );
_IICDEC_ BOOL IIC_Start(void);
_IICDEC_ BOOLEAN MDrv_IIC_OPT_ReadBytes(U16 u16BusNumSlaveID, U16 ucBufLen, U8* pBuf); //gchen @ 20171213

#undef _IICDEC_

#endif // _IIC_H_
