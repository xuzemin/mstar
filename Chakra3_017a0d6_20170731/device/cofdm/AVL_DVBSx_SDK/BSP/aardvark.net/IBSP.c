/*
 *           Copyright 2010 Availink, Inc.
 *
 *  This software contains Availink proprietary information and
 *  its use and disclosure are restricted solely to the terms in
 *  the corresponding written license agreement. It shall not be 
 *  disclosed to anyone other than valid licensees without
 *  written permission of Availink, Inc.
 *
 */


//$Revision: 563 $
//$Date: 2008-09-24 17:24:29 -0400 (Wed, 24 Sep 2008) $
//
#include "avl.h"
#include "IBSP.h"

#using <System.dll>
using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;

/// Please use the following table of PLL configurations if 55 Msps symbol rate is desired at the demod end. 

///	{503,  1, 6, 4, 2,  4000, 12600, 16800, 25200} < Reference clock 4 MHz,   Demod clock 126 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
///	,{447,  1, 6, 4, 2,  4500, 12600, 16800, 25200} < Reference clock 4.5 MHz, Demod clock 126 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
///	,{503,  4, 6, 4, 2, 10000, 12600, 16800, 25200} < Reference clock 10 MHz,  Demod clock 126 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
///	,{503,  7, 6, 4, 2, 16000, 12600, 16800, 25200} < Reference clock 16 MHz,  Demod clock 126 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
///	,{111,  2, 6, 4, 2, 27000, 12600, 16800, 25200} < Reference clock 27 MHz,  Demod clock 126 MHz, FEC clock 168 MHz, MPEG clock 252 MHz

/// Feel free to contact Availink Support staff for further infromation on this.

/// Users can remove unused elements from the following array to reduce the SDK footprint size.
const struct AVL_DVBSx_PllConf pll_conf[] =
{
	 {503,  1, 7, 4, 2,  4000, 11200, 16800, 25200} ///< Reference clock 4 MHz,   Demod clock 112 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
	,{447,  1, 7, 4, 2,  4500, 11200, 16800, 25200} ///< Reference clock 4.5 MHz, Demod clock 112 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
	,{503,  4, 7, 4, 2, 10000, 11200, 16800, 25200} ///< Reference clock 10 MHz,  Demod clock 112 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
	,{503,  7, 7, 4, 2, 16000, 11200, 16800, 25200} ///< Reference clock 16 MHz,  Demod clock 112 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
	,{111,  2, 7, 4, 2, 27000, 11200, 16800, 25200} ///< Reference clock 27 MHz,  Demod clock 112 MHz, FEC clock 168 MHz, MPEG clock 252 MHz
};
const AVL_uint16 pll_array_size = sizeof(pll_conf)/sizeof(struct AVL_DVBSx_PllConf);

namespace AVL_GLOBAL
{
	public ref class AVL_global
	{
	public: static System::Net::Sockets::Socket^ ClientSocket;
	public: static array<AVL_uchar>^ I2CBuff;
	public: static array<AVL_uchar>^ GPIOBuff;
	public: static array<System::Threading::Semaphore^>^ g_semaphores;
	public: static unsigned char sem_ID;
	public: static System::Threading::Semaphore^ GPIO_sem;
	};
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_Initialize(System::String^ strServerName, int iPort)
{
#if 1
	if( 0 == strServerName->CompareTo("localhost") )
	{
		strServerName = Dns::GetHostName();
	}
	AVL_GLOBAL::AVL_global::ClientSocket = gcnew System::Net::Sockets::Socket(System::Net::Sockets::AddressFamily::InterNetwork, System::Net::Sockets::SocketType::Stream, System::Net::Sockets::ProtocolType::Tcp);
	AVL_GLOBAL::AVL_global::I2CBuff = gcnew array<AVL_uchar>(512);
	AVL_GLOBAL::AVL_global::GPIOBuff = gcnew array<AVL_uchar>(64);
	AVL_GLOBAL::AVL_global::g_semaphores = gcnew array<System::Threading::Semaphore^>(20);
	AVL_GLOBAL::AVL_global::GPIO_sem = gcnew System::Threading::Semaphore(1, 1);
	AVL_GLOBAL::AVL_global::sem_ID = 0;
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Connect(strServerName, iPort);
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		return(AVL_DVBSx_EC_GeneralFail);
	}

