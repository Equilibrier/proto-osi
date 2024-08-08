#include "osi_impl/diprovider.h"
#include "osi_impl/layer_eth_sim.h"

std::unique_ptr<L2Socket> DataFrameSocket = std::make_unique<OSL2Socket>(InterfaceName);