

#include "Board.h"

#include "Panel.h"

#if( ENABLE_TCON_2014 )

#include "BinInfo.h"
#include "SysInit.h"

#include "Utl.h"
#include "debug.h"

#include "msAPI_BDMA.h"
#include "msAPI_PnlBin.h"
#include "msAPI_TCON.h"

//=========================================================================


#define TCON_BIN_FORMAT_VER_1   0
#define TCON_BIN_FORMAT_VER_2   1

#ifndef TCON_BIN_FORMAT_VER_SEL
  #if( ENABLE_TCON_VER_20 )
    #define TCON_BIN_FORMAT_VER_SEL TCON_BIN_FORMAT_VER_2
  #else
    #define TCON_BIN_FORMAT_VER_SEL TCON_BIN_FORMAT_VER_1
  #endif
#endif


#define DEBUG_TCON(x)       //x

#define DEBUG_PARSE_RESULT      0

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
#define DEBUG_PANEL_INFO(x) x
#endif

#define TCON_WRITE_REG(addr, mask, val)   MDrv_WriteByteMask((addr),(val),(mask))

#define _TCON_BANK_BACKUP()     //U8 u8TConBankBackup = MDrv_ReadByte(REG_23FE);
#define _TCON_BANK_RESTORE()    //MDrv_WriteByte(REG_23FE, u8TConBankBackup)

//======================================================================
//#define ENABLE_TCON_BIN 1

#define TCON_USE_SWDB   0

//-----------------------------------------------------------------------------------------------------------

#define MAKEU16_BIG(ptr, x) (U16)((ptr)[(x)+1] + ((ptr)[(x)+0] << 8))
#define MAKEU24_BIG(ptr, x) (U32)(((ptr)[(x)+2]) + ((ptr)[(x)+1] << 8) + ((ptr)[(x)+0] << 16))
#define MAKEU32_BIG(ptr, x) (U32)((ptr)[(x)+3] + ((ptr)[(x)+2] << 8) + ((ptr)[(x)+1] << 16) + ((ptr)[(x)+0] << 24))

#define MAKEU16_Lit(ptr, x) (U16)((ptr)[(x)+0] + ((ptr)[(x)+1] << 8))
#define MAKEU24_Lit(ptr, x) (U32)(((ptr)[(x)+0]) + ((ptr)[(x)+1] << 8) + ((ptr)[(x)+2] << 16))
#define MAKEU32_Lit(ptr, x) (U32)((ptr)[(x)+0] + ((ptr)[(x)+1] << 8) + ((ptr)[(x)+2] << 16) + ((ptr)[(x)+3] << 24))
//------------------------------------------------------------------------------------------------------------

//#define TCON_CHANGE_SETTING_NONE        0
//#define TCON_CHANGE_SETTING_START       1
//#define TCON_CHANGE_SETTING_WAIT_UPDATE 2
//#define TCON_CHANGE_SETTING_DONE        3

//static U8 s_TCON_u8ChangeSettingState = TCON_CHANGE_SETTING_NONE;

//---------------------------------------------------------------------------

typedef enum
{
    TCON_TABTYPE_GENERAL        = 0,
    TCON_TABTYPE_GPIO           = 1,
    TCON_TABTYPE_SCALER         = 2,
    TCON_TABTYPE_MOD            = 3,
    TCON_TABTYPE_GAMMA          = 4,
    TCON_TABTYPE_POWER_SEQUENCE_ON = 5,
    TCON_TABTYPE_POWER_SEQUENCE_OFF = 6,
#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
    TCON_TABTYPE_PANEL_INFO     = 7,
    TCON_TABTYPE_OVER_DRIVER    = 8,
#endif

} E_TCON_SUB_TAB_TYPE;

typedef enum
{
    TCON_REG_TYPE__6BYTE = 0,
    TCON_REG_TYPE__4BYTE = 1,

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
    TCON_REG_TYPE__OVER_DRIVE = 8,
    TCON_REG_TYPE__PANEL_INFO_6BYTE = 9,
    TCON_REG_TYPE__PowerSequence_OnOff_15_bytes = 10,
#endif
} E_TCON_REG_TYPE;

typedef struct
{
    U8 u8SubTableType;  // TCON Sub-Table type
    U16 u16RegCount;    // Register count
    U8 u8RegType;       // Register type
    U32 u32RegListOffset; // Register offset
} STRCUT_PACK STRU_TCON_SUB_TABLE_INFO;

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
typedef struct
{
    U8 u8MajorVersion;
    U8 u8MinorVersion;

    U8 u8PanelInterface;
    U8 u8PanelSize;

    U16 u16Year;
    U8 u8Month;
    U8 u8Day;

    U8 au8ProjectName[16];
    U8 au8CustomerName[16];
} STRCUT_PACK STRU_TCON_20_VERSION_INFO;
#endif

//---------------------------------------------------------------------------

//static U32 g_Tcon_Reset_u32Time = 0;
//static U32 g_Tcon_Reset_u32VCnt = 0;
static BOOL g_Tcon_bInitDone = 0;

static BOOL s_TCON_BIN_bInitDone = 0;

static U32 s_TCON_BIN_u32MemAddr;

#define TCON_BIN_SIZE_MAX   8000
static U8 s_TCON_BIN_au8BinData[TCON_BIN_SIZE_MAX] = {0};


#define TCON_BIN_TBL_2D 0
#define TCON_BIN_TBL_3D 1
static U8 s_TCON_BIN_u8TblNum[2] = {0,0}; // 2D, 3D

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
static U8 s_TCON_BIN_u8SubTblNum = 0;
static const STRU_TCON_20_VERSION_INFO* s_TCON_BIN_pstTCON_20_VERSION_INFO;
#endif

#if(DEBUG_PARSE_RESULT)
BOOLEAN g_TCON_bDebugParse = 0;
#endif

//======================================================================

#define BIN_DATA_OFFSET_PNL_BIN_HEADER      0
#define BIN_DATA_OFFSET_TCON_BIN_HEADER     (BIN_DATA_OFFSET_PNL_BIN_HEADER+PNL_BIN_HEADER_SIZE)

#define BIN_DATA_OFFSET_TCON_2D_TBL_NUM     (BIN_DATA_OFFSET_TCON_BIN_HEADER+0)
#define BIN_DATA_OFFSET_TCON_3D_TBL_NUM     (BIN_DATA_OFFSET_TCON_BIN_HEADER+1)

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
    #define BIN_DATA_OFFSET_TCON_SUB_TBL_NUM (BIN_DATA_OFFSET_TCON_BIN_HEADER+2)
    #define BIN_DATA_OFFSET_TCON_VER_INFO   (BIN_DATA_OFFSET_TCON_BIN_HEADER+8)
    #define BIN_DATA__TCON_VER_INFO_SIZE    40
#endif

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
    #define BIN_DATA_OFFSET_TCON_SUB_TBL_START  (BIN_DATA_OFFSET_TCON_BIN_HEADER+0x30)
