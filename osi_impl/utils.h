//#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <netinet/ip.h>

bool macStringToBytes(const std::string& macStr, uint8_t* macAddr) {
    std::istringstream stream(macStr);
    int values[6];
    char colon;

    // Citirea adresei MAC în șase componente separate de 2 caractere
    if (stream >> std::hex >> values[0] >> colon >>
                values[1] >> colon >>
                values[2] >> colon >>
                values[3] >> colon >>
                values[4] >> colon >>
                values[5]) {
        // Verifică dacă fiecare componentă a fost citită corect
        if (stream.fail() || !stream.eof()) {
            return false; // A apărut o eroare la citirea
        }

        // Convertirea fiecărei componente în octeți și salvarea în array
        for (int i = 0; i < 6; ++i) {
            macAddr[i] = static_cast<unsigned char>(values[i]);
        }
        return true;
    }
    return false;
}

uint16_t ip_header_checksum(iphdr *ip_header) {
    uint32_t sum = 0;
    uint16_t *header = (uint16_t *) ip_header;
    int sum_terms_length = ip_header->ip_hl * 2; // ip_hl este în cuvinte de 32 de biți

    ip_header->ip_sum = 0; // Setăm checksum-ul la 0 pentru calcul

    for (int i = 0; i < sum_terms_length; i++) {
        sum += header[i];
        if (sum > 0xFFFF) {
            sum -= 0xFFFF; // Overflow de 16 biți
        }
    }

    return (uint16_t)(~sum);
}
