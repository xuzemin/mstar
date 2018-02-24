#ifndef _MDRV_LD_H_
#define _MDRV_LD_H_

#ifdef _MDRV_LD_C_
#define _MDRV_LD_
#else
#define _MDRV_LD_ extern
#endif

#include "Board.h"

#if ( LD_ENABLE )

#include "leddevice.h"


#define DRV_LD_USE_SWSPI    0

//#define LD_LR_ENGINE


void MDrv_LD_ISR(void);
BOOL MDrv_LD_Init(void);
void MDrv_LD_Int_Init(void);

void MDrv_LD_SPI_Init(void);
void MDrv_LD_LDF_Init(void);
void MDrv_LD_LDB_Init(void);
void MDrv_LD_SW_Init(void);
void MDrv_LD_Load_CompensationTable(const U8* pu8CompTable);
void MDrv_LD_Load_CompensationLowTable(const U8* pu8CompTable);
void MDrv_LD_Load_Edge2DTable(const U8* pu8Edge2DTable);


#if 0
void MDrv_LD_Set_PWM(U8 pwmch,U16 duty,U16 shift);
#endif
void MDrv_LD_Update_InputSize(U16 height,U16 width);

//_MDRV_LD_ void MDrv_LD_SetSpiClkDelayFromVsync(U16 u16Val);
#define MDrv_LD_SetSpiClkDelayFromVsync MDrv_LDM_DMA_Set_TrigDelay

_MDRV_LD_ void MDrv_LD_SetLedControlNumber(U16 u16Val);
_MDRV_LD_ void MDrv_LD_SetLedControlMode(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetLedAmplitude(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetLdbAmplitude(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetLocalDimmingStrength(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetGlobalDimmingStrength(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetCompensationEnable(BOOL bEn);
_MDRV_LD_ void MDrv_LD_SetCompensationGain(U8 u8Val);

//_MDRV_LD_ void MDrv_LD_DemoModeInit(void);
//_MDRV_LD_ void MDrv_LD_SetDemoMode(U8 mode);

_MDRV_LD_ void MDrv_LD_SetSpiOuputAvg(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetSpiOuputMin(U8 u8Val);
_MDRV_LD_ void MDrv_LD_SetSpiOuputMax(U8 u8Val);

#endif // LD_ENABLE

#endif // _MDRV_LD_H_
