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
#ifndef _AUTOTEST_H
#define _AUTOTEST_H


#include "Board.h"
#if ENABLE_AUTOTEST

#include "datatype.h"

typedef enum {
    PW_TEST_START = 0,
    ACE_PW_TEST   = PW_TEST_START,
    AUDIO_PW_TEST,
    CI_PW_TEST,
    CNI_PW_TEST,
    DEMUX_PW_TEST,
    DLC_PW_TEST,
    GE_PW_TEST,
    MS_OD_PW_TEST,
    MVF_PW_TEST,
    SUBTITLE_PW_TEST,
    TTX_PW_TEST,
    USB_PW_TEST,
    SCALER_PW_TEST,
    FILE_SYS_PW_TEST,
    HDMI_PW_TEST,
    MIU_PW_TEST,
    DMA_PW_TEST,
    GOP_PW_TEST,
    VOP_PW_TEST,
    TV_ENCODE_PW_TEST,
    VDEC_PW_TEST,
    FLASH_PW_TEST,
    TIMER_PW_TEST,
    CRC_PW_TEST,
    RTC_PW_TEST,
    MVD_PW_TEST,

    HW_IP_MAX  = 0xFF
}pw_ip_t;

typedef struct {
      U16 width;
      U16 height;
      U16 pitch;
      U16 fbFmt;
      U32 addr;
      U32 size;
}fbuf_t;

//void MDrv_PWMGT_Excute(U8 index1);
void MDrv_Autotest_Excute_Key(U8 index1);
void MDrv_Autotest_Excute_Sp(U8 index1);

#if 0 // 20150211 No use
void MDrv_PWMGT_Init(void);
void MDrv_PWMGT_Attach(U8 u8IPIndex, void (*func)(void));
#endif

void MDrv_Mheg5_Debug(void);

#define DHRY 1
#if DHRY
typedef struct record
{
    struct record *Ptr_Comp;
    U32    Discr;
    union
    {
        struct
        {
            U32 Enum_Comp;
            U32 Int_Comp;
            U8  Str_Comp[31];
        } var_1;
        struct
        {
            U32 E_Comp_2;
            U8  Str_2_Comp[31];
        } var_2;
        struct
        {
            U8  Ch_1_Comp;
            U8  Ch_2_Comp;
        } var_3;
    } variant;
} Rec_Type, *Rec_Pointer;

void dhry2(unsigned int*);
void Proc_1(Rec_Pointer Ptr_Val_Par);
void Proc_2(U32 *Int_Par_Ref);
void Proc_3(Rec_Pointer *Ptr_Ref_Par);
void Proc_4(void);
void Proc_5(void);
void Proc_6(U32 Enum_Val_Par, U32 *Enum_Ref_Par);
void Proc_7(U32 Int_1_Par_Val, U32 Int_2_Par_Val, U32 *Int_Par_Ref);
void Proc_8(U32 *Arr_1_Par_Ref, U32 Arr_2_Par_Ref[][50], U32 Int_1_Par_Val, U32 Int_2_Par_Val);
U32 Func_1(U8 Ch_1_Par_Val, U8 Ch_2_Par_Val);
BOOLEAN Func_2 (U8 *Str_1_Par_Ref, U8 *Str_2_Par_Ref);
BOOLEAN Func_3(U32 Enum_Par_Val);

void CPU_BENCHMARK_TEST(char *str_mips_dhry,char *str_aeon_dhry, char *str_mips_mmtest, char *str_aeon_mmtest);
void MBX_RECV(unsigned int *);

char *itoa(int n, char *s, int b);
char *strrev(char *str);
int _strlen(const char *string);

#endif // DHRY

#endif // #if ENABLE_AUTOTEST

#endif /*_AUTOTEST_H*/
