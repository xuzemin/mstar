#if defined(__aeon__)

#include "Board.h"

#include "Utl.h"
#include "MsOS.h"

#include "r2_backtrace.h"

#include "drvAeonR2.h"



void MDrv_AeonR2_Backtrace(MS_U32 pHalReg)
{
    MHAL_SavedRegisters * regs;
    regs = (MHAL_SavedRegisters *)pHalReg;

    printf("\n===== R2 Backtrace =====\n");

    printf("r0 : %08X  r1 : %08X  r2 : %08X  r3 : %08X\n", regs->r[0],  regs->r[1],  regs->r[2],  regs->r[3]);
    printf("r4 : %08X  r5 : %08X  r6 : %08X  r7 : %08X\n", regs->r[4],  regs->r[5],  regs->r[6],  regs->r[7]);
    printf("r8 : %08X  r9 : %08X  r10: %08X  r11: %08X\n", regs->r[8],  regs->r[9],  regs->r[10], regs->r[11]);
    printf("r12: %08X  r13: %08X  r14: %08X  r15: %08X\n", regs->r[12], regs->r[13], regs->r[14], regs->r[15]);
    printf("r16: %08X  r17: %08X  r18: %08X  r19: %08X\n", regs->r[16], regs->r[17], regs->r[18], regs->r[19]);
    printf("r20: %08X  r21: %08X  r22: %08X  r23: %08X\n", regs->r[20], regs->r[21], regs->r[22], regs->r[23]);
    printf("r24: %08X  r25: %08X  r26: %08X  r27: %08X\n", regs->r[24], regs->r[25], regs->r[26], regs->r[27]);
    printf("r28: %08X  r29: %08X  r30: %08X  r31: %08X\n", regs->r[28], regs->r[29], regs->r[30], regs->r[31]);

    printf("sr : %08X  pc : %08X  eear: %08X\n", regs->sr, regs->pc, regs->eear);

  #if( ENABLE_R2_BACKTRACE )
    r2_online_except_bt(regs->r[1], regs->pc, regs->r[9]);
  #endif
}

#if 0//( ENABLE_R2_BACKTRACE )
#define R2BT_CMD_BUF_SZIE   8

static U8 s_R2BT_au8CmdBuf[R2BT_CMD_BUF_SZIE];
static U8 s_R2BT_u8CmdBufLen = 0;

BOOL MDrv_R2BT_RecvDataHandler(U8 u8Data, MS_U32 pHalReg)
{
    BOOL bEnterKeyPressed = FALSE;


    if( (u8Data == 0x0D) || (u8Data == 0x0A) )
    {
        bEnterKeyPressed = TRUE;
    }
    else
    {
        if( s_R2BT_u8CmdBufLen < R2BT_CMD_BUF_SZIE )
        {
            //if( u8Data != '\n' )
            {
                s_R2BT_au8CmdBuf[s_R2BT_u8CmdBufLen] = u8Data;
                s_R2BT_u8CmdBufLen += 1;
            }
        }
    }

/*
    //if( u8Data == '\n' )
    if( bEnterKeyPressed )
    {
        U8 i;
        printf("Cmd[%u]={", s_R2BT_u8CmdBufLen);
        for( i = 0; i < s_R2BT_u8CmdBufLen; i += 1 )
        {
            printf(" 0x%X ", s_R2BT_au8CmdBuf[i]);
        }
        //printf("} 0x%X ", '\n');
        printf("\n");
    }
*/

    if( bEnterKeyPressed )
    {
        // Password = "bt1234"
        if( (s_R2BT_u8CmdBufLen == 6)
          &&(strncmp( "bt1234", (const char *)s_R2BT_au8CmdBuf, 6) == 0)
          )
        {
            //printf("pHalReg=0x%X\n", pHalReg);
            {
                MHAL_SavedRegisters * regs;
                regs = (MHAL_SavedRegisters *)pHalReg;
                printf("\n===== R2 Backtrace =====\n");

                printf("r0 : %08X  r1 : %08X  r2 : %08X  r3 : %08X\n", regs->r[0],  regs->r[1],  regs->r[2],  regs->r[3]);
                printf("r4 : %08X  r5 : %08X  r6 : %08X  r7 : %08X\n", regs->r[4],  regs->r[5],  regs->r[6],  regs->r[7]);
                printf("r8 : %08X  r9 : %08X  r10: %08X  r11: %08X\n", regs->r[8],  regs->r[9],  regs->r[10], regs->r[11]);
                printf("r12: %08X  r13: %08X  r14: %08X  r15: %08X\n", regs->r[12], regs->r[13], regs->r[14], regs->r[15]);
                printf("r16: %08X  r17: %08X  r18: %08X  r19: %08X\n", regs->r[16], regs->r[17], regs->r[18], regs->r[19]);
                printf("r20: %08X  r21: %08X  r22: %08X  r23: %08X\n", regs->r[20], regs->r[21], regs->r[22], regs->r[23]);
                printf("r24: %08X  r25: %08X  r26: %08X  r27: %08X\n", regs->r[24], regs->r[25], regs->r[26], regs->r[27]);
                printf("r28: %08X  r29: %08X  r30: %08X  r31: %08X\n", regs->r[28], regs->r[29], regs->r[30], regs->r[31]);

                printf("sr : %08X  pc : %08X  eear: %08X\n", regs->sr, regs->pc, regs->eear);

                r2_online_except_bt(regs->r[1], regs->pc, regs->r[9]);
            }

            return TRUE;
        }

        s_R2BT_u8CmdBufLen = 0;

    }

    return FALSE;
}

#endif // ENABLE_R2_BACKTRACE

#endif // Aeon

