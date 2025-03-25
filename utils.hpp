#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef unsigned char Byte;
typedef unsigned int uint;

namespace huffman{

    typedef struct h_code{
        Byte symbol;
        Byte size;
    } h_code_tag;

    typedef struct leaves {
        struct h_node *zero;
        struct h_node *one;
    } child;

    typedef struct h_node {
        unsigned char id;
        unsigned char isLeaf;
        union {
            child children;
            h_code_tag leaf;
        };
    } h_node_t;

    class HuffTree {

        h_node *root;

    public:
        HuffTree(const vector<size_t> &frequencies);// build huffman tree from the frequencies
        
        h_code_tag encode(const Byte& byte);

        Byte decode(const Byte& byte);

    };
}
