#ifndef LNB_CONTROLER_H
#define LNB_CONTROLER_H

//#include "IBSP.h"
//#include "avl2108.h"
#include "MsCommon.h"
#include "drvIIC.h"
#include "drvGPIO.h"
#include "AVL_DVBSx_SDK/AVL_DVBSx/include/avl_dvbsx.h"

#define MDrv_IIC_Write_LNBC(u16SlaveID, pu8Addr, u8AddrSize, pu8Buf, u16BufSize) MDrv_IIC_WriteBytes(0x210, u8AddrSize, pu8Addr, u16BufSize, pu8Buf)
#define IIC_DEVICEID               0
#define IIC_WRITE_LNBC             MDrv_IIC_Write_LNBC

#define MDrv_IIC_Read_LNBC(u8DevId, buf, count) MDrv_IIC_ReadBytes(0x211, 0, NULL, count, buf)
#define IIC_Read_LNBC			MDrv_IIC_Read_LNBC

//------------------
//#define AVL_DVBSx_ErrorCode MS_BOOL 
//#define AVL_DVBSx_EC_OK  0//A2108_EC_OK
//#define AVL_DVBSx_EC_GeneralFail  1//A2108_EC_GeneralFail
#define LNBC_WRITE_ADD 0x10 //LNB Controler A8293 device address
#define LNBC_READ_ADDR 0x08

//Control Register Address (I1, I0) = 10 and 11
/*#define	CONTROL_REGISTER1_VSEL0(x) x&0x01
#define CONTROL_REGISTER1_VSEL1(x) x&0x02
#define CONTROL_REGISTER1_VSEL2(x) x&0x04
#define CONTROL_REGISTER1_VSEL3(x) x&0x08
#define CONTROL_REGISTER1_ODT(x) x&0x10  //1 (recommended): The ODT functions are always enabled

#define CONTROL_REGISTER1_ENB(x) x|0x20  //0: Disable LNB Output 1: Enable LNB Output
#define CONTROL_REGISTER1_DISENABLE(x) x&0xdf  //1101 1111

#define	CONTROL_REGISTER2_TMODE(x) x&0x01  //0: External Tone 1: Internal Tone
#define	CONTROL_REGISTER2_TGATE_OFF(x) x&0x01  // Gated Off 

//Output Voltage Amplitude Selection
#define LNBC_OUT_VOLTAGE1 12.709  //VSEL3 VSEL2 VSEL1 VSEL0 0000 
#define LNBC_OUT_VOLTAGE2 13.042  //VSEL3 VSEL2 VSEL1 VSEL0 0001
#define LNBC_OUT_VOLTAGE3 14.042  //VSEL3 VSEL2 VSEL1 VSEL0 0100
#define LNBC_OUT_VOLTAGE4 18.042 //1000
#define LNBC_OUT_VOLTAGE5 19.042 //1011

typedef  char AVL_char;		///< 8 bits signed char data type.
typedef  unsigned char AVL_uchar;	///< 8 bits unsigned char data type.

typedef  short AVL_int16;	///< 16 bits signed char data type.
typedef  unsigned short AVL_uint16;	///< 16 bits unsigned char data type.

typedef  int AVL_int32;		///< 32 bits signed char data type.
typedef  unsigned int AVL_uint32;	///< 32 bits unsigned char data type.

typedef  char * AVL_pchar;	///< pointer to a 8 bits signed char data type.
typedef  unsigned char * AVL_puchar; ///< pointer to a 8 bits unsigned char data type.

typedef  short * AVL_pint16;	///< pointer to a 16 bits signed char data type.
typedef  unsigned short * AVL_puint16;	///< pointer to a 16 bits unsigned char data type.

typedef  int * AVL_pint32;	///< pointer to a 32 bits signed char data type.
typedef  unsigned int * AVL_puint32; ///< pointer to a 32 bits unsigned char data type.

typedef unsigned char AVL_semaphore; 	///< the semaphore data type.
typedef unsigned char * AVL_psemaphore;		///< the pointer to a semaphore data type.

//const AVL_uchar LNBCOutV[5] = {0x30, 0x31,0x34, 0x38, 0x3b};// enable LNB OUT put
//0:Gate off the tone out
//1:Use internal tone, gated by the TGATE bit
//2:Use internal tone, gated by the EXTM pin
//3:Use external tone,it just provides LNB voltage, the DiSEqC tone is provided by Ruby
//const AVL_uchar LNBCToneMode[4] = {0x80, 0x83, 0x83, 0x82};*/
AVL_DVBSx_ErrorCode A8293_Control(unsigned char Level);

#endif
