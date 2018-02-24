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
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
///@file drvMmsDbg.c
///@brief System functions:Menu mode System debug mode related functions
//
///////////////////////////////////////////////////////////////////////////////


#include "datatype.h"
#include "drvMmsDisp_if.h"
#include "MsCommon.h"
#include "drvUartDebug.h"
#if ( ENABLE_MMS)
#include <math.h>
#include "drvMmsCfg_if.h"
#include "drvMmsCfgSw_if.h"
#include "drvUART.h"

typedef struct {
    U8 *para0;
    U8 *para1;
    U8 *para2;
    U8 *para3;
    U8 *para4;
    U8 *para5;
    U8 *para6;
    U8 *para7;
    U8 *para8;
    U8 *para9;
}para_t;
para_t parmtbl;

int DbgMenuMode  = 0;
int DbgMenuLevel = 0;
int CatMenuLevel = 0;
int UntMenuLevel = 0;
int CfgMenuLevel = 0;

U8 InputPara = 0;
U8 ParaTbl[PARA_ROW_SIZE][PARA_COL_SIZE];
U8 ParaTblLen[PARA_ROW_SIZE];
U8 ParaTblIndex = 0;
U8 ParaIndex    = 0;
//U16 para[PARA_ROW_SIZE];
U8 dynLevel = 0;


void MDrv_MMS_ClearCmd(void)
{
       UART_MENU_CMD0 = NULL;
       UART_MENU_CMD1 = NULL;
       UART_MENU_CMD2 = NULL;
       UART_MENU_CMD3 = NULL;
       UART_MENU_CMD4 = NULL;
       UART_MENU_CMD5 = NULL;
       UART_MENU_CMD6 = NULL;
       UART_MENU_CMD7 = NULL;
       UART_MENU_CMD8 = NULL;
       UART_MENU_CMD9 = NULL;
       UART_MENU_CMD10 = NULL;
       UART_MENU_CMD11 = NULL;
       UART_MENU_CMD12 = NULL;
       UART_MENU_CMD13 = NULL;
       UART_MENU_CMD14 = NULL;
       UART_MENU_CMD15 = NULL;
       UART_MENU_CMD16 = NULL;
}


