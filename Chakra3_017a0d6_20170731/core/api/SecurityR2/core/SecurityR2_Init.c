
//#include "drvGlobal.h"
#include "Board.h"
//#include "SW_Config.h"
//#include "default_option_define.h"

#if( ENABLE_SECURITY_R2 )

#include "SysInit.h"

#include "SecurityR2_Init.h"
#include "SecurityR2_App.h"

#include "mbx_reg_tbl.h"
#include "secure_reg_tbl.h"

#include "debug.h"
#include "MApp_GlobalFunction.h"

#include "msAPI_SecurityR2.h"
#include "drvHDCPMbx.h"
#include "drvHDCPRx.h"
#include "msReg.h"

#include "msAPI_MIU.h"



#define DEBUG_SEC_R2_INIT(x)    //x

//====================================================
//====================================================
//================== general function =======================
//====================================================
//====================================================

static U16 Map_DramSize_Tbl(U16 u16DramSize)
{
    U16 u16MapValue = 0xFFFF;

    switch (u16DramSize)
    {
        case 2:
            u16MapValue = DRAM_SIZE_002MB;
            break;
        case 4:
            u16MapValue = DRAM_SIZE_004MB;
            break;
        case 8:
            u16MapValue = DRAM_SIZE_008MB;
            break;
        case 16:
            u16MapValue = DRAM_SIZE_016MB;
            break;
        case 32:
            u16MapValue = DRAM_SIZE_032MB;
            break;
        case 64:
            u16MapValue = DRAM_SIZE_064MB;
            break;
        case 128:
            u16MapValue = DRAM_SIZE_128MB;
            break;
        case 256:
            u16MapValue = DRAM_SIZE_256MB;
            break;
        case 512:
            u16MapValue = DRAM_SIZE_512MB;
            break;
        case 1024:
            u16MapValue = DRAM_SIZE_001GB;
            break;
        default:
            break;
    }

    return u16MapValue;
}


// clean MBX before using
// clean MBX after using
static void Clean_MBX_All_Register(void)
{
    //clear mbx register
    U32 i;

    //
    for (i = (MBX_START_ADDR+MBX_OFFSET_MM_START); i<=(MBX_START_ADDR+MBX_OFFSET_MM_END) ; i+=1)
    {
        MDrv_WriteByte(i, 0x00);
    }
}

//====================================================
//====================================================
//====================================================
//====================================================
//====================================================




static void Set_RC_Lock(void)
{
    U16 u16Data;

    u16Data = MDrv_Read2Byte((SECURE_PUBLIC+REG_RC_CLOCK*2));
    u16Data = (u16Data | 0x000F) | (ENABLE_RC_LOCK) ;
    MDrv_Write2Byte((SECURE_PUBLIC+REG_RC_CLOCK*2), u16Data);
}

static E_SecR2_Satus Set_SECRANGE_DramSize(U16 u16DramSize)
{
    U8 u8RegData = 0;

    U16 u16DramSizeMap = 0;

    u16DramSizeMap = Map_DramSize_Tbl(u16DramSize);
    if (u16DramSizeMap == 0xFFFF)
    {
        return E_SECR2_DRAMSIZE_ERROR;
    }

    u8RegData = ENABLE_DRAM_SIZE| u16DramSizeMap;

    // enable secure range dram size
    MDrv_WriteByte((SECURE_PUBLIC+REG_DRAM_SIZE*2),u8RegData);

    return E_SECR2_SUCCESS;
}

