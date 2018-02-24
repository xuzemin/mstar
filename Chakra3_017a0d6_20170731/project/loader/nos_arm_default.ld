OUTPUT_FORMAT("elf33-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

/*STARTUP(vectors.o)*/
ENTRY(exception_vector)

/* INPUT(extras.o) */

GROUP(libgcc.a libsupc++.a  libstdc++.a)

RAM_START = 0x00000000;  
RAM_SIZE  = 0x00A00000;

RAM_START_VA = 0;
RAM_START_PA = 0;

HEAP_SIZE   = 0x50000;
STACK_SIZE  = 0x8000;

HEAD_OFFSET = 0x8000;
AP_OFFSET   = 0x9000;

/* For what?? */
_ld_vector_ram_pa_start = RAM_START_VA ;
__ram_code_start = RAM_START_VA ;

MEMORY
{
    vector :  ORIGIN = 0x00000000,     LENGTH = 32K
    head   :  ORIGIN = 0x00008000,     LENGTH = 4K
    ap     :  ORIGIN = 0x00009000,     LENGTH = 32M
}

abort = 0x00000010;

SECTIONS
{   
    . = ALIGN(4096); 
      
    .text1 :
    {   
        _readonly_start = .;
        _stext = .; 
        _ftext = .;
        _ld_vector_ram_va_start = . ;
        . = ALIGN(16);
        *vectors.o (.text*)
        *vectors.o (.rodata*)
        . = ALIGN(16);
    /*
        prog_img_info = .; KEEP (*(.prog_img_info))
        img_info = .; KEEP (*(.img_info))
        isp_info = .; KEEP (*(.isp_info))
    */
          
        . = (0x1100);
        prog_img_info = .; KEEP (*(.prog_img_info))
        
        . = (0x2000);
        img_info = .; KEEP (*(.img_info))
        
        . = (0x3000);
        isp_info = .; KEEP (*(.isp_info))
    
    } > vector


    .text2 : AT ( LOADADDR(.text1) + HEAD_OFFSET)
    {
        . = ALIGN(16);
        _ld_ap_ram_pa_start = . ; 
        _ld_ap_ram_va_start = . ;
        reset_vector = .;
        *head.o (.text*)
        *head.o (.rodata*)
        . = ALIGN(16);
    } > head

    .text3 : AT ( LOADADDR(.text1) + AP_OFFSET)
    {
        *(.text*)
        *(.rodata*)
    } > ap

    text3_end = .;

    . = ALIGN(4096); _readonly_end = .;

    .data ALIGN (0x40): 
    {
        *(.data)
    } > ap

    .bss ALIGN (0x40): 
    {
        _ld_bss_start = .;
       *(.bss)
    } > ap

    _ld_bss_end = .;
    _etext = .; PROVIDE (etext = .);
    
    .fini ALIGN (0x40) : { . = .; KEEP (*(.fini)) } > ap =0
    .rodata ALIGN (0x40) : { . = .; *(.rodata) *(.rodata.*) } > ap
    .rodata1 ALIGN (0x40) : { . = .; *(.rodata1) *(.rodata1.*) } > ap __ram_code_end = .;
/*    
    . = ALIGN(4096); _readonly_end = .;
*/    
    .tspdat ALIGN (0x10) : { . = .; *(.tspdat) } > ap
    .data1 ALIGN (0x40) : AT ((LOADADDR (.data) + SIZEOF (.data) + 0x40 - 1) & ~ (0x40 - 1)) { . = .; *(.data1) *(.data1.*) } > ap
    _gp = ALIGN(16) + 0x7ff0;
    
    .sdata ALIGN (0x8) : { __SDATA_START__ = ABSOLUTE(.); . = .; *(.sdata) *(.sdata.*) *(.gnu.linkonce.s*) } > ap
    .lit8 ALIGN (0x8) : { . = .; *(.lit8) _MY_MARK = .; LONG(0xAABBCCDD) LONG(0); } > ap
    
     _fbss = .; .sbss ALIGN (0x40) : { . = .; *(.dynsbss) *(.sbss) *(.sbss.*) *(.scommon) } > ap
     
    /* Stack is 16384-byte, ISR and user uses the same stack */

    . = ALIGN (64);
    
    _ld_irq_stack_end = . ; . = . + STACK_SIZE; _ld_irq_stack_start = . ;
    _ld_fiq_stack_end = . ; . = . + STACK_SIZE; _ld_fiq_stack_start = . ;
    _ld_svc_stack_end = . ; . = . + STACK_SIZE; _ld_svc_stack_start = . ;
    
    _stack_end = . ; . = . + STACK_SIZE; __stack_begin = . ; 

    /* for sbrk.c */
    . = ALIGN (64);
     __heap = .; . = RAM_START_VA + RAM_SIZE; __heap_end = RAM_START_VA + RAM_SIZE;
    . = ALIGN (64);
    . = __heap_end ;

/*
    _ld_irq_stack_end = . ; . = . + STACK_SIZE; _ld_irq_stack_start = . ;
    _ld_fiq_stack_end = . ; . = . + STACK_SIZE; _ld_fiq_stack_start = . ;
    _ld_svc_stack_end = . ; . = . + STACK_SIZE; _ld_svc_stack_start = . ;
*/

    _ld_ap_ram_va_end = .; 

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx*)
        _ld_MEMORY_ram_end = .;
        _ld_bootram_RAM_end = .;
    } > ap
    __exidx_end = .;

    RISC32_DCACHE_SIZE = 4096;
    RISC32_DCACHE_LINE_SIZE = 16;
    RISC32_DCACHE_WAYS = 2;
    
}

