#include "Board.h"

#include "Panel.h"


#if( ENABLE_OVERDRIVE&&ENABLE_OD_BIN )

#include "BinInfo.h"
#include "sysinfo.h"
#include "SysInit.h"

#include "Utl.h"

#include "msAPI_BDMA.h"
#include "msAPI_Flash.h"
#include "msAPI_PnlBin.h"
#include "msAPI_OverDrive.h"



#define DEBUG_OD(x)       //x


#define OD_BIN_SIZE_MAX   5000

#define OD_BIN_TMP_BUF_MEM_ADDR (POOL_BUFFER_MEMORY_TYPE & MIU1 ?POOL_BUFFER_ADR | MIU_INTERVAL: POOL_BUFFER_ADR)

#define OD_DECOMP_TMP_BUF_1     (MsOS_PA2KSEG1(OD_BIN_TMP_BUF_MEM_ADDR+0x8000))
#define OD_DECOMP_TMP_BUF_2     (MsOS_PA2KSEG1(OD_BIN_TMP_BUF_MEM_ADDR+0x10000))


#define BIN_DATA_OFFSET_PNL_BIN_HEADER      0

#define BIN_DATA_OFFSET_OD_BIN_HEADER       (BIN_DATA_OFFSET_PNL_BIN_HEADER+PNL_BIN_HEADER_SIZE)

#define BIN_DATA_OFFSET_OD_2D_TBL_NUM       (BIN_DATA_OFFSET_OD_BIN_HEADER+0)
#define BIN_DATA_OFFSET_OD_3D_TBL_NUM       (BIN_DATA_OFFSET_OD_BIN_HEADER+1)
#define BIN_DATA_OFFSET_OD_RGB_SEP_FLAG     (BIN_DATA_OFFSET_OD_BIN_HEADER+2)
#define BIN_DATA_OFFSET_OD_TBL_DATA         (BIN_DATA_OFFSET_OD_BIN_HEADER+4)

#define OD_BIN_DATA_OFFSET_INVALID      0

#define OD_TBL_33x33_SIZE   1056
#define OD_TBL_17x17_SIZE   289


typedef struct
{
    U32 u32ODBinFileSize;
    U32 u32ODBinFlashAddr;

    U8 au8TblNum[2]; // 2D, 3D

    // RBG Separate Flag is at bit0:
    //  0: OD RGB channels use same table
    //  1: OD RGB channels use different tables
    U8 bRGBSeperateFlag : 1;

    // No-2nd-OD is at bit1:
    // 0: 2nd OD table is included in the BIN
    // 1: 2nd OD table is not included in the BIN
    U8 bNo2ndOdFlag : 1;

} StruODBinInfo;

static StruODBinInfo s_OD_BIN_Info;

static BOOL s_OD_BIN_bInitDone = 0;


//================================================================================
U32 _msAPI_OD_BIN_Get_TblOffset(BOOL bIs3D, U8 u8TblIdx, U8 u8RGBChannel, U8 u8TblType );

