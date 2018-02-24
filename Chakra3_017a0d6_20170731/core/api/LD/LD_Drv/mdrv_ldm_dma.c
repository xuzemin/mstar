#define _MDRV_LDM_DMA_C_

#include "Board.h"

#if( LD_ENABLE)

#include "drvGlobal.h"

#include "leddevice.h"

#include "mhal_ld.h"

#include "mdrv_mfc_spi.h"
#include "mdrv_ld.h"
#include "mdrv_ldm_dma.h"

#include "msAPI_Timer.h"



#define DEBUG_LDM_DMA(x)    //x

extern t_sDrvLdCusPtrMap sCusPtrMap;

void MDrv_LDM_DMA_SetMenuloadNumber( U16 u16Number )
{
    DEBUG_LDM_DMA( printf("MDrv_LDM_DMA_SetMenuloadNumber(u16Number=%u)\n", u16Number););

    MDrv_Write2ByteMask(LDM_DMA_REG(0x02), u16Number, 0x3FF);
    #if ENABLE_TWO_SPI
    MDrv_Write2ByteMask(LDM_DMA_REG2(0x02), u16Number, 0x3FF);
    #elif ENABLE_FOUR_SPI
    MDrv_Write2ByteMask(LDM_DMA_REG(0x02), u16Number/4, 0x3FF);
    MDrv_Write2ByteMask(LDM_DMA_REG2(0x02), u16Number/4, 0x3FF);
    MDrv_Write2ByteMask(LDM_DMA_REG3(0x02), u16Number/4, 0x3FF);
    MDrv_Write2ByteMask(LDM_DMA_REG4(0x02), u16Number/4, 0x3FF);
    #endif

    MHal_LD_Set_DmaAccessYEnd( ((u16Number/8)+1) );
}