static E_SecR2_Satus ConductMBX_Info_ROMSecR2(U32 u32SecureR2_Base_Addr, U32 u32SecureR2_Size, U32 u32SecureRange_Base_Addr, U32 u32SecureRange_Size)
{
/*
    bank:0x1033
    8bits,
0xA0:[S]
0xA1:[E]
0xA2:[R]
0xA3:[2]
0xA4~0xA7:[R2 Dram address]
0xA8~0xA11:[R2 Dram len]
0xA12~0xA13:[AckStaus]

0xB0:[S]
0xB1:[E]
0xB2:[D]
0xB3:[M]
0xB4~0xB7:[Secure Range start address]
0xB8~0xB11:[Secure Reange length]
0xB12~0xB13:[AckStaus]
*/

    U32 u32MBXBufAddr = 0;

    if ( (u32SecureR2_Base_Addr & 0xFFFFFFFF) > (u32SecureRange_Base_Addr &0xFFFFFFFF))
    {
        printf("Set Start Addr Error, %s[%d], SecureR2:0x%x vs SeucreRange:0x%x\n",
                __FUNCTION__, __LINE__,
                u32SecureR2_Base_Addr, u32SecureRange_Base_Addr);
        return E_SECR2_SecureR2_BaseAddr_ERROR;
    }

    if ( ((u32SecureR2_Base_Addr + u32SecureR2_Size) & 0xFFFFFFFF) > ((u32SecureRange_Base_Addr + u32SecureRange_Size)&0xFFFFFFFF) )
    {
        printf("Set End Addr Error, %s[%d], SecureR2:0x%x vs SeucreRange:0x%x\n",
                __FUNCTION__, __LINE__,
                (u32SecureR2_Base_Addr + u32SecureR2_Size),
                (u32SecureRange_Base_Addr + u32SecureRange_Size) );
        return E_SECR2_SecureR2_Size_ERROR;
    }


    Clean_MBX_All_Register(); //Clean all mailbox register

    MDrv_WriteByte(MBX_SECR2_ADDR+OFFSET_COMMAND_HEAD_0, 'S');
    MDrv_WriteByte(MBX_SECR2_ADDR+OFFSET_COMMAND_HEAD_1, 'E');
    MDrv_WriteByte(MBX_SECR2_ADDR+OFFSET_COMMAND_HEAD_2, 'R');
    MDrv_WriteByte(MBX_SECR2_ADDR+OFFSET_COMMAND_HEAD_3, '2');
    MDrv_Write4Byte(MBX_SECR2_ADDR+OFFSET_START_ADDR, u32SecureR2_Base_Addr);
    MDrv_Write4Byte(MBX_SECR2_ADDR+OFFSET_LENGTHE, u32SecureR2_Size);
    MDrv_Write2Byte(MBX_SECR2_ADDR+OFFSET_ACK_STATUS, 0x0000);

    MDrv_WriteByte(MBX_SECRANGE_ADDR+OFFSET_COMMAND_HEAD_0, 'S');
    MDrv_WriteByte(MBX_SECRANGE_ADDR+OFFSET_COMMAND_HEAD_1, 'E');
    MDrv_WriteByte(MBX_SECRANGE_ADDR+OFFSET_COMMAND_HEAD_2, 'D');
    MDrv_WriteByte(MBX_SECRANGE_ADDR+OFFSET_COMMAND_HEAD_3, 'M');
    MDrv_Write4Byte(MBX_SECRANGE_ADDR+OFFSET_START_ADDR,u32SecureRange_Base_Addr);
    MDrv_Write4Byte(MBX_SECRANGE_ADDR+OFFSET_LENGTHE, u32SecureRange_Size);
    MDrv_Write2Byte(MBX_SECRANGE_ADDR+OFFSET_ACK_STATUS, 0x0000);

    //fill address & size
    drv_HDCPRx_SetTxBufAddr((HDCP_MBX_BUFFER_MEMORY_TYPE & MIU1) ? (HDCP_MBX_BUFFER_ADR | MIU_INTERVAL) : (HDCP_MBX_BUFFER_ADR));
    u32MBXBufAddr = drv_HDCPRx_GetTxBufAddr();

#if(LD_ENABLE&&LD_ALGO_RUN_IN_CROP) // This is a bad method~
    {
        U32 u32LDShareMem = LD_SHARE_MEM_ADR;
        PRINT_CURRENT_LINE();
        printf("HDCP_MBX_BUFFER_ADR=0x%X\n", HDCP_MBX_BUFFER_ADR);
        printf("u32LDShareMem=0x%X\n", u32LDShareMem);
        msAPI_MIU_WriteMemBytes(HDCP_MBX_BUFFER_ADR+0xFFF0, (U8*)&u32LDShareMem, 4 );
        msAPI_MIU_ReadMemBytes(HDCP_MBX_BUFFER_ADR+0xFFF0, (U8*)&u32LDShareMem, 4 );
        printf(" => u32LDShareMem=0x%X\n", u32LDShareMem);
    }
#endif

#if 0
    MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x04, u32_ADR);
    MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x08, sg_u32BinLength);
    MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x0C, u32_ADR); //sec dram start
    MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x10, u32_LEN); //sec dram size
#endif

    MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x14, u32MBXBufAddr); //mbx start
    // Mbx size is 48??
    MDrv_Write4Byte(HDCPMBX_START_ADDR + 0x18, 48); //mbx size

    return E_SECR2_SUCCESS;
}


