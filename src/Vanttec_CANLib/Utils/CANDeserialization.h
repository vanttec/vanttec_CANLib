//
// Created by abiel on 12/9/21.
//

#pragma once

#include <cstdint>
#include <cmath>

namespace vanttec {
    float deserializeFloat(uint32_t in);

    uint16_t deserializeShort(uint8_t *data);

    uint32_t deserializeLong(uint8_t *data);
}
