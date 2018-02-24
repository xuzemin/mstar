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


#include "Board.h"

#include "hwreg.h"

#include "i2c.h"

#define mcuSetIntEn()                   ;//(EA = 1)
#define mcuClrIntEn()                   ;//(EA = 0)

#ifndef EEPROM_CLK_SEL
#define EEPROM_CLK_SEL EEPROM_CLK_100KHZ
#endif

#if EEPROM_CLK_SEL == EEPROM_CLK_400KHZ
#define devI2C_Delay()  \
    { \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); _nop_(); _nop_(); _nop_(); \
        _nop_(); \
    }
#elif EEPROM_CLK_SEL == EEPROM_CLK_200KHZ
void devI2C_Delay(void)
{
    _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_(); _nop_();
    _nop_(); _nop_(); _nop_();
}
#else
void devI2C_Delay(void)
{
    U8 u8Loop;

    u8Loop = 30;                // 99Khz

    while (u8Loop-- > 0)
    {
        _nop_();
    }
}
#endif

#if ( _EEPROM_ACCESS == IIC_BY_SW )
////////////////////////////////////////////////////////////////////////////////
// Set I2C SCL pin high/low.
//
// Arguments: bSet - high/low bit
////////////////////////////////////////////////////////////////////////////////
void devI2C_SetSCL_Chk(bit bSet)
{
    BYTE ucDummy;       // loop dummy

    i2cSCL_PIN_OUT();
    i2cSetSCL(bSet);    // set SCL pin

    if (bSet == _HIGH)  // if set pin high
    {
        ucDummy = I2C_CHECK_PIN_DUMMY; // initialize dummy

        i2cSCL_PIN_IN();

        while ((GetPinI2cSCL() == _LOW) && (ucDummy--)) ; // check SCL pull high

        i2cSCL_PIN_OUT();
    }
}

////////////////////////////////////////////////////////////////////////////////
// Set I2C SDA pin high/low
//
// Arguments: bSet - high/low bit
////////////////////////////////////////////////////////////////////////////////
void devI2C_SetSDA_Chk(bit bSet)
{
    BYTE ucDummy;       // loop dummy

    i2cSDA_PIN_OUT();

    i2cSetSDA(bSet);    // set SDA pin

    if (bSet == _HIGH)  // if set pin high
    {
        ucDummy = I2C_CHECK_PIN_DUMMY; // initialize dummy

        i2cSDA_PIN_IN();

        while ((GetPinI2cSDA() == _LOW) && (ucDummy--)) ; // check SDA pull high

        i2cSDA_PIN_OUT();
    }

}

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
BOOL devI2C_Start(void)
{
    BOOL bStatus = TRUE;    // success status
    mcuClrIntEn();          // disable all interrupt

    devI2C_SetSDA_Chk(_HIGH);

    devI2C_Delay();

    devI2C_SetSCL_Chk(_HIGH);

    devI2C_Delay();

    // check pin error
    i2cSCL_PIN_IN();

    i2cSDA_PIN_IN();

    if ((GetPinI2cSCL() == _LOW) || (GetPinI2cSDA() == _LOW))
    {
        i2cSCL_PIN_OUT();
        i2cSDA_PIN_OUT();
        bStatus = FALSE;
    }
    else // success
    {
        i2cSDA_PIN_OUT();
        i2cSetSDA(_LOW);
        devI2C_Delay();
        i2cSCL_PIN_OUT();
        i2cSetSCL(_LOW);
    }

    mcuSetIntEn(); // release EA bit

    return bStatus;
}

////////////////////////////////////////////////////////////////////////////////
// I2C stop signal.
// <comment>
//              ____________
//  SCL _______/
//                 _________
//  SDA __________/
////////////////////////////////////////////////////////////////////////////////
void devI2C_Stop(void)
{
    mcuClrIntEn(); // disable all interrupt

    i2cSetSCL(_LOW);
    devI2C_Delay();
    i2cSetSDA(_LOW);
    devI2C_Delay();
    devI2C_SetSCL_Chk(_HIGH);
    devI2C_Delay();
    devI2C_SetSDA_Chk(_HIGH);
    devI2C_Delay();

    mcuSetIntEn(); // release EA bit
}

