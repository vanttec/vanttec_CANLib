//
// Created by abiel on 12/9/21.
//

#pragma once

#include <cstdint>

namespace vanttec{
    struct CANMessage {
        uint8_t *data{nullptr};
        std::size_t len{0};

        ~CANMessage(){
            if(len)
                delete data;
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
