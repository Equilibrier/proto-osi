#ifndef NETWORK_PARAMS_H
#define NETWORK_PARAMS_H

#include <cstdint>
//#include <memory>
#include <mutex>

class NetworkParams
{
public:
    NetworkParams(const NetworkParams&) = delete;
    void operator = (const NetworkParams&) = delete;

    static NetworkParams* instance(
        #ifdef TEST 
        uint16_t mtu 
        #endif
    );

    void setMtu(uint16_t mtu);
    uint16_t mtu();

private:
    NetworkParams(
        #ifdef TEST
        uint16_t mtu
        #endif
    ) {
       #ifdef TEST
       mtu_ = mtu;
       #endif 
    }// = default;
    ~NetworkParams() = default;

    static NetworkParams* instance_;
    static std::mutex mutex_;

    #ifdef TEST
    uint16_t mtu_;
    #endif 
};


#endif // NETWORK_PARAMS_H