#include "osi_impl/layer_tcp.h"

TransportLayer::TransportLayer(uint16_t mss): 
    mss_(mss) 
{
}
TransportLayer::TransportLayer(const TransportLayer& oth) 
{
    mss_ = oth.mss_;
}

//tcphdr
void TransportLayer::receive(tcphdr* tcp_packet, uint16_t totalSize) 
{
    // parse header
    // validate segment&header (checksum includes both) 
    //    + ACK logic, if the case (send an ACK packetm or NOT IF DUPLICATE part)
    //    + TCP connection logic, if the case (three-handshake start connection packet or four-handshake end connection packet to be sent)
    // extract payload 
    // TCP packet composing; and continue only if complete packet is ready:
        // send payload to next level
}
void TransportLayer::send(tcphdr* tcp_packet, uint16_t totalSize) 
{
    // parse header & do segmention on the received packet by, MSS limit, if the case
    // then, for each segment:
        // build dataframe header, reform the dataframe packet and send it to the lower level (dataframe), using the send(...) method
}