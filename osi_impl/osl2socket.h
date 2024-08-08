#ifndef OSL2SOCKER_H
#define OSL2SOCKER_H

#include "osi_impl/layer_eth_sim.h"

/*TO BE FINISHED - it should properly hook into OS legit mechanisms to read ethernet frames and send ethernet frames to the selected interface's NIC device
maybe libcap and libnet should be used instead...
*/
class OSL2Socket: public L2Socket
{
public:
    OSL2Socket(const std::string& interface_name);
    ~OSL2Socket();

    void send(const std::shared_ptr<EthernetFrame>& frame);
    std::shared_ptr<EthernetFrame> receive();
private:
    int sockfd_;
    std::string interface_name_;
    std::queue<uint8_t> in_buff_;
};

#endif // OSL2SOCKER_H