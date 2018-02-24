//
// Copyright (c) 2006-2007 MStar Semiconductor, Inc.
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

//////////////////////////////////////////////////////////////////////////////
///
/// @file   apiDTVFreqTable.h
/// @brief  DVBC Physical Channel Database API
/// @author MStar Semiconductor Inc.
//////////////////////////////////////////////////////////////////////////////

#if !defined(__API_DTVFREQTABLE_H__)
#define __API_DTVFREQTABLE_H__

#if (ENABLE_S2)
#include "apiDTVSatTable.h"
#include "msAPI_DTVSystem.h"

//#include "msAPI_Tuner.h"
#define SATDB_MODE 				1
#define MAX_NUM_OF_PCH 			3000 //max physical channel
#define MAX_NUM_OF_PCHBYSATID 	3000 //max physical channel of one satellite

#define MAX_PHYCHTABLEMAP  		((MAX_NUM_OF_PCH+7)/8)
//****************************************************************************
// Public attributes.
//****************************************************************************
//#define INVALID_FREQUENCY        0xFFFFFFFF
#define INVALID_CONSTELLATION    0xFFFFFFFF
#define INVALID_SYMBOLRATE       0xFFFF
#define INVALID_IQMODE           0xFFFFFFFF
#define INVALID_TAPASSIGN        0xFF
#define INVALID_FREQOFFSET       0xFFFFFFFF
#define INVALID_TUNERFREQOFFSET  0xFF  // tuner freq offset
#define INVALID_SATID 			 0xFF
#define INVALID_POLARITY 		 0xFF


#define INVALID_PCHINDEX         	0xFFFF
#define INVALID_POSBYSATID          0xFFFF   // position by SAT ID

typedef BYTE    ePCHDATA_MEMBER;
//----------------------------------
#define pftFREQUENCY        0x01
#define pftCONSTELLATION    0x02
#define pftSYMBOLRATE       0x03
#define pftIQMODE           0x04
#define pftTAPASSIGN        0x05
#define pftFREQOFFSET       0x06
#define pftTUNERFREQOFFSET  0x07
#define pftTPALL            0x08
#define pftTEREBANDWIDTH	0x09
#define pftSATID    		0x0a
#define pftPOLARITY    		0x0b
extern BOOLEAN MApi_DFT_SelectPCHEntity(WORD wPCH, MS_BOOL bSelected);
extern BOOLEAN MApi_DFT_IsPCHEntirySelect(WORD wPCH);
extern void MApi_DFT_UnSelectAllPCH(void);
extern void MApi_DB_DFT_CheckIfAnySamePCH(WORD *pwPhyChIdx, DTVPROGRAMID_M *pCarrierParam);
extern BOOLEAN MApi_DB_DFT_AddPhysicalChannel(WORD *pwPhyChIdx, DTVPROGRAMID_M *pCarrierParam);
extern WORD MApi_DB_DFT_PCHIndex2PositionBySatID(WORD wPchIndex,BYTE *pbSatID);
extern BOOLEAN MApi_DB_DFT_UpdatePhysicalChannel(WORD wPchIndex, DTVPROGRAMID_M *pCarrierParam);
extern BOOLEAN MApi_DB_DFT_DeletePhysicalChannel(WORD wPhyChIdx);

#endif
#endif // __API_DTVFREQTABLE_H__

