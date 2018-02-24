#define _MDRV_MSPI_C_

#include "Board.h"

#if( LD_ENABLE)
#include "msReg.h"
#include "drvGlobal.h"

#include "sysinfo.h"

#include "MsOS.h"
#include "MsCommon.h"

#include "mhal_ld.h"

#include "mdrv_mfc_spi.h"

#include "drvIRQ.h"
#include "drvISR.h"
#include "drvGPIO.h"

#include "msAPI_LD_PWM.h"
#include "msAPI_Timer.h"


//========================================================================================================

static BOOL s_bMDrvSPI_InitFinished = FALSE;
static StuMSPICtrlInfo s_MSPICtrlInfo;

static BOOL s_bMspiOperationIsDone = 0;

// User buffer will copy to real buffer when every V sync
static U8 s_aucSpiWriteBuf_Real[SPI_WRITE_BUF_SIZE];
static U8 s_aucSpiWriteBuf_User[SPI_WRITE_BUF_SIZE];
static BOOL s_bSpiWriteBufUserChanged = FALSE;

static U8 s_aucSpiWriteBuf_BitLen[SPI_WRITE_BUF_SIZE];
static U8 s_aucSpiWriteBuf_Delay[SPI_WRITE_BUF_SIZE];

static U16 s_u16SpiWriteBufSize = 0;
static U16 s_u16SpiWriteBuf_Index = 0;

static EnuSpiTriggerMode s_eSpiTriggerMode = E_SPI_TRIGGER_NONE;

static EnuSpiState s_eSpiState = E_SPI_STATE__NONE;

//========================================================================================================

#define MSPI_WRITEBYTE(u32Reg, u8Val)                       MDrv_WriteByte(0x153A00+0x100*MSPI_PORT_NUM+u32Reg, u8Val)
#define MSPI_WRITEBYTEMASK(u32Reg, u8Val, mask)             MDrv_WriteByteMask(0x153A00+0x100*MSPI_PORT_NUM+u32Reg, u8Val,mask)
#define MSPI_WRITE2BYTESMASK(u32Reg, u16Val, mask)          MDrv_Write2ByteMask(0x153A00+0x100*MSPI_PORT_NUM+u32Reg, u16Val, mask)
#define MSPI_WRITEBIT(u32Reg, u8Val, mask)                  MDrv_WriteRegBit(0x153A00+0x100*MSPI_PORT_NUM+u32Reg, u8Val, mask)

#if ENABLE_TWO_SPI
//#define MSPI_PORT_NUM2 2
#define MSPI_WRITEBYTE2(u32Reg, u8Val)                      MDrv_WriteByte(0x153A00+0x100*MSPI_PORT_NUM2+u32Reg, u8Val)
#define MSPI_WRITEBYTEMASK2(u32Reg, u8Val, mask)            MDrv_WriteByteMask(0x153A00+0x100*MSPI_PORT_NUM2+u32Reg, u8Val,mask)
#define MSPI_WRITE2BYTESMASK2(u32Reg, u16Val, mask)         MDrv_Write2ByteMask(0x153A00+0x100*MSPI_PORT_NUM2+u32Reg, u16Val, mask)
#define MSPI_WRITEBIT2(u32Reg, u8Val, mask)                 MDrv_WriteRegBit(0x153A00+0x100*MSPI_PORT_NUM2+u32Reg, u8Val, mask)
#endif

//========================================================================================================

// Bank = clk_gen1
// Reg = 0x31_L[4:2]=clk_sel
// Reg = 0x31_L[0]=clk_gate
//  .clk0  (clk_27_buf),
//  .clk1  (clk_48_buf),
//  .clk2  (clk_62_buf),
//  .clk3  (clk_72_buf),
//  .clk4  (clk_86_buf),
//  .clk5  (clk_108_buf),
//  .clk6  (clk_123_buf),
//  .clk7  (clk_160_buf),

U32 MHal_MSPI_Clk_To_Period_Us_X1000(EnuMSPI_CLOCK_DIV eMSPIClk )
{
    U32 u32DivVal = 2;
    U32 u32MSPIClk;
    U32 u32MSPIClkPeriodX100 = 100;

    if( eMSPIClk > MSPI_CLK_SPD__DIV_256 )
        return 0;


    u32DivVal = u32DivVal << eMSPIClk;
    u32MSPIClk = MSPI_INTERNAL_CLOCK / u32DivVal;

    u32MSPIClkPeriodX100 = 1000000000 / u32MSPIClk;

    return u32MSPIClkPeriodX100;
}

void MHal_MSPI_SetClockDiv( EnuMSPI_CLOCK_DIV eClockDiv )
{
    MSPI_WRITEBYTEMASK(REG_MSPI__CLOCK_RATE, eClockDiv, 0x07);
#if ENABLE_TWO_SPI
    MSPI_WRITEBYTEMASK2(REG_MSPI__CLOCK_RATE, eClockDiv, 0x07);
#elif ENABLE_FOUR_SPI
    MSPI_WRITEBYTEMASK2(REG_MSPI__CLOCK_RATE, eClockDiv, 0x07);
    MSPI_WRITEBYTEMASK3(REG_MSPI__CLOCK_RATE, eClockDiv, 0x07);
    MSPI_WRITEBYTEMASK4(REG_MSPI__CLOCK_RATE, eClockDiv, 0x07);
#endif
}

void MHal_MSPI_SetClockGen( EnuMSPI_CLOCK_GEN eClockGen )
{
    //printf("MHal_MSPI_SetClockGen(eClockGen=%u)\n", eClockGen);

    if( MSPI_CLK_SPD_CRYSTAL == eClockGen )
    {
        MDrv_WriteByteMask(0x100B2E, 0, BIT5);// bit2~5
        MDrv_WriteByteMask(0x100B2E, 0, BIT0) ; // clock enable

        MDrv_WriteByteMask(0x100B30, 0, BIT5);// bit2~5
        MDrv_WriteByteMask(0x100B30, 0, BIT0) ; // clock enable
    }
    else
    {
        MDrv_WriteByteMask(0x100B2E, (eClockGen<<2)|BIT5, 0x3C);// bit2~5
        MDrv_WriteByteMask(0x100B2E, 0, BIT0) ; // clock enable

        MDrv_WriteByteMask(0x100B30, (eClockGen<<2)|BIT5, 0x3C);// bit2~5
        MDrv_WriteByteMask(0x100B30, 0, BIT0) ; // clock enable
    }
}

void MHal_MSPI_SetClockPolarity( U8 u8ClockPolarity )
{
    s_MSPICtrlInfo.u8ClockPolarity = u8ClockPolarity;
    MSPI_WRITEBIT(REG_MSPI__CTRL, u8ClockPolarity, MASK_MSPI_CTRL__CLOCK_POLARITY);
#if ENABLE_TWO_SPI
    MSPI_WRITEBIT2(REG_MSPI__CTRL, u8ClockPolarity, MASK_MSPI_CTRL__CLOCK_POLARITY);
#elif ENABLE_FOUR_SPI
    MSPI_WRITEBIT2(REG_MSPI__CTRL, u8ClockPolarity, MASK_MSPI_CTRL__CLOCK_POLARITY);
    MSPI_WRITEBIT3(REG_MSPI__CTRL, u8ClockPolarity, MASK_MSPI_CTRL__CLOCK_POLARITY);
    MSPI_WRITEBIT4(REG_MSPI__CTRL, u8ClockPolarity, MASK_MSPI_CTRL__CLOCK_POLARITY);
#endif
}
void MHal_MSPI_SetClockPhase( U8 u8ClockPhase )
{
    s_MSPICtrlInfo.u8ClockPhase = u8ClockPhase;
    MSPI_WRITEBIT(REG_MSPI__CTRL, u8ClockPhase, MASK_MSPI_CTRL__CLOCK_PHASE);
#if ENABLE_TWO_SPI
    MSPI_WRITEBIT2(REG_MSPI__CTRL, u8ClockPhase, MASK_MSPI_CTRL__CLOCK_PHASE);
#elif ENABLE_FOUR_SPI
    MSPI_WRITEBIT2(REG_MSPI__CTRL, u8ClockPhase, MASK_MSPI_CTRL__CLOCK_PHASE);
    MSPI_WRITEBIT3(REG_MSPI__CTRL, u8ClockPhase, MASK_MSPI_CTRL__CLOCK_PHASE);
    MSPI_WRITEBIT4(REG_MSPI__CTRL, u8ClockPhase, MASK_MSPI_CTRL__CLOCK_PHASE);
#endif
}

