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
// (MStar Confidential Information) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///@file drvuart.h
///@brief System functions:UART Module
/// This file is vaild when "ENABLE_MSTV_UART_DEBUG" is enable
/// The brief function is get the register content by UART without halt the whole
/// system.
//
///////////////////////////////////////////////////////////////////////////////

#define _DRVUART_C_
#include "Board.h"
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "msAPI_Timer.h"

#include "MApp_InputSource.h" //gchen  @ 20171219
#include "MApp_TopStateMachine.h" //gchen  @ 20171220
#include "Dlp_Optical.h" //gchen  @ 20171222
#include "drvGPIO.h" //gchen  @ 20171228


// Common Definition
#include "debug.h"
#include "apiXC.h"
#include "hwreg.h"
#include "drvUartDebug.h"
#include "sysinfo.h"
#include "drvIIC.h"
#include "apiXC_Dlc.h"
#include "SysInit.h"
#include "apiXC_Dlc.h"
#include "apiXC_DBC.h"
#include "apiGOP.h"
#include "drvGlobal.h"
#include "drvUART.h"
#include "Panel.h"
#include "msAPI_Ram.h"
#include "apiXC_Ace.h"
#include "apiXC_Sys.h"
#include "msAPI_audio.h"

#include "apiXC_Dlc.h"
#include "drvPWM.h"

#include "autotest.h"
#include "MApp_USBDownload.h"
#include "drvMmsDisp_if.h"

#include "MApp_SaveData.h"
#include "drvUSB.h"
#include "MApp_Scaler.h"
#include "MApp_ZUI_ACTglobal.h"

#include "MApp_AutoTest.h"
#include "SW_Config.h"

#ifdef MSOS_TYPE_LINUX
#include "madp.h"
#endif

#ifndef ATSC_SYSTEM
#include "COFDM_Demodulator.h"
#include "IF_Demodulator.h"
#if(ENABLE_DTV)
#include "mapp_si.h"
#endif
#if (ENABLE_DTV_EPG)
#include "mapp_eit.h"
#endif
#endif

#if (FRONTEND_TUNER_TYPE == MSTAR_MSR1200_TUNER)
#define CANOPUS_DEBUG 1
#else
#define CANOPUS_DEBUG 0
#endif

//#if (FRONTEND_DEMOD_TYPE == MSTAR_MSB1200_DEMOD || FRONTEND_DEMOD_TYPE == MSTAR_MSB1210_DEMOD || FRONTEND_DEMOD_TYPE == EMBEDDED_DVBT_DEMOD)
//#define PHOENIX_DEBUG   1
//#else
#define PHOENIX_DEBUG   0
//#endif


#if (ENABLE_SECURITY_R2)
#include "msAPI_SecurityR2.h"
#endif



#if (ENABLE_MSTV_UART_DEBUG)

#ifdef ATSC_SYSTEM
  #include "MApp_Key.h"
  #include "MApp_GlobalVar.h"
  #include "MApp_UiMenu.h"
#else
#include "MApp_Key.h"
#include "MApp_UiMenuDef.h"
#endif

#if(ENABLE_MFC_6M30)
#include "drvUrsa6M30.h"
#endif

#if(ENABLE_6M40_4KX2K_PROCESS)
#include "drvUrsa6M40.h"
#endif

// panel
#include "Panel.h"
#include "apiPNL.h"


//gchen @ 20180118 uart2
#include "mapp_videoplayer.h"



#define UARTMSG(x)    //x

#if (CHANNEL_SCAN_AUTO_TEST)
#define CHSCANTEST_MSG(x)    x
#else
#define CHSCANTEST_MSG(x)
#endif

static XDATA U16 u16ACE_Report_Type = 0;

#if ENABLE_AUTOTEST
extern BOOLEAN g_bAutobuildDebug;
#endif

#if (ENABLE_MMS)
int DbgSystem = 0;
int CatEye    = 0;
int UnitTest  = 0;

extern U8 ParaTbl[PARA_ROW_SIZE][PARA_COL_SIZE];


void MDrv_LogoPrint(void);
#endif
/******************************************************************************/
/// UART device: putchar and ISR
/******************************************************************************/

static MS_U32 uart_debug;
void putcharb(MS_U8 byte)
{
    if (uart_debug)
    {
        mdrv_uart_write(uart_debug, (MS_U8 *)&byte, 1);
    }
}

#if 0//(SUPPORT_PEQ_TOOL)
#define ENABLE_UART_CHECKSUM    1
#else
#define ENABLE_UART_CHECKSUM    1
#endif

#if( ENABLE_UART_CHECKSUM )
// Check uart protocal
bit IsUartCmdValid(void)
{
    BYTE i, ucLen;
    BYTE ucCS = 0;

    if( UART_EXT )
    {
        ucLen = UART_CMD_EXT_LENGTH;
    }
    else
    {
        ucLen = UART_CMD_LENGTH;
    }

    ucCS = 0;
    for( i = 0; i < ucLen; ++ i )
    {
        ucCS += g_UartCommand.Buffer[i];
    }

    if( ucCS == 0xFF )
        return 1;

    return 0;
}
#endif


void MDrv_UsbUpdate(void);
extern void msAPI_BLoader_Reboot(void);


void MDrv_UART_RecvHandler(int c)
{
#if( CHAKRA3_AUTO_TEST )
    MApp_AT_RecvDataHandler(c);

    if( MApp_AT_Is_NeedDisableOtherUartFunction() )
        return;
#endif
	printf("MDrv_UART_RecvHandler 111 \n");


    g_Uart0CheckTick = 50;// time-out control ms

    if (g_UartCommand.Index >= _UART_CMD_LENGTH_)
    {
        g_UartCommand.Index = 0;
    }

#if (ENABLE_MMS)
    // detect dash
    if ((0x2D == c)&& (1 == DbgMenuMode))
    {
        InputPara = 1;
    }

    // recieve byte
    if (!InputPara)
    {
#endif
        g_UartCommand.Buffer[g_UartCommand.Index] = c;
#if (ENABLE_MMS)
    } else
    {
        MDrv_MMS_ParseCmdParm(c);
    }

    // receive for menu mode
    if (1 == DbgMenuMode)
    {
        MDrv_MMS_UARTRecvHandler(c);
        return;
    }

#endif

    // check command buffer index
    if (UART_EXT)
    {
        if (g_UartCommand.Index == 0) // check 1st data
        {
            g_UartCommand.Index++; // for get UART_CMD_EXT_LENGTH
        }
        else
        {
            if (g_UartCommand.Index < UART_CMD_EXT_LENGTH) // still read command
            {
                g_UartCommand.Index++; // next index of command buffer
            }
            if (g_UartCommand.Index >= UART_CMD_EXT_LENGTH) // read command ok
            {
                g_bUart0Detected = TRUE; // command  buffer recieve ok
                g_UartCommand.Index = 0; // reset index of command buffer
                g_Uart0CheckTick = 0;
            }
        }
    }
    else
    {
        if (g_UartCommand.Index < UART_CMD_LENGTH) // still read command
        {
            g_UartCommand.Index++; // next index of command buffer
        }
        if (g_UartCommand.Index >= UART_CMD_LENGTH) // read command ok
        {
            // check if Enter Key. (0x0D)
            if (g_UartCommand.Buffer[_UART_CMD_CODE_] == 0x0D) {
              #if (ENABLE_MMS)
                //set flag to enter menu mode
                DbgMenuMode = 1;
                MDrv_LogoPrint();
                if (!(DbgMenuLevel ||CatMenuLevel || CfgMenuLevel || UntMenuLevel))
                    MDrv_MainPagePrint();
               #endif
            }

        #if( ENABLE_UART_CHECKSUM )
            if( IsUartCmdValid() )
        #endif
           {
            g_bUart0Detected = TRUE; // command  buffer recieve ok
            }
            g_UartCommand.Index = 0; // reset index of command buffer
            g_Uart0CheckTick = 0;
        }
    }

    #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
        MsOS_EnableInterrupt(E_INT_IRQ_UART0);
    #endif
}


/******************************************************************************/
///Initial UART relative variable and flag.
/******************************************************************************/
void MDrv_UART_DebugInit(void)
{
    // reset Uart variables

    g_UartCommand.Index = 0;

    g_bDebugASCIICommandFlag = 0;
    g_bDebugProgStopFlag = FALSE;

    g_Uart0CheckTick = 0;

#if defined(__AEONR2__)// HK = R2
    uart_debug = mdrv_uart_open(E_UART_AEON_R2);
#else// HK = Aeon
    uart_debug = mdrv_uart_open(E_UART_AEON);
#endif

    if (uart_debug)
    {
        mdrv_uart_set_rx_callback(uart_debug, MDrv_UART_RecvHandler);
    }

/*#if (CHANNEL_SCAN_AUTO_TEST)
    g_ScanAutoTestData.u12ChNum = 0;
#endif*/
}

#if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
#ifndef MSOS_TYPE_LINUX
extern U8 MDrv_USBGetPortEnableStatus(void);
//extern void MApp_ZUI_SwUpdate_ProgressBar(U8 percent);

extern void msAPI_BLoader_Reboot(void);
extern BOOLEAN MDrv_UsbDeviceConnect(void);
#endif
#endif
//extern void MApp_UsbDownload_Monitor(void);
#if (TV_FREQ_SHIFT_CLOCK)
extern void _TVShiftClk(AVD_ATV_CLK_TYPE u8Mode);
extern void msAPI_Tuner_Patch_ResetTVShiftClk(void);
#endif

U8  gucDebugData0   = 0x00;
U8  gucDebugData1   = 0x00;
U16 gu16DebugData2  = 0x0000;
U16 gu16DebugData3  = 0x0000;

