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

#ifndef __UART_H
#define __UART_H

#include "datatype.h"
#include "Board.h"
#include "debug.h"

#define UARTMSG(x)    //x

#define OTHER_TUNER_DEBUG       0   // for MSTV_Tool tuner debug page

#ifdef _DRVUART_C_
#define INTERFACE
#define INITVALUE(v)    = (v)
#else
#define INTERFACE  extern
#define INITVALUE(v)
#endif

#if ( XMODEM_DWNLD_ENABLE )
// XMODEM Definitions
#define XMODSIZE           1024      // size of xmodem buffer
#define XMODEM_STD_SIZE     132      // 128Byte-Data+3Byte-Header+1Byte-Sum
#define XMODEM_1K_SIZE     1029      // 1024Byte-Data+3Byte-Header+2Byte-CRC
// XMODEM Constants
INTERFACE BOOLEAN PingPong;   //PingPong buffer flag
INTERFACE U16 Xmodem_Count;
INTERFACE U8 *dl_XBuf;    // buffer ptr for read data
INTERFACE U8 dl_Buff1[XMODSIZE + 6];    //1st buffer for data
INTERFACE U8 dl_Buff2[XMODSIZE + 6];    //2nd buffer for data
INTERFACE bit XModem_Rx_Timeout;
INTERFACE U32 xPktCnt;
INTERFACE U16 pktsize;     // default packet size is 128 bytes
INTERFACE U16 crcflag;
INTERFACE U8  g_bXmodemDetected;
#endif

INTERFACE bit g_bUart0Detected; // decode command flag
INTERFACE U16 g_Uart0CheckTick;

#if ENABLE_UART1_INTERRUPT

#if(ENABLE_UART1_DEBUG)
#define MAX_UART1_CMD_LENGTH    35
INTERFACE bit g_bUart1Detected; // decode command flag
INTERFACE U16 g_Uart1CheckTick;
INTERFACE U8 g_Uart1CmdBuf[35];
INTERFACE U8 g_ucUart1BufIndex;
INTERFACE bit g_bUartToolSelect;
#endif

#endif

#if (ENABLE_MSTV_UART_DEBUG)

/////////////////////////////////////////////
// Uart command structure
/////////////////////////////////////////////
typedef enum _UartCommadEnumType
{
    _UART_CMD_CODE_,
    _UART_CMD_INDEX1_,
    _UART_CMD_INDEX2_,
    _UART_CMD_INDEX3_,
    _UART_CMD_INDEX4_,
    _UART_CMD_INDEX5_,
    _UART_CMD_INDEX6_,
    _UART_CMD_INDEX7_,
    _UART_CMD_INDEX8_,
    _UART_CMD_INDEX9_,
    _UART_CMD_INDEX10_,
    _UART_CMD_INDEX11_,
    _UART_CMD_INDEX12_,
    _UART_CMD_INDEX13_,
    _UART_CMD_INDEX14_,
    _UART_CMD_INDEX15_,
    _UART_CMD_INDEX16_,
    _UART_CMD_INDEX17_,
    _UART_CMD_INDEX18_,
    _UART_CMD_INDEX19_,
    _UART_CMD_INDEX20_,
#if 1//ENABLE_AUTO_WHITE_BAlANCE
    _UART_CMD_INDEX21_,
    _UART_CMD_INDEX22_,
    _UART_CMD_INDEX23_,
    _UART_CMD_INDEX24_,
    _UART_CMD_INDEX25_,
    _UART_CMD_INDEX26_,
    _UART_CMD_INDEX27_,
    _UART_CMD_INDEX28_,
    _UART_CMD_INDEX29_,
    _UART_CMD_INDEX30_,
    _UART_CMD_INDEX31_,
    _UART_CMD_INDEX32_,
    _UART_CMD_INDEX33_,
    _UART_CMD_INDEX34_,
    _UART_CMD_INDEX35_,
    _UART_CMD_INDEX36_,
    _UART_CMD_INDEX37_,
    _UART_CMD_INDEX38_,
#endif    
    _UART_CMD_LENGTH_
}UartCommadEnumType;

