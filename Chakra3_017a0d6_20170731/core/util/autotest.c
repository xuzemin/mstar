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
#ifdef MSOS_TYPE_LINUX
#include <string.h>
#endif

#include <stdio.h>
#include "MsCommon.h"
#include "autotest.h"
#include "MApp_GlobalVar.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "MApp_GlobalSettingSt.h"
#include "MApp_TopStateMachine.h"
#include "MApp_RestoreToDefault.h"
#include "ZUI_exefunc.h"
#include "MApp_Install_Main.h"

#include "MApp_Key.h"

#include "drvGlobal.h"
#include "SysInit.h"

#include "apiGOP.h"
#include "msAPI_Video.h"
//#include "drvvdec_datatype.h"
#include "Utl.h"
#include "util_symbol.h"
#include "mw_debug.h"
#include "Analog_Reg.h"

#if MHEG5_ENABLE
#include "msAPI_MHEG5.h"
#include "msAPI_MailBox.h"
#endif

#if ENABLE_AUTOTEST

#if DHRY //Benchmark Dhry 2.1
#include "msAPI_CPU.h"
#include "InfoBlock.h"
#include "msAPI_Memory.h"
#include "msAPI_MIU.h"
//#include "msAPI_MHEG5.h"
#include "msAPI_MailBox.h"
#endif


#if ENABLE_DMP
extern BOOLEAN g_bOutputMMAliveMessage;
#endif

#if ENABLE_AUTOTEST
BOOLEAN g_bAutobuildDebug = false;
#endif

extern U32 UART_EXT_COUNT;
//static U32 CRC32Result;

void msAPI_Timer_Delayms(U32 u32DelayTime);

#define TOLERATE 60
#define PROP  0.6
#define IS_OFFSET 0x80000    //0x61280



fbuf_t fbuf;

#if 0
/// Frame buffer attributes for GWIN
typedef struct
{
    U8 gWinId;          ///< id
    U8 enable:1;        ///< 4bits enable
    U8 allocated:1;    ///< 4bits

    U16 x0;                 ///< U16
    U16 y0;                 ///< U16
    U16 x1;                 ///< U16
    U16 y1;                 ///< U16
    U16 width;                 ///< U16
    U16 height;                 ///< U16
    U16 pitch;                     ///< U16
    U16 fbFmt;                 ///< U16

    U32 addr;                     ///< U32
    U32 size;                     ///< U32

    U8 next;                 ///< U8
    U8 prev;                     ///< U8
    U8 string;               //store which AP use this FB
    //U8 flag;                ///< bit 0:scroll
    U16 s_x;                ///< U16
    U16 s_y;                ///< U16
    U16 dispWidth;          ///< U16
    U16 dispHeight;         ///< U16
} GOP_GwinFBAttr;
#endif


extern U32 debug_symbol_tbl[SYMBOL_LAST];


static unsigned long  u32CRC;



void CRC32_Init(void)
{
    u32CRC = 0xFFFFFFFF;
}


U32 CRC32_GetResult(void)
{
    return (~u32CRC);
}

#if 0 // 20150211 No use
void _msAPI_DMX_Init_CRC_Table(U32 *u32CRCtemptable)
{

    int i,j,tmp, result;

    for(i=0;i<=0xFF;i++)
    {
        tmp=i;
        result=0;

        for(j=1;j<9;j++)
        {
             if(tmp & 1)
             {
                        result |= (1 << (8 - j));
             }
             tmp >>= 1;
        }

        u32CRCtemptable[i]=result<<24;
        for(j=0; j<8; j++)
        {
            u32CRCtemptable[i] = (u32CRCtemptable[i] << 1) ^ ((u32CRCtemptable[i] & (1 << 31)) ? 0x04C11DB7 : 0);
        }

        tmp=u32CRCtemptable[i];
        result=0;

        for(j=1;j<33;j++)
        {
             if(tmp & 1)
             {
                result |= (1 << (32 - j));
             }
             tmp >>= 1;
        }
        u32CRCtemptable[i]=result;
        }
}

