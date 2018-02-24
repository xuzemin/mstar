//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all 
// or part of MStar Software is expressly prohibited, unless prior written 
// permission has been granted by MStar. 
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.  
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software. 
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s 
//    confidential information in strictest confidence and not disclose to any
//    third party.  
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.  
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or 
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.  
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
//***************************************************************************
//!file     "si_hal.h"
//!brief    Silicon Image HAL function library header.
//
// No part of this work may be reproduced, modified, distributed,
// transmitted, transcribed, or translated into any language or computer
// format, in any form or by any means without written permission of
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2008-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#ifndef __HAL_H__
#define __HAL_H__
#include "./SiI1292/API/si_datatypes.h"

#define API_DEBUG_CODE 0
//#define TIME_STAMP
//-------------------------------------------------------------------------------
//  HAL Macros
//-------------------------------------------------------------------------------
extern uint32_si g_pass;

//choose one, cannot both defined to 1.
#define BOARD_CP1292//using CP1292 board
//#define BOARD_JULIPORT//using RK1292 board

//#ifdef BOARD_CP1292
#define HWI2C//NOTE: please be sure that R27 and R29 is weld in CP1292 start kit
//#endif


#if (API_DEBUG_CODE==0)
//#define DEBUG_PRINT(l,x)   
//extern int printf(const CHAR *format, ...);
#endif


//-------------------------------------------------------------------------------
//  HAL Constants
//-------------------------------------------------------------------------------

#define I2C_BUS0        0
#define I2C_BUS1        1
#define I2C_BUS2        2
#define I2C_BUS3        3

    /* Rotary switch values.    */

#define RSW_POS_0           0x00
#define RSW_POS_1           0x01
#define RSW_POS_2           0x02
#define RSW_POS_3           0x03
#define RSW_POS_4           0x04
#define RSW_POS_5           0x05
#define RSW_POS_6           0x06
#define RSW_POS_7           0x07
#define RSW_NO_CHANGE       0xFF    // Rotary switch has not changed

//-------------------------------------------------------------------------------
//  Required before use of some HAL modules
//-------------------------------------------------------------------------------

bool_si    HalInitialize( void );
uint8_si HalVersion( bool_si wantMajor );
uint8_si HalVersionFPGA( bool_si wantMajor );

//-------------------------------------------------------------------------------
//  I2C Master BUS Interface
//-------------------------------------------------------------------------------