typedef struct _UartCommadType
{
    U8 Buffer[_UART_CMD_LENGTH_];  // command buffer
                                     // [Length+Command] - [Byte 2] - [Byte 3] - [Byte 4] - [Byte 5]
    U8 Index;                     // buffer index

}UartCommadType;

typedef enum
{
    MCU_P0,
    MCU_P1,
    MCU_P2,
    MCU_P3,
    MCU_P4,
    MCU_TCON,
    MCU_TMOD,
    MCU_PCON,
    MCU_IE,
    MCU_IP,
    MCU_SCON
} MCU_Reg;

/////////////////////////////////////////////
// Uart Variables
/////////////////////////////////////////////
INTERFACE bit g_bUartOutput;  // output hexidecimal data flag
INTERFACE bit g_bDebugASCIICommandFlag;
INTERFACE bit g_bDebugProgStopFlag;
#ifdef UI_ENABLE_DEBUG
INTERFACE bit g_bDisableUartDebug INITVALUE(1); // disable uart debug if UI can turn it on
#else
INTERFACE bit g_bDisableUartDebug INITVALUE(0);
#endif
INTERFACE UartCommadType g_UartCommand; // Uart command struct

#if (ENABLE_MMS)
//$
extern int DbgMenuMode;
extern int DbgMenuLevel;
extern int CatMenuLevel;
extern int UntMenuLevel;
extern int CfgMenuLevel;
//$
extern U8 InputPara;
extern U8 ParaTblIndex;
extern U8 ParaIndex;
extern U16 dbg_type;
extern U16 dbg_level;
extern U16 cfg_type;
extern U16 cfg_level;
#endif

#endif

#define UART_RXBUF_SIZE                             255

typedef struct _UartRxQueType
{
    U8  ByteCount;              // haracter counter for receive buffer
    U8  QueueHeader;
    U8  QueueTail;
    U8  RXBuf[UART_RXBUF_SIZE]; // Receive buffer
} UartRxQueType;

#if 1
#define UART_CLEAR_RX_INT (RI_1 = 0)    //Macro for clearing RX interrupt status bit
#define UART_CLEAR_TX_INT (TI_1 = 0)    //Macro for clearing TX interrupt status bit
INTERFACE UartRxQueType g_UartRxQue; // Uart command struct

#define uartRXByteCount g_UartRxQue.ByteCount        //haracter counter for receive buffer
#define uartRxQueueHeader g_UartRxQue.QueueHeader
#define uartRxQueueTail g_UartRxQue.QueueTail
#define uartRXBuf g_UartRxQue.RXBuf    //Receive buffer

INTERFACE BOOLEAN UART_GetChar(BYTE *u8Char);
//--------------------------------------------------------------------------

INTERFACE void MDrv_UART_DebugInit(void);
INTERFACE void MDrv_UART_DecodeCommand(void);
INTERFACE void MDrv_UART_DecodeNormalCommand(void);
INTERFACE void MDrv_UART_DecodeExtCommand(void);
INTERFACE void MDrv_UART_ExecTestCommand(void);
INTERFACE void UART_InOut_Select(U16 source, U8 output);
INTERFACE void MDrv_UART_Register_Empty_RecvHandler(void);
#if (ENABLE_MSTV_UART_DEBUG)
#ifdef MSOS_TYPE_LINUX
INTERFACE void MDrv_OBamaAutoTest_Init(void);
#endif
#endif

/*
    MsAPI_UARTDebug_GetUartKey is used to communicate with MApp_CheckKeyStatus function
    This function returns true if there is command in UART buffer.
*/
INTERFACE BOOLEAN MsAPI_UARTDebug_GetUartKey(U8 *u8key,U8 *u8Repstatus);

#define UART_CMD_LENGTH (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 5)
#define UART_CMD    (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x1F)
#define UART_CMD_MS_REG (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MS_DAT (g_UartCommand.Buffer[_UART_CMD_INDEX2_])