void MHal_MSPI_SetTime_TriggerToFirstClock(U8 u8Time )
{
    s_MSPICtrlInfo.u8Time_FromTriggerToFirstClock = u8Time;
    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE(REG_MSPI__TIME_TR_START, u8Time);
}
void MHal_MSPI_SetTime_LastClockToDone(U8 u8Time )
{
    s_MSPICtrlInfo.u8Time_LastClockToDone = u8Time;
    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE(REG_MSPI__TIME_TR_END, u8Time);
}

static void _MHal_MSPI_SetWriteBufBitLen(U8 u8BitLen)
{
#if 1  // U11 LD fix output 16bit to SPI, SPI choose output data mode
    U8 u8WriteByteNum, i;
    U8 u8Remain = u8BitLen%8;
    U32 u32data=0;

    if(u8BitLen<8)
        u8BitLen=8;
    if(u8BitLen>16)
        u8BitLen=16;

    if(u8Remain ==0)
        u8WriteByteNum = u8BitLen>>3;
    else
        u8WriteByteNum = (u8BitLen>>3)+1;

    // set write buf size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, u8WriteByteNum);
#if ENABLE_TWO_SPI
    MSPI_WRITEBYTE2(REG_MSPI__WRITE_BUF_SIZE, u8WriteByteNum);
#elif ENABLE_FOUR_SPI
    MSPI_WRITEBYTE2(REG_MSPI__WRITE_BUF_SIZE, u8WriteByteNum);
    MSPI_WRITEBYTE3(REG_MSPI__WRITE_BUF_SIZE, u8WriteByteNum);
    MSPI_WRITEBYTE4(REG_MSPI__WRITE_BUF_SIZE, u8WriteByteNum);
#endif

    for(i=0;i<u8WriteByteNum;i++)
    {
        if(u8BitLen > (8*i+7))
        {
            u32data |= (7<<(3*i));
        }
        else
        {
            u32data |= ((u8Remain-1)<<(3*i));
        }
    }

    MSPI_WRITE2BYTESMASK(REG_MSPI__WRITE_BUF_BIT_LEN, u32data, 0xFFF);
    MSPI_WRITE2BYTESMASK(REG_MSPI__WRITE_BUF_BIT_LEN+2, u32data>>12, 0xFFF);
#if ENABLE_TWO_SPI
    MSPI_WRITE2BYTESMASK2(REG_MSPI__WRITE_BUF_BIT_LEN, u32data, 0xFFF);
    MSPI_WRITE2BYTESMASK2(REG_MSPI__WRITE_BUF_BIT_LEN+2, u32data>>12, 0xFFF);
#elif ENABLE_FOUR_SPI
    MSPI_WRITE2BYTESMASK2(REG_MSPI__WRITE_BUF_BIT_LEN, u32data, 0xFFF);
    MSPI_WRITE2BYTESMASK2(REG_MSPI__WRITE_BUF_BIT_LEN+2, u32data>>12, 0xFFF);
    MSPI_WRITE2BYTESMASK3(REG_MSPI__WRITE_BUF_BIT_LEN, u32data, 0xFFF);
    MSPI_WRITE2BYTESMASK3(REG_MSPI__WRITE_BUF_BIT_LEN+2, u32data>>12, 0xFFF);
    MSPI_WRITE2BYTESMASK4(REG_MSPI__WRITE_BUF_BIT_LEN, u32data, 0xFFF);
    MSPI_WRITE2BYTESMASK4(REG_MSPI__WRITE_BUF_BIT_LEN+2, u32data>>12, 0xFFF);
#endif
#else
    U16 u16Data;

    if( u8BitLen == 0 || u8BitLen >= 16 )
        return;

    u8BitLen -= 1;
    if (u8BitLen < 8)
    {

        u16Data = u8BitLen;
        u16Data |= (((U16)u8BitLen)<<3);
        u16Data |= (((U16)u8BitLen)<<6);
        u16Data |= (((U16)u8BitLen)<<9);

    MSPI_WRITE2BYTESMASK(REG_MSPI__WRITE_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK(REG_MSPI__WRITE_BUF_BIT_LEN+2, u16Data, 0xFFF);
    #if ENABLE_TWO_SPI
    MSPI_WRITE2BYTESMASK2(REG_MSPI__WRITE_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK2(REG_MSPI__WRITE_BUF_BIT_LEN+2, u16Data, 0xFFF);
    #endif
	}
    else
    {
        /*SPI3 => BK1C
        Buffer0 Bit Length
        Bk1C98[2:0]:7(3'b111: 8Bits)   Bk1C98[2:0]:6(3'b110: 7Bits)
        Bk1C98[2:0]:5(3'b111: 6Bits)   Bk1C98[2:0]:4(3'b110: 5Bits)
        Bk1C98[2:0]:3(3'b111: 4Bits)   Bk1C98[2:0]:2(3'b110: 3Bits)
        Bk1C98[2:0]:1(3'b111: 2Bits)   Bk1C98[2:0]:0(3'b110: 1Bits)

        Buffer1 Bit Length
        Bk1C98[5:3]:7(3'b111: 8Bits)   Bk1C98[5:3]:6(3'b111: 7Bits)
        Bk1C98[5:3]:5(3'b111: 6Bits)   Bk1C98[5:3]:4(3'b111: 5Bits)
        Bk1C98[5:3]:3(3'b111: 4Bits)   Bk1C98[5:3]:2(3'b111: 3Bits)
        Bk1C98[5:3]:1(3'b111: 2Bits)   Bk1C98[5:3]:0(3'b111: 1Bits)
        */
        u16Data = 7;
        u16Data |= ((((U16)u8BitLen&7))<<3);
        u16Data |= (((U16)7)<<6);
        u16Data |= (((U16)7)<<9);
        MSPI_WRITE2BYTESMASK(REG_MSPI__WRITE_BUF_BIT_LEN, u16Data, 0xFFF);
    }
#endif
}

static void _MHal_MSPI_SetReadBufBitLen(U8 u8BitLen)
{
    U16 u16Data;


    if( u8BitLen == 0 || u8BitLen > 8 )
        return;

    u8BitLen -= 1;

    u16Data = u8BitLen;
    u16Data |= (((U16)u8BitLen)<<3);
    u16Data |= (((U16)u8BitLen)<<6);
    u16Data |= (((U16)u8BitLen)<<9);

    MSPI_WRITE2BYTESMASK(REG_MSPI__READ_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK(REG_MSPI__READ_BUF_BIT_LEN+2, u16Data, 0xFFF);
#if ENABLE_TWO_SPI
    MSPI_WRITE2BYTESMASK2(REG_MSPI__READ_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK2(REG_MSPI__READ_BUF_BIT_LEN+2, u16Data, 0xFFF);
#elif ENABLE_FOUR_SPI
    MSPI_WRITE2BYTESMASK2(REG_MSPI__READ_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK2(REG_MSPI__READ_BUF_BIT_LEN+2, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK3(REG_MSPI__READ_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK3(REG_MSPI__READ_BUF_BIT_LEN+2, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK4(REG_MSPI__READ_BUF_BIT_LEN, u16Data, 0xFFF);
    MSPI_WRITE2BYTESMASK4(REG_MSPI__READ_BUF_BIT_LEN+2, u16Data, 0xFFF);
#endif
}

static void _MHal_MSPI_SetupTimingAndDelay(StuMSPICtrlInfo* pMSPICtrlInfo)
{
    MHal_MSPI_SetClockGen( pMSPICtrlInfo->eMSPIClockGen ) ;
    MHal_MSPI_SetClockDiv( pMSPICtrlInfo->eMSPIClockDiv  ) ;

    MHal_MSPI_SetClockPolarity( pMSPICtrlInfo->u8ClockPolarity );
    MHal_MSPI_SetClockPhase( pMSPICtrlInfo->u8ClockPhase );

    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE(REG_MSPI__TIME_TR_START, pMSPICtrlInfo->u8Time_FromTriggerToFirstClock);
    // The time from last SPI clock to "reg_mspi_done_flag"
    MSPI_WRITEBYTE(REG_MSPI__TIME_TR_END, pMSPICtrlInfo->u8Time_LastClockToDone);
    // The time between byte to byte transfer
    MSPI_WRITEBYTE(REG_MSPI__TIME_B_TO_B, pMSPICtrlInfo->u8Time_BetweenByteToByte);
    // The time between last write and first read,
    MSPI_WRITEBYTE(REG_MSPI__TIME_W_TO_R, pMSPICtrlInfo->u8Time_FromWriteToRead);
#if ENABLE_TWO_SPI
    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE2(REG_MSPI__TIME_TR_START, pMSPICtrlInfo->u8Time_FromTriggerToFirstClock);
    // The time from last SPI clock to "reg_mspi_done_flag"
    MSPI_WRITEBYTE2(REG_MSPI__TIME_TR_END, pMSPICtrlInfo->u8Time_LastClockToDone);
    // The time between byte to byte transfer
    MSPI_WRITEBYTE2(REG_MSPI__TIME_B_TO_B, pMSPICtrlInfo->u8Time_BetweenByteToByte);
    // The time between last write and first read,
    MSPI_WRITEBYTE2(REG_MSPI__TIME_W_TO_R, pMSPICtrlInfo->u8Time_FromWriteToRead);
#elif ENABLE_FOUR_SPI
    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE2(REG_MSPI__TIME_TR_START, pMSPICtrlInfo->u8Time_FromTriggerToFirstClock);
    // The time from last SPI clock to "reg_mspi_done_flag"
    MSPI_WRITEBYTE2(REG_MSPI__TIME_TR_END, pMSPICtrlInfo->u8Time_LastClockToDone);
    // The time between byte to byte transfer
    MSPI_WRITEBYTE2(REG_MSPI__TIME_B_TO_B, pMSPICtrlInfo->u8Time_BetweenByteToByte);
    // The time between last write and first read,
    MSPI_WRITEBYTE2(REG_MSPI__TIME_W_TO_R, pMSPICtrlInfo->u8Time_FromWriteToRead);

    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE3(REG_MSPI__TIME_TR_START, pMSPICtrlInfo->u8Time_FromTriggerToFirstClock);
    // The time from last SPI clock to "reg_mspi_done_flag"
    MSPI_WRITEBYTE3(REG_MSPI__TIME_TR_END, pMSPICtrlInfo->u8Time_LastClockToDone);
    // The time between byte to byte transfer
    MSPI_WRITEBYTE3(REG_MSPI__TIME_B_TO_B, pMSPICtrlInfo->u8Time_BetweenByteToByte);
    // The time between last write and first read,
    MSPI_WRITEBYTE3(REG_MSPI__TIME_W_TO_R, pMSPICtrlInfo->u8Time_FromWriteToRead);

    // The time from "reg_mspi_trigger" to first SPI clock
    MSPI_WRITEBYTE4(REG_MSPI__TIME_TR_START, pMSPICtrlInfo->u8Time_FromTriggerToFirstClock);
    // The time from last SPI clock to "reg_mspi_done_flag"
    MSPI_WRITEBYTE4(REG_MSPI__TIME_TR_END, pMSPICtrlInfo->u8Time_LastClockToDone);
    // The time between byte to byte transfer
    MSPI_WRITEBYTE4(REG_MSPI__TIME_B_TO_B, pMSPICtrlInfo->u8Time_BetweenByteToByte);
    // The time between last write and first read,
    MSPI_WRITEBYTE4(REG_MSPI__TIME_W_TO_R, pMSPICtrlInfo->u8Time_FromWriteToRead);
#endif
}

void MDrv_SPI0_LDMA_Done_ISR(void)
{

}

void MDrv_SPI1_LDMA_Done_ISR(void)
{


}

void MDrv_SPI2_LDMA_Done_ISR(void)
{

}

void MDrv_SPI3_LDMA_Done_ISR(void)
{

}

#if (ENABLE_LDMA_MSPI_DONE_INT )
void MDrv_SPI_LDMA_Done_INT_Init(void)
{
    if(MSPI_PORT_NUM == 0)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE0, (InterruptCb)MDrv_SPI0_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE0);
    }
    else if (MSPI_PORT_NUM == 1)
    {

        #if 0//(CustomerType == CustomerType_Xiaomi_Ultrasonic)

        #else
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE1, (InterruptCb)MDrv_SPI1_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE1);
        #endif
    }
    else if (MSPI_PORT_NUM == 2)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE2, (InterruptCb)MDrv_SPI2_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE2);
    }
    else if (MSPI_PORT_NUM == 3)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE3, (InterruptCb)MDrv_SPI3_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE3);
    }

#if (ENABLE_TWO_SPI == 1)

    if(MSPI_PORT_NUM2 == 0)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE0, (InterruptCb)MDrv_SPI0_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE0);
    }
    else if (MSPI_PORT_NUM2 == 1)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE1, (InterruptCb)MDrv_SPI1_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE1);
    }
    else if (MSPI_PORT_NUM2 == 2)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE2, (InterruptCb)MDrv_SPI2_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE2);
    }
    else if (MSPI_PORT_NUM2 == 3)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE3, (InterruptCb)MDrv_SPI3_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE3);
    }
