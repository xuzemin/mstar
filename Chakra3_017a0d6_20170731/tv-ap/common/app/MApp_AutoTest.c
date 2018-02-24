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

#include "Board.h"

#if( CHAKRA3_AUTO_TEST )

#define MAPP_AUTOTEST_C

#include "Utl.h"

#include "SysInit.h"


#include "msAPI_Tuning.h"
#include "msAPI_Timer.h"
#include "apiAUDIO.h"

#include "MApp_AutoTest.h"
#include "MApp_InputSource.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_GlobalFunction.h"

#include "msIR.h"

#include "MApp_AutoTest_Cus.h"
#include "MApp_Scaler.h"

//=======================================================================


#define AUTO_TEST_MSG_BUF_SIZE  65536


#define DEBUG_AT_CMD_PARSER(x)  //x

//---------------------------------------------------------------------------
//      Local
//---------------------------------------------------------------------------


#define AUTO_TEST_INPUT_BUFFER_LEN 32

typedef struct _AT_CMD_RECV
{
    MS_U8 m_u8Index;
    MS_U8 m_u8Buffer[AUTO_TEST_INPUT_BUFFER_LEN];
} AT_CMD_RECV;

static AT_CMD_RECV s_AT_RxBuf;

#define Auto_Test_Index1        ( s_AT_RxBuf.m_u8Buffer[0] )
#define Auto_Test_Index2        ( s_AT_RxBuf.m_u8Buffer[1] )
#define Auto_Test_Index3        ( s_AT_RxBuf.m_u8Buffer[2] )
#define Auto_Test_Index4        ( s_AT_RxBuf.m_u8Buffer[3] )
#define Auto_Test_Index5        ( s_AT_RxBuf.m_u8Buffer[4] )
#define Auto_Test_Index6        ( s_AT_RxBuf.m_u8Buffer[5] )
#define Auto_Test_Index7        ( s_AT_RxBuf.m_u8Buffer[6] )
#define Auto_Test_Index8        ( s_AT_RxBuf.m_u8Buffer[7] )
#define Auto_Test_Index9        ( s_AT_RxBuf.m_u8Buffer[8] )

//--------------------------------------------------------------------------
typedef enum
{
    AT_STATE__WAIT_INPUT_STR,   // Ready for get cmd string
    AT_STATE__PARSE_CMD,        // Convert input string to command
    AT_STATE__EXEC_CMD,         // Exec command
    AT_STATE__WAIT_CMD_DONE,    // Wait exec done
} EnuATState;

typedef struct
{
    EnuATState eATState;
    BOOL bAutoTestActive;

    AT_CMD curCmd;

}StuAutoTestInfo;

static StuAutoTestInfo s_AutoTest_Info;
static EN_AT_KEYCODE_MVK s_AT_enKeyCode_MVK;
static U16 s_AT_SymbolSetting = 0xFFFF;
static U16 s_AT_QamSetting = 0xFFFF;


#if(AT_IR_SIM)
static EN_AT_IR_SIM s_AT_enIRKeySimulation;
#endif

//#define MAX_AT_MESSAGE_FIFO_ROW     512
//#define MAX_AT_MESSAGE_FIFO_COLUMN  64
//static BYTE _AT_Message_FIFO[MAX_AT_MESSAGE_FIFO_ROW][MAX_AT_MESSAGE_FIFO_COLUMN];
// 512 x 64 = 32K !! too big!!
//---------------------------------------------------------------------------
//      Function
//---------------------------------------------------------------------------

BOOL MApp_AT_Is_AutoTestActive(void)
{
    return s_AutoTest_Info.bAutoTestActive;
}

BOOL MApp_AT_Is_NeedDisableOtherUartFunction(void)
{
    return s_AutoTest_Info.bAutoTestActive;
}


static U16 s_AT_u16MsgLen = 0;
static U8 s_AT_au8MsgBuf[AUTO_TEST_MSG_BUF_SIZE];

static void MApp_AT_Msg_Clear(void)
{
    s_AT_u16MsgLen = 0;
    s_AT_au8MsgBuf[0] = 0;
}

void MApp_AT_Msg_Add(const U8* pcMsg)
{
    if( pcMsg == NULL )
        return;

    int iStrLen = strlen((char*)pcMsg);

    if( (s_AT_u16MsgLen + iStrLen) > (AUTO_TEST_MSG_BUF_SIZE-1) )
    {
        printf("\nError: AT msg buffer full!!\n");
        return;
    }

    strcat((char*)s_AT_au8MsgBuf + s_AT_u16MsgLen, (char*)pcMsg);

    s_AT_u16MsgLen += iStrLen;
}

void MApp_AT_Msg_Add__AndAppendNewLine(const U8* pcMsg)
{
    if( pcMsg )
    {
        MApp_AT_Msg_Add(pcMsg);
    }

    MApp_AT_Msg_Add( (U8*)"\n");
}
/*
static void MApp_AT_Msg_Add_2(const U8* pcMsg1, const char* pcMsg2)
{
    if( pcMsg1 )
    {
        MApp_AT_Msg_Add(pcMsg1);
    }

    if( pcMsg2 )
    {
        MApp_AT_Msg_Add((U8*)pcMsg2);
    }
}
*/

static void MApp_AT_Msg_Print(void)
{
    U16 i;
    U8 u8Char;
    /*
    for( i = 0; i < s_AT_u16MsgLen; ++ i )
    {
        u8Char = s_AT_au8MsgBuf[i];
        if( u8Char == 0 )
        {
            printf("(%X)\n", u8Char);
        }
        else if( u8Char == '\n' )
        {
            putchar('\r');
            putchar('\n');
        }
        else if( (u8Char < 0x20) || (u8Char > 0x7F) )
        {
            printf("(%X)", u8Char);
        }
        else
        {
            putchar(u8Char);
        }
    }
    */
    for( i = 0; i < s_AT_u16MsgLen; ++ i )
    {
        u8Char = s_AT_au8MsgBuf[i];
        putchar(u8Char);
    }
}

void MApp_AT_Init(void)
{
    g_AT_enATVAutoTuningState = E_AUTO_TEST_TUNING_NONE;
    g_AT_enATVManualTuningState = E_AUTO_TEST_TUNING_NONE;

#if( ENABLE_DTV )
    g_AT_enDTVAutoTuningState = E_AUTO_TEST_TUNING_NONE;
    g_AT_enDTVManualTuningState = E_AUTO_TEST_TUNING_NONE;
#endif

#if(AT_IR_SIM)
    s_AT_enIRKeySimulation = EN_AT_IR_SIM_NULL;
#endif
    s_AT_enKeyCode_MVK = EN_AT_KEYCODE_NULL;


    s_AutoTest_Info.eATState = AT_STATE__WAIT_INPUT_STR;

    s_AutoTest_Info.bAutoTestActive = FALSE;

    s_AT_RxBuf.m_u8Index = 0;

    g_AT_en8ChangeChannelState = E_AUTO_TEST_CHANGE_CHANNEL_NONE;

    g_AT_bChangeSource = FALSE;
    MApp_AT_Msg_Clear();

}

static void _MApp_AT_ClearRxBuffer(void)
{
    s_AT_RxBuf.m_u8Index = 0;
    s_AT_RxBuf.m_u8Buffer[0] = 0;
}

static void _MApp_AT_PrintRxBuffer(void)
{
    U8 i;
    U8 u8Char;

    printf(" Rx[%d]=", s_AT_RxBuf.m_u8Index);

    for( i = 0; i < s_AT_RxBuf.m_u8Index; ++ i )
    {
        u8Char = s_AT_RxBuf.m_u8Buffer[i];
        if( u8Char >= 0x20 && u8Char < 0x7F )
        {
            putchar(u8Char);
        }
        else
        {
            printf("(%X)", u8Char);
        }
    }
    printf("\n");
}