// for EXT Command
#define UART_EXT             (UART_CMD_LENGTH == 7)
#define UART_CMD_EXT_LENGTH  (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_EXT_DEV         (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_EXT_CMD         (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_EXT_CMD_MS_DAT1 (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
#define UART_EXT_CMD_MS_DAT2 (g_UartCommand.Buffer[_UART_CMD_INDEX5_])
#define UART_EXT_CMD_MS_DAT3 (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
#define UART_EXT_CMD_MS_DAT4 (g_UartCommand.Buffer[_UART_CMD_INDEX7_])
#define UART_EXT_CMD_MS_DAT5 (g_UartCommand.Buffer[_UART_CMD_INDEX8_])
#define UART_EXT_CMD_MS_DAT6 (g_UartCommand.Buffer[_UART_CMD_INDEX9_])
#define UART_EXT_CMD_MS_DAT7 (g_UartCommand.Buffer[_UART_CMD_INDEX10_])
#define UART_EXT_CMD_MS_DAT8 (g_UartCommand.Buffer[_UART_CMD_INDEX11_])
#define UART_EXT_CMD_MS_DAT9 (g_UartCommand.Buffer[_UART_CMD_INDEX12_])
#define UART_EXT_CMD_MS_DAT10 (g_UartCommand.Buffer[_UART_CMD_INDEX13_])
#define UART_EXT_CMD_MS_DAT11 (g_UartCommand.Buffer[_UART_CMD_INDEX14_])
#define UART_EXT_CMD_MS_DAT12 (g_UartCommand.Buffer[_UART_CMD_INDEX15_])
#define UART_EXT_CMD_MS_DAT13 (g_UartCommand.Buffer[_UART_CMD_INDEX16_])

#define UART_CMD_FLASH_LENGTH    (g_UartCommand.Buffer[_UART_CMD_CODE_] >> 3)
#define UART_CMD_FLASH_ADDR0    (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_FLASH_ADDR1    (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_FLASH_ADDR2    (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_CMD_FLASH_DATA     (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_FLASH_CMD          (g_UartCommand.Buffer[_UART_CMD_CODE_] & 0x07)

//for menu mode used.
#define  UART_MENU_CMD0        (g_UartCommand.Buffer[_UART_CMD_CODE_])
#define  UART_MENU_CMD1        (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define  UART_MENU_CMD2        (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define  UART_MENU_CMD3        (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define  UART_MENU_CMD4        (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
#define  UART_MENU_CMD5        (g_UartCommand.Buffer[_UART_CMD_INDEX5_])
#define  UART_MENU_CMD6        (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
#define  UART_MENU_CMD7        (g_UartCommand.Buffer[_UART_CMD_INDEX7_])
#define  UART_MENU_CMD8        (g_UartCommand.Buffer[_UART_CMD_INDEX8_])
#define  UART_MENU_CMD9        (g_UartCommand.Buffer[_UART_CMD_INDEX9_])
#define  UART_MENU_CMD10        (g_UartCommand.Buffer[_UART_CMD_INDEX10_])
#define  UART_MENU_CMD11        (g_UartCommand.Buffer[_UART_CMD_INDEX11_])
#define  UART_MENU_CMD12        (g_UartCommand.Buffer[_UART_CMD_INDEX12_])
#define  UART_MENU_CMD13        (g_UartCommand.Buffer[_UART_CMD_INDEX13_])
#define  UART_MENU_CMD14        (g_UartCommand.Buffer[_UART_CMD_INDEX14_])
#define  UART_MENU_CMD15        (g_UartCommand.Buffer[_UART_CMD_INDEX15_])
#define  UART_MENU_CMD16        (g_UartCommand.Buffer[_UART_CMD_INDEX16_])

#define _EOS_ '\0' // end of string

#define uartWrite_MST_Bank_n    0x01
#define uartRead_MST_Bank_n     0x02
#define uartXC_Read_MST_Bank    0x20
#define uartXC_Write_MST_Bank   0x21


#define uartRead_MCU_XDATA      0x04
#define uartWrite_MCU_XDATA     0x05

#define uartRead_Demod          0x06
#define uartWrite_Demod         0x07
#define uartRead_Tuner          0x0A
#define uartWrite_Tuner         0x0B
#if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
#define uartRead_PI2C           0x0C
#define uartWrite_PI2C          0x0D
#endif

