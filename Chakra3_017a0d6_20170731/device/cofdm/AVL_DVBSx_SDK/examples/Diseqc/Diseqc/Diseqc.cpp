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


// Diseqc.cpp : main project file.

#include "stdafx.h"

#if 1  //sdk files
#include "IBSP.h"
#include "Diseqc_source.h"
#endif

using namespace System;
using namespace System::IO;

int main(array<System::String ^> ^args)
{
	StreamReader^ sr;	
	System::String^ line;
	String^ strServerName;
	int iSocketPort;
	AVL_DVBSx_ErrorCode r=AVL_DVBSx_EC_OK;

#if 1  //load init parameters	

	if( !File::Exists("app.ini") )
	{
		Console::WriteLine( L"Can not find file app.ini");
		Console::WriteLine( L"Use default I2CServer parameters");
		strServerName = L"localhost";
		iSocketPort = 88;
	}
	else
	{
		sr = gcnew StreamReader("app.ini");     
		while( (line = sr->ReadLine()) != nullptr )
		{
			line = line->Trim();
			if( line->StartsWith("server") )
			{				
				strServerName = line->Substring(line->IndexOf('=')+1);
				strServerName->Trim();									
			}			
			else if( line->StartsWith("port") )
			{			
				line = line->Substring(line->IndexOf('=')+1);
				line->Trim();
				iSocketPort = Convert::ToInt32(line);								
			}
		}
		sr->Close();
	}
#endif

	Console::WriteLine(L"Example start...");

#if 1  //connect to i2cserver
	r = AVL_DVBSx_IBSP_Initialize(strServerName, iSocketPort);
	if( AVL_DVBSx_EC_OK !=  r)
	{
		Console::WriteLine( L"BSP Initialization failed!\nPlease check the app.ini for the server name and the port.\nPlease also make sure the I2CServer application is running in the server computer.");
		return 1;

	}
#endif

    r=Diseqc();
	AVL_DVBSx_Error_Dispose(r);

	Console::WriteLine(L"Example end...");
	return 1;

}
