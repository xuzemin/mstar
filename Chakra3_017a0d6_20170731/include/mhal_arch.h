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
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __MHAL_ARCH_H__
#define __MHAL_ARCH_H__

/// @file mhal_arch.h
///
/// @brief MStar HAL for risc32 architecture
/// @par Example: register handler for trap exception
/// @code
/// void trap_isr(MHAL_SavedRegisters *regs, U32 data);
/// mhal_exception_attach(E_EXCEPTION_TRAP, trap_isr, 0 /* data pass to isr */);
/// @endcode
///
/// @par Example: ciritical section for interrupt
/// @code
/// // method 1 (suggested)
/// mhal_interrupt_lock();
/// // ... critical section ...
/// mhal_interrupt_unlock();
///
/// // method 2
/// int old = mhal_interrupt_disable();
/// // ... critical section ...
/// mhal_interrupt_restore(old);
/// @endcode

#ifdef LIBPRANA
#include "risc32_spr.h"
#include "risc32_util.h"
#endif

#if defined (__mips__)

#ifdef CHIP_FAMILY_TYPE
#include "chiptype.h"
#if (CHIP_FAMILY_TYPE == CHIP_FAMILY_S7)
#define NONCACHABLE(_x_)    ((_x_) | 0xC0000000)
#else
/// convert address to corresponding noncacheable address
#define NONCACHABLE(_x_)    ((_x_) | 0xA0000000)
#endif
#endif

#include "datatype.h"

typedef enum {
    E_EXCEPTION_DATA_TLBERROR_ACCESS = 1,    // TLB modification exception
    E_EXCEPTION_DATA_TLBMISS_ACCESS,         // TLB miss (Load or IFetch)
    E_EXCEPTION_DATA_TLBMISS_WRITE,          // TLB miss (Store)
    E_EXCEPTION_DATA_UNALIGNED_ACCESS,       // Address error (Load or Ifetch)
    E_EXCEPTION_DATA_UNALIGNED_WRITE,        // Address error (store)
    E_EXCEPTION_CODE_ACCESS,                 // Bus error (Ifetch)
    E_EXCEPTION_DATA_ACCESS,                 // Bus error (data load or store)
    E_EXCEPTION_SYSTEM_CALL,                 // System call
    E_EXCEPTION_INSTRUCTION_BP,              // Break point
    E_EXCEPTION_ILLEGAL_INSTRUCTION,         // Reserved instruction
    E_EXCEPTION_COPROCESSOR,                 // Coprocessor unusable
    E_EXCEPTION_OVERFLOW,                    // Arithmetic overflow
    E_EXCEPTION_RESERVED_13,                 // Reserved
    E_EXCEPTION_DIV_BY_ZERO,                 // Division-by-zero [reserved vector]
    E_EXCEPTION_FPU,                         // Floating point exception
    E_EXCEPTION_MAX = E_EXCEPTION_FPU,
} MHAL_EXCEPTION_TYPE;

typedef enum {
    E_INTERRUPT_02 = 0,
    E_INTERRUPT_03,
    E_INTERRUPT_04,
    E_INTERRUPT_05,
    E_INTERRUPT_06,
    E_INTERRUPT_07,
} MHAL_INTERRUPT_TYPE;

// Aliases for interrupt number
#define E_INTERRUPT_FIQ         E_INTERRUPT_03
#define E_INTERRUPT_IRQ         E_INTERRUPT_02
#define E_INTERRUPT_TICK_TIMER  E_INTERRUPT_07
#define E_INTERRUPT_MAX         E_INTERRUPT_07
#define E_EXCEPTION_TRAP        E_EXCEPTION_RESERVED_13

typedef struct
{
    // These are common to all saved states
    unsigned long    d[32];          /* Data regs                    */
    unsigned long    hi;             /* hi word of mpy/div reg       */
    unsigned long    lo;             /* lo word of mpy/div reg       */

    // The status register contains the interrupt-enable bit which needs
    // to be preserved across context switches.
    unsigned long    sr;             /* Status Reg                   */

    // These are only saved for exceptions and interrupts
    unsigned long    vector;         /* Vector number                */
    unsigned long    pc;             /* Program Counter              */

    // These are only saved for exceptions, and are not restored
    // when continued.
    unsigned long    cause;          /* Exception cause register     */
    unsigned long    badvr;          /* Bad virtual address reg      */

} MHAL_SavedRegisters;

#endif

#ifdef __aeon__

#ifdef CHIP_FAMILY_TYPE
#include "chiptype.h"
#if ((CHIP_FAMILY_TYPE == CHIP_FAMILY_S7)||(CHIP_FAMILY_TYPE == CHIP_FAMILY_U3))
#define NONCACHABLE(_x_)    ((_x_) | 0xC0000000)
#else
/// convert address to corresponding noncacheable address
#define NONCACHABLE(_x_)    ((_x_) | 0x80000000)
#endif
#endif

