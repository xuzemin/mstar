
#include "Board.h"

#include "Utl.h"

#include "msAPI_PnlBin.h"



// Customer ID list
// No.   Customer Name   "ID Value (2 bytes)"
// 1   MStar    x0000
// 2   AUO     0x0100
// 3   CMI     0x0200
// 4   HISENSE  0x0300
// 5   CSOT         x0400
// 6   AmTRAN   0x0500
// 7   TCL     0x0600
// 8   TSB     0x0700
// 9   LGD     0x0800
// 10  SEC     0x0900
// 11  LGE     0x0A00


/*
typedef struct
{
#if 1
    U16 u16BinID;       //BIN ID
    U16 u16CustomerID;  // Customer ID
    U16 u16BinChecksum; // CheckSum
    U32 u32Data_Len;    // Data Length
    U8  au8Description[18]; // BIN description
    U8  au8Resserved[4]; // Reserved
#endif
} STRU_PNL_BIN_HEADER;
*/

BOOLEAN msAPI_PNL_BIN_Get_BinHeader(U8* pu8BinData, STRU_PNL_BIN_HEADER *pPnlBinHeader )
{
    //U8 u8Idx;

    if( sizeof(STRU_PNL_BIN_HEADER) != PNL_BIN_HEADER_SIZE )
    {
        printf("\nError: PnlBin struct size=%u is wrong!\n", sizeof(STRU_PNL_BIN_HEADER));
        return FALSE;
    }

    memcpy( pPnlBinHeader, pu8BinData, PNL_BIN_HEADER_SIZE );

#if 0
    pPnlBinHeader->u16BinID =

    BinHeader->BIN_ID = MIU16(u32Addr);
    BinHeader->CUS_ID = MIU16(u32Addr+2);
    BinHeader->CHKSUM = MIU16(u32Addr+4);
    BinHeader->Data_Len = ((U32)MIU16(u32Addr+8)<<16) | (MIU16(u32Addr+6));

    if (BinHeader->Data_Len == 0x00)
        return FALSE;

    for (u8Idx=0; u8Idx<18; u8Idx++)
    {
        BinHeader->BIN_Description[u8Idx] = MIU8(u32Addr+10+u8Idx);
    }
    BinHeader->BIN_Description[18] = '\0';
#endif

    return TRUE;
}

U16 msAPI_PNL_BIN_Cal_Checksum(U8* pu8BinData, U32 u32BinDataSize)
{
    U32 i;
    U16 u16BinChecksum = 0;


    for( i = 0; i < u32BinDataSize; ++ i )
    {
        if( i == 4 || i == 5 )
        {
        }
        else
        {
            u16BinChecksum += pu8BinData[i];
        }
    }

    return u16BinChecksum;
}