void MDrv_LDM_DMA_SetSPICommandFormat( U8 u8CmdLen, U16* pu16CmdBuf, BOOL bEnCheckSum )
{
    U8 i;
    U16 u16Reg_Cmd_Len_Val = 0;
    U8 u8Reg_chksum_md_Val = 0;

    DEBUG_LDM_DMA( printf("MDrv_LDM_DMA_SetSPICommandFormat(u8CmdLen=%u, bEnCheckSum=%u)\n", u8CmdLen, bEnCheckSum););

    if( u8CmdLen > LDM_MAX_SPI_CMD_NUM )
    {
        printf("[LDM-DMA]Spi command len is too long=%u!\n", u8CmdLen);
        u8CmdLen = LDM_MAX_SPI_CMD_NUM;
    }


    if( u8CmdLen == 0 )
        u8Reg_chksum_md_Val = 2; // data only
    else if( u8CmdLen == 1 )
        u8Reg_chksum_md_Val = 1; // command + data
    else //if( u8CmdLen >= 2 )
        u8Reg_chksum_md_Val = 0; // start + command + data

    //u8Reg_chksum_md_Val = 1; // command + data
    MDrv_WriteByteMask(LDM_DMA_REG(0x1A), u8Reg_chksum_md_Val, 0x7);//checksum mode

    #if ENABLE_TWO_SPI
        MDrv_WriteByteMask(LDM_DMA_REG2(0x1A), u8Reg_chksum_md_Val, 0x7);//checksum mode
    #elif ENABLE_FOUR_SPI
        MDrv_WriteByteMask(LDM_DMA_REG2(0x1A), u8Reg_chksum_md_Val, 0x7);//checksum mode
        MDrv_WriteByteMask(LDM_DMA_REG3(0x1A), u8Reg_chksum_md_Val, 0x7);//checksum mode
        MDrv_WriteByteMask(LDM_DMA_REG4(0x1A), u8Reg_chksum_md_Val, 0x7);//checksum mode
    #endif

    for( i = 0; i < u8CmdLen; ++ i )
    {
        u16Reg_Cmd_Len_Val |= (1<<i);

         if( i == 0 )
        {
            MDrv_Write2Byte(LDM_DMA_REG(0x16), pu16CmdBuf[0]);
            #if ENABLE_TWO_SPI
                MDrv_Write2Byte(LDM_DMA_REG2(0x16), pu16CmdBuf[0]);
            #elif ENABLE_FOUR_SPI
                MDrv_Write2Byte(LDM_DMA_REG2(0x16), pu16CmdBuf[0]);
                MDrv_Write2Byte(LDM_DMA_REG3(0x16), pu16CmdBuf[0]);
                MDrv_Write2Byte(LDM_DMA_REG4(0x16), pu16CmdBuf[0]);
            #endif
        }
        else if( i == 1 )
        {
            MDrv_Write2Byte(LDM_DMA_REG(0x18), pu16CmdBuf[1]);
            #if ENABLE_TWO_SPI
                MDrv_Write2Byte(LDM_DMA_REG2(0x18), pu16CmdBuf[1]);
            #elif ENABLE_FOUR_SPI
                MDrv_Write2Byte(LDM_DMA_REG2(0x18), pu16CmdBuf[1]);
                MDrv_Write2Byte(LDM_DMA_REG3(0x18), pu16CmdBuf[1]);
                MDrv_Write2Byte(LDM_DMA_REG4(0x18), pu16CmdBuf[1]);
            #endif
        }
        else
        {
            MDrv_Write2Byte(LDM_DMA_REG(0x42)+(i-2)*2, pu16CmdBuf[i]);
            #if ENABLE_TWO_SPI
                MDrv_Write2Byte(LDM_DMA_REG2(0x42)+(i-2)*2, pu16CmdBuf[i]);
            #elif ENABLE_FOUR_SPI
                MDrv_Write2Byte(LDM_DMA_REG2(0x42)+(i-2)*2, pu16CmdBuf[i]);
                MDrv_Write2Byte(LDM_DMA_REG3(0x42)+(i-2)*2, pu16CmdBuf[i]);
                MDrv_Write2Byte(LDM_DMA_REG4(0x42)+(i-2)*2, pu16CmdBuf[i]);
            #endif

        }
    }

    if( bEnCheckSum )
    {
        u16Reg_Cmd_Len_Val |= BIT15;
    }

    MDrv_Write2Byte(LDM_DMA_REG(0x40), u16Reg_Cmd_Len_Val);
    #if ENABLE_TWO_SPI
        MDrv_Write2Byte(LDM_DMA_REG2(0x40), u16Reg_Cmd_Len_Val);
    #elif ENABLE_FOUR_SPI
        MDrv_Write2Byte(LDM_DMA_REG2(0x40), u16Reg_Cmd_Len_Val);
        MDrv_Write2Byte(LDM_DMA_REG3(0x40), u16Reg_Cmd_Len_Val);
        MDrv_Write2Byte(LDM_DMA_REG4(0x40), u16Reg_Cmd_Len_Val);
    #endif

}


