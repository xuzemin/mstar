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
//!file     si_regio.c
//!brief    Silicon Image Device register I/O support.
//
// No part of this work may be reproduced, modified, distributed, 
// transmitted, transcribed, or translated into any language or computer 
// format, in any form or by any means without written permission of 
// Silicon Image, Inc., 1060 East Arques Avenue, Sunnyvale, California 94085
//
// Copyright 2008-2009, Silicon Image, Inc.  All rights reserved.
//***************************************************************************/

#include "./SiI1292/API/si_regio.h"
#include "./SiI1292/HAL/INC/si_hal.h"

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------

// Register Slave Address page map

//static uint8_si  XDATA l_regioDecodePage [16] =
uint8_si l_regioDecodePage [16] =
{
    REGIO_SLAVE_PAGE_0, REGIO_SLAVE_PAGE_1, REGIO_SLAVE_PAGE_2, REGIO_SLAVE_PAGE_3,
    REGIO_SLAVE_PAGE_4, REGIO_SLAVE_PAGE_5, REGIO_SLAVE_PAGE_6, REGIO_SLAVE_PAGE_7,
    REGIO_SLAVE_PAGE_8, REGIO_SLAVE_PAGE_9, REGIO_SLAVE_PAGE_A, REGIO_SLAVE_PAGE_B,
    REGIO_SLAVE_PAGE_C, REGIO_SLAVE_PAGE_D, REGIO_SLAVE_PAGE_E, REGIO_SLAVE_PAGE_F
};

#ifdef SPADE
//------------------------------------------------------------------------------
// Function:    SiIRegioSetBase
// Description: Set the device ID of the passed page.
//              Used to change from the default value if necessary.
//------------------------------------------------------------------------------

void SiIRegioSetBase ( uint8_si page, uint8_si newID )
{

    if ( page < sizeof( l_regioDecodePage ))
    {
        /* Change look-up table.    */

        l_regioDecodePage[ page] = newID;

        /* Change programmable base address register.   */

        switch ( page )
        {
        case  2:    SiIRegioWrite( REG_SLAVE_ADDR6, newID );    break;
        case  4:    SiIRegioWrite( REG_SLAVE_ADDR7, newID );    break;
        case  8:    SiIRegioWrite( REG_SLAVE_ADDR2, newID );    break;
        case  9:    SiIRegioWrite( REG_SLAVE_ADDR3, newID );    break;
        case 10:    SiIRegioWrite( REG_SLAVE_ADDR4, newID );    break;
        case 11:    SiIRegioWrite( REG_SLAVE_ADDR5, newID );    break;
        case 12:    SiIRegioWrite( REG_SLAVE_ADDR1, newID );    break;
        case 13:    SiIRegioWrite( REG_SLAVE_ADDR0, newID );    break;
        case 14:    SiIRegioWrite( REG_SLAVE_ADDR5, newID );    break;
        default:                                                break;
        }
    }
    
}

#endif // SPADE

//------------------------------------------------------------------------------
// Function:    SiIRegioRead
// Description: Read a one byte register.
//              The register address parameter is translated into an I2C slave
//              address and offset. The I2C slave address and offset are used 
//              to perform an I2C read operation.
//------------------------------------------------------------------------------

uint8_si SiIRegioRead ( uint16_si regAddr )
{

    return (uint8_si)( HalI2cReadByte( l_regioDecodePage[ regAddr >> 8], (uint8_si)regAddr ));
}

//------------------------------------------------------------------------------
// Function:    SiIRegioWrite
// Description: Write a one byte register.
//              The register address parameter is translated into an I2C
//              slave address and offset. The I2C slave address and offset 
//              are used to perform an I2C write operation.
//------------------------------------------------------------------------------

void SiIRegioWrite ( uint16_si regAddr, uint8_si value )
{
//	printf("[SiIRegioWrite =%x,regAddr=%x,value=%x]\n",l_regioDecodePage[ regAddr >> 8],regAddr,value);
    HalI2cWriteByte( l_regioDecodePage[ regAddr >> 8], (uint8_si)regAddr, value );
}

//------------------------------------------------------------------------------
// Function:    SiIRegioReadBlock
// Description: Read a block of registers starting with the specified register.
//              The register address parameter is translated into an I2C 
//              slave address and offset.
//              The block of data bytes is read from the I2C slave address 
//              and offset.
//------------------------------------------------------------------------------

void SiIRegioReadBlock ( uint16_si regAddr, uint8_si* buffer, uint16_si length)
{
    bool_si result;
    result = HalI2cReadBlock( l_regioDecodePage[ regAddr >> 8], (uint8_si)regAddr, buffer, length);
}

//------------------------------------------------------------------------------
// Function:    SiIRegioWriteBlock
// Description: Write a block of registers starting with the specified register.
//              The register address parameter is translated into an I2C slave
//              address and offset.
//              The block of data bytes is written to the I2C slave address 
//              and offset.
//------------------------------------------------------------------------------

void SiIRegioWriteBlock ( uint16_si regAddr, uint8_si* buffer, uint16_si length)
{
    bool_si result;
    result = HalI2cWriteBlock( l_regioDecodePage[ regAddr >> 8], (uint8_si)regAddr, buffer, length);
}

//------------------------------------------------------------------------------
// Function:    SiIRegioBitToggle
// Description: Toggle a bit or bits in a register
//              The register address parameter is translated into an I2C 
//              slave address and offset.
//              The I2C slave address and offset are used to perform I2C 
//              read and write operations.
//
//              All bits specified in the mask are first set and then cleared 
//              in the register.
//              This is a common operation for toggling a bit manually.
//------------------------------------------------------------------------------

void SiIRegioBitToggle ( uint16_si regAddr, uint8_si mask)
{
    uint8_si slaveID, abyte;

    slaveID = l_regioDecodePage[ regAddr >> 8];

    abyte = HalI2cReadByte( slaveID, (uint8_si)regAddr );
    abyte |=  mask;                                         //first set the bits in mask
    HalI2cWriteByte( slaveID, (uint8_si)regAddr, abyte);        //write register with bits set
    abyte &= ~mask;                                         //then clear the bits in mask
    HalI2cWriteByte( slaveID, (uint8_si)regAddr, abyte);        //write register with bits clear
}

//------------------------------------------------------------------------------
// Function:    SiIRegioModify
// Description: Modify a one byte register under mask.
//              The register address parameter is translated into an I2C 
//              slave address and offset. The I2C slave address and offset are 
//              used to perform I2C read and write operations.
//
//              All bits specified in the mask are set in the register 
//              according to the value specified.
//              A mask of 0x00 does not change any bits.
//              A mask of 0xFF is the same a writing a byte - all bits 
//              are set to the value given.
//              When only some bits in the mask are set, only those bits are 
//              changed to the values given.
//------------------------------------------------------------------------------

void SiIRegioModify ( uint16_si regAddr, uint8_si mask, uint8_si value)
{
    uint8_si slaveID, abyte;

    slaveID = l_regioDecodePage[ regAddr >> 8];

    abyte = HalI2cReadByte( slaveID, (uint8_si)regAddr );
    abyte &= (~mask);                                       //first clear all bits in mask
    abyte |= (mask & value);                                //then set bits from value
    HalI2cWriteByte( slaveID, (uint8_si)regAddr, abyte);
}

