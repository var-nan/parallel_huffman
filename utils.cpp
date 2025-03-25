#include "utils.hpp"
#include <queue>

using namespace huffman;


HuffTree::HuffTree(const std::vector<size_t> &frequencies) {
    // create min_heap from frequencies

    auto comparator = [](const std::pair<h_node_t *, size_t>& a, const std::pair<h_node_t *, size_t>& b){
        return a.second > b.second;
    };

    std::priority_queue<std::pair<h_node_t *, size_t>,
            std::vector<std::pair<h_node_t *, size_t>>, decltype(comparator)> pq(comparator);

    for (uint16_t i = 0; i < 256; i++){
        if (!frequencies[i]) continue; // ignore zeros.
        //
        h_node_t *current = new h_node(i);
        pq.push({current, frequencies[i]});
    }

    struct h_node *current = nullptr;
    uint index = 256;

    while (pq.size() != 1){

        auto top1 = pq.top(); pq.pop();
        auto top2 = pq.top(); pq.pop();

        // merge two elements and push to queue.
        current = new h_node(++index);
        current->children.zero = top1.first;
        current->children.one = top2.first;

        pq.push({current, top1.second + top2.second});
    }

    // top element should be the root.
    auto top = pq.top(); pq.pop();
    root = top.first;

    // assign labels
    fill(root, static_cast<DByte>(1), 0);
}

void HuffTree::fill(h_node_t *root, uint16_t tag, uint8_t level) {

    if (root->id > 256) {
        if (root->children.zero) fill(root->children.zero, (tag<<1), level+1);
        if (root->children.one) fill(root->children.one, (tag<<1)|0b1, level+1);
    }
    else { // leaf node, popluate symbol and size;
        root->leaf.symbol = tag;
        root->leaf.size = level;
    }
}

void go(const h_node_t *current, const vector<size_t> &frequencies){
    auto str = [](Byte tag, Byte size){
        string s = "";
        for (int i = 0; i < size; i++){
            s = std::to_string(tag&0b1) + s;
            tag = tag>>1;
        }
        return s;
    };

    if (current->id < 256){
        cout << "Id: " << current->id << " , freq: " << frequencies[current->id]
            << "\t, size: " << to_string(current->leaf.size) << ", code: " 
            << str(current->leaf.symbol, current->leaf.size) << endl;
    }

    if (current->id >= 256){
        if (current->children.zero) go(current->children.zero, frequencies);
        if (current->children.one) go(current->children.one, frequencies);
    }
}

void HuffTree::printTree(const vector<size_t> &frequencies) const {

    go(root, frequencies);
    
}