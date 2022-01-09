#include <iostream>
#include <cmath>
#include <limits>
#include <random>
#include <numeric>
#include <thread>
#include <chrono>
#include "Vanttec_CANLib/Utils/CANDeserialization.h"
#include "Vanttec_CANLib/Utils/CANSerialization.h"
#include "Vanttec_CANLib_Linux/CANHandler.h"
#include "Vanttec_CANLib/can_system_def.h"

int main() {
    vanttec::CANHandler handler("test");
//    std::thread writeThread([&]{
//        for(;;) {
//            handler.write(vanttec::CANMessage());
//            std::this_thread::sleep_for(std::chrono::seconds(10));
//        }
//    });
//
//    while(true){
//        handler.update_write();
//        std::cout << "Got data" << std::endl;
//    }

}