#elif ENABLE_FOUR_SPI
    //MSPI_PORT_NUM2
    if(MSPI_PORT_NUM2 == 0)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE0, (InterruptCb)MDrv_SPI0_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE0);
    }
    else if (MSPI_PORT_NUM2 == 1)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE1, (InterruptCb)MDrv_SPI1_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE1);
    }
    else if (MSPI_PORT_NUM2 == 2)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE2, (InterruptCb)MDrv_SPI2_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE2);
    }
    else if (MSPI_PORT_NUM2 == 3)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE3, (InterruptCb)MDrv_SPI3_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE3);
    }

    //MSPI_PORT_NUM3
    if(MSPI_PORT_NUM3 == 0)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE0, (InterruptCb)MDrv_SPI0_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE0);
    }
    else if (MSPI_PORT_NUM3 == 1)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE1, (InterruptCb)MDrv_SPI1_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE1);
    }
    else if (MSPI_PORT_NUM3 == 2)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE2, (InterruptCb)MDrv_SPI2_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE2);
    }
    else if (MSPI_PORT_NUM3 == 3)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE3, (InterruptCb)MDrv_SPI3_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE3);
    }

    //MSPI_PORT_NUM4
    if(MSPI_PORT_NUM4 == 0)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE0, (InterruptCb)MDrv_SPI0_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE0);
    }
    else if (MSPI_PORT_NUM4 == 1)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE1, (InterruptCb)MDrv_SPI1_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE1);
    }
    else if (MSPI_PORT_NUM4 == 2)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE2, (InterruptCb)MDrv_SPI2_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE2);
    }
    else if (MSPI_PORT_NUM4 == 3)
    {
        MDrv_IRQ_Attach(E_FIQ_LDM_DMA_DONE3, (InterruptCb)MDrv_SPI3_LDMA_Done_ISR);
        MDrv_IRQ_UnMask(E_FIQ_LDM_DMA_DONE3);
    }
#endif
}
#endif

