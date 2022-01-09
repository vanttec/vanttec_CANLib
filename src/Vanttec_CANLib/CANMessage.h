//
// Created by abiel on 12/9/21.
//

#pragma once

#include <cstdint>

namespace vanttec {
    struct CANMessage {
        uint8_t data[5];
        std::size_t len{0};

        ~CANMessage() {
            ;
        }
    };

    uint8_t getId(const CANMessage &message);

    float getFloat(const CANMessage &message);

    void packFloat(CANMessage &message, uint8_t id, float data);

    uint16_t getShort(const CANMessage &message);

    void packShort(CANMessage &message, uint8_t id, uint16_t data);

    uint32_t getLong(const CANMessage &message);

    void packLong(CANMessage &message, uint8_t id, uint32_t data);
}

extern "C" {
uint8_t can_parse_id(const uint8_t *data, uint8_t len);

void can_pack_float(uint8_t id, float n, uint8_t *data, uint8_t len);
float can_parse_float(const uint8_t *data, uint8_t len);

void can_pack_short(uint8_t id, uint16_t n, uint8_t *data, uint8_t len);
uint16_t can_parse_short(const uint8_t *data, uint8_t len);

void can_pack_long(uint8_t id, uint32_t n, uint8_t *data, uint8_t len);
uint32_t can_parse_long(const uint8_t *data, uint8_t len);
}