	AVL_GLOBAL::AVL_global::ClientSocket->ReceiveTimeout = 15000;		// 15 seconds
	AVL_GLOBAL::AVL_global::ClientSocket->SendTimeout = 15000;			// 15 seconds
#endif
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_Dispose(void)
{
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_Delay( AVL_uint32 uiMS )
{
	System::Threading::Thread::Sleep(uiMS);
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CRead(  const struct AVL_DVBSx_Chip * pAVLChip,  AVL_puchar pucBuff, AVL_puint16 puiSize )
{
	int i ,j;

	AVL_GLOBAL::AVL_global::I2CBuff[0] = 5;
	AVL_GLOBAL::AVL_global::I2CBuff[1] = 1;
	AVL_GLOBAL::AVL_global::I2CBuff[2] = (AVL_uchar) (*puiSize);
	AVL_GLOBAL::AVL_global::I2CBuff[3] = (AVL_uchar)(pAVLChip->m_SlaveAddr>>8);
	AVL_GLOBAL::AVL_global::I2CBuff[4] = (AVL_uchar)(pAVLChip->m_SlaveAddr);
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::I2CBuff, AVL_GLOBAL::AVL_global::I2CBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::I2CBuff);
		j = AVL_GLOBAL::AVL_global::I2CBuff[0];
		while( i<j )	  //the following loop code may not be used for ever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::I2CBuff[k2+i] = tempBuff[k2];
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		return(AVL_DVBSx_EC_I2CFail );
	}

	if( *puiSize != AVL_GLOBAL::AVL_global::I2CBuff[1] )
	{
		*puiSize = AVL_GLOBAL::AVL_global::I2CBuff[1];
		return(AVL_DVBSx_EC_I2CFail);
	}
	for( i=0; i<AVL_GLOBAL::AVL_global::I2CBuff[1]; i++ )
	{
		pucBuff[i] = AVL_GLOBAL::AVL_global::I2CBuff[i+2];
	}
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CWrite(  const struct AVL_DVBSx_Chip * pAVLChip,  AVL_puchar pucBuff,  AVL_puint16  puiSize )
{
	int i ,j;
	AVL_GLOBAL::AVL_global::I2CBuff[0] = 5+(*puiSize);
	AVL_GLOBAL::AVL_global::I2CBuff[1] = 0;
	AVL_GLOBAL::AVL_global::I2CBuff[2] = (AVL_uchar) (*puiSize);
	AVL_GLOBAL::AVL_global::I2CBuff[3] = (AVL_uchar)(pAVLChip->m_SlaveAddr>>8);
	AVL_GLOBAL::AVL_global::I2CBuff[4] = (AVL_uchar)(pAVLChip->m_SlaveAddr);
	for( i=0; i<(*puiSize); i++ )
	{
		AVL_GLOBAL::AVL_global::I2CBuff[5+i] = pucBuff[i];
	}
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::I2CBuff, AVL_GLOBAL::AVL_global::I2CBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::I2CBuff);
		j = AVL_GLOBAL::AVL_global::I2CBuff[0];
		while( i<j )	  //the following loop code may not be used for ever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::I2CBuff[k2+i] = tempBuff[k2];
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		return(AVL_DVBSx_EC_I2CFail );
	}