BOOL MDrv_SPI_Init(BOOL bForce ,StuMSPICtrlInfo MSPICtrlInfo)
{
    U16 i;

    if( s_bMDrvSPI_InitFinished )
    {
        if( bForce == FALSE )
        {
            // Already inited!
            return TRUE;
        }
    }

    MDrv_WriteRegBit(REG_33EC, TRUE, _BIT0);

    // Setup clock parameter
    s_MSPICtrlInfo.eMSPIClockGen = MSPICtrlInfo.eMSPIClockGen; //MSPI_CLK_SPD_24M;
    s_MSPICtrlInfo.eMSPIClockDiv = MSPICtrlInfo.eMSPIClockDiv; //MSPI_CLK_SPD__DIV_8;
    s_MSPICtrlInfo.u8ClockPolarity = MSPICtrlInfo.u8ClockPolarity;//0 ;
    s_MSPICtrlInfo.u8ClockPhase =  MSPICtrlInfo.u8ClockPhase; //0 ;
    // Setup timing&delay parameter
    s_MSPICtrlInfo.u8Time_FromTriggerToFirstClock = MSPICtrlInfo.u8Time_FromTriggerToFirstClock; //0; // 1 cycle
    s_MSPICtrlInfo.u8Time_LastClockToDone = MSPICtrlInfo.u8Time_LastClockToDone; //0; // 1 cycle
    s_MSPICtrlInfo.u8Time_BetweenByteToByte = MSPICtrlInfo.u8Time_BetweenByteToByte; //0; // 0 cycle
    s_MSPICtrlInfo.u8Time_FromWriteToRead = MSPICtrlInfo.u8Time_FromWriteToRead; //0; // 0 cycle

    _MHal_MSPI_SetupTimingAndDelay(&s_MSPICtrlInfo);


    /*if((CustomerType==CustomerType_TSB_Unicorn)&&(PANEL_TYPE_SEL == PNL_CMIV650DK1_KD1_4K2K120Hz))
    {
        _MHal_MSPI_SetWriteBufBitLen(12); //This is set SPI output bits.
    }
    else
    {
        _MHal_MSPI_SetWriteBufBitLen(8);
    }*/
    _MHal_MSPI_SetWriteBufBitLen(MSPICtrlInfo.u8SpiOutputDataBit);
    _MHal_MSPI_SetReadBufBitLen(8);

    MSPI_WRITEBIT(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI);
    MSPI_WRITEBIT(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);

    MSPI_WRITEBIT(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI_INT);

    MSPI_WRITEBYTE(REG_MSPI__CLEAR_DONE, 1); // Clear done

#if ENABLE_TWO_SPI
    MSPI_WRITEBIT2(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI);
    MSPI_WRITEBIT2(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);

    MSPI_WRITEBIT2(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI_INT);

    MSPI_WRITEBYTE2(REG_MSPI__CLEAR_DONE, 1); // Clear done
#elif ENABLE_FOUR_SPI
    MSPI_WRITEBIT2(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI);
    MSPI_WRITEBIT2(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);
    MSPI_WRITEBIT2(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI_INT);
    MSPI_WRITEBYTE2(REG_MSPI__CLEAR_DONE, 1); // Clear done

    MSPI_WRITEBIT3(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI);
    MSPI_WRITEBIT3(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);
    MSPI_WRITEBIT3(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI_INT);
    MSPI_WRITEBYTE3(REG_MSPI__CLEAR_DONE, 1); // Clear done

    MSPI_WRITEBIT4(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI);
    MSPI_WRITEBIT4(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);
    MSPI_WRITEBIT4(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__EN_MSPI_INT);
    MSPI_WRITEBYTE4(REG_MSPI__CLEAR_DONE, 1); // Clear done
#endif

    s_bMspiOperationIsDone = 0;

    s_eSpiTriggerMode = E_SPI_TRIGGER_NONE;

    // Setup write buffer ...
    for( i = 0; i < SPI_WRITE_BUF_SIZE; ++ i )
    {
        s_aucSpiWriteBuf_Real[i] = 0xFF;
        s_aucSpiWriteBuf_User[i] = 0xFF;
        s_bSpiWriteBufUserChanged = FALSE;
        s_aucSpiWriteBuf_BitLen[i] = 0x3F;
        s_aucSpiWriteBuf_Delay[i] = 0;
    #if (ENABLE_DEBUG_SW_SPI)
        g_u32DrvSPI_Debug_Int_t[i] = 0;
    #endif
    }
    s_u16SpiWriteBufSize = 0;
    s_u16SpiWriteBuf_Index = 0;

    s_eSpiState = E_SPI_STATE__NONE;


#if(ENABLE_DEBUG_SW_SPI )
    g_u32DrvSPI_Debug_VS_IntCnt = 0;
    g_u32DrvSPI_Debug_MSPI_IntCnt = 0;
    g_u32DrvSPI_Debug_MSPI_IntCnt_Err = 0;
#endif


    s_bMDrvSPI_InitFinished = TRUE;

#if(ENABLE_DEBUG_SW_SPI )
    MDrv_IRQ_Attach(E_IRQ_MSPI1_INT, (InterruptCb)FRC_R2_IRQ_ISR);

    MDrv_IRQ_UnMask(E_IRQ_MSPI1_INT);
#else
  #if (ENABLE_LDMA_MSPI_DONE_INT )
    MDrv_SPI_LDMA_Done_INT_Init();
  #endif
#endif

    //printf("\n -- ox %s()\n",__FUNCTION__);

    return s_bMDrvSPI_InitFinished;
}

#if (ENABLE_SSPI_DRIVER)
void MDrv_SPI_SSPI_Init(void)
{
    //MDrv_SPI_SSPI_Enable(ENABLE);//enable sspi

    MDrv_Write2Byte(REG_0212, 0x0002);  //RX mode only
    MDrv_Write2Byte(REG_0258, 0x0018);  //in intr mask ,rx under flow
    MDrv_Write2Byte(REG_0238, 0x0003);  // rx threshold :0 data
    MDrv_Write2Byte(REG_0200, 0x00c7);  // rx threshold :2 data
    MDrv_WriteByte(REG_03FE, 0x02);

    MDrv_SPI_SSPI_Port_Sel(SSPI_PORT_NUM);
}

void MDrv_SPI_SSPI_Enable(BOOL bEnable)
{
    if(bEnable)
        MDrv_WriteByteMask(REG_0210, BIT0, BIT0);  //enable sspi
    else
        MDrv_WriteByteMask(REG_0210, 0, BIT0);     //disable sspi
}

void MDrv_SPI_SSPI_Port_Sel(U8 u8SSPI_Port)
{
    if(u8SSPI_Port != SSPI_INVAILD_PORT_NUM)
        MDrv_WriteByteMask(REG_1E34, (1<<(u8SSPI_Port+4))&0xFF, 0xF0);     //no SPI as sspi
    else
        MDrv_WriteByteMask(REG_1E34, 0, 0xF0);     //no SPI as sspi

}

U16 MDrv_SPI_SSPI_Get_FIFO_Rec_Data_Number(void)
{
    return MDrv_Read2Byte(REG_0248);
}

void MDrv_SPI_SSPI_Data_Rec_ISR(void)
{
    U8 u8Data_Idx = 0;
    for(u8Data_Idx=0; u8Data_Idx < SSPI_ACCEPT_DATA; u8Data_Idx++)
    {
        g_u8SSPI_Data_Buf[u8Data_Idx] = MDrv_ReadByte(REG_02C0);
        //printf("%x\r\n",g_u8SSPI_Data_Buf[u8Data_Idx]);
    }
}

/*
BOOL MDrv_SPI_GetSSPIDataArray(U8* u8SSPI_Data, U8 u8arraysize)
{
    if(gSSPI_Size < u8arraysize)
    {
        U8 u8Idx=0;
        for(u8Idx=0; u8Idx<gSSPI_Size; u8Idx++)
        {
            u8SSPI_Data[u8Idx] = gu8SSPI_LD_Buf[u8Idx];
        }
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

U8 MDrv_SPI_GetSSPIDataSize(void)
{
    return gSSPI_Size;
}

BOOL MDrv_SPI_GetSSIP_Status(void)
{
    return bSSPI_Get_AllData;
}

void MDrv_SPI_Set_SSIP_Status(BOOL bIsFinished)
{
    bSSPI_Get_AllData = bIsFinished;
}

*/
#endif

