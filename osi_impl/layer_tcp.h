#include <iostream>
#include <netinet/tcp.h>

class TransportLayer
{
public:
    TransportLayer(uint16_t mss);
    TransportLayer(const TransportLayer& oth);
    ~TransportLayer() = default;

    //tcphdr
    void receive(tcphdr* tcp_packet, uint16_t totalSize);
    void send(tcphdr* tcp_packet, uint16_t totalSize);

private:
    uint16_t mss_;
};