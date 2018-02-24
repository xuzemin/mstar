/********************************************************************
* UserDefinedIIC.h
* User Defined IIC Header
* By yooheeyong 2010/02/20
*********************************************************************/


#ifndef _USERDEFINEDIIC_H
#define _USERDEFINEDIIC_H


#if defined( __cplusplus )
extern "C"                     /* Use "C" external linkage                  */
{
#endif

// 인터페이스 
typedef enum{
  SEL_LPT = 0,
  SEL_USB,
  SEL_CYPRESS_USB
}SEL_INTERFACE;


#define  SI2176_ADDRESS        0xC0
#define  SI2176_I2C_ADDR (((U16)TUNER_IIC_BUS<<8)| SI2176_ADDRESS)


#define READ_MODE    0
#define WRITE_MODE   1

/* IIC initialization */
void I2c_Init(void);
/* Si2176 IIC Write */
unsigned char Si2176_I2cWrite(unsigned char Chip, unsigned char nRegAddrSize, unsigned int *lpRegAddr, unsigned short nDataSize, unsigned char *lpData);
/* Si2176 IIC Read */
unsigned char Si2176_I2cRead(unsigned char Chip, unsigned char nRegAddrSize, unsigned int *lpRegAddr, unsigned short nDataSize, unsigned char *lpData);
/* User Defined Sleep */
void SemcoSleep(unsigned int nSleepTims_ms);

#if defined( __cplusplus )
}
#endif

#endif

