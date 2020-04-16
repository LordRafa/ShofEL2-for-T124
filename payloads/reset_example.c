#include "types.h"

static inline u32 read32(uintptr_t addr) {
    return *(vu32 *)addr;
}

static inline void write32(uintptr_t addr, u32 val) {
    *(vu32 *)addr = val;
}

static inline void or32(uintptr_t addr, u32 val) {
    write32(addr, read32(addr) | val);
}

#define PMC_BASE               0x7000e400
#define PMC_CNTRL              0x000
#define PMC_CNTRL_MAIN_RST    (1 << 4)
#define PMC_SCRATCH0           0x050
#define PMC_SCRATCH0_MODE_RCM (1 << 1)

__attribute__((section(".init")))
void main() {
//    or32(PMC_BASE + PMC_SCRATCH0, PMC_SCRATCH0_MODE_RCM);
    or32(PMC_BASE + PMC_CNTRL, PMC_CNTRL_MAIN_RST);
}

