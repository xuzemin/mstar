#ifndef _MSAPI_PNL_BIN_H_
#define _MSAPI_PNL_BIN_H_


#include "Board.h"

#define STRCUT_PACK __attribute__ ((__packed__))


// BIN ID list
// No. BIN ID Name  "ID Value(2 bytes)"	Description
// 1  Gamma      x0000 - 0x00FF	Digital gamma
// 2  OD                0x0100 - 0x01FF
// 3  System    0x0200 - 0x02FF
// 4  LED	0x0300 - 0x03FF	LED PWM & HSC
// 5  TCON	0x0400 - 0x04FF
// 6  MOD	0x0500 - 0x05FF
#define PNL_BIN_ID_OD_START     0x100
#define PNL_BIN_ID_OD_END       0x1FF

#define PNL_BIN_ID_TCON_START   0x400
#define PNL_BIN_ID_TCON_END     0x4FF



typedef struct STRCUT_PACK
{
    U16 u16BinID;       //BIN ID
    U16 u16CustomerID;  // Customer ID
    U16 u16BinChecksum; // CheckSum
    U32 u32Data_Len;    // Data Length
    U8  au8Description[18]; // BIN description
    U8  au8Resserved[4]; // Reserved
} STRU_PNL_BIN_HEADER;


#define PNL_BIN_HEADER_SIZE   32


BOOLEAN msAPI_PNL_BIN_Get_BinHeader(U8* pu8BinData, STRU_PNL_BIN_HEADER *pPnlBinHeader );

U16 msAPI_PNL_BIN_Cal_Checksum(U8* pu8BinData, U32 u32BinDataSize);


#endif

