////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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
#define _IIC_C_

#include "Board.h"
#include "hwreg.h"
#include "datatype.h"
#include "GPIO_macro.h"
#include "drvIIC.h"
#include "MsIRQ.h"
#include "MsOS.h"

#if (USE_SW_I2C_HIGHSPEED==1)
#if defined (MSOS_TYPE_NOS)
//extern void mhal_interrupt_lock(void);
//extern void mhal_interrupt_unlock(void);
#define DRV_SWI2C_InitLock()
#define DRV_SWI2C_InitLock()
#define DRV_SWI2C_Lock()
#define DRV_SWI2C_UnLock()
#else
static MS_S32 u32Mutex_SWI2C;
#define DRV_SWI2C_InitLock()    {\
                                    u32Mutex_SWI2C = OS_CREATE_MUTEX(SWI2C);\
                                    if(u32Mutex_SWI2C<0)\
                                    {\
                                        SWI2C_DEBUGINFO(printf("!!!Acquire Send Mutex for SWI2C Failed!\n"));\
                                    }\
                                }
#define DRV_SWI2C_DeInitLock()  OS_DELETE_MUTEX(u32Mutex_SWI2C)
#define DRV_SWI2C_Lock()        {\
                                    OS_OBTAIN_MUTEX(u32Mutex_SWI2C, MSOS_WAIT_FOREVER);\
                                    OS_ENTER_CRITICAL();\
                                }
#define DRV_SWI2C_UnLock()      {\
                                    OS_EXIT_CRITICAL(); \
                                    OS_RELEASE_MUTEX(u32Mutex_SWI2C);\
                                }
#endif
#endif


#ifndef EEPROM512_WP_ENABLE
    #define EEPROM512_WP_ENABLE 0
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif
#ifndef BOOL
#define BOOL unsigned char
#endif

//                         SCL              SDA             SPEED

//Melody: 128 pin
#if ( (MS_BOARD_TYPE_SEL == BD_MST242B_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST096B_10ARU_15384) || (MS_BOARD_TYPE_SEL == BD_MST106B_10ARU_16115_ISDB_MELODY))
    #define MIIC_BUS_SYS    PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCA0  PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCD0  PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_ISP  PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_200K  //wuhui

//Melody: 156 pin
#elif ( (MS_BOARD_TYPE_SEL == BD_MST242C_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST097B_10ARB_15384))
    #define MIIC_BUS_SYS    PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCA0  PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCD0  PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_ISP  PAD_GPIO1,  PAD_GPIO0,  I2C_SPEED_MAPPING_200K

//Melody: 80 pin
#elif ((MS_BOARD_TYPE_SEL == BD_MST242A_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST094B_10ARJ_15374))
    #define MIIC_BUS_SYS    PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCA0  PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCD0  PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_ISP  PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_200K

//Melody: 80 pin
#elif ((MS_BOARD_TYPE_SEL == BD_MST242D_D01A_S) || (MS_BOARD_TYPE_SEL == BD_MST094B_20ARJ_16234))
    #define MIIC_BUS_SYS    PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCA0  PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_DDCD0  PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_100K
    #define MIIC_BUS_ISP  PAD_TCON1,  PAD_TCON2,  I2C_SPEED_MAPPING_200K

#else
    #error "board type incorrect\n"
#endif


#if (USE_SW_I2C_HIGHSPEED==1)
#define REG_OEN(pad)                CONCAT(GPIO_NUM(pad),_OEN)
#define REG_OUT(pad)                CONCAT(GPIO_NUM(pad),_OUT)
#define REG_IN(pad)                 CONCAT(GPIO_NUM(pad),_IN)
#define _I2C_PAD(pad)               REG_OEN(pad), REG_OUT(pad), REG_IN(pad)
#define _I2C_BUS(scl, sda, dly)     _I2C_PAD(scl), _I2C_PAD(sda), dly
#define I2C_BUS(bus)                _I2C_BUS(bus)
typedef struct {
    U32 SclOenReg; U8  SclOenBit;   U32 SclOutReg; U8  SclOutBit;   U32 SclInReg;U8  SclInBit;
    U32 SdaOenReg; U8  SdaOenBit;   U32 SdaOutReg; U8  SdaOutBit;   U32 SdaInReg;U8  SdaInBit;
    U8  defDelay;
} I2C_Bus;
#else
#define __I2C_BUS(scl, sda, dly)    scl, sda, dly
#define I2C_BUS( bus )      __I2C_BUS( bus )
typedef struct
{
    U16 padSCL;
    U16 padSDA;
    U16 defDelay;
} I2C_Bus;
#endif