#else
    #define BIN_DATA_OFFSET_TCON_SUB_TBL_START  (BIN_DATA_OFFSET_TCON_BIN_HEADER+8)
#endif

#define BIN_DATA__TCON_SUB_TBL_INFO_SIZE    8

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
    #define BIN_DATA__TCON_SUB_TBL_INFO_NUM_MAX 9
    #define BIN_DATA__TCON_SUB_TBL_INFO_NUM     s_TCON_BIN_u8SubTblNum
#else
    #define BIN_DATA__TCON_SUB_TBL_INFO_NUM     7 // Every tcon-table has 7 sub-table
#endif

#define BIN_DATA__TCON_SUB_TBL_INFO_ALL_SIZE    (BIN_DATA__TCON_SUB_TBL_INFO_SIZE*BIN_DATA__TCON_SUB_TBL_INFO_NUM) // 8 X 7

U32 MDrv_TCON_BIN_Get_SubTableOffset(BOOL bIs3D, U8 u8TblIdx, U8 u8SubTblIdx)
{
    if( u8SubTblIdx >= BIN_DATA__TCON_SUB_TBL_INFO_NUM )
    {
        printf("\nError: u8SubTblIdx=%u is wrong!\n", u8SubTblIdx);
        u8SubTblIdx = 0;
        return 0;
    }

    if( bIs3D )
    {
        if( u8TblIdx >= s_TCON_BIN_u8TblNum[TCON_BIN_TBL_3D] )
        {
            printf("\nError: u8TblIdx=%u is wrong!\n", u8TblIdx);
            u8TblIdx = 0;
            return 0;
        }

        // 3D is after 2D, so add 2d sub table size
        u8TblIdx += s_TCON_BIN_u8TblNum[TCON_BIN_TBL_2D];
    }
    else
    {
        if( u8TblIdx >= s_TCON_BIN_u8TblNum[TCON_BIN_TBL_2D] )
        {
            printf("\nError: u8TblIdx=%u is wrong!\n", u8TblIdx);
            u8TblIdx = 0;
            return 0;
        }
    }

    return BIN_DATA_OFFSET_TCON_SUB_TBL_START
            + (u8TblIdx*BIN_DATA__TCON_SUB_TBL_INFO_ALL_SIZE)
            + (u8SubTblIdx*BIN_DATA__TCON_SUB_TBL_INFO_SIZE);
}

BOOL MDrv_TCON_BIN_Get_SubTableInfo(BOOL bIs3D, U8 u8TblIdx, U8 u8SubTblIdx,
                                        STRU_TCON_SUB_TABLE_INFO* pstTCON_SUB_TABLE_INFO)
{
    U32 u32SubTableOffset;

    DEBUG_TCON(printf("MDrv_TCON_BIN_Get_SubTableInfo(bIs3D=%u, u8TblIdx=%u, u8SubTblIdx=%u)\n", bIs3D, u8TblIdx, u8SubTblIdx););

    u32SubTableOffset = MDrv_TCON_BIN_Get_SubTableOffset(bIs3D, u8TblIdx, u8SubTblIdx);

    DEBUG_TCON(printf("  u32SubTableOffset=0x%X\n", u32SubTableOffset););

    if( u32SubTableOffset == 0 )
    {
        return FALSE;
    }

    memcpy(pstTCON_SUB_TABLE_INFO,
        &(s_TCON_BIN_au8BinData[u32SubTableOffset]),
        sizeof(STRU_TCON_SUB_TABLE_INFO) );

    return TRUE;
}

#if (ENABLE_TCON_BIN_IN_DB)
//#include "mw_usbdownload.h"
#include "MApp_USBDownload.h"
#include "msAPI_Flash.h"
#include "MApp_FlashMap.h"
#include "MApp_GlobalSettingSt.h"
#include "msAPI_FCtrl.h"

static FileEntry g_fileEntry_T;

void MApp_DetectUSB(void)
{
   extern U8 MDrv_USBGetPortEnableStatus(void);
   extern BOOLEAN MDrv_UsbDeviceConnect(void);
   extern BOOLEAN MDrv_UsbDeviceConnect_Port2(void);

   U8 u8PortEnStatus = 0;

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();
    if(((u8PortEnStatus & BIT0) == BIT0)&&MDrv_UsbDeviceConnect())
    {
        //MApp_UsbDownload_Init(BIT0, MApp_ZUI_SwUpdate_ProgressBar);
        MApp_UsbSaveData_SetPort(BIT0);
        printf(" USB port 0\n");
    }
    else if(((u8PortEnStatus & BIT1) == BIT1)&&MDrv_UsbDeviceConnect_Port2())
    {
        //MApp_UsbDownload_Init(BIT1, MApp_ZUI_SwUpdate_ProgressBar);
        MApp_UsbSaveData_SetPort(BIT1);
        printf(" USB port 1\n");
    }
    else
    {
        printf("Error> Unknown USB port\n");
        return;
    }

   if (!MApp_UsbSaveData_InitFileSystem())
   {
	   MApp_UsbSaveData_Exit();
	   printf("Exit");
	   return ;
   }
}

BOOLEAN MApp_SearchFirmwareByUSB(void)
{
   extern BOOLEAN MApp_UsbSaveData_SearchFileInRoot(U8* pu8FileName, FileEntry* pFileEntry);
   U8 u8RetValue = FALSE;
   U8 u8FileName[20] = "TCON.bin";

   MApp_DetectUSB();

   if(FALSE == MApp_UsbSaveData_SearchFileInRoot((U8 *)u8FileName, &g_fileEntry_T))
   {
      printf("No File \n");
	  u8RetValue = FALSE;
   }
   else
   {
      printf("have file ! \n");
	  u8RetValue = TRUE;
   }
   return u8RetValue;
}

