#ifndef NETWORK_LAYER_H
#define NETWORK_LAYER_H

#include <iostream>
#include <netinet/ip.h>

class NetworkLayer
{
    NetworkLayer(); // the rule of three, if I need a personalized constructor, I should also need a copy constructor (to be determined :) ) and a custom destructor
    NetworkLayer(const NetworkLayer& oth);
    ~NetworkLayer() = default;

    //iphdr
    void receive(iphdr* ip_packet, uint16_t totalSize);
    void send(iphdr* ip_packet, uint16_t totalSize);

private:
    // ...
};

#endif // NETWORK_LAYER_H