#define uartTest_Command        0x09

#define uartI2C_Device_Write    0x10
#define uartI2C_Device_Read     0x11

#define uartEEPROM_Write        0x12
#define uartEEPROM_Read         0x13

//---------------------------------
#define uartExtDev_I2C_DEVICE               0x00
#define uartExtDev_Other_Tuner_Debug        0x02
#define uartExtDev_EEPROM_HDCP              0x03
#define uartExtDev_MstDlcTest               0x05
#define uartExtDev_ACE_REPORT               0x07
#define DEV_MST_DBC_TEST                    0x0A
#define uartExtDev_XC_rw                    0x0B

#define uartExtDev_SAMSUNG_S5H1409_DEMODE   0x10
#define uartExtDev_MstAutoBench 0x15
#if ((CHANNEL_SCAN_AUTO_TEST) || (SFU_AUTO_TEST))
#define uartExtDev_I2C_DEVICE_NEW           0x20
#define uartExtDev_SCAN_TUNER               0x30
#define uartExtDev_AUDIO_DEBUG              0x80
#endif

#define ENABLE_HDCP_KEY_WRITE 				ENABLE //xzm //for hdcp
#define uartExtDev_FLASH_HDCP              	0x14   
#define URCMD_FLASH_HDCP_WRITE_START        0
#define URCMD_FLASH_HDCP_WRITE             	1
#define URCMD_FLASH_HDCP_WRITE_END         	2
#define URCMD_FLASH_HDCP_GET_CHECKSUM      	3


#define uartExtDev_Autotest_Key             0x36 //'6'
#define uartExtDev_Autotest_Sp              0x37 //'7'
#define uartExtDev_USB_Download             0x38 //'8'
#define uartExtDev_Power_Test               0x39 //'9'

#define URCMD_EEPROM_HDCP_GET_ADDR          0
#define URCMD_EEPROM_HDCP_WRITE             1
#define URCMD_EEPROM_HDCP_WRITE_END         2
#define URCMD_EEPROM_HDCP_GET_CHECKSUM      3

//---------------------------------

// kWrite_MST_Bank_n, kRead_MST_Bank_n
#define UART_CMD_MS_BANK_H     (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MS_BANK_L     (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_MS_REGINDEX   (g_UartCommand.Buffer[_UART_CMD_INDEX3_])

#define UART_CMD_MS_REGDATA    (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
// kRead_MCU_XDATA, kWrite_MCU_XDATA
#define UART_CMD_MCU_IDX_H   (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MCU_IDX_H1     (g_UartCommand.Buffer[_UART_CMD_INDEX1_])
#define UART_CMD_MCU_IDX_H2     (g_UartCommand.Buffer[_UART_CMD_INDEX2_])
#define UART_CMD_MCU_IDX_L      (g_UartCommand.Buffer[_UART_CMD_INDEX3_])
#define UART_CMD_MCU_DATA       (g_UartCommand.Buffer[_UART_CMD_INDEX4_])

#define URCMD_MST_DLC_TEST_FORCE_PAUSE      0
#define URCMD_MST_DLC_TEST_FORCE_RUN        1
#define URCMD_MST_DLC_TEST_READ             2
#define URCMD_MST_DLC_TEST_WRITE_1          3
#define URCMD_MST_DLC_TEST_WRITE_2          4
#define URCMD_MST_DLC_TEST_REINIT           5
#define URCMD_MST_DLC_TEST_BOUNDARY_READ    6
#define URCMD_MST_DLC_TEST_BOUNDARY_WRITE   7
#define URCMD_MST_DLC_TEST_READ_CV1         8
#define URCMD_MST_DLC_TEST_READ_CV2A        9
#define URCMD_MST_DLC_TEST_READ_CV2B        10
#define URCMD_MST_DLC_TEST_WRITE_CV1        11
#define URCMD_MST_DLC_TEST_WRITE_CV2A       12
#define URCMD_MST_DLC_TEST_WRITE_CV2B       13
#define URCMD_MST_DLC_TEST_READ_INFO        14
#define URCMD_MST_DLC_TEST_WRITE_INFO       15
#define URCMD_MST_DLC_TEST_CGC_REINIT       16

