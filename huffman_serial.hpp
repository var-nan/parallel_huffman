#ifndef HUFFMAN_SERIAL_H
#define HUFFMAN_SERIAL_H

#include "utils.hpp"
#include <cstdlib>

namespace serial {

    const static uint8_t LookupTable [8] = {
        0b10000000,
        0b01000000,
        0b00100000,
        0b00010000,
        0b00001000,
        0b00000100,
        0b00000010,
        0b00000001
    };

    void encode(const string& inFile, const string& outFile);

    void buffer_write(char *out_buf, size_t pos, uint32_t element);


}
#endif
