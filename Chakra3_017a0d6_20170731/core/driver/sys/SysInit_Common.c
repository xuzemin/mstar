
#include "drvWDT.h"
#include "hal_misc.h"

#ifdef __AEONR2__
#include "r2_backtrace.h"
#endif

#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
#include "msAPI_Timer.h"
#include "msAPI_Global.h"
#endif

void MDrv_Sys_StopCpu(U8 u8Flag)
{
    printf("[FORCE STOP]MDrv_Sys_StopCpu(%u)\n", u8Flag);

    if( u8Flag == STOP_CPU__WHILE_1_AND_WDT_STOP )
    {
        MDrv_WDT_Stop(E_WDT_DBGLV_ERR_ONLY);
    }

    while(1)
    {
    };
}

void MDrv_SysInit_CheckSbootUseTime(void)
{
    //for auto test recording booting time from Sboot to Ck3
    //U32 PiuTick = MDrv_Read2Byte(0x3048);
    //PiuTick |= (MDrv_Read2Byte(0x304a) << 16);
    U32 u32PiuTick = MHAL_PIU_TIMER_Get_CurTick(PIU_TIMER_1);

    //printf("PiuTick= 0x%X\n", PiuTick);

    //U32 u32SbootUseTimeMs = ((float)u32PiuTick / 12000000ul)*1000 ;  //ms
    U32 u32SbootUseTimeMs = (u32PiuTick / 12000ul);  //ms


#if (ENABLE_AUTOTEST || ENABLE_BOOTTIME)
    PRINT_AUTOTEST_TIME("start sysinit", u32SbootUseTimeMs);
    INIT_AUTOTEST_CHECKPT(u32SbootUseTimeMs);
#endif

    printf("sboot use %ums\n", u32SbootUseTimeMs);
}


#ifdef __aeon__
void Aeon_Exception_Handler(MHAL_SavedRegisters *regs, MS_U32 vector)
{
    printf("\nException: %d\n", vector);

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

    // CPU Stay in here
    MDrv_Sys_StopCpu(ENABLE);
}
#endif

#ifdef __aeon__
extern U32 _bss_start;
extern U32 _bss_end;
#endif

#ifdef __mips__
extern U32 __bss_start;
extern U32 __bss_end;
#endif

#ifdef __arm__
extern U32 _ld_bss_start;
extern U32 _ld_bss_end;
#endif

extern U32 __heap;
extern U32 __heap_end;

void Print_BeonMemory(U32 u32StackBegin, U32 u32StackSize)
{
#ifdef __aeon__
    U32 u32BssStart = (U32)(&_bss_start);
    U32 u32BssEnd = (U32)(&_bss_end);
#endif

#ifdef __mips__
    U32 u32BssStart = (U32)(&__bss_start);
    U32 u32BssEnd = (U32)(&__bss_end);
#endif

#ifdef __arm__
    U32 u32BssStart = (U32)(&_ld_bss_start);
    U32 u32BssEnd = (U32)(&_ld_bss_end);
#endif


#if 1 // Aeon/Mips
    U32 u32StackEnd = u32StackBegin - u32StackSize;
    U32 u32FreeSize;


    printf("u32BssStart = 0x%x, u32BssEnd = 0x%x\n", u32BssStart, u32BssEnd );
    printf("u32StackEnd = 0x%x, u32StackBegin = 0x%x\n", u32StackEnd, u32StackBegin );

    u32FreeSize = ((unsigned int)&__heap_end) - ((unsigned int)&__heap);

    printf("heap_start = 0x%x, heap_end = 0x%x\n", &__heap, &__heap_end );
    printf("heap_size => %u(0x%x)\n", u32FreeSize, u32FreeSize );

    if( (&__heap_end) <= (&__heap) )
    {
        printf("## ERROR!! MMAP lyout for CPU code is not enough!!!\n");
    }
    else if (u32FreeSize < 0x4B000)
    {
        printf("## heap size is %dK under 300K!!\n", (int)u32FreeSize/1024);
    }
#endif
}

#if (ENABLE_STACK_CHECK)
#define STACK_CHECK_SIZE                4
#define STACK_END_MAGIC_ID              0x78


#define ENABLE_STACK_CHECK_NON_CACHE    0

#if(ENABLE_STACK_CHECK_NON_CACHE)
//#define STACK_CHECK_NON_CACHE_OFFSET    0x10
#endif

static BOOL s_StackChk_InitDone = 0;
static U32 s_StackChk_u32StackEndAddr_VA = 0;
static U32 s_StackChk_u32StackBeginAddr_VA = 0;