void MDrv_UART_ExecUserDefinedCommand(void)
{
    //BYTE ucMainCmd = g_UartCommand.Buffer[_UART_CMD_CODE_];
    //BYTE ucSubCmd0 = g_UartCommand.Buffer[_UART_CMD_INDEX1_];
    BYTE ucSubCmd1 = g_UartCommand.Buffer[_UART_CMD_INDEX2_];
    BYTE ucPara1   = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    BYTE ucPara2   = g_UartCommand.Buffer[_UART_CMD_INDEX4_];
    //BYTE ucPara3   = g_UartCommand.Buffer[_UART_CMD_INDEX5_];

    switch( ucSubCmd1 )
    {
        case 0x00:// add for help!
            printf("\n~~~~User Defined Command~~~~");
            printf("\n [60 01]: Set Debug Variable(gucDebugData0, gucDebugData1)!");
            printf("\n [60 02]: ");
            printf("\n [60 03]: ");
            printf("\n [60 04]: ");
            printf("\n [60 05]: ");
            printf("\n~~~~~~~~~~~~~End~~~~~~~~~~~~\n");
            break;

        case 0x01:
            printf("\n[60 01]: Set Debug Variable(gucDebugData0, gucDebugData1):\n");
            gucDebugData0 = ucPara1;
            gucDebugData1 = ucPara2;
            printf("    gucDebugData0 = 0x%X\n", gucDebugData0);    // Fixed coverity CID33197.
            printf("    gucDebugData1 = 0x%X\n", gucDebugData1);    // Fixed coverity CID33198.
            break;

        case 0x02:
            printf("\n[60 02]: Set Debug Variable(gu16DebugData2):\n");
            gu16DebugData2 = ( (U16)ucPara1 << 8 ) | ( ucPara2 );
            printf("\n    gu16DebugData2 = 0x%X\n", gu16DebugData2);    // Fixed coverity CID33199.
            break;

        case 0x03:
            printf("\n[60 03]: Set Debug Variable(gu16DebugData3):\n");
            gu16DebugData3 = ( (U16)ucPara1 << 8 ) | ( ucPara2 );
            printf("\n    gu16DebugData3 = 0x%X\n", gu16DebugData3);    // Fixed coverity CID33200.
            break;

    #if (INPUT_HDMI_VIDEO_COUNT > 0)
      #if (ENABLE_MHL == ENABLE && MHL_TYPE!=MHL_TYPE_INTERNAL) // MHL
        case 0x04:
            {
                extern MS_U16 msReadWord(MS_U16 reg);

                printf("\n[60 04]: Check i2c is good for MHL!\n");
                printf("    [GOOD: REG_0203=0x0025]---0x%X\n", msReadWord(0x0203));
                printf("    [GOOD: REG_0000=0x01C8]---0x%X\n", msReadWord(0x0000));
            }
            break;
      #endif
    #endif

        default:
            break;

    }
}

