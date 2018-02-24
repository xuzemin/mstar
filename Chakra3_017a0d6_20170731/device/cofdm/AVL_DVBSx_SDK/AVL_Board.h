#ifndef _AVL_BOARD_H_
#define _AVL_BOARD_H_

#include "MsCommon.h"
#include "drvIIC.h"
#include "drvGPIO.h"
#if 1
#define MDrv_IIC_Write(u16SlaveID, pu8Addr, u8AddrSize, pu8Buf, u16BufSize) MDrv_IIC_WriteBytes(0x218, u8AddrSize, pu8Addr, u16BufSize, pu8Buf)
#define IIC_DEVICEID               0
#define IIC_WRITE             MDrv_IIC_Write

#define MDrv_IIC_Read(u8DevId, buf, count) MDrv_IIC_ReadBytes(0x219, 0, NULL, count, buf)
#define IIC_Read			MDrv_IIC_Read
#else
#if   (FRONTEND_DEMOD_CTRL == PIU_IIC_0)
#define IIC_DEVICEID               0
#define IIC_WRITE             MDrv_IIC_Write
#elif (FRONTEND_DEMOD_CTRL == PIU_IIC_1)
#define IIC_DEVICEID               1
#define IIC_WRITE             MDrv_IIC1_Write
#else
#error "FRONTEND_TUNER_CTRL"
#endif
#endif
#define DEVIIC_IOC_SLAVEID 0
#define DEVIIC_OK                  1

extern int IIC_Ioctl(MS_U8 u8DevId, MS_U32 u32Cmd, ...);
//extern int IIC_Read(MS_U8 u8DevId, MS_U8 *buf, MS_U32 count);

MS_U32 SysDelay(MS_U32 dwMs);

#endif
