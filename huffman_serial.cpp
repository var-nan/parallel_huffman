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

    // build tree basedon the frequencies
    
}