//ENABLE_DBC
#define URCMD_MST_DBC_TEST_READ_INFO        1
#define URCMD_MST_DBC_TEST_WRITE_INFO       2
#define URCMD_MST_DBC_TEST_REINIT           3

//ENABLE_ACE_REPORT
#define URCMD_MST_ACE_REPORT_CONTRAST   0
#define URCMD_MST_ACE_REPORT_SATURATION 1
#define URCMD_MST_ACE_REPORT_HUE        2
#define URCMD_MST_ACE_REPORT_R_GAIN     3
#define URCMD_MST_ACE_REPORT_G_GAIN     4
#define URCMD_MST_ACE_REPORT_B_GAIN     5
#define URCMD_MST_ACE_REPORT_R_BRI      6
#define URCMD_MST_ACE_REPORT_G_BRI      7
#define URCMD_MST_ACE_REPORT_B_BRI      8
#define URCMD_MST_ACE_REPORT_TYPE       9
#define URCMD_MST_ACE_REPORT_COLOR_CORRECTION_XY_R      10
#define URCMD_MST_ACE_REPORT_COLOR_CORRECTION_XY_G      11
#define URCMD_MST_ACE_REPORT_COLOR_CORRECTION_XY_B      12
#define URCMD_MST_ACE_REPORT_COLOR_CORRECTION_OFFSET_R  13
#define URCMD_MST_ACE_REPORT_COLOR_CORRECTION_OFFSET_G  14
#define URCMD_MST_ACE_REPORT_COLOR_CORRECTION_OFFSET_B  15
#define URCMD_MST_ACE_REPORT_IF_SUPPORT_RGB_GAIN 18

#define URCMD_MST_MV_PW_TEST   0

#if ((CHANNEL_SCAN_AUTO_TEST) || (SFU_AUTO_TEST))
// for uartExtDev_SCAN_TUNER
#define UART_SCAN_DATA1     (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
#define UART_SCAN_DATA2     (g_UartCommand.Buffer[_UART_CMD_INDEX5_])
#define UART_SCAN_DATA3     (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
#define UART_SCAN_DATA4     (g_UartCommand.Buffer[_UART_CMD_INDEX7_])
#define UART_SCAN_DATA5     (g_UartCommand.Buffer[_UART_CMD_INDEX8_])
#define UART_SCAN_DATA6     (g_UartCommand.Buffer[_UART_CMD_INDEX9_])
#define UART_SCAN_DATA7     (g_UartCommand.Buffer[_UART_CMD_INDEX10_])
#define UART_SCAN_DATA8     (g_UartCommand.Buffer[_UART_CMD_INDEX11_])

// for uartExtDev_AUDIO_DEBUG
#define UART_AUDIO_DATA1     (g_UartCommand.Buffer[_UART_CMD_INDEX4_])
#define UART_AUDIO_DATA2     (g_UartCommand.Buffer[_UART_CMD_INDEX5_])
#define UART_AUDIO_DATA3     (g_UartCommand.Buffer[_UART_CMD_INDEX6_])
#define UART_AUDIO_DATA4     (g_UartCommand.Buffer[_UART_CMD_INDEX7_])

#define UART_SCAN_CMD_SET_CH_CNT                0x00
#define UART_SCAN_CMD_SET_ANT                   0x01
#define UART_SCAN_CMD_SET_CABLE_SYSTEM          0x02
#define UART_SCAN_CMD_START                     0x03
#define UART_SCAN_CMD_END                       0x04
#define UART_SCAN_CMD_POLL                      0x05
#define UART_SCAN_CMD_READ_FOUND_CH_NUM         0x06
#define UART_SCAN_CMD_READ_SRV_INFO             0x07
#define UART_SCAN_CMD_READ_FOUND_SRV_NUM        0x08
#define UART_SCAN_CMD_SET_TUNER                 0x09
#define UART_SCAN_CMD_SET_DEMOD                 0x0A
#define UART_SCAN_CMD_SET_SPECTRUM              0x0B
#define UART_SCAN_CMD_SET_TUNE_TO_RFCH          0x0C
#define UART_SCAN_CMD_RETURN_TYPE               0x0D
#define UART_SCAN_CMD_READ_ONE_SRV_INFO         0x0E
//#define UART_SCAN_CMD_READ_SRV_INFO2            0x0F
#define UART_SCAN_CMD_CHK_MAINSTATE                0x0F
#define UART_SCAN_CMD_READ_ONE_SRV_INFO2        0x10
#define UART_SCAN_CMD_SET_PLUSCHANGE_ONE_CH        0x11
#define UART_SCAN_CMD_READ_MAINSTATE            0x12
#define UART_SCAN_CMD_SET_KEYVALUE                0x13