/*
typedef enum
{
    E_LDM_SPI_TRIGER_STOP,
    E_LDM_SPI_TRIGER_ONE_SHOT,
    E_LDM_SPI_TRIGER_EVERY_V_SYNC,
}EnuSpiTriggerMode;
*/
void MDrv_LDM_DMA_SetSpiTriggerMode( EnuLdmSpiTriggerMode eSpiTriggerMode )
{
    DEBUG_LDM_DMA( printf("MDrv_LDM_DMA_SetSpiTriggerMode(eSpiTriggerMode=%u)\n", eSpiTriggerMode););

    switch(eSpiTriggerMode)
    {
        case E_LDM_SPI_TRIGER_STOP:
            // Menuload trigger src = one shot

            MDrv_WriteByteMask(LDM_DMA_REG(0x00), 0, 0x83);
            // menuload abort one shot
            MDrv_WriteRegBit(LDM_DMA_REG(0x0A), 1, 1);
            // menuload disable one shot
            MDrv_WriteRegBit(LDM_DMA_REG(0x0C), 0, 1);

            #if ENABLE_TWO_SPI
            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG2(0x00), 0, 0x03);
            // menuload abort one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x0A), 1, 1);
            // menuload disable one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x0C), 0, 1);
            #elif ENABLE_FOUR_SPI
            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG2(0x00), 0, 0x03);
            // menuload abort one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x0A), 1, 1);
            // menuload disable one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x0C), 0, 1);

            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG3(0x00), 0, 0x03);
            // menuload abort one shot
            MDrv_WriteRegBit(LDM_DMA_REG3(0x0A), 1, 1);
            // menuload disable one shot
            MDrv_WriteRegBit(LDM_DMA_REG3(0x0C), 0, 1);

            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG4(0x00), 0, 0x03);
            // menuload abort one shot
            MDrv_WriteRegBit(LDM_DMA_REG4(0x0A), 1, 1);
            // menuload disable one shot
            MDrv_WriteRegBit(LDM_DMA_REG4(0x0C), 0, 1);
            #endif
            break;


        case E_LDM_SPI_TRIGER_ONE_SHOT:
            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG(0x00), 0, 0x83);
            // menuload enable one shot
            MDrv_WriteRegBit(LDM_DMA_REG(0x0C), 1, 1);
            // menuload realtime trigger one shot
            MDrv_WriteRegBit(LDM_DMA_REG(0x08), 1, 1);

            #if ENABLE_TWO_SPI
            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG2(0x00), 0, 0x03);
            // menuload enable one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x0C), 1, 1);
            // menuload realtime trigger one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x08), 1, 1);
            #elif ENABLE_FOUR_SPI
            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG2(0x00), 0, 0x03);
            // menuload enable one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x0C), 1, 1);
            // menuload realtime trigger one shot
            MDrv_WriteRegBit(LDM_DMA_REG2(0x08), 1, 1);

            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG3(0x00), 0, 0x03);
            // menuload enable one shot
            MDrv_WriteRegBit(LDM_DMA_REG3(0x0C), 1, 1);
            // menuload realtime trigger one shot
            MDrv_WriteRegBit(LDM_DMA_REG3(0x08), 1, 1);

            // Menuload trigger src = one shot
            MDrv_WriteByteMask(LDM_DMA_REG4(0x00), 0, 0x03);
            // menuload enable one shot
            MDrv_WriteRegBit(LDM_DMA_REG4(0x0C), 1, 1);
            // menuload realtime trigger one shot
            MDrv_WriteRegBit(LDM_DMA_REG4(0x08), 1, 1);
            #endif

            break;

        case E_LDM_SPI_TRIGER_EVERY_V_SYNC:
            // Menuload trigger src = V sync
            MDrv_WriteByteMask(LDM_DMA_REG(0x00), 0x81, 0x83); //bit7 , hw mode enable

            #if ENABLE_TWO_SPI
            // Menuload trigger src = V sync
            MDrv_WriteByteMask(LDM_DMA_REG2(0x00), 0x81, 0x83); //bit7 , hw mode enable
            #elif ENABLE_FOUR_SPI
            MDrv_WriteByteMask(LDM_DMA_REG2(0x00), 0x81, 0x83); //bit7 , hw mode enable
            MDrv_WriteByteMask(LDM_DMA_REG3(0x00), 0x81, 0x83); //bit7 , hw mode enable
            MDrv_WriteByteMask(LDM_DMA_REG4(0x00), 0x81, 0x83); //bit7 , hw mode enable
            #endif


            break;
    }
}