void MDrv_UART_ExecTestCommand(void)
{
    switch( g_UartCommand.Buffer[_UART_CMD_INDEX1_] )
    {
        case 0x60:
            MDrv_UART_ExecUserDefinedCommand();
            break;

    #if(ENABLE_UART2)
      #if(ENABLE_UART2_TEST)
        case 0x4B:
            printf("[4B]UART2_TXD >> 12345678\n");
            MDrv_UART2_TestTXD();
            break;
      #endif
    #endif

        case 0x50:
            g_bDebugProgStopFlag = !g_bDebugProgStopFlag;
            if( g_bDebugProgStopFlag )
            {
                printf("<Debug>\r\n");
            }
            else
            {
                printf("<Free>\r\n");
            }
            break;

    #if (TV_FREQ_SHIFT_CLOCK)
        case 0x51:
        {
            msAPI_Tuner_Patch_ResetTVShiftClk();
            _TVShiftClk((AVD_ATV_CLK_TYPE) g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            break;
        }
    #endif

        case 0x53:
        {
            MApi_AUDIO_ADVSOUND_SubProcessEnable( ((ADVFUNC)g_UartCommand.Buffer[_UART_CMD_INDEX2_]), ((WORD)g_UartCommand.Buffer[_UART_CMD_INDEX3_]<<8) + ((WORD)g_UartCommand.Buffer[_UART_CMD_INDEX4_]));
            printf("\r\n SRS CMD = %x %x", g_UartCommand.Buffer[_UART_CMD_INDEX2_],g_UartCommand.Buffer[_UART_CMD_INDEX3_]);

            break;
        }


        case 0x54:
        {
            MApi_AUDIO_ADVSOUND_SetParam( ((ADVSND_PARAM)g_UartCommand.Buffer[_UART_CMD_INDEX2_]), ((WORD)g_UartCommand.Buffer[_UART_CMD_INDEX3_]<<8) + ((WORD)g_UartCommand.Buffer[_UART_CMD_INDEX4_]),0);
            printf("\r\n SRS CMD = %x %x %x", g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_] , g_UartCommand.Buffer[_UART_CMD_INDEX4_]);

            break;
        }


    #if (SUPPORT_PEQ_TOOL)
        case 0x59:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(0, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;

        case 0x5A:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(1, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;

        case 0x5B:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(2, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;

        case 0x5C:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(3, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;

        case 0x5D:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(4, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;
      #if (PEQ_BANDS == 8)
        case 0x5E:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(5, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;

        case 0x5F:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(6, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;

        case 0x61:
            printf("G %d ",g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            printf("Fh %d ",g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            printf("Fl %d ",g_UartCommand.Buffer[_UART_CMD_INDEX4_]);
            printf("Q %d\r\n",g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            msAPI_AUD_SetPEQ(7, g_UartCommand.Buffer[_UART_CMD_INDEX2_], g_UartCommand.Buffer[_UART_CMD_INDEX3_], g_UartCommand.Buffer[_UART_CMD_INDEX4_], g_UartCommand.Buffer[_UART_CMD_INDEX5_]);
            break;
      #endif
    #endif

        case 0x63:  // Keypad Up
            u8KeyCode = KEY_UP;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;


    #if DYNAMIC_VECTOR_FONT_ENABLE
        case 0x64:
        {
            extern void msAPI_MVF_test(void);
            msAPI_MVF_test();

            break;
        }


        case 0x65:
        {
            extern void msAPI_MVF_LoadFont(void);
            msAPI_MVF_LoadFont();

            break;
        }
    #endif // #if DYNAMIC_VECTOR_FONT_ENABLE


        case 0x66:
        {
			//gchen add @ 20171218
			MApp_InputSource_SwitchSource( UI_INPUT_SOURCE_DMP, MAIN_WINDOW );
			MApp_TopStateMachine_SetTopState(STATE_TOP_DMP); //gchen @ 20171220
            break;
        }


        case 0x67:
        {
        #if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
            U8 u8PortEnStatus = 0;

            MDrv_UsbDeviceConnect();
            printf("USB SW Update!\n");
            u8PortEnStatus = MDrv_USBGetPortEnableStatus();
			#if 0 //gchen  @ 20171215 //usb update port
			if((u8PortEnStatus & BIT0) == BIT0)
            {
                MDrv_UsbDeviceConnect();
                MApp_UsbDownload_Init(BIT0, NULL);
            }
            else
			#endif
			if((u8PortEnStatus & BIT1) == BIT1)
            {
            	MDrv_UsbDeviceConnect();
                MApp_UsbDownload_Init(BIT1, NULL);
            }
            else
            {
                printf("Error> Unknown USB port\n");
                return;
            }

            if(!MW_UsbDownload_Search())
            {
                break;
            }

            if (MW_UsbDownload_Start())
            {
                msAPI_BLoader_Reboot();
            }
        #endif

            break;
        }

		case 0x68:
		{
			//gchen add @ 20171218
			//keystone_correction(0);
			AMP_ENABLE();
			
			break;
		}

		case 0x69:
		{
			//gchen add @ 20171218
			//keystone_correction(10);
			AMP_DISABLE();
			
			break;
		}

		case 0x6a:
		{
			//gchen add @ 20171218
			Power_Off();
			break;
		}

		
		case 0x6b:
		{
			//gchen add @ 20171218
			LEDPWR_ENABLE();
			break;
		}

		case 0x6c:
		{
			//gchen add @ 20171218
			LEDPWR_DISABLE();
		
			break;
		}


		case 0x6d:
		{
			//gchen add @ 20171218
			
			Optical_SetRes_854x480();

			MsOS_DelayTask(3000);
			
			break;
		}

		case 0x6e:
		{
			//gchen add @ 20171218
			Optical_Led_OpenANDClose(1);
		
			MsOS_DelayTask(3000);
		
			break;
		}

		case 0x6f:
		{
			//gchen add @ 20171218
			Optical_Led_OpenANDClose(0);

			MsOS_DelayTask(3000);

			break;
		}


    #if (ENABLE_SECURITY_R2_HDCP22)
        case 0x6F:
        {
            u8PrintHdcp22DebugInfo = 1 - u8PrintHdcp22DebugInfo;
            if(u8PrintHdcp22DebugInfo)
            {
                printf("<HDCP2.2 debug mode>");
            }
            else
            {
                printf("<HDCP2.2 release mode>");
            }

            break;
        }
    #endif



        case 0x72:  // Keypad Left
            u8KeyCode = KEY_LEFT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x73:  // Keypad Menu
            u8KeyCode = KEY_MENU;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x74:  // Keypad Right
            u8KeyCode = KEY_RIGHT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x75:  // Keypad Source
            u8KeyCode = KEY_INPUT_SOURCE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x76:  // Keypad Power
            u8KeyCode = KEY_POWER;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;


    #if(ENABLE_3D_PROCESS)
        case 0x80:
        {
            printf("DEBUG 3D ");

            switch(g_UartCommand.Buffer[_UART_CMD_INDEX2_])
            {
                case 0x00:
                    DB_3D_SETTING.en3DType = EN_3D_BYPASS;
                    printf("[80 00] >> EN_3D_BYPASS\n");
                    break;
                case 0x01:
                    DB_3D_SETTING.en3DType = EN_3D_SIDE_BY_SIDE;
                    printf("[80 01] >> EN_3D_SIDE_BY_SIDE\n");
                    break;
                case 0x02:
                    DB_3D_SETTING.en3DType = EN_3D_TOP_BOTTOM;
                    printf("[80 02] >> EN_3D_TOP_BOTTOM\n");
                    break;
                case 0x03:
                    DB_3D_SETTING.en3DType = EN_3D_LINE_ALTERNATIVE;
                    printf("[80 03] >> EN_3D_LINE_ALTERNATIVE\n");
                    break;
                case 0x04:
                    DB_3D_SETTING.en3DType = EN_3D_FRAME_ALTERNATIVE;
                    printf("[80 04] >> EN_3D_FRAME_ALTERNATIVE\n");
                    break;
                case 0x05:
                    DB_3D_SETTING.en3DType = EN_3D_FRAME_PACKING;
                    printf("[80 05] >> EN_3D_FRAME_PACKING\n");
                    break;
                case 0x06:
                    DB_3D_SETTING.en3DType = EN_3D_2DConvertTo3D;
                    printf("[80 06] >> EN_3D_NORMAL_2D\n");
                    break;
                case 0x07:
                    MApi_XC_Set_3D_LR_Frame_Exchg(MAIN_WINDOW);
                    printf("[80 07] >> 3D LR Frame \n");
                    break;
                default:
                    DB_3D_SETTING.en3DType = EN_3D_BYPASS;
                    printf("[80 Other] >> EN_3D_BYPASS\n");
                    break;
            }

            if(!MApi_XC_IsCurrentFrameBufferLessMode())
            {
            #if ENABLE_NEW_3D_FLOW
                msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                MApp_Scaler_EnableManualDetectTiming(TRUE);
                MApp_Scaler_SetVideo3DMode(DB_3D_SETTING.en3DType);
                MApi_XC_Set_3D_LR_Frame_Exchg(MAIN_WINDOW);
                msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            #else
                E_XC_3D_INPUT_MODE eInput3DMode;
                msAPI_Scaler_SetBlueScreen( ENABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
                eInput3DMode = MAPP_Scaler_MapUI3DModeToXCInput3DMode(DB_3D_SETTING.en3DType);
                MApp_Scaler_EnableManualDetectTiming(TRUE);
                MApp_Scaler_SetVideo3DMode(MAPP_Scaler_Map3DFormatTo3DUserMode(eInput3DMode));
                MApi_XC_Set_3D_LR_Frame_Exchg(MAIN_WINDOW);
                msAPI_Scaler_SetBlueScreen( DISABLE, E_XC_FREE_RUN_COLOR_BLACK, DEFAULT_SCREEN_UNMUTE_TIME, MAIN_WINDOW);
            #endif
            }

            break;
        }
    #endif // #if(ENABLE_3D_PROCESS)


        case 0x83:  // Keypad Down
            u8KeyCode = KEY_DOWN;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;

        case 0x84:  // IRKEY_EXIT
            u8KeyCode = KEY_EXIT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;

      #if ENABLE_DMP
        case 0x86:  // IRKEY_PAUSE
            u8KeyCode = KEY_PAUSE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x87:  // IRKEY_PLAY
            u8KeyCode = KEY_PLAY;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
      #endif

        case 0x90:  // Irkey Input
            u8KeyCode = KEY_INPUT_SOURCE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x91:  // Irkey Sleep
            u8KeyCode = KEY_SLEEP;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x92:  // Irkey 1
            u8KeyCode = KEY_1;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x93:  // Irkey 4
            u8KeyCode = KEY_4;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x94:  // Irkey 7
            u8KeyCode = KEY_7;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x95:  // Irkey 0
            u8KeyCode = KEY_0;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x96:  // Irkey Select
            u8KeyCode = KEY_SELECT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0x97:  // Irkey Menu
            u8KeyCode = KEY_MENU;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA1:  // Irkey Display
            u8KeyCode = KEY_INFO;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA2:  // Irkey 2
            u8KeyCode = KEY_2;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA3:  // Irkey 5
            u8KeyCode = KEY_5;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA4:  // Irkey 8
            u8KeyCode = KEY_8;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA5:  // Irkey -
            u8KeyCode = KEY_DASH;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA6:  // Irkey Up
            u8KeyCode = KEY_INPUT_SOURCE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xA7:  // Irkey Left
            u8KeyCode = KEY_LEFT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB1:  // Irkey MTS
            u8KeyCode = KEY_MTS;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB2:  // Irkey 3
            u8KeyCode = KEY_3;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB3:  // Irkey 6
            u8KeyCode = KEY_6;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB4:  // Irkey 9
            u8KeyCode = KEY_9;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
//        case 0xB5:  // Irkey CC
//            u8KeyCode = KEY_CC;
//            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
//            break;
        case 0xB5:  // Irkey Freeze
            u8KeyCode = KEY_FREEZE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB6:  // Irkey Zoom
            u8KeyCode = KEY_ZOOM;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB7:  // Irkey Right
            u8KeyCode = KEY_RIGHT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xB8:  // Irkey Exit
            u8KeyCode = KEY_EXIT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;


    #ifndef ATSC_SYSTEM

      #if ENABLE_DTV
        case 0xBA:
            //devCOFDM_Init();
            break;
      #endif

      #if (ENABLE_DTV_EPG)
        case 0xBB:
        {
            MS_EIT_CUR_EVENT_PF astEventInfo[2];
            if(MApp_EIT_GetCurPFInfo(astEventInfo) == FALSE)break;
            printf("\nf:><VersionNUm-Cur:%u>\n",astEventInfo ->version_number);
            if(MApp_EIT_Is_Cur_PF_Change())
            printf("Version Changing\n");
                else
            printf("VC End\n");
        }
        break;
      #endif  //#if (ENABLE_DTV_EPG)

    #endif // #ifndef ATSC_SYSTEM


        case 0xBC:
            break;

        case 0xCA:
            printf("enable gwin\n");
            MApi_GOP_GWIN_Enable(g_UartCommand.Buffer[_UART_CMD_INDEX2_],TRUE);
            break;

        case 0xCB:
            printf("disable gwin\n");
            MApi_GOP_GWIN_Enable(g_UartCommand.Buffer[_UART_CMD_INDEX2_],FALSE);
            break;


        case 0xC1:  // Irkey Mute
            u8KeyCode = KEY_MUTE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xC2:  // Irkey Vol+
            u8KeyCode = KEY_VOLUME_PLUS;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xC3:  // Irkey Vol-
            u8KeyCode = KEY_VOLUME_MINUS;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xC4:  // Irkey Ch+
            u8KeyCode = KEY_CHANNEL_PLUS;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xC5:  // Irkey Ch-
            u8KeyCode = KEY_CHANNEL_MINUS;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xC6:  // Irkey Picture
            u8KeyCode = KEY_PICTURE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xC7:  // Irkey Down
            u8KeyCode = KEY_DOWN;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;


        case 0xCC:
        {
            extern MS_BOOL MDrv_FLASH_ReadStatusRegister(MS_U8 *pu8StatusReg);
            extern MS_BOOL MDrv_FLASH_ReadStatusRegister2(MS_U8 *pu8StatusReg);
            U8 status;
            MDrv_FLASH_ReadStatusRegister(&status);
            printf("-status1=%x----\n",status);
            MDrv_FLASH_ReadStatusRegister2(&status);
            printf("-status2=%x----\n",status);

            break;
        }

        case 0xCE:
            printf("ChangeHdmiDviAudioMode\n");
          #if HDMI_DVI_AUDIO_MODE_CONFIG
            MApp_UiMenuFunc_ChangeHdmiDviAudioMode(1);
          #endif
            break;


        case 0xD0:  // Irkey Power
            u8KeyCode = KEY_POWER;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xD1:  // Irkey List
            u8KeyCode = KEY_CHANNEL_LIST;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xD2:  // Irkey Fav
            u8KeyCode = KEY_CHANNEL_FAV_LIST;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xD3:  // Irkey Sound
            u8KeyCode = KEY_AUDIO;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
//        case 0xD4:  // Irkey GUID
//            u8KeyCode = KEY_GUIDE;
//            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xD5:  // Irkey EPG
            u8KeyCode = KEY_EPG;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xD6:  // Irkey EXIT
            u8KeyCode = KEY_EXIT;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;
        case 0xD7:  // Irkey Up
            u8KeyCode = KEY_UP;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;

        case 0xD8:  // Keypad Menu
        printf("\n ** TTX **\n");
            u8KeyCode = KEY_TTX;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;

        case 0xD9:  // Keypad Menu
        printf("\n ** TTX D9 **\n");
            u8KeyCode = KEY_TTX_MODE;
            u32MonitorOsdTimer = msAPI_Timer_GetTime0();
            break;


       case 0xDA:
        {
            printf("change to 1080p60\n");
            MApp_ZUI_ACT_ShutdownOSD();
            g_PNL_TypeSel = PNL_FULLHD_CMO216_H1L01;
            msAPI_Scaler_ChangePanelType(g_PNL_TypeSel,MAIN_WINDOW);

            break;
        }


        case 0xDB:
        {
            printf("change to 1080p30\n");
            MApp_ZUI_ACT_ShutdownOSD();
            g_PNL_TypeSel = PNL_LVDS_1080P30;
            msAPI_Scaler_ChangePanelType(g_PNL_TypeSel,MAIN_WINDOW);

            break;
        }

        case 0xDC:
            break;



    #if(ENABLE_6M40_4KX2K_PROCESS)

        case 0xE0:
        {
        #if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
            U8 u8PortEnStatus = 0;

            MDrv_Ursa_USB_Update_SetChipType(SWUpdateForMFC);
            printf("USB MFC SW Update!\n");
            u8PortEnStatus = MDrv_USBGetPortEnableStatus();
            if((u8PortEnStatus & BIT0) == BIT0)
            {
                MApp_UsbDownload_Init(BIT0, NULL);//MApp_ZUI_SwUpdate_ProgressBar);
            }
            else if((u8PortEnStatus & BIT1) == BIT1)
            {
                MApp_UsbDownload_Init(BIT1, NULL);//MApp_ZUI_SwUpdate_ProgressBar);
            }
            else
            {
                MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
                printf("Error> Unknown USB port\n");
                return;
            }

            if(!MW_UsbDownload_Search())
            {
                MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
                break;
            }

            if (MW_UsbDownload_Start())
            {
                msAPI_BLoader_Reboot();
            }
        #endif

            break;
        }


        case 0xE1:
            printf(">>SET_VIDEO_MUTE_OFF \n");
            MDrv_Ursa_6M40_VIDEO_Enalbe(DISABLE);
            break;
        case 0xE2:
            printf(">>SET_VIDEO_MUTE_ON \n");
            MDrv_Ursa_6M40_VIDEO_Enalbe(ENABLE);
            break;
        case 0xE3:
            printf(">>SET_LVDS_DISABLE \n");
            MDrv_Ursa_6M40_LVDS_Enalbe(DISABLE);
            break;
        case 0xE4:
            printf(">>SET_LVDS_ENABLE \n");
            MDrv_Ursa_6M40_LVDS_Enalbe(ENABLE);
            break;
        case 0xE5:
            printf(">>Frame_Interleave_5x \n");//frame interleave 5x
            MDrv_Ursa_6M40_3D_MODE(PANEL_3D_MODE_FRAME_INTERLEAVE_25X);
            break;
        case 0xE6:
            printf("set debug port as MFC\n ");
            MDrv_Ursa_USB_Update_SetChipType(SWUpdateForMFC);
            break;
        case 0xE7:
            printf("set debug port as HK\n ");
            MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
            break;
        case 0xE8:
        {
            printf(" set MFC_Level\n ");
            MDrv_Ursa_6M40_MFC_Level((EN_6M40_MEMC_LEVEL)g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
            break;
        }

        case 0xE9:
        {
            EN_URSA_4K2K_MODE en4k2kmode=E_URSA_4K2K_MODE_FULLHD;
            switch(g_UartCommand.Buffer[_UART_CMD_INDEX2_])
            {
               case 0:
                    en4k2kmode=E_URSA_4K2K_MODE_FULLHD;
                    printf("set 4K2K_MODE E_URSA_4K2K_MODE_FULLHD \n");
                    break;
                case 1:
                    en4k2kmode=E_URSA_4K2K_MODE_4K1K;
                    printf(" set 4K2K_MODE E_URSA_4K2K_MODE_4K1K\n ");
                break;
                case 2:
                   en4k2kmode=E_URSA_4K2K_MODE_4K2K;
                    printf("set 4K2K_MODE E_URSA_4K2K_MODE_4K2K \n");
                break;
                case 3:
                    en4k2kmode=E_URSA_4K2K_MODE_HDMI4K2K;
                    printf(" set 4K2K_MODE E_URSA_4K2K_MODE_HDMI4K2K \n");
                break;
                default:
                    en4k2kmode=E_URSA_4K2K_MODE_FULLHD;
                    printf(" set 4K2K_MODE E_URSA_4K2K_MODE_FULLHD\n ");
                break;
            }
            MDrv_Ursa_6M40_Set4K2KType(en4k2kmode);

            break;
        }


        case 0xEA:
        {
            U8   en4k2kmode;
            MDrv_Ursa_6M40_Get4K2KType(&en4k2kmode);
            printf(" GET_4K2K_MODE  en4k2kmode=%d\n" ,en4k2kmode);

            break;
        }

        case 0xEB:
        {
            U8 pqlevel  =0;//EN_6M40_NR_OFF;
            switch(g_UartCommand.Buffer[_UART_CMD_INDEX2_])
            {
                case 0:
                    pqlevel  =(U8)EN_6M40_NR_OFF;
                    break;
                case 1:
                    pqlevel  =(U8)EN_6M40_NR_LOW;
                    break;
                case 2:
                    pqlevel  =(U8)EN_6M40_NR_MIDDLE;
                    break;
                case 3:
                    pqlevel  =(U8)EN_6M40_NR_HIGH;
                    break;
                    default:
                    pqlevel  =EN_6M40_NR_MIDDLE;
            }
            printf(" UC_SET_ACE_LEVEL_NR    pqlevel=%d\n" ,pqlevel);
            MDrv_Ursa_6M40_Cmd(UC_SET_ACE_LEVEL_NR,&pqlevel);

            break;
        }

    #endif // #if(ENABLE_6M40_4KX2K_PROCESS)


    #if(ENABLE_MFC_6M30)
        case 0xE0:
        {
        #if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
            U8 u8PortEnStatus = 0;

            MDrv_Ursa_USB_Update_SetChipType(SWUpdateForMFC);
            printf("USB MFC SW Update!\n");
            u8PortEnStatus = MDrv_USBGetPortEnableStatus();
            if((u8PortEnStatus & BIT0) == BIT0)
            {
                MApp_UsbDownload_Init(BIT0, NULL);//MApp_ZUI_SwUpdate_ProgressBar);
            }
            else if((u8PortEnStatus & BIT1) == BIT1)
            {
                MApp_UsbDownload_Init(BIT1, NULL);//MApp_ZUI_SwUpdate_ProgressBar);
            }
            else
            {
                MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
                printf("Error> Unknown USB port\n");
                return;
            }

            if(!MW_UsbDownload_Search())
            {
                MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
                break;
            }

            if (MW_UsbDownload_Start())
            {
                msAPI_BLoader_Reboot();
            }
        #endif

            break;
        }


        case 0xE1:
            printf(">>SET_VIDEO_MUTE_OFF \n");
            MDrv_Ursa_6M30_VIDEO_Enalbe(DISABLE);
            break;
        case 0xE2:
            printf(">>SET_VIDEO_MUTE_ON \n");
            MDrv_Ursa_6M30_VIDEO_Enalbe(ENABLE);
            break;
        case 0xE3:
            printf(">>3D_OFF \n");
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_NONE);
            break;
        case 0xE4:
            printf(">>3D_SBS \n");
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_SIDE_BY_SIDE_2X);
            break;
        case 0xE5:
            printf(">>3D_TB \n");
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_TOP_BOTTOM_2X);
            break;
        case 0xE6:
            printf(">>Frame_Interleave_5x \n");//frame interleave 5x
            MDrv_Ursa_6M30_3D_MODE(PANEL_3D_MODE_FRAME_INTERLEAVE_25X);
            break;
        case 0xE7:
            printf(">>Set debug port as MFC\n ");
            MDrv_Ursa_USB_Update_SetChipType(SWUpdateForMFC);
            break;
        case 0xE8:
            printf(">>Set debug port as HK\n ");
            MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
            break;

    #endif // #if(ENABLE_MFC_6M30)


        default:
            break;
    }

}

/******************************************************************************/
/// Decode the Command gets from UART port for main chip.
/// Command Buffer [0]:
///  -bit7~bit5 :Command length:1 ~ 6
///  -bit4~bit0 :UART command
/// Command Buffer [1]:
///  -Control address high.
/// Command Buffer [2]:
///  -Control address low.
/// if write command:
///   -Command buffer [3]: control data
/******************************************************************************/
void MDrv_UART_DecodeNormalCommand(void)
{
    //printf("MDrv_UART_DecodeNormalCommand %x\n", (U16)UART_CMD );
    U8 u8Value= 0;
#if PHOENIX_DEBUG
    U16 RegAddr, RegData;
#endif
    U16 u16EEADDR;

    switch ( UART_CMD )
    {
        case uartWrite_MST_Bank_n:
            MDrv_WriteByte(((U8)UART_CMD_MS_BANK_H << 16) |
                           ((U8)UART_CMD_MS_BANK_L << 8)  |
                            (U8)UART_CMD_MS_REGINDEX,
                                UART_CMD_MS_REGDATA
                          );
            putcharb( 0xF1 );
            break;
        case uartRead_MST_Bank_n:
        #if(ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
           MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
        #endif
            putcharb( 0xF2 );
            putcharb(MDrv_ReadByte(((U8)UART_CMD_MS_BANK_H << 16) |
                                   ((U8)UART_CMD_MS_BANK_L << 8)  |
                                   (U8)UART_CMD_MS_REGINDEX
                                  )
                    );
            break;
        case uartWrite_MCU_XDATA:

          #if(ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
           if((UART_CMD_MCU_IDX_H2>=0x10)&&(UART_CMD_MCU_IDX_H2<=0x3F))
           {
                   if(MDrv_Ursa_USB_Update_GetChipType() == SWUpdateForMFC)
                   {
                          MDrv_Ursa_6M30_Set_Value((((U8)UART_CMD_MCU_IDX_H2<<8)|(U8)UART_CMD_MCU_IDX_L),UART_CMD_MCU_DATA);
                          printf("N");
                   }
                   else
                   {
                         MDrv_WriteByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                                        ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                                         (U8)UART_CMD_MCU_IDX_L,
                                             UART_CMD_MCU_DATA
                                       );
                   }
           }
          else
        #elif(ENABLE_6M40_4KX2K_PROCESS)
           if((UART_CMD_MCU_IDX_H2>=0x10)&&(UART_CMD_MCU_IDX_H2<=0x3F))
           {
                   if(MDrv_Ursa_USB_Update_GetChipType() == SWUpdateForMFC)
                   {
                          MDrv_Ursa_6M40_Set_Value((((U8)UART_CMD_MCU_IDX_H2<<8)|(U8)UART_CMD_MCU_IDX_L),UART_CMD_MCU_DATA);
                          printf("N");
                   }
                   else
                   {
                         MDrv_WriteByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                                        ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                                         (U8)UART_CMD_MCU_IDX_L,
                                             UART_CMD_MCU_DATA
                                       );
                   }
           }
           else
        #endif
           {
            #if (ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
               MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
            #endif
             MDrv_WriteByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                           ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                            (U8)UART_CMD_MCU_IDX_L,
                                UART_CMD_MCU_DATA
                          );
            }
            putcharb( 0xF1 );
            // MDrv_WriteByte(((U8)UART_CMD_MCU_IDX_H<<8) | (U8)UART_CMD_MCU_IDX_L, UART_CMD_MCU_DATA);
            //putcharb(0xF1);
            break;
        case uartRead_MCU_XDATA:

       #if(ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS)
             //printf("_%bx/%bx ",UART_CMD_MCU_IDX_H2,UART_CMD_MCU_IDX_L);
           if((UART_CMD_MCU_IDX_H2>=0x10)&&(UART_CMD_MCU_IDX_H2<=0x3F))
           {
                   if(MDrv_Ursa_USB_Update_GetChipType() == SWUpdateForMFC)
                   {
                          U8 u8Data;
                          u8Data = MDrv_Ursa_6M30_Get_Value((((U8)UART_CMD_MCU_IDX_H2<<8)|(U8)UART_CMD_MCU_IDX_L),FALSE);
                          putcharb(0xF2);
                          putcharb(u8Data);
                          printf("N");
                   }
                   else
                   {
                          putcharb( 0xF2 );
                          putcharb(MDrv_ReadByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                                   ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                                   (U8)UART_CMD_MCU_IDX_L
                                  )
                    );
                   }
           }
          else
       #elif (ENABLE_6M40_4KX2K_PROCESS)
            //      printf("_%bx/%bx ",UART_CMD_MCU_IDX_H2,UART_CMD_MCU_IDX_L);
           if((UART_CMD_MCU_IDX_H2>=0x10)&&(UART_CMD_MCU_IDX_H2<=0x3F))
           {
                   if(MDrv_Ursa_USB_Update_GetChipType() == SWUpdateForMFC)
                   {
                          U8 u8Data;
                          u8Data = MDrv_Ursa_6M40_Get_Value((((U8)UART_CMD_MCU_IDX_H2<<8)|(U8)UART_CMD_MCU_IDX_L),FALSE);
                          putcharb(0xF2);
                          putcharb(u8Data);
                          printf("N");
                   }
                   else
                   {
                          putcharb( 0xF2 );
                          putcharb(MDrv_ReadByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                                   ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                                   (U8)UART_CMD_MCU_IDX_L
                                  )
                    );
                   }
           }
           else
       #endif
           {
            #if (ENABLE_MFC_6M30||ENABLE_6M40_4KX2K_PROCESS) //
                 MDrv_Ursa_USB_Update_SetChipType(SWUpdateForHK);
            #endif
                  putcharb( 0xF2 );
                  putcharb(MDrv_ReadByte(((U8)UART_CMD_MCU_IDX_H1 << 16) |
                                   ((U8)UART_CMD_MCU_IDX_H2 << 8)  |
                                   (U8)UART_CMD_MCU_IDX_L
                                  )
                    );
            }
            break;

        case uartI2C_Device_Write:
            if ( FALSE == MDrv_IIC_WriteByte( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L, UART_CMD_MCU_DATA ) )
            {
                printf( "I2C Error!!! uartI2C_Device_Write\n" );
            }

            putcharb( 0xF1 );
            break;

        case uartI2C_Device_Read:
            putcharb( 0xF2 );
            if ( MDrv_IIC_ReadByte( UART_CMD_MCU_IDX_H, UART_CMD_MCU_IDX_L, &u8Value ) )
                putcharb( u8Value );
            else
                putcharb( 0xFF );
            break;

        case uartEEPROM_Write:
            u16EEADDR = MAKEWORD( g_UartCommand.Buffer[_UART_CMD_INDEX1_], g_UartCommand.Buffer[_UART_CMD_INDEX2_] );
            msAPI_rmWriteByte( u16EEADDR, UART_CMD_MCU_DATA );
            printf( "\r\n u16EEADDR : 0x%x   data : 0x%x", u16EEADDR, ( U16 ) UART_CMD_MCU_DATA );
            putcharb( 0xF1 );
            break;

        case uartEEPROM_Read:
            u16EEADDR = MAKEWORD( g_UartCommand.Buffer[_UART_CMD_INDEX1_], g_UartCommand.Buffer[_UART_CMD_INDEX2_] );
            g_UartCommand.Buffer[_UART_CMD_INDEX3_] = msAPI_rmReadByte( u16EEADDR );
            putchar( 0xF2 );
            putchar( g_UartCommand.Buffer[_UART_CMD_INDEX3_] );
            /*
            if (g_bDebugASCIICommandFlag)
            {
                printf("EEPROM[0x%x]=", uwEEADDR);
                printf("0x%x \r\n", g_UartCommand.Buffer[_UART_CMD_INDEX3_]);
            }*/
            break;

        case uartTest_Command:
            MDrv_UART_ExecTestCommand();
            break;
#if PHOENIX_DEBUG
        case uartRead_Demod:
            {
                RegAddr = ( ( U16 ) g_UartCommand.Buffer[_UART_CMD_INDEX1_] << 8 ) | ( U16 ) g_UartCommand.Buffer[_UART_CMD_INDEX2_];
                RegData = devCOFDM_ReadReg( RegAddr );
                putcharb( 0xF3 );
                putcharb( ( U8 ) ( RegData >> 8 ) );
                putcharb( ( U8 ) ( RegData & 0xff ) );
                //printf("[%x] = %x\n", RegAddr, RegData);
            }
            break;
        case uartWrite_Demod:
            {
                RegAddr = ( ( U16 ) g_UartCommand.Buffer[_UART_CMD_INDEX1_] << 8 ) | ( U16 ) g_UartCommand.Buffer[_UART_CMD_INDEX2_];
                RegData = ( ( U16 ) g_UartCommand.Buffer[_UART_CMD_INDEX3_] << 8 ) | ( U16 ) g_UartCommand.Buffer[_UART_CMD_INDEX4_];
                RegData = devCOFDM_WriteReg( RegAddr, RegData );
                putcharb( 0xF1 );
                //printf("[%x] = %x\n", RegAddr, RegData);
            }
            break;
#endif
#if CANOPUS_DEBUG
        case uartRead_Tuner:
            {
                devCOFDM_PassThroughI2C_ReadBytes(_TUNER_I2C_ID,
                                              1,
                                              &g_UartCommand.Buffer[_UART_CMD_INDEX1_],
                                              1,
                                              &u8Value);
                putcharb( 0xF2 );
                putcharb( u8Value );
                //printf("[%x] = %x\n", RegAddr, RegData);
            }
            break;
        case uartWrite_Tuner:
            {
                  devCOFDM_PassThroughI2C_WriteBytes(_TUNER_I2C_ID,
                                               1,
                                               &g_UartCommand.Buffer[_UART_CMD_INDEX1_],
                                               1,
                                               &g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
                putcharb( 0xF1 );
                //printf("[%x] = %x\n", RegAddr, RegData);
            }
            break;
        case uartRead_PI2C:
            {
                devCOFDM_PassThroughI2C_ReadBytes(_IF_DEM_I2C_ID,
                                              0,
                                              NULL,
                                              1,
                                              &u8Value);
                putcharb( 0xF2 );
                putcharb( u8Value );
            }
            break;
        case uartWrite_PI2C:
            {
                  devCOFDM_PassThroughI2C_WriteBytes(_IF_DEM_I2C_ID,
                                               1,
                                               &g_UartCommand.Buffer[_UART_CMD_INDEX1_],
                                               1,
                                               &g_UartCommand.Buffer[_UART_CMD_INDEX2_]);
                putcharb( 0xF1 );
                printf( "TDA9886:[%d] = 0x%x\n", ( int ) g_UartCommand.Buffer[_UART_CMD_INDEX1_], ( int ) g_UartCommand.Buffer[_UART_CMD_INDEX2_] );
            }
            break;
#endif
        default:
            // printf("Unsupport Normal Command: 0x%x\n", (U16)UART_CMD );
            break;
    }
}

/******************************************************************************/
///     @brief Adust PWM, which is board&GPIO dependent.
///     @param pwm_value   IN:value to set the backlight, from 0 up to 255.
/******************************************************************************/
void _MDrv_UART_SetBacklightDutyCycle(MS_U32 pwm_value)
{
    printf("<Debug><_MDrv_UART_SetBacklightDutyCycle> pwm_value=%ld\r\n",pwm_value);

    MDrv_PWM_DutyCycle((PWM_ChNum)UART_EXT_CMD_MS_DAT2, pwm_value);
}


/******************************************************************************/
/// Decode the Command gets from UART port for extra device(like tunner/demodulator).
/// Command Buffer [0]:
///  -bit7~bit5 :111b
///  -bit4~bit0 :extra UART command
/// Command Buffer [1~8]:
///  -Extra Control data buffer.
/******************************************************************************/
void MDrv_UART_DecodeExtCommand(void)
{
    MS_U8 u8addressCount, u8dataCount;
    MS_U8 u8Result, i;

    switch( UART_EXT_DEV )
    {
#if ENABLE_DLC
        #if (ENABLE_DLC_TEST_BY_MSTVTOOL)
        case uartExtDev_MstDlcTest:
        {
            tDLC_CONTROL_PARAMS tDLC_Params = {
                .pCmdBuff       = g_UartCommand.Buffer,
                .u16PNL_Width   = g_IPanel.Width(),
                .u16PNL_Height  = g_IPanel.Height(),
                .fnDLC_Putchar  = putcharb
             };

            MApi_XC_DLC_DecodeExtCmd(&tDLC_Params);
            break;
        }
    #endif //ENABLE_DLC_TEST_BY_MSTVTOOL
#endif
    #if (ENABLE_DBC)
        case DEV_MST_DBC_TEST:
        {
             tDBC_CONTROL_PARAMS tDBC_Params ={
                 .pCmdBuff              = g_UartCommand.Buffer,
                 .fnDBC_AP_OnOff        = MApi_XC_Sys_DLC_DBC_OnOff,
                 .fnDBC_AdjustBacklight = _MDrv_UART_SetBacklightDutyCycle,
                 .fnDBC_Putchar         = putcharb
             };
             MApi_XC_DBC_DecodeExtCmd(&tDBC_Params);
             break;
        }
    #else
        case DEV_MST_DBC_TEST:
        {
            putcharb(0xF2);
            putcharb(0);
            break;
        }
    #endif //ENABLE_DBC

#if 1
        //ENABLE_ACE_REPORT
        case uartExtDev_ACE_REPORT:
        {
            switch(UART_EXT_CMD)
            {
                case URCMD_MST_ACE_REPORT_TYPE:
                    u16ACE_Report_Type = UART_EXT_CMD_MS_DAT1;
                    break;

                case URCMD_MST_ACE_REPORT_CONTRAST:
                    if(0)//( u16ACE_Report_Type&ACE_REPORT_CONTRAST_10BITS ) // New tool command
                    {
                        putcharb(0xF3);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_CONTRAST)>>9 );
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_CONTRAST)>>1 );
                    }
                    else
                    {
                        putcharb(0xF2);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_CONTRAST)>>3 );
                    }
                    break;
                case URCMD_MST_ACE_REPORT_SATURATION:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_SATURATION) );
                    break;
                case URCMD_MST_ACE_REPORT_HUE:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_HUE) );
                    break;
                case URCMD_MST_ACE_REPORT_R_GAIN:
                    if(0)//( u16ACE_Report_Type&ACE_REPORT_CONTRAST_10BITS ) // New tool command
                    {
                        putcharb(0xF3);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_R_GAIN)>>9 );
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_R_GAIN)>>1 );
                    }
                    else
                    {
                        putcharb(0xF2);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_R_GAIN)>>3 );
                    }
                    break;
                case URCMD_MST_ACE_REPORT_G_GAIN:
                    if(0)//( u16ACE_Report_Type&ACE_REPORT_CONTRAST_10BITS ) // New tool command
                    {
                        putcharb(0xF3);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_G_GAIN)>>9 );
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_G_GAIN)>>1 );
                    }
                    else
                    {
                        putcharb(0xF2);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_G_GAIN)>>3 );
                    }
                    break;
                case URCMD_MST_ACE_REPORT_B_GAIN:
                    if(0)//( u16ACE_Report_Type&ACE_REPORT_CONTRAST_10BITS ) // New tool command
                    {
                        putcharb(0xF3);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_G_GAIN)>>9 );
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_B_GAIN)>>1 );
                    }
                    else
                    {
                        putcharb(0xF2);
                        putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_B_GAIN)>>3 );
                    }
                    break;
                case URCMD_MST_ACE_REPORT_R_BRI:
                    putcharb(0xF2);
                    #if 0
                    MDrv_WriteByte(BK_SELECT_00, REG_BANK_S_VOP);
                    //if (1)//(UART_EXT_CMD_MS_DAT1 == 0) // Main
                        putcharb( MDrv_Read2Byte(L_BK_S_VOP(0x36)) >> 3 );
                    //else
                        //putcharb( (msRead2Bytes(SCF_72) >> 3) );
                    #else
                    // Temporarily changed, remove "Analog_Reg.h"
                    {
                        MDrv_WriteByte(0x102F00, 0x0F);
                        putcharb( MDrv_Read2Byte(((U32)0x102F00 | ((U16)0x36 << 1))) >> 3 );
                    }
                    #endif
                    break;
                case URCMD_MST_ACE_REPORT_G_BRI:
                    putcharb(0xF2);
                    #if 0
                    MDrv_WriteByte(BK_SELECT_00, REG_BANK_S_VOP);
                    //if (1)//(UART_EXT_CMD_MS_DAT1 == 0) // Main
                        putcharb( MDrv_Read2Byte(L_BK_S_VOP(0x37)) >> 3 );
                    //else
                        //putcharb( (msRead2Bytes(SCF_74) >> 3) );
                    #else
                    // Temporarily changed, remove "Analog_Reg.h"
                    {
                        MDrv_WriteByte(0x102F00, 0x0F);
                        putcharb( MDrv_Read2Byte(((U32)0x102F00 | ((U16)0x37 << 1))) >> 3 );
                    }
                    #endif
                    break;
                case URCMD_MST_ACE_REPORT_B_BRI:
                    putcharb(0xF2);
                    #if 0
                    MDrv_WriteByte(BK_SELECT_00, REG_BANK_S_VOP);
                    //if (1)//(UART_EXT_CMD_MS_DAT1 == 0) // Main
                        putcharb( MDrv_Read2Byte(L_BK_S_VOP(0x38)) >> 3 );
                   // else
                        //putcharb( (msRead2Bytes(SCF_76) >> 3) );
                    #else
                    // Temporarily changed, remove "Analog_Reg.h"
                    {
                        MDrv_WriteByte(0x102F00, 0x0F);
                        putcharb( MDrv_Read2Byte(((U32)0x102F00 | ((U16)0x38 << 1))) >> 3 );
                    }
                    #endif
                    break;
                case URCMD_MST_ACE_REPORT_COLOR_CORRECTION_XY_R:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_XY_R) );
                    break;
                case URCMD_MST_ACE_REPORT_COLOR_CORRECTION_XY_G:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_XY_G) );
                    break;
                case URCMD_MST_ACE_REPORT_COLOR_CORRECTION_XY_B:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_XY_B) );
                    break;
                case URCMD_MST_ACE_REPORT_COLOR_CORRECTION_OFFSET_R:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_OFFSET_R) );
                    break;
                case URCMD_MST_ACE_REPORT_COLOR_CORRECTION_OFFSET_G:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_OFFSET_G) );
                    break;
                case URCMD_MST_ACE_REPORT_COLOR_CORRECTION_OFFSET_B:
                    putcharb(0xF2);
                    putcharb( MApi_XC_ACE_GetACEInfo(UART_EXT_CMD_MS_DAT1, E_XC_ACE_INFO_TYPE_COLOR_CORRECTION_OFFSET_B) );
                    break;
                case URCMD_MST_ACE_REPORT_IF_SUPPORT_RGB_GAIN:
                    putcharb(0xF2);
                    putcharb(ACE_INFOEX_MODE_POST_RGB_GAIN);
                    break;
            } // End of switch(dev_cmd)
            break;
        }