I2C_Bus g_I2CBus[] =
{
    { I2C_BUS( MIIC_BUS_SYS ) },
    { I2C_BUS( MIIC_BUS_DDCA0 ) },
    { I2C_BUS( MIIC_BUS_DDCD0 ) },
    { I2C_BUS( MIIC_BUS_ISP ) },
};
SWI2C_BusCfg g_I2CBus_Temp[] =
{
    {MIIC_BUS_SYS},
    {MIIC_BUS_DDCA0},
    {MIIC_BUS_DDCD0},
    {MIIC_BUS_ISP},
};

static U8 u8BusSel = 0;

#define SWIIC_READ      0
#define SWIIC_WRITE     1

#define I2C_CHECK_PIN_DUMMY     100
#define I2C_ACKNOWLEDGE         _LOW
#define I2C_NON_ACKNOWLEDGE     _HIGH
#define I2C_ACCESS_DUMMY_TIME   3

#define HIBYTE(value)  ((BYTE)((value) / 0x100))
#define LOBYTE(value)  ((BYTE)(value))

#define SLAVE_ADDR_24C512   0xA0

#define SWI2C_DEBUGINFO(x)  //x

U32 SwIicDly=I2C_SPEED_MAPPING_100K;

/******************************************************************************/
#if 1
static void iic_delay(void)
{
    MS_U32 volatile u32Loop=SwIicDly;

    while(u32Loop--)
    {
        #ifdef __mips__
        __asm__ __volatile__ ("nop");
        #endif

        #ifdef __AEONR2__
        __asm__ __volatile__ ("l.nop");
        #endif

        #ifdef __arm__
        __asm__ __volatile__ ("mov r0, r0");
        #endif
    }
}
#else
static void iic_delay(void)
{
    // volatile is necessary to avoid optimization
    U32 volatile u32Dummy = 0;
    U32 u32Loop;

    u32Loop = SwIicDly;
    while (u32Loop-- > 0)
    {
        u32Dummy++;
    }
}
#endif
/******************************************************************************/

void IIC_UseBus( U8 u8BusChn )
{
    if ( u8BusChn < COUNTOF( g_I2CBus ) )
    {
        u8BusSel = u8BusChn;
        SwIicDly = g_I2CBus[u8BusSel].defDelay;
        switch ( u8BusChn )
        {
        case E_I2C_BUS_DDCA0:
            //GPIO_DDCA0_ENABLE(1);
            break;
        case E_I2C_BUS_DDCD0:
            //   GPIO_DDCD0_ENABLE(1);
            break;
        //case E_I2C_BUS_DDCD1:
            //   GPIO_DDCD1_ENABLE(1);
            //break;
        //case E_I2C_BUS_DDCD2:
            // GPIO_DDCD2_ENABLE(1);
            //break;
        default:
            break;
        }
    }
}


U32 MDrv_IIC_Speed_Setting(U8 u8BusNum, U32 u32Speed_K)
{
    U32 u32OriginalValue;

    u32OriginalValue = g_I2CBus[u8BusNum].defDelay;
    g_I2CBus[u8BusNum].defDelay = u32Speed_K;
    IIC_UseBus(u8BusNum);

    return u32OriginalValue;

}


