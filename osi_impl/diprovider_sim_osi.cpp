#include "osi_impl/diprovider.h"
#include "osi_impl/simul_ethernet_lev12_device.h"

#include <vector>

std::vector<std::shared_ptr<SimulEthernetLev12Device>> PHY_CONNECTED_DEVICES{
    std::make_shared<SimulEthernetLev12Device>("00:1A:2B:3C:4D:5E"),
    std::make_shared<SimulEthernetLev12Device>("F0:9F:6D:8E:7A:1B"),
    std::make_shared<SimulEthernetLev12Device>("B8:6A:4C:2D:3E:9F"),
    std::make_shared<SimulEthernetLev12Device>("7C:5D:3A:9E:0F:1B"),
    std::make_shared<SimulEthernetLev12Device>("A1:BC:4E:2D:5F:6G")
};

// TODO I'm not sure but I should build a topology, so the PHY_CONNECTED_DEVICES was good to be maintained oin the constructor (internal state) param form, or it can be globally defined as a tree-form topology (but the first is much more simpler) but since circular connections could be made, a connect(to_device) method should be provided as well, additionally to the phyconnected_devices which can be an empty list (implicit param)

std::unique_ptr<L2Socket> DataFrameSocket = std::make_unique<SimulEthernetLev12Device>("E2:7D:1F:8A:9B:4C");