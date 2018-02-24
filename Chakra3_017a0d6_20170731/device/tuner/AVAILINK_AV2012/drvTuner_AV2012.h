#ifndef _DRVTUNER_AV2012_H_
#define _DRVTUNER_AV2012_H_

MS_BOOL MDrv_DVBS_Tuner_SetFreq(MS_U16 u16CenterFreq_MHz, MS_U32 u32SymbolRate_Ks);
MS_BOOL MDrv_DVBS_Tuner_Initial(void);
MS_BOOL MDrv_DVBS_Tuner_CheckLock(void);

#endif