void IIC_UnuseBus( void )
{
    switch ( u8BusSel )
    {
    case E_I2C_BUS_DDCA0:
        //GPIO_DDCA0_ENABLE(0);
        break;
    case E_I2C_BUS_DDCD0:
        //GPIO_DDCD0_ENABLE(0);
        break;
    case E_I2C_BUS_DDCD1:
        //GPIO_DDCD1_ENABLE(0);
        break;
    case E_I2C_BUS_DDCD2:
        //GPIO_DDCD2_ENABLE(0);
        break;
    default:
        break;
    }
}

#if (USE_SW_I2C_HIGHSPEED==1)
#define SclOenReg               g_I2CBus[u8BusSel].SclOenReg
#define SclOenBit               g_I2CBus[u8BusSel].SclOenBit
#define SclOutReg               g_I2CBus[u8BusSel].SclOutReg
#define SclOutBit               g_I2CBus[u8BusSel].SclOutBit
#define SclInReg                g_I2CBus[u8BusSel].SclInReg
#define SclInBit                g_I2CBus[u8BusSel].SclInBit
#define pin_scl_set_input()     MDrv_WriteRegBit(SclOenReg,1,SclOenBit)
#define pin_scl_set_high()      MDrv_WriteRegBit(SclOenReg,1,SclOenBit)
#define pin_scl_set_low()       MDrv_WriteRegBit(SclOenReg,0,SclOenBit); MDrv_WriteRegBit(SclOutReg,0,SclOutBit)
#define pin_scl_get_level()     ((MDrv_ReadRegBit(SclInReg,SclInBit)!=0)? _HIGH : _LOW)
#else
static void pin_scl_set_input(void)
{
    mdrv_gpio_set_input( g_I2CBus[u8BusSel].padSCL );
}
static void pin_scl_set_high(void)
{
     //mdrv_gpio_set_high( g_I2CBus[u8BusSel].padSCL );
     mdrv_gpio_set_input( g_I2CBus[u8BusSel].padSCL );
}
static void pin_scl_set_low(void)
{
    mdrv_gpio_set_low( g_I2CBus[u8BusSel].padSCL );
}

static int pin_scl_get_level(void)
{
    return mdrv_gpio_get_level( g_I2CBus[u8BusSel].padSCL ) ? _HIGH : _LOW;
}
#endif

static void pin_scl_check_high(void)
{
    U8 u8Dummy;

    pin_scl_set_high();
    u8Dummy = I2C_CHECK_PIN_DUMMY;
    while ((pin_scl_get_level() == _LOW) && (u8Dummy--));
}

#if (USE_SW_I2C_HIGHSPEED==1)
#define SdaOenReg               g_I2CBus[u8BusSel].SdaOenReg
#define SdaOenBit               g_I2CBus[u8BusSel].SdaOenBit
#define SdaOutReg               g_I2CBus[u8BusSel].SdaOutReg
#define SdaOutBit               g_I2CBus[u8BusSel].SdaOutBit
#define SdaInReg                g_I2CBus[u8BusSel].SdaInReg
#define SdaInBit                g_I2CBus[u8BusSel].SdaInBit
#define pin_sda_set_input()     MDrv_WriteRegBit(SdaOenReg,1,SdaOenBit)
#define pin_sda_set_high()      MDrv_WriteRegBit(SdaOenReg,1,SdaOenBit)
#define pin_sda_set_low()       MDrv_WriteRegBit(SdaOenReg,0,SdaOenBit); MDrv_WriteRegBit(SdaOutReg,0,SdaOutBit)
#define pin_sda_get_level()     ((MDrv_ReadRegBit(SdaInReg,SdaInBit)!=0)? _HIGH : _LOW)
#else
static void pin_sda_set_input(void)
{
    mdrv_gpio_set_input( g_I2CBus[u8BusSel].padSDA );
}
static void pin_sda_set_high(void)
{
  //  mdrv_gpio_set_high( g_I2CBus[u8BusSel].padSDA );
    mdrv_gpio_set_input( g_I2CBus[u8BusSel].padSDA );
}
static void pin_sda_set_low(void)
{
    mdrv_gpio_set_low( g_I2CBus[u8BusSel].padSDA );
}

static int pin_sda_get_level(void)
{
    return mdrv_gpio_get_level( g_I2CBus[u8BusSel].padSDA ) ? _HIGH : _LOW;
}
#endif

