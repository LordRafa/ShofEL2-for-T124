#include "types.h"
#include "t124.h"

extern u32 __payload_bin_start;
extern u32 __payload_bin_end;

typedef void (*post_relocation_t)( void );
typedef void (*payload_ep_t)( void );
typedef void (*_memcpy_t)( void *dst, const void *src, size_t len );

void _memcpy( void *dst, const void *src, size_t len ) {

    for ( size_t i = 0; i < len; i++ ) {
        ( (u8 *)dst )[i] = ( (u8 *)src )[i];
    }

}
// Probably I could trust in have relative PC branches, so no address would
// require to be updated. This would work since there is a whole new copy
// of the binary on the relocated area and PC would be working on that area
// but having memcpy address on a register and update it to the relocated
// area when required should improve the chances of the compiler not messing
// up with the memcpy calls.
register _memcpy_t memcpy asm("r7");
        
void _post_relocation() {

    // Same with these arguments....
    register u32 payload_bef_len = *( (u32 *) IRAM_ADD_PAYLOAD_BEF_LENVAR );
    register u32 payload_aft_len = *( (u32 *) IRAM_ADD_PAYLOAD_AFT_LENVAR );
    register u32 payload_thumb_mode = *( (u32 *) IRAM_ADD_PAYLOAD_THUMB_MODE );

    memcpy -= INTERMEZZO_LEN;
    memcpy( (u8 *) BOOTROM_PAYLOAD_ENTRY, (u8 *) IRAM_ADD_PAYLOAD_START, payload_bef_len );
    memcpy( (u8 *) (BOOTROM_PAYLOAD_ENTRY + payload_bef_len), (u8 *) IRAM_ADD_PAYLOAD_CONT, payload_aft_len );

    payload_ep_t payload_ep = (payload_ep_t) ( BOOTROM_PAYLOAD_ENTRY | payload_thumb_mode );
    payload_ep();

}

__attribute__((section(".init")))
void pre_relocation() {

    u32 payload_bin_size = (u32)&__payload_bin_end - (u32)&__payload_bin_start;
    u8 *dest = (u8 *) ( BOOTROM_PAYLOAD_ENTRY - INTERMEZZO_LEN );

    memcpy = _memcpy;
    memcpy( dest, &__payload_bin_start, payload_bin_size );
 
    post_relocation_t post_relocation = _post_relocation - INTERMEZZO_LEN;
    post_relocation();

}