void MDrv_MMS_UARTRecvHandler(int c)
{
    g_Uart0CheckTick = 5000;           // time-out control ms

    //BS
    if(0x08 == c)
    {
        printf("\x1B[D");
        g_UartCommand.Index--;
        #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
            MsOS_EnableInterrupt(E_INT_IRQ_UART0);
        #endif
        return;
    }

    // Enter -- eof command
    if (0x0D == c)
    {
       g_bUart0Detected     = TRUE;    // command  buffer recieve ok
       g_UartCommand.Index  = 0;       // reset index of command buffer
      g_Uart0CheckTick     = 0;
       //
       InputPara            = 0;
      // Prompt = 1;
      ParaTblIndex          =0;
      ParaIndex             =0;
      #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
          MsOS_EnableInterrupt(E_INT_IRQ_UART0);
      #endif
       return;
    }

    //FF -- pre-page
    if(((UART_MENU_CMD0  == 'F' ) && (UART_MENU_CMD1  == 'F' )) ||
        ((UART_MENU_CMD0  == 'f' ) && (UART_MENU_CMD1  == 'f' )))
    {
        g_bUart0Detected     = TRUE;    // command  buffer recieve ok
        g_UartCommand.Index  = 0;       // reset index of command buffer
        g_Uart0CheckTick     = 0;

        if( (CfgMenuLevel == 2 || DbgMenuLevel == 2 || CatMenuLevel == 2 || UntMenuLevel == 2 ) && dynLevel)
        {
            printf("%c",c);
            dynLevel = 0;
            UART_MENU_CMD0 = 0x30;
            UART_MENU_CMD1 = 0x30;
            UART_MENU_CMD2 = 0x31;
        #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
            MsOS_EnableInterrupt(E_INT_IRQ_UART0);
        #endif
            return;
        }
        else
        {
            if(CfgMenuLevel > 0)
                CfgMenuLevel--;
            else if(DbgMenuLevel > 0)
                DbgMenuLevel--;
            else if(CatMenuLevel > 0)
                CatMenuLevel--;
            else if(UntMenuLevel > 0)
                UntMenuLevel--;
        }

        printf("%c",c);
        if (!(DbgMenuLevel ||CatMenuLevel || CfgMenuLevel || UntMenuLevel))
            MDrv_MainPagePrint();
        MDrv_MMS_ClearCmd();
        #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
            MsOS_EnableInterrupt(E_INT_IRQ_UART0);
        #endif
        return;
    }

    // ESC -- exit menu mode
    if (0x1B == c)
    {
            g_bUart0Detected     = TRUE;    // command  buffer recieve ok
            g_UartCommand.Index  = 0;       // reset index of command buffer
            g_Uart0CheckTick     = 0;       // reset timer
            DbgMenuMode          = 0;       // exit menu mode.
            DbgMenuLevel         = 0;       // reset dbg status
            CatMenuLevel         = 0;       // reset cat status
            UntMenuLevel         = 0;       // reset unt status
            CfgMenuLevel         = 0;       // reset cfg status

            dbg_type             = 0;
            dbg_level            = 0;
            cfg_type             = 0;
            cfg_level            = 0;
            MDrv_LogoPrint();
            printf("\n");
            printf("******************************************\n");
            printf("* Exit MStar Uart Debug Menu Mode System *\n");
            printf("******************************************\n");
            printf("\n                                        \n");
        #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
               MsOS_EnableInterrupt(E_INT_IRQ_UART0);
        #endif
            return;

    }

    // print input para.
    printf("%c",c);
    g_UartCommand.Index++;

    #if defined(MIPS_CHAKRA) || defined(__AEONR2__)
          MsOS_EnableInterrupt(E_INT_IRQ_UART0);
    #endif
    return;
}




void MDrv_ClearParaTbl(void)
{
   int x, y;

    for(x=0;x<PARA_ROW_SIZE;x++)
    {
        for(y=0;y<PARA_COL_SIZE;y++)
        {
            ParaTbl[x][y] = 0;
            para[x] = 0;
        }
    }
}

void MDrv_MMS_ParseCmdParm(int c)
{
    // get next parm.
    if (0x20 == c || 0x0D ==c) //space //enter
    {
        ParaTblLen[ParaTblIndex] = ParaIndex;

        ParaTblIndex++;
        ParaIndex =0;

        if ( ParaTblIndex >= PARA_ROW_SIZE)
        {
            printf("\nUp to the max para unmber !!!\n");
            return;
        }
    }

    //
    if (ParaIndex < PARA_ROW_SIZE)
    {
        if ((0x2D != c) && (0x20 != c) && (0x0D !=c))
        {
            ParaTbl[ParaTblIndex][ParaIndex] = c-48;
            ParaIndex++;
        }
    }
    else
    {
        printf("exceed the max para accounts\n");
        printf("press the para again\n");
        printf("\\>\n");
        ParaIndex = 0;
    }


}


void MDrv_DumpParaTbl(void)
{
    int x, y;
    printf("\n\n");

    printf("\n\n");
    printf("===============================\n");
    for(x=0;x<PARA_ROW_SIZE;x++)
    {
        for(y=0;y<PARA_COL_SIZE;y++)
        {
            if (y ==0)
                printf("Para %d: ", x);
            printf("%d", ParaTbl[x][y]);
            if (y==9) printf("\n");
        }
    }
    printf("===============================\n");
}