static void pin_sda_check_high(void)
{
    U8 u8Dummy;

    pin_sda_set_high();
    u8Dummy = I2C_CHECK_PIN_DUMMY;
    while ((pin_sda_get_level() == _LOW) && (u8Dummy--));
}

/******************************************************************************/
///I2C Initialize: set I2C Clock and enable I2C
/******************************************************************************/
void MDrv_IIC_Init()
{
    U8 u8Counter;

    // if SDA:H & SCL:H return
    // else initialize i2c (generate 9 clock SCL)
    // check SCK:H SDA:H

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_InitLock();
#endif

    pin_scl_set_input();
    pin_sda_set_input();
    iic_delay();
    if (pin_sda_get_level() == _LOW
     || pin_scl_get_level() == _LOW)
    {
        // initialization of I2C BUS.
        // generate 9 clocks of SCL line before using I2C BUS.
        // If a device holds SDA line and it is freed after
        // receiving 9 clocks of SCL at least.

        for (u8Counter = 0; u8Counter < 9; u8Counter++)
        {
            pin_scl_check_high();
            iic_delay();
            pin_scl_set_low();
            iic_delay();
        }
        pin_scl_check_high();

        if (pin_sda_get_level() == _LOW
         || pin_scl_get_level() == _LOW)
        {
            printf("IIC init fail SDA:%x SCL:%x\n", pin_sda_get_level(), pin_scl_get_level());
        }
    }
    MApi_SWI2C_Init(g_I2CBus_Temp, sizeof(g_I2CBus_Temp)/sizeof(SWI2C_BusCfg));

}

/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
// I2C start signal.
// <comment>
//  SCL ________
//              \_________
//  SDA _____
//           \____________
//
// Return value: None
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
BOOL IIC_Start(void)
{
    BOOL bStatus = TRUE;    // success status

    pin_sda_check_high();
    iic_delay();

    pin_scl_check_high();
    iic_delay();

    // check pin error
    pin_scl_set_input();
    pin_sda_set_input();

    if ((pin_scl_get_level() == _LOW) || (pin_sda_get_level() == _LOW))
    {
        pin_scl_set_high();
        pin_sda_set_high();
        bStatus = FALSE;
    }
    else // success
    {
        pin_sda_set_low();
        iic_delay();
        pin_scl_set_low();
    }

    return bStatus;     //vain
}

////////////////////////////////////////////////////////////////////////////////
// I2C stop signal.
// <comment>
//              ____________
//  SCL _______/
//                 _________
//  SDA __________/
////////////////////////////////////////////////////////////////////////////////
void IIC_Stop(void)
{
    pin_scl_set_low();
    iic_delay();
    pin_sda_set_low();

    iic_delay();
    pin_scl_set_input();
    iic_delay();
    pin_sda_set_input();
    iic_delay();
}

/******************************************************************************/
///Send 1 bytes data
///@param u8dat \b IN: 1 byte data to send
/******************************************************************************/
static BOOLEAN SendByte(U8 u8dat)   // Be used int IIC_SendByte
{
    U8    u8Mask = 0x80;
    bit   bAck; // acknowledge bit

    while ( u8Mask )
    {
        if (u8dat & u8Mask)
        {
            pin_sda_check_high();
        }
        else
        {
            pin_sda_set_low();
        }

        iic_delay();
        pin_scl_check_high();
        iic_delay();
        pin_scl_set_low();

        u8Mask >>= 1; // next
    }

    // recieve acknowledge
    pin_sda_set_input();
    iic_delay();
    pin_scl_check_high();

    iic_delay();
    bAck = pin_sda_get_level(); // recieve acknowlege
    pin_scl_set_low();

    iic_delay();

    //for I2c waveform sharp
    if (bAck)
        pin_sda_set_high();
    else
        pin_sda_set_low();

    pin_sda_set_input();

    iic_delay();
    iic_delay();
    iic_delay();
    iic_delay();

    return (bAck);
}

