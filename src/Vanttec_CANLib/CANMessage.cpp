//
// Created by abiel on 12/9/21.
//

#include "CANMessage.h"
#include "Vanttec_CANLib/Utils/CANSerialization.h"
#include "Vanttec_CANLib/Utils/CANDeserialization.h"

namespace vanttec {
    uint8_t getId(const CANMessage &message){
        if(message.len == 0 || message.data == nullptr) return 0;
        return message.data[0];
    }

    float getFloat(const CANMessage &message){
        if(message.len != 5){
            return NAN;
        }

        return deserializeFloat(deserializeLong(message.data + 1));
    }

    void packFloat(CANMessage & message, uint8_t id, float data){
        packLong(message, id, serializeFloat(data));
    }

    uint16_t getShort(const CANMessage &message){
        if(message.len != 3){
            return 0;
        }

        return deserializeShort(message.data + 1);
    }

    void packShort(CANMessage &message, uint8_t id, uint16_t data){
        message.data = (uint8_t*) malloc(3);
        message.len = 3;
        if(message.data == nullptr){
            message.len = 0;
            return;
        }

        message.data[0] = id;
        serializeShort(message.data + 1, data);
    }

    uint32_t getLong(const CANMessage &message){
        if(message.len != 5) return 0;
        return deserializeLong(message.data + 1);
    }

    void packLong(CANMessage &message, uint8_t id, uint32_t data){
        message.data = (uint8_t*) malloc(5);
        message.len = 5;
        if(message.data == nullptr){
            message.len = 0;
            return;
        }

        message.data[0] = id;
        serializeLong(message.data + 1, data);
    }
}