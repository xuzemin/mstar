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


#ifdef __AEONR2__


#include "risc32_spr.h"
#include "mhal_arch.h"
#include "r2_backtrace.h"


typedef struct symbol_tag {
	unsigned long addr; /* address of function */
	unsigned long str;  /* string address before initialized */
	unsigned long size; /* size of function */
} symbol_t;

typedef struct symbol_tag2 {
	unsigned long addr; /* address of function */
} symbol_t2;


typedef struct symbol_tag3 {
	unsigned long addr; /* address of function */
	unsigned long str;  /* string address before initialized */
} symbol_t3;

/*
 * These will be re-linked against their real values
 * during the second link stage.
 */
extern const unsigned long sym_type __attribute__((weak));
extern const unsigned long s_text __attribute__((weak));
extern const unsigned long e_text __attribute__((weak));
extern const unsigned long s_iqmem __attribute__((weak));
extern const unsigned long e_iqmem __attribute__((weak));
extern const unsigned long text_syms_str __attribute__((weak));
extern const unsigned long iqmem_syms_str __attribute__((weak));
extern const unsigned long text_syms_num __attribute__((weak));
extern const unsigned long iqmem_syms_num __attribute__((weak));
extern const unsigned long text_syms __attribute__((weak));
extern const unsigned long iqmem_syms __attribute__((weak));
extern const unsigned long bt_magic_number __attribute__((weak));

void r2_bt_init(void)
{
	printf("magic number: 0x%x\n",bt_magic_number);
	printf("sym_type: 0x%x\n",sym_type);
	printf("s_text:0x%x, e_text:0x%x\n", s_text, e_text);
	printf("text_syms_str:0x%x\n", &text_syms_str);
	printf("text_syms_num:%d\n", text_syms_num);
	printf("s_iqmem:0x%x, e_iqmem:0x%x\n", s_iqmem, e_iqmem);
	printf("iqmem_syms_str:0x%x\n", &iqmem_syms_str);
	printf("iqmem_syms_num:%d\n", iqmem_syms_num);
	printf("iqmem_syms:0x%x\n", &iqmem_syms);
}

unsigned long r2_bt_lookup(unsigned long addr)
{
	unsigned long i;
	unsigned long prev = 0;
	unsigned long sym_addr = 0;
	unsigned sym = 0;

	if (bt_magic_number != R2_BT_MAGIC_NUMBER)
	{
		return NULL;
	}
	if (text_syms_num) {
		if (addr >= s_text &&
		    addr < e_text) {
			for (i = 0; i < text_syms_num; i++) {
				if(sym_type == SYM_OFF)
				{
					sym = (unsigned long) (&((symbol_t2 *)&text_syms)[i]);
					sym_addr=((symbol_t2*) sym)->addr;
				}
                else if(sym_type & SYM_SIZE_ON)
				{
					sym = (unsigned long) (&((symbol_t *)&text_syms)[i]);
					sym_addr = ((symbol_t*) sym)->addr;
				}
				else if(sym_type & SYM_STR_ON)
				{
					sym = (unsigned long) (&((symbol_t3 *)&text_syms)[i]);
					sym_addr=((symbol_t3*) sym)->addr;
				}

				if (addr >=  sym_addr) {
					prev = sym;
					continue;
				} else {
					return prev;
				}
			}
		}
	}
	if (iqmem_syms_num) {
		if (addr >= s_iqmem &&
		    addr < e_iqmem) {
			for (i = 0; i < iqmem_syms_num; i++) {
				if(sym_type == SYM_OFF)
				{
					sym = (unsigned long) (&((symbol_t2 *)&iqmem_syms)[i]);
					sym_addr=((symbol_t2*) sym)->addr;
				}else if(sym_type & SYM_SIZE_ON)
				{
					sym = (unsigned long) (&((symbol_t *)&iqmem_syms)[i]);
					sym_addr=((symbol_t*) sym)->addr;
				}
				else if(sym_type & SYM_STR_ON)
				{
					sym = (unsigned long) (&((symbol_t3 *)&iqmem_syms)[i]);
					sym_addr=((symbol_t3*) sym)->addr;
				}

				if (addr >=  sym_addr) {
					prev = sym;
					continue;
				} else {
					return prev;
				}
			}
		}
	}

	return NULL;
}
// insn_size = insn_length_idx[(opcode first byte)>>5]
static const int insn_length_idx[8] = { 3, 3, 3, 3, 2, 4, 4, 4 };