static void _MApp_AT_ChangeStateTo(EnuATState eAtState)
{
    s_AutoTest_Info.eATState = eAtState;
    if( eAtState == AT_STATE__WAIT_INPUT_STR )
    {
        _MApp_AT_ClearRxBuffer();
    }
}


//-------------------------------------------------------------
// This function must attach to uart recieve interrupt
//
//void MDrv_UART_RecvAutoTestHandler(int c )
void MApp_AT_RecvDataHandler(int c)
{
    if( s_AutoTest_Info.eATState != AT_STATE__WAIT_INPUT_STR )
    {
        return;
    }

    putchar(c);


    if( s_AT_RxBuf.m_u8Index < AUTO_TEST_INPUT_BUFFER_LEN )
    {
        s_AT_RxBuf.m_u8Buffer[s_AT_RxBuf.m_u8Index] = c; //store enter key into buffer
        s_AT_RxBuf.m_u8Index ++;
    }
    else
    {
        if( s_AutoTest_Info.bAutoTestActive )
        {
            printf("Cmd is too long! \n");
        }
        s_AT_RxBuf.m_u8Index = 0;
    }

    if( c == ASCII_ENTER )  //check Enter Key
    {
        printf("\n");

        if( s_AT_RxBuf.m_u8Index > 0 )
            s_AT_RxBuf.m_u8Index -= 1;

        s_AutoTest_Info.eATState = AT_STATE__PARSE_CMD;
    }
    else if( c == ASCII_BACKSPACE ) // check backspace key
    {
        if( s_AT_RxBuf.m_u8Index > 0 )
            s_AT_RxBuf.m_u8Index --;
    }

}

static BOOLEAN _MApp_AT_CheckStartAutoTest(void)
{
    if( s_AT_RxBuf.m_u8Index != 13 )
        return FALSE;

    //check sentence "startautotest"
   if(  s_AT_RxBuf.m_u8Buffer[0]== 's' &&
        s_AT_RxBuf.m_u8Buffer[1]== 't' &&
        s_AT_RxBuf.m_u8Buffer[2]== 'a' &&
        s_AT_RxBuf.m_u8Buffer[3]== 'r' &&
        s_AT_RxBuf.m_u8Buffer[4]== 't' &&
        s_AT_RxBuf.m_u8Buffer[5]== 'a' &&
        s_AT_RxBuf.m_u8Buffer[6]== 'u' &&
        s_AT_RxBuf.m_u8Buffer[7]== 't' &&
        s_AT_RxBuf.m_u8Buffer[8]== 'o' &&
        s_AT_RxBuf.m_u8Buffer[9]== 't' &&
        s_AT_RxBuf.m_u8Buffer[10]== 'e' &&
        s_AT_RxBuf.m_u8Buffer[11]== 's' &&
        s_AT_RxBuf.m_u8Buffer[12]== 't'
      )
        return TRUE;
    else
        return FALSE;
}

static BOOLEAN _MApp_AT_CheckStopAutoTest(void)
{
    if( s_AT_RxBuf.m_u8Index != 12 )
        return FALSE;

    //check sentence "stopautotest"
   if(  s_AT_RxBuf.m_u8Buffer[0]== 's' &&
        s_AT_RxBuf.m_u8Buffer[1]== 't' &&
        s_AT_RxBuf.m_u8Buffer[2]== 'o' &&
        s_AT_RxBuf.m_u8Buffer[3]== 'p' &&
        s_AT_RxBuf.m_u8Buffer[4]== 'a' &&
        s_AT_RxBuf.m_u8Buffer[5]== 'u' &&
        s_AT_RxBuf.m_u8Buffer[6]== 't' &&
        s_AT_RxBuf.m_u8Buffer[7]== 'o' &&
        s_AT_RxBuf.m_u8Buffer[8]== 't' &&
        s_AT_RxBuf.m_u8Buffer[9]== 'e' &&
        s_AT_RxBuf.m_u8Buffer[10]== 's' &&
        s_AT_RxBuf.m_u8Buffer[11]== 't'
      )
        return TRUE;
    else
        return FALSE;
}

static BOOLEAN _MApp_AT_CheckCommandHeader(void)
{
    //check "at+wtest="
    if( Auto_Test_Index1== 'a' &&  Auto_Test_Index2== 't' &&
        Auto_Test_Index3== '+' &&  Auto_Test_Index4== 'w' &&
        Auto_Test_Index5== 't' &&  Auto_Test_Index6== 'e' &&
        Auto_Test_Index7== 's' &&  Auto_Test_Index8== 't' &&
        Auto_Test_Index9== '='
        )
        return TRUE;
    else
        return FALSE;
}

//----------------------------------------------------------------------------------------
// Convert input buffer string to AT-Cmd
static BOOLEAN _MApp_AT_CmdParser(AT_CMD *ATCmd)
{
    MS_U8 u8CmdCharIndex = AT_CMD_PARSE_BEGIN_INDEX;
    MS_U8 u8CheckCommaNum = 0, u8CmdParaIndex = 0;
    U8 u8CurChar;
    BOOL bRtn = TRUE;


    memset( ATCmd, 0, sizeof(AT_CMD) );

    if( u8CmdCharIndex >= s_AT_RxBuf.m_u8Index )
    {
        return FALSE;
    }

    u8CurChar = s_AT_RxBuf.m_u8Buffer[u8CmdCharIndex];

    if( (u8CurChar == ASCII_COMMA)||(u8CurChar == ASCII_ENTER) )
        return FALSE;

    for( ; u8CmdCharIndex < s_AT_RxBuf.m_u8Index; u8CmdCharIndex += 1 )
    {
        u8CurChar = s_AT_RxBuf.m_u8Buffer[u8CmdCharIndex];

        if( u8CurChar == ASCII_ENTER )// check enter key
            break;

        if( u8CurChar == ' ' ) // check space key
        {
            continue;
        }


        if( (u8CurChar != ASCII_COMMA)
          &&(u8CurChar < ASCII_NUMBER_0 || u8CurChar > ASCII_NUMBER_9)
          )  //only 0~9 and comma are legal characters
            return FALSE;

        if( u8CurChar == ASCII_COMMA &&
            s_AT_RxBuf.m_u8Buffer[u8CmdCharIndex-1] == ASCII_COMMA
          )  //continuous comma is illegal
            return FALSE;

        if( u8CheckCommaNum == 0 ) //get  cmd type
        {
            if( u8CurChar == ASCII_COMMA )
            {
                u8CheckCommaNum++;
            }
            else
            {
                ATCmd->u8CmdType = (ATCmd->u8CmdType) * 10 + (u8CurChar-ASCII_NUMBER_0);
            }
        }
        else if( u8CheckCommaNum == 1 ) //get  cmd subtype
        {
            if( u8CurChar == ASCII_COMMA )
            {
                u8CheckCommaNum++;
            }
            else
            {
                ATCmd->u16CmdSubType = ATCmd->u16CmdSubType * 10 + (u8CurChar-ASCII_NUMBER_0);
            }
        }
        else if( u8CheckCommaNum >= 2 ) //get  parameters
        {
            if( u8CurChar == ASCII_COMMA )
            {
                u8CheckCommaNum++;

                if( u8CheckCommaNum == AT_MAX_CMD_NUM ) //number of paramters exceed AT_MAX_CMD_PARA
                    return FALSE;
            }
            else
            {

                u8CmdParaIndex = u8CheckCommaNum - 2;
                //printf("u8CmdParaIndex=%u\n", u8CmdParaIndex);
                ATCmd->iCmdPara[u8CmdParaIndex] = ATCmd->iCmdPara[u8CmdParaIndex] * 10 + (u8CurChar-ASCII_NUMBER_0);
            }
        }

    }

    DEBUG_AT_CMD_PARSER( printf("DEBUG_AUTOTEST>> iCmdType= %d \n", ATCmd->u8CmdType) );
    DEBUG_AT_CMD_PARSER( printf("DEBUG_AUTOTEST>> iCmdSubType= %d \n", ATCmd->u16CmdSubType) );
    DEBUG_AT_CMD_PARSER( printf("DEBUG_AUTOTEST>> iCmdPara[0]= %d \n", ATCmd->iCmdPara[0]) );

    if( u8CheckCommaNum < 1 )
    {
        return FALSE;
    }


    return bRtn;
}

