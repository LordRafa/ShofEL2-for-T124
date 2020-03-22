ENTRY(__romhax_start)

SECTIONS {
    /* We don't do GOT relocation and rely on nothing ending up using the GOT
     * (-fno-common helps here) */
    /DISCARD/ : { *(.comment) }
    __romhax_start = 0x4000E000;
    .init 0x4000E000: { *(.init) *(.init.*) }
    .text : { *(.text) *(.text.*) }
    .data : { *(.data) *(.data.*) }
    .rodata : { *(.rodata) *(.rodata.*) *(.got) }
    __got_start = .;
    .got : { *(.got) }
    __got_end = .;
    __bss_start = .;
    .bss : { *(.bss) *(.bss.*) *(COMMON)}
    __bss_end = .;
    __romhax_end = .;
    .footer : { LONG(0xdeadbeef) } /* make sure .bss is padded out */
}