//for uartExtDev_AUDIO_DEBUG
#define UART_AUDIODBG_CMD_SET_BK9                0x00

//#define SCAN_AUTOTEST_CMD_DUMP_CH_INFO        0x01
#define SCAN_AUTOTEST_CMD_POLL                    0x01
#define SCAN_AUTOTEST_CMD_DUMP_ONE_CH_INFO      0x02
//#define SCAN_AUTOTEST_CMD_DUMP_CH_INFO2        0x04
#define SCAN_AUTOTEST_CMD_CHK_MAINSTATE            0x04
#define SCAN_AUTOTEST_CMD_DUMP_ONE_CH_INFO2        0x08
#define SCAN_AUTOTEST_CMD_PLUSCHANGE_ONE_CH        0x10
#define SCAN_AUTOTEST_CMD_DUMP_MAINSTATE        0x20
#define SCAN_AUTOTEST_CMD_SETKEY                0x40

#define AUDIO_DEBUG_CMD_RWREG                    0x01

typedef struct
{
    U16 u12ChNum:11;
    U16 f8Antenna:1;
    U16 u2CableSystem:2;
    U16 u2CableSystemSave:2;
    U16 u12ChFoundNum:11;
    U16 f8AntennaSave:1;
    U16 fScanTypeSave:1;
    U16 fCommand:1;             // 0: stop;     1: Start.
    U16 u2State:2;              // 0: Normal;   1: Scanning;    2. Stopped
    U16 u16SrvFoundNum;
    U16 u16DTVProgNum;
    U16 u16ATVProgNum;
    U16 u16AudioProgNum;
} ScanAutoTestData;

typedef struct
{
    U8 u8RegStartAddr;
    U8 u8WriteData;
    U8 u8ReadBytes;
} ScanAutoTestAU;

#endif

///===========================
/// AutoBenchCmd
///===========================
typedef enum
{
    /* HDMI */
    EN_AutoBenchCmd_HDMI1     =     0x00,
    EN_AutoBenchCmd_HDMI2     =     0x01,
    EN_AutoBenchCmd_HDMI3     =     0x02,
    EN_AutoBenchCmd_HDMI4     =     0x03,

    /* Component*/
    EN_AutoBenchCmd_YPbPr1     =     0x08,
    EN_AutoBenchCmd_YPbPr2     =     0x09,

    /* Svideo*/
    EN_AutoBenchCmd_Svideo1     =     0x10,
    EN_AutoBenchCmd_Svideo2     =     0x11,

    /* AV */
    EN_AutoBenchCmd_CVBS1    =     0x18,
    EN_AutoBenchCmd_CVBS2    =     0x19,

    /* Scart */
    EN_AutoBenchCmd_SCART1     =     0x20,
    EN_AutoBenchCmd_SCART2     =     0x21,

    EN_AutoBenchCmd_RGB      =        0x28,
    EN_AutoBenchCmd_DTV      =    0x30,   /* Only for DTV */
    EN_AutoBenchCmd_TV         =    0x38,   /* Known as ATV in DTV */
    EN_AutoBenchCmd_TTX     =    0x80,   /* Only for DTV */
    EN_AutoBenchCmd_OSD     =    0x81,
    EN_AutoBenchCmd_Exit    =    0xA0
}EN_AutoBenchCmd;

#endif

#define UART_CH_ADD        0x00
#define UART_CH_DEL_PHY    0x01
#define UART_CH_DEL_VIR    0x02