	if( *puiSize != AVL_GLOBAL::AVL_global::I2CBuff[1] )
	{
		return(AVL_DVBSx_EC_I2CFail);
	}
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_InitSemaphore( AVL_psemaphore pSemaphore )
{
	if( AVL_GLOBAL::AVL_global::sem_ID < AVL_GLOBAL::AVL_global::g_semaphores->Length )
	{
		*pSemaphore = AVL_GLOBAL::AVL_global::sem_ID;
		AVL_GLOBAL::AVL_global::g_semaphores[AVL_GLOBAL::AVL_global::sem_ID] = gcnew System::Threading::Semaphore(1, 1);
		AVL_GLOBAL::AVL_global::sem_ID ++;
		return(AVL_DVBSx_EC_OK);
	}
	else
	{
		return(AVL_DVBSx_EC_MemoryRunout);
	}
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_WaitSemaphore( AVL_psemaphore pSemaphore )
{
	if( *pSemaphore < AVL_GLOBAL::AVL_global::g_semaphores->Length )
	{
		if( nullptr != AVL_GLOBAL::AVL_global::g_semaphores[*pSemaphore] )
		{
			AVL_GLOBAL::AVL_global::g_semaphores[*pSemaphore]->WaitOne();
			return(AVL_DVBSx_EC_OK);
		}
	}
	return(AVL_DVBSx_EC_MemoryRunout);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_ReleaseSemaphore( AVL_psemaphore pSemaphore )
{
	if( *pSemaphore < AVL_GLOBAL::AVL_global::g_semaphores->Length )
	{
		if( nullptr != AVL_GLOBAL::AVL_global::g_semaphores[*pSemaphore] )
		{
			AVL_GLOBAL::AVL_global::g_semaphores[*pSemaphore]->Release();
			return(AVL_DVBSx_EC_OK);
		}
	}
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_AAGPIO_SetDirection( AVL_uchar ucDirectionMask )
{
	int i ,j;
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_GLOBAL::AVL_global::GPIO_sem->WaitOne();
	AVL_GLOBAL::AVL_global::GPIOBuff[0] = 4;		//package size
	AVL_GLOBAL::AVL_global::GPIOBuff[1] = 2;		//cmd
	AVL_GLOBAL::AVL_global::GPIOBuff[2] = 2;		//size
	AVL_GLOBAL::AVL_global::GPIOBuff[3] = ucDirectionMask;
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::GPIOBuff, AVL_GLOBAL::AVL_global::GPIOBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::GPIOBuff);
		j = AVL_GLOBAL::AVL_global::GPIOBuff[0];
		while( i<j )	  //the following loop code may not be used forever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::GPIOBuff[k2+i] = tempBuff[k2];
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		r = AVL_DVBSx_EC_BSP_ERROR1;
	}

	if( 0 != AVL_GLOBAL::AVL_global::GPIOBuff[1] )
	{
		r = AVL_DVBSx_EC_BSP_ERROR1;
	}
	AVL_GLOBAL::AVL_global::GPIO_sem->Release();
	return (r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_AAGPIO_SetValue( AVL_uchar ucValueMask )
{
		int i ,j;
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_GLOBAL::AVL_global::GPIO_sem->WaitOne();
	AVL_GLOBAL::AVL_global::GPIOBuff[0] = 4;		//package size
	AVL_GLOBAL::AVL_global::GPIOBuff[1] = 3;		//cmd
	AVL_GLOBAL::AVL_global::GPIOBuff[2] = 2;		//size
	AVL_GLOBAL::AVL_global::GPIOBuff[3] = ucValueMask;
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::GPIOBuff, AVL_GLOBAL::AVL_global::GPIOBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::GPIOBuff);
		j = AVL_GLOBAL::AVL_global::GPIOBuff[0];
		while( i<j )	  //the following loop code may not be used forever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::GPIOBuff[k2+i] = tempBuff[k2];
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		r = AVL_DVBSx_EC_BSP_ERROR1;
	}

	if( 0 != AVL_GLOBAL::AVL_global::GPIOBuff[1] )
	{
		r = AVL_DVBSx_EC_BSP_ERROR1;
	}
	AVL_GLOBAL::AVL_global::GPIO_sem->Release();
	return (r);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_AAGPIO_GetValue( AVL_puchar pucValueMask )
{
		int i ,j;
	AVL_DVBSx_ErrorCode r = AVL_DVBSx_EC_OK;
	AVL_GLOBAL::AVL_global::GPIO_sem->WaitOne();
	AVL_GLOBAL::AVL_global::GPIOBuff[0] = 3;		//package size
	AVL_GLOBAL::AVL_global::GPIOBuff[1] = 4;		//cmd
	AVL_GLOBAL::AVL_global::GPIOBuff[2] = 1;		//size
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::GPIOBuff, AVL_GLOBAL::AVL_global::GPIOBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::GPIOBuff);
		j = AVL_GLOBAL::AVL_global::GPIOBuff[0];
		while( i<j )	  //the following loop code may not be used forever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::GPIOBuff[k2+i] = tempBuff[k2];
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		r = AVL_DVBSx_EC_BSP_ERROR1;
	}

	if( 0 != AVL_GLOBAL::AVL_global::GPIOBuff[1] )
	{
		r = AVL_DVBSx_EC_BSP_ERROR1;
	}
	else
	{
		*pucValueMask = AVL_GLOBAL::AVL_global::GPIOBuff[2];
	}
	AVL_GLOBAL::AVL_global::GPIO_sem->Release();
	return (r);
}


AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CReadGeneric(AVL_uint16 uiSlaveAddr,  AVL_puchar pucBuff, AVL_puint16 puiSize)
{
	int i ,j; 

	AVL_GLOBAL::AVL_global::I2CBuff[0] = 5;
	AVL_GLOBAL::AVL_global::I2CBuff[1] = 1;
	AVL_GLOBAL::AVL_global::I2CBuff[2] = (AVL_uchar) (*puiSize);
	AVL_GLOBAL::AVL_global::I2CBuff[3] = (AVL_uchar)(uiSlaveAddr>>8);
	AVL_GLOBAL::AVL_global::I2CBuff[4] = (AVL_uchar)(uiSlaveAddr);
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::I2CBuff, AVL_GLOBAL::AVL_global::I2CBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::I2CBuff);
		j = AVL_GLOBAL::AVL_global::I2CBuff[0];
		while( i<j )	  //the following loop code may not be used for ever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::I2CBuff[k2+i] = tempBuff[k2]; 
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		return(AVL_DVBSx_EC_I2CFail );
	}

	if( *puiSize != AVL_GLOBAL::AVL_global::I2CBuff[1] )
	{
		*puiSize = AVL_GLOBAL::AVL_global::I2CBuff[1];
		return(AVL_DVBSx_EC_I2CFail);
	}
	if(AVL_GLOBAL::AVL_global::I2CBuff[1]==1)
	{
		*pucBuff = AVL_GLOBAL::AVL_global::I2CBuff[2];
	}
	else
	{
		for( i=0; i<AVL_GLOBAL::AVL_global::I2CBuff[1]; i++ )
		{
			pucBuff[i] = AVL_GLOBAL::AVL_global::I2CBuff[i+2];
		}
	}
	return(AVL_DVBSx_EC_OK);
}