static inline void fetch_insn(unsigned long addr, char *insn)
{
	char *p;
	p = (char *)addr;
	int i;

	for (i = 0; i < 4; i++) {
		insn[i] = *(p + i);
	}
}

/*
 * sym: current function
 * pc_addr: pc addr of current function
 * stack_addr: current stack addr
 * prev_pc_addr: pc addr of prev frame
 * prev_stack_addr: stack addr of prev frame
 */
static void find_prev_frame(symbol_t *sym,
	unsigned long pc_addr,
	unsigned long stack_addr,
	unsigned long *prev_pc_addr,
	unsigned long *prev_stack_addr)
{
	unsigned long addr;
	unsigned char insn[4]={0}; // fix coverity 166078
	int insn_size;
	unsigned long instruction;
	int prev_pc_found = 0;
	int prev_stack_found = 0;
	int rD,rA;
	unsigned int off;

	addr = sym->addr;
	while (addr < pc_addr && !prev_pc_found ) {
		fetch_insn(addr, (char *)insn);
		#ifdef __AEONR2__
		insn_size = insn_length_idx[insn[0] >> 5];
		instruction =
			(insn[0] << 24) |
			(insn[1] << 16) |
			(insn[2] << 8) |
			(insn[3]);
		instruction=instruction>>(32-insn_size*8);
		switch (insn[0] >> 2) {
		#elif defined __AEON1__
		insn_size = 4;
		instruction =
			(insn[3] << 24) |
			(insn[2] << 16) |
			(insn[1] << 8) |
			(insn[0]);
		instruction=instruction>>(32-insn_size*8);
		switch (insn[3] >> 2) {
		#endif
		#ifdef __AEONR2__
		case OP_R2_BT_ADDI_PFX:
			if (prev_stack_found == 0) {
				rD = (instruction >> 5) & 0x1f;
				if (rD == REG_R1) {
					off = instruction & 0x1f;
					if (off & 0x10) {
						off |= 0xffffffe0;
						off = ~off;
						off += 1;
						prev_stack_found = 1;
						*prev_stack_addr = stack_addr + off;
					}
				}
			}
			break;
		case OP_R2_BN_ADDI_PFX:
			if (prev_stack_found == 0) {
				rD = (instruction >> 13) & 0x1f;
				if (rD == REG_R1) {
					rA = (instruction >> 8) & 0x1f;
					if (rA == REG_R1) {
						off = instruction & 0xff;
						if (off & 0x80) {
							off |= 0xffffff00;
							off = ~off;
							off += 1;
							prev_stack_found = 1;
							*prev_stack_addr = stack_addr + off;
						}
					}
				}
			}
			break;
		case OP_R2_BG_ADDI_PFX:
			if (prev_stack_found == 0) {
				rD = (instruction >> 21) & 0x1f;
				if (rD == REG_R1) {
					rA = (instruction >> 16) & 0x1f;
					if (rA == REG_R1) {
						off = instruction & 0xffff;
						if (off & 0x8000) {
							off |= 0xffff0000;
							off = ~off;
							off += 1;
							prev_stack_found = 1;
							*prev_stack_addr = stack_addr + off;
						}
					}
				}
			}
			break;
		case OP_R2_ENTRI_PFX:
			if (prev_stack_found == 0) {
				if ((instruction & 0x1f) == OP_R2_ENTRI_SUB) {
					off = (instruction >> 14) & 0xf;
					off += (instruction >> 5) & 0x1ff;
					off *= 4;
					prev_stack_found = 1;
					prev_pc_found = 1;
					*prev_stack_addr = stack_addr + off;
					*prev_pc_addr = *((unsigned long *)(*prev_stack_addr-4));
				}
			}
			break;
		case OP_R2_BN_SW_PFX:
			if ((instruction & 0x3) == 0) {
				if ( (((instruction >> 13) & 0x1f) == REG_R9) &&
				     (((instruction >> 8)  & 0x1f) == REG_R1) ) {
					off = ((instruction >>2) & 0x3f);
					if (off & 0x20) {
						off |= 0xffffffd0;
						off = ~off;
						off += 1;
						off = off << 2;
						off = stack_addr - off;
						prev_pc_found = 1;
						*prev_pc_addr = *((unsigned long *)off);
					} else {
						off = off << 2;
						off = stack_addr + off;
						prev_pc_found = 1;
						*prev_pc_addr = *((unsigned long *)off);
					}
				}
			}
			break;
		case OP_R2_BG_SW_PFX:
			if ((instruction & 0x3) == 0) {
				if ( (((instruction >> 21) & 0x1f) == REG_R9) &&
				     (((instruction >> 16)  & 0x1f) == REG_R1) ) {
					off = (instruction >>2 ) & 0x3fff;
					if (off & 0x2000) {
						off |= 0xffffd000;
						off = ~off;
						off += 1;
						off = off << 2;
						off = stack_addr - off;
						prev_pc_found = 1;
						*prev_pc_addr = *((unsigned long *)off);
					} else {
						off = off << 2;
						off = stack_addr + off;
						prev_pc_found = 1;
						*prev_pc_addr = *((unsigned long *)off);
					}
				}
			}
			break;
		#elif defined __AEON1__
		case OP_AEON_ADDI_PFX:
			if (prev_stack_found == 0) {
				rD = (instruction >> 21) & 0x1f;
				if (rD == REG_R1) {
					rA = (instruction >> 16) & 0x1f;
					if (rA == REG_R1) {
						off = instruction & 0xffff;
						if (off & 0x8000) {
							off |= 0xffff0000;
							off = ~off;
							off += 1;
							prev_stack_found = 1;
							*prev_stack_addr = stack_addr + off;
						}
					}
				}
			}
			break;

		case OP_AEON_SW_PFX:
			{
				if ( (((instruction >> 11) & 0x1f) == REG_R9) &&
				     (((instruction >> 16)  & 0x1f) == REG_R1) ) {
					off = (((instruction >> 21)  & 0x1f)<< 11 | (instruction& 0x7ff ));
					if (off & 0x8000) {
						off |= 0xffff0000;
						off = ~off;
						off += 1;
						off = stack_addr - off;
						prev_pc_found = 1;
						*prev_pc_addr = *((unsigned long *)off);
					} else {
						off = stack_addr + off;
						prev_pc_found = 1;
						*prev_pc_addr = *((unsigned long *)off);
					}
				}
			}
			break;

		#endif
		default:
			break;
		} // switch

		/* next insn */
		addr += insn_size;
	}

	if (prev_pc_found == 0) {
		*prev_pc_addr = 0xffffffff;
	}
	if (prev_stack_found == 0) {
		*prev_stack_addr = 0xffffffff;
	}
}

static void __r2_bt(unsigned long pc_addr, unsigned long stack_addr)
{
	symbol_t *sym;
	unsigned long prev_pc_addr;
	unsigned long prev_stack_addr;


    //printf("__r2_bt(pc_addr=0x%X,stack_addr=0x%X)\n", pc_addr, stack_addr);

	sym = (symbol_t *) r2_bt_lookup(pc_addr);

    //printf(" sym=0x%X\n", sym);

	if (sym)
    {
		if((pc_addr >= s_text) && (pc_addr< e_text) && (sym_type & SYM_STR_ON))
			printf("name:%s, r9:0x%x\n", (char *)(sym->str + (unsigned long)(&text_syms_str)), pc_addr);
		else if (pc_addr >= s_iqmem && pc_addr < e_iqmem && (sym_type & SYM_STR_ON))
			printf("name:%s, r9:0x%x\n", (char *)(sym->str + (unsigned long)(&iqmem_syms_str)), pc_addr);
		else
        {
			printf("# r9:0x%x\n", pc_addr);
            //printf("# PC:0x%x\n", pc_addr);
            printf(" aeon-elf-addr2line -e AP.elf -f 0x%x\n", pc_addr);
        }

		/*
		 * find the pc and stack addr of previous frame
		 * by decoding instructions from sym->addr ~ pc_addr
		 */
		find_prev_frame(sym, pc_addr, stack_addr,
			&prev_pc_addr, &prev_stack_addr);

		if (prev_pc_addr == 0xffffffff) {
			/* cannot find the return addr */
			return;
		}
		if (prev_stack_addr == 0xffffffff) {
			/* no allocated stack */
			prev_stack_addr = stack_addr;
		}
		/* do recursive backtrace */
		__r2_bt(prev_pc_addr, prev_stack_addr);
	}
}

/*
 * first level backtrace
 */
void r2_bt(unsigned long pc_addr,  unsigned long stack_addr, unsigned long lr)
{
	symbol_t *sym;
	unsigned long prev_pc_addr;
	unsigned long prev_stack_addr;
	sym = (symbol_t *) r2_bt_lookup(pc_addr);
	if (sym) {
		if(pc_addr >= s_text && pc_addr<=e_text && (sym_type & SYM_STR_ON))
			printf("name:%s, r9:0x%x\n", (char *)(sym->str + (unsigned long) (&text_syms_str)), pc_addr);
		else if (pc_addr >= s_iqmem && pc_addr <= e_iqmem && (sym_type & SYM_STR_ON))
			printf("name:%s, r9:0x%x\n", (char *)(sym->str + (unsigned long)(&iqmem_syms_str)), pc_addr);
		else
        {
		    printf("# r9:0x%x\n", pc_addr);
            printf(" aeon-elf-addr2line -e AP.elf -f 0x%x\n", pc_addr);
        }

		/*
		 * find the stack addr of previous frame
		 * by decoding instructions from sym->addr ~ pc_addr
		 */
		find_prev_frame(sym, pc_addr, stack_addr,
			&prev_pc_addr, &prev_stack_addr);
		if (prev_pc_addr == 0xffffffff) {
			/* for some cases, there is no LR in leaf function */
			/* trigger exception and cannot find the return addr */
			prev_pc_addr = lr;
		}
		if (prev_stack_addr == 0xffffffff) { // leaf function
			prev_stack_addr = stack_addr;
		}
		__r2_bt(prev_pc_addr, prev_stack_addr);
	}
}

int r2_online_bt(void)
{
	unsigned long stack;
	unsigned long pc;
	asm volatile("b.ori   %0,r1,0x0\n\t" : "=r"(stack) : );
	asm volatile("b.mfspr %0,r0, %1\n\t" : "=r"(pc) : "I"(SPR_NPC)  );
	printf("\n#******* r2_online_bt start *******\n");
	/*
	  try to backtrace from r2_online_bt function,
	  and it will try to backtrace from r2_online_bt to r2_online_bt+0x10 in first stage.
	  Be aware, the value of (r2_online_bt+0x10) is within r2_online_bt function.
	*/
    __r2_bt( pc, stack);
	printf("\n#******* r2_online_bt end ******\n");
	return 0;
}

int r2_online_except_bt(int stack,int pc, int lr)
{
    printf("\n#****** r2_online_except_bt start ******\n");
    /*
          try to backtrace from r2_online_except_bt function,
          and it will try to backtrace from r2_online_except_bt to r2_online_except_bt+0x10 in first stage.
          Be aware, the value of (r2_online_except_bt+0x10) is within r2_online_except_bt function.
        */
    r2_bt(pc, stack, lr);
    printf("\n#****** r2_online_except_bt end ******\n");
    return 0;
}

#endif