#if(ENABLE_UART2)
// -----------------------------
// define global macro
// -----------------------------
#define ENABLE_UART2_TEST           1 // test  for uart2
#define PrintfUart2(x)          x // debug for uart2

#define MAX_UART2_CMD_LENGTH    35
#define UART2_CMD_LENGTH        (g_Uart2Command.Buffer[_UART_CMD_CODE_] >> 5)
#define UART2_CMD               (g_Uart2Command.Buffer[_UART_CMD_CODE_] & 0x1F)
#define UART2_CMD_MS_REG        (g_Uart2Command.Buffer[_UART_CMD_INDEX1_])
#define UART2_CMD_MS_DAT        (g_Uart2Command.Buffer[_UART_CMD_INDEX2_])

// for EXT Command
#define UART2_EXT               (UART2_CMD_LENGTH == 7)
#define UART2_CMD_EXT_LENGTH    (g_Uart2Command.Buffer[_UART_CMD_INDEX1_])
#define UART2_EXT_DEV           (g_Uart2Command.Buffer[_UART_CMD_INDEX2_])
#define UART2_EXT_CMD           (g_Uart2Command.Buffer[_UART_CMD_INDEX3_])
#define UART2_EXT_CMD_MS_DAT1   (g_Uart2Command.Buffer[_UART_CMD_INDEX4_])
#define UART2_EXT_CMD_MS_DAT2   (g_Uart2Command.Buffer[_UART_CMD_INDEX5_])
#define UART2_EXT_CMD_MS_DAT3   (g_Uart2Command.Buffer[_UART_CMD_INDEX6_])
#define UART2_EXT_CMD_MS_DAT4   (g_Uart2Command.Buffer[_UART_CMD_INDEX7_])
#define UART2_EXT_CMD_MS_DAT5   (g_Uart2Command.Buffer[_UART_CMD_INDEX8_])
#define UART2_EXT_CMD_MS_DAT6   (g_Uart2Command.Buffer[_UART_CMD_INDEX9_])
#define UART2_EXT_CMD_MS_DAT7   (g_Uart2Command.Buffer[_UART_CMD_INDEX10_])
#define UART2_EXT_CMD_MS_DAT8   (g_Uart2Command.Buffer[_UART_CMD_INDEX11_])
#define UART2_EXT_CMD_MS_DAT9   (g_Uart2Command.Buffer[_UART_CMD_INDEX12_])
#define UART2_EXT_CMD_MS_DAT10  (g_Uart2Command.Buffer[_UART_CMD_INDEX13_])
#define UART2_EXT_CMD_MS_DAT11  (g_Uart2Command.Buffer[_UART_CMD_INDEX14_])
#define UART2_EXT_CMD_MS_DAT12  (g_Uart2Command.Buffer[_UART_CMD_INDEX15_])
#define UART2_EXT_CMD_MS_DAT13  (g_Uart2Command.Buffer[_UART_CMD_INDEX16_])

#define UART2_CMD_FLASH_LENGTH  (g_Uart2Command.Buffer[_UART_CMD_CODE_] >> 3)
#define UART2_CMD_FLASH_ADDR0   (g_Uart2Command.Buffer[_UART_CMD_INDEX1_])
#define UART2_CMD_FLASH_ADDR1   (g_Uart2Command.Buffer[_UART_CMD_INDEX2_])
#define UART2_CMD_FLASH_ADDR2   (g_Uart2Command.Buffer[_UART_CMD_INDEX3_])
#define UART2_CMD_FLASH_DATA    (g_Uart2Command.Buffer[_UART_CMD_INDEX1_])
#define UART2_FLASH_CMD         (g_Uart2Command.Buffer[_UART_CMD_CODE_] & 0x07)