void MDrv_LDM_DMA_Init(void)
{
    DEBUG_LDM_DMA( printf("MDrv_LDM_DMA_Init()\n"););

    //MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_EVERY_V_SYNC);

    t_sDrvLdCusPtrMap* pstCurPtrMap = LedDev_Get_CurPtrMap();
    if( pstCurPtrMap == NULL )
        return;

    // Setup LDM-DMA ...
    //MDrv_LDM_DMA_SetSPICommandFormat( psDrvLdInfo->u8SpiCmdLen, psDrvLdInfo->au16SpiCmd, psDrvLdInfo->u8CheckSumMode );
    MDrv_LDM_DMA_SetSPICommandFormat(
            pstCurPtrMap->p_sDrvLdInfo->u8SpiCmdLen,
            pstCurPtrMap->p_sDrvLdInfo->au16SpiCmd,
            pstCurPtrMap->p_sDrvLdInfo->u8CheckSumMode );


    //MDrv_LDM_DMA_SetMenuloadNumber( psDrvLdInfo->u8DMAWidth*psDrvLdInfo->u8DMAHeight);
    MDrv_LDM_DMA_SetMenuloadNumber( 8);


#if 1 // Fill DMA memory
    {
        U32 u32DmaMemBase = MHal_LD_Get_SPI_BufBaseAddr();

        printf("Mem Base = 0x%X\n", u32DmaMemBase);

        U8 i;
        U8* pu8DmaMem = (U8*)MsOS_PA2KSEG1(u32DmaMemBase);

        for( i = 0; i < 250; i ++ )
        {
            pu8DmaMem[i] = 0;
        }

        MsOS_FlushMemory();
    }
#endif
}

#define DEBUG_DMA_W(x)  //x

#define DMA_MEM_ROW_OFFSET  32

static U32 s_u32DmaMemBase = 0;

void MDrv_LDM_DMA_Set_DMA0_Data(U16 u16Index, U16 u16Data)
{
    DEBUG_DMA_W( printf("MDrv_LDM_DMA_Set_DMA0_Data(%u,%u(0x%X))\n", u16Index, u16Data, u16Data); );

    if( s_u32DmaMemBase == 0 )
    {
        s_u32DmaMemBase = MHal_LD_Get_SPI_BufBaseAddr();
        if( s_u32DmaMemBase == 0 )
        {
            printf("MHal_LD_Get_SPI_BufBaseAddr() failed!\n");
            return;
        }
    }
    DEBUG_DMA_W( printf(" s_u32DmaMemBase=0x%X\n", s_u32DmaMemBase); );

    U16 u16Offset = (u16Index/8)*DMA_MEM_ROW_OFFSET + (u16Index%8)*2;
    DEBUG_DMA_W( printf(" u16Offset=0x%X\n", u16Offset); );

    U16* pu16DmaData = (U16*)MsOS_PA2KSEG1(s_u32DmaMemBase + u16Offset);

    *pu16DmaData = u16Data;
}

void MDrv_LDM_DMA_Set_DMA0_Datas(U16 u16BufLen, U16* pu16Buf, BOOLEAN bTrigger, BOOLEAN bWaitDone)
{
    DEBUG_DMA_W( printf("MDrv_LDM_DMA_Set_DMA0_Datas(%u))\n", u16BufLen); );

    if( s_u32DmaMemBase == 0 )
    {
        s_u32DmaMemBase = MHal_LD_Get_SPI_BufBaseAddr();
        if( s_u32DmaMemBase == 0 )
        {
            printf("MHal_LD_Get_SPI_BufBaseAddr() failed!\n");
            return;
        }
    }
    DEBUG_DMA_W( printf(" s_u32DmaMemBase=0x%X\n", s_u32DmaMemBase); );

    U16 u16Index;
    U16 u16Offset;
    U16* pu16DmaData;

    for( u16Index = 0; u16Index < u16BufLen; ++ u16Index )
    {
        u16Offset = (u16Index/8)*DMA_MEM_ROW_OFFSET + (u16Index%8)*2;
        DEBUG_DMA_W( printf(" u16Offset=0x%X\n", u16Offset); );

        pu16DmaData = (U16*)MsOS_PA2KSEG1(s_u32DmaMemBase + u16Offset);

        *pu16DmaData = pu16Buf[u16Index];
    }

    MsOS_FlushMemory();

    if( bTrigger )
    {
        // Set menuload number
        MDrv_LDM_DMA_SetMenuloadNumber(u16BufLen);

        // Trigger
        MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_EVERY_V_SYNC);

        // Wait done
        if(bWaitDone)
        {
            //msAPI_Timer_Delayms(40);
            //printf("Wait Busy\n");
            while(1)
            {
                if( MDrv_ReadByte(LDM_DMA_REG(0x01)) & BIT0 )
                {
                    break;
                }
            }

            //printf("Wait done\n");
            while(1)
            {
                if( MDrv_ReadByte(LDM_DMA_REG(0x01)) & BIT1 )
                {
                    break;
                }
            }

            MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_STOP);
        }
    }
}

