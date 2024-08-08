#ifndef DIPROVIDER_H
#define DIPROVIDER_H

#include <string>
#include <memory>

#include "osi_impl/layer_eth_sim.h"

extern std::string InterfaceName; // to be filled in with a cpp that reads it from an user interface/file or whatever...
extern std::unique_ptr<L2Socket> DataFrameSocket;

#endif // DIPROVIDER_H