void _MHAL_MSPI_SendOneByte( U8 u8DelayTime, U8 u8Data, U8 u8BitLen )
{
    //printf("[%X]",u8Data);
    // Set delay time before data
    MHal_MSPI_SetTime_TriggerToFirstClock(u8DelayTime);

    // Set write buffer data
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START, u8Data);

    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, u8BitLen-1, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, 1);


#if 0
    {
        U16 i;
        for(i=0;i<100; ++i )
            MFC_WriteByte(REG_MSPI__WRITE_BUF_SIZE, 1);
    }
#endif

    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );
}

void _MHAL_MSPI_SendBytes( U8 auSpiWriteBuf_Delay[], U8 auSpiWriteBuf_Data[], U8 auSpiWriteBuf_BitLen[], U8 auSpiWriteBuf_Len )
{

    U8 i;

    // Set delay time before data
    MHal_MSPI_SetTime_TriggerToFirstClock(auSpiWriteBuf_Delay[auSpiWriteBuf_Len*MSPI_SEND_BYTES]);

    for(i=0; i<MSPI_SEND_BYTES; i++)
    {

        // Set write buffer data
        //printf("auSpiWriteBuf_Data[%d] = 0x%x\n",auSpiWriteBuf_Len*3+i,auSpiWriteBuf_Data[auSpiWriteBuf_Len*3+i]);
        MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+i, auSpiWriteBuf_Data[auSpiWriteBuf_Len*MSPI_SEND_BYTES+i]);

    }

    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, auSpiWriteBuf_BitLen[auSpiWriteBuf_Len*MSPI_SEND_BYTES], 0x3F); //CC DISABLE FOR TEST
    //MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, auSpiWriteBuf_BitLen[0], 0x3F);//FOR TEST

    // Set write buffer size
    //MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, MSPI_SEND_BYTES);

    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );


}

void _MDrv_SPI_SetWriteBuf_User( U8 au8Buf[], U16 u16BufLen )
{
    U16 i;

    // Copy buf to internal temp write buffer
    for( i = 0; i < u16BufLen; ++ i )
    {
        s_aucSpiWriteBuf_User[i] = au8Buf[i];
    }
    s_u16SpiWriteBufSize = u16BufLen;
    s_bSpiWriteBufUserChanged = TRUE;
}

void _MDrv_SPI_CopyUserWriteBufToRealWriteBuf(void)
{
    U16 i;

    if( s_bSpiWriteBufUserChanged )
    {
        for( i = 0; i < s_u16SpiWriteBufSize; ++ i )
        {
            s_aucSpiWriteBuf_Real[i] = s_aucSpiWriteBuf_User[i];
        }
        s_bSpiWriteBufUserChanged = FALSE;
    }

    //_MDrv_SPI_CalCheckSum();
}

BOOL MDrv_SPI_SetWriteBuf_BitLen( U8 au8Buf_BitLen[], U16 u16BufLen )
{
    U16 i;


    if( s_bMDrvSPI_InitFinished == FALSE )
        return FALSE;

    if( au8Buf_BitLen == NULL )
        return FALSE;

    if( u16BufLen == 0 || (u16BufLen > SPI_WRITE_BUF_SIZE) )
        return FALSE;

    // Copy buf to internal write buffer
    for( i = 0; i < u16BufLen; ++ i )
    {
        s_aucSpiWriteBuf_BitLen[i] = au8Buf_BitLen[i];
    }

    return TRUE;
}

#define UNKNOWN_DELAY_US    7 // For MSPI_CLK_SPD__DIV_64

#define HW_DELAY_1_CYCLE    1
#define HW_DELAY_2_CYCLE    (HW_DELAY_1_CYCLE+1)

BOOL MDrv_SPI_SetWriteBuf_Delay( U8 au8Buf_Delay[], U16 u8BufLen )
{
    U16 i;
    U32 u32MSPIClkPeriodUsX1000;
    U16 u16DelayUs;
    U16 u16DelayCycle;


    if( s_bMDrvSPI_InitFinished == FALSE )
        return FALSE;

    if( au8Buf_Delay == NULL )
        return FALSE;

    if( u8BufLen == 0 || (u8BufLen > SPI_WRITE_BUF_SIZE) )
        return FALSE;

    u32MSPIClkPeriodUsX1000 = MHal_MSPI_Clk_To_Period_Us_X1000(s_MSPICtrlInfo.eMSPIClockDiv);
    //printf("u32MSPIClkPeriodUsX1000=%u\n", u32MSPIClkPeriodUsX1000);
    // Copy buf to internal write buffer
    for( i = 0; i < u8BufLen; ++ i )
    {
        u16DelayUs = au8Buf_Delay[i];
    //    printf("(%u) u16DelayUs=%u, ", i, u16DelayUs );
        if( u16DelayUs <= UNKNOWN_DELAY_US )
        {
            u16DelayUs = 0;
        }
        else
        {
            u16DelayUs -= UNKNOWN_DELAY_US;
        }
    //    printf(" u16DelayUs=%u, ", u16DelayUs );

        u16DelayCycle = (U32)1000*u16DelayUs/u32MSPIClkPeriodUsX1000;
        if( i == 0 )
        {
            if( u16DelayCycle <= HW_DELAY_1_CYCLE )
                u16DelayCycle = 0;
            else
                u16DelayCycle -= HW_DELAY_1_CYCLE;
        }
        else
        {
            if( u16DelayCycle <= HW_DELAY_2_CYCLE )
                u16DelayCycle = 0;
            else
                u16DelayCycle -= HW_DELAY_2_CYCLE;
        }
    //    printf(" u16DelayCycle=%u, ", u16DelayCycle );

        if( u16DelayCycle > 255 )
            s_aucSpiWriteBuf_Delay[i] = 255;
        else
            s_aucSpiWriteBuf_Delay[i] = u16DelayCycle;

        //s_aucSpiWriteBuf_Delay[i] = 0;
    //    printf(" => %u\n" , s_aucSpiWriteBuf_Delay[i]);
    }

    return TRUE;
}

BOOL _MDrv_SPI_Write_FirstByte(void)
{
    if( s_bMDrvSPI_InitFinished == FALSE )
        return FALSE;

    if( s_u16SpiWriteBufSize == 0 )
        return FALSE;

    // Set chip-select?
    MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 1, BIT0);
    // check first delay
#if (ENABLE_DEBUG_SW_SPI)
    g_u32DrvSPI_Debug_Int_t[0] = MsOS_GetSystemTime();
#endif
    s_u16SpiWriteBuf_Index = 0;
    _MHAL_MSPI_SendBytes( s_aucSpiWriteBuf_Delay, s_aucSpiWriteBuf_Real, s_aucSpiWriteBuf_BitLen, s_u16SpiWriteBuf_Index );
    s_u16SpiWriteBuf_Index += 1;

    return FALSE;
}

void _MDrv_MSPI_ResetState(void)
{
    // Reset MSPI
    MSPI_WRITEBIT(REG_MSPI__CTRL, 0, MASK_MSPI_CTRL__NOT_RESET);

    s_eSpiState = E_SPI_STATE__NONE;
    s_bMspiOperationIsDone = FALSE;

    // Not reset MSPI
    MSPI_WRITEBIT(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);

    MSPI_WRITEBYTE(REG_MSPI__CLEAR_DONE, 1); // Clear done
}

