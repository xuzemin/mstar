/******************************************************************************
**
**	Copyright (c) Newport Media Inc.  All rights reserved.
**
** 	Module Name:  nmicmndefs.h
**		These are the common defines that are being used by the ASIC driver.
**
** 
*******************************************************************************/

#ifndef _NMICMNDEFS_H_
#define _NMICMNDEFS_H_

/******************************************************************************
**
**	Macros
**
*******************************************************************************/
#define REV_A0         (0x0000a0)
#define REV_B0         (0x0000b0)

#define ISNM131(id)   (((id & 0xfff00) == 0x13100) ? 1 : 0) 
#define ISNM120(id)   (((id & 0xfff00) == 0x12000) ? 1: 0)
#define ISNM130(id)   (((id & 0xffff00) == 0x13000) ? 1: 0)
#define ISNM130v(id)  (((id & 0xffff00) == 0x813000) ? 1: 0)

#define ISREV(id, rev) ((((id) & 0x0000ff) == (rev   )) ? 1 : 0) 

#define HASATV(id)    (ISNM130(id) || ISNM130v(id) || ISNM131(id))
#define HASIF(id)     (ISNM120(id) || ISNM130(id) || ISNM131(id))
#define HASCVBS(id)   (ISNM131(id))
#define HASCVBSBBAUD(id) (ISNM131(id) && (!ISREV(id, REV_A0)))
#define HASVIFAIF(id) (ISNM130v(id) || ISNM131(id))


#define ISDTV(std)  ( ((std)==nDTV_6) || ((std)==nDTV_7) || ((std)==nDTV_8) ||\
					  ((std)==nDVBT_6)|| ((std)==nDVBT_7)|| ((std)==nDVBT_8))
#define ISATV(std)  ( (!ISDTV(std)) && ((std) != nInvalidNmiTvStd) )
#define ISCVBS(output) ( ((output) == nCvbsSif) || ((output) == nCvbsBBAud) )

/******************************************************************************
**
**	NMI Bus Type
**
*******************************************************************************/

typedef enum {
	nI2C,
	nUSB
} tNmiBus;

/******************************************************************************
**
**	NMI TV Standard
**	(*Note: Don't modify the order here)
**
*******************************************************************************/

typedef enum {
	nNTSC = 0,
	nPAL_G,			
	nPAL_M,
	nPAL_N,
	nPAL_K,
	nPAL_L,
	nDTV_6,
	nSECAM_L,
	nDTV_7,
	nSECAM_B,
	nPAL_I,
	nSECAM_D,
	nDTV_8,
	nFM_RADIO,
	nDVBT_6,
	nDVBT_7,
	nDVBT_8,
	nNmiTvStdMax,
	nInvalidNmiTvStd=0xffffffff
} tNmiTvStd;

/******************************************************************************
**
**	Lna Gain
**
*******************************************************************************/
typedef enum
{
	nHiGain = 0,
	nMiGain,
	nLoGain,
	nBypass,
	nAtten6,
	nAtten12,
	nAtten18,
} tNmiLnaGain;

typedef struct 
{
	uint8_t bbli_upper;
	uint8_t bbli_lower;
	uint8_t bbli_upper2;
	uint8_t bbli_lower2;
	bool_t bbli_avg_enable;
	u17_15_t bbli_avg_weight;

	bool_t use_dagc;
	u17_15_t dagc_upper;
	u17_15_t dagc_lower;
	u17_15_t dagc_upper2;
	u17_15_t dagc_lower2;
	bool_t dagc_avg_enable;
	u17_15_t dagc_avg_weight;		
} tNmiSwrfliArg;
/******************************************************************************
**
**	Output
**
*******************************************************************************/
typedef enum
{
	nCvbsSif = 0,
	nCvbsBBAud,
	nIf,
	nZif,
	nVifAif,	
	nNmiOutputMax,
	nInvalidNmiOutput=0xffffffff
} tNmiOutput;

typedef enum
{
	nDacDefault = 0,
	nDac1,
	nDac2,
	nDacBoth,
	nInvalidNmiDacSel=0xffffffff
} tNmiDacSel;

typedef enum
{
	nManualLoop1 = 0,
	nManualLoop2,
	nManualLoop3,
	nManualLoop4,
} tManualLoop;
/******************************************************************************
**
**	Debug Flags Defines
**
*******************************************************************************/

#define N_INIT			0x01
#define N_ERR			0x02
#define N_WARN          0x04
#define N_FUNC			0x08
#define N_INFO			0x10
#define N_DBG			0x20
#define N_VERB          0x40
#define N_SEEK          0x80


#endif

