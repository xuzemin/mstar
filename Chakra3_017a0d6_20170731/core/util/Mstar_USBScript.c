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
#define _MSTAR_USBSCRIPT_C_
////////////////////////////////////////////////////////////////////////////////
///
/// @file mstar_USBscript.c
/// @author MStar Semiconductor Inc.
/// @brief MStar Debug Related Functions
///
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*                              Header Files                                  */
/******************************************************************************/
// C Library
#include <stdio.h>
#include <string.h>

#if defined(__aeon__)
#include "risc32_spr.h"
#endif

// Global
#include "datatype.h"
#include "debug.h"
#include "sysinfo.h"
#include "SysInit.h"
#if (ENABLE_UART_MSG_TO_USB)
#include "MApp_GlobalSettingSt.h"
#endif
#include "msAPI_Global.h"
#include "msAPI_Tuning.h"
//...

// Driver Layer
#include "drvUSB.h"
//...

// API Layer
//#include "msAPI_Subtitle_Pub.h"
#include "msAPI_FCtrl.h"
#include "msAPI_MSDCtrl.h"
#include "msAPI_Timer.h"
//...

// MW Layer
#include "mstar_debug.h"
#include "mw_debug.h"
#if(ENABLE_DEBUG_DELAY_TIME&&ENABLE_DTV)
#include "msAPI_DTV_Common.h"
#endif

#include "Mstar_USBScript.h"


#if (ENABLE_SCRIPT_EXECUTE)

#define DEBUG_ES(x) //x
#define EXECUTE_SCRIPT_FILE_NAME   "MsUSB_DebugScript.txt"       //script name
#define FILE_BUFFER_SIZE (80*COMMAND_AMOUNT)  //80 : upper bond cahr per line about script CMD
#define COMMAND_AMOUNT 100
#define EVENT_AMOUNT 10
#define MESSAGE_CAHR_AMOUNT 256

//==============================================================//
static BOOL _s_ES_bFileSystemInited = FALSE;
static U8 _s_ES_u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;
//static FileEntry _s_ES_FileEntry;
static U8 _s_ES_u8FileHandle = INVALID_FILE_HANDLE;
//static BOOL _s_ES_bInitDone = FALSE;
//static BOOL _s_ES_bEnable = FALSE;
static U16 CurrentCommandAmount =0;      //current commandpool amount
static U8 CurrentEventCommandCount =0;  //count event's command
static EN_SCRIPT_EVENT_TYPE CurrentReadEvent = EN_SCRIPT_EVENT_NONE;
static U8 CurrentMessageAmount = 0;
static U8 USB_Insert = 0;
static U8 USB_ReadFinished = 0;
//==============================================================//
//static EnuU2ULogMode s_U2U_eLogMode = U2U_MODE_LOG_SAVE_TO_USB_DISABLE;
//static U16 s_U2U_u16Count_OpenFile = 0;
//static U32 s_U2U_u32ErrorCount_WriteFile = 0;
//static BOOL s_U2U_bProtectRecursive = FALSE;
//static U16 _s_U2U_u16FileNameCount = 0;



static MSUS_SCRIPT_COMMAND CommandPool[COMMAND_AMOUNT];
static MSUS_SCRIPT_EVENT EventPool[EVENT_AMOUNT];
static char MessagePool[MESSAGE_CAHR_AMOUNT];
static EVENT_NAME_TABLE EventNameTable[EVENT_AMOUNT] =
{
    {   EN_SCRIPT_EVENT_INIT,   "Init", },
    {   EN_SCRIPT_EVENT_INPUTSOURCE_SWITCHSOURCE,   "InputSource_SwitchSource", },
    {   EN_SCRIPT_EVENT_CHANNELCHANGE,   "ChannelChange", },
    {   EN_SCRIPT_EVENT_PROCESSUSERINPUT,   "ProcessUserInput", },
    {   EN_SCRIPT_EVENT_NONE,   NULL, },
};

void MApp_DbgATV_Scan(DWORD dwMinPLL, DWORD dwMaxPLL, U8 bNumber);

static BOOL _CompareString_U8_U16(char* pcStr, U16* pu16Str, U8 u8MaxLen)
{
    U8 i;
    BOOL bRtn = TRUE;
    U16 c1, c2;


    for( i = 0; i < u8MaxLen; ++ i )
    {
        c1 = pcStr[i];
        c2 = pu16Str[i];

    /*
        if ((c1 >= 'a') && (c1 <= 'z'))
        {
            c1 -= 'a' - 'A';
        }

        if ((c2 >= 'a') && (c2 <= 'z'))
        {
            c2 -= 'a' - 'A';
        }
        */

        if( c1 != c2 )
        {
            bRtn = FALSE;
            break;
        }

        if( c1 == 0 )
            break;

    }

    return bRtn;
}

static U32 msUS_Pow(U8 base,U8 exponet)
{
    U8 count;
    U32 sum=1;
    for(count = 0;count<exponet;count++)
    {
        sum *= base;
    }
    return sum;
}

BOOL msUS_CheckEventPoolEmpty(void)
{
    U8 i;
    for(i=0;i<EVENT_AMOUNT;i++)
    {
        if(EventPool[i].event !=EN_SCRIPT_EVENT_NONE)
        {
            return TRUE;
        }
    }

    return FALSE;
}



EN_SCRIPT_EVENT_TYPE msUS_CompareExecuteEventName(char* EventName)
{
    U8 i;
    for(i=0;i<EVENT_AMOUNT;i++)
    {
        if(stricmp(EventName , EventNameTable[i].name) == 0)
        {
            return EventNameTable[i].EventType;
        }
    }

    return EN_SCRIPT_EVENT_NONE;
}

BOOL msUS_ParseEvent(char* eventName, U8 u8EventNameLength)
{
    U8 i;
    DEBUG_ES(printf("event name: \"%s\"\n",eventName););
    DEBUG_ES(printf("event name length is %d\n",strlen(eventName)););
    for(i=0;i<EVENT_AMOUNT;i++)
    {
        if(strncmpi(eventName , EventNameTable[i].name, u8EventNameLength) == 0)
        {
            break;
        }
    }
    if(i>=EVENT_AMOUNT)
    {
        DEBUG_ES(printf("No such Event!!\t\n"););
        return FALSE;
    }
    else
    {   //first event
        if(CurrentReadEvent ==EN_SCRIPT_EVENT_NONE)
        {
            EventPool[EventNameTable[i].EventType].event = EventNameTable[i].EventType;
            EventPool[EventNameTable[i].EventType].u8CommandStart = 0;
            EventPool[EventNameTable[i].EventType].u8CommandLength = 0;
            CurrentReadEvent = EventNameTable[i].EventType;
            DEBUG_ES(printf("Start Parse Event: %s\t\n",EventNameTable[i].name););
        }
        else//others
        {
            if(EventPool[EventNameTable[i].EventType].event == EventNameTable[i].EventType)
            {
                DEBUG_ES(printf("%s\n",EventNameTable[CurrentReadEvent].name););
                DEBUG_ES(printf("%s\n",EventNameTable[i].name););
                DEBUG_ES(printf("Event already exists!!\t\n"););
                return FALSE;
            }
            else
            {
                //update last event data
                //EventPool[CurrentReadEvent].u8CommandStart = CurrentCommandAmount-CurrentEventCommandCount+1;
                EventPool[CurrentReadEvent].u8CommandLength = CurrentEventCommandCount - 1; //cut event title line "@xxxx"
                //update current event data and start read current event command
                EventPool[EventNameTable[i].EventType].event = EventNameTable[i].EventType;
                EventPool[EventNameTable[i].EventType].u8CommandStart = EventPool[CurrentReadEvent].u8CommandStart + EventPool[CurrentReadEvent].u8CommandLength;
                EventPool[EventNameTable[i].EventType].u8CommandLength = 0;
                CurrentReadEvent = EventNameTable[i].EventType;
                CurrentEventCommandCount =0;//clear current command count
                DEBUG_ES(printf("Start Parse Event: %s\t\n",EventNameTable[i].name););
            }
        }

        return TRUE;
    }
}