BOOL MDrv_SPI_SetTriggerMode(EnuSpiTriggerMode eSpiTriggerMode)
{
    if( s_bMDrvSPI_InitFinished == FALSE )
        return FALSE;

    if( (s_eSpiTriggerMode != eSpiTriggerMode)
      ||(eSpiTriggerMode == E_SPI_TRIGGER_NONE)
      ||(eSpiTriggerMode == E_SPI_TRIGGER_BY_ONE_TIME) )
    {
        _MDrv_MSPI_ResetState();
    }

    switch( eSpiTriggerMode )
    {
        case E_SPI_TRIGGER_NONE:
            // Do no-thing
            break;

        case E_SPI_TRIGGER_BY_ONE_TIME:
            s_eSpiState = E_SPI_STATE__W_WAIT_MSPI_INT;
            _MDrv_SPI_Write_FirstByte();
            break;

        case E_SPI_TRIGGER_BY_V_SYNC:
        case E_SPI_TRIGGER_BY_EVERY_V_SYNC:
            if( s_eSpiState == E_SPI_STATE__NONE )
                s_eSpiState = E_SPI_STATE__W_WAIT_VSYNC_INT;
        #if(ENABLE_DEBUG_SW_SPI)
            g_u32DrvSPI_Debug_VS_IntCnt = 0;
            g_u32DrvSPI_Debug_MSPI_IntCnt = 0;
        #endif
            break;
    }

    s_eSpiTriggerMode = eSpiTriggerMode;

    return TRUE;
}

void MDrv_SPI_ISR_Vsync(void)
{
    if( s_bMDrvSPI_InitFinished == FALSE )
        return;

    if( s_eSpiState == E_SPI_STATE__NONE )
        return;

    if( s_eSpiState == E_SPI_STATE__W_WAIT_MSPI_INT )
    {
        if( (s_eSpiTriggerMode == E_SPI_TRIGGER_BY_V_SYNC)
          ||(s_eSpiTriggerMode == E_SPI_TRIGGER_BY_EVERY_V_SYNC) )
        {
        #if(ENABLE_DEBUG_SW_SPI)
            g_u32DrvSPI_Debug_VS_Int_t2 = MsOS_GetSystemTime();
        #endif
            // Warning: It mean it can not finished in one frame time
            _MDrv_MSPI_ResetState();
//            ADD_SYS_ERR_MSG(SYS_ERR_SPI_OPERATION_CAN_NOT_FINISH_IN_ONE_FRAME, NULL);
            printf(" ==> Err:Idx=%u\n", s_u16SpiWriteBuf_Index);
        }
        return;
    }

    //if( s_eSpiState == E_SPI_STATE__W_WAIT_VSYNC_INT )
    {
        if( s_eSpiTriggerMode == E_SPI_TRIGGER_BY_EVERY_V_SYNC )
        {
            _MDrv_SPI_CopyUserWriteBufToRealWriteBuf();
        }

        s_eSpiState = E_SPI_STATE__W_WAIT_MSPI_INT;

        // Patch - Reset MSPI
        // Reset MSPI
        // MFC_WriteBit(REG_MSPI__CTRL, 0, MASK_MSPI_CTRL__NOT_RESET);
        // Not reset MSPI
        //MFC_WriteBit(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__NOT_RESET);

        _MDrv_SPI_Write_FirstByte();

    #if(ENABLE_DEBUG_SW_SPI)
        g_u32DrvSPI_Debug_VS_Int_t1 = MsOS_GetSystemTime();
        g_u32DrvSPI_Debug_VS_IntCnt += 1;
    #endif

    }
}

void MDrv_SPI_ISR(void)
{
//    U16 u16SpiWriteBuf_TmpIndex;
    MSPI_WRITEBYTE(REG_MSPI__CLEAR_DONE, 1); // Clear done
#if 1
    //printf(" s_eSpiState  = %d\n" ,s_eSpiState);
    if( s_bMDrvSPI_InitFinished == FALSE )
        return ;
    if( s_eSpiState != E_SPI_STATE__W_WAIT_MSPI_INT )
    {
        //printf(" MDrv_SPI_ISR 2 \n");
        MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 1, BIT0);
    #if(ENABLE_DEBUG_SW_SPI)
        g_u32DrvSPI_Debug_MSPI_IntCnt_Err += 1;
    #endif
        return;
    }
    else
    {
        #if (ENABLE_DEBUG_SW_SPI)
            g_u32DrvSPI_Debug_Int_t[s_u16SpiWriteBuf_Index*MSPI_SEND_BYTES] = MsOS_GetSystemTime();
        #endif
        if( s_u16SpiWriteBuf_Index < (s_u16SpiWriteBufSize/MSPI_SEND_BYTES +1) ) // Need send next data
        {
            _MHAL_MSPI_SendBytes( s_aucSpiWriteBuf_Delay, s_aucSpiWriteBuf_Real, s_aucSpiWriteBuf_BitLen, s_u16SpiWriteBuf_Index );
            s_u16SpiWriteBuf_Index += 1;
        }
        else
        {
            if( (s_eSpiTriggerMode == E_SPI_TRIGGER_BY_ONE_TIME)
              ||(s_eSpiTriggerMode == E_SPI_TRIGGER_BY_V_SYNC) )
            {
                s_eSpiState = E_SPI_STATE__NONE;
                s_eSpiTriggerMode = E_SPI_TRIGGER_NONE;
                MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 0, BIT0);
            }
            else if(s_eSpiTriggerMode == E_SPI_TRIGGER_BY_EVERY_V_SYNC)
            {
                s_eSpiState = E_SPI_STATE__W_WAIT_VSYNC_INT;
                MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 0, BIT0);

            }
            s_bMspiOperationIsDone = 1;
        }
    }

#if(ENABLE_DEBUG_SW_SPI)
    g_u32DrvSPI_Debug_MSPI_IntCnt += 1;
    g_u32DrvSPI_Debug_MSPI_Int_t = MsOS_GetSystemTime();
#endif

#endif
}

void MDrv_SPI_Stop(void)
{
    _MDrv_MSPI_ResetState();
    s_eSpiTriggerMode = E_SPI_TRIGGER_NONE;
}

BOOL MDrv_SPI_End(void)
{
    U32 u32Time;
    BOOL bResult = FALSE;
    while(1)
    {
        u32Time = MsOS_GetSystemTime();
        if(MDrv_ReadRegBit(0x1AB6,BIT0)==1)
        {
            MSPI_WRITEBYTEMASK(REG_MSPI__CLEAR_DONE, 1, BIT0);
            MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 1, BIT0);
            bResult = TRUE;
            break;
        }
        if( msAPI_Timer_DiffTimeFromNow(u32Time) > 500 ) // Timeout
        {
            printf("[MSPI]Wait done timeout!\n");
            bResult = FALSE;
            break;
        }
    }
    return bResult;
}

BOOL MDrv_SPI_WriteBytes( U8 au8Buf[], U16 u16BufLen, EnuSpiTriggerMode eSpiTriggerMode )
{
    BOOL bResult = FALSE;
    U32 u32Time;

    eSpiTriggerMode = eSpiTriggerMode;

    if( s_bMDrvSPI_InitFinished == FALSE )
        return FALSE;
    if( au8Buf == NULL )
        return FALSE;
    if( u16BufLen == 0 || (u16BufLen > SPI_WRITE_BUF_SIZE) )
        return FALSE;

    if( eSpiTriggerMode == E_SPI_TRIGGER_NONE )
    {
        return FALSE;
    }
    if( (s_eSpiTriggerMode != eSpiTriggerMode)
      ||(eSpiTriggerMode == E_SPI_TRIGGER_BY_ONE_TIME) )
    {
        //_MDrv_MSPI_ResetState();
        MDrv_SPI_Stop();
    }
    // Copy buf to internal write buffer

    _MDrv_SPI_SetWriteBuf_User( au8Buf, u16BufLen );
    _MDrv_SPI_CopyUserWriteBufToRealWriteBuf();


    MDrv_SPI_SetTriggerMode(eSpiTriggerMode);

    // Wait done
    if( eSpiTriggerMode == E_SPI_TRIGGER_BY_ONE_TIME )
    {
        u32Time = MsOS_GetSystemTime();
        while( 1 )
        {
            if( s_eSpiState == E_SPI_STATE__NONE || s_bMspiOperationIsDone ) // MSPI done
            {
                bResult = TRUE;
                break;
            }
            if( (MsOS_GetSystemTime()-u32Time) > 100 ) // Timeout
            {
                printf("[MSPI]Wait done timeout!\n");
                bResult = FALSE;
                break;
            }
        }
    }

    // Set chip-select?
    //MDrv_WriteByteMask(REG_MSPI__CHIP_SELECT, 1, _BIT0);

    return bResult;
}

