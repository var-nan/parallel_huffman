#include "huffman_serial.hpp"
#include <vector>
#include <fstream>
#include <iostream>


using namespace serial;

void encode(const string& inFileName, const string& outFileName){
    
    // open file for reading
    std::ifstream file(inFileName, std::ios::binary);

    if (!file) {
        // error
        return -1;
    }

    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0);

    std::vector<Byte> file_data (file_size);

    file.read(file_data.data(), file_size);

    // count characters
    vector<size_t> frequencies(256, 0);

    for (const auto& byte : file_data){
        frequencies[byte]++;
    }

    // build tree basedon the frequencies
    
}