static U8* s_StackChk_pu8Data_1 = 0;
#if(ENABLE_STACK_CHECK_NON_CACHE)
static U8* s_StackChk_pu8Data_NonCache = 0;
#endif
void MDrv_StackChk_Init(U32 u32StackBeginAddr_VA, U32 u32StackSize)
{
    s_StackChk_u32StackBeginAddr_VA = u32StackBeginAddr_VA;
    s_StackChk_u32StackEndAddr_VA = u32StackBeginAddr_VA - u32StackSize;

    // Align to 4
    //s_StackChk_u32StackEndAddr_VA = (s_StackChk_u32StackEndAddr_VA+3)&0xFFFFFFFC;

    s_StackChk_pu8Data_1 = (U8*)(s_StackChk_u32StackEndAddr_VA);

#if(ENABLE_STACK_CHECK_NON_CACHE)

    U32 u32StackEnd_PA = MsOS_VA2PA(s_StackChk_u32StackEndAddr_VA);
    //printf("&u32StackEnd_PA=0x%X\n", &u32StackEnd_PA);

    // Convert to non-cache pointer
    s_StackChk_pu8Data_NonCache = (U8*) MsOS_PA2KSEG1(u32StackEnd_PA);
#endif


    U8 i;


    //MsOS_Dcache_Flush(0, 0xFFFFFFFF);
    //MsOS_FlushMemory();
    //MsOS_Dcache_Invalidate(0, 0xFFFFFFFF);

    // Init cache memory
    for( i = 0 ; i < STACK_CHECK_SIZE; i ++ )
    {
        s_StackChk_pu8Data_1[i] = STACK_END_MAGIC_ID;
    }

    MsOS_Dcache_Flush(0, 0xFFFFFFFF);
    MsOS_FlushMemory();

#if 0//(ENABLE_STACK_CHECK_NON_CACHE)
    // Init non-cache memory
    for( i = 0 ; i < STACK_CHECK_SIZE; i ++ )
    {
        s_StackChk_pu8Data_NonCache[i] = STACK_END_MAGIC_ID;
    }

    MsOS_Dcache_Flush(0, 0xFFFFFFFF);
    MsOS_FlushMemory();
#endif

    //MDrv_StackChk_PrintInfo();

    if( MDrv_StackChk_CheckFlag() )
    {
        // Error happen
        printf("\nError: StackCheck init failed!\n");
    }
    else
    {
        s_StackChk_InitDone = 1;
    }

    //MDrv_StackChk_PrintInfo();
}

void MDrv_StackChk_PrintInfo(void)
{
    printf("StackChk Info:\n");

    printf(" _u32StackEndAddr_VA  =0x%X\n", (U32)s_StackChk_u32StackEndAddr_VA);
    printf(" _u32StackBeginAddr_VA=0x%X\n", (U32)s_StackChk_u32StackBeginAddr_VA);

    printf(" _pu8Data_1       =0x%X\n", (U32)s_StackChk_pu8Data_1);
#if(ENABLE_STACK_CHECK_NON_CACHE)
    printf(" _pu8Data_NonCache=0x%X\n", (U32)s_StackChk_pu8Data_NonCache);
#endif

    U8 i;

    MsOS_Dcache_Flush(0, 0xFFFFFFFF);
    MsOS_FlushMemory();


    for( i = 0 ; i < STACK_CHECK_SIZE; i ++ )
    {
        printf("s_StackChk_pu8Data_1[%u]=%X\n", i, s_StackChk_pu8Data_1[i]);
    }

#if(ENABLE_STACK_CHECK_NON_CACHE)
    for( i = 0 ; i < STACK_CHECK_SIZE; i ++ )
    {
        printf("s_StackChk_pu8Data_NonCache[%u]=%X\n", i, s_StackChk_pu8Data_NonCache[i]);
    }
#endif

    Print_Buffer( s_StackChk_pu8Data_1-16, 0x40);

#if(ENABLE_STACK_CHECK_NON_CACHE)
    Print_Buffer( s_StackChk_pu8Data_NonCache-16, 0x40);
#endif
}

void Print_Buffer(U8* pu8Buf, U32 u32Size );
U8 MDrv_StackChk_CheckFlag(void)
{
    U8 i;
    U8 u8ErrFound = 0;

    //MDrv_StackChk_PrintInfo();

    //MsOS_Dcache_Flush(0, 0xFFFFFFFF);
    MsOS_FlushMemory();

    for( i = 0 ; i < STACK_CHECK_SIZE; i ++ )
    {
        if( s_StackChk_pu8Data_1[i] != STACK_END_MAGIC_ID )
        {
            printf("s_StackChk_pu8Data_1[%u]=%X\n", i, s_StackChk_pu8Data_1[i]);
            u8ErrFound += 1;
        }

    #if(ENABLE_STACK_CHECK_NON_CACHE)
        if( s_StackChk_pu8Data_NonCache[i] != STACK_END_MAGIC_ID )
        {
            printf("s_StackChk_pu8Data_NonCache[%u]=%X\n", i, s_StackChk_pu8Data_NonCache[i]);
            u8ErrFound += 1;
        }
    #endif
    }

    if( u8ErrFound )
    {
        printf("\nError: StackCheck: Error found!\n");
        MDrv_StackChk_PrintInfo();

        //Print_Buffer( s_StackChk_pu8Data_1-32, 0x40);
        //Print_Buffer( s_StackChk_pu8Data_NonCache-32-STACK_CHECK_SIZE, 0x40);

        //while(1){}
    }

    return u8ErrFound;
}

BOOLEAN MDrv_StackChk_IsPtrValid(void * pvPointer, U32 u32Size)
{
    U32 u32Addr = (U32)pvPointer;

    if( (u32Addr <= s_StackChk_u32StackEndAddr_VA) )
        return FALSE;

    if( (u32Addr >= s_StackChk_u32StackBeginAddr_VA) )
        return FALSE;


    u32Addr = (U32)pvPointer + u32Size;

    if( (u32Addr <= s_StackChk_u32StackEndAddr_VA) )
        return FALSE;

    if( (u32Addr >= s_StackChk_u32StackBeginAddr_VA) )
        return FALSE;

    return TRUE;
}

#endif

