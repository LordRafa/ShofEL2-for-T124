__payload_bin_start = 0x4000E000;
ENTRY(__payload_bin_start)

SECTIONS {
    /* We don't do GOT relocation and rely on nothing ending up using the GOT
     * (-fno-common helps here) */
    /DISCARD/ : { *(.comment) }
    .init (__payload_bin_start): { *(.init) *(.init.*) }
    .text : { *(.text) *(.text.*) }
    .data : { *(.data) *(.data.*) }
    .rodata : { *(.rodata) *(.rodata.*) *(.got) }
    .got : { *(.got) }
    .bss : { *(.bss) *(.bss.*) *(COMMON)}
    .footer : { LONG(0xdeadbeef) } /* make sure .bss is padded out */
    __payload_bin_end = .;
}
