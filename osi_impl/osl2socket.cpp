#include "osi_impl/osl2socket.h"

#include <queue>

OSL2Socket::OSL2Socket(const std::string& interface_name)
{
    interface_name_ = interface_name;

    sockfd_ = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sockfd_ < 0) {
        throw std::runtime_error("Failed to create raw socket");
    }
    fcntl(sockfd_, F_SETFL, O_NONBLOCK);

    std::cout << "Raw socket successfully created";
}

OSL2Socket::~OSL2Socket()
{
    if (sockfd_ >= 0) {
        close(sockfd_);
        //sockfd_ = -1;
    }
    std::cout << "Raw socket was closed";
}

void OSL2Socket::send(const std::shared_ptr<EthernetFrame>& frame)
{
    sockaddr_ll destAddr = {};
    destAddr.sll_family = AF_PACKET;
    destAddr.sll_ifindex = if_nametoindex(interface_name_.c_str());

    if (sendto(sockfd_, frame->payload.data(), frame->payload.size(), 0, (sockaddr*)&destAddr, sizeof(destAddr)) < 0) {
        throw std::runtime_error("raw socket: failed to send data");
    }
    std::cout << "raw socket: send data";
}

std::shared_ptr<EthernetFrame> OSL2Socket::receive()
{
    std::vector<uint8_t> buff(2048);
    ssize_t len = recvfrom(sockfd_, buff.data(), buff.size(), 0, nullptr, nullptr);
    if (len < 0) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) {
            throw std::runtime_error("raw socket: failed to receive data");
        }
        return {};
    }
    buff.resize(len);
    std::cout << "raw socket: data received: " << len << " bytes";
    //return EthernetFrame(...); // should use casting for the header part and then pointer offseting for the payload part, then construct the frame (with std::make_shared) // but the problem is PACKET_SOCK dependent OS protocol should be instead, to be able to read complete frames, or even raw sockets but in_buff_ should be used to read in advance and maybe storing addresses to the begining of the header parts in a frames queue (it should be easier, not neccessarily optimal - for this is for academic purposes)
    throw std::runtime_error("to be further implemented");
}