BOOL MDrv_SPI_ReadBytes( U8 au8Buf[], U8 u8WriteBufLen,U8 u8ReadBufLen, EnuSpiTriggerMode eSpiTriggerMode )
{
    BOOL bResult = FALSE;
    U32 u32Time;
    U8 j;
    eSpiTriggerMode = eSpiTriggerMode;

    if(MDrv_ReadByte(0x1ABE)== 0xFF)
    {
        MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 0, BIT0);
    }

    for(j=0; j<u8WriteBufLen; j++)
        MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+j, au8Buf[j]);

    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, 0x7, 0x7);
    // Set read data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__READ_BUF_BIT_LEN, 0x7, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, u8WriteBufLen);
    // Set read buffer size
    MSPI_WRITEBYTE(REG_MSPI__READ_BUF_SIZE, u8ReadBufLen+u8WriteBufLen);
    // trigger

    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );

    while(1)
    {
        u32Time = MsOS_GetSystemTime();
        if(MDrv_ReadRegBit(0x1AB6,BIT0)==1)
        {
            MSPI_WRITEBYTEMASK(REG_MSPI__CLEAR_DONE, 1, BIT0);
            MSPI_WRITEBYTEMASK(REG_MSPI__CHIP_SELECT, 1, BIT0);
            bResult = TRUE;
            break;
        }
        if( (MsOS_GetSystemTime()-u32Time) > 100 ) // Timeout
        {
            printf("[MSPI]Wait done timeout!\n");
            bResult = FALSE;
            break;
        }
    }
    return bResult;
}

U8 MDrv_SPI_GetState(void)
{
    return s_eSpiState;
}
U8 MDrv_SPI_GetTriggerMode(void)
{
    return s_eSpiTriggerMode;
}

#if 0
void MDrv_SPI_VSyncLikeInit(void)
{
/***************************************************************************
Temp add for PWM5 as V-sync like configuration (need to implement in MIPS)
***************************************************************************/
    //0x37 Uart command
    MDrv_MFC_PWM_waveform_maker(PWM_CH5, 0x78 * 10, 0x01 * 10,
                                0 * 200, 12, 0,
                                Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, 0);

    MHal_PWM_WaveformResetEnable(PWM_CH5, ENABLE);

    MHal_PWM_OutputEn(PWM_CH5, ENABLE);

    MDrv_PWM_Set_PadEn( PWM_CH5, ENABLE );
}

void MDrv_SPI_Make_VSyncLike(U16 Freq,U16 Div,BOOL bPolarity)
{
Freq=Freq;
Div=Div;
bPolarity=bPolarity;


    MDrv_MFC_PWM_waveform_maker(PWM_CH5, Freq * 10, 0x01 * 10,
                                0 * 200, Div, 0,
                                Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, bPolarity);

    MHal_PWM_WaveformResetEnable(PWM_CH5, ENABLE);

    MHal_PWM_OutputEn(PWM_CH5, ENABLE);

    MDrv_PWM_Set_PadEn( PWM_CH5, ENABLE );
}

void MDrv_SPI_SttInit(void)
{
    U8 u8SttShift =6 ;

    u8SttShift=u8SttShift;

    //0x39 Uart command

    MDrv_MFC_PWM_waveform_maker(PWM_CH0, 0x78 * 10, 0x7D * 10,
                            u8SttShift , 12, 0,
                            Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, 0);

    MHal_PWM_WaveformResetEnable(PWM_CH0, ENABLE);

    MHal_PWM_OutputEn(PWM_CH0, ENABLE);

    MDrv_PWM_Set_PadEn( PWM_CH0, ENABLE );
}
#endif


void MDrv_SPI_Test1(void)
{
    BOOL bResult = FALSE;
    U8 au8TmpBuf[3];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    //U16 i;
    U16 j = 0;


    printf("MDrv_SPI_Test1\n");

    //for( i = 0; i < 32; ++ i )
    //    au8TmpBuf[i] = i;
    au8TmpBuf[0]= 0x41;
    au8TmpBuf[1]= 0x36;
    au8TmpBuf[2]= 0x03;
#if 0 // test E_SPI_TRIGGER_BY_ONE_TIME
    bResult = TRUE;
    for( j = 0; j < 1000; ++j )
    {
        //printf(" test %u\n", j);
        if( FALSE == MDrv_SPI_WriteBytes( au8TmpBuf, 100, E_SPI_TRIGGER_BY_ONE_TIME ) )
        {
            bResult = FALSE;
            break;
        }
    }
    if( bResult == FALSE )
    {
        printf("Test1 is failed! j=%u\n\n", j);
    }
    else
    {
        printf("Test1 is OK! j=%u\n\n", j);
    }

#else // test E_SPI_TRIGGER_BY_EVERY_V_SYNC
    j = j;
    bResult = bResult;

    // Set delay time before data
    //MHal_MSPI_SetTime_TriggerToFirstClock(u8DelayTime);

    // Set write buffer data
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START, au8TmpBuf[0]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+1, au8TmpBuf[1]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+2, au8TmpBuf[2]);
    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, 0x7, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, 3);
    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );
#endif

    //printf("Test1 result=%u\n\n", bResult);
}

void MDrv_SPI_Test2(void)
{
    BOOL bResult = FALSE;
    U8 au8TmpBuf[6];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    //U16 i;
    U16 j = 0;


    printf("MDrv_SPI_Test2\n");

    //for( i = 0; i < 32; ++ i )
    //    au8TmpBuf[i] = i;
    au8TmpBuf[0]= 0x41;
    au8TmpBuf[1]= 0x82;
    au8TmpBuf[2]= 0x00;
    au8TmpBuf[3]= 0x00;
    au8TmpBuf[4]= 0x00;
    au8TmpBuf[5]= 0x00;
#if 0 // test E_SPI_TRIGGER_BY_ONE_TIME
    bResult = TRUE;
    for( j = 0; j < 1000; ++j )
    {
        //printf(" test %u\n", j);
        if( FALSE == MDrv_SPI_WriteBytes( au8TmpBuf, 100, E_SPI_TRIGGER_BY_ONE_TIME ) )
        {
            bResult = FALSE;
            break;
        }
    }
    if( bResult == FALSE )
    {
        printf("Test1 is failed! j=%u\n\n", j);
    }
    else
    {
        printf("Test1 is OK! j=%u\n\n", j);
    }

#else // test E_SPI_TRIGGER_BY_EVERY_V_SYNC
    j = j;
    bResult = bResult;

    // Set delay time before data
    //MHal_MSPI_SetTime_TriggerToFirstClock(u8DelayTime);

    // Set write buffer data
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START, au8TmpBuf[0]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+1, au8TmpBuf[1]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+2, au8TmpBuf[2]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+3, au8TmpBuf[3]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+4, au8TmpBuf[4]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+5, au8TmpBuf[5]);
    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, 0x7, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, 6);
    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );
#endif

    //printf("Test1 result=%u\n\n", bResult);
}
void MDrv_SPI_Test3(U8 test1,U8 test2)
{
    BOOL bResult = FALSE;
    U8 au8TmpBuf[6];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    //U16 i;
    U16 j = 0;


    printf("MDrv_SPI_Test3\n");

    //for( i = 0; i < 32; ++ i )
    //    au8TmpBuf[i] = i;
    au8TmpBuf[0]= test1;
    au8TmpBuf[1]= test2;
    au8TmpBuf[2]= 0x00;
    au8TmpBuf[3]= 0x00;
    au8TmpBuf[4]= 0x00;
    au8TmpBuf[5]= 0x00;
#if 0 // test E_SPI_TRIGGER_BY_ONE_TIME
    bResult = TRUE;
    for( j = 0; j < 1000; ++j )
    {
        //printf(" test %u\n", j);
        if( FALSE == MDrv_SPI_WriteBytes( au8TmpBuf, 100, E_SPI_TRIGGER_BY_ONE_TIME ) )
        {
            bResult = FALSE;
            break;
        }
    }
    if( bResult == FALSE )
    {
        printf("Test1 is failed! j=%u\n\n", j);
    }
    else
    {
        printf("Test1 is OK! j=%u\n\n", j);
    }

#else // test E_SPI_TRIGGER_BY_EVERY_V_SYNC
    j = j;
    bResult = bResult;

    // Set delay time before data
    //MHal_MSPI_SetTime_TriggerToFirstClock(u8DelayTime);

    // Set write buffer data
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START, au8TmpBuf[0]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+1, au8TmpBuf[1]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+2, au8TmpBuf[2]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+3, au8TmpBuf[3]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+4, au8TmpBuf[4]);
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+5, au8TmpBuf[5]);
    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, 0x7, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, 6);
    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );
