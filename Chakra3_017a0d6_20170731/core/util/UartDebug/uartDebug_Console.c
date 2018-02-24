
#if(ENABLE_CONSOLE_CMD)

//#include <stdio.h>

//void msAPI_ConsoleCmd_RecvData(U8 u8Data);
//void msAPI_ConsoleCmd_ExecCmd(void);


#define DEBUG_PARSE_CMD(x)  //x

#define CONSOLE_CMD_ECHO_DATA   1

#define ENABLE_CPU_STOP         1


#define CONSOLE_CMD_BUF     64
U8 g_au8ConsoleCmdBuf[CONSOLE_CMD_BUF];

U8 g_ConsoleCmd_u8CharCount = 0;
BOOL g_ConsoleCmd_bGotCmd = 0;
BOOL g_ConsoleCmd_bEnable = 0;


#define CONSOLE_CMD_PARA_BUF    32
#define CONSOLE_CMD_PARA_NUM    5
U8 g_ConsoleCmd_u8ParaNum;
char g_ConsoleCmd_acParaBuf[CONSOLE_CMD_PARA_NUM][CONSOLE_CMD_PARA_BUF];

#if 1
#define IS_CHAR_VISIBLE(c)  (((c)>=0x20)&&((c)<=127))
#else
#define IS_CHAR_VISIBLE(c)  ( (((c)>=0x30)&&((c)<=0x39))\
                            ||(((c)>=0x41)&&((c)<=0x5A))\
                            ||(((c)>=0x61)&&((c)<=0x7A))\
                            )
#endif

void msAPI_ConsoleCmd_RecvData(U8 u8Data)
{
    if( g_ConsoleCmd_bGotCmd )
    {
        return;
    }

    if( g_ConsoleCmd_u8CharCount < (CONSOLE_CMD_BUF-1) )
    {
        if( IS_CHAR_VISIBLE(u8Data) )
        {
            g_au8ConsoleCmdBuf[g_ConsoleCmd_u8CharCount] = u8Data;
            g_ConsoleCmd_u8CharCount += 1;

        #if(CONSOLE_CMD_ECHO_DATA)
            if(g_ConsoleCmd_bEnable)
            {
                putchar(u8Data);
            }
        #endif
        }
    }

    if( u8Data == '\n' || u8Data == '\r' )
    {
    #if(CONSOLE_CMD_ECHO_DATA)
        if(g_ConsoleCmd_bEnable)
        {
            putchar('\r');
            putchar('\n');
        }
    #endif

        g_au8ConsoleCmdBuf[g_ConsoleCmd_u8CharCount] = 0;

        g_ConsoleCmd_bGotCmd = TRUE;
    }
}

void msAPI_ConsoleCmd_PrintCmdBuf(void)
{
    U8 i;
    printf("CmdBuf[%u]:", g_ConsoleCmd_u8CharCount);
    for( i = 0; i < g_ConsoleCmd_u8CharCount ; i += 1 )
    {
        U8 u8Char = g_au8ConsoleCmdBuf[i];
        if( IS_CHAR_VISIBLE(u8Char) )
        {
            putchar(u8Char);
            printf("(%02X)", u8Char );
        }
        else
            printf("(%02X)", u8Char );
    }
    printf("\n");
}

void msAPI_ConsoleCmd_PrintPara(void)
{
    U8 iPara;
    printf("==> ");
    for( iPara = 0; iPara < g_ConsoleCmd_u8ParaNum; iPara += 1)
    {
        printf("%s,", g_ConsoleCmd_acParaBuf[iPara]);
    }
    printf("\n");
}

void ConsoleCmd_CpuStop(void)
{
#if (ENABLE_CPU_STOP)
    printf("cpu stop\n");

    {
    #if(CHIP_FAMILY_TYPE == CHIP_FAMILY_MAZDA)
        MDrv_Write2ByteMask(0x110C22, BIT8, BIT8|BIT7);
    #endif
    }
#endif
}

void ConsoleCmd_Reg(void)
{
    printf("reg:\n");

    if( g_ConsoleCmd_u8ParaNum < 1 )
        return;

    U32 u32Addr = 0;

    u32Addr = strtoul(g_ConsoleCmd_acParaBuf[0], NULL, 0);

    u32Addr = u32Addr & 0x00FFFF00;

    printf("Reg_%X dump:\n", u32Addr);


    U16 i;

    for( i = 0; i < 256; ++ i )
    {
        if( (i % 16) == 0 )
        {
            printf("%02X : ", i);
        }

        printf("%02X ", MDrv_ReadByte(u32Addr + i));

        if( (i % 16) == 15 )
        {
            printf("\n");
        }
    }

}

void ConsoleCmd_MemDump(void)
{
    printf("mem dump\n");
    U32 u32Addr = 0;
    U32 u32Size = 0;

//    char * pcCmdStr;
//    pcCmdStr = "dump";
    //if( 0 == memcmp( pcCmdStr, g_ConsoleCmd_acParaBuf[0], strlen(pcCmdStr) ) )
    {
        //printf("mem dump\n");

        if( g_ConsoleCmd_u8ParaNum < 2 )
            return;

        u32Addr = strtoul(g_ConsoleCmd_acParaBuf[0], NULL, 0);
        u32Size = strtoul(g_ConsoleCmd_acParaBuf[1], NULL, 0);

        printf("mem dump 0x%X 0x%X\n", u32Addr, u32Size);

        if( u32Size > 1024 )
        {
            u32Size = 1024;
        }

        Print_Buffer((U8*)u32Addr, u32Size);
    }

}

BOOL Cus_UART_ExecTestCommand(void);