AVL_DVBSx_ErrorCode AVL_DVBSx_IBSP_I2CWriteGeneric(AVL_uint16 uiSlaveAddr,  AVL_puchar pucBuff, AVL_puint16 puiSize)
{
	int i ,j; 
	AVL_GLOBAL::AVL_global::I2CBuff[0] = 5+(*puiSize);
	AVL_GLOBAL::AVL_global::I2CBuff[1] = 0;
	AVL_GLOBAL::AVL_global::I2CBuff[2] = (AVL_uchar) (*puiSize);
	AVL_GLOBAL::AVL_global::I2CBuff[3] = (AVL_uchar)(uiSlaveAddr>>8);
	AVL_GLOBAL::AVL_global::I2CBuff[4] = (AVL_uchar)(uiSlaveAddr);
	for( i=0; i<(*puiSize); i++ )
	{
		AVL_GLOBAL::AVL_global::I2CBuff[5+i] = pucBuff[i];
	}
	try
	{
		AVL_GLOBAL::AVL_global::ClientSocket->Send(AVL_GLOBAL::AVL_global::I2CBuff, AVL_GLOBAL::AVL_global::I2CBuff[0], Sockets::SocketFlags::None);
		i = AVL_GLOBAL::AVL_global::ClientSocket->Receive(AVL_GLOBAL::AVL_global::I2CBuff);
		j = AVL_GLOBAL::AVL_global::I2CBuff[0];
		while( i<j )	  //the following loop code may not be used for ever.
		{
			array<AVL_uchar> ^ tempBuff = gcnew array<AVL_uchar>(256);
			int k1, k2;
			k1 = AVL_GLOBAL::AVL_global::ClientSocket->Receive(tempBuff);
			for( k2=0; k2<k1; k2++ )
			{
				AVL_GLOBAL::AVL_global::I2CBuff[k2+i] = tempBuff[k2]; 
			}
			i += k1;
		}
	}
	catch( System::Net::Sockets::SocketException^ )
	{
		return(AVL_DVBSx_EC_I2CFail );
	}

	if( *puiSize != AVL_GLOBAL::AVL_global::I2CBuff[1] )
	{
		return(AVL_DVBSx_EC_I2CFail);
	}
	return(AVL_DVBSx_EC_OK);	

}

