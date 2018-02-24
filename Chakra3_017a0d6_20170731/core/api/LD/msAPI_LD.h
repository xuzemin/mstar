#ifndef _MAPI_LD_H_
#define _MAPI_LD_H_

#include "Board.h"

#if ( LD_ENABLE )


#ifdef _MAPI_LD_C_
    #define _MAPI_LD_DEC_
#else
    #define _MAPI_LD_DEC_ extern
#endif


//=============================================================================
BOOL MApi_LD_Init(void);
void MApi_LD_ISR_OVSync(void);
void MApi_LD_ISR_1ms(void);

void MApi_LD_Main(void);

BOOL MApi_LD_GetLDEnable(void);
void MApi_LD_SetLDEnable(BOOL enable);


void MApi_LD_Set_OutputVFreq(U16 u16OutVFreqX10);
void MApi_LD_Set_SpiClk_Delay_FromVsync(U16 u16OutVFreqX10);

void MApi_LD_Set_Globaldimming_Strength(BOOL enable, U8 level);
void MApi_LD_Set_Localdimming_Strength(BOOL enable, U8 level);

void MApi_LD_Set_VideoCompensation_Strength( U8 level);

//void MApi_LD_Config_OutputSignal_To_LED(U16 u16OutVFreqX10);
void MApi_LD_Set_OutputVFreq(U16 u16OutVFreqX100);


void MApi_LD_Set_AlgoSpiBlockAddr(U16* pu16SpiBlock);
void MApi_LD_Set_ShareMemLedDataAddr(U16* pu16LedDataAddr);

void MApi_LD_Set_HasNewLedData(void);
//=============================================================================

#endif // LD_ENABLE

#endif // _MAPI_LD_H_