void Hex2Dec(void)
{
    U32 i, j;

    for(i = 0; i<PARA_ROW_SIZE ; i++)
        for(j = 0; j<PARA_COL_SIZE ;j++)
        {
            if(ParaTbl[i][0] == 0 && ParaTbl[i][1] == 72)
            {
                if(ParaTbl[i][j] == 17|| ParaTbl[i][j] == 49) //'a' or 'A'
                   ParaTbl[i][j] = 10;
                else if(ParaTbl[i][j] == 18|| ParaTbl[i][j] == 50) //'b' or 'B'
                   ParaTbl[i][j] = 11;
                else if(ParaTbl[i][j] == 19|| ParaTbl[i][j] == 51) //'c' or 'C'
                   ParaTbl[i][j] = 12;
                else if(ParaTbl[i][j] == 20|| ParaTbl[i][j] == 52) //'d' or 'D'
                   ParaTbl[i][j] = 13;
                else if(ParaTbl[i][j] == 21|| ParaTbl[i][j] == 53) //'e' or 'E'
                   ParaTbl[i][j] = 14;
                else if(ParaTbl[i][j] == 22|| ParaTbl[i][j] == 54) //'f' or 'F'
                   ParaTbl[i][j] = 15;
            }
        }
}
U32 digital2int(U8 index, U8 len, U8 unit)
{
    U32 sum = 0;
    U8 s = 0, i = index, j;

    if (16 == unit)
        s = 2;
    else if (10 == unit)
        s = 0;

    for(j = 0; j < len; j++)
    {
        sum += ParaTbl[i][s]*pow(unit,len-1);
        s++;
    }
    return sum;
}

void HotKey_Decode(void)
{
    //HotKey - 'usb'// usbUpdate
    if((UART_MENU_CMD0 == 'u' && UART_MENU_CMD1 == 's' && UART_MENU_CMD2 == 'b') ||
        (UART_MENU_CMD0 == 'U' && UART_MENU_CMD1 == 'S' && UART_MENU_CMD2 == 'B'))
    {
        printf("do usb\n");
        MDrv_UsbUpdate();
    }

    //uart switch - none
     if((UART_MENU_CMD0 == 'n' && UART_MENU_CMD1 == 'o' && UART_MENU_CMD2 == 'n' && UART_MENU_CMD3 == 'e') ||
        (UART_MENU_CMD0 == 'N' && UART_MENU_CMD1 == 'O' && UART_MENU_CMD2 == 'N' && UART_MENU_CMD3 == 'E'))
    {
        printf("switch uart to None\n");
        mdrv_uart_connect(E_UART_PORT0, E_UART_OFF);
    }

     //uart switch - hk
     if((UART_MENU_CMD0 == 'h' && UART_MENU_CMD1 == 'k') ||
        (UART_MENU_CMD0 == 'H' && UART_MENU_CMD1 == 'K' ))
    {
        printf("switch uart to HK\n");
        mdrv_uart_connect(E_UART_PORT0, E_UART_PIU_UART0);
    }

    //uart switch - mm
     if((UART_MENU_CMD0 == 'm' && UART_MENU_CMD1 == 'm') ||
        (UART_MENU_CMD0 == 'M' && UART_MENU_CMD1 == 'M' ))
    {
        printf("switch uart to MM\n");
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S8)
        mdrv_uart_connect(E_UART_PORT0, E_UART_AEON_R2);
#else
        mdrv_uart_connect(E_UART_PORT0, E_UART_AEON);
#endif
    }

     //uart switch - vdec
     if((UART_MENU_CMD0 == 'v' && UART_MENU_CMD1 == 'd' && UART_MENU_CMD2 == 'e' && UART_MENU_CMD3 == 'c') ||
        (UART_MENU_CMD0 == 'V' && UART_MENU_CMD1 == 'D' && UART_MENU_CMD2 == 'E' && UART_MENU_CMD3 == 'C'))
    {
        printf("switch uart to VDEC\n");
        mdrv_uart_connect(E_UART_PORT0, E_UART_VDEC);
    }

    if(((UART_MENU_CMD0 == 'h') && (UART_MENU_CMD1 == 'e') && (UART_MENU_CMD2 == 'l') && (UART_MENU_CMD3 == 'p')) ||
        ((UART_MENU_CMD0 == 'H') && (UART_MENU_CMD1 == 'E') && (UART_MENU_CMD2 == 'L') && (UART_MENU_CMD3 == 'P')))
    {
        MMS_Help();
    }
}

