#include "Board.h"

#define ENABLE_UART_DEBUG_TTS   0

#if(ENABLE_ATSC_TTS&&ENABLE_UART_DEBUG_TTS)

#include "msAPI_TTS_Debug.h"

#include "MApp_TTS_Cus.h"


void TestCommand_TTS(void)
{
    //U8 u8Para1 = g_UartCommand.Buffer[_UART_CMD_INDEX3_];
    //U8 u8Para2 = g_UartCommand.Buffer[_UART_CMD_INDEX4_];

    switch( g_UartCommand.Buffer[_UART_CMD_INDEX2_] )
    {
        case 0x00:
            printf("TTS Cmd List:\n");
            printf(" 01: \"Aspect Ratio\"\n");
            //printf(" 02: \"Aspect Ratio\" \"Auto\"\n");
            break;

        case 0x01:
            MApp_TTS_Say_Stop();
            MApp_TTS_Cus_AddU8String((U8*)"Aspect Ratio");
            MApp_TTS_Say_Start();
            break;

    #if 0
        case 0x02:
            MApp_TTS_Say_Stop();
            MApp_TTS_Cus_AddU8String((U8*)"Aspect Ratio");
            MApp_TTS_Cus_AddU8String((U8*)"Auto");
            MApp_TTS_Say_Start();
            break;
    #endif

    /*
        case 0x03:
            MApp_TTS_Say_Stop();
            MApp_TTS_Cus_AddU8String((U8*)"Aspect Ratio");
            MApp_TTS_Cus_AddU8String((U8*)"Auto");
            MApp_TTS_Say_Start();
            break;
*/

    #if 0
        case 0x04:
            MApp_TTS_Say_Stop();

        #if(ENABLE_TTS_DUMP_DATA)
            msAPI_TTS_Dump_Set_Enable(ENABLE);
        #endif

            //MApp_TTS_Cus_AddU8String((U8*)"Aspect Ratio");
            MApp_TTS_Cus_AddU8String((U8*)"Auto");

            MApp_TTS_Say_Start();
            while(1)
            {
                MApp_TTSControlHandler_Main();

                if( MApp_TTS_Is_InWorking() == FALSE )
                    break;
            }

        #if(ENABLE_TTS_DUMP_DATA)
            msAPI_TTS_Dump_Set_Enable(DISABLE);
        #endif

        #if( ENABLE_DBG_SAVE_USB )
            msDebug_SaveDataToUSB("TTS_Wave", msAPI_TTS_Dump_Get_DumpBuffer(), msAPI_TTS_Dump_Get_DumpDataSize());
        #endif

            printf("Say finish~\n");
            break;
    #endif

    /*
        case 0x5:
            {
                U8 au8Test[10] = {1,2,3,4,5,6,7,8,9,0};
                msDebug_SaveDataToUSB("TestWrite", au8Test, sizeof(au8Test) );
            }
            break;
    */


        case 0x06:
            MApp_TTS_Say_Stop();
            MApp_TTS_Cus_AddU8String((U8*)"DTV - 50-2 CH 50.2 -");
            MApp_TTS_Say_Start();
            break;

        case 0x07:
            MApp_TTS_Say_Stop();
            MApp_TTS_Cus_AddU8String((U8*)"DTV - 50-2 CH 50.2 -");
            MApp_TTS_Say_Start();
            MApp_TTS_WaitSayFinish(TTS_NO_TIMEOUT);
            break;


    }
}
#endif