/******************************************************************************/
///Send 1 bytes data, this function will retry 5 times until success.
///@param u8dat \b IN: 1 byte data to send
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
BOOLEAN IIC_SendByte(U8 u8dat)
{
    U8 i;

    for(i=0;i<5;i++)
    {
        if (SendByte(u8dat)==I2C_ACKNOWLEDGE)
            return TRUE;
    }

    SWI2C_DEBUGINFO(printf("IIC write byte 0x%bx fail!!\n", u8dat));
    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// I2C access start.
//
// Arguments: u8SlaveID - Slave ID (Address)
//            trans_t - I2C_TRANS_WRITE/I2C_TRANS_READ
////////////////////////////////////////////////////////////////////////////////
BOOL IIC_AccessStart(U8 u8SlaveID, U8 trans_t)
{
    U8 u8Dummy; // loop dummy

    if (trans_t == SWIIC_READ) // check i2c read or write
    {
        u8SlaveID |= BIT0;
    }
    else
    {
        u8SlaveID &= ~BIT0;
    }

    u8Dummy = I2C_ACCESS_DUMMY_TIME;

    while (u8Dummy--)
    {
        if ( IIC_Start() == FALSE)
        {
            continue;
        }

        if ( IIC_SendByte(u8SlaveID) == TRUE )  // check acknowledge
        {
            return TRUE;
        }

        IIC_Stop();
    }

    return FALSE;
}
/******************************************************************************/
///Get 1 bytes data, this function will retry 5 times until success.
///@param *u8dat \b IN: pointer to 1 byte data buffer for getting data
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************///
//static BOOLEAN IIC_GetByte(U8* pu8data)    // Auto generate ACK
BYTE IIC_GetByte (U16  bAck)
{
    BYTE ucReceive = 0;
    BYTE ucMask = 0x80;

    pin_sda_set_input();

    while ( ucMask )
    {
        iic_delay();
        pin_scl_check_high();
        iic_delay();

        if (pin_sda_get_level() == _HIGH)
        {
            ucReceive |= ucMask;
        }
        ucMask >>= 1; // next

        pin_scl_set_low();
    }
    if (bAck)
    {
        pin_sda_set_low();     // acknowledge
    }
    else
    {
        pin_sda_check_high();  // non-acknowledge
    }
    iic_delay();
    pin_scl_check_high();
    iic_delay();
    pin_scl_set_low();
    iic_delay();
    iic_delay();
    iic_delay();
    return ucReceive;
}

/******************************************************************************/
///Write bytes, be able to write 1 byte or several bytes to several register offsets in same slave address.
///@param u16BusNumSlaveID \b IN: Bus Number (high byte) and Slave ID (Address) (low byte)
///@param u8addrcount \b IN:  register NO to write, this parameter is the NO of register offsets in pu8addr buffer,
///it should be 0 when *pu8addr = NULL.
///@param *pu8addr \b IN: pointer to a buffer containing target register offsets to write
///@param u16size \b IN: Data length (in byte) to write
///@param *pu8data \b IN: pointer to the data buffer for write
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
BOOLEAN MDrv_IIC_WriteBytes(U16 u16BusNumSlaveID, U8 AddrCnt, U8* pu8addr, U16 u16size, U8* pBuf)
{
    U8 u8Dummy; // loop dummy
    BOOLEAN bRet;

    
    printf("\r\nID = %x",u16BusNumSlaveID);
    printf("\r\nADDR CNT = %x", AddrCnt);
    printf("\r\nADDR = %x",*pu8addr);
    printf("\r\nSIZE = %x", u16size);
    for (u8Dummy = 0;u8Dummy< u16size; u8Dummy++)
        printf("\r\nDATE%d = %x",u8Dummy,*(pBuf+u8Dummy));

    u8Dummy = 1;  //I2C_ACCESS_DUMMY_TIME;
    bRet = FALSE;

    #if 0//( EEPROM512_WP_ENABLE    ==1 )
        if ( ((U8) u16BusNumSlaveID) == 0xA0 )
            EEPROM512_WP_OFF();
    #endif

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_Lock();
#endif

    IIC_UseBus(HIBYTE(u16BusNumSlaveID));

    while (u8Dummy--)
    {
        if (IIC_AccessStart(LOBYTE(u16BusNumSlaveID), SWIIC_WRITE) == FALSE)
        {
        	printf("\r\nwrite i2c addr %x can't access", u16BusNumSlaveID);
            if( u8Dummy )
                continue;
            else
                goto fail;
        }

        while (AddrCnt)
        {
            AddrCnt--;
            if (IIC_SendByte(*pu8addr) == FALSE)
            {
                goto fail;
            }
            pu8addr++;
        }
        while (u16size) // loop of writting data
        {
            u16size-- ;
            if (IIC_SendByte(*pBuf) == FALSE)
            {
                goto fail;
            }
            pBuf++; // next byte pointer
        }

        break;
    }
    bRet = TRUE;

fail:

    IIC_Stop();
    #if 0// ( EEPROM512_WP_ENABLE  == 1 )
        EEPROM512_WP_ON();
    #endif

    IIC_UnuseBus();

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_UnLock();
#endif

    return bRet;
}


 /******************************************************************************/
///Read bytes, be able to read 1 byte or several bytes from several register offsets in same slave address.
///@param u16BusNumSlaveID \b IN: Bus Number (high byte) and Slave ID (Address) (low byte)
///@param u8AddrNum \b IN:  register NO to read, this parameter is the NO of register offsets in pu8addr buffer,
///it should be 0 when *paddr = NULL.
///@param *paddr \b IN: pointer to a buffer containing target register offsets to read
///@param u16size \b IN: Data length (in byte) to read
///@param *pu8data \b IN: pointer to retun data buffer.
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
BOOLEAN MDrv_IIC_ReadBytes(U16 u16BusNumSlaveID, U8 ucSubAdr, U8* paddr, U16 ucBufLen, U8* pBuf)
{
    U8 u8Dummy; // loop dummy
    BOOLEAN bRet;

    u8Dummy = I2C_ACCESS_DUMMY_TIME;
    bRet = FALSE;

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_Lock();
#endif

    IIC_UseBus(HIBYTE(u16BusNumSlaveID));

    while (u8Dummy--)
    {
        if (IIC_AccessStart(LOBYTE(u16BusNumSlaveID), SWIIC_WRITE) == FALSE)
        {
            if( u8Dummy )
                continue;
            else
                goto fail;
        }

        while (ucSubAdr)
        {
            ucSubAdr--;
            if (IIC_SendByte(*paddr) == FALSE)
            {
                goto fail;
            }
            paddr++;
        }
        if (IIC_AccessStart(LOBYTE(u16BusNumSlaveID), SWIIC_READ) == FALSE)
        {
            continue;
        }

        while (ucBufLen--) // loop to burst read
        {
            *pBuf = IIC_GetByte(ucBufLen); // receive byte
            pBuf++; // next byte pointer
        }

        break;
    }
    bRet = TRUE;

fail:

    IIC_Stop();

    IIC_UnuseBus();

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_UnLock();
#endif

    return bRet;
}

/******************************************************************************/
///Read 1 byte through IIC
///@param u16BusNumSlaveID \b IN: Bus Number (high byte) and Slave ID (Address) (low byte)
///@param u8RegAddr \b IN: Target register offset to read
///@param *pu8Data \b IN: pointer to 1 byte return data.
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
BOOLEAN MDrv_IIC_ReadByte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 *pu8Data)
{
    BOOLEAN Result;
    Result=MDrv_IIC_ReadBytes(u16BusNumSlaveID, 1, &u8RegAddr,1, pu8Data);
    return Result;
}

