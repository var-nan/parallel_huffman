#include "utils.hpp"
#include <queue>

using namespace huffman;


HuffTree::HuffTree(const std::vector<size_t> &frequencies) {
    // create min_heap from frequencies
    //
    auto comparator = [](const std::pair<h_node *, size_t>& a, const std::pair<h_node *, size_t>& b){
        return a.second > b.second;
    };

    std::priority_queue<std::pair<h_node *, size_t>,
            std::vector<std::pair<h_node *, size_t>>, decltype(comparator)> pq(comparator);

    for (uint i = 0; i < 256; i++){
        if (!frequencies[i]) continue; // ignore zeros.
        // create node
        h_node *current = new h_node();
        current->isLeaf = true;
        pq.push({current, frequencies[i]});
    }
    // build tree.

    h_node *current = nullptr;
    uint index = 256;

    while (pq.size() != 1){
        // pop two elements merge them.
        auto top1 = pq.top(); pq.pop();
        auto top2 = pq.top(); pq.pop();

        // merge 
        current = new h_node();
        current->isLeaf = false;
        current->children.one = top1.first;
        current->children.zero = top2.first;

    }

}