BOOL msUS_ParseCommand(char* commandName, U8 u8CommandName)
{
    //define command table//
    typedef struct
    {
        EN_SCRIPT_COMMAND_TYPE tCommandtype;
        char* tCommandName;
    }tempCommandTable;

    const tempCommandTable LocalCommandTable[] =         //8 EN_SCRIPT_COMMAND_TYPE amount
    {
        {   EN_SCRIPT_COMMAND_RRIU,                     "rriu",},
        {   EN_SCRIPT_COMMAND_WRIU,                    "wriu",},
        {   EN_SCRIPT_COMMAND_CHECK,                  "check",},
        {   EN_SCRIPT_COMMAND_LOG,                      "log",},
        {   EN_SCRIPT_COMMAND_MCUPAUSE,            "mcu_pause",},
        {   EN_SCRIPT_COMMAND_DUMPBANK,            "dump_bank",},
        {   EN_SCRIPT_COMMAND_DELAY,                   "delay",},
        {   EN_SCRIPT_COMMAND_UART2USBON,        "uart2usbon",},
        {   EN_SCRIPT_COMMAND_DBGATVSCAN,        "DbgATVScan",},
    };
    //////////////////////////////////////////////////
    U8 i;
    for(i=0;i<COMMAND_AMOUNT;i++)
    {
        if(strncmpi(commandName,LocalCommandTable[i].tCommandName,u8CommandName) == 0)
        {
            break;
        }
    }

    if(i>=COMMAND_AMOUNT)
    {
        DEBUG_ES(printf("No such command support\t\n"););
        //DEBUG_ES(printf("%s\t\n",LocalCommandTable[i].tCommandName););
        return FALSE;
    }
    else
    {//choose command type
        DEBUG_ES(printf("commmand name: \"%s\" \n",LocalCommandTable[i].tCommandName););
        DEBUG_ES(printf("commmand type: \"%x\" \n",LocalCommandTable[i].tCommandtype););
        DEBUG_ES(printf("CurrentCommandAmount: %x\n",CurrentCommandAmount););
        CommandPool[CurrentCommandAmount].CommandType = LocalCommandTable[i].tCommandtype;
        return TRUE;
    }
}


BOOL msUS_ParseAddress(char* Address, U8 u8AddressLength)
{
    U8 u8Length = u8AddressLength;
    U8 i; //temp value
    U32 AddressResult = 0;

    DEBUG_ES(printf("msUS_ParseAddress (Address): \"%s\"\t\n",Address););
    //hex
    if(Address[0]=='0' &&
        ((Address[1]=='x')||(Address[1]=='X')))
    {
        for(i=2;i<u8Length;i++)
        {
            if((Address[i] >= '0') && (Address[i] <= '9'))
            {
                AddressResult += (Address[i] - '0') * msUS_Pow(16, ((u8Length-i)-1));
            }
            else if((Address[i] >= 'a') && (Address[i] <= 'f'))
            {
                AddressResult += (Address[i] - 'a' + 0xA) * msUS_Pow(16, ((u8Length-i)-1));
            }
            else if((Address[i] >= 'A') && (Address[i] <= 'F'))
            {
                AddressResult += (Address[i] - 'A' + 0xA) * msUS_Pow(16, ((u8Length-i)-1));
            }
            else
            {
                DEBUG_ES(printf("[ES](HEX)wrong format about Address!!\t\n"););
                return FALSE;
            }
        }
    }
    else
    {
        //decimal
        for(i=0;i<u8Length;i++)
        {
            if((Address[i] >= '0') && (Address[i] <= '9'))
            {
                AddressResult += (Address[i] -'0') * msUS_Pow(10, ((u8Length-i)-1));
            }
            else
            {
                DEBUG_ES(printf("[ES](DEC)wrong format about Address!!\t\n"););
                return FALSE;
            }
        }
    }

    if(AddressResult > 0xffffff)
    {
        DEBUG_ES(printf("[ES]Address over range!!\t\n"););
        return FALSE;
    }
    DEBUG_ES(printf("[ES]Address: %x\t\n",AddressResult););
    CommandPool[CurrentCommandAmount].CommonParameter.Address[0] = (U8)AddressResult;
    CommandPool[CurrentCommandAmount].CommonParameter.Address[1] = (U8)(AddressResult >> 8);
    CommandPool[CurrentCommandAmount].CommonParameter.Address[2] = (U8)(AddressResult >> 16);
    return TRUE;
}

U16 msUS_ParseSecond(char* second,U8 u8secondLength)
{
    U8 u8Length = u8secondLength;
    U8 i; //temp value
    U16 sum=0;

    for(i=0;i<u8Length;i++)
    {
        if((second[i] >= '0') && (second[i] <= '9'))
        {
            sum += (second[i] - '0') * msUS_Pow(10, ((u8Length-i)-1));
        }
        else
        {
            DEBUG_ES(printf("[ES]wrong format about Second!!\t\n"););
            return FALSE;
        }
    }

    if(sum>10000)
    {
        DEBUG_ES(printf("[ES](Line %d)Second over range!!\t\n",CurrentCommandAmount););
        return FALSE;
    }

    CommandPool[CurrentCommandAmount].CommonParameter.Second = sum;
    return TRUE;
}