#endif
        case uartExtDev_I2C_DEVICE:
             u8addressCount = (UART_EXT_CMD_MS_DAT1 & 0xF0) >> 4;
             u8dataCount    = (UART_EXT_CMD_MS_DAT1 & 0x0F);
             if( u8addressCount + u8dataCount > 12 ) //UART_EXT_CMD_MS_DAT2...UART_EXT_CMD_MS_DAT13
               {   UARTMSG(printf("I2C error!")); }
             if( UART_EXT_CMD & 0x01 ) // I2C read
                 u8Result = MDrv_IIC_ReadBytes( UART_EXT_CMD,
                                                u8addressCount,
                                                &UART_EXT_CMD_MS_DAT2,
                                                u8dataCount,
                                                (&UART_EXT_CMD_MS_DAT2)+u8addressCount);
             else                      // I2C write
                 u8Result = MDrv_IIC_WriteBytes( UART_EXT_CMD,
                                                u8addressCount,
                                                &UART_EXT_CMD_MS_DAT2,
                                                u8dataCount,
                                                (&UART_EXT_CMD_MS_DAT2)+u8addressCount);

             if( u8Result )
             {
                 i = _UART_CMD_INDEX5_;
                 UARTMSG(printf("0x%02X ", (U16)UART_EXT_CMD ));
                 while( u8addressCount > 0 )
                 {
                     UARTMSG(printf("W0x%02X ", (U16)g_UartCommand.Buffer[i]));
                     --u8addressCount;
                     ++i;
                 }
                 while( u8dataCount > 0 )
                 {
                     if( UART_EXT_CMD & 0x01 ) {
                         UARTMSG(printf("R0x%02X ", (U16)g_UartCommand.Buffer[i]));}
                     else {
                         UARTMSG(printf("W0x%02X ", (U16)g_UartCommand.Buffer[i]));}
                     --u8dataCount;
                     ++i;
                 }
                 UARTMSG(printf("\n"));
             }
             else {
                 UARTMSG(printf("0x%02X doesn't exist!\n", (U16)UART_EXT_CMD));
             }
             break;

        case uartExtDev_SAMSUNG_S5H1409_DEMODE:
        {
             i = 0;
             while( 1 )
             {
                 if( MDrv_IIC_ReadBytes( UART_EXT_CMD|0x01 , 1, &i, 2, &UART_EXT_CMD_MS_DAT12) )
                     UARTMSG(printf("Reg 0x%02X = 0x%02X 0x%02X\n", (U16)i, (U16)UART_EXT_CMD_MS_DAT12, (U16)UART_EXT_CMD_MS_DAT13));
                 else
                 {
                     UARTMSG(printf("0x%02X doesn't exist!\n", (U16)UART_EXT_CMD));
                     break;
                 }
                 if( i == 0xFF )
                    break;
                 ++i;
             }
        }
             break;

       case uartExtDev_XC_rw:

         if (UART_EXT_CMD == 0x02) {
               MDrv_WriteByte(0x102F00, UART_EXT_CMD_MS_DAT1 );

           MDrv_WriteByte(((U8)UART_EXT_CMD_MS_DAT2 << 16) |
                                ((U8)UART_EXT_CMD_MS_DAT3 << 8)  |
                                (U8)UART_EXT_CMD_MS_DAT4,
                                (U8)UART_EXT_CMD_MS_DAT5
                               );
                putcharb(0xF1);
         }else if (UART_EXT_CMD == 0x01) {
                putcharb(0xF2);

                MDrv_WriteByte(0x102F00, UART_EXT_CMD_MS_DAT1 );
                putcharb(MDrv_ReadByte(((U8)UART_EXT_CMD_MS_DAT2 << 16) |
                                       ((U8)UART_EXT_CMD_MS_DAT3 << 8)  |
                                       (U8)UART_EXT_CMD_MS_DAT4
                                      )
                        );
          }
       break;

