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
#include "./SiI1292/API/si_datatypes.h"
#include "./SiI1292/HAL/INC/si_hal.h"

uint32_si  timer_count;
uint32_si  timer_count2;
uint32_si  timer_count4;
uint32_si  timer_count3;
uint8_si     g_halMsgLevel;

uint16_si g_timerCounters[4];
uint16_si g_timerElapsed;
uint16_si g_elapsedTick;
uint16_si g_timerElapsedGranularity;

uint16_si g_timerElapsed1;
uint16_si g_elapsedTick1;
uint16_si g_timerElapsedGranularity1;

uint16_si g_pulseWidthCounter = 0;
bool_si   g_startWidthCounter = false;
enum
{
	HDMI = 0,
	MHL
};
extern uint8_si g_currentInputMode;

//extern UINT8 ucI2cRead(UINT8 ucI2cAddr, UINT8 ucRegAddr, UINT8 *pucBuffer, UINT16 ucByteCount);
//extern UINT8 ucI2cWrite(UINT8 ucI2cAddr, UINT8 ucRegAddr, UINT8 *pucBuffer, UINT16 ucByteCount);

extern MS_BOOL MApi_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
extern MS_BOOL MApi_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);

bool_si HalTimerDelay(uint32_si baseTime, uint32_si delay)
{
	uint32_si diff_time = timer_count - baseTime;

	printf("base: %u; delay: %u; count: %u\n", (int)baseTime, (int)delay, (int)timer_count);

	if( diff_time < delay)
		return false;
	else
		return true;
}

bool_si HalTimerDelay2( uint32_si delay)
{
	timer_count2 ++;
	if(timer_count2 > delay)
	{
		timer_count2 =0;
		return true;
	}
	else
	{
		return false;
	}
}
bool_si HalTimerDelay4( uint32_si delay)
{
	timer_count4 ++;
	if(timer_count4 > delay)
	{
		timer_count4 =0;
		return true;
	}
	else
	{
		return false;
	}
}

bool_si HalTimerDelay3_Flag = 0;
bool_si HalTimerDelay3( uint32_si delay)
{
	static uint32_si baseTime = 0;
	uint32_si diff_time = timer_count3 - baseTime;
	
	if( diff_time < delay)
      {
		return false;
	}
	else
	{
		baseTime = timer_count3;
		HalTimerDelay3_Flag = true;	
		return true;
	}
}



uint8_si HalTimerExpired( uint8_si timer )
{
	if ( timer < 4 ) // 4 timers 
	{
		return( g_timerCounters[ timer ] == 0);
	}

	return( 0 );
}

void    HalTimerSet( uint8_si timer, uint16_si m_sec )
{
	switch ( timer )
	{
		case TIMER_0:
		case TIMER_POLLING:
		case TIMER_2:
		case TIMER_3:
		g_timerCounters[ timer ] = m_sec;
		break;

		case ELAPSED_TIMER:
		g_timerElapsedGranularity = m_sec;
		g_timerElapsed = 0;
		g_elapsedTick = 0;
		break;
		case ELAPSED_TIMER1:
		g_timerElapsedGranularity1 = m_sec;
		g_timerElapsed1 = 0;
		g_elapsedTick1 = 0;
		break;
	}
}

void T0_irqtimes(void)
{
     uint8_si i;
    //decrement all active timers in array

    for ( i = 0; i < 4; i++ )
    {
        if ( g_timerCounters[ i ] > 0 )
        {
            g_timerCounters[ i ]--;
        }
    }
    g_elapsedTick++;
    if ( g_elapsedTick == g_timerElapsedGranularity )
    {
        g_timerElapsed++;
        g_elapsedTick = 0;
    }
    g_elapsedTick1++;
    if ( g_elapsedTick1 == g_timerElapsedGranularity1 )
    {
        g_timerElapsed1++;
        g_elapsedTick1 = 0;
    }

	//Jin: for wakeup pulse detect
	if( g_startWidthCounter )
	{
		g_pulseWidthCounter ++;
	}

	//Jin: for new timer system
	timer_count ++;
	timer_count3 ++;
}

bool_si HAL_RemoteRequestHandler( void )
{
	return false;
}

bool_si HalGpioReadWakeUpPin(void)
{
	return true;    //wait to modify
}

extern void    Waitms_forMHL( uint16_si m_sec );
void    HalTimerWait( uint16_si m_sec )
{
	Waitms_forMHL(m_sec); //ms
}
typedef unsigned char UINT8 ;
IrCommand_t  IRkeycommon;