void MMS_Help(void)
{
    printf("\n");
    printf("************************************************************* \n");
    printf("<<COMMOM>>\n");
    printf("    FF - return to pre-page\n");
    printf("    ESC - exit uart debug system\n");
    printf("    '-' - input parameter\n");
    printf("\n<<HOTKEY>>\n");
    printf("    USB - usb update\n ");
    printf("   UART switch\n");
    printf("     none\nhk\nmm\nvdec\n");
    printf("************************************************************* \n");
    printf("\n");
}


BOOLEAN MDrv_GetPara(U8 para_count)
{
    U32 sum;
    U8 i, paraCount = 0;

    Hex2Dec();
    for(i = 0; i<PARA_ROW_SIZE;i++)
    {
        sum = 0;
        if(ParaTbl[i][0] == 0 && (ParaTbl[i][1] == 72 || ParaTbl[i][1] == 40)) //'0x' or '0X'
        {
            ParaTblLen[i] -=2;
            sum = digital2int(i, ParaTblLen[i], 16);
        }
        else
        {
            sum = digital2int(i ,ParaTblLen[i], 10);
        }
        para[i] = (U16)sum;
    }

    for(i = 0; i< para_count; i++)
    {
        if(0 != ParaTblLen[i])
            paraCount++;
    }

    if(paraCount < para_count)
    {
        printf("the format isn't match\n");
        return FALSE;
    }

    printf("\n");

    //for(i =0;i <10;i++)
        //printf("%d\n",para[i]);

    return TRUE;
}



void MDrv_LogoPrint(void)
{
printf("\n");
printf("********************************************************************************** \n");
printf("*  ,,_,,_       _,,_,,                                                           * \n");
printf("*  400000#_     _000000pe&'                                                      * \n");
printf("*  4000000M    _0000000T                                                         * \n");
printf("*  40000000&  _00000000                                                          * \n");
printf("*  400000000Nu000000000          _            _                                  * \n");
printf("*  40000#    pMM8#00000     _g00~^'=q      ,gN0                                  * \n");
printf("*  40000#   0#0U8 00000    Q0000g        ]M0000          ___                     * \n");
printf("*  40000#  BMMB@  00000    0000006      NQ00000VM    _pF~~~0M0pg    ]N00N& gMM&  * \n");
printf("*  40000#y0#M0#   00000    0000000&_     ]00000      F     ]0000#   4000000`     * \n");
printf("*  40000M0RBQ0    00000     0000000Mp    ]0000&      __,,_ ]0000#   40000#       * \n");
printf("*  4000MMDM8#t    00000     `000000006   ]0000&     p000# `M0000#   00000#       * \n");
printf("*  4000M0OBM0     00000       M0000000,  ]00000    j00006  ]00000   N0000#       * \n");
printf("*  400000 ]N9     00000        7000000{  40000&    40000&   00000   Q0000#       * \n");
printf("*  gg0000#ggKf  _gg00000&g *q     00000   ~0000& _A *0000&  j0000#   Q0000#      * \n");
printf("*  000MM0MM0f   #00000000&   ^*r,gMM0~     ~00000^   ~MM0MeF M00006  MMM0M#      * \n");
printf("*                                                                                * \n");
printf("*                    Welcome to MStar Menu Mode System 1.0                       * \n");
printf("*                                                                                * \n");
printf("********************************************************************************** \n");
}

void MDrv_MainPagePrint(void)
{
    printf("\n");
    printf("************************************************************* \n");
    printf(" -Press 'dbg' enter debug main page \n");
    printf(" -Press 'cat' enter cateye main page\n");
    printf(" -Press 'unt' enter unit test main page\n");
    printf(" -Press 'cfg' enter set config main page\n");
    printf(" -Press <ESC> exit uart debug system\n");
    printf("************************************************************* \n");
    printf(":\\M>");
}

#endif //ENABLE_MSTV_UART_DEBUG