//for menu mode used.
#define  UART2_MENU_CMD0        (g_Uart2Command.Buffer[_UART_CMD_CODE_])
#define  UART2_MENU_CMD1        (g_Uart2Command.Buffer[_UART_CMD_INDEX1_])
#define  UART2_MENU_CMD2        (g_Uart2Command.Buffer[_UART_CMD_INDEX2_])
#define  UART2_MENU_CMD3        (g_Uart2Command.Buffer[_UART_CMD_INDEX3_])
#define  UART2_MENU_CMD4        (g_Uart2Command.Buffer[_UART_CMD_INDEX4_])
#define  UART2_MENU_CMD5        (g_Uart2Command.Buffer[_UART_CMD_INDEX5_])
#define  UART2_MENU_CMD6        (g_Uart2Command.Buffer[_UART_CMD_INDEX6_])
#define  UART2_MENU_CMD7        (g_Uart2Command.Buffer[_UART_CMD_INDEX7_])
#define  UART2_MENU_CMD8        (g_Uart2Command.Buffer[_UART_CMD_INDEX8_])
#define  UART2_MENU_CMD9        (g_Uart2Command.Buffer[_UART_CMD_INDEX9_])
#define  UART2_MENU_CMD10       (g_Uart2Command.Buffer[_UART_CMD_INDEX10_])
#define  UART2_MENU_CMD11       (g_Uart2Command.Buffer[_UART_CMD_INDEX11_])
#define  UART2_MENU_CMD12       (g_Uart2Command.Buffer[_UART_CMD_INDEX12_])
#define  UART2_MENU_CMD13       (g_Uart2Command.Buffer[_UART_CMD_INDEX13_])
#define  UART2_MENU_CMD14       (g_Uart2Command.Buffer[_UART_CMD_INDEX14_])
#define  UART2_MENU_CMD15       (g_Uart2Command.Buffer[_UART_CMD_INDEX15_])
#define  UART2_MENU_CMD16       (g_Uart2Command.Buffer[_UART_CMD_INDEX16_])

//<<gchen @ 20180202 uart mcu cmd

#define  UART2_MCU_UP				0x01
#define  UART2_MCU_DOWN				0x02
#define  UART2_MCU_LEFT				0x03
#define  UART2_MCU_RIGHT			0x04
#define  UART2_MCU_SELECT			0x05
#define  UART2_MCU_POWER			0x06
#define  UART2_MCU_MENU				0x07
#define  UART2_MCU_SOURCE			0x08
#define  UART2_MCU_STOP				0x09
#define  UART2_MCU_DISPLAY			0x0a
#define  UART2_MCU_PLAY				0x0b
#define  UART2_MCU_PREVIOUS			0x0c
#define  UART2_MCU_NEXT				0x0d
#define  UART2_MCU_VOLUME_PLUS		0x0e
#define  UART2_MCU_VOLUME_MINUS		0x0f
#define  UART2_MCU_MUTE				0x11
#define  UART2_MCU_KEYSTONE_POS		0x12
#define  UART2_MCU_KEYSTONE_NEG		0x13
#define  UART2_MCU_EXIT				0x14
#define  UART2_MCU_SHUTDOWN			0x15


#define  UART2_TO_MCU_SHUT_DOWN		0x15
#define  UART2_TO_MCU_POWER_OFF		0x06



//>>gchen @ 20180202 uart mcu cmd


// -----------------------------
// define global variable
// -----------------------------
INTERFACE bit   g_bUart2Detected;
INTERFACE U16   g_Uart2CheckTick;
INTERFACE U8    g_Uart2CmdBuf[MAX_UART2_CMD_LENGTH];
INTERFACE U8    g_ucUart2BufIndex;

// -----------------------------
// define global function
// -----------------------------
INTERFACE UartCommadType g_Uart2Command;
INTERFACE void MDrv_UART2_DebugInit(void);
INTERFACE void MDrv_UART2_Close(void);
INTERFACE void MDrv_UART2_SendCommand(MS_U8 *ucCommand, U16 u16Len);
INTERFACE void MDrv_UART2_MCU_RXD(void);
INTERFACE void MDrv_UART2_MCU_TXD(MS_U8 sendChar);

#if(ENABLE_UART2_TEST)
INTERFACE void MDrv_UART2_TestRXD(void);
INTERFACE void MDrv_UART2_TestTXD(void);
#endif

#endif

#undef INTERFACE
#endif /* __UART_H  */