extern bool_si SI_IrRcpKeys( uint8_si key, uint8_si eventType );
void HAL_8032_TO_RiscIR(uint8_si teventType,uint8_si command )
{
	/* In CEC demo mode, send a key up command for every key we sent a key down command.  */
	teventType = teventType;
	if (g_currentInputMode == MHL)
		SI_IrRcpKeys(command, KEY_DOWN );
	//else
	//	IrCecKeys( command, teventType);
}

IrCommand_t HalGetIRCommand( void )
{
	IrCommand_t tcmmon;
       tcmmon.command = IRkeycommon.command;
       tcmmon.eventType= IRkeycommon.eventType;
	return tcmmon;
}

bool_si HalIRReturnRC5( bool_si returnRC5 )
{
	returnRC5 = returnRC5;
	return false;
}

#define IICFLAG   1
unsigned char twi_read_block( unsigned char slave_addr, unsigned char reg_addr, unsigned char *buf, unsigned short len )
{
	#if IICFLAG
	//ucI2cRead(slave_addr, reg_addr, buf, len);
	if(MApi_SWI2C_ReadBytes((MS_U16)slave_addr, 1, &reg_addr, (MS_U16) len, buf))
	{
		;//printf("%s Success!!!]\n",__FUNCTION__);
	}
	else
	{
		printf("%s Error!!!]\n",__FUNCTION__);
	}
	return 0;
	#else
	return 0;
	#endif
}

unsigned char twi_read_byte( unsigned char slave_addr, unsigned char reg_addr )
{
	#if IICFLAG
	unsigned char bufferdata;
	unsigned char result;
//	result = ucI2cRead(slave_addr, reg_addr, &bufferdata, 1);
	result = MApi_SWI2C_ReadBytes((MS_U16)slave_addr, 1, &reg_addr, 1, &bufferdata);
	if(result == 1) //read success
	{
		;//printf("%s Success!!!]\n",__FUNCTION__);
		return bufferdata;
	}
	else
	{
		printf("%s Error]\n",__FUNCTION__);
	}
	return 0;
	#else
	return 0;
	#endif
}

unsigned char twi_write_block( unsigned char slave_addr, unsigned char reg_addr, unsigned char *buf, unsigned short len )
{
	#if IICFLAG
//	ucI2cWrite(slave_addr, reg_addr, buf, len);
	if(MApi_SWI2C_WriteBytes((MS_U16)slave_addr, 1,&reg_addr, (MS_U16)len, buf))
	{
		;//printf("%s Success!!!]\n",__FUNCTION__);
	}
	else
	{
		printf("%s Error]\n",__FUNCTION__);
	}
	return 0;
	#else
	return 0;
	#endif
}

unsigned char twi_write_byte( unsigned char slave_addr, unsigned char reg_addr, unsigned char byte )
{
	MS_U16 Slave_i2c_addr=0;
		
	Slave_i2c_addr = slave_addr&0x00ff;	
	#if IICFLAG
//	ucI2cWrite(slave_addr, reg_addr, &byte, 1);
//	printf("Slave_i2c_addr=0x%x,reg_addr=0x%x,byte=0x%x\n",Slave_i2c_addr,reg_addr,byte);
	if(MApi_SWI2C_WriteBytes(Slave_i2c_addr, 1,&reg_addr, 1, &byte))
	{
		;
//		printf("%s Success!!!]\n",__FUNCTION__);
	}
	else
	{
		printf("%s Error]\n",__FUNCTION__);
	}
	return 0;
	#else
	return 0xff;
	#endif
}
#define HAL_VERSION_MAJOR               1
#define HAL_VERSION_MINOR               14
uint8_si HalVersion ( bool_si wantMajor )

{
    return( (wantMajor) ? HAL_VERSION_MAJOR : HAL_VERSION_MINOR );
}


bool_si Getcp1292_isMHLState(UINT8 statenum)
{
	 if(statenum == 0)
	 {
		if(g_currentInputMode == MHL)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	 }
	else
	{
		if(g_currentInputMode == HDMI)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

}

extern bool_si g_HPD_IN;
void SetHPDflag(bool_si flag)
{
	g_HPD_IN = flag;
}

 bool_si Cp1292runflag = false; 
void Setcp1292run(bool_si flag)
{
	if(flag == true)
		{
			Cp1292runflag = true;
		}
	else
		{
			Cp1292runflag = false;
		}
}
extern bool_si g_HDMI_Source_Connected;
extern bool_si g_MHL_Source_Connected;
bool_si CP1292HDMIconnectstate(void)
{
	return g_HDMI_Source_Connected;
}
bool_si CP1292MHLconnectstate(void)
{
	return g_MHL_Source_Connected;
}

