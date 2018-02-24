#ifndef _MDRV_MSPI_H_
#define _MDRV_MSPI_H_


#ifdef _MDRV_MSPI_C_
    #define _MDRV_MSPI_DEC_
#else
    #define _MDRV_MSPI_DEC_  extern
#endif


#include "datatype.h"


#define ENABLE_SW_SPI           1

#define ENABLE_DEBUG_SW_SPI     (ENABLE_SW_SPI&&0)

//#define SW_SPI_USE_MSPI1        1

#define SPI_WRITE_BUF_SIZE      64

#if (ENABLE_SSPI_DRIVER)
#define SSPI_INVAILD_PORT_NUM   0xFF
#if 0//(CustomerType==CustomerType_INX_Ubike)
#define SSPI_PORT_NUM 3
#define SSPI_ACCEPT_DATA 4       //it can catch 256 byte one time
#else
#define SSPI_PORT_NUM 0
#define SSPI_ACCEPT_DATA 4       //it can catch 256 byte one time
#endif
#endif


//#define MSPI_PORT_NUM 1 // Current used MSPI port 0~3
#define MSPI_PORT_NUM   LD_SPI_PORT


#define REG_MSPI__WRITE_BUF_START   (0x80)
#define REG_MSPI__READ_BUF_START    (0x88)
#define REG_MSPI__WRITE_BUF_SIZE    (0x90)
#define REG_MSPI__READ_BUF_SIZE     (0x91)
#define REG_MSPI__CTRL              (0x92)
#define REG_MSPI__CLOCK_RATE        (0x93)
#define REG_MSPI__TIME_TR_START     (0x94) // The time from "reg_mspi_trigger" to first SPI clock
#define REG_MSPI__TIME_TR_END       (0x95) // The time from last SPI clock to "reg_mspi_done_flag"
#define REG_MSPI__TIME_B_TO_B       (0x96) // The time between byte to byte transfer
#define REG_MSPI__TIME_W_TO_R       (0x97) // The time between last write and first read,
#define REG_MSPI__WRITE_BUF_BIT_LEN (0x98) // Bit Length selection for write buffer0 1
#define REG_MSPI__READ_BUF_BIT_LEN  (0x9C) // Bit Length selection for write buffer0 1
#define REG_MSPI__TRIGGER_TRANSFER  (0xB4) // trigger starting data transfer
#define REG_MSPI__DONE_FLAG         (0xB6) // transfer status
#define REG_MSPI__CLEAR_DONE        (0xB8) // clear done status
#define REG_MSPI__CHIP_SELECT       (0xBE) // reg_chip_select 1~8


#define MASK_MSPI_CTRL__EN_MSPI         _BIT0
#define MASK_MSPI_CTRL__NOT_RESET       _BIT1
#define MASK_MSPI_CTRL__EN_MSPI_INT     _BIT2
#define MASK_MSPI_CTRL__EN_3_WIRE_MODE  _BIT4
#define MASK_MSPI_CTRL__CLOCK_PHASE     _BIT6
#define MASK_MSPI_CTRL__CLOCK_POLARITY  _BIT7

#define MSPI_SEND_BYTES                 2// 1~2 BYTES
//#define MSPI_SEND_BITS                  0x05//0x07 //BITS



typedef enum
{
    E_SPI_STATE__NONE,
    E_SPI_STATE__W_WAIT_VSYNC_INT, // For write first byte
    E_SPI_STATE__W_WAIT_MSPI_INT, // For write other byte

} EnuSpiState;


typedef enum
{
    E_SPI_TRIGGER_NONE,
    E_SPI_TRIGGER_BY_ONE_TIME,
    E_SPI_TRIGGER_BY_V_SYNC,
    E_SPI_TRIGGER_BY_EVERY_V_SYNC,
} EnuSpiTriggerMode;


#define MSPI_INTERNAL_CLOCK 27000000
// When mspi_internal_clk=27M
// DIV_2   = 0.074us
// DIV_4   = 0.148us
// DIV_8   = 0.296us
// DIV_16  = 0.592us
// DIV_32  = 1.185us
// DIV_64  = 2.370us
// DIV_128 = 4.740us
// DIV_256 = 9.481us

typedef enum
{
    MSPI_CLK_SPD__DIV_2=0, // mspi_internal_clk/2
    MSPI_CLK_SPD__DIV_4, // mspi_internal_clk/4
    MSPI_CLK_SPD__DIV_8, // mspi_internal_clk/8
    MSPI_CLK_SPD__DIV_16, // mspi_internal_clk/16
    MSPI_CLK_SPD__DIV_32, // mspi_internal_clk/32
    MSPI_CLK_SPD__DIV_64, // mspi_internal_clk/64
    MSPI_CLK_SPD__DIV_128, // mspi_internal_clk/128
    MSPI_CLK_SPD__DIV_256, // mspi_internal_clk/256
}EnuMSPI_CLOCK_DIV;

typedef enum
{
#if(CHIP_FAMILY_MAYA==CHIP_FAMILY_TYPE)
    MSPI_CLK_SPD_27M=0x0,//27 MHz
    MSPI_CLK_SPD_48M=0x1,//27 MHz
    MSPI_CLK_SPD_62M=0x2,//43.2 MHz
    MSPI_CLK_SPD_72M=0x3,
    MSPI_CLK_SPD_86M=0x4,//86Mhz
    MSPI_CLK_SPD_108M=0x5,
    MSPI_CLK_SPD_123M=0x6,
    MSPI_CLK_SPD_160M=0x7,
#else
    MSPI_CLK_SPD_24M=0,// cystal 24Mhz
    MSPI_CLK_SPD_27M=0x9,//27 MHz
    MSPI_CLK_SPD_36M=0xA,
    MSPI_CLK_SPD_43M=0xB,//43.2 MHz
    MSPI_CLK_SPD_54M=0xC,
    MSPI_CLK_SPD_86M=0xE,//86Mhz
#endif
    MSPI_CLK_SPD_CRYSTAL=0xFF,
}EnuMSPI_CLOCK_GEN; // 1E98[2:5] ; bit5=0 is crystal,bit5=1 decide by bit2~4