#include "datatype.h"

/// exception type for risc32
typedef enum {
    E_EXCEPTION_BUS_ERROR = 2,
    E_EXCEPTION_DATA_PAGE_FAULT,
    E_EXCEPTION_INSTRUCTION_PAGE_FAULT,
    E_EXCEPTION_TICK_TIMER,             ///< tick timer, do not use directly
    E_EXCEPTION_UNALIGNED_ACCESS,
    E_EXCEPTION_ILLEGAL_INSTRUCTION,
    E_EXCEPTION_EXTERNAL_INTERRUPT,     ///< external interrupt, do not use directly
    E_EXCEPTION_DTLB_MISS,
    E_EXCEPTION_ITLB_MISS,
    E_EXCEPTION_RANGE,
    E_EXCEPTION_SYSCALL,                ///< caused by l.sys
    E_EXCEPTION_RESERVED,
    E_EXCEPTION_TRAP,                   ///< caused by l.trap
    E_EXCEPTION_MAX = E_EXCEPTION_TRAP,
} MHAL_EXCEPTION_TYPE;

/// interrupt type for PIC on external interrupt exception including tick_timer
typedef enum {
    E_INTERRUPT_TICK_TIMER, //< risc32 builtin tick timer
    E_INTERRUPT_00 = 1,     //< PIC interrupt start from 1 for handler performance
    E_INTERRUPT_01,
    E_INTERRUPT_02,
    E_INTERRUPT_03,
    E_INTERRUPT_04,
    E_INTERRUPT_05,
    E_INTERRUPT_06,
    E_INTERRUPT_07,
    E_INTERRUPT_08,
    E_INTERRUPT_09,
    E_INTERRUPT_10,
    E_INTERRUPT_11,
    E_INTERRUPT_12,
    E_INTERRUPT_13,
    E_INTERRUPT_14,
    E_INTERRUPT_15,
    E_INTERRUPT_16,
    E_INTERRUPT_17,
    E_INTERRUPT_18,
    E_INTERRUPT_19,
    E_INTERRUPT_20,
    E_INTERRUPT_21,
    E_INTERRUPT_22,
    E_INTERRUPT_23,
    E_INTERRUPT_24,
    E_INTERRUPT_25,
    E_INTERRUPT_26,
    E_INTERRUPT_27,
    E_INTERRUPT_28,
    E_INTERRUPT_29,
    E_INTERRUPT_30,
    E_INTERRUPT_31,
} MHAL_INTERRUPT_TYPE;

// Aliases for interrupt number
#define E_INTERRUPT_FIQ         E_INTERRUPT_02
#define E_INTERRUPT_IRQ         E_INTERRUPT_03
#define E_INTERRUPT_UART        E_INTERRUPT_19
#define E_INTERRUPT_MAX         E_INTERRUPT_31

/// task context used for context switch
typedef struct
{
    unsigned long   r1;         ///< stack pointer
    unsigned long   r2;
    unsigned long   r3;         ///< parameter 0
    unsigned long   r9;         ///< link register
    unsigned long   r10;        ///< frame pointer
    unsigned long   r12;
    unsigned long   r14;
    unsigned long   r16;
    unsigned long   r18;
    unsigned long   r20;
    unsigned long   r22;
    unsigned long   r24;
    unsigned long   r26;
    unsigned long   r28;
    unsigned long   r30;
    unsigned long   sr;
} MHAL_Context;

/// interrupt/exception context
typedef struct
{
    unsigned long   r[32];          ///< GPR registers
#ifdef __AEONR2__
    unsigned long   machi2;          // High and low words of
#endif
    unsigned long   machi;          // High and low words of
    unsigned long   maclo;          //   multiply/accumulate reg

    // These are only saved for exceptions and interrupts
    int             vector;         ///< vector number
    int             sr;             ///< status register
    unsigned long   pc;             ///< program counter

    // Saved only for exceptions, and not restored when continued:
    // Effective address of instruction/data access that caused exception
    unsigned long   eear;           ///< exception effective address
} MHAL_SavedRegisters;

#endif


#if defined(__aeon__) || defined(__mips__)
/// interrupt service routine prototype
typedef void (*mhal_isr_t)(MHAL_SavedRegisters *regs, U32 vector);
#endif

MST_BEGIN_DECL

/////////////////////////////////////////////////////////////////////////////
/// @brief register ISR of exception
/// @param <IN>     \b expt_num     : exception type
/// @param <IN>     \b isr          : exception interrupt service routine
/// @param <IN>     \b data         : user data will be passed to ISR
/// @see   mhal_exception_detach
/////////////////////////////////////////////////////////////////////////////
void mhal_exception_attach(MHAL_EXCEPTION_TYPE expt_num, mhal_isr_t isr, U32 data);

