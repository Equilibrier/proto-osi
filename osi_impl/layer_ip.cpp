#include "osi_impl/layer_ip.h"
#include "osi_impl/utils.h"

#include "osi_impl/network_params.h"
#include "osi_impl/diprovider.h"

NetworkLayer::NetworkLayer()
{ // the rule of three, if I need a personalized constructor, I should also need a copy constructor (to be determined :) ) and a custom destructor
}

NetworkLayer::NetworkLayer(const NetworkLayer& oth) {
    this->mtu_ = oth.mtu_;
}

//iphdr
void NetworkLayer::receive(iphdr* ip_packet, uint16_t totalSize) // compose fragments
{
    // parse header & validate header
    // IP packet composing; and continue only if complete packet is ready:
        // extract payload
        // send payload to next layer (transport layer)

    //calculate_ip_checksum
    uint16_t recv_csum = ip_packet->check;
    ip_packet->check = 0; // for checksum calculation, by protocol implementation specification
    uint16_t actual_csum = ip_header_checksum(ip_packet);
    if (recv_csum != actual_csum) {
        // fragment will be dropped, as it has an invalid, meaning it will just not be sent further (upper) in the stack
        std::cout << "ip packet fragment invalid - dropped";
        return;
    }
    ip_packet->check = recv_csum;
    
    
}
void NetworkLayer::send(iphdr* ip_packet, uint16_t totalSize) // do fragmentation
{
    // parse header & do fragmentation of the received message, by MTU limit, if the case
    // parse header and read source & dest IPsm and then, for each fragment: 
        // do ARP and routing logic with possible rerouting logic taken into account
        // build dataframe header, reform the dataframe packet and send it to the lower level (dataframe), using the send(...) method

    if (ip_packet->tot_len < NetworkParams::instance()->mtu()) {
        // it can be sent as a single fragment ip packet
        DataFrameSocket()
    }
    else {

    }
}