void ConsoleCmd_TestCmd(void)
{
    printf("TestCmd:\n");

    //msAPI_ConsoleCmd_PrintPara();

    // Pass para to test command
    U8 iPara;
    U8 u8Tmp;
    printf("==> ");
    for( iPara = 0; (iPara < g_ConsoleCmd_u8ParaNum)&&(iPara<6); iPara += 1)
    {
        //printf("%s,", g_ConsoleCmd_acParaBuf[iPara]);
        u8Tmp = strtoul(g_ConsoleCmd_acParaBuf[iPara], NULL, 0);
        printf("%02X,", u8Tmp);
        g_UartCommand.Buffer[_UART_CMD_INDEX1_ + iPara] = u8Tmp;
    }
    printf("\n");

    Cus_UART_ExecTestCommand();

}

void ConsoleCmd_test1(void)
{
    printf("test1\n");
}

void ConsoleCmd_test2(void)
{
    printf("test2\n");
}

typedef struct
{
    char* pcCmdName;
    void (*pfCmdHandler)(void);
} StruConsoleCmdInfo;

StruConsoleCmdInfo g_astConsoleCmdInfo[] =
{
    { "cpustop",    ConsoleCmd_CpuStop },
    { "reg",        ConsoleCmd_Reg },
    { "memdump",    ConsoleCmd_MemDump },
    { "testcmd",    ConsoleCmd_TestCmd },

    { "test1",      ConsoleCmd_test1 },
    { "test2",      ConsoleCmd_test2 },
};

void msAPI_ConsoleCmd_ParseCmd(void)
{
    // Get first token
    char* pcTok = strtok((char*)g_au8ConsoleCmdBuf, " ,.-");

    if( pcTok == NULL )
    {
        return;
    }

    DEBUG_PARSE_CMD( printf("pcTok=%s\n", pcTok); );

    // check cmd type
    BOOLEAN bCmdFound = 0;
    U8 u8CmdIdx;
    U8 u8TokLen = strlen(pcTok);
    U8 u8CmdLen;
    for(u8CmdIdx=0; u8CmdIdx < (sizeof(g_astConsoleCmdInfo)/sizeof(StruConsoleCmdInfo)); u8CmdIdx += 1)
    {
        //printf("Cmd[%u]=%s\n", u8CmdIdx, g_astConsoleCmdInfo[u8CmdIdx].pcCmdName);

        u8CmdLen = strlen(g_astConsoleCmdInfo[u8CmdIdx].pcCmdName);

        if( u8TokLen != u8CmdLen )
            continue;

        if( 0 == memcmp( pcTok, g_astConsoleCmdInfo[u8CmdIdx].pcCmdName, u8CmdLen ) )
        {
            DEBUG_PARSE_CMD( printf("Cmd found!\n"); );
            bCmdFound = 1;
            break;
        }
    }

    if( bCmdFound )
    {
    #if(CONSOLE_CMD_ECHO_DATA)
        printf("\n");
    #endif

        //msAPI_ConsoleCmd_ParsePara(g_au8ConsoleCmdBuf + u8TokLen);
        g_ConsoleCmd_u8ParaNum = 0;
        memset(g_ConsoleCmd_acParaBuf, 0, sizeof(g_ConsoleCmd_acParaBuf));

        while(1)
        {
            pcTok = strtok( NULL, " ,.-");
            if( pcTok == NULL )
                break;

            //printf("{%s}", pcTok);
            strncpy( g_ConsoleCmd_acParaBuf[g_ConsoleCmd_u8ParaNum], pcTok, CONSOLE_CMD_PARA_BUF );
            g_ConsoleCmd_u8ParaNum += 1;

            if( g_ConsoleCmd_u8ParaNum >= CONSOLE_CMD_PARA_NUM )
                break;
        }

    #if 1
        msAPI_ConsoleCmd_PrintPara();
    #endif

        if( g_astConsoleCmdInfo[u8CmdIdx].pfCmdHandler )
        {
            g_astConsoleCmdInfo[u8CmdIdx].pfCmdHandler();
        }

    }
    else
    {
    #if(CONSOLE_CMD_ECHO_DATA)
        printf("\nUnknown cmd!\n");
        msAPI_ConsoleCmd_PrintCmdBuf();
    #endif
    }
}

void msAPI_ConsoleCmd_ExecCmd(void)
{
    if( !g_ConsoleCmd_bGotCmd )
    {
        return;
    }

    // print cmd buf
    //msDebug_ConsoleCmd_PrintCmdBuf();

    // Remove buf end '\n'
/*
    if( g_ConsoleCmd_u8CharCount > 0 )
    {
        if( g_au8ConsoleCmdBuf[g_ConsoleCmd_u8CharCount-1] == 0x0D )
        {
            g_au8ConsoleCmdBuf[g_ConsoleCmd_u8CharCount-1] = 0;
            g_ConsoleCmd_u8CharCount -= 1;
        }
    }
*/

    if( !g_ConsoleCmd_bEnable )
    {
        if( 0 == memcmp( "80336647", g_au8ConsoleCmdBuf, 8 ) )
        {
            printf("\nConcole command enable!\n");
            g_ConsoleCmd_bEnable = 1;
        }
    }
    else
    {
        if( g_ConsoleCmd_u8CharCount )
        {
            // print cmd buf
            DEBUG_PARSE_CMD( msAPI_ConsoleCmd_PrintCmdBuf(); );

            // Pasre cmd...
            msAPI_ConsoleCmd_ParseCmd();
        }
    }

    // Clear command buffer
    memset( g_au8ConsoleCmdBuf, 0, sizeof(g_au8ConsoleCmdBuf));
    g_ConsoleCmd_u8CharCount = 0;
    g_ConsoleCmd_bGotCmd = 0;
}

#endif

