#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

typedef uint8_t Byte;
typedef uint16_t DByte;
typedef uint32_t uint;

enum BITS{
    ZERO    = 0b0,
    ONE     = 0b1,
    TWO     = 0b11,
    THREE   = 0b111,
    FOUR    = 0b1111,
    FIVE    = 0b11111,
    SIX     = 0b111111,
    SEVEN   = 0b1111111
};

static const vector<BITS> bits = {
                        BITS::ZERO, BITS::ONE, BITS::TWO,
                        BITS::THREE, BITS::FOUR,
                        BITS::FIVE, BITS::SIX, BITS::SEVEN
};

namespace huffman{

    typedef struct h_code{
        DByte symbol;
        Byte size;
    } h_code_tag;

    typedef struct leaves {
        struct h_node *zero = nullptr;
        struct h_node *one = nullptr;
    } child;

    typedef struct h_node {
        DByte id; // if id > 256, its not leaf node.
        union {
            child children;
            h_code_tag leaf;
        };

        h_node(DByte id_):id{id_}{}
    } h_node_t;

    class HuffTree {

        h_node *root;

        void fill(h_node_t *root, DByte tag, Byte level); // populates the leaf nodes.

    public:
        HuffTree(const vector<size_t> &frequencies);// build huffman tree from the frequencies
        
        h_code_tag encode(const Byte& byte);

        Byte decode(const Byte& byte);

        void printTree(const vector<size_t> &frequencies) const;

    };
}