////////////////////////////////////////////////////////////////////////////////
// I2C receive byte from device.
//
// Return value: receive byte
////////////////////////////////////////////////////////////////////////////////
BYTE devI2C_ReceiveByte(BOOL bAck)
{
    BYTE ucReceive = 0;
    BYTE ucMask = 0x80;

    mcuClrIntEn();

    i2cSDA_PIN_IN();

    while ( ucMask )
    {
        devI2C_SetSCL_Chk(_HIGH);
        devI2C_Delay();

        if (GetPinI2cSDA() == _HIGH)
        {
            ucReceive |= ucMask;
        }

        i2cSetSCL(_LOW);
        devI2C_Delay();

        ucMask >>= 1; // next
    }

    i2cSDA_PIN_OUT();

    if (bAck)
    {
        // acknowledge
        devI2C_SetSDA_Chk(I2C_ACKNOWLEDGE);
    }
    else
    {
        // non-acknowledge
        devI2C_SetSDA_Chk(I2C_NON_ACKNOWLEDGE);
    }

    devI2C_Delay();
    devI2C_SetSCL_Chk(_HIGH);
    devI2C_Delay();
    i2cSetSCL(_LOW);
    devI2C_Delay();

    mcuSetIntEn(); // release EA bit

    return ucReceive;
}


////////////////////////////////////////////////////////////////////////////////
// I2C send byte to device.
//
// Arguments: ucVal - send byte
// Return value: I2C acknowledge bit
//               I2C_ACKNOWLEDGE/I2C_NON_ACKNOWLEDGE
////////////////////////////////////////////////////////////////////////////////
bit devI2C_SendByte(BYTE ucVal)
{
    BYTE    ucMask = 0x80;
    bit     bAck; // acknowledge bit

    mcuClrIntEn();

    while ( ucMask )
    {
        if (ucVal & ucMask)
        {
            devI2C_SetSDA_Chk(_HIGH);
        }
        else
        {
            devI2C_SetSDA_Chk(_LOW);
        }

        devI2C_Delay();
        devI2C_SetSCL_Chk(_HIGH); // clock
        devI2C_Delay();
        i2cSetSCL(_LOW);
        devI2C_Delay();

        ucMask >>= 1; // next
    }

    // recieve acknowledge
    i2cSDA_PIN_IN();
    devI2C_Delay();
    devI2C_SetSCL_Chk(_HIGH);
    devI2C_Delay();
    bAck = GetPinI2cSDA(); // recieve acknowlege
    i2cSDA_PIN_OUT();
    i2cSetSCL(_LOW);
    devI2C_Delay();

    mcuSetIntEn(); // release EA bit

    return (bAck);
}

////////////////////////////////////////////////////////////////////////////////
// I2C access start.
//
// Arguments: ucSlaveAdr - slave address
//            trans_t - I2C_TRANS_WRITE/I2C_TRANS_READ
////////////////////////////////////////////////////////////////////////////////
BOOL devI2C_AccessStart(BYTE ucSlaveAdr, I2cIoTransType trans_t)
{
    BYTE ucDummy; // loop dummy

    if (trans_t == I2C_TRANS_READ) // check i2c read or write
    {
        ucSlaveAdr = I2C_DEVICE_ADR_READ(ucSlaveAdr); // read
    }
    else
    {
        ucSlaveAdr = I2C_DEVICE_ADR_WRITE(ucSlaveAdr); // write
    }

    // enlarge retry count to cover internal write period

    ucDummy = 60;  //I2C_ACCESS_DUMMY_TIME;

    while (ucDummy--)
    {
        if (devI2C_Start() == FALSE)
        {
            continue;
        }

        if (devI2C_SendByte(ucSlaveAdr) == I2C_ACKNOWLEDGE) // check acknowledge
        {
            return TRUE;
        }

        devI2C_Stop();
    }

    return FALSE;
}

////////////////////////////////////////////////////////////////////////////////
// I2C read bytes from device.
//
// Arguments: ucSlaveAdr - slave address
//            ucSubAdr - sub address
//            pBuf - pointer of buffer
//            ucBufLen - length of buffer
////////////////////////////////////////////////////////////////////////////////

#if (KEEP_UNUSED_FUNC == 1)

void devI2C_BurstWriteBytes_2(BYTE ucSlaveAdr, BYTE *pBuf, BYTE ucBufLen)
{
    devI2C_BurstWriteBytes( ucSlaveAdr, pBuf[0], pBuf+1, ucBufLen-1 );
}

/////////////////////////////////////////////////////////////////
// I2C read a current byte from device.
//
// Arguments: ucSlaveAdr - slave address
// Return value: read byte
/////////////////////////////////////////////////////////////////
BYTE devI2C_ReadCurrent(BYTE ucSlaveAdr)
{
    BYTE ucByte; // byte buffer

    i2cBurstReadBytes_2(ucSlaveAdr,&ucByte,1);
    return ucByte;
}

#endif

