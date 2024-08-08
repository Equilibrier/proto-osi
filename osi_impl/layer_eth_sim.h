#include <cstdint>
#include <linux/if_ether.h>
#include <memory>
#include <vector>

/*
#include <iostream>
#include <queue>
#include <thread>
#include <condition_variable>
#include <netinet/ether.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <net/if.h>
#include <net/ethernet.h>
#include <linux/if_packet.h>

#include "osi_impl/utils.h"*/

struct EthernetFrame {
    std::array<uint8_t, ETH_ALEN> dest_mac;  // Adresa MAC de destinație
    std::array<uint8_t, ETH_ALEN> src_mac;   // Adresa MAC sursă
    uint16_t protocol;                // Tipul de protocol (ex: ETH_P_IP)
    std::vector<uint8_t> payload;    // Payload-ul efectiv
};

class L2Socket 
{
public:
    virtual void send(const std::shared_ptr<EthernetFrame>& frame) = 0;
    virtual std::shared_ptr<EthernetFrame> receive() = 0;

    virtual ~L2Socket() = 0;
};