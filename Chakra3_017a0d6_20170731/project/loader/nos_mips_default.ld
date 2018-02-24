OUTPUT_FORMAT("elf32-tradlittlemips")


OUTPUT_ARCH(mips)

STARTUP(vectors.o)
ENTRY(reset_vector)

/* INPUT(extras.o) */

GROUP(libgcc.a libsupc++.a  libstdc++.a)

RAM_START = 0x803B0000;
RAM_SIZE = 0x2B0000;

MEMORY
{
    ram : ORIGIN = 0x803B0180, LENGTH = 0x01fffe80 /* 32MB */
}

SECTIONS
{
    .rom_vectors : { __ram_code_start = .; KEEP(*(.other_vector)) . = . + 0x80; . = ALIGN (0x100); KEEP (*(.reset_vector))} > ram
    . = ALIGN(4096); _readonly_start = .;
    .prog_img_info 0x803B1100 : { prog_img_info = .; KEEP (*(.prog_img_info)) } > ram
    .img_info 0x803B2000 : { img_info = .; KEEP (*(.img_info)) } > ram /* for image information data */               	
    .isp_info 0x803B3000 : { isp_info = .; KEEP (*(.isp_info)) } > ram /* for isp tool WP table information data */             				
    .text ALIGN (0x40) : { _stext = .; _ftext = . ; *(.text) *(.text.*) *(.stub) } > ram =0 _etext = .; PROVIDE (etext = .);
    .fini ALIGN (0x40) : { . = .; KEEP (*(.fini)) } > ram =0
    .rodata ALIGN (0x40) : { . = .; *(.rodata) *(.rodata.*) } > ram
    .rodata1 ALIGN (0x40) : { . = .; *(.rodata1) *(.rodata1.*) } > ram  __ram_code_end = .;
    . = ALIGN(4096); _readonly_end = .;
    .tspdat ALIGN (0x10) : { . = .; *(.tspdat) } > ram
    .data ALIGN (0x40) : AT ((LOADADDR (.tspdat) + SIZEOF (.tspdat) + 0x40 - 1) & ~ (0x40 - 1)) { __ram_data_start = ABSOLUTE (.); _fdata = . ; *(.data) *(.data.*) *( .2ram.*) . = ALIGN (8); SORT(CONSTRUCTORS) } > ram __rom_data_start = LOADADDR(.data);
    .data1 ALIGN (0x40) : AT ((LOADADDR (.data) + SIZEOF (.data) + 0x40 - 1) & ~ (0x40 - 1)) { . = .; *(.data1) *(.data1.*) } > ram
    _gp = ALIGN(16) + 0x7ff0;
    .sdata ALIGN (0x8) : { __SDATA_START__ = ABSOLUTE(.); . = .; *(.sdata) *(.sdata.*) *(.gnu.linkonce.s*) } > ram
    .lit8 ALIGN (0x8) : { . = .; *(.lit8) _MY_MARK = .; LONG(0xAABBCCDD) LONG(0); } > ram
    __bss_start = .; _fbss = .; .sbss ALIGN (0x40) : { . = .; *(.dynsbss) *(.sbss) *(.sbss.*) *(.scommon) } > ram
    .bss ALIGN (0x40) : { *(.dynbss) *(.bss) *(.bss.*) *(COMMON) *(.gnu.linkonce.b.*) } > ram __bss_end = .;
    /* Stack is 16384-byte, ISR and user uses the same stack */
    . = ALIGN(0x40); .stack_end = .; . = . + 16384; __stack_begin = .;

    /* for sbrk.c */
    . = ALIGN (0x8);
    __heap = .; __heap_end = RAM_START + RAM_SIZE;

    RISC32_DCACHE_SIZE = 4096;
    RISC32_DCACHE_LINE_SIZE = 16;
    RISC32_DCACHE_WAYS = 2;
}

