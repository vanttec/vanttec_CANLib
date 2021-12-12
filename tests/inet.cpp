//
// Created by abiel on 12/9/21.
//

#include <gtest/gtest.h>
#include "Vanttec_CANLib/ByteOrder/inet.h"
#include <arpa/inet.h>
/**
 * Compare vanttec implementation vs inet
 */

TEST(inet, hton){
    for(uint16_t i = 0; i < std::numeric_limits<uint8_t>().max(); i++){
        EXPECT_EQ(htons(i), vanttec::htons(i));
    }

    for(uint32_t i = 0; i < std::numeric_limits<uint16_t>().max(); i++){
        EXPECT_EQ(htonl(i), vanttec::htonl(i));
    }
}

TEST(inet, ntoh){
    for(uint16_t i = 0; i < std::numeric_limits<uint8_t>().max(); i++){
        EXPECT_EQ(ntohs(i), vanttec::ntohs(i));
    }

    for(uint32_t i = 0; i < std::numeric_limits<uint16_t>().max(); i++){
        EXPECT_EQ(ntohl(i), vanttec::ntohl(i));
    }
}