BOOL msUS_ParseMessage(char* message, U8 u8MessageLength)
{
    U8 u8Length = u8MessageLength;
    DEBUG_ES(printf("u8Length : %x\n",u8Length););
    U8 i;

    if((CurrentMessageAmount + u8Length + 1) > MESSAGE_CAHR_AMOUNT)
    {
        DEBUG_ES(printf("[ES]Message buffer was not enough!!\t\n"););
        return FALSE;
    }

    for(i=0;i<u8Length;i++)
    {
        MessagePool[(CurrentMessageAmount+i)] = message[i];
        DEBUG_ES(printf("MessagePool[(CurrentMessageAmount+i)]  is %c, ",MessagePool[(CurrentMessageAmount+i)] ););
        DEBUG_ES(printf("message[i]  is %c\n",message[i]););
    }
    MessagePool[(CurrentMessageAmount+u8Length)] = '\0'; //add null char for message end
    DEBUG_ES(printf("CurrentMessageAmount : %x\t\n",CurrentMessageAmount););
    CommandPool[CurrentCommandAmount].CommonParameter.MessagePoint = CurrentMessageAmount;//message start position for its command
    DEBUG_ES(printf("CommandPool[CurrentCommandAmount].CommonParameter.MessagePoint : %x\t\n",CommandPool[CurrentCommandAmount].CommonParameter.MessagePoint););
    CurrentMessageAmount = CurrentMessageAmount + u8Length +1;//next restore position
    DEBUG_ES(printf("CurrentMessageAmount : %x\t\n",CurrentMessageAmount););

    return TRUE;
}

BOOL msUS_ParseValue(char* value,U8 u8ValueLength)
{
    U8 u8Length = u8ValueLength;
    U8 i; //temp value
    U16 sum=0;
    DEBUG_ES(printf("msUS_ParseValue is \"%s\"\n",value););
    DEBUG_ES(printf("msUS_ParseValue u8Length is %d\n",u8Length););
    //hex
    if(value[0]=='0' &&
        ((value[1]=='x')||(value[1]=='X')))
    {
        for(i=2;i<u8Length;i++)
        {
            if((value[i] >= '0') && (value[i] <= '9'))
            {
                sum += (value[i] - '0') * msUS_Pow(16, ((u8Length-i)-1));
                DEBUG_ES(printf("msUS_ParseValue sum is %d\n",sum););
            }
            else
            {
                DEBUG_ES(printf("[ES](HEX)wrong format about value!!\t\n"););
                return FALSE;
            }
        }
    }
    else
    {
        //decimal
        for(i=0;i<u8Length;i++)
        {
            if((value[i] >= '0') && (value[i] <= '9'))
            {
                sum += (value[i] - '0') * msUS_Pow(10, ((u8Length-i)-1));
            }
            else
            {
                DEBUG_ES(printf("[ES](DEC)wrong format about value!!\t\n"););
                return FALSE;
            }
        }
    }
    if(sum>0xff)
    {
        DEBUG_ES(printf("[ES](Line %d)Value over range!!\t\n",CurrentCommandAmount););
        return FALSE;
    }

    CommandPool[CurrentCommandAmount].u8value  = sum;
    return TRUE;
}

BOOL msUS_ParseMask(char* mask,U8 u8MaskLength)
{
    U8 u8Length = u8MaskLength;
    U8 i; //temp value
    U16 sum=0;

    //hex
    if(mask[0]=='0' &&
        ((mask[1]=='x')||(mask[1]=='X')))
    {
        for(i=2;i<u8Length;i++)
        {
            if((mask[i] >= '0') && (mask[i] <= '9'))
            {
                sum += (mask[i] -'0') * msUS_Pow(16, ((u8Length-i)-1));
            }
            else if((mask[i] >= 'a') && (mask[i] <= 'f'))
            {
                sum += (mask[i] -'a' + 0x0A) * msUS_Pow(16, ((u8Length-i)-1));
            }
            else if((mask[i] >= 'A') && (mask[i] <= 'F'))
            {
                sum += (mask[i] -'A' + 0x0A) * msUS_Pow(16, ((u8Length-i)-1));
            }
            else
            {
                DEBUG_ES(printf("[ES](HEX)wrong format about mask!!\t\n"););
                return FALSE;
            }
        }
    }
    else
    {
        //decimal
        for(i=0;i<u8Length;i++)
        {
            if((mask[i] >= '0') && (mask[i] <= '9'))
            {
                sum += (mask[i] - '0') * msUS_Pow(10, ((u8Length-i)-1));
            }
            else
            {
                DEBUG_ES(printf("[ES](DEC)wrong format about mask!!\t\n"););
                return FALSE;
            }
        }
    }
    if(sum>0xff)
    {
        DEBUG_ES(printf("[ES](Line %d)Mask over range!!\t\n",CurrentCommandAmount););
        return FALSE;
    }

    CommandPool[CurrentCommandAmount].CommonParameter2.mask= sum;
    return TRUE;
}

U32 msUS_ParseFrequency(char* frequency,U8 u8frequencyLength)
{
    U8 u8Length = u8frequencyLength;
    U8 i; //temp value
    U32 sum=0;
    DEBUG_ES(printf("msUS_ParseFrequency is \"%s\"\n",frequency););
    DEBUG_ES(printf("msUS_ParseFrequency u8Length is %d\n",u8Length););
    //hex
    if(frequency[0]=='0' &&
        ((frequency[1]=='x')||(frequency[1]=='X')))
    {
        for(i=2;i<u8Length;i++)
        {
            if((frequency[i] >= '0') && (frequency[i] <= '9'))
            {
                sum += (frequency[i] - '0') * msUS_Pow(16, ((u8Length-i)-1));
                DEBUG_ES(printf("msUS_ParseFrequency sum is %d\n",sum););
            }
            else
            {
                DEBUG_ES(printf("[ES](HEX)wrong format about frequency!!\t\n"););
                return FALSE;
            }
        }
    }
    else
    {
        //decimal
        for(i=0;i<u8Length;i++)
        {
            if((frequency[i] >= '0') && (frequency[i] <= '9'))
            {
                sum += (frequency[i] - '0') * msUS_Pow(10, ((u8Length-i)-1));
            }
            else
            {
                DEBUG_ES(printf("[ES](DEC)wrong format about frequency!!\t\n"););
                return FALSE;
            }
        }
    }
    if((sum > 80025) || (sum < 4325))
    {
        DEBUG_ES(printf("[ES](Line %d)frequency over range!!\t\n",CurrentCommandAmount););
        return FALSE;
    }

    return sum;
}