void CRC32_Update(const U8 *pu8Data, U32 u32Size)
{
    U32 u32CRCTable[256];
    U32  u32LoopCounter;

    if (pu8Data == NULL || u32Size == 0) return;

    _msAPI_DMX_Init_CRC_Table(u32CRCTable);

    #if 0
        int i;
        for(i = 0;i<256;i++)
        {
            printf("0x%08x,\n", u32CRCTable[i]);
        }
    #endif

    for (u32LoopCounter=0; u32LoopCounter<u32Size; u32LoopCounter++)
    {
        u32CRC = (u32CRC >> 8) ^ u32CRCTable[ pu8Data[u32LoopCounter] ^ (unsigned char)(u32CRC & 0xFF) ];
    }
}

void send_mailbox_test2(U8 mbxindex)  //change index to mbxindex : To fix compiler error
{
    if (mbxindex == 0)
    {
        //send GE info
        U8           fbid;
        GOP_GwinFBAttr sFBInfo;
        fbid = MApi_GOP_GWIN_GetFBfromGWIN(5);
        MApi_GOP_GWIN_GetFBInfo(fbid,&sFBInfo);

        CRC32_Init();
        CRC32_Update((U8 *)sFBInfo.addr,(U32) sFBInfo.size);
        CRC32Result = CRC32_GetResult();
        printf("CRC32Result(OSD) = %8lx\n", CRC32Result);
    }
}
#endif


#if 0 // 20150211 No use
void MDrv_PWMGT_Attach(U8 u8IPIndex, void (*func)(void))
{
    printf("attache index = %d\n", u8IPIndex);
    printf("MDrv_MVD_PW_Test address = %lx\n", (U32)func);
    printf("F[index]= %lx\n", (U32)F[u8IPIndex]);
    F[u8IPIndex] = func;
    printf("F[index]= %lx\n", (U32)F[u8IPIndex]);
}

void MDrv_PWMGT_Detach(U8 u8IPIndex)
{
    F[u8IPIndex] = NULL;
}

void MDrv_PWMGT_Excute(U8 index1)
{
    U8 index_local = index1-48;  //only for user input ASSCI code '0' = 0x30

   // add for test mailbox command
   printf("Send nwdebug command via mailbox\n");

   // printf("MB_51_REG_CMD_CLASS = %d\n",MDrv_ReadByte(MB_51_REG_CMD_CLASS) );
   // printf("MB_51_REG_CMD_IDX = %d\n",MDrv_ReadByte(MB_51_REG_CMD_IDX) );
   // printf("MB_51_REG_PARAM_CNT = %d\n",MDrv_ReadByte(MB_51_REG_PARAM_CNT) );

   send_mailbox_test2(index_local);
   // printf("class = %d",MDrv_ReadByte(0x3381) );

#if 0
    if (F[(index)])
        F[(index)]();
    else
        printf("Un-attached HW IP\n");
#endif
}
#endif

void MDrv_Autotest_Excute_Key(U8 index1)
{
    u8KeyCode = index1;
}

void MDrv_Autotest_Excute_Sp(U8 index1)
{
#if 1 // 20150211 No Use
    index1=index1;
#else
    if (I[(index1)])
        I[(index1)]();
    else
        printf("Un-attached Autotest Fun.\n");
#endif
}


#include "MApp_GlobalSettingSt.h"

