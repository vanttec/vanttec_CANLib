//
// Created by abiel on 12/9/21.
//

#include <gtest/gtest.h>
#include "Vanttec_CANLib/Utils/CANSerialization.h"
#include "Vanttec_CANLib/Utils/CANDeserialization.h"

float serializeDeserializeFloat(float in){
    return vanttec::deserializeFloat(vanttec::serializeFloat(in));
}

TEST(CANSerialize, serializeFloat){
    float i = -1000.0;
    while(i < 1000){
        EXPECT_NEAR(serializeDeserializeFloat(i), i, 0.001);
        i += 0.01;
    }
}

TEST(CANSerialize, serializeShort){
    uint8_t data[2];
    for(uint32_t i = 0; i < std::numeric_limits<uint16_t>().max(); i++){
        vanttec::serializeShort(data, i);
        EXPECT_EQ(vanttec::deserializeShort(data), i);
    }
}

TEST(CANSerialize, serializeLong){
    uint8_t data[4];
    for(uint64_t i = 0; i < std::numeric_limits<uint32_t>().max(); i += 1024){
        vanttec::serializeLong(data, i);
        EXPECT_EQ(vanttec::deserializeLong(data), i);
    }
}