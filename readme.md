# OSI Stack Implementation

This project demonstrates the implementation of a simplified OSI stack for academic purposes, focusing on core principles and basic protocols. The goal is to showcase understanding of network stack implementation with a basic, extendable approach in C/C++.

## Project Overview

The project includes a basic implementation of the OSI stack with attention to:

- **Core OSI Layers**: Implemented to a basic level.
- **Network Protocols**: Includes simplified implementations of DHCP, DNS, HTTP, MQTT, NTP, Telnet, and WebSocket.
- **Simulation and Testing**: (@TODO) Utilizes a dummy simulation executable for testing and includes stubs for more advanced features.


## Features

- **Basic OSI Layers Implementation**: Focuses on network and transport layers with ongoing development.
- **Protocol Simulation**: Simulates basic Ethernet Level 1+2 devices.
- **Testing**: (for now, it includes basic internal tests for singleton, threading, and synchronization) @TODO Will include simulation tests for the implemented stack.

## Getting Started

To build and run the project:

1. Clone the repository:
    ```bash
    git clone https://github.com/Equilibrier/proto-osi.git ProtoOSI-cpp
    cd ProtoOSI-cpp
    ```

2. Build the project:
    ```bash
    make
    ```
    or
    ```bash
    make tests
    ```

3. Run the simulation executable:
    ```bash
    ./build/sim_osi_stack
    ```
    @TODO it will have the possibility to choose (from cli) between simulation and real in OS-stack implementation injection mode with derived instructions on how to simulate the real end of the connections (linux utilities implementing real OSI).

## Future Work

- **Extended Protocol Support**: Adding more detailed protocol implementations and handling.
- **Advanced Testing**: Incorporating tests for congestion, simulated physical errors, and other edge cases.
- **Namespace Injection**: Implementation to be completed for real OSI stack injection and interaction with real devices.

## Contributing

Feel free to contribute by submitting issues or pull requests. This project is in active development, and any contributions or feedback are welcome!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

This project is intended for academic demonstration and personal development. It provides a foundation for understanding OSI stack implementation and network protocols.