#if ((CHANNEL_SCAN_AUTO_TEST) || (SFU_AUTO_TEST))
        case uartExtDev_I2C_DEVICE_NEW:
             u8addressCount = (UART_EXT_CMD_MS_DAT1 & 0xF0) >> 4;
             u8dataCount    = (UART_EXT_CMD_MS_DAT1 & 0x0F);
             if( u8addressCount + u8dataCount > 12 ) //UART_EXT_CMD_MS_DAT2...UART_EXT_CMD_MS_DAT13
             {    CHSCANTEST_MSG(printf("I2C error!"));}
             if( UART_EXT_CMD & 0x01 ) // I2C read
                 u8Result = MDrv_IIC_ReadBytes( UART_EXT_CMD,
                                                u8addressCount,
                                                &UART_EXT_CMD_MS_DAT2,
                                                u8dataCount,
                                                (&UART_EXT_CMD_MS_DAT2)+u8addressCount);
             else                      // I2C write
                 u8Result = MDrv_IIC_WriteBytes( UART_EXT_CMD,
                                                u8addressCount,
                                                &UART_EXT_CMD_MS_DAT2,
                                                u8dataCount,
                                                (&UART_EXT_CMD_MS_DAT2)+u8addressCount);

             if( u8Result )
             {
                 if( UART_EXT_CMD & 0x01 )  // I2C Read
                 {
                     i = _UART_CMD_INDEX5_+u8addressCount;
                     while( u8dataCount > 0 )
                     {
                        CHSCANTEST_MSG(printf("%02bx ", g_UartCommand.Buffer[i]));
                        --u8dataCount;
                        ++i;
                     }
                     CHSCANTEST_MSG(printf("\n"));
                 }
                 else                       // I2C Write
                 {
                    CHSCANTEST_MSG(printf("OK\n"));
                 }
             }
             else
             {
                 CHSCANTEST_MSG(printf("err\n"));
             }
             break;
