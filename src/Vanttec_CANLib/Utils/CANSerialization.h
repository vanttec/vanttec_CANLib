//
// Created by abiel on 12/9/21.
//

#pragma once

#include <cstdint>
#include <cmath>

namespace vanttec {
    uint32_t serializeFloat(float input);

    void serializeShort(uint8_t *data, uint16_t in);

    void serializeLong(uint8_t *data, uint32_t in);
};
