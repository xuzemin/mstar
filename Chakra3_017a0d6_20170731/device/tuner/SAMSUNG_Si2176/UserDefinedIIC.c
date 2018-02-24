/********************************************************************
* UserDefinedIIC.c
* User Defined IIC Function
* By yooheeyong 2010/02/20
*********************************************************************/

//#include <windows.h>
#include "UserDefinedIIC.h"
#include "drvIIC.h"
#include "datatype.h"


#ifdef SEMCO_IIC
  #include "lpt.h"
  extern Ciic m_iic;  /* IIC 인터페이스 객체 선언 */
  extern int EXTERN_LPT_USB;
#endif

#ifndef UNUSED_SAMSUNG //to avoid compile warnings...
#define UNUSED_SAMSUNG(var) (void)((var) = (var))
#endif


/* IIC initialization */
void I2c_Init(void)
{
#ifdef SEMCO_IIC
    #define LPTDELAY    4000
    m_iic.I2cInit(LPTDELAY);
#endif
}



/* Si2176 IIC Write */
unsigned char Si2176_I2cWrite(unsigned char Chip, unsigned char nRegAddrSize, unsigned int *lpRegAddr, unsigned short nDataSize, unsigned char *lpData)
{
  UNUSED_SAMSUNG(Chip);
  UNUSED_SAMSUNG(nRegAddrSize);
  UNUSED_SAMSUNG(lpRegAddr);

#ifdef SEMCO_IIC
  unsigned long ret;
  ret = m_iic.Semco_I2c_WriteBytes(Chip,nRegAddrSize,(unsigned int)*lpRegAddr,lpData,(long)nDataSize);
    if(ret != 1) /* IIC error */
     return 1;
#endif
           // printf("I2c Write nRegAddrSize %u, *lpRegAddr %u , *u8lpRegAddr%u ,nDataSize %u, *lpData %u\r\n", nRegAddrSize,lpRegAddr,(U8 *)lpRegAddr,nDataSize,lpData);

      if(MDrv_IIC_WriteBytes(SI2176_I2C_ADDR, 0,NULL, (U16) nDataSize, lpData)==0)
        {
           // printf("Si2176 IIC2 wirte error\r\n");
            return 1;
        }

  return 0;

}

//MS_BOOL MApi_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);

/* Si2176 IIC Read */
unsigned char Si2176_I2cRead(unsigned char Chip, unsigned char nRegAddrSize, unsigned int *lpRegAddr, unsigned short nDataSize, unsigned char *lpData)
{
  UNUSED_SAMSUNG(Chip);
  UNUSED_SAMSUNG(nRegAddrSize);
  UNUSED_SAMSUNG(lpRegAddr);

#ifdef SEMCO_IIC
  unsigned long ret;
    m_iic.Semco_I2c_ReadBytes(Chip,nRegAddrSize,(unsigned int)*lpRegAddr,lpData,(long)nDataSize);
    if(ret != 1) /* IIC error */
     return 1;
#endif
        if(MDrv_IIC_ReadBytes(SI2176_I2C_ADDR, 0, NULL, (U16) nDataSize, lpData)==0)
        {
            printf("Si2176 IIC2 read error %d\r\n",__LINE__);
           // printf("nRegAddrSize %u, *lpRegAddr %u , *u8lpRegAddr%u ,nDataSize %u, *lpData %u\r\n", nRegAddrSize,lpRegAddr,(U8 *)lpRegAddr,nDataSize,lpData);
            return 1;
        }
        else
        {
            //printf("I2C Read nRegAddrSize %u, *lpRegAddr %u , *u8lpRegAddr%u ,nDataSize %u, *lpData %u\r\n", nRegAddrSize,lpRegAddr,(U8 *)lpRegAddr,nDataSize,lpData);
        }
  return 0;
}



/* User Defined Delay */
void SemcoSleep(unsigned int nSleepTims_ms)
{
#ifdef SEMCO_IIC
    /* Semco IIC function */
  Sleep(nSleepTims_ms);
#endif
 UNUSED_SAMSUNG(nSleepTims_ms);
}