static void Bringup_SecR2_with_ROM(void)
{
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    MDrv_WriteByte(0x122a80, 0x00);
    MDrv_WriteByte(0x122a80, 0x0F);
#else
    MDrv_WriteByte(0x100E80, 0x00);
    MDrv_WriteByte(0x100E80, 0x0F);
#endif
}



/*
name :
msAPI_SecurityR2_Init

function:
Set Secure R2 init & Bringup Secure R2

In:
u16DramSize - DRAM Size
SecureR2_Base_Addr - Seucre R2 in DRAM Base Address
SecureR2_Size - Secure R2  in DRAM  length
SecureRange_Base_Addr - Secure Range Base Address
SecureRange_Size - Secure Range length

out:
E_SecR2_Satus - Secure R2 report Status
*/
E_SecR2_Satus SecurityR2_Init(U16 u16DramSize, U32 u32SecureR2_Base_Addr, U32 u32SecureR2_Size, U32 u32SecureRange_Base_Addr, U32 u32SecureRange_Size, U16 u16DebugMode)
{
    E_SecR2_Satus eRet = E_SECR2_SUCCESS;

    u16DebugMode = u16DebugMode;

    DEBUG_SEC_R2_INIT( printf("%s , info: [%d]\n", __FUNCTION__, u16DebugMode); );
    DEBUG_SEC_R2_INIT( printf("DRAM Size:%d\n", u16DramSize); );
    DEBUG_SEC_R2_INIT( printf("SecureR2 Start Addr in DRAM:0x%x\n", u32SecureR2_Base_Addr); );
    DEBUG_SEC_R2_INIT( printf("SecureR2 End Addr in DRAM:0x%x\n", (u32SecureR2_Base_Addr+u32SecureR2_Size)); );
    DEBUG_SEC_R2_INIT( printf("SecureRange Start Addr in DRAM:0x%x\n", u32SecureRange_Base_Addr); );
    DEBUG_SEC_R2_INIT( printf("SecureRange End Addr in DRAM:0x%x\n", (u32SecureRange_Base_Addr+u32SecureRange_Size)); );

    //Set RC Lock Set
    Set_RC_Lock();

    //Set Secure Raneg DRAM Size
    eRet = Set_SECRANGE_DramSize(u16DramSize);
    if (eRet != E_SECR2_SUCCESS)
    {
        printf("%s[%d] eRet=%d\n", __FUNCTION__, __LINE__, eRet);
        return eRet;
    }

    eRet = ConductMBX_Info_ROMSecR2(u32SecureR2_Base_Addr, u32SecureR2_Size, u32SecureRange_Base_Addr, u32SecureRange_Size);
    if (eRet != E_SECR2_SUCCESS)
    {
        printf("%s[%d] eRet=%d\n", __FUNCTION__, __LINE__, eRet);
        return eRet;

    }
#if( (CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA) )
    MDrv_Write4Byte(0x122ab2, SECURITY_R2_ADR);
    //MDrv_WriteByte(0x101eA6, 0xFD);     //uart source switch to secu r2
#endif
    Bringup_SecR2_with_ROM();   //but mazda security r2 not rom boot,no need to check rom state

    if (u16DebugMode >= 1) // self test  for wait Secure R2 in DRAM run ok
    {
#if( (CHIP_FAMILY_TYPE != CHIP_FAMILY_MAZDA) )      //mazda not rom boot,no need to check rom state
        #define QUERY_MAX_NUM (20)
        E_SecR2_ROM_Mode eTemp;
        U16 u16Retry = 0;

        while ((eTemp = SecureR2_Query_ROM_State()) != E_SECR2_ROM_RUN_DRAM_SUCCESS && u16Retry++<QUERY_MAX_NUM);

        DEBUG_SEC_R2_INIT( printf("State=%d\n", eTemp); );
        DEBUG_SEC_R2_INIT( printf("u16Retry=%d\n", u16Retry); );
        DEBUG_SEC_R2_INIT( printf("QUERY_MAX_NUM=%d\n", QUERY_MAX_NUM); );

        if (u16Retry <QUERY_MAX_NUM)
        {
            printf("==================== Secure R2 Success Run in DRAM ================\n");
        }
        else
        {
            MApp_Fatal_Error("== Secure R2 Auth. fail ==",__FUNCTION__);
        }
#endif
        //   while(1);
        Clean_MBX_All_Register();
    }

    return eRet;
}

//******************************************************************************

#endif // #if( ENABLE_SECURITY_R2 )
