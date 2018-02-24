#ifndef __SECURE_R2_REG__
#define __SECURE_R2_REG__


#define SECURE_PUBLIC 0x123900
#define REG_RC_CLOCK  0x10
#define ENABLE_RC_LOCK    (1<<13)
#define REG_DRAM_SIZE 0x20
#define DRAM_NO_LIMIT       0x0000
#define DRAM_SIZE_002MB     0x0001
#define DRAM_SIZE_004MB     0x0002
#define DRAM_SIZE_008MB     0x0003
#define DRAM_SIZE_016MB     0x0004
#define DRAM_SIZE_032MB     0x0005
#define DRAM_SIZE_064MB     0x0006
#define DRAM_SIZE_128MB     0x0007
#define DRAM_SIZE_256MB     0x0008
#define DRAM_SIZE_512MB     0x0009
#define DRAM_SIZE_001GB     0x000A
#define ENABLE_DRAM_SIZE    0x0010

#endif