#endif

#if (INPUT_HDMI_VIDEO_COUNT > 0)
#if (HDCP_KEY_TYPE==HDCP_KEY_IN_24C04 || HDCP_KEY_TYPE==HDCP_KEY_IN_24C64)
         case uartExtDev_EEPROM_HDCP:
         {
             static U16 g_wHDCP_KeyChkSum;
             static U16 g_HDCP_KeyCounter;

             switch(UART_EXT_CMD)
             {
                 case URCMD_EEPROM_HDCP_GET_ADDR:  // mothod 1/2
/*
                    {
                        printf("URCMD_EEPROM_HDCP_GET_ADDR:\n");
                        for(i=0;i<17;i++)
                        {
                            printf("0x%x,",g_UartCommand.Buffer[i]);
                        }
                        printf("\n");
                    }
*/
                    g_bDebugProgStopFlag = 1; // pause the program
                    putcharb(0xF3);
                    putcharb( HIBYTE(HDCP_KEY_ADDR) );
                    putcharb( LOBYTE(HDCP_KEY_ADDR) );
                    g_HDCP_KeyCounter = HDCP_KEY_ADDR;
                    break;
                 case URCMD_EEPROM_HDCP_WRITE:   // mothod 2
                     {
                        U16 u16Length;
/*
                        {
                            printf("URCMD_EEPROM_HDCP_WRITE:\n");
                            for(i=0;i<17;i++)
                            {
                                printf("0x%x,",g_UartCommand.Buffer[i]);
                            }
                            printf("\n");
                        }
*/
                        #if ( ENABLE_UART_CHECKSUM )
                        UART_CMD_EXT_LENGTH--; // remove checksum byte
                        #endif

                        u16Length = (UART_CMD_EXT_LENGTH-4);
                        msAPI_hdcpkeyBurstWriteBytes(g_HDCP_KeyCounter, (BYTE *)&UART_EXT_CMD_MS_DAT1, u16Length);
                        g_HDCP_KeyCounter+=u16Length;
                     }
                     break;
                 case URCMD_EEPROM_HDCP_WRITE_END: // mothod 2
                     {
/*
                        {
                            printf("URCMD_EEPROM_HDCP_WRITE_END:\n");
                            for(i=0;i<17;i++)
                            {
                                printf("0x%x,",g_UartCommand.Buffer[i]);
                            }
                            printf("\n");
                        }
*/
                        #if ( ENABLE_UART_CHECKSUM )
                        UART_CMD_EXT_LENGTH--; // remove checksum byte
                        #endif
                        msAPI_hdcpkeyBurstWriteBytes(g_HDCP_KeyCounter, (BYTE *)&UART_EXT_CMD_MS_DAT1, (UART_CMD_EXT_LENGTH-4));
                     }
                     break;
                 case URCMD_EEPROM_HDCP_GET_CHECKSUM:    // mothod 1/2
                    {
                        U16 ii;
                        //printf("URCMD_EEPROM_HDCP_GET_CHECKSUM:\n");
                        for (ii=HDCP_KEY_ADDR, g_wHDCP_KeyChkSum=0; ii<(HDCP_KEY_ADDR+HDCP_KEY_SIZE); ii++)
                        {
                            U8 u8Value;
                            msAPI_hdcpkeyReadByte(ii,&u8Value);
                            g_wHDCP_KeyChkSum += u8Value;
                            //printf(">> %d Value =0x%x\n",(U16)ii,(U16)u8Value);
                        }
                        //printf("g_wHDCP_KeyChkSum = 0x%X\n", g_wHDCP_KeyChkSum);
                    }

                    putcharb(0xF3);
                    putcharb( HIBYTE(g_wHDCP_KeyChkSum) );
                    putcharb( LOBYTE(g_wHDCP_KeyChkSum) );

                    MApi_XC_Sys_HDMI_Init();

                    g_bDebugProgStopFlag = 0; // restart the program
                     break;
             } // End of switch(dev_cmd)
         }
         break;