BOOL msAPI_OD_BIN_Init(void)
{
    BININFO BinInfo;
    BOOLEAN bResult;
    STRU_PNL_BIN_HEADER stPnlBinHeader;
    U16 u16BinChecksum = 0;
    //U8 au8BinData[OD_BIN_SIZE_MAX] = {0};
    U32 u32BinDataMemAddr = OD_BIN_TMP_BUF_MEM_ADDR;
    U8* pu8BinData;


    DEBUG_OD( printf("msAPI_OD_BIN_Init()\n"););

    s_OD_BIN_bInitDone = FALSE;

    memset( &s_OD_BIN_Info, 0, sizeof(StruODBinInfo) );

    BinInfo.B_ID = (U32)BIN_ID_OVERDRIVE;
    MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
    if ( bResult != PASS)
    {
         printf( "could not find OD bin on flash.\n" );
         return FALSE;
    }

    s_OD_BIN_Info.u32ODBinFileSize = BinInfo.B_Len;
    s_OD_BIN_Info.u32ODBinFlashAddr = BinInfo.B_FAddr;

    DEBUG_OD( printf(" B_FAddr=0x%x\n", BinInfo.B_FAddr ); );
    DEBUG_OD( printf(" B_Len=0x%x\n", BinInfo.B_Len); );
    DEBUG_OD( printf(" B_IsComp=0x%x\n", BinInfo.B_IsComp); );

    //check bin length
    if( BinInfo.B_Len > OD_BIN_SIZE_MAX)
    {
        printf("\n!!ERROR!! OD bin is too big!\n");
        return FALSE;
    }


    //u32BinDataMemAddr = MsOS_VA2PA((U32)au8BinData);

    pu8BinData = (U8*)MsOS_PA2KSEG1(u32BinDataMemAddr);

    DEBUG_OD(printf(" au8BinData=0x%x\n", (U32)pu8BinData);)
    DEBUG_OD(printf(" u32BinDataMemAddr=0x%x\n", u32BinDataMemAddr);)

    if( !MDrv_DMA_LoadBin(&BinInfo, (U32)pu8BinData, OD_DECOMP_TMP_BUF_1, OD_DECOMP_TMP_BUF_2) )
    {
        printf("\n!!ERROR!! !Load TCONtable Fail!\n");
        return FALSE;
    }

    //if (Get_BinHeader(&TCON_BinHeader, s_TCON_BIN_u32MemAddr))
    if( msAPI_PNL_BIN_Get_BinHeader( &(pu8BinData[BIN_DATA_OFFSET_PNL_BIN_HEADER]), &stPnlBinHeader) )
    {
        DEBUG_OD(printf(" BIN_ID=0x%x\n", stPnlBinHeader.u16BinID);)
        DEBUG_OD(printf(" CUS_ID=0x%x\n", stPnlBinHeader.u16CustomerID);)
        DEBUG_OD(printf(" CHKSUM=0x%x\n", stPnlBinHeader.u16BinChecksum);)
        DEBUG_OD(printf(" Data_Len=0x%x\n", stPnlBinHeader.u32Data_Len);)
    }
    else
    {
        printf("\nError: Get_PnlBinHeader fail!\n");
        return FALSE;
    }

    // Check bin id
    if( (stPnlBinHeader.u16BinID < PNL_BIN_ID_OD_START)
      ||(stPnlBinHeader.u16BinID > PNL_BIN_ID_OD_END)
      )
    {
        printf( "\nError! OD bin header-id(0x%X) is wrong\n", stPnlBinHeader.u16BinID);
        return FALSE;
    }

    // Check data size
    if( stPnlBinHeader.u32Data_Len + PNL_BIN_HEADER_SIZE > BinInfo.B_Len )
    {
        printf( "\nError! OD bin data-len=(0x%X) is wrong\n", stPnlBinHeader.u32Data_Len);
        return FALSE;
    }

    // Check checksum
    u16BinChecksum = msAPI_PNL_BIN_Cal_Checksum(pu8BinData, stPnlBinHeader.u32Data_Len + PNL_BIN_HEADER_SIZE);
    if( u16BinChecksum != stPnlBinHeader.u16BinChecksum )
    {
        //printf(" u16BinChecksum=0x%X\n", u16BinChecksum);
        printf( "\nError! OD bin checksum is wrong!(%X,%X)\n", stPnlBinHeader.u16BinChecksum, u16BinChecksum);
        return FALSE;
    }


    s_OD_BIN_Info.au8TblNum[OD_BIN_TBL_2D] = pu8BinData[BIN_DATA_OFFSET_OD_2D_TBL_NUM];
    s_OD_BIN_Info.au8TblNum[OD_BIN_TBL_3D] = pu8BinData[BIN_DATA_OFFSET_OD_3D_TBL_NUM];
    DEBUG_OD(printf(" s_OD_BIN_Info.au8TblNum[]=%u,%u\n", s_OD_BIN_Info.au8TblNum[0], s_OD_BIN_Info.au8TblNum[1]););


    s_OD_BIN_Info.bRGBSeperateFlag = pu8BinData[BIN_DATA_OFFSET_OD_RGB_SEP_FLAG]&1;
    s_OD_BIN_Info.bNo2ndOdFlag = (pu8BinData[BIN_DATA_OFFSET_OD_RGB_SEP_FLAG]>>1)&1;
    DEBUG_OD(printf(" bRGBSeperateFlag=%u\n", s_OD_BIN_Info.bRGBSeperateFlag); );
    DEBUG_OD(printf(" bNo2ndOdFlag=%u\n", s_OD_BIN_Info.bNo2ndOdFlag); );

    s_OD_BIN_bInitDone = TRUE;

#if 0

    // 2D, table 0, R,
    _msAPI_OD_BIN_Get_TblOffset(OD_BIN_TBL_2D, 0, 0, 0 );
    // 2D, table 0, G,
    _msAPI_OD_BIN_Get_TblOffset(OD_BIN_TBL_2D, 0, 1, 0 );
    // 2D,table 0,  B,
    //_msAPI_OD_BIN_Get_TblOffset(OD_BIN_TBL_2D, 0, 2, 0 );

    // 3D, table 0, R,
    //_msAPI_OD_BIN_Get_TblOffset(OD_BIN_TBL_3D, 0, 0,  0 );

#endif

    return TRUE;
}

