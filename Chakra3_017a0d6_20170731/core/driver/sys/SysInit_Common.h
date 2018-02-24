
#if((CHIP_FAMILY_TYPE == CHIP_FAMILY_WHISKY)\
  ||(CHIP_FAMILY_TYPE == CHIP_FAMILY_MILAN)\
   )
    #define ENABLE_STACK_CHECK  1
#else
    #define ENABLE_STACK_CHECK  0
#endif


#if (ENABLE_STACK_CHECK)
void MDrv_StackChk_Init(U32 u32StackBeginAddr_VA, U32 u32StackSize);
U8 MDrv_StackChk_CheckFlag(void);
BOOLEAN MDrv_StackChk_IsPtrValid(void * pvPointer, U32 u32Size);
void MDrv_StackChk_PrintInfo(void);

#define CHECK_STACK()   do{ \
    if( MDrv_StackChk_CheckFlag() )\
    {\
        PRINT_CURRENT_LINE();\
        printf("\nError: Stack is overflow!!\n"); \
        MDrv_Sys_StopCpu(1); \
    }\
} while(0)

#else
    #define CHECK_STACK()
#endif


typedef enum
{
    STOP_CPU__WHILE_1_ONLY          = 0,
    STOP_CPU__WHILE_1_AND_WDT_STOP  = 1,

} EnuStopCpuMode;

void MDrv_Sys_StopCpu(U8 u8Flag);

void MDrv_SysInit_CheckSbootUseTime(void);

void Print_BeonMemory(U32 u32StackBegin, U32 u32StackSize);