void MDrv_TCON_Save_SUBBIN(void)
{
    extern void msAPI_BLoader_Reboot(void);
    extern void MApp_DB_GEN_SaveData_RightNow(void);

	U8 u8HandleNo;
    //U8 Data[256];
    U32 readBytes = 0;
    U32 u32Length = 0;
    //U8 i=0;

    if(MApp_SearchFirmwareByUSB() == TRUE)
    {
		u8HandleNo = msAPI_FCtrl_FileOpen(&g_fileEntry_T, OPEN_MODE_FOR_READ);
        if(u8HandleNo != FCTRL_INVALID_FILE_HANDLE)
		{
			printf("====erase flash addr = %lx====\n",FMAP_TCON_BIN_BANK_START*0x10000);
			if (msAPI_Flash_AddressErase(FMAP_TCON_BIN_BANK_START*0x10000, 0x10000, TRUE) == FALSE)
		    {
		        return; //FALSE;
		    }
    		//bResult = msAPI_FCtrl_FileSeek(u8HandleNo, 0x100, FILE_SEEK_SET);
    		//if (bResult == TRUE)
    		{
    			//u32Length = msAPI_FCtrl_FileRead(u8HandleNo, (U32 *)&Data, 256);
    			u32Length = msAPI_FCtrl_FileRead(u8HandleNo, DOWNLOAD_BUFFER_ADR, 256);

        		while(u32Length == 0)
        		{
					if (msAPI_Flash_Write(FMAP_TCON_BIN_BANK_START*0x10000 + readBytes, 256, (U8 *)_PA2VA(DOWNLOAD_BUFFER_ADR)/*(U8 *)Data*/) == TRUE)
				    {

				    }
                    u32Length = msAPI_FCtrl_FileRead(u8HandleNo, DOWNLOAD_BUFFER_ADR, 256);
        			readBytes = readBytes +256;
    			}
                printf("===u32Length = %d\n",u32Length);
                //for(i=0;i<u32Length;i++)
                //    printf("data[i=%d]=%x\n",i,Data[i]);

                if (msAPI_Flash_Write(FMAP_TCON_BIN_BANK_START*0x10000 + readBytes, 256 - u32Length, (U8 *)_PA2VA(DOWNLOAD_BUFFER_ADR)) == TRUE)
                {
                	stGenSetting.g_SysSetting.TconBinInDB = TRUE;
                }
                readBytes = readBytes + 256 - u32Length;
                printf("===readBytes = %d\n",readBytes);
                stGenSetting.g_SysSetting.TconBinSize = readBytes;
			}
         }
        msAPI_FCtrl_FileClose(u8HandleNo);
        MApp_DB_GEN_SaveData_RightNow();
        msAPI_BLoader_Reboot();
    }
}
#endif

BOOL MDrv_TCON_BIN_Parse_SubHeader(U8* pBinBuf)
{
    DEBUG_TCON( printf("MDrv_TCON_BIN_Parse_SubHeader()\n"); );

    s_TCON_BIN_u8TblNum[TCON_BIN_TBL_2D] = pBinBuf[BIN_DATA_OFFSET_TCON_2D_TBL_NUM];
    s_TCON_BIN_u8TblNum[TCON_BIN_TBL_3D] = pBinBuf[BIN_DATA_OFFSET_TCON_3D_TBL_NUM];
    DEBUG_TCON(printf(" s_TCON_BIN_u8TblNum=%u,%u\n", s_TCON_BIN_u8TblNum[0], s_TCON_BIN_u8TblNum[1]););

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)

    s_TCON_BIN_u8SubTblNum = pBinBuf[BIN_DATA_OFFSET_TCON_SUB_TBL_NUM];
    DEBUG_TCON( printf(" s_TCON_BIN_u8SubTblNum=%u\n", s_TCON_BIN_u8SubTblNum); );

    if( s_TCON_BIN_u8SubTblNum > BIN_DATA__TCON_SUB_TBL_INFO_NUM_MAX )
    {
        printf("\nError: s_TCON_BIN_u8SubTblNum=%u > %u\n", s_TCON_BIN_u8SubTblNum, BIN_DATA__TCON_SUB_TBL_INFO_NUM_MAX);
        return FALSE;
    }

    s_TCON_BIN_pstTCON_20_VERSION_INFO = (STRU_TCON_20_VERSION_INFO *)&(pBinBuf[BIN_DATA_OFFSET_TCON_VER_INFO]);
    DEBUG_TCON( printf(" Ver=%u.%u\n", s_TCON_BIN_pstTCON_20_VERSION_INFO->u8MajorVersion, s_TCON_BIN_pstTCON_20_VERSION_INFO->u8MinorVersion ); );

#endif

    return TRUE;
}