// void MDrv_LD_SetSpiClkDelayFromVsync(U16 u16Val);
void MDrv_LDM_DMA_Set_TrigDelay(U32 u32Delay)
{
//h002a reg_trig_delay0_cnt0
//h002b reg_trig_delay0_cnt1
//h002c reg_trig_delay1_cnt0
//h002d reg_trig_delay1_cnt1

    //MDrv_Write2Byte(LDM_DMA_REG(0x58), u16Val);
    MDrv_Write4Byte(LDM_DMA_REG(0x58), u32Delay);
}


#if  0
static BOOL s_bMDrv_LDM_DMA_InitFinished = FALSE;

BOOL MDrv_LDM_DMA_Init(void)
{
    if( s_bMDrv_LDM_DMA_InitFinished )
        return TRUE;

/*
    if( MDrv_SPI_Init(TRUE) == FALSE )
    {
        ADD_SYS_ERR_MSG(SYS_ERR_INIT_MSPI_FAILED, "Init drvMSPI failed!\n");
        return FALSE;
    }
*/
#if ( DRV_LD_USE_SWSPI )
    MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_STOP);
#else
    MDrv_LDM_DMA_SetSpiTriggerMode(E_LDM_SPI_TRIGER_EVERY_V_SYNC);
#endif

#if ( DRV_LD_USE_SWSPI )
{
    U16 i;
    U16 u16TotalSPIDataLen = 0;

    // Setup SPI cmd data...
    for( i = 0; i < s_DrvLdInfo.u8SpiCmdLen; ++ i )
    {
        s_au8DrvLD_SPIBuf[i] = s_DrvLdInfo.au16SpiCmd[i];
    }

    // Setup MSPI timing ...
    u16TotalSPIDataLen = s_DrvLdInfo.u8SpiCmdLen + LD_LED_NUMBER;
    if( s_DrvLdInfo.u8CheckSumMode )
        u16TotalSPIDataLen += 1;

    // Setup the delay time before every data
    //s_au8DrvLD_SPI_delay[0] = (s_DrvLdInfo.u8SpiTime_VSyncWidth + s_DrvLdInfo.u8SpiTime_VSync_To_FirstClock);
    s_au8DrvLD_SPI_delay[0] = s_DrvLdInfo.u8SpiTime_VSync_To_FirstClock;

    for( i = 1; i < u16TotalSPIDataLen; ++ i )
    {
        s_au8DrvLD_SPI_delay[i] = s_DrvLdInfo.u8SpiTime_Byte_to_Byte;
    }
    MDrv_SPI_SetWriteBuf_Delay( s_au8DrvLD_SPI_delay, u16TotalSPIDataLen );
}
#else
    // Setup MSPI timing
//    MHal_MSPI_SetTime_TriggerToFirstClock(s_DrvLdInfo.u8SpiTime_FromTriggerToFirstClock);
//    MHal_MSPI_SetTime_LastClockToDone(s_DrvLdInfo.u8SpiTime_LastClockToDone);

    // Setup LDM-DMA ...
    MDrv_LDM_DMA_SetSPICommandFormat( s_DrvLdInfo.u8SpiCmdLen, s_DrvLdInfo.au16SpiCmd, s_DrvLdInfo.u8CheckSumMode );
    MDrv_LDM_DMA_SetMenuloadNumber( s_DrvLdInfo.u8DMAWidth*s_DrvLdInfo.u8DMAHeight);
#endif

    s_bMDrv_LDM_DMA_InitFinished = TRUE;

printf("\n -- ox %s()\n",__FUNCTION__);

    return s_bMDrv_LDM_DMA_InitFinished;
}
#endif


#endif