U32 _msAPI_OD_BIN_Get_TblOffset(BOOL bIs3D, U8 u8TblIdx, U8 u8RGBChannel, U8 u8TblType )
{

    U32 u32Offset = OD_BIN_DATA_OFFSET_INVALID;
    U32 u32ODTblSizePerOneChannel = (s_OD_BIN_Info.bNo2ndOdFlag?(OD_TBL_33x33_SIZE):(OD_TBL_33x33_SIZE+OD_TBL_17x17_SIZE));
    U32 u32ODTblSizePerAllChannel;
    U32 u32ODTblSizePerAll2D;


    DEBUG_OD( printf("_msAPI_OD_BIN_Get_TblOffset(bIs3D=%u, u8TblIdx=%u,u8RGBChannel=%u, u8TblType=%u)\n", bIs3D, u8TblIdx,u8RGBChannel, u8TblType); );

    if( s_OD_BIN_bInitDone == FALSE )
        return OD_BIN_DATA_OFFSET_INVALID;

    if( bIs3D )
    {
        if( s_OD_BIN_Info.au8TblNum[OD_BIN_TBL_3D] == 0 )
        {
            printf("\nError: There is no 3D OD tbl!\n");
            return OD_BIN_DATA_OFFSET_INVALID;
        }
    }

    if( u8RGBChannel > 2 )
        return OD_BIN_DATA_OFFSET_INVALID;
    else if( u8RGBChannel > 0 ) // G or B channel
    {
        if( s_OD_BIN_Info.bRGBSeperateFlag == 0 ) // There are only one channel data
        {
            u8RGBChannel = 0;
        }
    }

    if( u8TblType >= OD_BIN_TBL_TYPE_17X17 ) // Want to get 2nd tbl data
    {
        if( s_OD_BIN_Info.bNo2ndOdFlag == 0 ) // There is no 2nd OD tbl
        {
            printf("\nError: There is no 2nd-OD tbl!\n");
            return OD_BIN_DATA_OFFSET_INVALID;
        }
    }


    if( s_OD_BIN_Info.bRGBSeperateFlag )
        u32ODTblSizePerAllChannel = u32ODTblSizePerOneChannel * 3;
    else
        u32ODTblSizePerAllChannel = u32ODTblSizePerOneChannel;

    u32ODTblSizePerAll2D = u32ODTblSizePerAllChannel * s_OD_BIN_Info.au8TblNum[OD_BIN_TBL_2D];

    DEBUG_OD( printf(" u32ODTblSizePerOneChannel=0x%X\n", u32ODTblSizePerOneChannel); );
    DEBUG_OD( printf(" u32ODTblSizePerAllChannel=0x%X\n", u32ODTblSizePerAllChannel); );
    DEBUG_OD( printf(" u32ODTblSizePerAll2D=0x%X\n", u32ODTblSizePerAll2D); );


    u32Offset = BIN_DATA_OFFSET_OD_TBL_DATA;

    // Shift to 2D/3D tbl start
    if( bIs3D )
        u32Offset += u32ODTblSizePerAll2D;

    // Shift to tbl n
    u32Offset += (u8TblIdx * u32ODTblSizePerAllChannel);

    // Shift to channel R/G/B
    u32Offset += (u8RGBChannel * u32ODTblSizePerOneChannel);

    // Shift to 33x33/17x17
    if( u8TblType >= OD_BIN_TBL_TYPE_17X17 )
        u32Offset += OD_TBL_33x33_SIZE;


    DEBUG_OD( printf(" u32Offset=0x%X\n", u32Offset); );

    return u32Offset;
}

BOOL msAPI_OD_BIN_Get_TableData(BOOL bIs3D, U8 u8TblIdx, U8 u8RGBChannel, U8 u8TblType, U8* pu8TblDataBuf, U16 u16BufSize)
{
    U32 u32Offset = OD_BIN_DATA_OFFSET_INVALID;
    U32 u32DataSize;


    DEBUG_OD( printf("msAPI_OD_BIN_Get_TableData(bIs3D=%u, u8TblIdx=%u,u8RGBChannel=%u, u8TblType=%u)\n", bIs3D, u8TblIdx, u8RGBChannel, u8TblType); );

    if( s_OD_BIN_bInitDone == FALSE )
        return FALSE;


    if( u8TblType == OD_BIN_TBL_TYPE_33x33 )
        u32DataSize = OD_TBL_33x33_SIZE;
    else
        u32DataSize = OD_TBL_17x17_SIZE;

    // Check buffer size
    if( u32DataSize > u16BufSize )
    {
        printf("\nError: Get OD tbl: buffer size=%u is too small!\n", u16BufSize);
        return FALSE;
    }


    u32Offset = _msAPI_OD_BIN_Get_TblOffset(bIs3D, u8TblIdx, u8RGBChannel, u8TblType);
    if( u32Offset == OD_BIN_DATA_OFFSET_INVALID )
    {
        printf("\nError: Get OD tbl offset failed!\n");
        return FALSE;
    }

    DEBUG_OD( printf(" TblOffset=0x%X\n", u32Offset); );


    // Copy OD data from flash to buffer
    if( FALSE == msAPI_Flash_Read(s_OD_BIN_Info.u32ODBinFlashAddr + u32Offset,
                    u32DataSize, pu8TblDataBuf) )
    {
        printf("\nError: Get OD tbl: Read flash failed!\n");
        return FALSE;
    }

#if 0 // printf data
{
    U16 i;
    printf("\nOD data:\n");
    for( i = 0; i < u32DataSize; ++ i )
    {
        printf("%02X,", pu8TblDataBuf[i]);
        if( (i % 16) == 15 )
            printf("\n");
    }
    printf("\n");
}

#endif

    return TRUE;
}

#endif

