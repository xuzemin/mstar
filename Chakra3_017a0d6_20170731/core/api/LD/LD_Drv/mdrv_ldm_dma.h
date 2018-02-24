
#ifndef _MDRV_LDM_DMA_H_
#define _MDRV_LDM_DMA_H_


#include "Board.h"

#if ( LD_ENABLE)


#include "MsTypes.h"
//#include "msReg.h"

#include "mdrv_mfc_spi.h"

//#include "mdrv_ld.h"


#ifdef _MDRV_LDM_DMA_C_
    #define _MDRV_LDM_DMA_DEC_
#else
    #define _MDRV_LDM_DMA_DEC_  extern
#endif


#define LDM_DMA_PORT  1//(psDrvLdInfo->u8LdDmaSpiPort)

#if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAYA)

    #define LDM_DMA_REG_BASE        0x102D00
    #define LDM_DMA_REG_BASE_OFFSET 0x80

#else
    #define LDM_DMA_REG_BASE_OFFSET 0x100
#endif

#define LDM_DMA_REG(x)  (LDM_DMA_REG_BASE+LDM_DMA_REG_BASE_OFFSET*LDM_DMA_PORT+x)
#if ENABLE_TWO_SPI
#define LDM_DMA_PORT2   MSPI_PORT_NUM2
#define LDM_DMA_REG2(x) (LDM_DMA_REG_BASE+LDM_DMA_REG_BASE_OFFSET*LDM_DMA_PORT2+x)
#elif ENABLE_FOUR_SPI
#define LDM_DMA_PORT2   MSPI_PORT_NUM2
#define LDM_DMA_REG2(x)  (LDM_DMA_REG_BASE+LDM_DMA_REG_BASE_OFFSET*LDM_DMA_PORT2+x)
#define LDM_DMA_PORT3   MSPI_PORT_NUM3
#define LDM_DMA_REG3(x)  (LDM_DMA_REG_BASE+LDM_DMA_REG_BASE_OFFSET*LDM_DMA_PORT3+x)
#define LDM_DMA_PORT4   MSPI_PORT_NUM4
#define LDM_DMA_REG4(x)  (LDM_DMA_REG_BASE+LDM_DMA_REG_BASE_OFFSET*LDM_DMA_PORT4+x)
#endif


#define LDM_MAX_SPI_CMD_NUM     10//ursa7 , 10

typedef enum
{
    E_LDM_SPI_TRIGER_STOP,
    E_LDM_SPI_TRIGER_ONE_SHOT,
    E_LDM_SPI_TRIGER_EVERY_V_SYNC,
}EnuLdmSpiTriggerMode;

void MDrv_LDM_DMA_Init(void);

void MDrv_LDM_DMA_SetMenuloadNumber( U16 u16Number );

void MDrv_LDM_DMA_SetSPICommandFormat( U8 u8CmdLen, U16* pu16CmdBuf, BOOL bEnCheckSum );

void MDrv_LDM_DMA_SetSpiTriggerMode( EnuLdmSpiTriggerMode eLdmSpiTriggerMode );

void MDrv_LDM_DMA_Set_DMA0_Data(U16 u16Index, U16 u16Data);

void MDrv_LDM_DMA_Set_DMA0_Datas(U16 u16BufLen, U16* pu16Buf, BOOLEAN bTrigger, BOOLEAN bWaitDone);

void MDrv_LDM_DMA_Set_TrigDelay(U32 u32Delay);

#endif
#endif


