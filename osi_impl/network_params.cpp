//#include <iostream>

#include "osi_impl/network_params.h"

std::mutex NetworkParams::mutex_;
NetworkParams* NetworkParams::instance_{nullptr};

// default parameters
uint16_t mtu_ = 1500;

NetworkParams* NetworkParams::instance(
    #ifdef TEST
    uint16_t mtu
    #endif
    )
{
    std::lock_guard<std::mutex> lock(NetworkParams::mutex_);
    if (instance_ == nullptr) {
        instance_ = new NetworkParams(
            #ifdef TEST
            mtu
            #endif
        );
    }
    return instance_;
}

void NetworkParams::setMtu(uint16_t mtu) { mtu_ = mtu;}
uint16_t NetworkParams::mtu() { return mtu_; }