typedef struct
{
    EnuMSPI_CLOCK_GEN eMSPIClockGen;
    EnuMSPI_CLOCK_DIV eMSPIClockDiv;

    U8 u8SpiOutputDataBit; // 8 or 10 or 16
    U8 u8ClockPolarity; // 0 or 1
    U8 u8ClockPhase;    // 0 or 1

    U8 u8Time_FromTriggerToFirstClock;  // The time from "reg_mspi_trigger" to first SPI clock.     0 => Delay 1 MSPI clock
    U8 u8Time_LastClockToDone;    // The time from last SPI clock to "reg_mspi_done_flag"     0 => Delay 1 MSPI clock
    U8 u8Time_BetweenByteToByte;  // The time between byte to byte transfer       0 => Delay 0 MSPI clock
    U8 u8Time_FromWriteToRead;    // The time between last write and first read   0 => Delay 0 MSPI clock

} StuMSPICtrlInfo;


#if(ENABLE_DEBUG_SW_SPI)
_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_VS_IntCnt;

_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_VS_Int_t1;
_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_VS_Int_t2;

_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_MSPI_IntCnt;
_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_MSPI_IntCnt_Err;

_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_MSPI_Int_t;
_MDRV_MSPI_DEC_ U32 g_u32DrvSPI_Debug_Int_t[SPI_WRITE_BUF_SIZE];
#endif



U32 MHal_MSPI_Clk_To_Period_Us_X1000(EnuMSPI_CLOCK_DIV eMSPIClk );

//void MHal_MSPI_SetClockSpeed( EnuMSPI_CLOCK_SPEED eClockSpeed );
void MHal_MSPI_SetClockDiv( EnuMSPI_CLOCK_DIV eClockDiv );
void MHal_MSPI_SetClockGen( EnuMSPI_CLOCK_GEN eClockGen );
void MHal_MSPI_SetClockPolarity( U8 u8ClockPolarity );
void MHal_MSPI_SetClockPhase( U8 u8ClockPhase );

void MHal_MSPI_SetTime_TriggerToFirstClock(U8 u8Time );
void MHal_MSPI_SetTime_LastClockToDone(U8 u8Time );
void _MHAL_MSPI_SendOneByte( U8 u8DelayTime, U8 u8Data, U8 u8BitLen );
void _MDrv_SPI_SetWriteBuf_User( U8 au8Buf[], U16 u8BufLen );
void _MDrv_SPI_CopyUserWriteBufToRealWriteBuf(void);
BOOL MDrv_SPI_Init(BOOL bForce ,StuMSPICtrlInfo MSPICtrlInfo) ;
void MDrv_SPI_ISR_Vsync(void);
void MDrv_SPI_ISR(void);
void MDrv_SPI_Stop(void);
//void MDrv_SPI_SetCheckSumMode(U8 u8CheckSumMode);
BOOL MDrv_SPI_SetWriteBuf_Delay( U8 au8Buf_Delay[], U16 u8BufLen );

BOOL MDrv_SPI_WriteBytes( U8 au8Buf[], U16 u8BufLen, EnuSpiTriggerMode eSpiTriggerMode );
BOOL MDrv_SPI_ReadBytes( U8 au8Buf[], U8 u8WriteBufLen,U8 u8ReadBufLen, EnuSpiTriggerMode eSpiTriggerMode );
void MDrv_SPI_UpdateWriteBuf(U8 au8Buf[], U8 u8BufLen);
BOOL MDrv_SPI_SetTriggerMode(EnuSpiTriggerMode eSpiTriggerMode);
BOOL MDrv_SPI_Test4(U8 au8Buf [ ], U8 u8BufLen, EnuSpiTriggerMode eSpiTriggerMode);
void MDrv_SPI_Test5(void);
U8 MDrv_SPI_GetState(void);
U8 MDrv_SPI_GetTriggerMode(void);

void MDrv_SPI_VSyncLikeInit(void);
void MDrv_SPI_SttInit(void);
void MDrv_SPI_Test1(void);
void MDrv_SPI_Test2(void);
void MDrv_SPI_Test3(U8 test1,U8 test2);
void MDrv_SPI_Test6( U8 au8Buf[]);
void MDrv_SPI_Test7( U16 au8SPI_Write_BufSize,U8 au8SPI_Write_Data);
void MDrv_SPI_PrintDebugInfo(void);

#if (ENABLE_SSPI_DRIVER)
_MDRV_MSPI_DEC_ U8 g_u8SSPI_Data_Buf[SSPI_ACCEPT_DATA];  //LD_SSPI return Data

void MDrv_SPI_SSPI_Init(void);
void MDrv_SPI_SSPI_Enable(BOOL bEnable);
void MDrv_SPI_SSPI_Port_Sel(U8 u8SSPI_Port);
U16 MDrv_SPI_SSPI_Get_FIFO_Rec_Data_Number(void);
void MDrv_SPI_SSPI_Data_Rec_ISR(void);

/*
BOOL MDrv_SPI_GetSSPIDataArray(U8* gu8SSPI_Data, U8 u8arraysize);
U8 MDrv_SPI_GetSSPIDataSize(void);
BOOL MDrv_SPI_GetSSIP_Status(void);
void MDrv_SPI_Set_SSIP_Status(BOOL bIsFinished);
*/
#endif

void MDrv_MSPI_Set_ChipSelect(BOOLEAN bHigh);

#endif

