//
// Created by abiel on 12/9/21.
//

#pragma once

#include <cstdint>

/**
* All data transfered over CAN will be sent in big-endian byte order
 * cross-platform version of https://linux.die.net/man/3/htonl
*/
namespace vanttec {
    uint32_t htonl(uint32_t hostlong);

    uint16_t htons(uint16_t hostshort);

    uint32_t ntohl(uint32_t netlong);

    uint16_t ntohs(uint16_t netshort);
}