/////////////////////////////////////////////////////////////////////////////
/// @brief unregister ISR of exception
/// @param <IN>     \b expt_num     : exception type
/// @see   mhal_exception_attach
/////////////////////////////////////////////////////////////////////////////
void mhal_exception_detach(MHAL_EXCEPTION_TYPE expt_num);

/////////////////////////////////////////////////////////////////////////////
/// @brief disable interrupt controller and timer interrupt
/// @return old status
/// @see   mhal_interrupt_restore
/// @see   mhal_interrupt_enable
/////////////////////////////////////////////////////////////////////////////
int  mhal_interrupt_disable(void);

/////////////////////////////////////////////////////////////////////////////
/// @brief enable interrupt controller and timer interrupt
/// @see   mhal_interrupt_disable
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_enable(void);

/////////////////////////////////////////////////////////////////////////////
/// @brief enable interrupt controller and timer interrupt
/// @see   mhal_interrupt_disable
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_restore(int old);

/////////////////////////////////////////////////////////////////////////////
/// mask a source on interrupt controller
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_mask(MHAL_INTERRUPT_TYPE intr_num);

/////////////////////////////////////////////////////////////////////////////
/// unmask a source on interrupt controller
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_unmask(MHAL_INTERRUPT_TYPE intr_num);

/////////////////////////////////////////////////////////////////////////////
/// mask all interrupt sources on interrupt controller
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_mask_all(void);

/////////////////////////////////////////////////////////////////////////////
/// lock interrupt, mhal_interrupt_lock() and mhal_interrupt_unlock()
/// should be used in pair, and can be nested.
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_lock(void);

/////////////////////////////////////////////////////////////////////////////
/// unlock interrupt
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_unlock(void);

/////////////////////////////////////////////////////////////////////////////
/// @brief register ISR of interrupt contoller
/// @param <IN>     \b expt_num     : interrupt type
/// @param <IN>     \b isr          : interrupt service routine
/// @param <IN>     \b data         : user data will be passed to ISR
/// @see   mhal_interrupt_detach
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_attach(MHAL_INTERRUPT_TYPE intr_num, mhal_isr_t isr, U32 data);

/////////////////////////////////////////////////////////////////////////////
/// @brief unregister ISR of interrupt controller
/// @param <IN>     \b expt_num     : interrupt type
/// @see   mhal_interrupt_attach
/////////////////////////////////////////////////////////////////////////////
void mhal_interrupt_detach(MHAL_INTERRUPT_TYPE intr_num);

/////////////////////////////////////////////////////////////////////////////
/// please note original variables or parameters in current stack frame will be lost
/// @brief set stack of current context
/// @param <IN>     \b stack:   stack pointer (high address)
/////////////////////////////////////////////////////////////////////////////
void mhal_stack_init(void *stack);

/////////////////////////////////////////////////////////////////////////////
/// @brief flush dcache
/// @param <IN>     \b u32Base: memory region base address
/// @param <IN>     \b u32Size: memory region size
/////////////////////////////////////////////////////////////////////////////
void mhal_dcache_flush(U32 u32Base, U32 u32Size);

/// task main function prototype
typedef int (mhal_task_func)(int arg);

#if defined (__aeon__)

/////////////////////////////////////////////////////////////////////////////
/// @brief setup context structure for task creation
/// @param <IN>     \b stkptr:  stack pointer (bottom: low address)
/// @param <IN>     \b stklen:  stack size
/// @param <IN>     \b start:   task main function
/// @param <IN>     \b arg:     argument for task
/////////////////////////////////////////////////////////////////////////////
MHAL_Context *mhal_context_setup(unsigned long *stkptr, int stklen, mhal_task_func start, int arg);

/////////////////////////////////////////////////////////////////////////////
/// @brief switch to new context and save current context to stack
/// @param <IN>     \b pNextCtx:        new context's stack pointer to context
/// @param <IN>     \b pSavedCtxPtr:    pointer to variable that is used to store
///                                     the pointer of current tack context
/////////////////////////////////////////////////////////////////////////////
void mhal_context_switch(MHAL_Context *pNextCtx, MHAL_Context **pSaveCtxPtr);

/////////////////////////////////////////////////////////////////////////////
/// @brief switch to new context
/// @param <IN>     \b pNextCtx:        new context's stack pointer to context
/////////////////////////////////////////////////////////////////////////////
void mhal_context_load(MHAL_Context *pNextCtx);

#endif

MST_END_DECL

#endif /* __MHAL_ARCH_H__ */