static void _MApp_AT_RetACK(void)
{
    printf("\n\n%s\n",AT_RESPONSE_START_ACK);
    printf("%s\n",AT_STATUS_ACK);
    printf("%s\n",AT_RESPONSE_END_ACK);
}

void MApp_AT_ProecssRxBuffer(void)
{
    _MApp_AT_PrintRxBuffer();

    if( FALSE == s_AutoTest_Info.bAutoTestActive ) // Auto test is not active
    {
        if( _MApp_AT_CheckStartAutoTest() )// enter the whole chakar 3 auto-test model
        {
            printf("Start Auto Test. \n");
            s_AutoTest_Info.bAutoTestActive = TRUE;
        }
        else
        {
            printf("Please keyin cmd to start Auto Test! \n");
        }

        _MApp_AT_ChangeStateTo(AT_STATE__WAIT_INPUT_STR);
    }
    else // Auto test is active
    {
        if( _MApp_AT_CheckStopAutoTest() ) // leave the whole chakar 3 auto-test model
        {
            printf("Auto Test finished. \n");
            s_AutoTest_Info.bAutoTestActive = FALSE;

            _MApp_AT_ChangeStateTo(AT_STATE__WAIT_INPUT_STR);
        }
    #if(AT_IR_SIM)
        else if( _MApp_AT_CheckIRKeySimulation() )
        {
            s_AutoTest_Info.eATState = AT_STATE__WAIT_CMD_DONE;
        }
    #endif
        else if( _MApp_AT_CheckCommandHeader() )//if command header is "at+wteset=", enter the whole auto-test model.
        {

            memset(&(s_AutoTest_Info.curCmd), 0, sizeof(AT_CMD));
            // Input buffer ==> Cmd
            if( _MApp_AT_CmdParser( &(s_AutoTest_Info.curCmd) ) ) // get cmd type, cmd subtype and parameters
            {
                _MApp_AT_RetACK();

                printf("\nInput command : %s%d, %d, %d\n", AT_CMD_HEADER,
                                            s_AutoTest_Info.curCmd.u8CmdType,
                                            s_AutoTest_Info.curCmd.u16CmdSubType,
                                            s_AutoTest_Info.curCmd.iCmdPara[0]);

                printf("\n======== FLUSH COMMAND %d SUBTYPE %d ======== \n",
                    s_AutoTest_Info.curCmd.u8CmdType, s_AutoTest_Info.curCmd.u16CmdSubType);

                s_AutoTest_Info.eATState = AT_STATE__EXEC_CMD;
            }
            else
            {
                printf("Illegal AT cmd syntax! \n");
                _MApp_AT_ChangeStateTo(AT_STATE__WAIT_INPUT_STR);
            }

        }
        else
        {
            _MApp_AT_ChangeStateTo(AT_STATE__WAIT_INPUT_STR);
            printf("Illegal AT cmd header! \n");
        }

    }

    _MApp_AT_ClearRxBuffer();
}


void MApp_AT_Get_CurCmd(AT_CMD* pAutoTestCmd)
{
    *pAutoTestCmd = s_AutoTest_Info.curCmd;
}

U16 MApp_AT_Get_CurCmdType(void)
{
    return s_AutoTest_Info.curCmd.u8CmdType;
}

U16 MApp_AT_Get_CurCmdSubType(void)
{
    return s_AutoTest_Info.curCmd.u16CmdSubType;
}

U16 MApp_AT_Get_SymbolSetting(void)
{
    if(s_AT_SymbolSetting!=0xFFFF)
    {
        U16 u16tmp = s_AT_SymbolSetting;
        s_AT_SymbolSetting = 0xFFFF;   //Clear
        return u16tmp;
    }
    else
        return 0xFFFF;
}

U16 MApp_AT_Get_QamSetting(void)
{
    if(s_AT_QamSetting!=0xFFFF)
    {
        U16 u16tmp = s_AT_QamSetting;
        s_AT_QamSetting = 0xFFFF;   //Clear
        return u16tmp;
    }
    else
        return 0xFFFF;
}

static void MApp_AT_RetStatus(EN_AT_Reply eResult)
{
    if( eResult != EN_AT_REPLY_STATUS_TV_INIT )
    {
        printf("======== FLUSH COMMAND %u RESULT %d ======== \n", MApp_AT_Get_CurCmdType(), eResult);
    }

    printf("\n%s\n",AT_RESPONSE_START_SIG);

    //_MApp_AT_GetFIFO();
    MApp_AT_Msg_Print();
    MApp_AT_Msg_Clear();

    switch(eResult)
    {
        case EN_AT_REPLY_STATUS_OK:
        {
            printf("%s\n",AT_STATUS_OK);
            break;
        }
        case EN_AT_REPLY_STATUS_ER:
        {
            printf("%s\n",AT_STATUS_ER);
            break;
        }
        case EN_AT_REPLY_STATUS_TV_INIT:
        {
            printf("%s\n",AT_STATUS_START);
            break;
        }
        default:
            break;
    }

    printf("%s\n",AT_RESPONSE_END_SIG);
}

//========================================================================


static U32 s_AT_u32AtvManualTuneFreq = 0;

U32 MApp_AT_Get_AtvManualTuneFreq(void)
{
    return s_AT_u32AtvManualTuneFreq;
}

static U16 s_AT_u16DtvManualTuneChannelNumber = 0;
U16 MApp_AT_Get_DtvManualTuneChannelNumber(void)
{
    return s_AT_u16DtvManualTuneChannelNumber;
}

//============================================================================

