#include <iostream>
#include <thread>

#include "osi_impl/network_params.h"

int main(int argc, char** argv)
{
    std::thread t1([&]{ std::cout << NetworkParams::instance(128)->mtu() << std::endl; });
    std::thread t2([&]{ std::cout << NetworkParams::instance(256)->mtu() << std::endl; });

    t1.join();
    t2.join();

    return 0;
}