#if MHEG5_ENABLE
MS_BOOL _bMheg5DbgInitialized = FALSE;
void MDrv_Mheg5_Debug(void)
{
    MBX_MSGQ_Status Mstatus;
    MBX_Msg mheg5Msg;
    MS_U16 u16MailCnt=0;
    MBX_Result mbxResult=E_MBX_UNKNOW_ERROR;

    memset(&Mstatus,0,sizeof(MBX_MSGQ_Status));
    memset(&mheg5Msg,0,sizeof(MBX_Msg));

    if(FALSE == _bMheg5DbgInitialized)
    {
        //mbxResult = MSApi_MBX_Init();
        //if(E_MBX_SUCCESS != mbxResult)
        //{
        //    printf("MBX init error\n");
        //}
        MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_AUTO_TEST);
        mbxResult = MSApi_MBX_RegisterMSG(E_MBX_CLASS_AUTO_TEST, 0xA);
        if(E_MBX_SUCCESS != mbxResult)
        {
            printf("E_MBX_CLASS_AUTO_TEST - MBX register msg error\n");
        }
        //MSApi_MBX_Enable(TRUE);
        msAPI_MHEG5_AUTOTEST_Enable(TRUE);
        _bMheg5DbgInitialized = TRUE;
    }

    MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_AUTO_TEST, &Mstatus);
    if(Mstatus.status & MBX_STATUS_QUEUE_HAS_NORMAL_MSG)
    {
      //printf("==>.....2\n");
      for(u16MailCnt=0; u16MailCnt<Mstatus.u32NormalMsgCount; u16MailCnt++)
      {
          MSApi_MBX_RecvMsg(E_MBX_CLASS_AUTO_TEST, &mheg5Msg, 0,MBX_CHECK_NORMAL_MSG);

          if(mheg5Msg.u8MsgClass == E_MBX_CLASS_AUTO_TEST)
          {
              switch(mheg5Msg.u8Parameters[0])
              {
                  case 0x1C:
                      printf("111_MHEG5_Alive\n");
                      printf("111_MHEG5_Red\n");
                      break;

                  case 0x1D:
                      printf("111_MHEG5_Green\n");
                      break;

                  case 0x33:
                      printf("111_MHEG5_Yellow\n");
                      break;

                  case 0x34:
                      printf("111_MHEG5_Blue\n");
                      break;

                  default:

                      break;
              }
              //printf("MHEG5Q.u8Parameters[0] = %x \n", MHEG5Q.u8Parameters[0]);
          }
      }
    }
}
#endif // #if MHEG5_ENABLE

#if DHRY //Benchmark Dhry 2.1

#define structassign(d, s)      d = s

Rec_Pointer Ptr_Glob, Next_Ptr_Glob;
BOOL    Bool_Glob;
U32     Int_Glob;
U8      Ch_1_Glob, Ch_2_Glob;
U32     Arr_1_Glob[50];
U32     Arr_2_Glob[50][50];

