//
// Created by abiel on 12/9/21.
//

#include "inet.h"

namespace vanttec {
    uint32_t htonl(uint32_t hostlong) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        return hostlong; //No conversion needed
#else
        return __builtin_bswap32(hostlong);
#endif
    }

    uint16_t htons(uint16_t hostshort) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        return hostshort; //No conversion needed
#else
        return __builtin_bswap16(hostshort);
#endif
    }

    uint32_t ntohl(uint32_t netlong) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        return netlong; //No conversion needed
#else
        return __builtin_bswap32(netlong);
#endif
    }

    uint16_t ntohs(uint16_t netshort) {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
        return netlong; //No conversion needed
#else
        return __builtin_bswap16(netshort);
#endif
    }
}