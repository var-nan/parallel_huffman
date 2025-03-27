#include <iostream>
#include <vector>
#include <algorithm>

#include "huffman_serial.hpp"

using namespace std;

int main() {
    // vector<size_t> frequencies (256, 0);
    
    // for (int i = 65; i < 90; i++){
    //     frequencies[i] = rand()%1000;
    // }
    // frequencies[65] = rand()%1000 + 100000;

    // huffman::HuffTree tree(frequencies);

    // auto codes = tree.printTree(frequencies);

    // sort(codes.begin(), codes.end(), [](const string& a, const string& b){return a.size() < b.size();});

    // // for (const auto& s : codes) cout<< s << endl;
    // if (validate(codes)) cout << "generated codes are prefix codes" << endl;
    // else cout << "generated codes are not prefix codes" << endl;


    string inFile = "./dummy.txt";
    string outFile = "./dummy_enc.txt";

    serial::encode(inFile, outFile);

}