uint8_si HalI2cBus0ReadByte( uint8_si device_id, uint8_si addr );
void HalI2cBus0WriteByte( uint8_si deviceID, uint8_si offset, uint8_si value );
bool_si HalI2cBus0ReadBlock( uint8_si deviceID, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2cBus0WriteBlock( uint8_si device_id, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2cBus016ReadBlock( uint8_si device_id, uint16_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2cBus016WriteBlock( uint8_si device_id, uint16_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2CBus0WaitForAck( uint8_si device_id );
uint8_si HalI2cBus0GetStatus( void );

uint8_si HalI2cBus1ReadByte( uint8_si device_id, uint8_si addr );
void HalI2cBus1WriteByte( uint8_si deviceID, uint8_si offset, uint8_si value );
bool_si HalI2cBus1ReadBlock( uint8_si deviceID, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2cBus1WriteBlock( uint8_si device_id, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
uint8_si HalI2cBus1GetStatus( void );

uint8_si HalI2cBus2ReadByte( uint8_si device_id, uint8_si addr );
void HalI2cBus2WriteByte( uint8_si deviceID, uint8_si offset, uint8_si value );
bool_si HalI2cBus2ReadBlock( uint8_si deviceID, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2cBus2WriteBlock( uint8_si device_id, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
uint8_si HalI2cBus2GetStatus( void );

uint8_si HalI2cBus3ReadByte( uint8_si device_id, uint8_si addr );
void HalI2cBus3WriteByte( uint8_si deviceID, uint8_si offset, uint8_si value );
bool_si HalI2cBus3ReadBlock( uint8_si deviceID, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si HalI2cBus3WriteBlock( uint8_si device_id, uint8_si addr, uint8_si *p_data, uint16_si nbytes );
uint8_si HalI2cBus3GetStatus( void );

extern void twi_init(void);
extern unsigned char twi_DDC_read( unsigned char seg, unsigned char slave_addr, unsigned char reg_addr, unsigned short len, unsigned char *buf );
extern unsigned char twi_read( unsigned char slave_addr, unsigned char reg_addr, unsigned short len, unsigned char *buf );
extern unsigned char twi_write( unsigned char slave_addr, unsigned char reg_addr, unsigned short len, unsigned char *buf );
extern unsigned char twi_read_byte( unsigned char slave_addr, unsigned char reg_addr );
extern unsigned char twi_write_byte( unsigned char slave_addr, unsigned char reg_addr, unsigned char byte );
extern unsigned char twi_read_block( unsigned char slave_addr, unsigned char reg_addr, unsigned char *buf, unsigned short len );
extern unsigned char twi_write_block( unsigned char slave_addr, unsigned char reg_addr, unsigned char *buf, unsigned short len );
extern unsigned char twi_16read( unsigned char slave_addr, unsigned short reg_addr, unsigned short len, unsigned char *buf );
extern unsigned char twi_16write( unsigned char slave_addr, unsigned short reg_addr, unsigned short len, unsigned char *buf );
extern unsigned char twi_wait_ack( unsigned char slave_addr, unsigned char timeoutMs );
//-------------------------------------------------------------------------------
//  I2C Local Bus
//  Macros to select the I2C bus that is used by this board's local I2C bus.
//-------------------------------------------------------------------------------

#ifdef HWI2C
#define HalI2cReadByte( device_id, addr )                       twi_read_byte( device_id, addr )
#define HalI2cWriteByte( device_id, addr, value )               twi_write_byte( device_id, addr, value ) 
#define HalI2cReadBlock( device_id, addr, p_data, nbytes )      (0 == twi_read_block( device_id, addr, p_data, nbytes ))
#define HalI2cWriteBlock( device_id, addr, p_data, nbytes )     (0 == twi_write_block( device_id, addr, p_data, nbytes ))
#define HalI2c16ReadBlock( device_id, addr, p_data, nbytes )    (0 == twi_16read( device_id, addr, nbytes, p_data ))
#define HalI2c16WriteBlock( device_id, addr, p_data, nbytes )   (0 == twi_16write( device_id, addr, nbytes, p_data ))
#define HalI2CWaitForAck( device_id)                (0 == twi_wait_ack( device_id, 1 ))
#else
#define HalI2cReadByte( device_id, addr )                       HalI2cBus0ReadByte( device_id, addr )
#define HalI2cWriteByte( device_id, addr, value )               HalI2cBus0WriteByte( device_id, addr, value )
#define HalI2cReadBlock( device_id, addr, p_data, nbytes )      HalI2cBus0ReadBlock( device_id, addr, p_data, nbytes )
#define HalI2cWriteBlock( device_id, addr, p_data, nbytes )     HalI2cBus0WriteBlock( device_id, addr, p_data, nbytes )
#define HalI2c16ReadBlock( device_id, addr, p_data, nbytes )    HalI2cBus016ReadBlock( device_id, addr, p_data, nbytes )
#define HalI2c16WriteBlock( device_id, addr, p_data, nbytes )   HalI2cBus016WriteBlock( device_id, addr, p_data, nbytes )
#define HalI2CWaitForAck( device_id )                           HalI2CBus0WaitForAck( device_id )
#define HalI2cGetStatus()                                       HalI2cBus0GetStatus()

#endif

//-------------------------------------------------------------------------------
//  I2C Slave Interface
//
//  Implemented as a set of registers that a master device can read and write 
//  as if it was a device
//-------------------------------------------------------------------------------

#define HAL_SLAVE_I2C_ADDR 		0x82    // Address of device as it appears to external master

#define HAL_SLAVE_REG_COUNT     4       // Total number of slave registers
#define HAL_SLAVE_REG_ACTIVE    0       // Number of slave registers that cause an indirect call into application code

void HalSlaveI2CInit( void );
uint8_si HalSlaveI2CRead( uint8_si regOffset );
void HalSlaveI2CWrite( uint8_si regOffset, uint8_si value );

//-------------------------------------------------------------------------------
//  UART functions
//-------------------------------------------------------------------------------

#define MSG_ALWAYS              0x00
#define MSG_STAT                0x01
#define MSG_DBG                 0x02
#define MSG_PRINT_ALL           0xFF

extern  uint8_si     g_halMsgLevel;

void    HalUartInit( void );
//uint8_si putchar( uint8_si c );
//uint8_si _getkey( void );

//-------------------------------------------------------------------------------
//  REMOTE functions
//-------------------------------------------------------------------------------

bool_si HAL_RemoteRequestHandler( void );

//-------------------------------------------------------------------------------
//  Timer Functions
//-------------------------------------------------------------------------------

#define ELAPSED_TIMER               0xFF
#define ELAPSED_TIMER1              0xFE
#define TIMER_0                     0   // DO NOT USE - reserved for TimerWait()
#define TIMER_POLLING               1   // Reserved for main polling loop
#define TIMER_2                     2   // Available
#define TIMER_3                     3   // Available

void    HalTimerInit( void );
void    HalTimerSet( uint8_si timer, uint16_si m_sec );
uint8_si HalTimerExpired( uint8_si timer );
void    HalTimerWait( uint16_si m_sec );
uint16_si HalTimerElapsed( uint8_si index );
bool_si HalTimerDelay(uint32_si baseTime, uint32_si delay);


//-------------------------------------------------------------------------------
//  Extended GPIO Functions
//-------------------------------------------------------------------------------

#define DEF_EX_DIRECTION    0x00    // All GPIOs output
#define DEF_EX_POLARITY     0x00    // All GPIO outputs not inverted
#define DEF_EX_DEFAULT_VAL  0xE0    // Default output state

#define EX_GPIO_DEVICE_ID   0x38
#define EX_GPIO_INPUT       0
#define EX_GPIO_OUTPUT      1
#define EX_GPIO_POLARITY    2
#define EX_GPIO_CONFIG      3

void    HalGpioInit( void );
uint8_si HalGpioExRead( void );
void    HalGpioExWrite( uint8_si newValue );

uint8_si HalGpioReadRotarySwitch ( uint8_si i_want_it_now );

bool_si HalGpioReadWakeUpPin(void);


//-------------------------------------------------------------------------------
//  Internal EEPROM functions
//-------------------------------------------------------------------------------

uint8_si HalEEintReadByte( uint16_si addr );
void    HalEEintWriteByte( uint16_si addr, uint8_si value );
bool_si    HalEEintReadBlock( uint16_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si    HalEEintWriteBlock( uint16_si addr, uint8_si *p_data, uint16_si nbytes );

//-------------------------------------------------------------------------------
//  External EEPROM functions
//-------------------------------------------------------------------------------

uint8_si HalEEextReadByte( uint16_si addr );
void    HalEEextWriteByte( uint16_si addr, uint8_si value );
bool_si    HalEEextReadBlock( uint16_si addr, uint8_si *p_data, uint16_si nbytes );
bool_si    HalEEextWriteBlock( uint16_si addr, uint8_si *p_data, uint16_si nbytes );

//-------------------------------------------------------------------------------
//  IR Interface functions
//-------------------------------------------------------------------------------

//typedef enum
enum
{
    NO_EVENT,  //!< nothing happened
    KEY_DOWN,  //!< remote control key pressed down
    KEY_UP,    //!< remote control key released
};

typedef struct
{
    uint8_si eventType;  //!< UI event type
    uint8_si command;    //!< UI command
} IrCommand_t;

typedef struct 
{
    uint8_si rc5Command;         //!< rc protocol command code
    uint8_si uiCommand;          //!< UI command code
} UiRc5Conversion_t;

typedef struct
{
    uint8_si rc5address;
    uint8_si uiRc5convTableLength;
    const UiRc5Conversion_t* uiRc5convTable;

} UiRC5CommandMap_t;

// user will provide this for the lib( no need to change lib when customizing applications ).

extern const UiRC5CommandMap_t irCommandMap;
                                 
IrCommand_t HalGetIRCommand( void );
void HalIRInit( void );
bool_si HalIRReturnRC5( bool_si returnRC5 );


#endif  // _HAL_H__