void dhry2(unsigned int* final)
{
    printf("*****************************************************\n");
    printf("\n");
    printf("Dhrystone Benchmark, Version 2.1 (Language: C or C++)\n");
    printf("\n");

    U32   Int_1_Loc = 0, Int_2_Loc = 0, Int_3_Loc = 0;
    U8    Ch_Index;
    U32   Enum_Loc;
    U8    Str_1_Loc[31];
    U8    Str_2_Loc[31];
    U32   Run_Index;
    unsigned long long   Number_Of_Runs=0;
    U32   count = 10;
    U32   mstimer, User_Time;
    U32   Microseconds, Dhrystones_Per_Second;


    //Next_Ptr_Glob = (Rec_Pointer)MsOS_AllocateMemory(sizeof(Rec_Type), 0);
    Next_Ptr_Glob = (Rec_Pointer)msAPI_Memory_Allocate(sizeof(Rec_Type), BUF_ID_AUTO_TEST);

    //Ptr_Glob = (Rec_Pointer)MsOS_AllocateMemory(sizeof(Rec_Type), 1);
    Ptr_Glob = (Rec_Pointer)msAPI_Memory_Allocate(sizeof(Rec_Type), BUF_ID_AUTO_TEST);

    Ptr_Glob->Ptr_Comp                    = Next_Ptr_Glob;
    Ptr_Glob->Discr                       = 0;
    Ptr_Glob->variant.var_1.Enum_Comp     = 2;
    Ptr_Glob->variant.var_1.Int_Comp      = 40;

    strcpy((char *)Ptr_Glob->variant.var_1.Str_Comp, "DHRYSTONE PROGRAM, SOME STRING");
    strcpy((char *)Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING");

    Arr_2_Glob[8][7] = 10;

    Number_Of_Runs = 5000;

    do
    {
        Number_Of_Runs = Number_Of_Runs * 2;
        count = count - 1;
        Arr_2_Glob[8][7] = 10;

        /***************/
        /* Start timer */
        /***************/

        //start_time();
        mstimer = MsOS_GetSystemTime();

        for(Run_Index = 1; Run_Index <= Number_Of_Runs; ++Run_Index)
        {

            Proc_5();
            Proc_4();
            Int_1_Loc = 2;
            Int_2_Loc = 3;
            strcpy((char *)Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING");
            Enum_Loc = 1;
            Bool_Glob = !Func_2(Str_1_Loc, Str_2_Loc);
            while(Int_1_Loc < Int_2_Loc)
            {
                Int_3_Loc = 5 * Int_1_Loc - Int_2_Loc;
                Proc_7(Int_1_Loc, Int_2_Loc, &Int_3_Loc);
                Int_1_Loc += 1;
            }
            Proc_8(Arr_1_Glob, Arr_2_Glob, Int_1_Loc, Int_3_Loc);

            Proc_1(Ptr_Glob);
            for(Ch_Index = 'A'; Ch_Index <= Ch_2_Glob; ++Ch_Index)
            {
                if(Enum_Loc == Func_1 (Ch_Index, 'C'))
                {
                    Proc_6(0, &Enum_Loc);
                    strcpy((char *)Str_2_Loc, "DHRYSTONE PROGRAM, 3'RD STRING");
                    Int_2_Loc = Run_Index;
                    Int_Glob = Run_Index;
                }
            }
            Int_2_Loc = Int_2_Loc * Int_1_Loc;
            Int_1_Loc = Int_2_Loc / Int_3_Loc;
            Int_2_Loc = 7 * (Int_2_Loc - Int_3_Loc) - Int_1_Loc;

            Proc_2(&Int_1_Loc);

        }   /* loop "for Run_Index" */

        /**************/
        /* Stop timer */
        /**************/

        User_Time = MsOS_Timer_DiffTimeFromNow(mstimer);

        printf("%12lu runs %6lu.%03lu seconds \n", (U32)Number_Of_Runs, User_Time / 1000, User_Time % 1000);
        if(User_Time > 2000)
        {
            count = 0;
        }
        else
        {
            if(User_Time < 50)
            {
                Number_Of_Runs = Number_Of_Runs * 5;
            }
        }

    }while(count > 0);

    printf("\n");
    printf("Final values (* implementation-dependent):\n");
    printf("\n");
    printf("Int_Glob:      ");
    if(Int_Glob == 5)  printf("O.K.  ");
    else               printf("WRONG ");
    printf("%lu  ", Int_Glob);

    printf("Bool_Glob:     ");
    if(Bool_Glob == 1) printf("O.K.  ");
    else               printf("WRONG ");
    printf("%d\n", Bool_Glob);

    printf("Ch_1_Glob:     ");
    if(Ch_1_Glob == 'A')  printf("O.K.  ");
    else                  printf("WRONG ");
    printf("%c  ", Ch_1_Glob);

    printf("Ch_2_Glob:     ");
    if(Ch_2_Glob == 'B')  printf("O.K.  ");
    else                  printf("WRONG ");
    printf("%c\n",  Ch_2_Glob);

    printf("Arr_1_Glob[8]: ");
    if(Arr_1_Glob[8] == 7)  printf("O.K.  ");
    else                    printf("WRONG ");
    printf ("%lu  ", Arr_1_Glob[8]);

    printf("Arr_2_Glob8/7: ");
    if(Arr_2_Glob[8][7] == Number_Of_Runs + 10)
                          printf("O.K.  ");
    else                  printf("WRONG ");
    printf("%10lu\n", Arr_2_Glob[8][7]);

    printf("Ptr_Glob->            ");
    printf("  Ptr_Comp:       *    %lu\n", (U32) Ptr_Glob->Ptr_Comp);

    printf("  Discr:       ");
    if(Ptr_Glob->Discr == 0)  printf("O.K.  ");
    else                      printf("WRONG ");
    printf("%lu  ", Ptr_Glob->Discr);

    printf("Enum_Comp:     ");
    if(Ptr_Glob->variant.var_1.Enum_Comp == 2)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu\n", Ptr_Glob->variant.var_1.Enum_Comp);

    printf("  Int_Comp:    ");
    if(Ptr_Glob->variant.var_1.Int_Comp == 17)  printf("O.K.  ");
    else                                        printf("WRONG ");
    printf("%lu ", Ptr_Glob->variant.var_1.Int_Comp);

    printf("Str_Comp:      ");
    if(strcmp((char *)Ptr_Glob->variant.var_1.Str_Comp,
                        "DHRYSTONE PROGRAM, SOME STRING") == 0)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%s\n", Ptr_Glob->variant.var_1.Str_Comp);

    printf("Next_Ptr_Glob->       ");
    printf("  Ptr_Comp:       *    %lu", (U32) Next_Ptr_Glob->Ptr_Comp);
    printf(" same as above\n");

    printf("  Discr:       ");
    if(Next_Ptr_Glob->Discr == 0)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu  ", Next_Ptr_Glob->Discr);

    printf("Enum_Comp:     ");
    if(Next_Ptr_Glob->variant.var_1.Enum_Comp == 1)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf ("%lu\n", Next_Ptr_Glob->variant.var_1.Enum_Comp);

    printf ("  Int_Comp:    ");
    if(Next_Ptr_Glob->variant.var_1.Int_Comp == 18)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu ", Next_Ptr_Glob->variant.var_1.Int_Comp);

    printf("Str_Comp:      ");
    if(strcmp((char *)Next_Ptr_Glob->variant.var_1.Str_Comp,
                        "DHRYSTONE PROGRAM, SOME STRING") == 0)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%s\n", Next_Ptr_Glob->variant.var_1.Str_Comp);

    printf("Int_1_Loc:     ");
    if(Int_1_Loc == 5)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu  ", Int_1_Loc);

    printf("Int_2_Loc:     ");
    if(Int_2_Loc == 13)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu\n", Int_2_Loc);

    printf("Int_3_Loc:     ");
    if(Int_3_Loc == 7)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu  ", Int_3_Loc);

    printf("Enum_Loc:      ");
    if(Enum_Loc == 1)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%lu\n", Enum_Loc);

    printf("Str_1_Loc:                             ");
    if(strcmp((char *)Str_1_Loc, "DHRYSTONE PROGRAM, 1'ST STRING") == 0)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%s\n", Str_1_Loc);

    printf("Str_2_Loc:                             ");
    if(strcmp((char *)Str_2_Loc, "DHRYSTONE PROGRAM, 2'ND STRING") == 0)
                        printf("O.K.  ");
    else                printf("WRONG ");
    printf("%s\n", Str_2_Loc);

    printf("\n");

    Microseconds = User_Time * 1000;
    *final = Dhrystones_Per_Second = (Number_Of_Runs * 1000) / User_Time;

    printf("Microseconds for one run through Dhrystone: ");
    printf("%12lu.%02lu \n", (U32)(Microseconds / Number_Of_Runs), (U32)(((Microseconds * 100) / Number_Of_Runs) % 100));
    printf("Dhrystones per Second:                      ");
    printf("%12lu \n", Dhrystones_Per_Second);
    printf("VAX  MIPS rating =                          ");
    printf("%12lu.%02lu \n", Dhrystones_Per_Second / 1757, ((Dhrystones_Per_Second * 100) / 1757) % 100);
    printf("\n");

    printf("\n");
    printf("*****************************************************\n");
}

//*********************************************************************
void Proc_1(Rec_Pointer Ptr_Val_Par)
{
    Rec_Pointer Next_Record = Ptr_Val_Par->Ptr_Comp;

    structassign(*Ptr_Val_Par->Ptr_Comp, *Ptr_Glob);
    Ptr_Val_Par->variant.var_1.Int_Comp = 5;
    Next_Record->variant.var_1.Int_Comp
        = Ptr_Val_Par->variant.var_1.Int_Comp;
    Next_Record->Ptr_Comp = Ptr_Val_Par->Ptr_Comp;
    Proc_3(&Next_Record->Ptr_Comp);

    if(Next_Record->Discr == 0)
    {
        Next_Record->variant.var_1.Int_Comp = 6;
        Proc_6(Ptr_Val_Par->variant.var_1.Enum_Comp,
            &Next_Record->variant.var_1.Enum_Comp);
        Next_Record->Ptr_Comp = Ptr_Glob->Ptr_Comp;
        Proc_7(Next_Record->variant.var_1.Int_Comp, 10,
            &Next_Record->variant.var_1.Int_Comp);
    }
    else
    {
        structassign(*Ptr_Val_Par, *Ptr_Val_Par->Ptr_Comp);
    }
}

void Proc_2(U32 *Int_Par_Ref)
{
    U32 Int_Loc;
    U32 Enum_Loc = 0;

    Int_Loc = *Int_Par_Ref + 10;
    do
    {
        if(Ch_1_Glob == 'A')
        {
            Int_Loc -= 1;
            *Int_Par_Ref = Int_Loc - Int_Glob;
            Enum_Loc = 0;
        }
    }while(Enum_Loc != 0);
}

void Proc_3(Rec_Pointer *Ptr_Ref_Par)
{
    if(Ptr_Glob != 0)
        *Ptr_Ref_Par = Ptr_Glob->Ptr_Comp;
    Proc_7(10, Int_Glob, &Ptr_Glob->variant.var_1.Int_Comp);
}

void Proc_4()
{
    BOOLEAN Bool_Loc;

    Bool_Loc = Ch_1_Glob == 'A';
    Bool_Glob = Bool_Loc | Bool_Glob;
    Ch_2_Glob = 'B';
}
void Proc_5()
{
    Ch_1_Glob = 'A';
    Bool_Glob = false;
}

void Proc_6(U32 Enum_Val_Par, U32 *Enum_Ref_Par)
{
    *Enum_Ref_Par = Enum_Val_Par;
    if(! Func_3 (Enum_Val_Par))
        *Enum_Ref_Par = 3;
    switch(Enum_Val_Par)
    {
        case 0:
            *Enum_Ref_Par = 0;
        break;
        case 1:
            if(Int_Glob > 100)
                *Enum_Ref_Par = 0;
            else *Enum_Ref_Par = 3;
        break;
        case 2: /* executed */
            *Enum_Ref_Par = 1;
        break;
        case 3: break;
        case 4:
            *Enum_Ref_Par = 2;
        break;
    }
}

void Proc_7(U32 Int_1_Par_Val, U32 Int_2_Par_Val, U32 *Int_Par_Ref)
{
    U32 Int_Loc;

    Int_Loc = Int_1_Par_Val + 2;
    *Int_Par_Ref = Int_2_Par_Val + Int_Loc;
}

void Proc_8(U32 *Arr_1_Par_Ref, U32 Arr_2_Par_Ref[][50], U32 Int_1_Par_Val, U32 Int_2_Par_Val)
{
    U32 Int_Index;
    U32 Int_Loc;

    Int_Loc = Int_1_Par_Val + 5;
    Arr_1_Par_Ref[Int_Loc] = Int_2_Par_Val;
    Arr_1_Par_Ref[Int_Loc+1] = Arr_1_Par_Ref[Int_Loc];
    Arr_1_Par_Ref[Int_Loc+30] = Int_Loc;
    for(Int_Index = Int_Loc; Int_Index <= Int_Loc+1; ++Int_Index)
    {
        Arr_2_Par_Ref[Int_Loc][Int_Index] = Int_Loc;
    }
    Arr_2_Par_Ref[Int_Loc][Int_Loc-1] += 1;
    Arr_2_Par_Ref[Int_Loc+20][Int_Loc] = Arr_1_Par_Ref[Int_Loc];
    Int_Glob = 5;
}

U32 Func_1(U8 Ch_1_Par_Val, U8 Ch_2_Par_Val)
{
    U8  Ch_1_Loc, Ch_2_Loc;

    Ch_1_Loc = Ch_1_Par_Val;
    Ch_2_Loc = Ch_1_Loc;
    if(Ch_2_Loc != Ch_2_Par_Val)
    {
        return 0;
    }
    else
    {
        Ch_1_Glob = Ch_1_Loc;
        return 1;
    }
}

BOOLEAN Func_2(U8 *Str_1_Par_Ref, U8 *Str_2_Par_Ref)
{
    U32 Int_Loc;
    U8  Ch_Loc;

    Int_Loc = 2;
    while(Int_Loc <= 2)
    {
        if(Func_1(Str_1_Par_Ref[Int_Loc], Str_2_Par_Ref[Int_Loc+1]) == 0)
        {
            Ch_Loc = 'A';
            Int_Loc += 1;
        }
    }
    if(Ch_Loc >= 'W' && Ch_Loc < 'Z')
    {
        Int_Loc = 7;
    }
    if(Ch_Loc == 'R')
    {
        return (true);
    }
    else
    {
        if(strcmp((char *)Str_1_Par_Ref, (char *)Str_2_Par_Ref) > 0)
        {
            Int_Loc += 7;
            Int_Glob = Int_Loc;
            return (true);
        }
        else
        {
            return (false);
        }
    }
}

BOOLEAN Func_3(U32 Enum_Par_Val)
{
    U32 Enum_Loc;

    Enum_Loc = Enum_Par_Val;
    if(Enum_Loc == 2)
        return (true);
    else
        return (false);
}

void _HandleMHEG5MSG1(MBX_Msg *pMsg, MS_BOOL *pbAddToQueue)
{
     pMsg = pMsg;
     pbAddToQueue = pbAddToQueue;
     printf("CB _HandleMHEG5MSG1!!!!!!");
}

void MBX_RECV(unsigned int *final)
{
    MBX_MSGQ_Status Mstatus;
    MBX_Msg mheg5Msg;
    MBX_Result mbxResult;
    int i=0,j=0;
    unsigned int tmp;

    printf("MBX test start\n");

    memset(&Mstatus, 0, sizeof(MBX_MSGQ_Status));
    mbxResult = MSApi_MBX_Init();

    if(E_MBX_SUCCESS != mbxResult)
    {
        printf("MBX init error\n");
        return;
    }

    if(MSApi_MBX_UnRegisterMSG(E_MBX_CLASS_MHEG5_STATE) != E_MBX_SUCCESS)
    {
        printf("MBX UNregister msg error\n");
        MSApi_MBX_ClearMSG(E_MBX_CLASS_MHEG5_STATE);
        mbxResult = MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_MHEG5_STATE, 0xA, _HandleMHEG5MSG1);
        if(E_MBX_SUCCESS != mbxResult)
        {
            printf("!!!!!!MBX register msg error\n");
            return;
        }
    }
    else
    {
        //mbxResult = MSApi_MBX_RegisterMSG(E_MBX_CLASS_MHEG5_STATE, 0xA);
        mbxResult = MSApi_MBX_RegisterMSGWithCallBack(E_MBX_CLASS_MHEG5_STATE, 0xA, _HandleMHEG5MSG1);
        if(E_MBX_SUCCESS != mbxResult)
        {
            printf("!!!!!!MBX register msg error\n");
            return;
        }
    }
    MSApi_MBX_Enable(TRUE);

    printf("\n[1]== GetMsgQueueStatus start ==\n");
    do
    {
        mbxResult = MSApi_MBX_GetMsgQueueStatus(E_MBX_CLASS_MHEG5_STATE, &Mstatus);
    }while(Mstatus.u32NormalMsgCount == 0);
    printf("\n[1]== GetMsgQueueStatus start ==\n");
    //(*(volatile unsigned int*)(0xBF2067A0)) = Mstatus.u32NormalMsgCount;
    mbxResult   = MDrv_MBX_RecvMsg(E_MBX_CLASS_MHEG5_STATE, &mheg5Msg, 0, MBX_CHECK_NORMAL_MSG);

    printf("===get message===\n");
    for(i=0;i<8;i++)
    {
        printf("===u8Parameters[%d] %d===\n",i,mheg5Msg.u8Parameters[i]);
        j = i;

        if(j == 0)
            *final += mheg5Msg.u8Parameters[i];
        else
        {
            tmp = mheg5Msg.u8Parameters[i];
            while(j--)
                tmp *= 10;
            *final += tmp;
        }
        //printf("*final : %d      %d\n",*final,mheg5Msg.u8Parameters[i] );
    }

    printf("\n***** final : %d  **** \n",*final);
   // (*(volatile unsigned int*)(0xBF2067A0)) = mheg5Msg.u8Parameters[0];

}

int variable_tmp = 0;
void MMtest(unsigned int *final)
{
    U32 u32Loop;
    U32   mstimer, User_Time;

    //printf("[%s %d]:%x\n", __FILE__, __LINE__, MsOS_GetSystemTime());    // Chuan.test
    mstimer = MsOS_GetSystemTime();

    u32Loop = 3500000;

    while (u32Loop)
    {
        U32 u32ChunkId;
        U32 u32Flags;
        U32 u32Offset;
        U32 u32Size;
        U32 u32Idx = 0;
        U8 idx;
        volatile U8  u8Byte[4];

        u32Loop--;

        for(idx = 0; idx < 4; idx++)
            u8Byte[idx] = *((volatile U8*)(&variable_tmp + u32Idx++));

        u32ChunkId = (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);

        for(idx = 0; idx < 4; idx++)
            u8Byte[idx] = *((volatile U8*)(&variable_tmp + u32Idx++));

        u32Flags = (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);

        for(idx = 0; idx < 4; idx++)
            u8Byte[idx] = *((volatile U8*)(&variable_tmp + u32Idx++));

        u32Offset = (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);

        for(idx = 0; idx < 4; idx++)
            u8Byte[idx] = *((volatile U8*)(&variable_tmp + u32Idx++));

        u32Size = (U32)u8Byte[0] | ((U32)u8Byte[1] << 8) | ((U32)u8Byte[2] << 16) | ((U32)u8Byte[3] << 24);

        if (u32Idx > 0x400000)
        {
            u32Idx = 0;
        }
    }

    //printf("[%s %d]:%x\n", __FILE__, __LINE__, MsOS_GetSystemTime());    // Chuan.test
    User_Time = MsOS_Timer_DiffTimeFromNow(mstimer);

    *final = User_Time;

}


int _strlen(const char *string)
{
    const char *s;

    s = string;

    while (*s)
        s++;

    return s - string;
}

char *strrev(char *str) {
        char *p1, *p2;

        if (!str || !*str)
                return str;

        for (p1 = str, p2 = str + _strlen(str) - 1; p2 > p1; ++p1, --p2) {
                *p1 ^= *p2;
                *p2 ^= *p1;
                *p1 ^= *p2;
        }

        return str;
}


char* itoa(int n, char *s, int b) {
        static char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        int i=0, sign;

        if ((sign = n) < 0)
                n = -n;

        do {
                s[i++] = digits[n % b];
        } while ((n /= b) > 0);

        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';

        return strrev(s);
}



void CPU_BENCHMARK_TEST(char *str_mips_dhry,char *str_aeon_dhry, char *str_mips_mmtest, char *str_aeon_mmtest)
{
    printf("cpu benchmark test\n");
    unsigned int mips_dhry=0;
    unsigned int aeon_dhry=0;
    unsigned int mips_mmtest=0;
    unsigned int aeon_mmtest=0;

    #ifdef BIN_ID_CODE_AEON_BENCHMARK
    dhry2(&mips_dhry);
    itoa(mips_dhry, str_mips_dhry, 10);
    printf("********************%d    %s\n",mips_dhry,str_mips_dhry);


    msAPI_COPRO_Init(BIN_ID_CODE_AEON_BENCHMARK,((AEON_MEM_MEMORY_TYPE & MIU1) ? (AEON_MEM_ADR | MIU_INTERVAL) : (AEON_MEM_ADR)),AEON_MEM_LEN);
    MBX_RECV(&aeon_dhry);
    itoa(aeon_dhry, str_aeon_dhry, 10);

    printf("easy test bin info end\n");
    MMtest(&mips_mmtest);
    itoa(mips_mmtest, str_mips_mmtest, 10);

    MBX_RECV(&aeon_mmtest);
    itoa(aeon_mmtest, str_aeon_mmtest, 10);
     //MDrv_COPRO_Disable();
    #else
    itoa(mips_dhry, str_mips_dhry, 10);
    itoa(aeon_dhry, str_aeon_dhry, 10);
    itoa(mips_mmtest, str_mips_mmtest, 10);
    itoa(aeon_mmtest, str_aeon_mmtest, 10);
    #endif
}

#endif // DHRY

#endif // #if ENABLE_AUTOTEST
