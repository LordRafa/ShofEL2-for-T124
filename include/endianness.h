#ifndef _ENDIANNESS_H_
#define _ENDIANNESS_H_

#ifdef __BYTE_ORDER
    #if __BYTE_ORDER == __BIG_ENDIAN

        #include <byteswap.h>
        #define TO_LITTLE_ENDIAN(x) bswap_32(x)

    #elif __BYTE_ORDER == __LITTLE_ENDIAN

        #define TO_LITTLE_ENDIAN(x) x

    #endif
#endif

#endif