/******************************************************************************/
///Write 1 byte through IIC
///@param u16BusNumSlaveID \b IN: Bus Number (high byte) and Slave ID (Address) (low byte)
///@param u8RegAddr \b IN: Target register offset to write
///@param u8Data \b IN: 1 byte data to write
///@return BOOLEAN:
///- TRUE: Success
///- FALSE: Fail
/******************************************************************************/
BOOLEAN MDrv_IIC_WriteByte(U16 u16BusNumSlaveID, U8 u8RegAddr, U8 u8Data)
{
    return( MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &u8RegAddr, 1, &u8Data) );
}
//------------------------------------------------------------------------
BOOLEAN MDrv_IIC_Write2Bytes(U16 u16BusNumSlaveID, U8 u8addr, U16 u16data)
{
    U8 u8Data[2];
    u8Data[0] = (u16data>>8) & 0xFF;
    u8Data[1] = (u16data) & 0xFF;
    return (MDrv_IIC_WriteBytes(u16BusNumSlaveID, 1, &u8addr, 2, u8Data));
}

U16 MDrv_IIC_Read2Bytes(U16 u16BusNumSlaveID, U8 u8addr)
{
    U8 u8Data[2]= {0};
    MDrv_IIC_ReadBytes(u16BusNumSlaveID, 1, &u8addr, 2, u8Data);

    return ( (((U16)u8Data[0])<<8)|u8Data[1] );
}

