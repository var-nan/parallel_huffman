#include "huffman_serial.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>


using namespace serial;

void serial::encode(const string& inFileName, const string& outFileName){
    
    // open file for reading
    std::ifstream file(inFileName, std::ios::binary);

    if (!file) {
        std::cerr << "File cannot be opened " << std::endl;
        // error
        return ;
    }

    file.seekg(0, std::ios::end);
    std::streampos file_size = file.tellg();
    file.seekg(0);

    std::vector<char> file_data (file_size);

    file.read(file_data.data(), file_size);

    // count characters
    vector<size_t> frequencies(128, 0);

    for (const auto& byte : file_data){
        frequencies[byte]++;
    }

    huffman::HuffTree tree(frequencies);

    auto codes = tree.printTree(frequencies);

    auto codes_copy = codes;

    std::sort(codes.begin(), codes.end(), [](const string& a, const string& b) {return a.size() < b.size();});

    for (const string& e : codes){
        if (!e.empty()) cout << e << endl;
    }

    if (validate(codes)) cout << "generated codes are prefix codes" << endl;
    else cout << "generated codes are not prefix codes" << endl;


    // print the compression efficiency.
    size_t newTotal = 0, oldTotal = 0;
    for (int i = 0; i < MAX_CHAR; i++){
        newTotal += codes[i].size() * frequencies[i];
        oldTotal += 8 * frequencies[i];
    }
    cout << "Original file size: " << oldTotal << " bits" << endl;
    cout << "Compressed file size: " << newTotal << " bits" << endl;


    uint32_t mappings[MAX_CHAR]; // 8 lsb is size of endoding and 24 msb is the encoding.
    
    for (int i = 0; i < MAX_CHAR; i++){
        const auto& str = codes_copy[i];
        uint32_t entry = 0;
        for (auto begin = str.rbegin(); begin != str.rend(); ++begin){
            // if (*begin == '1')
                // entry = entry |1;
            entry = entry | (*begin - 48); // 48 is the ascii value of '0'.
            entry = entry <<1;
        }
        entry = entry << 8; // shift entry 8 bits to include size.
        uint32_t size = str.size();
        entry |= size;
        mappings[i] = entry;
    }


    // read input file from beginning and encode
    char *in_buffer = new char[file_size];
    size_t nBytes = (newTotal+ 7)/8;
    char *out_buffer = new char[nBytes];

    file.read(in_buffer, file_size);

    std::cout << "Encoding file to compressed format" << std::endl;

    size_t pos = 0;
    for (size_t i = 0; i < file_size; i++){
        auto entry = mappings[in_buffer[i]];
        // uint8_t size = entry & 0xFF;
        // uint32_t symbol = entry >> 8;
        
        buffer_write(out_buffer, pos, entry);
        pos += (entry&0xFF);
    }

    std::cout << "Writing compressed file to disk" << std::endl;
    // write buffer to file?
    std::ofstream outFile (outFileName);

    outFile.write(out_buffer, nBytes);
    std::cout << "Compressed File write completed" << std::endl;
}


/**
 * Writes the given element to the buffer at specified bit index.
 */
void serial::buffer_write(char *out_buff, size_t pos, uint32_t element){
    // extract size and code 
    uint8_t size = element&0xFF;
    uint32_t symbol = element>>8; // pop 8 lsb.

    // compute the byte number and offset
    size_t byteNum = pos >> 3;
    size_t offset = pos & 0b111;

    for (int i = 0; i < size; i++){
        // pop lsb from symbol and write to out_buff
        // if the lsb is 1. 
        // if (symbol&1) {
        //     *(out_buff+byteNum) |= LookupTable[offset];
        // }
        // if ((offset++ %8) == 0) byteNum++;

        /* (offset&0b111) returns last three binary bits. subtracting this number from 7 gives
         * number of bits to shift left. */
        // *(out_buff+byteNum) |= ((symbol&1) << (7 - (pos&0b111)));
        // symbol = symbol>>1; // pop last bit. Popped bit already written to buffer.
        // byteNum += !((++pos)&0b111); // if offset reaches byte, move to next byte in buffer.

        *(out_buff + byteNum) |= ((symbol&1) << (7- (pos&0b111)));
        byteNum = (++pos)>>3;
        symbol = symbol>>1;
    }
}