BOOL MDrv_TCON_BIN_Init(void)
{
    BININFO BinInfo;
    BOOLEAN bResult;
    STRU_PNL_BIN_HEADER stPnlBinHeader;
    U16 u16BinChecksum = 0;
    //U32 i;


    printf("MDrv_TCON_BIN_Init()\n");

#if( ENABLE_TCON_BIN_IN_DB )
    if(stGenSetting.g_SysSetting.TconBinInDB == TRUE)
    {
        BinInfo.B_FAddr = FMAP_TCON_BIN_BANK_START*0x10000;
        BinInfo.B_Len = stGenSetting.g_SysSetting.TconBinSize;
        DEBUG_TCON(printf("usr tcon bin addr = %lx,len = %d\n",BinInfo.B_FAddr,BinInfo.B_Len););

        //check bin length
        if( BinInfo.B_Len > TCON_BIN_SIZE_MAX)
        {
            printf("\n!!ERROR! TconBinSize=%u is too big!\n", BinInfo.B_Len);
            return FALSE;
        }

        s_TCON_BIN_u32MemAddr = MsOS_VA2PA((U32)s_TCON_BIN_au8BinData); //TCON_TBL_ADR;

        msAPI_Flash_Read(BinInfo.B_FAddr, BinInfo.B_Len, (U8 *)_PA2VA((U32)(s_TCON_BIN_u32MemAddr)));
    }
    else
#endif
    {

        BinInfo.B_ID = (U32)BIN_ID_TCON;
        MDrv_Sys_Get_BinInfo(&BinInfo, &bResult);
        if ( bResult != PASS)
        {
             printf( "could not find TCON binary on flash.\n" );
             return FALSE;
        }
        DEBUG_TCON( printf(" B_FAddr=0x%x\n", BinInfo.B_FAddr ); );
        DEBUG_TCON( printf(" B_Len=0x%x\n", BinInfo.B_Len); );
        //DEBUG_TCON( printf(" B_IsComp=0x%x\n", BinInfo.B_IsComp); );

    #if 0//( ENABLE_BIN_DATA_FROM_DRAM )
        s_TCON_BIN_u32MemAddr = BIN_GROUP_MEM_ADR + BinInfo.B_FAddr - MDrv_BinInfo_Get_BinData_FlashAddrStart();

        DEBUG_TCON( printf("s_TCON_BIN_u32MemAddr=%x\n", s_TCON_BIN_u32MemAddr); );

    #else

        //check bin length
        if( BinInfo.B_Len > TCON_BIN_SIZE_MAX)
        {
            printf("\n!!ERROR!! TCON.bin=%u is too big!\n", BinInfo.B_Len);
            return FALSE;
        }

        s_TCON_BIN_u32MemAddr = MsOS_VA2PA((U32)s_TCON_BIN_au8BinData); //TCON_TBL_ADR;

        DEBUG_TCON(printf(" s_TCON_BIN_au8BinData=0x%x\n", (U32)s_TCON_BIN_au8BinData););
        DEBUG_TCON(printf(" s_TCON_BIN_u32MemAddr=0x%x\n", s_TCON_BIN_u32MemAddr););

        if( !MDrv_DMA_LoadBin(&BinInfo, _PA2VA((U32)(s_TCON_BIN_u32MemAddr)), 0, 0) )
        {
            printf("\n!!ERROR!! !Load TCONtable Fail!\n");
            return FALSE;
        }
    #endif
    }

    //if (Get_BinHeader(&TCON_BinHeader, s_TCON_BIN_u32MemAddr))
    if( msAPI_PNL_BIN_Get_BinHeader( &(s_TCON_BIN_au8BinData[BIN_DATA_OFFSET_PNL_BIN_HEADER]), &stPnlBinHeader) )
    {
        DEBUG_TCON(printf(" BIN_ID=0x%x", stPnlBinHeader.u16BinID);)
        DEBUG_TCON(printf(" CUS_ID=0x%x", stPnlBinHeader.u16CustomerID);)
        DEBUG_TCON(printf(" CHKSUM=0x%x", stPnlBinHeader.u16BinChecksum);)
        DEBUG_TCON(printf(" Data_Len=0x%x\n", stPnlBinHeader.u32Data_Len);)
    }
    else
    {
        printf("\nError: Get_PnlBinHeader fail!\n");
        return FALSE;
    }

    // Check bin id
    if( (stPnlBinHeader.u16BinID < PNL_BIN_ID_TCON_START)
      ||(stPnlBinHeader.u16BinID > PNL_BIN_ID_TCON_END)
      )
    {
        printf( "\nError! Tcon bin header-id(0x%X) is wrong\n", stPnlBinHeader.u16BinID);
        return FALSE;
    }

    // Check data size
    if( stPnlBinHeader.u32Data_Len + PNL_BIN_HEADER_SIZE > BinInfo.B_Len )
    {
        printf( "\nError! Tcon bin data-len=(0x%X) is wrong\n", stPnlBinHeader.u32Data_Len);
        return FALSE;
    }

    // Check checksum
    u16BinChecksum = msAPI_PNL_BIN_Cal_Checksum(s_TCON_BIN_au8BinData, stPnlBinHeader.u32Data_Len + PNL_BIN_HEADER_SIZE);
    if( u16BinChecksum != stPnlBinHeader.u16BinChecksum )
    {
        //printf(" u16BinChecksum=0x%X\n", u16BinChecksum);
        printf( "\nError! Tcon bin checksum is wrong!(%X,%X)\n", stPnlBinHeader.u16BinChecksum, u16BinChecksum);
        return FALSE;
    }

    // Read sub-header
    if( FALSE == MDrv_TCON_BIN_Parse_SubHeader(s_TCON_BIN_au8BinData) )
    {
        printf( "\nError! Parse subheader fail\n");
        return FALSE;
    }


#if 0
{
    STRU_TCON_SUB_TABLE_INFO stTCON_SUB_TABLE_INFO;
    U8 i;

    for( i = 0; i < 7; ++ i )
    {
        MDrv_TCON_BIN_Get_SubTableInfo(0, 0, i, &stTCON_SUB_TABLE_INFO );

        printf(" i=%u\n", i );

        printf("  u8SubTableType=%u\n", stTCON_SUB_TABLE_INFO.u8SubTableType );
        printf("  u16RegCount=%u\n", stTCON_SUB_TABLE_INFO.u16RegCount );
        printf("  u8RegType=%u\n", stTCON_SUB_TABLE_INFO.u8RegType );
        printf("  u32RegListOffset=0x%X\n", stTCON_SUB_TABLE_INFO.u32RegListOffset );
    }
}
#endif


    s_TCON_BIN_bInitDone = TRUE;

    return TRUE;
}

// address: 4 Byte (Big Endian)
// mask:    1 Byte
// value:   1 Byte
void MDrv_TCON_BIN_DownloadTbl_Reg_6Byte(U8* pu8RegTable, U16 u16RegCount)
{
    U32 u32RegAddr;
    U8 u8Mask;
    U8 u8Value;
    U16 i;
    U8 u8TconBank = 0xFF;


    DEBUG_TCON( printf("MDrv_TCON_BIN_DownloadTbl_Reg_6Byte(u16RegCount=%u)\n", u16RegCount); );

    for( i = 0; i < u16RegCount; ++ i )
    {
        u32RegAddr = MAKEU32_BIG(pu8RegTable, 0);
        u8Mask = pu8RegTable[4];
        u8Value = pu8RegTable[5];

        if( u32RegAddr == 0x103000 )
        {
            u8TconBank = u8Value;
        }

    #if(DEBUG_PARSE_RESULT)
        if( g_TCON_bDebugParse )
        {
            if( (u32RegAddr&0xFFFF00) == 0x103000 )
                printf("(%u) %02X %06X,%02X,%02X\n", i, u8TconBank, u32RegAddr, u8Mask, u8Value);
            else
                printf("(%u)  %06X,%02X,%02X\n", i, u32RegAddr, u8Mask, u8Value);
        }
    #endif

        TCON_WRITE_REG(u32RegAddr, u8Mask, u8Value);

        pu8RegTable += 6;
    }
}

// address: 2 Byte (Big Endian)
// mask:    1 Byte
// value:   1 Byte
void MDrv_TCON_BIN_DownloadTbl_Reg_4Byte(U8* pu8RegTable, U16 u16RegCount)
{
    U32 u32RegAddr;
    U8 u8Mask;
    U8 u8Value;
    U16 i;


    DEBUG_TCON( printf("MDrv_TCON_BIN_DownloadTbl_Reg_4Byte(u16RegCount=%u)\n", u16RegCount); );

    for( i = 0; i < u16RegCount; ++ i )
    {
        u32RegAddr = MAKEU16_BIG(pu8RegTable, 0);
        u8Mask = pu8RegTable[2];
        u8Value = pu8RegTable[3];

    #if(DEBUG_PARSE_RESULT)
        if( g_TCON_bDebugParse )
        {
            printf("(%u) %06X,%02X,%02X\n", i, u32RegAddr, u8Mask, u8Value);
        }
    #endif

        TCON_WRITE_REG(u32RegAddr, u8Mask, u8Value);

        pu8RegTable += 4;
    }
}

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
//Sub-bank Address0x00 - 0x02	3	Address to set sub-bank number
//Sub-bank Mask     0x03 - 0x03	1	Mask of sub-bank number
//Sub-bank Number 0x04 - 0x04	1	Sub-bank number
//Address                  0x05 - 0x07	3	16-bit Register address
//Mask                      0x08 - 0x09	2	Mask
//Value                     0x0A - 0x0B	2	Value
//Delay Time            0x0C - 0x0D	2	Delay time
//Reserved              0x0E - 0x0E	1	Used for cmd Priority (For tool use)