static EN_AT_RESULT _MApp_AT_KeyShortPressHandler(AT_CMD ATCmd)
{
    if( s_AT_enKeyCode_MVK != EN_AT_KEYCODE_NULL )
    {
        printf("[Auto Test] Pre KeyShortPress is not finished!");
        return EN_AT_RESULT_ER;
    }


    switch(ATCmd.u16CmdSubType)
    {
        case EN_AT_KEYCODE_MVK_CHANNEL_LIST:
        {
            printf("EN_AT_KEYCODE_MVK_CHANNEL_LIST \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_CHANNEL_LIST;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_CHANNEL_RETURN:
        {
            printf("EN_AT_KEYCODE_MVK_CHANNEL_RETURN \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_CHANNEL_RETURN;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_CHANNEL_PLUS:
        {
            printf("EN_AT_KEYCODE_MVK_CHANNEL_PLUS \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_CHANNEL_PLUS;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_CHANNEL_MINUS:
        {
            printf("EN_AT_KEYCODE_MVK_CHANNEL_MINUS \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_CHANNEL_MINUS;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_AUDIO:
        {
            printf("EN_AT_KEYCODE_MVK_AUDIO \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_AUDIO;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_VOLUME_PLUS:
        {
            printf("EN_AT_KEYCODE_MVK_VOLUME_PLUS \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_VOLUME_PLUS;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_VOLUME_MINUS:
        {
            printf("EN_AT_KEYCODE_MVK_VOLUME_MINUS \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_VOLUME_MINUS;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_UP:
        {
            printf("EN_AT_KEYCODE_MVK_UP \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_UP;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_DOWN:
        {
            printf("EN_AT_KEYCODE_MVK_DOWN \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_DOWN;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_LEFT:
        {
            printf("EN_AT_KEYCODE_MVK_LEFT \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_LEFT;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_RIGHT:
        {
            printf("EN_AT_KEYCODE_MVK_RIGHT \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_RIGHT;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_POWER:
        {
            printf("EN_AT_KEYCODE_MVK_POWER \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_POWER;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_EXIT:
        {
            printf("EN_AT_KEYCODE_MVK_EXIT \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_EXIT;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_MENU:
        {
            printf("EN_AT_KEYCODE_MVK_MENU \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_MENU;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_SELECT:
        {
            printf("EN_AT_KEYCODE_MVK_SELECT \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_SELECT;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_0:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_0 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_0;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_1:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_1 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_1;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_2:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_2 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_2;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_3:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_3 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_3;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_4:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_4 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_4;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_5:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_5 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_5;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_6:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_6 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_6;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_7:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_7 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_7;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_8:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_8 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_8;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NUM_9:
        {
            printf("EN_AT_KEYCODE_MVK_NUM_9 \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NUM_9;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_MUTE:
        {
            printf("EN_AT_KEYCODE_MVK_MUTE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_MUTE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PAGE_UP:
        {
            printf("EN_AT_KEYCODE_MVK_PAGE_UP \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PAGE_UP;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PAGE_DOWN:
        {
            printf("EN_AT_KEYCODE_MVK_PAGE_DOWN \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PAGE_DOWN;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_INFO:
        {
            printf("EN_AT_KEYCODE_MVK_INFO \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_INFO;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_RED:
        {
            printf("EN_AT_KEYCODE_MVK_RED \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_RED;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_GREEN:
        {
            printf("EN_AT_KEYCODE_MVK_GREEN \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_GREEN;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_YELLOW:
        {
            printf("EN_AT_KEYCODE_MVK_YELLOW \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_YELLOW;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_BLUE:
        {
            printf("EN_AT_KEYCODE_MVK_BLUE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_BLUE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_INPUT_SOURCE:
        {
            printf("EN_AT_KEYCODE_MVK_INPUT_SOURCE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_INPUT_SOURCE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_EPG:
        {
            printf("EN_AT_KEYCODE_MVK_EPG \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_EPG;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_MTS:
        {
            printf("EN_AT_KEYCODE_MVK_MTS \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_MTS;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_TTX:
        {
            printf("EN_AT_KEYCODE_MVK_TTX \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_TTX;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_SLEEP:
        {
            printf("EN_AT_KEYCODE_MVK_SLEEP \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_SLEEP;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_ZOOM:
        {
            printf("EN_AT_KEYCODE_MVK_ZOOM \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_ZOOM;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_INDEX:
        {
            printf("EN_AT_KEYCODE_MVK_INDEX \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_INDEX;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PLAY:
        {
            printf("EN_AT_KEYCODE_MVK_PLAY \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PLAY;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PAUSE:
        {
            printf("EN_AT_KEYCODE_MVK_PAUSE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PAUSE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_STOP:
        {
            printf("EN_AT_KEYCODE_MVK_STOP \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_STOP;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_NEXT:
        {
            printf("EN_AT_KEYCODE_MVK_NEXT \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_NEXT;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PREVIOUS:
        {
            printf("EN_AT_KEYCODE_MVK_PREVIOUS \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PREVIOUS;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_FORWARD:
        {
            printf("EN_AT_KEYCODE_MVK_FORWARD \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_FORWARD;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_BACKWARD:
        {
            printf("EN_AT_KEYCODE_MVK_BACKWARD \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_BACKWARD;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_CC:
        {
            printf("EN_AT_KEYCODE_MVK_CC \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_CC;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_RECORD:
        {
            printf("EN_AT_KEYCODE_MVK_RECORD \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_RECORD;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_SUBTITLE:
        {
            printf("EN_AT_KEYCODE_MVK_SUBTITLE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_SUBTITLE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_SUBCODE:
        {
            printf("EN_AT_KEYCODE_MVK_SUBCODE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_SUBCODE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PHOTO:
        {
            printf("EN_AT_KEYCODE_MVK_PHOTO \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PHOTO;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_FREEZE:
        {
            printf("EN_AT_KEYCODE_MVK_FREEZE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_FREEZE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_PIP:
        {
            printf("EN_AT_KEYCODE_MVK_PIP \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_PIP;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_MIX:
        {
            printf("EN_AT_KEYCODE_MVK_MIX \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_MIX;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_GUIDE:
        {
            printf("EN_AT_KEYCODE_MVK_GUIDE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_GUIDE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_HOLD:
        {
            printf("EN_AT_KEYCODE_MVK_HOLD \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_HOLD;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_UPDATE:
        {
            printf("EN_AT_KEYCODE_MVK_UPDATE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_UPDATE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_REVEAL:
        {
            printf("EN_AT_KEYCODE_MVK_REVEAL \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_REVEAL;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_SIZE:
        {
            printf("EN_AT_KEYCODE_MVK_SIZE \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_SIZE;

            return EN_AT_RESULT_OK;
        }
        case EN_AT_KEYCODE_MVK_CLOCK:
        {
            printf("EN_AT_KEYCODE_MVK_CLOCK \n");

            s_AT_enKeyCode_MVK = EN_AT_KEYCODE_MVK_CLOCK;

            return EN_AT_RESULT_OK;
        }
        default:
        {
            printf("Wrong SubCmdType! \n");
            return EN_AT_RESULT_ER;
        }
    }
}

static EN_AT_RESULT _MApp_AT_DirectCmdHandler(AT_CMD ATCmd)
{
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_DIRECT_CMD_SET_INPUT_SOURCE: // 1
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_SET_INPUT_SOURCE \n");

            EN_AT_INPUT_SOURCE_TYPE enAutoTestInputSrc = (EN_AT_INPUT_SOURCE_TYPE)ATCmd.iCmdPara[0];

            E_UI_INPUT_SOURCE EnUiInputSource = MApp_InputSource_GetUIInputSourceType( (INPUT_SOURCE_TYPE_t)enAutoTestInputSrc );

            if( UI_INPUT_SOURCE_NONE == EnUiInputSource )
            {
                printf("Invalid source number=%u\n", enAutoTestInputSrc);
                return EN_AT_RESULT_ER;
            }
            else if( UI_INPUT_SOURCE_TYPE == EnUiInputSource )
            {
                return EN_AT_RESULT_OK;
            }

            SET_AUTOTEST_CHECKPT();
            PRINT_AUTOTEST_CHECKPT_TIME("start source change");

            g_AT_u32UnmuteVideo =0;
            g_AT_bChangeSource = TRUE;
            g_AT_u32ChangeSourceTime = 0;//MsOS_GetSystemTime();
            //printf("g_AT_u32ChangeSourceTime = %u\n", g_AT_u32ChangeSourceTime);

            if( MApp_AT_Cmd_SetInputSource(enAutoTestInputSrc) )
            {
                AT_LOG("AT_Cmd_SetInputSource done" );
                return EN_AT_RESULT_ONGOING;
            }
            else
            {
                g_AT_bChangeSource = FALSE;
                printf("\n MApp_AT_Cmd_SetInputSource() failed!\n");
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_GET_INPUT_SIGNAL: // 2
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_GET_INPUT_SIGNAL \n");

            if( MApp_AT_Cmd_GetInputSignal() )
            {
                //printf("EN_AT_RESULT_OK\n");
                return EN_AT_RESULT_OK;
            }
            else
            {
                printf("EN_AT_RESULT_ER\n");
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_DTV_SCAN: // 3
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_DTV_SCAN \n");
        #if(ENABLE_DTV)
            EN_AT_MEMBER_COUNTRY enAutoTestCountry = (EN_AT_MEMBER_COUNTRY)ATCmd.iCmdPara[0];
            SET_AUTOTEST_CHECKPT();
            PRINT_AUTOTEST_CHECKPT_TIME("start dtv auto scan");
            //printf("enAutoTestCountry=%d\n", enAutoTestCountry);
            if( MApp_AT_Cmd_DtvAutoScan(enAutoTestCountry) )
            {
                g_AT_enDTVAutoTuningState = E_AUTO_TEST_TUNING_START;
                return EN_AT_RESULT_ONGOING;
            }
            else
            {
                printf("Please execute this cmd in STATE_TOP_DIGITALINPUTS.\n");
                return EN_AT_RESULT_ER;
            }
        #else
            printf("This TV is ATV only\n");
            return EN_AT_RESULT_ER;
        #endif
        }
        case EN_AUTO_TEST_DIRECT_CMD_ATV_SCAN: // 4
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_ATV_SCAN \n");

            EN_AT_MEMBER_COUNTRY enAutoTestCountry = (EN_AT_MEMBER_COUNTRY)ATCmd.iCmdPara[0];
            //printf("enAutoTestCountry=%d\n", enAutoTestCountry);
            SET_AUTOTEST_CHECKPT();
            PRINT_AUTOTEST_CHECKPT_TIME("start atv auto scan");
            if( MApp_AT_Cmd_AtvAutoScan(enAutoTestCountry) )
            {
                g_AT_enATVAutoTuningState = E_AUTO_TEST_TUNING_START;
                return EN_AT_RESULT_ONGOING;
            }
            else
            {
                printf("Please execute this cmd in STATE_TOP_DIGITALINPUTS.\n");
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_GET_DTV_CHANNEL_LIST: // 5
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_GET_DTV_CHANNEL_LIST \n");

          #if (ENABLE_DTV)
            if( MApp_AT_Cmd_GetDtvChannelList() )
            {
                return EN_AT_RESULT_OK;
            }
            else
            {
                printf("Channel count is 0.\n");
                return EN_AT_RESULT_ER;
            }
          #else
            printf("DTV is not enabled.\n");
            return EN_AT_RESULT_ER;
          #endif
        }
        case EN_AUTO_TEST_DIRECT_CMD_GET_ATV_CHANNEL_LIST: // 6
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_GET_ATV_CHANNEL_LIST \n");

            if( MApp_AT_Cmd_GetAtvChannelList() )
            {
                return EN_AT_RESULT_OK;
            }
            else
            {
                printf("Channel count is 0.\n");
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_GET_INPUT_SOURCE: //8
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_GET_INPUT_SOURCE \n");

            INPUT_SOURCE_TYPE_t eValue = MApp_InputSource_GetInputSourceType(UI_INPUT_SOURCE_TYPE);

            if(eValue < INPUT_SOURCE_NUM)
            {
                BYTE buffer[10]={ASCII_NULL};
                snprintf((char *)buffer, 9, "%d",eValue);
                MApp_AT_Msg_Add__AndAppendNewLine(buffer);

                return EN_AT_RESULT_OK;
            }
            else
            {
                printf("Unreasonable source number.\n");
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_DTV_DIRECT_SCAN: // 11
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_DTV_DIRECT_SCAN \n");

        #if(ENABLE_DTV)
            // Save channel number
            s_AT_u16DtvManualTuneChannelNumber = s_AutoTest_Info.curCmd.iCmdPara[0];
          #if ENABLE_DVBC
            s_AT_SymbolSetting = s_AutoTest_Info.curCmd.iCmdPara[1];
            s_AT_QamSetting = s_AutoTest_Info.curCmd.iCmdPara[2];
          #endif
            printf("s_AT_u16DtvManualTuneChannelNumber=%u\n", s_AT_u16DtvManualTuneChannelNumber);

            if( MApp_AT_Cmd_DtvManualScan(s_AT_u16DtvManualTuneChannelNumber) )
            {
                g_AT_enDTVManualTuningState = E_AUTO_TEST_TUNING_WAIT_START;

                return EN_AT_RESULT_ONGOING;
            }
            else
            {
                printf("Please execute this cmd in STATE_TOP_DIGITALINPUTS.\n");
                return EN_AT_RESULT_ER;
            }
        #else
            printf("This TV is only ATV\n");
            return EN_AT_RESULT_ER;
        #endif
        }
        case EN_AUTO_TEST_DIRECT_CMD_ATV_DIRECT_SCAN: // 12
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_ATV_DIRECT_SCAN \n");

            // Save freq...
            s_AT_u32AtvManualTuneFreq = s_AutoTest_Info.curCmd.iCmdPara[0];
            printf("s_AT_u32AtvManualTuneFreq=%u\n", s_AT_u32AtvManualTuneFreq);

            if( MApp_AT_Cmd_AtvManualScan(s_AT_u32AtvManualTuneFreq) )
            {
                g_AT_enATVManualTuningState = E_AUTO_TEST_TUNING_WAIT_START;
                return EN_AT_RESULT_ONGOING;
            }
            else
            {
                printf("Please execute this cmd in STATE_TOP_DIGITALINPUTS.\n");
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_GET_VIDEO_STATE: // 24
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_GET_VIDEO_STATE \n");

            if( MApp_AT_Cmd_GetVideoState() )
            {
                return EN_AT_RESULT_OK;
            }
            else
            {
                return EN_AT_RESULT_ER;
            }
        }
        case EN_AUTO_TEST_DIRECT_CMD_SET_ASPECT_RATIO: // 27
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_SET_ASPECT_RATIO \n");

            EN_ASPECT_RATIO_TYPE eVideoARCType;
            switch(ATCmd.iCmdPara[0])
            {
                case E_AR_16x9:
                    eVideoARCType = VIDEOSCREEN_FULL;
                    break;
                case E_AR_4x3:
                    eVideoARCType = VIDEOSCREEN_NORMAL;
                    break;
                case E_AR_AUTO:
                    eVideoARCType = VIDEOSCREEN_ORIGIN;
                    break;
                case E_AR_Panorama:
                    eVideoARCType = VIDEOSCREEN_PANORAMA;
                    break;
                case E_AR_JustScan:
                    eVideoARCType = VIDEOSCREEN_JUSTSCAN;
                    break;
                case E_AR_Zoom1:
                    eVideoARCType = VIDEOSCREEN_ZOOM1;
                    break;
                case E_AR_Zoom2:
                    eVideoARCType = VIDEOSCREEN_ZOOM2;
                    break;
                default:
                    eVideoARCType = VIDEOSCREEN_ORIGIN;
                    break;
            }
            stSystemInfo[MAIN_WINDOW].enAspectRatio = eVideoARCType;
            MApp_Scaler_SetWindow(NULL, NULL, NULL, stSystemInfo[MAIN_WINDOW].enAspectRatio, SYS_INPUT_SOURCE_TYPE(MAIN_WINDOW), MAIN_WINDOW);
            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_DIRECT_CMD_DTV_SIGNAL: // 28
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_DTV_SIGNAL \n");

#if (ENABLE_DTV)
            if( MApp_AT_Cmd_GetDtvSignal() )
            {
                return EN_AT_RESULT_OK;
            }
            else
            {
                printf("Channel count is 0 or not in DTV source.\n");
                return EN_AT_RESULT_ER;
            }
#else
            printf("DTV is not enabled.\n");
            return EN_AT_RESULT_ER;
#endif
        }
        case EN_AUTO_TEST_DIRECT_CMD_ATV_SIGNAL: // 29
        {
            printf("EN_AUTO_TEST_DIRECT_CMD_ATV_SIGNAL \n");

            if( MApp_AT_Cmd_GetAtvSignal() )
            {
                return EN_AT_RESULT_OK;
            }
            else
            {
                printf("Channel count is 0 or not in ATV source.\n");
                return EN_AT_RESULT_ER;
            }
        }
        default:
        {
            printf("Wrong SubCmdType! \n");
            return EN_AT_RESULT_ER;
        }
    }
}

static EN_AT_RESULT _MApp_AT_MiscCmdHandler(AT_CMD ATCmd)
{
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_MISC_RESET_FACTORY: // 2
        {
            printf("EN_AUTO_TEST_MISC_RESET_FACTORY \n");

            MApp_AT_RetStatus(EN_AT_REPLY_STATUS_OK);

            MApp_AT_Cmd_FactoryReset();

            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_MISC_REBOOT: // 3
        {
            printf("EN_AUTO_TEST_MISC_REBOOT \n");

            MApp_AT_RetStatus(EN_AT_REPLY_STATUS_OK);

            MDrv_Sys_WholeChipReset();

            return EN_AT_RESULT_OK;
        }
        case EN_AUTO_TEST_MISC_CLEAR_CMDB: // 1
        case EN_AUTO_TEST_MISC_CLEAR_PROGRAM: // 4
        {
            printf("EN_AUTO_TEST_MISC_CLEAR_PROGRAM \n");

            MApp_AT_Cmd_ClearProgram();

            return EN_AT_RESULT_OK;
        }
        default:
        {
            printf("Wrong SubCmdType! \n");
            return EN_AT_RESULT_ER;
        }
    }
}

static EN_AT_RESULT _MApp_AT_OADCmdHandler(AT_CMD ATCmd)
{
    switch(ATCmd.u16CmdSubType)
    {
        case EN_AUTO_TEST_OAD_SOFTWARE_UPDATE_USB: // 6
        {
            printf("EN_AUTO_TEST_OAD_SOFTWARE_UPDATE_USB \n");

            if( !MApp_AT_Cmd_SwUpgrade_Init() )
            {
                return EN_AT_RESULT_ER;
            }
            MApp_AT_RetStatus(EN_AT_REPLY_STATUS_OK);

            MApp_AT_Cmd_SwUpgrade_Start();
        }
        default:
        {
            printf("Wrong SubCmdType!\n");
            return EN_AT_RESULT_ER;
        }
    }
}

static BOOLEAN _MApp_AT_CmdHandler(void)
{
    EN_AT_RESULT eResult = EN_AT_RESULT_OK;

    AT_CMD ATCmd;

    printf("[%u]_MApp_AT_CmdHandler() at %u\n", AUTO_TEST_VERSION, MsOS_GetSystemTime());


    MApp_AT_Get_CurCmd(&ATCmd);


    switch(ATCmd.u8CmdType)
    {
        case EN_AUTO_TEST_CMD_TYPE_KEY_SHORT_PRESS_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_KEY_SHORT_PRESS_CMD\n"));
            eResult = _MApp_AT_KeyShortPressHandler(ATCmd);
            break;
        }
        /*
        case EN_AUTO_TEST_CMD_TYPE_KEY_LONG_PRESS_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_KEY_LONG_PRESS_CMD\n"));

            break;
        }
        */
        case EN_AUTO_TEST_CMD_TYPE_DIRECT_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_DIRECT_CMD\n"));
            eResult = _MApp_AT_DirectCmdHandler(ATCmd);
            break;
        }

        case EN_AUTO_TEST_CMD_TYPE_SI_CMD:
        {
        #if (ENABLE_DTV)
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_SI_CMD\n"));
            eResult = _MApp_AT_SICmdHandler(ATCmd);
        #else
            DEBUG_AUTOTEST(printf("Not Support SI Feature\n"));
            eResult = EN_AT_RESULT_ER;
        #endif
            break;
        }

        case EN_AUTO_TEST_CMD_TYPE_AUDIO_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_AUDIO_CMD\n"));
            eResult = _MApp_AT_AudioCmdHandler(ATCmd);
            break;
        }
        case EN_AUTO_TEST_CMD_TYPE_MISC_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_MISC_CMD\n"));
            eResult = _MApp_AT_MiscCmdHandler(ATCmd);
            break;
        }
        case EN_AUTO_TEST_CMD_TYPE_SUBTITLE_CMD:
        {
        #if (ENABLE_SUBTITLE)
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_SUBTITLE_CMD\n"));
            eResult = _MApp_AT_SubtitleCmdHandler(ATCmd);
        #else
            DEBUG_AUTOTEST(printf("Not Support Subtilte Feature\n"));
            eResult = EN_AT_RESULT_ER;
        #endif
            break;
        }

        case EN_AUTO_TEST_CMD_TYPE_CI_CMD:
        {
        #if ENABLE_CI
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_CI_CMD\n"));
            eResult = _MApp_AT_CICmdHandler(ATCmd);
        #else
            DEBUG_AUTOTEST(printf("Not Support CI Feature\n"));
            eResult = EN_AT_RESULT_ER;
        #endif
            break;
        }

        case EN_AUTO_TEST_CMD_TYPE_OSD_DUMP_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_OSD_DUMP_CMD\n"));
            eResult = _MApp_AT_OSDCmdHandler(ATCmd);
            break;
        }

        case EN_AUTO_TEST_CMD_TYPE_EPG_CMD:
        {
        #if (ENABLE_DTV_EPG)
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_EPG_CMD\n"));
            eResult = _MApp_AT_EPGCmdHandler(ATCmd);
        #else
            DEBUG_AUTOTEST(printf("Not Support EPG Feature\n"));
            eResult = EN_AT_RESULT_ER;
        #endif
            break;
        }

        case EN_AUTO_TEST_CMD_TYPE_OAD_CMD:
        {
            DEBUG_AUTOTEST(printf("EN_AUTO_TEST_CMD_TYPE_OAD_CMD\n"));
            eResult = _MApp_AT_OADCmdHandler(ATCmd);
            break;
        }
        default:
        {
            printf("Wrong CmdType=0x%X! \n", ATCmd.u8CmdType);
            eResult = EN_AT_RESULT_ER;
            break;
        }
    }

    if( eResult == EN_AT_RESULT_ONGOING)
    {
        s_AutoTest_Info.eATState = AT_STATE__WAIT_CMD_DONE;

    }
    else
    {
        MApp_AT_RetStatus((EN_AT_Reply)eResult);

        _MApp_AT_ChangeStateTo(AT_STATE__WAIT_INPUT_STR);
    }

    return TRUE;
}


#if(AT_IR_SIM)
static BOOLEAN _MApp_AT_CheckIRKeySimulation(void)
{
    BOOLEAN bResult = TRUE;


    if( s_AT_RxBuf.m_u8Index != 1 )
        return FALSE;

    if( Auto_Test_Index1 == 'e' )
        s_AT_enIRKeySimulation = EN_AT_IR_SIM_EXIT;
    else if( Auto_Test_Index1== 'y' )
        s_AT_enIRKeySimulation = EN_AT_IR_SIM_LEFT;
    else if( Auto_Test_Index1== 'n' )
        s_AT_enIRKeySimulation = EN_AT_IR_SIM_RIGHT;
    else
    {
        s_AT_enIRKeySimulation = EN_AT_IR_SIM_NULL;
        bResult = FALSE;
    }
    return bResult;
}
#endif

void MApp_AT_Task(void)
{

    // Parse CMD
    if( s_AutoTest_Info.eATState == AT_STATE__PARSE_CMD )
    {
        MApp_AT_ProecssRxBuffer();
    }


    // Exec CMD
    if( s_AutoTest_Info.eATState == AT_STATE__EXEC_CMD )
    {
        _MApp_AT_CmdHandler();
    }

    // Check signal status after change source
    if( g_AT_bChangeSource )
    {
        U32 u32CurTime = MsOS_GetSystemTime();
        U32 u32TimeoutTime = 5000;  //set default to 5000 for all source

#if 0
        if( MApp_IsInputSrcUseHDMIPort(MAIN_WINDOW) )
        {
            u32TimeoutTime = 4000;
        }
        else if( MApp_IsInputSrcUseAVD(MAIN_WINDOW) )
        {
            u32TimeoutTime = 1800;
        }


#endif

        //printf("Check signal at %u\n", u32CurTime);

        if( g_AT_u32ChangeSourceTime > u32TimeoutTime )
        {
            printf("Check signal timeout(%u) at %u\n", u32TimeoutTime, u32CurTime );

            if( MApp_IsSrcHasSignal(MAIN_WINDOW) )
            {
                MApp_AT_SendEvent( E_AT_EVENT_CHANGE_SOURCE_UNMUTE, (void*)u32CurTime);
            }
            else
            {
                MApp_AT_SendEvent( E_AT_EVENT_CHANGE_SOURCE_NO_SIGNAL, (void*)u32CurTime);
            }
            g_AT_bChangeSource = FALSE;
        }
    }

}

//========================================================================

static U32 s_AT_u32BootTimeStart = 0;
static U32 s_AT_u32ChangeChannelTimeStart = 0;

void MApp_AT_SendEvent(EnuAutoTestEvent enATEvent, void* pvInfo)
{
    U32 u32Tmp = (U32)pvInfo;
    pvInfo = pvInfo;

    switch( enATEvent )
    {
        case E_AT_EVENT_BOOT_TIME_START:
            printf("[CK3_Auto_Test] boot time start=%u\n", u32Tmp);
            s_AT_u32BootTimeStart = u32Tmp;
            break;

        case E_AT_EVENT_BOOT_TIME_END:
            //printf("boot time end=%u\n", u32Tmp);
            if( s_AT_u32BootTimeStart != 0xFFFFFFFF )
            {
                MApp_AT_RetStatus(EN_AT_REPLY_STATUS_TV_INIT);
                //if( UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_ATV )
                {
                    printf("[CK3_Auto_Test] boot time = %ld\n", msAPI_Timer_DiffTime_2(s_AT_u32BootTimeStart, u32Tmp));
                }

                s_AT_u32BootTimeStart = 0xFFFFFFFF;
            }
            break;

        case E_AT_EVENT_CHANGE_CHANNEL_TIME_START:
            s_AT_u32ChangeChannelTimeStart = u32Tmp;
            //printf("[CK3_Auto_Test] Change channel time start=%u\n", u32Tmp);
            break;

        case E_AT_EVENT_CHANGE_CHANNEL_TIME_END:
            if( s_AT_u32ChangeChannelTimeStart != 0xFFFFFFFF )
            {
                //if( UI_INPUT_SOURCE_TYPE == UI_INPUT_SOURCE_ATV )
                {
                    printf("\n [CK3_Auto_Test] ch change time = %ld\n", msAPI_Timer_DiffTime_2(s_AT_u32ChangeChannelTimeStart, u32Tmp));
                }

                s_AT_u32ChangeChannelTimeStart = 0xFFFFFFFF;
            }
            break;

        case E_AT_EVENT_ATV_AUTO_SCAN_FINISH:
            if( (s_AutoTest_Info.eATState == AT_STATE__WAIT_CMD_DONE)
              &&(g_AT_enATVAutoTuningState == E_AUTO_TEST_TUNING_START)
              )
            {
                MApp_AT_RetStatus((EN_AT_Reply)EN_AT_RESULT_OK);
                g_AT_enATVAutoTuningState = E_AUTO_TEST_TUNING_END;
                s_AutoTest_Info.eATState = AT_STATE__WAIT_INPUT_STR;
                PRINT_AUTOTEST_CHECKPT_TIME("finish atv auto scan");
                printf("E_AUTO_TEST_TUNING_END\n");
            }
            break;

        case E_AT_EVENT_ATV_MANUAL_SCAN_FINISH:
            if( (s_AutoTest_Info.eATState == AT_STATE__WAIT_CMD_DONE)
              &&(g_AT_enATVManualTuningState == E_AUTO_TEST_TUNING_START)
              )
            {
                MApp_AT_RetStatus((EN_AT_Reply)EN_AT_RESULT_OK);
                g_AT_enATVManualTuningState = E_AUTO_TEST_TUNING_END;
                s_AutoTest_Info.eATState = AT_STATE__WAIT_INPUT_STR;
                printf("E_AUTO_TEST_TUNING_END\n");
            }
            break;

    #if(ENABLE_DTV)
        case E_AT_EVENT_DTV_AUTO_SCAN_FINISH:
            if( (s_AutoTest_Info.eATState == AT_STATE__WAIT_CMD_DONE)
              &&(g_AT_enDTVAutoTuningState == E_AUTO_TEST_TUNING_START)
              )
            {
                MApp_AT_RetStatus((EN_AT_Reply)EN_AT_RESULT_OK);
                g_AT_enDTVAutoTuningState = E_AUTO_TEST_TUNING_END;
                s_AutoTest_Info.eATState = AT_STATE__WAIT_INPUT_STR;
                PRINT_AUTOTEST_CHECKPT_TIME("finish dtv auto scan");
            }
            break;

        case E_AT_EVENT_DTV_MANUAL_SCAN_FINISH:
            if( (s_AutoTest_Info.eATState == AT_STATE__WAIT_CMD_DONE)
              &&(g_AT_enDTVManualTuningState == E_AUTO_TEST_TUNING_START)
              )
            {
                MApp_AT_RetStatus((EN_AT_Reply)EN_AT_RESULT_OK);
                g_AT_enDTVManualTuningState = E_AUTO_TEST_TUNING_END;
                s_AutoTest_Info.eATState = AT_STATE__WAIT_INPUT_STR;
            }
            break;
    #endif

    case E_AT_EVENT_CHANGE_SOURCE_UNMUTE:
    case E_AT_EVENT_CHANGE_SOURCE_NO_SIGNAL:
        if(s_AutoTest_Info.eATState == AT_STATE__WAIT_CMD_DONE)
        {
            if (E_AT_EVENT_CHANGE_SOURCE_UNMUTE == enATEvent)
            {
                PRINT_AUTOTEST_CHECKPT_TIME("source change unmute video");
            }
            else
            {
                PRINT_AUTOTEST_CHECKPT_TIME("source change no signal");
            }
            MApp_AT_RetStatus((EN_AT_Reply)EN_AT_RESULT_OK);
            s_AutoTest_Info.eATState = AT_STATE__WAIT_INPUT_STR;
            g_AT_u32UnmuteVideo = u32Tmp;
            g_AT_bChangeSource = FALSE;
        }
        break;
    }

}

//================================================================
U8 MApp_AT_MVKToIrKey(EN_AT_KEYCODE_MVK enAutoTestMVK)
{
    U8 irKey = IRKEY_DUMY;

    switch(enAutoTestMVK)
    {
        case EN_AT_KEYCODE_MVK_CHANNEL_LIST:
            irKey = IRKEY_CHANNEL_LIST;
            break;
        case EN_AT_KEYCODE_MVK_CHANNEL_RETURN:
            irKey = IRKEY_CHANNEL_RETURN;
            break;
        case EN_AT_KEYCODE_MVK_CHANNEL_PLUS:
            irKey = IRKEY_CHANNEL_PLUS;
            break;
        case EN_AT_KEYCODE_MVK_CHANNEL_MINUS:
            irKey = IRKEY_CHANNEL_MINUS;
            break;
        case EN_AT_KEYCODE_MVK_AUDIO:
            irKey = IRKEY_AUDIO;
            break;
        case EN_AT_KEYCODE_MVK_VOLUME_PLUS:
            irKey = IRKEY_VOLUME_PLUS;
            break;
        case EN_AT_KEYCODE_MVK_VOLUME_MINUS:
            irKey = IRKEY_VOLUME_MINUS;
            break;
        case EN_AT_KEYCODE_MVK_UP:
            irKey = IRKEY_UP;
            break;
        case EN_AT_KEYCODE_MVK_DOWN:
            irKey = IRKEY_DOWN;
            break;
        case EN_AT_KEYCODE_MVK_LEFT:
            irKey = IRKEY_LEFT;
            break;
        case EN_AT_KEYCODE_MVK_RIGHT:
            irKey = IRKEY_RIGHT;
            break;
        case EN_AT_KEYCODE_MVK_POWER:
            irKey = IRKEY_POWER;
            break;
        case EN_AT_KEYCODE_MVK_EXIT:
            irKey = IRKEY_EXIT;
            break;
        case EN_AT_KEYCODE_MVK_MENU:
            irKey = IRKEY_MENU;
            break;
        case EN_AT_KEYCODE_MVK_SELECT:
            irKey = IRKEY_SELECT;
            break;
        case EN_AT_KEYCODE_MVK_NUM_0:
            irKey = IRKEY_NUM_0;
            break;
        case EN_AT_KEYCODE_MVK_NUM_1:
            irKey = IRKEY_NUM_1;
            break;
        case EN_AT_KEYCODE_MVK_NUM_2:
            irKey = IRKEY_NUM_2;
            break;
        case EN_AT_KEYCODE_MVK_NUM_3:
            irKey = IRKEY_NUM_3;
            break;
        case EN_AT_KEYCODE_MVK_NUM_4:
            irKey = IRKEY_NUM_4;
            break;
        case EN_AT_KEYCODE_MVK_NUM_5:
            irKey = IRKEY_NUM_5;
            break;
        case EN_AT_KEYCODE_MVK_NUM_6:
            irKey = IRKEY_NUM_6;
            break;
        case EN_AT_KEYCODE_MVK_NUM_7:
            irKey = IRKEY_NUM_7;
            break;
        case EN_AT_KEYCODE_MVK_NUM_8:
            irKey = IRKEY_NUM_8;
            break;
        case EN_AT_KEYCODE_MVK_NUM_9:
            irKey = IRKEY_NUM_9;
            break;
        case EN_AT_KEYCODE_MVK_MUTE:
            irKey = IRKEY_MUTE;
            break;
#if ENABLE_DMP
        case EN_AT_KEYCODE_MVK_PAGE_UP:
            irKey = IRKEY_PAGE_UP;
            break;
#endif
        case EN_AT_KEYCODE_MVK_PAGE_DOWN:
            irKey = IRKEY_PAGE_DOWN;
            break;
        case EN_AT_KEYCODE_MVK_INFO:
            irKey = IRKEY_INFO;
            break;
        case EN_AT_KEYCODE_MVK_RED:
            irKey = IRKEY_RED;
            break;
        case EN_AT_KEYCODE_MVK_GREEN:
            irKey = IRKEY_GREEN;
            break;
        case EN_AT_KEYCODE_MVK_YELLOW:
            irKey = IRKEY_YELLOW;
            break;
        case EN_AT_KEYCODE_MVK_BLUE:
            irKey = IRKEY_BLUE;
            break;
        case EN_AT_KEYCODE_MVK_INPUT_SOURCE:
            irKey = IRKEY_INPUT_SOURCE;
            break;
        case EN_AT_KEYCODE_MVK_EPG:
            irKey = IRKEY_EPG;
            break;
        case EN_AT_KEYCODE_MVK_MTS:
            irKey = IRKEY_MTS;
            break;
        case EN_AT_KEYCODE_MVK_TTX:
            irKey = IRKEY_TTX;
            break;
        case EN_AT_KEYCODE_MVK_SLEEP:
            irKey = IRKEY_SLEEP;
            break;
        case EN_AT_KEYCODE_MVK_ZOOM:
            irKey = IRKEY_ZOOM;
            break;
        case EN_AT_KEYCODE_MVK_INDEX:
            irKey = IRKEY_INDEX;
            break;
        case EN_AT_KEYCODE_MVK_PLAY:
            irKey = IRKEY_PLAY;
            break;
        case EN_AT_KEYCODE_MVK_PAUSE:
            irKey = IRKEY_PAUSE;
            break;
        case EN_AT_KEYCODE_MVK_STOP:
            irKey = IRKEY_STOP;
            break;
        case EN_AT_KEYCODE_MVK_NEXT:
            irKey = IRKEY_NEXT;
            break;
        case EN_AT_KEYCODE_MVK_PREVIOUS:
            irKey = IRKEY_PREVIOUS;
            break;
        case EN_AT_KEYCODE_MVK_FORWARD:
            irKey = IRKEY_FORWARD;
            break;
        case EN_AT_KEYCODE_MVK_BACKWARD:
            irKey = IRKEY_BACKWARD;
            break;
        case EN_AT_KEYCODE_MVK_CC:
            irKey = IRKEY_CC;
            break;
        case EN_AT_KEYCODE_MVK_RECORD:
            irKey = IRKEY_RECORD;
            break;
        case EN_AT_KEYCODE_MVK_SUBTITLE:
            irKey = IRKEY_SUBTITLE;
            break;
        case EN_AT_KEYCODE_MVK_SUBCODE:
            irKey = IRKEY_SUBCODE;
            break;
        case EN_AT_KEYCODE_MVK_PHOTO:
            irKey = IRKEY_PHOTO;
            break;
        case EN_AT_KEYCODE_MVK_FREEZE:
            irKey = IRKEY_FREEZE;
            break;
        case EN_AT_KEYCODE_MVK_PIP:
            irKey = IRKEY_PICTURE;
            break;
        case EN_AT_KEYCODE_MVK_MIX:
            irKey = IRKEY_MIX;
            break;
        case EN_AT_KEYCODE_MVK_GUIDE:
            irKey = IRKEY_GUIDE;
            break;
        case EN_AT_KEYCODE_MVK_HOLD:
            irKey = IRKEY_HOLD;
            break;
        case EN_AT_KEYCODE_MVK_UPDATE:
            irKey = IRKEY_UPDATE;
            break;
        case EN_AT_KEYCODE_MVK_REVEAL:
            irKey = IRKEY_REVEAL;
            break;
        case EN_AT_KEYCODE_MVK_SIZE:
            irKey = IRKEY_SIZE;
            break;
        case EN_AT_KEYCODE_MVK_CLOCK:
            irKey = IRKEY_CLOCK;
            break;
        default:
            break;
    }

    return irKey;
}

BOOL MApp_AT_Get_SimuIRKey(U8 *pu8IrKey)
{
    BOOL bRtn = FALSE;
    U8 _u8Key = IRKEY_DUMY;


    if( s_AT_enKeyCode_MVK != EN_AT_KEYCODE_NULL )
    {
        _u8Key = MApp_AT_MVKToIrKey(s_AT_enKeyCode_MVK);
        if( _u8Key != IRKEY_DUMY )
        {
            bRtn = TRUE;
        }
        s_AT_enKeyCode_MVK = EN_AT_KEYCODE_NULL;
    }
#if(AT_IR_SIM)
    else if( s_AT_enIRKeySimulation != EN_AT_IR_SIM_NULL )
    {
        bRtn = TRUE;
        switch(s_AT_enIRKeySimulation)
        {
            case EN_AT_IR_SIM_EXIT:
                _u8Key = IRKEY_EXIT;
                break;
            case EN_AT_IR_SIM_LEFT:
                _u8Key = IRKEY_LEFT;
                break;
            case EN_AT_IR_SIM_RIGHT:
                _u8Key = IRKEY_RIGHT;
                break;
            default:
                bRtn = FALSE;
                break;
        }
        s_AT_enIRKeySimulation = EN_AT_IR_SIM_NULL;
    }
#endif

    if( bRtn )
    {
        *pu8IrKey = _u8Key;
    }

    return bRtn;
}

#endif

#undef MAPP_AUTOTEST_C

