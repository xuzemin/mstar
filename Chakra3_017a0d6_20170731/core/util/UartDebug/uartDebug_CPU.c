
#define TEST_EXCEPTION_6    0
#if TEST_EXCEPTION_6 // Test exception 6

#include <stddef.h>
//#include <string.h>
typedef struct __attribute__((__packed__))
{
    U16 u16AudioPid:13;
    U16 u16AudStreamType:2; //0=Mpeg, 1=AC3, 2= AAC
    U16 u16IsAudLangGetinPMT:1;

    U8 u8AudLangIdx:4;
    U8 u8AudPidInPMT:1;  // if this audio pid in PMT
    U8 u8AudAc3Bsmod:3;
} MS_SOUND_TRACK_A;

typedef struct __attribute__((__packed__))
{
    U8 u8Data_ofst_0;
    U16 u16Data_ofst_1;
    U8 u8Data_ofst_3;
}  StruSon_1;

typedef struct //__attribute__((__packed__))
{
    U8 u8Data_ofst_0;
    U16 u16Data_ofst_1;
    U8 u8Data_ofst_3;
}  StruSon_2;
typedef struct __attribute__((__packed__))
{
    StruSon_1 stSon_1;
    U8 u8Data_2;
    StruSon_2 stSon_2;
}  StruMother;

StruMother s_astMother[2];

void TestExcep6_ST(MS_SOUND_TRACK_A* pstST)
{
    printf(" pstST=0x%X\n", (U32)pstST);
    printf(" ->u16AudioPid=0x%X\n", (pstST->u16AudioPid));
    printf(" ->u16AudStreamType=0x%X\n", (pstST->u16AudStreamType));
    printf(" ->u8AudPidInPMT=0x%X\n", (pstST->u8AudPidInPMT));
}

void TestExcep6_Son_1(StruSon_1* pstSon_1)
{
    printf(" pstSon_1=0x%X\n", (U32)pstSon_1);
    printf(" ->u8Data_ofst_0=0x%X\n", (pstSon_1->u8Data_ofst_0));
    printf(" ->u16Data_ofst_1=0x%X\n", (pstSon_1->u16Data_ofst_1));
    //printf(" ->u8Data_ofst_3=0x%X\n", (pstSon_1->u8Data_ofst_3));
}
void TestExcep6_Son_2(StruSon_2* pstSon_2)
{
    printf(" pstSon_2=0x%X\n", (U32)pstSon_2);
    printf(" ->u8Data_ofst_0=0x%X\n", (pstSon_2->u8Data_ofst_0));
    printf(" ->u16Data_ofst_1=0x%X\n", (pstSon_2->u16Data_ofst_1));
    //printf(" ->u8Data_ofst_3=0x%X\n", (pstSon_2->u8Data_ofst_3));
}

void TestException6(U8 u8Flag)
{
    printf("Test Exception6()\n",u8Flag);
    printf(" sizeof(StruMother)=0x%X\n", sizeof(StruMother));
    printf(" sizeof(StruSon_1)=0x%X\n", sizeof(StruSon_1));
    printf(" sizeof(StruSon_2)=0x%X\n", sizeof(StruSon_2) );

    printf(" offset(stSon_1)=0x%X\n", offsetof(StruMother, stSon_1) );
    printf(" offset(stSon_2)=0x%X\n", offsetof(StruMother, stSon_2) );


    printf(" Test 1:\n");
    printf("  &stSon_1.u16Data_ofst_1=0x%X\n", &(s_astMother[0].stSon_1.u16Data_ofst_1));
    printf("  &stSon_2.u16Data_ofst_1=0x%X\n", &(s_astMother[0].stSon_2.u16Data_ofst_1));

    printf("  stSon_1.u16Data_ofst_1=0x%X\n", s_astMother[0].stSon_1.u16Data_ofst_1);
    printf("  stSon_2.u16Data_ofst_1=0x%X\n", s_astMother[0].stSon_2.u16Data_ofst_1);


    printf(" Test 2-1:\n");
    StruSon_1* pSon_1 = &(s_astMother[0].stSon_1);
    printf("  pSon_1=0x%X\n", (U32)pSon_1);
    //printf("  ->u8Data_ofst_0=0x%X\n", (pSon_1->u8Data_ofst_0));
    printf("  ->u16Data_ofst_1=0x%X\n", (pSon_1->u16Data_ofst_1));

    printf(" Test 2-2:\n");
    TestExcep6_Son_1(pSon_1);


    printf(" Test 2-3:\n");
    StruSon_2* pSon_2 = &(s_astMother[0].stSon_2);
    printf("  pSon_2=0x%X\n", (U32)pSon_2);
    //printf("  ->u8Data_ofst_0=0x%X\n", (pSon_2->u8Data_ofst_0));
    printf("  ->u16Data_ofst_1=0x%X\n", (pSon_2->u16Data_ofst_1));

    printf(" Test 2-4:\n");
    TestExcep6_Son_2(pSon_2);


    //printf(" u16AudStreamType=0x%X\n", (s_astMother[0].stSoundTrack.u16AudioPid));

    //TestExcep6_ST(&(s_astMother[0].stSoundTrack));

}

#endif
