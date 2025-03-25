#include <iostream>
#include <vector>

#include "utils.hpp"
using namespace std;

int main() {
    vector<size_t> frequencies (256, 0);
    
    for (int i = 65; i < 90; i++){
        frequencies[i] = rand()%1000;
    }
    frequencies[65] = rand()%1000 + 1000000;

    huffman::HuffTree tree(frequencies);

    tree.printTree(frequencies);
}