#ifndef SIMULETH_LEV12DEVICE_H
#define SIMULETH_LEV12DEVICE_H

#include "osi_impl/layer_eth_sim.h"

#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <memory>

class SimulEthernetLev12Device;

extern std::vector<std::shared_ptr<SimulEthernetLev12Device>> PHY_CONNECTED_DEVICES;

class SimulEthernetLev12Device: public L2Socket
{
public:
    SimulEthernetLev12Device(const std::string& mac_address);
    SimulEthernetLev12Device(const SimulEthernetLev12Device& oth); // rule of three :)
    virtual ~SimulEthernetLev12Device();

    void send(const std::shared_ptr<EthernetFrame>& frame);
    std::shared_ptr<EthernetFrame> receive(const std::shared_ptr<EthernetFrame>& frame);

private:
    std::queue<std::shared_ptr<EthernetFrame>> in_buff_;
    std::queue<std::shared_ptr<EthernetFrame>> out_buff_;
    std::vector<uint8_t> mac_address_;
    std::thread consumer_thread_;
    std::thread producer_thread_;
    std::condition_variable consumer_cv_;
    std::mutex consumer_mutex_;
    std::condition_variable producer_cv_;
    std::mutex producer_mutex_;
    bool stopFlag_;

    void _frame_arrived(const std::shared_ptr<EthernetFrame>& frame);
    void _consume_arrived_frames();
    void _produce_tobesent_frames(); // it's redundant, practically it should not have it's own thread, because the processing of the arrived frames on the phy connected devices is already decoupled with the consuming_thread, so this would be fast enough to process to require a separate thread, but we do this just for academic purposes, to be honest in properly simulating the hardware part (transmission and reception of byte packages , in here, frame construction and deconstruction as well - as these are implied in this Ethernet Lev 1 + 2 simulated device)
};

// testing app will use frame_arrived to push dummy data into the device, and should use make_shared to construct a shared pointer variant of an Ethernet Frame...

#endif // SIMULETH_LEV12DEVICE_H