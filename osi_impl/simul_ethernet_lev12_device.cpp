#include "osi_impl/simul_ethernet_lev12_device.h"
#include "osi_impl/utils.h"

#include <iostream>

SimulEthernetLev12Device::SimulEthernetLev12Device(const std::string& mac_address): 
    mac_address_(std::vector<uint8_t>(ETH_ALEN)), 
    consumer_thread_(std::thread(_consume_arrived_frames)),
    producer_thread_(std::thread(_produce_tobesent_frames)),
    stopFlag_(false) 
{
    macStringToBytes(mac_address, mac_address_.data());
}

SimulEthernetLev12Device::SimulEthernetLev12Device(const SimulEthernetLev12Device& oth)
{
    mac_address_ = oth.mac_address_;
    
    in_buff_ = oth.in_buff_;
    out_buff_ = oth.out_buff_;
}

void SimulEthernetLev12Device::send(const std::shared_ptr<EthernetFrame>& frame) 
{
    {
        std::lock_guard<std::mutex> lock(producer_mutex_);
        out_buff_.push(frame);
        producer_cv_.notify_one();
    }
    std::cout << "to-be-sent frame was buffered";
}

std::shared_ptr<EthernetFrame> SimulEthernetLev12Device::receive(const std::shared_ptr<EthernetFrame>& frame) 
{
    // get the current (Ethernet) header, check it if so, and call receive on the next level (network level) on the (remaining) payload
}

SimulEthernetLev12Device::~SimulEthernetLev12Device() 
{
    if (!stopFlag_) {
        stopFlag_ = true;
        consumer_cv_.notify_all();
        producer_cv_.notify_all();
        consumer_thread_.join();
        producer_thread_.join();
    }
}

void SimulEthernetLev12Device::_frame_arrived(const std::shared_ptr<EthernetFrame>& frame) {
    in_buff_.push(frame);
}

void SimulEthernetLev12Device::_consume_arrived_frames() {
    while (1) {
        std::unique_lock<std::mutex> lock(consumer_mutex_);
        
        consumer_cv_.wait(lock, [this]{return !this->in_buff_.empty() || this->stopFlag_;});
        if (stopFlag_) break;

        auto frame = in_buff_.front();
        try {
            receive(frame);
        }
        catch (std::exception e) {
            std::cout << "error on processing -receive (send to the next upwards tcpip level (network level)) ethernet frame " << frame << ": " << e;
        }
        in_buff_.pop();

        lock.unlock();
    }
}

void SimulEthernetLev12Device::_produce_tobesent_frames() {
    while (1) {
        std::unique_lock<std::mutex> lock(producer_mutex_);
        producer_cv_.wait(lock, [this] { !this->out_buff_.empty() || this->stopFlag_; });
        if (stopFlag_) break;

        auto frame = out_buff_.front();
        try {
            for (const std::shared_ptr<SimulEthernetLev12Device>& ethdev: PHY_CONNECTED_DEVICES) {
                ethdev->_frame_arrived(frame);
            }
        }
        catch (std::exception e) {
            std::cout << "error on sending buffered frame to phisically connected devices " << e;
        }
        out_buff_.pop();
        lock.unlock();
    }
}