#endif //#if (HDCP_KEY_TYPE==HDCP_KEY_IN_24C04 || HDCP_KEY_TYPE==HDCP_KEY_IN_24C64)
#endif


    #ifndef ATSC_SYSTEM
         case uartExtDev_Power_Test:
          #if ENABLE_AUTOTEST
              //MDrv_PWMGT_Excute(UART_EXT_CMD);
          #endif
            break;

        case uartExtDev_USB_Download:
        {
        #if ( (ENABLE_USB||ENABLE_USB_2) && ENABLE_FILESYSTEM )
          #ifndef MSOS_TYPE_LINUX
            extern U8 MDrv_USBGetPortEnableStatus(void);
            extern void MApp_ZUI_SwUpdate_ProgressBar(U8 percent);
            extern void msAPI_BLoader_Reboot(void);
            U8 u8PortEnStatus = 0;

            printf("USB SW Update!\n");
            u8PortEnStatus = MDrv_USBGetPortEnableStatus();
            if((u8PortEnStatus & BIT0) == BIT0)
            {
                MApp_UsbDownload_Init(BIT0, MApp_ZUI_SwUpdate_ProgressBar);
            }
            else if((u8PortEnStatus & BIT1) == BIT1)
            {
                MApp_UsbDownload_Init(BIT1, MApp_ZUI_SwUpdate_ProgressBar);
            }
            else
            {
                printf("Error> Unknown USB port\n");
                return;
            }

            if(!MW_UsbDownload_Search())
            {
                break;
            }

            if (MW_UsbDownload_Start())
            {
                msAPI_BLoader_Reboot();
            }
          #else
            printf("Un-support USB Update\n");
          #endif // #ifndef MSOS_TYPE_LINUX
        #endif
         }
              break;

         case uartExtDev_Autotest_Key:
             #if ENABLE_AUTOTEST
             MDrv_Autotest_Excute_Key(UART_EXT_CMD);
             #endif
             break;
    #endif // #ifndef ATSC_SYSTEM


         case uartExtDev_Autotest_Sp:
             #if ENABLE_AUTOTEST
             MDrv_Autotest_Excute_Sp(UART_EXT_CMD);
             #endif
             break;

         default:

             UARTMSG(printf("Unsupport ExtDev %d\n", (U16)UART_EXT_DEV));
             break;
    }
}
#ifdef MSOS_TYPE_LINUX
BOOLEAN OBAMA_MSG_CB (unsigned char * pu8InData, unsigned short u16InDataSize, unsigned char * pu8OutData, unsigned short u16OutDataSize)
{
    unsigned short i;
    pu8OutData = pu8OutData;
    u16OutDataSize = u16OutDataSize;
    // because MAdp_MSGCH_PollingEvent() has been called in main loop,
    // so this callback function would be automatically executed.
    printf("=====.....OBAMA_MSG_CB=====\n");
    for(i=0; i<u16InDataSize; i++)
    {
        MDrv_UART_RecvHandler(pu8InData[i]);
    }

    return TRUE;
}

void MDrv_OBamaAutoTest_Init(void)
{
    U8 u8ChIndex;

    MAdp_MSGCH_Init();

    u8ChIndex = MAdp_MSGCH_GetChannelIndex("AUTO_TEST");
    //printf("=====.....MDrv_OBamaAutoTest_Init===== u8ChIndex=%d\n", u8ChIndex);
    MAdp_MSGCH_SetCallBack(u8ChIndex, OBAMA_MSG_CB);
}

#endif

#else
// Fixed compiling warning : No one refer to u8Dummy.
//static U8 code u8Dummy;
static MS_U32 uart_debug;
static void MDrv_Empty_UART_RecvHandler(int c)
{
    UNUSED(c);
}
void MDrv_UART_Register_Empty_RecvHandler(void)
{
    uart_debug = mdrv_uart_open(E_UART_AEON);
    mdrv_uart_set_rx_callback(uart_debug, MDrv_Empty_UART_RecvHandler);
}
#endif /* ENABLE_MSTV_UART_DEBUG */


BOOLEAN UART_GetChar(BYTE *u8Char)
{
    BOOLEAN bOK;

    //ES1 = 0;                      // disable uart interrupt
    //_SetInt_SERIAL1(DISABLE);
    if( uartRXByteCount > 0 )                 /* is there any char in buffer   */
    {
        bOK = TRUE;
        *u8Char = uartRXBuf[uartRxQueueTail];        /* fetch the character           */

        uartRxQueueTail++;                    /* adjust it to the next         */

        if( uartRxQueueTail == UART_RXBUF_SIZE)
        {
            uartRxQueueTail = 0x00;                   /* going round                   */
        }
        uartRXByteCount--;                     /* decrement character counter   */
    }
    else
    {
        bOK = FALSE;
    }
    //ES1 = 1;                      // enable uart interrupt
    //_SetInt_SERIAL1(ENABLE);

    return (bOK);

} /* UART_GetChar() */

void UART_Clear(void)
{
    uartRXByteCount   = 0x00;                  /* reset pointers and counter    */
     uartRxQueueHeader = 0x00;
    uartRxQueueTail = 0x00;
}