BOOL msUS_ParseLine(U8 *LineString,U8 LineLength)
{
    //-----------------------event token @---------------------------//
    U8 token[80];
    //token = (U8*)malloc(sizeof(U8)*80);//80:character uper-bound per line
    memset(token,0,80);
    U8 u8CharCount=0;
    U8 u8TokenCount = 0; //0:command 1:parameter1 2:parameter2 3:parameter3
    U8 u8TokenCharCount = 0;
    BOOL bParseResult = FALSE;
    U8 bLogMessageFlag = 0;//reading log message... (")
    for(u8CharCount=0;u8CharCount<LineLength;u8CharCount++,u8TokenCharCount++)
    {
        if((LineString[u8CharCount] != 0x20) && (LineString[u8CharCount] != 0x22))
        {
            token[u8TokenCharCount] = LineString[u8CharCount] ;
            DEBUG_ES(printf("*(token + u8CharCount) is %c\n",token[u8TokenCharCount]););
            DEBUG_ES(printf("LineString[u8CharCount]  is %c\n",LineString[u8CharCount]););
        }
        else if(LineString[u8CharCount] == 0x22)// log message "xxxxx"
        {
            bLogMessageFlag++;
            if(bLogMessageFlag>2)
            {
                DEBUG_ES(printf("Log Message format error!!\t\n"););
                return FALSE;
            }
            if(bLogMessageFlag == 2)
            {
                bLogMessageFlag = 0;
            }
            u8TokenCharCount--;
        }
        else if((LineString[u8CharCount] == 0x20) && (bLogMessageFlag ==1)) //log message `s blank ' '
        {
            token[u8TokenCharCount] = LineString[u8CharCount] ;
        }
        else if((LineString[u8CharCount] == 0x20) && (bLogMessageFlag ==0))
        {
            //u8CharCount = u8CharCount - 1;//avoid count blank
            //-----------------------parse event-------------------------//
            if(token[0] == '@')
            {
                U8 i;
                char EventName[u8TokenCharCount - 1];
                DEBUG_ES(printf("EventName length is %d\n",strlen(EventName)););
                for(i=0;i<(u8TokenCharCount - 1);i++)
                {
                    EventName[i] = token[i+1];
                    DEBUG_ES(printf("EventName[i] is %c,  token[i+1] is %c\t\n",EventName[i],token[i+1]););
                }

                DEBUG_ES(printf("EventName: \"%s\"\n",EventName););
                bParseResult = msUS_ParseEvent(EventName, (u8TokenCharCount - 1));

                if(bParseResult == FALSE)
                {
                    return FALSE;
                }
                CurrentCommandAmount--;
            }
            else
            //-----------------------parse command----------------------//
            {
                //DEBUG_ES(printf("\ntoken is \"%s\"\n",token););
                DEBUG_ES(printf("u8CharCount is \"%d\"\n",u8CharCount););
                DEBUG_ES(printf("u8TokenCharCount is %d\n",u8TokenCharCount););
                printf("u8TokenCount : %d\t\n",u8TokenCount);
                if(u8TokenCount == 0)
                {
                    char CommandName[u8TokenCharCount];
                    U8 i;
                    for(i=0;i<u8TokenCharCount;i++)
                    {
                        CommandName[i] = token[i];
                        DEBUG_ES(printf("CommandName[i] : %c\n",CommandName[i]););
                        DEBUG_ES(printf("token[i] : %c\n",token[i]););
                    }
                    DEBUG_ES(printf("command: %s \t\n",CommandName););

                    bParseResult = msUS_ParseCommand(CommandName, u8TokenCharCount);

                    if(bParseResult == FALSE)
                    {
                        return FALSE;
                    }
                    u8TokenCount++;
                }//-----------------parse parameter1-----------------------------//
                else if(u8TokenCount ==1)
                {
                    char ParameterName[u8TokenCharCount];
                    DEBUG_ES(printf("u8TokenCharCount is %d\n",u8TokenCharCount););
                    U8 i;
                    BOOL ParseResult;
                    U32 u32sum; //parse frequency
                    for(i=0;i<u8TokenCharCount;i++)
                    {
                        ParameterName[i] = token[i];
                        DEBUG_ES(printf("ParameterName[i] is %c,  ",ParameterName[i]););
                        DEBUG_ES(printf("token[i] is %c \n",token[i]););
                    }
                    DEBUG_ES(printf("ParameterName is \"%s\"\n",ParameterName););

                    switch(CommandPool[CurrentCommandAmount].CommandType)
                    {
                        case EN_SCRIPT_COMMAND_RRIU:
                        case EN_SCRIPT_COMMAND_WRIU:
                        case EN_SCRIPT_COMMAND_CHECK:
                        {
                            ParseResult = msUS_ParseAddress(ParameterName,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }

                        case EN_SCRIPT_COMMAND_DUMPBANK:
                        {
                            ParseResult = msUS_ParseAddress(ParameterName,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }

                        case EN_SCRIPT_COMMAND_LOG:
                        {
                            ParseResult = msUS_ParseMessage(ParameterName,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }

                        case EN_SCRIPT_COMMAND_DELAY:
                        {
                            ParseResult = msUS_ParseSecond(ParameterName,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }
                        case EN_SCRIPT_COMMAND_DBGATVSCAN:
                        {
                            u32sum = msUS_ParseFrequency(ParameterName,u8TokenCharCount);
                            if(u32sum ==FALSE)
                            {
                                return FALSE;
                            }
                            // 1st frequency
                            CommandPool[CurrentCommandAmount].CommonParameter.frequency1[0] = (U8)u32sum;
                            CommandPool[CurrentCommandAmount].CommonParameter.frequency1[1] = (U8)(u32sum >> 8);
                            CommandPool[CurrentCommandAmount].CommonParameter.frequency1[2] = (U8)(u32sum >> 16);
                            break;
                        }

                        case EN_SCRIPT_COMMAND_MCUPAUSE:
                        case EN_SCRIPT_COMMAND_UART2USBON:
                        {
                            DEBUG_ES(printf("[ES](Line %d)This command should not has parameter!!\t\n",CurrentCommandAmount););
                            return FALSE;
                            break;
                        }
                        default:
                            break;
                    }
                    u8TokenCount++;
                }
                //-----------------parse parameter2------------------------//
                else if(u8TokenCount == 2)
                {
                    char Parameter2Name[u8TokenCharCount];
                    U8 i;
                    BOOL ParseResult;
                    U32 u32sum;//parse frequency
                    for(i=0;i<u8TokenCharCount;i++)
                    {
                        Parameter2Name[i] = token[i];
                    }

                    switch(CommandPool[CurrentCommandAmount].CommandType)
                    {
                        case EN_SCRIPT_COMMAND_WRIU:
                        case EN_SCRIPT_COMMAND_CHECK:
                        {
                            ParseResult = msUS_ParseValue(Parameter2Name,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }

                        case EN_SCRIPT_COMMAND_DBGATVSCAN:
                        {
                            u32sum = msUS_ParseFrequency(Parameter2Name,u8TokenCharCount);
                            if(u32sum ==FALSE)
                            {
                                return FALSE;
                            }
                            // 2st frequency
                            CommandPool[CurrentCommandAmount].CommonParameter2.frequency2[0] = (U8)u32sum;
                            CommandPool[CurrentCommandAmount].CommonParameter2.frequency2[1] = (U8)(u32sum >> 8);
                            CommandPool[CurrentCommandAmount].CommonParameter2.frequency2[2] = (U8)(u32sum >> 16);
                            break;
                        }
                        case EN_SCRIPT_COMMAND_RRIU:
                        case EN_SCRIPT_COMMAND_DUMPBANK:
                        case EN_SCRIPT_COMMAND_LOG:
                        case EN_SCRIPT_COMMAND_DELAY:
                        case EN_SCRIPT_COMMAND_MCUPAUSE:
                        case EN_SCRIPT_COMMAND_UART2USBON:
                        {
                            DEBUG_ES(printf("[ES](Line %d)This command should not has parameter2!!\t\n",CurrentCommandAmount););
                            return FALSE;
                            break;
                        }
                        default:
                            break;
                    }
                    u8TokenCount++;
                }
                //-----------------parse parameter3------------------------//
                else if(u8TokenCount == 3)
                {
                    char Parameter3Name[u8TokenCharCount];
                    U8 i;
                    BOOL ParseResult;
                    for(i=0;i<u8TokenCharCount;i++)
                    {
                        Parameter3Name[i] = token[i];
                    }

                    switch(CommandPool[CurrentCommandAmount].CommandType)
                    {
                        case EN_SCRIPT_COMMAND_WRIU:
                        case EN_SCRIPT_COMMAND_CHECK:
                        {
                            ParseResult = msUS_ParseMask(Parameter3Name,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }

                        case EN_SCRIPT_COMMAND_DBGATVSCAN:
                        {
                            ParseResult = msUS_ParseValue(Parameter3Name,u8TokenCharCount);
                            if(ParseResult ==FALSE)
                            {
                                return FALSE;
                            }
                            break;
                        }
                        case EN_SCRIPT_COMMAND_RRIU:
                        case EN_SCRIPT_COMMAND_DUMPBANK:
                        case EN_SCRIPT_COMMAND_LOG:
                        case EN_SCRIPT_COMMAND_DELAY:
                        case EN_SCRIPT_COMMAND_MCUPAUSE:
                        case EN_SCRIPT_COMMAND_UART2USBON:
                        {
                            DEBUG_ES(printf("[ES](Line %d)This command should not has parameter3!!\t\n",CurrentCommandAmount););
                            return FALSE;
                            break;
                        }
                        default:
                            break;
                    }
                    u8TokenCount++;
                }
                else if(u8TokenCount >4)
                {
                    DEBUG_ES(printf("[ES](Line %d)Hey!! Too many command parameter!!\t\n",CurrentCommandAmount););
                    return FALSE;
                }
            }
        u8TokenCharCount = -1;
        }

    }
    DEBUG_ES(printf("[ES]Line %d parse finished!!\t\n",CurrentCommandAmount););
    CurrentEventCommandCount ++;
    CurrentCommandAmount++;
    return TRUE;
}

void msUS_EventInit(void)
{
    U8 i;

    USB_Insert = 0;
    USB_ReadFinished = 0;

    //clear message pool
    for(i=0;i<EVENT_AMOUNT;i++)
    {
        EventPool[i].event =EN_SCRIPT_EVENT_NONE;
    }
    CurrentReadEvent = EN_SCRIPT_EVENT_NONE;
    CurrentEventCommandCount = 0;


    //clear message pool
    CurrentMessageAmount = 0;

    //clear command pool
    CurrentCommandAmount =0;
}

U8 msUS_OpenUSBPort(void)
{
#if ( (ENABLE_USB || ENABLE_USB_2) && ENABLE_FILESYSTEM )
    U8 u8PortEnStatus = 0;
    U8 u8UsbPortNO = 0;

    DEBUG_ES( printf(" [ES]msUS_OpenUSBPort()\n",0); );

    u8PortEnStatus = MDrv_USBGetPortEnableStatus();

    if((u8PortEnStatus & BIT0) == BIT0)
    {
        if( !MDrv_UsbDeviceConnect() )
        {
            DEBUG_ES( printf("\n [ES]Warning: port0 not connect!\n", 0); );
            u8UsbPortNO = 0;
        }
        else
        {
            u8UsbPortNO = 1;
        }
    }
    if((u8PortEnStatus & BIT1) == BIT1)
    {
        if(u8UsbPortNO != 1)
        {
            if (!MDrv_UsbDeviceConnect_Port2())
            {
                DEBUG_ES( printf("\n [ES]Warning: port1 not connect!\n", 0); );
                u8UsbPortNO = 0;
            }
            else
            {
                u8UsbPortNO = 2;
            }
        }
    }
    if(((u8PortEnStatus & BIT0) != BIT0)&&((u8PortEnStatus & BIT1) != BIT1))
    {
        DEBUG_ES(printf("\n Error: [ES]Unknown USB port\n", 0););
        return 0;
    }

    return u8UsbPortNO;
#else
    return 0;
#endif
}

BOOL msUS_InitFileSystem(U8 u8UsbPortNO)
{
    DEBUG_ES( printf("[ES] msUS_InitFileSystem(u8UsbPortNO=%u)\n", u8UsbPortNO); );

    if( (u8UsbPortNO != 1) && (u8UsbPortNO != 2) )
    {
        printf("\nError: [ES]u8UsbPortNO=%u\n", u8UsbPortNO);
        return FALSE;
    }

    msAPI_MSDCtrl_CheckDevices();

    _s_ES_bFileSystemInited = FALSE;
    _s_ES_u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;

    if( (u8UsbPortNO == 1) || (u8UsbPortNO == 2) )
    {
        U8 u8DeviceIdx_Start, u8DeviceIdx_End;
        U8 u8DeviceIdx;

        if( u8UsbPortNO == 1 )
        {
            u8DeviceIdx_Start = MSD_USB_INDEX_START;
            u8DeviceIdx_End = MSD_USB_INDEX_START + MSD_USB_NUM;
        }
        else
        {
            u8DeviceIdx_Start = MSD_USB_2_INDEX_START;
            u8DeviceIdx_End = MSD_USB_2_INDEX_START + MSD_USB_2_NUM;
        }

        for( u8DeviceIdx = u8DeviceIdx_Start; u8DeviceIdx < u8DeviceIdx_End; u8DeviceIdx++)
        {
            EN_MSD_STATUS eMsdStatus = msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIdx);
            //printf("  Dev=%u status=%u\n", u8DeviceIdx, eMsdStatus );
            if( eMsdStatus == MSD_STATUS_INSERTED )
            {
                msAPI_FCtrl_ActiveDevice(u8DeviceIdx);
                eMsdStatus = msAPI_MSDCtrl_GetDeviceStatus(u8DeviceIdx);
                //printf("  status=%u\n", eMsdStatus );
            }

            if( eMsdStatus == MSD_STATUS_IDLE )
            {
                _s_ES_u8FileSysEnvironmentID = msAPI_FSEnv_Register(0x00 /*'A'*/);
                _s_ES_bFileSystemInited = msAPI_FCtrl_DirectoryChangeToRoot(_s_ES_u8FileSysEnvironmentID);
                //printf("  u8DeviceIdx=%u, FSEnvId=%u, init=%u\n", u8DeviceIdx, _s_U2U_u8FileSysEnvironmentID, _s_U2U_bFileSystemInited);
                break;
            }
        }
    }

    if( !_s_ES_bFileSystemInited )
    {
        printf("\nError:[ES] Init file system failed! (u8UsbPortNO=%u)\n", u8UsbPortNO);
        return FALSE;
    }

    return TRUE;
}

void msUS_DeInitFileSystem(void)
{
    DEBUG_ES( printf(" [ES]msUS_DeInitFileSystem()\n", 0); );

    if( _s_ES_u8FileSysEnvironmentID != INVALID_FS_ENVIRONMENT_INDEX )
    {
        msAPI_FSEnv_UnRegister(_s_ES_u8FileSysEnvironmentID);
        _s_ES_u8FileSysEnvironmentID = INVALID_FS_ENVIRONMENT_INDEX;
    }

    _s_ES_bFileSystemInited = FALSE;
}

BOOL msUS_SearchFile(U8 u8FSEnvId, char* pcTargetFileName, BOOL bFindFolder, FileEntry* pFileEntry)
{
    U16 u16EntryIdx;

    U8 u8TargetFileNameLen = strlen(pcTargetFileName);
    BOOL bFolderFound = FALSE;
    FileEntry tmpFileEntry;
    EN_ENTRY_TYPE tmpEntryType;
    U16 au16CurFileName[128];
    U8 u8CurFileNameLen;


    DEBUG_ES( printf(" [ES]msUS_SearchFile(%s)\n", pcTargetFileName); );

    //DEBUG_U2U( printf("  u8TargetFileNameLen=%u\n", u8TargetFileNameLen ); );

    if( u8TargetFileNameLen == 0 )
        return FALSE;

    msAPI_FCtrl_EntryFirst(u8FSEnvId);

    // Find out the special folder
    u16EntryIdx = 0;
    while( msAPI_FCtrl_EntryNext(u8FSEnvId, &tmpFileEntry) == ENTRY_NEXT_RESULT_SUCCESS )
    {
        //U2U_CLEAR_WATCHDOG();

        tmpEntryType = tmpFileEntry.EntryType;

        if( bFindFolder ) // Check directory
        {
            if( tmpEntryType != ENTRY_TYPE_DIR )
                continue;
        }
        else // Check file
        {
            if( tmpEntryType != ENTRY_TYPE_FILE)
                continue;
        }

        u8CurFileNameLen = msAPI_FCtrl_EntryGetCurrentName(u8FSEnvId, (U32)(au16CurFileName), 127);

    #if 0
        printf("%u) %s %u ", u16EntryIdx, (tmpEntryType == ENTRY_TYPE_DIR)?"D":"F",u8CurFileNameLen);
        _PrintFileName(au16CurFileName);
        printf("\n");
    #endif

        if( u8CurFileNameLen == u8TargetFileNameLen )
        {
            if( _CompareString_U8_U16(pcTargetFileName, au16CurFileName, u8TargetFileNameLen) )
            {
                printf(" =====> \"%s\" found!\n", pcTargetFileName);
                bFolderFound = TRUE;
                break;
            }
            else
            {
                //printf(" =====> Not Found\n");
            }
        }

        u16EntryIdx += 1;
    }

    if( FALSE == bFolderFound )
    {
        //printf("\nWarning: %s not found\n", pcTargetFileName);
        return FALSE;
    }

    *pFileEntry = tmpFileEntry;

    return TRUE;
}

void msUS_ExecuteScript_Task(void)
{
    static U32 _s_u32LastTime = 0;
    U32 u32CurTime;
    BOOL bReadResult = FALSE;

    u32CurTime = MsOS_GetSystemTime();

    if( msAPI_Timer_DiffTime_2(_s_u32LastTime, u32CurTime) < 2000 )
    {
        return;
    }


    _s_u32LastTime = u32CurTime;

    printf("USB_ReadFinished : %d\t\n",USB_ReadFinished);
    //printf_2(" tt=%u\n", u32CurTime);
    //printf(" t=%u\n", u32CurTime);

    //printf(" Try to OpenFile ...\n");

    U8 u8UsbPortNO = msUS_OpenUSBPort();
    printf("u8UsbPortNO : %d\t\n",u8UsbPortNO);
    if( 0 == u8UsbPortNO ) // No use connected!!
    {
        USB_Insert = 0;
        USB_ReadFinished = 0;
        printf("\n Warning: Open USB port failed\n", 0);
    }
    else
    {
        if(USB_ReadFinished == 0)
        {
            msUS_EventInit();
            bReadResult = msUS_ReadScript();
            if(bReadResult == FALSE)
            {
                return;
            }
            USB_ReadFinished = 1;
            USB_Insert =1;
            printf("USB_ReadFinished 2: %d\t\n",USB_ReadFinished);
        }
    }
}

BOOL msUS_ReadScript(void)
{
    DEBUG_ES(printf("\t\n [ES]msUS_ReadScript start !!\t\n"););

    U8 u8UsbPortNO = 0;
    FileEntry fFolderFileEntry;
    BOOL bSearchFileResult;
    static U32 u32FileLength = 0;  //upper bond cahr per line about script CMD
    U32 ret_val = 0;
#if 0
    CommandPool[0].CommandType = 0;
    CommandPool[0].CommonParameter.Address[2] = 0x00;
    CommandPool[0].CommonParameter.Address[1] = 0x00;
    CommandPool[0].CommonParameter.Address[0] = 0x00;
    CommandPool[0].CommonParameter.MessagePoint = 0x00;
    CommandPool[0].CommonParameter.Second = 0x00;
    CommandPool[0].u8mask = 0x00;
    CommandPool[0].u8value = 0x00;
#endif
    //init event pool
    msUS_EventInit();

    u8UsbPortNO = msUS_OpenUSBPort();
    if( 0 == u8UsbPortNO )
    {
        DEBUG_ES( printf("\n Warning: Open USB port failed\n", 0); );
        msUS_CloseScript();
        return FALSE;
    }

    // Init file system => Get fileEnv
    if( FALSE == msUS_InitFileSystem(u8UsbPortNO) )
    {
        printf("\nError: Init file system failed\n", 0);
        msUS_DeInitFileSystem();
        msUS_CloseScript();
        return FALSE;
    }

     // Change to root
    if( FALSE == msAPI_FCtrl_DirectoryChangeToRoot(_s_ES_u8FileSysEnvironmentID) )
    {
        printf("\nError: [ES]msAPI_FCtrl_DirectoryChangeToRoot failed\n", 0);
        msUS_DeInitFileSystem();
        msUS_CloseScript();
        return FALSE;
    }

    // Find script file
    //bSearchFileResult = msUS_SearchFile(_s_ES_u8FileSysEnvironmentID, EXECUTE_SCRIPT_FILE_NAME, TRUE, &fFolderFileEntry);
    bSearchFileResult = msUS_SearchFile(_s_ES_u8FileSysEnvironmentID, EXECUTE_SCRIPT_FILE_NAME, FALSE, &fFolderFileEntry);

    if(FALSE == bSearchFileResult)
    {
        printf("\nError: [ES]No Script file or file name error!!\n");
        msUS_DeInitFileSystem();
        msUS_CloseScript();
        return FALSE;
    }
#if 1
    //open and read file
    _s_ES_u8FileHandle = msAPI_FCtrl_FileOpen(&fFolderFileEntry, OPEN_MODE_FOR_READ);
    DEBUG_ES(printf("_s_ES_u8FileHandle :  0x%X\t\n",_s_ES_u8FileHandle););
    u32FileLength = msAPI_FCtrl_FileLength(_s_ES_u8FileHandle);
    U8 *FileBuffer = malloc(u32FileLength*(sizeof(U8)));
    ret_val = msAPI_FCtrl_FileRead2(_s_ES_u8FileHandle, (U32)FileBuffer, u32FileLength);
    DEBUG_ES(printf("0x%X \t\n",ret_val););



    if(ret_val<=u32FileLength)
    {
        u32FileLength = u32FileLength - ret_val;
    }
    // No need file env anymore
    msUS_DeInitFileSystem();

    if(u32FileLength == 0)
    {
        printf("Scritp is empty!!\n\n");
        msUS_CloseScript();
        free(FileBuffer);
        return FALSE;
    }

    //read per line
    U32 u32CurrentReadPosition = 0;
    U8 CurrentReadLine[80];
    memset(CurrentReadLine, NULL, 80);  //initial readline
    U8 u8CurrentReadCharCount = 0;
    BOOL bParseResult;
    //verify file size when last char was not ' ' or '\n'
    if((FileBuffer[u32FileLength-1] !=0x20) ||
        ((FileBuffer[u32FileLength-2] !=0x0D)&&(FileBuffer[u32FileLength-1] )!=0x0A))
    {
        FileBuffer[u32FileLength]  = 0x0D;
        FileBuffer[u32FileLength+1]  = 0x0A;
        u32FileLength +=2;
    }

    while(u32CurrentReadPosition < u32FileLength)
    {
        /*test//
        U8 u8count=0;
        printf("%x ",FileBuffer[u32CurrentReadPosition]);
        printf("%c \n",FileBuffer[u32CurrentReadPosition]);
        u8count++;
        if(u8count == 10)
        {
        u8count = 0; printf("\n");
        }
        u32CurrentReadPosition++;*/
        //Enter
        if(((FileBuffer[u32CurrentReadPosition] == 0x0D) && (FileBuffer[u32CurrentReadPosition+1] == 0x0A)) &&
            ((FileBuffer[u32CurrentReadPosition-1] != 0x0A) && (FileBuffer[u32CurrentReadPosition-2] != 0x0D)))
        {
            CurrentReadLine[u8CurrentReadCharCount] = 0x20;//add a blank at line tail
            DEBUG_ES(printf("token length: %d\t\n",u8CurrentReadCharCount););
            bParseResult = msUS_ParseLine(CurrentReadLine, u8CurrentReadCharCount+1);
            //bParseResult = FALSE;

            if(bParseResult == FALSE)
            {
                msUS_CloseScript();
                free(FileBuffer);
                return FALSE;
            }

            u8CurrentReadCharCount = 0;
            memset(CurrentReadLine, NULL, 80);  //clear temp readline
            u32CurrentReadPosition++; //ignore 0x0a 0x0d

        }
        else if(((FileBuffer[u32CurrentReadPosition] == 0x0D) && (FileBuffer[u32CurrentReadPosition+1] == 0x0A)) &&
            ((FileBuffer[u32CurrentReadPosition-1] == 0x0A) && (FileBuffer[u32CurrentReadPosition-2] == 0x0D)))
        {
             //ignore empty line
            u8CurrentReadCharCount = 0;
            memset(CurrentReadLine, NULL, 80);  //clear temp readline
            u32CurrentReadPosition++; //ignore 0x0a 0x0d
        }
        else
        {
            CurrentReadLine[u8CurrentReadCharCount] = FileBuffer[u32CurrentReadPosition];
            u8CurrentReadCharCount++;
        }
        u32CurrentReadPosition++;//next readbyte
    }
    EventPool[CurrentReadEvent].u8CommandLength = CurrentEventCommandCount - 1; //cut event title line "@xxxx"
    //-------test-----------//
    printf("!!Read Script Finished!!\t\n");
    printf("!!Read Script Finished!!\t\n");
    printf("!!Read Script Finished!!\t\n");
#endif
#if 1
    U8 i;
    //test
    //command pool
    printf("command pool:\t\n");
    for(i=0;i<CurrentCommandAmount;i++)
    {
        printf("[%d] : \n",i);
        printf("command type: %x\n",CommandPool[i].CommandType);
        printf("Address[2]: %x\n",CommandPool[i].CommonParameter.Address[2]);
        printf("Address[1]: %x\n",CommandPool[i].CommonParameter.Address[1]);
        printf("Address[0]: %x\n",CommandPool[i].CommonParameter.Address[0]);
        printf("MessagePoint: %x\n",CommandPool[i].CommonParameter.MessagePoint);
        printf("Second: %x\n",CommandPool[i].CommonParameter.Second);
        printf("u8mask: %x\n",CommandPool[i].CommonParameter2.mask);
        printf("u8value: %x\n",CommandPool[i].u8value);
    }
    //message pool
    i=0;
    while(i<CurrentMessageAmount)
    {
        if(MessagePool[i] != '\0')
        {
            printf("%c",MessagePool[i]);
        }
        else
        {
            printf("\n");
        }

        i++;
    }
    printf("\t\n messagepool : %s\n",MessagePool);


    //event pool

    printf("event pool:\t\n");
    for(i=0;i<EVENT_AMOUNT;i++)
    {
        printf("[%d] : \n",i);
        printf("event : %x\n",EventPool[i].event);
        printf("event start: %x\n",EventPool[i].u8CommandStart);
        printf("event length: %x\n",EventPool[i].u8CommandLength);
    }
    printf("ALOHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1\t\n");
#endif

    free(FileBuffer);
    return TRUE;
}

void msUS_ScriptExecute(EN_SCRIPT_EVENT_TYPE tEventType)
{
    U16 u16EventCommandCurrent = 0;
    U16 u16EventCommandEnd = 0;
    MSUS_SCRIPT_EVENT event;

    printf("\t\n msUS_ScriptExecute Start!!!\t\n");
    printf("\t\n ---------------------------------------------------------\t\n");

    if(tEventType == 0xff)
    {
        printf("[ES-EX]No Support this Event !!\t\n");
        return ;
    }
    printf("tEventType :%x\t\n",tEventType);

    event = EventPool[tEventType];

    if(event.event== 0xFF)
        return;

    u16EventCommandCurrent = event.u8CommandStart;
    u16EventCommandEnd = u16EventCommandCurrent +event.u8CommandLength -1;
    printf("u16EventCommandCurrent : %x\t\n",u16EventCommandCurrent);
    printf("u16EventCommandEnd : %x\t\n",u16EventCommandEnd);
    printf("%x\t\n",CommandPool[u16EventCommandCurrent].CommandType);

    while(u16EventCommandCurrent <= u16EventCommandEnd)
    {
        switch(CommandPool[u16EventCommandCurrent].CommandType)
        {
            case EN_SCRIPT_COMMAND_RRIU:
            {
                msUS_CommandRriu(CommandPool[u16EventCommandCurrent]);
            }
            break;

            case EN_SCRIPT_COMMAND_WRIU:
            {
                msUS_CommandWriu(CommandPool[u16EventCommandCurrent]);
            }
            break;

            case EN_SCRIPT_COMMAND_CHECK:
            {
                if(!(msUS_CommandCheck(CommandPool[u16EventCommandCurrent])))
                {
                    u16EventCommandCurrent++;                                   //drop next command
                }
            }
            break;

            case EN_SCRIPT_COMMAND_LOG:
            {
                msUS_CommandLog(CommandPool[u16EventCommandCurrent]);
            }
            break;

            case EN_SCRIPT_COMMAND_MCUPAUSE:
            {
                msUS_CommandMcuPause();
            }
            break;

            case EN_SCRIPT_COMMAND_DUMPBANK:
            {
                msUS_CommandDumpBank(CommandPool[u16EventCommandCurrent]);
            }
            break;

            case EN_SCRIPT_COMMAND_DELAY:
            {
                msUS_CommandDelay(CommandPool[u16EventCommandCurrent]);
            }
            break;

            case EN_SCRIPT_COMMAND_UART2USBON:
            {
                msUS_CommandUart2USBOn();
            }
            break;

            case EN_SCRIPT_COMMAND_DBGATVSCAN:
            {
                msUS_CommandDbgATVScan(CommandPool[u16EventCommandCurrent]);
            }
            break;
        }

        u16EventCommandCurrent++;    //event next command
    }
    printf("\t\n ---------------------------------------------------------\t\n");
}

void msUS_UseScript(EN_SCRIPT_EVENT_TYPE tEventType)
{
    if(g_stFactorySetting.stFacMiscSetting.eFactoryExecuteScript== EN_FACTORY_EXECUTE_SCRIPT_ON)
    {
        if(tEventType == EN_SCRIPT_EVENT_INIT)
        {
            msUS_ExecuteScript_Task();
        }

        if(msUS_CheckEventPoolEmpty())
        {
            msUS_ScriptExecute(tEventType);
        }
    }
}

void msUS_CloseScript(void)
{
    msUS_EventInit();
    g_stFactorySetting.stFacMiscSetting.eFactoryExecuteScript = EN_FACTORY_EXECUTE_SCRIPT_OFF;
}

BOOL msUS_CommandRriu(MSUS_SCRIPT_COMMAND command)
{
    U32 u32address;
    U8 u8data;

    u32address = (command.CommonParameter.Address[2] << 16) | (command.CommonParameter.Address[1] << 8) | (command.CommonParameter.Address[0] );
    u8data = MDrv_ReadByte(u32address);
    printf("Read Address 0x%x : 0x%x \t\n",u32address,u8data);

    return TRUE;
}

BOOL msUS_CommandWriu(MSUS_SCRIPT_COMMAND command)
{
    U32 u32address;
    U8 u8data;
    U8 u8mask;

    u32address = (command.CommonParameter.Address[2] << 16) | (command.CommonParameter.Address[1] << 8) | (command.CommonParameter.Address[0] );
    u8data = command.u8value;
    u8mask = command.CommonParameter2.mask;

    MDrv_WriteByteMask(u32address, u8data, u8mask);
    printf("Write Address 0x%X \t\n",u32address);
    printf("Write u8data   0x%X \t\n",u8data);
    printf("Write u8mask  0x%X \t\n",u8mask);
    return TRUE;
}

BOOL msUS_CommandLog(MSUS_SCRIPT_COMMAND command)
{
    U8 CurrentPrintChar;
    CurrentPrintChar = command.CommonParameter.MessagePoint;

    printf("[Message] :");
    while(MessagePool[CurrentPrintChar]  != '\0')
    {
        printf("%c",MessagePool[CurrentPrintChar]);
        CurrentPrintChar++;
    }
    printf("\t\n");

    return TRUE;
}

BOOL msUS_CommandCheck(MSUS_SCRIPT_COMMAND command)
{
    U32 u32address;
    U8 u8data;
    U8 u8mask;

    printf("execute check\n");
    u32address = (command.CommonParameter.Address[2] << 16) | (command.CommonParameter.Address[1] << 8) | (command.CommonParameter.Address[0] );
    u8data = MDrv_ReadByte(u32address);
    u8mask = command.CommonParameter2.mask;
    printf("Script value : %x\t\n",command.u8value);

    u8data = u8data & u8mask;
    if(u8data != command.u8value)
    {
        printf("check FALSE\t\n");
        return FALSE;
    }
    else
    {
        printf("check TRUE\t\n");
        return TRUE;
    }
}

void msUS_CommandMcuPause(void)
{
    char* temp =NULL;   //just input a null char , pointless
    MCUPause(temp,0);
}

BOOL msUS_CommandDumpBank(MSUS_SCRIPT_COMMAND command)
{
    U32 u32BankAddress;
    U8 u8data;
    U32 u32ReadAddress;

    u32BankAddress = (command.CommonParameter.Address[2] << 16) | (command.CommonParameter.Address[1] << 8) | (command.CommonParameter.Address[0] );
    if(u32BankAddress > 0xFFFF)
    {
        printf("[Dump bank range overflow!! \t\n]");
        return FALSE;
    }

    printf("  ----- Bank 0x%X -----\r\n",u32BankAddress);
    printf("    00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n  -------------------------------------------------\r\n");
    int i,j;
    for(i =0;i<16;i++)
    {
        printf("%X0",i);
        for(j=0;j<16;j++)
        {
            u32ReadAddress = (u32BankAddress << 8) | (i<<4) | j;
            u8data = MDrv_ReadByte(u32ReadAddress);
            printf("%X ",u8data);
        }
        printf("\t\n");
    }
    printf("Bank Done!\t\n");

    return TRUE;
}

BOOL msUS_CommandDelay(MSUS_SCRIPT_COMMAND command)
{
    U32 millisecond;

    millisecond = command.CommonParameter.Second;
    MsOS_DelayTask(millisecond);
    printf("Delay Done!\t\n");

    return TRUE;
}

BOOL msUS_CommandUart2USBOn(void)
{
    g_stFactorySetting.stFacMiscSetting.eFactoryUSBLog = EN_FACTORY_USB_LOG_ON;
    msDebug_UartToUSB_Set_Enable(TRUE);

    return TRUE;
}

BOOL msUS_CommandDbgATVScan(MSUS_SCRIPT_COMMAND command)
{
    DWORD dwFrequencyLowBound;
    DWORD dwFrequencyUpBound;
    U8 u8time;

    dwFrequencyLowBound = (command.CommonParameter.frequency1[2] << 16) | (command.CommonParameter.frequency1[1] << 8) | (command.CommonParameter.frequency1[0] );
    dwFrequencyUpBound = (command.CommonParameter2.frequency2[2] << 16) | (command.CommonParameter2.frequency2[1] << 8) | (command.CommonParameter2.frequency2[0] );
    u8time = command.u8value;

#if ENABLE_DBG_ATV_SCAN
    MApp_DbgATV_Scan(dwFrequencyLowBound, dwFrequencyUpBound, u8time);
#endif//ENABLE_DBG_ATV_SCAN
    return TRUE;
}

#endif //#if (ENABLE_SCRIPT_EXECUTE)