void MDrv_TCON_BIN_DownloadTbl_PowerSequence_OnOff_15_bytes(U8* pu8RegTable, U16 u16RegCount)
{
    U32 u32SubBank; // Use 3 bytes
    U8 u8SubBankMask;
    U8 u8SubBankNum;

    U32 u32RegAddr;
    U16 u16Mask;
    U16 u16Value;

    U16 u16DelayTime;

    U16 i;


    DEBUG_TCON( printf("MDrv_TCON_BIN_DownloadTbl_PowerSequence_OnOff_15_bytes(u16RegCount=%u)\n", u16RegCount); );

    for( i = 0; i < u16RegCount; ++ i )
    {
        u32SubBank = MAKEU24_Lit(pu8RegTable, 0);
        u8SubBankMask = pu8RegTable[3];
        u8SubBankNum = pu8RegTable[4];

        u32RegAddr = MAKEU24_Lit(pu8RegTable, 5);
        u16Mask = MAKEU16_Lit(pu8RegTable, 8);
        u16Value = MAKEU16_Lit(pu8RegTable, 0xA);

        u16DelayTime = MAKEU16_Lit(pu8RegTable, 0xC);

    #if(DEBUG_PARSE_RESULT)
        if( g_TCON_bDebugParse )
        {
            printf("(%2u) %06X,%02X,%02X; %06X,%04X,%04X; %u\n", i, u32SubBank, u8SubBankMask, u8SubBankNum, u32RegAddr, u16Mask, u16Value, u16DelayTime );
        }
    #endif

        //TCON_WRITE_REG(u32RegAddr, u8Mask, u8Value);

        pu8RegTable += 15;
    }
}