#if(ENABLE_UART2)
static MS_U32 uart2_debug;
U8 g_Uart2_ack = 0;
static void MDrv_UART2_RecvHandler(int c)
{
	printf("MDrv_UART2_RecvHandler 111 \n");
    g_Uart2CheckTick = 50;// time-out control ms
    if (g_Uart2Command.Index >= _UART_CMD_LENGTH_)
    {
        g_Uart2Command.Index = 0;
    }
    g_Uart2Command.Buffer[g_Uart2Command.Index] = c; // recieve byte
    PrintfUart2(printf("%x ", c));
    g_Uart2_ack = 0xE5;

    g_Uart2Command.Index ++;
    if (g_Uart2Command.Index == 9)// ÿָ9ֽ.
    {
        g_bUart2Detected     = TRUE; // command  buffer recieve ok
        g_Uart2Command.Index = 0;    // reset index of command buffer
        g_Uart2CheckTick     = 0;
    }
    else if(g_Uart2Command.Buffer[0] == 0x69 && g_Uart2Command.Index == 3)
    {// Mstar ָ.
        g_bUart2Detected     = TRUE; // command  buffer recieve ok
        g_Uart2Command.Index = 0;    // reset index of command buffer
        g_Uart2CheckTick     = 0;
    }
	else if(g_Uart2Command.Buffer[0] == 0x68 && g_Uart2Command.Index == 3)
    {// Mstar ָ.
        g_bUart2Detected     = TRUE; // command  buffer recieve ok
        g_Uart2Command.Index = 0;    // reset index of command buffer
        g_Uart2CheckTick     = 0;
    }
	//MsOS_EnableInterrupt(E_INT_IRQ_UART2);
    MsOS_EnableInterrupt(E_INT_IRQ_UART1);
}

/******************************************************************************/
///Initial UART2 relative variable and flag.
/******************************************************************************/
void MDrv_UART2_DebugInit(void)
{
    PrintfUart2(printf("MDrv_UART2_DebugInit()\n"));
    // reset Uart variables
    MS_U16 u16Res = 0x00;
    g_Uart2Command.Index = 0;
    g_Uart2CheckTick = 0;

    //uart2_debug = mdrv_uart_open(E_UART_PIU_UART1); //gchen @ 20180118 //uart2
    uart2_debug = mdrv_uart_open(E_UART_PIU_UART0);
    PrintfUart2(printf("[UART2Init]mdrv_uart_open()>>%u\n", uart2_debug));
    //u16Res = mdrv_uart_connect(E_UART_PORT2, E_UART_PIU_UART1);
    u16Res = mdrv_uart_connect(E_UART_PORT3, E_UART_PIU_UART0);
    PrintfUart2(printf("[UART2Init]mdrv_uart_connect()>>%u\n", u16Res));

    if (uart2_debug)
    {
        u16Res = mdrv_uart_set_baudrate(uart2_debug, 115200);
        PrintfUart2(printf("[UART2Init]mdrv_uart_set_baudrate()>>%u\n", u16Res));
        u16Res = mdrv_uart_rx_enable(uart2_debug);
        PrintfUart2(printf("[UART2Init]mdrv_uart_rx_enable()>>%u\n", u16Res));
        u16Res = mdrv_uart_tx_enable(uart2_debug);
        PrintfUart2(printf("[UART2Init]mdrv_uart_tx_enable()>>%u\n", u16Res));
        u16Res = mdrv_uart_set_rx_callback(uart2_debug, MDrv_UART2_RecvHandler);
        PrintfUart2(printf("[UART2Init]mdrv_uart_set_rx_callback()>>%u\n", u16Res));
    }
    else
    {
        PrintfUart2(printf("[UART2Init]open uart2 fail\n"));
    }

    if(u16Res==0xFE)
    {
        MDrv_UART2_RecvHandler(0x00);
    }
}

void MDrv_UART2_Close(void)
{
    g_Uart2Command.Index = 0;
    memset(&g_Uart2Command, 0, sizeof(UartCommadType));
    g_Uart2CheckTick = 0;

    if(uart2_debug)
    {
       mdrv_uart_close(uart2_debug);
    }
}

void MDrv_UART2_SendCommand(MS_U8 *ucCommand, U16 u16Len)
{
    if(uart2_debug)
    {
        printf(">\n");
        mdrv_uart_write(uart2_debug, ucCommand, u16Len);
    }
    else
    {
        PrintfUart2(printf("[UART2SendCommand]open uart2 fail\n"));
    }
}

void MDrv_UART2_Read(MS_U8 *buf, MS_U32 len)
{
    if(uart2_debug)
    {
        mdrv_uart_read(uart2_debug, buf, len);
    }
    else
    {
        PrintfUart2(printf("[UART2Read]open uart2 fail\n"));
    }
}

void MDrv_UART2_MCU_RXD(void)
{
    if (g_bUart2Detected) // check command flag
    {
        g_bUart2Detected = FALSE;
		//header is 0x68 0x97 with code 0x0 0x0 , last is sumcheck

      #if(1)
        printf("\n[UART2] MDrv_UART2_MCU_RXD >> ");
        if(g_Uart2Command.Buffer[_UART_CMD_CODE_]>0x0F)  printf("%x ", g_Uart2Command.Buffer[_UART_CMD_CODE_]);  else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_CODE_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX1_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX1_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX1_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX2_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX2_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX2_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX3_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX3_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX3_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX4_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX4_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX4_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX5_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX5_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX5_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX6_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX6_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX6_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX7_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX7_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX7_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX8_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX8_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX8_]);
        printf("\n");
      #endif

        //command normal mode
        if((g_Uart2Command.Buffer[0] == 0x68) && 
			(g_Uart2Command.Buffer[_UART_CMD_INDEX1_] == 0x97))
        {
            switch( g_Uart2Command.Buffer[_UART_CMD_INDEX2_] )
            {
                case UART2_MCU_UP:  // Keypad Up
                    u8KeyCode = KEY_UP;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_DOWN:  // Keypad Down
                    u8KeyCode = KEY_DOWN;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_LEFT:  // Keypad Left
                    u8KeyCode = KEY_LEFT;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_RIGHT:  // Keypad Right
                    u8KeyCode = KEY_RIGHT;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_SELECT:  // Keypad Select
                    u8KeyCode = KEY_SELECT;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_POWER:  // Keypad Power
                    u8KeyCode = KEY_POWER;
					MDrv_UART2_MCU_TXD(UART2_MCU_POWER);
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_MENU:  // Keypad Menu
                    u8KeyCode = KEY_MENU;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case UART2_MCU_SOURCE:  // Source
                    u8KeyCode = KEY_INPUT_SOURCE;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
				case UART2_MCU_STOP:	// Stop
				  	u8KeyCode = KEY_STOP;
				  	u32MonitorOsdTimer = msAPI_Timer_GetTime0();
				  	break;
				case UART2_MCU_DISPLAY:	// Return
					//u8KeyCode = KEY_DISPLAY;
					//u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_PLAY:	// Return
					u8KeyCode = KEY_PLAY;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_PREVIOUS:	// Return
					u8KeyCode = KEY_PREVIOUS;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_NEXT:	// Return
					u8KeyCode = KEY_NEXT;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_VOLUME_PLUS:	// Return
					u8KeyCode = KEY_VOLUME_PLUS;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_VOLUME_MINUS:	// Return
					u8KeyCode = KEY_VOLUME_MINUS;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_MUTE:	// Return
					u8KeyCode = KEY_MUTE;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_KEYSTONE_POS:	// Return
					u8KeyCode = KEY_KEYSTONE_POS;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_KEYSTONE_NEG:	// Return
					u8KeyCode = KEY_KEYSTONE_NEG;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				case UART2_MCU_EXIT:	// Return
					u8KeyCode = KEY_EXIT;
					u32MonitorOsdTimer = msAPI_Timer_GetTime0();
					break;
				default:
					break;
            }
        }
    }
}

void MDrv_UART2_MCU_TXD(MS_U8 sendChar)
{
    MS_U8 u8TXDList[3] = {0x67, 0x98, sendChar};
    MDrv_UART2_SendCommand(u8TXDList, 3);
    //PrintfUart2(printf("[UART2_TestTXD][12345678]>>\n0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38\n"));
}


#if(ENABLE_UART2_TEST)
void MDrv_UART2_TestRXD(void)
{
    if (g_bUart2Detected) // check command flag
    {
        g_bUart2Detected = FALSE;
        // MENU: >> 69 73 23
        // LEFT: >> 69 72 24
        // RIGHT:>> 69 74 22
        // EXIT: >> 69 84 12
        // SOURCE>> 69 75 21

      #if(1)
        printf("\n[UART2] >> ");
        if(g_Uart2Command.Buffer[_UART_CMD_CODE_]>0x0F)  printf("%x ", g_Uart2Command.Buffer[_UART_CMD_CODE_]);  else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_CODE_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX1_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX1_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX1_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX2_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX2_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX2_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX3_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX3_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX3_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX4_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX4_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX4_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX5_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX5_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX5_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX6_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX6_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX6_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX7_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX7_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX7_]);
        if(g_Uart2Command.Buffer[_UART_CMD_INDEX8_]>0x0F)printf("%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX8_]);else printf("0%x ", g_Uart2Command.Buffer[_UART_CMD_INDEX8_]);
        printf("\n");
      #endif

        //command normal mode
        if(g_Uart2Command.Buffer[0] == 0x69)
        {
            switch( g_Uart2Command.Buffer[_UART_CMD_INDEX1_] )
            {
                case 0x63:  // Keypad Up
                    u8KeyCode = KEY_UP;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case 0x72:  // Keypad Left
                    u8KeyCode = KEY_LEFT;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case 0x73:  // Keypad Menu
                    u8KeyCode = KEY_MENU;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case 0x74:  // Keypad Right
                    u8KeyCode = KEY_RIGHT;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case 0x75:  // Keypad Source
                    u8KeyCode = KEY_INPUT_SOURCE;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case 0x76:  // Keypad Power
                    u8KeyCode = KEY_POWER;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
                case 0x83:  // Keypad Down
                    u8KeyCode = KEY_DOWN;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;

                case 0x84:  // IRKEY_EXIT
                    u8KeyCode = KEY_EXIT;
                    u32MonitorOsdTimer = msAPI_Timer_GetTime0();
                    break;
            }
        }
    }
	else
	{
		//printf("\n[UART2] >> g_bUart2Detected == false ");
	}
}

void MDrv_UART2_TestTXD(void)
{
    MS_U8 u8TXDList[8] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38};
    MDrv_UART2_SendCommand(u8TXDList, 8);
    //PrintfUart2(printf("[UART2_TestTXD][12345678]>>\n0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38\n"));
}
#endif

#endif

#undef _DRVUART_C_