BOOLEAN MDrv_IIC_WriteByteDirectly(U16 u16BusNumSlaveID, U8 u8Data)
{
    BOOLEAN bRet;

    bRet = FALSE;

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_Lock();
#endif

    IIC_UseBus(HIBYTE(u16BusNumSlaveID));

    IIC_Start();

    if (IIC_SendByte(LOBYTE(u16BusNumSlaveID) & ~BIT0) == FALSE)
        goto fail;

    if (IIC_SendByte(u8Data)==FALSE)
        goto fail;

    bRet = TRUE;
fail:
    IIC_Stop();
    IIC_UnuseBus();

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_UnLock();
#endif

    return bRet;
}


BOOLEAN MDrv_IIC_Write4Bytes(U16 u16BusNumSlaveID, U32 u32Data, U8 u8EndData)
{
    BOOLEAN bRet;

    bRet = FALSE;

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_Lock();
#endif

    IIC_UseBus(HIBYTE(u16BusNumSlaveID));
    IIC_Start();

    if(IIC_SendByte( LOBYTE(u16BusNumSlaveID) & ~BIT0 )==FALSE)
        goto fail;

    if(IIC_SendByte( (U8)(((U32)u32Data)>>24) ) == FALSE )
        goto fail;

    if(IIC_SendByte( (U8)(((U32)u32Data)>>16) ) == FALSE )
        goto fail;

    if(IIC_SendByte( (U8)(((U32)u32Data)>>8) ) == FALSE )
        goto fail;

    if(IIC_SendByte( (U8)(((U32)u32Data)>>0) ) == FALSE )
        goto fail;

    if(IIC_SendByte(u8EndData)==FALSE)
        goto fail;

    bRet = TRUE;
fail:
    IIC_Stop();
    IIC_UnuseBus();

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_UnLock();
#endif

    return bRet;
}

BOOLEAN MDrv_IIC_WriteGroupBytes(U16 u16BusNumSlaveID, U8 u8SubGroup, U16 u16Addr, U16 u16Data)
{
    BOOLEAN bRet;

    bRet = FALSE;

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_Lock();
#endif

    IIC_UseBus(HIBYTE(u16BusNumSlaveID));
    IIC_Start();

    if(IIC_SendByte( LOBYTE(u16BusNumSlaveID) & ~BIT0 )==FALSE)
        goto fail;

    if(IIC_SendByte(u8SubGroup)==FALSE)
        goto fail;

    if(IIC_SendByte((u16Addr>>8)&0xFF)==FALSE)
        goto fail;

    if(IIC_SendByte(u16Addr&0xFF)==FALSE)
        goto fail;

    if(IIC_SendByte((u16Data>>8)&0xFF)==FALSE)
        goto fail;

    if(IIC_SendByte(u16Data&0xFF)==FALSE)
        goto fail;

    bRet = TRUE;
fail:
    IIC_Stop();
    IIC_UnuseBus();

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_UnLock();
#endif

    return bRet;
}

