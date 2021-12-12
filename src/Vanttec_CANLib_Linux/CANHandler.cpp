//
// Created by abiel on 12/9/21.
//

#include "CANHandler.h"
#include "socketcan.h"
#include <iostream>

namespace vanttec {
    CANHandler::CANHandler(const std::string &interfaceName) {
//    epfd = epoll_create1(0);
//    canfd = vanttec::socketcan_open(interfaceName);
//    if(epfd == -1 || canfd == -1){
//        if(epfd) close(epfd);
//        if(canfd) close(canfd);
//        throw std::runtime_error("Could not initialise CANHandler fds");
//    }
//
//    int ret;
//    epoll_event ev{};
//
//    ev.data.fd = canfd;
//    ev.events = EPOLLIN; //Poll for read and write
//
//    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, canfd, &ev);
//    if(ret == -1){
//        close(epfd);
//        close(canfd);
//        throw std::runtime_error("Could not add to epoll");
//    }
    }

    void CANHandler::write(const vanttec::CANMessage &msg) {
        //TODO Do something with the message
        std::unique_lock<std::mutex> lk(cv_m);
        writeQueue.push(1);

        lk.unlock();
        cv.notify_all();
    }

    void CANHandler::update_read() {
        int rdy = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
        if (rdy == -1) {
            std::cerr << "Error waiting for epoll" << std::endl;
            return;
        }

        for (int i = 0; i < rdy; i++) {
            if (evlist[i].events & EPOLLIN) {
                //Read available
                //TODO read
            }
        }
    }

    void CANHandler::update_write() {
        std::unique_lock<std::mutex> lk(cv_m);
        cv.wait(lk, [this] {
            return !this->writeQueue.empty();
        });

        auto elem = writeQueue.front();
        writeQueue.pop();
        lk.unlock();
    }

    CANHandler::~CANHandler() {
        if (epfd)
            close(epfd);

        if (canfd)
            close(canfd);
    }
}