/////////////////////////////////////////////////////////////////
// I2C read a byte from device.
//
// Arguments: ucSlaveAdr - slave address
//            ucSubAdr - sub address
// Return value: read byte
/////////////////////////////////////////////////////////////////
void devI2C_BurstReadBytes(BYTE ucSlaveAdr, unsigned int ucSubAdr, BYTE *pBuf, BYTE ucBufLen)
{
    BYTE ucDummy; // loop dummy

    ucDummy = I2C_ACCESS_DUMMY_TIME;

    while (ucDummy--)
    {
        if (devI2C_AccessStart(ucSlaveAdr, I2C_TRANS_WRITE) == FALSE)
        {
            continue;
        }

        if (devI2C_SendByte(HIBYTE(ucSubAdr)) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
        {
            continue;
        }

        if (devI2C_SendByte(LOBYTE(ucSubAdr)) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
        {
            continue;
        }

        if (devI2C_AccessStart(ucSlaveAdr, I2C_TRANS_READ) == FALSE)
        {
            continue;
        }

        while (ucBufLen--) // loop to burst read
        {
            *pBuf = devI2C_ReceiveByte(ucBufLen); // receive byte

            pBuf++; // next byte pointer
        }

        break;
    }

    devI2C_Stop();
}

////////////////////////////////////////////////////////////////////////////////
// I2C write bytes to device.
//
// Arguments: ucSlaveAdr - slave address
//            ucSubAdr - sub address
//            pBuf - pointer of buffer
//            ucBufLen - length of buffer
////////////////////////////////////////////////////////////////////////////////
void devI2C_BurstWriteBytes(BYTE ucSlaveAdr, unsigned int ucSubAdr, BYTE *pBuf, BYTE ucBufLen)
{
    BYTE ucDummy; // loop dummy

    ucDummy = 1; //I2C_ACCESS_DUMMY_TIME;

    while (ucDummy--)
    {
        if (devI2C_AccessStart(ucSlaveAdr, I2C_TRANS_WRITE) == FALSE)
        {
            continue;
        }

        if (devI2C_SendByte(HIBYTE(ucSubAdr)) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
        {
            continue;
        }

        if (devI2C_SendByte(LOBYTE(ucSubAdr)) == I2C_NON_ACKNOWLEDGE) // check non-acknowledge
        {
            continue;
        }

        while (ucBufLen--) // loop of writting data
        {
            devI2C_SendByte(*pBuf); // send byte

            pBuf++; // next byte pointer
        }

        break;
    }

    devI2C_Stop();
}

BYTE devI2C_ReadByte(BYTE ucSlaveAdr, U16 ucSubAdr)
{
    BYTE ucBuf; // byte buffer

    devI2C_BurstReadBytes(ucSlaveAdr, ucSubAdr, &ucBuf, 1);

    return ucBuf;
}

/////////////////////////////////////////////////////////////////
// I2C write a byte from device.
//
// Arguments: ucSlaveAdr - slave address
//            ucSubAdr - sub address
//            ucVal - write byte
/////////////////////////////////////////////////////////////////
void devI2C_WriteByte(BYTE ucSlaveAdr, U16 ucSubAdr, BYTE ucVal)
{
    devI2C_BurstWriteBytes(ucSlaveAdr, ucSubAdr, &ucVal, 1);
}

//------------------------------------------------------------------------------
#if 0 // Software I2C Test
void SwI2cTest( void )
{
//    code unsigned char xxTest[8]={0x00,0x99,0x88,0x77,0x66,0x55,0x44,0x33};
//    code unsigned char yyTest[8]={0x10,0x19,0x18,0x17,0x16,0x15,0x14,0x13};
    unsigned int  SubAddr;
//    unsigned char read[8];
    unsigned char i,j;

       printf("sw i2c test...\n");
    i=0x55;
    SubAddr=0x0150;
    devI2C_BurstWriteBytes(0xa0,SubAddr,&i,1);
    printf("1 byte write done\n");
    devI2C_BurstReadBytes(0xa0, SubAddr, &j, 1);
    printf("j=%02bx. \n",j);



    i=0xAA;
    SubAddr=0x0100;
    devI2C_BurstWriteBytes(0xa0,SubAddr,&i,1);
    printf("1 byte write done\n");
    devI2C_BurstReadBytes(0xa0, SubAddr, &j, 1);
    printf("j=%02bx. \n",j);


    SubAddr=0x120;
    devI2C_BurstWriteBytes(0xa0,SubAddr,8, xxTest);
    printf("8_1 byte write done\n");

    devI2C_BurstReadBytes(0xa0,SubAddr, 8, read );

    for ( i=0;i<8;i++ )
       printf("%02bx ,",read[i]);
    printf("\n");


    addr[0]=0x02; addr[1]=0x80;
    MDrv_I2C_WriteBytes(0xa0,2,addr,8, yyTest);
    printf("8-2 byte write done\n");

    MDrv_I2C_ReadBytes(0xa0,2, addr, 8, read );
    for ( i=0;i<8;i++ )
       printf("%02bx ,",read[i]);
    printf("\n");

}
#endif

#endif //_EEPROM_ACCESS == IIC_BY_SW