U16 MDrv_IIC_ReadGroupBytes(U16 u16BusNumSlaveID, U8 u8SubGroup, U16 u16Addr)
{
    U16 u16Data = 0;
    U8 u8Address[3];

    u8Address[0] = u8SubGroup;
    u8Address[1] = (u16Addr>>8)&0xFF;
    u8Address[2] = u16Addr&0xFF;

    MDrv_IIC_ReadBytes(u16BusNumSlaveID, 3, u8Address, 2, (U8 *)&u16Data);

    return u16Data;
}

bool I2C_Write_Byte(U8 DataByte)
{
	U8 bitcnt;
	bit Status;
	
	for (bitcnt=0; bitcnt<8; bitcnt++)
	{
		if (DataByte&0x80){
			pin_sda_check_high();
		}else{						
			pin_sda_set_low();
		}
		iic_delay();
		pin_scl_check_high();
		iic_delay();
		pin_scl_set_low();
		DataByte <<=1;
	}
	//pin_sda_check_high();
	pin_sda_set_input();
	iic_delay();
	pin_scl_check_high();	
	
	iic_delay();
	Status = pin_sda_get_level();
	pin_scl_set_low();
	
	iic_delay();
	
	if (Status)
        pin_sda_check_high();
    else
        pin_sda_set_low();
	
	pin_sda_set_input();
	
    iic_delay();
    iic_delay();
    iic_delay();
    iic_delay();
	return Status;
}

BOOL I2C_Start (void)
{
	BOOL bStatus = FALSE;
	pin_sda_check_high();
	iic_delay();
	pin_scl_check_high();
	iic_delay();
    pin_sda_set_low();
	iic_delay();
	pin_scl_set_low();
	iic_delay();
	return bStatus;
}
void I2C_Stop (void)
{
	pin_scl_set_low();
	iic_delay();
	pin_sda_set_low();
	iic_delay();
	pin_scl_set_high();
	iic_delay();
    pin_sda_set_high();
	iic_delay();
	iic_delay();
	iic_delay();
}

U8 I2C_Read_Byte(U8 ack)
{
	U8 bitcnt;
	U8 DataByte=0;
	pin_scl_set_low();
	pin_sda_set_high();
	//pin_sda_set_input();

	iic_delay();
	
	for(bitcnt=0; bitcnt<8; bitcnt++)
	{
		DataByte <<= 1;
		pin_scl_check_high();
		if(pin_sda_get_level())		DataByte |= 0x01;
		
		iic_delay();
		pin_scl_set_low();
		iic_delay();
 	}
	
	//switch SDA pin from input to output	
	//pin_sda_set_input();
	iic_delay();
	
	if (ack  == 1){		pin_sda_set_low();
	
	}else{				pin_sda_check_high();}
	
	iic_delay();
	iic_delay();
    iic_delay();
	
	pin_scl_check_high();
	iic_delay();
	iic_delay();
	
	pin_scl_set_low();
	
	return (DataByte);
}

BOOLEAN MDrv_IIC_OPT_ReadBytes(U16 u16BusNumSlaveID, U16 ucBufLen, U8* pBuf)
{
    U8 u8Dummy; // loop dummy
    BOOLEAN bRet;

    u8Dummy = I2C_ACCESS_DUMMY_TIME;
    bRet = FALSE;

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_Lock();
#endif

    IIC_UseBus(HIBYTE(u16BusNumSlaveID));

    while (u8Dummy--)
    {
        if (IIC_AccessStart(LOBYTE(u16BusNumSlaveID), SWIIC_READ) == FALSE)
        {
            continue;
        }

        while (ucBufLen--) // loop to burst read
        {
            *pBuf = IIC_GetByte(ucBufLen); // receive byte
           // printf("optical read data number(%x)is =%x\n",ucBufLen,*pBuf);
            pBuf++; // next byte pointer
            
        }

        break;
    }
    bRet = TRUE;

//fail:

    IIC_Stop();

    IIC_UnuseBus();

#if (USE_SW_I2C_HIGHSPEED==1)
    DRV_SWI2C_UnLock();
#endif

    return bRet;
}

#undef _IIC_C_