#endif

    //printf("Test1 result=%u\n\n", bResult);
}

BOOL MDrv_SPI_Test4( U8 au8Buf[], U8 u8BufLen, EnuSpiTriggerMode eSpiTriggerMode )
{
    BOOL bResult = FALSE;
    //U8 au8TmpBuf[6];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    //U16 i;
    U16 j = 0;

    eSpiTriggerMode = eSpiTriggerMode;
    printf("MDrv_SPI_Test4\n");
    j = j;
    bResult = bResult;
    // Set delay time before data
    //MHal_MSPI_SetTime_TriggerToFirstClock(u8DelayTime);

    // Set write buffer data
    for(j=0; j<u8BufLen; j++)
        MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+j, au8Buf[j]);

    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, 0x7, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, u8BufLen);
    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );

    return TRUE;
    //printf("Test1 result=%u\n\n", bResult);
}
void MDrv_SPI_Test5(void)
{
    BOOL bResult = FALSE;
    U8 au8TmpBuf[8];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    //U16 i;
    U16 j = 0;


    printf("MDrv_SPI_Test1\n");

    //for( i = 0; i < 32; ++ i )
    //    au8TmpBuf[i] = i;
    au8TmpBuf[0]= 0x41;
    au8TmpBuf[1]= 0x36;
    au8TmpBuf[2]= 0x03;


    au8TmpBuf[3]= 0x41;
    au8TmpBuf[4]= 0xB6;
    au8TmpBuf[5]= 0x00;
    au8TmpBuf[6]= 0x00;

    j = j;
    bResult = bResult;

    // Set delay time before data
    //MHal_MSPI_SetTime_TriggerToFirstClock(u8DelayTime);

    for(j=0; j<8; j++)
        MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_START+j, au8TmpBuf[j]);
    // Set write data bit length
    MSPI_WRITEBYTEMASK(REG_MSPI__WRITE_BUF_BIT_LEN, 0x7, 0x7);

    // Set write buffer size
    MSPI_WRITEBYTE(REG_MSPI__WRITE_BUF_SIZE, 3);
    // trigger
    MSPI_WRITEBYTE( REG_MSPI__TRIGGER_TRANSFER, 1 );

    //printf("Test1 result=%u\n\n", bResult);
}
void MDrv_SPI_Test6( U8 au8Buf[])
{
    BOOL bResult = FALSE;
//    U8 au8TmpBuf[8];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    //U16 i;
    U16 j = 0;


    printf("MDrv_SPI_Test1\n");

    //for( i = 0; i < 32; ++ i )
    //    au8TmpBuf[i] = i;
    //au8TmpBuf[0]= 0x41;
    //au8TmpBuf[1]= 0x36;
    //au8TmpBuf[2]= 0xAC;


    j = j;
    bResult = bResult;

    MDrv_SPI_WriteBytes(au8Buf, 3, E_SPI_TRIGGER_BY_V_SYNC);

}
void MDrv_SPI_Test7( U16 au8SPI_Write_BufSize,U8 au8SPI_Write_Data)
{
    U8 au8TmpBuf[au8SPI_Write_BufSize ];// = { 0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99};
    U16 i;
    for( i = 0; i < au8SPI_Write_BufSize+1; ++ i )
        au8TmpBuf[i] = au8SPI_Write_Data;
    for( i = 2; i < au8SPI_Write_BufSize+1; ++ i )
        s_aucSpiWriteBuf_BitLen[i] = 0x0F;
    MDrv_WriteByte(REG_1E98, 0x00);
    MDrv_WriteByte(REG_1A93, 0x02);
    MSPI_WRITEBIT(REG_MSPI__CTRL, 1, MASK_MSPI_CTRL__CLOCK_PHASE);
    MDrv_SPI_WriteBytes(au8TmpBuf, au8SPI_Write_BufSize, E_SPI_TRIGGER_BY_EVERY_V_SYNC);

}
void MDrv_SPI_PrintDebugInfo(void)
{
#if(ENABLE_DEBUG_SW_SPI)
    printf("-SwSPI info - start:\n");
    printf("  SPI_TriggerMode=%u, SPI_State=%u\n\r", MDrv_SPI_GetTriggerMode(),MDrv_SPI_GetState());
    printf("  g_u32DrvSPI_Debug_VS_IntCnt=%lu\n", g_u32DrvSPI_Debug_VS_IntCnt);
    printf("  g_u32DrvSPI_Debug_MSPI_IntCnt=%lu(Err=%lu)\n", g_u32DrvSPI_Debug_MSPI_IntCnt,g_u32DrvSPI_Debug_MSPI_IntCnt_Err);

    printf("  g_u32DrvSPI_Debug_VS_Int_t1=%u, g_u32DrvSPI_Debug_VS_Int_t2=%u\n\r", g_u32DrvSPI_Debug_VS_Int_t1, g_u32DrvSPI_Debug_VS_Int_t2);
    printf("  g_u32DrvSPI_Debug_MSPI_Int_t=%u\n\r", g_u32DrvSPI_Debug_MSPI_Int_t);
    /*{
        U16 i;
        for( i = 0; i < 12; ++ i )
            printf("[%lu]", g_u32DrvSPI_Debug_Int_t[i]);
        printf("\n");
    }*/
    printf("-SwSPI info - end:\n");
#endif
}

#if 0
void SPI_And_LD_Patch(U8 u8SttShift)
{
u8SttShift=u8SttShift;

    ////////// PWM5 /////////////
    MDrv_Write2Byte(0x2522, 0x07ff) ;
    MDrv_Write2Byte(0x2564, 0x0001) ;  //shift
    MDrv_Write2Byte(0x2524, 0x0010) ;  //duty
    MDrv_Write2Byte(0x2526, 0x4400) ;

    MDrv_Write2Byte(0x3302, 0x0001); //local dimming enable


    //0x37 Uart command
    MDrv_MFC_PWM_waveform_maker(PWM_CH5, 0x78 * 10, 0x01 * 10,
                                0 * 200, 12, 0,
                                Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, 0);

    MHal_PWM_WaveformResetEnable(PWM_CH5, ENABLE);

    MHal_PWM_OutputEn(PWM_CH5, ENABLE);

    MDrv_PWM_Set_PadEn( PWM_CH5, ENABLE );


    //0x39 Uart command

    MDrv_MFC_PWM_waveform_maker(PWM_CH0, 0x78 * 10, 0x7D * 10,
                            u8SttShift , 12, 0,
                            Vsync_DoubleBF, PWM_RST_CTRL__VSYNC, 0);

    MHal_PWM_WaveformResetEnable(PWM_CH0, ENABLE);

    MHal_PWM_OutputEn(PWM_CH0, ENABLE);

    MDrv_PWM_Set_PadEn( PWM_CH0, ENABLE );

    MDrv_WriteRegBit(0x3305, TRUE, _BIT0);  //Patch to disable LDF write 0x02[8]: reg_wbank_soft_mode
}
#endif

void MDrv_MSPI_Set_ChipSelect(BOOLEAN bHigh)
{
    MSPI_WRITEBIT(REG_MSPI__CHIP_SELECT, bHigh, BIT0);
#if ENABLE_TWO_SPI
    MSPI_WRITEBIT2(REG_MSPI__CHIP_SELECT, bHigh, BIT0);
#endif
}

#endif

