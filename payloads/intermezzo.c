#include "types.h"
#include "t124.h"

typedef int (*ep1_in_imm_t)( void *buffer, u32 size, u32 *num_xfer );


__attribute__((section(".init")))
void entry() {


    register ep1_in_imm_t ep1_in_imm = (ep1_in_imm_t) ( *( (u32 *) IRAM_ADD_TRANSPORT_ADD ) | 1 );

    register u32 *mio = (u32*) 0x4003FFF8;

    *mio = 0xFAFA;


    static u32 num_xfer;
    static char buffer[32] = "WOLOLO";
    ep1_in_imm( buffer, 7, &num_xfer );
    while(1);

}