static ST_PANEL_NEW_PANELTYPE g_stTCON_BIN_PNL =
{
    {
        "TCON_BIN_PNL",//m_pPanelName
        //////////////////////////////////////////////
        // Panel output
        //////////////////////////////////////////////
        0,          //BOOL m_bPanelDither :1;           //PANEL_DITHER          // 8/6 bits panel
        LINK_EXT,   // LINK_MINILVDS_2CH_3P_8BIT,  //BOOL m_ePanelLinkType :2;         //PANEL_LINK

        0,          //BOOL m_bPanelDualPort :1;         //PANEL_DUAL_PORT

        1^PANEL_CONNECTOR_SWAP_PORT,                    // shall swap if
                                                        // (PANEL_SWAP_PORT XOR Board_Connect_Swap) is TRUE

        0,          //BOOL m_bPanelSwapOdd_ML   :1;     //PANEL_SWAP_ODD_ML
        0,          //BOOL m_bPanelSwapEven_ML  :1;     //PANEL_SWAP_EVEN_ML
        0,          //BOOL m_bPanelSwapOdd_RB   :1;     //PANEL_SWAP_ODD_RB
        0,          //BOOL m_bPanelSwapEven_RB  :1;     //PANEL_SWAP_EVEN_RB

        PANEL_SWAP_LVDS_POL,

        0,          //BOOL m_bPanelSwapLVDS_CH  :1;     //PANEL_SWAP_LVDS_CH
        PANEL_PDP_10BIT,          //BOOL m_bPanelPDP10BIT     :1;     //PANEL_PDP_10BIT
        1,          //BOOL m_bPanelLVDS_TI_MODE :1;     //PANEL_LVDS_TI_MODE
        0x00,       //BYTE m_ucPanelDCLKDelay;          //PANEL_DCLK_DELAY
        0,          //BOOL m_bPanelInvDCLK  :1;         //PANEL_INV_DCLK
        0,          //BOOL m_bPanelInvDE        :1;     //PANEL_INV_DE
        0,          //BOOL m_bPanelInvHSync :1;         //PANEL_INV_HSYNC
        0,          //BOOL m_bPanelInvVSync :1;         //PANEL_INV_VSYNC

        ///////////////////////////////////////////////
        // Output tmming setting
        ///////////////////////////////////////////////
        // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
        0x01,       //BYTE m_ucPanelDCKLCurrent;        //PANEL_DCLK_CURRENT         // DCLK current
        0x01,       //BYTE m_ucPanelDECurrent;          //PANEL_DE_CURRENT           // DE signal current
        0x01,       //BYTE m_ucPanelODDDataCurrent;     //PANEL_ODD_DATA_CURRENT     // odd data current
        0x01,       //BYTE m_ucPanelEvenDataCurrent;    //PANEL_EVEN_DATA_CURRENT    // even data current

        30,         //BYTE m_ucPanelOnTiming1;          //PANEL_ON_TIMING1          // time between panel & data while turn on power
        200,        //BYTE m_ucPanelOnTiming2;          //PANEL_ON_TIMING2          // time between data & back light while turn on power
        220,        //BYTE m_ucPanelOffTiming1;         //PANEL_OFF_TIMING1         // time between back light & data while turn off power
        10,         //BYTE m_ucPanelOffTiming2;         //PANEL_OFF_TIMING2         // time between data & panel while turn off power

        32,         //BYTE m_ucPanelHSyncWidth;         //PANEL_HSYNC_WIDTH
        80,         //BYTE m_ucPanelHSyncBackPorch;     //PANEL_HSYNC_BACK_PORCH

        8,          //BYTE m_ucPanelVSyncWidth;         //PANEL_VSYNC_WIDTH
        11,         //BYTE m_ucPanelBackPorch;          //PANEL_VSYNC_BACK_PORCH

        // DE related
        0x70,       //MS_U16 m_wPanelHStart;     ///<  VOP_04[11:0], PANEL_HSTART, DE H Start (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
        0x00,       //MS_U16 m_wPanelVStart;     ///<  VOP_06[11:0], PANEL_VSTART, DE V Start
        1920,       // MS_U16 m_wPanelWidth;    ///< PANEL_WIDTH, DE width (VOP_05[11:0] = HEnd = HStart + Width - 1)
        1080,       // MS_U16 m_wPanelHeight;   ///< PANEL_HEIGHT, DE height (VOP_07[11:0], = Vend = VStart + Height - 1)

        2650,       //WORD m_wPanelMaxHTotal;           //PANEL_MAX_HTOTAL
        2400,       //WORD m_wPanelHTotal;              //PANEL_HTOTAL
        2340,       //WORD m_wPanelMinHTotal;           //PANEL_MIN_HTOTAL

        1480,       //WORD m_wPanelMaxVTotal;           //PANEL_MAX_VTOTAL
        1125,       //WORD m_wPanelVTotal;              //PANEL_VTOTAL 20060511 chris :for Frame Lock operation
        1090,       //WORD m_wPanelMinVTotal;           //PANEL_MIN_VTOTAL

        (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
        (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
        (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK

        0x0019,     //m_wSpreadSpectrumStep;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)
        0x00C0,     //m_wSpreadSpectrumSpan;        //Value for Spread_Spectrum_Control register(B7..3:Period,B2..0:Amplitude)

        0x6D,       //m_ucDimmingCtl

        255,        //m_ucMaxPWMVal;
        0x20,//63,  //m_ucMinPWMVal;
        0,          //BOOL m_bPanelDeinterMode  :1;     //PANEL_DEINTER_MODE
        E_PNL_ASPECT_RATIO_WIDE,
        //
        //  Board related params.
        //
       (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L,            //MS_U16 m_u16LVDSTxSwapValue
       TI_8BIT_MODE,               //8bit ti bit mode
       OUTPUT_10BIT_MODE,          //10bit ti bit mode
       0,          //   PANEL_SWAP_ODD_RG
       0,          //   PANEL_SWAP_EVEN_RG
       0,          //   PANEL_SWAP_ODD_GB
       0,          //   PANEL_SWAP_EVEN_GB
       1,          //   double clock
       0xFFFFFF,
       0x000000,
       E_PNL_CHG_DCLK,
       1,///<  PAFRC mixed with noise dither disable
    },
    (164),      //DWORD m_dwPanelMaxDCLK;           //PANEL_MAX_DCLK
    (150),      //DWORD m_dwPanelDCLK;              //PANEL_DCLK
    (120),      //DWORD m_dwPanelMinDCLK;           //PANEL_MIN_DCLK
    LINK_MINILVDS_2CH_3P_8BIT,   //Which extern type exactly, only valid when m_ePanelLinkType==LINK_EXT, otherwise, don't care
};

typedef enum
{
    TCON_PNL_INFO_ID_PANEL_LinkType     = 0,
    TCON_PNL_INFO_ID_PANEL_LinkExtType  = 1,

    TCON_PNL_INFO_ID_FIX_V_BACKPORCH    = 2,
    TCON_PNL_INFO_ID_FIX_H_BACKPORCH    = 3,

    TCON_PNL_INFO_ID_V_SYNC_START       = 11,
    TCON_PNL_INFO_ID_V_SYNC_END         = 12,
    TCON_PNL_INFO_ID_V_DE_START         = 13,
    TCON_PNL_INFO_ID_V_DE_END           = 14,

    TCON_PNL_INFO_ID_UNKNOWN            = 0xFFFF,

}EnuPanelInfoId;

void MDrv_TCON_BIN_PanelInfo_Set_Info(U16 u16PanelInfoId, U32 u32Value)
{
    u32Value=u32Value;

    switch(u16PanelInfoId)
    {
        case TCON_PNL_INFO_ID_PANEL_LinkType:
            // This valud is fixed!!
            //g_stTCON_BIN_PNL.stOldPanelTypeFromUtopia.m_ePanelLinkType = LINK_EXT;
            break;

        case TCON_PNL_INFO_ID_PANEL_LinkExtType:
            g_stTCON_BIN_PNL.enLinkExtType = (APIPNL_LINK_EXT_TYPE)u32Value;
            break;

        case TCON_PNL_INFO_ID_FIX_V_BACKPORCH: // 0 or 1
            // todo:
            break;

        case TCON_PNL_INFO_ID_FIX_H_BACKPORCH: // 0 or 1
            // todo
            break;

        case TCON_PNL_INFO_ID_V_SYNC_START:
            // todo:
            //g_stTCON_BIN_PNL. = u32Value;
            break;

        case TCON_PNL_INFO_ID_V_SYNC_END:
            // todo:
            //g_stTCON_BIN_PNL. = u32Value;
            break;

        case TCON_PNL_INFO_ID_V_DE_START:
            g_stTCON_BIN_PNL.stOldPanelTypeFromUtopia.m_wPanelVStart = u32Value;
            break;
        case TCON_PNL_INFO_ID_V_DE_END:
            //g_TCON_u16DE_V_End = u32Value;
            g_stTCON_BIN_PNL.stOldPanelTypeFromUtopia.m_wPanelHeight = u32Value - g_stTCON_BIN_PNL.stOldPanelTypeFromUtopia.m_wPanelVStart + 1;
            printf("m_wPanelHeight=%u\n", g_stTCON_BIN_PNL.stOldPanelTypeFromUtopia.m_wPanelHeight);
            break;

        case TCON_PNL_INFO_ID_UNKNOWN:
        default:
            printf("Unknown PnlInfoId=%u\n", u16PanelInfoId);
            break;
    }
}

//ID        0x00 - 0x01	2PanelInfo ID
//Value 0x02 - 0x05	4Value
void MDrv_TCON_BIN_Parse_PanelInfo_6_bytes(U8* pu8RegTable, U16 u16RegCount)
{
    U16 u16PanelInfoId;
    U32 u32Value;

    U16 i;


    DEBUG_TCON( printf("MDrv_TCON_BIN_Parse_PanelInfo_6_bytes(u16RegCount=%u)\n", u16RegCount); );

    for( i = 0; i < u16RegCount; ++ i )
    {
        u16PanelInfoId = MAKEU16_Lit(pu8RegTable, 0);
        u32Value = MAKEU32_Lit(pu8RegTable, 2);

    #if 1//(DEBUG_PARSE_RESULT)
        //if( g_TCON_bDebugParse )
        {
            DEBUG_PANEL_INFO( printf("(%2u) %u, 0x%X\n", i, u16PanelInfoId, u32Value ); );
        }
    #endif

        MDrv_TCON_BIN_PanelInfo_Set_Info( u16PanelInfoId, u32Value);

        pu8RegTable += 6;
    }
}

void MDrv_TCON_BIN_DownloadTbl_OverDrive(U8* pu8RegTable, U16 u16RegCount)
{
    printf("todo: MDrv_TCON_BIN_DownloadTbl_OverDrive(u16RegCount=%u)\n", u16RegCount);

    UNUSED(pu8RegTable);
}
#endif

void MDrv_TCON_BIN_DownloadSubTable(STRU_TCON_SUB_TABLE_INFO* pstTCON_SUB_TABLE_INFO)
{
    U8* pu8RegTable;
    U8 u8SubTableType;
    U16 u16RegCount;


    DEBUG_TCON( printf("MDrv_TCON_BIN_DownloadSubTable()\n"); );

    if( s_TCON_BIN_bInitDone == 0 )
    {
        printf("\nError: TCON BIN is not init!\n");
        return;
    }

    if( pstTCON_SUB_TABLE_INFO == NULL )
        return;


    u8SubTableType = pstTCON_SUB_TABLE_INFO->u8SubTableType;
    u16RegCount = pstTCON_SUB_TABLE_INFO->u16RegCount;
    DEBUG_TCON( printf("  u8SubTableType=%u\n", u8SubTableType ); );
    DEBUG_TCON( printf("  u16RegCount=%u\n", u16RegCount ); );

    if( u16RegCount == 0 )
    {
        DEBUG_TCON( printf(" => Empty sub table\n"); );
        return;
    }

    DEBUG_TCON( printf("   u8RegType=%u\n", pstTCON_SUB_TABLE_INFO->u8RegType ); );
    DEBUG_TCON( printf("   u32RegListOffset=0x%X\n", pstTCON_SUB_TABLE_INFO->u32RegListOffset ); );


    pu8RegTable = &(s_TCON_BIN_au8BinData[pstTCON_SUB_TABLE_INFO->u32RegListOffset]);

    switch( u8SubTableType )
    {
        default:
            printf("\nError: Unsupported tcon u8SubTableType=%u\n", u8SubTableType);
            break;

        case TCON_TABTYPE_GENERAL:
        case TCON_TABTYPE_GPIO:
        case TCON_TABTYPE_SCALER:
        case TCON_TABTYPE_MOD:
            if( pstTCON_SUB_TABLE_INFO->u8RegType == TCON_REG_TYPE__6BYTE )
            {
                MDrv_TCON_BIN_DownloadTbl_Reg_6Byte(pu8RegTable, u16RegCount );
            }
            else if( pstTCON_SUB_TABLE_INFO->u8RegType == TCON_REG_TYPE__4BYTE )
            {
                MDrv_TCON_BIN_DownloadTbl_Reg_4Byte(pu8RegTable, u16RegCount );
            }
            else
            {
                printf("\nError: Unsupported tcon reg-type=%u!\n", pstTCON_SUB_TABLE_INFO->u8RegType);
            }
            break;

    #if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
        case TCON_TABTYPE_POWER_SEQUENCE_ON:
        case TCON_TABTYPE_POWER_SEQUENCE_OFF:
            if( pstTCON_SUB_TABLE_INFO->u8RegType == TCON_REG_TYPE__PowerSequence_OnOff_15_bytes )
            {
                MDrv_TCON_BIN_DownloadTbl_PowerSequence_OnOff_15_bytes(pu8RegTable, u16RegCount);
            }
            else
            {
                printf("\nError: Unsupported reg-type=%u for PowerSeq OnOff!\n", pstTCON_SUB_TABLE_INFO->u8RegType);
            }
            break;

        case TCON_TABTYPE_PANEL_INFO:
            if( pstTCON_SUB_TABLE_INFO->u8RegType == TCON_REG_TYPE__PANEL_INFO_6BYTE )
            {
                MDrv_TCON_BIN_Parse_PanelInfo_6_bytes(pu8RegTable, u16RegCount);
            }
            else
            {
                printf("\nError: Unsupported reg-type=%u for PanelInfo!\n", pstTCON_SUB_TABLE_INFO->u8RegType);
            }
            break;

        case TCON_TABTYPE_OVER_DRIVER:
            if( pstTCON_SUB_TABLE_INFO->u8RegType == TCON_REG_TYPE__OVER_DRIVE )
            {
                MDrv_TCON_BIN_DownloadTbl_OverDrive(pu8RegTable, u16RegCount);
            }
            else
            {
                printf("\nError: Unsupported reg-type=%u for OD!\n", pstTCON_SUB_TABLE_INFO->u8RegType);
            }
            break;
    #endif

    }

}

BOOL MDrv_TCON_BIN_SwitchTable(BOOL bIs3D, U8 u8TblIdx)
{
    STRU_TCON_SUB_TABLE_INFO stTCON_SUB_TABLE_INFO;
    U8 i;


    DEBUG_TCON(printf("MDrv_TCON_BIN_SwitchTable(bIs3D=%u, u8TblIdx=%u)\n", bIs3D, u8TblIdx););

    if( s_TCON_BIN_bInitDone == 0 )
    {
        printf("\nError: TCON BIN is not init!\n");
        return FALSE;
    }

    for( i = 0; i < BIN_DATA__TCON_SUB_TBL_INFO_NUM; ++ i )
    {
        DEBUG_TCON( printf(" i=%u\n", i ); );

        if( FALSE == MDrv_TCON_BIN_Get_SubTableInfo(bIs3D, u8TblIdx, i, &stTCON_SUB_TABLE_INFO ) )
        {
            break;
        }

    #if(DEBUG_PARSE_RESULT)
        if( i >= 5)
            g_TCON_bDebugParse = 1;
        else
            g_TCON_bDebugParse = 0;
    #endif

    #if 0
        DEBUG_TCON( printf("  u8SubTableType=%u\n", stTCON_SUB_TABLE_INFO.u8SubTableType ); );
        DEBUG_TCON( printf("  u16RegCount=%u\n", stTCON_SUB_TABLE_INFO.u16RegCount ); );
        DEBUG_TCON( printf("  u8RegType=%u\n", stTCON_SUB_TABLE_INFO.u8RegType ); );
        DEBUG_TCON( printf("  u32RegListOffset=0x%X\n", stTCON_SUB_TABLE_INFO.u32RegListOffset ); );
    #endif

    #if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
        if( stTCON_SUB_TABLE_INFO.u8SubTableType == TCON_TABTYPE_PANEL_INFO )
        {
            continue;
        }
    #endif


        MDrv_TCON_BIN_DownloadSubTable(&stTCON_SUB_TABLE_INFO);
    }

    return TRUE;
}

#if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
BOOL MDrv_TCON_BIN_ReadPanelInfo(void)
{
    DEBUG_TCON( PRINT_CURRENT_LINE(); );
    DEBUG_TCON( printf("MDrv_TCON_BIN_ReadPanelInfo()\n"); );

    STRU_TCON_SUB_TABLE_INFO stTCON_SUB_TABLE_INFO;
    U8 i;


    if( s_TCON_BIN_bInitDone == 0 )
    {
        printf("\nError: TCON BIN is not init!\n");
        return FALSE;
    }

    for( i = 0; i < BIN_DATA__TCON_SUB_TBL_INFO_NUM; ++ i )
    {
        //DEBUG_TCON( printf(" i=%u\n", i ); );

        if( FALSE == MDrv_TCON_BIN_Get_SubTableInfo(FALSE, 0, i, &stTCON_SUB_TABLE_INFO ) )
        {
            break;
        }

    #if 0
        DEBUG_TCON( printf("  u8SubTableType=%u\n", stTCON_SUB_TABLE_INFO.u8SubTableType ); );
        DEBUG_TCON( printf("  u16RegCount=%u\n", stTCON_SUB_TABLE_INFO.u16RegCount ); );
        DEBUG_TCON( printf("  u8RegType=%u\n", stTCON_SUB_TABLE_INFO.u8RegType ); );
        DEBUG_TCON( printf("  u32RegListOffset=0x%X\n", stTCON_SUB_TABLE_INFO.u32RegListOffset ); );
    #endif

    #if(TCON_BIN_FORMAT_VER_SEL >= TCON_BIN_FORMAT_VER_2)
        if( stTCON_SUB_TABLE_INFO.u8SubTableType == TCON_TABTYPE_PANEL_INFO )
        {
            MDrv_TCON_BIN_DownloadSubTable(&stTCON_SUB_TABLE_INFO);
            break;
        }
    #endif

    }

    return TRUE;
}
#endif

void MDrv_TCON_ChangeSetting_Start(void)
{
#if 0
    if( s_TCON_u8ChangeSettingState == TCON_CHANGE_SETTING_WAIT_UPDATE )
    {
        printf("\nError: TCON_ChangeSetting_Start: state=WAIT_UPDATE\n");
        return;
    }

    s_TCON_u8ChangeSettingState = TCON_CHANGE_SETTING_START;

    _TCON_BANK_BACKUP();

    //printf("MDrv_TCON_ChangeSetting_Start() at %u\n", MsOS_GetSystemTime());

    MDrv_WriteByte(REG_23FE,0x0); //switch to sub bank 0

#if TCON_USE_SWDB
    MDrv_WriteRegBit(REG_2313,0,BIT7);
#else
    MDrv_Write2ByteMask(REG_2312,  BIT13, (_BIT15|BIT13)); //  Disable para update, En DB
#endif

    _TCON_BANK_RESTORE();
#endif
}

void MDrv_TCON_ChangeSetting_End(void)
{
#if 0
    if( s_TCON_u8ChangeSettingState != TCON_CHANGE_SETTING_START )
    {
        printf("\nError: TCON_ChangeSetting_End: state!=START\n");
        return;
    }

    //printf("MDrv_TCON_ChangeSetting_End() at %u\n", MsOS_GetSystemTime());

#if TCON_USE_SWDB

    s_TCON_u8ChangeSettingState = TCON_CHANGE_SETTING_WAIT_UPDATE;

#else

    _TCON_BANK_BACKUP();

    MDrv_WriteByte(REG_23FE, 0x0); //switch to sub bank 0
    MDrv_Write2Byte(REG_2312, BIT15      |BIT13); // tcon frame counter reset

    _TCON_BANK_RESTORE();

    s_TCON_u8ChangeSettingState = TCON_CHANGE_SETTING_DONE;

    if( g_Tcon_Reset_u32Time == 0 ) // First time reset
    {
        g_Tcon_Reset_u32Time = MsOS_GetSystemTime();
        g_Tcon_Reset_u32VCnt = MDrv_ISR_Get_VSyncCount();

      #if 0//( ENABLE_AUO_POWER_ON_SEQ )
        Cus_AUO_PwrSeq_TConResetDone();
      #endif
    }

#endif

#endif
}

#if 0//TCON_USE_SWDB
#define PREVIOUS_WAIT_VSYNC_NUM 1
#define WAIT_VSYNC_NUM          (4+PREVIOUS_WAIT_VSYNC_NUM)

void MDrv_TCON_VSync_ISR(void)
{
    static U8 su8_Tcon_u8WaitVSyncCount = 0;

    if( s_TCON_u8ChangeSettingState == TCON_CHANGE_SETTING_WAIT_UPDATE )
    {
        _TCON_BANK_BACKUP();

        MDrv_WriteByte(REG_23FE,0x0);//switch to sub bank 0

        su8_Tcon_u8WaitVSyncCount++;

        if (su8_Tcon_u8WaitVSyncCount == PREVIOUS_WAIT_VSYNC_NUM)
        {
            MDrv_WriteRegBit(REG_2313, BIT7,   BIT7  );//[15]
            MDrv_WriteRegBit(REG_2313, BIT6,   BIT6  );//[14]
        }
        else if(su8_Tcon_u8WaitVSyncCount == WAIT_VSYNC_NUM)
        {
            MDrv_WriteRegBit(REG_2313, 0x0,   BIT7  );//[15]
            MDrv_WriteRegBit(REG_2313, 0x0,   BIT6  );//[14]

            if( g_Tcon_Reset_u32Time == 0 ) // First time reset
            {
                g_Tcon_Reset_u32Time = MsOS_GetSystemTime();
                g_Tcon_Reset_u32VCnt = MDrv_ISR_Get_VSyncCount();

            #if 0//( ENABLE_AUO_POWER_ON_SEQ )
                Cus_AUO_PwrSeq_TConResetDone();
            #endif
            }
            s_TCON_u8ChangeSettingState = TCON_CHANGE_SETTING_DONE;
            su8_Tcon_u8WaitVSyncCount = 0;
        }

        _TCON_BANK_RESTORE();
    }
}
#endif

BOOL MDrv_TCON_SwitchTable(BOOL bIs3D, U8 u8TblIdx)
{
    BOOL bResult = TRUE;

    DEBUG_TCON(printf("MDrv_TCON_SwitchTable(bIs3D=%u, u8TblIdx=%u)\n", bIs3D, u8TblIdx););

    if( g_Tcon_bInitDone == 0 )
    {
        printf("\nError: TCON is not init!\n");
        return FALSE;
    }

#if 1
    MDrv_TCON_ChangeSetting_Start();

    //MDrv_Pnl_LoadTconSetting(bIs3D); // Load 2D setting

#if 1//(ENABLE_TCON_BIN)
    bResult = MDrv_TCON_BIN_SwitchTable( bIs3D, u8TblIdx);
#else
    MDrv_TCON_ChangeSetting_End();
#endif

#endif

    return bResult;
}

BOOL MDrv_TCON_Init(void)
{
    BOOL bResult = TRUE;

    DEBUG_TCON( printf("MDrv_TCON_Init()\n"); );

    //g_Tcon_Reset_u32Time = 0;
    //g_Tcon_Reset_u32VCnt = 0;

    //s_TCON_u8ChangeSettingState = TCON_CHANGE_SETTING_NONE;

#if 1//(ENABLE_TCON_BIN)
    if( FALSE == MDrv_TCON_BIN_Init() )
    {
        printf("\nError: MDrv_TCON_Init() failed\n");
        return FALSE;
    }
#endif

    g_Tcon_bInitDone = TRUE;

    return bResult;
}

BOOL msAPI_TCON_Init(void)
{
    BOOL bResult = TRUE;
    DEBUG_TCON( PRINT_CURRENT_LINE(); );
    DEBUG_TCON( printf("msAPI_TCON_Init()\n"); );

    bResult = MDrv_TCON_Init();

    if( bResult == FALSE )
    {
        MsOS_DelayTask(5000);
        return FALSE;
    }

#if( ENABLE_TCON_VER_20 )
    // Read panel info...
    MDrv_TCON_BIN_ReadPanelInfo();


#else
    MDrv_TCON_SwitchTable(0, 0); // Load 2D setting
#endif

    //while(1){}

    return bResult;
}

BOOL msAPI_TCON_LoadTable(EnuTConTbl2D3D eTConTbl2D3D)
{
    DEBUG_TCON( PRINT_CURRENT_LINE(); );
    DEBUG_TCON( printf("msAPI_TCON_LoadTable()\n"); );

    if( g_Tcon_bInitDone == FALSE )
    {
        printf("\nError: TCON is not inited!\n");
        return FALSE;
    }

    BOOL bResult = MDrv_TCON_SwitchTable( (eTConTbl2D3D==TCON_TBL_3D)?TRUE:FALSE, 0);

    //while(1){}

    return bResult;
}

#endif

