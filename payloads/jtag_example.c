#include "types.h"

static inline void write32(uintptr_t addr, u32 val) {
    *(vu32 *)addr = val;
}

#define APB_BASE	0x70000000
#define APB_MISC_PP_CONFIG_CTL_0	0x24
#define JTAG_ON				0xC0

#define SECURE_BOOT_BASE	0x6000C200
#define SB_PFCFG_0		0x8
#define DEBUG_ON		0x00C0008F

__attribute__((section(".init")))
void main() {
    // TODO: THIS DOESN'T WORK
    write32(APB_BASE + APB_MISC_PP_CONFIG_CTL_0, JTAG_ON);
    write32(SECURE_BOOT_BASE + SB_PFCFG_0, DEBUG_ON);
    while(1);
}

